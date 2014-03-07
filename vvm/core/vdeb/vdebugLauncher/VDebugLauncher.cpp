//////////
//
// /libsf/vvm/vdebuglauncher/VDebugLauncher.cpp
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
//     Sep.19.2012 - Initial creation
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



#include <Windows.h>
#include <stdio.h>

#include "\libsf\vvm\core\common\common.h"
#include "\libsf\vvm\core\vvm\vvm_structs.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\oss\oss_class.h"

// Global variables
const s8		cgcVDebugName[]					= "VDebug v0.70";
const s8		cgcCR[]							= "\n";

// Forward declarations
bool			iValidateColor					(u32 tnColor);
u32				iBuildDebuggerIniFile			(u32 tnUniqueId, u32 tnBackColor);




//////////
//
// Main entry point for the launcher.  Its main goal is to locate the
// running VVM instance (and if not found, then to instantiate it, and then
// send a message to the VVM asking for a unique ID number which it will use
// to create a vvm_########.ini file, where ######## is the unique ID number,
// which contains information about the vdebug.dll instance to launch.
//
// This launcher process is created so that multiple debuggers can connect to
// a running instance of a VVM, each capable of simultaneously debugging
// separate or identical portions of code (since everything is automatically
// coordinated through the VVM for code changes and data access).
//
// Future versions will allow remote debugging via a stub which acts as a
// network transporter.
//
//////
	int APIENTRY WinMain(	HINSTANCE	hInstance,
							HINSTANCE	hPrevInstance,
							LPTSTR		lpCmdLine,
							int			nCmdShow)
	{
		u32		lnResult, lnMagicNumber, lnUniqueId, lnBackColor;
		HWND	lhWnd;


		// Attempt to find the window
		lnResult	= -1;
		lhWnd		= FindWindowA(gcVvmOssMessageClass, NULL);
		if (!lhWnd)
		{
			// Failure
// TODO:  In the future, possibly startup the VVM.EXE automatically
			MessageBoxA(NULL, "Unable to find a running VVM instance", "VDebug Failure", MB_OK);

		} else {
			// Send it a message to obtain the next unique ID
			while (1)
			{
				lnMagicNumber = SendMessage(lhWnd, VVMOSS_REQUEST_MAGIC_NUMBER, 0, 0);
				if (lnMagicNumber == VVMOSS_MAGIC_NUMBER)
				{
					lnUniqueId = SendMessage(lhWnd, VVMOSS_REQUEST_UNIQUE_ID, 0, 0);
					if (lnUniqueId >= 1000)
					{
						// We're good
						lnBackColor = SendMessage(lhWnd, VVMOSS_REQUEST_UNIQUE_DEBUGGER_BACKGROUND_COLOR, 0, 0);
						if (!iValidateColor(lnBackColor))
							lnBackColor = -1;
						
						// Prepare the ini file and tell VVM's OSS to try to load the debugger
						lnResult = iBuildDebuggerIniFile(lnUniqueId, lnBackColor);
						if (lnResult != -1)
						{
							lnResult = SendMessage(lhWnd, VVMOSS_LOAD_DEBUGGER_DLL, lnUniqueId, 0);
							if ((s32)lnResult >= 0)
								break;		// We're good!
						}
					}
				}
				// If we get here, something failed
				MessageBoxA(NULL, "Unable to connect to the running VVM instance.", "VDebug Failure", MB_OK);
				break;
			}
		}
		// When we reach here, either the DLL has been launched, or it has not, but
		// the user has been informed.  If so, then the launcher has served its purpose.
		// The VDebug.dll instance has been loaded, and it is self-contained.

		// Indicate success or failure
		return(lnResult);
	}

	// We're looking for colors like rgb(255,225,192), where at least one is 255, and the others are at least 192
	bool iValidateColor(u32 tnColor)
	{
		if (red(tnColor) == 255 && grn(tnColor) >= 192 && blu(tnColor) >= 192)
			return(true);		// It's has red as an anchor in its color

		if (red(tnColor) >= 192 && grn(tnColor) == 255 && blu(tnColor) >= 192)
			return(true);		// It's has green as an anchor in its color

		if (red(tnColor) >= 192 && grn(tnColor) >= 192 && blu(tnColor) == 255)
			return(true);		// It's has green as an anchor in its color

		// If we get here, the color sequence is invalid for what we expect back from VVM/OSS
		return(false);
	}

	u32 iBuildDebuggerIniFile(u32 tnUniqueId, u32 tnBackColor)
	{
		u32		lnResult, lnLength;
		FILE*	lfh;
		s8		buffer[_MAX_PATH];
		s8		bufferDll[_MAX_PATH];
		s8		bufferColor[1024];


		// Initially indicate failure
		lnResult = -1;


		//////////
		// Create the output filename
		//////
			memset(buffer, 0, sizeof(buffer));
			GetCurrentDirectoryA(sizeof(buffer), buffer);
			lnLength = strlen(buffer);
			if (buffer[lnLength - 1] != '\\')
			{
				buffer[lnLength] = '\\';
				++lnLength;
			}
			memcpy(bufferDll, buffer, sizeof(bufferDll));
			sprintf_s(buffer    + lnLength, sizeof(buffer)    - lnLength, "vvm_%08x.ini\000", tnUniqueId);
			sprintf_s(bufferDll + lnLength, sizeof(bufferDll) - lnLength, "vdebug.dll\000");
			sprintf_s(bufferColor, "backcolor=%08x\000", tnBackColor);


		//////////
		// Create the output file
		//////
			fopen_s(&lfh, buffer, "wb+");
			if (lfh)
			{
				// We're good
				// Write the debugger name
				fwrite(cgcName,			1,	sizeof(cgcName) - 1,			lfh);
				fwrite(cgcVDebugName,	1,	sizeof(cgcVDebugName) - 1,		lfh);
				fwrite(cgcCR,			1,	sizeof(cgcCR) -1,				lfh);

				// Write the DLL location (fullpath)
				fwrite(cgcDll,			1,	sizeof(cgcDll) - 1,				lfh);
				fwrite(bufferDll,		1,	strlen(bufferDll),				lfh);
				fwrite(cgcCR,			1,	sizeof(cgcCR) -1,				lfh);

				// Write the color
				fwrite(bufferColor,		1,	strlen(bufferColor),			lfh);
				fwrite(cgcCR,			1,	sizeof(cgcCR) -1,				lfh);

				// All done
				fclose(lfh);
				lnResult = 0;
			}


		// All done
		return(lnResult);
	}
