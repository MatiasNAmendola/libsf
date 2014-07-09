//////////
//
// /libsf/source/vjr/engine.cpp
//
//////
// Version 0.30
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jul.05.2014
//////
// Change log:
//     Jul.05.2014 - Initial creation
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
// Called to execute a stand-alone command, such as from the command window.
//
//////
	bool iEngine_executeStandaloneCommand(SEditChain* line)
	{
		bool		llManufactured;
		SComp*		comp;
		SComp*		compNext;
		SVariable*	var;
		SVariable*	varText;


// Incomplete function
return(false);


		// Make sure our environment is sane
		if (line && line->sourceCode && line->sourceCode->data && line->sourceCodePopulated > 0)
		{
			// Parse out the line
			iComps_translateSourceLineTo(&cgcFundamentalSymbols[0], line);
			if (!line->compilerInfo->firstComp)
				return(false);		// Nothing to compile on this line
			
			// Get the first component
			comp = line->compilerInfo->firstComp;


			//////////
			// If it's a line comment, we don't need to process it
			//////
				if (comp->iCode == _ICODE_COMMENT || comp->iCode == _ICODE_LINE_COMMENT)
					return(false);


			//////////
			// Perform natural source code fixups
			//////
				iComps_removeStartEndComments(line);		// Remove /* comments */
				iComps_fixupNaturalGroupings(line);			// Fixup natural groupings [_][aaa][999] becomes [_aaa999], [999][.][99] becomes [999.99], etc.
				iComps_removeWhitespaces(line);				// Remove whitespaces [use][whitespace][foo] becomes [use][foo]


			//////////
			// Translate sequences to known keywords
			//////
				iComps_translateToOthers(&cgcKeywordKeywords[0], line);


			//////////
			// Based on the first keyword, process it
			//////
				switch (comp->iCode)
				{
					case _ICODE_QUESTION_MARK:
						// It is a "? something" command
						if (!(compNext = (SComp*)comp->ll.next))
						{
							// Syntax error, expected "? something" got only "?"
							iEditChainManager_appendLine(screenData, (s8*)cgcSyntaxError, -1);
							return(false);

						} else {
							// It's a number, display it
							if (var = iEngine_getVariableFromComponent(compNext, &llManufactured))
							{
								// We have a variable we can display its contents
								varText = iVariable_convertForDisplay(var);

// TODO:  Working here

								// Release the variable if it was manufactured
								if (llManufactured)
									iVariable_delete(varText, true);
							}
						}
						break;

// 					case _ICODE_WAIT:
// 						if (comp->ll.next && ((SComp*)comp->ll.next)->iCode == _ICODE_WINDOW)
// 						{
// 							// It's a wait window
// 
// 						} else {
// 							// Not a currently supported command
// 							return(false);
// 						}
// 						break;
// 
					default:
						if (comp->ll.next && ((SComp*)comp->ll.next)->iCode == _ICODE_EQUAL_SIGN)
						{
							// It is an assignment
// TODO:  Working here

						} else {
							// Not a currently supported command
							return(false);
						}
				}
// TODO:  Working here
				// If we get here, we're good
				return(true);

		} else {
			// Failure
			return(false);
		}
	}




//////////
//
// Called to obtain a variable from the component.  It will translate a literal
// into a variable, or if it's already a variable reference it will copy the
// reference.
//
//////
	SVariable* iEngine_getVariableFromComponent(SComp* comp, bool* tlManufactured)
	{
// TODO:  working here
		return(NULL);
	}
