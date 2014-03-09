//////////
//
// /libsf/vvm/vvmmc/mc_sup.cpp
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
//     Nov.23.2012 - Initial creation
//////
// VVM Assembler supplemental source code
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
// Loads the indicated resource language for the debugger
//
//////
	bool iLoadResource(s8* tcLanguage)
	{
		s8 buffer[MAX_PATH];


		// Try to load the dll
		sprintf_s(buffer, sizeof(buffer), "vvmmc%s.dll\000", tcLanguage);
		ghResourceDll = LoadLibraryA(buffer);
		if (!ghResourceDll)
		{
			// There was an error loading the indicated resource dll
			// Fallback to English
			ghResourceDll = LoadLibraryA(cgcVvmmcEngDll);
			if (!ghResourceDll)
				return(false);		// If we get here, then it's bad, bad, bad news, mister!
		}
		// We're good
		return(true);
	}




//////////
//
// Callback to search for matching resources to those already loaded
//
//////
	bool iimc_loadResourceAsciiTextCallback(SStartEndCallback* cb)
	{
		SVvmmcResourceText*	lr;


		// Make sure the environment is sane
		if (cb && cb->ptr)
		{
			lr = (SVvmmcResourceText*)cb->ptr;
			if (lr->resourceNumber == cb->extra)
				return(true);		// It's a match
		}
		// Not a match
		return(false);
	}




//////////
//
// Append the indicated error to the error list
//
//////
	void imc_appendError(SStartEnd* tseErrors, SOssLine* line, SOssComp* comp, u32 tnResource)
	{
		SVvmmcError* lve;


		// Make sure our environment is sane
		if (tseErrors && line && comp)
		{
			// Create our new error entry
			lve = (SVvmmcError*)vvm_SEChain_append(tseErrors, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SVvmmcError), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);
			if (lve)
			{
				// Store the error location
				lve->lineNumber		= line->lineNumber;
				lve->column			= line->whitespace + comp->start;
				lve->pathName		= ((_isSLineInfo*)(line->extra))->file->pathname.data._s8;

				// Store error number and info
				lve->code			= tnResource;
				lve->text			= mc_loadResourceAsciiText(tnResource);
			}
		}
	}




//////////
//
// Append the indicated error to the error list
//
//////
	void imc_appendWarning(SStartEnd* tseWarnings, SOssLine* line, SOssComp* comp, u32 tnResource)
	{
		// AT the current time, the storage mechanism for warnings and errors is the same.
		// However, in the future it could be broken out and made separate
		imc_appendError(tseWarnings, line, comp, tnResource);
	}




//////////
//
// Append the indicated variable to the variable list
//
//////
	void imc_appendVariable(SStartEnd* tseVariable, SOssComp* compName, SOssComp* compData, s64 tnLength)
	{
		SVariable*	lv;


		// Make sure our environment is sane
		if (tseVariable && compName && compName->line && compName->line->base && compData && compData->line && compData->line->base && tnLength > 0)
		{
			lv = (SVariable*)vvm_SEChain_append(tseVariable, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SVariable), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);
			if (lv)
			{
				// Store the variable
				lv->name.data._s8					= (s8*)oss_alloc(compName->length + 1, true);
				if (lv->name.data._s8)				vvm_memcpy(lv->name.data._s8, compName->line->base + compName->line->start + compName->line->whitespace + compName->start, compName->length);
				lv->name.length						= compName->length;

				// Store the variable's data
				lv->current._value.data._s8			= (s8*)oss_alloc(tnLength + 1, true);
				if (lv->current._value.data._s8)	vvm_memcpy(lv->current._value.data._s8, compData->line->base + compData->line->start + compData->line->whitespace + compData->start, tnLength);
				lv->current._value.length			= tnLength;

				// Indicate this variable is ascii character data
				lv->current.type				= _VVM_VARIABLE_ASCII;
			}
		}
	}




//////////
//
// Helper functions to save lots of syntax
//
//////
	SStartEnd* imc_programGetScreens(SStartEnd* tseProg)
	{
		if (tseProg && tseProg->last && tseProg->last->ptr)		return(&(((SProgram*)tseProg->last->ptr)->screens));
		return(NULL);		// If we get here, not valid
	}

	SStartEnd* imc_programGetGlobals(SStartEnd* tseProg)
	{
		if (tseProg && tseProg->last && tseProg->last->ptr)		return(&(((SProgram*)tseProg->last->ptr)->_globals));
		return(NULL);		// If we get here, not valid
	}

	SStartEnd* imc_programGetSnippets(SStartEnd* tseProg)
	{
		if (tseProg && tseProg->last && tseProg->last->ptr)		return(&(((SProgram*)tseProg->last->ptr)->snips));
		return(NULL);		// If we get here, not valid
	}

	SStartEnd* imc_programGetDynSnips(SStartEnd* tseProg)
	{
		if (tseProg && tseProg->last && tseProg->last->ptr)		return(&(((SProgram*)tseProg->last->ptr)->dsnips));
		return(NULL);		// If we get here, not valid
	}

	SStartEnd* imc_programGetTimers(SStartEnd* tseProg)
	{
		if (tseProg && tseProg->last && tseProg->last->ptr)		return(&(((SProgram*)tseProg->last->ptr)->_timers));
		return(NULL);		// If we get here, not valid
	}

	SStartEnd* imc_programGetThreads(SStartEnd* tseProg)
	{
		if (tseProg && tseProg->last && tseProg->last->ptr)		return(&(((SProgram*)tseProg->last->ptr)->_threads));
		return(NULL);		// If we get here, not valid
	}

	SStartEnd* imc_programGetDefines(SStartEnd* tseProg)
	{
		if (tseProg && tseProg->last && tseProg->last->ptr)		return(&(((SProgram*)tseProg->last->ptr)->_defines));
		return(NULL);		// If we get here, not valid
	}




