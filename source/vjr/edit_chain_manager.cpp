//////////
//
// /libsf/source/vjr/edit_chain_manager.cpp
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
//
// Called to create a new ECM (Edit Chain Manager)
//
//////
	SEditChainManager* iEditChainManager_allocate(void)
	{
		SEditChainManager* ecm;


		// Allocate a new structure
		ecm = (SEditChainManager*)malloc(sizeof(SEditChainManager));

		// Initialize
		if (ecm)
			memset(ecm, 0, sizeof(SEditChainManager));

		// Indicate our status
		return(ecm);
	}




//////////
//
// Duplicate the entire ECM
//
//////
	bool iEditChainManager_duplicate(SEditChainManager** root, SEditChainManager* ecmSource, bool tlIncludeUndoHistory)
	{
		SEditChainManager*	ecmNew;
		SEditChain*			ecSource;
		SEditChain*			ecNew;
		SEditChain*			ecLast;
		SEditChain**		ecPrev;
		SExtraInfo*			eiSource;
		SExtraInfo*			eiNew;
		SExtraInfo**		eiPrev;
		SBuilder*			xlatRoot;
		STranslate*			xlat;


		// Create the master record
// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
		ecmNew = (SEditChainManager*)malloc(sizeof(SEditChainManager));
		if (ecmNew)
		{
			//////////
			// Initialize
			//////
				memcpy(ecmNew, ecmSource, sizeof(SEditChainManager));


			//////////
			// Remove the connection to any undo history
			// Note:  The undo history will be copied and translated separately if need be
			//////
				ecmNew->undoHistory = NULL;
				iBuilder_createAndInitialize(&xlatRoot, -1);
				// Note:  We create the translation regardless so we can update the ecmNew-> members which relate to cursor line, highlighted, etc.


			//////////
			// Update caller
			//////
				*root = ecmNew;
				// Right now:
				//		ecmNew		-- our new SEC
				//		ecmSource	-- SEC to duplicate


			//////////
			// Indicate where we'll be updating
			//////
				ecPrev	= &ecmNew->ecFirst;
				ecLast	= NULL;


			//////////
			// Duplicate the chain
			//////
				ecSource = ecmSource->ecFirst;
				while (ecSource)
				{
					//////////
					// Create a new entry for this one
					//////
						ecNew = (SEditChain*)malloc(sizeof(SEditChain));
						if (ecNew)
						{
							// Create a translation for original pointers to new pointers
							if (tlIncludeUndoHistory)
							{
								// Create the translation for this ecSource <--> ecNew
								xlat = (STranslate*)iBuilder_allocateBytes(xlatRoot, sizeof(STranslate));
								if (xlat)
								{
									// Create the translation
									xlat->p1	= ecSource;									// The old pointer in the undoHistory will point to
									xlat->p2	= ecNew;									// the new pointer
								}
							}

						} else {
							// Should not happen.
							return(false);
						}


					//////////
					// Copy source information to new
					//////
						memcpy(ecNew, ecSource, sizeof(SEditChain));
						*ecPrev		= ecNew;												// Update the prior record to point here
						ecNew->prev	= ecLast;												// Point backward to the previous entry
						ecNew->next	= NULL;													// Currently points forward to nothing


					//////////
					// Duplicate its data
					//////
						ecNew->sourceCode = NULL;
						iDatum_duplicate(ecNew->sourceCode, ecSource->sourceCode);


					//////////
					// General purpose extra data
					//////
						if (ecSource->extra_info)
						{
							// Copy any extra_info that's relevant
							eiPrev		= &ecNew->extra_info;
							eiSource	= ecSource->extra_info;
							while (eiSource)
							{
								//////////
								// Duplicate this entry
								//////
									// Are we duplicating by a function call?  Or manually?
									if (*(u32*)&eiSource->extra_info_duplicate != 0)
									{
										// Function call
										eiNew = eiSource->extra_info_duplicate(ecmSource, ecSource, ecSource->extra_info);
										// Right now, eiNew has either been updated or not depending on the decision making process in extra_info_duplicate().

									} else {
										// Manual duplication
										eiNew = (SExtraInfo*)malloc(sizeof(SExtraInfo));
										if (eiNew)
										{
											// Copy everything
											memcpy(eiNew, eiSource, sizeof(SExtraInfo));

											// Clear, and then duplicate the info datum
											memset(&eiNew->info, 0, sizeof(eiNew->info));
											iDatum_duplicate(&eiNew->info, &eiSource->info);

										} else {
											// Should not happen
											return(false);
										}
									}


								//////////
								// Update the back-link if need be
								//////
									if (eiNew)
									{
										*eiPrev	= eiNew;
										eiPrev	= &eiNew->next;
									}


								//////////
								// Move to next extra_info
								//////
									eiSource = eiSource->next;
							}
						}


					//////////
					// Move to next entry to duplicate
					//////
						ecLast		= ecNew;
						ecPrev		= &ecNew->next;
						ecSource	= ecSource->next;
				}


			//////////
			// Translate each of the ecmSource pointers for ecmNew
			// Note:  The rest of them use uid lookups
			//////
				ecmNew->ecFirst				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecFirst);
				ecmNew->ecLast				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecLast);
				ecmNew->ecTop				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecTop);
				ecmNew->ecCursorLine		= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecCursorLine);
				ecmNew->ecCursorLineLast	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecCursorLineLast);
				ecmNew->ecSelectedLineStart	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecSelectedLineStart);
				ecmNew->ecSelectedLineEnd	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecSelectedLineEnd);


			//////////
			// Free the pointers
			//////
				iBuilder_freeAndRelease(&xlatRoot);


			//////////
			// Indicate success
			//////
				return(true);
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to free the ECM content, and optionally itself
//
//////
	void iEditChainManager_delete(SEditChainManager** root, bool tlDeleteSelf)
	{
		SEditChainManager* ecm;


		// Make sure our environment is sane
		if (root && *root)
		{
// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
			ecm = *root;
			//////////
			// Are we really the thing?  Or just an indirect reference to the thing?
			//////
				if (!ecm->indirect)
				{
					//////////
					// We are the thing
					// Free undo history
					//////
						if ((*root)->undoHistory)
							iEditChainManager_delete(&(*root)->undoHistory, true);


					//////////
					// Free content
					//////
						iEditChain_free(&(*root)->ecFirst, true);
				}


			//////////
			// Free self
			//////
				if (tlDeleteSelf)
				{
					free(*root);
					*root = NULL;
				}
		}
	}




