//////////
//
// /libsf/vvm/vvmoss/vo_Bxml.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     December 31, 2012
//////
// Change log:
//     December 31, 2012 - Initial creation
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
// Examples:
//		/this(0).level(0).data(3).attrib(0).name
//		/this(0).level(0).data(3).attrib(0).value
//		/this(0).level(0).data(3).attrib(name).value
//		/this(1).field(2):_avalue(1)
//		/this(1).field(2):_aname(1)
//		/this*.foo*.way
//		/this.foo.way
//
//




//////////
//
// Load the file into a buffer, and then call the load algorithm to load it into an XML handle
//
// Note:  Error codes exist in range of -101 to -103 from this function, and -1 to -99 from the
//        actual ibxml_asciiLoadBuffer() function:
//
//		-101			- File could not be opened
//		-102			- Unable to allocate memory for load
//		-103			- Unable to read file into memory
//
/////
	SBxml* ibxml_asciiLoadFile(s8* filename, u64* tnBytesRead, u64* tnErrorOffset, u64* tnErrorCode)
	{
		u64		lfh, lnFileSize, lnNumread;
		s8*		tptr;
		SBxml*	lbxml;


		// Initialize our variables
		*tnErrorOffset	= -1;
		*tnErrorCode	= 0;

		// Open the file specified by the user
		lfh = oss_sharedAsciiOpenFile(filename, false, false, false, false, false, false, false, false);
		if ((s64)lfh < 0)
		{
			iibxml_storeErrorCode(tnErrorOffset, 0, tnErrorCode, -101);
			return(NULL);		// No file could be opened
		}


		// Find out how big it is
		lnFileSize = oss_sharedAsciiFileSize(lfh);


		// Allocate memory
		tptr = (s8*)oss_alloc((u32)lnFileSize, false);
		if (tptr == NULL)
			return((SBxml*)-102);		// Cannot allocate memory


		// Read into memory
		lnNumread = oss_sharedAsciiReadFile(lfh, tptr, (u32)lnFileSize);

		// Store the bytes read if required
		if (tnBytesRead)
			*tnBytesRead = lnNumread;

		// Did we read the correct number?
		if (lnNumread != lnFileSize)
			return((SBxml*)-103);


		// Close the file
		oss_sharedAsciiCloseFile(lfh);


		// Load it as XML
		lbxml = ibxml_asciiLoadBuffer(tptr, lnFileSize, tnErrorOffset, tnErrorCode);


		// Note:  ibxml_asciiLoadBuffer() makes copies of every string as needed
		oss_free(tptr);


		// All done!
		return(lbxml);
	}