//////////
//
// Searches previously identified variables for the program for a match.
// tseVariables should point to a Start/end holding SVariable structures.
//
// Returns:
//		SVariable*		- of the define variable if found
//		NULL			- not found
//
//////
	SVariable* imc_searchVariablesByName(SStartEnd* tseVariables, SDatum* tsDatum)
	{
		SStartEndCallback cb;

		// If any defines are defined, then search them
		if (tseVariables)
		{
			cb._func	= (u64)iimc_searchVariablesByNameCallback;
			cb.extra	= (u64)tsDatum;
			return((SVariable*)vvm_SEChain_searchByCallback(tseVariables, &cb));

		} else {
			return(NULL);		// None are yet defined
		}
	}

	bool iimc_searchVariablesByNameCallback(SStartEndCallback* cb)
	{
		SDatum*		ld;
		SVariable*	lv;


		// Make sure the environment is sane
		if (cb && cb->ptr)
		{
			lv	= (SVariable*)cb->ptr;
			ld	= (SDatum*)cb->extra;
			if (lv->name.length == ld->length)
			{
				// They're the same length, it's possible they match
				if (_memicmp(lv->name.data._s8, ld->data._s8, (u32)ld->length) == 0)
					return(true);		// This is it
			}
		}
		// If we get here, failure, indicate it wasn't found
		return(false);
	}




//////////
//
// Callback for validating the line comps (used during initial development/debugging only)
//
//////
	bool iimc_validateStartEndCompsCallback(SStartEndCallback* cb)
	{
		SOssLine* line;


		// Make sure our environment is sane
		if (cb && cb->ptr)
		{
			// Grab the ptr as what it is, a line
			line = (SOssLine*)cb->ptr;

			// Validate any of the line's components or combined components
			vvm_SEChain_validate(&line->comps, 0);
			vvm_SEChain_validate(&line->compsCombined, 0);

			// If we get here, we're good, had there been an error there would've been _asm int 3 on one of those iValidateStartEnd entries
			return(true);
		}
		// There's an error
		return(false);
	}




//////////
//
// From mc_asm.cpp:
//
// Called to handle the pass-0 assembly process.  Breaks out all known tokens, and identifies
// the start and end of every snip/dsnip block, along with global memory variable definition,
// loading of constants, etc.
//
//////
	void imc_assemblyPass0(SAssembly* ta, SSourceFile* tsf)
	{
		SOssLine*				line;
		SOssComp*				comp;
		_isSLineInfo*			lli;
		_isPass0BlockScanData	pbsd;


		// Make sure there are lines to process
		if (tsf->lines.root)
		{
			// We repeat for the number of lines there are, but we move line independently of the entry in tseLines->master[] because as include files are found they are inserted
			line = (SOssLine*)tsf->lines.root->ptr;
			while (line)
			{
				// Grab the extra data for this line
				lli = (_isSLineInfo*)line->extra;
				if (!lli->completed)
				{
					// Grab the first component
					comp = (SOssComp*)line->comps.root->ptr;

					// See if this line begins with the include keyword
					oss_translateSOssCompsToOthers(cgcKeywordKeywords0, line);
				}

				// Move to original next line
				line = (SOssLine*)line->ll.next;
			}
			// When we get here, everything that is initially known should be identified, including all blocks

// TODO:  add a pass0 post fixup function which identifies common groupings

			// Scan through to make sure blocks are matched, report first error and terminate
			memset(&pbsd, 0, sizeof(_isPass0BlockScanData));
			pbsd.ta		= ta;
			pbsd.tsf	= tsf;
			iimc_assemblyPass0ScanForBlocks((SOssLine*)tsf->lines.root->ptr, _MC_ICODE_UNKNOWN, NULL, &pbsd);
			// There is a boolean value returned here, but we don't use it.
			// The tsf->errors and tsf->warnings will be updated with issues when we return
		}
	}




//////////
//
// From mc_asm.cpp:
//
// Replace ~tilde~ values with related defines, and then re-parse the line.  The way this
// replacement works is that it cannot and will not subsequently replace with the include
// keyword, and then execute on that keyword.  It will be left unprocessed and later
// reported as an unknown keyword error.
//
//////
	void imc_assemblyPass1(SAssembly* ta, SSourceFile* tsf)
	{
		u64				lnStart, lnEnd, lnNewLength;
		SOssLine*		line;
		_isSLineInfo*	lli;
		SDatum			ldatum;
		SVariable*		ld;
		s8*				lcNewLineBase;


		// Make sure there are lines to process
		if (tsf->lines.root)
		{
			// We repeat for the number of lines there are, but we move line independently of the entry in tseLines->master[] because as include files are found they are inserted
			line = (SOssLine*)tsf->lines.root->ptr;
			while (line)
			{
				// Grab the extra data for this line
				lli = (_isSLineInfo*)line->extra;
				if (!lli->completed)
				{
					// So long as there are ~tilde~ pairs, repeat the search
// TODO:  (future enhancement) make this a true 64-bit find first occurrence function
					while (	oss_findFirstOccurrenceOfAsciiCharacter(line->base + line->start + line->whitespace,					(u32)line->length,					'~',	&lnStart) &&	/* first tilde */
							oss_findFirstOccurrenceOfAsciiCharacter(line->base + line->start + line->whitespace + lnStart + 1,		(u32)line->length - lnStart - 1,	'~',	&lnEnd))		/* second tilde */
					{
						// Search the indicated ~tilde~ item to see if it's known to us
						ldatum.data._s8		= line->base + line->start + line->whitespace + lnStart + 1;
						ldatum.length		= lnEnd;
						ld					= imc_searchVariablesByName(&ta->prog->_defines, &ldatum);
						if (ld)
						{
							// It is known, we need to swap it out
							// Delete the existing components on this line
							vvm_SEChain_delete(&line->comps, 0, 0, true);
							vvm_SEChain_delete(&line->compsCombined, 0, 0, true);


							//////////
							// Substitute the line
							//////
								// Determine the new length
								lnNewLength	= line->length + line->whitespace - ldatum.length + ld->current._value.length - 2;
								lcNewLineBase	= (s8*)oss_alloc(lnNewLength, false);
								if (lcNewLineBase)
								{
									// Copy everything up to the tilde
									vvm_memcpy(lcNewLineBase, line->base + line->start, line->whitespace + lnStart);
									// Copy the substitution
									vvm_memcpy(lcNewLineBase + line->whitespace + lnStart, ld->current._value.data._s8, ld->current._value.length);
									// Copy everything after the tilde
									vvm_memcpy(lcNewLineBase + line->whitespace + lnStart + ld->current._value.length, 
											line->base + line->start + line->whitespace + lnStart + lnEnd,
											line->length - lnStart - lnEnd - 2);
									// When we get here, we have our new, expanded line

									// The alternate base holds a flag indicating if the original base has been replaced by post-processing.  Refer to its definition in the structure.
									if (line->alternateBase)
										oss_free(line->base);		// We've already expanded at least once, so we delete the old value and replace

									// The new line base
									line->alternateBase	= lcNewLineBase;
									line->base			= lcNewLineBase;
									line->start			= 0;
									line->length		= lnNewLength;

									// Reprocess the line after the tilde entries were expanded
									oss_translateSOssLinesToSOssComps(cgcKeywordOperators, line);
									oss_translateSOssCompsToOthers(cgcKeywordKeywords0, line);
								}
						}
					}
				}

				// Attempt to identify pass-1 keywords
				oss_translateSOssCompsToOthers(cgcKeywordKeywords1, line);

// TODO:  add a pass1 post fixup function which identifies common groupings

				// Move to original next line
				line = (SOssLine*)line->ll.next;
			}
		}
	}




