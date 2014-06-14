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
	HINSTANCE			ghInstance;
	ITaskbarList*		giTaskbar;
	SBuilder*			gWindows;
	SBuilder*			gFonts;
	HWND				ghwndMsg;
	HWND				ghwndScreen;
	HWND				ghwndJDebi;
	SWindow				winScreen;
	SWindow				winJDebi;
	s64					systemStartedMs;


	// JDebi window
	STextChainManager*	commandHistory;																// The command window history


	// Global colors
	const SBgra			white								= { rgba(255, 255, 255, 255) };
	const SBgra			black								= { rgba(0, 0, 0, 255) };
	const SBgra			gray								= { rgba(192, 192, 192, 255) };

	// Four-corner window color schemes (eventually these will be loaded from themes.dbf)
	const SBgra			colorNW								= { rgba(222, 230, 255, 255) };
	const SBgra			colorNE								= { rgba(157, 194, 214, 255) };
	const SBgra			colorSW								= { rgba(255, 255, 255, 255) };
	const SBgra			colorSE								= { rgba(192, 212, 255, 255) };


	// Mouse options
	bool				glMoving							= false;								// When the user clicks and drags the title bar area, the window will move
	bool				glResizing							= false;								// When the user clicks and drags the corner triangle areas, the window will resize, resulting in larger or smaller scaling
	u32					gnResizingFrom						= 0;									// The _UPPER_LEFT.._LOWER_LEFT constants from below
// 	RECT				grcMoveStart						= { 0, 0, 0, 0 };
// 	RECT				grcResizeStart						= { 0, 0, 0, 0 };
	SXYS32				gMousePositionMoveStart				= { -1, -1 };							// Mouse position when the move started
	SXYS32				gMousePositionMoveEnd				= { -1, -1 };							// Mouse position when the move ended
	SXYS32				gMousePositionResizeStart			= { -1, -1 };							// Mouse position when the resize started
	SXYS32				gMousePositionResizeEnd				= { -1, -1 };							// Mouse position when the resize ended

	SXYS32				gMousePosition						= { -1, -1 };							// Mouse position indicated by windows in the interface window
	bool				glMouseInClientArea					= false;								// When the mouse is in the client area, this flag is raised
	SXYS32				gMousePositionClientArea			= { -1, -1 };							// Mouse position in the client area of the interface window
	SXYS32				gnMouseDelta						= { 0, 0 };								// Change in position
	bool				glMouseLeftButton					= false;
	bool				glMouseMiddleButton					= false;
	bool				glMouseRightButton					= false;

