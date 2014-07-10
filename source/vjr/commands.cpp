//////////
//
// /libsf/source/vjr/commands.cpp
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
// Reports an error.
//
//////
	void iError_report(cs8* constantErrorText)
	{
		iError_report((s8*)constantErrorText);
	}

	void iError_report(s8* errorText)
	{
		// Append the error to the ECM
		iEditChainManager_appendLine(screenData, errorText, -1);
	}




//////////
//
// Reports an error by number.
//
//////
	void iError_reportByNumber(u32 tnErrorNum)
	{
		switch (tnErrorNum)
		{
			case _ERROR_OUT_OF_MEMORY:
				iError_report((s8*)cgcOutOfMemory);
				break;

			case _ERROR_UNEXPECTED_COMMAND:
				iError_report((s8*)cgcUnexpectedCommand);
				break;

			case _ERROR_CONTEXT_HAS_CHANGED:
				iError_report((s8*)cgcContextHasChanged);
				break;

			case _ERROR_FULL_RECOMPILE_REQUIRED:
				iError_report((s8*)cgcFullRecompileRequired);
				break;

			case _ERROR_NOT_A_VARIABLE:
				iError_report((s8*)cgcNotAVariable);
				break;

			case _ERROR_NUMERIC_OVERFLOW:
				iError_report((s8*)cgcNumericOverflow);
				break;

			case _ERROR_NOT_NUMERIC:
				iError_report((s8*)cgcNotNumeric);
				break;

			case _ERROR_EMPTY_STRING:
				iError_report((s8*)cgcEmptyString);
				break;

			case _ERROR_SYNTAX:
				iError_report((s8*)cgcSyntaxError);
				break;

			case _ERROR_UNRECOGNIZED_PARAMETER:
				iError_report((s8*)cgcUnrecognizedParameter);
				break;
		}
	}




//////////
//
// Function: ASC()
// Takes a character input and converts it to its ASCII value.
//
//////
// Version 0.30
// Last update:
//     Jul.05.2014
//////
// Change log:
//     Jul.05.2014 - Initial creation
//////
// Parameters:
//     p1		-- Character, must be at least one character long
//
//////
// Returns:
//    Numeric	-- Input number converted to ASCII value number
//////
    SVariable* function_asc(SVariable* p1)
    {
        u8 			value;
        SVariable*	result;


		//////////
        // Parameter 1 must be character
		//////
			if (!iVariable_isValid(p1) || iVariable_getType(p1) != _VAR_TYPE_CHARACTER)
			{
				iError_report("Parameter 1 is not correct");
				return(NULL);
			}


		//////////
        // It must be at least one character long
		//////
			if (p1->value.length == 0)
				iError_reportByNumber(_ERROR_EMPTY_STRING);


		//////////
		// Extract the first character, and convert it to a number
		//////
			value = p1->value.udata[0];


		//////////
        // Create our return result
		//////
	        result = iVariable_create(_VAR_TYPE_INTEGER, NULL);
			if (!result)
			{
				iError_report("Internal error.");
				return(NULL);
			}


		//////////
        // Populate the result as an ASCII character
		//////
	        *(s32*)result->value.data = value;


		//////////
        // Return our converted result
		//////
	        return result;
    }




//////////
//
// Function: CHR()
// Takes a numeric input in the range 0..255, and converts it to its ASCII character.
//
//////
// Version 0.30
// Last update:
//     Jul.05.2014
//////
// Change log:
//     Jul.05.2014 - Initial creation
//////
// Parameters:
//     p1			-- Numeric, in the range 0..255
//
//////
// Returns:
//    Character		-- Input number converted to character
//////
    SVariable* function_chr(SVariable* p1)
    {
        s32			value;
		u32			errorNum;
        bool		error;
        SVariable*	result;
		s8			buffer[16];


		//////////
        // Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(p1) || iVariable_getType(p1) != _VAR_TYPE_NUMERIC)
			{
				iError_report("Parameter 1 is not correct");
				return(NULL);
			}


		//////////
        // It must be in the range 0..255
		//////
			value = iiVariable_getAs_s32(p1, false, &error, &errorNum);
			if (value > 255 || value < 0)
			{
				// We report our own error
				iError_report("Parameter must be in the range 0..255");
				return(NULL);

			} else if (error) {
				// The iVariable_getAs_s32() function reported an error.
				// This means the user is trying to obtain an integer value from a logical, or something similar.
				iError_reportByNumber(errorNum);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(_VAR_TYPE_CHARACTER, NULL);
			if (!result)
			{
				iError_report("Internal error.");
				return(NULL);
			}


		//////////
        // Populate the result as an ASCII character
		//////
	        buffer[0] = (u8)value;
			buffer[1] = 0;
			iDatum_duplicate(&result->value, buffer, 1);


		//////////
        // Return our converted result
		//////
	        return result;
    }
