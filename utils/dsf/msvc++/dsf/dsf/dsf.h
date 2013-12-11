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
typedef		const f64			cf64;
typedef		const f64			cf64;


//////////
// Source code files to include
//////
	#include "scale.cpp"
	#include "builder.cpp"




struct SBGR
{
	u8	blu;
	u8	grn;
	u8	red;
};

struct SBGR_AF64
{
	u8	blu;
	u8	grn;
	u8	red;
	f64	falp;
};

struct SXYF64
{
	f64			x;
	f64			y;
};

struct SXYS32
{
	s32			xi;
	s32			yi;
};

struct SLineS32
{
	// This line is not computed, but holds two points for easy reference
	SXYS32		p1i;
	SXYS32		p2i;
};

struct SLineF64
{
	// These are the two input points
	SXYF64		p1;
	SXYF64		p2;

	// These are computed with iComputeLine()
	SXYF64		delta;
	SXYF64		mid;
	f64			length;
	f64			m;							// Slope
	f64			mp;							// Perpendicular slope
	f64			theta;						// Theta (from p1 to p2, note: add _PI to reverse the angle from p2 to p1)
	SXYS32		p1i;
	SXYS32		p2i;
	s32			p1_quad;
	s32			p2_quad;
};

//////////
// Structures used by DSF
//////
	struct SFont
	{
		f64			fAscent;						// Maximum ascent within the 0..1 range
		f64			fUpper;							// Horizontal line of the top of the upper-case letters, and letters like h, l, k, etc
		f64			fLower;							// Horizontal line of the top of the lower-case letters, such as top of c, e, o, etc.
		f64			fLeft;							// Vertical line of the left-side of the characters
		f64			fRight;							// Vertical line of the right-side of the characters
		f64			fBase;							// Horizontal line of the base of all characters
		f64			fDescent;						// Horizontal line for the bottom of the descending characters, like y, g, q, etc.
		f64			fWidth;							// Horizontal width of the average stroke (couples with fLeft and fRight for guides)
		f64			fItalics;						// Radians to slant from PI/2 toward 0 (use negative values for reverse slant)
		f64			fBold;							// Standard percentage to add for standard bold setting
		f64			fUnderTop;						// Horizontal line for the top of the underline
		f64			fUnderBot;						// Horizontal line for the bottom of the underline
		f64			fStrikeTop;						// Horizontal line for the top of the strikethrough location
		f64			fStrikeBot;						// Horizontal line for the bottom of the strikethrough location
	};

	struct SChars
	{
		SBuilder*	splines;						// (SChar) Holds full char records
		SBuilder*	temsRaw;						// (STems) Holds all raw template points for this character (those sent from the calling app)

		// After the intial load is completed, (or in future upon resize), the temsRaw are aliased down to single instances for the visible size of the edit character window
		SBuilder*	tems;							// (STems) Holds aliased template points, one per pixel, as per temsRaw and the size of the edit character window (see dsf_initial_load_complete())
		SBuilder*	temsLines;						// (STemsLines) Holds all alpha layer rendering data for the comprising
	};

	struct SSpline
	{
		s8			cType;							// S=Spline, D=Definition, R=Reference, L=Link
		u32			iid;							// Character number (ASCII character)
		s32			iOrder;							// Stroke order within the character
		s8			cDesc[10];						// A brief description of this section, usually used with lNewStroke for a new pen stroke
		bool		lPenDown;						// Used for an "i", for example, when the dot is a different stroke than the lower stock, each time the pen goes down it's a new stroke
		bool		lSelected;						// Is this item selected?
		f64			ox;								// Origin-X
		f64			oy;								// Origin-Y
		f64			ot;								// Origin-Theta (rotation)
		f64			lr;								// Left-Radius
		f64			lt;								// Left-Theta
		f64			rr;								// Right-Radius
		f64			rt;								// Right-Theta
		u32			iSubdivs;						// Automatic sub-divisions between this spline and the next one
		u32			iLnkId;							// If cType=R, the iid of the definition object; If cType=L, the iid of the link object (used with iLnkOrder to indicate which linked item this one modifies)
		s32			iLnkOrder;						// If cType=L, the item within the link object that this entry modifies

		// Used to determine if this spline has already been processed this go around
		bool		tlLProcessed;					// When the mouse goes down, these are set to false
		bool		tlOProcessed;					// As they are changed, they are raised.
		bool		tlRProcessed;					// This will prevent them from being double-processed during a single select/unselect/toggle operation

		// Used internally for editing
		bool		tlOSelected;					// Is the original selected?
		bool		tlRSelected;					// Is the left-side selected?
		bool		tlLSelected;					// Is the right-side selected?
	};

	struct SRefs
	{
		s8			cType;							// Line types supported:  H=Horizontal, V=Vertical, 2=Two point, 3=Three point, 5=Five point
		s8			cDesc[40];						// Description of this reference
		f64			fref1x;							// Used for H,V,2,3,5
		f64			fref1y;							// Used for H,V,2,3,5
		f64			fref2x;							// Used for 2,3,5
		f64			fref2y;							// Used for 2,3,5
		f64			fref3x;							// Used for 3,5
		f64			fref3y;							// Used for 3,5
		f64			fref4x;							// Used for 5
		f64			fref4y;							// Used for 5
		f64			fref5x;							// Used for 5
		f64			fref5y;							// Used for 5
		bool		lVisible;						// Should this item be used
		s8			cChars1[128];					// Characters this item should be displayed on #1
		s8			cChars2[128];					// Characters this item should be displayed on #2

		SBuilder*	floans;							// Floan data for this particular entry
	};

	// Template point -- is an X,Y coordinate for part of an outline or line that was created as a template for the font.
	// Certain mathematical operations for spline placement use these for reference
	struct STems
	{
		f64		fx;									// X of X,Y coordinate for this outline point
		f64		fy;									// Y of X,Y coordinate for this outline point
		u32		recno;								// Original record number this item came from

		u8		changed;							// Set each time this tems entry is changed
		u8		deleted;							// Set when items are deleted
	};

	struct STemsLines
	{
		SXYF64	p1;									// P1 is from location
		SXYF64	p2;									// P2 is to location
	};

	// Windows used for rendering previews atop VFP forms
	struct SHwnd
	{
		union {
			HWND	hwndParent;						// The parent HWND to which this hwnd is a child
			u32		_hwndParent;					// Accessible value of the parent window
		};
		bool		isValid;						// When a window is no longer a window, it is marked isValid=false

		// The last settings
		u32			markup;							// The last setting passed for the markup condition for rendering
		u32			bold;							// The last bold setting
		u32			italic;							// The last italic setting
		u32			underline;						// The last underline setting
		u32			strikethrough;					// The last strikethrough setting

		// Coordinates
		s32			x;								// X position on the parent hwnd's client area
		s32			y;								// Y position on the parent hwnd's client area
		s32			w;								// Window width
		s32			h;								// Window height

		// Data used expressly for the generated bitmap, and rendering it locally on windows
		union {
			HWND			hwnd;					// The HWND handle
			u32				_hwnd;					// hwnd of the render window
		};
		WNDPROC				oldWndProcAddress;		// Used for re-directing window handling through our DLL
		WNDPROC				oldWndParentProcAddress;// Used for re-directing window handling through our DLL
		BITMAPFILEHEADER	bh;						// Bitmap header if this bitmap is written to disk
		BITMAPINFOHEADER	bi;						// Bitmap info
		RECT				rc;						// Same as SetRect(&rc, 0, 0, w, h)
		s32					rowWidth;				// How wide is each row (rounded up to nearest 32-bit boundary)
		HDC					hdc;					// Device context when window was created
		HBITMAP				hbmp;					// Handle to DIBSection
		SBGR*				bd;						// Pointer to literal bit data for the active window buffer
		HBRUSH				backDarkGrayBrush;		// Color used for dark gray background brush
		HFONT				fontXY;					// Font for rendering X,Y coordiantes in the lower-right

		// Used for real-time mouse drawing
		HDC					hdc2;					// Device context when window was created
		HBITMAP				hbmp2;					// Handle to DIBSection
		SBGR*				bd2;					// Copy of bd used for rendering real-time mouse data

	};

	// SInstance structures are always branded with DSF! as first four bytes, and then length of the structure after
	const s8 cgcDsfBrand[] = "DSF!";
	struct SInstance
	{
		s8				id[4];						// Always 'DSF!' (used to identify the handle)
		u32				id_size;					// sizeof(SInstance)

		SFont			font;						// Font information for this instance
		u32				activeChar;					// The character currently being edited / displayed
		u32				maxChar;					// The maximum character found during the initial load, or created later
		u32				disposition;				// 0=select, 1=unselect, 2=toggle, 3=flip left to right, right to left, 4=flip left/middle to right/middle, and right/middle to left/middle
		u32				mode;						// 0=point, 1=spline, 2=stroke, 3=before and current, 4=current and after
		u32				method;						// 0=left, 1=middle, 2=right, 3=left+middle, 4=middle+right, 5=left+right, 6=spline, 7=point
		u32				range;						// 0=active character, 1=AZ, 2=az, 3=AZaz, 4=09, 5=AZaz09, 6=AZaz09!@.., 7=all
		u32				showTems;					// 0=no, 1=yes
		u32				temsType;					// 0=track, 1=display
		u32				showSplines;				// 0=no, 1=yes
		u32				splinesType;				// 0=fill, 1=outline, 2=LOR only
		u32				selectArea;					// Some value between 10..30 (how big they want the mouse select area to be)

		SBuilder*		chars;						// (SBuilder) Characters, one SBuilder for every character, with each character SBuilder pointing to its many SChar entries
		SBuilder*		refs;						// (SRefs) References
		SBuilder*		hwnds;						// Child window references for this instance
	};


	

