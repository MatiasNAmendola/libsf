//////////
//
// /libsf/vvm/vvm/vvm_debv1.cpp
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
//     Sep.24.2012 - Initial creation
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
// Return the language indicated on the command line with the -r: flag
//
//////
	s8* CALLTYPE vvm_getLanguage(u32* tnLength)
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
	s8* CALLTYPE vvm_loadResourceAsciiText(u32 tnResourceNumber)
	{
		u32					lnLength;
		SVvmmcResourceText*	lr;
		s8					buffer[1024];
		SStartEndCallback	cb;


		// Try to find the resource we've already loaded
		cb._func	= (u64)&iivvm_loadResourceAsciiTextCallback;
		cb.extra	= tnResourceNumber;
		lr = (SVvmmcResourceText*)vvm_SEChain_searchByCallback(&gsVvm.gseRootResourceTexts, &cb);
		if (lr)
			return(lr->text);		// It's already been loaded

		// Try to locate it
		if (!LoadStringA(gsVvm.ghVvmResourceDll, tnResourceNumber, buffer, sizeof(buffer)))
			return((s8*)cgcUnableToLocateResource);		// Use the default failure string

		// Allocate the new item
		lr = (SVvmmcResourceText*)vvm_SEChain_append(&gsVvm.gseRootResourceTexts, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SVvmResourceText), _COMMON_START_END_BLOCK_SIZE, NULL);
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
	void CALLTYPE vvm_resourcePrintf(u32 tnResourceNumber)
	{
		ivvm_resourcePrintf(tnResourceNumber);
	}




//////////
//
// Returns a guaranteed thread-safe unique ID to this running VVM instance
//
//////
	u64 CALLTYPE vvm_requestUniqueID(void)
    {
		return(0);
    }




//////////
//
// Connects to the specified local running program
//
//////
	u64 CALLTYPE vvm_connect(u64 id, s8* tcPath)
    {
		return(0);
    }




//////////
//
// Connects to the specified remote running program at the specified ip address or machine
//
//////
	u64 CALLTYPE vvm_connectRemote(u64 id, s8* tcPath, s8* ipAddressOrMachineName)
    {
		return(0);
    }




//////////
//
// Returns the OSS-assigned next unique ID
//
//////
	u64 CALLTYPE vvm_getNextUniqueId(void)
	{
		return(ivvm_getNextUniqueId());
	}




//////////
//
// Returns a list of running programs.
//
//////
	void CALLTYPE vvm_copyProgramList(u64 id, SProgram** list, u32* count)
    {
    }




//////////
//
// Returns a list of all screens associated with the specified program.
//
//////
	void CALLTYPE vvm_programCopyScreensList(u64 id, SProgram* program, SScreen**    list, u32* count)
    {
    }




//////////
//
// Returns a list of defined global variables for the specified program.
//
//////
	void CALLTYPE vvm_programCopyGlobalsList(u64 id, SProgram* program, SVariable**  list, u32* count)
    {
    }




//////////
//
// Returns a list of snippets for the specified program.
//
//////
	void CALLTYPE vvm_programCopySnippetsList(u64 id, SProgram* program, SSnipExec**   list, u32* count)
    {
    }




//////////
//
// Returns a list of dynamic snippets for the specified program.
//
//////
	void CALLTYPE vvm_programCopyDynamicSnippetsList(u64 id, SProgram* program, SDynSnip**   list, u32* count)
    {
    }




//////////
//
// Returns a list of timers for the specified program.
//
//////
	void CALLTYPE vvm_programCopyTimersList(u64 id, SProgram* program, STimer**     list, u32* count)
    {
    }




//////////
//
// Returns a list of threads for the specified program.
//
//////
	void CALLTYPE vvm_programCopyThreadsList(u64 id, SProgram* program, SThread**    list, u32* count)
    {
    }




//////////
//
// Instructs the VVM to pause the specified program.
//
//////
	u64 CALLTYPE vvm_programPause(u64 id, SProgram* program)
    {
		return(0);
    }




//////////
//
// Instructs the VVM to resume the specified program.
//
//////
	u64 CALLTYPE vvm_programResume(u64 id, SProgram* program, bool singleStep)
    {
		return(0);
    }




//////////
//
// Instructs the VVM to terminate the specified program.
//
//////
	u64 CALLTYPE vvm_programTerminate(u64 id, SProgram* program)
    {
		return(0);
    }




//////////
//
// Instructs the VVM to pause the specified thread.
//
//////
	u64 CALLTYPE vvm_threadPause(u64 id, SThread* thread)
    {
		return(0);
    }




//////////
//
// Instructs the VVM to resume the specified thread.
//
//////
	u64 CALLTYPE vvm_threadResume(u64 id, SThread* thread, bool singleStep)
    {
		return(0);
    }




//////////
//
// Instructs the VVM to terminate the specified thread.
//
//////
	u64 CALLTYPE vvm_threadTerminate(u64 id, SThread* thread)
    {
		return(0);
    }




//////////
//
// Asks the VVM to terminate itself (possibly politely).
//
//////
	void CALLTYPE vvm_terminateVvm(u64 id, bool tlPolitely)
    {
    }




//////////
//
// Gets a list of all active and inactive breakpoints.
//
//////
	void CALLTYPE vvm_getBreakpointList(u64 id, SBreakpoint** root, u32* count)
    {
    }




//////////
//
// Sets a new breakpoint.
//
//////
	SBreakpoint* CALLTYPE vvm_breakpointSet(u64 id, SSnipExec* snippet, SLine* line, SBreakCond* bc, bool enable)
    {
		return(NULL);
    }




//////////
//
// Clears the indicated breakpoint.
//
//////
	bool CALLTYPE vvm_breakpointClear(u64 id, SBreakpoint* bp)
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
	bool CALLTYPE vvm_copyProgram(u64 id, SProgram*   program, SProgram**   copy)
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
	bool CALLTYPE vvm_copyThread(u64 id, SThread*    thread, SThread**    copy)
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
	bool CALLTYPE vvm_copyStack(u64 id, SThread*    thread, SStack**     copy)
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
	bool CALLTYPE vvm_copyRegisters(u64 id, SThread*    thread, SRegs** copy)
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
	bool CALLTYPE vvm_copyGlobal(u64 id, SVariable*  global, SVariable**  copy)
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
	bool CALLTYPE vvm_copyTimer(u64 id, STimer*     timer, STimer**     copy)
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
	bool CALLTYPE vvm_copyScreen(u64 id, SScreen*    screen, SScreen**    copyScreen, SCanvas** copyCanvas)
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
	bool CALLTYPE vvm_copyCanvas(u64 id, SCanvas*    canvas, SScreen**    copy)
    {
		return(false);
    }




//////////
//
// Copies the currently executing snippet or dynamic snippet for the specified thread.
//
//////
	bool CALLTYPE vvm_copySnippetTS(u64 id, SThread*  thread, SSnipExec** copyS, SDynSnip* copyDS, bool* isDynSnip)
    {
		return(false);
    }




//////////
//
// Copies the parent snippet or dynamic snippet for the running snippet.
//
//////
	bool CALLTYPE vvm_copySnippetParent(u64 id, SSnipExec* snippet, SSnipExec** copyS, SDynSnip* copyDS, bool* isDynSnip)
    {
		return(false);
    }




//////////
//
// Copies the specified snippet to a duplicate that can be used by the debugger.
//
//////
	bool CALLTYPE vvm_copySnippetSS(u64 id, SSnipExec* snippet, SSnipExec** copy)
    {
		return(false);
    }




//////////
//
// Copies the specified dynamic snippet to a duplicate that can be used by the debugger.
//
//////
	bool CALLTYPE vvm_copyDynamicSnippet(u64 id, SDynSnip* dynSnippet, SDynSnip** copy)
    {
		return(false);
    }




//////////
//
// Asks the VVM to coordinate with the program's loaded DLLs to compile the indicated snippet.
//
//////
	// For edit-and-continue (SUpSnip is SSnippet with _prevLine member, indicating the relationship of the old snippet code to the new snippet code)
	SUpSnip* CALLTYPE vvm_snippetCompile(u64 id, SLine* firstLineOfSnippetSourceCode)
    {
		return(NULL);
    }




//////////
//
// Asks the VVM to coordinate with the program's loaded DLLs to compile the indicated single
// line of code.
//
//////
	SUpLine* CALLTYPE vvm_snippetCompileLine(u64 id, SSnipExec* snippet, SLine* originalLineOfSnippetSourceCode, SLine* replacementLineOfSnippetSourceCode, bool commitIfCompilesOkay)
    {
		return(NULL);
    }




//////////
//
// Asks the VVM to coordinate with the program's loaded DLLs to compile the indicated dynamic
// snippet line.
//
//////
	SUpLine* CALLTYPE vvm_dynSnipCompileLine(u64 id, SDynSnip* dynSnippet, SLine* originalLineOfDynSnipSourceCode, SLine* replacementLineOfDynSnipSourceCode, bool commitIfCompilesOkay)
    {
		return(NULL);
    }




//////////
//
// Asks the VVM to delete the indicated snippet.
//
//////
	bool CALLTYPE vvm_snippetDelete(u64 id, SSnipExec* snippet)
    {
		return(false);
    }




//////////
//
// Asks the VVM to update the indicated snippet, to swap it out with the new snippet.
//
//////
	bool CALLTYPE vvm_snippetUpdate(u64 id, SSnipExec* snippet, SUpSnip* newSnippet)
    {
		return(false);
    }




//////////
//
// Asks the VVM to append the indicated snippet to the list of loaded snippets.
//
//////
	u64 CALLTYPE vvm_snippetAppend(u64 id, SSnipExec* snippet)
    {
		return(0);
    }




//////////
//
// Asks the VVM to delete the indicated dynamic snippet.
//
//////
	bool CALLTYPE vvm_dynamicSnippetDelete(u64 id, SDynSnip* dynSnippet)
    {
		return(false);
    }




//////////
//
// Asks the VVM to update the indicated snippet, to swap it out with the new dynamic snippet.
//
//////
	bool CALLTYPE vvm_dynamicSnippetUpdate(u64 id, SDynSnip* dynSnippet, SUpSnip* newSnippet)
    {
		return(false);
    }




//////////
//
// Asks the VVM to append the the indicated dynamic snippet to the end of the list of
// loaded dynamic snippets.
//
//////
	u64 CALLTYPE vvm_dynamicSnippetAppend(u64 id, SDynSnip* dynSnippet)
    {
		return(0);
    }




//////////
//
// Asks the VVM to save all changes made since the program was loaded to disk, thereby making
// the current edits permanent on disk to the original program.bxml file.
//
//////
	bool CALLTYPE vvm_flushChangesToBxml(u64 id, SProgram* program)
    {
		return(false);
    }




//////////
//
// Asks the VVM to terminate itself (possibly politely).
//
//////
	u64 CALLTYPE vvm_createThread(u64 id, void* functionAddress, u32 tnParameter)
    {
		return(0);
    }




//////////
//
// Asks the VVM to display an OSS-specific MessageBox
//
//////
	u64 CALLTYPE vvm_messageBox(u64 id, s8* tcText, s8* tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel)
    {
		return(oss_messageBox(id, tcText, tcCaption, tlYes, tlNo, tlOk, tlRetry, tlCancel));
    }




//////////
//
// Initializes a new buffer to the default allocation size.
// No content is changed.
//
// Returns:  
//		Pointer to the point in the buffer where the
//////
	void CALLTYPE vvm_builderCreateAndInitialize(SBuilder** buffRoot, u32 tnAllocationBlockSize)
	{
		SBuilder*	buffNew;


		// Make sure our environment is sane
		if (buffRoot && tnAllocationBlockSize != 0)
		{
			buffNew = (SBuilder*)oss_alloc(sizeof(SBuilder), true);
			if (buffNew)
			{
				// Store the pointer
				*buffRoot = buffNew;

				// Make sure our allocation block size is at least 4KB
				tnAllocationBlockSize		= max(4096, tnAllocationBlockSize);

				// Allocate the data space
				buffNew->data				= (s8*)oss_alloc(tnAllocationBlockSize, true);

				// If we allocated, we're good
				if (buffNew->data)			buffNew->allocatedLength	= tnAllocationBlockSize;
				else						buffNew->allocatedLength	= 0;

				// Update the allocation size
				buffNew->allocateBlockSize	= tnAllocationBlockSize;
			}
		}
	}




//////////
//
// Appends the indicated text to the end of the buffer.
//
// Returns:  
//		Pointer to the point in the buffer where the text was inserted, can be used
//		for a furthering or continuance of this function embedded in a higher call.
//////
	s8* CALLTYPE vvm_builderAppendData(SBuilder* buffRoot, s8* tcData, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot)
		{
			// If they want us to populate the length, do so
			if (tnDataLength == -1)
				tnDataLength = (u32)vvm_scanForwardUntilCharacter(_csu8p(tcData), 0);

			// If there's anything to do, do it
			if (tnDataLength != 0)
			{
				// Make sure this much data will fit there in the buffer
				ivvm_bufferVerifySizeForNewBytes(buffRoot, tnDataLength);

				// If we're still valid, proceed with the copy
				if (buffRoot->data && tcData)
					vvm_memcpy(buffRoot->data + buffRoot->populatedLength - tnDataLength, tcData, tnDataLength);
			}
			// Indicate where the start of that buffer is
			return(buffRoot->data + buffRoot->populatedLength - tnDataLength);
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Called to allocate bytes in the builder, but not yet populate them with anything
//
//////
	s8* CALLTYPE vvm_builderAllocateBytes(SBuilder*	buffRoot, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot)
		{
			// Make sure this much data will fit there in the buffer
			if (tnDataLength != 0)
				ivvm_bufferVerifySizeForNewBytes(buffRoot, tnDataLength);
			
			// Indicate where the start of that buffer is
			return(buffRoot->data + buffRoot->populatedLength - tnDataLength);
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Specifies the size the buffer should be.  Either allocates up or down. No content
// is changed, however the buffer pointer value could be changed from oss_realloc().
// In addition, this function should not be used for resizing in general.  Simply call
// the vvm_builderAppendData() function and it will automatically resize if needed, as
// per the allocated block size.
//
//////
	void CALLTYPE vvm_builderSetSize(SBuilder* buffRoot, u32 tnBufferLength)
	{
		s8* lcNew;


		// Make sure our environment is sane
		if (buffRoot)
		{
			//////////
			// See if they want to make it whatever the populated size is
			//////
				if (tnBufferLength == -1)
					tnBufferLength = buffRoot->populatedLength;


			//////////
			// See if they're releasing everything
			//////
				if (tnBufferLength == 0)
				{
// TODO:  Untested code, breakpoint and examine
_asm int 3;
					//////////
					// They are freeing everything
					//////
						free(buffRoot->data);
						buffRoot->data				= NULL;
						buffRoot->populatedLength	= 0;
						buffRoot->allocatedLength	= 0;


				} else if (tnBufferLength != buffRoot->allocatedLength) {
					//////////
					// They are resizing
					//////
						lcNew = (s8*)oss_realloc(buffRoot->data, tnBufferLength);
						if (lcNew)
						{
							//////////
							// Set the allocated length
							//////
								buffRoot->data				= lcNew;
								buffRoot->allocatedLength	= tnBufferLength;


							//////////
							// If our populated length no longer fits into the new allocated space, then adjust it down
							//////
								if (buffRoot->populatedLength > buffRoot->allocatedLength)
									buffRoot->populatedLength = buffRoot->allocatedLength;		// Bring the populated area down to the new size

						} else {
							// Failure on resize
// TODO:  Untested code, breakpoint and examine
_asm int 3;
						}
				}
		}
	}




//////////
//
// Releases the buffer allocated for the SBuilder structure
//
//////
	void CALLTYPE vvm_builderFreeAndRelease(SBuilder** buffRoot)
	{
		SBuilder* buffDelete;


		// Make sure our environment is sane
		if (buffRoot && *buffRoot)
		{
			// Copy our *buffRoot pointer to local space so we can "appear" to kill it before it's actually killed
			buffDelete	= *buffRoot;
			*buffRoot	= NULL;

			// Release the data buffer
			if (buffDelete->data)
			{
				// Trim our sizes down to 0
				buffDelete->allocatedLength = 0;
				buffDelete->populatedLength = 0;

				// Release our buffer
				oss_free(buffDelete->data);

				// Mark it as no longer valid
				buffDelete->data = NULL;
			}

			// Release the SBuilder structure
			oss_free(buffDelete);
		}
	}




//////////
//
// Called to write out the indicated builder file as an 8-bit ASCII file
//
//////
	u32 CALLTYPE vvm_builderAsciiWriteOutFile(SBuilder* buffRoot, s8* tcFilename)
	{
		if (buffRoot && tcFilename)		return(oss_sharedAsciiWriteOutFile(tcFilename, buffRoot->data, buffRoot->populatedLength));
		else							return(-1);
	}




//////////
//
// SHA-1 functions, passed off to an external application included in the VVMOSS.
// See LibSF's \libsf\utils\sha1\sha1.cpp source file for these functions.
//
//////
	void CALLTYPE vvm_sha1ComputeSha1(s8* tcData, u32 tnDataLength, u8 shaOutput[20])
	{
		sha1_computeSha1((const u8*)tcData, tnDataLength, shaOutput);
	}

	u64 CALLTYPE vvm_sha1ComputeSha1As64Bit(s8* tcData, u32 tnDataLength)
	{
		u8 sha20Bytes[20];

		// Process normal SHA-1, then convert to 64-bit
		sha1_computeSha1((const u8*)tcData, tnDataLength, sha20Bytes);
		return(sha1_convertSha20To64Bit(sha20Bytes));
	}

	u32 CALLTYPE vvm_sha1ComputeSha1As32Bit(s8* tcData, u32 tnDataLength)
	{
		u8 sha20Bytes[20];

		// Process normal SHA-1, then convert to 64-bit
		sha1_computeSha1((const u8*)tcData, tnDataLength, sha20Bytes);
		return(sha1_convertSha20To32Bit(sha20Bytes));
	}

	void CALLTYPE vvm_sha1ComputeSha1AsHex(s8* tcData, u32 tnDataLength, s8* tcHexOutput, bool tlInsertSpaces)
	{
		u8	sha20Bytes[20];

		// Compute to our local buffer, then convert to hex
		sha1_computeSha1((const u8*)tcData, tnDataLength, sha20Bytes);
		sha1_computeSha1AsHex((const u8*)tcData, tnDataLength, sha20Bytes, tcHexOutput, tlInsertSpaces);
	}

	void CALLTYPE vvm_sha1ConvertHexToSha1(u8 shaOutput[20], s8* tcHexInput, bool* tlError)
	{
		sha1_convertHexToSha20(tcHexInput, shaOutput, tlError);
	}

	void CALLTYPE vvm_sha1ConvertSha1ToHex(s8* tcHexInput, u8 shaOutput[20], bool tlInsertSpaces)
	{
		sha1_convertSha20ToHex(shaOutput, tcHexInput, tlInsertSpaces);
	}

	void CALLTYPE vvm_sha1ComputeSha1_Start(u8 context[92])
	{
		memset(context, 0, sizeof(context));
		sha1_92initialize(context);
	}

	void CALLTYPE vvm_sha1ComputeSha1_ProcessThisData(u8 context[92], s8* tcData, u32 tnDataLength)
	{
		sha1_92continueOnThisData(context, (const u8*)tcData, tnDataLength);
	}

	void CALLTYPE vvm_sha1ComputeSha1_FinishAsSha1(u8 context[92], u8 shaOutput[20], bool tlWipeData)
	{
		sha1_92finalize(context, shaOutput, tlWipeData);
	}

	void CALLTYPE vvm_sha1ComputeSha1_FinishAsHex(u8 context[92], s8* tcHexOutput, bool tlInsertSpaces, bool tlWipeData)
	{
		u8	lcSha20Buffer[20];

		// Compute to our local buffer, then convert to hex
		sha1_92finalize(context, lcSha20Buffer, tlWipeData);
		sha1_convertSha20ToHex(lcSha20Buffer, tcHexOutput, tlInsertSpaces);
	}

	u64 CALLTYPE vvm_sha1Compute64BitFromSha1(u8 sha20Bytes[20])
	{
		return(sha1_convertSha20To64Bit(sha20Bytes));
	}

	u32 CALLTYPE vvm_sha1Compute32BitFromSha1(u8 sha20Bytes[20])
	{
		return(sha1_convertSha20To32Bit(sha20Bytes));
	}

	bool CALLTYPE vvm_sha1Compare(u8 sha20Bytes1[20], u8 sha20Bytes2[20])
	{
		return(sha1_compare(sha20Bytes1, sha20Bytes2));
	}




//////////
//
// Loads the specified BXML file from disk.
//
// Note:  If tnPathnameLength is 0, then tcPathname is assumed to be a pointer to a memory block
//        with bxml data
//
// Returns:
//		-1			- syntax error
//		others		- pointer to the root node
//
//////
	SBxml* CALLTYPE vvm_bxmlLoad(s8* tcPathname, u32 tnPathnameLength, u64* tnBytesRead, u64* tnErrorOffset, u64* tnErrorCode)
	{
		s8 buffer[_MAX_PATH + 1];


		// Copy our filename locally for NULL-termination
		memset(buffer, 0, sizeof(buffer));
		vvm_copyUpToShortestString((u8*)buffer, sizeof(buffer), (u8*)tcPathname, tnPathnameLength);

		// Physically process the incoming file, and return the result
		return(ibxml_asciiLoadFile(buffer, tnBytesRead, tnErrorOffset, tnErrorCode));
	}




//////////
//
// Parses the indicated buffer as an BXML file, and returns the root BXML structure if valid.
//
//////
	SBxml* CALLTYPE vvm_bxmlLoadFromBuffer(s8* tcBxmlData, u32 tnBxmlDataLength, u64* tnErrorOffset, u64* tnErrorCode)
	{
		return(ibxml_asciiLoadBuffer(tcBxmlData, tnBxmlDataLength, tnErrorOffset, tnErrorCode));
	}




//////////
//
// Saves the specified bxml node as the top-level node to the indicated file.
//
// Returns:
//		true		- success, and if tnBytesWritten is !NULL, it holds the total bytes written
//		false		- error opening indicated pathname, or writing to the file, and if tnBytesWritten is !NULL, it holds the number of bytes successfully written
//
//////
	bool CALLTYPE vvm_bxmlSave(SBxml* bxml, s8* tcPathname, u32 tnPathnameLength, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnBytesWritten)
	{
		u64			lnHandle, lnError;
		s64			lnBytesWritten;
		bool		llResult;
		SBuilder*	build;


		// Initialize our return values
		llResult = false;
		if (tnBytesWritten)							*tnBytesWritten = 0;
		if (tcPathname && tnPathnameLength == 0)	tnPathnameLength = (u32)vvm_scanForwardUntilCharacter(_csu8p(tcPathname), 0);

		// Make sure our environment is sane
		if (bxml && tcPathname)
		{
			// Attempt to create the indicated file
			lnHandle = oss_sharedAsciiOpenFile(tcPathname, true, false, false, false, false, true, true, false);
			if (lnHandle)
			{
				// Create our accumulation buffer
				vvm_builderCreateAndInitialize(&build, _COMMON_BUILDER_BLOCK_SIZE);
				while (build)
				{
					// Save this node, which will save all child nodes
					lnError = 0;
					ibxml_saveNode(build, bxml, tlSaveChildNodes, tlSaveSiblings, &lnError);
					if (lnError != 0)
						break;		// Failure in building the save node

					// Right now, build->buffer is populated with the content to be written to disk
					lnBytesWritten = (s64)oss_sharedAsciiWriteFile(lnHandle, build->data, build->populatedLength);

					// Save the bytes written if they have requested it
					if (tnBytesWritten)
						*tnBytesWritten = lnBytesWritten;

					// If we had an error, we're done
					if (lnBytesWritten < 0)
						break;		// Failure

					// Release our build buffer
					vvm_builderFreeAndRelease(&build);

					// When we get here, success
					llResult = true;
					break;
				}
				// When we get here, we're either successful or not
				if (oss_sharedAsciiCloseFile(lnHandle) != 0)
					llResult = false;		// Some error closing the handle
				// When we get here, llResult indicates our success
			}
		}
		// Indicate our success or failure
		return(llResult);
	}




//////////
//
// Serializes the BXML content to a buffer
//
//////
	void CALLTYPE vvm_bxmlSaveToBuffer(SBxml* bxml, SBuilder** build, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnErrorNumber)
	{
		// Make sure our environment is sane
		if (bxml && build)
		{
			// Create our accumulation buffer
			vvm_builderCreateAndInitialize(build, _COMMON_BUILDER_BLOCK_SIZE);

			// Save this node, which will save all child nodes
			if (*build)
				ibxml_saveNode(*build, bxml, tlSaveChildNodes, tlSaveSiblings, tnErrorNumber);
			// When we get here, we're either successful or not, tnErrorNumber and build are populated
		}
	}




//////////
//
// Create the attribute as a stand-alone creation, independent, free, in and of itself, probably a very happy attribute as it were, but only until it begins to get in touch with its inner feelings which exhibit the need to be part of something larger, which is not only a relationship or family, but also of being one of God's beloved. :-)
//
//////
	SBxmla* CALLTYPE vvm_bxmlaCreate(s8* tcNewName, u32 tnNewNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength)
	{
		return(ibxml_attributeCreateAsWithData(tcNewName, tnNewNameLength, tcData, tnDataLength, tnTotalDataLength));
	}




//////////
//
// Sets the attribute name
//
//////
	bool CALLTYPE vvm_bxmlaSetName(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength)
	{
		bool llResult;


		// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (bxmla && tcNewName && tnNewNameLength != 0)
		{
			// Create the new data block based on what is requested
			vvm_datumSet(&bxmla->_name, (u8*)tcNewName, tnNewNameLength, true);
			llResult = (bxmla->_name.data._s8 != NULL);
		}
		// Indicate our success or failure
		return(llResult);
	}




//////////
//
// Sets the attribute to the indicated value.  If tcData is NULL, it resets the data value
// to an empty state.
//
//////
	bool CALLTYPE vvm_bxmlaSetData(SBxmla* bxmla, s8* tcData, u32 tnDataLength)
	{
		bool llResult;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (bxmla && tcData)
		{
			// Create the new data block based on what is requested
			vvm_datum2Set(&bxmla->_data, (u8*)tcData, tnDataLength, bxmla->_data.lengthTotal, true);

			// Update our new total length (if need be)
			bxmla->_data.lengthTotal = max(tnDataLength, bxmla->_data.lengthTotal);

			// Success!
			llResult = (bxmla->_data.datum.data._s8 != NULL);
		}
		// Indicate our success or failure
		return(llResult);
	}




//////////
//
// Sets the attribute's total length, which could override the current length of the
// attribute, thereby requiring it to be truncated if the value is less.
//
//////
	bool CALLTYPE vvm_bxmlaSetTotalLength(SBxmla* bxmla, u32 tnDataLengthTotal)
	{
		bool	llResult;
		s8*		lcData;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (bxmla && bxmla->_data.lengthTotal != tnDataLengthTotal)
		{
			while (1)
			{
				if (bxmla->_data.datum.data._s8)
				{
					// We are adjusting data that's already been allocated
					if (bxmla->_data.lengthTotal > tnDataLengthTotal)
					{
						// We are decreasing the length
						if (tnDataLengthTotal >= bxmla->_data.datum.length)
						{
							// It's still bigger than that which is allocated, so we can just decrease it
							bxmla->_data.lengthTotal = tnDataLengthTotal;
							// Success
							llResult = true;

						} else {
							// It's smaller than the data already allocated, so we're reallocating
							if (tnDataLengthTotal == 0)
							{
								// They are removing all data
								// There is already data assigned, free it
								lcData = bxmla->_data.datum.data._s8;

								// Delete the data entry
								bxmla->_data.datum.data._s8		= NULL;
								bxmla->_data.datum.length		= 0;
								bxmla->_data.lengthTotal		= 0;

								// Release the actual memory block
								if (lcData)
									free(lcData);

								// Success
								llResult = true;

							} else {
								// There is some data still remaining
								lcData = (s8*)realloc(bxmla->_data.datum.data._s8, tnDataLengthTotal);
								if (!lcData)
									break;		// Failure to resize
								// If we get here, We're good

								// Set the new data and length
								bxmla->_data.datum.data._s8		= lcData;
								bxmla->_data.datum.length		= tnDataLengthTotal;
								bxmla->_data.lengthTotal		= tnDataLengthTotal;

								// Success
								llResult = true;
							}
						}

					} else {
						// We are increasing the length
						lcData = (s8*)realloc(bxmla->_data.datum.data._s8, tnDataLengthTotal);
						if (!lcData)
							break;		// Failure to resize
						// If we get here, We're good

						// Clear out the newly allocated memory
						memset(lcData + bxmla->_data.datum.length, 0, tnDataLengthTotal - (u32)bxmla->_data.datum.length);

						// Set the new data and length
						bxmla->_data.datum.data._s8		= lcData;
						bxmla->_data.datum.length		= tnDataLengthTotal;
						bxmla->_data.lengthTotal		= tnDataLengthTotal;

						// Success
						llResult = true;
					}

				} else {
					// We are creating the first data that will go here
// TODO:  untested code, breakpoint and examine
_asm nop;
					vvm_datum2Set(&bxmla->_data, NULL, tnDataLengthTotal, tnDataLengthTotal, false);
				}
				// When we get here, we're done
				break;
			}
		}
		// When we get here, llResult indicates our status
		return(llResult);
	}




//////////
//
// Deletes the indicated attribute from the chain, returns it as a "now free" attribute which
// can then be manually deleted.
//
//////
	SBxmla* CALLTYPE vvm_bxmlaDelete(SBxmla* bxmla, bool tlFreeMemory)
	{
		_isSBxmlAttributeDeleteParams	lbadp;
		SStartEndCallback				cb;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		if (bxmla)
		{
			// Remove this entry (if it exists in this parent)
			if (bxmla->_parent)
			{
				cb._func	= (u64)&iibxml_AttributeDeleteCallback;
				cb.extra	= (u64)&lbadp;
				vvm_SEChain_deleteFromAfterCallback(&bxmla->_parent->_attributes, true, &cb);
			}
			// When we get here, it's either been removed, or not
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Inserts a new attribute by name and value before or after the indicated one.  If Bxmla
// is NULL, then it will either be appended to the very start, or very end of the list,
// based on tlAfter.
//
// Note:  If tnNameLength is 0, tcName is assumed to be an SBxmla* to be directly inserted.
//
//////
	bool CALLTYPE vvm_bxmlaInsert(SBxml* bxml, SBxmla* bxmlaRef, s8* tcName, u32 tnNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength, bool tlAfter)
	{
		bool		llResult;
		SBxmla*		bxmlaNew;


		// Make sure our environment is sane
		// We only need to have a true bxml and tcName (for the attribute tag), the rest can be null / non-existent
		if (bxml && tcName && tnNameLength >= 1)
		{
			// Create the attribute
			bxmlaNew = vvm_bxmlaCreate(tcName, tnNameLength, tcData, tnDataLength, tnTotalDataLength);
			if (bxmlaNew)
				return(vvm_bxmlaInsertExisting(bxml, bxmlaRef, bxmlaNew, tlAfter));

		} else {
			// Invalid parameters
			llResult = false;
		}

		// Indicate our status
		return(llResult);
	}




//////////
//
// Inserts a new attribute by name and value before or after the indicated one.  If Bxmla
// is NULL, then it will either be appended to the very start, or very end of the list,
// based on tlAfter.
//
// Note:  If tnNameLength is 0, tcName is assumed to be an SBxmla* to be directly inserted.
//
//////
	bool CALLTYPE vvm_bxmlaInsertExisting(SBxml* bxml, SBxmla* bxmlaRef, SBxmla* bxmlaNew, bool tlAfter)
	{
		bool llResult;


		// Make sure our environment is sane
		// We only need to have a true bxml and tcName (for the attribute tag), the rest can be null / non-existent
		if (bxml && bxmlaNew)
		{
			// Append it to the chain after the entry
			vvm_SEChain_appendExistingRelativeToMember(&bxml->_attributes, (SLL*)bxmlaRef, vvm_getNextUniqueId(), (SLL*)bxmlaNew, _COMMON_START_END_BLOCK_SIZE, tlAfter, &llResult);

		} else {
			// Invalid parameters
			llResult = false;
		}

		// Indicate our status
		return(llResult);
	}




//////////
//
// Copies the attribute to a new stand-alone instance.
//
//////
	SBxmla* CALLTYPE vvm_bxmlaCopy(SBxmla* bxmla)
	{
		return(ibxml_attributeDuplicate(bxmla));
	}




//////////
//
// Copies the attribute as a new name for a stand-alone instance.
//
//////
	SBxmla* CALLTYPE vvm_bxmlaCopyAs(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength)
	{
		return(ibxml_attributeDuplicateAs(bxmla, tcNewName, tnNewNameLength));
	}




//////////
//
// Computes the SHA-1 of the tag+data, or just tag, or just data.  The 64-bit return value is
// the summed up portions of the 20-byte form.  It will obviously not have the same period without
// collisions, but may be sufficient for simple hashing.
//
//////
	u64 CALLTYPE vvm_bxmlaSha1One(SBxmla* bxmla, u8 sha20Bytes[20])
	{
		return(ivvm_bxmlAttributeSha1One(bxmla, sha20Bytes));
	}

	u64 CALLTYPE vvm_bxmlaSha1(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ivvm_bxmlAttributeSha1(bxml, sha20Bytes));
	}

	u64 CALLTYPE vvm_bxmlaSha1Tag(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ivvm_bxmlAttributeSha1Tag(bxml, sha20Bytes));
	}

	u64 CALLTYPE vvm_bxmlaSha1Data(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ivvm_bxmlAttributeSha1Data(bxml, sha20Bytes));
	}




//////////
//
// Called to return the values directly without having to obtain 
//
//////
	u32 CALLTYPE vvm_bxmlaFindAndGetString(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, SDatum* tsResult, bool* tlError)
	{
		return(vvm_bxmlaGetString(iivvm_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tsResult, tlError));
	}

	u32 CALLTYPE vvm_bxmlaFindAndGetU32(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError)
	{
		return(vvm_bxmlaGetU32(iivvm_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tlError));
	}

	u64 CALLTYPE vvm_bxmlaFindAndGetU64(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError)
	{
		return(vvm_bxmlaGetU64(iivvm_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tlError));
	}

	bool CALLTYPE vvm_bxmlaFindAndGetBool(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError)
	{
		return(vvm_bxmlaGetBool(iivvm_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tlError));
	}

	f32 CALLTYPE vvm_bxmlaFindAndGetF32(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError)
	{
		return(vvm_bxmlaGetF32(iivvm_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tlError));
	}

	f64 CALLTYPE vvm_bxmlaFindAndGetF64(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError)
	{
		return(vvm_bxmlaGetF64(iivvm_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tlError));
	}

	u32 CALLTYPE vvm_bxmlaGetString(SBxmla* bxmla, SDatum* tsResult, bool* tlError)
	{
		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Copy our datum
			if (tsResult)
				memcpy(&tsResult->data, &bxmla->_data.datum, sizeof(SDatum));

			// Indicate the length of the value
			return((u32)bxmla->_data.datum.length);

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}

	u32 CALLTYPE vvm_bxmlaGetU32(SBxmla* bxmla, bool* tlError)
	{
		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Indicate our value
			return(atoi(bxmla->_data.datum.data._s8));

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}

	u64 CALLTYPE vvm_bxmlaGetU64(SBxmla* bxmla, bool* tlError)
	{
		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Indicate our value
			return(atol(bxmla->_data.datum.data._s8));

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}

	// Valid "true" conditions are 1,Y,y,T,t
	bool CALLTYPE vvm_bxmlaGetBool(SBxmla* bxmla, bool* tlError)
	{
		s8 lc;


		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Indicate our value
			lc = bxmla->_data.datum.data._s8[0];
			return((lc == '1' || lc == 'Y' || lc == 'y' || lc == 'T' || lc == 't'));

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}

	f32 CALLTYPE vvm_bxmlaGetF32(SBxmla* bxmla, bool* tlError)
	{
		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Indicate our value
			return((f32)atof(bxmla->_data.datum.data._s8));

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}

	f64 CALLTYPE vvm_bxmlaGetF64(SBxmla* bxmla, bool* tlError)
	{
		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Indicate our value
			return(atof(bxmla->_data.datum.data._s8));

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}




//////////
//
// Provided as convenient access to the next/prev members for a given attribute.  These
// can be accessed natively by navigating the high and tricky waters of the SBxmla structure's
// ll member ... but why bother when we've gone to such trouble to provide this assistance tool? :-)
//
//////
	SBxmla* CALLTYPE vvm_bxmlaGetNext(SBxmla* bxmla)
	{
		u32		lnI;
		bool	llFound;
		SBxml*	bxml;


		// Make sure the environment is sane
		if (bxmla && bxmla->_parent)
		{
			// Iterate through all the attributes to find the next one
			bxml	= (SBxml*)bxmla->_parent;
			llFound	= false;
			for (lnI = 0; lnI < bxml->_attributes.masterCount; lnI++)
			{
				if (bxml->_attributes.master[lnI]->used)
				{
					if (llFound)
					{
						// This is our return item
						return((SBxmla*)bxml->_attributes.master[lnI]->ptr);

					} else if (bxml->_attributes.master[lnI]->ptr == bxmla) {
						// We found the item, so the next item is the next one
						llFound = true;
					}
				}
			}
		}
		// If we get here, not found
		return(NULL);
	}

	SBxmla* CALLTYPE vvm_bxmlaGetPrev(SBxmla* bxmla)
	{
		u32		lnI, lnILast;
		SBxml*	bxml;


		// Make sure the environment is sane
		if (bxmla && bxmla->_parent)
		{
			// Iterate through all the attributes to find the next one
			bxml	= (SBxml*)bxmla->_parent;
			lnILast	= -1;
			for (lnI = 0; lnI < bxml->_attributes.masterCount; lnI++)
			{
				if (bxml->_attributes.master[lnI]->used)
				{
					// Is this a match?
					if (bxml->_attributes.master[lnI]->ptr == bxmla)
					{
						// We found the item, so the previous item is the one
						if (lnILast == -1)
						{
							// Nothing previous
							return(NULL);

						} else {
							// We have one previous to return
							return((SBxmla*)bxml->_attributes.master[lnILast]->ptr);
						}
					}

					// This is a previous attribute candidate, so update it
					lnILast = lnI;
				}
			}
		}
		// If we get here, not found
		return(NULL);
	}




//////////
//
// Creates the indicated stand-alone node
//
//////
	SBxml* CALLTYPE vvm_bxmlNodeCreate(s8* tcNewName, u32 tnNewNameLength)
	{
		return(ibxml_nodeCreateAs(tcNewName, tnNewNameLength));
	}




//////////
//
// Called to modify the tag name
//
//////
	bool CALLTYPE vvm_bxmlNodeSetName(SBxml* bxml, s8* tcNewName, u32 tnNewNameLength)
	{
		bool llResult;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (bxml && tcNewName && tnNewNameLength != 0)
		{
			// Create the new data block based on what is requested
			vvm_datumSet(&bxml->_name, (u8*)tcNewName, tnNewNameLength, true);
			llResult = (bxml->_name.data._s8 != NULL);
		}
		// Indicate our success or failure
		return(llResult);
	}




//////////
//
// Deletes the indicated node, and all child nodes, and all attributes contained therein or below
// if tlFreeMemory is true, otherwise simply disconnects it from the 4-way node configuration.
//
//////
	bool CALLTYPE vvm_bxmlNodeDelete(SBxml* bxml, bool tlFreeMemory)
	{
		bool llResult;


		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// Deletes the indicated node from wherever it is in the parent chain
			llResult = vvm_ll4bxml_orphanize((SLL4*)bxml);

			// When we get here, it has been disconnected, which means it now exists as an orphan
			// Now we need to delete everything (if indeed we do), clearing up the entire path, including all attributes, children, everything
			if (llResult && tlFreeMemory)
				llResult = ibxml_nodeDeleteBranch(bxml);

			// When we get here, llResult indicates if we weer successful
		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// Inserts the indicated node before or after the current sibling/location.
//
// Note:  If tnNameLength is 0, tcName is assumed to be an existing BxmlNode that will be inserted directly.
//
//////
	bool CALLTYPE vvm_bxmlNodeInsert(SBxml* bxml, SBxml* bxmlRef, bool tlAfter)
	{
		bool llResult;


		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// Inserts the node before or after the reference node as a sibling
			llResult = vvm_ll4bxml_insert((SLL4*)bxml, (SLL4*)bxmlRef, tlAfter);

			// If we were successful, update the level
			if (llResult)
				bxml->level = bxmlRef->level;
		}
		// Indicate our status
		return(llResult);
	}

	bool CALLTYPE vvm_bxmlNodeInsertAsChild(SBxml* bxml, SBxml* bxmlParent, bool tlAfter)
	{
		bool llResult;


		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// Inserts the node relative tothe reference node as a child
			llResult = vvm_ll4bxml_insertAsChild((SLL4*)bxml, (SLL4*)bxmlParent, tlAfter);

			// If we were successful, update the level
			if (llResult)
				bxml->level = bxmlParent->level + 1;
		}
		// Indicate our status
		return(llResult);
	}

	bool CALLTYPE vvm_bxmlNodeInsertAsChildAfter(SBxml* bxml, SBxml* bxmlParent, SBxml* bxmlRef, bool tlAfter)
	{
		bool llResult;


		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// Deletes the indicated node from wherever it is in the parent chain
			llResult = vvm_ll4bxml_insertAsChildRegarding((SLL4*)bxml, (SLL4*)bxmlParent, (SLL4*)bxmlRef, tlAfter);

			// If we were successful, update the level
			if (llResult)
				bxml->level = bxmlParent->level + 1;
		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// Copies the indicated node, and optionally copies all attributes and child nodes as well.
//
//////
	SBxml* CALLTYPE vvm_bxmlNodeCopy(SBxml* bxml, bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult)
	{
		if (bxml && bxml->_name.data._s8 && bxml->_name.length != 0)
			return(ibxml_nodeCopyAs(bxml, bxml->_name.data._s8, bxml->_name.length, tlCopyAttributes, tlCopyChildren, tlResult));
		
		// Failure in passed parameters
		return(NULL);
	}




//////////
//
// Copies the indicated node as the new name, and optionally copies all attributes and child nodes as well.
//
//////
	SBxml* CALLTYPE vvm_bxmlNodeCopyAs(SBxml* bxml, s8* tcNewName, u32 tnNewNameLength, bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult)
	{
		return(ibxml_nodeCopyAs(bxml, tcNewName, tnNewNameLength, tlCopyAttributes, tlCopyChildren, tlResult));
	}




//////////
//
// Computes the SHA-1 of the tag+data, or just tag, or just data.  The 64-bit return value is
// the summed up portions of the 20-byte form.  It will obviously not have the same period without
// collisions, but may be sufficient for simple hashing.
//
//////
	u64 CALLTYPE vvm_bxmlNodeSha1(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ivvm_bxmlNodeSha1(bxml, sha20Bytes));
	}

	u64 CALLTYPE vvm_bxmlNodeSha1Tag(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ivvm_bxmlNodeSha1Tag(bxml, sha20Bytes));
	}

	u64 CALLTYPE vvm_bxmlNodeSha1Data(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ivvm_bxmlNodeSha1Data(bxml, sha20Bytes));
	}




