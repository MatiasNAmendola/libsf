//////////
//
// /libsf/utils/dsf/msvc++/dsf/dsf/dsf.cpp
//
//////
//
//
//////
// Version 0.60
// Copyright (c) 2013 by Rick C. Hodgin
//////
// Last update:
//     Dec.02.2013
//////
// Change log:
//     Dec.02.2013	- Initial creation
//////
//
// Top-level program for DSF.DLL. Contains all helper algorithms for creating binary characters
// of existing font sets for translation into the DSF format.
//
//////////
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




#include "dsf.h"




//////////
//
// Main DLL entry point
//
//////
	BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
	{
		//////////
		// Store the instance for global use
		//////
			ghInstance = hModule;


		//////////
		// Windows tells us why we're being invoked
		//////
			switch (ul_reason_for_call)
			{
				case DLL_PROCESS_ATTACH:
					initialize();
					break;
				case DLL_THREAD_ATTACH:
				case DLL_THREAD_DETACH:
				case DLL_PROCESS_DETACH:
					break;
			}
			return TRUE;
	}




//////////
//
// Called to obtain the bitmap of the indicated character.
//
//////
	int dsf_get_character_bitmap(int tnAscii, char* tcBitmapFilename, char* tcFloanFilename, char* tcFontName, int tnHeight, int tnWidth)
	{
		int		lnResult;
		bool	llPseudo;
		char	buffer[] = "delete_me.bmp";


		//////////
		// Make sure there is a valid filename
		//////
			if (!tcBitmapFilename || strlen(tcBitmapFilename) == 0)
			{
				llPseudo			= true;
				tcBitmapFilename	= (char*)buffer;		// Use our fake filename
			}


		//////////
		// Grab the bitmap
		//////
			lnResult = iGetCharacterBitmap(tnAscii, tcBitmapFilename, tcFontName, tnHeight, tnWidth);


		//////////
		// If they want the floan data, generate it
		//////
			if (lnResult == 0 && tcFloanFilename)
				lnResult = iGetFloanFromBitmap(tnAscii, tcBitmapFilename, tcFloanFilename);


		//////////
		// If we had to create a temporary filename, delete it
		//////
			if (llPseudo)
				DeleteFileA(tcBitmapFilename);


		//////////
		// Indicate success or failure
		//////
			return(lnResult);
	}




//////////
//
// Called to scale a bitmap to the indicated size, and clip it to some other portion.  This
// algorithm was created to allow the user to obtain a font from dsf_get_character_bitmap(),
// but then to override the default generated image to make it resized appropriately for the
// target font.
//
//////
	int dsf_scale_and_clip_bitmap(char* tcBitmapFilenameIn, char* tcBitmapFilenameOut, f64 tfWidth, f64 tfHeight, int tnClipLeft, int tnClipTop, int tnNewWidth, int tnNewHeight)
	{
// TODO:  This feature may be supplanted by using the templates point system, whereby points are simply manipulated rather than a physical bitmap being scaled.
// TODO:  However, "We shall see, Xur.  We shall see."  Can you name that quote? :-)  Here's another clue:  "It takes more than a sceptor to rule, Xur, even on Rylos."
// TODO:  https://www.youtube.com/watch?v=JwaRQ-_kgy8
		return(0);
	}




//////////
//
//  Called to initiate a new session of editing.
//
//////
	int dsf_create_new_instance(void)
	{
		union {
			SInstance*	p;
			u32			value;
		};


		//////////
		// Allocate our instance
		//////
			p = (SInstance*)builder_allocateBytes(instances, sizeof(SInstance));


		//////////
		// Initialize it
		//////
			memset(p, 0, sizeof(SInstance));
			builder_createAndInitialize(&p->chars,	-1);
			builder_createAndInitialize(&p->refs,	-1);
			builder_createAndInitialize(&p->hwnds,	-1);


		//////////
		// Brand it
		//////
			memcpy(&p->id, cgcDsfBrand, sizeof(p->id));
			p->id_size		= sizeof(SInstance);
			p->activeChar	= 65;				// Default to "A"


		//////////
		// Return the address as its handle
		//////
			return(value);
	}