//////////
//
// Physically parse the raw text of the input file.
//
// Note:  This process only accepts ASCII files.
//        It will not parse UNICODE or wide-character files.
//
//----------
// Error codes in tnErrorCode, with tnErrorOffset being offset into buffer where it occurred:
//		-1			- Syntax error
//
/////
	SBxml* ibxml_asciiLoadBuffer(s8* buffer, u64 tnMaxLength, u64* tnErrorOffset, u64* tnErrorCode)
	{
		s8		lcQuoteChar;
		s32		lnLevel;
		u64		lnOffset, lnLength, lnAttrTagLength, lnAttrDataLength, lnNumberLength, lnNumberLength1, lnNumberLength2, lnValue, lnValue1, lnValue2;
		bool	llProcessingAttributes;
		SBxml*	bxml;
		SBxmla*	bxmla;
		SBxmla*	bxmlaNew;


// TODO:  This algorithm currently leaks memory if there is an error. This will need to be fixed.
		// We must now be at the root node
		if (tnMaxLength == 0)
			tnMaxLength = strlen(buffer);


		// See what's there
		lnLevel		= 0;
		bxml		= NULL;
		bxmla		= NULL;
		bxmlaNew	= NULL;
		lnOffset	= 0;
		while (lnOffset < tnMaxLength && lnLevel >= 0)
		{
			// Skip past initial white spaces
			lnOffset += ioss_skipWhitespacesAndCrLf(buffer + lnOffset, tnMaxLength - lnOffset);
			if (lnOffset >= tnMaxLength)
				break;		// We've reached the end of the XML file


			// Right now, we should be on the first non-whitespace character at (wherever we are in the file)
			if (buffer[lnOffset] == '<')
			{
				if (ioss_verifyLength(lnOffset + 3, tnMaxLength) && buffer[lnOffset + 1] == '!' && buffer[lnOffset + 2] == '-' && buffer[lnOffset + 3] == '-')
				{
					// Ignore comments, skip forward until we find "-->"
					lnLength = 4;
					while (ioss_verifyLength(lnOffset + lnLength + 2, tnMaxLength) && !(buffer[lnOffset + lnLength] == '-' && buffer[lnOffset + lnLength + 1] == '-' && buffer[lnOffset + lnLength + 2] == '>'))
						++lnLength;

					// Append an attribute which contains the comment data
					bxmlaNew = (SBxmla*)oss_SEChain_append(&bxml->_attributes, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SBxmla), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);
					if (!bxmlaNew)
						return((SBxml*)-1);

					// Update the parent
					bxmlaNew->_parent = bxml;

					// Store the tag name and allocate space for the data, set it to NULLs
					oss_datumSet (&bxmlaNew->_name,	(u8*)cgcAutoComment,		sizeof(cgcAutoComment) - 1,					false);
					oss_datum2Set(&bxmlaNew->_data,	(u8*)buffer + lnOffset,		lnLength + 3,				lnLength + 3,	false);

					// If we're at the end of the input, syntax error
					if (!ioss_verifyLength(lnOffset + 2, tnMaxLength))
						return((SBxml*)-1);		// We reached end-of-file before finding the closing comment tag

					// If we get here, we went past our comment
					lnOffset += lnLength + 3;

				} else if (ioss_verifyLength(lnOffset + 1, tnMaxLength) && buffer[lnOffset + 1] == '/') {
					// We've reached the </ which should be </something> where "something" matches the parent bxml entry
					lnOffset += 2;
					if (lnOffset >= tnMaxLength)
						return((SBxml*)-1);		// We've reached the end unexpectedly

					// Is it alpha?
					if (!ioss_isAlpha(buffer[lnOffset + 1]))
						return((SBxml*)-1);

					// Scan forward until we reach a non-contiguous group of alphanumeric characters
					lnLength = iibxml_scanForwardToNonAlphanumeric(buffer + lnOffset, tnMaxLength - lnOffset);
					if (lnLength + lnOffset >= tnMaxLength)
						return((SBxml*)-1);		// We've reached the end unexpectedly
					// Verify we have proper syntax
					if (buffer[lnOffset + lnLength] != '>')
						return((SBxml*)-1);		// Syntax error

					// Verify our environment is sane
					if (!bxml)
						return((SBxml*)-1);		// Syntax error

					// See what they're closing
					if (!bxml->closed)
					{
						// They have to be closing this tag
						if (lnLength != bxml->_name.length || _memicmp(buffer + lnOffset, bxml->_name.data._s8, (u32)lnLength) != 0)
							return((SBxml*)-1);		// Syntax error
						// If we get here, they properly closed it
						bxml->closed = true;
						// Still staying at same level for siblings being added

					} else {
						// They have to be closing the parent tag
						if (!bxml->ll4.parent || lnLength != ((SBxml*)bxml->ll4.parent)->_name.length || _memicmp(buffer + lnOffset, ((SBxml*)bxml->ll4.parent)->_name.data._s8, (u32)lnLength) != 0)
							return((SBxml*)-1);		// Syntax error

						// If we get here, they properly closed it
						bxml = (SBxml*)bxml->ll4.parent;
						bxml->closed = true;
						// Go back up to the appropriate level
						lnLevel = bxml->level;
					}
					// If we get here, we found a matching tag, so we're good

					// Move past this tag
					lnOffset += lnLength + 1;

				} else {
					// It must be a tag
					// Get the offset to the tag name
					++lnOffset;
					if (lnOffset >= tnMaxLength)
						return((SBxml*)-1);		// We've reached the end unexpectedly

					// Is it alpha?
					if (!ioss_isAlpha(buffer[lnOffset + 1]))
						return((SBxml*)-1);

					// Scan forward until we reach a non-contiguous group of alphanumeric characters
					lnLength = iibxml_scanForwardToNonAlphanumeric(buffer + lnOffset, tnMaxLength - lnOffset);
					if (lnLength + lnOffset >= tnMaxLength)
						return((SBxml*)-1);		// We've reached the end unexpectedly

					// Store the entry
					if (!bxml || lnLevel == bxml->level)
					{
						// Adding a sibling
						bxml = iibxml_createNewSBxml(lnLevel, bxml, false, NULL, bxml, ((bxml) ? (SBxml*)bxml->ll4.parent : NULL), NULL);

					} else {
						// Adding a child
						bxml = iibxml_createNewSBxml(lnLevel, bxml, true, NULL, NULL, bxml, NULL);
					}

					// Verify we added the tag successfully
					if (!bxml)
						return((SBxml*)-1);		// Memory error??

					// Store the tag name
					oss_datumSet(&bxml->_name, (u8*)buffer + lnOffset, lnLength, false);

					// Skip past the name
					lnOffset += lnLength;

					// Iterate repeatedly until we exhaust any attributes (should there be any)
					llProcessingAttributes = true;
					while (llProcessingAttributes)
					{
						// Next non-whitespace character must be a letter (attribute), "/" closing single tag, or ">" closing first tag
						lnOffset += ioss_skipWhitespaces(buffer + lnOffset, tnMaxLength - lnOffset);
						if (lnOffset >= tnMaxLength)
							return((SBxml*)-1);		// We've reached the end unexpectedly

						// See what character is there
						switch (buffer[lnOffset])
						{
							case '/':
								// It's likely a /> closing tag
								if (ioss_verifyLength(lnOffset + 1, tnMaxLength) && buffer[lnOffset + 1] == '>')
								{
									// We're good
									llProcessingAttributes = false;
									lnOffset += 2;
									// They closed this tag
									bxml->closed = true;

								} else {
									// Syntax error
									return((SBxml*)-1);
								}
								break;

							case '>':
								// It's a > closing tag
								// We can skip this tag and continue processing
								llProcessingAttributes = false;
								++lnOffset;
								// All following entries will be at a new level
								++lnLevel;
								break;

							default:
								// See what it is, if it's alpha or underscore, it is another attribute
// TODO:  this nop can be removed, it's kept here for easy breakpoint testing
_asm nop;
								while (ioss_isAlpha(buffer[lnOffset]))
								{
									// It could be an attribute
									lnAttrTagLength = iibxml_scanForwardToNonAlphanumeric(buffer + lnOffset, tnMaxLength - lnOffset);

									// Verify our length is still on track
									if (lnOffset + lnAttrTagLength >= tnMaxLength)
										return((SBxml*)-1);		// We've reached the end unexpectedly

									// We have the attribute name, but what's after it?
									switch (buffer[lnOffset + lnAttrTagLength])
									{
										case '=':
											// Access the quote character
											lcQuoteChar	= buffer[lnOffset + lnAttrTagLength + 1];
											if (lcQuoteChar != 34 && lcQuoteChar != 39)
												return((SBxml*)-1);		// It wasn't a quote character, syntax error
											
											// Find out how long the quoted portion is
											lnAttrDataLength = iibxml_scanForwardToCharacter(buffer + lnOffset + lnAttrTagLength + 1 + 1, tnMaxLength - lnOffset - lnAttrTagLength - 1 - 1, lcQuoteChar);
											if (lnLength + lnOffset + lnAttrTagLength + lnAttrDataLength + 1 + 1 >= tnMaxLength)
												return((SBxml*)-1);		// We've reached the end unexpectedly

											// We're sitting no the closing quote character
											// Append this attribute
											bxmlaNew = (SBxmla*)oss_SEChain_append(&bxml->_attributes, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SBxmla), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);
											if (!bxmlaNew)
												return((SBxml*)-1);

											// Update the parent
											bxmlaNew->_parent = bxml;

											// Store the tag name and data
											oss_datumSet (&bxmlaNew->_name, (u8*)buffer + lnOffset,								lnAttrTagLength,						false);
											oss_datum2Set(&bxmlaNew->_data, (u8*)buffer + lnOffset + lnAttrTagLength + 1 + 1,	lnAttrDataLength, lnAttrDataLength,		false);

											// Move past this attribute
											lnOffset += lnAttrTagLength + 1 + 1 + lnAttrDataLength + 1;
											if (lnOffset >= tnMaxLength)
												return((SBxml*)-1);		// We've reached the end unexpectedly
											break;

										case ':':
											// Verify our length is still on track
											if (lnOffset + lnAttrTagLength + 1 >= tnMaxLength)
												return((SBxml*)-1);		// We've reached the end unexpectedly

											// See if the next character is also a colon
											if (buffer[lnOffset + lnAttrTagLength + 1] == ':')
											{
												// It is, so it's attr::#
												// Grab the number after the colon, and allocate that much space
												lnNumberLength = iibxml_scanForwardToNonNumeric(buffer + lnOffset + lnAttrTagLength + 2, tnMaxLength - lnOffset - lnAttrTagLength - 2);

												// Verify our file position is okay, that there was a number
												if (lnOffset + lnAttrTagLength + 2 + lnNumberLength >= tnMaxLength)
													return((SBxml*)-1);		// We've reached the end unexpectedly
												if (lnNumberLength == 0)
													return((SBxml*)-1);		// There was no number, a syntax error

												// Get the value of the number
												lnValue = ioss_convertValidatedNumericStringToU32(buffer + lnOffset + lnAttrTagLength + 2, (u32)lnNumberLength);

												// Append this attribute
												bxmlaNew = (SBxmla*)oss_SEChain_append(&bxml->_attributes, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SBxmla), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);
												if (!bxmlaNew)
													return((SBxml*)-1);

												// Update the parent
												bxmlaNew->_parent = bxml;

												// Store the tag name and allocate space for the data, set it to NULLs
												oss_datumSet		  (&bxmlaNew->_name,	(u8*)buffer + lnOffset,		lnAttrTagLength,	false);
												oss_datum2SetNullString(&bxmlaNew->_data,								 lnValue,			true);

												// Move past this attribute size allocator
												lnOffset += lnAttrTagLength + 2 + lnNumberLength;
												if (lnOffset >= tnMaxLength)
													return((SBxml*)-1);		// We've reached the end unexpectedly
												// When we get here, we're ready for the next attribute or end of the tag

											} else {
												// It's not a colon, it must be either attr:#= or attr:#:#=
												lnNumberLength1 = iibxml_scanForwardToNonNumeric(buffer + lnOffset + lnAttrTagLength + 1, tnMaxLength - lnOffset - lnAttrTagLength - 1);

												// Verify our file position is okay, that there was a number
												if (lnOffset + lnAttrTagLength + 1 + lnNumberLength1 >= tnMaxLength)
													return((SBxml*)-1);		// We've reached the end unexpectedly
												if (lnNumberLength1 == 0)
													return((SBxml*)-1);		// There was no number, a syntax error

												// Get the value of the first number
												lnValue = ioss_convertValidatedNumericStringToU32(buffer + lnOffset + lnAttrTagLength + 1, (u32)lnNumberLength1);

												// See what's after the number, it must be either a colon or an equal sign
												switch (buffer[lnOffset + lnAttrTagLength + 1 + lnNumberLength1])
												{
													case ':':
														// It's attr:#:#=
														lnNumberLength2 = iibxml_scanForwardToNonNumeric(buffer + lnOffset + lnAttrTagLength + 1 + lnNumberLength1 + 1, tnMaxLength - lnOffset - lnAttrTagLength - 1 - lnNumberLength1 - 1);

														// Verify our file position is okay, that there was a number
														if (lnOffset + lnAttrTagLength + 1 + lnNumberLength1 + 1 + lnNumberLength2 >= tnMaxLength)
															return((SBxml*)-1);		// We've reached the end unexpectedly
														if (lnNumberLength2 == 0)
															return((SBxml*)-1);		// There was no number, a syntax error

														// Get the value of the second number
														lnValue2 = ioss_convertValidatedNumericStringToU32(buffer + lnOffset + lnAttrTagLength + 1 + lnNumberLength1 + 1, (u32)lnNumberLength2);
														if (lnValue >= lnValue2)
														{
															// The attribute is something like name:20:5=
															lnValue1 = lnValue;		// lnValue1 = 20, lnValue2 = 5

														} else {
															// The attribute is something like name:5:20=
															lnValue1 = lnValue2;	// lnValue1 = 20, lnValue2 = 20
														}

														// Append this attribute
														bxmlaNew = (SBxmla*)oss_SEChain_append(&bxml->_attributes, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SBxmla), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);
														if (!bxmlaNew)
															return((SBxml*)-1);

														// Update the parent
														bxmlaNew->_parent = bxml;

														// Store the tag name and allocate space for the data, set it to NULLs
														oss_datumSet (&bxmlaNew->_name,	(u8*)buffer + lnOffset,																		lnAttrTagLength,				false);
														oss_datum2Set(&bxmlaNew->_data,	(u8*)buffer + lnOffset + lnAttrTagLength + 1 + lnNumberLength1 + 1 + lnNumberLength2 + 1,	lnValue2,			lnValue1,	false);

														// Move past this attribute size allocator
														lnOffset += lnAttrTagLength + 1 + lnNumberLength1 + 1 + lnNumberLength2 + 1 + lnValue2;
														if (lnOffset >= tnMaxLength)
															return((SBxml*)-1);		// We've reached the end unexpectedly
														// When we get here, we're ready for the next attribute or end of the tag
														break;

													case '=':
														// It's attr:#=
														// Get the value of the number
														lnValue = ioss_convertValidatedNumericStringToU32(buffer + lnOffset + lnAttrTagLength + 1, (u32)lnNumberLength1);

														// Append this attribute
														bxmlaNew = (SBxmla*)oss_SEChain_append(&bxml->_attributes, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SBxmla), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);
														if (!bxmlaNew)
															return((SBxml*)-1);

														// Update the parent
														bxmlaNew->_parent = bxml;

														// Store the tag name and allocate space for the data, set it to NULLs
														oss_datumSet (&bxmlaNew->_name,	(u8*)buffer + lnOffset,												lnAttrTagLength,			false);
														oss_datum2Set(&bxmlaNew->_data,	(u8*)buffer + lnOffset + lnAttrTagLength + 1 + lnNumberLength1 + 1,	lnValue,		lnValue,	false);

														// Move past this attribute size allocator
														lnOffset += lnAttrTagLength + 1 + lnNumberLength1 + 1 + lnValue;
														if (lnOffset >= tnMaxLength)
															return((SBxml*)-1);		// We've reached the end unexpectedly
														// When we get here, we're ready for the next attribute or end of the tag
														break;

													default:
														// It's a syntax error
														return((SBxml*)-1);
												}
											}
											break;

										default:
											// Syntax error
											return((SBxml*)-1);
											break;
									}
									// When we get here, this attribute has been processed

									// Skip past any whitespaces between attributes
									lnOffset += ioss_skipWhitespaces(buffer + lnOffset, tnMaxLength - lnOffset);
									if (lnOffset >= tnMaxLength)
										return((SBxml*)-1);
								}
								// When we get here, we must be at end of file, sitting on / or >.
								// Anything else is a syntax error.
								// These conditions will be tested in the llProcessingAttributes loop
// TODO:  this nop can be removed, it's kept here for easy breakpoint testing
_asm nop;
						}
						// When we get here, we should be ready for the next attribute thing
					}
					// When we get here, we're done with attributes, we should be on to the next sibling tag
				}

			} else {
				// Syntax error
				return((SBxml*)-1);
			}
		}
		// When we get here, we need to have the root node closed to be successful
		if (lnLevel != 0)
			return((SBxml*)-1);

		// If we parsed anything, verify that which we parsed is, in fact, up to specs. :-)
		if (bxml)
		{
			// If we're not closed
			if (!bxml->closed)
				return((SBxml*)-1);		// Syntax error

			// If we're not back at our root
			if (bxml->level != lnLevel)
				return((SBxml*)-1);		// Syntax error
		}

		// Make sure we return the sibling back up to the top-most level
		while (bxml->ll4.prev)
			bxml = (SBxml*)bxml->ll4.prev;

		// If we get here, we're good
		return(bxml);
	}