//////////
//
// Added for logical use in code to make it clear to developers what's going on, without having
// to navigate the high and tricky waters of structures.
//
//////
	SBxml* CALLTYPE vvm_bxmlNodeGetNext(SBxml* bxml)
	{
		SBxml* bxmlTarget;


		// Make sure the environment is sane
		bxmlTarget = NULL;
		if (bxml)
			bxmlTarget = (SBxml*)bxml->ll4.next;
		
		// Return our target
		return(bxmlTarget);
	}

	SBxml* CALLTYPE vvm_bxmlNodeGetPrev(SBxml* bxml)
	{
		SBxml* bxmlTarget;


		// Make sure the environment is sane
		bxmlTarget = NULL;
		if (bxml)
			bxmlTarget = (SBxml*)bxml->ll4.prev;

		// Return our target
		return(bxmlTarget);
	}

	SBxml* CALLTYPE vvm_bxmlNodeGetParent(SBxml* bxml)
	{
		SBxml* bxmlTarget;


		// Make sure the environment is sane
		bxmlTarget = NULL;
		if (bxml)
			bxmlTarget = (SBxml*)bxml->ll4.parent;

		// Return our target
		return(bxmlTarget);
	}

	SBxml* CALLTYPE vvm_bxmlNodeGetFirstChild(SBxml* bxml)
	{
		SBxml* bxmlTarget;


		// Make sure the environment is sane
		bxmlTarget = NULL;
		if (bxml)
			bxmlTarget = (SBxml*)bxml->ll4.child;

		// Return our target
		return(bxmlTarget);
	}

	SBxmla* CALLTYPE vvm_bxmlNodeGetFirstAttribute(SBxml* bxml)
	{
		u32 lnI;


		// Make sure the environment is sane
		if (bxml)
		{
			for (lnI = 0; lnI < bxml->_attributes.masterCount; lnI++)
			{
				if (bxml->_attributes.master[lnI]->used && bxml->_attributes.master[lnI]->ptr)
					return((SBxmla*)bxml->_attributes.master[lnI]->ptr);
			}
		}
		// If we get here, no attribute
		return(NULL);
	}




//////////
//
// Called to find the indicated attribute directly for the indicated node
//
//////
	SBxmla* CALLTYPE vvm_bxmlFindAttribute(SBxml* bxml, SDatum* tsWildcardSearch, u32 tnInstance)
	{
		u32		lnInstance;
		SBxmla*	bxmla;


		lnInstance	= 0;
		bxmla		= vvm_bxmlNodeGetFirstAttribute(bxml);
		while (bxmla)
		{
			// Is this a match?
			if (vvm_wildcardMatch(_csu8p(bxmla->_name.data._u8), _csu8p(tsWildcardSearch->data._u8), false) == 0)
			{
				++lnInstance;
				if (lnInstance >= tnInstance)
					break;	// This is our match
			}

			// Move to next attribute
			bxmla = vvm_bxmlaGetNext(bxmla);
		}
		// Indicate our failure
		return(bxmla);
	}




//////////
//
// Using the indicated wildcard search string as begins searching from the root node.
// It locates (from the top down) the first entry matching the search criteria.
//
// Note:  If x is provided, then it will be populated with a structure to subsequently pass to vvm_bxmlFindContinue()
//
//////
	bool CALLTYPE vvm_bxmlFindFirst(SBxml* bxmlRoot, SBxml** bxmlNodeFound, SBxmla** bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, bool tlSearchAttributes, void** x)
	{
		// Make sure the environment is sane
		if (bxmlRoot && tsWildcardSearch && tsWildcardSearch->data._u8 && tsWildcardSearch->length != 0 && (bxmlNodeFound || bxmlaAttributeFound/*at least one must be defined*/))
			return(iivvm_bxmlFindFirst(bxmlRoot, bxmlNodeFound, bxmlaAttributeFound, tsWildcardSearch, tlTraverseChildren, tlSearchAttributes, x));

		// Failure
		return(false);
	}




//////////
//
// Will continue from a previous search location, or if no prior search location exists, or if
// the end has been reached (and previously reported), it will start again from the top down.
//
//////
	bool CALLTYPE vvm_bxmlFindContinue(void* x)
	{
		// Make sure the environment is sane
		if (x)
			return(iivvm_bxmlFindContinue(x));

		// Failure
		return(false);
	}




//////////
//
// Will search from the top down for nodes matching the indicated search pattern, and when
// found will append them to a Start/end list that can be traversed.
//
// Note:  bxmlFinds and bxmlaFinds will be appended to.
// Note:  To find a specific number of entries, populate *tnMaxFindsToInclude, otherwise use -1
//
//////
	u32 CALLTYPE vvm_bxmlFindAllAsStartEndLists(SBxml* bxmlRoot, SStartEnd* bxmlFinds, SStartEnd* bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren, bool tlSearchAttributes)
	{
		u32				lnMaxFinds;
		bool			llResult;
		void*			x;
		SBxml*			bxml;
		SBxmla*			bxmla;
		SBxmlList*		bxmlList;
		SBxmlaList*		bxmlaList;


		//////////
		// Do we find at least one?
		//////
			// Do we have a sane environment?
			if (bxmlRoot && (bxmlFinds || bxmlaFinds) && tsWildcardSearch && tnMaxFindsToInclude)
			{
				// Initialize
				lnMaxFinds	= *tnMaxFindsToInclude;
				bxml		= NULL;
				bxmla		= NULL;
				x			= NULL;


				//////////
				// Iterate so long as there are finds
				//////
					// Find first here, and the findContinue is at the end of the do..while
					*tnMaxFindsToInclude = 0;
					if (vvm_bxmlFindFirst(bxmlRoot, &bxml, &bxmla, tsWildcardSearch, tlTraverseChildren, tlSearchAttributes, &x))
					{
						// Found at least one
						do {

							// Store it
							if (bxml)
							{
								// A node was found
								bxmlList = (SBxmlList*)vvm_SEChain_append(bxmlFinds, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SBxmlList), _COMMON_START_END_BLOCK_SIZE, &llResult);

								// Store that node
								if (bxmlList)
								{
									++(*tnMaxFindsToInclude);		// Increase the count
									bxmlList->bxml = bxml;			// Store the pointer
								}

							} else {
								// An attribute was found
								bxmlaList = (SBxmlaList*)vvm_SEChain_append(bxmlaFinds, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SBxmlaList), _COMMON_START_END_BLOCK_SIZE, &llResult);

								// Store that attribute
								if (bxmlaList)
								{
									++(*tnMaxFindsToInclude);		// Increase the count
									bxmlaList->bxmla = bxmla;		// Store the pointer
								}
							}

						// And keep going
						} while (*tnMaxFindsToInclude < lnMaxFinds && vvm_bxmlFindContinue(x));

						// when we get here, they've all been found
						oss_free(x);

						// Indicate how many were found
						return(*tnMaxFindsToInclude);

					}
					//else no finds
			}


		//////////
		// If we get here, no finds
		//////
			return(0);
	}




//////////
//
// Searches from the indicated node for data items (attributes) and returns the first match,
// along with a structure that can be used to pass to vvm_bxmlDataFindContinue() in subsequent
// finds.
//
//////
	bool CALLTYPE vvm_bxmlDataFindFirst(SBxml* bxmlRoot, SBxmla** bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, void** x)
	{
		// Make sure the environment is sane
		if (bxmlRoot && tsWildcardSearch && tsWildcardSearch->data._u8 && tsWildcardSearch->length != 0 && bxmlaAttributeFound)
			return(iivvm_bxmlDataFindFirst(bxmlRoot, bxmlaAttributeFound, tsWildcardSearch, tlTraverseChildren, x));

		// Failure
		return(false);
	}




//////////
//
// Searches from the indicated node for data items (attributes) and returns the first match,
// along with a structure that can be used to pass to vvm_bxmlDataFindContinue() in subsequent
// finds.
//
//////
	bool CALLTYPE vvm_bxmlDataFindContinue(void* x)
	{
		// Make sure the environment is sane
		if (x)
			return(iivvm_bxmlDataFindContinue(x));

		// Failure
		return(false);
	}




//////////
//
// Searches from the indicated node for data items (attributes) and returns the first match,
// along with a structure that can be used to pass to vvm_bxmlDataFindContinue() in subsequent
// finds.
//
//////
	u32 CALLTYPE vvm_bxmlDataFindAllAsStartEndList(SBxml* bxmlRoot, SStartEnd* bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren)
	{
		u32				lnMaxFinds;
		bool			llResult;
		void*			x;
		SBxml*			bxml;
		SBxmla*			bxmla;
		SBxmlaList*		bxmlaList;


		//////////
		// Do we find at least one?
		//////
			// Do we have a sane environment?
			if (bxmlRoot && bxmlaFinds && tsWildcardSearch && tnMaxFindsToInclude)
			{
				// Initialize
				lnMaxFinds	= *tnMaxFindsToInclude;
				bxml		= NULL;
				bxmla		= NULL;
				x			= NULL;

				//////////
				// Iterate so long as there are finds
				//////
					// Find first here, and the findContinue is at the end of the do..while
					*tnMaxFindsToInclude = 0;
					if (vvm_bxmlDataFindFirst(bxmlRoot, &bxmla, tsWildcardSearch, tlTraverseChildren, &x))
					{
						// Found at least one
						do {

							// Store it
							if (bxmla)
							{
								// An attribute was found
								bxmlaList = (SBxmlaList*)vvm_SEChain_append(bxmlaFinds, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SBxmlaList), _COMMON_START_END_BLOCK_SIZE, &llResult);

								// Store that attribute
								if (bxmlaList)
								{
									++(*tnMaxFindsToInclude);		// Increase the count
									bxmlaList->bxmla = bxmla;		// Store the pointer
								}
							}

						// And keep going
						} while (*tnMaxFindsToInclude < lnMaxFinds && vvm_bxmlDataFindContinue(x));

						// when we get here, they've all been found
						oss_free(x);

						// Indicate how many were found
						return(*tnMaxFindsToInclude);

					}
					//else no finds
			}


		//////////
		// If we get here, no finds
		//////
			return(0);
	}




//////////
//
// Called to return the last error information for any BXML operations
//
//////
	void CALLTYPE vvm_bxmlGetLastError(SBxmlError* errorInfo)
	{
// TODO:  we need to record more explicit error messages so they can be reported on politely
#pragma message("vo.cpp::vvm_bxmlGetLastError() contains the ability to retrieve the last bxml error, however not all errors are being captured or recorded.")
		vvm_memcpy((s8*)errorInfo, (s8*)&gsLastErrorInfo, sizeof(SBxmlError));
	}




//////////
//
// Duplicate the indicated ASCII string
//
//////
	u8* CALLTYPE vvm_duplicateString(u8* ptr, u64 length)
	{
		u8* ptrNew;


		// Make sure our environment is sane
		ptrNew = NULL;
		if (ptr && length < 0xffffffff)
		{
			// Try to create the new string
			ptrNew = (u8*)malloc((u32)length + 1);

			//  Copy the string if successful
			if (ptrNew)
			{
				// Copy the string and null-terminate it
				memcpy(ptrNew, ptr, (u32)length);
				ptrNew[(u32)length] = 0;
			}
		}
		// All done
		return(ptrNew);
	}




//////////
//
// Duplicate the unicode string
//
//////
	w16* CALLTYPE vvm_duplicateUnicodeString(w16* tuText)
	{
		u32		tnLength;
		w16*	tuNewText;


		// Make sure our environment is sane
		tuNewText = NULL;
		if (tuText)
		{
			// Get the length
			tnLength = wcslen(tuText) * sizeof(w16);

			// Allocate that much space
			tuNewText = (w16*)malloc(tnLength);

			// If we're good, complete the copy
			if (tuNewText)
				memcpy(tuNewText, tuText, tnLength);
		}
		// Indicate our status
		return(tuNewText);
	}




//////////
//
// Duplicate and store to a datum structure
//
//////
	SDatum* CALLTYPE vvm_datumSet(SDatum* datum, u8* ptr, u64 length, bool tlFreeExisting)
	{
		u8* lptr;


		// Make sure our environment is sane
		if (datum)
		{
			// Do they want us to set the length?
			if (length == -1)
				length = vvm_scanForwardUntilCharacter(_csu8p(ptr), 0);

			// Is there anything to do?
			if (length != 0)
			{
				// If there is already a value here, free it up
				if (tlFreeExisting && datum->data._u8)
				{
					// Grab the pointer
					lptr				= datum->data._u8;

					// Indicate it is NULL in the structure (in case a task switch happens right now)
					datum->data._u8		= NULL;
					datum->length		= 0;

					// Release the allocated memory
					free(lptr);
				}

				if (ptr)
				{
					// Duplicate the string
					datum->data._u8 = vvm_duplicateString(ptr, length);

				} else {
					// Create a blank string and initialize it to NULLs
					datum->data._u8 = (u8*)malloc((u32)length);
					if (datum->data._u8)
						memset(datum->data._u8, 0, (u32)length);
				}

				// Verify our string was allocated properly
				if (datum->data._u8)
				{
					// Set the length
					datum->length = length;

				} else {
					// Indicate it failed
					datum->length = 0;
				}

			} else {
				// Initialize it to NULL
				datum->data._u8		= NULL;
				datum->length		= 0;
			}
		}
		return(datum);
	}




//////////
//
// Duplicate and store to a datum2 structure
//
//////
	SDatum2* CALLTYPE vvm_datum2Set(SDatum2* datum2, u8* ptr, u64 length, u64 lengthTotal, bool tlFreeExisting)
	{
		// Make sure our environment is sane
		if (datum2)
		{
			// Do they want us to set the length?
			if (length == -1)
				length = vvm_scanForwardUntilCharacter(_csu8p(ptr), 0);

			// Is there anything to do?
			if (length != 0)
			{
				// Duplicate the datum string
				vvm_datumSet(&datum2->datum, ptr, length, tlFreeExisting);

				// Update our totals if the string was allocated appropriately
				if (datum2->datum.data._u8)
				{
					// We allocated and copied correctly
					datum2->lengthTotal	= lengthTotal;

				} else {
					// We did not, so this string is not valid
					datum2->lengthTotal	= 0;
				}

			} else {
				// They are clearing out whatever is already there
				vvm_datumDelete(&datum2->datum);

				// Initialize it to NULL
				datum2->lengthTotal	= lengthTotal;
			}
		}
		return(datum2);
	}




