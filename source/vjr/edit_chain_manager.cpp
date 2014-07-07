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
// 		SEditChainManager*	ecmNew;
// 		SEditChain*			ecSource;
// 		SEditChain*			ecNew;
// 		SEditChain*			ecLast;
// 		SEditChain**		ecPrev;
// 		SExtraInfo*			eiSource;
// 		SExtraInfo*			eiNew;
// 		SExtraInfo**		eiPrev;
// 		SBuilder*			xlatRoot;
// 		STranslate*			xlat;


		// Create the master record
// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
// 		ecmNew = (SEditChainManager*)malloc(sizeof(SEditChainManager));
// 		if (ecmNew)
// 		{
// 			//////////
// 			// Initialize
// 			//////
// 				memcpy(ecmNew, ecmSource, sizeof(SEditChainManager));
// 
// 
// 			//////////
// 			// Remove the connection to any undo history
// 			// Note:  The undo history will be copied and translated separately if need be
// 			//////
// 				ecmNew->undoHistory = NULL;
// 				iBuilder_createAndInitialize(&xlatRoot, -1);
// 				// Note:  We create the translation regardless so we can update the ecmNew-> members which relate to cursor line, highlighted, etc.
// 
// 
// 			//////////
// 			// Update caller
// 			//////
// 				*root = ecmNew;
// 				// Right now:
// 				//		ecmNew		-- our new SEC
// 				//		ecmSource	-- SEC to duplicate
// 
// 
// 			//////////
// 			// Indicate where we'll be updating
// 			//////
// 				ecPrev	= &ecmNew->ecFirst;
// 				ecLast	= NULL;
// 
// 
// 			//////////
// 			// Duplicate the chain
// 			//////
// 				ecSource = ecmSource->ecFirst;
// 				while (ecSource)
// 				{
// 					//////////
// 					// Create a new entry for this one
// 					//////
// 						ecNew = (SEditChain*)malloc(sizeof(SEditChain));
// 						if (ecNew)
// 						{
// 							// Create a translation for original pointers to new pointers
// 							if (tlIncludeUndoHistory)
// 							{
// 								// Create the translation for this ecSource <--> ecNew
// 								xlat = (STranslate*)iBuilder_allocateBytes(xlatRoot, sizeof(STranslate));
// 								if (xlat)
// 								{
// 									// Create the translation
// 									xlat->p1	= ecSource;									// The old pointer in the undoHistory will point to
// 									xlat->p2	= ecNew;									// the new pointer
// 								}
// 							}
// 
// 						} else {
// 							// Should not happen.
// 							return(false);
// 						}
// 
// 
// 					//////////
// 					// Copy source information to new
// 					//////
// 						memcpy(ecNew, ecSource, sizeof(SEditChain));
// 						*ecPrev		= ecNew;												// Update the prior record to point here
// 						ecNew->prev	= ecLast;												// Point backward to the previous entry
// 						ecNew->next	= NULL;													// Currently points forward to nothing
// 
// 
// 					//////////
// 					// Duplicate its data
// 					//////
// 						ecNew->sourceCode = NULL;
// 						iDatum_duplicate(ecNew->sourceCode, ecSource->sourceCode);
// 
// 
// 					//////////
// 					// General purpose extra data
// 					//////
// 						if (ecSource->extra_info)
// 						{
// 							// Copy any extra_info that's relevant
// 							eiPrev		= &ecNew->extra_info;
// 							eiSource	= ecSource->extra_info;
// 							while (eiSource)
// 							{
// 								//////////
// 								// Duplicate this entry
// 								//////
// 									// Are we duplicating by a function call?  Or manually?
// 									if (*(u32*)&eiSource->extra_info_duplicate != 0)
// 									{
// 										// Function call
// 										eiNew = eiSource->extra_info_duplicate(ecmSource, ecSource, ecSource->extra_info);
// 										// Right now, eiNew has either been updated or not depending on the decision making process in extra_info_duplicate().
// 
// 									} else {
// 										// Manual duplication
// 										eiNew = (SExtraInfo*)malloc(sizeof(SExtraInfo));
// 										if (eiNew)
// 										{
// 											// Copy everything
// 											memcpy(eiNew, eiSource, sizeof(SExtraInfo));
// 
// 											// Clear, and then duplicate the info datum
// 											memset(&eiNew->info, 0, sizeof(eiNew->info));
// 											iDatum_duplicate(&eiNew->info, &eiSource->info);
// 
// 										} else {
// 											// Should not happen
// 											return(false);
// 										}
// 									}
// 
// 
// 								//////////
// 								// Update the back-link if need be
// 								//////
// 									if (eiNew)
// 									{
// 										*eiPrev	= eiNew;
// 										eiPrev	= &eiNew->next;
// 									}
// 
// 
// 								//////////
// 								// Move to next extra_info
// 								//////
// 									eiSource = eiSource->next;
// 							}
// 						}
// 
// 
// 					//////////
// 					// Move to next entry to duplicate
// 					//////
// 						ecLast		= ecNew;
// 						ecPrev		= &ecNew->next;
// 						ecSource	= ecSource->next;
// 				}
// 
// 
// 			//////////
// 			// Translate each of the ecmSource pointers for ecmNew
// 			// Note:  The rest of them use uid lookups
// 			//////
// 				ecmNew->ecFirst				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecFirst);
// 				ecmNew->ecLast				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecLast);
// 				ecmNew->ecTopLine				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecTopLine);
// 				ecmNew->ecCursorLine		= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecCursorLine);
// 				ecmNew->ecCursorLineLast	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecCursorLineLast);
// 				ecmNew->ecSelectedLineStart	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecSelectedLineStart);
// 				ecmNew->ecSelectedLineEnd	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecSelectedLineEnd);
// 
// 
// 			//////////
// 			// Free the pointers
// 			//////
// 				iBuilder_freeAndRelease(&xlatRoot);
// 
// 
// 			//////////
// 			// Indicate success
// 			//////
// 				return(true);
// 		}

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
		SEditChain* ec;


		// Make sure our environment is sane
		// Note:  We do not test for tcText and tnTextLength because we can add blank lines
		ec = NULL;
		if (ecm)
		{
			// Allocate our new structure
			if (ecm->ecLast)
			{
				// Append after the last line
				ec = (SEditChain*)iLl_appendNewNodeAtEnd((SLL**)&ecm->ecLast, sizeof(SEditChain));

			} else {
				// This is the first line, add it and set the last line to the same
				ec = (SEditChain*)iLl_appendNewNodeAtEnd((SLL**)&ecm->ecFirst, sizeof(SEditChain));
				if (ec)
				{
					// Update defaults
					ecm->ecLast					= ec;
					ecm->ecCursorLine			= ec;
					ecm->ecCursorLineLast		= ec;
					ecm->ecTopLine				= ec;
					ecm->ecSelectedLineStart	= NULL;
					ecm->ecSelectedLineEnd		= NULL;
				}
			}

			// Populate if added
			if (ec)
				ec->sourceCode = iDatum_allocate(tcText, tnTextLength);
		}

		// Indicate our status
		return(ec);
	}




