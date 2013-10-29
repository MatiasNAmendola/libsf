//////////
//
// /libsf/vvm/vvmoss/vo.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     September 19, 2012 - Initial creation
//     September 29, 2012 - PBL v1.0 license included directly in source files.
//     November 07, 2012 - 0.60 development begins
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
#include "\libsf\vvm\core\common\common.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_vvmoss_plugins.h"
#include "\libsf\vvm\core\common\common_vvmoss_const.h"
#include "\libsf\vvm\core\common\common_vvmmc.h"
#include "\libsf\vvm\core\localization\vvmenu\resource.h"					// Resource constants
#include "vo_const.h"
#include "\libsf\vvm\core\common\fonts\font8x6.h"
#include "\libsf\vvm\core\common\fonts\font8x8.h"
#include "\libsf\vvm\core\common\fonts\font8x14.h"
#include "\libsf\vvm\core\common\fonts\font8x16.h"
#include "vo_structs.h"
#include "vo_istructs.h"
#include "\libsf\vvm\core\vvm\vvm_structs.h"
#include "vo_plugins.h"
#include "vo_defs.h"
#include "vo_glob.h"
#include "vo_class.h"
#include "\libsf\vvm\core\common\vvm_key_const.h"
#include "vo_bxml.h"

// THe following are include files of external (non-VVM) LibSF projects
#include "\libsf\utils\sha1\sha1.h"		// SHA-1 hashing algorithm




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
	u64 CALLTYPE oss_firstCallback(u64 tnDebuggerInterfaceAddress)
	{
		//////////
		// Load the base VVM functions
		//////
			if (tnDebuggerInterfaceAddress != 0)
				iLoadVvmFunctionsFromVVM((void**)tnDebuggerInterfaceAddress);


		//////////
		// Initialize internally required variables and semaphores
		//////
			InitializeCriticalSection(&gcsUniqueIdAccess);
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
	void CALLTYPE oss_bootstrapInitialization(u64 tnDebuggerInterfaceAddress)
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
			ioss_loadPlugins(tnDebuggerInterfaceAddress);
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
	void CALLTYPE oss_initialization(u64 tnDebuggerInterfaceAddress)
	{
		//////////
		// Load the VVMMC functions (if they're available to us, they should be)
		//////
			if (tnDebuggerInterfaceAddress != 0)
				iLoadVvmmcFunctionsFromVVM((void**)tnDebuggerInterfaceAddress);


		//////////
		// Set our initial BXML error condition to a no-error state
		//////
			iibxml_recordLastError(IDS_BXML_NO_ERROR, 0, NULL, NULL, NULL, 0);
	}





//////////
//
// Called to get a version string of this DLL
//
///////
	const s8* CALLTYPE oss_getVersion(void)
	{
		return(cgcVvmossVersion);
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
		_iswSOssWindowLL* w;


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
		plugin = (_isSInterfacePlugin*)oss_SEChain_searchByCallback(&gsRootFunctionPlugins, &cb);
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
					oss_datumSet(&plugin->editor.identifier, (u8*)tcMetaName, -1, true);
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
// Get the next unique id number
//
//////
	u64 CALLTYPE oss_getNextUniqueId(void)
	{
		return(ioss_getNextUniqueId());
	}




//////////
//
// Get the next N unique ids.
//
// Use as:
//		u32 lnLastId, lnIds[5];
//		lnLastId = oss_getNextNUniqueIds(&lnIds[0], 5);
//
// Returns:
//		Populates the array for the indicated number of ids beginning at the u32* address specified
//		Returns the last unique id number assigned in the chain
//
//////
	u64 CALLTYPE oss_getNextN_UniqueIds(u64* tnArrayBase, u32 tnCount)
	{
		return(ioss_getNextN_UniqueIds(tnArrayBase, tnCount));
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
					ioss_deleteScaleCompute(lsm);

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
// Returns a copy/duplicate or the template region
//
///////
	SRegion* CALLTYPE oss_regionDuplicate(u64 tnAssociatedId, SRegion* templateRegion)
	{
		return(NULL);
	}




//////////
//
// Called to paint a region using the default algorithms
//
//////
	u64 CALLTYPE oss_regionDefaultPaint(SRegion* tr)
	{
		u64 lnPixelsDrawn;
		u32 lnType;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tr->canvas && tr->data)
		{
			// Make sure there's a canvas we have to display something
			lnType = tr->type & _VVM_REGION_I_CANVAS_MASK;
			switch (lnType)
			{
				case _VVM_REGION_EDITBOX:
					lnPixelsDrawn = ioss_regionDefaultPaintEditbox(tr, tr->canvas, tr->canvas->bda, (SRegionEditboxData*)tr->data);
					break;

				case _VVM_REGION_BUTTON:
					lnPixelsDrawn = ioss_regionDefaultPaintButton(tr, tr->canvas, tr->canvas->bda, (SRegionButtonData*)tr->data);
					break;

				case _VVM_REGION_IMAGE:
					lnPixelsDrawn = ioss_regionDefaultPaintImage(tr, tr->canvas, tr->canvas->bda, (SRegionImageData*)tr->data);
					break;

				case _VVM_REGION_LABEL:
					lnPixelsDrawn = ioss_regionDefaultPaintLabel(tr, tr->canvas, tr->canvas->bda, (SRegionLabelData*)tr->data);
					break;

				case _VVM_REGION_CHECKBOX:
					lnPixelsDrawn = ioss_regionDefaultPaintCheckbox(tr, tr->canvas, tr->canvas->bda, (SRegionCheckboxData*)tr->data);
					break;

				case _VVM_REGION_RECTANGLE:
					lnPixelsDrawn = ioss_regionDefaultPaintRectangle(tr, tr->canvas, tr->canvas->bda, (SRegionRectangleData*)tr->data);
					break;

				default:
					// There is no default type that is recognized
					ioss_regionDoDefaultDebugTrapCallback(tr, _VVM_DEBUGTRAP_UNKNOWN_TYPE, lnType);
					break;
			}
		}
		// Indicate how many pixels were drawn
		return(lnPixelsDrawn);
	}




//////////
//
// Called to refresh this region by drawing all sub-regions within
//
//////
	u64 CALLTYPE oss_regionRefresh(SRegion* tr, SRegion* trParent)
	{
		u32					lnPixelsDrawn;
		SStartEndCallback	cb;


		// Prepare our callback
		// Note:  We use cb->count1 for the pixels drawn
		memset(&cb, 0, sizeof(cb));

		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr->canvas)
		{
			//////////
			// Lock the canvas's semaphore for drawing
			//////
//				oss_lockSemaphore(tr->canvas->semRefresh);


			//////////
			// Paint the region
			//////
				// See if it has its own repaint algorithm
				if (tr->callback.region._callback_paint != 0)
				{
					// Custom callback for painting
					cb.count1 += tr->callback.region.callback_paint(tr, tr->canvas, tr->canvas->bd);

				} else {
					// Paint the background
					cb.count1 += oss_canvasFillRect(tr->canvas, tr->canvas->bd, 0, 0, tr->canvas->width, tr->canvas->height, 0, tr->canvas->backColor, tr->canvas->backColor);

					// Use a default drawing algorithm
					cb.count1 += oss_regionDefaultPaint(tr);
				}


			//////////
			// Iterate through any child regions, redrawing them as necessary
			//////
				if (tr->subRegions.masterCount != 0)
				{
					cb._func		= (u64)&ioss_regionRefreshCallback;
					cb.ex2PtrRegion	= trParent;
					oss_SEChain_iterateThroughForCallback(&tr->subRegions, &cb);
				}


			//////////
			// Draw this item onto its parent (if any)
			//////
				if (trParent && trParent->canvas)
				{
					// Paint it onto the parent
					if (tr->canvas->width == tr->width && tr->canvas->height == tr->height)
					{
						// The region is the same size as the canvas, do a literal bitBlt
						cb.count1 += oss_canvasBitBlt(trParent->canvas, false, 
														(s32)(tr->x * (f32)trParent->canvas->width),
														(s32)(tr->y * (f32)trParent->canvas->height),
														tr->canvas, false, 0, 0, tr->canvas->width, tr->canvas->height);

					} else {
						// They are not the same size.  Perfor the scale, and then do the bitBlt
						oss_canvasScale(tr->canvasScale, tr->canvas, &tr->canvasScale->firstScaleMap);
						cb.count1 += oss_canvasBitBlt(trParent->canvas, false, 
														(s32)(tr->x * (f32)trParent->canvas->width),
														(s32)(tr->y * (f32)trParent->canvas->height),
														tr->canvasScale, false, 0, 0, tr->canvasScale->width, tr->canvasScale->height);
					}

					// Mark this region's canvas as no longer being dirty (because it's just been updated)
					tr->canvas->isDirty = false;
				}


			//////////
			// Unlock the canvas's semaphore
			//////
//				oss_unlockSemaphore(tr->canvas->semRefresh);
		}
		// Indicate the number of pixels drawn for this region
		return(cb.count1);
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
// Draws fixed-point (8 x fontHeight) characters onto the canvas.
//
// Returns:
//		Number of pixels drawn, 0 if none, -1 if error, >0 if something new was actually rendered onto the canvas
//
//////
	u64 CALLTYPE oss_canvasDrawFixedPointText(SCanvas* tc, SBGRA* bd, u32 fontWidth, u32 fontHeight, s32 ulx, s32 uly, s8* text, u32 characterCount, SBGRA foreground, SBGRA background)
    {
		u64 lnResult;


		// Make sure the environment is sane
		lnResult = -1;
		if (tc && text)
		{
			// Make sure our count is valid
			if (characterCount == -1)
				characterCount = (u32)oss_strlen(_csu8p(text));

			// Draw the text
			lnResult = ioss_drawFixedPoint(tc, bd, fontWidth, fontHeight, ulx, uly, text, characterCount, foreground, background);

			// Mark the item dirty
			if (lnResult != 0)
				tc->isDirty = true;
		}
		// Indicate success or failure
		return lnResult;
    }




//////////
//
// Draws OSS-specific fonts onto the canvas using the standard ASCII character set.
//
// Returns:
//		-1				- Canvas ID not found
//		-2				- font Handle is invalid
//		characterCount	- success
//
//////
	u64 CALLTYPE oss_canvasDrawText(SCanvas* tc, SBGRA* bd, u64 fontHandle, s32 ulx, s32 uly, s32 lrx, s32 lry, s8* tcText, u32 tnTextLength, SBGRA foreground, SBGRA background)
    {
		u64 lnResult;


// UNTESTED CODE:  breakpoint and examine
		lnResult = 0;
		if (tc)
		{
			// Draw the text
			lnResult = ioss_drawText(tcText, tnTextLength, ulx, uly, lrx, lry, foreground, background, fontHandle, tc->bd_vvmoss);
			if (lnResult > 0)
			{
				// Copy the text drawn onto the system bitmap onto the canvas
				lnResult = oss_lowLevel_bitBlt_ossRgb_onto_canvasBgra(tc->bd_vvmoss, ulx, uly, lrx-ulx, lry-uly, tc, bd);

				// Mark the item dirty
				if (lnResult != 0)
					tc->isDirty = true;
			}

		}
		// Indicate success or failure
		return(lnResult);
    }




//////////
//
// Draws a rectangle frame onto a canvas (no fill).
//
//////
	u64 CALLTYPE oss_canvasFrameRect(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border)
    {
		u8		lnFrameRed, lnFrameGrn, lnFrameBlu;
		s32		lnY, lnX, lnX0, lnY0, lnPixelsDrawn, lnHeight;
		SBGRA*	lrgba;


		// Make sure the environment is sane
		if (!tc || !bd)
			return(-1);

		// Frame colors
		lnFrameRed	= border.red;
		lnFrameGrn	= border.grn;
		lnFrameBlu	= border.blu;

		// Box height
		lnHeight = lry - uly;

		// Draw the rectangle for all pixels that should be drawn vertically
		lnPixelsDrawn = 0;
		for (lnY0 = 0, lnY = uly; lnY < lry; lnY0++, lnY++)
		{
			if (lnY >= 0 && lnY < tc->height)
			{
				// Find out on what row this pixel data will go
				lrgba = bd + (lnY * tc->width) + ulx;

				// Are we drawing the top and bottom part?
				if (lnY0 < borderThickness || lnY0 >= lnHeight - borderThickness)
				{
					// Yes.  This is drawing an entire border across
					for (lnX = ulx; lnX < lrx; lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}

				} else {
					// Nope.  We are drawing three parts:  (1) left-border, (2) fill area, (3) right-border

					// Draw left-border
					for (lnX0 = 0, lnX = ulx; lnX < lrx && lnX0 < borderThickness; lnX0++, lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}

					// Skip filler
// TODO:  Both of these algorithms, frame and fill rect, need to be rewritten to use line segments
					for ( ; lnX < lrx - borderThickness; lnX++)
						++lrgba;

					// Draw right-border
					for ( ; lnX < lrx; lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}
				}
			}
		}

		// Mark the item dirty
		if (lnPixelsDrawn != 0)
			tc->isDirty = true;

		// Indicate how many pixels we drew
		return(lnPixelsDrawn);
    }




//////////
//
// Draws a filled rectangle onto a canvas.
//
//////
	u64 CALLTYPE oss_canvasFillRect(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 borderThickness, SBGRA border, SBGRA background)
    {
		u8		lnFrameRed, lnFrameGrn, lnFrameBlu, lnFillRed, lnFillGrn, lnFillBlu;
		s32		lnY, lnX, lnX0, lnY0, lnPixelsDrawn, lnHeight;
		SBGRA*	lrgba;


		// Make sure the environment is sane
		if (!tc || !bd)
			return(-1);

		// Fill colors
		lnFillRed	= background.red;
		lnFillGrn	= background.grn;
		lnFillBlu	= background.blu;

		// Frame colors
		lnFrameRed	= border.red;
		lnFrameGrn	= border.grn;
		lnFrameBlu	= border.blu;

		// Box height
		lnHeight = lry - uly;

		// Draw the rectangle for all pixels that should be drawn vertically
		lnPixelsDrawn = 0;
		for (lnY0 = 0, lnY = uly; lnY < lry; lnY0++, lnY++)
		{
			if (lnY >= 0 && lnY < tc->height)
			{
				// Find out on what row this pixel data will go
				lrgba = bd + (lnY * tc->width) + ulx;

				// Are we drawing the top and bottom part?
				if (lnY0 < borderThickness || lnY0 >= lnHeight - borderThickness)
				{
					// Yes.  This is drawing an entire border across
					for (lnX = ulx; lnX < lrx; lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}

				} else {
					// Nope.  We are drawing three parts:  (1) left-border, (2) fill area, (3) right-border

					// Draw left-border
					for (lnX0 = 0, lnX = ulx; lnX < lrx && lnX0 < borderThickness; lnX0++, lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}

					// Draw filler
					for ( ; lnX < lrx - borderThickness; lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Fill color
							lrgba->red = lnFillRed;
							lrgba->grn = lnFillGrn;
							lrgba->blu = lnFillBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}

					// Draw right-border
					for ( ; lnX < lrx; lnX++)
					{
						if (lnX >= 0 && lnX < tc->width)
						{
							// Frame color
							lrgba->red = lnFrameRed;
							lrgba->grn = lnFrameGrn;
							lrgba->blu = lnFrameBlu;
							++lnPixelsDrawn;
						}
						// Move to next pixel
						++lrgba;
					}
				}
			}
		}

		// Mark the item dirty
		if (lnPixelsDrawn != 0)
			tc->isDirty = true;

		// Indicate how many pixels we drew
		return(lnPixelsDrawn);
    }




//////////
//
// Draws a line on the canvas.
//
//////
	u64 CALLTYPE oss_canvasLine(SCanvas* tc, SBGRA* bd, s32 p1x, s32 p1y, s32 p2x, s32 p2y, s32 lineThickness, SBGRA line)
    {
		f32		lfI, lfX, lfY, lfDeltaX, lfDeltaY, lfStepI, lfStepX, lfStepY, lfHyp, lfHalfLine;
		f32		lfXP, lfYP, lfStepXP, lfStepYP, lfThetaP;
		s32		lnX0;
		u64		lnPixelsDrawn;
		u8		lnRed, lnGrn, lnBlu;
		SBGRA*	lrgba;


		// Make sure the environment is sane
		if (!tc || !bd || lineThickness < 1)
			return(-1);

		// See what type of line it is
		lnPixelsDrawn	= 0;
		lfHalfLine		= (f32)lineThickness / 2.0f;
		if (p1x == p2x)
		{
			// Vertical line
			lnPixelsDrawn = oss_canvasFillRect(tc, bd, (s32)((f32)p1x - lfHalfLine), min(p1y, p2y), (s32)((f32)p1x + lfHalfLine), max(p1y, p2y), 0, line, line);

		} else if (p1y == p2y) {
			// Horizontal line
			lnPixelsDrawn = oss_canvasFillRect(tc, bd, min(p1x, p2x), (s32)((f32)p1y - lfHalfLine), max(p1x, p2x), (s32)((f32)p1y + lfHalfLine), 0, line, line);

		} else {
			// Arbitrary line
			lfX				= (f32)p1x;
			lfY				= (f32)p1y;
			lfDeltaX		= (f32)p2x - (f32)p1x;
			lfDeltaY		= (f32)p2y - (f32)p1y;
			lfHyp			= sqrt(lfDeltaX*lfDeltaX + lfDeltaY*lfDeltaY);
			lfStepX			= lfDeltaX / lfHyp;
			lfStepY			= lfDeltaY / lfHyp;
			lfStepI			= 1.0f / lfHyp;

			// Compute slope
			if (lineThickness != 1)
			{
				lfThetaP		= atan2(-lfDeltaX, lfDeltaY);		// Get theta for X
				lfStepXP		= cos(lfThetaP) / 3.0f;
				lfStepYP		= sin(lfThetaP) / 3.0f;
				lfHalfLine		= lfHalfLine * 3.0f;
				lineThickness	= lineThickness * 3;
			}

			// Grab the colors
			lnRed		= line.red;
			lnGrn		= line.grn;
			lnBlu		= line.blu;

			// Iterate for every pixel along the hypotenuse
			for (	lfI = 0;
					lfI < 1.0f;
					lfI += lfStepI, lfX += lfStepX, lfY += lfStepY	)
			{
				// Are we on the canvas vertically?
				if (lfY >= 0.0f && (s32)lfY < tc->height)
				{
					// Based on our line thickness, we use one of two formulas
					if (lineThickness != 1)
					{
						// Do the perpendicular slope for the line, one point at a time
						lfXP = lfX - (lfHalfLine * lfStepXP);
						lfYP = lfY - (lfHalfLine * lfStepYP);
						for (lnX0 = 0; lnX0 < lineThickness; lnX0++, lfXP += lfStepXP, lfYP += lfStepYP)
						{
							// Find out on what row this pixel data will go
							lrgba = bd + ((s32)lfYP * tc->width) + (s32)lfXP;

							// Store the color
							lrgba->red	= lnRed;
							lrgba->grn	= lnGrn;
							lrgba->blu	= lnBlu;

							// Increase our pixel drawn count
							++lnPixelsDrawn;
						}

					} else {
						// Are we on the canvas horizontally?
						if (lfX >= 0.0f && (s32)lfX < tc->width)
						{
							// Find out on what row this pixel data will go
							lrgba = bd + ((s32)lfY * tc->width) + (s32)lfX;

							// Store the color
							lrgba->red	= lnRed;
							lrgba->grn	= lnGrn;
							lrgba->blu	= lnBlu;

							// Increase our pixel drawn count
							++lnPixelsDrawn;
						}
					}
				}
			}
		}

		// Mark the item dirty
		if (lnPixelsDrawn != 0)
			tc->isDirty = true;

		// Indicate how many pixels were updated
		return(lnPixelsDrawn);
    }




//////////
//
// Draws an arc on the canvas.
//
//////
	u64 CALLTYPE oss_canvasArc(SCanvas* tc, SBGRA* bd, s32 ox, s32 oy, f32 radius, f32 start, f32 end, s32 lineThickness, SBGRA line)
    {
		// Make sure the environment is sane
		if (!tc || !bd)
			return(-1);

		// Make sure our start and end are within 0..2pi
//		start	= fmod(start,	_2PI);
//		end		= fmod(end,		_2PI);


		return(-1);
    }




//////////
//
// Extracts a portion of a canvas, creating a new canvas.
//
//////
	SCanvas* CALLTYPE oss_canvasExtract(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry)
    {
		s32			lnWidth, lnHeight;
		SCanvas*	lc;


		// Make sure the environment is sane
		if (tc && bd && ulx < lrx && uly < lry)
		{
			// Create the canvas
			lnWidth		= lrx - ulx;
			lnHeight	= lry - uly;
// TODO: Possible bug observed here, with the tc->state.useTransparency setting possibly not being honored
			lc			= oss_createCanvas(tc->ll.uniqueId, (u32)lnWidth, (u32)lnHeight, tc->backColor);

			// Copy the bitmap data
			if (lc)
				oss_canvasBitBlt(lc, false, 0, 0, tc, false, ulx, uly, lrx, lry);
			
			// Indicate our success or failure
			return(lc);
		}
		return(NULL);
    }




//////////
//
// Converts the canvas rectangle to grayscale, and then applies the specified color
// to the entire area.
//
//////
	u64 CALLTYPE oss_canvasColorize(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry, SBGRA color)
    {
		u64		lnPixelsDrawn;
		s32		lnY, lnX;
		f32		lfGray, lfRed, lfGrn, lfBlu;
		SBGRA*	lrgba;


		// Make sure the environment is sane
		if (!tc || !bd)
			return(-1);

		// Get the colors
		lfRed = (f32)color.red;
		lfGrn = (f32)color.grn;
		lfBlu = (f32)color.blu;

		// Iterate through every pixel in the rectangle
		lnPixelsDrawn = 0;
		for (lnY = uly; lnY < lry; lnY++)
		{
			if (lnY >= 0 && lnY < tc->height)
			{
				// Find out on what row this pixel data will go
				lrgba = bd + (lnY * tc->width) + ulx;

				// We are drawing an entire border across
				for (lnX = ulx; lnX < lrx; lnX++)
				{
					if (lnX >= 0 && lnX < tc->width)
					{
						// Compute the grayscale percentage
						lfGray	= (((f32)lrgba->red * 0.35f) + ((f32)lrgba->grn * 0.54f) + ((f32)lrgba->blu * 0.11f)) / 255.0f;

						// Convert to that color
						lrgba->red = (u8)(lfGray * lfRed);
						lrgba->grn = (u8)(lfGray * lfGrn);
						lrgba->blu = (u8)(lfGray * lfBlu);

						// Increase our pixel modified count
						++lnPixelsDrawn;
					}
					// Move to next pixel
					++lrgba;
				}
			}
		}

		// Mark the item dirty
		if (lnPixelsDrawn != 0)
			tc->isDirty = true;

		// Return the number of pixels colorized
		return(lnPixelsDrawn);
    }




//////////
//
// Converts the canvas rectangle to grayscale.
//
//////
	u64 CALLTYPE oss_canvasGrayscale(SCanvas* tc, SBGRA* bd, s32 ulx, s32 uly, s32 lrx, s32 lry)
    {
		u8		lnGray;
		u64		lnPixelsDrawn;
		s32		lnY, lnX;
		SBGRA*	lrgba;


		// Make sure the environment is sane
		if (!tc || !bd)
			return(-1);

		// Iterate through every pixel in the rectangle
		lnPixelsDrawn = 0;
		for (lnY = uly; lnY < lry; lnY++)
		{
			if (lnY >= 0 && lnY < tc->height)
			{
				// Find out on what row this pixel data will go
				lrgba = bd + (lnY * tc->width) + ulx;

				// We are drawing an entire border across
				for (lnX = ulx; lnX < lrx; lnX++)
				{
					if (lnX >= 0 && lnX < tc->width)
					{
						// Compute the grayscale percentage
						lnGray = (u8)(((f32)lrgba->red * 0.35f) + ((f32)lrgba->grn * 0.54f) + ((f32)lrgba->blu * 0.11f));

						// Convert to that color
						lrgba->red = lnGray;
						lrgba->grn = lnGray;
						lrgba->blu = lnGray;

						// Increase our pixel modified count
						++lnPixelsDrawn;
					}
					// Move to next pixel
					++lrgba;
				}
			}
		}

		// Mark the item dirty
		if (lnPixelsDrawn != 0)
			tc->isDirty = true;

		// Return the number of pixels colorized
		return(lnPixelsDrawn);
    }




//////////
//
// Creates a gradient of the indicated colors.
// Note:  Goes from bd to bd, does not use accumulator.
//
//////
	u64 CALLTYPE oss_canvasGradient(SCanvas* tc, SBGRA* bd, SBGRA ul, SBGRA ur, SBGRA lr, SBGRA ll)
	{
		u64 lnPixelsDrawn;


		// Make sure the environment is sane
		if (tc && bd && (bd == tc->bd || bd == tc->bda))
		{
			// Perform the gradient
			lnPixelsDrawn = iioss_gradient(tc, bd, ul, ur, lr, ll);

			// Mark the item dirty
			if (lnPixelsDrawn != 0)
				tc->isDirty = true;
		}

		// Indicate failure
		return(-1);
	}




//////////
//
// Overlay or alpha blend the specified canvas onto the destination canvas.
//
//////
	u64 CALLTYPE oss_canvasBitBlt(SCanvas* tsDst, bool tlDstAccumulator, s32 dulx, s32 duly, SCanvas* tsSrc, bool tlSrcAccumulator, s32 sulx, s32 suly, s32 slrx, s32 slry)
    {
		u64 lnPixelsDrawn;


		// Make sure the environment is sane
		if (tsDst && tsSrc)
		{
			// perform the copy
			lnPixelsDrawn = ioss_bitBltSection(tsDst, tlDstAccumulator, dulx, duly, tsSrc, tlSrcAccumulator, sulx, suly, slrx, slry);

			// Mark the item dirty
			if (lnPixelsDrawn != 0)
				tsDst->isDirty = true;
		}

		// If we get here, invalid data
		return(-1);
    }




//////////
//
// Called to scale a canvas from the src size to the dst size
//
//////
	u64 CALLTYPE oss_canvasScale(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap** tsScaleMap)
	{
		u64 lnPixelsDrawn;


		// Make sure the environment is sane
		if (tsDst && tsSrc && tsDst->bd && tsSrc->bd && tsScaleMap)
		{
			// Perform the scale
			lnPixelsDrawn = iioss_canvasScale(tsDst, tsSrc, tsScaleMap);

			// Mark the item dirty
			if (lnPixelsDrawn != 0)
				tsDst->isDirty = true;
		}

		// If we get here, failure
		return(0);
	}




//////////
//
// Refreshes the screen (draws all regions within)
//
//////
	u64 CALLTYPE oss_screenRefresh(SScreen* ts)
    {
		u64					lnPixelsDrawn;
		_iswSOssWindowLL*	w;



		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (ts && ts->activeRegion && ts->activeRegion->canvas)
		{
			// Refresh this region
			if (oss_regionRefresh(ts->activeRegion, NULL) != 0)
			{
				// Something was updated, refresh this screen
				w = ioss_find_iswSOssWindowLL_By_iOssWindowId(ts->_iOssWindowId);
				if (w)
				{
					// See if the window is the same size
					if (w->isw.width == ts->activeRegion->canvas->width && w->isw.height == ts->activeRegion->canvas->height)
					{
						// They are the same size, use the standard window drawing
						lnPixelsDrawn = oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb(ts->_iOssWindowId, ts->activeRegion->canvas->bd, ts->activeRegion->canvas->width, ts->activeRegion->canvas->height);

					} else {
						// They are not the same size, scale the canvas up/down to the destination size, and then draw
						oss_canvasScale(ts->activeRegion->canvasScale, ts->activeRegion->canvas, &ts->activeRegion->canvasScale->firstScaleMap);
						lnPixelsDrawn = oss_lowLevel_bitBlt_CanvasBgra_onto_ossRgb(ts->_iOssWindowId, ts->activeRegion->canvasScale->bd, ts->activeRegion->canvasScale->width, ts->activeRegion->canvasScale->height);
					}
				}
			}
		}
		// Indicate our success or failure
		return(lnPixelsDrawn);
    }




//////////
//
// Called to specify that the indicated screen should have keyboard focus
//
//////
	bool CALLTYPE oss_screenSetFocus(SScreen* ts)
	{
		_iswSOssWindowLL* low;


		// Make sure the environment is sane
		if (ts)
		{
			// Make sure the screen they indicated is valid
			low = ioss_findSOssWindowLLByScreenId(ts->_iOssWindowId);
			if (low)
			{
				// Sends the WM_SETFOCUS message so it hits the window-owner thread, which then
				// signals the events for change of focus
				SetFocus((HWND)low->isw.osHandle);
				return(true);
			}
		}

		// The window wasn't found
		return(false);
	}




//////////
//
// Refreshes the canvas (draws its accumulator buffer onto its main buffer)
//
//////
	u64 CALLTYPE oss_canvasRefresh(SCanvas* tc)
	{
		u64 lnPixelsDrawn;
		

		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tc && tc->bd && tc->bda)
			lnPixelsDrawn = oss_canvasBitBlt(tc, false, 0, 0, tc, true, 0, 0, tc->width, tc->height);

		return(lnPixelsDrawn);
	}




//////////
//
// Refer to the _VVMOSS_CASK_* constants.
// Creates a cask of the indicated size and style:
//     Round:         (|name|)
//     Square:        [|name|]
//     Diamond:       <|name|>
//
// States allow various sizes (shown here as round, but is the same for all types):
//     Closed:         ()
//     Minimal:        (|)
//     Text:           (|text|)
//     Extended text:  (|=left=|text|=right=|)
//
// There may or may not be pips on each side.  Pip counts must be 0 through 3.
//
//////
	SCask* CALLTYPE oss_caskDefineStandard(u32 tnHeight, u32 tnWidth,
		                                   u32 tnLeftStyle,  u32 tnLeftState,  u32 tnLeftPipCount,  u32 tnLeftColor,  csu8p tcLeftText,
		                                   u32 tnRightStyle, u32 tnRightState, u32 tnRightPipCount, u32 tnRightColor, csu8p tcRightText)
	{
		return(NULL);
	}




//////////
//
// Create an encompassing rectangle cask, which has a form like:
//
//     (|+====--------------------==+|]
//      \|                          |/
//       |                          |
//       |                          |
//       |                          |
//       |                          |
//       +====--------------------==+
//
//////
	SCask* CALLTYPE oss_caskDefineEncompassingRectangle(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SRectXYXY* tsOuter)
	{
		return(NULL);
	}




//////////
//
// Create an up rectangle cask, which goes up from a cask, or from a particular pip on a cask.
// It has the form like:
//
//     +===---------------------------------==+
//     |                                      |
//     |                                      |
//     +===---------------------------------==|
//     ||
//  (|P||text|)
//
//////
	SCask* CALLTYPE oss_caskDefineUpRectangle(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter)
	{
		return(NULL);
	}




//////////
//
// Create an up rectangle cask, which goes up from a cask, or from a particular pip on a cask.
// It has the form like:
//
//  (|text||P|)
//        ||
//        +===---------------------------------==+
//        |                                      |
//        |                                      |
//        +===---------------------------------==|
//
//////
	SCask* CALLTYPE oss_caskDefineDownRectangle(u32 tnInnerWidth, u32 tnInnerHeight, u32 tnColor, SCask* caskFrom, u32 tnFromPip, SRectXYXY* tsOuter)
	{
		return(NULL);
	}




//////////
//
// Cask Pips do not have to exist.  If they do not exist then the cask itself is made somewhat
// less wide, and does not respond to mouse events in the pip area, apart from the normal
// operation.
//
//////
	SCaskPip* CALLTYPE oss_caskSetPipByValues(SCask* cask, bool tlLeft, u32 tnPip, SBGRA tnPipColorNeutral, SBGRA tnPipColorOver, SBGRA tnPipColorClick, u64 tnEnterCallback, u64 tnLeaveCallback, u64 tnHoverCallback, u64 tnClickCallback, bool tlCreateCopy)
	{
		return(NULL);
	}




//////////
//
// Cask
//
//////
	SCaskPip* CALLTYPE oss_caskSetPipByStruct(SCask* cask, bool tlLeft, u32 tnPip, SCaskPip* caskPip, bool tlCreateCopy)
	{
		return(NULL);
	}




//////////
//
// Cask
//
//////
	SCask* CALLTYPE oss_caskCreate(SCask* cask, bool tlCreateCopy)
	{
		return(NULL);
	}




//////////
//
// Cask
//
//////
	SCanvas* CALLTYPE oss_caskRefresh(SCask* cask)
	{
		return(NULL);
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
			lsf = (_iswSSystemFont*)oss_SEChain_append(&gseRootFonts, 0, ioss_getNextUniqueId(), sizeof(_iswSSystemFont), _COMMON_START_END_BLOCK_SIZE, NULL);
			if (lsf)
			{
				// Prepare our structure
				lnUniqueId			= ioss_getNextUniqueId();

				// Store the identifier into
				lsf->ll.uniqueId	= lnUniqueId;
				lsf->handle			= lf;

				// Store the font's attributes
				lsf->fontName		= (s8*)oss_duplicateString((u8*)fontName, max(strlen(fontName), 128));
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
		lsf = (_iswSSystemFont*)oss_SEChain_searchByCallback(&gseRootFonts, &cb);

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
				tnCaptionLength = (u32)oss_strlen(_csu8p(tcCaption));

			// Visible identifier
			tisw->caption			= (s8*)oss_duplicateString((u8*)tcCaption, tnCaptionLength + 1);
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
				oss_SEChain_delete(&lse, NULL, 0, true);
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
			oss_SEChain_iterateThroughForCallback(tsMonitors, &cb);

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
		_iswSOssWindowLL* low;


		// Make sure the screen they indicated is valid
		low = ioss_find_iswSOssWindowLL_By_iOssWindowId(tnOssWindowId);
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
		_iswSOssWindowLL* w;


		// Make sure the screen they indicated is valid
		w = ioss_find_iswSOssWindowLL_By_iOssWindowId(tnOssWindowId);
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
// 		ldll = (SDatumLL*)oss_SEChain_append(&gseRootMemoryBlocks, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SDatumLL), _COMMON_START_END_BLOCK_SIZE, NULL);
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
// 					oss_memset(ldll->datum.data._s8, 0, tnSize);
// 
// 				// Indicate our success
// 				return(ldll->datum.data._v);
// 			}
// 			// Failure!
// 			oss_SEChain_deleteFrom(&gseRootMemoryBlocks, (SLL*)ldll, true);
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
// 		ldll = (SDatumLL*)oss_SEChain_searchByCallback(&gseRootMemoryBlocks, &cb);
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
		ldll = (SDatumLL*)oss_SEChain_searchByCallback(&gseRootMemoryBlocks, &cb);
		if (!ldll)
			return(NULL);		// It's not one of our pointers, tisk, tisk!


		// Free the memory
		free(ptr);


		// Delete its associated entry in the chain
		oss_SEChain_deleteFrom(&gseRootMemoryBlocks, (SLL*)ldll, true);


		// Indicate success
		return((void*)0);
	}




//////////
//
// Called to perform a wildcard match.  Uses repeated sequences, as in:
//
// Wildcard:	*rick*c*hodgin*
// Search:		Frederick C. Hodgin, III
// Result:		Would search for and find "Frede[rick] [C]. [Hodgin], III" within and return a match.
//
// Returns:
//		-3		-- Invalid candidate or wildcardPattern provided
//		-2		-- Syntax error in wildcardPattern
//		-1		-- candidate is less than wildcardPattern
//		0		-- candidate matches wildcardPattern
//		1		-- candidate is greater than wildcardPattern
//
///////
	s32 CALLTYPE oss_wildcardMatchDatum(SDatum* tsCandidate, SDatum* tsWildcardPattern, bool tlCaseSensitive)
	{
		return(oss_wildcardMatch(_csu8p(tsCandidate->data._u8), _csu8p(tsWildcardPattern->data._u8), tlCaseSensitive));
	}

	s32 CALLTYPE oss_wildcardMatch(csu8p candidate, csu8p wildcardPattern, bool tlCaseSensitive)
	{
		u8		c, w;
		u32		lnC, lnW, lnNeedleLength, lnFoundPosition;
		bool	llWildcardFound;
		csu8p	needle, haystack;


// TODO:  breakpoint and examine
_asm nop;
		// Make sure the environment is sane
		if (candidate._u8 && wildcardPattern._u8)
		{
			// Repeat for every character in the wildcardPattern
			llWildcardFound = false;
			for (lnC = 0, lnW = 0;	wildcardPattern._u8[lnW] != 0;	)
			{
				//////////
				// Grab the characters
				//////
					c = candidate._u8[lnC];
					w = wildcardPattern._u8[lnW];


				//////////
				// Based on the wildcardPattern, try it
				//////
					if (w == '?')
					{
						// c can be anything, we accept it as is
						llWildcardFound = true;
						++lnC;					// Increment in candidate
						++lnW;					// Increment in wildcardPattern


					} else if (w == '*') {
						// The rest of c can be anything, unless there is something more in w after the asterisk
						llWildcardFound = true;
						if (wildcardPattern._u8[lnW + 1] == 0)
						{
							// We're done, the rest of candidate can be anything
							return(0);		// Match

						} else if (wildcardPattern._u8[lnW + 1] == '*' || wildcardPattern._u8[lnW + 1] == '?') {
							// Syntax error
							return(-2);

						} else {
							// We skip forward to the next part of wildcardPattern is matched
							++lnW;


							//////////
							// Find out how long the next part of wildcardPattern is
							//////
								lnNeedleLength = 0;
								do {
									// Are we done with the wildcard?
									if (wildcardPattern._u8[lnW + lnNeedleLength] == 0)
									{
										// Yes
										break;

									// Have we reached a terminating character for this leg?
									} else if (wildcardPattern._u8[lnW + lnNeedleLength] == '?' || wildcardPattern._u8[lnW + lnNeedleLength] == '*') {
										// Yes
										break;

									} else {
										// Continuing onward and upward
										++lnNeedleLength;
									}
								} while(1);


							//////////
							// We have the length of the part after the * now
							//////
								if (lnNeedleLength == 0)
								{
									// We reached the end of the wildcardPattern, which means this is a match
									return(0);		// The candidate was a match

								} else {
									// We have a segment to match up

									// Setup the needle and haystack
									needle		= _csu8p(wildcardPattern._u8	+ lnW);
									haystack	= _csu8p(candidate._u8			+ lnC);

									// Search forward for it
									if (!oss_isNeedleInHaystack(haystack, (u32)oss_strlen(candidate) - lnC, needle, lnNeedleLength, tlCaseSensitive, &lnFoundPosition))
										return(-1);		// Not found, the candidate is less than the wildcardPattern

									// If we get here, then it was found, so we continue on
									lnC += lnNeedleLength + lnFoundPosition;	// Candidate moves forward by the wildcardPattern length of this section, plus the found content
									lnW += lnNeedleLength;						// Move past the length of this section
								}
						}


					} else {
						// We're doing a character-by-character comparison
						if (!tlCaseSensitive)
						{
							// Case in-sensitive
							if (c >= 'A' && c <= 'Z')		c |= 0x20;		// Convert it to lower-case
							if (w >= 'A' && w <= 'Z')		w |= 0x20;		// Convert it to lower-case
							// Right now, case is adjusted
						}

						// Do the compare
						if (c != w)
						{
							// Something doesn't match
							if (c < w)		return(-1);		// The candidate is less than the wildcard
							else			return(1);		// The candidate is greater than the wildcard
						}
						// If we get here, still a match
						++lnC;
						++lnW;
					}
			}
			// When we get here, the wildcardPattern is done being searched

			// Are we done scanning the candidate yet?
			if (candidate._u8[lnC] == 0)
			{
				// Yes, everything matched
				// It may still not be a match though if the strings are not the same length
				if (llWildcardFound)
				{
					// The lengths must match to be a match
					return(oss_strlen(candidate) == oss_strlen(wildcardPattern));

				} else {
					// It was a match
					return(0);
				}

			} else {
				// Nope, it didn't match, the candidate is greater than the wildcardPattern
				return(1);
			}

		} else {
			// Something's awry
			return(-3);
		}
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
						line = (SOssLine*)oss_SEChain_append(tseLines, ioss_getNextUniqueId(), ioss_getNextUniqueId(), sizeof(SOssLine), _COMMON_START_END_BLOCK_SIZE, NULL);


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
									if (line->extra)		oss_memset((s8*)line->extra, 0, tnAllocSize);
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
		bool					llSigned;
		SOssComp*				compFirst;
		SOssComp*				compLast;
		SOssComp*				comp;
		s8*						lcData;
		SAsciiCompSearcher*		lacs;


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
							// It matches, mark its current condition
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
								comp = (SOssComp*)oss_SEChain_append(&line->comps, ioss_getNextUniqueId(), ioss_getNextUniqueId(), sizeof(SOssComp), _COMMON_START_END_SMALL_BLOCK_SIZE, NULL);


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
		oss_SEChain_searchByCallback(&line->comps, &cb);
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
			oss_memset(buffer, 32, sizeof(buffer));

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
						oss_memcpy(buffer, line->base + line->start, line->whitespace);

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
							oss_memcpy(buffer + lnStart, line->base + line->start + lnStart, lnLength);
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
					oss_memset(buffer, 32, lnMaxLength);
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
							oss_memcpy(buffer + lnBufLength, line->base + line->start + lnStart, lnLength);
							lnBufLength += lnLength;
						}

						// Close the comp
						buffer[lnBufLength++] = ']';

						// Write the component contents
						oss_sharedAsciiWriteFile(lnHandle, buffer, lnBufLength);
						lnBytesWritten += lnBufLength;

						// Reset the portion we just used
						oss_memset(buffer, 0, lnBufLength);

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
							oss_SEChain_completelyMigrateSLLByPtr(&line->compsCombined, &line->comps, (SLL*)comp2, 0, _COMMON_START_END_BLOCK_SIZE);

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
							oss_SEChain_completelyMigrateSLLByPtr(&line->compsCombined, &line->comps, (SLL*)comp2, 0, _COMMON_START_END_BLOCK_SIZE);
							oss_SEChain_completelyMigrateSLLByPtr(&line->compsCombined, &line->comps, (SLL*)comp3, 0, _COMMON_START_END_BLOCK_SIZE);

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
								oss_SEChain_completelyMigrateSLLByPtr(&line->compsCombined, &line->comps, (SLL*)compNext, 0, _COMMON_START_END_BLOCK_SIZE);

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
							oss_SEChain_completelyMigrateSLLByPtr(&line->compsCombined, &line->comps, (SLL*)compNext, 0, _COMMON_START_END_BLOCK_SIZE);

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
		_iswSSharedFile* lsf = (_iswSSharedFile*)oss_SEChain_append(&gseRootForeignFiles, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(_iswSSharedFile), _COMMON_START_END_BLOCK_SIZE, NULL);
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
		lsf = (_iswSSharedFile*)oss_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
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
		lsf = (_iswSSharedFile*)oss_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
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
		lsf = (_iswSSharedFile*)oss_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
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
		lsf = (_iswSSharedFile*)oss_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
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
			lsfl = (_iswSSharedFileLocks*)oss_SEChain_append(&lsf->locks, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(_iswSSharedFileLocks), _COMMON_START_END_BLOCK_SIZE, NULL);
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
		lsf = (_iswSSharedFile*)oss_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
		if (!lsf)	return(-1);			// Invalid file handle

		lsfl = (_iswSSharedFileLocks*)oss_SEChain_searchByUniqueId(&lsf->locks, tnLockHandle);
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
			oss_SEChain_deleteFrom(&lsf->locks, (SLL*)lsfl, true);

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
		lsf = (_iswSSharedFile*)oss_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
		if (!lsf)	return(-1);			// Invalid file handle

		// Close the handle
		_close(lsf->handle);

		// Delete any locks, with a callback to unlock any active locks
		oss_SEChain_delete(&lsf->locks, (u64)&iioss_sharedAsciiCloseFileLocksCallback, (u64)lsf, true);

		// Delete this entry
		oss_SEChain_deleteFrom(&gseRootForeignFiles, (SLL*)lsf, true);

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
		lsf = (_iswSSharedFile*)oss_SEChain_searchByUniqueId(&gseRootForeignFiles, tnFileHandle);
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
// Duplicate the indicated ASCII string
//
//////
	u8* CALLTYPE oss_duplicateString(u8* ptr, u64 length)
	{
		u8* ptrNew;


		// Make sure our environment is sane
		ptrNew = NULL;
		if (ptr && length < 0xffffffff)
		{
			// Try to create the new string
			ptrNew = (u8*)malloc((u32)length + 1);

			//  Copy the string if successful
			if (ptrNew)
			{
				// Copy the string and null-terminate it
				memcpy(ptrNew, ptr, (u32)length);
				ptrNew[(u32)length] = 0;
			}
		}
		// All done
		return(ptrNew);
	}




//////////
//
// Duplicate the unicode string
//
//////
	w16* CALLTYPE oss_duplicateUnicodeString(w16* tuText)
	{
		u32		tnLength;
		w16*	tuNewText;


		// Make sure our environment is sane
		tuNewText = NULL;
		if (tuText)
		{
			// Get the length
			tnLength = wcslen(tuText) * sizeof(w16);

			// Allocate that much space
			tuNewText = (w16*)malloc(tnLength);

			// If we're good, complete the copy
			if (tuNewText)
				memcpy(tuNewText, tuText, tnLength);
		}
		// Indicate our status
		return(tuNewText);
	}




//////////
//
// Duplicate and store to a datum structure
//
//////
	SDatum* CALLTYPE oss_datumSet(SDatum* datum, u8* ptr, u64 length, bool tlFreeExisting)
	{
		u8* lptr;


		// Make sure our environment is sane
		if (datum)
		{
			// Do they want us to set the length?
			if (length == -1)
				length = oss_strlen(_csu8p(ptr));

			// Is there anything to do?
			if (length != 0)
			{
				// If there is already a value here, free it up
				if (tlFreeExisting && datum->data._u8)
				{
					// Grab the pointer
					lptr				= datum->data._u8;

					// Indicate it is NULL in the structure (in case a task switch happens right now)
					datum->data._u8		= NULL;
					datum->length		= 0;

					// Release the allocated memory
					free(lptr);
				}

				if (ptr)
				{
					// Duplicate the string
					datum->data._u8 = oss_duplicateString(ptr, length);

				} else {
					// Create a blank string and initialize it to NULLs
					datum->data._u8 = (u8*)malloc((u32)length);
					if (datum->data._u8)
						memset(datum->data._u8, 0, (u32)length);
				}

				// Verify our string was allocated properly
				if (datum->data._u8)
				{
					// Set the length
					datum->length = length;

				} else {
					// Indicate it failed
					datum->length = 0;
				}

			} else {
				// Initialize it to NULL
				datum->data._u8		= NULL;
				datum->length		= 0;
			}
		}
		return(datum);
	}




//////////
//
// Duplicate and store to a datum2 structure
//
//////
	SDatum2* CALLTYPE oss_datum2Set(SDatum2* datum2, u8* ptr, u64 length, u64 lengthTotal, bool tlFreeExisting)
	{
		// Make sure our environment is sane
		if (datum2)
		{
			// Do they want us to set the length?
			if (length == -1)
				length = oss_strlen(_csu8p(ptr));

			// Is there anything to do?
			if (length != 0)
			{
				// Duplicate the datum string
				oss_datumSet(&datum2->datum, ptr, length, tlFreeExisting);

				// Update our totals if the string was allocated appropriately
				if (datum2->datum.data._u8)
				{
					// We allocated and copied correctly
					datum2->lengthTotal	= lengthTotal;

				} else {
					// We did not, so this string is not valid
					datum2->lengthTotal	= 0;
				}

			} else {
				// They are clearing out whatever is already there
				oss_datumDelete(&datum2->datum);

				// Initialize it to NULL
				datum2->lengthTotal	= lengthTotal;
			}
		}
		return(datum2);
	}




//////////
//
// Duplicates a datum into another datum
//
//////
	SDatum* CALLTYPE oss_datumDuplicate(SDatum* datumDst, SDatum* datumSrc)
	{
		// Make sure our environment is sane
		if (datumDst && datumSrc && datumSrc->data._u8 && datumSrc->length != 0)
		{
			// If it's already populated, release it
			if (datumDst->data._u8)
				free(datumDst->data._u8);

			// Copy the item
			datumDst->data._u8 = oss_duplicateString(datumSrc->data._u8, datumSrc->length);

			// If it was copied, update the length
			if (datumDst->data._u8)
			{
				// Store the length
				datumDst->length = datumSrc->length;

			} else {
				// Indicate it failed
				datumDst->length = 0;
			}
		}
		return(datumDst);
	}




//////////
//
// Duplicates a datum2 into another datum2
//
//////
	SDatum2* CALLTYPE oss_datum2Duplicate(SDatum2* datum2Dst, SDatum2* datum2Src)
	{
		// Make sure our environment is sane
		if (datum2Dst && datum2Src && datum2Src->datum.data._u8 && datum2Src->datum.length != 0)
		{
			// If it's already populated, release it
			if (datum2Dst->datum.data._u8)
				free(datum2Dst->datum.data._u8);

			// Copy the item
			datum2Dst->datum.data._u8 = oss_duplicateString(datum2Src->datum.data._u8, datum2Src->datum.length);

			// If it was copied, update the length
			if (datum2Dst->datum.data._u8)
			{
				// Success
				datum2Dst->datum.length		= datum2Src->datum.length;
				datum2Dst->lengthTotal		= datum2Src->lengthTotal;

			} else {
				// Failure
				datum2Dst->datum.length		= 0;
				datum2Dst->lengthTotal		= 0;
			}
		}
		return(datum2Dst);
	}




//////////
//
// Deletes the indicated datum
//
//////
	void CALLTYPE oss_datumDelete(SDatum* datum)
	{
		if (datum)
		{
			if (datum->data._u8)
			{
				// Free the memory
				free(datum->data._u8);

				// Reset the datum structure
				datum->data._u8 = NULL;
			}

			// Reset the length
			datum->length = 0;
		}
	}




//////////
//
// Delete the indicated datum2
//
//////
	void CALLTYPE oss_datum2Delete(SDatum2* datum2)
	{
		if (datum2 && datum2->datum.data._u8)
		{
			// Free the memory
			oss_datumDelete(&datum2->datum);

			// Reset the datum2 total size
			datum2->lengthTotal	= 0;
		}
	}




//////////
//
// Allocate an empty string into datum2
//
//////
	void CALLTYPE oss_datum2SetNullString(SDatum2* datum2, u64 length, bool tlInitialize)
	{
		// Make sure our environment is sane
		if (datum2)
		{
			if (length != 0)
			{
				// Create the string space
				datum2->datum.data._u8 = (u8*)malloc((u32)length);		// Note:  This function does not automatically allocate the trailing NULL as the iDuplicateStringIntoDatum() function does
				if (datum2->datum.data._u8)
				{
					// We're good, set up the length
					datum2->datum.length	= length;
					datum2->lengthTotal		= length;

					// Set it to NULLs if we need to
					if (tlInitialize)
						memset(datum2->datum.data._u8, 0, (u32)length);

				} else {
					// Store the length value of 0
					datum2->datum.length	= 0;
					datum2->lengthTotal		= 0;
				}

			} else {
				// Initialize it to NULL
				datum2->datum.data._u8		= NULL;
				datum2->datum.length		= 0;
				datum2->lengthTotal			= 0;
			}
		}
	}




//////////
//
// Copy up to the shortest string of the two from source to destination
//
//////
	void CALLTYPE oss_copyUpToShortestString(u8* dst, u32 tnDstLength, u8* src, u32 tnSrcLength)
	{
		u32 lnI;


		// Copy as many characters as are allowed
		for (lnI = 0; lnI < tnDstLength && lnI < tnSrcLength; lnI++)
			dst[lnI] = src[lnI];
	}




//////////
//
// ASCII to unicode conversion
//
//////
	w16* CALLTYPE oss_asciiToUnicode(u8* tcText, u32 tnTextLength)
	{
		u32		lnI;
		w16*	luOut;


		// Allocate 2 bytes for every ascii byte, plus 2 more for the trailing s16 null
		luOut = (w16*)malloc((tnTextLength * 2) + 2);
		if (luOut)
		{
			// Convert to 16-bit forms
			for (lnI = 0; lnI < tnTextLength; lnI++)
				luOut[lnI] = (w16)tcText[lnI];

			// Append an extra trailing null
			luOut[lnI] = 0;
		}
		return(luOut);
	}




//////////
//
// Unicode to ASCII conversion
//
//////
	s8* CALLTYPE oss_unicodeToAscii(w16* tuText, u32 tnTextLength)
	{
		u32		lnI;
		s8*		lcOut;


		// Allocate 2 bytes for every ascii byte, plus 2 more for the trailing s16 null
		lcOut = (s8*)malloc(tnTextLength + 1);
		if (lcOut)
		{
			// Convert to 16-bit forms
			for (lnI = 0; lnI < tnTextLength; lnI++)
				lcOut[lnI] = (s8)tuText[lnI];

			// Append an extra trailing null
			lcOut[lnI] = 0;
		}
		return(lcOut);
	}




//////////
//
// Convert a single ASCII character to unicode
//
//////
	w16 CALLTYPE oss_asciiToUnicodeChar(u8 tcChar)
	{
		return((w16)tcChar);
	}




//////////
//
// Convert unicode to single ASCII
//
//////
	s8 CALLTYPE oss_unicodeToAsciiCharacter(w16 tuChar)
	{
		return((s8)tuChar);
	}




//////////
//
// Scans forward in the indicated string until the character changes, or until the maximum
// length is reached.
//
//////
	u64 CALLTYPE oss_scanForwardUntilCharacterChanges(csu8p tcData, u64 tnMaxLength)
	{
		u64 lnI;


		// Make sure our environment is sane
		lnI = 0;
		if (tcData._cu8 && tnMaxLength != 0)
		{
			// Continue comparing every character
			for (++lnI; lnI < tnMaxLength; lnI++)
			{
				// If the character changes, we're done
				if (tcData._cu8[lnI] != tcData._cu8[0])
					return(lnI);		// We're done
			}
		}
		// When we get here, lnI is how far we skipped
		return(lnI);
	}




//////////
//
// Scan forward until the indicated character is found without regards to length
//
//////
	u64 CALLTYPE oss_scanForwardUntilCharacter(csu8p tcData, s8 c)
	{
		u64 lnI;


		// Scan through the data
		lnI = 0;
		if (tcData._cu8)
		{
			for ( ; tcData._cu8[lnI] != c; )
				++lnI;
		}
		// Indicate our length
		return(lnI);
	}




//////////
//
// Unicode memory compare
//
//////
	int CALLTYPE oss_unicodeMemcmp(w16* l, w16* r, u32 tnLength)
	{
		u32 lnI;


		// For every character in the length, compare left to right
		for (lnI = 0; lnI < tnLength; lnI++)
		{
			if (l[lnI] != r[lnI])
			{
				if (l[lnI] < r[lnI])
					return -1;		// Left is less than right
				return 1;			// Left is greater than right
			}
		}
		// They're equal
		return 0;
	}




//////////
//
// Unicode memory compare without regards to case
//
//////
	int CALLTYPE oss_unicodeMemicmp(w16* l, w16* r, u32 tnLength)
	{
		w16		ll, rl;		// Left- and right-lower
		u32		lnI;


		// For every character in the length, compare left to right
		for (lnI = 0; lnI < tnLength; lnI++)
		{
			ll = oss_lowerCaseW(l[lnI]);
			rl = oss_lowerCaseW(r[lnI]);
			if (ll != rl)
			{
				if (ll < rl)
					return -1;		// Left is less than right
				return 1;			// Left is greater than right
			}
		}
		// They're equal
		return 0;
	}




//////////
//
// Unicode memory set (initialize)
//
//////
	int CALLTYPE oss_unicodeMemset(w16* p, w16 uc, u32 tnLength)
	{
		u32 lnI;


		// Make sure the environment is sane
		lnI = 0;
		if (p)
		{
			// For the indicated length, stick the indicated unicode character in there
			for (; lnI < tnLength; lnI++)
				p[lnI + lnI] = uc;
		}

		// Indicate the number of characters we processed
		return(lnI);
	}




//////////
//
// Convert the indicated wide characgter to upper-case
//
//////
	w16 CALLTYPE oss_upperCaseW(w16 u)
	{
		s8 c;
// TODO:  (unicode) foreign languages will need to have other tests here

		// See if it's a lower-case character in ASCII
		c = (s8)u;
		if (c >= 'a' && c <= 'z')
			return((w16)(c - 0x20));		// It is, convert to upper-case

		// If we get here, we're good as we are
		return(u);
	}




//////////
//
// Convert the indicated wide character to lower-case
//
//////
	w16 CALLTYPE oss_lowerCaseW(w16 u)
	{
		s8 c;
// TODO:  (unicode) foreign languages will need to have other tests here


		// See if it's a lower-case character in ASCII
		c = (s8)u;
		if (c >= 'A' && c <= 'Z')
			return((w16)(c + 0x20));		// It is, convert to lower-case

		// If we get here, we're good as we are
		return(u);
	}




//////////
//
// ASCII memory set byte by byte
//
//////
	void CALLTYPE oss_memset(s8* dst, s8 c, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (dst)
		{
			// Iterate for every indicated character
			for (lnI = 0; lnI < tnCount; lnI++)
				dst[lnI] = c;
		}
	}




//////////
//
// ASCII memory set as a series of integer values
//
//////
	void CALLTYPE oss_memset4(u32* dst, u32 val, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (dst)
		{
			// Iterate for every indicated dword
			for (lnI = 0; lnI < tnCount; lnI++)
				dst[lnI] = val;
		}
	}




//////////
//
// Memory copy byte by byte
//
//////
	void CALLTYPE oss_memcpy(s8* dst, s8* src, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (dst && src)
		{
			// Copy everything
			for (lnI = 0; lnI < tnCount; lnI++)
				dst[lnI] = src[lnI];
		}
	}




//////////
//
// Memory compare left and right
//
//////
	s32 CALLTYPE oss_memcmp(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (l._cu8 && r._cu8)
		{
			for (lnI = 0; lnI < tnCount; lnI++)
			{
				if (l._cu8[lnI] != r._cu8[lnI])
				{
					if (l._cu8[lnI] < r._cu8[lnI])		return(-1);		// left is less than right
					else								return(1);		// left is greater than right
				}
				// Still good, keep going
			}
			// When we get here, they're equal
			return(0);
		}
		// Invalid configuration
		return(-2);
	}




//////////
//
// Memory compare left and right without regards to case
//
//////
	s32 CALLTYPE oss_memicmp(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount)
	{
		u64		lnI;
		u8		cl, cr;


		// Make sure our environment is sane
		if (l._cu8 && r._cu8 && tnCount != 0)
		{
			for (lnI = 0; lnI < tnCount; lnI++)
			{
				// Grab the bytes
				cl = l._cu8[lnI];
				cr = r._cu8[lnI];

				// Ignore case
				if (cl >= 'A' && cl <= 'Z')		cl |= 0x20;
				if (cr >= 'A' && cr <= 'Z')		cr |= 0x20;

				if (cl != cr)
				{
					if (cl < cr)		return(-1);		// left is less than right
					else				return(1);		// left is greater than right
				}
				// Still good, keep going
			}
			// When we get here, they're equal
			return(0);
		}
		// Invalid configuration
		return(-2);
	}




//////////
//
// Compare two strings possibly of different lengths without regards to case
//
//////
	s32 CALLTYPE oss_memicmpTwoLengths(csu8p l/*eft*/, u64 tnLeftLength, csu8p r/*ight*/, u64 tnRightLength)
	{
		u64		lnI;
		u8		cl, cr;


		// Make sure our environment is sane
		if (l._cu8 && r._cu8 && tnLeftLength != 0 && tnRightLength != 0)
		{
			for (lnI = 0; lnI < tnLeftLength && lnI < tnRightLength; lnI++)
			{
				// Grab the bytes
				cl = l._cu8[lnI];
				cr = r._cu8[lnI];

				// Ignore case
				if (cl >= 'A' && cl <= 'Z')		cl |= 0x20;
				if (cr >= 'A' && cr <= 'Z')		cr |= 0x20;

				if (cl != cr)
				{
					if (cl < cr)		return(-1);		// left is less than right
					else				return(1);		// left is greater than right
				}
				// Still good, keep going
			}
			// When we get here, they're equal
			if (tnLeftLength == tnRightLength)
				return(0);		// They're equal

			// If we get here, they're different lengths, so based on whichever one is shorter, return that result
			if (tnRightLength >= tnLeftLength)		return(1);		// Left is shorter
			else									return(-1);		// Right is shorter
		}
		// Invalid configuration
		return(-2);
	}




//////////
//
// Compare a string to a datum without regards to case
//
//////
	s32 CALLTYPE oss_memicmpDatum(SDatum* datum, csu8p r/*ight*/, u64 tnRightLength)
	{
		// Make sure our environment is sane
		if (datum && r._cu8 && tnRightLength != 0 && datum->length != 0)
			return(oss_memicmpTwoLengths(datum->data, datum->length, r, tnRightLength));

		// If we get here, failure
		return(-2);
	}




//////////
//
// Compare a string to a datum2 without regards to case
//
//////
	s32 CALLTYPE oss_memicmpDatum2(SDatum2* datum2, csu8p r/*ight*/, u64 tnRightLength)
	{
		// Make sure our environment is sane
		if (datum2 && r._cu8 && tnRightLength != 0 && datum2->datum.length != 0)
			return(oss_memicmpTwoLengths(datum2->datum.data, datum2->datum.length, r, tnRightLength));

		// If we get here, failure
		return(-2);
	}




//////////
//
// Compare a datum to a datum without regards to case
//
//////
	s32 CALLTYPE oss_memicmpDatumDatum(SDatum* datumL, SDatum* datumR)
	{
		if (datumL && datumR)
			return(oss_memicmpTwoLengths(datumL->data, datumL->length, datumR->data, datumR->length));

		// If we get here, failure
		return(-2);
	}




//////////
//
// Compare a datum2 to a datum2 without regards to case
//
//////
	s32 CALLTYPE oss_memicmpDatum2Datum2(SDatum2* datum2L, SDatum2* datum2R)
	{
		if (datum2L && datum2R)
			return(oss_memicmpTwoLengths(datum2L->datum.data, datum2L->datum.length, datum2R->datum.data, datum2R->datum.length));

		// If we get here, failure
		return(-2);
	}




//////////
//
// Extract the red, green, blue, and alpha components from the indicated color
//
//////
	void CALLTYPE oss_deriveRGBA(u32 tnColor, u8* tnRed, u8* tnGrn, u8* tnBlu, f32* tfAlp)
	{
		*tnRed = red(tnColor);
		*tnGrn = grn(tnColor);
		*tnBlu = blu(tnColor);
		*tfAlp = (f32)(alp(tnColor)) / 255.0f;
	}




//////////
//
// Called to create a non-pseudo-random, but predictable pattern that can be used to create
// testable values or patterns to ensure that something hasn't been altered.
//
//////
	u8 CALLTYPE oss_getPredictableSequentialPattern(u32 tnIterator, u32 tnValue)
	{
		u32 ln1, ln2, ln3, ln4, lnTotal, lnResult;


		//////////
		// Create the four forms
		//////
			ln1 = _rotl(  tnValue,         (tnIterator / 2) % 32);
			ln2 = _rotl(~(tnValue * 100),  (tnIterator / 4) % 32);
			ln3 = _rotl( (tnValue * 1000),  tnIterator      % 32);
			ln4 = _rotl(~(tnValue * 10000), tnIterator      % 32);


		//////////
		// Put the four forms together
		//////
			lnTotal = ln1 + ln2 + ln3 + ln4;


		//////////
		// Extract a single byte
		//////
			lnResult =	((lnTotal & 0xff000000) >> 24) +
						((lnTotal & 0x00ff0000) >> 16) +
						((lnTotal & 0x0000ff00) >>  8) +
						((lnTotal & 0x000000ff));


		//////////
		// And compute the final result as a single 8-bit value
		//////
			while (lnResult > 255)
			{
				lnResult =	((lnResult & 0x0000ff00) >> 8) +
							((lnResult & 0x000000ff));
			}


		//////////
		// All done
		//////
			return((u8)lnResult);
	}





//////////
//
// Creates a new 2-way linked list with optional nodePrev and nodeNext info, using
// the indicated size for the allocation (which includes the SLL portion at the head).
// The value of tnSize is the number of extra bytes required for the structure.  It
// should always be greater than zero because if it is only zero, that means only a
// raw SLL will be created.
//
//////
	SLL* CALLTYPE oss_ll_create(SLL* nodePrev, SLL* nodeNext, u64 tnUniqueId, u32 tnSize)
	{
		SLL* node;


		// Allocate the size
		node = (SLL*)malloc(sizeof(SLL) + tnSize);
		if (node)
		{
			// We're good
			memset(node, 0, tnSize);
			
			// Store a unique id
			node->uniqueId	= tnUniqueId;

			// Update our pointers
			node->prev		= nodePrev;
			node->next		= nodeNext;
		}

		// Indicate our success or failure
		return(node);
	}




//////////
//
// Called to delete a link list node.  If need be it orphanizes the node first.
//
//////
	void CALLTYPE oss_ll_delete(SLL* node)
	{
		if (node)
		{
			//////////
			// Disconnect
			//////
				if (node->prev || node->next)
					oss_ll_orphanize(node);


			//////////
			// Delete the node
			//////
				free(node);
		}
	}




//////////
//
// Called to delete a link list node with a callback.  If need be it orphanizes the node first.
//
//////
	void CALLTYPE oss_ll_deleteWithCallback(SLLCallback* cb)
	{
		if (cb && cb->node)
		{
			//////////
			// Disconnect
			//////
				if (cb->node->prev || cb->node->next)
					oss_ll_orphanize(cb->node);


			//////////
			// Let the user say their goodbyes
			//////
				if (cb->_func)
					cb->funcVoid(cb);


			//////////
			// Delete the node
			//////
				free(cb->node);
		}
	}




//////////
//
// Inserts a 2-way linked relative to the nodeRef, either before or after.  If the
// node is already connected, it is disconnected.
//
//////
	bool CALLTYPE oss_ll_insert(SLL* node,  SLL* nodeRef,  bool tlAfter)
	{
// TODO:  UNTESTED CODE
		// Is our environment sane?
		if (node && nodeRef)
		{
			//////////
			// Disconnect
			//////
				if (node->prev || node->next)
					oss_ll_orphanize(node);


			//////////
			// Is it going before or after?
			//////
				if (tlAfter)
				{
					// Point the one after this back to node to be inserted
					if (nodeRef->next)
						nodeRef->next->prev	= node;		// The one after points back to the node we're inserting

					// Are we updating to a valid node?
					if (node)
					{
						// The node is valid, so we can update relative pointers
						// Point this node to the one that will be after
						node->next = nodeRef->next;
						node->prev = nodeRef;
					}

					// Store the pointer to the node
					nodeRef->next = node;


				} else {
					// Positioning this node before
					// Point the one before this forward to the node to be inserted
					if (nodeRef->prev)
						nodeRef->prev->next = node;

					// Are we updating to a valid node?
					if (node)
					{
						// The node is valid, so we can update relative pointers
						// Point this node to the one that will be after
						node->prev = nodeRef->prev;
						node->next = nodeRef;
					}

					// Store the pointer to the node
					nodeRef->prev = node;
				}
		}
		// Failure
		return(false);
	}




//////////
//
// Disconnects a node from its existing chain
//
//////
	void CALLTYPE oss_ll_orphanize(SLL* node)
	{
// TODO:  UNTESTED CODE
		// Is our environment sane?
		if (node)
		{

			//////////
			// Is there one before?
			//////
				if (node->prev)
					node->prev->next = node->next;		// Make the one before point to the one after

			//////////
			// Is there one after?
			//////
				if (node->next)
					node->next->prev = node->prev;		// Make the one after point to the one before

			//////////
			// Free up all parts
			//////
				node->next	= NULL;
				node->prev	= NULL;
		}
	}




//////////
//
// Called to delete the entire chain (beginning from where it's at
//
//////
	void CALLTYPE oss_ll_deleteChain(SLL** root)
	{
		SLL* node;
		SLL* nodeNext;


		// Make sure the environment is sane
		if (root)
		{
			// Iterate through deleting each entry
			node = *root;
			while (node)
			{
				// Grab the next node
				nodeNext = node->next;
				
				// Delete the node
				free(node);

				// Move to next item
				node = nodeNext;
			}

			// Reset the pointer
			*root = NULL;
		}
	}




//////////
//
// Called to delete the entire chain (beginning from where it's at on) using an optional callback.
// The callback should not delete the node, but only anything the node points to.
//
//////
	void CALLTYPE oss_ll_deleteChainWithCallback(SLLCallback* cb)
	{
		SLL* nodeNext;


		// Make sure the environment is sane
		if (cb)
		{
			// Iterate through deleting each entry
			while (cb->node)
			{
				// Grab the next node
				nodeNext = cb->node->next;

				// Perform the callback
				if (cb->_func)
					cb->funcVoid(cb);

				// Delete the node
				free(cb->node);

				// Move to next node
				cb->node = nodeNext;
			}
			// All done
		}
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
//////
	void CALLTYPE oss_ll_iterateViaCallback(SLLCallback* cb)
	{
		//////////
		// For each node, process its portion
		//////
			while (cb->node)
			{

				//////////
				// Callback to compute the SHA1 on this item
				//////
					cb->funcVoid(cb);
					//oss_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


				//////////
				// Move to next node
				//////
					cb->node = cb->node->next;
			}
	}




//////////
//
// Called to iterate from the indicated node backwards
//
//////
	void CALLTYPE oss_ll_iterateBackwardViaCallback(SLLCallback* cb)
	{
		//////////
		// For each node, process its portion
		//////
			while (cb->node)
			{

				//////////
				// Callback to compute the SHA1 on this item
				//////
					cb->funcVoid(cb);
					//oss_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


				//////////
				// Move to next node
				//////
					cb->node = cb->node->prev;
			}
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
//////
	SLL* CALLTYPE oss_ll_getFirstNode(SLL* node)
	{
		// Make sure the environment is sane
		if (node)
		{
			// Iterate backwards to the top
			while (node->prev)
				node = node->prev;
		}

		// Indicate where we are
		return(node);
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
// The parameters in the callback are:
//		ptr			-- LL node
//////
	SLL* CALLTYPE oss_ll_getLastNode(SLL* node)
	{
		// Make sure the environment is sane
		if (node)
		{
			// Iterate forwards to the end
			while (node->next)
				node = node->next;
		}

		// Indicate where we are
		return(node);
	}




//////////
//
// Creates a new 2-way linked list with optional nodePrev and nodeNext info, using
// the indicated size for the allocation (which includes the SLL portion at the head).
// The value of tnSize is the number of extra bytes required for the structure.  It
// should always be greater than zero because if it is only zero, that means only a
// raw SLL will be created.
//
//////
	SLL4* CALLTYPE oss_ll4_create(SLL4* nodeWest, SLL4* nodeEast, SLL4* nodeNorth, SLL4* nodeSouth, u64 tnUniqueId, u32 tnSize)
	{
		SLL4* node;


		// Allocate the size
		node = (SLL4*)malloc(sizeof(SLL4) + tnSize);
		if (node)
		{
			// We're good
			memset(node, 0, sizeof(SLL4) + tnSize);
			
			// Store a unique id
			node->uniqueId	= tnUniqueId;

			// Update our pointers
			node->west		= nodeWest;
			node->east		= nodeEast;
			node->north		= nodeNorth;
			node->south		= nodeSouth;
		}

		// Indicate our success or failure
		return(node);
	}




//////////
//
// Called to create a 4-way linked list chain in a particular direction, for the indicated number
// of entries.
//
//////
	SLL4* CALLTYPE oss_ll4_createChain(u32 tnSize, u32* tnCount, u32 tnDirection)
	{
		u32		lnI;
		SLL4*	ll4;
		SLL4*	ll4Root;
		SLL4*	ll4Last;


		// Iterate until our count is consumed, or we fail
		ll4		= NULL;
		ll4Root = NULL;
		ll4Last	= NULL;
		for (lnI = 0; lnI < *tnCount; lnI++)
		{
			// Create the new entry
			switch (tnDirection)
			{
				case _LL4_WEST:
					ll4 = oss_ll4_create(NULL, ll4Last, NULL, NULL, oss_getNextUniqueId(), tnSize);
					if (ll4Last)
						ll4Last->west = ll4;
					break;

				case _LL4_EAST:
					ll4 = oss_ll4_create(ll4Last, NULL, NULL, NULL, oss_getNextUniqueId(), tnSize);
					if (ll4Last)
						ll4Last->east = ll4;
					break;

				case _LL4_NORTH:
					ll4 = oss_ll4_create(NULL, NULL, NULL, ll4Last, oss_getNextUniqueId(), tnSize);
					if (ll4Last)
						ll4Last->north = ll4;
					break;

				case _LL4_SOUTH:
					ll4 = oss_ll4_create(NULL, NULL, ll4Last, NULL, oss_getNextUniqueId(), tnSize);
					if (ll4Last)
						ll4Last->south = ll4;
					break;

				default:
					// Unknown, failure.
					*tnCount = lnI;
					return(ll4Root);
			}
			// When we get here, we have our new entry
			if (!ll4Root)
				ll4Root = ll4;

			// Update the last pointer
			ll4Last = ll4;
		}
		// When we get here, we're good
		return(ll4Root);
	}




//////////
//
// Called to delete a single node from the four-way link list
//
//////
	void CALLTYPE oss_ll4_delete(SLL4* node)
	{
		if (node)
		{
			// Disconnect from everything
			oss_ll4_orphanize(node);

			// Free it
			free(node);
		}
	}




//////////
//
// Called to delete a four-way link list node with a callback.  If need be it orphanizes
// the node first.
//
//////
	void CALLTYPE oss_ll4_deleteWithCallback(SLL4Callback* cb)
	{
		if (cb && cb->node)
		{
			//////////
			// Disconnect
			//////
				oss_ll4_orphanize(cb->node);


			//////////
			// Let the user say their goodbyes
			//////
				if (cb->_func)
					cb->funcVoid(cb);


			//////////
			// Delete the node
			//////
				free(cb->node);
		}
	}




//////////
//
// Disconnects an SLL4 structure from either an BXML or a traditional node configuration.
// LL4 entries go off in four directions, toward siblings (prev/next), and toward parents
// and children.  These can be thought of as the cardinal directions as well (north/east/
// south/west).
//
//////
	// Note:  The common code itself knows nothing about SBxml structure formally, but it
	//        has at its header the SLL4 structure, which it does know about.
	//
	// In SBxml structures, we always update siblings, but if we have no previous entry,
	// then we must make the parent (if any) point to our next sibling, and we always
	// keep the children (for they are indeed most important!) :-)
	bool CALLTYPE oss_ll4bxml_orphanize(SLL4* bxml)
	{
		bool	llResult;


// TODO:  tested code working properly, but not tested thoroughly enough
		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// We have something to work with, but of what caliber is it?
			// Should we accept it on its word that it is a good bxml and not being merely deceptive so as to harm our system? :-)

			// Update its elements if any
			// See if this is the first child
			if (!bxml->prev && bxml->parent)
				bxml->parent->child = bxml->next;		// This is the first item, so our parent must now point to our next sibling

			// Disconnect this node from its siblings
			if (bxml->next)		bxml->next->prev = bxml->prev;
			if (bxml->prev)		bxml->prev->next = bxml->next;

			// When we get here, this node has been made an orphan
			// Let it now believe so
			bxml->parent	= NULL;
			bxml->next		= NULL;
			bxml->prev		= NULL;
			// Note:  It will still keep its children

			// If we get here, we were good
			llResult = true;
		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// In nodes, we always update north/south paths, as well as east/west paths, as the node is
// just a point on a mesh or clutter mesh.
//
//////
	bool CALLTYPE oss_ll4_orphanize(SLL4* node)
	{
		bool llResult;


		// Make sure our environment is sane
		llResult = false;
		if (node)
		{

			//////////
			// Disconnect this node in/from the four cardinal directions
			//////
				if (node->north)
					node->north->south = node->south;		// It points to an entry above itself

				if (node->south)
					node->south->north = node->north;		// It points to an entry below itself

				if (node->east)
					node->east->west = node->west;			// It points to an entry to the right

				if (node->west)
					node->west->east = node->east;			// It points to an entry to the left


			//////////
			// Update the node to reflects its new orphaned status
			//////
				node->north		= NULL;
				node->south		= NULL;
				node->east		= NULL;
				node->west		= NULL;

		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// Called to insert the indicated node where it should go
//
//////
	// Inserts only as a sibling, either before or after the reference bxml
	bool CALLTYPE oss_ll4bxml_insert(SLL4* bxmlSibling, SLL4* bxmlRef, bool tlAfter)
	{
		bool	llResult;
		SLL4*	bxmlNext;
		SLL4*	bxmlPrev;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment's sane
		if (bxmlSibling && bxmlRef)
		{
			// Only success at this point. :-)
			llResult = true;

			// Are we inserting before or after?
			if (tlAfter)
			{
				// We're inserting this one AFTER the reference bxml
				bxmlNext		= bxmlRef->next;			// Grab the original next

				// Going between BxmlRef and BxmlNext
				bxmlSibling->prev		= bxmlRef;					// The one we're inserting points back to the reference
				bxmlSibling->next		= bxmlNext;					// The one we're inserting points forward to what used to be the next
				bxmlRef->next	= bxmlSibling;						// The reference points forward to the one we're inserting

				// Update the other one that's out there, you know, "on the other side"
				if (bxmlNext)
					bxmlNext->prev = bxmlSibling;					// The original next now points backward to the one we're inserting

			} else {
				// We're inserting this one BEFORE the reference bxml
				bxmlPrev		= bxmlRef->prev;			// Grab original previous

				// Going between BxmlPrev and BxmlRef
				bxmlSibling->prev		= bxmlPrev;					// The one we're inserting before points back to the original previous
				bxmlSibling->next		= bxmlRef;					// The one we're inserting before points forward to the reference
				bxmlRef->prev	= bxmlSibling;						// The reference points back to the one we're inserting before
				if (bxmlPrev)
					bxmlPrev->next = bxmlSibling;					// The previous points forward to the one we're inserting

				// Was this the first item we just inserted before?
				if (bxmlRef->parent && bxmlRef->parent->firstChild == bxmlRef)
				{
					// Yes, it needs to now point to the new item
					bxmlRef->parent->firstChild = bxmlSibling;
				}
			}

		} else {
			// Failure on parameters
			llResult = false;
		}

		// Indicate our status
		return(llResult);
	}

	// Positions the element as a child either at the start (faster) or end (slower)
	bool CALLTYPE oss_ll4bxml_insertAsChild(SLL4* bxmlChild, SLL4* bxmlParent, bool tlAfter)
	{
		bool	llResult;
		SLL4*	bxmlRunner;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment's sane
		if (bxmlChild && bxmlParent)
		{
			// Only success at this point
			llResult = true;

			// Before or after?
			if (tlAfter)
			{
				// Going to the tail
				if (bxmlParent->child)
				{
					// We need to iterate to the end
					bxmlRunner = bxmlParent->child;
					while (bxmlRunner->next)
						bxmlRunner = bxmlRunner->next;

					// When we get here, we have the last child
					bxmlRunner->next			= bxmlChild;
					bxmlChild->prev				= bxmlRunner;

				} else {
					// First child
					bxmlParent->firstChild		= bxmlChild;
					bxmlChild->prev				= NULL;
				}
				// Nothing point after
				bxmlChild->next = NULL;

			} else {
				// Going to the start
				if (bxmlParent->child)
					bxmlChild->next = bxmlParent->child;		// There is already a child, make sure this new one points to that child

				// Update the parent to point to its new first child
				bxmlParent->firstChild			= bxmlChild;

				// Nothing pointing before
				bxmlChild->prev					= NULL;
			}
			// If we get here, we're good
			llResult = true;

		} else {
			// Invalid parameters
			llResult = false;
		}

		// Indicate our status
		return(llResult);
	}

	// Positions the element relative to the bxml reference, either before or after, and
	// therefore "regarding" it.
	bool CALLTYPE oss_ll4bxml_insertAsChildRegarding(SLL4* bxmlChild, SLL4* bxmlParent, SLL4* bxmlRegarding, bool tlAfter)
	{
		bool	llResult;
		SLL4*	BxmlNext;
		SLL4*	BxmlPrev;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (bxmlChild && bxmlParent && bxmlRegarding)
		{
			if (tlAfter)
			{
				// It's going AFTER the reference entry
				if (bxmlRegarding->next)
				{
					// There IS an entry after this one
					// bxml is going between BxmlRef and BxmlNext
					BxmlNext = bxmlRegarding->next;

					// Insert the node
					bxmlChild->prev			= bxmlRegarding;
					bxmlChild->next			= BxmlNext;
					bxmlRegarding->next		= bxmlChild;
					BxmlNext->prev			= bxmlChild;

				} else {
					// BxmlRef is the last entry
					bxmlRegarding->next		= bxmlChild;
					bxmlChild->prev			= bxmlRegarding;
					bxmlChild->next			= NULL;
				}

			} else {
				// It's going BEFORE the reference entry
				if (bxmlRegarding->prev)
				{
					// There IS an entry before this one
					BxmlPrev = bxmlRegarding->prev;
					// This is going between BxmlPrev and BxmlRef
					bxmlChild->prev				= BxmlPrev;
					bxmlChild->next				= bxmlRegarding;
					BxmlPrev->next				= bxmlChild;
					bxmlRegarding->prev			= bxmlChild;

				} else {
					// xmlRef is the first entry
					bxmlChild->prev				= NULL;
					bxmlChild->next				= bxmlRegarding;
					bxmlParent->firstChild		= bxmlChild;
					bxmlRegarding->prev			= bxmlChild;
				}
			}
			// Update the pointer to point back up to its new parent.
			bxmlChild->parent = bxmlParent;

			// Success
			llResult = true;
		}
		// Indicate our status
		return(llResult);
	}

	// Inserts the node before or after the indicated node
	bool CALLTYPE oss_ll4_insertNorthSouth(SLL4* node, SLL4* nodeRef, bool tlAfter)
	{
		bool	llResult;
		SLL4*	nodeNorth;
		SLL4*	nodeSouth;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (node && nodeRef)
		{
			if (tlAfter)
			{
				// node is going after nodeRef
				if (nodeRef->south)
				{
					// There is an entry after nodeRef, so we insert it between nodeRef and nodeRef->next
					nodeSouth			= nodeRef->south;

					// Update nodeRef to point to this one
					node->south			= nodeSouth;
					nodeRef->south		= node;

					// Update nodeNext to point back to this one
					node->north			= nodeSouth->north;
					nodeSouth->north	= node;

				} else {
					// There is no entry after nodeRef, so we just put it after
					nodeRef->south		= node;
					node->north			= nodeRef;
					node->south			= NULL;				// Make sure this entry is not hooked up otherwise
				}

			} else {
				// node is going before nodeRef
				if (nodeRef->north)
				{
					// There is an entry before nodeRef, so we insert it between nodeRef and nodeRef->prev
					nodeNorth			= nodeRef->north;

					// Update nodeRef to point to this one
					node->north			= nodeNorth;
					nodeRef->north		= node;

					// Update nodePrev to point forward to this one
					node->south			= nodeRef;
					nodeNorth->south	= node;

				} else {
					// There is no entry before nodeRef, so we just put it before
					nodeRef->north		= node;
					node->south			= nodeRef;
					node->north			= NULL;				// Make sure this entry is not hooked up otherwise
				}
			}
		}
		// Indicate our status
		return(llResult);
	}

	// Inserts the node before or after the indicated node
	bool CALLTYPE oss_ll4_insertWestEast(SLL4* node, SLL4* nodeRef, bool tlAfter)
	{
		bool	llResult;
		SLL4*	nodeWest;
		SLL4*	nodeEast;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (node && nodeRef)
		{
			if (tlAfter)
			{
				// node is going after (east) nodeRef
				if (nodeRef->east)
				{
					// There is an entry after nodeRef, so we insert it between nodeRef and nodeRef->next
					nodeEast		= nodeRef->east;

					// Update nodeRef to point to this one
					node->east		= nodeEast;
					nodeRef->east	= node;

					// Update nodeNext to point back to this one
					node->west		= nodeEast->west;
					nodeEast->west	= node;

				} else {
					// There is no entry after nodeRef, so we just put it after
					nodeRef->east	= node;
					node->west		= nodeRef;
					node->east		= NULL;				// Make sure this entry is not hooked up otherwise
				}

			} else {
				// node is going before (west) nodeRef
				if (nodeRef->west)
				{
					// There is an entry before nodeRef, so we insert it between nodeRef and nodeRef->west
					nodeWest		= nodeRef->west;

					// Update nodeRef to point to this one
					node->west		= nodeWest;
					nodeRef->west	= node;

					// Update nodePrev to point forward to this one
					node->east		= nodeRef;
					nodeWest->east	= node;

				} else {
					// There is no entry before nodeRef, so we just put it before
					nodeRef->west	= node;
					node->east		= nodeRef;
					node->west		= NULL;				// Make sure this entry is not hooked up otherwise
				}
			}
		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// Called to delete the chain of items in the indicated direction
//
//////
	void CALLTYPE oss_ll4_deleteChain(SLL4** root, u32 tnDirection)
	{
		SLL4*	node;
		SLL4*	nodeNext;


		// Make sure our environment is sane
		if (root && *root)
		{
			// Grab the node
			node = *root;

			// Are we deleting all, or just in a particular direction?
			if (tnDirection == _LL4_ALL)
			{
				// Delete everything
				ioss_ll4_deleteChainAllNodes(NULL, *root);

			} else {
				// Iterate through every node in the indicated direction
				while (node)
				{
					//////////
					// Grab the next node
					/////
						switch (tnDirection)
						{
							case _LL4_NORTH:
								nodeNext = node->north;
								break;

							case _LL4_SOUTH:
								nodeNext = node->south;
								break;

							case _LL4_WEST:
								nodeNext = node->west;
								break;

							case _LL4_EAST:
								nodeNext = node->east;
								break;

							default:
								// Invalid direction, abort
								return;
						}


					//////////
					// Disconnect if we are not deleting all
					//////
						if (tnDirection != _LL4_ALL)
							oss_ll4_orphanize(node);


					//////////
					// Delete this entry
					/////
						free(node);


					//////////
					// Move to the next node
					/////
						node = nodeNext;
				}
			}

			// All done, update our root pointer
			*root = NULL;
		}
	}




//////////
//
// 
// Called to delete the entire chain (beginning from where it's at on) using an optional callback.
// The callback should not delete the node, but only anything the node points to.
//
//////
	void CALLTYPE oss_ll4_deleteChainWithCallback(SLL4Callback* cb, u32 tnDirection)
	{
		SLL4* nodeNext;


		if (tnDirection == _LL4_ALL)
		{
			// Delete everything
			ioss_ll4_deleteChainAllNodes(cb, cb->node);

		} else {
			// Iterate through the master list until we find the associated entry
			while (cb->node)
			{
				//////////
				// Grab the next node
				/////
					switch (tnDirection)
					{
						case _LL4_NORTH:
							nodeNext = cb->node->north;
							break;

						case _LL4_SOUTH:
							nodeNext = cb->node->south;
							break;

						case _LL4_WEST:
							nodeNext = cb->node->west;
							break;

						case _LL4_EAST:
							nodeNext = cb->node->east;
							break;

						default:
							// Invalid direction, abort
							return;
					}


				//////////
				// Disconnect if we are not deleting all
				//////
					if (tnDirection != _LL4_ALL)
						oss_ll4_orphanize(cb->node);


				//////////
				// Perform the callback
				//////
					cb->funcBool(cb);


				//////////
				// Delete this entry
				/////
					free(cb->node);


				//////////
				// Move to the next node
				/////
					cb->node = nodeNext;
			}
			// All done
		}
	}




//////////
//
// Called to navigate through an entire list of nodes, calling the indicated function on
// each one.
//
//////
	void CALLTYPE oss_ll4_iterateViaCallback(SLL4Callback* cb, u32 tnDirection)
	{
		// Make sure the environment is sane
		if (cb && cb->_func)
		{
			//////////
			// For each node, process its portion
			//////
				while (cb->node)
				{
					//////////
					// Callback to compute the SHA1 on this item
					//////
						cb->funcVoid(cb);
						//oss_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


					//////////
					// Move to "next" node
					//////
						switch (tnDirection)
						{
							case _LL4_WEST:
								cb->node = cb->node->west;
								break;

							case _LL4_EAST:
								cb->node = cb->node->east;
								break;

							case _LL4_NORTH:
								cb->node = cb->node->north;
								break;

							case _LL4_SOUTH:
								cb->node = cb->node->south;
								break;
						}
				}
		}
	}




//////////
//
// Called to iterate in the indicated direction until we reach the furthest extent.
// Note:  This can be a dangerous function because there is no iterative exit.  Any circular
//        pointer will cause the system to go into an unbreakable loop.
//
//////
	SLL4* CALLTYPE oss_ll4_getLastNode(SLL4* node, u32 tnDirection)
	{
		// Make sure the environment is sane
		if (node)
		{
			// Iterate so long as there's something to which to iterate toward. :-)
			do {
				if (tnDirection == _LL4_WEST)
				{
					if (node->west)		node = node->west;
					else				break;

				} else if (tnDirection == _LL4_EAST) {
					if (node->east)		node = node->east;
					else				break;

				} else if (tnDirection == _LL4_NORTH) {
					if (node->north)	node = node->north;
					else				break;

				} else if (tnDirection == _LL4_SOUTH) {
					if (node->south)	node = node->south;
					else				break;

				} else {
					// Unknown item
					break;
				}
				// Repeat until we find the end
			} while (1);
		}
		// Indicate our success or failure
		return(node);
	}




//////////
//
// Append a new record of indicated size to the start/end chain
//
// Returns:
//		NULL		- If error
//		other		- A pointer to the new object
//
// Note:  Initializes memory block of tnSize to NULLs upon successful allocation
//
//////
	void* CALLTYPE oss_SEChain_prepend(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(ioss_SEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, true, tlResult));
	}

	void* CALLTYPE oss_SEChain_append(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(ioss_SEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, false, tlResult));
	}

	// Prepends or appends to the Start/end chain
	void* ioss_SEChain_appendOrPrepend (SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult)
	{
		SLL*			ptrCaller;
		SMasterList*	ptrNew;
		SMasterList*	ptrPrev;
		SMasterList**	prev;


// TODO:  untested code, breakpoint and examine
// Note:  This code has been tested, but it is truly essential to operations of the VVM, and needs thoroughly tested many, many, many times. :-)
		// See where we are
		ptrCaller = NULL;
		if (ptrSE)
		{
			if (!ptrSE->root)
			{
				// This is the first item
				ptrPrev	= NULL;
				prev	= &ptrSE->root;

			} else {
				// We're appending
				if (tlPrepend)
				{
					// We go to the beginning
					ptrPrev	= ptrSE->root;
					prev	= &ptrSE->root;

				} else {
					// We are appending to the end
					ptrPrev	= ptrSE->last;
					prev	= (SMasterList**)&ptrSE->last->ll.next;
				}
			}

			// Allocate for our SMasterList pointer
			ptrNew = (SMasterList*)malloc(sizeof(SMasterList));
			if (ptrNew)
			{
				// We have our new pointer, initialize the structure
				memset(ptrNew, 0, sizeof(SMasterList));

				// Create the new caller structure
				ptrCaller = (SLL*)malloc(tnSize);
				if (ptrCaller)
				{
					// Initialize the structure
					memset(ptrCaller, 0, tnSize);

					// Indicate its unique ID
					ptrCaller->uniqueId	= tnUniqueId;

					// Store the memory variable for the caller memory block
					ptrNew->ptr			= ptrCaller;

					// Update the back-link
					*prev				= ptrNew;

					// Update the other part of the back link
					ptrNew->ll.uniqueId	= tnUniqueIdExtra;
					if (tlPrepend)
					{
						// Previous ptrSE->root points backward to ptrNew, which is now the entry pointed to by ptrSE->root
						ptrPrev->ll.prev	= (SLL*)ptrNew;		// Old first entry points backward to new first entry
						ptrNew->ll.next		= (SLL*)ptrPrev;	// New first entry points forward to old first entry
						ptrSE->root			= ptrNew;			// New first entry

					} else {
						// We are appending to the end
						ptrNew->ll.prev		= (SLL*)ptrPrev;	// Previous last entry pointing forward to new last entry
						ptrSE->last			= ptrNew;			// New last entry
					}

					// Store it in the master list (so when VM is suspended, this data gets saved)
					ioss_SEChain_appendMasterList(ptrSE, ptrNew, 0, tnBlockSizeIfNewBlockNeeded);

					// All done!
				}
				// When we get here, ptrCaller is either populated or NULL
			}
		}
		// Indicate our success or failure explicitly if required
		if (tlResult)
			*tlResult = !(ptrCaller == NULL);

		// Return our pointer
		return(ptrCaller);
	}




	// Appends or prepends an existing (already allocated) orphan pointer to the indicated Start/end list
	void* ioss_SEChain_appendOrPrependExisting(SStartEnd* ptrSE, SLL* ptrExisting, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult)
	{
		SMasterList*	ptrNew;
		SMasterList*	ptrPrev;
		SMasterList**	prev;


// TODO:  untested code, breakpoint and examine
// Note:  This code has been tested, but it is truly essential to operations of the VVM, and needs thoroughly tested many, many, many times. :-)
		// See where we are
		if (ptrSE)
		{
			if (!ptrSE->root)
			{
				// This is the first item
				ptrPrev	= NULL;
				prev	= &ptrSE->root;

			} else {
				// We're appending
				if (tlPrepend)
				{
					// We go to the beginning
					ptrPrev	= ptrSE->root;
					prev	= &ptrSE->root;

				} else {
					// We are appending to the end
					ptrPrev	= ptrSE->last;
					prev	= (SMasterList**)&ptrSE->last->ll.next;
				}
			}

			// Allocate for our SMasterList pointer
			ptrNew = (SMasterList*)malloc(sizeof(SMasterList));
			if (ptrNew)
			{
				// We have our new pointer, initialize the structure
				memset(ptrNew, 0, sizeof(SMasterList));

				// Create the new caller structure
				// Store the memory variable for the caller memory block
				ptrNew->ptr			= ptrExisting;

				// Update the back-link
				*prev				= ptrNew;

				// Update the other part of the back link
				if (tlPrepend)
				{
					// Previous ptrSE->root points backward to ptrNew, which is now the entry pointed to by ptrSE->root
					ptrPrev->ll.prev	= (SLL*)ptrNew;		// Old first entry points backward to new first entry
					ptrNew->ll.next		= (SLL*)ptrPrev;	// New first entry points forward to old first entry
					ptrSE->root			= ptrNew;			// New first entry

				} else {
					// We are appending to the end
					ptrNew->ll.prev		= (SLL*)ptrPrev;	// Previous last entry pointing forward to new last entry
					ptrSE->last			= ptrNew;			// New last entry
				}

				// Store it in the master list (so when VM is suspended, this data gets saved)
				ioss_SEChain_appendMasterList(ptrSE, ptrNew, 0, tnBlockSizeIfNewBlockNeeded);
				// All done!

				// Indicate our success
				return(ptrExisting);
			}
		}
		// Indicate our failure
		return(NULL);
	}




	// Appends an entry relative to the indicated SMasterList* member (either before or after the entry)
	void* CALLTYPE oss_SEChain_appendRelativeToMember(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult)
	{
		SLL* ptrCaller;


		// See where we are
		if (ptrSE)
		{
			if (!ptrSE->root)
				return(NULL);		// There are no entries, so we can't be adding relative to the reference pointer

			// Create the new caller structure
			ptrCaller = (SLL*)malloc(tnSize);
			if (ptrCaller)
			{
				// Initialize the structure
				memset(ptrCaller, 0, tnSize);

				// Indicate its unique ID
				ptrCaller->uniqueId	= tnUniqueId;

				// Append the now existing pointer
				return(oss_SEChain_appendExistingRelativeToMember(ptrSE, ptrRef, tnUniqueIdExtra, ptrCaller, tnBlockSizeIfNewBlockNeeded, tlAfter, tlResult));
			}
		}
		// If we get here, error
		return(NULL);
	}

	void* CALLTYPE oss_SEChain_appendExistingRelativeToMember(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueIdExtra, SLL* ptrCaller, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult)
	{
		u32				lnI, lnHint;
		bool			llFound;
		SMasterList*	lmlNew;


		// See where we are
// TODO:  untested code, breakpoint and examine
// Note:  This code has been tested, but it is truly essential to operations of the VVM, and needs thoroughly tested
		if (ptrSE)
		{
			if (!ptrSE->root)
				return(NULL);		// There are no entries, so we can't be adding relative to the reference pointer

			// If there's a reference, add it relative to the reference
			if (ptrRef)
			{
				// Locate the indicated reference in this list
				llFound = false;
				for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
				{
					if (ptrSE->master[lnI]->used && ptrSE->master[lnI]->ptr == ptrRef)
					{
						// We found our match
						if (tlAfter)		lnHint = lnI + 1;		// Should go after
						else				lnHint = lnI;			// Should go before, which means where the current entry was found

						// Make sure there's room
						ioss_SEChain_freeUpSlot(ptrSE, lnHint, tnBlockSizeIfNewBlockNeeded);

						// Continue to insert this item
						llFound = true;
						break;
					}
				}

				// See if we found our entry
				if (!llFound)
					return(NULL);		// The indicated ptrRef was not found as a member of this Start/End list

			} else {
				// Add at the first available slot
				lnHint = 0;
			}
			// When we get here, we have the relative of where the new entry will go

			// Allocate for our SMasterList pointer
			lmlNew = (SMasterList*)malloc(sizeof(SMasterList));
			if (lmlNew)
			{
				// We have our new pointer, initialize the structure
				memset(lmlNew, 0, sizeof(SMasterList));

				// Store the data
				lmlNew->ll.uniqueId	= tnUniqueIdExtra;
				lmlNew->ptr			= ptrCaller;

				// Store it in the master list (so when VM is suspended, this data gets saved)
				ioss_SEChain_appendMasterList(ptrSE, lmlNew, lnHint, tnBlockSizeIfNewBlockNeeded);


				///////////
				// Adjust this item relative to its ptrRef
				//////
					if (ptrRef)
					{
						if (tlAfter)
						{
							// ptrNew goes after ptrRef
							ptrCaller->prev		= ptrRef;			// New one points backward to reference
							ptrCaller->next		= ptrRef->next;		// New one points forward to what reference used to point to
							ptrRef->next		= ptrCaller;		// Reference points forward to thew new one

							// Update the one after where reference used to be
							if (ptrCaller->next)
								ptrCaller->next->prev = ptrCaller;	// One originally after reference points backward to new one

						} else {
							// ptrNew goes before ptrRef
							ptrCaller->next		= ptrRef;			// New one points forward to what reference
							ptrCaller->prev		= ptrRef->prev;		// New one points backward to what reference used to point backward to
							ptrRef->prev		= ptrCaller;		// Reference points backward to the new one

							// Update the one before where reference used to be
							if (ptrCaller->prev)
								ptrCaller->prev->next = ptrCaller;	// One originally before reference points forward to new one
						}
					}


				// When we get here, ptrCaller is either populated or NULL indicating success or failure
				return(ptrCaller);
			}
		}
		// If we get here, error
		return(NULL);
	}




	// NOTE!  Do not call this function directly!  Call iAppendToStarEndChain() only.
	void ioss_SEChain_appendMasterList(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded)
	{
		// This function should not be called directly.  It is automatically called from
		// iAppendToStarEndChain().  It stores pointers in the master list, pointers
		// which are part of the chain in ptrSE->root..ptrSE->last.
		u32 lnI;


// UNTESTED CODE:  Breakpoint and examine!
		lnI = tnHint;
		while (1)
		{
			// Search for first unused item
			if (ptrSE->master)
			{
				// Check to see if there is an unused slot
				for ( ; lnI < ptrSE->masterCount; lnI++)
				{
					if (!ptrSE->master[lnI])
					{
						// This slot is unused, store it
						ptrSE->master[lnI] = ptrNew;

						// Update it
						ptrNew->used = true;

						// All done
						return;
					}
				}
				// If we get here, there were no unused slots
			}
			// If we get here, no slots are available, add some more

			// Allocate some pointer space
			oss_SEChain_allocateAdditionalMasterSlots(ptrSE, tnBlockSizeIfNewBlockNeeded);
			// We never break out of this loop because we will always return above from it
		}
	}


	void ioss_SEChain_freeUpSlot(SStartEnd* ptrSE, u32 tnSlot, u32 tnBlockSizeIfNewBlockNeeded)
	{
		u32		lnI;
		bool	llFound;


		//////////
		// See if the indicated slot is already open
		//////
			if (!ptrSE->master[tnSlot] || !ptrSE->master[tnSlot]->used)
				return;	// We're good already, the slot is free


		//////////
		// If we get here, we have to make room
		//////
			do {

				//////////
				// Find the first free slot after the indicated slot
				//////
					llFound = false;
					for (lnI = tnSlot + 1; lnI < ptrSE->masterCount; lnI++)
					{
						// Is this slot open?
						if (!ptrSE->master[lnI] || !ptrSE->master[lnI]->used)
						{
							// Yes
							llFound = true;
							break;
						}
					}


				//////////
				// Did we find a free slot?
				//////
					if (llFound)
						break;	// Yes


				//////////
				// We did not find room
				// Allocate some pointer space
				//////
					oss_SEChain_allocateAdditionalMasterSlots(ptrSE, tnBlockSizeIfNewBlockNeeded);
					// We never break out of this loop because we will always return above from it

			} while (1);


		//////////
		// When we get here, lnI is the free slot
		//////
			for (--lnI; lnI <= tnSlot; lnI--)
			{
				// Move this slot to the next slot
				ptrSE->master[lnI+1] = ptrSE->master[lnI];
			}


		//////////
		// Free up the new slot
		//////
			ptrSE->master[tnSlot] = NULL;
	}

	bool CALLTYPE oss_SEChain_allocateAdditionalMasterSlots(SStartEnd* ptrSE, u32 tnBlockSize)
	{
		bool			llResult;
		SMasterList**	lml;


		// Indicate failure initially
		llResult = false;

		// Make sure our environment is sane
		if (ptrSE)
		{
			// Make sure we're really doing something
			tnBlockSize = max(tnBlockSize, 1);

			// See where we are
			if (ptrSE->master)
			{
				// Allocate another _COMMON_START_END_BLOCK_SIZE pointers
				lml = (SMasterList**)realloc(ptrSE->master, sizeof(SMasterList*) * (ptrSE->masterCount + tnBlockSize));
				if (lml)
				{
					// We're good, initialize the new section
					ptrSE->master = lml;
					memset(&ptrSE->master[ptrSE->masterCount], 0, sizeof(SMasterList*) * tnBlockSize);
					ptrSE->masterCount += tnBlockSize;
					llResult = true;

				} else {
					// It failed here
// TODO:  Something major needs to happen here.  This is more or less a catastrophic failure.  It could require shutting down the VVM.
_asm int 3;
					ptrSE->masterCount += tnBlockSize;
				}

			} else {
				// Allocate the first N pointers
				ptrSE->master = (SMasterList**)malloc(sizeof(SMasterList*) * tnBlockSize);
				if (ptrSE->master)
				{
					// We're good, initialize the new section
					memset(&ptrSE->master[0], 0, sizeof(SMasterList*) * tnBlockSize);
					ptrSE->masterCount	= tnBlockSize;
					llResult = true;
				}
			}
		}
		// If we get here, failure
		return(llResult);
	}




//////////
//
// Migrate all SMasterList items from source to destination
//
//////
	void* CALLTYPE oss_SEChain_migrateAll(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc)
	{
		u32 lnI, lnStartCount;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && ptrSESrc->masterCount > 0)
		{
			// Grab a reasonable starting point (the end), for the first hint
			lnStartCount = (ptrSEDst->masterCount >= _COMMON_START_END_BLOCK_SIZE) ? (ptrSEDst->masterCount - _COMMON_START_END_BLOCK_SIZE) : 0;

			// Iterate through every source
			for (lnI = 0; lnI < ptrSESrc->masterCount; lnI++)
			{
				// Copy every populated slot
				if (ptrSESrc->master[lnI] && ptrSESrc->master[lnI]->used)
				{
					// Append it to the destination list
					ioss_SEChain_appendMasterList(ptrSEDst, ptrSESrc->master[lnI], lnStartCount + lnI, _COMMON_START_END_BLOCK_SIZE);

					// Clear out the source slot
					ptrSESrc->master[lnI] = NULL;
				}
			}
		}
		// Failure if we get here
		return(NULL);
	}




//////////
//
// Migrate the existing SMasterList item from one Start/end chain to another, by either pointer
// or physical position number
//
//////
	SMasterList* CALLTYPE oss_SEChain_migrateByPtr(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, void* ptr, u32 tnHint, u32 tnBlockSize)
	{
		u32 lnI;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && ptrSESrc->masterCount >= 1)
		{
			for (lnI = 0; lnI < ptrSESrc->masterCount; lnI++)
			{
				// Is this our pointer?
				if (ptrSESrc->master[lnI] && ptrSESrc->master[lnI]->ptr == ptr)
				{
					// This is our man, migrate it
// TODO:  (enhancement) we want some kind of better hinting algorithm here, such as the end of the list - common block size, for now we'll just pass 0
					return(oss_SEChain_migrateByNum(ptrSEDst, ptrSESrc, lnI, 0, tnBlockSize));
				}
			}
			// If we get here, not found
		}
		// Indicate failure
		return(NULL);
	}

	SMasterList* CALLTYPE oss_SEChain_migrateByNum(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize)
	{
		u32				lnI;
		SMasterList*	lml;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && lnSrcNum < ptrSESrc->masterCount && lnSrcNum <= ptrSESrc->masterCount)
		{
			// We enter an infinite loop in case we have to
			while (1)
			{
				// Find an empty slot in the destination
				for (lnI = tnHint; lnI < ptrSEDst->masterCount; lnI++)
				{
					if (!ptrSEDst->master[lnI] || !ptrSEDst->master[lnI]->used)
					{
						// We found an empty slot, migrate it
						lml							= ptrSESrc->master[lnSrcNum];
						ptrSEDst->master[lnI]		= lml;

						// Clear out the source slot
						ptrSESrc->master[lnSrcNum]	= NULL;

						// See if the thing that was pointed to was the first or last entry (or both (only entry))
						if (ptrSESrc->root == lml)
						{
							// This was the first entry
							if (ptrSESrc->last == lml)
							{
								// And it was the last entry, making it the ONLY entry
								ptrSESrc->root = NULL;
								ptrSESrc->last = NULL;

							} else {
								// It was just the first entry
								ptrSESrc->root = (SMasterList*)lml->ll.next;
							}

						} else if (ptrSESrc->last == lml) {
							// It was the last entry
							ptrSESrc->last = (SMasterList*)lml->ll.prev;
						}
						//else it's just one in the middle, so no worries

						// Detach from its former list (former's previous points to former's next, former's next points to former's previous, basically they both skip over this item)
						if (lml->ll.prev)	((SMasterList*)(lml->ll.prev))->ll.next = lml->ll.next;
						if (lml->ll.next)	((SMasterList*)(lml->ll.next))->ll.prev = lml->ll.prev;
						// Right now, lml is an orphan, but it has pointers to its old slots

						// Append it to the new list, and update its pointers to its new home
						if (!ptrSEDst->root)
						{
							// This is the first item in the destination
							ptrSEDst->root	= lml;
							ptrSEDst->last	= lml;
							lml->ll.prev	= NULL;

						} else {
							// Append it to the end of the chain
							ptrSEDst->last->ll.next = (SLL*)lml;
							lml->ll.prev			= (SLL*)ptrSEDst->last;
							ptrSEDst->last			= lml;
						}
						// Make the newly migrated item now point to nothing, because it is the last item
						lml->ll.next = NULL;

						// All done!
						return(lml);
					}
				}
				// If we get here, no empty slots. Allocate some, rinse, and repeat. :-)
				oss_SEChain_allocateAdditionalMasterSlots(ptrSEDst, tnBlockSize);

				// Process through again beginning at the newly added portion
				tnHint = lnI;
				// We'll never break out of this loop because we will always return above
			}
			// Control will never get here
		}
		// If we get here, error
		return(NULL);
	}




//////////
//
// Migrate the existing SMasterList item, and its associated SLL item, from one Start/end chain
// to another, by either pointer or physical position number.
//
//////
	SLL* CALLTYPE oss_SEChain_completelyMigrateSLLByPtr(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr, u32 tnHint, u32 tnBlockSize)
	{
		u32 lnI;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && ptrSESrc->masterCount >= 1)
		{
			for (lnI = 0; lnI < ptrSESrc->masterCount; lnI++)
			{
				// Is this our pointer?
				if (ptrSESrc->master[lnI] && ptrSESrc->master[lnI]->ptr == (void*)ptr)
				{
					// This is our man, migrate it
// TODO:  (enhancement) we want some kind of better hinting algorithm here, such as the end of the list - common block size, for now we'll just pass 0
					return(oss_SEChain_completelyMigrateSLLByNum(ptrSEDst, ptrSESrc, lnI, 0, tnBlockSize));
				}
			}
			// If we get here, not found
		}
		// Indicate failure
		return(NULL);
	}

	SLL* CALLTYPE oss_SEChain_completelyMigrateSLLByNum(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize)
	{
		SLL*			lllPrev;
		SLL*			lllNext;
		SLL*			lll;
		SMasterList*	lml;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && lnSrcNum < ptrSESrc->masterCount && lnSrcNum <= ptrSESrc->masterCount)
		{
			// Migrate it, and get its SMasterList entry
			lml = oss_SEChain_migrateByNum(ptrSEDst, ptrSESrc, lnSrcNum, tnHint, tnBlockSize);
			if (lml && lml->ptr)
			{
				// Grab the pointer to the SLL entry
				lll = (SLL*)lml->ptr;
				// Right now, lll points to the SLL* object from ptrSESrc

				// Grab ptrSESrc's preceding, and following objects (if any)
				lllPrev	= lll->prev;
				lllNext = lll->next;


				//////////
				// Update the ptrSESrc entry, to remove this lll entry from its lists
				//////
					// Update the pointer for the preceding entry
					if (lllPrev)
						lllPrev->next = lllNext;
					// Update the pointer for the following entry
					if (lllNext)
						lllNext->prev = lllPrev;
					// Right now, lllPrev points forward past lll, and lllNext points backward past lll


				//////////
				// lll is currently an orphan entry that thinks it's not orphaned because it still has prev and next pointers potentially pointing off somewhere
				//////
					// Update lll's prev and next entries to point nowhere
					lll->next = NULL;
					lll->prev = NULL;
					// At this point, lll is only pointed to by its lml entry.


				// All done!
				return(lll);
			}
		}
		// If we get here, invalid environment
		return(NULL);
	}




//////////
//
// Counts how many actual items in the masterCount are valid (contain entries that are in use,
// versus
//
//////
	u32 CALLTYPE oss_SEChain_countValids(SStartEnd* ptrSE)
	{
		u32	lnI, lnValidCount;


		// Make sure our environment is sane
		if (!ptrSE)
			return(0);

		// Iterate through each one, and for every valid entry increase our count
		for (lnValidCount = 0, lnI = 0; 
			 lnI < ptrSE->masterCount; 
			 lnI++)
		{
			// If this entry is valid, increase our count
			if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				++lnValidCount;
		}
		// Return our value
		return(lnValidCount);
	}




//////////
//
// Called to delete an entire Start/end chain
//
// Returns:
//		-1 error in ptrSE, ptrSE->master or ptrSE->masterCount
//		Number of records deleted
//
//////
	u32 CALLTYPE oss_SEChain_delete(SStartEnd* ptrSE, u64 tnCallback, u64 tnParam, bool tlDeletePointers)
	{
		u32			lnI, lnDeletedCount;
		union {
			u64		_callbackAddress;
			void	(*callbackAddress)(void* ptrSE, u64 tnParam);
		};


		// Make sure the environment's sane
		if (ptrSE && ptrSE->master && ptrSE->masterCount != 0)
		{
			// Store our callback address
			_callbackAddress = tnCallback;

			//  Iterate through all entries
			lnDeletedCount = 0;
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				{
					// Callback to the caller if they need to do something special to delete this entry
					if (tnCallback != 0)
						callbackAddress(ptrSE->master[lnI]->ptr, tnParam);

					// Delete the pointer from the list
					oss_SEChain_deleteFrom(ptrSE, ptrSE->master[lnI]->ptr, tlDeletePointers);
					++lnDeletedCount;
				}
			}
			// When we get here, everything's deleted, now delete the container for everything. :-)
			free(ptrSE->master);
			ptrSE->master = NULL;

			// Indicate the number we deleted
			return(lnDeletedCount);
		}
		// Indicate failure
		return(-1);
	}




//////////
//
// Called to delete an entire Start/end chain
//
// Returns:
//		-1 error in ptrSE, ptrSE->master or ptrSE->masterCount
//		Number of records deleted
//
//////
	void CALLTYPE oss_SEChain_deleteAsPtrBlock(SStartEnd* ptrSE)
	{
		// Make sure the environment's sane
		if (ptrSE && ptrSE->master && ptrSE->masterCount != 0)
		{
			// When we get here, everything's deleted, now delete the container for everything. :-)
			free(ptrSE->master);
			ptrSE->master = NULL;
		}
	}




//////////
//
// Delete the indicated item from the chain
//
//////
	void CALLTYPE oss_SEChain_deleteFrom(SStartEnd* ptrSE, void* ptrCaller, bool tlDeletePointers)
	{
		u32				lnI;
		SMasterList*	ptrDel;
		SMasterList**	master;


		// See where we are
// UNTESTED CODE:  Breakpoint and examine!
		if (ptrSE)
		{
			if (!ptrSE->root)
			{
				// There are no existing items, nothing to do, why are they messing around with our brains? :-)
				return;
			}

			// Iterate through the master list to find the matching record to delete in the chain
			master = ptrSE->master;
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// See if this item matches
				ptrDel = master[lnI];
				if (ptrDel && ptrDel->used && ptrDel->ptr == ptrCaller)
				{
					// Mark it as not being used
					ptrDel->used = false;

					// Remove it from its chain
					if (ptrDel == ptrSE->root)
					{
//////////
// This is the first item
//////
						// We are deleting the first item in the list
						if (ptrDel == ptrSE->last)
						{
							// Which is also the last item in the list
							ptrSE->root = NULL;
							ptrSE->last = NULL;
							// No items exist after this

						} else {
							// It's just the first item in a chain
							ptrSE->root = (SMasterList*)ptrDel->ll.next;
						}


					} else if (ptrDel == ptrSE->last) {
//////////
// This is the last item
//////
						// We are deleting the last item in the list
						ptrSE->last									= (SMasterList*)ptrDel->ll.prev;	// This will never be NULL because we've already checked the first condition
						((SMasterList*)(ptrDel->ll.prev))->ll.next	= NULL;								// Make the one before this point to nothing, because it is now the last item


					} else {
//////////
// This is an entry in the middle somewhere
//////
						// We are deleting an entry in the middle somewhere
						((SMasterList*)(ptrDel->ll.prev))->ll.next	= ptrDel->ll.next;		// Make the one before this point to the one after this
						((SMasterList*)(ptrDel->ll.next))->ll.prev	= ptrDel->ll.prev;		// Make the one after this point to the one before this
					}
					// When we get here, the start/end chain is updated


					// Release our SMasterList pointer
					free(ptrDel);
					master[lnI] = NULL;


					// Release the caller's memory (or not if they want to keep it)
					if (tlDeletePointers)
						free(ptrCaller);		// Delete this pointer
					// All done
				}
			}
		}
		//else not found
	}




//////////
//
// Search by callback for the indicated element, and when found delete it
//
//////
	bool CALLTYPE oss_SEChain_deleteFromAfterCallback(SStartEnd* ptrSE, bool tlDeletePointers, SStartEndCallback* cb)
	{
		u32		lnI;
		bool	llResult;


		// Make sure the environment is sane
		llResult = false;
		if (ptrSE)
		{
			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Ask the caller if this is it
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				{
					// Store the pointer for reference
					cb->ptr = ptrSE->master[lnI]->ptr;

					// Perform the call
					if (cb->funcBool(cb))
					{
						// This is the entry they want to delete
						oss_SEChain_deleteFrom(ptrSE, ptrSE->master[lnI]->ptr, tlDeletePointers);
						llResult = true;
						break;
					}
				}
			}
		}
		// If we get here, it wasn't found
		return(llResult);
	}






