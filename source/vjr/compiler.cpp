//////////
//
// /libsf/source/vjr/compiler.cpp
//
//////
// Version 0.30
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









//////////
//
// Compiles a VXB-- source code block.  If tlEditAndContinue is true, then only those
// lines which have differing line->compilerInfo->sourceCode and line->sourceCode are
// compiled.  If the current debug environment is operating on this line, the debugger
// will need to take special note about the before and after sub-instructions to
// to determine if the current location can be maintained, or if the line needs to
// start over.
//
//////
	u32 compile_Vxbmm(SEditChainManager* codeBlock_, SCompileContext* ccData_, bool tlEditAndContinue_)
	{
		SCompileVxbmmContext	cvc;


		//////////
		// Initialize our compile context to 0s
		//////
			memset(&cvc, 0, sizeof(SCompileVxbmmContext));
			cvc.codeBlock		= codeBlock_;
			cvc.ccData			= ccData_;
			cvc.editAndContinue	= tlEditAndContinue_;

			if (!cvc.ccData)
				cvc.ccData = &cvc.ccDataLocal;

			memset(cvc.ccData, 0, sizeof(SCompileContext));


		//////////
		// Make sure our environment is sane
		//////
			if (cvc.codeBlock && cvc.codeBlock->ecFirst)
			{
				// Before compilation, we need to remove any dependencies on things that have changed
				iiCompile_Vxbmm_precompile(&cvc);

				// Physically compile
				iiCompile_Vxbmm_compile(&cvc);
			}


		//////////
		// Indicate our result
		//////
			return(cvc.ccData->sourceLines);
	}




//////////
//
// Called before compilation to remove any references to any lines that have
// changed, so all of those lines will be recompiled as well.  The references
// are things like FUNCTION definitions, PARAMS, LOBJECT, LPARAMETERS, LOCALS,
// RETURNS, ADHOC, anything that defines functions or variables.  As each of
// those are removed a list is built, and then each source code line is searched
// exhaustively to find out if any component on those lines references the now
// removed variable.  If so, it will be marked for recompilation as well so it
// references what will become the new function, new adhoc, or new variable.
//
//////
	void iiCompile_Vxbmm_precompile(SCompileVxbmmContext* cvc)
	{
		if (cvc->editAndContinue)
		{
			// Determine what will now be stale in this code block, and needs recompiling.

		} else {
			// Everything is stale.
		}
	}




//////////
//
// Called to physically compile each line of source code.
//
//////
	void iiCompile_Vxbmm_compile(SCompileVxbmmContext* cvc)
	{
		// Begin compiling
		cvc->currentFunction	= &cvc->codeBlock->firstFunction;
		cvc->currentAdhoc		= NULL;
		cvc->line				= cvc->codeBlock->ecFirst;
		while (cvc->line)
		{
			// Increase our line count
			++cvc->ccData->sourceLines;

			// Make sure we have a compilerInfo object
			if (!cvc->line->compilerInfo)
				cvc->line->compilerInfo = iCompiler_allocate(cvc->line);

			// Is there anything to parse on this line?
			if (cvc->line->sourceCode && cvc->line->sourceCodePopulated > 0)
			{
				//////////
				// Determine if this line needs compiled
				//////
					if (cvc->editAndContinue)
					{
						// We are in edit-and-continue mode, which means we only process this line
						// if its contents have changed.  Otherwise, we use what was already compiled.
						if (!cvc->line->compilerInfo->sourceCode || cvc->line->forceRecompile || !cvc->line->compilerInfo->firstComp)
						{
							// This line has not yet been compiled.
							// This line needs to be compiled.
							cvc->llProcessThisLine = true;

						} else if (cvc->line->sourceCode->length != cvc->line->compilerInfo->sourceCode->length) {
							// The lines are no longer the same length.  Something has changed.
							// This line needs to be compiled.
							cvc->llProcessThisLine = true;

						} else if (iDatum_compare(cvc->line->sourceCode, cvc->line->compilerInfo->sourceCode) != 0) {
							// The source code contents have changed.
							// This line needs to be compiled.
							cvc->llProcessThisLine = true;

						} else if (cvc->line->compilerInfo->warnings || cvc->line->compilerInfo->errors) {
							// The source code line has warnings or errors, it needs recompiled
							cvc->llProcessThisLine = true;

						} else {
							// The lines are identical.  Does not need re-compiled.
							cvc->llProcessThisLine = false;
						}

					} else {
						cvc->llProcessThisLine = true;
					}


				//////////
				// Should we process this line?
				//////
					if (!cvc->llProcessThisLine)
					{
						if (cvc->editAndContinue)
						{
							// In an edit-and-continue environment, we have to track functions so we maintain the
							// current function we are in, even if the source code for those functions didn't change.
							if (cvc->line->compilerInfo->firstComp)
							{
								// We need to track certain things through on non-compiled lines

							//////////
							// FUNCTION
							//////
								if (cvc->line->compilerInfo->firstComp->iCode == _ICODE_FUNCTION)
								{
									// We've moved into another function
									cvc->currentFunction = NULL;
									cvc->func = &cvc->codeBlock->firstFunction;
									while (cvc->func)
									{
										// Is this the function relating to this source code line?
										if (cvc->func->firstLine == cvc->line)
										{
											cvc->currentFunction = cvc->func;		// We found our match
											break;
										}

										// Move to next 
										cvc->func = cvc->func->next;
									}
									if (!cvc->currentFunction)
									{
										// We didn't find a match for the indicated function.  Something has changed.
										// We need a full recompile to sort it out at this point.
										iLine_appendError(cvc->line, _ERROR_CONTEXT_HAS_CHANGED,		(s8*)cgcContextHasChanged,		cvc->line->compilerInfo->firstComp->start, cvc->line->compilerInfo->firstComp->length);
										iLine_appendError(cvc->line, _ERROR_FULL_RECOMPILE_REQUIRED,	(s8*)cgcFullRecompileRequired,	cvc->line->compilerInfo->firstComp->start, cvc->line->compilerInfo->firstComp->length);
									}

							//////////
							// ADHOC
							//////
								} else if (cvc->line->compilerInfo->firstComp->iCode == _ICODE_ADHOC) {
									// We've moved into an adhoc
									if (cvc->currentFunction)
									{
										// Iterate to see where this adhoc is
										cvc->adhoc = cvc->currentFunction->firstAdhoc;
										while (cvc->adhoc)
										{
											// Is this the function relating to this source code line?
											if (cvc->adhoc->firstLine == cvc->line)
											{
												// We found our match
												cvc->currentAdhoc = cvc->adhoc;
												break;
											}

											// Move to next 
											cvc->adhoc = cvc->adhoc->next;
										}

									} else {
										// We're not in a function and they're adding an ADHOC.
										// Unexpected command
										iLine_appendError(cvc->line, _ERROR_UNEXPECTED_COMMAND, (s8*)cgcUnexpectedCommand, cvc->line->compilerInfo->firstComp->start, cvc->line->compilerInfo->firstComp->length);
									}

								} else if (cvc->line->compilerInfo->firstComp->iCode == _ICODE_ENDADHOC) {
									// We've moved out of the adhoc
									cvc->currentAdhoc = NULL;
								}
							}
						}

					} else {
						// Note:  This while block exists so it can be exited politely with break.
						// Note:  It does not loop.
						while (1)
						{
							//////////
							// We need to clear out anything from any prior compile
							//////
								iComps_removeAll(cvc->line);
								iCompileNote_removeAll(&cvc->line->compilerInfo->warnings);
								iCompileNote_removeAll(&cvc->line->compilerInfo->errors);
								iNode_politelyDeleteAll(&cvc->line->compilerInfo->firstNode, true, true, true, true, true, true);


							//////////
							// Convert raw source code to known character sequences
							//////
								iComps_translateSourceLineTo(&cgcFundamentalSymbols[0], cvc->line);
								if (!cvc->line->compilerInfo->firstComp)
								{
									++cvc->ccData->blankLines;
									break;		// Nothing to compile on this line
								}
								cvc->comp = cvc->line->compilerInfo->firstComp;


							//////////
							// If it's a line comment, we don't need to process it
							//////
								if (cvc->line->compilerInfo->firstComp->iCode == _ICODE_COMMENT || cvc->line->compilerInfo->firstComp->iCode == _ICODE_LINE_COMMENT)
								{
									++cvc->ccData->commentLines;
									break;
								}


							//////////
							// Perform fixups
							//////
								iComps_removeStartEndComments(cvc->line);			// Remove /* comments */
								iComps_fixupNaturalGroupings(cvc->line);			// Fixup natural groupings [_][aaa][999] becomes [_aaa999], [999][.][99] becomes [999.99], etc.
								iComps_removeWhitespaces(cvc->line);				// Remove whitespaces [use][whitespace][foo] becomes [use][foo]


							//////////
							// Translate sequences to known keywords
							//////
								iComps_translateToOthers(&cgcKeywordKeywords[0], cvc->line);


							//////////
							// Process this line based upon what it is
							//////
								if (cvc->comp->iCode == _ICODE_FUNCTION)
								{
									// They are adding another function
									cvc->currentFunction = iiComps_decodeSyntax_function(cvc);


								} else if (cvc->comp->iCode == _ICODE_ADHOC) {
									// They are adding an adhoc function
									iiComps_decodeSyntax_adhoc(cvc);


								} else if (cvc->comp->iCode == _ICODE_PARAMS) {
									// They are adding parameters
									// Process the PARAMS line
// TODO:  working here
									iiComps_decodeSyntax_params(cvc);


								} else if (cvc->comp->iCode == _ICODE_LOBJECT) {
									// They are adding parameters via an object
									// Process the LOBJECT line
// TODO:  working here
									iiComps_decodeSyntax_lobject(cvc);


								} else if (cvc->comp->iCode == _ICODE_LPARAMETERS) {
									// They are adding lparameters
									// Process the LPARAMETERS line
// TODO:  working here
									iiComps_decodeSyntax_lparameters(cvc);


								} else if (cvc->comp->iCode == _ICODE_RETURNS) {
									// They are specifying returns
									// Process the RETURNS line
// TODO:  working here
									iiComps_decodeSyntax_returns(cvc);


								} else {
									// Translate into operations
									iiComps_xlatToNodes(cvc->line, cvc->line->compilerInfo);
									// Note:  Right now, line->errors and line->warnings have notes attached to them about the compilation of this line
								}


							// All done with this line
							break;
						}
					}
				}


			//////////
			// Move to the next line
			//////
				cvc->line = cvc->line->next;
		}
	}




//////////
//
// Called to post-compile, primarily to flag variables that are not referenced
// 
//////
	void iiCompile_Vxbmm_postcompile(SEditChainManager* codeBlock, SCompileContext* ccData, bool tlEditAndContinue)
	{
	}




//////////
//
// Called to handle a FUNCTION source code line.
//
// Syntax:	FUNCTION cFunctionName
//
//////
	SFunction* iiComps_decodeSyntax_function(SCompileVxbmmContext* cvc)
	{
		SComp*		comp;
		SComp*		compName;
		SFunction*	func;


		// Make sure our environment is sane
		func = NULL;
		if (cvc->codeBlock && cvc->line && cvc->line->compilerInfo)
		{
			// The syntax must be [FUNCTION][cFunctionName]
			if ((comp = cvc->line->compilerInfo->firstComp) && comp->iCode == _ICODE_FUNCTION)
			{
				// [FUNCTION]
				if (comp->ll.next)
				{
					// [FUNCTION][something after]
					if ((compName = (SComp*)comp->ll.next) && (compName->iCode == _ICODE_ALPHA || compName->iCode == _ICODE_ALPHANUMERIC))
					{
						// [FUNCTION][cFuncionName]
// TODO:  We need to do a lookup on this name to see if we're replacing a function, or adding a new one

						// Create the new function
						func = iFunction_allocate(compName);

						// Indicate information about this function
						func->firstLine	= cvc->line;
						func->lastLine	= cvc->line;

// TODO:  Needs added to the current function chain

						// Generate warnings for ignored components if any appear after
						iComp_reportWarningsOnRemainder((SComp*)compName->ll.next, _WARNING_SPURIOUS_COMPONENTS_IGNORED, (s8*)cgcSpuriousIgnored);
					}
				}
			}
		}

		// Indicate our status
		return(func);
	}




//////////
//
// Called to handle an ADHOC source code line.
//
// Syntax:	ADHOC cAdhocName
//
//////
	SFunction* iiComps_decodeSyntax_adhoc(SCompileVxbmmContext* cvc)
	{
		SComp*		comp;
		SComp*		compName;
		SFunction*	adhoc;


		// Make sure our environment is sane
		adhoc = NULL;
		if (cvc->codeBlock && cvc->line && cvc->line->compilerInfo)
		{
			// The syntax must be [ADHOC][cAdhocName]
			if ((comp = cvc->line->compilerInfo->firstComp) && comp->iCode == _ICODE_ADHOC)
			{
				// [ADHOC]
				if (comp->ll.next)
				{
					// [ADHOC][something after]
					if ((compName = (SComp*)comp->ll.next) && (compName->iCode == _ICODE_ALPHA || compName->iCode == _ICODE_ALPHANUMERIC))
					{
						// [ADHOC][cAdhocName]
// TODO:  We need to do a lookup on this name to see if we're replacing an adhoc, or adding a new one

						// Create the new adhoc
						adhoc = iFunction_allocate(compName);

						// Indicate information about this adhoc
						adhoc->firstLine	= cvc->line;
						adhoc->lastLine		= cvc->line;

// TODO:  Needs added to the current function

						// Generate warnings for ignored components if any appear after
						iComp_reportWarningsOnRemainder((SComp*)compName->ll.next, _WARNING_SPURIOUS_COMPONENTS_IGNORED, (s8*)cgcSpuriousIgnored);
					}
				}
			}
		}

		// Indicate our status
		return(adhoc);
	}




