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

//////////
// Temporarily hijacked to convey some conversion from the existing icon.bmp files and their
// corresponding bxml files, to extract individual icons into a single BXML which is written
// to disk.
//////////
hijack_toLoadIcons();
return(false);

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
// Temporarily hijacked to convey some conversion from the existing icon.bmp files and their
// corresponding bxml files, to extract individual icons into a single BXML which is written
// to disk.
//////////
	void hijack_toLoadIcons(void)
	{
		u32			lnResult, lnUlX, lnUlY, lnWidth, lnHeight, lnStrideX, lnStrideY, lnFilenameLength;
		u64			lnNumread, lnErrorOffset, lnErrorCode;
		SBxml*		vdbi;
		SBxml*		icons;
		SBxml*		icon;
		csu8p		file;
		SCanvas*	canvasIcons;
		SDatum		searchString;
		SDatum		resultString;
		s8			buffer[256];


		// Load the VDEBUG_ICONS.BXML file
		// file="vdebug_icons.bmp" ulx="2" uly="2" width="36" height="36" stridex="38" stridey="38"
		vdbi = oss_bxmlLoad("\\libsf\\vvm\\core\\vdebug\\graphics\\vdebug_icons.bxml", -1, &lnNumread, &lnErrorOffset, &lnErrorCode);
		if (!vdbi)
			_asm int 3;

		// Iterate through loading the icons
		icons = oss_bxmlNodeGetFirstChild(vdbi);
		if (!icons)
			_asm int 3;

		// Grab the name of the icon file, and the associated integers
		lnResult	= oss_bxmlaFindAndGetString	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"file",	-1, true), 1, &resultString);
		lnUlX		= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"ulx",		-1, true), 1);
		lnUlY		= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"uly",		-1, true), 1);
		lnWidth		= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"width",	-1, true), 1);
		lnHeight	= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"height",	-1, true), 1);
		lnStrideX	= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"stridex",	-1, true), 1);
		lnStrideY	= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"stridey",	-1, true), 1);
		oss_datumDelete(&searchString);
		// Validate sanity
		if (!file._u8 || lnFilenameLength > sizeof(buffer) || lnUlX == -1 || lnUlY == -1 || lnWidth == -1 || lnHeight == -1 || lnStrideX == -1 || lnStrideY == -1)
			_asm int 3;

		// Open the file
		memset(&buffer, 0, sizeof(buffer));
		memcpy(buffer, file._s8, lnFilenameLength);
		oss_loadBitmapFromDisk(buffer, &canvasIcons, &lnWidth, &lnHeight, rgba(0,0,0,0));

		// Iterate through each icon, loading its data
		icon = oss_bxmlNodeGetFirstChild(icons);
		while (icon)
		{
			// Extract this icon from the icon master file

			// Move to next icon
			icon = oss_bxmlNodeGetNext(icon);
		}
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
