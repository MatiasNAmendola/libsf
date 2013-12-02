//////////
//
// /libsf/utils/dsf/msvc++/dsf/dsf/scale.cpp
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
// This file is self-contained and handles all scaling algorithms.  It can be used as an include
// file for other stand-alone projects.  It was extracted from offline code related to the
// Village Freedom Project.
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




struct SRGB24
{
	u8		blu;				// 24-bit RGB values in bitmap files are physically stored as BGR
	u8		grn;
	u8		red;
};

struct SRGBF24
{
	f32		blu;				// 24-bit RGB values
	f32		grn;
	f32		red;
	f32		area;				// Area of a single pixel accounting for this color component, 1.0 if encompasses entire pixel
};

struct SBitmapProcess
{
	// Input
	BITMAPINFOHEADER*	bii;
	s8*					bdi;
	u32					actualWidthI;

	// Output
	BITMAPINFOHEADER*	bio;
	s8*					bdo;
	u32					actualWidthO;

	// Holds storage data for single spanned pixels
	u32					red;
	u32					grn;
	u32					blu;

	// tpoints is a buffer created to store the conversion pixel data during accumulation
	// Use formula:
	//		tpoints	= (SRGBF24*)malloc(		((u32)(1.0/ratioV) + 3)   *
	//										((u32)(1.0/ratioH) + 3))
	//
	f32					ratioV;			// (f32)bio->biHeight	/ (f32)bii->biHeight;
	f32					ratioH;			// (f32)bio->biWidth	/ (f32)bii->biWidth;
	u32					count;			// Number of valid points in tpoints
	SRGBF24*			pixels;			// Accumulation buffer for point data needed to feed into destination

	// Temporary variables used for processing
	SRGB24*				optr;				// Output pointer to the upper-left pixel for this x,y
	SRGB24*				iptra;				// Input pointer to the left-most pixel of the first row (the anchor)
	SRGB24*				iptr;				// Input pointer to the left-most pixel for this y row
	u32					x;					// X-coordinate
	u32					y;					// Y-coordinate
	f32					ulx;				// Upper-left X
	f32					uly;				// Upper-left Y
	f32					lrx;				// Lower-right X
	f32					lry;				// Lower-right Y
	f32					widthLeft;			// Width for each left-most pixel
	f32					widthRight;			// Width for each right-most pixel
	f32					height;				// Height for a particular pixel portion (upper, lower)
	f32					area;				// Temporary computed area for various pixels
	s32					left;				// Left-side pixel offset into line
	s32					right;				// Number of pixels to reach the right-most pixel
	s32					middleStartH;		// Starting pixel offset for middle span
	s32					middleFinishH;		// Ending pixel offset for middle span
	s32					middleStartV;		// Middle starting pixel
	s32					middleFinishV;		// Middle ending pixel

	// Indicates the span from upper-left corner
	bool				spans2H;			// Spans at least 2 pixels horizontally, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 2.x
	bool				spans3H;			// Spans at least 3 pixels horizontally, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 3.x
	bool				spans2V;			// Spans at least 2 pixels vertically, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 2.x
	bool				spans3V;			// Spans at least 3 pixels vertically, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 3.x
};




//////////
// Forward declarations
//////
	u32				iScaleImage										(s8* tcBmp24FilenameIn, s8* tcBmp24FilenameOut, f32 tfHorizontalScaler, f32 tfVerticalScaler);
	u32				iComputeActualWidth								(u32 tnWidth);
	u32				iIntegersBetween								(float p1, float p2);
	void			iGetSpannedPixelColors							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors1							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors2							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors3							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors4							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors5							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors6							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors7							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors8							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors9							(SBitmapProcess* bp);




