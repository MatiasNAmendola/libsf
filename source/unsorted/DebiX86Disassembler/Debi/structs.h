//////////
//
// DebiX86Disassembler/Debi/structs.h
//
//////
// Version 0.80
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.13.2014
//////
// Change log:
//     Feb.13.2014 - Initial creation
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




// structs.h


// When changing REGTYPE, update disasm.cpp::do_common_return_operand_size_text()
enum REGTYPE {  _8bit		= 1,			/* ah/al */
				_16bit		= 2,			/* ax */
				_32bit		= 4,			/* eax */
				_64bit		= 8,			/* rax */
				_mmx		= 16,			/* mm0 */
				_xmmx		= 32,			/* xmm0 */
				_fpu		= 64,			/* st0 */
				_80bit		= 128,			/* size of stx regs */
				_128bit		= 256,			/* size of xmmx regs */
				_6byte		= 512,			/* size of gdt register in legacy/compat mode */
				_10byte		= 1024,			/* size of gdt register in IA-32e mode */
				_illegal	= 2048,			/* Added for illegal opcode encodings */
				_0bit		= 4096,			/* Added to indicate no prefix should be used */
				_f32		= 8192,			/* f32 ptr */
				_f64		= 16384,		/* f64 ptr */
				_f80		= 32768,		/* f80 ptr */
				_s32		= 65536,		/* s32 ptr */
				_s64		= 131072,		/* s64 ptr */
				_s16		= 256142,		/* s16 ptr */
				_m80		= 524288,		/* m80 ptr */
				_m94byte	= 1048576,		/* 94-byte ptr */
				_m108byte	= 2097152,		/* 108-byte ptr */
				_m14byte	= 4194304,		/* 14-byte ptr */
				_m28byte	= 8388608,		/* 28-byte ptr */
				_varies		= 16777216 };	/* Varies by side, refer to dd->op1_regtype and dd->op2_regtype */

enum PREFIX	  { CSREG	= 1,			/* cs: */
				DSREG	= 2,			/* ds: */
				ESREG	= 4,			/* es: */
				FSREG	= 8,			/* fs: */
				GSREG	= 16,			/* gs: */
				SSREG	= 32,			/* ss: */
				LOCK	= 64,			/* lock */
				REPE	= 128,			/* REP/REPE */
				REPNE	= 256 };		/* REPNE */

enum OVERRIDE { Operand	= 1,
				Address	= 2 };
				
enum MODE { _16bit_mode	= 1,
			_32bit_mode	= 2,
			_64bit_mode	= 3 };

enum OPERAND {	Byte	= 1,		/* byte ptr */
				Word	= 2,		/* word ptr */
				Dword	= 4,		/* dword ptr */
				Qword	= 8,		/* qword ptr */
				Tbyte	= 16,		/* tbyte ptr */
				DQword	= 32 };		/* dqword ptr */

enum DESTINATION {	Memory		= 1,	/* A memory location */
					Register	= 2 };	/* some register */

enum REGSET1 {	_accum_low_reg	= 0,
				_count_low_reg	= 1,
				_data_low_reg	= 2,
				_base_low_reg	= 3,
				_accum_high_reg	= 4,
				_count_high_reg	= 5,
				_data_high_reg	= 6,
				_base_high_reg	= 7 };

enum REGSET2 {	_accum_reg	= 0,
				_count_reg	= 1,
				_data_reg	= 2,
				_base_reg	= 3,
				_stack_reg	= 4,
				_bptr_reg	= 5,
				_source_reg	= 6,
				_dest_reg	= 7 };

enum REGSET3 {	_gp_reg		= 0,
				_control_reg= 1,
				_debug_reg	= 2,
				_test_reg	= 3,
				_segment_reg= 4,
				_fpu_reg	= 5,
				_mmx_reg	= 6,
				_xmmx_reg	= 7 };



// Structure for the disassembly data
struct SDisasmData
{
	u32			prefixes;					// Refer to Enum PREFIX for list
	u32			overrides;					// Refer to Enum OVERRIDE for list
	u8*			mnemonic;					// Something like "nop"
	u8*			comment;					// Comment about this statement
	u8*			line_comment;				// A comment to be included on the source code line, such as:
											//		nop		; do not do anything
	u8*			operand1;					// Something like "eax" in "add eax,ebx"
	u32			operand1_source_type;		// Type of operand for operand 1
	u32			operand1_regtype;			// Register type for operand 1 if rt = _varies
	u8*			operand2;					// Something like "ebx" in "add eax,ecx"
	u32			operand2_source_type;		// Type of operand for operand 2
	u32			operand2_regtype;			// Register type for operand 2 if rt = _varies
	u8*			operand3;					// Something like "cl" in "shrd eax,ebx,cl"
	u32			operand3_source_type;		// Type of operand for operand 3
	u8*			immediate;					// Something like "5" in "add eax,5"
	u32			immediate_value;			// Value of immediate
	u32			operand_size;				// Refer to Enum OPERAND for list
	u32			destination_source_type;	// Refer to Enum DESTINATION for list
	
	// Flags
	u32			force_reg;					// Refer to Enum REGTYPE for list, used to override current cpu mode when fixed-sized operand is required
	u32			regrm_reversed;				// Should the reg/regm operands internal to the mod/r/m byte be reversed for this instruction?
	u32			sib_reversed;				// Should the i/b operands internal to the s/i/b byte be reversed for this instruction?
	u32			is_reversed;				// Are operands 1 and 2 reversed (called from common_reversed() functions)
	
	// Literal source data
	u8*			data;						// Pointer to the start of the opcode bytes for this iteration through prefixes, overrides, opcodes, etc.
	u8*			data_root;					// Pointer to the start of the opcode from the get-go, before moving over for prefixes, etc.
	u32			opcode_bytes;				// Length of the instruction, like 1 for NOP, 2 for INT 0x80
};
