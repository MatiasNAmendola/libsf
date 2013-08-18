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
// Linked List required constants and variables
//
//////
			u32		gnLlInitializerValue						= 1;								// Begin at our initializer value
	const	u32		cgnLlBufferSize								= 256 * sizeof(u32);				// Enough room for 256 32-bit quantities
	const	u64		cgnTestLl1NodeSha1As64Bit					= 0x8e187bd07652c715;				// 8e18 7bd0 7652 c715
	const	u32		cgnTestLl1NodeSha1As32Bit					= 0x05b45f4b;						// 05b4 5f4b

	const	u64		cgnTestLl2NodeSha1As64Bit					= 0x5c6a71d22d539eeb;				// 5c6a 71d2 2d53 9eeb
	const	u32		cgnTestLl2NodeSha1As32Bit					= 0x11cde623;						// 11cd e623

	const	u64		cgnTestLl3NodeSha1As64Bit					= 0xfd5bf04c7f179e55;				// fd5b f04c 7f17 9e55
	const	u32		cgnTestLl3NodeSha1As32Bit					= 0xc9e2a6a8;						// c9e2 a6a8

	const	u64		cgnTestLl4NodeSha1As64Bit					= 0x159d34958a4c2a0c;				// 159d 3495 8a4c 2a0c
	const	u32		cgnTestLl4NodeSha1As32Bit					= 0xd6cfd305;						// d6cf d305

	const	u64		cgnTestLl5NodeSha1As64Bit					= 0x216f7a53c688ff40;				// 216f 7a53 c688 ff40
	const	u32		cgnTestLl5NodeSha1As32Bit					= 0x1029d328;						// 1029 d328

	const	u64		cgnTestLl6NodeSha1As64Bit					= 0xe9e107911d037d1a;				// e9e1 0791 1d03 7d1a
	const	u32		cgnTestLl6NodeSha1As32Bit					= 0xd88324a3;						// d883 24a3

	const	u64		cgnTestLl7NodeSha1As64Bit					= 0x57571b0fc22491a6;				// 5757 1b0f c224 91a6
	const	u32		cgnTestLl7NodeSha1As32Bit					= 0x2a0e94c3;						// 2a0e 94c3

	const	u64		cgnTestLl8NodeSha1As64Bit					= 0x71e72704128c31eb;				// 71e7 2704 128c 31eb
	const	u32		cgnTestLl8NodeSha1As32Bit					= 0x10eca433;						// 10ec a433

	const	u64		cgnTestLl9NodeSha1As64Bit					= 0x5830322388a9b487;				// 5830 3223 88a9 b487
	const	u32		cgnTestLl9NodeSha1As32Bit					= 0x363059a9;						// 3630 59a9

	const	u64		cgnTestLl10NodeSha1As64Bit					= 0xcd3e8d48ae26895a;				// cd3e 8d48 ae26 895a
	const	u32		cgnTestLl10NodeSha1As32Bit					= 0x8ac9817b;						// 8ac9 817b

	const	u64		cgnTestLl11NodeSha1As64Bit					= 0xdd5f61c2cbd5d283;				// dd5f 61c2 cbd5 d283
	const	u32		cgnTestLl11NodeSha1As32Bit					= 0x4e96bd41;						// 4e96 bd41


//////////
//
// 4-way Linked List required constants and variables
//
//////
			u32		gnLl4InitializerValue						= 1;								// Begin at our initializer value
	const	u32		cgnLl4BufferSize							= 256 * sizeof(u32);				// Enough room for 256 32-bit quantities

	// Test 1
	const	u64		cgnTest1Ll41NodeSha1As64Bit					= 0xa3d2dbacfbf105b7;				// a3d2 dbac fbf1 05b7
	const	u32		cgnTest1Ll41NodeSha1As32Bit					= 0xf6019c40;						// f601 9c40

	const	u64		cgnTest1Ll42NodeSha1As64Bit					= 0x7f446e8c2b9e6011;				// 7f44 6e8c 2b9e 6011
	const	u32		cgnTest1Ll42NodeSha1As32Bit					= 0x0890465e;						// 0890 465e

	const	u64		cgnTest1Ll43NodeSha1As64Bit					= 0xc0eb50ede7565199;				// c0eb 50ed e756 5199
	const	u32		cgnTest1Ll43NodeSha1As32Bit					= 0x90f1ac8c;						// 90f1 ac8c

	const	u64		cgnTest1Ll44NodeSha1As64Bit					= 0x2c832db8d8702880;				// 2c83 2db8 d870 2880
	const	u32		cgnTest1Ll44NodeSha1As32Bit					= 0x16c611d1;						// 16c6 11d1

	const	u64		cgnTest1Ll45NodeSha1As64Bit					= 0xd7d495da9574cb51;				// d7d4 95da 9574 cb51
	const	u32		cgnTest1Ll45NodeSha1As32Bit					= 0xad0836ce;						// ad08 36ce

	const	u64		cgnTest1Ll46NodeSha1As64Bit					= 0x11f15e25fc6455d4;				// 11f1 5e25 fc64 55d4
	const	u32		cgnTest1Ll46NodeSha1As32Bit					= 0x06e91813;						// 06e9 1813

	const	u64		cgnTest1Ll47NodeSha1As64Bit					= 0x121cbfe4229907be;				// 121c bfe4 2299 07be
	const	u32		cgnTest1Ll47NodeSha1As32Bit					= 0x680ab4d3;						// 680a b4d3

	const	u64		cgnTest1Ll48NodeSha1As64Bit					= 0xa8e69aa91b0f1fe5;				// a8e6 9aa9 1b0f 1fe5
	const	u32		cgnTest1Ll48NodeSha1As32Bit					= 0xc72895a9;						// c728 95a9

	const	u64		cgnTest1Ll49NodeSha1As64Bit					= 0xcaa6bb3c5a223cee;				// caa6 bb3c 5a22 3cee
	const	u32		cgnTest1Ll49NodeSha1As32Bit					= 0xf2013210;						// f201 3210

	// Test 2
	const	u64		cgnTest2Ll41NodeSha1As64Bit					= 0x3bb2033bbf61e292;				// 3bb2 033b bf61 e292
	const	u32		cgnTest2Ll41NodeSha1As32Bit					= 0x66312552;						// 6631 2552


