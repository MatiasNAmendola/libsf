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

#include "\libsf\vvm\core\common\common.h"
#include "\libsf\utils\sha1\sha1.h"											// SHA-1 hashing algorithm
#include "\libsf\vvm\core\localization\vvmenu\resource.h"					// Resource constants
#include "vgo_const.h"
#include "\libsf\vvm\core\oss\oss_class.h"
#include "\libsf\vvm\core\oss\oss_structs.h"
#include "\libsf\vvm\core\mc\mc_structs.h"
#include "\libsf\vvm\core\common\fonts\font8x6.h"
#include "\libsf\vvm\core\common\fonts\font8x8.h"
#include "\libsf\vvm\core\common\fonts\font8x14.h"
#include "\libsf\vvm\core\common\fonts\font8x16.h"
#include "vgo_structs.h"
#include "vgo_defs.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_oss.h"
#include "\libsf\vvm\core\common\common_mc.h"
#include "vgo_glob.h"




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
		// Load VVM functions
		//////
			if (!iLoadVvmFunctionsFromDll())
			{
				// Unable to load, or instantiate the message window for the VVM
//				ivgo_resourceMessageBoxLocal(IDS_VVM_FAILURE_TO_LOAD_MINUS_1, IDS_VVM_LOAD_ERROR, false, false, false);
				exit(-1);
			}


		//////////
		// Load OS-Specific functions
		//////
			if (!iLoadOssFunctionsFromDll())
			{
				// Unable to load, or instantiate the message window for the VVM
//				ivgo_resourceMessageBoxLocal(IDS_VVM_FAILURE_TO_LOAD_MINUS_1, IDS_VVM_LOAD_ERROR, false, false, false);
				exit(-1);
			}


		//////////
		// Load Machine Code-Specific functions
		//////
			if (!iLoadMcFunctionsFromDll())
			{
				// Unable to load
//				ivgo_resourceMessageBoxLocal(IDS_VVM_FAILURE_TO_LOAD_VVMMC_MINUS_3, IDS_VVM_LOAD_ERROR, false, false, false);
				exit(-1);
			}


		//////////
		// Initially pass the command line
		// Test cases can be run from the command line using:  "vvm -test"
		//////
			vvm_parseCommandLine(lpCmdLine, &llRunTestCases);


		//////////
		// Control will never get here:
		//////
			return(0);
	}
