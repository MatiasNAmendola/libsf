//////////
//
// /libsf/vvm/apps/whitebox/wb_defs.h
//
//////
// Version 0.10
// Copyright (c) 2013 by Rick C. Hodgin
//////
// Last update:
//     Apr.29.2013
//////
// Change log:
//     Apr.29.2013 - Initial creation
//     May.17.2013 - Refactoring, moved wb_screens.h into wb_cb.cpp, wb_sup.cpp
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
//     http://www.visual-freepro.org/wiki/
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




//////////
// Internal functions
//////
	bool				iLoadResource									(s8* tcLanguage);
	DWORD CALLTYPE		iwb_main										(LPVOID lpParameter);


	// wb_sup.h
	u64					iwb_buildScreenTemplate							(u64 tnUniqueId, s8* tcCaption, u32 tnCaptionLength, u32 tnX, u32 tnY, u32 tnWidth, u32 tnHeight, u32 tnWidthMin, u32 tnHeightMin, u32 tnWidthMax, u32 tnHeightMax, u32 foreColor, u32 backColor, bool tlResizable, bool tlMovable, bool tlClosable, bool tlVisible, bool tlBorder, SCallbacks* tsCallbacks);
	void				iwb_initializeCallbacks							(SCallbacks* tcb);
	bool				iwb_buildNewMainScreen							(u64 tnUniqueId, SWBScreen* tsWbScreen);
	bool				iwb_buildNewMediaScreen							(u64 tnUniqueId, SWBScreen* tsWbScreen);
	bool				iwb_buildNewChannelScreen						(u64 tnUniqueId, SWBScreen* tsWbScreen);
	bool				iiwb_createMainRegions							(SCanvas* canvas);
	bool				iiwb_createMediaRegions							(SCanvas* canvas);
	bool				iiwb_createChannelRegions						(SCanvas* canvas);
	bool				iiwb_createScreenCanvas							(u64 tnUniqueId, u32 tnWidth, u32 tnHeight, SScreen** tsScreen, SCanvas** tsCanvas, SCallbacks* callbacks);


	// wb_cb.cpp (cb=callbacks)
	void CALLTYPE		iwb_callbackWindowMoved							(u64 tnUniqueId, SOssWindow* tisw, u32 tnXNew, u32 tnYNew);
	void CALLTYPE		iwb_callbackWindowResized						(u64 tnUniqueId, SOssWindow* tisw, u32 tnWidthNew, u32 tnHeightNew);
	void CALLTYPE		iwb_callbackWindowGotFocus						(u64 tnUniqueId, SOssWindow* tisw);
	void CALLTYPE		iwb_callbackWindowLostFocus						(u64 tnUniqueId, SOssWindow* tisw);
	void CALLTYPE		iwb_callbackMouseDown							(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	void CALLTYPE		iwb_callbackMouseUp								(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	void CALLTYPE		iwb_callbackMouseMove							(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	void CALLTYPE		iwb_callbackMouseHover							(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	void CALLTYPE		iwb_callbackDragStart							(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	void CALLTYPE		iwb_callbackDragging							(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds);
	void CALLTYPE		iwb_callbackDragDrop							(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds);
	void CALLTYPE		iwb_callbackKeyDown								(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
	void CALLTYPE		iwb_callbackKeyUp								(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
	void CALLTYPE		iwb_callbackKeyPress							(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
	void CALLTYPE		iwb_callbackKeyFlags							(u64 tnUniqueId, SOssWindow* tisw, u32 tnKeyFlagsOld, u32 tnKeyFlagsNew);
