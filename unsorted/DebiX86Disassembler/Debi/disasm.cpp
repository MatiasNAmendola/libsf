//////////
//
// DebiX86Disassembler/Debi/disasm.cpp
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




#include <stdlib.h>
#include <stdio.h>

#include "const.h"
#include "structs.h"
#include "defs.h"

#include "disasm.h"
extern DISASM_FUNC second_byte_functions[];


//////////
//
// Supporting functions
//
/////
	void extract_gp_reg_operand(SDisasmData* dd, u8 reg, u8** op, u32/*REGTYPE*/ rt)
	{
		if (rt == _8bit)
		{
			// 8-bit register
			extract_8bit_reg_operand(reg, op);
		}
		else
		{
			// 16-bit or 32-bit immediate
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			{
				// 32-bit addressing mode
				extract_32bit_reg_operand(reg, op);
			}
			else
			{
				// 16-bit addressing mode
				extract_16bit_reg_operand(reg, op);
			}
		}
	}
	
	void add_prefix_op(u8** op, u8* prefix_op)
	{
		// See if there's anything to prefix
		if (prefix_op == _null_string)
			return;	// nope
		
		// Replace the current value with the destination value
		sprintf((s8*)&prefix_op_buffer[0], "%s%s", prefix_op, *op);
		*op = &prefix_op_buffer[0];
	}

	void extract_8bit_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)
			*op = _al_reg;
		else if (reg == 1)
			*op = _cl_reg;
		else if (reg == 2)
			*op = _dl_reg;
		else if (reg == 3)
			*op = _bl_reg;
		else if (reg == 4)
			*op = _ah_reg;
		else if (reg == 5)
			*op = _ch_reg;
		else if (reg == 6)
			*op = _dh_reg;
		else if (reg == 7)
			*op = _bh_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_16bit_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)
			*op = _ax_reg;
		else if (reg == 1)
			*op = _cx_reg;
		else if (reg == 2)
			*op = _dx_reg;
		else if (reg == 3)
			*op = _bx_reg;
		else if (reg == 4)
			*op = _sp_reg;
		else if (reg == 5)
			*op = _bp_reg;
		else if (reg == 6)
			*op = _si_reg;
		else if (reg == 7)
			*op = _di_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_32bit_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)
			*op = _eax_reg;
		else if (reg == 1)
			*op = _ecx_reg;
		else if (reg == 2)
			*op = _edx_reg;
		else if (reg == 3)
			*op = _ebx_reg;
		else if (reg == 4)
			*op = _esp_reg;
		else if (reg == 5)
			*op = _ebp_reg;
		else if (reg == 6)
			*op = _esi_reg;
		else if (reg == 7)
			*op = _edi_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_64bit_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)
			*op = _rax_reg;
		else if (reg == 1)
			*op = _rcx_reg;
		else if (reg == 2)
			*op = _rdx_reg;
		else if (reg == 3)
			*op = _rbx_reg;
		else if (reg == 4)
			*op = _rsp_reg;
		else if (reg == 5)
			*op = _rbp_reg;
		else if (reg == 6)
			*op = _rsi_reg;
		else if (reg == 7)
			*op = _rdi_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_test_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)
			*op = _tr0_reg;
		else if (reg == 1)
			*op = _tr1_reg;
		else if (reg == 2)
			*op = _tr2_reg;
		else if (reg == 3)
			*op = _tr3_reg;
		else if (reg == 4)
			*op = _tr4_reg;
		else if (reg == 5)
			*op = _tr5_reg;
		else if (reg == 6)
			*op = _tr6_reg;
		else if (reg == 7)
			*op = _tr7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_debug_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)
			*op = _dr0_reg;
		else if (reg == 1)
			*op = _dr1_reg;
		else if (reg == 2)
			*op = _dr2_reg;
		else if (reg == 3)
			*op = _dr3_reg;
		else if (reg == 4)
			*op = _dr4_reg;
		else if (reg == 5)
			*op = _dr5_reg;
		else if (reg == 6)
			*op = _dr6_reg;
		else if (reg == 7)
			*op = _dr7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_control_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)
			*op = _cr0_reg;
		else if (reg == 1)
			*op = _cr1_reg;
		else if (reg == 2)
			*op = _cr2_reg;
		else if (reg == 3)
			*op = _cr3_reg;
		else if (reg == 4)
			*op = _cr4_reg;
		else if (reg == 5)
			*op = _cr5_reg;
		else if (reg == 6)
			*op = _cr6_reg;
		else if (reg == 7)
			*op = _cr7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_mmx_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)
			*op = _mm0_reg;
		else if (reg == 1)
			*op = _mm1_reg;
		else if (reg == 2)
			*op = _mm2_reg;
		else if (reg == 3)
			*op = _mm3_reg;
		else if (reg == 4)
			*op = _mm4_reg;
		else if (reg == 5)
			*op = _mm5_reg;
		else if (reg == 6)
			*op = _mm6_reg;
		else if (reg == 7)
			*op = _mm7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_xmmx_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)
			*op = _xmm0_reg;
		else if (reg == 1)
			*op = _xmm1_reg;
		else if (reg == 2)
			*op = _xmm2_reg;
		else if (reg == 3)
			*op = _xmm3_reg;
		else if (reg == 4)
			*op = _xmm4_reg;
		else if (reg == 5)
			*op = _xmm5_reg;
		else if (reg == 6)
			*op = _xmm6_reg;
		else if (reg == 7)
			*op = _xmm7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_stx_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)
			*op = _st0_reg;
		else if (reg == 1)
			*op = _st1_reg;
		else if (reg == 2)
			*op = _st2_reg;
		else if (reg == 3)
			*op = _st3_reg;
		else if (reg == 4)
			*op = _st4_reg;
		else if (reg == 5)
			*op = _st5_reg;
		else if (reg == 6)
			*op = _st6_reg;
		else if (reg == 7)
			*op = _st7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_8bit_reg_operands_1_2(u8* data, SDisasmData* dd)
	{
		extract_8bit_reg_operand((*data & 0xf0) >> 4, &dd->operand1);
		extract_8bit_reg_operand( *data & 0x0f,		  &dd->operand2);
		dd->operand_size = Byte;
	}
	
	void store_prefix_mnemonics(u8* buffer, SDisasmData* dd)
	{
		// Refer to PREFIX enums in structs.h
		// Note:  Proper syntax does not allow for multiple of these override prefixes,
		//        though they can be physically encoded and will be processed by the CPU
		sprintf((s8*)buffer, "%s%s%s%s%s%s%s", 
			dd->prefixes & LOCK  ? (s8*)"[lock] " : (s8*)_null_string,
			dd->prefixes & CSREG ? (s8*)_cs_colon : (s8*)_null_string,
			dd->prefixes & DSREG ? (s8*)_ds_colon : (s8*)_null_string,
			dd->prefixes & ESREG ? (s8*)_es_colon : (s8*)_null_string,
			dd->prefixes & FSREG ? (s8*)_fs_colon : (s8*)_null_string,
			dd->prefixes & GSREG ? (s8*)_gs_colon : (s8*)_null_string,
			dd->prefixes & SSREG ? (s8*)_ss_colon : (s8*)_null_string);
	}

	void extract_modrm_16bit_address_mode(u8* data, SDisasmData* dd, u8* op_buffer, u8** op1, u8** op2, REGTYPE rt, bool do_reg, u8* prefix_op1)
	{
		u8 t;
		u8 prefix_buffer[32];
		u8 mod = (*data & 0xc0) >> 6;	// Upper 2 bits
		u8 r   = (*data & 0x38) >> 3;	// Next 3 lower
		u8 rm  = (*data & 0x07);		// Bottom 3


		// Load any "cs:", "ss:" stuff
		store_prefix_mnemonics(&prefix_buffer[0], dd);


		// See if we're supposed to order reg/rm operands in the reverse order
		if (dd->regrm_reversed)
		{
			// swap
			t = rm;
			rm = r;
			r = t;
		}


		// Figure out what to do here
		switch (mod)
		{
			case 0:
				dd->opcode_bytes			+= 1;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[bx+si]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[bx+di]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[bp+si]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[bp+di]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)op_buffer, "%s%s[si]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[di]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 6:
						// 16-bit displacement value
						sprintf((s8*)op_buffer, "%s%s[%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						dd->opcode_bytes += 2;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[bx]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 1:
				dd->opcode_bytes			+= 2;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[bx+si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[bx+di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[bp+si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[bp+di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)op_buffer, "%s%s[si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[bp+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[bx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 2:
				dd->opcode_bytes += 3;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[bx+si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[bx+di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[bp+si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[bp+di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)op_buffer, "%s%s[si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[bp+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[bx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 3:
				dd->opcode_bytes += 1;
				dd->destination_source_type	= Register;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (dd->force_reg ? dd->force_reg : 
						rt != _varies ? rt :
						dd->is_reversed ? dd->operand2_regtype : dd->operand1_regtype)
				{
					case _8bit:
						extract_8bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _16bit:
						extract_16bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _32bit:
						extract_32bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _64bit:
						extract_64bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _mmx:
						extract_mmx_reg_operand(rm, op1, prefix_op1);
						break;
					case _xmmx:
						extract_xmmx_reg_operand(rm, op1, prefix_op1);
						break;
				}
				break;

		}
		
		if (do_reg)
		{
			// Store operand2
			if (dd->is_reversed)
				dd->operand1_source_type = Register;
			else
				dd->operand2_source_type = Register;


			switch (dd->force_reg ? dd->force_reg : 
					rt != _varies ? rt :
					dd->is_reversed ? dd->operand1_regtype : dd->operand2_regtype)
			{
				case _8bit:
					extract_8bit_reg_operand(r, op2);
					dd->operand_size = Byte;
					break;
				case _16bit:
					extract_16bit_reg_operand(r, op2);
					dd->operand_size = Word;
					break;
				case _32bit:
					extract_32bit_reg_operand(r, op2);
					dd->operand_size = Dword;
					break;
				case _64bit:
					extract_64bit_reg_operand(r, op2);
					dd->operand_size = Qword;
					break;
				case _mmx:
					extract_mmx_reg_operand(r, op2);
					dd->operand_size = Qword;
					break;
				case _xmmx:
					extract_xmmx_reg_operand(r, op2);
					dd->operand_size = DQword;
					break;
			}
		}
	}

	void extract_modrm_32bit_address_mode(u8* data, SDisasmData* dd, u8* op_buffer, u8** op1, u8** op2, REGTYPE rt, bool do_reg, u8* prefix_op1)
	{
		u8 t;
		u8 prefix_buffer[32];
		u8 mod = (*data & 0xc0) >> 6;	// Upper 2 bits
		u8 r   = (*data & 0x38) >> 3;	// Next 3 lower
		u8 rm  = (*data & 0x07);		// Bottom 3


		// Load any "cs:", "ss:" stuff
		store_prefix_mnemonics(&prefix_buffer[0], dd);


		// See if we're supposed to order reg/rm operands in the reverse order
		if (dd->regrm_reversed)
		{
			// swap
			t = rm;
			rm = r;
			r = t;
		}


		// Figure out what to do here
		switch (mod)
		{
			case 0:
				dd->opcode_bytes			+= 1;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[eax]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[ecx]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[edx]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[ebx]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						// SIB byte follows
						extract_sib_32bit_address_mode(data + 1, dd, _null_string, &prefix_buffer[0], op_buffer, op1, op2, mod, prefix_op1);
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						dd->opcode_bytes += 4;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[esi]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[edi]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 1:
				dd->opcode_bytes			+= 2;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[eax+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[ecx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[edx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[ebx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)&sib2_buffer[0], "+%u", (int)*(u8*)(data + 2));
						extract_sib_32bit_address_mode(data + 1, dd, &sib2_buffer[0], &prefix_buffer[0], op_buffer, op1, op2, mod, prefix_op1);
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[ebp+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[esi+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[edi+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 2:
				dd->opcode_bytes			+= 5;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[eax+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[ecx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[edx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[ecx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)&sib2_buffer[0], "+%u", (int)*(u32*)(data + 2));
						extract_sib_32bit_address_mode(data + 1, dd, &sib2_buffer[0], &prefix_buffer[0], op_buffer, op1, op2, mod, prefix_op1);
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[ebp+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[esi+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[edi+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 3:
				dd->opcode_bytes += 1;
				dd->destination_source_type	= Register;
				if (dd->is_reversed)
					dd->operand2_source_type = Register;
				else
					dd->operand1_source_type = Register;


				switch (dd->force_reg ? dd->force_reg : 
						rt != _varies ? rt :
						dd->is_reversed ? dd->operand2_regtype : dd->operand1_regtype)
				{
					case _8bit:
						extract_8bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _16bit:
						extract_16bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _32bit:
						extract_32bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _64bit:
						extract_64bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _mmx:
						extract_mmx_reg_operand(rm, op1, prefix_op1);
						break;
					case _xmmx:
						extract_xmmx_reg_operand(rm, op1, prefix_op1);
						break;
				}
				break;

		}
		
		if (do_reg)
		{
			// Store operand2
			if (dd->is_reversed)
				dd->operand1_source_type = Register;
			else
				dd->operand2_source_type = Register;


			switch (dd->force_reg ? dd->force_reg : 
					rt != _varies ? rt :
					dd->is_reversed ? dd->operand1_regtype : dd->operand2_regtype)
			{
				case _8bit:
					extract_8bit_reg_operand(r, op2);
					dd->operand_size = Byte;
					break;
				case _16bit:
					extract_16bit_reg_operand(r, op2);
					dd->operand_size = Word;
					break;
				case _32bit:
					extract_32bit_reg_operand(r, op2);
					dd->operand_size = Dword;
					break;
				case _64bit:
					extract_64bit_reg_operand(r, op2);
					dd->operand_size = Qword;
					break;
				case _mmx:
					extract_mmx_reg_operand(r, op2);
					dd->operand_size = Qword;
					break;
				case _xmmx:
					extract_xmmx_reg_operand(r, op2);
					dd->operand_size = DQword;
					break;
			}
		}
	}
	
	u8* do_common_return_operand_size_text(SDisasmData* dd)
	{
		switch (dd->operand_size)
		{
			case _8bit:
				return(_byte_ptr);
			case _16bit:
				return(_word_ptr);
			case _32bit:
				return(_dword_ptr);
			case _64bit:
				return(_qword_ptr);
			case _80bit:
				return(_tbyte_ptr);
			case _128bit:
				return(_dqword_ptr);
			case _6byte:
				return(_6byte_ptr);
			case _10byte:
				return(_10byte_ptr);
			case _illegal:
				return(_illegal_ptr);
			case _0bit:
				return(_null_string);
			case _f32:
				return(_f32_ptr);
			case _f64:
				return(_f64_ptr);
			case _f80:
				return(_f80_ptr);
			case _s32:
				return(_s32_ptr);
			case _s64:
				return(_s64_ptr);
			case _mmx:
				return(_mmx_ptr);
			case _xmmx:
				return(_xmmx_ptr);
			case _fpu:
				return(_fpu_ptr);
			case _m94byte:
				return(_94byte_ptr);
			case _m108byte:
				return(_108byte_ptr);
			case _m14byte:
				return(_14byte_ptr);
			case _m28byte:
				return(_28byte_ptr);
			default:
				return(_unk_ptr);		// Should never be used
		}
	}
	
	void do_common_set_operand_size(SDisasmData* dd)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit operand mode
			dd->operand_size = _32bit;
		}
		else
		{
			// 16-bit operand mode
			dd->operand_size = _16bit;
		}
	}

	void extract_sib_32bit_address_mode(u8* data, SDisasmData* dd, u8* disp, u8* prefix_buffer, u8* op_buffer, u8** op1, u8** op2, u8 mod, u8* prefix_op1)
	{
		u32 needs_plus;					// Does the base reg need a plus sign before the scale? True if not (mod=0, b=5)
		u8 s = (*data & 0xc0) >> 6;		// Upper 2 bits
		u8 i  = (*data & 0x38) >> 3;	// Next 3 lower
		u8 b   = (*data & 0x07);		// Bottom 3



		// Set the base register
		needs_plus = 1;
		switch (b)
		{
			case 0:
				sprintf((s8*)&sib_buffer[0], "%s", _eax_reg);
				break;
			case 1:
				sprintf((s8*)&sib_buffer[0], "%s", _ecx_reg);
				break;
			case 2:
				sprintf((s8*)&sib_buffer[0], "%s", _edx_reg);
				break;
			case 3:
				sprintf((s8*)&sib_buffer[0], "%s", _ebx_reg);
				break;
			case 4:
				sprintf((s8*)&sib_buffer[0], "%s", _esp_reg);
				break;
			case 5:
				if (mod == 0)
				{
					// None is used
					sprintf((s8*)&sib_buffer[0], "%s", (s8*)_null_string);
					needs_plus = 0;
				}
				else
				{
					// It's ebp
					sprintf((s8*)&sib_buffer[0], "%s", _ebp_reg);
				}
				break;
			case 6:
				sprintf((s8*)&sib_buffer[0], "%s", _esi_reg);
				break;
			case 7:
				sprintf((s8*)&sib_buffer[0], "%s", _edi_reg);
				break;
		}
		
		switch (s)
		{
			case 0:
				dd->opcode_bytes += 1;
				switch (i)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[%s%seax%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[%s%secx%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[%s%sedx%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[%s%sebx%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)op_buffer, "%s%s[%s%s%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[%s%sebp%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[%s%sesi%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[%s%sedi%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
				}
				break;

			case 1:
				dd->opcode_bytes += 1;
				switch (i)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[%s%seax*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[%s%secx*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[%s%sedx*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[%s%sebx*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 4:
						// None
						sprintf((s8*)op_buffer, "%s%s[%s%s%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[%s%sebp*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[%s%sesi*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[%s%sedi*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
				}
				break;

			case 2:
				dd->opcode_bytes += 1;
				switch (i)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[%s%seax*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[%s%secx*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[%s%sedx*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[%s%sebx*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 4:
						// None
						sprintf((s8*)op_buffer, "%s%s[%s%s%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[%s%sebp*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[%s%sesi*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[%s%sedi*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
				}
				break;

			case 3:
				dd->opcode_bytes += 1;
				switch (i)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[%s%seax*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[%s%secx*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[%s%sedx*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[%s%sebx*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 4:
						// None
						sprintf((s8*)op_buffer, "%s%s[%s%s%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[%s%sebp*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[%s%sesi*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[%s%sedi*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? _plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
				}
				break;

		}
	}
	
	void do_common_adjust_register_size(u8* op, u32/*REGTYPE*/ rt)
	{
		switch (rt)
		{
			case _8bit:
				if (op == _ax_reg || op == _eax_reg)
					op = _al_reg;
				else if (op == _bx_reg || op == _ebx_reg)
					op = _bl_reg;
				else if (op == _cx_reg || op == _ecx_reg)
					op = _cl_reg;
				else if (op == _dx_reg || op == _edx_reg)
					op = _dl_reg;
				break;

			case _16bit:
				if (op == _al_reg || op == _eax_reg)
					op = _ax_reg;
				else if (op == _bl_reg || op == _ebx_reg)
					op = _bx_reg;
				else if (op == _cl_reg || op == _ecx_reg)
					op = _cx_reg;
				else if (op == _dl_reg || op == _edx_reg)
					op = _dx_reg;
				else if (op == _esi_reg)
					op = _si_reg;
				else if (op == _edi_reg)
					op = _di_reg;
				else if (op == _ebp_reg)
					op = _bp_reg;
				else if (op == _esp_reg)
					op = _sp_reg;
				break;

			case _32bit:
				if (op == _al_reg || op == _ax_reg)
					op = _eax_reg;
				else if (op == _bl_reg || op == _bx_reg)
					op = _ebx_reg;
				else if (op == _cl_reg || op == _cx_reg)
					op = _ecx_reg;
				else if (op == _dl_reg || op == _dx_reg)
					op = _edx_reg;
				else if (op == _esi_reg)
					op = _esi_reg;
				else if (op == _edi_reg)
					op = _edi_reg;
				else if (op == _ebp_reg)
					op = _ebp_reg;
				else if (op == _esp_reg)
					op = _esp_reg;
				break;
		}
	}

	void do_common_regrm(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, bool do_reg, u8* prefix_op1)
	{
		u32 lTest;
		
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Address) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Address) != 0))
		{
			// 32-bit addressing mode
			if (rt == _8bit)
				extract_modrm_32bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _8bit, do_reg, prefix_op1);
			else
			{
				if ((dd->overrides & (u32)Operand) == 0 && rt != (u32)_16bit)
				{
					// No operand override
					// The next two lines (and repeats of the same) are coded this way due to an apparent bug in g++
					// The syntax:  if (rt == (_16bit | _32bit)) does not work.
					// The syntax:  if (rt & (_16bit | _32bit) == rt) does not work
					// etc.
					lTest = (rt == _16bit | _32bit) ? 1 : 0;
					if (lTest)
						extract_modrm_32bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _cpu_mode == _16bit_mode ? _16bit : _32bit, do_reg, prefix_op1);
					else
						extract_modrm_32bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, (REGTYPE)rt, do_reg, prefix_op1);
				}
				else
				{
					// Operand override
					lTest = (rt == _16bit | _32bit) ? 1 : 0;
					if (lTest)
						extract_modrm_32bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _cpu_mode == _16bit_mode ? _32bit : _16bit, do_reg, prefix_op1);
					else
						extract_modrm_32bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, (REGTYPE)rt, do_reg, prefix_op1);
				}
			}
		}
		else
		{
			// 16-bit addressing mode
			if (rt == _8bit)
				extract_modrm_16bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _8bit, do_reg, prefix_op1);
			else
			{
				if ((dd->overrides & (u32)Operand) == 0 && rt != (u32)_32bit)
				{
					// No operand override
					lTest = (rt == _16bit | _32bit) ? 1 : 0;
					if (lTest)
						extract_modrm_16bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _cpu_mode == _16bit_mode ? _16bit : _32bit, do_reg, prefix_op1);
					else
						extract_modrm_16bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, (REGTYPE)rt, do_reg, prefix_op1);
				}
				else
				{
					// Operand override
					lTest = (rt == _16bit | _32bit) ? 1 : 0;
					if (lTest)
						extract_modrm_16bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _cpu_mode == _16bit_mode ? _32bit : _16bit, do_reg, prefix_op1);
					else
						extract_modrm_16bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, (REGTYPE)rt, do_reg, prefix_op1);
				}
			}
		}
	}

	void do_common_regrm_reversed(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, bool do_reg, u8* prefix_op1)
	{
		u32 lTest;
		
		dd->is_reversed = 1;
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Address) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Address) != 0))
		{
			// 32-bit addressing mode
			if (rt == _8bit)
				extract_modrm_32bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _8bit, do_reg, prefix_op1);
			else
			{
				if ((dd->overrides & (u32)Operand) == 0 && rt != (u32)_16bit)
				{
					// No operand override
					lTest = (rt == _16bit | _32bit) ? 1 : 0;
					if (lTest)
						extract_modrm_32bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _cpu_mode == _16bit_mode ? _16bit : _32bit, do_reg, prefix_op1);
					else
						extract_modrm_32bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, (REGTYPE)rt, do_reg, prefix_op1);
				}
				else
				{
					// Operand override
					lTest = (rt == _16bit | _32bit) ? 1 : 0;
					if (lTest)
						extract_modrm_32bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _cpu_mode == _16bit_mode ? _32bit : _16bit, do_reg, prefix_op1);
					else
						extract_modrm_32bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, (REGTYPE)rt, do_reg, prefix_op1);
				}
			}
		}
		else
		{
			// 16-bit addressing mode
			if (rt == _8bit)
				extract_modrm_16bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _8bit, do_reg, prefix_op1);
			else
			{
				if ((dd->overrides & (u32)Operand) == 0 && rt != (u32)_32bit)
				{
					// No operand override
					lTest = (rt == _16bit | _32bit) ? 1 : 0;
					if (lTest)
						extract_modrm_16bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _cpu_mode == _16bit_mode ? _16bit : _32bit, do_reg, prefix_op1);
					else
						extract_modrm_16bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, (REGTYPE)rt, do_reg, prefix_op1);
				}
				else
				{
					// Operand override
					lTest = (rt == _16bit | _32bit) ? 1 : 0;
					if (lTest)
						extract_modrm_16bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _cpu_mode == _16bit_mode ? _32bit : _16bit, do_reg, prefix_op1);
					else
						extract_modrm_16bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, (REGTYPE)rt, do_reg, prefix_op1);
				}
			}
		}
	}

	void do_common_rm(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op1)
	{
		do_common_regrm(data, dd, rt, false, prefix_op1);
	}

	void do_common_r(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op1)
	{
		dd->regrm_reversed = 1;
		do_common_regrm(data, dd, rt, false, prefix_op1);
	}
	
	void do_common_opcode_mov(u8* data, SDisasmData* dd, u32 op1_reg, u32 op2_reg, u32 opcode_length)
	{
		dd->mnemonic			= _mov_instruction;
		dd->operand1_regtype	= op1_reg;
		dd->operand2_regtype	= op1_reg;
		dd->opcode_bytes		+= opcode_length;
		do_common_regrm(dd->data_root + dd->opcode_bytes, dd, _varies);
	}
	
	void do_common_opcode_rm8_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;

		do_common_rm(dd->data_root + opcode_length, dd, _8bit);
		if (dd->operand1_source_type == Memory)
		{
			if (hard_operand_size != 0)
				dd->operand_size = hard_operand_size;
			else
				do_common_set_operand_size(dd);
			
			do_common_prefix_operand1(dd, do_common_return_operand_size_text(dd));
		}
	}
	
	void do_common_opcode_rm16_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;

		do_common_rm(dd->data_root + opcode_length, dd, _16bit);
		if (dd->operand1_source_type == Memory)
		{
			if (hard_operand_size != 0)
				dd->operand_size = hard_operand_size;
			else
				do_common_set_operand_size(dd);
			
			do_common_prefix_operand1(dd, do_common_return_operand_size_text(dd));
		}
	}
	
	void do_common_opcode_rm32_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m32", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;

		do_common_rm(dd->data_root + opcode_length, dd, _32bit);
		if (dd->operand1_source_type == Memory)
		{
			if (hard_operand_size != 0)
				dd->operand_size = hard_operand_size;
			else
				do_common_set_operand_size(dd);
			
			do_common_prefix_operand1(dd, do_common_return_operand_size_text(dd));
		}
	}
	
	void do_common_opcode_fpu_rm_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 operand_size, u32 opcode_length)
	{
		u8* p;
		
		dd->operand_size	= operand_size;
		p					= do_common_return_operand_size_text(dd);
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s %s", mnemonic, (s8*)p);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		
		do_common_rm(dd->data_root + opcode_length, dd, _fpu, p);
	}
	
	void do_common_opcode_fpu_hard_stx(u8* data, SDisasmData* dd, u8* mnemonic, u32 reg, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		extract_stx_reg_operand(reg, &dd->operand1);
		extract_stx_reg_operand(*(data + 1) & 0x07, &dd->operand2);
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_fpu_stx_hard(u8* data, SDisasmData* dd, u8* mnemonic, u32 reg, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		extract_stx_reg_operand(*(data + 1) & 0x07, &dd->operand1);
		extract_stx_reg_operand(reg, &dd->operand2);
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_fpu_stx(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		extract_stx_reg_operand(*(data + 1) & 0x07, &dd->operand1);
		dd->opcode_bytes	+= opcode_length;
	}

	void do_common_opcode_r16_m16_16_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r16,m16_16", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;

		do_common_rm(dd->data_root + opcode_length, dd, _16bit | _32bit);
		do_common_prefix_operand1(dd, _m16_16_ptr);
	}
	
	void do_common_opcode_r32_m16_32_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r32,m16_32", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;

		do_common_rm(dd->data_root + opcode_length, dd, _16bit | _32bit);
		do_common_prefix_operand1(dd, _m16_32_ptr);
	}
	
	void do_common_opcode_rm16_rm32_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16; %s r32/m32", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		
		do_common_rm(dd->data_root + opcode_length, dd, _16bit | _32bit);
		if (dd->operand1_source_type == Memory)
		{
			if (hard_operand_size != 0)
				dd->operand_size = hard_operand_size;
			else
				do_common_set_operand_size(dd);
			
			do_common_prefix_operand1(dd, do_common_return_operand_size_text(dd));
		}
	}

	void do_common_opcode_m_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s m", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		
		do_common_rm(dd->data_root + opcode_length, dd, _16bit | _32bit);
		
		if (hard_operand_size != 0)
			dd->operand_size = hard_operand_size;
		else
			do_common_set_operand_size(dd);
		
		if (dd->operand1_source_type != Memory)
		{
			sprintf((s8*)&misc_buffer[0], "%s%s", (s8*)_illegal_ptr, (s8*)do_common_return_operand_size_text(dd));
			do_common_prefix_operand1(dd, &misc_buffer[0]);
		}
		else
			do_common_prefix_operand1(dd, do_common_return_operand_size_text(dd));
	}

	void do_immediate(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op)
	{
		if (rt == _8bit)
		{
			// 8-bit immediate
			sprintf((s8*)&immediate_buffer[0], "%s%u", prefix_op, (int)*data);
			dd->immediate_value	= (u32)*data;
			dd->opcode_bytes	+= 1;
			dd->operand_size	= Byte;
		}
		else
		{
			// 16-bit or 32-bit immediate
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			{
				// 32-bit addressing mode
				sprintf((s8*)&immediate_buffer[0], "%s%u", prefix_op, (int)*(u32*)data);
				dd->immediate_value	= (u32)*(u32*)data;
				dd->opcode_bytes	+= 4;
				dd->operand_size	= Dword;
			}
			else
			{
				// 16-bit addressing mode
				sprintf((s8*)&immediate_buffer[0], "%s%u", prefix_op, (int)*(u16*)data);
				dd->immediate_value	= (u32)*(u16*)data;
				dd->opcode_bytes	+= 2;
				dd->operand_size	= Word;
			}
		}
		// Store the buffer operand
		dd->immediate = &immediate_buffer[0];
	}

	void do_signed_immediate(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op)
	{
		int i;
		
		
		if (rt == _8bit)
		{
			// 8-bit immediate
			i = (int)*data;
			sprintf((s8*)&immediate_buffer[0], "%s%s%i", prefix_op, i < 0 ? _null_string : _plus_string, i);
			dd->immediate_value	= (u32)*data;
			dd->opcode_bytes	+= 1;
			dd->operand_size	= Byte;
		}
		else
		{
			// 16-bit or 32-bit immediate
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			{
				// 32-bit addressing mode
				i = (int)*(u32*)data;
				sprintf((s8*)&immediate_buffer[0], "%s%s%i", prefix_op, i < 0 ? _null_string : _plus_string, i);
				dd->immediate_value	= (u32)*(u32*)data;
				dd->opcode_bytes	+= 4;
				dd->operand_size	= Dword;
			}
			else
			{
				// 16-bit addressing mode
				i = (int)*(u16*)data;
				sprintf((s8*)&immediate_buffer[0], "%s%s%i", prefix_op, i < 0 ? _null_string : _plus_string, i);
				dd->immediate_value	= (u32)*(u16*)data;
				dd->opcode_bytes	+= 2;
				dd->operand_size	= Word;
			}
		}
		// Store the buffer operand
		dd->immediate = &immediate_buffer[0];
	}
	
	int sign_extend_8bit_to_32bits(u8 value)
	{
		// Extract 7th bit, extend it through to the top 24 bits
		return((int)value + ((((int)value & 0x80) >> 7) * 0xffffff00));
	}
	
	int sign_extend_16bits_to_32bits(u16 value)
	{
		// Extract 15th bit, extend it through to the top 16 bits
		return((int)value + ((((int)value & 0x8000) >> 15) * 0xffff0000));
	}
	
	void do_common_swap_operand1_operand2(SDisasmData* dd)
	{
		u8* t			= dd->operand1;
		dd->operand1	= dd->operand2;
		dd->operand2	= t;
		
		u32 tst						= dd->operand1_source_type;
		dd->operand1_source_type	= dd->operand2_source_type;
		dd->operand2_source_type	= tst;
	}
	
	void do_common_prefix_operand1(SDisasmData* dd, u8* prefix)
	{
		sprintf((s8*)&prefix_op1_buffer[0], "%s%s", prefix, dd->operand1);
		dd->operand1 = &prefix_op1_buffer[0];
	}
	
	void do_common_prefix_operand2(SDisasmData* dd, u8* prefix)
	{
		sprintf((s8*)&prefix_op2_buffer[0], "%s%s", prefix, dd->operand2);
		dd->operand2 = &prefix_op2_buffer[0];
	}

	void do_immediate_sign_extend_8bits_to_16_32bit(u8* data, SDisasmData* dd)
	{
		// 16-bit or 32-bit immediate
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit addressing mode
			sprintf((s8*)&immediate_buffer[0], "%u", (int)sign_extend_8bit_to_32bits(*data));
			dd->immediate_value	= (u32)*(u32*)data;
			dd->opcode_bytes	+= 4;
			dd->operand_size	= Dword;
		}
		else
		{
			// 16-bit addressing mode
			sprintf((s8*)&immediate_buffer[0], "%u", (int)(sign_extend_8bit_to_32bits(*data) & 0xffff));
			dd->immediate_value	= (u32)*(u16*)data;
			dd->opcode_bytes	+= 2;
			dd->operand_size	= Word;
		}
		// Store the buffer operand
		dd->immediate = &immediate_buffer[0];
	}

	void do_common_opcode_rm8(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m8,r8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}

	void do_common_opcode_r1632_rm8(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r16/32,r8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm8_reversed(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r8,r/m8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm16_rm32(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,r16; %s r32/m32,r32", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm16_r16(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,r16", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm32_r32(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m32,r32", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_r16_rm16(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r16,r/m16", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_r32_rm32(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r32,r/m32", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_r1632_rm1632(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			do_common_opcode_r32_rm32(dd, mnemonic, opcode_length);
		else
			do_common_opcode_r16_rm16(dd, mnemonic, opcode_length);
	}

	void do_common_opcode_rm1632_m16_1632(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			do_common_opcode_r32_m16_32_one_operand(data, dd, mnemonic, opcode_length);
		}
		else
		{
			do_common_opcode_r16_m16_16_one_operand(data, dd, mnemonic, opcode_length);
		}
	}

	void do_common_opcode_rm16_r16_cl(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,r16,cl", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm32_r32_cl(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m32,r32,cl", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm1632_r1632_cl(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			do_common_opcode_rm32_r32_cl(dd, mnemonic, opcode_length);
		else
			do_common_opcode_rm16_r16_cl(dd, mnemonic, opcode_length);
	}
	
	void do_common_opcode_rm16_rm32_reversed(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r16,r/m16; %s r32,r32/m32", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_r_rm_mmx(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s mm,mm/m64", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_r_rm_xmmx(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s xmm,xmm/m128", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm_r_mmx(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s mm/m64,mm", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm_r_xmmx(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s xmm/m128,xmm", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_mmx_immed8(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s mm/m64,immed8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_xmmx_immed8(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s xmm/m128,immed8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_rm8_immed8(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m8,immed8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _8bit);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}
	
	void do_common_rm8_1(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m8,1", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _8bit);
		dd->immediate		= _1_string;
	}
	
	void do_common_rm8_cl(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m8,cl", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _8bit);
		dd->immediate		= _cl_reg;
	}
	
	void do_common_rm16_32_immed8(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,immed8; %s r32/m32,immed8", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit);
		do_immediate_sign_extend_8bits_to_16_32bit(dd->data_root + dd->opcode_bytes, dd);
	}
	
	void do_common_rm16_32_1(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,1; %s r32/m32,1", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit);
		dd->immediate		= _1_string;
	}
	
	void do_common_rm16_32_cl(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,cl; %s r32/m32,cl", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit);
		dd->immediate		= _cl_reg;
	}
	
	void do_common_rm16_32_immed16_32(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,immed16; %s r32/m32,immed32", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit);
	}
	
	void do_common_accum8_immed8(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s al,immed8", mnemonic);
		dd->comment			= &comment_buffer[0];
		extract_8bit_reg_operand((u8)_accum_low_reg, &dd->operand1);
		dd->opcode_bytes	+= opcode_length;
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}

	void do_common_accum16_32_immed8(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s ax,immed16; %s eax,immed32", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit addressing mode
			extract_32bit_reg_operand((u8)_accum_reg, &dd->operand1);
		}
		else
			extract_16bit_reg_operand((u8)_accum_reg, &dd->operand1);
			
		dd->opcode_bytes += opcode_length;
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit);
	}
	
	void do_common_accum16_32_immed16_32(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s ax,immed8; %s eax,immed8", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit addressing mode
			extract_32bit_reg_operand((u8)_accum_reg, &dd->operand1);
			do_immediate(dd->data_root + dd->opcode_bytes, dd, _32bit);
		}
		else
		{
			extract_16bit_reg_operand((u8)_accum_reg, &dd->operand1);
			do_immediate(dd->data_root + dd->opcode_bytes, dd, _16bit);
		}
	}

	void do_common_mnemonic(SDisasmData* dd, u8* mnemonic, u32 opcode_length, u8* comment, u8* line_comment)
	{
		dd->mnemonic		= mnemonic;
		dd->opcode_bytes	+= opcode_length;
		if (comment)
			dd->comment		= comment;
		if (line_comment)
			dd->line_comment= comment;
	}
	
	void do_common_unknown(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length, u8* comment, u8* line_comment)
	{
		int i;
		u8 opcode_sequence[256];
		u8 buff[256];
		u8 line_buff[256];
		
		// Store the opcode bytes
		for (i=0; i < opcode_length; i++)
			sprintf((s8*)&opcode_sequence[i*3],"%02x ", (int)(dd->data_root + dd->opcode_bytes + i));

		// Create the comments
		sprintf((s8*)&line_buff[0], "; (%s)", (s8*)&opcode_sequence[0]);
		sprintf((s8*)&buff[0], "; UNK - Unknown instruction (%s)", (s8*)&opcode_sequence[0]);
		// Store the instruction
		do_common_mnemonic(dd, mnemonic, opcode_length,
							dd->comment  ? comment      : buff,
							line_comment ? line_comment : line_buff);
	}


	void do_common_operand_size_check_mnemonic(SDisasmData* dd, u32 opcode_length, u8* _16bit_mnemonic, u8* _32bit_mnemonic)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			do_common_mnemonic(dd, _32bit_mnemonic);
		else
			do_common_mnemonic(dd, _16bit_mnemonic);
	}
	
	void do_common_two_prefixes_mnemonic_operand_size_check(SDisasmData* dd, u32 opcode_length, 
															u32 prefix1, u8* mnemonic1,
															u32 prefix2, u8* mnemonic2,
															u8* _16bit_operand,
															u8* _32bit_operand)
	{
		if (dd->prefixes & prefix1)
		{
			dd->mnemonic	= mnemonic1;
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				dd->operand1		= _32bit_operand;
			else
				dd->operand1		= _16bit_operand;
		}
		else if (dd->prefixes & prefix2)
		{
			dd->mnemonic	= mnemonic2;
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				dd->operand1		= _32bit_operand;
			else
				dd->operand1		= _16bit_operand;
		}
		else
		{
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				dd->mnemonic		= _32bit_operand;
			else
				dd->mnemonic		= _16bit_operand;
		}
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_mmx_xmmx_immed8(u8* data, SDisasmData* dd, u8* instruction, u8* comment)
	{
		do_common_opcode_xmmx_immed8(dd, instruction, 0);
		do_common_rm(data, dd, dd->overrides & (u32)Operand ? _xmmx : _mmx);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
		sprintf((s8*)&comment_buffer[0], "%s", (s8*)comment);
	}
	
	void do_common_opcode_mmx_xmmx(u8* data, SDisasmData* dd, u8* instruction, u8* comment)
	{
		do_common_opcode_r_rm_xmmx(dd, instruction, 0);
		do_common_regrm_reversed(data, dd, dd->overrides & (u32)Operand ? _xmmx : _mmx);
		sprintf((s8*)&comment_buffer[0], "%s", (s8*)comment);
		dd->comment = &comment_buffer[0];
	}









//////////
//
// Decode instructions
//
//////////
	void opcode_aaa(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _aaa_instruction);
	}

	void opcode_aad(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _aad_instruction, 2);
	}

	void opcode_aam(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _aam_instruction, 2);
	}

	void opcode_aas(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _aas_instruction);
	}

	void opcode_adc10(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, _adc_instruction);
		do_common_regrm(data + 1, dd, _8bit);
	}

	void opcode_adc11(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _adc_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_adc12(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, _adc_instruction);
		do_common_regrm_reversed(data + 1, dd, _8bit);
	}

	void opcode_adc13(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _add_instruction);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit);
	}

	void opcode_adc_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, _adc_instruction);
	}

	void opcode_adc_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, _adc_instruction);
	}

	void opcode_add00(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, _add_instruction);
		do_common_regrm(data + 1, dd, _8bit);
	}

	void opcode_add01(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _add_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_add02(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, _add_instruction);
		do_common_regrm_reversed(data + 1, dd, _8bit);
	}

	void opcode_add03(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32_reversed(dd, _add_instruction);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit);
	}

	void opcode_add_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, _add_instruction);
	}

	void opcode_add_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, _add_instruction);
	}

	void opcode_adr_size_override(u8* data, SDisasmData* dd)
	{
		dd->opcode_bytes += 1;
		dd->overrides |= Address;
	}

	void opcode_and20(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, _and_instruction);
		do_common_regrm(data + 1, dd, _8bit);
	}

	void opcode_and21(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _and_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_and22(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, _and_instruction);
		do_common_regrm_reversed(data + 1, dd, _8bit);
	}

	void opcode_and23(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _and_instruction);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit);
	}

	void opcode_and_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, _and_instruction);
	}

	void opcode_and_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, _and_instruction);
	}

	void opcode_arpl(u8* data, SDisasmData* dd)
	{
		dd->force_reg = _16bit;
		do_common_opcode_rm16_r16(dd, _arpl_instruction);
		do_common_regrm(data + 1, dd, _16bit);
	}

	void opcode_bound(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, _bound_instruction);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit);
	}

	void opcode_bsf(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, _bsf_instruction);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit);
	}

	void opcode_bsr(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, _bsr_instruction);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit);
	}
	
	void opcode_bswap_xxx(u8* data, SDisasmData* dd)
	{
		dd->mnemonic		= _bswap_instruction;
		extract_32bit_reg_operand(*data & 0x07, &dd->operand1);
		sprintf((s8*)&comment_buffer[0], "bswap %s; byte swap, swaps endian", dd->operand1);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= 1;
	}
	
	void opcode_bt(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, _bt_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_btc(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, _btc_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_btr(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, _btr_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_bts(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, _bts_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_jmp_call_far_operand(u8* data, SDisasmData* dd, u8* instruction)
	{
		int v1, v2;		// Values pulled from opcode encoding
		
		
		do_common_mnemonic(dd, instruction);
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit addressing mode
			v1 = (int)(*(u16*)(data + 5));
			v2 = (int)(*(u32*)(data + 1));
			sprintf((s8*)&operand1_buffer[0], "%04xh:%08xh", v1, v2);
			dd->opcode_bytes += 6;
		}
		else
		{
			// 16-bit addressing mode
			v1 = (int)(*(u16*)(data + 3));
			v2 = (int)(*(u16*)(data + 1));
			sprintf((s8*)&operand1_buffer[0], "%04xh:%04xh", v1, v2);
			dd->opcode_bytes += 4;
		}
		dd->operand1 = &operand1_buffer[0];
		
		// Store additional information in the line comment
		sprintf((s8*)&line_comment_buffer[0], "; %u:%u (base-10)", v1, v2);
		dd->line_comment = &line_comment_buffer[0];
	}

	void opcode_jmp_call_near_relative(u8* data, SDisasmData* dd, u8* instruction)
	{
		do_common_mnemonic(dd, instruction);
		do_signed_immediate(data + 1, dd, _16bit | _32bit);
	}

	void opcode_cbw(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cbw_instruction);
	}

	void opcode_check_reg_0f00(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 0)
		{
			// It's SLDT
			do_common_opcode_rm16_rm32(dd, _sldt_instruction, 0);
			do_common_regrm(data, dd, _16bit, false);
			sprintf((s8*)&comment_buffer[0], "SLDT - Store Local Descriptor Table");
		}
		else if (r == 1)
		{
			// It's STR r/m16
			do_common_opcode_rm16_rm32(dd, _str_instruction, 0);
			do_common_regrm(data, dd, _16bit, false);
			sprintf((s8*)&comment_buffer[0], "STR - Store Task Register");
		}
		else if (r == 2)
		{
			// It's LLDT
			do_common_opcode_rm16_rm32(dd, _lldt_instruction, 0);
			do_common_regrm(data, dd, _16bit, false);
			sprintf((s8*)&comment_buffer[0], "LLDT - Load Local Descriptor Table");
		}
		else if (r == 3)
		{
			// It's LTR
			do_common_opcode_rm16_rm32(dd, _ltr_instruction, 0);
			do_common_regrm(data, dd, _16bit, false);
			sprintf((s8*)&comment_buffer[0], "LTR - Load Task Register");
		}
		else if (r == 4)
		{
			// It's VERR r/m16
			do_common_opcode_rm16_rm32(dd, _verr_instruction, 0);
			do_common_regrm(data, dd, _16bit, false);
			sprintf((s8*)&comment_buffer[0], "VERW - Verify segment for reading");
		}
		else if (r == 5)
		{
			// It's VERW r/m16
			do_common_opcode_rm16_rm32(dd, _verw_instruction, 0);
			do_common_regrm(data, dd, _16bit, false);
			sprintf((s8*)&comment_buffer[0], "VERW - Verify segment for writing");
		}
		else
		{
			// Unused
			do_common_opcode_rm16_rm32(dd, _unk_instruction, 0);
			do_common_regrm(data, dd, _16bit, false);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F 00 /%u) in the class of LLDT, SLDT, LTR, STR, VERR, VERW", r);
		}
		dd->comment = &comment_buffer[0];
	}

	void opcode_check_reg_0f01(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 0)
		{
			// It's SGDT
			do_common_opcode_m_one_operand(data, dd, _sgdt_instruction, _10byte, 0);
			// The fllowing is handled in the do_common_opcode_m_one_operand() function
			//do_common_rm(data, dd, _16bit, false);
			sprintf((s8*)&comment_buffer[0], "SGDT - Store Global Descriptor Table");
		}
		else if (r == 1)
		{
			// It's SIDT
			do_common_opcode_m_one_operand(data, dd, _sidt_instruction, _10byte, 0);
			sprintf((s8*)&comment_buffer[0], "SIDT - Store Interrupt Descriptor Table");
		}
		else if (r == 2)
		{
			// It's LGDT
			do_common_opcode_m_one_operand(data, dd, _lgdt_instruction, _10byte, 0);
			sprintf((s8*)&comment_buffer[0], "LGDT - Load Global Descriptor Table");
		}
		else if (r == 3)
		{
			// It's LIDT
			do_common_opcode_m_one_operand(data, dd, _lidt_instruction, _10byte, 0);
			sprintf((s8*)&comment_buffer[0], "LIDT - Load Interrupt Descriptor Table");
		}
		else if (r == 4)
		{
			// It's SMSW r/m16/32
			do_common_opcode_rm16_rm32_one_operand(data, dd, _smsw_instruction, _16bit, 0);
			sprintf((s8*)&comment_buffer[0], "LMSW - Store Machine Status Word");
		}
		else if (r == 6)
		{
			// It's LMSW r/m16
			do_common_opcode_rm16_one_operand(data, dd, _lmsw_instruction, _16bit, 0);
			sprintf((s8*)&comment_buffer[0], "LMSW - Load Machine Status Word");
		}
		else if (r == 7)
		{
			// It's INVLPG mem
			do_common_opcode_rm16_one_operand(data, dd, _invlpg_instruction, _0bit, 0);
			sprintf((s8*)&comment_buffer[0], "INVLPG - Invalidate TLB Entry");
		}
		else
		{
			// Unused
			do_common_opcode_rm16_rm32(dd, _unk_instruction, 0);
			do_common_regrm(data, dd, _16bit, false);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F 01 /%u) in the class of LGDT, SGDT, LIDT, SIDT, LMSR, SMSW, INVLPG", r);
		}
		dd->comment = &comment_buffer[0];
	}

	void opcode_check_reg_0f71(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 2)
			opcode_psrlw_immed8(data, dd);					// It's PSRLW mm,immed8
		else if (r == 4)
			opcode_psraw_immed8(data, dd);					// It's PSRAW mm,immed8
		else
		{
			// Unused
			if (dd->overrides & (u32)Operand)
			{
				do_common_opcode_xmmx_immed8(dd, _unk_instruction, 0);
				do_common_rm(data, dd, _xmmx);
			}
			else
			{
				do_common_opcode_mmx_immed8(dd, _unk_instruction, 0);
				do_common_rm(data, dd, _mmx);
			}
			do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F 71 /%u) in the class of PSRAW/PSLAW mm,immed8", r);
		}
		dd->comment = &comment_buffer[0];
	}

	void opcode_check_reg_0f72(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 2)
			opcode_psrld_immed8(data, dd);					// It's PSRLD mm,immed8
		else if (r == 4)
			opcode_psrad_immed8(data, dd);					// It's PSRAD mm,immed8
		else
		{
			// Unused
			if (dd->overrides & (u32)Operand)
			{
				do_common_opcode_xmmx_immed8(dd, _unk_instruction, 0);
				do_common_rm(data, dd, _xmmx);
			}
			else
			{
				do_common_opcode_mmx_immed8(dd, _unk_instruction, 0);
				do_common_rm(data, dd, _mmx);
			}
			do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F 72 /%u) in the class of PSRAD/PSRLD mm,immed8", r);
		}
		dd->comment = &comment_buffer[0];
	}

	void opcode_check_reg_0f73(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 2)
			opcode_psrlq_immed8(data, dd);					// It's PSRLQ mm,immed8
		else
		{
			// Unused
			if (dd->overrides & (u32)Operand)
			{
				do_common_opcode_xmmx_immed8(dd, _unk_instruction, 0);
				do_common_rm(data, dd, _xmmx);
			}
			else
			{
				do_common_opcode_mmx_immed8(dd, _unk_instruction, 0);
				do_common_rm(data, dd, _mmx);
			}
			do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F 73 /%u) in the class of PSRLQ mm,immed8", r);
			dd->comment = &comment_buffer[0];
		}
	}

	void opcode_check_reg_0fba(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 4)
			do_common_rm16_32_immed8(data, dd, _bt_instruction);		// It's BT r/m16/32,imm8
		else if (r == 5)
			do_common_rm16_32_immed8(data, dd, _bts_instruction);		// It's BTS r/m16/32,imm8
		else if (r == 6)
			do_common_rm16_32_immed8(data, dd, _btr_instruction);		// It's BTR r/m16/32,imm8
		else if (r == 7)
			do_common_rm16_32_immed8(data, dd, _btc_instruction);		// It's BTC r/m16/32,imm8
		else
		{
			// Unused
			do_common_rm16_32_immed8(data, dd, _unk_instruction, 0);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F ba /%u) in the class of BT, BTS, BTR, BTC r/m16/32,immed8", (int)r);
			dd->comment = &comment_buffer[0];
		}
	}

	void opcode_check_reg_0fc7(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 1)
			opcode_cmpxchg8b(data, dd);					// It's CMPXCHG8B m64
		else
		{
			if (dd->prefixes & (u32)LOCK && *data == 0xc8)
			{
				//  Undocumented instruction "hcf, halt and catch fire"
				// f0 0f c7 c8
				do_common_mnemonic(dd, _hcf_instruction, 1, (u8*)"HCF - Halt and Catch Fire", (u8*)"; Warning! Locks up the cpu");
			}
			else
			{
				// Unused
				do_common_rm16_32_immed8(data, dd, _unk_instruction, 0);
				sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F ba /%u) in the class of BT, BTS, BTR, BTC r/m16/32,immed8", r);
				dd->comment = &comment_buffer[0];
			}
		}
	}

	void opcode_check_reg_80(u8* data, SDisasmData* dd)
	{
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm8_immed8(data, dd, _add_instruction);	// It's ADD r/m8,imm8
		else if (r == 1)
			do_common_rm8_immed8(data, dd, _or_instruction);	// It's OR r/m8,imm8
		else if (r == 2)
			do_common_rm8_immed8(data, dd, _adc_instruction);	// It's ADC r/m8,imm8
		else if (r == 3)
			do_common_rm8_immed8(data, dd, _sbb_instruction);	// It's SBB r/m8,imm8
		else if (r == 4)
			do_common_rm8_immed8(data, dd, _and_instruction);	// It's AND r/m8,imm8
		else if (r == 5)
			do_common_rm8_immed8(data, dd, _sub_instruction);	// It's SUB r/m8,imm8
		else if (r == 6)
			do_common_rm8_immed8(data, dd, _xor_instruction);	// It's XOR r/m8,imm8
		else if (r == 7)
			do_common_rm8_immed8(data, dd, _cmp_instruction);	// It's CMP r/m8,imm8
	}

	void opcode_check_reg_81(u8* data, SDisasmData* dd)
	{
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm16_32_immed16_32(data, dd, _add_instruction);	// It's ADD r/m16/32,imm16/32
		else if (r == 1)
			do_common_rm16_32_immed16_32(data, dd, _or_instruction);	// It's OR r/m16/32,immed16/32
		else if (r == 2)
			do_common_rm16_32_immed16_32(data, dd, _adc_instruction);	// It's ADC r/m16/32,imm16/32
		else if (r == 3)
			do_common_rm16_32_immed16_32(data, dd, _sbb_instruction);	// It's SBB r/m16/32,imm16/32
		else if (r == 4)
			do_common_rm16_32_immed16_32(data, dd, _and_instruction);	// It's AND r/m16/32,imm16/32
		else if (r == 5)
			do_common_rm16_32_immed16_32(data, dd, _sub_instruction);	// It's SUB r/m16/32,imm16/32
		else if (r == 6)
			do_common_rm16_32_immed16_32(data, dd, _xor_instruction);	// It's XOR r/m16/32,imm16/32
		else if (r == 7)
			do_common_rm16_32_immed16_32(data, dd, _cmp_instruction);	// It's CMP r/m16/32,imm16/32
	}

	void opcode_check_reg_82(u8* data, SDisasmData* dd)
	{ // 82
		// Unused
		do_common_unknown(data, dd, _unk_instruction, 1);
	}

	void opcode_check_reg_83(u8* data, SDisasmData* dd)
	{
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm16_32_immed8(data, dd, _add_instruction);	// It's ADD r/m16/32,imm8
		else if (r == 1)
			do_common_rm16_32_immed8(data, dd, _or_instruction);	// It's OR r/m16/32,immed8
		else if (r == 2)
			do_common_rm16_32_immed8(data, dd, _adc_instruction);	// It's ADC r/m16/32,imm8
		else if (r == 3)
			do_common_rm16_32_immed8(data, dd, _sbb_instruction);	// It's SBB r/m16/32,imm8
		else if (r == 4)
			do_common_rm16_32_immed8(data, dd, _and_instruction);	// It's AND r/m16/32,imm8
		else if (r == 5)
			do_common_rm16_32_immed8(data, dd, _sub_instruction);	// It's SUB r/m16/32,imm8
		else if (r == 6)
			do_common_rm16_32_immed8(data, dd, _xor_instruction);	// It's XOR r/m16/32,imm8
		else if (r == 7)
			do_common_rm16_32_immed8(data, dd, _cmp_instruction);	// It's CMP r/m16/32,imm8
	}

	void opcode_check_reg_8f(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_opcode_rm16_rm32_one_operand(data, dd, _pop_instruction);	// It's POP rm16/32
		else
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (8f /%u) in the class of POP m16/32", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
	}

	void opcode_check_reg_c0(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm8_immed8(data, dd, _rol_instruction);	// It's ROL rm8,imm8
		else if (r == 1)
			do_common_rm8_immed8(data, dd, _ror_instruction);	// It's ROR rm8,imm8
		else if (r == 2)
			do_common_rm8_immed8(data, dd, _rcl_instruction);	// It's RCL rm8,imm8
		else if (r == 3)
			do_common_rm8_immed8(data, dd, _rcr_instruction);	// It's RCR rm8,imm8
		else if (r == 4)
			do_common_rm8_immed8(data, dd, _shl_instruction);	// It's SHL rm8,imm8
		else if (r == 5)
			do_common_rm8_immed8(data, dd, _shr_instruction);	// It's SHR rm8,imm8
		else if (r == 7)
			do_common_rm8_immed8(data, dd, _sar_instruction);	// It's SAR rm8,imm8
		else
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (c0 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR rm8,immed8", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
	}

	void opcode_check_reg_c1(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm16_32_immed8(data, dd, _rol_instruction);	// It's ROL rm16/32,imm8
		else if (r == 1)
			do_common_rm16_32_immed8(data, dd, _ror_instruction);	// It's ROR rm16/32,imm8
		else if (r == 2)
			do_common_rm16_32_immed8(data, dd, _rcl_instruction);	// It's RCL rm16/32,imm8
		else if (r == 3)
			do_common_rm16_32_immed8(data, dd, _rcr_instruction);	// It's RCR rm16/32,imm8
		else if (r == 4)
			do_common_rm16_32_immed8(data, dd, _shl_instruction);	// It's SHL rm16/32,imm8
		else if (r == 5)
			do_common_rm16_32_immed8(data, dd, _shr_instruction);	// It's SHR rm16/32,imm8
		else if (r == 6)
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (c1 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR m16/32", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
		else if (r == 7)
			do_common_rm16_32_immed8(data, dd, _sar_instruction);	// It's SAR rm16/32,imm8
	}

	void opcode_check_reg_c6(u8* data, SDisasmData* dd)
	{
		u8 buff[0];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm8_immed8(data, dd, _mov_instruction);	// It's MOV rm8,imm8
		else
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (c6 /%u) in the class of MOV rm8,imm8", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
	}

	void opcode_check_reg_c7(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm16_32_immed16_32(data, dd, _mov_instruction);	// It's mov rm/16/32,imm16/32
		else if (r == 1)
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (c7 /%u) in the class of MOV rm16/32,immed16/32", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
	}

	void opcode_check_reg_d0(u8* data, SDisasmData* dd)
	{
		u8 buff[0];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm8_1(data, dd, _rol_instruction);	// It's ROL rm8,1
		else if (r == 1)
			do_common_rm8_1(data, dd, _ror_instruction);	// It's ROR rm8,1
		else if (r == 2)
			do_common_rm8_1(data, dd, _rcl_instruction);	// It's RCL rm8,1
		else if (r == 3)
			do_common_rm8_1(data, dd, _rcl_instruction);	// It's RCR rm8,1
		else if (r == 4)
			do_common_rm8_1(data, dd, _shl_instruction);	// It's SHL rm8,1
		else if (r == 5)
			do_common_rm8_1(data, dd, _shr_instruction);	// It's SHR rm8,1
		else if (r == 6)
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (d0 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR rm8,1", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
		else if (r == 7)
			do_common_rm8_1(data, dd, _sar_instruction);	// It's SAR rm8,1
	}

	void opcode_check_reg_d1(u8* data, SDisasmData* dd)
	{
		u8 buff[0];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm16_32_1(data, dd, _rol_instruction);	// It's ROL rm16/32,1
		else if (r == 1)
			do_common_rm16_32_1(data, dd, _ror_instruction);	// It's ROR rm16/32,1
		else if (r == 2)
			do_common_rm16_32_1(data, dd, _rcl_instruction);	// It's RCL rm16/32,1
		else if (r == 3)
			do_common_rm16_32_1(data, dd, _rcr_instruction);	// It's RCR rm16/32,1
		else if (r == 4)
			do_common_rm16_32_1(data, dd, _shl_instruction);	// It's SHL rm16/32,1
		else if (r == 5)
			do_common_rm16_32_1(data, dd, _shr_instruction);	// It's SHR rm16/32,1
		else if (r == 6)
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (d1 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR rm16/32,1", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
		else if (r == 7)
			do_common_rm16_32_1(data, dd, _sar_instruction);	// It's SAR rm16/32,1
	}

	void opcode_check_reg_d2(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm8_cl(data, dd, _rol_instruction);		// It's ROL rm8,cl
		else if (r == 1)
			do_common_rm8_cl(data, dd, _rol_instruction);		// It's ROR rm8,cl
		else if (r == 2)
			do_common_rm8_cl(data, dd, _rcl_instruction);		// It's RCL rm8,cl
		else if (r == 3)
			do_common_rm8_cl(data, dd, _rcr_instruction);		// It's RCR rm8,cl
		else if (r == 4)
			do_common_rm8_cl(data, dd, _shl_instruction);		// It's SHL rm8,cl
		else if (r == 5)
			do_common_rm8_cl(data, dd, _shr_instruction);		// It's SHR rm8,cl
		else if (r == 6)
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (d2 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR rm8,cl", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
		else if (r == 7)
			do_common_rm8_cl(data, dd, _sar_instruction);		// It's SAR rm8,cl
	}

	void opcode_check_reg_d3(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm16_32_cl(data, dd, _rol_instruction);	// It's ROL rm16/32,cl
		else if (r == 1)
			do_common_rm16_32_cl(data, dd, _ror_instruction);	// It's ROR rm16/32,cl
		else if (r == 2)
			do_common_rm16_32_cl(data, dd, _rcl_instruction);	// It's RCL rm16/32,cl
		else if (r == 3)
			do_common_rm16_32_cl(data, dd, _rcr_instruction);	// It's RCR rm16/32,cl
		else if (r == 4)
			do_common_rm16_32_cl(data, dd, _shl_instruction);	// It's SHL rm16/32,cl
		else if (r == 5)
			do_common_rm16_32_cl(data, dd, _shr_instruction);	// It's SHR rm16/32,cl
		else if (r == 6)
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (d2 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR rm16/32,cl", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
		else if (r == 7)
			do_common_rm16_32_cl(data, dd, _sar_instruction);	// It's SAR rm16/32,cl
	}

	void opcode_check_reg_f6(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm8_immed8(data, dd, _test_instruction);				// It's TEST rm8,imm8
		else if (r == 1)
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (f6 /%u) in the class of TEST, NOT, NEG, MUL, IMUL, DIV, IDIV rm8", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
		else if (r == 2)
			do_common_opcode_rm8_one_operand(data, dd, _not_instruction);	// It's NOT rm8
		else if (r == 3)
			do_common_opcode_rm8_one_operand(data, dd, _neg_instruction);	// It's NEG rm8
		else if (r == 4)
			do_common_opcode_rm8_one_operand(data, dd, _mul_instruction);	// It's MUL rm8
		else if (r == 5)
			do_common_opcode_rm8_one_operand(data, dd, _imul_instruction);	// It's IMUL rm8
		else if (r == 6)
			do_common_opcode_rm8_one_operand(data, dd, _div_instruction);	// It's DIV rm8
		else if (r == 7)
			do_common_opcode_rm8_one_operand(data, dd, _idiv_instruction);	// It's IDIV rm8
	}

	void opcode_check_reg_f7(u8* data, SDisasmData* dd)
	{
		u8 buff[0];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm16_32_immed16_32(data, dd, _test_instruction);				// It's TEST rm16/32,imm16/32
		else if (r == 1)
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (f7 /%u) in the class of TEST, NOT, NEG, MUL, IMUL, DIV, IDIV rm16/32,immed16/32", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
		else if (r == 2)
			do_common_opcode_rm16_rm32_one_operand(data, dd, _neg_instruction);		// It's NEG rm16/32
		else if (r == 3)
			do_common_opcode_rm16_rm32_one_operand(data, dd, _neg_instruction);		// It's NOT rm16/32
		else if (r == 4)
			do_common_opcode_rm16_rm32_one_operand(data, dd, _neg_instruction);		// It's MUL rm16/32
		else if (r == 5)
			do_common_opcode_rm16_rm32_one_operand(data, dd, _imul_instruction);	// It's IMUL rm16/32
		else if (r == 6)
			do_common_opcode_rm16_rm32_one_operand(data, dd, _div_instruction);		// It's DIV rm16/32
		else if (r == 7)
			do_common_opcode_rm16_rm32_one_operand(data, dd, _idiv_instruction);	// It's IDIV rm16/32
	}

	void opcode_check_reg_fe(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_opcode_rm8_one_operand(data, dd, _inc_instruction);	// It's INC rm8
		else if (r == 1)
			do_common_opcode_rm8_one_operand(data, dd, _dec_instruction);	// It's DEC rm8
		else
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (fe /%u) in the class of INC, DEC rm8", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
	}
	
	void opcode_jmp_call_rm1632_absolute_indirect(u8* data, SDisasmData* dd, u8* instruction)
	{
		do_common_mnemonic(dd, instruction);
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Address) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Address) != 0))
		{
			// 32-bit addressing mode
			extract_modrm_32bit_address_mode(data + 1, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2,
											 dd->overrides & (u32)Operand ? _16bit    : _32bit, false, 
											 dd->overrides & (u32)Operand ? _word_ptr : _dword_ptr);
		}
		else
		{
			// 16-bit addressing mode
			extract_modrm_16bit_address_mode(data + 1, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2,
											 dd->overrides & (u32)Operand ? _32bit     : _16bit, false,
											 dd->overrides & (u32)Operand ? _dword_ptr : _word_ptr);
		}
	}
	
	void opcode_jmp_call_m16_m1632_absolute_indirect(u8* data, SDisasmData* dd, u8* instruction)
	{
		do_common_mnemonic(dd, instruction);
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Address) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Address) != 0))
		{
			// 32-bit addressing mode
			extract_modrm_32bit_address_mode(data + 1, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2,
											 dd->overrides & (u32)Operand ? _16bit    : _32bit, false, 
											 dd->overrides & (u32)Operand ? _word_ptr : _dword_ptr);
		}
		else
		{
			// 16-bit addressing mode
			extract_modrm_16bit_address_mode(data + 1, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2,
											 dd->overrides & (u32)Operand ? _32bit     : _16bit, false,
											 dd->overrides & (u32)Operand ? _dword_ptr : _word_ptr);
		}
	}

	void opcode_check_reg_ff(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_opcode_rm16_rm32_one_operand(data, dd, _inc_instruction);			// It's INC rm16/32
		else if (r == 1)
			do_common_opcode_rm16_rm32_one_operand(data, dd, _dec_instruction);			// It's DEC rm16/32
		else if (r == 2)
			opcode_jmp_call_rm1632_absolute_indirect(data, dd, _call_instruction);		// It's CALL rm16/32 absolute
		else if (r == 3)
			opcode_jmp_call_m16_m1632_absolute_indirect(data, dd, _call_instruction);	// It's CALL m16_m16/32 absolute
		else if (r == 4)
			opcode_jmp_call_rm1632_absolute_indirect(data, dd, _jmp_instruction);		// It's JMP m16_m16/32 absolute
		else if (r == 5)
			opcode_jmp_call_m16_m1632_absolute_indirect(data, dd, _jmp_instruction);	// It's JMP FAR m16_m16/32 absolute
		else if (r == 6)
			do_common_opcode_rm16_rm32_one_operand(data, dd, _push_instruction);		// It's PUSH rm16/32
		else if (r == 7)
		{
			// Unused
			sprintf((s8*)&buff[0], "UNK - Unknown instruction (ff /%u) in the class of INC, DEC rm16/32, CALL/JMP rm16/32, CALL/JMP m16_m16/32", (int)r);
			do_common_mnemonic(dd, _unk_instruction, 2, &buff[0]);
		}
	}

	void opcode_clc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _clc_instruction);
	}

	void opcode_cld(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cld_instruction);
	}

	void opcode_cli(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cli_instruction);
	}

	void opcode_clts(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _clts_instruction);
	}

	void opcode_cmc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmc_instruction);
	}

	void opcode_cmova(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmova_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovc_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovg(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovg_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovl(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovl_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovna(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovna_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovnc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovnc_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovng(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovng_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovnl(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovnl_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovno(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovno_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovns(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovns_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovnz(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovnz_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovo(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovo_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovpe(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovpe_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovpo(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovpo_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovs(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovs_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_cmovz(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmovz_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}
	
	void opcode_cmp38(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, _cmp_instruction);
		do_common_regrm(data + 1, dd, _8bit);
	}

	void opcode_cmp39(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32_reversed(dd, _cmp_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_cmp3a(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, _cmp_instruction);
		do_common_regrm_reversed(data + 1, dd, _8bit);
	}

	void opcode_cmp3b(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _cmp_instruction);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit);
	}

	void opcode_cmp3c(u8* data, SDisasmData* dd)
	{
		do_common_accum8_immed8(data, dd, _cmp_instruction);
	}

	void opcode_cmp3d(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, _cmp_instruction);
	}

	void opcode_cmpsb(u8* data, SDisasmData* dd)
	{
		if (dd->prefixes & REPE)
		{
			dd->mnemonic	= (u8*)"repe";
			dd->operand1	= (u8*)"cmpsb";
		}
		else if (dd->prefixes & REPNE)
		{
			dd->mnemonic	= (u8*)"repne";
			dd->operand1	= (u8*)"cmpsb";
		}
		else
		{
			dd->mnemonic	= (u8*)"cmpsb";
		}
		dd->opcode_bytes	+= 1;
	}

	void opcode_cmpsw(u8* data, SDisasmData* dd)
	{
		do_common_two_prefixes_mnemonic_operand_size_check(dd, 1, 
															REPE,	_repe_instruction,
															REPNE,	_repne_instruction,
															_cmpsw_instruction,
															_cmpsd_instruction);
	}

	void opcode_cmpxchg(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmpxchg_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit);
	}

	void opcode_cmpxchg_byte(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmpxchg_instruction, 0);
		do_common_regrm(data, dd, _8bit);
	}

	void opcode_cmpxchg8b(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cmpxchg8b_instruction, 0);
		do_common_rm(data, dd, _16bit | _32bit);
	}

	void opcode_cpuid(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cpuid_instruction);
	}

	void opcode_cs_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= CSREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_cwd(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _cwd_instruction);
	}

	void opcode_daa(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _daa_instruction);
	}

	void opcode_das(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _das_instruction);
	}

	void opcode_dec_xxx(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _dec_instruction);
		extract_gp_reg_operand(dd, *data & 0x07, &dd->operand1, _16bit | _32bit);
	}
	
	void opcode_ds_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= DSREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_emms(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _emms_instruction);
	}

	void opcode_enter(u8* data, SDisasmData* dd)
	{
		sprintf((s8*)&operand1_buffer[0], "%u", (int)(*(u16*)(data + 1)));
		sprintf((s8*)&operand2_buffer[0], "%u", (int)(*(u8*)(data + 3)));
		dd->mnemonic		= (u8*)"enter";
		dd->operand1		= &operand1_buffer[0];
		dd->operand2		= &operand2_buffer[0];
		dd->opcode_bytes	+= 4;
	}

	void opcode_es_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= ESREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_fpu_d8(u8* data, SDisasmData* dd)
	{
		asm("int3");
		u8 rm = *(data + 1);
		
		
		if (rm >= 0xc0 && rm <= 0xc7)
			do_common_opcode_fpu_hard_stx(data, dd, _fadd_instruction, 0);		// It's FADD st(0),st(i)
		else if (rm >= 0xc8 && rm <= 0xcf)
			do_common_opcode_fpu_hard_stx(data, dd, _fmul_instruction, 0);		// It's FMUL st(0),st(i)
		else if (rm >= 0xd0 && rm <= 0xd7)
			do_common_opcode_fpu_hard_stx(data, dd, _fcom_instruction, 0);		// It's FCOM st(0),st(i)
		else if (rm >= 0xd8 && rm <= 0xdf)
			do_common_opcode_fpu_hard_stx(data, dd, _fcomp_instruction, 0);		// It's FCOMP st(0),st(i)
		else if (rm >= 0xe0 && rm <= 0xe7)
			do_common_opcode_fpu_hard_stx(data, dd, _fsub_instruction, 0);		// It's FSUB st(0),st(i)
		else if (rm >= 0xe8 && rm <= 0xef)
			do_common_opcode_fpu_hard_stx(data, dd, _fsubr_instruction, 0);		// It's FSUBR st(0),st(i)
		else if (rm >= 0xf0 && rm <= 0xf7)
			do_common_opcode_fpu_hard_stx(data, dd, _fdiv_instruction, 0);		// It's FDIV st(0),st(i)
		else if (rm >= 0xf8 && rm <= 0xff)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FDIVR st(0),st(i)


		// It wasn't one of the st0/sti instructions, so we check the reg bits
		rm = (rm >> 3) & 0x07;
		if (rm == 0)
			do_common_opcode_fpu_rm_one_operand(data, dd, _fadd_instruction, _f32);		// It's FADD real4
		else if (rm == 1)
			do_common_opcode_fpu_rm_one_operand(data, dd, _fmul_instruction, _f32);		// It's FMUL real4
		else if (rm == 2)
			do_common_opcode_fpu_rm_one_operand(data, dd, _fcom_instruction, _f32);		// It's FCOM real4
		else if (rm == 3)
			do_common_opcode_fpu_rm_one_operand(data, dd, _fcomp_instruction, _f32);	// It's FCOMP real4
		else if (rm == 4)
			do_common_opcode_fpu_rm_one_operand(data, dd, _fsub_instruction, _f32);		// It's FSUB real4
		else if (rm == 5)
			do_common_opcode_fpu_rm_one_operand(data, dd, _fsubr_instruction, _f32);	// It's FSUBR real4
		else if (rm == 6)
			do_common_opcode_fpu_rm_one_operand(data, dd, _fdiv_instruction, _f32);		// It's FDIV real4
		else if (rm == 7)
			do_common_opcode_fpu_rm_one_operand(data, dd, _fdivr_instruction, _f32);	// It's FDIVR real4
	}

	void opcode_fpu_d9(u8* data, SDisasmData* dd)
	{
		asm("int3");
		u8 rm = *(data + 1);
		
		if (rm >= 0xc0 && rm <= 0xc7)
			do_common_opcode_fpu_stx(data, dd, _fld_instruction);		// It's FLD st(i)
		else if (rm >= 0xc8 && rm <= 0xcf)
			do_common_opcode_fpu_stx(data, dd, _fxch_instruction);		// It's FXCH st(i)
		else if (rm == 0xd0)
			do_common_mnemonic(dd, _fnop_instruction);		// fnop
		else if (rm == 0xe0)
			do_common_mnemonic(dd, _fchs_instruction);		// fchs
		else if (rm == 0xe1)
			do_common_mnemonic(dd, _fabs_instruction);		// fabs
		else if (rm == 0xe4)
			do_common_mnemonic(dd, _ftst_instruction);		// ftst
		else if (rm == 0xe5)
			do_common_mnemonic(dd, _fxam_instruction);		// fxam
		else if (rm == 0xe8)
			do_common_mnemonic(dd, _fld1_instruction);		// fld1
		else if (rm == 0xe9)
			do_common_mnemonic(dd, _fld2t_instruction);		// fldl2t
		else if (rm == 0xea)
			do_common_mnemonic(dd, _fld2e_instruction);		// fldl2e
		else if (rm == 0xeb)
			do_common_mnemonic(dd, _fldpi_instruction);		// fldpi
		else if (rm == 0xec)
			do_common_mnemonic(dd, _fldlg2_instruction);	// fldlg2
		else if (rm == 0xed)
			do_common_mnemonic(dd, _fldln2_instruction);	// fldln2
		else if (rm == 0xee)
			do_common_mnemonic(dd, _fldz_instruction);		// fldz
		else if (rm == 0xf0)
			do_common_mnemonic(dd, _f2xm1_instruction);		// f2xm1
		else if (rm == 0xf1)
			do_common_mnemonic(dd, _fyl2x_instruction);		// fyl2x
		else if (rm == 0xf2)
			do_common_mnemonic(dd, _fptan_instruction);		// fptan
		else if (rm == 0xf3)
			do_common_mnemonic(dd, _fpatan_instruction);	// fpatan
		else if (rm == 0xf4)
			do_common_mnemonic(dd, _fxtract_instruction);	// fxtract
		else if (rm == 0xf5)
			do_common_mnemonic(dd, _fprem1_instruction);	// fprem1
		else if (rm == 0xf6)
			do_common_mnemonic(dd, _fdecstp_instruction);	// fdecstp
		else if (rm == 0xf7)
			do_common_mnemonic(dd, _fincstp_instruction);	// fincstp
		else if (rm == 0xf8)
			do_common_mnemonic(dd, _fprem_instruction);		// fprem
		else if (rm == 0xf9)
			do_common_mnemonic(dd, _fyl2xp1_instruction);	// fyl2xp1
		else if (rm == 0xfa)
			do_common_mnemonic(dd, _fsqrt_instruction);		// fsqrt
		else if (rm == 0xfb)
			do_common_mnemonic(dd, _fsincos_instruction);	// fsincos
		else if (rm == 0xfc)
			do_common_mnemonic(dd, _frndint_instruction);	// frndint
		else if (rm == 0xfd)
			do_common_mnemonic(dd, _fscale_instruction);	// fscale
		else if (rm == 0xfe)
			do_common_mnemonic(dd, _fsin_instruction);		// fsin
		else if (rm == 0xff)
			do_common_mnemonic(dd, _fcos_instruction);		// fcos
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fadd_instruction, _f32);		// It's FLD real4
			else if (rm == 2)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fst_instruction, _f32);		// It's FST real4
			else if (rm == 3)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fstp_instruction, _f32);		// It's FSTP real4
			else if (rm == 4)
			{
				// fldenv
				if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
					(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				{
					// 32-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, _fldenv_instruction, _m28byte);
				}
				else
				{
					// 16-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, _fldenv_instruction, _m14byte);
				}
			}
			else if (rm == 5)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fldcw_instruction, _16bit);		// It's fldcw m16
			else if (rm == 6)
			{
				// fnstenv
				if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
					(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				{
					// 32-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, _fnstenv_instruction, _m28byte);
				}
				else
				{
					// 16-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, _fnstenv_instruction, _m14byte);
				}
			}
			else if (rm == 7)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fnstcw_instruction, _16bit);		// It's fnstcw m16
			else
				do_common_unknown(data, dd, (u8*)"FUNK", 2, (u8*)"FUNK - Floating point unknown instruction");
		}
	}

	void opcode_fpu_da(u8* data, SDisasmData* dd)
	{
		asm("int3");
		u8 rm = *(data + 1);

		if (rm >= 0xc0 && rm <= 0xc7)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FCMOVB st0,sti
		else if (rm >= 0xc8 && rm <= 0xcf)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FCMOVZ st0,sti
		else if (rm >= 0xd0 && rm <= 0xd7)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FCMOVNG st0,sti
		else if (rm >= 0xd8 && rm <= 0xdf)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FCMOVPO st0,sti
		else if (rm == 0xe9)
			do_common_mnemonic(dd, _fucompp_instruction);							// It's FUCOMPP
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fiadd_instruction, _s32);	// It's FIADD m32_int
			else if (rm == 1)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fimul_instruction, _s32);	// It's FIMUL m32_int
			else if (rm == 2)
				do_common_opcode_fpu_rm_one_operand(data, dd, _ficom_instruction, _s32);	// It's FICOM m32_int
			else if (rm == 3)
				do_common_opcode_fpu_rm_one_operand(data, dd, _ficomp_instruction, _s32);	// It's FICOMP m32_int
			else if (rm == 4)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fisub_instruction, _s32);	// It's FISUB m32_int
			else if (rm == 5)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fisubr_instruction, _s32);	// It's FISUBR m32_int
			else if (rm == 6)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fidiv_instruction, _s32);	// It's FIDIV m32_int
			else if (rm == 7)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fidivr_instruction, _s32);	// It's FIDIVR m32_int
		}
	}

	void opcode_fpu_db(u8* data, SDisasmData* dd)
	{
		asm("int3");
		u8 rm = *(data + 1);


		if (rm >= 0xc0 && rm <= 0xc7)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FCMOVNB st0,sti
		else if (rm >= 0xc8 && rm <= 0xcf)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FCMOVNZ st0,sti
		else if (rm >= 0xd0 && rm <= 0xd7)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FCMOVG st0,sti
		else if (rm >= 0xd8 && rm <= 0xdf)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FCMOVPE st0,sti
		else if (rm == 0xe2)
			do_common_mnemonic(dd, _fnclex_instruction);							// It's fnclex
		else if (rm == 0xe3)
			do_common_mnemonic(dd, _fninit_instruction);							// It's fninit
		else if (rm >= 0xe8 && rm <= 0xef)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FUCOMI st(0),st(i)
		else if (rm >= 0xf0 && rm <= 0xf7)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FCOMI st(0),st(i)
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fild_instruction, _s32);		// It's FILD m32_int
			else if (rm == 2)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fist_instruction, _s32);		// It's FIST m32_int
			else if (rm == 3)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fistp_instruction, _s32);	// It's FISTP m32_int
			else if (rm == 5)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fld_instruction, _f80);		// It's FLD real10
			else if (rm == 7)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fstp_instruction, _f80);		// It's FSTP real10
			else
				do_common_unknown(data, dd, (u8*)"FUNK", 2, (u8*)"FUNK - Floating point unknown instruction");
		}
	}

	void opcode_fpu_dc(u8* data, SDisasmData* dd)
	{
		asm("int3");
		u8 rm = *(data + 1);
		
		if (rm >= 0xc0 && rm <= 0xc7)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FADD st(i),st(0)
		else if (rm >= 0xc8 && rm <= 0xcf)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FMUL st(i),st(0)
		else if (rm >= 0xe0 && rm <= 0xe7)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FSUBR st(i),st(0)
		else if (rm >= 0xe8 && rm <= 0xef)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FSUB st(i),st(0)
		else if (rm >= 0xf0 && rm <= 0xf7)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FDIVR st(i),st(0)
		else if (rm >= 0xf8 && rm <= 0xff)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FDIV st(i),st(0)
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fadd_instruction, _f64);		// It's FADD real8
			else if (rm == 1)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fmul_instruction, _f64);		// It's FMUL real8
			else if (rm == 2)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fcom_instruction, _f64);		// It's FCOM real8
			else if (rm == 3)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fcomp_instruction, _f64);	// It's FCOMP real8
			else if (rm == 4)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fsub_instruction, _f64);		// It's FSUB real8
			else if (rm == 5)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fsubr_instruction, _f64);	// It's FSUBR real8
			else if (rm == 6)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fdiv_instruction, _f64);		// It's FDIV real8
			else if (rm == 7)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fdivr_instruction, _f64);	// It's FDIVR real8
		}
	}

	void opcode_fpu_dd(u8* data, SDisasmData* dd)
	{
		asm("int3");
		u8 rm = *(data + 1);
		
		if (rm >= 0xc0 && rm <= 0xc7)
			do_common_opcode_fpu_stx(data, dd, _fld_instruction);		// It's FFREE st(i)
		else if (rm >= 0xd0 && rm <= 0xd7)
			do_common_opcode_fpu_stx(data, dd, _fld_instruction);		// It's FST st(i)
		else if (rm >= 0xd8 && rm <= 0xdf)
			do_common_opcode_fpu_stx(data, dd, _fld_instruction);		// It's FSTP st(i)
		else if (rm >= 0xe0 && rm <= 0xe7)
			do_common_opcode_fpu_stx(data, dd, _fld_instruction);		// It's FUCOM st(i)
		else if (rm >= 0xe8 && rm <= 0xef)
			do_common_opcode_fpu_stx(data, dd, _fld_instruction);		// It's FUCOMP st(i)
		else if (rm == 0xe9)
			do_common_mnemonic(dd, _fucomp_instruction);				// It's FUCOMP
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fld_instruction, _f64);		// It's FLD real8
			else if (rm == 2)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fst_instruction, _f64);		// It's FST real8
			else if (rm == 3)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fstp_instruction, _f64);		// It's FSTP real8
			else if (rm == 4)
			{
				// frstor
				if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
					(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				{
					// 32-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, _frstor_instruction, _m108byte);
				}
				else
				{
					// 16-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, _frstor_instruction, _m94byte);
				}
			}
			else if (rm == 6)
			{
				// fnsave
				if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
					(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				{
					// 32-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, _fnsave_instruction, _m108byte);
				}
				else
				{
					// 16-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, _fnsave_instruction, _m94byte);
				}
			}
			else if (rm == 7)
				do_common_mnemonic(dd, _fnstsw_instruction);		// It's FNSTSW
			else
				do_common_unknown(data, dd, (u8*)"FUNK", 2, (u8*)"FUNK - Floating point unknown instruction");
		}
	}

	void opcode_fpu_de(u8* data, SDisasmData* dd)
	{
		asm("int3");
		u8 rm = *(data + 1);


		if (rm >= 0xc0 && rm <= 0xc7)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FADDP st(i),st(0)
		else if (rm >= 0xc8 && rm <= 0xcf)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FMULP st(i),st(0)
		else if (rm == 0xd9)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FCOMPP
		else if (rm >= 0xe0 && rm <= 0xe7)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FSUBRP st(i),st(0)
		else if (rm >= 0xe8 && rm <= 0xef)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FSUBP st(i),st(0)
		else if (rm >= 0xf0 && rm <= 0xf7)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FDIVRP st(i),st(0)
		else if (rm >= 0xf8 && rm <= 0xff)
			do_common_opcode_fpu_stx_hard(data, dd, _fdivr_instruction, 0);		// It's FDIVP st(i),st(0)
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fiadd_instruction, _s64);	// It's FIADD m64_int
			else if (rm == 1)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fimul_instruction, _s64);	// It's FIMUL m16_int
			else if (rm == 2)
				do_common_opcode_fpu_rm_one_operand(data, dd, _ficom_instruction, _s16);	// It's FICOM m16_int
			else if (rm == 3)
				do_common_opcode_fpu_rm_one_operand(data, dd, _ficomp_instruction, _s16);	// It's FICOMP m16_int
			else if (rm == 4)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fisub_instruction, _s16);	// It's FISUB m16_int
			else if (rm == 5)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fisubr_instruction, _s16);	// It's FISUBR m16_int
			else if (rm == 6)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fidiv_instruction, _s16);	// It's FIDIV m16_int
			else if (rm == 7)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fidivr_instruction, _s16);	// It's FIDIVR m16_int
		}
	}