//////////
//
// From mc_asm.cpp:
//
// Parses the starts and stops of key components for high-level pieces of snippet information.
// By the time we get here, every keyword should be completely broken out, the blocks have
// been coordinated each with a proper start and end, all labels and pipe-sign parameters have
// been identified.
//
//////
	void imc_assemblyPass2(SAssembly* ta, SSourceFile* tsf)
	{
		SOssLine*		line;
		_isSLineInfo*	lli;


		// Parse the block starting line, extracting components
		if (!iimc_assemblyPass2ParseBlockStartsAndLabels(ta, tsf))
			return;		// A failure parsing this block identifier

		// Make sure there are lines to process
		if (tsf->lines.root)
		{
			// We repeat for the number of lines there are, but we move line independently of the entry in tseLines->master[] because as include files are found they are inserted
			line = (SOssLine*)tsf->lines.root->ptr;
			while (line)
			{
				// Grab the extra data for this line
				lli = (_isSLineInfo*)line->extra;
				if (!lli->completed)
				{
// TODO:  working here
				}

				// Move to original next line
				line = (SOssLine*)line->ll.next;
			}
		}
	}




//////////
//
// From mc_asm.cpp:
//
// Called to do the heavy lifting of loading individual source files, breaking out lines, and
// tagging each line with what is necessary for processing subsequent internal requests, such
// as loading include files, etc.
//
// We know when this function is called that tcData is valid, and that tnFileSize is > 0.
//
//////
	SSourceFile* imc_loadSourceFile(	s8*			tcSourcePathname, 
										s8*			tcData,					u64			tnFileSize, 
										SAssembly*	ta, 
										u64			tnAllocSize,			bool		tlUseOssAlloc		)
	{
		u64				lnLineCount, lnLength;
		SOssLine*		line;
		SOssComp*		comp;
		SSourceFile*	lsf;


		//////////
		// Verify our environment is sane
		//////
			if (!tcData || tnFileSize == 0 || !ta)
				return(NULL);	// Nothing to do

		//////////
		// Add this filename to the list of loaded files
		//////
			lnLength	= strlen(tcSourcePathname);
			lsf			= (SSourceFile*)vvm_SEChain_append(&ta->includeFiles, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SSourceFile), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);
			if (!lsf)	return(NULL);		// Failure


		//////////
		// Append the pathname
		//////
			lsf->pathname.data._s8				= (s8*)oss_alloc(lnLength + 1, true);
			if (!lsf->pathname.data._s8)		return(lsf);			// Failure
			vvm_memcpy(lsf->pathname.data._s8, tcSourcePathname, lnLength);
			lsf->pathname.length				= lnLength;


		//////////
		// Add the source code itself to the assembly entry
		//////
			lsf->sourceCode.data._s8			= (s8*)oss_alloc(tnFileSize, false);
			if (!lsf->sourceCode.data._s8)		return(lsf);			// Failure
			vvm_memcpy(lsf->sourceCode.data._s8, tcData, tnFileSize);
			lsf->sourceCode.length				= tnFileSize;


		//////////
		// Convert the source code to separate lines
		//////
			lnLineCount = oss_breakoutAsciiTextIntoSOssLines(tcData, tnFileSize, &lsf->lines, sizeof(_isSLineInfo), tlUseOssAlloc);
			// Note:  We don't check the line count here because we know when this function is called that tnFileSize is > 0, which means at least one line
