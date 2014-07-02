//////////
//
// /libsf/source/vjr/bitmaps.cpp
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jun.17.2014
//////
// Change log:
//     Jun.17.2014 - Initial creation
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
// Allocates a new structure
//////
	SBitmap* iBmp_allocate(void)
	{
		SBitmap* bmp;


		// Allocate our new structure
		bmp = (SBitmap*)malloc(sizeof(SBitmap));

		// Initialize if successful
		if (bmp)
			memset(bmp, 0, sizeof(SBitmap));

		// Indicate our success or failure
		return(bmp);
	}
;




//////////
//
// Called to copy a bitmap, to duplicate it completely
//
//////
	SBitmap* iBmp_copy(SBitmap* bmpSrc)
	{
		SBitmap*	bmp;
		RECT		lrc;


		// Make sure our environment is sane
		bmp = NULL;
		if (bmpSrc && iBmp_validate(bmpSrc))
		{
			// Allocate a new structure
			bmp = iBmp_allocate();
			if (bmp)
			{
				// Create a bitmap of the target size
				iBmp_createBySize(bmp, bmpSrc->bi.biWidth, bmpSrc->bi.biHeight, bmpSrc->bi.biBitCount);
				
				// Copy the bitmap over
				SetRect(&lrc, 0, 0, bmpSrc->bi.biWidth, bmpSrc->bi.biHeight);
				iBmp_bitBlt(bmp, &lrc, bmpSrc);
			}
		}

		// Indicate our success or failure
		return(bmp);
	}




//////////
//
// Called to make sure there is a copy, and if not it creates it, and if so
// then makes sure they are the same size, and if not then deletes the existing
// one and creates a new copy of the same size.
//
// Note:  It does not bitblt into the copy, but only creates a bmp the same size.
//
//////
	SBitmap* iBmp_verifyCopyIsSameSize(SBitmap* bmpCopy, SBitmap* bmp)
	{
		SBitmap* bmpNew;


		// Make sure we have something that makes sense
		if (bmp)
		{
			if (bmpCopy)
			{
				// Make sure it's the same size
				if (bmp->bi.biWidth == bmpCopy->bi.biWidth && bmp->bi.biHeight == bmpCopy->bi.biHeight)
					return(bmpCopy);		// They're the same already

				// If we get here, we need to delete the copy
				iBmp_delete(bmpCopy, true, true);
				// Note:  From now on we use bmpNew, and return that
			}

			// When we get here, we need to create a new one
			bmpNew = iBmp_allocate();
			if (bmpNew)
				iBmp_createBySize(bmpNew, bmp->bi.biWidth, bmp->bi.biHeight, bmp->bi.biBitCount);

			// Indicate our success or failure
			return(bmpNew);

		} else {
			// Unknown what the size is, so we just leave it the way it is
			return(bmpCopy);
		}
	}




//////////
//
// Called to verify the bitmap size is correct, and if not then it will create one of
// the correct size and scale this one into it.
//
//////
	SBitmap* iBmp_verifySizeOrResize(SBitmap* bmp, u32 tnWidth, u32 tnHeight)
	{
		SBitmap* bmpNew;


		// Make sure our environment is sane
		if (!bmp || bmp->bi.biWidth != tnWidth || bmp->bi.biHeight != tnHeight)
		{
			// Something has changed
			bmpNew = iBmp_allocate();
			iBmp_createBySize(bmpNew, tnWidth, tnHeight, ((bmp) ? bmp->bi.biBitCount : 32));

			// Process the old
			if (bmp)
			{
				// Scale to the new one
				iBmp_scale(bmpNew, bmp);

				// Delete the old version
				iBmp_delete(bmp, true, true);
			}
			// All done!

		} else {
			// They're the same
			bmpNew = bmp;
		}

		// Indicate our success
		return(bmpNew);
	}




//////////
//
// Called to load a bitmap file that was loaded from disk, or simulated loaded from disk.
//
//////
	SBitmap* iBmp_rawLoad(cu8* bmpRawFileData)
	{
		BITMAPFILEHEADER*	bh;
		BITMAPINFOHEADER*	bi;
		SBitmap*			bmp;


		//////////
		// Grab the headers
		//////
			bh = (BITMAPFILEHEADER*)bmpRawFileData;
			bi = (BITMAPINFOHEADER*)(bh + 1);


		//////////
		// Initialize the bitmap, and populate
		//////
			bmp = iBmp_allocate();
			if (bmp)
			{
				// Copy to bmp
				memcpy(&bmp->bh, bh, sizeof(bmp->bh));
				memcpy(&bmp->bi, bi, sizeof(bmp->bi));
				bmp->bd = (s8*)(bmpRawFileData + bh->bfOffBits);

				// Compute the row width
				bmp->rowWidth = iBmp_computeRowWidth(bmp);

				// Convert to 32-bit if need be
				if (bmp->bi.biBitCount == 24)
					iBmp_convertTo32Bits(bmp);
			}

		//////////
		// Indicate our success or failure
		//////
			return(bmp);
	}




//////////
//
// Called to convert the indicated bitmap to 32-bits if need be
//
//////
	void iBmp_convertTo32Bits(SBitmap* bmp)
	{
		SBitmap bmp32;


		// Are we already there?
		if (bmp && bmp->bi.biBitCount != 32)
		{
			// No, but we only know how to handle 24-bit bitmaps
			if (bmp->bi.biBitCount == 24)
			{
				// We need to convert it
				// Create the 32-bit version
				memset(&bmp32, 0, sizeof(SBitmap));
				iBmp_createBySize(&bmp32, bmp->bi.biWidth, bmp->bi.biHeight, 32);

				// Copy it
				iBmp_copy24To32(&bmp32, bmp);

				// Free the (now old) bitmap
				iBmp_delete(bmp, true, false);

				// Copy our bitmap to the destination
				memcpy(bmp, &bmp32, sizeof(SBitmap));
			}
		}
	}




//////////
//
// Copies the 24-bit bitmap to a 32-bit bitmap.
// Note:  This function is no longer needed, but may be faster for equal sized
//        bitmaps that are known to be 24-bit and 32-bit.  The iBmp_bitBlt()
//        function now handles arbitrary 24-bit and 32-bit sources and destinations.
//
//////
	void iBmp_copy24To32(SBitmap* bmp32, SBitmap* bmp24)
	{
		s32		lnX, lnY;
		SBgr*	lbgr;
		SBgra*	lbgra;


		// Iterate through every row
		for (lnY = 0; lnY < bmp24->bi.biHeight; lnY++)
		{
			// Grab our pointers
			lbgr	= (SBgr*)(bmp24->bd  + ((bmp24->bi.biHeight - lnY - 1) * bmp24->rowWidth));
			lbgra	= (SBgra*)(bmp32->bd + ((bmp32->bi.biHeight - lnY - 1) * bmp32->rowWidth));

			// Iterate though every column
			for (lnX = 0; lnX < bmp24->bi.biWidth; lnX++, lbgr++, lbgra++)
			{
				// Copy the pixel
				lbgra->alp	= 255;
				lbgra->red	= lbgr->red;
				lbgra->grn	= lbgr->grn;
				lbgra->blu	= lbgr->blu;
			}
		}
	}




