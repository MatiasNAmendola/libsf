//////////
//
// /libsf/vvm/core/vvmtests/vvmt_core/vvmt_defs.h
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
	// SHA-1 tests
	// vvmt_sha1.cpp
	//////
		bool					ivvmt_testSha1											(u64 lnHandleLog);
		bool					iivvmt_testSha1_1										(u64 lnHandleLog);


	//////////
	// BXML
	// vvmt_Bxml.cpp
	//////
		bool					ivvmt_testBxml											(u64 lnHandleLog);
		void					iivvmt_testBxml_computeSha1CallbackBxml					(void* ptr, u64 tnExtra/*u8 context[_SHA1_CONTEXT_SIZE] pointer*/);
		void					iivvmt_testBxml_computeSha1CallbackBxmla				(void* ptr, u64 tnExtra/*u8 context[_SHA1_CONTEXT_SIZE] pointer*/);
		void					iivvmt_testBxml_computeSha1CallbackBxmlaData			(void* ptr, u64 tnExtra/*u8 context[_SHA1_CONTEXT_SIZE] pointer*/);
		bool					iivvmt_testBxml_1										(u64 lnHandleLog, SBxml** bxml);
		bool					iivvmt_testBxml_2										(u64 lnHandleLog, SBxml*  bxml);
		bool					iivvmt_testBxml_3										(u64 lnHandleLog, SBxml*  bxml);
		bool					iivvmt_testBxml_4										(u64 lnHandleLog, SBxml*  bxml);
		bool					iivvmt_testBxml_5										(u64 lnHandleLog, SBxml*  bxml);
		bool					iivvmt_testBxml_6										(u64 lnHandleLog, SBxml*  bxml);
		bool					iivvmt_testBxml_7										(u64 lnHandleLog, SBxml*  bxml);
		bool					iivvmt_testBxml_8										(u64 lnHandleLog, SBxml*  bxml);
		bool					iivvmt_testBxml_9										(u64 lnHandleLog, SBxml*  bxml);
		bool					iivvmt_testBxml_10										(u64 lnHandleLog, SBxml*  bxml);
		bool					iivvmt_testBxml_11										(u64 lnHandleLog, SBxml*  bxml);
		bool					iivvmt_testBxml_12										(u64 lnHandleLog, SBxml*  bxml);
		bool					iivvmt_testBxml_13										(u64 lnHandleLog, SBxml*  bxml);
