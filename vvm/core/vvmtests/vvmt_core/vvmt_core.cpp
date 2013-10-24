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

hijack_createWindow();
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
		SBGRA		lrgba;
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
			lnThisWidth = canvasNew->width * canvasNew->height * sizeof(SBGRA);
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
		SBGRA		lrgba;
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
			lnThisWidth = canvasNew->width * canvasNew->height * sizeof(SBGRA);
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
		// When we get here, we know everything has been tested successfully
	}




//////////
//
// Temporary function for hijacking control of the VVM during development
//
/////
	SScreen* screen;
	SCanvas* canvas;

	void hijack_createWindow(void)
	{
		s32				lnX, lnY;
		u32				lnWidth, lnHeight, lnMinWidth, lnMinHeight, lnMaxWidth, lnMaxHeight;
		SOssWindow*		low;
		SCallbacksW		cb;
		SStartEnd		lse;


		//////////
		// Indicate our handlers
		//////
			cb.window._callback_created		= (u64)&hj_window_created;
			cb.window._callback_unload		= (u64)&hj_window_unload;
			cb.window._callback_closed		= (u64)&hj_window_closed;
			cb.window._callback_moved		= (u64)&hj_window_moved;
			cb.window._callback_resized		= (u64)&hj_window_resized;
			cb.window._callback_gotFocus	= (u64)&hj_window_gotFocus;
			cb.window._callback_lostFocus	= (u64)&hj_window_lostFocus;

			cb.object._callback_enter		= (u64)&hj_object_enter;
			cb.object._callback_leave		= (u64)&hj_object_leave;

			cb.mouse._callback_down			= (u64)&hj_mouse_down;
			cb.mouse._callback_up			= (u64)&hj_mouse_up;
			cb.mouse._callback_move			= (u64)&hj_mouse_move;
			cb.mouse._callback_hover		= (u64)&hj_mouse_hover;

			cb.keyboard._callback_down		= (u64)&hj_keyboard_down;
			cb.keyboard._callback_up		= (u64)&hj_keyboard_up;
			cb.keyboard._callback_press		= (u64)&hj_keyboard_press;
			cb.keyboard._callback_flags		= (u64)&hj_keyboard_flags;

			cb.drag._callback_start			= (u64)&hj_drag_start;
			cb.drag._callback_dragging		= (u64)&hj_drag_dragging;
			cb.drag._callback_drop			= (u64)&hj_drag_drop;

			cb.custom._callback_custom		= (u64)&hj_custom_custom;


		//////////
		// Create our window position
		//////
			memset(&lse, 0, sizeof(SStartEnd));
			low = oss_enumerateMonitors(&lse);
			oss_computeMonitorCoordinates(low, 80.0f, _VVMOSS_SCREEN_UPPER_LEFT, 5.0f, &lnX, &lnY, &lnWidth, &lnHeight, &lnMaxWidth, &lnMaxHeight, &lnMinWidth, &lnMinHeight);


		//////////
		// Create our screen template
		//////
			SBGRA foreground, background;
			foreground.color = rgba(0,0,0,0);
			background.color = rgba(255,255,255,255);
			low = oss_createScreenTemplate(	oss_getNextUniqueId(),
											oss_getNextUniqueId(),
											"Test Window", -1, 
											lnX, lnY, lnWidth, lnHeight, lnMaxWidth, lnMaxHeight, lnMinWidth, lnMinHeight,
											0, 0, lnWidth, 40, 4, foreground, background,
											true, true, true, true, true,
											&cb);

			screen = oss_requestScreen(0, low);
			if (screen)
			{
				canvas = oss_requestCanvasForScreen(screen);
				if (canvas)
				{
					SBGRA white1 = { 255, 255, 255, 255 };
					SBGRA white2 = { 255, 215, 215, 255 };
					SBGRA white3 = { 215, 255, 215, 255 };
					SBGRA white4 = { 215, 215, 255, 255 };
					SBGRA black = { 0, 0, 0, 255 };
					SBGRA blue = { 255, 235, 235, 255 };
					oss_canvasFillRect(canvas, canvas->bd, 0, 0, canvas->width, canvas->height, 0, white1, white1);
					oss_canvasGradient(canvas, canvas->bd, white1, white2, white3, white4);
					oss_canvasDrawFixedPointText(canvas, canvas->bd, 8, 16, 50, 50, "8x16 font -- ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789", -1, black, white1);
					oss_canvasDrawFixedPointText(canvas, canvas->bd, 8, 14, 50, 70, "8x14 font -- ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789", -1, black, white1);
					oss_canvasDrawFixedPointText(canvas, canvas->bd, 8, 8, 50, 90, "8x8  font -- ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789", -1, black, white1);
					oss_canvasDrawFixedPointText(canvas, canvas->bd, 8, 6, 50, 110, "8x6  font -- ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789", -1, black, white1);
					oss_canvasArc(canvas, canvas->bd, 2 0 0, 200, 40.0f, 0.0f, 3.14f, 2, black);
					oss_canvasRefresh(canvas);
				}
			}
	}