//////////
//
// Performs basic tests on the bitmap to see if it appears to be a valid structure.
//
//////
	bool iBmp_validate(SBitmap* bmp)
	{
		// Planes must be 1
		if (bmp->bi.biPlanes != 1)
			return(false);

		// Bits must be 24 or 32
		if (bmp->bi.biBitCount != 24 && bmp->bi.biBitCount != 32)
			return(false);

		// No compression (meaning default BMP file)
		if (bmp->bi.biCompression != 0)
			return(false);

		// Make sure the biSizeImage is accurate
		iBmp_computeRowWidth(bmp);
		if (bmp->rowWidth * bmp->bi.biHeight != bmp->bi.biSizeImage)
			return(false);

		// Make sure the pixels per meter are set
		if (bmp->bi.biXPelsPerMeter <= 0)			bmp->bi.biXPelsPerMeter = 2835;					// Default to 72 pixels per inch, a "twip" as it were
		if (bmp->bi.biYPelsPerMeter <= 0)			bmp->bi.biYPelsPerMeter = 2835;

		// We're good
		return(true);
	}




//////////
//
// Computes the row width of the pixels using BGR format (3 bytes per pixel) then rounded up to
// the nearest DWORD.
//
//////
	s32 iBmp_computeRowWidth(SBitmap* bmp)
	{
		s32 lnWidth;


		// See the bit counts
		if (bmp->bi.biBitCount == 24)
		{
			// 24-bit formats are rounded up to nearest DWORD
			lnWidth = bmp->bi.biWidth * 3;
			if (lnWidth % 4 == 0)
				return(lnWidth);

			// Increase the width
			lnWidth += (4 - (lnWidth % 4));
			return(lnWidth);


		} else if (bmp->bi.biBitCount == 32) {
			// 32-bit formats are also DWORD aligned, but naturally, of course. :-)
			return(bmp->bi.biWidth * 4);


		} else {
			// Uh oh, spaghetti-oh!
			return(bmp->bi.biSizeImage / bmp->bi.biHeight);
		}
	}




//////////
//
// Called to create a basic bitmap by the indicated size, and initially populate it to white
//
//////
	void iBmp_createBySize(SBitmap* bmp, u32 width, u32 height, u32 tnBitCount)
	{
		// Populate the initial structure
		if (tnBitCount == 24)		iBmp_populateBitmapStructure(bmp, width, height, 24);
		else						iBmp_populateBitmapStructure(bmp, width, height, 32);

		// Create the HDC and DIB Section
		bmp->hdc	= CreateCompatibleDC(GetDC(GetDesktopWindow()));
		bmp->hbmp	= CreateDIBSection(bmp->hdc, (BITMAPINFO*)&bmp->bi, DIB_RGB_COLORS, (void**)&bmp->bd, NULL, 0);
		SelectObject(bmp->hdc, bmp->hbmp);

		// Paint it white initially (the fast/easy way)
		memset(bmp->bd, 255, bmp->bi.biSizeImage);
	}




//////////
//
// Called to create an empty 24-bit bitmap
//
//////
	void iBmp_populateBitmapStructure(SBitmap* bmp, u32 tnWidth, u32 tnHeight, u32 tnBitCount)
	{
		memset(&bmp->bi, 0, sizeof(bmp->bi));
		bmp->bi.biSize				= sizeof(bmp->bi);
		bmp->bi.biWidth				= tnWidth;
		bmp->bi.biHeight			= tnHeight;
		bmp->bi.biCompression		= 0;
		bmp->bi.biPlanes			= 1;
		bmp->bi.biBitCount			= (u16)((tnBitCount == 24 || tnBitCount == 32) ? tnBitCount : 32);
		bmp->bi.biXPelsPerMeter		= 2835;	// Assume 72 dpi
		bmp->bi.biYPelsPerMeter		= 2835;
		bmp->rowWidth				= iBmp_computeRowWidth(bmp);
		bmp->bi.biSizeImage			= bmp->rowWidth * tnHeight;
//////////
// Note:  The compression formats can be:
// 0	BI_RGB	none (most common)
// 4	BI_JPEG	data bits following need to be fed into a JPG decoder to access bit rows, to save back to disk a JPG encoder is required, lossy compression (always loses bitmap color data)
// 5	BI_PNG	data bits following need to be fed into a PNG decoder to access bit rows, to save back to disk a PNG encoder is required, lossless compression (always maintains original color data)
//////
	}




//////////
//
// Called to delete the indicated bitmap and optionally free all resources.
// Note:  The tlFreeBits flags allows the bitmap data to be copied to something else, with
//        the container SBitmap being deleted, but not the bits and related data within.
//
//////
	void iBmp_delete(SBitmap* bmp, bool tlFreeBits, bool tlFreeSelf)
	{
		if (bmp)
		{
			// Do we need to free the internals?
			if (tlFreeBits)
			{
				// Free the internal/Windows bits
				DeleteObject((HGDIOBJ)bmp->hbmp);
				DeleteDC(bmp->hdc);
			}

			// Release the bitmap
			if (tlFreeSelf)
				free(bmp);
		}
	}




//////////
//
// Draw the indicated object
//
//////
	void iBmp_bitBltObject(SBitmap* bmpDst, SObject* objSrc, SBitmap* bmpSrc)
	{
		iBmp_bitBlt(bmpDst, &objSrc->rc, bmpSrc);
	}




//////////
//
// Draws all except bits with the mask color rgb(222,22,222)
//
//////
	void iBmp_bitBltObjectMask(SBitmap* bmpDst, SObject* obj, SBitmap* bmpSrc)
	{
		iBmp_bitBltMask(bmpDst, &obj->rc, bmpSrc);
	}




