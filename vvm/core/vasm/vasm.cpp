//////////
//
// libsf/vvm/vasm/vasm.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 13, 2012
//////
// Change log:
//     November 13, 2012 - Initial creation
//////
// VVM Assembler Command Line Utility
// See devhelp.txt.
//////
//
// This software is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// You are free to use, copy, modify and share this software.  However, it can only
// be released under the PBL version indicated, and every project must include a copy
// of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org
//     http://www.visual-freepro.org/blog/
//     http://www.visual-freepro.org/forum/
//     http://www.visual-freepro.org/wiki/
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//



#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "\libsf\vvm\core\common\common.h"
#include "\libsf\vvm\core\vvmoss\oss_structs.h"
#include "\libsf\vvm\core\vvm\vvm_structs.h"
#include "\libsf\vvm\core\vvmmc\mc_structs.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_mc.h"
#include "\libsf\vvm\core\common\common_oss.h"
#include "\libsf\vvm\core\localization\vvmmcenu\resource.h"




// Global variables
u32			gnFilesProcessed					= 0;
u32			gnErrors							= 0;
u32			gnWarnings							= 0;
bool		glQuiet								= false;
bool		glIgnoreWarnings					= false;
s8*			gcResourceLanguage					= "enu";
HINSTANCE	vvmmcResourceDll					= NULL;


// Forward declarations
void		iProcessCommandLineLanguageOption	(s8* tcHyphenRColon);
void		iLoadDlls							(void);
void		iShowHelp							(void);
void		iAssembleFile						(s8* tcPathname);