//////////
//
// Duplicates a datum into another datum
//
//////
	SDatum* CALLTYPE vvm_datumDuplicate(SDatum* datumDst, SDatum* datumSrc)
	{
		// Make sure our environment is sane
		if (datumDst && datumSrc && datumSrc->data._u8 && datumSrc->length != 0)
		{
			// If it's already populated, release it
			if (datumDst->data._u8)
				free(datumDst->data._u8);

			// Copy the item
			datumDst->data._u8 = vvm_duplicateString(datumSrc->data._u8, datumSrc->length);

			// If it was copied, update the length
			if (datumDst->data._u8)
			{
				// Store the length
				datumDst->length = datumSrc->length;

			} else {
				// Indicate it failed
				datumDst->length = 0;
			}
		}
		return(datumDst);
	}




//////////
//
// Duplicates a datum2 into another datum2
//
//////
	SDatum2* CALLTYPE vvm_datum2Duplicate(SDatum2* datum2Dst, SDatum2* datum2Src)
	{
		// Make sure our environment is sane
		if (datum2Dst && datum2Src && datum2Src->datum.data._u8 && datum2Src->datum.length != 0)
		{
			// If it's already populated, release it
			if (datum2Dst->datum.data._u8)
				free(datum2Dst->datum.data._u8);

			// Copy the item
			datum2Dst->datum.data._u8 = vvm_duplicateString(datum2Src->datum.data._u8, datum2Src->datum.length);

			// If it was copied, update the length
			if (datum2Dst->datum.data._u8)
			{
				// Success
				datum2Dst->datum.length		= datum2Src->datum.length;
				datum2Dst->lengthTotal		= datum2Src->lengthTotal;

			} else {
				// Failure
				datum2Dst->datum.length		= 0;
				datum2Dst->lengthTotal		= 0;
			}
		}
		return(datum2Dst);
	}




//////////
//
// Deletes the indicated datum
//
//////
	void CALLTYPE vvm_datumDelete(SDatum* datum)
	{
		if (datum)
		{
			if (datum->data._u8)
			{
				// Free the memory
				free(datum->data._u8);

				// Reset the datum structure
				datum->data._u8 = NULL;
			}

			// Reset the length
			datum->length = 0;
		}
	}




//////////
//
// Delete the indicated datum2
//
//////
	void CALLTYPE vvm_datum2Delete(SDatum2* datum2)
	{
		if (datum2 && datum2->datum.data._u8)
		{
			// Free the memory
			vvm_datumDelete(&datum2->datum);

			// Reset the datum2 total size
			datum2->lengthTotal	= 0;
		}
	}




//////////
//
// Allocate an empty string into datum2
//
//////
	void CALLTYPE vvm_datum2SetNullString(SDatum2* datum2, u64 length, bool tlInitialize)
	{
		// Make sure our environment is sane
		if (datum2)
		{
			if (length != 0)
			{
				// Create the string space
				datum2->datum.data._u8 = (u8*)malloc((u32)length);		// Note:  This function does not automatically allocate the trailing NULL as the iDuplicateStringIntoDatum() function does
				if (datum2->datum.data._u8)
				{
					// We're good, set up the length
					datum2->datum.length	= length;
					datum2->lengthTotal		= length;

					// Set it to NULLs if we need to
					if (tlInitialize)
						memset(datum2->datum.data._u8, 0, (u32)length);

				} else {
					// Store the length value of 0
					datum2->datum.length	= 0;
					datum2->lengthTotal		= 0;
				}

			} else {
				// Initialize it to NULL
				datum2->datum.data._u8		= NULL;
				datum2->datum.length		= 0;
				datum2->lengthTotal			= 0;
			}
		}
	}




//////////
//
// Copy up to the shortest string of the two from source to destination
//
//////
	void CALLTYPE vvm_copyUpToShortestString(u8* dst, u32 tnDstLength, u8* src, u32 tnSrcLength)
	{
		u32 lnI;


		// Copy as many characters as are allowed
		for (lnI = 0; lnI < tnDstLength && lnI < tnSrcLength; lnI++)
			dst[lnI] = src[lnI];
	}




//////////
//
// Called to perform a wildcard match.  Uses repeated sequences, as in:
//
// Wildcard:	*rick*c*hodgin*
// Search:		Frederick C. Hodgin, III
// Result:		Would search for and find "Frede[rick] [C]. [Hodgin], III" within and return a match.
//
// Returns:
//		-3		-- Invalid candidate or wildcardPattern provided
//		-2		-- Syntax error in wildcardPattern
//		-1		-- candidate is less than wildcardPattern
//		0		-- candidate matches wildcardPattern
//		1		-- candidate is greater than wildcardPattern
//
///////
	s32 CALLTYPE vvm_wildcardMatchDatum(SDatum* tsCandidate, SDatum* tsWildcardPattern, bool tlCaseSensitive)
	{
		return(vvm_wildcardMatch(_csu8p(tsCandidate->data._u8), _csu8p(tsWildcardPattern->data._u8), tlCaseSensitive));
	}

	s32 CALLTYPE vvm_wildcardMatch(csu8p candidate, csu8p wildcardPattern, bool tlCaseSensitive)
	{
		u8		c, w;
		u32		lnC, lnW, lnNeedleLength, lnFoundPosition;
		bool	llWildcardFound;
		csu8p	needle, haystack;


// TODO:  breakpoint and examine
_asm nop;
		// Make sure the environment is sane
		if (candidate._u8 && wildcardPattern._u8)
		{
			// Repeat for every character in the wildcardPattern
			llWildcardFound = false;
			for (lnC = 0, lnW = 0;	wildcardPattern._u8[lnW] != 0;	)
			{
				//////////
				// Grab the characters
				//////
					c = candidate._u8[lnC];
					w = wildcardPattern._u8[lnW];


				//////////
				// Based on the wildcardPattern, try it
				//////
					if (w == '?')
					{
						// c can be anything, we accept it as is
						llWildcardFound = true;
						++lnC;					// Increment in candidate
						++lnW;					// Increment in wildcardPattern


					} else if (w == '*') {
						// The rest of c can be anything, unless there is something more in w after the asterisk
						llWildcardFound = true;
						if (wildcardPattern._u8[lnW + 1] == 0)
						{
							// We're done, the rest of candidate can be anything
							return(0);		// Match

						} else if (wildcardPattern._u8[lnW + 1] == '*' || wildcardPattern._u8[lnW + 1] == '?') {
							// Syntax error
							return(-2);

						} else {
							// We skip forward to the next part of wildcardPattern is matched
							++lnW;


							//////////
							// Find out how long the next part of wildcardPattern is
							//////
								lnNeedleLength = 0;
								do {
									// Are we done with the wildcard?
									if (wildcardPattern._u8[lnW + lnNeedleLength] == 0)
									{
										// Yes
										break;

									// Have we reached a terminating character for this leg?
									} else if (wildcardPattern._u8[lnW + lnNeedleLength] == '?' || wildcardPattern._u8[lnW + lnNeedleLength] == '*') {
										// Yes
										break;

									} else {
										// Continuing onward and upward
										++lnNeedleLength;
									}
								} while(1);


							//////////
							// We have the length of the part after the * now
							//////
								if (lnNeedleLength == 0)
								{
									// We reached the end of the wildcardPattern, which means this is a match
									return(0);		// The candidate was a match

								} else {
									// We have a segment to match up

									// Setup the needle and haystack
									needle		= _csu8p(wildcardPattern._u8	+ lnW);
									haystack	= _csu8p(candidate._u8			+ lnC);

									// Search forward for it
									if (!vvm_isNeedleInHaystack(haystack, (u32)vvm_scanForwardUntilCharacter(candidate, 0) - lnC, needle, lnNeedleLength, tlCaseSensitive, &lnFoundPosition))
										return(-1);		// Not found, the candidate is less than the wildcardPattern

									// If we get here, then it was found, so we continue on
									lnC += lnNeedleLength + lnFoundPosition;	// Candidate moves forward by the wildcardPattern length of this section, plus the found content
									lnW += lnNeedleLength;						// Move past the length of this section
								}
						}


					} else {
						// We're doing a character-by-character comparison
						if (!tlCaseSensitive)
						{
							// Case in-sensitive
							if (c >= 'A' && c <= 'Z')		c |= 0x20;		// Convert it to lower-case
							if (w >= 'A' && w <= 'Z')		w |= 0x20;		// Convert it to lower-case
							// Right now, case is adjusted
						}

						// Do the compare
						if (c != w)
						{
							// Something doesn't match
							if (c < w)		return(-1);		// The candidate is less than the wildcard
							else			return(1);		// The candidate is greater than the wildcard
						}
						// If we get here, still a match
						++lnC;
						++lnW;
					}
			}
			// When we get here, the wildcardPattern is done being searched

			// Are we done scanning the candidate yet?
			if (candidate._u8[lnC] == 0)
			{
				// Yes, everything matched
				// It may still not be a match though if the strings are not the same length
				if (llWildcardFound)
				{
					// The lengths must match to be a match
					return(vvm_scanForwardUntilCharacter(candidate, 0) == vvm_scanForwardUntilCharacter(wildcardPattern, 0));

				} else {
					// It was a match
					return(0);
				}

			} else {
				// Nope, it didn't match, the candidate is greater than the wildcardPattern
				return(1);
			}

		} else {
			// Something's awry
			return(-3);
		}
	}




//////////
//
// ASCII to unicode conversion
//
//////
	w16* CALLTYPE vvm_asciiToUnicode(u8* tcText, u32 tnTextLength)
	{
		u32		lnI;
		w16*	luOut;


		// Allocate 2 bytes for every ascii byte, plus 2 more for the trailing s16 null
		luOut = (w16*)malloc((tnTextLength * 2) + 2);
		if (luOut)
		{
			// Convert to 16-bit forms
			for (lnI = 0; lnI < tnTextLength; lnI++)
				luOut[lnI] = (w16)tcText[lnI];

			// Append an extra trailing null
			luOut[lnI] = 0;
		}
		return(luOut);
	}




//////////
//
// Unicode to ASCII conversion
//
//////
	s8* CALLTYPE vvm_unicodeToAscii(w16* tuText, u32 tnTextLength)
	{
		u32		lnI;
		s8*		lcOut;


		// Allocate 2 bytes for every ascii byte, plus 2 more for the trailing s16 null
		lcOut = (s8*)malloc(tnTextLength + 1);
		if (lcOut)
		{
			// Convert to 16-bit forms
			for (lnI = 0; lnI < tnTextLength; lnI++)
				lcOut[lnI] = (s8)tuText[lnI];

			// Append an extra trailing null
			lcOut[lnI] = 0;
		}
		return(lcOut);
	}




//////////
//
// Convert a single ASCII character to unicode
//
//////
	w16 CALLTYPE vvm_asciiToUnicodeChar(u8 tcChar)
	{
		return((w16)tcChar);
	}




//////////
//
// Convert unicode to single ASCII
//
//////
	s8 CALLTYPE vvm_unicodeToAsciiCharacter(w16 tuChar)
	{
		return((s8)tuChar);
	}




//////////
//
// Scans forward in the indicated string until the character changes, or until the maximum
// length is reached.
//
//////
	u64 CALLTYPE vvm_scanForwardUntilCharacterChanges(csu8p tcData, u64 tnMaxLength)
	{
		u64 lnI;


		// Make sure our environment is sane
		lnI = 0;
		if (tcData._cu8 && tnMaxLength != 0)
		{
			// Continue comparing every character
			for (++lnI; lnI < tnMaxLength; lnI++)
			{
				// If the character changes, we're done
				if (tcData._cu8[lnI] != tcData._cu8[0])
					return(lnI);		// We're done
			}
		}
		// When we get here, lnI is how far we skipped
		return(lnI);
	}




//////////
//
// Scan forward until the indicated character is found without regards to length
//
//////
	u64 CALLTYPE vvm_scanForwardUntilCharacter(csu8p tcData, s8 c)
	{
		u64 lnI;


		// Scan through the data
		lnI = 0;
		if (tcData._cu8)
		{
			for ( ; tcData._cu8[lnI] != c; )
				++lnI;
		}
		// Indicate our length
		return(lnI);
	}




//////////
//
// Unicode memory compare
//
//////
	int CALLTYPE vvm_unicodeMemcmp(w16* l, w16* r, u32 tnLength)
	{
		u32 lnI;


		// For every character in the length, compare left to right
		for (lnI = 0; lnI < tnLength; lnI++)
		{
			if (l[lnI] != r[lnI])
			{
				if (l[lnI] < r[lnI])
					return -1;		// Left is less than right
				return 1;			// Left is greater than right
			}
		}
		// They're equal
		return 0;
	}




//////////
//
// Unicode memory compare without regards to case
//
//////
	int CALLTYPE vvm_unicodeMemicmp(w16* l, w16* r, u32 tnLength)
	{
		w16		ll, rl;		// Left- and right-lower
		u32		lnI;


		// For every character in the length, compare left to right
		for (lnI = 0; lnI < tnLength; lnI++)
		{
			ll = vvm_lowerCaseW(l[lnI]);
			rl = vvm_lowerCaseW(r[lnI]);
			if (ll != rl)
			{
				if (ll < rl)
					return -1;		// Left is less than right
				return 1;			// Left is greater than right
			}
		}
		// They're equal
		return 0;
	}




//////////
//
// Unicode memory set (initialize)
//
//////
	int CALLTYPE vvm_unicodeMemset(w16* p, w16 uc, u32 tnLength)
	{
		u32 lnI;


		// Make sure the environment is sane
		lnI = 0;
		if (p)
		{
			// For the indicated length, stick the indicated unicode character in there
			for (; lnI < tnLength; lnI++)
				p[lnI + lnI] = uc;
		}

		// Indicate the number of characters we processed
		return(lnI);
	}




//////////
//
// Convert the indicated wide characgter to upper-case
//
//////
	w16 CALLTYPE vvm_upperCaseW(w16 u)
	{
		s8 c;
// TODO:  (unicode) foreign languages will need to have other tests here

		// See if it's a lower-case character in ASCII
		c = (s8)u;
		if (c >= 'a' && c <= 'z')
			return((w16)(c - 0x20));		// It is, convert to upper-case

		// If we get here, we're good as we are
		return(u);
	}




//////////
//
// Convert the indicated wide character to lower-case
//
//////
	w16 CALLTYPE vvm_lowerCaseW(w16 u)
	{
		s8 c;
// TODO:  (unicode) foreign languages will need to have other tests here


		// See if it's a lower-case character in ASCII
		c = (s8)u;
		if (c >= 'A' && c <= 'Z')
			return((w16)(c + 0x20));		// It is, convert to lower-case

		// If we get here, we're good as we are
		return(u);
	}




//////////
//
// ASCII memory set byte by byte
//
//////
	void CALLTYPE vvm_memset(s8* dst, s8 c, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (dst)
		{
			// Iterate for every indicated character
			for (lnI = 0; lnI < tnCount; lnI++)
				dst[lnI] = c;
		}
	}




//////////
//
// ASCII memory set as a series of integer values
//
//////
	void CALLTYPE vvm_memset4(u32* dst, u32 val, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (dst)
		{
			// Iterate for every indicated dword
			for (lnI = 0; lnI < tnCount; lnI++)
				dst[lnI] = val;
		}
	}




//////////
//
// Memory copy byte by byte
//
//////
	void CALLTYPE vvm_memcpy(s8* dst, s8* src, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (dst && src)
		{
			// Copy everything
			for (lnI = 0; lnI < tnCount; lnI++)
				dst[lnI] = src[lnI];
		}
	}




//////////
//
// Memory compare left and right
//
//////
	s32 CALLTYPE vvm_memcmp(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (l._cu8 && r._cu8)
		{
			for (lnI = 0; lnI < tnCount; lnI++)
			{
				if (l._cu8[lnI] != r._cu8[lnI])
				{
					if (l._cu8[lnI] < r._cu8[lnI])		return(-1);		// left is less than right
					else								return(1);		// left is greater than right
				}
				// Still good, keep going
			}
			// When we get here, they're equal
			return(0);
		}
		// Invalid configuration
		return(-2);
	}




//////////
//
// Memory compare left and right without regards to case
//
//////
	s32 CALLTYPE vvm_memicmp(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount)
	{
		u64		lnI;
		u8		cl, cr;


		// Make sure our environment is sane
		if (l._cu8 && r._cu8 && tnCount != 0)
		{
			for (lnI = 0; lnI < tnCount; lnI++)
			{
				// Grab the bytes
				cl = l._cu8[lnI];
				cr = r._cu8[lnI];

				// Ignore case
				if (cl >= 'A' && cl <= 'Z')		cl |= 0x20;
				if (cr >= 'A' && cr <= 'Z')		cr |= 0x20;

				if (cl != cr)
				{
					if (cl < cr)		return(-1);		// left is less than right
					else				return(1);		// left is greater than right
				}
				// Still good, keep going
			}
			// When we get here, they're equal
			return(0);
		}
		// Invalid configuration
		return(-2);
	}




//////////
//
// Compare two strings possibly of different lengths without regards to case
//
//////
	s32 CALLTYPE vvm_memicmpTwoLengths(csu8p l/*eft*/, u64 tnLeftLength, csu8p r/*ight*/, u64 tnRightLength)
	{
		u64		lnI;
		u8		cl, cr;


		// Make sure our environment is sane
		if (l._cu8 && r._cu8 && tnLeftLength != 0 && tnRightLength != 0)
		{
			for (lnI = 0; lnI < tnLeftLength && lnI < tnRightLength; lnI++)
			{
				// Grab the bytes
				cl = l._cu8[lnI];
				cr = r._cu8[lnI];

				// Ignore case
				if (cl >= 'A' && cl <= 'Z')		cl |= 0x20;
				if (cr >= 'A' && cr <= 'Z')		cr |= 0x20;

				if (cl != cr)
				{
					if (cl < cr)		return(-1);		// left is less than right
					else				return(1);		// left is greater than right
				}
				// Still good, keep going
			}
			// When we get here, they're equal
			if (tnLeftLength == tnRightLength)
				return(0);		// They're equal

			// If we get here, they're different lengths, so based on whichever one is shorter, return that result
			if (tnRightLength >= tnLeftLength)		return(1);		// Left is shorter
			else									return(-1);		// Right is shorter
		}
		// Invalid configuration
		return(-2);
	}




//////////
//
// Compare a string to a datum without regards to case
//
//////
	s32 CALLTYPE vvm_memicmpDatum(SDatum* datum, csu8p r/*ight*/, u64 tnRightLength)
	{
		// Make sure our environment is sane
		if (datum && r._cu8 && tnRightLength != 0 && datum->length != 0)
			return(vvm_memicmpTwoLengths(datum->data, datum->length, r, tnRightLength));

		// If we get here, failure
		return(-2);
	}




//////////
//
// Compare a string to a datum2 without regards to case
//
//////
	s32 CALLTYPE vvm_memicmpDatum2(SDatum2* datum2, csu8p r/*ight*/, u64 tnRightLength)
	{
		// Make sure our environment is sane
		if (datum2 && r._cu8 && tnRightLength != 0 && datum2->datum.length != 0)
			return(vvm_memicmpTwoLengths(datum2->datum.data, datum2->datum.length, r, tnRightLength));

		// If we get here, failure
		return(-2);
	}




//////////
//
// Compare a datum to a datum without regards to case
//
//////
	s32 CALLTYPE vvm_memicmpDatumDatum(SDatum* datumL, SDatum* datumR)
	{
		if (datumL && datumR)
			return(vvm_memicmpTwoLengths(datumL->data, datumL->length, datumR->data, datumR->length));

		// If we get here, failure
		return(-2);
	}




//////////
//
// Compare a datum2 to a datum2 without regards to case
//
//////
	s32 CALLTYPE vvm_memicmpDatum2Datum2(SDatum2* datum2L, SDatum2* datum2R)
	{
		if (datum2L && datum2R)
			return(vvm_memicmpTwoLengths(datum2L->datum.data, datum2L->datum.length, datum2R->datum.data, datum2R->datum.length));

		// If we get here, failure
		return(-2);
	}




//////////
//
// Extract the red, green, blue, and alpha components from the indicated color
//
//////
	void CALLTYPE vvm_deriveRGBA(u32 tnColor, u8* tnRed, u8* tnGrn, u8* tnBlu, f32* tfAlp)
	{
		*tnRed = red(tnColor);
		*tnGrn = grn(tnColor);
		*tnBlu = blu(tnColor);
		*tfAlp = (f32)(alp(tnColor)) / 255.0f;
	}




//////////
//
// Called to create a non-pseudo-random, but predictable pattern that can be used to create
// testable values or patterns to ensure that something hasn't been altered.
//
//////
	u8 CALLTYPE vvm_getPredictableSequentialPattern(u32 tnIterator, u32 tnValue)
	{
		u32 ln1, ln2, ln3, ln4, lnTotal, lnResult;


		//////////
		// Create the four forms
		//////
			ln1 = _rotl(  tnValue,         (tnIterator / 2) % 32);
			ln2 = _rotl(~(tnValue * 100),  (tnIterator / 4) % 32);
			ln3 = _rotl( (tnValue * 1000),  tnIterator      % 32);
			ln4 = _rotl(~(tnValue * 10000), tnIterator      % 32);


		//////////
		// Put the four forms together
		//////
			lnTotal = ln1 + ln2 + ln3 + ln4;


		//////////
		// Extract a single byte
		//////
			lnResult =	((lnTotal & 0xff000000) >> 24) +
						((lnTotal & 0x00ff0000) >> 16) +
						((lnTotal & 0x0000ff00) >>  8) +
						((lnTotal & 0x000000ff));


		//////////
		// And compute the final result as a single 8-bit value
		//////
			while (lnResult > 255)
			{
				lnResult =	((lnResult & 0x0000ff00) >> 8) +
							((lnResult & 0x000000ff));
			}


		//////////
		// All done
		//////
			return((u8)lnResult);
	}




//////////
//
// Append a new node to the list, and return the pointer.
// The nodeHint is provided and can be used to find the end of the chain faster than iterating
// from the root.  Typically it is the last returned node.  However, if NULL, this process will
// iterate from the root node forward.
//
//////
	SLL* CALLTYPE vvm_ll_appendNode(SLL** root, SLL* nodeHint, SLL* nodeNext, SLL* nodePrev, u64 tnUniqueId, u32 tnSize)
	{
		SLL* node;


		// Make sure our environment is sane
		node = NULL;
		if (root)
		{
			// Create a new node
			node = vvm_ll_createNode(nodePrev, nodeNext, tnUniqueId, tnSize);
			
			// Append it to the chain
			if (*root)
			{
				// There is already data
				if (!nodeHint)
					nodeHint = *root;

				// Iterate forward until we reach the end
				while (nodeHint->next)
					nodeHint = nodeHint->next;

				// Append as the next item from where we are
				nodeHint->next = node;

			} else {
				// This will be the first entry
				*root = node;
			}
		}
		// Indicate our success or failure
		return(node);
	}




//////////
//
// Creates a new 2-way linked list with optional nodePrev and nodeNext info, using
// the indicated size for the allocation (which is beyond the SLL portion at the head).
//////
	SLL* CALLTYPE vvm_ll_createNode(SLL* nodePrev, SLL* nodeNext, u64 tnUniqueId, u32 tnSize)
	{
		SLL* node;


		// Allocate the size
		node = (SLL*)malloc(sizeof(SLL) + tnSize);
		if (node)
		{
			// We're good
			memset(node, 0, tnSize);
			
			// Store a unique id
			node->uniqueId	= tnUniqueId;

			// Update our pointers
			node->prev		= nodePrev;
			node->next		= nodeNext;
		}

		// Indicate our success or failure
		return(node);
	}




//////////
//
// Called to delete a link list node.  If need be it orphanizes the node first.
//
//////
	void CALLTYPE vvm_ll_deleteNode(SLL* node)
	{
		if (node)
		{
			//////////
			// Disconnect
			//////
				if (node->prev || node->next)
					vvm_ll_orphanizeNode(node);


			//////////
			// Delete the node
			//////
				free(node);
		}
	}




//////////
//
// Called to delete a link list node with a callback.  If need be it orphanizes the node first.
//
//////
	void CALLTYPE vvm_ll_deleteNodesWithCallback(SLLCallback* cb)
	{
		if (cb && cb->node)
		{
			//////////
			// Disconnect
			//////
				if (cb->node->prev || cb->node->next)
					vvm_ll_orphanizeNode(cb->node);


			//////////
			// Let the user say their goodbyes
			//////
				if (cb->_func)
					cb->funcVoid(cb);


			//////////
			// Delete the node
			//////
				free(cb->node);
		}
	}




//////////
//
// Inserts a 2-way linked relative to the nodeRef, either before or after.  If the
// node is already connected, it is disconnected.
//
//////
	bool CALLTYPE vvm_ll_insertNode(SLL* node,  SLL* nodeRef,  bool tlAfter)
	{
// TODO:  UNTESTED CODE
		// Is our environment sane?
		if (node && nodeRef)
		{
			//////////
			// Disconnect
			//////
				if (node->prev || node->next)
					vvm_ll_orphanizeNode(node);


			//////////
			// Is it going before or after?
			//////
				if (tlAfter)
				{
					// Point the one after this back to node to be inserted
					if (nodeRef->next)
						nodeRef->next->prev	= node;		// The one after points back to the node we're inserting

					// Are we updating to a valid node?
					if (node)
					{
						// The node is valid, so we can update relative pointers
						// Point this node to the one that will be after
						node->next = nodeRef->next;
						node->prev = nodeRef;
					}

					// Store the pointer to the node
					nodeRef->next = node;


				} else {
					// Positioning this node before
					// Point the one before this forward to the node to be inserted
					if (nodeRef->prev)
						nodeRef->prev->next = node;

					// Are we updating to a valid node?
					if (node)
					{
						// The node is valid, so we can update relative pointers
						// Point this node to the one that will be after
						node->prev = nodeRef->prev;
						node->next = nodeRef;
					}

					// Store the pointer to the node
					nodeRef->prev = node;
				}
		}
		// Failure
		return(false);
	}




//////////
//
// Disconnects a node from its existing chain
//
//////
	void CALLTYPE vvm_ll_orphanizeNode(SLL* node)
	{
// TODO:  UNTESTED CODE
		// Is our environment sane?
		if (node)
		{

			//////////
			// Is there one before?
			//////
				if (node->prev)
					node->prev->next = node->next;		// Make the one before point to the one after

			//////////
			// Is there one after?
			//////
				if (node->next)
					node->next->prev = node->prev;		// Make the one after point to the one before

			//////////
			// Free up all parts
			//////
				node->next	= NULL;
				node->prev	= NULL;
		}
	}




//////////
//
// Called to delete the entire chain (beginning from where it's at
//
//////
	void CALLTYPE vvm_ll_deleteNodeChain(SLL** root)
	{
		SLL* node;
		SLL* nodeNext;


		// Make sure the environment is sane
		if (root)
		{
			// Iterate through deleting each entry
			node = *root;
			while (node)
			{
				// Grab the next node
				nodeNext = node->next;
				
				// Delete the node
				free(node);

				// Move to next item
				node = nodeNext;
			}

			// Reset the pointer
			*root = NULL;
		}
	}