//////////
//
// Searches forward from where we are for the next non-alphanumeric character
//
//////
	u64 iibxml_scanForwardToNonAlphanumeric(s8* buffer, u64 tnMaxLength)
	{
		u32 lnI;


		// Scan forward until we find one
		for (lnI = 0; lnI < tnMaxLength; lnI++)
		{
			// See if that character is an alphanumeric
			if (lnI == 0)
			{
				// First character must not be numeric
				if (!ioss_isAlpha(buffer[lnI]))
					break;		// It is not an alphanumeric kid

			} else {
				// Every character thereafter can be alpha, numeric, or underscore
				if (!ioss_isAlphanumeric(buffer[lnI]))
					break;		// It is not an alphanumeric kid
			}
		}
		// When we get here, we're reached the end
		return(lnI);
	}




//////////
//
// Searches forward from where we are for the next non-numeric character
//
//////
	u64 iibxml_scanForwardToNonNumeric(s8* buffer, u64 tnMaxLength)
	{
		u32 lnI;


		// Scan forward until we find one
		for (lnI = 0; lnI < tnMaxLength; lnI++)
		{
			// See if that character is a numeric
			if (!ioss_isNumeric(buffer[lnI]))
				break;		// It is not an alphanumeric kid
		}
		// When we get here, we're reached the end
		return(lnI);
	}




