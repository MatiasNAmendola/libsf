//////////
//
// /libsf/vvm/common/common_vvm.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     October 23, 2012 - Initial creation
//     October 23, 2012 - PBL v1.0 license included directly in source files.
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
//
// Constants used by the VVM
//
//////
	const u32		_VVM_REGION_TAB_STOP							= 1;
	const u32		_VVM_REGION_KEYBOARD_INPUT						= 2;
	const u32		_VVM_REGION_MOUSE_INPUT							= 4;
	const u32		_VVM_REGION_STANDARD_INPUT						= _VVM_REGION_TAB_STOP + _VVM_REGION_KEYBOARD_INPUT + _VVM_REGION_MOUSE_INPUT;

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
	const s8		cgcVvmV1GetLanguage[]							= "vvm1_getLanguage";
	const s8		cgcVvmV1LoadResourceAsciiText[]					= "vvm1_loadResourceAsciiText";
	const s8		cgcVvmV1ResourcePrintf[]						= "vvm1_resourcePrintf";
	const s8		cgcVvmV1Debugger[]								= "vvm1_debugger";
	const s8		cgcVvmV1RequestUniqueId[]						= "vvm1_requestUniqueID";
	const s8		cgcVvmV1Connect[]								= "vvm1_connect";
	const s8		cgcVvmV1ConnectRemote[]							= "vvm1_connectRemote";
	const s8		cgcVvmV1GetNextUniqueId[]						= "vvm1_getNextUniqueId";

	const s8		cgcVvmV1CopyProgramList[]						= "vvm1_copyProgramList";
	const s8		cgcVvmV1ProgramCopyScreensList[]				= "vvm1_pogramCopyScreensList";
	const s8		cgcVvmV1ProgramCopyGlobalsList[]				= "vvm1_programCopyGlobalsList";
	const s8		cgcVvmV1ProgramCopySnippetsList[]				= "vvm1_programCopySnippetsList";
	const s8		cgcVvmV1ProgramCopyDynamicSnippetsList[]		= "vvm1_programCopyDynamicSnippetsList";
	const s8		cgcVvmV1ProgramCopyTimersList[]					= "vvm1_programCopyTimersList";
	const s8		cgcVvmV1ProgramCopyThreadsList[]				= "vvm1_programCopyThreadsList";

	const s8		cgcVvmV1ProgramPause[]							= "vvm1_programPause";
	const s8		cgcVvmV1ProgramResume[]							= "vvm1_programResume";
	const s8		cgcVvmV1ProgramTerminate[]						= "vvm1_programTerminate";
	const s8		cgcVvmV1ThreadPause[]							= "vvm1_threadPause";
	const s8		cgcVvmV1ThreadResume[]							= "vvm1_threadResume";
	const s8		cgcVvmV1ThreadTerminate[]						= "vvm1_threadTerminate";
	const s8		cgcVvmV1TerminateVvm[]							= "vvm1_terminateVvm";

	const s8		cgcVvmV1GetBreakpointList[]						= "vvm1_getBreakpointList";
	const s8		cgcVvmV1BreakpointSet[]							= "vvm1_breakpointSet";
	const s8		cgcVvmV1BreakpointClear[]						= "vvm1_breakpointClear";

	const s8		cgcVvmV1CopyProgram[]							= "vvm1_copyProgram";
	const s8		cgcVvmV1CopyThread[]							= "vvm1_copyThread";
	const s8		cgcVvmV1CopyStack[]								= "vvm1_copyStack";
	const s8		cgcVvmV1CopyRegisters[]							= "vvm1_copyRegisters";
	const s8		cgcVvmV1CopyGlobal[]							= "vvm1_copyGlobal";
	const s8		cgcVvmV1CopyTimer[]								= "vvm1_copyTimer";
	const s8		cgcVvmV1CopyScreen[]							= "vvm1_copyScreen";
	const s8		cgcVvmV1CopyCanvas[]							= "vvm1_copyCanvas";

	const s8		cgcVvmV1CopySnippetTS[]							= "vvm1_copySnippetTS";
	const s8		cgcVvmV1CopySnippetParent[]						= "vvm1_copySnippetParent";
	const s8		cgcVvmV1CopySnippetSS[]							= "vvm1_copySnippetSS";
	const s8		cgcVvmV1CopyDynamicSnippet[]					= "vvm1_copyDynamicSnippet";

	const s8		cgcVvmV1SnippetCompile[]						= "vvm1_snippetCompile";
	const s8		cgcVvmV1SnippetCompileLine[]					= "vvm1_snippetCompileLine";
	const s8		cgcVvmV1DynSnipCompileLine[]					= "vvm1_dynSnipCompileLine";
	const s8		cgcVvmV1SnippetDelete[]							= "vvm1_snippetDelete";
	const s8		cgcVvmV1SnippetUpdate[]							= "vvm1_snippetUpdate";
	const s8		cgcVvmV1SnippetAppend[]							= "vvm1_snippetAppend";
	const s8		cgcVvmV1DynamicSnippetDelete[]					= "vvm1_dynamicSnippetDelete";
	const s8		cgcVvmV1DynamicSnippetUpdate[]					= "vvm1_dynamicSnippetUpdate";
	const s8		cgcVvmV1DynamicSnippetAppend[]					= "vvm1_dynamicSnippetAppend";
	const s8		cgcVvmV1FlushChangesToBxml[]					= "vvm1_flushChangesToBxml";

	const s8		cgcVvmV1CreateThread[]							= "vvm1_createThread";
	const s8		cgcVvmV1MessageBox[]							= "vvm1_messageBox";

	const s8		cgcVvmV1EnableBreakpoints[]						= "vvm1_enableBreakpoints";
	const s8		cgcVvmV1DisableBreakpoints[]					= "vvm1_disableBreakpoints";




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
	u64				(CALLTYPE *vvm_debugger)							(s8* functionName);
	s8*				(CALLTYPE *vvm_getLanguage)							(u32* tnLength);
	s8*				(CALLTYPE *vvm_loadResourceAsciiText)				(u32 tnResourceNumber);
	void			(CALLTYPE *vvm_resourcePrintf)						(u32 tnResourceNumber);
	u64				(CALLTYPE *vvm_requestUniqueID)						(void);
	u64				(CALLTYPE *vvm_connect)								(u64 id, s8* tcPath);
	u64				(CALLTYPE *vvm_connectRemote)						(u64 id, s8* tcPath, s8* ipAddressOrMachineName);
	u64				(CALLTYPE *vvm_getNextUniqueId)						(void);

	// For information about the VM
	void			(CALLTYPE *vvm_copyProgramList)						(u64 id, SProgram** list, u32* count);
	void			(CALLTYPE *vvm_programCopyScreensList)				(u64 id, SProgram* program, SScreen**    list, u32* count);
	void			(CALLTYPE *vvm_programCopyGlobalsList)				(u64 id, SProgram* program, SVariable**  list, u32* count);
	void			(CALLTYPE *vvm_programCopySnippetsList)				(u64 id, SProgram* program, SSnipExec**   list, u32* count);
	void			(CALLTYPE *vvm_programCopyDynamicSnippetsList)		(u64 id, SProgram* program, SDynSnip**   list, u32* count);
	void			(CALLTYPE *vvm_programCopyTimersList)				(u64 id, SProgram* program, STimer**     list, u32* count);
	void			(CALLTYPE *vvm_programCopyThreadsList)				(u64 id, SProgram* program, SThread**    list, u32* count);

	// For controlling the VM
	u64				(CALLTYPE *vvm_programPause)						(u64 id, SProgram* program);
	u64				(CALLTYPE *vvm_programResume)						(u64 id, SProgram* program, bool singleStep);
	u64				(CALLTYPE *vvm_programTerminate)					(u64 id, SProgram* program);
	u64				(CALLTYPE *vvm_threadPause)							(u64 id, SThread* thread);
	u64				(CALLTYPE *vvm_threadResume)						(u64 id, SThread* thread, bool singleStep);
	u64				(CALLTYPE *vvm_threadTerminate)						(u64 id, SThread* thread);
	void			(CALLTYPE *vvm_terminateVvm)						(u64 id, bool tlPolitely);

	// Breakpoints
	void			(CALLTYPE *vvm_getBreakpointList)					(u64 id, SBreakpoint** root, u32* count);
	SBreakpoint*   	(CALLTYPE *vvm_breakpointSet)						(u64 id, SSnipExec* snippet, SLine* line, SBreakCond* bc, bool enable);
	bool			(CALLTYPE *vvm_breakpointClear)						(u64 id, SBreakpoint* bp);

	// For retrieving running content (thread may be temporarily paused upon request to retrieve data, and resumes after fill)
	bool			(CALLTYPE *vvm_copyProgram)							(u64 id, SProgram*   program,   SProgram**   copy);
	bool			(CALLTYPE *vvm_copyThread)							(u64 id, SThread*    thread,    SThread**    copy);
	bool			(CALLTYPE *vvm_copyStack)							(u64 id, SThread*    thread,    SStack**     copy);
	bool			(CALLTYPE *vvm_copyRegisters)						(u64 id, SThread*    thread,    SRegs** copy);
	bool			(CALLTYPE *vvm_copyGlobal)							(u64 id, SVariable*  global,    SVariable**  copy);
	bool			(CALLTYPE *vvm_copyTimer)							(u64 id, STimer*     timer,     STimer**     copy);
	bool			(CALLTYPE *vvm_copyScreen)							(u64 id, SScreen*    screen,    SScreen**    copyScreen,    SCanvas** copyCanvas);
	bool			(CALLTYPE *vvm_copyCanvas)							(u64 id, SCanvas*    canvas,    SScreen**    copy);

	// The following snippets are copied with original source code lines for each snippet
	bool			(CALLTYPE *vvm_copySnippetTS)						(u64 id, SThread*  snippet,    SSnipExec** copyS,   SDynSnip* copyDS,   bool* isDynSnip);
	bool			(CALLTYPE *vvm_copySnippetParent)					(u64 id, SSnipExec* snippet,    SSnipExec** copyS,   SDynSnip* copyDS,   bool* isDynSnip);
	bool			(CALLTYPE *vvm_copySnippetSS)						(u64 id, SSnipExec* snippet,    SSnipExec** copy);
	bool			(CALLTYPE *vvm_copyDynamicSnippet)					(u64 id, SDynSnip* dynSnippet, SDynSnip** copy);

	// For edit-and-continue (SUpSnip is SSnippet with _prevLine member, indicating the relationship of the old snippet code to the new snippet code)
	SUpSnip*		(CALLTYPE *vvm_snippetCompile)						(u64 id, SLine* firstLineOfSnippetSourceCode);
	SUpLine*		(CALLTYPE *vvm_snippetCompileLine)					(u64 id, SSnipExec* snippet,    SLine* originalLineOfSnippetSourceCode, SLine* replacementLineOfSnippetSourceCode, bool commitIfCompilesOkay);
	SUpLine*		(CALLTYPE *vvm_dynSnipCompileLine)					(u64 id, SDynSnip* dynSnippet, SLine* originalLineOfDynSnipSourceCode, SLine* replacementLineOfDynSnipSourceCode, bool commitIfCompilesOkay);
	bool			(CALLTYPE *vvm_snippetDelete)						(u64 id, SSnipExec* snippet);
	bool			(CALLTYPE *vvm_snippetUpdate)						(u64 id, SSnipExec* snippet,    SUpSnip* newSnippet);
	u64				(CALLTYPE *vvm_snippetAppend)						(u64 id, SSnipExec* snippet);
	bool			(CALLTYPE *vvm_dynamicSnippetDelete)				(u64 id, SDynSnip* dynSnippet);
	bool			(CALLTYPE *vvm_dynamicSnippetUpdate)				(u64 id, SDynSnip* dynSnippet, SUpSnip* newSnippet);
	u64				(CALLTYPE *vvm_dynamicSnippetAppend)				(u64 id, SDynSnip* dynSnippet);
	bool			(CALLTYPE *vvm_flushChangesToBxml)					(u64 id, SProgram* program);

	// For general access and control
	u64				(CALLTYPE *vvm_createThread)						(u64 id, void* functionAddress, u32 tnParameter);
	u64				(CALLTYPE *vvm_messageBox)							(u64 id, s8* tcText, s8* tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);

	void			(CALLTYPE *vvm_enableBreakpoints)					(void);
	void			(CALLTYPE *vvm_disableBreakpoints)					(void);




