//////////
//
// /libsf/source/vjr/vjr_globals.h
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




//////////
// Global Variables
//////
	HINSTANCE			ghInstance							= NULL;
	ITaskbarList*		giTaskbar							= NULL;
	SBuilder*			gWindows							= NULL;
	SBuilder*			gFonts								= NULL;
	HWND				ghwndMsg							= NULL;
	CRITICAL_SECTION	gcsUniqueIdAccess;
	u32					gnNextUniqueId						= 0;
	s64					systemStartedMs						= 0;


	// JDebi window items
	SEditChainManager*	commandHistory						= NULL;									// The command window history

	// App icons
	SBitmap*			bmpVjrIcon							= NULL;
	SBitmap*			bmpJDebiIcon						= NULL;

	// When there is no image
	SBitmap*			bmpNoImage							= NULL;

	// For mouse objects
	SBitmap*			bmpMove								= NULL;									// Icons used for move, minimize, maximize, close
	SBitmap*			bmpMinimize							= NULL;
	SBitmap*			bmpMaximize							= NULL;
	SBitmap*			bmpClose							= NULL;

	// For the corner triangles
	SBitmap*			bmpArrowUl							= NULL;									// Icons used for the move arrows
	SBitmap*			bmpArrowUr							= NULL;
	SBitmap*			bmpArrowLr							= NULL;
	SBitmap*			bmpArrowLl							= NULL;

	// Default screens used by VJr
	SObject*			gobj_screen							= NULL;
	SObject*			gobj_jdebi							= NULL;
	SWindow*			gWinScreen							= NULL;
	SWindow*			gWinJDebi							= NULL;

	// Default class structures
	SObject*			gobj_defaultEmpty					= NULL;
	SObject*			gobj_defaultForm					= NULL;
	SObject*			gobj_defaultSubform					= NULL;
	SObject*			gobj_defaultLabel					= NULL;
	SObject*			gobj_defaultTextbox					= NULL;
	SObject*			gobj_defaultButton					= NULL;
	SObject*			gobj_defaultImage					= NULL;
	SObject*			gobj_defaultCheckbox				= NULL;
	SObject*			gobj_defaultOption					= NULL;
	SObject*			gobj_defaultRadio					= NULL;

	//////////
	// General defaults
	//////
		SFont*			gsFont								= NULL;									// Default font, Ubuntu 10 pt
		SFont*			gsWindowTitleBarFont				= NULL;									// Default font, Ubuntu Bold 12 pt
		// Global colors
		const SBgra		white								= { rgba(255, 255, 255, 255) };
		const SBgra		black								= { rgba(0, 0, 0, 255) };
		const SBgra		gray								= { rgba(192, 192, 192, 255) };
		const SBgra		selectedBackColor					= { rgba(32, 164, 255, 255) };
		const SBgra		selectedForeColor					= { rgba(255, 255, 255, 255) };
		const SBgra		disabledBackColor					= { rgba(255, 255, 255, 255) };
		const SBgra		disabledForeColor					= { rgba(192, 192, 230, 255) };
		// Four-corner window color schemes (eventually these will be loaded from themes.dbf)
		const SBgra		NwColor								= { rgba(222, 230, 255, 255) };
		const SBgra		NeColor								= { rgba(157, 194, 214, 255) };
		const SBgra		SwColor								= { rgba(255, 255, 255, 255) };
		const SBgra		SeColor								= { rgba(192, 212, 255, 255) };


	//////////
	// Mouse options
	//////
		bool			glMoving							= false;								// When the user clicks and drags the title bar area, the window will move
		bool			glResizing							= false;								// When the user clicks and drags the corner triangle areas, the window will resize, resulting in larger or smaller scaling
		u32				gnResizingFrom						= 0;									// The _UPPER_LEFT.._LOWER_LEFT constants from below
// 		RECT			grcMoveStart						= { 0, 0, 0, 0 };
// 		RECT			grcResizeStart						= { 0, 0, 0, 0 };
		SXYS32			gMousePositionMoveStart				= { -1, -1 };							// Mouse position when the move started
		SXYS32			gMousePositionMoveEnd				= { -1, -1 };							// Mouse position when the move ended
		SXYS32			gMousePositionResizeStart			= { -1, -1 };							// Mouse position when the resize started
		SXYS32			gMousePositionResizeEnd				= { -1, -1 };							// Mouse position when the resize ended

		SXYS32			gMousePosition						= { -1, -1 };							// Mouse position indicated by windows in the interface window
		bool			glMouseInClientArea					= false;								// When the mouse is in the client area, this flag is raised
		SXYS32			gMousePositionClientArea			= { -1, -1 };							// Mouse position in the client area of the interface window
		SXYS32			gnMouseDelta						= { 0, 0 };								// Change in position
		bool			glMouseLeftButton					= false;
		bool			glMouseMiddleButton					= false;
		bool			glMouseRightButton					= false;

