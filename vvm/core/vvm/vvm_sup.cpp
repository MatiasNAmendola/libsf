//////////
//
// /libsf/vvm/vvm/vvm_sup.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     November 07, 2012 - Iniital creation
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
// Called to initialize a program structure to its power on state
//
// Returns:
//		Only returns true or false right now.
// TODO:  Could return information in some way (a log file) about what failed
//
//////
	bool ivvm_initializeProgram(SProgram* tp)
	{
		bool llResult;


		// Indicate failure initially
		llResult = false;

		// Lock the semaphore
		oss_lockSemaphore(gsVvm.gsemProgramsAccess);

		// Enter a loop for breaking
		while (tp)
		{
			/////////
			// Create program-level semaphore for access
			//////
				tp->semForThreadsAccess = oss_createSemaphore();


			/////////
			// Allocate our block of global memory slots
			//////
				llResult = ivvm_reallocateVariableBlock(&tp->_globals, gsVvm.gnGlobalAllocationBlockSize);
				if (!llResult)		break;		// Could not allocate our memory variable name slots


			/////////
			// Allocate our first thread block
			//////
				llResult = ivvm_allocateThread(&tp->_threads, NULL/*we don't need to know the slot during the first setup*/);
				if (!llResult)		break;		// Could not allocate our thread slot

			// If we get here, we're good, everything is setup
			break;
		}

		// Unlock the semaphore
		oss_unlockSemaphore(gsVvm.gsemProgramsAccess);

		// So far, so good
		return(llResult);
	}




//////////
//
// Called to initialize our memory variable slots
//
//////
	bool ivvm_reallocateVariableBlock(SStartEnd* ptrSEVar, u32 tnAllocationSize)
	{
		u32			lnI, lnStart;
		bool		llResult;
		SVariable*	lv;


		// Make sure our environment is sane
		llResult = false;
		if (ptrSEVar)
		{
			// Get our current count
			lnStart = ptrSEVar->masterCount;

			// Increase our buffer by the block size
			llResult = oss_allocateAdditionalStartEndMasterSlots(ptrSEVar, tnAllocationSize);
			if (llResult)
			{
				// From our initial value to the end, allocate space for each variable
				for (lnI = lnStart; llResult && lnI < ptrSEVar->masterCount; lnI++)
				{
					// Allocate the new entry
					lv = (SVariable*)oss_SEChain_append(ptrSEVar, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SVariable), tnAllocationSize, NULL);
					if (lv)
					{
						// Indicate no variables initially exist here, and that this is an empty slot
						lv->current.type	= _VVM_VARIABLE_TYPE_UNUSED;		// Initialize the slot to unused
						lv->prior.type		= _VVM_VARIABLE_TYPE_UNUSED;		// No prior variable type
						lv->_default.type	= _VVM_VARIABLE_TYPE_UNUSED;		// No default value

					} else {
						// Well, we had at least one error
						llResult = false;
					}
				}
			}
		}

		// Indicate success or failure
		return(llResult);
	}




//////////
//
// Allocates (or re-uses) a thread slot, initializes its stack, registers, etc., to an empty state
//
// Returns:
//		bool		- Indicates if a slot was found
//		ttSlot		- If provided, updated with the new slot pointer
//
//////
	bool ivvm_allocateThread(SStartEnd* ptrSEVar, SThread** ttSlot)
	{
		u32			lnI;
		bool		llResult;
		SThread*	ltNew;


		// Initially indicate failure
		llResult = false;

		// Make sure the environment is sane
		if (ptrSEVar)
		{
			// See if there exists anything already
			if (ptrSEVar->root)
			{
				for (lnI = 0; lnI < ptrSEVar->masterCount; lnI++)
				{
					if (!ptrSEVar->master[lnI]->used)
					{
						// We've found a free slot
						// Mark it used
						ptrSEVar->master[lnI]->used = true;

						// Update the caller's variable
						if (ttSlot)
							*ttSlot = (SThread*)ptrSEVar->master[lnI]->ptr;

						// Indicate success
						return(true);
					}
				}
				// If we get here, no unused slots
			}
			// If we get here, we need to increase the allocation

			// Allocate our new entry
			if (oss_allocateAdditionalStartEndMasterSlots(ptrSEVar, 1))
			{
				// We know we have our slot now
				// Allocate our new entry
				ltNew = (SThread*)oss_SEChain_append(ptrSEVar, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SThread), 1, NULL);
				if (ltNew)
				{
					// Allocate the stack size, we will use our 
					ltNew->stack.data._u8			= (u8*)oss_allocateAndNull(gsVvm.gnStackAllocationBlockSize, true);
					ltNew->stack.length				= gsVvm.gnStackAllocationBlockSize;
					ltNew->status.semaphoreAccess	= oss_createSemaphore();

					// Note:  The stack's offset is referenced by the sp (stack register) in ltNew->regs.sp
					// Note:  Registers are automatically allocated

					// Allocate the snippets for this thread
					llResult = ivvm_reallocateSnippets(&ltNew->snippet);
					// When we get here with llResult = true, the virtual machine is initialized
				}
			}
		}

		// Indicate success or failure
		return(llResult);
	}




