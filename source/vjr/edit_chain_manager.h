//////////
//
// /libsf/source/vjr/edit_chain_manager.h
//
//////
// Version 0.30
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jul.06.2014
//////
// Change log:
//     Jul.06.2014 - Initial creation
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
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




//////////
// Constants
//////
	const u32				_ECM_MINIMUM_LINE_ALLOCATION_LENGTH		= 96;		// Allocate data in 96 byte blocks


//////////
// Forward declarations
//////
	SEditChainManager*		iEditChainManager_allocate				(void);
	bool					iEditChainManager_duplicate				(SEditChainManager** root, SEditChainManager* chain, bool tlIncludeUndoHistory);
	void					iEditChainManager_delete				(SEditChainManager** root, bool tlDeleteSelf);
	void					iEditChainManager_deleteChain			(SEditChainManager** root, bool tlDeleteSelf);
	SEditChain*				iEditChainManager_appendLine			(SEditChainManager* ecm, s8* tcText, s32 tnTextLength);
	SEditChain*				iEditChainManager_insertLine			(SEditChainManager* ecm, s8* tcText, s32 tnTextLength, SEditChain* line, bool tlInsertAfter);
	void					iEditChainManager_deleteLine			(SEditChainManager* ecm);
	SFont*					iEditChainManager_getRectAndFont		(SEditChainManager* ecm, SObject* obj, RECT* rc);
	void					iEditChainManager_getColors				(SEditChainManager* ecm, SObject* obj, SBgra& backColor, SBgra& foreColor);
	void					iEditChainManager_render				(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_verifyCursorIsVisible	(SEditChainManager* ecm, RECT* rc, SFont* font);


	// Editor movements
	bool					iEditChainManager_keystroke				(SEditChainManager* ecm, SObject* obj, u8 asciiChar);
	bool					iEditChainManager_navigate				(SEditChainManager* ecm, SObject* obj, s32 deltaY, s32 deltaX);
	bool					iEditChainManager_navigatePages			(SEditChainManager* ecm, SObject* obj, s32 deltaY);
	bool					iEditChainManager_clearLine				(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_clearToEndOfLine		(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_clearToBeginningOfLine(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_toggleInsert			(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_tabIn					(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_tabOut				(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_returnKey				(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_selectAll				(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_cut					(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_copy					(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_paste					(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_navigateWordLeft		(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_navigateWordRight		(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_navigateTop			(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_navigateEnd			(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_selectLineUp			(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_selectLineDown		(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_selectLeft			(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_selectRight			(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_selectToEndOfLine		(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_selectToBeginOfLine	(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_selectColumnToggle	(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_selectLineToggle		(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_selectWordLeft		(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_selectWordRight		(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_deleteLeft			(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_deleteRight			(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_deleteWordLeft		(SEditChainManager* ecm, SObject* obj);
	bool					iEditChainManager_deleteWordRight		(SEditChainManager* ecm, SObject* obj);
