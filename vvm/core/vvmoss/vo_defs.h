//////////
//
// /libsf/vvm/vvmoss/vo_defs.h
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
// vo.cpp
//////
	u64 CALLTYPE			oss_firstCallback								(u64 tnDebuggerInterfaceAddress);
	void CALLTYPE			oss_bootstrapInitialization						(u64 tnDebuggerInterfaceAddress);
	void CALLTYPE			oss_initialization								(u64 tnDebuggerInterfaceAddress);
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
		void CALLTYPE			oss_dateTimeGet							(SDateTime* tdt);
		s8* CALLTYPE			oss_changePathnameExtension					(s8* tcPathname, s8* tcNewPathname);
		bool CALLTYPE			oss_validateFilenameCharacter				(s8* tcPathname, u64 tnPathnameLength, u64* tnErrorPosition);
		u64 CALLTYPE			oss_getNextUniqueId							(void);
		u64 CALLTYPE			oss_getNextN_UniqueIds						(u64* tnArrayBase, u32 tnCount);


//////////
//
// Window and canvas related functions
// All canvases are 32-bit with an alpha layer.
// All windows use 24-bit presentations.
//
//////
		u64 CALLTYPE			oss_deleteScreen							(SScreen* ts);
		u64 CALLTYPE			oss_deleteCanvas							(SCanvas* tc);

		SScreen* CALLTYPE		oss_createScreenAndVisibleWindow			(u64 tnAssociatedId, SOssWindow*  tisw/*tisw was created by oss_screenCreateTemplate()*/);
		SRegion* CALLTYPE		oss_createRegionForScreen					(SScreen* ts, SCallbacks* callbacks, SStartEnd* events, SRegionState* trs);
		SCanvas* CALLTYPE		oss_createCanvasForScreen					(SScreen* ts);
		SCanvas* CALLTYPE	 	oss_createCanvas							(u64 tnAssociatedId, u32 tnWidth, u32 tnHeight, SBGRA tnBackColor);
		SRegion* CALLTYPE		oss_createRegion							(u64 tnAssociatedId, u32 tnType, f32 ulx, f32 uly, f32 lrx, f32 lry, SCallbacks* callbacks, SStartEnd* events, SRegionState* trs);
		bool CALLTYPE			oss_createRegionAndCanvas					(u64 tnAssociatedId, SBGRA tnBackColor, f32 ulx, f32 uly, f32 lrx, f32 lry, SCanvas** tc, SRegion** tr, SRegionState* regionState, SCallbacks* callbacks, SStartEnd* events);
		u64 CALLTYPE		 	oss_createFontHandle						(s8* fontName, u32 fontWidth, bool bold, bool italics, bool underline, bool strikethrough);

		u64 CALLTYPE			oss_screenRefresh							(SScreen* ts);
		bool CALLTYPE			oss_screenSetFocus							(SScreen *ts);

		SRegion* CALLTYPE		oss_regionDuplicate							(u64 tnAssociatedId, SRegion* templateRegion);
		u64 CALLTYPE			oss_regionDefaultPaint						(SRegion* tr);
		u64 CALLTYPE			oss_regionRefresh							(SRegion* tr, SRegion* trParent);

		u64 CALLTYPE		 	oss_canvasDrawFixedPointText				(SCanvas* tc, SBGRA* bd, u32 fontWidth, u32 fontHeight, s32 ulx, s32 uly,    s8*  text, u32 characterCount, SBGRA foreground, SBGRA background);
		u64 CALLTYPE		 	oss_canvasDrawText							(SCanvas* tc, SBGRA* bd, u64 fontHandle, s32 ulx, s32 uly, s32 lrx, s32 lry, s8*  tcText, u32 tnTextLength, SBGRA foreground, SBGRA background);
		u64 CALLTYPE		 	oss_canvasFrameRect							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border);
		u64 CALLTYPE		 	oss_canvasFillRect							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border, SBGRA background);
		u64 CALLTYPE		 	oss_canvasLine								(SCanvas* tc, SBGRA* bd, SXYF32* p1, SXYF32* p2, f32 lineThickness, SBGRA color, bool tlFloan);
		u64 CALLTYPE		 	oss_canvasArc								(SCanvas* tc, SBGRA* bd, s32 ox, s32 oy, f32 radius, f32 start, f32 end, s32 lineThickness, SBGRA line);
		u64 CALLTYPE			oss_canvasBezier							(SCanvas* tc, SBGRA* bd, SBezier* bez);
		SCanvas* CALLTYPE	 	oss_canvasExtract							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry);
		u64 CALLTYPE		 	oss_canvasColorize							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, SBGRA color);
		u64 CALLTYPE		 	oss_canvasGrayscale							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry);
		u64 CALLTYPE		 	oss_canvasGradient							(SCanvas* tc, SBGRA* bd, SBGRA ul, SBGRA ur, SBGRA lr, SBGRA ll);
		u64 CALLTYPE		 	oss_canvasBitBlt							(SCanvas* tsDst, bool tlDstAccumulator, s32 dulx, s32 duly, SCanvas* tsSrc, bool tlSrcAccumulator, s32 sulx, s32 suly, s32 slrx, s32 slry);
		u64 CALLTYPE			oss_canvasScale								(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap** tsScaleMap);
		u64 CALLTYPE			oss_canvasRotate							(SCanvas* tsDst, SBGRA* bdd, s32 ulx, s32 uly, SCanvas* tsSrc, SBGRA* bds, f32 tfRadians);
		u64 CALLTYPE			oss_canvasRotateAbout						(SCanvas* tsDst, SBGRA* bdd, s32 ulx, s32 uly, SCanvas* tsSrc, SBGRA* bds, f32 tfRadians, f32 ox, f32 oy);
		u64 CALLTYPE			oss_canvasPolygon							(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color);

		SCask* CALLTYPE			oss_caskDefineStandard						(u32 tnHeight, u32 tnWidth, u32 tnLeftStyle, u32 tnLeftState, u32 tnLeftPipCount, u32 tnLeftColor, csu8p tcLeftText, u32 tnRightStyle, u32 tnRightState, u32 tnRightPipCount, u32 tnRightColor, csu8p tcRightText);
		SCask* CALLTYPE			oss_caskDefineEncompassingRectangle			(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SRectXYXY* tsOuter);
		SCask* CALLTYPE			oss_caskDefineUpRectangle					(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter);
		SCask* CALLTYPE			oss_caskDefineDownRectangle					(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter);
		SCaskPip* CALLTYPE		oss_caskSetPipByValues						(SCask* cask, bool tlLeft, u32 tnPip, SBGRA tnPipColorNeutral, SBGRA tnPipColorOver, SBGRA tnPipColorClick, u64 tnEnterCallback, u64 tnLeaveCallback, u64 tnHoverCallback, u64 tnClickCallback, bool tlCreateCopy);
		SCaskPip* CALLTYPE		oss_caskSetPipByStruct						(SCask* cask, bool tlLeft, u32 tnPip, SCaskPip* caskPip, bool tlCreateCopy);
		SCask* CALLTYPE			oss_caskCreate								(SCask* cask, bool tlCreateCopy);
		SCanvas* CALLTYPE		oss_caskRefresh								(SCask* cask);

		u64 CALLTYPE			oss_screenMouseSetEventCallback				(u64 id, SCanvas* tc, SEvent* event);
		u64 CALLTYPE			oss_screenMouseRemoveEventCallback			(u64 id, SCanvas* tc, SEvent* event);
		void CALLTYPE			oss_screenMouseGetEventCallbacksList		(u64 id, SCanvas* tc, SEvent** events, u32* count);
		u64 CALLTYPE			oss_screenKeyboardSetEventCallback			(u64 id, SCanvas* tc, SEvent* event);
		u64 CALLTYPE			oss_screenKeyboardRemoveEventCallback		(u64 id, SCanvas* tc, SEvent* event);
		void CALLTYPE			oss_screenKeyboardGetEventCallbacksList		(u64 id, SCanvas* tc, SEvent** events, u32* count);

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

		void CALLTYPE			oss_screenComputeMonitorCoordinates				(SOssWindow* tow, f32 tfPercent, u32 tnPosition, f32 tfMargin, s32* tnX, s32* tnY, u32* tnWidth, u32* tnHeight, u32* tnWidthMax, u32* tnHeightMax, u32* tnWidthMin, u32* tnHeightMin);
		SOssWindow* CALLTYPE	oss_screenEnumerateMonitors						(SStartEnd* tsMonitors/*Returns SOssWindow* structures*/);
		bool CALLTYPE			oss_screenGetDimensions						(u64 tnOssWindowId, s32* tnX, s32* tnY, u32* tnWidth, u32* tnHeight, u32* tnWidthMax, u32* tnHeightMax, u32* tnWidthMin, u32* tnHeightMin);
		u64 CALLTYPE			oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb	(u64 tnOssWindowId, SBGRA* bd, u32 width, u32 height);
		u64 CALLTYPE			oss_lowLevel_bitBlt_ossRgb_onto_canvasBgra	(u64 bdoss, s32 tnX, s32 tnY, u32 tnWidth, u32 tnHeight, SCanvas* tc, SBGRA* bdRoot);
		u64 CALLTYPE			oss_getNextMessage							(u32* message, void* extra);
		u64 CALLTYPE			oss_messageBox								(u64 id, s8*  tcText, s8*  tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);
		u64 CALLTYPE			oss_messageBoxUnicode						(u64 id, w16* tuText, w16* tuCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);


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
// Common functions (previously in common.h)
//
//////
		// Prototype definitions
		u8* CALLTYPE			oss_duplicateString							(u8* ptr, u64 length);
		w16* CALLTYPE			oss_duplicateUnicodeString					(w16* tuText);
		SDatum* CALLTYPE		oss_datumSet								(SDatum*  datum,  u8* ptr, u64 length,                  bool tlFreeExisting);
		SDatum2* CALLTYPE		oss_datum2Set								(SDatum2* datum2, u8* ptr, u64 length, u64 totalLength, bool tlFreeExisting);
		SDatum* CALLTYPE		oss_datumDuplicate							(SDatum*  datumDst,  SDatum*  datumSrc);
		SDatum2* CALLTYPE		oss_datum2Duplicate							(SDatum2* datum2Dst, SDatum2* datum2Src);
		void CALLTYPE			oss_datumDelete								(SDatum*  datum);
		void CALLTYPE			oss_datum2Delete							(SDatum2* datum2);
		void CALLTYPE			oss_datum2SetNullString						(SDatum2* datum2, u64 length, bool tlInitialize);
		void CALLTYPE			oss_copyUpToShortestString					(u8* dst, u32 tnDstLength, u8* src, u32 tnSrcLength);
		s32 CALLTYPE			oss_wildcardMatchDatum						(SDatum* tsCandidate, SDatum* tsWildcardPattern, bool tlCaseSensitive);
		s32 CALLTYPE			oss_wildcardMatch							(csu8p candidate, csu8p wildcardPattern, bool tlCaseSensitive);
		w16* CALLTYPE			oss_asciiToUnicode							(u8* tcText, u32 tnTextLength);
		s8* CALLTYPE			oss_unicodeToAscii							(w16* tuText, u32 tnTextLength);
		w16 CALLTYPE			oss_asciiToUnicodeChar						(u8 tcChar);
		s8 CALLTYPE				oss_unicodeToAsciiCharacter					(w16 tuChar);
		u64 CALLTYPE			oss_scanForwardUntilCharacterChanges		(csu8p tcData, u64 tnMaxLength);
		u64 CALLTYPE			oss_scanForwardUntilCharacter				(csu8p tcData, s8 c);
		int CALLTYPE			oss_unicodeMemcmp							(w16* l, w16* r, u32 tnLength);
		int CALLTYPE			oss_unicodeMemicmp							(w16* l, w16* r, u32 tnLength);
		int CALLTYPE			oss_unicodeMemset							(w16* p, w16 c, u32 tnLength);
		w16 CALLTYPE			oss_upperCaseW								(w16 u);
		w16 CALLTYPE			oss_lowerCaseW								(w16 u);
		void CALLTYPE			oss_memset									(s8* dst, s8 c, u64 tnCount);
		void CALLTYPE			oss_memset4									(u32* dst, u32 val, u64 tnCount);
		void CALLTYPE			oss_memcpy									(s8* dst, s8* src, u64 tnCount);
		s32 CALLTYPE			oss_memcmp									(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
		s32 CALLTYPE			oss_memicmp									(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
		s32 CALLTYPE			oss_memicmpTwoLengths						(csu8p l/*eft*/, u64 tnLeftLength, csu8p r/*ight*/, u64 tnRightLength);
		s32 CALLTYPE			oss_memicmpDatum							(SDatum*  datum,  csu8p r/*ight*/, u64 tnRightLength);
		s32 CALLTYPE			oss_memicmpDatum2							(SDatum2* datum2, csu8p r/*ight*/, u64 tnRightLength);
		s32 CALLTYPE			oss_memicmpDatumDatum						(SDatum*  datumL,  SDatum*  datumR);
		s32 CALLTYPE			oss_memicmpDatum2Datum2						(SDatum2* datum2L, SDatum2* datum2R);
		void CALLTYPE			oss_deriveRGBA								(u32 tnColor, u8* tnRed, u8* tnGrn, u8* tnBlu, f32* tfAlp);
		u8 CALLTYPE				oss_getPredictableSequentialPattern			(u32 tnIterator, u32 tnValue);

		SLL* CALLTYPE			oss_ll_create								(SLL* nodePrev, SLL* nodeNext, u64 tnUniqueId, u32  tnSize);
		void CALLTYPE			oss_ll_delete								(SLL* node);
		void CALLTYPE			oss_ll_deleteWithCallback					(SLLCallback* cb);
		bool CALLTYPE			oss_ll_insert								(SLL* node, SLL* nodeRef, bool tlAfter);
		void CALLTYPE			oss_ll_orphanize							(SLL* node);
		void CALLTYPE			oss_ll_deleteChain							(SLL** root);
		void CALLTYPE			oss_ll_deleteChainWithCallback				(SLLCallback* cb);
		void CALLTYPE			oss_ll_iterateViaCallback					(SLLCallback* cb);
		void CALLTYPE			oss_ll_iterateBackwardViaCallback			(SLLCallback* cb);
		SLL* CALLTYPE			oss_ll_getFirstNode							(SLL* node);
		SLL* CALLTYPE			oss_ll_getLastNode							(SLL* node);

		SLL4* CALLTYPE			oss_ll4_create								(SLL4* nodeWest, SLL4* nodeEast, SLL4* nodeNorth, SLL4* nodeSouth, u64 tnUniqueId, u32 tnSize);
		SLL4* CALLTYPE			oss_ll4_createChain							(u32 tnSize, u32* tnCount, u32 tnDirection);
		void CALLTYPE			oss_ll4_delete								(SLL4* node);
		void CALLTYPE			oss_ll4_deleteWithCallback					(SLL4* node);
		bool CALLTYPE			oss_ll4_orphanize							(SLL4* node);
		bool CALLTYPE			oss_ll4_insertNorthSouth					(SLL4* node, SLL4* nodeRef, bool tlAfter);
		bool CALLTYPE			oss_ll4_insertWestEast						(SLL4* node, SLL4* nodeRef, bool tlAfter);
		void CALLTYPE			oss_ll4_deleteChain							(SLL4** root, u32 tnDirection);
		void CALLTYPE			oss_ll4_deleteChainWithCallback				(SLL4Callback* cb, u32 tnDirection);
		void CALLTYPE			oss_ll4_iterateViaCallback					(SLL4Callback* cb, u32 tnDirection);
		SLL4* CALLTYPE			oss_ll4_getLastNode							(SLL4* node, u32 tnDirection);
	
		bool CALLTYPE			oss_ll4bxml_orphanize						(SLL4* bxml);
		bool CALLTYPE			oss_ll4bxml_insert							(SLL4* bxmlSibling,	SLL4* bxmlRef,							bool tlAfter);
		bool CALLTYPE			oss_ll4bxml_insertAsChild					(SLL4* bxmlChild,	SLL4* bxmlParent,						bool tlPrepend);
		bool CALLTYPE			oss_ll4bxml_insertAsChildRegarding			(SLL4* bxmlChild,	SLL4* bxmlParent, SLL4* bxmlRegarding,	bool tlAfter);

		void* CALLTYPE			oss_SEChain_prepend							(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
		void* CALLTYPE			oss_SEChain_append							(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
		void* CALLTYPE			oss_SEChain_appendRelativeToMember			(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize,     u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);
		void* CALLTYPE			oss_SEChain_appendExistingRelativeToMember	(SStartEnd* ptrSE, SLL* ptrRef,                 u64 tnUniqueIdExtra, SLL* ptrCaller, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);

		void* CALLTYPE			oss_SEChain_migrateAll						(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc);
		SMasterList* CALLTYPE	oss_SEChain_migrateByPtr					(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, void* ptr,    u32 tnHint, u32 tnBlockSize);
		SMasterList* CALLTYPE	oss_SEChain_migrateByNum					(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);
		SLL* CALLTYPE			oss_SEChain_completelyMigrateSLLByPtr		(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr,     u32 tnHint, u32 tnBlockSize);
		SLL* CALLTYPE			oss_SEChain_completelyMigrateSLLByNum		(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);

		u32 CALLTYPE			oss_SEChain_countValids						(SStartEnd* ptrSE);
		u32 CALLTYPE			oss_SEChain_delete							(SStartEnd* ptrSE, u64 tnCallback, u64 tnParam, bool tlDeletePointers);
		void CALLTYPE			oss_SEChain_deleteAsPtrBlock				(SStartEnd* ptrSE);
		void CALLTYPE			oss_SEChain_deleteFrom						(SStartEnd* ptrSE, void* ptrDel, bool tlDeletePointers);
		bool CALLTYPE			oss_SEChain_deleteFromAfterCallback			(SStartEnd* ptrSE, bool tlDeletePointers, SStartEndCallback* cb);

		bool CALLTYPE			oss_SEChain_allocateAdditionalMasterSlots	(SStartEnd* ptrSE, u32 tnBlockSize);
		void* CALLTYPE			oss_SEChain_searchByUniqueId				(SStartEnd* ptrSE, u64 tnUniqueId);
		void* CALLTYPE			oss_SEChain_searchByCallback				(SStartEnd* ptrSE, SStartEndCallback* cb);
		void CALLTYPE			oss_SEChain_iterateThroughForCallback		(SStartEnd* ptrSE, SStartEndCallback* cb);
		void CALLTYPE			oss_SEChain_validate						(SStartEnd* ptrSE, SStartEndCallback* cb);

		u32 CALLTYPE			oss_swapEndian								(u32 tnValue);
		u32 CALLTYPE			oss_RGBA2BGRA								(u32 tnColor);
		void* CALLTYPE			oss_allocateAndNull							(u32 tnSize, bool tnInitToZeros);
		bool CALLTYPE			oss_isNeedleInHaystack						(csu8p tcHaystack, s32 tnHaystackLength, csu8p tcNeedle, s32 tnNeedleLength, bool tlCaseSensitive, u32* tnFoundPosition);
		bool CALLTYPE			oss_isNeedleInHaystack_Unicode				(w16* twHaystack, w16* twNeedle);
		u32 CALLTYPE			oss_countConsecutiveAsciiNumericDigits		(s8* buffer, u32 tnMaxLength);
		u32 CALLTYPE			oss_convertTextToU32						(s8* tcNumbers, u32 tnMaxLength);

		void CALLTYPE			oss_math_computeTriangle					(STriangleInOutF64* tri);
		void CALLTYPE			oss_math_computeSquare						(SSquareInOutF64* sq, f32 ox, f32 oy);
		void CALLTYPE			oss_math_computeLine						(SLineF64* line);
		void CALLTYPE			oss_math_squareRotateAbout					(SSquareInOutF64* sq);
		u32 CALLTYPE			oss_math_getGravityOfThetaAndLeft			(f64 tfTheta, bool tlLeft);
		s32 CALLTYPE			oss_math_getGravity07FromDecoratedGravity	(u32 tnGravityDecorated);
		f64 CALLTYPE			oss_math_getAreaOfSquareUsing_po_p1_p2		(s32 tnGravity07_po, s32 tnGravity07_p1, s32 tnGravity07_p2, SXYF64* po, SXYF64* p1, SXYF64* p2);
		void CALLTYPE			oss_math_getNextAxisInterceptXY				(SXYF64* p, f64 tfTheta);
		s32 CALLTYPE			oss_math_getGravityByRelativePosition		(SXYF64* p, SXYS32* po);
		s32 CALLTYPE			oss_math_getGravityInteger					(SXYS32* p, SXYS32* po);
		s32 CALLTYPE			oss_math_fineAdjustGravityByTheta			(SXYF64* po, SXYF64* p, SXYF64* pg, s32 lnGravity07p, s32 lnGravity07pg);
		f64 CALLTYPE			oss_math_adjustTheta						(f64 tfTheta);
		bool CALLTYPE			oss_math_withinDelta						(f64 tfValue1, f64 tfValue2, s32 tnDeltaDecimals);
		u64 CALLTYPE			oss_math_washFloans							(SCanvas* tc, SBGRA* bd, SBuilder** pointFloans, SBuilder** washFloans, SBuilder** drawFloans, bool tlIsFilledLeft);

		bool CALLTYPE			oss_polygon_initialize						(SPolygon* poly, u32 tnLineCount, bool tlAllocatePolyLines);
		bool CALLTYPE			oss_polygon_setByPolyLine					(SPolygon* poly, u32 tnEntry, SPolyLine* line);
		bool CALLTYPE			oss_polygon_setByValues						(SPolygon* poly, u32 tnEntry, SXYF64* start, SXYF64* end, SXYF64* gravity);
		bool CALLTYPE			oss_polygon_reset							(SPolygon* poly, bool tlResetFloans);
		bool CALLTYPE			oss_polygon_freeAndRelease					(SPolygon* poly, bool tlReleaseFloans);


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
// Build Buffer
// An accumulation template for appending data in a stream manner, or for allocating a specified
// size and then randomly updating it.
//
//////////
		void CALLTYPE			oss_builderCreateAndInitialize				(SBuilder** buffRoot, u32 tnAllocationSize);
		s8* CALLTYPE			oss_builderAppendData						(SBuilder*  buffRoot, s8* tcData, u32 tnDataLength);
		s8* CALLTYPE			oss_builderAllocateBytes					(SBuilder*	buffRoot, u32 tnDataLength);
		void CALLTYPE			oss_builderSetSize							(SBuilder*  buffRoot, u32 tnBufferLength);
		void CALLTYPE			oss_builderFreeAndRelease					(SBuilder** buffRoot);
		u32 CALLTYPE			oss_builderAsciiWriteOutFile				(SBuilder*  buffRoot, s8* tcFilename);


//////////
//
// SHA-1
// Computes SHA-1 values in various ways.  The Start/ProcessThisData/Finish sections are to
// be used when a computation must be conducted over multiple source calls.
//
//////
		void CALLTYPE			oss_sha1ComputeSha1							(s8* tcData, u32 tnDataLength, u8 shaOutput[20]);
		u64 CALLTYPE			oss_sha1ComputeSha1As64Bit					(s8* tcData, u32 tnDataLength);
		u32 CALLTYPE			oss_sha1ComputeSha1As32Bit					(s8* tcData, u32 tnDataLength);
		void CALLTYPE			oss_sha1ComputeSha1AsHex					(s8* tcData, u32 tnDataLength, s8* tcHexOutput, bool tlInsertSpaces);
		void CALLTYPE			oss_sha1ConvertHexToSha1					(u8 shaOutput[20], s8* tcHexInput, bool* tlError);
		void CALLTYPE			oss_sha1ConvertSha1ToHex					(s8* tcHexInput, u8 shaOutput[20], bool tlInsertSpaces);
		void CALLTYPE			oss_sha1ComputeSha1_Start					(u8 context[92]);
		void CALLTYPE			oss_sha1ComputeSha1_ProcessThisData			(u8 context[92], s8* tcData, u32 tnDataLength);
		void CALLTYPE			oss_sha1ComputeSha1_FinishAsSha1			(u8 context[92], u8 shaOutput[20], bool tlWipeData);
		void CALLTYPE			oss_sha1ComputeSha1_FinishAsHex				(u8 context[92], s8* tcHexOutput, bool tlInsertSpaces, bool tlWipeData);
		u64 CALLTYPE			oss_sha1Compute64BitFromSha1				(u8 sha20Bytes[20]);
		u32 CALLTYPE			oss_sha1Compute32BitFromSha1				(u8 sha20Bytes[20]);
		bool CALLTYPE			oss_sha1Compare								(u8 sha20Bytes1[20], u8 sha20Bytes2[20]);


//////////
//
// BXML
// The following functions relate the BXML engine as provided by the VVMOSS.
// It is created to provide an autonomous and robust way to access any BXML file
// as created by this engine.
//
//////////
		SBxml* CALLTYPE			oss_bxmlLoad								(s8* tcPathname, u32 tnPathnameLength, u64* tnBytesRead, u64* tnErrorOffset, u64* tnErrorCode);
		SBxml* CALLTYPE			oss_bxmlLoadFromBuffer						(s8* tcBxmlData, u32 tnBxmlDataLength,                   u64* tnErrorOffset, u64* tnErrorCode);
		bool CALLTYPE			oss_bxmlSave								(SBxml* bxml, s8* tcPathname, u32 tnPathnameLength, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnErrorNumber);
		void CALLTYPE			oss_bxmlSaveToBuffer						(SBxml* bxml, SBuilder** build, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnErrorNumber);

		SBxmla* CALLTYPE		oss_bxmlaCreate								(s8* tcNewName, u32 tnNewNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength);
		bool CALLTYPE			oss_bxmlaSetName							(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength);
		bool CALLTYPE			oss_bxmlaSetData							(SBxmla* bxmla, s8* tcData, u32 tnDataLength);
		bool CALLTYPE			oss_bxmlaSetTotalLength						(SBxmla* bxmla, u32 tnDataLengthTotal);
		SBxmla* CALLTYPE		oss_bxmlaDelete								(SBxmla* bxmla, bool tlFreeMemory);
		bool CALLTYPE			oss_bxmlaInsert								(SBxml* bxml, SBxmla* bxmlaRef, s8* tcName, u32 tnNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength, bool tlAfter);
		bool CALLTYPE			oss_bxmlaInsertExisting						(SBxml* bxml, SBxmla* bxmlaRef, SBxmla* bxmlaNew, bool tlAfter);
		SBxmla* CALLTYPE		oss_bxmlaCopy								(SBxmla* bxmla);
		SBxmla* CALLTYPE		oss_bxmlaCopyAs								(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength);
		u64 CALLTYPE			oss_bxmlaSha1One							(SBxmla* bxmla, u8 sha20Bytes[20]);
		u64 CALLTYPE			oss_bxmlaSha1								(SBxml* bxml, u8 sha20Bytes[20]);
		u64 CALLTYPE			oss_bxmlaSha1Tag							(SBxml* bxml, u8 sha20Bytes[20]);
		u64 CALLTYPE			oss_bxmlaSha1Data							(SBxml* bxml, u8 sha20Bytes[20]);

		u32 CALLTYPE			oss_bxmlaFindAndGetString					(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, SDatum* tsResult, bool* tlError);
		u32 CALLTYPE			oss_bxmlaFindAndGetU32						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		u64 CALLTYPE			oss_bxmlaFindAndGetU64						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		bool CALLTYPE			oss_bxmlaFindAndGetBool						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		f32 CALLTYPE			oss_bxmlaFindAndGetF32						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		f64 CALLTYPE			oss_bxmlaFindAndGetF64						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);

		u32 CALLTYPE			oss_bxmlaGetString							(SBxmla* bxmla, SDatum* tsResult, bool* tlError);
		u32 CALLTYPE			oss_bxmlaGetU32								(SBxmla* bxmla, bool* tlError);
		u64 CALLTYPE			oss_bxmlaGetU64								(SBxmla* bxmla, bool* tlError);
		bool CALLTYPE			oss_bxmlaGetBool							(SBxmla* bxmla, bool* tlError);
		f32 CALLTYPE			oss_bxmlaGetF32								(SBxmla* bxmla, bool* tlError);
		f64 CALLTYPE			oss_bxmlaGetF64								(SBxmla* bxmla, bool* tlError);

		// For 2-way navigation through the attributes (can be done manually, but these expressly do it
		SBxmla* CALLTYPE		oss_bxmlaGetNext							(SBxmla* bxmla);
		SBxmla* CALLTYPE		oss_bxmlaGetPrev							(SBxmla* bxmla);

		SBxml* CALLTYPE			oss_bxmlNodeCreate							(s8* tcNewName, u32 tnNewNameLength);
		bool CALLTYPE			oss_bxmlNodeSetName							(SBxml* bxml, s8* tcNewName, u32 tnNewNameLength);
		bool CALLTYPE			oss_bxmlNodeDelete							(SBxml* bxml, bool tlFreeMemory);
		bool CALLTYPE			oss_bxmlNodeInsert							(SBxml* bxml, SBxml* bxmlRef,                                     bool tlAfter);
		bool CALLTYPE			oss_bxmlNodeInsertAsChild					(SBxml* bxml, SBxml* bxmlParent,                                  bool tlAfter);
		bool CALLTYPE			oss_bxmlNodeInsertAsChildAfter				(SBxml* bxml, SBxml* bxmlParent, SBxml* bxmlRef,                  bool tlAfter);
		SBxml* CALLTYPE			oss_bxmlNodeCopy							(SBxml* bxml,                                        bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult);
		SBxml* CALLTYPE			oss_bxmlNodeCopyAs							(SBxml* bxml,    s8* tcNewName, u32 tnNewNameLength, bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult);
		u64 CALLTYPE			oss_bxmlNodeSha1							(SBxml* bxml, u8 sha20Bytes[20]);
		u64 CALLTYPE			oss_bxmlNodeSha1Tag							(SBxml* bxml, u8 sha20Bytes[20]);
		u64 CALLTYPE			oss_bxmlNodeSha1Data						(SBxml* bxml, u8 sha20Bytes[20]);

		// For 4-way navigation through the XML structure (can be done manually, but these expressly do it
		SBxml* CALLTYPE			oss_bxmlNodeGetNext							(SBxml* bxml);
		SBxml* CALLTYPE			oss_bxmlNodeGetPrev							(SBxml* bxml);
		SBxml* CALLTYPE			oss_bxmlNodeGetParent						(SBxml* bxml);
		SBxml* CALLTYPE			oss_bxmlNodeGetFirstChild					(SBxml* bxml);
		SBxmla* CALLTYPE		oss_bxmlNodeGetFirstAttribute				(SBxml* bxml);

		// Searches node or attribute names for the indicated wildcard search string
		SBxmla* CALLTYPE		oss_bxmlFindAttribute						(SBxml* bxml, SDatum* tsWildcardSearch, u32 tnInstance);
		bool CALLTYPE			oss_bxmlFindFirst							(SBxml* bxmlRoot, SBxml* bxmlNodeFound, SBxmla* bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, bool tlSearchAttributes, void** x);
		bool CALLTYPE			oss_bxmlFindContinue						(void* x);
		u32 CALLTYPE			oss_bxmlFindAllAsStartEndLists				(SBxml* bxmlRoot, SStartEnd** bxmlFinds, SStartEnd** bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren, bool tlSearchAttributes);
		// Searches populated data in attributes for the indicated wildcard search string
		bool CALLTYPE			oss_bxmlDataFindFirst						(SBxml* bxmlRoot, SBxmla* bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, void** x);
		bool CALLTYPE			oss_bxmlDataFindContinue					(void* x);
		u32 CALLTYPE			oss_bxmlDataFindAllAsStartEndList			(SBxml* bxmlRoot, SStartEnd** bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren);

		void CALLTYPE			oss_bxmlGetLastError						(SBxmlError* errorInfo);


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
	u64						ioss_getNextUniqueId							(void);
	u64						ioss_getNextN_UniqueIds							(u64* tnArrayBase, u32 tnCount);
	u64						ioss_loadDebuggerDll							(u32 tnUniqueId);
	u64						ioss_loadDebuggerByIniFile						(FILE* tfh, u32 tnUniqueId, s8* tcPathname);
	void					ioss_locateLineThenGetStartAndEnd				(s8* tcHaystack, u32 tnHaystackLength, s8* tcNeedle, u32 tnNeedleLength, u32* tnStart, u32* tnEnd);
	u32						ioss_searchHaystackForNeedle					(s8* tcHaystack, u32 tnHaystackLength, s8* tcNeedle, u32 tnNeedleLength);
	u32						ioss_searchHaystackForNeedleCase				(s8* tcHaystack, u32 tnHaystackLength, s8* tcNeedle, u32 tnNeedleLength);
	u64						ioss_validateDebuggerDll						(s8* tcDllPathname, u32 tnDllPathnameLength, u32 tnUniqueId);
	void					ioss_createVisibleWindow						(SOssWindow* tisw, _iswSOssWindowLL** tow);
	void					ioss_signalWindowFocus							(u64 tnOsHandle);
	void					ioss_lockSemaphore								(u64 semaphore);
	void					ioss_unlockSemaphore							(u64 semaphore);
	void					ioss_deleteVisibleWindow						(_iswSOssWindowLL* w);
	LRESULT CALLTYPE		ioss_wndProc_Message							(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	LRESULT CALLTYPE		ioss_wndProc_Visible							(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	void					ioss_checkWindowResize							(HWND hwnd, MINMAXINFO* tmmi);
	void					ioss_createBitmap								(HWND hwnd);
	u64						ioss_createDibWithBitBuffer						(HDC thDC, u32 tnWidth, u32 tnHeight, BITMAPINFO* tbi, s8** tbd, u32* tnActualWidth);
	void					ioss_initializeBackground						(u32 tnWidth, u32 tnHeight, u32 tnBackColor, s8* tbd, u32 tnActualWidth);
	u32						ioss_computeActualWidth							(u32 tnWidth);
	bool					ioss_paintWindow								(HWND hwnd);
	u64						ioss_canvasLine									(SCanvas* tc, SBGRA* bd, SXYF32* p1, SXYF32* p2, f32 lineThickness, SBGRA color);
	_iswSOssWindowLL*		ioss_findSOssWindowLLByHwnd						(HWND hwnd);
	bool					iioss_findSOssWindowLLByHwndCallback			(SStartEndCallback* cb);
	_iswSOssWindowLL*		ioss_findSOssWindowLLByScreenId					(u64 tnScreenId);
	bool					iioss_findSOssWindowLLByScreenId				(SStartEndCallback* cb);
	_iswSOssWindowLL*		ioss_find_iswSOssWindowLL_By_iOssWindowId		(u64 tnOssWindowId);
	bool					iioss_findSOssWindowByOssWindowIdCallback		(SStartEndCallback* cb);
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
	void					ioss_signalWindowClosedCallback					(_iswSOssWindowLL* w);
	u64						ioss_lowLevel_bitBlt_Sgra_onto_ossWindow		(_iswSOssWindowLL* tow, SBGRA* bd, u32 width, u32 height);
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
	u64						ioss_skipWhitespaces							(s8* tcData, u64 tnMaxLength);
	u64						ioss_skipWhitespacesAndCrLf						(s8* tcData, u64 tnMaxLength);
	u64						ioss_skipToCarriageReturnLineFeed				(s8* tcData, u64 tnMaxLength, u64* tnCRLF_Length);
	s32						ioss_translateSOssLinesToSOssCompsTest			(s8* tcHaystack, s8* tcNeedle, s32 tnLength);
	bool					iioss_translateSOssCompsToOthersCallback		(SStartEndCallback* cb);
inline bool					ioss_verifyLength								(u64 tnGoingTo, u64 tnMaxAllowable);
	bool					ioss_isAlpha									(s8 c);
	bool					ioss_isNumeric									(s8 c);
	bool					ioss_isAlphanumeric								(s8 c);
	u32						ioss_convertValidatedNumericStringToU32			(s8* tcData, u32 tnMaxLength);
	u64						ioss_convertValidatedNumericStringToU64			(s8* tcData, u32 tnMaxLength);
	void					ioss_bufferVerifySizeForNewBytes				(SBuilder* buffRoot, u32 tnDataLength);
	u64						iioss_canvasScale								(SCanvas* tsDst, SCanvas* tcSrc, SScaleMap** tsSm);
	u64						iioss_canvasScaleProcess						(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap*  tsSm, f64 tfVerticalScaler, f64 tfHorizontalScaler);
	void					iioss_getSpannedPixelComputation				(_isSSpannedPixelProcessing* bp);
	void					iioss_getSpannedPixelComputationAppend			(_isSSpannedPixelProcessing* bp, s32 tnDeltaX, s32 tnDeltaY, f64 tfAlpha);
	u32						ioss_getIntegersBetween							(f64 p1, f64 p2);
	void					ioss_setFindFileStatus							(SFindFile* tsFileInfo, WIN32_FIND_DATAA* twfd);
	void					ioss_convertFileTimeToSDateTime					(SFileTime* tsDateTime, FILETIME* tsFiletime);

	void					ioss_ll4_deleteChainAllNodes					(SLL4Callback* cb, SLL4* root);
	void					iioss_ll4_deleteChainAllNodes					(SStartEnd* nodeList, SLL4* root, u32 tnDirection);

	bool					iioss_bxmlFindFirst								(SBxml* bxmlRoot, SBxml** bxmlNodeFound, SBxmla** bxmlaAttributeFound, SDatum* tsWildcard, bool tlTraverseChildren, bool tlSearchAttributes, void** x);
	bool					iioss_bxmlFindContinue							(void* x);
	bool					iioss_bxmlDataFindFirst							(SBxml* bxmlRoot, SBxmla** bxmlaAttributeFound, SDatum* tsWildcard, bool tlTraverseChildren, void** x);
	bool					iioss_bxmlDataFindContinue						(void* x);
	SBxmla*					iioss_bxmlFindAttribute							(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance);

	SScreen*				ioss_createScreen								(u64 tnAssociatedId);
	SCanvas*				ioss_createCanvas								(u64 tnAssociatedId, u32 tnWidth, u32 tnHeight, SBGRA tnBackColor);
	SRegion*				ioss_createRegion								(u64 tnAssociatedId, SRegionState* tsState, u32 tnType, f32 ulx, f32 uly, f32 lrx, f32 lry, SCallbacks* callback, SStartEnd* events);
	void					ioss_regionRefreshCallback						(SStartEndCallback* cb);

	u64						ioss_drawText									(s8* tcText, u32 tnTextLength, s32 ulx, s32 uly, s32 lrx, s32 lry, SBGRA foreground, SBGRA background, u64 tnSystemFont, u64 tnSystemBitmap);

	// TODO:  to be added later: regions need to be able to trigger custom region events (see common.h's Custom event)
	bool					iioss_findCanvasCallback						(SStartEndCallback* cb);
	SRegion*				ioss_appendRegionToRegion						(SRegion* trParent, SRegion* trChild, u64 tnAssociatedId, SRegionState* tsState, u32 tnX, u32 tnY, SCallbacks* callback);
	u64						ioss_drawFixedPoint								(SCanvas* tc, SBGRA* bd, u32 fontWidth, u32 fontHeight, s32 ulx, s32 uly, s8* text, u32 characterCount, SBGRA foreground, SBGRA background);
	u64						ioss_bitBltAll									(SCanvas* tsDst, bool tlDstIsAccumulatorBuffer, s32 tnX, s32 tnY, SCanvas* tsSrc, bool tlSrcIsAccumulatorBuffer);
	void					iioss_bitBltAll_Opaque							(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 tnX, s32 tnY, SBGRA* trgbaSrcRoot, SCanvas* tsSrc);
	void					iioss_bitBltAll_Alpha							(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 tnX, s32 tnY, SBGRA* trgbaSrcRoot, SCanvas* tsSrc);
	u64						ioss_bitBltSection								(SCanvas* tsDst, bool tlDstIsAccumulatorBuffer, s32 dulx, s32 duly, SCanvas* tsSrc, bool tlSrcIsAccumulatorBuffer, s32 sulx, s32 suly, s32 slrx, s32 slry);
	void					iioss_bitBltSection_Opaque						(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 dulx, s32 duly, SBGRA* trgbaSrcRoot, SCanvas* tsSrc, s32 sulx, s32 suly, s32 slrx, s32 slry);
	void					iioss_bitBltSection_Alpha						(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 dulx, s32 duly, SBGRA* trgbaSrcRoot, SCanvas* tsSrc, s32 sulx, s32 suly, s32 slrx, s32 slry);
	u32						iioss_gradient									(SCanvas* tc, SBGRA* bd, SBGRA ul, SBGRA ur, SBGRA lr, SBGRA ll);
	void					iioss_createRegionAppendEventsCallback			(SStartEndCallback* cb);
	void					iioss_screenRefreshCallback						(SStartEndCallback* cb);

	u64						ioss_regionDefaultPaintEditbox					(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionEditboxData* editbox);
	u64						ioss_regionDefaultPaintButton					(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionButtonData* button);
	u64						ioss_regionDefaultPaintImage					(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionImageData* image);
	u64						ioss_regionDefaultPaintLabel					(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionLabelData* label);
	u64						ioss_regionDefaultPaintCheckbox					(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionCheckboxData* checkbox);
	u64						ioss_regionDefaultPaintRectangle				(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionRectangleData* rectangle);
	void					ioss_regionDoDefaultDebugTrapCallback			(SRegion* tr, u64 tnIdentifier, u64 tnExtra);

	void*					ioss_SEChain_appendOrPrepend					(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult);
	void*					ioss_SEChain_appendOrPrependExisting			(SStartEnd* ptrSE, SLL* ptrExisting, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult);
	void					ioss_SEChain_appendMasterList					(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded);
	void					ioss_SEChain_freeUpSlot							(SStartEnd* ptrSE, u32 tnSlot, u32 tnBlockSizeIfNewBlockNeeded);
	void					ioss_deleteFromSEChainMasterList				(SStartEnd* ptrSE, void* ptrDel);

	BOOL CALLBACK			iioss_enumerateMonitors							(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
	void					iioss_enumerateMonitorsIterateCallback			(SStartEndCallback* cb);

	void					ioss_deleteScaleCompute							(SScaleMap* tsm);
	void					iioss_math_computeTriangle						(STriangleF64* tri);
	void					iioss_math_computeSquare						(SSquareInOutF64* sq, f32 ox, f32 oy);
	void					iioss_math_computeLine							(SLineF64* line);
	s32						iioss_math_computeQuad							(SXYF64* p);
	void					iioss_copyLine									(SLineF64* line, SXYF64* p1, SXYF64* p2, bool tlComputeLine);
	void					ioss_math_squareRotateAbout						(SSquareInOutF64* sq);
	bool					iioss_polygon_initialize						(SPolygon* poly, u32 tnLineCount, bool tlAllocatePolyLines);
	bool					iioss_polygon_setByPolyLine						(SPolygon* poly, u32 tnEntry, SPolyLine* line);
	bool					iioss_polygon_setByValues						(SPolygon* poly, u32 tnEntry, SXYF64* start, SXYF64* end, SXYF64* gravity);
	u64						iioss_canvasPolygon								(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color);
	void					iioss_canvasPolygon_processSmall				(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_processNormal				(SCanvas* tsDst, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_draw						(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_computeLine					(SCanvas* tsDst, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_getCornerFloans				(_isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_getRangeFloans				(SCanvas* tsDst, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_drawPixelFloans				(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_drawRangeFloans				(                SBGRA* bd, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp);
	bool					iioss_canvasPolygon_determineIfSmall			(SPolygon* poly);
	int						iioss_canvasPolygon_qsortFloansCallback			(const void* l, const void* r);
	u32						iioss_canvasPolygon_getNextLineSegment			(u32 tnIndex, u32 tnMaxCount, SBGRACompute* sbgracRoot, SBGRACompute** p1, SBGRACompute** p2);
	void					iioss_canvasPolygon_storeCorner					(SBuilder* corners, SXYF64* po, SXYF64* pi, _isSStoreFloan_lineData* sfld);
	void					iioss_canvasPolygon_storeFloans					(_isSStoreFloan_lineData* sfld);
	void					iioss_canvasPolygon_storeFloansCorner			(_isSStoreFloan_lineData* sfld, _isSStoreFloan_cornerData* sfcd1, _isSStoreFloan_cornerData* sfcd2);
	u32						iioss_math_getGravityOfThetaAndLeft				(f64 tfTheta, bool tlLeft);
	s32						iioss_math_getGravity07FromDecoratedGravity		(u32 tnGravityDecorated);
	f64						iioss_math_getAreaOfSquareUsing_po_p1_p2		(s32 tnGravity07po, s32 tnGravity07_p1, s32 tnGravity07_p2, SXYF64* po, SXYF64* p1, SXYF64* p2);
	void					iioss_math_getNextAxisInterceptXY				(SXYF64* p, f64 tfTheta);
	s32						iioss_math_getGravityByRelativePosition			(SXYF64* p, SXYS32* po);
	s32						iioss_math_getGravityInteger					(SXYS32* p, SXYS32* po);
	s32						iioss_math_fineAdjustGravityByTheta				(SXYF64* po, SXYF64* p, SXYF64* pg, s32 lnGravity07p, s32 lnGravity07pg);
	f64						iioss_math_adjustTheta							(f64 tfTheta);
	bool					iioss_math_withinDelta							(f64 tfValue1, f64 tfValue2, s32 tnDeltaDecimals);
	void					iioss_math_multiplyBy							(SXYF64* p, f64 tfMultiplier);
	u64						iioss_canvasRotateAbout							(SCanvas* tsDst, SBGRA* bdd, s32 ulx, s32 uly, SCanvas* tsSrc, SBGRA* bds, f32 tfRadians, f32 ox, f32 oy);
	u64						iioss_canvasBezier3								(SCanvas* tc, SBGRA* bd, SBezier* bez);
	u64						iioss_canvasBezier4								(SCanvas* tc, SBGRA* bd, SBezier* bez);
	u64						iioss_canvasBezier5								(SCanvas* tc, SBGRA* bd, SBezier* bez);
	void					iioss_canvasBezier_wash							(SCanvas* tc, SBGRA* bd, SBuilder** pointFloans, SBuilder** washFloans, SBezier* bez);
	u64						iioss_canvasBezier_draw							(SCanvas* tc, SBGRA* bd, SBezier* bez);
	u64 					iioss_math_washFloans							(SCanvas* tc, SBGRA* bd, SBuilder** pointFloans, SBuilder** washFloans, SBuilder** drawFloans, bool tlIsFilledLeft);
	u64						iioss_math_washFloans_doDraw					(SCanvas* tc, SBGRA* bd, SBuilder** washFloans, SBuilder** drawFloans, bool tlIsFilledLeft);


//////////
// The following functions handle floan segments from point to point.
//      NW __N__ NE     2__3__4
//      W |     |E      1  8  5		// Note:  8 is only used when comparing integers, as they refer to entire pixels compared with other entire pixels, 8 means they are both of the same location
//      SW|__S__|SE     0__7__6
//////
	void					storeFloan_pointToPoint_bad						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_0_2						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_0_3						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_0_4						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_0_5						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_0_6						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_1_3						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_1_4						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_1_5						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_1_6						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_1_7						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_2_0						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_2_4						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_2_5						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_2_6						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_2_7						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_3_0						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_3_1						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_3_5						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_3_6						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_3_7						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_4_0						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_4_1						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_4_2						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_4_6						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_4_7						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_5_0						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_5_1						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_5_2						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_5_3						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_5_7						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_6_0						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_6_1						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_6_2						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_6_3						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_6_4						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_7_1						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_7_2						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_7_3						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_7_4						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_7_5						(_isSStoreFloan_lineData* sfld);


//////////
//
// Support for plugins
//
//////
	_isSInterfacePlugin*	ioss_plugin_register							(u64 DllInstance);
	u64						ioss_plugin_unregister							(u64 DllInstance);
	bool					ioss_plugin_registerCallback					(SStartEndCallback* cb);