//////////
//
// Search for the indicated uniqueId in the chain.
//
// Returns:
//		NULL if error
//		The associated pointer if found
//
//////
	struct SScreen2
	{
		SLL				ll;						// 2-way link list
		u64				associatedId;			// A user-defined id of something associated with this screen

		// Limited access is granted during a refresh operation
		u64				semRefresh;				// Limited access to 
		bool			isRefreshing;			// Is this screen refreshing?

		// Associated canvas for this screen
		void*			activeCanvas;			// Pointer to this screen's active canvas (must be a member of the canvastList
		SStartEnd		canvasList;				// Pointer to this screen's first SCanvasList entry

		// Internal information used to make it happen for the target OS
		u64				ossWindowId;			// information necessary to render this screen on the OSS (pointer to _iSWindow struct, for example)
	};
	void* CALLTYPE oss_SEChain_searchByUniqueId(SStartEnd* ptrSE, u64 tnUniqueId)
	{
		u32 lnI;


		// Make sure the environment is sane
		if (ptrSE)
		{
			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used && ((SLL*)(ptrSE->master[lnI]->ptr))->uniqueId == tnUniqueId)
				{
					// We've found our man
					return(ptrSE->master[lnI]->ptr);
				}
			}
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Search for the indicated record in the chain by using a user-defined callback on the pointer.
// Callback function should return true when found, false to continue sending other items back.
//
// Returns:
//		NULL if error
//		The associated pointer if found
//
//////
	void* CALLTYPE oss_SEChain_searchByCallback(SStartEnd* ptrSE, SStartEndCallback* cb)
	{
		u32 lnI;


		// Make sure the environment is sane
		if (ptrSE)
		{
			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Ask the caller if this is it
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				{
					// Store the pointer for the caller
					cb->ptr = ptrSE->master[lnI]->ptr;

					// Perform the call
					if (cb->funcBool(cb))
						return(ptrSE->master[lnI]->ptr);	// We've found our man
				}
			}
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Iterates through the indicated Start/End list, calling back the callback function for every item.
//
//////
	void CALLTYPE oss_SEChain_iterateThroughForCallback(SStartEnd* ptrSE, SStartEndCallback* cb)
	{
		u32 lnI;


		// Make sure the environment is sane
		if (ptrSE)
		{
			// Iterate through the master list calling every valid entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Give this to the caller for their processing
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				{
					// Store the pointer for the caller
					cb->ptr = ptrSE->master[lnI]->ptr;

					// Perform the call
					cb->funcVoid(cb);
				}
			}
		}
	}




