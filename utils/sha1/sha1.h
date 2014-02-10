//////////
//
// /libsf/utils/sha1/sha1.h
//
//////
// Version 1.00
// Public Domain - See sha1.cpp.
//////
// Last update:
//     February 17, 2013
//////
// Change log:
//     February 17, 2013 - Initial creation, compiles with VVMOSS in VS2008 Professional.
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




//////////
// Constants (defined so they're visible in the debugger)
//////
	const u32	_SHA1_NUMBER_SIZE	= 20;
	const u32	_SHA1_CONTEXT_SIZE	= 92;


//////////
// Forward declarations used outside of the SHA-1 sha1.cpp source code
//////
	void			sha1_computeSha1					(const u8* tcData, u32 tnLength, u8 sha20Bytes[_SHA1_NUMBER_SIZE]);
	void			sha1_convertSha20ToHex				(const u8 sha20Bytes[_SHA1_NUMBER_SIZE], s8* tcHexOutput, bool tlSpacesBetween);
	void			sha1_computeSha1AsHex				(const u8* tcData, u32 tnLength, u8 sha20Bytes[_SHA1_NUMBER_SIZE], s8* tcHexOutput, bool tlSpacesBetween);
	void			sha1_convertHexToSha20				(const s8* tcHexInput, u8 sha20Bytes[_SHA1_NUMBER_SIZE], bool* tlError);
	void			sha1_92initialize					(u8 context[92]);
	void			sha1_92continueOnThisData			(u8 context[92], const u8* tcData, u32 tnLength);
	void			sha1_92finalize						(u8 context[92], u8 sha20Bytes[_SHA1_NUMBER_SIZE], bool tlWipeData);
	u64				sha1_convertSha20To64Bit			(u8 sha20Bytes[_SHA1_NUMBER_SIZE]);
	u32				sha1_convertSha20To32Bit			(u8 sha20Bytes[_SHA1_NUMBER_SIZE]);
	bool			sha1_compare						(u8 sha20Bytes1[_SHA1_NUMBER_SIZE], u8 sha20Bytes2[_SHA1_NUMBER_SIZE]);
