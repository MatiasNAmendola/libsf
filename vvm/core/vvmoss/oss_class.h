//////////
//
// /libsf/vvm/vvmoss/vo_class.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     September 20, 2012 - Initial creation
//     September 29, 2012 - PBL v1.0 license included directly in source files.
//     November 07, 2012 - 0.60 development begins
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
//



//////////
// Window messages supported
//////
	const u32	VVMOSS_MAGIC_NUMBER									= 0x19690810;		// The date of Rick C. Hodgin's birth! :-)
	const u32	VVMOSS_REQUEST_MAGIC_NUMBER							= WM_USER + 1;		// Validates that the object identified by gcVvmOssClass is actually our target
	const u32	VVMOSS_REQUEST_UNIQUE_ID							= WM_USER + 2;		// Returns the next Unique ID given by the VVM
	const u32	VVMOSS_LOAD_DEBUGGER_DLL							= WM_USER + 3;		// Asks the VVM to load the specified debugger DLL
	const u32	VVMOSS_CREATE_VISIBLE_WINDOW						= WM_USER + 4;		// Creates a visible OS-specific window
	const u32	VVMOSS_CREATE_WINDOW_BITMAP							= WM_USER + 5;		// Creates the specified bitmap for the indicated window
	const u32	VVMOSS_REQUEST_UNIQUE_DEBUGGER_BACKGROUND_COLOR		= WM_USER + 6;		// Since multiple debuggers can be instantiated simultaneously, a background color coding scheme can be used.
	const u32	VVMOSS_VISIBLE_WINDOW_CLOSED						= WM_USER + 7;		// Visible windows which have a WindowClosed callback signal this message to the message window
	const u32	VVMOSS_FATAL_ERROR									= WM_USER + 8;		// Thrown when something in another thread encountered a physical error
	
	// Where did the fatal errors come from?
	const u32	VVMOSS_FATAL_ERROR_IN_1MS_TIMER						= 1;				// From the 1ms TimerAPCProc routine


//////////
// Mouse-related messages
//////
	// Constants used for timing events
	const u64	gnHoverTimeout										= 600;				// 0.6 seconds
	const f32	gfMouseDragThreshold								= 7.071f;			// ~sqrt(5*5 + 5*5), movement of ~5 pixels on both axes average before triggering a drag

	// Used by iRecordMouseEvent() and any functions receiving callbacks
	const u32	VVMOSS_MOUSE_MOVE									= 1 << 0;
	const u32	VVMOSS_MOUSE_BUTTON_DOWN_RIGHT						= 1 << 1;
	const u32	VVMOSS_MOUSE_BUTTON_DOWN_LEFT						= 1 << 2;
	const u32	VVMOSS_MOUSE_BUTTON_DOWN							= 1 << 3;
	const u32	VVMOSS_MOUSE_BUTTON_UP_RIGHT						= 1 << 4;
	const u32	VVMOSS_MOUSE_BUTTON_UP_LEFT							= 1 << 5;
	const u32	VVMOSS_MOUSE_BUTTON_UP								= 1 << 6;

	// Identified mouse buttons
	const u32	VVMOSS_MOUSE_LEFT									= 1 << 0;		// Standard mouse buttons
	const u32	VVMOSS_MOUSE_MIDDLE									= 1 << 1;
	const u32	VVMOSS_MOUSE_RIGHT									= 1 << 2;
	const u32	VVMOSS_MOUSE_EXTRA1									= 1 << 3;		// Other mouse buttons
	const u32	VVMOSS_MOUSE_EXTRA2									= 1 << 4;
	// A mask for any mouse button
	const u32	VVMOSS_MOUSE_DOWN_MASK								= (VVMOSS_MOUSE_EXTRA2 * 2) - 1;


/////////
// Keyboard-related messages
//////
	// Used by iRecordKeyboardEvent() and any functions receiving callbacks
	const u32	VVMOSS_KEYBOARD_DOWN								= 1 << 0;
	const u32	VVMOSS_KEYBOARD_UP									= 1 << 1;

	// Identified keystrokes overrides
	const u32	VVMOSS_KEYBOARD_CONTROL								= 1 << 0;		// Special keys
	const u32	VVMOSS_KEYBOARD_SHIFT								= 1 << 1;
	const u32	VVMOSS_KEYBOARD_ALT									= 1 << 2;
	const u32	VVMOSS_KEYBOARD_RIGHT_CONTROL						= 1 << 3;		// Right-side keystrokes
	const u32	VVMOSS_KEYBOARD_RIGHT_SHIFT							= 1 << 4;
	const u32	VVMOSS_KEYBOARD_RIGHT_ALT							= 1 << 5;
	const u32	VVMOSS_KEYBOARD_LEFT_CONTROL						= 1 << 6;		// Left-side keystrokes
	const u32	VVMOSS_KEYBOARD_LEFT_SHIFT							= 1 << 7;
	const u32	VVMOSS_KEYBOARD_LEFT_ALT							= 1 << 8;
	// Specific conditions
	const u32	VVMOSS_KEYBOARD_SHIFT_TOGGLED						= 1 << 28;
	const u32	VVMOSS_KEYBOARD_CONTROL_TOGGLED						= 1 << 29;
	const u32	VVMOSS_KEYBOARD_ALT_TOGGLED							= 1 << 30;
	const u32	VVMOSS_KEYBOARD_SCROLL_LOCK_ON						= 1 << 29;		// Is scroll lock on?
	const u32	VVMOSS_KEYBOARD_NUM_LOCK_ON							= 1 << 30;		// Is num lock on?
	const u32	VVMOSS_KEYBOARD_CAPS_LOCK_ON						= 1 << 31;		// Is caps lock on?
	// A mask for any key flag
	const u32	VVMOSS_KEYBOARD_DOWN_MASK							= (VVMOSS_KEYBOARD_LEFT_ALT * 2) - 1;
	// Note:  All key definitions in vvm_key_const.h


//////////
// Class used to find the VvmOss message window
//////
	const s8		gcVvmOssMessageClass[]							= "vvmoss_1.0.message.window";
	const s8		gcVvmOssVisibleClass[]							= "vvmoss_1.0.visible.window";
	const wchar_t	guVvmOssVisibleClass[]							= L"vvmoss_1.0.visible.windowu";


//////////
// Constant strings
//////
	const s8		cgcName[]										= "name=";
	const s8		cgcDll[]										= "dll=";
