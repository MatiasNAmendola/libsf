//////////
//
// /libsf/vvm/core/vdebug/vdeb_structs.h
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.25.2014
//////
// Change log:
//     Feb.25.2014 - 0.70 development begins
//     Nov.07.2012 - 0.60 development begins
//     Sep.29.2012 - PBL v1.0 license included directly in source files.
//     Sep.26.2012 - Initial creation
//////
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




//////////
// Structures known to the debugger
//////
	struct SLocal1
	{
		s8		line1[26];
		s8		line2[26];
		s8		line3[26];
		s8		line4[26];
		s8		line5[26];
	};

	struct SLocal2
	{
		s8		line1[54];
		s8		line2[54];
		s8		line3[54];
		s8		line4[54];
		s8		line5[54];
	};

	struct SLocal3
	{
		s8		line1[82];
		s8		line2[82];
		s8		line3[82];
		s8		line4[82];
		s8		line5[82];
	};

	struct SRegs1
	{
		s8		line1[26];
		s8		line2[26];
		s8		line3[26];
		s8		line4[26];
		s8		line5[26];
		s8		line6[26];
		s8		line7[26];
		s8		line8[26];
		s8		line9[26];
		s8		line10[26];
		s8		line11[26];
		s8		line12[26];
		s8		line13[26];
		s8		line14[26];
		s8		line15[26];
		s8		line16[26];
	};

	struct SInt1
	{
		s8		line1[26];
		s8		line2[26];
		s8		line3[26];
		s8		line4[26];
		s8		line5[26];
		s8		line6[26];
		s8		line7[26];
		s8		line8[26];
		s8		line9[26];
		s8		line10[26];
		s8		line11[26];
		s8		line12[26];
		s8		line13[26];
		s8		line14[26];
		s8		line15[26];
		s8		line16[26];
	};

	struct SFloat1
	{
		s8		line1[26];
		s8		line2[26];
		s8		line3[26];
		s8		line4[26];
		s8		line5[26];
		s8		line6[26];
		s8		line7[26];
		s8		line8[26];
		s8		line9[26];
		s8		line10[26];
		s8		line11[26];
		s8		line12[26];
		s8		line13[26];
		s8		line14[26];
		s8		line15[26];
		s8		line16[26];
	};

	struct SCFSCA1
	{
		s8		line1[84];
		s8		line2[84];
		s8		line3[84];
		s8		line4[84];
		s8		line5[84];
		s8		line6[84];
		s8		line7[84];
		s8		line8[84];
		s8		line9[84];
		s8		line10[84];
		s8		line11[84];
		s8		line12[84];
		s8		line13[84];
		s8		line14[84];
		s8		line15[84];
		s8		line16[84];
		s8		line17[84];
		s8		line18[84];
		s8		line19[84];
	};

	struct SReady3
	{
		s8		line1[84];
		s8		line2[84];
		s8		line3[84];
		s8		line4[84];
		s8		line5[84];
		s8		line6[84];
		s8		line7[84];
		s8		line8[84];
		s8		line9[84];
		s8		line10[84];
	};

	struct SMemory1
	{
		s8		line1[26];
		s8		line2[26];
		s8		line3[26];
	};

	struct SMemory2
	{
		s8		line1[54];
		s8		line2[54];
		s8		line3[54];
	};

	struct SMemory3
	{
		s8		line1[82];
		s8		line2[82];
		s8		line3[82];
	};

	struct SWatch3
	{
		s8		line1[82];
		s8		line2[82];
		s8		line3[82];
		s8		line4[82];
	};

	struct SAutos3
	{
		s8		line1[82];
		s8		line2[82];
		s8		line3[82];
		s8		line4[82];
		s8		line5[82];
	};

	struct SStack1
	{
		s8		line1[26];
		s8		line2[26];
		s8		line3[26];
		s8		line4[26];
		s8		line5[26];
		s8		line6[26];
		s8		line7[26];
		s8		line8[26];
		s8		line9[26];
		s8		line10[26];
		s8		line11[26];
		s8		line12[26];
		s8		line13[26];
		s8		line14[26];
		s8		line15[26];
		s8		line16[26];
	};

	struct SHover2
	{
		s8		line1[55];
		s8		line2[55];
		s8		line3[55];
	};

	struct STimer2
	{
		s8		line1[55];
		s8		line2[55];
		s8		line3[55];
	};

	struct SPrograms2
	{
		s8		line1[55];
		s8		line2[55];
	};

	struct SThreads2
	{
		s8		line1[55];
		s8		line2[55];
		s8		line3[55];
		s8		line4[55];
		s8		line5[55];
	};
