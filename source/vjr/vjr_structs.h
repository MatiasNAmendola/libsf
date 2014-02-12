//////////
//
// /libsf/source/vjr/vjr_structs.h
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.12.2014
//////
// Change log:
//     Feb.12.2014 - Initial creation
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




struct SBGR
{
	u8	blu;
	u8	grn;
	u8	red;
};

struct SBGRA
{
	u8	blu;
	u8	grn;
	u8	red;
	u8	alp;
};

struct SBitmap
{
	// Device context and bitmap handle to this data
	HDC					hdc;
	HBITMAP				hbmp;

	// Raw bitmap data (suitable for writing to disk)
	BITMAPFILEHEADER	bh;
	BITMAPINFOHEADER	bi;
	s8*					bd;
	u32					rowWidth;
};

struct SFont
{
	HDC			hdc;
	HFONT		hfont;

	s8*			name;
	u32			nameLength;
	s32			sizeUsedForCreateFont;
	u32			size;
	u32			weight;
	u32			italics;
	u32			underline;
	TEXTMETRIC	tm;
};

struct SSize
{
	union {
		s32		width;
		f32		fWidth;
	};
	union {
		s32		height;
		f32		fHeight;
	};
};

struct SRect
{
	s32			left;
	s32			top;
	s32			right;
	s32			bottom;
};

struct SXYS32
{
	s32			x;
	s32			y;
};

struct SWindow
{
	bool				slotUsed;										// Is this slot still used?  If not, it can be re-allocated
	bool				hasFocus;										// Does this window have active focus?
	union {
		f32				scaleFactor;									// How much should this window be scaled?
		u32				_scaleFactor;
	};
	s8*					identifier;										// Identifier for this window
	s64					creationMs;										// Local time when the window was added to our queue

	// For the camera
	s8*					cameraPath;										// The path to save camera snapshots

	// Augments for drawing text more clearly when scaled
	SBuilder*			augments;										// (SAugment) Any text items to display atop the basic image

	//////////
	// Used if the window is a window we're presenting in the interface
	//////
		_union(HWND, u32, hwndSrc);										// HWND of the window we're getting bitmap picture data from, and sending messages to
		RECT			rcSrc;											// The size of the original bitmap
		RECT			rcTab;											// The position of the tab

		// Capture handles
		SBitmap			bmpSrc;
};

struct SObject
{
	bool		isMouseOver;													// Is the mouse over this object?
	RECT		rc;														// Where is this object?
	SBitmap		bmp;													// Image to draw when the mouse is not over it
	SBitmap		bmpOver;												// Image to draw when the mouse is over it
};

struct SWindowIface
{
	SBitmap		bmp;													// Bitmap data for the window
	bool		isMaximized;											// Is the window maximized?
	RECT		rcBeforeMaximize;										// Used when switching to/from maximized size, holds the window rectangle before the maximize
	RECT		rc;														// Rectangle of window's physical position
	SFont*		fontCaption;											// Tahoma 10pt semibold
	SFont*		fontTabs;												// Tahoma 8pt semibold

	// Rectangles for non-object drawn components
	RECT		rcCaption;												// Caption area
	RECT		rcClient;												// Client area where SWindow data is drawn

	// Mouse pointer icons
	SObject		mousePointerBoth;										// When both left and right buttons are down
	SObject		mousePointerLeft;										// When left button is down
	SObject		mousePointerRight;										// When right button is down
	SObject		mousePointer;											// When no buttons are down

	// For the corner triangles
	SObject		arrowUl;
	SObject		arrowUr;
	SObject		arrowLr;
	SObject		arrowLl;

	// For mouse objects
	SObject		settings;
	SObject		minimize;
	SObject		maximize;
	SObject		close;
	SObject		keyIcon;
	SObject		clientCamcorder;
	SObject		clientCamera;
	SObject		clientSettings;

	SObject		tabLeft;
	SObject		tabMiddle;
	SObject		tabRight;
};
