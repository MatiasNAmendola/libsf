//////////
//
// /libsf/vvm/vvmoss/vo_defs.h
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
//     Sep.29.2012 - PBL v1.0 license included directly in source files.
//     Sep.20.2012 - Initial creation
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
// vo.cpp
//////
	u64 CALLTYPE			oss_firstCallback								(u32 tnDoNotLoadOptions);
	void CALLTYPE			oss_bootstrapInitialization						(void);
	void CALLTYPE			oss_initialization								(void);
	const s8* CALLTYPE		oss_getVersion									(void);
	bool CALLTYPE			oss_createMessageWindow							(void);
	u64 CALLTYPE			oss_createVisibleWindow							(SOssWindow* tisw, u64 tnScreenId);


//////////
// Plugin callbacks
//////
	u64 CALLTYPE			oss_plugin_registerFunction						(u64 tnInstanceId, u64 tnFunction, f32 tfVersion, u32 tnBuild, const u8* tcMetaName, u64 tnFunc);
	u64 CALLTYPE			oss_plugin_unregisterFunction					(u64 tnInstanceId, u64 tnFunction);


//////////
//
// Basic system functions
//
//////
		void CALLTYPE			oss_getSystemInfo							(SSysInfo* tsi);
		void CALLTYPE			oss_sleep									(u32 tnMilliseconds);
		void CALLTYPE			oss_dateTimeGet								(SDateTime* tdt);
		s8* CALLTYPE			oss_changePathnameExtension					(s8* tcPathname, s8* tcNewPathname);
		bool CALLTYPE			oss_validateFilenameCharacter				(s8* tcPathname, u64 tnPathnameLength, u64* tnErrorPosition);