//////////
//
// Called to insert a line before or after the indicated line
//
//////
	SEditChain* iEditChainManager_insertLine(SEditChainManager* ecm, s8* tcText, s32 tnTextLength, SEditChain* line, bool tlInsertAfter)
	{
		SEditChain* lineNew;


		// Make sure our environment is sane
		// Note:  We do not test for tcText and tnTextLength because we can add blank lines
		lineNew = NULL;
		if (ecm && line)
		{
			// Create a new entry
			lineNew = (SEditChain*)malloc(sizeof(SEditChain));
			if (lineNew)
			{
				// Initialize
				memset(lineNew, 0, sizeof(SEditChain));

				// Append a blank line
				lineNew->sourceCode = iDatum_allocate(tcText, tnTextLength);

				// Insert before or after the indicated line
				if (tlInsertAfter)
				{
					//////////
					// [line->] [<-after]
					// becomes:
					// [line->] [<-lineNew->] [<after]
					//////
						lineNew->ll.next	= line->ll.next;
						lineNew->ll.prev	= (SLL*)line;
						line->ll.next		= (SLL*)lineNew;


					//////////
					// If there's one after this, have it point back
					//////
						if (lineNew->ll.next)
						{
							// Insert it after
							lineNew->ll.prev		= lineNew->ll.next->prev;
							lineNew->ll.next->prev	= (SLL*)lineNew;

						} else {
							// None after, so we update ecLast
							ecm->ecLast = lineNew;
						}

				} else {
					//////////
					// [before->] [<-line]
					// becomes:
					// [before->] [<-lineNew->] [<-line]
					//////
						lineNew->ll.prev	= line->ll.prev;
						lineNew->ll.next	= (SLL*)line;
						line->ll.prev		= (SLL*)lineNew;


					//////////
					// If there's one before this, have it point forward
					//////
						if (lineNew->ll.next)
						{
							// Insert it before
							lineNew->ll.next		= lineNew->ll.prev->next;
							lineNew->ll.prev->next	= (SLL*)lineNew;

						} else {
							// None after, so we update ecLast
							ecm->ecFirst = lineNew;
						}
				}
			}
		}

		// Indicate our status
		return(lineNew);
	}




