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
hijack_loadIcons();
hijack_verifyIcons();
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
	void hijack_loadIcons(void)
	{
		bool		llErrorFile, llErrorUlx, llErrorUly, llErrorWidth, llErrorHeight, llErrorStridex, llErrorStridey;
		u32			lnX, lnY, lnResult, lnUlX, lnUlY, lnWidth, lnHeight, lnStrideX, lnStrideY, lnThisWidth;
		u64			lnNumread, lnErrorOffset, lnErrorCode;
		SRGBA		lrgba;
		SBxml*		vdbi;
		SBxml*		icons;
		SBxml*		icon;
		SCanvas*	canvasIcons;
		SCanvas*	canvasNew;
		SDatum		searchString = { NULL, 0 };
		SDatum		resultString = { NULL, 0 };
		s8			buffer[256];
		s8			bufferWidth[8];
		s8			bufferHeight[8];
		s8			bufferCanvasLength[8];


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
		lnResult	= oss_bxmlaFindAndGetString	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"file",	-1, true), 1, &resultString, &llErrorFile);
		lnUlX		= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"ulx",		-1, true), 1, &llErrorUlx);
		lnUlY		= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"uly",		-1, true), 1, &llErrorUly);
		lnWidth		= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"width",	-1, true), 1, &llErrorWidth);
		lnHeight	= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"height",	-1, true), 1, &llErrorHeight);
		lnStrideX	= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"stridex",	-1, true), 1, &llErrorStridex);
		lnStrideY	= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"stridey",	-1, true), 1, &llErrorStridey);
		oss_datumDelete(&searchString);
		// Validate sanity
		if (llErrorFile || llErrorUlx || llErrorUly || llErrorWidth || llErrorHeight || llErrorStridex || llErrorStridey)
			_asm int 3;

		// Open the file
		memset(&buffer, 0, sizeof(buffer));
		memcpy(buffer, "\\libsf\\vvm\\core\\vdebug\\graphics\\", 32);
		memcpy(buffer + strlen(buffer), resultString.data._s8, (u32)resultString.length);
		lrgba.color = rgba(0,0,0,0);
		oss_loadBitmapFromDisk(buffer, &canvasIcons, &lnWidth, &lnHeight, lrgba);
		oss_saveBitmapToDisk(canvasIcons, canvasIcons->bd, "\\temp\\test.bmp");

		// Store width information
		sprintf_s(bufferWidth,	sizeof(bufferWidth),	"%u\0", lnStrideX - lnUlX);
		sprintf_s(bufferHeight,	sizeof(bufferHeight),	"%u\0", lnStrideY - lnUlY);

		// Iterate through each icon, loading its data
		icon	= oss_bxmlNodeGetFirstChild(icons);
		lnX		= lnUlX;
		lnY		= lnUlY;
		while (icon)
		{
			// Extract this icon from the icon master file
			canvasNew = oss_canvasExtract(canvasIcons, canvasIcons->bd, lnX, lnY, lnX+lnStrideX-lnUlX, lnY+lnStrideY-lnUlY);
			if (!canvasNew)
				_asm int 3;

//			s8 bufferFile[256];
//			sprintf_s(bufferFile, sizeof(bufferFile), "\\temp\\extract_%03u_%04u.bmp", lnX, lnY);
//			oss_saveBitmapToDisk(canvasNew, canvasNew->bd, bufferFile);

			// Store the size for this bitmap data
			lnThisWidth = canvasNew->width * canvasNew->height * sizeof(SRGBA);
			sprintf_s(bufferCanvasLength, sizeof(bufferCanvasLength), "%u\0", lnThisWidth);

			// Append this extracted bitmap data to the bxml
			oss_bxmlaInsert(icon, NULL, "rgbaw", 5, bufferWidth,		strlen(bufferWidth),	strlen(bufferWidth),	true);
			oss_bxmlaInsert(icon, NULL, "rgbah", 5, bufferHeight,		strlen(bufferHeight),	strlen(bufferHeight),	true);
			oss_bxmlaInsert(icon, NULL, "rgba",  4, (s8*)canvasNew->bd,	lnThisWidth,			lnThisWidth,			true);

			// Move to next icon
			lnX += lnStrideX;
			if (lnX >= lnWidth)
			{
				lnY += lnStrideY;
				lnX = lnUlX;
			}

			// Grab the next icon bxml node
			icon = oss_bxmlNodeGetNext(icon);
		}

		// Save the converted bitmap in its stand-alone form
		oss_bxmlSave(vdbi, "\\temp\\icons.bxml", -1, true, true, &lnNumread);
	}

	void hijack_verifyIcons(void)
	{
		bool		llErrorFile, llErrorUlx, llErrorUly, llErrorWidth, llErrorHeight, llErrorStridex, llErrorStridey;
		u32			lnX, lnY, lnResult, lnUlX, lnUlY, lnWidth, lnHeight, lnStrideX, lnStrideY, lnThisWidth;
		u64			lnNumread, lnErrorOffset, lnErrorCode;
		void*		searchPtr = NULL;
		SRGBA		lrgba;
		SBxml*		vdbi;
		SBxml*		icons;
		SBxml*		icon;
		SBxml*		vdbi2;
		SBxml*		icon2;
		SBxmla*		bxmlaName;
		SBxmla*		bxmlaRgba;
		SBxmla*		bxmlaRgbaw;
		SBxmla*		bxmlaRgbah;
		SBxmla*		bxmla2Name;
		SBxmla*		bxmla2Rgba;
		SBxmla*		bxmla2Rgbaw;
		SBxmla*		bxmla2Rgbah;
		SCanvas*	canvasIcons;
		SCanvas*	canvasNew;
		SDatum		searchString = { NULL, 0 };
		SDatum		resultString = { NULL, 0 };
		SDatum		searchStringRgbaw = { (u8*)"rgbaw", 5 };
		SDatum		searchStringRgbah = { (u8*)"rgbah", 5 };
		SDatum		searchStringRgba  = { (u8*)"rgba",  4 };
		s8			buffer[256];
		s8			bufferWidth[8];
		s8			bufferHeight[8];
		s8			bufferCanvasLength[8];


		// Load the VDEBUG_ICONS.BXML file
		// file="vdebug_icons.bmp" ulx="2" uly="2" width="36" height="36" stridex="38" stridey="38"
		vdbi = oss_bxmlLoad("\\libsf\\vvm\\core\\vdebug\\graphics\\vdebug_icons.bxml", -1, &lnNumread, &lnErrorOffset, &lnErrorCode);
		if (!vdbi)
			_asm int 3;

		vdbi2 = oss_bxmlLoad("\\temp\\icons.bxml", -1, &lnNumread, &lnErrorOffset, &lnErrorCode);
		if (!vdbi2)
			_asm int 3;

		// Iterate through loading the icons
		icons = oss_bxmlNodeGetFirstChild(vdbi);
		if (!icons)
			_asm int 3;

		// Grab the name of the icon file, and the associated integers
		lnResult	= oss_bxmlaFindAndGetString	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"file",	-1, true), 1, &resultString, &llErrorFile);
		lnUlX		= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"ulx",		-1, true), 1, &llErrorUlx);
		lnUlY		= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"uly",		-1, true), 1, &llErrorUly);
		lnWidth		= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"width",	-1, true), 1, &llErrorWidth);
		lnHeight	= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"height",	-1, true), 1, &llErrorHeight);
		lnStrideX	= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"stridex",	-1, true), 1, &llErrorStridex);
		lnStrideY	= oss_bxmlaFindAndGetU32	(icons,	NULL,	oss_datumSet(&searchString, (u8*)"stridey",	-1, true), 1, &llErrorStridey);
		oss_datumDelete(&searchString);
		// Validate sanity
		if (llErrorFile || llErrorUlx || llErrorUly || llErrorWidth || llErrorHeight || llErrorStridex || llErrorStridey)
			_asm int 3;

		// Open the file
		memset(&buffer, 0, sizeof(buffer));
		memcpy(buffer, "\\libsf\\vvm\\core\\vdebug\\graphics\\", 32);
		memcpy(buffer + strlen(buffer), resultString.data._s8, (u32)resultString.length);
		lrgba.color = rgba(0,0,0,0);
		oss_loadBitmapFromDisk(buffer, &canvasIcons, &lnWidth, &lnHeight, lrgba);
		oss_saveBitmapToDisk(canvasIcons, canvasIcons->bd, "\\temp\\test.bmp");

		// Store width information
		sprintf_s(bufferWidth,	sizeof(bufferWidth),	"%u\0", lnStrideX - lnUlX);
		sprintf_s(bufferHeight,	sizeof(bufferHeight),	"%u\0", lnStrideY - lnUlY);

		// Iterate through each icon, loading its data
		icon	= oss_bxmlNodeGetFirstChild(icons);
		lnX		= lnUlX;
		lnY		= lnUlY;
		while (icon)
		{
			// Extract this icon from the icon master file
			canvasNew = oss_canvasExtract(canvasIcons, canvasIcons->bd, lnX, lnY, lnX+lnStrideX-lnUlX, lnY+lnStrideY-lnUlY);
			if (!canvasNew)
				_asm int 3;


			// Store the size for this bitmap data
			lnThisWidth = canvasNew->width * canvasNew->height * sizeof(SRGBA);
			sprintf_s(bufferCanvasLength, sizeof(bufferCanvasLength), "%u\0", lnThisWidth);

			// Append this extracted bitmap data to the bxml
			oss_bxmlaInsert(icon, NULL, "rgbaw", 5, bufferWidth,		strlen(bufferWidth),	strlen(bufferWidth),	true);
			oss_bxmlaInsert(icon, NULL, "rgbah", 5, bufferHeight,		strlen(bufferHeight),	strlen(bufferHeight),	true);
			oss_bxmlaInsert(icon, NULL, "rgba",  4, (s8*)canvasNew->bd,	lnThisWidth,			lnThisWidth,			true);

			//////////
			// Get the vdbi entry
			//////
				oss_bxmlFindFirst(icon,	NULL, &bxmlaName,	oss_datumSet(&searchString, (u8*)"name",  -1, true), false, true, NULL);
				if (!bxmlaName)
					_asm int 3;

				// Grab the other attributes
				oss_bxmlFindFirst(icon,	NULL, &bxmlaRgbaw,	&searchStringRgbaw, false, true, NULL);
				oss_bxmlFindFirst(icon,	NULL, &bxmlaRgbah,	&searchStringRgbah, false, true, NULL);
				oss_bxmlFindFirst(icon,	NULL, &bxmlaRgba,	&searchStringRgba,  false, true, NULL);
				if (!bxmlaRgbaw || !bxmlaRgbah || !bxmlaRgba)
					_asm int 3;


			//////////
			// Locate the matching entry in vdbi2
			//////
				oss_datumSet(&searchString, bxmlaName->_name.data._u8, bxmlaName->_name.length, true);
				if (!searchPtr)
				{
					// Find the first item
					oss_bxmlFindFirst(vdbi2, NULL, &bxmla2Name, &searchString, true, false, &searchPtr);
					if (!bxmla2Name)
						_asm int 3;

				} else {
					// Move to the next item
					if (!oss_bxmlFindContinue(searchPtr))
						_asm int 3;

				}

				// Iterate until we find the data match
				while (bxmla2Name)
				{
					if (oss_memicmpDatum2Datum2(&bxmlaName->_data, &bxmla2Name->_data) == 0)
						break;		// We found a match

					// Move to the next item
					if (!oss_bxmlFindContinue(searchPtr))
						_asm int 3;
				}

				// Grab the other attributes
				bxmla2Rgbaw	= NULL;
				bxmla2Rgbah	= NULL;
				bxmla2Rgba	= NULL;
				icon2		= bxmla2Name->_parent;
				oss_bxmlFindFirst(icon2,	NULL, &bxmla2Rgbaw,	&searchStringRgbaw, false, true, NULL);
				oss_bxmlFindFirst(icon2,	NULL, &bxmla2Rgbah,	&searchStringRgbah, false, true, NULL);
				oss_bxmlFindFirst(icon2,	NULL, &bxmla2Rgba,	&searchStringRgba,  false, true, NULL);
				if (!bxmla2Rgbaw || !bxmla2Rgbah || !bxmla2Rgba)
					_asm int 3;

			
			//////////
			// Verify that the content extracted from the bitmap is the same as the rgbaw, rgbah, and rgba attributes of vdbi2
			//////
				if (bxmlaRgbaw->_data.datum.length != bxmla2Rgbaw->_data.datum.length)
					_asm int 3;
				if (bxmlaRgbah->_data.datum.length != bxmla2Rgbah->_data.datum.length)
					_asm int 3;
				if (bxmlaRgba->_data.datum.length != bxmla2Rgba->_data.datum.length)
					_asm int 3;
				if (oss_memicmpDatumDatum(&bxmlaRgbaw->_data.datum, &bxmla2Rgbaw->_data.datum) != 0)
					_asm int 3;
				if (oss_memicmpDatumDatum(&bxmlaRgbah->_data.datum, &bxmla2Rgbah->_data.datum) != 0)
					_asm int 3;
				if (oss_memicmpDatumDatum(&bxmlaRgba->_data.datum,  &bxmla2Rgba->_data.datum)  != 0)
					_asm int 3;
				// If we get here, they are the same


			//////////
			// Move to next icon
			//////
				lnX += lnStrideX;
				if (lnX >= lnWidth)
				{
					lnY += lnStrideY;
					lnX = lnUlX;
				}
				// Grab the next icon bxml node
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
