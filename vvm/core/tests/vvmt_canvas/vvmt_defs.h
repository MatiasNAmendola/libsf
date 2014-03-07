//////////
//
// /libsf/vvm/core/vvmtests/vvmt_canvas/vvmt_defs.h
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
//     Mar.02.2013 - Initial creation
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
// Forward declarations
//////
	//////////
	// vvmmt.cpp
	//////
		u64 CALLTYPE			vvmt_firstCallback										(u64 tnDebuggerInterfaceAddress);
		void CALLTYPE			vvmt_bootstrapInitialization							(u64 tnDebuggerInterfaceAddress);
		void CALLTYPE			vvmt_initialization										(u64 tnDebuggerInterfaceAddress);
		const s8* CALLTYPE		vvmt_getVersion											(void);

		bool CALLTYPE			vvmt_executeTests										(u64 lnHandleLog);

		void CALLTYPE			vvmt_enableBreakpoints									(void);
		void CALLTYPE			vvmt_disableBreakpoints									(void);

	
	//////////
	// Canvas
	// vvmt_canvas_test.cpp
	//////
		bool					ivvmt_testCanvas										(u64 lnHandleLog);
		bool					iivvmt_testCanvas_1										(u64 lnHandleLog);
		bool					iivvmt_testCanvas_2										(u64 lnHandleLog);