//////////
//
// Physically render the bitmap atop the bitmap
//
//////
	u32 iBmp_bitBlt(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc)
	{
		u32			lnPixelsRendered;
		s32			lnY, lnX, lnYDst, lnXDst;
		f64			lfAlp, lfMalp;
		SBgr*		lbgrDst;
		SBgr*		lbgrSrc;
		SBgra*		lbgraDst;
		SBgra*		lbgraSrc;


		//////////
		// Draw it
		//////
			lnPixelsRendered = 0;
			for (lnY = 0, lnYDst = trc->top; lnY < bmpSrc->bi.biHeight && lnYDst < trc->bottom; lnYDst++, lnY++)
			{
				// Are we on the image?
				if (lnYDst >= 0 && lnYDst < bmpDst->bi.biHeight)
				{
					// Build the pointer
					lbgrDst		= (SBgr*)((s8*)bmpDst->bd  + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgrSrc		= (SBgr*)((s8*)bmpSrc->bd  + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));
					lbgraDst	= (SBgra*)((s8*)bmpDst->bd + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgraSrc	= (SBgra*)((s8*)bmpSrc->bd + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));

					// What exactly are we copying?
					if (bmpSrc->bi.biBitCount == 24)
					{
						// 24-bit source
						if (bmpDst->bi.biBitCount == 24)
						{
							// 24-bit to 24-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth)
								{
									// Copy the pixel
									lbgrDst->red	= lbgrSrc->red;
									lbgrDst->grn	= lbgrSrc->grn;
									lbgrDst->blu	= lbgrSrc->blu;
									++lnPixelsRendered;
								}

								// Move to next pixel on both
								++lbgrDst;
								++lbgrSrc;
							}

						} else {
							// 24-bit to 32-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth)
								{
									// Copy the pixel
									lbgraDst->alp	= 255;
									lbgraDst->red	= lbgrSrc->red;
									lbgraDst->grn	= lbgrSrc->grn;
									lbgraDst->blu	= lbgrSrc->blu;
									++lnPixelsRendered;
								}

								// Move to next pixel on both
								++lbgraDst;
								++lbgrSrc;
							}
						}

					} else {
						// 32-bit source
						if (bmpDst->bi.biBitCount == 24)
						{
							// 32-bit to 24-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth && lbgraSrc->alp != 0)
								{
									// Copy the pixel
									lfAlp			= ((f64)lbgraSrc->alp / 255.0);
									lfMalp			= 1.0 - lfAlp;
									lbgrDst->red	= (u8)min(max(((f64)lbgrDst->red * lfMalp) + (lbgraSrc->red * lfAlp), 0.0), 255.0);
									lbgrDst->grn	= (u8)min(max(((f64)lbgrDst->grn * lfMalp) + (lbgraSrc->grn * lfAlp), 0.0), 255.0);
									lbgrDst->blu	= (u8)min(max(((f64)lbgrDst->blu * lfMalp) + (lbgraSrc->blu * lfAlp), 0.0), 255.0);
									++lnPixelsRendered;
								}

								// Move to next pixel on both
								++lbgrDst;
								++lbgraSrc;
							}

						} else {
							// 32-bit to 32-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth && lbgraSrc->alp != 0)
								{
									// Copy the pixel
									lfAlp			= ((f64)lbgraSrc->alp / 255.0);
									lfMalp			= 1.0 - lfAlp;
// 									lbgraDst->alp	= lbgraSrc->alp;
									lbgraDst->red	= (u8)min(max(((f64)lbgraDst->red * lfMalp) + (lbgraSrc->red * lfAlp), 0.0), 255.0);
									lbgraDst->grn	= (u8)min(max(((f64)lbgraDst->grn * lfMalp) + (lbgraSrc->grn * lfAlp), 0.0), 255.0);
									lbgraDst->blu	= (u8)min(max(((f64)lbgraDst->blu * lfMalp) + (lbgraSrc->blu * lfAlp), 0.0), 255.0);
									++lnPixelsRendered;
								}

								// Move to next pixel on both
								++lbgraDst;
								++lbgraSrc;
							}
						}
					}
				}
			}


		//////////
		// Indicate how many pixels were rendered
		//////
			return(lnPixelsRendered);
	}




