//////////
//
// /libsf/vvm/common/common_vvmoss.h
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//	   Feb.25.2014
//////
// Change log:
//     Feb.25.2014 - Development on 0.70 begins
//	   Nov.07.2012 - 0.60 development begins
//	   Sep.29.2012 - PBL v1.0 license included directly in source files.
//	   Sep.19.2012 - Initial creation
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




#ifndef _OSS_COMPILING
	struct SOssWindowLL;

	//////////
	//
	// The following variables and function define the interface to VVMOSS.
	// By including this file and calling iLoadVvmOssFunctions() from the vvm_firstCallback() callback
	// in the DLL ... all things become accessible.
	//
	// Note:  To directly access the VVM-specific code, use common_vvmoss.h.
	//
	//////
		const s8		cgcOssFirstCallback[]									= "oss_firstCallback";
		const s8		cgcOssBootstrapInitialization[]							= "oss_bootstrapInitialization";
		const s8		cgcOssInitialization[]									= "oss_initialization";
		const s8		cgcOssGetVersion[]										= "oss_getVersion";
		const s8		cgcOssCreateMessageWindow[]								= "oss_createMessageWindow";
		const s8		cgcOssCreateVisibleWindow[]								= "oss_createVisibleWindow";

		const s8		cgcOssPluginRegisterFunction[]							= "oss_plugin_registerFunction";
		const s8		cgcOssPluginUnregisterFunction[]						= "oss_plugin_unregisterFunction";

		const s8		cgcOssGetSystemInfo[]									= "oss_getSystemInfo";
		const s8		cgcOssSleep[]											= "oss_sleep";
		const s8		cgcOssDateTimeGet[]										= "oss_dateTimeGet";
		const s8		cgcOssChangePathnameExtension[]							= "oss_changePathnameExtension";
		const s8		cgcOssValidateFilenameCharacter[]						= "oss_validateFilenameCharacter";

		const s8		cgcOssDeleteScreen[]									= "oss_deleteScreen";
		const s8		cgcOssDeleteCanvas[]									= "oss_deleteCanvas";

		const s8		cgcOssCreateScreenAndVisibleWindow[]					= "oss_createScreenAndVisibleWindow";
		const s8		cgcOssCreateRegionForScreen[]							= "oss_createRegionForScreen";
		const s8		cgcOssCreateCanvasForScreen[]							= "oss_createCanvasForScreen";
		const s8		cgcOssCreateCanvas[]									= "oss_createCanvas";
		const s8		cgcOssCreateRegion[]									= "oss_createRegion";
		const s8		cgcOssCreateRegionAndCanvas[]							= "oss_createRegionAndCanvas";
		const s8		cgcOssCreateFontHandle[]								= "oss_createFontHandle";

		const s8		cgcOssScreenMouseSetEventCallback[]						= "oss_screenMouseSetEventCallback";
		const s8		cgcOssScreenMouseRemoveEventCallback[]					= "oss_screenMouseRemoveEventCallback";
		const s8		cgcOssScreenMouseGetEventCallbacksList[]				= "oss_screenMouseGetEventCallbacksList";
		const s8		cgcOssScreenKeyboardSetEventCallback[]					= "oss_screenKeyboardSetEventCallback";
		const s8		cgcOssScreenKeyboardRemoveEventCallback[]				= "oss_screenKeyboardRemoveEventCallback";
		const s8		cgcOssScreenKeyboardGetEventCallbacksList[]				= "oss_screenKeyboardGetEventCallbacksList";

		const s8		cgcOssFindSOssWindowLLByHwnd[]							= "oss_findSOssWindowLLByHwnd";
		const s8		cgcOssFindSOssWindowLLByScreenId[]						= "oss_findSOssWindowLLByScreenId";
		const s8		cgcOssFind_iswSOssWindowLL_By_iOssWindowId[]			= "oss_find_iswSOssWindowLL_By_iOssWindowId";

		const s8		cgcOssLoadBitmapFromDisk[]								= "oss_bitmapLoadFromDisk";
		const s8		cgcOssSaveBitmapToDisk[]								= "oss_bitmapSaveToDisk";
		const s8		cgcOssCreateSystemFont[]								= "oss_systemCreateFont";
		const s8		cgcOssCreateSystemBitmap[]								= "oss_systemCreateBitmap";
		const s8		cgcOssFindSystemFontByHandle[]							= "oss_systemFindFontByHandle";

		const s8		cgcOssCreateScreenTemplate[]							= "oss_screenCreateTemplate";
		const s8		cgcOssComputeMonitorCoordinates[]						= "oss_screenComputeMonitorCoordinates";
		const s8		cgcOssEnumerateMonitors[]								= "oss_screenEnumerateMonitors";
		const s8		cgcOssGetScreenDimensions[]								= "oss_screenGetDimensions";
		const s8		cgcOssSetFocus[]										= "oss_setFocus";

		const s8		cgcOssLowLevelBitBltCanvasBgraOntoOssRgb[]				= "oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb";
		const s8		cgcOssLowLevelBitBltOssRgbOntoCanvasBgra[]				= "oss_lowLevel_bitBlt_ossRgb_onto_canvasBgra";

		const s8		cgcOssGetNextMessage[]									= "oss_getNextMessage";
		const s8		cgcOssMessageBox[]										= "oss_messageBox";
		const s8		cgcOssMessageBoxUnicode[]								= "oss_messageBoxUnicode";
		const s8		cgcOssDrawText[]										= "oss_drawText";

		const s8		cgcOssAlloc[]											= "oss_alloc";
		const s8		cgcOssRealloc[]											= "oss_realloc";
		const s8		cgcOssFree[]											= "oss_free";

		#include "common_oss_plugins.h"

		const s8		cgcOssBreakoutAsciiTextDataIntoSOssLines[]				= "oss_breakoutAsciiTextIntoSOssLines";
		const s8		cgcOssTranslateSOssLinesToSOssComps[]					= "oss_translateSOssLinesToSOssComps";
		const s8		cgcOssTranslateSOssCompsToOthers[]						= "oss_translateSOssCompsToOthers";
		const s8		cgcOssWriteSOssLineSequenceToDisk[]						= "oss_writeSOssLineSequenceToDisk";
		const s8		cgcOssWriteSOssLineSequenceCompsToDisk[]				= "oss_writeSOssLineSequenceCompsToDisk";
		const s8		cgcOssWriteSOssLineSequenceCompsDebuggingToDisk[]		= "oss_writeSOssLineSequenceCompsDebuggingToDisk";
		const s8		cgcOssFindNextSOssCompBy_iCode[]						= "oss_findNextSOssCompBy_iCode";
		const s8		cgcOssSkipPastSOssComp_iCode[]							= "oss_skipPastSOssComp_iCode";
		const s8		cgcOssCombine2SOssComps[]								= "oss_combine2SOssComps";
		const s8		cgcOssCombine3SOssComps[]								= "oss_combine3SOssComps";
		const s8		cgcOssCombineAllBetweenSOssComps[]						= "oss_combineAllBetweenSOssComps";
		const s8		cgcOssCombineAllAfterSOssComp[]							= "oss_combineAllAfterSOssComp";
		const s8		cgcOssCombineAllCasks[]									= "oss_combineAllCasks";
		const s8		cgcOssRemoveExtraneousWhitespaceSOssComps[]				= "oss_removeExtraneousWhitespaceSOssComps";
		const s8		cgcOssFindFirstOccurrenceOfAsciiCharacter[]				= "oss_findFirstOccurrenceOfAsciiCharacter";

		const s8		cgcOssSharedAsciiOpenFile[]								= "oss_sharedAsciiOpenFile";
		const s8		cgcOssSharedAsciiSeekFile[]								= "oss_sharedAsciiSeekFile";
		const s8		cgcOssSharedAsciiReadFile[]								= "oss_sharedAsciiReadFile";
		const s8		cgcOssSharedAsciiWriteFile[]							= "oss_sharedAsciiWriteFile";
		const s8		cgcOssSharedAsciiLockFile[]								= "oss_sharedAsciiLockFile";
		const s8		cgcOssSharedAsciiUnlockFile[]							= "oss_sharedAsciiUnlockFile";
		const s8		cgcOssSharedAsciiCloseFile[]							= "oss_sharedAsciiCloseFile";
		const s8		cgcOssSharedAsciiFileSize[]								= "oss_sharedAsciiFileSize";
		const s8		cgcOssSharedAsciiGetTempFilename[]						= "oss_sharedAsciiGetTempFilename";
		const s8		cgcOssSharedAsciiDeleteFile[]							= "oss_sharedAsciiDeleteFile";
		const s8		cgcOssSharedAsciiWriteOutFile[]							= "oss_sharedAsciiWriteOutFile";

		const s8		cgcOssFindFirstFile[]									= "oss_fileFindFirst";
		const s8		cgcOssFindNextFile[]									= "oss_fileFindNext";
		const s8		cgcOssFindClose[]										= "oss_fileFindClose";

		const s8		cgcOssThreadCreate[]									= "oss_threadCreate";
		const s8		cgcOssThreadSuspend[]									= "oss_threadSuspend";
		const s8		cgcOssThreadResume[]									= "oss_threadResume";
		const s8		cgcOssThreadTerminate[]									= "oss_threadTerminate";

		const s8		cgcOssCreateSemaphore[]									= "oss_createSemaphore";
		const s8		cgcOssLockSemaphore[]									= "oss_lockSemaphore";
		const s8		cgcOssTryLockSemaphore[]								= "oss_tryLockSemaphore";
		const s8		cgcOssUnlockSemaphore[]									= "oss_unlockSemaphore";
		const s8		cgcOssDeleteSemaphore[]									= "oss_deleteSemaphore";

		const s8		cgcOssEnableBreakpoints[]								= "oss_enableBreakpoints";
		const s8		cgcOssDisableBreakpoints[]								= "oss_disableBreakpoints";




	//////////
	//
	// VVMOSS function prototype definitions.  These must match the vo_defs.h, as
	// well as the implementation in their associated vo_*.cpp files.
	//
	// See devhelp.txt.
	//
	//////
		u64				(CALLTYPE *oss_firstCallback)							(u32 tnDoNotLoadOptions);
		void			(CALLTYPE *oss_bootstrapInitialization)					(void);
		void			(CALLTYPE *oss_initialization)							(void);
		const s8*		(CALLTYPE *oss_getVersion)								(void);
		bool			(CALLTYPE *oss_createMessageWindow)						(void);
		u64				(CALLTYPE *oss_createVisibleWindow)						(SOssWindow* tisw, u64 tnScreenId);


	//////////
	//
	// Support for plugins
	//
	//////
		u64				(CALLTYPE *oss_plugin_registerFunction)					(u64 tnInstanceId, u64 tnFunction, f32 tfVersion, u32 tnBuild, const u8* tcMetaName, u64 tnFunc);
		u64				(CALLTYPE *oss_plugin_unregisterFunction)				(u64 tnInstanceId, u64 tnFunction);


	//////////
	//
	// Basic system functions
	//
	//////
			void			(CALLTYPE *oss_getSystemInfo)							(SSysInfo* tsi);
			void			(CALLTYPE *oss_sleep)									(u32 tnMilliseconds);
			void			(CALLTYPE *oss_dateTimeGet)								(SDateTime* tdt);
			s8*				(CALLTYPE *oss_changePathnameExtension)					(s8* tcPathname, s8* tcNewPathname);
			bool			(CALLTYPE *oss_validateFilenameCharacter)				(s8* tcPathname, u64 tnPathnameLength, u64* tnErrorPosition);


	//////////
	//
	// Window and canvas related functions
	// All canvases are 32-bit with an alpha layer.
	// All windows use 24-bit presentations.
	//
	//////
			// Clean house
			u64				(CALLTYPE *oss_deleteScreen)							(SScreen* ts);
			u64				(CALLTYPE *oss_deleteCanvas)							(SCanvas* tc);

			// Visible window information
			SScreen*		(CALLTYPE *oss_createScreenAndVisibleWindow)			(u64 tnAssociatedId, SOssWindow* tisw/*tisw was created by oss_screenCreateTemplate()*/);
			SRegion*		(CALLTYPE *oss_createRegionForScreen)					(SScreen* ts, SCallbacks* callbacks, SStartEnd* events, SRegionState* trs);
			SCanvas*		(CALLTYPE *oss_createCanvasForScreen)					(SScreen* ts);
			SCanvas*		(CALLTYPE *oss_createCanvas)							(u64 tnAssociatedId, u32 tnWidth, u32 tnHeight, SBGRA tnBackColor);
			SRegion*		(CALLTYPE *oss_createRegion)							(u64 tnAssociatedId, u32 tnType, f32 ulx, f32 uly, f32 lrx, f32 lry, SCallbacks* callbacks, SStartEnd* events, SRegionState* trs);
			bool			(CALLTYPE *oss_createRegionAndCanvas)					(u64 tnAssociatedId, SBGRA tnBackColor, f32 ulx, f32 uly, f32 lrx, f32 lry, SCanvas** tc, SRegion** tr, SRegionState* regionState, SCallbacks* callbacks, SStartEnd* events);
			u64				(CALLTYPE *oss_createFontHandle)						(s8* fontName, u32 fontWidth, bool bold, bool italics, bool underline, bool strikethrough);

			u64				(CALLTYPE *oss_screenMouseSetEventCallback)				(u64 id, SCanvas* tc, SEvent* event);
			u64				(CALLTYPE *oss_screenMouseRemoveEventCallback)			(u64 id, SCanvas* tc, SEvent* event);
			void			(CALLTYPE *oss_screenMouseGetEventCallbacksList)		(u64 id, SCanvas* tc, SEvent** events, u32* count);
			u64				(CALLTYPE *oss_screenKeyboardSetEventCallback)			(u64 id, SCanvas* tc, SEvent* event);
			u64				(CALLTYPE *oss_screenKeyboardRemoveEventCallback)		(u64 id, SCanvas* tc, SEvent* event);
			void			(CALLTYPE *oss_screenKeyboardGetEventCallbacksList)		(u64 id, SCanvas* tc, SEvent** events, u32* count);

			SOssWindowLL*	(CALLTYPE *oss_findSOssWindowLLByHwnd)					(HWND hwnd);
			SOssWindowLL*	(CALLTYPE *oss_findSOssWindowLLByScreenId)				(u64 tnScreenId);
			SOssWindowLL*	(CALLTYPE *oss_find_iswSOssWindowLL_By_iOssWindowId)	(u64 tnOssWindowId);

			// Only 24-bit or 32-bit bitmaps can be loaded from disk at present.
			u64				(CALLTYPE *oss_bitmapLoadFromDisk)						(s8* tcPathname, SCanvas** tc, u32* tnWidth, u32* tnHeight, SBGRA tnBackColor);
			u64				(CALLTYPE *oss_bitmapSaveToDisk)						(SCanvas* tc, SBGRA* bd, s8* tcPathname);
			u64				(CALLTYPE *oss_systemCreateFont)						(s8* fontName, u32 fontPointSize, bool bold, bool italics, bool underline, bool strikethrough);
			u64				(CALLTYPE *oss_systemCreateBitmap)						(u32 tnWidth, u32 tnHeight);
			u64				(CALLTYPE *oss_systemFindFontByHandle)					(u64 tnFontHandle);

			SOssWindow*		(CALLTYPE *oss_screenCreateTemplate)					(u64 id, u64 uniqueScreenId,
																						s8* tcCaption, u32 tnCaptionLength,
																						s32 tnX, s32 tnY,
																						u32 tnWidth, u32 tnHeight,
																						u32 tnWidthMin, u32 tnHeightMin,
																						u32 tnWidthMax, u32 tnHeightMax,
																						u32 ncUlx, u32 ncUly, u32 ncLrx, u32 ncLry, u32 ncBorder,
																						SBGRA tnForeColor, SBGRA tnBackColor,
																						bool tlResizable, bool tlMovable, bool tlClosable, bool tlVisible, bool tlBorder,
																						SCallbacksW* callbacks);
			SOssWindow*		(CALLTYPE *oss_screenEnumerateMonitors)					(SStartEnd* tsMonitors/*Returns SOssWindow* structures*/);
			void			(CALLTYPE *oss_screenComputeMonitorCoordinates)			(SOssWindow* tow, f32 tfPercent, u32 tnPosition, f32 tfMargin, s32* tnX, s32* tnY, u32* tnWidth, u32* tnHeight, u32* tnWidthMax, u32* tnHeightMax, u32* tnWidthMin, u32* tnHeightMin);
			bool			(CALLTYPE *oss_screenGetDimensions)						(u64 tnOssWindowId, s32* tnX, s32* tnY, u32* tnWidth, u32* tnHeight, u32* tnWidthMax, u32* tnHeightMax, u32* tnWidthMin, u32* tnHeightMin);

			u64				(CALLTYPE *oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb)	(u64 tnOssWindowId, SBGRA* bd, u32 width, u32 height);
			u64				(CALLTYPE *oss_lowLevel_bitBlt_ossRgb_onto_canvasBgra)	(u64 bdoss, s32 tnX, s32 tnY, u32 tnWidth, u32 tnHeight, SCanvas* tc, SBGRA* bdRoot);
			u64				(CALLTYPE *oss_getNextMessage)							(u32* message, void* extra);
			u64				(CALLTYPE *oss_messageBox)								(u64 id, s8* tcText, s8* tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);
			u64				(CALLTYPE *oss_messageBoxUnicode)						(u64 id, w16* tcText, w16* tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);
			u64				(CALLTYPE *oss_drawText)								(s8* tcText, u32 tnTextLength, s32 ulx, s32 uly, s32 lrx, s32 lry, SBGRA foreground, SBGRA background, u64 tnSystemFont, u64 tnSystemBitmap);


	//////////
	//
	// Memory allocation and related string operations exposed through the VVMOSS
	//
	// The VVM is a virtual machine, it needs a way to know what memory should be saved during
	// times of suspension, and restored upon resumption.
	//
	//////////
			void*			(CALLTYPE *oss_alloc)								(u64 tnSize, bool tlInitialize);
			void*			(CALLTYPE *oss_realloc)								(void* ptrOld, u64 tnNewSize);
			void*			(CALLTYPE *oss_free)								(void* ptr);


	//////////
	//
	// Sound plugin
	// The VVM will provide a sound stub functions, but if a plugin exists
	// the VVMOSS will load that plugin at startup and use the sound functions.
	//
	//////////
			//////////
			// See:		vo_plugins.cpp
			//			vo_plugins.h
			//			common_vvmoss_plugins.h
			//////


	//////////
	//
	// Lines and Components
	// Facilities are provided for parsing distinct bits of text found in text files.  These are
	// called components, and each line of a text file can be broken out, and then parsed for known
	// keywords using these facilities.  VASM (the VVM Assembler) uses this for all of its syntax
	// parsing of raw assembly source code files, for example.
	//
	//////////
			u64				(CALLTYPE *oss_breakoutAsciiTextIntoSOssLines)		(s8* tcData, u64 tnFileSize, SStartEnd* tseLines, u64 tnAllocSize, bool tlUseOssAlloc);
			SOssComp*		(CALLTYPE *oss_translateSOssLinesToSOssComps)		(SAsciiCompSearcher* tsComps, SOssLine* line);
			void			(CALLTYPE *oss_translateSOssCompsToOthers)			(SAsciiCompSearcher* tsComps, SOssLine* line);
			u64				(CALLTYPE *oss_writeSOssLineSequenceToDisk)			(s8* tcPathname, SStartEnd* tseLines);
			u64				(CALLTYPE *oss_writeSOssLineSequenceCompsToDisk)	(s8* tcPathname, SStartEnd* tseLines);
			u64				(CALLTYPE *oss_writeSOssLineSequenceCompsDebuggingToDisk)(s8* tcPathname, SStartEnd* tseLines);
			SOssComp*		(CALLTYPE *oss_findNextSOssCompBy_iCode)			(SOssComp* comp, u32 tniCode, SOssComp** compLastScanned);
			SOssComp*		(CALLTYPE *oss_skipPastSOssComp_iCode)				(SOssComp* comp, u32 tniCode);
			u32				(CALLTYPE *oss_combine2SOssComps)					(SOssLine* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2,                     u32 tniCodeCombined);
			u32				(CALLTYPE *oss_combine3SOssComps)					(SOssLine* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeNeedle3, u32 tniCodeCombined);
			u32				(CALLTYPE *oss_combineAllBetweenSOssComps)			(SOssLine* line, u32 tniCodeNeedle,                                          u32 tniCodeCombined);
			u32				(CALLTYPE *oss_combineAllAfterSOssComp)				(SOssLine* line, u32 tniCodeNeedle);
			u32				(CALLTYPE *oss_combineAllCasks)						(SOssComp* firstComp);
			u32				(CALLTYPE *oss_removeExtraneousWhitespaceSOssComps)	(SOssLine* line, u32 tniCodeWhitespace);
			bool			(CALLTYPE *oss_findFirstOccurrenceOfAsciiCharacter)	(s8* tcHaystack, u64 tnHaystackLength, s8 tcNeedle, u64* tnPosition);


	//////////
	//
	// ASCII File Access
	// Functions to access ASCII-based files.
	//
	//////////
			u64				(CALLTYPE *oss_sharedAsciiOpenFile)					(s8* tcPathname, bool tlExclusive, bool tlReadOnly, bool tlIfShared_DenyReads, bool tlIfShared_DenyWrites, bool tlAppendMode, bool tlTruncate, bool tlShortLived, bool tlTemporaryFile);
			u64				(CALLTYPE *oss_sharedAsciiSeekFile)					(u64 tnFileHandle, s64 tnDisplacement, u64 tnSource/*0=file offset, -1=relative backward, 1=relative forward*/);
			u64				(CALLTYPE *oss_sharedAsciiReadFile)					(u64 tnFileHandle, s8* tcDest,   u64 tnBytesToRead);
			u64				(CALLTYPE *oss_sharedAsciiWriteFile)				(u64 tnFileHandle, s8* tcSource, u64 tnBytesToWrite);
			u64				(CALLTYPE *oss_sharedAsciiLockFile)					(u64 tnFileHandle, u64 tnStart, u64 tnLength);
			u64				(CALLTYPE *oss_sharedAsciiUnlockFile)				(u64 tnFileHandle, u64 tnLockHandle);
			u64				(CALLTYPE *oss_sharedAsciiCloseFile)				(u64 tnFileHandle);
			u64				(CALLTYPE *oss_sharedAsciiFileSize)					(u64 tnFileHandle);
			s8*				(CALLTYPE *oss_sharedAsciiGetTempFilename)			(void);
			bool			(CALLTYPE *oss_sharedAsciiDeleteFile)				(s8* tcFullPathname);
			bool			(CALLTYPE *oss_sharedAsciiWriteOutFile)				(s8* tcFullPathname, s8* tcData, u32 tnDataLength);



	//////////
	//
	// Find files
	//
	//////////
			u64				(CALLTYPE *oss_fileFindFirst)						(SFindFile* tsFileInfo);
			bool			(CALLTYPE *oss_fileFindNext)						(u64 tnHandle, SFindFile* tsFileInfo);
			void			(CALLTYPE *oss_fileFindClose)						(u64 tnHandle, SFindFile* tsFileInfo);




	//////////
	//
	// Threading
	// These services are exposed by the VVMOSS to facilitate the needs of
	// creating a new thread for execution.	 These operate in an operating-system
	// neutral way externally, allowing the same function to always be called
	// with the expected results
	//
	//////////
			u64				(CALLTYPE *oss_threadCreate)						(u64 tnThreadAddress, void* data, bool tlStartSuspended);
			u64				(CALLTYPE *oss_threadSuspend)						(u64 ossData);
			u64				(CALLTYPE *oss_threadResume)						(u64 ossData);
			u64				(CALLTYPE *oss_threadTerminate)						(u64 ossData, u32 tnTerminationCode);


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
			u64				(CALLTYPE *oss_createSemaphore)						(void);
			void			(CALLTYPE *oss_lockSemaphore)						(u64 handle);
			bool			(CALLTYPE *oss_tryLockSemaphore)					(u64 handle);
			void			(CALLTYPE *oss_unlockSemaphore)						(u64 handle);
			void			(CALLTYPE *oss_deleteSemaphore)						(u64 handle);


	//////////
	//
	// Debugging
	// Used internally to trap for debugging breakpoints.  Allows conditional execution of something
	// until a condition arises, and only then will the debugger be trapped if internal breakpoints
	// have been enabled by an explicit call to oss_enableBreakpoints().
	//
	//////////
			void			(CALLTYPE *oss_enableBreakpoints)					(void);
			void			(CALLTYPE *oss_disableBreakpoints)					(void);


	//////////
	//
	// List of functions and their corresponding names.	 Used in iLoadVvmOssFunctions().
	// NOTE:  The items in this list must appear in the same order as their definitions above
	//
	//////
		void* gVvmOssFunctions[] =
		{
			(void *)&oss_firstCallback,											(void *)cgcOssFirstCallback,
			(void *)&oss_bootstrapInitialization,								(void *)cgcOssBootstrapInitialization,
			(void *)&oss_initialization,										(void *)cgcOssInitialization,
			(void *)&oss_getVersion,											(void *)cgcOssGetVersion,
			(void *)&oss_createMessageWindow,									(void *)cgcOssCreateMessageWindow,
			(void *)&oss_createVisibleWindow,									(void *)cgcOssCreateVisibleWindow,

			(void *)&oss_plugin_registerFunction,								(void *)cgcOssPluginRegisterFunction,
			(void *)&oss_plugin_unregisterFunction,								(void *)cgcOssPluginUnregisterFunction,

			(void *)&oss_getSystemInfo,											(void *)cgcOssGetSystemInfo,
			(void *)&oss_sleep,													(void *)cgcOssSleep,
			(void *)&oss_dateTimeGet,											(void *)cgcOssDateTimeGet,
			(void *)&oss_changePathnameExtension,								(void *)cgcOssChangePathnameExtension,
			(void *)&oss_validateFilenameCharacter,								(void *)cgcOssValidateFilenameCharacter,

			(void *)&oss_deleteScreen,											(void *)cgcOssDeleteScreen,
			(void *)&oss_deleteCanvas,											(void *)cgcOssDeleteCanvas,

			(void *)&oss_createScreenAndVisibleWindow,							(void *)cgcOssCreateScreenAndVisibleWindow,
			(void *)&oss_createRegionForScreen,									(void *)cgcOssCreateRegionForScreen,
			(void *)&oss_createCanvasForScreen,									(void *)cgcOssCreateCanvasForScreen,
			(void *)&oss_createCanvas,											(void *)cgcOssCreateCanvas,
			(void *)&oss_createRegion,											(void *)cgcOssCreateRegion,
			(void *)&oss_createRegionAndCanvas,									(void *)cgcOssCreateRegionAndCanvas,
			(void *)&oss_createFontHandle,										(void *)cgcOssCreateFontHandle,

			(void *)&oss_screenMouseSetEventCallback,							(void *)cgcOssScreenMouseSetEventCallback,
			(void *)&oss_screenMouseRemoveEventCallback,						(void *)cgcOssScreenMouseRemoveEventCallback,
			(void *)&oss_screenMouseGetEventCallbacksList,						(void *)cgcOssScreenMouseGetEventCallbacksList,
			(void *)&oss_screenKeyboardSetEventCallback,						(void *)cgcOssScreenKeyboardSetEventCallback,
			(void *)&oss_screenKeyboardRemoveEventCallback,						(void *)cgcOssScreenKeyboardRemoveEventCallback,
			(void *)&oss_screenKeyboardGetEventCallbacksList,					(void *)cgcOssScreenKeyboardGetEventCallbacksList,

			(void *)&oss_findSOssWindowLLByHwnd,								(void *)cgcOssFindSOssWindowLLByHwnd,
			(void *)&oss_findSOssWindowLLByScreenId,							(void *)cgcOssFindSOssWindowLLByScreenId,
			(void *)&oss_find_iswSOssWindowLL_By_iOssWindowId,					(void *)cgcOssFind_iswSOssWindowLL_By_iOssWindowId,

			(void *)&oss_bitmapLoadFromDisk,									(void *)cgcOssLoadBitmapFromDisk,
			(void *)&oss_bitmapSaveToDisk,										(void *)cgcOssSaveBitmapToDisk,

			(void *)&oss_systemCreateFont,										(void *)cgcOssCreateSystemFont,
			(void *)&oss_systemCreateBitmap,									(void *)cgcOssCreateSystemBitmap,
			(void *)&oss_systemFindFontByHandle,								(void *)cgcOssFindSystemFontByHandle,

			(void *)&oss_screenCreateTemplate,									(void *)cgcOssCreateScreenTemplate,
			(void *)&oss_screenComputeMonitorCoordinates,						(void *)cgcOssComputeMonitorCoordinates,
			(void *)&oss_screenEnumerateMonitors,								(void *)cgcOssEnumerateMonitors,
			(void *)&oss_screenGetDimensions,									(void *)cgcOssGetScreenDimensions,

			(void *)&oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb,				(void *)cgcOssLowLevelBitBltCanvasBgraOntoOssRgb,
			(void *)&oss_lowLevel_bitBlt_ossRgb_onto_canvasBgra,				(void *)cgcOssLowLevelBitBltOssRgbOntoCanvasBgra,

			(void *)&oss_getNextMessage,										(void *)cgcOssGetNextMessage,
			(void *)&oss_messageBox,											(void *)cgcOssMessageBox,
			(void *)&oss_messageBoxUnicode,										(void *)cgcOssMessageBoxUnicode,

			(void *)&oss_drawText,												(void *)cgcOssDrawText,

			(void *)&oss_alloc,													(void *)cgcOssAlloc,
			(void *)&oss_realloc,												(void *)cgcOssRealloc,
			(void *)&oss_free,													(void *)cgcOssFree,

#ifndef _NATIVE_CALLS
			(void *)&oss_soundInitialize,										(void *)cgcOssSoundInitialize,
			(void *)&oss_soundCreateTone,										(void *)cgcOssSoundCreateTone,
			(void *)&oss_soundCreateStream,										(void *)cgcOssSoundCreateStream,
			(void *)&oss_soundSetVolume,										(void *)cgcOssSoundSetVolume,
			(void *)&oss_soundPlayStart,										(void *)cgcOssSoundPlayStart,
			(void *)&oss_soundPlayCancel,										(void *)cgcOssSoundPlayCancel,
			(void *)&oss_soundDelete,											(void *)cgcOssSoundDelete,
#endif

			(void *)&oss_breakoutAsciiTextIntoSOssLines,						(void *)cgcOssBreakoutAsciiTextDataIntoSOssLines,
			(void *)&oss_translateSOssLinesToSOssComps,							(void *)cgcOssTranslateSOssLinesToSOssComps,
			(void *)&oss_translateSOssCompsToOthers,							(void *)cgcOssTranslateSOssCompsToOthers,
			(void *)&oss_writeSOssLineSequenceToDisk,							(void *)cgcOssWriteSOssLineSequenceToDisk,
			(void *)&oss_writeSOssLineSequenceCompsToDisk,						(void *)cgcOssWriteSOssLineSequenceCompsToDisk,
			(void *)&oss_writeSOssLineSequenceCompsDebuggingToDisk,				(void *)cgcOssWriteSOssLineSequenceCompsDebuggingToDisk,
			(void *)&oss_findNextSOssCompBy_iCode,								(void *)cgcOssFindNextSOssCompBy_iCode,
			(void *)&oss_skipPastSOssComp_iCode,								(void *)cgcOssSkipPastSOssComp_iCode,
			(void *)&oss_combine2SOssComps,										(void *)cgcOssCombine2SOssComps,
			(void *)&oss_combine3SOssComps,										(void *)cgcOssCombine3SOssComps,
			(void *)&oss_combineAllBetweenSOssComps,							(void *)cgcOssCombineAllBetweenSOssComps,
			(void *)&oss_combineAllAfterSOssComp,								(void *)cgcOssCombineAllAfterSOssComp,
			(void *)&oss_combineAllCasks,										(void *)cgcOssCombineAllCasks,
			(void *)&oss_removeExtraneousWhitespaceSOssComps,					(void *)cgcOssRemoveExtraneousWhitespaceSOssComps,
			(void *)&oss_findFirstOccurrenceOfAsciiCharacter,					(void *)cgcOssFindFirstOccurrenceOfAsciiCharacter,

			(void *)&oss_sharedAsciiOpenFile,									(void *)cgcOssSharedAsciiOpenFile,
			(void *)&oss_sharedAsciiSeekFile,									(void *)cgcOssSharedAsciiSeekFile,
			(void *)&oss_sharedAsciiReadFile,									(void *)cgcOssSharedAsciiReadFile,
			(void *)&oss_sharedAsciiWriteFile,									(void *)cgcOssSharedAsciiWriteFile,
			(void *)&oss_sharedAsciiLockFile,									(void *)cgcOssSharedAsciiLockFile,
			(void *)&oss_sharedAsciiUnlockFile,									(void *)cgcOssSharedAsciiUnlockFile,
			(void *)&oss_sharedAsciiCloseFile,									(void *)cgcOssSharedAsciiCloseFile,
			(void *)&oss_sharedAsciiFileSize,									(void *)cgcOssSharedAsciiFileSize,
			(void *)&oss_sharedAsciiGetTempFilename,							(void *)cgcOssSharedAsciiGetTempFilename,
			(void *)&oss_sharedAsciiDeleteFile,									(void *)cgcOssSharedAsciiDeleteFile,
			(void *)&oss_sharedAsciiWriteOutFile,								(void *)cgcOssSharedAsciiWriteOutFile,

			(void *)&oss_fileFindFirst,											(void *)cgcOssFindFirstFile,
			(void *)&oss_fileFindNext,											(void *)cgcOssFindNextFile,
			(void *)&oss_fileFindClose,											(void *)cgcOssFindClose,

			(void *)&oss_threadCreate,											(void *)cgcOssThreadCreate,
			(void *)&oss_threadSuspend,											(void *)cgcOssThreadSuspend,
			(void *)&oss_threadResume,											(void *)cgcOssThreadResume,
			(void *)&oss_threadTerminate,										(void *)cgcOssThreadTerminate,

			(void *)&oss_createSemaphore,										(void *)cgcOssCreateSemaphore,
			(void *)&oss_lockSemaphore,											(void *)cgcOssLockSemaphore,
			(void *)&oss_tryLockSemaphore,										(void *)cgcOssTryLockSemaphore,
			(void *)&oss_unlockSemaphore,										(void *)cgcOssUnlockSemaphore,
			(void *)&oss_deleteSemaphore,										(void *)cgcOssDeleteSemaphore,

			(void *)&oss_enableBreakpoints,										(void *)cgcOssEnableBreakpoints,
			(void *)&oss_disableBreakpoints,									(void *)cgcOssDisableBreakpoints
		};
		u32 gVvmOssFunctionCount = sizeof(gVvmOssFunctions) / (2 * sizeof(void*));




	//////////
	//
	// Attempt to load vvmoss.dll and access all required functions
	//
	//////
		HINSTANCE ossDllInstance = NULL;
		bool iLoadOssFunctionsFromDll(void)
		{
			u32			lnI;
			s8*			lcFuncName;
			void**		lcFuncAddress;
			void*		lcAddress;
			s8			buffer[1024];


			// Try to load the dll
			if (!ossDllInstance)
			{
				ossDllInstance = LoadLibraryA("oss.dll");
				if (!ossDllInstance)
				{
					// There was an error loading the dll
					return(false);
				}
			}
			// If we get here, we have a candidate.
			// But, to be valid it has to have the required functions

			// Now, repeatedly call back that address with the request to all of the function addresses
			for (lnI = 0; lnI < gVvmOssFunctionCount; lnI++)
			{
				// Grab the details of this entry
				lcFuncAddress	= (void**)gVvmOssFunctions[(lnI * 2) + 0];		// Grab the indirect address to store
				lcFuncName		= (s8*)   gVvmOssFunctions[(lnI * 2) + 1];		// Grab the function name to request

				// Ask the VVM for this specific function location
				lcAddress = GetProcAddress(ossDllInstance, lcFuncName);

				// Process the result
				if (!lcAddress)
				{
					// The specified functionality is not available
					// Note:  By design, this should never happen.  It is the result of a programming error.
					sprintf_s(buffer, sizeof(buffer), "Error accessing: %s\000", lcFuncName);
					MessageBoxA(NULL, buffer, "VVMOSS Initialization Error", MB_OK);
					// The specified functionality is not available
					return(false);
				}
				// If we get here, this function was found and we can store it
				*lcFuncAddress = lcAddress;
			}
			// When we get here, we've made the full connection to the vvmoss.dll functions
			return(true);
		}
#endif