//////////
//
// Skip forward until we find the indicated character
//
//////
	u64 iibxml_scanForwardToCharacter(s8* buffer, u64 tnMaxLength, s8 tcChar)
	{
		u32 lnI;


// TODO:  (possible bug, future enhancement) if the tcChar is a quote character, we might want to recognize that we're also looking for escaped quotes within quoted material
		// Make sure our environment is sane
		lnI = 0;
		if (buffer && tnMaxLength > 0)
		{
			while (buffer[lnI] != tcChar && lnI < tnMaxLength)
				++lnI;
		}
		// Indicate how many we skipped
		return(lnI);
	}




//////////
//
// Create a new SBxml record with 4-way links
//
//////
	SBxml* iibxml_createNewSBxml(u32 tnLevel, SBxml* bxmlRelation, bool tlIsChild, SBxml* next, SBxml* prev, SBxml* parent, SBxml* child)
	{
		SBxml* bxmlNew;


		// Allocate our new entry
		bxmlNew = (SBxml*)malloc(sizeof(SBxml));

		// If we have a valid bxml, proceed
		if (bxmlNew)
		{
			// Initialize the memory
			memset(bxmlNew, 0, sizeof(SBxml));

			// If this new entry is a child, update its relation (parent)
			if (bxmlRelation)
			{
				if (tlIsChild)		bxmlRelation->ll4.child = (SLL4*)bxmlNew;		// This is a child of the relation
				else				bxmlRelation->ll4.next	= (SLL4*)bxmlNew;		// This is a sibling of the relation
			}

			// Populate its header 
			bxmlNew->ll4.uniqueId	= oss_getNextUniqueId();

			// Store the level
			bxmlNew->level			= tnLevel;

			// Populate its links
			bxmlNew->ll4.next		= (SLL4*)next;
			bxmlNew->ll4.prev		= (SLL4*)prev;
			bxmlNew->ll4.parent		= (SLL4*)parent;
			bxmlNew->ll4.child		= (SLL4*)child;
		}
		// When we get here, we were either successful or not, but bxml knows the story
		return(bxmlNew);
	}




//////////
//
// Store error information based on what the user wants to know
//
//////
	void iibxml_storeErrorCode(u64* tnErrorOffsetStore, u64 tnErrorOffset, u64* tnErrorCodeStore, u64 tnErrorCode)
	{
		// Store the offset where the error occurred
		if (tnErrorOffsetStore)
			*tnErrorOffsetStore = tnErrorOffset;

		// Store the error code itself
		if (tnErrorCodeStore)
			*tnErrorCodeStore = tnErrorCode;

		// Store the local variables
		gnLastErrorOffset	= tnErrorOffset;
		gnLastErrorCode		= tnErrorCode;
	}




//////////
//
// Called to write the indicated BXML node to the buffer, and possibly its children as well
//
//////
	void ibxml_saveNode(SBuffer* build, SBxml* bxml, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnError)
	{
		u32					lnI;
		SStartEndCallback	cb;


// TODO:  this code works and has been tested, though not as thoroughly as it should be
		//////////
		// Make sure our environment is sane
		//////
			if (!bxml)
			{
				// There is a NULL pointer
				if (tnError)
					++*tnError;

				// Early termination due to failure
				return;
			}


			// Iterate through every sibling
			while (bxml)
			{

			//////////
			// If we are on a non-zero level, and there's anything we're doing with children or siblings, record the indentation
			//////
				if (tlSaveChildNodes || tlSaveSiblings)
				{
					// Two spaces per indention
					for (lnI = 0; lnI < bxml->level; lnI++)
						oss_buildBufferAppendText(build, (s8*)cgcSpaceBxmlIndent, sizeof(cgcSpaceBxmlIndent) - 1);
				}


			//////////
			// Append the tag format
			//////
				// <
				oss_buildBufferAppendText(build, (s8*)cgcTagLeader, sizeof(cgcTagLeader) - 1);

				// tag name
				oss_buildBufferAppendText(build, bxml->_name.data._s8, (u32)bxml->_name.length);

				// If there are attributes, process them
				if (bxml->_attributes.masterCount != 0)
				{
					// There are attributes
					// Iterate through each attribute, appending them as we go
					cb._func	= (u64)&iibxml_saveNodeCallback;
					cb.extra	= (u64)(void*)build;
					oss_iterateThroughStartEndForCallback(&bxml->_attributes, &cb);
				}

				// Add the closer for this tag
				if (bxml->ll4.child && tlSaveChildNodes)
				{
					// There are children, so this tag is not closed
					oss_buildBufferAppendText(build, (s8*)cgcTagCloser, sizeof(cgcTagCloser) - 1);

					// Append CR/LF
					oss_buildBufferAppendText(build, (s8*)cgcCrLf, sizeof(cgcCrLf) - 1);

					// Append the children
					ibxml_saveNode(build, (SBxml*)bxml->ll4.child, tlSaveChildNodes, tlSaveSiblings, tnError);
					if (tnError && *tnError)
						return;		// Failure during the child save

					// Close the tag
					// Two spaces per indention
					for (lnI = 0; lnI < bxml->level; lnI++)
						oss_buildBufferAppendText(build, (s8*)cgcSpaceBxmlIndent, sizeof(cgcSpaceBxmlIndent) - 1);

					// </
					oss_buildBufferAppendText(build, (s8*)cgcTagClosingLeader, sizeof(cgcTagClosingLeader) - 1);

					// tag name
					oss_buildBufferAppendText(build, bxml->_name.data._s8, (u32)bxml->_name.length);

					// closing tag
					oss_buildBufferAppendText(build, (s8*)cgcTagCloser, sizeof(cgcTagCloser) - 1);

				} else {
					// We are completed, there are no children, or they do not want to see children, so we add the singleCloser
					oss_buildBufferAppendText(build, (s8*)cgcTagSingleCloser, sizeof(cgcTagSingleCloser) - 1);
				}


			//////////
			// Append CR/LF
			//////
				oss_buildBufferAppendText(build, (s8*)cgcCrLf, sizeof(cgcCrLf) - 1);


			//////////
			// Move to next sibling (if any)
			//////
				if (!tlSaveSiblings)
					break;		// All done

				// Keep going with siblings
				bxml = (SBxml*)bxml->ll4.next;
			}
	}

	// One callback for every attribute
	void iibxml_saveNodeCallback(SStartEndCallback* cb)
	{
		SBxmla*		bxmla;
		SBuffer*	build;
		bool		llStoreAttributeData;
		s8			buffer[32];


// TODO:  this code works and has been tested, though not as thoroughly as it should be
		// Make sure our environment is sane
		if (cb && cb->ptr && cb->extra != 0)
		{
		//////////
		// Restore our pointers
		//////
			bxmla	= (SBxmla*)cb->ptr;
			build	= (SBuffer*)cb->extra;


		//////////
		// Append our attribute
		//////
			// Append space before each attribute
			oss_buildBufferAppendText(build, (s8*)cgcSpace1, sizeof(cgcSpace1) - 1);

			// Attribute name
			oss_buildBufferAppendText(build, bxmla->_name.data._s8, (u32)bxmla->_name.length);
			if (bxmla->_data.datum.data._s8)
			{
				// There is actually data allocated for the tag
				llStoreAttributeData = true;
				if (bxmla->_data.lengthTotal <= bxmla->_data.datum.length)
				{
					// Both the attribute length and the total length are the same, so we can store it as one attr:##=
					// However, if the data allocated is all NULLs, then we don't need to store it
					if (bxmla->_data.datum.length >= 1 && bxmla->_data.datum.data._s8[0] == 0 && oss_scanForwardUntilCharacterChanges(bxmla->_data.datum.data, bxmla->_data.datum.length) == bxmla->_data.datum.length)
					{
						// It's all NULL, we need to write, so we write "attr::##"
						sprintf_s(buffer, sizeof(buffer), "%u\0", bxmla->_data.lengthTotal);
						oss_buildBufferAppendText(build, (s8*)cgcColonColon, sizeof(cgcColonColon) - 1);
						oss_buildBufferAppendText(build, buffer, strlen(buffer));
						llStoreAttributeData = false;

					} else {
						// There is data we need to write, so we write "attr:##="
						sprintf_s(buffer, sizeof(buffer), "%u\0", bxmla->_data.lengthTotal);
						oss_buildBufferAppendText(build, (s8*)cgcColon, sizeof(cgcColon) - 1);
						oss_buildBufferAppendText(build, buffer, strlen(buffer));
					}

				} else {
					// The attribute length and the total space assigned to it are not the same, so we must store as attr:#1:#2=
					// Append total length indicated
					sprintf_s(buffer, sizeof(buffer), "%u\0", bxmla->_data.lengthTotal);
					oss_buildBufferAppendText(build, (s8*)cgcColon, sizeof(cgcColon) - 1);
					oss_buildBufferAppendText(build, buffer, strlen(buffer));
					// Append data length
					sprintf_s(buffer, sizeof(buffer), "%u\0", bxmla->_data.datum.length);
					oss_buildBufferAppendText(build, (s8*)cgcColon, sizeof(cgcColon) - 1);
					oss_buildBufferAppendText(build, buffer, strlen(buffer));
				}

				// If we need to store the literal data, do so
				if (llStoreAttributeData)
				{
					// Store the attribute data (equal sign and content)
					oss_buildBufferAppendText(build, (s8*)cgcEqual, sizeof(cgcEqual) - 1);
					oss_buildBufferAppendText(build, bxmla->_data.datum.data._s8, (u32)bxmla->_data.datum.length);
				}


			} else {
				// There is no data allocated, so it's a storage mechanism that has no data associated with it
				// These are stored as attr::##
				sprintf_s(buffer, sizeof(buffer), "%u\0", max(bxmla->_data.lengthTotal, bxmla->_data.lengthTotal));
				oss_buildBufferAppendText(build, (s8*)cgcColonColon, sizeof(cgcColonColon) - 1);
				oss_buildBufferAppendText(build, buffer, strlen(buffer));
			}
		}
	}