//////////
//
// Physically render the bitmap atop the bitmap, with without the mask bits rgb(222,22,222)
//
//////
	void iBmp_bitBltMask(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc)
	{
		s32			lnY, lnX, lnYDst, lnXDst;
		f64			lfAlp, lfMalp;
		SBgr*		lbgrDst;
		SBgr*		lbgrSrc;
		SBgra*		lbgraDst;
		SBgra*		lbgraSrc;


		//////////
		// Draw it
		//////
			for (lnY = 0, lnYDst = trc->top; lnY < bmpSrc->bi.biHeight && lnYDst < trc->bottom; lnYDst++, lnY++)
			{
				// Are we on the image?
				if (lnYDst >= 0 && lnYDst < bmpDst->bi.biHeight)
				{
					// Build the pointer
					lbgrDst		= (SBgr*)((s8*)bmpDst->bd  + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgrSrc		= (SBgr*)((s8*)bmpSrc->bd  + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));
					lbgraDst	= (SBgra*)((s8*)bmpDst->bd + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgraSrc	= (SBgra*)((s8*)bmpSrc->bd + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));

					// What exactly are we copying?
					if (bmpSrc->bi.biBitCount == 24)
					{
						// 24-bit source
						if (bmpDst->bi.biBitCount == 24)
						{
							// 24-bit to 24-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth)
								{
									// Copy the pixel if it's not a mask pixel
									if (lbgrSrc->red != 222 && lbgrSrc->grn != 22 && lbgrSrc->blu != 222)
									{
										lbgrDst->red	= lbgrSrc->red;
										lbgrDst->grn	= lbgrSrc->grn;
										lbgrDst->blu	= lbgrSrc->blu;
									}
								}

								// Move to next pixel on both
								++lbgrDst;
								++lbgrSrc;
							}

						} else {
							// 24-bit to 32-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth)
								{
									// Copy the pixel if it's not a mask pixel
									if (lbgrSrc->red != 222 && lbgrSrc->grn != 22 && lbgrSrc->blu != 222)
									{
										lbgraDst->alp	= 255;
										lbgraDst->red	= lbgrSrc->red;
										lbgraDst->grn	= lbgrSrc->grn;
										lbgraDst->blu	= lbgrSrc->blu;
									}
								}

								// Move to next pixel on both
								++lbgraDst;
								++lbgrSrc;
							}
						}

					} else {
						// 32-bit source
						if (bmpDst->bi.biBitCount == 24)
						{
							// 32-bit to 24-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth && lbgraSrc->alp != 0)
								{
									// Copy the pixel if it's not a mask pixel
									if (lbgraSrc->red != 222 && lbgraSrc->grn != 22 && lbgraSrc->blu != 222)
									{
										lfAlp			= ((f64)lbgraSrc->alp / 255.0);
										lfMalp			= 1.0 - lfAlp;
										lbgrDst->red	= (u8)min(max(((f64)lbgrDst->red * lfMalp) + (lbgraSrc->red * lfAlp), 0.0), 255.0);
										lbgrDst->grn	= (u8)min(max(((f64)lbgrDst->grn * lfMalp) + (lbgraSrc->grn * lfAlp), 0.0), 255.0);
										lbgrDst->blu	= (u8)min(max(((f64)lbgrDst->blu * lfMalp) + (lbgraSrc->blu * lfAlp), 0.0), 255.0);
									}
								}

								// Move to next pixel on both
								++lbgrDst;
								++lbgraSrc;
							}

						} else {
							// 32-bit to 32-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth && lbgraSrc->alp != 0)
								{
									// Copy the pixel if it's not a mask pixel
									if (lbgraSrc->red != 222 && lbgraSrc->grn != 22 && lbgraSrc->blu != 222)
									{
										lfAlp			= ((f64)lbgraSrc->alp / 255.0);
										lfMalp			= 1.0 - lfAlp;
//										lbgraDst->alp	= lbgraSrc->alp;
										lbgraDst->red	= (u8)min(max(((f64)lbgraDst->red * lfMalp) + (lbgraSrc->red * lfAlp), 0.0), 255.0);
										lbgraDst->grn	= (u8)min(max(((f64)lbgraDst->grn * lfMalp) + (lbgraSrc->grn * lfAlp), 0.0), 255.0);
										lbgraDst->blu	= (u8)min(max(((f64)lbgraDst->blu * lfMalp) + (lbgraSrc->blu * lfAlp), 0.0), 255.0);
									}
								}

								// Move to next pixel on both
								++lbgraDst;
								++lbgraSrc;
							}
						}
					}
				}
			}
	}

	void iBmp_drawPoint(SBitmap* bmp, s32 tnX, s32 tnY, SBgra color)
	{
		SBgr*	lbgr;


		// Make sure our coordinates are valid
		if (tnX >= 0 && tnX < bmp->bi.biWidth && tnY >= 0 && tnY < bmp->bi.biHeight)
		{
			// Get our offset
			lbgr = (SBgr*)(bmp->bd + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));

			// Draw it
			lbgr->red	= color.red;
			lbgr->grn	= color.grn;
			lbgr->blu	= color.blu;
		}
	}

	void iBmp_fillRect(SBitmap* bmp, RECT* rc, SBgra colorNW, SBgra colorNE, SBgra colorSW, SBgra colorSE, bool tlUseGradient)
	{
		s32		lnY;
		f32		lfRed, lfGrn, lfBlu, lfRedTo, lfGrnTo, lfBluTo, lfRedInc, lfGrnInc, lfBluInc, lfPercent, lfPercentInc, lfHeight, lfWidth;


		//////////
		// Fill every row
		//////
			lfWidth			= (f32)(rc->right  - 1 - rc->left);
			lfHeight		= (f32)(rc->bottom - 1 - rc->top);
			lfPercentInc	= 1.0f / lfHeight;
			for (lfPercent = 0.0, lnY = rc->top; lnY < rc->bottom; lnY++, lfPercent += lfPercentInc)
			{
				if (tlUseGradient)
				{
					//////////
					// Compute FROM colors
					//////
						lfRed		= (f32)colorNW.red + (((f32)colorSW.red - (f32)colorNW.red) * lfPercent);
						lfGrn		= (f32)colorNW.grn + (((f32)colorSW.grn - (f32)colorNW.grn) * lfPercent);
						lfBlu		= (f32)colorNW.blu + (((f32)colorSW.blu - (f32)colorNW.blu) * lfPercent);


					//////////
					// Compute TO colors
					//////
						lfRedTo		= (f32)colorNE.red + (((f32)colorSE.red - (f32)colorNE.red) * lfPercent);
						lfGrnTo		= (f32)colorNE.grn + (((f32)colorSE.grn - (f32)colorNE.grn) * lfPercent);
						lfBluTo		= (f32)colorNE.blu + (((f32)colorSE.blu - (f32)colorNE.blu) * lfPercent);


					//////////
					// Compute increment
					//////
						lfRedInc	= (lfRedTo - lfRed) / lfWidth;
						lfGrnInc	= (lfGrnTo - lfGrn) / lfWidth;
						lfBluInc	= (lfBluTo - lfBlu) / lfWidth;


					//////////
					// Draw this line with its gradient
					//////
						iBmp_drawHorizontalLineGradient(bmp, rc->left, rc->right - 1, lnY, lfRed, lfGrn, lfBlu, lfRedInc, lfGrnInc, lfBluInc);

				} else {
					// Draw this line with the NW color
					iBmp_drawHorizontalLine(bmp, rc->left, rc->right - 1, lnY, colorNW);
				}
			}
	}

	void iBmp_frameRect(SBitmap* bmp, RECT* rc, SBgra colorNW, SBgra colorNE, SBgra colorSW, SBgra colorSE, bool tlUseGradient)
	{
		f32 lfRed, lfGrn, lfBlu, lfRedTo, lfGrnTo, lfBluTo, lfRedInc, lfGrnInc, lfBluInc, lfHeight, lfWidth;


		if (tlUseGradient)
		{
			// Compute standards
			lfWidth		= (f32)(rc->right  - 1 - rc->left);
			lfHeight	= (f32)(rc->bottom - 1 - rc->top);

			//////////
			// Top (NW to NE)
			//////
				// Compute FROM and TO colors
				lfRed = (f32)colorNW.red;			lfRedTo = (f32)colorNE.red;
				lfGrn = (f32)colorNW.grn;			lfGrnTo = (f32)colorNE.grn;
				lfBlu = (f32)colorNW.blu;			lfBluTo = (f32)colorNE.blu;

				// Compute increment
				lfRedInc	= (lfRedTo - lfRed) / lfWidth;
				lfGrnInc	= (lfGrnTo - lfGrn) / lfWidth;
				lfBluInc	= (lfBluTo - lfBlu) / lfWidth;

				// Draw it
				iBmp_drawHorizontalLineGradient(bmp, rc->left, rc->right - 1, rc->top, lfRed, lfGrn, lfBlu, lfRedInc, lfGrnInc, lfBluInc);


			//////////
			// Bottom (SW to SE)
			//////
				// Compute FROM and TO colors
				lfRed = (f32)colorSW.red;			lfRedTo = (f32)colorSE.red;
				lfGrn = (f32)colorSW.grn;			lfGrnTo = (f32)colorSE.grn;
				lfBlu = (f32)colorSW.blu;			lfBluTo = (f32)colorSE.blu;

				// Compute increment
				lfRedInc	= (lfRedTo - lfRed) / lfWidth;
				lfGrnInc	= (lfGrnTo - lfGrn) / lfWidth;
				lfBluInc	= (lfBluTo - lfBlu) / lfWidth;

				// Draw it
				iBmp_drawHorizontalLineGradient(bmp, rc->left, rc->right - 1, rc->bottom - 1, lfRed, lfGrn, lfBlu, lfRedInc, lfGrnInc, lfBluInc);


			//////////
			// Left (NW to SW)
			//////
				// Compute FROM and TO colors
				lfRed = (f32)colorNW.red;			lfRedTo = (f32)colorSW.red;
				lfGrn = (f32)colorNW.grn;			lfGrnTo = (f32)colorSW.grn;
				lfBlu = (f32)colorNW.blu;			lfBluTo = (f32)colorSW.blu;

				// Compute increment
				lfRedInc	= (lfRedTo - lfRed) / lfWidth;
				lfGrnInc	= (lfGrnTo - lfGrn) / lfWidth;
				lfBluInc	= (lfBluTo - lfBlu) / lfWidth;

				// Draw it
				iBmp_drawVerticalLineGradient(bmp, rc->top, rc->bottom - 1, rc->left, lfRed, lfGrn, lfBlu, lfRedInc, lfGrnInc, lfBluInc);


			//////////
			// Right (NE to SE)
			//////
				// Compute FROM and TO colors
				lfRed = (f32)colorNE.red;			lfRedTo = (f32)colorSE.red;
				lfGrn = (f32)colorNE.grn;			lfGrnTo = (f32)colorSE.grn;
				lfBlu = (f32)colorNE.blu;			lfBluTo = (f32)colorSE.blu;

				// Compute increment
				lfRedInc	= (lfRedTo - lfRed) / lfWidth;
				lfGrnInc	= (lfGrnTo - lfGrn) / lfWidth;
				lfBluInc	= (lfBluTo - lfBlu) / lfWidth;

				// Draw it
				iBmp_drawVerticalLineGradient(bmp, rc->top, rc->bottom - 1, rc->right - 1, lfRed, lfGrn, lfBlu, lfRedInc, lfGrnInc, lfBluInc);

		} else {
			// Just draw in a solid color
			iBmp_drawHorizontalLine(bmp, rc->left, rc->right - 1, rc->top, colorNW);
			iBmp_drawHorizontalLine(bmp, rc->left, rc->right - 1, rc->bottom - 1, colorNW);
			iBmp_drawVerticalLine(bmp, rc->top, rc->bottom - 1, rc->left, colorNW);
			iBmp_drawVerticalLine(bmp, rc->top, rc->bottom - 1, rc->right - 1, colorNW);
		}
	}

	void iBmp_drawHorizontalLine(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, SBgra color)
	{
		s32		lnX;
		SBgr*	lbgr;
		SBgra*	lbgra;


		// Get our starting point
		lbgr	= (SBgr*)(bmp->bd  + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX1 * (bmp->bi.biBitCount / 8)));
		lbgra	= (SBgra*)(bmp->bd + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX1 * (bmp->bi.biBitCount / 8)));

		if (bmp->bi.biBitCount == 24)
		{
			// Iterate for each column
			for (lnX = tnX1; lnX <= tnX2; lnX++)
			{
				// Are we on the bitmap?
				if (lnX >= 0 && lnX < bmp->bi.biWidth)
				{
					// Draw the pixel
					lbgr->red	= color.red;
					lbgr->grn	= color.grn;
					lbgr->blu	= color.blu;

					// Move to next column
					++lbgr;
				}
			}

		} else if (bmp->bi.biBitCount == 32) {
			// Iterate for each column
			for (lnX = tnX1; lnX <= tnX2; lnX++)
			{
				// Are we on the bitmap?
				if (lnX >= 0 && lnX < bmp->bi.biWidth)
				{
					// Draw the pixel
					lbgra->alp	= 255;
					lbgra->red	= color.red;
					lbgra->grn	= color.grn;
					lbgra->blu	= color.blu;

					// Move to next column
					++lbgra;
				}
			}
		}
	}

	void iBmp_drawVerticalLine(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, SBgra color)
	{
		s32		lnY;
		SBgr*	lbgr;
		SBgra*	lbgra;


		// Get our starting point
		lbgr	= (SBgr*)(bmp->bd  + ((bmp->bi.biHeight - tnY1 - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));
		lbgra	= (SBgra*)(bmp->bd + ((bmp->bi.biHeight - tnY1 - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));

		if (bmp->bi.biBitCount == 24)
		{
			// Iterate for each column
			for (lnY = tnY1; lnY <= tnY2; lnY++)
			{
				// Are we on the bitmap?
				if (lnY >= 0 && lnY < bmp->bi.biHeight)
				{
					// Draw the pixel
					lbgr->red	= color.red;
					lbgr->grn	= color.grn;
					lbgr->blu	= color.blu;

					// Move to next row
					lbgr = (SBgr*)((s8*)lbgr - bmp->rowWidth);
				}
			}

		} else if (bmp->bi.biBitCount == 32) {
			// Iterate for each column
			for (lnY = tnY1; lnY <= tnY2; lnY++)
			{
				// Are we on the bitmap?
				if (lnY >= 0 && lnY < bmp->bi.biHeight)
				{
					// Draw the pixel
					lbgra->alp	= 255;
					lbgra->red	= color.red;
					lbgra->grn	= color.grn;
					lbgra->blu	= color.blu;

					// Move to next row
					lbgra = (SBgra*)((s8*)lbgra - bmp->rowWidth);
				}
			}
		}
	}




//////////
//
// Gradient line algorithms
//
//////
	void iBmp_drawHorizontalLineGradient(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc)
	{
		s32		lnX;
		SBgr*	lbgr;
		SBgra*	lbgra;


		// Get our starting point
		lbgr	= (SBgr*)(bmp->bd  + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX1 * (bmp->bi.biBitCount / 8)));
		lbgra	= (SBgra*)(bmp->bd + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX1 * (bmp->bi.biBitCount / 8)));

		if (bmp->bi.biBitCount == 24)
		{
			// Iterate for each column
			for (lnX = tnX1; lnX <= tnX2; lnX++, tfRed += tfRedInc, tfGrn += tfGrnInc, tfBlu += tfBluInc)
			{
				// Are we on the bitmap?
				if (lnX >= 0 && lnX < bmp->bi.biWidth)
				{
					// Draw the pixel
					lbgr->red	= (u8)tfRed;
					lbgr->grn	= (u8)tfGrn;
					lbgr->blu	= (u8)tfBlu;

					// Move to next column
					++lbgr;
				}
			}

		} else if (bmp->bi.biBitCount == 32) {
			// Iterate for each column
			for (lnX = tnX1; lnX <= tnX2; lnX++, tfRed += tfRedInc, tfGrn += tfGrnInc, tfBlu += tfBluInc)
			{
				// Are we on the bitmap?
				if (lnX >= 0 && lnX < bmp->bi.biWidth)
				{
					// Draw the pixel
					lbgra->alp	= 255;
					lbgra->red	= (u8)tfRed;
					lbgra->grn	= (u8)tfGrn;
					lbgra->blu	= (u8)tfBlu;

					// Move to next column
					++lbgra;
				}
			}
		}
	}

	void iBmp_drawVerticalLineGradient(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc)
	{
		s32		lnY;
		SBgr*	lbgr;
		SBgra*	lbgra;


		// Get our starting point
		lbgr	= (SBgr*)(bmp->bd  + ((bmp->bi.biHeight - tnY1 - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));
		lbgra	= (SBgra*)(bmp->bd + ((bmp->bi.biHeight - tnY1 - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));

		if (bmp->bi.biBitCount == 24)
		{
			// Iterate for each column
			for (lnY = tnY1; lnY <= tnY2; lnY++, tfRed += tfRedInc, tfGrn += tfGrnInc, tfBlu += tfBluInc)
			{
				// Are we on the bitmap?
				if (lnY >= 0 && lnY < bmp->bi.biHeight)
				{
					// Draw the pixel
					lbgr->red	= (u8)tfRed;
					lbgr->grn	= (u8)tfGrn;
					lbgr->blu	= (u8)tfBlu;

					// Move to next row
					lbgr = (SBgr*)((s8*)lbgr - bmp->rowWidth);
				}
			}

		} else if (bmp->bi.biBitCount == 32) {
			// Iterate for each column
			for (lnY = tnY1; lnY <= tnY2; lnY++, tfRed += tfRedInc, tfGrn += tfGrnInc, tfBlu += tfBluInc)
			{
				// Are we on the bitmap?
				if (lnY >= 0 && lnY < bmp->bi.biHeight)
				{
					// Draw the pixel
					lbgra->alp	= 255;
					lbgra->red	= (u8)tfRed;
					lbgra->grn	= (u8)tfGrn;
					lbgra->blu	= (u8)tfBlu;

					// Move to next row
					lbgra = (SBgra*)((s8*)lbgra - bmp->rowWidth);
				}
			}
		}
	}




//////////
//
// Called to scale one bitmap into another.
//
// Note:  All of this code was adapted from the Visual FreePro.
// Note:  See https://github.com/RickCHodgin/libsf (in vvm\core\).
//
//////
	u32 iBmp_scale(SBitmap* bmpDst, SBitmap* bmpSrc)
	{
		u32		lnResult;
		f32		lfVertical, lfHorizontal;
		RECT	lrc;


		// Make sure our environment is sane
		lnResult = -1;
		if (bmpDst->bi.biBitCount == 24 || bmpDst->bi.biBitCount == 32)
		{
			if (bmpSrc->bi.biBitCount == 24 || bmpSrc->bi.biBitCount == 32)
			{
				// We have valid source and destination bitmaps
				if (bmpSrc->bi.biWidth == bmpDst->bi.biWidth && bmpSrc->bi.biHeight == bmpDst->bi.biHeight)
				{
					// They're the same size
					if (bmpSrc->bi.biBitCount == bmpDst->bi.biBitCount)
					{
						// They're the same bit counts, do a fast copy
						memcpy(bmpDst->bd, bmpSrc->bd, bmpSrc->bi.biSizeImage);

					} else {
						// Do a bitBlt to translate bit counts
						SetRect(&lrc, 0, 0, bmpDst->bi.biWidth, bmpDst->bi.biHeight);
						iBmp_bitBlt(bmpDst, &lrc, bmpSrc);
					}
					// Indicate success
					lnResult = 1;

				} else {
					// We need to scale
					lfVertical		= (f32)bmpSrc->bi.biHeight / (f32)bmpDst->bi.biHeight;
					lfHorizontal	= (f32)bmpSrc->bi.biWidth  / (f32)bmpDst->bi.biWidth;
					lnResult		= iiBmp_scale_Process(bmpDst, bmpSrc, lfVertical, lfHorizontal);
				}
			}
		}

		// Indicate our failure or success
		return(lnResult);
	}




//////////
//
// Takes a 24-bit bitmap, and scales it up or down to the specified size, with a
// minimum of a 1x1 pixel size.
//
// Returns:
//		-1		- Input file could not be opened
//		-2		- Invalid input bitmap
//		-3		- Unable to allocate memory for input bitmap
//		-4		- Error reading input bitmap
//		-5		- Unable to allocate memory for output bitmap
//		-6		- Unable to create the output file
//		-7		- Unable to write to output file
//
//////
	u32 iiBmp_scale_Process(SBitmap* bmpDst, SBitmap* bmpSrc, f32 tfVerticalScaler, f32 tfHorizontalScaler)
	{
		s32				lnY, lnX;
		SBitmapProcess	bp;


		// Being the scaling procedure
		bp.src		= bmpSrc;
		bp.ratioV	= (f32)bmpSrc->bi.biHeight	/ (f32)bmpDst->bi.biHeight;
		bp.ratioH	= (f32)bmpSrc->bi.biWidth	/ (f32)bmpDst->bi.biWidth;
		bp.pixels	= (SBgraf*)malloc(((u32)bp.ratioV + 16) * ((u32)bp.ratioH + 16) * sizeof(SBgraf));

		// Iterate through every pixel
		for (lnY = 0; lnY < bmpDst->bi.biHeight; lnY++)
		{
			// Grab the offset for this line
			if (bmpDst->bi.biBitCount == 24)		bp.optr		= (SBgr*)( bmpDst->bd + ((bmpDst->bi.biHeight - lnY - 1) * bmpDst->rowWidth));
			else									bp.optra	= (SBgra*)(bmpDst->bd + ((bmpDst->bi.biHeight - lnY - 1) * bmpDst->rowWidth));

			// Repeat for every pixel across this row
			for (lnX = 0; lnX < bmpDst->bi.biWidth; lnX++)
			{
				// Compute data for this spanned pixel
				bp.uly	= min((f32)lnY * bp.ratioV, (f32)bmpSrc->bi.biHeight - bp.ratioV);
				bp.ulx	= min((f32)lnX * bp.ratioH, (f32)bmpSrc->bi.biWidth  - bp.ratioH);
				bp.lry	= bp.uly + bp.ratioV;
				bp.lrx	= bp.ulx + bp.ratioH;

				// Get all the color information for this potentially spanned pixel
				iiBmp_scale_processPixels(&bp);

				// Store the color
				if (bmpDst->bi.biBitCount == 24)
				{
					bp.optr->red = (u8)bp.red;
					bp.optr->grn = (u8)bp.grn;
					bp.optr->blu = (u8)bp.blu;
					// Move to the next pixel
					++bp.optr;

				} else {
					bp.optra->red = (u8)bp.red;
					bp.optra->grn = (u8)bp.grn;
					bp.optra->blu = (u8)bp.blu;
					// Move to the next pixel
					++bp.optra;
				}
			}
		}
		// When we get here, we've computed everything

		// Finished, indicate the pixel count
		return(bmpDst->bi.biHeight * bmpDst->bi.biWidth * sizeof(SBgr));
	}




//////////
//
// Get spanned pixel data, meaning the input (bii, bdi) values are scanned based on the
// location of tnY,tnX and the relationship between bii and bio, meaning the input and
// output sizes.  If bii is bigger, then each bio pixel maps to more than one bii pixel.
// If they're identical, it's 1:1.  If bii is smaller, then each bio pixel maps to less
// than one full bii pixel.  There are no other options. :-)  This algorithm should not
// be used for 1:1 ratio conversions.
//
// Note that each of the above conditions applies to both width and height, meaning the
// relationship between bii and bio is analyzed on each axis, resulting in nine possible
// states (wider+taller, wider+equal, wider+shorter, equal+taller, equal+equal, equal+shorter,
// narrower+taller, narrower+equal, narrower+shorter).
//
// This natural relationship breaks down into nine general point forms:
//		Original pixels:			Output pixels span original pixels:
//		 ______________ 			 ______________ 			 ______________
//		|    |    |    |			|    |    |    |			|1   | 2  |   3|
//		|____|____|____|			|__+--------+__|			|__+--------+__|
//		|    |    |    |	==>		|  |        |  |	==>		|4 |   5    | 6|
//		|____|____|____|	==>		|__|        |__|	==>		|__|        |__|
//		|    |    |    |			|  +--------+  |			|7 +---8----+ 9|
//		|____|____|____|			|____|____|____|			|____|____|____|
//
// This form is comprised of 9 general parts, eight of which may not be present in all
// relationships, and five of which may span multiple columns, rows or both.
//
// These are:
//		1	- upper-left	(always,	spans at most one pixel)
//		2	- upper-middle	(optional,	spans at most multiple partial or full pixels)
//		3	- upper-right	(optional,	spans at most one pixel)
//		4	- middle-left	(optional,	spans at most multiple partial or full pixels)
//		5	- middle-middle	(optional,	can span multiple partial or full pixels)
//		6	- middle-right	(optional,	spans at most multiple partial or full pixels)
//		7	- lower-left	(optional,	spans at most one pixel)
//		8	- lower-middle	(optional,	spans at most multiple partial or full pixels)
//		9	- lower-right	(optional,	spans at most one pixel)
//
//////
	void iiBmp_scale_processPixels(SBitmapProcess* bp)
	{
		u32		lnI;
		f32		lfRed, lfGrn, lfBlu, lfAlp, lfAreaAccumulator;


		// Raise the flags for which portions are valid / required
		bp->spans2H		= (iiBmp_scale_processGetIntegersBetween(bp->ulx, bp->lrx) >= 1);		// It occupies at least two pixels horizontally (itself and one more)
		bp->spans3H		= (iiBmp_scale_processGetIntegersBetween(bp->ulx, bp->lrx) >= 2);		// It occupies at least three pixels horizontally (itself, at least one in the middle, and one at the right)
		bp->spans2V		= (iiBmp_scale_processGetIntegersBetween(bp->uly, bp->lry) >= 1);		// It occupies at least two pixels vertically (itself and one more)
		bp->spans3V		= (iiBmp_scale_processGetIntegersBetween(bp->uly, bp->lry) >= 2);		// It occupies at least three pixels vertically (itself, at least one in the middle, and one at the right)

		// Reset the point count
		bp->count		= 0;

		// Indicate the start of this input line
		if (bp->src->bi.biBitCount == 24)
		{
			// 24-bit bitmap
			bp->iptr		= (SBgr*)(bp->src->bd + ((bp->src->bi.biHeight - (s32)bp->uly - 1) * bp->src->rowWidth));	// current line
			bp->iptrAnchor	= (SBgr*)(bp->src->bd + ((bp->src->bi.biHeight                   ) * bp->src->rowWidth));	// root anchor (does not include the conversion from base-1)

		} else {
			// 32-bit bitmap
			bp->iptra		= (SBgra*)(bp->src->bd + ((bp->src->bi.biHeight - (s32)bp->uly - 1) * bp->src->rowWidth));	// current line
			bp->iptrAnchora	= (SBgra*)(bp->src->bd + ((bp->src->bi.biHeight                   ) * bp->src->rowWidth));	// root anchor (does not include the conversion from base-1)
		}


		//////////
		// The following functions (if called) update the number of pieces of picture data to add to the output
		//////
			//////////
			// 1 - upper-left (always, spans at most one pixel)
			//////
				iiBmp_scale_processSpannedPixel1(bp);

			//////////
			// 2 - upper-middle (optional, spans at most multiple partial or full pixels, but only if 1, 2 and 3 exist)
			//////
				if (bp->spans3H)
					iiBmp_scale_processSpannedPixel2(bp);


			//////////
			// 3 - upper-right (optional, spans at most one pixel, but only if 1 and 3 exist (as 1 and 2))
			//////
				if (bp->spans2H || bp->spans3H)
					iiBmp_scale_processSpannedPixel3(bp);


			//////////
			// 4 - middle-left (optional, spans at most multiple partial or full pixels)
			//////
				if (bp->spans3V && bp->spans2V)
					iiBmp_scale_processSpannedPixel4(bp);


			//////////
			// 5 - middle-middle (optional, can span multiple partial or full pixels)
			//////
				if (bp->spans3V && bp->spans3H)
					iiBmp_scale_processSpannedPixel5(bp);


			//////////
			// 6 - middle-right (optional, spans at most multiple partial or full pixels)
			//////
				if (bp->spans3V && (bp->spans2H || bp->spans3H))
					iiBmp_scale_processSpannedPixel6(bp);


			//////////
			// 7 - lower-left (optional, spans at most one pixel)
			//////
				if (bp->spans2V)
					iiBmp_scale_processSpannedPixel7(bp);


			//////////
			// 8 - lower-middle (optional, spans at most multiple partial or full pixels)
			//////
				if (bp->spans2V && bp->spans3H)
					iiBmp_scale_processSpannedPixel8(bp);


			//////////
			// 9 - lower-right (optional, spans at most one pixel)
			//////
				if (bp->spans2V && (bp->spans2H || bp->spans3H))
					iiBmp_scale_processSpannedPixel9(bp);


		//////////
		// Add up all the pixels to compute the specified value
		//////
			lfAreaAccumulator = 0.0;
			for (lnI = 0; lnI < bp->count; lnI++)
				lfAreaAccumulator += bp->pixels[lnI].area;

			// Initialize
			lfRed	= 0;
			lfGrn	= 0;
			lfBlu	= 0;
			lfAlp	= 0;

			// Now, compute each component as its part of the total area
			for (lnI = 0; lnI < bp->count; lnI++)
			{
				// Derive this portion component
				lfRed	+=		bp->pixels[lnI].red	*	(bp->pixels[lnI].area / lfAreaAccumulator);
				lfGrn	+=		bp->pixels[lnI].grn	*	(bp->pixels[lnI].area / lfAreaAccumulator);
				lfBlu	+=		bp->pixels[lnI].blu	*	(bp->pixels[lnI].area / lfAreaAccumulator);
				lfAlp	+=		bp->pixels[lnI].alp	*	(bp->pixels[lnI].area / lfAreaAccumulator);
			}

			// When we get here, we have our values, now create the final summed up output
			bp->red = (u8)(lfRed + 0.5);
			bp->grn = (u8)(lfGrn + 0.5);
			bp->blu = (u8)(lfBlu + 0.5);
			bp->alp = (u8)(lfAlp + 0.5);
	}




//////////
//
// 1 - upper-left (see iGetSpannedPixelColors() above)
// Upper left pixels is ALWAYS computed. It may be the ONLY one computed, but it is always computed.
//
//////
	void iiBmp_scale_processSpannedPixel1(SBitmapProcess* bp)
	{
		// Store left- and right-sides for this spanned pixel
		bp->left			= (s32)min(bp->ulx,			bp->src->bi.biWidth - 1);
		bp->right			= (s32)min(bp->lrx,			bp->src->bi.biWidth - 1);

		// Compute the middle section in pixels
		// Note: -2 is for -1 base 0, and -1 because we want the max value to be one before the width/height
		bp->middleStartH	= (s32)min(bp->ulx + 1,		bp->src->bi.biWidth  - 1);		// next pixel right of upper-left
		bp->middleFinishH	= (s32)min(bp->lrx - 1,		bp->src->bi.biWidth  - 1);		// next pixel left of upper-right (which is actually lower-right, but on this upper line)
		bp->middleStartV	= (s32)min(bp->uly + 1,		bp->src->bi.biHeight - 1);		// next pixel right of left-side pixels
		bp->middleFinishV	= (s32)min(bp->lry - 1,		bp->src->bi.biHeight - 1);		// next pixel left of right-side pixels

		// Find out where this upper-left pixel falls
		if (!bp->spans2H)	bp->widthLeft	=      bp->lrx          - bp->ulx;		// Entire width is within this one pixel, so it's only a portion of the pixel's overall width
		else				bp->widthLeft	= (f32)bp->middleStartH - bp->ulx;		// It spans from where it is to the right of the pixel square

 		if (!bp->spans2V)	bp->height		=      bp->lry          - bp->uly;			// It's entire height is within this one pixel, so it's only a portion of the pixel's overall height
		else				bp->height		= (f32)bp->middleStartV - bp->uly;			// It spans from where it is to the bottom of the pixel square

		// Compute the area for this pixel component
		bp->area = bp->widthLeft * bp->height;

		// Store the colors for this point
		if (bp->src->bi.biBitCount == 24)
		{
			// 24-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->left * 3)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->left * 3)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->left * 3)))->blu);
			(bp->pixels[bp->count]).area	= bp->area;

		} else {
			// 32-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->left * 4)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->left * 4)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->left * 4)))->blu);
			(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->left * 4)))->alp);
			(bp->pixels[bp->count]).area	= bp->area;
		}

		// Move over for the next point
		++bp->count;
	}




