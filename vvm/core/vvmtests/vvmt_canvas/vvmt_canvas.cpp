//////////
//
// /libsf/vvm/vvmtests/vvmtests.cpp
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
//     Jun.20.2013	- Refactoring into a stand-alone DLL loaded at runtime only if -test is specified on the command line
//     Mar.02.2013	- Initial creation
//////
//
// Main test application.
// Tests the SHA-1 and BXML functionality, upon which the remaining tests all depend upon.
//
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




#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <share.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <sys\locking.h>
#include <errno.h>
#include <windows.h>
#include <math.h>
#include "\libsf\vvm\core\common\common.h"
#include "\libsf\vvm\core\localization\vvmenu\resource.h"					// Resource constants
#include "vvmt_const.h"
#include "\libsf\vvm\core\vvm\vvm_structs.h"
#include "\libsf\vvm\core\vvmoss\vo_structs.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_vvmoss.h"
#include "vvmt_structs.h"
#include "vvmt_defs.h"
#include "vvmt_glob.h"
#include "\libsf\vvm\core\vvmoss\vo_class.h"
#include "\libsf\vvm\core\common\vvm_key_const.h"

// The following are include files of external (non-VVM) LibSF projects
#include "\libsf\utils\sha1\sha1.h"		// SHA-1 hashing algorithm

// Test source file
#include "vvmt_canvas_test.cpp"




//////////
//
// Main entry point for the VVM's Operating System Specific code
//
//////
	BOOL APIENTRY DllMain(	HMODULE	hModule,
							DWORD	ul_reason_for_call,
							LPVOID	lpReserved )
	{
		ghInstance = hModule;
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
			case DLL_PROCESS_DETACH:
			case DLL_THREAD_ATTACH:
			case DLL_THREAD_DETACH:
				break;
		}
		return TRUE;
	}




//////////
//
// This function is called ONLY from the VVM after loading this DLL.
// If this DLL is loaded from another source (not the VVM), it is not
// to call this function.  The VVM calls to give it the address to call
// for debugger API requests, as well as those of the already loaded VVMOSS.
//
//////
	u64 CALLTYPE vvmt_firstCallback(u64 tnCallbackAddress)
	{
		//////////
		// Load all VVM and VVMOSS functions
		//////
			iLoadVvmFunctionsFromVVM((void**)tnCallbackAddress);
			iLoadVvmOssFunctionsFromVVM((void**)tnCallbackAddress);


		// Indicate success
		return(0);
	}




//////////
//
// Called to handle any bootstrap initialization, things where only primitive services of the
// VVM and VVMOSS are available, and not completely at that.
//
//////
	void CALLTYPE vvmt_bootstrapInitialization(u64 tnDebuggerInterfaceAddress)
	{
		// Nothing is currently defined for bootstrap initialization
	}





//////////
//
// Called to handle any initialization after the system has been through bootstrapping, and
// all initial conditions are met, able to service requests.
//
//////
	void CALLTYPE vvmt_initialization(u64 tnDebuggerInterfaceAddress)
	{
		// Nothing is currently defined for initialization
	}




//////////
//
// Called to indicate the VVMTESTS.DLL version
//
//////
	const s8* CALLTYPE vvmt_getVersion(void)
	{
		return(cgcVvmtVersion);
	}




//////////
//
// Called to execute the tests, returns true or false if the tests passed.
// Uses the vvm_resourcePrintf() function to direct output made during the tests.
//
//////
	bool CALLTYPE vvmt_executeTests(u64 lnHandle)
	{
		bool llResult;


		//////////
		// Initially default to success
		//////
			llResult = true;


		//////////
		// If any test fails, early out
		//////
						llResult = ivvmt_testCanvas(lnHandle);
//		if (llResult)	llResult = ivvmt_test???();


		// Indicate total success or not
		return(llResult);
	}




//////////
//
// For debugging, turns on/off the internal breakpoint flag.
//
//////
	void CALLTYPE vvmt_enableBreakpoints(void)
	{
	}

	void CALLTYPE vvmt_disableBreakpoints(void)
	{
	}