//////////
//
// List of functions and their corresponding names.  Used in iLoadVvmFunctions().
// NOTE:  The items in this list must appear in the same order as their definitions above
//
//////
#ifdef _VVM_COMPILING
	void* gVvmFunctions[] =
	{
		(void *)&vvm1_debugger,									(void *)cgcVvmV1Debugger,
		(void *)&vvm1_getLanguage,								(void *)cgcVvmV1GetLanguage,
		(void *)&vvm1_loadResourceAsciiText,					(void *)cgcVvmV1LoadResourceAsciiText,
		(void *)&vvm1_resourcePrintf,							(void *)cgcVvmV1ResourcePrintf,
		(void *)&vvm1_requestUniqueID,							(void *)cgcVvmV1RequestUniqueId,
		(void *)&vvm1_connect,									(void *)cgcVvmV1Connect,
		(void *)&vvm1_connectRemote,							(void *)cgcVvmV1ConnectRemote,
		(void *)&vvm1_getNextUniqueId,							(void *)cgcVvmV1GetNextUniqueId,

		(void *)&vvm1_copyProgramList,							(void *)cgcVvmV1CopyProgramList,
		(void *)&vvm1_programCopyScreensList,					(void *)cgcVvmV1ProgramCopyScreensList,
		(void *)&vvm1_programCopyGlobalsList,					(void *)cgcVvmV1ProgramCopyGlobalsList,
		(void *)&vvm1_programCopySnippetsList,					(void *)cgcVvmV1ProgramCopySnippetsList,
		(void *)&vvm1_programCopyDynamicSnippetsList,			(void *)cgcVvmV1ProgramCopyDynamicSnippetsList,
		(void *)&vvm1_programCopyTimersList,					(void *)cgcVvmV1ProgramCopyTimersList,
		(void *)&vvm1_programCopyThreadsList,					(void *)cgcVvmV1ProgramCopyThreadsList,

		(void *)&vvm1_programPause,								(void *)cgcVvmV1ProgramPause,
		(void *)&vvm1_programResume,							(void *)cgcVvmV1ProgramResume,
		(void *)&vvm1_programTerminate,							(void *)cgcVvmV1ProgramTerminate,
		(void *)&vvm1_threadPause,								(void *)cgcVvmV1ThreadPause,
		(void *)&vvm1_threadResume,								(void *)cgcVvmV1ThreadResume,
		(void *)&vvm1_threadTerminate,							(void *)cgcVvmV1ThreadTerminate,
		(void *)&vvm1_terminateVvm,								(void *)cgcVvmV1TerminateVvm,

		(void *)&vvm1_getBreakpointList,						(void *)cgcVvmV1GetBreakpointList,
		(void *)&vvm1_breakpointSet,							(void *)cgcVvmV1BreakpointSet,
		(void *)&vvm1_breakpointClear,							(void *)cgcVvmV1BreakpointClear,

		(void *)&vvm1_copyProgram,								(void *)cgcVvmV1CopyProgram,
		(void *)&vvm1_copyThread,								(void *)cgcVvmV1CopyThread,
		(void *)&vvm1_copyStack,								(void *)cgcVvmV1CopyStack,
		(void *)&vvm1_copyRegisters,							(void *)cgcVvmV1CopyRegisters,
		(void *)&vvm1_copyGlobal,								(void *)cgcVvmV1CopyGlobal,
		(void *)&vvm1_copyTimer,								(void *)cgcVvmV1CopyTimer,
		(void *)&vvm1_copyScreen,								(void *)cgcVvmV1CopyScreen,
		(void *)&vvm1_copyCanvas,								(void *)cgcVvmV1CopyCanvas,

		(void *)&vvm1_copySnippetTS,							(void *)cgcVvmV1CopySnippetTS,
		(void *)&vvm1_copySnippetParent,						(void *)cgcVvmV1CopySnippetParent,
		(void *)&vvm1_copySnippetSS,							(void *)cgcVvmV1CopySnippetSS,
		(void *)&vvm1_copyDynamicSnippet,						(void *)cgcVvmV1CopyDynamicSnippet,

		(void *)&vvm1_snippetCompile,							(void *)cgcVvmV1SnippetCompile,
		(void *)&vvm1_snippetCompileLine,						(void *)cgcVvmV1SnippetCompileLine,
		(void *)&vvm1_dynSnipCompileLine,						(void *)cgcVvmV1DynSnipCompileLine,
		(void *)&vvm1_snippetDelete,							(void *)cgcVvmV1SnippetDelete,
		(void *)&vvm1_snippetUpdate,							(void *)cgcVvmV1SnippetUpdate,
		(void *)&vvm1_snippetAppend,							(void *)cgcVvmV1SnippetAppend,
		(void *)&vvm1_dynamicSnippetDelete,						(void *)cgcVvmV1DynamicSnippetDelete,
		(void *)&vvm1_dynamicSnippetUpdate,						(void *)cgcVvmV1DynamicSnippetUpdate,
		(void *)&vvm1_dynamicSnippetAppend,						(void *)cgcVvmV1DynamicSnippetAppend,
		(void *)&vvm1_flushChangesToBxml,						(void *)cgcVvmV1FlushChangesToBxml,

		(void *)&vvm1_createThread,								(void *)cgcVvmV1CreateThread,
		(void *)&vvm1_messageBox,								(void *)cgcVvmV1MessageBox,

		(void *)&vvm1_enableBreakpoints,						(void *)cgcVvmV1EnableBreakpoints,
		(void *)&vvm1_disableBreakpoints,						(void *)cgcVvmV1DisableBreakpoints
	};