//////////
//
// 2 - upper-middle (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least one, full, middle pixel
//
//////
	void iiBmp_scale_processSpannedPixel2(SBitmapProcess* bp)
	{
		s32 lnPixel;


		// For every middle pixel, apply these values
		for (lnPixel = bp->middleStartH; lnPixel < bp->middleFinishH; lnPixel++)
		{
			// Store this pixel data
			if (bp->src->bi.biBitCount == 24)
			{
				// 24-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptr + (lnPixel * 3)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptr + (lnPixel * 3)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptr + (lnPixel * 3)))->blu);
				(bp->pixels[bp->count]).area	= bp->height;

			} else {
				// 32-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptra + (lnPixel * 4)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptra + (lnPixel * 4)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptra + (lnPixel * 4)))->blu);
				(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptra + (lnPixel * 4)))->alp);
				(bp->pixels[bp->count]).area	= bp->height;
			}

			// Move over for the next point
			++bp->count;
		}
	}




//////////
//
// 3 - upper-right (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row
//
//////
	void iiBmp_scale_processSpannedPixel3(SBitmapProcess* bp)
	{
		// Find out where this upper-left pixel falls
		bp->widthRight = bp->lrx - (f32)bp->right;		// It spans from the start of the right-most pixel to wherever it falls therein

		// Compute the area for this pixel component
		bp->area = bp->widthRight * bp->height;

		// Store this pixel data
		if (bp->src->bi.biBitCount == 24)
		{
			// 24-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->right * 3)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->right * 3)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->right * 3)))->blu);
			(bp->pixels[bp->count]).area	= bp->area;

		} else {
			// 32-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->right * 4)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->right * 4)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->right * 4)))->blu);
			(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->right * 4)))->alp);
			(bp->pixels[bp->count]).area	= bp->area;
		}

		// Move over for the next point
		++bp->count;
	}