//////////
//
// Called to set the data for the font instance
//
//////
	int dsf_set_font_data(u32 tnInstance,	f64 tfAscent,	f64 tfUpper,	f64 tfLower,		f64 tfLeft,			f64 tfRight,
											f64 tfBase,		f64 tfDescent,	f64 tfWidth,
											f64 tfItalics,	f64 tfBold,		f64 tfUnderTop,		f64 tfUnderBot,		f64 tfStrikeTop,	f64 tfStrikeBot)
	{
		SInstance*	p;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);

		//////////
		// Store the indicated data
		//////
			p->font.fAscent		= tfAscent;				// See the explanations in the VFP DSF project, frmEdit::create_tables()
			p->font.fUpper		= tfUpper;
			p->font.fLower		= tfLower;
			p->font.fLeft		= tfLeft;
			p->font.fRight		= tfRight;
			p->font.fBase		= tfBase;
			p->font.fDescent	= tfDescent;
			p->font.fWidth		= tfWidth;
			p->font.fItalics	= tfItalics;
			p->font.fBold		= tfBold;
			p->font.fUnderTop	= tfUnderTop;
			p->font.fUnderBot	= tfUnderBot;
			p->font.fStrikeTop	= tfStrikeTop;
			p->font.fStrikeBot	= tfStrikeBot;


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to load a character with its data based on (u8)tnType (S=Spline, D=Definition,
// R=Reference, L=Link). For Definition entries, tiid must be above the standard 0..255 ASCII
// character range.  Reference entries will be in the 0..255 range, but tiLnkId must refer to
// an entry 256 or above.  Link entries can refer to any item, but must also include tiLnkOrder
// to indicate what explicit item they want to modify.
//
//////
	int dsf_load_character(u32 tnInstance,	u32 tnType, u32 tiid, u32 tiOrder, s8* tcDesc10, u32 tlNewStroke, u32 tlSelected,
											f64 tfOx, f64 tfOy, f64 tfOt, f64 tfLr, f64 tfLt, f64 tfRr, f64 tfRt, 
											u32 tiSubdivs, u32 tiLnkId, u32 tiLnkOrder)
	{
		SInstance*	p;
		SSpline*	s;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);

			// See if this character is of a higher number than previous ones
			if (tiid > p->maxChar)
				p->maxChar = tiid;


		//////////
		// Find or create the indicated character instance
		//////
			s = iFindSplineInstance(p->chars, tiid, (u8)tnType, tiOrder, tiLnkId, tiLnkOrder);
			if (!s)
				return(-2);		// Error finding (an invalid combination was provided)


		//////////
		// Populate the data
		//////
			s->cType		= (u8)tnType;
			s->iid			= tiid;
			s->iOrder		= tiOrder;
			s->lPenDown	= ((tlNewStroke == 0) ? false : true);
			s->lSelected	= ((tlSelected == 0) ? false : true);
			s->ox			= tfOx;
			s->oy			= tfOy;
			s->ot			= tfOt;
			s->lr			= tfLr;
			s->lt			= tfLt;
			s->rr			= tfRr;
			s->rt			= tfRt;
			s->iSubdivs		= tiSubdivs;
			s->iLnkId		= tiLnkId;
			s->iLnkOrder	= tiLnkOrder;

			// Store the description
			memcpy(&s->cDesc[0], tcDesc10, 10);
		

		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_load_reference(u32 tnInstance,	u32 tnType, s8* tcDesc40,
											f64 tfRef1X, f64 tfRef1Y,
											f64 tfRef2X, f64 tfRef2Y,
											f64 tfRef3X, f64 tfRef3Y,
											f64 tfRef4X, f64 tfRef4Y,
											f64 tfRef5X, f64 tfRef5Y,
											bool tlVisible, s8* tcChars1_128, s8* tcChars2_128)
	{
		SInstance*	p;
		SRefs*		r;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			r = iFindRefsInstance(p->refs, (u8)tnType, tcDesc40);
			if (!r)
			{
				// It's a new entry
				r = (SRefs*)builder_allocateBytes(p->refs, sizeof(SRefs));
				if (!r)
					return(-2);		// Error allocating

				// Initialize it
				memset(r, 0, sizeof(SRefs));
			}


		//////////
		// Populate the data
		//////
			r->cType		= (u8)tnType;

			r->fref1x		= tfRef1X;
			r->fref1y		= tfRef1Y;

			r->fref2x		= tfRef2X;
			r->fref2y		= tfRef2Y;

			r->fref3x		= tfRef3X;
			r->fref3y		= tfRef3Y;

			r->fref4x		= tfRef4X;
			r->fref4y		= tfRef4Y;

			r->fref5x		= tfRef5X;
			r->fref5y		= tfRef5Y;

			r->lVisible		= tlVisible;

			memcpy(&r->cDesc[0], tcDesc40, 40);
			memcpy(&r->cChars1[0], tcChars1_128, 128);
			memcpy(&r->cChars2[0], tcChars2_128, 128);


		//////////
		// Release the floan data.  It will be re-populated later if this ref is ever referenced
		//////
			builder_freeAndRelease(&r->floans);


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_load_template(u32 tnInstance, u32 tipid, f32 tfX, f32 tfY, u32 tnRecno)
	{
		SInstance*	p;
		STems*		t;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			if (tfX < 0.0 || tfX > 1.0 || tfY < 0.0 || tfY > 1.0)
				return(-2);		// Invalid parameter

			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			t = iCreateNewTemsEntry(p->chars, tipid);
			if (!t)
				return(-2);		// Error allocating


		//////////
		// Populate the data
		//////
			t->fx		= tfX;
			t->fy		= tfY;
			t->recno	= tnRecno;


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called once all of the initial loading of data is complete.
//
//////
	void dsf_initial_load_complete(u32 tnInstance, u32 tnWidth, u32 tnHeight)
	{
		u32			lnI, lnJ, lnTemsRawCount, lnTemsTempCount;
		f64			lfWidth, lfHeight;
		SInstance*	p;
		SChars*		c;
		SXYS32*		temsTemp;
		SXYS32*		temsTempLast;
		SBuilder*	temsTempBuilder;		// Temporary builder used to convert temsRaw into aliased pixel values
		STems*		t;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return;


		//////////
		// Convert the temsRaw into something used explicitly for the current window size
		//////
			lfWidth		= (f64)max(tnWidth,		400);
			lfHeight	= (f64)max(tnHeight,	400);


		//////////
		// Sort the lists
		//////
			for (lnI = 0; lnI < p->chars->populatedLength; lnI += sizeof(SChars))
			{
				//////////
				// Grab this pointer
				//////
					c = (SChars*)(p->chars->data + lnI);


				//////////
				// Are there any tems?
				//////
					if (c->temsRaw->populatedLength != 0)
					{
						// Initialize our builder
						builder_createAndInitialize(&temsTempBuilder, -1);


						//////////
						// Iterate through and create entries in temsTemp for the aliased pixel values
						//////
							// Sort the raw list
							lnTemsRawCount = c->temsRaw->populatedLength / sizeof(STems);
							qsort(c->temsRaw->data, lnTemsRawCount, sizeof(STems), iiTems_qsortCallback);
							for (lnJ = 0; lnJ < c->temsRaw->populatedLength; lnJ += sizeof(STems))
							{
								// Grab the pointer
								t = (STems*)(c->temsRaw->data + lnJ);

								// Create the temporary list of aliased pixel values
								temsTemp = (SXYS32*)builder_allocateBytes(temsTempBuilder, sizeof(SXYS32));
								if (temsTemp)
								{
									// Translate through to the aliased size
									temsTemp->xi	= (s32)((f64)t->fx * lfWidth);
									temsTemp->yi	= (s32)((f64)t->fy * lfHeight);
								}
							}
							// When we get here, we have a completely aliased set of coordinates


						//////////
						// Convert the aliased list into a list of real entries, unique per pixel
						//////
							// Sort the aliased list
							lnTemsTempCount = temsTempBuilder->populatedLength / sizeof(SXYS32);
							qsort(temsTempBuilder->data, lnTemsTempCount, sizeof(SXYS32), iiSXyS32_qsortCallback);
							for (lnJ = 0; lnJ < temsTempBuilder->populatedLength; lnJ += sizeof(SXYS32))
							{
								// Grab the pointer
								temsTemp = (SXYS32*)(temsTempBuilder->data + lnJ);

								// Has it changed?
								if (lnJ == 0 || temsTempLast->xi != temsTemp->xi || temsTempLast->yi != temsTemp->yi)
								{
									// This is now our new last item
									temsTempLast = temsTemp;

									// Create the converted data
									t = (STems*)builder_allocateBytes(c->tems, sizeof(STems));
									if (t)
									{
										// Translate through to the aliased size
										t->fx	= ((f64)temsTemp->xi / lfWidth)  + 0.0000001;
										t->fy	= ((f64)temsTemp->yi / lfHeight) + 0.0000001;
									}
								}
							}
							// When we get here, c->tems is populated with a list of only aliased pixel values


						//////////
						// Release our builder
						//////
							builder_freeAndRelease(&temsTempBuilder);
					}
			}
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_get_changed_template(u32 tnInstance, u32 tipid, s8* tcY12, s8* tcX12, s8* tcRecno12, u32 tnNextNewRecno)
	{
		u32			lnI;
		SInstance*	p;
		SBuilder*	tems;
		STems*		t;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			tems = iGetTemsRawBuilder(p->chars, tipid);
			if (!tems)
				return(-2);		// Error accessing this pid


		//////////
		// Find the first changed entry
		//////
			for (lnI = 0; lnI < tems->populatedLength; lnI += sizeof(STems))
			{
				// Grab the pointer
				t = (STems*)(tems->data + lnI);

				// If it's changed, but not deleted
				if (t->changed && !t->deleted)
				{
					// Update the recno() if it's a new item
					if (t->recno == -1)
						t->recno = tnNextNewRecno;

					// Store each item
					sprintf(tcX12,		"%7.5f",	t->fx);
					sprintf(tcY12,		"%7.5f",	t->fy);
					sprintf(tcRecno12,	"%u",		t->recno);

					// Mark it no longer changed
					t->changed = false;

					// Indicate success
					return(0);
				}
			}


		//////////
		// Indicate that there are no more items
		//////
			return(-3);
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_get_deleted_template(u32 tnInstance, u32 tipid, s8* tcRecno12)
	{
		u32			lnI;
		SInstance*	p;
		SBuilder*	tems;
		STems*		t;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			tems = iGetTemsRawBuilder(p->chars, tipid);
			if (!tems)
				return(-2);		// Error accessing this pid


		//////////
		// Find the first changed entry
		//////
			for (lnI = 0; lnI < tems->populatedLength; lnI += sizeof(STems))
			{
				// Grab the pointer
				t = (STems*)(tems->data + lnI);

				// Report on previously existing deleted items.  If the user adds an item, then
				// deletes it before saving it is simply an orphan record that will be freed at exit.
				if (t->deleted && t->recno != -1)
				{
					// Store the record number
					sprintf(tcRecno12, "%u", t->recno);

					// Indicate success
					return(0);
				}
			}


		//////////
		// Indicate that there are no more items
		//////
			return(-3);
	}




//////////
//
// Called to set the cues the user wants to see, along with whether or not the mouse should track
// near to any of the specified cues.
//
//////
	int dsf_user_cues(u32 tnInstance,	u32 tnAscent,			u32 tnTrackAscent, 
										u32 tnUpper,			u32 tnTrackUpper, 
										u32 tnLower,			u32 tnTrackLower, 
										u32 tnBase,				u32 tnTrackBase, 
										u32 tnDescent,			u32 tnTrackDescent, 
										u32 tnStrikethrough,	u32 tnTrackStrike, 
										u32 tnUnderline,		u32 tnTrackUnderline, 
										u32 tnRefs,				u32 tnTrackRefs)
	{
		SInstance*	p;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Set the values, and trigger a refresh on any markup windows
		//////
			p->ascent			= iValidateRange(tnAscent,			 	_NO, 	_YES,	_NO);
			p->trackAscent		= iValidateRange(tnTrackAscent,			_NO,	_YES,	_NO);
			p->upper			= iValidateRange(tnUpper,				_NO,	_YES,	_NO);
			p->trackUpper		= iValidateRange(tnTrackUpper,			_NO,	_YES,	_NO);
			p->lower			= iValidateRange(tnLower,				_NO,	_YES,	_NO);
			p->trackLower		= iValidateRange(tnTrackLower,			_NO,	_YES,	_NO);
			p->base				= iValidateRange(tnBase,				_NO,	_YES,	_NO);
			p->trackBase		= iValidateRange(tnTrackBase,			_NO,	_YES,	_NO);
			p->descent			= iValidateRange(tnDescent,				_NO,	_YES,	_NO);
			p->trackDescent		= iValidateRange(tnTrackDescent,		_NO,	_YES,	_NO);
			p->strikethrough	= iValidateRange(tnStrikethrough,		_NO,	_YES,	_NO);
			p->trackStrike		= iValidateRange(tnTrackStrike,			_NO,	_YES,	_NO);
			p->underline		= iValidateRange(tnUnderline,			_NO,	_YES,	_NO);
			p->trackUnderline	= iValidateRange(tnTrackUnderline,		_NO,	_YES,	_NO);
			p->showRefs			= iValidateRange(tnRefs,				_NO,	_YES,	_NO);
			p->trackRefs		= iValidateRange(tnTrackRefs,			_NO,	_YES,	_NO);
			// Note:  We do not render here because the cues and settings are usually sent one after the other


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to convey user settings
//
//////
	int dsf_user_settings(u32 tnInstance,
							u32 tnDisposition, u32 tnMode, u32 tnMethod, u32 tnRange,
							u32 tlShowTems, u32 tnTemsType,
							u32 tlShowSplines, u32 tnSplinesType,
							u32 tlHighlighSectionOnFinal, u32 tlShowPenDowns, u32 tlShowMouseCrosshairs,
							u32 tlInvert, u32 tlZoomLens,
							u32 tnSelectArea)
	{
		u32			lnI;
		SInstance*	p;
		SHwnd*		h;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Set the values, and trigger a refresh on any markup windows
		//////
			p->disposition				= iValidateRange(tnDisposition,				_DISPOSITION_SELECT,	_DISPOSITION_FLIP_LM_RM,	_DISPOSITION_SELECT);
			p->mode						= iValidateRange(tnMode,					_MODE_POINT,			_MODE_AFTER,				_MODE_POINT);
			p->method					= iValidateRange(tnMethod,					_METHOD_LEFT,			_METHOD_POINT,				_METHOD_POINT);
			p->range					= iValidateRange(tnRange,					_RANGE_ACTIVE_CHAR,		_RANGE_ALL,					_RANGE_ACTIVE_CHAR);
			p->showTems					= iValidateRange(tlShowTems,				_NO,					_YES,						_YES);
			p->temsType					= iValidateRange(tnTemsType,				_TEMS_TRACK,			_TEMS_DISPLAY,				_TEMS_TRACK);
			p->showSplines				= iValidateRange(tlShowSplines,				_NO,					_YES,						_YES);
			p->splinesType				= iValidateRange(tnSplinesType,				_SPLINES_FILL,			_SPLINES_LOR,				_SPLINES_FILL);
			p->highlighSectionOnFinal	= iValidateRange(tlHighlighSectionOnFinal,	_NO,					_YES,						_YES);
			p->showPenDowns				= iValidateRange(tlShowPenDowns,			_NO,					_YES,						_NO);
			p->showMouseCrosshairs		= iValidateRange(tlShowMouseCrosshairs,		_NO,					_YES,						_YES);
			p->invert					= iValidateRange(tlInvert,					_NO,					_YES,						_NO);
			p->zoomLens					= iValidateRange(tlZoomLens,				_NO,					_YES,						_NO);
			p->selectArea				= iValidateRange(tnSelectArea,				_SELECT_AREA_SMALL,		_SELECT_AREA_EXTRA_LARGE,	_SELECT_AREA_SMALL);


		//////////
		// Force a re-render (whether we need one or not. :-))
		//////
			for (lnI = 0; lnI < p->hwnds->populatedLength; lnI += sizeof(SHwnd))
			{
				// Grab the pointer
				h = (SHwnd*)(p->hwnds->data + lnI);

				// If it's a markup window, re-render it
				PostMessage(h->hwndParent, WM_REDRAW_WINDOW, (u32)p, (u32)h->hwnd);
			}


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to indicate the user wants to make active another character for editing
//
//////
	int dsf_set_active_character(u32 tnInstance, u32 tiid)
	{
		SInstance*	p;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Make sure that character is defined
		/////
			if (tiid * sizeof(SChars) < p->chars->populatedLength)
			{
				// It exists
				p->activeChar = tiid;
				return(0);

			} else {
				// Invalid character range
				return(-2);
			}
	}




//////////
//
// Called to render a markup form used for editing, or for debugging, at the indicated size.  This
// is what the font looks like in the edit window of the DSF Font Editor.
//
//////
	int dsf_render_markup(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY)
	{
		SInstance*	p;
		SHwnd*		h;
		SChars*		thisChar;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Find the active character instance
		//////
			thisChar = iiFindOnlyThisChars(p->chars, p->activeChar);
			if (!thisChar)
				return(-2);		// Error finding (an invalid combination was provided)


		//////////
		// Determine where we will update our bitmap
		//////
			h = iFindOrCreateHwnd(p->hwnds, tnHwnd, tnX, tnY, tnWidth, tnHeight, true);
			if (!h)
				return(-3);


		//////////
		// Render it
		//////
			h->markup			= true;
			h->bold				= tlBold;
			h->italic			= tlItalic;
			h->underline		= tlUnderline;
			h->strikethrough	= tlStrikethrough;
			return(iRender(p, h, thisChar, tnWidth, tnHeight, tnHwnd, tnX, tnY));
	}




//////////
//
// Called to render a final form at the indicated size.  This is what the font will look like when
// generated for regular use by the system.
//
//////
	int dsf_render_final(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY)
	{
		SInstance*	p;
		SHwnd*		h;
		SChars*		thisChar;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Find the active character instance
		//////
			thisChar = iiFindOnlyThisChars(p->chars, p->activeChar);
			if (!thisChar)
				return(-2);		// Error finding (an invalid combination was provided)


		//////////
		// Determine where we will update our bitmap
		//////
			h = iFindOrCreateHwnd(p->hwnds, tnHwnd, tnX, tnY, tnWidth, tnHeight, false);
			if (!h)
				return(-3);


		//////////
		// Render it
		//////
			h->markup			= false;
			h->bold				= tlBold;
			h->italic			= tlItalic;
			h->underline		= tlUnderline;
			h->strikethrough	= tlStrikethrough;
			return(iRender(p, h, thisChar, tnWidth, tnHeight, tnHwnd, tnX, tnY));
	}




//////////
//
// Called to re-render a window that has been signaled that it needs re-rendering
//
//////
	int dsf_re_render(u32 tnInstance, u32 tnHwnd)
	{
		SInstance*	p;
		SChars*		thisChar;
		SHwnd*		h;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Find the active character instance
		//////
			thisChar = iiFindOnlyThisChars(p->chars, p->activeChar);
			if (!thisChar)
				return(-2);		// Error finding (an invalid combination was provided)


		//////////
		// See if we're found on this instance
		//////
			if (!IsWindow((HWND)tnHwnd))
				return(-2);		// Invalid window


		//////////
		// Search for it
		//////
			h = iFindOnlyHwndByHwnd(p->hwnds, (u32)GetParent((HWND)tnHwnd), tnHwnd);
			if (h)		return(iRender(p, h, thisChar, h->w, h->h, tnHwnd, h->x, h->y));
			else		return(-3);
	}




/////////
//
// Called from DllMain() one time to initialize the DSF DLL.
//
//////
	void initialize(void)
	{
		f64			lfX, lfY, lfTheta, lfRadius, lfA, lfB, lfV1, lfV2;
//		SSpline*	s;
		bool		llPenDown;


		//////////
		// Initialize our global buffers
		/////
			builder_createAndInitialize(&instances, -1);
			builder_createAndInitialize(&placeholder, -1);


		//////////
		// Build an "i at the cross" for the placeholder (meaning " 'me' at the cross")
		//////
			// Cross
			iAddSplineFromToLR(placeholder, true,		0.4075,		0.975,		0.59,		0.975);
			iAddSplineFromToLR(placeholder, false,		0.4075,		0.05,		0.59,		0.05);
			iAddSplineFromToLR(placeholder, true,		0.045,		0.74,		0.955,		0.74);
			iAddSplineFromToLR(placeholder, false,		0.045,		0.62,		0.955,		0.62);

			// "i" leg
			iAddSplineFromToLR(placeholder, true,		0.775,		0.435,		0.85,		0.485);
			iAddSplineFromToLR(placeholder, false,		0.7825,		0.425,		0.865,		0.47);
			iAddSplineFromToLR(placeholder, false,		0.7875,		0.415,		0.8775,		0.45);
			iAddSplineFromToLR(placeholder, false,		0.79,		0.405,		0.8875,		0.425);
			iAddSplineFromToLR(placeholder, false,		0.7925,		0.3975,		0.8925,		0.405);
			iAddSplineFromToLR(placeholder, false,		0.7925,		0.39,		0.895,		0.39);
			iAddSplineFromToLR(placeholder, false,		0.7925,		0.14,		0.895,		0.14);
			iAddSplineFromToLR(placeholder, false,		0.795,		0.125,		0.895,		0.13);
			iAddSplineFromToLR(placeholder, false,		0.80,		0.105,		0.8975,		0.12);
			iAddSplineFromToLR(placeholder, false,		0.81,		0.08,		0.90,		0.1125);
			iAddSplineFromToLR(placeholder, false,		0.825,		0.06,		0.905,		0.1);
			iAddSplineFromToLR(placeholder, false,		0.8375,		0.0425,		0.915,		0.095);

			// "i" dot
			lfX			= 0.765;
			lfY			= 0.5225;
			lfA			= 0.1325 / 2.0;
			lfB			= 0.0925 / 2.0;
			llPenDown	= true;
			for (lfTheta = 0.0; lfTheta <= _PI + 0.001; lfTheta += _PI / 10.0)
			{
				// Given:  a=major, b=minor, r=radius
				//         r = (a*b) / sqrt(b*cos(theta)^2 + a*sin(theta)^2)
				lfV1		= lfB * cos(lfTheta);
				lfV2		= lfA * sin(lfTheta);
				lfRadius	= (lfA * lfB) / sqrt(lfV1*lfV1 + lfV2*lfV2);
				iAddSplineCenterThetaRadiusLR(placeholder, llPenDown, lfX, lfY, lfRadius, iAdjustTheta(_2PI - lfTheta), lfTheta);
				llPenDown = false;
			}
	}




//////////
//
// Adds a new spline to the builder, computing its components based on a straight line from L to R.
//
//////
	SSpline* iAddSplineFromToLR(SBuilder* b, bool tlPenDown, f64 tfXL, f64 tfYL, f64 tfXR, f64 tfYR)
	{
		SLineF64	line;
		SSpline*	s;


		//////////
		// Compute the line
		//////
			line.p1.x	= tfXL;
			line.p1.y	= tfYL;
			line.p2.x	= tfXR;
			line.p2.y	= tfYR;
			iComputeLine(&line);


		//////////
		// Add the midpoint as the spline, and use the slope of the line to determine the rotation.
		//////
			s = (SSpline*)builder_allocateBytes(b, sizeof(SSpline));
			if (s)
			{
				// Initialize everything
				memset(s, 0, sizeof(SSpline));

				// Populate
				s->ox	= line.mid.x;
				s->oy	= line.mid.y;
				s->ot	= line.theta;

				// Indicate the right and left side length (left and right theta is 0)
				s->lr	= line.length / 2.0f;
				s->lt	= _PI;
				s->rr	= s->lr;

				// Does this start a new pen stroke?
				s->lPenDown = tlPenDown;
			}
			return(s);
	}




//////////
//
// Adds a new spline to the builder, computing from the indicated x,y center, given a radius and
// two angles, first for L, then for R.  The line runs horizontally, which means from 0..1, which
// is from left to right in our system, as per the standard Quad 1 X,Y coordinate system.
//
//////
	SSpline* iAddSplineCenterThetaRadiusLR(SBuilder* b, bool tlPenDown, f64 tfX, f64 tfY, f64 tfRadius, f64 tfThetaL, f64 tfThetaR)
	{
		SSpline* s;


		//////////
		// Add the midpoint as the spline, and use the slope of the line to determine the rotation.
		//////
			s = (SSpline*)builder_allocateBytes(b, sizeof(SSpline));
			if (s)
			{
				// Initialize everything
				memset(s, 0, sizeof(SSpline));

				// Populate
				s->ox	= tfX;
				s->oy	= tfY;

				// Indicate the right and left side length (left and right theta is 0)
				s->lr	= tfRadius;
				s->lt	= tfThetaL;
				s->rr	= tfRadius;
				s->rt	= tfThetaR;

				// Does this start a new pen stroke?
				s->lPenDown = tlPenDown;
			}
			return(s);
	}




//////////
//
// Physically construct the indicated character.    It does this by sizing some known maximums, and
// generating the bitmap for our new characters using that size.  We migrate and center the bitmap
// onto the known maximum bitmap canvas, and then using scale the image down to the indicated size.
//
//		(1) "hKltfgpqy" + SPACE(1)
//		(2) "hKltfgpqy" + SPACE(1) + CHR(tnAscii)
//
// Then the second bitmap will be wider than the first, but otherwise identical.  That following
// portion is the part which is returned to the indicated filename.  An appropriate font size is
// used based on the height and width, with the final image generated being scaled to the
//
//////
	int iGetCharacterBitmap(int tnAscii, char* tcBitmapFilename, char* tcFontName, int tnHeight, int tnWidth)
	{
		int			lnWidth, lnHeight, lnMakeWidth;
		f64			lfH, lfV;
		HFONT		hfont;
		HDC			lhdc;
		HBITMAP		lhbmp2;
		RECT		lrc1, lrc2, lrcM, lrcW;
		SBGR*		bd2;
		char		mbuffer[] = "M";
		char		wbuffer[] = "W";
		char		buffer[] = "hKltfgpqy  \0";
		char		rawBuffer[_MAX_FNAME];


		//////////
		// Create the font
		//////
			lnHeight = -MulDiv(tnHeight, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);
			hfont = CreateFontA(lnHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, tcFontName);
			if (!hfont)
				return(-1);


		//////////
		// Generate the two bitmaps
		//////
			lhdc = CreateCompatibleDC(GetDC(GetDesktopWindow()));
			SelectObject(lhdc, hfont);
			buffer[sizeof(buffer) - 3] = 0;


		//////////
		// Determine sizes
		//////
			// Bitmap 1 (without the indicated character)
			SetRect(&lrc1, 0, 0, 0, 0);
			DrawTextA(lhdc, buffer, strlen(buffer), &lrc1, DT_CALCRECT);

			// Bitmap 2 (with the indicated character)
			buffer[sizeof(buffer) - 3] = (char)tnAscii;
			SetRect(&lrc2, 0, 0, 0, 0);
			DrawTextA(lhdc, buffer, strlen(buffer), &lrc2, DT_CALCRECT);

			// M
			SetRect(&lrcM, 0, 0, 0, 0);
			DrawTextA(lhdc, mbuffer, 1, &lrcM, DT_CALCRECT);

			// W
			SetRect(&lrcW, 0, 0, 0, 0);
			DrawTextA(lhdc, wbuffer, 1, &lrcW, DT_CALCRECT);

			// Compute width and height
			lnWidth		= lrc2.right  - lrc2.left;
			lnHeight	= lrc2.bottom - lrc2.top;
			lnMakeWidth	= max(lrcM.right - lrcM.left, lrcW.right - lrcW.left);


		//////////
		// Bitmap 2
		//////
			lhbmp2 = iCreateBitmap(lhdc, lnWidth, lnHeight, 1, 24, (void**)&bd2);
			SelectObject(lhdc, lhbmp2);
			FillRect(lhdc, &lrc2, (HBRUSH)GetStockObject(WHITE_BRUSH));
			DrawTextA(lhdc, buffer, strlen(buffer), &lrc2, DT_LEFT);


		//////////
		// Write out the portion that's different to a temporary file
		//////
			memset(rawBuffer, 0, sizeof(rawBuffer));
			memcpy(rawBuffer, tcBitmapFilename, min(strlen(tcBitmapFilename), sizeof(rawBuffer) - 1));
			rawBuffer[strlen(rawBuffer) - 1] = 'q';
			lnMakeWidth = iSaveBitmap(bd2, lnWidth, lnHeight, lrc1.right - lrc1.left, rawBuffer, lnMakeWidth);


		//////////
		// Release everything
		//////
			DeleteObject((HGDIOBJ)hfont);
			DeleteObject((HGDIOBJ)lhbmp2);
			DeleteDC(lhdc);


		//////////
		// Scale the generated image up to the indicated size
		//////
			lfH = (f64)tnWidth	/ (f64)lnMakeWidth;
			lfV = (f64)tnHeight	/ (f64)lnHeight;
			iScaleImage(rawBuffer, tcBitmapFilename, (f32)lfH, (f32)lfV);
			DeleteFileA(rawBuffer);


		//////////
		// Indicate success
		//////
			return(0);
	}

	int iSaveBitmap(SBGR* bgr, int tnWidth, int tnHeight, int tnLeft, char* tcBitmapFilename, int tnMakeWidth)
	{
		int					lnY, lnRowWidth, lnWritePels, lnCopyPels, lnOffset, lnCopyWidth;
		SBGR*				lbgr;
		SBGR*				lbgrBuffer;
		BITMAPFILEHEADER	lbh;
		BITMAPINFOHEADER	lbi;
		FILE*				lfh;


		//////////
		// Create the output bitmap header
		//////    This is a test
			memset(&lbh, 0, sizeof(lbh));
			lbh.bfType		= 'MB';
			lbh.bfOffBits	= sizeof(lbh) + sizeof(lbi);

			lnCopyWidth		= max(tnWidth - tnLeft, tnMakeWidth);
			lnRowWidth		= iComputeRowWidth(tnWidth);
 
			memset(&lbi, 0, sizeof(lbi));
			lbi.biSize		= sizeof(lbi);
			lbi.biWidth		= lnCopyWidth;
			lnCopyPels		= (tnWidth - tnLeft) * 3;
			lnWritePels		= iComputeRowWidth(lbi.biWidth);
			lbi.biHeight	= tnHeight;
			lbi.biPlanes	= 1;
			lbi.biBitCount	= 24;
			lbi.biSizeImage	= lnWritePels * tnHeight;
			lbi.biXPelsPerMeter = 3270;
			lbi.biYPelsPerMeter = 3270;

			lbh.bfSize		= sizeof(lbh) + sizeof(lbi) + lbi.biSizeImage;
			

		//////////
		// Get metrics for the incoming image, and create a buffer for each line
		//////
			lnOffset	= (lbi.biWidth - (tnWidth - tnLeft)) / 2;
			lbgrBuffer	= (SBGR*)malloc(lnWritePels);
			if (lbgrBuffer)
			{
			//////////
			// Write out the header
			//////
				lfh = fopen(tcBitmapFilename, "wb+");
				if (lfh)
				{
					fwrite(&lbh, 1, sizeof(lbh), lfh);
					fwrite(&lbi, 1, sizeof(lbi), lfh);


				//////////
				// Extract out the bitmap portions.
				// Bitmaps are stored in reverse order, so we can iterate normally down through
				//////
					for (lnY = 0; lnY < tnHeight; lnY++)
					{
						//////////
						// Compute the offset to this part
						//////
							lbgr = (SBGR*)((char*)bgr + (lnY * lnRowWidth) + (tnLeft * 3));


						//////////
						// Copy to our buffer row
						//////
							memset(lbgrBuffer, 255, lnWritePels);
							memcpy(lbgrBuffer + lnOffset, lbgr, lnCopyPels);


						//////////
						// Write this row
						//////
							fwrite(lbgrBuffer, 1, lnWritePels, lfh);
					}
					// When we get here, it's saved
					fclose(lfh);
				}
				// We're done
				free(lbgrBuffer);
			}
			// Indicate how wide it is
			return(lnCopyWidth);
	}

	int iComputeRowWidth(int tnWidth)
	{
		int lnWidth;


		lnWidth = tnWidth * 3;
		if (lnWidth % 4 == 0)
			return(lnWidth);

		// Increase the width
		lnWidth += (4 - (lnWidth % 4));
		return(lnWidth);
	}

	HBITMAP iCreateBitmap(HDC thdc, int tnWidth, int tnHeight, int tnPlanes, int tnBits, void**tbd)
	{
		BITMAPINFO bi;


		//////////
		// Create a new DIB
		//////
			memset(&bi, 0, sizeof(BITMAPINFO));
			bi.bmiHeader.biSize			= sizeof(bi.bmiHeader);
			bi.bmiHeader.biWidth		= tnWidth;
			bi.bmiHeader.biHeight		= tnHeight;
			bi.bmiHeader.biPlanes		= tnPlanes;
			bi.bmiHeader.biBitCount		= tnBits;


		//////////
		// Physically create the bitmap
		//////
			return(CreateDIBSection(thdc, &bi, DIB_RGB_COLORS, tbd, NULL, 0));
	}




//////////
//
// Find every outline point and create a list of the same.
//
//////
	struct SFloanPoint
	{
		f64	x;			// X coordinate of an X,Y pair
		f64	y;			// Y coordinate of an X,Y pair
	};

	int iGetFloanFromBitmap(u32 tnAscii, char* tcBitmapFilename, char* tcFloanFilename)
	{
		int					lnI, lnY, lnX, lnRowWidth, lnOldFloanCount, lnNewFloanCount;
		f64					lfGray, lfLastGray;
		SBGR*				lbgr;
		SBGR*				lbgrBuffer;
		BITMAPFILEHEADER	lbh;
		BITMAPINFOHEADER	lbi;
		FILE*				lfh;
		SBuilder*			floans;
		SBuilder*			floansCsv;
		SFloanPoint			point;
		SFloanPoint*		pDst;
		SFloanPoint*		pSrc;
		s8					buffer[256];


		//////////
		// Open the indicated bitmap
		//////
			lfh = fopen(tcBitmapFilename, "rb");
			if (!lfh)
				return(-1);		// File does not exist


		//////////
		// Read in the header
		//////
			fread(&lbh, 1, sizeof(lbh), lfh);
			fread(&lbi, 1, sizeof(lbi), lfh);


		//////////
		// Make sure it's a sane bitmap
		//////
			if (lbh.bfSize != sizeof(lbh) + sizeof(lbi) + lbi.biSizeImage)
			{
				fclose(lfh);
				return(-2);				// Invalid header
			}
			if (lbi.biSize != sizeof(lbi))
			{
				fclose(lfh);
				return(-3);				// Invalid info
			}
			if (lbi.biPlanes != 1 || lbi.biBitCount != 24)
			{
				fclose(lfh);
				return(-4);				// Invalid bitmap style/format
			}
			lnRowWidth = iComputeRowWidth(lbi.biWidth);
			if (lnRowWidth * lbi.biHeight != lbi.biSizeImage)
			{
				fclose(lfh);
				return(-5);				// Invalid size
			}


		//////////
		// Load in the data
		//////
			lbgrBuffer = (SBGR*)malloc(lbi.biSizeImage);
			if (!lbgrBuffer)
			{
				fclose(lfh);
				return(-6);				// Out of memory
			}
			fread(lbgrBuffer, 1, lbi.biSizeImage, lfh);
			fclose(lfh);


		//////////
		// Increase contrast to full
		//////
			for (lnY = 0; lnY < lbi.biHeight; lnY++)
			{
				// Iterate all the way across
				lbgr = (SBGR*)((char*)lbgrBuffer + (lnY * lnRowWidth));

				// Look for where things start or stop
				for (lnX = 0; lnX < lbi.biWidth; lnX++, lbgr++)
				{
					// Determine the grayscale value of this pixel
					lfGray = (((f64)lbgr->red * 0.35f) + ((f64)lbgr->grn * 0.54f) + ((f64)lbgr->blu * 0.11f)) / 255.0f;

					// Is it visibly darkened?
					if (lfGray < 0.7f)
					{
						// Make it black
						lbgr->red = 0;
						lbgr->grn = 0;
						lbgr->blu = 0;

					} else {
						// Make it white
						lbgr->red = 255;
						lbgr->grn = 255;
						lbgr->blu = 255;
					}
				}
			}


		//////////
		// Initialize
		//////
			builder_createAndInitialize(&floans,	65536);
			builder_createAndInitialize(&floansCsv,	65536);


		//////////
		// Iterate through each row grabbing floan positions
		//////
			for (lnY = 0; lnY < lbi.biHeight; lnY++)
			{
				// Iterate all the way across
				lbgr = (SBGR*)((char*)lbgrBuffer + (lnY * lnRowWidth));

				// Look for where things start or stop
				lfLastGray = 1.0;		// Assume we start on a white pixel
				for (lnX = 0; lnX < lbi.biWidth; lnX++, lbgr++)
				{
					// Determine the grayscale value of this pixel
					lfGray = (((f64)lbgr->red * 0.35f) + ((f64)lbgr->grn * 0.54f) + ((f64)lbgr->blu * 0.11f)) / 255.0f;

					// Has something changed?
					if (fabs(lfGray - lfLastGray) > 0.9f)
					{
						// Store the position
						point.x = (f64)lnX	/ (f64)lbi.biWidth;
						point.y = (f64)lnY	/ (f64)lbi.biHeight;

						// Make sure it's on the reservation :-)
						if (point.x >= 0.0 && point.y >= 0.0)
							builder_appendData(floans, (s8*)&point, sizeof(point));

						// Prepare for our next test
						lfLastGray = lfGray;
					}
				}
			}


		//////////
		// Iterate through each column grabbing floan positions
		//////
			for (lnX = 0; lnX < lbi.biWidth; lnX++)
			{
				// Iterate point by point in vertical columns
				lbgr = (SBGR*)((char*)lbgrBuffer + (lnX * 3));

				// Look for where things start or stop
				lfLastGray = 1.0;		// Assume we start on a white pixel
				for (lnY = 0; lnY < lbi.biHeight; lnY++)
				{
					// Determine the grayscale value of this pixel
					lfGray = (((f64)lbgr->red * 0.35f) + ((f64)lbgr->grn * 0.54f) + ((f64)lbgr->blu * 0.11f)) / 255.0f;

					// Has something changed?
					if (fabs(lfGray - lfLastGray) > 0.9f)
					{
						// Store the position
						point.x = (f64)lnX	/ (f64)lbi.biWidth;
						point.y = (f64)lnY	/ (f64)lbi.biHeight;

						// Make sure it's on the reservation :-)
						if (point.x >= 0.0 && point.y >= 0.0)
							builder_appendData(floans, (s8*)&point, sizeof(point));

						// Prepare for our next test
						lfLastGray = lfGray;
					}

					// Move to next row on same column
					lbgr = (SBGR*)((s8*)lbgr + lnRowWidth);
				}
			}


		//////////
		// Sort the data in Y order ascending, then X ascending
		//////
			lnOldFloanCount = floans->populatedLength / sizeof(SFloanPoint);
			qsort(floans->data, lnOldFloanCount, sizeof(SFloanPoint), iiGetFloanFromBitmap_qsortCallback);


		//////////
		// Wash disparate data points
		//////
// TODO: The idea is to grab the points closest to each point, and then average to use the middle, rather than the integer alias


		//////////
		// Remove duplicates
		//////
			// Begin at the beginning
			pDst = (SFloanPoint*)floans->data;
			pSrc = pDst + 1;
			for (lnI = 1, lnNewFloanCount = 0; lnI < lnOldFloanCount; lnI++, pSrc++)
			{
				//////////
				// Is this one different?
				//////
					if (pDst->y != pSrc->y || pDst->x != pSrc->x)
					{
						// Yes, advance our destination pointer
						++pDst;

						// If we're not overwriting our pointer, then copy
						if (pDst != pSrc)
							memcpy(pDst, pSrc, sizeof(SFloanPoint));

						// Increase our count
						++lnNewFloanCount;
					}
			}


		//////////
		// Resize (floans are already in correct order)
		//////
			builder_setSize(floans, lnNewFloanCount * sizeof(SFloanPoint));


		//////////
		// Copy to our CSV
		//////
			pSrc = (SFloanPoint*)floans->data;
			for (lnI = 0; lnI < lnNewFloanCount; lnI++, pSrc++)
			{
				// Store the output
				sprintf(buffer, "%15.12f, %15.12f\n\0", pSrc->x, pSrc->y);

				// Append it to the builder
				builder_appendData(floansCsv, buffer, strlen(buffer));
			}
			builder_asciiWriteOutFile(floansCsv, tcFloanFilename);


		//////////
		// For debugging, populate the individual found points within the bitmap in green, and write it back out
		//////
			int					lnRowWidth_debug;
			SBGR*				lbgrBuffer_debug;
			BITMAPFILEHEADER	lbh_debug;
			BITMAPINFOHEADER	lbi_debug;
			FILE*				lfh_debug;

			memcpy(&lbh_debug, &lbh, sizeof(lbh));
			memcpy(&lbi_debug, &lbi, sizeof(lbi));

			lbi_debug.biWidth		= 400;
			lbi_debug.biHeight		= 400;
			lnRowWidth_debug		= iComputeRowWidth(lbi_debug.biWidth);
			lbi_debug.biSizeImage	= lnRowWidth_debug * lbi_debug.biHeight;
			lbh_debug.bfSize		= sizeof(lbh_debug) + sizeof(lbi_debug) + lbi_debug.biSizeImage;
			lbgrBuffer_debug		= (SBGR*)malloc(lbi_debug.biSizeImage);
			memset(lbgrBuffer_debug, 255, lbi_debug.biSizeImage);

			pSrc = (SFloanPoint*)floans->data;
			for (lnI = 0; lnI < lnNewFloanCount; lnI++, pSrc++)
			{
				// Re-acquire our position
				lnX = (s32)(pSrc->x * (f64)lbi_debug.biWidth);
				lnY = (s32)(pSrc->y * (f64)lbi_debug.biHeight);

				// Store it
				lbgr = (SBGR*)((s8*)lbgrBuffer_debug + (lnY * lnRowWidth_debug) + (lnX * 3));

				// Make it black
				lbgr->red	= 0;
				lbgr->grn	= 0;
				lbgr->blu	= 0;
			}
			char filename[_MAX_FNAME];
			sprintf(filename, "ascii_%03u.bmp\0", tnAscii);
			lfh_debug = fopen(filename, "wb+");
			fwrite(&lbh_debug, 1, sizeof(lbh_debug), lfh_debug);
			fwrite(&lbi_debug, 1, sizeof(lbi_debug), lfh_debug);
			fwrite(lbgrBuffer_debug, 1, lbi_debug.biSizeImage, lfh_debug);
			fclose(lfh_debug);
//			_asm nop;
//			DeleteFileA(filename);


		//////////
		// Clean house
		//////
			builder_freeAndRelease(&floans);
			builder_freeAndRelease(&floansCsv);


		//////////
		// Indicate our success
		//////
			return(lnNewFloanCount);
	}




//////////
//
// QSORT() callback, orders data by Y ascending, then by X ascending.
//
//////
	int iiGetFloanFromBitmap_qsortCallback(const void* l, const void* r)
	{
		SFloanPoint*	left;
		SFloanPoint*	right;


		// Get our pointers properly
		left	= (SFloanPoint*)l;
		right	= (SFloanPoint*)r;

		// See how the cookie crumbles
		     if (left->y < right->y)		return(-1);		// Left is less than right
		else if (left->y > right->y)		return(1);		// Left is greater than right
		else if (left->x < right->x)		return(-1);		// Left is less than right
		else if (left->x > right->x)		return(1);		// Left is greater than right
		else								return(0);		// They're equal
	}




//////////
//
// Called to verify if the indicated handle is valid
//
//////
	SInstance* iGetDsfInstance(u32 tnHandle, bool* tlValid)
	{
		union {
			SInstance*	p;
			u32			_p;
		};


		//////////
		// Make sure our environment is sane, and if so that the handle is valid
		//////
			_p = tnHandle;

			// Is it a pointer?
			if (p)
			{
				// Is it in range?
				if (_p >= instances->_data && _p <= instances->_data + instances->populatedLength)
				{
					// Is it identical?
					if (_memicmp(p->id, cgcDsfBrand, sizeof(p->id)) == 0 && p->id_size == sizeof(SInstance))
					{
						// Valid
						*tlValid = true;
						return(p);
					}
				}
			}

			// Invalid
			*tlValid = false;
			return(NULL);
	}




//////////
//
// Called to search through the character splines, definition entries, links, etc., to find the
// matching character reference.
//
//////
	SSpline* iFindSplineInstance(SBuilder* charsBuilder, u32 tnIid, u8 tcType, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder)
	{
		SChars*		thisChar;
		SBuilder*	thisSplineBuilder;


		//////////
		// Make sure our environment is sane
		//////
			if (charsBuilder && charsBuilder->data)
			{
				// Grab that builder
				thisChar = iiFindOrCreateThisChars(charsBuilder, tnIid);
				if (!thisChar)
					return(NULL);

				// Grab this character's builder for splines/definitions
				thisSplineBuilder = thisChar->splines;

				// Find out what type this one is
				switch (tcType)
				{
					case 'S':
					case 's':
						// It's a spline, which is part of the indicated item
						// We search by tnIid and tiOrder
						if (tnIid > 255)
							return(NULL);		// Invalid spline reference

						// Search for (and add it if need be)
						return(iFindSplineInstance_SD(thisSplineBuilder, tnIid, tiOrder, true));


					case 'D':
					case 'd':
						// It's the same as a spline, but the definition must be an item above 255, and it's
						// not part of a character, but rather just a segment to be used by characters.
						// We search by tnIid and tiOrder
						if (tnIid <= 255)
							return(NULL);		// Error

						// Search for (and add it if need be)
						return(iFindSplineInstance_SD(thisSplineBuilder, tnIid, tiOrder, true));


					case 'R':
					case 'r':
						// It's a reference. The reference must refer to an item above 255, per tiLnkId
						// We search by tnIid, tiOrder, and tiLnkId
						if (tnIid < 256)
							return(NULL);		// Error

						// Search for (and add it if need be)
						return(iFindSplineInstance_R(thisSplineBuilder, tnIid, tiOrder, tiLnkId, true));


					case 'L':
					case 'l':
						// It's a link. The reference can refer to any item, but must include the tiLnkId and tiLnkOrder
						// We search by tnIid, tiOrder, tiLnkId, and tiLnkOrder

						// Search for (and add it if need be)
						return(iFindSplineInstance_L(thisSplineBuilder, tnIid, tiOrder, tiLnkId, tiLnkOrder, true));

				}
			}


		// If we get here, not found
		return(NULL);
	}

	SChars* iiFindOrCreateThisChars(SBuilder* charsBuilder, u32 tnIid)
	{
		u32			lnI, lnStart, lnEnd;
		SChars*		thisChar;


		// See if there's already room for this item
		if (charsBuilder->populatedLength < tnIid * sizeof(SChars))
		{
			// We have to make room for it
			lnStart = (charsBuilder->populatedLength / sizeof(SChars));
			lnEnd	= tnIid * sizeof(SChars);
			for (lnI = lnStart; lnI <= lnEnd; lnI += sizeof(SChars))
			{
				// Grab the pointer
				thisChar = (SChars*)builder_allocateBytes(charsBuilder, sizeof(SChars));

				// Initialize it
				memset(thisChar, 0, sizeof(SChars));

				// Create new builders for it
				builder_createAndInitialize(&thisChar->splines,		-1);
				builder_createAndInitialize(&thisChar->temsRaw,		-1);
				builder_createAndInitialize(&thisChar->tems,		-1);
				builder_createAndInitialize(&thisChar->temsLines,	-1);
			}
		}


		//////////
		// Return the builder
		//////
			return(iiFindOnlyThisChars(charsBuilder, tnIid));
	}

	SChars* iiFindOnlyThisChars(SBuilder* charsBuilder, u32 tnIid)
	{
		if (charsBuilder->populatedLength >= tnIid * sizeof(SChars))
		{
			// There is enough room for this character to exist
			return((SChars*)(charsBuilder->data + (tnIid * sizeof(SChars))));

		} else {
			// Something's awry
			return(NULL);
		}
	}

	SSpline* iFindSplineInstance_SD(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, bool tlAddIfNotFound)
	{
		u32			lnI;
		SSpline*	s;


		//////////
		// Make sure our environment is sane
		//////
			if (!thisSplineBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisSplineBuilder->populatedLength; lnI += sizeof(SSpline))
			{
				// Grab the pointer
				s = (SSpline*)(thisSplineBuilder->data + lnI);

				// See if this is it
				if (s->iid == tnIid && s->iOrder == tiOrder)
					return(s);
			}


		//////////
		// If we get here, it wasn't found
		//////
			if (tlAddIfNotFound)
			{
				// Create a new entry
				return((SSpline*)builder_allocateBytes(thisSplineBuilder, sizeof(SSpline)));

			} else {
				// 
				return(NULL);
			}
	}

	SSpline* iFindSplineInstance_R(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, bool tlAddIfNotFound)
	{
		u32			lnI;
		SSpline*	s;


		//////////
		// Make sure our environment is sane
		//////
			if (thisSplineBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisSplineBuilder->populatedLength; lnI += sizeof(SSpline))
			{
				// Grab the pointer
				s = (SSpline*)(thisSplineBuilder->data + lnI);

				// See if this is it
				if (s->iid == tnIid && s->iOrder == tiOrder && s->iLnkId == tiLnkId)
					return(s);
			}


		//////////
		// If we get here, it wasn't found
		//////
			if (tlAddIfNotFound)
			{
				// Create a new entry
				return((SSpline*)builder_allocateBytes(thisSplineBuilder, sizeof(SSpline)));

			} else {
				// 
				return(NULL);
			}
	}

	SSpline* iFindSplineInstance_L(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder, bool tlAddIfNotFound)
	{
		u32			lnI;
		SSpline*	s;


		//////////
		// Make sure our environment is sane
		//////
			if (thisSplineBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisSplineBuilder->populatedLength; lnI += sizeof(SSpline))
			{
				// Grab the pointer
				s = (SSpline*)(thisSplineBuilder->data + lnI);

				// See if this is it
				if (s->iid == tnIid && s->iOrder == tiOrder && s->iLnkId == tiLnkId && s->iLnkOrder == tiLnkOrder)
					return(s);
			}


		//////////
		// If we get here, it wasn't found
		//////
			if (tlAddIfNotFound)
			{
				// Create a new entry
				return((SSpline*)builder_allocateBytes(thisSplineBuilder, sizeof(SSpline)));

			} else {
				// 
				return(NULL);
			}
	}




//////////
//
// Called to search through the existing refs entry to see if the indicated reference is found
//
//////
	SRefs* iFindRefsInstance(SBuilder* refs, u8 tcType, s8* tcDesc40)
	{
		s32		lnI, lnMaxCount;
		SRefs*	r;


		//////////
		// Make sure our environment is sane
		//////
			if (refs && refs->data && refs->populatedLength >= sizeof(SRefs))
			{
				// Get our starting and ending points
				lnMaxCount	= refs->populatedLength / sizeof(SRefs);
				r			= (SRefs*)refs->data;

				// Iterate through every ref
				for (lnI = 0; lnI < lnMaxCount; lnI++, r++)
				{
					// Is this it?
					if (r->cType == tcType && _memicmp(r->cDesc, tcDesc40, 40) == 0)
						return(r);		// Found it
				}
				// If we get here, not found
			}


		// If we get here, not found
		return(NULL);
	}




//////////
//
// Called to create a new templates entry as template data is being initially loaded
//
//////
	STems* iCreateNewTemsEntry(SBuilder* charsBuilder, u32 tipid)
	{
		SChars*		thisChars;
		STems*		t;


		//////////
		// Grab the thisChars parent
		//////
			thisChars = iiFindOrCreateThisChars(charsBuilder, tipid);
			if (thisChars)
			{
				// Allocate and return the new template
				t = (STems*)builder_allocateBytes(thisChars->temsRaw, sizeof(STems));

				// Initialize the memory
				if (t)
					memset(t, 0, sizeof(STems));

				// Indicate our pointer
				return(t);

			} else {
				// Failure
				return(NULL);
			}
	}




//////////
//
// Locate the indicated tems for the associated thisChars
//
//////
	SBuilder* iGetTemsRawBuilder(SBuilder* charsBuilder,u32 tipid)
	{
		SChars*		thisChars;


		//////////
		// Grab the thisChars parent
		//////
			thisChars = iiFindOnlyThisChars(charsBuilder, tipid);
			if (thisChars)
			{
				// Return the template
				return(thisChars->temsRaw);

			} else {
				// Failure
				return(NULL);
			}
	}




//////////
//
// Called to render the indicated character
//
//////
	int iRender(SInstance* p, SHwnd* h, SChars* c, s32 tnWidth, s32 tnHeight, u32 tnHwndParent, s32 tnX, s32 tnY)
	{
		RECT lrc;


		//////////
		// Render the character window
		//////
			SetRect(&lrc, 0, 0, h->w, h->h);
			if (p->activeChar < 0)
			{
				// No valid character has been specified
				FillRect(h->hdc, &lrc, h->backDarkGrayBrush);

			} else {
				// An active character exists, render it
				if (h->markup != 0)
				{
					// Fill with the dark background for markup editing
					FillRect(h->hdc, &lrc, h->backDarkGrayBrush);

					// Render the splines withmarkup
					if (p->showSplines)
						iRenderSplines(p, h, c, h->markup, h->bold, h->italic, h->underline, h->strikethrough);

					// Render the mouse coordinates, tems, and mouse overlay info
					iRenderMouseCoordinates(p, h);

					if (p->showTems)
						iRenderTems(p, h, c);

					// Render the mouse overlay for current mouse activity
					iRenderMouseOverlay(p, h, c);

				} else {
					// Render final as black text on a white background
					FillRect(h->hdc, &lrc, (HBRUSH)GetStockObject(WHITE_BRUSH));
					iRenderSplines(p, h, c, h->markup, h->bold, h->italic, h->underline, h->strikethrough);
				}
			}


		//////////
		// 
		//////
			if (p->zoomLens)
				iRenderZoomLens(h);


		//////////
		// Invert
		//////
			if (p->invert)
				iInvertImage(h);	// Invert the colors


		//////////
		// Redraw after the rendering
		//////
			if (h->_hwnd)
			{
// 				SetRect(&lrc, 0, 0, 10000, 10000);
// 				if (IsWindow(h->hwndParent))
// 					InvalidateRect(h->hwndParent, &lrc, TRUE);

				SetRect(&lrc, 0, 0, h->w, h->h);
				if (IsWindow(h->hwnd))
					InvalidateRect(h->hwnd, &lrc, TRUE);	
			}


		// Indicate the hwnd handle we rendered
		return(h->_hwnd);
	}




//////////
//
// Called to put the mouse coordinates in the lower-right
//
//////
	void iRenderMouseCoordinates(SInstance* p, SHwnd* h)
	{
		RECT	lrcX, lrcY;
		s8		bufferX[32];
		s8		bufferY[32];


		// Only draw the coordinates if we're on the area
		if (gMouse.xi >= 0 && gMouse.xi < h->w && gMouse.yi >= 0 && gMouse.yi < h->h)
		{
			// Setup the font
			SelectObject(h->hdc, h->fontXY);
			SetBkMode(h->hdc, TRANSPARENT);
			SetTextColor(h->hdc, RGB(255,255,255));

			// Get our coordinates
			sprintf(bufferX, "X:%6.4lf\0", (f32)gMouse.xi			/ (f32)h->w);
			sprintf(bufferY, "Y:%6.4lf\0", ((f32)(h->h - gMouse.yi) / (f32)h->h));		// Invert mouse Y coordinate for the calculation

			// Find out how big it is
			SetRect(&lrcX, 0, 0, 0, 0);
			SetRect(&lrcY, 0, 0, 0, 0);
			DrawTextA(h->hdc, bufferX, strlen(bufferX), &lrcX, DT_CALCRECT);
			DrawTextA(h->hdc, bufferY, strlen(bufferY), &lrcY, DT_CALCRECT);

			// Determine the actual rendering coordinates
			SetRect(&lrcY, h->w - 3 - (lrcY.right - lrcY.left), h->h - 3 - (lrcY.bottom - lrcY.top), h->w - 3, h->h - 3);
			SetRect(&lrcX, h->w - 3 - (lrcY.right - lrcY.left) - 3 - (lrcX.right - lrcX.left), h->h - 3 - (lrcX.bottom - lrcX.top), lrcY.left - 3, lrcY.bottom);

			// Render
			DrawTextA(h->hdc, bufferX, strlen(bufferX), &lrcX, DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS);
			DrawTextA(h->hdc, bufferY, strlen(bufferY), &lrcY, DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS);
		}
	}




//////////
//
// Called to render the indicated splines onto the character
//
//////
	void iRenderSplines(SInstance* p, SHwnd* h, SChars* c, u32 tlMarkup, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough)
	{
		u32			lnI, lnSplineNumber;
		SXYF64		prLast, poLast, plLast;
		SXYF64		pr, po, pl, p1, p2, p3, p4;
		SLineF64	line, lineL, lineR, lineLLast, lineRLast, lineLtoLLast, lineRtoRLast;
		SSpline*	s;
		SSpline*	sLast;
		SBuilder*	b;
		SBGR		colorLine;
		SBGR		quad, quadSelected, p1ColorR, p2ColorR, p3ColorR, p4ColorR, p1ColorL, p2ColorL, p3ColorL, p4ColorL;


		//////////
		// For new characters or definitions there may not yet be any splines.  We use a placeholder
		// drawn onto the character until such time
		/////
			// Draw a placeholder (used for debugging)
			if (c->splines->populatedLength <= sizeof(SSpline))		b = placeholder;//	return;		// Return (optionally, the the placeholder could be drawn)
			else													b = c->splines;					// Draw the character splines

			// Determine the colors
			// Fill area
			if (tlMarkup == 0)
			{
				// It is a final render, black on white
				quad			= black;
				if (p->highlighSectionOnFinal)			quadSelected	= blackSelected;
				else									quadSelected	= black;

			} else {
				// It is a markup render, gray on black
				if (p->splinesType == _SPLINES_FILL)
				{
					// Normal rendering
					quad			= gray;
					quadSelected	= graySelected;

				} else {
					// Outline or LOR rendering
					quad			= background;
					quadSelected	= backgroundSelected;
				}
			}

			// Splines
			if (p->splinesType != _SPLINES_FILL)					colorLine = gray;				// They don't want to see it filled in, so make it a little more visible
			else													colorLine = black;				// They want to see it filled in, so it can be black


		//////////
		// Iterate through each spline
		//////
			sLast = NULL;
			for (lnI = 0; lnI < b->populatedLength; lnI += sizeof(SSpline))
			{
				// Grab the pointer
				s = (SSpline*)(b->data + lnI);

				// There are negative values which store meta data
				if (s->iOrder >= 0)
				{
					//////////
					// Compute left, origin/middle, right
					//////
						iComputeLOR(s, &pl, &po, &pr);


					//////////
					// Connect the last points to the new points
					//////
						if (!s->lPenDown)
						{
							// Colors are determined by their relative point's selected color
							iComputeQuadColorsR(s, sLast, quad, quadSelected, &p1ColorR, &p2ColorR, &p3ColorR, &p4ColorR);
							iComputeQuadColorsL(s, sLast, quad, quadSelected, &p1ColorL, &p2ColorL, &p3ColorL, &p4ColorL);

							// Draw in filled in final mode, or when the user wants to see it in markup mode
							// Lines are drawn p1..p4, p2..p3 using the following form:
							// iFillQuad(h, &p1, &p2, &p3, &p4, p1Color, p2Color, p3Color, p4Color);
							iFillQuadAlpha(h, /*p1*/&prLast, /*p2*/&pr, /*p3*/&po, /*p4*/&poLast, p1ColorR, p2ColorR, p3ColorR, p4ColorR, 1.0, 1.0, 1.0, 1.0);
							iFillQuadAlpha(h, /*p1*/&poLast, /*p2*/&po, /*p3*/&pl, /*p4*/&plLast, p1ColorL, p2ColorL, p3ColorL, p4ColorL, 1.0, 1.0, 1.0, 1.0);
						}


					//////////
					// Setup for the next stroke
					//////
						iCopyPoint(&prLast, &pr);
						iCopyPoint(&poLast, &po);
						iCopyPoint(&plLast, &pl);
						sLast = s;
				}
			}


		//////////
		// Overlay markup drawing
		//////
			if (tlMarkup != 0)
			{
				for (lnI = 0, lnSplineNumber = 0; lnI < b->populatedLength; lnI += sizeof(SSpline))
				{
					// Grab the pointer
					s = (SSpline*)(b->data + lnI);

					// There are negative values which store meta data
					if (s->iOrder >= 0)
					{
						//////////
						// Compute left, origin/middle, right
						//////
							iComputeLOR(s, &pl, &po, &pr);


						//////////
						// Indicate the spline number
						//////
							if (s->lPenDown)		lnSplineNumber = 0;
							else					++lnSplineNumber;


						//////////
						// If this is the start of a new stroke, render the indicator
						//////
							if (p->showPenDowns)
							{
								//////////
								// For pendown strokes, render the large indicator
								//////
									if (s->lPenDown)
									{
										// Compute the line from L to R
										iComputeLineFromTwoPoints(&line, &pl, &pr);

										/////////
										// Extend out the points by 5 pixels
										//////
											// L
											line.p1.x	= line.p1.x + ((5.0 / (f64)h->w) * cos(line.theta + _PI));
											line.p1.y	= line.p1.y + ((5.0 / (f64)h->h) * sin(line.theta + _PI));
											// R
											line.p2.x	= line.p2.x + ((5.0 / (f64)h->w) * cos(line.theta));
											line.p2.y	= line.p2.y + ((5.0 / (f64)h->h) * sin(line.theta));
											iComputeLine(&line);


										//////////
										// Create a quad extending out 5 pixels behind, 10 pixels in front
										//////
											// p1..p4
											p1.x		= line.p1.x + ((10.0 / (f64)h->w) * cos(line.theta - _PI_2));
											p1.y		= line.p1.y + ((10.0 / (f64)h->h) * sin(line.theta - _PI_2));
											p4.x		= line.p1.x + ((5.0 / (f64)h->w) * cos(line.theta + _PI_2));
											p4.y		= line.p1.y + ((5.0 / (f64)h->h) * sin(line.theta + _PI_2));
											// p2..p3
											p2.x		= line.p2.x + ((10.0 / (f64)h->w) * cos(line.theta - _PI_2));
											p2.y		= line.p2.y + ((10.0 / (f64)h->h) * sin(line.theta - _PI_2));
											p3.x		= line.p2.x + ((5.0 / (f64)h->w) * cos(line.theta + _PI_2));
											p3.y		= line.p2.y + ((5.0 / (f64)h->h) * sin(line.theta + _PI_2));


										//////////
										// Fill this quad in using a pastel pink cue
										//////
											iFillQuadAlpha(h, &p1, &p2, &p3, &p4, stroke, stroke, stroke, stroke, 0.0, 0.0, 0.7, 0.7);
									}


								//////////
								// For all splines after the second, render hint arrows
								//////
									if (lnSplineNumber >= 1)
									{
										// Compute the line from L to O and O to R on both the current and the last points
										iComputeLineFromTwoPoints(&lineL, &pl, &po);
										iComputeLineFromTwoPoints(&lineR, &po, &pr);
										iComputeLineFromTwoPoints(&lineLLast, &plLast, &poLast);
										iComputeLineFromTwoPoints(&lineRLast, &poLast, &prLast);

										// Compute a line from the midpoints forward
										iComputeLineFromTwoPoints(&lineLtoLLast, &lineLLast.mid, &lineL.mid);
										iComputeLineFromTwoPoints(&lineRtoRLast, &lineRLast.mid, &lineR.mid);

										// Build quads around the endpoints
										if (lineL.length * (f64)h->w >= 9.0)
											iRenderHint(h, &lineLtoLLast, &lineLtoLLast.p1);			// There's enough room to draw a hint on the left side

										if (lineR.length * (f64)h->w >= 9.0)
											iRenderHint(h, &lineRtoRLast, &lineRtoRLast.p1);			// There's enough room to draw a hint on the right side
									}
							}


						//////////
						// Render this spline onto the bitmap
						//////

							// Connect the last points to the new points
							if (!s->lPenDown)
							{
								// Connect left, right as markup lines
								if (p->splinesType == _SPLINES_FILL || p->splinesType == _SPLINES_OUTLINE)
								{
									iDrawLine(h, &pr, &prLast, s->tlRSelected ? colorSelected : colorLine, sLast->tlRSelected ? colorSelected : colorLine);
									iDrawLine(h, &po, &poLast, s->tlOSelected ? colorSelected : colorLine, sLast->tlOSelected ? colorSelected : colorLine);
									iDrawLine(h, &pl, &plLast, s->tlLSelected ? colorSelected : colorLine, sLast->tlLSelected ? colorSelected : colorLine);
								}
								iDrawPoints(h, &prLast, &poLast, &plLast, sLast, colorSelected, colorR, colorO, colorL, colorRSelected, colorOSelected, colorLSelected);

							} else {
								// Reset the spline count
								lnSplineNumber = 0;
							}

							// Connect left, middle, right as markup lines
							iDrawLine(h, &pr, &po, s->tlRSelected ? colorSelected : colorLine, s->tlOSelected ? colorSelected : colorLine);
							iDrawLine(h, &po, &pl, s->tlOSelected ? colorSelected : colorLine, s->tlLSelected ? colorSelected : colorLine);
							iDrawPoints(h, &pr, &po, &pl, s, colorSelected, colorR, colorO, colorL, colorRSelected, colorOSelected, colorLSelected);


						//////////
						// Setup for the next stroke
						//////
							iCopyPoint(&prLast, &pr);
							iCopyPoint(&poLast, &po);
							iCopyPoint(&plLast, &pl);
							sLast = s;
					}
				}
			}
	}

	void iRenderHint(SHwnd* h, SLineF64* line, SXYF64* pt)
	{
		SXYF64		pLeft;
		SXYF64		pForward;
		SXYF64		pRight;


		// Create line moving left, forward, and right from the end of the provided line
		pLeft.x		= pt->x + ((2.5 / (f64)h->w)  * cos(line->theta - _PI_2));
		pLeft.y		= pt->y + ((2.5 / (f64)h->w)  * sin(line->theta - _PI_2));

		pForward.x	= pt->x + ((6.0 / (f64)h->w)  * cos(line->theta));
		pForward.y	= pt->y + ((6.0 / (f64)h->w)  * sin(line->theta));

		pRight.x	= pt->x + ((2.5 / (f64)h->w)  * cos(line->theta + _PI_2));
		pRight.y	= pt->y + ((2.5 / (f64)h->w)  * sin(line->theta + _PI_2));

		// Draw the quad
		iFillQuadAlpha(h, &pLeft, &pForward, &pForward, &pRight, stroke, stroke, stroke, stroke, 1.0, 1.0, 1.0, 1.0);
	}

	void iComputeLOR(SSpline* s, SXYF64* pl, SXYF64* po, SXYF64* pr)
	{
		// left, origin/middle, right
		iSetPoint(pl,	s->ox + (s->lr * cos(s->ot + s->lt)),	s->oy + (s->lr * sin(s->ot + s->lt)));
		iSetPoint(po,	s->ox,									s->oy);
		iSetPoint(pr,	s->ox + (s->rr * cos(s->ot + s->rt)),	s->oy + (s->rr * sin(s->ot + s->rt)));
	}

	// Order is: prLast..poLast, pr..po, which are quad1from, quad1to, quad2from, quad2to
	// iFillQuad(h, /*p1*/&prLast, /*p2*/&pr, /*p3*/&po, /*p4*/&poLast, p1ColorR, p2ColorR, p3ColorR, p4ColorR);
	void iComputeQuadColorsR(SSpline* s, SSpline* sLast, SBGR quadNormal, SBGR quadSelected, SBGR* p1ColorR, SBGR* p2ColorR, SBGR* p3ColorR, SBGR* p4ColorR)
	{
		*p1ColorR	= ((sLast->tlRSelected)	? quadSelected : quadNormal);
		*p2ColorR	= ((s->tlRSelected)		? quadSelected : quadNormal);
		*p3ColorR	= ((s->tlOSelected)		? quadSelected : quadNormal);
		*p4ColorR	= ((sLast->tlOSelected)	? quadSelected : quadNormal);
	}

	// Order is: poLast..plLast, po..pl, which are quad1from, quad1to, quad2from, quad2to
	// iFillQuad(h, /*p1*/&poLast, /*p2*/&po, /*p3*/&pl, /*p4*/&plLast, quad1fromL, p1ColorL, p2ColorL, p3ColorL, p4ColorL);
	void iComputeQuadColorsL(SSpline* s, SSpline* sLast, SBGR quadNormal, SBGR quadSelected, SBGR* p1ColorL, SBGR* p2ColorL, SBGR* p3ColorL, SBGR* p4ColorL)
	{
		*p1ColorL	= ((sLast->tlOSelected)	? quadSelected : quadNormal);
		*p2ColorL	= ((s->tlOSelected)		? quadSelected : quadNormal);
		*p3ColorL	= ((s->tlLSelected)		? quadSelected : quadNormal);
		*p4ColorL	= ((sLast->tlLSelected)	? quadSelected : quadNormal);
	}

	void iDrawPoints(SHwnd* h, SXYF64* pr, SXYF64* po, SXYF64* pl, SSpline* s, SBGR colorSelected, SBGR colorR, SBGR colorO, SBGR colorL, SBGR colorRSelected, SBGR colorOSelected, SBGR colorLSelected)
	{
		//////////
		// Right
		//////
			if (s->tlRSelected)
			{
				iDrawPointLarge(h, pr, colorSelected);
				iDrawPoint(h, pr, colorRSelected);

			} else {
				iDrawPoint(h, pr, colorR);
			}


		//////////
		// Origin/middle
		//////
			if (s->tlOSelected)
			{
				iDrawPointLarge(h, po, colorSelected);
				iDrawPoint(h, po, colorOSelected);

			} else {
				iDrawPoint(h, po, colorO);
			}


		//////////
		// Left
		//////
			if (s->tlLSelected)
			{
				iDrawPointLarge(h, pl, colorSelected);
				iDrawPoint(h, pl, colorLSelected);

			} else {
				iDrawPoint(h, pl, colorL);
			}
	}

	void iDrawLine(SHwnd* h, SXYF64* p1, SXYF64* p2, SBGR colorStart, SBGR colorEnd)
	{
		SBGR_AF64	colorStartAlp, colorEndAlp;


		//////////
		// Create our 1.0 alpha pseudo colors
		//////
			// start
			colorStartAlp.red	= colorStart.red;
			colorStartAlp.grn	= colorStart.grn;
			colorStartAlp.blu	= colorStart.blu;
			colorStartAlp.falp	= 1.0;

			// end
			colorEndAlp.red	= colorEnd.red;
			colorEndAlp.grn	= colorEnd.grn;
			colorEndAlp.blu	= colorEnd.blu;
			colorEndAlp.falp	= 1.0;


		//////////
		// Draw in the alpha algorithm
		//////
			iDrawLineAlpha(h, p1, p2, &colorStartAlp, &colorEndAlp, NULL, false);
	}

	void iDrawLineAlpha(SHwnd* h, SXYF64* p1, SXYF64* p2, SBGR_AF64* colorStart, SBGR_AF64* colorEnd, SBuilder* pointsDrawn, bool tlNoDuplicates)
	{
		f64			lfPercent, lfSteps, lfStepInc, lfRadius, lfCosTheta, lfSinTheta;
		f64			lfRed, lfGrn, lfBlu, lfAlp, lfMalp, lfRedStep, lfGrnStep, lfBluStep, lfAlpStep;
		s32			lnX, lnY, lnXLast, lnYLast;
		SLineF64	line;
		SBGRA		color;
		SBGR*		lbgr;


		//////////
		// Make sure we're not in a non-draw position
		//////
			if (p1->x == -1.0 && p1->y == -1.0)
				return;		// Do not draw this point


		//////////
		// Compute the line we'll draw along
		//////
			line.p1.x	= p1->x * (f64)h->w;
			line.p1.y	= p1->y * (f64)h->h;
			line.p2.x	= p2->x * (f64)h->w;
			line.p2.y	= p2->y * (f64)h->h;
			iComputeLine(&line);
			lfCosTheta	= cos(line.theta);
			lfSinTheta	= sin(line.theta);


		//////////
		// Compute colors
		//////
			lfSteps		= line.length * _SQRT2;
			lfRed		= (f64)colorStart->red;
			lfGrn		= (f64)colorStart->grn;
			lfBlu		= (f64)colorStart->blu;
			lfAlp		= colorStart->falp;
			lfRedStep	= ((f64)colorEnd->red - lfRed) / lfSteps;
			lfGrnStep	= ((f64)colorEnd->grn - lfGrn) / lfSteps;
			lfBluStep	= ((f64)colorEnd->blu - lfBlu) / lfSteps;
			lfAlpStep	= (colorEnd->falp - lfAlp) / lfSteps;


		//////////
		// Proceed for the number of pixels times sqrt(2)
		//////
			lfStepInc = 1.0 / lfSteps;
			lnXLast		= -10000;
			lnYLast		= -10000;
			for (lfPercent = 0.0f; lfPercent < 1.0f; lfPercent += lfStepInc, lfRed += lfRedStep, lfGrn += lfGrnStep, lfBlu += lfBluStep, lfAlp += lfAlpStep)
			{
				// Compute the radius for this point
				lfRadius = lfPercent * line.length;

				// Compute the color
				color.red	= (u8)lfRed;
				color.grn	= (u8)lfGrn;
				color.blu	= (u8)lfBlu;
				color.alp	= (u8)(lfAlp * 255.0);
				lfMalp		= 1.0 - lfAlp;

				// Compute this point
				lnX = (s32)(line.p1.x + (lfRadius * lfCosTheta));
				lnY = (s32)(line.p1.y + (lfRadius * lfSinTheta));

				// Render it if it's visible
				if (lnX >= 0 && lnX < h->w && lnY >= 0 && lnY < h->h && !(lnX == lnXLast && lnY == lnYLast))
				{
					if (tlNoDuplicates || pointsDrawn)
					{
						// Add it to a list to remove duplicates later
						iAddPointToPointsDrawn(pointsDrawn, lnX, lnY, color);

					} else {
						// Directly render it
						lbgr		= (SBGR*)((s8*)h->bd + (lnY * h->rowWidth) + (lnX * 3));
						lbgr->red	= (u8)(((f64)lbgr->red * lfMalp) + (lfRed * lfAlp));
						lbgr->grn	= (u8)(((f64)lbgr->grn * lfMalp) + (lfGrn * lfAlp));
						lbgr->blu	= (u8)(((f64)lbgr->blu * lfMalp) + (lfBlu * lfAlp));
					}
				}

				// Store the last point we rendered
				lnXLast		= lnX;
				lnYLast		= lnY;
			}
	}

	void iDrawLineAlphaNoDuplicates(SHwnd* h, SBuilder* pointsDrawn)
	{
		u32				lnI, lnCount;
		s32				lnXLast, lnYLast;
		f64				lfAlp, lfMalp;
		SBGR*			lbgr;
		SPointsDrawn*	dp;


		//////////
		// Sort the list
		//////
			lnCount = pointsDrawn->populatedLength / sizeof(SPointsDrawn);
			qsort(pointsDrawn->data, lnCount, sizeof(SPointsDrawn), iiSPointsDrawn_qsortCallback);


		//////////
		// Render each point
		//////
			lnXLast = -10000;
			lnYLast = -10000;
			for (lnI = 0; lnI < pointsDrawn->populatedLength; lnI += sizeof(SPointsDrawn))
			{
				// Grab the pointer
				dp = (SPointsDrawn*)(pointsDrawn->data + lnI);

				// Render this item
				if (!(dp->pt.xi == lnXLast && dp->pt.yi == lnYLast))
				{
					// Grab the alpha
					lfAlp		= (f64)dp->color.alp / 255.0;
					lfMalp		= 1.0 - lfAlp;

					// Render it
					lbgr		= (SBGR*)((s8*)h->bd + (dp->pt.yi * h->rowWidth) + (dp->pt.xi * 3));
					lbgr->red	= (u8)(((f64)lbgr->red * lfMalp) + ((f64)dp->color.red * lfAlp));
					lbgr->grn	= (u8)(((f64)lbgr->grn * lfMalp) + ((f64)dp->color.grn * lfAlp));
					lbgr->blu	= (u8)(((f64)lbgr->blu * lfMalp) + ((f64)dp->color.blu * lfAlp));

					// Store for the next go so we don't do this point again
					lnXLast = dp->pt.xi;
					lnYLast = dp->pt.yi;
				}
			}
	}

	// For alpha-rendering, we don't want to double-apply an alpha pixel, so this algorithm does
	// a binary search.  If it finds the point, it returns false because it could not be added.
	// If it was not found it is added.
	void iAddPointToPointsDrawn(SBuilder* pointsDrawn, s32 tnX, s32 tnY, SBGRA color)
	{
		SPointsDrawn* dp;


		// Add a new entry
		dp = (SPointsDrawn*)builder_allocateBytes(pointsDrawn, sizeof(SPointsDrawn));
		if (dp)
		{
			dp->pt.xi	= tnX;
			dp->pt.yi	= tnY;
			dp->color	= color;
		}
	}

	// Draw the point
	void iDrawPoint(SHwnd* h, SXYF64* p1, SBGR color)
	{
		SXYS32	p;


		// Determine the center point
		p.xi = (s32)(p1->x * (f64)h->w);
		p.yi = (s32)(p1->y * (f64)h->h);

		// Draw the circle there
		iDrawHorizontalLineByPixels(h, p.xi-1, p.xi+1, p.yi-2, color);		//   * * *
		iDrawHorizontalLineByPixels(h, p.xi-2, p.xi+2, p.yi-1, color);		// * * * * *
		iDrawHorizontalLineByPixels(h, p.xi-2, p.xi+2, p.yi-0, color);		// * * * * *
		iDrawHorizontalLineByPixels(h, p.xi-2, p.xi+2, p.yi+1, color);		// * * * * * 
		iDrawHorizontalLineByPixels(h, p.xi-1, p.xi+1, p.yi+2, color);		//   * * *
	}

	// Draw the small middle
	void iDrawPointSmall(SHwnd* h, SXYF64* p1, SBGR color)
	{
		SXYS32	p;


		// Determine the center point
		p.xi = (s32)(p1->x * (f64)h->w);
		p.yi = (s32)(p1->y * (f64)h->h);

		// Draw the circle there
// 		iDrawHorizontalLineByPixels(h, p.xi,	p.xi,	p.yi-1,	color);		//   *
// 		iDrawHorizontalLineByPixels(h, p.xi-1,	p.xi+1,	p.yi-0,	color);		// * * *
// 		iDrawHorizontalLineByPixels(h, p.xi,	p.xi,	p.yi+1,	color);		//   *
		iDrawHorizontalLineByPixels(h, p.xi,	p.xi,	p.yi,	color);		//   *
	}

	// Draw the point large
	void iDrawPointLarge(SHwnd* h, SXYF64* p1, SBGR color)
	{
		SXYS32	p;


		// Determine the center point
		p.xi = (s32)(p1->x * (f64)h->w);
		p.yi = (s32)(p1->y * (f64)h->h);

		// Draw the circle there
		iDrawHorizontalLineByPixels(h, p.xi-1, p.xi+1, p.yi-3, color);		//     * * *
		iDrawHorizontalLineByPixels(h, p.xi-2, p.xi+2, p.yi-2, color);		//   * * * * *
		iDrawHorizontalLineByPixels(h, p.xi-3, p.xi+3, p.yi-1, color);		// * * * * * * *
		iDrawHorizontalLineByPixels(h, p.xi-3, p.xi+3, p.yi-0, color);		// * * * * * * *
		iDrawHorizontalLineByPixels(h, p.xi-3, p.xi+3, p.yi+1, color);		// * * * * * * *
		iDrawHorizontalLineByPixels(h, p.xi-2, p.xi+2, p.yi+2, color);		//   * * * * *
		iDrawHorizontalLineByPixels(h, p.xi-1, p.xi+1, p.yi+3, color);		//     * * *
	}

	void iDrawHorizontalLineByPixels(SHwnd* h, s32 x1, s32 x2, s32 y, SBGR color)
	{
		s32		lnX;
		SBGR*	lbgr;


		// Is it out of bounds?
		if (y < 0 || y > h->h)
			return;

		// Get the pointer
		lbgr = (SBGR*)((s8*)h->bd + (y * h->rowWidth) + (x1 * 3));

		// Iterate for every x
		for (lnX = x1; lnX <= x2; lnX++, lbgr++)
		{
			// Is it out of bounds?
			if (lnX >= 0 && lnX < h->w)
			{
				// Render it
				lbgr->red	= color.red;
				lbgr->grn	= color.grn;
				lbgr->blu	= color.blu;
			}
		}
	}

	// Draw p1..p2 along the lines from p1..p4, p2..p3
	void iFillQuadAlpha(SHwnd* h, SXYF64* p1, SXYF64* p2, SXYF64* p3, SXYF64* p4, SBGR p1Color, SBGR p2Color, SBGR p3Color, SBGR p4Color, f64 tfP1Alp, f64 tfP2Alp, f64 tfP3Alp, f64 tfP4Alp)
	{
		f64			lfPercent, lfStep, lfStepCount, lfCosThetaP1P4, lfSinThetaP1P4, lfCosThetaP2P3, lfSinThetaP2P3, lfMultiplier;
		SXYF64		lp1, lp2;
		SLineF64	p1p4, p2p3;
		bool		llNoAlpha;
		f64			lfRedP1P4, lfGrnP1P4, lfBluP1P4, lfAlpP1P4, lfRedP2P3, lfGrnP2P3, lfBluP2P3, lfAlpP2P3;
		f64			lfRedP1P4Step, lfGrnP1P4Step, lfBluP1P4Step, lfAlpP1P4Step, lfRedP2P3Step, lfGrnP2P3Step, lfBluP2P3Step, lfAlpP2P3Step;
		SBGR_AF64	colorP1P4, colorP2P3;
		SBuilder*	pointsDrawn;


		//////////
		// Build our lines from p1..p4, p2..p3
		//////
			// Get our multiplier based on size
			lfMultiplier	= sqrt((f64)h->w * (f64)h->w + (f64)h->h * (f64)h->h) * _SQRT2;

			// p1..p4
			p1p4.p1.x	= p1->x;
			p1p4.p1.y	= p1->y;
			p1p4.p2.x	= p4->x;
			p1p4.p2.y	= p4->y;
			iComputeLine(&p1p4);
			lfCosThetaP1P4	= cos(p1p4.theta);
			lfSinThetaP1P4	= sin(p1p4.theta);

			// p2..p3
			p2p3.p1.x	= p2->x;
			p2p3.p1.y	= p2->y;
			p2p3.p2.x	= p3->x;
			p2p3.p2.y	= p3->y;
			iComputeLine(&p2p3);
			lfCosThetaP2P3		= cos(p2p3.theta);
			lfSinThetaP2P3		= sin(p2p3.theta);

			// Steps
			lfStepCount	= (max(p1p4.length, p2p3.length) * lfMultiplier);
			lfStep		= 1.0 / lfStepCount;


		//////////
		// Compute the color steps for this rendering
		//////
			// p1..p4
			lfRedP1P4		= (f64)p1Color.red;
			lfGrnP1P4		= (f64)p1Color.grn;
			lfBluP1P4		= (f64)p1Color.blu;
			lfAlpP1P4		= tfP1Alp;
			lfRedP1P4Step	= ((f64)p4Color.red - lfRedP1P4) / lfStepCount;
			lfGrnP1P4Step	= ((f64)p4Color.grn - lfGrnP1P4) / lfStepCount;
			lfBluP1P4Step	= ((f64)p4Color.blu - lfBluP1P4) / lfStepCount;
			lfAlpP1P4Step	= (tfP4Alp - tfP1Alp) / lfStepCount;

			// p2..p3
			lfRedP2P3		= (f64)p2Color.red;
			lfGrnP2P3		= (f64)p2Color.grn;
			lfBluP2P3		= (f64)p2Color.blu;
			lfAlpP2P3		= tfP2Alp;
			lfRedP2P3Step	= ((f64)p3Color.red - lfRedP2P3) / lfStepCount;
			lfGrnP2P3Step	= ((f64)p3Color.grn - lfGrnP2P3) / lfStepCount;
			lfBluP2P3Step	= ((f64)p3Color.blu - lfBluP2P3) / lfStepCount;
			lfAlpP2P3Step	= (tfP3Alp - tfP2Alp) / lfStepCount;

			// Are we rendering any that are alpha?
// The following does a test to see if we should use the alpha algorithm.  It works, but it is
// notably slower on large strokes.  So, by default it is shut off.
//			llNoAlpha = false;
// 			if (tfP1Alp == 1.0 && tfP2Alp == 1.0 && tfP3Alp == 1.0 && tfP4Alp == 1.0)
				llNoAlpha = true;


		//////////
		// Create our points drawn buffer so duplicate points are not rendered
		//////
			if (!llNoAlpha)
				builder_createAndInitialize(&pointsDrawn, -1);



		//////////
		// Iterate by sqrt(2) times the maximum line length
		//////
			for (lfPercent = 0.0; lfPercent < 1.0; lfPercent += lfStep)
			{
				//////////
				// Compute the points
				//////
					lp1.x	= p1p4.p1.x + (lfPercent * p1p4.length * lfCosThetaP1P4);
					lp1.y	= p1p4.p1.y + (lfPercent * p1p4.length * lfSinThetaP1P4);
					lp2.x	= p2p3.p1.x + (lfPercent * p2p3.length * lfCosThetaP2P3);
					lp2.y	= p2p3.p1.y + (lfPercent * p2p3.length * lfSinThetaP2P3);


				//////////
				// Compute the color for this leg
				//////
					// p1..p4
					colorP1P4.red	= (u8)lfRedP1P4;
					colorP1P4.grn	= (u8)lfGrnP1P4;
					colorP1P4.blu	= (u8)lfBluP1P4;
					colorP1P4.falp	= lfAlpP1P4;
					// p2..p3
					colorP2P3.red	= (u8)lfRedP2P3;
					colorP2P3.grn	= (u8)lfGrnP2P3;
					colorP2P3.blu	= (u8)lfBluP2P3;
					colorP2P3.falp	= lfAlpP2P3;


				//////////
				// Draw this line
				//////
					if (llNoAlpha)		iDrawLineAlpha(h, &lp1, &lp2, &colorP1P4, &colorP2P3, NULL,			false);
					else				iDrawLineAlpha(h, &lp1, &lp2, &colorP1P4, &colorP2P3, pointsDrawn,	true);


				//////////
				// Increase the color for the next iteration
				//////
					// p1..p4
					lfRedP1P4	+= lfRedP1P4Step;
					lfGrnP1P4	+= lfGrnP1P4Step;
					lfBluP1P4	+= lfBluP1P4Step;
					lfAlpP1P4	+= lfAlpP1P4Step;
					// p2..p3
					lfRedP2P3	+= lfRedP2P3Step;
					lfGrnP2P3	+= lfGrnP2P3Step;
					lfBluP2P3	+= lfBluP2P3Step;
					lfAlpP2P3	+= lfAlpP2P3Step;
			}


		//////////
		// Destroy the points drawn buffer after first rendering it
		//////
			if (!llNoAlpha)
			{
				iDrawLineAlphaNoDuplicates(h, pointsDrawn);
				builder_freeAndRelease(&pointsDrawn);
			}
	}

	void iSetPoint(SXYF64* p, f64 x, f64 y)
	{
		p->x = x;
		p->y = y;
	}

	void iCopyPoint(SXYF64* pDst, SXYF64* pSrc)
	{
		pDst->x = pSrc->x;
		pDst->y = pSrc->y;
	}




//////////
//
// Called to render the mouse atop the current image
//
//////
	void iRenderMouseOverlay(SInstance* p, SHwnd* h, SChars* c)
	{
		SXYS32		p1;
		SLineF64	line;
		s32			lnX, lnY, lnYLast;
		f64			lfTheta, lfThetaStep, lfA, lfB, lfV1, lfV2, lfX, lfY, lfRadius;
		SBGR		color;


		// Invert the Y mouse coordinates for rendering
		p1.xi = gMouse.xi;
		p1.yi = h->h - gMouse.yi;

		// Do we need to render the select area?
		if (glCtrlKeyDown && !(glMouseLeft || glMouseRight))		color = mousePeeakaheadColor;
		else														color = mouseColor;

		// If the CTRL key is down, compute what would be the closest point, and render that line
		if (glCtrlKeyDown)
		{
			// Compute the closest line to the mouse, but only within a certain radius
			if (iComputeClosestMouseLine(&line))
			{
				// Draw a point at the center of the indicated line
				iDrawPointLarge(h, &line.mid, color);
			}
		}

		// Is there a reason to render the rectangles?
		if (glMouseLeft || glMouseRight)
		{
			// The mouse is pressed down, render the select area
			// Render it (we're basically drawing an oval area the mouse will interact with)
			lfRadius	= (f64)iValidateRange(p->selectArea, _SELECT_AREA_SMALL, _SELECT_AREA_EXTRA_LARGE, _SELECT_AREA_SMALL);
			lnYLast		= -1;
			lfA			= lfRadius * 1.0;		// A is 100%
			lfB			= lfRadius * 0.7;		// B is 70%, this gives us a 10:7 oval
			lfThetaStep	= _PI / ((f64)gMouseType * 128.0);
			for (lfTheta = 0; lfTheta < _PI_2; lfTheta += lfThetaStep)
			{
				// Compute the X,Y for Quad I, then reflect for lines in Quad2..1, and Quad3..4
				lfV1		= lfB * cos(lfTheta);
				lfV2		= lfA * sin(lfTheta);
				lfRadius	= (lfA*lfB) / sqrt(lfV1*lfV1 + lfV2*lfV2);

				// Compute X and Y given this radius
				lfX			= lfRadius * cos(lfTheta);
				lfY			= lfRadius * sin(lfTheta);

				// Convert to integer
				lnY			= (s32)lfY;
				lnX			= (s32)lfX;

				// If it's changed, draw it
				if (lnY != lnYLast)
				{
					// Draw the mouse indicator there, and perform any operations
					iColorizeAndProcessHorizontalLineByPixels(p, h, c, p1.xi - lnX, p1.xi + lnX, p1.yi + lnY, color);		// Above
					if (lnY != 0)
						iColorizeAndProcessHorizontalLineByPixels(p, h, c, p1.xi - lnX, p1.xi + lnX, p1.yi - lnY, color);	// Below

					lnYLast = lnY;
				}
			}
		}

		if (p->showMouseCrosshairs && p1.xi >= 0 && p1.xi < h->w && p1.yi >= 0 && p1.yi < h->h)
		{
			// Render the horizontal and vertical crosshair lines
			iColorizeHorizontalLineByPixels(p, h, c, 0, h->w - 1, p1.yi, mouseColor);		// Horizontal
			iColorizeVerticalLineByPixels(  p, h, c, 0, h->h - 1, p1.xi, mouseColor);		// Vertical
		}
	}

	bool iComputeClosestMouseLine(SLineF64* line)
	{
		// Find the closest point to the current mouse coordinates

		// Find the closest 20 points to that

		// Determine the slope of every point to every other point

		// Sort the list by slope order

		// Determine the deltas between each item

		// Sort the list by the deltas

		// Using the top 10 deltas, determine the midpoint and average slope and radius

		// Construct a line with that information
		return(false);
	}

	void iColorizeAndProcessHorizontalLineByPixels(SInstance* p, SHwnd* h, SChars* c, s32 x1, s32 x2, s32 y, SBGR color)
	{
		SXYF64 ul, lr;


		//////////
		// Make sure the values are in the correct order
		/////
			iMakeSureLowToHighS32(&x1, &x2);


		//////////
		// Colorize it
		//////
			iColorizeHorizontalLineByPixels(p, h, c, x1, x2, y, color);

		//////
		// Process it
		// Scan through this range and see if there are any splines, points, or strokes which need selected
		//////
			// Compute upper-left and lower-right range
			ul.x = (f64)x1                    / (f64)h->w;
			ul.y = ((f64)y  + 0.999999999999) / (f64)h->h;
			lr.x = ((f64)x2 + 0.999999999999) / (f64)h->w;
			lr.y = (f64)y                     / (f64)h->h;

			// Process the selection operation on this range
			iSelectRange(p, h, c, &lr, &lr);
	}

	void iColorizeHorizontalLineByPixels(SInstance* p, SHwnd* h, SChars* c, s32 x1, s32 x2, s32 y, SBGR color)
	{
		s32		lnX;
		f64		lfAlp, lfMalp, lfRed, lfGrn, lfBlu;
		SBGR*	lbgr;


		// Is it out of bounds?
		if (y < 0 || y >= h->h)
			return;

		// Get the pointer
		lbgr = (SBGR*)((s8*)h->bd + (y * h->rowWidth) + (x1 * 3));

		// Get the colors
		lfRed	= (f64)color.red;
		lfGrn	= (f64)color.grn;
		lfBlu	= (f64)color.blu;
		lfAlp	= 0.5;
		lfMalp	= 1.0 - lfAlp;

		// Iterate for every x
		for (lnX = x1; lnX <= x2; lnX++, lbgr++)
		{
			// Is it out of bounds?
			if (lnX >= 0 && lnX < h->w)
			{
				// Colorize it
				lbgr->red	= (u8)iScaleIntoRange((s32)((lfAlp * lfRed) + (lfMalp * (f64)lbgr->red)), 255, 92, 255);
				lbgr->grn	= (u8)iScaleIntoRange((s32)((lfAlp * lfGrn) + (lfMalp * (f64)lbgr->grn)), 255, 92, 255);
				lbgr->blu	= (u8)iScaleIntoRange((s32)((lfAlp * lfBlu) + (lfMalp * (f64)lbgr->red)), 255, 92, 255);
			}
		}

	}

	void iColorizeAndProcessVerticalLineByPixels(SInstance* p, SHwnd* h, SChars* c, s32 y1, s32 y2, s32 x, SBGR color)
	{
		SXYF64 ul, lr;


		//////////
		// Make sure the values are in the correct order
		/////
			iMakeSureLowToHighS32(&y1, &y2);


		//////////
		// Colorize it
		//////
			iColorizeVerticalLineByPixels(p, h, c, y1, y2, x, color);


		//////
		// Process it
		// Scan through this range and see if there are any splines, points, or strokes which need selected
		//////
			// Compute upper-left and lower-right range
			ul.x = (f64)x                     / (f64)h->w;
			ul.y = ((f64)y1 + 0.999999999999) / (f64)h->h;
			lr.x = ((f64)x  + 0.999999999999) / (f64)h->w;
			lr.y = (f64)y2                    / (f64)h->h;
			iSelectRange(p, h, c, &lr, &lr);
	}

	void iColorizeVerticalLineByPixels(SInstance* p, SHwnd* h, SChars* c, s32 y1, s32 y2, s32 x, SBGR color)
	{
		s32		lnY;
		f64		lfAlp, lfMalp, lfRed, lfGrn, lfBlu;
		SBGR*	lbgr;


		// Is it out of bounds?
		if (x < 0 || x >= h->w)
			return;

		// Get the pointer
		lbgr = (SBGR*)((s8*)h->bd + (y1 * h->rowWidth) + (x * 3));

		// Get the colors
		lfRed	= (f64)color.red;
		lfGrn	= (f64)color.grn;
		lfBlu	= (f64)color.blu;
		lfAlp	= 0.5;
		lfMalp	= 1.0 - lfAlp;

		// Iterate for every x
		for (lnY = y1; lnY <= y2; lnY++, lbgr = (SBGR*)((s8*)lbgr + h->rowWidth))
		{
			// Is it out of bounds?
			if (lnY >= 0 && lnY < h->h)
			{
				// Colorize it
				lbgr->red	= (u8)iScaleIntoRange((s32)((lfAlp * lfRed) + (lfMalp * (f64)lbgr->red)), 255, 92, 255);
				lbgr->grn	= (u8)iScaleIntoRange((s32)((lfAlp * lfGrn) + (lfMalp * (f64)lbgr->grn)), 255, 92, 255);
				lbgr->blu	= (u8)iScaleIntoRange((s32)((lfAlp * lfBlu) + (lfMalp * (f64)lbgr->red)), 255, 92, 255);
			}
		}
	}




//////////
//
// Called to render the markup data onto the character
//
//////
	void iRenderTems(SInstance* p, SHwnd* h, SChars* c)
	{
// 		s32			lnX;
// 		u32			lnI, lnINext, lnTemsCount;
// 		STemsLines*	tl;
// 		STems*		p1;
// 		STems*		p2;
// 		SLineS32	line;
		u32			lnI;
		f64			lfRed, lfGrn, lfBlu, lfGray, lfMGray;
		SXYS32		point;
		STems*		t;
		SBGR*		lbgr;


// Note:  This commented code block was an attempt to overlay using solid areas rather than an outline.
// Note:  It didn't always work correctly due to noise in the incoming outline data.  At some point I'll
//        add smoothing algorithms which correct the noise.  Until then, we'll just use the outline.
// 		//////////
// 		// Do we need to rebuild the overlay information?
// 		//////
// 			if (c->temsLines->populatedLength == 0)
// 			{
// 				// Sort the list of tems
// 				lnTemsCount = c->tems->populatedLength / sizeof(STems);
// 				qsort(c->tems->data, lnTemsCount, sizeof(STems), iiTems_qsortCallback);
// 
// 				// Iterate through each block and grab horizontal line runs in blocks
// 				// Note:  At each horizontal stop there may be one or more pixels side-by-side.
// 				//        If they exist in this way, that grouping is considered to be a single
// 				//        group, and the line data will begin beyond it.
// 				for (lnI = 0; lnI < lnTemsCount; lnI = lnINext)
// 				{
// 					// Grab the next set of line entries for this block
// 					lnINext = iiRenderMarkup_getNextLineSegment(lnI, lnTemsCount, h, (STems*)c->tems->data, &p1, &p2);
// 
// 					// Are we still valid?
// 					if (lnINext < lnTemsCount)
// 					{
// 						//////////
// 						// Allocate space for the temsLines entry
// 						//////
// 							tl = (STemsLines*)builder_allocateBytes(c->temsLines, sizeof(STemsLines));
// 							if (tl)
// 							{
// 								// Store the from and to locations
// 								tl->p1.x	= p1->fx;
// 								tl->p1.y	= p1->fy;
// 								tl->p2.x	= p2->fx;
// 								tl->p2.y	= p2->fy;
// 							}
// 					}
// 				}
// 				// When we get here, we have all of the horizontal runs
// 			}
// 
// 
// 		//////////
// 		// Iterate through each temsLines entry
// 		//////
// 			lfRed = (f64)color.red;
// 			lfGrn = (f64)color.grn;
// 			lfBlu = (f64)color.blu;
// 			for (lnI = 0; lnI < c->temsLines->populatedLength; lnI += sizeof(STemsLines))
// 			{
// 				// Grab the pointer
// 				tl = (STemsLines*)(c->temsLines->data + lnI);
// 
// 				// Render this template onto the bitmap
// 				line.p1i.xi = (s32)(tl->p1.x * (f64)h->w);
// 				line.p1i.yi = (s32)(tl->p1.y * (f64)h->h);
// 				line.p2i.xi = (s32)(tl->p2.x * (f64)h->w);
// 				line.p2i.yi = (s32)(tl->p2.y * (f64)h->h);
// 
// 				// Are we on a visible row?
// 				if (line.p1i.yi >= 0 && line.p1i.yi < h->h)
// 				{
// 					// Get the pointer
// 					lbgr = (SBGR*)((s8*)h->bd + (line.p1i.yi * h->rowWidth) + (line.p1i.xi * 3));
// 
// 					// Determine the offset
// 					for (lnX = line.p1i.xi; lnX <= line.p2i.xi; lnX++, lbgr++)
// 					{
// 						// Are we on a visible column?
// 						if (lnX >= 0 && lnX < h->w)
// 						{
// 							// Compute grayscale
// 							lfGray		= ((0.35 * (f64)lbgr->red) + (0.54 * (f64)lbgr->grn) + (0.11 * (f64)lbgr->blu)) / 255.0;
// 							lfMGray		= 1.0 - lfGray;
// 
// 							// Render it
// 							lbgr->red	= (u8)min((u32)((lfGray * lfRed) + (lfMGray * (f64)lbgr->red)), 255);
// 							lbgr->grn	= (u8)min((u32)((lfGray * lfGrn) + (lfMGray * (f64)lbgr->grn)), 255);
// 							lbgr->blu	= (u8)min((u32)((lfGray * lfBlu) + (lfMGray * (f64)lbgr->blu)), 255);
// 						}
// 					}
// 				}
// 			}


		//////////
		// Iterate through each tems entries and draw the outline
		//////
			lfRed = (f64)colorMarkup.red;
			lfGrn = (f64)colorMarkup.grn;
			lfBlu = (f64)colorMarkup.blu;
			for (lnI = 0; lnI < c->tems->populatedLength; lnI += sizeof(STems))
			{
				// Grab the pointer
				t = (STems*)(c->tems->data + lnI);

				// Render this template onto the bitmap
				point.xi = (s32)(t->fx * (f64)h->w);
				point.yi = (s32)(t->fy * (f64)h->h);

				// Are we on a visible row?
				if (point.yi >= 0 && point.yi < h->h && point.xi >= 0 && point.xi < h->w)
				{
					// Get the pointer
					lbgr = (SBGR*)((s8*)h->bd + (point.yi * h->rowWidth) + (point.xi * 3));

					// Compute grayscale
					lfGray		= ((0.35 * (f64)lbgr->red) + (0.54 * (f64)lbgr->grn) + (0.11 * (f64)lbgr->blu)) / 255.0;
					lfMGray		= 1.0 - lfGray;

					// Render it
					lbgr->red	= (u8)iScaleIntoRange(min((u32)((lfGray * lfRed) + (lfMGray * (f64)lbgr->red)), 255), 255, 32, 64);
					lbgr->grn	= (u8)iScaleIntoRange(min((u32)((lfGray * lfGrn) + (lfMGray * (f64)lbgr->grn)), 255), 255, 128, 255);
					lbgr->blu	= (u8)iScaleIntoRange(min((u32)((lfGray * lfBlu) + (lfMGray * (f64)lbgr->blu)), 255), 255, 32, 64);
				}
			}
	}

	void iInvertImage(SHwnd* h)
	{
		s32		lnX, lnY;
		SBGR*	lbgr;


		//////////
		// Iterate through every pixel
		//////
			for (lnY = 0; lnY < h->h; lnY++)
			{
				// Begin on this row
				lbgr = (SBGR*)((s8*)h->bd + (lnY * h->rowWidth));
				for (lnX = 0; lnX < h->w; lnX++, lbgr++)
				{
					// Invert the pixel
					lbgr->red = 255 - lbgr->red;
					lbgr->grn = 255 - lbgr->grn;
					lbgr->blu = 255 - lbgr->blu;
				}
			}
	}

	// Zoom the 32x32 box around the mouse coordinates into a zoom lens overlain either on the
	// upper-left or lower-left (depending on whether or not the mouse is over the default upper-
	// left display area
	void iRenderZoomLens(SHwnd* h)
	{
		s32		lnX, lnY, lnX2, lnY2, lnXSrc, lnYSrc, lnXDst, lnYDst;
		RECT	lrc;
		SBGR*	lbgrSrc;
		SBGR*	lbgrDst;


		//////////
		// See if the mouse is in this default upper-left area
		//////
			SetRect(&lrc, 0, 0, 128 + 16, 128 + 16);
			if (gMouse.xi >= lrc.left && gMouse.xi < lrc.right && gMouse.yi >= lrc.top && gMouse.yi < lrc.bottom)
				SetRect(&lrc, 0, h->h - 128, 128, h->h);


		//////////
		// Copy the image into the area
		//////
			for (lnY = 0, lnYSrc = gMouse.yi - 16, lnYDst = lrc.top; lnY < 32; lnY++, lnYSrc++, lnYDst += 4)
			{
				// Compute the source pointer for the row
				lbgrSrc = (SBGR*)((s8*)h->bd + ((h->h - lnYSrc - 1) * h->rowWidth) + ((gMouse.xi - 16) * 3));

				// Copy the columns
				for (lnX = 0, lnXSrc = gMouse.xi - 16, lnXDst = lrc.left; lnX < 32; lnX++, lnXSrc++, lnXDst += 4, lbgrSrc++)
				{
					// Repeat for a 4x zoom
					for (lnY2 = 0; lnY2 < 4; lnY2++)
					{
						// Compute the destination for this row
						lbgrDst = (SBGR*)((s8*)h->bd + ((h->h - (lnYDst + lnY2)) * h->rowWidth) + (lnXDst * 3));

						// Repeat 4x for the column
						for (lnX2 = 0; lnX2 < 4; lnX2++, lbgrDst++)
						{
							// See if this is a pixel we can copy
							if (lnXSrc >= 0 && lnXSrc < h->w && lnYSrc >= 0 && lnYSrc < h->h)
							{
								// Copy this pixel
								lbgrDst->red	= (u8)min((u32)lbgrSrc->red + 32, 255);
								lbgrDst->grn	= (u8)min((u32)lbgrSrc->grn + 32, 255);
								lbgrDst->blu	= (u8)min((u32)lbgrSrc->blu + 32, 255);

							} else {
								// Render the background color
								lbgrDst->red	= (u8)min((u32)background.red + 32, 255);
								lbgrDst->grn	= (u8)min((u32)background.grn + 32, 255);
								lbgrDst->blu	= (u8)min((u32)background.blu + 32, 255);
							}
						}
					}
				}
			}
	}

	u32 iScaleIntoRange(s32 tnValue, s32 tnValueMax, s32 tnMinRange, s32 tnMaxRange)
	{
		if (tnValue > tnValueMax)
			tnValue = tnValueMax;

		return(tnMinRange + (s32)(((f64)tnValue / (f64)tnValueMax) * (f64)(tnMaxRange - tnMinRange)));
	}

	u32 iValidateRange(s32 tnValue, s32 tnValueMin, s32 tnValueMax, s32 tnDefaultValue)
	{
		if (tnValue >= tnValueMin && tnValue <= tnValueMax)		return(tnValue);
		else													return(tnDefaultValue);
	}

	void iMakeSureLowToHighU32(u32* p1, u32* p2)
	{
		u32 lp;


		// Are they already sorted
		if (*p1 <= *p2)
			return;

		// Reverse them
		lp	= *p2;
		*p2	= *p1;
		*p1	= lp;
	}

	void iMakeSureLowToHighS32(s32* p1, s32* p2)
	{
		s32 lp;


		// Are they already sorted
		if (*p1 <= *p2)
			return;

		// Reverse them
		lp	= *p2;
		*p2	= *p1;
		*p1	= lp;
	}

	void iMakeSureLowToHighF64(f64* p1, f64* p2)
	{
		f64 lp;


		// Are they already sorted
		if (*p1 <= *p2)
			return;

		// Reverse them
		lp	= *p2;
		*p2	= *p1;
		*p1	= lp;
	}

	// Sort by Y, then X, ascending in both directions
	int iiTems_qsortCallback(const void* l, const void* r)
	{
		STems*	left;
		STems*	right;


		// Get our pointers properly
		left	= (STems*)l;
		right	= (STems*)r;

		// See how the cookie crumbles
		     if (left->fy < right->fy)		return(-1);		// Left is less than right
		else if (left->fy > right->fy)		return(1);		// Left is greater than right
		else if (left->fx < right->fx)		return(-1);		// Left is less than right
		else if (left->fx > right->fx)		return(1);		// Left is greater than right
		else								return(0);		// They're equal
	}

	// Sort by Y, then X, ascending in both directions
	int iiSXyS32_qsortCallback(const void* l, const void* r)
	{
		SXYS32*	left;
		SXYS32*	right;


		// Get our pointers properly
		left	= (SXYS32*)l;
		right	= (SXYS32*)r;

		// See how the cookie crumbles
		     if (left->yi < right->yi)		return(-1);		// Left is less than right
		else if (left->yi > right->yi)		return(1);		// Left is greater than right
		else if (left->xi < right->xi)		return(-1);		// Left is less than right
		else if (left->xi > right->xi)		return(1);		// Left is greater than right
		else								return(0);		// They're equal
	}

	int iiSPointsDrawn_qsortCallback(const void* l, const void* r)
	{
		SPointsDrawn*	left;
		SPointsDrawn*	right;


		// Get our pointers properly
		left	= (SPointsDrawn*)l;
		right	= (SPointsDrawn*)r;

		// See how the cookie crumbles
		     if (left->pt.yi < right->pt.yi)		return(-1);		// Left is less than right
		else if (left->pt.yi > right->pt.yi)		return(1);		// Left is greater than right
		else if (left->pt.xi < right->pt.xi)		return(-1);		// Left is less than right
		else if (left->pt.xi > right->pt.xi)		return(1);		// Left is greater than right
		else										return(0);		// They're equal
	}

	// Grabs the next line segment as processing through the floans.
	u32 iiRenderMarkup_getNextLineSegment(u32 tnIndex, u32 tnMaxCount, SHwnd* h, STems* root, STems** p1, STems** p2)
	{
		u32			lnI, lnOffset;
		STems*		t;
		SXYS32		lp1, lp2;


		// Skip past while the pixels are adjacent
		t = root + tnIndex;
		for (lnOffset = 1; tnIndex + lnOffset < tnMaxCount; lnOffset++)
		{
			//////////
			// Are we still on the same row?
			//////
				lp1.yi = iiGetPoint((t + lnOffset + 0)->fy,		h->h);
				lp2.yi = iiGetPoint((t + lnOffset - 1)->fy,		h->h);
				if (lp1.yi != lp2.yi)
				{
					// We've passed to another row, we begin again, but from here
					return(iiRenderMarkup_getNextLineSegment(tnIndex + lnOffset, tnMaxCount, h, root, p1, p2));
				}


			//////////
			// Are the pixels not adjacent?
			//////
				lp1.xi = iiGetPoint((t + lnOffset + 0)->fx,		h->w);
				lp2.xi = iiGetPoint((t + lnOffset - 1)->fx,		h->w);
				if (lp1.xi > lp2.xi + 1)
					break;		// Yes, they are not adjacent.  We've found the end of the grouping/run.
			

			// If we get here, we keep going because we're still on a side-by-side pixel grouping
		}

		// When we get here, we have found two pixels that are not near each other.
		*p1 = (t + lnOffset - 1);		// Last pixel in the left-side grouping
		*p2 = (t + lnOffset);			// First pixel of the right-side grouping


		//////////
		// To determine how much further we go, we now iterate forward while there are two pixels by each other until there is a gap, or end of this row
		//////
			for (lnI = 1; tnIndex + lnOffset + lnI < tnMaxCount; lnI++)
			{
				lp1.yi = iiGetPoint((t + lnOffset + lnI + 0)->fy,		h->h);
				lp1.xi = iiGetPoint((t + lnOffset + lnI + 0)->fx,		h->w);
				lp2.yi = iiGetPoint((t + lnOffset + lnI - 1)->fy,		h->h);
				lp2.xi = iiGetPoint((t + lnOffset + lnI - 1)->fx,		h->w);
				if (lp1.yi != lp2.yi || lp2.xi + 1 != lp1.xi)
				{
					lnOffset += (lnI - 1);
					break;
				}
			}


		// Indicate how far we moved
		return(tnIndex + lnOffset + 1);
	}

	s32 iiGetPoint(f64 tfValue01, s32 tnMultiplier)
	{
		return((s32)(tfValue01 * (f64)tnMultiplier));
	}




//////////
//
// Called to create a new window, or to reuse an existing window, which is for rendering displayed
// items for preview or examination.
//
//////
	SHwnd* iFindOnlyHwndByHwnd(SBuilder* hwnds, u32 tnHwndParent, u32 tnHwnd)
	{
		u32		lnI;
		SHwnd*	h;


		//////////
		// See if the existing item exists
		//////
			for (lnI = 0; lnI < hwnds->populatedLength; lnI += sizeof(SHwnd))
			{
				// Grab this pointer
				h = (SHwnd*)(hwnds->data + lnI);

				// See if it's a match
				if (h->_hwndParent == tnHwndParent && h->_hwnd == tnHwnd)
				{
					// It's a match
					return(h);
				}
			}
			// If we get here, it wasn't found
			return(NULL);
	}

	SHwnd* iFindOnlyHwndByHwndParent(SBuilder* hwnds, u32 tnHwndParent)
	{
		u32		lnI;
		SHwnd*	h;


		//////////
		// See if the existing item exists
		//////
			for (lnI = 0; lnI < hwnds->populatedLength; lnI += sizeof(SHwnd))
			{
				// Grab this pointer
				h = (SHwnd*)(hwnds->data + lnI);

				// See if it's a match
				if (h->_hwndParent == tnHwndParent && h->markup)
				{
					// It's a match
					return(h);
				}
			}
			// If we get here, it wasn't found
			return(NULL);
	}

	SHwnd* iFindOnlyHwnd(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight)
	{
		u32		lnI;
		SHwnd*	h;


		//////////
		// See if the existing item exists
		//////
			for (lnI = 0; lnI < hwnds->populatedLength; lnI += sizeof(SHwnd))
			{
				// Grab this pointer
				h = (SHwnd*)(hwnds->data + lnI);

				// See if it's a match
				if (	h->_hwndParent == tnHwndParent
					&&	h->x == tnX
					&&	h->y == tnY
					&&	h->w == tnWidth
					&&	h->h == tnHeight)
				{
					// It's a match
					return(h);
				}
			}
			// If we get here, it wasn't found
			return(NULL);
	}

	SHwnd* iFindOrCreateHwnd(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight, u32 tlMarkup)
	{
		SHwnd*	h;


		//////////
		// See if it already exists
		//////
			h = iFindOnlyHwnd(hwnds, tnHwndParent, tnX, tnY, tnWidth, tnHeight);
			if (h)
				return(h);

		//////////
		// Add it
		//////
			h = (SHwnd*)builder_allocateBytes(hwnds, sizeof(SHwnd));
			if (h)
			{
				// Initialize it
				memset(h, 0, sizeof(SHwnd));

				// Populate it
				h->_hwndParent			= tnHwndParent;
				h->x					= tnX;
				h->y					= tnY;
				h->w					= tnWidth;
				h->h					= tnHeight;
				h->markup				= tlMarkup;
				h->rowWidth				= iComputeRowWidth(tnWidth);

				// Bitmap info
				h->bi.biSize			= sizeof(h->bi);
				h->bi.biWidth			= tnWidth;
				h->bi.biHeight			= tnHeight;
				h->bi.biPlanes			= 1;
				h->bi.biBitCount		= 24;
				h->bi.biXPelsPerMeter	= 3270;
				h->bi.biYPelsPerMeter	= 3270;
				h->bi.biSizeImage		= h->rowWidth * tnHeight;

				// Bitmap header
				h->bh.bfType			= 'MB';
				h->bh.bfOffBits			= sizeof(h->bh) + sizeof(h->bi);
				h->bh.bfSize			= h->bh.bfOffBits + h->bi.biSizeImage;

				// Create the window
				h->_hwnd				= iCreateWindow(h);
			}
			// Return our pointer
			return(h);
	}




//////////
//
// Called to create a window of the indicated size, and setup the bitmap and DibSection bd bits.
//
//////
	u32 iCreateWindow(SHwnd* h)
	{
		ATOM			atom;
		WNDCLASSEXA		classa;
		RECT			lrc;


		//////////
		// Register the class if need be
		//////
			if (!GetClassInfoExA(ghInstance, cgcPreviewWindowClass, &classa))
			{
				// Initialize
				memset(&classa, 0, sizeof(classa));

				// Populate
				classa.cbSize				= sizeof(WNDCLASSEXA);
				classa.hInstance			= ghInstance;
				classa.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
				classa.lpszClassName		= cgcPreviewWindowClass;
				classa.lpfnWndProc			= (WNDPROC)GetWindowLong(h->hwndParent, GWL_WNDPROC);

				// Register
				atom = RegisterClassExA(&classa);
				if (!atom)
					return(0);		// Failure
			}
		


		//////////
		// Create the window
		//////
			h->hwnd = CreateWindowA(cgcPreviewWindowClass, cgcPreviewWindowClass, WS_CHILD, h->x, h->y, h->w, h->h, h->hwndParent, NULL, ghInstance, (LPVOID)h);
			if (h->_hwnd)
			{
				// Update the WNDPROC handler so we receive messages
				h->oldWndProcAddress = (WNDPROC)GetWindowLong(h->hwnd, GWL_WNDPROC);
				SetWindowLong(h->hwnd, GWL_WNDPROC, (long)&iWindowProcCallback);

				// Add a timer for markup windows (there should only be one)
				if (h->markup)
				{
// Removed ... probably not necessary any longer 12/10
// 					// We need the parent's window messages as well
// 					h->oldWndParentProcAddress = (WNDPROC)GetWindowLong(h->hwndParent, GWL_WNDPROC);
// 					SetWindowLong(h->hwndParent, GWL_WNDPROC, (long)&iWindowProcCallback);

					// Create a timer to read the mouse 30 times per second
					SetTimer(h->hwnd, (u32)h, 33, NULL);
				}

				// Create a DIB Section for accessing this window's bits
				SetRect(&h->rc, h->x, h->y, (h->x + h->w), (h->y + h->h));
				h->hdc	= CreateCompatibleDC(GetDC(h->hwnd));
				h->hbmp	= CreateDIBSection(h->hdc, (BITMAPINFO*)&h->bi, DIB_RGB_COLORS, (void**)&h->bd, NULL, 0);
				SelectObject(h->hdc, h->hbmp);

				// Create a second DIB Section for drawing real-time mouse events
				h->hdc2		= CreateCompatibleDC(GetDC(h->hwnd));
				h->hbmp2	= CreateDIBSection(h->hdc2, (BITMAPINFO*)&h->bi, DIB_RGB_COLORS, (void**)&h->bd2, NULL, 0);
				SelectObject(h->hdc2, h->hbmp2);

				// Create a gray brush
				h->backDarkGrayBrush = CreateSolidBrush(RGB(background.red, background.grn, background.blu));

				// Create a font for rendering the X,Y coordinate in the lower-right
				s32 lnHeight = -MulDiv(8, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);
				h->fontXY = CreateFontA(lnHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, "Tahoma");

				// Make it initially gray
				SetRect(&lrc, 0, 0, h->w, h->h);
				FillRect(h->hdc, &lrc, h->backDarkGrayBrush);
				InvalidateRect(h->hwnd, NULL, FALSE);

				// Make it visible
				ShowWindow(h->hwnd, SW_SHOW);

			} else {
				int error = GetLastError();
				_asm int 3;
			}
			return(h->_hwnd);
	}




//////////
//
// Called to compute the midpoint, slope, and perpendicular slope of a line
//
//////
	void iComputeLine(SLineF64* line)
	{
		// Midpoint = (x2-x1)/2, (y2-y1)/2
		line->mid.x			= (line->p1.x + line->p2.x) / 2.0f;
		line->mid.y			= (line->p1.y + line->p2.y) / 2.0f;
		line->delta.x		= line->p2.x - line->p1.x;
		line->delta.y		= line->p2.y - line->p1.y;
		line->theta			= iAdjustTheta(atan2(line->delta.y, line->delta.x));
		line->length		= sqrt(line->delta.x*line->delta.x + line->delta.y*line->delta.y);

		// Slope = rise over run
		line->m				= line->delta.y / ((line->delta.x == 0.0) ? 0.0000000000001 : line->delta.x);

		// Perpendicular slope = -1/m
		line->mp			= -1.0 / ((line->m == 0.0) ? 0.0000000000001 : line->m);

		// Integer roundings if need be
		// Start
		line->p1i.xi	= (s32)line->p1.x;
		line->p1i.yi	= (s32)line->p1.y;
		// End
		line->p2i.xi	= (s32)line->p2.x;
		line->p2i.yi	= (s32)line->p2.y;

		// Compute the quadrants if need be
		// Quads 1..4
		line->p1_quad	= iComputeQuad(&line->p1);
		line->p2_quad	= iComputeQuad(&line->p2);
	}

	void iComputeLineFromTwoPoints(SLineF64* line, SXYF64* p1, SXYF64* p2)
	{
		// p1
		line->p1.x	= p1->x;
		line->p1.y	= p1->y;

		// p2
		line->p2.x	= p2->x;
		line->p2.y	= p2->y;

		// Compute
		iComputeLine(line);
	}




//////////
//
// Called to constrain a quad around a line.  It is assumed that the quad runs from p1..p4, and
// p2..p3 around the line with p1..p4 being near line.p1, and p2..p3 being near line.p2.  The
// constraining distances are maximum radii out from the line to the corner points of the quad.
// If they exceed then they are reined in.  And if they are less then the flag determines if they
// are forcibly constrained to that distance.
//
//////
	void iConstrainQuadAroundLine(SLineF64* lineRef, SXYF64* p1, SXYF64* p2, SXYF64* p3, SXYF64* p4, f64 tfp1Max, f64 tfp2Max, f64 tfp3Max, f64 tfp4Max, bool tlForceSize)
	{
		iConstrainLineLength(&lineRef->p1, p1, tfp1Max, tlForceSize);
		iConstrainLineLength(&lineRef->p2, p2, tfp2Max, tlForceSize);
		iConstrainLineLength(&lineRef->p2, p3, tfp3Max, tlForceSize);
		iConstrainLineLength(&lineRef->p1, p4, tfp4Max, tlForceSize);
	}

	void iConstrainLineLength(SXYF64* po, SXYF64* pToConstrain, f64 tfMaxLength, bool tlForceToLength)
	{
		SLineF64	line;


		//////////
		// Compute our line
		//////
			line.p1.x = po->x;
			line.p1.y = po->y;
			line.p2.x = pToConstrain->x;
			line.p2.y = pToConstrain->y;
			iComputeLine(&line);
			if (tlForceToLength || line.length > tfMaxLength)
			{
				// Force the point to that length's location
				pToConstrain->x	= line.p1.x + (tfMaxLength * cos(line.theta));
				pToConstrain->y	= line.p1.y + (tfMaxLength * sin(line.theta));
			}
	}




//////////
//
// Called to adjust theta into the range 0..2pi
//
//////
	f64 iAdjustTheta(f64 tfTheta)
	{
		// Validate theta is positive
		while (tfTheta < 0.0f)
			tfTheta += _2PI;

		// Validate theta is 0..2pi
		while (tfTheta > _2PI)
			tfTheta -= _2PI;

		return(tfTheta);
	}




//////////
//
// Returns the quadrant for the indicated point
//
//////
	s32 iComputeQuad(SXYF64* p)
	{
		if (p->x >= 0.0)
		{
			// Either 1 or 4
			if (p->y >= 0.0)		return(1);		// X is positive, Y is positive
			else					return(4);		// X is positive, Y is negative

		} else {
			// Either 2 or 3
			if (p->y >= 0.0)		return(2);		// X is negative, Y is positive
			else					return(3);		// X is negative, Y is negative
		}
	}




//////////
//
// Called when the mouse is selected on this area.  Based on the selection criteria, what is
// needing to be processed will be processed.
//
//////
	void iSelectRange(SInstance* p, SHwnd* h, SChars* c, SXYF64* ul, SXYF64* lr)
	{
		u32			lnI;
		bool		llL, llO, llR, llSkipToNextStroke;
		SXYF64		pl, po, pr;
		SSpline*	spline;
		SSpline*	splineStrokeStart;


		// Iterate through each item
		llSkipToNextStroke	= false;
		splineStrokeStart	= (SSpline*)c->splines->data;
		for (lnI = 0; lnI < c->splines->populatedLength; lnI += sizeof(SSpline))
		{
			// Grab the pointer
			spline = (SSpline*)(c->splines->data + lnI);

			// We only process iOrder records above 0
			if (spline->iOrder > 0)
			{
				// See if this is the start of a new stroke
				if (spline->lPenDown)
				{
					// It is
					llSkipToNextStroke	= false;
					splineStrokeStart	= spline;
				}

				// Are supposed to skip to the start of the next stroke?
				if (!llSkipToNextStroke)
				{
					// Compute the three points
					iSplineCompute(spline, &pl, &po, &pr);

					// If any of the points are in range, then we operate appropriately
					llL		= iIsPointInRange(&pl, ul, lr);
					llO		= iIsPointInRange(&po, ul, lr);
					llR		= iIsPointInRange(&pr, ul, lr);
					if (llL || llO || llR)
					{
						// At least one of these points is in line
						switch (p->mode)
						{
							case _MODE_POINT:
								// We are selecting any matching points only
								if (llL)		iSelectPoint(p, spline, &spline->tlLSelected);
								if (llO)		iSelectPoint(p, spline, &spline->tlOSelected);
								if (llR)		iSelectPoint(p, spline, &spline->tlRSelected);
								break;

							case _MODE_SPLINE:
								// We are selecting the entire spline
								iSelectSpline(p, spline);
								break;

							case _MODE_STROKE:
								// We are selecting the entire stroke
								iSelectStroke(p, splineStrokeStart);
								llSkipToNextStroke = true;
								break;

							case _MODE_BEFORE:
								// We are selecting everything up to and including this spline on the stroke
								iSelectStrokeBefore(p, splineStrokeStart, spline);
								break;

							case _MODE_AFTER:
								// We are selecting everything from this spline and beyond on this stroke
								iSelectStrokeAfter(p, spline);
								llSkipToNextStroke = true;
								break;

							default:
								// A settings error
								_asm int 3;
								return;
						}
					}
				}
			}
		}
	}

	void iSelectPoint(SInstance* p, SSpline* spline, bool* tlSelected)
	{
		if (p->disposition == _DISPOSITION_FLIP_LR || p->disposition == _DISPOSITION_FLIP_LM_RM)
		{
			// This is an entire spline operation
			iSelectSpline(p, spline);
			return;
		}

		// If we get here, it's some other disposition
		switch (p->method)
		{
			case _METHOD_LEFT:
				// They want the left point selected, and the middle and right points not selected
				switch (p->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = true;
						spline->tlLProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = false;
						spline->tlLProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlLProcessed)		spline->tlLSelected = !spline->tlLSelected;
						spline->tlLProcessed = true;
						break;
				}
				break;

			case _METHOD_MIDDLE:
				// They want the middle point selected, and the left and right points not selected
				switch (p->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlOProcessed)		spline->tlOSelected = true;
						spline->tlOProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlOProcessed)		spline->tlOSelected = false;
						spline->tlOProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlOProcessed)		spline->tlOSelected = !spline->tlOSelected;
						spline->tlOProcessed = true;
						break;
				}
				break;

			case _METHOD_RIGHT:
				// They want the right point selected, and the left and middle points not selected
				switch (p->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlRProcessed)		spline->tlRSelected = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlRProcessed)		spline->tlRSelected = false;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlRProcessed)		spline->tlRSelected = !spline->tlRSelected;
						spline->tlRProcessed = true;
						break;
				}
				break;

			case _METHOD_LEFT_MIDDLE:
				// They want the left and middle points selected, and the right point not selected
				switch (p->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = true;
						if (!spline->tlOProcessed)		spline->tlOSelected = true;
						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = false;
						if (!spline->tlOProcessed)		spline->tlOSelected = false;
						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlLProcessed)		spline->tlLSelected = !spline->tlLSelected;
						if (!spline->tlOProcessed)		spline->tlOSelected = !spline->tlOSelected;
						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						break;
				}
				break;

			case _METHOD_MIDDLE_RIGHT:
				// They want the middle and right points selected, and the left point not selected
				switch (p->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlOProcessed)		spline->tlOSelected = true;
						if (!spline->tlRProcessed)		spline->tlRSelected = true;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlOProcessed)		spline->tlOSelected = false;
						if (!spline->tlRProcessed)		spline->tlRSelected = false;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlOProcessed)		spline->tlOSelected = !spline->tlOSelected;
						if (!spline->tlRProcessed)		spline->tlRSelected = !spline->tlRSelected;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;
				}
				break;

			case _METHOD_LEFT_RIGHT:
				// They want the left and right points selected, and the middle point not selected
				switch (p->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = true;
						if (!spline->tlRProcessed)		spline->tlRSelected = true;
						spline->tlLProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = false;
						if (!spline->tlRProcessed)		spline->tlRSelected = false;
						spline->tlLProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlLProcessed)		spline->tlLSelected = !spline->tlLSelected;
						if (!spline->tlRProcessed)		spline->tlRSelected = !spline->tlRSelected;
						spline->tlLProcessed = true;
						spline->tlRProcessed = true;
						break;
				}
				break;

			case _METHOD_SPLINE:
				// They want the all three, left, middle, and right points selected
				switch (p->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = true;
						if (!spline->tlOProcessed)		spline->tlOSelected = true;
						if (!spline->tlRProcessed)		spline->tlRSelected = true;

						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = false;
						if (!spline->tlOProcessed)		spline->tlOSelected = false;
						if (!spline->tlRProcessed)		spline->tlRSelected = false;

						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlLProcessed)		spline->tlLSelected = !spline->tlLSelected;
						if (!spline->tlOProcessed)		spline->tlOSelected = !spline->tlOSelected;
						if (!spline->tlRProcessed)		spline->tlRSelected = !spline->tlRSelected;

						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;
				}
				break;

			case _METHOD_POINT:
				switch (p->disposition)
				{
					case _DISPOSITION_SELECT:
						// We are simply selecting
						if (!spline->tlLProcessed)		*tlSelected = true;
						spline->tlLProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// We are simply unselecting
						if (!spline->tlLProcessed)		*tlSelected = false;
						spline->tlLProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlLProcessed)		*tlSelected = !*tlSelected;
						spline->tlLProcessed = true;
						break;
				}
				break;
		}
	}

	void iSelectSpline(SInstance* p, SSpline* spline)
	{
		switch (p->disposition)
		{
			case _DISPOSITION_SELECT:
				// They are selecting
				if (!spline->tlLProcessed)		spline->tlLSelected = true;
				if (!spline->tlOProcessed)		spline->tlOSelected = true;
				if (!spline->tlRProcessed)		spline->tlRSelected = true;

				spline->tlLProcessed = true;
				spline->tlOProcessed = true;
				spline->tlRProcessed = true;
				break;

			case _DISPOSITION_UNSELECT:
				// They are un-selecting
				if (!spline->tlLProcessed)		spline->tlLSelected = false;
				if (!spline->tlOProcessed)		spline->tlOSelected = false;
				if (!spline->tlRProcessed)		spline->tlRSelected = false;

				spline->tlLProcessed = true;
				spline->tlOProcessed = true;
				spline->tlRProcessed = true;
				break;

			case _DISPOSITION_TOGGLE:
				// We are toggling
				if (!spline->tlLProcessed)		spline->tlLSelected = !spline->tlLSelected;
				if (!spline->tlOProcessed)		spline->tlOSelected = !spline->tlOSelected;
				if (!spline->tlRProcessed)		spline->tlRSelected = !spline->tlRSelected;

				spline->tlLProcessed = true;
				spline->tlOProcessed = true;
				spline->tlRProcessed = true;
				break;

			case _DISPOSITION_FLIP_LR:
				// We are toggling left right, or right left
				if (spline->tlLSelected)
				{
					// Switch to right
					if (!spline->tlLProcessed)		spline->tlLSelected = false;
					if (!spline->tlOProcessed)		spline->tlOSelected = false;
					if (!spline->tlRProcessed)		spline->tlRSelected = true;

				} else if (spline->tlRSelected) {
					// Switch to left
					if (!spline->tlLProcessed)		spline->tlLSelected = true;
					if (!spline->tlOProcessed)		spline->tlOSelected = false;
					if (!spline->tlRProcessed)		spline->tlRSelected = false;
				}

				spline->tlLProcessed = true;
				spline->tlOProcessed = true;
				spline->tlRProcessed = true;
				break;

			case _DISPOSITION_FLIP_LM_RM:
				// We are toggling left+middle to middle+right, or middle+right to middle+left
				if (spline->tlLSelected)
				{
					// Switch to right
					if (!spline->tlLProcessed)		spline->tlLSelected = false;
					if (!spline->tlOProcessed)		spline->tlOSelected = true;
					if (!spline->tlRProcessed)		spline->tlRSelected = true;

				} else if (spline->tlRSelected) {
					// Switch to left
					if (!spline->tlLProcessed)		spline->tlLSelected = true;
					if (!spline->tlOProcessed)		spline->tlOSelected = true;
					if (!spline->tlRProcessed)		spline->tlRSelected = false;
				}

				spline->tlLProcessed = true;
				spline->tlOProcessed = true;
				spline->tlRProcessed = true;
				break;
		}
	}

	void iSelectStroke(SInstance* p, SSpline* splineStrokeStart)
	{
		// Incomplete feature
		_asm int 3;
	}

	void iSelectStrokeBefore(SInstance* p, SSpline* splineStrokeStart, SSpline* splineStrokeEnd)
	{
		// Incomplete feature
		_asm int 3;
	}

	void iSelectStrokeAfter(SInstance* p, SSpline* splineStrokeStart)
	{
		// Incomplete feature
		_asm int 3;
	}

	void iSplineCompute(SSpline* spline, SXYF64* pl, SXYF64* po, SXYF64* pr)
	{
		//////////
		// Origin is a simple copy
		//////
			po->x = spline->ox;
			po->y = spline->oy;


		//////////
		// Left and right are computed based on theta and origin
		//////
			// Right
			pr->x = spline->ox + (spline->rr * cos(spline->rt + spline->ot));
			pr->y = spline->oy + (spline->rr * sin(spline->rt + spline->ot));
			// Left
			pl->x = spline->ox + (spline->lr * cos(spline->lt + spline->ot));
			pl->y = spline->oy + (spline->lr * sin(spline->lt + spline->ot));

	}

	// Test the point against the ul..lr range
	bool iIsPointInRange(SXYF64* pt, SXYF64* ul, SXYF64* lr)
	{
		if (pt->y >= ul->y && pt->y <= lr->y)
		{
			if (pt->x >= ul->x && pt->x <= lr->x)
			{
				// We're good
				return(true);
			}
		}
		// Not in range
		return(false);
	}




