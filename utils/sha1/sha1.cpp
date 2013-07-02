//////////
//
// /libsf/utils/sha1/sha1.cpp
//
// Note:  For testing this in Visual Studio, see the #define _TEST_ME line.  It is not
//        normally un-commented so the sha1.cpp can be directly included in other projects.
//        However, for testing it must be uncommented to expose the main() function and
//        related at the end of this source code file.
//
//////
// Version 1.00
// Public Domain - See sha1_continueOnThisData() for instructions on how to process a SHA1 value.
//////
// Last update:
//     February 16, 2013
//////
// Change log:
//     February 16, 2013 - Initial creation, compiles with Visual Studio 2008 Professional.
//     February 17, 2013 - Added hexadecimal to sha-1 160-bit format conversion in preparation for use in VVMOSS
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
//////////
//
// Prior work attribution:
//		SHA-1 in C by Steve Reid <sreid@sea-to-sky.net> 100% Public Domain
//		Modified 7/98 By James H. Brown <jbrown@burgoyne.com> Still 100% Public Domain
//		Modified 8/98 By Steve Reid <sreid@sea-to-sky.net> Still 100% public domain
//		Modified 4/01 By Saul Kravitz <Saul.Kravitz@celera.com> Still 100% public domain
//		Modified 07/2002 By Ralph Giles <giles@ghostscript.com> Still 100% public domain
//		Note:  In the same directory as this sha1.cpp file, there should be a file named
//		       sha1_original.txt.  It contains information about the original algorithm,
//		       with a diff being possible to see how it was changed.
//
//////////
//
// Test module exists at the end of this source code.  Un-comment the #define _TEST_ME line.
// Test Vectors (from FIPS PUB 180-1)
//
//		"abc"
//		  A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
//
//		"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
//		  84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
//
//		A million repetitions of "a"
//		  34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
//
//////




// This constant should only be defined when testing from within the sha1.sln project.
// #define _TEST_ME
#ifdef _TEST_ME
	#include <stdio.h>
	#include <string.h>
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
	#include "sha1.h"
#endif




//////////
// Base rol() algorithm
//////
	#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

//////////
// blk0() and blk() perform the initial expand.
//////
	#define blk0(lnI)	(block._u32_data[lnI]		=   (rol(block._u32_data[lnI], 24) & 0xff00ff00) | (rol(block._u32_data[lnI], 8)  & 0x00ff00ff))
	#define blk(lnI)	(block._u32_data[lnI & 15]	=    rol(block._u32_data[(lnI + 13) & 15] ^ block._u32_data[(lnI + 8) & 15] ^ block._u32_data[(lnI + 2) & 15] ^ block._u32_data[lnI & 15], 1))

//////////
// (R0 + R1), R2, R3, R4 are the different operations used in SHA1
//////
	#define R0(v,w,x,y,z,lnI) z +=	((w & (x ^ y)) ^ y)       + blk0(lnI) + 0x5a827999 + rol(v, 5); \
									w = rol(w, 30);

	#define R1(v,w,x,y,z,lnI) z += 	((w & (x ^ y)) ^ y)       + blk(lnI)  + 0x5a827999 + rol(v, 5); \
									w = rol(w, 30);

	#define R2(v,w,x,y,z,lnI) z += 	(w ^ x ^ y)               + blk(lnI)  + 0x6ed9eba1 + rol(v, 5); \
									w = rol(w, 30);

	#define R3(v,w,x,y,z,lnI) z += 	(((w | x) & y) | (w & x)) + blk(lnI)  + 0x8f1bbcdc + rol(v, 5); \
									w = rol(w, 30);

	#define R4(v,w,x,y,z,lnI) z += 	(w ^ x ^ y)               + blk(lnI)  + 0xca62c1d6 + rol(v, 5); \
									w = rol(w, 30);


//////////
// Structures
//////
	struct SSha1Context
	{
		u32		state[5];				// Offset 0, Length 20
		u32		count[2];				// Offset 20, Length 8
		u8		buffer[64];				// Offset 28, Length 64
		// Total:  92 bytes
	};

	union UnionChar64AndLong16
	{
		u8		_u8_data[64];
		u32		_u32_data[16];
	};