//////////
//
// Callback to examine the pointer and delete the indicated member elements.
// Also guarantees that the indicated Bxmla is actually a member of bxml
//
//////
	bool iibxml_AttributeDeleteCallback(SStartEndCallback* cb)
	{
		_isSBxmlAttributeDeleteParams*	lbadp;
		SBxml*							bxml;
		SBxmla*							bxmla;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		if (cb && cb->ptr && cb->extra != 0)
		{
			// Get our pointers back
			bxmla		= (SBxmla*)cb->ptr;
			lbadp		= (_isSBxmlAttributeDeleteParams*)cb->extra;

			// See if this is our man
			if (bxmla == lbadp->bxmla)
			{
				// This is the one we want to delete
_asm nop;
				// Update its pointers (if any)
				bxml = bxmla->_parent;
				if (bxmla->ll.prev && bxmla->ll.next)
				{
					// Removing one in the middle
					((SBxmla*)bxmla->ll.prev)->ll.next = bxmla->ll.next;		// The one before this points to the one after this
					((SBxmla*)bxmla->ll.next)->ll.prev = bxmla->ll.prev;		// The one after this points to the one before this

				} else if (bxmla->ll.prev) {
					// Removing the last entry
					((SBxmla*)bxmla->ll.prev)->ll.next = NULL;					// The one before this points to nothing

				} else if (bxmla->ll.next) {
					// Removing the first entry
					((SBxmla*)bxmla->ll.prev)->ll.next = NULL;					// The one before this points to nothing

				} else {
					// Removing the only entry
				}

				// Delete the name
				oss_datumDelete(&bxmla->_name);

				// Delete the data
				oss_datum2Delete(&bxmla->_data);

				// Now that we've deleted the subordinate structure components, we are free to release the structure itself, both happily, and obediently. :-)
				// Indicate we found our man
				return(true);
			}
		}
		// Keep going by indicating we have not yet found our man
		return(false);
	}




//////////
//
// Callback to find the location of the item they want to add the entry relative to
//
//////
	bool iibxml_attributeInsertCallback(SStartEndCallback* cb)
	{
		SBxmla*		bxmla;
		SBxmla*		bxmlaRef;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		if (cb && cb->ptr)
		{
			// Restore our pointers
			bxmla		= (SBxmla*)cb->ptr;
			bxmlaRef	= (SBxmla*)cb->extra;

			// See if this is our target
			if (bxmla == bxmlaRef)
			{
				// It is, we found a match
				return(true);		// Indicate this is success
			}
		}
		// When we get here, this wasn't it, indicate we didn't find it so we need more
		return(false);
	}




//////////
//
// Called to copy the indicated attribute to a new, orphan record
//
//////
	SBxmla* ibxml_attributeDuplicate(SBxmla* bxmlaOriginal)
	{
// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		if (bxmlaOriginal && bxmlaOriginal->_name.data._s8 && bxmlaOriginal->_name.length != 0)
		{
			// We're good, attempt the replication
			return(ibxml_attributeDuplicateAs(bxmlaOriginal, bxmlaOriginal->_name.data._s8, (u32)bxmlaOriginal->_name.length));

		} else {
			// Failure, environment is completely insane (why do they do this to us??? :-))
			return(NULL);	// Invalid name, cannot be replicated (at least not in this universe)
		}
	}