//////////
//
// Window and canvas related functions
// All canvases are 32-bit with an alpha layer.
// All windows use 24-bit presentations.
//
//////
		u64 CALLTYPE			oss_deleteScreen							(SScreen* ts);
		u64 CALLTYPE			oss_deleteCanvas							(SCanvas* tc);

		SScreen* CALLTYPE		oss_createScreenAndVisibleWindow			(u64 tnAssociatedId, SOssWindow* tisw/*tisw was created by oss_screenCreateTemplate()*/);
		SRegion* CALLTYPE		oss_createRegionForScreen					(SScreen* ts, SCallbacks* callbacks, SStartEnd* events, SRegionState* trs);
		SCanvas* CALLTYPE		oss_createCanvasForScreen					(SScreen* ts);
		SCanvas* CALLTYPE	 	oss_createCanvas							(u64 tnAssociatedId, u32 tnWidth, u32 tnHeight, SBGRA tnBackColor);
		SRegion* CALLTYPE		oss_createRegion							(u64 tnAssociatedId, u32 tnType, f32 ulx, f32 uly, f32 lrx, f32 lry, SCallbacks* callbacks, SStartEnd* events, SRegionState* trs);
		bool CALLTYPE			oss_createRegionAndCanvas					(u64 tnAssociatedId, SBGRA tnBackColor, f32 ulx, f32 uly, f32 lrx, f32 lry, SCanvas** tc, SRegion** tr, SRegionState* regionState, SCallbacks* callbacks, SStartEnd* events);
		u64 CALLTYPE		 	oss_createFontHandle						(s8* fontName, u32 fontWidth, bool bold, bool italics, bool underline, bool strikethrough);

		u64 CALLTYPE			oss_screenMouseSetEventCallback				(u64 id, SCanvas* tc, SEvent* event);
		u64 CALLTYPE			oss_screenMouseRemoveEventCallback			(u64 id, SCanvas* tc, SEvent* event);
		void CALLTYPE			oss_screenMouseGetEventCallbacksList		(u64 id, SCanvas* tc, SEvent** events, u32* count);
		u64 CALLTYPE			oss_screenKeyboardSetEventCallback			(u64 id, SCanvas* tc, SEvent* event);
		u64 CALLTYPE			oss_screenKeyboardRemoveEventCallback		(u64 id, SCanvas* tc, SEvent* event);
		void CALLTYPE			oss_screenKeyboardGetEventCallbacksList		(u64 id, SCanvas* tc, SEvent** events, u32* count);

		SOssWindowLL* CALLTYPE	oss_findSOssWindowLLByHwnd					(HWND hwnd);
		SOssWindowLL* CALLTYPE	oss_findSOssWindowLLByScreenId				(u64 tnScreenId);
		SOssWindowLL* CALLTYPE	oss_find_iswSOssWindowLL_By_iOssWindowId	(u64 tnOssWindowId);

		// Only 24-bit or 32-bit bitmaps can be loaded from disk at present.
		u64 CALLTYPE			oss_bitmapLoadFromDisk						(s8* tcPathname, SCanvas** tc, u32* tnWidth, u32* tnHeight, SBGRA tnBackColor);
		u64 CALLTYPE			oss_bitmapSaveToDisk						(SCanvas* tc, SBGRA* bd, s8* tcPathname);
		u64 CALLTYPE			oss_systemCreateFont						(s8* fontName, u32 fontWidth, bool bold, bool italics, bool underline, bool strikethrough);
		u64 CALLTYPE			oss_systemCreateBitmap						(u32 tnWidth, u32 tnHeight);
		u64 CALLTYPE			oss_systemFindFontByHandle					(u64 tnFontHandle);

		// This 64-bit return value is used as input into vvm_requestScreen()
		SOssWindow* CALLTYPE	oss_screenCreateTemplate					(u64 id, u64 uniqueScreenId,
																				s8* tcCaption, u32 tnCaptionLength,
																				s32 tnX, s32 tnY,
																				u32 tnWidth, u32 tnHeight,
																				u32 tnWidthMin, u32 tnHeightMin,
																				u32 tnWidthMax, u32 tnHeightMax,
																				u32 ncUlx, u32 ncUly, u32 ncLrx, u32 ncLry, u32 ncBorder,
																				SBGRA tnForeColor, SBGRA tnBackColor,
																				bool tlResizable, bool tlMovable, bool tlClosable, bool tlVisible, bool tlBorder,
																				SCallbacksW* callbacks);

		void CALLTYPE			oss_screenComputeMonitorCoordinates			(SOssWindow* tow, f32 tfPercent, u32 tnPosition, f32 tfMargin, s32* tnX, s32* tnY, u32* tnWidth, u32* tnHeight, u32* tnWidthMax, u32* tnHeightMax, u32* tnWidthMin, u32* tnHeightMin);
		SOssWindow* CALLTYPE	oss_screenEnumerateMonitors					(SStartEnd* tsMonitors/*Returns SOssWindow* structures*/);
		bool CALLTYPE			oss_screenGetDimensions						(u64 tnOssWindowId, s32* tnX, s32* tnY, u32* tnWidth, u32* tnHeight, u32* tnWidthMax, u32* tnHeightMax, u32* tnWidthMin, u32* tnHeightMin);
		u64 CALLTYPE			oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb	(u64 tnOssWindowId, SBGRA* bd, u32 width, u32 height);
		u64 CALLTYPE			oss_lowLevel_bitBlt_ossRgb_onto_canvasBgra	(u64 bdoss, s32 tnX, s32 tnY, u32 tnWidth, u32 tnHeight, SCanvas* tc, SBGRA* bdRoot);
		u64 CALLTYPE			oss_getNextMessage							(u32* message, void* extra);
		u64 CALLTYPE			oss_messageBox								(u64 id, s8*  tcText, s8*  tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);
		u64 CALLTYPE			oss_messageBoxUnicode						(u64 id, w16* tuText, w16* tuCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);
		u64 CALLTYPE			oss_drawText								(s8* tcText, u32 tnTextLength, s32 ulx, s32 uly, s32 lrx, s32 lry, SBGRA foreground, SBGRA background, u64 tnSystemFont, u64 tnSystemBitmap);