//////////
//
// Called to delete the entire chain (beginning from where it's at on) using an optional callback.
// The callback should not delete the node, but only anything the node points to.
//
//////
	void CALLTYPE vvm_ll_deleteNodeChainWithCallback(SLLCallback* cb)
	{
		SLL* nodeNext;


		// Make sure the environment is sane
		if (cb)
		{
			// Iterate through deleting each entry
			while (cb->node)
			{
				// Grab the next node
				nodeNext = cb->node->next;

				// Perform the callback
				if (cb->_func)
					cb->funcVoid(cb);

				// Delete the node
				free(cb->node);

				// Move to next node
				cb->node = nodeNext;
			}
			// All done
		}
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
//////
	void CALLTYPE vvm_ll_iterateViaCallback(SLLCallback* cb)
	{
		//////////
		// For each node, process its portion
		//////
			while (cb->node)
			{

				//////////
				// Callback to compute the SHA1 on this item
				//////
					cb->funcVoid(cb);
					//vvm_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


				//////////
				// Move to next node
				//////
					cb->node = cb->node->next;
			}
	}




//////////
//
// Called to iterate from the indicated node backwards
//
//////
	void CALLTYPE vvm_ll_iterateBackwardViaCallback(SLLCallback* cb)
	{
		//////////
		// For each node, process its portion
		//////
			while (cb->node)
			{

				//////////
				// Callback to compute the SHA1 on this item
				//////
					cb->funcVoid(cb);
					//vvm_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


				//////////
				// Move to next node
				//////
					cb->node = cb->node->prev;
			}
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
//////
	SLL* CALLTYPE vvm_ll_getFirstNode(SLL* node)
	{
		// Make sure the environment is sane
		if (node)
		{
			// Iterate backwards to the top
			while (node->prev)
				node = node->prev;
		}

		// Indicate where we are
		return(node);
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
// The parameters in the callback are:
//		ptr			-- LL node
//////
	SLL* CALLTYPE vvm_ll_getLastNode(SLL* node)
	{
		// Make sure the environment is sane
		if (node)
		{
			// Iterate forwards to the end
			while (node->next)
				node = node->next;
		}

		// Indicate where we are
		return(node);
	}




//////////
//
// Creates a new 2-way linked list with optional nodePrev and nodeNext info, using
// the indicated size for the allocation (which includes the SLL portion at the head).
// The value of tnSize is the number of extra bytes required for the structure.  It
// should always be greater than zero because if it is only zero, that means only a
// raw SLL will be created.
//
//////
	SLL4* CALLTYPE vvm_ll4_create(SLL4* nodeWest, SLL4* nodeEast, SLL4* nodeNorth, SLL4* nodeSouth, u64 tnUniqueId, u32 tnSize)
	{
		SLL4* node;


		// Allocate the size
		node = (SLL4*)malloc(sizeof(SLL4) + tnSize);
		if (node)
		{
			// We're good
			memset(node, 0, sizeof(SLL4) + tnSize);
			
			// Store a unique id
			node->uniqueId	= tnUniqueId;

			// Update our pointers
			node->west		= nodeWest;
			node->east		= nodeEast;
			node->north		= nodeNorth;
			node->south		= nodeSouth;
		}

		// Indicate our success or failure
		return(node);
	}




//////////
//
// Called to create a 4-way linked list chain in a particular direction, for the indicated number
// of entries.
//
//////
	SLL4* CALLTYPE vvm_ll4_createChain(u32 tnSize, u32* tnCount, u32 tnDirection)
	{
		u32		lnI;
		SLL4*	ll4;
		SLL4*	ll4Root;
		SLL4*	ll4Last;


		// Iterate until our count is consumed, or we fail
		ll4		= NULL;
		ll4Root = NULL;
		ll4Last	= NULL;
		for (lnI = 0; lnI < *tnCount; lnI++)
		{
			// Create the new entry
			switch (tnDirection)
			{
				case _LL4_WEST:
					ll4 = vvm_ll4_create(NULL, ll4Last, NULL, NULL, vvm_getNextUniqueId(), tnSize);
					if (ll4Last)
						ll4Last->west = ll4;
					break;

				case _LL4_EAST:
					ll4 = vvm_ll4_create(ll4Last, NULL, NULL, NULL, vvm_getNextUniqueId(), tnSize);
					if (ll4Last)
						ll4Last->east = ll4;
					break;

				case _LL4_NORTH:
					ll4 = vvm_ll4_create(NULL, NULL, NULL, ll4Last, vvm_getNextUniqueId(), tnSize);
					if (ll4Last)
						ll4Last->north = ll4;
					break;

				case _LL4_SOUTH:
					ll4 = vvm_ll4_create(NULL, NULL, ll4Last, NULL, vvm_getNextUniqueId(), tnSize);
					if (ll4Last)
						ll4Last->south = ll4;
					break;

				default:
					// Unknown, failure.
					*tnCount = lnI;
					return(ll4Root);
			}
			// When we get here, we have our new entry
			if (!ll4Root)
				ll4Root = ll4;

			// Update the last pointer
			ll4Last = ll4;
		}
		// When we get here, we're good
		return(ll4Root);
	}




//////////
//
// Called to delete a single node from the four-way link list
//
//////
	void CALLTYPE vvm_ll4_delete(SLL4* node)
	{
		if (node)
		{
			// Disconnect from everything
			vvm_ll4_orphanize(node);

			// Free it
			free(node);
		}
	}




//////////
//
// Called to delete a four-way link list node with a callback.  If need be it orphanizes
// the node first.
//
//////
	void CALLTYPE vvm_ll4_deleteWithCallback(SLL4Callback* cb)
	{
		if (cb && cb->node)
		{
			//////////
			// Disconnect
			//////
				vvm_ll4_orphanize(cb->node);


			//////////
			// Let the user say their goodbyes
			//////
				if (cb->_func)
					cb->funcVoid(cb);


			//////////
			// Delete the node
			//////
				free(cb->node);
		}
	}




//////////
//
// Disconnects an SLL4 structure from either an BXML or a traditional node configuration.
// LL4 entries go off in four directions, toward siblings (prev/next), and toward parents
// and children.  These can be thought of as the cardinal directions as well (north/east/
// south/west).
//
//////
	// Note:  The common code itself knows nothing about SBxml structure formally, but it
	//        has at its header the SLL4 structure, which it does know about.
	//
	// In SBxml structures, we always update siblings, but if we have no previous entry,
	// then we must make the parent (if any) point to our next sibling, and we always
	// keep the children (for they are indeed most important!) :-)
	bool CALLTYPE vvm_ll4bxml_orphanize(SLL4* bxml)
	{
		bool	llResult;


// TODO:  tested code working properly, but not tested thoroughly enough
		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// We have something to work with, but of what caliber is it?
			// Should we accept it on its word that it is a good bxml and not being merely deceptive so as to harm our system? :-)

			// Update its elements if any
			// See if this is the first child
			if (!bxml->prev && bxml->parent)
				bxml->parent->child = bxml->next;		// This is the first item, so our parent must now point to our next sibling

			// Disconnect this node from its siblings
			if (bxml->next)		bxml->next->prev = bxml->prev;
			if (bxml->prev)		bxml->prev->next = bxml->next;

			// When we get here, this node has been made an orphan
			// Let it now believe so
			bxml->parent	= NULL;
			bxml->next		= NULL;
			bxml->prev		= NULL;
			// Note:  It will still keep its children

			// If we get here, we were good
			llResult = true;
		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// In nodes, we always update north/south paths, as well as east/west paths, as the node is
// just a point on a mesh or clutter mesh.
//
//////
	bool CALLTYPE vvm_ll4_orphanize(SLL4* node)
	{
		bool llResult;


		// Make sure our environment is sane
		llResult = false;
		if (node)
		{

			//////////
			// Disconnect this node in/from the four cardinal directions
			//////
				if (node->north)
					node->north->south = node->south;		// It points to an entry above itself

				if (node->south)
					node->south->north = node->north;		// It points to an entry below itself

				if (node->east)
					node->east->west = node->west;			// It points to an entry to the right

				if (node->west)
					node->west->east = node->east;			// It points to an entry to the left


			//////////
			// Update the node to reflects its new orphaned status
			//////
				node->north		= NULL;
				node->south		= NULL;
				node->east		= NULL;
				node->west		= NULL;

		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// Called to insert the indicated node where it should go
//
//////
	// Inserts only as a sibling, either before or after the reference bxml
	bool CALLTYPE vvm_ll4bxml_insert(SLL4* bxmlSibling, SLL4* bxmlRef, bool tlAfter)
	{
		bool	llResult;
		SLL4*	bxmlNext;
		SLL4*	bxmlPrev;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment's sane
		if (bxmlSibling && bxmlRef)
		{
			// Only success at this point. :-)
			llResult = true;

			// Are we inserting before or after?
			if (tlAfter)
			{
				// We're inserting this one AFTER the reference bxml
				bxmlNext		= bxmlRef->next;			// Grab the original next

				// Going between BxmlRef and BxmlNext
				bxmlSibling->prev		= bxmlRef;					// The one we're inserting points back to the reference
				bxmlSibling->next		= bxmlNext;					// The one we're inserting points forward to what used to be the next
				bxmlRef->next	= bxmlSibling;						// The reference points forward to the one we're inserting

				// Update the other one that's out there, you know, "on the other side"
				if (bxmlNext)
					bxmlNext->prev = bxmlSibling;					// The original next now points backward to the one we're inserting

			} else {
				// We're inserting this one BEFORE the reference bxml
				bxmlPrev		= bxmlRef->prev;			// Grab original previous

				// Going between BxmlPrev and BxmlRef
				bxmlSibling->prev		= bxmlPrev;					// The one we're inserting before points back to the original previous
				bxmlSibling->next		= bxmlRef;					// The one we're inserting before points forward to the reference
				bxmlRef->prev	= bxmlSibling;						// The reference points back to the one we're inserting before
				if (bxmlPrev)
					bxmlPrev->next = bxmlSibling;					// The previous points forward to the one we're inserting

				// Was this the first item we just inserted before?
				if (bxmlRef->parent && bxmlRef->parent->firstChild == bxmlRef)
				{
					// Yes, it needs to now point to the new item
					bxmlRef->parent->firstChild = bxmlSibling;
				}
			}

		} else {
			// Failure on parameters
			llResult = false;
		}

		// Indicate our status
		return(llResult);
	}

	// Positions the element as a child either at the start (faster) or end (slower)
	bool CALLTYPE vvm_ll4bxml_insertAsChild(SLL4* bxmlChild, SLL4* bxmlParent, bool tlAfter)
	{
		bool	llResult;
		SLL4*	bxmlRunner;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment's sane
		if (bxmlChild && bxmlParent)
		{
			// Only success at this point
			llResult = true;

			// Before or after?
			if (tlAfter)
			{
				// Going to the tail
				if (bxmlParent->child)
				{
					// We need to iterate to the end
					bxmlRunner = bxmlParent->child;
					while (bxmlRunner->next)
						bxmlRunner = bxmlRunner->next;

					// When we get here, we have the last child
					bxmlRunner->next			= bxmlChild;
					bxmlChild->prev				= bxmlRunner;

				} else {
					// First child
					bxmlParent->firstChild		= bxmlChild;
					bxmlChild->prev				= NULL;
				}
				// Nothing point after
				bxmlChild->next = NULL;

			} else {
				// Going to the start
				if (bxmlParent->child)
					bxmlChild->next = bxmlParent->child;		// There is already a child, make sure this new one points to that child

				// Update the parent to point to its new first child
				bxmlParent->firstChild			= bxmlChild;

				// Nothing pointing before
				bxmlChild->prev					= NULL;
			}
			// If we get here, we're good
			llResult = true;

		} else {
			// Invalid parameters
			llResult = false;
		}

		// Indicate our status
		return(llResult);
	}

	// Positions the element relative to the bxml reference, either before or after, and
	// therefore "regarding" it.
	bool CALLTYPE vvm_ll4bxml_insertAsChildRegarding(SLL4* bxmlChild, SLL4* bxmlParent, SLL4* bxmlRegarding, bool tlAfter)
	{
		bool	llResult;
		SLL4*	BxmlNext;
		SLL4*	BxmlPrev;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (bxmlChild && bxmlParent && bxmlRegarding)
		{
			if (tlAfter)
			{
				// It's going AFTER the reference entry
				if (bxmlRegarding->next)
				{
					// There IS an entry after this one
					// bxml is going between BxmlRef and BxmlNext
					BxmlNext = bxmlRegarding->next;

					// Insert the node
					bxmlChild->prev			= bxmlRegarding;
					bxmlChild->next			= BxmlNext;
					bxmlRegarding->next		= bxmlChild;
					BxmlNext->prev			= bxmlChild;

				} else {
					// BxmlRef is the last entry
					bxmlRegarding->next		= bxmlChild;
					bxmlChild->prev			= bxmlRegarding;
					bxmlChild->next			= NULL;
				}

			} else {
				// It's going BEFORE the reference entry
				if (bxmlRegarding->prev)
				{
					// There IS an entry before this one
					BxmlPrev = bxmlRegarding->prev;
					// This is going between BxmlPrev and BxmlRef
					bxmlChild->prev				= BxmlPrev;
					bxmlChild->next				= bxmlRegarding;
					BxmlPrev->next				= bxmlChild;
					bxmlRegarding->prev			= bxmlChild;

				} else {
					// xmlRef is the first entry
					bxmlChild->prev				= NULL;
					bxmlChild->next				= bxmlRegarding;
					bxmlParent->firstChild		= bxmlChild;
					bxmlRegarding->prev			= bxmlChild;
				}
			}
			// Update the pointer to point back up to its new parent.
			bxmlChild->parent = bxmlParent;

			// Success
			llResult = true;
		}
		// Indicate our status
		return(llResult);
	}

	// Inserts the node before or after the indicated node
	bool CALLTYPE vvm_ll4_insertNorthSouth(SLL4* node, SLL4* nodeRef, bool tlAfter)
	{
		bool	llResult;
		SLL4*	nodeNorth;
		SLL4*	nodeSouth;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (node && nodeRef)
		{
			if (tlAfter)
			{
				// node is going after nodeRef
				if (nodeRef->south)
				{
					// There is an entry after nodeRef, so we insert it between nodeRef and nodeRef->next
					nodeSouth			= nodeRef->south;

					// Update nodeRef to point to this one
					node->south			= nodeSouth;
					nodeRef->south		= node;

					// Update nodeNext to point back to this one
					node->north			= nodeSouth->north;
					nodeSouth->north	= node;

				} else {
					// There is no entry after nodeRef, so we just put it after
					nodeRef->south		= node;
					node->north			= nodeRef;
					node->south			= NULL;				// Make sure this entry is not hooked up otherwise
				}

			} else {
				// node is going before nodeRef
				if (nodeRef->north)
				{
					// There is an entry before nodeRef, so we insert it between nodeRef and nodeRef->prev
					nodeNorth			= nodeRef->north;

					// Update nodeRef to point to this one
					node->north			= nodeNorth;
					nodeRef->north		= node;

					// Update nodePrev to point forward to this one
					node->south			= nodeRef;
					nodeNorth->south	= node;

				} else {
					// There is no entry before nodeRef, so we just put it before
					nodeRef->north		= node;
					node->south			= nodeRef;
					node->north			= NULL;				// Make sure this entry is not hooked up otherwise
				}
			}
		}
		// Indicate our status
		return(llResult);
	}

	// Inserts the node before or after the indicated node
	bool CALLTYPE vvm_ll4_insertWestEast(SLL4* node, SLL4* nodeRef, bool tlAfter)
	{
		bool	llResult;
		SLL4*	nodeWest;
		SLL4*	nodeEast;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (node && nodeRef)
		{
			if (tlAfter)
			{
				// node is going after (east) nodeRef
				if (nodeRef->east)
				{
					// There is an entry after nodeRef, so we insert it between nodeRef and nodeRef->next
					nodeEast		= nodeRef->east;

					// Update nodeRef to point to this one
					node->east		= nodeEast;
					nodeRef->east	= node;

					// Update nodeNext to point back to this one
					node->west		= nodeEast->west;
					nodeEast->west	= node;

				} else {
					// There is no entry after nodeRef, so we just put it after
					nodeRef->east	= node;
					node->west		= nodeRef;
					node->east		= NULL;				// Make sure this entry is not hooked up otherwise
				}

			} else {
				// node is going before (west) nodeRef
				if (nodeRef->west)
				{
					// There is an entry before nodeRef, so we insert it between nodeRef and nodeRef->west
					nodeWest		= nodeRef->west;

					// Update nodeRef to point to this one
					node->west		= nodeWest;
					nodeRef->west	= node;

					// Update nodePrev to point forward to this one
					node->east		= nodeRef;
					nodeWest->east	= node;

				} else {
					// There is no entry before nodeRef, so we just put it before
					nodeRef->west	= node;
					node->east		= nodeRef;
					node->west		= NULL;				// Make sure this entry is not hooked up otherwise
				}
			}
		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// Called to delete the chain of items in the indicated direction
//
//////
	void CALLTYPE vvm_ll4_deleteChain(SLL4** root, u32 tnDirection)
	{
		SLL4*	node;
		SLL4*	nodeNext;


		// Make sure our environment is sane
		if (root && *root)
		{
			// Grab the node
			node = *root;

			// Are we deleting all, or just in a particular direction?
			if (tnDirection == _LL4_ALL)
			{
				// Delete everything
				ivvm_ll4_deleteChainAllNodes(NULL, *root);

			} else {
				// Iterate through every node in the indicated direction
				while (node)
				{
					//////////
					// Grab the next node
					/////
						switch (tnDirection)
						{
							case _LL4_NORTH:
								nodeNext = node->north;
								break;

							case _LL4_SOUTH:
								nodeNext = node->south;
								break;

							case _LL4_WEST:
								nodeNext = node->west;
								break;

							case _LL4_EAST:
								nodeNext = node->east;
								break;

							default:
								// Invalid direction, abort
								return;
						}


					//////////
					// Disconnect if we are not deleting all
					//////
						if (tnDirection != _LL4_ALL)
							vvm_ll4_orphanize(node);


					//////////
					// Delete this entry
					/////
						free(node);


					//////////
					// Move to the next node
					/////
						node = nodeNext;
				}
			}

			// All done, update our root pointer
			*root = NULL;
		}
	}




//////////
//
// 
// Called to delete the entire chain (beginning from where it's at on) using an optional callback.
// The callback should not delete the node, but only anything the node points to.
//
//////
	void CALLTYPE vvm_ll4_deleteChainWithCallback(SLL4Callback* cb, u32 tnDirection)
	{
		SLL4* nodeNext;


		if (tnDirection == _LL4_ALL)
		{
			// Delete everything
			ivvm_ll4_deleteChainAllNodes(cb, cb->node);

		} else {
			// Iterate through the master list until we find the associated entry
			while (cb->node)
			{
				//////////
				// Grab the next node
				/////
					switch (tnDirection)
					{
						case _LL4_NORTH:
							nodeNext = cb->node->north;
							break;

						case _LL4_SOUTH:
							nodeNext = cb->node->south;
							break;

						case _LL4_WEST:
							nodeNext = cb->node->west;
							break;

						case _LL4_EAST:
							nodeNext = cb->node->east;
							break;

						default:
							// Invalid direction, abort
							return;
					}


				//////////
				// Disconnect if we are not deleting all
				//////
					if (tnDirection != _LL4_ALL)
						vvm_ll4_orphanize(cb->node);


				//////////
				// Perform the callback
				//////
					cb->funcBool(cb);


				//////////
				// Delete this entry
				/////
					free(cb->node);


				//////////
				// Move to the next node
				/////
					cb->node = nodeNext;
			}
			// All done
		}
	}




//////////
//
// Called to navigate through an entire list of nodes, calling the indicated function on
// each one.
//
//////
	void CALLTYPE vvm_ll4_iterateViaCallback(SLL4Callback* cb, u32 tnDirection)
	{
		// Make sure the environment is sane
		if (cb && cb->_func)
		{
			//////////
			// For each node, process its portion
			//////
				while (cb->node)
				{
					//////////
					// Callback to compute the SHA1 on this item
					//////
						cb->funcVoid(cb);
						//vvm_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


					//////////
					// Move to "next" node
					//////
						switch (tnDirection)
						{
							case _LL4_WEST:
								cb->node = cb->node->west;
								break;

							case _LL4_EAST:
								cb->node = cb->node->east;
								break;

							case _LL4_NORTH:
								cb->node = cb->node->north;
								break;

							case _LL4_SOUTH:
								cb->node = cb->node->south;
								break;
						}
				}
		}
	}




//////////
//
// Called to iterate in the indicated direction until we reach the furthest extent.
// Note:  This can be a dangerous function because there is no iterative exit.  Any circular
//        pointer will cause the system to go into an unbreakable loop.
//
//////
	SLL4* CALLTYPE vvm_ll4_getLastNode(SLL4* node, u32 tnDirection)
	{
		// Make sure the environment is sane
		if (node)
		{
			// Iterate so long as there's something to which to iterate toward. :-)
			do {
				if (tnDirection == _LL4_WEST)
				{
					if (node->west)		node = node->west;
					else				break;

				} else if (tnDirection == _LL4_EAST) {
					if (node->east)		node = node->east;
					else				break;

				} else if (tnDirection == _LL4_NORTH) {
					if (node->north)	node = node->north;
					else				break;

				} else if (tnDirection == _LL4_SOUTH) {
					if (node->south)	node = node->south;
					else				break;

				} else {
					// Unknown item
					break;
				}
				// Repeat until we find the end
			} while (1);
		}
		// Indicate our success or failure
		return(node);
	}




//////////
//
// Append a new record of indicated size to the start/end chain
//
// Returns:
//		NULL		- If error
//		other		- A pointer to the new object
//
// Note:  Initializes memory block of tnSize to NULLs upon successful allocation
//
//////
	void* CALLTYPE vvm_SEChain_prepend(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(ivvm_SEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, true, tlResult));
	}

	void* CALLTYPE vvm_SEChain_append(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(ivvm_SEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, false, tlResult));
	}

	// Prepends or appends to the Start/end chain
	void* ivvm_SEChain_appendOrPrepend (SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult)
	{
		SLL*			ptrCaller;
		SMasterList*	ptrNew;
		SMasterList*	ptrPrev;
		SMasterList**	prev;


// TODO:  untested code, breakpoint and examine
// Note:  This code has been tested, but it is truly essential to operations of the VVM, and needs thoroughly tested many, many, many times. :-)
		// See where we are
		ptrCaller = NULL;
		if (ptrSE)
		{
			if (!ptrSE->root)
			{
				// This is the first item
				ptrPrev	= NULL;
				prev	= &ptrSE->root;

			} else {
				// We're appending
				if (tlPrepend)
				{
					// We go to the beginning
					ptrPrev	= ptrSE->root;
					prev	= &ptrSE->root;

				} else {
					// We are appending to the end
					ptrPrev	= ptrSE->last;
					prev	= (SMasterList**)&ptrSE->last->ll.next;
				}
			}

			// Allocate for our SMasterList pointer
			ptrNew = (SMasterList*)malloc(sizeof(SMasterList));
			if (ptrNew)
			{
				// We have our new pointer, initialize the structure
				memset(ptrNew, 0, sizeof(SMasterList));

				// Create the new caller structure
				ptrCaller = (SLL*)malloc(tnSize);
				if (ptrCaller)
				{
					// Initialize the structure
					memset(ptrCaller, 0, tnSize);

					// Indicate its unique ID
					ptrCaller->uniqueId	= tnUniqueId;

					// Store the memory variable for the caller memory block
					ptrNew->ptr			= ptrCaller;

					// Update the back-link
					*prev				= ptrNew;

					// Update the other part of the back link
					ptrNew->ll.uniqueId	= tnUniqueIdExtra;
					if (tlPrepend)
					{
						// Previous ptrSE->root points backward to ptrNew, which is now the entry pointed to by ptrSE->root
						ptrPrev->ll.prev	= (SLL*)ptrNew;		// Old first entry points backward to new first entry
						ptrNew->ll.next		= (SLL*)ptrPrev;	// New first entry points forward to old first entry
						ptrSE->root			= ptrNew;			// New first entry

					} else {
						// We are appending to the end
						ptrNew->ll.prev		= (SLL*)ptrPrev;	// Previous last entry pointing forward to new last entry
						ptrSE->last			= ptrNew;			// New last entry
					}

					// Store it in the master list (so when VM is suspended, this data gets saved)
					ivvm_SEChain_appendMasterList(ptrSE, ptrNew, 0, tnBlockSizeIfNewBlockNeeded);

					// All done!
				}
				// When we get here, ptrCaller is either populated or NULL
			}
		}
		// Indicate our success or failure explicitly if required
		if (tlResult)
			*tlResult = !(ptrCaller == NULL);

		// Return our pointer
		return(ptrCaller);
	}




	// Appends or prepends an existing (already allocated) orphan pointer to the indicated Start/end list
	void* ivvm_SEChain_appendOrPrependExisting(SStartEnd* ptrSE, SLL* ptrExisting, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult)
	{
		SMasterList*	ptrNew;
		SMasterList*	ptrPrev;
		SMasterList**	prev;


// TODO:  untested code, breakpoint and examine
// Note:  This code has been tested, but it is truly essential to operations of the VVM, and needs thoroughly tested many, many, many times. :-)
		// See where we are
		if (ptrSE)
		{
			if (!ptrSE->root)
			{
				// This is the first item
				ptrPrev	= NULL;
				prev	= &ptrSE->root;

			} else {
				// We're appending
				if (tlPrepend)
				{
					// We go to the beginning
					ptrPrev	= ptrSE->root;
					prev	= &ptrSE->root;

				} else {
					// We are appending to the end
					ptrPrev	= ptrSE->last;
					prev	= (SMasterList**)&ptrSE->last->ll.next;
				}
			}

			// Allocate for our SMasterList pointer
			ptrNew = (SMasterList*)malloc(sizeof(SMasterList));
			if (ptrNew)
			{
				// We have our new pointer, initialize the structure
				memset(ptrNew, 0, sizeof(SMasterList));

				// Create the new caller structure
				// Store the memory variable for the caller memory block
				ptrNew->ptr			= ptrExisting;

				// Update the back-link
				*prev				= ptrNew;

				// Update the other part of the back link
				if (tlPrepend)
				{
					// Previous ptrSE->root points backward to ptrNew, which is now the entry pointed to by ptrSE->root
					ptrPrev->ll.prev	= (SLL*)ptrNew;		// Old first entry points backward to new first entry
					ptrNew->ll.next		= (SLL*)ptrPrev;	// New first entry points forward to old first entry
					ptrSE->root			= ptrNew;			// New first entry

				} else {
					// We are appending to the end
					ptrNew->ll.prev		= (SLL*)ptrPrev;	// Previous last entry pointing forward to new last entry
					ptrSE->last			= ptrNew;			// New last entry
				}

				// Store it in the master list (so when VM is suspended, this data gets saved)
				ivvm_SEChain_appendMasterList(ptrSE, ptrNew, 0, tnBlockSizeIfNewBlockNeeded);
				// All done!

				// Indicate our success
				return(ptrExisting);
			}
		}
		// Indicate our failure
		return(NULL);
	}




	// Appends an entry relative to the indicated SMasterList* member (either before or after the entry)
	void* CALLTYPE vvm_SEChain_appendRelativeToMember(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult)
	{
		SLL* ptrCaller;


		// See where we are
		if (ptrSE)
		{
			if (!ptrSE->root)
				return(NULL);		// There are no entries, so we can't be adding relative to the reference pointer

			// Create the new caller structure
			ptrCaller = (SLL*)malloc(tnSize);
			if (ptrCaller)
			{
				// Initialize the structure
				memset(ptrCaller, 0, tnSize);

				// Indicate its unique ID
				ptrCaller->uniqueId	= tnUniqueId;

				// Append the now existing pointer
				return(vvm_SEChain_appendExistingRelativeToMember(ptrSE, ptrRef, tnUniqueIdExtra, ptrCaller, tnBlockSizeIfNewBlockNeeded, tlAfter, tlResult));
			}
		}
		// If we get here, error
		return(NULL);
	}

	void* CALLTYPE vvm_SEChain_appendExistingRelativeToMember(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueIdExtra, SLL* ptrCaller, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult)
	{
		u32				lnI, lnHint;
		bool			llFound;
		SMasterList*	lmlNew;


		// See where we are
// TODO:  untested code, breakpoint and examine
// Note:  This code has been tested, but it is truly essential to operations of the VVM, and needs thoroughly tested
		if (ptrSE)
		{
			if (!ptrSE->root)
				return(NULL);		// There are no entries, so we can't be adding relative to the reference pointer

			// If there's a reference, add it relative to the reference
			if (ptrRef)
			{
				// Locate the indicated reference in this list
				llFound = false;
				for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
				{
					if (ptrSE->master[lnI]->used && ptrSE->master[lnI]->ptr == ptrRef)
					{
						// We found our match
						if (tlAfter)		lnHint = lnI + 1;		// Should go after
						else				lnHint = lnI;			// Should go before, which means where the current entry was found

						// Make sure there's room
						ivvm_SEChain_freeUpSlot(ptrSE, lnHint, tnBlockSizeIfNewBlockNeeded);

						// Continue to insert this item
						llFound = true;
						break;
					}
				}

				// See if we found our entry
				if (!llFound)
					return(NULL);		// The indicated ptrRef was not found as a member of this Start/End list

			} else {
				// Add at the first available slot
				lnHint = 0;
			}
			// When we get here, we have the relative of where the new entry will go

			// Allocate for our SMasterList pointer
			lmlNew = (SMasterList*)malloc(sizeof(SMasterList));
			if (lmlNew)
			{
				// We have our new pointer, initialize the structure
				memset(lmlNew, 0, sizeof(SMasterList));

				// Store the data
				lmlNew->ll.uniqueId	= tnUniqueIdExtra;
				lmlNew->ptr			= ptrCaller;

				// Store it in the master list (so when VM is suspended, this data gets saved)
				ivvm_SEChain_appendMasterList(ptrSE, lmlNew, lnHint, tnBlockSizeIfNewBlockNeeded);


				///////////
				// Adjust this item relative to its ptrRef
				//////
					if (ptrRef)
					{
						if (tlAfter)
						{
							// ptrNew goes after ptrRef
							ptrCaller->prev		= ptrRef;			// New one points backward to reference
							ptrCaller->next		= ptrRef->next;		// New one points forward to what reference used to point to
							ptrRef->next		= ptrCaller;		// Reference points forward to thew new one

							// Update the one after where reference used to be
							if (ptrCaller->next)
								ptrCaller->next->prev = ptrCaller;	// One originally after reference points backward to new one

						} else {
							// ptrNew goes before ptrRef
							ptrCaller->next		= ptrRef;			// New one points forward to what reference
							ptrCaller->prev		= ptrRef->prev;		// New one points backward to what reference used to point backward to
							ptrRef->prev		= ptrCaller;		// Reference points backward to the new one

							// Update the one before where reference used to be
							if (ptrCaller->prev)
								ptrCaller->prev->next = ptrCaller;	// One originally before reference points forward to new one
						}
					}


				// When we get here, ptrCaller is either populated or NULL indicating success or failure
				return(ptrCaller);
			}
		}
		// If we get here, error
		return(NULL);
	}




	// NOTE!  Do not call this function directly!  Call iAppendToStarEndChain() only.
	void ivvm_SEChain_appendMasterList(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded)
	{
		// This function should not be called directly.  It is automatically called from
		// iAppendToStarEndChain().  It stores pointers in the master list, pointers
		// which are part of the chain in ptrSE->root..ptrSE->last.
		u32 lnI;


// UNTESTED CODE:  Breakpoint and examine!
		lnI = tnHint;
		while (1)
		{
			// Search for first unused item
			if (ptrSE->master)
			{
				// Check to see if there is an unused slot
				for ( ; lnI < ptrSE->masterCount; lnI++)
				{
					if (!ptrSE->master[lnI])
					{
						// This slot is unused, store it
						ptrSE->master[lnI] = ptrNew;

						// Update it
						ptrNew->used = true;

						// All done
						return;
					}
				}
				// If we get here, there were no unused slots
			}
			// If we get here, no slots are available, add some more

			// Allocate some pointer space
			vvm_SEChain_allocateAdditionalMasterSlots(ptrSE, tnBlockSizeIfNewBlockNeeded);
			// We never break out of this loop because we will always return above from it
		}
	}


	void ivvm_SEChain_freeUpSlot(SStartEnd* ptrSE, u32 tnSlot, u32 tnBlockSizeIfNewBlockNeeded)
	{
		u32		lnI;
		bool	llFound;


		//////////
		// See if the indicated slot is already open
		//////
			if (!ptrSE->master[tnSlot] || !ptrSE->master[tnSlot]->used)
				return;	// We're good already, the slot is free


		//////////
		// If we get here, we have to make room
		//////
			do {

				//////////
				// Find the first free slot after the indicated slot
				//////
					llFound = false;
					for (lnI = tnSlot + 1; lnI < ptrSE->masterCount; lnI++)
					{
						// Is this slot open?
						if (!ptrSE->master[lnI] || !ptrSE->master[lnI]->used)
						{
							// Yes
							llFound = true;
							break;
						}
					}


				//////////
				// Did we find a free slot?
				//////
					if (llFound)
						break;	// Yes


				//////////
				// We did not find room
				// Allocate some pointer space
				//////
					vvm_SEChain_allocateAdditionalMasterSlots(ptrSE, tnBlockSizeIfNewBlockNeeded);
					// We never break out of this loop because we will always return above from it

			} while (1);


		//////////
		// When we get here, lnI is the free slot
		//////
			for (--lnI; lnI <= tnSlot; lnI--)
			{
				// Move this slot to the next slot
				ptrSE->master[lnI+1] = ptrSE->master[lnI];
			}


		//////////
		// Free up the new slot
		//////
			ptrSE->master[tnSlot] = NULL;
	}

	bool CALLTYPE vvm_SEChain_allocateAdditionalMasterSlots(SStartEnd* ptrSE, u32 tnBlockSize)
	{
		bool			llResult;
		SMasterList**	lml;


		// Indicate failure initially
		llResult = false;

		// Make sure our environment is sane
		if (ptrSE)
		{
			// Make sure we're really doing something
			tnBlockSize = max(tnBlockSize, 1);

			// See where we are
			if (ptrSE->master)
			{
				// Allocate another _COMMON_START_END_BLOCK_SIZE pointers
				lml = (SMasterList**)realloc(ptrSE->master, sizeof(SMasterList*) * (ptrSE->masterCount + tnBlockSize));
				if (lml)
				{
					// We're good, initialize the new section
					ptrSE->master = lml;
					memset(&ptrSE->master[ptrSE->masterCount], 0, sizeof(SMasterList*) * tnBlockSize);
					ptrSE->masterCount += tnBlockSize;
					llResult = true;

				} else {
					// It failed here
// TODO:  Something major needs to happen here.  This is more or less a catastrophic failure.  It could require shutting down the VVM.
_asm int 3;
					ptrSE->masterCount += tnBlockSize;
				}

			} else {
				// Allocate the first N pointers
				ptrSE->master = (SMasterList**)malloc(sizeof(SMasterList*) * tnBlockSize);
				if (ptrSE->master)
				{
					// We're good, initialize the new section
					memset(&ptrSE->master[0], 0, sizeof(SMasterList*) * tnBlockSize);
					ptrSE->masterCount	= tnBlockSize;
					llResult = true;
				}
			}
		}
		// If we get here, failure
		return(llResult);
	}




//////////
//
// Migrate all SMasterList items from source to destination
//
//////
	void* CALLTYPE vvm_SEChain_migrateAll(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc)
	{
		u32 lnI, lnStartCount;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && ptrSESrc->masterCount > 0)
		{
			// Grab a reasonable starting point (the end), for the first hint
			lnStartCount = (ptrSEDst->masterCount >= _COMMON_START_END_BLOCK_SIZE) ? (ptrSEDst->masterCount - _COMMON_START_END_BLOCK_SIZE) : 0;

			// Iterate through every source
			for (lnI = 0; lnI < ptrSESrc->masterCount; lnI++)
			{
				// Copy every populated slot
				if (ptrSESrc->master[lnI] && ptrSESrc->master[lnI]->used)
				{
					// Append it to the destination list
					ivvm_SEChain_appendMasterList(ptrSEDst, ptrSESrc->master[lnI], lnStartCount + lnI, _COMMON_START_END_BLOCK_SIZE);

					// Clear out the source slot
					ptrSESrc->master[lnI] = NULL;
				}
			}
		}
		// Failure if we get here
		return(NULL);
	}




//////////
//
// Migrate the existing SMasterList item from one Start/end chain to another, by either pointer
// or physical position number
//
//////
	SMasterList* CALLTYPE vvm_SEChain_migrateByPtr(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, void* ptr, u32 tnHint, u32 tnBlockSize)
	{
		u32 lnI;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && ptrSESrc->masterCount >= 1)
		{
			for (lnI = 0; lnI < ptrSESrc->masterCount; lnI++)
			{
				// Is this our pointer?
				if (ptrSESrc->master[lnI] && ptrSESrc->master[lnI]->ptr == ptr)
				{
					// This is our man, migrate it
// TODO:  (enhancement) we want some kind of better hinting algorithm here, such as the end of the list - common block size, for now we'll just pass 0
					return(vvm_SEChain_migrateByNum(ptrSEDst, ptrSESrc, lnI, 0, tnBlockSize));
				}
			}
			// If we get here, not found
		}
		// Indicate failure
		return(NULL);
	}

	SMasterList* CALLTYPE vvm_SEChain_migrateByNum(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize)
	{
		u32				lnI;
		SMasterList*	lml;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && lnSrcNum < ptrSESrc->masterCount && lnSrcNum <= ptrSESrc->masterCount)
		{
			// We enter an infinite loop in case we have to
			while (1)
			{
				// Find an empty slot in the destination
				for (lnI = tnHint; lnI < ptrSEDst->masterCount; lnI++)
				{
					if (!ptrSEDst->master[lnI] || !ptrSEDst->master[lnI]->used)
					{
						// We found an empty slot, migrate it
						lml							= ptrSESrc->master[lnSrcNum];
						ptrSEDst->master[lnI]		= lml;

						// Clear out the source slot
						ptrSESrc->master[lnSrcNum]	= NULL;

						// See if the thing that was pointed to was the first or last entry (or both (only entry))
						if (ptrSESrc->root == lml)
						{
							// This was the first entry
							if (ptrSESrc->last == lml)
							{
								// And it was the last entry, making it the ONLY entry
								ptrSESrc->root = NULL;
								ptrSESrc->last = NULL;

							} else {
								// It was just the first entry
								ptrSESrc->root = (SMasterList*)lml->ll.next;
							}

						} else if (ptrSESrc->last == lml) {
							// It was the last entry
							ptrSESrc->last = (SMasterList*)lml->ll.prev;
						}
						//else it's just one in the middle, so no worries

						// Detach from its former list (former's previous points to former's next, former's next points to former's previous, basically they both skip over this item)
						if (lml->ll.prev)	((SMasterList*)(lml->ll.prev))->ll.next = lml->ll.next;
						if (lml->ll.next)	((SMasterList*)(lml->ll.next))->ll.prev = lml->ll.prev;
						// Right now, lml is an orphan, but it has pointers to its old slots

						// Append it to the new list, and update its pointers to its new home
						if (!ptrSEDst->root)
						{
							// This is the first item in the destination
							ptrSEDst->root	= lml;
							ptrSEDst->last	= lml;
							lml->ll.prev	= NULL;

						} else {
							// Append it to the end of the chain
							ptrSEDst->last->ll.next = (SLL*)lml;
							lml->ll.prev			= (SLL*)ptrSEDst->last;
							ptrSEDst->last			= lml;
						}
						// Make the newly migrated item now point to nothing, because it is the last item
						lml->ll.next = NULL;

						// All done!
						return(lml);
					}
				}
				// If we get here, no empty slots. Allocate some, rinse, and repeat. :-)
				vvm_SEChain_allocateAdditionalMasterSlots(ptrSEDst, tnBlockSize);

				// Process through again beginning at the newly added portion
				tnHint = lnI;
				// We'll never break out of this loop because we will always return above
			}
			// Control will never get here
		}
		// If we get here, error
		return(NULL);
	}




//////////
//
// Migrate the existing SMasterList item, and its associated SLL item, from one Start/end chain
// to another, by either pointer or physical position number.
//
//////
	SLL* CALLTYPE vvm_SEChain_completelyMigrateSLLByPtr(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr, u32 tnHint, u32 tnBlockSize)
	{
		u32 lnI;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && ptrSESrc->masterCount >= 1)
		{
			for (lnI = 0; lnI < ptrSESrc->masterCount; lnI++)
			{
				// Is this our pointer?
				if (ptrSESrc->master[lnI] && ptrSESrc->master[lnI]->ptr == (void*)ptr)
				{
					// This is our man, migrate it
// TODO:  (enhancement) we want some kind of better hinting algorithm here, such as the end of the list - common block size, for now we'll just pass 0
					return(vvm_SEChain_completelyMigrateSLLByNum(ptrSEDst, ptrSESrc, lnI, 0, tnBlockSize));
				}
			}
			// If we get here, not found
		}
		// Indicate failure
		return(NULL);
	}

	SLL* CALLTYPE vvm_SEChain_completelyMigrateSLLByNum(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize)
	{
		SLL*			lllPrev;
		SLL*			lllNext;
		SLL*			lll;
		SMasterList*	lml;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && lnSrcNum < ptrSESrc->masterCount && lnSrcNum <= ptrSESrc->masterCount)
		{
			// Migrate it, and get its SMasterList entry
			lml = vvm_SEChain_migrateByNum(ptrSEDst, ptrSESrc, lnSrcNum, tnHint, tnBlockSize);
			if (lml && lml->ptr)
			{
				// Grab the pointer to the SLL entry
				lll = (SLL*)lml->ptr;
				// Right now, lll points to the SLL* object from ptrSESrc

				// Grab ptrSESrc's preceding, and following objects (if any)
				lllPrev	= lll->prev;
				lllNext = lll->next;


				//////////
				// Update the ptrSESrc entry, to remove this lll entry from its lists
				//////
					// Update the pointer for the preceding entry
					if (lllPrev)
						lllPrev->next = lllNext;
					// Update the pointer for the following entry
					if (lllNext)
						lllNext->prev = lllPrev;
					// Right now, lllPrev points forward past lll, and lllNext points backward past lll


				//////////
				// lll is currently an orphan entry that thinks it's not orphaned because it still has prev and next pointers potentially pointing off somewhere
				//////
					// Update lll's prev and next entries to point nowhere
					lll->next = NULL;
					lll->prev = NULL;
					// At this point, lll is only pointed to by its lml entry.


				// All done!
				return(lll);
			}
		}
		// If we get here, invalid environment
		return(NULL);
	}




//////////
//
// Counts how many actual items in the masterCount are valid (contain entries that are in use,
// versus
//
//////
	u32 CALLTYPE vvm_SEChain_countValids(SStartEnd* ptrSE)
	{
		u32	lnI, lnValidCount;


		// Make sure our environment is sane
		if (!ptrSE)
			return(0);

		// Iterate through each one, and for every valid entry increase our count
		for (lnValidCount = 0, lnI = 0; 
			 lnI < ptrSE->masterCount; 
			 lnI++)
		{
			// If this entry is valid, increase our count
			if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				++lnValidCount;
		}
		// Return our value
		return(lnValidCount);
	}




//////////
//
// Called to delete an entire Start/end chain
//
// Returns:
//		-1 error in ptrSE, ptrSE->master or ptrSE->masterCount
//		Number of records deleted
//
//////
	u32 CALLTYPE vvm_SEChain_delete(SStartEnd* ptrSE, u64 tnCallback, u64 tnParam, bool tlDeletePointers)
	{
		u32			lnI, lnDeletedCount;
		union {
			u64		_callbackAddress;
			void	(*callbackAddress)(void* ptrSE, u64 tnParam);
		};


		// Make sure the environment's sane
		if (ptrSE && ptrSE->master && ptrSE->masterCount != 0)
		{
			// Store our callback address
			_callbackAddress = tnCallback;

			//  Iterate through all entries
			lnDeletedCount = 0;
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				{
					// Callback to the caller if they need to do something special to delete this entry
					if (tnCallback != 0)
						callbackAddress(ptrSE->master[lnI]->ptr, tnParam);

					// Delete the pointer from the list
					vvm_SEChain_deleteFrom(ptrSE, ptrSE->master[lnI]->ptr, tlDeletePointers);
					++lnDeletedCount;
				}
			}
			// When we get here, everything's deleted, now delete the container for everything. :-)
			free(ptrSE->master);
			ptrSE->master = NULL;

			// Indicate the number we deleted
			return(lnDeletedCount);
		}
		// Indicate failure
		return(-1);
	}




