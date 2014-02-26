//////////
//
// /libsf/VDebug/VDebug/mc_defs.h
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
//     Nov.12.2012 - Initial creation
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
		u64 CALLTYPE			mc_firstCallback										(u64 tnDebuggerInterfaceAddress);
		void CALLTYPE			mc_bootstrapInitialization								(u64 tnDebuggerInterfaceAddress);
		void CALLTYPE			mc_initialization										(u64 tnDebuggerInterfaceAddress);
		const s8* CALLTYPE		mc_getVersion											(void);
		bool CALLTYPE			mc_loadVvmmOssFunctions									(void);
		bool CALLTYPE			mc_loadResourceLanguage									(s8* tcResourceLanguage, u64* tnDllHandle);
		s8* CALLTYPE			mc_loadResourceAsciiText								(u32 tnResourceNumber);
		// Validation functions
		bool CALLTYPE			mc_verifyVariableAsciiName								(SOssComp* compName,		u64* tnCompOffsetOfError);
		bool CALLTYPE			mc_verifyAsciiFilename									(SOssComp* compFilename,	u64* tnCompOffsetOfError);


		// mc_asm.cpp
		u32 CALLTYPE			mc_assembleSourceCode									(s8* tcVasmPathname, s8* tcData, u32 tnFileSize, SProgram* tsProgram);
		// mc_save.cpp
		u32 CALLTYPE			mc_saveSnippetsToBxml									(s8* tcBxmlPathname, SStartEnd* tseSnips, bool tlOverwrite);
		// mc_disasm.cpp
		u32 CALLTYPE			mc_disassembleOpcodes									(s8* vvmMachineCode, u32 tnVvmMachineCodeLength);


	//////////
	// mc_sup.cpp
	//////
		bool				iLoadResource												(s8* tcLanguage);
		bool				iimc_loadResourceAsciiTextCallback							(SStartEndCallback* cb);
		// Warning and error functions
		void				imc_appendError												(SStartEnd* tseErrors,		SOssLine* line, SOssComp* comp, u32 tnResource);
		void				imc_appendWarning											(SStartEnd* tseWarnings,	SOssLine* line, SOssComp* comp, u32 tnResource);
		// Variable functions
		void				imc_appendVariable											(SStartEnd* tseVariable, SOssComp* compName, SOssComp* compData, s64 tnLength);
		// Helper functions
		SStartEnd*			imc_programGetScreens										(SStartEnd* tseProg);
		SStartEnd*			imc_programGetGlobals										(SStartEnd* tseProg);
		SStartEnd*			imc_programGetSnippets										(SStartEnd* tseProg);
		SStartEnd*			imc_programGetDynSnips										(SStartEnd* tseProg);
		SStartEnd*			imc_programGetTimers										(SStartEnd* tseProg);
		SStartEnd*			imc_programGetThreads										(SStartEnd* tseProg);
		SStartEnd*			imc_programGetDefines										(SStartEnd* tseProg);
		// Search defines
		SVariable*			imc_searchVariablesByName									(SStartEnd* tseVariables, SDatum* tsDatum);
		bool				iimc_searchVariablesByNameCallback							(SStartEndCallback* cb);
		bool				iimc_validateStartEndCompsCallback							(SStartEndCallback* cb);
		// Used by mc_asm.cpp as internal functions, but exist in mc_sup.cpp
		void				imc_assemblyPass0											(SAssembly* ta, SSourceFile* tsf);
		void				imc_assemblyPass1											(SAssembly* ta, SSourceFile* tsf);
		void				imc_assemblyPass2											(SAssembly* ta, SSourceFile* tsf);
		SSourceFile*		imc_loadSourceFile											(s8* tcSourceFileName, s8* tcData, u64 tnFileSize, SAssembly* ta, u64 tnAllocSize, bool tlUseOssAlloc);
		void				imc_parseIncludeFilesAndDefines								(SAssembly* ta, SSourceFile* tsf);
		SSourceFile*		iimc_loadThisIncludeFile									(s8* tcPathname, SOssLine* line, SOssComp* compName, SAssembly* ta, SSourceFile* tsf);
		SOssLine*			iimc_assemblyPass0ScanForBlocks								(SOssLine* line, u32 tniCode, SBlock*  block, _isPass0BlockScanData* pbsd);
		SOssLine*			iimc_assemblyPass0ScanForBlocksSnipDefs						(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd);
		SOssLine*			iimc_assemblyPass0ScanForBlocksEnd							(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd);
		SOssLine*			iimc_assemblyPass0ScanForBlocksColin						(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd);
		SOssLine*			iimc_assemblyPass0ScanForBlocksDllFuncDef					(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd);
		SOssLine*			iimc_assemblyPass0ScanForBlocksPipeSign						(SOssLine* line, u32 tniCode, SBlock** block, _isPass0BlockScanData* pbsd);
		bool				iimc_assemblyPass2ParseBlockStartsAndLabels					(SAssembly* ta, SSourceFile* tsf);
		bool				iimc_assemblyPass2ParseBlockStartsAndLabelsDsnipDll			(SAssembly* ta, SSourceFile* tsf, SBlock* block);
		bool				iimc_assemblyPass2ParseBlockStartsAndLabelsDsnipBxml		(SAssembly* ta, SSourceFile* tsf, SBlock* block);
		bool				iimc_assemblyPass2ParseBlockStartsAndLabelsSnip				(SAssembly* ta, SSourceFile* tsf, SBlock* block);