//////////
//
// Delete the indicated line
//
//////
	void iEditChainManager_deleteLine(SEditChainManager* ecm)
	{
		SEditChain* lineDeleted;
		SEditChain* lineNewCursorLine;


		// Make sure the environment is sane
		if (ecm && !ecm->isReadOnly && ecm->ecCursorLine)
		{
			// Delete any content on this line
			if (ecm->ecCursorLine->sourceCode)
				iDatum_delete(ecm->ecCursorLine->sourceCode, true);

// TODO:  delete compiler info, and extra info

			// Delete the line itself, and determine which one would be the new line
			lineDeleted			= ecm->ecCursorLine;
			lineNewCursorLine	= (SEditChain*)iLl_deleteNode((SLL*)ecm->ecCursorLine, true);

			// Update anything that may have changed as a result
			if (ecm->ecLast == lineDeleted)
				ecm->ecLast = lineNewCursorLine;

			if (ecm->ecFirst == lineDeleted)
				ecm->ecFirst = lineNewCursorLine;

			if (ecm->ecTopLine == lineDeleted)
				ecm->ecTopLine = lineNewCursorLine;

			ecm->ecCursorLine = lineNewCursorLine;
		}
	}




//////////
//
// Called to get the colors
//
//////
	void iEditChainManager_getColors(SEditChainManager* ecm, SObject* obj, SBgra& backColor, SBgra& foreColor)
	{
		union {
			SSubObjForm*		form;
			SSubObjSubform*		subform;
			SSubObjEditbox*		editbox;
		};


		// Make sure our environment is sane
		if (ecm && obj && obj->sub_obj)
		{
			// What is the object?
			switch (obj->objType)
			{
				case _OBJ_TYPE_FORM:
					// Use the rcClient
					form		= (SSubObjForm*)obj->sub_obj;
					backColor	= form->backColor;
					foreColor	= form->foreColor;
					break;

				case _OBJ_TYPE_SUBFORM:
					// Use the rcClient
					subform		= (SSubObjSubform*)obj->sub_obj;
					backColor	= subform->backColor;
					foreColor	= subform->foreColor;
					break;

				case _OBJ_TYPE_EDITBOX:
					// Use the object default
					editbox		= (SSubObjEditbox*)obj->sub_obj;
					backColor	= editbox->backColor;
					foreColor	= editbox->foreColor;
					break;

				default:
					// Use the system fonts
					form		= (SSubObjForm*)gobj_defaultForm->sub_obj;
					backColor	= form->backColor;
					foreColor	= form->foreColor;
					break;
			}
			// When we get here, we have our rect in relative coordinates.

		} else {
			// It's insane, so we set our rc to something that will prevent processing
			form		= (SSubObjForm*)gobj_defaultForm->sub_obj;
			backColor	= form->backColor;
			foreColor	= form->foreColor;
		}
	}




//////////
//
// Obtains the rectangle we have to operate in.  If the object we relate back to is a
// form or subform, then we use the rcClient parameters created by the last render,
// otherwise we use the object's rc.
//
//////
	SFont* iEditChainManager_getRectAndFont(SEditChainManager* ecm, SObject* obj, RECT* rc)
	{
		SFont* font;
		union {
			SSubObjForm*		form;
			SSubObjSubform*		subform;
			SSubObjEditbox*		editbox;
		};


		// Make sure our environment is sane
		font = gsFont;
		if (ecm && obj && obj->sub_obj)
		{
			// What is the object?
			switch (obj->objType)
			{
				case _OBJ_TYPE_FORM:
					// Use the rcClient
					form = (SSubObjForm*)obj->sub_obj;
					font = form->font;
					CopyRect(rc, &form->rcClient);
					break;

				case _OBJ_TYPE_SUBFORM:
					// Use the rcClient
					subform	= (SSubObjSubform*)obj->sub_obj;
					font	= subform->font;
					CopyRect(rc, &subform->rcClient);
					break;

				case _OBJ_TYPE_EDITBOX:
					// Use the object default
					editbox	= (SSubObjEditbox*)obj->sub_obj;
					font	= editbox->font;
					CopyRect(rc, &obj->rc);
					break;

				default:
					// Use the rc and use the system font
					CopyRect(rc, &obj->rc);
					break;
			}
			// When we get here, we have our rect in relative coordinates.

		} else {
			// It's insane, so we set our rc to something that will prevent processing
			SetRect(rc, 0, 0, 0, 0);
		}

		// Return the font
		return(font);
	}