//////////
//
// Called to copy the indicated attribute to a new, orphan record
//
//////
	SBxmla* ibxml_attributeDuplicateAs(SBxmla* bxmlaOriginal, s8* tcNewName, u32 tnNewNameLength)
	{
		SBxmla*	bxmlaNew;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		bxmlaNew = NULL;
		if (bxmlaOriginal)
		{
			// Create a new orphan Bxmla entry
			bxmlaNew = ibxml_attributeCreateAs(tcNewName, tnNewNameLength);

			// If we're valid, duplicate the source entry's data component
			if (bxmlaNew)
				oss_datum2Duplicate(&bxmlaNew->_data, &bxmlaOriginal->_data);
		}
		// Indicate our status
		return(bxmlaNew);
	}




//////////
//
// Creates a new orphan attribute from scratch giving it a name only
//
//////
	SBxmla* ibxml_attributeCreateAs(s8* tcNewName, u32 tnNewNameLength)
	{
		SBxmla*	bxmlaNew;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		bxmlaNew = NULL;
		if (tcNewName && tnNewNameLength != 0)
		{
			// Allocate our new entry
			bxmlaNew = (SBxmla*)oss_alloc(sizeof(SBxmla), true);

			// If we're valid, duplicate the essential components
			if (bxmlaNew)
			{
				// Initialize the structure to empty
				memset(bxmlaNew, 0, sizeof(SBxmla));

				// Populate its key components
				bxmlaNew->ll.uniqueId = oss_getNextUniqueId();

				// Duplicate the source entry's components
				oss_datumSet(&bxmlaNew->_name, (u8*)tcNewName, tnNewNameLength, false);
			}
		}
		// Indicate our status
		return(bxmlaNew);
	}




//////////
//
// Creates a new orphan attribute from scratch, giving it both name and data
//
//////
	SBxmla* ibxml_attributeCreateAsWithData(s8* tcNewName, u32 tnNewNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength)
	{
		SBxmla*	bxmlaNew;


		// Make sure our environment is sane
		bxmlaNew = ibxml_attributeCreateAs(tcNewName, tnNewNameLength);
		if (bxmlaNew)
		{
			// Append the data
			oss_datum2Set(&bxmlaNew->_data, (u8*)tcData, tnDataLength, tnTotalDataLength, false);

		}
		// Indicate our status
		return(bxmlaNew);
	}




//////////
//
// Creates an orphan node with the given name
//
//////
	SBxml* ibxml_nodeCreateAs(s8* tcNewName, u32 tnNewNameLength)
	{
		SBxml*	bxmlNew;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		bxmlNew = NULL;
		if (tcNewName && tnNewNameLength != 0)
		{
			// Allocate our new entry
			bxmlNew = (SBxml*)oss_alloc(sizeof(SBxml), true);

			// If we're valid, duplicate the essential components
			if (bxmlNew)
			{
				// Initialize the structure to empty
				memset(bxmlNew, 0, sizeof(SBxmla));

				// Populate its key components
				bxmlNew->ll4.uniqueId = oss_getNextUniqueId();

				// Duplicate the source entry's components
				oss_datumSet(&bxmlNew->_name, (u8*)tcNewName, tnNewNameLength, false);
			}
		}
		// Indicate our status
		return(bxmlNew);
	}




//////////
//
// Creates a copy of the node, including optionally its attributes and children
//
//////
	SBxml* ibxml_nodeCopyAs(SBxml* bxmlSrc, s8* tcNewName, u64 tnNewNameLength, bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult)
	{
		SBxml*	bxmlNew;
		bool	llResult;


// TODO:  tested, but not thoroughly tested
		// Make sure the environment is sane
		llResult	= false;			// Initially assume failure
		bxmlNew		= NULL;
		if (bxmlSrc && tcNewName && tnNewNameLength != 0)
		{
			// Create the new entry
			bxmlNew = iibxml_createNewSBxml(0, NULL, false, NULL, NULL, NULL, NULL);

			// Once inside, assume success, failures will be signaled
			llResult = true;

			// If we succeeded, populate the necessary information
			if (bxmlNew)
			{
				// Duplicate the name
				oss_datumSet(&bxmlNew->_name, (u8*)tcNewName, tnNewNameLength, false);

				// If we are to copy attributes, do so
				if (tlCopyAttributes && bxmlSrc->_attributes.masterCount != 0)
					iibxml_nodeCopyAttributes(bxmlNew, bxmlSrc, &llResult);

				// If we are to copy children, do so
				if (llResult && tlCopyChildren)
					iibxml_nodeCopyChildren(bxmlNew, bxmlSrc, tlCopyAttributes, &llResult);
			}
		}

		// Indicate our status
		if (tlResult)
			*tlResult = llResult;

		// Return our pointer
		return(bxmlNew);
	}




//////////
//
// Copies all attributes from the source to the destination
//
//////
	void iibxml_nodeCopyAttributes(SBxml* bxmlDst, SBxml* bxmlSrc, bool* tlResult)
	{
		_isSBxmlCopyAttrParams	params;
		SStartEndCallback		cb;



// TODO:  tested and functioning correctly, but not tested thoroughly
		// Make sure our environment is sane
		if (bxmlDst && bxmlSrc && bxmlSrc->_attributes.masterCount != 0)
		{
			// Copy attributes
			params.bxmlDst	= bxmlDst;
			params.tlResult	= tlResult;

			// Iterate through each attribute copying them out
			cb._func	= (u64)&iibxml_nodeCopyAttributesCallback;
			cb.extra	= (u64)(void*)&params;
			oss_iterateThroughStartEndForCallback(&bxmlSrc->_attributes, &cb);

			// Update the result if we failed
			if (tlResult && !*params.tlResult)
				*tlResult = *params.tlResult;		// Failure
		}
	}

	void iibxml_nodeCopyAttributesCallback(SStartEndCallback* cb)
	{
		SBxmla*					bxmla;
		SBxmla*					bxmlaNew;
		bool					llResult;
		_isSBxmlCopyAttrParams*	params;


// TODO:  tested and functioning correctly, but not tested thoroughly
		// Make sure our environment is sane
		if (cb && cb->ptr && cb->extra != 0)
		{
			// Restore our pointers
			bxmla		= (SBxmla*)cb->ptr;
			params		= (_isSBxmlCopyAttrParams*)cb->extra;

			// Duplicate this attribute
			bxmlaNew	= ibxml_attributeDuplicate(bxmla);

			// Append this attribute to the destination
			if (bxmlaNew)		ioss_SEChain_appendOrPrependExisting(&params->bxmlDst->_attributes, (SLL*)bxmlaNew, _COMMON_START_END_SMALL_BLOCK_SIZE, false, &llResult);
			else				llResult = false;

			// Update our status if we fail
			if (!llResult && params->tlResult)
				*(params->tlResult) = llResult;
		}
	}




