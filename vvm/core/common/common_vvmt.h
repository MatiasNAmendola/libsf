//////////
//
// /libsf/vvm/common/common_vvmt.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//	   Mar.02.2013
//////
// Change log:
//	   Mar.02.2013	- Initial creation
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
//	   http://www.libsf.org/
//	   http://www.libsf.org/licenses/
//	   http://www.visual-freepro.org
//	   http://www.visual-freepro.org/blog/
//	   http://www.visual-freepro.org/forum/
//	   http://www.visual-freepro.org/wiki/
//	   http://www.visual-freepro.org/wiki/index.php/PBL
//	   http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.	In Jesus' name I pray.  Amen.
//
//




//////////
//
// The following variables and function define the interface to VVMOSS.
// By including this file and calling iLoadVvmOssFunctions() from the vvm_firstCallback() callback
// in the DLL ... all things become accessible.
//
// Note:  To directly access the VVM-specific code, use common_vvmoss.h.
//
//////
	const s8		cgcVvmtFirstCallback[]									= "vvmt_firstCallback";
	const s8		cgcVvmtBootstrapInitialization[]						= "vvmt_bootstrapInitialization";
	const s8		cgcVvmtInitialization[]									= "vvmt_initialization";
	const s8		cgcVvmtGetVersion[]										= "vvmt_getVersion";
	const s8		cgcVvmtExecuteTests[]									= "vvmt_executeTests";

	const s8		cgcVvmtEnableBreakpoints[]								= "vvmt_enableBreakpoints";
	const s8		cgcVvmtDisableBreakpoints[]								= "vvmt_disableBreakpoints";




// TODO:  There needs to be some refactoring on the order / grouping of related functions below
// NOTE:  This todo is being duplicated in vo_defs.h


//////////
//
// VVMOSS function prototype definitions.  These must match the vo_defs.h, as well as the
// implementation in their associated vo_*.cpp files.
//
// See devhelp.txt.
//
//////
	u64				(CALLTYPE *vvmt_firstCallback)							(u64 tnDebuggerInterfaceAddress);
	void			(CALLTYPE *vvmt_bootstrapInitialization)				(u64 tnDebuggerInterfaceAddress);
	void			(CALLTYPE *vvmt_initialization)							(u64 tnDebuggerInterfaceAddress);
	const s8*		(CALLTYPE *vvmt_getVersion)								(void);
	bool			(CALLTYPE *vvmt_executeTests)							(void);


//////////
//
// Debugging
// Used internally to trap for debugging breakpoints.  Allows conditional execution of something
// until a condition arises, and only then will the debugger be trapped if internal breakpoints
// have been enabled by an explicit call to oss_enableBreakpoints().
//
//////////
		void			(CALLTYPE *vvmt_enableBreakpoints)					(void);
		void			(CALLTYPE *vvmt_disableBreakpoints)					(void);


//////////
//
// List of functions and their corresponding names.	 Used in iLoadVvmOssFunctions().
// NOTE:  The items in this list must appear in the same order as their definitions above
//
//////
	void* gVvmtFunctions[] =
	{
		(void *)&vvmt_firstCallback,										(void *)cgcVvmtFirstCallback,
		(void *)&vvmt_bootstrapInitialization,								(void *)cgcVvmtBootstrapInitialization,
		(void *)&vvmt_initialization,										(void *)cgcVvmtInitialization,
		(void *)&vvmt_getVersion,											(void *)cgcVvmtGetVersion,
		(void *)&vvmt_executeTests,											(void *)cgcVvmtExecuteTests,

		(void *)&vvmt_enableBreakpoints,									(void *)cgcVvmtEnableBreakpoints,
		(void *)&vvmt_disableBreakpoints,									(void *)cgcVvmtDisableBreakpoints
	};
	u32 gVvmtFunctionCount = sizeof(gVvmtFunctions) / (2 * sizeof(void*));




//////////
//
// Attempt to load vvmoss.dll and access all required functions
//
//////
	HINSTANCE vvmtDllInstance = NULL;
	bool iLoadVvmtFunctionsFromDll(void)
	{
		u32			lnI;
		s8*			lcFuncName;
		void**		lcFuncAddress;
		void*		lcAddress;
		s8			buffer[1024];


		// Try to load the dll
		if (!vvmtDllInstance)
		{
			vvmtDllInstance = LoadLibraryA("vvmtests.dll");
			if (!vvmtDllInstance)
			{
				// There was an error loading the dll
				return(false);
			}
		}
		// If we get here, we have a candidate.
		// But, to be valid it has to have the required functions

		// Now, repeatedly call back that address with the request to all of the function addresses
		for (lnI = 0; lnI < gVvmtFunctionCount; lnI++)
		{
			// Grab the details of this entry
			lcFuncAddress	= (void**)gVvmtFunctions[(lnI * 2) + 0];		// Grab the indirect address to store
			lcFuncName		= (s8*)   gVvmtFunctions[(lnI * 2) + 1];		// Grab the function name to request

			// Ask the VVM for this specific function location
			lcAddress = GetProcAddress(vvmtDllInstance, lcFuncName);

			// Process the result
			if (!lcAddress)
			{
				// The specified functionality is not available
				// Note:  By design, this should never happen.  It is the result of a programming error.
				sprintf_s(buffer, sizeof(buffer), "Error accessing: %s\000", lcFuncName);
				MessageBoxA(NULL, buffer, "VVMTESTS Initialization Error", MB_OK);
				// The specified functionality is not available
				return(false);
			}
			// If we get here, this function was found and we can store it
			*lcFuncAddress = lcAddress;
		}
		// When we get here, we've made the full connection to the vvmoss.dll functions
		return(true);
	}