// For debugging:
//oss_writeSOssLineSequenceToDisk("\\libsf\\vvm\\vasm\\test\\testout.vasm", &lsf->lines);


		//////////
		// Iterate through each line and populate its extra data
		//////
			line = (SOssLine*)lsf->lines.root->ptr;
			while (line)
			{
				//////////
				// Populate the extra data pointer with the associated file on this line
				//////
					((_isSLineInfo*)line->extra)->file = lsf;


				//////////
				// Breakout the components on this line to their base forms for later reconstitution into known keywords
				//////
					comp = oss_translateSOssLinesToSOssComps(cgcKeywordOperators, line);
					// Note:  comp is not used here, but it is included in source code to indicate at a glance what is returned
#pragma message("mc_sup.cpp::imc_loadSourceFile() contains several validation functions which slow down performance.  These can be removed after development and strong testing.")
SStartEndCallback cb;
cb._func = (u64)iimc_validateStartEndCompsCallback;
vvm_SEChain_validate(&lsf->lines, &cb);

//if (iIsNeedleInHaystack(line->base + line->start + line->whitespace, line->length, "_", 1))
//	oss_writeSOssLineSequenceCompsToDisk("\\libsf\\vvm\\vasm\\test\\testoutcomps.txt", &lsf->lines);
//	_asm nop;

				//////////
				// Combine standard things
				//////
// TODO:  (future enhancement) will need to continually combine items which are related, such as a variable _like_this_14_abc into a single alphanumeric
					oss_combine2SOssComps			(line, _MC_ICODE_UNDERSCORE,		_MC_ICODE_NUMERIC,		_MC_ICODE_ALPHANUMERIC);
cb._func = (u64)iimc_validateStartEndCompsCallback;
vvm_SEChain_validate(&lsf->lines, &cb);

					oss_combine2SOssComps			(line, _MC_ICODE_ALPHA,			_MC_ICODE_UNDERSCORE,	_MC_ICODE_ALPHA);
cb._func = (u64)iimc_validateStartEndCompsCallback;
vvm_SEChain_validate(&lsf->lines, &cb);

					oss_combine2SOssComps			(line, _MC_ICODE_UNDERSCORE,		_MC_ICODE_ALPHA,			_MC_ICODE_ALPHA);
cb._func = (u64)iimc_validateStartEndCompsCallback;
vvm_SEChain_validate(&lsf->lines, &cb);

					oss_combine2SOssComps			(line, _MC_ICODE_ALPHA,			_MC_ICODE_NUMERIC,		_MC_ICODE_ALPHANUMERIC);
cb._func = (u64)iimc_validateStartEndCompsCallback;
vvm_SEChain_validate(&lsf->lines, &cb);

					oss_combine2SOssComps			(line, _MC_ICODE_ALPHANUMERIC,	_MC_ICODE_UNDERSCORE,	_MC_ICODE_ALPHANUMERIC);
cb._func = (u64)iimc_validateStartEndCompsCallback;
vvm_SEChain_validate(&lsf->lines, &cb);

					oss_combine3SOssComps			(line, _MC_ICODE_NUMERIC,		_MC_ICODE_DOT,		_MC_ICODE_NUMERIC,		_MC_ICODE_NUMERIC);
cb._func = (u64)iimc_validateStartEndCompsCallback;
vvm_SEChain_validate(&lsf->lines, &cb);

//if (iIsNeedleInHaystack(line->base + line->start + line->whitespace, line->length, "_", 1))
//	oss_writeSOssLineSequenceCompsToDisk("\\libsf\\vvm\\vasm\\test\\testoutcomps.txt", &lsf->lines);
//	_asm nop;

				//////////
				// Fixup quotes, comments
				//////
					oss_combineAllBetweenSOssComps	(line, _MC_ICODE_SINGLE_QUOTE,		_MC_ICODE_SINGLE_QUOTED_TEXT);
cb._func = (u64)iimc_validateStartEndCompsCallback;
vvm_SEChain_validate(&lsf->lines, &cb);

					oss_combineAllBetweenSOssComps	(line, _MC_ICODE_DOUBLE_QUOTE,		_MC_ICODE_DOUBLE_QUOTED_TEXT);
cb._func = (u64)iimc_validateStartEndCompsCallback;
vvm_SEChain_validate(&lsf->lines, &cb);

					oss_combineAllAfterSOssComp		(line, _MC_ICODE_COMMENT);
cb._func = (u64)iimc_validateStartEndCompsCallback;
vvm_SEChain_validate(&lsf->lines, &cb);


				//////////
				// Fixup casks
				//////
					oss_combineAllCasks((SOssComp*)line->comps.root->ptr);
cb._func = (u64)iimc_validateStartEndCompsCallback;
vvm_SEChain_validate(&lsf->lines, &cb);
if (	iIsNeedleInHaystack(line->base + line->start + line->whitespace, (u32)line->length, "(|", 2)
	||	iIsNeedleInHaystack(line->base + line->start + line->whitespace, (u32)line->length, "[|", 2)
	||	iIsNeedleInHaystack(line->base + line->start + line->whitespace, (u32)line->length, "<|", 2)
	||	iIsNeedleInHaystack(line->base + line->start + line->whitespace, (u32)line->length, "~|", 2))
	oss_writeSOssLineSequenceCompsToDisk("\\libsf\\vvm\\vasm\\test\\testoutcomps.txt", &lsf->lines);
	_asm nop;


				//////////
				// Move to next line
				//////
					line  =(SOssLine*)line->ll.next;
			}
			// When we get here, we have every line in the source file loaded, and tagged with the tcSourceFilename it came from


		//////////
		// Load any include files found within
		//////
			imc_parseIncludeFilesAndDefines(ta, lsf);


		// Indicate our success
// For debugging:
// oss_writeSOssLineSequenceCompsToDisk("\\libsf\\vvm\\vasm\\test\\testoutcomps.txt", &lsf->lines);
		return(lsf);
	}