//////////
//
// Memory Allocation
// The VVM is a virtual machine, it needs a way to know what memory should be saved during
// times of suspension, and restored upon resumption.
//
//////////
		void* CALLTYPE			oss_alloc									(u64 tnSize, bool tlInitialize);
		void* CALLTYPE			oss_realloc									(void* ptrOld, u64 tnNewSize);
		void* CALLTYPE			oss_free									(void* ptr);


//////////
//
// Sound plugin
// The VVM will provide a sound stub functions, but if a plugin exists
// it will load that plugin and use the sound functions.
//
//////////
		// See common_vvmoss_plugins.h


//////////
//
// Lines and Components
// Facilities are provided for parsing distinct bits of text found in text files.  These are
// called components, and each line of a text file can be broken out, and then parsed for known
// keywords using these facilities.  VASM (the VVM Assembler) uses this for all of its syntax
// parsing of raw assembly source code files, for example.
//
//////////
		u64 CALLTYPE			oss_breakoutAsciiTextIntoSOssLines			(s8* tcData, u64 tnFileSize, SStartEnd* tseLines, u64 tnAllocSize, bool tlUseOssAlloc);
		SOssComp* CALLTYPE		oss_translateSOssLinesToSOssComps			(SAsciiCompSearcher* tsComps, SOssLine* line);
		void CALLTYPE			oss_translateSOssCompsToOthers				(SAsciiCompSearcher* tsComps, SOssLine* line);
		u64 CALLTYPE			oss_writeSOssLineSequenceToDisk				(s8* tcPathname, SStartEnd* tseLines);
		u64 CALLTYPE			oss_writeSOssLineSequenceCompsToDisk		(s8* tcPathname, SStartEnd* tseLines);
		u64 CALLTYPE			oss_writeSOssLineSequenceCompsDebuggingToDisk(s8* tcPathname, SStartEnd* tseLines);
		bool CALLTYPE			oss_findFirstOccurrenceOfAsciiCharacter		(s8* tcHaystack, u64 tnHaystackLength, s8 tcNeedle, u64* tnPosition);
		SOssComp* CALLTYPE		oss_findNextSOssCompBy_iCode				(SOssComp* comp, u32 tniCode, SOssComp** compLastScanned);
		SOssComp* CALLTYPE		oss_skipPastSOssComp_iCode					(SOssComp* comp, u32 tniCode);
		u32 CALLTYPE			oss_combine2SOssComps						(SOssLine* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2,                     u32 tniCodeCombined);
		u32 CALLTYPE			oss_combine3SOssComps						(SOssLine* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeNeedle3, u32 tniCodeCombined);
		u32 CALLTYPE			oss_combineAllBetweenSOssComps				(SOssLine* line, u32 tniCodeNeedle,                                          u32 tniCodeCombined);
		u32 CALLTYPE			oss_combineAllAfterSOssComp					(SOssLine* line, u32 tniCodeNeedle);
		u32 CALLTYPE			oss_removeExtraneousWhitespaceSOssComps		(SOssLine* line, u32 tniCodeWhitespace);


//////////
//
// ASCII File Access
// Functions to access ASCII-based files.
//
//////////
		u64 CALLTYPE			oss_sharedAsciiOpenFile						(s8* tcPathname, bool tlExclusive, bool tlReadOnly, bool tlIfShared_DenyReads, bool tlIfShared_DenyWrites, bool tlAppendMode, bool tlTruncate, bool tlShortLived, bool tlTemporaryFile);
		u64 CALLTYPE			oss_sharedAsciiSeekFile						(u64 tnFileHandle, s64 tnDisplacement, u64 tnSource/*0=file offset, -1=relative backward, 1=relative forward*/);
		u64 CALLTYPE			oss_sharedAsciiReadFile						(u64 tnFileHandle, s8* tcDest,   u64 tnBytesToRead);
		u64 CALLTYPE			oss_sharedAsciiWriteFile					(u64 tnFileHandle, s8* tcSource, u64 tnBytesToWrite);
		u64 CALLTYPE			oss_sharedAsciiLockFile						(u64 tnFileHandle, u64 tnStart, u64 tnLength);
		u64 CALLTYPE			oss_sharedAsciiUnlockFile					(u64 tnFileHandle, u64 tnLockHandle);
		u64 CALLTYPE			oss_sharedAsciiCloseFile					(u64 tnFileHandle);
		u64 CALLTYPE			oss_sharedAsciiFileSize						(u64 tnFileHandle);
		s8* CALLTYPE			oss_sharedAsciiGetTempFilename				(void);
		bool CALLTYPE			oss_sharedAsciiDeleteFile					(s8* tcFullPathname);
		bool CALLTYPE			oss_sharedAsciiWriteOutFile					(s8* tcFullPathname, s8* tcData, u32 tnDataLength);




