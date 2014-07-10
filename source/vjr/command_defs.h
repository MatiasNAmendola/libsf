//////////
//
// /libsf/source/vjr/command_defs.h
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




struct SVariable;


//////////
// commands.cpp
// Note:  This source file contains both commands and functions.  Each will be
//        given by its name, such as "function_chr()" being a function.
//////
	// Temporary error reporting until the proper engine is constructed.
	void				iError_report								(cs8* constantErrorText);
	void				iError_report								(s8* errorText);
	void				iError_reportByNumber						(u32 tnErrorNum);


//////////
// Functions
//////
	SVariable*			function_asc								(SVariable* p1);
	SVariable*			function_chr								(SVariable* p1);


//////////
// Translation
//////
	struct SFunctionList
	{
		s32		iCode;
		union {
			u32			_func;
			SVariable*	(*func_1p)		(SVariable* p1);
			SVariable*	(*func_2p)		(SVariable* p1, SVariable* p2);
			SVariable*	(*func_3p)		(SVariable* p1, SVariable* p2, SVariable* p3);
			SVariable*	(*func_4p)		(SVariable* p1, SVariable* p2, SVariable* p3, SVariable* p4);
			SVariable*	(*func_5p)		(SVariable* p1, SVariable* p2, SVariable* p3, SVariable* p4, SVariable* p5);
		};
		s32		parameters;
	};

	SFunctionList gsKnownFunctions[] = {
		{	_ICODE_ASC,			(u32)&function_asc,		1	},
		{	_ICODE_CHR,			(u32)&function_chr,		1	},

		// Do not delete this line, it is used to terminate the searching list
		{	0,					NULL,					0	}
	};
