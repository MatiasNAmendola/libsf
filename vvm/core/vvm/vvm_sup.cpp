//////////
//
// /libsf/vvm/vvm/vvm_sup.cpp
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
//     Nov.07.2012 - Iniital creation
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
// Get the next Unique ID
//
//////
	u64 ivvm_getNextUniqueId(void)
	{
		u64 lnValue;

		// Synchronized access
		oss_lockSemaphore((u64)&gcsUniqueIdAccess);

		// Get our value and increment
		lnValue = gnNextUniqueId;
		++gnNextUniqueId;

		// All done
		oss_unlockSemaphore((u64)&gcsUniqueIdAccess);

		// Return that value
		return(lnValue);
	}




//////////
//
// Get the next N Unique IDs
//
// Returns:
//		The last unique id assigned
//		-1 if error
//
//////
	u64 ivvm_getNextN_UniqueIds(u64* tnArrayBase, u32 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (tnArrayBase && tnCount > 0)
		{
			// Synchronized access
			oss_lockSemaphore((u64)&gcsUniqueIdAccess);

			// Get our value and increment
			for (lnI = 0; lnI < tnCount; lnI++)
			{
				tnArrayBase[lnI] = gnNextUniqueId;
				++gnNextUniqueId;
			}

			// All done
			oss_unlockSemaphore((u64)&gcsUniqueIdAccess);

			// Return that value
			return(tnArrayBase[lnI - 1]);

		} else {
			// Hmmm... bad params, indicate failure
			return(-1);
		}
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
			llResult = vvm_SEChain_allocateAdditionalMasterSlots(ptrSEVar, tnAllocationSize);
			if (llResult)
			{
				// From our initial value to the end, allocate space for each variable
				for (lnI = lnStart; llResult && lnI < ptrSEVar->masterCount; lnI++)
				{
					// Allocate the new entry
					lv = (SVariable*)vvm_SEChain_append(ptrSEVar, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SVariable), tnAllocationSize, NULL);
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
			if (vvm_SEChain_allocateAdditionalMasterSlots(ptrSEVar, 1))
			{
				// We know we have our slot now
				// Allocate our new entry
				ltNew = (SThread*)vvm_SEChain_append(ptrSEVar, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SThread), 1, NULL);
				if (ltNew)
				{
					// Allocate the stack size, we will use our 
					ltNew->stack.data._u8			= (u8*)vvm_allocateAndNull(gsVvm.gnStackAllocationBlockSize, true);
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
			llResult = vvm_SEChain_allocateAdditionalMasterSlots(ptrSESnip, gsVvm.gnSnippetAllocationBlockSize);
			if (llResult)
			{
				// From our initial value to the end, allocate space for each snippet
				for (lnI = lnStart; llResult && lnI < ptrSESnip->masterCount; lnI++)
				{
					// Allocate the new entry
					lse = (SSnipExec*)vvm_SEChain_append(ptrSESnip, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SSnipExec), gsVvm.gnSnippetAllocationBlockSize, NULL);
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
			llResult = vvm_SEChain_allocateAdditionalMasterSlots(ptrSEVar, tnAllocationSize);
			if (llResult)
			{
				// From our initial value to the end, allocate space for each snippet
				for (lnI = lnStart; llResult && lnI < ptrSEVar->masterCount; lnI++)
				{
					// Allocate the new entry
					lv = (SVariable*)vvm_SEChain_append(ptrSEVar, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SVariable), tnAllocationSize, NULL);
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
// Scans from the indicated location forward until finding a non-whitespace, non-cr, non-lf
// character.
//
//////
	u64 ivvm_skipWhitespacesAndCrLf(s8* tcData, u64 tnMaxLength)
	{
		u64 lnLength;


		// Make sure our environment's sane
		lnLength = 0;		// Initially indicate no whitespaces
		if (tcData && tnMaxLength > 0)
		{
			// While we encounter spaces or tabs, count them
			while (lnLength < tnMaxLength && (tcData[lnLength] == 32 || tcData[lnLength] == 9 || tcData[lnLength] == 10 || tcData[lnLength] == 13))
				++lnLength;
			// When we get here, lnLength is the number of whitespace/cr/lf (if any)
		}
		// Indicate the total length encountered
		return(lnLength);
	}




//////////
//
// Verifies that the indicated length is allowed based on the maximum length / position.
//
//////
	inline bool ivvm_verifyLength(u64 tnGoingTo, u64 tnMaxAllowable)
	{
		return(tnGoingTo <= tnMaxAllowable);
	}




//////////
//
// Returns whether or not the indicated character is alpha or alphanumeric
//
//////
	bool ivvm_isAlpha(s8 c)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
			return(true);

		// If we get here, it wasn't alpha
		return(false);
	}

	bool ivvm_isNumeric(s8 c)
	{
		if (c >= '0' && c <= '9')
			return(true);

		// If we get here, it wasn't numeric
		return(false);
	}

	bool ivvm_isAlphanumeric(s8 c)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
			return(true);

		// If we get here, it wasn't alphanumeric
		return(false);
	}




//////////
//
// Called to convert the sequence of numeric digits, which must be pre-validated to exist as
// numeric digits, into a number.
//
//////
	u32 ivvm_convertValidatedNumericStringToU32(s8* tcData, u32 tnMaxLength)
	{
		u32 lnI, lnValue;


		// Make sure our environment is sane
		lnValue = 0;
		if (tcData && tnMaxLength != 0)
		{
			// Repeat for every digit
			for (lnI = 0; lnI < tnMaxLength; lnI++)
			{
				lnValue = lnValue * 10;
				lnValue = lnValue + (u32)(tcData[lnI] - '0');
			}
		}

		// Return our value
		return(lnValue);
	}

	u64 ivvm_convertValidatedNumericStringToU64(s8* tcData, u32 tnMaxLength)
	{
		u32 lnI;
		u64 lnValue;


		// Make sure our environment is sane
		lnValue = 0;
		if (tcData && tnMaxLength != 0)
		{
			// Repeat for every digit
			for (lnI = 0; lnI < tnMaxLength; lnI++)
			{
				lnValue = lnValue * 10;
				lnValue = lnValue + (u64)(tcData[lnI] - '0');
			}
		}

		// Return our value
		return(lnValue);
	}




//////////
//
// Called to delete all nodes 
//
//////
	void ivvm_ll4_deleteChainAllNodes(SLL4Callback* cb, SLL4* node)
	{
		u32			lnI;
		SStartEnd	nodeList;


// TODO:  UNTESTED CODE
		// Make sure our environment is sane
		if (node)
		{
			//////////
			// Initialize a buffer for all the of the nodes (we traverse to get a unique node list before deleting them all)
			//////
				memset(&nodeList, 0, sizeof(nodeList));
				vvm_SEChain_allocateAdditionalMasterSlots(&nodeList, _COMMON_START_END_BIG_BLOCK_SIZE);


			//////////
			// Build the list from the node mesh
			//////
				iivvm_ll4_deleteChainAllNodes(&nodeList, node,			_LL4_EAST);		// Conduct self plus everything east
				iivvm_ll4_deleteChainAllNodes(&nodeList, node->west,	_LL4_WEST);		// Conduct everything west
				iivvm_ll4_deleteChainAllNodes(&nodeList, node->north,	_LL4_NORTH);	// Conduct everything north
				iivvm_ll4_deleteChainAllNodes(&nodeList, node->south,	_LL4_SOUTH);	// Conduct everything south


			//////////
			// Now we have our list of items to delete
			//////
				for (lnI = 0; lnI < nodeList.masterCount; lnI++)
				{
					//////////
					// When we're done, we're done
					//////
						if (!nodeList.ptr[lnI])
							break;	// We're done


					//////////
					// Callback if need be
					//////
						if (cb && cb->_func)
						{
							cb->node = node;
							cb->funcVoid(cb);
						}


					//////////
					// Free this node, which also orphanizes it if need be
					//////
						vvm_ll4_delete((SLL4*)nodeList.ptr[lnI]);
				}


			//////////
			// Delete the list of nodes, which is no longer required
			//////
				vvm_SEChain_delete(&nodeList, 0, 0, false);
		}
	}




//////////
//
// We scan each pointer to see if it exists in the already compiled list
//
//////
	void iivvm_ll4_deleteChainAllNodes(SStartEnd* nodeList, SLL4* node, u32 tnDirection)
	{
		u32		lnI;
		SLL4*	nodeNext;


// TODO:  UNTESTED CODE
		// Iterate through every node in the indicated direction
		while (node)
		{
			//////////
			// See if this pointer is already known
			//////
				for (lnI = 0; lnI < nodeList->masterCount; lnI++)
				{
					// Are we out of slots to test?
					if (!nodeList->ptr[lnI])
						break;	// Yes, we're done searching for slots (the new pointer can go here)

					// See if this is a match
					if (nodeList->ptr[lnI] == node)
						return;	// Yes, we're done with this direction
				}
				// When we get here, we know it wasn't found and we need to add it


			//////////
			// Is there enough space?
			//////
				if (lnI == nodeList->masterCount)
					vvm_SEChain_allocateAdditionalMasterSlots(nodeList, _COMMON_START_END_BIG_BLOCK_SIZE);		// No, allocate more space


			//////////
			// Append this data to this slot
			//////
				nodeList->ptr[lnI] = node;


			//////////
			// Grab the next node
			/////
				switch (tnDirection)
				{
					case _LL4_NORTH:
						nodeNext = node->north;
						// Spawn off a search easterly, and westerly
						iivvm_ll4_deleteChainAllNodes(nodeList, node->east,		_LL4_EAST);
						iivvm_ll4_deleteChainAllNodes(nodeList, node->west,		_LL4_WEST);
						break;

					case _LL4_SOUTH:
						nodeNext = node->south;
						// Spawn off a search easterly, and westerly
						iivvm_ll4_deleteChainAllNodes(nodeList, node->east,		_LL4_EAST);
						iivvm_ll4_deleteChainAllNodes(nodeList, node->west,		_LL4_WEST);
						break;

					case _LL4_WEST:
						nodeNext = node->west;
						// Spawn off a search northerly, and southerly
						iivvm_ll4_deleteChainAllNodes(nodeList, node->north,	_LL4_NORTH);
						iivvm_ll4_deleteChainAllNodes(nodeList, node->south,	_LL4_SOUTH);
						break;

					case _LL4_EAST:
						nodeNext = node->east;
						// Spawn off a search northerly, and southerly
						iivvm_ll4_deleteChainAllNodes(nodeList, node->north,	_LL4_NORTH);
						iivvm_ll4_deleteChainAllNodes(nodeList, node->south,	_LL4_SOUTH);
						break;

					default:
						// Invalid direction, abort
						return;
				}


			//////////
			// Move to the next node
			/////
				node = nodeNext;
		}
	}




//////////
//
// Called to ensure the indicated number of bytes can be appended onto the buffer without
// issue.  If not, reallocates the buffer.
//
//////
	void ivvm_bufferVerifySizeForNewBytes(SBuilder* buffRoot, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot && tnDataLength != 0)
		{
			// Repeatedly allocate our allocation size until we get big enough
			while (buffRoot->data)
			{
				// Are we there yet?
				if (buffRoot->populatedLength + tnDataLength < buffRoot->allocatedLength)
				{
					// We're good, update our populated size
					buffRoot->populatedLength += tnDataLength;
					return;
				}
				// If we get here, we need to allocate more space

				// Reallocate and continue
				buffRoot->data				= (s8*)oss_realloc(buffRoot->data, buffRoot->allocatedLength + buffRoot->allocateBlockSize);
				buffRoot->allocatedLength	+= buffRoot->allocateBlockSize;
			}
		}
		// If we get here, there's been an error
	}




//////////
//
// Computes the sides, semiperimeter and area of a triangle
//
//////
	void iivvm_math_computeTriangle(STriangleF64* tri)
	{
		f64 lfdx, lfdy;


		//////////
		// P1..P2 length
		//////
			lfdx		= tri->p1.x - tri->p2.x;
			lfdy		= tri->p1.y - tri->p2.y;
			tri->p1_p2	= sqrt(lfdx*lfdx + lfdy*lfdy);

		//////////
		// P2..P3 length
		//////
			lfdx			= tri->p2.x - tri->p3.x;
			lfdy			= tri->p2.y - tri->p3.y;
			tri->p2_p3	= sqrt(lfdx*lfdx + lfdy*lfdy);

		//////////
		// P3..P1 length
		//////
			lfdx			= tri->p3.x - tri->p1.x;
			lfdy			= tri->p3.y - tri->p1.y;
			tri->p3_p1	= sqrt(lfdx*lfdx + lfdy*lfdy);

		//////////
		// Semi-perimeter (half the perimeter)
		//////
			tri->sp		= (tri->p1_p2 + tri->p2_p3 + tri->p3_p1) / 2.0;

		//////////
		// Area:  sqrt(s * (s-p12) * (s-p23) * (s-p31))
		//////
			tri->area	= sqrt( tri->sp * (tri->sp - tri->p1_p2) * (tri->sp - tri->p2_p3) * (tri->sp - tri->p3_p1));
	}




//////////
//
// Computes information about a square relative to a given origin
//
//////
	void iivvm_math_computeSquare(SSquareInOutF64* sq, f32 ox, f32 oy)
	{
		f64 lfdx, lfdy;


		//////////
		// Store origin
		//////
			sq->compute->origin.x		= (f64)ox;
			sq->compute->origin.y		= (f64)oy;

		//////////
		// Compute center
		//////
			sq->compute->center.x		= (sq->input->p1.x + sq->input->p2.x + sq->input->p3.x + sq->input->p4.x) / 4.0;
			sq->compute->center.y		= (sq->input->p1.y + sq->input->p2.y + sq->input->p3.y + sq->input->p4.y) / 4.0;

		//////////
		// Compute midpoints
		//////
			// p1..p2
			sq->compute->p1_p2mid.x		= (sq->input->p1.x + sq->input->p2.x) / 2.0;
			sq->compute->p1_p2mid.y		= (sq->input->p1.y + sq->input->p2.y) / 2.0;
			// p2..p3
			sq->compute->p2_p3mid.x		= (sq->input->p2.x + sq->input->p3.x) / 2.0;
			sq->compute->p2_p3mid.y		= (sq->input->p2.y + sq->input->p3.y) / 2.0;
			// p3..p4
			sq->compute->p3_p4mid.x		= (sq->input->p3.x + sq->input->p4.x) / 2.0;
			sq->compute->p3_p4mid.y		= (sq->input->p3.y + sq->input->p4.y) / 2.0;
			// p4..p1
			sq->compute->p4_p1mid.x		= (sq->input->p4.x + sq->input->p1.x) / 2.0;
			sq->compute->p4_p1mid.y		= (sq->input->p4.y + sq->input->p1.y) / 2.0;

		//////////
		// Compute lengths and slopes
		//////
			// p1..p2
			lfdx						= sq->input->p2.x - sq->input->p1.x;
			lfdy						= sq->input->p2.y - sq->input->p1.y;
			sq->compute->p1_p2			= sqrt(lfdx*lfdx + lfdy*lfdy);
			sq->compute->p1_p2mmp.m		= lfdy / lfdx;
			sq->compute->p1_p2mmp.mp	= -lfdx / lfdy;
			// p2..p3
			lfdx						= sq->input->p3.x - sq->input->p2.x;
			lfdy						= sq->input->p3.y - sq->input->p2.y;
			sq->compute->p2_p3			= sqrt(lfdx*lfdx + lfdy*lfdy);
			sq->compute->p2_p3mmp.m		= lfdy / lfdx;
			sq->compute->p2_p3mmp.mp	= -lfdx / lfdy;
			// p3..p4
			lfdx						= sq->input->p4.x - sq->input->p3.x;
			lfdy						= sq->input->p4.y - sq->input->p3.y;
			sq->compute->p3_p4			= sqrt(lfdx*lfdx + lfdy*lfdy);
			sq->compute->p3_p4mmp.m		= lfdy / lfdx;
			sq->compute->p3_p4mmp.mp	= -lfdx / lfdy;
			// p4..p1
			lfdx						= sq->input->p1.x - sq->input->p4.x;
			lfdy						= sq->input->p1.y - sq->input->p4.y;
			sq->compute->p4_p1			= sqrt(lfdx*lfdx + lfdy*lfdy);
			sq->compute->p4_p1mmp.m		= lfdy / lfdx;
			sq->compute->p4_p1mmp.mp	= -lfdx / lfdy;

		//////////
		// Compute radius and theta
		//////
			// p1
			sq->compute->p1rt.theta		= atan2(sq->input->p1.y - sq->compute->center.y, sq->input->p1.x - sq->compute->center.x);
			lfdx						= sq->input->p1.x - sq->compute->center.x;
			lfdy						= sq->input->p1.y - sq->compute->center.y;
			sq->compute->p1rt.radius	= sqrt(lfdx*lfdx + lfdy*lfdy);
			// p2
			sq->compute->p2rt.theta		= atan2(sq->input->p2.y - sq->compute->center.y, sq->input->p2.x - sq->compute->center.x);
			lfdx						= sq->input->p2.x - sq->compute->center.x;
			lfdy						= sq->input->p2.y - sq->compute->center.y;
			sq->compute->p2rt.radius	= sqrt(lfdx*lfdx + lfdy*lfdy);
			// p3
			sq->compute->p3rt.theta		= atan2(sq->input->p3.y - sq->compute->center.y, sq->input->p3.x - sq->compute->center.x);
			lfdx						= sq->input->p3.x - sq->compute->center.x;
			lfdy						= sq->input->p3.y - sq->compute->center.y;
			sq->compute->p3rt.radius	= sqrt(lfdx*lfdx + lfdy*lfdy);
			// p4
			sq->compute->p4rt.theta		= atan2(sq->input->p4.y - sq->compute->center.y, sq->input->p4.x - sq->compute->center.x);
			lfdx						= sq->input->p4.x - sq->compute->center.x;
			lfdy						= sq->input->p4.y - sq->compute->center.y;
			sq->compute->p4rt.radius	= sqrt(lfdx*lfdx + lfdy*lfdy);
	}




//////////
//
// Called to compute the midpoint, slope, and perpendicular slope of a line
//
//////
	void iivvm_math_computeLine(SLineF64* line)
	{
		// Midpoint = (x2-x1)/2, (y2-y1)/2
		line->mid.x			= (line->p1.x + line->p2.x) / 2.0;
		line->mid.y			= (line->p1.y + line->p2.y) / 2.0;

		// Compute our deltas
		line->delta.x		= line->p2.x - line->p1.x;
		line->delta.y		= line->p2.y - line->p1.y;

		// Length
		line->length		= sqrt(line->delta.x*line->delta.x + line->delta.y*line->delta.y);

		// Slope = rise over run
		line->m				= line->delta.y / ((line->delta.x == 0.0) ? 0.00000000000001 : line->delta.x);

		// Perpendicular slope = -1/m
		line->mp			= -1.0 / ((line->m == 0.0) ? 0.00000000000001 : line->m);


		//////////
		// Compute theta if need be (radius is same as length)
		/////
			if (line->trig)
				line->theta		= iivvm_math_adjustTheta(atan2(line->delta.y, line->delta.x));


		//////////
		// Compute the integer roundings if need be
		//////
			if (line->ints)
			{
				// Start
				line->p1i.x		= (s32)line->p1.x;
				line->p1i.y		= (s32)line->p1.y;
				// End
				line->p2i.x		= (s32)line->p2.x;
				line->p2i.y		= (s32)line->p2.y;
			}


		//////////
		// Compute the quadrants if need be
		//////
			if (line->quads)
			{
				// Quads 1..4
				line->p1_quad	= iivvm_math_computeQuad(&line->p1);
				line->p2_quad	= iivvm_math_computeQuad(&line->p2);
			}
	}




//////////
//
// Returns the quadrant for the indicated point
//
//////
	s32 iivvm_math_computeQuad(SXYF64* p)
	{
		if (p->x >= 0.0)
		{
			// Either 1 or 4
			if (p->y >= 0.0)		return(1);		// X is positive, Y is positive
			else					return(4);		// X is positive, Y is negative

		} else {
			// Either 2 or 3
			if (p->y >= 0.0)		return(2);		// X is negative, Y is positive
			else					return(3);		// X is negative, Y is negative
		}
	}




//////////
//
// Copies the two points into the line, and optionally computes the line
//
//////
	void iivvm_copyLine(SLineF64* line, SXYF64* p1, SXYF64* p2, bool tlComputeLine)
	{
		// Copy
		memcpy(&line->p1, p1, sizeof(SXYF64));
		memcpy(&line->p2, p2, sizeof(SXYF64));

		// Compute if need be
		if (tlComputeLine)
			iivvm_math_computeLine(line);
	}




//////////
//
// Called to rotate the square about the sq->computed radians.  The data in sq->computed
// should've already been set (or computed with a call to ivvm_math_computeSquare() relative
// to the indicated origin pixel).
//
//////
	void ivvm_math_squareRotateAbout(SSquareInOutF64* sq)
	{
//		f64 lfdx, lfdy;


		// Make sure our environment is sane
		if (sq && sq->input && sq->output)
		{
// 			//////////
// 			// Rotate P1
// 			//////
// 				sq->output->p1x		= sq->computed->ox + (sq->computed->radiusP1 * cos(sq->computed->thetaP1 + sq->computed->radians));
// 				sq->output->p1y		= sq->computed->oy + (sq->computed->radiusP1 * sin(sq->computed->thetaP1 + sq->computed->radians));
// 
// 			//////////
// 			// Rotate P2
// 			//////
// 				sq->output->p2x		= sq->computed->ox + (sq->computed->radiusP2 * cos(sq->computed->thetaP2 + sq->computed->radians));
// 				sq->output->p2y		= sq->computed->oy + (sq->computed->radiusP2 * sin(sq->computed->thetaP2 + sq->computed->radians));
// 
// 			//////////
// 			// Rotate P3
// 			//////
// 				sq->output->p3x		= sq->computed->ox + (sq->computed->radiusP3 * cos(sq->computed->thetaP3 + sq->computed->radians));
// 				sq->output->p3y		= sq->computed->oy + (sq->computed->radiusP3 * sin(sq->computed->thetaP3 + sq->computed->radians));
// 
// 			//////////
// 			// Rotate P4
// 			//////
// 				sq->output->p4x		= sq->computed->ox + (sq->computed->radiusP4 * cos(sq->computed->thetaP4 + sq->computed->radians));
// 				sq->output->p4y		= sq->computed->oy + (sq->computed->radiusP4 * sin(sq->computed->thetaP4 + sq->computed->radians));
// 
// 			//////////
// 			// Compute the new slope, and perpendicular slope
// 			//////
// 				lfdx				=   sq->output->p2x - sq->output->p1x;
// 				lfdy				= -(sq->output->p2y - sq->output->p1y);				// Negative because Y is reversed on-screen
// 
// 				if (lfdx == 0)		sq->output->m = lfdy / 0.0000000000001;
// 				else				sq->output->m = lfdy / lfdx;						// Compute the slope P1..P2 (rise/run)
// 
// 				sq->output->mp		= -1.0 / sq->output->m;								// Compute the perpendicular slope, which is the slope of P1..P4
		}
	}




//////////
//
// Called to initialize a new polygon (or re-initialize an existing polygon), and to
// optionally allocate new lines and initialize those as well.
//
//////
	bool iivvm_polygon_initialize(SPolygon* poly, u32 tnLineCount, bool tlAllocatePolyLines)
	{
		u32			lnI;
		bool		llResult;
		SPolyLine**	lplp;
		SPolyLine*	lpl;


		// Is it already allocated?
		llResult = false;
		if (poly->line)
		{
			// We may need to increase its size
			if (poly->lineCount < tnLineCount)
			{
				//////////
				// We need to increase the allocation
				//////
					lplp = (SPolyLine**)realloc(poly->line, tnLineCount * sizeof(SPolyLine));
					if (lplp)
					{
						//////////
						// We're good
						//////
							poly->line = lplp;


						//////////
						// Initialize the extra entries
						//////
							llResult = true;
							for (lnI = poly->lineCount; lnI < tnLineCount; lnI++)
							{
								if (tlAllocatePolyLines)
								{
									// Allocate the new entry
									poly->line[lnI] = (SPolyLine*)malloc(sizeof(SPolyLine));

									// If it was allocated, initialize it to empty
									if (poly->line[lnI])
									{
										// Initialize it
										memset(poly->line[lnI], 0, sizeof(SPolyLine));

									} else {
										// There was a failure at some point
										llResult = false;
									}

								} else {
									// Initialize the new entry to nothingness
									poly->line[lnI] = NULL;
								}
							}


						//////////
						// Store the new count
						//////
							poly->lineCount	= tnLineCount;
					}

			// We may need to decrease its size
			} else if (poly->lineCount > tnLineCount) {
				//////////
				// We need to decrease the allocation
				//////
					// Free the extra allocated entries
					for (lnI = tnLineCount + 1; lnI < poly->lineCount; lnI++)
					{
						// Grab that line
						lpl = poly->line[lnI];

						// Free it if need be
						if (lpl)
							free(lpl);

						// Mark it freed
						poly->line[lnI] = NULL;
					}

					// Resize to the newer, lower size
					lplp = (SPolyLine**)realloc(poly->line, tnLineCount * sizeof(SPolyLine));
					if (lplp)
					{
						//////////
						// We're good
						//////
							poly->line		= lplp;
							poly->lineCount	= tnLineCount;
							llResult		= true;
					}
			}

		} else {
			// We need to allocate the lot
			lplp = (SPolyLine**)malloc(tnLineCount * sizeof(SPolyLine));
			if (lplp)
			{
				// We're good
				poly->line		= lplp;
				poly->lineCount	= tnLineCount;

				//////////
				// Initialize the new entries
				//////
					llResult = true;
					for (lnI = 0; lnI < tnLineCount; lnI++)
					{
						if (tlAllocatePolyLines)
						{
							// Allocate the new entry
							poly->line[lnI] = (SPolyLine*)malloc(sizeof(SPolyLine));

							// If it was allocated, initialize it to empty
							if (poly->line[lnI])
							{
								// Populate the line
								memset(poly->line[lnI], 0, sizeof(SPolyLine));

							} else {
								// There was a failure at some point
								llResult = false;
							}

						} else {
							// Initialize the new entry to nothingness
							poly->line[lnI] = NULL;
						}
					}
			}
		}
		// Indicate our success or failure
		return(llResult);
	}




//////////
//
// Called to set the indicated polygon
//
//////
	bool iivvm_polygon_setByPolyLine(SPolygon* poly, u32 tnEntry, SPolyLine* line)
	{
		//////////
		// If this slot hasn't already been allocated, allocate it
		//////
			if (!poly->line[tnEntry])
			{
				// There isn't an entry yet allocated.
				// Create one.
				poly->line[tnEntry] = (SPolyLine*)malloc(sizeof(SPolyLine));
			}


		//////////
		// If we have an allocated slot, copy it
		//////
			if (poly->line[tnEntry])
			{
				// Copy, and indicate success
				memcpy(poly->line[tnEntry], line, sizeof(SPolyLine));
				return(true);

			} else {
				// Indicate failure
				return(false);
			}
	}




//////////
//
// Called to set the indicated polygon by values
//
//////
	bool iivvm_polygon_setByValues(SPolygon* poly, u32 tnEntry, SXYF64* start, SXYF64* end, SXYF64* gravity)
	{
		//////////
		// If this slot hasn't already been allocated, allocate it
		//////
			if (!poly->line[tnEntry])
			{
				// There isn't an entry yet allocated.
				// Create one.
				poly->line[tnEntry] = (SPolyLine*)malloc(sizeof(SPolyLine));
			}


		//////////
		// If we have an allocated slot, copy it
		//////
			if (poly->line[tnEntry])
			{
				// Copy the values
				memcpy(&poly->line[tnEntry]->start,		start,		sizeof(SXYF64));
				memcpy(&poly->line[tnEntry]->end,		end,		sizeof(SXYF64));
				memcpy(&poly->line[tnEntry]->gravity,	gravity,	sizeof(SXYF64));

				// Indicate success
				return(true);

			} else {
				// Indicate failure
				return(false);
			}
	}




	void iivvm_canvasPolygon_processSmall(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color, _isSCanvasDrawPolygonParameters* lcdp)
	{
		u32				lnI;
		s32				lnX, lnY, lnX4, lnY4, lnMinX, lnMinY, lnMaxX, lnMaxY, lnWidth, lnHeight, lnMinX4, lnMinY4, lnMaxX4, lnMaxY4;
		f64				lfArea;
		SXYF64			start, end;
		SPolygon		lpoly;
		SPolyLine*		line;
		SBGRACompute*	sbgrac;
		SBGRACompute	sbgracNew;


		//////////
		// Create our temporary polygon
		//////
			if (!vvm_polygon_initialize(&lpoly, poly->lineCount, true))
				return;		// Failure allocating


		//////////
		// Find the point closest to the origin
		//////
			// Initialize our polygon
			memset(&lpoly, 0, sizeof(lpoly));

			// Initialize our min and max to out of range values so they'll be set in the loop
			lnMinX	= 999999999;
			lnMinY	= 999999999;
			lnMaxX	= -999999999;
			lnMaxY	= -999999999;

			// Move forward
			for (lnI = 0; lnI < poly->lineCount; lnI++)
			{
				// Grab the line
				line = poly->line[lnI];

				// Check our min's
				if ((s32)line->start.x < lnMinX)		lnMinX = (s32)line->start.x;
				if ((s32)line->start.y < lnMinY)		lnMinY = (s32)line->start.y;
				if ((s32)line->end.x   < lnMinX)		lnMinX = (s32)line->end.x;
				if ((s32)line->end.y   < lnMinY)		lnMinY = (s32)line->end.y;

				// Check our max's
				if ((s32)line->start.x > lnMaxX)		lnMaxX = (s32)line->start.x;
				if ((s32)line->start.y > lnMaxY)		lnMaxY = (s32)line->start.y;
				if ((s32)line->end.x   > lnMaxX)		lnMaxX = (s32)line->end.x;
				if ((s32)line->end.y   > lnMaxY)		lnMaxY = (s32)line->end.y;
			}

			// Get our width and height
			lnWidth		= lnMaxX - lnMinX;
			lnHeight	= lnMaxY - lnMinY;


		//////////
		// Move the indicated polygon to (0,0) to (w,h)
		//////
			for (lnI = 0; lnI < poly->lineCount; lnI++)
			{
				// Grab the line
				line = poly->line[lnI];

				// Adjust start and end to 0,0
				start.x		= line->start.x	- (f64)lnMinX;
				start.y		= line->start.y	- (f64)lnMinY;
				end.x		= line->end.x	- (f64)lnMinX;
				end.y		= line->end.y	- (f64)lnMinY;

				// Set this value
				vvm_polygon_setByValues(&lpoly, lnI, &start, &end, &line->gravity);
			}
		
		
		//////////
		// Multiply every polygon line size by 4
		// Note:  This could be combined with the above, but it's not that much slower, and
		//        it is easier to mentally visualize and debug ... so ... why not leave it? :-)
		//////
			for (lnI = 0; lnI < poly->lineCount; lnI++)
			{
				// Grab the line
				line = lpoly.line[lnI];

				// Multiply each point size by 4
				iivvm_math_multiplyBy(&line->start,	4.0);
				iivvm_math_multiplyBy(&line->end,	4.0);
			}
		
		
		//////////
		// Recompute
		//////
			vvm_iiCanvasPolygon(tsDst, NULL, &lpoly, color);


		//////////
		// Assemble the larger polygon down into the smaller polygon
		//////
			for (lnY = 0; lnY < lnHeight; lnY++)
			{
				for (lnX = 0; lnX < lnWidth; lnX++)
				{
					//////////
					// Initialize
					//////
						lfArea	= 0.0;
						lnMinX4 = lnX * 4;				// Set the X,Y range to be a-checkin' for, by gum!
						lnMinY4 = lnY * 4;
						lnMaxX4 = lnMinX4 + 3;
						lnMaxY4 = lnMinY4 + 3;


					//////////
					// Add in any pixel floans
					//////
						for (lnI = 0; lnI < lpoly.pixelFloans->populatedLength; lnI += sizeof(SBGRACompute))
						{
							// Grab this floan pixel element
							sbgrac = (SBGRACompute*)(lpoly.pixelFloans->data + lnI);

							// Is it in range in both the X and Y directions?
							if (sbgrac->y >= lnMinY4 && sbgrac->y <= lnMaxY4 && sbgrac->x >= lnMinX4 && sbgrac->x <= lnMaxX4)
							{
								// Yes, this is one
								lfArea += sbgrac->alpha;
							}
						}


					//////////
					// Add in any range floans which occupy this pixel range
					//////
						for (lnI = 0; lnI < lpoly.rangeFloans->populatedLength; lnI += sizeof(SBGRACompute))
						{
							// Grab this floan range element
							sbgrac = (SBGRACompute*)(lpoly.rangeFloans->data + lnI);

							// See if it's in range
							for (lnY4 = lnMinY4; lnY4 <= lnMaxY4; lnY4++)
							{
								// Are we on the right row?
								if (lnY4 >= sbgrac->yStart && lnY4 <= sbgrac->yEnd)
								{
									// Yes, check the columns
									for (lnX4 = lnMinX4; lnX4 <= lnMaxX4; lnX4++)
									{
										// Are we on the right column?
										if (lnX4 >= sbgrac->xStart && lnX4 <= sbgrac->xEnd)
										{
											// Yes, this is one
											lfArea += sbgrac->alpha;
										}
									}
								}
							}
						}


					/////////
					// We have our total area
					//////
						lfArea /= 16.0;
						if (lfArea != 0.0)
						{
							// Initialize our new floan information
							memset(&sbgracNew, 0, sizeof(sbgracNew));

							// Populate it
							sbgracNew.x			= lnX + lnMinX;
							sbgracNew.y			= lnY + lnMinY;
							sbgracNew.alpha		= lfArea;

							// Add in a floan to the destination polygon
							vvm_builderAppendData(poly->pixelFloans, (s8*)&sbgracNew, sizeof(sbgracNew));
						}

				}
			}


		//////////
		// All done!
		//////
			vvm_polygon_freeAndRelease(poly, true);
	}

	void iivvm_canvasPolygon_processNormal(SCanvas* tsDst, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp)
	{
		//////////
		// Allocate for the corners, floans, and lines, and initialize our internal structure
		//////
			vvm_builderCreateAndInitialize(&lcdp->corners,		_COMMON_BUILDER_BLOCK_SIZE);
			vvm_builderCreateAndInitialize(&poly->pixelFloans,	_COMMON_BUILDER_BLOCK_SIZE_BIG);	// SBGRACompute structure indicating individual pixel populations
			vvm_builderCreateAndInitialize(&poly->rangeFloans,	_COMMON_BUILDER_BLOCK_SIZE_BIG);	// SBGRACompute structure indicating the starting and ending range
			memset(&lcdp->sfld, 0, sizeof(lcdp->sfld));


		//////////
		// Store the information used for computing all the floans
		//////
			lcdp->sfld.floans	= poly->pixelFloans;


		//////////
		// Compute each polygon side, compute all floans based upon gravity
		//////
			for (lcdp->lnI = 0; lcdp->lnI < poly->lineCount; lcdp->lnI++)
			{
				// Compute this polyline
				lcdp->lpl = poly->line[lcdp->lnI];
				iivvm_canvasPolygon_computeLine(tsDst, lcdp);
			}


		//////////
		// Compute the corners and fillers
		//////
			iivvm_canvasPolygon_getCornerFloans(lcdp);
			iivvm_canvasPolygon_getRangeFloans(tsDst, poly, lcdp);


		//////////
		// When we get here, the polygon has been outlined.  All floans are present
		//////
			lcdp->lnPixelsDrawn += (poly->pixelFloans->populatedLength / sizeof(SBGRACompute));
	}

	void iivvm_canvasPolygon_draw(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color, _isSCanvasDrawPolygonParameters* lcdp)
	{
		//////////
		// If they want us to actually draw something, then draw it, otherwise we just store it
		//////
			if (tsDst && bd)
			{
				// Grab our constants
				lcdp->alpc	= (f64)color.alp / 255.0;
				lcdp->lfRed	= (f64)color.red;
				lcdp->lfGrn = (f64)color.grn;
				lcdp->lfBlu = (f64)color.blu;

				// Reset our pixels drawn value
				lcdp->lnPixelsDrawn = 0;

				// Physically draw the polygon
				iivvm_canvasPolygon_drawPixelFloans(tsDst, bd, poly, lcdp);			// Draw the pixel floans
				iivvm_canvasPolygon_drawRangeFloans(bd, poly, lcdp);					// Draw the range floans
			}
	}

	void iivvm_canvasPolygon_computeLine(SCanvas* tsDst, _isSCanvasDrawPolygonParameters* lcdp)
	{
		//////////
		// Compute deltas, slope, theta and gravity
		//////
			lcdp->lfDeltaX				= lcdp->lpl->end.x - lcdp->lpl->start.x;
			lcdp->lfDeltaY				= lcdp->lpl->end.y - lcdp->lpl->start.y;
			lcdp->lfLength				= sqrt(lcdp->lfDeltaX*lcdp->lfDeltaX + lcdp->lfDeltaY*lcdp->lfDeltaY);
			lcdp->llLeft				= (((lcdp->lpl->gravity.y - lcdp->lpl->start.y) * (lcdp->lpl->end.x - lcdp->lpl->start.x)) > ((lcdp->lpl->gravity.x - lcdp->lpl->start.x) * (lcdp->lpl->end.y - lcdp->lpl->start.y)));
			// Note:  llLeft is taken from the algorithm: ((y - starty) * (endx - startx) > (x - startx) * (endy - starty))
			// Note:  It is basically the shortened form of the algorithm whereby you rotate everything around so start (X,Y) is at (0,0), and then rotate theta around to 0, then examine if the gravity point is above or below the Y axis

			// Store the passed parameter values
			lcdp->sfld.end.x			= (s32)lcdp->lpl->end.x;
			lcdp->sfld.end.y			= (s32)lcdp->lpl->end.y;
			lcdp->sfld.m				= lcdp->lfDeltaY / ((lcdp->lfDeltaX == 0.0) ? 0.0000000000001 : lcdp->lfDeltaX);
			lcdp->sfld.theta			= iivvm_math_adjustTheta(atan2(lcdp->lfDeltaY, lcdp->lfDeltaX));
			lcdp->sfld.gravityDecorated	= iivvm_math_getGravityOfThetaAndLeft(lcdp->sfld.theta, lcdp->llLeft);
			lcdp->sfld.gravity07		= iivvm_math_getGravity07FromDecoratedGravity(lcdp->sfld.gravityDecorated);


		//////////
		// Begin where we are starting, and move to the next axis, and then use that as our starting point
		//////
			lcdp->sfld.p1.x				 = lcdp->lpl->start.x;
			lcdp->sfld.p1.y				 = lcdp->lpl->start.y;
			lcdp->sfld.p2.x				 = lcdp->lpl->start.x;
			lcdp->sfld.p2.y				 = lcdp->lpl->start.y;
			lcdp->sfld.po.x				 = (s32)lcdp->sfld.p1.x;
			lcdp->sfld.po.y				 = (s32)lcdp->sfld.p1.y;
			iivvm_math_getNextAxisInterceptXY(&lcdp->sfld.p2, lcdp->sfld.theta);

		
		//////////
		// Store the starting floan, and move to the first whole pixel start
		//////
			iivvm_canvasPolygon_storeCorner(lcdp->corners, &lcdp->lpl->start, &lcdp->sfld.p2, &lcdp->sfld);


		//////////
		// Compute each middle floans
		//////
			do {

				//////////
				// Move forward to the next pixel
				//////
					lcdp->sfld.p1.x		= lcdp->sfld.p2.x;
					lcdp->sfld.p1.y		= lcdp->sfld.p2.y;


				//////////
				// We have P1 above, now find out where P2 will go (what axis it will hit next)
				//////
					// Find out where it will hit next
					iivvm_math_getNextAxisInterceptXY(&lcdp->sfld.p2, lcdp->sfld.theta);

					// Store the actual pixel coordinate based on the midpoint's integer base
					lcdp->sfld.po.x		= (s32)((lcdp->sfld.p1.x + lcdp->sfld.p2.x) / 2.0);
					lcdp->sfld.po.y		= (s32)((lcdp->sfld.p1.y + lcdp->sfld.p2.y) / 2.0);
					lcdp->sfld.offset	= (lcdp->sfld.po.y * tsDst->width) + lcdp->sfld.po.x;


				//////////
				// Make sure we're not already done
				//////
					if (lcdp->sfld.po.x == lcdp->sfld.end.x && lcdp->sfld.po.y == lcdp->sfld.end.y)
						break;		// We're done, this pixel is the last part of the line, so we just store the corner


				//////////
				// Store this pixel's floans
				//////
					iivvm_canvasPolygon_storeFloans(&lcdp->sfld);

			} while (1);


		//////////
		// Store the ending floan
		//////
			// Recompute the ending floan just in case there was "jitter" in the last two iterations
			lcdp->sfld.p2.x		= lcdp->lpl->end.x;
			lcdp->sfld.p2.y		= lcdp->lpl->end.y;
			lcdp->sfld.po.x		= (s32)lcdp->sfld.p2.x;
			lcdp->sfld.po.y		= (s32)lcdp->sfld.p2.y;
			iivvm_math_getNextAxisInterceptXY(&lcdp->sfld.p2, iivvm_math_adjustTheta(lcdp->sfld.theta + _PI));

			// Store it
			iivvm_canvasPolygon_storeCorner(lcdp->corners, &lcdp->lpl->end, &lcdp->sfld.p2, &lcdp->sfld);
	}

	void iivvm_canvasPolygon_getCornerFloans(_isSCanvasDrawPolygonParameters* lcdp)
	{
		//////////
		// Now we need to connect all corners that are connected. If a corner is
		// self-terminating (as of an incomplete polygon), we just leave it.  This
		// algorithm only looks at pairs of corners.  If multiple lines converge on
		// a single corner, they will be found one by one and added to any prior
		// floan that was already put at that position.  These will be summed up in
		// the algorithm below which removes redundant floans.
		//////
			for (lcdp->lnI = 0; lcdp->lnI < lcdp->corners->populatedLength; lcdp->lnI += sizeof(_isSStoreFloan_cornerData))
			{
				// Grab this root location of this corner
				lcdp->sfcdRoot = (_isSStoreFloan_cornerData*)(lcdp->corners->data + lcdp->lnI);

				// Try to connect to all others
				for (lcdp->lnJ = lcdp->lnI + sizeof(_isSStoreFloan_cornerData); lcdp->lnJ < lcdp->corners->populatedLength; lcdp->lnJ += sizeof(_isSStoreFloan_cornerData))
				{
					// Grab the location of this corner
					lcdp->sfcd = (_isSStoreFloan_cornerData*)(lcdp->corners->data + lcdp->lnJ);

					// If it's at the same coordinate as the previous corner, it's a match
					if (lcdp->sfcdRoot->po.x == lcdp->sfcd->po.x && lcdp->sfcdRoot->po.y == lcdp->sfcd->po.y)
					{
						// This is a match
						// Grab all the points for this pixel
						iivvm_canvasPolygon_storeFloansCorner(&lcdp->sfld, lcdp->sfcdRoot, lcdp->sfcd);
						break;
					}
				}
			}
	}

	void iivvm_canvasPolygon_getRangeFloans(SCanvas* tsDst, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp)
	{
			lcdp->lnFloanCount = poly->pixelFloans->populatedLength / sizeof(SBGRACompute);
			qsort(poly->pixelFloans->data, (size_t)lcdp->lnFloanCount, sizeof(SBGRACompute), iivvm_canvasPolygon_qsortFloansCallback);

			// Iterate through each block and grab horizontal line runs in blocks
			// Note:  At each horizontal stop there may be one or more pixels side-by-side.
			//        If they exist in this way, that grouping is considered to be a single
			//        group, and the line data will begin beyond it.
			for (lcdp->lnI = 0; lcdp->lnI < lcdp->lnFloanCount; lcdp->lnI = lcdp->lnINext)
			{
				// Grab the next set of line entries for this block
				lcdp->lnINext = iivvm_canvasPolygon_getNextLineSegment(lcdp->lnI, lcdp->lnFloanCount, (SBGRACompute*)poly->pixelFloans->data, &lcdp->sbgrac1, &lcdp->sbgrac2);

				// Are we still valid?
				if (lcdp->lnINext < lcdp->lnFloanCount)
				{
					//////////
					// Allocate space for the line segment entry
					//////
						if (lcdp->sbgrac1->x + 1 != lcdp->sbgrac2->x - 1)
						{
							// It is a range exceeding one pixel in length, so we add it as a range
							lcdp->sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(poly->rangeFloans, sizeof(SBGRACompute));
							if (lcdp->sbgrac)
							{
								// Store the from and to locations
								lcdp->sbgrac->start		= (lcdp->sbgrac1->y * tsDst->width) + lcdp->sbgrac1->x + 1;
								lcdp->sbgrac->end		= (lcdp->sbgrac2->y * tsDst->width) + lcdp->sbgrac2->x - 1;
								lcdp->sbgrac->alpha		= 1.0;
								lcdp->lnPixelsDrawn		= lcdp->sbgrac2->x - lcdp->sbgrac1->x;
							}

						} else {
							// It is only a single pixel, we we simply add it as another pixel floan
							lcdp->sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(poly->pixelFloans, sizeof(SBGRACompute));
							if (lcdp->sbgrac)
							{
								// Store the from and to locations
								lcdp->sbgrac->x		= lcdp->sbgrac1->x + 1;
								lcdp->sbgrac->y		= lcdp->sbgrac1->y;
								lcdp->sbgrac->alpha	= 1.0;
								++lcdp->lnPixelsDrawn;
							}
						}
				}
			}
	}


	void iivvm_canvasPolygon_drawPixelFloans(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp)
	{
		// Iterate through every floan, drawing it one by one
		for (lcdp->lnI = 0; lcdp->lnI < poly->pixelFloans->populatedLength; lcdp->lnI += sizeof(SBGRACompute))
		{
			// Grab this entry
			lcdp->sbgrac		= (SBGRACompute*)(poly->pixelFloans->data + lcdp->lnI);

			// Grab alpha and 1.0-alpha for this floan
			lcdp->alp			= lcdp->sbgrac->alpha * lcdp->alpc;
			lcdp->malp			= (1.0 - lcdp->alp);

			// Populate this color into the target canvas
			lcdp->sbgra			= bd + (lcdp->sbgrac->y * tsDst->width) + lcdp->sbgrac->x;
			lcdp->sbgra->red	= (s8)min((s32)((lcdp->sbgra->red * lcdp->malp) + (lcdp->lfRed * lcdp->alp)), 255);
			lcdp->sbgra->grn	= (s8)min((s32)((lcdp->sbgra->grn * lcdp->malp) + (lcdp->lfGrn * lcdp->alp)), 255);
			lcdp->sbgra->blu	= (s8)min((s32)((lcdp->sbgra->blu * lcdp->malp) + (lcdp->lfBlu * lcdp->alp)), 255);

			// Increase our pixel drawn count
			++lcdp->lnPixelsDrawn;
		}
	}

	void iivvm_canvasPolygon_drawRangeFloans(SBGRA* bd, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp)
	{
		for (lcdp->lnI = 0; lcdp->lnI < poly->rangeFloans->populatedLength; lcdp->lnI += sizeof(SBGRACompute))
		{
			// Grab this entry
			lcdp->sbgrac	= (SBGRACompute*)(poly->rangeFloans->data + lcdp->lnI);

			// Grab alpha and 1.0-alpha for this floan
			lcdp->alp		= lcdp->sbgrac->alpha * lcdp->alpc;
			lcdp->malp	= (1.0 - lcdp->alp);

			// Populate this color into the target canvas for the range
			lcdp->sbgra	= bd + lcdp->sbgrac->start;
			for (lcdp->lnJ = lcdp->sbgrac->start; lcdp->lnJ <= lcdp->sbgrac->end; lcdp->lnJ++, lcdp->sbgra++)
			{
				// Populate the color
				lcdp->sbgra->red	= (s8)min((s32)((lcdp->sbgra->red * lcdp->malp) + (lcdp->lfRed * lcdp->alp)), 255);
				lcdp->sbgra->grn	= (s8)min((s32)((lcdp->sbgra->grn * lcdp->malp) + (lcdp->lfGrn * lcdp->alp)), 255);
				lcdp->sbgra->blu	= (s8)min((s32)((lcdp->sbgra->blu * lcdp->malp) + (lcdp->lfBlu * lcdp->alp)), 255);

				// Increase our pixel drawn count
				++lcdp->lnPixelsDrawn;
			}
		}
	}





//////////
//
// Returns true or false if this polygon is small (average extent is less than two pixels, or
// if there are any segments which are less than one pixel)
//
//////
	bool iivvm_canvasPolygon_determineIfSmall(SPolygon* poly)
	{
		u32			lnI;
		SLineF64	line;
		f64			lfLength;


		if (poly)
		{
			// If any lines are less than one pixel, or if the average line length is less than
			// two pixels, then it is considered short
			lfLength = 0.0;
			for (lnI = 0; lnI < poly->lineCount; lnI++)
			{
				// Set our points
				memcpy(&line.start,		&(poly->line[lnI])->start,		sizeof(SXYF64));
				memcpy(&line.end,		&(poly->line[lnI])->end,		sizeof(SXYF64));

				// Compute the line
				vvm_math_computeLine(&line);


				//////////
				// Is it less than one pixel
				// If yes, then small polygon
				//////
					if (line.length < 1.0)
						return(true);	// Yes


				// Add it to our running total
				lfLength += line.length;
			}

			//////////
			// Is the average less than two pixels?
			// If yes, then small polygon
			//////
				if (lfLength / (f64)poly->lineCount < 2.0)
					return(true);		// Yes


			//////////
			// If we get here, it's not a small polygon
			//////
				return(false);

		} else {
			// Invalid
			return(false);
		}
	}




//////////
//
// QSORT() callback, orders data by Y ascending, then by X ascending.  This is crucial for the
// rangeFloan and floan merging algorithms.
//
//////
	int iivvm_canvasPolygon_qsortFloansCallback(const void* l, const void* r)
	{
		SBGRACompute*        left;
		SBGRACompute*        right;


		// Get our pointers properly
		left		= (SBGRACompute*)l;
		right		= (SBGRACompute*)r;

		// See how the cookie crumbles
		     if (left->y < right->y)		return(-1);							// Left is less than right
		else if (left->y > right->y)		return(1);							// Left is greater than right
		else								return(left->x - right->x);			// If left is less, return will be negative, otherwise equal or greater than
	}




//////////
//
// Grabs the next line segment as processing through the floans.
//
//////
	u32 iivvm_canvasPolygon_getNextLineSegment(u32 tnIndex, u32 tnMaxCount, SBGRACompute* sbgracRoot, SBGRACompute** p1, SBGRACompute** p2)
	{
		u32				lnSkip;
		SBGRACompute*	sbgrac;


		// While the pixels are adjacent, move forward
		sbgrac = sbgracRoot + tnIndex;
		for (lnSkip = 1; tnIndex + lnSkip < tnMaxCount; lnSkip++)
		{
			//////////
			// Are we still on the same row?
			//////
				if ((sbgrac + lnSkip)->y != (sbgrac + lnSkip - 1)->y)
				{
					// We've passed to another row, we begin again, but from here
					return(iivvm_canvasPolygon_getNextLineSegment(tnIndex + lnSkip, tnMaxCount, sbgracRoot, p1, p2));
				}


			//////////
			// Are the pixels not adjacent?
			//////
				if ((sbgrac + lnSkip)->x != (sbgrac + lnSkip - 1)->x + 1)
					break;		// Yes, they are not adjacent.  We've found the end of the grouping/run.
			

			// If we get here, we keep going because we're still on a side-by-side pixel grouping
		}

		// When we get here, we have found two pixels
		*p1 = (sbgrac + lnSkip - 1);		// Last pixel in the left-side grouping
		*p2 = (sbgrac + lnSkip);			// First pixel of the right-side grouping

		// Indicate how far we moved
		return(tnIndex + lnSkip + 1);
	}




//////////
//
// Called to store the corner point.  This is used for final assembly after all corners and floans
// are computed.  The corner floans are then computed based on overlay information.
//
// Note (from code in iioss_canvasPolygon()): SBuilder* corners; // SXYF64 indicating where the corner falls
//
//////
	void iivvm_canvasPolygon_storeCorner(SBuilder* corners, SXYF64* po, SXYF64* pi, _isSStoreFloan_lineData* sfld)
	{
		_isSStoreFloan_cornerData lsfcd;


		//////////
		// Copy to our temporary buffer
		//////

			// Corner point
			lsfcd.po.x = po->x;
			lsfcd.po.y = po->y;

			// Intercept point
			lsfcd.pi.x = pi->x;
			lsfcd.pi.y = pi->y;

			// Line data
			memcpy(&lsfcd.lineData, sfld, sizeof(_isSStoreFloan_lineData));


		//////////
		// Append it
		//////
			vvm_builderAppendData(corners, (s8*)&lsfcd, sizeof(lsfcd));
	}




/////////
//
// Called to store all of the triangles required to make up this floan.
// There are 8 parts where a line can intersect with, thereby bisecting a pixel:
//        2__3__4
//        1     5
//        0__7__6
//
//	From those locations, pixels can run in up to 20 combinations (disregarding direction):
//		0..6, 0..5, 0..4, 0..3, 0..2
//		1..3, 1..4, 1..5, 1..6, 1..7
//		2..4, 2..5, 2..6, 2..7
//		3..5, 3..6, 3..7
//		4..6, 4..7
//		5..7
//
// Given the gravity direction, this then determines how the area is computed for the partial
// pixel which intersects in one of the 20 ways, resulting in 40 total gravity formulas. :-)
//
// Yes, I did this all manually.  And yes, I hope there's an easier and better way to do it
// that someone will show me because I really hated doing this.  It took me almost three weeks
// (during the midst of two weeks of insomnia anyway, which I'm sure was the biggest cause of
// the three week time frame). :-)
//
// (tfX,tfY) is the corner closest toward the origin of the current pixel.
// (tfX1,tfY1) is any point on any of the 8 parts
// (tfX2,tfY2) is any other point on any of the 8 parts
//
//////
	_isS_iioss_canvasPolygon_storeFloans shortcuts[64] = 
	{
		// The naming convention here is the FROM:TO or the corresponding TO:FROM indicator so as to reduce duplication
		(u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_2_0, (u32)&storeFloan_pointToPoint_3_0, (u32)&storeFloan_pointToPoint_4_0, (u32)&storeFloan_pointToPoint_5_0, (u32)&storeFloan_pointToPoint_6_0, (u32)&storeFloan_pointToPoint_bad,
		(u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_3_1, (u32)&storeFloan_pointToPoint_4_1, (u32)&storeFloan_pointToPoint_5_1, (u32)&storeFloan_pointToPoint_6_1, (u32)&storeFloan_pointToPoint_7_1,
		(u32)&storeFloan_pointToPoint_0_2, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_4_2, (u32)&storeFloan_pointToPoint_5_2, (u32)&storeFloan_pointToPoint_6_2, (u32)&storeFloan_pointToPoint_7_2,
		(u32)&storeFloan_pointToPoint_0_3, (u32)&storeFloan_pointToPoint_1_3, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_5_3, (u32)&storeFloan_pointToPoint_6_3, (u32)&storeFloan_pointToPoint_7_3,
		(u32)&storeFloan_pointToPoint_0_4, (u32)&storeFloan_pointToPoint_1_4, (u32)&storeFloan_pointToPoint_2_4, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_6_4, (u32)&storeFloan_pointToPoint_7_4,
		(u32)&storeFloan_pointToPoint_0_5, (u32)&storeFloan_pointToPoint_1_5, (u32)&storeFloan_pointToPoint_2_5, (u32)&storeFloan_pointToPoint_3_5, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_7_5,
		(u32)&storeFloan_pointToPoint_0_6, (u32)&storeFloan_pointToPoint_1_6, (u32)&storeFloan_pointToPoint_2_6, (u32)&storeFloan_pointToPoint_3_6, (u32)&storeFloan_pointToPoint_4_6, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad,
		(u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_1_7, (u32)&storeFloan_pointToPoint_2_7, (u32)&storeFloan_pointToPoint_3_7, (u32)&storeFloan_pointToPoint_4_7, (u32)&storeFloan_pointToPoint_5_7, (u32)&storeFloan_pointToPoint_bad, (u32)&storeFloan_pointToPoint_bad
	};

	void iivvm_canvasPolygon_storeFloans(_isSStoreFloan_lineData* sfld)
	{
		u32 lnOperation;
		s32 lnGravityFrom, lnGravityTo;


		// Make sure we will be drawing on a canvas
		if (sfld->p1.x < 0 || sfld->p1.y < 0 || sfld->p2.x < 0 || sfld->p2.y < 0)
			return;		// This floan extends into invisible areas


		//////////
		// Grab the gravity points for this intersection
		//////
			lnGravityFrom	= iivvm_math_getGravityByRelativePosition(&sfld->p1, &sfld->po);
			lnGravityTo		= iivvm_math_getGravityByRelativePosition(&sfld->p2, &sfld->po);


		//////////
		// Dispatch the operation, from which point to which point
		//////
			if (lnGravityFrom >= 0 && lnGravityTo >= 0)
			{
				lnOperation	= ((u32)lnGravityTo << 3) | (u32)lnGravityFrom;
				shortcuts[lnOperation].storeFloan_pointToPoint(sfld);
			}
	}

	void iivvm_canvasPolygon_storeFloansCorner(_isSStoreFloan_lineData* sfld, _isSStoreFloan_cornerData* sfcd1, _isSStoreFloan_cornerData* sfcd2)
	{
		s32							lnGravity1i, lnGravity2i;
		f64							lfArea;
		SXYS32						poBase1, poBase2;
		SBGRACompute*				sbgrac;


		//////////
		// Get the integer-based position of the corner point (where they intersect)
		// It is the same for sfcd1 and sfcd2, as they intersect at some fraction within.
		//////
			poBase1.x = (s32)sfcd1->po.x;
			poBase1.y = (s32)sfcd1->po.y;
			poBase2.x = (s32)sfcd2->po.x;
			poBase2.y = (s32)sfcd2->po.y;


		//////////
		// Grab their gravities
		//////
			lnGravity1i		= iivvm_math_getGravityByRelativePosition(&sfcd1->pi, &poBase1);
			lnGravity2i		= iivvm_math_getGravityByRelativePosition(&sfcd2->pi, &poBase2);


		//////////
		// Compute their floan based on gravity of the first line, and use its points for the area
		// Note:  We assume these two sides have gravities facing toward each other, so we only need one
		//////
			lfArea = iivvm_math_getAreaOfSquareUsing_po_p1_p2(sfcd1->lineData.gravity07, lnGravity1i, lnGravity2i, &sfcd1->po, &sfcd1->pi, &sfcd2->pi);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x		= poBase1.x;
				sbgrac->y		= poBase1.y;
				sbgrac->alpha	= lfArea;
			}
	}




//////////
//
// Called to determine if we should go around the pixel clockwise, or counter-clockwise, based on gravity
//
//      NW __N__ NE     2__3__4
//      W |     |E      1     5
//      SW|__S__|SE     0__7__6
//
//////
	f64 iivvm_math_getAreaOfSquareUsing_po_p1_p2(s32 tnGravity07_po, s32 tnGravity07_p1, s32 tnGravity07_p2, SXYF64* po, SXYF64* p1, SXYF64* p2)
	{
		STriangleF64	tri1, tri2, tri3;
		bool			llTwoTriangles, llThreeTriangles;
		bool			llOneMinusArea;


		//////////
		// For most computations, we compute the triangle po..p1..p2, and then either use
		// that area, or (1.0 - area).	For some computations we need two triangles.
		//////
			// We assume the small triangle
			llOneMinusArea		= false;

			// We assume one triangle to begin with, and then adjust as needed
			llTwoTriangles		= false;
			llThreeTriangles	= false;

			// Triangle p1..p2..po
			memcpy(&tri1.p1, p1, sizeof(SXYF64));
			memcpy(&tri1.p2, p2, sizeof(SXYF64));
			memcpy(&tri1.p3, po, sizeof(SXYF64));


		// See where we're going from and to
		switch (tnGravity07_p1)
		{
			case 0:
				//		NW __N__ NE		2__3__4
				//		W |		|E		1	  5
				//		SW|__S__|SE		0__7__6
				//
				switch (tnGravity07_p2)
				{
					case 1:		// Runs from SW to W
						if (!(tnGravity07_po == 0 || tnGravity07_po == 1))	llOneMinusArea = true;		// Fills in from 0..7..6..5..4..3..2..1
						// else																			// Fills in from 0..1
						break;

					case 2:		// Runs from SW to NW
						if (tnGravity07_po >= 3 && tnGravity07_po <= 7)		llOneMinusArea = true;		// Fills in from 0..7..6..5..4..3..2
						// else																			// Fills in from 0..1..2
						break;

					case 3:		// Runs from SW to N
						//////////
						// This will require two triangles:
						//		(1) p1..2..po
						//		(2) 2..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..2..po
							//tri1.p1										// p1
							tri1.p2.x = p1->x;								// 2
							tri1.p2.y = p2->y;
							//tri1.p3										// po

							// Make triangle two be 2..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 2
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2

						// Indicate if we need the area, or 1.0-area
						if (tnGravity07_po >= 4 && tnGravity07_po <= 7)		llOneMinusArea = true;		// Fills in from 0..7..6..5..4..3
						// else																			// Fills in from 0..1..2..3
						break;

					case 4:		// Runs from SW to NE
						// This is a constant, it's always 0.5 (half the pixel)
						 return(0.5);

					case 5:		// Runs from SW to E
						//////////
						// This will require two triangles:
						//		(1) p1..6..po
						//		(2) 6..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..6..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 6
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 6..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 6
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2

						// Indicate if we need the area, or 1.0-area
						if (!(tnGravity07_po >= 6 && tnGravity07_po <= 7))	llOneMinusArea = true;		// Fills in from 0..1..2..3..4..5
						// else																			// Fills in from 0..7..6..5
						break;

					case 6:		// Runs from SW to SE
						if (tnGravity07_po >= 1 && tnGravity07_po <= 5)		llOneMinusArea = true;		// Fills in from 0..1..2..3..4..5..6
						// else																			// Fills in from 0..7..6
						break;

					case 7:		// Runs from SW to S
						if (!(tnGravity07_po == 0 || tnGravity07_po == 7))	llOneMinusArea = true;		// Fills in from 0..1..2..3..4..5..6..7
						// else																			// Fills in from 0..7
						break;

					default:
						// This should never happen.  It means tnGravity07_p1 is not 0..7, but something else
						_asm int 3;
						return false;
				}
				break;

			case 1:
				//		NW __N__ NE		2__3__4
				//		W |		|E		1	  5
				//		SW|__S__|SE		0__7__6
				//
				switch (tnGravity07_p2)
				{
					case 0:		// Runs from W to SW
						if (!(tnGravity07_po == 0 || tnGravity07_po == 1))	llOneMinusArea = true;		// Fills in from 1..2..3..4..5..6..7..0
						// else																			// Fills in from 1..0
						break;

					case 1:		// Runs from W to W
						if (!(tnGravity07_po == 1))						llOneMinusArea = true;			// Fills in from 1..2..3..4..5..6..7..0..1
						// else																			// Fills in from 1..1
						break;

					case 2:		// Runs from W to NW
						if (!(tnGravity07_po == 1 || tnGravity07_po == 2))	llOneMinusArea = true;		// Fills in from 1..0..7..6..5..4..3..2
						// else																			// Fills in from 1..2
						break;

					case 3:		// Runs from W to N
						//////////
						// This will require two triangles:
						//		(1) p1..2..po
						//		(2) 2..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..2..po
							//tri1.p1										// p1
							tri1.p2.x = p1->x;								// 2
							tri1.p2.y = p2->y;
							//tri1.p3										// po

							// Make triangle two be 2..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 2
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (tnGravity07_po == 0 || tnGravity07_po >= 4)		llOneMinusArea = true;		// Fills in from 1..0..7..6..5..4..3
							// else																			// Fills in from 1..2..3
							break;

					case 4:		// Runs from W to NE
						//////////
						// This will require two triangles:
						//		(1) p1..2..po
						//		(2) 2..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..2..po
							//tri1.p1										// p1
							tri1.p2.x = p1->x;								// 2
							tri1.p2.y = p2->y;
							//tri1.p3										// po

							// Make triangle two be 2..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 2
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (tnGravity07_po == 0 || tnGravity07_po >= 5)		llOneMinusArea = true;		// Fills in from 1..0..7..6..5..4
							// else																			// Fills in from 1..2..3..4
							break;

					case 5:		// Runs from W to E
						//////////
						// This will require three triangles:
						//		(1) p1..2..po
						//		(2) 2..po..4
						//		(3) 4..po..p2
						//////
							llThreeTriangles = true;

							// Modify triangle one to be p1..2..po
							// tri.p1												// p1
							tri1.p2.x = tri1.p1.x;									// 2
							tri1.p2.y = (f64)((s32)p1->y + 1);
							// tri.p3												// po

							// Make triangle two be 2..po..4
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));			// 2
							memcpy(&tri2.p2, po,		sizeof(SXYF64));			// po
							tri2.p3.x = p2->x;										// 4
							tri2.p3.y = tri1.p2.y;

							// Make triangle three be 4..po..p2
							memcpy(&tri3.p1, &tri2.p3,	sizeof(SXYF64));			// 4
							memcpy(&tri2.p2, po,		sizeof(SXYF64));			// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));			// p2


						//////////
						// See which way the line is going
						//////
							if (p1->y < p2->y)
							{
								// Line slants / up
								if (!(tnGravity07_po >= 1 && tnGravity07_po < 5))		llOneMinusArea = true;		// Fills in from 1..2..3..4..5
								// else																				// Fills in from 1..0..7..6..5

							} else {
								// Line slants \ down
								if (!(tnGravity07_po > 1 && tnGravity07_po <= 5))		llOneMinusArea = true;		// Fills in from 1..2..3..4..5
								// else																				// Fills in from 1..0..7..6..5
							}
							break;

					case 6:		// Runs from W to SE
						//////////
						// This will require two triangles:
						//		(1) p1..0..po
						//		(2) 0..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..0..po
							//tri1.p1										// p1
							tri1.p2.x = p1->x;								// 0
							tri1.p2.y = p2->y;
							//tri1.p3										// po

							// Make triangle two be 0..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 0
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (!(tnGravity07_po == 0 || tnGravity07_po >= 7))		llOneMinusArea = true;		// Fills in from 1..0..7..6
							// else																				// Fills in from 1..2..3..4..5..6
							break;

					case 7:		// Runs from W to S
						//////////
						// This will require two triangles:
						//		(1) p1..0..po
						//		(2) 0..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..0..po
							//tri1.p1										// p1
							tri1.p2.x = p1->x;								// 0
							tri1.p2.y = p2->y;
							//tri1.p3										// po

							// Make triangle two be 0..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 0
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (!(tnGravity07_po <= 1 || tnGravity07_po >= 7))	llOneMinusArea = true;		// Fills in from 1..2..3..4..5..6..7
							// else																			// Fills in from 1..0..7
							break;

					default:
						// This should never happen.  It means tnGravity07_p1 is not 0..7, but something else
						_asm int 3;
						return false;
				}
				break;

			case 2:
				//		NW __N__ NE		2__3__4
				//		W |		|E		1	  5
				//		SW|__S__|SE		0__7__6
				//
				switch (tnGravity07_p2)
				{
					case 0:		// Runs from NW to SW
						if (tnGravity07_po >= 3)							llOneMinusArea = true;		// Fills in from 2..3..4..5..6..7..0
						// else																			// Fills in from 2..1..0
						break;

					case 1:		// Runs from NW to W
						if (!(tnGravity07_po == 2 || tnGravity07_po == 1))	llOneMinusArea = true;		// Fills in from 2..3..4..5..6..7..0..1
						// else																			// Fills in from 2..1
						break;

					case 3:		// Runs from NW to N
						if (!(tnGravity07_po == 2 || tnGravity07_po == 3))	llOneMinusArea = true;		// Fills in from 2..1..0..7..6..5..4..3
						// else																			// Fills in from 2..3
						break;

					case 4:		// Runs from NW to NE
						if (tnGravity07_po <= 1 || tnGravity07_po >= 5)		llOneMinusArea = true;		// Fills in from 2..1..0..7..6..5..4
						// else																			// Fills in from 2..3..4
						break;

					case 5:		// Runs from NW to E
						//////////
						// This will require two triangles:
						//		(1) p1..4..po
						//		(2) 4..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..4..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 4
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 4..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 4
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (!(tnGravity07_po >= 3 && tnGravity07_po <= 5))	llOneMinusArea = true;		// Fills in from 2..1..0..7..6..5
							// else																			// Fills in from 2..3..4..5
							break;

					case 6:		// Runs from NW to SE
						// This is a constant, it's always 0.5 (half the pixel)
						return(0.5);

					case 7:		// Runs from NW to S
						//////////
						// This will require two triangles:
						//		(1) p1..0..po
						//		(2) 0..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..0..po
							//tri1.p1										// p1
							tri1.p2.x = p1->x;								// 0
							tri1.p2.y = p2->y;
							//tri1.p3										// po

							// Make triangle two be 0..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 0
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (!(tnGravity07_po <= 1))						llOneMinusArea = true;		// Fills in from 2..1..0..7
							// else																		// Fills in from 2..3..4..5..6..7
							break;

					default:
						// This should never happen.  It means tnGravity07_p1 is not 0..7, but something else
						_asm int 3;
						return false;
				}
				break;

			case 3:
				//		NW __N__ NE		2__3__4
				//		W |		|E		1	  5
				//		SW|__S__|SE		0__7__6
				//
				switch (tnGravity07_p2)
				{
					case 0:		// Runs from N to SW
						//////////
						// This will require two triangles:
						//		(1) p1..2..po
						//		(2) 2..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..2..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 2
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 2..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 2
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (tnGravity07_po >= 4)						llOneMinusArea = true;		// Fills in from 3..4..5..6..7..0
							// else																		// Fills in from 3..2..1..0
							break;

					case 1:		// Runs from N to W
						//////////
						// This will require two triangles:
						//		(1) p1..2..po
						//		(2) 2..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..2..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 2
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 2..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 2
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (tnGravity07_po == 0 || tnGravity07_po >= 4)		llOneMinusArea = true;		// Fills in from 3..4..5..6..7..0..1
							// else																			// Fills in from 3..2..1
							break;

					case 2:		// Runs from N to NW
						if (!(tnGravity07_po == 3 || tnGravity07_po == 2))	llOneMinusArea = true;			// Fills in from 3..4..5..6..7..0..1..2
						// else																				// Fills in from 3..2
						break;

					case 3:		// Runs from N to N
						if (!(tnGravity07_po == 3))						llOneMinusArea = true;				// Fills in from 3..4..5..6..7..0..1..2..3
						// else																				// Fills in from 3..3
						break;

					case 4:		// Runs from N to NE
						if (!(tnGravity07_po == 3 || tnGravity07_po == 4))	llOneMinusArea = true;			// Fills in from 3..2..1..0..7..6..5..4
						// else																				// Fills in from 3..4
						break;

					case 5:		// Runs from N to E
						//////////
						// This will require two triangles:
						//		(1) p1..4..po
						//		(2) 4..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..4..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 4
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 4..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 4
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (tnGravity07_po <= 2 || tnGravity07_po >= 6)		llOneMinusArea = true;		// Fills in from 3..2..1..0..7..6..5
							// else																			// Fills in from 3..4..5
							break;

					case 6:		// Runs from N to SE
						//////////
						// This will require two triangles:
						//		(1) p1..4..po
						//		(2) 4..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..4..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 4
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 4..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 4
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
						   if (tnGravity07_po <= 2 || tnGravity07_po >= 7)	llOneMinusArea = true;		// Fills in from 3..2..1..0..7..6
							// else																		// Fills in from 3..4..5..6
						   break;

					case 7:		// Runs from N to S
						//////////
						// We will process the left side.  It requires three triangles:
						//		(1) p1..2..po
						//		(2) 2..po..0
						//		(3) 0..po..p2
						//////
							llThreeTriangles = true;

							// Modify triangle one to be p1..2..po
							// tri.p1												// p1
							tri1.p2.x = (f64)((s32)p1->x);							// 2
							tri1.p2.y = p1->y;
							// tri.p3												// po

							// Make triangle two be 2..po..0
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));			// 2
							memcpy(&tri2.p2, po,		sizeof(SXYF64));			// po
							tri2.p3.x = tri1.p2.x;									// 0
							tri2.p3.y = p2->y;

							// Make triangle three be 2..po..p2
							memcpy(&tri3.p1, &tri2.p3,	sizeof(SXYF64));			// 0
							memcpy(&tri3.p2, po,		sizeof(SXYF64));			// po
							memcpy(&tri3.p3, p2,		sizeof(SXYF64));			// p2


						//////////
						// See which way the line is going
						//////
							if (p1->x < p2->x)
							{
								// Line slants \ down
								if (tnGravity07_po >= 3 || tnGravity07_po < 7)	llOneMinusArea = true;	// Fills in from 3..4..5..6..7
								// else																	// Fills in from 3..2..1..0..7

							} else {
								// Line slants / up
								if (tnGravity07_po > 3 || tnGravity07_po <= 7)	llOneMinusArea = true;	// Fills in from 3..4..5..6..7
								// else																	// Fills in from 3..2..1..0..7
							}
							break;

					default:
						// This should never happen.  It means tnGravity07_p1 is not 0..7, but something else
						_asm int 3;
						return false;
				}
				break;

			case 4:
				//		NW __N__ NE		2__3__4
				//		W |		|E		1	  5
				//		SW|__S__|SE		0__7__6
				//
				switch (tnGravity07_p2)
				{
					case 0:		// Runs from NE to SW
						// This is a constant, it's always 0.5 (half the pixel)
						return(0.5);

					case 1:		// Runs from NE to W
						//////////
						// This will require two triangles:
						//		(1) p1..2..po
						//		(2) 2..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..2..po
							//tri1.p1										// p1
							tri1.p2.x = p1->x;								// 2
							tri1.p2.y = p2->y;
							//tri1.p3										// po

							// Make triangle two be 2..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 2
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (tnGravity07_po == 0 || tnGravity07_po >= 5)		llOneMinusArea = true;		// Fills in from 4..5..6..7..0..1
							// else																			// Fills in from 4..3..2..1
							break;

					case 2:		// Runs from NE to NW
						if (tnGravity07_po <= 1 || tnGravity07_po >= 5)		llOneMinusArea = true;			// Fills in from 4..5..6..7..0..1..2
						// else																				// Fills in from 4..3..2
						break;

					case 3:		// Runs from NE to N
						if (!(tnGravity07_po == 4 || tnGravity07_po == 3))	llOneMinusArea = true;			// Fills in from 4..5..6..7..0..1..2..3
						// else																				// Fills in from 4..3
						break;

					case 5:		// Runs from NE to E
						if (!(tnGravity07_po == 4 || tnGravity07_po == 5))	llOneMinusArea = true;			// Fills in from 4..3..2..1..0..7..6..5
						// else																				// Fills in from 4..5
						break;

					case 6:		// Runs from NE to SE
						if (!(tnGravity07_po <= 3 || tnGravity07_po >= 7))	llOneMinusArea = true;			// Fills in from 4..3..2..1..0..7..6
						// else																				// Fills in from 4..5..6
						break;

					case 7:		// Runs from NE to S
						//////////
						// This will require two triangles:
						//		(1) p1..6..po
						//		(2) 6..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..6..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 6
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 6..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 6
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (tnGravity07_po <= 3)						llOneMinusArea = true;		// Fills in from 4..5..6..7
							// else																		// Fills in from 4..3..2..1..0..7
							break;

					default:
						// This should never happen.  It means tnGravity07_p1 is not 0..7, but something else
						_asm int 3;
						return false;
				}
				break;

			case 5:
				//		NW __N__ NE		2__3__4
				//		W |		|E		1	  5
				//		SW|__S__|SE		0__7__6
				//
				switch (tnGravity07_p2)
				{
					case 0:		// Runs from E to SW
						//////////
						// This will require two triangles:
						//		(1) p1..6..po
						//		(2) 6..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..6..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 6
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 6..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 6
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (!(tnGravity07_po >= 6))					llOneMinusArea = true;		// Fills in from 5..6..7..0
							// else																	// Fills in from 5..4..3..2..1..0
							break;

					case 1:		// Runs from E to W
						//////////
						// We will process the top side.  It requires three triangles:
						//		(1) p1..4..po
						//		(2) 4..po..2
						//		(3) 2..po..p2
						//////
							llThreeTriangles = true;

							// Modify triangle one to be p1..4..po
							// tri.p1												// p1
							tri1.p2.x = (f64)((s32)p1->x + 1);						// 4
							tri1.p2.y = (f64)((s32)p1->y + 1);
							// tri.p3												// po

							// Make triangle two be 4..po..2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));			// 4
							memcpy(&tri2.p2, po,		sizeof(SXYF64));			// po
							tri2.p3.x = p2->x;										// 2
							tri2.p3.y = tri1.p2.y;

							// Make triangle three be 2..po..p2
							memcpy(&tri3.p1, &tri2.p3,	sizeof(SXYF64));			// 2
							memcpy(&tri3.p2, po,		sizeof(SXYF64));			// po
							memcpy(&tri3.p3, p2,		sizeof(SXYF64));			// p2


						//////////
						// See which way the line is going
						//////
							if (p1->y < p2->y)
							{
								// Line slants \ down
								if (tnGravity07_po >= 1 || tnGravity07_po < 5)	llOneMinusArea = true;		// Fills in from 1..2..3..4..5
								// else																		// Fills in from 1..0..7..6..5

							} else {
								// Line slants / up
								if (tnGravity07_po > 1 || tnGravity07_po <= 5)	llOneMinusArea = true;		// Fills in from 1..2..3..4..5
								// else																		// Fills in from 1..0..7..6..5
							}
							break;

					case 2:		// Runs from E to NW
						//////////
						// This will require two triangles:
						//		(1) p1..4..po
						//		(2) 4..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..4..po
							//tri1.p1										// p1
							tri1.p2.x = p1->x;								// 4
							tri1.p2.y = p2->y;
							//tri1.p3										// po

							// Make triangle two be 4..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 4
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (!(tnGravity07_po >= 3 && tnGravity07_po <= 4))	llOneMinusArea = true;		// Fills in from 5..4..3..2
							// else																			// Fills in from 5..6..7..0..1..2
							break;

					case 3:		// Runs from E to N
						//////////
						// This will require two triangles:
						//		(1) p1..4..po
						//		(2) 4..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..4..po
							//tri1.p1										// p1
							tri1.p2.x = p1->x;								// 4
							tri1.p2.y = p2->y;
							//tri1.p3										// po

							// Make triangle two be 4..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 4
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (!(tnGravity07_po >= 3 && tnGravity07_po <= 5))	llOneMinusArea = true;		// Fills in from 5..6..7..0..1..2..3
							// else																			// Fills in from 5..4..3
							break;

					case 4:		// Runs from E to NE
						if (!(tnGravity07_po == 5 || tnGravity07_po == 4))	llOneMinusArea = true;			// Fills in from 5..6..7..0..1..2..3..4
						// else																				// Fills in from 5..4
						break;

					case 5:		// Runs from E to E
						if (!(tnGravity07_po == 5))						llOneMinusArea = true;				// Fills in from 5..6..7..0..1..2..3..4..5
						// else																				// Fills in from 5..5
						break;

					case 6:		// Runs from E to SE
						if (!(tnGravity07_po == 5 || tnGravity07_po == 6))	llOneMinusArea = true;			// Fills in from 5..4..3..2..1..0..7..6
						// else																				// Fills in from 5..6
						break;

					case 7:		// Runs from E to S
						//////////
						// This will require two triangles:
						//		(1) p1..6..po
						//		(2) 6..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..6..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 6
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 6..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 6
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (!(tnGravity07_po >= 5))						llOneMinusArea = true;		// Fills in from 5..4..3..2..1..0..7
							// else																		// Fills in from 5..6..7
							break;

					default:
						// This should never happen.  It means tnGravity07_p1 is not 0..7, but something else
						_asm int 3;
						return false;
				}
				break;

			case 6:
				//		NW __N__ NE		2__3__4
				//		W |		|E		1	  5
				//		SW|__S__|SE		0__7__6
				//
				switch (tnGravity07_p2)
				{
					case 0:		// Runs from SE to SW
						if (tnGravity07_po >= 1 && tnGravity07_po <= 5)		llOneMinusArea = true;		// Fills in from 6..5..4..3..2..1..0
						// else																			// Fills in from 6..7..0
						break;

					case 1:		// Runs from SE to W
						//////////
						// This will require two triangles:
						//		(1) p1..0..po
						//		(2) 0..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..0..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 0
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 0..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 0
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (tnGravity07_po >= 2 && tnGravity07_po <= 6)	llOneMinusArea = true;		// Fills in from 6..5..4..3..2..1
							// else																		// Fills in from 6..7..0..1
							break;

					case 2:		// Runs fro3 SE to NW
						// This is a constant, it's always 0.5 (half the pixel)
						return(0.5);

					case 3:		// Runs from SE to N
						//////////
						// This will require two triangles:
						//		(1) p1..4..po
						//		(2) 4..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..4..po
							//tri1.p1										// p1
							tri1.p2.x = p1->x;								// 4
							tri1.p2.y = p2->y;
							//tri1.p3										// po

							// Make triangle two be 4..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 4
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (!(tnGravity07_po >= 3 && tnGravity07_po <= 5))	llOneMinusArea = true;		// Fills in from 6..5..4..3
							// else																			// Fills in from 6..7..0..1..2..3
							break;

					case 4:		// Runs from SE to NE
						if (tnGravity07_po <= 3 || tnGravity07_po >= 7)		llOneMinusArea = true;			// Fills in from 6..7..0..1..2..3..4
						// else																				// Fills in from 6..5..4
						break;

					case 5:		// Runs from SE to E
						if (!(tnGravity07_po == 6 || tnGravity07_po == 5))	llOneMinusArea = true;			// Fills in from 6..7..0..1..2..3..4..5
						// else																				// Fills in from 6..5
						break;

					case 7:		// Runs from SE to S
						if (!(tnGravity07_po >= 6))						llOneMinusArea = true;				// Fills in from 6..5..4..3..2..1..0..7
						// else																				// Fills in from 6..7
						break;

					default:
						// This should never happen.  It means tnGravity07_p1 is not 0..7, but something else
						_asm int 3;
						return false;
				}
				break;

			case 7:
				//		NW __N__ NE		2__3__4
				//		W |		|E		1	  5
				//		SW|__S__|SE		0__7__6
				//
				switch (tnGravity07_p2)
				{
					case 0:		// Runs from S to SW
						if (!(tnGravity07_po == 0 || tnGravity07_po == 7))	llOneMinusArea = true;			// Fills in from 7..6..5..4..3..2..1..0
						// else																				// Fills in from 7..0
						break;

					case 1:		// Runs from S to W
						//////////
						// This will require two triangles:
						//		(1) p1..0..po
						//		(2) 0..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..0..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 0
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 0..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 6
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (tnGravity07_po <= 6 && tnGravity07_po >= 2)		llOneMinusArea = true;		// Fills in from 7..6..5..4..3..2..1
							// else																			// Fills in from 7..0..1
							break;

					case 2:		// Runs from S to NW
						//////////
						// This will require two triangles:
						//		(1) p1..0..po
						//		(2) 0..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..0..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 0
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 0..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 0
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (tnGravity07_po >= 3 && tnGravity07_po <=6)	llOneMinusArea = true;			// Fills in from 7..6..5..4..3..2
							// else																			// Fills in from 7..0..1..2
							break;

					case 3:		// Runs from S to N
						//////////
						// We will process the left side.  It requires three triangles:
						//		(1) p1..0..po
						//		(2) 0..po..2
						//		(3) 2..po..p2
						//////
							llThreeTriangles = true;

							// Modify triangle one to be p1..0..po
							// tri.p1												// p1
							tri1.p2.x = (f64)((s32)p1->x);							// 0
							tri1.p2.y = p1->y;
							// tri.p3												// po

							// Make triangle two be 0..po..2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));			// 0
							memcpy(&tri2.p2, po,		sizeof(SXYF64));			// po
							tri2.p3.x = tri1.p2.x;									// 2
							tri2.p3.y = p2->y;

							// Make triangle three be 2..po..p2
							memcpy(&tri3.p1, &tri2.p3,	sizeof(SXYF64));			// 2
							memcpy(&tri3.p2, po,		sizeof(SXYF64));			// po
							memcpy(&tri3.p3, p2,		sizeof(SXYF64));			// p2


						//////////
						// See which way the line is going
						//////
							if (p2->x < p1->x)
							{
								// Line slants \ down
								if (tnGravity07_po >= 3 || tnGravity07_po < 7)	llOneMinusArea = true;		// Fills in from 3..4..5..6..7
								// else																		// Fills in from 3..2..1..0..7

							} else {
								// Line slants / up
								if (tnGravity07_po > 3 || tnGravity07_po <= 7)	llOneMinusArea = true;		// Fills in from 3..4..5..6..7
								// else																		// Fills in from 3..2..1..0..7
							}
							break;

					case 4:		// Runs from S to NE
						//////////
						// This will require two triangles:
						//		(1) p1..6..po
						//		(2) 6..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..6..po
							//tri1.p1										// p1
							tri1.p2.x = p1->x;								// 6
							tri1.p2.y = p2->y;
							//tri1.p3										// po

							// Make triangle two be 6..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 6
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (tnGravity07_po <= 3)					llOneMinusArea = true;				// Fills in from 7..6..5..4
							// else																			// Fills in from 7..0..1..2..3..4
							break;

					case 5:		// Runs from S to E
						//////////
						// This will require two triangles:
						//		(1) p1..6..po
						//		(2) 6..po..p2
						//////
							llTwoTriangles = true;

							// Modify triangle one to be p1..6..po
							//tri1.p1										// p1
							tri1.p2.x = p2->x;								// 6
							tri1.p2.y = p1->y;
							//tri1.p3										// po

							// Make triangle two be 6..po..p2
							memcpy(&tri2.p1, &tri1.p2,	sizeof(SXYF64));	// 6
							memcpy(&tri2.p2, po,		sizeof(SXYF64));	// po
							memcpy(&tri2.p3, p2,		sizeof(SXYF64));	// p2


						//////////
						// Indicate if we need the area, or 1.0-area
						//////
							if (!(tnGravity07_po >= 5))					llOneMinusArea = true;				// Fills in from 7..0..1..2..3..4..5
							// else																			// Fills in from 7..6..5
							break;

					case 6:		// Runs from S to SE
						if (!(tnGravity07_po >= 6))						llOneMinusArea = true;				// Fills in from 7..0..1..2..3..4..5..6
						// else																				// Fills in from 7..6
						break;

					case 7:		// Runs from S to S
						if (!(tnGravity07_po == 7))						llOneMinusArea = true;				// Fills in from 7..6..5..4..3..2..1..0..7
						// else																				// Fills in from 7..7
						break;

					default:
						// This should never happen.  It means tnGravity07_p1 is not 0..7, but something else
						_asm int 3;
						return false;
				}
				break;

			default:
				// This should never happen.  It means tnGravity07_p1 is not 0..7, but something else
				_asm int 3;
				return false;
		}


		//////////
		// Ready to compute
		//////
			// Triangle 1
			iivvm_math_computeTriangle(&tri1);

			// Do we need two triangles?
			if (llTwoTriangles)
			{
				// Yes, add in the second triangle
				iivvm_math_computeTriangle(&tri2);
				tri1.area += tri2.area;
			}

			// Do we need three triangles?
			if (llThreeTriangles)
			{
				// Yes, add in the third triangle
				iivvm_math_computeTriangle(&tri3);
				tri1.area += tri3.area;
			}


		//////////
		// Ready to return our result
		//////
			if (llOneMinusArea)
			{
				// It's the opposite value
				return(1.0 - tri1.area);

			} else {
				// It's the value
				return(tri1.area);
			}
	}