//////////
//
// Called to delete an entire Start/end chain
//
// Returns:
//		-1 error in ptrSE, ptrSE->master or ptrSE->masterCount
//		Number of records deleted
//
//////
	void CALLTYPE vvm_SEChain_deleteAsPtrBlock(SStartEnd* ptrSE)
	{
		// Make sure the environment's sane
		if (ptrSE && ptrSE->master && ptrSE->masterCount != 0)
		{
			// When we get here, everything's deleted, now delete the container for everything. :-)
			free(ptrSE->master);
			ptrSE->master = NULL;
		}
	}




//////////
//
// Delete the indicated item from the chain
//
//////
	void CALLTYPE vvm_SEChain_deleteFrom(SStartEnd* ptrSE, void* ptrCaller, bool tlDeletePointers)
	{
		u32				lnI;
		SMasterList*	ptrDel;
		SMasterList**	master;


		// See where we are
// UNTESTED CODE:  Breakpoint and examine!
		if (ptrSE)
		{
			if (!ptrSE->root)
			{
				// There are no existing items, nothing to do, why are they messing around with our brains? :-)
				return;
			}

			// Iterate through the master list to find the matching record to delete in the chain
			master = ptrSE->master;
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// See if this item matches
				ptrDel = master[lnI];
				if (ptrDel && ptrDel->used && ptrDel->ptr == ptrCaller)
				{
					// Mark it as not being used
					ptrDel->used = false;

					// Remove it from its chain
					if (ptrDel == ptrSE->root)
					{
//////////
// This is the first item
//////
						// We are deleting the first item in the list
						if (ptrDel == ptrSE->last)
						{
							// Which is also the last item in the list
							ptrSE->root = NULL;
							ptrSE->last = NULL;
							// No items exist after this

						} else {
							// It's just the first item in a chain
							ptrSE->root = (SMasterList*)ptrDel->ll.next;
						}


					} else if (ptrDel == ptrSE->last) {
//////////
// This is the last item
//////
						// We are deleting the last item in the list
						ptrSE->last									= (SMasterList*)ptrDel->ll.prev;	// This will never be NULL because we've already checked the first condition
						((SMasterList*)(ptrDel->ll.prev))->ll.next	= NULL;								// Make the one before this point to nothing, because it is now the last item


					} else {
//////////
// This is an entry in the middle somewhere
//////
						// We are deleting an entry in the middle somewhere
						((SMasterList*)(ptrDel->ll.prev))->ll.next	= ptrDel->ll.next;		// Make the one before this point to the one after this
						((SMasterList*)(ptrDel->ll.next))->ll.prev	= ptrDel->ll.prev;		// Make the one after this point to the one before this
					}
					// When we get here, the start/end chain is updated


					// Release our SMasterList pointer
					free(ptrDel);
					master[lnI] = NULL;


					// Release the caller's memory (or not if they want to keep it)
					if (tlDeletePointers)
						free(ptrCaller);		// Delete this pointer
					// All done
				}
			}
		}
		//else not found
	}




//////////
//
// Search by callback for the indicated element, and when found delete it
//
//////
	bool CALLTYPE vvm_SEChain_deleteFromAfterCallback(SStartEnd* ptrSE, bool tlDeletePointers, SStartEndCallback* cb)
	{
		u32		lnI;
		bool	llResult;


		// Make sure the environment is sane
		llResult = false;
		if (ptrSE)
		{
			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Ask the caller if this is it
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				{
					// Store the pointer for reference
					cb->ptr = ptrSE->master[lnI]->ptr;

					// Perform the call
					if (cb->funcBool(cb))
					{
						// This is the entry they want to delete
						vvm_SEChain_deleteFrom(ptrSE, ptrSE->master[lnI]->ptr, tlDeletePointers);
						llResult = true;
						break;
					}
				}
			}
		}
		// If we get here, it wasn't found
		return(llResult);
	}






//////////
//
// Search for the indicated uniqueId in the chain.
//
// Returns:
//		NULL if error
//		The associated pointer if found
//
//////
	struct SScreen2
	{
		SLL				ll;						// 2-way link list
		u64				associatedId;			// A user-defined id of something associated with this screen

		// Limited access is granted during a refresh operation
		u64				semRefresh;				// Limited access to 
		bool			isRefreshing;			// Is this screen refreshing?

		// Associated canvas for this screen
		void*			activeCanvas;			// Pointer to this screen's active canvas (must be a member of the canvastList
		SStartEnd		canvasList;				// Pointer to this screen's first SCanvasList entry

		// Internal information used to make it happen for the target OS
		u64				ossWindowId;			// information necessary to render this screen on the OSS (pointer to _iSWindow struct, for example)
	};
	void* CALLTYPE vvm_SEChain_searchByUniqueId(SStartEnd* ptrSE, u64 tnUniqueId)
	{
		u32 lnI;


		// Make sure the environment is sane
		if (ptrSE)
		{
			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used && ((SLL*)(ptrSE->master[lnI]->ptr))->uniqueId == tnUniqueId)
				{
					// We've found our man
					return(ptrSE->master[lnI]->ptr);
				}
			}
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Search for the indicated record in the chain by using a user-defined callback on the pointer.
// Callback function should return true when found, false to continue sending other items back.
//
// Returns:
//		NULL if error
//		The associated pointer if found
//
//////
	void* CALLTYPE vvm_SEChain_searchByCallback(SStartEnd* ptrSE, SStartEndCallback* cb)
	{
		u32 lnI;


		// Make sure the environment is sane
		if (ptrSE)
		{
			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Ask the caller if this is it
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				{
					// Store the pointer for the caller
					cb->ptr = ptrSE->master[lnI]->ptr;

					// Perform the call
					if (cb->funcBool(cb))
						return(ptrSE->master[lnI]->ptr);	// We've found our man
				}
			}
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Iterates through the indicated Start/End list, calling back the callback function for every item.
//
//////
	void CALLTYPE vvm_SEChain_iterateThroughForCallback(SStartEnd* ptrSE, SStartEndCallback* cb)
	{
		u32 lnI;


		// Make sure the environment is sane
		if (ptrSE)
		{
			// Iterate through the master list calling every valid entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Give this to the caller for their processing
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				{
					// Store the pointer for the caller
					cb->ptr = ptrSE->master[lnI]->ptr;

					// Perform the call
					cb->funcVoid(cb);
				}
			}
		}
	}




//////////
//
// Added for debugging.  Validates that all of the entries in a Start/end chain have proper
// ll.prev and ll.next members.  Should only need to be used during initial development, and
// in tracking down future bugs.  I intend for these Start/end functions to be heavily tested
// and made completely reliable in all conditions.
//
// If the func is populated, then if it returns:
//			true		- test was good
//			false		- test failed
// Note:  The callback is only needed if the lml->ptr structure itself has Start/end members
//        that need to be examined.  If func is not populated, only tests
//        the members contained in the ptrSE Start/end structure.
//
// This function doesn't return anything.
// If there is an error, it will trap to the debugger so the machine state can be examined.
//
//////
	void CALLTYPE vvm_SEChain_validate(SStartEnd* ptrSE, SStartEndCallback* cb)
	{
		u32				lnI;
		SMasterList*	lml;


		// Make sure the environment is sane
		if (ptrSE && cb)
		{
			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Ask the caller if this is it
				lml = ptrSE->master[lnI];
				if (lml && lml->used)
				{
					if (lml == ptrSE->root)
					{
						if (lml == ptrSE->last)
						{
							// This is the ONLY entry
							// ll.prev and ll.next need to be null
							if (lml->ll.prev != NULL)
								_asm int 3;
							if (lml->ll.next != NULL)
								_asm int 3;

						} else {
							// This is the first entry
							// ll.prev needs to be null, ll.next needs to be not null
							if (lml->ll.prev != NULL)
								_asm int 3;
							if (lml->ll.next == NULL)
								_asm int 3;
						}

					} else if (lml == ptrSE->last) {
						// This is the last entry
						// ll.prev needs to be not null, ll.next needs to be null
						if (lml->ll.prev == NULL)
							_asm int 3;
						if (lml->ll.next != NULL)
							_asm int 3;

					} else {
						// Somewhere in the middle
						// ll.prev and ll.next need to be not null
						if (lml->ll.prev == NULL)
							_asm int 3;
						if (lml->ll.next == NULL)
							_asm int 3;
					}

					// If there's a callback on this entry, try it out
					// If it returns false, there's an issue, if it returns true it's okay
					cb->ptr = lml->ptr;
					if (!cb->funcBool(cb))
						_asm int 3;
				}
			}
		}
	}




//////////
//
// Called to reverse the endian
//
//////
	u32 CALLTYPE vvm_swapEndian(u32 tnValue)
	{
		_asm {
			mov		eax,tnValue
			bswap	eax
			mov		tnValue,eax
		}
		return tnValue;
	}




//////////
//
// For certain operations, colors are reversed
//
//////
	u32 CALLTYPE vvm_RGBA2BGRA(u32 tnColor)
	{
		u8 lnRed, lnGrn, lnBlu, lnAlp;


		// Grab the indicated colors
		lnRed	= red(tnColor);
		lnGrn	= grn(tnColor);
		lnBlu	= blu(tnColor);
		lnAlp	= alp(tnColor);

		// Encode and return the new color
		return(rgba(lnBlu, lnGrn, lnRed, lnAlp));
	}




//////////
//
// Allocate the indicated size memory block, and initialize it to nulls
//
// Returns:
//		pointer to the newly allocated block
//
// Note:  The allocated memory is initialized to null if allocated successfully
//
//////
	void* CALLTYPE vvm_allocateAndNull(u32 tnSize, bool tnInitToZeros)
	{
		s8* lp;


		// Allocate
		lp = (s8*)malloc(tnSize);

		// Null if valid
		if (lp && tnInitToZeros)
			vvm_memset(lp, 0, tnSize);

		// Return the fruits of our labor
		return(lp);
	}




//////////
//
// Called to search the haystack for the needle
//
//////
	bool CALLTYPE vvm_isNeedleInHaystack(csu8p tcHaystack, s32 tnHaystackLength, csu8p tcNeedle, s32 tnNeedleLength, bool tlCaseSensitive, u32* tnFoundPosition)
	{
		s32		lnI;
		u32		lnResult;
		csu8p	ptr;


		// Make sure our environment's sane
		if (tcHaystack._cu8 && tcNeedle._cu8 && tnHaystackLength > 0 && tnNeedleLength > 0 && tnHaystackLength >= tnNeedleLength)
		{
			// Iterate until we reach the end
			for (lnI = 0; lnI + tnNeedleLength <= tnHaystackLength; lnI++)
			{
				// Get this offset to this location
				ptr._cu8 = tcHaystack._cu8 + lnI;

				// Scan from this location
				if (tlCaseSensitive)	lnResult = vvm_memcmp(ptr, tcNeedle, tnNeedleLength);
				else					lnResult = vvm_memicmp(ptr, tcNeedle, tnNeedleLength);

				// What were the findings?
				if (lnResult == 0)
				{
					// It was found, store the position
					if (tnFoundPosition)
						*tnFoundPosition = lnI;

					// Indicate success
					return(true);
				}
			}
		}
		// If we get here, failure
		if (tnFoundPosition)
			*tnFoundPosition = -1;

		// Indicate failure
		return(false);
	}




//////////
//
// Search the specified unicode string haystack for the needle
//
//////
	bool CALLTYPE vvm_isNeedleInHaystack_Unicode(w16* twHaystack, w16* twNeedle)
	{
		s32 lnI, lnLengthHaystack, lnLengthNeedle;


		// Make sure our environment's sane
		if (twHaystack && twNeedle)
		{
			// Get the lengths
			lnLengthHaystack	= wcslen(twHaystack);
			lnLengthNeedle		= wcslen(twNeedle);

			// Repeat throughout the unicode string
			for (lnI = 0; lnI <= lnLengthHaystack - lnLengthNeedle; lnI++)
			{
				// Did we find a match?
				if (_wcsicmp(twHaystack + lnI, twNeedle) == 0)
					return(true);
			}
		}
		// If we get here, not found
		return(false);
	}




//////////
//
// Scans forward so long as there are numerical digits (ASCII-48 through ASCII-57, "0" through "9")
//
//////
	u32 CALLTYPE vvm_countConsecutiveAsciiNumericDigits(s8* buffer, u32 tnMaxLength)
	{
		u32 lnLength;


		// While we have numbers, continue
		for (lnLength = 0;		lnLength < tnMaxLength && buffer[lnLength] >= '0' && buffer[lnLength] <= '9';		)
			++lnLength;

		// We have our length
		return(lnLength);
	}




//////////
//
// Reads through the numbers, presumably previously determined by iScanConsecutiveNumbers(),
// to obtain the numerical value after converting from text to an unsigned integer
//
//////
	u32 CALLTYPE vvm_convertTextToU32(s8* tcNumbers, u32 tnMaxLength)
	{
		u32 lnLength, lnValue, lnMultiplier;


		// Scan through every number
		for (lnLength = 0, lnValue = 0, lnMultiplier = 10;
			 lnLength < tnMaxLength;
			 lnLength++)
		{
			lnValue = (lnValue * lnMultiplier) + (u32)(tcNumbers[lnLength] - '0');
		}

		// We have our converted value
		return(lnValue);
	}




//////////
//
// Called to perform various math operations.
//
// Heron's formula:  area = sqrt(s*(s-a)*(s-b)*(s-c))
//                      s = (a+b+c) / 2
//                      a = length(p1,p2)    // tri->l12
//                      b = length(p2,p3)    // tri->l23
//                      c = length(p3,p1)    // tri->l31
//
//////
	// Given three points, what are the side lengths, semiperimeter, and area
	void CALLTYPE vvm_math_computeTriangle(STriangleInOutF64* tri)
	{
		if (tri && tri->input && tri->output)
			iivvm_math_computeTriangle(tri->input);
	}

	// Given the 4 points of a square, the origin by which it rotates around, and the radians to
	// rotate, compute the new four point locations.  To do this, we assume all the points are proper.
	// Note:  If they are not the computation will not be correct, but it will not cause an error.
	void CALLTYPE vvm_math_computeSquare(SSquareInOutF64* sq, f32 ox, f32 oy)
	{
		// Make sure our environment is sane
		if (sq && sq->input && sq->compute && sq->output)
			iivvm_math_computeSquare(sq, ox, oy);
	}

	// Called to compute the midpoint of a line, its length, slope, and perpendicular slope.
	void CALLTYPE vvm_math_computeLine (SLineF64* line)
	{
		if (line)
			iivvm_math_computeLine(line);
	}