//////////
//
// From mc_asm.cpp:
//
// Called to scan the source file for include lines, and if found to load them, which pre-parses
// them into their cgcKeywordOperators condition.
//
//////
	void imc_parseIncludeFilesAndDefines(SAssembly* ta, SSourceFile* tsf)
	{
		u64				lnLastPosition;
		_isSLineInfo*	lli;
		SOssLine*		lineNext;
		SOssLine*		line;
		SOssComp*		comp;
		SOssComp*		compName;
		SOssComp*		compData;
		SSourceFile*	lsf;
		s8				lcIncludeFilename[1024];


		// Make sure there are lines to process
		if (tsf->lines.master && tsf->lines.root)
		{
			// We repeat for the number of lines there are, but we move line independently of the entry in tseLines->master[] because as include files are found they are inserted
			line = (SOssLine*)tsf->lines.root->ptr;
			while (line)
			{
				// Grab the extra info
				lli = (_isSLineInfo*)line->extra;

				// Grab the next line we're currently pointing to
				lineNext = (SOssLine*)line->ll.next;

				// Make sure the line is valid
				if (line->length != 0)
				{
					// See if this line begins with the include keyword
					oss_translateSOssCompsToOthers(cgcKeywordKeywordsPre, line);

					// Make sure we have components on this line
					if (line->comps.root)
					{
						// Grab a pointer to the first component
						comp = (SOssComp*)line->comps.root->ptr;

						// Check for comments and include files only
						if (comp->iCode == _MC_ICODE_COMMENT)
						{
							// The first component is a comment, mark this whole line as completed
							lli->completed = true;

//////////
// DEFINE
//////
						} else if (comp->iCode == _MC_ICODE_DEFINE) {
							// It's a define command, add it to the list of defines
							// See if there is a name for the define thing
							compName = (SOssComp*)comp->ll.next;
							compName = oss_skipPastSOssComp_iCode(compName, _MC_ICODE_WHITESPACE);
							if (!compName)
							{
								// Syntax error, nothing after define
								imc_appendError(&tsf->errors, line, comp, IDS_SYNTAX_ERROR);
								break;
							}

							// See if there is something after the name
							compData = (SOssComp*)compName->ll.next;
							compData = oss_skipPastSOssComp_iCode(compData, _MC_ICODE_WHITESPACE);
							if (!compData)
							{
								// Syntax error, nothing after define name
								imc_appendError(&tsf->errors, line, (SOssComp*)comp->ll.next, IDS_SYNTAX_ERROR);
								break;
							}

							// Verify the name is in proper form
							if (!mc_verifyVariableAsciiName(compName, &lnLastPosition))
							{
								// Name is not proper
								// Adjust to the position of error
								compName->start += lnLastPosition;

								// Store the error
								imc_appendError(&tsf->errors, line, compName, IDS_INVALID_VARIABLE_NAME);
								break;
							}

							// Store the new define variable
							imc_appendVariable(&ta->prog->_defines, compName, compData, line->length - compData->start);

							// Mark it as completed
							lli->completed = true;

//////////
// INCLUDE
//////
						} else if (comp->iCode == _MC_ICODE_INCLUDE) {
							// The first component is the include keyword
							compName = (SOssComp*)comp->ll.next;
							compName = oss_skipPastSOssComp_iCode(compName, _MC_ICODE_WHITESPACE);
							if (!compName)
							{
								// Syntax error, nothing after define
								imc_appendError(&tsf->errors, line, compName, IDS_SYNTAX_ERROR);
								break;
							}

							// Grab the filename
							if (!mc_verifyAsciiFilename(compName, &lnLastPosition))
							{
								// Name is not proper
								// Adjust to the position of error
								compName->start += lnLastPosition;

								// Store the error
								imc_appendError(&tsf->errors, line, compName, IDS_INVALID_VARIABLE_NAME);
								break;
							}

							// Copy and null-terminate the filename
							vvm_memset(lcIncludeFilename, 0, sizeof(lcIncludeFilename));
							if (compName->iCode == _MC_ICODE_SINGLE_QUOTED_TEXT || compName->iCode == _MC_ICODE_DOUBLE_QUOTED_TEXT)
							{
								// We have to bypass the quote character
								vvm_memcpy(lcIncludeFilename, compName->line->base + compName->line->start + compName->line->whitespace + compName->start + 1, min(lnLastPosition, sizeof(lcIncludeFilename)-1));

							} else {
								// It's just a filename, copy it as it is
								vvm_memcpy(lcIncludeFilename, compName->line->base + compName->line->start + compName->line->whitespace + compName->start, min(lnLastPosition, sizeof(lcIncludeFilename)-1));
							}

							// Try to open it and load its lines
							lsf = iimc_loadThisIncludeFile(lcIncludeFilename, line, compName, ta, tsf);
							if (!lsf)
								return;		// There were errors loading this file.

							// If lines were added, they need to be appended into the file after the current location
							if (lsf->lines.masterCount != 0 && lsf->lines.root)
							{
								// Migrate the master list of lines to the end of the existing master list
								// This puts all the source lines in 
								line->ll.next								= (SLL*)lsf->lines.root->ptr;
								((SOssLine*)lsf->lines.last->ptr)->ll.next	= (SLL*)lineNext;

								// Move all the lsf->lines to the end of tsf->lines.  They won't be in sequence in tsf->lines, but the proper order was handled above
								vvm_SEChain_migrateAll(&tsf->lines, &lsf->lines);

// For debugging:
// Write the output file of all the lines now to disk
//oss_writeSOssLineSequenceToDisk("c:\\temp\\out.vasm", &tsf->lines);
							}

							// Mark it as completed
							lli->completed = true;
						}
						//else ignore it
					}

				} else {
					// Mark this line as completed
					lli->completed = true;
				}

				// Move to the next line, see if it has any include files
				line = lineNext;
			}
		}
	}




//////////
//
// From mc_asm.cpp:
//
// Called to physically load the indicated include file from disk.
// Note:  This is not the original (top-level) .vasm source file, but is only the
//        subsequent include files that are specified.
//
//////
	SSourceFile* iimc_loadThisIncludeFile(s8* tcPathname, SOssLine* line, SOssComp* compName, SAssembly* ta, SSourceFile* tsf)
	{
		s64		lnHandle, lnFileSize, lnNumread;
		s8*		lcData;


		// Attempt to open the file
		lnHandle = oss_sharedAsciiOpenFile(tcPathname, false, true, false, false, false, false, false, false);
		if (lnHandle < 0)
		{
			// Open file error
			imc_appendError(&tsf->errors, line, compName, IDS_ERROR_UNABLE_TO_OPEN);
			return(NULL);
		}
		// If we get here, we're good


		// Get file size
		lnFileSize = oss_sharedAsciiFileSize(lnHandle);
		if (lnFileSize > 0xffffffff)
		{
			// Uhhh... what are they trying to do to us? :-)
			imc_appendError(&tsf->errors, line, compName, IDS_ERROR_FILE_IS_TOO_BIG);
			return(NULL);
		}
		if (lnFileSize == 0)
		{
			// This is not an error for include files, as they can be zero bytes
			// It is a warning, however.
			imc_appendWarning(&tsf->errors, line, compName, IDS_WARNING_FILE_IS_0_BYTES);
			oss_sharedAsciiCloseFile(lnHandle);
			return(NULL);
		}


		// Allocate memory to load
		lcData = (s8*)oss_alloc((u32)lnFileSize, false);
		if (!lcData)
		{
			// We should always be able to allocate memory
			imc_appendError(&tsf->errors, line, compName, IDS_ERROR_ALLOCATING_MEMORY);
			oss_sharedAsciiCloseFile(lnHandle);
			return(NULL);
		}
		// If we get here, memory is allocated


		// Read into it
		lnNumread = oss_sharedAsciiReadFile(lnHandle, lcData, (u32)lnFileSize);
		oss_sharedAsciiCloseFile(lnHandle);
		if (lnNumread != lnFileSize)
		{
			// We should always be able to read the file bytes
			imc_appendError(&tsf->errors, line, compName, IDS_ERROR_UNABLE_TO_READ_BYTES_FROM);
			return(NULL);
		}
		// We're good

		// Load the raw data, parse out into lines, load any include files contained therein
		return(imc_loadSourceFile(tcPathname, lcData, (u32)lnFileSize, ta, sizeof(_isSLineInfo), false));
	}




