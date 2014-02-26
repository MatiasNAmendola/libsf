//////////
//
// /libsf/vvm/vvmmc/mc_asm.cpp
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
// VVM Assembler Logic
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
// Takes a VASM-compatible source file, and creates an executable program to be run on the VVM.
//
// Returns:
//		Number of bytes generated in machine code
//		Note:  If 0, did not do any valid processing, however the tseProg structure may still have
//		       been updated.
//
//////
	u32 CALLTYPE mc_assembleSourceCode(s8* tcVasmPathname, s8* tcData, u32 tnFileSize, SProgram* tsProgram)
	{
		u32				lnBytes;
		SAssembly*		la;
		SSourceFile*	lsf;


		// Allocate our assembly data
		la = (SAssembly*)vvm_SEChain_append(&tsProgram->_assembly, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SAssembly), _COMMON_START_END_BLOCK_SIZE, NULL);
		if (!la)	return(0);		// This is bad.  Very bad.  Should never happen.
		la->prog	= tsProgram;


		// Make sure our environment is sane
		lnBytes = 0;
		while (1)
		{
			if (!tcData || tnFileSize == 0)
				break;		//  Nothing to do


			//////////
			// Load the raw data, parse out into lines, load any include files
			//////
				lsf = imc_loadSourceFile(tcVasmPathname, tcData, tnFileSize, la, sizeof(_isSLineInfo), false);
				if (lsf->errors.masterCount != 0)
					break;		// Errors at this stage, we're done


			//////////
			// Begin parsing the source code, breaking out all lines to independent quantities that are recognized in later pass parsing
			//////
// For debugging:
//oss_writeSOssLineSequenceCompsDebuggingToDisk("\\libsf\\vvm\\vasm\\test\\testoutcomps.txt", &lsf->lines);
				imc_assemblyPass0(la, lsf);
// For debugging:
//oss_writeSOssLineSequenceCompsDebuggingToDisk("\\libsf\\vvm\\vasm\\test\\testoutcomps2.txt", &lsf->lines);
				if (lsf->errors.masterCount != 0)
					break;		// Errors at this stage, we're done


			//////////
			// Replace any tilde quantities, which are "macro substitutions" (for lack of a better term)
			//////
				imc_assemblyPass1(la, lsf);
// For debugging:
//oss_writeSOssLineSequenceCompsDebuggingToDisk("\\libsf\\vvm\\vasm\\test\\testoutcomps3.txt", &lsf->lines);
				if (lsf->errors.masterCount != 0)
					break;		// Errors at this stage, we're done


			//////////
			// Look for anything that's not currently known (meaning the first comp is one of alpha/alphanumeric/numeric/unknown)
			//////
// TODO:  continuing here
				imc_assemblyPass2(la, lsf);
// For debugging:
//oss_writeSOssLineSequenceCompsDebuggingToDisk("\\libsf\\vvm\\vasm\\test\\testoutcomps3.txt", &lsf->lines);
				if (lsf->errors.masterCount != 0)
					break;		// Errors at this stage, we're done


			// Unconditional break to return to caller
			break;
		}
		// Indicate the number of machine code bytes generated
		return(lnBytes);
	}