//////////
//
// VVM Assembler command line syntax is simple:
//
//////
	int main(int argc, s8* argv[])
	{
		bool	llNull;
		s32		lnI, lnLength;


		// Tell the world who we are
		printf("Visual FreePro Virtual Machine Assembler 0.60\n");
		printf("Copyright (c) 2012 Rick C. Hodgin - Released under PBL1.0 - /? for help\n");
		printf("---\n");
		printf("---\n");


		// Repeat for every command line parameter
		for (lnI = 1; lnI < argc; lnI++)
		{
			llNull		= true;
			lnLength	= strlen(argv[lnI]);
			if (lnLength >= 2 && (_memicmp(argv[lnI], "/?", 2) == 0 || _memicmp(argv[lnI], "-h", 2) == 0 || _memicmp(argv[lnI], "/h", 2) == 0))
			{
				// They want help
				iShowHelp();

			} else if (lnLength > 3 && _memicmp(argv[lnI], "-r:", 3) == 0) {
				// They are specifying an override for the default language
				iProcessCommandLineLanguageOption(argv[lnI]);

			} else if (lnLength >= 2 && _memicmp(argv[lnI], "/q", 2) == 0) {
				// They want quiet mode
				glQuiet = true;

			} else if (lnLength >= 2 && _memicmp(argv[lnI], "/i", 2) == 0) {
				// They want to ignore warnings
				glIgnoreWarnings = true;

			} else {
				// We will soon try to open the indicated file, but not yet
				llNull = false;
			}

			// Set first byte null if we are done processing this entry
			if (llNull)
				argv[lnI][0] = 0;
		}
		// When we get here, we've done a first pass on the command line parameters


		// Try to load the OSS.DLL and MC.DLL files now that we have the language
		iLoadDlls();


		// Now, try to open and assemble the remaining files
		for (lnI = 1; lnI < argc; lnI++)
		{
			if (argv[lnI][0] != 0)
			{
				// Try to assemble this file
				iAssembleFile(argv[lnI]);
			}
		}


		// All done
		printf("---\n");
		printf(mc_loadResourceAsciiText(IDS_FILES_PROCESSED), gnFilesProcessed, gnErrors, gnWarnings);
		return gnErrors;
	}




	// Process -r:abc where "abc" is the language to load
	void iProcessCommandLineLanguageOption(s8* tcHyphenRColon)
	{
		u32 lnI;


		// Store the starting offset
		gcResourceLanguage = tcHyphenRColon + 3;
		for (lnI = 0; lnI < 3; lnI++)
		{
			if (gcResourceLanguage[lnI] == 0 || gcResourceLanguage[lnI] == 32)
			{
				// We found the delineator/end
				break;
			}
		}
		// When we get here, all done
		gcResourceLanguage[lnI] = 0;
	}




	void iLoadDlls(void)
	{
		// Try to load MC.DLL
		if (!iLoadVvmmcFunctionsFromDll() || !mc_loadResourceLanguage(gcResourceLanguage, (u64*)&vvmmcResourceDll))
		{
			printf("* Error:  Unable to load required MC.DLL.  Terminating with -2.\n");
			exit(-2);
		}


		// Try to load OSS.DLL
		if (!iLoadOssFunctionsFromDll())
		{
			printf("* Error:  Unable to load required VVMOSS.DLL.  Terminating with -1.\n");
			exit(-1);
		}
		if (!mc_loadVvmmOssFunctions())
		{
			printf("* Error:  VVMMC was unable to load required VVMOSS.DLL functions.  Terminating with -3.\n");
			exit(-3);
		}


		// Let it initialize itself
		oss_bootstrapInitialization(0);


		// Indicate the version we have loaded
		printf(mc_loadResourceAsciiText(IDS_LOADED), oss_getVersion());
		printf(mc_loadResourceAsciiText(IDS_LOADED), mc_getVersion());
		printf("---\n");
		printf("---\n");
	}




	void iShowHelp(void)
	{
		printf("--- Usage:  vasm [/?] [/i] [/q] file1.vasm file2.vasm file3.vasm fileN.vasm\n");
		printf("---              /? - this help screen\n");
		printf("---              /i - ignore warnings\n");
		printf("---              /q - quiet mode, only show total error+warning count\n");
// TODO:  Add a /Zi option to indicate whether or not to include debugger information in the output BXML file
		printf("---         Note:  Assembler output goes to file1.bxml, file2.bxml...\n");
		printf("---\n");
		printf("--- This application is Liberty Software (free to use, distribute), released\n");
		printf("--- under a Repeat License which you must follow and include as a recipient.\n");
		printf("---\n");
		printf("--- Released under PBL1.0, Public Benefit License, providing end-user rights.\n");
		printf("---\n");
		printf("--- www.libsf.org for information about Liberty Software.\n");
		printf("--- www.visual-freepro.org/wiki/index.php/PBL for Public Benefit License info.\n");
		printf("--- www.visual-freepro.org/wiki/index.php/Repeat_License for license info.\n");
		printf("---\n");
		printf("---\n");
	}




