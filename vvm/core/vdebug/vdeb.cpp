//////////
//
// /libsf/vvm/vdebug/vdebug.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     September 20, 2012 - Initial creation
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



#include "windows.h"
#include "stdio.h"
#include "\libsf\vvm\core\common\common.h"
#include "\libsf\vvm\core\common\vvm_key_const.h"
#include "\libsf\vvm\core\vvm\vvm_structs.h"
#include "\libsf\vvm\core\vvmoss\vo_class.h"
#include "\libsf\vvm\core\vvmoss\vo_structs.h"
#include "vdeb_const.h"
#include "vdeb_defs.h"
#include "vdeb_glob.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_vvmoss.h"
#include "\libsf\vvm\core\common\common_vvmmc.h"
#include "vdeb_screens.h"




//////////
//
// Debugger entry point for Windows
//
//////
	BOOL APIENTRY DllMainW(	HMODULE		hModule,
							DWORD		ul_reason_for_call,
							LPVOID		lpReserved)
	{
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
			case DLL_THREAD_ATTACH:
			case DLL_THREAD_DETACH:
			case DLL_PROCESS_DETACH:
				break;
		}
		return TRUE;
	}




	// This function is called from the VVM after loading this DLL to give this debugger
	// the address to call for debugger API requests
	u64 CALLTYPE vvm_firstCallback(u64 tnCallbackAddress, u32 tnUniqueId)
	{
		DWORD lnThreadId;


		//////////
		// Load all VVM, VVMOSS and VVMMC functions from the VVM
		//////
			iLoadVvmFunctionsFromVVM((void**)tnCallbackAddress);
			iLoadVvmOssFunctionsFromVVM((void**)tnCallbackAddress);
			iLoadVvmmcFunctionsFromVVM((void**)tnCallbackAddress);


		//////////
		// Load the resource, which contains text and graphics
		//////
			iLoadResource(vvm_getLanguage(NULL));


		//////////
		// Spawn the initial thread which will create and run the debugger instance
		//////
			CreateThread(0, 0, &iDebuggerMain, (void*)tnUniqueId, 0, &lnThreadId);


		// Indicate success
		return(gVvmFunctionCount);
	}




//////////
//
// Loads the indicated resource language for the debugger
//
//////
	bool iLoadResource(s8* tcLanguage)
	{
		s8 buffer[MAX_PATH];


		// Try to load the dll
		sprintf_s(buffer, sizeof(buffer), "vdebug%s.dll\000", tcLanguage);
		ghResourceDll = LoadLibraryA(buffer);
		if (!ghResourceDll)
		{
			// There was an error loading the indicated resource dll
			// Fallback to English
			ghResourceDll = LoadLibraryA(cgcVvmmcEngDll);
			if (!ghResourceDll)
				return(false);		// If we get here, then it's bad, bad, bad news, mister!
		}
		// We're good
		return(true);
	}




//////////
//
// Main debugger entry point after instantiation and connection to vvm
//
//////
	DWORD CALLTYPE iDebuggerMain(LPVOID lpParameter)
	{
		u32		lnDebuggerUid;
		SBxml*	bxmlDebuggerSettings;


		// Grab the unique id for this instance
		lnDebuggerUid = (u32)lpParameter;

		// Build the debugger screen
// TODO:  Working on vdebug.bxml
//		bxmlDebuggerSettings = ivdeb_getDebuggerSettings();

		// Create the debugger screen
		while (1 /*Need to add a global variable for this instance of the debugger running*/)
		{
			Sleep(1);
		}
	}




// Include support files for VDebug
#include "vdeb_sup.cpp"