/////////
//
// Called to move from the X or Y coordinate to the next x-intercept or y-intercept along theta
//
//////
	void iivvm_math_getNextAxisInterceptXY(SXYF64* p, f64 tfTheta)
	{
		f64		lfX, lfY, lfXLength, lfYLength, lfCosTheta, lfSinTheta;
		s32		lnX, lnY;


		//////////
		// Setup some common used constants
		//////
			lnX		= (s32)p->x;
			lnY		= (s32)p->y;
			lfX		= (f64)lnX;
			lfY		= (f64)lnY;


		//////////
		// Determine where the next intercepts are if it's a cardinal direction
		//////
			// Based on the slope of the line, determine which portion of each pixel will update
			if (iivvm_math_withinDelta(tfTheta, 0.0, 14) || iivvm_math_withinDelta(tfTheta, _2PI, 14))
			{
				// Slope is due east (toward +X), Y will not change, X will be next larger integer
				p->x = lfX + 1.0;

			} else if (iivvm_math_withinDelta(tfTheta, _PI_2, 14)) {
				// Slope is north (toward +Y), X will not change, Y will be next larger integer
				p->y = lfY + 1.0;

			} else if (iivvm_math_withinDelta(tfTheta, _PI, 14)) {
				// Slope is west (toward -X), Y will not change, X will be next smaller integer
				p->x = lfX - 1.0;

			} else if (iivvm_math_withinDelta(tfTheta, _3PI_2, 14)) {
				// Slope is south (toward -Y), X will not change, Y will be next smaller integer
				p->y = lfY - 1.0;

			} else {
				// If we get here, it's an ordinal direction
				// Initialize our test origins
				lfCosTheta	= cos(tfTheta);
				lfSinTheta	= sin(tfTheta);

				// See which one it is
				if (tfTheta > 0.0f && tfTheta < _PI_2)
				{
					//////////
					// Theta is between 0 and pi/2
					// Slope is north-east, going positive in both Y and X, so we're looking for the integer greater than the current integer on both
					//												                     Y-Intercept
					//												 ___________ _______o___
					// Formulas:		x = r * cos(theta)			|           |           |
					//					y = r * sin(theta)			|           o X-Intercept
					//												|           |           |
					//												|__o________|___________|
					//												   start
					//
					//					X:We know X to determine the radius (next X length):
					//						r = x / cos(theta)
					//						r = (int(x)+1 - x) / cos(theta)
					//
					//					Y:We know Y to determine the radius (next Y length):
					//						r = y / sin(theta)
					//						r = (int(y)+1 - y) / sin(theta)
					//////
						lfXLength	= ((lfX + 1.0) - p->x) / lfCosTheta;
						lfYLength	= ((lfY + 1.0) - p->y) / lfSinTheta;


				} else if (tfTheta > _PI_2 && tfTheta < _PI) {
					//////////
					// Theta is between pi/2 and pi
					// Slope is north-west, going positive in Y and negative in X, so we're looking for the integer greater than the current integer on Y, and less than on X
					//												   Y-Intercept
					//												 __o________ ___________
					// Formulas:		x = r * cos(theta)			|           |           |
					//					y = r * sin(theta)			|           o X-Intercept
					//												|           |           |
					//												|___________|_________o_|
					//												                      start
					//
					//					X:We know X to determine the radius (next X length):
					//						r = x / cos(theta)
					//						[int(x) = x]		r = -1         / cos(theta)
					//						[int(x) != x]		r = x - int(x) / cos(theta)
					//
					//					Y:We know Y to determine the radius (next Y length):
					//						r = y / sin(theta)
					//						r = (int(y)+1 - y) / sin(theta)
					//////
						// X is either int(X) or X-1
						if (lfX == p->x)		lfXLength	= fabs(-1.0			/ lfCosTheta);
						else					lfXLength	= fabs((p->x - lfX)	/ lfCosTheta);

						// Y is always the next integer up
						lfYLength	= ((lfY + 1.0) - p->y) / lfSinTheta;


				} else if (tfTheta > _PI && tfTheta < _3PI_2) {
					//////////
					// Theta is between pi and 3*pi/2
					// Slope is south-west, going negative in both Y and X, so we're looking for the integer less than the current integer on both
					//												                      start
					//												 ___________ _________o_
					// Formulas:		x = r * cos(theta)			|           |           |
					//					y = r * sin(theta)			|           o X-Intercept
					//												|           |           |
					//												|__o________|___________|
					//												   Y-Intercept
					//
					//					X:We know X to determine the radius (next X length):
					//						r = x / cos(theta)
					//						[int(x) = x]		r = (x - 1) / cos(theta)
					//						[int(x) != x]		r = int(x) / cos(theta)
					//
					//					Y:We know Y to determine the radius (next Y length):
					//						r = y / sin(theta)
					//						[int(y) = y]		r = -1 / sin(theta)
					//						[int(y) != y]		r = (int(y) - y) / sin(theta)
					//////
						// X is either int(X) or X-1
						if (lfX == p->x)		lfXLength	= fabs(-1.0			/ lfCosTheta);
						else					lfXLength	= fabs((p->x - lfX)	/ lfCosTheta);

						// Y is either int(Y) or Y-1
						if (lfY == p->y)		lfYLength	= fabs(-1.0			/ lfSinTheta);
						else					lfYLength	= fabs((lfY - p->y)	/ lfSinTheta);


				} else if (tfTheta > _3PI_2 && tfTheta < _2PI) {
					//////////
					// Theta is between 3*pi/2 and 2pi
					// Slope is south-east, going negative in Y and positive in X, so we're looking for the integer less than the current integer on y, and greater than on X
					//												   start
					//												 __o________ ___________
					// Formulas:		x = r * cos(theta)			|           |           |
					//					y = r * sin(theta)			|           o X-Intercept
					//												|           |           |
					//												|___________|_________o_|
					//												                      Y-Intercept
					//
					//					X:We know X to determine the radius (next X length):
					//						r = x / cos(theta)
					//						r = (x - int(x)) / cos(theta)
					//
					//					Y:We know Y to determine the radius (next Y length):
					//						r = y / sin(theta)
					//						[int(y) = y]		r = -1 / sin(theta)
					//						[int(y) != y]		r = (int(y) - y) / sin(theta)
					//////
						// X is always forward from its integer base
						lfXLength	= ((lfX + 1.0) - p->x) / lfCosTheta;

						// Y is either int(Y) or Y-1
						if (lfY == p->y)		lfYLength	= fabs(-1.0			/ lfSinTheta);
						else					lfYLength	= fabs((lfY - p->y)	/ lfSinTheta);


				} else {
					// This should never happen.  It means theta is not in the range 0..2pi.
					// It is advisable to debug the code and fix it.
					_asm int 3;
					return;
				}


			//////////
			// Store the shortest distance for the next point
			//////
				if (lfXLength <= lfYLength)
				{
					// It will hit X at or before it hits Y
					p->x	+= lfXLength * lfCosTheta;
					p->y	+= lfXLength * lfSinTheta;

				} else {
					// It will hit Y before it hits X
					p->x	+= lfYLength * lfCosTheta;
					p->y	+= lfYLength * lfSinTheta;
				}


			//////////
			// Round to nearest 15 significant digits (to remove rounding issues which caused weird artifacts in this algorithm)
			//////
				p->x = ((f64)((u64)(p->x * 100000000000000.0)) / 100000000000000.0);
				p->y = ((f64)((u64)(p->y * 100000000000000.0)) / 100000000000000.0);
		}
		// We're done
	}




