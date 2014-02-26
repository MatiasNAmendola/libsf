//////////
//
// /libsf/vvm/vvm/vvm_globals.h
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
//     Nov.07.2012 - 0.60 development begins
//     Sep.29.2012 - PBL v1.0 license included directly in source files.
//     Sep.21.2012 - Initial creation
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
// Global variables used by VVM
//////
	_isSVvmApp		gsVvm;
	SSysInfo		gsVvmSysInfo;				// Populated during ivvmtm_initialize(), holds system information

	// BXML last error
	u64					gnLastErrorOffset		= -1;					// Initially indicate no prior error offset
	u64					gnLastErrorCode			= 0;					// Initially indicate no prior error code
	SBxmlError			gsLastErrorInfo =	{
												{ NULL, 0 },			// Description (initially set to no error)
												0,						// Last error offset
												0,						// Last error code
												NULL,					// Last BXML in error
												NULL					// Last BxmlA in error
											};


//////////
// Critical sections for synchronized access
//////
	u64					gnNextUniqueId			= 1000;					// Increments after each reference (see vvm_getNextUniqueId() and iGetNextUniqueId())
	CRITICAL_SECTION	gcsUniqueIdAccess;								// Next Unique ID access
	

//////////
// Data specifically related to the VVM test suites
//////
	_isSVvmTests	gsVvmTest;


