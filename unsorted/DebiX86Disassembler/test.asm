;;;;;;;;;;
;;
;; DebiX86Disassembler/Debi/test.asm
;;
;;;;;;
;; Version 0.80
;; Copyright (c) 2014 by Rick C. Hodgin
;;;;;;
;; Last update:
;;     Feb.13.2014
;;;;;;
;; Change log:
;;     Feb.13.2014 - Initial creation
;;;;;;
;;
;; This software is released as Liberty Software under a Repeat License, as governed
;; by the Public Benefit License v1.0 or later (PBL).
;;
;; You are free to use, copy, modify and share this software.  However, it can only
;; be released under the PBL version indicated, and every project must include a copy
;; of the pbl.txt document for its version as is at http:;;www.libsf.org/licenses/.
;;
;; For additional information about this project, or to view the license, see:
;;
;;     http:;;www.libsf.org/
;;     http:;;www.libsf.org/licenses/
;;     http:;;www.visual-freepro.org/vjr/indexmain.html
;;     http:;;www.visual-freepro.org/wiki/index.php/PBL
;;     http:;;www.visual-freepro.org/wiki/index.php/Repeat_License
;;
;; Thank you.  And may The Lord bless you richly as you lift up your life, your
;; talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
;;
;;






BITS 32
SECTION .data
	foo:	dd 0
	foo2:	dw 0

