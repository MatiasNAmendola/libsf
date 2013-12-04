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
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
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
	int dsf_scale_and_clip_bitmap(char* tcBitmapFilenameIn, char* tcBitmapFilenameOut, f32 tfWidth, f32 tfHeight, int tnClipLeft, int tnClipTop, int tnNewWidth, int tnNewHeight)
	{
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
			p = (SInstance*)malloc(sizeof(SInstance));


		//////////
		// Initialize it
		//////
			memset(p, 0, sizeof(SInstance));


		//////////
		// Brand it
		//////
			memcpy(&p->id, cgcDsfBrand, sizeof(p->id));
			p->id_size = sizeof(SInstance);


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
	int dsf_set_font_data(u32 tnInstance,	f32 tfAscent,	f32 tfUpper,	f32 tfLower,		f32 tfLeft,			f32 tfRight,
											f32 tfBase,		f32 tfDescent,	f32 tfWidth,
											f32 tfItalics,	f32 tfBold,		f32 tfUnderTop,		f32 tfUnderBot,		f32 tfStrikeTop,	f32 tfStrikeBot)
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
											f32 tfOx, f32 tfOy, f32 tfOt, f32 tfLr, f32 tfLt, f32 tfRr, f32 tfRt, 
											u32 tiSubdivs, u32 tiLnkId, u32 tiLnkOrder)
	{
		SInstance*	p;
		SChar*		c;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Find or create the indicated character
		//////
			c = iFindCharInstance(p->chars, tiid, (u8)tnType, tiOrder, tiLnkId, tiLnkOrder);
			if (!c)
				return(-2);		// Error finding or creating


		//////////
		// Populate the data
		//////
			c->cType		= (u8)tnType;
			c->iid			= tiid;
			c->iOrder		= tiOrder;
			c->lNewStroke	= ((tlNewStroke == 0) ? false : true);
			c->lSelected	= ((tlSelected == 0) ? false : true);
			c->ox			= tfOx;
			c->oy			= tfOy;
			c->ot			= tfOt;
			c->lr			= tfLr;
			c->lt			= tfLt;
			c->rr			= tfRr;
			c->rt			= tfRt;
			c->iSubdivs		= tiSubdivs;
			c->iLnkId		= tiLnkId;
			c->iLnkOrder	= tiLnkOrder;

			// Store the description
			memcpy(&c->cDesc[0], tcDesc10, 10);
		

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
											f32 tfRef1X, f32 tfRef1Y,
											f32 tfRef2X, f32 tfRef2Y,
											f32 tfRef3X, f32 tfRef3Y,
											f32 tfRef4X, f32 tfRef4Y,
											f32 tfRef5X, f32 tfRef5Y,
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
			memcpy(&r->cDesc[0], tcDesc40, 40);

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
		f32			lfH, lfV;
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
			lfH = (f32)tnWidth	/ (f32)lnMakeWidth;
			lfV = (f32)tnHeight	/ (f32)lnHeight;
			iScaleImage(rawBuffer, tcBitmapFilename, lfH, lfV);
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
		f32					lfGray, lfLastGray;
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
					lfGray = (((f32)lbgr->red * 0.35f) + ((f32)lbgr->grn * 0.54f) + ((f32)lbgr->blu * 0.11f)) / 255.0f;

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
					lfGray = (((f32)lbgr->red * 0.35f) + ((f32)lbgr->grn * 0.54f) + ((f32)lbgr->blu * 0.11f)) / 255.0f;

					// Has something changed?
					if (fabs(lfGray - lfLastGray) > 0.9f)
					{
						// Store the position
						point.x = (f64)lnX	/ (f64)lbi.biWidth;
						point.y = (f64)lnY	/ (f64)lbi.biHeight;

						// Make sure it's on the reservation :-)
						if (point.x >= 0.0f && point.y >= 0.0f)
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
					lfGray = (((f32)lbgr->red * 0.35f) + ((f32)lbgr->grn * 0.54f) + ((f32)lbgr->blu * 0.11f)) / 255.0f;

					// Has something changed?
					if (fabs(lfGray - lfLastGray) > 0.9f)
					{
						// Store the position
						point.x = (f64)lnX	/ (f64)lbi.biWidth;
						point.y = (f64)lnY	/ (f64)lbi.biHeight;

						// Make sure it's on the reservation :-)
						if (point.x >= 0.0f && point.y >= 0.0f)
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
				lnX = (s32)(pSrc->x * (f32)lbi_debug.biWidth);
				lnY = (s32)(pSrc->y * (f32)lbi_debug.biHeight);

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
			u32			lnHandle;
		};


		//////////
		// Make sure our environment is sane, and if so that the handle is valid
		//////
			lnHandle = tnHandle;
			if (p && _memicmp(p->id, cgcDsfBrand, sizeof(p->id)) == 0 && p->id_size == sizeof(SInstance))
			{
				// Valid
				*tlValid = true;
				return(p);

			} else {
				// Invalid
				*tlValid = false;
				return(NULL);
			}
	}




//////////
//
// Called to search through the character splines, definition entries, links, etc., to find the
// matching character reference.
//
//////
	SChar* iFindCharInstance(SBuilder* charsBuilder, u32 tnIid, u8 tcType, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder)
	{
		SBuilder* thisCharBuilder;


		//////////
		// Make sure our environment is sane
		//////
			if (charsBuilder && charsBuilder->data)
			{
				// Grab that builder
				thisCharBuilder = iiGetThisCharBuilder(charsBuilder, tnIid);

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
						return(iFindCharInstance_SD(thisCharBuilder, tnIid, tiOrder, true));


					case 'D':
					case 'd':
						// It's the same as a spline, but the definition must be an item above 255, and it's
						// not part of a character, but rather just a segment to be used by characters.
						// We search by tnIid and tiOrder
						if (tnIid <= 255)
							return(NULL);		// Error

						// Search for (and add it if need be)
						return(iFindCharInstance_SD(thisCharBuilder, tnIid, tiOrder, true));


					case 'R':
					case 'r':
						// It's a reference. The reference must refer to an item above 255, per tiLnkId
						// We search by tnIid, tiOrder, and tiLnkId
						if (tnIid < 256)
							return(NULL);		// Error

						// Search for (and add it if need be)
						return(iFindCharInstance_R(thisCharBuilder, tnIid, tiOrder, tiLnkId, true));


					case 'L':
					case 'l':
						// It's a link. The reference can refer to any item, but must include the tiLnkId and tiLnkOrder
						// We search by tnIid, tiOrder, tiLnkId, and tiLnkOrder

						// Search for (and add it if need be)
						return(iFindCharInstance_L(thisCharBuilder, tnIid, tiOrder, tiLnkId, tiLnkOrder, true));

				}
			}


		// If we get here, not found
		return(NULL);
	}

	SBuilder* iiGetThisCharBuilder(SBuilder* charsBuilder, u32 tnIid)
	{
		u32			lnI, lnStart, lnEnd;
		SBuilder*	thisCharBuilder;


		// See if there's already room for this item
		if (charsBuilder->populatedLength < tnIid * sizeof(SChar))
		{
			// We have to make room for it
			lnStart = (charsBuilder->populatedLength / sizeof(SChar));
			lnEnd	= tnIid * sizeof(SChar);
			for (lnI = lnStart; lnI < lnEnd; lnI += sizeof(SChar))
			{
				// Grab the pointer
				thisCharBuilder = (SBuilder*)builder_allocateBytes(charsBuilder, sizeof(SChar));

				// Initialize it
				memset(thisCharBuilder, 0, sizeof(SChar));
			}
		}


		//////////
		// Return the builder
		//////
			return((SBuilder*)(charsBuilder->data + (tnIid * sizeof(SChar))));
	}

	SChar* iFindCharInstance_SD(SBuilder* thisCharBuilder, u32 tnIid, u32 tiOrder, bool tlAddIfNotFound)
	{
		u32		lnI;
		SChar*	c;


		//////////
		// Make sure our environment is sane
		//////
			if (thisCharBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisCharBuilder->populatedLength; lnI += sizeof(SChar))
			{
				// Grab the pointer
				c = (SChar*)(thisCharBuilder->data + lnI);

				// See if this is it
				if (c->iid == tnIid && c->iOrder == tiOrder)
					return(c);
			}


		//////////
		// If we get here, it wasn't found
		//////
			if (tlAddIfNotFound)
			{
				// Create a new entry
				return((SChar*)builder_allocateBytes(thisCharBuilder, sizeof(SChar)));

			} else {
				// 
				return(NULL);
			}
	}

	SChar* iFindCharInstance_R(SBuilder* thisCharBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, bool tlAddIfNotFound)
	{
		u32		lnI;
		SChar*	c;


		//////////
		// Make sure our environment is sane
		//////
			if (thisCharBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisCharBuilder->populatedLength; lnI += sizeof(SChar))
			{
				// Grab the pointer
				c = (SChar*)(thisCharBuilder->data + lnI);

				// See if this is it
				if (c->iid == tnIid && c->iOrder == tiOrder && c->iLnkId == tiLnkId)
					return(c);
			}


		//////////
		// If we get here, it wasn't found
		//////
			if (tlAddIfNotFound)
			{
				// Create a new entry
				return((SChar*)builder_allocateBytes(thisCharBuilder, sizeof(SChar)));

			} else {
				// 
				return(NULL);
			}
	}

	SChar* iFindCharInstance_L(SBuilder* thisCharBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder, bool tlAddIfNotFound)
	{
		u32		lnI;
		SChar*	c;


		//////////
		// Make sure our environment is sane
		//////
			if (thisCharBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisCharBuilder->populatedLength; lnI += sizeof(SChar))
			{
				// Grab the pointer
				c = (SChar*)(thisCharBuilder->data + lnI);

				// See if this is it
				if (c->iid == tnIid && c->iOrder == tiOrder && c->iLnkId == tiLnkId && c->iLnkOrder == tiLnkOrder)
					return(c);
			}


		//////////
		// If we get here, it wasn't found
		//////
			if (tlAddIfNotFound)
			{
				// Create a new entry
				return((SChar*)builder_allocateBytes(thisCharBuilder, sizeof(SChar)));

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
