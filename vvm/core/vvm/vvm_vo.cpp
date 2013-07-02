//////////
//
// /libsf/vvm/vvm/vvm_vo.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     October 03, 2012 - Initial creation
//     October 03, 2012 - PBL v1.0 license included directly in source files.
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
//
// Called to load the VVMOSS.DLL stuff, following the startup protocol.
//
//////
	bool ivvm_loadAndInitializeVvmOss(void)
	{
		// Load the DLL
		if (!iLoadVvmOssFunctionsFromDll())
			return(false);

		// Let it initialize itself
		oss_firstCallback((u64)&vvm_debuggerInterfaceCallback);
		oss_bootstrapInitialization((u64)&vvm_debuggerInterfaceCallback);

		// Create our main message window
		if (!oss_createMessageWindow())
			return(false);

		// We're good
		return(true);
	}




//////////
//
// Debugger interface to request function addresses for interface
//
// See devhelp.txt.  Duplicate changes here in VDebug.h, vvm.cpp, vvm_v1.cpp, vvm_defs.h, and vo_class.h.
//
//////
	// See what function they're requesting
	u64 CALLTYPE vvm_debuggerInterfaceCallback(s8* tcFunctionName)
	{
		u64			lnFuncAddress;
		u32			lnI, lnHaystackLength, lnNeedleLength;
		s8*			lcFuncName;
		void**		lcFuncAddress;


//////////
//
// V V M O S S   FUNCTIONS
//
//////
		// Search for the needle (tnFunctionName) in the haystack (gVvmOssFunction's lcFuncName)
		lnNeedleLength = strlen(tcFunctionName);
		for (lnI = 0; lnI < gVvmOssFunctionCount; lnI++)
		{
			// Grab the details of this entry
			lcFuncAddress	= (void**)gVvmOssFunctions[(lnI * 2) + 0];						// Grab the indirect address to store
			lcFuncName		= (s8*)   gVvmOssFunctions[(lnI * 2) + 1];						// Grab the function name to request

			lnHaystackLength = strlen(lcFuncName);
			if (lnNeedleLength == lnHaystackLength && _memicmp(tcFunctionName, lcFuncName, lnHaystackLength) == 0)
				return((u64)*lcFuncAddress);
		}
		// If we get here, not found in VVMOSS functions


//////////
//
// V V M M C   FUNCTIONS
//
//////
		// Search for the needle (tnFunctionName) in the haystack (gVvmmcFunctions's lcFuncName)
		lnNeedleLength = strlen(tcFunctionName);
		for (lnI = 0; lnI < gVvmmcFunctionCount; lnI++)
		{
			// Grab the details of this entry
			lcFuncAddress	= (void**)gVvmmcFunctions[(lnI * 2) + 0];						// Grab the indirect address to store
			lcFuncName		= (s8*)   gVvmmcFunctions[(lnI * 2) + 1];						// Grab the function name to request

			lnHaystackLength = strlen(lcFuncName);
			if (lnNeedleLength == lnHaystackLength && _memicmp(tcFunctionName, lcFuncName, lnHaystackLength) == 0)
				return((u64)*lcFuncAddress);
		}
		// If we get here, not found



//////////
//
// V V M   FUNCTIONS
//
//////
		// Search for the needle (tnFunctionName) in the haystack (gVvmmcFunctions's lcFuncName)
		lnNeedleLength = strlen(tcFunctionName);
		for (lnI = 0; lnI < gVvmFunctionCount; lnI++)
		{
			// Grab the details of this entry
			lnFuncAddress	= (u64)gVvmFunctions[(lnI * 2) + 0];							// Grab the indirect address to store
			lcFuncName		= (s8*)gVvmFunctions[(lnI * 2) + 1];							// Grab the function name to request

			lnHaystackLength = strlen(lcFuncName);
			if (lnNeedleLength == lnHaystackLength && _memicmp(tcFunctionName, lcFuncName, lnHaystackLength) == 0)
				return(lnFuncAddress);
		}
		// If we get here, not found

		// If we get here, indicate our failure
		return(NULL);
	}