//////////
// Constants
//////
	const f64	_2PI						= 6.28318530717959;		// 2*pi
	const f64	_3PI_2						= 4.71238898038469;		// 3*pi/2
	const f64	_4PI_3						= 4.18879020478639;		// 4*pi/3
	const f64	_PI							= 3.14159265358979;		// pi
	const f64	_2PI_3						= 2.09439510239320;		// 2*pi/3
	const f64	_PI_2						= 1.57079632679490;		// pi/2
	const f64	_PI_3						= 1.04719755119660;		// pi/3
	const f64	_PI_4						= 0.78539816339745;		// pi/4
	const f64	_PI_6						= 0.52359877559830;		// pi/6
	const f64	_SQRT2						= 1.4142135624;
	const s8	cgcPreviewWindowClass[]	 = "DSF-Preview-Window-Class";

	const u32	_NO							= 0;
	const u32	_YES						= 1;

	const u32	_SELECT_AREA_SMALL			= 10;
	const u32	_SELECT_AREA_MEDIUM			= 20;
	const u32	_SELECT_AREA_LARGE			= 30;

	const u32	_DISPOSITION_SELECT			= 0;
	const u32	_DISPOSITION_UNSELECT		= 1;
	const u32	_DISPOSITION_TOGGLE			= 2;
	const u32	_DISPOSITION_FLIP_LR		= 3;
	const u32	_DISPOSITION_FLIP_LM_RM		= 4;
	
	const u32	_MODE_POINT					= 0;
	const u32	_MODE_SPLINE				= 1;
	const u32	_MODE_STROKE				= 2;
	const u32	_MODE_BEFORE				= 3;
	const u32	_MODE_AFTER					= 4;
	
	const u32	_METHOD_LEFT				= 0;
	const u32	_METHOD_MIDDLE				= 1;
	const u32	_METHOD_RIGHT				= 2;
	const u32	_METHOD_LEFT_MIDDLE			= 3;
	const u32	_METHOD_MIDDLE_RIGHT		= 4;
	const u32	_METHOD_LEFT_RIGHT			= 5;
	const u32	_METHOD_SPLINE				= 6;
	const u32	_METHOD_POINT				= 7;
	
	const u32	_RANGE_ACTIVE_CHAR			= 0;
	const u32	_RANGE_AZ					= 1;
	const u32	_RANGE_az					= 2;
	const u32	_RANGE_AZ_az				= 3;
	const u32	_RANGE_09					= 4;
	const u32	_RANGE_AZ_az_09				= 5;
	const u32	_RANGE_AZ_az_09_PLUS		= 6;
	const u32	_RANGE_ALL					= 7;

	const u32	_TEMS_TRACK					= 0;
	const u32	_TEMS_DISPLAY				= 1;
	
	const u32	_SPLINES_FILL				= 0;
	const u32	_SPLINES_OUTLINE			= 1;
	const u32	_SPLINES_LOR				= 2;

	const u32	WM_REDRAW_WINDOW			= WM_USER + 1;




