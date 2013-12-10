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
			builder_FreeAndRelease(&r->floans);


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
							builder_FreeAndRelease(&temsTempBuilder);
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
		f64		lfX, lfY, lfTheta, lfRadius, lfA, lfB, lfV1, lfV2;
		bool	llPenDown;


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
	void iAddSplineFromToLR(SBuilder* b, bool tlPenDown, f64 tfXL, f64 tfYL, f64 tfXR, f64 tfYR)
	{
		SLinef64	line;
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
	}




//////////
//
// Adds a new spline to the builder, computing from the indicated x,y center, given a radius and
// two angles, first for L, then for R.  The line runs horizontally, which means from 0..1, which
// is from left to right in our system, as per the standard Quad 1 X,Y coordinate system.
//
//////
	void iAddSplineCenterThetaRadiusLR(SBuilder* b, bool tlPenDown, f64 tfX, f64 tfY, f64 tfRadius, f64 tfThetaL, f64 tfThetaR)
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
			builder_FreeAndRelease(&floans);
			builder_FreeAndRelease(&floansCsv);


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
				if (h->markup != 0)		FillRect(h->hdc, &lrc, h->backDarkGrayBrush);
				else					FillRect(h->hdc, &lrc, (HBRUSH)GetStockObject(WHITE_BRUSH));

				// Render the splines with markup lines
				iRenderSplines(p, h, c, h->markup, h->bold, h->italic, h->underline, h->strikethrough);

				// Render the markup
				if (h->markup != 0)
				{
					iRenderMarkup(p, h, c);
					iRenderMouseOverlay(p, h, c);
				}
			}

			// Redraw after the rendering
			if (h->_hwnd)
			{
				SetRect(&lrc, 0, 0, 10000, 10000);
				if (IsWindow(h->hwndParent))
					InvalidateRect(h->hwndParent, &lrc, TRUE);

				SetRect(&lrc, 0, 0, h->w, h->h);
				if (IsWindow(h->hwnd))
					InvalidateRect(h->hwnd, &lrc, TRUE);	
			}


		// Indicate the hwnd handle we rendered
		return(h->_hwnd);
	}




