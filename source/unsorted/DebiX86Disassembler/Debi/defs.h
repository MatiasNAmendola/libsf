//////////
//
// DebiX86Disassembler/Debi/defs.h
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




// defs.h


// Disassemble
void	debi_disassemble				(u8* data, u32 length, u32 address);


// This function is called to reach the ones below, it is constantly updated
typedef void(*DISASM_FUNC)(u8* data, SDisasmData* dd);


// Opcode decode functions
void    opcode_aaa                      (u8* data, SDisasmData* dd);
void    opcode_aad                      (u8* data, SDisasmData* dd);
void    opcode_aam                      (u8* data, SDisasmData* dd);
void    opcode_aas                      (u8* data, SDisasmData* dd);
void    opcode_adc10                    (u8* data, SDisasmData* dd);
void    opcode_adc11                    (u8* data, SDisasmData* dd);
void    opcode_adc12                    (u8* data, SDisasmData* dd);
void    opcode_adc13                    (u8* data, SDisasmData* dd);
void    opcode_adc_rm8_immed8           (u8* data, SDisasmData* dd);
void    opcode_adc_rm16_32_immed16_32	(u8* data, SDisasmData* dd);
void    opcode_adc_rm16_32_immed8		(u8* data, SDisasmData* dd);
void    opcode_add00                    (u8* data, SDisasmData* dd);
void    opcode_add01                    (u8* data, SDisasmData* dd);
void    opcode_add02                    (u8* data, SDisasmData* dd);
void    opcode_add03                    (u8* data, SDisasmData* dd);
void    opcode_add_rm8_immed8           (u8* data, SDisasmData* dd);
void    opcode_add_rm16_32_immed16_32	(u8* data, SDisasmData* dd);
void    opcode_add_rm16_32_immed8		(u8* data, SDisasmData* dd);
void    opcode_adr_size_override        (u8* data, SDisasmData* dd);
void    opcode_and20                    (u8* data, SDisasmData* dd);
void    opcode_and21                    (u8* data, SDisasmData* dd);
void    opcode_and22                    (u8* data, SDisasmData* dd);
void    opcode_and23                    (u8* data, SDisasmData* dd);
void    opcode_and_rm8_immed8           (u8* data, SDisasmData* dd);
void    opcode_and_rm16_32_immed16_32   (u8* data, SDisasmData* dd);
void    opcode_and_rm16_32_immed8		(u8* data, SDisasmData* dd);
void    opcode_arpl                     (u8* data, SDisasmData* dd);
void    opcode_bound                    (u8* data, SDisasmData* dd);
void    opcode_bsf                      (u8* data, SDisasmData* dd);
void    opcode_bsr                      (u8* data, SDisasmData* dd);
void    opcode_bswap_xxx                (u8* data, SDisasmData* dd);
void    opcode_bt                       (u8* data, SDisasmData* dd);
void    opcode_btc                      (u8* data, SDisasmData* dd);
void    opcode_btr                      (u8* data, SDisasmData* dd);
void    opcode_bts                      (u8* data, SDisasmData* dd);
void    opcode_call_far_operand     	(u8* data, SDisasmData* dd);
void	opcode_call_near_relative		(u8* data, SDisasmData* dd);
void    opcode_jmp_call_far_operand     				(u8* data, SDisasmData* dd, u8* instruction);
void    opcode_jmp_call_near_relative   				(u8* data, SDisasmData* dd, u8* instruction);
void	opcode_jmp_call_rm1632_absolute_indirect		(u8* data, SDisasmData* dd, u8* instruction);
void	opcode_jmp_call_m16_rm1632_absolute_indirect	(u8* data, SDisasmData* dd, u8* instruction);
void    opcode_cbw                      (u8* data, SDisasmData* dd);
void    opcode_check_reg_0f00           (u8* data, SDisasmData* dd);
void    opcode_check_reg_0f01           (u8* data, SDisasmData* dd);
void    opcode_check_reg_0f71           (u8* data, SDisasmData* dd);
void    opcode_check_reg_0f72           (u8* data, SDisasmData* dd);
void    opcode_check_reg_0f73           (u8* data, SDisasmData* dd);
void    opcode_check_reg_0fba           (u8* data, SDisasmData* dd);
void    opcode_check_reg_0fc7           (u8* data, SDisasmData* dd);
void    opcode_check_reg_80             (u8* data, SDisasmData* dd);
void    opcode_check_reg_81             (u8* data, SDisasmData* dd);
void    opcode_check_reg_82             (u8* data, SDisasmData* dd);
void    opcode_check_reg_83             (u8* data, SDisasmData* dd);
void    opcode_check_reg_8f             (u8* data, SDisasmData* dd);
void    opcode_check_reg_c0             (u8* data, SDisasmData* dd);
void    opcode_check_reg_c1             (u8* data, SDisasmData* dd);
void    opcode_check_reg_c6             (u8* data, SDisasmData* dd);
void    opcode_check_reg_c7             (u8* data, SDisasmData* dd);
void    opcode_check_reg_d0             (u8* data, SDisasmData* dd);
void    opcode_check_reg_d1             (u8* data, SDisasmData* dd);
void    opcode_check_reg_d2             (u8* data, SDisasmData* dd);
void    opcode_check_reg_d3             (u8* data, SDisasmData* dd);
void    opcode_check_reg_f6             (u8* data, SDisasmData* dd);
void    opcode_check_reg_f7             (u8* data, SDisasmData* dd);
void    opcode_check_reg_fe             (u8* data, SDisasmData* dd);
void    opcode_check_reg_ff             (u8* data, SDisasmData* dd);
void    opcode_clc                      (u8* data, SDisasmData* dd);
void    opcode_cld                      (u8* data, SDisasmData* dd);
void    opcode_cli                      (u8* data, SDisasmData* dd);
void    opcode_clts                     (u8* data, SDisasmData* dd);
void    opcode_cmc                      (u8* data, SDisasmData* dd);
void    opcode_cmova                    (u8* data, SDisasmData* dd);
void    opcode_cmovc                    (u8* data, SDisasmData* dd);
void    opcode_cmovg                    (u8* data, SDisasmData* dd);
void    opcode_cmovl                    (u8* data, SDisasmData* dd);
void    opcode_cmovna                   (u8* data, SDisasmData* dd);
void    opcode_cmovnc                   (u8* data, SDisasmData* dd);
void    opcode_cmovng                   (u8* data, SDisasmData* dd);
void    opcode_cmovnl                   (u8* data, SDisasmData* dd);
void    opcode_cmovno                   (u8* data, SDisasmData* dd);
void    opcode_cmovns                   (u8* data, SDisasmData* dd);
void    opcode_cmovnz                   (u8* data, SDisasmData* dd);
void    opcode_cmovo                    (u8* data, SDisasmData* dd);
void    opcode_cmovpe                   (u8* data, SDisasmData* dd);
void    opcode_cmovpo                   (u8* data, SDisasmData* dd);
void    opcode_cmovs                    (u8* data, SDisasmData* dd);
void    opcode_cmovz                    (u8* data, SDisasmData* dd);
void    opcode_cmp_rm8_immed8           (u8* data, SDisasmData* dd);
void	opcode_cmp_rm16_32_immed8		(u8* data, SDisasmData* dd);
void	opcode_cmp_rm16_32_immed16_32	(u8* data, SDisasmData* dd);
void    opcode_cmp38                    (u8* data, SDisasmData* dd);
void    opcode_cmp39                    (u8* data, SDisasmData* dd);
void    opcode_cmp3a                    (u8* data, SDisasmData* dd);
void    opcode_cmp3b                    (u8* data, SDisasmData* dd);
void    opcode_cmp3c                    (u8* data, SDisasmData* dd);
void    opcode_cmp3d                    (u8* data, SDisasmData* dd);
void    opcode_cmpsb                    (u8* data, SDisasmData* dd);
void    opcode_cmpsw                    (u8* data, SDisasmData* dd);
void    opcode_cmpxchg                  (u8* data, SDisasmData* dd);
void    opcode_cmpxchg_byte             (u8* data, SDisasmData* dd);
void	opcode_cmpxchg8b				(u8* data, SDisasmData* dd);
void    opcode_cpuid                    (u8* data, SDisasmData* dd);
void    opcode_cs_override              (u8* data, SDisasmData* dd);
void    opcode_cwd                      (u8* data, SDisasmData* dd);
void    opcode_daa                      (u8* data, SDisasmData* dd);
void    opcode_das                      (u8* data, SDisasmData* dd);
void    opcode_dec_xxx                  (u8* data, SDisasmData* dd);
void	opcode_dec_rm8					(u8* data, SDisasmData* dd);
void	opcode_dec_rm1632				(u8* data, SDisasmData* dd);
void    opcode_ds_override              (u8* data, SDisasmData* dd);
void    opcode_emms                     (u8* data, SDisasmData* dd);
void    opcode_enter                    (u8* data, SDisasmData* dd);
void    opcode_es_override              (u8* data, SDisasmData* dd);
void    opcode_fpu_d8                   (u8* data, SDisasmData* dd);
void    opcode_fpu_d9                   (u8* data, SDisasmData* dd);
void    opcode_fpu_da                   (u8* data, SDisasmData* dd);
void    opcode_fpu_db                   (u8* data, SDisasmData* dd);
void    opcode_fpu_dc                   (u8* data, SDisasmData* dd);
void    opcode_fpu_dd                   (u8* data, SDisasmData* dd);
void    opcode_fpu_de                   (u8* data, SDisasmData* dd);
void    opcode_fpu_df                   (u8* data, SDisasmData* dd);
void    opcode_fs_override              (u8* data, SDisasmData* dd);
void    opcode_gs_override              (u8* data, SDisasmData* dd);
void    opcode_hlt                      (u8* data, SDisasmData* dd);
void	opcode_icebp					(u8* data, SDisasmData* dd);
void    opcode_imulaf                   (u8* data, SDisasmData* dd);
void    opcode_imul_3_parms_immed16_32  (u8* data, SDisasmData* dd);
void    opcode_imul_3_parms_immed8      (u8* data, SDisasmData* dd);
void	opcode_imul_rm8					(u8* data, SDisasmData* dd);
void	opcode_imul_rm1632				(u8* data, SDisasmData* dd);
void    opcode_in                       (u8* data, SDisasmData* dd);
void    opcode_in16_32_immed8           (u8* data, SDisasmData* dd);
void    opcode_in8_immed8               (u8* data, SDisasmData* dd);
void    opcode_in_byte                  (u8* data, SDisasmData* dd);
void    opcode_inc_xxx                  (u8* data, SDisasmData* dd);
void	opcode_inc_rm8					(u8* data, SDisasmData* dd);
void	opcode_inc_rm1632				(u8* data, SDisasmData* dd);
void    opcode_insb                     (u8* data, SDisasmData* dd);
void    opcode_insw                     (u8* data, SDisasmData* dd);
void    opcode_int3                     (u8* data, SDisasmData* dd);
void    opcode_into                     (u8* data, SDisasmData* dd);
void    opcode_intx                     (u8* data, SDisasmData* dd);
void    opcode_invd                     (u8* data, SDisasmData* dd);
void    opcode_iret                     (u8* data, SDisasmData* dd);
void	opcode_xxx_rel8					(u8* data, SDisasmData* dd, u8* instruction);
void	opcode_xxx_rel16				(u8* data, SDisasmData* dd, u8* instruction);
void    opcode_ja                       (u8* data, SDisasmData* dd);
void    opcode_ja_l                     (u8* data, SDisasmData* dd);
void    opcode_jc                       (u8* data, SDisasmData* dd);
void    opcode_jc_l                     (u8* data, SDisasmData* dd);
void    opcode_jcxz                     (u8* data, SDisasmData* dd);
void    opcode_jg                       (u8* data, SDisasmData* dd);
void    opcode_jg_l                     (u8* data, SDisasmData* dd);
void    opcode_jl                       (u8* data, SDisasmData* dd);
void    opcode_jl_l                     (u8* data, SDisasmData* dd);
void    opcode_jmp16_32                 (u8* data, SDisasmData* dd);
void    opcode_jmp8                     (u8* data, SDisasmData* dd);
void    opcode_jmp_far                  (u8* data, SDisasmData* dd);
void    opcode_jna                      (u8* data, SDisasmData* dd);
void    opcode_jna_l                    (u8* data, SDisasmData* dd);
void    opcode_jnc                      (u8* data, SDisasmData* dd);
void    opcode_jnc_l                    (u8* data, SDisasmData* dd);
void    opcode_jng                      (u8* data, SDisasmData* dd);
void    opcode_jng_l                    (u8* data, SDisasmData* dd);
void    opcode_jnl                      (u8* data, SDisasmData* dd);
void    opcode_jnl_l                    (u8* data, SDisasmData* dd);
void    opcode_jno                      (u8* data, SDisasmData* dd);
void    opcode_jno_l                    (u8* data, SDisasmData* dd);
void    opcode_jns                      (u8* data, SDisasmData* dd);
void    opcode_jns_l                    (u8* data, SDisasmData* dd);
void    opcode_jnz                      (u8* data, SDisasmData* dd);
void    opcode_jnz_l                    (u8* data, SDisasmData* dd);
void    opcode_jo                       (u8* data, SDisasmData* dd);
void    opcode_jo_l                     (u8* data, SDisasmData* dd);
void    opcode_jpe                      (u8* data, SDisasmData* dd);
void    opcode_jpe_l                    (u8* data, SDisasmData* dd);
void    opcode_jpo                      (u8* data, SDisasmData* dd);
void    opcode_jpo_l                    (u8* data, SDisasmData* dd);
void    opcode_js                       (u8* data, SDisasmData* dd);
void    opcode_js_l                     (u8* data, SDisasmData* dd);
void    opcode_jz                       (u8* data, SDisasmData* dd);
void    opcode_jz_l                     (u8* data, SDisasmData* dd);
void    opcode_lahf                     (u8* data, SDisasmData* dd);
void    opcode_lar                      (u8* data, SDisasmData* dd);
void    opcode_lds                      (u8* data, SDisasmData* dd);
void    opcode_lea                      (u8* data, SDisasmData* dd);
void    opcode_leave                    (u8* data, SDisasmData* dd);
void    opcode_les                      (u8* data, SDisasmData* dd);
void    opcode_lfs                      (u8* data, SDisasmData* dd);
void    opcode_lgs                      (u8* data, SDisasmData* dd);
void    opcode_lock_prefix              (u8* data, SDisasmData* dd);
void    opcode_lodsb                    (u8* data, SDisasmData* dd);
void    opcode_lodsw                    (u8* data, SDisasmData* dd);
void    opcode_loop                     (u8* data, SDisasmData* dd);
void    opcode_loope                    (u8* data, SDisasmData* dd);
void    opcode_loopne                   (u8* data, SDisasmData* dd);
void    opcode_lsl                      (u8* data, SDisasmData* dd);
void    opcode_lss                      (u8* data, SDisasmData* dd);
void    opcode_mov_accum_mem_16_32      (u8* data, SDisasmData* dd);
void    opcode_mov_accum_mem_8          (u8* data, SDisasmData* dd);
void    opcode_mov_gp_control           (u8* data, SDisasmData* dd);
void    opcode_mov_control_gp           (u8* data, SDisasmData* dd);
void    opcode_mov_gp_debug             (u8* data, SDisasmData* dd);
void    opcode_mov_debug_gp             (u8* data, SDisasmData* dd);
void    opcode_mov_gp_test              (u8* data, SDisasmData* dd);
void    opcode_mov_test_gp              (u8* data, SDisasmData* dd);
void    opcode_mov_mem_accum_16_32      (u8* data, SDisasmData* dd);
void    opcode_mov_mem_accum_8          (u8* data, SDisasmData* dd);
void    opcode_mov_reg16_32_sreg        (u8* data, SDisasmData* dd);
void    opcode_mov_reg_immed16_32       (u8* data, SDisasmData* dd);
void    opcode_mov_reg_immed8           (u8* data, SDisasmData* dd);
void    opcode_mov_reg_rm_16_32         (u8* data, SDisasmData* dd);
void    opcode_mov_reg_rm_8             (u8* data, SDisasmData* dd);
void    opcode_mov_rm_reg_16_32         (u8* data, SDisasmData* dd);
void    opcode_mov_rm_reg_8             (u8* data, SDisasmData* dd);
void    opcode_mov_sreg_reg16_32        (u8* data, SDisasmData* dd);
void    opcode_movd_gp_mmx              (u8* data, SDisasmData* dd);
void    opcode_movd_mmx_gp              (u8* data, SDisasmData* dd);
void    opcode_movq_mm_mmx_mmx          (u8* data, SDisasmData* dd);
void    opcode_movq_mmx_mm_mmx          (u8* data, SDisasmData* dd);
void    opcode_movsb                    (u8* data, SDisasmData* dd);
void    opcode_movsw                    (u8* data, SDisasmData* dd);
void    opcode_movsx_byte               (u8* data, SDisasmData* dd);
void    opcode_movsx_word               (u8* data, SDisasmData* dd);
void    opcode_movzx_byte               (u8* data, SDisasmData* dd);
void    opcode_movzx_word               (u8* data, SDisasmData* dd);
void    opcode_nop                      (u8* data, SDisasmData* dd);
void    opcode_op_size_override         (u8* data, SDisasmData* dd);
void    opcode_or_accum0c               (u8* data, SDisasmData* dd);
void    opcode_or_accum0d               (u8* data, SDisasmData* dd);
void    opcode_or_rm08                  (u8* data, SDisasmData* dd);
void    opcode_or_rm09                  (u8* data, SDisasmData* dd);
void    opcode_or_rm0a                  (u8* data, SDisasmData* dd);
void    opcode_or_rm0b                  (u8* data, SDisasmData* dd);
void	opcode_or_rm8_immed8			(u8* data, SDisasmData* dd);
void	opcode_or_rm16_32_immed16_32	(u8* data, SDisasmData* dd);
void	opcode_or_rm16_32_immed8		(u8* data, SDisasmData* dd);
void    opcode_oute6                    (u8* data, SDisasmData* dd);
void    opcode_oute7                    (u8* data, SDisasmData* dd);
void    opcode_outee                    (u8* data, SDisasmData* dd);
void    opcode_outef                    (u8* data, SDisasmData* dd);
void    opcode_out_byte                 (u8* data, SDisasmData* dd);
void    opcode_outsb                    (u8* data, SDisasmData* dd);
void    opcode_outsw                    (u8* data, SDisasmData* dd);
void    opcode_packssdw                 (u8* data, SDisasmData* dd);
void    opcode_packsswb                 (u8* data, SDisasmData* dd);
void    opcode_packuswb                 (u8* data, SDisasmData* dd);
void    opcode_paddb                    (u8* data, SDisasmData* dd);
void    opcode_paddd                    (u8* data, SDisasmData* dd);
void    opcode_paddsb                   (u8* data, SDisasmData* dd);
void    opcode_paddsw                   (u8* data, SDisasmData* dd);
void    opcode_paddusb                  (u8* data, SDisasmData* dd);
void    opcode_paddusw                  (u8* data, SDisasmData* dd);
void    opcode_paddw                    (u8* data, SDisasmData* dd);
void    opcode_pand                     (u8* data, SDisasmData* dd);
void    opcode_pandn                    (u8* data, SDisasmData* dd);
void    opcode_pcmpeqb                  (u8* data, SDisasmData* dd);
void    opcode_pcmpeqd                  (u8* data, SDisasmData* dd);
void    opcode_pcmpeqw                  (u8* data, SDisasmData* dd);
void    opcode_pcmpgtb                  (u8* data, SDisasmData* dd);
void    opcode_pcmpgtd                  (u8* data, SDisasmData* dd);
void    opcode_pcmpgtw                  (u8* data, SDisasmData* dd);
void    opcode_pmaddwd                  (u8* data, SDisasmData* dd);
void    opcode_pmulhw                   (u8* data, SDisasmData* dd);
void    opcode_pmullw                   (u8* data, SDisasmData* dd);
void    opcode_pop_ds                   (u8* data, SDisasmData* dd);
void    opcode_pop_es                   (u8* data, SDisasmData* dd);
void    opcode_pop_fs                   (u8* data, SDisasmData* dd);
void    opcode_pop_gs                   (u8* data, SDisasmData* dd);
void    opcode_pop_ss                   (u8* data, SDisasmData* dd);
void    opcode_pop_xreg                 (u8* data, SDisasmData* dd);
void    opcode_popa                     (u8* data, SDisasmData* dd);
void    opcode_popf                     (u8* data, SDisasmData* dd);
void    opcode_por                      (u8* data, SDisasmData* dd);
void    opcode_pslld                    (u8* data, SDisasmData* dd);
void    opcode_psllq                    (u8* data, SDisasmData* dd);
void    opcode_psllw                    (u8* data, SDisasmData* dd);
void    opcode_psrad                    (u8* data, SDisasmData* dd);
void    opcode_psraw                    (u8* data, SDisasmData* dd);
void    opcode_psrad_immed8             (u8* data, SDisasmData* dd);
void    opcode_psraw_immed8             (u8* data, SDisasmData* dd);
void    opcode_psrld                    (u8* data, SDisasmData* dd);
void    opcode_psrlq                    (u8* data, SDisasmData* dd);
void    opcode_psrlw                    (u8* data, SDisasmData* dd);
void    opcode_psrld_immed8             (u8* data, SDisasmData* dd);
void    opcode_psrlq_immed8             (u8* data, SDisasmData* dd);
void    opcode_psrlw_immed8             (u8* data, SDisasmData* dd);
void    opcode_psubb                    (u8* data, SDisasmData* dd);
void    opcode_psubd                    (u8* data, SDisasmData* dd);
void    opcode_psubsb                   (u8* data, SDisasmData* dd);
void    opcode_psubsw                   (u8* data, SDisasmData* dd);
void    opcode_psubusb                  (u8* data, SDisasmData* dd);
void    opcode_psubusw                  (u8* data, SDisasmData* dd);
void    opcode_psubw                    (u8* data, SDisasmData* dd);
void    opcode_punpckhbw                (u8* data, SDisasmData* dd);
void    opcode_punpckhdq                (u8* data, SDisasmData* dd);
void    opcode_punpckhwd                (u8* data, SDisasmData* dd);
void    opcode_punpcklbw                (u8* data, SDisasmData* dd);
void    opcode_punpckldq                (u8* data, SDisasmData* dd);
void    opcode_punpcklwd                (u8* data, SDisasmData* dd);
void    opcode_push_cs                  (u8* data, SDisasmData* dd);
void    opcode_push_ds                  (u8* data, SDisasmData* dd);
void    opcode_push_es                  (u8* data, SDisasmData* dd);
void    opcode_push_fs                  (u8* data, SDisasmData* dd);
void    opcode_push_gs                  (u8* data, SDisasmData* dd);
void    opcode_push_immed16_32          (u8* data, SDisasmData* dd);
void    opcode_push_immed8              (u8* data, SDisasmData* dd);
void    opcode_push_ss                  (u8* data, SDisasmData* dd);
void    opcode_push_xreg                (u8* data, SDisasmData* dd);
void    opcode_pusha                    (u8* data, SDisasmData* dd);
void    opcode_pushf                    (u8* data, SDisasmData* dd);
void    opcode_pxor                     (u8* data, SDisasmData* dd);
void    opcode_rdmsr                    (u8* data, SDisasmData* dd);
void    opcode_rdpmc                    (u8* data, SDisasmData* dd);
void    opcode_rdtsc                    (u8* data, SDisasmData* dd);
void    opcode_repe_prefix              (u8* data, SDisasmData* dd);
void    opcode_repne_prefix             (u8* data, SDisasmData* dd);
void    opcode_retf                     (u8* data, SDisasmData* dd);
void    opcode_retf_immed               (u8* data, SDisasmData* dd);
void    opcode_retn                     (u8* data, SDisasmData* dd);
void    opcode_retn_immed               (u8* data, SDisasmData* dd);
void    opcode_rsm                      (u8* data, SDisasmData* dd);
void    opcode_sahf                     (u8* data, SDisasmData* dd);
void    opcode_sbb_accum_immed16_32     (u8* data, SDisasmData* dd);
void    opcode_sbb_accum_immed8         (u8* data, SDisasmData* dd);
void    opcode_sbb18                    (u8* data, SDisasmData* dd);
void    opcode_sbb19                    (u8* data, SDisasmData* dd);
void    opcode_sbb1a                    (u8* data, SDisasmData* dd);
void    opcode_sbb1b                    (u8* data, SDisasmData* dd);
void	opcode_sbb_rm8_immed8			(u8* data, SDisasmData* dd);
void	opcode_sbb_rm16_32_immed16_32	(u8* data, SDisasmData* dd);
void	opcode_sbb_rm16_32_immed8		(u8* data, SDisasmData* dd);
void    opcode_scasb                    (u8* data, SDisasmData* dd);
void    opcode_scasw                    (u8* data, SDisasmData* dd);
void    opcode_seta                     (u8* data, SDisasmData* dd);
void    opcode_setc                     (u8* data, SDisasmData* dd);
void    opcode_setg                     (u8* data, SDisasmData* dd);
void    opcode_setl                     (u8* data, SDisasmData* dd);
void    opcode_setna                    (u8* data, SDisasmData* dd);
void    opcode_setnc                    (u8* data, SDisasmData* dd);
void    opcode_setng                    (u8* data, SDisasmData* dd);
void    opcode_setnl                    (u8* data, SDisasmData* dd);
void    opcode_setno                    (u8* data, SDisasmData* dd);
void    opcode_setns                    (u8* data, SDisasmData* dd);
void    opcode_setnz                    (u8* data, SDisasmData* dd);
void    opcode_seto                     (u8* data, SDisasmData* dd);
void    opcode_setpe                    (u8* data, SDisasmData* dd);
void    opcode_setpo                    (u8* data, SDisasmData* dd);
void    opcode_sets                     (u8* data, SDisasmData* dd);
void    opcode_setz                     (u8* data, SDisasmData* dd);
void    opcode_shld_cl                  (u8* data, SDisasmData* dd);
void    opcode_shld_immed               (u8* data, SDisasmData* dd);
void    opcode_shrd_cl                  (u8* data, SDisasmData* dd);
void    opcode_shrd_immed               (u8* data, SDisasmData* dd);
void    opcode_ss_override              (u8* data, SDisasmData* dd);
void    opcode_stc                      (u8* data, SDisasmData* dd);
void    opcode_std                      (u8* data, SDisasmData* dd);
void    opcode_sti                      (u8* data, SDisasmData* dd);
void    opcode_stosb                    (u8* data, SDisasmData* dd);
void    opcode_stosw                    (u8* data, SDisasmData* dd);
void    opcode_sub_accum_immed16_32     (u8* data, SDisasmData* dd);
void    opcode_sub_accum_immed8         (u8* data, SDisasmData* dd);
void    opcode_sub28                    (u8* data, SDisasmData* dd);
void    opcode_sub29                    (u8* data, SDisasmData* dd);
void    opcode_sub2a                    (u8* data, SDisasmData* dd);
void    opcode_sub2b                    (u8* data, SDisasmData* dd);
void	opcode_sub_rm8_immed8			(u8* data, SDisasmData* dd);
void	opcode_sub_rm16_32_immed16_32	(u8* data, SDisasmData* dd);
void	opcode_sub_rm16_32_immed8		(u8* data, SDisasmData* dd);
void    opcode_test_accum_imm16_32      (u8* data, SDisasmData* dd);
void    opcode_test_accum_imm8          (u8* data, SDisasmData* dd);
void    opcode_test_rm_reg16_32         (u8* data, SDisasmData* dd);
void    opcode_test_rm_reg_8            (u8* data, SDisasmData* dd);
void    opcode_two_byte_instruction     (u8* data, SDisasmData* dd);
void    opcode_two_byte_unused          (u8* data, SDisasmData* dd);
void    opcode_ud2_0f0b                 (u8* data, SDisasmData* dd);
void    opcode_ud2_0fb9                 (u8* data, SDisasmData* dd);
void    opcode_unused                   (u8* data, SDisasmData* dd);
void    opcode_wait                     (u8* data, SDisasmData* dd);
void    opcode_wbinvd                   (u8* data, SDisasmData* dd);
void    opcode_wrmsr                    (u8* data, SDisasmData* dd);
void    opcode_xadd                     (u8* data, SDisasmData* dd);
void    opcode_xadd_byte                (u8* data, SDisasmData* dd);
void    opcode_xchg                     (u8* data, SDisasmData* dd);
void    opcode_xchg_byte                (u8* data, SDisasmData* dd);
void    opcode_xchg_xxx                 (u8* data, SDisasmData* dd);
void    opcode_xlat                     (u8* data, SDisasmData* dd);
void    opcode_xor_accum_immed16_32     (u8* data, SDisasmData* dd);
void    opcode_xor_accum_immed8         (u8* data, SDisasmData* dd);
void    opcode_xor30                    (u8* data, SDisasmData* dd);
void    opcode_xor31                    (u8* data, SDisasmData* dd);
void    opcode_xor32                    (u8* data, SDisasmData* dd);
void    opcode_xor33                    (u8* data, SDisasmData* dd);
void	opcode_xor_rm8_immed8			(u8* data, SDisasmData* dd);
void	opcode_xor_rm16_32_immed16_32	(u8* data, SDisasmData* dd);
void	opcode_xor_rm16_32_immed8		(u8* data, SDisasmData* dd);