//////////
//
// Copies all children from the source to the destination
//
//////
	void iibxml_nodeCopyChildren(SBxml* bxmlDst, SBxml* bxmlSrc, bool tlCopyAttributes, bool* tlResult)
	{
		SBxml*	bxmlSrcChild;
		SBxml*	bxmlNewPrev;
		SBxml*	bxmlNew;
		bool	llResult;


// TODO:  tested and functioning correctly, but not thoroughly enough
		// Make sure our environment is sane
		if (bxmlDst && bxmlSrc)
		{
			// Copy children?
			if (bxmlSrc->ll4.child)
			{
				// Copy children
				// Repeat for every sibling at this child level
				bxmlSrcChild	= (SBxml*)bxmlSrc->ll4.child;
				bxmlNewPrev		= NULL;
				while (bxmlSrcChild)
				{
					//////////
					// Create a duplicate of this entry
					//////
						if (bxmlNewPrev == NULL)
						{
							// First entry is a child to bxmlDst
							bxmlNew = iibxml_createNewSBxml(bxmlDst->level + 1,		bxmlDst,		true,	NULL, NULL,			bxmlDst,							NULL);

						} else {
							// Entries after that are siblings to bmxlChildPrev
							bxmlNew = iibxml_createNewSBxml(bxmlNewPrev->level,		bxmlNewPrev,	false,	NULL, bxmlNewPrev,	(SBxml*)bxmlNewPrev->ll4.parent,	NULL);
						}


					//////////
					// Was everything okay?
					//////
						if (!bxmlNew)
						{
							// If they want to know the status, indicate that we have now failed
							if (tlResult)
								*tlResult = false;

							// Record a proper error
							iibxml_recordLastError(IDS_BXML_UNABLE_TO_CREATE_BXML, 0, NULL, bxmlNew, NULL, 0);

							// Return (defeated, but still happy)
							return;		// An error was encountered
						}


					//////////
					// Append the duplicated tag name
					//////
						oss_datumDuplicate(&bxmlNew->_name, &bxmlSrcChild->_name);


					//////////
					// We force it closed because the closed condition is really only used as a test during load, not later
					//////
						bxmlNew->closed = true;


					//////////
					// Copy the attributes if we should copy them
					//////
						if (tlCopyAttributes)		iibxml_nodeCopyAttributes(bxmlNew, bxmlSrcChild, &llResult);
						else						llResult = false;


					//////////
					// If there are children at this level, we also copy those
					//////
						if (llResult)
						{
							iibxml_nodeCopyChildren(bxmlNew, (SBxml*)bxmlSrcChild, tlCopyAttributes, &llResult);
							if (!llResult)
								return;		// A failure somewhere below on the childer levels
						}


					//////////
					// Move to the child's next sibling
					//////
						bxmlNewPrev		= bxmlNew;
						bxmlSrcChild	= (SBxml*)bxmlSrcChild->ll4.next;

				}
				// When we get here, we have a success
			}
			//else there are no children, so ... we're defacto finished with our task! :-)
		}
	}




//////////
//
// Record an error in BXML processing
//
//////
	void iibxml_recordLastError(u32 tnResourceNumber, u32 tnErrorNumber, s8* tcDescriptionZ, SBxml* bxml, SBxmla* bxmla, u64 tnErrorOffset)
	{
		// See if they've given us an easy task
		if (tnResourceNumber != 0)
		{
			// They indicated a resource number, so we use that for the error number and description
			tnErrorNumber	= tnResourceNumber;
			tcDescriptionZ	= vvm_loadResourceAsciiText(tnResourceNumber);

		}
		//else, they specified an explicit error number and custom description... this should only be used for debugging, not for runtime, because we want everything to go through localization

		// Update the last pointers and error number
		gsLastErrorInfo.bxmlInError		= bxml;
		gsLastErrorInfo.bxmlaInError	= bxmla;
		gsLastErrorInfo.lastErrorCode	= tnErrorNumber;

		// Update the last error structure
		oss_datumSet(&gsLastErrorInfo.description, (u8*)tcDescriptionZ, oss_strlen(_csu8p(tcDescriptionZ)), true);
		// When we get here, the last error has been updated
	}




//////////
//
// Called to delete everything on a given SBxml, releasing all memory as we go
//
//////
	bool ibxml_nodeDeleteBranch(SBxml* bxml)
	{
		u32		lnOriginalCount, lnDeletedCount;
		bool	llResult;


		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// Initially indicate success
			llResult = true;

			// Delete any children
			if (bxml->ll4.child)
				ibxml_nodeDeleteBranch((SBxml*)bxml->ll4.child);

			// Delete all the attributes
			if (bxml->_attributes.masterCount != 0)
			{
				// Get the count of items that should be deleted
				lnOriginalCount	= oss_SEChain_countValids(&bxml->_attributes);
				lnDeletedCount	= oss_SEChain_delete(&bxml->_attributes, (u64)&iibxml_nodeDeleteBranchAttributeCallback, (u64)(void*)bxml, true);

				// Our success indicates whether or not they were completely deleted
				llResult = (lnOriginalCount == lnDeletedCount);
			}

			// Delete itself
			free(bxml);
		}

		// Indicate our status
		return(llResult);
	}

	// Callback to delete the components of every Start/end entry
	void iibxml_nodeDeleteBranchAttributeCallback(SStartEndCallback* cb)
	{
		SBxml*	bxml;
		SBxmla*	bxmla;


		// Make sure our environment is sane
		if (cb && cb->ptr && cb->extra != 0)
		{
			// Restore our pointers
			bxmla	= (SBxmla*)cb->ptr;
			bxml	= (SBxml*)cb->extra;

			// Delete this attribute's datum and datum2 items
			oss_datumDelete(&bxmla->_name);
			oss_datum2Delete(&bxmla->_data);
		}
	}




//////////
//
// Called to compute the SHA-1 of the one attribute, or all attributes, or just tags, or just data.
//
//////
	u64 ioss_bxmlAttributeSha1One(SBxmla* bxmla, u8 sha20Bytes[20])
	{
		u8	context[92];
		u8	buffer[64];


		// Make sure our environment's sane
		if (bxmla)
		{
			// We can compute it
			oss_sha1ComputeSha1_Start(context);
			iioss_bxmlComputeSha1OnAttribute(bxmla, context, buffer, true, true);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			return(oss_sha1Compute64BitFromSha1(sha20Bytes));
		}
		// If we get here, failure
		memset(sha20Bytes, 0, sizeof(sha20Bytes));
		return(-1);
	}

	u64 ioss_bxmlAttributeSha1(SBxml* bxml, u8 sha20Bytes[20])
	{
		u8	context[92];
		u8	buffer[64];


		// Make sure our environment's sane
		if (bxml)
		{
			// We can compute it
			oss_sha1ComputeSha1_Start(context);
			iioss_bxmlComputeSha1OnNode(bxml, context, buffer, 0, true, false, false);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			return(oss_sha1Compute64BitFromSha1(sha20Bytes));
		}
		// If we get here, failure
		memset(sha20Bytes, 0, sizeof(sha20Bytes));
		return(-1);
	}

	u64 ioss_bxmlAttributeSha1Tag(SBxml* bxml, u8 sha20Bytes[20])
	{
		SBxmla*	bxmla;
		u8		context[92];
		u8		buffer[64];


		// Make sure our environment's sane
		if (bxml)
		{
			// We can compute it
			oss_sha1ComputeSha1_Start(context);
			
			// Repeat for every attribute, just doing the names
			bxmla = oss_bxmlNodeGetFirstAttribute(bxml);
			while (bxmla)
			{
				// Process this attribute
				iioss_bxmlComputeSha1OnAttribute(bxmla, context, buffer, true, false);

				// Move to next attribute
				bxmla = oss_bxmlaGetNext(bxmla);
			}

			// All done
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			return(oss_sha1Compute64BitFromSha1(sha20Bytes));
		}
		// If we get here, failure
		memset(sha20Bytes, 0, sizeof(sha20Bytes));
		return(-1);
	}

	u64 ioss_bxmlAttributeSha1Data(SBxml* bxml, u8 sha20Bytes[20])
	{
		SBxmla*	bxmla;
		u8		context[92];
		u8		buffer[64];


		// Make sure our environment's sane
		if (bxml)
		{
			// We can compute it
			oss_sha1ComputeSha1_Start(context);

			// Repeat for every attribute, just doing the names
			bxmla = oss_bxmlNodeGetFirstAttribute(bxml);
			while (bxmla)
			{
				// Process this attribute
				iioss_bxmlComputeSha1OnAttribute(bxmla, context, buffer, false, true);

				// Move to next attribute
				bxmla = oss_bxmlaGetNext(bxmla);
			}

			// All done
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			return(oss_sha1Compute64BitFromSha1(sha20Bytes));
		}
		// If we get here, failure
		memset(sha20Bytes, 0, sizeof(sha20Bytes));
		return(-1);
	}