// Undocumented instructions
// FFREEP performs FFREE ST(i) and pop stack
// DF 1101 1111 1100 0REG (6)
// http://www.pagetable.com/?p=16
	void opcode_fpu_df(u8* data, SDisasmData* dd)
	{
		asm("int3");
		u8 v;
		u8 rm = *(data + 1);


		if (rm >= 0xc0 && rm <= 0xc7)
			do_common_opcode_fpu_stx(data, dd, _fld_instruction);		// FFREEP st(i)
		else if (rm == 0xe0)
		{ // It's FNSTSW ax
			asm("int3");
			v = _accum_reg;
			do_common_opcode_fpu_rm_one_operand((u8*)&v, dd, _fnstsw_instruction, _16bit);
		}
		else if (rm >= 0xe8 && rm <= 0xef)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FUCOMIP st(0),st(i)
		else if (rm >= 0xf0 && rm <= 0xf7)
			do_common_opcode_fpu_hard_stx(data, dd, _fdivr_instruction, 0);		// It's FCOMIP st(0),st(i)
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fild_instruction, _s16);		// It's FILD m16_int
			else if (rm == 2)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fist_instruction, _s16);		// It's FIST m16_int
			else if (rm == 3)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fistp_instruction, _s16);	// It's FISTP m16_int
			else if (rm == 4)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fbld_instruction, _m80);		// It's fbld m80_bcd
			else if (rm == 5)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fild_instruction, _s64);		// It's FILD m64_int
			else if (rm == 6)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fbstp_instruction, _m80);	// It's fbstp m80_bcd
			else if (rm == 7)
				do_common_opcode_fpu_rm_one_operand(data, dd, _fistp_instruction, _s64);	// It's FISTP m64_int
			else
				do_common_unknown(data, dd, (u8*)"FUNK", 2, (u8*)"FUNK - Floating point unknown instruction");
		}
	}

	void opcode_fs_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= FSREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_gs_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= GSREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_hlt(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _hlt_instruction);
	}

	void opcode_imul_rm8(u8* data, SDisasmData* dd)
	{ // f6
		do_common_opcode_rm8_one_operand(data, dd, _imul_instruction);
	}

	void opcode_imul_rm1632(u8* data, SDisasmData* dd)
	{ // f7
		do_common_opcode_rm16_rm32_one_operand(data, dd, _imul_instruction);
	}

	void opcode_imulaf(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _imul_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_imul_3_parms_immed16_32(u8* data, SDisasmData* dd)
	{ // 69
		do_common_opcode_rm1632_r1632_cl(dd, _imul_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit);
	}

	void opcode_imul_3_parms_immed8(u8* data, SDisasmData* dd)
	{ // 68
		do_common_opcode_rm1632_r1632_cl(dd, _imul_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}

	void opcode_in(u8* data, SDisasmData* dd)
	{ // ed
		do_common_mnemonic(dd, _in_instruction);
		dd->operand1	= _al_reg;
		extract_gp_reg_operand(dd, _data_reg, &dd->operand2, _16bit | _32bit);
	}

	void opcode_in16_32_immed8(u8* data, SDisasmData* dd)
	{ // e5
		do_common_mnemonic(dd, _in_instruction);
		extract_gp_reg_operand(dd, _accum_reg, &dd->operand2, _16bit | _32bit);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}

	void opcode_in8_immed8(u8* data, SDisasmData* dd)
	{ // e4
		do_common_mnemonic(dd, _in_instruction);
		dd->operand1	= _al_reg;
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}

	void opcode_in_byte(u8* data, SDisasmData* dd)
	{ // ec
		do_common_mnemonic(dd, _in_instruction);
		dd->operand1	= _al_reg;
		dd->operand2	= _dx_reg;
	}

	void opcode_inc_xxx(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _inc_instruction);
		extract_gp_reg_operand(dd, *data & 0x07, &dd->operand1, _16bit | _32bit);
	}
	void opcode_insb(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _insb_instruction);
	}

	void opcode_insw(u8* data, SDisasmData* dd)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			do_common_mnemonic(dd, _insd_instruction);
		else
			do_common_mnemonic(dd, _insw_instruction);
	}

	void opcode_int3(u8* data, SDisasmData* dd)
	{ // cc
		do_common_mnemonic(dd, _int3_instruction);
	}

	void opcode_into(u8* data, SDisasmData* dd)
	{ // ce
		do_common_mnemonic(dd,_into_instruction);
	}

	void opcode_intx(u8* data, SDisasmData* dd)
	{ // cd 
		sprintf((s8*)&operand1_buffer[0], "0x%x", (int)*(data + 1));
		dd->operand1		= &operand1_buffer[0];
		do_common_mnemonic(dd, _int_instruction, 2);
	}

	void opcode_invd(u8* data, SDisasmData* dd)
	{ // 0f 08
		do_common_mnemonic(dd, _invd_instruction);
	}

	void opcode_iret(u8* data, SDisasmData* dd)
	{ // cf
		do_common_mnemonic(dd, _iret_instruction);
	}
	

	void opcode_ja(u8* data, SDisasmData* dd)
	{ // 70
		opcode_xxx_rel8(data, dd, _ja_instruction);
	}

	void opcode_ja_l(u8* data, SDisasmData* dd)
	{ // 0f 80
		opcode_xxx_rel16(data, dd, _ja_instruction);
	}

	void opcode_jc(u8* data, SDisasmData* dd)
	{ // 72
		opcode_xxx_rel8(data, dd, _jc_instruction);
	}

	void opcode_jc_l(u8* data, SDisasmData* dd)
	{ // 0f 82
		opcode_xxx_rel16(data, dd, _jc_instruction);
	}

	void opcode_jcxz(u8* data, SDisasmData* dd)
	{ // e3
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			
			opcode_xxx_rel8(data, dd, _jecxz_instruction);		// 32-bit addressing mode
		else
			opcode_xxx_rel8(data, dd, _jcxz_instruction);		// 16-bit addressing mode
	}

	void opcode_jg(u8* data, SDisasmData* dd)
	{ // 7f
		opcode_xxx_rel8(data, dd, _jg_instruction);
	}

	void opcode_jg_l(u8* data, SDisasmData* dd)
	{ // 0f 8f
		opcode_xxx_rel16(data, dd, _jg_instruction);
	}

	void opcode_jl(u8* data, SDisasmData* dd)
	{ // 0f 7c
		opcode_xxx_rel8(data, dd, _jl_instruction);
	}

	void opcode_jl_l(u8* data, SDisasmData* dd)
	{ // 0f 8c
		opcode_xxx_rel16(data, dd, _jl_instruction);
	}

	void opcode_jmp16_32(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32_one_operand(data, dd, _jmp_instruction);
	}

	void opcode_jmp8(u8* data, SDisasmData* dd)
	{
		opcode_xxx_rel8(data, dd, _jmp_instruction);
	}

	void opcode_call_near_relative(u8* data, SDisasmData* dd)
	{
		opcode_jmp_call_near_relative(data, dd, _call_instruction);
	}

	void opcode_call_far_operand(u8* data, SDisasmData* dd)
	{
		opcode_jmp_call_far_operand(data, dd, _call_instruction);
	}

	void opcode_jmp_far(u8* data, SDisasmData* dd)
	{
		opcode_jmp_call_far_operand(data, dd, _jmp_instruction);
	}
	
	void opcode_xxx_rel8(u8* data, SDisasmData* dd, u8* instruction)
	{
		do_common_mnemonic(dd, instruction, 1);
		do_immediate(data + 1, dd, _8bit);
	}
	
	void opcode_xxx_rel16(u8* data, SDisasmData* dd, u8* instruction)
	{
		do_common_mnemonic(dd, instruction, 2);
		do_immediate(data + 2, dd, _16bit);
	}

	void opcode_jna(u8* data, SDisasmData* dd)
	{ // 76
		opcode_xxx_rel8(data, dd, _jna_instruction);
	}

	void opcode_jna_l(u8* data, SDisasmData* dd)
	{ // 0f 86
		opcode_xxx_rel16(data, dd, _jna_instruction);
	}

	void opcode_jnc(u8* data, SDisasmData* dd)
	{ // 73
		opcode_xxx_rel8(data, dd, _jnc_instruction);
	}

	void opcode_jnc_l(u8* data, SDisasmData* dd)
	{ // 0f 83
		opcode_xxx_rel16(data, dd, _jnc_instruction);
	}

	void opcode_jng(u8* data, SDisasmData* dd)
	{ // 7e
		opcode_xxx_rel8(data, dd, _jng_instruction);
	}

	void opcode_jng_l(u8* data, SDisasmData* dd)
	{ // 0f 8e
		opcode_xxx_rel16(data, dd, _jng_instruction);
	}

	void opcode_jnl(u8* data, SDisasmData* dd)
	{ // 7d
		opcode_xxx_rel8(data, dd, _jnl_instruction);
	}

	void opcode_jnl_l(u8* data, SDisasmData* dd)
	{ // 0f 8d
		opcode_xxx_rel16(data, dd, _jnl_instruction);
	}

	void opcode_jno(u8* data, SDisasmData* dd)
	{ // 7a
		opcode_xxx_rel8(data, dd, _jno_instruction);
	}

	void opcode_jno_l(u8* data, SDisasmData* dd)
	{ // 81
		opcode_xxx_rel16(data, dd, _jno_instruction);
	}

	void opcode_jns(u8* data, SDisasmData* dd)
	{ // 79
		opcode_xxx_rel8(data, dd, _jns_instruction);
	}

	void opcode_jns_l(u8* data, SDisasmData* dd)
	{ // 0f 89
		opcode_xxx_rel16(data, dd, _jns_instruction);
	}

	void opcode_jnz(u8* data, SDisasmData* dd)
	{ // 75
		opcode_xxx_rel8(data, dd, _jnz_instruction);
	}

	void opcode_jnz_l(u8* data, SDisasmData* dd)
	{ // 0f 85
		opcode_xxx_rel16(data, dd, _jnz_instruction);
	}

	void opcode_jo(u8* data, SDisasmData* dd)
	{ // 70
		opcode_xxx_rel8(data, dd, _jo_instruction);
	}

	void opcode_jo_l(u8* data, SDisasmData* dd)
	{ // 0f 80
		opcode_xxx_rel16(data, dd, _jo_instruction);
	}

	void opcode_jpe(u8* data, SDisasmData* dd)
	{ // 7a
		opcode_xxx_rel8(data, dd, _jpe_instruction);
	}

	void opcode_jpe_l(u8* data, SDisasmData* dd)
	{ // 0f 8a
		opcode_xxx_rel16(data, dd, _jpe_instruction);
	}

	void opcode_jpo(u8* data, SDisasmData* dd)
	{ // 7b
		opcode_xxx_rel8(data, dd, _jpo_instruction);
	}

	void opcode_jpo_l(u8* data, SDisasmData* dd)
	{ // 0f 8b
		opcode_xxx_rel16(data, dd, _jpo_instruction);
	}

	void opcode_js(u8* data, SDisasmData* dd)
	{ // 78
		opcode_xxx_rel8(data, dd, _js_instruction);
	}

	void opcode_js_l(u8* data, SDisasmData* dd)
	{ // 0f 78
		opcode_xxx_rel16(data, dd, _js_instruction);
	}

	void opcode_jz(u8* data, SDisasmData* dd)
	{ // 74
		opcode_xxx_rel8(data, dd, _jz_instruction);
	}

	void opcode_jz_l(u8* data, SDisasmData* dd)
	{ // 0f 84
		opcode_xxx_rel16(data, dd, _jz_instruction);
	}

	void opcode_lahf(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _lahf_instruction);
	}

	void opcode_lar(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, _lar_instruction);
	}

	void opcode_lds(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm1632_m16_1632(data, dd, _lds_instruction);
	}

	void opcode_lea(u8* data, SDisasmData* dd)
	{ // 8d
		do_common_opcode_rm16_rm32_reversed(dd, _lea_instruction);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_leave(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _leave_instruction);
	}

	void opcode_les(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm1632_m16_1632(data, dd, _les_instruction);
	}

	void opcode_lfs(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm1632_m16_1632(data, dd, _lfs_instruction);
	}

	void opcode_lgs(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm1632_m16_1632(data, dd, _lgs_instruction);
	}
	
	void opcode_icebp(u8* data, SDisasmData* dd)
	{ // f1
		do_common_mnemonic(dd, _icebp_instruction);
		dd->line_comment = (u8*)"; Undocumented instruction";
	}

	void opcode_lock_prefix(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= LOCK;
		dd->opcode_bytes	+= 1;
	}

	void opcode_lodsb(u8* data, SDisasmData* dd)
	{
		if (dd->prefixes & REPE)
		{
			dd->mnemonic	= (u8*)"repe";
			dd->operand1	= (u8*)"lodsb";
		}
		else if (dd->prefixes & REPNE)
		{
			dd->mnemonic	= (u8*)"repne";
			dd->operand1	= (u8*)"lodsb";
		}
		else
		{
			dd->mnemonic	= (u8*)"lodsb";
		}
		dd->opcode_bytes	+= 1;
	}

	void opcode_lodsw(u8* data, SDisasmData* dd)
	{
		do_common_two_prefixes_mnemonic_operand_size_check(dd, 1, 
															REPE,	_repe_instruction,
															REPNE,	_repne_instruction,
															_lodsw_instruction,
															_lodsd_instruction);
	}

	void opcode_loop(u8* data, SDisasmData* dd)
	{ // e2
		opcode_xxx_rel8(data, dd, _loop_instruction);
	}

	void opcode_loope(u8* data, SDisasmData* dd)
	{ // e1
		opcode_xxx_rel8(data, dd, _loope_instruction);
	}

	void opcode_loopne(u8* data, SDisasmData* dd)
	{ // e0
		opcode_xxx_rel8(data, dd, _loopne_instruction);
	}

	void opcode_lsl(u8* data, SDisasmData* dd)
	{ // 0f 03
		do_common_opcode_rm16_rm32_reversed(dd, _lsl_instruction);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_lss(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm1632_m16_1632(data, dd, _lss_instruction);
	}

	void opcode_mov_accum_mem_16_32(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, _mov_instruction);
	}

	void opcode_mov_accum_mem_8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm8(dd, _mov_instruction);
	}

	void opcode_mov_gp_control(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _gp_reg, _control_reg);
	}

	void opcode_mov_gp_debug(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _gp_reg, _debug_reg);
	}

	void opcode_mov_gp_test(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _gp_reg, _test_reg);
	}

	void opcode_mov_control_gp(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _control_reg, _gp_reg);
	}

	void opcode_mov_debug_gp(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _debug_reg, _gp_reg);
	}

	void opcode_mov_test_gp(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _test_reg, _gp_reg);
	}

	void opcode_mov_mem_accum_16_32(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_mov_mem_accum_8(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_mov_reg16_32_sreg(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _gp_reg, _segment_reg);
	}

	void opcode_mov_reg_immed16_32(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_mov_reg_immed8(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_mov_reg_rm_16_32(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_mov_reg_rm_8(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_mov_rm_reg_16_32(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_mov_rm_reg_8(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_mov_sreg_reg16_32(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _segment_reg, _gp_reg);
	}

	void opcode_movd_gp_mmx(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _gp_reg, _mmx_reg);
	}

	void opcode_movd_mmx_gp(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _mmx_reg, _gp_reg);
	}

	void opcode_movq_mm_mmx_mmx(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_movq_mmx_mm_mmx(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_movsb(u8* data, SDisasmData* dd)
	{
		if (dd->prefixes & REPE)
		{
			dd->mnemonic	= (u8*)"repe";
			dd->operand1	= (u8*)"movsb";
		}
		else if (dd->prefixes & REPNE)
		{
			dd->mnemonic	= (u8*)"repne";
			dd->operand1	= (u8*)"movsb";
		}
		else
		{
			dd->mnemonic	= (u8*)"movsb";
		}
		dd->opcode_bytes	+= 1;
	}

	void opcode_movsw(u8* data, SDisasmData* dd)
	{
		do_common_two_prefixes_mnemonic_operand_size_check(dd, 1, 
															REPE,	_repe_instruction,
															REPNE,	_repne_instruction,
															_movsw_instruction,
															_movsd_instruction);
	}

	void opcode_movsx_byte(u8* data, SDisasmData* dd)
	{ // 0f be
		do_common_opcode_r1632_rm8(dd, _movsx_instruction);
		do_common_regrm(data, dd, _16bit | _32bit);
		do_common_adjust_register_size(dd->operand2, _8bit);
	}

	void opcode_movsx_word(u8* data, SDisasmData* dd)
	{ // 0f bf
		do_common_opcode_r1632_rm8(dd, _movsx_instruction);
		do_common_regrm(data, dd, _32bit);
		do_common_adjust_register_size(dd->operand2, _16bit);
	}

	void opcode_movzx_byte(u8* data, SDisasmData* dd)
	{ // 0f b6
		do_common_opcode_r1632_rm8(dd, _movzx_instruction);
		do_common_regrm(data, dd, _16bit | _32bit);
		do_common_adjust_register_size(dd->operand2, _8bit);
	}

	void opcode_movzx_word(u8* data, SDisasmData* dd)
	{ // 0f b7
		do_common_opcode_r1632_rm8(dd, _movzx_instruction);
		do_common_regrm(data, dd, _32bit);
		do_common_adjust_register_size(dd->operand2, _16bit);
	}

	void opcode_nop(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _nop_instruction);
	}

	void opcode_op_size_override(u8* data, SDisasmData* dd)
	{
		dd->overrides		|= Operand;
		dd->opcode_bytes	+= 1;
	}

	void opcode_or_accum0c(u8* data, SDisasmData* dd)
	{ // 0c
		do_common_accum8_immed8(data, dd, _or_instruction);
	}

	void opcode_or_accum0d(u8* data, SDisasmData* dd)
	{ // 0d
		do_common_accum16_32_immed16_32(data, dd, _or_instruction);
	}

	void opcode_or_rm08(u8* data, SDisasmData* dd)
	{ // 08
		do_common_opcode_rm8(dd, _or_instruction);
		do_common_regrm(data, dd, _8bit);
	}

	void opcode_or_rm09(u8* data, SDisasmData* dd)
	{ // 09
		do_common_opcode_rm16_rm32(dd, _or_instruction);
		do_common_regrm(data, dd, _16bit | _32bit);
	}

	void opcode_or_rm0a(u8* data, SDisasmData* dd)
	{ // 0a
		do_common_opcode_rm8_reversed(dd, _or_instruction);
		do_common_regrm(data, dd, _8bit);
	}

	void opcode_or_rm0b(u8* data, SDisasmData* dd)
	{ // 0b
		do_common_opcode_rm16_rm32_reversed(dd, _or_instruction);
		do_common_regrm_reversed(data, dd, _16bit | _32bit);
	}

	void opcode_or_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, _or_instruction);
	}

	void opcode_or_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, _or_instruction);
	}

	void opcode_or_rm16_32_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed8(data, dd, _or_instruction);
	}

	void opcode_oute7(u8* data, SDisasmData* dd)
	{ // e7
		do_common_mnemonic(dd, _in_instruction);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit);
		dd->operand1	= dd->immediate;
		dd->immediate	= NULL;
		extract_gp_reg_operand(dd, _accum_reg, &dd->operand2, _16bit | _32bit);
	}

	void opcode_oute6(u8* data, SDisasmData* dd)
	{ // e6
		do_common_mnemonic(dd, _in_instruction);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
		dd->operand1	= dd->immediate;
		dd->immediate	= NULL;
		extract_gp_reg_operand(dd, _accum_reg, &dd->operand2, _8bit);
	}

	void opcode_outee(u8* data, SDisasmData* dd)
	{ // ee
		do_common_mnemonic(dd, _in_instruction);
		dd->operand1	= _dx_reg;
		extract_gp_reg_operand(dd, _accum_reg, &dd->operand2, _8bit);
	}

	void opcode_outef(u8* data, SDisasmData* dd)
	{ // ef
		do_common_mnemonic(dd, _in_instruction);
		dd->operand1	= _dx_reg;
		extract_gp_reg_operand(dd, _accum_reg, &dd->operand2, _16bit | _32bit);
	}

	void opcode_outsb(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _outsb_instruction);
	}

	void opcode_outsw(u8* data, SDisasmData* dd)
	{
		do_common_operand_size_check_mnemonic(dd, 1, _outsw_instruction, _outsd_instruction);
	}

	void opcode_packssdw(u8* data, SDisasmData* dd)
	{ // 0f 63
		do_common_opcode_mmx_xmmx(data, dd, _packssdw_instruction, (u8*)"PACKSSDW - Pack dwords into with words with signed saturation");
	}

	void opcode_packsswb(u8* data, SDisasmData* dd)
	{ // 0f 6b
		do_common_opcode_mmx_xmmx(data, dd, _packsswb_instruction, (u8*)"PACKSSWB - Pack words into with bytes with signed saturation");
	}

	void opcode_packuswb(u8* data, SDisasmData* dd)
	{ // 0f 67
		do_common_opcode_mmx_xmmx(data, dd, _packuswb_instruction, (u8*)"PACKUSWB - Pack words into with bytes with unsigned saturation");
	}

	void opcode_paddb(u8* data, SDisasmData* dd)
	{ // 0f fc
		do_common_opcode_mmx_xmmx(data, dd, _paddb_instruction, (u8*)"PADDB - Packed add bytes");
	}

	void opcode_paddd(u8* data, SDisasmData* dd)
	{ // 0f fe
		do_common_opcode_mmx_xmmx(data, dd, _paddd_instruction, (u8*)"PADDD - Packed add dwords");
	}

	void opcode_paddsb(u8* data, SDisasmData* dd)
	{ // 0f ec
		do_common_opcode_mmx_xmmx(data, dd, _paddsb_instruction, (u8*)"PADDSB - Packed add signed integer bytes");
	}

	void opcode_paddsw(u8* data, SDisasmData* dd)
	{ // 0f ed
		do_common_opcode_mmx_xmmx(data, dd, _paddsb_instruction, (u8*)"PADDSW - Packed add signed integer words");
	}

	void opcode_paddusb(u8* data, SDisasmData* dd)
	{ // 0f dc
		do_common_opcode_mmx_xmmx(data, dd, _paddusb_instruction, (u8*)"PADDUSB - Packed add unsigned integer bytes");
	}

	void opcode_paddusw(u8* data, SDisasmData* dd)
	{ // 0f dd
		do_common_opcode_mmx_xmmx(data, dd, _paddusw_instruction, (u8*)"PADDUSW - Packed add unsigned integer words");
	}

	void opcode_paddw(u8* data, SDisasmData* dd)
	{ // 0f fd
		do_common_opcode_mmx_xmmx(data, dd, _paddw_instruction, (u8*)"PADDW - Packed add words");
	}

	void opcode_pand(u8* data, SDisasmData* dd)
	{ // 0f db
		do_common_opcode_mmx_xmmx(data, dd, _pand_instruction, (u8*)"PAND - Packed logical AND");
	}

	void opcode_pandn(u8* data, SDisasmData* dd)
	{ // 0f df
		do_common_opcode_mmx_xmmx(data, dd, _pandn_instruction, (u8*)"PANDN - Packed logical NOT on first operand, then AND");
	}

	void opcode_pcmpeqb(u8* data, SDisasmData* dd)
	{ // 0f 74
		do_common_opcode_mmx_xmmx(data, dd, _pcmpeqb_instruction, (u8*)"PCMPEQB - Packed compare equality bytes");
	}

	void opcode_pcmpeqd(u8* data, SDisasmData* dd)
	{ // 0f 76
		do_common_opcode_mmx_xmmx(data, dd, _pcmpeqd_instruction, (u8*)"PCMPEQD - Packed compare equality dwords");
	}

	void opcode_pcmpeqw(u8* data, SDisasmData* dd)
	{ // 0f 75
		do_common_opcode_mmx_xmmx(data, dd, _pcmpeqw_instruction, (u8*)"PCMPEQW - Packed compare equality words");
	}

	void opcode_pcmpgtb(u8* data, SDisasmData* dd)
	{ // 0f 64
		do_common_opcode_mmx_xmmx(data, dd, _pcmpgtb_instruction, (u8*)"PCMPGTB - Packed compare greater than signed bytes");
	}

	void opcode_pcmpgtd(u8* data, SDisasmData* dd)
	{ // 0f 66
		do_common_opcode_mmx_xmmx(data, dd, _pcmpgtd_instruction, (u8*)"PCMPGTD - Packed compare greater than signed dwords");
	}

	void opcode_pcmpgtw(u8* data, SDisasmData* dd)
	{ // 0f 65
		do_common_opcode_mmx_xmmx(data, dd, _pcmpgtw_instruction, (u8*)"PCMPGTW - Packed compare greater than signed words");
	}

	void opcode_pmaddwd(u8* data, SDisasmData* dd)
	{ // 0f f5
		do_common_opcode_mmx_xmmx(data, dd, _pmaddwd_instruction, (u8*)"PMADDWD - Packed multiply-add signed words");
	}

	void opcode_pmulhw(u8* data, SDisasmData* dd)
	{ // 0f e5
		do_common_opcode_mmx_xmmx(data, dd, _pmulhw_instruction, (u8*)"PMULHW - Packed multiply signed word integers, store high result");
	}

	void opcode_pmullw(u8* data, SDisasmData* dd)
	{ // 0f d5
		do_common_opcode_mmx_xmmx(data, dd, _pmullw_instruction, (u8*)"PMULLW - Packed multiply signed word integers, store low result");
	}

	void opcode_pop_ds(u8* data, SDisasmData* dd)
	{
		dd->operand1		= _ds_reg;
		do_common_mnemonic(dd, _pop_instruction);
	}

	void opcode_pop_es(u8* data, SDisasmData* dd)
	{
		dd->operand1		= _es_reg;
		do_common_mnemonic(dd, _pop_instruction);
	}

	void opcode_pop_fs(u8* data, SDisasmData* dd)
	{
		dd->operand1		= _fs_reg;
		do_common_mnemonic(dd, _pop_instruction);
	}

	void opcode_pop_gs(u8* data, SDisasmData* dd)
	{
		dd->operand1		= _gs_reg;
		do_common_mnemonic(dd, _pop_instruction);
	}

	void opcode_pop_ss(u8* data, SDisasmData* dd)
	{
		dd->operand1		= _ss_reg;
		do_common_mnemonic(dd, _pop_instruction);
	}

	void opcode_pop_xreg(u8* data, SDisasmData* dd)
	{
		extract_gp_reg_operand(dd, *data & 0x07, &dd->operand1, _16bit | _32bit);
		do_common_mnemonic(dd, _pop_instruction);
	}

	void opcode_popa(u8* data, SDisasmData* dd)
	{
		do_common_operand_size_check_mnemonic(dd, 1, _popa_instruction, _popad_instruction);
	}

	void opcode_popf(u8* data, SDisasmData* dd)
	{
		do_common_operand_size_check_mnemonic(dd, 1, _popf_instruction, _popfd_instruction);
	}

	void opcode_por(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _por_instruction, (u8*)"POR - Packed logical OR");
	}

	void opcode_pslld(u8* data, SDisasmData* dd)
	{ // 0f f2
		do_common_opcode_mmx_xmmx(data, dd, _pslld_instruction, (u8*)"PSLLD - Packed shift left logical dwords");
	}

	void opcode_psllq(u8* data, SDisasmData* dd)
	{ // 0f f3
		do_common_opcode_mmx_xmmx(data, dd, _psllq_instruction, (u8*)"PSLLQ - Packed shift left logical qwords");
	}

	void opcode_psllw(u8* data, SDisasmData* dd)
	{ // 0f f1
		do_common_opcode_mmx_xmmx(data, dd, _psllw_instruction, (u8*)"PSLLW - Packed shift left logical words");
	}

	u8 _psrad_comment[] = "PSRAD - Shift Packed Data Right Arithmetic Dword";
	void opcode_psrad_immed8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx_immed8(data, dd, _psrad_instruction, _psrad_comment);
	}

	void opcode_psrad(u8* data, SDisasmData* dd)
	{ // 0f e2
		do_common_opcode_mmx_xmmx(data, dd, _psrad_instruction, _psrad_comment);
	}

	u8 _psraw_comment[] = "PSRAW - Shift Packed Data Right Arithmetic Word";
	void opcode_psraw_immed8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx_immed8(data, dd, _psraw_instruction, _psraw_comment);
	}

	void opcode_psraw(u8* data, SDisasmData* dd)
	{ // 0f e1
		do_common_opcode_mmx_xmmx(data, dd, _psraw_instruction, _psraw_comment);
	}

	u8 _psrld_comment[] = "PSLRD - Shift Packed Data Right Logical Dword";
	void opcode_psrld_immed8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx_immed8(data, dd, _psrld_instruction, _psrld_comment);
	}

	void opcode_psrld(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _psrld_instruction, _psrld_comment);
	}

	u8 _psrlq_comment[] = "PSLRQ - Shift Packed Data Right Logical Qword";
	void opcode_psrlq_immed8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx_immed8(data, dd, _psrlq_instruction, _psrlq_comment);
	}

	void opcode_psrlq(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _psrlq_instruction, _psrlq_comment);
	}

	u8 _psrlw_comment[] = "PSLRQ - Shift Packed Data Right Logical Word";
	void opcode_psrlw_immed8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx_immed8(data, dd, _psrlw_instruction, _psrlw_comment);
	}

	void opcode_psrlw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _psrlw_instruction, _psrlw_comment);
	}

	void opcode_psubb(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _psubb_instruction, (u8*)"PSUBB - Subtract packed bytes");
	}

	void opcode_psubd(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _psubd_instruction, (u8*)"PSUBD - Subtract packed dwords");
	}

	void opcode_psubsb(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _psubsb_instruction, (u8*)"PSUBSB - Subtract packed signed bytes with signed saturation");
	}

	void opcode_psubsw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _psubsw_instruction, (u8*)"PSUBSW - Subtract packed signed words with signed saturation");
	}

	void opcode_psubusb(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _psubusb_instruction, (u8*)"PSUBUSB - Subtract packed unsigned bytes with unsigned saturation");
	}

	void opcode_psubusw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _psubusw_instruction, (u8*)"PSUBUSW - Subtract packed unsigned words with unsigned saturation");
	}

	void opcode_psubw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _psubw_instruction, (u8*)"PSUBW - Subtract packed words");
	}

	void opcode_punpckhbw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _punpckhbw_instruction, (u8*)"PUNPCKHBW- Unpack high data, bytes to words");
	}

	void opcode_punpckhdq(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _punpckhdq_instruction, (u8*)"PUNPCKHDQ - Unpack high data, dwords to qwords");
	}

	void opcode_punpckhwd(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _punpckhwd_instruction, (u8*)"PUNPCKHWD - Unpack high data, words to dwords");
	}

	void opcode_punpcklbw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _punpcklbw_instruction, (u8*)"PUNPCKLBW- Unpack low data, bytes to words");
	}

	void opcode_punpckldq(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _punpckldq_instruction, (u8*)"PUNPCKLDQ- Unpack low data, dwords to qwords");
	}

	void opcode_punpcklwd(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, _punpcklwd_instruction, (u8*)"PUNPCKLWD- Unpack low data, words to dwords");
	}

	void opcode_push_cs(u8* data, SDisasmData* dd)
	{
		dd->operand1		= _cs_reg;
		do_common_mnemonic(dd, _push_instruction);
	}

	void opcode_push_ds(u8* data, SDisasmData* dd)
	{
		dd->operand1		= _ds_reg;
		do_common_mnemonic(dd, _push_instruction);
	}

	void opcode_push_es(u8* data, SDisasmData* dd)
	{
		dd->operand1		= _es_reg;
		do_common_mnemonic(dd, _push_instruction);
	}

	void opcode_push_fs(u8* data, SDisasmData* dd)
	{
		dd->operand1		= _fs_reg;
		do_common_mnemonic(dd, _push_instruction);
	}

	void opcode_push_gs(u8* data, SDisasmData* dd)
	{
		dd->operand1		= _gs_reg;
		do_common_mnemonic(dd, _push_instruction);
	}

	void opcode_push_immed16_32(u8* data, SDisasmData* dd)
	{ // 68
		u16 v1;
		u32 v2;
		
		do_common_mnemonic(dd, _push_instruction);
		
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit addressing mode
			v2 = *(u32*)(data + 1);
			sprintf((s8*)&line_comment_buffer[0], "; dword 0x%04x (%u)", (int)v2, (int)v2);
			do_immediate(data + 1, dd, _32bit);
		}
		else
		{
			// 16-bit addressing mode
			v1 = *(u16*)(data + 1);
			v2 = sign_extend_16bits_to_32bits(v1);
			sprintf((s8*)&line_comment_buffer[0], "; word 0x%04x (%u) pushed as dword 0x%08x (%u)", (int)v1, (int)v1, (int)v2, (int)v2);
			do_immediate(data + 1, dd, _16bit);
		}
		dd->line_comment = &line_comment_buffer[0];
	}

	void opcode_push_immed8(u8* data, SDisasmData* dd)
	{ // 6a
		u8 v1;
		u32 v2;
		
		do_common_mnemonic(dd, _push_instruction);
		
		v1 = *(data + 1);
		v2 = sign_extend_8bit_to_32bits(v1);
		sprintf((s8*)&line_comment_buffer[0], "; byte 0x%02x (%u) pushed as dword %08x (%u)", (int)v1, (int)v1, (int)v2, (int)v2);
		dd->line_comment = &line_comment_buffer[0];
		
		do_immediate(data + 1, dd, _8bit);
	}

	void opcode_push_ss(u8* data, SDisasmData* dd)
	{
		dd->operand1		= _ss_reg;
		do_common_mnemonic(dd, _push_instruction);
	}

	void opcode_push_xreg(u8* data, SDisasmData* dd)
	{
		extract_gp_reg_operand(dd, *data & 0x07, &dd->operand1, _16bit | _32bit);
		do_common_mnemonic(dd, _push_instruction);
	}

	void opcode_pusha(u8* data, SDisasmData* dd)
	{
		do_common_operand_size_check_mnemonic(dd, 1, _pusha_instruction, _pushad_instruction);
	}

	void opcode_pushf(u8* data, SDisasmData* dd)
	{
		do_common_operand_size_check_mnemonic(dd, 1, _pushf_instruction, _pushfd_instruction);
	}

	void opcode_pxor(u8* data, SDisasmData* dd)
	{ // 0f ef
		do_common_opcode_mmx_xmmx(data, dd, _pxor_instruction, (u8*)"PXOR - Packed logical exclusive OR");
	}

	void opcode_rdmsr(u8* data, SDisasmData* dd)
	{ // 
		do_common_mnemonic(dd, _rdmsr_instruction);
	}

	void opcode_rdpmc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _rdpmc_instruction);
	}

	void opcode_rdtsc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _rdtsc_instruction);
	}

	void opcode_repe_prefix(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= REPE;
		dd->opcode_bytes	+= 1;
	}

	void opcode_repne_prefix(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= REPNE;
		dd->opcode_bytes	+= 1;
	}

	void opcode_retf(u8* data, SDisasmData* dd)
	{ // cb
		do_common_mnemonic(dd, _retf_instruction);
	}

	void opcode_retf_immed(u8* data, SDisasmData* dd)
	{ // ca iw
		do_common_mnemonic(dd, _retf_instruction);
		do_immediate(data + 1, dd, _16bit);
	}

	void opcode_retn(u8* data, SDisasmData* dd)
	{ // c3
		do_common_mnemonic(dd, _retn_instruction);
	}

	void opcode_retn_immed(u8* data, SDisasmData* dd)
	{ // c2 iw
		do_common_mnemonic(dd, _retn_instruction);
		do_immediate(data + 1, dd, _16bit);
	}

	void opcode_rsm(u8* data, SDisasmData* dd)
	{ // 0f aa
		do_common_mnemonic(dd, _rsm_instruction, 2);
	}

	void opcode_sahf(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _sahf_instruction);
	}

	void opcode_sbb_accum_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, _sbb_instruction);
	}

	void opcode_sbb_accum_immed8(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed8(data, dd, _sbb_instruction);
	}

	void opcode_sbb18(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, _sbb_instruction);
		do_common_regrm(data + 1, dd, _8bit);
	}

	void opcode_sbb19(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _sbb_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_sbb1a(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, _sbb_instruction);
		do_common_regrm_reversed(data + 1, dd, _8bit);
	}

	void opcode_sbb1b(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _sbb_instruction);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit);
	}

	void opcode_sbb_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, _sbb_instruction);
	}

	void opcode_sbb_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, _sbb_instruction);
	}

	void opcode_sbb_rm16_32_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed8(data, dd, _sbb_instruction);
	}

	void opcode_scasb(u8* data, SDisasmData* dd)
	{
		if (dd->prefixes & REPE)
		{
			dd->mnemonic	= (u8*)"repe";
			dd->operand1	= (u8*)"scasb";
		}
		else if (dd->prefixes & REPNE)
		{
			dd->mnemonic	= (u8*)"repne";
			dd->operand1	= (u8*)"scasb";
		}
		else
		{
			dd->mnemonic	= (u8*)"scasb";
		}
		dd->opcode_bytes	+= 1;
	}

	void opcode_scasw(u8* data, SDisasmData* dd)
	{
		do_common_two_prefixes_mnemonic_operand_size_check(dd, 1, 
															REPE,	_repe_instruction,
															REPNE,	_repne_instruction,
															_scasw_instruction,
															_scasd_instruction);
	}

	void opcode_seta(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _seta_instruction);
	}

	void opcode_setc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setc_instruction);
	}

	void opcode_setg(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setg_instruction);
	}

	void opcode_setl(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setl_instruction);
	}

	void opcode_setna(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setna_instruction);
	}

	void opcode_setnc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setnc_instruction);
	}

	void opcode_setng(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setng_instruction);
	}

	void opcode_setnl(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setnl_instruction);
	}

	void opcode_setno(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setno_instruction);
	}

	void opcode_setns(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setns_instruction);
	}

	void opcode_setnz(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setnz_instruction);
	}

	void opcode_seto(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _seto_instruction);
	}

	void opcode_setpe(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setpe_instruction);
	}

	void opcode_setpo(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setpo_instruction);
	}

	void opcode_sets(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _sets_instruction);
	}

	void opcode_setz(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _setz_instruction);
	}

	void opcode_shld_cl(u8* data, SDisasmData* dd)
	{ // 0f a5
		do_common_opcode_rm1632_r1632_cl(dd, _shld_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit);
		extract_gp_reg_operand(dd, (int)_count_low_reg, &dd->operand3, _8bit);
	}

	void opcode_shld_immed(u8* data, SDisasmData* dd)
	{ // 0f a4
		do_common_opcode_rm1632_r1632_cl(dd, _shld_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}

	void opcode_shrd_cl(u8* data, SDisasmData* dd)
	{ // 0f ad
		do_common_opcode_rm1632_r1632_cl(dd, _shrd_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit);
		extract_gp_reg_operand(dd, (int)_count_low_reg, &dd->operand3, _8bit);
	}

	void opcode_shrd_immed(u8* data, SDisasmData* dd)
	{ // 0f ac
		do_common_opcode_rm1632_r1632_cl(dd, _shrd_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}

	void opcode_ss_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= SSREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_stc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _stc_instruction);
	}

	void opcode_std(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _std_instruction);
	}

	void opcode_sti(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _sti_instruction);
	}

	void opcode_stosb(u8* data, SDisasmData* dd)
	{
		if (dd->prefixes & REPE)
		{
			dd->mnemonic	= (u8*)"repe";
			dd->operand1	= (u8*)"stosb";
		}
		else if (dd->prefixes & REPNE)
		{
			dd->mnemonic	= (u8*)"repne";
			dd->operand1	= (u8*)"stosb";
		}
		else
		{
			dd->mnemonic	= (u8*)"stosb";
		}
		dd->opcode_bytes	+= 1;
	}

	void opcode_stosw(u8* data, SDisasmData* dd)
	{
		do_common_two_prefixes_mnemonic_operand_size_check(dd, 1, 
															REPE,	_repe_instruction,
															REPNE,	_repne_instruction,
															_stosw_instruction,
															_stosd_instruction);
	}

	void opcode_sub_accum_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, _sub_instruction);
	}

	void opcode_sub_accum_immed8(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed8(data, dd, _sub_instruction);
	}

	void opcode_sub28(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, _sub_instruction);
		do_common_regrm(data + 1, dd, _8bit);
	}

	void opcode_sub29(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _sub_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_sub2a(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, _sub_instruction);
		do_common_regrm_reversed(data + 1, dd, _8bit);
	}

	void opcode_sub2b(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _sub_instruction);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit);
	}

	void opcode_sub_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, _sub_instruction);
	}

	void opcode_sub_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, _sub_instruction);
	}

	void opcode_sub_rm16_32_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed8(data, dd, _sub_instruction);
	}

	void opcode_test_accum_imm16_32(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, _test_instruction);
	}

	void opcode_test_accum_imm8(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed8(data, dd, _test_instruction);
	}

	void opcode_test_rm_reg16_32(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_test_rm_reg_8(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_two_byte_instruction(u8* data, SDisasmData* dd)
	{
		dd->opcode_bytes += 2;
		second_byte_functions[dd->data_root[dd->opcode_bytes - 1]]
			(dd->data_root + dd->opcode_bytes, dd);
	}

	void opcode_two_byte_unused(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_ud2_0f0b(u8* data, SDisasmData* dd)
	{ // 0f 0b
		do_common_mnemonic(dd, _ud2_instruction);
		dd->line_comment = (u8*)"; 0f 0b, always generates #UD";
	}

	void opcode_ud2_0fb9(u8* data, SDisasmData* dd)
	{ // 0f b9
		do_common_mnemonic(dd, _ud2_instruction);
		dd->line_comment = (u8*)"; 0f b9, always generates #UD";
	}

	void opcode_unused(u8* data, SDisasmData* dd)
	{
		asm("int3");
	}

	void opcode_wait(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _wait_instruction);
	}

	void opcode_wbinvd(u8* data, SDisasmData* dd)
	{ // 0f 09
		do_common_mnemonic(dd, _wbinvd_instruction);
	}

	void opcode_wrmsr(u8* data, SDisasmData* dd)
	{ // 0f 30
		do_common_mnemonic(dd, _wrmsr_instruction);
	}

	void opcode_xadd(u8* data, SDisasmData* dd)
	{ // 0f c1
		do_common_opcode_rm16_rm32(dd, _xadd_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_xadd_byte(u8* data, SDisasmData* dd)
	{ // 0f c0
		do_common_opcode_rm8(dd, _xadd_instruction);
		do_common_regrm(data + 1, dd, _8bit);
	}

	void opcode_xchg(u8* data, SDisasmData* dd)
	{  // 87
		do_common_opcode_rm16_rm32(dd, _xchg_instruction);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit);
	}

	void opcode_xchg_byte(u8* data, SDisasmData* dd)
	{ // 86
		do_common_opcode_rm16_rm32(dd, _xchg_instruction);
		do_common_regrm_reversed(data + 1, dd, _8bit);
	}

	void opcode_xchg_xxx(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _xchg_instruction);
		extract_gp_reg_operand(dd, *data & 0x07, &dd->operand1, _16bit | _32bit);
	}

	void opcode_xlat(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, _xlat_instruction);
	}

	void opcode_xor_accum_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, _xor_instruction);
	}

	void opcode_xor_accum_immed8(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed8(data, dd, _xor_instruction);
	}

	void opcode_xor30(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, _xor_instruction);
		do_common_regrm(data + 1, dd, _8bit);
	}

	void opcode_xor31(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _xor_instruction);
		do_common_regrm(data + 1, dd, _16bit | _32bit);
	}

	void opcode_xor32(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, _xor_instruction);
		do_common_regrm_reversed(data + 1, dd, _8bit);
	}

	void opcode_xor33(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, _xor_instruction);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit);
	}

	void opcode_xor_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, _xor_instruction);
	}

	void opcode_xor_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, _xor_instruction);
	}

	void opcode_xor_rm16_32_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed8(data, dd, _xor_instruction);
	}
