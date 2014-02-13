//////////
//
// /libsf/utils/f2h/f2h.cpp
//
//////
// Version 1.00
// Public Domain - See main() below for command line usage.
//////
// Last update:
//     February 18, 2013
//////
// Change log:
//     February 18, 2013 - Initial creation, compiles with Visual Studio 2008 Professional.
//////
//
// This software is released into the Public Domain.  Enjoy. :-)
//
//     http://www.libsf.org/
//
// Thank you.  And may The Lord bless you richly as you lift up
// your life, your talents, your gifts, your praise, unto Him.
// In Jesus' name I pray.  Amen.
//
//////




#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <memory.h>


// Common constants
typedef unsigned long long			u64;
typedef unsigned long				u32;
typedef unsigned short				u16;
typedef unsigned char				u8;

typedef long long					s64;
typedef long						s32;
typedef short						s16;
typedef char						s8;

typedef float						f32;
typedef double						f64;


// SHA-1 support
#include "\libsf\utils\sha1\sha1.h"
#include "\libsf\utils\sha1\sha1.cpp"


// Version
const s8 cgcVersion[]		= "File To C++ Header Converter, Version 1.00";


// Forward declarations
int		iAppendToBuffer		(char* buffer, int offset, char* asciiZ);
void	iShowUsage			(void);




