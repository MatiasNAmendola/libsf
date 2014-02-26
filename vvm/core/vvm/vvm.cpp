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
#include "\libsf\vvm\core\vvmoss\oss_class.h"
#include "\libsf\vvm\core\vvmoss\oss_structs.h"
#include "\libsf\vvm\core\vvmmc\mc_structs.h"
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
// VVM entry point
//
//////
	int APIENTRY wWinMain(	HINSTANCE	hInstance,
							HINSTANCE	hPrevInstance,
							LPWSTR		lpCmdLine,
							int			nCmdShow)
	{
		bool llRunTestCases;


		//////////
		// Bootup initialization
		//////
			iivvm_bootupInitialization();


		//////////
		// Initially pass the command line
		// Test cases can be run from the command line using:  "vvm -test"
		//////
			ivvm_parseCommandLine(lpCmdLine, &llRunTestCases);


		///////////
		// Load the required foundation components
		//////
			if (!ivvm_loadVvmResourceDll())
			{
				// Unable to load
				MessageBox(NULL, L"Missing Resource DLL (vvmenu.dll)\nTerminating with error code -1.", L"VVM Load Error", MB_OK);
				exit(-1);
			}


		//////////
		// Load OS-Specific functions
		//////
			if (!ivvm_loadAndInitializeVvmOss())
			{
				// Unable to load, or instantiate the message window for the VVM
				ivvm_resourceMessageBoxLocal(IDS_VVM_FAILURE_TO_LOAD_MINUS_1, IDS_VVM_LOAD_ERROR, false, false, false);
				exit(-1);
			}


		//////////
		// Load Machine Code-Specific functions
		//////
			if (!ivvm_loadAndInitializeVvmmc())
			{
				// Unable to load
				ivvm_resourceMessageBoxLocal(IDS_VVM_FAILURE_TO_LOAD_VVMMC_MINUS_3, IDS_VVM_LOAD_ERROR, false, false, false);
				exit(-1);
			}


//////////
//
// Once we get here, the system has been through bootstrap initialization,
// all resources are loaded, the system is in a condition where all base
// criteria for successful operations have been achieved.
//
// In short, we're in a "GO" state.
//
//////////


		//////////
		// Indicate to the VVMOSS and VVMMC that we've now loaded everything and they can proceed with the rest of their initialization requirements (if any)
		//////
			oss_initialization((u64)&vvm_debuggerInterfaceCallback);
			mc_initialization((u64)&vvm_debuggerInterfaceCallback);


		//////////
		// Initialize the VVM to its power-on state
		//////
			if (!ivvme_initialize(GetCommandLineW(), &llRunTestCases))
			{
				ivvm_resourceMessageBox(IDS_VVM_FAILURE_TO_INITIALIZE_MINUS_2, IDS_VVM_INITIALIZE_ERROR, false, false, true, false, false);
				exit(-2);
			}


		//////////
		// Test cases
		//////
			if (llRunTestCases)
				ivvm_runTestPlugins();	// They exist in vvm_tests.cpp


		//////////
		// Tell the world we're up and running, ready to do out utmost at all points. :-)
		//////
			ivvm_resourcePrintf(IDS_VVM_RUNNING);
			while (gsVvm.glVvmIsRunning)
			{
				// Will need communication with OSS for thread scheduling and execution
				Sleep(10);
			}


		//////////
		// All done!
		//////
			return(gsVvm.gnVvmReturnResult);
	}




// Include files that are not compiled separately / stand-alone
#include "vvm_eng.cpp"					// Main execution engine code
#include "vvm_tm.cpp"					// Execution engine thread mizer (thread scheduler)
#include "vvm_sup.cpp"					// Supplemental source code to vvm_eng.cpp mostly
#include "vvm_oss.cpp"					// Code related to interfacing with oss.dll
#include "vvm_mc.cpp"					// Code related to interfacing with mc.dll
#include "vvm_res.cpp"					// Load resource dll
#include "vvm_misc.cpp"					// Miscellaneous support functions
#include "vvm1.cpp"						// Version 1 VVM interface (for the debugger or other apps desiring to use the VVM)
#include "vvm_bxml.cpp"					// BXML algorithms

// For test cases only
#include "vvm_tests.cpp"				// Runs test cases on the constructed build, reports any deviations from previously established norms/requirements.

	// THe following are include files of external (non-VVM) LibSF projects
#include "\libsf\utils\sha1\sha1.cpp"	// SHA-1 hashing algorithm