//////////
//
// Called to render the ECM in the indicated rectangle on the object's bitmap
//
//////
	void iEditChainManager_render(SEditChainManager* ecm, SObject* obj)
	{
		s32				lnTop, lnLeft, lnRight;
		SFont*			font;
		SEditChain*		line;
		SBitmap*		bmp;
		HGDIOBJ			hfontOld;
		SBgra			foreColor, backColor, fillColor;
		RECT			rc, lrc, lrc2, lrc3;


		// Make sure our environment is sane
		if (ecm && ecm->ecTopLine && obj)
		{
			// Get the top line and continue down as far as we can
			line	= ecm->ecTopLine;
			bmp		= obj->bmp;
			lnTop	= 0;

			// Grab font, coordinates, and colors
			font = iEditChainManager_getRectAndFont(ecm, obj, &rc);
			iEditChainManager_getColors(ecm, obj, backColor, foreColor);

			// Prepare
			CopyRect(&lrc, &rc);
			hfontOld = SelectObject(bmp->hdc, font->hfont);

			// Iterate for every visible line
			while (line && lrc.top < rc.bottom)
			{
				//////////
				// Determine the position
				//////
					SetRect(&lrc, rc.left, rc.top + lnTop, rc.right, rc.top + lnTop + font->tm.tmHeight - 1);
					if (lrc.bottom > rc.bottom)
						lrc.bottom = rc.bottom;


				//////////
				// Determine the color
				//////
					if (ecm->ecCursorLine == line)
					{
						// Display in the cursor color line
						SetBkColor(bmp->hdc, RGB(currentStatementBackColor.red, currentStatementBackColor.grn, currentStatementBackColor.blu));
						SetBkMode(bmp->hdc, OPAQUE);
						SetTextColor(bmp->hdc, RGB(currentStatementForeColor.red, currentStatementForeColor.grn, currentStatementForeColor.blu));
						fillColor.color = currentStatementBackColor.color;

					} else {
						// Display in normal background color
						SetBkColor(bmp->hdc, RGB(backColor.red, backColor.grn, backColor.blu));
						SetBkMode(bmp->hdc, OPAQUE);
						SetTextColor(bmp->hdc, RGB(foreColor.red, foreColor.grn, foreColor.blu));
						hfontOld = SelectObject(bmp->hdc, font->hfont);
						fillColor.color = backColor.color;
					}


				//////////
				// Determine the render rectangles (populated area on left, area to clear on right)
				//////
					CopyRect(&lrc2, &lrc);
					// Will we fit?
					if (ecm->leftColumn < line->sourceCodePopulated)
					{
						// Draw the portion that will fit
						DrawText(bmp->hdc, line->sourceCode->data + ecm->leftColumn, line->sourceCodePopulated - ecm->leftColumn, &lrc2, DT_END_ELLIPSIS | DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_CALCRECT);

					} else {
						// We're scrolled past this line, so the entire area must be filled in
						SetRect(&lrc2, rc.left, lrc.top, rc.left, lrc.bottom);
					}
					// Set the clear border
					SetRect(&lrc3, lrc2.right, lrc.top, rc.right, lrc.bottom + 1);


				//////////
				// Draw the text
				//////
					if (ecm->leftColumn < line->sourceCodePopulated)
						DrawText(bmp->hdc, line->sourceCode->data + ecm->leftColumn, line->sourceCodePopulated - ecm->leftColumn, &lrc2, DT_END_ELLIPSIS | DT_VCENTER | DT_LEFT | DT_SINGLELINE);
					

				//////////
				// Clear the rest of the line
				//////
					iBmp_fillRect(bmp, &lrc3, fillColor, fillColor, fillColor, fillColor, false);


				//////////
				// Draw the cursor if on the cursor line
				//////
					if (ecm->ecCursorLine == line)
					{
						lnLeft	= rc.left + ((ecm->column - ecm->leftColumn) * font->tm.tmAveCharWidth);
						lnRight	= lnLeft + font->tm.tmAveCharWidth;
						iBmp_invert(bmp, lnLeft, ((ecm->isOverwrite) ? lrc.bottom - 2 : lrc.top), lnRight, lrc.bottom);
					}


				//////////
				// Move down to the next row
				//////
					lnTop	+= font->tm.tmHeight;
					line	= (SEditChain*)line->ll.next;
			}

			// Fill in the remainder of the display
			SetRect(&lrc, rc.left, rc.top + lnTop, rc.right, rc.bottom);
			iBmp_fillRect(bmp, &lrc, backColor, backColor, backColor, backColor, false);

			// Reset the font
			SelectObject(bmp->hdc, hfontOld);
		}
	}




