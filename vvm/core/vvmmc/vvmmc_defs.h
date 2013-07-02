//////////
//
// /libsf/VDebug/VDebug/vvmmc_defs.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 12, 2012
//////
// Change log:
//     November 12, 2012 - Initial creation
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
// Internal VVM Machine Code functions
//////
	//////////
	// vvmmc.cpp
	//////
		u64 CALLTYPE			vvmmc_firstCallback										(u64 tnDebuggerInterfaceAddress);
		void CALLTYPE			vvmmc_bootstrapInitialization							(u64 tnDebuggerInterfaceAddress);
		void CALLTYPE			vvmmc_initialization									(u64 tnDebuggerInterfaceAddress);
		const s8* CALLTYPE		vvmmc_getVersion										(void);
		bool CALLTYPE			vvmmc_loadVvmmOssFunctions								(void);
		bool CALLTYPE			vvmmc_loadResourceLanguage								(s8* tcResourceLanguage, u64* tnDllHandle);
		s8* CALLTYPE			vvmmc_loadResourceAsciiText								(u32 tnResourceNumber);
		// Validation functions
		bool CALLTYPE			vvmmc_verifyVariableAsciiName							(SOssComp* compName,		u64* tnCompOffsetOfError);
		bool CALLTYPE			vvmmc_verifyAsciiFilename								(SOssComp* compFilename,	u64* tnCompOffsetOfError);


		// vvmmc_asm.cpp
		u32 CALLTYPE			vvmmc_assembleSourceCode								(s8* tcVasmPathname, s8* tcData, u32 tnFileSize, SProgram* tsProgram);
		// vvmmc_save.cpp
		u32 CALLTYPE			vvmmc_saveSnippetsToBxml								(s8* tcBxmlPathname, SStartEnd* tseSnips, bool tlOverwrite);
		// vvmmc_disasm.cpp
		u32 CALLTYPE			vvmmc_disassembleOpcodes								(s8* vvmMachineCode, u32 tnVvmMachineCodeLength);


	//////////
	// vvmmc_sup.cpp
	//////
		bool				iLoadResource												(s8* tcLanguage);
		bool				iivvmmc_loadResourceAsciiTextCallback						(void* ptr, u64 tnExtra);
		// Warning and error functions
		void				ivvmmc_appendError											(SStartEnd* tseErrors,		SOssLine* line, SOssComp* comp, u32 tnResource);
		void				ivvmmc_appendWarning										(SStartEnd* tseWarnings,	SOssLine* line, SOssComp* comp, u32 tnResource);
		// Variable functions
		void				ivvmmc_appendVariable										(SStartEnd* tseVariable, SOssComp* compName, SOssComp* compData, s64 tnLength);
		// Helper functions
		SStartEnd*			ivvmmc_programGetScreens									(SStartEnd* tseProg);
		SStartEnd*			ivvmmc_programGetGlobals									(SStartEnd* tseProg);
		SStartEnd*			ivvmmc_programGetSnippets									(SStartEnd* tseProg);
		SStartEnd*			ivvmmc_programGetDynSnips									(SStartEnd* tseProg);
		SStartEnd*			ivvmmc_programGetTimers										(SStartEnd* tseProg);
		SStartEnd*			ivvmmc_programGetThreads									(SStartEnd* tseProg);
		SStartEnd*			ivvmmc_programGetDefines									(SStartEnd* tseProg);
		// Search defines
		SVariable*			ivvmmc_searchVariablesByName								(SStartEnd* tseVariables, SDatum* tsDatum);
		bool				iivvmmc_searchVariablesByNameCallback						(void* ptr, u64 tnExtra);
		bool				iivvmmc_validateStartEndCompsCallback						(void* ptr, u64 tnExtra);
		// Used by vvmmc_asm.cpp as internal functions, but exist in vvmmc_sup.cpp
		void				ivvmmc_assemblyPass0										(SAssembly* ta, SSourceFile* tsf);
		void				ivvmmc_assemblyPass1										(SAssembly* ta, SSourceFile* tsf);
		void				ivvmmc_assemblyPass2										(SAssembly* ta, SSourceFile* tsf);
		SSourceFile*		ivvmmc_loadSourceFile										(s8* tcSourceFileName, s8* tcData, u64 tnFileSize, SAssembly* ta, u64 tnAllocSize, bool tlUseOssAlloc);
		void				ivvmmc_parseIncludeFilesAndDefines							(SAssembly* ta, SSourceFile* tsf);
		SSourceFile*		iivvmmc_loadThisIncludeFile									(s8* tcPathname, SOssLine* line, SOssComp* compName, SAssembly* ta, SSourceFile* tsf);
		SOssLine*			iivvmmc_assemblyPass0ScanForBlocks							(SOssLine* line, u32 tniCode, SBlock*  block, _isPass0BlockScanData* pbsd);
		SOssLine*			iivvmmc_assemblyPass0ScanForBlocksSnipDefs					(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd);
		SOssLine*			iivvmmc_assemblyPass0ScanForBlocksEnd						(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd);
		SOssLine*			iivvmmc_assemblyPass0ScanForBlocksColin						(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd);
		SOssLine*			iivvmmc_assemblyPass0ScanForBlocksDllFuncDef				(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd);
		SOssLine*			iivvmmc_assemblyPass0ScanForBlocksPipeSign					(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd);
		bool				iivvmmc_assemblyPass2ParseBlockStartsAndLabels				(SAssembly* ta, SSourceFile* tsf);
		bool				iivvmmc_assemblyPass2ParseBlockStartsAndLabelsDsnipDll		(SAssembly* ta, SSourceFile* tsf, SBlock* block);
		bool				iivvmmc_assemblyPass2ParseBlockStartsAndLabelsDsnipBxml		(SAssembly* ta, SSourceFile* tsf, SBlock* block);
		bool				iivvmmc_assemblyPass2ParseBlockStartsAndLabelsSnip			(SAssembly* ta, SSourceFile* tsf, SBlock* block);
