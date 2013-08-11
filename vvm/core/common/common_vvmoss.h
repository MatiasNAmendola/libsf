//////////
//
// /libsf/vvm/common/common_vvmoss.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//	   November 07, 2012
//////
// Change log:
//	   September 19, 2012 - Initial creation
//	   September 29, 2012 - PBL v1.0 license included directly in source files.
//	   November 07, 2012 - 0.60 development begins
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

	const s8		cgcOssGetSystemInfo[]									= "oss_getSystemInfo";
	const s8		cgcOssSleep[]											= "oss_sleep";
	const s8		cgcOssStoreDateTime[]									= "oss_storeDateTime";
	const s8		cgcOssChangePathnameExtension[]							= "oss_changePathnameExtension";
	const s8		cgcOssValidateFilenameCharacter[]						= "oss_validateFilenameCharacter";
	const s8		cgcOssGetNextUniqueId[]									= "oss_getNextUniqueId";
	const s8		cgcOssGetNextN_UniqueIds[]								= "oss_getNextN_UniqueIds";

	const s8		cgcOssDeleteScreen[]									= "oss_deleteScreen";
	const s8		cgcOssDeleteCanvas[]									= "oss_deleteCanvas";

	const s8		cgcOssRequestScreen[]									= "oss_requestScreen";
	const s8		cgcOssRequestCanvasForScreen[]							= "oss_requestCanvasForScreen";
	const s8		cgcOssRequestCanvasForCanvas[]							= "oss_requestCanvasForCanvas";
	const s8		cgcOssRequestCanvas[]									= "oss_requestCanvas";
	const s8		cgcOssRequestCanvasAndRegion[]							= "oss_requestCanvasAndRegion";
	const s8		cgcOssRequestRegion[]									= "oss_requestRegion";
	const s8		cgcOssRequestDuplicateRegion[]							= "oss_requestDuplicateRegion";
	const s8		cgcOssAssociateCanvasWithScreen[]						= "oss_associateCanvasWithScreen";
	const s8		cgcOssAssociateCanvasWithCanvas[]						= "oss_associateCanvasWithCanvas";
	const s8		cgcOssAssociateRegionWithCanvas[]						= "oss_associateRegionWithCanvas";
	const s8		cgcOssAssociateRegionWithRegion[]						= "oss_associateRegionWithRegion";
	const s8		cgcOssRequestFontHandle[]								= "oss_requestFontHandle";
	const s8		cgcOssCanvasWriteFixedPointText[]						= "oss_canvasDrawFixedPointText";
	const s8		cgcOssCanvasDrawText[]									= "oss_canvasDrawText";
	const s8		cgcOssCanvasDrawTextUnicode[]							= "oss_canvasDrawTextUnicode";
	const s8		cgcOssCanvasFrameRect[]									= "oss_canvasFrameRect";
	const s8		cgcOssCanvasFillRect[]									= "oss_canvasFillRect";
	const s8		cgcOssCanvasLine[]										= "oss_canvasLine";
	const s8		cgcOssCanvasArc[]										= "oss_canvasArc";
	const s8		cgcOssCanvasExtract[]									= "oss_canvasExtract";
	const s8		cgcOssCanvasColorize[]									= "oss_canvasColorize";
	const s8		cgcOssCanvasGrayscale[]									= "oss_canvasGrayscale";
	const s8		cgcOssCanvasGradient[]									= "oss_canvasGradient";
	const s8		cgcOssCanvasBitBlt[]									= "oss_canvasBitBlt";
	const s8		cgcOssCanvasRefresh[]									= "oss_canvasRefresh";
	const s8		cgcOssCanvasSetRegionAndEventCallback[]					= "oss_canvasSetRegionAndEventCallback";
	const s8		cgcOssCanvasGetRegionsList[]							= "oss_canvasGetRegionsList";
	const s8		cgcOssCanvasRemoveRegion[]								= "oss_canvasRemoveRegion";

	const s8		cgcOssScreenMouseSetEventCallback[]						= "oss_screenMouseSetEventCallback";
	const s8		cgcOssScreenMouseRemoveEventCallback[]					= "oss_screenMouseRemoveEventCallback";
	const s8		cgcOssScreenMouseGetEventCallbacksList[]				= "oss_screenMouseGetEventCallbacksList";
	const s8		cgcOssScreenKeyboardSetEventCallback[]					= "oss_screenKeyboardSetEventCallback";
	const s8		cgcOssScreenKeyboardRemoveEventCallback[]				= "oss_screenKeyboardRemoveEventCallback";
	const s8		cgcOssScreenKeyboardGetEventCallbacksList[]				= "oss_screenKeyboardGetEventCallbacksList";

	const s8		cgcOssCanvasScale[]										= "oss_canvasScale";
	const s8		cgcOssLoadBitmapFromDisk[]								= "oss_loadBitmapFromDisk";
	const s8		cgcOssSaveBitmapToDisk[]								= "oss_saveBitmapToDisk";
	const s8		cgcOssRequestSystemFont[]								= "oss_requestSystemFont";
	const s8		cgcOssRequestSystemBitmap[]								= "oss_requestSystemBitmap";
	const s8		cgcOssFindSystemFontByHandle[]							= "oss_findSystemFontByHandle";

	const s8		cgcOssAlloc[]											= "oss_alloc";
	const s8		cgcOssRealloc[]											= "oss_realloc";
	const s8		cgcOssFree[]											= "oss_free";

	#include "common_vvmoss_plugins.h"

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

	const s8		cgcOssDuplicateString[]									= "oss_duplicateString";
	const s8		cgcOssDuplicateUnicodeString[]							= "oss_duplicateUnicodeString";
	const s8		cgcOssDuplicateStringIntoDatum[]						= "oss_duplicateStringIntoDatum";
	const s8		cgcOssDuplicateStringIntoDatum2[]						= "oss_duplicateStringIntoDatum2";
	const s8		cgcOssDuplicateDatum[]									= "oss_duplicateDatum";
	const s8		cgcOssDuplicateDatum2[]									= "oss_duplicateDatum2";
	const s8		cgcOssDeleteDatum[]										= "oss_deleteDatum";
	const s8		cgcOssDeleteDatum2[]									= "oss_deleteDatum2";
	const s8		cgcOssAllocateNullStringIntoDatum2[]					= "oss_allocateNullStringIntoDatum2";
	const s8		cgcOssCopyUpToShortestString[]							= "oss_copyUpToShortestString";
	const s8		cgcOssWildcardMatch[]									= "oss_wildcardMatch";
	const s8		cgcOssAsciiToUnicode[]									= "oss_asciiToUnicode";
	const s8		cgcOssUnicodeToAscii[]									= "oss_unicodeToAscii";
	const s8		cgcOssAsciiToUnicodeChar[]								= "oss_asciiToUnicodeChar";
	const s8		cgcOssUnicodeToAsciiCharacter[]							= "oss_unicodeToAsciiCharacter";
	const s8		cgcOssScanForwardUntilCharacterChanges[]				= "oss_scanForwardUntilCharacterChanges";
	const s8		cgcOssScanForwardUntilCharacter[]						= "oss_scanForwardUntilCharacter";
	const s8		cgcOssUnicodeMemcmp[]									= "oss_unicodeMemcmp";
	const s8		cgcOssUnicodeMemicmp[]									= "oss_unicodeMemicmp";
	const s8		cgcOssUnicodeMemset[]									= "oss_unicodeMemset";
	const s8		cgcOssUpperCaseW[]										= "oss_upperCaseW";
	const s8		cgcOssLowerCaseW[]										= "oss_lowerCaseW";
	const s8		cgcOssMemset[]											= "oss_memset";
	const s8		cgcOssMemset4[]											= "oss_memset4";
	const s8		cgcOssMemcpy[]											= "oss_memcpy";
	const s8		cgcOssMemcmp[]											= "oss_memcmp";
	const s8		cgcOssMemicmp[]											= "oss_memicmp";
	const s8		cgcOssMemicmpTwoLengths[]								= "oss_memicmpTwoLengths";
	const s8		cgcOssMemicmpDatum[]									= "oss_memicmpDatum";
	const s8		cgcOssMemicmpDatum2[]									= "oss_memicmpDatum2";
	const s8		cgcOssMemicmpDatumDatum[]								= "oss_memicmpDatumDatum";
	const s8		cgcOssMemicmpDatum2Datum2[]								= "oss_memicmpDatum2Datum2";
	const s8		cgcOssDeriveRGBA[]										= "oss_deriveRGBA";
	const s8		cgcOssGetPredictableSequentialPattern[]					= "oss_getPredictableSequentialPattern";

	const s8		cgcOssLlCreate[]										= "oss_ll_create";
	const s8		cgcOssLlInsert[]										= "oss_ll_insert";
	const s8		cgcOssLlOrphanize[]										= "oss_ll_orphanize";
	const s8		cgcOssLlDeleteChainWithCallback[]						= "oss_ll_deleteChainWithCallback";
	const s8		cgcOssLlSha1Chain[]										= "oss_ll_iterateViaCallback";

	const s8		cgcOssLl4Create[]										= "oss_ll4_create";
	const s8		cgcOssLl4OrphanizeAsBxml[]								= "oss_ll4_orphanizeAsBxml";
	const s8		cgcOssLl4OrphanizeAsNode[]								= "oss_ll4_orphanizeAsNode";
	const s8		cgcOssLl4InsertAsBxml[]									= "oss_ll4_insertAsBxml";
	const s8		cgcOssLl4InsertAsBxmlAsChild[]							= "oss_ll4_insertAsBxmlAsChild";
	const s8		cgcOssLl4InsertAsBxmlAsChildRegarding[]					= "oss_ll4_insertAsBxmlAsChildRegarding";
	const s8		cgcOssLl4InsertAsNodeNorthSouth[]						= "oss_ll4_insertAsNodeNorthSouth";
	const s8		cgcOssLl4InsertAsNodeEastWest[]							= "oss_ll4_insertAsNodeEastWest";
	const s8		cgcOssLl4DeleteChainWithCallback[]						= "oss_ll4_deleteChainWithCallback";

	const s8		cgcOssSEChainPrepend[]									= "oss_SEChain_prepend";
	const s8		cgcOssSEChainAppend[]									= "oss_SEChain_append";
	const s8		cgcOssSEChainAppendRelativeToMember[]					= "oss_SEChain_appendRelativeToMember";
	const s8		cgcOssSEChainAppendExistingRelativeToMember[]			= "oss_SEChain_appendExistingRelativeToMember";

	const s8		cgcOssSEChainMigrateAll[]								= "oss_SEChain_migrateAll";
	const s8		cgcOssSEChainMigrateByPtr[]								= "oss_SEChain_migrateByPtr";
	const s8		cgcOssSEChainMigrateByNum[]								= "oss_SEChain_migrateByNum";
	const s8		cgcOssSEChainCompletelyMigrateSLLByPtr[]				= "oss_SEChain_completelyMigrateSLLByPtr";
	const s8		cgcOssSEChainCompletelyMigrateSLLByNum[]				= "oss_SEChain_completelyMigrateSLLByNum";

	const s8		cgcOssSEChainCountValids[]								= "oss_SEChain_countValids";
	const s8		cgcOssSEChainDelete[]									= "oss_SEChain_delete";
	const s8		cgcOssSEChainDeleteFrom[]								= "oss_SEChain_deleteFrom";
	const s8		cgcOssSEChainDeleteFromAfterCallback[]					= "oss_SEChain_deleteFromAfterCallback";

	const s8		cgcOssAllocateAdditionalStartEndMasterSlots[]			= "oss_allocateAdditionalStartEndMasterSlots";
	const s8		cgcOssSearchSEChainByUniqueId[]							= "oss_searchSEChainByUniqueId";
	const s8		cgcOssSearchSEChainByCallback[]							= "oss_searchSEChainByCallback";
	const s8		cgcOssIterateThroughStartEndForCallback[]				= "oss_iterateThroughStartEndForCallback";
	const s8		cgcOssValidateStartEnd[]								= "oss_validateStartEnd";
	const s8		cgcOssSwapEndian[]										= "oss_swapEndian";
	const s8		cgcOssRGA2BGRA[]										= "oss_RGBA2BGRA";
	const s8		cgcOssAllocateAndNull[]									= "oss_allocateAndNull";
	const s8		cgcOssIsNeedleInHaystack[]								= "oss_isNeedleInHaystack";
	const s8		cgcOssIsNeedleInHaystackUnicode[]						= "oss_isNeedleInHaystack_Unicode";
	const s8		cgcOssCountConsecutiveAsciiNumericDigits[]				= "oss_countConsecutiveAsciiNumericDigits";
	const s8		cgcOssConvertTextToU32[]								= "oss_convertTextToU32";

	const s8		cgcOssFindFirstFile[]									= "oss_fileFindFirst";
	const s8		cgcOssFindNextFile[]									= "oss_fileFindNext";
	const s8		cgcOssFindClose[]										= "oss_fileFindClose";

	const s8		cgcOssBuildBufferCreateAndInitialize[]					= "oss_buildBufferCreateAndInitialize";
	const s8		cgcOssBuildBufferAppendText[]							= "oss_buildBufferAppendText";
	const s8		cgcOssBuildBufferSetSize[]								= "oss_buildBufferSetSize";
	const s8		cgcOssBuildBufferFreeAndRelease[]						= "oss_buildBufferFreeAndRelease";

	const s8		cgcOssSha1ComputeSha1[]									= "oss_sha1ComputeSha1";
	const s8		cgcOssSha1ComputeSha1As64Bit[]							= "oss_sha1ComputeSha1As64Bit";
	const s8		cgcOssSha1ComputeSha1As32Bit[]							= "oss_sha1ComputeSha1As32Bit";
	const s8		cgcOssSha1ComputeSha1AsHex[]							= "oss_sha1ComputeSha1AsHex";
	const s8		cgcOssSha1ConvertHexToSha1[]							= "oss_sha1ConvertHexToSha1";
	const s8		cgcOssSha1ConvertSha1ToHex[]							= "oss_sha1ConvertSha1ToHex";
	const s8		cgcOssSha1ComputeSha1_Start[]							= "oss_sha1ComputeSha1_Start";
	const s8		cgcOssSha1ComputeSha1_ProcessThisData[]					= "oss_sha1ComputeSha1_ProcessThisData";
	const s8		cgcOssSha1ComputeSha1_FinishAsSha1[]					= "oss_sha1ComputeSha1_FinishAsSha1";
	const s8		cgcOssSha1ComputeSha1_FinishAsHex[]						= "oss_sha1ComputeSha1_FinishAsHex";
	const s8		cgcOssSha1Compute64BitFromSha1[]						= "oss_sha1Compute64BitFromSha1";
	const s8		cgcOssSha1Compute32BitFromSha1[]						= "oss_sha1Compute32BitFromSha1";
	const s8		cgcOssSha1Compare[]										= "oss_sha1Compare";

	const s8		cgcOssBxmlLoad[]										= "oss_bxmlLoad";
	const s8		cgcOssBxmlLoadFromBuffer[]								= "oss_bxmlLoadFromBuffer";
	const s8		cgcOssBxmlSave[]										= "oss_bxmlSave";
	const s8		cgcOssBxmlSaveToBuffer[]								= "oss_bxmlSaveToBuffer";

	const s8		cgcOssBxmlAttributeCreate[]								= "oss_bxmlaCreate";
	const s8		cgcOssBxmlAttributeSetName[]							= "oss_bxmlaSetName";
	const s8		cgcOssBxmlAttributeSetData[]							= "oss_bxmlaSetData";
	const s8		cgcOssBxmlAttributeSetTotalLength[]						= "oss_bxmlaSetTotalLength";
	const s8		cgcOssBxmlAttributeDelete[]								= "oss_bxmlaDelete";
	const s8		cgcOssBxmlAttributeInsert[]								= "oss_bxmlaInsert";
	const s8		cgcOssBxmlAttributeInsertExisting[]						= "oss_bxmlaInsertExisting";
	const s8		cgcOssBxmlAttributeCopy[]								= "oss_bxmlaCopy";
	const s8		cgcOssBxmlAttributeCopyAs[]								= "oss_bxmlaCopyAs";
	const s8		cgcOssBxmlAttributeSha1One[]							= "oss_bxmlaSha1One";
	const s8		cgcOssBxmlAttributeSha1[]								= "oss_bxmlaSha1";
	const s8		cgcOssBxmlAttributeSha1Tag[]							= "oss_bxmlaSha1Tag";
	const s8		cgcOssBxmlAttributeSha1Data[]							= "oss_bxmlaSha1Data";

	const s8		cgcOssBxmlAttributeGetNext[]							= "oss_bxmlaGetNext";
	const s8		cgcOssBxmlAttributeGetPrev[]							= "oss_bxmlaGetPrev";

	const s8		cgcOssBxmlNodeCreate[]									= "oss_bxmlNodeCreate";
	const s8		cgcOssBxmlNodeSetName[]									= "oss_bxmlNodeSetName";
	const s8		cgcOssBxmlNodeDelete[]									= "oss_bxmlNodeDelete";
	const s8		cgcOssBxmlNodeInsert[]									= "oss_bxmlNodeInsert";
	const s8		cgcOssBxmlNodeInsertAsChild[]							= "oss_bxmlNodeInsertAsChild";
	const s8		cgcOssBxmlNodeInsertAsChildAfter[]						= "oss_bxmlNodeInsertAsChildAfter";
	const s8		cgcOssBxmlNodeSha1[]									= "oss_bxmlNodeSha1";
	const s8		cgcOssBxmlNodeSha1Tag[]									= "oss_bxmlNodeSha1Tag";
	const s8		cgcOssBxmlNodeSha1Data[]								= "oss_bxmlNodeSha1Data";

	const s8		cgcOssBxmlNodeCopy[]									= "oss_bxmlNodeCopy";
	const s8		cgcOssBxmlNodeCopyAs[]									= "oss_bxmlNodeCopyAs";

	const s8		cgcOssBxmlGetNext[]										= "oss_bxmlNodeGetNext";
	const s8		cgcOssBxmlGetPrev[]										= "oss_bxmlNodeGetPrev";
	const s8		cgcOssBxmlGetParent[]									= "oss_bxmlNodeGetParent";
	const s8		cgcOssBxmlGetFirstChild[]								= "oss_bxmlNodeGetFirstChild";
	const s8		cgcOssBxmlGetFirstAttribute[]							= "oss_bxmlNodeGetFirstAttribute";

	const s8		cgcOssBxmlFindFirst[]									= "oss_bxmlFindFirst";
	const s8		cgcOssBxmlFindContinue[]								= "oss_bxmlFindContinue";
	const s8		cgcOssBxmlFindAllAsStartEndLists[]						= "oss_bxmlFindAllAsStartEndLists";

	const s8		cgcOssBxmlDatFindFirst[]								= "oss_bxmlDataFindFirst";
	const s8		cgcOssBxmlDataFindContinue[]							= "oss_bxmlDataFindContinue";
	const s8		cgcOssBxmlDataFindAllAsStartEndList[]					= "oss_bxmlDataFindAllAsStartEndList";

	const s8		cgcOssBxmlGetLastError[]								= "oss_bxmlGetLastError";

	const s8		cgcOssThreadCreate[]									= "oss_threadCreate";
	const s8		cgcOssThreadSuspend[]									= "oss_threadSuspend";
	const s8		cgcOssThreadResume[]									= "oss_threadResume";
	const s8		cgcOssThreadTerminate[]									= "oss_threadTerminate";

	const s8		cgcOssCreateScreenTemplate[]							= "oss_createScreenTemplate";

	const s8		cgcOssGetScreenDimensions[]								= "oss_getScreenDimensions";
	const s8		cgcOssSetFocus[]										= "oss_setFocus";

	const s8		cgcOssBitBlt[]											= "oss_bitBlt";
	const s8		cgcOssBitBltSystemBitmapToSRGBA[]						= "oss_bitBltSystemBitmapToSRGBA";

	const s8		cgcOssDrawText[]										= "oss_drawText";

	const s8		cgcOssGetNextMessage[]									= "oss_getNextMessage";
	const s8		cgcOssMessageBox[]										= "oss_messageBox";
	const s8		cgcOssMessageBoxUnicode[]								= "oss_messageBoxUnicode";

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
	u64				(CALLTYPE *oss_firstCallback)							(u64 tnDebuggerInterfaceAddress);
	void			(CALLTYPE *oss_bootstrapInitialization)					(u64 tnDebuggerInterfaceAddress);
	void			(CALLTYPE *oss_initialization)							(u64 tnDebuggerInterfaceAddress);
	const s8*		(CALLTYPE *oss_getVersion)								(void);
	bool			(CALLTYPE *oss_createMessageWindow)						(void);
	u64				(CALLTYPE *oss_createVisibleWindow)						(u64 tisw, u64 tnScreenId);


