//////////
//
// /libsf/vvm/vvmoss/vo_const.h
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.25.2014
//////
// Change log:
//     Feb.25.2014 - Development on 0.70 begins
//     Nov.07.2012 - 0.60 development begins
//     Sep.29.2012 - PBL v1.0 license included directly in source files.
//     Sep.20.2012 - Initial creation
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
//
// Constant strings
//
//////
	const s8		cgcOssVersion[]							= "OSS.DLL Version 0.70";			// The format of this version string will remain consistent throughout all future releases
	const wchar_t	cgw1msTimer[]							= L"oss_1msTimer";




//////////
//
// Used for cask definition processing
//
//////
	const s8		cgcCaskRoundOpenParams[]						= "(||";
	const s8		cgcCaskRoundCloseParams[]						= "||)";
	const s8		cgcCaskSquareOpenParams[]						= "[||";
	const s8		cgcCaskSquareCloseParams[]						= "||]";
	const s8		cgcCaskTriangleOpenParams[]						= "<||";
	const s8		cgcCaskTriangleCloseParams[]					= "||>";
	const s8		cgcCaskTildeOpenParams[]						= "~||";
	const s8		cgcCaskTildeCloseParams[]						= "||~";
	const s8		cgcCaskRoundOpen[]								= "(|";
	const s8		cgcCaskRoundClose[]								= "|)";
	const s8		cgcCaskSquareOpen[]								= "[|";
	const s8		cgcCaskSquareClose[]							= "|]";
	const s8		cgcCaskTriangleOpen[]							= "<|";
	const s8		cgcCaskTriangleClose[]							= "|>";
	const s8		cgcCaskTildeOpen[]								= "~|";
	const s8		cgcCaskTildeClose[]								= "|~";

	const u32		_MC_ICODE_CASK_ROUND_OPEN_PARAMS				= 1000001;
	const u32		_MC_ICODE_CASK_ROUND_CLOSE_PARAMS				= 1000002;
	const u32		_MC_ICODE_CASK_SQUARE_OPEN_PARAMS				= 1000003;
	const u32		_MC_ICODE_CASK_SQUARE_CLOSE_PARAMS				= 1000004;
	const u32		_MC_ICODE_CASK_TRIANGLE_OPEN_PARAMS				= 1000005;
	const u32		_MC_ICODE_CASK_TRIANGLE_CLOSE_PARAMS			= 1000006;
	const u32		_MC_ICODE_CASK_TILDE_OPEN_PARAMS				= 1000007;
	const u32		_MC_ICODE_CASK_TILDE_CLOSE_PARAMS				= 1000008;
	const u32		_MC_ICODE_CASK_ROUND_OPEN						= 1000009;
	const u32		_MC_ICODE_CASK_ROUND_CLOSE						= 1000010;
	const u32		_MC_ICODE_CASK_SQUARE_OPEN						= 1000011;
	const u32		_MC_ICODE_CASK_SQUARE_CLOSE						= 1000012;
	const u32		_MC_ICODE_CASK_TRIANGLE_OPEN					= 1000013;
	const u32		_MC_ICODE_CASK_TRIANGLE_CLOSE					= 1000014;
	const u32		_MC_ICODE_CASK_TILDE_OPEN						= 1000015;
	const u32		_MC_ICODE_CASK_TILDE_CLOSE						= 1000016;
