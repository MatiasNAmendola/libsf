//////////
//
// /libsf/vvm/core/vvmtests/vvmt_core/vvmt_core.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     Jun.20.2013
//////
// Change log:
//     Mar.02.2013	- Initial creation
//     Jun.20.2013	- Refactoring into a stand-alone DLL loaded at runtime only if -test is specified on the command line
//////
//
// VVM Primary Test application.
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

// Test source files
#include "vvmt_sha1_test.cpp"
#include "vvmt_bxml_test.cpp"
#include "vvmt_sll_test.cpp"
#include "vvmt_sll4_test.cpp"




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


		//////////
		// Indicate success
		//////
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
	bool CALLTYPE vvmt_executeTests(u64 lnHandleLog)
	{
		bool llResult;


// Test code
SBGRA		white				= {255,255,255,255};
SDateTime	lsdtStart, lsdtStop;
u32			lnI, lnWidth, lnHeight;
SCanvas*	lc;
SCanvas*	lcScaled;
SBuilder*	builder;
f64			lnH, lnW, lnHStep, lnWStep;
s8			buffer[256];
s8			timing[256];

oss_builderCreateAndInitialize(&builder, 2048);
oss_bitmapLoadFromDisk("c:\\temp\\test.bmp", &lc, &lnWidth, &lnHeight, white);

lnHStep = (f64)lnHeight / 5.0;
lnWStep = (f64)lnWidth / 5.0;
for (lnH = lnHeight / 5, lnW = lnWidth / 5; lnH < (f64)lnHeight * 2.0f; lnH += lnHStep, lnW += lnWStep)
{
	lcScaled = oss_createCanvas(0, (u32)lnW, (u32)lnH, white);
	for (lnI = 0; lnI < 10; lnI++)
	{
		oss_dateTimeGet(&lsdtStart);
		oss_canvasScale(lcScaled, lc, &lcScaled->firstScaleMap);
		oss_dateTimeGet(&lsdtStop);
		sprintf(timing, "\\temp\\Scale_%ux%u_Iteration_%u_Milliseconds_%f.bmp\0", (u32)lnW, (u32)lnH, lnI, (f32)((f64)(lsdtStop.tickCount - lsdtStart.tickCount) / (f64)lsdtStart.frequency));
		oss_builderAppendText(builder, timing + 6, strlen(timing) - 6 - 4);
		oss_bitmapSaveToDisk(lcScaled, lcScaled->bd, timing);
		oss_builderAppendText(builder, "\n", 1);
	}
	//oss_bitmapSaveToDisk(lcScaled, lcScaled->bd, buffer);
	//oss_deleteCanvas(lcScaled);
}
oss_sharedAsciiWriteOutFile("c:\\temp\\information.txt", builder->data, builder->populatedLength);

		//////////
		// If any test fails, early out
		//////
			llResult =	(true		& ivvmt_testSha1(lnHandleLog));
			llResult =	(llResult	& ivvmt_testSll(lnHandleLog));
			llResult =	(llResult	& ivvmt_testSll4(lnHandleLog));
			llResult =	(llResult	& ivvmt_testBxml(lnHandleLog));


		//////////
		// Indicate total success or not
		//////
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