//////////
//
// Read the mouse position asynchronously
//
//////
	void iReadMousePosition(SInstance* p, SHwnd* h)
	{
		u32			lnI, lnJ;
		bool		llLastMouseLeft, llLastMouseRight, llLastCtrl, llLastShift, llLastAlt, llMoved, llWasOnTheReservation;
		SChars*		c;
		SSpline*	spline;
		POINT		pt;


		//////////
		// Grab the cursor position
		//////
			llLastMouseLeft		= glMouseLeft;
			llLastMouseRight	= glMouseRight;
			glMouseLeft			= (GetAsyncKeyState(VK_LBUTTON) != 0);
			glMouseRight		= (GetAsyncKeyState(VK_RBUTTON) != 0);
			GetCursorPos(&pt);
			ScreenToClient(h->hwnd, &pt);


		//////////
		// Grab the key states
		//////
			llLastCtrl			= glCtrlKeyDown;
			llLastShift			= glShiftKeyDown;
			llLastAlt			= glAltKeyDown;
			glCtrlKeyDown		= (GetAsyncKeyState(VK_CONTROL) != 0);
			glShiftKeyDown		= (GetAsyncKeyState(VK_SHIFT) != 0);
			glAltKeyDown		= (GetAsyncKeyState(VK_MENU) != 0);

		
		//////////
		// Adjust for the window
		//////
			// Adjust for our window
			pt.y		-= h->y;

			// See if it's moved, and if so if it's moved off the reservation
			llMoved					= !(gMouse.xi == pt.x && gMouse.yi == pt.y);
			llWasOnTheReservation	= (gMouse.xi >= 0 && gMouse.xi < h->w && gMouse.yi >= 0 && gMouse.yi < h->h);

			// Store the new value
			gMouse.xi	= pt.x;
			gMouse.yi	= pt.y;

			// If we are now off the reservation, then ignore the mouse clicks
			if (!(gMouse.xi >= 0 && gMouse.xi < h->w && gMouse.yi >= 0 && gMouse.yi < h->h))
			{
				// We are no longer on the reservation, ignore mouse clicks and key shift changes
				llLastMouseLeft		= glMouseLeft;
				llLastMouseRight	= glMouseRight;
				llLastCtrl			= glCtrlKeyDown;
				llLastShift			= glShiftKeyDown;
				llLastAlt			= glAltKeyDown;
			}


		//////////
		// Has the mouse moved?
		//////
			if (llWasOnTheReservation || 
				(llMoved && gMouse.xi >= 0 && gMouse.xi < h->w && gMouse.yi >= 0 && gMouse.yi < h->h) ||
				llLastMouseLeft != glMouseLeft || llLastMouseRight != glMouseRight || 
				llLastCtrl != glCtrlKeyDown || llLastShift != glShiftKeyDown || llLastAlt != glAltKeyDown)
			{
				//////////
				// Has the left mouse button gone down?
				//////
					if (!llLastMouseLeft && glMouseLeft)
					{
						// Yes, set everything to being not processed
						for (lnI = 0; lnI < p->chars->populatedLength; lnI += sizeof(SChars))
						{
							// Grab this pointer
							c = (SChars*)(p->chars->data + lnI);

							// Do every spline within each character
							for (lnJ = 0; lnJ < c->splines->populatedLength; lnJ += sizeof(SSpline))
							{
								// Grab this pointer
								spline = (SSpline*)(c->splines->data + lnJ);

								// We only process positive orders
								if (spline->iOrder > 0)
								{
									// Set this one to not processed
									spline->tlLProcessed	= false;
									spline->tlOProcessed	= false;
									spline->tlRProcessed	= false;
								}
							}
						}
					}


				//////////
				// Post a message back to the parent to indicate this child needs to be redrawn
				//////
					PostMessage(h->hwndParent, WM_REDRAW_WINDOW, (u32)p, h->_hwnd);
			}
	}