//////////
//
// Added for debugging.  Validates that all of the entries in a Start/end chain have proper
// ll.prev and ll.next members.  Should only need to be used during initial development, and
// in tracking down future bugs.  I intend for these Start/end functions to be heavily tested
// and made completely reliable in all conditions.
//
// If the func is populated, then if it returns:
//			true		- test was good
//			false		- test failed
// Note:  The callback is only needed if the lml->ptr structure itself has Start/end members
//        that need to be examined.  If func is not populated, only tests
//        the members contained in the ptrSE Start/end structure.
//
// This function doesn't return anything.
// If there is an error, it will trap to the debugger so the machine state can be examined.
//
//////
	void CALLTYPE oss_SEChain_validate(SStartEnd* ptrSE, SStartEndCallback* cb)
	{
		u32				lnI;
		SMasterList*	lml;


		// Make sure the environment is sane
		if (ptrSE && cb)
		{
			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Ask the caller if this is it
				lml = ptrSE->master[lnI];
				if (lml && lml->used)
				{
					if (lml == ptrSE->root)
					{
						if (lml == ptrSE->last)
						{
							// This is the ONLY entry
							// ll.prev and ll.next need to be null
							if (lml->ll.prev != NULL)
								_asm int 3;
							if (lml->ll.next != NULL)
								_asm int 3;

						} else {
							// This is the first entry
							// ll.prev needs to be null, ll.next needs to be not null
							if (lml->ll.prev != NULL)
								_asm int 3;
							if (lml->ll.next == NULL)
								_asm int 3;
						}

					} else if (lml == ptrSE->last) {
						// This is the last entry
						// ll.prev needs to be not null, ll.next needs to be null
						if (lml->ll.prev == NULL)
							_asm int 3;
						if (lml->ll.next != NULL)
							_asm int 3;

					} else {
						// Somewhere in the middle
						// ll.prev and ll.next need to be not null
						if (lml->ll.prev == NULL)
							_asm int 3;
						if (lml->ll.next == NULL)
							_asm int 3;
					}

					// If there's a callback on this entry, try it out
					// If it returns false, there's an issue, if it returns true it's okay
					cb->ptr = lml->ptr;
					if (!cb->funcBool(cb))
						_asm int 3;
				}
			}
		}
	}