#else
	void* gVvmFunctions[] =
	{
		(void *)&vvm_debugger,									(void *)cgcVvmV1Debugger,
		(void *)&vvm_getLanguage,								(void *)cgcVvmV1GetLanguage,
		(void *)&vvm_loadResourceAsciiText,						(void *)cgcVvmV1LoadResourceAsciiText,
		(void *)&vvm_resourcePrintf,							(void *)cgcVvmV1ResourcePrintf,
		(void *)&vvm_requestUniqueID,							(void *)cgcVvmV1RequestUniqueId,
		(void *)&vvm_connect,									(void *)cgcVvmV1Connect,
		(void *)&vvm_connectRemote,								(void *)cgcVvmV1ConnectRemote,
		(void *)&vvm_getNextUniqueId,							(void *)cgcVvmV1GetNextUniqueId,

		(void *)&vvm_copyProgramList,							(void *)cgcVvmV1CopyProgramList,
		(void *)&vvm_programCopyScreensList,					(void *)cgcVvmV1ProgramCopyScreensList,
		(void *)&vvm_programCopyGlobalsList,					(void *)cgcVvmV1ProgramCopyGlobalsList,
		(void *)&vvm_programCopySnippetsList,					(void *)cgcVvmV1ProgramCopySnippetsList,
		(void *)&vvm_programCopyDynamicSnippetsList,			(void *)cgcVvmV1ProgramCopyDynamicSnippetsList,
		(void *)&vvm_programCopyTimersList,						(void *)cgcVvmV1ProgramCopyTimersList,
		(void *)&vvm_programCopyThreadsList,					(void *)cgcVvmV1ProgramCopyThreadsList,

		(void *)&vvm_programPause,								(void *)cgcVvmV1ProgramPause,
		(void *)&vvm_programResume,								(void *)cgcVvmV1ProgramResume,
		(void *)&vvm_programTerminate,							(void *)cgcVvmV1ProgramTerminate,
		(void *)&vvm_threadPause,								(void *)cgcVvmV1ThreadPause,
		(void *)&vvm_threadResume,								(void *)cgcVvmV1ThreadResume,
		(void *)&vvm_threadTerminate,							(void *)cgcVvmV1ThreadTerminate,
		(void *)&vvm_terminateVvm,								(void *)cgcVvmV1TerminateVvm,

		(void *)&vvm_getBreakpointList,							(void *)cgcVvmV1GetBreakpointList,
		(void *)&vvm_breakpointSet,								(void *)cgcVvmV1BreakpointSet,
		(void *)&vvm_breakpointClear,							(void *)cgcVvmV1BreakpointClear,

		(void *)&vvm_copyProgram,								(void *)cgcVvmV1CopyProgram,
		(void *)&vvm_copyThread,								(void *)cgcVvmV1CopyThread,
		(void *)&vvm_copyStack,									(void *)cgcVvmV1CopyStack,
		(void *)&vvm_copyRegisters,								(void *)cgcVvmV1CopyRegisters,
		(void *)&vvm_copyGlobal,								(void *)cgcVvmV1CopyGlobal,
		(void *)&vvm_copyTimer,									(void *)cgcVvmV1CopyTimer,
		(void *)&vvm_copyScreen,								(void *)cgcVvmV1CopyScreen,
		(void *)&vvm_copyCanvas,								(void *)cgcVvmV1CopyCanvas,

		(void *)&vvm_copySnippetTS,								(void *)cgcVvmV1CopySnippetTS,
		(void *)&vvm_copySnippetParent,							(void *)cgcVvmV1CopySnippetParent,
		(void *)&vvm_copySnippetSS,								(void *)cgcVvmV1CopySnippetSS,
		(void *)&vvm_copyDynamicSnippet,						(void *)cgcVvmV1CopyDynamicSnippet,

		(void *)&vvm_snippetCompile,							(void *)cgcVvmV1SnippetCompile,
		(void *)&vvm_snippetCompileLine,						(void *)cgcVvmV1SnippetCompileLine,
		(void *)&vvm_dynSnipCompileLine,						(void *)cgcVvmV1DynSnipCompileLine,
		(void *)&vvm_snippetDelete,								(void *)cgcVvmV1SnippetDelete,
		(void *)&vvm_snippetUpdate,								(void *)cgcVvmV1SnippetUpdate,
		(void *)&vvm_snippetAppend,								(void *)cgcVvmV1SnippetAppend,
		(void *)&vvm_dynamicSnippetDelete,						(void *)cgcVvmV1DynamicSnippetDelete,
		(void *)&vvm_dynamicSnippetUpdate,						(void *)cgcVvmV1DynamicSnippetUpdate,
		(void *)&vvm_dynamicSnippetAppend,						(void *)cgcVvmV1DynamicSnippetAppend,
		(void *)&vvm_flushChangesToBxml,						(void *)cgcVvmV1FlushChangesToBxml,

		(void *)&vvm_createThread,								(void *)cgcVvmV1CreateThread,
		(void *)&vvm_messageBox,								(void *)cgcVvmV1MessageBox,

		(void *)&vvm_enableBreakpoints,							(void *)cgcVvmV1EnableBreakpoints,
		(void *)&vvm_disableBreakpoints,						(void *)cgcVvmV1DisableBreakpoints
	};