SECTION .text
;;  add		[foo],edx                       ; 0x00, 0x01, 0x02, 0x03 - add
;;  add		[ss:esi],dx                     ; 0x00, 0x01, 0x02, 0x03 - add
;;  add		[fs:bx+di+6435],ax              ; 0x00, 0x01, 0x02, 0x03 - add
;;  add		[cs:bx],bx                      ; 0x00, 0x01, 0x02, 0x03 - add
;;  add		[ds:edi+ebp],dx                 ; 0x00, 0x01, 0x02, 0x03 - add
;;  add		edx,[foo]                       ; 0x00, 0x01, 0x02, 0x03 - add
;;  add		dx,[ss:esi]                     ; 0x00, 0x01, 0x02, 0x03 - add
;;  add		ax,[fs:bx+di+6435]              ; 0x00, 0x01, 0x02, 0x03 - add
;;  add		bx,[cs:bx]                      ; 0x00, 0x01, 0x02, 0x03 - add
;;  add		dx,[ds:edi+ebp]                 ; 0x00, 0x01, 0x02, 0x03 - add
;;  add 	byte [fs:foo+bp],5              ; 0x04 - add_immed8
;;  add 	word [fs:foo+bp],5              ; 0x05 - opcode_add_immed16_32
;;  add 	dword [fs:foo+bp],5             ; 0x05 - opcode_add_immed16_32
;;  add 	byte [fs:foo+ebp],5             ; 0x04 - add_immed8
;;  add 	word [fs:foo+ebp],5             ; 0x05 - opcode_add_immed16_32
;;  add 	dword [fs:foo+ebp],5            ; 0x05 - opcode_add_immed16_32
;;  add 	edx,5                           ; 0x05 - opcode_add_immed16_32
;;  add 	ebp,67895432                    ; 0x05 - opcode_add_immed16_32
;;  add 	byte [fs:foo+bp],150            ; 0x04 - add_immed8
;;  add 	word [fs:foo+bp],35000          ; 0x05 - opcode_add_immed16_32
;;  add 	dword [fs:foo+bp],2000000000    ; 0x05 - opcode_add_immed16_32
;;  add 	byte [fs:foo+ebp],150           ; 0x04 - add_immed8
;;  add 	word [fs:foo+ebp],35000         ; 0x05 - opcode_add_immed16_32
;;  add 	dword [fs:foo+ebp],2000000000   ; 0x05 - opcode_add_immed16_32
;;  add 	byte [fs:foo],5                 ; 0x04 - add_immed8
;;  add 	word [fs:foo],5                 ; 0x05 - opcode_add_immed16_32
;;  add 	dword [fs:foo],5                ; 0x05 - opcode_add_immed16_32
;;  push	es                              ; 0x06 - opcode_push_es
;;  pop		es                              ; 0x07 - opcode_pop_es
;;	arpl	word [fs:foo+ebp],bx			; 0x60 /r
;;	bound	ax,[cs:ebx]						; 0x62 /r
;;	bound	ax,[ds:bx+si]					; 0x62 /r
;;	bound	edx,[gs:ebp+edi]				; 0x62 /r
;;	bound	edx,[gs:ebx+esi]				; 0x62 /r
;;	bound	edx,[gs:eax+esp]				; 0x62 /r
;;	bsf		ax,dx
;;	bsf		bx,[gs:ebx]
;;	bsf		ecx,ebx
;;	bsf		eax,[ss:esi]
;;	bswap	eax
;;	bswap	edi
;;  btc		[gs:edi],bx
;;	btc		ax,bx
;;	btc		edx,esi
;;	btr		[gs:edi],bx
;;	btr		ax,bx
;;	btr		edx,esi
;;	bts		[gs:edi],bx
;;	bts		ax,bx
;;	bts		edx,esi
;;	call	word [cs:ebx+edi]
;;	call	word [gs:ebp-8]
;;	call	word [cs:foo+30]
;;	call	dword [cs:ebx+edi]
;;	cmova	ax,dx
;;	cmova	ebp,[esi+ebp+5];
;;	cmovc	bx,dx
;;	cmovc	ebx,[esi+ebp+5];
;;	cmovg	cx,dx
;;	cmovg	ebp,[esi+ebp+5];
;;	cmovl	dx,dx
;;	cmovl	ebx,[esi+ebp+5];
;;	cmovna	ax,dx
;;	cmovna	ebp,[esi+ebp+5];
;;	cmovnc	bx,dx
;;	cmovnc	ebx,[esi+ebp+5];
;;	cmovng	cx,dx
;;	cmovng	ebp,[esi+ebp+5];
;;	cmovnl	dx,dx
;;	cmovnl	ebx,[esi+ebp+5];
;;	cmovno	ax,dx
;;	cmovno	ebp,[esi+ebp+5];
;;	cmovns	bx,dx
;;	cmovns	ebx,[esi+ebp+5];
;;	cmovnz	cx,dx
;;	cmovnz	ebp,[esi+ebp+5];
;;	cmovo	dx,dx
;;	cmovo	ebx,[esi+ebp+5];
;;	cmovpe	ax,dx
;;	cmovpe	ebp,[esi+ebp+5];
;;	cmovpo	bx,dx
;;	cmovpo	ebx,[esi+ebp+5];
;;	cmovs	cx,dx
;;	cmovs	ebp,[esi+ebp+5];
;;	cmovz	dx,dx
;;	cmovz	ebx,[esi+ebp+5];
;;	cmp		al,5
;;	cmp		bl,dh
;;	cmp		ax,5000
;;	cmp		bx,dx
;;	cmp		bx,5000
;;	cmp		eax,500000000
;;	cmp		ebx,500000000
;;	cmp		ebx,[ss:esi+eax]
;;	cmp		[ss:ebx+ebx],esp
;;	cmp		ebp,esi
;;	cmp		al,[cs:foo+8+ebp+edi]
;;	cmpxchg	byte [gs:foo+edi],al
;;	cmpxchg bl,dh
;;	cmpxchg dl,ah
;;	cmpxchg	[ss:foo+ebx+edi],cl
;;	cmpxchg	[ss:foo+bx+di],bp
;;	cmpxchg	[ss:foo+si],edx
;;	dec		ax
;;	dec		ebp
;;	inc		dx
;;	inc		esi
;;	dec		byte [ss:bx]
;;	dec		byte [ss:ebx+edi]
;;	dec		byte [ss:ebx+edi+foo]
;;	dec		word [fs:foo]
;;	imul	eax,dword [fs:ebx]				; 0x0f af
;;	imul	al								; 0xf6
;;	imul	dx,word [fs:ebx+eax]			; 0xf7
;;	imul	word [fs:bx]					; 0xf7
;;	imul	dx								; 0xf7
;;	imul	esi								; 0xf7
;;	dec		dword [ss:esi+edi]
;;	imul	byte [ss:ebx*4+eax]				; 0xf6
;;	bound	edx,[gs:ebp*4+edi]				; 0x62 /r
;;	imul	byte [ss:ebp*2+esi+8]				; 0xf6
;;	imul	word [gs:ebp*8+esi+8]				; 0xf7
;;	imul	dword [cs:ebp+esi*2+8]			; 0xf7
;;	sldt	[gs:eax*4+ebx+16]
;;	lldt	[gs:ebx*2+ecx]
;;	sgdt	[gs:ebp*8+edi+40]
;;	lgdt	[cs:ebp+edi+18]
;;	sidt	[fs:ebp*4+edi+12]
;;	lidt	[es:esp+ebx+4]
;;	ltr		ax
;;	verr	dx
;;	verw	si
;;	lmsw	[cs:bx+di]
;;	smsw	[cs:esp+5]
;;	invlpg	[cs:bx+di]
;;	psraw	mm0,mm7
;;	psraw	mm1,[cs:ebx+16]
;;	psraw	mm2,5
;;	psraw	xmm0,xmm7
;;	psraw	xmm1,[cs:ebx+16]
;;	psraw	xmm2,5
;;	psrlw	mm0,mm7
;;	psrlw	mm1,[cs:ebx+16]
;;	psrlw	mm2,5
;;	psrlw	xmm0,xmm7
;;	psrlw	xmm1,[cs:ebx+16]
;;	psrlw	xmm2,5
;;	psrld	mm0,mm7
;;	psrld	mm1,[cs:ebx+16]
;;	psrld	mm2,5
;;	psrld	xmm0,xmm7
;;	psrld	xmm1,[cs:ebx+16]
;;	psrld	xmm2,5
;;	psrlq	mm0,mm7
;;	psrlq	mm1,[cs:ebx+16]
;;	psrlq	mm2,5
;;	psrlq	xmm0,xmm7
;;	psrlq	xmm1,[cs:ebx+16]
;;	psrlq	xmm2,5
;;	psubb	mm0,mm3
;;	psubb	mm5,[gs:ebp+esi*4+84]
;;	psubb	xmm5,xmm2
;;	psubb	xmm5,[gs:esp+eax*2+168]
;;	psubd	mm0,mm3
;;	psubd	mm5,[gs:ebp+esi*4+84]
;;	psubd	xmm5,xmm2
;;	psubd	xmm5,[gs:esp+eax*2+168]
;;	psubw	mm0,mm3
;;	psubw	mm5,[gs:ebp+esi*4+84]
;;	psubw	xmm5,xmm2
;;	psubw	xmm5,[gs:esp+eax*2+168]
;;	psubsb	mm0,mm3
;;	psubsb	mm5,[gs:ebp+esi*4+84]
;;	psubsb	xmm5,xmm2
;;	psubsb	xmm5,[gs:esp+eax*2+168]
;;	psubsw	mm0,mm3
;;	psubsw	mm5,[gs:ebp+esi*4+84]
;;	psubsw	xmm5,xmm2
;;	psubsw	xmm5,[gs:esp+eax*2+168]
;;	psubusb	mm0,mm3
;;	psubusb	mm5,[gs:ebp+esi*4+84]
;;	psubusb	xmm5,xmm2
;;	psubusb	xmm5,[gs:esp+eax*2+168]
;;	psubusw	mm0,mm3
;;	psubusw	mm5,[gs:ebp+esi*4+84]
;;	psubusw	xmm5,xmm2
;;	psubusw	xmm5,[gs:esp+eax*2+168]
;;	punpckhbw	mm6,mm4
;;	punpckhbw	mm2,[ss:ebp+esi*4+40]
;;	punpckhbw	xmm1,xmm3
;;	punpckhbw	xmm2,[ss:ebp+edi*8+80]
;;	punpckhwd	mm6,mm4
;;	punpckhwd	mm2,[ss:ebp+esi*4+40]
;;	punpckhwd	xmm1,xmm3
;;	punpckhwd	xmm2,[ss:ebp+edi*8+80]
;;	punpckhdq	mm6,mm4
;;	punpckhdq	mm2,[ss:ebp+esi*4+40]
;;	punpckhdq	xmm1,xmm3
;;	punpckhdq	xmm2,[ss:ebp+edi*8+80]
;;	push	byte 16
;;	push	word 24000
;;	push	dword 48000000
;;	shld	ecx,edx,cl
;;	shld	bx,ax,cl
;;	shrd	ecx,edx,cl
;;	shrd	bx,ax,cl
;;	shld	ecx,edx,2
;;	shrd	ecx,edx,8
;;	shld	cx,si,2
;;	shrd	sp,bp,8
;;	or		al,dh
;;	or		bx,cx
;;	or		esi,ebp
	fadd	st2,st0