//////////
//
// 4 - middle-left (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least an entire second row
//
//////
// 	void iValidatePoint(SBitmapProcess* bp, s32 tnX, s32 tnY)
// 	{
// 		if (tnX >= bp->bii->biWidth)
// 			_asm nop;
// 
// 		if (tnY >= bp->bii->biHeight)
// 			_asm nop;
// 	}

	void iiBmp_scale_processSpannedPixel4(SBitmapProcess* bp)
	{
		s32 lnPixelY;


		// Repeat for each middle pixel
		for (lnPixelY = bp->middleStartV; lnPixelY <= bp->middleFinishV; lnPixelY++)
		{
			// Store the colors for this point
			if (bp->src->bi.biBitCount == 24)
			{
				// 24-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->left * 3)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->left * 3)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->left * 3)))->blu);
				(bp->pixels[bp->count]).area	= bp->widthLeft;

			} else {
				// 32-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->left * 4)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->left * 4)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->left * 4)))->blu);
				(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->left * 4)))->alp);
				(bp->pixels[bp->count]).area	= bp->widthLeft;
			}

			// Move over for the next point
			++bp->count;
		}
	}




//////////
//
// 5 - middle-middle (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row, and at least
// one pixel in the middle
//
//////
	void iiBmp_scale_processSpannedPixel5(SBitmapProcess* bp)
	{
		s32 lnPixelY, lnPixelX;


		// Iterate for each pixel row vertically
		for (lnPixelY = bp->middleStartV; lnPixelY <= bp->middleFinishV; lnPixelY++)
		{
			// And each individual pixel horizontally
			for (lnPixelX = bp->middleStartH; lnPixelX <= bp->middleFinishH; lnPixelX++)
			{
				// Store the colors for this point
				if (bp->src->bi.biBitCount == 24)
				{
					// 24-bit bitmap
					(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 3)))->red);
					(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 3)))->grn);
					(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 3)))->blu);
					(bp->pixels[bp->count]).area	= 1.0;

				} else {
					// 32-bit bitmap
					(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 4)))->red);
					(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 4)))->grn);
					(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 4)))->blu);
					(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 4)))->alp);
					(bp->pixels[bp->count]).area	= 1.0;
				}

				// Move over for the next point
				++bp->count;
			}
		}
	}