//////////
//
// Top level program.
// Reads the command line parameters and takes the input file, producing a file suitable for
// inclusion as a .h file by converting its bytes to hexadecimal values.
//
//////
	int main(int argc, char* argv[])
	{
		int					lnVariableParameter, lnOutputNameParameter;
		unsigned long long	lnSha1As64;
		unsigned long		lnSha1As32;
		bool				llSha1, llSha1AsHex, llSha1As64Bit, llSha1As32Bit, llPublic;
		size_t				lnI, lnJ, lnFileSize, lnNumRead, lnTotalAllocatedBufferSize, lnLineCount, lnOffset, lnNumWritten;
		FILE*				lfh;
		char*				lcContent;					// The loaded file content
		char*				lcOutput;					// The output to write
		char				buffer[_MAX_PATH * 2];		// Holds temporary buffer data, as well as the full SHA-1 hexadecimal value
		unsigned char		sha20Bytes[20];


		// Tell the world who we are
		printf(" ____________________________________________________________________________\n");
		printf("|   |                                                                    |   |\n");
		printf("|F2H|     %s (Public Domain)     |F2H|\n", cgcVersion);
		printf("|___|     by Liberty Software Foundation Feb.18.2013 Rick C. Hodgin      |___|\n");


	//////////
	//
	// Command line must be in the form of three parameters:
	//		(0)			f2h.exe
	//		(1)			\path\to\input.bin
	//		(optional)	/sha1  -- include the 20-byte value as a sequence of bytes
	//		(optional)	/shex  -- include the 160-bit value as hexadecimal
	//		(optional)	/s64   -- include the 160-bit value computed down to a 64-bit value
	//		(optional)	/s32   -- include the 160-bit value computed down to a 32-bit value
	//		(optional)	/pub   -- include the __declspec(dllexport) prefix to make the symbol public
	//		(2)			variableName
	//		(3)			\path\to\output.h
	//		
	// Example:
	//		f2h \path\to\input.bin variableName \path\to\output.h
	//
	//////
		if (argc < 4)
		{
			// Command line syntax error
			iShowUsage();
			printf("\n");
			printf("Exiting.\n");
			return -1;
		}
		// If we get here, the parameter count is at least good


		// By default we assume there are no SHA-1 considerations
		lnVariableParameter		= 2;
		lnOutputNameParameter	= 3;
		llSha1					= false;
		llSha1AsHex				= false;
		llSha1As64Bit			= false;
		llSha1As32Bit			= false;
		llPublic				= false;

		// Iterate through each parameter
		for (lnI = 2; lnI < (u32)argc - 2; lnI++)
		{
			if (argv[lnI][0] == '/')
			{
				// This is a parameter
				// Move over the required fixed parameters
				++lnVariableParameter;
				++lnOutputNameParameter;

				// See what it is
				if (_memicmp(argv[lnI], "/sha1", 5) == 0)
				{
					llSha1 = true;

				} else if (_memicmp(argv[lnI], "/shex", 5) == 0) {
					llSha1AsHex = true;

				} else if (_memicmp(argv[lnI], "/s64", 5) == 0) {
					llSha1As64Bit = true;

				} else if (_memicmp(argv[lnI], "/s32", 5) == 0) {
					llSha1As32Bit = true;

				} else if (_memicmp(argv[lnI], "/pub", 5) == 0) {
					llPublic = true;

				} else {
					// Syntax error
					printf("Unrecognized command line option:  %s\n", argv[lnI]);
					printf("\n");
					printf("Exiting.\n");
					exit(-100);
				}
			}
		}


		//////////
		// Open the file
		//////
			fopen_s(&lfh, argv[1], "rb");		// File must exist, read-only, binary
			if (!lfh)
			{
				iShowUsage();
				printf("Error:  Unable to open %s.\n", argv[1]);
				printf("\n");
				printf("Exiting.\n");
				return -2;
			}
			// When we get here, the file is open
			fseek(lfh, 0, SEEK_END);
			lnFileSize = ftell(lfh);
			fseek(lfh, 0, SEEK_SET);


		//////////
		// Allocate our buffer to read in the file
		//////
			lcContent = (char*)malloc(lnFileSize);
			if (!lcContent)
			{
				iShowUsage();
				printf("Error:  Unable to allocate %u bytes of memory for input file.\n", lnFileSize);
				printf("\n");
				printf("Exiting.\n");
				return -3;
			}


		//////////
		// Load the content
		//////
			lnNumRead = fread(lcContent, 1, lnFileSize, lfh);
			if (lnNumRead != lnFileSize)
			{
				iShowUsage();
				printf("Error:  Unable to read %u bytes from %s.\n", lnFileSize, argv[1]);
				printf("\n");
				printf("Exiting.\n");
				return -4;
			}
			fclose(lfh);


		//////////
		//
		// Allocate space for the output buffer.  Each line will look (at most) like this:
		//  ___________________________________________________________________________________________________________
		// |         1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20
		// |		===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===  ===
		// |          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
		// |        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
		// |____________________________________________________________________________________________________________
		//
		// Our allocation formula assumes a minimum of 6 lines of overhead, plus one full line (109 characters + CR + LF):
		//		lnTotalAllocatedBufferSize = ((lnFileSize / 20) + 6) * 111
		// For every logical llSha1* output, we add another 111 bytes
		// This will always result in a buffer that is too big.  However, it will never be
		// too small, and it will only be marginally too big.
		//
		//////
			lnTotalAllocatedBufferSize	= ((lnFileSize / 20) + 6) * 111;
			lnTotalAllocatedBufferSize	+= ((llSha1)		? 111 : 0);
			lnTotalAllocatedBufferSize	+= ((llSha1AsHex)	? 111 : 0);
			lnTotalAllocatedBufferSize	+= ((llSha1As64Bit)	? 111 : 0);
			lnTotalAllocatedBufferSize	+= ((llSha1As32Bit)	? 111 : 0);

			// Allocate the buffer
			lcOutput = (char*)malloc(lnTotalAllocatedBufferSize);
			if (!lcOutput)
			{
				iShowUsage();
				printf("Error:  Unable to allocate %u bytes of memory for output file.\n", lnFileSize);
				printf("\n");
				printf("Exiting.\n");
				return -5;
			}
			// Initialize it to all NULLs
			memset(lcOutput, 0, lnTotalAllocatedBufferSize);
			memset(buffer, 0, sizeof(buffer));


		//////////
		// Prepare the header
		//////
			// Identification
			sprintf_s(buffer, sizeof(buffer), "// Created using f2h.exe (%s)\n", cgcVersion);
			iAppendToBuffer(lcOutput, strlen(lcOutput), buffer);

			// Command line
			iAppendToBuffer(lcOutput, strlen(lcOutput), "// Command line: ");
			for (lnI = 0; lnI < (u32)argc; lnI++)
			{
				iAppendToBuffer(lcOutput, strlen(lcOutput), argv[lnI]);
				iAppendToBuffer(lcOutput, strlen(lcOutput), " ");
			}
			iAppendToBuffer(lcOutput, strlen(lcOutput), "\n\n");

			// Optional SHA1 values
			if (llSha1 || llSha1AsHex || llSha1As64Bit || llSha1As32Bit)
			{
				// Compute the SHA-1 value
				sha1_computeSha1((const u8*)lcContent, lnFileSize, sha20Bytes);
				lnSha1As64	= sha1_convertSha20To64Bit(sha20Bytes);
				lnSha1As32	= sha1_convertSha20To32Bit(sha20Bytes);

				// Render it as has been requested
				// In 20-byte raw form
				if (llSha1)
				{
					if (llPublic)	iAppendToBuffer(lcOutput, strlen(lcOutput), "__declspec(dllexport) \0");
					// u8 varSha1[] = { 0, 0, ... }
					iAppendToBuffer(lcOutput, strlen(lcOutput),		"const  u8 cgc_\0");
					iAppendToBuffer(lcOutput, strlen(lcOutput),		argv[lnVariableParameter]);
					iAppendToBuffer(lcOutput, strlen(lcOutput),		"Sha1[20]\t\t= { ");
					for (lnI = 0; lnI < 20; lnI++)
					{
						sprintf_s(buffer, sizeof(buffer), "0x%02x%s\0", sha20Bytes[lnI], ((lnI + 1 < 20) ? ", " : " "));
						iAppendToBuffer(lcOutput, strlen(lcOutput), buffer);
					}
					iAppendToBuffer(lcOutput, strlen(lcOutput),		"};\n");
				}

				// In hexadecimal form
				if (llSha1AsHex)
				{
					if (llPublic)	iAppendToBuffer(lcOutput, strlen(lcOutput), "__declspec(dllexport) \0");
					// u8 varSha1AsHex[] = { 0, 0, ... }
					sha1_convertSha20ToHex(sha20Bytes, buffer, true);
					buffer[44] = 0;		// NULL terminate
					iAppendToBuffer(lcOutput, strlen(lcOutput),		"const  u8 cgc_\0");
					iAppendToBuffer(lcOutput, strlen(lcOutput),		argv[lnVariableParameter]);
					iAppendToBuffer(lcOutput, strlen(lcOutput),		"Sha1AsHex[]\t= \"");
					iAppendToBuffer(lcOutput, strlen(lcOutput),		buffer);
					iAppendToBuffer(lcOutput, strlen(lcOutput),		"\";\n");
				}

				// In 64-bit hexadecimal integer form
				if (llSha1As64Bit)
				{
					if (llPublic)	iAppendToBuffer(lcOutput, strlen(lcOutput), "__declspec(dllexport) \0");
					// u8 varSha1As64Bit[] = 0x000
					iAppendToBuffer(lcOutput, strlen(lcOutput),		"const u64 cgn_\0");
					iAppendToBuffer(lcOutput, strlen(lcOutput),		argv[lnVariableParameter]);
					iAppendToBuffer(lcOutput, strlen(lcOutput),		"Sha1As64Bit\t= ");
					sprintf_s(buffer, sizeof(buffer), "0x%016llx\0", lnSha1As64);
					iAppendToBuffer(lcOutput, strlen(lcOutput),		buffer);
					iAppendToBuffer(lcOutput, strlen(lcOutput),		";\n");
				}

				// In 32-bit hexadecimal integer form
				if (llSha1As32Bit)
				{
					if (llPublic)	iAppendToBuffer(lcOutput, strlen(lcOutput), "__declspec(dllexport) \0");
					// u8 varSha1As64Bit[] = 0x000
					iAppendToBuffer(lcOutput, strlen(lcOutput),		"const u32 cgn_\0");
					iAppendToBuffer(lcOutput, strlen(lcOutput),		argv[lnVariableParameter]);
					iAppendToBuffer(lcOutput, strlen(lcOutput),		"Sha1As32Bit\t= ");
					sprintf_s(buffer, sizeof(buffer), "0x%08lx\0",	lnSha1As32);
					iAppendToBuffer(lcOutput, strlen(lcOutput),		buffer);
					iAppendToBuffer(lcOutput, strlen(lcOutput),		";\n");
				}

				// Double-space
				iAppendToBuffer(lcOutput, strlen(lcOutput), "\n");
			}


			// Comment about what the input file is
			iAppendToBuffer(lcOutput, strlen(lcOutput),		"// source file \"\0");
			iAppendToBuffer(lcOutput, strlen(lcOutput),		argv[1]);
			iAppendToBuffer(lcOutput, strlen(lcOutput),		"\"\n\0");

			// If we're public, prepend the line
			if (llPublic)
				iAppendToBuffer(lcOutput, strlen(lcOutput),		"__declspec(dllexport) \0");

			// Actual data
			iAppendToBuffer(lcOutput, strlen(lcOutput),		"const  u8 cgc_\0");
			iAppendToBuffer(lcOutput, strlen(lcOutput),		argv[lnVariableParameter]);
			sprintf_s(buffer, sizeof(buffer), "[%u] = \n", lnFileSize);
			iAppendToBuffer(lcOutput, strlen(lcOutput),		buffer);
			iAppendToBuffer(lcOutput, strlen(lcOutput),		"    {\n        ");


		//////////
		// Write the middle bytes repeatedly
		//////
			lnOffset	= strlen(lcOutput);
			lnLineCount	= 0;
			for (lnI = 0; lnI < lnFileSize; lnI++)
			{
				// Prepare this byte
				sprintf_s(buffer, sizeof(buffer), "%3u%s\0", (u8)lcContent[lnI], ((lnI + 1 < lnFileSize) ? ", " : ""));

				// Remove leading zeros
				for (lnJ = 0; buffer[lnJ] == '0'; lnJ++)
					buffer[lnJ] = ' ';		// Replace with space

				// Store to the buffer
				lnOffset += iAppendToBuffer(lcOutput, lnOffset, buffer);

				// If we've more bytes, see if we're done with this line
				if (lnI + 1 < lnFileSize)
				{
					// We have at least one more byte to go
					++lnLineCount;
					if (lnLineCount == 20)
					{
						// We've reached the end of this line, prepare for the next line
						lnOffset	+= iAppendToBuffer(lcOutput, lnOffset, "\n        ");
						lnLineCount	= 0;		// Start our line count back over
					}
				}
				// Continue on so long as we're continuing on
			}


		//////////
		// Append the footer
		//////
			lnOffset += iAppendToBuffer(lcOutput, lnOffset, "\n    };\n");
			// All done


		//////////
		// Write the output
		//////
			fopen_s(&lfh, argv[lnOutputNameParameter], "wb+");		// Read/write, create if does not exist, binary
			if (!lfh)
			{
				iShowUsage();
				printf("Error:  Unable to create %s.\n", argv[lnOutputNameParameter]);
				printf("\n");
				printf("Exiting.\n");
				return -6;
			}
			// File is open
			lnNumWritten = fwrite(lcOutput, 1, lnOffset, lfh);
			if (lnNumWritten != lnOffset)
			{
				iShowUsage();
				printf("Error:  Unable to write %u bytes to %s.\n", lnFileSize, argv[1]);
				printf("\n");
				printf("Exiting.\n");
				return -7;
			}
			// All done
			fclose(lfh);


		//////////
		// Success
		//////
			printf(" ___\n");
			printf("|\n");
			printf("| Wrote %u bytes to %s successfully\n", lnOffset, argv[lnOutputNameParameter]);
			printf("|___\n");
        

		// We're good
		return 0;
	}