//////////
//
// Takes a 24-bit bitmap, scales it to the specified size (a minimum 1x1 pixel size).
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
	u32 iScaleImage(s8* tcBmp24FilenameIn, s8* tcBmp24FilenameOut, f32 tfHorizontalScaler, f32 tfVerticalScaler)
	{
		u32					lnY, lnX, lnWidth, lnHeight, lnActualWidth, lnNumread, lnResult;
		f32					lfWidth, lfHeight;
		// bh, bi and bd are bitmap header, info and data, abbreviated, and with "i" for input, "o" for output
		SBitmapProcess		bp;
		BITMAPFILEHEADER	bhi, bho;
		BITMAPINFOHEADER	bii, bio;
		s8*					bdi;
		s8*					bdo;
		FILE*				lfh;


		// Try to open incoming
		lfh = fopen(tcBmp24FilenameIn, "rb");
		if (!lfh)
			return(-1);		// Failure opening input file

		// Read the header
		lnNumread = fread(&bhi, 1, sizeof(bhi), lfh);
		if (lnNumread != sizeof(bhi))
		{
			fclose(lfh);
			return(-4);		// Unable to read header from file
		}
		
		// Read the info
		lnNumread = fread(&bii, 1, sizeof(bii), lfh);
		if (lnNumread != sizeof(bii))
		{
			fclose(lfh);
			return(-4);		// Unable to read info from file
		}

		// We don't read the bits yet in case we don't need to
		// Make sure it's a 24-bit 1-plane bitmap
		if (bii.biSize < sizeof(bii) || bii.biPlanes != 1 || bii.biBitCount != 24)
		{
			// An unknown form of bitmap file is attempted.
			fclose(lfh);
			return(-2);
		}
		// When we get here, we're good, go ahead and allocate and read in the bits
		bdi = (s8*)malloc(bii.biSizeImage);
		if (!bdi)
		{
			// Unable to allocate memory
			fclose(lfh);
			return(-3);
		}
		fseek(lfh, sizeof(bhi) + bii.biSize, SEEK_SET);
		lnNumread = fread(bdi, 1, bii.biSizeImage, lfh);
		fclose(lfh);
		if (lnNumread != bii.biSizeImage)
			return(-4);		// Unable to read bits from file

		// Determine the new size
		lfWidth			= (f32)bii.biWidth  * fabs(tfHorizontalScaler);
		lfHeight		= (f32)bii.biHeight * fabs(tfVerticalScaler);
		lnWidth			= (u32)max(lfWidth  + 0.5, 1.0);
		lnHeight		= (u32)max(lfHeight + 0.5, 1.0);
		lnActualWidth	= iComputeActualWidth(lnWidth);

		// Create the new output
		memcpy(&bho, &bhi, sizeof(bho));
		memcpy(&bio, &bii, sizeof(bio));
		// Update the changed fields
		bio.biSize		= sizeof(bio);
		bio.biWidth		= lnWidth;
		bio.biHeight	= lnHeight;
		bio.biSizeImage	= lnActualWidth * lnHeight;
		bho.bfOffBits	= sizeof(bho) + sizeof(bio);
		bho.bfSize		= sizeof(bho) + sizeof(bio) + bio.biSizeImage;

		// Allocate the memory for the new output bits
		bdo = (s8*)malloc(bio.biSizeImage);
		if (!bdo)
		{
			// Error allocating memory
			free(bdi);
			return(-5);
		}
		// When we get here, everything is in place
		// Initialize everything to black
		memset(bdo, 0, bio.biSizeImage);

		// Being the scaling procedure
		bp.bii				= &bii;
		bp.bdi				= bdi;
		bp.actualWidthI		= iComputeActualWidth(bii.biWidth);
		bp.bio				= &bio;
		bp.bdo				= bdo;
		bp.actualWidthO		= lnActualWidth;	// iComputeActualWidth(bio.biWidth);
		bp.ratioV			= (f32)bii.biHeight		/ (f32)bio.biHeight;
		bp.ratioH			= (f32)bii.biWidth		/ (f32)bio.biWidth;
		bp.pixels			= (SRGBF24*)malloc(((u32)bp.ratioV + 1 + 3) * ((u32)bp.ratioH + 1 + 3) * sizeof(SRGBF24));
		for (lnY = 0; lnY < lnHeight; lnY++)
		{
			// Grab the offset for this line
			bp.optr = (SRGB24*)(bdo + ((bio.biHeight - lnY - 1) * bp.actualWidthO));

			// Repeat for every pixel across this row
			for (lnX = 0; lnX < lnWidth; lnX++)
			{
				// Compute data for this spanned pixel
				bp.uly	= min((f32)lnY * bp.ratioV, (f32)bii.biHeight - bp.ratioV);
				bp.ulx	= min((f32)lnX * bp.ratioH, (f32)bii.biWidth  - bp.ratioH);
				bp.lry	= bp.uly + bp.ratioV;
				bp.lrx	= bp.ulx + bp.ratioH;

				// Get all the color information for this potentially spanned pixel
				iGetSpannedPixelColors(&bp);

				// Store the color
				bp.optr->red = (u8)bp.red;
				bp.optr->grn = (u8)bp.grn;
				bp.optr->blu = (u8)bp.blu;

				// Move to the next pixel
				++bp.optr;
			}
		}
		// When we get here, we've computed everything

		// Write the output file
		lfh = fopen(tcBmp24FilenameOut, "wb+");
		if (lfh)
		{
			// Write the output file
			lnResult	= -7;
			lnNumread	= fwrite(&bho, 1, sizeof(bho), lfh);
			if (lnNumread == sizeof(bho))
			{
				lnNumread = fwrite(&bio, 1, sizeof(bio), lfh);
				if (lnNumread == sizeof(bio))
				{
					lnNumread = fwrite(bdo, 1, bio.biSizeImage, lfh);
					if (lnNumread == bio.biSizeImage)
					{
						// We're good all the way through
						lnResult = sizeof(bho) + sizeof(bio) + bio.biSizeImage;

					} else {
						lnResult = -7;
					}

				} else {
					lnResult = -7;
				}

			} else {
				lnResult = -7;
			}
			// Close the file, success or failure
			fclose(lfh);

		} else {
			// There was an error opening the file
			lnResult = -6;
		}

		// Release everything
		free(bdi);
		free(bdo);

		// Finished, indicate the file size
		return(lnResult);
	}




