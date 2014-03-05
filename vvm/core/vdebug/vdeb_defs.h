//////////
//
// /libsf/VDebug/VDebug/vdeb_defs.h
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
//     Oct.21.2012 - PBL v1.0 license included directly in source files.
//     Oct.21.2012 - Initial creation
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
// Internal debugger functions
//////
	bool				iLoadResource									(s8* tcLanguage);
	DWORD CALLTYPE		iDebuggerMain									(LPVOID lpParameter);


	// vdeb_sup.cpp
	SBxml*				ivdeb_debuggerScreensCreate						(SBxml* bxml);
	void				ivdeb_debuggerScreensDelete						(SBxml* bxml);
	void				ivdeb_updateLocal1								(SThread* th);
	void				ivdeb_updateLocal2								(SThread* th);
	void				ivdeb_updateLocal3								(SThread* th);
	void				ivdeb_updateRegs1								(SThread* th);
	void				ivdeb_updateInt1								(SThread* th);
	void				ivdeb_updateFloat1								(SThread* th);
	void				ivdeb_updateCFSCA1								(SThread* th);
	void				ivdeb_updateReady3								(SThread* th);
	void				ivdeb_updateMemory1								(SThread* th);
	void				ivdeb_updateMemory2								(SThread* th);
	void				ivdeb_updateMemory3								(SThread* th);
	void				ivdeb_updateWatch3								(SThread* th);
	void				ivdeb_updateAutos3								(SThread* th);
	void				ivdeb_updateStack1								(SThread* th);
	void				ivdeb_updateHover2								(SThread* th);
	void				ivdeb_updateTimer2								(SThread* th);
	void				ivdeb_updatePrograms2							(SThread* th);
	void				ivdeb_updateThreads2							(SThread* th);

	s8*					ivdeb_getU64WithSpaceAndDots					(u64 tnValue, s8* buffer);
