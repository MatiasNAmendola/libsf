//////////
//
// /libsf/vvm/core/common/common_vvm.h
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     Feb.25.2014 - Development on 0.70 begins
//     Nov.07.2012 - 0.60 development begins
//     Oct.23.2012 - PBL v1.0 license included directly in source files.
//     Oct.23.2012 - Initial creation
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
//
// Constants used by the VVM
//
//////
	// Events it responds to
	const u32		_VVM_REGION_TAB_STOP							= 0x00000001;
	const u32		_VVM_REGION_KEYBOARD_INPUT						= 0x00000002;
	const u32		_VVM_REGION_MOUSE_INPUT							= 0x00000004;
	const u32		_VVM_REGION_STANDARD_INPUT						= _VVM_REGION_TAB_STOP | _VVM_REGION_KEYBOARD_INPUT | _VVM_REGION_MOUSE_INPUT;
	// Types of default input
	const u32		_VVM_REGION_EDITBOX								= 0x00000100;
	const u32		_VVM_REGION_BUTTON								= 0x00000200;
	const u32		_VVM_REGION_IMAGE								= 0x00000400;
	const u32		_VVM_REGION_LABEL								= 0x00000800;
	const u32		_VVM_REGION_CHECKBOX							= 0x00001000;
	const u32		_VVM_REGION_RECTANGLE							= 0x00002000;
	const u32		_VVM_REGION_CUSTOM_CANVAS						= 0x40000000;
	const u32		_VVM_REGION_CUSTOM_NO_CANVAS					= 0x80000000;
	// Only used internally:
	const u32		_VVM_REGION_I_CANVAS_MASK						= 0x7fffff00;		// Masks off any region inputs that have an associated canvas

	// These correlate to Visual FreePro definitions for text alignment
	const u32		_VVM_ALIGN_LEFT									= 1;
	const u32		_VVM_ALIGN_RIGHT								= 2;
	const u32		_VVM_ALIGN_CENTER								= 3;

	// Variable types
	const u32		_VVM_VARIABLE_TYPE_UNUSED						= 1;
	const u32		_VVM_VARIABLE_TYPE_U32							= 2;
	const u32		_VVM_VARIABLE_TYPE_U64							= 3;
	const u32		_VVM_VARIABLE_TYPE_S32							= 4;
	const u32		_VVM_VARIABLE_TYPE_S64							= 5;
	const u32		_VVM_VARIABLE_TYPE_F32							= 6;
	const u32		_VVM_VARIABLE_TYPE_F64							= 7;
	const u32		_VVM_VARIABLE_TYPE_ASCII						= 8;
	const u32		_VVM_VARIABLE_TYPE_UNICODE						= 9;
	// Extended format variables
	const u32		_VVM_VARIABLE_TYPE_BI							= 100;			// Big integer
	const u32		_VVM_VARIABLE_TYPE_BFP							= 101;			// Big floating point
	// Other variable types will be defined

	// Snippet types (see vvm_structs.h)
	const u32		_VVM_SNIP										= 1;			// Indicates a snippet
	const u32		_VVM_DSNIP										= 2;			// Indicates any of the 3 forms
	const u32		_VVM_DSNIP__RUNTIME_LOADED						= 10;			// An BXML file loaded at runtime
	const u32		_VVM_DSNIP__DLL									= 11;			// Access to a DLL through protocol
	const u32		_VVM_DSNIP__EDIT_AND_CONTINUE					= 12;			// Edit-and-continue, compiled VVM code replacing a previous snippet or non-DLL-based dynamic snippet

	// Identifiers for snippet components, for view in the debugger while hovering over source code
// TODO:  for the compiler + debugger source code line components, this will require some thought, about what types of data items can be viewed from the debugger, as is stored in the PDB
	const u32		_VVM_COMP_TYPE_SCREEN							= 0;
	const u32		_VVM_COMP_TYPE_CANVAS							= 0;
	const u32		_VVM_COMP_TYPE_REGION							= 0;
	const u32		_VVM_COMP_TYPE_GLOBAL							= 0;
	const u32		_VVM_COMP_TYPE_GLOBAL_TIMER						= 0;
//	const u32		_VVM_COMP_TYPE_ SCREEN							= 0;
//	const u32		_VVM_COMP_TYPE_ SCREEN							= 0;

	// Constants used (arbitrarily, but per some modicum of reason) for the VVM's engine
	const u32		_VVM_PARAMS_ALLOCATION_SIZE						= 16;	// The logic is: if you pass more than 16 items, you probably should do it different (pass an allocated object)
	const u32		_VVM_RETURNS_ALLOCATION_SIZE					= 16;	// The logic is: really?  Returning more than 16 items?  Seriously? :-)


//////////
// Variable types
//////
	const u32		_VVM_VARIABLE_U8								= 1;			// unsigned 8-bit
	const u32		_VVM_VARIABLE_U16								= 2;			// unsigned 16-bit
	const u32		_VVM_VARIABLE_U32								= 3;			// unsigned 32-bit
	const u32		_VVM_VARIABLE_U64								= 4;			// unsigned 64-bit
	const u32		_VVM_VARIABLE_S8								= 5;			// unsigned 8-bit
	const u32		_VVM_VARIABLE_S16								= 6;			// unsigned 16-bit
	const u32		_VVM_VARIABLE_S32								= 7;			// unsigned 32-bit
	const u32		_VVM_VARIABLE_S64								= 8;			// unsigned 64-bit
	const u32		_VVM_VARIABLE_ASCII								= 9;			// ASCII data of the indicated length
	const u32		_VVM_VARIABLE_UNICODE							= 10;			// UNICODE data of the indicated length (in bytes, not in characters)