//////////
//
// Takes as input a null-terminated string for the buffer, and appends the null-terminated
// string (including the NULL)
//
//////
	int iAppendToBuffer(char* buffer, int offset, char* asciiZ)
	{
		int lnLength;

		lnLength = strlen(asciiZ);
		memcpy(buffer + offset, asciiZ, lnLength + 1);
		return(lnLength);
	}
;




//////////
//
// Show the user the usage for this app
//
//////
	void iShowUsage(void)
	{
		printf(" __\n");
		printf("|\n");
		printf("|  Usage:  f2h input.bin [/sha1] [/s64] [/s32] [/pub] variableName output.h\n");
		printf("|Example:  f2h \\myGraphics\\greenDoor.png pngGreenDoor \\myProject\\greenDoor.h\n");
		printf("|           __\n");
		printf("|          |\n");
		printf("|          |const  u8 pngGreenDoorSha1[20]    = { 0, 0, ... }  // \"/sha1\"\n");
		printf("|          |const  u8 pngGreenDoorSha1AsHex[] = \"0a0383..\"     // \"/shex\"\n");
		printf("|          |const u64 pngGreenDoorSha1As64Bit = 0x0            // \"/s64\"\n");
		printf("|          |const u32 pngGreenDoorSha1As32Bit = 0x0            // \"/s32\"\n");
		printf("|          |\n");
		printf("|          |const  u8 pngGreenDoor[] = \n");
		printf("|          |    {\n");
		printf("|          |        0, 0, 255, .... continues on for every byte in input.png\n");
		printf("|          |    };\n");
		printf("|          |__\n");
		printf("|\n");
		printf("| If you need several files concatenated together into one, run f2h to\n");
		printf("| generate each part, then use:  COPY file1+file2+fileN outputFile\n");
		printf("|__\n");
	}
