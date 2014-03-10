//////////
//
// /libsf/vvm/vvmmc/mc_const.h
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.25.2014
//////
// Change log:
//     Feb.25.2014 - Development on 0.70 begins
//     Nov.13.2012 - Initial creation
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
//




//////////
//
// Constant strings
//
//////
	const s8		cgcVvmmcVersion[]								= "MC.DLL Version 0.70";		// The format of this version string will remain consistent throughout all future releases
	const s8		cgcUnableToLocateResource[]						= "Unable to locate resource";




//////////
//
// Constant types
//
//////
	const u32		_MC_ICODE_UNKNOWN								= 0;
	const u32		_MC_ICODE_ALPHA									= 1;
	const u32		_MC_ICODE_ALPHANUMERIC							= 2;
	const u32		_MC_ICODE_NUMERIC								= 3;
	const u32		_MC_ICODE_OPERATOR								= 4;
	const u32		_MC_ICODE_WHITESPACE							= 5;
	const u32		_MC_ICODE_PLUS									= 6;
	const u32		_MC_ICODE_MINU									= 7;
	const u32		_MC_ICODE_ASTERISK								= 8;
	const u32		_MC_ICODE_BACKSLASH								= 9;
	const u32		_MC_ICODE_DOUBLE_QUOTE							= 10;
	const u32		_MC_ICODE_SINGLE_QUOTE							= 11;
	const u32		_MC_ICODE_TILDE									= 12;
	const u32		_MC_ICODE_DOT									= 13;
	const u32		_MC_ICODE_COLON									= 14;
	const u32		_MC_ICODE_COMMA									= 15;
	const u32		_MC_ICODE_UNDERSCORE							= 16;
	const u32		_MC_ICODE_AT_SIGN								= 17;
	const u32		_MC_ICODE_QUESTION_MARK							= 18;
	const u32		_MC_ICODE_EXCLAMATION_MARK						= 19;
	const u32		_MC_ICODE_POUND_SIGN							= 20;
	const u32		_MC_ICODE_PERCENT_SIGN							= 21;
	const u32		_MC_ICODE_CARET									= 22;
	const u32		_MC_ICODE_AMPERSAND								= 23;
	const u32		_MC_ICODE_EQUAL_SIGN							= 24;
	const u32		_MC_ICODE_PIPE_SIGN								= 25;
	const u32		_MC_ICODE_REVERSE_QUOTE							= 26;
	const u32		_MC_ICODE_SEMICOLON								= 27;
	const u32		_MC_ICODE_GREATER_THAN							= 28;
	const u32		_MC_ICODE_LESS_THAN								= 30;
	const u32		_MC_ICODE_LEFT_PARENTHESIS						= 31;
	const u32		_MC_ICODE_RIGHT_PARENTHESIS						= 32;
	const u32		_MC_ICODE_LEFT_BRACKET							= 33;
	const u32		_MC_ICODE_RIGHT_BRACKET							= 34;
	const u32		_MC_ICODE_LEFT_BRACE							= 35;
	const u32		_MC_ICODE_RIGHT_BRACE							= 36;
	const u32		_MC_ICODE_SLASH									= 37;
	const u32		_MC_ICODE_DOLLAR_SIGN							= 38;

	// Combined items
	const u32		_MC_ICODE_SINGLE_QUOTED_TEXT					= 90;
	const u32		_MC_ICODE_DOUBLE_QUOTED_TEXT					= 91;

	const u32		_MC_ICODE_INCLUDE								= 100;
	const u32		_MC_ICODE_DEFINE								= 101;
	const u32		_MC_ICODE_DLL_FUNCTION_DEFINITION				= 106;
	const u32		_MC_ICODE_PROTOTYPE								= 107;
	const u32		_MC_ICODE_END									= 108;

	const u32		_MC_ICODE_PARAMS_DEFINITION						= 109;
	const u32		_MC_ICODE_RETURN_DEFINITION						= 110;
	const u32		_MC_ICODE_LOCALS_DEFINITION						= 111;

	const u32		_MC_LOWEST_ICODE_VARIABLE_DEFINITION			= 2000;
	const u32		_MC_ICODE_U8									= 2000;
	const u32		_MC_ICODE_U16									= 2001;
	const u32		_MC_ICODE_U32									= 2002;
	const u32		_MC_ICODE_U64									= 2003;
	const u32		_MC_ICODE_S8									= 2004;
	const u32		_MC_ICODE_S16									= 2005;
	const u32		_MC_ICODE_S32									= 2006;
	const u32		_MC_ICODE_S64									= 2007;
	const u32		_MC_ICODE_F32									= 2008;
	const u32		_MC_ICODE_F64									= 2009;
	const u32		_MC_ICODE_BNI									= 2010;
	const u32		_MC_ICODE_BNF									= 2011;
	const u32		_MC_HIGHEST_ICODE_VARIABLE_DEFINITION			= 2011;

	const u32		_MC_ICODE_ESNIP_REG								= 3000;
	const u32		_MC_ICODE_IP_REG								= 3001;
	const u32		_MC_ICODE_SP_REG								= 3002;
	const u32		_MC_ICODE_BP_REG								= 3003;
	const u32		_MC_ICODE_READY_REG								= 3004;
	const u32		_MC_ICODE_READY_OFFSET_REG						= 3005;
	const u32		_MC_ICODE_FLAGS_REG								= 3006;
	const u32		_MC_ICODE_PRED_REG								= 3007;
	const u32		_MC_ICODE_PREDCOUNT_REG							= 3008;
	const u32		_MC_ICODE_EXSNIP_REG							= 3009;
	const u32		_MC_ICODE_ERROR_REG								= 3010;

	const u32		_MC_ICODE_DLL									= 125;
	const u32		_MC_ICODE_BXML									= 126;
	const u32		_MC_ICODE_PARAMS								= 127;
	const u32		_MC_ICODE_RETURNS								= 128;
	const u32		_MC_ICODE_DSNIP									= 129;
	const u32		_MC_ICODE_SNIP									= 130;
	const u32		_MC_ICODE_DLL_FUNCTION							= 131;
	const u32		_MC_ICODE_LINE									= 148;
	const u32		_MC_ICODE_COMMENT								= 149;

	const u32		_MC_ICODE_A										= 150;
	const u32		_MC_ICODE_B										= 151;
	const u32		_MC_ICODE_C										= 152;
	const u32		_MC_ICODE_D										= 153;
	const u32		_MC_ICODE_E										= 154;
	const u32		_MC_ICODE_F										= 155;
	const u32		_MC_ICODE_G										= 156;
	const u32		_MC_ICODE_H										= 157;
	const u32		_MC_ICODE_I										= 158;
	const u32		_MC_ICODE_J										= 159;
	const u32		_MC_ICODE_K										= 160;
	const u32		_MC_ICODE_L										= 161;
	const u32		_MC_ICODE_M										= 162;
	const u32		_MC_ICODE_N										= 163;
	const u32		_MC_ICODE_O										= 164;
	const u32		_MC_ICODE_P										= 165;

	const u32		_MC_ICODE_FA									= 166;
	const u32		_MC_ICODE_FB									= 167;
	const u32		_MC_ICODE_FC									= 168;
	const u32		_MC_ICODE_FD									= 169;
	const u32		_MC_ICODE_FE									= 170;
	const u32		_MC_ICODE_FF									= 171;
	const u32		_MC_ICODE_FG									= 172;
	const u32		_MC_ICODE_FH									= 173;
	const u32		_MC_ICODE_FI									= 174;
	const u32		_MC_ICODE_FJ									= 175;
	const u32		_MC_ICODE_FK									= 176;
	const u32		_MC_ICODE_FL									= 177;
	const u32		_MC_ICODE_FM									= 178;
	const u32		_MC_ICODE_FN									= 179;
	const u32		_MC_ICODE_FO									= 180;
	const u32		_MC_ICODE_FP									= 181;

	const u32		_MC_ICODE_RESULT								= 182;
	const u32		_MC_ICODE_RESULT2								= 183;

	// Opcodes are sequential, we use the base of 10,000 for the first one to clearly separate keywords
	const u32		_MC_ICODE_ADD_CMD								= 10000 + 0;
	const u32		_MC_ICODE_SUB_CMD								= 10000 + 1;
	const u32		_MC_ICODE_MUL_CMD								= 10000 + 2;
	const u32		_MC_ICODE_DIV_CMD								= 10000 + 3;
	const u32		_MC_ICODE_COMP_CMD								= 10000 + 4;
	const u32		_MC_ICODE_COPY_CMD								= 10000 + 5;
	const u32		_MC_ICODE_MOVE_CMD								= 10000 + 6;
	const u32		_MC_ICODE_EXCHANGE_CMD							= 10000 + 7;
	const u32		_MC_ICODE_AND_CMD								= 10000 + 8;
	const u32		_MC_ICODE_OR_CMD								= 10000 + 9;
	const u32		_MC_ICODE_NOT_CMD								= 10000 + 10;
	const u32		_MC_ICODE_XOR_CMD								= 10000 + 11;
	const u32		_MC_ICODE_NEG_CMD								= 10000 + 12;
	const u32		_MC_ICODE_INC_CMD								= 10000 + 13;
	const u32		_MC_ICODE_DEC_CMD								= 10000 + 14;
	const u32		_MC_ICODE_SHL_CMD								= 10000 + 15;
	const u32		_MC_ICODE_SHR_CMD								= 10000 + 16;
	const u32		_MC_ICODE_ROL_CMD								= 10000 + 17;
	const u32		_MC_ICODE_ROR_CMD								= 10000 + 18;
	const u32		_MC_ICODE_ADDRESS_CMD							= 10000 + 19;
	const u32		_MC_ICODE_FLAG_CMD								= 10000 + 20;
	const u32		_MC_ICODE_FLAGS_CMD								= 10000 + 21;
	const u32		_MC_ICODE_BUMP_CMD								= 10000 + 22;
	const u32		_MC_ICODE_DEBUG_CMD								= 10000 + 23;
	const u32		_MC_ICODE_SLEEP_CMD								= 10000 + 24;
	const u32		_MC_ICODE_NOP_CMD								= 10000 + 25;
	const u32		_MC_ICODE_EXCEPTION_CMD							= 10000 + 26;
	const u32		_MC_ICODE_JUMP_CMD								= 10000 + 27;
	const u32		_MC_ICODE_CALL_CMD								= 10000 + 28;
	const u32		_MC_ICODE_HOST_CMD								= 10000 + 29;
	const u32		_MC_ICODE_PUSH_CMD								= 10000 + 30;
	const u32		_MC_ICODE_POP_CMD								= 10000 + 31;
	const u32		_MC_ICODE_REGS_CMD								= 10000 + 32;
	const u32		_MC_ICODE_READY_CMD								= 10000 + 33;
	const u32		_MC_ICODE_SET_CMD								= 10000 + 34;
	const u32		_MC_ICODE_GO_CMD								= 10000 + 35;
	const u32		_MC_ICODE_SEMAPHORE_CMD							= 10000 + 36;
	const u32		_MC_ICODE_PRED_CMD_CMD							= 10000 + 37;
	const u32		_MC_ICODE_X86_CMD								= 10000 + 38;
	const u32		_MC_ICODE_ARM_CMD								= 10000 + 39;

	const u32		_MC_ICODE_OUT									= 10000 + 40;
	const u32		_MC_ICODE_IN									= 10000 + 41;
	const u32		_MC_ICODE_SNO									= 10000 + 42;
	const u32		_MC_ICODE_DSNO									= 10000 + 43;
	const u32		_MC_ICODE_HARD									= 10000 + 44;
	const u32		_MC_ICODE_BACK									= 10000 + 45;
	const u32		_MC_ICODE_SET2									= 10000 + 46;
	const u32		_MC_ICODE_CLEAR									= 10000 + 47;
	const u32		_MC_ICODE_TOGGLE								= 10000 + 48;
	const u32		_MC_ICODE_OFFSET								= 10000 + 49;
	const u32		_MC_ICODE_SKIP									= 10000 + 50;
	const u32		_MC_ICODE_IMM64									= 10000 + 51;
	const u32		_MC_ICODE_IMM32									= 10000 + 52;
	const u32		_MC_ICODE_CREATE								= 10000 + 53;
	const u32		_MC_ICODE_TRYLOCK								= 10000 + 54;
	const u32		_MC_ICODE_LOCK									= 10000 + 55;
	const u32		_MC_ICODE_UNLOCK								= 10000 + 56;
	const u32		_MC_ICODE_DELETE								= 10000 + 57;
	const u32		_MC_ICODE_LOAD									= 10000 + 58;
	const u32		_MC_ICODE_FILL									= 10000 + 59;
	const u32		_MC_ICODE_64									= 10000 + 60;
	const u32		_MC_ICODE_32									= 10000 + 61;
	const u32		_MC_ICODE_16									= 10000 + 62;
	const u32		_MC_ICODE_8										= 10000 + 63;
