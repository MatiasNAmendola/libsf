//////////
//
// /libsf/vvm/vvm/vvm.cpp
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
//     Nov.07.2012 - 0.60 development begins
//     Sep.29.2012 - PBL v1.0 license included directly in source files.
//     Sep.17.2012 - Initial creation
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




#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#define _VVM_COMPILING

#include "\libsf\vvm\core\common\common.h"
#include "\libsf\utils\sha1\sha1.h"											// SHA-1 hashing algorithm
#include "\libsf\vvm\core\localization\vvmenu\resource.h"					// Resource constants
#include "vvm_const.h"
#include "\libsf\vvm\core\oss\oss_class.h"
#include "\libsf\vvm\core\oss\oss_structs.h"
#include "\libsf\vvm\core\mc\mc_structs.h"
#include "\libsf\vvm\core\common\fonts\font8x6.h"
#include "\libsf\vvm\core\common\fonts\font8x8.h"
#include "\libsf\vvm\core\common\fonts\font8x14.h"
#include "\libsf\vvm\core\common\fonts\font8x16.h"
#include "vvm_structs.h"
#include "vvm_istructs.h"
#include "vvm_defs.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_oss.h"
#include "\libsf\vvm\core\common\common_mc.h"
#include "vvm_glob.h"
#include "vvm_bxml.h"




//////////
//
// The first callback
//
//////
	u64 CALLTYPE vvm_firstCallback(u32 tnDoNotLoadOptions)
	{
		//////////
		// Load the base VVM functions
		//////
			iLoadOssFunctionsFromDll();
			iLoadMcFunctionsFromDll();


		//////////
		// Let it OSS and MC initialize themselves
		//////
			if ((tnDoNotLoadOptions & _DO_NOT_LOAD_OSS) != _DO_NOT_LOAD_OSS)
			{
				oss_firstCallback(tnDoNotLoadOptions | _DO_NOT_LOAD_VVM);
				oss_bootstrapInitialization();
			}
			if ((tnDoNotLoadOptions & _DO_NOT_LOAD_MC) != _DO_NOT_LOAD_MC)
			{
				mc_firstCallback(tnDoNotLoadOptions | _DO_NOT_LOAD_VVM);
				mc_bootstrapInitialization();
			}


		//////////
		// Initialize our unique number critical section access
		//////
			InitializeCriticalSection(&gcsUniqueIdAccess);


		//////////
		// Indicate success
		//////
			return(1);
	}




//////////
//
// 
//////
	void CALLTYPE vvm_bootstrapInitialization(void)
	{
		// Nothing currently defined
	}




//////////
//
// Parse the command line for known options
//
//////
	s64 CALLTYPE vvm_startTheVvm(w16* tuCmdLine, bool* tlTestCasesOnly)
	{
		u32		lnI, lnLength, lnSkip;
		bool	llRunTestCases;


		// Find out how long the line is
		lnLength = wcslen(tuCmdLine);

		// Initially lower the test-case setting
		llRunTestCases = false;
		if (tlTestCasesOnly)
			*tlTestCasesOnly = false;

		// Iterate looking for known switches
		for (lnI = 0; lnI < lnLength; lnI++)
		{
//////////
// -r:ES, -r:ENU
//////
			if (lnLength - lnI >= 3 && ivvm_unicodeMemicmp(tuCmdLine + lnI, L"-r:", 3) == 0)
			{
				// Find out how long this string portion is
				lnSkip					= ivvm_scanStringAndNullTerminateAtNextWhitespaceW(tuCmdLine + lnI + 3) + 3;
				gsVvm.gcVvmResourceLang	= vvm_unicodeToAscii(tuCmdLine + lnI + 3, wcslen(tuCmdLine + lnI + 3));

				// Blank out that portion of the command line
				vvm_unicodeMemset(tuCmdLine + lnI, (w16)' ', lnSkip);

				// Move past ti
				lnI += lnSkip;


//////////
// -test
//////
// TODO:  a future syntax will allow for -test:file.bxml to run the tests identified within an executable file.
			} else if (lnLength - lnI >= 5 && ivvm_unicodeMemicmp(tuCmdLine + lnI, L"-test", 5) == 0) {
				// Yes
				*tlTestCasesOnly = true;

			}


//////////
// New commands can be added here:
//////
		}




//////////
//
// Bootup initialization can now proceed.
// This follow processing of the command line above.
//
//////////


		///////////
		// Load the required foundation components
		//////
			if (!ivvm_loadVvmResourceDll())
				return(-1);


		//////////
		// Load OS-Specific functions following
		//////
			if (!ivvm_loadAndInitializeOss())
				return(-2);


		//////////
		// Load Machine Code-Specific functions
		//////
			if (!ivvm_loadAndInitializeMc())
			{
				// Unable to load
				ivvm_resourceMessageBoxLocal(IDS_VVM_FAILURE_TO_LOAD_VVMMC_MINUS_3, IDS_VVM_LOAD_ERROR, false, false, false);
				exit(-3);
			}


		//////////
		// Bootup initialization
		//////
			iivvm_bootupInitialization();


//////////
//
// Once we get here, the system has been through bootstrap initialization,
// all resources are loaded, the system is in a condition where all base
// criteria for successful operations have been achieved.
//
// In short, we're in a "FULL GO" state.
//
//////////


		//////////
		// Tell the OSS and MC that we've now loaded everything and they can proceed with
		// the rest of their initialization requirements (if any)
		//////
			oss_initialization();
			mc_initialization();


		//////////
		// Initialize the VVM engine to its default power-on state
		//////
			if (!ivvme_initialize(tuCmdLine, &llRunTestCases))
				return(-4);


		//////////
		// If we are instructed to run test cases, then run them.
		//////
			if (llRunTestCases)
				ivvm_runTestPlugins();	// See vvm_tests.cpp


		//////////
		// All done!
		// Indicate success.
		//////
			return(0);
	}




// Include files that are not compiled separately / stand-alone
#include "vvm_eng.cpp"					// Main execution engine code
#include "vvm_tm.cpp"					// Execution engine thread mizer (thread scheduler)
#include "vvm_sup.cpp"					// Supplemental source code to vvm_eng.cpp mostly
#include "vvm_res.cpp"					// Load resource dll
#include "vvm_misc.cpp"					// Miscellaneous support functions
#include "vvm1.cpp"						// Version 1 VVM interface (for the debugger or other apps desiring to use the VVM)
#include "vvm_bxml.cpp"					// BXML algorithms

// For test cases only
#include "vvm_tests.cpp"				// Runs test cases on the constructed build, reports any deviations from previously established norms/requirements.

	// THe following are include files of external (non-VVM) LibSF projects
#include "\libsf\utils\sha1\sha1.cpp"	// SHA-1 hashing algorithm