void iiComps_decodeSyntax_params(SCompileVxbmmContext* cvc)
{
// TODO:  write this function
}

void iiComps_decodeSyntax_lobject(SCompileVxbmmContext* cvc)
{
// TODO:  write this function
}

void iiComps_decodeSyntax_lparameters(SCompileVxbmmContext* cvc)
{
// TODO:  write this function
}

void iiComps_decodeSyntax_returns(SCompileVxbmmContext* cvc)
{
// TODO:  write this function
}




//////////
//
// Translates components into a sequence of sub-instruction operations.
//
/////
	bool iiComps_xlatToNodes(SEditChain* line, SCompiler* compiler)
	{
		SComp*		comp;
		SComp*		compLast;
		SNode*		nodeActive;			// Current active node


		// Iterate through every component building the operations as we go
		comp		= line->compilerInfo->firstComp;
		compLast	= comp;
		nodeActive	= iNode_create(&compiler->firstNode, NULL, 0, NULL, NULL, NULL, NULL, NULL);
		while (comp)
		{
			//////////
			// If it's an operand we're looking for, then we process it
			//////
				switch (comp->iCode)
				{
					// (
					case _ICODE_PARENTHESIS_LEFT:
						nodeActive = iiComps_xlatToNodes_parenthesis_left(&compiler->firstNode, nodeActive, comp);
						break;

					// )
					case _ICODE_PARENTHESIS_RIGHT:
						nodeActive = iiComps_xlatToNodes_parenthesis_right(&compiler->firstNode, nodeActive, comp);
						break;

					// [
					case _ICODE_BRACKET_LEFT:
						break;

					// ]
					case _ICODE_BRACKET_RIGHT:
						break;

					// {
					case _ICODE_BRACE_LEFT:
						break;

					// }
					case _ICODE_BRACE_RIGHT:
						break;

					// <<
					case _ICODE_SHIFT_LEFT:
						break;

					// >>
					case _ICODE_SHIFT_RIGHT:
						break;

					// ^ or **
					case _ICODE_EXPONENT:
						break;

					// ++
					case _ICODE_PLUS_PLUS:
						break;

					// --
					case _ICODE_MINUS_MINUS:
						break;

					// *
					case _ICODE_ASTERISK:
						break;

					// /
					case _ICODE_SLASH:
						break;

					// %
					case _ICODE_PERCENT_SIGN:
						break;

					// +
					case _ICODE_PLUS:
						break;

					// -
					case _ICODE_HYPHEN:
						break;

					// $
					case _ICODE_FOUND_IN:
						break;

					// !$
					case _ICODE_NOT_FOUND_IN:
						break;

					// NOT or !
					case _ICODE_NOT:
					case _ICODE_EXCLAMATION_MARK:
						break;

					// AND
					case _ICODE_AND:
						break;

					// OR
					case _ICODE_OR:
						break;

					// <<=
					case _ICODE_SHIFT_LEFT_ASSIGNMENT:
						break;

					// >>=
					case _ICODE_SHIFT_RIGHT_ASSIGNMENT:
						break;

					// =
					case _ICODE_EQUAL_SIGN:
						break;

					// <
					case _ICODE_LESS_THAN:
						break;

					// >
					case _ICODE_GREATER_THAN:
						break;

					// <>, #, !=
					case _ICODE_NOT_EQUAL:
					case _ICODE_POUND_SIGN:
						break;

					// <= or =<
					case _ICODE_LESS_THAN_OR_EQUAL_TO:
						break;

					// >= or =>
					case _ICODE_GREATER_THAN_OR_EQUAL_TO:
						break;

					// ==
					case _ICODE_EXACTLY_EQUAL_TO:
						break;

					// FLAGS
					case _ICODE_FLAGS:
						break;
				}


			//////////
			// Are we in error?  If so, we stop compiling this line.
			//////
				if (nodeActive->op.op_type == _OP_TYPE_NULL)
				{
					// We are in error
					return(false);
				}


			//////////
			// Move to next component
			//////
				compLast	= comp;
				comp		= (SComp*)comp->ll.next;
		}

		// If we get here everything was processed properly
		return(true);
	}




//////////
//
// Processes the left parenthesis.  Takes an existing item like this (note the [?] is the active node):
//     x = (a + b) + c
//      / \
//     x  [?]
//
// And translates it into this:
//     x = (a + b) + c
//      / \
//     x   (
//          \
//          [?]
//
//////
	SNode* iiComps_xlatToNodes_parenthesis_left(SNode** root, SNode* active, SComp* comp)
	{
		SNode*		node;
		SVariable*	var;


		// Insert a parenthesis node at the active node, and direct the active node to the right
		node = iNode_insertBetween(root, active->parent, active, _NODE_PARENT, _NODE_RIGHT);
		if (node)
		{
			//////////
			// Update its operation to our parenthesis
			//////
				node->op.op_type	= _OP_TYPE_PARENTHESIS_LEFT;
				node->op.comp		= comp;


			//////////
			// Indicate we'll need a temporary variable for our result
			//////
				var = iVariable_create(_VAR_TYPE_NULL, NULL);
				if (var)
				{
					// Append the temporary variable
					iOp_setVariable_scoped(&node->op, var, true);

				} else {
					// Internal compile error
					iComp_appendError(comp, _ERROR_OUT_OF_MEMORY, (s8*)cgcOutOfMemory);
					iOp_setNull(&node->op);
				}
		}

		// Indicate our status
		return(node);
	}




//////////
//
// Process the right parenthesis.
//
//////
	SNode* iiComps_xlatToNodes_parenthesis_right(SNode** root, SNode* active, SComp* comp)
	{
// TODO:  Working here
		return(NULL);
	}
;




//////////
//
// Called to remove all components for this line
//
//////
	void iComps_removeAll(SEditChain* line)
	{
		if (line && line->compilerInfo)
		{
			// Delete all components
			iLl_deleteNodeChain((SLL**)line->compilerInfo->firstComp);

			// Reset the pointer
			line->compilerInfo->firstComp = NULL;
		}
	}




//////////
//
// Called to search the SAsciiCompSearcher format list of text item keywords.
//
// Note:  If the length column of the SAsciiCompSearcher entry is negative, it is a case-sensitive search.
//
// Returns:
//		The first component created (if any)
//
//////
	SComp* iComps_translateSourceLineTo(SAsciiCompSearcher* tsComps, SEditChain* line)
	{
		s32						lnI, lnMaxLength, lnStart, lnLength, lnLacsLength;
		bool					llSigned, llResult;
		SComp*					compFirst;
		SComp*					compLast;
		SComp*					comp;
		s8*						lcData;
		SAsciiCompSearcher*		lacs;
		SCompCallback			lccb;


		// Make sure the environment's sane
		compFirst = NULL;
		if (tsComps && line)
		{
			// Scan starting at the beginning of the line
			lcData = line->sourceCode->data;

			// Iterate through every byte identifying every component we can
			compLast	= NULL;
			lnMaxLength	= line->sourceCodePopulated;
			for (lnI = 0; lnI < lnMaxLength; )
			{
				// Search through the tsComps list one by one
				for (	lacs = tsComps;
						lacs->length != 0;
						lacs++)
				{
					// Find out our signed status and get normalized length
					llSigned		= (lacs->length < 0);
					lnLacsLength	= abs(lacs->length);

					// Process through this entry
					if ((!lacs->firstOnLine || lnI == 0) && lnLacsLength <= lnMaxLength - lnI)
					{
						// There is enough room for this component to be examined
						// See if it matches
						if (iTranslateToCompsTest((s8*)lacs->keyword, lcData + lnI, lacs->length) == 0)
						{
							// It matches
							// Is there a secondary validation?
							if (lacs->_validate)
							{
								// Yes, make sure it validates there as well
								lccb.text					= lcData + lnI;
								lccb.length					= lacs->length;
								lccb.iCode					= lacs->iCode;
								lccb._insertCompByComp		= NULL;
								lccb._insertCompByParams	= NULL;
								lccb._deleteComps			= NULL;
								lccb._cloneComps			= NULL;
								lccb._mergeComps			= NULL;

								// Perform the validation
								llResult = lacs->validate(&lccb);

							} else {
								// If there is no extra validation, we just pass through
								llResult = true;
							}
							
							// Are we still good?
							if (llResult)
							{
								// mark its current condition
								lnStart		= lnI;
								lnLength	= lnLacsLength;
								// See if it's allowed to repeat
								if (lacs->repeats)
								{
									while (	lnStart + lnLength + lnLacsLength <= lnMaxLength
											&& iTranslateToCompsTest((s8*)lacs->keyword, lcData + lnStart + lnLength, lacs->length) == 0)
									{
										// We found another repeated entry
										lnLength += lnLacsLength;
									}
									// When we get here, every repeated entry has been found (if any)
								}
								// When we get here, we have the starting point and the full length (including any repeats)


								//////////
								// Allocate this entry
								///////
									comp = (SComp*)iLl_appendNewNode((SLL**)&line->compilerInfo->firstComp, (SLL*)compLast, NULL, (SLL*)compLast, iGetNextUid(), sizeof(SComp));


								//////////
								// Populate the component with specified information
								//////
									//
									//////
										if (comp)
										{
											// Update the back links
											if (compLast)	compLast->ll.next = (SLL*)comp;			// Previous one points to this one
											comp->ll.prev	= (SLL*)compLast;						// This one points back to previous one

											// Update the component's information
											comp->line		= line;
											comp->start		= lnStart;
											comp->length	= lnLength;
											comp->iCode		= lacs->iCode;

											// Update our first component (if it's not updated already)
											if (!compFirst)	compFirst = comp;

											// All done
											compLast = comp;
										}
									//////
									//
								//////
								// END
								//////////


								//////////
								// Move beyond this entry, and continue on search again afterward
								//////
									lnI += lnLength;
									break;		// leaves lnJ loop, continues with lnI loop
							}
						}
						//else it doesn't match, this isn't a good find
					}
				}
				// When we get here, we've processed through everything here
				if (lacs->length == 0)
					lnI++;			// We didn't find anything at that character, continue on to the next
			}
			// When we get here, lnI has been updated to its new location,
			// and any indicated components have been added
		}
		// Return the count
		return(compFirst);
	}




//////////
//
// Called to search the already parsed SAsciiCompSearcher list of components, looking for
// combinations which relate to other component types.  The primary translations here are
// alpha/alphanumeric/numeric forms to other forms.
//
//////
	bool iComps_translateToOthers(SAsciiCompSearcher* tacs, SEditChain* line)
	{
		bool			llResult;
		s32				lnTacsLength;
		SComp*			comp;
		SCompCallback	lccb;


		// Make sure the environment is sane
		llResult = false;
		if (tacs && line)
		{
			// Grab our pointers into recognizable thingamajigs
			comp = line->compilerInfo->firstComp;

			// Iterate through this item to see if any match
			for (/* tacs is initialize above */; tacs->length != 0; tacs++)
			{
				// Grab the normalized length
				lnTacsLength = abs(tacs->length);

				// We only test if they're the same length
				if (lnTacsLength == comp->length || (tacs->repeats && lnTacsLength <= comp->length))
				{
					// We only test if this item is not the first item on line, or if must be the first
					// item on the line, then this component must be the first component on the line.  Simple, yes? :-)
					if (!tacs->firstOnLine || comp->start == 0)
					{
						// Physically conduct the exact comparison
						if (iComps_translateToOthers_test((s8*)tacs->keyword, comp->line->sourceCode->data + comp->start, tacs->length) == 0)
						{
							// This is a match
							// Is there a secondary test?
							if (tacs->_validate)
							{
								// Yes, make sure it validates there as well
								lccb.comp					= comp;
								lccb.length					= 0;
								lccb.iCode					= tacs->iCode;
								// Setup the functions the custom handler would require
								lccb._insertCompByComp		= (u64)&iiComps_xlatToOthersCallback__insertCompByCompCallback;
								lccb._insertCompByParams	= (u64)&iiComps_xlatToOthersCallback__insertCompByParamsCallback;
								lccb._deleteComps			= (u64)&iiComps_xlatToOthersCallback__deleteCompsCallback;
								lccb._cloneComps			= (u64)&iiComps_xlatToOthersCallback__cloneCompsCallback;
								lccb._mergeComps			= (u64)&iiComps_xlatToOthersCallback__mergeCompsCallback;

								// Perform the validation
								llResult = tacs->validate(&lccb);

							} else {
								// No, just let it fall through
								llResult = true;
							}

							if (llResult)
							{
								// Convert it, translate it, whatever you want to call it, just make it be the new code, per the user's request, got it? :-)
								comp->iCode = tacs->iCode;
								// All done with this component
								break;
							}
						}
					}
				}
			}

		}
		// We always simulate a false condition so we'll keep receiving each item
		return(false);
	}