//////////
//
// Callback for the window
//
//////
	LRESULT CALLBACK iWindowProcCallback(HWND hwnd, UINT m, WPARAM w, LPARAM l)
	{
		u32				lnI;
		PAINTSTRUCT		ps;
		HDC				lhdc;
		union {
			HWND		thisHwnd;
			u32			_thisHwnd;
		};
		union {
			HWND		hwndParent;
			u32			_hwndParent;
		};
		SHwnd*			h;
		SInstance*		s;


		// See if we know this hwnd
		thisHwnd	= hwnd;
		hwndParent	= GetParent(hwnd);
		for (lnI = 0; lnI < instances->populatedLength; lnI += sizeof(SInstance))
		{
			// Grab the pointer
			s = (SInstance*)(instances->data + lnI);

			// See if we're found on this instance
			h = iFindOnlyHwndByHwnd(s->hwnds, _hwndParent, _thisHwnd);
			if (h)
			{
				// It was one of our windows
				switch (m)
				{
					// Create a timer for reading the mouse position because as of yet I have not figured out how to get this child window attached to a VFP form to reliably send over WM_MOUSEMOVE messages unless the mouse is physically depressed
					case WM_DESTROY:
						KillTimer(hwnd, (u32)h);
						break;

					// Get the mouse and keyboard state
					case WM_TIMER:
						iReadMousePosition(s, h);
						break;

					// Redraw the window
					case WM_PAINT:
						// Paint it
						lhdc = BeginPaint(hwnd, &ps);
						BitBlt(lhdc, 0, 0, h->w, h->h, h->hdc, 0, 0, SRCCOPY);
						EndPaint(hwnd, &ps);
						// All done

						// Indicate to Windows that we processed it
						return 0;
						// If we get here, we are not processing this message any longer
						break;
				}
				// Call Windows' default procedure handler
				return(DefWindowProc(hwnd, m, w, l));
			}

			// See if this hwnd is one of our parent hwnd's
			h = iFindOnlyHwndByHwndParent(s->hwnds, _thisHwnd);
			if (h)
			{
// 				//////////
// 				// Make sure we have the keyboard/mouse capture
// 				//////
// 					if (GetCapture() != h->hwnd)
// 						SetCapture(h->hwnd);

				// What do they want? :-)
				switch (m)
				{
					case WM_LBUTTONDBLCLK:
					case WM_RBUTTONDBLCLK:
					case WM_MBUTTONDBLCLK:
						break;

					case WM_MOUSEMOVE:
						iReadMousePosition(s, h);
						break;

					case WM_LBUTTONDOWN:
					case WM_RBUTTONDOWN:
					case WM_MBUTTONDOWN:
						iReadMousePosition(s, h);
						break;

					case WM_LBUTTONUP:
					case WM_RBUTTONUP:
					case WM_MBUTTONUP:
						iReadMousePosition(s, h);
						break;
						break;
				}
				// We found that it's a parent message
				return(CallWindowProc(h->oldWndParentProcAddress, hwnd, m, w, l));
			}
		}
		// Call Windows' default procedure handler
		return(DefWindowProc(hwnd, m, w, l));
	}