#endif
	u32 gVvmFunctionCount = sizeof(gVvmFunctions) / (2 * sizeof(void*));




//////////
//
// Called once to load all the gVvmFunctions[] at startup.
//
//////
	void** iLoadVvmFunctionsFromVVM(void** tnFuncAddress)
	{
		u32			lnI;
		s8*			lcFuncName;
		void*		lnAddress;
		void**		lnFuncAddress;
		s8			buffer[1024];


		// Grab the address of the VVM interface for function address requests
		lnFuncAddress	= (void**)&vvm_debuggerInterface;
		*lnFuncAddress	= (void*)tnFuncAddress;

		
		// Now, repeatedly call back that address with the request to all of the function addresses
		for (lnI = 0; lnI < gVvmFunctionCount; lnI++)
		{
			// Grab the details of this entry
			tnFuncAddress	= (void**)gVvmFunctions[(lnI * 2) + 0];						// Grab the indirect address to store
			lcFuncName		= (s8*)   gVvmFunctions[(lnI * 2) + 1];						// Grab the function name to request

			// Ask the VVM for this specific function location
			lnAddress = (void*)vvm_debuggerInterface(lcFuncName);						// We only call the indicated callback to obtain our portal for v1 functions

			// Process the result
			if (!lnAddress)
			{
				// The specified functionality is not available
				// Note:  By design, this should never happen.  It is the result of a programming error.
				sprintf_s(buffer, sizeof(buffer), "Error accessing: %s\000", lcFuncName);
				MessageBoxA(NULL, buffer, "VVM Initialization Error", MB_OK);
				// We need all the functions we request, not just some of them
				return((void**)-1);		// Indicate a fatal error
			}
			// If we get here, this function was found and we can store it
			*tnFuncAddress = lnAddress;
		}
		// When we get here, we've made the full connection to the VVM
		return(tnFuncAddress);
	}
