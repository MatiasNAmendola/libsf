//////////
//
// /libsf/vvm/vvmmc/mc_istructs.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 17, 2012
//////
// Change log:
//     November 17, 2012 - Initial creation
//////
// VVM Assembler Internal Structures (not visible to external apps)
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
//////
//
// Note:  For the naming conventions,  for example "_isSLine"
//			_i		- indicates internal
//			s		- is a system structure, not one the VVM knows about, but one only used here internally
//			SLine	- the line structure
//
//




//////////
//
// Structures designed to handle the VVMMC related portions of code
//
//////
	// Extra information tagged on parsed SOssLine structures
	struct _isSLineInfo
	{
		bool			completed;							// Is this line completed?
		SSourceFile*	file;								// The source file this line is associated with
	};

	struct _isPass0BlockScanData
	{
		SAssembly*		ta;
		SSourceFile*	tsf;
		bool			llOkayToAddPipeDataToBlock;
		SOssComp*		comp;
		SOssLine*		lineNext;
		SOssLine*		linePrev;
		SLabelInfo*		llab;
		SPipeInfo*		lpip;
		SDllFuncInfo*	ldfi;
	};