//////////
//
// Called to reverse the endian
//
//////
	u32 CALLTYPE oss_swapEndian(u32 tnValue)
	{
		_asm {
			mov		eax,tnValue
			bswap	eax
			mov		tnValue,eax
		}
		return tnValue;
	}




//////////
//
// For certain operations, colors are reversed
//
//////
	u32 CALLTYPE oss_RGBA2BGRA(u32 tnColor)
	{
		u8 lnRed, lnGrn, lnBlu, lnAlp;


		// Grab the indicated colors
		lnRed	= red(tnColor);
		lnGrn	= grn(tnColor);
		lnBlu	= blu(tnColor);
		lnAlp	= alp(tnColor);

		// Encode and return the new color
		return(rgba(lnBlu, lnGrn, lnRed, lnAlp));
	}




//////////
//
// Allocate the indicated size memory block, and initialize it to nulls
//
// Returns:
//		pointer to the newly allocated block
//
// Note:  The allocated memory is initialized to null if allocated successfully
//
//////
	void* CALLTYPE oss_allocateAndNull(u32 tnSize, bool tnInitToZeros)
	{
		s8* lp;


		// Allocate
		lp = (s8*)malloc(tnSize);

		// Null if valid
		if (lp && tnInitToZeros)
			oss_memset(lp, 0, tnSize);

		// Return the fruits of our labor
		return(lp);
	}