//////////
// Forward declarations
//////
	// Additional declarations are in sha1.h (see above _TEST_ME definition)
			void		sha1_initialize						(SSha1Context* context);
			void		sha1_continueOnThisData				(SSha1Context* context, const u8* tcData, u32 tnLength);
			void		sha1_finalize						(SSha1Context* context, u8 sha20Bytes[_SHA1_NUMBER_SIZE], bool tlWipeData);
	static 	void		isha1_transform						(u32 state[5], const u8 buffer[64]);
			u8			isha1_hexFF_ToCharacter				(const s8* tcHexFF, bool* tlErrorFound);
			bool		isha1_isHexDigit					(u8 c);




//////////
//
// A function to conduct the entire operation of computing a SHA-1 value in one call on one
// set of data.
//
//////
	void sha1_computeSha1(const u8* tcData, u32 tnLength, u8 sha20Bytes[_SHA1_NUMBER_SIZE])
	{
		SSha1Context	lsContext;


		// Initialize our context
		sha1_initialize(&lsContext);
		sha1_continueOnThisData(&lsContext, tcData, tnLength);
		sha1_finalize(&lsContext, sha20Bytes, false);
	}




//////////
//
// A function to convert a previously computed 20-byte SHA-1 value into hexadecimal.
// An option allows it to appear concatenated, or natively.
//
//////
	void sha1_convertSha20ToHex(const u8 sha20Bytes[_SHA1_NUMBER_SIZE], s8* tcHexOutput, bool tlSpacesBetween)
	{
		u32		lnI;
		s8		buffer[64];


		// Make sure our environment is sane
		if (tcHexOutput)
		{
			// Iterate through all twenty 8-bit quantities
			memset(buffer, 0, sizeof(buffer));
			for (lnI = 0; lnI < _SHA1_NUMBER_SIZE; lnI++)
			{
				// Convert this 32-bit quantity to hexadecimal
				sprintf_s(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "%02x\0", sha20Bytes[lnI]);

				// Append a space between each 32-bit quantity if they want
				if (tlSpacesBetween && lnI != 0 && (lnI + 1) % 4 == 0)
					sprintf_s(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), " ");
			}

			// When we get here, we have our string
			memcpy(tcHexOutput, buffer, strlen(buffer));
		}
	}




//////////
//
// Called to compute the SHA-1 and convert it to hexadecimal automatically
//
//////
	void sha1_computeSha1AsHex(const u8* tcData, u32 tnLength, u8 sha20Bytes[_SHA1_NUMBER_SIZE], s8* tcHexOutput, bool tlSpacesBetween)
	{
		sha1_computeSha1(tcData, tnLength, sha20Bytes);
		sha1_convertSha20ToHex(sha20Bytes, tcHexOutput, tlSpacesBetween);
	}




//////////
//
// Called to convert a text-based hexadecimal representation of a SHA-1 20-byte value
// into its true 20-byte value.
//
//////
	void sha1_convertHexToSha20(const s8* tcHexInput, u8 sha20Bytes[_SHA1_NUMBER_SIZE], bool* tlError)
	{
		u8		c;
		u32		lnSha20Offset, lnHexInputOffset;
		bool	llErrorFound;


		// Make sure our environment is sane
		llErrorFound = true;
		if (tcHexInput)
		{
			// Assume no failure
			llErrorFound = false;
			for (lnHexInputOffset = 0, lnSha20Offset = 0;
				 lnSha20Offset < _SHA1_NUMBER_SIZE;
				 lnHexInputOffset += 2, lnSha20Offset++)
			{
				// Skip any whitespaces
				while (tcHexInput[lnHexInputOffset] == 9 || tcHexInput[lnHexInputOffset] == 32)
					++lnHexInputOffset;

				// Convert from hexadecimal text to an unsigned character
				c = isha1_hexFF_ToCharacter(tcHexInput + lnHexInputOffset, &llErrorFound);
				if (llErrorFound)
					break;		// We encountered something wrong in the input stream

				// Store this byte
				sha20Bytes[lnSha20Offset] = c;
			}
			// When we get here, llErrorFound indicates our status
		}
		// Indicate our success or not
		if (tlError)
			*tlError = llErrorFound;
	}

	u8 isha1_hexFF_ToCharacter(const s8* tcHexFF, bool* tlErrorFound)
	{
		u8		c, c1, c2;
		bool	llErrorFound;


		// Make sure our environment is sane
		c				= 0;
		llErrorFound	= false;
		while (tcHexFF)
		{
			// Grab our bytes
			c1	= tcHexFF[0];
			c2	= tcHexFF[1];

			// Make sure the bytes are lower-case
			if (c1 >= 'A' && c1 <= 'Z')		c1 += 0x20;
			if (c2 >= 'A' && c2 <= 'Z')		c2 += 0x20;

			// Make sure they are hex digits
			if (!isha1_isHexDigit(c1) || !isha1_isHexDigit(c2))
			{
				// Not a digit
				llErrorFound = true;
				break;
			}

			// Convert to decimal
			// Upper nibble
			if (c1 >= 'a' && c1 <= 'f')		c1 = c1 - 'a' + 10;		// a..f
			else							c1 = c1 - '0';			// 0..9

			// Lower nibble
			if (c2 >= 'a' && c2 <= 'f')		c2 = c2 - 'a' + 10;		// a..f
			else							c2 = c2 - '0';			// 0..9

			// Combine
			c = (c1 << 4) | c2;

			// When we get here, we're good
			break;
		}
		// Indicate our status
		if (tlErrorFound)
			*tlErrorFound = llErrorFound;

		// Return our last character converted (if any)
		return(c);
	}

	bool isha1_isHexDigit(u8 c)
	{
			 if (c >= 'a' && c <= 'f')		return true;		// a..f
		else if (c >= '0' && c <= '9')		return true;		// 0..9
		else								return false;		// Something else
	}




