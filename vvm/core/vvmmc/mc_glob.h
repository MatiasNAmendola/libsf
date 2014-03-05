//////////
//
// /libsf/VDebug/VDebug/mc_glob.h
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//	   Feb.25.2014
//////
// Change log:
//	   Feb.25.2014 - Development on 0.70 begins
//	   Nov.12.2012 - Initial creation
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
//	   http://www.libsf.org/
//	   http://www.libsf.org/licenses/
//	   http://www.visual-freepro.org
//	   http://www.visual-freepro.org/blog/
//	   http://www.visual-freepro.org/forum/
//	   http://www.visual-freepro.org/wiki/
//	   http://www.visual-freepro.org/wiki/index.php/PBL
//	   http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.	In Jesus' name I pray.	Amen.
//
//




//////////
// Global variables
//////
	HINSTANCE		ghInstance;
	HINSTANCE		ghResourceDll						= NULL;					// Handle to the loaded resource dll instance
	s8				cgcVvmmcEngDll[]					= "vvmmcenu.dll";		// Default resource file
	SStartEnd		gseRootResourceTexts				= { NULL, NULL };


	// Known operators to the system
	SAsciiCompSearcher	cgcKeywordOperators[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		validate handler,		custom handler
		{ "_azAZ__\000\000",		1,			true,		_MC_ICODE_ALPHA,						false,				NULL,					NULL },
		{ "_09\000\000",			1,			true,		_MC_ICODE_NUMERIC,						false,				NULL,					NULL },
		{ " ",						1,			true,		_MC_ICODE_WHITESPACE,					false,				NULL,					NULL },
		{ "\t",						1,			true,		_MC_ICODE_WHITESPACE,					false,				NULL,					NULL },
		{ "___",					1,			false,		_MC_ICODE_UNDERSCORE,					false,				NULL,					NULL },
		{ "(",						1,			false,		_MC_ICODE_LEFT_PARENTHESIS,				false,				NULL,					NULL },
		{ ")",						1,			false,		_MC_ICODE_RIGHT_PARENTHESIS,			false,				NULL,					NULL },
		{ "[",						1,			false,		_MC_ICODE_LEFT_BRACKET,					false,				NULL,					NULL },
		{ "]",						1,			false,		_MC_ICODE_RIGHT_BRACKET,				false,				NULL,					NULL },
		{ "{",						1,			false,		_MC_ICODE_LEFT_BRACE,					false,				NULL,					NULL },
		{ "}",						1,			false,		_MC_ICODE_RIGHT_BRACE,					false,				NULL,					NULL },
		{ "+",						1,			false,		_MC_ICODE_PLUS,							false,				NULL,					NULL },
		{ "-",						1,			false,		_MC_ICODE_MINU,							false,				NULL,					NULL },
		{ "*",						1,			true,		_MC_ICODE_ASTERISK,						false,				NULL,					NULL },
		{ "\\",						1,			true,		_MC_ICODE_SLASH,						false,				NULL,					NULL },
		{ "/",						1,			true,		_MC_ICODE_BACKSLASH,					false,				NULL,					NULL },
		{ "\"",						1,			false,		_MC_ICODE_DOUBLE_QUOTE,					false,				NULL,					NULL },
		{ "'",						1,			false,		_MC_ICODE_SINGLE_QUOTE,					false,				NULL,					NULL },
		{ ".",						1,			false,		_MC_ICODE_PERIOD,						false,				NULL,					NULL },
		{ ",",						1,			false,		_MC_ICODE_COMMA,						false,				NULL,					NULL },
		{ ":",						1,			false,		_MC_ICODE_COLON,						false,				NULL,					NULL },
		{ "_",						1,			false,		_MC_ICODE_UNDERSCORE,					false,				NULL,					NULL },
		{ "~",						1,			false,		_MC_ICODE_TILDE,						false,				NULL,					NULL },
		{ "@",						1,			false,		_MC_ICODE_AT_SIGN,						false,				NULL,					NULL },
		{ "?",						1,			false,		_MC_ICODE_QUESTION_MARK,				false,				NULL,					NULL },
		{ "!",						1,			false,		_MC_ICODE_EXCLAMATION_MARK,				false,				NULL,					NULL },
		{ "#",						1,			false,		_MC_ICODE_POUND_SIGN,					false,				NULL,					NULL },
		{ "$",						1,			false,		_MC_ICODE_DOLLAR_SIGN,					false,				NULL,					NULL },
		{ "%",						1,			false,		_MC_ICODE_PERCENT_SIGN,					false,				NULL,					NULL },
		{ "^",						1,			false,		_MC_ICODE_CARET,						false,				NULL,					NULL },
		{ "&",						1,			false,		_MC_ICODE_AMPERSAND,					false,				NULL,					NULL },
		{ "=",						1,			false,		_MC_ICODE_EQUAL_SIGN,					false,				NULL,					NULL },
		{ "|",						1,			false,		_MC_ICODE_PIPE_SIGN,					false,				NULL,					NULL },
		{ "`",						1,			false,		_MC_ICODE_REVERSE_QUOTE,				false,				NULL,					NULL },
		{ ";",						1,			false,		_MC_ICODE_SEMICOLON,					false,				NULL,					NULL },
		{ ">",						1,			false,		_MC_ICODE_GREATER_THAN,					false,				NULL,					NULL },
		{ "<",						1,			false,		_MC_ICODE_LESS_THAN,					false,				NULL,					NULL },
		/* As a last-case condition, we tag every character that we didn't previously identify with the unknown tag */                      	
		{ "_\000\377\000\000",		1,			true,		_MC_ICODE_UNKNOWN,						false,				NULL,					NULL },
		{ 0,						0,			0,			0,										0,					0,						0 }
	};




	// Pre-zeroeth-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywordsPre[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		validate handler		custom handler
		{ "(||",					3,			false,		_MC_ICODE_CASK_ROUND_OPEN_PARAMS,		false,				NULL,					NULL },
		{ "||)",					3,			false,		_MC_ICODE_CASK_ROUND_CLOSE_PARAMS,		false,				NULL,					NULL },
		{ "[||",					3,			false,		_MC_ICODE_CASK_SQUARE_OPEN_PARAMS,		false,				NULL,					NULL },
		{ "||]",					3,			false,		_MC_ICODE_CASK_SQUARE_CLOSE_PARAMS,		false,				NULL,					NULL },
		{ "<||",					3,			false,		_MC_ICODE_CASK_TRIANGLE_OPEN_PARAMS,	false,				NULL,					NULL },
		{ "||>",					3,			false,		_MC_ICODE_CASK_TRIANGLE_CLOSE_PARAMS,	false,				NULL,					NULL },
		{ "~||",					3,			false,		_MC_ICODE_CASK_TILDE_OPEN_PARAMS,		false,				NULL,					NULL },
		{ "||~",					3,			false,		_MC_ICODE_CASK_TILDE_CLOSE_PARAMS,		false,				NULL,					NULL },
		{ "(|",						2,			false,		_MC_ICODE_CASK_ROUND_OPEN,				false,				NULL,					NULL },
		{ "|)",						2,			false,		_MC_ICODE_CASK_ROUND_CLOSE,				false,				NULL,					NULL },
		{ "[|",						2,			false,		_MC_ICODE_CASK_SQUARE_OPEN,				false,				NULL,					NULL },
		{ "|]",						2,			false,		_MC_ICODE_CASK_SQUARE_CLOSE,			false,				NULL,					NULL },
		{ "<|",						2,			false,		_MC_ICODE_CASK_TRIANGLE_OPEN,			false,				NULL,					NULL },
		{ "|>",						2,			false,		_MC_ICODE_CASK_TRIANGLE_CLOSE,			false,				NULL,					NULL },
		{ "~|",						2,			false,		_MC_ICODE_CASK_TILDE_OPEN,				false,				NULL,					NULL },
		{ "|~",						2,			false,		_MC_ICODE_CASK_TILDE_CLOSE,				false,				NULL,					NULL },
		{ "include",				7,			false,		_MC_ICODE_INCLUDE,						true,				NULL,					NULL },
		{ "define",					6,			false,		_MC_ICODE_DEFINE,						true,				NULL,					NULL },
		{ "dll",					3,			false,		_MC_ICODE_DLL,							true,				NULL,					NULL },
		{ "bxml",					4,			false,		_MC_ICODE_BXML,							true,				NULL,					NULL },
		{ "params",					6,			false,		_MC_ICODE_PARAMS,						true,				NULL,					NULL },
		{ "returns",				7,			false,		_MC_ICODE_RETURNS,						true,				NULL,					NULL },
		{ "dsnip",					5,			false,		_MC_ICODE_DSNIP,						true,				NULL,					NULL },
		{ "snip",					4,			false,		_MC_ICODE_SNIP,							true,				NULL,					NULL },
		{ "dll_function",			12,			false,		_MC_ICODE_DLL_FUNCTION,					true,				NULL,					NULL },
		{ "end",					3,			false,		_MC_ICODE_END,							true,				NULL,					NULL },
		{ "prototype",				9,			false,		_MC_ICODE_PROTOTYPE,					true,				NULL,					NULL },
		{ "u8",						2,			false,		_MC_ICODE_U8,							false,				NULL,					NULL },
		{ "u16",					3,			false,		_MC_ICODE_U16,							false,				NULL,					NULL },
		{ "u32",					3,			false,		_MC_ICODE_U32,							false,				NULL,					NULL },
		{ "u64",					3,			false,		_MC_ICODE_U64,							false,				NULL,					NULL },
		{ "s8",						2,			false,		_MC_ICODE_S8,							false,				NULL,					NULL },
		{ "s16",					3,			false,		_MC_ICODE_S16,							false,				NULL,					NULL },
		{ "s32",					3,			false,		_MC_ICODE_S32,							false,				NULL,					NULL },
		{ "s64",					3,			false,		_MC_ICODE_S64,							false,				NULL,					NULL },
		{ "f32",					3,			false,		_MC_ICODE_F32,							false,				NULL,					NULL },
		{ "f64",					3,			false,		_MC_ICODE_F64,							false,				NULL,					NULL },
		{ "bni",					3,			false,		_MC_ICODE_BNI,							false,				NULL,					NULL },
		{ "bnf",					3,			false,		_MC_ICODE_BNF,							false,				NULL,					NULL },
		{ "line",					4,			false,		_MC_ICODE_LINE,							true,				NULL,					NULL },
		{ "//",						2,			true,		_MC_ICODE_COMMENT,						true,				NULL,					NULL },
		{ 0,						0,			0,			0,										0,					0,						0 }
	};




	// Zeroeth-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywords0[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		validate handler		custom handler
		{ "esnip",					5,			false,		_MC_ICODE_ESNIP_REG,					false,				NULL,					NULL },
		{ "ip",						2,			false,		_MC_ICODE_IP_REG,						false,				NULL,					NULL },
		{ "sp",						2,			false,		_MC_ICODE_SP_REG,						false,				NULL,					NULL },
		{ "bp",						2,			false,		_MC_ICODE_BP_REG,						false,				NULL,					NULL },
		{ "ready",					5,			false,		_MC_ICODE_READY_REG,					false,				NULL,					NULL },
		{ "ready.offset",			12,			false,		_MC_ICODE_READY_OFFSET_REG,				false,				NULL,					NULL },
		{ "flags",					5,			false,		_MC_ICODE_FLAGS_REG,					false,				NULL,					NULL },
		{ "pred",					4,			false,		_MC_ICODE_PRED_REG,						false,				NULL,					NULL },
		{ "pred.count",				10,			false,		_MC_ICODE_PREDCOUNT_REG,				false,				NULL,					NULL },
		{ "exsnip",					6,			false,		_MC_ICODE_EXSNIP_REG,					false,				NULL,					NULL },
		{ "error",					5,			false,		_MC_ICODE_ERROR_REG,					false,				NULL,					NULL },
		{ "a",						1,			false,		_MC_ICODE_A,							false,				NULL,					NULL },
		{ "b",						1,			false,		_MC_ICODE_B,							false,				NULL,					NULL },
		{ "c",						1,			false,		_MC_ICODE_C,							false,				NULL,					NULL },
		{ "d",						1,			false,		_MC_ICODE_D,							false,				NULL,					NULL },
		{ "e",						1,			false,		_MC_ICODE_E,							false,				NULL,					NULL },
		{ "f",						1,			false,		_MC_ICODE_F,							false,				NULL,					NULL },
		{ "g",						1,			false,		_MC_ICODE_G,							false,				NULL,					NULL },
		{ "h",						1,			false,		_MC_ICODE_H,							false,				NULL,					NULL },
		{ "i",						1,			false,		_MC_ICODE_I,							false,				NULL,					NULL },
		{ "j",						1,			false,		_MC_ICODE_J,							false,				NULL,					NULL },
		{ "k",						1,			false,		_MC_ICODE_K,							false,				NULL,					NULL },
		{ "l",						1,			false,		_MC_ICODE_L,							false,				NULL,					NULL },
		{ "m",						1,			false,		_MC_ICODE_M,							false,				NULL,					NULL },
		{ "n",						1,			false,		_MC_ICODE_N,							false,				NULL,					NULL },
		{ "o",						1,			false,		_MC_ICODE_O,							false,				NULL,					NULL },
		{ "p",						1,			false,		_MC_ICODE_P,							false,				NULL,					NULL },
		{ "fa",						2,			false,		_MC_ICODE_FA,							false,				NULL,					NULL },
		{ "fb",						2,			false,		_MC_ICODE_FB,							false,				NULL,					NULL },
		{ "fc",						2,			false,		_MC_ICODE_FC,							false,				NULL,					NULL },
		{ "fd",						2,			false,		_MC_ICODE_FD,							false,				NULL,					NULL },
		{ "fe",						2,			false,		_MC_ICODE_FE,							false,				NULL,					NULL },
		{ "ff",						2,			false,		_MC_ICODE_FF,							false,				NULL,					NULL },
		{ "fg",						2,			false,		_MC_ICODE_FG,							false,				NULL,					NULL },
		{ "fh",						2,			false,		_MC_ICODE_FH,							false,				NULL,					NULL },
		{ "fi",						2,			false,		_MC_ICODE_FI,							false,				NULL,					NULL },
		{ "fj",						2,			false,		_MC_ICODE_FJ,							false,				NULL,					NULL },
		{ "fk",						2,			false,		_MC_ICODE_FK,							false,				NULL,					NULL },
		{ "fl",						2,			false,		_MC_ICODE_FL,							false,				NULL,					NULL },
		{ "fm",						2,			false,		_MC_ICODE_FM,							false,				NULL,					NULL },
		{ "fn",						2,			false,		_MC_ICODE_FN,							false,				NULL,					NULL },
		{ "fo",						2,			false,		_MC_ICODE_FO,							false,				NULL,					NULL },
		{ "fp",						2,			false,		_MC_ICODE_FP,							false,				NULL,					NULL },
		{ "result2",				7,			false,		_MC_ICODE_RESULT2,						false,				NULL,					NULL },
		{ "result",					6,			false,		_MC_ICODE_RESULT,						false,				NULL,					NULL },
		{ 0,						0,			0,			0,										0,					0,						0 }
	};




	// First-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywords1[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		validate handler		custom handler
		{ "add",					3,			false,		_MC_ICODE_ADD_CMD,						true,				 NULL,					NULL },
		{ "sub",					3,			false,		_MC_ICODE_SUB_CMD,						true,				 NULL,					NULL },
		{ "mul",					3,			false,		_MC_ICODE_MUL_CMD,						true,				 NULL,					NULL },
		{ "div",					3,			false,		_MC_ICODE_DIV_CMD,						true,				 NULL,					NULL },
		{ "comp",					4,			false,		_MC_ICODE_COMP_CMD,						true,				 NULL,					NULL },
		{ "copy",					4,			false,		_MC_ICODE_COPY_CMD,						true,				 NULL,					NULL },
		{ "move",					4,			false,		_MC_ICODE_MOVE_CMD,						true,				 NULL,					NULL },
		{ "exchange",				8,			false,		_MC_ICODE_EXCHANGE_CMD,					true,				 NULL,					NULL },
		{ "and",					3,			false,		_MC_ICODE_AND_CMD,						true,				 NULL,					NULL },
		{ "or",						2,			false,		_MC_ICODE_OR_CMD,						true,				 NULL,					NULL },
		{ "not",					3,			false,		_MC_ICODE_NOT_CMD,						true,				 NULL,					NULL },
		{ "xor",					3,			false,		_MC_ICODE_XOR_CMD,						true,				 NULL,					NULL },
		{ "neg",					3,			false,		_MC_ICODE_NEG_CMD,						true,				 NULL,					NULL },
		{ "inc",					3,			false,		_MC_ICODE_INC_CMD,						true,				 NULL,					NULL },
		{ "dec",					3,			false,		_MC_ICODE_DEC_CMD,						true,				 NULL,					NULL },
		{ "shl",					3,			false,		_MC_ICODE_SHL_CMD,						true,				 NULL,					NULL },
		{ "shr",					3,			false,		_MC_ICODE_SHR_CMD,						true,				 NULL,					NULL },
		{ "rol",					3,			false,		_MC_ICODE_ROL_CMD,						true,				 NULL,					NULL },
		{ "ror",					3,			false,		_MC_ICODE_ROR_CMD,						true,				 NULL,					NULL },
		{ "address",				7,			false,		_MC_ICODE_ADDRESS_CMD,					true,				 NULL,					NULL },
		{ "flag",					4,			false,		_MC_ICODE_FLAG_CMD,						true,				 NULL,					NULL },
		{ "flags",					5,			false,		_MC_ICODE_FLAGS_CMD,					true,				 NULL,					NULL },
		{ "bump",					4,			false,		_MC_ICODE_BUMP_CMD,						true,				 NULL,					NULL },
		{ "debug",					5,			false,		_MC_ICODE_DEBUG_CMD,					true,				 NULL,					NULL },
		{ "sleep",					5,			false,		_MC_ICODE_SLEEP_CMD,					true,				 NULL,					NULL },
		{ "nop",					3,			false,		_MC_ICODE_NOP_CMD,						true,				 NULL,					NULL },
		{ "exception",				9,			false,		_MC_ICODE_EXCEPTION_CMD,				true,				 NULL,					NULL },
		{ "jump",					4,			false,		_MC_ICODE_JUMP_CMD,						true,				 NULL,					NULL },
		{ "call",					4,			false,		_MC_ICODE_CALL_CMD,						true,				 NULL,					NULL },
		{ "host",					4,			false,		_MC_ICODE_HOST_CMD,						true,				 NULL,					NULL },
		{ "push",					4,			false,		_MC_ICODE_PUSH_CMD,						true,				 NULL,					NULL },
		{ "pop",					3,			false,		_MC_ICODE_POP_CMD,						true,				 NULL,					NULL },
		{ "regs",					4,			false,		_MC_ICODE_REGS_CMD,						true,				 NULL,					NULL },
		{ "ready",					5,			false,		_MC_ICODE_READY_CMD,					true,				 NULL,					NULL },
		{ "set",					3,			false,		_MC_ICODE_SET_CMD,						true,				 NULL,					NULL },
		{ "go",						2,			false,		_MC_ICODE_GO_CMD,						true,				 NULL,					NULL },
		{ "semaphore",				9,			false,		_MC_ICODE_SEMAPHORE_CMD,				true,				 NULL,					NULL },
		{ "pred",					4,			false,		_MC_ICODE_PRED_CMD_CMD,					true,				 NULL,					NULL },
		{ "x86",					3,			false,		_MC_ICODE_X86_CMD,						true,				 NULL,					NULL },
		{ "arm",					3,			false,		_MC_ICODE_ARM_CMD,						true,				 NULL,					NULL },
		{ "out",					3,			false,		_MC_ICODE_OUT,							false,				 NULL,					NULL },
		{ "in",						2,			false,		_MC_ICODE_IN,							false,				 NULL,					NULL },
		{ "sno",					3,			false,		_MC_ICODE_SNO,							false,				 NULL,					NULL },
		{ "dsno",					4,			false,		_MC_ICODE_DSNO,							false,				 NULL,					NULL },
		{ "hard",					4,			false,		_MC_ICODE_HARD,							false,				 NULL,					NULL },
		{ "back",					4,			false,		_MC_ICODE_BACK,							false,				 NULL,					NULL },
		{ "set",					3,			false,		_MC_ICODE_SET2,							false,				 NULL,					NULL },
		{ "clear",					5,			false,		_MC_ICODE_CLEAR,						false,				 NULL,					NULL },
		{ "toggle",					6,			false,		_MC_ICODE_TOGGLE,						false,				 NULL,					NULL },
		{ "offset",					6,			false,		_MC_ICODE_OFFSET,						false,				 NULL,					NULL },
		{ "skip",					4,			false,		_MC_ICODE_SKIP,							false,				 NULL,					NULL },
		{ "imm64",					5,			false,		_MC_ICODE_IMM64,						false,				 NULL,					NULL },
		{ "imm32",					5,			false,		_MC_ICODE_IMM32,						false,				 NULL,					NULL },
		{ "create",					6,			false,		_MC_ICODE_CREATE,						false,				 NULL,					NULL },
		{ "trylock",				7,			false,		_MC_ICODE_TRYLOCK,						false,				 NULL,					NULL },
		{ "lock",					4,			false,		_MC_ICODE_LOCK,							false,				 NULL,					NULL },
		{ "unlock",					6,			false,		_MC_ICODE_UNLOCK,						false,				 NULL,					NULL },
		{ "delete",					6,			false,		_MC_ICODE_DELETE,						false,				 NULL,					NULL },
		{ "load",					4,			false,		_MC_ICODE_LOAD,							false,				 NULL,					NULL },
		{ "fill",					4,			false,		_MC_ICODE_FILL,							false,				 NULL,					NULL },
		{ "64",						2,			false,		_MC_ICODE_64,							false,				 (u64)&iimc_checkDotPrefix,	NULL },
		{ "32",						2,			false,		_MC_ICODE_32,							false,				 (u64)&iimc_checkDotPrefix,	NULL },
		{ "16",						2,			false,		_MC_ICODE_16,							false,				 (u64)&iimc_checkDotPrefix,	NULL },
		{ "8",						2,			false,		_MC_ICODE_8,							false,				 (u64)&iimc_checkDotPrefix,	NULL },
		{ 0,						0,			0,			0,										0,					0 }
	};
