//////////
//
// /libsf/vvm/core/vvmtests/vvmt_core/vvmt_glob.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     Mar.02.2013
//////
// Change log:
//     Mar.02.2013	- Initial creation
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




//////////
//
// SHA-1 test required constants and variables
// Note:  These cannot be localized.  They must be literal ASCII text strings.
//
//////
	const	s8		cgc_Test_Sha1_1_1[]		= "abc";
	const	s8		cgc_Test_Sha1_1_2[]		= "A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D";		// Should be
			s8		cgc_Test_Sha1_1_3[]		= "........ ........ ........ ........ ........";		// Actual result

	const	s8		cgc_Test_Sha1_2_1[]		= "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
	const	s8		cgc_Test_Sha1_2_2[]		= "84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1";		// Should be
			s8		cgc_Test_Sha1_2_3[]		= "........ ........ ........ ........ ........";		// Actual result

	const	s8		cgc_Test_Sha1_3_1[]		= "a";
	const	s8		cgc_Test_Sha1_3_2[]		= "34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F";		// Should be
			s8		cgc_Test_Sha1_3_3[]		= "........ ........ ........ ........ ........";		// Actual result




//////////
//
// BXML test required constants and variables
//
//////
	#include "include\vvmt_bxml_test1.h"															// cgc_Test_Bxml_1_1

	// Constant values derived from runtime observation, used for testing
	const	u64		cgnTestBxmlDotHNodeSha1As64Bit				= 0xfdb64befd4f70df4;						// fdb6 4bef d4f7 0df4
	const	u32		cgnTestBxmlDotHNodeSha1As32Bit				= 0xf5d6783e;								// f5d6 783e


//////////
// Constant used for test 4
//////
	const	u64		cgnTestBxml41_Sha1As64Bit					= 0x5da0c261bbc5cf53;						// 5da0 c261 bbc5 cf53
	const	u32		cgnTestBxml41_Sha1As32Bit					= 0xa256abc9;								// a256 abc9

	const	u64		cgnTestBxml42_Sha1As64Bit					= 0xe1fda2104ebb9a52;						// e1fd a210 4ebb 9a52
	const	u32		cgnTestBxml42_Sha1As32Bit					= 0x8eaa6fe3;								// 8eaa 6fe3

	const	u64		cgnTestBxml43_Sha1As64Bit					= 0xae7bbe0d7d83693b;						// ae7b be0d 7d83 693b
	const	u32		cgnTestBxml43_Sha1As32Bit					= 0x8cde4d17;								// 8cde 4d17

	const	s8		cgcTestBxml4PrependNodeName[]				= "prependNode4";
	const	s8		cgcTestBxml4AppendNodeName[]				= "appendNode4";
	const	s8		cgcTestBxml4FindChildNode[]					= "*child*";
	const	s8		cgcTestBxml4FindAttributes[]				= "*o*";
	const	s8		cgcTestBxml4FindData[]						= "*l*";


//////////
// Constants used for test 5
//////
//	const	s8		cgcTestBxml5FindChildNode[]					= "*child*";								// Unused, we use the cgcTestBxml4FindChildNode, since they are the same
	const	s8		cgcTestBxml5PrependNodeName[]				= "prependNode5";
	const	s8		cgcTestBxml5AppendNodeName[]				= "appendNode5";

	const	u64		cgnTestBxml51_Sha1As64Bit					= 0x6cab7490f49b4b7e;						// 6cab 7490 f49b 4b7e
	const	u32		cgnTestBxml51_Sha1As32Bit					= 0xa0517f25;								// a051 7f25


//////////
// Constants used for test 6
//////
	const	s8		cgcTestBxml6FindChildNode[]					= "child2";
	const	s8		cgcTestBxml6PrependNodeName[]				= "prependNode6";
	const	s8		cgcTestBxml6AppendNodeName[]				= "appendNode6";

	const	u64		cgnTestBxml61_Sha1As64Bit					= 0xa1ced1448c925591;						// a1ce d144 8c92 5591
	const	u32		cgnTestBxml61_Sha1As32Bit					= 0x41e1f514;								// 41e1 f514


//////////
// Constants used for test 7
//////
	const	s8		cgcTestBxml7FindChildAttribute[]			= "food";
	const	s8		cgcTestBxml7PrependAttributeName[]			= "prependAttribute7";
	const	s8		cgcTestBxml7AppendAttributeName[]			= "appendAttribute7";

	const	u64		cgnTestBxml71_Sha1As64Bit					= 0xafe6c2b1c39a01f9;						// a1ce d144 8c92 5591
	const	u32		cgnTestBxml71_Sha1As32Bit					= 0xceef8911;								// 41e1 f514


//////////
// Constants used for test 8
//////
	const	s8		cgcTestBxml8FindChildNode1[]				= "grandchild1";
	const	s8		cgcTestBxml8FindChildNode2[]				= "grandchild2";

	const	u64		cgnTestBxml81_Sha1As64Bit					= 0x9a1fee2ee79513e2;						// 9a1f ee2e e795 13e2
	const	u32		cgnTestBxml81_Sha1As32Bit					= 0x3bd8ebd3;								// 3bd8 ebd3

	const	u64		cgnTestBxml82_Sha1As64Bit					= 0xafe6c2b1c39a01f9;						// a1ce d144 8c92 5591
	const	u32		cgnTestBxml82_Sha1As32Bit					= 0xceef8911;								// 41e1 f514

/*
	const	s8		cgcTestBxmlFirstNodeName[]					= "node1First";
	const	s8		cgcTestBxmlSecondNodeName[]					= "node2";
	const	s8		cgcTestBxmlThirdNodeName[]					= "node3";
	const	s8		cgcTestBxmlFourthNodeName[]					= "node4";
	const	s8		cgcTestBxmlLastNodeName[]					= "node5Last";

	const	s8		cgcTestBxmlPrependAttributeName[]			= "prependAttribute5";
	const	s8		cgcTestBxmlAppendAttributeName[]			= "appendAttribute5";
	const	s8		cgcTestBxmlFirstAttributeName[]				= "attribute1First";
	const	s8		cgcTestBxmlSecondAttributeName[]			= "attribute2";
	const	s8		cgcTestBxmlThirdAttributeName[]				= "attribute3";
	const	s8		cgcTestBxmlFourthAttributeName[]			= "attribute4";
	const	s8		cgcTestBxmlLastAttributeName[]				= "attribute5Last";
*/