//////////
//
// Called to search the haystack for the needle
//
//////
	bool CALLTYPE oss_isNeedleInHaystack(csu8p tcHaystack, s32 tnHaystackLength, csu8p tcNeedle, s32 tnNeedleLength, bool tlCaseSensitive, u32* tnFoundPosition)
	{
		s32		lnI;
		u32		lnResult;
		csu8p	ptr;


		// Make sure our environment's sane
		if (tcHaystack._cu8 && tcNeedle._cu8 && tnHaystackLength > 0 && tnNeedleLength > 0 && tnHaystackLength >= tnNeedleLength)
		{
			// Iterate until we reach the end
			for (lnI = 0; lnI + tnNeedleLength <= tnHaystackLength; lnI++)
			{
				// Get this offset to this location
				ptr._cu8 = tcHaystack._cu8 + lnI;

				// Scan from this location
				if (tlCaseSensitive)	lnResult = oss_memcmp(ptr, tcNeedle, tnNeedleLength);
				else					lnResult = oss_memicmp(ptr, tcNeedle, tnNeedleLength);

				// What were the findings?
				if (lnResult == 0)
				{
					// It was found, store the position
					if (tnFoundPosition)
						*tnFoundPosition = lnI;

					// Indicate success
					return(true);
				}
			}
		}
		// If we get here, failure
		if (tnFoundPosition)
			*tnFoundPosition = -1;

		// Indicate failure
		return(false);
	}