//////////
//
// Called to render the indicated splines onto the character
//
//////
	void iRenderSplines(SInstance* p, SHwnd* h, SChars* c, u32 tlMarkup, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough)
	{
		u32			lnI;
		SXYF64		prLast, poLast, plLast;
		SXYF64		pr, po, pl;
		SSpline*	s;
		SSpline*	sLast;
		SBuilder*	b;


		//////////
		// For new characters or definitions there may not yet be any splines.  We use a placeholder
		// drawn onto the character until such time
		/////
			if (c->splines->populatedLength <= sizeof(SSpline))
				b = placeholder;//	return;					// Return (optionally, the the placeholder could be drawn)
			else
				b = c->splines;								// Draw the character splines

			// Determine the color
			if (tlMarkup == 0)
			{
				// It is a final render, black on white
				spline.red = 0;
				spline.grn = 0;
				spline.blu = 0;

			} else {
				// It is a markup render, light gray on black
				spline.red = 92;
				spline.grn = 92;
				spline.blu = 92;
			}


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
					// Render this spline onto the bitmap
					//////
						// Right, origin/middle, left
						iSetPoint(&pr,	s->ox + (s->rr * cos(s->ot + s->rt)),	s->oy + (s->rr * sin(s->ot + s->rt)));
						iSetPoint(&po,	s->ox,									s->oy);
						iSetPoint(&pl,	s->ox + (s->lr * cos(s->ot + s->lt)),	s->oy + (s->lr * sin(s->ot + s->lt)));

						// Connect the last points to the new points
						if (!s->lPenDown)
						{
							// Draw in filled in final mode
							iFillQuad(h, &prLast, &pr, &po, &poLast, spline);
							iFillQuad(h, &poLast, &po, &pl, &plLast, spline);
						}


					//////////
					// Setup for the next stroke
					//////
						iCopyPoint(&prLast, &pr);
						iCopyPoint(&poLast, &po);
						iCopyPoint(&plLast, &pl);
				}
			}


		//////////
		// Overlay markup
		//////
			if (tlMarkup != 0)
			{
				for (lnI = 0; lnI < b->populatedLength; lnI += sizeof(SSpline))
				{
					// Grab the pointer
					s = (SSpline*)(b->data + lnI);


					//////////
					// Render this spline onto the bitmap
					//////
						// Right, origin/middle, left
						iSetPoint(&pr,	s->ox + (s->rr * cos(s->ot + s->rt)),	s->oy + (s->rr * sin(s->ot + s->rt)));
						iSetPoint(&po,	s->ox,									s->oy);
						iSetPoint(&pl,	s->ox + (s->lr * cos(s->ot + s->lt)),	s->oy + (s->lr * sin(s->ot + s->lt)));

						// Connect the last points to the new points
						if (!s->lPenDown)
						{
							// Connect left, right as markup lines
							iDrawLine(h, &pr, &prLast, sLast->tlRSelected ? colorSelected : black, s->tlRSelected ? colorSelected : black);
							iDrawLine(h, &po, &poLast, sLast->tlOSelected ? colorSelected : black, s->tlOSelected ? colorSelected : black);
							iDrawLine(h, &pl, &plLast, sLast->tlLSelected ? colorSelected : black, s->tlLSelected ? colorSelected : black);
							iDrawPoints(h, &prLast, &poLast, &plLast, sLast, colorSelected, colorR, colorO, colorL);
						}

						// Connect left, middle, right as markup lines
						iDrawLine(h, &pr, &po, s->tlRSelected ? colorSelected : black, s->tlOSelected ? colorSelected : black);
						iDrawLine(h, &po, &pl, s->tlOSelected ? colorSelected : black, s->tlLSelected ? colorSelected : black);
						iDrawPoints(h, &pr, &po, &pl, s, colorSelected, colorR, colorO, colorL);


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

	void iDrawPoints(SHwnd* h, SXYF64* pr, SXYF64* po, SXYF64* pl, SSpline* s, SBGR colorSelected, SBGR colorR, SBGR colorO, SBGR colorL)
	{
		// Right
		if (s->tlRSelected)				iDrawPointLarge(h, pr, colorSelected);
		iDrawPoint(h, pr, colorR);

		// Origin/middle
		if (s->tlOSelected)				iDrawPointLarge(h, po, colorSelected);
		iDrawPoint(h, po, colorO);

		// Left
		if (s->tlLSelected)				iDrawPointLarge(h, pl, colorSelected);
		iDrawPoint(h, pl, colorL);
	}

	void iDrawLine(SHwnd* h, SXYF64* p1, SXYF64* p2, SBGR colorStart, SBGR colorEnd)
	{
		f64			lfPercent, lfSteps, lfStepInc, lfRadius, lfCosTheta, lfSinTheta;
		f64			lfRed, lfGrn, lfBlu, lfRedStep, lfGrnStep, lfBluStep;
		s32			lnX, lnY;
		SLinef64	line;
		SBGR		color;
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
			lfRed		= (f64)colorStart.red;
			lfGrn		= (f64)colorStart.grn;
			lfBlu		= (f64)colorStart.blu;
			lfRedStep	= ((f64)colorEnd.red - lfRed) / lfSteps;
			lfGrnStep	= ((f64)colorEnd.grn - lfGrn) / lfSteps;
			lfBluStep	= ((f64)colorEnd.blu - lfBlu) / lfSteps;


		//////////
		// Proceed for the number of pixels times sqrt(2)
		//////
			lfStepInc = 1.0 / lfSteps;
			for (lfPercent = 0.0f; lfPercent < 1.0f; lfPercent += lfStepInc, lfRed += lfRedStep, lfGrn += lfGrnStep, lfBlu += lfBluStep)
			{
				// Compute the radius for this point
				lfRadius = lfPercent * line.length;

				// Compute the color
				color.red = (u8)lfRed;
				color.grn = (u8)lfGrn;
				color.blu = (u8)lfBlu;

				// Compute this point
				lnX = (s32)(line.p1.x + (lfRadius * lfCosTheta));
				lnY = (s32)(line.p1.y + (lfRadius * lfSinTheta));

				// Render it if it's visible
				if (lnX >= 0 && lnX < h->w && lnY >= 0 && lnY < h->h)
				{
					// Get the pointer
					lbgr = (SBGR*)((s8*)h->bd + (lnY * h->rowWidth) + (lnX * 3));

					// Render it
					lbgr->red	= color.red;
					lbgr->grn	= color.grn;
					lbgr->blu	= color.blu;
				}
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
	void iFillQuad(SHwnd* h, SXYF64* p1, SXYF64* p2, SXYF64* p3, SXYF64* p4, SBGR color)
	{
		f64			lfPercent, lfStep, lfCosThetaP1P4, lfSinThetaP1P4, lfCosThetaP2P3, lfSinThetaP2P3, lfMultiplier;
		SXYF64		lp1, lp2;
		SLinef64	p1p4, p2p3;


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


		//////////
		// Iterate by sqrt(2) times the maximum line length
		//////
			lfStep = 1.0 / (max(p1p4.length, p2p3.length) * lfMultiplier);
			for (lfPercent = 0.0; lfPercent < 1.0; lfPercent += lfStep)
			{
				// Compute the points
				lp1.x	= p1p4.p1.x + (lfPercent * p1p4.length * lfCosThetaP1P4);
				lp1.y	= p1p4.p1.y + (lfPercent * p1p4.length * lfSinThetaP1P4);
				lp2.x	= p2p3.p1.x + (lfPercent * p2p3.length * lfCosThetaP2P3);
				lp2.y	= p2p3.p1.y + (lfPercent * p2p3.length * lfSinThetaP2P3);

				// Draw this line
				iDrawLine(h, &lp1, &lp2, color, color);
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
		SXYS32	p1;
		s32		lnX, lnY, lnYLast;
		f64		lfTheta, lfThetaStep, lfA, lfB, lfV1, lfV2, lfX, lfY, lfRadius;


		// Can we render it?
		if (gMouse.xi >= 0 && gMouse.xi < h->w && gMouse.yi >= 0 && gMouse.yi < h->h)
		{
			// Invert the Y mouse coordinates for rendering
			p1.xi = gMouse.xi;
			p1.yi = h->h - gMouse.yi;

			// Render it (we're basically drawing an oval area the mouse will interact with)
			lfRadius	= (f64)min(max(gMouseType, _MOUSE_TYPE_SMALL), _MOUSE_TYPE_LARGE);
			lnYLast		= -1;
			lfA			= lfRadius * 1.0;		// A is 100%
			lfB			= lfRadius * 0.7;		// B is 70%, this gives us a 10:7 oval
			lfThetaStep	= _PI / ((f64)gMouseType * 8.0);
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
					iColorizeAndProcessHorizontalLineByPixels(p, h, c, p1.xi - lnX, p1.xi + lnX, p1.yi + lnY, mouseColor);		// Above
					if (lnY != 0)
						iColorizeAndProcessHorizontalLineByPixels(p, h, c, p1.xi - lnX, p1.xi + lnX, p1.yi - lnY, mouseColor);	// Below

					lnYLast = lnY;
				}
			}
		}
	}

	void iColorizeAndProcessHorizontalLineByPixels(SInstance* p, SHwnd* h, SChars* c, s32 x1, s32 x2, s32 y, SBGR color)
	{
		s32		lnX;
		f64		lfAlp, lfMalp, lfGray, lfRed, lfGrn, lfBlu;
		SBGR*	lbgr;


		// Is it out of bounds?
		if (y < 0 || y > h->h)
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
// 				// Grayscale the color
// 				lfGray = (((f64)lbgr->red * 0.35) + (f64)lbgr->grn * 0.54 + (f64)lbgr->blu * 0.11) / 255.0;

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
	void iRenderMarkup(SInstance* p, SHwnd* h, SChars* c)
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
		SBGR		color = { 22, 222, 22 };


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
			lfRed = (f64)color.red;
			lfGrn = (f64)color.grn;
			lfBlu = (f64)color.blu;
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

	u32 iScaleIntoRange(s32 tnValue, s32 tnValueMax, s32 tnMinRange, s32 tnMaxRange)
	{
		if (tnValue > tnValueMax)
			tnValue = tnValueMax;

		return(tnMinRange + (s32)(((f64)tnValue / (f64)tnValueMax) * (f64)(tnMaxRange - tnMinRange)));
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
				if (h->_hwndParent == tnHwndParent && h->oldWndParentProcAddress != 0)
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
				if (h->markup)
				{
					// Update the WNDPROC handler so we receive messages
					h->oldWndProcAddress = (WNDPROC)GetWindowLong(h->hwnd, GWL_WNDPROC);
					SetWindowLong(h->hwnd, GWL_WNDPROC, (long)&iWindowProcCallback);
					h->oldWndParentProcAddress = (WNDPROC)GetWindowLong(h->hwndParent, GWL_WNDPROC);
					SetWindowLong(h->hwndParent, GWL_WNDPROC, (long)&iWindowProcCallback);
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
				h->backDarkGrayBrush = CreateSolidBrush(RGB(32, 32, 32));

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
	void iComputeLine(SLinef64* line)
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
// Callback for the window
//
//////
	LRESULT CALLBACK iWindowProcCallback(HWND hwnd, UINT m, WPARAM w, LPARAM l)
	{
		u32				lnI;
		POINTS			p;
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


		// Iterate through each window to see which one this is
		if (m == WM_MOUSEMOVE)
			_asm nop;

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
				switch (m)
				{
					case WM_LBUTTONDBLCLK:
					case WM_RBUTTONDBLCLK:
					case WM_MBUTTONDBLCLK:
						break;

					case WM_MOUSEMOVE:
						p = MAKEPOINTS(l);
						if (p.x >= h->x && p.x < h->x + h->w)
						{
							if (p.y >= h->y && p.y < h->y + h->h)
							{
								gMouse.xi = p.x - h->x;
								gMouse.yi = p.y - h->y;
								// Send a message back to the parent to indicate this child needs to be redrawn
								SendMessage(h->hwndParent, WM_REDRAW_WINDOW, (u32)s, h->_hwnd);
							}
						}
						break;

					case WM_LBUTTONDOWN:
					case WM_RBUTTONDOWN:
					case WM_MBUTTONDOWN:
						p = MAKEPOINTS(l);
						if (p.x >= h->x && p.x < h->x + h->w)
						{
							if (p.y >= h->y && p.y < h->y + h->h)
							{
								gMouse.xi = p.x - h->x;
								gMouse.yi = p.y - h->y;
								// Send a message back to the parent to indicate this child needs to be redrawn
								SendMessage(h->hwndParent, WM_REDRAW_WINDOW, (u32)s, h->_hwnd);
							}
						}
						break;

					case WM_LBUTTONUP:
					case WM_RBUTTONUP:
					case WM_MBUTTONUP:
						gMouse.xi = -1;
						gMouse.yi = -1;
						// Send a message back to the parent to indicate this child needs to be redrawn
						SendMessage(h->hwndParent, WM_REDRAW_WINDOW, (u32)s, h->_hwnd);
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
