//////////
//
// /libsf/vvm/vvm/vmm_defs.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     September 19, 2012 - Initial creation
//     September 29, 2012 - PBL v1.0 license included directly in source files.
//     November 07, 2012 - 0.60 development begins
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
// Function prototype definitions
//////
	struct _ivvme_executeThreadSnippetData;
	struct _ivvmtm_SMainLoop;

	// vvm_eng.cpp
	bool					ivvme_initialize							(LPWSTR tcCmdLine, bool* tlTestCasesOnly);
	void					ivvme_executeThread							(SThread* tt, u64 tnTicks);
	void					ivvme_executeThreadSnippet					(SThread* tt, u64 tnTicks, SSnip* ts);

	void					ivvme_executeThreadSnippet_uadd64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_uadd32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_uadd16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_uadd8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_usub64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_usub32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_usub16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_usub8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_umul64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_umul32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_umul16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_umul8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_udiv64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_udiv32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_udiv16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_udiv8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ucomp64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ucomp32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ucomp16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ucomp8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_saddf64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_saddf32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sadd64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sadd32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sadd16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sadd8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ssubf64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ssubf32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ssub64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ssub32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ssub16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ssub8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_smulf64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_smulf32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_smul64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_smul32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_smul16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_smul8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sdivf64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sdivf32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sdiv64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sdiv32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sdiv16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sdiv8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_scompf64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_scompf32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_scomp64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_scomp32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_scomp16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_scomp8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copyf64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copyf32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_movef64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_movef32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_move64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_move32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_move16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_move8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchf64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchf32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xch64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xch32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xch16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xch8				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchuadd64		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchuadd32		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchuadd16		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchuadd8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchumul64		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchumul32		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchumul16		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchumul8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsaddf64		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsaddf32		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsadd64		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsadd32		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsadd16		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsadd8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsmulf64		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsmulf32		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsmul64		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsmul32		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsmul16		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xchsmul8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_and64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_and32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_and16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_and8				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_or64				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_or32				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_or16				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_or8				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_not64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_not32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_not16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_not8				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xor64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xor32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xor16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_xor8				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_chgsf64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_chgsf32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_neg64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_neg32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_neg16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_neg8				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_incf64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_incf32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_inc64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_inc32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_inc16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_inc8				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_decf64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_decf32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_dec64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_dec32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_dec16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_dec8				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shl64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shl32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shl16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shl8				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shur64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shur32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shur16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shur8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shsr64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shsr32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shsr16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_shsr8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_rol64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_rol32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_rol16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_rol8				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ror64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ror32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ror16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_ror8				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_cnvobj			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy3232fi		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy3232if		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy6464fi		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy6464if		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy3264fi		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy3264if		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy6432fi		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy6432if		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy64fs			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copy64sf			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copyresult		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_allocs			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_deallocs			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_debug			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_halt				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_nop				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_lenobj			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_numobja			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_numobju			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_nua				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_nun				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_setipxs			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_setipx			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_adjip64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_adjip32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_adjip16			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_adjip8			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_callsn			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_callsna			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_callsnu			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_callsdn			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_calldsna			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_calldsnu			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_callhn			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_callhna			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_push64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_pop64			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_push32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_pop32			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_stackcpy32		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_return			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_rettonam			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_rettonum			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sflag			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_cflag			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_tflag			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_inflag			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_outflag			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_setc				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_seto				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_setu				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sete				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_setz				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_setn				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_setp				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_seta				(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_setan			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_clran			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_togan			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_loadtheme		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_renderstart		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_rendrregion		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_rendercanvas		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_renderscreen		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_renderstop		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_appoapa			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_appoach			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_appoapr			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_appoane			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_delofo			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_destroy			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_iscatter			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_fscatter			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_igather			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_fgather			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_tmraddg			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_tmrdelg			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_tmrenag			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_tmrdisg			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_tmraddt			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_tmrdelt			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_tmrenat			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_tmrdist			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_passive			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_active			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_setexs			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_exceps			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_thrap			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_thraps			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_thras			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_thraf			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_thrst			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_thrsp			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_thrxt			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_thrxp			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_thrxr			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_thrxrs			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_thrxj			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_screate			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_slock			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_strylock			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sunlock			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_sdelete			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_predicate		(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_copypred			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_unused			(_ivvme_executeThreadSnippetData* tsed);
	void					ivvme_executeThreadSnippet_extended			(_ivvme_executeThreadSnippetData* tsed);


	// vvm_tm.cpp
	bool					ivvmtm_initialize							(void);
	void					ivvmtm_mainLoop								(void* ttm);
	void					ivvmtm_mainLoopPrograms						(_ivvmtm_SMainLoop* tml);
	void					ivvmtm_mainLoopThreads						(_ivvmtm_SMainLoop* tml);
	void					ivvmtm_mainLoopAttemptThreadExecution		(_ivvmtm_SMainLoop* tml);
	void					ivvmtm_mainLoopThreadExecute				(_ivvmtm_SMainLoop* tml);

	// vvm_sup.cpp
	bool					ivvm_initializeProgram						(SProgram* tp);
	bool					ivvm_reallocateVariableBlock				(SStartEnd* ptrSEVar, u32 tnAllocationSize);
	bool					ivvm_allocateThread							(SStartEnd* ptrSEVar, SThread** ttSlot);
	bool					ivvm_reallocateSnippets						(SStartEnd* ptrSESnip);
	bool					ivvm_allocateSnippetParamsReturnsLocals		(SSnipExec* tse);
	bool					ivvm_allocateSnippetVariables				(SStartEnd* ptrSEVar, u32 tnAllocationSize);
	

	// vvm_vo.cpp
	bool					ivvm_loadAndInitializeVvmOss				(void);
	u64 CALLTYPE			vvm_debuggerInterfaceCallback				(s8* tcFunctionName);

	// vvm_vvmmc.cpp
	bool					ivvm_loadAndInitializeVvmmc					(void);

	// vvm_res.cpp
	bool					ivvm_loadVvmResourceDll						(void);

	// vvm_misc.cpp
	void					iivvm_bootupInitialization					(void);
	u64						ivvm_resourceMessageBox						(int tnMessage, int tnCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);
	u64						ivvm_resourceMessageBoxLocal				(int tnMessage, int tnCaption, bool tlYes,                       bool tlRetry, bool tlCancel);
	void					ivvm_resourceGetString						(int tnMessage, wchar_t** tuString);
	void					ivvm_resourcePrintf							(int tnMessage);
	void					ivvm_resourcePrintf1						(int tnMessage, void* p1);
	void					ivvm_parseCommandLine						(w16* tcCmdLine, bool* tlTestCasesOnly);
	int						ivvm_unicodeMemicmp							(w16* l, w16* r, u32 tnLength);
	w16						ivvm_lowerCaseW								(w16 u);
	int						ivvm_scanStringAndNullTerminateAtNextWhitespaceW(w16* tcString);
	bool					iivvm_loadResourceAsciiTextCallback			(SStartEndCallback* cb);
	bool					ivvm_debugBreaksOn							(void);
	bool					ivvm_debugBreaksOff							(void);
	void					ivvm_debugBreak								(void);
	bool					ivvm_debugBreaksOn							(bool* tlTest);
	bool					ivvm_debugBreaksOff							(bool* tlTest);
	void					ivvm_debugBreak								(bool* tlTest);

	// vvm_tests.cpp
	void					ivvm_runTestPlugins							(void);
	bool					ivvm_loadTestsByName						(u64 lnHandleLog, csu8p tcDirectory, csu8p tcFilePattern, csu8p tcExclusionList);
	bool					iivvm_runVvmTest							(u64 lnHandleLog, SFindFile* tff);




//////////
// Callback from any connecting debuggers
//////
	// See devhelp.txt.  Duplicate changes here in VDebug.h, vvm.cpp, vvm_v1.cpp, vvm_defs.h, and vo_class.h.
	// vvm_v1.cpp
	u64 CALLTYPE			vvm1_debugger								(s8* functionName);
	s8* CALLTYPE			vvm1_getLanguage							(u32* tnLength);
	s8* CALLTYPE			vvm1_loadResourceAsciiText					(u32 tnResourceNumber);
	void CALLTYPE			vvm1_resourcePrintf							(u32 tnResourceNumber);
	u64 CALLTYPE		 	vvm1_requestUniqueID						(void);
	u64 CALLTYPE		 	vvm1_connect								(u64 id, s8* tcPath);
	u64 CALLTYPE		 	vvm1_connectRemote							(u64 id, s8* tcPath, s8* ipAddressOrMachineName);
	u64 CALLTYPE			vvm1_getNextUniqueId						(void);

	void CALLTYPE			vvm1_copyProgramList						(u64 id, SProgram** list, u32* count);
	void CALLTYPE			vvm1_programCopyScreensList					(u64 id, SProgram* program, SScreen**	list, u32* count);
	void CALLTYPE			vvm1_programCopyGlobalsList					(u64 id, SProgram* program, SVariable** list, u32* count);
	void CALLTYPE			vvm1_programCopySnippetsList				(u64 id, SProgram* program, SSnipExec** list, u32* count);
	void CALLTYPE			vvm1_programCopyDynamicSnippetsList			(u64 id, SProgram* program, SDynSnip**  list, u32* count);
	void CALLTYPE			vvm1_programCopyTimersList					(u64 id, SProgram* program, STimer**	list, u32* count);
	void CALLTYPE			vvm1_programCopyThreadsList					(u64 id, SProgram* program, SThread**	list, u32* count);

	u64 CALLTYPE		 	vvm1_programPause							(u64 id, SProgram* program);
	u64 CALLTYPE		 	vvm1_programResume							(u64 id, SProgram* program, bool singleStep);
	u64 CALLTYPE		 	vvm1_programTerminate						(u64 id, SProgram* program);
	u64 CALLTYPE		 	vvm1_threadPause							(u64 id, SThread* thread);
	u64 CALLTYPE		 	vvm1_threadResume							(u64 id, SThread* thread, bool singleStep);
	u64 CALLTYPE		 	vvm1_threadTerminate						(u64 id, SThread* thread);
	void CALLTYPE			vvm1_terminateVvm							(u64 id, bool tlPolitely);

	void CALLTYPE			vvm1_getBreakpointList						(u64 id, SBreakpoint** root, u32* count);
	SBreakpoint* CALLTYPE	vvm1_breakpointSet							(u64 id, SSnipExec* snippet, SLine* line, SBreakCond* bc, bool enable);
	bool CALLTYPE			vvm1_breakpointClear						(u64 id, SBreakpoint* bp);

	bool CALLTYPE			vvm1_copyProgram							(u64 id, SProgram*	program,	SProgram**		copy);
	bool CALLTYPE			vvm1_copyThread								(u64 id, SThread*	thread,		SThread**		copy);
	bool CALLTYPE			vvm1_copyStack								(u64 id, SThread*	thread,		SStack**		copy);
	bool CALLTYPE			vvm1_copyRegisters							(u64 id, SThread*	thread,		SRegs**	copy);
	bool CALLTYPE			vvm1_copyGlobal								(u64 id, SVariable*	global,		SVariable**		copy);
	bool CALLTYPE			vvm1_copyTimer								(u64 id, STimer*	 timer,		STimer**		copy);
	bool CALLTYPE			vvm1_copyScreen								(u64 id, SScreen*	screen,		SScreen**		copyScreen,		SCanvas**	copyCanvas);
	bool CALLTYPE			vvm1_copyCanvas								(u64 id, SCanvas*	canvas,		SScreen**		copy);
	bool CALLTYPE			vvm1_copySnippetTS							(u64 id, SThread*	snippet,	SSnipExec**		copyS,			SDynSnip*	copyDS,		bool* isDynSnip);
	bool CALLTYPE			vvm1_copySnippetParent						(u64 id, SSnipExec*	snippet,	SSnipExec**		copyS,			SDynSnip*	copyDS,		bool* isDynSnip);
	bool CALLTYPE			vvm1_copySnippetSS							(u64 id, SSnipExec*	snippet,	SSnipExec**		copy);
	bool CALLTYPE			vvm1_copyDynamicSnippet						(u64 id, SDynSnip*	dynSnippet,	SDynSnip**		copy);

	SUpSnip* CALLTYPE		vvm1_snippetCompile							(u64 id, SLine* firstLineOfSnippetSourceCode);
	SUpLine* CALLTYPE		vvm1_snippetCompileLine						(u64 id, SSnipExec* snippet,		SLine* originalLineOfSnippetSourceCode, SLine* replacementLineOfSnippetSourceCode, bool commitIfCompilesOkay);
	SUpLine* CALLTYPE		vvm1_dynSnipCompileLine						(u64 id, SDynSnip* dynSnippet,	SLine* originalLineOfDynSnipSourceCode, SLine* replacementLineOfDynSnipSourceCode, bool commitIfCompilesOkay);

	bool CALLTYPE			vvm1_snippetDelete							(u64 id, SSnipExec* snippet);
	bool CALLTYPE			vvm1_snippetUpdate							(u64 id, SSnipExec* snippet,	SUpSnip* newSnippet);
	u64 CALLTYPE		 	vvm1_snippetAppend							(u64 id, SSnipExec* snippet);
	bool CALLTYPE			vvm1_dynamicSnippetDelete					(u64 id, SDynSnip* dynSnippet);
	bool CALLTYPE			vvm1_dynamicSnippetUpdate					(u64 id, SDynSnip* dynSnippet, SUpSnip* newSnippet);
	u64 CALLTYPE		 	vvm1_dynamicSnippetAppend					(u64 id, SDynSnip* dynSnippet);
	bool CALLTYPE			vvm1_flushChangesToBxml						(u64 id, SProgram* program);

	u64 CALLTYPE			vvm1_createThread							(u64 id, void* functionAddress, u32 tnParameter);
	u64 CALLTYPE			vvm1_messageBox								(u64 id, s8* tcText, s8* tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel);

	void CALLTYPE		 	vvm1_enableBreakpoints						(u64 id);
	void CALLTYPE		 	vvm1_disableBreakpoints						(u64 id);