//////////
//
// Returns the cardinal or ordinal direction for the indicated point given the pixel's point
// (which is logically the 0/SW position).
//
// Note:  For quadrant I, the pixel point is the point closest to (0,0).
// Note:  It is assumed that P is somewhere on the border of the pixel box of PO's pixel.
//
//////
	s32 iivvm_math_getGravityByRelativePosition(SXYF64* p, SXYS32* po)
	{
		//////////
		//
		// Consider that we're always in quadrant 1 at this point, because we've tested and
		// points that contain one or more coordinates in negative space.
		//      NW __N__ NE     2__3__4
		//      W |     |E      1     5
		//      SW|__S__|SE     0__7__6
		//
		//////
			if (p->x == po->x && p->y == po->y)
			{
				// It's the point closest to the origin
													return(0);		// It's Southwest

			} else if (p->x == po->x) {
				// It's on the SW..NW side
				if (p->y != po->y + 1)				return(1);		// It's west
				else								return(2);		// It's northwest

			} else if (p->y == po->y) {
				// It's on the SW..SE side
				if (p->x != po->x + 1)				return(7);		// It's south
				else								return(6);		// It's southeast

			} else if (p->x == po->x + 1) {
				// It's on the SE..NE side
				if (p->y != po->y + 1)				return(5);		// It's east
				else								return(4);		// It's northeast

			} else if (p->y == po->y + 1) {
				// It's north
													return(3);		// It's north

			} else {
				// It wasn't found.  This will happen if one of the axis isn't at a true gravity
				// condition (i.e. on an axis relative to po).  Even so, there are some conditions
				// we can still examine.
				if ((s32)p->y == po->y)
				{
					// The pixels are on the same y, so it's either west or east
					if (p->x < po->x)				return(1);		// It's west
					else							return(5);		// It's east

				} else if ((s32)p->x == po->x) {
					// The pixels are on the same x, so it's either north or south
					if (p->y < po->y)				return(3);		// It's north
					else							return(7);		// It's south

				} else {
													return(-1);		// It remains invalid :-(
				}
			}
	}