//////////
//
// Called to initialize our snippet slotsslots
//
//////
	bool ivvm_reallocateSnippets(SStartEnd* ptrSESnip)
	{
		u32			lnI, lnStart;
		bool		llResult;
		SSnipExec*	lse;


		// Make sure our environment is sane
		llResult = false;
		if (ptrSESnip)
		{
			// Get our current count
			lnStart = ptrSESnip->masterCount;

			// Increase our buffer by the block size
			llResult = oss_allocateAdditionalStartEndMasterSlots(ptrSESnip, gsVvm.gnSnippetAllocationBlockSize);
			if (llResult)
			{
				// From our initial value to the end, allocate space for each snippet
				for (lnI = lnStart; llResult && lnI < ptrSESnip->masterCount; lnI++)
				{
					// Allocate the new entry
					lse = (SSnipExec*)oss_SEChain_append(ptrSESnip, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SSnipExec), gsVvm.gnSnippetAllocationBlockSize, NULL);
					if (lse)
					{
						// Indicate no parameters are initially populated at each snippet level
						// In essence, make them ready for first call
						llResult = ivvm_allocateSnippetParamsReturnsLocals(lse);

					} else {
						// Well, we had at least one error
						llResult = false;
					}
				}
			}
		}

		// Indicate success or failure
		return(llResult);
	}




//////////
//
// This function is called to allocate everything required for a newly allocated snippet slot
// for a thread.  It should only be called at startup, and then as the source code begins to
// get deeper than the gnSnippetAllocationBlockSize.
//
//////
	bool ivvm_allocateSnippetParamsReturnsLocals(SSnipExec* tse)
	{
		bool llResult;


		// Initially indicate failure
		llResult = false;

		// Parameters first
		if (ivvm_allocateSnippetVariables(&tse->_params, _VVM_PARAMS_ALLOCATION_SIZE))
		{
			// Return variables second (Note:  These will ALL be references)
			if (ivvm_allocateSnippetVariables(&tse->_returns, _VVM_RETURNS_ALLOCATION_SIZE))
			{
				// Local variables
				if (ivvm_allocateSnippetVariables(&tse->_locals, gsVvm.gnLocalAllocationBlockSize))
				{
					// If we get here, we have everything allocated
					llResult = true;
				}
			}
		}

		// If we get here, something failed
		return(llResult);
	}

	bool ivvm_allocateSnippetVariables(SStartEnd* ptrSEVar, u32 tnAllocationSize)
	{
		u32			lnI, lnStart;
		bool		llResult;
		SVariable*	lv;


		// Make sure our environment is sane
		llResult = false;
		if (ptrSEVar)
		{
			// Get our current count
			lnStart = ptrSEVar->masterCount;

			// Increase our buffer by the block size
			llResult = oss_allocateAdditionalStartEndMasterSlots(ptrSEVar, tnAllocationSize);
			if (llResult)
			{
				// From our initial value to the end, allocate space for each snippet
				for (lnI = lnStart; llResult && lnI < ptrSEVar->masterCount; lnI++)
				{
					// Allocate the new entry
					lv = (SVariable*)oss_SEChain_append(ptrSEVar, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SVariable), tnAllocationSize, NULL);
					if (lv)
					{
						// Indicate no variables initially exist here, and that this is an empty slot
						lv->current.type	= _VVM_VARIABLE_TYPE_UNUSED;		// Initialize the slot to unused
						lv->prior.type		= _VVM_VARIABLE_TYPE_UNUSED;		// No prior variable type
						lv->_default.type	= _VVM_VARIABLE_TYPE_UNUSED;		// No default value

					} else {
						// Well, we had at least one error
						llResult = false;
					}
				}
			}
		}

		// Indicate success or failure
		return(llResult);
	}
