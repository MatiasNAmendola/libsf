//////////
//
// /libsf/VDebug/VDebug/vdeb_defs.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     October 21, 2012 - Initial creation
//     October 21, 2012 - PBL v1.0 license included directly in source files.
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
// Internal debugger functions
//////
	bool				iLoadResource									(s8* tcLanguage);
	DWORD CALLTYPE		iDebuggerMain									(LPVOID lpParameter);


	// vdeb_screens.h
	u64					iBuildNewScreen_Scratch							(u64 tnUniqueId);
	void CALLTYPE		iScratchCallbackMouseHover						(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_ProgramRegisters				(u64 tnUniqueId);
	void CALLTYPE		iProgramRegistersCallbackMouseHover				(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_ControlRegisters				(u64 tnUniqueId);
	void CALLTYPE		iControlRegistersCallbackMouseHover				(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_IntegerRegisters				(u64 tnUniqueId);
	void CALLTYPE		iIntegerRegistersCallbackMouseHover				(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_FloatingPointRegisters			(u64 tnUniqueId);
	void CALLTYPE		iFloatingPointRegistersCallbackMouseHover		(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_Stack							(u64 tnUniqueId);
	void CALLTYPE		iStackCallbackMouseHover						(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_Watch							(u64 tnUniqueId);
	void CALLTYPE		iWatchCallbackMouseHover						(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_Hover							(u64 tnUniqueId);
	void CALLTYPE		iHoverCallbackMouseHover						(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_Locals							(u64 tnUniqueId);
	void CALLTYPE		iLocalsCallbackMouseHover						(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_Autos							(u64 tnUniqueId);
	void CALLTYPE		iAutosCallbackMouseHover						(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_Timers							(u64 tnUniqueId);
	void CALLTYPE		iTimersCallbackMouseHover						(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_Memory							(u64 tnUniqueId);
	void CALLTYPE		iMemoryCallbackMouseHover						(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_Programs						(u64 tnUniqueId);
	void CALLTYPE		iProgramsCallbackMouseHover						(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_Threads							(u64 tnUniqueId);
	void CALLTYPE		iThreadsCallbackMouseHover						(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_AsciiChart						(u64 tnUniqueId);
	void CALLTYPE		iAsciiCallbackMouseHover						(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	u64					iBuildNewScreen_VDebLauncher					(u64 tnUniqueId);
	void CALLTYPE		iVDebLauncherCallbackKeyDown					(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);


	// vdeb_sup.h
	SOssWindow*			iBuildScreen									(u64 tnUniqueId, s8* tcCaption, u32 tnCaptionLength, u32 tnX, u32 tnY, u32 tnWidth, u32 tnHeight, u32 tnWidthMin, u32 tnHeightMin, u32 tnWidthMax, u32 tnHeightMax, u32 foreColor, u32 backColor, bool tlResizable, bool tlMovable, bool tlClosable, bool tlVisible, bool tlBorder, SCallbacksW* tsCallbacks);
	void				iInitializeCallbacksToNull						(SCallbacksW* tcb);

	void CALLTYPE		iCallbackWindowMoved							(u64 tnUniqueId, SOssWindow* tisw, u32 tnXNew, u32 tnYNew);
	void CALLTYPE		iCallbackWindowResized							(u64 tnUniqueId, SOssWindow* tisw, u32 tnWidthNew, u32 tnHeightNew);
	void CALLTYPE		iCallbackWindowGotFocus							(u64 tnUniqueId, SOssWindow* tisw);
	void CALLTYPE		iCallbackWindowLostFocus						(u64 tnUniqueId, SOssWindow* tisw);

	void CALLTYPE		iCallbackMouseDown								(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	void CALLTYPE		iCallbackMouseUp								(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	void CALLTYPE		iCallbackMouseMove								(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	void CALLTYPE		iCallbackMouseHover								(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);

	void CALLTYPE		iCallbackDragStart								(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
	void CALLTYPE		iCallbackDragging								(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds);
	void CALLTYPE		iCallbackDragDrop								(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds);

	void CALLTYPE		iCallbackKeyDown								(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
	void CALLTYPE		iCallbackKeyUp									(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
	void CALLTYPE		iCallbackKeyPress								(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
	void CALLTYPE		iCallbackKeyFlags								(u64 tnUniqueId, SOssWindow* tisw, u32 tnKeyFlagsOld, u32 tnKeyFlagsNew);