//////////
//
// 6 - middle-right (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row, and a right pixel
//
//////
	void iiBmp_scale_processSpannedPixel6(SBitmapProcess* bp)
	{
		s32 lnPixelY;


		// Repeat for each middle pixel
		for (lnPixelY = bp->middleStartV; lnPixelY <= bp->middleFinishV; lnPixelY++)
		{
			// Store the colors for this point
			if (bp->src->bi.biBitCount == 24)
			{
				// 24-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->right * 3)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->right * 3)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->right * 3)))->blu);
				(bp->pixels[bp->count]).area	= bp->widthRight;

			} else {
				// 32-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->right * 4)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->right * 4)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->right * 4)))->blu);
				(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->right * 4)))->alp);
				(bp->pixels[bp->count]).area	= bp->widthRight;
			}

			// Move over for the next point
			++bp->count;
		}
	}




//////////
//
// 7 - lower-left (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row
//
//////
	void iiBmp_scale_processSpannedPixel7(SBitmapProcess* bp)
	{
		// Compute the area
		bp->height	= bp->lry - (f32)((s32)bp->lry);
		bp->area	= bp->widthLeft * bp->height;

		// Store the colors for this point
		if (bp->src->bi.biBitCount == 24)
		{
			// 24-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 3)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 3)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 3)))->blu);
			(bp->pixels[bp->count]).area	= bp->area;

		} else {
			// 32-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 4)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 4)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 4)))->blu);
			(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 4)))->alp);
			(bp->pixels[bp->count]).area	= bp->area;
		}

		// Move over for the next point
		++bp->count;
	}