//////////
//
// Called to delete the entire chain
//
//////
	void iEditChainManager_deleteChain(SEditChainManager** root, bool tlDeleteSelf)
	{
		if (root && *root)
		{
// TODO:  write this code :-)
_asm int 3;
		}
	}




//////////
//
// Called to append a line of text to the indicated ECM.
//
//////
	SEditChain* iEditChainManager_appendLine(SEditChainManager* ecm, s8* tcText, s32 tnTextLength)
	{
		u32				lnLineNum;
		SEditChain*		ec;


		// Make sure our environment is sane
		// Note:  We do not test for tcText and tnTextLength because we can add blank lines
		ec = NULL;
		if (ecm)
		{
			// Allocate our new structure
			if (ecm->ecLast)
			{
				// Append after the last line
				lnLineNum	= ecm->ecLast->line + 1;
				ec = (SEditChain*)iLl_appendNewNodeAtEnd((SLL**)ecm->ecLast, sizeof(SEditChain));

			} else {
				// This is the first line, add it and set the last line to the same
				ec = (SEditChain*)iLl_appendNewNodeAtEnd((SLL**)ecm->ecFirst, sizeof(SEditChain));
				if (ec)
					ecm->ecLast = ec;
			}

			// Was it added?
			if (ec)
			{
				// Initialize
				memset(ec, 0, sizeof(SEditChain));

				// Populate
				ec->sourceCode = iDatum_allocate(tcText, tnTextLength);
			}
		}

		// Indicate our status
		return(ec);
	}




//////////
//
// Obtains the rectangle we have to operate in.  If the object we relate back to is a
// form or subform, then we use the rcClient parameters created by the last render,
// otherwise we use the object's rc.
//
//////
	void iEditChainManager_getRect(SEditChainManager* ecm, SObject* obj, RECT* rc)
	{
		union {
			SSubObjForm*	form;
			SSubObjSubform*	subform;
		};


		// Make sure our environment is sane
		if (ecm && obj && obj->sub_obj)
		{
			// What is the object?
			switch (obj->objType)
			{
				case _OBJ_TYPE_FORM:
					// Use the rcClient
					form = (SSubObjForm*)obj->sub_obj;
					CopyRect(rc, &form->rcClient);
					break;

				case _OBJ_TYPE_SUBFORM:
					// Use the rcClient
					subform = (SSubObjSubform*)obj->sub_obj;
					CopyRect(rc, &subform->rcClient);
					break;

				default:
					// Use the rc
					CopyRect(rc, &obj->rc);
					break;
			}
			// When we get here, we have our rect

		} else {
			// It's insane, so we set our rc to something that will prevent processing
			SetRect(rc, 0, 0, 0, 0);
		}
	}




