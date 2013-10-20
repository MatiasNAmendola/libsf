//////////
//
// /libsf/vvm/vvm/vvm_debv1.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     September 24, 2012 - Initial creation
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
//
// Returns the debugger functions for v1 of the VVM debugger interface
//
//////
	u64 CALLTYPE vvm1_debugger(s8* tcFunctionName)
    {
		return(vvm_debuggerInterface(tcFunctionName));
    }




//////////
//
// Return the language indicated on the command line with the -r: flag
//
//////
	s8* CALLTYPE vvm1_getLanguage(u32* tnLength)
	{
		// Store the length of the name
		if (tnLength)
			*tnLength = strlen(gsVvm.gcVvmResourceLang);

		// Return a pointer to the language
		return(gsVvm.gcVvmResourceLang);
	}




//////////
//
// Load a resource string from the vmm resource
//
//////
	s8* CALLTYPE vvm1_loadResourceAsciiText(u32 tnResourceNumber)
	{
		u32					lnLength;
		SVvmmcResourceText*	lr;
		s8					buffer[1024];
		SStartEndCallback	cb;


		// Try to find the resource we've already loaded
		cb._func	= (u64)&iivvm_loadResourceAsciiTextCallback;
		cb.extra	= tnResourceNumber;
		lr = (SVvmmcResourceText*)oss_SEChain_searchByCallback(&gsVvm.gseRootResourceTexts, &cb);
		if (lr)
			return(lr->text);		// It's already been loaded

		// Try to locate it
		if (!LoadStringA(gsVvm.ghVvmResourceDll, tnResourceNumber, buffer, sizeof(buffer)))
			return((s8*)cgcUnableToLocateResource);		// Use the default failure string

		// Allocate the new item
		lr = (SVvmmcResourceText*)oss_SEChain_append(&gsVvm.gseRootResourceTexts, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SVvmResourceText), _COMMON_START_END_BLOCK_SIZE, NULL);
		if (lr)
		{
			// Store the resource information
			lr->resourceNumber	= tnResourceNumber;

			// Duplicate the loaded string
			lnLength			= strlen(buffer) + 1;
			lr->text			= (s8*)oss_alloc(lnLength, true);
			if (lr->text)		memcpy(lr->text, buffer, lnLength - 1);

			// All done
			return(lr->text);
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Called to execute a resourcePrintf() on a localized resource number
//
//////
	void CALLTYPE vvm1_resourcePrintf(u32 tnResourceNumber)
	{
		ivvm_resourcePrintf(tnResourceNumber);
	}




//////////
//
// Returns a guaranteed thread-safe unique ID to this running VVM instance
//
//////
	u64 CALLTYPE vvm1_requestUniqueID(void)
    {
		return(0);
    }




//////////
//
// Connects to the specified local running program
//
//////
	u64 CALLTYPE vvm1_connect(u64 id, s8* tcPath)
    {
		return(0);
    }




//////////
//
// Connects to the specified remote running program at the specified ip address or machine
//
//////
	u64 CALLTYPE vvm1_connectRemote(u64 id, s8* tcPath, s8* ipAddressOrMachineName)
    {
		return(0);
    }




//////////
//
// Returns the OSS-assigned next unique ID
//
//////
	u64 CALLTYPE vvm1_getNextUniqueId(void)
	{
		return(oss_getNextUniqueId());
	}




//////////
//
// Returns a list of running programs.
//
//////
	void CALLTYPE vvm1_copyProgramList(u64 id, SProgram** list, u32* count)
    {
    }




//////////
//
// Returns a list of all screens associated with the specified program.
//
//////
	void CALLTYPE vvm1_programCopyScreensList(u64 id, SProgram* program, SScreen**    list, u32* count)
    {
    }




//////////
//
// Returns a list of defined global variables for the specified program.
//
//////
	void CALLTYPE vvm1_programCopyGlobalsList(u64 id, SProgram* program, SVariable**  list, u32* count)
    {
    }




//////////
//
// Returns a list of snippets for the specified program.
//
//////
	void CALLTYPE vvm1_programCopySnippetsList(u64 id, SProgram* program, SSnipExec**   list, u32* count)
    {
    }




//////////
//
// Returns a list of dynamic snippets for the specified program.
//
//////
	void CALLTYPE vvm1_programCopyDynamicSnippetsList(u64 id, SProgram* program, SDynSnip**   list, u32* count)
    {
    }




//////////
//
// Returns a list of timers for the specified program.
//
//////
	void CALLTYPE vvm1_programCopyTimersList(u64 id, SProgram* program, STimer**     list, u32* count)
    {
    }




//////////
//
// Returns a list of threads for the specified program.
//
//////
	void CALLTYPE vvm1_programCopyThreadsList(u64 id, SProgram* program, SThread**    list, u32* count)
    {
    }




//////////
//
// Instructs the VVM to pause the specified program.
//
//////
	u64 CALLTYPE vvm1_programPause(u64 id, SProgram* program)
    {
		return(0);
    }




//////////
//
// Instructs the VVM to resume the specified program.
//
//////
	u64 CALLTYPE vvm1_programResume(u64 id, SProgram* program, bool singleStep)
    {
		return(0);
    }




//////////
//
// Instructs the VVM to terminate the specified program.
//
//////
	u64 CALLTYPE vvm1_programTerminate(u64 id, SProgram* program)
    {
		return(0);
    }




//////////
//
// Instructs the VVM to pause the specified thread.
//
//////
	u64 CALLTYPE vvm1_threadPause(u64 id, SThread* thread)
    {
		return(0);
    }




//////////
//
// Instructs the VVM to resume the specified thread.
//
//////
	u64 CALLTYPE vvm1_threadResume(u64 id, SThread* thread, bool singleStep)
    {
		return(0);
    }




//////////
//
// Instructs the VVM to terminate the specified thread.
//
//////
	u64 CALLTYPE vvm1_threadTerminate(u64 id, SThread* thread)
    {
		return(0);
    }




//////////
//
// Asks the VVM to terminate itself (possibly politely).
//
//////
	void CALLTYPE vvm1_terminateVvm(u64 id, bool tlPolitely)
    {
    }




//////////
//
// Gets a list of all active and inactive breakpoints.
//
//////
	void CALLTYPE vvm1_getBreakpointList(u64 id, SBreakpoint** root, u32* count)
    {
    }




//////////
//
// Sets a new breakpoint.
//
//////
	SBreakpoint* CALLTYPE vvm1_breakpointSet(u64 id, SSnipExec* snippet, SLine* line, SBreakCond* bc, bool enable)
    {
		return(NULL);
    }




//////////
//
// Clears the indicated breakpoint.
//
//////
	bool CALLTYPE vvm1_breakpointClear(u64 id, SBreakpoint* bp)
    {
		return(false);
    }




//////////
//
// Copies the current state of the program to a duplicate variable for display in a debugger,
// or saving out to a disk file as a snapshot, for example.
//
// Note:  The program will be paused for the duration of this event.
//
//////
	bool CALLTYPE vvm1_copyProgram(u64 id, SProgram*   program, SProgram**   copy)
    {
		return(false);
    }




//////////
//
// Copies the current state of the thread to a duplicate variable for display in a debugger,
// or saving out to a disk file as a snapshot, for example.
//
// Note:  The program will be paused for the duration of this event.
//
//////
	bool CALLTYPE vvm1_copyThread(u64 id, SThread*    thread, SThread**    copy)
    {
		return(false);
    }




//////////
//
// Copies the current state of the program stack to a duplicate variable for display in a
// debugger, or saving out to a disk file as a snapshot, for example.
//
// Note:  The program will be paused for the duration of this event.
//
//////
	bool CALLTYPE vvm1_copyStack(u64 id, SThread*    thread, SStack**     copy)
    {
		return(false);
    }




//////////
//
// Copies the current state of the program registers to a duplicate variable for display
// in a debugger, or saving out to a disk file as a snapshot, for example.
//
// Note:  The program will be paused for the duration of this event.
//
//////
	bool CALLTYPE vvm1_copyRegisters(u64 id, SThread*    thread, SRegs** copy)
    {
		return(false);
    }




//////////
//
// Copies the current state of the global variable to a duplicate variable for display
// in a debugger, or saving out to a disk file as a snapshot, for example.
//
// Note:  The program will be paused for the duration of this event.
//
//////
	bool CALLTYPE vvm1_copyGlobal(u64 id, SVariable*  global, SVariable**  copy)
    {
		return(false);
    }




//////////
//
// Copies the current state of the program timer to a duplicate variable for display in
// a debugger, or saving out to a disk file as a snapshot, for example.
//
// Note:  The program will be paused for the duration of this event.
//
//////
	bool CALLTYPE vvm1_copyTimer(u64 id, STimer*     timer, STimer**     copy)
    {
		return(false);
    }




//////////
//
// Copies the current state of the indicated screen (as it literally appears at the time of
// the call) to a duplicate screen for display in a debugger, or saving out to a disk file,
// for example.
//
//////
	bool CALLTYPE vvm1_copyScreen(u64 id, SScreen*    screen, SScreen**    copyScreen, SCanvas** copyCanvas)
    {
		return(false);
    }




//////////
//
// Copies the current state of the indicated canvas (as it literally exists at the time of
// the call) to a duplicate canvas for display in a debugger, or saving out to a disk file,
// for example.
//
//////
	bool CALLTYPE vvm1_copyCanvas(u64 id, SCanvas*    canvas, SScreen**    copy)
    {
		return(false);
    }




//////////
//
// Copies the currently executing snippet or dynamic snippet for the specified thread.
//
//////
	bool CALLTYPE vvm1_copySnippetTS(u64 id, SThread*  thread, SSnipExec** copyS, SDynSnip* copyDS, bool* isDynSnip)
    {
		return(false);
    }




//////////
//
// Copies the parent snippet or dynamic snippet for the running snippet.
//
//////
	bool CALLTYPE vvm1_copySnippetParent(u64 id, SSnipExec* snippet, SSnipExec** copyS, SDynSnip* copyDS, bool* isDynSnip)
    {
		return(false);
    }




//////////
//
// Copies the specified snippet to a duplicate that can be used by the debugger.
//
//////
	bool CALLTYPE vvm1_copySnippetSS(u64 id, SSnipExec* snippet, SSnipExec** copy)
    {
		return(false);
    }




//////////
//
// Copies the specified dynamic snippet to a duplicate that can be used by the debugger.
//
//////
	bool CALLTYPE vvm1_copyDynamicSnippet(u64 id, SDynSnip* dynSnippet, SDynSnip** copy)
    {
		return(false);
    }




//////////
//
// Asks the VVM to coordinate with the program's loaded DLLs to compile the indicated snippet.
//
//////
	// For edit-and-continue (SUpSnip is SSnippet with _prevLine member, indicating the relationship of the old snippet code to the new snippet code)
	SUpSnip* CALLTYPE vvm1_snippetCompile(u64 id, SLine* firstLineOfSnippetSourceCode)
    {
		return(NULL);
    }




//////////
//
// Asks the VVM to coordinate with the program's loaded DLLs to compile the indicated single
// line of code.
//
//////
	SUpLine* CALLTYPE vvm1_snippetCompileLine(u64 id, SSnipExec* snippet, SLine* originalLineOfSnippetSourceCode, SLine* replacementLineOfSnippetSourceCode, bool commitIfCompilesOkay)
    {
		return(NULL);
    }




//////////
//
// Asks the VVM to coordinate with the program's loaded DLLs to compile the indicated dynamic
// snippet line.
//
//////
	SUpLine* CALLTYPE vvm1_dynSnipCompileLine(u64 id, SDynSnip* dynSnippet, SLine* originalLineOfDynSnipSourceCode, SLine* replacementLineOfDynSnipSourceCode, bool commitIfCompilesOkay)
    {
		return(NULL);
    }




//////////
//
// Asks the VVM to delete the indicated snippet.
//
//////
	bool CALLTYPE vvm1_snippetDelete(u64 id, SSnipExec* snippet)
    {
		return(false);
    }




//////////
//
// Asks the VVM to update the indicated snippet, to swap it out with the new snippet.
//
//////
	bool CALLTYPE vvm1_snippetUpdate(u64 id, SSnipExec* snippet, SUpSnip* newSnippet)
    {
		return(false);
    }




//////////
//
// Asks the VVM to append the indicated snippet to the list of loaded snippets.
//
//////
	u64 CALLTYPE vvm1_snippetAppend(u64 id, SSnipExec* snippet)
    {
		return(0);
    }




//////////
//
// Asks the VVM to delete the indicated dynamic snippet.
//
//////
	bool CALLTYPE vvm1_dynamicSnippetDelete(u64 id, SDynSnip* dynSnippet)
    {
		return(false);
    }




//////////
//
// Asks the VVM to update the indicated snippet, to swap it out with the new dynamic snippet.
//
//////
	bool CALLTYPE vvm1_dynamicSnippetUpdate(u64 id, SDynSnip* dynSnippet, SUpSnip* newSnippet)
    {
		return(false);
    }




//////////
//
// Asks the VVM to append the the indicated dynamic snippet to the end of the list of
// loaded dynamic snippets.
//
//////
	u64 CALLTYPE vvm1_dynamicSnippetAppend(u64 id, SDynSnip* dynSnippet)
    {
		return(0);
    }




//////////
//
// Asks the VVM to save all changes made since the program was loaded to disk, thereby making
// the current edits permanent on disk to the original program.bxml file.
//
//////
	bool CALLTYPE vvm1_flushChangesToBxml(u64 id, SProgram* program)
    {
		return(false);
    }




//////////
//
// Asks the VVM to terminate itself (possibly politely).
//
//////
	u64 CALLTYPE vvm1_createThread(u64 id, void* functionAddress, u32 tnParameter)
    {
		return(0);
    }




//////////
//
// Asks the VVM to display an OSS-specific MessageBox
//
//////
	u64 CALLTYPE vvm1_messageBox(u64 id, s8* tcText, s8* tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel)
    {
		return(oss_messageBox(id, tcText, tcCaption, tlYes, tlNo, tlOk, tlRetry, tlCancel));
    }





//////////
//
// Used for internal debugging.
//
//////
	void CALLTYPE vvm1_enableBreakpoints(u64 id)
    {
    }




//////////
//
// Used for internal debugging.
//
//////
	void CALLTYPE vvm1_disableBreakpoints(u64 id)
    {
    }