//////////
//
// 8 - lower-middle (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row, and at least one
// pixel in the middle
//
//////
	void iiBmp_scale_processSpannedPixel8(SBitmapProcess* bp)
	{
		s32 lnPixelX;


		// For every middle pixel, apply these values
		for (lnPixelX = bp->middleStartH; lnPixelX <= bp->middleFinishH; lnPixelX++)
		{
			// Store the colors for this point
			if (bp->src->bi.biBitCount == 24)
			{
				// 24-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 3)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 3)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 3)))->blu);
				(bp->pixels[bp->count]).area	= bp->height;

			} else {
				// 32-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 4)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 4)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 4)))->blu);
				(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 4)))->alp);
				(bp->pixels[bp->count]).area	= bp->height;
			}

			// Move over for the next point
			++bp->count;
		}
	}




//////////
//
// 9 - lower-right (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row, and a right pixel
//
//////
	void iiBmp_scale_processSpannedPixel9(SBitmapProcess* bp)
	{
		// Compute the area
		bp->area = bp->widthRight * bp->height;

		// Store the colors for this point
		if (bp->src->bi.biBitCount == 24)
		{
			// 24-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 3)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 3)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 3)))->blu);
			(bp->pixels[bp->count]).area	= bp->area;

		} else {
			// 32-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 4)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 4)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 4)))->blu);
			(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 4)))->alp);
			(bp->pixels[bp->count]).area	= bp->area;
		}

		// Move over for the next point
		++bp->count;
	}




//////////
//
// Integers between means which maximum integer is touched?
// Basically, chopping off decimals reveals the range, such that values of
// 1.001 and 2.999 only touch integers 1 and 2, even though with rounding
// they would go from 1 to 3.  Their numerical roots are in only integers
// 1 and 2.
//
//////
	u32 iiBmp_scale_processGetIntegersBetween(f32 p1, f32 p2)
	{
		u32 lfMin, lfMax;


		// Grab the integer values (without rounding)
		lfMin = (u32)min(p1,p2);
		lfMax = (u32)max(p1,p2);

		// Indicate the number between
		return(lfMax - lfMin);
	}
