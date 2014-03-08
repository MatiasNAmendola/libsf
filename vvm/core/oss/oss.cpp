//////////
//
// /libsf/vvm/vvmoss/vo.cpp
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




#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define _NATIVE_CALLS					// We use native function calls here
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

#define _OSS_COMPILING

#include "\libsf\vvm\core\common\common.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_oss.h"
#include "\libsf\vvm\core\common\common_oss_plugins.h"
#include "\libsf\vvm\core\common\common_oss_const.h"
#include "\libsf\vvm\core\common\common_mc.h"
#include "\libsf\vvm\core\localization\vvmenu\resource.h"					// Resource constants
#include "oss_const.h"
#include "oss_structs.h"
#include "oss_istructs.h"
#include "\libsf\vvm\core\vvm\vvm_structs.h"
#include "oss_plugins.h"
#include "oss_defs.h"
#include "oss_glob.h"
#include "oss_class.h"
#include "\libsf\vvm\core\common\vvm_key_const.h"




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
				gsemBuildScreen			= oss_createSemaphore();
				gsemForeignThreadAccess	= oss_createSemaphore();
				break;

			case DLL_PROCESS_DETACH:
				oss_deleteSemaphore(gsemBuildScreen);
				oss_deleteSemaphore(gsemForeignThreadAccess);
				break;

			case DLL_THREAD_ATTACH:
			case DLL_THREAD_DETACH:
				break;
		}
		return TRUE;
	}




//////////
//
// Required first initialization after initial DLL load
//
//////
	// Called after the VVM has loaded VVMOSS before continuing with loading VVMMCC
	u64 CALLTYPE oss_firstCallback(u32 tnDoNotLoadOptions)
	{
		//////////
		// Load the base VVM functions
		//////
			iLoadVvmFunctionsFromDll();
			iLoadMcFunctionsFromDll();


		//////////
		// Tell the VVM.DLL to initialize itself
		//////
			if ((tnDoNotLoadOptions & _DO_NOT_LOAD_VVM) != _DO_NOT_LOAD_VVM)
			{
				vvm_firstCallback(tnDoNotLoadOptions | _DO_NOT_LOAD_OSS);
				vvm_bootstrapInitialization();
			}
			if ((tnDoNotLoadOptions & _DO_NOT_LOAD_MC) != _DO_NOT_LOAD_MC)
			{
				mc_firstCallback(tnDoNotLoadOptions | _DO_NOT_LOAD_OSS);
				mc_bootstrapInitialization();
			}


		//////////
		// Initialize internally required variables and semaphores
		//////
			gsemScreenAccess = oss_createSemaphore();
			gsemCanvasAccess = oss_createSemaphore();
			gsemRegionAccess = oss_createSemaphore();


		//////////
		// Initialize the sound plugin structure
		//////
			memset(&gsSoundPlugin, 0, sizeof(gsSoundPlugin));


		//////////
		// Indicate success
		//////
			return(1);
	}




//////////
//
// Called after the VVM has loaded VVMOSS, but before continuing on to load the VVMMCC
//
//////
	void CALLTYPE oss_bootstrapInitialization(void)
	{
		//////////
		//
		// Attempt to load plugins
		//
		// See:
		//		vo_plugins.h
		//		vo_plugins.cpp
		//		(as well as the source files in the \libsf\vvm\core\plugins\ directories)
		//
		//////
			ioss_loadPlugins();
	}




// 
// //////////
// //
// // Required first initialization after initial DLL load and first callback
// //
// //////
// 	void CALLTYPE iioss_soundCallback(f32* stream, u32 tnLength, bool* tlContinueAfterThisSampleSet)
// 	{
// 		u32 lnI;
// 
// 
// 		// Create rapid triangle waves
// 		for (lnI = 0; lnI < tnLength; lnI++)
// 		{
// 			if		(lnI % 4 == 0)		stream[lnI] =  1.0f;
// 			else if (lnI % 3 == 0)		stream[lnI] =  0.33f;
// 			else if (lnI % 2 == 0)		stream[lnI] = -0.33f;
// 			else						stream[lnI] = -1.0f;
// 		}
// 	}
// 
// 	// Called after the VVM has loaded VVMOSS before continuing with loading VVMMCC
// 	void CALLTYPE oss_bootstrapInitialization(u64 tnDebuggerInterfaceAddress)
// 	{
// 			u64 lnStream1, lnStream2, lnStream3;
// 
// 		//////////
// 		// Attempt to load plugins (vo_plugins.h, vo_plugins.cpp)
// 		//////
// 			ioss_loadPlugins();
// 			oss_soundInitialize();
// 
// 			lnStream2 = (u32)oss_soundCreateTone(350.0f, 440.0f, -1.0f, -1.0f, 5000);
// 			lnStream1 = (u32)oss_soundCreateTone(697.0f, 1209.0f, -1.0f, -1.0f, 1500);
// //			lnStream3 = (u32)oss_soundCreateStream(44100, (u64)&iioss_soundCallback);
// 
// 			oss_soundPlayStart(lnStream1, 1.0f);
// 
// 			// Only play for half a second
// 			oss_sleep(6000);
// //			oss_soundPlayStart(lnStream2, 0.3f);
// //			oss_sleep(1000);
// 
// //			lnStream3 = (u32)oss_soundCreateTone(350.0f, 440.0f, -1.0f, -1.0f, 1000);
// //			oss_soundPlayStart(lnStream1, 0.3f);
// //			oss_soundPlayStart(lnStream3, 0.5f);
// //			oss_sleep(3000);
// 
// 			// We're 
// 			oss_soundPlayCancel(lnStream1);
// //			oss_soundPlayCancel(lnStream2);
// //			oss_soundPlayCancel(lnStream3);
// 
// 			oss_soundDelete(lnStream1);
// //			oss_soundDelete(lnStream2);
// //			oss_soundDelete(lnStream3);
// 	}





//////////
//
// Called after the VVM has loaded, after VVMMC has loaded, after all required subordinate DLLs are
// loaded, with their firstCallback() and bootstrapInitialization() functions also already being
// called.
//
// This is the traditional startup place for most oss-specific initialization that's not bootup-
// fundamental.
//
//////
	void CALLTYPE oss_initialization(void)
	{
		// Nothing is currently defined
	}





//////////
//
// Called to get a version string of this DLL
//
///////
	const s8* CALLTYPE oss_getVersion(void)
	{
		return(cgcOssVersion);
	}





//////////
//
// Create a message Window
//
//////
	bool CALLTYPE oss_createMessageWindow(void)
	{
		u32		lnError;
		DWORD	lnThreadId;
		HANDLE	lnhThread;


		//////////
		// Register the message window class
		//////
			lnError = 0;
			if (!ioss_registerWindowClasses(&lnError))
				return(false);


		//////////
		// Create the window
		//////
			lnhThread = CreateThread(0, 0, &ioss_messageLoop, 0, 0, &lnThreadId);		// Create the listener thread


		//////////
		// Pause until the window is created
		//////
			while (ghWndMsg == 0)
				Sleep(0);


		//////////
		// All done
		//////
			return(true);
	}




//////////
//
// Create a visible Window, one which will receive all messages through the main
// OSS thread
//
//////
	u64 CALLTYPE oss_createVisibleWindow(SOssWindow* tisw, u64 tnScreenId)
	{
		SOssWindowLL* w;


		// Lock the semaphore for synchronous access
		oss_lockSemaphore(gsemBuildScreen);

		// Physically create the window in the message thread (so it will receive messages from windows in the message thread)
		SendMessage(ghWndMsg, VVMOSS_CREATE_VISIBLE_WINDOW, (WPARAM)tisw, (LPARAM)&w);

		// Unlock the semaphore
		oss_unlockSemaphore(gsemBuildScreen);

		// Return our screen identifier
		if (w)
		{
			// Store the screen id
			w->isw.screenId = tnScreenId;

			// Return the status
			return(w->ll.uniqueId);

		} else {
			// Indicate failure
			return(0);
		}
	}




//////////
//
// Called to register a function that a plugin possesses, or to unregister a function.
//
//////
	u64 CALLTYPE oss_plugin_registerFunction(u64 tnInstanceId, u64 tnFunction, f32 tfVersion, u32 tnBuild, const u8* tcMetaName, u64 tnFunc)
	{
		_isSInterfacePlugin*	plugin;
		SStartEndCallback		cb;


		// Prepare for search
		cb._func	= (u64)&ioss_plugin_registerCallback;
		cb.extra	= tnInstanceId;

		// Search for the plugin
		plugin = (_isSInterfacePlugin*)vvm_SEChain_searchByCallback(&gsRootFunctionPlugins, &cb);
		if (plugin)
		{
			switch (tnFunction)
			{
				case _VVMOSS_PLUGIN_EDITOR:
					// They are registering an editor
					plugin->editor.available	= true;
					plugin->editor.version		= tfVersion;
					plugin->editor.build		= tnBuild;
					plugin->editor._func		= tnFunc;
					vvm_datumSet(&plugin->editor.identifier, (u8*)tcMetaName, -1, true);
					return(0);
					break;

				default:
					// Requested function is not known
					return(-2);
					break;
			}

		} else {
			// Plugin was not found
			return(-1);
		}
	}




	u64 CALLTYPE oss_plugin_unregisterFunction(u64 tnInstanceId, u64 tnFunction)
	{
		return(0);
	}




//////////
//
// Query the OS for information about the system
//
//////
	void CALLTYPE oss_getSystemInfo(SSysInfo* tsi)
	{
		SYSTEM_INFO lsi;


		// Make sure the environment is sane
		if (tsi)
		{
			// Ask the OS about the system
			GetSystemInfo(&lsi);

			// Store the parameters we care about
			tsi->cores					= (s32)lsi.dwNumberOfProcessors;				// Includes hyper-threaded cores on Intel CPUs
			tsi->addressOf1MsTickCount	= (u64*)&gnExternallyVisibleTickCount;			// Anyone requesting this information can access our externally visible tick count variable
		}
	}




/////////
//
// Called to release this thread's timeslice so the OS can service any other tasks of equal
// priority.  Sending a millisecond time of 0 immediately returns if nothing else is waiting.
//
//////
	void CALLTYPE oss_sleep(u32 tnMilliseconds)
	{
		Sleep(tnMilliseconds);
	}




//////////
//
// Called to store the immediate / current date and time to the specified structure.
//
//////
	void CALLTYPE oss_dateTimeGet(SDateTime* tdt)
	{
		SYSTEMTIME		lst;
		LARGE_INTEGER	lpc;
		LARGE_INTEGER	lpf;


		// Grab the current local time
		GetLocalTime(&lst);
		tdt->year			= lst.wYear;
		tdt->month			= (u8)lst.wMonth;
		tdt->day			= (u8)lst.wDay;
		tdt->hour			= (u8)lst.wHour;
		tdt->minute			= (u8)lst.wMinute;
		tdt->millisecond	= lst.wMilliseconds;

		// Grab the high resolution timer information
		QueryPerformanceCounter(&lpc);
		QueryPerformanceFrequency(&lpf);
		tdt->tickCount	= lpc.QuadPart;
		tdt->frequency	= lpf.QuadPart;
	}




//////////
//
// Called to change the filename extension from what it is (if any) to the indicated form.
// Allocates a new string with oss_alloc, returns a pointer to it.
//
//////
	s8* CALLTYPE oss_changePathnameExtension(s8* tcPathname, s8* tcNewExtension)
	{
		s32		lnI;
		u32		lnLength, lnNewExtensionLength;
		s8*		lcNewPathname;


		// Make sure the environment's sane
		if (tcPathname)
		{
			// Grab the string length
			lnLength				= strlen(tcPathname);
			lnNewExtensionLength	= strlen(tcNewExtension);

			// Scan backwards for a period
			for (lnI = lnLength - 1; lnI >= 0; lnI--)
			{
				if (tcPathname[lnI] == '.')
					break;
			}

			// If we didn't find a period, use the entire length
			if (lnI < 0)
				lnI = lnLength;

			// Allocate that much plus the length of the new extension plus the trailing NULL
			lcNewPathname = (s8*)oss_alloc(lnI + lnNewExtensionLength + 1, false);
			if (lcNewPathname)
			{
				// Copy the old stem
				memcpy(lcNewPathname,		tcPathname,		lnI);
				// Copy the new extension
				memcpy(lcNewPathname + lnI,	tcNewExtension,	lnNewExtensionLength);
				// NULL terminate it
				lcNewPathname[lnI + lnNewExtensionLength] = 0;
				// All done!
				return(lcNewPathname);
			}
		}
		// If we get here, no valid pointer to begin with
		return(NULL);
	}