//////////
//
// Returns the cardinal or ordinal direction for the indicated point given the pixel's point
// (which is logically the 0/SW position).
//
// Note:  For quadrant I, the pixel point is the point closest to (0,0).
// Note:  It is assumed that P is somewhere on the border of the pixel box of PO's pixel.
//
//////
	s32 iivvm_math_getGravityInteger(SXYS32* p, SXYS32* po)
	{
		//////////
		//
		// Consider that we're always in quadrant 1 at this point, because we've tested and
		// points that contain one or more coordinates in negative space.
		//      NW __N__ NE     2__3__4
		//      W |  Eq |E      1  8  5
		//      SW|__S__|SE     0__7__6
		//
		// For this value, we can also return -1 if the points are equal (since they are integer-
		// aliased, we are comparing entire pixel positions to entire pixel positions for our
		// derived gravity directions).
		//
		//////
		if (p->x < po->x) {
			// P's to the left of PO
			if (p->y < po->y)						return(0);		// P's to the left and below PO
			else if (p->y > po->y)					return(2);		// P's to the left and above PO
			else									return(1);		// P's directly to the left of PO

		} else if (p->x > po->x) {
			// P's to the right of PO
			if (p->y < po->y)						return(6);		// P's to the right and below PO
			else if (p->y > po->y)					return(4);		// P's to the right and above PO
			else									return(5);		// P's directly to the right of PO

		} else {
			// P is on the same horizontal as PO
			if (p->y < po->y)						return(7);		// P's directly below PO
			else if (p->y > po->y)					return(3);		// P's directly above PO
			else									return(8);		// P is the same as PO
		}
	}




