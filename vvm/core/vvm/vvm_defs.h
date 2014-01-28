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
	u64						ivvm_getNextUniqueId						(void);
	u64						ioss_getNextN_UniqueIds						(u64* tnArrayBase, u32 tnCount);
	bool					ivvm_reallocateVariableBlock				(SStartEnd* ptrSEVar, u32 tnAllocationSize);
	bool					ivvm_allocateThread							(SStartEnd* ptrSEVar, SThread** ttSlot);
	bool					ivvm_reallocateSnippets						(SStartEnd* ptrSESnip);
	bool					ivvm_allocateSnippetParamsReturnsLocals		(SSnipExec* tse);
	bool					ivvm_allocateSnippetVariables				(SStartEnd* ptrSEVar, u32 tnAllocationSize);
	u64						ioss_skipWhitespacesAndCrLf					(s8* tcData, u64 tnMaxLength);
inline bool					ioss_verifyLength							(u64 tnGoingTo, u64 tnMaxAllowable);
	bool					ioss_isAlpha								(s8 c);
	bool					ioss_isNumeric								(s8 c);
	bool					ioss_isAlphanumeric							(s8 c);
	u32						ioss_convertValidatedNumericStringToU32		(s8* tcData, u32 tnMaxLength);
	u64						ioss_convertValidatedNumericStringToU64		(s8* tcData, u32 tnMaxLength);
	void					ivvm_ll4_deleteChainAllNodes				(SLL4Callback* cb, SLL4* root);
	void					iivvm_ll4_deleteChainAllNodes				(SStartEnd* nodeList, SLL4* root, u32 tnDirection);
	void					ioss_bufferVerifySizeForNewBytes			(SBuilder* buffRoot, u32 tnDataLength);
	void*					ivvm_SEChain_appendOrPrepend				(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult);
	void*					ivvm_SEChain_appendOrPrependExisting		(SStartEnd* ptrSE, SLL* ptrExisting, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult);
	void					ivvm_SEChain_appendMasterList				(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded);
	void					ivvm_SEChain_freeUpSlot						(SStartEnd* ptrSE, u32 tnSlot, u32 tnBlockSizeIfNewBlockNeeded);
	void					ioss_deleteFromSEChainMasterList			(SStartEnd* ptrSE, void* ptrDel);
	void					iivvm_math_computeTriangle					(STriangleF64* tri);
	void					iivvm_math_computeSquare					(SSquareInOutF64* sq, f32 ox, f32 oy);
	void					iivvm_math_computeLine						(SLineF64* line);
	s32						iioss_math_computeQuad						(SXYF64* p);
	void					iioss_copyLine								(SLineF64* line, SXYF64* p1, SXYF64* p2, bool tlComputeLine);
	void					ivvm_math_squareRotateAbout					(SSquareInOutF64* sq);
	bool					iivvm_polygon_initialize					(SPolygon* poly, u32 tnLineCount, bool tlAllocatePolyLines);
	bool					iivvm_polygon_setByPolyLine					(SPolygon* poly, u32 tnEntry, SPolyLine* line);
	bool					iivvm_polygon_setByValues					(SPolygon* poly, u32 tnEntry, SXYF64* start, SXYF64* end, SXYF64* gravity);
	void					iioss_canvasPolygon_processSmall			(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_processNormal			(SCanvas* tsDst, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_draw					(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_computeLine				(SCanvas* tsDst, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_getCornerFloans			(_isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_getRangeFloans				(SCanvas* tsDst, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_drawPixelFloans				(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp);
	void					iioss_canvasPolygon_drawRangeFloans				(                SBGRA* bd, SPolygon* poly, _isSCanvasDrawPolygonParameters* lcdp);
	bool					iioss_canvasPolygon_determineIfSmall			(SPolygon* poly);
	int						iioss_canvasPolygon_qsortFloansCallback			(const void* l, const void* r);
	u32						iioss_canvasPolygon_getNextLineSegment			(u32 tnIndex, u32 tnMaxCount, SBGRACompute* sbgracRoot, SBGRACompute** p1, SBGRACompute** p2);
	void					iioss_canvasPolygon_storeCorner					(SBuilder* corners, SXYF64* po, SXYF64* pi, _isSStoreFloan_lineData* sfld);
	void					iioss_canvasPolygon_storeFloans					(_isSStoreFloan_lineData* sfld);
	void					iioss_canvasPolygon_storeFloansCorner			(_isSStoreFloan_lineData* sfld, _isSStoreFloan_cornerData* sfcd1, _isSStoreFloan_cornerData* sfcd2);
	u32						iivvm_math_getGravityOfThetaAndLeft				(f64 tfTheta, bool tlLeft);
	s32						iivvm_math_getGravity07FromDecoratedGravity		(u32 tnGravityDecorated);
	f64						iivvm_math_getAreaOfSquareUsing_po_p1_p2		(s32 tnGravity07po, s32 tnGravity07_p1, s32 tnGravity07_p2, SXYF64* po, SXYF64* p1, SXYF64* p2);
	void					iivvm_math_getNextAxisInterceptXY				(SXYF64* p, f64 tfTheta);
	s32						iivvm_math_getGravityByRelativePosition			(SXYF64* p, SXYS32* po);
	s32						iivvm_math_getGravityInteger					(SXYS32* p, SXYS32* po);
	s32						iivvm_math_fineAdjustGravityByTheta				(SXYF64* po, SXYF64* p, SXYF64* pg, s32 lnGravity07p, s32 lnGravity07pg);
	f64						iivvm_math_adjustTheta							(f64 tfTheta);
	bool					iivvm_math_withinDelta							(f64 tfValue1, f64 tfValue2, s32 tnDeltaDecimals);
	void					iioss_math_multiplyBy							(SXYF64* p, f64 tfMultiplier);
	u64						iioss_canvasRotateAbout							(SCanvas* tsDst, SBGRA* bdd, s32 ulx, s32 uly, SCanvas* tsSrc, SBGRA* bds, f32 tfRadians, f32 ox, f32 oy);
	u64						iioss_canvasBezier3								(SCanvas* tc, SBGRA* bd, SBezier* bez);
	u64						iioss_canvasBezier4								(SCanvas* tc, SBGRA* bd, SBezier* bez);
	u64						iioss_canvasBezier5								(SCanvas* tc, SBGRA* bd, SBezier* bez);
	void					iioss_canvasBezier_wash							(SCanvas* tc, SBGRA* bd, SBuilder** pointFloans, SBuilder** washFloans, SBezier* bez);
	u64						iioss_canvasBezier_draw							(SCanvas* tc, SBGRA* bd, SBezier* bez);
	u64 					iivvm_math_washFloans							(SCanvas* tc, SBGRA* bd, SBuilder** pointFloans, SBuilder** washFloans, SBuilder** drawFloans, bool tlIsFilledLeft);
	u64						iivvm_math_washFloans_doDraw					(SCanvas* tc, SBGRA* bd, SBuilder** washFloans, SBuilder** drawFloans, bool tlIsFilledLeft);
	void					ioss_regionRefreshCallback						(SStartEndCallback* cb);

//////////
// The following functions handle floan segments from point to point.
//      NW __N__ NE     2__3__4
//      W |     |E      1  8  5		// Note:  8 is only used when comparing integers, as they refer to entire pixels compared with other entire pixels, 8 means they are both of the same location
//      SW|__S__|SE     0__7__6
//////
	void					storeFloan_pointToPoint_bad						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_0_2						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_0_3						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_0_4						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_0_5						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_0_6						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_1_3						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_1_4						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_1_5						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_1_6						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_1_7						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_2_0						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_2_4						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_2_5						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_2_6						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_2_7						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_3_0						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_3_1						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_3_5						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_3_6						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_3_7						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_4_0						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_4_1						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_4_2						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_4_6						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_4_7						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_5_0						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_5_1						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_5_2						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_5_3						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_5_7						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_6_0						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_6_1						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_6_2						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_6_3						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_6_4						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_7_1						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_7_2						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_7_3						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_7_4						(_isSStoreFloan_lineData* sfld);
	void					storeFloan_pointToPoint_7_5						(_isSStoreFloan_lineData* sfld);


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

//////////
//
// Build Buffer
// An accumulation template for appending data in a stream manner, or for allocating a specified
// size and then randomly updating it.
//
//////////
	void CALLTYPE			vvm1_builderCreateAndInitialize				(SBuilder** buffRoot, u32 tnAllocationSize);
	s8* CALLTYPE			vvm1_builderAppendData						(SBuilder*  buffRoot, s8* tcData, u32 tnDataLength);
	s8* CALLTYPE			vvm1_builderAllocateBytes					(SBuilder*	buffRoot, u32 tnDataLength);
	void CALLTYPE			vvm1_builderSetSize							(SBuilder*  buffRoot, u32 tnBufferLength);
	void CALLTYPE			vvm1_builderFreeAndRelease					(SBuilder** buffRoot);
	u32 CALLTYPE			vvm1_builderAsciiWriteOutFile				(SBuilder*  buffRoot, s8* tcFilename);


//////////
//
// SHA-1
// Computes SHA-1 values in various ways.  The Start/ProcessThisData/Finish sections are to
// be used when a computation must be conducted over multiple source calls.
//
//////
	void CALLTYPE			vvm1_sha1ComputeSha1						(s8* tcData, u32 tnDataLength, u8 shaOutput[20]);
	u64 CALLTYPE			vvm1_sha1ComputeSha1As64Bit					(s8* tcData, u32 tnDataLength);
	u32 CALLTYPE			vvm1_sha1ComputeSha1As32Bit					(s8* tcData, u32 tnDataLength);
	void CALLTYPE			vvm1_sha1ComputeSha1AsHex					(s8* tcData, u32 tnDataLength, s8* tcHexOutput, bool tlInsertSpaces);
	void CALLTYPE			vvm1_sha1ConvertHexToSha1					(u8 shaOutput[20], s8* tcHexInput, bool* tlError);
	void CALLTYPE			vvm1_sha1ConvertSha1ToHex					(s8* tcHexInput, u8 shaOutput[20], bool tlInsertSpaces);
	void CALLTYPE			vvm1_sha1ComputeSha1_Start					(u8 context[92]);
	void CALLTYPE			vvm1_sha1ComputeSha1_ProcessThisData		(u8 context[92], s8* tcData, u32 tnDataLength);
	void CALLTYPE			vvm1_sha1ComputeSha1_FinishAsSha1			(u8 context[92], u8 shaOutput[20], bool tlWipeData);
	void CALLTYPE			vvm1_sha1ComputeSha1_FinishAsHex			(u8 context[92], s8* tcHexOutput, bool tlInsertSpaces, bool tlWipeData);
	u64 CALLTYPE			vvm1_sha1Compute64BitFromSha1				(u8 sha20Bytes[20]);
	u32 CALLTYPE			vvm1_sha1Compute32BitFromSha1				(u8 sha20Bytes[20]);
	bool CALLTYPE			vvm1_sha1Compare							(u8 sha20Bytes1[20], u8 sha20Bytes2[20]);


//////////
//
// BXML
// The following functions relate the BXML engine as provided by the VVMOSS.
// It is created to provide an autonomous and robust way to access any BXML file
// as created by this engine.
//
//////////
	SBxml* CALLTYPE			vvm1_bxmlLoad								(s8* tcPathname, u32 tnPathnameLength, u64* tnBytesRead, u64* tnErrorOffset, u64* tnErrorCode);
	SBxml* CALLTYPE			vvm1_bxmlLoadFromBuffer						(s8* tcBxmlData, u32 tnBxmlDataLength,                   u64* tnErrorOffset, u64* tnErrorCode);
	bool CALLTYPE			vvm1_bxmlSave								(SBxml* bxml, s8* tcPathname, u32 tnPathnameLength, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnErrorNumber);
	void CALLTYPE			vvm1_bxmlSaveToBuffer						(SBxml* bxml, SBuilder** build, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnErrorNumber);

	SBxmla* CALLTYPE		vvm1_bxmlaCreate							(s8* tcNewName, u32 tnNewNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength);
	bool CALLTYPE			vvm1_bxmlaSetName							(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength);
	bool CALLTYPE			vvm1_bxmlaSetData							(SBxmla* bxmla, s8* tcData, u32 tnDataLength);
	bool CALLTYPE			vvm1_bxmlaSetTotalLength					(SBxmla* bxmla, u32 tnDataLengthTotal);
	SBxmla* CALLTYPE		vvm1_bxmlaDelete							(SBxmla* bxmla, bool tlFreeMemory);
	bool CALLTYPE			vvm1_bxmlaInsert							(SBxml* bxml, SBxmla* bxmlaRef, s8* tcName, u32 tnNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength, bool tlAfter);
	bool CALLTYPE			vvm1_bxmlaInsertExisting					(SBxml* bxml, SBxmla* bxmlaRef, SBxmla* bxmlaNew, bool tlAfter);
	SBxmla* CALLTYPE		vvm1_bxmlaCopy								(SBxmla* bxmla);
	SBxmla* CALLTYPE		vvm1_bxmlaCopyAs							(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength);
	u64 CALLTYPE			vvm1_bxmlaSha1One							(SBxmla* bxmla, u8 sha20Bytes[20]);
	u64 CALLTYPE			vvm1_bxmlaSha1								(SBxml* bxml, u8 sha20Bytes[20]);
	u64 CALLTYPE			vvm1_bxmlaSha1Tag							(SBxml* bxml, u8 sha20Bytes[20]);
	u64 CALLTYPE			vvm1_bxmlaSha1Data							(SBxml* bxml, u8 sha20Bytes[20]);

	u32 CALLTYPE			vvm1_bxmlaFindAndGetString					(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, SDatum* tsResult, bool* tlError);
	u32 CALLTYPE			vvm1_bxmlaFindAndGetU32						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
	u64 CALLTYPE			vvm1_bxmlaFindAndGetU64						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
	bool CALLTYPE			vvm1_bxmlaFindAndGetBool					(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
	f32 CALLTYPE			vvm1_bxmlaFindAndGetF32						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);
	f64 CALLTYPE			vvm1_bxmlaFindAndGetF64						(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError);

	u32 CALLTYPE			vvm1_bxmlaGetString							(SBxmla* bxmla, SDatum* tsResult, bool* tlError);
	u32 CALLTYPE			vvm1_bxmlaGetU32							(SBxmla* bxmla, bool* tlError);
	u64 CALLTYPE			vvm1_bxmlaGetU64							(SBxmla* bxmla, bool* tlError);
	bool CALLTYPE			vvm1_bxmlaGetBool							(SBxmla* bxmla, bool* tlError);
	f32 CALLTYPE			vvm1_bxmlaGetF32							(SBxmla* bxmla, bool* tlError);
	f64 CALLTYPE			vvm1_bxmlaGetF64							(SBxmla* bxmla, bool* tlError);

	// For 2-way navigation through the attributes (can be done manually, but these expressly do it
	SBxmla* CALLTYPE		vvm1_bxmlaGetNext							(SBxmla* bxmla);
	SBxmla* CALLTYPE		vvm1_bxmlaGetPrev							(SBxmla* bxmla);

	SBxml* CALLTYPE			vvm1_bxmlNodeCreate							(s8* tcNewName, u32 tnNewNameLength);
	bool CALLTYPE			vvm1_bxmlNodeSetName						(SBxml* bxml, s8* tcNewName, u32 tnNewNameLength);
	bool CALLTYPE			vvm1_bxmlNodeDelete							(SBxml* bxml, bool tlFreeMemory);
	bool CALLTYPE			vvm1_bxmlNodeInsert							(SBxml* bxml, SBxml* bxmlRef,                                     bool tlAfter);
	bool CALLTYPE			vvm1_bxmlNodeInsertAsChild					(SBxml* bxml, SBxml* bxmlParent,                                  bool tlAfter);
	bool CALLTYPE			vvm1_bxmlNodeInsertAsChildAfter				(SBxml* bxml, SBxml* bxmlParent, SBxml* bxmlRef,                  bool tlAfter);
	SBxml* CALLTYPE			vvm1_bxmlNodeCopy							(SBxml* bxml,                                        bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult);
	SBxml* CALLTYPE			vvm1_bxmlNodeCopyAs							(SBxml* bxml,    s8* tcNewName, u32 tnNewNameLength, bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult);
	u64 CALLTYPE			vvm1_bxmlNodeSha1							(SBxml* bxml, u8 sha20Bytes[20]);
	u64 CALLTYPE			vvm1_bxmlNodeSha1Tag						(SBxml* bxml, u8 sha20Bytes[20]);
	u64 CALLTYPE			vvm1_bxmlNodeSha1Data						(SBxml* bxml, u8 sha20Bytes[20]);

	// For 4-way navigation through the XML structure (can be done manually, but these expressly do it
	SBxml* CALLTYPE			vvm1_bxmlNodeGetNext						(SBxml* bxml);
	SBxml* CALLTYPE			vvm1_bxmlNodeGetPrev						(SBxml* bxml);
	SBxml* CALLTYPE			vvm1_bxmlNodeGetParent						(SBxml* bxml);
	SBxml* CALLTYPE			vvm1_bxmlNodeGetFirstChild					(SBxml* bxml);
	SBxmla* CALLTYPE		vvm1_bxmlNodeGetFirstAttribute				(SBxml* bxml);

	// Searches node or attribute names for the indicated wildcard search string
	SBxmla* CALLTYPE		vvm1_bxmlFindAttribute						(SBxml* bxml, SDatum* tsWildcardSearch, u32 tnInstance);
	bool CALLTYPE			vvm1_bxmlFindFirst							(SBxml* bxmlRoot, SBxml* bxmlNodeFound, SBxmla* bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, bool tlSearchAttributes, void** x);
	bool CALLTYPE			vvm1_bxmlFindContinue						(void* x);
	u32 CALLTYPE			vvm1_bxmlFindAllAsStartEndLists				(SBxml* bxmlRoot, SStartEnd** bxmlFinds, SStartEnd** bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren, bool tlSearchAttributes);
	// Searches populated data in attributes for the indicated wildcard search string
	bool CALLTYPE			vvm1_bxmlDataFindFirst						(SBxml* bxmlRoot, SBxmla* bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, void** x);
	bool CALLTYPE			vvm1_bxmlDataFindContinue					(void* x);
	u32 CALLTYPE			vvm1_bxmlDataFindAllAsStartEndList			(SBxml* bxmlRoot, SStartEnd** bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren);

	void CALLTYPE			vvm1_bxmlGetLastError						(SBxmlError* errorInfo);


//////////
//
// Common functions (previously in common.h)
//
//////
	// Prototype definitions
	u8* CALLTYPE			vvm1_duplicateString						(u8* ptr, u64 length);
	w16* CALLTYPE			vvm1_duplicateUnicodeString					(w16* tuText);
	SDatum* CALLTYPE		vvm1_datumSet								(SDatum*  datum,  u8* ptr, u64 length,                  bool tlFreeExisting);
	SDatum2* CALLTYPE		vvm1_datum2Set								(SDatum2* datum2, u8* ptr, u64 length, u64 totalLength, bool tlFreeExisting);
	SDatum* CALLTYPE		vvm1_datumDuplicate							(SDatum*  datumDst,  SDatum*  datumSrc);
	SDatum2* CALLTYPE		vvm1_datum2Duplicate						(SDatum2* datum2Dst, SDatum2* datum2Src);
	void CALLTYPE			vvm1_datumDelete							(SDatum*  datum);
	void CALLTYPE			vvm1_datum2Delete							(SDatum2* datum2);
	void CALLTYPE			vvm1_datum2SetNullString					(SDatum2* datum2, u64 length, bool tlInitialize);
	void CALLTYPE			vvm1_copyUpToShortestString					(u8* dst, u32 tnDstLength, u8* src, u32 tnSrcLength);
	s32 CALLTYPE			vvm1_wildcardMatchDatum						(SDatum* tsCandidate, SDatum* tsWildcardPattern, bool tlCaseSensitive);
	s32 CALLTYPE			vvm1_wildcardMatch							(csu8p candidate, csu8p wildcardPattern, bool tlCaseSensitive);
	w16* CALLTYPE			vvm1_asciiToUnicode							(u8* tcText, u32 tnTextLength);
	s8* CALLTYPE			vvm1_unicodeToAscii							(w16* tuText, u32 tnTextLength);
	w16 CALLTYPE			vvm1_asciiToUnicodeChar						(u8 tcChar);
	s8 CALLTYPE				vvm1_unicodeToAsciiCharacter				(w16 tuChar);
	u64 CALLTYPE			vvm1_scanForwardUntilCharacterChanges		(csu8p tcData, u64 tnMaxLength);
	u64 CALLTYPE			vvm1_scanForwardUntilCharacter				(csu8p tcData, s8 c);
	int CALLTYPE			vvm1_unicodeMemcmp							(w16* l, w16* r, u32 tnLength);
	int CALLTYPE			vvm1_unicodeMemicmp							(w16* l, w16* r, u32 tnLength);
	int CALLTYPE			vvm1_unicodeMemset							(w16* p, w16 c, u32 tnLength);
	w16 CALLTYPE			vvm1_upperCaseW								(w16 u);
	w16 CALLTYPE			vvm1_lowerCaseW								(w16 u);
	void CALLTYPE			vvm1_memset									(s8* dst, s8 c, u64 tnCount);
	void CALLTYPE			vvm1_memset4								(u32* dst, u32 val, u64 tnCount);
	void CALLTYPE			vvm1_memcpy									(s8* dst, s8* src, u64 tnCount);
	s32 CALLTYPE			vvm1_memcmp									(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
	s32 CALLTYPE			vvm1_memicmp								(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
	s32 CALLTYPE			vvm1_memicmpTwoLengths						(csu8p l/*eft*/, u64 tnLeftLength, csu8p r/*ight*/, u64 tnRightLength);
	s32 CALLTYPE			vvm1_memicmpDatum							(SDatum*  datum,  csu8p r/*ight*/, u64 tnRightLength);
	s32 CALLTYPE			vvm1_memicmpDatum2							(SDatum2* datum2, csu8p r/*ight*/, u64 tnRightLength);
	s32 CALLTYPE			vvm1_memicmpDatumDatum						(SDatum*  datumL,  SDatum*  datumR);
	s32 CALLTYPE			vvm1_memicmpDatum2Datum2					(SDatum2* datum2L, SDatum2* datum2R);
	void CALLTYPE			vvm1_deriveRGBA								(u32 tnColor, u8* tnRed, u8* tnGrn, u8* tnBlu, f32* tfAlp);
	u8 CALLTYPE				vvm1_getPredictableSequentialPattern		(u32 tnIterator, u32 tnValue);

	SLL* CALLTYPE			vvm1_ll_create								(SLL* nodePrev, SLL* nodeNext, u64 tnUniqueId, u32  tnSize);
	void CALLTYPE			vvm1_ll_delete								(SLL* node);
	void CALLTYPE			vvm1_ll_deleteWithCallback					(SLLCallback* cb);
	bool CALLTYPE			vvm1_ll_insert								(SLL* node, SLL* nodeRef, bool tlAfter);
	void CALLTYPE			vvm1_ll_orphanize							(SLL* node);
	void CALLTYPE			vvm1_ll_deleteChain							(SLL** root);
	void CALLTYPE			vvm1_ll_deleteChainWithCallback				(SLLCallback* cb);
	void CALLTYPE			vvm1_ll_iterateViaCallback					(SLLCallback* cb);
	void CALLTYPE			vvm1_ll_iterateBackwardViaCallback			(SLLCallback* cb);
	SLL* CALLTYPE			vvm1_ll_getFirstNode						(SLL* node);
	SLL* CALLTYPE			vvm1_ll_getLastNode							(SLL* node);

	SLL4* CALLTYPE			vvm1_ll4_create								(SLL4* nodeWest, SLL4* nodeEast, SLL4* nodeNorth, SLL4* nodeSouth, u64 tnUniqueId, u32 tnSize);
	SLL4* CALLTYPE			vvm1_ll4_createChain						(u32 tnSize, u32* tnCount, u32 tnDirection);
	void CALLTYPE			vvm1_ll4_delete								(SLL4* node);
	void CALLTYPE			vvm1_ll4_deleteWithCallback					(SLL4* node);
	bool CALLTYPE			vvm1_ll4_orphanize							(SLL4* node);
	bool CALLTYPE			vvm1_ll4_insertNorthSouth					(SLL4* node, SLL4* nodeRef, bool tlAfter);
	bool CALLTYPE			vvm1_ll4_insertWestEast						(SLL4* node, SLL4* nodeRef, bool tlAfter);
	void CALLTYPE			vvm1_ll4_deleteChain						(SLL4** root, u32 tnDirection);
	void CALLTYPE			vvm1_ll4_deleteChainWithCallback			(SLL4Callback* cb, u32 tnDirection);
	void CALLTYPE			vvm1_ll4_iterateViaCallback					(SLL4Callback* cb, u32 tnDirection);
	SLL4* CALLTYPE			vvm1_ll4_getLastNode						(SLL4* node, u32 tnDirection);

	bool CALLTYPE			vvm1_ll4bxml_orphanize						(SLL4* bxml);
	bool CALLTYPE			vvm1_ll4bxml_insert							(SLL4* bxmlSibling,	SLL4* bxmlRef,							bool tlAfter);
	bool CALLTYPE			vvm1_ll4bxml_insertAsChild					(SLL4* bxmlChild,	SLL4* bxmlParent,						bool tlPrepend);
	bool CALLTYPE			vvm1_ll4bxml_insertAsChildRegarding			(SLL4* bxmlChild,	SLL4* bxmlParent, SLL4* bxmlRegarding,	bool tlAfter);

	void* CALLTYPE			vvm1_SEChain_prepend						(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void* CALLTYPE			vvm1_SEChain_append							(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void* CALLTYPE			vvm1_SEChain_appendRelativeToMember			(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize,     u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);
	void* CALLTYPE			vvm1_SEChain_appendExistingRelativeToMember	(SStartEnd* ptrSE, SLL* ptrRef,                 u64 tnUniqueIdExtra, SLL* ptrCaller, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);

	void* CALLTYPE			vvm1_SEChain_migrateAll						(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc);
	SMasterList* CALLTYPE	vvm1_SEChain_migrateByPtr					(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, void* ptr,    u32 tnHint, u32 tnBlockSize);
	SMasterList* CALLTYPE	vvm1_SEChain_migrateByNum					(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);
	SLL* CALLTYPE			vvm1_SEChain_completelyMigrateSLLByPtr		(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr,     u32 tnHint, u32 tnBlockSize);
	SLL* CALLTYPE			vvm1_SEChain_completelyMigrateSLLByNum		(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);

	u32 CALLTYPE			vvm1_SEChain_countValids					(SStartEnd* ptrSE);
	u32 CALLTYPE			vvm1_SEChain_delete							(SStartEnd* ptrSE, u64 tnCallback, u64 tnParam, bool tlDeletePointers);
	void CALLTYPE			vvm1_SEChain_deleteAsPtrBlock				(SStartEnd* ptrSE);
	void CALLTYPE			vvm1_SEChain_deleteFrom						(SStartEnd* ptrSE, void* ptrDel, bool tlDeletePointers);
	bool CALLTYPE			vvm1_SEChain_deleteFromAfterCallback		(SStartEnd* ptrSE, bool tlDeletePointers, SStartEndCallback* cb);

	bool CALLTYPE			vvm1_SEChain_allocateAdditionalMasterSlots	(SStartEnd* ptrSE, u32 tnBlockSize);
	void* CALLTYPE			vvm1_SEChain_searchByUniqueId				(SStartEnd* ptrSE, u64 tnUniqueId);
	void* CALLTYPE			vvm1_SEChain_searchByCallback				(SStartEnd* ptrSE, SStartEndCallback* cb);
	void CALLTYPE			vvm1_SEChain_iterateThroughForCallback		(SStartEnd* ptrSE, SStartEndCallback* cb);
	void CALLTYPE			vvm1_SEChain_validate						(SStartEnd* ptrSE, SStartEndCallback* cb);

	u32 CALLTYPE			vvm1_swapEndian								(u32 tnValue);
	u32 CALLTYPE			vvm1_RGBA2BGRA								(u32 tnColor);
	void* CALLTYPE			vvm1_allocateAndNull						(u32 tnSize, bool tnInitToZeros);
	bool CALLTYPE			vvm1_isNeedleInHaystack						(csu8p tcHaystack, s32 tnHaystackLength, csu8p tcNeedle, s32 tnNeedleLength, bool tlCaseSensitive, u32* tnFoundPosition);
	bool CALLTYPE			vvm1_isNeedleInHaystack_Unicode				(w16* twHaystack, w16* twNeedle);
	u32 CALLTYPE			vvm1_countConsecutiveAsciiNumericDigits		(s8* buffer, u32 tnMaxLength);
	u32 CALLTYPE			vvm1_convertTextToU32						(s8* tcNumbers, u32 tnMaxLength);

	void CALLTYPE			vvm1_math_computeTriangle					(STriangleInOutF64* tri);
	void CALLTYPE			vvm1_math_computeSquare						(SSquareInOutF64* sq, f32 ox, f32 oy);
	void CALLTYPE			vvm1_math_computeLine						(SLineF64* line);
	void CALLTYPE			vvm1_math_squareRotateAbout					(SSquareInOutF64* sq);
	u32 CALLTYPE			vvm1_math_getGravityOfThetaAndLeft			(f64 tfTheta, bool tlLeft);
	s32 CALLTYPE			vvm1_math_getGravity07FromDecoratedGravity	(u32 tnGravityDecorated);
	f64 CALLTYPE			vvm1_math_getAreaOfSquareUsing_po_p1_p2		(s32 tnGravity07_po, s32 tnGravity07_p1, s32 tnGravity07_p2, SXYF64* po, SXYF64* p1, SXYF64* p2);
	void CALLTYPE			vvm1_math_getNextAxisInterceptXY			(SXYF64* p, f64 tfTheta);
	s32 CALLTYPE			vvm1_math_getGravityByRelativePosition		(SXYF64* p, SXYS32* po);
	s32 CALLTYPE			vvm1_math_getGravityInteger					(SXYS32* p, SXYS32* po);
	s32 CALLTYPE			vvm1_math_fineAdjustGravityByTheta			(SXYF64* po, SXYF64* p, SXYF64* pg, s32 lnGravity07p, s32 lnGravity07pg);
	f64 CALLTYPE			vvm1_math_adjustTheta						(f64 tfTheta);
	bool CALLTYPE			vvm1_math_withinDelta						(f64 tfValue1, f64 tfValue2, s32 tnDeltaDecimals);
	u64 CALLTYPE			vvm1_math_washFloans						(SCanvas* tc, SBGRA* bd, SBuilder** pointFloans, SBuilder** washFloans, SBuilder** drawFloans, bool tlIsFilledLeft);

	bool CALLTYPE			vvm1_bezier_initialize						(SBezier* bez, u32 tnCurveCount, u32 tnComputePointCount, bool tlWash);
	bool CALLTYPE			vvm1_bezier_setByValues						(SBezier* bez, SBGRA color, SXYF64* p1, SXYF64* p2, SXYF64* p3, SXYF64* p4, SXYF64* p5);

	bool CALLTYPE			vvm1_polygon_initialize						(SPolygon* poly, u32 tnLineCount, bool tlAllocatePolyLines);
	bool CALLTYPE			vvm1_polygon_setByPolyLine					(SPolygon* poly, u32 tnEntry, SPolyLine* line);
	bool CALLTYPE			vvm1_polygon_setByValues					(SPolygon* poly, u32 tnEntry, SXYF64* start, SXYF64* end, SXYF64* gravity);
	bool CALLTYPE			vvm1_polygon_reset							(SPolygon* poly, bool tlResetFloans);
	bool CALLTYPE			vvm1_polygon_freeAndRelease					(SPolygon* poly, bool tlReleaseFloans);

	u64 CALLTYPE			vvm1_screenRefresh							(SScreen* ts);
	bool CALLTYPE			vvm1_screenSetFocus							(SScreen *ts);

	SRegion* CALLTYPE		vvm1_regionDuplicate						(u64 tnAssociatedId, SRegion* templateRegion);
	u64 CALLTYPE			vvm1_regionDefaultPaint						(SRegion* tr);
	u64 CALLTYPE			vvm1_regionRefresh							(SRegion* tr, SRegion* trParent);

	u64 CALLTYPE		 	vvm1_canvasDrawFixedPointText				(SCanvas* tc, SBGRA* bd, u32 fontWidth, u32 fontHeight, s32 ulx, s32 uly,    s8*  text, u32 characterCount, SBGRA foreground, SBGRA background);
	u64 CALLTYPE		 	vvm1_canvasDrawText							(SCanvas* tc, SBGRA* bd, u64 fontHandle, s32 ulx, s32 uly, s32 lrx, s32 lry, s8*  tcText, u32 tnTextLength, SBGRA foreground, SBGRA background);
	u64 CALLTYPE		 	vvm1_canvasFrameRect						(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border);
	u64 CALLTYPE		 	vvm1_canvasFillRect							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border, SBGRA background);
	u64 CALLTYPE		 	vvm1_canvasLine								(SCanvas* tc, SBGRA* bd, SXYF32* p1, SXYF32* p2, f32 lineThickness, SBGRA color, bool tlFloan);
	u64 CALLTYPE		 	vvm1_canvasArc								(SCanvas* tc, SBGRA* bd, s32 ox, s32 oy, f32 radius, f32 start, f32 end, s32 lineThickness, SBGRA line);
	u64 CALLTYPE			vvm1_canvasBezier							(SCanvas* tc, SBGRA* bd, SBezier* bez);
	SCanvas* CALLTYPE	 	vvm1_canvasExtract							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry);
	u64 CALLTYPE		 	vvm1_canvasColorize							(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, SBGRA color);
	u64 CALLTYPE		 	vvm1_canvasGrayscale						(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry);
	u64 CALLTYPE		 	vvm1_canvasGradient							(SCanvas* tc, SBGRA* bd, SBGRA ul, SBGRA ur, SBGRA lr, SBGRA ll);
	u64 CALLTYPE		 	vvm1_canvasBitBlt							(SCanvas* tsDst, bool tlDstAccumulator, s32 dulx, s32 duly, SCanvas* tsSrc, bool tlSrcAccumulator, s32 sulx, s32 suly, s32 slrx, s32 slry);
	u64 CALLTYPE			vvm1_canvasScale							(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap** tsScaleMap);
	u64 CALLTYPE			vvm1_canvasRotate							(SCanvas* tsDst, SBGRA* bdd, s32 ulx, s32 uly, SCanvas* tsSrc, SBGRA* bds, f32 tfRadians);
	u64 CALLTYPE			vvm1_canvasRotateAbout						(SCanvas* tsDst, SBGRA* bdd, s32 ulx, s32 uly, SCanvas* tsSrc, SBGRA* bds, f32 tfRadians, f32 ox, f32 oy);
	u64 CALLTYPE			vvm1_canvasPolygon							(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color);

	SCask* CALLTYPE			vvm1_caskDefineStandard						(u32 tnHeight, u32 tnWidth, u32 tnLeftStyle, u32 tnLeftState, u32 tnLeftPipCount, u32 tnLeftColor, csu8p tcLeftText, u32 tnRightStyle, u32 tnRightState, u32 tnRightPipCount, u32 tnRightColor, csu8p tcRightText);
	SCask* CALLTYPE			vvm1_caskDefineEncompassingRectangle		(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SRectXYXY* tsOuter);
	SCask* CALLTYPE			vvm1_caskDefineUpRectangle					(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter);
	SCask* CALLTYPE			vvm1_caskDefineDownRectangle				(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter);
	SCaskPip* CALLTYPE		vvm1_caskSetPipByValues						(SCask* cask, bool tlLeft, u32 tnPip, SBGRA tnPipColorNeutral, SBGRA tnPipColorOver, SBGRA tnPipColorClick, u64 tnEnterCallback, u64 tnLeaveCallback, u64 tnHoverCallback, u64 tnClickCallback, bool tlCreateCopy);
	SCaskPip* CALLTYPE		vvm1_caskSetPipByStruct						(SCask* cask, bool tlLeft, u32 tnPip, SCaskPip* caskPip, bool tlCreateCopy);
	SCask* CALLTYPE			vvm1_caskCreate								(SCask* cask, bool tlCreateCopy);
	SCanvas* CALLTYPE		vvm1_caskRefresh							(SCask* cask);

	u64 CALLTYPE			vvm1_iiCanvasPolygon						(SCanvas* tsDst, SBGRA* bd, SPolygon* poly, SBGRA color);
	void CALLTYPE			vvm1_iDeleteScaleCompute					(SScaleMap* tsm);
	u64 CALLTYPE			vvm1_iSkipWhitespaces						(s8* tcData, u64 tnMaxLength);
	u64 CALLTYPE			vvm1_iSkipToCarriageReturnLineFeed			(s8* tcData, u64 tnMaxLength, u64* tnCRLF_Length);
	u64 CALLTYPE			vvm1_iRegionDefaultPaintEditbox				(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionEditboxData* editbox);
	u64 CALLTYPE			vvm1_iRegionDefaultPaintButton				(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionButtonData* button);
	u64 CALLTYPE			vvm1_iRegionDefaultPaintImage				(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionImageData* image);
	u64 CALLTYPE			vvm1_iRegionDefaultPaintLabel				(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionLabelData* label);
	u64 CALLTYPE			vvm1_iRegionDefaultPaintCheckbox			(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionCheckboxData* checkbox);
	u64 CALLTYPE			vvm1_iRegionDefaultPaintRectangle			(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionRectangleData* rectangle);
	void CALLTYPE			vvm1_iRegionDoDefaultDebugTrapCallback		(SRegion* tr, u64 tnIdentifier, u64 tnExtra);
	u64 CALLTYPE			vvm1_iDrawFixedPoint						(SCanvas* tc, SBGRA* bd, u32 fontWidth, u32 fontHeight, s32 ulx, s32 uly, s8* text, u32 characterCount, SBGRA foreground, SBGRA background);
	u64 CALLTYPE			vvm1_iBitBltAll								(SCanvas* tsDst, bool tlDstIsAccumulatorBuffer, s32 tnX, s32 tnY, SCanvas* tsSrc, bool tlSrcIsAccumulatorBuffer);
	void CALLTYPE			vvm1_iiBitBltAll_Opaque						(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 tnX, s32 tnY, SBGRA* trgbaSrcRoot, SCanvas* tsSrc);
	void CALLTYPE			vvm1_iiBitBltAll_Alpha						(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 tnX, s32 tnY, SBGRA* trgbaSrcRoot, SCanvas* tsSrc);
	u64 CALLTYPE			vvm1_iBitBltSection							(SCanvas* tsDst, bool tlDstIsAccumulatorBuffer, s32 dulx, s32 duly, SCanvas* tsSrc, bool tlSrcIsAccumulatorBuffer, s32 sulx, s32 suly, s32 slrx, s32 slry);
	void CALLTYPE			vvm1_iiBitBltSection_Opaque					(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 dulx, s32 duly, SBGRA* trgbaSrcRoot, SCanvas* tsSrc, s32 sulx, s32 suly, s32 slrx, s32 slry);
	void CALLTYPE			vvm1_iiBitBltSection_Alpha					(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 dulx, s32 duly, SBGRA* trgbaSrcRoot, SCanvas* tsSrc, s32 sulx, s32 suly, s32 slrx, s32 slry);
	u32 CALLTYPE			vvm1_iiGradient								(SCanvas* tc, SBGRA* bd, SBGRA ul, SBGRA ur, SBGRA lr, SBGRA ll);
	u64 CALLTYPE			vvm1_iCanvasLine							(SCanvas* tc, SBGRA* bd, SXYF32* p1, SXYF32* p2, f32 lineThickness, SBGRA color);
	u64 CALLTYPE			vvm1_iiCanvasScale							(SCanvas* tsDst, SCanvas* tcSrc, SScaleMap** tsSm);
	u64 CALLTYPE			vvm1_iiCanvasScaleProcess					(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap*  tsSm, f64 tfVerticalScaler, f64 tfHorizontalScaler);
	void CALLTYPE			vvm1_iiGetSpannedPixelComputation			(_isSSpannedPixelProcessing* bp);
	void CALLTYPE			vvm1_iiGetSpannedPixelComputationAppend		(_isSSpannedPixelProcessing* bp, s32 tnDeltaX, s32 tnDeltaY, f64 tfAlpha);
	u32 CALLTYPE			vvm1_iGetIntegersBetween					(f64 p1, f64 p2);


//////////
//
// For internal VVM debugging
//
//////
	void CALLTYPE		 	vvm1_enableBreakpoints						(u64 id);
	void CALLTYPE		 	vvm1_disableBreakpoints						(u64 id);