//////////
//
// Called to indicate if the specified filename characters are valid for this operating system
//
//////
	bool CALLTYPE oss_validateFilenameCharacter(s8* tcPathname, u64 tnPathnameLength, u64* tnErrorPosition)
	{
		u64	lnI;
		u8	ch;


		// Make sure our environment is sane
		if (tcPathname)
		{
// TODO:  future enhancement, need to check the filename format to verify it's of a valid form
			// For every character, repeat all the way through
			for (lnI = 0; lnI < tnPathnameLength; lnI++)
			{
				ch = tcPathname[lnI];
				if (ch >= 'a' && ch <= 'z')
				{	// lower-case character
				} else if (ch >= 'A' && ch <= 'Z') {
					// upper-case character
				} else if (ch >= '0' && ch <= '9') {
					// number
				} else {
					switch (ch)
					{
						case '/':
						case '\\':
						case ':':
						case '.':
						case ' ':
						case ';':
						case ',':
						case '~':
						case '!':
						case '@':
						case '#':
						case '$':
						case '%':
						case '^':
						case '&':
						case '(':
						case ')':
						case '_':
						case '+':
						case '-':
						case '=':
						case '[':
						case ']':
						case '{':
						case '}':
						case '\'':
						case '\"':
							break;
						default:
							// Invalid character
							if (tnErrorPosition)
								*tnErrorPosition = lnI;
							return(false);
					}
				}
				// If we get here, still good
			}
			// If we get here, it's all good
			return(true);
		}
		// If we get here, invalid parameters
		if (tnErrorPosition)
			*tnErrorPosition = 0;
		return(false);
	}




//////////
//
// Deletes the specified screen and its associated os-specific window
//
//////
	u64 CALLTYPE oss_deleteScreen(SScreen* ts)
	{
		return(0);
	}




//////////
//
// Deletes the specified canvas and removes it from everything it's connected to
//
//////
	u64 CALLTYPE oss_deleteCanvas(SCanvas* tc)
	{
		SScaleMap*	lsm;
		SScaleMap*	lsmNext;


		// Make sure the environment is sane
		if (tc)
		{
			// Lock the semaphore
			oss_lockSemaphore(tc->semRefresh);

			// Do we need to delete the scale maps?
			if (tc->firstScaleMap)
			{
				lsm = tc->firstScaleMap;
				while (lsm)
				{
					// Grab the next item
					lsmNext = (SScaleMap*)lsm->next;

					// Delete this map
					vvm_iDeleteScaleCompute(lsm);

					// Move to next one
					lsm = lsmNext;
				}
			}

			// Delete the allocated buffers
			if (tc->bd)			free(tc->bd);
			if (tc->bda)		free(tc->bda);
			if (tc->bd_vvmoss)	free((void*)tc->bd_vvmoss);

			// Release the semaphore
			oss_unlockSemaphore(tc->semRefresh);
			oss_deleteSemaphore(tc->semRefresh);

			// Free the canvas itself
			free(tc);

			// Indicate success
			return(0);

		} else {
			// Indicate failure
			return(-1);
		}
	}




//////////
//
// Requests a new screen of the specified width and height.  The returned id is passed
// to drawing algorithms to reference that screen.
//
// Returns:
//		SScreen* of new item
//			member ll.uniqueId	= vvm screenId
//			member ossWindowId	= oss id
//
//////
	SScreen* CALLTYPE oss_createScreenAndVisibleWindow(u64 tnAssociatedId, SOssWindow* tisw)
    {
		SScreen* ls;


		// Create the vvm screen
		ls = ioss_createScreen(tnAssociatedId);
		if (ls)
		{
			// Physically create the window
			ls->_iOssWindowId = oss_createVisibleWindow(tisw, ls->ll.uniqueId);
		}
		// Indicate success or failure
		return(ls);
    }




//////////
//
// Called to create a region for the indicated screen.  The region is automatically assigned a
// canvas since it is related to the screen
//
//////
	SRegion* CALLTYPE oss_createRegionForScreen(SScreen* ts, SCallbacks* callbacks, SStartEnd* events, SRegionState* trs)
	{
		SRegion*		lr;
		u32				lnWidth, lnHeight;
		SBGRA			lrgba;


		// Get the screen dimensions
		lr = NULL;
		if (oss_screenGetDimensions(ts->_iOssWindowId, NULL, NULL, &lnWidth, &lnHeight, NULL, NULL, NULL, NULL))
		{
			// Create a region
			lr = ioss_createRegion(ts->ll.uniqueId, trs, 0, 0.0f, 0.0f, (f32)lnWidth, (f32)lnHeight, callbacks, events);
			if (lr)
			{
				// Does this screen have an active region yet?
				if (!ts->activeRegion)
					ts->activeRegion = lr;		// Make it active

				// Create the associated canvas of the current size
				lrgba.color = rgba(255,255,255,255);
				lr->canvas	= ioss_createCanvas(lr->ll.uniqueId, lnWidth, lnHeight, lrgba);
			}
		}
		// Indicate our success or failure
		return(lr);
	}




//////////
//
// Creates a canvas of the appropriate size for the indicated screen
//
//////
	SCanvas* CALLTYPE oss_createCanvasForScreen(SScreen* ts)
	{
		u32		lnWidth, lnHeight;
		SBGRA	lrgba;


		// Get the screen dimensions
		if (ts && oss_screenGetDimensions(ts->_iOssWindowId, NULL, NULL, &lnWidth, &lnHeight, NULL, NULL, NULL, NULL))
		{
			lrgba.color = rgba(255,255,255,255);
			return(ioss_createCanvas(ts->ll.uniqueId, lnWidth, lnHeight, lrgba));
		}
		// Indicate our failure
		return(NULL);
	}




//////////
//
// Returns a new canvas of the specified dimension.
//
//////
	SCanvas* CALLTYPE oss_createCanvas(u64 tnAssociatedId, u32 tnWidth, u32 tnHeight, SBGRA tnBackColor)
    {
		SCanvas*		lc;


		// We create a canvas of the indicated size
		lc = ioss_createCanvas(tnAssociatedId, tnWidth, tnHeight, tnBackColor);

		// Since this is a VVM structure, we will return the SCanvas*
		return(lc);
		// See SCanvas->ll.uniqueId for id number
    }




//////////
//
// Returns a new region of the specified settings
//
//////
	SRegion* CALLTYPE oss_createRegion(u64 tnAssociatedId, u32 tnType, f32 ulx, f32 uly, f32 lrx, f32 lry, SCallbacks* callbacks, SStartEnd* events, SRegionState* trs)
	{
		SRegion* lr;


		// Try to create the region
		lr = ioss_createRegion(tnAssociatedId, trs, 0, ulx, uly, lrx, lry, callbacks, events);
		if (lr)
		{
			// Store the coordinates for this item
			lr->x = ulx;
			lr->y = uly;
			// Note:  It does not have a canvas, just dimensions
		}
		// Indicate our success or failure
		return(lr);
	}




//////////
//
// Called to create both a canvas and a region at the same time.
// Often a canvas is a drawn area that must respond to mouse and keyboard events over its entire
// area.  As such, a combined function is created to allow this creation in one shot.
//
//////
	bool CALLTYPE oss_createRegionAndCanvas(u64 tnAssociatedId, SBGRA tnBackColor, f32 ulx, f32 uly, f32 lrx, f32 lry, SCanvas** tc, SRegion** tr, SRegionState* regionState, SCallbacks* callbacks, SStartEnd* events)
	{
		SRegion*	lr;
		SCanvas*	lc;


		// Make sure our environment is sane
		if (tc && tr)
		{
			// Create our canvas
			lc	= oss_createCanvas(tnAssociatedId, (u32)ceil(lrx - ulx), (u32)ceil(lry - uly), tnBackColor);

			// Apply our region to it
			lr	= ioss_createRegion(tnAssociatedId, regionState, 0, ulx, uly, lrx, lry, callbacks, events);
			
			// Indicate our success or failure
			return(lc && lr);
		}
		// Indicate our failure
		return(false);
	}




//////////
//
// Returns an OSS-specific font handle that can be used for the CanvasWriteText() and
// CanvasWriteUnicode() functions, which use OSS-specific drawing algorithms to draw non-
// fixed point text onto the screen.
//
//////
	u64 CALLTYPE oss_createFontHandle(s8* fontName, u32 fontPointSize, bool bold, bool italics, bool underline, bool strikethrough)
    {
		return(oss_systemCreateFont(fontName, fontPointSize, bold, italics, underline, strikethrough));
    }




//////////
//
// Indicate a mouse event callback.
//
//////
	u64 CALLTYPE oss_screenMouseSetEventCallback(u64 id, SCanvas* tc, SEvent* event)
	{
		return(0);
	}




//////////
//
// Removes a mouse event.
//
//////
	u64 CALLTYPE oss_screenMouseRemoveEventCallback(u64 id, SCanvas* tc, SEvent* event)
	{
		return(0);
	}




//////////
//
// Obtains a list of all mouse events.
//
//////
	void CALLTYPE oss_screenMouseGetEventCallbacksList(u64 id, SCanvas* tc, SEvent** events, u32* count)
	{
	}




//////////
//
// Indicate a keyboard event callback.
//
//////
	u64 CALLTYPE oss_screenKeyboardSetEventCallback(u64 id, SCanvas* tc, SEvent* event)
	{
		return(0);
	}




//////////
//
// Removes a keyboard event.
//
//////
	u64 CALLTYPE oss_screenKeyboardRemoveEventCallback(u64 id, SCanvas* tc, SEvent* event)
	{
		return(0);
	}




//////////
//
// Obtains a list of all keyboard events.
//
//////
	void CALLTYPE oss_screenKeyboardGetEventCallbacksList(u64 id, SCanvas* tc, SEvent** events, u32* count)
	{
	}





//////////
//
// Searches through the list of known screens visible on the display at the present
// time by HWND, and returns a pointer to it if found.  NULL if not.
//
//////
	SOssWindowLL* CALLTYPE oss_findSOssWindowLLByHwnd(HWND hwnd)
	{
		SStartEndCallback cb;


		cb._func	= (u64)iioss_findSOssWindowLLByHwndCallback;
		cb.extra	= (u64)hwnd;
		return((SOssWindowLL*)vvm_SEChain_searchByCallback(&gseRootWindows, &cb));
	}




//////////
//
// Searches through the list of known screens visible on the display at the present
// time by screen id, and returns a pointer to it if found.  NULL if not.
//
//////
	SOssWindowLL* CALLTYPE oss_findSOssWindowLLByScreenId(u64 tnScreenId)
	{
		SStartEndCallback cb;


		cb._func	= (u64)iioss_findSOssWindowLLByScreenId;
		cb.extra	= (u64)tnScreenId;
		return((SOssWindowLL*)vvm_SEChain_searchByCallback(&gseRootWindows, &cb));
	}




//////////
//
// Callback from findScreenByOssWindowId() to locate the indicated SOssWindowLL structure by its
// ID, and not the actual SOssWindowLL->isw->ll.uniqueId for the actual internal screen structure
//
//////
	SOssWindowLL* CALLTYPE oss_find_iswSOssWindowLL_By_iOssWindowId(u64 tnOssWindowId)
	{
		SStartEndCallback cb;


		// Try to find it using the callback
		cb._func	= (u64)&iioss_findSOssWindowByOssWindowIdCallback;
		cb.extra	= tnOssWindowId;
		return((SOssWindowLL*)vvm_SEChain_searchByCallback(&gseRootWindows, &cb));
	}




//////////
//
// Loads the indicated bitmap file from disk.
// Supports 24-bit and 32-bit bitmaps in top-down, or bottom-up order.
//
// Returns:
//		>=0				- Success (indicates number of pixels allocated)
//		-1				- No 'BM' header
//		-2				- Planes wrong, must be 1
//		-3				- Bits must be 24 or 32
//		-4				- Unable to allocate memory for bits
//		-5				- Unable to read file
//		-6				- Offset to bits in header not correct
//		-7				- Unable to allocate memory for internal SBGRA bits
//		-8				- Unable to open pathname
//		Our return values:
//		-50				- Invalid parameters
//
//////
	u64 CALLTYPE oss_bitmapLoadFromDisk(s8* tcPathname, SCanvas** tc, u32* tnWidth, u32* tnHeight, SBGRA tnBackColor)
	{
		bool			llLoadResult;
		u32				lnResult;
		SBitmapHeader	lbh;		// Header
		SBitmapInfo		lbi;		// Info
		s8*				lbd;		// Data
		SCanvas*		lc;			// Newly created canvas
		SBGRA*			lrgbad;		// Destination is always 32-bit


// TODO:  Someone needs to test this with different bitmap formats from different sources, 24-bit and 32-bit
// TODO:  verify that this function is working properly by loading and bitBlting the converted SBGRA buffer onto a canvas
		// Make sure the environment is sane
		lnResult = 0;
		if (tcPathname && tc)
		{
			llLoadResult = ioss_openAndReadBitmapFile(tcPathname, &lbh, &lbi, &lbd, &lnResult);
			while (llLoadResult)
			{
				// Store the width and height
				if (tnWidth)	*tnWidth	= lbi.width;
				if (tnHeight)	*tnHeight	= lbi.height;

				// Allocate our canvas
				lc = oss_createCanvas(0, lbi.width, lbi.height, tnBackColor);

				// Update their pointer if they want
				if (tc)
					*tc = lc;

				// If it's all valid, copy it over
				if (lc && lc->bd && lc->bda)
				{
					// Based on file size, process it appropriately
					if (lbi.bitCount == 24)
					{
						// We have a 24-bit bitmap, which can either be top-down or bottom-up
						// Copy the actual width
						lbi.actualWidth = ioss_computeActualWidth(lbi.width);

						// See which one it is, and then reverse it
						if ((s32)lbi.height < 0)
						{
							// It's stored in top-down order
							lbi.height = (u32)((s32)lbi.height * -1);
							ioss_allocateSBGRAandCopy24Bit_BitmapTopDown(&lrgbad, &lbh, &lbi, (SRGB*)lbd, &lnResult, -7);

						} else {
							// It's stored in bottom-up order
							ioss_allocateSBGRAandCopy24Bit_BitmapBottomUp(&lrgbad, &lbh, &lbi, (SRGB*)lbd, &lnResult, -7);
						}

					} else {
						// It's a 32-bit bitmap
						if ((s32)lbi.height < 0)
						{
							// It's stored in top-down order
							lbi.height = (u32)((s32)lbi.height * -1);
							ioss_allocateSBGRAandCopy32Bit_BitmapTopDown(&lrgbad, &lbh, &lbi, (SBGRA*)lbd, &lnResult, -7);

						} else {
							// It's stored in bottom-up order
							ioss_allocateSBGRAandCopy32Bit_BitmapBottomUp(&lrgbad, &lbh, &lbi, (SBGRA*)lbd, &lnResult, -7);
						}
					}
					// When we get here, we will have loaded the bitmap and copied it from its native format to the indicated SBGRA structure
					// Copy the temporary SBGRA of the loaded image to the new canvas we've created
					memcpy(lc->bd,  lrgbad, lbi.height * lbi.width * sizeof(SBGRA));
					memcpy(lc->bda, lrgbad, lbi.height * lbi.width * sizeof(SBGRA));

					// Release our temporary SBGRA buffer
					free(lrgbad);
				}
				// Once we get here we have everything we need
				// Release our allocated memory for bits from disk
				free(lbd);

				// Unconditional break here
				break;
			}

		} else {
			// The user provided invalid parameters
			lnResult = -50;
		}

		// Indicate our success or failure
		return(lnResult);
	}