//////////
//
// Basic system functions
//
//////
		void			(CALLTYPE *oss_getSystemInfo)							(SSysInfo* tsi);
		void			(CALLTYPE *oss_sleep)									(u32 tnMilliseconds);
		void			(CALLTYPE *oss_storeDateTime)							(SDateTime* tdt);
		s8*				(CALLTYPE *oss_changePathnameExtension)					(s8* tcPathname, s8* tcNewPathname);
		bool			(CALLTYPE *oss_validateFilenameCharacter)				(s8* tcPathname, u64 tnPathnameLength, u64* tnErrorPosition);
		u64				(CALLTYPE *oss_getNextUniqueId)							(void);
		u64				(CALLTYPE *oss_getNextN_UniqueIds)						(u64* tnArrayBase, u32 tnCount);


//////////
//
// Window and canvas related functions
// All canvases are 32-bit with an alpha layer.
// All windows use 24-bit presentations.
//
//////
		// Clean house
		u64				(CALLTYPE *oss_deleteScreen)							(u64 id, SScreen* ts);
		u64				(CALLTYPE *oss_deleteCanvas)							(u64 id, SCanvas* tc);

		// Visible window information
		SScreen*		(CALLTYPE *oss_requestScreen)							(u64 tnAssociatedId, u64 tisw);
		SCanvas*		(CALLTYPE *oss_requestCanvasForScreen)					(SScreen* ts);
		SCanvas*		(CALLTYPE *oss_requestCanvasForCanvas)					(SCanvas* tc);
		SCanvas*		(CALLTYPE *oss_requestCanvas)							(u64 tnAssociatedId, u32 tnWidth, u32 tnHeight, u32 tnBackColor, bool tlIsActive, bool tlUseTransparency);
		SRegion*		(CALLTYPE *oss_requestRegion)							(u64 tnAssociatedId, SRegionState* tsState, u32 tnType, u32 tnWidth, u32 tnHeight, SCallbacks* callback, SStartEnd* events);
		SRegion*		(CALLTYPE *oss_requestDuplicateRegion)					(u64 tnAssociatedId, SRegion* templateRegion);
		bool			(CALLTYPE *oss_requestCanvasAndRegion)					(u64 tnAssociatedId, u32 tnWidth, u32 tnHeight, u32 tnBackColor, bool tlIsActive, bool tlUseTransparency, SCanvas** tc, SRegion** tr, SCallbacks* callbacks, SStartEnd* events);
		SCanvasList* 	(CALLTYPE *oss_associateCanvasWithScreen)				(SScreen* ts, SCanvas* tc, bool tlMakeActive);
		SCanvasList* 	(CALLTYPE *oss_associateCanvasWithCanvas)				(SCanvas* tcParent, SCanvas* tcChild);
		SRegionList*	(CALLTYPE *oss_associateRegionWithCanvas)				(SCanvas* tc, SRegion* tr);
		SRegionList*	(CALLTYPE *oss_associateRegionWithRegion)				(SRegion* tcParent, SRegion* trChild);
		u64				(CALLTYPE *oss_requestFontHandle)						(s8* fontName, u32 fontWidth, bool bold, bool italics, bool underline, bool strikethrough);
		u64				(CALLTYPE *oss_canvasDrawFixedPointText)				(SCanvas* tc, SRGBA* bd, u32 fontWidth, u32 fontHeight, u32 ulx, u32 uly,    s8*  text, u32 characterCount, u32 foreground, u32 background);
		u64				(CALLTYPE *oss_canvasDrawText)							(SCanvas* tc, SRGBA* bd, u64 fontHandle, s32 ulx, s32 uly, s32 lrx, s32 lry, s8*  tcText, u32 tnTextLength, u32 foreground, u32 background, SDrawState* tsDrawState);
		u64				(CALLTYPE *oss_canvasDrawTextUnicode)					(SCanvas* tc, SRGBA* bd, u64 fontHandle, s32 ulx, s32 uly, s32 lrx, s32 lry, w16* tuText, u32 tnTextLength, u32 foreground, u32 background, SDrawState* tsDrawState);
		u64				(CALLTYPE *oss_canvasFrameRect)							(SCanvas* tc, SRGBA* bd, u32 ulx, u32 uly, u32 lrx, u32 lry, u32 borderThickness, u32 border);
		u64				(CALLTYPE *oss_canvasFillRect)							(SCanvas* tc, SRGBA* bd, u32 ulx, u32 uly, u32 lrx, u32 lry, u32 borderThickness, u32 border, u32 background);
		u64				(CALLTYPE *oss_canvasLine)								(SCanvas* tc, SRGBA* bd, u32 ulx, u32 uly, u32 lrx, u32 lry, u32 lineThickness, u32 line);
		u64				(CALLTYPE *oss_canvasArc)								(SCanvas* tc, SRGBA* bd, u32 ox, u32 oy, f32 start, f32 end, u32 lineThickness, u32 line);
		SCanvas*		(CALLTYPE *oss_canvasExtract)							(SCanvas* tc, SRGBA* bd, u32 ulx, u32 uly, u32 lrx, u32 lry);
		u64				(CALLTYPE *oss_canvasColorize)							(SCanvas* tc, SRGBA* bd, u32 ulx, u32 uly, u32 lrx, u32 lry, u32 color);
		u64				(CALLTYPE *oss_canvasGrayscale)							(SCanvas* tc, SRGBA* bd, u32 ulx, u32 uly, u32 lrx, u32 lry);
		u64				(CALLTYPE *oss_canvasGradient)							(SCanvas* tc, SRGBA* bd, SRGBA ul, SRGBA ur, SRGBA lr, SRGBA ll);
		u64				(CALLTYPE *oss_canvasBitBlt)							(SCanvas* tc, SCanvas* tcDst, bool tlDstAccumulator, u32 dulx, u32 duly, u32 dlrx, u32 dlry, SCanvas* tsSrc, bool tlSrcAccumulator, u32 sulx, u32 suly, u32 slrx, u32 slry);
		u64				(CALLTYPE *oss_canvasScale)								(SCanvas* tcDst, SCanvas* tcSrc);
		u64				(CALLTYPE *oss_canvasRefresh)							(SCanvas* tc);
		u64				(CALLTYPE *oss_canvasSetRegionAndEventCallback)			(SCanvas* tc, SRegion*  region,  SEvent*  event);
		void			(CALLTYPE *oss_canvasGetRegionsList)					(SCanvas* tc, SRegion** regions, SEvent** events, u32* count);
		u64				(CALLTYPE *oss_canvasRemoveRegion)						(SCanvas* tc, SRegion* region);

		u64				(CALLTYPE *oss_screenMouseSetEventCallback)				(u64 id, SCanvas* tc, SEvent* event);
		u64				(CALLTYPE *oss_screenMouseRemoveEventCallback)			(u64 id, SCanvas* tc, SEvent* event);
		void			(CALLTYPE *oss_screenMouseGetEventCallbacksList)		(u64 id, SCanvas* tc, SEvent** events, u32* count);
		u64				(CALLTYPE *oss_screenKeyboardSetEventCallback)			(u64 id, SCanvas* tc, SEvent* event);
		u64				(CALLTYPE *oss_screenKeyboardRemoveEventCallback)		(u64 id, SCanvas* tc, SEvent* event);
		void			(CALLTYPE *oss_screenKeyboardGetEventCallbacksList)		(u64 id, SCanvas* tc, SEvent** events, u32* count);

		// Only 24-bit or 32-bit bitmaps can be loaded from disk at present.
		u64				(CALLTYPE *oss_loadBitmapFromDisk)						(s8* tcPathname, SCanvas** tc, u32* tnWidth, u32* tnHeight, u32 tnBackColor);
		u64				(CALLTYPE *oss_saveBitmapToDisk)						(SCanvas* tc, SRGBA* bd, s8* tcPathname);
		u64				(CALLTYPE *oss_requestSystemFont)						(s8* fontName, u32 fontPointSize, bool bold, bool italics, bool underline, bool strikethrough);
		u64				(CALLTYPE *oss_requestSystemBitmap)						(u32 tnWidth, u32 tnHeight);
		u64				(CALLTYPE *oss_findSystemFontByHandle)					(u64 tnFontHandle);

		u64				(CALLTYPE *oss_createScreenTemplate)					(u64 id, u64 uniqueScreenId,
																					s8* tcCaption, u32 tnCaptionLength,
																					u32 tnX, u32 tnY,
																					u32 tnWidth, u32 tnHeight,
																					u32 tnWidthMin, u32 tnHeightMin,
																					u32 tnWidthMax, u32 tnHeightMax,
																					u32 ncUlx, u32 ncUly, u32 ncLrx, u32 ncLry, u32 ncBorder,
																					u32 tnForeColor, u32 tnBackColor,
																					bool tlResizable, bool tlMovable, bool tlClosable, bool tlVisible, bool tlBorder,
																					SCallbacks* callbacks);

		bool			(CALLTYPE *oss_getScreenDimensions)						(u64 tnOssWindowId, u32* tnX, u32* tnY, u32* tnWidth, u32* tnHeight, u32* tnWidthMax, u32* tnHeightMax, u32* tnWidthMin, u32* tnHeightMin);
		bool			(CALLTYPE *oss_setFocus)								(u64 tnScreenId);
		u64				(CALLTYPE *oss_bitBlt)									(u64 tnOssWindowId, SRGBA* buffer, u32 width, u32 height);
		u64				(CALLTYPE *oss_bitBltSystemBitmapToSRGBA)				(u64 bdoss, s32 tnX, s32 tnY, u32 tnWidth, u32 tnHeight, SCanvas* tc, SRGBA* bdRoot);
		u64				(CALLTYPE *oss_drawText)								(s8* tcText, u32 tnTextLength, s32 ulx, s32 uly, s32 lrx, s32 lry, u32 foreground, u32 background, SDrawState* tsDrawState, u64 tnSystemFont, u64 tnSystemBitmap);
		u64				(CALLTYPE *oss_getNextMessage)							(u32* message, void* extra);
		u64				(CALLTYPE *oss_messageBox)								(u64 id, s8* tcText, s8* tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);
		u64				(CALLTYPE *oss_messageBoxUnicode)						(u64 id, w16* tcText, w16* tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);


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
		SOssComp*		(CALLTYPE* oss_translateSOssLinesToSOssComps)		(SAsciiCompSearcher* tsComps, SOssLine* line);
		void			(CALLTYPE* oss_translateSOssCompsToOthers)			(SAsciiCompSearcher* tsComps, SOssLine* line);
		u64				(CALLTYPE* oss_writeSOssLineSequenceToDisk)			(s8* tcPathname, SStartEnd* tseLines);
		u64				(CALLTYPE* oss_writeSOssLineSequenceCompsToDisk)	(s8* tcPathname, SStartEnd* tseLines);
		u64				(CALLTYPE* oss_writeSOssLineSequenceCompsDebuggingToDisk)(s8* tcPathname, SStartEnd* tseLines);
		SOssComp*		(CALLTYPE* oss_findNextSOssCompBy_iCode)			(SOssComp* comp, u32 tniCode, SOssComp** compLastScanned);
		SOssComp*		(CALLTYPE* oss_skipPastSOssComp_iCode)				(SOssComp* comp, u32 tniCode);
		u32				(CALLTYPE* oss_combine2SOssComps)					(SOssLine* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2,                     u32 tniCodeCombined);
		u32				(CALLTYPE* oss_combine3SOssComps)					(SOssLine* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeNeedle3, u32 tniCodeCombined);
		u32				(CALLTYPE* oss_combineAllBetweenSOssComps)			(SOssLine* line, u32 tniCodeNeedle,                                          u32 tniCodeCombined);
		u32				(CALLTYPE* oss_combineAllAfterSOssComp)				(SOssLine* line, u32 tniCodeNeedle);
		u32				(CALLTYPE* oss_removeExtraneousWhitespaceSOssComps)	(SOssLine* line, u32 tniCodeWhitespace);
		bool			(CALLTYPE* oss_findFirstOccurrenceOfAsciiCharacter)	(s8* tcHaystack, u64 tnHaystackLength, s8 tcNeedle, u64* tnPosition);


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
		bool			(CALLBACK *oss_sharedAsciiDeleteFile)				(s8* tcFullPathname);
		bool			(CALLTYPE *oss_sharedAsciiWriteOutFile)				(s8* tcFullPathname, s8* tcData, u32 tnDataLength);


