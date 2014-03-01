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
		// keyword					length		repeats?	extra (type)							first on line?		custom handler
		{ "_azAZ__\000\000",		1,			true,		_MC_ICODE_ALPHA,						false,				NULL },
		{ "_09\000\000",			1,			true,		_MC_ICODE_NUMERIC,						false,				NULL },
		{ " ",						1,			true,		_MC_ICODE_WHITESPACE,					false,				NULL },
		{ "\t",						1,			true,		_MC_ICODE_WHITESPACE,					false,				NULL },
		{ "___",					1,			false,		_MC_ICODE_UNDERSCORE,					false,				NULL },
		{ "(",						1,			false,		_MC_ICODE_LEFT_PARENTHESIS,				false,				NULL },
		{ ")",						1,			false,		_MC_ICODE_RIGHT_PARENTHESIS,			false,				NULL },
		{ "[",						1,			false,		_MC_ICODE_LEFT_BRACKET,					false,				NULL },
		{ "]",						1,			false,		_MC_ICODE_RIGHT_BRACKET,				false,				NULL },
		{ "{",						1,			false,		_MC_ICODE_LEFT_BRACE,					false,				NULL },
		{ "}",						1,			false,		_MC_ICODE_RIGHT_BRACE,					false,				NULL },
		{ "+",						1,			false,		_MC_ICODE_PLUS,							false,				NULL },
		{ "-",						1,			false,		_MC_ICODE_MINU,							false,				NULL },
		{ "*",						1,			true,		_MC_ICODE_ASTERISK,						false,				NULL },
		{ "\\",						1,			true,		_MC_ICODE_SLASH,						false,				NULL },
		{ "/",						1,			true,		_MC_ICODE_BACKSLASH,					false,				NULL },
		{ "\"",						1,			false,		_MC_ICODE_DOUBLE_QUOTE,					false,				NULL },
		{ "'",						1,			false,		_MC_ICODE_SINGLE_QUOTE,					false,				NULL },
		{ ".",						1,			false,		_MC_ICODE_PERIOD,						false,				NULL },
		{ ",",						1,			false,		_MC_ICODE_COMMA,						false,				NULL },
		{ ":",						1,			false,		_MC_ICODE_COLON,						false,				NULL },
		{ "_",						1,			false,		_MC_ICODE_UNDERSCORE,					false,				NULL },
		{ "~",						1,			false,		_MC_ICODE_TILDE,						false,				NULL },
		{ "@",						1,			false,		_MC_ICODE_AT_SIGN,						false,				NULL },
		{ "?",						1,			false,		_MC_ICODE_QUESTION_MARK,				false,				NULL },
		{ "!",						1,			false,		_MC_ICODE_EXCLAMATION_MARK,				false,				NULL },
		{ "#",						1,			false,		_MC_ICODE_POUND_SIGN,					false,				NULL },
		{ "$",						1,			false,		_MC_ICODE_DOLLAR_SIGN,					false,				NULL },
		{ "%",						1,			false,		_MC_ICODE_PERCENT_SIGN,					false,				NULL },
		{ "^",						1,			false,		_MC_ICODE_CARET,						false,				NULL },
		{ "&",						1,			false,		_MC_ICODE_AMPERSAND,					false,				NULL },
		{ "=",						1,			false,		_MC_ICODE_EQUAL_SIGN,					false,				NULL },
		{ "|",						1,			false,		_MC_ICODE_PIPE_SIGN,					false,				NULL },
		{ "`",						1,			false,		_MC_ICODE_REVERSE_QUOTE,				false,				NULL },
		{ ";",						1,			false,		_MC_ICODE_SEMICOLON,					false,				NULL },
		{ ">",						1,			false,		_MC_ICODE_GREATER_THAN,					false,				NULL },
		{ "<",						1,			false,		_MC_ICODE_LESS_THAN,					false,				NULL },
		/* As a last-case condition, we tag every character that we didn't previously identify with the unknown tag */
		{ "_\000\377\000\000",		1,			true,		_MC_ICODE_UNKNOWN,						false,				NULL },
		{ 0,						0,			0,			0,										0,					0 }
	};




	// Pre-zeroeth-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywordsPre[] =
	{
		// keyword					length		repeats?	extra (type)								first on line?		custom handler
		{ "include",				7,			false,		_MC_ICODE_INCLUDE,						true,				NULL },
		{ "define",					6,			false,		_MC_ICODE_DEFINE,						true,				NULL },
		{ "//",						2,			true,		_MC_ICODE_COMMENT,						true,				NULL },
		{ 0,						0,			0,			0,										0,					0 }
	};




	// Zeroeth-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywords0[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		custom handler
		{ "dsnip_bxml",				10,			false,		_MC_ICODE_DSNIP_BXML_DEFINITION,		true,				NULL },
		{ "dsnip_dll",				9,			false,		_MC_ICODE_DSNIP_DLL_DEFINITION,			true,				NULL },
		{ "dsnip",					5,			false,		_MC_ICODE_DSNIP_DEFINITION,				true,				NULL },
		{ "snip",					4,			false,		_MC_ICODE_SNIP_DEFINITION,				true,				NULL },
		{ "function",				8,			false,		_MC_ICODE_SNIP_DEFINITION,				true,				NULL },
		{ "dll_function",			12,			false,		_MC_ICODE_DLL_FUNCTION_DEFINITION,		true,				NULL },
		{ "end",					3,			false,		_MC_ICODE_END,							true,				NULL },
		{ "prototype",				9,			false,		_MC_ICODE_PROTOTYPE,					true,				NULL },

		{ "params",					6,			false,		_MC_ICODE_PARAMS_DEFINITION,			false,				NULL },
		{ "returns",				7,			false,		_MC_ICODE_RETURN_DEFINITION,			false,				NULL },
		{ "locals",					6,			false,		_MC_ICODE_LOCALS_DEFINITION,			false,				NULL },

		{ "u8",						2,			false,		_MC_ICODE_U8_DEFINITION,				true,				NULL },
		{ "u16",					3,			false,		_MC_ICODE_U16_DEFINITION,				true,				NULL },
		{ "u32",					3,			false,		_MC_ICODE_U32_DEFINITION,				true,				NULL },
		{ "u64",					3,			false,		_MC_ICODE_U64_DEFINITION,				true,				NULL },
		{ "s8",						2,			false,		_MC_ICODE_S8_DEFINITION,				true,				NULL },
		{ "s16",					3,			false,		_MC_ICODE_S16_DEFINITION,				true,				NULL },
		{ "s32",					3,			false,		_MC_ICODE_S32_DEFINITION,				true,				NULL },
		{ "s64",					3,			false,		_MC_ICODE_S64_DEFINITION,				true,				NULL },
		{ "f32",					3,			false,		_MC_ICODE_F32_DEFINITION,				true,				NULL },
		{ "f64",					3,			false,		_MC_ICODE_F64_DEFINITION,				true,				NULL },
		{ "bni",					3,			false,		_MC_ICODE_BNI_DEFINITION,				true,				NULL },
		{ "bnf",					3,			false,		_MC_ICODE_BNF_DEFINITION,				true,				NULL },

		{ "u8",						2,			false,		_MC_ICODE_U8,							false,				NULL },
		{ "u16",					3,			false,		_MC_ICODE_U16,							false,				NULL },
		{ "u32",					3,			false,		_MC_ICODE_U32,							false,				NULL },
		{ "u64",					3,			false,		_MC_ICODE_U64,							false,				NULL },
		{ "s8",						2,			false,		_MC_ICODE_S8,							false,				NULL },
		{ "s16",					3,			false,		_MC_ICODE_S16,							false,				NULL },
		{ "s32",					3,			false,		_MC_ICODE_S32,							false,				NULL },
		{ "s64",					3,			false,		_MC_ICODE_S64,							false,				NULL },
		{ "f32",					3,			false,		_MC_ICODE_F32,							false,				NULL },
		{ "f64",					3,			false,		_MC_ICODE_F64,							false,				NULL },
		{ "bni",					3,			false,		_MC_ICODE_BNI,							false,				NULL },
		{ "bnf",					3,			false,		_MC_ICODE_BNF,							false,				NULL },

		{ "snip",					4,			false,		_MC_ICODE_SNIP,							false,				NULL },
		{ "ip",						2,			false,		_MC_ICODE_IP,							false,				NULL },
		{ "sp",						2,			false,		_MC_ICODE_SP,							false,				NULL },
		{ "bp",						2,			false,		_MC_ICODE_BP,							false,				NULL },
		{ "ready",					5,			false,		_MC_ICODE_READY,						false,				NULL },
		{ "ready.offset",			12,			false,		_MC_ICODE_READY_OFFSET,					false,				NULL },
		{ "flags",					5,			false,		_MC_ICODE_FLAGS,						false,				NULL },
		{ "pred",					4,			false,		_MC_ICODE_PRED,							false,				NULL },
		{ "pred.count",				10,			false,		_MC_ICODE_PREDCOUNT,					false,				NULL },
		{ "exsnip",					6,			false,		_MC_ICODE_EXSNIP,						false,				NULL },
		{ "error",					5,			false,		_MC_ICODE_ERROR,						false,				NULL },

		{ "a",						1,			false,		_MC_ICODE_A,							false,				NULL },
		{ "b",						1,			false,		_MC_ICODE_B,							false,				NULL },
		{ "c",						1,			false,		_MC_ICODE_C,							false,				NULL },
		{ "d",						1,			false,		_MC_ICODE_D,							false,				NULL },
		{ "e",						1,			false,		_MC_ICODE_E,							false,				NULL },
		{ "f",						1,			false,		_MC_ICODE_F,							false,				NULL },
		{ "g",						1,			false,		_MC_ICODE_G,							false,				NULL },
		{ "h",						1,			false,		_MC_ICODE_H,							false,				NULL },
		{ "i",						1,			false,		_MC_ICODE_I,							false,				NULL },
		{ "j",						1,			false,		_MC_ICODE_J,							false,				NULL },
		{ "k",						1,			false,		_MC_ICODE_K,							false,				NULL },
		{ "l",						1,			false,		_MC_ICODE_L,							false,				NULL },
		{ "m",						1,			false,		_MC_ICODE_M,							false,				NULL },
		{ "n",						1,			false,		_MC_ICODE_N,							false,				NULL },
		{ "o",						1,			false,		_MC_ICODE_O,							false,				NULL },
		{ "p",						1,			false,		_MC_ICODE_P,							false,				NULL },

		{ "fa",						2,			false,		_MC_ICODE_FA,							false,				NULL },
		{ "fb",						2,			false,		_MC_ICODE_FB,							false,				NULL },
		{ "fc",						2,			false,		_MC_ICODE_FC,							false,				NULL },
		{ "fd",						2,			false,		_MC_ICODE_FD,							false,				NULL },
		{ "fe",						2,			false,		_MC_ICODE_FE,							false,				NULL },
		{ "ff",						2,			false,		_MC_ICODE_FF,							false,				NULL },
		{ "fg",						2,			false,		_MC_ICODE_FG,							false,				NULL },
		{ "fh",						2,			false,		_MC_ICODE_FH,							false,				NULL },
		{ "fi",						2,			false,		_MC_ICODE_FI,							false,				NULL },
		{ "fj",						2,			false,		_MC_ICODE_FJ,							false,				NULL },
		{ "fk",						2,			false,		_MC_ICODE_FK,							false,				NULL },
		{ "fl",						2,			false,		_MC_ICODE_FL,							false,				NULL },
		{ "fm",						2,			false,		_MC_ICODE_FM,							false,				NULL },
		{ "fn",						2,			false,		_MC_ICODE_FN,							false,				NULL },
		{ "fo",						2,			false,		_MC_ICODE_FO,							false,				NULL },
		{ "fp",						2,			false,		_MC_ICODE_FP,							false,				NULL },

		{ "result2",				7,			false,		_MC_ICODE_RESULT2,						false,				NULL },
		{ "result",					6,			false,		_MC_ICODE_RESULT,						false,				NULL },

		{ 0,						0,			0,			0,										0,					0 }
	};




	// First-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywords1[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		custom handler
		{ "add",					3,			false,		_MC_ICODE_ADD,							true,				 NULL },
		{ "sub",					3,			false,		_MC_ICODE_SUB,							true,				 NULL },
		{ "mul",					3,			false,		_MC_ICODE_MUL,							true,				 NULL },
		{ "div",					3,			false,		_MC_ICODE_DIV,							true,				 NULL },
		{ "comp",					4,			false,		_MC_ICODE_COMP,							true,				 NULL },
		{ "copy",					4,			false,		_MC_ICODE_COPY,							true,				 NULL },
		{ "move",					4,			false,		_MC_ICODE_MOVE,							true,				 NULL },
		{ "exchange",				8,			false,		_MC_ICODE_EXCHANGE,						true,				 NULL },
		{ "and",					3,			false,		_MC_ICODE_AND,							true,				 NULL },
		{ "or",						2,			false,		_MC_ICODE_OR,							true,				 NULL },
		{ "not",					3,			false,		_MC_ICODE_NOT,							true,				 NULL },
		{ "xor",					3,			false,		_MC_ICODE_XOR,							true,				 NULL },
		{ "neg",					3,			false,		_MC_ICODE_NEG,							true,				 NULL },
		{ "inc",					3,			false,		_MC_ICODE_INC,							true,				 NULL },
		{ "dec",					3,			false,		_MC_ICODE_DEC,							true,				 NULL },
		{ "shl",					3,			false,		_MC_ICODE_SHL,							true,				 NULL },
		{ "shr",					3,			false,		_MC_ICODE_SHR,							true,				 NULL },
		{ "rol",					3,			false,		_MC_ICODE_ROL,							true,				 NULL },
		{ "ror",					3,			false,		_MC_ICODE_ROR,							true,				 NULL },
		{ "address",				7,			false,		_MC_ICODE_ADDRESS,						true,				 NULL },
		{ "flag",					4,			false,		_MC_ICODE_FLAG,							true,				 NULL },
		{ "flags",					5,			false,		_MC_ICODE_FLAGS,						true,				 NULL },
		{ "bump",					4,			false,		_MC_ICODE_BUMP,							true,				 NULL },
		{ "debug",					5,			false,		_MC_ICODE_DEBUG,						true,				 NULL },
		{ "sleep",					5,			false,		_MC_ICODE_SLEEP,						true,				 NULL },
		{ "nop",					3,			false,		_MC_ICODE_NOP,							true,				 NULL },
		{ "exception",				9,			false,		_MC_ICODE_EXCEPTION,					true,				 NULL },
		{ "jump",					4,			false,		_MC_ICODE_JUMP,							true,				 NULL },
		{ "call",					4,			false,		_MC_ICODE_CALL,							true,				 NULL },
		{ "host",					4,			false,		_MC_ICODE_HOST,							true,				 NULL },
		{ "push",					4,			false,		_MC_ICODE_PUSH,							true,				 NULL },
		{ "pop",					3,			false,		_MC_ICODE_POP,							true,				 NULL },
		{ "regs",					4,			false,		_MC_ICODE_REGS,							true,				 NULL },
		{ "ready",					5,			false,		_MC_ICODE_READY,						true,				 NULL },
		{ "set",					3,			false,		_MC_ICODE_SET,							true,				 NULL },
		{ "go",						2,			false,		_MC_ICODE_GO,							true,				 NULL },
		{ "semaphore",				9,			false,		_MC_ICODE_SEMAPHORE,					true,				 NULL },
		{ "pred",					4,			false,		_MC_ICODE_PRED,							true,				 NULL },
		{ "x86",					3,			false,		_MC_ICODE_X86,							true,				 NULL },
		{ "arm",					3,			false,		_MC_ICODE_ARM,							true,				 NULL },
		
		{ "out",					3,			false,		_MC_ICODE_OUT,							false,				 NULL },
		{ "in",						2,			false,		_MC_ICODE_IN,							false,				 NULL },
		{ "sno",					3,			false,		_MC_ICODE_SNO,							false,				 NULL },
		{ "dsno",					4,			false,		_MC_ICODE_DSNO,							false,				 NULL },
		{ "hard",					4,			false,		_MC_ICODE_HARD,							false,				 NULL },
		{ "back",					4,			false,		_MC_ICODE_BACK,							false,				 NULL },
		{ "set",					3,			false,		_MC_ICODE_SET2,							false,				 NULL },
		{ "clear",					5,			false,		_MC_ICODE_CLEAR,						false,				 NULL },
		{ "toggle",					6,			false,		_MC_ICODE_TOGGLE,						false,				 NULL },
		{ "offset",					6,			false,		_MC_ICODE_OFFSET,						false,				 NULL },
		{ "skip",					4,			false,		_MC_ICODE_SKIP,							false,				 NULL },
		{ "imm64",					5,			false,		_MC_ICODE_IMM64,						false,				 NULL },
		{ "imm32",					5,			false,		_MC_ICODE_IMM32,						false,				 NULL },
		{ "create",					6,			false,		_MC_ICODE_CREATE,						false,				 NULL },
		{ "trylock",				7,			false,		_MC_ICODE_TRYLOCK,						false,				 NULL },
		{ "lock",					4,			false,		_MC_ICODE_LOCK,							false,				 NULL },
		{ "unlock",					6,			false,		_MC_ICODE_UNLOCK,						false,				 NULL },
		{ "delete",					6,			false,		_MC_ICODE_DELETE,						false,				 NULL },
		{ "load",					4,			false,		_MC_ICODE_LOAD,							false,				 NULL },
		{ "fill",					4,			false,		_MC_ICODE_FILL,							false,				 NULL },
		
		{ 0,						0,			0,			0,										0,					0 }
	};
