//////////
//
// /libsf/source/vjr/engine.h
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
// Constants for .T. and .F. settings using LOGICALX()
//
//////
	const u32	_TRUEFALSE_TF					= 1;
	const u32	_TRUEFALSE_YN					= 2;
	const u32	_TRUEFALSE_UD					= 3;


//////////
// SET settings. :-)
// http://www.visual-freepro.org/wiki/index.php/VFrP_changes#SET_Options
//////
	bool		_set_indexMetaData				= false;
	bool		_set_honorBarriers				= true;
	bool		_set_variablesFirst				= false;
	bool		_set_autoConvert				= false;
	bool		_set_caseSensitiveNames			= false;
	bool		_set_caseSensitiveCompares		= true;
	bool		_set_namingConventions			= false;
	bool		_set_trueFalse					= _TRUEFALSE_TF;
	bool		_set_implicitParams				= false;
	bool		_set_stickyParameters			= true;
	bool		_set_tableEqualAssignments		= false;
	bool		_set_tableObjects				= false;
	bool		_set_sloppyPrinting				= false;
	SDatum		_set_languageTo					= { "en", 2 };