//////////
//
// Scan for blocks, called recursively to scan for matched blocks
//
//////
	SOssLine* iimc_assemblyPass0ScanForBlocks(SOssLine* line, u32 tniCode, SBlock* block, _isPass0BlockScanData* pbsd)
	{
		SOssLine*		lineResult;
		_isSLineInfo*	lli;


// TODO:  this algorithm needs to be completely refactored due to the use of casks
_asm int 3;
		// Make sure our environment is sane
		pbsd->llOkayToAddPipeDataToBlock	= (block != NULL);
		pbsd->llab							= NULL;
		pbsd->lpip							= NULL;
		pbsd->ldfi							= NULL;
		while (line)
		{
			// Grab this line's extra information
			lli = (_isSLineInfo*)line->extra;
			if (!lli->completed)
			{
				// If the line data is sane, continue processing
				if (line->comps.root && (SOssComp*)line->comps.root->ptr)
				{
					// This line has something no it, see where we are
					// Only looking at the first component on the line
					pbsd->comp = (SOssComp*)line->comps.root->ptr;

					// See where we are
					if (pbsd->comp->iCode != _MC_ICODE_COMMENT)
					{
						// We process block pipes up until we hit any other line of code
						if (pbsd->comp->iCode != _MC_ICODE_PIPE_SIGN)
							pbsd->llOkayToAddPipeDataToBlock = false;

						//////////
						// For certain block-related components, we process them here
						//////
							if (pbsd->comp->iCode == _MC_ICODE_SNIP || 
								pbsd->comp->iCode == _MC_ICODE_DSNIP || 
								pbsd->comp->iCode == _MC_ICODE_DLL ||
								pbsd->comp->iCode == _MC_ICODE_BXML)
							{
								// We've found the start of a SNIP/FUNCTION or DSNIP definition
								line = iimc_assemblyPass0ScanForBlocksSnipDefs(line, tniCode, &block, pbsd);
								if (!line)	return(NULL);

							} else if (pbsd->comp->iCode == _MC_ICODE_END) {
								// We've found the end
								// It's either a correct end, or an incorrect end, but regardless we're returning to the caller
								return(iimc_assemblyPass0ScanForBlocksEnd(line, tniCode, &block, pbsd));

							} else if (pbsd->comp->iCode == _MC_ICODE_COLON) {
								// It's the start of a label, which *MUST* appear within a block
								lineResult = iimc_assemblyPass0ScanForBlocksColon(line, tniCode, &block, pbsd);
								if (!lineResult)	return(lineResult);

							} else if (pbsd->comp->iCode == _MC_ICODE_DLL_FUNCTION_DEFINITION) {
								// We are starting a DLL function definition.  We need to be inside a DSNIP_DLL iCode.
								lineResult = iimc_assemblyPass0ScanForBlocksDllFuncDef(line, tniCode, &block, pbsd);
								if (!lineResult)	return(lineResult);

							} else if (pbsd->comp->iCode == _MC_ICODE_PIPE_SIGN) {
								// There is pipe data, needs to be for either the block (appropriately) or the dsnip_dll
								lineResult = iimc_assemblyPass0ScanForBlocksPipeSign(line, tniCode, &block, pbsd);
								if (!lineResult)	return(lineResult);

							} else {
								// When we get here, we have not found one of our regular keywords we're looking for at this level.
								// However, if we are outside of a block, we only allow comments and variable declarations
								if (tniCode == _MC_ICODE_UNKNOWN)
								{
									// We're outside of a block
									if (pbsd->comp->iCode < _MC_LOWEST_ICODE_VARIABLE_DEFINITION || pbsd->comp->iCode > _MC_HIGHEST_ICODE_VARIABLE_DEFINITION)
									{
										// Oops!  And we found something other than a comment!
										imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_ERROR_UNABLE_TO_READ_BYTES_FROM);
										return(NULL);
									}
								}
							}

					}
				}
			}
			// Move to the next line
			pbsd->linePrev	= line;
			line			= (SOssLine*)line->ll.next;
		}
		// When we get here, we're done
		if (tniCode != _MC_ICODE_UNKNOWN && tniCode != _MC_ICODE_END)
		{
			// We have reached the end, but we weren't looking for the end
			if (pbsd->linePrev)	imc_appendError(&pbsd->tsf->errors, pbsd->linePrev,	NULL,	IDS_UNMATCHED_BLOCK);
			else				imc_appendError(&pbsd->tsf->errors, NULL,			NULL,	IDS_UNMATCHED_BLOCK);
		}
		// When we get here, we're always NULL
		return(NULL);
	}