//////////
//
// Saves the indicated canvas to disk
//
//////
	u64 CALLTYPE oss_bitmapSaveToDisk(SCanvas* tc, SBGRA* bd, s8* tcPathname)
	{
		u64				lnResult, lnHandle, lnNumread;
		SBitmapHeader	lbh;		// Header
		SBitmapInfo		lbi;		// Info


		// Make sure the environment is sane
		lnResult = -1;
		if (tc && bd && tcPathname)
		{
			// Create the file
			lnHandle = oss_sharedAsciiOpenFile(tcPathname, true, false, false, false, false, true, false, false);
			if (lnHandle > 0)
			{
				// Create a bitmap header
				memset(&lbh, 0, sizeof(lbh));
				memset(&lbi, 0, sizeof(lbi));

				// Update the info
				lbi.sizeOfInfoBlock		= sizeof(lbi);
				lbi.bitCount			= 32;
				lbi.planes				= 1;
				lbi.height				= -(s32)tc->height;
				lbi.width				= tc->width;
				lbi.ppmX				= 3270;
				lbi.ppmY				= 3270;
				lbi.sizeOfImage			= tc->height * tc->width * sizeof(SBGRA);

				// Update the disk header
				lbh.type				= 'MB';
				lbh.offsetToBits		= sizeof(lbh) + sizeof(lbi);
				lbh.size				= lbi.sizeOfImage + lbh.offsetToBits;

				// Write the header
				lnNumread = oss_sharedAsciiWriteFile(lnHandle, (s8*)&lbh, sizeof(lbh));
				if (lnNumread == sizeof(lbh))
				{
					// Write the info
					lnNumread = oss_sharedAsciiWriteFile(lnHandle, (s8*)&lbi, sizeof(lbi));
					if (lnNumread == sizeof(lbi))
					{
						// write the bits
						// Swap the bits for the write to disk
						lnNumread	= oss_sharedAsciiWriteFile(lnHandle, (s8*)bd, lbi.sizeOfImage);
						if (lnNumread == lbi.sizeOfImage)
						{
							// We're good, a successful bitmap was written
							lnResult = 0;
						}
					}
				}
				// When we get here, regardless of success, we close the file
				oss_sharedAsciiCloseFile(lnHandle);
			}
		}
		// Indicate the status
		return(lnResult);
	}




//////////
//
// Request a system font based on the name, size and attributes provided.  The OS will fallback
// to the closest matching font if the explicitly named font is not available.
//
// Returns:
//		pointer to _isWSSystemFont structure (the Start/end structure)
//		Note:  use _isWSSystemFont->handle for HFONT
//
//////
	u64 CALLTYPE oss_systemCreateFont(s8* fontName, u32 fontPointSize, bool bold, bool italics, bool underline, bool strikethrough)
	{
		u64					lnUniqueId;
		s32					lnHeight;
		HFONT				lf;
		_iswSSystemFont*	lsf;


		// Convert point size to font height parameters
		lnHeight	= -MulDiv(fontPointSize, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);

		// Try to allocate the font
		lnUniqueId	= 0;
		lsf			= NULL;
		lf			= CreateFontA(lnHeight, 0, 0, 0, (bold) ? FW_BOLD :  FW_NORMAL, italics, underline, strikethrough, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, fontName);
		if (lf)
		{
			// Append it to our start/end list
			lsf = (_iswSSystemFont*)vvm_SEChain_append(&gseRootFonts, 0, vvm_getNextUniqueId(), sizeof(_iswSSystemFont), _COMMON_START_END_BLOCK_SIZE, NULL);
			if (lsf)
			{
				// Prepare our structure
				lnUniqueId			= vvm_getNextUniqueId();

				// Store the identifier into
				lsf->ll.uniqueId	= lnUniqueId;
				lsf->handle			= lf;

				// Store the font's attributes
				lsf->fontName		= (s8*)vvm_duplicateString((u8*)fontName, max(strlen(fontName), 128));
				lsf->fontPointSize	= fontPointSize;
				lsf->bold			= bold;
				lsf->italics		= italics;
				lsf->underline		= underline;
				lsf->strikethrough	= strikethrough;
				// When we get here, we have our list
			}
		}
		// Return the identifier in the start/end chain for reference
		return((u64)lsf);
	}




//////////
//
// Request a system bitmap based on the width and height.  This will be a DIB that can be used
// primarily for drawing text onto, and then copying back out to SBGRA buffers.
//
// Returns:
//		pointer to _isWSystemBitmap (the Start/end structure)
//		Note:  This should not be used directly outside of oss_code.  Pass the returned 64-bit value to oss code for processing.
//		Note:  use _isWSystemBitmap->bdRoot
//		           _isWSystemBitmap->width
//		           _isWSystemBitmap->height
//
//////
	u64 CALLTYPE oss_systemCreateBitmap(u32 tnWidth, u32 tnHeight)
	{
		_iswSSystemBitmap*	lsb;


		// Allocate our the system bitmap they're requesting
		lsb = (_iswSSystemBitmap*)malloc(sizeof(_iswSSystemBitmap));
		if (lsb)
		{
			// Create our new DC and bitmap
			lsb->hdc		= CreateCompatibleDC(GetDC(GetDesktopWindow()));
			lsb->hbmp		= (HBITMAP)ioss_createDibWithBitBuffer(lsb->hdc, tnWidth, tnHeight, &lsb->bi, &lsb->bd, &lsb->actualWidth);
			lsb->width		= lsb->bi.bmiHeader.biWidth;
			lsb->height		= lsb->bi.bmiHeader.biHeight;

			// Associate the bitmap with the device context
			SelectObject(lsb->hdc, lsb->hbmp);
		}
		return((u64)lsb);
	}




//////////
//
// Searches the start/end structure for the indicated font handle
// Note:  AT this point, the fontHandle is actually a uniqueID into the fontRoot start/end structure
//
// Returns:
//		0			- Not found
//		others		- HFONT
//
//////
	u64 CALLTYPE oss_systemFindFontByHandle(u64 tnFontHandle)
	{
		_iswSSystemFont*	lsf;
		SStartEndCallback	cb;



// UNTESTED CODE:  breakpoint and examine
		// Find the indicated font by its uniqueId, which the systems uses as its handle between VVM and VVMOSS
		cb._func	= (u64)&iioss_findSystemFontByHandleCallback;
		cb.extra	= tnFontHandle;
		lsf = (_iswSSystemFont*)vvm_SEChain_searchByCallback(&gseRootFonts, &cb);

		// Based on return result, indicate our handle or failure
		if (lsf)	return((u64)lsf->handle);		// Return the HFONT for immediate use by caller
		else		return(NULL);					// Failure
	}




//////////
//
// Create the specified screen structure
//
//////
	SOssWindow* CALLTYPE oss_screenCreateTemplate(u64 id, u64 uniqueScreenId,
													 s8* tcCaption, u32 tnCaptionLength,
													 s32 tnX, s32 tnY,
													 u32 tnWidth, u32 tnHeight,
													 u32 tnWidthMin, u32 tnHeightMin,
													 u32 tnWidthMax, u32 tnHeightMax,
													 u32 ncUlx, u32 ncUly, u32 ncLrx, u32 ncLry, u32 ncBorder,
													 SBGRA tnForeColor, SBGRA tnBackColor,
													 bool tlResizable, bool tlMovable, bool tlClosable, bool tlVisible, bool tlBorder,
													 SCallbacksW* callbacks)
	{
		SOssWindow*	tisw;


		// Allocate the new screen structure
		tisw = (SOssWindow*)malloc(sizeof(SOssWindow));
		if (tisw)
		{
			// Initialize it to 0
			memset(tisw, 0, sizeof(SOssWindow));

			// Populate it
			tisw->uniqueId			= uniqueScreenId;

			// Set the length if necessary
			if (tnCaptionLength == -1)
				tnCaptionLength = (u32)vvm_scanForwardUntilCharacter(_csu8p(tcCaption), 0);

			// Visible identifier
			tisw->caption			= (s8*)vvm_duplicateString((u8*)tcCaption, tnCaptionLength + 1);
			tisw->captionLength		= tnCaptionLength;

			// Position
			tisw->osX				= tnX;
			tisw->osY				= tnY;
			tisw->width				= tnWidth;
			tisw->height			= tnHeight;
			tisw->widthMin			= tnWidthMin;
			tisw->heightMin			= tnHeightMin;
			tisw->widthMax			= tnWidthMax;
			tisw->heightMax			= tnHeightMax;

			// Non-client portions
			tisw->ncUlX				= ncUlx;
			tisw->ncUlY				= ncUly;
			tisw->ncLrX				= ncLrx;
			tisw->ncLrY				= ncLry;
			tisw->ncBorder			= ncBorder;

			// Colors
			tisw->foreColor			= tnForeColor;
			tisw->backColor			= tnBackColor;

			// Flags
			tisw->resizable			= tlResizable;
			tisw->movable			= tlMovable;
			tisw->closable			= tlClosable;
			tisw->visible			= tlVisible;
			tisw->border			= tlBorder;

			// Callbacks
			if (callbacks)
				memcpy(&tisw->callback, callbacks, sizeof(tisw->callback));
		}
		// When we get here, we're done
		return(tisw);
	}




//////////
//
// Called to determine how big a screen should be to fit on the indicated monitor
//
//////
	void CALLTYPE oss_screenComputeMonitorCoordinates(SOssWindow* tow, f32 tfPercent, u32 tnPosition, f32 tfMargin, s32* tnX, s32* tnY, u32* tnWidth, u32* tnHeight, u32* tnWidthMax, u32* tnHeightMax, u32* tnWidthMin, u32* tnHeightMin)
	{
		bool		llDelete;
		f32			lfX, lfY, lfWidth, lfHeight, lfMarginX, lfMarginY;
		SStartEnd	lse;


		////////////
		// Do we have a monitor to use?
		//////
			if (!tow)
			{
				// Nope, we have to get our own
				memset(&lse, 0, sizeof(lse));
				llDelete	= true;
				tow			= oss_screenEnumerateMonitors(&lse);

			} else {
				// We do not need to delete the SStartEnd chain
				llDelete	= false;
			}


		//////////
		// Adjust percentages into the 0..1 range
		//////
			if (tfPercent > 1.0f)	tfPercent = tfPercent / 100.0f;
			if (tfMargin > 1.0f)	tfMargin  = tfMargin / 100.0f;

			// Verify they're in the 0..1 range
			if (tfPercent < 0.0f)	tfPercent = 0.0f;
			if (tfPercent > 1.0f)	tfPercent = 1.0f;
			if (tfMargin < 0.0f)	tfMargin  = 0.0f;
			if (tfMargin > 1.0f)	tfMargin  = 1.0f;


		//////////
		// Determine the size
		//////
			lfWidth		= (f32)tow->width	* tfPercent;
			lfHeight	= (f32)tow->height	* tfPercent;
			lfMarginX	= (f32)tow->width	* tfMargin;
			lfMarginY	= (f32)tow->height	* tfMargin;


		//////////
		// Determine its position
		//////
			switch (tnPosition)
			{
				default:
				case _VVMOSS_SCREEN_UPPER_LEFT:
					lfX = lfMarginX;
					lfY = lfMarginY;
					break;

				case _VVMOSS_SCREEN_UPPER_RIGHT:
					lfX = (f32)tow->width - lfMarginX - lfWidth;
					lfY = tfMargin;
					break;

				case _VVMOSS_SCREEN_LOWER_LEFT:
					lfX = tfMargin;
					lfY = (f32)tow->height - lfMarginY - lfHeight;
					break;

				case _VVMOSS_SCREEN_LOWER_RIGHT:
					lfX = (f32)tow->width - lfMarginX - lfWidth;
					lfY = (f32)tow->height - lfMarginY - lfHeight;
					break;

				case _VVMOSS_SCREEN_CENTER:
					lfX = ((f32)tow->width  - lfWidth)  / 2.0f;
					lfY = ((f32)tow->height - lfHeight) / 2.0f;
					break;
			}


		//////////
		// Convert to the components they want
		//////
			if (tnX)				*tnX			= (s32)lfX;
			if (tnY)				*tnY			= (s32)lfY;
			if (tnWidth)			*tnWidth		= (u32)lfWidth;
			if (tnHeight)			*tnHeight		= (u32)lfHeight;
			if (tnWidthMax)			*tnWidthMax		= (u32)lfWidth;
			if (tnHeightMax)		*tnHeightMax	= (u32)lfHeight;
			if (tnWidthMin)			*tnWidthMin		= (u32)lfWidth;
			if (tnHeightMin)		*tnHeightMin	= (u32)lfHeight;


		//////////
		// Clean up
		//////
			if (llDelete)
			{
				// We need to delete our list of monitors
				vvm_SEChain_delete(&lse, NULL, 0, true);
			}
	}