//////////
//
// Initialize a new context (to begin computing a SHA-1)
//
//////
	// Used for access outside of the SHA-1 framework
	void sha1_92initialize(u8 context[92])
	{
		sha1_initialize((SSha1Context*)context);
	}

	void sha1_initialize(SSha1Context* context)
	{
		// SHA1 initialization constants
		context->state[0]	= 0x67452301;
		context->state[1]	= 0xefcdab89;
		context->state[2]	= 0x98badcfe;
		context->state[3]	= 0x10325476;
		context->state[4]	= 0xc3d2e1f0;

		context->count[0]	= 0;
		context->count[1]	= 0;
	}




//////////
//
// Run your data through this, referencing the prior context created in sha1_initialize().
//
// Example usage:
//		See the sha1_computeSha1() function above.
//
//////
	// Used for access outside of the SHA-1 framework
	void sha1_92continueOnThisData(u8 context[92], const u8* tcData, u32 tnLength)
	{
		sha1_continueOnThisData((SSha1Context*)context, tcData, tnLength);
	}

	void sha1_continueOnThisData(SSha1Context* context, const u8* tcData, u32 tnLength)
	{
		u32 lnI, lnJ;


		lnJ = (context->count[0] >> 3) & 63;

		if ((context->count[0] += tnLength << 3) < (tnLength << 3))
			context->count[1]++;

		context->count[1] += (tnLength >> 29);
		if ((lnJ + tnLength) > 63)
		{
			memcpy(&context->buffer[lnJ], tcData, (lnI = 64-lnJ));
			isha1_transform(context->state, context->buffer);
			for ( ; lnI + 63 < tnLength; lnI += 64)
				isha1_transform(context->state, tcData + lnI);
				
			lnJ = 0;
			
		} else {
			lnI = 0;
		}

		memcpy(&context->buffer[lnJ], &tcData[lnI], tnLength - lnI);
	}




//////////
//
// Add padding and return the message as a 20-byte quantity (160 bits).
//
//////
	// Used for access outside of the SHA-1 framework
	void sha1_92finalize(u8 context[92], u8 sha20Bytes[_SHA1_NUMBER_SIZE], bool tlWipeData)
	{
		sha1_finalize((SSha1Context*)context, sha20Bytes, tlWipeData);
	}

	void sha1_finalize(SSha1Context* context, u8 sha20Bytes[_SHA1_NUMBER_SIZE], bool tlWipeData)
	{
		u32		lnI;
		u8		finalcount[8];


		for (lnI = 0; lnI < 8; lnI++)
			finalcount[lnI] = (unsigned char)((context->count[(lnI >= 4 ? 0 : 1)] >> ((3-(lnI & 3)) * 8) ) & 255);

		sha1_continueOnThisData(context, (u8 *)"\200", 1);
		while ((context->count[0] & 504) != 448)
			sha1_continueOnThisData(context, (u8 *)"\0", 1);

		sha1_continueOnThisData(context, finalcount, 8);  // Should cause a SHA1_Transform()
		for (lnI = 0; lnI < _SHA1_NUMBER_SIZE; lnI++)
			sha20Bytes[lnI] = (u8)((context->state[lnI>>2] >> ((3-(lnI & 3)) * 8) ) & 255);

		// Wipe variables
		if (tlWipeData)
		{
			memset(context->buffer,		0, 64);
			memset(context->state,		0, 20);
			memset(context->count,		0, 8);
		}

		// Always reset our local variables
		lnI = 0;
		memset(finalcount, 0, 8);
	}