//////////
//
// Called to adjust the gravity based on the value of theta.  This is a slower process than the
// standard relative point compare, but when the gravity point indicates the same side as another
// point, it is time to fine-grain adjust it, and then indicate it as being either at, above, or below.
//
//////
	s32 iivvm_math_fineAdjustGravityByTheta(SXYF64* po, SXYF64* p, SXYF64* pg, s32 lnGravity07p, s32 lnGravity07pg)
	{
		f64 lfDeltaX, lfDeltaY, lfThetaP, lfThetaPg;


		//////////
		// If we're on a corner, then it is a perfect match already
		//////
			switch(lnGravity07p)
			{
				case 0:
				case 2:
				case 4:
				case 6:
					return(lnGravity07pg);		// It is correct being duplicated
			}


		//////////
		// Grab both thetas
		//////
			// p
			lfDeltaX	= p->x - po->x;
			lfDeltaY	= p->y - po->y;
			lfThetaP	= iivvm_math_adjustTheta(atan2(lfDeltaY, lfDeltaX));

			// pg
			lfDeltaX	= pg->x - po->x;
			lfDeltaY	= pg->y - po->y;
			lfThetaPg	= iivvm_math_adjustTheta(atan2(lfDeltaY, lfDeltaX));


		//////////
		// Are they the same?
		//////
			if (lfThetaP == lfThetaPg)
				return(lnGravity07pg);		// Yes, it is correct being duplicated


		//////////
		// If we get here, we need to see where it goes, and adjust from there
		//////
			switch (lnGravity07p)
			{
				case 1:
					if (lfThetaPg < lfThetaP)			return(2);		// Move it to NW
					else								return(0);		// Move it to SW
					break;

				case 3:
					if (lfThetaPg < lfThetaP)			return(4);		// Move it to NE
					else								return(2);		// Move it to NW
					break;

				case 5:
					if (lfThetaPg < lfThetaP)			return(4);		// Move it to NE
					else								return(6);		// Move it to SE
					break;

				case 7:
					if (lfThetaPg < lfThetaP)			return(0);		// Move it to SW
					else								return(6);		// Move it to SE
					break;
				default:
					return(lnGravity07pg);								// Control should never get here, but if it does just send back what was sent in
			}
	}




//////////
//
// Called to adjust theta into the range 0..2pi
//
//////
	f64 iivvm_math_adjustTheta(f64 tfTheta)
	{
		// Validate theta is positive
		while (tfTheta < 0.0)
			tfTheta += _2PI;

		// Validate theta is 0..2pi
		while (tfTheta > _2PI)
			tfTheta -= _2PI;

		return(tfTheta);
	}




//////////
//
// Called to see if the two floating point values are within the delta as is indicated by the
// number of delta digits
//
//////
	bool iivvm_math_withinDelta(f64 tfValue1, f64 tfValue2, s32 tnDeltaDecimals)
	{
		f64 lfDiff;


		//////////
		// Grab the diff and find out the difference
		//////
			lfDiff = fabs(tfValue1 - tfValue2);
			switch (tnDeltaDecimals)
			{
				case 1:
					return(lfDiff <= 0.1);
				case 2:
					return(lfDiff <= 0.01);
				case 3:
					return(lfDiff <= 0.001);
				case 4:
					return(lfDiff <= 0.0001);
				case 5:
					return(lfDiff <= 0.00001);
				case 6:
					return(lfDiff <= 0.000001);
				case 7:
					return(lfDiff <= 0.0000001);
				case 8:
					return(lfDiff <= 0.00000001);
				case 9:
					return(lfDiff <= 0.000000001);
				case 10:
					return(lfDiff <= 0.0000000001);
				case 11:
					return(lfDiff <= 0.00000000001);
				case 12:
					return(lfDiff <= 0.000000000001);
				case 13:
					return(lfDiff <= 0.0000000000001);
				case 14:
					return(lfDiff <= 0.00000000000001);
				case 15:
					return(lfDiff <= 0.000000000000001);
				case 16:
					return(lfDiff <= 0.0000000000000001);
				case -1:
					return(lfDiff <= 1.0);
				case -2:
					return(lfDiff <= 10.0);
				case -3:
					return(lfDiff <= 100.0);
				case -4:
					return(lfDiff <= 1000.0);
				case -5:
					return(lfDiff <= 10000.0);
				case -6:
					return(lfDiff <= 100000.0);
				case -7:
					return(lfDiff <= 1000000.0);
				case -8:
					return(lfDiff <= 10000000.0);
				case -9:
					return(lfDiff <= 100000000.0);
				case -10:
					return(lfDiff <= 1000000000.0);
				case -11:
					return(lfDiff <= 10000000000.0);
				case -12:
					return(lfDiff <= 100000000000.0);
				case -13:
					return(lfDiff <= 1000000000000.0);
				case -14:
					return(lfDiff <= 10000000000000.0);
				case -15:
					return(lfDiff <= 100000000000000.0);
				case -16:
					return(lfDiff <= 1000000000000000.0);

				default:
					return(false);
			}
	}




//////////
//
// Called to multiply an x,y combination by a constant value
//
//////
	void iivvm_math_multiplyBy(SXYF64* p, f64 tfMultiplier)
	{
		if (p)
		{
			p->x *= tfMultiplier;
			p->y *= tfMultiplier;
		}
	}




//////////
//
// Called to determine which direction the gravity point goes based on the line's direction and slope
//
//////
	u32 iivvm_math_getGravityOfThetaAndLeft(f64 tfTheta, bool tlLeft)
	{
		// Based on the slope of the line, determine which portion of each pixel will hold the 
		if (tfTheta == 0 || tfTheta == _2PI)
		{
			// Slope is due east
			if (tlLeft)		return(_COMPASS_NORTH	| _COMPASS_DECORATION_TOP);
			else			return(_COMPASS_SOUTH	| _COMPASS_DECORATION_BOTTOM);

		} else if (tfTheta > 0.0f && tfTheta < _PI_2) {
			// Slope is north-east
			if (tlLeft)		return(_COMPASS_NORTH_WEST	| _COMPASS_DECORATION_TOP		| _COMPASS_DECORATION_LEFT);
			else			return(_COMPASS_SOUTH_EAST	| _COMPASS_DECORATION_BOTTOM	| _COMPASS_DECORATION_RIGHT);

		} else if (tfTheta == _PI_2) {
			// Slope is north
			if (tlLeft)		return(_COMPASS_WEST	| _COMPASS_DECORATION_LEFT);
			else			return(_COMPASS_EAST	| _COMPASS_DECORATION_RIGHT);

		} else if (tfTheta > _PI_2 && tfTheta < _PI) {
			// Slope is north-west
			if (tlLeft)		return(_COMPASS_SOUTH_WEST	| _COMPASS_DECORATION_BOTTOM	| _COMPASS_DECORATION_LEFT);
			else			return(_COMPASS_NORTH_EAST	| _COMPASS_DECORATION_TOP		| _COMPASS_DECORATION_RIGHT);

		} else if (tfTheta == _PI) {
			// Slope is west
			if (tlLeft)		return(_COMPASS_SOUTH	| _COMPASS_DECORATION_BOTTOM);
			else			return(_COMPASS_NORTH	| _COMPASS_DECORATION_TOP);

		} else if (tfTheta > _PI && tfTheta < _3PI_2) {
			// Slope is south-west
			if (tlLeft)		return(_COMPASS_SOUTH_EAST	| _COMPASS_DECORATION_BOTTOM	| _COMPASS_DECORATION_RIGHT);
			else			return(_COMPASS_NORTH_WEST	| _COMPASS_DECORATION_TOP		| _COMPASS_DECORATION_LEFT);

		} else if (tfTheta == _3PI_2) {
			// Slope is south
			if (tlLeft)		return(_COMPASS_EAST	| _COMPASS_DECORATION_RIGHT);
			else			return(_COMPASS_WEST	| _COMPASS_DECORATION_LEFT);

		} else if (tfTheta > _3PI_2 && tfTheta < _2PI) {
			// Slope is south-east
			if (tlLeft)		return(_COMPASS_NORTH_EAST	| _COMPASS_DECORATION_TOP		| _COMPASS_DECORATION_RIGHT);
			else			return(_COMPASS_SOUTH_WEST	| _COMPASS_DECORATION_BOTTOM	| _COMPASS_DECORATION_LEFT);

		} else {
			// This should never happen.  It means theta is not in the range 0..2pi.
			// Debug the code and fix it, sayeth he.
			_asm int 3;
			return(false);
		}
	}




//////////
//
// Converts the standard cardinal/ordinal form to the 0..7 gravity form used by the polygon
// algorithms for determining pixel intercepts
//
//		2__3__4		NW__N__NE
//		1     5		 W     E
//		0__7__6		SW__S__SE
//////
	s32 iivvm_math_getGravity07FromDecoratedGravity(u32 tnGravityDecorated)
	{
		switch (tnGravityDecorated & _COMPASS_CARDINAL_ORDINAL_MASK)
		{
			case _COMPASS_SOUTH_WEST:
				return(0);
			case _COMPASS_WEST:
				return(1);
			case _COMPASS_NORTH_WEST:
				return(2);
			case _COMPASS_NORTH:
				return(3);
			case _COMPASS_NORTH_EAST:
				return(4);
			case _COMPASS_EAST:
				return(5);
			case _COMPASS_SOUTH_EAST:
				return(6);
			case _COMPASS_SOUTH:
				return(7);
			default:
				// This condition should never occur
				// The only forms this input supports are _COMPASS_SOUTH_WEST through _COMPASS_SOUTH, at cardinal and ordinal stops
				_asm int 3;
				return(0);
		}
	}