//////////
//
// Called to verify the cursor is visible by adjuting ecm->leftColumn
//
//////
	bool iEditChainManager_verifyCursorIsVisible(SEditChainManager* ecm, RECT* rc, SFont* font)
	{
		bool llChanged;


		// Make sure our environment is sane
		llChanged = false;
		if (ecm)
		{
			// Make sure we're not before it to the left
			if (ecm->column < ecm->leftColumn)
			{
				ecm->leftColumn	= ecm->column;
				llChanged		= true;
			}

			// Make sure we're not beyond it to the right
			if ((ecm->column - ecm->leftColumn) * font->tm.tmAveCharWidth > rc->right)
			{
				ecm->leftColumn	+= (rc->right - ((ecm->column - ecm->leftColumn) * font->tm.tmAveCharWidth)) / font->tm.tmAveCharWidth;
				llChanged		= true;
			}
		}

		// Indicate our status
		return(llChanged);
	}




//////////
//
// Called to process the ASCII character into the input buffer.
//
//////
	bool iEditChainManager_keystroke(SEditChainManager* ecm, SObject* obj, u8 asciiChar)
	{
		bool	llDirty;
		SFont*	font;
		RECT	lrc;


		//////////
		// Indicate initially that no changes were made that require a re-render
		//////
			llDirty = false;
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		// Make sure our environment is sane
// TODO:  Added the extra test on ecm->column because of a bug when scrolling... will fix. :-)
		if (ecm && !ecm->isReadOnly && ecm->column < _ECM_MINIMUM_LINE_ALLOCATION_LENGTH - 10)
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
				if (!ecm->isOverwrite)
				{
					// We are inserting
					if (ecm->ecSelectedLineStart != NULL)
					{
						// There is a selection, which means we are replacing everything that's selected with this new keystroke
// TODO:  write this code

					} else {
						// We are just overwriting whatever's there
						llDirty = iEditChain_characterInsert(ecm, asciiChar);
					}

				} else {
					// We are overwriting
					if (ecm->ecSelectedLineStart != NULL)
					{
						// There is a selection, which means we are replacing everything that's selected with this new keystroke
// TODO:  write this code

					} else {
						// We are just overwriting whatever's there
						llDirty = iEditChain_characterOverwrite(ecm, asciiChar);
					}
				}
		}

		// If we updated something, mark the object dirty
		if (llDirty)
			obj->isDirty = true;

		// Indicate our status
		return(llDirty);
	}




