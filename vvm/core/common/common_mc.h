//////////
//
// /libsf/vvm/common/common_mc.h
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
// VVM Machine Code [Parser]
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
// Constants used by the VVMMC
//
//////
	// None currently defined




//////////
//
// The following variables and function define the interface to VVMMC.
// By including this file and calling iLoadVvmmcFunctions() from the vvm_firstCallback() callback
// in the DLL ... all things become accessible.
//
// Note:  To directly access the VVM code, use common_vvm.h.
// Note:  To directly access the OS-specific code, use common_vvmoss.h.
//
//////
	// VVMMC interface functions
	// See devhelp.txt.
	const s8		cgcMcV1FirstCallback[]							= "mc_firstCallback";
	const s8		cgcMcV1BootstrapInitialization[]				= "mc_bootstrapInitialization";
	const s8		cgcMcV1Initialization[]							= "mc_initialization";
	const s8		cgcMcV1GetVersion[]								= "mc_getVersion";
	const s8		cgcMcV1LoadVvmOssFunctions[]					= "mc_loadVvmmOssFunctions";
	const s8		cgcMcV1LoadResourceLanguage[]					= "mc_loadResourceLanguage";
	const s8		cgcMcV1LoadResourceAsciiText[]					= "mc_loadResourceAsciiText";

	const s8		cgcMcV1VerifyVariableAsciiName[]				= "mc_verifyVariableAsciiName";
	const s8		cgcMcV1VerifyAsciiFilename[]					= "mc_verifyAsciiFilename";

	const s8		cgcMcV1AssembleSourceCode[]						= "mc_assembleSourceCode";

	const s8		cgcMcV1DisassembleOpcodes[]						= "mc_disassembleOpcodes";

	const s8		cgcMcV1SaveSnippetsToBxml[]						= "mc_saveSnippetsToBxml";

	const s8		cgcMcV1EnableBreakpoints[]						= "mc_enableBreakpoints";
	const s8		cgcMcV1DisableBreakpoints[]						= "mc_disableBreakpoints";




//////////
//
// VVMMC function prototype definitions.  These must match the mc_defs.h, as well as the
// implementation in their associated mc_*.cpp files.
//
// See devhelp.txt.
//
//////
	// Callbacks specific to version 1 (the VVM could be much newer than this debugger, but we require version 1)
	u64				(CALLTYPE *mc_firstCallback)						(u64 tnDebuggerInterfaceAddress);
	void			(CALLTYPE *mc_bootstrapInitialization)				(u64 tnDebuggerInterfaceAddress);
	void			(CALLTYPE *mc_initialization)						(u64 tnDebuggerInterfaceAddress);
	const s8*		(CALLTYPE *mc_getVersion)							(void);
	bool			(CALLTYPE *mc_loadVvmmOssFunctions)					(void);
	bool			(CALLTYPE *mc_loadResourceLanguage)					(s8* tcResourceLanguage, u64* tnDllHandle);
	s8*				(CALLTYPE *mc_loadResourceAsciiText)				(u32 tnResourceNumber);

	bool			(CALLTYPE *mc_verifyVariableAsciiName)				(SOssComp* compName,		u64* tnCompOffsetOfError);
	bool			(CALLTYPE *mc_verifyAsciiFilename)					(SOssComp* compFilename,	u64* tnCompOffsetOfError);

	u32				(CALLTYPE *mc_assembleSourceCode)					(s8* tcVasmPathname, s8* tcData, u32 tnFileSize, SProgram* tsProgram);

	u32				(CALLTYPE *mc_disassembleOpcodes)					(s8* vvmMachineCode, u32 tnVvmMachineCodeLength);

	u32				(CALLTYPE *mc_saveSnippetsToBxml)					(s8* tcBxmlPathname, SStartEnd* tseSnips, bool tlOverwrite);

	void			(CALLTYPE *mc_enableBreakpoints)					(void);
	void			(CALLTYPE *mc_disableBreakpoints)					(void);