//////////
//
// Search the specified unicode string haystack for the needle
//
//////
	bool CALLTYPE oss_isNeedleInHaystack_Unicode(w16* twHaystack, w16* twNeedle)
	{
		s32 lnI, lnLengthHaystack, lnLengthNeedle;


		// Make sure our environment's sane
		if (twHaystack && twNeedle)
		{
			// Get the lengths
			lnLengthHaystack	= wcslen(twHaystack);
			lnLengthNeedle		= wcslen(twNeedle);

			// Repeat throughout the unicode string
			for (lnI = 0; lnI <= lnLengthHaystack - lnLengthNeedle; lnI++)
			{
				// Did we find a match?
				if (_wcsicmp(twHaystack + lnI, twNeedle) == 0)
					return(true);
			}
		}
		// If we get here, not found
		return(false);
	}




//////////
//
// Scans forward so long as there are numerical digits (ASCII-48 through ASCII-57, "0" through "9")
//
//////
	u32 CALLTYPE oss_countConsecutiveAsciiNumericDigits(s8* buffer, u32 tnMaxLength)
	{
		u32 lnLength;


		// While we have numbers, continue
		for (lnLength = 0;		lnLength < tnMaxLength && buffer[lnLength] >= '0' && buffer[lnLength] <= '9';		)
			++lnLength;

		// We have our length
		return(lnLength);
	}




//////////
//
// Reads through the numbers, presumably previously determined by iScanConsecutiveNumbers(),
// to obtain the numerical value after converting from text to an unsigned integer
//
//////
	u32 CALLTYPE oss_convertTextToU32(s8* tcNumbers, u32 tnMaxLength)
	{
		u32 lnLength, lnValue, lnMultiplier;


		// Scan through every number
		for (lnLength = 0, lnValue = 0, lnMultiplier = 10;
			 lnLength < tnMaxLength;
			 lnLength++)
		{
			lnValue = (lnValue * lnMultiplier) + (u32)(tcNumbers[lnLength] - '0');
		}

		// We have our converted value
		return(lnValue);
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
			oss_datumSet(&tsFileInfo->pathnameOfSearch, (u8*)".\\", -1, true);

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
				oss_memcpy(buffer, tsFileInfo->pathnameOfSearch.data._s8, lnLength);

				// Make sure it is terminated with a backslash
				if (buffer[lnLength - 1] != '\\')
				{
					// Needs a backslash
					buffer[lnLength] = '\\';
					++lnLength;
				}
				// Append on the file spec
				oss_memcpy(buffer + lnLength, tsFileInfo->filenameSearched.data._s8, tsFileInfo->filenameSearched.length);
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
			oss_datumDelete(&tsFileInfo->filenameSearched);

		// Pathname
		if (tsFileInfo->pathnameOfSearch.data._u8 && tsFileInfo->pathnameOfSearch.length != 0)
			oss_datumDelete(&tsFileInfo->pathnameOfSearch);

		// File
		if (tsFileInfo->file.data._u8 && tsFileInfo->file.length != 0)
			oss_datumDelete(&tsFileInfo->file);

		// File2
		if (tsFileInfo->file2.data._u8 && tsFileInfo->file2.length != 0)
			oss_datumDelete(&tsFileInfo->file2);
	}




