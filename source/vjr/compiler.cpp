//////////
//
// /libsf/source/vjr/compiler.cpp
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jun.17.2014
//////
// Change log:
//     Jun.17.2014 - Initial creation
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
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




struct SStartEnd;
struct SMasterList;

//////////
//
// Forward declarations for parsing VXB-- lines and components
//
//////////
	u32						compiler_breakoutAsciiTextIntoSOssLines		(s8* tcData, u32 tnFileSize, SStartEnd* tseLines, u32 tnAllocSize);
// 	SOssComp* CALLTYPE		oss_translateSOssLinesToSOssComps			(SAsciiCompSearcher* tsComps, SOssLine* line);
// 	void CALLTYPE			oss_translateSOssCompsToOthers				(SAsciiCompSearcher* tsComps, SOssLine* line);
// 	u32 CALLTYPE			oss_writeSOssLineSequenceToDisk				(s8* tcPathname, SStartEnd* tseLines);
// 	u32 CALLTYPE			oss_writeSOssLineSequenceCompsToDisk		(s8* tcPathname, SStartEnd* tseLines);
// 	u32 CALLTYPE			oss_writeSOssLineSequenceCompsDebuggingToDisk(s8* tcPathname, SStartEnd* tseLines);
// 	bool CALLTYPE			oss_findFirstOccurrenceOfAsciiCharacter		(s8* tcHaystack, u32 tnHaystackLength, s8 tcNeedle, u32* tnPosition);
// 	SOssComp* CALLTYPE		oss_findNextSOssCompBy_iCode				(SOssComp* comp, u32 tniCode, SOssComp** compLastScanned);
// 	SOssComp* CALLTYPE		oss_skipPastSOssComp_iCode					(SOssComp* comp, u32 tniCode);
// 	u32 CALLTYPE			oss_combine2SOssComps						(SOssLine* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2,                     u32 tniCodeCombined);
// 	u32 CALLTYPE			oss_combine3SOssComps						(SOssLine* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeNeedle3, u32 tniCodeCombined);
// 	u32 CALLTYPE			oss_combineAllBetweenSOssComps				(SOssLine* line, u32 tniCodeNeedle,                                          u32 tniCodeCombined);
// 	u32 CALLTYPE			oss_combineAllAfterSOssComp					(SOssLine* line, u32 tniCodeNeedle);
// 	u32 CALLTYPE			oss_combineAllCasks							(SOssComp* firstComp, bool* tlNestingError, SOssComp** compError);
// 	u32 CALLTYPE			oss_removeExtraneousWhitespaceSOssComps		(SOssLine* line, u32 tniCodeWhitespace);

	u32						ioss_breakoutAsciiTextDataIntoLines_ScanLine(s8* tcData, u32 tnMaxLength, u32* tnLength, u32* tnWhitespaces);
	u32						vvm_getNextUniqueId							(void);
	void*					vvm_SEChain_prepend							(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*					vvm_SEChain_append							(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*					ivvm_SEChain_appendOrPrepend				(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult);
	u32						vvm_iSkipWhitespaces						(s8* tcData, u32 tnMaxLength);
	u32						vvm_iSkipToCarriageReturnLineFeed			(s8* tcData, u32 tnMaxLength, u32* tnCRLF_Length);
	void					ivvm_SEChain_appendMasterList				(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded);
	bool					vvm_SEChain_allocateAdditionalMasterSlots	(SStartEnd* ptrSE, u32 tnBlockSize);


//////////
// Constant integers
//////
	cu32					_COMMON_START_END_BLOCK_SIZE			= 32;			// Allocate 32 entries/slots at a time (Start/end)
	cu32					_COMMON_START_END_SMALL_BLOCK_SIZE		= 4;			// Allocate 4 entries/slots at a time (Start/end)
	cu32					_COMMON_START_END_BIG_BLOCK_SIZE		= 256;			// Allocate 256 entries/slots at a time (Start/end)
	cu32					_COMMON_BUILDER_BLOCK_SIZE				= 16384;		// Allocate 16KB at a time
	cu32					_COMMON_BUILDER_BLOCK_SIZE_BIG			= 10240000;		// Allocate 1MB at a time


//////////
// Structures taken from Visual FreePro
//////
	struct SLL
	{
		SLL*			next;					// Next entry in linked list
		SLL*			prev;					// Previous entry in linked list
		u32				uniqueId;				// Unique id associated with this object
	};

	struct SMasterList
	{
		SLL				ll;						// 2-way link list to hold the related pointer
		bool			used;					// Is this entry/slot used?

		// The reference pointer used to occupy this slot/position
		void*			ptr;					// The pointer associated with this entry
	};

	// The rigidity of this structure is extremely important.
	// Every item in the chain between root and last must be included in the master list!
	struct SStartEnd
	{
		SMasterList*	root;					// Root item
		SMasterList*	last;					// Last item

		// SStartEnd lists can have a master (which points to other items using the SMasterList protocol), or it can be used merely a pointer holder
		union {
			SMasterList**	master;				// Every item in the start/end chain is appended here when created (used primarily for suspension and resumption of the VVM)
			void**			ptr;
		};
		u32				masterCount;			// Number of entries in the master array (used for resizing)

		// Not used and reserved for future use
		void*			extra;					// For future expansion
	};

	// Holds a line structure, one entry for every line in a file
	struct SOssLine
	{
		SLL				ll;												// 2-way link list

		// Information about the line
		s8*				alternateBase;									// (Optional) If used, indicates we are not using "the associated base memory blocK" as the the reference pointer for this line, but have replaced it with our own oss_malloc allocation, if so then it will need manually freed with oss_free
		s8*				base;											// Base for the start of this line
		u32				start;											// Start of the line in the associated base memory block
		u32				length;											// Length of the line (excluding trailing CR/LF combinations)
		u32				whitespace;										// How much whitespace precedes the start of non-whitespace content on the line
		u32				lineNumber;										// Line number when initially parsed

		// Parsed / processed information about the raw source line (if used)
		SStartEnd		comps;											// Pointer to the first component identified on this line	(SOssComp)
		SStartEnd		compsCombined;									// When comps are combined, the first element is morphed into the new type, but any that were replaced go here	(SOssComp)
		// Note:  components begin at (line->base + line->start + line->whitespace), which is what would be found if comp->start = 0

		// For portions of the line which have been parsed
		void*			extra;											// Extra data associated with this structure (application specific)
	};









//////////
//
// Called to parse the indicated block of text data.  It converts every combination of an ASCII-13,
// ASCII-10, or groupings in any order of ASCII-13+ASCII-10 into end-of-line entries.
//
// Returns:
//		NULL	- error
//		Pointer to the first SOssLine entry
//		Note:  Every reference in SOssLine points to a location within tcData, so if tcData is freed, then all references are lost
//
//////
	u32 compiler_breakoutAsciiTextIntoSOssLines(s8* tcData, u32 tnFileSize, SStartEnd* tseLines, u32 tnAllocSize)
	{
		u32			lnOffset, lnTotalLineLength, lnLineCount;
		SOssLine*	linePrev;
		SOssLine*	line;


		// Make sure our environment is sane
		lnLineCount = 0;
		if (tcData && tnFileSize != 0 && tnAllocSize <= 0xffffffff)
		{
			// Initialize our variables
			lnOffset	= 0;
			lnLineCount	= 0;
			linePrev	= NULL;
			goto storeFirstOne;

			// Iterate through every byte of the source data until all lines are broken out
			while (line && lnOffset < tnFileSize)
			{
				// Mark the start of this line
				lnTotalLineLength	= ioss_breakoutAsciiTextDataIntoLines_ScanLine(tcData + lnOffset, tnFileSize - lnOffset, &line->length, &line->whitespace);

				// Make sure we still have more to go
				lnOffset += lnTotalLineLength;
				if (lnOffset <= tnFileSize)
				{
					// Create the next line
					linePrev = line;

storeFirstOne:
					//////////
					// Allocate this entry
					///////
						line = (SOssLine*)vvm_SEChain_append(tseLines, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SOssLine), _COMMON_START_END_BLOCK_SIZE, NULL);


					//////////
					// Populate the line with specified information
					//////
						//
						//////
							if (line)
							{
								// Update our link lists
								if (linePrev)		linePrev->ll.next	= (SLL*)line;
								line->ll.prev		= (SLL*)linePrev;

								// Indicate where this next line will/would start
								line->start			= lnOffset;
								line->base			= tcData;
								line->lineNumber	= lnLineCount + 1;						// Store the number as base-1, not base-0

								// Allocate the extra block if we have one to do
								if (tnAllocSize != 0)
								{
									// Allocate the memory block for this extra associated item
									line->extra = malloc((u32)tnAllocSize);

									// Initialize it to its empty state
									if (line->extra)		memset((s8*)line->extra, 0, tnAllocSize);
								}

								// Increase our line count
								++lnLineCount;
							}
						//////
						//
					//////
					// END
					//////////
				}
			}
			// IF we get here, failure
		}
		// If we get here, we do not have any lines
		return(lnLineCount);
	}




//////////
//
// Scans from the indicated location forward until finding CR/LF or any combination thereof,
// nothing whitespaces, content, and total line length (including cr/lf combinations at the end)
//
//////
	u32 ioss_breakoutAsciiTextDataIntoLines_ScanLine(s8* tcData, u32 tnMaxLength, u32* tnLength, u32* tnWhitespaces)
	{
		u32 lnLength, lnWhitespaces, lnCRLF_Length;


		// Make sure we have something to do
		lnLength		= 0;
		lnWhitespaces	= 0;
		lnCRLF_Length	= 0;
		if (tcData && tnMaxLength > 0)
		{
			// Skip past any whitespaces
			lnWhitespaces = vvm_iSkipWhitespaces(tcData, tnMaxLength);
			if (tnWhitespaces)
				*tnWhitespaces = lnWhitespaces;


			// Skip to the ending carriage return / line feed
			lnLength = vvm_iSkipToCarriageReturnLineFeed(tcData + lnWhitespaces, tnMaxLength - lnWhitespaces, &lnCRLF_Length);
			if (tnLength)
				*tnLength = lnLength;
		}
		// Return the total length
		return(lnWhitespaces + lnLength + lnCRLF_Length);
	}




//////////
//
// Scans from the indicated location forward until finding a non-whitespace character
//
//////
	u32 vvm_iSkipWhitespaces(s8* tcData, u32 tnMaxLength)
	{
		u32 lnLength;


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
	u32 vvm_iSkipToCarriageReturnLineFeed(s8* tcData, u32 tnMaxLength, u32* tnCRLF_Length)
	{
		u32 lnLength, lnCRLF_Length;


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
// Get the next Unique ID
//
//////
	u32 vvm_getNextUniqueId(void)
	{
		u32 lnValue;

		// Synchronized access
		EnterCriticalSection(&gcsUniqueIdAccess);

		// Get our value and increment
		lnValue = gnNextUniqueId;
		++gnNextUniqueId;

		// All done
		LeaveCriticalSection(&gcsUniqueIdAccess);

		// Return that value
		return(lnValue);
	}



	void* vvm_SEChain_prepend(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(ivvm_SEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, true, tlResult));
	}

	void* vvm_SEChain_append(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(ivvm_SEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, false, tlResult));
	}

	// Prepends or appends to the Start/end chain
	void* ivvm_SEChain_appendOrPrepend (SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult)
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

	
	bool vvm_SEChain_allocateAdditionalMasterSlots(SStartEnd* ptrSE, u32 tnBlockSize)
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