// TODO:  in the future, concatenated snippets may be allowed.  For now, they will have to be named with underscores.
	SOssLine* iimc_assemblyPass0ScanForBlocksSnipDefs(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd)
	{
		SLabelInfo*		llab;
		SPipeInfo*		lpip;
		SDllFuncInfo*	ldfi;


// TODO:  this algorithm needs to be completely refactored due to the use of casks
_asm int 3;
		// See where we are
		if (tniCode == _MC_ICODE_UNKNOWN)
		{
			// Allocate the start of this block
			*block = (SBlock*)vvm_SEChain_append(&pbsd->tsf->blocks, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SBlock), _COMMON_START_END_BLOCK_SIZE, NULL);
			if (!*block)
			{
				// Memory error
				imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_ERROR_ALLOCATING_MEMORY);
				return(NULL);
			}

			// Populate the block information
			(*block)->start			= line;
			(*block)->compTrigger	= pbsd->comp;

			// Allocate the start of the thing
			if (pbsd->comp->iCode == _MC_ICODE_SNIP)
			{
				// Allocate the snippet (for future use)
				(*block)->snip = (SSnip*)oss_alloc(sizeof(SSnip), true);
				if (!(*block)->snip)
				{
					// Memory error
					imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_ERROR_ALLOCATING_MEMORY);
					return(NULL);
				}

			} else {
				// Allocate the dynamic snippet (for future use)
				(*block)->dsnip = (SDynSnip*)oss_alloc(sizeof(SDynSnip), true);
				if (!(*block)->dsnip)
				{
					// Memory error
					imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_ERROR_ALLOCATING_MEMORY);
					return(NULL);
				}
			}

			// Save our values for future restoration
			llab			= pbsd->llab;
			lpip			= pbsd->lpip;
			ldfi			= pbsd->ldfi;

			// We are not currently looking for anything, so we can accept this and we must be looking for the matching END
			pbsd->lineNext	= iimc_assemblyPass0ScanForBlocks((SOssLine*)line->ll.next, _MC_ICODE_END, *block, pbsd);
			if (!pbsd->lineNext)
				return(NULL);		// Not found, did not match up

			// If we get here, we found a valid value, so we are pointing to the end of the block
			line			= pbsd->lineNext;
			(*block)->end	= pbsd->lineNext;
			// When lineNext becomes lineNext->ll.next, it will be on the line after this block

			// Restore our original values
			pbsd->llab		= llab;
			pbsd->lpip		= lpip;
			pbsd->ldfi		= ldfi;

			// Indicate success
			return(line);


		} else if (tniCode == _MC_ICODE_END) {
			// We were explicitly looking for the END
			// If we get here, we're not looking for an 'END' keyword
			imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_EXPECTED_END);
			return(NULL);


		} else {
			// Expected something to be matched, but not sure what it is
			imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_UNMATCHED_BLOCK);
			return(NULL);
		}
	}

	SOssLine* iimc_assemblyPass0ScanForBlocksEnd(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd)
	{
		if (pbsd->comp->iCode == _MC_ICODE_END)
			return((SOssLine*)line);		// We're good, matched up

		// If we get here, we're not looking for an end
		imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_UNMATCHED_BLOCK);
		return(NULL);
	}

	SOssLine* iimc_assemblyPass0ScanForBlocksColon(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd)
	{
		_isSLineInfo*	lli;


// TODO:  this algorithm needs to be completely refactored due to the use of casks
_asm int 3;
		// Make sure we're where we should be
		if (tniCode != _MC_ICODE_END)
		{
			// We're not looking for the end, so this label is out in the middle of space
			// If we get here, we're not looking for an end
			imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_LABEL_OUTSIDE_OF_BLOCK);
			return(NULL);
		}
		// If we get here, we're in a block
		pbsd->llab = (SLabelInfo*)vvm_SEChain_append(&(*block)->labels, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SLabelInfo), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);
		if (!pbsd->llab)
		{
			// Memory error
			imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_ERROR_ALLOCATING_MEMORY);
			return(NULL);
		}
		// Record this line
		pbsd->llab->blockAssociation	= *block;
		pbsd->llab->comp				= pbsd->comp;

		// Mark this line as being completed, as it will be explicitly processed as a label line without further line-by-line processing
		lli = (_isSLineInfo*)line->extra;
		lli->completed = true;

		// Indicate success
		return(line);
	}

	SOssLine* iimc_assemblyPass0ScanForBlocksDllFuncDef(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd)
	{
// TODO:  this algorithm needs to be completely refactored due to the use of casks
_asm int 3;
		if (!*block || (*block)->compTrigger->iCode != _MC_ICODE_DLL)
		{
			// A DLL_FUNCTION was found where it should not be
			imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_ERROR_UNEXPECTED_KEYWORD);
			return(NULL);
		}
		// If we get here, we're good
		pbsd->ldfi = (SDllFuncInfo*)vvm_SEChain_append(&(*block)->dllFuncs, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SDllFuncInfo), _COMMON_START_END_BLOCK_SIZE, NULL);
		if (!pbsd->ldfi)
		{
			// Memory error
			imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_ERROR_ALLOCATING_MEMORY);
			return(NULL);
		}
		// If we get here, we have allocated our entry
		pbsd->ldfi->comp = pbsd->comp;

		// Indicate success
		return(line);
	}

	SOssLine* iimc_assemblyPass0ScanForBlocksPipeSign(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd)
	{
		_isSLineInfo*	lli;


// TODO:  this algorithm needs to be completely refactored due to the use of casks
_asm int 3;
		// Make sure the environment is sane
		if (pbsd->ldfi)
		{
			// Adding to the pipe data here
			pbsd->lpip = (SPipeInfo*)vvm_SEChain_append(&pbsd->ldfi->pipeData, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SPipeInfo), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);

		} else if (pbsd->llOkayToAddPipeDataToBlock) {
			// We are adding to the block
			pbsd->lpip = (SPipeInfo*)vvm_SEChain_append(&(*block)->pipeData, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SPipeInfo), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);

		} else {
			// "What we have here is a failure to communicate" :-)
			// A DLL_FUNCTION was found where it should not be
			imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_SYNTAX_ERROR);
			return(NULL);
		}

		// Check our memory allocation
		if (!pbsd->lpip)
		{
			// Memory error
			imc_appendError(&pbsd->tsf->errors, line, pbsd->comp, IDS_ERROR_ALLOCATING_MEMORY);
			return(NULL);
		}
		// When we get here, we have our pipe entry
		pbsd->lpip->comp = pbsd->comp;

		// Mark this line as being completed, as it will be explicitly processed as a pipe-sign line without further line-by-line processing
		lli = (_isSLineInfo*)line->extra;
		lli->completed = true;

		// Indicate success
		return(line);
	}