//////////
// Used by vvm_eng.cpp, the opcode decoding engine
//////
	u32 gnVvmMachineOpodeHandlers[256] =
	{
		// Unsigned adds
		(u32)&ivvme_executeThreadSnippet_uadd64,					// UADD64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_uadd32,					// UADD32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_uadd16,					// UADD16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_uadd8,						// UADD8 [SOURCE] TO [SOURCE]

		// Unsigned subtracts
		(u32)&ivvme_executeThreadSnippet_usub64,					// USUB64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_usub32,					// USUB32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_usub16,					// USUB16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_usub8,						// USUB8 [SOURCE] TO [SOURCE]

		// Unsigned multiplies
		(u32)&ivvme_executeThreadSnippet_umul64,					// UMUL64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_umul32,					// UMUL32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_umul16,					// UMUL16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_umul8,						// UMUL8 [SOURCE] TO [SOURCE]

		// Unsigned divides
		(u32)&ivvme_executeThreadSnippet_udiv64,					// UDIV64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_udiv32,					// UDIV32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_udiv16,					// UDIV16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_udiv8,						// UDIV8 [SOURCE] TO [SOURCE]

		// Unsigned compares
		(u32)&ivvme_executeThreadSnippet_ucomp64,					// UCOMP64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_ucomp32,					// UCOMP32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_ucomp16,					// UCOMP16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_ucomp8,					// UCOMP8 [SOURCE] TO [SOURCE]

		// Signed adds
		(u32)&ivvme_executeThreadSnippet_saddf64,					// SADDF64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_saddf32,					// SADDF32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_sadd64,					// SADD64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_sadd32,					// SADD32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_sadd16,					// SADD16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_sadd8,						// SADD8 [SOURCE] TO [SOURCE]

		// Signed subtracts
		(u32)&ivvme_executeThreadSnippet_ssubf64,					// SSUBF64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_ssubf32,					// SSUBF32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_ssub64,					// SSUB64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_ssub32,					// SSUB32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_ssub16,					// SSUB16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_ssub8,						// SSUB8 [SOURCE] TO [SOURCE]

		// Signed multiplies
		(u32)&ivvme_executeThreadSnippet_smulf64,					// SMULF64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_smulf32,					// SMULF32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_smul64,					// SMUL64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_smul32,					// SMUL32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_smul16,					// SMUL16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_smul8,						// SMUL8 [SOURCE] TO [SOURCE]

		// Signed divides
		(u32)&ivvme_executeThreadSnippet_sdivf64,					// SDIVF64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_sdivf32,					// SDIVF32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_sdiv64,					// SDIV64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_sdiv32,					// SDIV32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_sdiv16,					// SDIV16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_sdiv8,						// SDIV8 [SOURCE] TO [SOURCE]

		// Signed compares
		(u32)&ivvme_executeThreadSnippet_scompf64,					// SCOMPF64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_scompf32,					// SCOMPF32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_scomp64,					// SCOMP64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_scomp32,					// SCOMP32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_scomp16,					// SCOMP16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_scomp8,					// SCOMP8 [SOURCE] TO [SOURCE]

		// Copy value to value
		(u32)&ivvme_executeThreadSnippet_copyf64,					// COPYF64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_copyf32,					// COPYF32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_copy64,					// COPY64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_copy32,					// COPY32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_copy16,					// COPY16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_copy8,						// COPY8 [SOURCE] TO [SOURCE]

		// Move value to value, 0 to source
		(u32)&ivvme_executeThreadSnippet_movef64,					// MOVEF64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_movef32,					// MOVEF32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_move64,					// MOVE64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_move32,					// MOVE32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_move16,					// MOVE16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_move8,						// MOVE8 [SOURCE] TO [SOURCE]

		// Exchange value for value
		(u32)&ivvme_executeThreadSnippet_xchf64,					// XCHF64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchf32,					// XCHF32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xch64,						// XCH64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xch32,						// XCH32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xch16,						// XCH16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xch8,						// XCH8 [SOURCE] TO [SOURCE]

		// Unsigned add, then exchange value for value
		(u32)&ivvme_executeThreadSnippet_xchuadd64,					// XCHUADD64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchuadd32,					// XCHUADD32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchuadd16,					// XCHUADD16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchuadd8,					// XCHUADD8 [SOURCE] TO [SOURCE]

		// Unsigned multiply, then exchange value for value
		(u32)&ivvme_executeThreadSnippet_xchumul64,					// XCHUMUL64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchumul32,					// XCHUMUL32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchumul16,					// XCHUMUL16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchumul8,					// XCHUMUL8 [SOURCE] TO [SOURCE]

		// Signed add, then exchange value for value
		(u32)&ivvme_executeThreadSnippet_xchsaddf64,				// XCHSADDF64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchsaddf32,				// XCHSADDF32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchsadd64,					// XCHSADD64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchsadd32,					// XCHSADD32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchsadd16,					// XCHSADD16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchsadd8,					// XCHSADD8 [SOURCE] TO [SOURCE]

		// Signed multiply, then exchange value for value
		(u32)&ivvme_executeThreadSnippet_xchsmulf64,				// XCHSMULF64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchsmulf32,				// XCHSMULF32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchsmul64,					// XCHSMUL64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchsmul32,					// XCHSMUL32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchsmul16,					// XCHSMUL16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xchsmul8,					// XCHSMUL8 [SOURCE] TO [SOURCE]

		// Bitwise AND
		(u32)&ivvme_executeThreadSnippet_and64,						// AND64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_and32,						// AND32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_and16,						// AND16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_and8,						// AND8 [SOURCE] TO [SOURCE]

		// Bitwise OR
		(u32)&ivvme_executeThreadSnippet_or64,						// OR64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_or32,						// OR32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_or16,						// OR16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_or8,						// OR8 [SOURCE] TO [SOURCE]

		// Bitwise NOT
		(u32)&ivvme_executeThreadSnippet_not64,						// NOT64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_not32,						// NOT32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_not16,						// NOT16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_not8,						// NOT8 [SOURCE] TO [SOURCE]

		// Bitwise XOR
		(u32)&ivvme_executeThreadSnippet_xor64,						// XOR64 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xor32,						// XOR32 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xor16,						// XOR16 [SOURCE] TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_xor8,						// XOR8 [SOURCE] TO [SOURCE]

		// Floating point change sign
		(u32)&ivvme_executeThreadSnippet_chgsf64,					// CHGSF64 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_chgsf32,					// CHGSF32 [SOURCE]

		// Negate
		(u32)&ivvme_executeThreadSnippet_neg64,						// NEG64 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_neg32,						// NEG32 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_neg16,						// NEG16 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_neg8,						// NEG8 [SOURCE]

		// Increment
		(u32)&ivvme_executeThreadSnippet_incf64,					// INCF64 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_incf32,					// INCF32 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_inc64,						// INC64 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_inc32,						// INC32 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_inc16,						// INC16 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_inc8,						// INC8 [SOURCE]

		// Decrement
		(u32)&ivvme_executeThreadSnippet_decf64,					// DECF64 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_decf32,					// DECF32 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_dec64,						// DEC64 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_dec32,						// DEC32 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_dec16,						// DEC16 [SOURCE]
		(u32)&ivvme_executeThreadSnippet_dec8,						// DEC8 [SOURCE]

		// Shift left
		(u32)&ivvme_executeThreadSnippet_shl64,						// SHL64 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_shl32,						// SHL32 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_shl16,						// SHL16 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_shl8,						// SHL8 [SOURCE] BY [SOURCE]

		// Shift right unsigned
		(u32)&ivvme_executeThreadSnippet_shur64,					// SHUR64 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_shur32,					// SHUR32 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_shur16,					// SHUR16 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_shur8,						// SHUR8 [SOURCE] BY [SOURCE]

		// Shift right signed
		(u32)&ivvme_executeThreadSnippet_shsr64,					// SHSR64 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_shsr32,					// SHSR32 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_shsr16,					// SHSR16 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_shsr8,						// SHSR8 [SOURCE] BY [SOURCE]

		// Rotate left
		(u32)&ivvme_executeThreadSnippet_rol64,						// ROL64 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_rol32,						// ROL32 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_rol16,						// ROL16 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_rol8,						// ROL8 [SOURCE] BY [SOURCE]

		// Rotate right
		(u32)&ivvme_executeThreadSnippet_ror64,						// ROR64 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_ror32,						// ROR32 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_ror16,						// ROR16 [SOURCE] BY [SOURCE]
		(u32)&ivvme_executeThreadSnippet_ror8,						// ROR8 [SOURCE] BY [SOURCE]

		// Convert object to VVM type
		(u32)&ivvme_executeThreadSnippet_cnvobj,					// CNVOBJ [REG] TO VVM TYPE [IMM8]	; TAKES OBJECT TYPE AND CONVERTS TO THE NEW FORMAT SUPPORTED BY THE VVM

		// Copy floating point to integer, or integer to floating point
		(u32)&ivvme_executeThreadSnippet_copy3232fi,				// COPY3232 [FREG32] TO [REG32]
		(u32)&ivvme_executeThreadSnippet_copy3232if,				// COPY3232 [REG32] TO [FREG32]
		(u32)&ivvme_executeThreadSnippet_copy6464fi,				// COPY6464 [FREG64] TO [REG64]
		(u32)&ivvme_executeThreadSnippet_copy6464if,				// COPY6464 [REG64] TO [FREG64]

		// Copy floating point to integer, or integer to floating point, and upsize or downsize
		(u32)&ivvme_executeThreadSnippet_copy3264fi,				// COPY3264 [FREG32] TO [REG64]
		(u32)&ivvme_executeThreadSnippet_copy3264if,				// COPY3264 [REG32] TO [FREG64]
		(u32)&ivvme_executeThreadSnippet_copy6432fi,				// COPY6432 [FREG64] TO [REG32]
		(u32)&ivvme_executeThreadSnippet_copy6432if,				// COPY6432 [REG64] TO [FREG32]

		// Copy flags to source, source to flags, or result to source
		(u32)&ivvme_executeThreadSnippet_copy64fs,					// COPY64 FLAGS TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_copy64sf,					// COPY64 [SOURCE] TO FLAGS
		(u32)&ivvme_executeThreadSnippet_copyresult,				// COPY RESULT64 TO [SOURCE]

		// Scratch space allocate or deallocate
		(u32)&ivvme_executeThreadSnippet_allocs,					// ALLOCS [IMM8]					; ALLOCATE SCRATCH SPACE
		(u32)&ivvme_executeThreadSnippet_deallocs,					// DEALLOCS [IMM8]					; DEALLOCATE SCRATCH SPACE

		// Debugger commands
		(u32)&ivvme_executeThreadSnippet_debug,						// DEBUG							; PAUSES FOR DEBUGGER
		(u32)&ivvme_executeThreadSnippet_halt,						// HALT								; HALTS TIMESLICE EXECUTION UNTIL NEXT SCHEDULING
		(u32)&ivvme_executeThreadSnippet_nop,						// NOP								; USED FOR PADDING

		(u32)&ivvme_executeThreadSnippet_lenobj,					// LENOBJ							; LENGTH OF OBJECT NUMBER
		(u32)&ivvme_executeThreadSnippet_numobja,					// NUMOBJA							; NUMBER OF OBJECT ASCII NAME
		(u32)&ivvme_executeThreadSnippet_numobju,					// NUMOBJU							; NUMBER OF OBJECT UNICODE NAME
		(u32)&ivvme_executeThreadSnippet_nua,						// NUA								; NEXT UNIQUE NAME
		(u32)&ivvme_executeThreadSnippet_nun,						// NUN								; NEXT UNIQUE NUMBER

		(u32)&ivvme_executeThreadSnippet_setipxs,					// SETIPXS TO [SNIPPET SOURCE] + [OFFSET SOURCE]	; EXPLICIT ADDRESS FROM [SNIPPET NUMBER]'S OFFSET 0
		(u32)&ivvme_executeThreadSnippet_setipx,					// SETIPX TO [OFFSET SOURCE]		; EXPLICIT ADDRESS FROM CURRENT SNIPPET'S OFFSET 0
		(u32)&ivvme_executeThreadSnippet_adjip64,					// ADJIP64 [SOURCE]					; ADJUST IP FORWARD/BACKWARD BY SIGNED [SOURCE]
		(u32)&ivvme_executeThreadSnippet_adjip32,					// ADJIP32 [SOURCE]					; ADJUST IP FORWARD/BACKWARD BY SIGNED [SOURCE]
		(u32)&ivvme_executeThreadSnippet_adjip16,					// ADJIP16 [IMM16]					; ADJUST IP FORWARD/BACKWARD BY SIGNED [IMM16]
		(u32)&ivvme_executeThreadSnippet_adjip8,					// ADJIP8 [IMM8]					; ADJUST IP FORWARD BACKWARD BY SIGNED [IMM8]

		(u32)&ivvme_executeThreadSnippet_callsn,					// CALLSN [SOURCE]					; CALL SNIPPET NUMBER
		(u32)&ivvme_executeThreadSnippet_callsna,					// CALLSNA [SOURCE]					; CALL SNIPPET NAME ASCII
		(u32)&ivvme_executeThreadSnippet_callsnu,					// CALLSNU [SOURCE]					; CALL SNIPPET NAME UNICODE
		(u32)&ivvme_executeThreadSnippet_callsdn,					// CALLDSN [SOURCE]					; CALL DYNAMIC SNIPPET NUMBER
		(u32)&ivvme_executeThreadSnippet_calldsna,					// CALLDSNA [SOURCE]				; CALL DYNAMIC SNIPPET NAME ASCII
		(u32)&ivvme_executeThreadSnippet_calldsnu,					// CALLDSNU [SOURCE]				; CALL DYNAMIC SNIPPET NAME UNICODE
		(u32)&ivvme_executeThreadSnippet_callhn,					// CALLHN [SOURCE]					; CALL HOST NUMBER
		(u32)&ivvme_executeThreadSnippet_callhna,					// CALLHNA [SOURCE]					; CALL HOST NAME ASCII (ALL HOST FUNCTIONS ARE ONLY ASCII)

		(u32)&ivvme_executeThreadSnippet_push64,					// PUSH64 [SOURCE]					; PUSHES 64-BIT QUANTITY ONTO STACK FROM SOURCE
		(u32)&ivvme_executeThreadSnippet_pop64,						// POP64 [SOURCE]					; POPS 64-BIT QUANTITY BACK OFF STACK INTO SOURCE
		(u32)&ivvme_executeThreadSnippet_push32,					// PUSH32 [SOURCE]					; PUSHES 32-BIT QUANTITY ONTO STACK FROM SOURCE
		(u32)&ivvme_executeThreadSnippet_pop32,						// POP32 [SOURCE]					; POPS 32-BIT QUANTITY BACK OFF STACK INTO SOURCE
		(u32)&ivvme_executeThreadSnippet_stackcpy32,				// STACKCPY32 [SOURCE][LENGTH][SOURCE]	; COPY STACK [SOURCE] [LENGTH IN DWORDS] TO [DESTINATION]

		(u32)&ivvme_executeThreadSnippet_return,					// RETURN							; EXPLICIT RETURN TO IMMEDIATE PARENT, IF AT TOP LEVEL, TERMINATES PROGRAM
		(u32)&ivvme_executeThreadSnippet_rettonam,					// RETTONAM [SOURCE]				; RETURN TO SNIPPET NAME IN PARENT LINEAGE
		(u32)&ivvme_executeThreadSnippet_rettonum,					// RETTONUM [SOURCE]				; RETURN TO SNIPPET NUMBER IN PARENT LINEAGE

		(u32)&ivvme_executeThreadSnippet_sflag,						// SFLAG [IMM8]						; SET FLAG BITS
		(u32)&ivvme_executeThreadSnippet_cflag,						// CFLAG [IMM8]						; CLEAR FLAG BITS
		(u32)&ivvme_executeThreadSnippet_tflag,						// TFLAG [IMM8]						; TOGGLE FLAG BITS
		(u32)&ivvme_executeThreadSnippet_inflag,					// INFLAG [SOURCE]					; COPY [SOURCE] TO FLAGS
		(u32)&ivvme_executeThreadSnippet_outflag,					// OUTFLAG [SOURCE]					; COPY FLAGS TO [SOURCE]
		(u32)&ivvme_executeThreadSnippet_setc,						// SETC								; SET CARRY? FLAG
		(u32)&ivvme_executeThreadSnippet_seto,						// SETO								; SET OVERFLOW? FLAG
		(u32)&ivvme_executeThreadSnippet_setu,						// SETU								; SET UNDERFLOW? FLAG
		(u32)&ivvme_executeThreadSnippet_sete,						// SETE								; SET EQUAL? FLAG
		(u32)&ivvme_executeThreadSnippet_setz,						// SETZ								; SET ZERO? FLAG
		(u32)&ivvme_executeThreadSnippet_setn,						// SETN								; SET NEGATIVE? FLAG
		(u32)&ivvme_executeThreadSnippet_setp,						// SETP								; SET POSITIVE? FLAG
		(u32)&ivvme_executeThreadSnippet_seta,						// SETA								; SET APP? FLAG
		(u32)&ivvme_executeThreadSnippet_setan,						// SETAN [IMM4]						; SET APPn? FLAG
		(u32)&ivvme_executeThreadSnippet_clran,						// CLRAN [IMM4]						; CLEAR APPn? FLAG
		(u32)&ivvme_executeThreadSnippet_togan,						// TOGAN [IMM4]						; MOVE APPn? IN TO APP? FLAG

		(u32)&ivvme_executeThreadSnippet_loadtheme,					// LOADTHEME [SOURCE]				; ASCII NAME OF THE THEME TO LOAD
		(u32)&ivvme_executeThreadSnippet_renderstart,				// RENDERSTART [SOURCE]				; SIGNAL TO THE VVM THAT RENDER UPDATES ARE BEGINNING USING [THEME]
		(u32)&ivvme_executeThreadSnippet_rendrregion,				// RENDERREGION [SOURCE] [SOURCE] [SOURCE]	; RENDER THE INDICATED [SCREEN], [CANVAS] AND [REGION] USING VIA HOST DEFAULT
		(u32)&ivvme_executeThreadSnippet_rendercanvas,				// RENDERCANVAS [SOURCE]			; RENDER THE INDICATED [CANVAS] (DRAWS ALL CHILD CANVASES ONTO IT)
		(u32)&ivvme_executeThreadSnippet_renderscreen,				// RENDERSCREEN [SOURCE]			; RENDER THE INDICATED [SCREEN] (DRAWS ALL CHILD CANVASES ONTO IT)
		(u32)&ivvme_executeThreadSnippet_renderstop,				// RENDERSTOP						; SIGNAL VVM RENDER UPDATES ARE COMPLETE

		(u32)&ivvme_executeThreadSnippet_appoapa,					// APPOAPA [SOURCE] TO [SOURCE]		; APPEND OBJECT [REG] TO OBJECT [REG] AS PARENT
		(u32)&ivvme_executeThreadSnippet_appoach,					// APPOACH [SOURCE] TO [SOURCE]		; APPEND OBJECT [REG] TO OBJECT [REG] AS CHILD
		(u32)&ivvme_executeThreadSnippet_appoapr,					// APPOAPR [SOURCE] TO [SOURCE]		; APPEND OBJECT [REG] TO OBJECT [REG] AS PREV
		(u32)&ivvme_executeThreadSnippet_appoane,					// APPOANE [SOURCE] TO [SOURCE]		; APPEND OBJECT [REG] TO OBJECT [REG] AS NEXT
		(u32)&ivvme_executeThreadSnippet_delofo,					// DELOFO [SOURCE] FROM [SOURCE]	; DELETE/PRUNE [REG] FROM OBJECT [REG] (STILL EXISTS AS INSTANCE OBJECT, AND POSSIBLY ON OTHER PARENTS)
		(u32)&ivvme_executeThreadSnippet_destroy,					// DESTROY [SOURCE]					; DESTROY OBJECT

		(u32)&ivvme_executeThreadSnippet_iscatter,					// ISCATTER [SOURCE]				; ISCATTER (INTEGER REGISTERS TO MEMORY BLOCK)
		(u32)&ivvme_executeThreadSnippet_igather,					// IGATHER [SOURCE]					; IGATHER (MEMORY BLOCK TO INTEGER REGISTERS)
		(u32)&ivvme_executeThreadSnippet_fscatter,					// FSCATTER [SOURCE]				; FSCATTER (FLOATING POINT REGISTERS TO MEMORY BLOCK)
		(u32)&ivvme_executeThreadSnippet_fgather,					// FGATHER [SOURCE]					; FGATHER (MEMORY BLOCK TO FLOATING POINT REGISTERS)

		(u32)&ivvme_executeThreadSnippet_tmraddg,					// TMRADDG [INTERVAL] [SNIPPET]		; TIMER ADD GLOBAL INTERVAL [REG] USING SNIPPET [REG]
		(u32)&ivvme_executeThreadSnippet_tmrdelg,					// TMRDELG [SOURCE]					; TIMER DELETE GLOBAL [REG]
		(u32)&ivvme_executeThreadSnippet_tmrenag,					// TMRENAG [SOURCE]					; TIMER ENABLE GLOBAL [REG]
		(u32)&ivvme_executeThreadSnippet_tmrdisg,					// TMRDISG [SOURCE]					; TIMER DISABLE GLOBAL [REG]

		(u32)&ivvme_executeThreadSnippet_tmraddt,					// TMRADDT [INTERVAL] [SNIPPET]		; TIMER ADD THREAD INTERVAL [REG] USING SNIPPET [REG]
		(u32)&ivvme_executeThreadSnippet_tmrdelt,					// TMRDELT [SOURCE]					; TIMER DELETE THREAD [REG]
		(u32)&ivvme_executeThreadSnippet_tmrenat,					// TMRENAT [SOURCE]					; TIMER ENABLE THREAD [REG]
		(u32)&ivvme_executeThreadSnippet_tmrdist,					// TMRDIST [SOURCE]					; TIMER DISABLE THREAD [REG]

		(u32)&ivvme_executeThreadSnippet_passive,					// PASSIVE							; ENTER PASSIVE MODE, READ EVENTS AND RESPOND TO THEM WITHOUT CONTINUING THREAD EXECUTION
		(u32)&ivvme_executeThreadSnippet_active,					// ACTIVE							; LEAVE PASSIVE MODE UPON COMPLETION OF CURRENT SNIPPET, CLEAR EVENTS AND RESUME LINEAR EXECUTION

		(u32)&ivvme_executeThreadSnippet_setexs,					// SETEXS [SOURCE]					; EXCEPTION SET DEFAULT SNIPPET [REG]
		(u32)&ivvme_executeThreadSnippet_exceps,					// EXCEPS [SOURCE SNIPPET]			; EXCEPTION TRIGGER EXPLICIT SNIPPET [NUMBER]

		(u32)&ivvme_executeThreadSnippet_thrap,						// THRAP							; THREAD ADD, PAUSED, NO SNIPPET DEFINED
		(u32)&ivvme_executeThreadSnippet_thraps,					// THRAPS [SOURCE]					; THREAD ADD, PAUSED, USING SNIPPET [REG]
		(u32)&ivvme_executeThreadSnippet_thras,						// THRAS [SOURCE]					; THREAD ADD, NOT PAUSED, USING SNIPPET [REG]
		(u32)&ivvme_executeThreadSnippet_thraf,						// THRAF [SOURCE THREAD] [IMM8 CPU]	; THREAD [REG] ASCRIBE AFFINITY [REG]
		(u32)&ivvme_executeThreadSnippet_thrst,						// THRST							; THREAD SELF TERMINATE
		(u32)&ivvme_executeThreadSnippet_thrsp,						// THRSP							; THREAD SELF PAUSE
		(u32)&ivvme_executeThreadSnippet_thrxt,						// THRXT [SOURCE]					; THREAD [REG] TERMINATE
		(u32)&ivvme_executeThreadSnippet_thrxp,						// THRXP [SOURCE]					; THREAD [REG] PAUSE
		(u32)&ivvme_executeThreadSnippet_thrxr,						// THRXR [SOURCE]					; THREAD [REG] RESUME
		(u32)&ivvme_executeThreadSnippet_thrxrs,					// THRXRS [SOURCE THREAD] [SNIPPET]	; THREAD [REG] RESUME USING SNIPPET [REG]
		(u32)&ivvme_executeThreadSnippet_thrxj,						// THRXJ [SOURCE]					; THREAD [REG] JOIN

		(u32)&ivvme_executeThreadSnippet_screate,					// SCREATE							; SEMAPHORE CREATE
		(u32)&ivvme_executeThreadSnippet_slock,						// SLOCK	[SOURCE]				; SEMAPHORE LOCK, WAIT UNTIL LOCKS
		(u32)&ivvme_executeThreadSnippet_strylock,					// STRYLOCK [SOURCE]				; TRY SEMAPHORE LOCK, RETURN IMMEDIATELY IF FAILS
		(u32)&ivvme_executeThreadSnippet_sunlock,					// SUNLOCK [SOURCE]					; SEMAPHORE UNLOCK
		(u32)&ivvme_executeThreadSnippet_sdelete,					// SDELETE [SOURCE]					; SEMAPHORE DELETE

		(u32)&ivvme_executeThreadSnippet_predicate,					// PREDICATE [IMM16]				; USES AN EXTENDED PREDICATE FOR A HIGH COMBINATION OF EXPLICIT CONDITIONS
		(u32)&ivvme_executeThreadSnippet_copypred,					// COPYPRED [SOURCE]				; COPIES THE INDICATED SOURCE TO THE PREDICATE REGISTER

		(u32)&ivvme_executeThreadSnippet_unused,					// 248 UNUSED
		(u32)&ivvme_executeThreadSnippet_unused,					// 249 UNUSED
		(u32)&ivvme_executeThreadSnippet_unused,					// 250 UNUSED
		(u32)&ivvme_executeThreadSnippet_unused,					// 251 UNUSED
		(u32)&ivvme_executeThreadSnippet_unused,					// 252 UNUSED
		(u32)&ivvme_executeThreadSnippet_unused,					// 253 UNUSED
		(u32)&ivvme_executeThreadSnippet_unused,					// 254 UNUSED

		(u32)&ivvme_executeThreadSnippet_extended,					// 255 UNUSED
	};
