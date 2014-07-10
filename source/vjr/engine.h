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
	const u32	_LOGICAL_TF						= 1;
	const u32	_LOGICAL_YN						= 2;
	const u32	_LOGICAL_UD						= 3;


//////////
// Constants for date formats
//////
	const u32	_SET_DATE_AMERICAN				= 1;			// mm/dd/yy
	const u32	_SET_DATE_ANSI					= 2;			// yy.mm.dd
	const u32	_SET_DATE_BRITISH				= 3;			// dd/mm/yy
	const u32	_SET_DATE_FRENCH				= 4;			// dd/mm/yy
	const u32	_SET_DATE_GERMAN				= 5;			// dd.mm.yy
	const u32	_SET_DATE_ITALIAN				= 6;			// dd-mm-yy
	const u32	_SET_DATE_JAPAN					= 7;			// yy/mm/dd
	const u32	_SET_DATE_TAIWAN				= 8;			// yy/mm/dd
	const u32	_SET_DATE_LONG					= 9;			// Dayofweek, Month dd, yyyy
	const u32	_SET_DATE_SHORT					= 10;			// m/d/yy
	const u32	_SET_DATE_USA					= 11;			// mm-dd-yy
	const u32	_SET_DATE_DMY					= 12;			// dd/mm/yy
	const u32	_SET_DATE_MDY					= 13;			// mm/dd/yy
	const u32	_SET_DATE_YMD					= 14;			// yy/mm/dd


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
	s32			_set_logical					= _LOGICAL_TF;
	bool		_set_implicitParams				= false;
	bool		_set_stickyParameters			= true;
	bool		_set_tableEqualAssignments		= false;
	bool		_set_tableObjects				= false;
	bool		_set_sloppyPrinting				= false;
	SDatum		_set_languageTo					= { "en", 2 };
	s32			_set_decimals					= 2;
	s32			_set_date						= _SET_DATE_AMERICAN;		// See _SET_DATE_* constants above
	bool		_set_century					= true;


//////////
// Forward declarations
//////
	bool					iEngine_executeStandaloneCommand		(SEditChain* line);
	SVariable*				iEngine_getVariableFromComponent		(SComp* comp, bool& tlManufactured);
	SVariable*				iEngine_getFunctionResult				(SComp* comp, bool& tlManufactured);