//////////
//
// Called to convert the 160-bit format into a more manageable 64- or 32-bit form using basic
// math conversions.  Is not as accurate as the 160-bit form, but is more manageable.
//
//////
	u64 sha1_convertSha20To64Bit(u8 sha20Bytes[_SHA1_NUMBER_SIZE])
	{
		u32	lnI;
		u64	lnValue;


		// Add up the 64-bit quantities atop a palindrome of my birthday! :-)
		lnValue = 0x0810196996190180;
		for (lnI = 0; lnI < 2; lnI++)
			lnValue += *((u64*)&sha20Bytes[lnI * 8]);

		// Add in the last 32-bit quantity to both 32-bit halves
		lnValue += (u64)(*((u32*)&sha20Bytes[16]));				// Add to lower 32-bit quantity
		lnValue += (u64)(*((u32*)&sha20Bytes[16])) << 32;		// Add to upper 32-bit quantity

		// We have our sum
		return(lnValue);
	}

	u32 sha1_convertSha20To32Bit(u8 sha20Bytes[_SHA1_NUMBER_SIZE])
	{
		u32 lnI, lnValue;


		// Add up the 32-bit quantities atop my birthday! :-)
		lnValue = 0x08101969;
		for (lnI = 0; lnI < 5; lnI++)
			lnValue += *((u32*)&sha20Bytes[lnI * 4]);

		// We have our sum
		return(lnValue);
	}

	bool sha1_compare(u8 sha20Bytes1[_SHA1_NUMBER_SIZE], u8 sha20Bytes2[_SHA1_NUMBER_SIZE])
	{
#ifdef icommon_memicmp
		return(icommon_memicmp(sha20Bytes1, sha20Bytes2, 20) == 0);
#else
		return(_memicmp(sha20Bytes1, sha20Bytes2, 20) == 0);
#endif
	}