// Called after window is created, before it is displayed
u64 CALLTYPE hj_window_created(u64 tnUniqueId, SOssWindow* tisw)
{
	return(0);
}

// Called when a window will be closed, while everything related to it is still viable
u64 CALLTYPE hj_window_unload(u64 tnUniqueId, SOssWindow* tisw)
{
	return(0);
}

// Called after a window has been destroyed, before it is released by VVMOSS's internal lists of known windows
u64 CALLTYPE hj_window_closed(u64 tnUniqueId, SOssWindow* tisw)
{
	return(0);
}

// After a window has been moved from one place to another (not while it is moving)
u64 CALLTYPE hj_window_moved(u64 tnUniqueId, SOssWindow* tisw, u32 tnXNew, u32 tnYNew)
{
	return(0);
}

// After a window has been resized, and the buffers related to its screen have been allocated
u64 CALLTYPE hj_window_resized(u64 tnUniqueId, SOssWindow* tisw, u32 tnWidthNew, u32 tnHeightNew)
{
	return(0);
}

// After a window has received focus, and after the window that lost focus (if any) has been signaled
u64 CALLTYPE hj_window_gotFocus(u64 tnUniqueId, SOssWindow* tisw)
{
	return(0);
}

// Before a new window receives focus
u64 CALLTYPE hj_window_lostFocus(u64 tnUniqueId, SOssWindow* tisw)
{
	return(0);
}

u64 CALLTYPE hj_object_enter(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
{
	return(0);
}

u64 CALLTYPE hj_object_leave(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
{
	return(0);
}

u64 CALLTYPE hj_mouse_down(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
{
	return(0);
}

u64 CALLTYPE hj_mouse_up(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
{
	return(0);
}

u64 CALLTYPE hj_mouse_move(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
{
	return(0);
}

u64 CALLTYPE hj_mouse_hover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
{
	return(0);
}

u64 CALLTYPE hj_keyboard_down(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
{
	return(0);
}

u64 CALLTYPE hj_keyboard_up(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
{
	return(0);
}

u64 CALLTYPE hj_keyboard_press(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
{
	return(0);
}

u64 CALLTYPE hj_keyboard_flags(u64 tnUniqueId, SOssWindow* tisw, u32 tnKeyFlagsOld, u32 tnKeyFlagsNew)
{
	return(0);
}

u64 CALLTYPE hj_drag_start(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
{
	return(0);
}

u64 CALLTYPE hj_drag_dragging(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds)
{
	return(0);
}

u64 CALLTYPE hj_drag_drop(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds)
{
	return(0);
}

u64 CALLTYPE hj_custom_custom(u64 tnUniqueId, SOssWindow* tisw, u64 tnCustomEventId, u64 tnOtherData)
{
	return(0);
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