//////////
//
// Find files
//
//////////
		u64 CALLTYPE			oss_fileFindFirst							(SFindFile* tsFileInfo);
		bool CALLTYPE			oss_fileFindNext							(u64 tnHandle, SFindFile* tsFileInfo);
		void CALLTYPE			oss_fileFindClose							(u64 tnHandle, SFindFile* tsFileInfo);




//////////
//
// Threading
// These services are exposed by the VVMOSS to facilitate the needs of
// creating a new thread for execution.  These operate in an operating-system
// neutral way externally, allowing the same function to always be called
// with the expected results
//
//////////
		u64 CALLTYPE			oss_threadCreate							(u64 tnThreadAddress, void* data, bool tlStartSuspended);
		u64 CALLTYPE			oss_threadSuspend							(u64 ossData);
		u64 CALLTYPE			oss_threadResume							(u64 ossData);
		u64 CALLTYPE			oss_threadTerminate							(u64 ossData, u32 tnTerminationCode);


//////////
//
// Semaphores
// These services are exposed to allow anything that needs to be blocked
// to be blocked by creating a semaphore, calling these functions, which
// will guarantee that after the semaphore is locked, exclusive access
// can be granted to the desired resource.  Do not forget to unlock after
// locking.  Trylock can be used to see if you can, at the present time,
// lock the semaphore for exclusive access.
//
//////////
		u64 CALLTYPE			oss_createSemaphore							(void);
		void CALLTYPE			oss_lockSemaphore							(u64 handle);
		bool CALLTYPE			oss_tryLockSemaphore						(u64 handle);
		void CALLTYPE			oss_unlockSemaphore							(u64 handle);
		void CALLTYPE			oss_deleteSemaphore							(u64 handle);


//////////
//
// Debugging
// Used internally to trap for debugging breakpoints.  Allows conditional execution of something
// until a condition arises, and only then will the debugger be trapped if internal breakpoints
// have been enabled by an explicit call to oss_enableBreakpoints().
//
//////
		void CALLTYPE			oss_enableBreakpoints						(void);
		void CALLTYPE			oss_disableBreakpoints						(void);