//////////
//
// Given the 4 points of a square, the origin by which it rotates around, and the radians to
// rotate, compute the new four point locations.  To do this, we assume all the points are proper
// or that a call to vvm_math_computeSquare() was done immediately prior.
//
// Note:  If they are not the computation will not be correct, but it will not cause an error.
//
//////
	void CALLTYPE vvm_math_squareRotateAbout(SSquareInOutF64* sq)
	{
		if (sq)
			ivvm_math_squareRotateAbout(sq);
	}




//////////
//
// Called to get the decorated gravity of the indicated theta and left setting
//
//////
	u32 CALLTYPE vvm_math_getGravityOfThetaAndLeft(f64 tfTheta, bool tlLeft)
	{
		return(iivvm_math_getGravityOfThetaAndLeft(tfTheta, tlLeft));
	}




//////////
//
// Called to obtain the 0..7 gravity range from a decorated gravity setting
//
//////
	s32 CALLTYPE vvm_math_getGravity07FromDecoratedGravity(u32 tnGravityDecorated)
	{
		return(iivvm_math_getGravity07FromDecoratedGravity(tnGravityDecorated));
	}




//////////
//
// Called to compute the partial area of a square using an intersect/origin point, and then
// two points which are on the X-Intercept or Y-Intercept axes.  It computes the area based on
// gravity relative to the first line (PO..P1).
//
// Note:  The two Intersect gravities are where the intercept it the line in the 0..7 form.
// Note:  The line1 gravity indicates which part of the area should be computed, it's either the
//        side of the portion which is smaller or larger (unless it cuts the square exactly in half).
//
//////
	f64 CALLTYPE vvm_math_getAreaOfSquareUsing_po_p1_p2(s32 tnGravity07_po, s32 tnGravity07_p1, s32 tnGravity07_p2, SXYF64* po, SXYF64* p1, SXYF64* p2)
	{
		return(iivvm_math_getAreaOfSquareUsing_po_p1_p2(tnGravity07_po, tnGravity07_p1, tnGravity07_p2, po, p1, p2));
	}




//////////
//
// Gets the next intercept given a point and a theta
//
//////
	void CALLTYPE vvm_math_getNextAxisInterceptXY(SXYF64* p, f64 tfTheta)
	{
		if (p)		iivvm_math_getNextAxisInterceptXY(p, tfTheta);		// Compute it
	}




//////////
//
// Gets the gravity of p relative to po
//
//////
	s32 CALLTYPE vvm_math_getGravityByRelativePosition(SXYF64* p, SXYS32* po)
	{
		if (p && po)		return(iivvm_math_getGravityByRelativePosition(p, po));
		else				return(-1);
	}




//////////
//
// Gets the gravity of p relative to po as per the entire pixel's position
//
//////
	s32 CALLTYPE vvm_math_getGravityInteger(SXYS32* p, SXYS32* po)
	{
		if (p && po)		return(iivvm_math_getGravityInteger(p, po));
		else				return(-1);
	}




//////////
//
// Gets the true gravity position by slope when the gravity is on the same axis as another point
// or points.  Only PO, PG and one of either P1 or P2 are required.  If 
//
//////
	s32 CALLTYPE vvm_math_fineAdjustGravityByTheta(SXYF64* po, SXYF64* p, SXYF64* pg, s32 lnGravity07p, s32 lnGravity07pg)
	{
		// If they sent us valid parameters, we adjust, otherwise whatever it is passes through
		if (po && p && pg)		return(iivvm_math_fineAdjustGravityByTheta(po, p, pg, lnGravity07p, lnGravity07pg));
		else					return(lnGravity07pg);
	}




//////////
//
// Called to adjust theta into the range 0..2pi
//
//////
	f64 CALLTYPE vvm_math_adjustTheta(f64 tfTheta)
	{
		return(iivvm_math_adjustTheta(tfTheta));
	}




//////////
//
// Called to determine if the indicated floating point values are within the delta
//
//////
	bool CALLTYPE vvm_math_withinDelta(f64 tfValue1, f64 tfValue2, s32 tnDeltaDecimals)
	{
		return(iivvm_math_withinDelta(tfValue1, tfValue2, tnDeltaDecimals));
	}




//////////
//
// Called to wash the floans.  Some floan generating algorithms are inside of pixels, sometimes
// with many points being inside a single pixel.  This washing algorithm removes those extra
// points and only includes points which explicitly hit an X- or Y-Intercept pixel boundary.
// This allows the data to be used for later floan computation more accurately.
//
// It should be noted that there may be some loss or gain of floan area due to the rounding.
// To bypass this, it is recommended to scale the floans up to some higher level, wash the
// pixels there, and then scale back down and add up the alphas.  However, depending on the
// source, the difference is likely to be very small, and typically not visually perceptible
// (such as with bezier curve point data).
//
//////
	u64 CALLTYPE vvm_math_washFloans(SCanvas* tc, SBGRA* bd, SBuilder** pointFloans, SBuilder** washFloans, SBuilder** drawFloans, bool tlIsFilledLeft)
	{
		if (pointFloans && washFloans)		return(iivvm_math_washFloans(tc, bd, pointFloans, washFloans, drawFloans, tlIsFilledLeft));
		else								return(false);
	}




//////////
//
// Called to initialize a bezier curve to the indicated points, and resolution
//
//////
	bool CALLTYPE vvm_bezier_initialize(SBezier* bez, u32 tnCurveCount, u32 tnComputePointCount, bool tlWash)
	{
		if (bez && tnCurveCount >= 3 && tnCurveCount <= 5)
		{
// TODO:  We may want to manually verify that the floan components are released here
			// Initialize
			memset(bez, 0, sizeof(SBezier));

			// Store parameters
			bez->curveCount			= tnCurveCount;
			bez->computePointCount	= tnComputePointCount;
			bez->wash				= tlWash;

			// Indicate success
			return(true);

		} else {
			// Failure of some kind
			return(false);
		}
	}




//////////
//
// Called to set the bezier curve values based upon the indicated points
//
//////
	bool CALLTYPE vvm_bezier_setByValues(SBezier* bez, SBGRA color, SXYF64* p1, SXYF64* p2, SXYF64* p3, SXYF64* p4, SXYF64* p5)
	{
		bool llSuccess;


		// Make sure our environment is sane
		llSuccess = false;
		if (bez)
		{
			// Store the color
			bez->color = color;

			// Test each explicitly to indicate success or failure
			if (bez->curveCount == 3 && p1 && p2 && p3)
			{
				// P1
				bez->p1.x = p1->x;
				bez->p1.y = p1->y;
				// P2
				bez->p2.x = p2->x;
				bez->p2.y = p2->y;
				// P3
				bez->p3.x = p3->x;
				bez->p3.y = p3->y;
				// We're good
				llSuccess = true;

			} else if (bez->curveCount == 4 && p1 && p2 && p3 && p4) {
				// P1
				bez->p1.x = p1->x;
				bez->p1.y = p1->y;
				// P2
				bez->p2.x = p2->x;
				bez->p2.y = p2->y;
				// P3
				bez->p3.x = p3->x;
				bez->p3.y = p3->y;
				// P4
				bez->p4.x = p4->x;
				bez->p4.y = p4->y;
				// We're good
				llSuccess = true;

			} else if (bez->curveCount == 5 && p1 && p2 && p3 && p4 && p5) {
				// P1
				bez->p1.x = p1->x;
				bez->p1.y = p1->y;
				// P2
				bez->p2.x = p2->x;
				bez->p2.y = p2->y;
				// P3
				bez->p3.x = p3->x;
				bez->p3.y = p3->y;
				// P4
				bez->p4.x = p4->x;
				bez->p4.y = p4->y;
				// P5
				bez->p5.x = p5->x;
				bez->p5.y = p5->y;
				// We're good
				llSuccess = true;
			}
		}

		// Indicate our success or failure
		return(llSuccess);
	}




//////////
//
// Called to initialize a polygon to the number indicated by poly->lineCount.
//
//////
	bool CALLTYPE vvm_polygon_initialize(SPolygon* poly, u32 tnLineCount, bool tlAllocatePolyLines)
	{
		if (poly && (s32)tnLineCount >= 1)
		{
			// Pass it through
			return(iivvm_polygon_initialize(poly, tnLineCount, tlAllocatePolyLines));

		} else {
			// Indicate our failure
			return(false);
		}
	}




//////////
//
// Called to set the indicated polyline for the indicated polygon.
//
///////
	bool CALLTYPE vvm_polygon_setByPolyLine(SPolygon* poly, u32 tnEntry, SPolyLine* line)
	{
		if (poly && tnEntry < poly->lineCount)
		{
			// Pass it through
			return(iivvm_polygon_setByPolyLine(poly, tnEntry, line));

		} else {
			// Indicate our failure
			return(false);
		}
	}




//////////
//
// Called to set the indicated polyline for the indicated polygon by values.
//
//////
	bool CALLTYPE vvm_polygon_setByValues(SPolygon* poly, u32 tnEntry, SXYF64* start, SXYF64* end, SXYF64* gravity)
	{
		if (poly && tnEntry < poly->lineCount && start && end && gravity)
		{
			// Pass it through
			return(iivvm_polygon_setByValues(poly, tnEntry, start, end, gravity));

		} else {
			// Indicate our failure
			return(false);
		}
	}




//////////
//
// Called to reset the polygon listing to empty.  This will force the polygon to be recomputed on
// the next use, rather than just using the previously computed polygon floan data.
//
//////
	bool CALLTYPE vvm_polygon_reset(SPolygon* poly, bool tlResetFloans)
	{
		if (poly)
		{
			// Should we actually release the floans?
			if (tlResetFloans)
			{
				// Yes, release both pixel floans and range floans
				vvm_builderFreeAndRelease(&poly->pixelFloans);
				vvm_builderFreeAndRelease(&poly->rangeFloans);

			} else {
				// Reset them locally to empty
				poly->pixelFloans = NULL;
				poly->rangeFloans = NULL;
			}

			// All done
			return(true);

		} else {
			return(false);
		}
	}




//////////
//
// Called to release the polygon and optionally free the floans
//
//////
	bool CALLTYPE vvm_polygon_freeAndRelease(SPolygon* poly, bool tlReleaseFloans)
	{
		u32 lnI;
		

		// First, reset the polygon
		if (poly && vvm_polygon_reset(poly, tlReleaseFloans))
		{
			// Then release its lines
			for (lnI = 0; lnI < poly->lineCount; lnI++)
			{
				// Delete this line
				free(poly->line[lnI]);
			}

			// Release the physical polygon
			free(poly);

			// All done, indicate success
			return(true);

		} else {
			// Nothing to do, indicate failure
			return(false);
		}
	}




//////////
//
// Refreshes the screen (draws all regions within)
//
//////
	u64 CALLTYPE vvm_screenRefresh(SScreen* ts)
    {
		u64				lnPixelsDrawn;
		SOssWindowLL*	w;



		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (ts && ts->activeRegion && ts->activeRegion->canvas)
		{
			// Refresh this region
			if (vvm_regionRefresh(ts->activeRegion, NULL) != 0)
			{
				// Something was updated, refresh this screen
				w = oss_find_iswSOssWindowLL_By_iOssWindowId(ts->_iOssWindowId);
				if (w)
				{
					// See if the window is the same size
					if (w->isw.width == ts->activeRegion->canvas->width && w->isw.height == ts->activeRegion->canvas->height)
					{
						// They are the same size, use the standard window drawing
						lnPixelsDrawn = oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb(ts->_iOssWindowId, ts->activeRegion->canvas->bd, ts->activeRegion->canvas->width, ts->activeRegion->canvas->height);

					} else {
						// They are not the same size, scale the canvas up/down to the destination size, and then draw
						vvm_canvasScale(ts->activeRegion->canvasScale, ts->activeRegion->canvas, &ts->activeRegion->canvasScale->firstScaleMap);
						lnPixelsDrawn = oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb(ts->_iOssWindowId, ts->activeRegion->canvasScale->bd, ts->activeRegion->canvasScale->width, ts->activeRegion->canvasScale->height);
					}
				}
			}
		}
		// Indicate our success or failure
		return(lnPixelsDrawn);
    }




//////////
//
// Called to specify that the indicated screen should have keyboard focus
//
//////
	bool CALLTYPE vvm_screenSetFocus(SScreen* ts)
	{
		SOssWindowLL* low;


		// Make sure the environment is sane
		if (ts)
		{
			// Make sure the screen they indicated is valid
			low = oss_findSOssWindowLLByScreenId(ts->_iOssWindowId);
			if (low)
			{
				// Sends the WM_SETFOCUS message so it hits the window-owner thread, which then
				// signals the events for change of focus
				SetFocus((HWND)low->isw.osHandle);
				return(true);
			}
		}

		// The window wasn't found
		return(false);
	}




//////////
//
// Returns a copy/duplicate or the template region
//
///////
	SRegion* CALLTYPE vvm_regionDuplicate(u64 tnAssociatedId, SRegion* templateRegion)
	{
		return(NULL);
	}




//////////
//
// Called to paint a region using the default algorithms
//
//////
	u64 CALLTYPE vvm_regionDefaultPaint(SRegion* tr)
	{
		u64 lnPixelsDrawn;
		u32 lnType;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tr->canvas && tr->data)
		{
			// Make sure there's a canvas we have to display something
			lnType = tr->type & _VVM_REGION_I_CANVAS_MASK;
			switch (lnType)
			{
				case _VVM_REGION_EDITBOX:
					lnPixelsDrawn = vvm_iRegionDefaultPaintEditbox(tr, tr->canvas, tr->canvas->bda, (SRegionEditboxData*)tr->data);
					break;

				case _VVM_REGION_BUTTON:
					lnPixelsDrawn = vvm_iRegionDefaultPaintButton(tr, tr->canvas, tr->canvas->bda, (SRegionButtonData*)tr->data);
					break;

				case _VVM_REGION_IMAGE:
					lnPixelsDrawn = vvm_iRegionDefaultPaintImage(tr, tr->canvas, tr->canvas->bda, (SRegionImageData*)tr->data);
					break;

				case _VVM_REGION_LABEL:
					lnPixelsDrawn = vvm_iRegionDefaultPaintLabel(tr, tr->canvas, tr->canvas->bda, (SRegionLabelData*)tr->data);
					break;

				case _VVM_REGION_CHECKBOX:
					lnPixelsDrawn = vvm_iRegionDefaultPaintCheckbox(tr, tr->canvas, tr->canvas->bda, (SRegionCheckboxData*)tr->data);
					break;

				case _VVM_REGION_RECTANGLE:
					lnPixelsDrawn = vvm_iRegionDefaultPaintRectangle(tr, tr->canvas, tr->canvas->bda, (SRegionRectangleData*)tr->data);
					break;

				default:
					// There is no default type that is recognized
					ivvm_regionDoDefaultDebugTrapCallback(tr, _VVM_DEBUGTRAP_UNKNOWN_TYPE, lnType);
					break;
			}
		}
		// Indicate how many pixels were drawn
		return(lnPixelsDrawn);
	}




//////////
//
// Called to refresh this region by drawing all sub-regions within
//
//////
	u64 CALLTYPE vvm_regionRefresh(SRegion* tr, SRegion* trParent)
	{
		u32					lnPixelsDrawn;
		SStartEndCallback	cb;


		// Prepare our callback
		// Note:  We use cb->count1 for the pixels drawn
		memset(&cb, 0, sizeof(cb));

		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr->canvas)
		{
			//////////
			// Lock the canvas's semaphore for drawing
			//////
//				oss_lockSemaphore(tr->canvas->semRefresh);


			//////////
			// Paint the region
			//////
				// See if it has its own repaint algorithm
				if (tr->callback.region._callback_paint != 0)
				{
					// Custom callback for painting
					cb.count1 += tr->callback.region.callback_paint(tr, tr->canvas, tr->canvas->bd);

				} else {
					// Paint the background
					cb.count1 += vvm_canvasFillRect(tr->canvas, tr->canvas->bd, 0, 0, tr->canvas->width, tr->canvas->height, 0, tr->canvas->backColor, tr->canvas->backColor);

					// Use a default drawing algorithm
					cb.count1 += vvm_regionDefaultPaint(tr);
				}


			//////////
			// Iterate through any child regions, redrawing them as necessary
			//////
				if (tr->subRegions.masterCount != 0)
				{
					cb._func		= (u64)&ivvm_regionRefreshCallback;
					cb.ex2PtrRegion	= trParent;
					vvm_SEChain_iterateThroughForCallback(&tr->subRegions, &cb);
				}


			//////////
			// Draw this item onto its parent (if any)
			//////
				if (trParent && trParent->canvas)
				{
					// Paint it onto the parent
					if (tr->canvas->width == tr->width && tr->canvas->height == tr->height)
					{
						// The region is the same size as the canvas, do a literal bitBlt
						cb.count1 += vvm_canvasBitBlt(trParent->canvas, false, 
														(s32)(tr->x * (f32)trParent->canvas->width),
														(s32)(tr->y * (f32)trParent->canvas->height),
														tr->canvas, false, 0, 0, tr->canvas->width, tr->canvas->height);

					} else {
						// They are not the same size.  Perfor the scale, and then do the bitBlt
						vvm_canvasScale(tr->canvasScale, tr->canvas, &tr->canvasScale->firstScaleMap);
						cb.count1 += vvm_canvasBitBlt(trParent->canvas, false, 
														(s32)(tr->x * (f32)trParent->canvas->width),
														(s32)(tr->y * (f32)trParent->canvas->height),
														tr->canvasScale, false, 0, 0, tr->canvasScale->width, tr->canvasScale->height);
					}

					// Mark this region's canvas as no longer being dirty (because it's just been updated)
					tr->canvas->isDirty = false;
				}


			//////////
			// Unlock the canvas's semaphore
			//////
//				oss_unlockSemaphore(tr->canvas->semRefresh);
		}
		// Indicate the number of pixels drawn for this region
		return(cb.count1);
	}




//////////
//
// Draws fixed-point (8 x fontHeight) characters onto the canvas.
//
// Returns:
//		Number of pixels drawn, 0 if none, -1 if error, >0 if something new was actually rendered onto the canvas
//
//////
	u64 CALLTYPE vvm_canvasDrawFixedPointText(SCanvas* tc, SBGRA* bd, u32 fontWidth, u32 fontHeight, s32 ulx, s32 uly, s8* text, u32 characterCount, SBGRA foreground, SBGRA background)
    {
		u64 lnResult;


		// Make sure the environment is sane
		lnResult = -1;
		if (tc && text)
		{
			// Make sure our count is valid
			if (characterCount == -1)
				characterCount = (u32)vvm_scanForwardUntilCharacter(_csu8p(text), 0);

			// Draw the text
			lnResult = vvm_iDrawFixedPoint(tc, bd, fontWidth, fontHeight, ulx, uly, text, characterCount, foreground, background);

			// Mark the item dirty
			if (lnResult != 0)
				tc->isDirty = true;
		}
		// Indicate success or failure
		return lnResult;
    }




//////////
//
// Draws OSS-specific fonts onto the canvas using the standard ASCII character set.
//
// Returns:
//		-1				- Canvas ID not found
//		-2				- font Handle is invalid
//		characterCount	- success
//
//////
	u64 CALLTYPE vvm_canvasDrawText(SCanvas* tc, SBGRA* bd, u64 fontHandle, s32 ulx, s32 uly, s32 lrx, s32 lry, s8* tcText, u32 tnTextLength, SBGRA foreground, SBGRA background)
    {
		u64 lnResult;


// UNTESTED CODE:  breakpoint and examine
		lnResult = 0;
		if (tc)
		{
			// Draw the text
			lnResult = oss_drawText(tcText, tnTextLength, ulx, uly, lrx, lry, foreground, background, fontHandle, tc->bd_vvmoss);
			if (lnResult > 0)
			{
				// Copy the text drawn onto the system bitmap onto the canvas
				lnResult = oss_lowLevel_bitBlt_ossRgb_onto_canvasBgra(tc->bd_vvmoss, ulx, uly, lrx-ulx, lry-uly, tc, bd);

				// Mark the item dirty
				if (lnResult != 0)
					tc->isDirty = true;
			}

		}
		// Indicate success or failure
		return(lnResult);
    }




//////////
//
// Draws a rectangle frame onto a canvas (no fill).
//
//////
	u64 CALLTYPE vvm_canvasFrameRect(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border)
    {
		u8		lnFrameRed, lnFrameGrn, lnFrameBlu;
		s32		lnY, lnX, lnX0, lnY0, lnPixelsDrawn, lnHeight;
		SBGRA*	lrgba;


		// Make sure the environment is sane
		if (!tc || !bd)
			return(-1);

		// Frame colors
		lnFrameRed	= border.red;
		lnFrameGrn	= border.grn;
		lnFrameBlu	= border.blu;

		// Box height
		lnHeight = lry - uly;

		// Draw the rectangle for all pixels that should be drawn vertically
		lnPixelsDrawn = 0;
		for (lnY0 = 0, lnY = uly; lnY < lry; lnY0++, lnY++)
		{
			if (lnY >= 0 && lnY < tc->height)
			{
				// Find out on what row this pixel data will go
				lrgba = bd + (lnY * tc->width) + ulx;

				// Are we drawing the top and bottom part?
				if (lnY0 < borderThickness || lnY0 >= lnHeight - borderThickness)
				{
					// Yes.  This is drawing an entire border across
					for (lnX = ulx; lnX < lrx; lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}

				} else {
					// Nope.  We are drawing three parts:  (1) left-border, (2) fill area, (3) right-border

					// Draw left-border
					for (lnX0 = 0, lnX = ulx; lnX < lrx && lnX0 < borderThickness; lnX0++, lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}

					// Skip filler
// TODO:  Both of these algorithms, frame and fill rect, need to be rewritten to use line segments
					for ( ; lnX < lrx - borderThickness; lnX++)
						++lrgba;

					// Draw right-border
					for ( ; lnX < lrx; lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}
				}
			}
		}

		// Mark the item dirty
		if (lnPixelsDrawn != 0)
			tc->isDirty = true;

		// Indicate how many pixels we drew
		return(lnPixelsDrawn);
    }




//////////
//
// Draws a filled rectangle onto a canvas.
//
//////
	u64 CALLTYPE vvm_canvasFillRect(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border, SBGRA background)
    {
		u8		lnFrameRed, lnFrameGrn, lnFrameBlu, lnFillRed, lnFillGrn, lnFillBlu;
		s32		lnY, lnX, lnX0, lnY0, lnPixelsDrawn, lnHeight;
		SBGRA*	lrgba;


		// Make sure the environment is sane
		if (!tc || !bd)
			return(-1);

		// Fill colors
		lnFillRed	= background.red;
		lnFillGrn	= background.grn;
		lnFillBlu	= background.blu;

		// Frame colors
		lnFrameRed	= border.red;
		lnFrameGrn	= border.grn;
		lnFrameBlu	= border.blu;

		// Box height
		lnHeight = lry - uly;

		// Draw the rectangle for all pixels that should be drawn vertically
		lnPixelsDrawn = 0;
		for (lnY0 = 0, lnY = uly; lnY < lry; lnY0++, lnY++)
		{
			if (lnY >= 0 && lnY < tc->height)
			{
				// Find out on what row this pixel data will go
				lrgba = bd + (lnY * tc->width) + ulx;

				// Are we drawing the top and bottom part?
				if (lnY0 < borderThickness || lnY0 >= lnHeight - borderThickness)
				{
					// Yes.  This is drawing an entire border across
					for (lnX = ulx; lnX < lrx; lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}

				} else {
					// Nope.  We are drawing three parts:  (1) left-border, (2) fill area, (3) right-border

					// Draw left-border
					for (lnX0 = 0, lnX = ulx; lnX < lrx && lnX0 < borderThickness; lnX0++, lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}

					// Draw filler
					for ( ; lnX < lrx - borderThickness; lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Fill color
							lrgba->red = lnFillRed;
							lrgba->grn = lnFillGrn;
							lrgba->blu = lnFillBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}

					// Draw right-border
					for ( ; lnX < lrx; lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}
				}
			}
		}

		// Mark the item dirty
		if (lnPixelsDrawn != 0)
			tc->isDirty = true;

		// Indicate how many pixels we drew
		return(lnPixelsDrawn);
    }




//////////
//
// Draws a line on the canvas.
//
//////
	u64 CALLTYPE vvm_canvasLine(SCanvas* tc, SBGRA* bd, SXYF32* p1, SXYF32* p2, f32 lineThickness, SBGRA color, bool tlFloan)
    {
		u64 lnPixelsDrawn;


		// Make sure the environment is sane
		if (!tc || !bd || lineThickness < 1)
			return(-1);

		// Draw the line in floaned fashion
		lnPixelsDrawn = vvm_iCanvasLine(tc, bd, p1, p2, lineThickness, color);

		// Mark the item dirty
		if (lnPixelsDrawn != 0)
			tc->isDirty = true;

		// Indicate how many pixels were updated
		return(lnPixelsDrawn);
    }




//////////
//
// Draws an arc on the canvas.
//
//////
	u64 CALLTYPE vvm_canvasArc(SCanvas* tc, SBGRA* bd, s32 ox, s32 oy, f32 radius, f32 start, f32 end, s32 lineThickness, SBGRA line)
    {
		// Make sure the environment is sane
		if (!tc || !bd)
			return(-1);

		// Make sure our start and end are within 0..2pi
//		start	= fmod(start,	_2PI);
//		end		= fmod(end,		_2PI);


		return(-1);
    }




//////////
//
// Called to draw a 3-point, 4-point, or 5-point Bezier curve, or to generate the points affected
// for the given canvas
//
//////
	u64 CALLTYPE vvm_canvasBezier(SCanvas* tc, SBGRA* bd, SBezier* bez)
	{
		// Make sure our environment is sane
		if (bez && bez->computePointCount >= bez->curveCount && bez->curveCount >= 3 && bez->curveCount <= 5)
		{
			// Draw or generate the bezier curve points
			switch (bez->curveCount)
			{
				case 3:
					return(iivvm_canvasBezier3(tc, bd, bez));
				case 4:
					return(iivvm_canvasBezier4(tc, bd, bez));
				case 5:
					return(iivvm_canvasBezier5(tc, bd, bez));
			}

		}
		// If we get here, invalid data
		return(-1);
	}




//////////
//
// Extracts a portion of a canvas, creating a new canvas.
//
//////
	SCanvas* CALLTYPE vvm_canvasExtract(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry)
    {
		s32			lnWidth, lnHeight;
		SCanvas*	lc;


		// Make sure the environment is sane
		if (tc && bd && ulx < lrx && uly < lry)
		{
			// Create the canvas
			lnWidth		= lrx - ulx;
			lnHeight	= lry - uly;
// TODO: Possible bug observed here, with the tc->state.useTransparency setting possibly not being honored
			lc			= oss_createCanvas(tc->ll.uniqueId, (u32)lnWidth, (u32)lnHeight, tc->backColor);

			// Copy the bitmap data
			if (lc)
				vvm_canvasBitBlt(lc, false, 0, 0, tc, false, ulx, uly, lrx, lry);
			
			// Indicate our success or failure
			return(lc);
		}
		return(NULL);
    }




//////////
//
// Converts the canvas rectangle to grayscale, and then applies the specified color
// to the entire area.
//
//////
	u64 CALLTYPE vvm_canvasColorize(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, SBGRA color)
    {
		u64		lnPixelsDrawn;
		s32		lnY, lnX;
		f32		lfGray, lfRed, lfGrn, lfBlu;
		SBGRA*	lrgba;


		// Make sure the environment is sane
		if (!tc || !bd)
			return(-1);

		// Get the colors
		lfRed = (f32)color.red;
		lfGrn = (f32)color.grn;
		lfBlu = (f32)color.blu;

		// Iterate through every pixel in the rectangle
		lnPixelsDrawn = 0;
		for (lnY = uly; lnY < lry; lnY++)
		{
			if (lnY >= 0 && lnY < tc->height)
			{
				// Find out on what row this pixel data will go
				lrgba = bd + (lnY * tc->width) + ulx;

				// We are drawing an entire border across
				for (lnX = ulx; lnX < lrx; lnX++)
				{
					if (lnX >= 0 && lnX < tc->width)
					{
						// Compute the grayscale percentage
						lfGray	= (((f32)lrgba->red * 0.35f) + ((f32)lrgba->grn * 0.54f) + ((f32)lrgba->blu * 0.11f)) / 255.0f;

						// Convert to that color
						lrgba->red = (u8)(lfGray * lfRed);
						lrgba->grn = (u8)(lfGray * lfGrn);
						lrgba->blu = (u8)(lfGray * lfBlu);

						// Increase our pixel modified count
						++lnPixelsDrawn;
					}
					// Move to next pixel
					++lrgba;
				}
			}
		}

		// Mark the item dirty
		if (lnPixelsDrawn != 0)
			tc->isDirty = true;

		// Return the number of pixels colorized
		return(lnPixelsDrawn);
    }