//////////
//
// Called to physically render the floan, being from P1 to P2, and thusly in a straight line, and
// in that direction, gravity being where gravity is.
//
//////
	void storeFloan_pointToPoint_bad(_isSStoreFloan_lineData* sfld)
	{
		// This one should NEVER be called.
		// If it is called, it's because a line is trying to go from an invalid location to
		// another invalid location, such as from S to S, or SE to S, or some part that's not
		// a valid line intersection with a square.
		// In shrot:  it's an error somewhere, and is time to put your debug on.
		_asm int 3;
	}


//////////
//	2_____
//	|     |		Runs from SW to NW
//	0_____|		Constant 1.0 if gravity is not left
//
// There is one possible floan for the line 0:2:
//		2__3__4
//		1     5		floan:	the square 0:2:4:6, which is the constant 1.0
//		0__7__6
//
//////
	void storeFloan_pointToPoint_0_2(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*	sbgrac;


		// We will always store a floan here even if it's not needed
		sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
		if (sbgrac)
		{
			// Set the offset
			sbgrac->x	= sfld->po.x;
			sbgrac->y	= sfld->po.y;

			// See where gravity is
			if (sfld->gravityDecorated & _COMPASS_DECORATION_LEFT)
			{
				// They are asking for a floan to the smaller of this coordinate, of which it is of no size, therefore there is no such animal.
				// NOP (no operation), but serves as a placeholder to allow corresponding neighbor pixels to be populated.
				sbgrac->alpha = 0.0;

			} else {
				// Full floanage.
				sbgrac->alpha = 1.0;
			}
		}
	}