//////////
//
// Hash a single 512-bit block. This is the core of the algorithm.
//
//////
	static void isha1_transform(u32 state[5], const u8 buffer[64])
	{
		u32		lnA, lnB, lnC, lnD, lnE;
		UnionChar64AndLong16	block;


		// Copy the 64-byte (512 bit) block
		memcpy(&block, buffer, 64);

		// Copy context->state[] to working vars
		lnA = state[0];
		lnB = state[1];
		lnC = state[2];
		lnD = state[3];
		lnE = state[4];

		// 4 rounds of 20 operations each. Loop unrolled
		R0(lnA,lnB,lnC,lnD,lnE, 0); R0(lnE,lnA,lnB,lnC,lnD, 1); R0(lnD,lnE,lnA,lnB,lnC, 2); R0(lnC,lnD,lnE,lnA,lnB, 3);
		R0(lnB,lnC,lnD,lnE,lnA, 4); R0(lnA,lnB,lnC,lnD,lnE, 5); R0(lnE,lnA,lnB,lnC,lnD, 6); R0(lnD,lnE,lnA,lnB,lnC, 7);
		R0(lnC,lnD,lnE,lnA,lnB, 8); R0(lnB,lnC,lnD,lnE,lnA, 9); R0(lnA,lnB,lnC,lnD,lnE,10); R0(lnE,lnA,lnB,lnC,lnD,11);
		R0(lnD,lnE,lnA,lnB,lnC,12); R0(lnC,lnD,lnE,lnA,lnB,13); R0(lnB,lnC,lnD,lnE,lnA,14); R0(lnA,lnB,lnC,lnD,lnE,15);
		R1(lnE,lnA,lnB,lnC,lnD,16); R1(lnD,lnE,lnA,lnB,lnC,17); R1(lnC,lnD,lnE,lnA,lnB,18); R1(lnB,lnC,lnD,lnE,lnA,19);
		R2(lnA,lnB,lnC,lnD,lnE,20); R2(lnE,lnA,lnB,lnC,lnD,21); R2(lnD,lnE,lnA,lnB,lnC,22); R2(lnC,lnD,lnE,lnA,lnB,23);
		R2(lnB,lnC,lnD,lnE,lnA,24); R2(lnA,lnB,lnC,lnD,lnE,25); R2(lnE,lnA,lnB,lnC,lnD,26); R2(lnD,lnE,lnA,lnB,lnC,27);
		R2(lnC,lnD,lnE,lnA,lnB,28); R2(lnB,lnC,lnD,lnE,lnA,29); R2(lnA,lnB,lnC,lnD,lnE,30); R2(lnE,lnA,lnB,lnC,lnD,31);
		R2(lnD,lnE,lnA,lnB,lnC,32); R2(lnC,lnD,lnE,lnA,lnB,33); R2(lnB,lnC,lnD,lnE,lnA,34); R2(lnA,lnB,lnC,lnD,lnE,35);
		R2(lnE,lnA,lnB,lnC,lnD,36); R2(lnD,lnE,lnA,lnB,lnC,37); R2(lnC,lnD,lnE,lnA,lnB,38); R2(lnB,lnC,lnD,lnE,lnA,39);
		R3(lnA,lnB,lnC,lnD,lnE,40); R3(lnE,lnA,lnB,lnC,lnD,41); R3(lnD,lnE,lnA,lnB,lnC,42); R3(lnC,lnD,lnE,lnA,lnB,43);
		R3(lnB,lnC,lnD,lnE,lnA,44); R3(lnA,lnB,lnC,lnD,lnE,45); R3(lnE,lnA,lnB,lnC,lnD,46); R3(lnD,lnE,lnA,lnB,lnC,47);
		R3(lnC,lnD,lnE,lnA,lnB,48); R3(lnB,lnC,lnD,lnE,lnA,49); R3(lnA,lnB,lnC,lnD,lnE,50); R3(lnE,lnA,lnB,lnC,lnD,51);
		R3(lnD,lnE,lnA,lnB,lnC,52); R3(lnC,lnD,lnE,lnA,lnB,53); R3(lnB,lnC,lnD,lnE,lnA,54); R3(lnA,lnB,lnC,lnD,lnE,55);
		R3(lnE,lnA,lnB,lnC,lnD,56); R3(lnD,lnE,lnA,lnB,lnC,57); R3(lnC,lnD,lnE,lnA,lnB,58); R3(lnB,lnC,lnD,lnE,lnA,59);
		R4(lnA,lnB,lnC,lnD,lnE,60); R4(lnE,lnA,lnB,lnC,lnD,61); R4(lnD,lnE,lnA,lnB,lnC,62); R4(lnC,lnD,lnE,lnA,lnB,63);
		R4(lnB,lnC,lnD,lnE,lnA,64); R4(lnA,lnB,lnC,lnD,lnE,65); R4(lnE,lnA,lnB,lnC,lnD,66); R4(lnD,lnE,lnA,lnB,lnC,67);
		R4(lnC,lnD,lnE,lnA,lnB,68); R4(lnB,lnC,lnD,lnE,lnA,69); R4(lnA,lnB,lnC,lnD,lnE,70); R4(lnE,lnA,lnB,lnC,lnD,71);
		R4(lnD,lnE,lnA,lnB,lnC,72); R4(lnC,lnD,lnE,lnA,lnB,73); R4(lnB,lnC,lnD,lnE,lnA,74); R4(lnA,lnB,lnC,lnD,lnE,75);
		R4(lnE,lnA,lnB,lnC,lnD,76); R4(lnD,lnE,lnA,lnB,lnC,77); R4(lnC,lnD,lnE,lnA,lnB,78); R4(lnB,lnC,lnD,lnE,lnA,79);

		// Add the working vars back into context.state[]
		state[0] += lnA;
		state[1] += lnB;
		state[2] += lnC;
		state[3] += lnD;
		state[4] += lnE;

		// Wipe variables
		lnA = 0;
		lnB = 0;
		lnC = 0;
		lnD = 0;
		lnE = 0;
	}