//////////
//
// Called to navigate rows (deltaY) or columns (deltaX) or both.
//
//////
	bool iEditChainManager_navigate(SEditChainManager* ecm, SObject* obj, s32 deltaY, s32 deltaX)
	{
		s32				lnI, lnTop, lnBottom;
		bool			llResetTopLine;
		SFont*			font;
		SEditChain*		line;
		SEditChain*		lineRunner;
		RECT			lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (ecm && ecm->ecCursorLine && ecm->ecCursorLine->sourceCode)
			{
				//////////
				// Grab the line and form
				//////
					line = ecm->ecCursorLine;


				//////////
				// Navigate by lines
				//////
					if (deltaY != 0)
					{
						if (deltaY > 0)
						{
							// Going forward
							for (lnI = 0; line->ll.next && lnI != deltaY; lnI++)
								line = (SEditChain*)line->ll.next;

							// We need to scan forward from ecTopLine to see if we'd be off screen.
							// If so, we drag ecTopLine forward until we reach the visible portion
							lnTop		= lrc.top;
							lnBottom	= lrc.bottom - font->tm.tmHeight;
							lineRunner	= ecm->ecTopLine;
							while (ecm->ecTopLine->ll.next && lineRunner != line)
							{
								//////////
								// Are we still on screen?
								//////
									if (lnTop > lnBottom)
									{
										// We're off screen, so we're dragging the top forward
										ecm->ecTopLine = (SEditChain*)ecm->ecTopLine->ll.next;

									} else {
										// Still on the same page
										lnTop += font->tm.tmHeight;
									}


								//////////
								// Move to next line
								//////
									lineRunner = (SEditChain*)lineRunner->ll.next;
							}

						} else {
							// Going backward
							llResetTopLine = false;
							for (lnI = 0; line->ll.prev && lnI != deltaY; lnI--)
							{
								// Are we dragging the top line with us yet?
								if (ecm->ecTopLine == line)
									llResetTopLine = true;

								// Move back one line
								line = (SEditChain*)line->ll.prev;
							}

							if (llResetTopLine)
								ecm->ecTopLine = line;
						}

					//////////
					// Update the pointers
					//////
						ecm->ecCursorLine = line;
				}


				//////////
				// Move columns
				//////
					if (deltaX != 0)
					{
						if (deltaX < 0)
						{
							// Moving left
							ecm->column = max(ecm->column + deltaX, 0);

						} else {
							// Moving right
							ecm->column += deltaX;
						}
					}


				//////////
				// Verify we're visible
				//////
					iEditChainManager_verifyCursorIsVisible(ecm, &lrc, font);


				// Indicate success
				return(true);
			}


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
		s32		lnI;
		SFont*	font;
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (ecm && ecm->ecCursorLine && ecm->ecCursorLine->sourceCode && deltaY != 0)
			{
				//////////
				// Determine how many visible lines there are and move that far
				//////
					deltaY = deltaY * ((lrc.bottom - lrc.top) / font->tm.tmHeight);
					if (deltaY > 0)
					{
						// Going forward
						for (lnI = 0; ecm->ecCursorLine->ll.next && lnI != deltaY; lnI++)
						{
							// Move the top line to the next line
							ecm->ecTopLine		= (SEditChain*)ecm->ecTopLine->ll.next;
							ecm->ecCursorLine	= (SEditChain*)ecm->ecCursorLine->ll.next;
						}

					} else {
						// Going backward
						for (lnI = 0; ecm->ecCursorLine->ll.prev && lnI != deltaY; lnI--)
						{
							// Move the top line up (if we can)
							if (ecm->ecTopLine->ll.prev)
								ecm->ecTopLine	= (SEditChain*)ecm->ecTopLine->ll.prev;

							// Move the cursor line up
							ecm->ecCursorLine	= (SEditChain*)ecm->ecCursorLine->ll.prev;
						}

					}


				//////////
				// Verify we're visible
				//////
					iEditChainManager_verifyCursorIsVisible(ecm, &lrc, font);


				// Indicate success
				return(true);
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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		if (ecm)
		{
			// Toggle the flag
			ecm->isOverwrite = !ecm->isOverwrite;

			// Toggling insert changes the shape of the cursor, so we always redraw
			return(true);
		}

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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// 
//
//////
	bool iEditChainManager_returnKey(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		// Make sure the environment is sane
		if (ecm && !ecm->isReadOnly && ecm->ecCursorLine && obj)
		{
			// If we're in insert mode, we split the line
			if (!ecm->isOverwrite)
			{
				// Insert mode
				iEditChainManager_insertLine(ecm, NULL, 0, ecm->ecCursorLine, true);	// Append a new line after the cursor line

			} else {
				// Overwrite mode
				if (!ecm->ecCursorLine->ll.next)
					iEditChainManager_appendLine(ecm, NULL, 0);		// Append a new line at the end
			}

			// Move to the new line, and to the start of that line
			iEditChainManager_navigate(ecm, obj, 1, -ecm->column);

			// Indicate success
			return(true);
		}


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*			font;
		SEditChain*		line;
		RECT			lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (ecm && ecm->ecCursorLine && ecm->ecCursorLine->sourceCode)
			{
				//////////
				// Grab the line and form
				//////
					line = ecm->ecCursorLine;


				//////////
				// Iterate until we find a space
				//////
					if (ecm->column == 0 || line->sourceCodePopulated == 0)
					{
						// We have to go to the previous line (if we can)
						if (ecm->ecFirst != line)
						{
							// Go up one line
							iEditChainManager_navigate(ecm, obj, -1, 0);

							// Go to the end of this line
							iEditChainManager_navigate(ecm, obj, 0, ecm->ecCursorLine->sourceCodePopulated);

							// Continue looking word left on this line
							return(iEditChainManager_navigateWordLeft(ecm, obj));
						}

					} else if (line->sourceCodePopulated < ecm->column) {
						// We're beyond end of line, move to the end of line
						iEditChainManager_navigate(ecm, obj, 0, ecm->ecCursorLine->sourceCodePopulated - ecm->column);

						// Then continue looking word left on this line
						return(iEditChainManager_navigateWordLeft(ecm, obj));

					} else {
						//////////
						// We're somewhere on the line, move one column left first
						//////
							--ecm->column;


						//////////
						// If we're on a whitespace character, scan left until we reach a non-whitespace character
						//////
							// When we get to the first non-whitespace, we break
							for ( ; ecm->column > 0 && (line->sourceCode->data[ecm->column] == 32 || line->sourceCode->data[ecm->column] == 9); )
								--ecm->column;


						//////////
						// If we're not at the beginning of the line, then we look for the first whitespace character
						//////
							if (ecm->column != 0)
							{
								// Search left for the first whitespace or comma
								for ( ; ecm->column > 0; ecm->column--)
								{
									// Did we find a whitespace to our left?
									if (line->sourceCode->data[ecm->column - 1] == 32 || line->sourceCode->data[ecm->column - 1] == 9 || line->sourceCode->data[ecm->column - 1] == ',')
										break;	// Yes
								}
							}
					}


				//////////
				// Verify we're visible
				//////
					iEditChainManager_verifyCursorIsVisible(ecm, &lrc, font);


				// Indicate success
				return(true);
			}


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
		SFont*			font;
		SEditChain*		line;
		RECT			lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (ecm && ecm->ecCursorLine && ecm->ecCursorLine->sourceCode)
			{
				//////////
				// Grab the line and form
				//////
					line = ecm->ecCursorLine;


				//////////
				// Iterate until we find a space
				//////
					if (ecm->column >= line->sourceCodePopulated)
					{
						// We have to go to the next line (if we can)
						if (ecm->ecLast != line)
						{
							// Go down one line
							iEditChainManager_navigate(ecm, obj, 1, 0);

							// Go to the start of the line
							if (ecm->column > 0)
								iEditChainManager_navigate(ecm, obj, 0, -ecm->column);

							// Continue looking word left on this line
							return(iEditChainManager_navigateWordRight(ecm, obj));
						}

					} else {
						//////////
						// We're somewhere on the line, move one column right first
						//////
							++ecm->column;


						//////////
						// If we're on a whitespace character, scan left until we reach a non-whitespace character
						//////
							// When we get to the first non-whitespace, we break
							for ( ; ecm->column < line->sourceCodePopulated && (line->sourceCode->data[ecm->column] == 32 || line->sourceCode->data[ecm->column] == 9); )
								++ecm->column;


						//////////
						// If we're not at the end of the line, then we look for the first whitespace character
						//////
							if (ecm->column < line->sourceCodePopulated)
							{
								// Search right for the first whitespace or comma
								for ( ; ecm->column < line->sourceCodePopulated; ecm->column++)
								{
									// Did we find a whitespace to our left?
									if (line->sourceCode->data[ecm->column + 1] == 32 || line->sourceCode->data[ecm->column + 1] == 9 || line->sourceCode->data[ecm->column + 1] == ',')
										break;	// Yes
								}

							} else {
								// We have to go to the next line (if we can)
								if (ecm->ecLast != line)
								{
									// Go down one line
									iEditChainManager_navigate(ecm, obj, 1, 0);

									// Go to the start of the line
									if (ecm->column > 0)
										iEditChainManager_navigate(ecm, obj, 0, -ecm->column);

									// Continue looking word left on this line
									return(iEditChainManager_navigateWordLeft(ecm, obj));
								}
							}
					}


				//////////
				// Verify we're visible
				//////
					iEditChainManager_verifyCursorIsVisible(ecm, &lrc, font);


				// Indicate success
				return(true);
			}


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
		// Make sure the environment is sane
		if (ecm && ecm->ecFirst)
		{
			// Save previous position
			ecm->ecCursorLineLast	= ecm->ecCursorLine;

			// Move to top of the document
			ecm->ecTopLine			= ecm->ecFirst;
			ecm->ecCursorLine		= ecm->ecFirst;

			// Indicate we did something
			return(true);
		}


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
		s32				lnTop, lnBottom;
		SFont*			font;
		SEditChain*		line;
		RECT			lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (ecm && !ecm->isReadOnly && ecm->ecCursorLine)
			{
				//////////
				// Grab the line and form
				//////
					line = ecm->ecCursorLine;


				//////////
				// Navigate to the end
				//////
					// We need to scan forward from ecTopLine to see if we'd be off screen.
					// If so, we drag ecTopLine forward until we reach the visible portion
					lnTop		= lrc.top;
					lnBottom	= lrc.bottom - font->tm.tmHeight;
					while (ecm->ecTopLine->ll.next && line->ll.next)
					{
						//////////
						// Are we still on screen?
						//////
							if (lnTop > lnBottom)
							{
								// We're off screen, so we're dragging the top forward
								ecm->ecTopLine = (SEditChain*)ecm->ecTopLine->ll.next;

							} else {
								// Still on the same page
								lnTop += font->tm.tmHeight;
							}


						//////////
						// Move to next line
						//////
							line = (SEditChain*)line->ll.next;
					}


				//////////
				// Update the cursor line
				//////
					ecm->ecCursorLine = line;


				//////////
				// Verify we're visible
				//////
					iEditChainManager_verifyCursorIsVisible(ecm, &lrc, font);


				// Indicate success
				return(true);
			}


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


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
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to delete one character left (backspace)
//
//////
	bool iEditChainManager_deleteLeft(SEditChainManager* ecm, SObject* obj)
	{
		SEditChain*	line;
		SEditChain*	lineLast;
		SFont*		font;
		RECT		lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (ecm && !ecm->isReadOnly && ecm->ecCursorLine)
			{
				// Grab the line
				line		= ecm->ecCursorLine;
				lineLast	= ecm->ecLast;

				// If there's nothing on this line, delete it
				if (ecm->ecCursorLine->sourceCodePopulated == 0)
				{
					if (ecm->ecFirst != ecm->ecLast)
					{
						// Delete the current line
						iEditChainManager_deleteLine(ecm);

						if (lineLast != line)
						{
							// Navigate up one line
							iEditChainManager_navigate(ecm, obj, -1, 0);
						}

						// Navigate to the end of the current line
						iEditChainManager_navigate(ecm, obj, 0, ecm->ecCursorLine->sourceCodePopulated - ecm->column);
					}

				} else {
					// Do we need to do anything?
					if (ecm->column == 0)
					{
						if (ecm->ecFirst != ecm->ecLast)
						{
							// Delete the current line
							iEditChainManager_deleteLine(ecm);

							if (lineLast != line)
							{
								// Navigate up one line
								iEditChainManager_navigate(ecm, obj, -1, 0);
							}

							// Navigate to the end of the current line
							iEditChainManager_navigate(ecm, obj, 0, ecm->ecCursorLine->sourceCodePopulated - ecm->column);
						}

					} else if (ecm->column > 0 && ecm->column <= line->sourceCodePopulated) {
						// Reduce our column position
						--ecm->column;

						// Based on insert, handle it different
						if (!ecm->isOverwrite)
						{
							// We're in insert mode, so we drag everything with us
							iEditChain_characterDelete(ecm);

						} else {
							// We're in overwrite mode, so we just insert a space
							iEditChain_characterOverwrite(ecm, ' ');

							// The overwrite moves us back right again, so we reduce our column position
							--ecm->column;
						}
					}
				}


				//////////
				// Verify we're visible
				//////
					iEditChainManager_verifyCursorIsVisible(ecm, &lrc, font);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select one character right (delete key)
//
//////
	bool iEditChainManager_deleteRight(SEditChainManager* ecm, SObject* obj)
	{
		SFont*	font;
		RECT	lrc;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (ecm && !ecm->isReadOnly && ecm->ecCursorLine)
			{
				if (ecm->ecCursorLine->sourceCodePopulated == 0)
				{
					// There's no data on this line, if we're in insert mode delete the line
					if (!ecm->isOverwrite)
						iEditChainManager_deleteLine(ecm);

				} else {
					// Delete everything to the right
					iEditChain_characterDelete(ecm);
				}


				//////////
				// Verify we're visible
				//////
					iEditChainManager_verifyCursorIsVisible(ecm, &lrc, font);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to delete one word left (ctrl+backspace)
//
//////
	bool iEditChainManager_deleteWordLeft(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to delete one word right (ctrl+delete)
//
//////
	bool iEditChainManager_deleteWordRight(SEditChainManager* ecm, SObject* obj)
	{
		RECT	lrc;
		SFont*	font;


		//////////
		// Grab the rectangle we're working in
		//////
			font = iEditChainManager_getRectAndFont(ecm, obj, &lrc);


		// If we get here, indicate failure
		return(false);
	}
