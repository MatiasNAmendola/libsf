//////////
//
// /libsf/vvm/core/vfrp/vfrp.cpp
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//     Mar.07.2014
//////
// Change log:
//     Mar.07.2012 - Initial creation
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
#include "vfrp_const.h"
#include "\libsf\vvm\core\oss\oss_class.h"
#include "\libsf\vvm\core\oss\oss_structs.h"
#include "\libsf\vvm\core\mc\mc_structs.h"
#include "\libsf\vvm\core\common\fonts\font8x6.h"
#include "\libsf\vvm\core\common\fonts\font8x8.h"
#include "\libsf\vvm\core\common\fonts\font8x14.h"
#include "\libsf\vvm\core\common\fonts\font8x16.h"
#include "vfrp_structs.h"
#include "vfrp_defs.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_oss.h"
#include "\libsf\vvm\core\common\common_mc.h"
#include "vfrp_glob.h"




//////////
//
// Visual FreePro top level entry point
//
//////
	int APIENTRY wWinMain(	HINSTANCE	hInstance,
							HINSTANCE	hPrevInstance,
							LPWSTR		lpCmdLine,
							int			nCmdShow)
	{
		s64		lnResult;
		bool	llRunTestCases;


		//////////
		// Load VVM functions
		//////
			if (!ivfrp_loadAndInitializeVvm())
			{
				// Unable to load, or instantiate the message window for the VVM
				MessageBoxA(NULL, "Unable to load VVM.DLL", "Visual FreePro Launch Error", MB_OK);
				exit(-1);
			}


		//////////
		// Load OS-Specific functions
		//////
			if (!ivfrp_loadAndInitializeOss())
			{
				// Unable to load, or instantiate the message window for the VVM
				MessageBoxA(NULL, "Unable to load OSS.DLL", "Visual FreePro Launch Error", MB_OK);
				exit(-1);
			}


		//////////
		// Load Machine Code-Specific functions
		//////
			if (!ivfrp_loadAndInitializeMc())
			{
				// Unable to load
				MessageBoxA(NULL, "Unable to load MC.DLL", "Visual FreePro Launch Error", MB_OK);
				exit(-1);
			}


		//////////
		// Initially pass the command line
		// Test cases can be run from the command line using:  "vvm -test"
		//////
			if ((lnResult = vvm_startTheVvm(lpCmdLine, &llRunTestCases)) < 0 || llRunTestCases)
			{
				// If we ran test cases, 
				if (llRunTestCases)
					return((s32)lnResult);

				// 
				switch (lnResult)
				{
					case -1:
						// Failure to load resource DLL
						MessageBoxA(NULL, "Missing Resource DLL (vvmenu.dll)\nTerminating with error code -1.", "VVM Load Error", MB_OK);
						break;

					case -2:
						// Failure to load OSS.DLL
						MessageBoxA(NULL, "Missing OSS.DLL.\nTerminating with error code -2.", "VVM Load Error", MB_OK);
						break;

					case -3:
						// Failure to load MC.DLL
						MessageBoxA(NULL, "Missing MC.DLL.\nTerminating with error code -3.", "VVM Load Error", MB_OK);
						break;

					case -4:
						// Failure to initialize the VVM to its power-on state
						MessageBoxA(NULL, "Unable to initialize the VVM.\nTerminating with error code -4.", "VVM Initialization Error", MB_OK);
						break;

					default:
						MessageBoxA(NULL, "An unspecified error occurred while starting the VVM.\nTerminating.", "VVM Load Error", MB_OK);
				}
			}


		//////////
		// Begin processing Visual FreePro
		//////
			// Note:  Nothing done yet ... but soon! (James 4:15)


			// Indicate our final exit result
			return((s32)lnResult);
	}




//////////
// #include source files which are not compiled separately
/////
	#include "vfrp_sup.cpp"