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
	const u32		_MC_ICODE_PERIOD								= 13;
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
	const u32		_MC_ICODE_DSNIP_DEFINITION						= 102;
	const u32		_MC_ICODE_DSNIP_DLL_DEFINITION					= 103;
	const u32		_MC_ICODE_DSNIP_BXML_DEFINITION					= 104;
	const u32		_MC_ICODE_SNIP_DEFINITION						= 105;
//	const u32		_MC_ICODE_FUNCTION								= 105;	// MAPPED ONTO _VMMC_ICODE_SNIP_DEFINITION
	const u32		_MC_ICODE_DLL_FUNCTION_DEFINITION				= 106;
	const u32		_MC_ICODE_PROTOTYPE								= 107;
	const u32		_MC_ICODE_END									= 108;

	const u32		_MC_ICODE_PARAMS_DEFINITION						= 109;
	const u32		_MC_ICODE_RETURN_DEFINITION						= 110;
	const u32		_MC_ICODE_LOCALS_DEFINITION						= 111;

// TODO:  These values can be refactored into the traditional number range.  They were renumbered to allow BNI and BNF to be added.
	const u32		_MC_LOWEST_ICODE_VARIABLE_DEFINITION			= 1000;
	const u32		_MC_ICODE_U8_DEFINITION							= 1001;
	const u32		_MC_ICODE_U16_DEFINITION						= 1002;
	const u32		_MC_ICODE_U32_DEFINITION						= 1003;
	const u32		_MC_ICODE_U64_DEFINITION						= 1004;
	const u32		_MC_ICODE_S8_DEFINITION							= 1005;
	const u32		_MC_ICODE_S16_DEFINITION						= 1006;
	const u32		_MC_ICODE_S32_DEFINITION						= 1007;
	const u32		_MC_ICODE_S64_DEFINITION						= 1008;
	const u32		_MC_ICODE_F32_DEFINITION						= 1009;
	const u32		_MC_ICODE_F64_DEFINITION						= 1010;
	const u32		_MC_ICODE_BNI_DEFINITION						= 1011;
	const u32		_MC_ICODE_BNF_DEFINITION						= 1012;
	const u32		_MC_HIGHEST_ICODE_VARIABLE_DEFINITION			= 1013;

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

	const u32		_MC_ICODE_SNIP									= 3000;
	const u32		_MC_ICODE_IP									= 3001;
	const u32		_MC_ICODE_SP									= 3002;
	const u32		_MC_ICODE_BP									= 3003;
	const u32		_MC_ICODE_READY									= 3004;
	const u32		_MC_ICODE_READY_OFFSET							= 3005;
	const u32		_MC_ICODE_FLAGS									= 3006;
	const u32		_MC_ICODE_PRED									= 3007;
	const u32		_MC_ICODE_PREDCOUNT								= 3008;
	const u32		_MC_ICODE_EXSNIP								= 3009;
	const u32		_MC_ICODE_ERROR									= 3010;

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
	const u32   _MC_ICODE_UADD64									= 10000 + 0;
	const u32   _MC_ICODE_UADD32									= 10000 + 1;
	const u32   _MC_ICODE_UADD16									= 10000 + 2;
	const u32   _MC_ICODE_UADD8										= 10000 + 3;
	const u32   _MC_ICODE_USUB64									= 10000 + 4;
	const u32   _MC_ICODE_USUB32									= 10000 + 5;
	const u32   _MC_ICODE_USUB16									= 10000 + 6;
	const u32   _MC_ICODE_USUB8										= 10000 + 7;
	const u32   _MC_ICODE_UMUL64									= 10000 + 8;
	const u32   _MC_ICODE_UMUL32									= 10000 + 9;
	const u32   _MC_ICODE_UMUL16                                    = 10000 + 10;
	const u32   _MC_ICODE_UMUL8                                     = 10000 + 11;
	const u32   _MC_ICODE_UDIV64                                    = 10000 + 12;
	const u32   _MC_ICODE_UDIV32                                    = 10000 + 13;
	const u32   _MC_ICODE_UDIV16                                    = 10000 + 14;
	const u32   _MC_ICODE_UDIV8                                     = 10000 + 15;
	const u32   _MC_ICODE_UCOMP64                                   = 10000 + 16;
	const u32   _MC_ICODE_UCOMP32                                   = 10000 + 17;
	const u32   _MC_ICODE_UCOMP16                                   = 10000 + 18;
	const u32   _MC_ICODE_UCOMP8                                    = 10000 + 19;
	const u32   _MC_ICODE_SADDF64                                   = 10000 + 20;
	const u32   _MC_ICODE_SADDF32                                   = 10000 + 21;
	const u32   _MC_ICODE_SADD64                                    = 10000 + 22;
	const u32   _MC_ICODE_SADD32                                    = 10000 + 23;
	const u32   _MC_ICODE_SADD16                                    = 10000 + 24;
	const u32   _MC_ICODE_SADD8                                     = 10000 + 25;
	const u32   _MC_ICODE_SSUBF64                                   = 10000 + 26;
	const u32   _MC_ICODE_SSUBF32                                   = 10000 + 27;
	const u32   _MC_ICODE_SSUB64                                    = 10000 + 28;
	const u32   _MC_ICODE_SSUB32                                    = 10000 + 29;
	const u32   _MC_ICODE_SSUB16                                    = 10000 + 30;
	const u32   _MC_ICODE_SSUB8                                     = 10000 + 31;
	const u32   _MC_ICODE_SMULF64                                   = 10000 + 32;
	const u32   _MC_ICODE_SMULF32                                   = 10000 + 33;
	const u32   _MC_ICODE_SMUL64                                    = 10000 + 34;
	const u32   _MC_ICODE_SMUL32                                    = 10000 + 35;
	const u32   _MC_ICODE_SMUL16                                    = 10000 + 36;
	const u32   _MC_ICODE_SMUL8                                     = 10000 + 37;
	const u32   _MC_ICODE_SDIVF64                                   = 10000 + 38;
	const u32   _MC_ICODE_SDIVF32                                   = 10000 + 39;
	const u32   _MC_ICODE_SDIV64                                    = 10000 + 40;
	const u32   _MC_ICODE_SDIV32                                    = 10000 + 41;
	const u32   _MC_ICODE_SDIV16                                    = 10000 + 42;
	const u32   _MC_ICODE_SDIV8                                     = 10000 + 43;
	const u32   _MC_ICODE_SCOMPF64                                  = 10000 + 44;
	const u32   _MC_ICODE_SCOMPF32                                  = 10000 + 45;
	const u32   _MC_ICODE_SCOMP64                                   = 10000 + 46;
	const u32   _MC_ICODE_SCOMP32                                   = 10000 + 47;
	const u32   _MC_ICODE_SCOMP16                                   = 10000 + 48;
	const u32   _MC_ICODE_SCOMP8                                    = 10000 + 49;
	const u32   _MC_ICODE_COPYF64                                   = 10000 + 50;
	const u32   _MC_ICODE_COPYF32                                   = 10000 + 51;
	const u32   _MC_ICODE_COPY64                                    = 10000 + 52;
	const u32   _MC_ICODE_COPY32                                    = 10000 + 53;
	const u32   _MC_ICODE_COPY16                                    = 10000 + 54;
	const u32   _MC_ICODE_COPY8                                     = 10000 + 55;
	const u32   _MC_ICODE_COPY8X                                    = 10000 + 56;
	const u32   _MC_ICODE_MOVEF64                                   = 10000 + 57;
	const u32   _MC_ICODE_MOVEF32                                   = 10000 + 58;
	const u32   _MC_ICODE_MOVE64                                    = 10000 + 59;
	const u32   _MC_ICODE_MOVE32                                    = 10000 + 60;
	const u32   _MC_ICODE_MOVE16                                    = 10000 + 61;
	const u32   _MC_ICODE_MOVE8                                     = 10000 + 62;
	const u32   _MC_ICODE_XCHF64                                    = 10000 + 63;
	const u32   _MC_ICODE_XCHF32                                    = 10000 + 64;
	const u32   _MC_ICODE_XCH64                                     = 10000 + 65;
	const u32   _MC_ICODE_XCH32                                     = 10000 + 66;
	const u32   _MC_ICODE_XCH16                                     = 10000 + 67;
	const u32   _MC_ICODE_XCH8                                      = 10000 + 68;
	const u32   _MC_ICODE_XCHUADD64                                 = 10000 + 69;
	const u32   _MC_ICODE_XCHUADD32                                 = 10000 + 70;
	const u32   _MC_ICODE_XCHUADD16                                 = 10000 + 71;
	const u32   _MC_ICODE_XCHUADD8                                  = 10000 + 72;
	const u32   _MC_ICODE_XCHUMUL64                                 = 10000 + 73;
	const u32   _MC_ICODE_XCHUMUL32                                 = 10000 + 74;
	const u32   _MC_ICODE_XCHUMUL16                                 = 10000 + 75;
	const u32   _MC_ICODE_XCHUMUL8                                  = 10000 + 76;
	const u32   _MC_ICODE_XCHSADDF64                                = 10000 + 77;
	const u32   _MC_ICODE_XCHSADDF32                                = 10000 + 78;
	const u32   _MC_ICODE_XCHSADD64                                 = 10000 + 79;
	const u32   _MC_ICODE_XCHSADD32                                 = 10000 + 80;
	const u32   _MC_ICODE_XCHSADD16                                 = 10000 + 81;
	const u32   _MC_ICODE_XCHSADD8                                  = 10000 + 82;
	const u32   _MC_ICODE_XCHSMULF64                                = 10000 + 83;
	const u32   _MC_ICODE_XCHSMULF32                                = 10000 + 84;
	const u32   _MC_ICODE_XCHSMUL64                                 = 10000 + 85;
	const u32   _MC_ICODE_XCHSMUL32                                 = 10000 + 86;
	const u32   _MC_ICODE_XCHSMUL16                                 = 10000 + 87;
	const u32   _MC_ICODE_XCHSMUL8                                  = 10000 + 88;
	const u32   _MC_ICODE_AND64                                     = 10000 + 89;
	const u32   _MC_ICODE_AND32                                     = 10000 + 90;
	const u32   _MC_ICODE_AND16                                     = 10000 + 91;
	const u32   _MC_ICODE_AND8                                      = 10000 + 92;
	const u32   _MC_ICODE_OR64                                      = 10000 + 93;
	const u32   _MC_ICODE_OR32                                      = 10000 + 94;
	const u32   _MC_ICODE_OR16                                      = 10000 + 95;
	const u32   _MC_ICODE_OR8                                       = 10000 + 96;
	const u32   _MC_ICODE_NOT64                                     = 10000 + 97;
	const u32   _MC_ICODE_NOT32                                     = 10000 + 98;
	const u32   _MC_ICODE_NOT16                                     = 10000 + 99;
	const u32   _MC_ICODE_NOT8                                      = 10000 + 100;
	const u32   _MC_ICODE_XOR64                                     = 10000 + 101;
	const u32   _MC_ICODE_XOR32                                     = 10000 + 102;
	const u32   _MC_ICODE_XOR16                                     = 10000 + 103;
	const u32   _MC_ICODE_XOR8                                      = 10000 + 104;
	const u32   _MC_ICODE_CHGSF64                                   = 10000 + 105;
	const u32   _MC_ICODE_CHGSF32                                   = 10000 + 106;
	const u32   _MC_ICODE_NEG64                                     = 10000 + 107;
	const u32   _MC_ICODE_NEG32                                     = 10000 + 108;
	const u32   _MC_ICODE_NEG16                                     = 10000 + 109;
	const u32   _MC_ICODE_NEG8                                      = 10000 + 110;
	const u32   _MC_ICODE_INCF64                                    = 10000 + 111;
	const u32   _MC_ICODE_INCF32                                    = 10000 + 112;
	const u32   _MC_ICODE_INC64                                     = 10000 + 113;
	const u32   _MC_ICODE_INC32                                     = 10000 + 114;
	const u32   _MC_ICODE_INC16                                     = 10000 + 115;
	const u32   _MC_ICODE_INC8                                      = 10000 + 116;
	const u32   _MC_ICODE_DECF64                                    = 10000 + 117;
	const u32   _MC_ICODE_DECF32                                    = 10000 + 118;
	const u32   _MC_ICODE_DEC64                                     = 10000 + 119;
	const u32   _MC_ICODE_DEC32                                     = 10000 + 120;
	const u32   _MC_ICODE_DEC16                                     = 10000 + 121;
	const u32   _MC_ICODE_DEC8                                      = 10000 + 122;
	const u32   _MC_ICODE_SHL64                                     = 10000 + 123;
	const u32   _MC_ICODE_SHL32                                     = 10000 + 124;
	const u32   _MC_ICODE_SHL16                                     = 10000 + 125;
	const u32   _MC_ICODE_SHL8                                      = 10000 + 126;
	const u32   _MC_ICODE_SHRU64                                    = 10000 + 127;
	const u32   _MC_ICODE_SHRU32                                    = 10000 + 128;
	const u32   _MC_ICODE_SHRU16                                    = 10000 + 129;
	const u32   _MC_ICODE_SHRU8                                     = 10000 + 130;
	const u32   _MC_ICODE_SHRS64                                    = 10000 + 131;
	const u32   _MC_ICODE_SHRS32                                    = 10000 + 132;
	const u32   _MC_ICODE_SHRS16                                    = 10000 + 133;
	const u32   _MC_ICODE_SHRS8                                     = 10000 + 134;
	const u32   _MC_ICODE_ROL64                                     = 10000 + 135;
	const u32   _MC_ICODE_ROL32                                     = 10000 + 136;
	const u32   _MC_ICODE_ROL16                                     = 10000 + 137;
	const u32   _MC_ICODE_ROL8                                      = 10000 + 138;
	const u32   _MC_ICODE_ROR64                                     = 10000 + 139;
	const u32   _MC_ICODE_ROR32                                     = 10000 + 140;
	const u32   _MC_ICODE_ROR16                                     = 10000 + 141;
	const u32   _MC_ICODE_ROR8                                      = 10000 + 142;
	const u32   _MC_ICODE_CNVOBJ                                    = 10000 + 143;
	const u32   _MC_ICODE_COPYF32I32                                = 10000 + 144;
	const u32   _MC_ICODE_COPYI32F32                                = 10000 + 145;
	const u32   _MC_ICODE_COPYF64I64                                = 10000 + 146;
	const u32   _MC_ICODE_COPYI64F64                                = 10000 + 147;
	const u32   _MC_ICODE_COPYF32I64                                = 10000 + 148;
	const u32   _MC_ICODE_COPYI32F64                                = 10000 + 149;
	const u32   _MC_ICODE_COPYF64I32                                = 10000 + 150;
	const u32   _MC_ICODE_COPYI64F32                                = 10000 + 151;
	const u32   _MC_ICODE_COPYF264                                  = 10000 + 152;
	const u32   _MC_ICODE_COPY642F                                  = 10000 + 153;
	const u32   _MC_ICODE_COPY                                      = 10000 + 154;
	const u32   _MC_ICODE_ALLOCS                                    = 10000 + 155;
	const u32   _MC_ICODE_DEALLOCS                                  = 10000 + 156;
	const u32   _MC_ICODE_DEBUG                                     = 10000 + 157;
	const u32   _MC_ICODE_HALT                                      = 10000 + 158;
	const u32   _MC_ICODE_NOP                                       = 10000 + 159;
	const u32   _MC_ICODE_LENOBJ                                    = 10000 + 160;
	const u32   _MC_ICODE_NUMOBJA                                   = 10000 + 161;
	const u32   _MC_ICODE_NUMOBJU                                   = 10000 + 162;
	const u32   _MC_ICODE_NUA                                       = 10000 + 163;
	const u32   _MC_ICODE_NUN                                       = 10000 + 164;
	const u32   _MC_ICODE_SETIPS                                    = 10000 + 165;
	const u32   _MC_ICODE_SETIP                                     = 10000 + 166;
	const u32   _MC_ICODE_ADJIP64                                   = 10000 + 167;
	const u32   _MC_ICODE_ADJIP32                                   = 10000 + 168;
	const u32   _MC_ICODE_ADJIP16                                   = 10000 + 169;
	const u32   _MC_ICODE_ADJIP8                                    = 10000 + 170;
	const u32   _MC_ICODE_CALLSN                                    = 10000 + 171;
	const u32   _MC_ICODE_CALLSNA                                   = 10000 + 172;
	const u32   _MC_ICODE_CALLSNU                                   = 10000 + 173;
	const u32   _MC_ICODE_CALLDSN                                   = 10000 + 174;
	const u32   _MC_ICODE_CALLDSNA                                  = 10000 + 175;
	const u32   _MC_ICODE_CALLDSNU                                  = 10000 + 176;
	const u32   _MC_ICODE_CALLHN                                    = 10000 + 177;
	const u32   _MC_ICODE_CALLHNA                                   = 10000 + 178;
	const u32   _MC_ICODE_PUSH64                                    = 10000 + 179;
	const u32   _MC_ICODE_POP64                                     = 10000 + 180;
	const u32   _MC_ICODE_PUSH32                                    = 10000 + 181;
	const u32   _MC_ICODE_POP32                                     = 10000 + 182;
	const u32   _MC_ICODE_STACKCPY32                                = 10000 + 183;
	const u32   _MC_ICODE_RETURN                                    = 10000 + 184;
	const u32   _MC_ICODE_RETTONAM                                  = 10000 + 185;
	const u32   _MC_ICODE_RETTONUM                                  = 10000 + 186;
	const u32   _MC_ICODE_SFLAG                                     = 10000 + 187;
	const u32   _MC_ICODE_CFLAG                                     = 10000 + 188;
	const u32   _MC_ICODE_TFLAG                                     = 10000 + 189;
	const u32   _MC_ICODE_INFLAG                                    = 10000 + 190;
	const u32   _MC_ICODE_OUTFLAG                                   = 10000 + 191;
	const u32   _MC_ICODE_SETC                                      = 10000 + 192;
	const u32   _MC_ICODE_SETO                                      = 10000 + 193;
	const u32   _MC_ICODE_SETU                                      = 10000 + 194;
	const u32   _MC_ICODE_SETE                                      = 10000 + 195;
	const u32   _MC_ICODE_SETZ                                      = 10000 + 196;
	const u32   _MC_ICODE_SETN                                      = 10000 + 197;
	const u32   _MC_ICODE_SETP                                      = 10000 + 198;
	const u32   _MC_ICODE_SETA                                      = 10000 + 199;
	const u32   _MC_ICODE_SETAN                                     = 10000 + 200;
	const u32   _MC_ICODE_CLRA                                      = 10000 + 201;
	const u32   _MC_ICODE_TOGA                                      = 10000 + 202;
	const u32   _MC_ICODE_LOADTHEME                                 = 10000 + 203;
	const u32   _MC_ICODE_RENDERSTART                               = 10000 + 204;
	const u32   _MC_ICODE_RENDERREGION                              = 10000 + 205;
	const u32   _MC_ICODE_RENDERCANVAS                              = 10000 + 206;
	const u32   _MC_ICODE_RENDERSCREEN                              = 10000 + 207;
	const u32   _MC_ICODE_RENDERSTOP                                = 10000 + 208;
	const u32   _MC_ICODE_APPOAPA                                   = 10000 + 209;
	const u32   _MC_ICODE_APPOACH                                   = 10000 + 210;
	const u32   _MC_ICODE_APPOAPR                                   = 10000 + 211;
	const u32   _MC_ICODE_APPOANE                                   = 10000 + 212;
	const u32   _MC_ICODE_DELOFO                                    = 10000 + 213;
	const u32   _MC_ICODE_DESTROY                                   = 10000 + 214;
	const u32   _MC_ICODE_ISCATTER                                  = 10000 + 215;
	const u32   _MC_ICODE_IGATHER                                   = 10000 + 216;
	const u32   _MC_ICODE_FSCATTER                                  = 10000 + 217;
	const u32   _MC_ICODE_FGATHER                                   = 10000 + 218;
	const u32   _MC_ICODE_TMRADDG                                   = 10000 + 219;
	const u32   _MC_ICODE_TMRDELG                                   = 10000 + 220;
	const u32   _MC_ICODE_TMRENAG                                   = 10000 + 221;
	const u32   _MC_ICODE_TMRDISG                                   = 10000 + 222;
	const u32   _MC_ICODE_TMRADDT                                   = 10000 + 223;
	const u32   _MC_ICODE_TMRDELT                                   = 10000 + 224;
	const u32   _MC_ICODE_TMRENAT                                   = 10000 + 225;
	const u32   _MC_ICODE_TMRDIST                                   = 10000 + 226;
	const u32   _MC_ICODE_PASSIVE                                   = 10000 + 227;
	const u32   _MC_ICODE_ACTIVE                                    = 10000 + 228;
	const u32   _MC_ICODE_SETEXS                                    = 10000 + 229;
	const u32   _MC_ICODE_EXCEPS                                    = 10000 + 230;
	const u32   _MC_ICODE_THRAP                                     = 10000 + 231;
	const u32   _MC_ICODE_THRAPS                                    = 10000 + 232;
	const u32   _MC_ICODE_THRAS                                     = 10000 + 233;
	const u32   _MC_ICODE_THRAF                                     = 10000 + 234;
	const u32   _MC_ICODE_THRST                                     = 10000 + 235;
	const u32   _MC_ICODE_THRSP                                     = 10000 + 236;
	const u32   _MC_ICODE_THRXT                                     = 10000 + 237;
	const u32   _MC_ICODE_THRXP                                     = 10000 + 238;
	const u32   _MC_ICODE_THRXR                                     = 10000 + 239;
	const u32   _MC_ICODE_THRXRS                                    = 10000 + 240;
	const u32   _MC_ICODE_THRXJ                                     = 10000 + 241;
	const u32   _MC_ICODE_SCREATE                                   = 10000 + 242;
	const u32   _MC_ICODE_SLOCK                                     = 10000 + 243;
	const u32   _MC_ICODE_SUNLOCK                                   = 10000 + 244;
	const u32   _MC_ICODE_SDELETE                                   = 10000 + 245;
	const u32   _MC_ICODE_PREDICATE                                 = 10000 + 246;
	const u32   _MC_ICODE_COPYPRED                                  = 10000 + 247;
//	const u32   _MC_ICODE_UNUSED                                    = 10000 + 248;
//	const u32   _MC_ICODE_UNUSED                                    = 10000 + 249;
//	const u32   _MC_ICODE_UNUSED                                    = 10000 + 250;
//	const u32   _MC_ICODE_UNUSED                                    = 10000 + 251;
//	const u32   _MC_ICODE_UNUSED                                    = 10000 + 252;
//	const u32   _MC_ICODE_UNUSED                                    = 10000 + 253;
//	const u32   _MC_ICODE_UNUSED                                    = 10000 + 254;
//	const u32   _MC_ICODE_EXTENDED                                  = 10000 + 255;