//////////
//
// BXML test required constants and variables
//
//////
	#include "include\vvmt_bxml_test1.h"															// cgc_Test_Bxml_1_1

	// Constant values derived from runtime observation, used for testing
	const	u64		cgnTestBxmlDotHNodeSha1As64Bit				= 0xfdb64befd4f70df4;				// fdb6 4bef d4f7 0df4
	const	u32		cgnTestBxmlDotHNodeSha1As32Bit				= 0xf5d6783e;						// f5d6 783e


//////////
// Constant used for test 4
//////
	const	u64		cgnTestBxml41_Sha1As64Bit					= 0x5da0c261bbc5cf53;				// 5da0 c261 bbc5 cf53
	const	u32		cgnTestBxml41_Sha1As32Bit					= 0xa256abc9;						// a256 abc9

	const	u64		cgnTestBxml42_Sha1As64Bit					= 0xe1fda2104ebb9a52;				// e1fd a210 4ebb 9a52
	const	u32		cgnTestBxml42_Sha1As32Bit					= 0x8eaa6fe3;						// 8eaa 6fe3

	const	u64		cgnTestBxml43_Sha1As64Bit					= 0xae7bbe0d7d83693b;				// ae7b be0d 7d83 693b
	const	u32		cgnTestBxml43_Sha1As32Bit					= 0x8cde4d17;						// 8cde 4d17

	const	s8		cgcTestBxml4PrependNodeName[]				= "prependNode4";
	const	s8		cgcTestBxml4AppendNodeName[]				= "appendNode4";
	const	s8		cgcTestBxml4FindChildNode[]					= "*child*";
	const	s8		cgcTestBxml4FindAttributes[]				= "*o*";
	const	s8		cgcTestBxml4FindData[]						= "*l*";


//////////
// Constants used for test 5
//////
//	const	s8		cgcTestBxml5FindChildNode[]					= "*child*";						// Unused, we use the cgcTestBxml4FindChildNode, since they are the same
	const	s8		cgcTestBxml5PrependNodeName[]				= "prependNode5";
	const	s8		cgcTestBxml5AppendNodeName[]				= "appendNode5";

	const	u64		cgnTestBxml51_Sha1As64Bit					= 0x6cab7490f49b4b7e;				// 6cab 7490 f49b 4b7e
	const	u32		cgnTestBxml51_Sha1As32Bit					= 0xa0517f25;						// a051 7f25


//////////
// Constants used for test 6
//////
	const	s8		cgcTestBxml6FindChildNode[]					= "child2";
	const	s8		cgcTestBxml6PrependNodeName[]				= "prependNode6";
	const	s8		cgcTestBxml6AppendNodeName[]				= "appendNode6";

	const	u64		cgnTestBxml61_Sha1As64Bit					= 0xa1ced1448c925591;				// a1ce d144 8c92 5591
	const	u32		cgnTestBxml61_Sha1As32Bit					= 0x41e1f514;						// 41e1 f514


//////////
// Constants used for test 7
//////
	const	s8		cgcTestBxml7FindChildAttribute[]			= "food";
	const	s8		cgcTestBxml7PrependAttributeName[]			= "prependAttribute7";
	const	s8		cgcTestBxml7AppendAttributeName[]			= "appendAttribute7";

	const	u64		cgnTestBxml71_Sha1As64Bit					= 0xafe6c2b1c39a01f9;				// a1ce d144 8c92 5591
	const	u32		cgnTestBxml71_Sha1As32Bit					= 0xceef8911;						// 41e1 f514


//////////
// Constants used for test 8
//////
	const	s8		cgcTestBxml8FindChildNode1[]				= "grandchild1";
	const	s8		cgcTestBxml8FindChildNode2[]				= "grandchild2";

	const	u64		cgnTestBxml81_Sha1As64Bit					= 0x9a1fee2ee79513e2;				// 9a1f ee2e e795 13e2
	const	u32		cgnTestBxml81_Sha1As32Bit					= 0x3bd8ebd3;						// 3bd8 ebd3

	const	u64		cgnTestBxml82_Sha1As64Bit					= 0xafe6c2b1c39a01f9;				// a1ce d144 8c92 5591
	const	u32		cgnTestBxml82_Sha1As32Bit					= 0xceef8911;						// 41e1 f514

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