//////////
//
// Initializes a new buffer to the default allocation size.
// No content is changed.
//
// Returns:  
//		Pointer to the point in the buffer where the
//////
	void CALLTYPE oss_builderCreateAndInitialize(SBuilder** buffRoot, u32 tnAllocationBlockSize)
	{
		SBuilder*	buffNew;


		// Make sure our environment is sane
		if (buffRoot && tnAllocationBlockSize != 0)
		{
			buffNew = (SBuilder*)oss_alloc(sizeof(SBuilder), true);
			if (buffNew)
			{
				// Store the pointer
				*buffRoot = buffNew;

				// Make sure our allocation block size is at least 4KB
				tnAllocationBlockSize		= max(4096, tnAllocationBlockSize);

				// Allocate the data space
				buffNew->data				= (s8*)oss_alloc(tnAllocationBlockSize, true);

				// If we allocated, we're good
				if (buffNew->data)			buffNew->allocatedLength	= tnAllocationBlockSize;
				else						buffNew->allocatedLength	= 0;

				// Update the allocation size
				buffNew->allocateBlockSize	= tnAllocationBlockSize;
			}
		}
	}




//////////
//
// Appends the indicated text to the end of the buffer.
//
// Returns:  
//		Pointer to the point in the buffer where the text was inserted, can be used
//		for a furthering or continuance of this function embedded in a higher call.
//////
	s8* CALLTYPE oss_builderAppendText(SBuilder* buffRoot, s8* tcData, u32 tnDataLength)
	{
// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		if (buffRoot)
		{
			if (tcData && tnDataLength != 0)
			{
				// Make sure this much data will fit there in the buffer
				ioss_bufferVerifySizeForNewBytes(buffRoot, tnDataLength);

				// If we're still valid, proceed with the copy
				if (buffRoot->data)
					oss_memcpy(buffRoot->data + buffRoot->populatedLength - tnDataLength, tcData, tnDataLength);
			}
			// Indicate where we are
			return(buffRoot->data + buffRoot->populatedLength - tnDataLength);
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Specifies the size the buffer should be.  Either allocates up or down. No content
// is changed, however the buffer pointer value could be changed from oss_realloc().
//
//////
	void CALLTYPE oss_builderSetSize(SBuilder** buffRoot, u32 tnBufferLength)
	{
// TODO:  untested code, breakpoint and examine
// Note:  This code should not be being executed.  The code in ioss_bufferVerifySizeForNewBytes() should be used
_asm int 3;
		// Make sure our environment is sane
		if (buffRoot && *buffRoot && tnBufferLength != 0)
		{
			*buffRoot = (SBuilder*)oss_realloc(*buffRoot, tnBufferLength);
			if (*buffRoot)
				(*buffRoot)->allocatedLength = tnBufferLength;
		}
	}




//////////
//
// Releases the buffer allocated for the SBuilder structure
//
//////
	void CALLTYPE oss_builderFreeAndRelease(SBuilder** buffRoot)
	{
		SBuilder* buffDelete;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		if (buffRoot && *buffRoot)
		{
			// Copy our *buffRoot pointer to local space so we can "appear" to kill it before it's actually killed
			buffDelete	= *buffRoot;
			*buffRoot	= NULL;

			// Release the data buffer
			if (buffDelete->data)
			{
				// Trim our sizes down to 0
				buffDelete->allocatedLength = 0;
				buffDelete->populatedLength = 0;

				// Release our buffer
				oss_free(buffDelete->data);

				// Mark it as no longer valid
				buffDelete->data = NULL;
			}

			// Release the SBuilder structure
			oss_free(buffDelete);
		}
	}




//////////
//
// SHA-1 functions, passed off to an external application included in the VVMOSS.
// See LibSF's \libsf\utils\sha1\sha1.cpp source file for these functions.
//
//////
	void CALLTYPE oss_sha1ComputeSha1(s8* tcData, u32 tnDataLength, u8 shaOutput[20])
	{
		sha1_computeSha1((const u8*)tcData, tnDataLength, shaOutput);
	}

	u64 CALLTYPE oss_sha1ComputeSha1As64Bit(s8* tcData, u32 tnDataLength)
	{
		u8 sha20Bytes[20];

		// Process normal SHA-1, then convert to 64-bit
		sha1_computeSha1((const u8*)tcData, tnDataLength, sha20Bytes);
		return(sha1_convertSha20To64Bit(sha20Bytes));
	}

	u32 CALLTYPE oss_sha1ComputeSha1As32Bit(s8* tcData, u32 tnDataLength)
	{
		u8 sha20Bytes[20];

		// Process normal SHA-1, then convert to 64-bit
		sha1_computeSha1((const u8*)tcData, tnDataLength, sha20Bytes);
		return(sha1_convertSha20To32Bit(sha20Bytes));
	}

	void CALLTYPE oss_sha1ComputeSha1AsHex(s8* tcData, u32 tnDataLength, s8* tcHexOutput, bool tlInsertSpaces)
	{
		u8	sha20Bytes[20];

		// Compute to our local buffer, then convert to hex
		sha1_computeSha1((const u8*)tcData, tnDataLength, sha20Bytes);
		sha1_computeSha1AsHex((const u8*)tcData, tnDataLength, sha20Bytes, tcHexOutput, tlInsertSpaces);
	}

	void CALLTYPE oss_sha1ConvertHexToSha1(u8 shaOutput[20], s8* tcHexInput, bool* tlError)
	{
		sha1_convertHexToSha20(tcHexInput, shaOutput, tlError);
	}

	void CALLTYPE oss_sha1ConvertSha1ToHex(s8* tcHexInput, u8 shaOutput[20], bool tlInsertSpaces)
	{
		sha1_convertSha20ToHex(shaOutput, tcHexInput, tlInsertSpaces);
	}

	void CALLTYPE oss_sha1ComputeSha1_Start(u8 context[92])
	{
		memset(context, 0, sizeof(context));
		sha1_92initialize(context);
	}

	void CALLTYPE oss_sha1ComputeSha1_ProcessThisData(u8 context[92], s8* tcData, u32 tnDataLength)
	{
		sha1_92continueOnThisData(context, (const u8*)tcData, tnDataLength);
	}

	void CALLTYPE oss_sha1ComputeSha1_FinishAsSha1(u8 context[92], u8 shaOutput[20], bool tlWipeData)
	{
		sha1_92finalize(context, shaOutput, tlWipeData);
	}

	void CALLTYPE oss_sha1ComputeSha1_FinishAsHex(u8 context[92], s8* tcHexOutput, bool tlInsertSpaces, bool tlWipeData)
	{
		u8	lcSha20Buffer[20];

		// Compute to our local buffer, then convert to hex
		sha1_92finalize(context, lcSha20Buffer, tlWipeData);
		sha1_convertSha20ToHex(lcSha20Buffer, tcHexOutput, tlInsertSpaces);
	}

	u64 CALLTYPE oss_sha1Compute64BitFromSha1(u8 sha20Bytes[20])
	{
		return(sha1_convertSha20To64Bit(sha20Bytes));
	}

	u32 CALLTYPE oss_sha1Compute32BitFromSha1(u8 sha20Bytes[20])
	{
		return(sha1_convertSha20To32Bit(sha20Bytes));
	}

	bool CALLTYPE oss_sha1Compare(u8 sha20Bytes1[20], u8 sha20Bytes2[20])
	{
		return(sha1_compare(sha20Bytes1, sha20Bytes2));
	}




//////////
//
// Loads the specified BXML file from disk.
//
// Note:  If tnPathnameLength is 0, then tcPathname is assumed to be a pointer to a memory block
//        with bxml data
//
// Returns:
//		-1			- syntax error
//		others		- pointer to the root node
//
//////
	SBxml* CALLTYPE oss_bxmlLoad(s8* tcPathname, u32 tnPathnameLength, u64* tnBytesRead, u64* tnErrorOffset, u64* tnErrorCode)
	{
		s8 buffer[_MAX_PATH + 1];


		// Copy our filename locally for NULL-termination
		memset(buffer, 0, sizeof(buffer));
		oss_copyUpToShortestString((u8*)buffer, sizeof(buffer), (u8*)tcPathname, tnPathnameLength);

		// Physically process the incoming file, and return the result
		return(ibxml_asciiLoadFile(buffer, tnBytesRead, tnErrorOffset, tnErrorCode));
	}




//////////
//
// Parses the indicated buffer as an BXML file, and returns the root BXML structure if valid.
//
//////
	SBxml* CALLTYPE oss_bxmlLoadFromBuffer(s8* tcBxmlData, u32 tnBxmlDataLength, u64* tnErrorOffset, u64* tnErrorCode)
	{
		return(ibxml_asciiLoadBuffer(tcBxmlData, tnBxmlDataLength, tnErrorOffset, tnErrorCode));
	}




//////////
//
// Saves the specified bxml node as the top-level node to the indicated file.
//
// Returns:
//		true		- success, and if tnBytesWritten is !NULL, it holds the total bytes written
//		false		- error opening indicated pathname, or writing to the file, and if tnBytesWritten is !NULL, it holds the number of bytes successfully written
//
//////
	bool CALLTYPE oss_bxmlSave(SBxml* bxml, s8* tcPathname, u32 tnPathnameLength, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnBytesWritten)
	{
		u64			lnHandle, lnError;
		s64			lnBytesWritten;
		bool		llResult;
		SBuilder*	build;


		// Initialize our return values
		llResult = false;
		if (tnBytesWritten)							*tnBytesWritten = 0;
		if (tcPathname && tnPathnameLength == 0)	tnPathnameLength = (u32)oss_strlen(_csu8p(tcPathname));

		// Make sure our environment is sane
		if (bxml && tcPathname)
		{
			// Attempt to create the indicated file
			lnHandle = oss_sharedAsciiOpenFile(tcPathname, true, false, false, false, false, true, true, false);
			if (lnHandle)
			{
				// Create our accumulation buffer
				oss_builderCreateAndInitialize(&build, _COMMON_BUFFER_BLOCK_SIZE);
				while (build)
				{
					// Save this node, which will save all child nodes
					lnError = 0;
					ibxml_saveNode(build, bxml, tlSaveChildNodes, tlSaveSiblings, &lnError);
					if (lnError != 0)
						break;		// Failure in building the save node

					// Right now, build->buffer is populated with the content to be written to disk
					lnBytesWritten = (s64)oss_sharedAsciiWriteFile(lnHandle, build->data, build->populatedLength);

					// Save the bytes written if they have requested it
					if (tnBytesWritten)
						*tnBytesWritten = lnBytesWritten;

					// If we had an error, we're done
					if (lnBytesWritten < 0)
						break;		// Failure

					// Release our build buffer
					oss_builderFreeAndRelease(&build);

					// When we get here, success
					llResult = true;
					break;
				}
				// When we get here, we're either successful or not
				if (oss_sharedAsciiCloseFile(lnHandle) != 0)
					llResult = false;		// Some error closing the handle
				// When we get here, llResult indicates our success
			}
		}
		// Indicate our success or failure
		return(llResult);
	}




//////////
//
// Serializes the BXML content to a buffer
//
//////
	void CALLTYPE oss_bxmlSaveToBuffer(SBxml* bxml, SBuilder** build, bool tlSaveChildNodes, bool tlSaveSiblings, u64* tnErrorNumber)
	{
		// Make sure our environment is sane
		if (bxml && build)
		{
			// Create our accumulation buffer
			oss_builderCreateAndInitialize(build, _COMMON_BUFFER_BLOCK_SIZE);

			// Save this node, which will save all child nodes
			if (*build)
				ibxml_saveNode(*build, bxml, tlSaveChildNodes, tlSaveSiblings, tnErrorNumber);
			// When we get here, we're either successful or not, tnErrorNumber and build are populated
		}
	}




//////////
//
// Create the attribute as a stand-alone creation, independent, free, in and of itself, probably a very happy attribute as it were, but only until it begins to get in touch with its inner feelings which exhibit the need to be part of something larger, which is not only a relationship or family, but also of being one of God's beloved. :-)
//
//////
	SBxmla* CALLTYPE oss_bxmlaCreate(s8* tcNewName, u32 tnNewNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength)
	{
		return(ibxml_attributeCreateAsWithData(tcNewName, tnNewNameLength, tcData, tnDataLength, tnTotalDataLength));
	}




//////////
//
// Sets the attribute name
//
//////
	bool CALLTYPE oss_bxmlaSetName(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength)
	{
		bool llResult;


		// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (bxmla && tcNewName && tnNewNameLength != 0)
		{
			// Create the new data block based on what is requested
			oss_datumSet(&bxmla->_name, (u8*)tcNewName, tnNewNameLength, true);
			llResult = (bxmla->_name.data._s8 != NULL);
		}
		// Indicate our success or failure
		return(llResult);
	}




//////////
//
// Sets the attribute to the indicated value.  If tcData is NULL, it resets the data value
// to an empty state.
//
//////
	bool CALLTYPE oss_bxmlaSetData(SBxmla* bxmla, s8* tcData, u32 tnDataLength)
	{
		bool llResult;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (bxmla && tcData)
		{
			// Create the new data block based on what is requested
			oss_datum2Set(&bxmla->_data, (u8*)tcData, tnDataLength, bxmla->_data.lengthTotal, true);

			// Update our new total length (if need be)
			bxmla->_data.lengthTotal = max(tnDataLength, bxmla->_data.lengthTotal);

			// Success!
			llResult = (bxmla->_data.datum.data._s8 != NULL);
		}
		// Indicate our success or failure
		return(llResult);
	}




//////////
//
// Sets the attribute's total length, which could override the current length of the
// attribute, thereby requiring it to be truncated if the value is less.
//
//////
	bool CALLTYPE oss_bxmlaSetTotalLength(SBxmla* bxmla, u32 tnDataLengthTotal)
	{
		bool	llResult;
		s8*		lcData;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (bxmla && bxmla->_data.lengthTotal != tnDataLengthTotal)
		{
			while (1)
			{
				if (bxmla->_data.datum.data._s8)
				{
					// We are adjusting data that's already been allocated
					if (bxmla->_data.lengthTotal > tnDataLengthTotal)
					{
						// We are decreasing the length
						if (tnDataLengthTotal >= bxmla->_data.datum.length)
						{
							// It's still bigger than that which is allocated, so we can just decrease it
							bxmla->_data.lengthTotal = tnDataLengthTotal;
							// Success
							llResult = true;

						} else {
							// It's smaller than the data already allocated, so we're reallocating
							if (tnDataLengthTotal == 0)
							{
								// They are removing all data
								// There is already data assigned, free it
								lcData = bxmla->_data.datum.data._s8;

								// Delete the data entry
								bxmla->_data.datum.data._s8		= NULL;
								bxmla->_data.datum.length		= 0;
								bxmla->_data.lengthTotal		= 0;

								// Release the actual memory block
								if (lcData)
									free(lcData);

								// Success
								llResult = true;

							} else {
								// There is some data still remaining
								lcData = (s8*)realloc(bxmla->_data.datum.data._s8, tnDataLengthTotal);
								if (!lcData)
									break;		// Failure to resize
								// If we get here, We're good

								// Set the new data and length
								bxmla->_data.datum.data._s8		= lcData;
								bxmla->_data.datum.length		= tnDataLengthTotal;
								bxmla->_data.lengthTotal		= tnDataLengthTotal;

								// Success
								llResult = true;
							}
						}

					} else {
						// We are increasing the length
						lcData = (s8*)realloc(bxmla->_data.datum.data._s8, tnDataLengthTotal);
						if (!lcData)
							break;		// Failure to resize
						// If we get here, We're good

						// Clear out the newly allocated memory
						memset(lcData + bxmla->_data.datum.length, 0, tnDataLengthTotal - (u32)bxmla->_data.datum.length);

						// Set the new data and length
						bxmla->_data.datum.data._s8		= lcData;
						bxmla->_data.datum.length		= tnDataLengthTotal;
						bxmla->_data.lengthTotal		= tnDataLengthTotal;

						// Success
						llResult = true;
					}

				} else {
					// We are creating the first data that will go here
// TODO:  untested code, breakpoint and examine
_asm nop;
					oss_datum2Set(&bxmla->_data, NULL, tnDataLengthTotal, tnDataLengthTotal, false);
				}
				// When we get here, we're done
				break;
			}
		}
		// When we get here, llResult indicates our status
		return(llResult);
	}




//////////
//
// Deletes the indicated attribute from the chain, returns it as a "now free" attribute which
// can then be manually deleted.
//
//////
	SBxmla* CALLTYPE oss_bxmlaDelete(SBxmla* bxmla, bool tlFreeMemory)
	{
		_isSBxmlAttributeDeleteParams	lbadp;
		SStartEndCallback				cb;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		if (bxmla)
		{
			// Remove this entry (if it exists in this parent)
			if (bxmla->_parent)
			{
				cb._func	= (u64)&iibxml_AttributeDeleteCallback;
				cb.extra	= (u64)&lbadp;
				oss_SEChain_deleteFromAfterCallback(&bxmla->_parent->_attributes, true, &cb);
			}
			// When we get here, it's either been removed, or not
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Inserts a new attribute by name and value before or after the indicated one.  If Bxmla
// is NULL, then it will either be appended to the very start, or very end of the list,
// based on tlAfter.
//
// Note:  If tnNameLength is 0, tcName is assumed to be an SBxmla* to be directly inserted.
//
//////
	bool CALLTYPE oss_bxmlaInsert(SBxml* bxml, SBxmla* bxmlaRef, s8* tcName, u32 tnNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength, bool tlAfter)
	{
		bool		llResult;
		SBxmla*		bxmlaNew;


		// Make sure our environment is sane
		// We only need to have a true bxml and tcName (for the attribute tag), the rest can be null / non-existent
		if (bxml && tcName && tnNameLength >= 1)
		{
			// Create the attribute
			bxmlaNew = oss_bxmlaCreate(tcName, tnNameLength, tcData, tnDataLength, tnTotalDataLength);
			if (bxmlaNew)
				return(oss_bxmlaInsertExisting(bxml, bxmlaRef, bxmlaNew, tlAfter));

		} else {
			// Invalid parameters
			llResult = false;
		}

		// Indicate our status
		return(llResult);
	}




//////////
//
// Inserts a new attribute by name and value before or after the indicated one.  If Bxmla
// is NULL, then it will either be appended to the very start, or very end of the list,
// based on tlAfter.
//
// Note:  If tnNameLength is 0, tcName is assumed to be an SBxmla* to be directly inserted.
//
//////
	bool CALLTYPE oss_bxmlaInsertExisting(SBxml* bxml, SBxmla* bxmlaRef, SBxmla* bxmlaNew, bool tlAfter)
	{
		bool llResult;


		// Make sure our environment is sane
		// We only need to have a true bxml and tcName (for the attribute tag), the rest can be null / non-existent
		if (bxml && bxmlaNew)
		{
			// Append it to the chain after the entry
			oss_SEChain_appendExistingRelativeToMember(&bxml->_attributes, (SLL*)bxmlaRef, oss_getNextUniqueId(), (SLL*)bxmlaNew, _COMMON_START_END_BLOCK_SIZE, tlAfter, &llResult);

		} else {
			// Invalid parameters
			llResult = false;
		}

		// Indicate our status
		return(llResult);
	}




//////////
//
// Copies the attribute to a new stand-alone instance.
//
//////
	SBxmla* CALLTYPE oss_bxmlaCopy(SBxmla* bxmla)
	{
		return(ibxml_attributeDuplicate(bxmla));
	}




//////////
//
// Copies the attribute as a new name for a stand-alone instance.
//
//////
	SBxmla* CALLTYPE oss_bxmlaCopyAs(SBxmla* bxmla, s8* tcNewName, u32 tnNewNameLength)
	{
		return(ibxml_attributeDuplicateAs(bxmla, tcNewName, tnNewNameLength));
	}




//////////
//
// Computes the SHA-1 of the tag+data, or just tag, or just data.  The 64-bit return value is
// the summed up portions of the 20-byte form.  It will obviously not have the same period without
// collisions, but may be sufficient for simple hashing.
//
//////
	u64 CALLTYPE oss_bxmlaSha1One(SBxmla* bxmla, u8 sha20Bytes[20])
	{
		return(ioss_bxmlAttributeSha1One(bxmla, sha20Bytes));
	}

	u64 CALLTYPE oss_bxmlaSha1(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ioss_bxmlAttributeSha1(bxml, sha20Bytes));
	}

	u64 CALLTYPE oss_bxmlaSha1Tag(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ioss_bxmlAttributeSha1Tag(bxml, sha20Bytes));
	}

	u64 CALLTYPE oss_bxmlaSha1Data(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ioss_bxmlAttributeSha1Data(bxml, sha20Bytes));
	}




//////////
//
// Called to return the values directly without having to obtain 
//
//////
	u32 CALLTYPE oss_bxmlaFindAndGetString(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, SDatum* tsResult, bool* tlError)
	{
		return(oss_bxmlaGetString(iioss_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tsResult, tlError));
	}

	u32 CALLTYPE oss_bxmlaFindAndGetU32(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError)
	{
		return(oss_bxmlaGetU32(iioss_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tlError));
	}

	u64 CALLTYPE oss_bxmlaFindAndGetU64(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError)
	{
		return(oss_bxmlaGetU64(iioss_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tlError));
	}

	bool CALLTYPE oss_bxmlaFindAndGetBool(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError)
	{
		return(oss_bxmlaGetBool(iioss_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tlError));
	}

	f32 CALLTYPE oss_bxmlaFindAndGetF32(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError)
	{
		return(oss_bxmlaGetF32(iioss_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tlError));
	}

	f64 CALLTYPE oss_bxmlaFindAndGetF64(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance, bool* tlError)
	{
		return(oss_bxmlaGetF64(iioss_bxmlFindAttribute(bxml, bxmla, tsWildcardSearch, tnInstance), tlError));
	}

	u32 CALLTYPE oss_bxmlaGetString(SBxmla* bxmla, SDatum* tsResult, bool* tlError)
	{
		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Copy our datum
			if (tsResult)
				memcpy(&tsResult->data, &bxmla->_data.datum, sizeof(SDatum));

			// Indicate the length of the value
			return((u32)bxmla->_data.datum.length);

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}

	u32 CALLTYPE oss_bxmlaGetU32(SBxmla* bxmla, bool* tlError)
	{
		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Indicate our value
			return(atoi(bxmla->_data.datum.data._s8));

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}

	u64 CALLTYPE oss_bxmlaGetU64(SBxmla* bxmla, bool* tlError)
	{
		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Indicate our value
			return(atol(bxmla->_data.datum.data._s8));

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}

	// Valid "true" conditions are 1,Y,y,T,t
	bool CALLTYPE oss_bxmlaGetBool(SBxmla* bxmla, bool* tlError)
	{
		s8 lc;


		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Indicate our value
			lc = bxmla->_data.datum.data._s8[0];
			return((lc == '1' || lc == 'Y' || lc == 'y' || lc == 'T' || lc == 't'));

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}

	f32 CALLTYPE oss_bxmlaGetF32(SBxmla* bxmla, bool* tlError)
	{
		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Indicate our value
			return((f32)atof(bxmla->_data.datum.data._s8));

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}

	f64 CALLTYPE oss_bxmlaGetF64(SBxmla* bxmla, bool* tlError)
	{
		if (bxmla && bxmla->_data.datum.data._u8 && bxmla->_data.datum.length != 0)
		{
			// Indicate success
			if (*tlError)
				*tlError = false;

			// Indicate our value
			return(atof(bxmla->_data.datum.data._s8));

		} else {
			// Indicate failure (unable to find the attribute)
			if (tlError)
				*tlError = true;

			// Return anything
			return(0);
		}
	}




//////////
//
// Provided as convenient access to the next/prev members for a given attribute.  These
// can be accessed natively by navigating the high and tricky waters of the SBxmla structure's
// ll member ... but why bother when we've gone to such trouble to provide this assistance tool? :-)
//
//////
	SBxmla* CALLTYPE oss_bxmlaGetNext(SBxmla* bxmla)
	{
		u32		lnI;
		bool	llFound;
		SBxml*	bxml;


		// Make sure the environment is sane
		if (bxmla && bxmla->_parent)
		{
			// Iterate through all the attributes to find the next one
			bxml	= (SBxml*)bxmla->_parent;
			llFound	= false;
			for (lnI = 0; lnI < bxml->_attributes.masterCount; lnI++)
			{
				if (bxml->_attributes.master[lnI]->used)
				{
					if (llFound)
					{
						// This is our return item
						return((SBxmla*)bxml->_attributes.master[lnI]->ptr);

					} else if (bxml->_attributes.master[lnI]->ptr == bxmla) {
						// We found the item, so the next item is the next one
						llFound = true;
					}
				}
			}
		}
		// If we get here, not found
		return(NULL);
	}

	SBxmla* CALLTYPE oss_bxmlaGetPrev(SBxmla* bxmla)
	{
		u32		lnI, lnILast;
		SBxml*	bxml;


		// Make sure the environment is sane
		if (bxmla && bxmla->_parent)
		{
			// Iterate through all the attributes to find the next one
			bxml	= (SBxml*)bxmla->_parent;
			lnILast	= -1;
			for (lnI = 0; lnI < bxml->_attributes.masterCount; lnI++)
			{
				if (bxml->_attributes.master[lnI]->used)
				{
					// Is this a match?
					if (bxml->_attributes.master[lnI]->ptr == bxmla)
					{
						// We found the item, so the previous item is the one
						if (lnILast == -1)
						{
							// Nothing previous
							return(NULL);

						} else {
							// We have one previous to return
							return((SBxmla*)bxml->_attributes.master[lnILast]->ptr);
						}
					}

					// This is a previous attribute candidate, so update it
					lnILast = lnI;
				}
			}
		}
		// If we get here, not found
		return(NULL);
	}




//////////
//
// Creates the indicated stand-alone node
//
//////
	SBxml* CALLTYPE oss_bxmlNodeCreate(s8* tcNewName, u32 tnNewNameLength)
	{
		return(ibxml_nodeCreateAs(tcNewName, tnNewNameLength));
	}




//////////
//
// Called to modify the tag name
//
//////
	bool CALLTYPE oss_bxmlNodeSetName(SBxml* bxml, s8* tcNewName, u32 tnNewNameLength)
	{
		bool llResult;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (bxml && tcNewName && tnNewNameLength != 0)
		{
			// Create the new data block based on what is requested
			oss_datumSet(&bxml->_name, (u8*)tcNewName, tnNewNameLength, true);
			llResult = (bxml->_name.data._s8 != NULL);
		}
		// Indicate our success or failure
		return(llResult);
	}




//////////
//
// Deletes the indicated node, and all child nodes, and all attributes contained therein or below
// if tlFreeMemory is true, otherwise simply disconnects it from the 4-way node configuration.
//
//////
	bool CALLTYPE oss_bxmlNodeDelete(SBxml* bxml, bool tlFreeMemory)
	{
		bool llResult;


		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// Deletes the indicated node from wherever it is in the parent chain
			llResult = oss_ll4bxml_orphanize((SLL4*)bxml);

			// When we get here, it has been disconnected, which means it now exists as an orphan
			// Now we need to delete everything (if indeed we do), clearing up the entire path, including all attributes, children, everything
			if (llResult && tlFreeMemory)
				llResult = ibxml_nodeDeleteBranch(bxml);

			// When we get here, llResult indicates if we weer successful
		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// Inserts the indicated node before or after the current sibling/location.
//
// Note:  If tnNameLength is 0, tcName is assumed to be an existing BxmlNode that will be inserted directly.
//
//////
	bool CALLTYPE oss_bxmlNodeInsert(SBxml* bxml, SBxml* bxmlRef, bool tlAfter)
	{
		bool llResult;


		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// Inserts the node before or after the reference node as a sibling
			llResult = oss_ll4bxml_insert((SLL4*)bxml, (SLL4*)bxmlRef, tlAfter);

			// If we were successful, update the level
			if (llResult)
				bxml->level = bxmlRef->level;
		}
		// Indicate our status
		return(llResult);
	}

	bool CALLTYPE oss_bxmlNodeInsertAsChild(SBxml* bxml, SBxml* bxmlParent, bool tlAfter)
	{
		bool llResult;


		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// Inserts the node relative tothe reference node as a child
			llResult = oss_ll4bxml_insertAsChild((SLL4*)bxml, (SLL4*)bxmlParent, tlAfter);

			// If we were successful, update the level
			if (llResult)
				bxml->level = bxmlParent->level + 1;
		}
		// Indicate our status
		return(llResult);
	}

	bool CALLTYPE oss_bxmlNodeInsertAsChildAfter(SBxml* bxml, SBxml* bxmlParent, SBxml* bxmlRef, bool tlAfter)
	{
		bool llResult;


		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// Deletes the indicated node from wherever it is in the parent chain
			llResult = oss_ll4bxml_insertAsChildRegarding((SLL4*)bxml, (SLL4*)bxmlParent, (SLL4*)bxmlRef, tlAfter);

			// If we were successful, update the level
			if (llResult)
				bxml->level = bxmlParent->level + 1;
		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// Copies the indicated node, and optionally copies all attributes and child nodes as well.
//
//////
	SBxml* CALLTYPE oss_bxmlNodeCopy(SBxml* bxml, bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult)
	{
		if (bxml && bxml->_name.data._s8 && bxml->_name.length != 0)
			return(ibxml_nodeCopyAs(bxml, bxml->_name.data._s8, bxml->_name.length, tlCopyAttributes, tlCopyChildren, tlResult));
		
		// Failure in passed parameters
		return(NULL);
	}




//////////
//
// Copies the indicated node as the new name, and optionally copies all attributes and child nodes as well.
//
//////
	SBxml* CALLTYPE oss_bxmlNodeCopyAs(SBxml* bxml, s8* tcNewName, u32 tnNewNameLength, bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult)
	{
		return(ibxml_nodeCopyAs(bxml, tcNewName, tnNewNameLength, tlCopyAttributes, tlCopyChildren, tlResult));
	}




//////////
//
// Computes the SHA-1 of the tag+data, or just tag, or just data.  The 64-bit return value is
// the summed up portions of the 20-byte form.  It will obviously not have the same period without
// collisions, but may be sufficient for simple hashing.
//
//////
	u64 CALLTYPE oss_bxmlNodeSha1(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ioss_bxmlNodeSha1(bxml, sha20Bytes));
	}

	u64 CALLTYPE oss_bxmlNodeSha1Tag(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ioss_bxmlNodeSha1Tag(bxml, sha20Bytes));
	}

	u64 CALLTYPE oss_bxmlNodeSha1Data(SBxml* bxml, u8 sha20Bytes[20])
	{
		return(ioss_bxmlNodeSha1Data(bxml, sha20Bytes));
	}