//////////
// Global variables
//////
	HINSTANCE	ghInstance;
	SBuilder*	instances;
	SBuilder*	placeholder;
	SXYS32		gMouse					= { -1, -1 };
	u32			gMouseType				= _SELECT_AREA_SMALL;
	bool		glMouseLeft;
	bool		glMouseRight;
	bool		glCtrlKeyDown			= false;
	bool		glShiftKeyDown			= false;
	bool		glAltKeyDown			= false;
	// Common color
	SBGR		black					= { 0, 0, 0 };
	SBGR		stroke					= { 192, 192, 255 };
	SBGR		blackSelected			= { 0, 255, 255 };
	SBGR		darkGray				= { 92, 92, 92 };
	SBGR		background				= { 32, 32, 32 };
	SBGR		backgroundSelected		= { 0, 255, 255 };
	SBGR		colorSelected			= { 64, 128, 255 };
	SBGR		colorR					= { 64, 64, 215 };
	SBGR		colorO					= { 255, 64, 64 };
	SBGR		colorL					= { 64, 215, 64 };
	SBGR		colorRSelected			= { 32, 112, 235 };
	SBGR		colorOSelected			= { 128, 160, 160 };
	SBGR		colorLSelected			= { 32, 235, 160 };
	SBGR		mousePeeakaheadColor	= { 255, 255, 0 };
	SBGR		mouseColor				= { 0, 255, 255 };
	SBGR		colorMarkup				= { 22, 222, 22 };
	SBGR		gray					= { 128, 128, 128 };
	SBGR		graySelected			= { 0, 255, 255 };