//////////
//
// Assembles the indicated file.vasm, creating a file.bxml
//
//////
	void iAssembleFile(s8* tcPathname)
	{
		u32				lnI, lnMachineCodeBytes, lnErrorCount, lnWarningCount;
		s64				lnHandle, lnFileSize, lnNumread;
		s8*				lcData;
		s8*				lcBxmlPathname;
		SStartEnd		lseProg;
		SProgram*		lp;			// program
		SVvmmcError*	lve;		// error
		SVvmmcWarning*	lvw;		// warning
		SAssembly*		la;			// assembly info
		SSourceFile*	lsf;		// top-level source file


		// Attempt to open the file
		lnHandle = oss_sharedAsciiOpenFile(tcPathname, false, true, false, false, false, false, false, false);
		if (lnHandle < 0)
		{
			// Open file error
			printf(mc_loadResourceAsciiText(IDS_UNABLE_TO_OPEN), tcPathname);
			++gnErrors;
			return;
		}
		// If we get here, we're good


		// Get file size
		lnFileSize = oss_sharedAsciiFileSize(lnHandle);
		if (lnFileSize > 0xffffffff)
		{
			// Uhhh... what are they trying to do to us? :-)
			printf(mc_loadResourceAsciiText(IDS_FILE_IS_TOO_BIG), tcPathname);
			++gnErrors;
			return;
		}
		if (lnFileSize == 0)
		{
			printf(mc_loadResourceAsciiText(IDS_FILE_IS_ZERO_BYTES), tcPathname);
			++gnErrors;
			return;
		}


		// Allocate memory to load
		lcData = (s8*)oss_alloc((u32)lnFileSize, false);
		if (!lcData)
		{
			printf(mc_loadResourceAsciiText(IDS_ERROR_ALLOCATING), lnFileSize, tcPathname);
			++gnErrors;
			return;
		}
		// If we get here, memory is allocated


		// Read into it
		lnNumread = oss_sharedAsciiReadFile(lnHandle, lcData, (u32)lnFileSize);
		if (lnNumread != lnFileSize)
		{
			printf(mc_loadResourceAsciiText(IDS_UNABLE_TO_READ_BYTES_FROM), (u32)lnFileSize, tcPathname, lnNumread);
			++gnErrors;
			return;
		}
		// We're good
		oss_sharedAsciiCloseFile(lnHandle);


		// Initialize our variables
		memset(&lseProg, 0, sizeof(lseProg));
		// Define this initial program to its default empty state
		lp = (SProgram*)vvm_SEChain_append(&lseProg, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SProgram), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);
		printf(mc_loadResourceAsciiText(IDS_ASSEMBLING), tcPathname);


		//////////
		// Physically conduct the assembly
		//////
			//
			//////
				//
				lnMachineCodeBytes = mc_assembleSourceCode(tcPathname, lcData, (u32)lnFileSize, lp);
				//
			//////
			//
		//////
		// END
		//////////


		// When we get here, we've assembled our source file, with warnings, errors, or whatever
		// Free up our processed memory
		oss_free(lcData);


		// See where we sit
		if (!lp->_assembly.root)
		{
			// A fatal, unrecoverable error occurred where we didn't even get the initial startup data allocated
			printf(mc_loadResourceAsciiText(IDS_UNRECOVERABLE_ERROR));
			++gnErrors;
			return;
		}
		// We're good.
		// Grab the top-level file info
		la		= (SAssembly*)lp->_assembly.root->ptr;			// SAssembly information
		lsf		= (SSourceFile*)la->includeFiles.root->ptr;		// Top-level source file (which contains the master list of all errors, warnings, and source file lines)


		// Report on warnings and errors
		if (!glQuiet)
		{
			// Report warnings
			if (!glIgnoreWarnings)
			{
				lnWarningCount = 0;
				for (lnI = 0; lnI < lsf->warnings.masterCount; lnI++)
				{
					if (lsf->warnings.master[lnI] && lsf->warnings.master[lnI]->used)
					{
						// Grab the warning data
						lvw = (SVvmmcWarning*)lsf->warnings.master[lnI]->ptr;
						printf("--- %s\n---   |W:%u L:%u C:%u - %s\n", lvw->pathName, lvw->code, lvw->lineNumber, lvw->column, lvw->text);
						++lnWarningCount;
					}
				}
			}

			// Report errors
			lnErrorCount = 0;
			for (lnI = 0; lnI < lsf->errors.masterCount; lnI++)
			{
				if (lsf->errors.master[lnI] && lsf->errors.master[lnI]->used)
				{
					// Grab the warning data
					lve = (SVvmmcError*)lsf->errors.master[lnI]->ptr;
					printf("--- %s\n---   |E:%u L:%u C:%u - %s\n", lve->pathName, lve->code, lve->lineNumber, lve->column, lve->text);
					++lnErrorCount;
				}
			}
		}


		// Write the output
		lcBxmlPathname = oss_changePathnameExtension(tcPathname, ".bxml");
		mc_saveSnippetsToBxml(lcBxmlPathname, &lseProg, true);
		oss_free(lcBxmlPathname);


		// Indicate we've processed another file
		++gnFilesProcessed;


		// Indicate our final status
		printf("---\n");
		printf(mc_loadResourceAsciiText(IDS_ERRORS_WARNINGS_FOUND), lsf->errors.masterCount, lsf->warnings.masterCount, tcPathname);
		printf("---\n");

		// Update global totals
		gnErrors	+= lnErrorCount;
		gnWarnings	+= lnWarningCount;
	}