#ifdef _TEST_ME
	static s8* test_data[] = {		"abc",
									"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
									"A million repetitions of 'a'"
								};

	static s8* test_results[] = {		"A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D",
										"84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1",
										"34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F"
									};


	void digest_to_hex(const u8 digest[_SHA1_NUMBER_SIZE], s8* output)
	{
		int i,j;
		char *c = output;

		for (i = 0; i < _SHA1_NUMBER_SIZE/4; i++) {
			for (j = 0; j < 4; j++) {
				sprintf_s(c, 3, "%02X", digest[i*4+j]);
				c += 2;
			}
			sprintf_s(c, 2, " ");
			c += 1;
		}
		*(c - 1) = '\0';
	}


// Can be used to test internally rather than through main:
//	int sha1_test(void)
	int main(int argc, char** argv)
	{
		int				lnI, lnIteratorA;
		bool			llError;
		SSha1Context	context;
		u8				sha20Bytes[20];
		u8				sha20Bytes2[20];
		char			sha20ConvertedToHex[80];

		fprintf(stdout, "SHA1.CPP -- Verifying SHA-1 implementation...\n");

		for (lnI = 0; lnI < 2; lnI++)
		{
			printf("\nTesting: %s\n", test_data[lnI]);

			sha1_initialize(&context);
			sha1_continueOnThisData(&context, (u8*)test_data[lnI], strlen(test_data[lnI]));
			sha1_finalize(&context, sha20Bytes);

			memset(sha20ConvertedToHex, 0, sizeof(sha20ConvertedToHex));
			digest_to_hex(sha20Bytes, sha20ConvertedToHex);
			printf("    Should be: %s\n", test_results[lnI]);
			printf("     Computed: %s",   sha20ConvertedToHex);

			if (strcmp(sha20ConvertedToHex, test_results[lnI]))
			{
				fprintf(stdout, "\nFAIL\n");
				fprintf(stderr,"* hash of \"%s\" incorrect:\n", test_data[lnI]);
				fprintf(stderr,"\t%s returned\n", sha20ConvertedToHex);
				fprintf(stderr,"\t%s is correct\n", test_results[lnI]);
				return (1);

			} else {
				printf("...ok\n");
			}
		}

		// The test description is still in test_data
		printf("\nTesting: %s\n", test_data[lnI]);

		/* million 'a' vector we feed separately */
		sha1_initialize(&context);
		for (lnIteratorA = 0; lnIteratorA < 1000000; lnIteratorA++)
			sha1_continueOnThisData(&context, (u8*)"a", 1);

		sha1_finalize(&context, sha20Bytes);

		memset(sha20ConvertedToHex, 0, sizeof(sha20ConvertedToHex));
		digest_to_hex(sha20Bytes, sha20ConvertedToHex);
		printf("    Should be: %s\n", test_results[lnI]);
		printf("     Computed: %s",   sha20ConvertedToHex);

		if (strcmp(sha20ConvertedToHex, test_results[2]))
		{
			fprintf(stdout, "\nFAIL\n");
			fprintf(stderr,"* hash of \"%s\" incorrect:\n", test_data[2]);
			fprintf(stderr,"\t%s returned\n", sha20ConvertedToHex);
			fprintf(stderr,"\t%s is correct\n", test_results[2]);
			return (1);

		} else {
			printf("...ok\n");
		}


		// Compute a similar tests on the data sets using the simple algorithms
		printf("\nUsing simple function: %s\n", test_data[0]);

		// Calling separately
		sha1_computeSha1((const u8*)test_data[0], strlen(test_data[0]), sha20Bytes);
		sha1_convertSha20ToHex(sha20Bytes, sha20ConvertedToHex, true);
		printf("    %s\n", sha20ConvertedToHex);

		// Calling singularly
		sha1_computeSha1AsHex((const u8*)test_data[0], strlen(test_data[0]), sha20Bytes, sha20ConvertedToHex, true);
		printf("    %s\n", sha20ConvertedToHex);


		// Verify that the hexadecimal values can be converted back to a new sha20Bytes value
		printf("\nTesting hexadecimal text conversion to SHA-1 160-bit format...");
		sha1_convertHexToSha20(sha20ConvertedToHex, sha20Bytes2, &llError);
		if (!llError && memcmp(sha20Bytes, sha20Bytes2, _SHA1_NUMBER_SIZE) == 0)
			printf("ok\n");
		else
			printf("failed\n");


		// success
		fprintf(stdout, "\nFinished ok\n");
_asm int 3;
		return(0);
	}
#endif