//////////
//
// Called to enumerate the monitors available to the VVMOSS.  The left-most monitor is conveyed
// as the coordinate 0,0, and every other monitor is relative to that location.  By computing the
// deltas based upon width and height of each monitor, a map can be created.
//
// Note:  Returns the SOssWindow* structure, one for each monitor, in the SStartEnd.
//
//////
	SOssWindow* CALLTYPE oss_screenEnumerateMonitors(SStartEnd* tsMonitors)
	{
		SOssWindow*			low;
		SStartEndCallback	cb;


		// Make sure our environment is sane
		if (tsMonitors)
		{
			// Ask Windows to please send us a response for each monitor
			EnumDisplayMonitors(NULL, NULL, iioss_enumerateMonitors, (LPARAM)tsMonitors);

			low			= NULL;
			cb._func	= (u64)&iioss_enumerateMonitorsIterateCallback;
			cb.extra	= (u64)&low;

			// Iterate through each and find the largest 
			vvm_SEChain_iterateThroughForCallback(tsMonitors, &cb);

			// Return the largest monitor
			return(low);

		} else {
			// Indicate failure
			return(NULL);
		}
	}




//////////
//
// Return dimensions for the indicated screen (if found)
//
//////
	bool CALLTYPE oss_screenGetDimensions(u64 tnOssWindowId, s32* tnX, s32* tnY, u32* tnWidth, u32* tnHeight, u32* tnWidthMax, u32* tnHeightMax, u32* tnWidthMin, u32* tnHeightMin)
	{
		SOssWindowLL* low;


		// Make sure the screen they indicated is valid
		low = oss_find_iswSOssWindowLL_By_iOssWindowId(tnOssWindowId);
		if (low)
		{
			// Update the dimensions
			if (tnX)			*tnX			= low->isw.osX;
			if (tnY)			*tnY			= low->isw.osY;
			if (tnWidth)		*tnWidth		= low->isw.width;
			if (tnHeight)		*tnHeight		= low->isw.height;
			if (tnWidthMax)		*tnWidthMax		= low->isw.widthMax;
			if (tnHeightMax)	*tnHeightMax	= low->isw.heightMax;
			if (tnWidthMin)		*tnWidthMin		= low->isw.widthMin;
			if (tnHeightMin)	*tnHeightMin	= low->isw.heightMin;
			return(true);
		}
		// The window wasn't found
		return(false);
	}




//////////
//
// Blt the specified buffer onto the indicated operating-system specific screen id
//
//////
	u64 CALLTYPE oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb(u64 tnOssWindowId, SBGRA* bd, u32 width, u32 height)
	{
		SOssWindowLL* w;


		// Make sure the screen they indicated is valid
		w = oss_find_iswSOssWindowLL_By_iOssWindowId(tnOssWindowId);
		if (w)
		{
			// Copy over the buffer contents, as much as will fit (should be all of it)
			return(ioss_lowLevel_bitBlt_Sgra_onto_ossWindow(w, bd, width, height));

		} else {
			// Indicate failure
			return(-1);
		}
	}




//////////
//
// Blts the specified OSS buffer onto the indicated SBGRA using the tnX,tnY coordinates for the
// upper-left, for the width and the height.  This function is used for things that the OS itself
// renders into a bit bucket, which is then copied into our buffer.
//
//////
	u64 CALLTYPE oss_lowLevel_bitBlt_ossRgb_onto_canvasBgra(u64 bdoss, s32 tnX, s32 tnY, u32 tnWidth, u32 tnHeight, SCanvas* tc, SBGRA* bd)
	{
		u64					lnPixels;
		s32					lnY, lnX, lnThisY, lnThisX;
		_iswSSystemBitmap*	lsb;
		SRGB*				lrgbs;
		SBGRA*				lrgbad;


// TODO:  (an optimization) could make the code below look for blocks which exist in the destination, and only iterate across those ranges
// Working here, copy out the DIB section bitmap rectangle to the SBGRA buffer
		lnPixels	= 0;
		lsb			= (_iswSSystemBitmap*)bdoss;
		for (	lnY = 0, lnThisY = tnY;
				lnY < (s32)tnHeight;
				lnY++, lnThisY++	)
		{
			// Is this a row to process?
			if (lnThisY >= 0 && lnThisY < (s32)lsb->height && lnThisY < (s32)tc->height)
			{
				// Set our source and destination pointers
				lrgbs	= (SRGB*)( (s8*)lsb->bd + ((lsb->height - (lnY + tnY) - 1) * lsb->actualWidth)  + (tnX * sizeof(SRGB)));
				lrgbad	= bd + ((lnY + tnY) * tc->width) + tnX;

				// Repeat for every valid pixel
				for (	lnX = 0, lnThisX = tnX;
						lnX < (s32)tnWidth; 
						lnX++, lnThisX++	)
				{
					// Make sure this is one to copy
					if (lnThisX >= 0 && lnThisX < (s32)tc->width)
					{
						// Copy this pixel
						lrgbad->red = lrgbs->red;
						lrgbad->grn = lrgbs->grn;
						lrgbad->blu = lrgbs->blu;
						lrgbad->alp = 255;
						// Update our count
						++lnPixels;
					}

					// Move to next pixel
					++lrgbs;
					++lrgbad;
				}
			}
		}
		// Indicate what we did
		return(lnPixels);
	}




//////////
//
// Grab the next waiting message
//
//////
	u64 CALLTYPE oss_getNextMessage(u32* message, void* extra)
	{
// TODO:  this code needs written
		return(0);
	}




//////////
//
// Display a message box.
// Valid button groupings are:
//		Yes, No, Cancel
//		Yes, No
//		Retry,  Cancel
//		Ok, Cancel
//		Ok
//
//////
	u64 CALLTYPE oss_messageBox(u64 id, s8* tcText, s8* tcCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel)
	{
		u32 lnButtons;


		// See what we should display
		if (tlYes && tlNo && tlCancel)	lnButtons = MB_YESNOCANCEL;
		else if (tlYes && tlNo)			lnButtons = MB_YESNO;
		else if (tlRetry && tlCancel)	lnButtons = MB_RETRYCANCEL;
		else if (tlOk && tlCancel)		lnButtons = MB_OKCANCEL;
		else							lnButtons = MB_OK;

		// Display it and return their result
		return(MessageBoxA(NULL, tcText, tcCaption, lnButtons));
	}

	// Unicode variety
	u64 CALLTYPE oss_messageBoxUnicode(u64 id, w16* tuText, w16* tuCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel)
	{
		u32 lnButtons;


		// See what we should display
		if (tlYes && tlNo && tlCancel)	lnButtons = MB_YESNOCANCEL;
		else if (tlYes && tlNo)			lnButtons = MB_YESNO;
		else if (tlRetry && tlCancel)	lnButtons = MB_RETRYCANCEL;
		else if (tlOk && tlCancel)		lnButtons = MB_OKCANCEL;
		else							lnButtons = MB_OK;

		// Display it and return their result
		return(MessageBoxW(NULL, tuText, tuCaption, lnButtons));
	}




//////////
//
// Called to draw some text in the indicated font onto the indicated dib bitmap
//
// Note:  tnSystemFont and tnSystemBitmap are _isWSystem* structures
//
//////
	u64 CALLTYPE oss_drawText(s8* tcText, u32 tnTextLength, s32 ulx, s32 uly, s32 lrx, s32 lry, SBGRA foreground, SBGRA background, u64 tnSystemFont, u64 tnSystemBitmap)
	{
		u32					lnCount, lnFormat, lnForeColor, lnBackColor;
		RECT				lrc;
		HBRUSH				lhBrush;
		_iswSSystemBitmap*	lsb;
		_iswSSystemFont*	lsf;


		// Make sure there's something to do
		lnCount = 0;
		if (tcText && tnTextLength != 0)
		{
			// Convert the passed u64 values to their proper structure
			lsb	= (_iswSSystemBitmap*)tnSystemBitmap;
			lsf	= (_iswSSystemFont*)tnSystemFont;

			// Load our font
			SelectObject(lsb->hdc, (HGDIOBJ)lsf->handle);

			// Prepare our text info
			lnForeColor = foreground.color;
			lnBackColor = background.color;
			SetTextColor(lsb->hdc, lnForeColor);
			SetBkColor	(lsb->hdc, lnBackColor);
			SetBkMode	(lsb->hdc, OPAQUE);

			// Get our initial condition
			lnFormat = DT_LEFT | DT_END_ELLIPSIS;

			// Set our rectangle
			SetRect(&lrc, ulx, uly, lrx, lry);

			// Fill the rectangle with the explicit opaque color
			lhBrush = CreateSolidBrush(lnBackColor);
			FillRect(lsb->hdc, &lrc, lhBrush);
			DeleteObject((HGDIOBJ)lhBrush);

			// Physically draw it
			if (DrawTextA(lsb->hdc, tcText, tnTextLength, &lrc, lnFormat) != 0)
				lnCount = tnTextLength;
		}
		// Return the number of characters we copied
		return(lnCount);
	}




//////////
//
// Called to allocate a block of memory which must persist upon termination of the VVM.
//
//////
	void* CALLTYPE oss_alloc(u64 tnSize, bool tlInitialize)
	{
		s8* ptr;
//		SDatumLL* ldll;


		// Make sure our environment's sane
// TODO:  (future enhancement) make this a true 64-bit alloc
		if (tnSize == 0 || tnSize > 0xffffffff)
			return(NULL);


// 		// Append it to the list of memory blocks we have
// 		ldll = (SDatumLL*)vvm_SEChain_append(&gseRootMemoryBlocks, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SDatumLL), _COMMON_START_END_BLOCK_SIZE, NULL);
// 		if (ldll)
// 		{
// 			// Allocate this datum's data.  Think through that a few times... :-)
// 			ldll->datum.data._s8 = (s8*)malloc((u32)tnSize);
// 			if (ldll->datum.data._s8)
// 			{
// 				// Success!
// 				ldll->datum.length = tnSize;
// 
// 				// Initialize to NULLs
// 				if (tlInitialize)
// 					vvm_memset(ldll->datum.data._s8, 0, tnSize);
// 
// 				// Indicate our success
// 				return(ldll->datum.data._v);
// 			}
// 			// Failure!
// 			vvm_SEChain_deleteFrom(&gseRootMemoryBlocks, (SLL*)ldll, true);
// 		}
		ptr = (s8*)malloc((u32)tnSize);
		if (ptr && tlInitialize)
			memset(ptr, 0, (u32)tnSize);

		// Indicate failure
		return(ptr);
	}




//////////
//
// Resizes a previously allocated block of memory using oss_alloc()
//
//////
	void* CALLTYPE oss_realloc(void* ptrOld, u64 tnNewSize)
	{
		void*				txPtrNew;
// 		SDatumLL*			ldll;
// 		SStartEndCallback	cb;



		// Make sure the environment's sane
// TODO:  (future enhancement) make this a true 64-bit realloc
		if (!ptrOld || tnNewSize == 0 || tnNewSize > 0xffffffff)
			return(NULL);


// 		// Locate the existing master list pointer
// 		cb._func	= (u64)iioss_reallocAndFreeCallback;
// 		cb.extra	= (u64)ptrOld;
// 		ldll = (SDatumLL*)vvm_SEChain_searchByCallback(&gseRootMemoryBlocks, &cb);
// 		if (!ldll)
// 			return(NULL);		// It's not one of our pointers, tisk, tisk!


		// Attempt the resize
		txPtrNew = realloc(ptrOld, (u32)tnNewSize);
		if (txPtrNew)
		{
			// It worked
			// Update the entry in the associated structure
// 			ldll->datum.data._s8	= (s8*)txPtrNew;
// 			ldll->datum.length		= tnNewSize;
		}
		// Indicate failure or success
		return(txPtrNew);
	}




