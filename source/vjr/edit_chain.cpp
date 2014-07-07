//////////
//
// /libsf/source/vjr/edit_chain.cpp
//
//////
// Version 0.30
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jul.06.2014
//////
// Change log:
//     Jul.06.2014 - Initial creation
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
// Called to make sure enough information is populated currently in the ecm->ecCursorLine->sourceCode
// buffer for the new indicated line length.
//
//////
	bool iEditChain_ensureLineLength(SEditChainManager* ecm, s32 newLineLength)
	{
		SEditChain* line;


		// Make sure the environment is sane
		if (ecm && ecm->ecCursorLine)
		{
			// Has this line had its data allocated?
			line = ecm->ecCursorLine;
			if (!line->sourceCode)
			{
				// We need to allocate the initial data block
				iDatum_allocateSpace(line->sourceCode, max(_ECM_MINIMUM_LINE_ALLOCATION_LENGTH, newLineLength));
				line->sourceCodePopulated	= 0;
			}

			// Is there room from where we are to the new line length?
			if (line->sourceCode->length > newLineLength)
				return(true);		// We're good

			// If we get here, we need to reallocate
			return(iDatum_resize(line->sourceCode, newLineLength + _ECM_MINIMUM_LINE_ALLOCATION_LENGTH));
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Free the edit chain
//
//////
	void iEditChain_free(SEditChain** root, bool tlDeleteSelf)
	{
		SEditChain*		chain;
		SEditChain*		chainNext;


// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
		// Make sure our environment is sane
		if (root && *root)
		{
			// Repeat throughout the entire chain
			chain = *root;
			while (chain)
			{
				//////////
				// Note next item in chain
				//////
					chainNext = (SEditChain*)chain->ll.next;


				//////////
				// Delete any extra information associated with this chain entry
				//////
					iExtraInfo_free(NULL, chain, &chain->extra_info, true);


				//////////
				// Delete this item's components
				//////
					iDatum_delete(chain->sourceCode, true);


				//////////
				// Free self
				//////
					if (tlDeleteSelf)
						free(chain);


				//////////
				// Move to next item in the chain
				//////
					chain = chainNext;
			}


			//////////
			// Free self
			//////
				if (tlDeleteSelf)
					*root = NULL;	// It would've been freed above, so we just update the pointer
		}
	}




//////////
//
// Called to insert a character
//
//////
	bool iEditChain_characterInsert(SEditChainManager* ecm, u8 asciiChar)
	{
		s32				lnI;
		SEditChain*		line;


		// Make sure our environment is sane
		if (ecm && !ecm->isReadOnly && ecm->ecCursorLine && ecm->ecCursorLine->sourceCode)
		{
			// Make sure there's room enough for the keystroke
			line = ecm->ecCursorLine;
			if (iEditChain_ensureLineLength(ecm, ecm->ecCursorLine->sourceCodePopulated + 1))
			{
				// They could've been beyond the end of line, and if so then we need to insert spaces between the end and here
				if (ecm->column > line->sourceCodePopulated)
				{
					// Fill with spaces
					for (lnI = line->sourceCodePopulated; lnI < ecm->column; lnI++)
						line->sourceCode->data[lnI] = ' ';
				}

				// Move everything from the end of the line to where we are right one character
				for (lnI = line->sourceCodePopulated + 1; lnI > ecm->column && lnI > 0; lnI--)
					line->sourceCode->data[lnI] = line->sourceCode->data[lnI - 1];

				// Insert the character
				line->sourceCode->data[ecm->column] = asciiChar;

				// Move to the next column
				++ecm->column;

				// Increase the populated length
				++line->sourceCodePopulated;

				// If we're past the end, we need to indicate our populated line length
				if (ecm->column > line->sourceCodePopulated)
					line->sourceCodePopulated = ecm->column;

				// Indicate success
				return(true);
			}
		}

		// If we get here, we could not insert it
		return(false);
	}




//////////
//
// Called to overwrite the existing character wherever we are
//
//////
	bool iEditChain_characterOverwrite(SEditChainManager* ecm, u8 asciiChar)
	{
		s32				lnI;
		SEditChain*		line;


		// Make sure our environment is sane
		if (ecm && !ecm->isReadOnly && ecm->ecCursorLine && ecm->ecCursorLine->sourceCode)
		{
			// Is there room to inject it?
			line = ecm->ecCursorLine;
			if (iEditChain_ensureLineLength(ecm, ecm->ecCursorLine->sourceCodePopulated + 1))
			{
				if (ecm->column > line->sourceCodePopulated)
				{
					// We need to insert it because we're at the end of the populated length
					return(iEditChain_characterInsert(ecm, asciiChar));

				} else {
					// We can overwrite it

					// They could've been beyond the end of line, and if so then we need to insert spaces between the end and here
					if (ecm->column > line->sourceCodePopulated)
					{
						// Fill with spaces
						for (lnI = line->sourceCodePopulated; lnI < ecm->column; lnI++)
							line->sourceCode->data[lnI] = ' ';
					}

					// Overwrite the character
					line->sourceCode->data[ecm->column] = asciiChar;

					// Move to the next column
					++ecm->column;

					// If we're past the end, we need to indicate our populated line length
					if (ecm->column > line->sourceCodePopulated)
						line->sourceCodePopulated = ecm->column;

					// Indicate success
					return(true);
				}
			}
		}

		// If we get here, we could not overwrite
		return(false);
	}




//////////
//
// Called to delete the character where we are, which, depending on insert mode,
// will affect the line in different ways.
//
//////
	bool iEditChain_characterDelete(SEditChainManager* ecm)
	{
		s32			lnI;
		SEditChain* line;


		// Make sure our environment is sane
		if (ecm && !ecm->isReadOnly && ecm->ecCursorLine && ecm->ecCursorLine->sourceCode)
		{
			// Grab the line
			line = ecm->ecCursorLine;

			// If we're in the populated area
			if (ecm->column < line->sourceCodePopulated)
			{
				// Move everything left one character
				for (lnI = ecm->column; lnI < line->sourceCodePopulated; lnI++)
					line->sourceCode->data[lnI] = line->sourceCode->data[lnI + 1];

				// Reduce the length of the populated portion of the line by one
				--line->sourceCodePopulated;

				// Indicate success
				return(true);
			}
		}

		// If we get here, we could not overwrite
		return(false);
	}
