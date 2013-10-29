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



#include "common_vvmoss_const.h"



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
	const s8		cgcOssGetNextUniqueId[]									= "oss_getNextUniqueId";
	const s8		cgcOssGetNextN_UniqueIds[]								= "oss_getNextN_UniqueIds";

	const s8		cgcOssDeleteScreen[]									= "oss_deleteScreen";
	const s8		cgcOssDeleteCanvas[]									= "oss_deleteCanvas";

	const s8		cgcOssCreateScreenAndVisibleWindow[]					= "oss_createScreenAndVisibleWindow";
	const s8		cgcOssCreateRegionForScreen[]							= "oss_createRegionForScreen";
	const s8		cgcOssCreateCanvasForScreen[]							= "oss_createCanvasForScreen";
	const s8		cgcOssCreateCanvas[]									= "oss_createCanvas";
	const s8		cgcOssCreateRegion[]									= "oss_createRegion";
	const s8		cgcOssCreateRegionAndCanvas[]							= "oss_createRegionAndCanvas";
	const s8		cgcOssCreateFontHandle[]								= "oss_createFontHandle";

	const s8		cgcOssScreenRefresh[]									= "oss_screenRefresh";
	const s8		cgcOssScreenSetFocus[]									= "oss_screenSetFocus";

	const s8		cgcOssRegionDuplicate[]									= "oss_regionDuplicate";
	const s8		cgcOssRegionDefaultPaint[]								= "oss_regionDefaultPaint";
	const s8		cgcOssRegionRefresh[]									= "oss_regionRefresh";

	const s8		cgcOssCanvasWriteFixedPointText[]						= "oss_canvasDrawFixedPointText";
	const s8		cgcOssCanvasDrawText[]									= "oss_canvasDrawText";
	const s8		cgcOssCanvasFrameRect[]									= "oss_canvasFrameRect";
	const s8		cgcOssCanvasFillRect[]									= "oss_canvasFillRect";
	const s8		cgcOssCanvasLine[]										= "oss_canvasLine";
	const s8		cgcOssCanvasArc[]										= "oss_canvasArc";
	const s8		cgcOssCanvasExtract[]									= "oss_canvasExtract";
	const s8		cgcOssCanvasColorize[]									= "oss_canvasColorize";
	const s8		cgcOssCanvasGrayscale[]									= "oss_canvasGrayscale";
	const s8		cgcOssCanvasGradient[]									= "oss_canvasGradient";
	const s8		cgcOssCanvasBitBlt[]									= "oss_canvasBitBlt";
	const s8		cgcOssCanvasScale[]										= "oss_canvasScale";

	const s8		cgcOssCaskDefineStandard[]								= "oss_caskDefineStandard";
	const s8		cgcOssCaskDefineEncompassingRectangle[]					= "oss_caskDefineEncompassingRectangle";
	const s8		cgcOssCaskDefineUpRectangle[]							= "oss_caskDefineUpRectangle";
	const s8		cgcOssCaskDefineDownRectangle[]							= "oss_caskDefineDownRectangle";
	const s8		cgcOssCaskSetPipByValues[]								= "oss_caskSetPipByValues";
	const s8		cgcOssCaskSetPipByStruct[]								= "oss_caskSetPipByStruct";
	const s8		cgcOssCaskCreate[]										= "oss_caskCreate";
	const s8		cgcOssCaskRefresh[]										= "oss_caskRefresh";

	const s8		cgcOssScreenMouseSetEventCallback[]						= "oss_screenMouseSetEventCallback";
	const s8		cgcOssScreenMouseRemoveEventCallback[]					= "oss_screenMouseRemoveEventCallback";
	const s8		cgcOssScreenMouseGetEventCallbacksList[]				= "oss_screenMouseGetEventCallbacksList";
	const s8		cgcOssScreenKeyboardSetEventCallback[]					= "oss_screenKeyboardSetEventCallback";
	const s8		cgcOssScreenKeyboardRemoveEventCallback[]				= "oss_screenKeyboardRemoveEventCallback";
	const s8		cgcOssScreenKeyboardGetEventCallbacksList[]				= "oss_screenKeyboardGetEventCallbacksList";

	const s8		cgcOssLoadBitmapFromDisk[]								= "oss_bitmapLoadFromDisk";
	const s8		cgcOssSaveBitmapToDisk[]								= "oss_bitmapSaveToDisk";
	const s8		cgcOssCreateSystemFont[]								= "oss_systemCreateFont";
	const s8		cgcOssCreateSystemBitmap[]								= "oss_systemCreateBitmap";
	const s8		cgcOssFindSystemFontByHandle[]							= "oss_systemFindFontByHandle";

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
	const s8		cgcOssDatumSet[]										= "oss_datumSet";
	const s8		cgcOssDatum2Set[]										= "oss_datum2Set";
	const s8		cgcOssDatumDuplicate[]									= "oss_datumDuplicate";
	const s8		cgcOssDatum2Duplicate[]									= "oss_datum2Duplicate";
	const s8		cgcOssDatumDelete[]										= "oss_datumDelete";
	const s8		cgcOssDatum2Delete[]									= "oss_datum2Delete";
	const s8		cgcOssDatum2SetNullString[]								= "oss_datum2SetNullString";
	
	const s8		cgcOssCopyUpToShortestString[]							= "oss_copyUpToShortestString";
	const s8		cgcOssWildcardMatchDatum[]								= "oss_wildcardMatchDatum";
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
	const s8		cgcOssLlDelete[]										= "oss_ll_delete";
	const s8		cgcOssLlDeleteWithCallback[]							= "oss_ll_deleteWithCallback";
	const s8		cgcOssLlInsert[]										= "oss_ll_insert";
	const s8		cgcOssLlOrphanize[]										= "oss_ll_orphanize";
	const s8		cgcOssLlDeleteChain[]									= "oss_ll_deleteChain";
	const s8		cgcOssLlDeleteChainWithCallback[]						= "oss_ll_deleteChainWithCallback";
	const s8		cgcOssLlIterateViaCallback[]							= "oss_ll_iterateViaCallback";
	const s8		cgcOssLlIterateBackwardViaCallback[]					= "oss_ll_iterateBackwardViaCallback";
	const s8		cgcOssLlGetFirstNode[]									= "oss_ll_getFirstNode";
	const s8		cgcOssLlGetLastNode[]									= "oss_ll_getLastNode";

	const s8		cgcOssLl4Create[]										= "oss_ll4_create";
	const s8		cgcOssLl4CreateChain[]									= "oss_ll4_createChain";
	const s8		cgcOssLl4Delete[]										= "oss_ll4_delete";
	const s8		cgcOssLl4OrphanizeAsNode[]								= "oss_ll4_orphanize";
	const s8		cgcOssLl4InsertAsNodeNorthSouth[]						= "oss_ll4_insertNorthSouth";
	const s8		cgcOssLl4InsertAsNodeEastWest[]							= "oss_ll4_insertWestEast";
	const s8		cgcOssLl4DeleteChain[]									= "oss_ll4_deleteChain";
	const s8		cgcOssLl4DeleteChainWithCallback[]						= "oss_ll4_deleteChainWithCallback";
	const s8		cgcOssLl4IterateViaCallback[]							= "oss_ll4_iterateViaCallback";
	const s8		cgcOssLl4GetLastNode[]									= "oss_ll4_getLastNode";

	const s8		cgcOssLl4BxmlInsert[]									= "oss_ll4bxml_insert";
	const s8		cgcOssLl4BxmlOrphanize[]								= "oss_ll4bxml_orphanize";
	const s8		cgcOssLl4BxmlInsertAsChild[]							= "oss_ll4bxml_insertAsChild";
	const s8		cgcOssLl4BxmlInsertAsChildRegarding[]					= "oss_ll4bxml_insertAsChildRegarding";

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
	const s8		cgcOssSEChainDeleteAsPtrBlock[]							= "oss_SEChain_deleteAsPtrBlock";
	const s8		cgcOssSEChainDeleteFrom[]								= "oss_SEChain_deleteFrom";
	const s8		cgcOssSEChainDeleteFromAfterCallback[]					= "oss_SEChain_deleteFromAfterCallback";

	const s8		cgcOssSEChainAllocateAdditionalMasterSlots[]			= "oss_SEChain_allocateAdditionalMasterSlots";
	const s8		cgcOssSEChainSearchByUniqueId[]							= "oss_SEChain_searchByUniqueId";
	const s8		cgcOssSEChainSearchByCallback[]							= "oss_SEChain_searchByCallback";
	const s8		cgcOssSEChainIterateThroughForCallback[]				= "oss_SEChain_iterateThroughForCallback";
	const s8		cgcOssSEChainValidate[]									= "oss_SEChain_validate";
	
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

	const s8		cgcOssBuildBufferCreateAndInitialize[]					= "oss_builderCreateAndInitialize";
	const s8		cgcOssBuildBufferAppendText[]							= "oss_builderAppendText";
	const s8		cgcOssBuildBufferSetSize[]								= "oss_builderSetSize";
	const s8		cgcOssBuildBufferFreeAndRelease[]						= "oss_builderFreeAndRelease";

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

	const s8		cgcOssBxmlAttributeFindAndGetString[]					= "oss_bxmlaFindAndGetString";
	const s8		cgcOssBxmlAttributeFindAndGetU32[]						= "oss_bxmlaFindAndGetU32";
	const s8		cgcOssBxmlAttributeFindAndGetU64[]						= "oss_bxmlaFindAndGetU64";
	const s8		cgcOssBxmlAttributeFindAndGetUBool[]					= "oss_bxmlaFindAndGetBool";
	const s8		cgcOssBxmlAttributeFindAndGetF32[]						= "oss_bxmlaFindAndGetF32";
	const s8		cgcOssBxmlAttributeFindAndGetF64[]						= "oss_bxmlaFindAndGetF64";

	const s8		cgcOssBxmlAttributeGetString[]							= "oss_bxmlaGetString";
	const s8		cgcOssBxmlAttributeGetU32[]								= "oss_bxmlaGetU32";
	const s8		cgcOssBxmlAttributeGetU64[]								= "oss_bxmlaGetU64";
	const s8		cgcOssBxmlAttributeGetUBool[]							= "oss_bxmlaGetBool";
	const s8		cgcOssBxmlAttributeGetF32[]								= "oss_bxmlaGetF32";
	const s8		cgcOssBxmlAttributeGetF64[]								= "oss_bxmlaGetF64";

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

	const s8		cgcOssBxmlFindAttribute[]								= "oss_bxmlFindAttribute";
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
		void			(CALLTYPE *oss_dateTimeGet)							(SDateTime* tdt);
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

		u64				(CALLTYPE *oss_screenRefresh)							(SScreen* ts);
		bool			(CALLTYPE *oss_screenSetFocus)							(SScreen *ts);

		SRegion*		(CALLTYPE *oss_regionDuplicate)							(u64 tnAssociatedId, SRegion* templateRegion);
		u64				(CALLTYPE *oss_regionDefaultPaint)						(SRegion* tr);
		u64				(CALLTYPE *oss_regionRefresh)							(SRegion* tr, SRegion* trParent);

		u64				(CALLTYPE *oss_canvasDrawFixedPointText)				(SCanvas* tc, SBGRA* bd, u32 fontWidth, u32 fontHeight, s32 ulx, s32 uly,    s8*  text, u32 characterCount, SBGRA foreground, SBGRA background);
		u64				(CALLTYPE *oss_canvasDrawText)							(SCanvas* tc, SBGRA* bd, u64 fontHandle, s32 ulx, s32 uly, s32 lrx, s32 lry, s8*  tcText, u32 tnTextLength, SBGRA foreground, SBGRA background);
		u64				(CALLTYPE *oss_canvasFrameRect)							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border);
		u64				(CALLTYPE *oss_canvasFillRect)							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border, SBGRA background);
		u64				(CALLTYPE *oss_canvasLine)								(SCanvas* tc, SBGRA* bd, s32 p1x, s32 p1y, s32 p2x, s32 p2y, s32 lineThickness, SBGRA line);
		u64				(CALLTYPE *oss_canvasArc)								(SCanvas* tc, SBGRA* bd, s32 ox, s32 oy, f32 radius, f32 start, f32 end, s32 lineThickness, SBGRA line);
		SCanvas*		(CALLTYPE *oss_canvasExtract)							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry);
		u64				(CALLTYPE *oss_canvasColorize)							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, SBGRA color);
		u64				(CALLTYPE *oss_canvasGrayscale)							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry);
		u64				(CALLTYPE *oss_canvasGradient)							(SCanvas* tc, SBGRA* bd, SBGRA ul, SBGRA ur, SBGRA lr, SBGRA ll);
		u64				(CALLTYPE *oss_canvasBitBlt)							(SCanvas* tsDst, bool tlDstAccumulator, s32 dulx, s32 duly, SCanvas* tsSrc, bool tlSrcAccumulator, s32 sulx, s32 suly, s32 slrx, s32 slry);
		u64				(CALLTYPE *oss_canvasScale)								(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap** tsScaleMap);

		SCask*			(CALLTYPE *oss_caskDefineStandard)						(u32 tnHeight, u32 tnWidth, u32 tnLeftStyle, u32 tnLeftState, u32 tnLeftPipCount, u32 tnLeftColor, csu8p tcLeftText, u32 tnRightStyle, u32 tnRightState, u32 tnRightPipCount, u32 tnRightColor, csu8p tcRightText);
		SCask*			(CALLTYPE *oss_caskDefineEncompassingRectangle)			(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SRectXYXY* tsOuter);
		SCask*			(CALLTYPE *oss_caskDefineUpRectangle)					(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter);
		SCask*			(CALLTYPE *oss_caskDefineDownRectangle)					(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter);
		SCaskPip*		(CALLTYPE *oss_caskSetPipByValues)						(SCask* cask, bool tlLeft, u32 tnPip, SBGRA tnPipColorNeutral, SBGRA tnPipColorOver, SBGRA tnPipColorClick, u64 tnEnterCallback, u64 tnLeaveCallback, u64 tnHoverCallback, u64 tnClickCallback, bool tlCreateCopy);
		SCaskPip*		(CALLTYPE *oss_caskSetPipByStruct)						(SCask* cask, bool tlLeft, u32 tnPip, SCaskPip* caskPip, bool tlCreateCopy);
		SCask*			(CALLTYPE *oss_caskCreate)								(SCask* cask, bool tlCreateCopy);
		SCanvas*		(CALLTYPE *oss_caskRefresh)								(SCask* cask);

		u64				(CALLTYPE *oss_screenMouseSetEventCallback)				(u64 id, SCanvas* tc, SEvent* event);
		u64				(CALLTYPE *oss_screenMouseRemoveEventCallback)			(u64 id, SCanvas* tc, SEvent* event);
		void			(CALLTYPE *oss_screenMouseGetEventCallbacksList)		(u64 id, SCanvas* tc, SEvent** events, u32* count);
		u64				(CALLTYPE *oss_screenKeyboardSetEventCallback)			(u64 id, SCanvas* tc, SEvent* event);
		u64				(CALLTYPE *oss_screenKeyboardRemoveEventCallback)		(u64 id, SCanvas* tc, SEvent* event);
		void			(CALLTYPE *oss_screenKeyboardGetEventCallbacksList)		(u64 id, SCanvas* tc, SEvent** events, u32* count);

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
		SOssWindow*		(CALLTYPE *oss_screenEnumerateMonitors)						(SStartEnd* tsMonitors/*Returns SOssWindow* structures*/);
		void			(CALLTYPE *oss_screenComputeMonitorCoordinates)				(SOssWindow* tow, f32 tfPercent, u32 tnPosition, f32 tfMargin, s32* tnX, s32* tnY, u32* tnWidth, u32* tnHeight, u32* tnWidthMax, u32* tnHeightMax, u32* tnWidthMin, u32* tnHeightMin);
		bool			(CALLTYPE *oss_screenGetDimensions)						(u64 tnOssWindowId, s32* tnX, s32* tnY, u32* tnWidth, u32* tnHeight, u32* tnWidthMax, u32* tnHeightMax, u32* tnWidthMin, u32* tnHeightMin);

		u64				(CALLTYPE *oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb)	(u64 tnOssWindowId, SBGRA* bd, u32 width, u32 height);
		u64				(CALLTYPE *oss_lowLevel_bitBlt_ossRgb_onto_canvasBgra)	(u64 bdoss, s32 tnX, s32 tnY, u32 tnWidth, u32 tnHeight, SCanvas* tc, SBGRA* bdRoot);
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
		bool			(CALLTYPE *oss_sharedAsciiDeleteFile)				(s8* tcFullPathname);
		bool			(CALLTYPE *oss_sharedAsciiWriteOutFile)				(s8* tcFullPathname, s8* tcData, u32 tnDataLength);