//////////
//
// Converts the canvas rectangle to grayscale.
//
//////
	u64 CALLTYPE vvm_canvasGrayscale(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry)
    {
		u8		lnGray;
		u64		lnPixelsDrawn;
		s32		lnY, lnX;
		SBGRA*	lrgba;


		// Make sure the environment is sane
		if (!tc || !bd)
			return(-1);

		// Iterate through every pixel in the rectangle
		lnPixelsDrawn = 0;
		for (lnY = uly; lnY < lry; lnY++)
		{
			if (lnY >= 0 && lnY < tc->height)
			{
				// Find out on what row this pixel data will go
				lrgba = bd + (lnY * tc->width) + ulx;

				// We are drawing an entire border across
				for (lnX = ulx; lnX < lrx; lnX++)
				{
					if (lnX >= 0 && lnX < tc->width)
					{
						// Compute the grayscale percentage
						lnGray = (u8)(((f32)lrgba->red * 0.35f) + ((f32)lrgba->grn * 0.54f) + ((f32)lrgba->blu * 0.11f));

						// Convert to that color
						lrgba->red = lnGray;
						lrgba->grn = lnGray;
						lrgba->blu = lnGray;

						// Increase our pixel modified count
						++lnPixelsDrawn;
					}
					// Move to next pixel
					++lrgba;
				}
			}
		}

		// Mark the item dirty
		if (lnPixelsDrawn != 0)
			tc->isDirty = true;

		// Return the number of pixels colorized
		return(lnPixelsDrawn);
    }




//////////
//
// Creates a gradient of the indicated colors.
// Note:  Goes from bd to bd, does not use accumulator.
//
//////
	u64 CALLTYPE vvm_canvasGradient(SCanvas* tc, SBGRA* bd, SBGRA ul, SBGRA ur, SBGRA lr, SBGRA ll)
	{
		u64 lnPixelsDrawn;


		// Make sure the environment is sane
		if (tc && bd && (bd == tc->bd || bd == tc->bda))
		{
			// Perform the gradient
			lnPixelsDrawn = vvm_iiGradient(tc, bd, ul, ur, lr, ll);

			// Mark the item dirty
			if (lnPixelsDrawn != 0)
				tc->isDirty = true;
		}

		// Indicate failure
		return(-1);
	}




//////////
//
// Overlay or alpha blend the specified canvas onto the destination canvas.
//
//////
	u64 CALLTYPE vvm_canvasBitBlt(SCanvas* tsDst, bool tlDstAccumulator, s32 dulx, s32 duly, SCanvas* tsSrc, bool tlSrcAccumulator, s32 sulx, s32 suly, s32 slrx, s32 slry)
    {
		u64 lnPixelsDrawn;


		// Make sure the environment is sane
		if (tsDst && tsSrc)
		{
			// perform the copy
			lnPixelsDrawn = vvm_iBitBltSection(tsDst, tlDstAccumulator, dulx, duly, tsSrc, tlSrcAccumulator, sulx, suly, slrx, slry);

			// Mark the item dirty
			if (lnPixelsDrawn != 0)
				tsDst->isDirty = true;
		}

		// If we get here, invalid data
		return(-1);
    }




//////////
//
// Called to scale a canvas from the src size to the dst size
//
//////
	u64 CALLTYPE vvm_canvasScale(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap** tsScaleMap)
	{
		u64 lnPixelsDrawn;


		// Make sure the environment is sane
		if (tsDst && tsSrc && tsDst->bd && tsSrc->bd && tsScaleMap)
		{
			// Perform the scale
			lnPixelsDrawn = vvm_iiCanvasScale(tsDst, tsSrc, tsScaleMap);

			// Mark the item dirty
			if (lnPixelsDrawn != 0)
				tsDst->isDirty = true;
		}

		// If we get here, failure
		return(0);
	}




//////////
//
// Rotates the indicated canvas onto the destination at the (ulx,uly) coordinates.  Those
// coordinates represent where the upper-left corner would've been before the rotation.  The
// rotation will be about the center of the source canvas, rotating the indicated number of
// radians from there, so that it may exceed the bounds ranging from (ulx,uly) to (ulx+w,uly+h).
// Please bear this in mind. :-)
//
//////
	u64 CALLTYPE vvm_canvasRotate(SCanvas* tsDst, SBGRA* bdd, s32 ulx, s32 uly, SCanvas* tsSrc, SBGRA* bds, f32 tfRadians)
	{
		if (tsDst && bdd && tsSrc && bds)
			return(iivvm_canvasRotateAbout(tsDst, bdd, ulx, uly, tsSrc, bds, tfRadians, (f32)ulx + ((f32)tsSrc->width / 2.0f), (f32)uly + ((f32)tsSrc->height / 2.0f)));

		// If we get here, failure
		return(0);
	}




//////////
//
// Rotates the indicated canvas onto the destination at the (ulx,uly) coordinates.  Those
// coordinates represent where the upper-left corner would've been before the rotation.  The
// rotation will be about the center of the source canvas, rotating the indicated number of
// radians from there, so that it may exceed the bounds ranging from (ulx,uly) to (ulx+w,uly+h).
// Please bear this in mind. :-)
//
//////
	u64 CALLTYPE vvm_canvasRotateAbout(SCanvas* tsDst, SBGRA* bdd, s32 ulx, s32 uly, SCanvas* tsSrc, SBGRA* bds, f32 tfRadians, f32 ox, f32 oy)
	{
		if (tsDst && bdd && tsSrc && bds)
			return(iivvm_canvasRotateAbout(tsDst, bdd, ulx, uly, tsSrc, bds, tfRadians, ox, oy));

		// If we get here, failure
		return(0);
	}




//////////
//
// Called to draw the polygon onto the canvas.
//
//////
	u64 CALLTYPE vvm_canvasPolygon(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color)
	{
		if (poly && poly->line && poly->lineCount >= 3)
			return(vvm_iiCanvasPolygon(tsDst, bd, poly, color));

		// If we get here, failure
		return(0);
	}




//////////
//
// Refreshes the canvas (draws its accumulator buffer onto its main buffer)
//
//////
	u64 CALLTYPE vvm_canvasRefresh(SCanvas* tc)
	{
		u64 lnPixelsDrawn;
		

		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tc && tc->bd && tc->bda)
			lnPixelsDrawn = vvm_canvasBitBlt(tc, false, 0, 0, tc, true, 0, 0, tc->width, tc->height);

		return(lnPixelsDrawn);
	}




//////////
//
// Refer to the _VVMOSS_CASK_* constants.
// Creates a cask of the indicated size and style:
//     Round:         (|name|)
//     Square:        [|name|]
//     Diamond:       <|name|>
//
// States allow various sizes (shown here as round, but is the same for all types):
//     Closed:         ()
//     Minimal:        (|)
//     Text:           (|text|)
//     Extended text:  (|=left=|text|=right=|)
//
// There may or may not be pips on each side.  Pip counts must be 0 through 3.
//
//////
	SCask* CALLTYPE vvm_caskDefineStandard(u32 tnHeight, u32 tnWidth,
		                                    u32 tnLeftStyle,  u32 tnLeftState,  u32 tnLeftPipCount,  u32 tnLeftColor,  csu8p tcLeftText,
		                                    u32 tnRightStyle, u32 tnRightState, u32 tnRightPipCount, u32 tnRightColor, csu8p tcRightText)
	{
		return(NULL);
	}




//////////
//
// Create an encompassing rectangle cask, which has a form like:
//
//     (|+====--------------------==+|]
//      \|                          |/
//       |                          |
//       |                          |
//       |                          |
//       |                          |
//       +====--------------------==+
//
//////
	SCask* CALLTYPE vvm_caskDefineEncompassingRectangle(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SRectXYXY* tsOuter)
	{
		return(NULL);
	}




//////////
//
// Create an up rectangle cask, which goes up from a cask, or from a particular pip on a cask.
// It has the form like:
//
//     +===---------------------------------==+
//     |                                      |
//     |                                      |
//     +===---------------------------------==|
//     ||
//  (|P||text|)
//
//////
	SCask* CALLTYPE vvm_caskDefineUpRectangle(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter)
	{
		return(NULL);
	}




//////////
//
// Create an up rectangle cask, which goes up from a cask, or from a particular pip on a cask.
// It has the form like:
//
//  (|text||P|)
//        ||
//        +===---------------------------------==+
//        |                                      |
//        |                                      |
//        +===---------------------------------==|
//
//////
	SCask* CALLTYPE vvm_caskDefineDownRectangle(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter)
	{
		return(NULL);
	}




//////////
//
// Cask Pips do not have to exist.  If they do not exist then the cask itself is made somewhat
// less wide, and does not respond to mouse events in the pip area, apart from the normal
// operation.
//
//////
	SCaskPip* CALLTYPE vvm_caskSetPipByValues(SCask* cask, bool tlLeft, u32 tnPip, SBGRA tnPipColorNeutral, SBGRA tnPipColorOver, SBGRA tnPipColorClick, u64 tnEnterCallback, u64 tnLeaveCallback, u64 tnHoverCallback, u64 tnClickCallback, bool tlCreateCopy)
	{
		return(NULL);
	}




//////////
//
// Cask
//
//////
	SCaskPip* CALLTYPE vvm_caskSetPipByStruct(SCask* cask, bool tlLeft, u32 tnPip, SCaskPip* caskPip, bool tlCreateCopy)
	{
		return(NULL);
	}




//////////
//
// Cask
//
//////
	SCask* CALLTYPE vvm_caskCreate(SCask* cask, bool tlCreateCopy)
	{
		return(NULL);
	}




//////////
//
// Cask
//
//////
	SCanvas* CALLTYPE vvm_caskRefresh(SCask* cask)
	{
		return(NULL);
	}




//////////
//
// Painting algorithms for standard controls
//
//////
	u64 CALLTYPE vvm_iRegionDefaultPaintEditbox(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionEditboxData* editbox)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && editbox)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}

	u64 CALLTYPE vvm_iRegionDefaultPaintButton(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionButtonData* button)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && button)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}

	u64 CALLTYPE vvm_iRegionDefaultPaintImage(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionImageData* image)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && image)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}

	u64 CALLTYPE vvm_iRegionDefaultPaintLabel(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionLabelData* label)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && label)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}

	u64 CALLTYPE vvm_iRegionDefaultPaintCheckbox(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionCheckboxData* checkbox)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && checkbox)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}

	u64 CALLTYPE vvm_iRegionDefaultPaintRectangle(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionRectangleData* rectangle)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && rectangle)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}




//////////
//
// Called to draw the polygon.  This algorithm uses floaning, and was originally created for
// support of the DSF (dynamic scalable font) in the VVM.
//
//////
	u64 CALLTYPE vvm_iiCanvasPolygon(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color)
	{
		_isSCanvasDrawPolygonParameters lcdp;


		//////////
		// Compute if need be
		//////
			if (!poly->pixelFloans && !poly->rangeFloans)
			{
				// Should it be computed as a small or big polygon?
				if (iivvm_canvasPolygon_determineIfSmall(poly))
				{
					// We process it at 16x resolution (4x wider, 4x higher), then merge down the computed values for the final / partial floan computations.
					iivvm_canvasPolygon_processSmall(tsDst, bd, poly, color, &lcdp);

				} else {
					// Normal.
					// Build all floans like normal.
					iivvm_canvasPolygon_processNormal(tsDst, poly, &lcdp);
				}
			}


		//////////
		// Draw
		//////
			iivvm_canvasPolygon_draw(tsDst, bd, poly, color, &lcdp);


		//////////
		// Indicate our success or failure
		//////
			return(lcdp.lnPixelsDrawn);
	}




/////////
//
// Delete the scale compute chain for the indicated scale map
//
//////
	void CALLTYPE vvm_iDeleteScaleCompute(SScaleMap* tsm)
	{
		// Make sure our environment is sane
		if (tsm && tsm->scaleData)
			vvm_builderFreeAndRelease(&tsm->scaleData);
	}




//////////
//
// Scans from the indicated location forward until finding a non-whitespace character
//
//////
	u64 CALLTYPE vvm_iSkipWhitespaces(s8* tcData, u64 tnMaxLength)
	{
		u64 lnLength;


		// Make sure our environment's sane
		lnLength = 0;		// Initially indicate no whitespaces
		if (tcData && tnMaxLength > 0)
		{
			// While we encounter spaces or tabs, count them
			while (lnLength < tnMaxLength && (tcData[lnLength] == 32 || tcData[lnLength] == 9))
				++lnLength;
			// When we get here, lnLength is the number of whitespaces (if any)
		}
		// Indicate the total length encountered
		return(lnLength);
	}




//////////
//
// Scans from the indicated location forward until finding CR/LF or any combination thereof
//
//////
	u64 CALLTYPE vvm_iSkipToCarriageReturnLineFeed(s8* tcData, u64 tnMaxLength, u64* tnCRLF_Length)
	{
		u64 lnLength, lnCRLF_Length;


		// Make sure our environment's sane
		lnLength		= 0;		// Initially indicate a line length of 0
		lnCRLF_Length	= 0;		// Same for CR/LF length
		if (tcData && tnMaxLength > 0)
		{
			// While we do not counter a CR or LF, continue
			while (lnLength < tnMaxLength && tcData[lnLength] != 13 && tcData[lnLength] != 10)
				++lnLength;

			// See if we are done
			if (lnLength < tnMaxLength)
			{
				// We did not reach the end of the entire data available to us to search
				// So, when we get here, we're sitting on a CR or LF, which is the end of line
				if (tcData[lnLength] == 13)
				{
					// We're sitting on a carriage return
					// If the next character is a line feed, we count it
					if (tcData[lnLength + 1] == 10)		lnCRLF_Length = 2;		// We have a pair
					else								lnCRLF_Length = 1;		// Just the one

				} else {
					// We know we're sitting on a line feed
					// If the next character is a carriage return, we count it
					if (tcData[lnLength + 1] == 13)		lnCRLF_Length = 2;		// We have a pair
					else								lnCRLF_Length = 1;		// Just the one
				}

			} else {
				// We reached the end
				// We don't do anything here, but just return the length
			}
		}
		// When we get here, return the lengths
		// The CR/LF length
		if (tnCRLF_Length)
			*tnCRLF_Length = lnCRLF_Length;

		// The stuff before length :-)
		return(lnLength);
	}




//////////
//
// This function draws fixed point text onto the indicated canvas using the specified font,
// colors, text, etc.  These facilities will look identically regardless of the OSS font that
// could be used by the ioss_drawText() function.
//
//////
	u64 CALLTYPE vvm_iDrawFixedPoint(SCanvas* tc, SBGRA* bd, u32 fontWidth, u32 fontHeight, s32 ulx, s32 uly, s8* tcText, u32 tnTextLength, SBGRA foreground, SBGRA background)
	{
		u64		lnPixels;
        s32		lnX, lnY, lnFontWidth, lnFontHeight, lnPixelY, lnSX, lnScalerY, lnScalerX;
		u8		lcThisCharacter, lcRowBits, lcMask, fred, fgrn, fblu, bred, bgrn, bblu;
        u8*		lcFontBase;
        u32		lnCharacterOffset;
		SBGRA*	lrgba;


        // See what font they're using
		lnScalerY	= 1;
		lnScalerX	= 1;
		switch (fontWidth)
		{
			case 8:
				lnFontWidth	= 8;
				break;

			case -16:
				lnFontWidth	= 8;
				lnScalerX	= 2;
				break;

			case -24:
				lnFontWidth	= 8;
				lnScalerX	= 3;
				break;

			case -32:
				lnFontWidth	= 8;
				lnScalerX	= 4;
				break;

			default:
				return -2;
		}

        switch (fontHeight)
        {
			case -12:
				lcFontBase		= (u8*)gxFontBase_8x6;
				lnFontHeight	= 6;
				lnScalerY		= 2;
				break;

			case -18:
				lcFontBase		= (u8*)gxFontBase_8x6;
				lnFontHeight	= 6;
				lnScalerY		= 3;
				break;

            case 6:
                lcFontBase		= (u8*)gxFontBase_8x6;
                lnFontHeight	= 6;
                break;

            case 8:
                lcFontBase		= (u8*)gxFontBase_8x8;
                lnFontHeight	= 8;
                break;

			case -16:
				lcFontBase		= (u8*)gxFontBase_8x8;
				lnFontHeight	= 8;
				lnScalerY		= 2;
				break;

            case 14:
                lcFontBase		= (u8*)gxFontBase_8x14;
                lnFontHeight	= 14;
                break;

			case -28:
				lcFontBase		= (u8*)gxFontBase_8x14;
				lnFontHeight	= 14;
				lnScalerY		= 2;
				break;

			case -42:
				lcFontBase		= (u8*)gxFontBase_8x14;
				lnFontHeight	= 14;
				lnScalerY		= 3;
				break;

			case -56:
				lcFontBase		= (u8*)gxFontBase_8x14;
				lnFontHeight	= 14;
				lnScalerY		= 4;
				break;

            case 16:
                lcFontBase		= (u8*)gxFontBase_8x16;
                lnFontHeight	= 16;
                break;

			case -32:
				lcFontBase		= (u8*)gxFontBase_8x16;
				lnFontHeight	= 16;
				lnScalerY		= 2;
				break;

			case -48:
				lcFontBase		= (u8*)gxFontBase_8x16;
				lnFontHeight	= 16;
				lnScalerY		= 3;
				break;

			case -64:
				lcFontBase		= (u8*)gxFontBase_8x16;
				lnFontHeight	= 16;
				lnScalerY		= 4;
				break;

            default:
				// Invalid parameters
                return -1;
        }

		// Extract the colors
		fred	= foreground.red;
		fgrn	= foreground.grn;
		fblu	= foreground.blu;

		bred	= background.red;
		bgrn	= background.grn;
		bblu	= background.blu;

        // Begin drawing the text
		lnPixels = 0;
        while (tnTextLength > 0)
        {
            // Grab this character
            lcThisCharacter		= *tcText;
            lnCharacterOffset	= (u32)lcThisCharacter * (u32)lnFontHeight;

            // Put it into the tbDst
            for (lnY = 0; lnY < lnFontHeight; lnY++)
            {
				for (lnPixelY = 0; lnPixelY < lnScalerY; lnPixelY++)
				{
					if ((uly + (lnY * lnScalerY) + lnPixelY) < tc->height)
					{
						// Position the pointer for this part of the font's
						lrgba = bd + ((uly + (lnY * lnScalerY) + lnPixelY) * tc->width) + (ulx * lnScalerX);

						// Grab the bits
						lcRowBits = lcFontBase[lnCharacterOffset];
						lcMask = 0x80;

						// Iterate through all of the bits
						for (lnX = 0; lnX < lnFontWidth; lnX++)
						{
							for (lnSX = 0; lnSX < lnScalerX; lnSX++)
							{
								if ((ulx + (lnX * lnScalerX) + lnSX) < tc->width)
								{
									// This character is within the bitmap
									++lnPixels;
									if ((lcRowBits & lcMask) != 0)
									{
										// Foreground bit
										lrgba->red = fred;
										lrgba->grn = fgrn;
										lrgba->blu = fblu;

									} else {
										// Background bit
										lrgba->red = bred;
										lrgba->grn = bgrn;
										lrgba->blu = bblu;
									}
								}
								// Move to the next pixel
								++lrgba;
							}

							// Shift the mask over 1 bit to get to the next pixel
							lcMask >>= 1;
						}
					}
				}

                // Move to the next row of pixels in the font
                ++lnCharacterOffset;
            }

            // Move to next position
            ulx += lnFontWidth;

            // Move to next character
            ++tcText;
            --tnTextLength;
        }
		// Return the number of pixels updated
		return(lnPixels);
	}




//////////
//
// Called to BitBlt a 32-bit RGBA canvas onto another one.
//
// Returns:
//		0		- error
//		other	- Number of rows painted (partial or otherwise)
//
//////
	u64 CALLTYPE vvm_iBitBltAll(SCanvas* tsDst, bool tlDstIsAccumulatorBuffer, s32 tnX, s32 tnY, SCanvas* tsSrc, bool tlSrcIsAccumulatorBuffer)
	{
		u64			lnRowCount;
		SBGRA*		lrgbaDstRoot;
		SBGRA*		lrgbaSrcRoot;


// OPTIMIZATION:  We can go through here and determine line portions to process to speed this up.
//                This will likely be a heavily called function, and that optimization would be welcomed.  Any takers? :-)
// UNTESTED CODE:  Breakpoint and examine!
		// Make sure the environment is sane
		lnRowCount = 0;
		if (tsDst && tsSrc)
		{
			// See if we're copying from accumulation buffer to (non-accumulation) buffer on the same entry
			if (tsDst == tsSrc && !tlDstIsAccumulatorBuffer && tlSrcIsAccumulatorBuffer)
			{
				// Are the parameters valid for the copy?
				if (tsDst->bd && tsDst->bda)
				{
					// We are doing a copy from accumulation to non-accumulation
					memcpy(tsDst->bd, tsDst->bda, tsDst->height * tsDst->width * sizeof(SBGRA));		// Copy the entire buffer

					// Indicate we copied all of them
					lnRowCount = tsDst->height;
				}

			} else {
				// Find out our source and destination buffers
				lrgbaDstRoot = (tlDstIsAccumulatorBuffer) ? tsDst->bda : tsDst->bd;
				lrgbaSrcRoot = (tlSrcIsAccumulatorBuffer) ? tsSrc->bda : tsSrc->bd;

				// Make sure the pointers are valid
				if (lrgbaDstRoot || lrgbaSrcRoot)
				{
					vvm_iiBitBltAll_Alpha( lrgbaDstRoot, tsDst, tnX, tnY, lrgbaSrcRoot, tsSrc);				// Use the slower algorithm to blend the the two 
					//iioss_bitBltAll_Opaque(lrgbaDstRoot, tsDst, tnX, tnY, lrgbaSrcRoot, tsSrc);			// Iterate through every row for all pixels to copy
					
					// We always indicate we processed this many rows, even if something wasn't updated
					lnRowCount = tsSrc->height;
				}
			}
		}
		// Indicate our success/failure
		return(lnRowCount);
	}




//////////
//
// Perform an alpha blending from the src canvas to the dst canvas, based on the
// src alpha settings.
//
//////
	void CALLTYPE vvm_iiBitBltAll_Alpha(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 tnX, s32 tnY, SBGRA* trgbaSrcRoot, SCanvas* tsSrc)
	{
		s32			lnY, lnX;
		u8			redd, grnd, blud;
		f32			alp, malp;
		SBGRA*		lrgbad;
		SBGRA*		lrgbas;


// TODO:  this algorithm needs to more properly consider transparency, of the source to destination, along with individual bits within
		// Derive the colors from the back color
		vvm_deriveRGBA(tsDst->backColor.color, &redd, &grnd, &blud, &malp);
		alp		= (f32)tsSrc->backColor.alp / 255.0f;
		malp	= 1.0f - alp;


		// Repeat for every row
		for (lnY = tnY; lnY < (s32)tsSrc->height; lnY++)
		{
			// Can we copy this row?
			if (lnY >= 0 && lnY < (s32)tsDst->height)
			{
				// Yes we can, recompute the positions for this line
				lrgbad = trgbaDstRoot + (lnY * tsDst->width);
				lrgbas = trgbaSrcRoot + (lnY * tsSrc->width);

				// Iterate for as many pixels as will fit
				for (lnX = tnX; lnX < (s32)tsSrc->width; lnX++)
				{
					// Can we copy this pixel?
					if (lnX >= 0 && lnX < (s32)tsDst->width)
					{
						// Yes we can each color channel of this pixel
						lrgbad->red	= (u8)(((f32)lrgbas->red * alp) + ((f32)lrgbad->red * malp));
						lrgbad->grn = (u8)(((f32)lrgbas->grn * alp) + ((f32)lrgbad->grn * malp));
						lrgbad->blu = (u8)(((f32)lrgbas->blu * alp) + ((f32)lrgbad->blu * malp));
						lrgbad->alp = 255;
					}

					// Move to the next pixel
					++lrgbad;
					++lrgbas;
				}
			}
		}
	}




//////////
//
// Perform an alpha blending from the src canvas to the dst canvas, based on the
// src alpha settings.
//
//////
	// It is probbaly best NOT to call this function directory, but rather call ioss_bitBltAll()
	void CALLTYPE vvm_iiBitBltAll_Opaque(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 tnX, s32 tnY, SBGRA* trgbaSrcRoot, SCanvas* tsSrc)
	{
		s32			lnY, lnX;
		SBGRA*		lrgbad;
		SBGRA*		lrgbas;


		// Repeat for every row
		for (lnY = tnY; lnY < (s32)tsSrc->height; lnY++)
		{
			// Can we copy this row?
			if (lnY >= 0 && lnY < (s32)tsDst->height)
			{
				// Yes we can, recompute the positions for this line
				lrgbad = trgbaDstRoot + (lnY * tsDst->width);
				lrgbas = trgbaSrcRoot + (lnY * tsSrc->width);

				// Iterate for as many pixels as will fit
				for (lnX = tnX; lnX < (s32)tsSrc->width; lnX++)
				{
					// Can we copy this pixel?
					if (lnX >= 0 && lnX < (s32)tsDst->width)
					{
						// Yes we can each color channel of this pixel
						lrgbad->red	= lrgbas->red;
						lrgbad->grn = lrgbas->grn;
						lrgbad->blu = lrgbas->blu;
						lrgbad->alp = lrgbas->alp;
					}

					// Move to the next pixel
					++lrgbad;
					++lrgbas;
				}
			}
		}
	}




//////////
//
// Called to BitBlt a 32-bit RGBA canvas onto another one, for the section indicated.
// Note:  This function will be slightly slower than the ioss_bitBltAll()
//
// Returns:
//		0		- error
//		other	- Number of rows painted (partial or otherwise)
//
//////
	// It is probbaly best NOT to call this function directory, but rather call ioss_bitBltSection()
	u64 CALLTYPE vvm_iBitBltSection(SCanvas* tsDst, bool tlDstIsAccumulatorBuffer, s32 dulx, s32 duly, SCanvas* tsSrc, bool tlSrcIsAccumulatorBuffer, s32 sulx, s32 suly, s32 slrx, s32 slry)
	{
		u64			lnRowCount;
		SBGRA*		lrgbaDstRoot;
		SBGRA*		lrgbaSrcRoot;


// OPTIMIZATION:  We can go through here and determine line portions to process to speed this up.
//                This will likely be a heavily called function, and that optimization would be welcomed.  Any takers? :-)
// UNTESTED CODE:  Breakpoint and examine!
		// Make sure the environment is sane
		lnRowCount = 0;
		if (tsDst && tsSrc)
		{
			// See if we're copying from accumulation buffer to (non-accumulation) buffer on the same entry
			if (tsDst == tsSrc && !tlDstIsAccumulatorBuffer && tlSrcIsAccumulatorBuffer)
			{
				// Are the parameters valid for the copy?
				if (tsDst->bd && tsDst->bda)
				{
					// We are doing a copy from accumulation to non-accumulation
					memcpy(tsDst->bd, tsDst->bda, tsDst->height * tsDst->width * sizeof(SBGRA));		// Copy the entire buffer

					// Indicate we copied all of them
					lnRowCount = tsDst->height;
				}

			} else {
				// Find out our source and destination buffers
				lrgbaDstRoot = (tlDstIsAccumulatorBuffer) ? tsDst->bda : tsDst->bd;
				lrgbaSrcRoot = (tlSrcIsAccumulatorBuffer) ? tsSrc->bda : tsSrc->bd;

				// Make sure the pointers are valid
				if (lrgbaDstRoot || lrgbaSrcRoot)
				{
					vvm_iiBitBltSection_Alpha( lrgbaDstRoot, tsDst, dulx, duly, lrgbaSrcRoot, tsSrc, sulx, suly, slrx, slry);		// Use the slower algorithm to blend the the two 
					//iioss_bitBltSection_Opaque(lrgbaDstRoot, tsDst, dulx, duly, lrgbaSrcRoot, tsSrc, sulx, suly, slrx, slry);		// Iterate through every row for all pixels to copy
					
					// We always indicate we processed this many rows, even if something wasn't updated
					lnRowCount = tsSrc->height;
				}
			}
		}
		// Indicate our success/failure
		return(lnRowCount);
	}