//////////
// vo_sup.cpp
//////
	// Callbacks related to above
	bool					iioss_findSystemFontByHandleCallback			(SStartEndCallback* cb);
	bool					ioss_registerWindowClasses						(u32* tnError);
	HWND					ioss_createMessageWindow						(void);
	DWORD CALLTYPE			ioss_messageLoop								(LPVOID lpParameter);
	u64						ioss_loadDebuggerDll							(u32 tnUniqueId);
	u64						ioss_loadDebuggerByIniFile						(FILE* tfh, u32 tnUniqueId, s8* tcPathname);
	void					ioss_locateLineThenGetStartAndEnd				(s8* tcHaystack, u32 tnHaystackLength, s8* tcNeedle, u32 tnNeedleLength, u32* tnStart, u32* tnEnd);
	u32						ioss_searchHaystackForNeedle					(s8* tcHaystack, u32 tnHaystackLength, s8* tcNeedle, u32 tnNeedleLength);
	u32						ioss_searchHaystackForNeedleCase				(s8* tcHaystack, u32 tnHaystackLength, s8* tcNeedle, u32 tnNeedleLength);
	u64						ioss_validateDebuggerDll						(s8* tcDllPathname, u32 tnDllPathnameLength, u32 tnUniqueId);
	void					ioss_createVisibleWindow						(SOssWindow* tisw, SOssWindowLL** tow);
	void					ioss_signalWindowFocus							(u64 tnOsHandle);
	void					ioss_lockSemaphore								(u64 semaphore);
	void					ioss_unlockSemaphore							(u64 semaphore);
	void					ioss_deleteVisibleWindow						(SOssWindowLL* w);
	LRESULT CALLTYPE		ioss_wndProc_Message							(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	LRESULT CALLTYPE		ioss_wndProc_Visible							(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	void					ioss_checkWindowResize							(HWND hwnd, MINMAXINFO* tmmi);
	void					ioss_createBitmap								(HWND hwnd);
	u64						ioss_createDibWithBitBuffer						(HDC thDC, u32 tnWidth, u32 tnHeight, BITMAPINFO* tbi, s8** tbd, u32* tnActualWidth);
	void					ioss_initializeBackground						(u32 tnWidth, u32 tnHeight, u32 tnBackColor, s8* tbd, u32 tnActualWidth);
	u32						ioss_computeActualWidth							(u32 tnWidth);
	bool					ioss_paintWindow								(HWND hwnd);
	void					ioss_deriveMouseInformation						(u32* tnX, u32* tnY, u32* tnButtons, u32* tnKeyFlags, u32 tnWinKeys, u32 tnXlowYhigh);
	void					ioss_recordMouseEvent							(HWND hwnd, u32 tnEVent, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeyFlags);
	void					ioss_deriveKeyboardInformation					(u32* tnKey, u32* tnKeyFlags, s8* tcAscii, s16* tuUnicode, u32 tnVkey, _iswSwindowExtraKeyData* tsXKeyInfo);
	void					ioss_recordKeyboardEvent						(HWND hwnd, u32 tnEVent, u32 tnKey, u32 tnKeyFlags, _iswSwindowExtraKeyData* tsXKeyInfo, s8 tcAscii, s16 tuUnicode);
	void					ioss_signalMove									(HWND hwnd, u32 tnX, u32 tnY);
	void					ioss_recreateBitmap								(HWND hwnd, u32 tnWidth, u32 tnHeight);		// Note:  The resized size includes any OSS window styles
	u32						ioss_getWindowStyle								(SOssWindow* tisw);
	f32						ioss_distanceBetween							(u32 tnX1, u32 tnY1, u32 tnX2, u32 tnY2);
	void					ioss_translateWindowsToVvmKey					(u32* tnKey, u32 tnVkey);
	bool					iioss_signalWindowFocusCallbacksCallback		(SStartEndCallback* cb);
	void					ioss_signalWindowUnloadCallback					(HWND hwnd);
	void					ioss_signalWindowClosedCallback					(SOssWindowLL* w);
	u64						ioss_lowLevel_bitBlt_Sgra_onto_ossWindow		(SOssWindowLL* tow, SBGRA* bd, u32 width, u32 height);
	bool					ioss_openAndReadBitmapFile						(s8* tcPathname, SBitmapHeader* tbh, SBitmapInfo* tbi, s8** tbd, u32* tnResult);
	void					ioss_allocateSBGRAandCopy32Bit_BitmapTopDown	(SBGRA** trgbad, SBitmapHeader* tbh, SBitmapInfo* tbi, SBGRA* lrgbas,    u32* tnResult, u32 tnErrorValue);
	void					ioss_allocateSBGRAandCopy32Bit_BitmapBottomUp	(SBGRA** trgbad, SBitmapHeader* tbh, SBitmapInfo* tbi, SBGRA* lrgbas,    u32* tnResult, u32 tnErrorValue);
	void					ioss_allocateSBGRAandCopy24Bit_BitmapTopDown	(SBGRA** trgbad, SBitmapHeader* tbh, SBitmapInfo* tbi, SRGB*  lrgbsRoot, u32* tnResult, u32 tnErrorValue);
	void					ioss_allocateSBGRAandCopy24Bit_BitmapBottomUp	(SBGRA** trgbad, SBitmapHeader* tbh, SBitmapInfo* tbi, SRGB*  lrgbsRoot, u32* tnResult, u32 tnErrorValue);
	LRESULT CALLTYPE		iioss_timerProc_10ms							(HWND hwnd, UINT msg, UINT_PTR idEvent, DWORD dwTime);
	bool					iioss_update10msTimersCallback					(SStartEndCallback* cb);
	DWORD CALLTYPE			iioss_1MsTimerThread							(LPVOID lpParameter);
	VOID CALLTYPE			iiioss_1MsTimerThreadTimerAPCProc				(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue);
	void					iioss_sharedAsciiCloseFileLocksCallback			(void* ptr, u64 tnParam);
	bool					iioss_reallocAndFreeCallback					(SStartEndCallback* cb);
	u64						ioss_breakoutAsciiTextDataIntoLines_ScanLine	(s8* tcData, u64 tnMaxLength, u64* tnLength, u64* tnWhitespaces);

	// SOssLines
	s32						ioss_translateSOssLinesToSOssCompsTest			(s8* tcHaystack, s8* tcNeedle, s32 tnLength);

	// SOssComps
	bool					iioss_translateSOssCompsToOthersCallback								(SStartEndCallback* cb);
	void					iioss_translateSOssCompsToOthersCallback__insertCompByCompCallback		(SOssComp* compRef, SOssComp* compNew, bool tlInsertAfter);
	void					iioss_translateSOssCompsToOthersCallback__insertCompByParamsCallback	(SOssComp* compRef, SOssLine* line, u32 tniCode, u64 tnStart, s64 tnLength, bool tlInsertAfter);
	void					iioss_translateSOssCompsToOthersCallback__deleteCompsCallback			(SOssComp* comp, SOssLine* line);
	SOssComp*				iioss_translateSOssCompsToOthersCallback__cloneCompsCallback			(SOssComp* comp, SOssLine* line);
	SOssComp*				iioss_translateSOssCompsToOthersCallback__mergeCompsCallback			(SOssComp* comp, SOssLine* line, u32 tnCount, u32 tniCodeNew);

	void					ioss_setFindFileStatus							(SFindFile* tsFileInfo, WIN32_FIND_DATAA* twfd);
	void					ioss_convertFileTimeToSDateTime					(SFileTime* tsDateTime, FILETIME* tsFiletime);

	SScreen*				ioss_createScreen								(u64 tnAssociatedId);
	SCanvas*				ioss_createCanvas								(u64 tnAssociatedId, u32 tnWidth, u32 tnHeight, SBGRA tnBackColor);
	SRegion*				ioss_createRegion								(u64 tnAssociatedId, SRegionState* tsState, u32 tnType, f32 ulx, f32 uly, f32 lrx, f32 lry, SCallbacks* callback, SStartEnd* events);

	// TODO:  to be added later: regions need to be able to trigger custom region events (see common.h's Custom event)
	bool					iioss_findCanvasCallback						(SStartEndCallback* cb);
	SRegion*				ioss_appendRegionToRegion						(SRegion* trParent, SRegion* trChild, u64 tnAssociatedId, SRegionState* tsState, u32 tnX, u32 tnY, SCallbacks* callback);
	void					iioss_createRegionAppendEventsCallback			(SStartEndCallback* cb);
	void					iivvm_screenRefreshCallback						(SStartEndCallback* cb);

	bool					iioss_findSOssWindowLLByHwndCallback			(SStartEndCallback* cb);
	bool					iioss_findSOssWindowLLByScreenId				(SStartEndCallback* cb);
	bool					iioss_findSOssWindowByOssWindowIdCallback		(SStartEndCallback* cb);

	BOOL CALLBACK			iioss_enumerateMonitors							(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
	void					iioss_enumerateMonitorsIterateCallback			(SStartEndCallback* cb);


//////////
//
// Support for plugins
//
//////
	_isSInterfacePlugin*	ioss_plugin_register							(u64 DllInstance);
	u64						ioss_plugin_unregister							(u64 DllInstance);
	bool					ioss_plugin_registerCallback					(SStartEndCallback* cb);
