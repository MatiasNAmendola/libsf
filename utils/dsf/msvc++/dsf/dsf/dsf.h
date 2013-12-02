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
// Structures used by DSF
//////
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
	int				iGetFloanFromBitmap						(char* tcBitmapFilename, char* tcFloanFilename);
	int				iiGetFloanFromBitmap_qsortCallback		(const void* l, const void* r);


//////////
// Source code files to include
//////
	#include "scale.cpp"
	#include "builder.cpp"