//////////
//
// List of functions and their corresponding names.  Used in iLoadVvmmcFunctions().
// NOTE:  The items in this list must appear in the same order as their definitions above
//
//////
	void* gMcFunctions[] =
	{
		(void *)&mc_firstCallback,								(void *)cgcMcV1FirstCallback,
		(void *)&mc_bootstrapInitialization,					(void *)cgcMcV1BootstrapInitialization,
		(void *)&mc_initialization,								(void *)cgcMcV1Initialization,
		(void *)&mc_getVersion,									(void *)cgcMcV1GetVersion,
		(void *)&mc_loadVvmmOssFunctions,						(void *)cgcMcV1LoadVvmOssFunctions,
		(void *)&mc_loadResourceLanguage,						(void *)cgcMcV1LoadResourceLanguage,
		(void *)&mc_loadResourceAsciiText,						(void *)cgcMcV1LoadResourceAsciiText,

		(void *)&mc_verifyVariableAsciiName,					(void *)cgcMcV1VerifyVariableAsciiName,
		(void *)&mc_verifyAsciiFilename,						(void *)cgcMcV1VerifyAsciiFilename,

		(void *)&mc_assembleSourceCode,							(void *)cgcMcV1AssembleSourceCode,

		(void *)&mc_disassembleOpcodes,							(void *)cgcMcV1DisassembleOpcodes,

		(void *)&mc_saveSnippetsToBxml,							(void *)cgcMcV1SaveSnippetsToBxml,

		(void *)&mc_enableBreakpoints,							(void *)cgcMcV1EnableBreakpoints,
		(void *)&mc_disableBreakpoints,							(void *)cgcMcV1DisableBreakpoints
	};
	u32 gMcFunctionCount = sizeof(gMcFunctions) / (2 * sizeof(void*));




//////////
//
// Called once to load all the gVvmmcFunctions[] at startup.
//
//////
	void** iLoadVvmmcFunctionsFromVVM(void** tnFuncAddress)
	{
		u32			lnI;
		s8*			lcFuncName;
		void*		lnAddress;
		void**		lnFuncAddress;
		s8			buffer[1024];


		// Grab the address of the VVM interface for function address requests
		lnFuncAddress	= (void**)&vvm_debuggerInterface;
		*lnFuncAddress	= (void*)tnFuncAddress;

		
		// Now, repeatedly call back that address with the request to all of the function addresses
		for (lnI = 0; lnI < gMcFunctionCount; lnI++)
		{
			// Grab the details of this entry
			tnFuncAddress	= (void**)gMcFunctions[(lnI * 2) + 0];			// Grab the indirect address to store
			lcFuncName		= (s8*)   gMcFunctions[(lnI * 2) + 1];			// Grab the function name to request

			// Ask the VVM for this specific function location
			lnAddress = (void*)vvm_debuggerInterface(lcFuncName);				// We only call the indicated callback to obtain our portal for v1 functions

			// Process the result
			if (!lnAddress)
			{
				// The specified functionality is not available
				// Note:  By design, this should never happen.  It is the result of a programming error.
				sprintf_s(buffer, sizeof(buffer), "Error accessing: %s\000", lcFuncName);
				MessageBoxA(NULL, buffer, "VVMMC (Machine Code) Initialization Error", MB_OK);
				// We need all the functions we request, not just some of them
				return((void**)-1);		// Indicate a fatal error
			}
			// If we get here, this function was found and we can store it
			*tnFuncAddress = lnAddress;
		}
		// When we get here, we've made the full connection to the VVM
		return(tnFuncAddress);
	}




//////////
//
// Attempt to load mc.dll and access all required functions
//
//////
	HINSTANCE McDllInstance;
	bool iLoadVvmmcFunctionsFromDll()
	{
		u32			lnI;
		s8*			lcFuncName;
		void**		lcFuncAddress;
		void*		lcAddress;
		s8			buffer[1024];


		// Try to load the dll
		if (!McDllInstance)
		{
			McDllInstance = LoadLibraryA("mc.dll");
			if (!McDllInstance)
			{
				return(false);		// There was an error loading the dll
			}
		}

		// If we get here, we have a candidate.
		// But, to be valid it has to have the required functions

		// Now, repeatedly call back that address with the request to all of the function addresses
		for (lnI = 0; lnI < gMcFunctionCount; lnI++)
		{
			// Grab the details of this entry
			lcFuncAddress	= (void**)gMcFunctions[(lnI * 2) + 0];		// Grab the indirect address to store
			lcFuncName		= (s8*)   gMcFunctions[(lnI * 2) + 1];		// Grab the function name to request

			// Ask the VVM for this specific function location
			lcAddress = GetProcAddress(McDllInstance, lcFuncName);

			// Process the result
			if (!lcAddress)
			{
				// The specified functionality is not available
				// Note:  By design, this should never happen.  It is the result of a programming error.
				sprintf_s(buffer, sizeof(buffer), "Error accessing: %s\000", lcFuncName);
				MessageBoxA(NULL, buffer, "MC (Machine Code) Initialization Error", MB_OK);
				// The specified functionality is not available
				return(false);
			}
			// If we get here, this function was found and we can store it
			*lcFuncAddress = lcAddress;
		}
		// When we get here, we've made the full connection to the mc.dll functions
		return(true);
	}