//////////
//
// Called to process the ASCII character into the input buffer.
//
//////
	bool iEditChainManager_keystroke(SEditChainManager* ecm, SObject* obj, u8 asciiChar)
	{
		bool	llRender;
		RECT	lrc;


		//////////
		// Indicate initially that no changes were made that require a re-render
		//////
			llRender = false;
			iEditChainManager_getRect(ecm, obj, &lrc);


		// Make sure our environment is sane
		if (ecm)
		{
			//////////
			// Are we on a line?
			//////
				if (!ecm->ecFirst)
					iEditChainManager_appendLine(ecm, NULL, 0);		// Append a blank line to receive this keystroke


			//////////
			// Is a line currently selected?
			//////
				if (!ecm->ecCursorLine)
					iEditChainManager_navigateTop(ecm, obj);


			//////////
			// Are we in insert mode?
			//////
				if (ecm->isInsert)
				{
					// We are inserting
					if (ecm->ecSelectedLineStart != NULL)
					{
						// There is a selection, which means we are replacing everything that's selected with this new keystroke
// TODO:  write this code

					} else {
						// We are just overwriting whatever's there
						return(iEditChain_characterInsert(ecm, asciiChar));
					}

				} else {
					// We are overwriting
					if (ecm->ecSelectedLineStart != NULL)
					{
						// There is a selection, which means we are replacing everything that's selected with this new keystroke
// TODO:  write this code

					} else {
						// We are just overwriting whatever's there
						return(iEditChain_characterOverwrite(ecm, asciiChar));
					}
				}
		}

		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate rows (deltaY) or columns (deltaX) or both.
//
//////
	bool iEditChainManager_navigate(SEditChainManager* ecm, SObject* obj, s32 deltaY, s32 deltaX)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate pages (deltaY) forward or backward)
//
//////
	bool iEditChainManager_navigatePages(SEditChainManager* ecm, SObject* obj, s32 deltaY)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// Is there room to navigate back?
		if (ecm->ecCursorLine != ecm->ecFirst)
		{
			// Determine how many lines we can move based upon the object's render size
		}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to clear the entire line.
//
//////
	bool iEditChainManager_clearLine(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to clear from where we are to the end of the line
//
//////
	bool iEditChainManager_clearToEndOfLine(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to clear from one character left of where we are to the beginning of the line
//
//////
	bool iEditChainManager_clearToBeginningOfLine(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to toggle insert mode
//
//////
	bool iEditChainManager_toggleInsert(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called when the users press TAB
//
//////
	bool iEditChainManager_tabIn(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called when the users presses SHIFT+TAB
//
//////
	bool iEditChainManager_tabOut(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select everything
//
//////
	bool iEditChainManager_selectAll(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to cut to the clipboard
//
//////
	bool iEditChainManager_cut(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to copy to the clipboard
//
//////
	bool iEditChainManager_copy(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to paste from the clipboard
//
//////
	bool iEditChainManager_paste(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate one word left
//
//////
	bool iEditChainManager_navigateWordLeft(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate one word right
//
//////
	bool iEditChainManager_navigateWordRight(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate to the top of the chain
//
//////
	bool iEditChainManager_navigateTop(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate to the end of the chain
//
//////
	bool iEditChainManager_navigateEnd(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select from where we are up one line.
// Note:  If we are not already selecting, then we assume an anchor mode select,
//        which begins at an arbitrary column, and ends at an arbitrary column.
//
//////
	bool iEditChainManager_selectLineUp(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select from where we are down one line.
// Note:  If we are not already selecting, then we assume an anchor mode select,
//        which begins at an arbitrary column, and ends at an arbitrary column.
//
//////
	bool iEditChainManager_selectLineDown(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select left one character.
// Note:  If we are in line select mode, this command has no effect unless we are at
//        the end of the line, at which time we will navigate to the next line.
//
//////
	bool iEditChainManager_selectLeft(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select right one character.
//
//////
	bool iEditChainManager_selectRight(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select from where we are to the end of line
//
//////
	bool iEditChainManager_selectToEndOfLine(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to left one character of where we are to the beginning of line
//
//////
	bool iEditChainManager_selectToBeginOfLine(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to toggle selection by column mode
//
//////
	bool iEditChainManager_selectColumnToggle(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to toggle selection by line mode
//
//////
	bool iEditChainManager_selectLineToggle(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select one word left
// Note:  If we are in line select mode, this command has no effect unless we are at
//        the beginning of the line, at which time we will navigate to the previous line
//        and all of the previous line will be selected.
//
//////
	bool iEditChainManager_selectWordLeft(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select one word right
// Note:  If we are in line select mode, this command has no effect unless we are at
//        the end of the line, at which time we will navigate to the next line and all
//        of the next line will be selected.
//
//////
	bool iEditChainManager_selectWordRight(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			iEditChainManager_getRect(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}
