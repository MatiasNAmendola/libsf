//////////
//
// DebiX86Disassembler/Debi/disasm.h
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




// disasm.h

#include "buffers.h"

extern u32 _cpu_mode;


//////////
//
// Prototype definitions
//
/////
	void	extract_gp_reg_operand						(SDisasmData* dd, u8 reg, u8** op, u32/*REGTYPE*/ rt);
	void	extract_8bit_reg_operand					(u8 reg, u8** op, u8* prefix_op = _null_string);
	void	extract_16bit_reg_operand					(u8 reg, u8** op, u8* prefix_op = _null_string);
	void	extract_32bit_reg_operand					(u8 reg, u8** op, u8* prefix_op = _null_string);
	void	extract_64bit_reg_operand					(u8 reg, u8** op, u8* prefix_op = _null_string);
	void	extract_test_reg_operand					(u8 reg, u8** op, u8* prefix_op = _null_string);
	void	extract_debug_reg_operand					(u8 reg, u8** op, u8* prefix_op = _null_string);
	void	extract_control_reg_operand					(u8 reg, u8** op, u8* prefix_op = _null_string);
	void	extract_mmx_reg_operand						(u8 reg, u8** op, u8* prefix_op = _null_string);
	void	extract_xmmx_reg_operand					(u8 reg, u8** op, u8* prefix_op = _null_string);
	void	extract_stx_reg_operand						(u8 reg, u8** op, u8* prefix_op = _null_string);
	void	extract_8bit_reg_operands_1_2				(u8* data, SDisasmData* dd);
	void	store_prefix_mnemonics						(u8* buffer, SDisasmData* dd);
	void	extract_modrm_16bit_address_mode			(u8* data, SDisasmData* dd, u8* op_buffer, u8** op1, u8** op2, REGTYPE rt, bool do_reg, u8* prefix_op1 = _null_string);
	void	extract_modrm_32bit_address_mode			(u8* data, SDisasmData* dd, u8* op_buffer, u8** op1, u8** op2, REGTYPE rt, bool do_reg, u8* prefix_op1 = _null_string);
	void	extract_sib_32bit_address_mode				(u8* data, SDisasmData* dd, u8* disp, u8* prefix_buffer, u8* op_buffer, u8** op1, u8** op2, u8 mod, u8* prefix_op1 = _null_string);
	void	do_common_adjust_register_size				(u8* op, u32/*REGTYPE*/ rt);
	u8*		do_common_return_operand_size_text			(SDisasmData* dd);
	void	do_common_set_operand_size					(SDisasmData* dd);
	void	do_common_regrm								(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, bool do_reg = true, u8* prefix_op1 = _null_string);
	void	do_common_regrm_reversed					(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, bool do_reg = true, u8* prefix_op1 = _null_string);
	void	do_common_rm								(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op1 = _null_string);
	void	do_common_r									(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op1 = _null_string);
	void	do_common_m									(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op1 = _null_string);
	void	do_common_opcode_mov						(u8* data, SDisasmData* dd, u32 op1_reg, u32 op2_reg, u32 opcode_length = 2);
	void	do_common_opcode_rm8_one_operand			(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size = 0, u32 opcode_length = 1);
	void	do_common_opcode_rm16_one_operand			(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size = 0, u32 opcode_length = 1);
	void	do_common_opcode_rm32_one_operand			(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size = 0, u32 opcode_length = 1);
	void	do_common_opcode_fpu_rm_one_operand			(u8* data, SDisasmData* dd, u8* mnemonic, u32 operand_size, u32 opcode_length = 2);
	void	do_common_opcode_fpu_hard_stx				(u8* data, SDisasmData* dd, u8* mnemonic, u32 reg, u32 opcode_length = 2);
	void	do_common_opcode_fpu_stx_hard				(u8* data, SDisasmData* dd, u8* mnemonic, u32 reg, u32 opcode_length = 2);
	void	do_common_opcode_fpu_stx					(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 2);
	void	do_common_opcode_r16_m16_16_one_operand		(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_r32_m16_32_one_operand		(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm16_rm32_one_operand		(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size = 0, u32 opcode_length = 1);
	void	do_common_opcode_m_one_operand				(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size = 0, u32 opcode_length = 1);
	void	do_common_unknown							(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1, u8* comment = NULL, u8* line_comment = NULL);
	void	do_immediate								(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op1 = _null_string);
	void	do_signed_immediate							(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op  = _null_string);
	int		sign_extend_8bit_to_32bits					(u8 value);
	int		sign_extend_16bits_to_32bits				(u16 value);
	void	do_common_swap_operand1_operand2			(SDisasmData* dd);
	void	do_common_prefix_operand1					(SDisasmData* dd, u8* prefix);
	void	do_common_prefix_operand2					(SDisasmData* dd, u8* prefix);
	void	do_immediate_sign_extend_8bits_to_16_32bit	(u8* data, SDisasmData* dd);
	void	do_common_opcode_rm8						(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_r1632_rm8					(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm8_reversed				(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm16_rm32					(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm16_r16					(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm32_r32					(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_r16_rm16					(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_r32_rm32					(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_r1632_rm1632				(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm1632_m16_1632			(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm16_r16_cl				(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm32_r32_cl				(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm1632_r1632_cl			(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm16_rm32_reversed			(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_r_rm_mmx					(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_r_rm_xmmx					(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm_r_mmx					(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_rm_r_xmmx					(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_mmx_immed8					(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_opcode_xmmx_immed8				(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_rm8_immed8						(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_rm8_1								(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_rm8_cl							(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_rm16_32_immed8					(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_rm16_32_1							(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_rm16_32_cl						(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_rm16_32_immed16_32				(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_accum8_immed8						(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_accum16_32_immed8					(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_accum16_32_immed16_32				(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1);
	void	do_common_mnemonic							(SDisasmData* dd, u8* mnemonic, u32 opcode_length = 1, u8* comment = NULL, u8* line_comment = NULL);
	void	do_common_operand_size_check_mnemonic		(SDisasmData* dd, u32 opcode_length, u8* _16bit_mnemonic, u8* _32bit_mnemonic);
	void	do_common_two_prefixes_mnemonic_operand_size_check
														(SDisasmData* dd, u32 opcode_length, 
														 u32 prefix1, u8* mnemonic1,
														 u32 prefix2, u8* mnemonic2,
														 u8* _16bit_operand,
														 u8* _32bit_operand);
	void	do_common_opcode_mmx_xmmx					(u8* data, SDisasmData* dd, u8* instuction, u8* comment);
	void	do_common_opcode_mmx_xmmx_immed8			(u8* data, SDisasmData* dd, u8* instuction, u8* comment);
