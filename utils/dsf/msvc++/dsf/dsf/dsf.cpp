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
				lnResult = iGetFloanFromBitmap(tcBitmapFilename, tcFloanFilename);


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
	int dsf_scale_and_clip_bitmap(char* tcBitmapFilenameIn, char* tcBitmapFilenameOut, float tfWidth, float tfHeight, int tnClipLeft, int tnClipTop, int tnNewWidth, int tnNewHeight)
	{
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
		float		lfH, lfV;
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
			hfont = CreateFontA(lnHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, tcFontName);
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
			lfH = (float)tnWidth	/ (float)lnMakeWidth;
			lfV = (float)tnHeight	/ (float)lnHeight;
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
		float	x;			// X coordinate of an X,Y pair
		float	y;			// Y coordinate of an X,Y pair
	};

	int iGetFloanFromBitmap(char* tcBitmapFilename, char* tcFloanFilename)
	{
		int					lnI, lnY, lnX, lnRowWidth, lnOldFloanCount, lnNewFloanCount;
		float				lfGray, lfLastGray;
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
			fread(lbgrBuffer, 1, lbi.biSize, lfh);
			fclose(lfh);


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
					lfGray = (float)(((lbgr->red * 0.35) + (lbgr->grn * 0.54) + (lbgr->blu * 0.11)) / 255.0);

					// Has something changed?
					if (max(lfGray, lfLastGray) - min(lfGray, lfLastGray) > 0.001)
					{
						// Store the position
						point.x = ((float)lnX + lfGray)	/ (float)lbi.biWidth;
						point.y = ((float)lnY			/ (float)lbi.biHeight);

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
					lfGray = (float)(((lbgr->red * 0.35) + (lbgr->grn * 0.54) + (lbgr->blu * 0.11)) / 255.0);

					// Has something changed?
					if (max(lfGray, lfLastGray) - min(lfGray, lfLastGray) > 0.001)
					{
						// Store the position
						point.x = ((float)lnX				/ (float)lbi.biWidth);
						point.y = (((float)lnY + lfGray)	/ (float)lbi.biHeight);

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
		// Remove duplicates
		//////
			lnOldFloanCount = floans->populatedLength / sizeof(SFloanPoint);
			qsort(floans->data, lnOldFloanCount, sizeof(SFloanPoint), iiGetFloanFromBitmap_qsortCallback);

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
				sprintf(buffer, "%8.4f, %8.4f\n\0", pSrc->x, pSrc->y);

				// Append it to the builder
				builder_appendData(floansCsv, buffer, strlen(buffer));
			}
			builder_asciiWriteOutFile(floansCsv, tcFloanFilename);


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