//////////
//
// Perform an alpha blending from the src canvas to the dst canvas, based on the
// src alpha settings, for the section indicated.
//
//////
	void CALLTYPE vvm_iiBitBltSection_Opaque(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 dulx, s32 duly, SBGRA* trgbaSrcRoot, SCanvas* tsSrc, s32 sulx, s32 suly, s32 slrx, s32 slry)
	{
		s32			lnY, lnX, lnThisX, lnThisY, lnWidth, lnHeight;
		u8			redd, grnd, blud;
		f32			alp, malp;
		SBGRA*		lrgbad;
		SBGRA*		lrgbas;


// TODO:  this algorithm needs to more properly consider transparency, of the source to destination, along with individual bits within
		// Derive the colors from the back color
		vvm_deriveRGBA(tsDst->backColor.color, &redd, &grnd, &blud, &malp);
		alp		= (f32)tsSrc->backColor.alp / 255.0f;
		malp	= 1.0f - alp;

		// Derive our size for the source rectangular region
		lnWidth		= slrx - sulx;
		lnHeight	= slry - suly;


		//////////
		// Repeat for every row
		//////
			for (	lnY = duly, lnThisY = 0;
					lnY < (s32)tsSrc->height && lnThisY < lnHeight;
					lnY++, lnThisY++	)
			{
				// Can we copy this row?
				if (lnY >= 0 && lnY < (s32)tsDst->height && lnThisY < lnHeight)
				{
					// Yes we can, recompute the positions for this line
					lrgbad = trgbaDstRoot + (lnY              * tsDst->width);
					lrgbas = trgbaSrcRoot + ((lnThisY + suly) * tsSrc->width) + sulx;

					//////////
					// Iterate for as many pixels as will fit
					//////
						for (	lnX = dulx, lnThisX = 0;
								lnX < (s32)tsSrc->width && lnThisX < lnWidth;
								lnX++, lnThisX++	)
						{
							// Can we copy this pixel?
							if (lnX >= 0 && lnX < (s32)tsDst->width && lnThisX < lnWidth)
							{
								// Yes we can each color channel of this pixel
								lrgbad->red	= (u8)(((f32)lrgbas->red * alp) + ((f32)lrgbad->red * malp));
								lrgbad->grn = (u8)(((f32)lrgbas->grn * alp) + ((f32)lrgbad->grn * malp));
								lrgbad->blu = (u8)(((f32)lrgbas->blu * alp) + ((f32)lrgbad->blu * malp));
								lrgbad->alp = 255;
							}

							// Move to the next pixel
							++lrgbad;
							++lrgbas;
						}	// end for lnX...
				}	// end if lnY...
			}	// end for lnY...
	}




//////////
//
// Perform an alpha blending from the src canvas to the dst canvas, based on the
// src alpha settings, for the section indicated.
//
//////
	void CALLTYPE vvm_iiBitBltSection_Alpha(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 dulx, s32 duly, SBGRA* trgbaSrcRoot, SCanvas* tsSrc, s32 sulx, s32 suly, s32 slrx, s32 slry)
	{
		s32			lnY, lnX, lnThisX, lnThisY, lnWidth, lnHeight;
		SBGRA*		lrgbad;
		SBGRA*		lrgbas;


		// Derive our size for the source rectangular region
		lnWidth		= slrx - sulx;
		lnHeight	= slry - suly;


		//////////
		// Repeat for every row
		//////
			for (	lnY = duly, lnThisY = 0;
					lnY < (s32)tsSrc->height && lnThisY < lnHeight;
					lnY++, lnThisY++	)
			{
				// Can we copy this row?
				if (lnY >= 0 && lnY < (s32)tsDst->height && lnThisY < lnHeight)
				{
					// Yes we can, recompute the positions for this line
					lrgbad = trgbaDstRoot + (lnY              * tsDst->width);
					lrgbas = trgbaSrcRoot + ((lnThisY + suly) * tsSrc->width) + sulx;


					//////////
					// Iterate for as many pixels as will fit
					//////
						for (	lnX = dulx, lnThisX = 0;
								lnX < (s32)tsSrc->width && lnThisX < lnWidth;
								lnX++, lnThisX++	)
						{
							// Can we copy this pixel?
							if (lnX >= 0 && lnX < (s32)tsDst->width && lnThisX < lnWidth)
							{
								// Yes we can each color channel of this pixel
								lrgbad->red	= lrgbas->red;
								lrgbad->grn = lrgbas->grn;
								lrgbad->blu = lrgbas->blu;
								lrgbad->alp = lrgbas->alp;
							}

							// Move to the next pixel
							++lrgbad;
							++lrgbas;
						}
				}
			}
	}




//////////
//
// Draws a gradient on the indicated canvas.
//
//////
	u32 CALLTYPE vvm_iiGradient(SCanvas* tc, SBGRA* bd, SBGRA ul, SBGRA ur, SBGRA lr, SBGRA ll)
	{
		s32		lnY, lnX;
		f32		red, grn, blu, redColumnStep, grnColumnStep, bluColumnStep;
		f32		redLeft,  grnLeft,  bluLeft;
		f32		redRight, grnRight, bluRight;
		f32		redRowLeftStep,  grnRowLeftStep,  bluRowLeftStep;
		f32		redRowRightStep, grnRowRightStep, bluRowRightStep;
		SBGRA*	lrgba;


		// Grab our colors
		redLeft			= ul.red;
		grnLeft			= ul.grn;
		bluLeft			= ul.blu;
		redRight		= ur.red;
		grnRight		= ur.grn;
		bluRight		= ur.blu;

		// Compute the row step
		redRowLeftStep	= ((f32)ll.red - (f32)ul.red) / (f32)tc->height;
		grnRowLeftStep	= ((f32)ll.grn - (f32)ul.grn) / (f32)tc->height;
		bluRowLeftStep	= ((f32)ll.blu - (f32)ul.blu) / (f32)tc->height;
		redRowRightStep	= ((f32)lr.red - (f32)ur.red) / (f32)tc->height;
		grnRowRightStep	= ((f32)lr.grn - (f32)ur.grn) / (f32)tc->height;
		bluRowRightStep	= ((f32)lr.blu - (f32)ur.blu) / (f32)tc->height;

		// Iterate through every row
		for (lnY = 0; lnY < tc->height; lnY++)
		{
			// Grab our starting color
			red = redLeft;
			grn = grnLeft;
			blu = bluLeft;

			// Determine our column steppings
			redColumnStep = (redRight - redLeft) / (f32)tc->width;
			grnColumnStep = (grnRight - grnLeft) / (f32)tc->width;
			bluColumnStep = (bluRight - bluLeft) / (f32)tc->width;

			// Compute this row's offset
			lrgba = bd + (lnY * tc->width);

			// Repeat for every pixel across
			for (lnX = 0; lnX < tc->width; lnX++)
			{
				// Store this gradient pixel
				lrgba->red	= (u8)red;
				lrgba->grn	= (u8)grn;
				lrgba->blu	= (u8)blu;

				// Increase the color horizontally
				red += redColumnStep;
				grn += grnColumnStep;
				blu += bluColumnStep;

				// Move to next pixel
				++lrgba;
			}

			// Increase the colors vertically
			redLeft		+= redRowLeftStep;
			grnLeft		+= grnRowLeftStep;
			bluLeft		+= bluRowLeftStep;
			redRight	+= redRowRightStep;
			grnRight	+= grnRowRightStep;
			bluRight	+= bluRowRightStep;
		}

		// Indicate success
		return(0);
	}




//////////
//
// Draws an aliased line on the indicated canvas, ether floaned or aliased
//
//////
	u64 CALLTYPE vvm_iCanvasLine(SCanvas* tc, SBGRA* bd, SXYF32* tsP1, SXYF32* tsP2, f32 lineThickness, SBGRA color)
	{
		f64			lfDeltaX, lfDeltaY, lfLineLength, lfTheta, lfHalfLineX, lfHalfLineY, lfStepXM, lfStepYM;
		u64			lnPixelsDrawn;
		SPolygon	polygon;
		SXYF64		p1, p2, p3, p4, gravity;


		// Initialize the polygon
		memset(&polygon, 0, sizeof(polygon));
		polygon.line		= (SPolyLine**)NULL;
		if (vvm_polygon_initialize(&polygon, 4, true))
		{
			// Convert our parameters for use
			lfDeltaX		= (f64)(tsP2->x - tsP1->x);
			lfDeltaY		= (f64)(tsP2->y - tsP1->y);
			lfLineLength	= sqrt(lfDeltaX*lfDeltaX + lfDeltaY*lfDeltaY);
			lfHalfLineX		= lineThickness * 0.5;
			lfHalfLineY		= lfLineLength * 0.5;
			lfTheta			= atan2(lfDeltaY, lfDeltaX);
			lfStepXM		= sin(lfTheta);
			lfStepYM		= cos(lfTheta);
			// We translate this into a 4-sided polygon

			// p1
			p1.x			= (f64)tsP1->x - (lfStepXM * lfHalfLineX);
			p1.y			= (f64)tsP1->y + (lfStepYM * lfHalfLineX);
			// p2
			p2.x			= (f64)tsP1->x + (lfStepXM * lfHalfLineX);
			p2.y			= (f64)tsP1->y - (lfStepYM * lfHalfLineX);
			// p3
			p3.x			= (f64)tsP2->x + (lfStepXM * lfHalfLineX);
			p3.y			= (f64)tsP2->y - (lfStepYM * lfHalfLineX);
			// p2
			p4.x			= (f64)tsP2->x - (lfStepXM * lfHalfLineX);
			p4.y			= (f64)tsP2->y + (lfStepYM * lfHalfLineX);

			// Gravity is the center point of the line's 4 point coordinates
			gravity.x		= (p1.x + p2.x + p3.x + p4.x) / 4.0;
			gravity.y		= (p1.y + p2.y + p3.y + p4.y) / 4.0;

			// Set the lines
			vvm_polygon_setByValues(&polygon, 0, &p1, &p2, &gravity);		// p1..p2
			vvm_polygon_setByValues(&polygon, 1, &p2, &p3, &gravity);		// p2..p3
			vvm_polygon_setByValues(&polygon, 2, &p3, &p4, &gravity);		// p3..p4
			vvm_polygon_setByValues(&polygon, 3, &p4, &p1, &gravity);		// p4..p1

			// Draw the polygon
			lnPixelsDrawn = vvm_iiCanvasPolygon(tc, bd, &polygon, color);
		}

		// Indicate what we did
		return(lnPixelsDrawn);
	}




//////////
//
// Scales the canvas from source to destination
//
//////
	u64 CALLTYPE vvm_iiCanvasScale(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap** tsSm)
	{
		u64			lnPixelsDrawn;
		f64			lfVertical, lfHorizontal;
		SScaleMap*	lsm;
		SScaleMap**	lsmLast;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		// We have valid source and destination canvases
		if (tsSrc->width == tsDst->width && tsSrc->height == tsDst->height)
		{
			// They're the same size, just copy them
			memcpy(tsDst->bd, tsSrc->bd, tsSrc->width * tsSrc->height * sizeof(SBGRA));
			lnPixelsDrawn = tsSrc->width * tsSrc->height;

		} else {
			// We need to scale
			lsmLast	= tsSm;
			lsm		= NULL;

			// See if there is already an existing map
			if (*tsSm)
			{
				// Maybe one of those can be used
				lsm = *tsSm;
				while (lsm)
				{
					// See if it's the same size
					if (     /*Source*/ lsm->src.width == tsSrc->width && lsm->src.height == tsSrc->height &&
					    /*Destination*/ lsm->dst.width == tsDst->width && lsm->dst.height == tsDst->height)
					{
						// It is a full match, we can use this scale computation
						break;
					}

					// Move to the next entry
					lsmLast = (SScaleMap**)&lsm->next;
					lsm		= (SScaleMap*)lsm->next;
				}
			}

			// Do we need to create a new block?
			if (!lsm)
			{
				// Yes
				lsm = (SScaleMap*)malloc(sizeof(SScaleMap));

				// If we fail, we cannot proceed
				if (!lsm)
					return(0);

				// Initialize the block
				memset(lsm, 0, sizeof(SScaleMap));

				// Create the builder block for the stored scale compute records
				vvm_builderCreateAndInitialize(&lsm->scaleData, 8192000);	// Allocate 8MB at a time

				// Store its sizing parameters
				lsm->src.width	= tsSrc->width;
				lsm->src.height	= tsSrc->height;
				lsm->dst.width	= tsDst->width;
				lsm->dst.height	= tsDst->height;

				// Update the back-link
				*lsmLast = lsm;
			}

			// Physically conduct the scale
			lfVertical		= (f64)tsSrc->height / (f64)tsDst->height;
			lfHorizontal	= (f64)tsSrc->width  / (f64)tsDst->width;
			lnPixelsDrawn	= vvm_iiCanvasScaleProcess(tsDst, tsSrc, lsm, lfVertical, lfHorizontal);
		}

		// Indicate our failure or success
		return(lnPixelsDrawn);
	}




//////////
//
// Takes a 24-bit bitmap, and scales it up or down to the specified size, with a
// minimum of a 1x1 pixel size.
//
// Returns:
//		-1		- Input file could not be opened
//		-2		- Invalid input bitmap
//		-3		- Unable to allocate memory for input bitmap
//		-4		- Error reading input bitmap
//		-5		- Unable to allocate memory for output bitmap
//		-6		- Unable to create the output file
//		-7		- Unable to write to output file
//
//////
	u64 CALLTYPE vvm_iiCanvasScaleProcess(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap* tsSm, f64 tfVerticalScaler, f64 tfHorizontalScaler)
	{
		u64							lnPixelsDrawn;
		f64							lfMult, lfRed, lfGrn, lfBlu, lfAlp;
		s32							lnY, lnX;
		u32							lnOffset, lnMaxOffset, lnOffsetDst;
		_isSSpannedPixelProcessing	spp;
		SBGRACompute*				lsc;
		SBGRA*						lbgras;
		SBGRA*						lbgrad;


		// Initialize everything in the spp
		memset(&spp, 0, sizeof(spp));

		// Are we scaling based on the formula already derived?
		if (tsSm->scaleData->populatedLength == 0)
		{
			// Build the scale computation
			spp.dst			= tsDst;
			spp.src			= tsSrc;
			spp.sm			= tsSm;
			spp.ratioV		= (f64)tsSrc->height	/ (f64)tsDst->height;
			spp.ratioH		= (f64)tsSrc->width		/ (f64)tsDst->width;
			spp.rowWidth	= tsSrc->width * sizeof(SBGRA);

			// Iterate through every pixel row by row, column by column
			lnPixelsDrawn = 0;
			for (lnY = 0; lnY < tsDst->height; lnY++)
			{
				for (lnX = 0; lnX < tsDst->width; lnX++)
				{
					// Compute data for this spanned pixel
					spp.uly			= min((f64)lnY * spp.ratioV, (f64)tsSrc->height - spp.ratioV);
					spp.ulx			= min((f64)lnX * spp.ratioH, (f64)tsSrc->width  - spp.ratioH);
					spp.lry			= spp.uly + spp.ratioV - 0.000000000001f;
					spp.lrx			= spp.ulx + spp.ratioH - 0.000000000001f;
					spp.areaSpanned	= (spp.lrx - spp.ulx) * (spp.lry - spp.uly);

					// Compute offsets for this point (beginning at upper-left of any spanned pixels)
					spp.offsetSrc	= (((s32)spp.uly * tsSrc->width) + (s32)spp.ulx) * sizeof(SBGRA);
					spp.offsetDst	= ((lnY          * tsDst->width) + lnX         ) * sizeof(SBGRA);

					// Derive the scale computation for this spanned pixel
					vvm_iiGetSpannedPixelComputation(&spp);
				}
			}
			// When we get here, we've computed everything
			// Reduce the size of the scaleData builder to whatever was used
			vvm_builderSetSize(tsSm->scaleData, -1);
		}


		// Now perform the scale
		if (tsSm->scaleData->populatedLength)
		{
			// Initialize everything in the destination to black and 0 alpha (because every pixel computation is added to the prior values)
			vvm_memset4((u32*)tsDst->bd, 0, tsDst->width * tsDst->height);

			// Apply the scaling computation
			lnOffset	= 0;
			lnMaxOffset	= tsSm->scaleData->populatedLength;
			lsc			= (SBGRACompute*)tsSm->scaleData->data;
			while (lnOffset < lnMaxOffset)
			{
				// Compute this portion
				lbgras		= (SBGRA*)((s8*)tsSrc->bd + lsc->offsetSrc);
				lbgrad		= (SBGRA*)((s8*)tsDst->bd + lsc->offsetDst);
				lfMult		= lsc->alpha;

				// Compute the translation
				lfAlp		= (f64)lbgras->alp * lfMult;
				lfRed		= (f64)lbgras->red * lfMult;
				lfGrn		= (f64)lbgras->grn * lfMult;
				lfBlu		= (f64)lbgras->blu * lfMult;
				lnOffsetDst	= lsc->offsetDst;
				
				// Move to next scale entry
				lnOffset	+= sizeof(SBGRACompute);
				lsc			= (SBGRACompute*)(tsSm->scaleData->data + lnOffset);

				// So long as we're dealing with the same destination pixel, accumulate the alpha, red, green and blue values
				if (lnOffset < lnMaxOffset && lsc->offsetDst == lnOffsetDst)
				{
					// Accumulate everything for this destination offset
					do {
						// Get the multiplier for this pixel
						lbgras	= (SBGRA*)((s8*)tsSrc->bd + lsc->offsetSrc);
						lfMult	= lsc->alpha;

						// Add in this part of the computation
						lfAlp	+= (f64)lbgras->alp * lfMult;
						lfRed	+= (f64)lbgras->red * lfMult;
						lfGrn	+= (f64)lbgras->grn * lfMult;
						lfBlu	+= (f64)lbgras->blu * lfMult;

						// Move to next scale entry
						lnOffset	+= sizeof(SBGRACompute);
						lsc			= (SBGRACompute*)(tsSm->scaleData->data + lnOffset);

					} while (lnOffset < lnMaxOffset && lsc->offsetDst == lnOffsetDst);
				}

				// Store the physical data
				lbgrad->alp	+= (u8)lfAlp;
				lbgrad->red	+= (u8)lfRed;
				lbgrad->grn	+= (u8)lfGrn;
				lbgrad->blu	+= (u8)lfBlu;
			}
			// When we get here, the source is scaled into the destination
		}

		// Finished, indicate the pixel count
		return(tsDst->width * tsDst->height);
	}




//////////
//
// Get spanned pixel data, meaning the input (bii, bdi) values are scanned based on the
// location of tnY,tnX and the relationship between bii and bio, meaning the input and
// output sizes.  If bii is bigger, then each bio pixel maps to more than one bii pixel.
// If they're identical, it's 1:1.  If bii is smaller, then each bio pixel maps to less
// than one full bii pixel.  There are no other options. :-)  This algorithm should not
// be used for 1:1 ratio conversions.
//
// Note that each of the above conditions applies to both width and height, meaning the
// relationship between bii and bio is analyzed on each axis, resulting in nine possible
// states (wider+taller, wider+equal, wider+shorter, equal+taller, equal+equal, equal+shorter,
// narrower+taller, narrower+equal, narrower+shorter).
//
// This natural relationship breaks down into nine general point forms:
//		Original pixels:			Output pixels span original pixels:
//		 ______________ 			 ______________ 			 ______________
//		|    |    |    |			|    |    |    |			|1   | 2  |   3|
//		|____|____|____|			|__+--------+__|			|__+--------+__|
//		|    |    |    |	==>		|  |        |  |	==>		|4 |   5    | 6|
//		|____|____|____|	==>		|__|        |__|	==>		|__|        |__|
//		|    |    |    |			|  +--------+  |			|7 +---8----+ 9|
//		|____|____|____|			|____|____|____|			|____|____|____|
//
// This form is comprised of 9 general parts, eight of which may not be present in all
// relationships, and five of which may span multiple columns, rows or both.
//
// These are:
//		1	- upper-left	(always,	spans at most one pixel)
//		2	- upper-middle	(optional,	spans at most multiple partial or full pixels)
//		3	- upper-right	(optional,	spans at most one pixel)
//		4	- middle-left	(optional,	spans at most multiple partial or full pixels)
//		5	- middle-middle	(optional,	can span multiple partial or full pixels)
//		6	- middle-right	(optional,	spans at most multiple partial or full pixels)
//		7	- lower-left	(optional,	spans at most one pixel)
//		8	- lower-middle	(optional,	spans at most multiple partial or full pixels)
//		9	- lower-right	(optional,	spans at most one pixel)
//
//////
	void CALLTYPE vvm_iiGetSpannedPixelComputation(_isSSpannedPixelProcessing* spp)
	{
		// Raise the flags for which portions are valid / required
		spp->spans2H		= (vvm_iGetIntegersBetween(spp->ulx, spp->lrx) >= 1);		// It occupies at least two pixels horizontally (itself and one more)
		spp->spans3H		= (vvm_iGetIntegersBetween(spp->ulx, spp->lrx) >= 2);		// It occupies at least three pixels horizontally (itself, at least one in the middle, and one at the right)
		spp->spans2V		= (vvm_iGetIntegersBetween(spp->uly, spp->lry) >= 1);		// It occupies at least two pixels vertically (itself and one more)
		spp->spans3V		= (vvm_iGetIntegersBetween(spp->uly, spp->lry) >= 2);		// It occupies at least three pixels vertically (itself, at least one in the middle, and one at the right)

		// Compute the information necessary to process each of the 9 portions of points
		// Store left- and right-sides for this spanned pixel
		spp->left			= (s32)min(spp->ulx,			spp->src->width - 1);
		spp->right			= (s32)min(spp->lrx,			spp->src->width - 1);

		// Compute the middle section in pixels
		// Note: -2 is for -1 base 0, and -1 because we want the max value to be one before the width/height
		spp->middleStartH	= (s32)min(spp->ulx + 1,		spp->src->width  - 1);		// next pixel right of upper-left
		spp->middleFinishH	= (s32)min(spp->lrx - 1,		spp->src->width  - 1);		// next pixel left of upper-right (which is actually lower-right, but on this upper line)
		spp->middleStartV	= (s32)min(spp->uly + 1,		spp->src->height - 1);		// next pixel right of left-side pixels
		spp->middleFinishV	= (s32)min(spp->lry - 1,		spp->src->height - 1);		// next pixel left of right-side pixels

		// Compute how far over the right-most pixel is, and how far down the bottom-most pixel is
		spp->rightDelta		= (s32)(spp->lrx - spp->ulx);
		spp->bottomDelta	= (s32)(spp->lry - spp->uly);

		// Find out where this upper-left pixel falls
		if (!spp->spans2H)		spp->widthLeft	=      spp->lrx          - spp->ulx;		// Entire width is within this one pixel, so it's only a portion of the pixel's overall width
		else					spp->widthLeft	= (f64)spp->middleStartH - spp->ulx;		// It spans from where it is to the right of the pixel square

		if (!spp->spans2V)		spp->height		=      spp->lry          - spp->uly;		// It's entire height is within this one pixel, so it's only a portion of the pixel's overall height
		else					spp->height		= (f64)spp->middleStartV - spp->uly;		// It spans from where it is to the bottom of the pixel square

		//////////
		// The following functions (if called) update the number of pieces of picture data to add to the output
		//////
			//////////
			// 1 - upper-left (always, spans at most one pixel)
			//////
				// Compute the area for this pixel component
				spp->area = spp->widthLeft * spp->height;
				// Store the colors for this point
				vvm_iiGetSpannedPixelComputationAppend(spp, 0, 0, spp->area);


			//////////
			// 2 - upper-middle (optional, spans at most multiple partial or full pixels, but only if 1, 2 and 3 exist)
			//////
				if (spp->spans3H)
				{
					s32 lnX, lnPixel;
					// For every middle pixel, apply these values
					for (lnX = 1, lnPixel = spp->middleStartH; lnPixel <= spp->middleFinishH; lnX++, lnPixel++)
						vvm_iiGetSpannedPixelComputationAppend(spp, lnX, 0, spp->height);
				}


			//////////
			// 3 - upper-right (optional, spans at most one pixel, but only if 1 and 3 exist (as 1 and 2))
			//////
				if (spp->spans2H)
				{
					// Find out where this upper-left pixel falls
					spp->widthRight	= spp->lrx - (f64)spp->right;		// It spans from the start of the right-most pixel to wherever it falls therein
					// Compute the area for this pixel component
					spp->area = spp->widthRight * spp->height;
					// Store this pixel data
					vvm_iiGetSpannedPixelComputationAppend(spp, spp->rightDelta, 0, spp->area);
				}


			//////////
			// 4 - middle-left (optional, spans at most multiple partial or full pixels)
			//////
				if (spp->spans3V)
				{
					s32 lnY, lnPixelY;
					// Repeat for each middle pixel
					for (lnY = 1, lnPixelY = spp->middleStartV; lnPixelY <= spp->middleFinishV; lnY++, lnPixelY++)
						vvm_iiGetSpannedPixelComputationAppend(spp, 0, lnY, spp->widthLeft);
				}


			//////////
			// 5 - middle-middle (optional, can span multiple partial or full pixels)
			//////
				if (spp->spans3V && spp->spans3H)
				{
					s32 lnX, lnY, lnPixelY, lnPixelX;
					// Iterate for each pixel row vertically
					for (lnY = 1, lnPixelY = spp->middleStartV; lnPixelY <= spp->middleFinishV; lnY++, lnPixelY++)
					{
						// And each individual pixel horizontally
						for (lnX = 1, lnPixelX = spp->middleStartH; lnPixelX <= spp->middleFinishH; lnX++, lnPixelX++)
						{
							vvm_iiGetSpannedPixelComputationAppend(spp, lnX, lnY, 1.0f);
						}
					}
				}


			//////////
			// 6 - middle-right (optional, spans at most multiple partial or full pixels)
			//////
				if (spp->spans3V && spp->spans2H)
				{
					s32 lnY, lnPixelY;
					// Repeat for each middle pixel
					for (lnY = 1, lnPixelY = spp->middleStartV; lnPixelY <= spp->middleFinishV; lnY++, lnPixelY++)
						vvm_iiGetSpannedPixelComputationAppend(spp, spp->rightDelta, lnY, spp->widthRight);
				}


			//////////
			// 7 - lower-left (optional, spans at most one pixel)
			//////
				if (spp->spans2V)
				{
					// Compute the area
					spp->height	= spp->lry - (f64)((s32)spp->lry);
					spp->area	= spp->widthLeft * spp->height;
					vvm_iiGetSpannedPixelComputationAppend(spp, 0, spp->bottomDelta, spp->area);
				}


			//////////
			// 8 - lower-middle (optional, spans at most multiple partial or full pixels)
			//////
				if (spp->spans2V && spp->spans3H)
				{
					s32 lnX, lnPixelX;
					// For every middle pixel, apply these values
					for (lnX = 1, lnPixelX = spp->middleStartH; lnPixelX <= spp->middleFinishH; lnX++, lnPixelX++)
						vvm_iiGetSpannedPixelComputationAppend(spp, lnX, spp->bottomDelta, spp->height);
				}


			//////////
			// 9 - lower-right (optional, spans at most one pixel)
			//////
				if (spp->spans2V && spp->spans2H)
				{
					// Compute the area
					spp->area = spp->widthRight * spp->height;
					vvm_iiGetSpannedPixelComputationAppend(spp, spp->rightDelta, spp->bottomDelta, spp->area);
				}
	}




//////////
//
// Store the pixel for this as another step for the addition and subtraction of pixel information
//
//////
	void CALLTYPE vvm_iiGetSpannedPixelComputationAppend(_isSSpannedPixelProcessing* spp, s32 tnDeltaX, s32 tnDeltaY, f64 tfAlpha)
	{
		SBGRACompute	lsc;


		// Make sure there's some valid data here (something that a human eye could see)
		if (tfAlpha > 0.00001f)
		{
			// Store information specific to this part of the computation
			// Compute the relative offset into the source canvas (unscaled canvas)
			lsc.offsetSrc		= spp->offsetSrc;

			// If there is a Y delta, apply it
			if (tnDeltaY != 0)
				lsc.offsetSrc	+= (tnDeltaY * spp->rowWidth);

			// If there is an X delta, apply it
			if (tnDeltaX != 0)
				lsc.offsetSrc	+= (tnDeltaX * sizeof(SBGRA));

			// Store the destination offset and multiplier for this portion of the pixel
			lsc.offsetDst		= spp->offsetDst;					// Offset into the destination canvas (scaled canvas)
			lsc.alpha			= tfAlpha / spp->areaSpanned;	// Multiplier for this pixel portion to add in to the total for that spanned pixel

			// Append this entry
			vvm_builderAppendData(spp->sm->scaleData, (s8*)&lsc, sizeof(lsc));
		}
	}




//////////
//
// Integers between means which maximum integer is touched?
// Basically, chopping off decimals reveals the range, such that values of
// 1.001 and 2.999 only touch integers 1 and 2, even though with rounding
// they would go from 1 to 3.  Their numerical roots are in only integers
// 1 and 2.
//
//////
	u32 CALLTYPE vvm_iGetIntegersBetween(f64 p1, f64 p2)
	{
		f64 v1, v2;


		// Get the lower integers
		v1 = floor(min(p1,p2));
		v2 = floor(max(p1,p2));

		// Indicate the number between
		return((u32)(v2 - v1));
	}




//////////
//
// Used for internal debugging.
//
//////
	void CALLTYPE vvm_enableBreakpoints(u64 id)
    {
    }




//////////
//
// Used for internal debugging.
//
//////
	void CALLTYPE vvm_disableBreakpoints(u64 id)
    {
    }