//////////
//	 __3__ 
//	|     |		Runs from SW to N
//	0_____|		(p1,p1) to (p1,p2) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 0:3:
//		2__3__4
//		1     5		Smaller floan:	0:2:3
//		0__7__6		Larger floan:	0:3:4 + 0:4:6
//
//////
	void storeFloan_pointToPoint_0_3(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 0 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 2 - (p1,p2)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p2.y;

			// 3 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from SW to N
				if (sfld->gravity07 >= 0 && sfld->gravity07 <= 3)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 _____4
//	|     |		Runs from SW to NE
//	0_____|		Will be a constant 0.5 in all cases
//
// There are two possible floans depending on gravity for the line 0:4:
//		2__3__4
//		1     5		Floan 1:	0:2:4
//		0__7__6		Floan 2:	0:4:6
//
//////
	void storeFloan_pointToPoint_0_4(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute* sbgrac;


		//////////
		// Allocate space for the floan entry
		//////
		sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
		if (sbgrac)
		{
			// Store the destination offset
			sbgrac->x		= sfld->po.x;
			sbgrac->y		= sfld->po.y;
			sbgrac->alpha	= 0.5;
		}
	}



//////////
//	 _____ 
//	|     5		Runs from SW to E
//	0_____|		(p1,p1) to (p2,p2) to (p2,p1)
//
// There are two possible floans depending on gravity for the line 0:4:
//		2__3__4
//		1     5		Larger floan:	0:2:4 + 0:4:5
//		0__7__6		Smaller floan:	0:5:6
//
//////
	void storeFloan_pointToPoint_0_5(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 0 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 5 - (p2,p2)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p2.y;

			// 6 - (p2,p1)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p1.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from SW to NE
				if (sfld->gravity07 >= 0 && sfld->gravity07 <= 4)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 _____ 
//	|     |		Runs from NW to NE
//	0_____6
//
// There is one possible floan for the line 0:6:
//		2__3__4
//		1     5		floan:	the square 0:2:4:6, which is the constant 1.0
//		0__7__6
//
//////
	void storeFloan_pointToPoint_0_6(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*	sbgrac;


		// We will always store a floan here even if it's not needed
		sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
		if (sbgrac)
		{
			// Set the offset
			sbgrac->x	= sfld->po.x;
			sbgrac->y	= sfld->po.y;

			// See where gravity is
			if (sfld->gravityDecorated & _COMPASS_DECORATION_BOTTOM)
			{
				// They are asking for a floan to the smaller of this coordinate, of which it is of no size, therefore there is no such animal.
				// NOP (no operation), but serves as a placeholder to allow corresponding neighbor pixels to be populated.
				sbgrac->alpha = 0.0;

			} else {
				// Full floanage.
				sbgrac->alpha = 1.0;
			}
		}
	}



//////////
//	 __3__ 
//	1     |		Runs from W to N
//	|_____|		(p1,p1) to (p1,p2) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 1:3:
//		2__3__4
//		1     5		Smaller floan:	1:2:3
//		0__7__6		Larger floan:	0:1:3 + 0:3:4 + 0:4:6
//
//////
	void storeFloan_pointToPoint_1_3(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 1 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 2 - (p1,p2)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p2.y;

			// 3 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to N
				if (sfld->gravity07 >= 1 && sfld->gravity07 <= 3)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 _____4
//	1     |		Runs from W to SE
//	|_____|		(p1,p1) to (p1,p2) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 1:4:
//		2__3__4
//		1     5		Smaller floan:	1:2:4
//		0__7__6		Larger floan:	0:1:4 + 0:4:6
//
//////
	void storeFloan_pointToPoint_1_4(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 1 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 2 - (p1,p2)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p2.y;

			// 4 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to NE
				if (sfld->gravity07 >= 1 && sfld->gravity07 <= 4)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 _____ 
//	1     5		Runs from W to E, requires two triangles
//	|_____|		#1 - (p1,p1) to (p1,po) to (p2,po)
//				#2 - (p2,p2) to (p1,p1) to (p2,po)
//
// There are two possible floans depending on gravity for the line 1:5:
//		2__3__4
//		1     5		North floan:	1:2:4 + 1:4:5
//		0__7__6		South floan:	0:1:5 + 0:5:6
//
//////
	void storeFloan_pointToPoint_1_5(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri1, tri2;


		//////////
		// Compute the north floan, and then use its value in the appropriate way
		//////
			// Triangle 1
			tri1.p1.x	= sfld->p1.x;					// 1 - (p1,p1)
			tri1.p1.y	= sfld->p1.y;
			tri1.p2.x	= sfld->p1.x;					// 2 - (p1,po)
			tri1.p2.y	= (f64)sfld->po.y;
			tri1.p3.x	= sfld->p2.x;					// 4 - (p2,po)
			tri1.p3.y	= tri1.p2.y;
			iivvm_math_computeTriangle(&tri1);		// Compute the area

			// Triangle 2
			tri2.p1.x	= sfld->p2.x;					// 1 - (p2,p2)
			tri2.p1.y	= sfld->p2.y;
			tri2.p2.x	= sfld->p1.x;					// 4 - (p1,p1)
			tri2.p2.y	= sfld->p1.y;
			tri2.p3.x	= sfld->p2.x;					// 5 - (p2,p0)
			tri2.p3.y	= tri1.p2.y;
			iivvm_math_computeTriangle(&tri2);		// Compute the area

			// Combine their areas into tri1
			tri1.area	+= tri2.area;
			// Right now, tri1.area is the total area


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// Which way does it slant?
				if (sfld->p1.y > sfld->p2.y)
				{
					// It slants like this: \
					// See if gravity runs from NW to E
					if (sfld->gravity07 > 1 && sfld->gravity07 <= 5)
					{
						// North floan
						sbgrac->alpha	= 1.0 - tri1.area;

					} else {
						// South floan
						sbgrac->alpha	= tri1.area;
					}

				} else {
					// It slants like this: /
					// See if gravity runs from W to NE
					if (sfld->gravity07 >= 1 && sfld->gravity07 < 5)
					{
						// North floan
						sbgrac->alpha	= 1.0 - tri1.area;

					} else {
						// South floan
						sbgrac->alpha	= tri1.area;
					}
				}
			}
	}



//////////
//	 _____ 
//	1     |		Runs from W to SE
//	|_____6		(p1,p1) to (p1,p2) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 1:6:
//		2__3__4
//		1     5		Larger floan:	1:2:4 + 1:4:6
//		0__7__6		Smaller floan:	0:1:6
//
//////
	void storeFloan_pointToPoint_1_6(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 0 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 1 - (p1,p2)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p2.y;

			// 6 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to NE
				if (sfld->gravity07 <= 1 || sfld->gravity07 >= 6)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 _____ 
//	1     |		Runs from W to S
//	|__7__|		(p1,p1) to (p1,p2) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 1:7:
//		2__3__4
//		1     5		Larger floan:	1:2:4 + 1:4:6 + 1:6:7
//		0__7__6		Smaller floan:	0:1:7
//
//////
	void storeFloan_pointToPoint_1_7(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 0 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 1 - (p1,p2)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p2.y;

			// 7 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to N
				if (sfld->gravity07 <= 1 || sfld->gravity07 >= 7)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	2_____
//	|     |		Runs from NW to SW
//	0_____|		Constant of 1.0 if gravity is not left
//
// There is one possible floan for the line 0:2:
//		2__3__4
//		1     5		floan:	the square 0:2:4:6, which is the constant 1.0
//		0__7__6
//
//////
	void storeFloan_pointToPoint_2_0(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*	sbgrac;


		// We will always store a floan here even if it's not needed
		sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
		if (sbgrac)
		{
			// Set the offset
			sbgrac->x	= sfld->po.x;
			sbgrac->y	= sfld->po.y;

			// See where gravity is
			if (sfld->gravityDecorated & _COMPASS_DECORATION_LEFT)
			{
				// They are asking for a floan to the smaller of this coordinate, of which it is of no size, therefore there is no such animal.
				// NOP (no operation), but serves as a placeholder to allow corresponding neighbor pixels to be populated.
				sbgrac->alpha = 0.0;

			} else {
				// Full floanage.
				sbgrac->alpha = 1.0;
			}
		}
	}



//////////
//	2_____4
//	|     |		Runs from NW to NE
//	|_____|		Constant 1.0 if gravity is not north
//
// There is one possible floan for the line 2:4:
//		2__3__4
//		1     5		floan:	the square 0:2:4:6, which is the constant 1.0
//		0__7__6
//
//////
	void storeFloan_pointToPoint_2_4(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*	sbgrac;


		// We will always store a floan here even if it's not needed
		sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
		if (sbgrac)
		{
			// Set the offset
			sbgrac->x	= sfld->po.x;
			sbgrac->y	= sfld->po.y;

			// See where gravity is
			if (sfld->gravityDecorated & _COMPASS_DECORATION_TOP)
			{
				// They are asking for a floan to the smaller of this coordinate, of which it is of no size, therefore there is no such animal.
				// NOP (no operation), but serves as a placeholder to allow corresponding neighbor pixels to be populated.
				sbgrac->alpha = 0.0;

			} else {
				// Full floanage.
				sbgrac->alpha = 1.0;
			}
		}
	}



//////////
//	2_____ 
//	|     5		Runs from NW to E
//	|_____|		(p1,p1) to (p2,p1) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 2:5:
//		2__3__4
//		1     5		Larger floan:	1:2:6 + 2:5:6
//		0__7__6		Smaller floan:	2:4:5
//
//////
	void storeFloan_pointToPoint_2_5(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 2 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 4 - (p2,p1)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p1.y;

			// 5 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to N
				if (sfld->gravity07 >= 2 && sfld->gravity07 <= 5)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	2_____ 
//	|     |		Runs from NW to SE
//	|_____6		Will be a constant 0.5 in all cases
//
// There are two possible floans depending on gravity for the line 2:6:
//		2__3__4
//		1     5		Floan 1:	0:2:6
//		0__7__6		Floan 2:	2:4:6
//
//////
	void storeFloan_pointToPoint_2_6(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute* sbgrac;


		//////////
		// Allocate space for the floan entry
		//////
		sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
		if (sbgrac)
		{
			// Store the destination offset
			sbgrac->x		= sfld->po.x;
			sbgrac->y		= sfld->po.y;
			sbgrac->alpha	= 0.5;
		}
	}



//////////
//	2_____ 
//	|     |		Runs from NW to S
//	|__7__|		(p1,p2) to (p1,p1) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 2:7:
//		2__3__4
//		1     5		Larger floan:	2:4:6 + 2:6:7
//		0__7__6		Smaller floan:	0:2:7
//
//////
	void storeFloan_pointToPoint_2_7(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 0 - (p1,p2)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p2.y;

			// 2 - (p1,p1)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p1.y;

			// 7 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to N
				if (sfld->gravity07 <= 2 || sfld->gravity07 == 7)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 __3__ 
//	|     |		Runs from N to SW
//	0_____|		(p2,p2) to (p2,p1) to (p1,p1)
//
// There are two possible floans depending on gravity for the line 0:3:
//		2__3__4
//		1     5		Smaller floan:	0:2:3
//		0__7__6		Larger floan:	0:3:4 + 0:4:6
//
//////
	void storeFloan_pointToPoint_3_0(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 0 - (p2,p2)
			tri.p1.x	= sfld->p2.x;
			tri.p1.y	= sfld->p2.y;

			// 2 - (p2,p1)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p1.y;

			// 3 - (p1,p1)
			tri.p3.x	= sfld->p1.x;
			tri.p3.y	= sfld->p1.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to N
				if (sfld->gravity07 <= 3)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 __3__ 
//	1     |		Runs from N to W
//	|_____|		(p2,p2) to (p2,p1) to (p1,p1)
//
// There are two possible floans depending on gravity for the line 1:3:
//		2__3__4
//		1     5		Smaller floan:	1:2:3
//		0__7__6		Larger floan:	0:1:3 + 0:3:4 + 0:4:6
//
//////
	void storeFloan_pointToPoint_3_1(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 1 - (p2,p2)
			tri.p1.x	= sfld->p2.x;
			tri.p1.y	= sfld->p2.y;

			// 2 - (p2,p1)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p1.y;

			// 3 - (p1,p1)
			tri.p3.x	= sfld->p1.x;
			tri.p3.y	= sfld->p1.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to N
				if (sfld->gravity07 >= 1 && sfld->gravity07 <= 3)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 __3__ 
//	|     5		Runs from N to E
//	|_____|		(p1,p1) to (p2,p1) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 3:5:
//		2__3__4
//		1     5		Larger floan:	0:2:6 + 2:3:6 + 3:5:6
//		0__7__6		Smaller floan:	3:4:5
//
//////
	void storeFloan_pointToPoint_3_5(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 3 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 4 - (p2,p1)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p1.y;

			// 5 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to N
				if (sfld->gravity07 >= 3 && sfld->gravity07 <= 5)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 __3__ 
//	|     |		Runs from N to SE
//	|_____6		(p1,p1) to (p2,p1) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 3:6:
//		2__3__4
//		1     5		Larger floan:	0:2:6 + 2:3:6
//		0__7__6		Smaller floan:	3:4:6
//
//////
	void storeFloan_pointToPoint_3_6(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 3 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 4 - (p2,p1)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p1.y;

			// 6 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to N
				if (sfld->gravity07 >= 3 && sfld->gravity07 <= 6)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 __3__ 
//	|     |		Runs from N to S, requires two triangles
//	|__7__|		#1 - (po,po) to (po,p1) to (p1,p1)
//				#2 - (po,po) to (p1,p1) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 1:7:
//		2__3__4
//		1     5		Floan 1:	0:2:7 + 2:3:7
//		0__7__6		Floan 2:	3:4:7 + 4:6:7
//
//////
	void storeFloan_pointToPoint_3_7(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri1, tri2;


		//////////
		// Compute the north floan, and then use its value in the appropriate way
		//////
			// Triangle 1
			tri1.p1.x	= (f64)sfld->po.x;			// 0 - (po,po)
			tri1.p1.y	= (f64)sfld->po.y;
			tri1.p2.x	= tri1.p1.x;				// 2 - (po,p1)
			tri1.p2.y	= sfld->p1.y;
			tri1.p3.x	= sfld->p1.x;				// 3 - (p1,p1)
			tri1.p3.y	= sfld->p1.y;
			iivvm_math_computeTriangle(&tri1);		// Compute the area

			// Triangle 2
			tri2.p1.x	= tri1.p1.x;				// 0 - (po,po)
			tri2.p1.y	= tri1.p1.y;
			tri2.p2.x	= sfld->p1.x;				// 3 - (p1,p1)
			tri2.p2.y	= sfld->p1.y;
			tri2.p3.x	= sfld->p2.x;				// 7 - (p2,p2)
			tri2.p3.y	= sfld->p2.y;
			iivvm_math_computeTriangle(&tri2);		// Compute the area

			// Combine their areas into tri1
			tri1.area	+= tri2.area;
			// Right now, tri1.area is the total area


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// Which way does it slant?
				if (sfld->p2.x > sfld->p1.x)
				{
					// It slants like this: \
					// See if gravity runs from N to SE
					if (sfld->gravity07 >= 3 && sfld->gravity07 < 7)
					{
						// East floan
						sbgrac->alpha	= 1.0 - tri1.area;

					} else {
						// West floan
						sbgrac->alpha	= tri1.area;
					}

				} else {
					// It slants like this: /
					// See if gravity runs from NE to S
					if (sfld->gravity07 > 3 && sfld->gravity07 <= 7)
					{
						// East floan
						sbgrac->alpha	= 1.0 - tri1.area;

					} else {
						// West floan
						sbgrac->alpha	= tri1.area;
					}
				}
			}
	}



//////////
//	 _____4
//	|     |		Runs from NE to SW
//	0_____|		Will be a constant 0.5 in all cases
//
// There are two possible floans depending on gravity for the line 0:4:
//		2__3__4
//		1     5		Floan 1:	0:2:4
//		0__7__6		Floan 2:	0:4:6
//
//////
	void storeFloan_pointToPoint_4_0(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute* sbgrac;


		//////////
		// Allocate space for the floan entry
		//////
		sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
		if (sbgrac)
		{
			// Store the destination offset
			sbgrac->x		= sfld->po.x;
			sbgrac->y		= sfld->po.y;
			sbgrac->alpha	= 0.5;
		}
	}



//////////
//	 _____4
//	1     |		Runs from SE to W
//	|_____|		(p2,p2) to (p2,p1) to (p1,p1)
//
// There are two possible floans depending on gravity for the line 1:4:
//		2__3__4
//		1     5		Smaller floan:	1:2:4
//		0__7__6		Larger floan:	0:1:4 + 0:4:6
//
//////
	void storeFloan_pointToPoint_4_1(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 1 - (p2,p2)
			tri.p1.x	= sfld->p2.x;
			tri.p1.y	= sfld->p2.y;

			// 2 - (p2,p1)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p1.y;

			// 4 - (p1,p1)
			tri.p3.x	= sfld->p1.x;
			tri.p3.y	= sfld->p1.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 >= 1 && sfld->gravity07 < 4)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	2_____4
//	|     |		Runs from NE to NW
//	|_____|		Constant 1.0 if gravity points anywhere but north
//
// There is one possible floan for the line 2:4:
//		2__3__4
//		1     5		floan:	the square 0:2:4:6, which is the constant 1.0
//		0__7__6
//
//////
	void storeFloan_pointToPoint_4_2(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*	sbgrac;


		// See where gravity is
		if (sfld->gravityDecorated & _COMPASS_DECORATION_TOP)
		{
			// They are asking for a floan to the top of this coordinate, of which there is no such animal.
			// NOP (no operation)

		} else {
			// Full floanage.
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the full pixel value since the gravity runs southward
				sbgrac->x		= sfld->po.x;
				sbgrac->y		= sfld->po.y;
				sbgrac->alpha	= 1.0;
			}
		}
	}



//////////
//	 _____4
//	|     |		Runs from NE to SE
//	|_____6		Constant 1.0 if gravity is anywhere but right
//
// There is one possible floan for the line 4:6:
//		2__3__4
//		1     5		floan:	the square 0:2:4:6, which is the constant 1.0
//		0__7__6
//
//////
	void storeFloan_pointToPoint_4_6(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*	sbgrac;


		// See where gravity is
		if (sfld->gravityDecorated & _COMPASS_DECORATION_RIGHT)
		{
			// They are asking for a floan to the left of this coordinate, of which there is no such animal.
			// NOP (no operation)

		} else {
			// Full floanage.
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the full pixel value since the gravity runs eastward
				sbgrac->x		= sfld->po.x;
				sbgrac->y		= sfld->po.y;
				sbgrac->alpha	= 1.0;
			}
		}
	}



//////////
//	 _____4
//	|     |		Runs from NE to S
//	|__7__|		(p1,p1) to (p1,p2) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 4:7:
//		2__3__4
//		1     5		Larger floan:	0:2:4 + 0:4:7
//		0__7__6		Smaller floan:	4:6:7
//
//////
	void storeFloan_pointToPoint_4_7(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 4 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 6 - (p1,p2)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p2.y;

			// 7 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 > 4 && sfld->gravity07 <= 7)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 _____ 
//	|     5		Runs from E to SW
//	0_____|		(p1,p1) to (p1,p2) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 5:0:
//		2__3__4
//		1     5		Larger floan:	0:2:4 + 0:4:5
//		0__7__6		Smaller floan:	0:5:6
//
//////
	void storeFloan_pointToPoint_5_0(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 5 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 6 - (p1,p2)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p2.y;

			// 0 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 >= 5 && sfld->gravity07 <= 7)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 _____ 
//	1     5		Runs from E to W
//	|_____|		#1 - (po,po) to (p1,p1) to (p2,p2)
//				#2 - (po,po) to (p2,p2) to (p2,po)
//
// There are two possible floans depending on gravity for the line 5:1:
//		2__3__4
//		1     5		North floan:	1:2:4 + 1:4:5
//		0__7__6		South floan:	0:1:5 + 0:5:6
//
//////
	void storeFloan_pointToPoint_5_1(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri1, tri2;


		//////////
		// Compute the north floan, and then use its value in the appropriate way
		//////
			// Triangle 1
			tri1.p1.x	= (f64)sfld->po.x;			// 0 - (po,po)
			tri1.p1.y	= (f64)sfld->po.y;
			tri1.p2.x	= sfld->p1.x;					// 1 - (p1,p1)
			tri1.p2.y	= sfld->p1.y;
			tri1.p3.x	= sfld->p2.x;					// 5 - (p2,p2)
			tri1.p3.y	= sfld->p2.y;
			iivvm_math_computeTriangle(&tri1);		// Compute the area

			// Triangle 2
			tri2.p1.x	= tri1.p1.x;				// 0 - (po,po)
			tri2.p1.y	= tri1.p1.y;
			tri2.p2.x	= sfld->p2.x;					// 5 - (p2,p2)
			tri2.p2.y	= sfld->p2.y;
			tri2.p3.x	= sfld->p2.x;					// 6 - (p2,po)
			tri2.p3.y	= tri1.p1.y;
			iivvm_math_computeTriangle(&tri2);		// Compute the area

			// Combine their areas into tri1
			tri1.area	+= tri2.area;
			// Right now, tri1.area is the total area


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// Which way does it slant?
				if (sfld->p2.y > sfld->p1.y)
				{
					// It slants like this: \
					// See if gravity runs from NW to E
					if (sfld->gravity07 > 1 && sfld->gravity07 <= 5)
					{
						// North floan
						sbgrac->alpha	= 1.0 - tri1.area;

					} else {
						// South floan
						sbgrac->alpha	= tri1.area;
					}

				} else {
					// It slants like this:  /
					// See if gravity runs from W to NE
					if (sfld->gravity07 >= 1 && sfld->gravity07 < 5)
					{
						// North floan
						sbgrac->alpha	= 1.0 - tri1.area;

					} else {
						// South floan
						sbgrac->alpha	= tri1.area;
					}
				}
			}
	}



//////////
//	2_____ 
//	|     5		Runs from E to NW
//	|_____|		(p2,p2) to (p2,p1) to (p1,p1)
//
// There are two possible floans depending on gravity for the line 5:2:
//		2__3__4
//		1     5		Larger floan:	1:2:6 + 2:5:6
//		0__7__6		Smaller floan:	2:4:5
//
//////
	void storeFloan_pointToPoint_5_2(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 2 - (p2,p2)
			tri.p1.x	= sfld->p2.x;
			tri.p1.y	= sfld->p2.y;

			// 4 - (p2,p1)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p1.y;

			// 5 - (p1,p1)
			tri.p3.x	= sfld->p1.x;
			tri.p3.y	= sfld->p1.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 > 2 && sfld->gravity07 <= 5)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 __3__ 
//	|     5		Runs from E to N
//	|_____|		(p2,p2) to (p1,p2) to (p1,p1)
//
// There are two possible floans depending on gravity for the line 5:3:
//		2__3__4
//		1     5		Larger floan:	0:2:6 + 2:3:6 + 3:5:6
//		0__7__6		Smaller floan:	3:4:5
//
//////
	void storeFloan_pointToPoint_5_3(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 3 - (p2,p2)
			tri.p1.x	= sfld->p2.x;
			tri.p1.y	= sfld->p2.y;

			// 4 - (p1,p2)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p2.y;

			// 5 - (p1,p1)
			tri.p3.x	= sfld->p1.x;
			tri.p3.y	= sfld->p1.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 >= 3 && sfld->gravity07 <= 5)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 _____ 
//	|     5		Runs from E to S
//	|__7__|		(p1,p1) to (p1,p2) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 5:7:
//		2__3__4
//		1     5		Larger floan:	0:2:4 + 0:4:5 + 0:5:7
//		0__7__6		Smaller floan:	5:6:7
//
//////
	void storeFloan_pointToPoint_5_7(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 5 - (p1,p1)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p1.y;

			// 6 - (p1,p2)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p2.y;

			// 7 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 >= 5 && sfld->gravity07 <= 7)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 _____ 
//	|     |		Runs from NE to NW
//	0_____6		Constant 1.0 if gravity points anywhere but down
//
// There is one possible floan for the line 6:0:
//		2__3__4
//		1     5		floan:	the square 0:2:4:6, which is the constant 1.0
//		0__7__6
//
//////
	void storeFloan_pointToPoint_6_0(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*	sbgrac;


		// We will always store a floan here even if it's not needed
		sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
		if (sbgrac)
		{
			// Set the offset
			sbgrac->x	= sfld->po.x;
			sbgrac->y	= sfld->po.y;

			// See where gravity is
			if (sfld->gravityDecorated & _COMPASS_DECORATION_BOTTOM)
			{
				// They are asking for a floan to the smaller of this coordinate, of which it is of no size, therefore there is no such animal.
				// NOP (no operation), but serves as a placeholder to allow corresponding neighbor pixels to be populated.
				sbgrac->alpha = 0.0;

			} else {
				// Full floanage.
				sbgrac->alpha = 1.0;
			}
		}
	}



//////////
//	 _____ 
//	1     |		Runs from SE to W
//	|_____6		(p1,p2) to (p1,p1) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 6:1:
//		2__3__4
//		1     5		Larger floan:	1:2:4 + 1:4:6
//		0__7__6		Smaller floan:	0:1:6
//
//////
	void storeFloan_pointToPoint_6_1(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 0 - (p1,p2)
			tri.p1.x	= sfld->p1.x;
			tri.p1.y	= sfld->p2.y;

			// 1 - (p1,p1)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p1.y;

			// 6 - (p2,p2)
			tri.p3.x	= sfld->p2.x;
			tri.p3.y	= sfld->p2.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 <= 1 || sfld->gravity07 > 6)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	2_____ 
//	|     |		Runs from SE to NW
//	|_____6		Will be a constant 0.5 in all cases
//
// There are two possible floans depending on gravity for the line 6:2:
//		2__3__4
//		1     5		Floan 1:	0:2:6
//		0__7__6		Floan 2:	2:4:6
//
//////
	void storeFloan_pointToPoint_6_2(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute* sbgrac;


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x		= sfld->po.x;
				sbgrac->y		= sfld->po.y;
				sbgrac->alpha	= 0.5;
			}
	}



//////////
//	 __3__ 
//	|     |		Runs from SE to N
//	|_____6		(p2,p2) to (p1,p2) to (p1,p1)
//
// There are two possible floans depending on gravity for the line 6:3:
//		2__3__4
//		1     5		Larger floan:	0:2:6 + 2:3:6
//		0__7__6		Smaller floan:	3:4:6
//
//////
	void storeFloan_pointToPoint_6_3(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 3 - (p2,p2)
			tri.p1.x	= sfld->p2.x;
			tri.p1.y	= sfld->p2.y;

			// 4 - (p1,p2)
			tri.p2.x	= sfld->p1.x;
			tri.p2.y	= sfld->p2.y;

			// 6 - (p1,p1)
			tri.p3.x	= sfld->p1.x;
			tri.p3.y	= sfld->p1.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 >= 3 && sfld->gravity07 < 6)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 _____4
//	|     |		Runs from SE to NE
//	|_____6		Will be a constant 1.0 if gravity runs any direction except right
//
// There is one possible floan for the line 6:4:
//		2__3__4
//		1     5		floan:	the square 0:2:4:6, which is the constant 1.0
//		0__7__6
//
//////
	void storeFloan_pointToPoint_6_4(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*	sbgrac;


		// We will always store a floan here even if it's not needed
		sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
		if (sbgrac)
		{
			// Set the offset
			sbgrac->x	= sfld->po.x;
			sbgrac->y	= sfld->po.y;

			// See where gravity is
			if (sfld->gravityDecorated & _COMPASS_DECORATION_RIGHT)
			{
				// They are asking for a floan to the smaller of this coordinate, of which it is of no size, therefore there is no such animal.
				// NOP (no operation), but serves as a placeholder to allow corresponding neighbor pixels to be populated.
				sbgrac->alpha = 0.0;

			} else {
				// Full floanage.
				sbgrac->alpha = 1.0;
			}
		}
	}



//////////
//	 _____ 
//	1     |		Runs from S to W
//	|__7__|		(p2,p1) to (p2,p2) to (p2,p2)
//
// There are two possible floans depending on gravity for the line 7:1:
//		2__3__4
//		1     5		Larger floan:	1:2:4 + 1:4:6 + 1:6:7
//		0__7__6		Smaller floan:	0:1:7
//
//////
	void storeFloan_pointToPoint_7_1(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 0 - (p2,p1)
			tri.p1.x	= sfld->p2.x;
			tri.p1.y	= sfld->p1.y;

			// 1 - (p2,p2)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p2.y;

			// 7 - (p1,p1)
			tri.p3.x	= sfld->p1.x;
			tri.p3.y	= sfld->p1.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 <= 1 || sfld->gravity07 >= 7)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	2_____ 
//	|     |		Runs from S to NW
//	|__7__|		(p2,p1) to (p2,p2) to (p1,p1)
//
// There are two possible floans depending on gravity for the line 7:2:
//		2__3__4
//		1     5		Larger floan:	2:4:6 + 2:6:7
//		0__7__6		Smaller floan:	0:2:7
//
//////
	void storeFloan_pointToPoint_7_2(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 0 - (p2,p1)
			tri.p1.x	= sfld->p2.x;
			tri.p1.y	= sfld->p1.y;

			// 2 - (p2,p2)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p2.y;

			// 7 - (p1,p1)
			tri.p3.x	= sfld->p1.x;
			tri.p3.y	= sfld->p1.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 < 2 || sfld->gravity07 >= 7)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 __3__ 
//	|     |		Runs from S to N, requires two triangles
//	|__7__|		#1 - (po,p1) to (po,p2) to (p1,p1)
//				#2 - (po,p2) to (p2,p2) to (p1,p1)
//
// There are two possible floans depending on gravity for the line 7:3:
//		2__3__4
//		1     5		Floan 1:	0:2:7 + 2:3:7
//		0__7__6		Floan 2:	3:4:7 + 4:6:7
//
//////
	void storeFloan_pointToPoint_7_3(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri1, tri2;


		//////////
		// Compute the north floan, and then use its value in the appropriate way
		//////
			// Triangle 1
			tri1.p1.x	= (f64)sfld->po.x;			// 0 - (po,p1)
			tri1.p1.y	= sfld->p1.y;
			tri1.p2.x	= tri1.p1.x;				// 2 - (po,p2)
			tri1.p2.y	= sfld->p2.y;
			tri1.p3.x	= sfld->p1.x;					// 7 - (p1,p1)
			tri1.p3.y	= sfld->p1.y;
			iivvm_math_computeTriangle(&tri1);		// Compute the area

			// Triangle 2
			tri2.p1.x	= tri1.p1.x;				// 2 - (po,p2)
			tri2.p1.y	= sfld->p2.y;
			tri2.p2.x	= sfld->p2.x;					// 3 - (p2,p2)
			tri2.p2.y	= sfld->p2.y;
			tri2.p3.x	= sfld->p1.x;					// 7 - (p1,p1)
			tri2.p3.y	= sfld->p1.y;
			iivvm_math_computeTriangle(&tri2);		// Compute the area

			// Combine their areas into tri1
			tri1.area	+= tri2.area;
			// Right now, tri1.area is the total area


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// Which way does it slant?
				if (sfld->p1.x > sfld->p2.x)
				{
					// It slants like this: /
					// See if gravity runs from NE to S
					if (sfld->gravity07 > 3 && sfld->gravity07 <= 7)
					{
						// North floan
						sbgrac->alpha	= 1.0 - tri1.area;

					} else {
						// South floan
						sbgrac->alpha	= tri1.area;
					}

				} else {
					// It slants like this: \
					// See if gravity runs from NW to SE
					if (sfld->gravity07 >= 3 && sfld->gravity07 < 7)
					{
						// North floan
						sbgrac->alpha	= 1.0 - tri1.area;

					} else {
						// South floan
						sbgrac->alpha	= tri1.area;
					}
				}
			}
	}



//////////
//	 _____4
//	|     |		Runs from S to NE
//	|__7__|		(p2,p2) to (p2,p1) to (p1,p1)
//
// There are two possible floans depending on gravity for the line 7:4:
//		2__3__4
//		1     5		Larger floan:	0:2:4 + 0:4:7
//		0__7__6		Smaller floan:	4:6:7
//
//////
	void storeFloan_pointToPoint_7_4(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 4 - (p2,p2)
			tri.p1.x	= sfld->p2.x;
			tri.p1.y	= sfld->p2.y;

			// 6 - (p2,p1)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p1.y;

			// 7 - (p1,p1)
			tri.p3.x	= sfld->p1.x;
			tri.p3.y	= sfld->p1.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 > 4)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//	 _____ 
//	|     5		Runs from S to E
//	|__7__|		(p2,p2) to (p2,p1) to (p1,p1)
//
// There are two possible floans depending on gravity for the line 7:5:
//		2__3__4
//		1     5		Larger floan:	0:2:4 + 0:4:5 + 0:5:7
//		0__7__6		Smaller floan:	5:6:7
//
//////
	void storeFloan_pointToPoint_7_5(_isSStoreFloan_lineData* sfld)
	{
		SBGRACompute*		sbgrac;
		STriangleF64		tri;


		//////////
		// Compute the smaller floan, and then use its value in the appropriate way
		//////
			// 4 - (p2,p2)
			tri.p1.x	= sfld->p2.x;
			tri.p1.y	= sfld->p2.y;

			// 6 - (p2,p1)
			tri.p2.x	= sfld->p2.x;
			tri.p2.y	= sfld->p1.y;

			// 7 - (p1,p1)
			tri.p3.x	= sfld->p1.x;
			tri.p3.y	= sfld->p1.y;

			// Compute the area
			iivvm_math_computeTriangle(&tri);


		//////////
		// Allocate space for the floan entry
		//////
			sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(sfld->floans, sizeof(SBGRACompute));
			if (sbgrac)
			{
				// Store the destination offset
				sbgrac->x	= sfld->po.x;
				sbgrac->y	= sfld->po.y;

				// See if gravity runs from W to before NE
				if (sfld->gravity07 >= 5)
				{
					// Smaller floan
					sbgrac->alpha	= tri.area;

				} else {
					// Larger floan
					sbgrac->alpha	= 1.0 - tri.area;
				}
			}
	}



//////////
//
// Rotates the indicated canvas about the indicated point.
//
//////
	u64 iivvm_canvasRotateAbout(SCanvas* tsDst, SBGRA* bdd, s32 ulx, s32 uly, SCanvas* tsSrc, SBGRA* bds, f32 tfRadians, f32 ox, f32 oy)
	{
// TODO:  Write this algorithm. :-)
		return(0);
	}




//////////
//
// Called to draw or generate the bezier using 3 points
//
//////
	u64 iivvm_canvasBezier3(SCanvas* tc, SBGRA* bd, SBezier* bez)
	{
		u32				lnI;
		u64				lnPixelCount;
		f64				lfPercent, lfCosTheta1, lfSinTheta1, lfCosTheta2, lfSinTheta2;
		SXYF64			p1, p2, pbez;
		SLineF64		l1, l2;		// Lines from bez->p1 to bez->p2, and bez->p2 to bez->p3
		SLineF64		lmid;		// Line from l1 to l2
		SXYF64*			lxy;
		SBuilder*		pointFloans;
		SBuilder*		washFloans;


		// Do we need to compute?
		if (!bez->drawFloans)
		{
			//////////
			// Initialize our line data
			//////
				memset(&l1,		0, sizeof(l1));
				memset(&l2,		0, sizeof(l2));
				memset(&lmid,	0, sizeof(lmid));
				l1.trig		= true;
				l2.trig		= true;
				lmid.trig	= true;
				vvm_builderCreateAndInitialize(&pointFloans,	_COMMON_BUILDER_BLOCK_SIZE);		// SXYF64		- for raw floan data points
				vvm_builderCreateAndInitialize(&washFloans,		_COMMON_BUILDER_BLOCK_SIZE);		// SBGRACompute	- used for fx/fy (start/end) floan data points across each pixel

				// Initialize the drawFloans if we need to (they may not be drawing, but just computing)
				if (tc && bd && !bez->drawFloans)
					vvm_builderCreateAndInitialize(&bez->drawFloans, _COMMON_BUILDER_BLOCK_SIZE);


			//////////
			// Copy and compute our lines
			//////
				iivvm_copyLine(&l1, &bez->p1, &bez->p2, true);
				iivvm_copyLine(&l2, &bez->p2, &bez->p3, true);


			//////////
			// Compute our thetas for rapid use
			//////
				// L1
				lfCosTheta1		= cos(l1.theta);
				lfSinTheta1		= sin(l1.theta);
				// L2
				lfCosTheta2		= cos(l2.theta);
				lfSinTheta2		= sin(l2.theta);


			//////////
			// Now, iterate through the bezier building the points
			//////
				for (lnI = 0; lnI < bez->computePointCount; lnI++)
				{
					//////////
					// Get our percentage
					//////
						lfPercent = (f64)lnI / (f64)bez->computePointCount;


					//////////
					// Determine the two points for l1 and l2
					//////
						// P1, L1
						p1.x = bez->p1.x + (lfPercent * l1.radius * lfCosTheta1);
						p1.y = bez->p1.y + (lfPercent * l1.radius * lfSinTheta1);
						// P2, L2
						p2.x = bez->p2.x + (lfPercent * l2.radius * lfCosTheta2);
						p2.y = bez->p2.y + (lfPercent * l2.radius * lfSinTheta2);


					//////////
					// Construct the line between
					//////
						iivvm_copyLine(&lmid, &p1, &p2, true);


					//////////
					// Derive the position of this bezier point
					//////
						// PBEZ
						pbez.x = lmid.p1.x + (lfPercent * lmid.radius * cos(lmid.theta));
						pbez.y = lmid.p1.y + (lfPercent * lmid.radius * sin(lmid.theta));


					//////////
					// Store it as a point floan for later processing
					//////
						if (pbez.x >= 0.0 && pbez.y >= 0.0 && (!tc || (pbez.x < (s32)tc->width && (s32)pbez.y < tc->height)))
						{
							lxy = (SXYF64*)vvm_builderAllocateBytes(pointFloans, sizeof(SXYF64));
							if (lxy)
							{
								// Store the point where it was computed.
								// It may go through a washing algorithm below to actually stores only those X- and Y-Intercept points for the generated points into coordinate space
								lxy->x	= pbez.x;
								lxy->y	= pbez.y;
							}
						}
				}


				//////////
				// Finish by washing if need be
				//////
					if (bez->wash)
						iivvm_canvasBezier_wash(tc, bd, &pointFloans, &washFloans, bez);
		}


		//////////
		// Populate onto the canvas
		//////
			if (tc && bd)
				lnPixelCount = iivvm_canvasBezier_draw(tc, bd, bez);


		//////////
		// Indicate how many pixels were computed, or drawn
		//////
			return(lnPixelCount);
	}




//////////
//
// Called to draw or generate the bezier using 4 points
//
//////
	u64 iivvm_canvasBezier4(SCanvas* tc, SBGRA* bd, SBezier* bez)
	{
		u32				lnI;
		u64				lnPixelCount;
		f64				lfPercent, lfCosTheta1, lfSinTheta1, lfCosTheta2, lfSinTheta2, lfCosTheta3, lfSinTheta3;
		SXYF64			p1, p2, p3, pm1, pm2, pbez;
		SLineF64		l1, l2, l3;				// Lines from bez->p1 to bez->p2, bez->p2 to bez->p3, and bez->p3 to bez->p4
		SLineF64		lmid, lmid1, lmid2;		// Lines from lmid1 to lmid2, l1 to l2, l2 to l3
		SXYF64*			lxy;
		SBuilder*		pointFloans;
		SBuilder*		washFloans;


		// Do we need to compute?
		if (!bez->drawFloans)
		{
			//////////
			// Initialize our line data
			//////
				memset(&l1,		0, sizeof(l1));
				memset(&l2,		0, sizeof(l2));
				memset(&l3,		0, sizeof(l3));
				memset(&lmid,	0, sizeof(lmid));
				memset(&lmid1,	0, sizeof(lmid1));
				memset(&lmid2,	0, sizeof(lmid2));
				l1.trig		= true;
				l2.trig		= true;
				l3.trig		= true;
				lmid.trig	= true;
				lmid1.trig	= true;
				lmid2.trig	= true;
				vvm_builderCreateAndInitialize(&pointFloans,	_COMMON_BUILDER_BLOCK_SIZE);		// SXYF64		- for raw floan data points
				vvm_builderCreateAndInitialize(&washFloans,		_COMMON_BUILDER_BLOCK_SIZE);		// SBGRACompute	- used for fx/fy (start/end) floan data points across each pixel

				// Initialize the drawFloans if we need to (they may not be drawing, but just computing)
				if (tc && bd && !bez->drawFloans)
					vvm_builderCreateAndInitialize(&bez->drawFloans, _COMMON_BUILDER_BLOCK_SIZE);


			//////////
			// Copy and compute our lines
			//////
				iivvm_copyLine(&l1, &bez->p1, &bez->p2, true);
				iivvm_copyLine(&l2, &bez->p2, &bez->p3, true);
				iivvm_copyLine(&l3, &bez->p3, &bez->p4, true);


			//////////
			// Compute our thetas for rapid use
			//////
				// L1
				lfCosTheta1		= cos(l1.theta);
				lfSinTheta1		= sin(l1.theta);
				// L2
				lfCosTheta2		= cos(l2.theta);
				lfSinTheta2		= sin(l2.theta);
				// L3
				lfCosTheta3		= cos(l3.theta);
				lfSinTheta3		= sin(l3.theta);


			//////////
			// Now, iterate through the bezier building the points
			//////
				for (lnI = 0; lnI < bez->computePointCount; lnI++)
				{
					//////////
					// Get our percentage
					//////
						lfPercent = (f64)lnI / (f64)bez->computePointCount;


					//////////
					// Determine the points for l1, l2, and l3
					//////
						// P1
						p1.x = bez->p1.x + (lfPercent * l1.radius * lfCosTheta1);
						p1.y = bez->p1.y + (lfPercent * l1.radius * lfSinTheta1);
						// P2
						p2.x = bez->p2.x + (lfPercent * l2.radius * lfCosTheta2);
						p2.y = bez->p2.y + (lfPercent * l2.radius * lfSinTheta2);
						// P3
						p3.x = bez->p3.x + (lfPercent * l3.radius * lfCosTheta3);
						p3.y = bez->p3.y + (lfPercent * l3.radius * lfSinTheta3);


					//////////
					// Construct the lines between
					//////
						iivvm_copyLine(&lmid1, &p1, &p2, true);
						iivvm_copyLine(&lmid2, &p2, &p3, true);


					//////////
					// Based upon those points, find the middle of the line between them
					//////
						// PM1
						pm1.x = lmid1.p1.x + (lfPercent * lmid1.radius * cos(lmid1.theta));
						pm1.y = lmid1.p1.y + (lfPercent * lmid1.radius * sin(lmid1.theta));
						// PM2
						pm2.x = lmid2.p1.x + (lfPercent * lmid2.radius * cos(lmid2.theta));
						pm2.y = lmid2.p1.y + (lfPercent * lmid2.radius * sin(lmid2.theta));
						// Compute the line between
						iivvm_copyLine(&lmid, &pm1, &pm2, true);


					//////////
					// Derive the position of this bezier point
					//////
						// PBEZ
						pbez.x = lmid.p1.x + (lfPercent * lmid.radius * cos(lmid.theta));
						pbez.y = lmid.p1.y + (lfPercent * lmid.radius * sin(lmid.theta));


					//////////
					// Store it as a point floan for later processing
					//////
						if (pbez.x >= 0.0 && pbez.y >= 0.0 && (!tc || (pbez.x < (s32)tc->width && (s32)pbez.y < tc->height)))
						{
							lxy = (SXYF64*)vvm_builderAllocateBytes(pointFloans, sizeof(SXYF64));
							if (lxy)
							{
								// Store the point where it was computed.
								// It may go through a washing algorithm below to actually stores only those X- and Y-Intercept points for the generated points into coordinate space
								lxy->x	= pbez.x;
								lxy->y	= pbez.y;
							}
						}
				}

				// Finish by washing
				iivvm_canvasBezier_wash(tc, bd, &pointFloans, &washFloans, bez);
		}


		//////////
		// Populate onto the canvas
		//////
			if (tc && bd)
				lnPixelCount = iivvm_canvasBezier_draw(tc, bd, bez);


		//////////
		// Indicate how many pixels were computed, or drawn
		//////
			return(lnPixelCount);
	}




//////////
//
// Called to draw or generate the bezier using 5 points
//
//////
	u64 iivvm_canvasBezier5(SCanvas* tc, SBGRA* bd, SBezier* bez)
	{
		u32				lnI;
		u64				lnPixelCount;
		f64				lfPercent, lfCosTheta1, lfSinTheta1, lfCosTheta2, lfSinTheta2, lfCosTheta3, lfSinTheta3, lfCosTheta4, lfSinTheta4;
		SXYF64			p1, p2, p3, p4, pm1, pm2, pm3, pmm1, pmm2, pbez;
		SLineF64		l1, l2, l3, l4;							// Lines from bez->p1 to bez->p2, bez->p2 to bez->p3, bez->p3 to bez->p4, and bez->p4 to bez->p5
		SLineF64		lmid, lmid1, lmid2, lmid3, lmmid1, lmmid2;		// Lines from lmmid1 to lmmid2, l1 to l2, l2 to l3, l3 to l4, lmid1 to lmid2, lmid2 to lmid3
		SXYF64*			lxy;
		SBuilder*		pointFloans;
		SBuilder*		washFloans;


		// Do we need to compute?
		if (!bez->drawFloans)
		{
			//////////
			// Initialize our line data
			//////
				memset(&l1,		0, sizeof(l1));
				memset(&l2,		0, sizeof(l2));
				memset(&l3,		0, sizeof(l3));
				memset(&l4,		0, sizeof(l3));
				memset(&lmid,	0, sizeof(lmid));
				memset(&lmid1,	0, sizeof(lmid1));
				memset(&lmid2,	0, sizeof(lmid2));
				memset(&lmid3,	0, sizeof(lmid3));
				memset(&lmmid1,	0, sizeof(lmmid1));
				memset(&lmmid2,	0, sizeof(lmmid2));
				l1.trig		= true;
				l2.trig		= true;
				l3.trig		= true;
				l4.trig		= true;
				lmid.trig	= true;
				lmid1.trig	= true;
				lmid2.trig	= true;
				lmid3.trig	= true;
				lmmid1.trig	= true;
				lmmid2.trig	= true;
				vvm_builderCreateAndInitialize(&pointFloans,	_COMMON_BUILDER_BLOCK_SIZE);		// SXYF64		- for raw floan data points
				vvm_builderCreateAndInitialize(&washFloans,		_COMMON_BUILDER_BLOCK_SIZE);		// SBGRACompute	- used for fx/fy (start/end) floan data points across each pixel

				// Initialize the drawFloans if we need to (they may not be drawing, but just computing)
				if (tc && bd && !bez->drawFloans)
					vvm_builderCreateAndInitialize(&bez->drawFloans, _COMMON_BUILDER_BLOCK_SIZE);


			//////////
			// Copy and compute our lines
			//////
				iivvm_copyLine(&l1, &bez->p1, &bez->p2, true);
				iivvm_copyLine(&l2, &bez->p2, &bez->p3, true);
				iivvm_copyLine(&l3, &bez->p3, &bez->p4, true);
				iivvm_copyLine(&l4, &bez->p4, &bez->p5, true);


			//////////
			// Compute our thetas for rapid use
			//////
				// L1
				lfCosTheta1		= cos(l1.theta);
				lfSinTheta1		= sin(l1.theta);
				// L2
				lfCosTheta2		= cos(l2.theta);
				lfSinTheta2		= sin(l2.theta);
				// L3
				lfCosTheta3		= cos(l3.theta);
				lfSinTheta3		= sin(l3.theta);
				// L4
				lfCosTheta4		= cos(l4.theta);
				lfSinTheta4		= sin(l4.theta);


			//////////
			// Now, iterate through the bezier building the points
			//////
				for (lnI = 0; lnI < bez->computePointCount; lnI++)
				{
					//////////
					// Get our percentage
					//////
						lfPercent = (f64)lnI / (f64)bez->computePointCount;


					//////////
					// Determine the points for l1, l2, and l3
					//////
						// P1
						p1.x = bez->p1.x + (lfPercent * l1.radius * lfCosTheta1);
						p1.y = bez->p1.y + (lfPercent * l1.radius * lfSinTheta1);
						// P2
						p2.x = bez->p2.x + (lfPercent * l2.radius * lfCosTheta2);
						p2.y = bez->p2.y + (lfPercent * l2.radius * lfSinTheta2);
						// P3
						p3.x = bez->p3.x + (lfPercent * l3.radius * lfCosTheta3);
						p3.y = bez->p3.y + (lfPercent * l3.radius * lfSinTheta3);
						// P4
						p4.x = bez->p4.x + (lfPercent * l4.radius * lfCosTheta4);
						p4.y = bez->p4.y + (lfPercent * l4.radius * lfSinTheta4);


					//////////
					// Construct the lines between
					//////
						iivvm_copyLine(&lmid1, &p1, &p2, true);
						iivvm_copyLine(&lmid2, &p2, &p3, true);
						iivvm_copyLine(&lmid3, &p3, &p4, true);


					//////////
					// Based upon those points, compute the middle of the line between them
					//////
						// PM1
						pm1.x = p1.x + (lfPercent * l1.radius * cos(lmid1.theta));
						pm1.y = p1.y + (lfPercent * l1.radius * sin(lmid1.theta));
						// PM2
						pm2.x = p2.x + (lfPercent * l2.radius * cos(lmid2.theta));
						pm2.y = p2.y + (lfPercent * l2.radius * sin(lmid2.theta));
						// PM3
						pm3.x = p3.x + (lfPercent * l3.radius * cos(lmid3.theta));
						pm3.y = p3.x + (lfPercent * l3.radius * sin(lmid3.theta));
						// Compute the lines between
						iivvm_copyLine(&lmmid1, &pm1, &pm2, true);
						iivvm_copyLine(&lmmid2, &pm2, &pm3, true);


					//////////
					// Based upon those final two lines, compute the middle of the line between
					//////
						// PMM1
						pmm1.x = pm1.x + (lfPercent * lmmid1.radius * cos(lmmid1.theta));
						pmm1.y = pm1.y + (lfPercent * lmmid1.radius * sin(lmmid1.theta));
						// PMM2
						pmm2.x = pm2.x + (lfPercent * lmmid2.radius * cos(lmmid2.theta));
						pmm2.y = pm2.y + (lfPercent * lmmid2.radius * sin(lmmid2.theta));
						// Compute the lines between
						iivvm_copyLine(&lmid, &pmm1, &pmm2, true);


					//////////
					// Derive the position of this bezier point
					//////
						// PBEZ
						pbez.x = pmm1.x + (lfPercent * lmid.radius * cos(lmid.theta));
						pbez.y = pmm1.y + (lfPercent * lmid.radius * sin(lmid.theta));


					//////////
					// Store it as a point floan for later processing
					//////
						if (pbez.x >= 0.0 && pbez.y >= 0.0 && (!tc || (pbez.x < (s32)tc->width && (s32)pbez.y < tc->height)))
						{
							lxy = (SXYF64*)vvm_builderAllocateBytes(pointFloans, sizeof(SXYF64));
							if (lxy)
							{
								// Store the point where it was computed.
								// It may go through a washing algorithm below to actually stores only those X- and Y-Intercept points for the generated points into coordinate space
								lxy->x	= pbez.x;
								lxy->y	= pbez.y;
							}
						}
				}

				// Finish by washing
				iivvm_canvasBezier_wash(tc, bd, &pointFloans, &washFloans, bez);
		}


		//////////
		// Populate onto the canvas
		//////
			if (tc && bd)
				lnPixelCount = iivvm_canvasBezier_draw(tc, bd, bez);


		//////////
		// Indicate how many pixels were computed, or drawn
		//////
			return(lnPixelCount);
	}




//////////
//
// Called as a common bezier algorithm to wash the computed floans into a form which is usable
// by the common bezier drawing algorithm
//
//////
	void iivvm_canvasBezier_wash(SCanvas* tc, SBGRA* bd, SBuilder** pointFloans, SBuilder** washFloans, SBezier* bez)
	{
		//////////
		// Wash
		/////
			iivvm_math_washFloans(tc, bd, pointFloans, washFloans, ((tc && bd) ? &bez->drawFloans : NULL), false);
	}




//////////
//
// Called as a common drawing algorithm for the bezier curves
//
//////
	u64 iivvm_canvasBezier_draw(SCanvas* tc, SBGRA* bd, SBezier* bez)
	{
		u32				lnI;
		u64				lnPixelCount;
		f64				lfRed, lfGrn, lfBlu, lfAlp, lfMalp, lfAlp2, lfMalp2;
		SBGRA*			sbgra;
		SBGRACompute*	sbgrac;


		//////////
		// Get our colors and alpha masks
		//////
			lfAlp	= (f64)bez->color.alp / 255.0;
			lfMalp	= 1.0 - lfAlp;
			lfRed	= bez->color.red * lfAlp;
			lfGrn	= bez->color.grn * lfAlp;
			lfBlu	= bez->color.blu * lfAlp;


		// Draw each pixel where it goes
		lnPixelCount = 0;
		if (bez->wash)
		{
// TODO:  This drawing algorithm should be moved into a generic algorithm used by the various things which drawn floans
			// The pixels are ready to be drawn generically
			for (lnI = 0; lnI < bez->drawFloans->populatedLength; lnI += sizeof(SBGRACompute))
			{
				// Grab our compute pointer
				sbgrac = (SBGRACompute*)(bez->drawFloans->data + lnI);

				// Get our offset into the canvas
				sbgra	= bd + sbgrac->offsetDst;
				lfAlp2	= lfAlp * sbgrac->alpha;
				lfMalp2	= 1.0 - lfAlp2;

				// Stick the color in there
				sbgra->red	= (u8)(((f64)sbgra->red * lfMalp2) + (lfRed * lfAlp2));
				sbgra->grn	= (u8)(((f64)sbgra->grn * lfMalp2) + (lfGrn * lfAlp2));
				sbgra->blu	= (u8)(((f64)sbgra->blu * lfMalp2) + (lfBlu * lfAlp2));

				// Increase our pixel count
				++lnPixelCount;
			}

		} else {
			// It is a bunch of raw points, so we simply do an aliased population of points along the line
			for (lnI = 0; lnI < bez->drawFloans->populatedLength; lnI += sizeof(SBGRACompute))
			{
				// Grab our compute pointer
				sbgrac = (SBGRACompute*)(bez->drawFloans->data + lnI);

				// Get our offset into the canvas
				sbgra = bd + ((s32)sbgrac->y * tc->width) + (s32)sbgrac->x;

				// Stick the color in there
				sbgra->red	= (u8)(((f64)sbgra->red * lfMalp) + lfRed);
				sbgra->grn	= (u8)(((f64)sbgra->grn * lfMalp) + lfGrn);
				sbgra->blu	= (u8)(((f64)sbgra->blu * lfMalp) + lfBlu);

				// Increase our pixel count
				++lnPixelCount;
			}
		}

		// Indicate our result
		return(lnPixelCount);
	}




//////////
//
// Called to wash the floans to only X- and Y-Intercept boundary points across its line domain.
// Returns floans washed, or (if drawing was specified) drawn.
//
//////
	u64 iivvm_math_washFloans(SCanvas* tc, SBGRA* bd, SBuilder** pointFloans, SBuilder** washFloans, SBuilder** drawFloans, bool tlIsFilledLeft)
	{
		s32				lnI, lnMaxOffset;
		u64				lnFloanCount;
		SBuilder*		pre;
		SBuilder*		post;
		SXYF64*			prexy1;
		SXYF64*			prexy2;
		SXYF64			lastPixelCross, borderProjected;
		SLineF64		line, lineProjectedToPrexy2, lineProjectedToNextPixel;
		SBGRACompute*	sbgrac;


		//////////
		// Initialize
		//////
			pre				= *pointFloans;
			post			= *washFloans;
			lnFloanCount	= 0;
			lnMaxOffset		= pre->populatedLength - sizeof(SXYF64);

			// Turn on trig, ints, and quads, so we also get theta and integer approximations
			line.trig		= true;
			line.ints		= true;
			line.quads		= true;


		//////////
		// Wash (convert from raw point floan form to the washed floan form (pixel border to pixel border))
		//////
			for (lnI = 0; lnI < lnMaxOffset; lnI += sizeof(SXYF64))
			{
				//////////
				// Grab our inputs
				//////
					prexy1 = (SXYF64*)(pre->data + lnI);
					prexy2 = (SXYF64*)(pre->data + lnI + sizeof(SXYF64));
					iivvm_copyLine(&line, prexy1, prexy2, true);


				//////////
				// See if it crosses a pixel border in quadrant 1
				//////
					if (line.start_quad == 1 && line.end_quad == 1 && iivvm_math_getGravityInteger(&line.starti, &line.endi) != 8)
					{
						//////////
						// If one of the starting point, store it.
						//////
							if (prexy1->x == (f64)((s32)prexy1->x) || prexy1->y == (f64)((s32)prexy1->y))
							{
								// Allocate for prexy1 (starting point)
								sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(post, sizeof(SBGRACompute));
								if (sbgrac)
								{
									// Store it
									sbgrac->fx		= (f32)prexy1->x;
									sbgrac->fy		= (f32)prexy1->y;
									sbgrac->alpha	= 1.0;
									++lnFloanCount;
								}
							}

							// Prepare for our projections from wherever we are now
							lastPixelCross.x = line.start.x;
							lastPixelCross.y = line.start.y;


						//////////
						// Process from this point forward repeatedly projecting ahead to see if we will cross any more pixels before this line ends
						//////
							while (1)
							{
								//////////
								// Project ahead from here to see where we'll strike the next axis, and how far it is from here to the end point
								//////
									// To next axis
									borderProjected.x = lastPixelCross.x;
									borderProjected.y = lastPixelCross.y;
									iivvm_math_getNextAxisInterceptXY(&borderProjected, line.theta);
									iivvm_copyLine(&lineProjectedToNextPixel, &lastPixelCross, &borderProjected, true);

									// To end point
									iivvm_copyLine(&lineProjectedToPrexy2, &lastPixelCross, prexy2, true);


								//////////
								// Make sure we'd still be in the correct quadrant with the projection
								//////
									if (lineProjectedToNextPixel.start_quad != 1 || lineProjectedToNextPixel.end_quad != 1)
										break;


								//////////
								// If we hit an axis before the end point, we store that intermediate
								//////
									if (lineProjectedToNextPixel.length < lineProjectedToPrexy2.length)
									{
										// Allocate for the intermediate point
										sbgrac = (SBGRACompute*)vvm_builderAllocateBytes(post, sizeof(SBGRACompute));
										if (sbgrac)
										{
											// Store the floan
											sbgrac->fx		= (f32)borderProjected.x;
											sbgrac->fy		= (f32)borderProjected.y;
											sbgrac->alpha	= 1.0;
											++lnFloanCount;
										}

										// Copy projected to last crossing
										lastPixelCross.x = borderProjected.x;
										lastPixelCross.y = borderProjected.y;

									} else {
										// We're done, we'll hit the end point before, continue on from here
										break;
									}
							}
					}
					// When we get here, we'll continue on with the next point
			}


		//////////
		// Clean up pointFloans (since they've now been washed into washFloans)
		//////
			vvm_builderFreeAndRelease(pointFloans);


		//////////
		// If we are supposed to draw, then do the draw floans
		//////
			if (tc && bd && drawFloans)
				lnFloanCount = iivvm_math_washFloans_doDraw(tc, bd, washFloans, drawFloans, tlIsFilledLeft);


		//////////
		// Indicate our converted floan count
		//////
			return(lnFloanCount);
	}




//////////
//
// Called to draw the washed floans.
//
//////
	u64 iivvm_math_washFloans_doDraw(SCanvas* tc, SBGRA* bd, SBuilder** washFloans, SBuilder** drawFloans, bool tlIsFilledLeft)
	{
		s32				lnI, lnGravityPO, lnGravityP1, lnGravityP2;
		u64				lnFloanCount;
		f64				lfArea;
		SLineF64		line;
		SXYS32			poi;
		SXYF64			pof, p1, p2;
		SBuilder*		wash;
		SBuilder*		draw;
		SBGRACompute*	sbgrac;
		SBGRACompute*	sbgrac1;
		SBGRACompute*	sbgrac2;


		//////////
		// Wash floans are already pixel border to pixel border.  As such, we can easily convert
		// them to floans.
		//////
			lnFloanCount	= 0;
			wash			= *washFloans;
			draw			= *drawFloans;
			for (lnI = 0; lnI < (s32)(wash->populatedLength - sizeof(SBGRACompute)); lnI += sizeof(SBGRACompute))
			{
				//////////
				// Grab the pointers
				//////
					sbgrac1 = (SBGRACompute*)(wash->data + lnI);
					sbgrac2 = (SBGRACompute*)(wash->data + lnI + sizeof(SBGRACompute));


				//////////
				// Convert to f64
				//////
					// po
					poi.x	= (s32)sbgrac1->fx;
					poi.y	= (s32)sbgrac1->fy;
					pof.x	= (f64)poi.x;
					pof.y	= (f64)poi.y;
					// p1
					p1.x	= (f64)sbgrac1->fx;
					p1.y	= (f64)sbgrac1->fy;
					// p2
					p2.x	= (f64)sbgrac2->fx;
					p2.y	= (f64)sbgrac2->fy;


				//////////
				// pg (compute the gravity to be either to the left or right of the center of this point)
				//////
					iivvm_copyLine(&line, &p1, &p2, true);
					line.theta = iivvm_math_adjustTheta(line.theta + ((tlIsFilledLeft) ? _PI_4 : -_PI_4));
					iivvm_math_getNextAxisInterceptXY(&line.mid, line.theta);


				//////////
				// Grab the gravities
				//////
					lnGravityPO		= iivvm_math_getGravityByRelativePosition(&line.mid,	&poi);
					lnGravityP1		= iivvm_math_getGravityByRelativePosition(&p1,			&poi);
					lnGravityP2		= iivvm_math_getGravityByRelativePosition(&p2,			&poi);


				//////////
				// Convert it to floanage
				//////
					if (p1.x >= 0.0 && p1.y >= 0.0 && p2.x >= 0.0 && p2.y >= 0.0)
					{
						// Compute the area
						lfArea	= iivvm_math_getAreaOfSquareUsing_po_p1_p2(lnGravityPO, lnGravityP1, lnGravityP2, &pof, &p1, &p2);

						// Store the floan
						sbgrac	= (SBGRACompute*)vvm_builderAllocateBytes(draw, sizeof(SBGRACompute));
						if (sbgrac)
						{
							// Store the offset and area (alpha) for this part
							sbgrac->offsetDst	= ((s32)poi.y * tc->width) + (s32)poi.x;
							sbgrac->alpha		= lfArea;

							// Indicate we stored another floan
							++lnFloanCount;
						}
					}
			}
			

		//////////
		// Clean up washFloans, and resize drawFloans
		//////
			vvm_builderFreeAndRelease(washFloans);
			vvm_builderSetSize(draw, draw->populatedLength);


		//////////
		// Indicate how many floans we generated
		//////
			return(lnFloanCount);
	}




//////////
//
// We use cb->extra for the total pixels drawn
//
//////
	void ivvm_regionRefreshCallback(SStartEndCallback* cb)
	{
		// Process this region
		vvm_regionRefresh(cb->ptrRegion, cb->ex1PtrRegion);
	}




//////////
//
// Callback when there is a specified region that isn't a default being passed.  This could
// indicate a program error or an incompatibility between expected data, and available data
// for processing.
//
//////
	void ivvm_regionDoDefaultDebugTrapCallback(SRegion* tr, u64 tnIdentifier, u64 tnExtra)
	{
		// Trapped due to error, return and see where it occurred
		_asm int 3;
	}