//////////
//
// Common functions
//
//////
		// Prototype definitions
		u8*				(CALLBACK *oss_duplicateString)						(u8* ptr, u64 length);
		w16*			(CALLBACK *oss_duplicateUnicodeString)				(w16* tuText);
		void			(CALLBACK *oss_duplicateStringIntoDatum)			(SDatum*  datum,  u8* ptr, u64 length,                  bool tlFreeExisting);
		void			(CALLBACK *oss_duplicateStringIntoDatum2)			(SDatum2* datum2, u8* ptr, u64 length, u64 totalLength, bool tlFreeExisting);
		void			(CALLBACK *oss_duplicateDatum)						(SDatum*  datumDst,  SDatum*  datumSrc);
		void			(CALLBACK *oss_duplicateDatum2)						(SDatum2* datum2Dst, SDatum2* datum2Src);
		void			(CALLBACK *oss_deleteDatum)							(SDatum*  datum);
		void			(CALLBACK *oss_deleteDatum2)						(SDatum2* datum2);
		void			(CALLBACK *oss_allocateNullStringIntoDatum2)		(SDatum2* datum2, u64 length, bool tlInitialize);
		void			(CALLBACK *oss_copyUpToShortestString)				(u8* dst, u32 tnDstLength, u8* src, u32 tnSrcLength);
		s32				(CALLBACK *oss_wildcardMatch)						(csu8p candidate, csu8p wildcardPattern, bool tlCaseSensitive);
		w16*			(CALLBACK *oss_asciiToUnicode)						(u8* tcText, u32 tnTextLength);
		s8*				(CALLBACK *oss_unicodeToAscii)						(w16* tuText, u32 tnTextLength);
		w16				(CALLBACK *oss_asciiToUnicodeChar)					(u8 tcChar);
		s8				(CALLBACK *oss_unicodeToAsciiCharacter)				(w16 tuChar);
		u64				(CALLBACK *oss_scanForwardUntilCharacterChanges)	(csu8p tcData, u64 tnMaxLength);
		u64				(CALLBACK *oss_scanForwardUntilCharacter)			(csu8p tcData, s8 c);
		int				(CALLBACK *oss_unicodeMemcmp)						(w16* l, w16* r, u32 tnLength);
		int				(CALLBACK *oss_unicodeMemicmp)						(w16* l, w16* r, u32 tnLength);
		int				(CALLBACK *oss_unicodeMemset)						(w16* p, w16 c, u32 tnLength);
		w16				(CALLBACK *oss_upperCaseW)							(w16 u);
		w16				(CALLBACK *oss_lowerCaseW)							(w16 u);
		void			(CALLBACK *oss_memset)								(s8* dst, s8 c, u64 tnCount);
		void			(CALLBACK *oss_memset4)								(u32* dst, u32 val, u64 tnCount);
		void			(CALLBACK *oss_memcpy)								(s8* dst, s8* src, u64 tnCount);
		s32				(CALLBACK *oss_memcmp)								(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
		s32				(CALLBACK *oss_memicmp)								(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
		s32				(CALLBACK *oss_memicmpTwoLengths)					(csu8p l/*eft*/, u64 tnLeftLength, csu8p r/*ight*/, u64 tnRightLength);
		s32				(CALLBACK *oss_memicmpDatum)						(SDatum*  datum,  csu8p r/*ight*/, u64 tnRightLength);
		s32				(CALLBACK *oss_memicmpDatum2)						(SDatum2* datum2, csu8p r/*ight*/, u64 tnRightLength);
		s32				(CALLBACK *oss_memicmpDatumDatum)					(SDatum*  datumL,  SDatum*  datumR);
		s32				(CALLBACK *oss_memicmpDatum2Datum2)					(SDatum2* datum2L, SDatum2* datum2R);
		void			(CALLBACK *oss_deriveRGBA)							(u32 tnColor, u8* tnRed, u8* tnGrn, u8* tnBlu, f32* tfAlp);
		u8				(CALLTYPE *oss_getPredictableSequentialPattern)		(u32 tnIterator, u32 tnValue);

		SLL*			(CALLBACK *oss_ll_create)							(SLL* nodePrev, SLL* nodeNext, u64 tnUniqueId, u32  tnSize);
		bool			(CALLBACK *oss_ll_insert)							(SLL* node, SLL* nodeRef, bool tlAfter);
		void			(CALLBACK *oss_ll_orphanize)						(SLL* node);
		void			(CALLBACK *oss_ll_deleteChainWithCallback)			(SLL* node, u64 func, u64 tnExtra);
		void			(CALLTYPE *oss_ll_iterateViaCallback)				(SLL* node, SOssCbData2Void* cb);

		SLL4*			(CALLTYPE *oss_ll4_create)							(SLL4* nodeWest, SLL4* nodeEast, SLL4* nodeNorth, SLL4* nodeSouth, u64 tnUniqueId, u32 tnSize);
		bool			(CALLBACK *oss_ll4_orphanizeAsBxml)					(SLL4* bxml);
		bool			(CALLBACK *oss_ll4_orphanizeAsNode)					(SLL4* node);
		bool			(CALLBACK *oss_ll4_insertAsBxml)					(SLL4* bxml, SLL4* bxmlRef,                   bool tlAfter);
		bool			(CALLBACK *oss_ll4_insertAsBxmlAsChild)				(SLL4* bxml, SLL4* bxmlParent,                bool tlPrepend);
		bool			(CALLBACK *oss_ll4_insertAsBxmlAsChildRegarding)	(SLL4* bxml, SLL4* bxmlParent, SLL4* bxmlRef, bool tlAfter);
		bool			(CALLBACK *oss_ll4_insertAsNodeNorthSouth)			(SLL4* node, SLL4* nodeRef,                   bool tlAfter);
		bool			(CALLBACK *oss_ll4_insertAsNodeEastWest)			(SLL4* node, SLL4* nodeRef,                   bool tlAfter);
		void			(CALLTYPE *oss_ll4_deleteChainWithCallback)			(SLL4Callback* cb);

		void*			(CALLBACK *oss_SEChain_prepend)						(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
		void*			(CALLBACK *oss_SEChain_append)						(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
		void*			(CALLBACK *oss_SEChain_appendRelativeToMember)		(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize,     u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);
		void*			(CALLBACK *oss_SEChain_appendExistingRelativeToMember)(SStartEnd* ptrSE, SLL* ptrRef,                 u64 tnUniqueIdExtra, SLL* ptrCaller, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);

		void*			(CALLBACK *oss_SEChain_migrateAll)					(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc);
		SMasterList*	(CALLBACK *oss_SEChain_migrateByPtr)				(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, void* ptr,    u32 tnHint, u32 tnBlockSize);
		SMasterList*	(CALLBACK *oss_SEChain_migrateByNum)				(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);
		SLL*			(CALLBACK *oss_SEChain_completelyMigrateSLLByPtr)	(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr,     u32 tnHint, u32 tnBlockSize);
		SLL*			(CALLBACK *oss_SEChain_completelyMigrateSLLByNum)	(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);

		u32				(CALLBACK *oss_SEChain_countValids)					(SStartEnd* ptrSE);
		u32				(CALLBACK *oss_SEChain_delete)						(SStartEnd* ptrSE, u64 tnCallback, u64 tnParam, bool tlDeletePointers);
		void			(CALLBACK *oss_SEChain_deleteFrom)					(SStartEnd* ptrSE, void* ptrDel, bool tlDeletePointers);
		bool			(CALLTYPE *oss_SEChain_deleteFromAfterCallback)		(SStartEnd* ptrSE, bool tlDeletePointers, SStartEndCallback* cb);

		bool			(CALLBACK *oss_allocateAdditionalStartEndMasterSlots)(SStartEnd* ptrSE, u32 tnBlockSize);
		void*			(CALLBACK *oss_searchSEChainByUniqueId)				(SStartEnd* ptrSE, u64 tnUniqueId);
		void*			(CALLTYPE *oss_searchSEChainByCallback)				(SStartEnd* ptrSE, SStartEndCallback* cb);
		void			(CALLTYPE *oss_iterateThroughStartEndForCallback)	(SStartEnd* ptrSE, SStartEndCallback* cb);
		void			(CALLTYPE *oss_validateStartEnd)					(SStartEnd* ptrSE, SStartEndCallback* cb);
		u32				(CALLBACK *oss_swapEndian)							(u32 tnValue);
		u32				(CALLBACK *oss_RGBA2BGRA)							(u32 tnColor);
		void*			(CALLBACK *oss_allocateAndNull)						(u32 tnSize, bool tnInitToZeros);
		bool			(CALLBACK *oss_isNeedleInHaystack)					(csu8p tcHaystack, s32 tnHaystackLength, csu8p tcNeedle, s32 tnNeedleLength, bool tlCaseSensitive, u32* tnFoundPosition);
		bool			(CALLBACK *oss_isNeedleInHaystack_Unicode)			(w16* twHaystack, w16* twNeedle);
		u32				(CALLBACK *oss_countConsecutiveAsciiNumericDigits)	(s8* buffer, u32 tnMaxLength);
		u32				(CALLBACK *oss_convertTextToU32)					(s8* tcNumbers, u32 tnMaxLength);


//////////
//
// Find files
//
//////////
		u64				(CALLBACK *oss_fileFindFirst)						(csu8p tcPathname, csu8p tcFilenameTemplate, SFindFile* tsFileInfo);
		bool			(CALLBACK *oss_fileFindNext)						(u64 tnHandle, SFindFile* tsFileInfo);
		void			(CALLBACK *oss_fileFindClose)						(u64 tnHandle);


//////////
//
// Build Buffer
// An accumulation template for appending data in a stream manner, or for allocating a specified
// size and then randomly updating it.
//
//////////
		void			(CALLTYPE *oss_buildBufferCreateAndInitialize)		(SBuffer** buffRoot, u32 tnAllocationSize);
		s8*				(CALLTYPE *oss_buildBufferAppendText)				(SBuffer*  buffRoot, s8* tcData, u32 tnDataLength);
		void			(CALLTYPE *oss_buildBufferSetSize)					(SBuffer** buffRoot, u32 tnBufferLength);
		void			(CALLTYPE *oss_buildBufferFreeAndRelease)			(SBuffer** buffRoot);


//////////
//
// SHA-1
// Computes SHA-1 values in various ways.  The Start/ProcessThisData/Finish sections are to
// be used when a computation must be conducted over multiple source calls.
//
//////
		void			(CALLTYPE *oss_sha1ComputeSha1)						(s8* tcData, u32 tnDataLength, u8 shaOutput[20]);
		u64				(CALLTYPE *oss_sha1ComputeSha1As64Bit)				(s8* tcData, u32 tnDataLength);
		u32				(CALLTYPE *oss_sha1ComputeSha1As32Bit)				(s8* tcData, u32 tnDataLength);
		void			(CALLTYPE *oss_sha1ComputeSha1AsHex)				(s8* tcData, u32 tnDataLength, s8* tcHexOutput, bool tlInsertSpaces);
		void			(CALLTYPE *oss_sha1ConvertHexToSha1)				(u8 shaOutput[20], s8* tcHexInput, bool* tlError);
		void			(CALLTYPE *oss_sha1ConvertSha1ToHex)				(s8* tcHexInput, u8 shaOutput[20], bool tlInsertSpaces);
		void			(CALLTYPE *oss_sha1ComputeSha1_Start)				(u8 context[92]);
		void			(CALLTYPE *oss_sha1ComputeSha1_ProcessThisData)		(u8 context[92], s8* tcData, u32 tnDataLength);
		void			(CALLTYPE *oss_sha1ComputeSha1_FinishAsSha1)		(u8 context[92], u8 shaOutput[20], bool tlWipeData);
		void			(CALLTYPE *oss_sha1ComputeSha1_FinishAsHex)			(u8 context[92], s8* tcHexOutput, bool tlInsertSpaces, bool tlWipeData);
		u64				(CALLTYPE *oss_sha1Compute64BitFromSha1)			(u8 sha20Bytes[20]);
		u32				(CALLTYPE *oss_sha1Compute32BitFromSha1)			(u8 sha20Bytes[20]);
		bool			(CALLTYPE *oss_sha1Compare)							(u8 sha20Bytes1[20], u8 sha20Bytes2[20]);


//////////
//
// BXML
// The following functions relate the BXML engine as provided by the VVMOSS.
// It is created to provide an autonomous and robust way to access any BXML file
// as created by this engine.
//
//////////
		SBxml*			(CALLTYPE *oss_bxmlLoad)							(s8* tcPathname, u32 tnPathnameLength, u64* tnBytesRead, u64* tnErrorOffset, u64* tnErrorCode);
		SBxml*			(CALLTYPE *oss_bxmlLoadFromBuffer)					(s8* tcBxmlData, u32 tnBxmlDataLength,                   u64* tnErrorOffset, u64* tnErrorCode);
		bool			(CALLTYPE *oss_bxmlSave)							(SBxml* bxml, s8* tcPathname, u32 tnPathnameLength, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnBytesWritten);
		void			(CALLTYPE *oss_bxmlSaveToBuffer)					(SBxml* bxml, SBuffer** build, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnErrorNumber);

		SBxmla*			(CALLTYPE *oss_bxmlaCreate)							(s8* tcNewName, u32 tnNewNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength);
		bool			(CALLTYPE *oss_bxmlaSetName)						(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength);
		bool			(CALLTYPE *oss_bxmlaSetData)						(SBxmla* bxmla, s8* tcData, u32 tnDataLength);
		bool			(CALLTYPE *oss_bxmlaSetTotalLength)					(SBxmla* bxmla, u32 tnDataLengthTotal);
		SBxmla*			(CALLTYPE *oss_bxmlaDelete)							(SBxmla* bxmla, bool tlFreeMemory);
		bool			(CALLTYPE *oss_bxmlaInsert)							(SBxml* bxml, SBxmla* bxmla, s8* tcName, u32 tnNameLength, s8* tcData, u32 tnDataLength, bool tlAfter);
		bool			(CALLTYPE *oss_bxmlaInsertExisting)					(SBxml* bxml, SBxmla* bxmlaRef, SBxmla* bxmlaNew, bool tlAfter);
		SBxmla*			(CALLTYPE *oss_bxmlaCopy)							(SBxmla* bxmla);
		SBxmla*			(CALLTYPE *oss_bxmlaCopyAs)							(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength);
		u64				(CALLTYPE *oss_bxmlaSha1One)						(SBxmla* bxmla, u8 sha20Bytes[20]);
		u64				(CALLTYPE *oss_bxmlaSha1)							(SBxml*  bxml,  u8 sha20Bytes[20]);
		u64				(CALLTYPE *oss_bxmlaSha1Tag)						(SBxml*  bxml,  u8 sha20Bytes[20]);
		u64				(CALLTYPE *oss_bxmlaSha1Data)						(SBxml*  bxml,  u8 sha20Bytes[20]);

		// For 2-way navigation through the attributes (can be done manually, but these expressly do it
		SBxmla*			(CALLTYPE *oss_bxmlaGetNext)						(SBxmla* bxmla);
		SBxmla*			(CALLTYPE *oss_bxmlaGetPrev)						(SBxmla* bxmla);

		SBxml*			(CALLTYPE *oss_bxmlNodeCreate)						(s8* tcNewName, u32 tnNewNameLength);
		bool			(CALLTYPE *oss_bxmlNodeSetName)						(SBxml* bxml, s8* tcNewName, u32 tnNewNameLength);
		SBxml*			(CALLTYPE *oss_bxmlNodeDelete)						(SBxml* bxml, bool tlFreeMemory);
		bool			(CALLTYPE *oss_bxmlNodeInsert)						(SBxml* bxml, SBxml* bxmlRef,                                     bool tlAfter);
		bool			(CALLTYPE *oss_bxmlNodeInsertAsChild)				(SBxml* bxml, SBxml* bxmlParent,                                  bool tlAfter);
		bool			(CALLTYPE *oss_bxmlNodeInsertAsChildAfter)			(SBxml* bxml, SBxml* bxmlParent, SBxml* bxmlRef,                  bool tlAfter);
		SBxml*			(CALLTYPE *oss_bxmlNodeCopy)						(SBxml* bxml,                                        bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult);
		SBxml*			(CALLTYPE *oss_bxmlNodeCopyAs)						(SBxml* bxml,    s8* tcNewName, u32 tnNewNameLength, bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult);
		u64				(CALLTYPE *oss_bxmlNodeSha1)						(SBxml* bxml, u8 sha20Bytes[20]);
		u64				(CALLTYPE *oss_bxmlNodeSha1Tag)						(SBxml* bxml, u8 sha20Bytes[20]);
		u64				(CALLTYPE *oss_bxmlNodeSha1Data)					(SBxml* bxml, u8 sha20Bytes[20]);

		// For 4-way navigation through the XML structure (can be done manually, but these expressly do it
		SBxml*			(CALLTYPE *oss_bxmlNodeGetNext)						(SBxml* bxml);
		SBxml*			(CALLTYPE *oss_bxmlNodeGetPrev)						(SBxml* bxml);
		SBxml*			(CALLTYPE *oss_bxmlNodeGetParent)					(SBxml* bxml);
		SBxml*			(CALLTYPE *oss_bxmlNodeGetFirstChild)				(SBxml* bxml);
		SBxmla*			(CALLTYPE *oss_bxmlNodeGetFirstAttribute)			(SBxml* bxml);

		bool			(CALLTYPE *oss_bxmlFindFirst)						(SBxml* bxmlRoot, SBxml** bxmlNodeFound, SBxmla** bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, bool tlSearchAttributes, void** x);
		bool			(CALLTYPE *oss_bxmlFindContinue)					(void* x);
		u32				(CALLTYPE *oss_bxmlFindAllAsStartEndLists)			(SBxml* bxmlRoot, SStartEnd* bxmlFinds, SStartEnd* bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren, bool tlSearchAttributes);
		// Searches populated data in attributes for the indicated wildcard search string
		bool			(CALLTYPE *oss_bxmlDataFindFirst)					(SBxml* bxmlRoot, SBxmla** bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, void** x);
		bool			(CALLTYPE *oss_bxmlDataFindContinue)				(void* x);
		u32				(CALLTYPE *oss_bxmlDataFindAllAsStartEndList)		(SBxml* bxmlRoot, SStartEnd* bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren);

		void			(CALLTYPE *oss_bxmlGetLastError)					(SBxmlError* errorInfo);


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

		(void *)&oss_getSystemInfo,											(void *)cgcOssGetSystemInfo,
		(void *)&oss_sleep,													(void *)cgcOssSleep,
		(void *)&oss_storeDateTime,											(void *)cgcOssStoreDateTime,
		(void *)&oss_changePathnameExtension,								(void *)cgcOssChangePathnameExtension,
		(void *)&oss_validateFilenameCharacter,								(void *)cgcOssValidateFilenameCharacter,
		(void *)&oss_getNextUniqueId,										(void *)cgcOssGetNextUniqueId,
		(void *)&oss_getNextMessage,										(void *)cgcOssGetNextN_UniqueIds,

		(void *)&oss_deleteScreen,											(void *)cgcOssDeleteScreen,
		(void *)&oss_deleteCanvas,											(void *)cgcOssDeleteCanvas,

		(void *)&oss_requestScreen,											(void *)cgcOssRequestScreen,
		(void *)&oss_requestCanvasForScreen,								(void *)cgcOssRequestCanvasForScreen,
		(void *)&oss_requestCanvasForCanvas,								(void *)cgcOssRequestCanvasForCanvas,
		(void *)&oss_requestCanvas,											(void *)cgcOssRequestCanvas,
		(void *)&oss_requestCanvasAndRegion,								(void *)cgcOssRequestCanvasAndRegion,
		(void *)&oss_requestRegion,											(void *)cgcOssRequestRegion,
		(void *)&oss_requestDuplicateRegion,								(void *)cgcOssRequestDuplicateRegion,
		(void *)&oss_associateCanvasWithScreen,								(void *)cgcOssAssociateCanvasWithScreen,
		(void *)&oss_associateCanvasWithCanvas,								(void *)cgcOssAssociateCanvasWithCanvas,
		(void *)&oss_associateRegionWithCanvas,								(void *)cgcOssAssociateRegionWithCanvas,
		(void *)&oss_associateRegionWithRegion,								(void *)cgcOssAssociateRegionWithRegion,
		(void *)&oss_requestFontHandle,										(void *)cgcOssRequestFontHandle,
		(void *)&oss_canvasDrawFixedPointText,								(void *)cgcOssCanvasWriteFixedPointText,
		(void *)&oss_canvasDrawText,										(void *)cgcOssCanvasDrawText,
		(void *)&oss_canvasDrawTextUnicode,									(void *)cgcOssCanvasDrawTextUnicode,
		(void *)&oss_canvasFrameRect,										(void *)cgcOssCanvasFrameRect,
		(void *)&oss_canvasFillRect,										(void *)cgcOssCanvasFillRect,
		(void *)&oss_canvasLine,											(void *)cgcOssCanvasLine,
		(void *)&oss_canvasArc,												(void *)cgcOssCanvasArc,
		(void *)&oss_canvasExtract,											(void *)cgcOssCanvasExtract,
		(void *)&oss_canvasColorize,										(void *)cgcOssCanvasColorize,
		(void *)&oss_canvasGrayscale,										(void *)cgcOssCanvasGrayscale,
		(void *)&oss_canvasGradient,										(void *)cgcOssCanvasGradient,
		(void *)&oss_canvasBitBlt,											(void *)cgcOssCanvasBitBlt,
		(void *)&oss_canvasRefresh,											(void *)cgcOssCanvasRefresh,
		(void *)&oss_canvasSetRegionAndEventCallback,						(void *)cgcOssCanvasSetRegionAndEventCallback,
		(void *)&oss_canvasGetRegionsList,									(void *)cgcOssCanvasGetRegionsList,
		(void *)&oss_canvasRemoveRegion,									(void *)cgcOssCanvasRemoveRegion,

		(void *)&oss_screenMouseSetEventCallback,							(void *)cgcOssScreenMouseSetEventCallback,
		(void *)&oss_screenMouseRemoveEventCallback,						(void *)cgcOssScreenMouseRemoveEventCallback,
		(void *)&oss_screenMouseGetEventCallbacksList,						(void *)cgcOssScreenMouseGetEventCallbacksList,
		(void *)&oss_screenKeyboardSetEventCallback,						(void *)cgcOssScreenKeyboardSetEventCallback,
		(void *)&oss_screenKeyboardRemoveEventCallback,						(void *)cgcOssScreenKeyboardRemoveEventCallback,
		(void *)&oss_screenKeyboardGetEventCallbacksList,					(void *)cgcOssScreenKeyboardGetEventCallbacksList,

		(void *)&oss_canvasScale,											(void *)cgcOssCanvasScale,
		(void *)&oss_loadBitmapFromDisk,									(void *)cgcOssLoadBitmapFromDisk,
		(void *)&oss_saveBitmapToDisk,										(void *)cgcOssSaveBitmapToDisk,

		(void *)&oss_requestSystemFont,										(void *)cgcOssRequestSystemFont,
		(void *)&oss_requestSystemBitmap,									(void *)cgcOssRequestSystemBitmap,
		(void *)&oss_findSystemFontByHandle,								(void *)cgcOssFindSystemFontByHandle,

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

		(void*)&oss_duplicateString,										(void*)cgcOssDuplicateString,
		(void*)&oss_duplicateUnicodeString,									(void*)cgcOssDuplicateUnicodeString,
		(void*)&oss_duplicateStringIntoDatum,								(void*)cgcOssDuplicateStringIntoDatum,
		(void*)&oss_duplicateStringIntoDatum2,								(void*)cgcOssDuplicateStringIntoDatum2,
		(void*)&oss_duplicateDatum,											(void*)cgcOssDuplicateDatum,
		(void*)&oss_duplicateDatum2,										(void*)cgcOssDuplicateDatum2,
		(void*)&oss_deleteDatum,											(void*)cgcOssDeleteDatum,
		(void*)&oss_deleteDatum2,											(void*)cgcOssDeleteDatum2,
		(void*)&oss_allocateNullStringIntoDatum2,							(void*)cgcOssAllocateNullStringIntoDatum2,
		(void*)&oss_copyUpToShortestString,									(void*)cgcOssCopyUpToShortestString,
		(void*)&oss_wildcardMatch,											(void*)cgcOssWildcardMatch,
		(void*)&oss_asciiToUnicode,											(void*)cgcOssAsciiToUnicode,
		(void*)&oss_unicodeToAscii,											(void*)cgcOssUnicodeToAscii,
		(void*)&oss_asciiToUnicodeChar,										(void*)cgcOssAsciiToUnicodeChar,
		(void*)&oss_unicodeToAsciiCharacter,								(void*)cgcOssUnicodeToAsciiCharacter,
		(void*)&oss_scanForwardUntilCharacterChanges,						(void*)cgcOssScanForwardUntilCharacterChanges,
		(void*)&oss_scanForwardUntilCharacter,								(void*)cgcOssScanForwardUntilCharacter,
		(void*)&oss_unicodeMemcmp,											(void*)cgcOssUnicodeMemcmp,
		(void*)&oss_unicodeMemicmp,											(void*)cgcOssUnicodeMemicmp,
		(void*)&oss_unicodeMemset,											(void*)cgcOssUnicodeMemset,
		(void*)&oss_upperCaseW,												(void*)cgcOssUpperCaseW,
		(void*)&oss_lowerCaseW,												(void*)cgcOssLowerCaseW,
		(void*)&oss_memset,													(void*)cgcOssMemset,
		(void*)&oss_memset4,												(void*)cgcOssMemset4,
		(void*)&oss_memcpy,													(void*)cgcOssMemcpy,
		(void*)&oss_memcmp,													(void*)cgcOssMemcmp,
		(void*)&oss_memicmp,												(void*)cgcOssMemicmp,
		(void*)&oss_memicmpTwoLengths,										(void*)cgcOssMemicmpTwoLengths,
		(void*)&oss_memicmpDatum,											(void*)cgcOssMemicmpDatum,
		(void*)&oss_memicmpDatum2,											(void*)cgcOssMemicmpDatum2,
		(void*)&oss_memicmpDatumDatum,										(void*)cgcOssMemicmpDatumDatum,
		(void*)&oss_memicmpDatum2Datum2,									(void*)cgcOssMemicmpDatum2Datum2,
		(void*)&oss_deriveRGBA,												(void*)cgcOssDeriveRGBA,
		(void*)&oss_getPredictableSequentialPattern,						(void*)cgcOssGetPredictableSequentialPattern,

		(void*)&oss_ll_create,												(void*)cgcOssLlCreate,
		(void*)&oss_ll_insert,												(void*)cgcOssLlInsert,
		(void*)&oss_ll_orphanize,											(void*)cgcOssLlOrphanize,
		(void*)&oss_ll_deleteChainWithCallback,								(void*)cgcOssLlDeleteChainWithCallback,
		(void*)&oss_ll_iterateViaCallback,									(void*)cgcOssLlSha1Chain,

		(void*)&oss_ll4_create,												(void*)cgcOssLl4Create,
		(void*)&oss_ll4_orphanizeAsBxml,									(void*)cgcOssLl4OrphanizeAsBxml,
		(void*)&oss_ll4_orphanizeAsNode,									(void*)cgcOssLl4OrphanizeAsNode,
		(void*)&oss_ll4_insertAsBxml,										(void*)cgcOssLl4InsertAsBxml,
		(void*)&oss_ll4_insertAsBxmlAsChild,								(void*)cgcOssLl4InsertAsBxmlAsChild,
		(void*)&oss_ll4_insertAsBxmlAsChildRegarding,						(void*)cgcOssLl4InsertAsBxmlAsChildRegarding,
		(void*)&oss_ll4_insertAsNodeNorthSouth,								(void*)cgcOssLl4InsertAsNodeNorthSouth,
		(void*)&oss_ll4_insertAsNodeEastWest,								(void*)cgcOssLl4InsertAsNodeEastWest,
		(void*)&oss_ll4_deleteChainWithCallback,							(void*)cgcOssLl4DeleteChainWithCallback,

		(void*)&oss_SEChain_prepend,										(void*)cgcOssSEChainPrepend,
		(void*)&oss_SEChain_append,											(void*)cgcOssSEChainAppend,
		(void*)&oss_SEChain_appendRelativeToMember,							(void*)cgcOssSEChainAppendRelativeToMember,
		(void*)&oss_SEChain_appendExistingRelativeToMember,					(void*)cgcOssSEChainAppendExistingRelativeToMember,

		(void*)&oss_SEChain_migrateAll,										(void*)cgcOssSEChainMigrateAll,
		(void*)&oss_SEChain_migrateByPtr,									(void*)cgcOssSEChainMigrateByPtr,
		(void*)&oss_SEChain_migrateByNum,									(void*)cgcOssSEChainMigrateByNum,
		(void*)&oss_SEChain_completelyMigrateSLLByPtr,						(void*)cgcOssSEChainCompletelyMigrateSLLByPtr,
		(void*)&oss_SEChain_completelyMigrateSLLByNum,						(void*)cgcOssSEChainCompletelyMigrateSLLByNum,

		(void*)&oss_SEChain_countValids,									(void*)cgcOssSEChainCountValids,
		(void*)&oss_SEChain_delete,											(void*)cgcOssSEChainDelete,
		(void*)&oss_SEChain_deleteFrom,										(void*)cgcOssSEChainDeleteFrom,
		(void*)&oss_SEChain_deleteFromAfterCallback,						(void*)cgcOssSEChainDeleteFromAfterCallback,

		(void*)&oss_allocateAdditionalStartEndMasterSlots,					(void*)cgcOssAllocateAdditionalStartEndMasterSlots,
		(void*)&oss_searchSEChainByUniqueId,								(void*)cgcOssSearchSEChainByUniqueId,
		(void*)&oss_searchSEChainByCallback,								(void*)cgcOssSearchSEChainByCallback,
		(void*)&oss_iterateThroughStartEndForCallback,						(void*)cgcOssIterateThroughStartEndForCallback,
		(void*)&oss_validateStartEnd,										(void*)cgcOssValidateStartEnd,
		(void*)&oss_swapEndian,												(void*)cgcOssSwapEndian,
		(void*)&oss_RGBA2BGRA,												(void*)cgcOssRGA2BGRA,
		(void*)&oss_allocateAndNull,										(void*)cgcOssAllocateAndNull,
		(void*)&oss_isNeedleInHaystack,										(void*)cgcOssIsNeedleInHaystack,
		(void*)&oss_isNeedleInHaystack_Unicode,								(void*)cgcOssIsNeedleInHaystackUnicode,
		(void*)&oss_countConsecutiveAsciiNumericDigits,						(void*)cgcOssCountConsecutiveAsciiNumericDigits,
		(void*)&oss_convertTextToU32,										(void*)cgcOssConvertTextToU32,

		(void *)&oss_fileFindFirst,											(void *)cgcOssFindFirstFile,
		(void *)&oss_fileFindNext,											(void *)cgcOssFindNextFile,
		(void *)&oss_fileFindClose,											(void *)cgcOssFindClose,

		(void *)&oss_buildBufferCreateAndInitialize,						(void *)cgcOssBuildBufferCreateAndInitialize,
		(void *)&oss_buildBufferAppendText,									(void *)cgcOssBuildBufferAppendText,
		(void *)&oss_buildBufferSetSize,									(void *)cgcOssBuildBufferSetSize,
		(void *)&oss_buildBufferFreeAndRelease,								(void *)cgcOssBuildBufferFreeAndRelease,

		(void *)&oss_sha1ComputeSha1,										(void *)cgcOssSha1ComputeSha1,
		(void *)&oss_sha1ComputeSha1As64Bit,								(void *)cgcOssSha1ComputeSha1As64Bit,
		(void *)&oss_sha1ComputeSha1As32Bit,								(void *)cgcOssSha1ComputeSha1As32Bit,
		(void *)&oss_sha1ComputeSha1AsHex,									(void *)cgcOssSha1ComputeSha1AsHex,
		(void *)&oss_sha1ConvertHexToSha1,									(void *)cgcOssSha1ConvertHexToSha1,
		(void *)&oss_sha1ConvertSha1ToHex,									(void *)cgcOssSha1ConvertSha1ToHex,
		(void *)&oss_sha1ComputeSha1_Start,									(void *)cgcOssSha1ComputeSha1_Start,
		(void *)&oss_sha1ComputeSha1_ProcessThisData,						(void *)cgcOssSha1ComputeSha1_ProcessThisData,
		(void *)&oss_sha1ComputeSha1_FinishAsSha1,							(void *)cgcOssSha1ComputeSha1_FinishAsSha1,
		(void *)&oss_sha1ComputeSha1_FinishAsHex,							(void *)cgcOssSha1ComputeSha1_FinishAsHex,
		(void *)&oss_sha1Compute64BitFromSha1,								(void *)cgcOssSha1Compute64BitFromSha1,
		(void *)&oss_sha1Compute32BitFromSha1,								(void *)cgcOssSha1Compute32BitFromSha1,
		(void *)&oss_sha1Compare,											(void *)cgcOssSha1Compare,

		(void *)&oss_bxmlLoad,												(void *)cgcOssBxmlLoad,
		(void *)&oss_bxmlLoadFromBuffer,									(void *)cgcOssBxmlLoadFromBuffer,
		(void *)&oss_bxmlSave,												(void *)cgcOssBxmlSave,
		(void *)&oss_bxmlSaveToBuffer,										(void *)cgcOssBxmlSaveToBuffer,

		(void *)&oss_bxmlaCreate,											(void *)cgcOssBxmlAttributeCreate,
		(void *)&oss_bxmlaSetName,											(void *)cgcOssBxmlAttributeSetName,
		(void *)&oss_bxmlaSetData,											(void *)cgcOssBxmlAttributeSetData,
		(void *)&oss_bxmlaSetTotalLength,									(void *)cgcOssBxmlAttributeSetTotalLength,
		(void *)&oss_bxmlaDelete,											(void *)cgcOssBxmlAttributeDelete,
		(void *)&oss_bxmlaInsert,											(void *)cgcOssBxmlAttributeInsert,
		(void *)&oss_bxmlaInsertExisting,									(void *)cgcOssBxmlAttributeInsertExisting,
		(void *)&oss_bxmlaCopy,												(void *)cgcOssBxmlAttributeCopy,
		(void *)&oss_bxmlaCopyAs,											(void *)cgcOssBxmlAttributeCopyAs,
		(void *)&oss_bxmlaSha1One,											(void *)cgcOssBxmlAttributeSha1One,
		(void *)&oss_bxmlaSha1,												(void *)cgcOssBxmlAttributeSha1,
		(void *)&oss_bxmlaSha1Tag,											(void *)cgcOssBxmlAttributeSha1Tag,
		(void *)&oss_bxmlaSha1Data,											(void *)cgcOssBxmlAttributeSha1Data,

		(void *)&oss_bxmlaGetNext,											(void *)cgcOssBxmlAttributeGetNext,
		(void *)&oss_bxmlaGetPrev,											(void *)cgcOssBxmlAttributeGetPrev,

		(void *)&oss_bxmlNodeCreate,										(void *)cgcOssBxmlNodeCreate,
		(void *)&oss_bxmlNodeSetName,										(void *)cgcOssBxmlNodeSetName,
		(void *)&oss_bxmlNodeDelete,										(void *)cgcOssBxmlNodeDelete,
		(void *)&oss_bxmlNodeInsert,										(void *)cgcOssBxmlNodeInsert,
		(void *)&oss_bxmlNodeInsertAsChild,									(void *)cgcOssBxmlNodeInsertAsChild,
		(void *)&oss_bxmlNodeInsertAsChildAfter,							(void *)cgcOssBxmlNodeInsertAsChildAfter,
		(void *)&oss_bxmlNodeCopy,											(void *)cgcOssBxmlNodeCopy,
		(void *)&oss_bxmlNodeCopyAs,										(void *)cgcOssBxmlNodeCopyAs,
		(void *)&oss_bxmlNodeSha1,											(void *)cgcOssBxmlNodeSha1,
		(void *)&oss_bxmlNodeSha1Tag,										(void *)cgcOssBxmlNodeSha1Tag,
		(void *)&oss_bxmlNodeSha1Data,										(void *)cgcOssBxmlNodeSha1Data,

		(void *)&oss_bxmlNodeGetNext,										(void *)cgcOssBxmlGetNext,
		(void *)&oss_bxmlNodeGetPrev,										(void *)cgcOssBxmlGetPrev,
		(void *)&oss_bxmlNodeGetParent,										(void *)cgcOssBxmlGetParent,
		(void *)&oss_bxmlNodeGetFirstChild,									(void *)cgcOssBxmlGetFirstChild,
		(void *)&oss_bxmlNodeGetFirstAttribute,								(void *)cgcOssBxmlGetFirstAttribute,

		(void *)&oss_bxmlFindFirst,											(void *)cgcOssBxmlFindFirst,
		(void *)&oss_bxmlFindContinue,										(void *)cgcOssBxmlFindContinue,
		(void *)&oss_bxmlFindAllAsStartEndLists,							(void *)cgcOssBxmlFindAllAsStartEndLists,

		(void *)&oss_bxmlDataFindFirst,										(void *)cgcOssBxmlDatFindFirst,
		(void *)&oss_bxmlDataFindContinue,									(void *)cgcOssBxmlDataFindContinue,
		(void *)&oss_bxmlDataFindAllAsStartEndList,							(void *)cgcOssBxmlDataFindAllAsStartEndList,

		(void *)&oss_bxmlGetLastError,										(void *)cgcOssBxmlGetLastError,

		(void *)&oss_threadCreate,											(void *)cgcOssThreadCreate,
		(void *)&oss_threadSuspend,											(void *)cgcOssThreadSuspend,
		(void *)&oss_threadResume,											(void *)cgcOssThreadResume,
		(void *)&oss_threadTerminate,										(void *)cgcOssThreadTerminate,

		(void *)&oss_createScreenTemplate,									(void *)cgcOssCreateScreenTemplate,

		(void *)&oss_getScreenDimensions,									(void *)cgcOssGetScreenDimensions,
		(void *)&oss_setFocus,												(void *)cgcOssSetFocus,

		(void *)&oss_bitBlt,												(void *)cgcOssBitBlt,
		(void *)&oss_bitBltSystemBitmapToSRGBA,								(void *)cgcOssBitBltSystemBitmapToSRGBA,

		(void *)&oss_drawText,												(void *)cgcOssDrawText,

		(void *)&oss_getNextMessage,										(void *)cgcOssGetNextMessage,
		(void *)&oss_messageBox,											(void *)cgcOssMessageBox,
		(void *)&oss_messageBoxUnicode,										(void *)cgcOssMessageBoxUnicode,

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
// Called once to load all the gVvmOssFunctions[] at startup.
//
//////
	void** iLoadVvmOssFunctionsFromVVM(void** tnFuncAddress)
	{
		u32			lnI;
		s8*			lcFuncName;
		void*		lnAddress;
		void**		lcFuncAddress;
		s8			buffer[1024];


		// Grab the address of the VVM interface for function address requests
		lcFuncAddress	= (void**)&vvm_debuggerInterface;
		*lcFuncAddress	= (void*)tnFuncAddress;


		// Now, repeatedly call back that address with the request to all of the function addresses
		for (lnI = 0; lnI < gVvmOssFunctionCount; lnI++)
		{
			// Grab the details of this entry
			tnFuncAddress	= (void**)gVvmOssFunctions[(lnI * 2) + 0];						// Grab the indirect address to store
			lcFuncName		= (s8*)   gVvmOssFunctions[(lnI * 2) + 1];						// Grab the function name to request

			// Ask the VVM for this specific function location
			lnAddress = (void*)vvm_debuggerInterface(lcFuncName);

			// Process the result
			if (!lnAddress)
			{
				// The specified functionality is not available
				sprintf_s(buffer, sizeof(buffer), "Error accessing: %s\000", lcFuncName);
				MessageBoxA(NULL, buffer, "VVMOSS Initialization Error", MB_OK);
				// We need all the functions we request, not just some of them
				return((void**)-1);		// Indicate a fatal error
			}
			// If we get here, this function was found and we can store it
			*tnFuncAddress = lnAddress;
		}
		// When we get here, we've made the full connection to the VVM
		return(tnFuncAddress);
	}




//////////
//
// Attempt to load vvmoss.dll and access all required functions
//
//////
	HINSTANCE vvmOssDllInstance = NULL;
	bool iLoadVvmOssFunctionsFromDll(void)
	{
		u32			lnI;
		s8*			lcFuncName;
		void**		lcFuncAddress;
		void*		lcAddress;
		s8			buffer[1024];


		// Try to load the dll
		if (!vvmOssDllInstance)
		{
			vvmOssDllInstance = LoadLibraryA("vvmoss.dll");
			if (!vvmOssDllInstance)
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
			lcAddress = GetProcAddress(vvmOssDllInstance, lcFuncName);

			// Process the result
			if (!lcAddress)
			{
				// The specified functionality is not available
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