#ifndef _VVM_COMPILING
	//////////
	//
	// The following variables and function define the interface to VVM.
	// By including this file and calling iLoadVvmFunctions() from the vvm_firstCallback() callback
	// in the DLL ... all things become accessible.
	//
	// Note:  To directly access the OS-specific code, use common_vvmoss.h.
	//
	//////
		// VVM interface functions
		// See devhelp.txt.  Duplicate changes here in VDebug.h, vvm.cpp, vvm_v1.cpp, vvm_defs.h, and vo_class.h.
		const s8		cgcVvmV1FirstCallback[]							= "vvm_firstCallback";
		const s8		cgcVvmV1BootstrapInitialization[]				= "vvm_bootstrapInitialization";
		const s8		cgcVvmV1StartTheVvm[]							= "vvm_startTheVvm";
		const s8		cgcVvmV1GetVersion[]							= "vvm_getVersion";
		const s8		cgcVvmV1GetLanguage[]							= "vvm_getLanguage";
		const s8		cgcVvmV1LoadResourceAsciiText[]					= "vvm_loadResourceAsciiText";
		const s8		cgcVvmV1ResourcePrintf[]						= "vvm_resourcePrintf";
		const s8		cgcVvmV1RequestUniqueId[]						= "vvm_requestUniqueID";
		const s8		cgcVvmV1Connect[]								= "vvm_connect";
		const s8		cgcVvmV1ConnectRemote[]							= "vvm_connectRemote";
		const s8		cgcVvmV1GetNextUniqueId[]						= "vvm_getNextUniqueId";

		const s8		cgcVvmV1CopyProgramList[]						= "vvm_copyProgramList";
		const s8		cgcVvmV1ProgramCopyScreensList[]				= "vvm_programCopyScreensList";
		const s8		cgcVvmV1ProgramCopyGlobalsList[]				= "vvm_programCopyGlobalsList";
		const s8		cgcVvmV1ProgramCopySnippetsList[]				= "vvm_programCopySnippetsList";
		const s8		cgcVvmV1ProgramCopyDynamicSnippetsList[]		= "vvm_programCopyDynamicSnippetsList";
		const s8		cgcVvmV1ProgramCopyTimersList[]					= "vvm_programCopyTimersList";
		const s8		cgcVvmV1ProgramCopyThreadsList[]				= "vvm_programCopyThreadsList";

		const s8		cgcVvmV1ProgramPause[]							= "vvm_programPause";
		const s8		cgcVvmV1ProgramResume[]							= "vvm_programResume";
		const s8		cgcVvmV1ProgramTerminate[]						= "vvm_programTerminate";
		const s8		cgcVvmV1ThreadPause[]							= "vvm_threadPause";
		const s8		cgcVvmV1ThreadResume[]							= "vvm_threadResume";
		const s8		cgcVvmV1ThreadTerminate[]						= "vvm_threadTerminate";
		const s8		cgcVvmV1TerminateVvm[]							= "vvm_terminateVvm";

		const s8		cgcVvmV1GetBreakpointList[]						= "vvm_getBreakpointList";
		const s8		cgcVvmV1BreakpointSet[]							= "vvm_breakpointSet";
		const s8		cgcVvmV1BreakpointClear[]						= "vvm_breakpointClear";

		const s8		cgcVvmV1CopyProgram[]							= "vvm_copyProgram";
		const s8		cgcVvmV1CopyThread[]							= "vvm_copyThread";
		const s8		cgcVvmV1CopyStack[]								= "vvm_copyStack";
		const s8		cgcVvmV1CopyRegisters[]							= "vvm_copyRegisters";
		const s8		cgcVvmV1CopyGlobal[]							= "vvm_copyGlobal";
		const s8		cgcVvmV1CopyTimer[]								= "vvm_copyTimer";
		const s8		cgcVvmV1CopyScreen[]							= "vvm_copyScreen";
		const s8		cgcVvmV1CopyCanvas[]							= "vvm_copyCanvas";

		const s8		cgcVvmV1CopySnippetTS[]							= "vvm_copySnippetTS";
		const s8		cgcVvmV1CopySnippetParent[]						= "vvm_copySnippetParent";
		const s8		cgcVvmV1CopySnippetSS[]							= "vvm_copySnippetSS";
		const s8		cgcVvmV1CopyDynamicSnippet[]					= "vvm_copyDynamicSnippet";

		const s8		cgcVvmV1SnippetCompile[]						= "vvm_snippetCompile";
		const s8		cgcVvmV1SnippetCompileLine[]					= "vvm_snippetCompileLine";
		const s8		cgcVvmV1DynSnipCompileLine[]					= "vvm_dynSnipCompileLine";
		const s8		cgcVvmV1SnippetDelete[]							= "vvm_snippetDelete";
		const s8		cgcVvmV1SnippetUpdate[]							= "vvm_snippetUpdate";
		const s8		cgcVvmV1SnippetAppend[]							= "vvm_snippetAppend";
		const s8		cgcVvmV1DynamicSnippetDelete[]					= "vvm_dynamicSnippetDelete";
		const s8		cgcVvmV1DynamicSnippetUpdate[]					= "vvm_dynamicSnippetUpdate";
		const s8		cgcVvmV1DynamicSnippetAppend[]					= "vvm_dynamicSnippetAppend";
		const s8		cgcVvmV1FlushChangesToBxml[]					= "vvm_flushChangesToBxml";

		const s8		cgcVvmV1CreateThread[]							= "vvm_createThread";
		const s8		cgcVvmV1MessageBox[]							= "vvm_messageBox";

		const s8		cgcVvmV1BuildBufferCreateAndInitialize[]		= "vvm_builderCreateAndInitialize";
		const s8		cgcVvmV1BuildBufferAppendData[]					= "vvm_builderAppendData";
		const s8		cgcVvmV1BuilderAllocateBytes[]					= "vvm_builderAllocateBytes";
		const s8		cgcVvmV1BuildBufferSetSize[]					= "vvm_builderSetSize";
		const s8		cgcVvmV1BuildBufferFreeAndRelease[]				= "vvm_builderFreeAndRelease";
		const s8		cgcVvmV1BuilderWriteOutAsciiFile[]				= "vvm_builderAsciiWriteOutFile";

		const s8		cgcVvmV1Sha1ComputeSha1[]						= "vvm_sha1ComputeSha1";
		const s8		cgcVvmV1Sha1ComputeSha1As64Bit[]				= "vvm_sha1ComputeSha1As64Bit";
		const s8		cgcVvmV1Sha1ComputeSha1As32Bit[]				= "vvm_sha1ComputeSha1As32Bit";
		const s8		cgcVvmV1Sha1ComputeSha1AsHex[]					= "vvm_sha1ComputeSha1AsHex";
		const s8		cgcVvmV1Sha1ConvertHexToSha1[]					= "vvm_sha1ConvertHexToSha1";
		const s8		cgcVvmV1Sha1ConvertSha1ToHex[]					= "vvm_sha1ConvertSha1ToHex";
		const s8		cgcVvmV1Sha1ComputeSha1_Start[]					= "vvm_sha1ComputeSha1_Start";
		const s8		cgcVvmV1Sha1ComputeSha1_ProcessThisData[]		= "vvm_sha1ComputeSha1_ProcessThisData";
		const s8		cgcVvmV1Sha1ComputeSha1_FinishAsSha1[]			= "vvm_sha1ComputeSha1_FinishAsSha1";
		const s8		cgcVvmV1Sha1ComputeSha1_FinishAsHex[]			= "vvm_sha1ComputeSha1_FinishAsHex";
		const s8		cgcVvmV1Sha1Compute64BitFromSha1[]				= "vvm_sha1Compute64BitFromSha1";
		const s8		cgcVvmV1Sha1Compute32BitFromSha1[]				= "vvm_sha1Compute32BitFromSha1";
		const s8		cgcVvmV1Sha1Compare[]							= "vvm_sha1Compare";

		const s8		cgcVvmV1BxmlLoad[]								= "vvm_bxmlLoad";
		const s8		cgcVvmV1BxmlLoadFromBuffer[]					= "vvm_bxmlLoadFromBuffer";
		const s8		cgcVvmV1BxmlSave[]								= "vvm_bxmlSave";
		const s8		cgcVvmV1BxmlSaveToBuffer[]						= "vvm_bxmlSaveToBuffer";

		const s8		cgcVvmV1BxmlAttributeCreate[]					= "vvm_bxmlaCreate";
		const s8		cgcVvmV1BxmlAttributeSetName[]					= "vvm_bxmlaSetName";
		const s8		cgcVvmV1BxmlAttributeSetData[]					= "vvm_bxmlaSetData";
		const s8		cgcVvmV1BxmlAttributeSetTotalLength[]			= "vvm_bxmlaSetTotalLength";
		const s8		cgcVvmV1BxmlAttributeDelete[]					= "vvm_bxmlaDelete";
		const s8		cgcVvmV1BxmlAttributeInsert[]					= "vvm_bxmlaInsert";
		const s8		cgcVvmV1BxmlAttributeInsertExisting[]			= "vvm_bxmlaInsertExisting";
		const s8		cgcVvmV1BxmlAttributeCopy[]						= "vvm_bxmlaCopy";
		const s8		cgcVvmV1BxmlAttributeCopyAs[]					= "vvm_bxmlaCopyAs";
		const s8		cgcVvmV1BxmlAttributeSha1One[]					= "vvm_bxmlaSha1One";
		const s8		cgcVvmV1BxmlAttributeSha1[]						= "vvm_bxmlaSha1";
		const s8		cgcVvmV1BxmlAttributeSha1Tag[]					= "vvm_bxmlaSha1Tag";
		const s8		cgcVvmV1BxmlAttributeSha1Data[]					= "vvm_bxmlaSha1Data";

		const s8		cgcVvmV1BxmlAttributeFindAndGetString[]			= "vvm_bxmlaFindAndGetString";
		const s8		cgcVvmV1BxmlAttributeFindAndGetU32[]			= "vvm_bxmlaFindAndGetU32";
		const s8		cgcVvmV1BxmlAttributeFindAndGetU64[]			= "vvm_bxmlaFindAndGetU64";
		const s8		cgcVvmV1BxmlAttributeFindAndGetUBool[]			= "vvm_bxmlaFindAndGetBool";
		const s8		cgcVvmV1BxmlAttributeFindAndGetF32[]			= "vvm_bxmlaFindAndGetF32";
		const s8		cgcVvmV1BxmlAttributeFindAndGetF64[]			= "vvm_bxmlaFindAndGetF64";

		const s8		cgcVvmV1BxmlAttributeGetString[]				= "vvm_bxmlaGetString";
		const s8		cgcVvmV1BxmlAttributeGetU32[]					= "vvm_bxmlaGetU32";
		const s8		cgcVvmV1BxmlAttributeGetU64[]					= "vvm_bxmlaGetU64";
		const s8		cgcVvmV1BxmlAttributeGetUBool[]					= "vvm_bxmlaGetBool";
		const s8		cgcVvmV1BxmlAttributeGetF32[]					= "vvm_bxmlaGetF32";
		const s8		cgcVvmV1BxmlAttributeGetF64[]					= "vvm_bxmlaGetF64";

		const s8		cgcVvmV1BxmlAttributeGetNext[]					= "vvm_bxmlaGetNext";
		const s8		cgcVvmV1BxmlAttributeGetPrev[]					= "vvm_bxmlaGetPrev";

		const s8		cgcVvmV1BxmlNodeCreate[]						= "vvm_bxmlNodeCreate";
		const s8		cgcVvmV1BxmlNodeSetName[]						= "vvm_bxmlNodeSetName";
		const s8		cgcVvmV1BxmlNodeDelete[]						= "vvm_bxmlNodeDelete";
		const s8		cgcVvmV1BxmlNodeInsert[]						= "vvm_bxmlNodeInsert";
		const s8		cgcVvmV1BxmlNodeInsertAsChild[]					= "vvm_bxmlNodeInsertAsChild";
		const s8		cgcVvmV1BxmlNodeInsertAsChildAfter[]			= "vvm_bxmlNodeInsertAsChildAfter";
		const s8		cgcVvmV1BxmlNodeSha1[]							= "vvm_bxmlNodeSha1";
		const s8		cgcVvmV1BxmlNodeSha1Tag[]						= "vvm_bxmlNodeSha1Tag";
		const s8		cgcVvmV1BxmlNodeSha1Data[]						= "vvm_bxmlNodeSha1Data";

		const s8		cgcVvmV1BxmlNodeCopy[]							= "vvm_bxmlNodeCopy";
		const s8		cgcVvmV1BxmlNodeCopyAs[]						= "vvm_bxmlNodeCopyAs";

		const s8		cgcVvmV1BxmlGetNext[]							= "vvm_bxmlNodeGetNext";
		const s8		cgcVvmV1BxmlGetPrev[]							= "vvm_bxmlNodeGetPrev";
		const s8		cgcVvmV1BxmlGetParent[]							= "vvm_bxmlNodeGetParent";
		const s8		cgcVvmV1BxmlGetFirstChild[]						= "vvm_bxmlNodeGetFirstChild";
		const s8		cgcVvmV1BxmlGetFirstAttribute[]					= "vvm_bxmlNodeGetFirstAttribute";

		const s8		cgcVvmV1BxmlFindAttribute[]						= "vvm_bxmlFindAttribute";
		const s8		cgcVvmV1BxmlFindFirst[]							= "vvm_bxmlFindFirst";
		const s8		cgcVvmV1BxmlFindContinue[]						= "vvm_bxmlFindContinue";
		const s8		cgcVvmV1BxmlFindAllAsStartEndLists[]			= "vvm_bxmlFindAllAsStartEndLists";

		const s8		cgcVvmV1BxmlDatFindFirst[]						= "vvm_bxmlDataFindFirst";
		const s8		cgcVvmV1BxmlDataFindContinue[]					= "vvm_bxmlDataFindContinue";
		const s8		cgcVvmV1BxmlDataFindAllAsStartEndList[]			= "vvm_bxmlDataFindAllAsStartEndList";

		const s8		cgcVvmV1BxmlGetLastError[]						= "vvm_bxmlGetLastError";

		const s8		cgcVvmV1DuplicateString[]						= "vvm_duplicateString";
		const s8		cgcVvmV1DuplicateUnicodeString[]				= "vvm_duplicateUnicodeString";
		const s8		cgcVvmV1DatumSet[]								= "vvm_datumSet";
		const s8		cgcVvmV1Datum2Set[]								= "vvm_datum2Set";
		const s8		cgcVvmV1DatumDuplicate[]						= "vvm_datumDuplicate";
		const s8		cgcVvmV1Datum2Duplicate[]						= "vvm_datum2Duplicate";
		const s8		cgcVvmV1DatumDelete[]							= "vvm_datumDelete";
		const s8		cgcVvmV1Datum2Delete[]							= "vvm_datum2Delete";
		const s8		cgcVvmV1Datum2SetNullString[]					= "vvm_datum2SetNullString";

		const s8		cgcVvmV1CopyUpToShortestString[]				= "vvm_copyUpToShortestString";
		const s8		cgcVvmV1WildcardMatchDatum[]					= "vvm_wildcardMatchDatum";
		const s8		cgcVvmV1WildcardMatch[]							= "vvm_wildcardMatch";
		const s8		cgcVvmV1AsciiToUnicode[]						= "vvm_asciiToUnicode";
		const s8		cgcVvmV1UnicodeToAscii[]						= "vvm_unicodeToAscii";
		const s8		cgcVvmV1AsciiToUnicodeChar[]					= "vvm_asciiToUnicodeChar";
		const s8		cgcVvmV1UnicodeToAsciiCharacter[]				= "vvm_unicodeToAsciiCharacter";
		const s8		cgcVvmV1ScanForwardUntilCharacterChanges[]		= "vvm_scanForwardUntilCharacterChanges";
		const s8		cgcVvmV1ScanForwardUntilCharacter[]				= "vvm_scanForwardUntilCharacter";
		const s8		cgcVvmV1UnicodeMemcmp[]							= "vvm_unicodeMemcmp";
		const s8		cgcVvmV1UnicodeMemicmp[]						= "vvm_unicodeMemicmp";
		const s8		cgcVvmV1UnicodeMemset[]							= "vvm_unicodeMemset";
		const s8		cgcVvmV1UpperCaseW[]							= "vvm_upperCaseW";
		const s8		cgcVvmV1LowerCaseW[]							= "vvm_lowerCaseW";
		const s8		cgcVvmV1Memset[]								= "vvm_memset";
		const s8		cgcVvmV1Memset4[]								= "vvm_memset4";
		const s8		cgcVvmV1Memcpy[]								= "vvm_memcpy";
		const s8		cgcVvmV1Memcmp[]								= "vvm_memcmp";
		const s8		cgcVvmV1Memicmp[]								= "vvm_memicmp";
		const s8		cgcVvmV1MemicmpTwoLengths[]						= "vvm_memicmpTwoLengths";
		const s8		cgcVvmV1MemicmpDatum[]							= "vvm_memicmpDatum";
		const s8		cgcVvmV1MemicmpDatum2[]							= "vvm_memicmpDatum2";
		const s8		cgcVvmV1MemicmpDatumDatum[]						= "vvm_memicmpDatumDatum";
		const s8		cgcVvmV1MemicmpDatum2Datum2[]					= "vvm_memicmpDatum2Datum2";
		const s8		cgcVvmV1DeriveRGBA[]							= "vvm_deriveRGBA";
		const s8		cgcVvmV1GetPredictableSequentialPattern[]		= "vvm_getPredictableSequentialPattern";

		const s8		cgcVvmV1LlAppendNode[]							= "vvm_ll_appendNode";
		const s8		cgcVvmV1LlCreateNode[]							= "vvm_ll_createNode";
		const s8		cgcVvmV1LlDeleteNode[]							= "vvm_ll_deleteNode";
		const s8		cgcVvmV1LlDeleteNodeWithCallback[]				= "vvm_ll_deleteNodeWithCallback";
		const s8		cgcVvmV1LlInsertNode[]							= "vvm_ll_insertNode";
		const s8		cgcVvmV1LlOrphanizeNode[]						= "vvm_ll_orphanizeNode";
		const s8		cgcVvmV1LlDeleteNodeChain[]						= "vvm_ll_deleteNodeChain";
		const s8		cgcVvmV1LlDeleteNodeChainWithCallback[]			= "vvm_ll_deleteNodeChainWithCallback";
		const s8		cgcVvmV1LlIterateViaCallback[]					= "vvm_ll_iterateViaCallback";
		const s8		cgcVvmV1LlIterateBackwardViaCallback[]			= "vvm_ll_iterateBackwardViaCallback";
		const s8		cgcVvmV1LlGetFirstNode[]						= "vvm_ll_getFirstNode";
		const s8		cgcVvmV1LlGetLastNode[]							= "vvm_ll_getLastNode";

		const s8		cgcVvmV1Ll4Create[]								= "vvm_ll4_create";
		const s8		cgcVvmV1Ll4CreateChain[]						= "vvm_ll4_createChain";
		const s8		cgcVvmV1Ll4Delete[]								= "vvm_ll4_delete";
		const s8		cgcVvmV1Ll4OrphanizeAsNode[]					= "vvm_ll4_orphanize";
		const s8		cgcVvmV1Ll4InsertAsNodeNorthSouth[]				= "vvm_ll4_insertNorthSouth";
		const s8		cgcVvmV1Ll4InsertAsNodeEastWest[]				= "vvm_ll4_insertWestEast";
		const s8		cgcVvmV1Ll4DeleteChain[]						= "vvm_ll4_deleteChain";
		const s8		cgcVvmV1Ll4DeleteChainWithCallback[]			= "vvm_ll4_deleteChainWithCallback";
		const s8		cgcVvmV1Ll4IterateViaCallback[]					= "vvm_ll4_iterateViaCallback";
		const s8		cgcVvmV1Ll4GetLastNode[]						= "vvm_ll4_getLastNode";

		const s8		cgcVvmV1Ll4BxmlInsert[]							= "vvm_ll4bxml_insert";
		const s8		cgcVvmV1Ll4BxmlOrphanize[]						= "vvm_ll4bxml_orphanize";
		const s8		cgcVvmV1Ll4BxmlInsertAsChild[]					= "vvm_ll4bxml_insertAsChild";
		const s8		cgcVvmV1Ll4BxmlInsertAsChildRegarding[]			= "vvm_ll4bxml_insertAsChildRegarding";

		const s8		cgcVvmV1SEChainPrepend[]						= "vvm_SEChain_prepend";
		const s8		cgcVvmV1SEChainAppend[]							= "vvm_SEChain_append";
		const s8		cgcVvmV1SEChainAppendRelativeToMember[]			= "vvm_SEChain_appendRelativeToMember";
		const s8		cgcVvmV1SEChainAppendExistingRelativeToMember[]	= "vvm_SEChain_appendExistingRelativeToMember";

		const s8		cgcVvmV1SEChainMigrateAll[]						= "vvm_SEChain_migrateAll";
		const s8		cgcVvmV1SEChainMigrateByPtr[]					= "vvm_SEChain_migrateByPtr";
		const s8		cgcVvmV1SEChainMigrateByNum[]					= "vvm_SEChain_migrateByNum";
		const s8		cgcVvmV1SEChainCompletelyMigrateSLLByPtr[]		= "vvm_SEChain_completelyMigrateSLLByPtr";
		const s8		cgcVvmV1SEChainCompletelyMigrateSLLByNum[]		= "vvm_SEChain_completelyMigrateSLLByNum";

		const s8		cgcVvmV1SEChainCountValids[]					= "vvm_SEChain_countValids";
		const s8		cgcVvmV1SEChainDelete[]							= "vvm_SEChain_delete";
		const s8		cgcVvmV1SEChainDeleteAsPtrBlock[]				= "vvm_SEChain_deleteAsPtrBlock";
		const s8		cgcVvmV1SEChainDeleteFrom[]						= "vvm_SEChain_deleteFrom";
		const s8		cgcVvmV1SEChainDeleteFromAfterCallback[]		= "vvm_SEChain_deleteFromAfterCallback";

		const s8		cgcVvmV1SEChainAllocateAdditionalMasterSlots[]	= "vvm_SEChain_allocateAdditionalMasterSlots";
		const s8		cgcVvmV1SEChainSearchByUniqueId[]				= "vvm_SEChain_searchByUniqueId";
		const s8		cgcVvmV1SEChainSearchByCallback[]				= "vvm_SEChain_searchByCallback";
		const s8		cgcVvmV1SEChainIterateThroughForCallback[]		= "vvm_SEChain_iterateThroughForCallback";
		const s8		cgcVvmV1SEChainValidate[]						= "vvm_SEChain_validate";

		const s8		cgcVvmV1SwapEndian[]							= "vvm_swapEndian";
		const s8		cgcVvmV1RGA2BGRA[]								= "vvm_RGBA2BGRA";
		const s8		cgcVvmV1AllocateAndNull[]						= "vvm_allocateAndNull";
		const s8		cgcVvmV1IsNeedleInHaystack[]					= "vvm_isNeedleInHaystack";
		const s8		cgcVvmV1IsNeedleInHaystackUnicode[]				= "vvm_isNeedleInHaystack_Unicode";
		const s8		cgcVvmV1CountConsecutiveAsciiNumericDigits[]	= "vvm_countConsecutiveAsciiNumericDigits";
		const s8		cgcVvmV1ConvertTextToU32[]						= "vvm_convertTextToU32";

		const s8		cgcVvmV1MathComputeTriangle[]					= "vvm_math_computeTriangle";
		const s8		cgcVvmV1MathComputeSquare[]						= "vvm_math_computeSquare";
		const s8		cgcVvmV1MathComputeLine[]						= "vvm_math_computeLine";
		const s8		cgcVvmV1MathSquareRotateAbout[]					= "vvm_math_squareRotateAbout";
		const s8		cgcVvmV1MathGetGravityOfThetaAndLeft[]			= "vvm_math_getGravityOfThetaAndLeft";
		const s8		cgcVvmV1MathGetGravity07FromDecoratedGravity[]	= "vvm_math_getGravity07FromDecoratedGravity";
		const s8		cgcVvmV1MathGetAreaOfSquareUsingPoP1P2[]		= "vvm_math_getAreaOfSquareUsing_po_p1_p2";
		const s8		cgcVvmV1MathGetNextAxisInterceptXY[]			= "vvm_math_getNextAxisInterceptXY";
		const s8		cgcVvmV1MathGetRelativeGravity[]				= "vvm_math_getGravityByRelativePosition";
		const s8		cgcVvmV1MathGetGravityInteger[]					= "vvm_math_getGravityInteger";
		const s8		cgcVvmV1MathFineAdjustGravityByTheta[]			= "vvm_math_fineAdjustGravityByTheta";
		const s8		cgcVvmV1MathAdjustTheta[]						= "vvm_math_adjustTheta";
		const s8		cgcVvmV1MathWithinDelta[]						= "vvm_math_withinDelta";
		const s8		cgcVvmV1MathWashFloans[]						= "vvm_math_washFloans";

		const s8		cgcVvmV1BezierInitialize[]						= "vvm_bezier_initialize";
		const s8		cgcVvmV1BezierSetByValues[]						= "vvm_bezier_setByValues";

		const s8		cgcVvmV1PolygonInitialize[]						= "vvm_polygon_initialize";
		const s8		cgcVvmV1PolygonSetByPolyLine[]					= "vvm_polygon_setByPolyLine";
		const s8		cgcVvmV1PolygonSetByValues[]					= "vvm_polygon_setByValues";
		const s8		cgcVvmV1PolygonReset[]							= "vvm_polygon_reset";
		const s8		cgcVvmV1PolygonFreeAndRelease[]					= "vvm_polygon_freeAndRelease";

		const s8		cgcVvmV1ScreenRefresh[]							= "vvm_screenRefresh";
		const s8		cgcVvmV1ScreenSetFocus[]						= "vvm_screenSetFocus";

		const s8		cgcVvmV1RegionDuplicate[]						= "vvm_regionDuplicate";
		const s8		cgcVvmV1RegionDefaultPaint[]					= "vvm_regionDefaultPaint";
		const s8		cgcVvmV1RegionRefresh[]							= "vvm_regionRefresh";

		const s8		cgcVvmV1CanvasWriteFixedPointText[]				= "vvm_canvasDrawFixedPointText";
		const s8		cgcVvmV1CanvasDrawText[]						= "vvm_canvasDrawText";
		const s8		cgcVvmV1CanvasFrameRect[]						= "vvm_canvasFrameRect";
		const s8		cgcVvmV1CanvasFillRect[]						= "vvm_canvasFillRect";
		const s8		cgcVvmV1CanvasLine[]							= "vvm_canvasLine";
		const s8		cgcVvmV1CanvasArc[]								= "vvm_canvasArc";
		const s8		cgcVvmV1CanvasBezier[]							= "vvm_canvasBezier";
		const s8		cgcVvmV1CanvasExtract[]							= "vvm_canvasExtract";
		const s8		cgcVvmV1CanvasColorize[]						= "vvm_canvasColorize";
		const s8		cgcVvmV1CanvasGrayscale[]						= "vvm_canvasGrayscale";
		const s8		cgcVvmV1CanvasGradient[]						= "vvm_canvasGradient";
		const s8		cgcVvmV1CanvasBitBlt[]							= "vvm_canvasBitBlt";
		const s8		cgcVvmV1CanvasScale[]							= "vvm_canvasScale";
		const s8		cgcVvmV1CanvasRotate[]							= "vvm_canvasRotate";
		const s8		cgcVvmV1CanvasRotateAbout[]						= "vvm_canvasRotateAbout";
		const s8		cgcVvmV1CanvasPolygon[]							= "vvm_canvasPolygon";

		const s8		cgcVvmV1CaskDefineStandard[]					= "vvm_caskDefineStandard";
		const s8		cgcVvmV1CaskDefineEncompassingRectangle[]		= "vvm_caskDefineEncompassingRectangle";
		const s8		cgcVvmV1CaskDefineUpRectangle[]					= "vvm_caskDefineUpRectangle";
		const s8		cgcVvmV1CaskDefineDownRectangle[]				= "vvm_caskDefineDownRectangle";
		const s8		cgcVvmV1CaskSetPipByValues[]					= "vvm_caskSetPipByValues";
		const s8		cgcVvmV1CaskSetPipByStruct[]					= "vvm_caskSetPipByStruct";
		const s8		cgcVvmV1CaskCreate[]							= "vvm_caskCreate";
		const s8		cgcVvmV1CaskRefresh[]							= "vvm_caskRefresh";

		const s8		cgcVvmV1iiCanvasPolygon[]						= "vvm_iiCanvasPolygon";
		const s8		cgcVvmV1iDeleteScaleCompute[]					= "vvm_iDeleteScaleCompute";
		const s8		cgcVvmV1iSkipWhiteSpaces[]						= "vvm_iSkipWhitespaces";
		const s8		cgcVvmV1iSkipToCarriageReturnLineFeed[]			= "vvm_iSkipToCarriageReturnLineFeed";
		const s8		cgcVvmV1iRegionDefaultPaintEditbox[]			= "vvm_iRegionDefaultPaintEditbox";
		const s8		cgcVvmV1iRegionDefaultPaintButton[]				= "vvm_iRegionDefaultPaintButton";
		const s8		cgcVvmV1iRegionDefaultPaintImage[]				= "vvm_iRegionDefaultPaintImage";
		const s8		cgcVvmV1iRegionDefaultPaintLabel[]				= "vvm_iRegionDefaultPaintLabel";
		const s8		cgcVvmV1iRegionDefaultPaintCheckbox[]			= "vvm_iRegionDefaultPaintCheckbox";
		const s8		cgcVvmV1iRegionDefaultPaintRectangle[]			= "vvm_iRegionDefaultPaintRectangle";
		const s8		cgcVvmV1iDrawFixedPoint[]						= "vvm_iDrawFixedPoint";
		const s8		cgcVvmV1iBitBltAll[]							= "vvm_iBitBltAll";
		const s8		cgcVvmV1iiBitBltAll_Opaque[]					= "vvm_iiBitBltAll_Opaque";
		const s8		cgcVvmV1iiBitBltAll_Alpha[]						= "vvm_iiBitBltAll_Alpha";
		const s8		cgcVvmV1iBitBltSection[]						= "vvm_iBitBltSection";
		const s8		cgcVvmV1iiBitBltSection_Opaque[]				= "vvm_iiBitBltSection_Opaque";
		const s8		cgcVvmV1iiBitBltSection_Alpha[]					= "vvm_iiBitBltSection_Alpha";
		const s8		cgcVvmV1iiGradient[]							= "vvm_iiGradient";
		const s8		cgcVvmV1iCanvasLine[]							= "vvm_iCanvasLine";

		const s8		cgcVvmV1EnableBreakpoints[]						= "vvm_enableBreakpoints";
		const s8		cgcVvmV1DisableBreakpoints[]					= "vvm_disableBreakpoints";


	//////////
	//
	// VVM function prototype definitions.  These must match the vvm_defs.h, as well as the
	// implementation in their associated vvm_*.cpp files.
	//
	// See devhelp.txt.
	//
	//////
		struct SProgram;
		struct SScreen;
		struct SCanvas;
		struct SRegion;
		struct SVariable;
		struct SSnipExec;
		struct SDynSnip;
		struct STimer;
		struct SThread;
		struct SBreakpoint;
		struct SBreakCond;
		struct SLine;
		struct SStack;
		struct SRegs; 
		struct SUpSnip;
		struct SUpLine;
		
		// Callbacks specific to version 1 (the VVM could be much newer than this debugger, but we require version 1)
		u64				(CALLTYPE *vvm_firstCallback)							(u32 tnDoNotLoadOptions);
		void			(CALLTYPE *vvm_bootstrapInitialization)					(void);
		s64				(CALLTYPE *vvm_startTheVvm)								(w16* tcCmdLine, bool* tlTestCasesOnly);
		const s8*		(CALLTYPE *vvm_getVersion)								(void);
		s8*				(CALLTYPE *vvm_getLanguage)								(u32* tnLength);
		s8*				(CALLTYPE *vvm_loadResourceAsciiText)					(u32 tnResourceNumber);
		void			(CALLTYPE *vvm_resourcePrintf)							(u32 tnResourceNumber);
		u64				(CALLTYPE *vvm_requestUniqueID)							(void);
		u64				(CALLTYPE *vvm_connect)									(u64 id, s8* tcPath);
		u64				(CALLTYPE *vvm_connectRemote)							(u64 id, s8* tcPath, s8* ipAddressOrMachineName);
		u64				(CALLTYPE *vvm_getNextUniqueId)							(void);

		// For information about the VM
		void			(CALLTYPE *vvm_copyProgramList)							(u64 id, SProgram** list, u32* count);
		void			(CALLTYPE *vvm_programCopyScreensList)					(u64 id, SProgram* program, SScreen**    list, u32* count);
		void			(CALLTYPE *vvm_programCopyGlobalsList)					(u64 id, SProgram* program, SVariable**  list, u32* count);
		void			(CALLTYPE *vvm_programCopySnippetsList)					(u64 id, SProgram* program, SSnipExec**   list, u32* count);
		void			(CALLTYPE *vvm_programCopyDynamicSnippetsList)			(u64 id, SProgram* program, SDynSnip**   list, u32* count);
		void			(CALLTYPE *vvm_programCopyTimersList)					(u64 id, SProgram* program, STimer**     list, u32* count);
		void			(CALLTYPE *vvm_programCopyThreadsList)					(u64 id, SProgram* program, SThread**    list, u32* count);

		// For controlling the VM
		u64				(CALLTYPE *vvm_programPause)							(u64 id, SProgram* program);
		u64				(CALLTYPE *vvm_programResume)							(u64 id, SProgram* program, bool singleStep);
		u64				(CALLTYPE *vvm_programTerminate)						(u64 id, SProgram* program);
		u64				(CALLTYPE *vvm_threadPause)								(u64 id, SThread* thread);
		u64				(CALLTYPE *vvm_threadResume)							(u64 id, SThread* thread, bool singleStep);
		u64				(CALLTYPE *vvm_threadTerminate)							(u64 id, SThread* thread);
		void			(CALLTYPE *vvm_terminateVvm)							(u64 id, bool tlPolitely);

		// Breakpoints
		void			(CALLTYPE *vvm_getBreakpointList)						(u64 id, SBreakpoint** root, u32* count);
		SBreakpoint*   	(CALLTYPE *vvm_breakpointSet)							(u64 id, SSnipExec* snippet, SLine* line, SBreakCond* bc, bool enable);
		bool			(CALLTYPE *vvm_breakpointClear)							(u64 id, SBreakpoint* bp);

		// For retrieving running content (thread may be temporarily paused upon request to retrieve data, and resumes after fill)
		bool			(CALLTYPE *vvm_copyProgram)								(u64 id, SProgram*   program,   SProgram**   copy);
		bool			(CALLTYPE *vvm_copyThread)								(u64 id, SThread*    thread,    SThread**    copy);
		bool			(CALLTYPE *vvm_copyStack)								(u64 id, SThread*    thread,    SStack**     copy);
		bool			(CALLTYPE *vvm_copyRegisters)							(u64 id, SThread*    thread,    SRegs** copy);
		bool			(CALLTYPE *vvm_copyGlobal)								(u64 id, SVariable*  global,    SVariable**  copy);
		bool			(CALLTYPE *vvm_copyTimer)								(u64 id, STimer*     timer,     STimer**     copy);
		bool			(CALLTYPE *vvm_copyScreen)								(u64 id, SScreen*    screen,    SScreen**    copyScreen,    SCanvas** copyCanvas);
		bool			(CALLTYPE *vvm_copyCanvas)								(u64 id, SCanvas*    canvas,    SScreen**    copy);

		// The following snippets are copied with original source code lines for each snippet
		bool			(CALLTYPE *vvm_copySnippetTS)							(u64 id, SThread*  snippet,    SSnipExec** copyS,   SDynSnip* copyDS,   bool* isDynSnip);
		bool			(CALLTYPE *vvm_copySnippetParent)						(u64 id, SSnipExec* snippet,    SSnipExec** copyS,   SDynSnip* copyDS,   bool* isDynSnip);
		bool			(CALLTYPE *vvm_copySnippetSS)							(u64 id, SSnipExec* snippet,    SSnipExec** copy);
		bool			(CALLTYPE *vvm_copyDynamicSnippet)						(u64 id, SDynSnip* dynSnippet, SDynSnip** copy);

		// For edit-and-continue (SUpSnip is SSnippet with _prevLine member, indicating the relationship of the old snippet code to the new snippet code)
		SUpSnip*		(CALLTYPE *vvm_snippetCompile)							(u64 id, SLine* firstLineOfSnippetSourceCode);
		SUpLine*		(CALLTYPE *vvm_snippetCompileLine)						(u64 id, SSnipExec* snippet,    SLine* originalLineOfSnippetSourceCode, SLine* replacementLineOfSnippetSourceCode, bool commitIfCompilesOkay);
		SUpLine*		(CALLTYPE *vvm_dynSnipCompileLine)						(u64 id, SDynSnip* dynSnippet, SLine* originalLineOfDynSnipSourceCode, SLine* replacementLineOfDynSnipSourceCode, bool commitIfCompilesOkay);
		bool			(CALLTYPE *vvm_snippetDelete)							(u64 id, SSnipExec* snippet);
		bool			(CALLTYPE *vvm_snippetUpdate)							(u64 id, SSnipExec* snippet,    SUpSnip* newSnippet);
		u64				(CALLTYPE *vvm_snippetAppend)							(u64 id, SSnipExec* snippet);
		bool			(CALLTYPE *vvm_dynamicSnippetDelete)					(u64 id, SDynSnip* dynSnippet);
		bool			(CALLTYPE *vvm_dynamicSnippetUpdate)					(u64 id, SDynSnip* dynSnippet, SUpSnip* newSnippet);
		u64				(CALLTYPE *vvm_dynamicSnippetAppend)					(u64 id, SDynSnip* dynSnippet);
		bool			(CALLTYPE *vvm_flushChangesToBxml)						(u64 id, SProgram* program);

		// For general access and control
		u64				(CALLTYPE *vvm_createThread)							(u64 id, void* functionAddress, u32 tnParameter);
		u64				(CALLTYPE *vvm_messageBox)								(u64 id, s8* tcText, s8* tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);


	//////////
	//
	// Build Buffer
	// An accumulation template for appending data in a stream manner, or for allocating a specified
	// size and then randomly updating it.
	//
	//////////
		void			(CALLTYPE *vvm_builderCreateAndInitialize)				(SBuilder** buffRoot, u32 tnAllocationSize);
		s8*				(CALLTYPE *vvm_builderAppendData)						(SBuilder*  buffRoot, s8* tcData, u32 tnDataLength);
		s8*				(CALLTYPE *vvm_builderAllocateBytes)					(SBuilder*	buffRoot, u32 tnDataLength);
		void			(CALLTYPE *vvm_builderSetSize)							(SBuilder*  buffRoot, u32 tnBufferLength);
		void			(CALLTYPE *vvm_builderFreeAndRelease)					(SBuilder** buffRoot);
		u32				(CALLTYPE *vvm_builderAsciiWriteOutFile)				(SBuilder*  buffRoot, s8* tcFilename);


	//////////
	//
	// SHA-1
	// Computes SHA-1 values in various ways.  The Start/ProcessThisData/Finish sections are to
	// be used when a computation must be conducted over multiple source calls.
	//
	//////
		void			(CALLTYPE *vvm_sha1ComputeSha1)							(s8* tcData, u32 tnDataLength, u8 shaOutput[20]);
		u64				(CALLTYPE *vvm_sha1ComputeSha1As64Bit)					(s8* tcData, u32 tnDataLength);
		u32				(CALLTYPE *vvm_sha1ComputeSha1As32Bit)					(s8* tcData, u32 tnDataLength);
		void			(CALLTYPE *vvm_sha1ComputeSha1AsHex)					(s8* tcData, u32 tnDataLength, s8* tcHexOutput, bool tlInsertSpaces);
		void			(CALLTYPE *vvm_sha1ConvertHexToSha1)					(u8 shaOutput[20], s8* tcHexInput, bool* tlError);
		void			(CALLTYPE *vvm_sha1ConvertSha1ToHex)					(s8* tcHexInput, u8 shaOutput[20], bool tlInsertSpaces);
		void			(CALLTYPE *vvm_sha1ComputeSha1_Start)					(u8 context[92]);
		void			(CALLTYPE *vvm_sha1ComputeSha1_ProcessThisData)			(u8 context[92], s8* tcData, u32 tnDataLength);
		void			(CALLTYPE *vvm_sha1ComputeSha1_FinishAsSha1)			(u8 context[92], u8 shaOutput[20], bool tlWipeData);
		void			(CALLTYPE *vvm_sha1ComputeSha1_FinishAsHex)				(u8 context[92], s8* tcHexOutput, bool tlInsertSpaces, bool tlWipeData);
		u64				(CALLTYPE *vvm_sha1Compute64BitFromSha1)				(u8 sha20Bytes[20]);
		u32				(CALLTYPE *vvm_sha1Compute32BitFromSha1)				(u8 sha20Bytes[20]);
		bool			(CALLTYPE *vvm_sha1Compare)								(u8 sha20Bytes1[20], u8 sha20Bytes2[20]);


	//////////
	//
	// BXML
	// The following functions relate the BXML engine as provided by the VVMOSS.
	// It is created to provide an autonomous and robust way to access any BXML file
	// as created by this engine.
	//
	//////////
		SBxml*			(CALLTYPE *vvm_bxmlLoad)								(s8* tcPathname, u32 tnPathnameLength, u64* tnBytesRead, u64* tnErrorOffset, u64* tnErrorCode);
		SBxml*			(CALLTYPE *vvm_bxmlLoadFromBuffer)						(s8* tcBxmlData, u32 tnBxmlDataLength,                   u64* tnErrorOffset, u64* tnErrorCode);
		bool			(CALLTYPE *vvm_bxmlSave)								(SBxml* bxml, s8* tcPathname, u32 tnPathnameLength, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnBytesWritten);
		void			(CALLTYPE *vvm_bxmlSaveToBuffer)						(SBxml* bxml, SBuilder** build, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnErrorNumber);

		SBxmla*			(CALLTYPE *vvm_bxmlaCreate)								(s8* tcNewName, u32 tnNewNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength);
		bool			(CALLTYPE *vvm_bxmlaSetName)							(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength);
		bool			(CALLTYPE *vvm_bxmlaSetData)							(SBxmla* bxmla, s8* tcData, u32 tnDataLength);
		bool			(CALLTYPE *vvm_bxmlaSetTotalLength)						(SBxmla* bxmla, u32 tnDataLengthTotal);
		SBxmla*			(CALLTYPE *vvm_bxmlaDelete)								(SBxmla* bxmla, bool tlFreeMemory);
		bool			(CALLTYPE *vvm_bxmlaInsert)								(SBxml* bxml, SBxmla* bxmlaRef, s8* tcName, u32 tnNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength, bool tlAfter);
		bool			(CALLTYPE *vvm_bxmlaInsertExisting)						(SBxml* bxml, SBxmla* bxmlaRef, SBxmla* bxmlaNew, bool tlAfter);
		SBxmla*			(CALLTYPE *vvm_bxmlaCopy)								(SBxmla* bxmla);
		SBxmla*			(CALLTYPE *vvm_bxmlaCopyAs)								(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength);
		u64				(CALLTYPE *vvm_bxmlaSha1One)							(SBxmla* bxmla, u8 sha20Bytes[20]);
		u64				(CALLTYPE *vvm_bxmlaSha1)								(SBxml*  bxml,  u8 sha20Bytes[20]);
		u64				(CALLTYPE *vvm_bxmlaSha1Tag)							(SBxml*  bxml,  u8 sha20Bytes[20]);
		u64				(CALLTYPE *vvm_bxmlaSha1Data)							(SBxml*  bxml,  u8 sha20Bytes[20]);

		u32				(CALLTYPE *vvm_bxmlaFindAndGetString)					(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, SDatum* tsResult, bool* tlError);
		u32				(CALLTYPE *vvm_bxmlaFindAndGetU32)						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		u64				(CALLTYPE *vvm_bxmlaFindAndGetU64)						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		bool			(CALLTYPE *vvm_bxmlaFindAndGetBool)						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		f32				(CALLTYPE *vvm_bxmlaFindAndGetF32)						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
		f64				(CALLTYPE *vvm_bxmlaFindAndGetF64)						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);

		u32				(CALLTYPE *vvm_bxmlaGetString)							(SBxmla* bxmla, SDatum* tsResult, bool* tlError);
		u32				(CALLTYPE *vvm_bxmlaGetU32)								(SBxmla* bxmla, bool* tlError);
		u64				(CALLTYPE *vvm_bxmlaGetU64)								(SBxmla* bxmla, bool* tlError);
		bool			(CALLTYPE *vvm_bxmlaGetBool)							(SBxmla* bxmla, bool* tlError);
		f32				(CALLTYPE *vvm_bxmlaGetF32)								(SBxmla* bxmla, bool* tlError);
		f64				(CALLTYPE *vvm_bxmlaGetF64)								(SBxmla* bxmla, bool* tlError);

		// For 2-way navigation through the attributes (can be done manually, but these expressly do it
		SBxmla*			(CALLTYPE *vvm_bxmlaGetNext)							(SBxmla* bxmla);
		SBxmla*			(CALLTYPE *vvm_bxmlaGetPrev)							(SBxmla* bxmla);

		SBxml*			(CALLTYPE *vvm_bxmlNodeCreate)							(s8* tcNewName, u32 tnNewNameLength);
		bool			(CALLTYPE *vvm_bxmlNodeSetName)							(SBxml* bxml, s8* tcNewName, u32 tnNewNameLength);
		SBxml*			(CALLTYPE *vvm_bxmlNodeDelete)							(SBxml* bxml, bool tlFreeMemory);
		bool			(CALLTYPE *vvm_bxmlNodeInsert)							(SBxml* bxml, SBxml* bxmlRef,                                     bool tlAfter);
		bool			(CALLTYPE *vvm_bxmlNodeInsertAsChild)					(SBxml* bxml, SBxml* bxmlParent,                                  bool tlAfter);
		bool			(CALLTYPE *vvm_bxmlNodeInsertAsChildAfter)				(SBxml* bxml, SBxml* bxmlParent, SBxml* bxmlRef,                  bool tlAfter);
		SBxml*			(CALLTYPE *vvm_bxmlNodeCopy)							(SBxml* bxml,                                        bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult);
		SBxml*			(CALLTYPE *vvm_bxmlNodeCopyAs)							(SBxml* bxml,    s8* tcNewName, u32 tnNewNameLength, bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult);
		u64				(CALLTYPE *vvm_bxmlNodeSha1)							(SBxml* bxml, u8 sha20Bytes[20]);
		u64				(CALLTYPE *vvm_bxmlNodeSha1Tag)							(SBxml* bxml, u8 sha20Bytes[20]);
		u64				(CALLTYPE *vvm_bxmlNodeSha1Data)						(SBxml* bxml, u8 sha20Bytes[20]);

		// For 4-way navigation through the XML structure (can be done manually, but these expressly do it
		SBxml*			(CALLTYPE *vvm_bxmlNodeGetNext)							(SBxml* bxml);
		SBxml*			(CALLTYPE *vvm_bxmlNodeGetPrev)							(SBxml* bxml);
		SBxml*			(CALLTYPE *vvm_bxmlNodeGetParent)						(SBxml* bxml);
		SBxml*			(CALLTYPE *vvm_bxmlNodeGetFirstChild)					(SBxml* bxml);
		SBxmla*			(CALLTYPE *vvm_bxmlNodeGetFirstAttribute)				(SBxml* bxml);

		SBxmla*			(CALLTYPE *vvm_bxmlFindAttribute)						(SBxml* bxml, s8* tcAttributeName, u32 tnAttributeNameLength, u32 tnInstance);
		bool			(CALLTYPE *vvm_bxmlFindFirst)							(SBxml* bxmlRoot, SBxml** bxmlNodeFound, SBxmla** bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, bool tlSearchAttributes, void** x);
		bool			(CALLTYPE *vvm_bxmlFindContinue)						(void* x);
		u32				(CALLTYPE *vvm_bxmlFindAllAsStartEndLists)				(SBxml* bxmlRoot, SStartEnd* bxmlFinds, SStartEnd* bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren, bool tlSearchAttributes);
		// Searches populated data in attributes for the indicated wildcard search string
		bool			(CALLTYPE *vvm_bxmlDataFindFirst)						(SBxml* bxmlRoot, SBxmla** bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, void** x);
		bool			(CALLTYPE *vvm_bxmlDataFindContinue)					(void* x);
		u32				(CALLTYPE *vvm_bxmlDataFindAllAsStartEndList)			(SBxml* bxmlRoot, SStartEnd* bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren);

		void			(CALLTYPE *vvm_bxmlGetLastError)						(SBxmlError* errorInfo);


	//////////
	//
	// Common functions
	//
	//////
		// Prototype definitions
		u8*				(CALLTYPE *vvm_duplicateString)							(u8* ptr, u64 length);
		w16*			(CALLTYPE *vvm_duplicateUnicodeString)					(w16* tuText);
		SDatum*			(CALLTYPE *vvm_datumSet)								(SDatum*  datum,  u8* ptr, u64 length,                  bool tlFreeExisting);
		SDatum2*		(CALLTYPE *vvm_datum2Set)								(SDatum2* datum2, u8* ptr, u64 length, u64 totalLength, bool tlFreeExisting);
		SDatum*			(CALLTYPE *vvm_datumDuplicate)							(SDatum*  datumDst,  SDatum*  datumSrc);
		SDatum2*		(CALLTYPE *vvm_datum2Duplicate)							(SDatum2* datum2Dst, SDatum2* datum2Src);
		void			(CALLTYPE *vvm_datumDelete)								(SDatum*  datum);
		void			(CALLTYPE *vvm_datum2Delete)							(SDatum2* datum2);
		void			(CALLTYPE *vvm_datum2SetNullString)						(SDatum2* datum2, u64 length, bool tlInitialize);

		void			(CALLTYPE *vvm_copyUpToShortestString)					(u8* dst, u32 tnDstLength, u8* src, u32 tnSrcLength);
		s32				(CALLTYPE *vvm_wildcardMatchDatum)						(SDatum* tsCandidate, SDatum* tsWildcardPattern, bool tlCaseSensitive);
		s32				(CALLTYPE *vvm_wildcardMatch)							(csu8p candidate, csu8p wildcardPattern, bool tlCaseSensitive);
		w16*			(CALLTYPE *vvm_asciiToUnicode)							(u8* tcText, u32 tnTextLength);
		s8*				(CALLTYPE *vvm_unicodeToAscii)							(w16* tuText, u32 tnTextLength);
		w16				(CALLTYPE *vvm_asciiToUnicodeChar)						(u8 tcChar);
		s8				(CALLTYPE *vvm_unicodeToAsciiCharacter)					(w16 tuChar);
		u64				(CALLTYPE *vvm_scanForwardUntilCharacterChanges)		(csu8p tcData, u64 tnMaxLength);
		u64				(CALLTYPE *vvm_scanForwardUntilCharacter)				(csu8p tcData, s8 c);
		int				(CALLTYPE *vvm_unicodeMemcmp)							(w16* l, w16* r, u32 tnLength);
		int				(CALLTYPE *vvm_unicodeMemicmp)							(w16* l, w16* r, u32 tnLength);
		int				(CALLTYPE *vvm_unicodeMemset)							(w16* p, w16 c, u32 tnLength);
		w16				(CALLTYPE *vvm_upperCaseW)								(w16 u);
		w16				(CALLTYPE *vvm_lowerCaseW)								(w16 u);
		void			(CALLTYPE *vvm_memset)									(s8* dst, s8 c, u64 tnCount);
		void			(CALLTYPE *vvm_memset4)									(u32* dst, u32 val, u64 tnCount);
		void			(CALLTYPE *vvm_memcpy)									(s8* dst, s8* src, u64 tnCount);
		s32				(CALLTYPE *vvm_memcmp)									(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
		s32				(CALLTYPE *vvm_memicmp)									(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
		s32				(CALLTYPE *vvm_memicmpTwoLengths)						(csu8p l/*eft*/, u64 tnLeftLength, csu8p r/*ight*/, u64 tnRightLength);
		s32				(CALLTYPE *vvm_memicmpDatum)							(SDatum*  datum,  csu8p r/*ight*/, u64 tnRightLength);
		s32				(CALLTYPE *vvm_memicmpDatum2)							(SDatum2* datum2, csu8p r/*ight*/, u64 tnRightLength);
		s32				(CALLTYPE *vvm_memicmpDatumDatum)						(SDatum*  datumL,  SDatum*  datumR);
		s32				(CALLTYPE *vvm_memicmpDatum2Datum2)						(SDatum2* datum2L, SDatum2* datum2R);
		void			(CALLTYPE *vvm_deriveRGBA)								(u32 tnColor, u8* tnRed, u8* tnGrn, u8* tnBlu, f32* tfAlp);
		u8				(CALLTYPE *vvm_getPredictableSequentialPattern)			(u32 tnIterator, u32 tnValue);

		SLL*			(CALLTYPE *vvm_ll_appendNode)							(SLL** root, SLL* nodeHint, SLL* nodeNext, SLL* nodePrev, u64 tnUniqueId, u32 tnSize);
		SLL*			(CALLTYPE *vvm_ll_createNode)							(SLL* nodePrev, SLL* nodeNext, u64 tnUniqueId, u32  tnSize);
		void			(CALLTYPE *vvm_ll_deleteNode)							(SLL* node);
		void			(CALLTYPE *vvm_ll_deleteNodesWithCallback)				(SLLCallback* cb);
		bool			(CALLTYPE *vvm_ll_insertNode)							(SLL* node, SLL* nodeRef, bool tlAfter);
		void			(CALLTYPE *vvm_ll_orphanizeNode)						(SLL* node);
		void			(CALLTYPE *vvm_ll_deleteNodeChain)						(SLL** root);
		void			(CALLTYPE *vvm_ll_deleteNodeChainWithCallback)			(SLLCallback* cb);
		void			(CALLTYPE *vvm_ll_iterateViaCallback)					(SLLCallback* cb);
		void			(CALLTYPE *vvm_ll_iterateBackwardViaCallback)			(SLLCallback* cb);
		SLL*			(CALLTYPE *vvm_ll_getFirstNode)							(SLL* node);
		SLL*			(CALLTYPE *vvm_ll_getLastNode)							(SLL* node);

		SLL4*			(CALLTYPE *vvm_ll4_create)								(SLL4* nodeWest, SLL4* nodeEast, SLL4* nodeNorth, SLL4* nodeSouth, u64 tnUniqueId, u32 tnSize);
		SLL4*			(CALLTYPE *vvm_ll4_createChain)							(u32 tnSize, u32* tnCount, u32 tnDirection);
		void			(CALLTYPE *vvm_ll4_delete)								(SLL4* node);
		bool			(CALLTYPE *vvm_ll4_orphanize)							(SLL4* node);
		bool			(CALLTYPE *vvm_ll4_insertNorthSouth)					(SLL4* node, SLL4* nodeRef,                   bool tlAfter);
		bool			(CALLTYPE *vvm_ll4_insertWestEast)						(SLL4* node, SLL4* nodeRef,                   bool tlAfter);
		void			(CALLTYPE *vvm_ll4_deleteChain)							(SLL4** root, u32 tnDirection);
		void			(CALLTYPE *vvm_ll4_deleteChainWithCallback)				(SLL4Callback* cb, u32 tnDirection);
		void			(CALLTYPE *vvm_ll4_iterateViaCallback)					(SLL4Callback* cb, u32 tnDirection);
		SLL4*			(CALLTYPE *vvm_ll4_getLastNode)							(SLL4* node, u32 tnDirection);

		bool			(CALLTYPE *vvm_ll4bxml_orphanize)						(SLL4* bxml);
		bool			(CALLTYPE *vvm_ll4bxml_insert)							(SLL4* bxmlSibling,	SLL4* bxmlRef,							bool tlAfter);
		bool			(CALLTYPE *vvm_ll4bxml_insertAsChild)					(SLL4* bxmlChild,	SLL4* bxmlParent,						bool tlPrepend);
		bool			(CALLTYPE *vvm_ll4bxml_insertAsChildRegarding)			(SLL4* bxmlChild,	SLL4* bxmlParent, SLL4* bxmlRegarding,	bool tlAfter);

		void*			(CALLTYPE *vvm_SEChain_prepend)							(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
		void*			(CALLTYPE *vvm_SEChain_append)							(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
		void*			(CALLTYPE *vvm_SEChain_appendRelativeToMember)			(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize,     u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);
		void*			(CALLTYPE *vvm_SEChain_appendExistingRelativeToMember)	(SStartEnd* ptrSE, SLL* ptrRef,                 u64 tnUniqueIdExtra, SLL* ptrCaller, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);

		void*			(CALLTYPE *vvm_SEChain_migrateAll)						(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc);
		SMasterList*	(CALLTYPE *vvm_SEChain_migrateByPtr)					(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, void* ptr,    u32 tnHint, u32 tnBlockSize);
		SMasterList*	(CALLTYPE *vvm_SEChain_migrateByNum)					(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);
		SLL*			(CALLTYPE *vvm_SEChain_completelyMigrateSLLByPtr)		(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr,     u32 tnHint, u32 tnBlockSize);
		SLL*			(CALLTYPE *vvm_SEChain_completelyMigrateSLLByNum)		(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);

		u32				(CALLTYPE *vvm_SEChain_countValids)						(SStartEnd* ptrSE);
		u32				(CALLTYPE *vvm_SEChain_delete)							(SStartEnd* ptrSE, u64 tnCallback, u64 tnParam, bool tlDeletePointers);
		void			(CALLTYPE *vvm_SEChain_deleteAsPtrBlock)				(SStartEnd* ptrSE);
		void			(CALLTYPE *vvm_SEChain_deleteFrom)						(SStartEnd* ptrSE, void* ptrDel, bool tlDeletePointers);
		bool			(CALLTYPE *vvm_SEChain_deleteFromAfterCallback)			(SStartEnd* ptrSE, bool tlDeletePointers, SStartEndCallback* cb);

		bool			(CALLTYPE *vvm_SEChain_allocateAdditionalMasterSlots)	(SStartEnd* ptrSE, u32 tnBlockSize);
		void*			(CALLTYPE *vvm_SEChain_searchByUniqueId)				(SStartEnd* ptrSE, u64 tnUniqueId);
		void*			(CALLTYPE *vvm_SEChain_searchByCallback)				(SStartEnd* ptrSE, SStartEndCallback* cb);
		void			(CALLTYPE *vvm_SEChain_iterateThroughForCallback)		(SStartEnd* ptrSE, SStartEndCallback* cb);
		void			(CALLTYPE *vvm_SEChain_validate)						(SStartEnd* ptrSE, SStartEndCallback* cb);

		u32				(CALLTYPE *vvm_swapEndian)								(u32 tnValue);
		u32				(CALLTYPE *vvm_RGBA2BGRA)								(u32 tnColor);
		void*			(CALLTYPE *vvm_allocateAndNull)							(u32 tnSize, bool tnInitToZeros);
		bool			(CALLTYPE *vvm_isNeedleInHaystack)						(csu8p tcHaystack, s32 tnHaystackLength, csu8p tcNeedle, s32 tnNeedleLength, bool tlCaseSensitive, u32* tnFoundPosition);
		bool			(CALLTYPE *vvm_isNeedleInHaystack_Unicode)				(w16* twHaystack, w16* twNeedle);
		u32				(CALLTYPE *vvm_countConsecutiveAsciiNumericDigits)		(s8* buffer, u32 tnMaxLength);
		u32				(CALLTYPE *vvm_convertTextToU32)						(s8* tcNumbers, u32 tnMaxLength);

		void			(CALLTYPE *vvm_math_computeTriangle)					(STriangleInOutF64* tri);
		void			(CALLTYPE *vvm_math_computeSquare)						(SSquareInOutF64* sq, f32 ox, f32 oy);
		void			(CALLTYPE *vvm_math_computeLine)						(SLineF64* line);
		void			(CALLTYPE *vvm_math_squareRotateAbout)					(SSquareInOutF64* sq);
		u32				(CALLTYPE *vvm_math_getGravityOfThetaAndLeft)			(f64 tfTheta, bool tlLeft);
		s32				(CALLTYPE *vvm_math_getGravity07FromDecoratedGravity)	(u32 tnGravityDecorated);
		f64				(CALLTYPE *vvm_math_getAreaOfSquareUsing_po_p1_p2)		(s32 tnGravity07_po, s32 tnGravity07_p1, s32 tnGravity07_p2, SXYF64* po, SXYF64* p1, SXYF64* p2);
		void			(CALLTYPE *vvm_math_getNextAxisInterceptXY)				(SXYF64* p, f64 tfTheta);
		s32				(CALLTYPE *vvm_math_getGravityByRelativePosition)		(SXYF64* p, SXYS32* po);
		s32				(CALLTYPE *vvm_math_getGravityInteger)					(SXYS32* p, SXYS32* po);
		s32				(CALLTYPE *vvm_math_fineAdjustGravityByTheta)			(SXYF64* po, SXYF64* p, SXYF64* pg, s32 lnGravity07p, s32 lnGravity07pg);
		f64				(CALLTYPE *vvm_math_adjustTheta)						(f64 tfTheta);
		bool			(CALLTYPE *vvm_math_withinDelta)						(f64 tfValue1, f64 tfValue2, s32 tnDeltaDecimals);
		u64				(CALLTYPE *vvm_math_washFloans)							(SCanvas* tc, SBGRA* bd, SBuilder** pointFloans, SBuilder** washFloans, SBuilder** drawFloans, bool tlIsFilledLeft);

		bool			(CALLTYPE *vvm_bezier_initialize)						(SBezier* bez, u32 tnCurveCount, u32 tnComputePointCount, bool tlWash);
		bool			(CALLTYPE *vvm_bezier_setByValues)						(SBezier* bez, SBGRA color, SXYF64* p1, SXYF64* p2, SXYF64* p3, SXYF64* p4, SXYF64* p5);

		bool			(CALLTYPE *vvm_polygon_initialize)						(SPolygon* poly, u32 tnLineCount, bool tlAllocatePolyLines);
		bool			(CALLTYPE *vvm_polygon_setByPolyLine)					(SPolygon* poly, u32 tnEntry, SPolyLine* line);
		bool			(CALLTYPE *vvm_polygon_setByValues)						(SPolygon* poly, u32 tnEntry, SXYF64* start, SXYF64* end, SXYF64* gravity);
		bool			(CALLTYPE *vvm_polygon_reset)							(SPolygon* poly, bool tlResetFloans);
		bool			(CALLTYPE *vvm_polygon_freeAndRelease)					(SPolygon* poly, bool tlReleaseFloans);

		u64				(CALLTYPE *vvm_screenRefresh)							(SScreen* ts);
		bool			(CALLTYPE *vvm_screenSetFocus)							(SScreen *ts);

		SRegion*		(CALLTYPE *vvm_regionDuplicate)							(u64 tnAssociatedId, SRegion* templateRegion);
		u64				(CALLTYPE *vvm_regionDefaultPaint)						(SRegion* tr);
		u64				(CALLTYPE *vvm_regionRefresh)							(SRegion* tr, SRegion* trParent);

		u64				(CALLTYPE *vvm_canvasDrawFixedPointText)				(SCanvas* tc, SBGRA* bd, u32 fontWidth, u32 fontHeight, s32 ulx, s32 uly,    s8*  text, u32 characterCount, SBGRA foreground, SBGRA background);
		u64				(CALLTYPE *vvm_canvasDrawText)							(SCanvas* tc, SBGRA* bd, u64 fontHandle, s32 ulx, s32 uly, s32 lrx, s32 lry, s8*  tcText, u32 tnTextLength, SBGRA foreground, SBGRA background);
		u64				(CALLTYPE *vvm_canvasFrameRect)							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border);
		u64				(CALLTYPE *vvm_canvasFillRect)							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border, SBGRA background);
		u64				(CALLTYPE *vvm_canvasLine)								(SCanvas* tc, SBGRA* bd, SXYF32* p1, SXYF32* p2, f32 lineThickness, SBGRA color, bool tlFloan);
		u64				(CALLTYPE *vvm_canvasArc)								(SCanvas* tc, SBGRA* bd, s32 ox, s32 oy, f32 radius, f32 start, f32 end, s32 lineThickness, SBGRA line);
		u64				(CALLTYPE *vvm_canvasBezier)							(SCanvas* tc, SBGRA* bd, SBezier* bez);
		SCanvas*		(CALLTYPE *vvm_canvasExtract)							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry);
		u64				(CALLTYPE *vvm_canvasColorize)							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, SBGRA color);
		u64				(CALLTYPE *vvm_canvasGrayscale)							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry);
		u64				(CALLTYPE *vvm_canvasGradient)							(SCanvas* tc, SBGRA* bd, SBGRA ul, SBGRA ur, SBGRA lr, SBGRA ll);
		u64				(CALLTYPE *vvm_canvasBitBlt)							(SCanvas* tsDst, bool tlDstAccumulator, s32 dulx, s32 duly, SCanvas* tsSrc, bool tlSrcAccumulator, s32 sulx, s32 suly, s32 slrx, s32 slry);
		u64				(CALLTYPE *vvm_canvasScale)								(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap** tsScaleMap);
		u64				(CALLTYPE *vvm_canvasRotate)							(SCanvas* tsDst, SBGRA* bdd, s32 ulx, s32 uly, SCanvas* tsSrc, SBGRA* bds, f32 tfRadians);
		u64				(CALLTYPE *vvm_canvasRotateAbout)						(SCanvas* tsDst, SBGRA* bdd, s32 ulx, s32 uly, SCanvas* tsSrc, SBGRA* bds, f32 tfRadians, s32 ox, s32 oy);
		u64				(CALLTYPE *vvm_canvasPolygon)							(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color);

		SCask*			(CALLTYPE *vvm_caskDefineStandard)						(u32 tnHeight, u32 tnWidth, u32 tnLeftStyle, u32 tnLeftState, u32 tnLeftPipCount, u32 tnLeftColor, csu8p tcLeftText, u32 tnRightStyle, u32 tnRightState, u32 tnRightPipCount, u32 tnRightColor, csu8p tcRightText);
		SCask*			(CALLTYPE *vvm_caskDefineEncompassingRectangle)			(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SRectXYXY* tsOuter);
		SCask*			(CALLTYPE *vvm_caskDefineUpRectangle)					(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter);
		SCask*			(CALLTYPE *vvm_caskDefineDownRectangle)					(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter);
		SCaskPip*		(CALLTYPE *vvm_caskSetPipByValues)						(SCask* cask, bool tlLeft, u32 tnPip, SBGRA tnPipColorNeutral, SBGRA tnPipColorOver, SBGRA tnPipColorClick, u64 tnEnterCallback, u64 tnLeaveCallback, u64 tnHoverCallback, u64 tnClickCallback, bool tlCreateCopy);
		SCaskPip*		(CALLTYPE *vvm_caskSetPipByStruct)						(SCask* cask, bool tlLeft, u32 tnPip, SCaskPip* caskPip, bool tlCreateCopy);
		SCask*			(CALLTYPE *vvm_caskCreate)								(SCask* cask, bool tlCreateCopy);
		SCanvas*		(CALLTYPE *vvm_caskRefresh)								(SCask* cask);

		u64				(CALLTYPE *vvm_iiCanvasPolygon)							(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color);
		void			(CALLTYPE *vvm_iDeleteScaleCompute)						(SScaleMap* tsm);
		u64				(CALLTYPE *vvm_iSkipWhitespaces)						(s8* tcData, u64 tnMaxLength);
		u64				(CALLTYPE *vvm_iSkipToCarriageReturnLineFeed)			(s8* tcData, u64 tnMaxLength, u64* tnCRLF_Length);
		u64				(CALLTYPE *vvm_iRegionDefaultPaintEditbox)				(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionEditboxData* editbox);
		u64				(CALLTYPE *vvm_iRegionDefaultPaintButton)				(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionButtonData* button);
		u64				(CALLTYPE *vvm_iRegionDefaultPaintImage)				(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionImageData* image);
		u64				(CALLTYPE *vvm_iRegionDefaultPaintLabel)				(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionLabelData* label);
		u64				(CALLTYPE *vvm_iRegionDefaultPaintCheckbox)				(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionCheckboxData* checkbox);
		u64				(CALLTYPE *vvm_iRegionDefaultPaintRectangle)			(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionRectangleData* rectangle);
		u64				(CALLTYPE *vvm_iDrawFixedPoint)							(SCanvas* tc, SBGRA* bd, u32 fontWidth, u32 fontHeight, s32 ulx, s32 uly, s8* text, u32 characterCount, SBGRA foreground, SBGRA background);
		u64				(CALLTYPE *vvm_iBitBltAll)								(SCanvas* tsDst, bool tlDstIsAccumulatorBuffer, s32 tnX, s32 tnY, SCanvas* tsSrc, bool tlSrcIsAccumulatorBuffer);
		void			(CALLTYPE *vvm_iiBitBltAll_Opaque)						(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 tnX, s32 tnY, SBGRA* trgbaSrcRoot, SCanvas* tsSrc);
		void			(CALLTYPE *vvm_iiBitBltAll_Alpha)						(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 tnX, s32 tnY, SBGRA* trgbaSrcRoot, SCanvas* tsSrc);
		u64				(CALLTYPE *vvm_iBitBltSection)							(SCanvas* tsDst, bool tlDstIsAccumulatorBuffer, s32 dulx, s32 duly, SCanvas* tsSrc, bool tlSrcIsAccumulatorBuffer, s32 sulx, s32 suly, s32 slrx, s32 slry);
		void			(CALLTYPE *vvm_iiBitBltSection_Opaque)					(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 dulx, s32 duly, SBGRA* trgbaSrcRoot, SCanvas* tsSrc, s32 sulx, s32 suly, s32 slrx, s32 slry);
		void			(CALLTYPE *vvm_iiBitBltSection_Alpha)					(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 dulx, s32 duly, SBGRA* trgbaSrcRoot, SCanvas* tsSrc, s32 sulx, s32 suly, s32 slrx, s32 slry);
		u32				(CALLTYPE *vvm_iiGradient)								(SCanvas* tc, SBGRA* bd, SBGRA ul, SBGRA ur, SBGRA lr, SBGRA ll);
		u64				(CALLTYPE *vvm_iCanvasLine)								(SCanvas* tc, SBGRA* bd, SXYF32* p1, SXYF32* p2, f32 lineThickness, SBGRA color);

	//////////
	// For internal VVM debugging
	//////
		void			(CALLTYPE *vvm_enableBreakpoints)						(void);
		void			(CALLTYPE *vvm_disableBreakpoints)						(void);




	//////////
	//
	// List of functions and their corresponding names.  Used in iLoadVvmFunctions().
	// NOTE:  The items in this list must appear in the same order as their definitions above
	//
	//////
		void* gVvmFunctions[] =
		{
			(void *)&vvm_firstCallback,										(void *)cgcVvmV1FirstCallback,
			(void *)&vvm_bootstrapInitialization,							(void *)cgcVvmV1BootstrapInitialization,
			(void *)&vvm_startTheVvm,										(void *)cgcVvmV1StartTheVvm,
			(void *)&vvm_getVersion,										(void *)cgcVvmV1GetVersion,
			(void *)&vvm_getLanguage,										(void *)cgcVvmV1GetLanguage,
			(void *)&vvm_loadResourceAsciiText,								(void *)cgcVvmV1LoadResourceAsciiText,
			(void *)&vvm_resourcePrintf,									(void *)cgcVvmV1ResourcePrintf,
			(void *)&vvm_requestUniqueID,									(void *)cgcVvmV1RequestUniqueId,
			(void *)&vvm_connect,											(void *)cgcVvmV1Connect,
			(void *)&vvm_connectRemote,										(void *)cgcVvmV1ConnectRemote,
			(void *)&vvm_getNextUniqueId,									(void *)cgcVvmV1GetNextUniqueId,

			(void *)&vvm_copyProgramList,									(void *)cgcVvmV1CopyProgramList,
			(void *)&vvm_programCopyScreensList,							(void *)cgcVvmV1ProgramCopyScreensList,
			(void *)&vvm_programCopyGlobalsList,							(void *)cgcVvmV1ProgramCopyGlobalsList,
			(void *)&vvm_programCopySnippetsList,							(void *)cgcVvmV1ProgramCopySnippetsList,
			(void *)&vvm_programCopyDynamicSnippetsList,					(void *)cgcVvmV1ProgramCopyDynamicSnippetsList,
			(void *)&vvm_programCopyTimersList,								(void *)cgcVvmV1ProgramCopyTimersList,
			(void *)&vvm_programCopyThreadsList,							(void *)cgcVvmV1ProgramCopyThreadsList,

			(void *)&vvm_programPause,										(void *)cgcVvmV1ProgramPause,
			(void *)&vvm_programResume,										(void *)cgcVvmV1ProgramResume,
			(void *)&vvm_programTerminate,									(void *)cgcVvmV1ProgramTerminate,
			(void *)&vvm_threadPause,										(void *)cgcVvmV1ThreadPause,
			(void *)&vvm_threadResume,										(void *)cgcVvmV1ThreadResume,
			(void *)&vvm_threadTerminate,									(void *)cgcVvmV1ThreadTerminate,
			(void *)&vvm_terminateVvm,										(void *)cgcVvmV1TerminateVvm,

			(void *)&vvm_getBreakpointList,									(void *)cgcVvmV1GetBreakpointList,
			(void *)&vvm_breakpointSet,										(void *)cgcVvmV1BreakpointSet,
			(void *)&vvm_breakpointClear,									(void *)cgcVvmV1BreakpointClear,

			(void *)&vvm_copyProgram,										(void *)cgcVvmV1CopyProgram,
			(void *)&vvm_copyThread,										(void *)cgcVvmV1CopyThread,
			(void *)&vvm_copyStack,											(void *)cgcVvmV1CopyStack,
			(void *)&vvm_copyRegisters,										(void *)cgcVvmV1CopyRegisters,
			(void *)&vvm_copyGlobal,										(void *)cgcVvmV1CopyGlobal,
			(void *)&vvm_copyTimer,											(void *)cgcVvmV1CopyTimer,
			(void *)&vvm_copyScreen,										(void *)cgcVvmV1CopyScreen,
			(void *)&vvm_copyCanvas,										(void *)cgcVvmV1CopyCanvas,

			(void *)&vvm_copySnippetTS,										(void *)cgcVvmV1CopySnippetTS,
			(void *)&vvm_copySnippetParent,									(void *)cgcVvmV1CopySnippetParent,
			(void *)&vvm_copySnippetSS,										(void *)cgcVvmV1CopySnippetSS,
			(void *)&vvm_copyDynamicSnippet,								(void *)cgcVvmV1CopyDynamicSnippet,

			(void *)&vvm_snippetCompile,									(void *)cgcVvmV1SnippetCompile,
			(void *)&vvm_snippetCompileLine,								(void *)cgcVvmV1SnippetCompileLine,
			(void *)&vvm_dynSnipCompileLine,								(void *)cgcVvmV1DynSnipCompileLine,
			(void *)&vvm_snippetDelete,										(void *)cgcVvmV1SnippetDelete,
			(void *)&vvm_snippetUpdate,										(void *)cgcVvmV1SnippetUpdate,
			(void *)&vvm_snippetAppend,										(void *)cgcVvmV1SnippetAppend,
			(void *)&vvm_dynamicSnippetDelete,								(void *)cgcVvmV1DynamicSnippetDelete,
			(void *)&vvm_dynamicSnippetUpdate,								(void *)cgcVvmV1DynamicSnippetUpdate,
			(void *)&vvm_dynamicSnippetAppend,								(void *)cgcVvmV1DynamicSnippetAppend,
			(void *)&vvm_flushChangesToBxml,								(void *)cgcVvmV1FlushChangesToBxml,

			(void *)&vvm_createThread,										(void *)cgcVvmV1CreateThread,
			(void *)&vvm_messageBox,										(void *)cgcVvmV1MessageBox,

			(void *)&vvm_builderCreateAndInitialize,						(void *)cgcVvmV1BuildBufferCreateAndInitialize,
			(void *)&vvm_builderAppendData,									(void *)cgcVvmV1BuildBufferAppendData,
			(void *)&vvm_builderAllocateBytes,								(void *)cgcVvmV1BuilderAllocateBytes,
			(void *)&vvm_builderSetSize,									(void *)cgcVvmV1BuildBufferSetSize,
			(void *)&vvm_builderFreeAndRelease,								(void *)cgcVvmV1BuildBufferFreeAndRelease,
			(void *)&vvm_builderAsciiWriteOutFile,							(void *)cgcVvmV1BuilderWriteOutAsciiFile,

			(void *)&vvm_sha1ComputeSha1,									(void *)cgcVvmV1Sha1ComputeSha1,
			(void *)&vvm_sha1ComputeSha1As64Bit,							(void *)cgcVvmV1Sha1ComputeSha1As64Bit,
			(void *)&vvm_sha1ComputeSha1As32Bit,							(void *)cgcVvmV1Sha1ComputeSha1As32Bit,
			(void *)&vvm_sha1ComputeSha1AsHex,								(void *)cgcVvmV1Sha1ComputeSha1AsHex,
			(void *)&vvm_sha1ConvertHexToSha1,								(void *)cgcVvmV1Sha1ConvertHexToSha1,
			(void *)&vvm_sha1ConvertSha1ToHex,								(void *)cgcVvmV1Sha1ConvertSha1ToHex,
			(void *)&vvm_sha1ComputeSha1_Start,								(void *)cgcVvmV1Sha1ComputeSha1_Start,
			(void *)&vvm_sha1ComputeSha1_ProcessThisData,					(void *)cgcVvmV1Sha1ComputeSha1_ProcessThisData,
			(void *)&vvm_sha1ComputeSha1_FinishAsSha1,						(void *)cgcVvmV1Sha1ComputeSha1_FinishAsSha1,
			(void *)&vvm_sha1ComputeSha1_FinishAsHex,						(void *)cgcVvmV1Sha1ComputeSha1_FinishAsHex,
			(void *)&vvm_sha1Compute64BitFromSha1,							(void *)cgcVvmV1Sha1Compute64BitFromSha1,
			(void *)&vvm_sha1Compute32BitFromSha1,							(void *)cgcVvmV1Sha1Compute32BitFromSha1,
			(void *)&vvm_sha1Compare,										(void *)cgcVvmV1Sha1Compare,

			(void *)&vvm_bxmlLoad,											(void *)cgcVvmV1BxmlLoad,
			(void *)&vvm_bxmlLoadFromBuffer,								(void *)cgcVvmV1BxmlLoadFromBuffer,
			(void *)&vvm_bxmlSave,											(void *)cgcVvmV1BxmlSave,
			(void *)&vvm_bxmlSaveToBuffer,									(void *)cgcVvmV1BxmlSaveToBuffer,

			(void *)&vvm_bxmlaCreate,										(void *)cgcVvmV1BxmlAttributeCreate,
			(void *)&vvm_bxmlaSetName,										(void *)cgcVvmV1BxmlAttributeSetName,
			(void *)&vvm_bxmlaSetData,										(void *)cgcVvmV1BxmlAttributeSetData,
			(void *)&vvm_bxmlaSetTotalLength,								(void *)cgcVvmV1BxmlAttributeSetTotalLength,
			(void *)&vvm_bxmlaDelete,										(void *)cgcVvmV1BxmlAttributeDelete,
			(void *)&vvm_bxmlaInsert,										(void *)cgcVvmV1BxmlAttributeInsert,
			(void *)&vvm_bxmlaInsertExisting,								(void *)cgcVvmV1BxmlAttributeInsertExisting,
			(void *)&vvm_bxmlaCopy,											(void *)cgcVvmV1BxmlAttributeCopy,
			(void *)&vvm_bxmlaCopyAs,										(void *)cgcVvmV1BxmlAttributeCopyAs,
			(void *)&vvm_bxmlaSha1One,										(void *)cgcVvmV1BxmlAttributeSha1One,
			(void *)&vvm_bxmlaSha1,											(void *)cgcVvmV1BxmlAttributeSha1,
			(void *)&vvm_bxmlaSha1Tag,										(void *)cgcVvmV1BxmlAttributeSha1Tag,
			(void *)&vvm_bxmlaSha1Data,										(void *)cgcVvmV1BxmlAttributeSha1Data,

			(void *)&vvm_bxmlaFindAndGetString,								(void *)cgcVvmV1BxmlAttributeFindAndGetString,
			(void *)&vvm_bxmlaFindAndGetU32,								(void *)cgcVvmV1BxmlAttributeFindAndGetU32,
			(void *)&vvm_bxmlaFindAndGetU64,								(void *)cgcVvmV1BxmlAttributeFindAndGetU64,
			(void *)&vvm_bxmlaFindAndGetBool,								(void *)cgcVvmV1BxmlAttributeFindAndGetUBool,
			(void *)&vvm_bxmlaFindAndGetF32,								(void *)cgcVvmV1BxmlAttributeFindAndGetF32,
			(void *)&vvm_bxmlaFindAndGetF64,								(void *)cgcVvmV1BxmlAttributeFindAndGetF64,

			(void *)&vvm_bxmlaGetString,									(void *)cgcVvmV1BxmlAttributeGetString,
			(void *)&vvm_bxmlaGetU32,										(void *)cgcVvmV1BxmlAttributeGetU32,
			(void *)&vvm_bxmlaGetU64,										(void *)cgcVvmV1BxmlAttributeGetU64,
			(void *)&vvm_bxmlaGetBool,										(void *)cgcVvmV1BxmlAttributeGetUBool,
			(void *)&vvm_bxmlaGetF32,										(void *)cgcVvmV1BxmlAttributeGetF32,
			(void *)&vvm_bxmlaGetF64,										(void *)cgcVvmV1BxmlAttributeGetF64,

			(void *)&vvm_bxmlaGetNext,										(void *)cgcVvmV1BxmlAttributeGetNext,
			(void *)&vvm_bxmlaGetPrev,										(void *)cgcVvmV1BxmlAttributeGetPrev,

			(void *)&vvm_bxmlNodeCreate,									(void *)cgcVvmV1BxmlNodeCreate,
			(void *)&vvm_bxmlNodeSetName,									(void *)cgcVvmV1BxmlNodeSetName,
			(void *)&vvm_bxmlNodeDelete,									(void *)cgcVvmV1BxmlNodeDelete,
			(void *)&vvm_bxmlNodeInsert,									(void *)cgcVvmV1BxmlNodeInsert,
			(void *)&vvm_bxmlNodeInsertAsChild,								(void *)cgcVvmV1BxmlNodeInsertAsChild,
			(void *)&vvm_bxmlNodeInsertAsChildAfter,						(void *)cgcVvmV1BxmlNodeInsertAsChildAfter,
			(void *)&vvm_bxmlNodeCopy,										(void *)cgcVvmV1BxmlNodeCopy,
			(void *)&vvm_bxmlNodeCopyAs,									(void *)cgcVvmV1BxmlNodeCopyAs,
			(void *)&vvm_bxmlNodeSha1,										(void *)cgcVvmV1BxmlNodeSha1,
			(void *)&vvm_bxmlNodeSha1Tag,									(void *)cgcVvmV1BxmlNodeSha1Tag,
			(void *)&vvm_bxmlNodeSha1Data,									(void *)cgcVvmV1BxmlNodeSha1Data,

			(void *)&vvm_bxmlNodeGetNext,									(void *)cgcVvmV1BxmlGetNext,
			(void *)&vvm_bxmlNodeGetPrev,									(void *)cgcVvmV1BxmlGetPrev,
			(void *)&vvm_bxmlNodeGetParent,									(void *)cgcVvmV1BxmlGetParent,
			(void *)&vvm_bxmlNodeGetFirstChild,								(void *)cgcVvmV1BxmlGetFirstChild,
			(void *)&vvm_bxmlNodeGetFirstAttribute,							(void *)cgcVvmV1BxmlGetFirstAttribute,

			(void *)&vvm_bxmlFindAttribute,									(void *)cgcVvmV1BxmlFindAttribute,
			(void *)&vvm_bxmlFindFirst,										(void *)cgcVvmV1BxmlFindFirst,
			(void *)&vvm_bxmlFindContinue,									(void *)cgcVvmV1BxmlFindContinue,
			(void *)&vvm_bxmlFindAllAsStartEndLists,						(void *)cgcVvmV1BxmlFindAllAsStartEndLists,

			(void *)&vvm_bxmlDataFindFirst,									(void *)cgcVvmV1BxmlDatFindFirst,
			(void *)&vvm_bxmlDataFindContinue,								(void *)cgcVvmV1BxmlDataFindContinue,
			(void *)&vvm_bxmlDataFindAllAsStartEndList,						(void *)cgcVvmV1BxmlDataFindAllAsStartEndList,

			(void *)&vvm_bxmlGetLastError,									(void *)cgcVvmV1BxmlGetLastError,

			(void*)&vvm_duplicateString,									(void*)cgcVvmV1DuplicateString,
			(void*)&vvm_duplicateUnicodeString,								(void*)cgcVvmV1DuplicateUnicodeString,
			(void*)&vvm_datumSet,											(void*)cgcVvmV1DatumSet,
			(void*)&vvm_datum2Set,											(void*)cgcVvmV1Datum2Set,
			(void*)&vvm_datumDuplicate,										(void*)cgcVvmV1DatumDuplicate,
			(void*)&vvm_datum2Duplicate,									(void*)cgcVvmV1Datum2Duplicate,
			(void*)&vvm_datumDelete,										(void*)cgcVvmV1DatumDelete,
			(void*)&vvm_datum2Delete,										(void*)cgcVvmV1Datum2Delete,
			(void*)&vvm_datum2SetNullString,								(void*)cgcVvmV1Datum2SetNullString,

			(void*)&vvm_copyUpToShortestString,								(void*)cgcVvmV1CopyUpToShortestString,
			(void*)&vvm_wildcardMatchDatum,									(void*)cgcVvmV1WildcardMatchDatum,
			(void*)&vvm_wildcardMatch,										(void*)cgcVvmV1WildcardMatch,
			(void*)&vvm_asciiToUnicode,										(void*)cgcVvmV1AsciiToUnicode,
			(void*)&vvm_unicodeToAscii,										(void*)cgcVvmV1UnicodeToAscii,
			(void*)&vvm_asciiToUnicodeChar,									(void*)cgcVvmV1AsciiToUnicodeChar,
			(void*)&vvm_unicodeToAsciiCharacter,							(void*)cgcVvmV1UnicodeToAsciiCharacter,
			(void*)&vvm_scanForwardUntilCharacterChanges,					(void*)cgcVvmV1ScanForwardUntilCharacterChanges,
			(void*)&vvm_scanForwardUntilCharacter,							(void*)cgcVvmV1ScanForwardUntilCharacter,
			(void*)&vvm_unicodeMemcmp,										(void*)cgcVvmV1UnicodeMemcmp,
			(void*)&vvm_unicodeMemicmp,										(void*)cgcVvmV1UnicodeMemicmp,
			(void*)&vvm_unicodeMemset,										(void*)cgcVvmV1UnicodeMemset,
			(void*)&vvm_upperCaseW,											(void*)cgcVvmV1UpperCaseW,
			(void*)&vvm_lowerCaseW,											(void*)cgcVvmV1LowerCaseW,
			(void*)&vvm_memset,												(void*)cgcVvmV1Memset,
			(void*)&vvm_memset4,											(void*)cgcVvmV1Memset4,
			(void*)&vvm_memcpy,												(void*)cgcVvmV1Memcpy,
			(void*)&vvm_memcmp,												(void*)cgcVvmV1Memcmp,
			(void*)&vvm_memicmp,											(void*)cgcVvmV1Memicmp,
			(void*)&vvm_memicmpTwoLengths,									(void*)cgcVvmV1MemicmpTwoLengths,
			(void*)&vvm_memicmpDatum,										(void*)cgcVvmV1MemicmpDatum,
			(void*)&vvm_memicmpDatum2,										(void*)cgcVvmV1MemicmpDatum2,
			(void*)&vvm_memicmpDatumDatum,									(void*)cgcVvmV1MemicmpDatumDatum,
			(void*)&vvm_memicmpDatum2Datum2,								(void*)cgcVvmV1MemicmpDatum2Datum2,
			(void*)&vvm_deriveRGBA,											(void*)cgcVvmV1DeriveRGBA,
			(void*)&vvm_getPredictableSequentialPattern,					(void*)cgcVvmV1GetPredictableSequentialPattern,

			(void*)&vvm_ll_appendNode,										(void*)cgcVvmV1LlAppendNode,
			(void*)&vvm_ll_createNode,										(void*)cgcVvmV1LlCreateNode,
			(void*)&vvm_ll_deleteNode,										(void*)cgcVvmV1LlDeleteNode,
			(void*)&vvm_ll_deleteNodesWithCallback,							(void*)cgcVvmV1LlDeleteNodeWithCallback,
			(void*)&vvm_ll_insertNode,										(void*)cgcVvmV1LlInsertNode,
			(void*)&vvm_ll_orphanizeNode,									(void*)cgcVvmV1LlOrphanizeNode,
			(void*)&vvm_ll_deleteNodeChain,									(void*)cgcVvmV1LlDeleteNodeChain,
			(void*)&vvm_ll_deleteNodeChainWithCallback,						(void*)cgcVvmV1LlDeleteNodeChainWithCallback,
			(void*)&vvm_ll_iterateViaCallback,								(void*)cgcVvmV1LlIterateViaCallback,
			(void*)&vvm_ll_iterateBackwardViaCallback,						(void*)cgcVvmV1LlIterateBackwardViaCallback,
			(void*)&vvm_ll_getFirstNode,									(void*)cgcVvmV1LlGetFirstNode,
			(void*)&vvm_ll_getLastNode,										(void*)cgcVvmV1LlGetLastNode,

			(void*)&vvm_ll4_create,											(void*)cgcVvmV1Ll4Create,
			(void*)&vvm_ll4_createChain,									(void*)cgcVvmV1Ll4CreateChain,
			(void*)&vvm_ll4_delete,											(void*)cgcVvmV1Ll4Delete,
			(void*)&vvm_ll4_orphanize,										(void*)cgcVvmV1Ll4OrphanizeAsNode,
			(void*)&vvm_ll4_insertNorthSouth,								(void*)cgcVvmV1Ll4InsertAsNodeNorthSouth,
			(void*)&vvm_ll4_insertWestEast,									(void*)cgcVvmV1Ll4InsertAsNodeEastWest,
			(void*)&vvm_ll4_deleteChain,									(void*)cgcVvmV1Ll4DeleteChain,
			(void*)&vvm_ll4_deleteChainWithCallback,						(void*)cgcVvmV1Ll4DeleteChainWithCallback,
			(void*)&vvm_ll4_iterateViaCallback,								(void*)cgcVvmV1Ll4IterateViaCallback,
			(void*)&vvm_ll4_getLastNode,									(void*)cgcVvmV1Ll4GetLastNode,

			(void*)&vvm_ll4bxml_orphanize,									(void*)cgcVvmV1Ll4BxmlOrphanize,
			(void*)&vvm_ll4bxml_insert,										(void*)cgcVvmV1Ll4BxmlInsert,
			(void*)&vvm_ll4bxml_insertAsChild,								(void*)cgcVvmV1Ll4BxmlInsertAsChild,
			(void*)&vvm_ll4bxml_insertAsChildRegarding,						(void*)cgcVvmV1Ll4BxmlInsertAsChildRegarding,

			(void*)&vvm_SEChain_prepend,									(void*)cgcVvmV1SEChainPrepend,
			(void*)&vvm_SEChain_append,										(void*)cgcVvmV1SEChainAppend,
			(void*)&vvm_SEChain_appendRelativeToMember,						(void*)cgcVvmV1SEChainAppendRelativeToMember,
			(void*)&vvm_SEChain_appendExistingRelativeToMember,				(void*)cgcVvmV1SEChainAppendExistingRelativeToMember,

			(void*)&vvm_SEChain_migrateAll,									(void*)cgcVvmV1SEChainMigrateAll,
			(void*)&vvm_SEChain_migrateByPtr,								(void*)cgcVvmV1SEChainMigrateByPtr,
			(void*)&vvm_SEChain_migrateByNum,								(void*)cgcVvmV1SEChainMigrateByNum,
			(void*)&vvm_SEChain_completelyMigrateSLLByPtr,					(void*)cgcVvmV1SEChainCompletelyMigrateSLLByPtr,
			(void*)&vvm_SEChain_completelyMigrateSLLByNum,					(void*)cgcVvmV1SEChainCompletelyMigrateSLLByNum,

			(void*)&vvm_SEChain_countValids,								(void*)cgcVvmV1SEChainCountValids,
			(void*)&vvm_SEChain_delete,										(void*)cgcVvmV1SEChainDelete,
			(void*)&vvm_SEChain_deleteAsPtrBlock,							(void*)cgcVvmV1SEChainDeleteAsPtrBlock,
			(void*)&vvm_SEChain_deleteFrom,									(void*)cgcVvmV1SEChainDeleteFrom,
			(void*)&vvm_SEChain_deleteFromAfterCallback,					(void*)cgcVvmV1SEChainDeleteFromAfterCallback,

			(void*)&vvm_SEChain_allocateAdditionalMasterSlots,				(void*)cgcVvmV1SEChainAllocateAdditionalMasterSlots,
			(void*)&vvm_SEChain_searchByUniqueId,							(void*)cgcVvmV1SEChainSearchByUniqueId,
			(void*)&vvm_SEChain_searchByCallback,							(void*)cgcVvmV1SEChainSearchByCallback,
			(void*)&vvm_SEChain_iterateThroughForCallback,					(void*)cgcVvmV1SEChainIterateThroughForCallback,
			(void*)&vvm_SEChain_validate,									(void*)cgcVvmV1SEChainValidate,

			(void*)&vvm_swapEndian,											(void*)cgcVvmV1SwapEndian,
			(void*)&vvm_RGBA2BGRA,											(void*)cgcVvmV1RGA2BGRA,
			(void*)&vvm_allocateAndNull,									(void*)cgcVvmV1AllocateAndNull,
			(void*)&vvm_isNeedleInHaystack,									(void*)cgcVvmV1IsNeedleInHaystack,
			(void*)&vvm_isNeedleInHaystack_Unicode,							(void*)cgcVvmV1IsNeedleInHaystackUnicode,
			(void*)&vvm_countConsecutiveAsciiNumericDigits,					(void*)cgcVvmV1CountConsecutiveAsciiNumericDigits,
			(void*)&vvm_convertTextToU32,									(void*)cgcVvmV1ConvertTextToU32,

			(void*)&vvm_math_computeTriangle,								(void*)cgcVvmV1MathComputeTriangle,
			(void*)&vvm_math_computeSquare,									(void*)cgcVvmV1MathComputeSquare,
			(void*)&vvm_math_computeLine,									(void*)cgcVvmV1MathComputeLine,
			(void*)&vvm_math_squareRotateAbout,								(void*)cgcVvmV1MathSquareRotateAbout,
			(void*)&vvm_math_getGravityOfThetaAndLeft,						(void*)cgcVvmV1MathGetGravityOfThetaAndLeft,
			(void*)&vvm_math_getGravity07FromDecoratedGravity,				(void*)cgcVvmV1MathGetGravity07FromDecoratedGravity,
			(void*)&vvm_math_getAreaOfSquareUsing_po_p1_p2,					(void*)cgcVvmV1MathGetAreaOfSquareUsingPoP1P2,
			(void*)&vvm_math_getNextAxisInterceptXY,						(void*)cgcVvmV1MathGetNextAxisInterceptXY,
			(void*)&vvm_math_getGravityByRelativePosition,					(void*)cgcVvmV1MathGetRelativeGravity,
			(void*)&vvm_math_getGravityInteger,								(void*)cgcVvmV1MathGetGravityInteger,
			(void*)&vvm_math_fineAdjustGravityByTheta,						(void*)cgcVvmV1MathFineAdjustGravityByTheta,
			(void*)&vvm_math_adjustTheta,									(void*)cgcVvmV1MathAdjustTheta,
			(void*)&vvm_math_withinDelta,									(void*)cgcVvmV1MathWithinDelta,
			(void*)&vvm_math_washFloans,									(void*)cgcVvmV1MathWashFloans,

			(void*)&vvm_bezier_initialize,									(void*)cgcVvmV1BezierInitialize,
			(void*)&vvm_bezier_setByValues,									(void*)cgcVvmV1BezierSetByValues,

			(void*)&vvm_polygon_initialize,									(void*)cgcVvmV1PolygonInitialize,
			(void*)&vvm_polygon_setByPolyLine,								(void*)cgcVvmV1PolygonSetByPolyLine,
			(void*)&vvm_polygon_setByValues,								(void*)cgcVvmV1PolygonSetByValues,
			(void*)&vvm_polygon_reset,										(void*)cgcVvmV1PolygonReset,
			(void*)&vvm_polygon_freeAndRelease,								(void*)cgcVvmV1PolygonFreeAndRelease,

			(void *)&vvm_screenRefresh,										(void *)cgcVvmV1ScreenRefresh,
			(void *)&vvm_screenSetFocus,									(void *)cgcVvmV1ScreenSetFocus,

			(void *)&vvm_regionDuplicate,									(void *)cgcVvmV1RegionDuplicate,
			(void *)&vvm_regionDefaultPaint,								(void *)cgcVvmV1RegionDefaultPaint,
			(void *)&vvm_regionRefresh,										(void *)cgcVvmV1RegionRefresh,

			(void *)&vvm_canvasDrawFixedPointText,							(void *)cgcVvmV1CanvasWriteFixedPointText,
			(void *)&vvm_canvasDrawText,									(void *)cgcVvmV1CanvasDrawText,
			(void *)&vvm_canvasFrameRect,									(void *)cgcVvmV1CanvasFrameRect,
			(void *)&vvm_canvasFillRect,									(void *)cgcVvmV1CanvasFillRect,
			(void *)&vvm_canvasLine,										(void *)cgcVvmV1CanvasLine,
			(void *)&vvm_canvasArc,											(void *)cgcVvmV1CanvasArc,
			(void *)&vvm_canvasBezier,										(void *)cgcVvmV1CanvasBezier,

			(void *)&vvm_canvasExtract,										(void *)cgcVvmV1CanvasExtract,
			(void *)&vvm_canvasColorize,									(void *)cgcVvmV1CanvasColorize,
			(void *)&vvm_canvasGrayscale,									(void *)cgcVvmV1CanvasGrayscale,
			(void *)&vvm_canvasGradient,									(void *)cgcVvmV1CanvasGradient,
			(void *)&vvm_canvasBitBlt,										(void *)cgcVvmV1CanvasBitBlt,
			(void *)&vvm_canvasScale,										(void *)cgcVvmV1CanvasScale,
			(void *)&vvm_canvasRotate,										(void *)cgcVvmV1CanvasRotate,
			(void *)&vvm_canvasRotateAbout,									(void *)cgcVvmV1CanvasRotateAbout,
			(void *)&vvm_canvasPolygon,										(void *)cgcVvmV1CanvasPolygon,

			(void *)&vvm_caskDefineStandard,								(void *)cgcVvmV1CaskDefineStandard,
			(void *)&vvm_caskDefineEncompassingRectangle,					(void *)cgcVvmV1CaskDefineEncompassingRectangle,
			(void *)&vvm_caskDefineUpRectangle,								(void *)cgcVvmV1CaskDefineUpRectangle,
			(void *)&vvm_caskDefineDownRectangle,							(void *)cgcVvmV1CaskDefineDownRectangle,
			(void *)&vvm_caskSetPipByValues,								(void *)cgcVvmV1CaskSetPipByValues,
			(void *)&vvm_caskSetPipByStruct,								(void *)cgcVvmV1CaskSetPipByStruct,
			(void *)&vvm_caskCreate,										(void *)cgcVvmV1CaskCreate,
			(void *)&vvm_caskRefresh,										(void *)cgcVvmV1CaskRefresh,

			(void *)&vvm_iiCanvasPolygon,									(void *)cgcVvmV1iiCanvasPolygon,
			(void *)&vvm_iDeleteScaleCompute,								(void *)cgcVvmV1iDeleteScaleCompute,
			(void *)&vvm_iSkipWhitespaces,									(void *)cgcVvmV1iSkipWhiteSpaces,
			(void *)&vvm_iSkipToCarriageReturnLineFeed,						(void *)cgcVvmV1iSkipToCarriageReturnLineFeed,
			(void *)&vvm_iRegionDefaultPaintEditbox,						(void *)cgcVvmV1iRegionDefaultPaintEditbox,
			(void *)&vvm_iRegionDefaultPaintButton,							(void *)cgcVvmV1iRegionDefaultPaintButton,
			(void *)&vvm_iRegionDefaultPaintImage,							(void *)cgcVvmV1iRegionDefaultPaintImage,
			(void *)&vvm_iRegionDefaultPaintLabel,							(void *)cgcVvmV1iRegionDefaultPaintLabel,
			(void *)&vvm_iRegionDefaultPaintCheckbox,						(void *)cgcVvmV1iRegionDefaultPaintCheckbox,
			(void *)&vvm_iRegionDefaultPaintRectangle,						(void *)cgcVvmV1iRegionDefaultPaintRectangle,
			(void *)&vvm_iDrawFixedPoint,									(void *)cgcVvmV1iDrawFixedPoint,
			(void *)&vvm_iBitBltAll,										(void *)cgcVvmV1iBitBltAll,
			(void *)&vvm_iiBitBltAll_Opaque,								(void *)cgcVvmV1iiBitBltAll_Opaque,
			(void *)&vvm_iiBitBltAll_Alpha,									(void *)cgcVvmV1iiBitBltAll_Alpha,
			(void *)&vvm_iBitBltSection,									(void *)cgcVvmV1iBitBltSection,
			(void *)&vvm_iiBitBltSection_Opaque,							(void *)cgcVvmV1iiBitBltSection_Opaque,
			(void *)&vvm_iiBitBltSection_Alpha,								(void *)cgcVvmV1iiBitBltSection_Alpha,
			(void *)&vvm_iiGradient,										(void *)cgcVvmV1iiGradient,
			(void *)&vvm_iCanvasLine,										(void *)cgcVvmV1iCanvasLine,

			(void *)&vvm_enableBreakpoints,									(void *)cgcVvmV1EnableBreakpoints,
			(void *)&vvm_disableBreakpoints,								(void *)cgcVvmV1DisableBreakpoints
		};
		u32 gVvmFunctionCount = sizeof(gVvmFunctions) / (2 * sizeof(void*));



	//////////
	//
	// Called once to load all the gVvmFunctions[] at startup.
	//
	//////
		HINSTANCE vvmDllInstance = NULL;
		bool iLoadVvmFunctionsFromDll(void)
		{
			u32			lnI;
			s8*			lcFuncName;
			void**		lcFuncAddress;
			void*		lcAddress;
			s8			buffer[1024];


			// Try to load the dll
			if (!vvmDllInstance)
			{
				vvmDllInstance = LoadLibraryA("vvm.dll");
				if (!vvmDllInstance)
				{
					// There was an error loading the dll
					return(false);
				}
			}
			// If we get here, we have a candidate.
			// But, to be valid it has to have the required functions

			// Now, repeatedly call back that address with the request to all of the function addresses
			for (lnI = 0; lnI < gVvmFunctionCount; lnI++)
			{
				// Grab the details of this entry
				lcFuncAddress	= (void**)gVvmFunctions[(lnI * 2) + 0];		// Grab the indirect address to store
				lcFuncName		= (s8*)   gVvmFunctions[(lnI * 2) + 1];		// Grab the function name to request

				// Ask the VVM for this specific function location
				lcAddress = GetProcAddress(vvmDllInstance, lcFuncName);

				// Process the result
				if (!lcAddress)
				{
					// The specified functionality is not available
					// Note:  By design, this should never happen.  It is the result of a programming error.
					sprintf_s(buffer, sizeof(buffer), "Error accessing: %s\000", lcFuncName);
					MessageBoxA(NULL, buffer, "VVM Initialization Error", MB_OK);
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