//////////
//
// Releases a previously allocated block of memory using oss_alloc() or oss_realloc()
//
// Returns:
//		-1		- error
//		0		- success
//
//////
	void* CALLTYPE oss_free(void* ptr)
	{
		SDatumLL*			ldll;
		SStartEndCallback	cb;


		// Make sure the environment's sane
		if (!ptr)
			return((void*)-1);		// Uhhh.... no.


		// Locate the existing master list pointer
		cb._func	= (u64)iioss_reallocAndFreeCallback;
		cb.extra	= (u64)ptr;
		ldll = (SDatumLL*)vvm_SEChain_searchByCallback(&gseRootMemoryBlocks, &cb);
		if (!ldll)
			return(NULL);		// It's not one of our pointers, tisk, tisk!


		// Free the memory
		free(ptr);


		// Delete its associated entry in the chain
		vvm_SEChain_deleteFrom(&gseRootMemoryBlocks, (SLL*)ldll, true);


		// Indicate success
		return((void*)0);
	}




//////////
//
// The oss_sound* functions within the VVMOSS are stubs.  They require drives to be loaded at startup.
//
//////////
	//
	// See:		common_vvmoss_plugins.h
	//			vo_plugins.h
	//			vo_plugins.cpp
	//////




//////////
//
// Called to parse the indicated block of text data.  It converts every combination of an ASCII-13,
// ASCII-10, or groupings in any order of ASCII-13+ASCII-10 into end-of-line entries.
//
// Returns:
//		NULL	- error
//		Pointer to the first SOssLine entry
//		Note:  Every reference in SOssLine points to a location within tcData, so if tcData is freed, then all references are lost
//
//////
	u64 CALLTYPE oss_breakoutAsciiTextIntoSOssLines(s8* tcData, u64 tnFileSize, SStartEnd* tseLines, u64 tnAllocSize, bool tlUseOssAlloc)
	{
		u64			lnOffset, lnTotalLineLength, lnLineCount;
		SOssLine*	linePrev;
		SOssLine*	line;


		// Make sure our environment is sane
		lnLineCount = 0;
		if (tcData && tnFileSize != 0 && tnAllocSize <= 0xffffffff)
		{
			// Initialize our variables
			lnOffset	= 0;
			lnLineCount	= 0;
			linePrev	= NULL;
			goto storeFirstOne;

			// Iterate through every byte of the source data until all lines are broken out
			while (line && lnOffset < tnFileSize)
			{
				// Mark the start of this line
				lnTotalLineLength	= ioss_breakoutAsciiTextDataIntoLines_ScanLine(tcData + lnOffset, tnFileSize - lnOffset, &line->length, &line->whitespace);

				// Make sure we still have more to go
				lnOffset += lnTotalLineLength;
				if (lnOffset <= tnFileSize)
				{
					// Create the next line
					linePrev = line;

storeFirstOne:
					//////////
					// Allocate this entry
					///////
						line = (SOssLine*)vvm_SEChain_append(tseLines, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SOssLine), _COMMON_START_END_BLOCK_SIZE, NULL);


					//////////
					// Populate the line with specified information
					//////
						//
						//////
							if (line)
							{
								// Update our link lists
								if (linePrev)		linePrev->ll.next	= (SLL*)line;
								line->ll.prev		= (SLL*)linePrev;

								// Indicate where this next line will/would start
								line->start			= lnOffset;
								line->base			= tcData;
								line->lineNumber	= lnLineCount + 1;						// Store the number as base-1, not base-0

								// Allocate the extra block if we have one to do
								if (tnAllocSize != 0)
								{
									// Allocate the memory block for this extra associated item
									if (tlUseOssAlloc)		line->extra = oss_alloc(tnAllocSize, false);
									else					line->extra = malloc((u32)tnAllocSize);

									// Initialize it to its empty state
									if (line->extra)		vvm_memset((s8*)line->extra, 0, tnAllocSize);
								}

								// Increase our line count
								++lnLineCount;
							}
						//////
						//
					//////
					// END
					//////////
				}
			}
			// IF we get here, failure
		}
		// If we get here, we do not have any lines
		return(lnLineCount);
	}




//////////
//
// Called to search the SAsciiCompSearcher format list of text item keywords.
//
// Note:  If the length column of the SAsciiCompSearcher entry is negative, it is a case-sensitive search.
//
// Returns:
//		The first component created (if any)
//
//////
	SOssComp* CALLTYPE oss_translateSOssLinesToSOssComps(SAsciiCompSearcher* tsComps, SOssLine* line)
	{
		s64						lnI, lnMaxLength, lnStart, lnLength, lnLacsLength;
		bool					llSigned, llResult;
		SOssComp*				compFirst;
		SOssComp*				compLast;
		SOssComp*				comp;
		s8*						lcData;
		SAsciiCompSearcher*		lacs;
		SOssCompCallback		lccb;


		// Make sure the environment's sane
		compFirst = NULL;
		if (tsComps && line)
		{
			// Scan starting at the beginning of the line
			lcData = line->base + line->start + line->whitespace;

			// Iterate through every byte identifying every component we can
			compLast	= NULL;
			lnMaxLength	= line->length;
			for (lnI = 0; lnI < lnMaxLength; )
			{
				// Search through the tsComps list one by one
				for (	lacs = tsComps;
						lacs->length != 0;
						lacs++)
				{
					// Find out our signed status and get normalized length
					llSigned		= (lacs->length < 0);
					lnLacsLength	= abs(lacs->length);

					// Process through this entry
					if ((!lacs->firstOnLine || lnI == 0) && lnLacsLength <= lnMaxLength - lnI)
					{
						// There is enough room for this component to be examined
						// See if it matches
						if (ioss_translateSOssLinesToSOssCompsTest((s8*)lacs->keyword, lcData + lnI, lacs->length) == 0)
						{
							// It matches
							// Is there a secondary validation?
							if (lacs->_validate)
							{
								// Yes, make sure it validates there as well
								lccb.text					= lcData + lnI;
								lccb.length					= lacs->length;
								lccb.iCode					= lacs->iCode;
								lccb._insertCompByComp		= NULL;
								lccb._insertCompByParams	= NULL;
								lccb._deleteComps			= NULL;
								lccb._cloneComps			= NULL;
								lccb._mergeComps			= NULL;

								// Perform the validation
								llResult = lacs->validate(&lccb);

							} else {
								// If there is no extra validation, we just pass through
								llResult = true;
							}
							
							// Are we still good?
							if (llResult)
							{
								// mark its current condition
								lnStart		= lnI;
								lnLength	= lnLacsLength;
								// See if it's allowed to repeat
								if (lacs->repeats)
								{
									while (	lnStart + lnLength + lnLacsLength <= lnMaxLength
											&& ioss_translateSOssLinesToSOssCompsTest((s8*)lacs->keyword, lcData + lnStart + lnLength, lacs->length) == 0)
									{
										// We found another repeated entry
										lnLength += lnLacsLength;
									}
									// When we get here, every repeated entry has been found (if any)
								}
								// When we get here, we have the starting point and the full length (including any repeats)


								//////////
								// Allocate this entry
								///////
									comp = (SOssComp*)vvm_SEChain_append(&line->comps, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SOssComp), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);


								//////////
								// Populate the component with specified information
								//////
									//
									//////
										if (comp)
										{
											// Update the back links
											if (compLast)	compLast->ll.next = (SLL*)comp;			// Previous one points to this one
											comp->ll.prev	= (SLL*)compLast;						// This one points back to previous one

											// Update the component's information
											comp->line		= line;
											comp->start		= lnStart;
											comp->length	= lnLength;
											comp->iCode		= lacs->iCode;

											// Update our first component (if it's not updated already)
											if (!compFirst)	compFirst = comp;

											// All done
											compLast = comp;
										}
									//////
									//
								//////
								// END
								//////////


								//////////
								// Move beyond this entry, and continue on search again afterward
								//////
									lnI += lnLength;
									break;		// leaves lnJ loop, continues with lnI loop
							}
						}
						//else it doesn't match, this isn't a good find
					}
				}
				// When we get here, we've processed through everything here
				if (lacs->length == 0)
					lnI++;			// We didn't find anything at that character, continue on to the next
			}
			// When we get here, lnI has been updated to its new location,
			// and any indicated components have been added
		}
		// Return the count
		return(compFirst);
	}




//////////
//
// Called to search the already parsed SAsciiCompSearcher list of components, looking for
// combinations which relate to other component types.  The primary translations here are
// alpha/alphanumeric/numeric forms to other forms.
//
//////
	void CALLTYPE oss_translateSOssCompsToOthers(SAsciiCompSearcher* tsComps, SOssLine* line)
	{
		SStartEndCallback cb;


		cb._func	= (u64)iioss_translateSOssCompsToOthersCallback;
		cb.extra	= (u64)tsComps;
		vvm_SEChain_searchByCallback(&line->comps, &cb);
	}




//////////
//
// Called to write the SOssLine structure to a disk file
//
//////
	u64 CALLTYPE oss_writeSOssLineSequenceToDisk(s8* tcPathname, SStartEnd* tseLines)
	{
		u64			lnI, lnBytesWritten;
		s64			lnHandle;
		SOssLine*	line;


		// Attempt to open the indicated file
		lnBytesWritten	= 0;
		lnHandle		= oss_sharedAsciiOpenFile(tcPathname, true, false, true, true, false, true, true, false);
		if (lnHandle >= 0)
		{
			line = (SOssLine*)tseLines->root->ptr;
			while (line)
			{
				// Write this line
				// Write any whitespaces as spaces
				for (lnI = 0; lnI < line->whitespace; lnI++)
				{
					oss_sharedAsciiWriteFile(lnHandle, " ", 1);
					++lnBytesWritten;
				}

				// Write the line contents
				oss_sharedAsciiWriteFile(lnHandle, line->base + line->start + line->whitespace, line->length);
				lnBytesWritten += line->length;

				// Write the trailing CR/LF
				if (line->ll.next)
				{
					oss_sharedAsciiWriteFile(lnHandle, "\r\n", 2);
					lnBytesWritten += 2;
				}

				// Move to next line
				line = (SOssLine*)line->ll.next;
			}
			// Close the file handle
			oss_sharedAsciiCloseFile(lnHandle);
		}
		// Indicate how successful we were :-)
		return(lnBytesWritten);
	}




//////////
//
// Called to write the SOssLine structure's SOssComps to a disk file
//
//////
	u64 CALLTYPE oss_writeSOssLineSequenceCompsToDisk(s8* tcPathname, SStartEnd* tseLines)
	{
		u64			lnBytesWritten, lnMaxLength, lnStart, lnLength;
		s64			lnHandle;
		SOssLine*	line;
		SOssComp*	comp;
		s8			buffer[2048];


		// Attempt to open the indicated file
		lnBytesWritten	= 0;
		lnHandle		= oss_sharedAsciiOpenFile(tcPathname, true, false, true, true, false, true, true, false);
		if (lnHandle >= 0)
		{
			// Initialize our buffer one time up front
			vvm_memset(buffer, 32, sizeof(buffer));

			// Iterate through every line, providing each component
			line = (SOssLine*)tseLines->root->ptr;
			while (line)
			{
				// Make sure there's something to do for this line
				if (line->comps.root && line->comps.root->ptr)
				{
					// Prepare this line into a buffer which will be used for writing
					// Prepend any whitespace characters
					if (line->whitespace > 0)
						vvm_memcpy(buffer, line->base + line->start, line->whitespace);

					// Do each component in turn, populating the line
					comp		= (SOssComp*)line->comps.root->ptr;
					lnMaxLength	= 0;
					while (comp)
					{
						// For ease of readability, we expressly break these values out here so it's clear what we're doing
						lnStart		= line->whitespace + comp->start;
						lnLength	= comp->length;

						// If it will fit, populate it into our write buffer
						if (lnStart + lnLength < sizeof(buffer))
						{
							vvm_memcpy(buffer + lnStart, line->base + line->start + lnStart, lnLength);
							if (lnStart + lnLength > lnMaxLength)
								lnMaxLength = lnStart + lnLength;
						}

						// Move to the next component in the chain
						comp = (SOssComp*)comp->ll.next;
					}

					// Write the comp contents (or as much of them would fit in a sizeof(buffer) buffer)
					oss_sharedAsciiWriteFile(lnHandle, buffer, lnMaxLength);
					lnBytesWritten += lnMaxLength;

					// Reset the portion we just used
					vvm_memset(buffer, 32, lnMaxLength);
				}

				// Write the trailing CR/LF
				if (line->ll.next)
				{
					oss_sharedAsciiWriteFile(lnHandle, "\r\n", 2);
					lnBytesWritten += 2;
				}

				// Move to next line
				line = (SOssLine*)line->ll.next;
			}
			// Close the file handle
			oss_sharedAsciiCloseFile(lnHandle);
		}
		// Indicate how successful we were :-)
		return(lnBytesWritten);
	}