//////////
//
// Search the haystack for the needle, the haystack can be tupels, as in "_az" meaning
// (is it between "a" and "z" inclusive?)  To set this condition, use a length of 1,
// a leading "_" in tcHaystack, and two characters (one of which must NOT be NULL) after.
// Examples:
//		_az		= lower-case a to z inclusive
//		_AZ		= upper-case a to z inclusive
//		_09		= numeric 0 to 9 inclusive
//
// Returns:
//		0		= matches
//		!0		= does not tmach
//
//////
	s32 iComps_translateToOthers_test(s8* tcHaystack, s8* tcNeedle, s32 tnLength)
	{
		u32		lnI;
		bool	llSigned;


		// Make sure our environment is sane
		if (tnLength != 0)
		{
			// See if we're a signed or unsigned compare
			if (tnLength < 0)
			{
				// Case sensitive compare
				tnLength	= -tnLength;
				llSigned	= true;

			} else {
				// Case insensitive compare
				llSigned = false;
			}

			// See if we're looking for a tuple, or a regular compare
			if (tcHaystack[0] == '_' && tnLength == 1)
			{
				// It's an explicit match of a range (this is ALWAYS subject to case as it is an explicit range)
				for (lnI = 1; tcHaystack[lnI] != 0 || tcHaystack[lnI + 1] != 0; lnI += 2)
				{
					//		within the range low			.........			up to the range high
					if (tcNeedle[0] >= tcHaystack[lnI]			&&		tcNeedle[0] <= tcHaystack[lnI + 1])
						return(0);		// It's a match, needle is in the range
				}
				// Not a match, will fall through to below

			} else {
				// Just a regular compare
				if (llSigned)	return(  memcmp(tcHaystack, tcNeedle, tnLength));
				else			return(_memicmp(tcHaystack, tcNeedle, tnLength));
			}
		}
		// If we get here, no match
		return(-1);
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
	void* vvm_SEChain_searchByCallback(SStartEnd* ptrSE, SStartEndCallback* cb)
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
// Searches forward to find the indicated component by the indicated type.
//
// Returns:
//		The matching component
//		If NULL, the compLastScanned indicates the last component that was searched where it wasn't found
//
//////
	SComp* iComps_findNextBy_iCode(SComp* comp, u32 tniCode, SComp** compLastScanned)
	{
		// Initially indicate failure
		if (compLastScanned)
			*compLastScanned = comp;

		// Continue while the environment is sane
		while (comp)
		{
			// Store the component we're scanning
			if (compLastScanned)
				*compLastScanned = comp;

			// See if this is it
			if (comp->iCode == tniCode)
				break;		// It is, we're done

			// Move to the next component
			comp = (SComp*)comp->ll.next;
		}
		// When we get here, we either found it or not
		// Store our results
		return(comp);
	}




//////////
//
// Searches for the next non-indicated component, including itself
//
//////
	SComp* iComps_skipPast_iCode(SComp* comp, u32 tniCode)
	{
		while (comp && comp->iCode == tniCode)
		{
			// Move to next component
			comp = (SComp*)comp->ll.next;
		}
		// When we get here, we're sitting on either no valid component, or the one which does not match the specified type
		return(comp);
	}




//////////
//
// Called to combine two components into one.  If tnNewICode is > 0 then the
// iCode is updated as well.
//
//////
	u32 iComps_combineNextN(SComp* comp, u32 tnCount, s32 tnNewICode)
	{
		u32		lnCount;
		SComp*	compNext;


		// Make sure our environment is sane
		if (comp)
		{
			//////////
			// Combine the next N items
			//////
				for (lnCount = 0; lnCount < tnCount; lnCount++)
				{
					// Grab the next component
					compNext = (SComp*)comp->ll.next;

					// Combine it into this one
					if (compNext)
					{
						// Add in the length of the next component, plus any spaces between them
						comp->length += (compNext->length + iiComps_charactersBetween(comp, compNext));

						// Delete the next component
						iLl_deleteNode((SLL*)compNext, true);

					} else {
						// We're done, perhaps prematurely, but there are no more components
						break;
					}
				}


			//////////
			// Mark it as the new iCode
			//////
				if (tnNewICode > 0)
					comp->iCode = tnNewICode;


			//////////
			// Indicate how many we merged
			//////
				return(lnCount);

		} else {
			// Indicate failure
			return(0);
		}
	}




//////////
//
// Called to combine two components which are touching into one.
//
// Source:		define user32		something here
// Example:		[define][whitespace][user][32][whitespace][something][here]
// Search:		[alpha][numeric], convert to [alphanumeric]
// After:		[define][whitespace][user32][whitespace][something][here]
//
//////
	u32 iComps_combine2(SEditChain* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeCombined)
	{
		u32		lnCount;
		SComp*	compNext;
		SComp*	comp;
		SComp*	comp1;
		SComp*	comp2;


		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp = line->compilerInfo->firstComp;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = (SComp*)comp->ll.next;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Grab the one after that
				comp1 = comp;
				comp2 = (SComp*)comp1->ll.next;
				if (!comp2)
					return(lnCount);	// We're done

				// When we get here, we have needle-1 and needle-2 candidates.
				// Are they touching?
				if (comp1->start + comp1->length == comp2->start)
				{
					// Uh ... yes.  Can we get a chaperon over here, please?  Thank you!
					// Are they our requested?
					if (comp1->iCode == tniCodeNeedle1 && comp2->iCode == tniCodeNeedle2)
					{
						// YES!  This is the moment we've been waiting for. THIS is why we showed up for work today. THIS is why we came!
						// Gentlemen, we have a job to do.  Now, let's get to it!
						++lnCount;


						//////////
						// Combine these into one
						//////
							// Increase comp1's length, then move comp2 from line->comps to line->compsCombined
							comp1->length	+= comp2->length;
							comp1->iCode	= tniCodeCombined;
							iLl_deleteNode((SLL*)comp2, true);


						//////////
						// Point to the new next thing, which is now the thing after what previously had been comp2, but is now simply comp->ll.next (which could now be nothing)
						//////
							compNext = (SComp*)comp->ll.next;
					}
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to combine three components which are touching into one.
//
// Source:		saddf32		a,20.50
// Example:		[saddf32][whitespace][a][comma][20][period][50]
// Search:		[numeric][period][numeric], convert to [numeric]
// After:		[sadf32][whitespace][a][comma][20.50]
//
//////
	u32 iComps_combine3(SEditChain* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeNeedle3, u32 tniCodeCombined)
	{
		u32		lnCount;
		SComp*	compNext;
		SComp*	comp;
		SComp*	comp1;
		SComp*	comp2;
		SComp*	comp3;


// UNTESTED CODE:  breakpoint and examine
		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp = line->compilerInfo->firstComp;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = (SComp*)comp->ll.next;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Grab the one after that
				comp1 = compNext;
				comp2 = (SComp*)comp1->ll.next;
				if (!comp2)
					return(lnCount);	// We're done

				// Grab the one after that
				comp3 = (SComp*)comp2->ll.next;
				if (!comp3)
					return(lnCount);	// We're done

				// When we get here, we have needle-1, needle-2, and needle-3 candidates.
				// Are they touching?
				if (comp1->start + comp1->length == comp2->start && comp2->start + comp2->length == comp3->start)
				{
					// Are they our requested?
					if (comp1->iCode == tniCodeNeedle1 && comp2->iCode == tniCodeNeedle2 && comp3->iCode == tniCodeNeedle3)
					{
						// It's a match
						lnCount += 2;

						//////////
						// Combine these into one
						//////
							// Increase comp1's length, then move comp2 from line->comps to line->compsCombined
							comp1->length	+= comp2->length + comp3->length;
							comp1->iCode	= tniCodeCombined;
							iLl_deleteNode((SLL*)comp2, true);
							iLl_deleteNode((SLL*)comp3, true);


						//////////
						// Point to the new next thing, which is now the thing after what previously had been comp2, but is now simply comp->ll.next (which could now be nothing)
						//////
							compNext = (SComp*)comp->ll.next;
					}
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to combine adjacent combinations of underscore, alpha, numeric, or alphanumeric,
// which begin with an underscore, alpha, or alphanumeric, into one component that is then
// branded as alphanumeric.
//
//////
	u32 iComps_combineAdjacentAlphanumeric(SEditChain* line)
	{
		u32		lnCombined;
		SComp*	comp;
		SComp*	compNext;


		// Make sure our environment is sane
		lnCombined = 0;
		if (line && line->compilerInfo)
		{
			// Begin at the beginning and check across all components
			comp = line->compilerInfo->firstComp;
			while (comp)
			{
				// Grab the next component
				compNext = (SComp*)comp->ll.next;
				if (compNext)
				{
					// Is this an underscore, alpha, or alphanumeric?
					if (comp->iCode == _ICODE_UNDERSCORE || comp->iCode == _ICODE_ALPHA || comp->iCode == _ICODE_ALPHANUMERIC)
					{
						// Combine so long as the following are immediately adjacent, and are one of underscore, alpha, numeric, alphanumeric
						while (	(compNext = (SComp*)comp->ll.next)
								&& iiComps_charactersBetween(comp, compNext) == 0
								&& (	compNext->iCode == _ICODE_UNDERSCORE
									||	compNext->iCode == _ICODE_ALPHA
									||	compNext->iCode == _ICODE_NUMERIC
									||	compNext->iCode == _ICODE_ALPHANUMERIC
								)
							)
						{
							// Combine this comp and the next one into one
							iComps_combineNextN(comp, 1, _ICODE_ALPHANUMERIC);
							++lnCombined;
						}
					}
				}


				// Move to the next component
				comp = (SComp*)comp->ll.next;
			}
		}

		// Indicate how many we combined
		return(lnCombined);
	}




//////////
//
// Called to combine numeric combinations, such as [999][.][99] into [999.99] as
// a single numeric.  In addition, if a leading plus or negative is immediately
// adjacent, it is included as well.
//
//////
	u32 iComps_combineAdjacentNumeric(SEditChain* line)
	{
		u32		lnCombined;
		SComp*	comp;
		SComp*	compNext1;
		SComp*	compNext2;
		SComp*	compNext3;


		// Make sure our environment is sane
		lnCombined = 0;
		if (line && line->compilerInfo)
		{
			// Begin at the beginning and check across all components
			comp = line->compilerInfo->firstComp;
			while (comp)
			{
				// Grab the next component
				if ((compNext1 = (SComp*)comp->ll.next) && iiComps_charactersBetween(comp, compNext1) == 0)
				{
					// Is this an underscore, alpha, or alphanumeric?
					if ((comp->iCode == _ICODE_PLUS || comp->iCode == _ICODE_HYPHEN) && compNext1->iCode == _ICODE_NUMERIC)
					{
						// We have +-999
						if ((compNext2 = (SComp*)compNext1->ll.next) && compNext2->iCode == _ICODE_DOT)
						{
							// We have +-999.
							if ((compNext3 = (SComp*)compNext2->ll.next) && compNext3->iCode == _ICODE_NUMERIC)
							{
								// We have +-999.99
								iComps_combineNextN(comp, 3, _ICODE_NUMERIC);
								lnCombined += 3;

							} else {
								// Combine the +- with the 999 and the .
								iComps_combineNextN(comp, 2, _ICODE_NUMERIC);
								lnCombined += 2;
							}

						} else {
							// Combine the +- with the 999 into one
							iComps_combineNextN(comp, 1, _ICODE_NUMERIC);
							++lnCombined;
						}

					} else if (comp->iCode == _ICODE_NUMERIC) {
						// We have 999
						if ((compNext2 = (SComp*)compNext1->ll.next) && compNext2->iCode == _ICODE_DOT)
						{
							// We have 999.
							if ((compNext3 = (SComp*)compNext2->ll.next) && compNext3->iCode == _ICODE_NUMERIC)
							{
								// We have 999.99
								iComps_combineNextN(comp, 2, _ICODE_NUMERIC);
								lnCombined += 2;

							} else {
								// We just have 999.
								iComps_combineNextN(comp, 1, _ICODE_NUMERIC);
								++lnCombined;
							}
						}
					}
				}


				// Move to the next component
				comp = (SComp*)comp->ll.next;
			}
		}

		// Indicate how many we combined
		return(lnCombined);
	}




//////////
//
// Called to combine everything between two components
//
// Source:		u8 name[] = "foo"
// Example:		[u8][whitespace][name][left bracket][right bracket][whitespace][equal][whitespace][double quote][foo][double quote]
// Search:		[double quote], replace with [double quoted text]
// After:		[u8][whitespace][name][left bracket][right bracket][whitespace][equal][whitespace][double quote text]
//
//////
	u32 iComps_combineAllBetween(SEditChain* line, u32 tniCodeNeedle, u32 tniCodeCombined)
	{
		u32		lnCount;
		SComp*	compNext;
		SComp*	comp;
		SComp*	compSearcher;


// UNTESTED CODE:  breakpoint and examine
		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp = line->compilerInfo->firstComp;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = (SComp*)comp->ll.next;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Is this our intended?
				if (comp->iCode == tniCodeNeedle)
				{
					// Search forward to see if there is a matching entry
					compSearcher = compNext;
					while (compSearcher)
					{
						if (compSearcher->iCode == tniCodeNeedle)
						{
							// This is the match, combine everything between
							comp->length	= (compSearcher->start + compSearcher->length) - comp->start;
							comp->iCode		= tniCodeCombined;

							// Iterate and merge in
							while (compNext)
							{
								// Increase our count
								++lnCount;

								// Delete this one (as it was technically merged above with the comp->length = line)
								iLl_deleteNode((SLL*)compNext, true);

								// See if we're done
								if (compNext == compSearcher)
									break;		// This was the last one, we're done

								// Move to the next component (which is the comp->ll.next component again, because we just migrated the previous compNext
								compNext = (SComp*)comp->ll.next;
							}
							// When we get here, everything's migrated

							// Grab the new next, which is the one after the matched entry
							compNext = (SComp*)comp->ll.next;

							// Continue looking for more combinations on this line
							break;
						}

						// Move to the next component
						compSearcher = (SComp*)compSearcher->ll.next;
					}
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to combine everything after the indicated component into that one component.
//
//////
	u32 iComps_combineAllAfter(SEditChain* line, u32 tniCodeNeedle)
	{
		u32		lnCombined;
		SComp*	comp;


		// Make sure our environment is sane
		lnCombined = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp = (SComp*)line->compilerInfo->firstComp;

			// Iterate forward through all components
			while (comp)
			{
				// Is this our intended?
				if (comp->iCode == tniCodeNeedle)
				{
					// Combine from here on out
					while (comp->ll.next)
					{
						// Combine
						iComps_combineNextN(comp, 1, tniCodeNeedle);

						// Indicate the number combined
						++lnCombined;
					}
				}

				// Move to the next component
				comp = (SComp*)comp->ll.next;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCombined);
	}




//////////
//
// Called to delete everything after the indicated component
//
//////
	u32 iComps_deleteAllAfter(SEditChain* line, u32 tniCodeNeedle)
	{
		u32		lnDeleted;
		SComp*	comp;
		SComp**	compLast;


		// Make sure our environment is sane
		lnDeleted = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp		= (SComp*)line->compilerInfo->firstComp;
			compLast	= (SComp**)&line->compilerInfo->firstComp;

			// Iterate forward through all components
			while (comp)
			{
				// Is this our intended?
				if (comp->iCode == tniCodeNeedle)
				{
					// Combine from here on out
					while (comp)
					{
						// Indicate the number combined
						++lnDeleted;

						// Move to the next component
						comp = (SComp*)comp->ll.next;
					}

					// Delete from here on out
					iLl_deleteNodeChain((SLL**)compLast);
					break;
				}

				// Move to the next component
				compLast	= (SComp**)&comp->ll.next;
				comp		= (SComp*)comp->ll.next;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnDeleted);
	}




//////////
//
// Called to remove whitespaces.
// Note:  By the time this function is called, natural groupings should've already been
//        processed, such that all quoted text items are already combined into a single icode.
//
//////
	u32 iComps_removeWhitespaces(SEditChain* line)
	{
		u32		lnRemoved;
		SComp*	comp;
//		SComp*	compNext;


		// Make sure our environment is sane
		lnRemoved = 0;
		if (line && line->compilerInfo)
		{
			// Iterate through all looking for _ICODE_COMMENT_START
			comp = line->compilerInfo->firstComp;
			while (comp)
			{
				//////////
				// Is this a whitespace?
				//////
					while (comp && comp->iCode == _ICODE_WHITESPACE)
					{
						comp = (SComp*)iLl_deleteNode((SLL*)comp, true);
						++lnRemoved;
					}


				//////////
				// Continue on to next component
				//////
					if (comp)
						comp = (SComp*)comp->ll.next;
			}
		}

		// Indicate how many we removed
		return(lnRemoved);
	}




//////////
//
// Called to remove any /* comments */ from the current chain of comps.
//
//////
	void iComps_removeStartEndComments(SEditChain* line)
	{
		SComp* comp;


		// Make sure our environment is sane
		if (line && line->compilerInfo)
		{
			// Iterate through all looking for _ICODE_COMMENT_START
			comp = line->compilerInfo->firstComp;
			while (comp)
			{
				//////////
				// Is this a start?
				//////
					if (comp->iCode == _ICODE_COMMENT_START)
					{
						// Delete everything forward until we reach _ICODE_COMMENT_END or the last comp
						while (comp && comp->iCode != _ICODE_COMMENT_END)
						{
							// Delete this component
							comp = (SComp*)iLl_deleteNode((SLL*)comp, true);
						}

						// When we get here, we're sitting on the _ICODE_COMMENT_END
						if (comp && comp->iCode == _ICODE_COMMENT_END)
							comp = (SComp*)iLl_deleteNode((SLL*)comp, true);
					}


				//////////
				// Continue on to next component
				//////
					if (comp)
						comp = (SComp*)comp->ll.next;
			}
		}
	}




//////////
//
// Fixes up common things found in VXB-- source code.
//
//////
	void iComps_fixupNaturalGroupings(SEditChain* line)
	{
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			//////////
			// Fixup quotes, comments
			//////
				iComps_combineAllBetween(line, _ICODE_SINGLE_QUOTE,		_ICODE_SINGLE_QUOTED_TEXT);
				iComps_combineAllBetween(line, _ICODE_DOUBLE_QUOTE,		_ICODE_DOUBLE_QUOTED_TEXT);
				iComps_deleteAllAfter	(line, _ICODE_LINE_COMMENT);


			//////////
			// Search for combinations which are adjacent sequences beginning with an underscore or alpha,
			// which then alternate in some form of alpha, numeric, underscore, etc., and translate to
			// alphanumeric.  For numeric it looks for +-999.99 completely adjacent, and combines into one.
			//////
				iComps_combineAdjacentAlphanumeric(line);
				iComps_combineAdjacentNumeric(line);
		}
	}




//////////
//
// Returns the number of characters between two components.
//
//////
	s32 iiComps_charactersBetween(SComp* compLeft, SComp* compRight)
	{
		// Start of right component and end of left component
		return(compRight->start - (compLeft->start + compLeft->length));
	}




//////////
//
// Scans from the indicated location forward until finding CR/LF or any combination thereof,
// nothing whitespaces, content, and total line length (including cr/lf combinations at the end)
//
//////
	u32 iBreakoutAsciiTextDataIntoLines_ScanLine(s8* tcData, u32 tnMaxLength, u32* tnLength, u32* tnWhitespaces)
	{
		u32 lnLength, lnWhitespaces, lnCRLF_Length;


		// Make sure we have something to do
		lnLength		= 0;
		lnWhitespaces	= 0;
		lnCRLF_Length	= 0;
		if (tcData && tnMaxLength > 0)
		{
			// Skip past any whitespaces
			lnWhitespaces = iSkipWhitespaces(tcData, tnMaxLength);
			if (tnWhitespaces)
				*tnWhitespaces = lnWhitespaces;


			// Skip to the ending carriage return / line feed
			lnLength = iSkipToCarriageReturnLineFeed(tcData + lnWhitespaces, tnMaxLength - lnWhitespaces, &lnCRLF_Length);
			if (tnLength)
				*tnLength = lnLength;
		}
		// Return the total length
		return(lnWhitespaces + lnLength + lnCRLF_Length);
	}




//////////
//
// Searches the haystack for the indicated needle, and reports the position if found
//
// Returns:
//		true	- found, tnPosition is updated
//		false	- not found, tnPosition unchanged
//
//////
	bool iFindFirstOccurrenceOfAsciiCharacter(s8* tcHaystack, u32 tnHaystackLength, s8 tcNeedle, u32* tnPosition)
	{
		u32		lnI;
		bool	llFound;


		// Make sure our environment is sane
		llFound = false;
		if (tcHaystack && tnHaystackLength != 0)
		{
			// Repeat for the length of the string
			for (lnI = 0; lnI < tnHaystackLength; lnI++)
			{
				// See if this is the character we're after
				if (tcHaystack[lnI] == tcNeedle)
				{
					// We found it
					llFound = true;

					// Update caller's pointer if need be
					if (tnPosition)
						*tnPosition = lnI;

					// All done
					break;
				}
			}
			// When we get here, either found or not
		}
		// Indicate our found condition
		return(llFound);
	}




//////////
//
// Called to translate the indicated keywords into their corresponding operation.
//
//////
	void iiComps_xlatToSubInstr(SEditChain* line)
	{
		SNode	si;
		SComp*		saveComps;


		//////////
		// Copy the comps
		//////
			saveComps = line->compilerInfo->firstComp;


		//////////
		// Find the inmost expression
		//////
			while (iiComps_xlatToSubInstr_findInmostExpression(&si, line))
			{
				// Was it a valid operation?
				if (si.sub_instr >= 0)
				{
					// We found the operation
					// Did we find appropriate components?
// TODO:  Working here

				} else {
					// The sub_instruction is not valid, which means were done
					break;
				}

				// When we get here, try to find another
			}


		//////////
		// There are no more "inner" expressions.
		// Now we parse out by keyword.
		//////
			if (iiComps_xlatToSubInstr_isEqualAssignment(line))
			{
				// It's something like x = y, but it could be x,y,z = a(b,c)

			} else {
				// Based upon keyword, process it
			}
	}




//////////
//
// Called to search for the thing that needs to be done next.  Order of searching:
//
// First level:
//		(1)		exponents
//		(2)		multiply, divide
//		(3)		add, subtract
//
// Second level:
//		(4)		parenthetical expressions
//		(5)		bracket expressions (arrays)
//		(6)		
//
//////
	SComp* iiComps_xlatToSubInstr_findInmostExpression(SNode* si, SEditChain* line)
	{
		bool	llFound;
		SComp*	comp;


		//////////
		// Initially indicate that we did not find an inmost expression
		//////
			memset(si, 0, sizeof(SNode));
			si->sub_instr	= -1;			// Indicate failure initially (until something is found)
			si->sub_level	= -1;			// Unused during parsing


		//////////
		// Search for exponents
		//////
			comp	= line->compilerInfo->firstComp;
			llFound	= true;
			while (comp)
			{
				//////////
				// Is it an exponent?
				//////
					if (comp->iCode == _ICODE_EXPONENT)
					{
						// Exponent
						si->sub_instr	= _SUB_INSTR_EXPONENT;
						llFound			= true;

					} else if (comp->iCode == _ICODE_SLASH) {
						// Division
						si->sub_instr	= _SUB_INSTR_DIVIDE;
						llFound			= true;

					} else if (comp->iCode == _ICODE_ASTERISK) {
						// Multiplication
						si->sub_instr	= _SUB_INSTR_MULTIPLY;
						llFound			= true;

					} else if (comp->iCode == _ICODE_PLUS) {
						// Addition
						si->sub_instr	= _SUB_INSTR_ADD;
						llFound			= true;

					} else if (comp->iCode == _ICODE_HYPHEN) {
						// Subtraction
						si->sub_instr	= _SUB_INSTR_SUBTRACT;
						llFound			= true;
					}


				//////////
				// Was it found?
				//////
					if (llFound)
					{
						// Search for something to the left of the exponent, like the "someTable.someField" in "k = someTable.someField ^ xyz"
						// Search for something to the right of the exponent, like the "thisForm.someObject.someProperty" in "k = xyz ^ thisForm.someObject.someProperty"
// TODO:  Refactor for left and right nodes
// 						iiComps_xlatToSubInstr_findStartOfComponent	((SComp*)comp->ll.prev, si->op);
// 						iiComps_xlatToSubInstr_findFullComponent	((SComp*)comp->ll.next, si->op);

						// When we get here, si has been populated if there are operations there.
						// If they are null, then it is a syntax error
						break;
					}


				// Move to next component
				comp = (SComp*)comp->ll.next;
			}

		// Indicate our result
		return(comp);
	}




//////////
//
// We scan backwards until we get to any component other than a period or exclamation point.
//
//////
	void iiComps_xlatToSubInstr_findStartOfComponent(SComp* compRoot, SOp* op)
	{
		SComp*	comp;
		SComp*	compPrev;


		//////////
		// Iterate through
		//////
			comp		= compRoot;
			op->count	= 0;
			while (comp && comp->ll.prev && iiComps_charactersBetween((SComp*)comp->ll.prev, comp) == 0)
			{
				//////////
				// Previous component
				//////
					compPrev = (SComp*)comp->ll.prev;


				//////////
				// Is the component before this one still immediately adjacent?
				//////
					if (comp->iCode != _ICODE_DOT && comp->iCode != _ICODE_EXCLAMATION_MARK)
						break;		// We've reached the end, the previous component is not a continuation


				//////////
				// If we get here, we're continuing through this component at least
				//////
					comp = compPrev;
					++op->count;
			}


		//////////
		// If we get here, we will return the starting point
		//////
			op->comp = comp;
	}




//////////
//
// We scan forward so long as we are hitting a period or exclamation point which is
// immediately adjacent.
//
//////
	void iiComps_xlatToSubInstr_findFullComponent(SComp* compRoot, SOp* op)
	{
		SComp*	comp;
		SComp*	compNext;


		//////////
		// Iterate through
		//////
			comp		= compRoot;
			op->count	= 0;
			while (comp && comp->ll.next && iiComps_charactersBetween(comp, (SComp*)comp->ll.next) == 0)
			{
				//////////
				// Next component
				//////
					compNext = (SComp*)comp->ll.next;


				//////////
				// Is the component before this one still immediately adjacent?
				//////
					if (comp->iCode != _ICODE_DOT && comp->iCode != _ICODE_EXCLAMATION_MARK)
						break;	// We've reached the end, the next component is not a continuation


				//////////
				// If we get here, we're continuing through this component at least
				//////
					comp = compNext;
					++op->count;
			}


		//////////
		// At this point comp indicates the last component
		//////
			op->comp = comp;
	}




//////////
//
// Called to see if the instruction is an assignment:
//		x = y
//
//////
	bool iiComps_xlatToSubInstr_isEqualAssignment(SEditChain* line)
	{
// TODO:  Write this function :-)
		return(false);
	}




//////////
//
// Scans from the indicated location forward until finding a non-whitespace character
//
//////
	u32 iSkipWhitespaces(s8* tcData, u32 tnMaxLength)
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
	u32 iSkipToCarriageReturnLineFeed(s8* tcData, u32 tnMaxLength, u32* tnCRLF_Length)
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
	u32 iGetNextUid(void)
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



	void* iSEChain_prepend(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(iSEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, true, tlResult));
	}

	void* iSEChain_append(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(iSEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, false, tlResult));
	}

	// Prepends or appends to the Start/end chain
	void* iSEChain_appendOrPrepend (SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult)
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
					iSEChain_appendMasterList(ptrSE, ptrNew, 0, tnBlockSizeIfNewBlockNeeded);

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
	void iSEChain_appendMasterList(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded)
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
			iSEChain_allocateAdditionalMasterSlots(ptrSE, tnBlockSizeIfNewBlockNeeded);
			// We never break out of this loop because we will always return above from it
		}
	}

	
	bool iSEChain_allocateAdditionalMasterSlots(SStartEnd* ptrSE, u32 tnBlockSize)
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
// Search the haystack for the needle, the haystack can be tupels, as in "_az" meaning
// (is it between "a" and "z" inclusive?)  To set this condition, use a length of 1,
// a leading "_" in tcHaystack, and two characters (one of which must NOT be NULL) after.
// Examples:
//		_az		= lower-case a to z inclusive
//		_AZ		= upper-case a to z inclusive
//		_09		= numeric 0 to 9 inclusive
//
// Returns:
//		0		= matches
//		!0		= does not tmach
//
//////
	s32 iTranslateToCompsTest(s8* tcHaystack, s8* tcNeedle, s32 tnLength)
	{
		u32		lnI;
		bool	llSigned;


		// Make sure our environment is sane
		if (tnLength != 0)
		{
			// See if we're a signed or unsigned compare
			if (tnLength < 0)
			{
				// Case sensitive compare
				tnLength	= -tnLength;
				llSigned	= true;

			} else {
				// Case insensitive compare
				llSigned = false;
			}

			// See if we're looking for a tuple, or a regular compare
			if (tcHaystack[0] == '_' && tnLength == 1)
			{
				// It's an explicit match of a range (this is ALWAYS subject to case as it is an explicit range)
				for (lnI = 1; tcHaystack[lnI] != 0 || tcHaystack[lnI + 1] != 0; lnI += 2)
				{
					//		within the range low			.........			up to the range high
					if (tcNeedle[0] >= tcHaystack[lnI]			&&		tcNeedle[0] <= tcHaystack[lnI + 1])
						return(0);		// It's a match, needle is in the range
				}
				// Not a match, will fall through to below

			} else {
				// Just a regular compare
				if (llSigned)	return(  memcmp(tcHaystack, tcNeedle, tnLength));
				else			return(_memicmp(tcHaystack, tcNeedle, tnLength));
			}
		}
		// If we get here, no match
		return(-1);
	}




//////////
//
// Callback, used to translate existing components into other components
// Note:  Always returns false, so it will continue being fed every component
//
//////
	bool iioss_translateCompsToOthersCallback(SStartEndCallback* cb)
	{
		bool					llResult;
		s32						lnLacsLength;
		SComp*				comp;
		SAsciiCompSearcher*		lacs;
		SCompCallback		lccb;


		// Make sure the environment is sane
		if (cb && cb->ptr)
		{
			// Grab our pointers into recognizable thingamajigs
			comp	= (SComp*)cb->ptr;
			lacs	= (SAsciiCompSearcher*)cb->extra;

			// Iterate through this item to see if any match
			for (	/* lacs is initialize above */;
					lacs->length != 0;
					lacs++		)
			{
				// Grab the normalized length
				lnLacsLength = abs(lacs->length);

				// We only test if they're the same length
				if (lnLacsLength == comp->length || (lacs->repeats && lnLacsLength <= comp->length))
				{
					// We only test if this item is not the first item on line, or if must be the first
					// item on the line, then this component must be the first component on the line.  Simple, yes? :-)
					if (!lacs->firstOnLine || comp->start == 0)
					{
						// Physically conduct the exact comparison
						if (iTranslateToCompsTest((s8*)lacs->keyword, 
														comp->line->sourceCode->data + comp->start, 
														lacs->length) == 0)
						{
							// This is a match
							// Is there a secondary test?
							if (lacs->_validate)
							{
								// Yes, make sure it validates there as well
								lccb.comp					= comp;
								lccb.length					= 0;
								lccb.iCode					= lacs->iCode;
								lccb._insertCompByComp		= (u32)&iiComps_xlatToOthersCallback__insertCompByCompCallback;
								lccb._insertCompByParams	= (u32)&iiComps_xlatToOthersCallback__insertCompByParamsCallback;
								lccb._deleteComps			= (u32)&iiComps_xlatToOthersCallback__deleteCompsCallback;
								lccb._cloneComps			= (u32)&iiComps_xlatToOthersCallback__cloneCompsCallback;
								lccb._mergeComps			= (u32)&iiComps_xlatToOthersCallback__mergeCompsCallback;

								// Perform the validation
								llResult = lacs->validate(&lccb);

							} else {
								// No, just let it fall through
								llResult = true;
							}
							
							if (llResult)
							{
								// Convert it, translate it, whatever you want to call it, just make it be the new code, per the user's request, got it? :-)
								comp->iCode = lacs->iCode;
								// All done with this component
								break;
							}
						}
					}
				}
			}

		}
		// We always simulate a false condition so we'll keep receiving each item
		return(false);
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
	void* iSEChain_searchByCallback(SStartEnd* ptrSE, SStartEndCallback* cb)
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
// Called as a callback from the custom handler callback function, to do some manual insertion.
// Note:  If a rogue component is inserted here, one not already defined in the ref's SOssLine parent,
//        then it will need to be either manually added to the line->comps, or manually tended to.
//
//////
	void iiComps_xlatToOthersCallback__insertCompByCompCallback(SComp* compRef, SComp* compNew, bool tlInsertAfter)
	{
// TODO:  untested code, breakpoint and examine
_asm int 3;
		// Make sure our environment is sane
		if (compRef && compNew)
		{
			// Before or after?
			if (tlInsertAfter)
			{
				// Add the new comp after the reference comp
				if (compRef->ll.next)
					compRef->ll.next->prev	= (SLL*)compNew;	// One originally after ref points back to new

				compNew->ll.next	= compRef->ll.next;			// New points forward to the one originally after ref
				compNew->ll.prev	= (SLL*)compRef;			// New points back to ref
				compRef->ll.next	= (SLL*)compNew;			// Ref points forward to new

			} else {
				// Add the new comp before the reference comp
				if (compRef->ll.prev)
					compRef->ll.prev->next	= (SLL*)compNew;	// One originally before ref points forward to new

				compNew->ll.next	= (SLL*)compRef;			// New points forward to ref
				compNew->ll.prev	= compRef->ll.prev;			// New points back to the one originally before ref
				compRef->ll.prev	= (SLL*)compNew;			// Ref points back to new
			}
		}
	}




//////////
//
// Called as a callback from the custom handler callback function, to do some manual insertion.
//
//////
	void iiComps_xlatToOthersCallback__insertCompByParamsCallback(SComp* compRef, SEditChain* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter)
	{
		SComp* compNew;


// TODO:  untested code, breakpoint and examine
_asm int 3;
		// Make sure our environment is sane
		if (compRef && line && line->compilerInfo)
		{
			// Allocate a new pointer
			compNew = (SComp*)iLl_appendNewNode((SLL**)&line->compilerInfo->firstComp, NULL, NULL, NULL, iGetNextUid(), sizeof(SComp));
			if (compNew)
			{
				// Initialize it
				memset(compNew, 0, sizeof(SComp));

				// Populate it
				compNew->line		= line;
				compNew->iCode		= tniCode;
				compNew->start		= tnStart;
				compNew->length		= tnLength;

				// Add the new component as a component
				iiComps_xlatToOthersCallback__insertCompByCompCallback(compRef, compNew, tlInsertAfter);
			}
		}
	}




//////////
//
// Called as a callback from the custom handler callback function, to do delete the
// indicated component.
//
//////
	void iiComps_xlatToOthersCallback__deleteCompsCallback(SComp* comp, SEditChain* line)
	{
// TODO:  untested code, breakpoint and examine
_asm int 3;
		//////////
		// Disconnect the component from its siblings
		//////
			// Make the one before point forward to one after
			if (comp->ll.prev)
				comp->ll.prev->next = comp->ll.next;

			// Make the one after point back to the one before
			if (comp->ll.next)
				comp->ll.next->prev = comp->ll.prev;


		//////////
		// Delete it from the list of known components.
		// Component go bye bye. :-)
		//////
			if (line)
			{
				// Delete the entry from line->comps
				iLl_deleteNode((SLL*)comp, true);

			} else {
				// Free the rogue entry
				free(comp);
			}
	}




//////////
//
// Called as a callback from the custom handler callback function, to clone the indicated
// component.  If line is not NULL, the component is automatically added to line->comps;
//
//////
	SComp* iiComps_xlatToOthersCallback__cloneCompsCallback(SComp* comp, SEditChain* line)
	{
		SComp* compNew;


// TODO:  untested code, breakpoint and examine
_asm int 3;
		// Make sure our environment is sane
		if (comp)
		{
			// Are we adding to to a line?
			if (line && line->compilerInfo)
			{
				// Add the new component to line->comps
				compNew = (SComp*)iLl_appendNewNode((SLL**)&line->compilerInfo->firstComp, NULL, NULL, NULL, iGetNextUid(), sizeof(SComp));

			} else {
				// Just create a rogue one
				compNew = (SComp*)malloc(sizeof(SComp));
			}

			// Was it valid?
			if (compNew)
			{
				// Initialize it
				memset(compNew, 0, sizeof(SComp));

				// Populate it
				compNew->line		= line;
				compNew->iCode		= comp->iCode;
				compNew->start		= comp->start;
				compNew->length		= comp->length;

				// All done!
			}
		}

		// Return our new one, no matter if it was a success or not
		return(compNew);
	}




//////////
//
// Called as a callback from the custom handler callback function, to do merge components into
// a new one, and delete the one(s) which were merged.
//
// NOTE:  It's theoretically possible that there could be a gap here, such as a component next to
//        another component where there used to be a whitespace inbetween (or anything else), so
//        the components are no longer right by each other.  The caller will have to manually
//        handle that condition.
//
//////
	SComp* iiComps_xlatToOthersCallback__mergeCompsCallback(SComp* comp, SEditChain* line, u32 tnCount, u32 tniCodeNew)
	{
		u32			lnI;
		SComp*	compThis;


// TODO:  untested code, breakpoint and examine
_asm int 3;
		// Make sure our environment is sane
		if (comp)
		{
			// Iterate for each merging
			for (lnI = 1, compThis = (SComp*)comp->ll.next; compThis && lnI < tnCount; lnI++, compThis = (SComp*)comp->ll.next)
			{
				// Absorb compThis's length into comp's "collective"
				comp->length += compThis->length;

				// Delete this component
				iiComps_xlatToOthersCallback__deleteCompsCallback(compThis, comp->line);

				// Note:  compThis is always assigned comp->ll.next, because its next component keeps being updated after the delete
			}
			// When we get here, everything's merged
		}
		// Return the original component as a pass through (in case this is used as an intermediate function)
		return(comp);
	}




//////////
//
// Delete the indicated item from the chain
//
//////
	void iSEChain_deleteFrom(SStartEnd* ptrSE, void* ptrCaller, bool tlDeletePointers)
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
// Migrate the existing SMasterList item, and its associated SLL item, from one Start/end chain
// to another, by either pointer or physical position number.
//
//////
	SLL* iSEChain_completelyMigrateSLLByPtr(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr, u32 tnHint, u32 tnBlockSize)
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
					return(iSEChain_completelyMigrateSLLByNum(ptrSEDst, ptrSESrc, lnI, 0, tnBlockSize));
				}
			}
			// If we get here, not found
		}
		// Indicate failure
		return(NULL);
	}

	SLL* iSEChain_completelyMigrateSLLByNum(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize)
	{
		SLL*			lllPrev;
		SLL*			lllNext;
		SLL*			lll;
		SMasterList*	lml;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && lnSrcNum < ptrSESrc->masterCount && lnSrcNum <= ptrSESrc->masterCount)
		{
			// Migrate it, and get its SMasterList entry
			lml = iSEChain_migrateByNum(ptrSEDst, ptrSESrc, lnSrcNum, tnHint, tnBlockSize);
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

	SMasterList* iSEChain_migrateByNum(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize)
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
				iSEChain_allocateAdditionalMasterSlots(ptrSEDst, tnBlockSize);

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
// Append a new node to the list, and return the pointer.
// The nodeHint is provided and can be used to find the end of the chain faster than iterating
// from the root.  Typically it is the last returned node.  However, if NULL, this process will
// iterate from the root node forward.
//
//////
	SLL* iLl_appendNewNode(SLL** root, SLL* nodeHint, SLL* nodeNext, SLL* nodePrev, u32 tnUniqueId, u32 tnSize)
	{
		SLL* node;


		// Make sure our environment is sane
		node = NULL;
		if (root)
		{
			// Create a new node
			node = iLl_createOrphanNode(nodePrev, nodeNext, tnUniqueId, tnSize);
			
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
	SLL* iLl_createOrphanNode(SLL* nodePrev, SLL* nodeNext, u32 tnUniqueId, u32 tnSize)
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
// Called to append the node at the end of the chain
//
//////
	SLL* iLl_appendNewNodeAtEnd(SLL** root, u32 tnSize)
	{
		SLL* node;
		SLL* nodeNew;


		// Make sure our environment is sane
		nodeNew = NULL;
		if (root)
		{
			// Allocate new
			nodeNew = (SLL*)malloc(tnSize);
			if (nodeNew)
			{
				// Initialize
				memset(nodeNew, 0, tnSize);

				// Determine where it goes
				if (!*root)
				{
					// First entry
					*root = nodeNew;

				} else {
					// Append to end
					node = *root;
					while (node->next)
						node = node->next;

					// Append here
					node->next		= nodeNew;		// Previous points here
					nodeNew->prev	= node;			// We point back to previous
				}
			}
		}

		// Indicate our status
		return(nodeNew);
	}




/////////
//
// Called to append a node which already exists to the end
//
//////
	bool iLl_appendExistingNodeAtEnd(SLL** root, SLL* node)
	{
		bool	llAppended;
		SLL*	nodeLast;


		// Make sure our environment is sane
		llAppended = false;
		if (root && node)
		{
			// Determine where it goes
			if (!*root)
			{
				// First entry
				*root = node;

			} else {
				// Append to end
				nodeLast = *root;
				while (nodeLast->next)
					nodeLast = nodeLast->next;

				// Append here
				nodeLast->next	= node;			// Last one currently existing points here
				node->prev		= nodeLast;		// Node points back to previous last one
				llAppended		= true;
			}
		}

		// Indicate our status
		return(llAppended);
	}




//////////
//
// Called to delete a link list node from the chain.  It orphanizes the node first.
// It will fully delete it if tlDeleteSelf is true.  The return value is either the
// orphan node, or the node->next value if the node was fully deleted.
//
//////
	SLL* iLl_deleteNode(SLL* node, bool tlDeleteSelf)
	{
		SLL* nodeNext;


		// Make sure our environment is sane
		nodeNext = NULL;
		if (node)
		{
			//////////
			// Disconnect
			//////
				nodeNext = node->next;
				if (node->prev || node->next)
					iLl_orphanizeNode(node);


			//////////
			// Delete the node
			//////
				if (tlDeleteSelf)		free(node);
				else					nodeNext = node;
		}

		// Indicate our status
		return(nodeNext);
	}




//////////
//
// Called to delete a link list node with a callback.  If need be it orphanizes the node first.
//
//////
	void iLl_deleteNodesWithCallback(SLLCallback* cb)
	{
		if (cb && cb->node)
		{
			//////////
			// Disconnect
			//////
				if (cb->node->prev || cb->node->next)
					iLl_orphanizeNode(cb->node);


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
	bool iLl_insertNode(SLL* node,  SLL* nodeRef,  bool tlAfter)
	{
// TODO:  UNTESTED CODE
		// Is our environment sane?
		if (node && nodeRef)
		{
			//////////
			// Disconnect
			//////
				if (node->prev || node->next)
					iLl_orphanizeNode(node);


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
	void iLl_orphanizeNode(SLL* node)
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
	void iLl_deleteNodeChain(SLL** root)
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
	void iLl_deleteNodeChainWithCallback(SLLCallback* cb)
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

				// Delete the node itself
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
	void iLl_iterateViaCallback(SLLCallback* cb)
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
	void iLl_iterateBackwardViaCallback(SLLCallback* cb)
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
	SLL* iLl_getFirstNode(SLL* node)
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
	SLL* iLl_getLastNode(SLL* node)
	{
		// Make sure the environment is sane
		if (node)
		{
			// Iterate toward the end
			while (node->next)
				node = node->next;
		}

		// Indicate where we are
		return(node);
	}




//////////
//
// Called to count the nodes to the end
//
//////
	u32 iLl_countNodesToEnd(SLL* node)
	{
		u32 lnCount;


		// Make sure the environment is sane
		lnCount = 0;
		if (node)
		{
			// Iterate toward the end
			while (node)
			{
				// Increase our count
				++lnCount;

				// Continue on so long as we have nodes
				node = node->next;
			}
		}

		// Indicate how many we found
		return(lnCount);
	}




//////////
//
// Called to create a new node and attach it to the hint as indicated.
//
//////
	SNode* iNode_create(SNode** root, SNode* hint, u32 tnDirection, SNode* parent, SNode* prev, SNode* next, SNode* left, SNode* right)
	{
		SNode*		nodeNew;
		SNode**		nodePrev;
		SNode*		nodeOrphan;


		// Make sure our environment is sane
		nodeNew = NULL;
		if (root)
		{
			if (!*root)
			{
				// This is the first item
				nodePrev = root;

			} else {
				// We're adding to the hint
				if (!hint)
				{
					// No hint, we are creating an orphan
					nodePrev = &nodeOrphan;

				} else {
					// Relates to hint in some way
					switch (tnDirection)
					{
						default:
						case _NODE_NONE:
							// Create an orphan node
							nodePrev = &nodeOrphan;
							break;

						case _NODE_PARENT:
							// Connecting to hint->parent
							nodePrev = &hint->parent;
							break;

						case _NODE_PREV:
							// Connecting to hint->prev
							nodePrev = &hint->prev;
							break;

						case _NODE_NEXT:
							// Connecting to hint->next
							nodePrev = &hint->next;
							break;

						case _NODE_LEFT:
							// Connecting to hint->left
							nodePrev = &hint->left;
							break;

						case _NODE_RIGHT:
							// Connecting to hint->right
							nodePrev = &hint->right;
							break;
					}
				}
			}


			//////////
			// Add the new node
			//////
				nodeNew = (SNode*)malloc(sizeof(SNode));
				if (nodeNew)
				{
					// Initialize
					memset(nodeNew, 0, sizeof(SNode));

					// Update the link from previous
					*nodePrev			= nodeNew;

					// Connect our new node
					nodeNew->parent		= parent;
					nodeNew->prev		= prev;
					nodeNew->next		= next;
					nodeNew->left		= left;
					nodeNew->right		= right;
				}


		}

		// Indicate our status
		return(nodeNew);
	}




//////////
//
// Creates a new node and inserts it where node1 currently points to node2.
//
//////
	SNode* iNode_insertBetween(SNode** root, SNode* node1, SNode* node2, u32 tnNode1Direction, u32 tnNode2Direction)
	{
		u32		lnNode1Direction, lnNode2Direction;
		SNode*	nodeNew;


		// Make sure our environment is sane
		nodeNew = NULL;
		if (root)
		{
			//////////
			// Find out where we're going node1 to node2
			//////
				if (node1)
				{
					if (node1->parent == node2)			lnNode1Direction = _NODE_PARENT;		// We're going up
					else if (node1->prev == node2)		lnNode1Direction = _NODE_PREV;			// We're going to previous
					else if (node1->next == node2)		lnNode1Direction = _NODE_NEXT;			// We're going to next
					else if (node1->left == node2)		lnNode1Direction = _NODE_LEFT;			// We're going left
					else if (node1->right == node2)		lnNode1Direction = _NODE_RIGHT;			// We're going to right
					else								lnNode1Direction = _NODE_NONE;			// Failure, they are not connected

				} else {
					// No node1
					lnNode1Direction = tnNode1Direction;
				}


			//////////
			// Find out where we're going node2 to node1
			//////
				if (node2)
				{
					if (node2->parent == node1)			lnNode2Direction = _NODE_PARENT;		// We're going up
					else if (node2->prev == node1)		lnNode2Direction = _NODE_PREV;			// We're going to previous
					else if (node2->next == node1)		lnNode2Direction = _NODE_NEXT;			// We're going to next
					else if (node2->left == node1)		lnNode2Direction = _NODE_LEFT;			// We're going left
					else if (node2->right == node1)		lnNode2Direction = _NODE_RIGHT;			// We're going to right
					else								lnNode2Direction = _NODE_NONE;			// They are not connected in this direction

				} else {
					// No node2
					lnNode2Direction = tnNode2Direction;
				}


			// Create an orphan node
			nodeNew = iNode_create(root, NULL, 0, NULL, NULL, NULL, NULL, NULL);
			if (nodeNew)
			{
				//////////
				// Hook it up to node1
				//////
					switch (lnNode1Direction)
					{
						case _NODE_PARENT:
							// It's going up from node1 to node2
							nodeNew->parent	= node2;		// Hook the new node up to where node1 used to point (node2)
							node1->parent	= nodeNew;		// Make node1 now point to our inserted node (nodeNew)
							break;

						case _NODE_PREV:
							// It's going up from node1 to node2
							nodeNew->prev	= node2;		// Hook the new node up to where node1 used to point (node2)
							node1->prev		= nodeNew;		// Make node1 now point to our inserted node (nodeNew)
							break;

						case _NODE_NEXT:
							// It's going up from node1 to node2
							nodeNew->next	= node2;		// Hook the new node up to where node1 used to point (node2)
							node1->next		= nodeNew;		// Make node1 now point to our inserted node (nodeNew)
							break;

						case _NODE_LEFT:
							// It's going up from node1 to node2
							nodeNew->left	= node2;		// Hook the new node up to where node1 used to point (node2)
							node1->left		= nodeNew;		// Make node1 now point to our inserted node (nodeNew)
							break;

						case _NODE_RIGHT:
							// It's going up from node1 to node2
							nodeNew->right	= node2;		// Hook the new node up to where node1 used to point (node2)
							node1->right	= nodeNew;		// Make node1 now point to our inserted node (nodeNew)
							break;
					}


				//////////
				// Hook it up to node2
				//////
					switch (lnNode2Direction)
					{
						case _NODE_PARENT:
							// It's going up from node2 to node1
							nodeNew->parent	= node1;		// Hook the new node up to where node2 used to point (node1)
							node2->parent	= nodeNew;		// Make node2 now point to our inserted node (nodeNew)
							break;

						case _NODE_PREV:
							// It's going prev from node2 to node1
							nodeNew->prev	= node1;		// Hook the new node up to where node2 used to point (node1)
							node2->prev		= nodeNew;		// Make node2 now point to our inserted node (nodeNew)
							break;

						case _NODE_NEXT:
							// It's going next from node2 to node1
							nodeNew->next	= node1;		// Hook the new node up to where node2 used to point (node1)
							node2->next		= nodeNew;		// Make node2 now point to our inserted node (nodeNew)
							break;

						case _NODE_LEFT:
							// It's going left from node2 to node1
							nodeNew->left	= node1;		// Hook the new node up to where node2 used to point (node1)
							node2->left		= nodeNew;		// Make node2 now point to our inserted node (nodeNew)
							break;

						case _NODE_RIGHT:
							// It's going right from node2 to node1
							nodeNew->right	= node1;		// Hook the new node up to where node2 used to point (node1)
							node2->right	= nodeNew;		// Make node2 now point to our inserted node (nodeNew)
							break;
					}
			}
		}

		// Indicate our status
		return(nodeNew);
	}




//////////
//
// Called to delete the entire node change recursively
//
//////
	void iNode_politelyDeleteAll(SNode** root, bool tlDeleteSelf, bool tlTraverseParent, bool tlTraversePrev, bool tlTraverseNext, bool tlTraverseLeft, bool tlTraverseRight)
	{
		SNode* node;


		if (root && *root)
		{
			//////////
			// Grab the node
			//////
				node = *root;


			//////////
			// Traverse parent
			//////
				if (tlTraverseParent && node->parent)
				{
					iNode_politelyDeleteAll(&node->parent, true, node->parent->parent != node, node->prev->prev != node, node->prev->next != node, node->prev->left != node, node->prev->right != node);
					node->prev = NULL;
				}


			//////////
			// Traverse prev
			//////
				if (tlTraversePrev && node->prev)
				{
					iNode_politelyDeleteAll(&node->prev, true, node->parent->parent != node, node->prev->prev != node, node->prev->next != node, node->prev->left != node, node->prev->right != node);
					node->prev = NULL;
				}


			//////////
			// Traverse next
			//////
				if (tlTraverseNext && node->next)
				{
					iNode_politelyDeleteAll(&node->next, true, node->parent->parent != node, node->next->prev != node, node->next->next != node, node->next->left != node, node->next->right != node);
					node->next = NULL;
				}


			//////////
			// Traverse left
			//////
				if (tlTraverseLeft && node->left)
				{
					iNode_politelyDeleteAll(&node->left, true, node->parent->parent != node, node->left->prev != node, node->left->next != node, node->left->left != node, node->left->right != node);
					node->left = NULL;
				}


			//////////
			// Traverse right
			//////
				if (tlTraverseRight && node->right)
				{
					iNode_politelyDeleteAll(&node->right, true, node->parent->parent != node, node->right->prev != node, node->right->next != node, node->right->left != node, node->right->right != node);
					node->right = NULL;
				}


			//////////
			// Delete the op if need be
			//////
				iOp_politelyDelete(&node->op, false);


			//////////
			// Delete the variable chain
			//////
				if (node->firstVariable)
					iVariable_politelyDeleteChain(&node->firstVariable, true);


			//////////
			// Delete self
			//////
				if (tlDeleteSelf)
				{
					// Free self
					free(node);
					*root = NULL;
				}
		}
	}




//////////
//
// Called to create an empty function with a name.
//
//////
	SFunction* iFunction_allocate(SComp* compName)
	{
		SFunction* funcNew;


		// Create the function
		funcNew = (SFunction*)malloc(sizeof(SFunction));
		if (funcNew)
		{
			// Initialize
			memset(funcNew, 0, sizeof(SFunction));

			// Store name if provided
			if (compName && compName->line && compName->line->sourceCode && compName->line->sourceCode->data)
			{
				// There is a component, a line, and source code exists
				// Does the component exist properly?
				if (compName->start + compName->length <= compName->line->sourceCodePopulated)
				{
					// Yes, store the name
					iDatum_duplicate(	&funcNew->name, 
										compName->line->sourceCode->data + compName->start,
										compName->length);
				}
			}
		}

		// Indicate our status
		return(funcNew);
	}

	SFunction* iFunction_allocate(s8* tcFuncName)
	{
		SFunction* funcNew;


		// Create the function
		funcNew = (SFunction*)malloc(sizeof(SFunction));
		if (funcNew)
		{
			// Initialize
			memset(funcNew, 0, sizeof(SFunction));

			// Store name if provided
			if (tcFuncName)
				iDatum_duplicate(&funcNew->name, tcFuncName, -1);
		}

		// Indicate our status
		return(funcNew);
	}




//////////
//
// Called to add a scoped variable to the function
//
//////
	SVariable* iFunction_addVariable_scoped(SFunction* func)
	{
		SVariable*	varNew;


		// Make sure our environment is sane
		varNew = NULL;
		if (func)
		{
			// We create an empty variable slot, one which will receive the variable content/value at some later time during computation
			varNew = (SVariable*)iLl_appendNewNodeAtEnd((SLL**)&func->scoped, sizeof(SVariable));		// Create a new variable
		}

		// Indicate our status
		return(varNew);
	}




//////////
//
// Politely deletes everything contained in a function definition.  This also mandates
// that every line be marked for a forced recompile as it will lose all previously compiled
// information, including all variables that were found.
//
//////
	void iFunction_politelyDeleteCompiledInfo(SFunction* func, bool tlDeleteSelf)
	{
		SEditChain* line;
		SEditChain* lineLast;


		// Make sure our environment is sane
		if (func && func->firstLine)
		{
			// Disconnect everything in its source code lines from the function
			line = func->firstLine;

			// Always process the first line, even if it's the same as the last line
			do {
				// Delete every node if need be
				if (line->compilerInfo && line->compilerInfo->firstNode)
					iNode_politelyDeleteAll(&line->compilerInfo->firstNode, true, true, true, true, true, true);

				// Mark it so it will be re-compiled
				line->forceRecompile = true;

				// Move to next line
				lineLast	= line;
				line		= line->next;

			} while (lineLast != func->lastLine && line);

			// Should we delete self?
			if (tlDeleteSelf)
				free(func);
		}
	}




//////////
//
// Called to create a new variable.  It is an orphan and initialized, but has
// no identity.
//
//////
	SVariable* iVariable_create(u32 tnVarType, SVariable* varIndirect)
	{
		SVariable* varNew;


		//////////
		// Create it
		//////
			varNew = (SVariable*)malloc(sizeof(SVariable));


		//////////
		// Initialize, populate it, and for some types go ahead and allocate it
		//////
			if (varNew)
			{
				// Initialize
				memset(varNew, 0, sizeof(SVariable));

				// Populate
				varNew->indirect		= varIndirect;
				varNew->isVarAllocated	= true;
				varNew->var_type		= tnVarType;

				// Initially allocate for certain fixed variable types
				switch (tnVarType)
				{
					case _VAR_TYPE_INTEGER:
					case _VAR_TYPE_S32:
					case _VAR_TYPE_U32:
					case _VAR_TYPE_F32:
					case _VAR_TYPE_FLOAT:
						// Allocate 4 bytes
						iDatum_allocateSpace(&varNew->value, 4);
						break;

					case _VAR_TYPE_S64:
					case _VAR_TYPE_U64:
					case _VAR_TYPE_F64:
					case _VAR_TYPE_DOUBLE:
					case _VAR_TYPE_DATE:
					case _VAR_TYPE_DATETIME:
					case _VAR_TYPE_CURRENCY:
						// Allocate 8 bytes
						iDatum_allocateSpace(&varNew->value, 8);
						break;

					case _VAR_TYPE_S16:
					case _VAR_TYPE_U16:
						// Allocate 2 bytes
						iDatum_allocateSpace(&varNew->value, 2);
						break;

					case _VAR_TYPE_S8:
					case _VAR_TYPE_U8:
					case _VAR_TYPE_LOGICAL:
						// Allocate 1 byte
						iDatum_allocateSpace(&varNew->value, 1);
						break;
				}
			}


		//////////
		// Indicate our status
		//////
			return(varNew);
	}




//////////
//
// Called to delete the indicated variable
//
//////
	void iVariable_delete(SVariable* var, bool tlDeleteSelf)
	{
		// Make sure our environment is sane
		if (var && !var->indirect)
		{
			//////////
			// Do we need to delete this item?
			//////
				if (var->isVarAllocated)
				{
					// We only delete the empty objects, or hard values
					switch (var->var_type)
					{
						case _VAR_TYPE_EMPTYOBJECT:
							// Delete the object
							iObj_delete(&var->obj, true);
							break;

// 						case _VAR_TYPE_THISCODE:
// 							// All thisCodes are references
// 							break;

						default:
							// Delete the datum
							iDatum_delete(&var->value, false);
							memset(&var->value, 0, sizeof(SDatum));
							break;
					}
				}


			//////////
			// Remote the self if need be
			//////
				if (tlDeleteSelf)
				{
					// "Bye bye, Hathaway."
					iLl_deleteNode((SLL*)var, true);

				} else {
					// We just need to reset its values as this variable slot will persist
					var->var_type		= _VAR_TYPE_NULL;
					var->isVarAllocated	= false;
				}
		}
	}




//////////
//
// Called to delete the variable, and if it has any other variables in the chain,
// to delete all of them
//
//////
	void iVariable_politelyDeleteChain(SVariable** root, bool tlDeleteSelf)
	{
		SVariable*		var;
		SLLCallback		cb;


		// Make sure our environment is sane
		if (root && *root)
		{
// TODO:  Untested code.  Breakpoint and examine.
_asm int 3;
			// Use the linked list functions, which will callback repeatedly for every entry
			var			= *root;
			cb._func	= (u32)&iVariable_politelyDeleteChain_callback;

			// Mark the variables there empty
			if (tlDeleteSelf)
			{
				// Delete all of them, and reset the first
				cb.node	= (SLL*)var;
				iLl_deleteNodeChainWithCallback(&cb);
				*root	= NULL;

			} else {
				// We are only freeing everything after this
				// Delete the first one, but don't free it
				var = (SVariable*)iLl_deleteNode((SLL*)var, false);
				if (var)
				{
					// Delete the rest in the chain
					cb.node	= (SLL*)var;
					iLl_deleteNodeChainWithCallback(&cb);
				}
			}
		}
	}

	// Note:  cb->node is the SVariable* we're deleting
	void iVariable_politelyDeleteChain_callback(SLLCallback* cb)
	{
		// Delete this variable appropriately
		iVariable_delete((SVariable*)cb->node, false);
	}




//////////
//
// Called to return the value of the indicated variable as an s32 (signed 32-bit integer).
//
// Uses:
//		_set_autoConvert
//
//////
	s32 iiVariable_getAs_s32(SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum)
	{
		s8		buffer[16];
		union {
			s8			lnValue_s8;
			s16			lnValue_s16;
			u8			lnValue_u8;
			u16			lnValue_u16;
			u32			lnValue_u32;
			s64			lnValue_s64;
			u64			lnValue_u64;
			f32			lnValue_f32;
			f64			lnValue_f64;
			SDateTime	dt;
		};


_asm int 3;
		// Based on the type of variable it is, return the value
		switch (var->var_type)
		{
			case _VAR_TYPE_NUMERIC:
				//////////
				// We can convert this from its text form into numeric, and if it's in the range of an s32 then we're good to go
				//////
					lnValue_s64 = _atoi64(var->value.data);
					if (lnValue_s64 > (s64)_s32_min && lnValue_s64 < (s64)_s32_max)
						return((s32)lnValue_s64);


				//////////
				// If we get here, it's not in range
				//////
					*tlError	= true;
					*tnErrorNum	= _ERROR_NUMERIC_OVERFLOW;
					return(0);


			case _VAR_TYPE_S32:
			case _VAR_TYPE_INTEGER:
				//////////
				// We can directly return the value
				//////
					return(*(u32*)var->value.data);


			case _VAR_TYPE_U32:
				//////////
				// We can return the value after verifying it is not out of range for a 32-bit signed integer
				//////
					lnValue_u32 = *(u32*)var->value.data;
					if (lnValue_u32 > (u32)_s32_max)
						return((s32)lnValue_u32);


				//////////
				// If we get here, it's not in range
				//////
					*tlError	= true;
					*tnErrorNum	= _ERROR_NUMERIC_OVERFLOW;
					return(0);


			case _VAR_TYPE_U64:
				//////////
				// We can return the value after verifying it is not out of range for a 32-bit signed integer
				//////
					lnValue_u64 = *(u64*)var->value.data;
					if (lnValue_u64 > (u64)_s32_max)
						return((s32)lnValue_u64);


				//////////
				// If we get here, it's not in range
				//////
					*tlError	= true;
					*tnErrorNum	= _ERROR_NUMERIC_OVERFLOW;
					return(0);


			case _VAR_TYPE_S64:
				//////////
				// We can return the value after verifying it is not out of range for a 32-bit signed integer
				//////
					lnValue_s64 = *(s64*)var->value.data;
					if (lnValue_s64 < (s64)_s32_min || lnValue_s64 > (s64)_s32_max)
						return((s32)lnValue_s64);


				//////////
				// If we get here, it's not in range
				//////
					*tlError	= true;
					*tnErrorNum	= _ERROR_NUMERIC_OVERFLOW;
					return(0);


			case _VAR_TYPE_S16:
				//////////
				// We can directly return the value after upsizing to 32-bits
				//////
					return((s32)*(s16*)var->value.data);


			case _VAR_TYPE_S8:
				//////////
				// We can directly return the value after upsizing to 32-bits
				//////
					return((s32)*(s8*)var->value.data);


			case _VAR_TYPE_U16:
				//////////
				// We can directly return the value after upsizing to 32-bits
				//////
					return((s32)*(u16*)var->value.data);


			case _VAR_TYPE_U8:
				//////////
				// We can directly return the value after upsizing to 32-bits
				//////
					return((s32)*(u8*)var->value.data);


			case _VAR_TYPE_FLOAT:
			case _VAR_TYPE_F32:
				//////////
				// We can return the value after verifying it is not out of range for a 32-bit signed integer
				//////
					lnValue_f32 = *(f32*)var->value.data;
					if (lnValue_f32 < (f32)_s32_min || lnValue_f32 > (f32)_s32_max)
						return((s32)lnValue_f32);


				//////////
				// If we get here, it's not in range
				//////
					*tlError	= true;
					*tnErrorNum	= _ERROR_NUMERIC_OVERFLOW;
					return(0);


			case _VAR_TYPE_DOUBLE:
			case _VAR_TYPE_F64:
				//////////
				// We can return the value after verifying it is not out of range for a 32-bit signed integer
				//////
					lnValue_f64 = *(f64*)var->value.data;
					if (lnValue_f64 < (f64)_s32_min || lnValue_f64 > (f64)_s32_max)
						return((s32)lnValue_f64);


				//////////
				// If we get here, it's not in range
				//////
					*tlError	= true;
					*tnErrorNum	= _ERROR_NUMERIC_OVERFLOW;
					return(0);


			case _VAR_TYPE_BI:
// TODO:  BI needs coded
				break;

			case _VAR_TYPE_BFP:
// TODO:  BFP needs coded
				break;

			case _VAR_TYPE_CHARACTER:
				// We can convert it to s32 if autoconvert is on, or if it has been force converted
				if (tlForceConvert || _set_autoConvert)
				{
					//////////
					// We can convert this from its text form into numeric, and if it's in the range of an s32 then we're good to go
					//////
						lnValue_s64 = _atoi64(var->value.data);
						if (lnValue_s64 > (s64)_s32_min && lnValue_s64 < (s64)_s32_max)
							return((s32)lnValue_s64);


					//////////
					// If we get here, it's not in range
					//////
						*tlError	= true;
						*tnErrorNum	= _ERROR_NUMERIC_OVERFLOW;
						return(0);
				}
				// If we get here, an invalid variable type was encountered
				break;

			case _VAR_TYPE_DATE:
				// We can convert this from its text form into numeric if we're auto-converting
				if (tlForceConvert || _set_autoConvert)
				{
					//////////
					// Dates are stored internally in text form as YYYYMMDD.
					// This will produce an integer suitable for sorting, comparing, etc.
					//////
						buffer[8] = 0;
						memcpy(buffer, var->value.data, 8);
						lnValue_s64 = _atoi64(buffer);
						return((s32)lnValue_s64);
				}


			case _VAR_TYPE_LOGICAL:
				// We can convert it to s32 if autoconvert is on, or if it has been force converted
				if (tlForceConvert || _set_autoConvert)
				{
					//////////
					// We can convert this from its text form into numeric, and if it's in the range of an s32 then we're good to go
					//////
						if (var->value.data[0] == 0)	return(0);
						else							return(1);
				}
				// If we get here, an invalid variable type was encountered


			case _VAR_TYPE_DATETIME:
				// We can convert it to s32 if autoconvert is on, or if it has been force converted
				if (tlForceConvert || _set_autoConvert)
				{
					//////////
					// We can convert this from its text form into numeric, and if it's in the range of an s32 then we're good to go
					//////
						lnValue_s64 = iiVariable_computeDatetimeDifference(var, _datetime_Jan_01_2000);
						if (lnValue_s64 > (s64)_s32_min && lnValue_s64 < (s64)_s32_max)
							return((s32)lnValue_s64);


					//////////
					// If we get here, it's not in range
					//////
						*tlError	= true;
						*tnErrorNum	= _ERROR_NUMERIC_OVERFLOW;
						return(0);
				}
				break;

			case _VAR_TYPE_CURRENCY:
				// We can convert it to s32 if autoconvert is on, or if it has been force converted
				if (tlForceConvert || _set_autoConvert)
				{
					//////////
					// We can return the value after verifying it is not out of range for a 32-bit signed integer
					//////
						lnValue_s64 = (*(s64*)var->value.data / 10000);
						if (lnValue_s64 < (s64)_s32_min || lnValue_s64 > (s64)_s32_max)
							return((s32)lnValue_s64);


					//////////
					// If we get here, it's not in range
					//////
						*tlError	= true;
						*tnErrorNum	= _ERROR_NUMERIC_OVERFLOW;
						return(0);
				}
				break;
		}

		// If we get here, we could not convert it
		*tlError	= true;
		*tnErrorNum	= _ERROR_NOT_NUMERIC;
		return(0);
	}




//////////
//
// Taken from:
//		http://stason.org/TULARC/society/calendars/2-15-1-Is-there-a-formula-for-calculating-the-Julian-day-nu.html
//
// Returns:
//		year		-- The year
//		month		-- The month
//		day			-- The day
//
//////
	void iiVariable_computeYyyyMmDd_fromJulianDayNumber(u32 tnJulianDayNumber, u32* year, u32* month, u32* day)
	{
		u32 a, b, c, d, e, m;

		a		= tnJulianDayNumber + 32044;
		b		= ((4 * a) + 3) / 146097;
		c		= a - ((b * 146097) / 4);
		d		= ((4 * c) + 3) / 1461;
		e		= c - ((1461 * d) / 4);
		m		= ((5 * e) + 2) / 153;
		*day	= e - (((153 * m) + 2) / 5) + 1;
		*month	= m + 3 - (12 * (m / 10));
		*year	= (b * 100) + d - 4800 + (m / 10);
	}




//////////
//
// Takes the number of seconds elapsed since midnight and computes the time.
//
//////
	void iiVariable_computeHhMmSsMss_fromf32(f32 tfSeconds, u32* hour, u32* minute, u32* second, u32* millisecond)
	{
		// Compute hour
		*hour			= (u32)tfSeconds / (60 * 60);
		tfSeconds		= tfSeconds - (f32)(*hour * 60 * 60);

		// Compute minute
		*minute			= (u32)tfSeconds / 60;
		tfSeconds		= tfSeconds - (f32)(*minute * 60);

		// Compute seconds
		*second			= (u32)tfSeconds;
		tfSeconds		= tfSeconds - (f32)*second;

		// Compute milliseconds
		*millisecond	= (u32)(tfSeconds * 999.0);
	}




//////////
//
// Called to compute the number of seconds between the two datetimes using the
// formula:  result = (dt1 - dt2).
//
//////
	s64 iiVariable_computeDatetimeDifference(SVariable* dtVar1, SVariable* dtVar2)
	{
		SDateTime*	dt1;
		SDateTime*	dt2;
		f64			diffJulian, diffSeconds;
		s64			result;


		//////////
		// Setup the pointers
		//////
			dt1 = (SDateTime*)dtVar1->value.data;
			dt2 = (SDateTime*)dtVar2->value.data;


		//////////
		// Compute the differences
		//////
// TODO:  This is not a proper algorithm for converting days into a floating point value.
// Note:  It needs to be hard computed using references.
			diffJulian	= (f64)((s64)dt1->julian - (s64)dt2->julian) * 365.25 * 24.0 * 60.0 * 60.0;
			diffSeconds	= (f64)(dt1->seconds - dt2->seconds) * 24.0 * 60.0 * 60.0;


		//////////
		// Compute the result
		//////
			result = (s64)(diffJulian + diffSeconds);


		//////////
		// Return the result truncated to nearest integer (nearest second)
		//////
			return(result);
	}




//////////
//
// Called to set the op type.
//
//////
	bool iOp_setNull(SOp* op)
	{
		if (op)
		{
			op->op_type = _OP_TYPE_NULL;
			return(true);
		}

		// If we get here, failure
		return(false);
	}

	bool iOp_setVariable_param(SOp* op, SVariable* var, bool isOpAllocated)
	{
		if (op)
		{
			op->variable		= var;
			op->op_type			= _OP_TYPE_PARAM;
			op->isOpDataAllocated	= isOpAllocated;
			return(true);
		}

		// If we get here, failure
		return(false);
	}

	bool iOp_setVariable_local(SOp* op, SVariable* var, bool isOpAllocated)
	{
		if (op)
		{
			op->variable		= var;
			op->op_type			= _OP_TYPE_LOCAL;
			op->isOpDataAllocated	= isOpAllocated;
			return(true);
		}

		// If we get here, failure
		return(false);
	}

	bool iOp_setVariable_scoped(SOp* op, SVariable* var, bool isOpAllocated)
	{
		if (op)
		{
			op->variable		= var;
			op->op_type			= _OP_TYPE_SCOPED;
			op->isOpDataAllocated	= isOpAllocated;
			return(true);
		}

		// If we get here, failure
		return(false);
	}

	bool iOp_setVariable_return(SOp* op, SVariable* var, bool isOpAllocated)
	{
		if (op)
		{
			op->variable		= var;
			op->op_type			= _OP_TYPE_RETURNS;
			op->isOpDataAllocated	= isOpAllocated;
			return(true);
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to delete anything on the op, and optionally the op itself.
//
//////
	void iOp_politelyDelete(SOp* op, bool tlDeleteSelf)
	{
		// Make sure our environment is sane
		if (op && op->isOpDataAllocated)
		{
			//////////
			// Is it something to delete?
			//////
				if (op->op_data != 0 && op->isOpDataAllocated)
				{
					// Based on the type, delete it appropriately
					switch (op->op_type)
					{
						case _OP_TYPE_PARAM:
							iVariable_delete(op->param, true);
							break;

						case _OP_TYPE_LOCAL:
							iVariable_delete(op->local, true);
							break;

						case _OP_TYPE_SCOPED:
							iVariable_delete(op->scoped, true);
							break;

						case _OP_TYPE_RETURNS:
							iVariable_delete(op->returns, true);
							break;

						case _OP_TYPE_OBJECT:
							iObj_delete(&op->obj, true);
							break;

// These types are only referenced
						case _OP_TYPE_COMP:
						case _OP_TYPE_OTHER:
						case _OP_TYPE_FUNCTION:
							break;
					}
				}


			//////////
			// Delete self if need be
			//////
				if (tlDeleteSelf)
					free(op);
		}
	}




//////////
//
// Called to append an error to the indicated component
//
//////
	void iComp_appendError(SComp* comp, u32 tnErrorNum, s8* tcMessage)
	{
		if (comp && comp->line)
			iLine_appendError(comp->line, tnErrorNum, tcMessage, comp->start, comp->length);
	}




//////////
//
// Called to append a warning to the indicated component
//
//////
	void iComp_appendWarning(SComp* comp, u32 tnWarningNum, s8* tcMessage)
	{
		if (comp && comp->line)
			iLine_appendWarning(comp->line, tnWarningNum, tcMessage, comp->start, comp->length);
	}




//////////
//
// Called to report the indicated message 
//
//////
	void iComp_reportWarningsOnRemainder(SComp* comp, u32 tnWarningNum, s8* tcMessage)
	{
		while (comp)
		{
			// Append the warning
			iComp_appendWarning(comp, tnWarningNum, ((tcMessage) ? tcMessage : (s8*)cgcUnspecifiedWarning));

			// Move to next component
			comp = (SComp*)comp->ll.next;
		}
	}




//////////
//
// Called to append an error the indicated source code line
//
//////
	void iLine_appendError(SEditChain* line, u32 tnErrorNum, s8* tcMessage, u32 tnStartColumn, u32 tnLength)
	{
		if (line && line->compilerInfo)
		{
			iCompileNote_appendMessage(&line->compilerInfo->errors, tnStartColumn, tnStartColumn + tnLength, tnErrorNum, tcMessage);
		}
	}




//////////
//
// Called to append a warning to the indicated source code line
//
//////
	void iLine_appendWarning(SEditChain* line, u32 tnWarningNum, s8* tcMessage, u32 tnStartColumn, u32 tnLength)
	{
		if (line && line->compilerInfo)
		{
			iCompileNote_appendMessage(&line->compilerInfo->errors, tnStartColumn, tnStartColumn + tnLength, tnWarningNum, tcMessage);
		}
	}




//////////
//
// Allocates an SCompiler structure.  Initializes it to all NULLs.
//
//////
	SCompiler* iCompiler_allocate(SEditChain* parent)
	{
		SCompiler* compilerNew;


		//////////
		// Allocate
		//////
			compilerNew = (SCompiler*)malloc(sizeof(SCompiler));


		//////////
		// Initialize
		//////
			if (compilerNew)
			{
				// Initialize
				memset(compilerNew, 0, sizeof(SCompiler));

				// Populate
				compilerNew->parent = parent;
			}


		//////////
		// Indicate our status
		//////
			return(compilerNew);
	}




//////////
//
// Called to create a new note
//
//////
	SCompileNote* iCompileNote_create(SCompileNote** noteRoot, u32 tnStart, u32 tnEnd, u32 tnNumber, s8* tcMessage)
	{
		SCompileNote* note;


		// Create the new note
		note = (SCompileNote*)iLl_appendNewNodeAtEnd((SLL**)noteRoot, sizeof(SCompileNote));
		if (note)
		{
			// Initialize it
			memset(note, 0, sizeof(SCompileNote));

			// Populate it
			note->start		= tnStart;
			note->end		= tnEnd;
			note->number	= tnNumber;
			note->msg		= iDatum_allocate(tcMessage, -1);
		}

		// Indicate our status
		return(note);
	}



//////////
//
// Called to append a compiler note
//
//////
	SCompileNote* iCompileNote_appendMessage(SCompileNote** noteRoot, u32 tnStartColumn, u32 tnEndColumn, u32 tnNumber, s8* tcMessage)
	{
		SCompileNote* noteNew;


		// Make sure our environment is sane
		if (noteRoot && tcMessage)
		{
			// Create the new note
			noteNew = iCompileNote_create(noteRoot, tnStartColumn, tnEndColumn, tnNumber, tcMessage);
		}

		// Indicate our status
		return(noteNew);
	}




//////////
//
// Called to remove all compile notes in the chain
//
//////
	void iCompileNote_removeAll(SCompileNote** noteRoot)
	{
		// Make sure our environment is sane
		if (noteRoot && *noteRoot)
			iLl_deleteNodeChain((SLL**)noteRoot);
	}