hcf:
	db	0xf0, 0x0f, 0xc7, 0xc8
after:
	nop
	int3
	nop
;   or_rm                                   ; 0x08 - opcode_or_rm
;   or_rm                                   ; 0x09 - opcode_or_rm
;   or_rm                                   ; 0x0a - opcode_or_rm
;   or_rm                                   ; 0x0b - opcode_or_rm
;   or_accum                                ; 0x0c - opcode_or_accum
;   or_accum                                ; 0x0d - opcode_or_accum
;;  push	cs                              ; 0x0e - opcode_push_cs
;   two_byte_instruction                    ; 0x0f - opcode_two_byte_instruction
;   adc                                     ; 0x10 - opcode_adc
;   adc                                     ; 0x11 - opcode_adc
;   adc                                     ; 0x12 - opcode_adc
;   adc                                     ; 0x13 - opcode_adc
;   adc_immed8                              ; 0x14 - opcode_adc_immed8
;   adc_immed16_32                          ; 0x15 - opcode_adc_immed16_32
;;  push	ss                              ; 0x16 - opcode_push_ss
;;  pop		ss                              ; 0x17 - opcode_pop_ss
;   sbb_rm_reg8                             ; 0x18 - opcode_sbb_rm_reg8
;   sbb_rm_reg16_32                         ; 0x19 - opcode_sbb_rm_reg16_32
;   sbb_reg8_rm                             ; 0x1a - opcode_sbb_reg8_rm
;   sbb_reg16_32_rm                         ; 0x1b - opcode_sbb_reg16_32_rm
;   sbb_accum_immed8                        ; 0x1c - opcode_sbb_accum_immed8
;   sbb_accum_immed16_32                    ; 0x1d - opcode_sbb_accum_immed16_32
;;  push	ds                              ; 0x1e - opcode_push_ds
;;  pop		ds                              ; 0x1f - opcode_pop_ds
;   and                                     ; 0x20 - opcode_and
;   and                                     ; 0x21 - opcode_and
;   and                                     ; 0x22 - opcode_and
;   and                                     ; 0x23 - opcode_and
;   and_immed8                              ; 0x24 - opcode_and_immed8
;   and_immed16_32                          ; 0x25 - opcode_and_immed16_32
;   es_override                             ; 0x26 - opcode_es_override
;;  daa                                     ; 0x27 - opcode_daa
;   sub_rm_reg8                             ; 0x28 - opcode_sub_rm_reg8
;   sub_rm_reg16_32                         ; 0x29 - opcode_sub_rm_reg16_32
;   sub_reg8_rm                             ; 0x2a - opcode_sub_reg8_rm
;   sub_reg16_32_rm                         ; 0x2b - opcode_sub_reg16_32_rm
;   sub_accum_immed8                        ; 0x2c - opcode_sub_accum_immed8
;   sub_accum_immed16_32                    ; 0x2d - opcode_sub_accum_immed16_32
;   cs_override                             ; 0x2e - opcode_cs_override
;;  das                                     ; 0x2f - opcode_das
;   xor_rm_reg8                             ; 0x30 - opcode_xor_rm_reg8
;   xor_rm_reg16_32                         ; 0x31 - opcode_xor_rm_reg16_32
;   xor_reg8_rm                             ; 0x32 - opcode_xor_reg8_rm
;   xor_reg16_32_rm                         ; 0x33 - opcode_xor_reg16_32_rm
;   xor_accum_immed8                        ; 0x34 - opcode_xor_accum_immed8
;   xor_accum_immed16_32                    ; 0x35 - opcode_xor_accum_immed16_32
;   ss_override                             ; 0x36 - opcode_ss_override
;;  aaa                                     ; 0x37 - opcode_aaa
;   cmp_rm8_r8                              ; 0x38 - opcode_cmp_rm8_r8
;   cmp_rm16_r16                            ; 0x39 - opcode_cmp_rm16_r16
;   cmp_r8_rm8                              ; 0x3a - opcode_cmp_r8_rm8
;   cmp_r16_rm16                            ; 0x3b - opcode_cmp_r16_rm16
;   cmp_immed8                              ; 0x3c - opcode_cmp_immed8
;   cmp_immed16_32                          ; 0x3d - opcode_cmp_immed16_32
;   ds_override                             ; 0x3e - opcode_ds_override
;;  aas                                     ; 0x3f - opcode_aas
;   inc_xax                                 ; 0x40 - opcode_inc_xax
;   inc_xcx                                 ; 0x41 - opcode_inc_xcx
;   inc_xdx                                 ; 0x42 - opcode_inc_xdx
;   inc_xbx                                 ; 0x43 - opcode_inc_xbx
;   inc_xsp                                 ; 0x44 - opcode_inc_xsp
;   inc_xbp                                 ; 0x45 - opcode_inc_xbp
;   inc_xsi                                 ; 0x46 - opcode_inc_xsi
;   inc_xdi                                 ; 0x47 - opcode_inc_xdi
;   dec_xax                                 ; 0x48 - opcode_dec_xax
;   dec_xcx                                 ; 0x49 - opcode_dec_xcx
;   dec_xdx                                 ; 0x4a - opcode_dec_xdx
;   dec_xbx                                 ; 0x4b - opcode_dec_xbx
;   dec_xsp                                 ; 0x4c - opcode_dec_xsp
;   dec_xbp                                 ; 0x4d - opcode_dec_xbp
;   dec_xsi                                 ; 0x4e - opcode_dec_xsi
;   dec_xdi                                 ; 0x4f - opcode_dec_xdi
;   push_xax                                ; 0x50 - opcode_push_xax
;   push_xcx                                ; 0x51 - opcode_push_xcx
;   push_xdx                                ; 0x52 - opcode_push_xdx
;   push_xbx                                ; 0x53 - opcode_push_xbx
;   push_xsp                                ; 0x54 - opcode_push_xsp
;   push_xbp                                ; 0x55 - opcode_push_xbp
;   push_xsi                                ; 0x56 - opcode_push_xsi
;   push_xdi                                ; 0x57 - opcode_push_xdi
;   pop_xax                                 ; 0x58 - opcode_pop_xax
;   pop_xcx                                 ; 0x59 - opcode_pop_xcx
;   pop_xdx                                 ; 0x5a - opcode_pop_xdx
;   pop_xbx                                 ; 0x5b - opcode_pop_xbx
;   pop_xsp                                 ; 0x5c - opcode_pop_xsp
;   pop_xbp                                 ; 0x5d - opcode_pop_xbp
;   pop_xsi                                 ; 0x5e - opcode_pop_xsi
;   pop_xdi                                 ; 0x5f - opcode_pop_xdi
;;  pusha                                   ; 0x60 - opcode_pusha
;;  popa                                    ; 0x61 - opcode_popa
;   bound                                   ; 0x62 - opcode_bound
;   arpl                                    ; 0x63 - opcode_arpl
;   fs_override                             ; 0x64 - opcode_fs_override
;   gs_override                             ; 0x65 - opcode_gs_override
;   op_size_override                        ; 0x66 - opcode_op_size_override
;   adr_size_override                       ; 0x67 - opcode_adr_size_override
;   push_immed16_32                         ; 0x68 - opcode_push_immed16_32
;   imul_3_parms_immed16_32                 ; 0x69 - opcode_imul_3_parms_immed16_32
;   push_immed8                             ; 0x6a - opcode_push_immed8
;   imul_3_parms_immed8                     ; 0x6b - opcode_imul_3_parms_immed8
;;  insb                                    ; 0x6c - opcode_insb
;;  insw                                    ; 0x6d - opcode_insw
;;  outsb                                   ; 0x6e - opcode_outsb
;;  outsw                                   ; 0x6f - opcode_outsw
;   jo                                      ; 0x70 - opcode_jo
;   jno                                     ; 0x71 - opcode_jno
;   jc                                      ; 0x72 - opcode_jc
;   jnc                                     ; 0x73 - opcode_jnc
;   jz                                      ; 0x74 - opcode_jz
;   jnz                                     ; 0x75 - opcode_jnz
;   jna                                     ; 0x76 - opcode_jna
;   ja                                      ; 0x77 - opcode_ja
;   js                                      ; 0x78 - opcode_js
;   jns                                     ; 0x79 - opcode_jns
;   jpe                                     ; 0x7a - opcode_jpe
;   jpo                                     ; 0x7b - opcode_jpo
;   jl                                      ; 0x7c - opcode_jl
;   jnl                                     ; 0x7d - opcode_jnl
;   jng                                     ; 0x7e - opcode_jng
;   jg                                      ; 0x7f - opcode_jg
;   check_reg_80                            ; 0x80 - opcode_check_reg_80
;   check_reg_81                            ; 0x81 - opcode_check_reg_81
;   check_reg_82                            ; 0x82 - opcode_check_reg_82
;   check_reg_83                            ; 0x83 - opcode_check_reg_83
;   test_rm_reg_8                           ; 0x84 - opcode_test_rm_reg_8
;   test_rm_reg16_32                        ; 0x85 - opcode_test_rm_reg16_32
;   xchg_byte                               ; 0x86 - opcode_xchg_byte
;   xchg                                    ; 0x87 - opcode_xchg
;   mov_rm_reg_8                            ; 0x88 - opcode_mov_rm_reg_8
;   mov_rm_reg_16_32                        ; 0x89 - opcode_mov_rm_reg_16_32
;   mov_reg_rm_8                            ; 0x8a - opcode_mov_reg_rm_8
;   mov_reg_rm_16_32                        ; 0x8b - opcode_mov_reg_rm_16_32
;   mov_reg16_32_sreg                       ; 0x8c - opcode_mov_reg16_32_sreg
;   lea                                     ; 0x8d - opcode_lea
;   mov_sreg_reg16_32                       ; 0x8e - opcode_mov_sreg_reg16_32
;   check_reg_8f                            ; 0x8f - opcode_check_reg_8f
;;  nop                                     ; 0x90 - opcode_nop
;   xchg_xcx                                ; 0x91 - opcode_xchg_xcx
;   xchg_xdx                                ; 0x92 - opcode_xchg_xdx
;   xchg_xbx                                ; 0x93 - opcode_xchg_xbx
;   xchg_xsp                                ; 0x94 - opcode_xchg_xsp
;   xchg_xbp                                ; 0x95 - opcode_xchg_xbp
;   xchg_xsi                                ; 0x96 - opcode_xchg_xsi
;   xchg_xdi                                ; 0x97 - opcode_xchg_xdi
;;  cbw                                     ; 0x98 - opcode_cbw
;;  cwd                                     ; 0x99 - opcode_cwd
;   call_far_operand                        ; 0x9a - opcode_call_far_operand
;;  wait                                    ; 0x9b - opcode_wait
;;  pushf                                   ; 0x9c - opcode_pushf
;;  popf                                    ; 0x9d - opcode_popf
;;  sahf                                    ; 0x9e - opcode_sahf
;;  lahf                                    ; 0x9f - opcode_lahf
;   mov_accum_mem_8                         ; 0xa0 - opcode_mov_accum_mem_8
;   mov_accum_mem_16_32                     ; 0xa1 - opcode_mov_accum_mem_16_32
;   mov_mem_accum_8                         ; 0xa2 - opcode_mov_mem_accum_8
;   mov_mem_accum_16_32                     ; 0xa3 - opcode_mov_mem_accum_16_32
;;  repne	movsb                           ; 0xa4 - opcode_movsb
;;  repnz	movsw                           ; 0xa5 - opcode_movsw
;;  repe	cmpsb                           ; 0xa6 - opcode_cmpsb
;;  repe	cmpsw                           ; 0xa7 - opcode_cmpsw
;   test_accum_imm8                         ; 0xa8 - opcode_test_accum_imm8
;   test_accum_imm16_32                     ; 0xa9 - opcode_test_accum_imm16_32
;;  rep		stosb                           ; 0xaa - opcode_stosb
;;  rep		stosw                           ; 0xab - opcode_stosw
;;  rep		lodsb                           ; 0xac - opcode_lodsb
;;  rep		lodsw                           ; 0xad - opcode_lodsw
;;  rep		scasb                           ; 0xae - opcode_scasb
;;  rep		scasw                           ; 0xaf - opcode_scasw
;   mov_reg_immed8                          ; 0xb0 - opcode_mov_reg_immed8
;   mov_reg_immed8                          ; 0xb1 - opcode_mov_reg_immed8
;   mov_reg_immed8                          ; 0xb2 - opcode_mov_reg_immed8
;   mov_reg_immed8                          ; 0xb3 - opcode_mov_reg_immed8
;   mov_reg_immed8                          ; 0xb4 - opcode_mov_reg_immed8
;   mov_reg_immed8                          ; 0xb5 - opcode_mov_reg_immed8
;   mov_reg_immed8                          ; 0xb6 - opcode_mov_reg_immed8
;   mov_reg_immed8                          ; 0xb7 - opcode_mov_reg_immed8
;   mov_reg_immed16_32                      ; 0xb8 - opcode_mov_reg_immed16_32
;   mov_reg_immed16_32                      ; 0xb9 - opcode_mov_reg_immed16_32
;   mov_reg_immed16_32                      ; 0xba - opcode_mov_reg_immed16_32
;   mov_reg_immed16_32                      ; 0xbb - opcode_mov_reg_immed16_32
;   mov_reg_immed16_32                      ; 0xbc - opcode_mov_reg_immed16_32
;   mov_reg_immed16_32                      ; 0xbd - opcode_mov_reg_immed16_32
;   mov_reg_immed16_32                      ; 0xbe - opcode_mov_reg_immed16_32
;   mov_reg_immed16_32                      ; 0xbf - opcode_mov_reg_immed16_32
;   check_reg_c0                            ; 0xc0 - opcode_check_reg_c0
;   check_reg_c1                            ; 0xc1 - opcode_check_reg_c1
;;  retn	8                               ; 0xc2 - opcode_retn_immed
;;  retn                                    ; 0xc3 - opcode_retn
;   les                                     ; 0xc4 - opcode_les
;   lds                                     ; 0xc5 - opcode_lds
;   check_reg_c6                            ; 0xc6 - opcode_check_reg_c6
;   check_reg_c7                            ; 0xc7 - opcode_check_reg_c7
;;  enter	12,4                            ; 0xc8 - opcode_enter
;;  leave                                   ; 0xc9 - opcode_leave
;   retf_immed                              ; 0xca - opcode_retf_immed
;;  retf                                    ; 0xcb - opcode_retf
;;  int3                                    ; 0xcc - opcode_int3
;;  int		3                               ; 0xcd - opcode_intx
;;  into                                    ; 0xce - opcode_into
;;  iret                                    ; 0xcf - opcode_iret
;   check_reg_d0                            ; 0xd0 - opcode_check_reg_d0
;   check_reg_d1                            ; 0xd1 - opcode_check_reg_d1
;   check_reg_d2                            ; 0xd2 - opcode_check_reg_d2
;   check_reg_d3                            ; 0xd3 - opcode_check_reg_d3
;;  aam                                     ; 0xd4 - opcode_aam
;;  aad                                     ; 0xd5 - opcode_aad
;   unused                                  ; 0xd6 - opcode_unused
;;  xlat                                    ; 0xd7 - opcode_xlat
;   fpu_d8                                  ; 0xd8 - opcode_fpu_d8
;   fpu_d9                                  ; 0xd9 - opcode_fpu_d9
;   fpu_da                                  ; 0xda - opcode_fpu_da
;   fpu_db                                  ; 0xdb - opcode_fpu_db
;   fpu_dc                                  ; 0xdc - opcode_fpu_dc
;   fpu_dd                                  ; 0xdd - opcode_fpu_dd
;   fpu_de                                  ; 0xde - opcode_fpu_de
;   fpu_df                                  ; 0xdf - opcode_fpu_df
;   loopne                                  ; 0xe0 - opcode_loopne
;   loope                                   ; 0xe1 - opcode_loope
;   loop                                    ; 0xe2 - opcode_loop
;   jcxz                                    ; 0xe3 - opcode_jcxz
;   in8_immed8                              ; 0xe4 - opcode_in8_immed8
;   in16_32_immed8                          ; 0xe5 - opcode_in16_32_immed8
;   out                                     ; 0xe6 - opcode_out
;   out                                     ; 0xe7 - opcode_out
;   call_near_relative                      ; 0xe8 - opcode_call_near_relative
;   jmp16_32                                ; 0xe9 - opcode_jmp16_32
;   jmp_far                                 ; 0xea - opcode_jmp_far
;   jmp8                                    ; 0xeb - opcode_jmp8
;   in_byte                                 ; 0xec - opcode_in_byte
;   in                                      ; 0xed - opcode_in
;   out_byte                                ; 0xee - opcode_out_byte
;   out                                     ; 0xef - opcode_out
;   lock_prefix                             ; 0xf0 - opcode_lock_prefix
;   unused                                  ; 0xf1 - opcode_unused
;   repne_prefix                            ; 0xf2 - opcode_repne_prefix
;   repe_prefix                             ; 0xf3 - opcode_repe_prefix
;;  hlt                                     ; 0xf4 - opcode_hlt
;;  cmc                                     ; 0xf5 - opcode_cmc
;   check_reg_f6                            ; 0xf6 - opcode_check_reg_f6
;   check_reg_f7                            ; 0xf7 - opcode_check_reg_f7
;;  clc                                     ; 0xf8 - opcode_clc
;;  stc                                     ; 0xf9 - opcode_stc
;;  cli                                     ; 0xfa - opcode_cli
;;  sti                                     ; 0xfb - opcode_sti
;;  cld                                     ; 0xfc - opcode_cld
;;  std                                     ; 0xfd - opcode_std
;   check_reg_fe                            ; 0xfe - opcode_check_reg_fe
;   check_reg_ff                            ; 0xff - opcode_check_reg_ff
