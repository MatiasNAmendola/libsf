//////////
//
// /libsf/vvm/core/common/common_vvmoss_const.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//	   Oct.20.2013
//////
// Change log:
//	   Oct.20.2013 - Initial creation
//////
// See devhelp.txt.
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
//	   http://www.libsf.org/
//	   http://www.libsf.org/licenses/
//	   http://www.visual-freepro.org
//	   http://www.visual-freepro.org/blog/
//	   http://www.visual-freepro.org/forum/
//	   http://www.visual-freepro.org/wiki/
//	   http://www.visual-freepro.org/wiki/index.php/PBL
//	   http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.	In Jesus' name I pray.  Amen.
//
//




//////////
//
// Constants used by the VVMOSS.
//
//////
	cu32			_VVMOSS_CASK_PIPS0										= 0;		// No pips, no coloring
	cu32			_VVMOSS_CASK_PIPS1										= 1;		// One vertical pip, uses pip1 coloring
	cu32			_VVMOSS_CASK_PIPS2										= 2;		// Two vertical pips, uses pip1 and pip2 coloring
	cu32			_VVMOSS_CASK_PIPS3										= 3;		// Three vertical pips, uses pip1, pip2 and pip3 coloring

	cu32			_VVMOSS_CASK_COLOR_ORANGE								= 1;		// Orange coloring
	cu32			_VVMOSS_CASK_COLOR_RED									= 2;		// Red coloring
	cu32			_VVMOSS_CASK_COLOR_BLUE									= 3;		// Blue coloring
	cu32			_VVMOSS_CASK_COLOR_PURPLE								= 4;		// Purple coloring
	cu32			_VVMOSS_CASK_COLOR_CYAN									= 5;		// Cyan coloring
	cu32			_VVMOSS_CASK_COLOR_GREEN								= 6;		// Green coloring
	cu32			_VVMOSS_CASK_COLOR_YELLOW								= 7;		// Yellow coloring
	cu32			_VVMOSS_CASK_COLOR_GRAY									= 8;		// Gray coloring
	cu32			_VVMOSS_CASK_COLOR_WHITE								= 9;		// White coloring
	cu32			_VVMOSS_CASK_COLOR_BLACK								= 10;		// Black coloring

	cu32			_VVMOSS_CASK_STYLE_ROUND								= 0x10;		// (|cask|)
	cu32			_VVMOSS_CASK_STYLE_SQUARE								= 0x20;		// [|cask|]
	cu32			_VVMOSS_CASK_STYLE_DIAMOND								= 0x30;		// <|cask|>

	cu32			_VVMOSS_CASK_STATE_CLOSED								= 0x100;	// ()
	cu32			_VVMOSS_CASK_STATE_MINIMAL								= 0x200;	// (|)
	cu32			_VVMOSS_CASK_STATE_TEXT									= 0x300;	// (|text|)
	cu32			_VVMOSS_CASK_STATE_EXTENDED_TEXT						= 0x400;	// (|=|text|=|) with optional text on left and right sides

	cu32			_VVMOSS_CASK_TYPE_STANDARD								= 0x1000;	// A cask indicated by the type on both sides
	cu32			_VVMOSS_CASK_TYPE_ENCOMPASSING_RECTANGLE				= 0x2000;	// A semi-round cask which encompasses a rectangle which can be populated with text
	cu32			_VVMOSS_CASK_TYPE_UP_RECTANGLE							= 0x3000;	// The part which extends up and right from a cask
	cu32			_VVMOSS_CASK_TYPE_DOWN_RECTANGLE						= 0x4000;	// The part which extends down and left from a cask

	// For the SCREEN coordinate positioning functions
	cu32			_VVMOSS_SCREEN_UPPER_LEFT								= 1;		// Positions toward the upper-left of the active monitor in desktop coordinates
	cu32			_VVMOSS_SCREEN_UPPER_RIGHT								= 2;		// Positions toward the upper-right of the active monitor in desktop coordinates
	cu32			_VVMOSS_SCREEN_LOWER_LEFT								= 3;		// Positions toward the lower-left of the active monitor in desktop coordinates
	cu32			_VVMOSS_SCREEN_LOWER_RIGHT								= 4;		// Positions toward the lower-right of the active monitor in desktop coordinates
	cu32			_VVMOSS_SCREEN_CENTER									= 5;		// Positions toward the center of the active monitor in desktop coordinates

	// For plugins
	cu32			_VVMOSS_PLUGIN_EDITOR									= 1;		// This plugin is an editor plugin, for taking the standard line-by-line format and displaying it
	cu32			_VVMOSS_PLUGIN_EDITOR_CREATE_CONTEXT					= 1000;		// Editor, creates a context and associates it with the indicated bxml
	cu32			_VVMOSS_PLUGIN_EDITOR_ASSOCIATE_WITH_SCREEN				= 1001;		// Editor, associates the current context with the indicated screen

	// For debug trap callbacks (internal error codes reported on regions)
	cu32			_VVM_DEBUGTRAP_UNKNOWN_TYPE								= 1;		// An unknown type was specified
