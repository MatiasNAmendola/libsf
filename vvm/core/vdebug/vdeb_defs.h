//////////
//
// /libsf/VDebug/VDebug/vdeb_defs.h
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.25.2014
//////
// Change log:
//     Feb.25.2014 - Development on 0.70 begins
//     Nov.07.2012 - 0.60 development begins
//     Oct.21.2012 - PBL v1.0 license included directly in source files.
//     Oct.21.2012 - Initial creation
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
// Internal debugger functions
//////
	bool				iLoadResource									(s8* tcLanguage);
	DWORD CALLTYPE		iDebuggerMain									(LPVOID lpParameter);


	// vdeb_screens.h


	// vdeb_sup.h
	u64 CALLTYPE		vdeb_window_created								(u64 tnUniqueId, SOssWindow* tisw);
	u64 CALLTYPE		vdeb_window_unload								(u64 tnUniqueId, SOssWindow* tisw);
	u64 CALLTYPE		vdeb_window_closed								(u64 tnUniqueId, SOssWindow* tisw);
	u64 CALLTYPE		vdeb_window_moved								(u64 tnUniqueId, SOssWindow* tisw, u32 tnXNew, u32 tnYNew);
	u64 CALLTYPE		vdeb_window_resized								(u64 tnUniqueId, SOssWindow* tisw, u32 tnWidthNew, u32 tnHeightNew);
	u64 CALLTYPE		vdeb_window_gotFocus							(u64 tnUniqueId, SOssWindow* tisw);
	u64 CALLTYPE		vdeb_window_lostFocus							(u64 tnUniqueId, SOssWindow* tisw);

	u64 CALLTYPE		vdeb_region_enter								(SRegion* tr);
	u64 CALLTYPE		vdeb_region_leave								(SRegion* tr);
	u64 CALLTYPE		vdeb_region_paint								(SRegion* tr, SCanvas* tc, SBGRA* bd);
	u64 CALLTYPE		vdeb_region_debugTrap							(SRegion* tr, u64 tnIdentifier, u64 tnExtra);

	u64 CALLTYPE		vdeb_mouse_down									(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	u64 CALLTYPE		vdeb_mouse_up									(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	u64 CALLTYPE		vdeb_mouse_move									(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	u64 CALLTYPE		vdeb_mouse_hover								(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);

	u64 CALLTYPE		vdeb_keyboard_down								(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
	u64 CALLTYPE		vdeb_keyboard_up								(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
	u64 CALLTYPE		vdeb_keyboard_press								(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
	u64 CALLTYPE		vdeb_keyboard_flags								(u64 tnUniqueId, SOssWindow* tisw, u32 tnKeyFlagsOld, u32 tnKeyFlagsNew);

	u64 CALLTYPE		vdeb_drag_start									(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	u64 CALLTYPE		vdeb_drag_dragging								(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds);
	u64 CALLTYPE		vdeb_drag_drop									(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds);

	u64 CALLTYPE		vdeb_custom_custom								(u64 tnUniqueId, SOssWindow* tisw, u64 tnCustomEventId, u64 tnOtherData);