//////////
//
// Common functions
//
//////
		// Prototype definitions
		u8*				(CALLTYPE *oss_duplicateString)						(u8* ptr, u64 length);
		w16*			(CALLTYPE *oss_duplicateUnicodeString)				(w16* tuText);
		SDatum*			(CALLTYPE *oss_datumSet)							(SDatum*  datum,  u8* ptr, u64 length,                  bool tlFreeExisting);
		SDatum2*		(CALLTYPE *oss_datumSet2)							(SDatum2* datum2, u8* ptr, u64 length, u64 totalLength, bool tlFreeExisting);
		SDatum*			(CALLTYPE *oss_datumDuplicate)						(SDatum*  datumDst,  SDatum*  datumSrc);
		SDatum2*		(CALLTYPE *oss_datum2Duplicate)						(SDatum2* datum2Dst, SDatum2* datum2Src);
		void			(CALLTYPE *oss_datumDelete)							(SDatum*  datum);
		void			(CALLTYPE *oss_datum2Delete)						(SDatum2* datum2);
		void			(CALLTYPE *oss_datum2SetNullString)					(SDatum2* datum2, u64 length, bool tlInitialize);

		void			(CALLTYPE *oss_copyUpToShortestString)				(u8* dst, u32 tnDstLength, u8* src, u32 tnSrcLength);
		s32				(CALLTYPE *oss_wildcardMatchDatum)					(SDatum* tsCandidate, SDatum* tsWildcardPattern, bool tlCaseSensitive);
		s32				(CALLTYPE *oss_wildcardMatch)						(csu8p candidate, csu8p wildcardPattern, bool tlCaseSensitive);
		w16*			(CALLTYPE *oss_asciiToUnicode)						(u8* tcText, u32 tnTextLength);
		s8*				(CALLTYPE *oss_unicodeToAscii)						(w16* tuText, u32 tnTextLength);
		w16				(CALLTYPE *oss_asciiToUnicodeChar)					(u8 tcChar);
		s8				(CALLTYPE *oss_unicodeToAsciiCharacter)				(w16 tuChar);
		u64				(CALLTYPE *oss_scanForwardUntilCharacterChanges)	(csu8p tcData, u64 tnMaxLength);
		u64				(CALLTYPE *oss_scanForwardUntilCharacter)			(csu8p tcData, s8 c);
		int				(CALLTYPE *oss_unicodeMemcmp)						(w16* l, w16* r, u32 tnLength);
		int				(CALLTYPE *oss_unicodeMemicmp)						(w16* l, w16* r, u32 tnLength);
		int				(CALLTYPE *oss_unicodeMemset)						(w16* p, w16 c, u32 tnLength);
		w16				(CALLTYPE *oss_upperCaseW)							(w16 u);
		w16				(CALLTYPE *oss_lowerCaseW)							(w16 u);
		void			(CALLTYPE *oss_memset)								(s8* dst, s8 c, u64 tnCount);
		void			(CALLTYPE *oss_memset4)								(u32* dst, u32 val, u64 tnCount);
		void			(CALLTYPE *oss_memcpy)								(s8* dst, s8* src, u64 tnCount);
		s32				(CALLTYPE *oss_memcmp)								(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
		s32				(CALLTYPE *oss_memicmp)								(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
		s32				(CALLTYPE *oss_memicmpTwoLengths)					(csu8p l/*eft*/, u64 tnLeftLength, csu8p r/*ight*/, u64 tnRightLength);
		s32				(CALLTYPE *oss_memicmpDatum)						(SDatum*  datum,  csu8p r/*ight*/, u64 tnRightLength);
		s32				(CALLTYPE *oss_memicmpDatum2)						(SDatum2* datum2, csu8p r/*ight*/, u64 tnRightLength);
		s32				(CALLTYPE *oss_memicmpDatumDatum)					(SDatum*  datumL,  SDatum*  datumR);
		s32				(CALLTYPE *oss_memicmpDatum2Datum2)					(SDatum2* datum2L, SDatum2* datum2R);
		void			(CALLTYPE *oss_deriveRGBA)							(u32 tnColor, u8* tnRed, u8* tnGrn, u8* tnBlu, f32* tfAlp);
		u8				(CALLTYPE *oss_getPredictableSequentialPattern)		(u32 tnIterator, u32 tnValue);

		SLL*			(CALLTYPE *oss_ll_create)							(SLL* nodePrev, SLL* nodeNext, u64 tnUniqueId, u32  tnSize);
		void			(CALLTYPE *oss_ll_delete)							(SLL* node);
		void			(CALLTYPE *oss_ll_deleteWithCallback)				(SLLCallback* cb);
		bool			(CALLTYPE *oss_ll_insert)							(SLL* node, SLL* nodeRef, bool tlAfter);
		void			(CALLTYPE *oss_ll_orphanize)						(SLL* node);
		void			(CALLTYPE *oss_ll_deleteChain)						(SLL** root);
		void			(CALLTYPE *oss_ll_deleteChainWithCallback)			(SLLCallback* cb);
		void			(CALLTYPE *oss_ll_iterateViaCallback)				(SLLCallback* cb);
		void			(CALLTYPE *oss_ll_iterateBackwardViaCallback)		(SLLCallback* cb);
		SLL*			(CALLTYPE *oss_ll_getFirstNode)						(SLL* node);
		SLL*			(CALLTYPE *oss_ll_getLastNode)						(SLL* node);

		SLL4*			(CALLTYPE *oss_ll4_create)							(SLL4* nodeWest, SLL4* nodeEast, SLL4* nodeNorth, SLL4* nodeSouth, u64 tnUniqueId, u32 tnSize);
		SLL4*			(CALLTYPE *oss_ll4_createChain)						(u32 tnSize, u32* tnCount, u32 tnDirection);
		void			(CALLTYPE *oss_ll4_delete)							(SLL4* node);
		bool			(CALLTYPE *oss_ll4_orphanize)						(SLL4* node);
		bool			(CALLTYPE *oss_ll4_insertNorthSouth)				(SLL4* node, SLL4* nodeRef,                   bool tlAfter);
		bool			(CALLTYPE *oss_ll4_insertWestEast)					(SLL4* node, SLL4* nodeRef,                   bool tlAfter);
		void			(CALLTYPE *oss_ll4_deleteChain)						(SLL4** root, u32 tnDirection);
		void			(CALLTYPE *oss_ll4_deleteChainWithCallback)			(SLL4Callback* cb, u32 tnDirection);
		void			(CALLTYPE *oss_ll4_iterateViaCallback)				(SLL4Callback* cb, u32 tnDirection);
		SLL4*			(CALLTYPE *oss_ll4_getLastNode)						(SLL4* node, u32 tnDirection);

		bool			(CALLTYPE *oss_ll4bxml_orphanize)					(SLL4* bxml);
		bool			(CALLTYPE *oss_ll4bxml_insert)						(SLL4* bxmlSibling,	SLL4* bxmlRef,							bool tlAfter);
		bool			(CALLTYPE *oss_ll4bxml_insertAsChild)				(SLL4* bxmlChild,	SLL4* bxmlParent,						bool tlPrepend);
		bool			(CALLTYPE *oss_ll4bxml_insertAsChildRegarding)		(SLL4* bxmlChild,	SLL4* bxmlParent, SLL4* bxmlRegarding,	bool tlAfter);

		void*			(CALLTYPE *oss_SEChain_prepend)						(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
		void*			(CALLTYPE *oss_SEChain_append)						(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
		void*			(CALLTYPE *oss_SEChain_appendRelativeToMember)		(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize,     u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);
		void*			(CALLTYPE *oss_SEChain_appendExistingRelativeToMember)(SStartEnd* ptrSE, SLL* ptrRef,                 u64 tnUniqueIdExtra, SLL* ptrCaller, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);

		void*			(CALLTYPE *oss_SEChain_migrateAll)					(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc);
		SMasterList*	(CALLTYPE *oss_SEChain_migrateByPtr)				(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, void* ptr,    u32 tnHint, u32 tnBlockSize);
		SMasterList*	(CALLTYPE *oss_SEChain_migrateByNum)				(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);
		SLL*			(CALLTYPE *oss_SEChain_completelyMigrateSLLByPtr)	(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr,     u32 tnHint, u32 tnBlockSize);
		SLL*			(CALLTYPE *oss_SEChain_completelyMigrateSLLByNum)	(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);

		u32				(CALLTYPE *oss_SEChain_countValids)					(SStartEnd* ptrSE);
		u32				(CALLTYPE *oss_SEChain_delete)						(SStartEnd* ptrSE, u64 tnCallback, u64 tnParam, bool tlDeletePointers);
		void			(CALLTYPE *oss_SEChain_deleteAsPtrBlock)			(SStartEnd* ptrSE);
		void			(CALLTYPE *oss_SEChain_deleteFrom)					(SStartEnd* ptrSE, void* ptrDel, bool tlDeletePointers);
		bool			(CALLTYPE *oss_SEChain_deleteFromAfterCallback)		(SStartEnd* ptrSE, bool tlDeletePointers, SStartEndCallback* cb);

		bool			(CALLTYPE *oss_SEChain_allocateAdditionalMasterSlots)(SStartEnd* ptrSE, u32 tnBlockSize);
		void*			(CALLTYPE *oss_SEChain_searchByUniqueId)			(SStartEnd* ptrSE, u64 tnUniqueId);
		void*			(CALLTYPE *oss_SEChain_searchByCallback)			(SStartEnd* ptrSE, SStartEndCallback* cb);
		void			(CALLTYPE *oss_SEChain_iterateThroughForCallback)	(SStartEnd* ptrSE, SStartEndCallback* cb);
		void			(CALLTYPE *oss_SEChain_validate)					(SStartEnd* ptrSE, SStartEndCallback* cb);

		u32				(CALLTYPE *oss_swapEndian)							(u32 tnValue);
		u32				(CALLTYPE *oss_RGBA2BGRA)							(u32 tnColor);
		void*			(CALLTYPE *oss_allocateAndNull)						(u32 tnSize, bool tnInitToZeros);
		bool			(CALLTYPE *oss_isNeedleInHaystack)					(csu8p tcHaystack, s32 tnHaystackLength, csu8p tcNeedle, s32 tnNeedleLength, bool tlCaseSensitive, u32* tnFoundPosition);
		bool			(CALLTYPE *oss_isNeedleInHaystack_Unicode)			(w16* twHaystack, w16* twNeedle);
		u32				(CALLTYPE *oss_countConsecutiveAsciiNumericDigits)	(s8* buffer, u32 tnMaxLength);
		u32				(CALLTYPE *oss_convertTextToU32)					(s8* tcNumbers, u32 tnMaxLength);


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
// Build Buffer
// An accumulation template for appending data in a stream manner, or for allocating a specified
// size and then randomly updating it.
//
//////////
		void			(CALLTYPE *oss_builderCreateAndInitialize)		(SBuilder** buffRoot, u32 tnAllocationSize);
		s8*				(CALLTYPE *oss_builderAppendText)				(SBuilder*  buffRoot, s8* tcData, u32 tnDataLength);
		void			(CALLTYPE *oss_builderSetSize)					(SBuilder** buffRoot, u32 tnBufferLength);
		void			(CALLTYPE *oss_builderFreeAndRelease)			(SBuilder** buffRoot);


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
		void			(CALLTYPE *oss_bxmlSaveToBuffer)					(SBxml* bxml, SBuilder** build, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnErrorNumber);

		SBxmla*			(CALLTYPE *oss_bxmlaCreate)							(s8* tcNewName, u32 tnNewNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength);
		bool			(CALLTYPE *oss_bxmlaSetName)						(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength);
		bool			(CALLTYPE *oss_bxmlaSetData)						(SBxmla* bxmla, s8* tcData, u32 tnDataLength);
		bool			(CALLTYPE *oss_bxmlaSetTotalLength)					(SBxmla* bxmla, u32 tnDataLengthTotal);
		SBxmla*			(CALLTYPE *oss_bxmlaDelete)							(SBxmla* bxmla, bool tlFreeMemory);
		bool			(CALLTYPE *oss_bxmlaInsert)							(SBxml* bxml, SBxmla* bxmlaRef, s8* tcName, u32 tnNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength, bool tlAfter);
		bool			(CALLTYPE *oss_bxmlaInsertExisting)					(SBxml* bxml, SBxmla* bxmlaRef, SBxmla* bxmlaNew, bool tlAfter);
		SBxmla*			(CALLTYPE *oss_bxmlaCopy)							(SBxmla* bxmla);
		SBxmla*			(CALLTYPE *oss_bxmlaCopyAs)							(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength);
		u64				(CALLTYPE *oss_bxmlaSha1One)						(SBxmla* bxmla, u8 sha20Bytes[20]);
		u64				(CALLTYPE *oss_bxmlaSha1)							(SBxml*  bxml,  u8 sha20Bytes[20]);
		u64				(CALLTYPE *oss_bxmlaSha1Tag)						(SBxml*  bxml,  u8 sha20Bytes[20]);
		u64				(CALLTYPE *oss_bxmlaSha1Data)						(SBxml*  bxml,  u8 sha20Bytes[20]);

		u32				(CALLTYPE *oss_bxmlaFindAndGetString)				(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, SDatum* tsResult, bool* tlError);
		u32				(CALLTYPE *oss_bxmlaFindAndGetU32)					(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		u64				(CALLTYPE *oss_bxmlaFindAndGetU64)					(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		bool			(CALLTYPE *oss_bxmlaFindAndGetBool)					(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		f32				(CALLTYPE *oss_bxmlaFindAndGetF32)					(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		f64				(CALLTYPE *oss_bxmlaFindAndGetF64)					(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);

		u32				(CALLTYPE *oss_bxmlaGetString)						(SBxmla* bxmla, SDatum* tsResult, bool* tlError);
		u32				(CALLTYPE *oss_bxmlaGetU32)							(SBxmla* bxmla, bool* tlError);
		u64				(CALLTYPE *oss_bxmlaGetU64)							(SBxmla* bxmla, bool* tlError);
		bool			(CALLTYPE *oss_bxmlaGetBool)						(SBxmla* bxmla, bool* tlError);
		f32				(CALLTYPE *oss_bxmlaGetF32)							(SBxmla* bxmla, bool* tlError);
		f64				(CALLTYPE *oss_bxmlaGetF64)							(SBxmla* bxmla, bool* tlError);

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

		SBxmla*			(CALLTYPE *oss_bxmlFindAttribute)					(SBxml* bxml, s8* tcAttributeName, u32 tnAttributeNameLength, u32 tnInstance);
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

		(void *)&oss_plugin_registerFunction,								(void *)cgcOssPluginRegisterFunction,
		(void *)&oss_plugin_unregisterFunction,								(void *)cgcOssPluginUnregisterFunction,

		(void *)&oss_getSystemInfo,											(void *)cgcOssGetSystemInfo,
		(void *)&oss_sleep,													(void *)cgcOssSleep,
		(void *)&oss_dateTimeGet,											(void *)cgcOssDateTimeGet,
		(void *)&oss_changePathnameExtension,								(void *)cgcOssChangePathnameExtension,
		(void *)&oss_validateFilenameCharacter,								(void *)cgcOssValidateFilenameCharacter,
		(void *)&oss_getNextUniqueId,										(void *)cgcOssGetNextUniqueId,
		(void *)&oss_getNextMessage,										(void *)cgcOssGetNextN_UniqueIds,

		(void *)&oss_deleteScreen,											(void *)cgcOssDeleteScreen,
		(void *)&oss_deleteCanvas,											(void *)cgcOssDeleteCanvas,

		(void *)&oss_createScreenAndVisibleWindow,							(void *)cgcOssCreateScreenAndVisibleWindow,
		(void *)&oss_createRegionForScreen,									(void *)cgcOssCreateRegionForScreen,
		(void *)&oss_createCanvasForScreen,									(void *)cgcOssCreateCanvasForScreen,
		(void *)&oss_createCanvas,											(void *)cgcOssCreateCanvas,
		(void *)&oss_createRegion,											(void *)cgcOssCreateRegion,
		(void *)&oss_createRegionAndCanvas,									(void *)cgcOssCreateRegionAndCanvas,
		(void *)&oss_createFontHandle,										(void *)cgcOssCreateFontHandle,

		(void *)&oss_screenRefresh,											(void *)cgcOssScreenRefresh,
		(void *)&oss_screenSetFocus,										(void *)cgcOssScreenSetFocus,

		(void *)&oss_regionDuplicate,										(void *)cgcOssRegionDuplicate,
		(void *)&oss_regionDefaultPaint,									(void *)cgcOssRegionDefaultPaint,
		(void *)&oss_regionRefresh,											(void *)cgcOssRegionRefresh,

		(void *)&oss_canvasDrawFixedPointText,								(void *)cgcOssCanvasWriteFixedPointText,
		(void *)&oss_canvasDrawText,										(void *)cgcOssCanvasDrawText,
		(void *)&oss_canvasFrameRect,										(void *)cgcOssCanvasFrameRect,
		(void *)&oss_canvasFillRect,										(void *)cgcOssCanvasFillRect,
		(void *)&oss_canvasLine,											(void *)cgcOssCanvasLine,
		(void *)&oss_canvasArc,												(void *)cgcOssCanvasArc,
		(void *)&oss_canvasExtract,											(void *)cgcOssCanvasExtract,
		(void *)&oss_canvasColorize,										(void *)cgcOssCanvasColorize,
		(void *)&oss_canvasGrayscale,										(void *)cgcOssCanvasGrayscale,
		(void *)&oss_canvasGradient,										(void *)cgcOssCanvasGradient,
		(void *)&oss_canvasBitBlt,											(void *)cgcOssCanvasBitBlt,
		(void *)&oss_canvasScale,											(void *)cgcOssCanvasScale,

		(void *)&oss_caskDefineStandard,									(void *)cgcOssCaskDefineStandard,
		(void *)&oss_caskDefineEncompassingRectangle,						(void *)cgcOssCaskDefineEncompassingRectangle,
		(void *)&oss_caskDefineUpRectangle,									(void *)cgcOssCaskDefineUpRectangle,
		(void *)&oss_caskDefineDownRectangle,								(void *)cgcOssCaskDefineDownRectangle,
		(void *)&oss_caskSetPipByValues,									(void *)cgcOssCaskSetPipByValues,
		(void *)&oss_caskSetPipByStruct,									(void *)cgcOssCaskSetPipByStruct,
		(void *)&oss_caskCreate,											(void *)cgcOssCaskCreate,
		(void *)&oss_caskRefresh,											(void *)cgcOssCaskRefresh,

		(void *)&oss_screenMouseSetEventCallback,							(void *)cgcOssScreenMouseSetEventCallback,
		(void *)&oss_screenMouseRemoveEventCallback,						(void *)cgcOssScreenMouseRemoveEventCallback,
		(void *)&oss_screenMouseGetEventCallbacksList,						(void *)cgcOssScreenMouseGetEventCallbacksList,
		(void *)&oss_screenKeyboardSetEventCallback,						(void *)cgcOssScreenKeyboardSetEventCallback,
		(void *)&oss_screenKeyboardRemoveEventCallback,						(void *)cgcOssScreenKeyboardRemoveEventCallback,
		(void *)&oss_screenKeyboardGetEventCallbacksList,					(void *)cgcOssScreenKeyboardGetEventCallbacksList,

		(void *)&oss_canvasScale,											(void *)cgcOssCanvasScale,
		(void *)&oss_bitmapLoadFromDisk,									(void *)cgcOssLoadBitmapFromDisk,
		(void *)&oss_bitmapSaveToDisk,										(void *)cgcOssSaveBitmapToDisk,

		(void *)&oss_systemCreateFont,										(void *)cgcOssCreateSystemFont,
		(void *)&oss_systemCreateBitmap,									(void *)cgcOssCreateSystemBitmap,
		(void *)&oss_systemFindFontByHandle,								(void *)cgcOssFindSystemFontByHandle,

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
		(void*)&oss_datumSet,												(void*)cgcOssDatumSet,
		(void*)&oss_datumSet2,												(void*)cgcOssDatum2Set,
		(void*)&oss_datumDuplicate,											(void*)cgcOssDatumDuplicate,
		(void*)&oss_datum2Duplicate,										(void*)cgcOssDatum2Duplicate,
		(void*)&oss_datumDelete,											(void*)cgcOssDatumDelete,
		(void*)&oss_datum2Delete,											(void*)cgcOssDatum2Delete,
		(void*)&oss_datum2SetNullString,									(void*)cgcOssDatum2SetNullString,

		(void*)&oss_copyUpToShortestString,									(void*)cgcOssCopyUpToShortestString,
		(void*)&oss_wildcardMatchDatum,										(void*)cgcOssWildcardMatchDatum,
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
		(void*)&oss_ll_delete,												(void*)cgcOssLlDelete,
		(void*)&oss_ll_deleteWithCallback,									(void*)cgcOssLlDeleteWithCallback,
		(void*)&oss_ll_insert,												(void*)cgcOssLlInsert,
		(void*)&oss_ll_orphanize,											(void*)cgcOssLlOrphanize,
		(void*)&oss_ll_deleteChain,											(void*)cgcOssLlDeleteChain,
		(void*)&oss_ll_deleteChainWithCallback,								(void*)cgcOssLlDeleteChainWithCallback,
		(void*)&oss_ll_iterateViaCallback,									(void*)cgcOssLlIterateViaCallback,
		(void*)&oss_ll_iterateBackwardViaCallback,							(void*)cgcOssLlIterateBackwardViaCallback,
		(void*)&oss_ll_getFirstNode,										(void*)cgcOssLlGetFirstNode,
		(void*)&oss_ll_getLastNode,											(void*)cgcOssLlGetLastNode,

		(void*)&oss_ll4_create,												(void*)cgcOssLl4Create,
		(void*)&oss_ll4_createChain,										(void*)cgcOssLl4CreateChain,
		(void*)&oss_ll4_delete,												(void*)cgcOssLl4Delete,
		(void*)&oss_ll4_orphanize,											(void*)cgcOssLl4OrphanizeAsNode,
		(void*)&oss_ll4_insertNorthSouth,									(void*)cgcOssLl4InsertAsNodeNorthSouth,
		(void*)&oss_ll4_insertWestEast,										(void*)cgcOssLl4InsertAsNodeEastWest,
		(void*)&oss_ll4_deleteChain,										(void*)cgcOssLl4DeleteChain,
		(void*)&oss_ll4_deleteChainWithCallback,							(void*)cgcOssLl4DeleteChainWithCallback,
		(void*)&oss_ll4_iterateViaCallback,									(void*)cgcOssLl4IterateViaCallback,
		(void*)&oss_ll4_getLastNode,										(void*)cgcOssLl4GetLastNode,

		(void*)&oss_ll4bxml_orphanize,										(void*)cgcOssLl4BxmlOrphanize,
		(void*)&oss_ll4bxml_insert,											(void*)cgcOssLl4BxmlInsert,
		(void*)&oss_ll4bxml_insertAsChild,									(void*)cgcOssLl4BxmlInsertAsChild,
		(void*)&oss_ll4bxml_insertAsChildRegarding,							(void*)cgcOssLl4BxmlInsertAsChildRegarding,

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
		(void*)&oss_SEChain_deleteAsPtrBlock,								(void*)cgcOssSEChainDeleteAsPtrBlock,
		(void*)&oss_SEChain_deleteFrom,										(void*)cgcOssSEChainDeleteFrom,
		(void*)&oss_SEChain_deleteFromAfterCallback,						(void*)cgcOssSEChainDeleteFromAfterCallback,

		(void*)&oss_SEChain_allocateAdditionalMasterSlots,					(void*)cgcOssSEChainAllocateAdditionalMasterSlots,
		(void*)&oss_SEChain_searchByUniqueId,								(void*)cgcOssSEChainSearchByUniqueId,
		(void*)&oss_SEChain_searchByCallback,								(void*)cgcOssSEChainSearchByCallback,
		(void*)&oss_SEChain_iterateThroughForCallback,						(void*)cgcOssSEChainIterateThroughForCallback,
		(void*)&oss_SEChain_validate,										(void*)cgcOssSEChainValidate,

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

		(void *)&oss_builderCreateAndInitialize,						(void *)cgcOssBuildBufferCreateAndInitialize,
		(void *)&oss_builderAppendText,									(void *)cgcOssBuildBufferAppendText,
		(void *)&oss_builderSetSize,									(void *)cgcOssBuildBufferSetSize,
		(void *)&oss_builderFreeAndRelease,								(void *)cgcOssBuildBufferFreeAndRelease,

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

		(void *)&oss_bxmlaFindAndGetString,									(void *)cgcOssBxmlAttributeFindAndGetString,
		(void *)&oss_bxmlaFindAndGetU32,									(void *)cgcOssBxmlAttributeFindAndGetU32,
		(void *)&oss_bxmlaFindAndGetU64,									(void *)cgcOssBxmlAttributeFindAndGetU64,
		(void *)&oss_bxmlaFindAndGetBool,									(void *)cgcOssBxmlAttributeFindAndGetUBool,
		(void *)&oss_bxmlaFindAndGetF32,									(void *)cgcOssBxmlAttributeFindAndGetF32,
		(void *)&oss_bxmlaFindAndGetF64,									(void *)cgcOssBxmlAttributeFindAndGetF64,

		(void *)&oss_bxmlaGetString,										(void *)cgcOssBxmlAttributeGetString,
		(void *)&oss_bxmlaGetU32,											(void *)cgcOssBxmlAttributeGetU32,
		(void *)&oss_bxmlaGetU64,											(void *)cgcOssBxmlAttributeGetU64,
		(void *)&oss_bxmlaGetBool,											(void *)cgcOssBxmlAttributeGetUBool,
		(void *)&oss_bxmlaGetF32,											(void *)cgcOssBxmlAttributeGetF32,
		(void *)&oss_bxmlaGetF64,											(void *)cgcOssBxmlAttributeGetF64,

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

		(void *)&oss_bxmlFindAttribute,										(void *)cgcOssBxmlFindAttribute,
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

		(void *)&oss_screenCreateTemplate,									(void *)cgcOssCreateScreenTemplate,
		(void *)&oss_screenComputeMonitorCoordinates,								(void *)cgcOssComputeMonitorCoordinates,
		(void *)&oss_screenEnumerateMonitors,										(void *)cgcOssEnumerateMonitors,
		(void *)&oss_screenGetDimensions,									(void *)cgcOssGetScreenDimensions,

		(void *)&oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb,				(void *)cgcOssLowLevelBitBltCanvasBgraOntoOssRgb,
		(void *)&oss_lowLevel_bitBlt_ossRgb_onto_canvasBgra,				(void *)cgcOssLowLevelBitBltOssRgbOntoCanvasBgra,

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
				// Note:  By design, this should never happen.  It is the result of a programming error.
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