//////////
//
// Parse the block starts and labels to make sure they're valid
//
//////
	bool iimc_assemblyPass2ParseBlockStartsAndLabels(SAssembly* ta, SSourceFile* tsf)
	{
		SBlock*	block;


// TODO:  this algorithm needs to be completely refactored due to the use of casks
_asm int 3;
		// Parse the block starts and stops, labels and pipe-signs
		block = (SBlock*)tsf->blocks.root->ptr;
		while (block)
		{

			// See what the block definition is
			switch (block->compTrigger->iCode)
			{

				case _MC_ICODE_DSNIP:
				//////////
				// This DSNIP definition is not allowed explicitly to be defined at runtime.
				// Only implicitly through the DSNIP_Bxml syntax.  However, in saved states
				// of a captured-to-disk running VM, the DSNIP is valid.
				//////
					imc_appendError(&tsf->errors, block->compTrigger->line, block->compTrigger, IDS_ERROR_DSNIP_NOT_ALLOWED_AT_COMPILE_TIME);
					return(false);
					break;

				case _MC_ICODE_DLL:
					// Process the DSNIP_DLL source line, as well as any DLL_FUNCTION lines within (and their pipe-signs)
					if (!iimc_assemblyPass2ParseBlockStartsAndLabelsDsnipDll(ta, tsf, block))
						return(false);
					break;

				case _MC_ICODE_BXML:
					// Process the DSNIP_Bxml source line, as well as the required pipe-sign PROTOTYPE line within
					if (!iimc_assemblyPass2ParseBlockStartsAndLabelsDsnipBxml(ta, tsf, block))
						return(false);
					break;

				case _MC_ICODE_SNIP:
					// Process the FUNCTION / SNIP source line, as well as any pipe-signs and labels
					if (!iimc_assemblyPass2ParseBlockStartsAndLabelsSnip(ta, tsf, block))
						return(false);
					break;

				default:
					imc_appendError(&tsf->errors, block->compTrigger->line, block->compTrigger, IDS_ERROR_INTERNAL_COMPILER_ERROR);
					return(false);
			}

			// Move to the next block
			block = (SBlock*)block->ll.next;
		}
		// When we get here, we're done without error
		return(true);
	}




//////////
//
// Parses the dynamic dll snippet declaration source code line.
//
// Expecting a format like this, and includes DLL_FUNCTION declarations and their pipe-signs:
//
//		DSNIP_DLL "/path/to/user32.dll"
//
//			DLL_FUNCTION SendMessage
//				|PARAMS		u32 hwnd, u32 msg, u32 w, u32 l
//				|RETURNS	u32
//
//////
	bool iimc_assemblyPass2ParseBlockStartsAndLabelsDsnipDll(SAssembly* ta, SSourceFile* tsf, SBlock* block)
	{
		SOssComp*	comp;
		SDynSnip*	dsnip;


// TODO:  this algorithm needs to be completely refactored due to the use of casks
_asm int 3;
		// The next component after block->compTrigger must be a single/double-quoted text component
		comp = (SOssComp*)block->compTrigger->ll.next;
		if (!comp || (comp->iCode != _MC_ICODE_SINGLE_QUOTED_TEXT && comp->iCode != _MC_ICODE_DOUBLE_QUOTED_TEXT))
		{
			imc_appendError(&tsf->errors, block->compTrigger->line, block->compTrigger, IDS_ERROR_EXPECTED_QUOTED_PATHNAME);
			return(false);
		}
		// If we get here, we have at least one pathname
		dsnip = block->dsnip;
// TODO:  working here
		return(false);
	}




//////////
//
// Parses the dynamic bxml snippet declaration source code line.
//
// Expecting a format like this, and includes pipe-signs:
//
//		DSNIP_Bxml "d:\path\to\runtime\loadable.bxml", "loadable.bxml"
//			|PROTOTYPE "c:\path\to\devtime\loadable.bxml"
//
//////
	bool iimc_assemblyPass2ParseBlockStartsAndLabelsDsnipBxml(SAssembly* ta, SSourceFile* tsf, SBlock* block)
	{
// TODO:  working here
		return(false);
	}




//////////
//
// Parses the function/snippet declaration source code line.
//
// Expecting a format like this:
//
//		FUNCTION test_uadd
//			|PARAMS  u32 p1, u32 p2, u32 p3, u32 p4, u32 p5
//			|RETURNS u32 r1, u32 r2
//			|LOCALS  u32 lnI, u32 lnJ, u32 k
//		:@@
//		:foo
//
//////
	bool iimc_assemblyPass2ParseBlockStartsAndLabelsSnip(SAssembly* ta, SSourceFile* tsf, SBlock* block)
	{
// TODO:  working here
		return(false);
	}




//////////
//
// Called to verify that the integer value found is prefixed with a dot, and if so it merges all
// three into the indicated type.
//
//////
	bool iimc_checkDotPrefix(SOssCompCallback* cb)
	{
		SOssComp* compPrev;


		// Make sure our environment is sane
		if (cb->comp && cb->comp->ll.prev)
		{
			// Get the previous component
			compPrev = (SOssComp*)cb->comp->ll.prev;

			// Is it prefixed with a period?
			if (compPrev->iCode == _MC_ICODE_DOT && compPrev->start + 1 == cb->comp->start)
				return(true);		// Yes
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to verify that the integer value found is prefixed with a dot, and if so it merges all
// three into the indicated type.
//
//////
	void iimc_processDotPrefix(SOssCompCallback* cb)
	{
		SOssComp*	comp;
		SOssComp*	compPrev;


		// Make sure our environment is sane
		if (cb->comp && cb->comp->ll.prev)
		{
			// Is it prefixed with a period?
			comp		= cb->comp;
			compPrev	= (SOssComp*)comp->ll.prev;
			
			// Convert it to a single operator
			cb->mergeComps(compPrev, compPrev->line, 2, cb->iCode);

			// Indicate the new component to continue working on
			cb->comp = compPrev;
		}

	}