///////////
//
// For 24-bit bitmaps, the width of the data stored on disk must be
// rounded up to a value evenly divisible by 4.  This is called being
// "DWORD aligned" (read as "dee word aligned").  The term DWORD is a
// computer term for a double-word, which means 32-bits, because it is
// double the 16-bit word form, with a word being essentially a double-
// byte (8-bits).
//
// In any event, in 24-bit bitmaps, there are 3 pixels per bit, so the
// actual width, while a trivial calculation, is not easily encoded in
// a single source code line which makes sense.
//
//////
	u32 iComputeActualWidth(u32 tnWidth)
	{
		// Multiply by 3
		tnWidth = tnWidth * 3;

		// DWORD-align
		if (tnWidth % 4 != 0)
			tnWidth += 4 - (tnWidth % 4);

		// All done
		return(tnWidth);
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
	u32 iIntegersBetween(float p1, float p2)
	{
		u32 v1, v2;


		// Grab the integer values (without rounding)
		v1 = (u32)min(p1,p2);
		v2 = (u32)max(p1,p2);

		// Indicate the number between
		return(v2 - v1);
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
	void iGetSpannedPixelColors(SBitmapProcess* bp)
	{
		u32		lnI;
		f32		lfRed, lfGrn, lfBlu, lfAreaAccumulator;


		// Raise the flags for which portions are valid / required
		bp->spans2H		= (iIntegersBetween(bp->ulx, bp->lrx) >= 1);		// It occupies at least two pixels horizontally (itself and one more)
		bp->spans3H		= (iIntegersBetween(bp->ulx, bp->lrx) >= 2);		// It occupies at least three pixels horizontally (itself, at least one in the middle, and one at the right)
		bp->spans2V		= (iIntegersBetween(bp->uly, bp->lry) >= 1);		// It occupies at least two pixels vertically (itself and one more)
		bp->spans3V		= (iIntegersBetween(bp->uly, bp->lry) >= 2);		// It occupies at least three pixels vertically (itself, at least one in the middle, and one at the right)

		// Reset the point count
		bp->count		= 0;

		// Indicate the start of this input line
		bp->iptra		= (SRGB24*)(bp->bdi + ((bp->bii->biHeight                   ) * bp->actualWidthI));
		bp->iptr		= (SRGB24*)(bp->bdi + ((bp->bii->biHeight - (s32)bp->uly - 1) * bp->actualWidthI));


		//////////
		// Note:  The following functions (if called) update the number of pieces of picture data to add to the output
		//////


		//////////
		// 1 - upper-left (always, spans at most one pixel)
		//////
			iGetSpannedPixelColors1(bp);


		//////////
		// 2 - upper-middle (optional, spans at most multiple partial or full pixels, but only if 1, 2 and 3 exist)
		//////
			if (bp->spans3H)
				iGetSpannedPixelColors2(bp);


		//////////
		// 3 - upper-right (optional, spans at most one pixel, but only if 1 and 3 exist (as 1 and 2))
		//////
			if (bp->spans2H || bp->spans3H)
				iGetSpannedPixelColors3(bp);


		//////////
		// 4 - middle-left (optional, spans at most multiple partial or full pixels)
		//////
			if (bp->spans3V && bp->spans2V)
				iGetSpannedPixelColors4(bp);


		//////////
		// 5 - middle-middle (optional, can span multiple partial or full pixels)
		//////
			if (bp->spans3V && bp->spans3H)
				iGetSpannedPixelColors5(bp);


		//////////
		// 6 - middle-right (optional, spans at most multiple partial or full pixels)
		//////
			if (bp->spans3V && (bp->spans2H || bp->spans3H))
				iGetSpannedPixelColors6(bp);


		//////////
		// 7 - lower-left (optional, spans at most one pixel)
		//////
			if (bp->spans2V)
				iGetSpannedPixelColors7(bp);


		//////////
		// 8 - lower-middle (optional, spans at most multiple partial or full pixels)
		//////
			if (bp->spans2V && bp->spans3H)
				iGetSpannedPixelColors8(bp);


		//////////
		// 9 - lower-right (optional, spans at most one pixel)
		//////
			if (bp->spans2V && (bp->spans2H || bp->spans3H))
				iGetSpannedPixelColors9(bp);


		//////////
		// Now, add up all the pixels to compute the specified value
		//////
			lfAreaAccumulator = 0.0;
			for (lnI = 0; lnI < bp->count; lnI++)
				lfAreaAccumulator += bp->pixels[lnI].area;

			// Now, compute each component as its part of the total area
			lfRed	= 0;
			lfGrn	= 0;
			lfBlu	= 0;
			for (lnI = 0; lnI < bp->count; lnI++)
			{
				// Derive this portion component
				lfRed	+=		bp->pixels[lnI].red		*	(bp->pixels[lnI].area / lfAreaAccumulator);
				lfGrn	+=		bp->pixels[lnI].grn		*	(bp->pixels[lnI].area / lfAreaAccumulator);
				lfBlu	+=		bp->pixels[lnI].blu		*	(bp->pixels[lnI].area / lfAreaAccumulator);
			}
			// When we get here, we have our values, now create the final summed up output
			bp->red = (u8)(lfRed + 0.5);
			bp->grn = (u8)(lfGrn + 0.5);
			bp->blu = (u8)(lfBlu + 0.5);
	}




//////////
//
// 1 - upper-left (see iGetSpannedPixelColors() above)
// Upper left pixels is ALWAYS computed. It may be the ONLY one computed, but it is always computed.
//
//////
	void iGetSpannedPixelColors1(SBitmapProcess* bp)
	{
		// Store left- and right-sides for this spanned pixel
		bp->left			= (s32)min(bp->ulx, bp->bii->biWidth - 1);
		bp->right			= (s32)min(bp->lrx, bp->bii->biWidth - 1);

		// Compute the middle section in pixels
		// Note: -2 is for -1 base 0, and -1 because we want the max value to be one before the width/height
		bp->middleStartH	= (s32)min(bp->ulx + 1, bp->bii->biWidth  - 2);		// next pixel right of upper-left
		bp->middleFinishH	= (s32)min(bp->lrx - 1, bp->bii->biWidth  - 2);		// next pixel left of upper-right (which is actually lower-right, but on this upper line)
		bp->middleStartV	= (s32)min(bp->uly + 1, bp->bii->biHeight - 2);		// next pixel right of left-side pixels
		bp->middleFinishV	= (s32)min(bp->lry - 1, bp->bii->biHeight - 2);		// next pixel left of right-side pixels

		// Find out where this upper-left pixel falls
		if (!bp->spans2H)	bp->widthLeft =      bp->lrx          - bp->ulx;	// Entire width is within this one pixel, so it's only a portion of the pixel's overall width
		else				bp->widthLeft = (f32)bp->middleStartH - bp->ulx;	// It spans from where it is to the right of the pixel square

		if (!bp->spans2V)	bp->height =      bp->lry          - bp->uly;		// It's entire height is within this one pixel, so it's only a portion of the pixel's overall height
		else				bp->height = (f32)bp->middleStartV - bp->uly;		// It spans from where it is to the bottom of the pixel square

		// Compute the area for this pixel component
		bp->area = bp->widthLeft * bp->height;

		// Store the colors for this point
		(bp->pixels[bp->count]).red		= (f32)((bp->iptr + bp->left)->red);
		(bp->pixels[bp->count]).grn		= (f32)((bp->iptr + bp->left)->grn);
		(bp->pixels[bp->count]).blu		= (f32)((bp->iptr + bp->left)->blu);
		(bp->pixels[bp->count]).area	= bp->area;

		// Move over for the next point
		++bp->count;
	}




//////////
//
// 2 - upper-middle (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least one, full, middle pixel
//
//////
	void iGetSpannedPixelColors2(SBitmapProcess* bp)
	{
		s32 lnPixel;


		// For every middle pixel, apply these values
		for (lnPixel = bp->middleStartH; lnPixel < bp->middleFinishH; lnPixel++)
		{
			// Store this pixel data
			(bp->pixels[bp->count]).red		= (f32)((bp->iptr + lnPixel)->red);
			(bp->pixels[bp->count]).grn		= (f32)((bp->iptr + lnPixel)->grn);
			(bp->pixels[bp->count]).blu		= (f32)((bp->iptr + lnPixel)->blu);
			(bp->pixels[bp->count]).area	= bp->height;

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
	void iGetSpannedPixelColors3(SBitmapProcess* bp)
	{
		// Find out where this upper-left pixel falls
		bp->widthRight	= bp->lrx - (f32)bp->right;		// It spans from the start of the right-most pixel to wherever it falls therein

		// Compute the area for this pixel component
		bp->area = bp->widthRight * bp->height;

		// Store this pixel data
		(bp->pixels[bp->count]).red		= (f32)((bp->iptr + bp->right)->red);
		(bp->pixels[bp->count]).grn		= (f32)((bp->iptr + bp->right)->grn);
		(bp->pixels[bp->count]).blu		= (f32)((bp->iptr + bp->right)->blu);
		(bp->pixels[bp->count]).area	= bp->area;

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

	void iGetSpannedPixelColors4(SBitmapProcess* bp)
	{
		s32 lnPixelY;


		// Repeat for each middle pixel
		for (lnPixelY = bp->middleStartV; lnPixelY <= bp->middleFinishV; lnPixelY++)
		{
			// Store the colors for this point
			(bp->pixels[bp->count]).red		= (f32)(((SRGB24*)((s8*)bp->iptra - (lnPixelY * bp->actualWidthI) + (bp->left * 3)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SRGB24*)((s8*)bp->iptra - (lnPixelY * bp->actualWidthI) + (bp->left * 3)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SRGB24*)((s8*)bp->iptra - (lnPixelY * bp->actualWidthI) + (bp->left * 3)))->blu);
			(bp->pixels[bp->count]).area	= bp->widthLeft;

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
	void iGetSpannedPixelColors5(SBitmapProcess* bp)
	{
		s32 lnPixelY, lnPixelX;


		// Iterate for each pixel row vertically
		for (lnPixelY = bp->middleStartV; lnPixelY <= bp->middleFinishV; lnPixelY++)
		{
			// And each individual pixel horizontally
			for (lnPixelX = bp->middleStartH; lnPixelX <= bp->middleFinishH; lnPixelX++)
			{
				// Store the colors for this point
				(bp->pixels[bp->count]).red		= (f32)(((SRGB24*)((s8*)bp->iptra - (lnPixelY * bp->actualWidthI) + (lnPixelX * 3)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SRGB24*)((s8*)bp->iptra - (lnPixelY * bp->actualWidthI) + (lnPixelX * 3)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SRGB24*)((s8*)bp->iptra - (lnPixelY * bp->actualWidthI) + (lnPixelX * 3)))->blu);
				(bp->pixels[bp->count]).area	= 1.0;

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
	void iGetSpannedPixelColors6(SBitmapProcess* bp)
	{
		s32 lnPixelY;


		// Repeat for each middle pixel
		for (lnPixelY = bp->middleStartV; lnPixelY <= bp->middleFinishV; lnPixelY++)
		{
			// Store the colors for this point
			(bp->pixels[bp->count]).red		= (f32)(((SRGB24*)((s8*)bp->iptra - (lnPixelY * bp->actualWidthI) + (bp->right * 3)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SRGB24*)((s8*)bp->iptra - (lnPixelY * bp->actualWidthI) + (bp->right * 3)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SRGB24*)((s8*)bp->iptra - (lnPixelY * bp->actualWidthI) + (bp->right * 3)))->blu);
			(bp->pixels[bp->count]).area	= bp->widthRight;

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
	void iGetSpannedPixelColors7(SBitmapProcess* bp)
	{
		// Compute the area
		bp->height	= bp->lry - (f32)((s32)bp->lry);
		bp->area	= bp->widthLeft * bp->height;

		// Store the colors for this point
		(bp->pixels[bp->count]).red		= (f32)(((SRGB24*)((s8*)bp->iptra - (bp->actualWidthI * (bp->middleFinishV + 1)) + (bp->left * 3)))->red);
		(bp->pixels[bp->count]).grn		= (f32)(((SRGB24*)((s8*)bp->iptra - (bp->actualWidthI * (bp->middleFinishV + 1)) + (bp->left * 3)))->grn);
		(bp->pixels[bp->count]).blu		= (f32)(((SRGB24*)((s8*)bp->iptra - (bp->actualWidthI * (bp->middleFinishV + 1)) + (bp->left * 3)))->blu);
		(bp->pixels[bp->count]).area	= bp->area;

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
	void iGetSpannedPixelColors8(SBitmapProcess* bp)
	{
		s32 lnPixelX;


		// For every middle pixel, apply these values
		for (lnPixelX = bp->middleStartH; lnPixelX <= bp->middleFinishH; lnPixelX++)
		{
			// Store the colors for this point
			(bp->pixels[bp->count]).red		= (f32)(((SRGB24*)((s8*)bp->iptra - (bp->actualWidthI * (bp->middleFinishV + 1)) + (lnPixelX * 3)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SRGB24*)((s8*)bp->iptra - (bp->actualWidthI * (bp->middleFinishV + 1)) + (lnPixelX * 3)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SRGB24*)((s8*)bp->iptra - (bp->actualWidthI * (bp->middleFinishV + 1)) + (lnPixelX * 3)))->blu);
			(bp->pixels[bp->count]).area	= bp->height;

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
	void iGetSpannedPixelColors9(SBitmapProcess* bp)
	{
		// Compute the area
		bp->area = bp->widthRight * bp->height;

		// Store the colors for this point
		(bp->pixels[bp->count]).red		= (f32)(((SRGB24*)((s8*)bp->iptra - (bp->actualWidthI * (bp->middleFinishV + 1)) + (bp->right * 3)))->red);
		(bp->pixels[bp->count]).grn		= (f32)(((SRGB24*)((s8*)bp->iptra - (bp->actualWidthI * (bp->middleFinishV + 1)) + (bp->right * 3)))->grn);
		(bp->pixels[bp->count]).blu		= (f32)(((SRGB24*)((s8*)bp->iptra - (bp->actualWidthI * (bp->middleFinishV + 1)) + (bp->right * 3)))->blu);
		(bp->pixels[bp->count]).area	= bp->area;

		// Move over for the next point
		++bp->count;
	}