//////////
//
// Called to write the SOssLine structure's SOssComps to a disk file in a debugging format,
// which writes components in this form:
//		[1:something][2:next][3:thing][4:etc]
//
//////
	u64 CALLTYPE oss_writeSOssLineSequenceCompsDebuggingToDisk(s8* tcPathname, SStartEnd* tseLines)
	{
		u64			lnBytesWritten, lnStart, lnLength, lnBufLength;
		s64			lnHandle;
		SOssLine*	line;
		SOssComp*	comp;
		s8			buffer[2048];


		// Attempt to open the indicated file
		lnBytesWritten	= 0;
		lnHandle		= oss_sharedAsciiOpenFile(tcPathname, true, false, true, true, false, true, true, false);
		if (lnHandle >= 0)
		{
			// Initialize our buffer one time up front
			memset(buffer, 0, sizeof(buffer));

			// Iterate through every line, providing each component
			line = (SOssLine*)tseLines->root->ptr;
			while (line)
			{
				// Make sure there's something to do for this line
				if (line->comps.root && line->comps.root->ptr)
				{
					// Do each component in turn, populating the line
					comp		= (SOssComp*)line->comps.root->ptr;
					while (comp)
					{
						// Prepare this component's first part
						sprintf_s(buffer, sizeof(buffer), "[%u:%u:", comp->iCode, comp->length);

						// For ease of readability, we expressly break these values out here so it's clear what we're doing
						lnStart		= line->whitespace + comp->start;
						lnLength	= comp->length;
						lnBufLength	= strlen(buffer);

						// If it will fit, populate it into our write buffer
						if (lnStart + lnLength < sizeof(buffer))
						{
							vvm_memcpy(buffer + lnBufLength, line->base + line->start + lnStart, lnLength);
							lnBufLength += lnLength;
						}

						// Close the comp
						buffer[lnBufLength++] = ']';

						// Write the component contents
						oss_sharedAsciiWriteFile(lnHandle, buffer, lnBufLength);
						lnBytesWritten += lnBufLength;

						// Reset the portion we just used
						vvm_memset(buffer, 0, lnBufLength);

						// Move to the next component in the chain
						comp = (SOssComp*)comp->ll.next;
					}
				}

				// Write the trailing CR/LF
				if (line->ll.next)
				{
					oss_sharedAsciiWriteFile(lnHandle, "\r\n", 2);
					lnBytesWritten += 2;
				}

				// Move to next line
				line = (SOssLine*)line->ll.next;
			}
			// Close the file handle
			oss_sharedAsciiCloseFile(lnHandle);
		}
		// Indicate how successful we were :-)
		return(lnBytesWritten);
	}




//////////
//
// Searches the haystack for the indicated needle, and reports the position if found
//
// Returns:
//		true	- found, tnPosition is updated
//		false	- not found, tnPosition unchanged
//
//////
	bool CALLTYPE oss_findFirstOccurrenceOfAsciiCharacter(s8* tcHaystack, u64 tnHaystackLength, s8 tcNeedle, u64* tnPosition)
	{
		u64		lnI;
		bool	llFound;


		// Make sure our environment is sane
		llFound = false;
		if (tcHaystack && tnHaystackLength != 0)
		{
			// Repeat for the length of the string
			for (lnI = 0; lnI < tnHaystackLength; lnI++)
			{
				// See if this is the character we're after
				if (tcHaystack[lnI] == tcNeedle)
				{
					// We found it
					llFound = true;

					// Update caller's pointer if need be
					if (tnPosition)
						*tnPosition = lnI;

					// All done
					break;
				}
			}
			// When we get here, either found or not
		}
		// Indicate our found condition
		return(llFound);
	}




//////////
//
// Searches forward to find the indicated component by the indicated type.
//
// Returns:
//		The matching component
//		If NULL, the compLastScanned indicates the last component that was searched where it wasn't found
//
//////
	SOssComp* CALLTYPE oss_findNextSOssCompBy_iCode(SOssComp* comp, u32 tniCode, SOssComp** compLastScanned)
	{
		// Initially indicate failure
		if (compLastScanned)
			*compLastScanned = comp;

		// Continue while the environment is sane
		while (comp)
		{
			// Store the component we're scanning
			if (compLastScanned)
				*compLastScanned = comp;

			// See if this is it
			if (comp->iCode == tniCode)
				break;		// It is, we're done

			// Move to the next component
			comp = (SOssComp*)comp->ll.next;
		}
		// When we get here, we either found it or not
		// Store our results
		return(comp);
	}




//////////
//
// Searches for the next non-whitespace component, including itself
//
//////
	SOssComp* CALLTYPE oss_skipPastSOssComp_iCode(SOssComp* comp, u32 tniCode)
	{
		while (comp && comp->iCode == tniCode)
		{
			// Move to next component
			comp = (SOssComp*)comp->ll.next;
		}
		// When we get here, we're sitting on either no valid component, or the one which does not match the specified type
		return(comp);
	}




