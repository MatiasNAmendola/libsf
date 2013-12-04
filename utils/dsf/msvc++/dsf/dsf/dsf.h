//////////
//
// /libsf/utils/dsf/msvc++/dsf/dsf/dsf.h
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




#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER                          // Specifies that the minimum required platform is Windows Vista.
#define WINVER 0x0600           // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINDOWS          // Specifies that the minimum required platform is Windows 98.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE                       // Specifies that the minimum required platform is Internet Explorer 7.0.
#define _WIN32_IE 0x0700        // Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Unsigned
typedef		unsigned __int64	u64;
typedef		unsigned long		u32;
typedef		unsigned short		u16;
typedef		unsigned char		u8;

// Signed
typedef		LARGE_INTEGER		i64;
typedef		__int64				s64;
typedef		long				s32;
typedef		short				s16;
typedef		char				s8;

// Floating point
typedef		float				f32;
typedef		double				f64;

// Constant signed
typedef		const s8			cs8;
typedef		const s16			cs16;
typedef		const s32			cs32;
typedef		const s64			cs64;

// Constant unsigned
typedef		const u8			cu8;
typedef		const u16			cu16;
typedef		const u32			cu32;
typedef		const u64			cu64;

// Constant floating point
typedef		const f32			cf32;
typedef		const f64			cf64;


//////////
// Source code files to include
//////
	#include "scale.cpp"
	#include "builder.cpp"




//////////
// Structures used by DSF
//////
	struct SFont
	{
		f32			fAscent;						// Maximum ascent within the 0..1 range
		f32			fUpper;							// Horizontal line of the top of the upper-case letters, and letters like h, l, k, etc
		f32			fLower;							// Horizontal line of the top of the lower-case letters, such as top of c, e, o, etc.
		f32			fLeft;							// Vertical line of the left-side of the characters
		f32			fRight;							// Vertical line of the right-side of the characters
		f32			fBase;							// Horizontal line of the base of all characters
		f32			fDescent;						// Horizontal line for the bottom of the descending characters, like y, g, q, etc.
		f32			fWidth;							// Horizontal width of the average stroke (couples with fLeft and fRight for guides)
		f32			fItalics;						// Radians to slant from PI/2 toward 0 (use negative values for reverse slant)
		f32			fBold;							// Standard percentage to add for standard bold setting
		f32			fUnderTop;						// Horizontal line for the top of the underline
		f32			fUnderBot;						// Horizontal line for the bottom of the underline
		f32			fStrikeTop;						// Horizontal line for the top of the strikethrough location
		f32			fStrikeBot;						// Horizontal line for the bottom of the strikethrough location
	};

	struct SChars
	{
		SBuilder*	splines;						// (SChar) Holds full char records
		SBuilder*	tems;							// (STems) Holds all template points for this character
	};

	struct SChar
	{
		s8			cType;							// S=Spline, D=Definition, R=Reference, L=Link
		u32			iid;							// Character number (ASCII character)
		u32			iOrder;							// Stroke order within the character
		s8			cDesc[10];						// A brief description of this section, usually used with lNewStroke for a new pen stroke
		bool		lNewStroke;						// Used for an "i", for example, when the dot is a different stroke than the lower stock
		bool		lSelected;						// Is this item selected?
		f32			ox;								// Origin-X
		f32			oy;								// Origin-Y
		f32			ot;								// Origin-Theta (rotation)
		f32			lr;								// Left-Radius
		f32			lt;								// Left-Theta
		f32			rr;								// Right-Radius
		f32			rt;								// Right-Theta
		u32			iSubdivs;						// Automatic sub-divisions between this spline and the next one
		u32			iLnkId;							// If cType=R, the iid of the definition object; If cType=L, the iid of the link object (used with iLnkOrder to indicate which linked item this one modifies)
		u32			iLnkOrder;						// If cType=L, the item within the link object that this entry modifies

		SBuilder*	tems;							// (STems) Character template information for this character
	};

	struct SRefs
	{
		s8			cType;							// Line types supported:  H=Horizontal, V=Vertical, 2=Two point, 3=Three point, 5=Five point
		s8			cDesc[40];						// Description of this reference
		f32			fref1x;							// Used for H,V,2,3,5
		f32			fref1y;							// Used for H,V,2,3,5
		f32			fref2x;							// Used for 2,3,5
		f32			fref2y;							// Used for 2,3,5
		f32			fref3x;							// Used for 3,5
		f32			fref3y;							// Used for 3,5
		f32			fref4x;							// Used for 5
		f32			fref4y;							// Used for 5
		f32			fref5x;							// Used for 5
		f32			fref5y;							// Used for 5
		bool		lVisible;						// Should this item be used
		s8			cChars1[128];					// Characters this item should be displayed on #1
		s8			cChars2[128];					// Characters this item should be displayed on #2

		SBuilder*	floans;							// Floan data for this particular entry
	};

	// Template point -- is an X,Y coordinate for part of an outline or line that was created as a template for the font.
	// Certain mathematical operations for spline placement use these for reference
	struct STems
	{
		f32		fx;									// X of X,Y coordinate for this outline point
		f32		fy;									// Y of X,Y coordinate for this outline point
		u32		recno;								// Original record number this item came from
	};

	// SInstance structures are always branded with DSF! as first four bytes, and then length of the structure after
	const s8 cgcDsfBrand[] = "DSF!";
	struct SInstance
	{
		s8				id[4];						// Always 'DSF!' (used to identify the handle)
		u32				id_size;					// sizeof(SInstance)

		SFont			font;						// Font information for this instance
		SBuilder*		chars;						// (SBuilder) Characters, one SBuilder for every character, with each character SBuilder pointing to its many SChar entries
		SBuilder*		refs;						// (SRefs) References
	};

	struct SBGR
	{
		unsigned char	blu;
		unsigned char	grn;
		unsigned char	red;
	};


//////////
// Forward declarations
//////
	// Bitmaps
	int				iGetCharacterBitmap						(int tnAscii, char* tcBitmapFilename, char* tcFontName, int tnHeight, int tnWidth);
	int				iSaveBitmap								(SBGR* bgr, int tnWidth, int tnHeight, int tnLeft, char* tcBitmapFilename, int tnMakeWidth);
	int				iComputeRowWidth						(int tnWidth);
	HBITMAP			iCreateBitmap							(HDC thdc, int tnWidth, int tnHeight, int tnPlanes, int tnBits, void**tbd);
	// Floans
	int				iGetFloanFromBitmap						(u32 tnAscii, char* tcBitmapFilename, char* tcFloanFilename);
	int				iiGetFloanFromBitmap_qsortCallback		(const void* l, const void* r);
	// General purpose
	SInstance*		iGetDsfInstance							(u32 tnHandle, bool* tlValid);
	SChar*			iFindCharInstance						(SBuilder* charsBuilder, u32 tnIid, u8 tcType, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder);
	SChars*			iiGetThisChars							(SBuilder* charsBuilder, u32 tnIid);
	SChar*			iFindSplineInstance_SD					(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, bool tlAddIfNotFound);
	SChar*			iFindSplineInstance_R					(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, bool tlAddIfNotFound);
	SChar*			iFindSplineInstance_L					(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder, bool tlAddIfNotFound);
	SRefs*			iFindRefsInstance						(SBuilder* refs, u8 tcType, s8* tcDesc40);
	STems*			iFindTemsInstance						(SBuilder* charsBuilder, u32 tnIid);