//////////
//
// Called to compute the SHA-1 of the node, and its data branches, as a single number
//
//////
	// Computes the SHA-1 on the entire node, including its data, all children, all siblings (at or below the child level)
	u64 ioss_bxmlNodeSha1(SBxml* bxml, u8 sha20Bytes[20])
	{
		u8	context[92];
		u8	buffer[64];


		// Make sure our environment's sane
		if (bxml)
		{
			// We can compute it
			oss_sha1ComputeSha1_Start(context);
			iioss_bxmlComputeSha1OnNode(bxml, context, buffer, 0, true, true, true);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			return(oss_sha1Compute64BitFromSha1(sha20Bytes));
		}
		// If we get here, failure
		memset(sha20Bytes, 0, sizeof(sha20Bytes));
		return(-1);
	}

	// Computes the SHA-1 on the entire node tree of tag names only, including all children, all siblings (at or below the child level)
	u64 ioss_bxmlNodeSha1Tag(SBxml* bxml, u8 sha20Bytes[20])
	{
		u8	context[92];
		u8	buffer[64];


		// Make sure our environment's sane
		if (bxml)
		{
			// We can compute it
			oss_sha1ComputeSha1_Start(context);
			iioss_bxmlComputeSha1OnNode(bxml, context, buffer, 0, false, true, true);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			return(oss_sha1Compute64BitFromSha1(sha20Bytes));
		}
		// If we get here, failure
		memset(sha20Bytes, 0, sizeof(sha20Bytes));
		return(-1);
	}

	// Computes the SHA-1 on the node's data, including only its attributes (names and data)
	u64 ioss_bxmlNodeSha1Data(SBxml* bxml, u8 sha20Bytes[20])
	{
		u8	context[92];
		u8	buffer[64];


		// Make sure our environment's sane
		if (bxml)
		{
			// We can compute it
			oss_sha1ComputeSha1_Start(context);
			iioss_bxmlComputeSha1OnNode(bxml, context, buffer, 0, true, false, false);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			return(oss_sha1Compute64BitFromSha1(sha20Bytes));
		}
		// If we get here, failure
		memset(sha20Bytes, 0, sizeof(sha20Bytes));
		return(-1);
	}

	// Computes the SHA-1 on this node, and possibly its attributes, children and siblings
	void iioss_bxmlComputeSha1OnNode(SBxml* bxml, u8 handle[92], u8 buffer[64], u32 tnLevel, bool tlAttributes, bool tlChildren, bool tlSiblings)
	{
		_isSBxmlComputeSha1NodeParams	cbParams;
		SStartEndCallback				cb;



		// Make sure our environment is sane
		if (bxml)
		{
			// Populate our callback params
			cbParams.handle92Bytes	= handle;
			cbParams.buffer64Bytes	= buffer;

			// Compute the SHA-1 on the tag name of this node
			oss_sha1ComputeSha1_ProcessThisData(handle, (s8*)bxml->_name.data._s8, (u32)bxml->_name.length);

			// If we are to process attributes, process them next
			if (tlAttributes && bxml->_attributes.masterCount != 0)
			{
				cb._func	= (u64)&iioss_bxmlComputeSha1OnNodeAttributeCallback;
				cb.extra	= (u64)(void*)&cbParams;
				oss_iterateThroughStartEndForCallback(&bxml->_attributes, &cb);
			}

			// If we are to process children, process them next
			if (tlChildren)
				iioss_bxmlComputeSha1OnNode(oss_bxmlNodeGetFirstChild(bxml), handle, buffer, tnLevel + 1, tlAttributes, tlChildren, tlSiblings);

			// If we are to process siblings, process them next
			if (tnLevel != 0 && tlSiblings)
			{
				bxml = oss_bxmlNodeGetNext(bxml);
				while (bxml)
				{
					// Compute on this sibling node
					iioss_bxmlComputeSha1OnNode(bxml, handle, buffer, tnLevel + 1, tlAttributes, tlChildren, tlSiblings);

					// Move to next sibling
					bxml = oss_bxmlNodeGetNext(bxml);
				}
			}
		}
	}

	void iioss_bxmlComputeSha1OnNodeAttributeCallback(SStartEndCallback* cb)
	{
		_isSBxmlComputeSha1NodeParams*	cbParams;


		if (cb && cb->ptr && cb->extra != 0)
		{
			// Get our parameters back
			cbParams = (_isSBxmlComputeSha1NodeParams*)cb->extra;

			// Process this attribute
			iioss_bxmlComputeSha1OnAttribute((SBxmla*)cb->ptr, cbParams->handle92Bytes, cbParams->buffer64Bytes, true, true);
		}
	}

	// Computes the SHA-1 on this attribute, including its tag name and data
	void iioss_bxmlComputeSha1OnAttribute(SBxmla* bxmla, u8 handle[92], u8 buffer[64], bool tlName, bool tlData)
	{
		//////////
		// Attribute name
		//////
			if (tlName)
				oss_sha1ComputeSha1_ProcessThisData(handle, (s8*)bxmla->_name.data._s8, (u32)bxmla->_name.length);


			if (tlData)
			{
				//////////
				// Attribute data lengths
				//////
					// Get a 32-byte form of the lengthTotal and the populated length values
					sprintf_s((s8*)buffer, 64, "%016llx%016llx\0", bxmla->_data.lengthTotal, bxmla->_data.datum.length);
					oss_sha1ComputeSha1_ProcessThisData(handle, (s8*)buffer, 32);


				//////////
				// Attribute raw data
				//////
					if (bxmla->_data.datum.length != 0)
						oss_sha1ComputeSha1_ProcessThisData(handle, bxmla->_data.datum.data._s8, (u32)bxmla->_data.datum.length);
			}

		// This attribute is completed
	}