//////////
//
// Added for logical use in code to make it clear to developers what's going on, without having
// to navigate the high and tricky waters of structures.
//
//////
	SBxml* CALLTYPE oss_bxmlNodeGetNext(SBxml* bxml)
	{
		SBxml* bxmlTarget;


		// Make sure the environment is sane
		bxmlTarget = NULL;
		if (bxml)
			bxmlTarget = (SBxml*)bxml->ll4.next;
		
		// Return our target
		return(bxmlTarget);
	}

	SBxml* CALLTYPE oss_bxmlNodeGetPrev(SBxml* bxml)
	{
		SBxml* bxmlTarget;


		// Make sure the environment is sane
		bxmlTarget = NULL;
		if (bxml)
			bxmlTarget = (SBxml*)bxml->ll4.prev;

		// Return our target
		return(bxmlTarget);
	}

	SBxml* CALLTYPE oss_bxmlNodeGetParent(SBxml* bxml)
	{
		SBxml* bxmlTarget;


		// Make sure the environment is sane
		bxmlTarget = NULL;
		if (bxml)
			bxmlTarget = (SBxml*)bxml->ll4.parent;

		// Return our target
		return(bxmlTarget);
	}

	SBxml* CALLTYPE oss_bxmlNodeGetFirstChild(SBxml* bxml)
	{
		SBxml* bxmlTarget;


		// Make sure the environment is sane
		bxmlTarget = NULL;
		if (bxml)
			bxmlTarget = (SBxml*)bxml->ll4.child;

		// Return our target
		return(bxmlTarget);
	}

	SBxmla* CALLTYPE oss_bxmlNodeGetFirstAttribute(SBxml* bxml)
	{
		u32 lnI;


		// Make sure the environment is sane
		if (bxml)
		{
			for (lnI = 0; lnI < bxml->_attributes.masterCount; lnI++)
			{
				if (bxml->_attributes.master[lnI]->used && bxml->_attributes.master[lnI]->ptr)
					return((SBxmla*)bxml->_attributes.master[lnI]->ptr);
			}
		}
		// If we get here, no attribute
		return(NULL);
	}




//////////
//
// Called to find the indicated attribute directly for the indicated node
//
//////
	SBxmla* CALLTYPE oss_bxmlFindAttribute(SBxml* bxml, SDatum* tsWildcardSearch, u32 tnInstance)
	{
		u32		lnInstance;
		SBxmla*	bxmla;


		lnInstance	= 0;
		bxmla		= oss_bxmlNodeGetFirstAttribute(bxml);
		while (bxmla)
		{
			// Is this a match?
			if (oss_wildcardMatch(_csu8p(bxmla->_name.data._u8), _csu8p(tsWildcardSearch->data._u8), false) == 0)
			{
				++lnInstance;
				if (lnInstance >= tnInstance)
					break;	// This is our match
			}

			// Move to next attribute
			bxmla = oss_bxmlaGetNext(bxmla);
		}
		// Indicate our failure
		return(bxmla);
	}




//////////
//
// Using the indicated wildcard search string as begins searching from the root node.
// It locates (from the top down) the first entry matching the search criteria.
//
// Note:  If x is provided, then it will be populated with a structure to subsequently pass to oss_bxmlFindContinue()
//
//////
	bool CALLTYPE oss_bxmlFindFirst(SBxml* bxmlRoot, SBxml** bxmlNodeFound, SBxmla** bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, bool tlSearchAttributes, void** x)
	{
		// Make sure the environment is sane
		if (bxmlRoot && tsWildcardSearch && tsWildcardSearch->data._u8 && tsWildcardSearch->length != 0 && (bxmlNodeFound || bxmlaAttributeFound/*at least one must be defined*/))
			return(iioss_bxmlFindFirst(bxmlRoot, bxmlNodeFound, bxmlaAttributeFound, tsWildcardSearch, tlTraverseChildren, tlSearchAttributes, x));

		// Failure
		return(false);
	}




//////////
//
// Will continue from a previous search location, or if no prior search location exists, or if
// the end has been reached (and previously reported), it will start again from the top down.
//
//////
	bool CALLTYPE oss_bxmlFindContinue(void* x)
	{
		// Make sure the environment is sane
		if (x)
			return(iioss_bxmlFindContinue(x));

		// Failure
		return(false);
	}




//////////
//
// Will search from the top down for nodes matching the indicated search pattern, and when
// found will append them to a Start/end list that can be traversed.
//
// Note:  bxmlFinds and bxmlaFinds will be appended to.
// Note:  To find a specific number of entries, populate *tnMaxFindsToInclude, otherwise use -1
//
//////
	u32 CALLTYPE oss_bxmlFindAllAsStartEndLists(SBxml* bxmlRoot, SStartEnd* bxmlFinds, SStartEnd* bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren, bool tlSearchAttributes)
	{
		u32				lnMaxFinds;
		bool			llResult;
		void*			x;
		SBxml*			bxml;
		SBxmla*			bxmla;
		SBxmlList*		bxmlList;
		SBxmlaList*		bxmlaList;


		//////////
		// Do we find at least one?
		//////
			// Do we have a sane environment?
			if (bxmlRoot && (bxmlFinds || bxmlaFinds) && tsWildcardSearch && tnMaxFindsToInclude)
			{
				// Initialize
				lnMaxFinds	= *tnMaxFindsToInclude;
				bxml		= NULL;
				bxmla		= NULL;
				x			= NULL;


				//////////
				// Iterate so long as there are finds
				//////
					// Find first here, and the findContinue is at the end of the do..while
					*tnMaxFindsToInclude = 0;
					if (oss_bxmlFindFirst(bxmlRoot, &bxml, &bxmla, tsWildcardSearch, tlTraverseChildren, tlSearchAttributes, &x))
					{
						// Found at least one
						do {

							// Store it
							if (bxml)
							{
								// A node was found
								bxmlList = (SBxmlList*)oss_SEChain_append(bxmlFinds, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SBxmlList), _COMMON_START_END_BLOCK_SIZE, &llResult);

								// Store that node
								if (bxmlList)
								{
									++(*tnMaxFindsToInclude);		// Increase the count
									bxmlList->bxml = bxml;			// Store the pointer
								}

							} else {
								// An attribute was found
								bxmlaList = (SBxmlaList*)oss_SEChain_append(bxmlaFinds, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SBxmlaList), _COMMON_START_END_BLOCK_SIZE, &llResult);

								// Store that attribute
								if (bxmlaList)
								{
									++(*tnMaxFindsToInclude);		// Increase the count
									bxmlaList->bxmla = bxmla;		// Store the pointer
								}
							}

						// And keep going
						} while (*tnMaxFindsToInclude < lnMaxFinds && oss_bxmlFindContinue(x));

						// when we get here, they've all been found
						oss_free(x);

						// Indicate how many were found
						return(*tnMaxFindsToInclude);

					}
					//else no finds
			}


		//////////
		// If we get here, no finds
		//////
			return(0);
	}




//////////
//
// Searches from the indicated node for data items (attributes) and returns the first match,
// along with a structure that can be used to pass to oss_bxmlDataFindContinue() in subsequent
// finds.
//
//////
	bool CALLTYPE oss_bxmlDataFindFirst(SBxml* bxmlRoot, SBxmla** bxmlaAttributeFound, SDatum* tsWildcardSearch, bool tlTraverseChildren, void** x)
	{
		// Make sure the environment is sane
		if (bxmlRoot && tsWildcardSearch && tsWildcardSearch->data._u8 && tsWildcardSearch->length != 0 && bxmlaAttributeFound)
			return(iioss_bxmlDataFindFirst(bxmlRoot, bxmlaAttributeFound, tsWildcardSearch, tlTraverseChildren, x));

		// Failure
		return(false);
	}




//////////
//
// Searches from the indicated node for data items (attributes) and returns the first match,
// along with a structure that can be used to pass to oss_bxmlDataFindContinue() in subsequent
// finds.
//
//////
	bool CALLTYPE oss_bxmlDataFindContinue(void* x)
	{
		// Make sure the environment is sane
		if (x)
			return(iioss_bxmlDataFindContinue(x));

		// Failure
		return(false);
	}




//////////
//
// Searches from the indicated node for data items (attributes) and returns the first match,
// along with a structure that can be used to pass to oss_bxmlDataFindContinue() in subsequent
// finds.
//
//////
	u32 CALLTYPE oss_bxmlDataFindAllAsStartEndList(SBxml* bxmlRoot, SStartEnd* bxmlaFinds, SDatum* tsWildcardSearch, u32* tnMaxFindsToInclude, bool tlTraverseChildren)
	{
		u32				lnMaxFinds;
		bool			llResult;
		void*			x;
		SBxml*			bxml;
		SBxmla*			bxmla;
		SBxmlaList*		bxmlaList;


		//////////
		// Do we find at least one?
		//////
			// Do we have a sane environment?
			if (bxmlRoot && bxmlaFinds && tsWildcardSearch && tnMaxFindsToInclude)
			{
				// Initialize
				lnMaxFinds	= *tnMaxFindsToInclude;
				bxml		= NULL;
				bxmla		= NULL;
				x			= NULL;


				//////////
				// Iterate so long as there are finds
				//////
					// Find first here, and the findContinue is at the end of the do..while
					*tnMaxFindsToInclude = 0;
					if (oss_bxmlDataFindFirst(bxmlRoot, &bxmla, tsWildcardSearch, tlTraverseChildren, &x))
					{
						// Found at least one
						do {

							// Store it
							if (bxmla)
							{
								// An attribute was found
								bxmlaList = (SBxmlaList*)oss_SEChain_append(bxmlaFinds, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SBxmlaList), _COMMON_START_END_BLOCK_SIZE, &llResult);

								// Store that attribute
								if (bxmlaList)
								{
									++(*tnMaxFindsToInclude);		// Increase the count
									bxmlaList->bxmla = bxmla;		// Store the pointer
								}
							}

						// And keep going
						} while (*tnMaxFindsToInclude < lnMaxFinds && oss_bxmlDataFindContinue(x));

						// when we get here, they've all been found
						oss_free(x);

						// Indicate how many were found
						return(*tnMaxFindsToInclude);

					}
					//else no finds
			}


		//////////
		// If we get here, no finds
		//////
			return(0);
	}




//////////
//
// Called to return the last error information for any BXML operations
//
//////
	void CALLTYPE oss_bxmlGetLastError(SBxmlError* errorInfo)
	{
// TODO:  we need to record more explicit error messages so they can be reported on politely
#pragma message("vo.cpp::oss_bxmlGetLastError() contains the ability to retrieve the last bxml error, however not all errors are being captured or recorded.")
		oss_memcpy((s8*)errorInfo, (s8*)&gsLastErrorInfo, sizeof(SBxmlError));
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
			lt = (_iswSThreads*)oss_SEChain_append(&gseRootForeignThreads, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(_iswSThreads), _COMMON_START_END_BLOCK_SIZE, NULL);
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
		lt = (_iswSThreads*)oss_SEChain_searchByUniqueId(&gseRootForeignThreads, ossData);
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
		lt = (_iswSThreads*)oss_SEChain_searchByUniqueId(&gseRootForeignThreads, ossData);
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
		lt = (_iswSThreads*)oss_SEChain_searchByUniqueId(&gseRootForeignThreads, ossData);
		while (lt && lt->isViable)
		{
			// Resume the thread
			TerminateThread(lt->os_threadHandle, tnTerminationCode);

			// Delete the item from the Start/end chain
			oss_SEChain_deleteFrom(&gseRootForeignThreads, (SLL*)lt, true);

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
#include "vo_sup.cpp"					// Support algorithms for VVMOSS in general
#include "vo_Bxml.cpp"					// BXML algorithms

// THe following are include files of external (non-VVM) LibSF projects
#include "\libsf\utils\sha1\sha1.cpp"	// SHA-1 hashing algorithm