//////////
// Forward declarations
//////
	// From DllMain
	void				initialize								(void);
	SSpline* 			iAddSplineFromToLR						(SBuilder* b, bool tlPenDown, f64 tfXL, f64 tfYL, f64 tfXR, f64 tfYR);
	SSpline* 			iAddSplineCenterThetaRadiusLR			(SBuilder* b, bool tlPenDown, f64 tfX, f64 tfY, f64 tfRadius, f64 tfThetaL, f64 tfThetaR);

	// Bitmaps
	int					iGetCharacterBitmap						(int tnAscii, char* tcBitmapFilename, char* tcFontName, int tnHeight, int tnWidth);
	int					iSaveBitmap								(SBGR* bgr, int tnWidth, int tnHeight, int tnLeft, char* tcBitmapFilename, int tnMakeWidth);
	int					iComputeRowWidth						(int tnWidth);
	HBITMAP				iCreateBitmap							(HDC thdc, int tnWidth, int tnHeight, int tnPlanes, int tnBits, void**tbd);

	// Floans
	int					iGetFloanFromBitmap						(u32 tnAscii, char* tcBitmapFilename, char* tcFloanFilename);
	int					iiGetFloanFromBitmap_qsortCallback		(const void* l, const void* r);

	// General purpose
	SInstance*			iGetDsfInstance							(u32 tnHandle, bool* tlValid);
	SSpline*			iFindSplineInstance						(SBuilder* charsBuilder, u32 tnIid, u8 tcType, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder);
	SChars*				iiFindOrCreateThisChars					(SBuilder* charsBuilder, u32 tnIid);
	SChars*				iiFindOnlyThisChars						(SBuilder* charsBuilder, u32 tnIid);
	SSpline*			iFindSplineInstance_SD					(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, bool tlAddIfNotFound);
	SSpline*			iFindSplineInstance_R					(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, bool tlAddIfNotFound);
	SSpline*			iFindSplineInstance_L					(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder, bool tlAddIfNotFound);
	SRefs*				iFindRefsInstance						(SBuilder* refs, u8 tcType, s8* tcDesc40);
	STems*				iCreateNewTemsEntry						(SBuilder* charsBuilder, u32 tipid);
	SBuilder*			iGetTemsRawBuilder						(SBuilder* charsBuilder, u32 tipid);

	int					iRender									(SInstance* p, SHwnd* h, SChars* c, s32 tnWidth, s32 tnHeight, u32 tnHwndParent, s32 tnX, s32 tnY);
	void				iRenderMouseCoordinates					(SInstance* p, SHwnd* h);
	void				iRenderSplines							(SInstance* p, SHwnd* h, SChars* c, u32 tlMarkup, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough);
	void				iComputeLOR								(SSpline* s, SXYF64* pl, SXYF64* po, SXYF64* pr);
	void				iComputeQuadColorsR						(SSpline* s, SSpline* sLast, SBGR quadNormal, SBGR quadSelected, SBGR* p1ColorR, SBGR* p2ColorR, SBGR* p3ColorR, SBGR* p4ColorR);
	void				iComputeQuadColorsL						(SSpline* s, SSpline* sLast, SBGR quadNormal, SBGR quadSelected, SBGR* p1ColorL, SBGR* p2ColorL, SBGR* p3ColorL, SBGR* p4ColorL);
	void				iDrawPoints								(SHwnd* h, SXYF64* pr, SXYF64* po, SXYF64* pl, SSpline* s, SBGR colorSelected, SBGR colorR, SBGR colorO, SBGR colorL, SBGR colorRSelected, SBGR colorOSelected, SBGR colorLSelected);
	void				iDrawLine								(SHwnd* h, SXYF64* p1, SXYF64* p2, SBGR colorStart, SBGR colorEnd);
	void				iDrawLineAlpha							(SHwnd* h, SXYF64* p1, SXYF64* p2, SBGR_AF64* colorStart, SBGR_AF64* colorEnd);
	void				iDrawPoint								(SHwnd* h, SXYF64* p1, SBGR color);
	void				iDrawPointSmall							(SHwnd* h, SXYF64* p1, SBGR color);
	void				iDrawPointLarge							(SHwnd* h, SXYF64* p1, SBGR color);
	void				iDrawMouse								(SHwnd* h, SXYS32* p);
	void				iDrawHorizontalLineByPixels				(SHwnd* h, s32 x1, s32 x2, s32 y, SBGR color);
	void				iFillQuadAlpha							(SHwnd* h, SXYF64* p1, SXYF64* p2, SXYF64* p3, SXYF64* p4, SBGR p1Color, SBGR p2Color, SBGR p3Color, SBGR p4Color, f64 tfP1Alp, f64 tfP2Alp, f64 tfP3Alp, f64 tfP4Alp);
	void				iSetPoint								(SXYF64* p, f64 x, f64 y);
	void				iCopyPoint								(SXYF64* pDst, SXYF64* pSrc);
	void				iRenderMouseOverlay						(SInstance* p, SHwnd* h, SChars* c);
	bool				iComputeClosestMouseLine				(SLineF64* line);
	void				iColorizeAndProcessHorizontalLineByPixels(SInstance* p, SHwnd* h, SChars* c, s32 x1, s32 x2, s32 y, SBGR color);
	void				iColorizeHorizontalLineByPixels			(SInstance* p, SHwnd* h, SChars* c, s32 x1, s32 x2, s32 y, SBGR color);
	void				iColorizeAndProcessVerticalLineByPixels	(SInstance* p, SHwnd* h, SChars* c, s32 y1, s32 y2, s32 x, SBGR color);
	void				iColorizeVerticalLineByPixels			(SInstance* p, SHwnd* h, SChars* c, s32 y1, s32 y2, s32 x, SBGR color);
	void				iRenderTems								(SInstance* p, SHwnd* h, SChars* c);
	u32					iScaleIntoRange							(s32 tnValue, s32 tnValueMax, s32 tnMinRange, s32 tnMaxRange);
	u32					iValidateRange							(s32 tnValue, s32 tnValueMin, s32 tnValueMax, s32 tnDefaultValue);
	void				iMakeSureLowToHighU32					(u32* p1, u32* p2);
	void				iMakeSureLowToHighS32					(s32* p1, s32* p2);
	void				iMakeSureLowToHighF64					(f64* p1, f64* p2);
	int					iiTems_qsortCallback					(const void* l, const void* r);
	int					iiSXyS32_qsortCallback					(const void* l, const void* r);
	u32					iiRenderMarkup_getNextLineSegment		(u32 tnIndex, u32 tnMaxCount, SHwnd* h, STems* root, STems** p1, STems** p2);
	s32					iiGetPoint								(f64 tfValue01, s32 tnMultiplier);
	SHwnd*				iFindOnlyHwndByHwnd						(SBuilder* hwnds, u32 tnHwndParent, u32 tnHwnd);
	SHwnd*				iFindOnlyHwndByHwndParent				(SBuilder* hwnds, u32 tnHwndParent);
	SHwnd*				iFindOnlyHwnd							(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight);
	SHwnd*				iFindOrCreateHwnd						(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight, u32 tlMarkup);
	u32					iCreateWindow							(SHwnd* h);
	void				iComputeLine							(SLineF64* line);
	void				iConstrainQuadAroundLine				(SLineF64* lineRef, SXYF64* p1, SXYF64* p2, SXYF64* p3, SXYF64* p4, f64 tfp1Max, f64 tfp2Max, f64 tfp3Max, f64 tfp4Max, bool tlForceSize);
	void				iConstrainLineLength					(SXYF64* po, SXYF64* pToConstrain, f64 tfMaxLength, bool tlForceToLength);
	f64					iAdjustTheta							(f64 tfTheta);
	s32					iComputeQuad							(SXYF64* p);
	void				iSelectRange							(SInstance* p, SHwnd* h, SChars* c, SXYF64* p1, SXYF64* p2);
	void				iSelectPoint							(SInstance* p, SSpline* spline, bool* tlSelected);
	void				iSelectSpline							(SInstance* p, SSpline* spline);
	void				iSelectStroke							(SInstance* p, SSpline* splineStrokeStart);
	void				iSelectStrokeBefore						(SInstance* p, SSpline* splineStrokeStart, SSpline* splineStrokeEnd);
	void				iSelectStrokeAfter						(SInstance* p, SSpline* splineStrokeStart);
	void				iSplineCompute							(SSpline* spline, SXYF64* pl, SXYF64* po, SXYF64* pr);
	bool				iIsPointInRange							(SXYF64* pTest, SXYF64* ul, SXYF64* lr);
	void				iReadMousePosition						(SInstance* p, SHwnd* h);
	LRESULT CALLBACK	iWindowProcCallback						(HWND hwnd, UINT m, WPARAM w, LPARAM l);