//////////
//
// Called to combine two components which are touching into one.
//
// Source:		define user32		something here
// Example:		[define][whitespace][user][32][whitespace][something][here]
// Search:		[alpha][numeric], convert to [alphanumeric]
// After:		[define][whitespace][user32][whitespace][something][here]
//
//////
	u32 CALLTYPE oss_combine2SOssComps(SOssLine* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeCombined)
	{
		u32			lnCount;
		SOssComp*	compNext;
		SOssComp*	comp;
		SOssComp*	comp1;
		SOssComp*	comp2;


		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->comps.root)
		{
			// Grab the first component
			comp = (SOssComp*)line->comps.root->ptr;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = (SOssComp*)comp->ll.next;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Grab the one after that
				comp1 = comp;
				comp2 = (SOssComp*)comp1->ll.next;
				if (!comp2)
					return(lnCount);	// We're done

				// When we get here, we have needle-1 and needle-2 candidates.
				// Are they touching?
				if (comp1->start + comp1->length == comp2->start)
				{
					// Uh ... yes.  Can we get a chaperon over here, please?  Thank you!
					// Are they our requested?
					if (comp1->iCode == tniCodeNeedle1 && comp2->iCode == tniCodeNeedle2)
					{
						// YES!  This is the moment we've been waiting for. THIS is why we showed up for work today. THIS is why we came!
						// Gentlemen, we have a job to do.  Now, let's get to it!
						++lnCount;

						//////////
						// Combine these into one
						//////
							// Increase comp1's length, then move comp2 from line->comps to line->compsCombined
							comp1->length	+= comp2->length;
							comp1->iCode	= tniCodeCombined;
							vvm_SEChain_completelyMigrateSLLByPtr(&line->compsCombined, &line->comps, (SLL*)comp2, 0, _COMMON_START_END_BLOCK_SIZE);

						//////////
						// Point to the new next thing, which is now the thing after what previously had been comp2, but is now simply comp->ll.next (which could now be nothing)
						//////
							compNext = (SOssComp*)comp->ll.next;
					}
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to combine three components which are touching into one.
//
// Source:		saddf32		a,20.50
// Example:		[saddf32][whitespace][a][comma][20][period][50]
// Search:		[numeric][period][numeric], convert to [numeric]
// After:		[sadf32][whitespace][a][comma][20.50]
//
//////
	u32 CALLTYPE oss_combine3SOssComps(SOssLine* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeNeedle3, u32 tniCodeCombined)
	{
		u32			lnCount;
		SOssComp*	compNext;
		SOssComp*	comp;
		SOssComp*	comp1;
		SOssComp*	comp2;
		SOssComp*	comp3;


// UNTESTED CODE:  breakpoint and examine
		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->comps.root)
		{
			// Grab the first component
			comp = (SOssComp*)line->comps.root->ptr;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = (SOssComp*)comp->ll.next;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Grab the one after that
				comp1 = compNext;
				comp2 = (SOssComp*)comp1->ll.next;
				if (!comp2)
					return(lnCount);	// We're done

				// Grab the one after that
				comp3 = (SOssComp*)comp2->ll.next;
				if (!comp3)
					return(lnCount);	// We're done

				// When we get here, we have needle-1, needle-2, and needle-3 candidates.
				// Are they touching?
				if (comp1->start + comp1->length == comp2->start && comp2->start + comp2->length == comp3->start)
				{
					// Are they our requested?
					if (comp1->iCode == tniCodeNeedle1 && comp2->iCode == tniCodeNeedle2 && comp3->iCode == tniCodeNeedle3)
					{
						// It's a match
						lnCount += 2;

						//////////
						// Combine these into one
						//////
							// Increase comp1's length, then move comp2 from line->comps to line->compsCombined
							comp1->length	+= comp2->length + comp3->length;
							comp1->iCode	= tniCodeCombined;
							vvm_SEChain_completelyMigrateSLLByPtr(&line->compsCombined, &line->comps, (SLL*)comp2, 0, _COMMON_START_END_BLOCK_SIZE);
							vvm_SEChain_completelyMigrateSLLByPtr(&line->compsCombined, &line->comps, (SLL*)comp3, 0, _COMMON_START_END_BLOCK_SIZE);

						//////////
						// Point to the new next thing, which is now the thing after what previously had been comp2, but is now simply comp->ll.next (which could now be nothing)
						//////
							compNext = (SOssComp*)comp->ll.next;
					}
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to combine everything between two components
//
// Source:		u8 name[] = "foo"
// Example:		[u8][whitespace][name][left bracket][right bracket][whitespace][equal][whitespace][double quote][foo][double quote]
// Search:		[double quote], replace with [double quoted text]
// After:		[u8][whitespace][name][left bracket][right bracket][whitespace][equal][whitespace][double quote text]
//
//////
	u32 CALLTYPE oss_combineAllBetweenSOssComps(SOssLine* line, u32 tniCodeNeedle, u32 tniCodeCombined)
	{
		u32			lnCount;
		SOssComp*	compNext;
		SOssComp*	comp;
		SOssComp*	compSearcher;


// UNTESTED CODE:  breakpoint and examine
		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->comps.root)
		{
			// Grab the first component
			comp = (SOssComp*)line->comps.root->ptr;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = (SOssComp*)comp->ll.next;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Is this our intended?
				if (comp->iCode == tniCodeNeedle)
				{
					// Search forward to see if there is a matching entry
					compSearcher = compNext;
					while (compSearcher)
					{
						if (compSearcher->iCode == tniCodeNeedle)
						{
							// This is the match, combine everything between
							comp->length	= (compSearcher->start + compSearcher->length) - comp->start;
							comp->iCode		= tniCodeCombined;

							// Iterate and merge in
							while (compNext)
							{
								// Increase our count
								++lnCount;

								// Migrate this one (as it was technically merged above with the comp->length = line)
								vvm_SEChain_completelyMigrateSLLByPtr(&line->compsCombined, &line->comps, (SLL*)compNext, 0, _COMMON_START_END_BLOCK_SIZE);

								// See if we're done
								if (compNext == compSearcher)
									break;		// This was the last one, we're done

								// Move to the next component (which is the comp->ll.next component again, because we just migrated the previous compNext
								compNext = (SOssComp*)comp->ll.next;
							}
							// When we get here, everything's migrated

							// Grab the new next, which is the one after the matched entry
							compNext = (SOssComp*)comp->ll.next;

							// Continue looking for more combinations on this line
							break;
						}

						// Move to the next component
						compSearcher = (SOssComp*)compSearcher->ll.next;
					}
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to combine everything after the indicated component
//
// Source:		u8* name		// user name
// Example:		[u8][asterisk][whitespace][name][whitespace][comment][whitespace][user][whitespace][name]
// Search:		[comment]
// After:		[u8][asterisk][whitespace][name][whitespace][comment]
//
//////
	u32 CALLTYPE oss_combineAllAfterSOssComp(SOssLine* line, u32 tniCodeNeedle)
	{
		u32			lnCount;
		SOssComp*	compNext;
		SOssComp*	comp;


// UNTESTED CODE:  breakpoint and examine
		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->comps.root)
		{
			// Grab the first component
			comp = (SOssComp*)line->comps.root->ptr;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = (SOssComp*)comp->ll.next;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Is this our intended?
				if (comp->iCode == tniCodeNeedle)
				{
					//////////
					// Combine from here on out into one
					//////
						// Increase the original component to the line's whole length
						comp->length = line->length - comp->start;
						
						while (compNext)
						{
							// Indicate the number combined
							++lnCount;

							// Move this one along
							vvm_SEChain_completelyMigrateSLLByPtr(&line->compsCombined, &line->comps, (SLL*)compNext, 0, _COMMON_START_END_BLOCK_SIZE);

							// Move to next component (which is now again the comp->ll.next entry, because we've just migrated the prior compNext entry to compsCombined)
							compNext = (SOssComp*)comp->ll.next;
						}
						// When we get here, we're done
						break;
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to remove extraneous whitespaces
//
// Source:		u8* name		// user name
// Example:		[u8][asterisk][whitespace][name][whitespace][comment][whitespace][user][whitespace][name]
// Search:		[comment]
// After:		[u8][asterisk][whitespace][name][whitespace][comment]
//
//////
	u32 CALLTYPE oss_removeExtraneousWhitespaceSOssComps(SOssLine* line, u32 tniCodeWhitespace)
	{
		return(0);
	}




/////////
//
// Called to open a file in either shared or exclusive access mode.
//
// Returns:
//		-1 access error (attempt to open read-only file in read/write mode, for example, or file was a directory, not a file)
//		-2 out of file handles (too many files open)
//		-3 file not found, or could not be opened
//		-4 (internal error) an invalid combination of file flags was attempted
//		-5 other error, unspecified cause
//		a handle used to reference the file in future calls
//
//////
	u64 CALLTYPE oss_sharedAsciiOpenFile(s8* tcPathname, bool tlExclusive, bool tlReadOnly, bool tlIfShared_DenyReads, bool tlIfShared_DenyWrites, bool tlAppendMode, bool tlTruncate, bool tlShortLived, bool tlTemporaryFile)
	{
		bool	llTriedOnce;
		u32		lnMode, lnShare, lnHandle, lnSaveErrno;


		//////////
		// Open mode
		//////
			lnMode = _O_BINARY | _O_RANDOM;
			if (tlExclusive)		lnMode |= _O_EXCL;
			if (tlShortLived)		lnMode |= _O_SHORT_LIVED;
			if (tlTemporaryFile)	lnMode |= _O_TEMPORARY;

			// Read-only or read-write
			if (tlReadOnly)			lnMode |= _O_RDONLY;
			else					lnMode |= _O_RDWR;

			// Append or truncate:
			if (tlAppendMode)		lnMode |= _O_APPEND;
			else if (tlTruncate)	lnMode |= _O_TRUNC;


		//////////
		// Sharing mode
		//////
			if (tlExclusive || (tlIfShared_DenyReads && tlIfShared_DenyWrites))
			{
				// Deny reads and writes
				lnShare = _SH_DENYRW;

			} else if (tlIfShared_DenyReads) {
				// Deny only writes
				lnShare = _SH_DENYRD;

			} else if (tlIfShared_DenyWrites) {
				// Deny only writes
				lnShare = _SH_DENYWR;
			} else {
				// Deny nothing
				lnShare  =_SH_DENYNO;
			}


		//////////
		// Try to open
		//////
			llTriedOnce = false;
openAgain:
			lnHandle = _sopen(tcPathname, lnMode, lnShare);
			if (lnHandle == -1)
			{
				// Error opening the file
				lnSaveErrno	= errno;
				if (!llTriedOnce && tlTruncate)
				{
					// Try creating the file, since it would have been truncated anyway
					lnHandle	= _creat(tcPathname, _S_IREAD | _S_IWRITE);
					if (lnHandle != -1)
					{
						// Successful, now re-open in the asked-for mode
						_close(lnHandle);
						llTriedOnce = true;
						goto openAgain;
					}
				}
				if (lnSaveErrno == EACCES)	return(-1);
				if (lnSaveErrno == EMFILE)	return(-2);
				if (lnSaveErrno == ENOENT)	return(-3);
				if (lnSaveErrno == EINVAL)	return(-4);
				// If we get here, we don't know the error's explicit cause... so we indicate general error
				return(-5);
			}

		// If we get here, we're good
		// Create the entry in the open files listing
		_iswSSharedFile* lsf = (_iswSSharedFile*)vvm_SEChain_append(&gseRootForeignFiles, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(_iswSSharedFile), _COMMON_START_END_BLOCK_SIZE, NULL);
		if (lsf)
		{
			// Populate it with file data
			lsf->handle = lnHandle;

			// Store date and time
			oss_dateTimeGet(&lsf->fileOpened);
			memcpy(&lsf->fileAccessed, &lsf->fileOpened, sizeof(SDateTime));

			// Indicate success
			return(lsf->ll.uniqueId);

		} else {
			// Hmmm... what to do here?  The file opened, but we can't make a permanent record of it.
			// We return a unique id to our gseRootForeignFiles listing to access file data.
			// So ... we cannot succeed even though resources are available
			_close(lnHandle);
			return(-2);
		}
	}




/////////
//
// Called to seek to a file position, either explicitly, or relative to current location.
//
// Returns:
//		-1 if invalid handle
//		new explicit file offset
//
//////
	u64 CALLTYPE oss_sharedAsciiSeekFile(u64 tnFileHandle, s64 tnDisplacement, u64 tnSource/*0=file offset, -1=relative backward, 1=relative forward*/)
	{
		_iswSSharedFile*	lsf;


		// Make sure the indicated file exists
		lsf = (_iswSSharedFile*)vvm_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
		if (!lsf)	return(-1);		// Invalid file handle


		// Update last accessed time
		oss_dateTimeGet(&lsf->fileAccessed);


		// Make sure we have something to do
		if (tnDisplacement != 0)
		{
			// Attempt the move
			_lseeki64(lsf->handle, tnDisplacement, (tnSource == 0) ? SEEK_SET : SEEK_CUR);
		}


		// Report on the current/new file position
		lsf->lastOffset = _telli64(lsf->handle);
		return(lsf->lastOffset);
	}




/////////
//
// Called to read data from a previously opened file.
//
// Returns:
//		-1 if invalid handle
//		-2 if invalid destination address
//		-3 if read error
//		-4 if read is larger than 4GB
//		number of bytes read
//
//////
	u64 CALLTYPE oss_sharedAsciiReadFile(u64 tnFileHandle, s8* tcDest, u32 tnBytesToRead)
	{
		s64					lnNumread;
		_iswSSharedFile*	lsf;


		// Make sure we can read somewhere
		if (!tcDest)
			return(-2);		// Invalid pointer
// TODO:  (future enhancement) make this a true 64-bit read function
		if (tnBytesToRead > 0xffffffff)
			return(-4);

		// Make sure the indicated file exists
		lsf = (_iswSSharedFile*)vvm_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
		if (!lsf)	return(-1);			// Invalid file handle


		// Update last accessed time
		oss_dateTimeGet(&lsf->fileAccessed);


		// Attempt the read
		lnNumread = (s64)_read(lsf->handle, tcDest, tnBytesToRead);
		if (lnNumread <= 0)
			return(-3);					// Read error


		// Get new file position
		lsf->lastOffset = _telli64(lsf->handle);


		// Indicate how many were read
		lsf->bytesRead += lnNumread;
		return((u64)lnNumread);
	}




/////////
//
// Called to write data to a previously opened file.
//
// Returns:
//		-1 if invalid handle
//		-2 if invalid source address
//		-3 if write error
//		-4 if too write is larger than 4GB
//		number of bytes written
//
//////
	u64 CALLTYPE oss_sharedAsciiWriteFile(u64 tnFileHandle, s8* tcSource, u64 tnBytesToWrite)
	{
		s64					lnNumwritten;
		_iswSSharedFile*	lsf;


		// Make sure we can read somewhere
		if (!tcSource)
			return(-2);		// Invalid pointer
// TODO:  (future enhancement) make this a true 64-bit write function
		if (tnBytesToWrite > 0xffffffff)
			return(-4);


		// Make sure the indicated file exists
		lsf = (_iswSSharedFile*)vvm_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
		if (!lsf)	return(-1);			// Invalid file handle


		// Update last accessed time
		oss_dateTimeGet(&lsf->fileAccessed);


		// Attempt the write
		lnNumwritten = (s64)_write(lsf->handle, tcSource, (u32)tnBytesToWrite);
		if ((s64)lnNumwritten <= 0)
			return(-3);					// Write error


		// Get new file position
		lsf->lastOffset = _telli64(lsf->handle);


		// Indicate how many were written
		lsf->bytesWritten += lnNumwritten;
		return((u64)lnNumwritten);
	}




/////////
//
// Called to lock a file (or portion of a file) previously opened in shared mode for
// exclusive access for a portion.
//
// Returns:
//		-1 if invalid handle
//		-2 lock attempt unsuccessful (someone else has the file locked??)
//		number of bytes locked
//
//////
	u64 CALLTYPE oss_sharedAsciiLockFile(u64 tnFileHandle, u64 tnStart, u64 tnLength)
	{
		u32						lnResult;
		_iswSSharedFile*		lsf;
		_iswSSharedFileLocks*	lsfl;


		// Make sure the indicated file exists
		lsf = (_iswSSharedFile*)vvm_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
		if (!lsf)	return(-1);			// Invalid file handle


		// Update last accessed time
		oss_dateTimeGet(&lsf->fileAccessed);


		//////////
		// Attempt the lock
		//////
			// See to offset
			_lseeki64(lsf->handle, tnStart, SEEK_SET);

			// Lock the next specified bytes
			lnResult = _locking(lsf->handle, _LK_NBLCK, (s32)tnLength);
			if (lnResult == -1)		return(-2);		// Failure locking


		//////////
		// If we get here, we're good
		//////
			// Add the lock to the list of locks for this file
			lsfl = (_iswSSharedFileLocks*)vvm_SEChain_append(&lsf->locks, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(_iswSSharedFileLocks), _COMMON_START_END_BLOCK_SIZE, NULL);
			if (lsfl)
			{
				// Store lock time
				oss_dateTimeGet(&lsfl->locked);

				// Store lock info
				lsfl->offset = tnStart;
				lsfl->length = tnLength;

				// Increase our lock count
				++lsf->locksIssued;

				// Indicate success
				return(tnLength);

			} else {
				// It was locked, but we can't record it, so we fail
				_locking(lsf->handle, _LK_UNLCK, (s32)tnLength);
				return(-2);		// Failure
			}
	}




/////////
//
// Called to release a previous lock on a file.
//
// Returns:
//		-1 if invalid file handle
//		-2 if invalid lock handle
//		number of bytes unlocked
//
//////
	u64 CALLTYPE oss_sharedAsciiUnlockFile(u64 tnFileHandle, u64 tnLockHandle)
	{
		u64						lnLength;
		_iswSSharedFile*		lsf;
		_iswSSharedFileLocks*	lsfl;


		// Make sure the indicated file exists
		lsf = (_iswSSharedFile*)vvm_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
		if (!lsf)	return(-1);			// Invalid file handle

		lsfl = (_iswSSharedFileLocks*)vvm_SEChain_searchByUniqueId(&lsf->locks, tnLockHandle);
		if (!lsfl)	return(-2);			// Invalid lock handle


		// Update last accessed time
		oss_dateTimeGet(&lsf->fileAccessed);


		//////////
		// Unlock
		//////
			// See to offset
			_lseeki64(lsf->handle, lsfl->offset, SEEK_SET);

			// Unlock the next specified bytes
			lnLength = lsfl->length;
			_locking(lsf->handle, _LK_UNLCK, (s32)lnLength);


		//////////
		// If we get here, we're good
		//////
			// Delete this lock
			vvm_SEChain_deleteFrom(&lsf->locks, (SLL*)lsfl, true);

			// Increase the number of unlocks made
			++lsf->locksCleared;

			// Indicate success
			return(lnLength);
	}




/////////
//
// Called to close a previously opened file.
//
// Returns:
//		-1 if invalid handle
//		0 successful
//
//////
	u64 CALLTYPE oss_sharedAsciiCloseFile(u64 tnFileHandle)
	{
		_iswSSharedFile*	lsf;


		// Make sure the indicated file exists
		lsf = (_iswSSharedFile*)vvm_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
		if (!lsf)	return(-1);			// Invalid file handle

		// Close the handle
		_close(lsf->handle);

		// Delete any locks, with a callback to unlock any active locks
		vvm_SEChain_delete(&lsf->locks, (u64)&iioss_sharedAsciiCloseFileLocksCallback, (u64)lsf, true);

		// Delete this entry
		vvm_SEChain_deleteFrom(&gseRootForeignFiles, (SLL*)lsf, true);

		// Indicate success
		return(0);
	}




/////////
//
// Called to return the file's size
//
// Returns:
//		-1 if invalid handle
//		>=0 if successful
//
//////
	u64 CALLTYPE oss_sharedAsciiFileSize(u64 tnFileHandle)
	{
		u64					lnCurrent, lnSize;
		_iswSSharedFile*	lsf;


		// Make sure the indicated file exists
		lsf = (_iswSSharedFile*)vvm_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
		if (!lsf)	return(-1);			// Invalid file handle


		// Update last accessed time
		oss_dateTimeGet(&lsf->fileAccessed);


		// Get the current offset
		lnCurrent = _telli64(lsf->handle);


		// Move to the end
		_lseeki64(lsf->handle, 0, SEEK_END);


		// Get the file size
		lnSize = _telli64(lsf->handle);


		// Move back to where we started
		_lseeki64(lsf->handle, lnCurrent, SEEK_SET);


		// All done
		return(lnSize);
	}




//////////
//
// Called to allocate (using oss_alloc()) and return a temporary filename guaranteed to be
// unique.  The returned string must be cleaned up by the caller, using oss_free() to release
// it when finished.
//
//////
	s8* CALLTYPE oss_sharedAsciiGetTempFilename(void)
	{
		u32		lnLength;
		s8		lcTempPathOnly[_MAX_PATH];
		s8		lcTempFullPathname[_MAX_PATH];
		s8*		lcReturnFullPathname;


		// Get the temporary path
		if (!GetTempPathA(sizeof(lcTempPathOnly), lcTempPathOnly))
			return(NULL);

		// Get the concatenated temporary filename
		if (!GetTempFileNameA(lcTempPathOnly, NULL, 0, lcTempFullPathname))
			return(NULL);

		// Duplicate the string for return
		lnLength = strlen(lcTempFullPathname);
		lcReturnFullPathname = (s8*)oss_alloc(lnLength + 1, true);
		if (lcReturnFullPathname)
			memcpy(lcReturnFullPathname, lcTempFullPathname, lnLength);

		// When we get here, right, wrong, or indifferent, we're done
		return(lcReturnFullPathname);
	}




//////////
//
// Called to delete the indicated fully qualified pathname from the disk.
//
//////
	bool CALLTYPE oss_sharedAsciiDeleteFile(s8* tcFullPathname)
	{
		return(((DeleteFileA(tcFullPathname)) ? true : false));
	}




//////////
//
// Called to write out the specified data to the specified file
//
//////
	bool CALLTYPE oss_sharedAsciiWriteOutFile(s8* tcFullPathname, s8* tcData, u32 tnDataLength)
	{
		u64 lnFile, lnNumwritten;


		lnFile = oss_sharedAsciiOpenFile(tcFullPathname, true, false, false, false, false, true, true, false);
		if (lnFile >= 0)
		{
			// Attempt to write the data
			lnNumwritten = oss_sharedAsciiWriteFile(lnFile, tcData, tnDataLength);

			// Close the file
			oss_sharedAsciiCloseFile(lnFile);

			// Indicate our success or failure
			return(lnNumwritten == tnDataLength);
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called in a two or three part sequence, used to find the files in an indicated
// directory using the specified initial template
//
//////
	u64 CALLTYPE CALLTYPE oss_fileFindFirst(SFindFile* tsFileInfo)
	{
		u32					lnLength;
		HANDLE				lnHandle;
		WIN32_FIND_DATAA	lwfd;
		s8					buffer[_MAX_PATH];


		// Make sure there's a pathname
		if (!tsFileInfo->pathnameOfSearch.data._u8)
			vvm_datumSet(&tsFileInfo->pathnameOfSearch, (u8*)".\\", -1, true);

		// Make sure the environment has sane
		lnHandle = (HANDLE)-1;
		if (tsFileInfo && tsFileInfo->filenameSearched.data._u8 && tsFileInfo->filenameSearched.length != 0)
		{
			//////////
			// Create the filename
			//////
				memset(buffer, 0, sizeof(buffer));
				lnLength = (u32)tsFileInfo->pathnameOfSearch.length;

				// Copy the pathname part (if any)
				vvm_memcpy(buffer, tsFileInfo->pathnameOfSearch.data._s8, lnLength);

				// Make sure it is terminated with a backslash
				if (buffer[lnLength - 1] != '\\')
				{
					// Needs a backslash
					buffer[lnLength] = '\\';
					++lnLength;
				}
				// Append on the file spec
				vvm_memcpy(buffer + lnLength, tsFileInfo->filenameSearched.data._s8, tsFileInfo->filenameSearched.length);
				// Right now, the buffer is something like ".\plugins\sound.dll"
			

			// Attempt to get a file list
			lnHandle = FindFirstFileA(buffer, &lwfd);
			if (lnHandle != INVALID_HANDLE_VALUE)
				ioss_setFindFileStatus(tsFileInfo, &lwfd);	// Copy the file info

		}

		// The result is either -1, or a valid handle for subsequent calls to oss_fileFindNext()
		return((u64)lnHandle);
	}




//////////
//
// Called after a prior call to oss_fileFindFirst() to find the next file in an indicated
// directory using the specified initial template.
//
//////
	// Called to find the next file
	bool CALLTYPE oss_fileFindNext(u64 tnHandle, SFindFile* tsFileInfo)
	{
		bool				llResult;
		WIN32_FIND_DATAA	lwfd;


		// Make sure the environment is sane
		llResult = false;
		if (tsFileInfo)
		{
			// Locate
			llResult = ((FindNextFileA((HANDLE)tnHandle, &lwfd)) ? true : false);
			if (llResult)
				ioss_setFindFileStatus(tsFileInfo, &lwfd);	// Copy the file info

		}
		// Indicate the success
		return(llResult);

	}




//////////
//
// Called as the last step to close a previously opened find.
//
//////
	void CALLTYPE oss_fileFindClose(u64 tnHandle, SFindFile* tsFileInfo)
	{
		FindClose((HANDLE)tnHandle);

		// Release any allocated datums
		// Filename
		if (tsFileInfo->filenameSearched.data._u8 && tsFileInfo->filenameSearched.length != 0)
			vvm_datumDelete(&tsFileInfo->filenameSearched);

		// Pathname
		if (tsFileInfo->pathnameOfSearch.data._u8 && tsFileInfo->pathnameOfSearch.length != 0)
			vvm_datumDelete(&tsFileInfo->pathnameOfSearch);

		// File
		if (tsFileInfo->file.data._u8 && tsFileInfo->file.length != 0)
			vvm_datumDelete(&tsFileInfo->file);

		// File2
		if (tsFileInfo->file2.data._u8 && tsFileInfo->file2.length != 0)
			vvm_datumDelete(&tsFileInfo->file2);
	}




//////////
//
// Create a thread for the specified address
//
//////
	u64 CALLTYPE oss_threadCreate(u64 tnThreadAddress, void* data, bool tlStartSuspended)
	{
		u64				lnResult;
		_iswSThreads*	lt;


		// Lock the semaphore
		oss_lockSemaphore(gsemForeignThreadAccess);

		// Initially indicate failure
		lnResult = 0;

		// Enter a thread (for breaks)
		while (tnThreadAddress)
		{
			//////////
			// Create its entry in the next free slot
			//////
			lt = (_iswSThreads*)vvm_SEChain_append(&gseRootForeignThreads, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(_iswSThreads), _COMMON_START_END_BLOCK_SIZE, NULL);
				if (!lt)
				{
					// Should not happen, but it did
					lnResult = false;
					break;
				}


			//////////
			// Spawn it as a viable thread, potentially paused
			// BEGIN
			//////
				//////
					lt->os_threadHandle = CreateThread(	0, 0,											// Security attributes (use OS defaults)
														(LPTHREAD_START_ROUTINE)tnThreadAddress,		// Address to kick into gear (as it were)
														data,											// Caller-specified data
														(tlStartSuspended) ? CREATE_SUSPENDED : 0,		// Should it start suspended?
														&lt->os_threadId);								// OS will return the new thread id number
				//////
			//////
			// END
			//////////


			//////////
			// The thread was either spawned or not
			// If it was, indicate the id number to access this slot in the Start/end chain in the future
			//////
				if (lt->os_threadHandle)
				{
					// Set the successful startup of this thread
					lt->isViable	= true;
					lt->isSuspended = tlStartSuspended;

					// Indicate our ID number to access this structure in the future
					lnResult		= lt->ll.uniqueId;

				} else {
					// Set the failed startup of this thread
					lt->isViable	= false;
				}

			// All done
			break;
		}

		// Unlock the semaphore
		oss_unlockSemaphore(gsemForeignThreadAccess);

		// Indicate our success or failure
		return(lnResult);
	}




//////////
//
// Suspend the indicated thread
//
// Returns:
//		Tick count when the thread was suspended
//
//////
	u64 CALLTYPE oss_threadSuspend(u64 ossData)
	{
		u64				lnResult;
		_iswSThreads*	lt;


		// Lock the semaphore
		oss_lockSemaphore(gsemForeignThreadAccess);

		// Initially indicate failure
		lnResult = 0;

		// Locate the indicated thread
		lt = (_iswSThreads*)vvm_SEChain_searchByUniqueId(&gseRootForeignThreads, ossData);
		while (lt && lt->isViable && !lt->isSuspended)
		{
			// Suspend the thread
			SuspendThread(lt->os_threadHandle);

			// Mark it as such
			lt->isSuspended = true;

			// Return the tick count to indicate success
			lnResult = gnTickCount;

			// All done
			break;
		}

		// Unlock the semaphore
		oss_unlockSemaphore(gsemForeignThreadAccess);

		// Indicate success or failure
		return(lnResult);
	}




//////////
//
// Resume the indicated thread
//
//////
	u64 CALLTYPE oss_threadResume(u64 ossData)
	{
		u64				lnResult;
		_iswSThreads*	lt;


		// Lock the semaphore
		oss_lockSemaphore(gsemForeignThreadAccess);

		// Initially indicate failure
		lnResult = 0;

		// Locate the indicated thread
		lt = (_iswSThreads*)vvm_SEChain_searchByUniqueId(&gseRootForeignThreads, ossData);
		while (lt && lt->isViable && lt->isSuspended)
		{
			// Resume the thread
			ResumeThread(lt->os_threadHandle);

			// Mark it as such
			lt->isSuspended = false;

			// Return the tick count to indicate success
			lnResult = gnTickCount;

			// All done
			break;
		}

		// Unlock the semaphore
		oss_unlockSemaphore(gsemForeignThreadAccess);

		// Indicate success or failure
		return(lnResult);
	}




//////////
//
// Terminate the indicated thread
//
//////
	u64 CALLTYPE oss_threadTerminate(u64 ossData, u32 tnTerminationCode)
	{
		u64				lnResult;
		_iswSThreads*	lt;


		// Lock the semaphore
		oss_lockSemaphore(gsemForeignThreadAccess);

		// Initially indicate failure
		lnResult = 0;

		// Locate the indicated thread
		lt = (_iswSThreads*)vvm_SEChain_searchByUniqueId(&gseRootForeignThreads, ossData);
		while (lt && lt->isViable)
		{
			// Resume the thread
			TerminateThread(lt->os_threadHandle, tnTerminationCode);

			// Delete the item from the Start/end chain
			vvm_SEChain_deleteFrom(&gseRootForeignThreads, (SLL*)lt, true);

			// Return the tick count to indicate success
			lnResult = gnTickCount;

			// All done
			break;
		}

		// Unlock the semaphore
		oss_unlockSemaphore(gsemForeignThreadAccess);

		// Indicate success or failure
		return(lnResult);
	}




//////////
//
// Create a semaphore for synchronized resource access
//
//////
	u64 CALLTYPE oss_createSemaphore(void)
	{
		CRITICAL_SECTION* lcs;


		// Create a memory arae for the semaphore
		lcs = (CRITICAL_SECTION*)malloc(sizeof(CRITICAL_SECTION));
		if (lcs)
		{
			// Initialize the semaphore
			InitializeCriticalSection(lcs);

			// Return the results
			return((u64)lcs);

		} else {
			// Failure
			return(0);
		}
	}




//////////
//
// Wait until it's our turn across the semaphore
//
//////
	void CALLTYPE oss_lockSemaphore(u64 handle)
	{
		CRITICAL_SECTION* lcs;


		if (handle)
		{
			// Convert the handle to the critical section
			lcs = (CRITICAL_SECTION*)handle;

			// Enter the critical section
			EnterCriticalSection(lcs);
		}
	}




//////////
//
// Try to lock the semaphore, and immediately fail if unable
//
//////
	bool CALLTYPE oss_tryLockSemaphore(u64 handle)
	{
		CRITICAL_SECTION*	lcs;
		bool				llResult;


		if (handle)
		{
			// Convert the handle to the critical section
			lcs = (CRITICAL_SECTION*)handle;

			// Try to enter the critical section, return success
			llResult = (TryEnterCriticalSection(lcs)) ? true : false;

			// Indicate success or failure
			return(llResult);
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// We're done, release the semaphore resource
//
//////
	void CALLTYPE oss_unlockSemaphore(u64 handle)
	{
		CRITICAL_SECTION* lcs;


		if (handle)
		{
			// Convert the handle to the critical section
			lcs = (CRITICAL_SECTION*)handle;

			// Leave the critical section
			LeaveCriticalSection(lcs);
		}
	}




//////////
//
// Delete the semaphore
//
//////
	void CALLTYPE oss_deleteSemaphore(u64 handle)
	{
		CRITICAL_SECTION* lcs;


		if (handle)
		{
			// Convert the handle to the critical section
			lcs = (CRITICAL_SECTION*)handle;

			// Delete the critical section
			DeleteCriticalSection(lcs);
		}
	}




//////////
//
// Used for debugging, lowers a flag used internally to aid in debugging
//
//////
	void CALLTYPE oss_enableBreakpoints(void)
	{
		gbBreakpoints = false;
	}




//////////
//
// Used for debugging, raises a flag that can be used internally
//
//////
	void CALLTYPE oss_disableBreakpoints(void)
	{
		gbBreakpoints = true;
	}




// Additional source files not compiled separately, but merely as logical breakouts
#include "oss_sup.cpp"					// Support algorithms for VVMOSS in general
