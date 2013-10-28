//////////
//
// /libsf/vvm/vvmoss/vo_sup.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     September 20, 2012 - Initial creation
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




#include "vo_plugins.cpp"




//////////
//
// Callback for enumerating through the cached fonts we've already allocated
//
//////
	bool iioss_findSystemFontByHandleCallback(SStartEndCallback* cb)
	{
		// See if this is the font handle we're looking for
		return(((_iswSSystemFont*)cb->ptr)->handle == (HFONT)cb->extra/*fontHandle*/);
	}




//////////
//
// Register the message window class with Windows
//
//////
	bool ioss_registerWindowClasses(u32* tnError)
	{
		WNDCLASSEXA		wcexa;
		WNDCLASSEXW		wcexu;
		ATOM			a;


		// Message window callback
		memset(&wcexa, 0, sizeof(wcexa));
		wcexa.cbSize			= sizeof(WNDCLASSEXA);
		wcexa.lpfnWndProc		= ioss_wndProc_Message;
		wcexa.hInstance			= ghInstance;
		wcexa.lpszClassName		= gcVvmOssMessageClass;
		a = RegisterClassExA(&wcexa);
		// For debugging, get the error if there was cause for one
		if (a == (ATOM)NULL)
		{
			if (tnError)		*tnError = GetLastError();
			return(false);
		}

		// Visible window callback (ascii)
		memset(&wcexa, 0, sizeof(wcexa));
		wcexa.cbSize			= sizeof(WNDCLASSEXA);
		wcexa.lpfnWndProc		= ioss_wndProc_Visible;
		wcexa.hInstance			= ghInstance;
		wcexa.hCursor			= LoadCursor(NULL, IDC_ARROW);
		wcexa.lpszClassName		= gcVvmOssVisibleClass;
		wcexa.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		a = RegisterClassExA(&wcexa);
		// For debugging, get the error if there was cause for one
		if (a == (ATOM)NULL)
		{
			if (tnError)		*tnError = GetLastError();
			return(false);
		}

		// Visible window callback (unicode)
		memset(&wcexu, 0, sizeof(wcexu));
		wcexu.cbSize			= sizeof(WNDCLASSEXW);
		wcexu.lpfnWndProc		= ioss_wndProc_Visible;
		wcexu.hInstance			= ghInstance;
		wcexu.hCursor			= LoadCursor(NULL, IDC_ARROW);
		wcexu.lpszClassName		= guVvmOssVisibleClass;
		wcexu.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		a = RegisterClassExW(&wcexu);
		// For debugging, get the error if there was cause for one
		if (a == (ATOM)NULL)
		{
			if (tnError)		*tnError = GetLastError();
			return(false);
		}
		// We're good
		return(true);
	}




//////////
//
// Create the message-only window
//
//////
	HWND ioss_createMessageWindow(void)
	{
		return(CreateWindowA(gcVvmOssMessageClass, gcVvmOssMessageClass, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, ghInstance, NULL));
	}




//////////
//
// A message loop to process windows that are created
//
//////
	DWORD CALLTYPE ioss_messageLoop(LPVOID lpParameter)
	{
		MSG msg;


		// Process messages
		ghWndMsg = ioss_createMessageWindow();
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// All done
		return(msg.wParam);
	}




//////////
//
// Get the next Unique ID
//
//////
	u64 ioss_getNextUniqueId(void)
	{
		u64 lnValue;

		// Synchronized access
		oss_lockSemaphore((u64)&gcsUniqueIdAccess);

		// Get our value and increment
		lnValue = gnNextUniqueId;
		++gnNextUniqueId;

		// All done
		oss_unlockSemaphore((u64)&gcsUniqueIdAccess);

		// Return that value
		return(lnValue);
	}




//////////
//
// Get the next N Unique IDs
//
// Returns:
//		The last unique id assigned
//		-1 if error
//
//////
	u64 ioss_getNextN_UniqueIds(u64* tnArrayBase, u32 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (tnArrayBase && tnCount > 0)
		{
			// Synchronized access
			oss_lockSemaphore((u64)&gcsUniqueIdAccess);

			// Get our value and increment
			for (lnI = 0; lnI < tnCount; lnI++)
			{
				tnArrayBase[lnI] = gnNextUniqueId;
				++gnNextUniqueId;
			}

			// All done
			oss_unlockSemaphore((u64)&gcsUniqueIdAccess);

			// Return that value
			return(tnArrayBase[lnI - 1]);

		} else {
			// Hmmm... bad params, indicate failure
			return(-1);
		}
	}




//////////
//
// Load the specified debugger
//
//////
	u64 ioss_loadDebuggerDll(u32 tnUniqueId)
	{
		u32		lnLength;
		FILE*	lfh;
		s8		buffer[_MAX_PATH];


		// Create the pathname to the vmm_########.ini file
		GetCurrentDirectoryA(sizeof(buffer), buffer);
		lnLength = strlen(buffer);
		if (buffer[lnLength - 1] != '\\')
		{
			buffer[lnLength] = '\\';
			++lnLength;
		}
		sprintf_s(buffer + lnLength, sizeof(buffer) - lnLength, "vvm_%08x.ini\000", tnUniqueId);
		
		// Try to open the file
		lfh = fopen(buffer, "rb");
		return(ioss_loadDebuggerByIniFile(lfh, tnUniqueId, buffer));
	}




//////////
//
// Load the ini contents of the specified file handle.
// If successful, delete the file from disk.
//
//////
	u64 ioss_loadDebuggerByIniFile(FILE* tfh, u32 tnUniqueId, s8* tcPathname)
	{
		u64		lnResult;
		u32		lnSize, lnNumread, lnNameStart, lnNameEnd, lnDllStart, lnDllEnd;
		s8*		contents;


		// Initially assume a failure
		// Only a full success will lower the flag
		lnResult = -1;

		// Load the contents and look for two
		if (tfh)
		{
			// We're good, load the contents
			fseek(tfh, 0, SEEK_END);
			lnSize = ftell(tfh);
			fseek(tfh, 0, SEEK_SET);

			// Allocate memory for contents
			contents = (s8*)malloc(lnSize);
			if (contents)
			{
				// We have our memory, read the contents
				lnNumread = fread(contents, 1, lnSize, tfh);
				if (lnNumread == lnSize)
				{
					// We're good, process each line
					ioss_locateLineThenGetStartAndEnd(contents, lnSize, (s8*)cgcName, sizeof(cgcName) - 1, &lnNameStart, &lnNameEnd);
					ioss_locateLineThenGetStartAndEnd(contents, lnSize, (s8*)cgcDll,  sizeof(cgcDll)  - 1, &lnDllStart,  &lnDllEnd);
					if (lnNameStart != -1 && lnDllStart != -1)
					{
						// We have both of them, try to load the specified dll
						lnResult = ioss_validateDebuggerDll(contents + lnDllStart, lnDllEnd - lnDllStart, tnUniqueId);
					}
				}
				// All done here
				free(contents);
				fclose(tfh);
				// Delete the file
				DeleteFileA(tcPathname);
			}
		}

		// Indicate our success or failure
		return(lnResult);
	}




///////////
//
// Searches the haystack for the specified needle, and if found then determines the length of
// the item until the end of line, or end of the haystack, whichever comes first.
//
//////
	void ioss_locateLineThenGetStartAndEnd( s8* tcHaystack,  u32 tnHaystackLength,
										s8* tcNeedle,    u32 tnNeedleLength,
										u32* tnpStart,   u32* tnpEnd)
	{
		u32 lnI, lnStart;


		// Initialize their location to not existing
		*tnpStart	= -1;
		*tnpEnd		= -1;

		// Search for the specified item
		lnStart = ioss_searchHaystackForNeedle(tcHaystack, tnHaystackLength, tcNeedle, tnNeedleLength);
		if (lnStart != -1)
		{
			// We found it
			*tnpStart = lnStart + tnNeedleLength;

			// Find out how long the rest of the line is, or until the end of the haystack
			for (lnI = *tnpStart; lnI < tnHaystackLength; lnI++)
			{
				// Look for carriage return or line feed
				if (tcHaystack[lnI] == 13 || tcHaystack[lnI] == 10)
				{
					// We're done
					break;
				}
			}
			// When we get here, we're done (one way or another)
			*tnpEnd = lnI;
		}
	}




//////////
//
// Searches the specified haystack for the specified needle (ignores case)
//
//////
	u32 ioss_searchHaystackForNeedle(s8* tcHaystack, u32 tnHaystackLength, s8* tcNeedle, u32 tnNeedleLength)
	{
		u32 lnI;

		// Check to see if the specified word / phrase / whatever exists on this line
		for (lnI = 0; lnI <= tnHaystackLength - tnNeedleLength; lnI++)
		{
			if (_memicmp(tcHaystack + lnI, tcNeedle, tnNeedleLength) == 0)
				return(lnI);
		}

		// Failure
		return(-1);
	}




//////////
//
// Searches the specified haystack for the specified needle (ignores case)
//
//////
	u32 ioss_searchHaystackForNeedleCase(s8* tcHaystack, u32 tnHaystackLength, s8* tcNeedle, u32 tnNeedleLength)
	{
		u32 lnI;

		// Check to see if the specified word / phrase / whatever exists on this line
		for (lnI = 0; lnI <= tnHaystackLength - tnNeedleLength; lnI++)
		{
			if (memcmp(tcHaystack + lnI, tcNeedle, tnNeedleLength) == 0)
				return(lnI);
		}

		// Failure
		return(-1);
	}




//////////
//
// Validate a debugger DLL, making sure it has all of the required functions.
//
//////
	struct SDebuggerFirstCallback
	{
		u64		(CALLTYPE *vvm_firstCallback)(u64 tnCallbackAddress, u32 tnUniqueId);
	};
	u64 ioss_validateDebuggerDll(s8* tcDllPathname, u32 tnDllPathnameLength, u32 tnUniqueId)
	{
		u64						lnResult;
		HINSTANCE				dllInstance;
		s8						buffer[_MAX_PATH];
		void**					lnFuncAddress;
		void*					lnAddress;
		SDebuggerFirstCallback	t;


		// Initially indicate failure
		lnResult = -1;

		// Copy the pathname
		oss_memset(buffer, 0, sizeof(buffer));
		oss_memcpy(buffer, tcDllPathname, tnDllPathnameLength);

		// Try to open it
		dllInstance = LoadLibraryA(buffer);
		if (dllInstance)
		{
			// Loaded, see if it has all the functions
			// Ask the VVM for this specific function location
			lnFuncAddress	= (void**)&t.vvm_firstCallback;
			lnAddress		= GetProcAddress(dllInstance, "vvm_firstCallback");
			if (lnAddress)
			{
				// If we get here, this function was found and we can store it
				*lnFuncAddress = lnAddress;

				// Call the debugger's interface with the 
				lnFuncAddress = (void**)vvm_debuggerInterface;
				lnResult = t.vvm_firstCallback((u64)lnFuncAddress, tnUniqueId);
			}
		}

		// All done
		return(lnResult);
	}




//////////
//
// Create a visible window in the main GUI thread
//
//////
	void ioss_createVisibleWindow(SOssWindow* tisw, _iswSOssWindowLL** tow)
	{
		u32					lnError, lnWindowStyle, lnWidthDelta, lnHeightDelta;
		SOssWindow			lisw;
		w16*				luCaption;
		_iswSOssWindowLL*	low;
		RECT				lrc, lrco;


		// See if we should position / center the window on vertical or horizontal
		GetWindowRect(GetDesktopWindow(), &lrc);
		if (tisw->osX == -1)
			tisw->osX = ((lrc.right - lrc.left) - tisw->width) / 2;		// Position horizontal

		if (tisw->osY == -1)
			tisw->osY = ((lrc.bottom - lrc.top) - tisw->height) / 2;		// Position vertical


		// Determine the geometry for this type of window
		lnWindowStyle = ioss_getWindowStyle(tisw);
		SetRect(&lrco, 0, 0, tisw->width, tisw->height);
		SetRect(&lrc,  0, 0, tisw->width, tisw->height);
		AdjustWindowRect(&lrc, lnWindowStyle, FALSE);
		tisw->osWidth	= lrc.right - lrc.left;
		tisw->osHeight	= lrc.bottom - lrc.top;

		// Adjust the minimum width by any requirements of the border
		lnWidthDelta	= (lrc.right  - lrc.left) - (lrco.right  - lrco.left);
		lnHeightDelta	= (lrc.bottom - lrc.top)  - (lrco.bottom - lrco.top);
		tisw->widthMax	= ((s32)tisw->widthMax  <= 0 ? tisw->width  : tisw->widthMax)  + lnWidthDelta;
		tisw->heightMax	= ((s32)tisw->heightMax <= 0 ? tisw->height : tisw->heightMax) + lnHeightDelta;
		tisw->widthMin	+= lnWidthDelta;
		tisw->heightMin	+= lnHeightDelta;

		// Store this window to the queue
		low = (_iswSOssWindowLL*)oss_SEChain_append(&gseRootWindows, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(_iswSOssWindowLL), _COMMON_START_END_BLOCK_SIZE, NULL);
		if (low)
		{
			// We're good, copy everything to our permanent area
			memcpy(&low->isw, tisw, sizeof(SOssWindow));

		} else {
			// Indicate failure
			tisw->osHandle = NULL;
		}

		// Update the remote data if any
		if (tow)
			*tow = low;

		// Create the physical window
		luCaption	= oss_asciiToUnicode((u8*)low->isw.caption, low->isw.captionLength + 1);
		low->isw.osHandle = (u64)CreateWindowW(	guVvmOssVisibleClass,
												luCaption,
												lnWindowStyle,
												tisw->osX, tisw->osY,
												tisw->osWidth, tisw->osHeight,
												NULL, NULL, ghInstance, NULL);

		// Are we good?
		if (low->isw.osHandle)
		{
			// Create the window's DC, logical bitmap and related bit buffer
			SendMessage((HWND)low->isw.osHandle, VVMOSS_CREATE_WINDOW_BITMAP, 0, 0);

			// Set the text to its unicode state
			SetWindowTextW((HWND)low->isw.osHandle, luCaption);

			// Make the window visible if it's supposed to be
			if (tisw->visible)
			{
				ShowWindow((HWND)low->isw.osHandle, SW_SHOW);			// Make the window visible
				InvalidateRect((HWND)low->isw.osHandle, NULL, false);	// Force the redraw
			}

		} else {
			// For debugging, get the error if there was cause for one
			lnError = GetLastError();
		}

		// Lower the hover fired flag as the window is new and doesn't need an initial
		// callback until there is some user interaction.
		low->isw.osHoverCallbackFired	= true;

		// If need be, call the window created callback
		if (low->isw.callback.window._callback_created)
		{
			// Yes, it's needed
			// Create a copy of our isw in case the callee is a lunatic
			memcpy(&lisw, &low->isw, sizeof(SOssWindow));
			ioss_lockSemaphore(low->isw.callback.window.semaphore_created);
			low->isw.callback.window.callback_created(low->isw.uniqueId, &lisw);
			ioss_unlockSemaphore(low->isw.callback.window.semaphore_created);
		}

		// Indicate through events this window has focus
		ioss_signalWindowFocus(low->isw.osHandle);

		// Free our unicode caption
		free(luCaption);

		// When we get here, we are to free the passed parameter as it's now been copied locally
		free(tisw);
	}




//////////
//
// Called to signald that the indicated osHandle window is now to receive focus
//
//////
	void ioss_signalWindowFocus(u64 tnOsHandle)
	{
		SOssWindow			lisw;
		_iswSFocusCallback	lfc;
		SStartEndCallback	cb;


		lfc.forFocus	= NULL;
		lfc.osHandle	= tnOsHandle;
		cb._func		= (u64)iioss_signalWindowFocusCallbacksCallback;
		cb.extra		= (u64)&lfc;
		oss_SEChain_searchByCallback(&gseRootWindows, &cb);

		// Signal the new window that it has focus (if it was found, and doesn't already have focus)
		if (lfc.forFocus && !lfc.forFocus->isw.hasFocus)
		{
			// Indicate it has focus
			lfc.forFocus->isw.hasFocus = true;

			if (lfc.forFocus->isw.callback.window._callback_gotFocus)
			{
				// Create a copy in case the user is a lunatic! :-)
				memcpy(&lisw, &lfc.forFocus->isw, sizeof(SOssWindow));

				// Signal
				ioss_lockSemaphore(lfc.forFocus->isw.callback.window.semaphore_gotFocus);
				lfc.forFocus->isw.callback.window.callback_gotFocus(lfc.forFocus->isw.uniqueId, &lisw);
				ioss_unlockSemaphore(lfc.forFocus->isw.callback.window.semaphore_gotFocus);
			}
		}
	}




//////////
//
// Locks the specified semaphore if it is non-zero, ignores it otherwise
//
//////
	void ioss_lockSemaphore(u64 semaphore)
	{
		if (semaphore)
			EnterCriticalSection((LPCRITICAL_SECTION)semaphore);
	}




//////////
//
// Unlocks the specified semaphore if it is non-zero, ignores it otherwise
//
//////
	void ioss_unlockSemaphore(u64 semaphore)
	{
		if (semaphore)
			LeaveCriticalSection((LPCRITICAL_SECTION)semaphore);
	}




//////////
//
// Delete the indicated window from the start/end chain
//
//////
	void ioss_deleteVisibleWindow(_iswSOssWindowLL* w)
	{
		if (w)
		{
			// Release our allocated objects from the window
			if (w->isw.caption)		free(w->isw.caption);
			if (w->isw.osDC)		DeleteDC((HDC)w->isw.osDC);
			if (w->isw.osBitmap)	DeleteObject((HGDIOBJ)w->isw.osBitmap);
//			if (w->isw.osBitData)	free(w->isw.osBitData);	// Handled automatically by the DeleteObject() which is linked to the bitmap data

			// Delete the window from our known chain
			oss_SEChain_deleteFrom(&gseRootWindows, (SLL*)w, true);
		}
	}




//////////
//
// The message window callback from Windows, to parse all received messages
//
//////
#define _SECOND 10000000
	LRESULT CALLTYPE ioss_wndProc_Message(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
	{
		u64 lnValue64;


		// See what the message is
		switch (msg)
		{
			case WM_CREATE:
				// Introduce timers if not already setup
				// 10ms timer is non-critical, use Windows' standard timer
				if (!ghTimer10ms)
					ghTimer10ms	= SetTimer(hwnd, 0, 10, (TIMERPROC)&iioss_timerProc_10ms);		// ~10ms resolution

				// 1ms timer is critical, use waitable timer
				if (!ghTimer1ms)
					CreateThread(0, 0, &iioss_1MsTimerThread, 0, 0, 0);
				break;

			case VVMOSS_REQUEST_MAGIC_NUMBER:
				return VVMOSS_MAGIC_NUMBER;
				break;

			case VVMOSS_REQUEST_UNIQUE_ID:
				// Grab the next value, store at *w if indicated
				lnValue64 = ioss_getNextUniqueId();

				// Store the full value if specified
				if (wp)
					*(u64*)wp = lnValue64;

				// Return the lower 32-bits
				return (u32)(lnValue64 & 0xffffffff);
				break;

			case VVMOSS_LOAD_DEBUGGER_DLL:
				return (LRESULT)ioss_loadDebuggerDll((u32)wp);
				break;

			case VVMOSS_CREATE_VISIBLE_WINDOW:
				ioss_createVisibleWindow((SOssWindow*)wp, (_iswSOssWindowLL**)lp);
				break;

			case VVMOSS_REQUEST_UNIQUE_DEBUGGER_BACKGROUND_COLOR:
// TODO:  needs to be requested and setup as an INI file of the vvm_08x.ini file before the debugger is loaded
				// A set of 8 unique background colors
				return gnDebuggerColorList[gnDebuggerNumber++ & 0x7];
				break;

			case VVMOSS_VISIBLE_WINDOW_CLOSED:
				ioss_signalWindowClosedCallback((_iswSOssWindowLL*)wp);
				break;

			case VVMOSS_FATAL_ERROR:
				// Known fatal errors:
				// VVMOSS_FATAL_ERROR_IN_1MS_TIMER
// TODO:  needs to address the fatal error condition here
_asm int 3;
				break;

			default:
				return DefWindowProc(hwnd, msg, wp, lp);
		}
		return 0;
	}




//////////
//
// The visible window callback from Windows, to parse all received messages
//
//////
	LRESULT CALLTYPE ioss_wndProc_Visible(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
	{
		u32		lnX, lnY, lnButtons, lnKey, lnKeyFlags;
		s8		lcChar;
		s16		luUnicode;


		// See what they're on about
		switch (msg)
		{
			case VVMOSS_CREATE_WINDOW_BITMAP:
			// Create the specified bitmap
				ioss_createBitmap(hwnd);
				break;

			case WM_GETMINMAXINFO:
			// Based on the original settings and the resizable settings, let the window grow or not
				ioss_checkWindowResize(hwnd, (MINMAXINFO*)lp);
				return DefWindowProc(hwnd, msg, wp, lp);
				break;

		//////////
		// Window movement / resize events
		//////
			//
			case WM_MOVE:
			// The window has moved, signal the callback
				ioss_signalMove(hwnd,
							/*x*/(u32)(lp & 0xffff),
							/*y*/(u32)(lp >> 16));
				break;

			case WM_SIZE:
			// The window has moved, signal the callback
				ioss_recreateBitmap(hwnd,
								/*width */(u32)(lp & 0xffff),
								/*height*/(u32)(lp >> 16));
				break;
				//
		//////////
		// END
		//////


		//////////
		// Window focus events
		//////
			//
			case WM_SETFOCUS:
				ioss_signalWindowFocus((u64)hwnd);
				break;
				//
		//////////
		// END
		//////


		//////////
		// Keyboard events
		//////
			//
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				ioss_deriveKeyboardInformation(&lnKey, &lnKeyFlags, &lcChar, &luUnicode, wp, (_iswSwindowExtraKeyData*)&lp);
				ioss_recordKeyboardEvent(hwnd, VVMOSS_KEYBOARD_DOWN, lnKey, lnKeyFlags, (_iswSwindowExtraKeyData*)&lp, lcChar, luUnicode);
				break;
			case WM_KEYUP:
			case WM_SYSKEYUP:
				ioss_deriveKeyboardInformation(&lnKey, &lnKeyFlags, &lcChar, &luUnicode, wp, (_iswSwindowExtraKeyData*)&lp);
				ioss_recordKeyboardEvent(hwnd, VVMOSS_KEYBOARD_UP, lnKey, lnKeyFlags, (_iswSwindowExtraKeyData*)&lp, lcChar, luUnicode);
				break;
				//
		//////////
		// END
		//////


		//////////
		// Mouse events
		//////
			//
			case WM_MOUSEMOVE:
				ioss_deriveMouseInformation(&lnX, &lnY, &lnButtons, &lnKeyFlags, wp, lp);
				ioss_recordMouseEvent(hwnd, VVMOSS_MOUSE_MOVE, lnX, lnY, lnButtons, lnKeyFlags);
				break;
			case WM_RBUTTONDOWN:
				ioss_deriveMouseInformation(&lnX, &lnY, &lnButtons, &lnKeyFlags, wp, lp);
				ioss_recordMouseEvent(hwnd, VVMOSS_MOUSE_BUTTON_DOWN_RIGHT, lnX, lnY, lnButtons, lnKeyFlags);
				break;
			case WM_LBUTTONDOWN:
				ioss_deriveMouseInformation(&lnX, &lnY, &lnButtons, &lnKeyFlags, wp, lp);
				ioss_recordMouseEvent(hwnd, VVMOSS_MOUSE_BUTTON_DOWN_LEFT, lnX, lnY, lnButtons, lnKeyFlags);
				break;
			case WM_XBUTTONDOWN:
				ioss_deriveMouseInformation(&lnX, &lnY, &lnButtons, &lnKeyFlags, wp, lp);
				ioss_recordMouseEvent(hwnd, VVMOSS_MOUSE_BUTTON_DOWN, lnX, lnY, lnButtons, lnKeyFlags);
				break;
			case WM_RBUTTONUP:
				ioss_deriveMouseInformation(&lnX, &lnY, &lnButtons, &lnKeyFlags, wp, lp);
				ioss_recordMouseEvent(hwnd, VVMOSS_MOUSE_BUTTON_UP_RIGHT, lnX, lnY, lnButtons, lnKeyFlags);
				break;
			case WM_LBUTTONUP:
				ioss_deriveMouseInformation(&lnX, &lnY, &lnButtons, &lnKeyFlags, wp, lp);
				ioss_recordMouseEvent(hwnd, VVMOSS_MOUSE_BUTTON_UP_LEFT, lnX, lnY, lnButtons, lnKeyFlags);
			case WM_XBUTTONUP:
				ioss_deriveMouseInformation(&lnX, &lnY, &lnButtons, &lnKeyFlags, wp, lp);
				ioss_recordMouseEvent(hwnd, VVMOSS_MOUSE_BUTTON_UP, lnX, lnY, lnButtons, lnKeyFlags);
				break;
				//
		//////////
		// END
		//////


			case WM_PAINT:
				if (!ioss_paintWindow(hwnd))
					return DefWindowProc(hwnd, msg, wp, lp);
				break;


			case WM_CLOSE:
				// If need be, call the window created callback
				ioss_signalWindowUnloadCallback(hwnd);
				return DefWindowProc(hwnd, msg, wp, lp);
				break;

			case WM_DESTROY:
				// Note:  We won't handle this now, but in the future we may want to capture this event for the close rather than WM_CLOSE. However, with protocol ... we should be okay.
			default:
				return DefWindowProc(hwnd, msg, wp, lp);
		}
		return 0;
	}




//////////
//
// Creates the bitmap associated with the window's device context.  This is separate and
// independent of any canvases that are used to draw onto this bitmap.  This bitmap is at
// the OSS level.  Canvases should be used to draw items, then the canvas rendered.
//
//////
	void ioss_createBitmap(HWND hwnd)
	{
		u32				lnActualWidth;
		_iswSOssWindowLL*		w;
		BITMAPINFO		lbi;


		// Iterate through known windows to find our man
		w = ioss_findSOssWindowLLByHwnd(hwnd);
		if (w)
		{
			// Remove the old bitmap (it should not be here, by the way ... nyuck, nyuck :-) )
			if (w->isw.osBitmap)
				DeleteObject((HGDIOBJ)w->isw.osBitmap);		// Delete the old bitmap

			// Create the device context and bitmap
			w->isw.osDC			= (u64)((u32)CreateCompatibleDC(GetDC(GetDesktopWindow())));
			w->isw.osBitmap		= ioss_createDibWithBitBuffer((HDC)w->isw.osDC, w->isw.width, w->isw.height, &lbi, (s8**)&w->isw.osBitData, &lnActualWidth);
			if (w->isw.osDC && w->isw.osBitData)
				SelectObject((HDC)w->isw.osDC, (HGDIOBJ)w->isw.osBitmap);

			// Initialize the background color
			ioss_initializeBackground(w->isw.width, w->isw.height, w->isw.backColor.color, (s8*)w->isw.osBitData, lnActualWidth);
		}
	}




//////////
//
// Create the bitmap buffer as indicated, and return the HBITMAP handle as well as a pointer
// to the bitmap bits / data.
//
//////
	u64 ioss_createDibWithBitBuffer(HDC thDC, u32 tnWidth, u32 tnHeight, BITMAPINFO* tbi, s8** tbd, u32* tnActualWidth)
	{
		// Create a new DIB
		memset(tbi, 0, sizeof(BITMAPINFO));
		tbi->bmiHeader.biSize		= sizeof(tbi->bmiHeader);
		tbi->bmiHeader.biWidth		= tnWidth;
		tbi->bmiHeader.biHeight		= tnHeight;
		tbi->bmiHeader.biPlanes		= 1;
		tbi->bmiHeader.biBitCount	= 24;

		// Store the actual width if the user is requesting it
		if (tnActualWidth)
		{
			*tnActualWidth				= ioss_computeActualWidth(tnWidth);
			tbi->bmiHeader.biSizeImage	= *tnActualWidth * tnHeight;
		}

		// Physically create the bitmap
		return((u64)CreateDIBSection(thDC, tbi, DIB_RGB_COLORS, (void**)tbd, NULL, 0));
	}




//////////
//
// Initialize the background to its specified back color.
//
//////
	void ioss_initializeBackground(u32 tnWidth, u32 tnHeight, u32 tnBackColor, s8* tbd, u32 tnActualWidth)
	{
		u8		lnRed, lnGrn, lnBlu;
		u32		lnX, lnY;
		SRGB*	lrgb;


		// If we created the data, initialize the bits to the default backColor
		if (tbd)
		{
			// Grab our back colors
			lnRed	= red(tnBackColor);
			lnGrn	= grn(tnBackColor);
			lnBlu	= blu(tnBackColor);

			// Put it everywhere
			for (lnY = 0; lnY < tnHeight; lnY++)
			{
				lrgb = (SRGB*)(tbd + ((tnHeight - lnY - 1) * tnActualWidth));
				for (lnX = 0; lnX < tnWidth; lnX++)
				{
					// Populate this pixel
					lrgb->red	= lnRed;
					lrgb->grn	= lnGrn;
					lrgb->blu	= lnBlu;

					// Move to next pixel
					++lrgb;
				}
			}
		}
	}




//////////
//
// Computes the actual width for each bitmap line. In Windows, for general graphics adapter
// support, used bitmaps are 24-bits and are rounded up to the nearest DWORD for each row.
// With 3 bytes per pixel (one each for red, green, and blue), the formula takes this into
// account by multiplying by three first, then rounding up.
//
//////
	u32 ioss_computeActualWidth(u32 tnWidth)
	{
		u32 lnWidth;


		// Account for 3 bytes per pixel (RGB values)
		lnWidth = tnWidth * 3;

		// Adjust to nearest dword (32-bit quantity)
		if (lnWidth % 4)
			lnWidth += 4 - (lnWidth % 4);

		// All done!
		return(lnWidth);
	}




//////////
//
// Paints the window's bit buffer when demanded by the OSS.
//
//////
	bool ioss_paintWindow(HWND hwnd)
	{
		_iswSOssWindowLL*		w;
		PAINTSTRUCT		ps;


		// Iterate through known windows to find our man
		w = ioss_findSOssWindowLLByHwnd(hwnd);
		if (w)
		{
			// Paint it
			BeginPaint(hwnd, &ps);

			// BitBlt the image currently there
			BitBlt(ps.hdc, 0, 0, w->isw.width, w->isw.height, (HDC)w->isw.osDC, 0, 0, SRCCOPY);

			// All done
			EndPaint(hwnd, &ps);
			return(true);
		}
		// If we get here, not found
		return(false);
	}




//////////
//
// Called when the user tries to resize the window.  Sets programmed upper and lower
// boundaries per the given constraints.
//
//////
	void ioss_checkWindowResize(HWND hwnd, MINMAXINFO* tmmi)
	{
		_iswSOssWindowLL*	w;
		RECT			lrc;


		// Iterate through known windows to find our man
		w = ioss_findSOssWindowLLByHwnd(hwnd);
		if (w)
		{
			if (!w->isw.resizable)
			{
				// Grab the desktop window size
				GetWindowRect(GetDesktopWindow(), &lrc);

				// Must retain its original size
				tmmi->ptMaxSize.x		= w->isw.widthMax;
				tmmi->ptMaxSize.y		= w->isw.heightMax;
				tmmi->ptMaxPosition.x	= (lrc.right  - lrc.left) - w->isw.widthMax;
				tmmi->ptMaxPosition.y	= (lrc.bottom - lrc.top)  - w->isw.heightMax;

				// All done!
			}
			// We always update the minimum
			tmmi->ptMinTrackSize.x	= w->isw.widthMin;
			tmmi->ptMinTrackSize.y	= w->isw.heightMin;
			tmmi->ptMaxTrackSize.x	= w->isw.widthMax;
			tmmi->ptMaxTrackSize.y	= w->isw.heightMax;
		}
	}




//////////
//
// Searches through the list of known screens visible on the display at the present
// time by HWND, and returns a pointer to it if found.  NULL if not.
//
//////
	_iswSOssWindowLL* ioss_findSOssWindowLLByHwnd(HWND hwnd)
	{
		SStartEndCallback cb;


		cb._func	= (u64)iioss_findSOssWindowLLByHwndCallback;
		cb.extra	= (u64)hwnd;
		return((_iswSOssWindowLL*)oss_SEChain_searchByCallback(&gseRootWindows, &cb));
	}

	bool iioss_findSOssWindowLLByHwndCallback(SStartEndCallback* cb)
	{
		_iswSOssWindowLL* low;


		// Make sure our environment is sane
		if (cb && cb->ptr)
		{
			low = (_iswSOssWindowLL*)cb->ptr;
			if (low->isw.osHandle == cb->extra)
				return(true);		// It's a match
		}
		// If we get here, not found
		return(false);
	}




//////////
//
// Searches through the list of known screens visible on the display at the present
// time by screen id, and returns a pointer to it if found.  NULL if not.
//
//////
	_iswSOssWindowLL* ioss_findSOssWindowLLByScreenId(u64 tnScreenId)
	{
		SStartEndCallback cb;


		cb._func	= (u64)iioss_findSOssWindowLLByScreenId;
		cb.extra	= (u64)tnScreenId;
		return((_iswSOssWindowLL*)oss_SEChain_searchByCallback(&gseRootWindows, &cb));
	}

	bool iioss_findSOssWindowLLByScreenId(SStartEndCallback* cb)
	{
		_iswSOssWindowLL* low;


		// Make sure our environment is sane
		if (cb && cb->ptr)
		{
			low = (_iswSOssWindowLL*)cb->ptr;
			if (low->isw.screenId == cb->extra)
				return(true);		// It's a match
		}
		// If we get here, not found
		return(false);
	}




//////////
//
// Callback from findScreenByOssWindowId() to locate the indicated SOssWindowLL structure by its
// ID, and not the actual SOssWindowLL->isw->ll.uniqueId for the actual internal screen structure
//
//////
	_iswSOssWindowLL* ioss_find_iswSOssWindowLL_By_iOssWindowId(u64 tnOssWindowId)
	{
		SStartEndCallback cb;


		// Try to find it using the callback
		cb._func	= (u64)&iioss_findSOssWindowByOssWindowIdCallback;
		cb.extra	= tnOssWindowId;
		return((_iswSOssWindowLL*)oss_SEChain_searchByCallback(&gseRootWindows, &cb));
	}

	bool iioss_findSOssWindowByOssWindowIdCallback(SStartEndCallback* cb)
	{
		_iswSOssWindowLL* low;


		// Make sure the environment is sane
		if (cb && cb->ptr)
		{
			low = (_iswSOssWindowLL*)cb->ptr;
			if (low->ll.uniqueId == cb->extra)
				return(true);
		}
		// If we get here, not a match
		return(false);
	}





//////////
//
// Converts the windows encoded mouse data to something usable by VVM
//
//////
	void ioss_deriveMouseInformation(u32* tnX, u32* tnY, u32* tnButtons, u32* tnKeys, u32 tnWinKeys, u32 tnXlowYhigh)
	{
		// Initialize the keys and buttons to empty
		*tnKeys		= 0;
		*tnButtons	= 0;

		// Apply the keys which are enabled
		if (tnWinKeys & MK_CONTROL)		*tnKeys		|= VVMOSS_KEYBOARD_CONTROL;
		if (tnWinKeys & MK_SHIFT)		*tnKeys		|= VVMOSS_KEYBOARD_SHIFT;

		// See which button(s) is(are) depressed
		if (tnWinKeys & MK_LBUTTON)		*tnButtons	|= VVMOSS_MOUSE_LEFT;
		if (tnWinKeys & MK_MBUTTON)		*tnButtons	|= VVMOSS_MOUSE_MIDDLE;
		if (tnWinKeys & MK_RBUTTON)		*tnButtons	|= VVMOSS_MOUSE_RIGHT;
		if (tnWinKeys & MK_XBUTTON1)	*tnButtons	|= VVMOSS_MOUSE_EXTRA1;
		if (tnWinKeys & MK_XBUTTON2)	*tnButtons	|= VVMOSS_MOUSE_EXTRA2;

		// Obtain the X and Y coordinates
		*tnX = tnXlowYhigh & 0xffff;		// Lower 16-bits
		*tnY = tnXlowYhigh >> 16;			// Upper 16-bits
	}




//////////
//
// Records the indicated mouse event for the specified window
//
//////
	void ioss_recordMouseEvent(HWND hwnd, u32 tnEVent, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
	{
		_iswSOssWindowLL*	w;
		SOssWindow			lisw;
		SOssMouseEvent*		lisme;


		// Iterate through known windows to find our man
		w = ioss_findSOssWindowLLByHwnd(hwnd);
		if (w)
		{
// TODO:  In all places where the lisw structure is referenced, we need to blank out or create a duplicate of the structure at the start of every call
//        This way the user can mess with the structure, and nothing will be affected
			// See what event we're processing
			switch (tnEVent)
			{
				case VVMOSS_MOUSE_MOVE:
					// Do the callback
					if (w->isw.osIsDragging)
					{
						// Dragging something, signal that callback if necessary
						if (w->isw.callback.drag._callback_dragging)
						{
							ioss_lockSemaphore(w->isw.callback.drag.semaphore_dragging);
							memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
							w->isw.callback.drag.callback_dragging(w->isw.uniqueId, &lisw, tnX, tnY, tnButtons, tnKeys, w->isw.timer - w->isw.osDragStartTimer);
							ioss_unlockSemaphore(w->isw.callback.drag.semaphore_dragging);
						}

					} else {
						// Regular mouse move
						if (w->isw.callback.mouse._callback_move)
						{
							ioss_lockSemaphore(w->isw.callback.mouse.semaphore_move);
							memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
							w->isw.callback.mouse.callback_move(w->isw.uniqueId, &lisw, tnX, tnY, tnButtons, tnKeys);
							ioss_unlockSemaphore(w->isw.callback.mouse.semaphore_move);
						}
					}

					// Update this MouseMove entry
					lisme = &w->isw.osMouseMove;
					break;

				case VVMOSS_MOUSE_BUTTON_DOWN_LEFT:
				case VVMOSS_MOUSE_BUTTON_DOWN_RIGHT:
				case VVMOSS_MOUSE_BUTTON_DOWN:
					// Do the callback for the down buttons
					if (w->isw.callback.mouse._callback_down)
					{
						ioss_lockSemaphore(w->isw.callback.mouse.semaphore_down);
						memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
						w->isw.callback.mouse.callback_down(w->isw.uniqueId, &lisw, tnX, tnY, tnButtons, tnKeys);
						ioss_unlockSemaphore(w->isw.callback.mouse.semaphore_down);
					}

					// Note:  The determination for dragging is triggered on the timer event.
					//        Several criteria have to happen before a drag is considered to have begun.

					// Update this MouseMove entry
					lisme = &w->isw.osMouseDown;
					break;

				case VVMOSS_MOUSE_BUTTON_UP_RIGHT:
				case VVMOSS_MOUSE_BUTTON_UP_LEFT:
				case VVMOSS_MOUSE_BUTTON_UP:
					// Do the callback for the up buttons
					if (!w->isw.osIsDragging)
					{
						// Regular mouse release
						if (w->isw.callback.mouse._callback_up)
						{
							ioss_lockSemaphore(w->isw.callback.mouse.semaphore_up);
							memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
							w->isw.callback.mouse.callback_up(w->isw.uniqueId, &lisw, tnX, tnY, tnButtons, tnKeys);
							ioss_unlockSemaphore(w->isw.callback.mouse.semaphore_up);
						}
					}

					// Update this MouseMove entry
					lisme = &w->isw.osMouseUp;
					break;

				default:
					// Something's awry, captain!
					return;
			}
			// Update the mouse event for this operation
			lisme->timer	= w->isw.timer;
			lisme->x		= tnX;
			lisme->y		= tnY;
			lisme->buttons	= tnButtons;
			lisme->keys		= tnKeys;

			// See if any mouse buttons are still down
			if (tnButtons & VVMOSS_MOUSE_DOWN_MASK)
			{
				// A button is down
				if (!w->isw.osIsMouseButtonDown)
				{
					// We're just starting a new down-going mouse button operation.
					// Note:  Can trigger a mouseButtonDepressed event here if need be
					// Raise the down flag and reset the counter
					w->isw.osIsMouseButtonDown				= true;
					w->isw.osMouseDownAccumulationCounter	= 0;

					// Record the location of the first down button
					memcpy(&w->isw.osMouseDownFirst, lisme, sizeof(w->isw.osMouseDownFirst));
				}

			} else {
				// No buttons are presently down
				if (w->isw.osIsMouseButtonDown)
				{
					// We're just starting a new non-down-going mouse button operation
					// Note:  Can trigger a mouseButtonReleased event here if need be
					// Raise the down flag and reset the counter
					w->isw.osIsMouseButtonDown				= false;
					w->isw.osMouseDownAccumulationCounter	= 0;
				}
			}

			// See if we're done dragging
			if (w->isw.osIsDragging && !w->isw.osIsMouseButtonDown && w->isw.callback.drag._callback_drop)
			{
				// They're dropped the item
				// Note:  This is signaled here because the user can drag with any button, and insert and
				//        remove other buttons while dragging, for some potentially awesome abilities.
				w->isw.osIsDragging = false;
				ioss_lockSemaphore(w->isw.callback.drag.semaphore_drop);
				memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
				w->isw.callback.drag.callback_drop(w->isw.uniqueId, &lisw, w->isw.osMouseMove.x, w->isw.osMouseMove.y, w->isw.osMouseMove.buttons, w->isw.osMouseMove.keys, w->isw.timer - w->isw.osDragStartTimer);
				ioss_unlockSemaphore(w->isw.callback.drag.semaphore_drop);
			}

			// If need be, cancel the hover callback, and lower the hover flag
			if (w->isw.osHoverCallbackFired && w->isw.callback.mouse._callback_hover)
			{
				// Yes, it's needed
				// Cancel the hover operation
				ioss_lockSemaphore(w->isw.callback.mouse.semaphore_hover);
				memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
				w->isw.callback.mouse.callback_hover(w->isw.uniqueId, &lisw, w->isw.osMouseMove.x, w->isw.osMouseMove.y, w->isw.osMouseMove.buttons, w->isw.osMouseMove.keys, w->isw.timer - w->isw.osMouseMove.timer, true);
				ioss_unlockSemaphore(w->isw.callback.mouse.semaphore_hover);
				w->isw.osHoverCallbackFired = false;
			}
		}
	}




//////////
//
// Converts the windows encoded keystroke data to something usable by VVM
//
//////
	void ioss_deriveKeyboardInformation(u32* tnKey, u32* tnKeyFlags, s8* tcChar, s16* tuUnicode, u32 tnVkey, _iswSwindowExtraKeyData* tsXKeyInfo)
	{
		u32			lnKeyFlags;
		s8			bufferAscii[2];
		wchar_t		bufferUnicode[2];


		// Initialize the keys and buttons to empty
		*tcChar		= 0;
		*tuUnicode	= 0;


		// We explicitly poll the key states because on certain virtual machines
		// or remote desktop software viewers can change the states while not signaling
		// locally. However, when polled the current state will be updated properly.
		lnKeyFlags = 0;
		lnKeyFlags |= (GetKeyState(VK_LMENU)		& 1 << 15)		?	VVMOSS_KEYBOARD_LEFT_ALT		: 0;
		lnKeyFlags |= (GetKeyState(VK_RMENU)		& 1 << 15)		?	VVMOSS_KEYBOARD_LEFT_ALT		: 0;
		lnKeyFlags |= (GetKeyState(VK_LCONTROL)		& 1 << 15)		?	VVMOSS_KEYBOARD_LEFT_CONTROL	: 0;
		lnKeyFlags |= (GetKeyState(VK_RCONTROL)		& 1 << 15)		?	VVMOSS_KEYBOARD_LEFT_CONTROL	: 0;
		lnKeyFlags |= (GetKeyState(VK_LSHIFT)		& 1 << 15)		?	VVMOSS_KEYBOARD_LEFT_SHIFT		: 0;
		lnKeyFlags |= (GetKeyState(VK_RSHIFT)		& 1 << 15)		?	VVMOSS_KEYBOARD_LEFT_SHIFT		: 0;

		// If left- or right-keys are down, signal the general "down" condition as well
		lnKeyFlags |= (lnKeyFlags & (VVMOSS_KEYBOARD_LEFT_ALT		| VVMOSS_KEYBOARD_RIGHT_ALT))		?	VVMOSS_KEYBOARD_ALT			: 0;
		lnKeyFlags |= (lnKeyFlags & (VVMOSS_KEYBOARD_LEFT_CONTROL	| VVMOSS_KEYBOARD_RIGHT_CONTROL))	?	VVMOSS_KEYBOARD_CONTROL		: 0;
		lnKeyFlags |= (lnKeyFlags & (VVMOSS_KEYBOARD_LEFT_SHIFT		| VVMOSS_KEYBOARD_RIGHT_SHIFT))		?	VVMOSS_KEYBOARD_SHIFT		: 0;

		// Explicitly poll the state of caps lock, num lock and scroll lock for the same reasons
		lnKeyFlags |= (GetKeyState(VK_SCROLL))		?	VVMOSS_KEYBOARD_SCROLL_LOCK_ON		: 0;
		lnKeyFlags |= (GetKeyState(VK_NUMLOCK))		?	VVMOSS_KEYBOARD_NUM_LOCK_ON			: 0;
		lnKeyFlags |= (GetKeyState(VK_CAPITAL))		?	VVMOSS_KEYBOARD_CAPS_LOCK_ON		: 0;

		// Store the flags
		*tnKeyFlags = lnKeyFlags;

		// Set the key
		*tcChar = (u8)tnVkey;
		// We will accurately set lower-case if need be
		if (*tcChar >= 'A' && *tcChar <= 'Z')
		{
			// Potentially apply the appropriate shift+caps condition to lower-case the letter appropriately
			if ((lnKeyFlags & VVMOSS_KEYBOARD_CAPS_LOCK_ON))
			{
				// Shift keys have opposite effect
				if ((lnKeyFlags & VVMOSS_KEYBOARD_SHIFT))
				{
					// CAPS lock is on, and shift key is pressed.
					// Should be made lower-case
					*tcChar = *tcChar | 0x20;
				}

			} else {
				// Shift keys have capitalizing effect
				if (!(lnKeyFlags & VVMOSS_KEYBOARD_SHIFT))
				{
					// CAPS lock is NOT on, and shift key is NOT pressed.
					// Should be made lower-case
					*tcChar = *tcChar | 0x20;
				}
			}
		}

		// Obtain the unicode equivalent (with lower-case applied appropriately)
		bufferAscii[0]	= *tcChar;
		bufferAscii[1]	= 0;
		MultiByteToWideChar(CP_ACP, 0, bufferAscii, 1, bufferUnicode, sizeof(bufferUnicode) / sizeof(s16));
		*tuUnicode		= *(u16*)&bufferUnicode[0];
		// Note:  The reversing function:
		//        WideCharToMultiByte(CP_ACP, 0, bufferUnicode, 1, bufferAscii, sizeof(bufferAscii) / sizeof(s8), NULL, NULL);

		// Translate the windows-specific key to a VVM key
		ioss_translateWindowsToVvmKey(tnKey, tnVkey);
	}




//////////
//
// Records the indicated keyboard event for the specified window
//
//////
	void ioss_recordKeyboardEvent(HWND hwnd, u32 tnEVent, u32 tnKey, u32 tnKeyFlags, _iswSwindowExtraKeyData* tsXKeyInfo, s8 tcChar, s16 tuUnicode)
	{
		_iswSOssWindowLL*		w;
		SOssWindow		lisw;
		SOssKbdEvent*	liske;


		// Iterate through known windows to find our man
		w = ioss_findSOssWindowLLByHwnd(hwnd);
		if (w)
		{
			// Make a copy of the record in case the user goes nutty coo-coo! :-)
			memcpy(&lisw, &w->isw, sizeof(SOssWindow));


			// If shift/control/alt/caps/num/scroll have changed
			if (w->isw.osKeyDownLast.keyFlags != tnKeyFlags && w->isw.callback.keyboard._callback_flags)
			{
				// Keys have changed, signal the change
				ioss_lockSemaphore(w->isw.callback.keyboard.semaphore_flags);
				w->isw.callback.keyboard.callback_flags(w->isw.uniqueId, &lisw, w->isw.osKeyDownLast.keyFlags, tnKeyFlags);
				ioss_unlockSemaphore(w->isw.callback.keyboard.semaphore_flags);
			}


			// See what event we're processing
			switch (tnEVent)
			{
				case VVMOSS_KEYBOARD_DOWN:
					if (tsXKeyInfo->repeatCount == 1 && w->isw.callback.keyboard._callback_down)
					{
						// We fire the key down event only on the first press
						ioss_lockSemaphore(w->isw.callback.keyboard.semaphore_down);
						w->isw.callback.keyboard.callback_down(w->isw.uniqueId, &lisw, tnKey, tnKeyFlags, tcChar, tuUnicode);
						ioss_unlockSemaphore(w->isw.callback.keyboard.semaphore_down);
					}
					if (w->isw.callback.keyboard._callback_press)
					{
						// We fire every key repeated character under KeyPress
						ioss_lockSemaphore(w->isw.callback.keyboard.semaphore_press);
						w->isw.callback.keyboard.callback_press(w->isw.uniqueId, &lisw, tnKey, tnKeyFlags, tcChar, tuUnicode);
						ioss_unlockSemaphore(w->isw.callback.keyboard.semaphore_press);
					}

					// Update the key down
					liske = &w->isw.osKeyDown;
					break;

				case VVMOSS_KEYBOARD_UP:
					if (w->isw.callback.keyboard._callback_up)
					{
						// We fire the key down event only on the first press
						ioss_lockSemaphore(w->isw.callback.keyboard.semaphore_up);
						w->isw.callback.keyboard.callback_up(w->isw.uniqueId, &lisw, tnKey, tnKeyFlags, tcChar, tuUnicode);
						ioss_unlockSemaphore(w->isw.callback.keyboard.semaphore_up);
					}

					// Update the key down
					liske = &w->isw.osKeyUp;
					break;
			}
		}
	}




//////////
//
// Called to signal the move to the callback if defined
//
//////
	void ioss_signalMove(HWND hwnd, u32 tnX, u32 tnY)
	{
		_iswSOssWindowLL*		w;
		SOssWindow		lisw;


		// Iterate through known windows to find our man
		w = ioss_findSOssWindowLLByHwnd(hwnd);
		if (w)
		{
			// Create a copy in case the user is a lunatic! :-)
			memcpy(&lisw, &w->isw, sizeof(SOssWindow));

			// Signal the move if we are supposed to
			if (w->isw.callback.window._callback_moved)
			{
				ioss_lockSemaphore(w->isw.callback.window.semaphore_moved);
				w->isw.callback.window.callback_moved(w->isw.uniqueId, &lisw, tnX, tnY);
				ioss_unlockSemaphore(w->isw.callback.window.semaphore_moved);
			}

			// Position the window logically to match where it is
			w->isw.osX	= tnX;
			w->isw.osY	= tnY;
		}
	}




//////////
//
// Called to recreate the bitmap after it was resized, and to signal the resize
//
//////
	void ioss_recreateBitmap(HWND hwnd, u32 tnWidth, u32 tnHeight)
	{
		u32				lnActualWidth;
		u64				lnNewDC, lnNewBitmap;
		RECT			lrc;
		BITMAPINFO		lbi;
		s8*				lbd;
		_iswSOssWindowLL*		w;
		SOssWindow		lisw;


		// Iterate through known windows to find our man
		w = ioss_findSOssWindowLLByHwnd(hwnd);
		if (w && (w->isw.width != tnWidth || w->isw.height != tnHeight))
		{
			// Signal the resize (if we are supposed to)
			if (w->isw.callback.window._callback_resized)
			{
				// Callback
				ioss_lockSemaphore(w->isw.callback.window.semaphore_resized);
				memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
				w->isw.callback.window.callback_resized(w->isw.uniqueId, &lisw, tnWidth, tnHeight);
				ioss_unlockSemaphore(w->isw.callback.window.semaphore_resized);
			}

			// Create our new DC and bitmap
			lnNewDC		= (u64)CreateCompatibleDC((HDC)w->isw.osDC);
			lnNewBitmap	= ioss_createDibWithBitBuffer((HDC)lnNewDC, tnWidth, tnHeight, &lbi, &lbd, &lnActualWidth);
			if (lnNewDC && lnNewBitmap)
				SelectObject((HDC)lnNewDC, (HGDIOBJ)lnNewBitmap);

			// Initialize our new background to the default back color
			ioss_initializeBackground(tnWidth, tnHeight, w->isw.backColor.color, lbd, lnActualWidth);

			// Use Windows' native BitBlt algorithm to copy
			BitBlt(	(HDC)lnNewDC,		0, 0, min(tnWidth, w->isw.width), min(tnHeight, w->isw.height),
					(HDC)w->isw.osDC,	0, 0, SRCCOPY);

			// Delete the old bitmap
			DeleteObject((HGDIOBJ)w->isw.osBitmap);		// Auto-deletes w->isw.osBitData
			DeleteDC((HDC)w->isw.osDC);

			// Make the new ones active
			w->isw.osBitmap		= lnNewBitmap;
			w->isw.osDC			= lnNewDC;
			w->isw.osBitData	= lbd;

			// Resize the window logically to match what it now is
			w->isw.width		= tnWidth;
			w->isw.height		= tnHeight;

			// Find out how big the OS size for this window is
			GetWindowRect(hwnd, &lrc);
			w->isw.osWidth		= lrc.right  - lrc.left;
			w->isw.osHeight		= lrc.bottom - lrc.top;
		}
	}




//////////
//
// Determines the window style based on the flags which are set in the window
//
//////
	u32 ioss_getWindowStyle(SOssWindow* tisw)
	{
		u32 lnWindowStyle;


		// Determine the style via logic
		lnWindowStyle = (tisw->border ? 
							(tisw->resizable ? 
								WS_OVERLAPPEDWINDOW/* Both has a border and is resizable */ :
								(WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX))/* Only has a border, is not resizable */ :
							WS_POPUP/* Has no border, and is not resizable */
						);

		// All done
		return(lnWindowStyle);
	}




//////////
//
// Returns the straight-line distance between two points.
// c = sqrt(a*a + b*b)
//
//////
	f32 ioss_distanceBetween(u32 tnX1, u32 tnY1, u32 tnX2, u32 tnY2)
	{
		f32 a, b, c;


		// Set our values
		a	= (f32)max(tnX1, tnX2) - min(tnX1, tnX2);
		b	= (f32)max(tnY1, tnY2) - min(tnY1, tnY2);
		c	= sqrt(a*a + b*b);

		// Return distance
		return(c);
	}




//////////
//
// Convert the specified VK_* Windows values to VVM_* keys
//
//////
	void ioss_translateWindowsToVvmKey(u32* tnKey, u32 tnVkey)
	{
		switch (tnVkey)
		{
			case VK_LBUTTON:                              // 0x01  Left mouse button
				*tnKey = VVM_LBUTTON;
				break;
			case VK_RBUTTON:                              // 0x02  Right mouse button
				*tnKey = VVM_RBUTTON;
				break;
			case VK_CANCEL:                               // 0x03  Control-break processing
				*tnKey = VVM_CANCEL;
				break;
			case VK_MBUTTON:                              // 0x04  Middle mouse button (three-button mouse)
				*tnKey = VVM_MBUTTON;
				break;
			case VK_XBUTTON1:                             // 0x05  X1 mouse button
				*tnKey = VVM_XBUTTON1;
				break;
			case VK_XBUTTON2:                             // 0x06  X2 mouse button
				*tnKey = VVM_XBUTTON2;
				break;
			case VK_BACK:                                 // 0x08  BACKSPACE key
				*tnKey = VVM_BACK;
				break;
			case VK_TAB:                                  // 0x09  TAB key
				*tnKey = VVM_TAB;
				break;
			case VK_CLEAR:                                // 0x0C  CLEAR key
				*tnKey = VVM_CLEAR;
				break;
			case VK_RETURN:                               // 0x0D  ENTER key
				*tnKey = VVM_RETURN;
				break;
			case VK_SHIFT:                                // 0x10  SHIFT key
				*tnKey = VVM_SHIFT;
				break;
			case VK_CONTROL:                              // 0x11  CTRL key
				*tnKey = VVM_CONTROL;
				break;
			case VK_MENU:                                 // 0x12  ALT key
				*tnKey = VVM_MENU;
				break;
			case VK_PAUSE:                                // 0x13  PAUSE key
				*tnKey = VVM_PAUSE;
				break;
			case VK_CAPITAL:                              // 0x14  CAPS LOCK key
				*tnKey = VVM_CAPITAL;
				break;
			case VK_KANA:                                 // 0x15  IME Kana mode
				*tnKey = VVM_KANA;
				break;
			case VK_JUNJA:                                // 0x17  IME Junja mode
				*tnKey = VVM_JUNJA;
				break;
			case VK_FINAL:                                // 0x18  IME final mode
				*tnKey = VVM_FINAL;
				break;
			case VK_HANJA:                                // 0x19  IME Hanja mode
				*tnKey = VVM_HANJA;
				break;
			case VK_ESCAPE:                               // 0x1B  ESC key
				*tnKey = VVM_ESCAPE;
				break;
			case VK_CONVERT:                              // 0x1C  IME convert
				*tnKey = VVM_CONVERT;
				break;
			case VK_NONCONVERT:                           // 0x1D  IME nonconvert
				*tnKey = VVM_NONCONVERT;
				break;
			case VK_ACCEPT:                               // 0x1E  IME accept
				*tnKey = VVM_ACCEPT;
				break;
			case VK_MODECHANGE:                           // 0x1F  IME mode change request
				*tnKey = VVM_MODECHANGE;
				break;
			case VK_SPACE:                                // 0x20  SPACEBAR
				*tnKey = VVM_SPACE;
				break;
			case VK_PRIOR:                                // 0x21  PAGE UP key
				*tnKey = VVM_PRIOR;
				break;
			case VK_NEXT:                                 // 0x22  PAGE DOWN key
				*tnKey = VVM_NEXT;
				break;
			case VK_END:                                  // 0x23  END key
				*tnKey = VVM_END;
				break;
			case VK_HOME:                                 // 0x24  HOME key
				*tnKey = VVM_HOME;
				break;
			case VK_LEFT:                                 // 0x25  LEFT ARROW key
				*tnKey = VVM_LEFT;
				break;
			case VK_UP:                                   // 0x26  UP ARROW key
				*tnKey = VVM_UP;
				break;
			case VK_RIGHT:                                // 0x27  RIGHT ARROW key
				*tnKey = VVM_RIGHT;
				break;
			case VK_DOWN:                                 // 0x28  DOWN ARROW key
				*tnKey = VVM_DOWN;
				break;
			case VK_SELECT:                               // 0x29  SELECT key
				*tnKey = VVM_SELECT;
				break;
			case VK_PRINT:                                // 0x2A  PRINT key
				*tnKey = VVM_PRINT;
				break;
			case VK_EXECUTE:                              // 0x2B  EXECUTE key
				*tnKey = VVM_EXECUTE;
				break;
			case VK_SNAPSHOT:                             // 0x2C  PRINT SCREEN key
				*tnKey = VVM_SNAPSHOT;
				break;
			case VK_INSERT:                               // 0x2D  INS key
				*tnKey = VVM_INSERT;
				break;
			case VK_DELETE:                               // 0x2E  DEL key
				*tnKey = VVM_DELETE;
				break;
			case VK_HELP:                                 // 0x2F  HELP key
				*tnKey = VVM_HELP;
				break;
			case 0x30:                                    // 0x30  0 key
				*tnKey = VVM_0;
				break;
			case 0x31:                                    // 0x31  1 key
				*tnKey = VVM_1;
				break;
			case 0x32:                                    // 0x32  2 key
				*tnKey = VVM_2;
				break;
			case 0x33:                                    // 0x33  3 key
				*tnKey = VVM_3;
				break;
			case 0x34:                                    // 0x34  4 key
				*tnKey = VVM_4;
				break;
			case 0x35:                                    // 0x35  5 key
				*tnKey = VVM_5;
				break;
			case 0x36:                                    // 0x36  6 key
				*tnKey = VVM_6;
				break;
			case 0x37:                                    // 0x37  7 key
				*tnKey = VVM_7;
				break;
			case 0x38:                                    // 0x38  8 key
				*tnKey = VVM_8;
				break;
			case 0x39:                                    // 0x39  9 key
				*tnKey = VVM_9;
				break;
			case 0x41:                                    // 0x41  A key
				*tnKey = VVM_A;
				break;
			case 0x42:                                    // 0x42  B key
				*tnKey = VVM_B;
				break;
			case 0x43:                                    // 0x43  C key
				*tnKey = VVM_C;
				break;
			case 0x44:                                    // 0x44  D key
				*tnKey = VVM_D;
				break;
			case 0x45:                                    // 0x45  E key
				*tnKey = VVM_E;
				break;
			case 0x46:                                    // 0x46  F key
				*tnKey = VVM_F;
				break;
			case 0x47:                                    // 0x47  G key
				*tnKey = VVM_G;
				break;
			case 0x48:                                    // 0x48  H key
				*tnKey = VVM_H;
				break;
			case 0x49:                                    // 0x49  I key
				*tnKey = VVM_I;
				break;
			case 0x4A:                                    // 0x4A  J key
				*tnKey = VVM_J;
				break;
			case 0x4B:                                    // 0x4B  K key
				*tnKey = VVM_K;
				break;
			case 0x4C:                                    // 0x4C  L key
				*tnKey = VVM_L;
				break;
			case 0x4D:                                    // 0x4D  M key
				*tnKey = VVM_M;
				break;
			case 0x4E:                                    // 0x4E  N key
				*tnKey = VVM_N;
				break;
			case 0x4F:                                    // 0x4F  O key
				*tnKey = VVM_O;
				break;
			case 0x50:                                    // 0x50  P key
				*tnKey = VVM_P;
				break;
			case 0x51:                                    // 0x51  Q key
				*tnKey = VVM_Q;
				break;
			case 0x52:                                    // 0x52  R key
				*tnKey = VVM_R;
				break;
			case 0x53:                                    // 0x53  S key
				*tnKey = VVM_S;
				break;
			case 0x54:                                    // 0x54  T key
				*tnKey = VVM_T;
				break;
			case 0x55:                                    // 0x55  U key
				*tnKey = VVM_U;
				break;
			case 0x56:                                    // 0x56  V key
				*tnKey = VVM_V;
				break;
			case 0x57:                                    // 0x57  W key
				*tnKey = VVM_W;
				break;
			case 0x58:                                    // 0x58  X key
				*tnKey = VVM_X;
				break;
			case 0x59:                                    // 0x59  Y key
				*tnKey = VVM_Y;
				break;
			case 0x5A:                                    // 0x5A  Z key
				*tnKey = VVM_Z;
				break;
			case VK_LWIN:                                 // 0x5B  Left Windows key (Natural keyboard)
				*tnKey = VVM_LWIN;
				break;
			case VK_RWIN:                                 // 0x5C  Right Windows key (Natural keyboard)
				*tnKey = VVM_RWIN;
				break;
			case VK_APPS:                                 // 0x5D  Applications key (Natural keyboard)
				*tnKey = VVM_APPS;
				break;
			case VK_SLEEP:                                // 0x5F  Computer Sleep key
				*tnKey = VVM_SLEEP;
				break;
			case VK_NUMPAD0:                              // 0x60  Numeric keypad 0 key
				*tnKey = VVM_NUMPAD0;
				break;
			case VK_NUMPAD1:                              // 0x61  Numeric keypad 1 key
				*tnKey = VVM_NUMPAD1;
				break;
			case VK_NUMPAD2:                              // 0x62  Numeric keypad 2 key
				*tnKey = VVM_NUMPAD2;
				break;
			case VK_NUMPAD3:                              // 0x63  Numeric keypad 3 key
				*tnKey = VVM_NUMPAD3;
				break;
			case VK_NUMPAD4:                              // 0x64  Numeric keypad 4 key
				*tnKey = VVM_NUMPAD4;
				break;
			case VK_NUMPAD5:                              // 0x65  Numeric keypad 5 key
				*tnKey = VVM_NUMPAD5;
				break;
			case VK_NUMPAD6:                              // 0x66  Numeric keypad 6 key
				*tnKey = VVM_NUMPAD6;
				break;
			case VK_NUMPAD7:                              // 0x67  Numeric keypad 7 key
				*tnKey = VVM_NUMPAD7;
				break;
			case VK_NUMPAD8:                              // 0x68  Numeric keypad 8 key
				*tnKey = VVM_NUMPAD8;
				break;
			case VK_NUMPAD9:                              // 0x69  Numeric keypad 9 key
				*tnKey = VVM_NUMPAD9;
				break;
			case VK_MULTIPLY:                             // 0x6A  Multiply key
				*tnKey = VVM_MULTIPLY;
				break;
			case VK_ADD:                                  // 0x6B  Add key
				*tnKey = VVM_ADD;
				break;
			case VK_SEPARATOR:                            // 0x6C  Separator key
				*tnKey = VVM_SEPARATOR;
				break;
			case VK_SUBTRACT:                             // 0x6D  Subtract key
				*tnKey = VVM_SUBTRACT;
				break;
			case VK_DECIMAL:                              // 0x6E  Decimal key
				*tnKey = VVM_DECIMAL;
				break;
			case VK_DIVIDE:                               // 0x6F  Divide key
				*tnKey = VVM_DIVIDE;
				break;
			case VK_F1:                                   // 0x70  F1 key
				*tnKey = VVM_F1;
				break;
			case VK_F2:                                   // 0x71  F2 key
				*tnKey = VVM_F2;
				break;
			case VK_F3:                                   // 0x72  F3 key
				*tnKey = VVM_F3;
				break;
			case VK_F4:                                   // 0x73  F4 key
				*tnKey = VVM_F4;
				break;
			case VK_F5:                                   // 0x74  F5 key
				*tnKey = VVM_F5;
				break;
			case VK_F6:                                   // 0x75  F6 key
				*tnKey = VVM_F6;
				break;
			case VK_F7:                                   // 0x76  F7 key
				*tnKey = VVM_F7;
				break;
			case VK_F8:                                   // 0x77  F8 key
				*tnKey = VVM_F8;
				break;
			case VK_F9:                                   // 0x78  F9 key
				*tnKey = VVM_F9;
				break;
			case VK_F10:                                  // 0x79  F10 key
				*tnKey = VVM_F10;
				break;
			case VK_F11:                                  // 0x7A  F11 key
				*tnKey = VVM_F11;
				break;
			case VK_F12:                                  // 0x7B  F12 key
				*tnKey = VVM_F12;
				break;
			case VK_F13:                                  // 0x7C  F13 key
				*tnKey = VVM_F13;
				break;
			case VK_F14:                                  // 0x7D  F14 key
				*tnKey = VVM_F14;
				break;
			case VK_F15:                                  // 0x7E  F15 key
				*tnKey = VVM_F15;
				break;
			case VK_F16:                                  // 0x7F  F16 key
				*tnKey = VVM_F16;
				break;
			case VK_F17:                                  // 0x80  F17 key
				*tnKey = VVM_F17;
				break;
			case VK_F18:                                  // 0x81  F18 key
				*tnKey = VVM_F18;
				break;
			case VK_F19:                                  // 0x82  F19 key
				*tnKey = VVM_F19;
				break;
			case VK_F20:                                  // 0x83  F20 key
				*tnKey = VVM_F20;
				break;
			case VK_F21:                                  // 0x84  F21 key
				*tnKey = VVM_F21;
				break;
			case VK_F22:                                  // 0x85  F22 key
				*tnKey = VVM_F22;
				break;
			case VK_F23:                                  // 0x86  F23 key
				*tnKey = VVM_F23;
				break;
			case VK_F24:                                  // 0x87  F24 key
				*tnKey = VVM_F24;
				break;
			case VK_NUMLOCK:                              // 0x90  NUM LOCK key
				*tnKey = VVM_NUMLOCK;
				break;
			case VK_SCROLL:                               // 0x91  SCROLL LOCK key
				*tnKey = VVM_SCROLL;
				break;
			case VK_LSHIFT:                               // 0xA0  Left SHIFT key
				*tnKey = VVM_LSHIFT;
				break;
			case VK_RSHIFT:                               // 0xA1  Right SHIFT key
				*tnKey = VVM_RSHIFT;
				break;
			case VK_LCONTROL:                             // 0xA2  Left CONTROL key
				*tnKey = VVM_LCONTROL;
				break;
			case VK_RCONTROL:                             // 0xA3  Right CONTROL key
				*tnKey = VVM_RCONTROL;
				break;
			case VK_LMENU:                                // 0xA4  Left MENU key
				*tnKey = VVM_LMENU;
				break;
			case VK_RMENU:                                // 0xA5  Right MENU key
				*tnKey = VVM_RMENU;
				break;
			case VK_BROWSER_BACK:                         // 0xA6  Browser Back key
				*tnKey = VVM_BROWSER_BACK;
				break;
			case VK_BROWSER_FORWARD:                      // 0xA7  Browser Forward key
				*tnKey = VVM_BROWSER_FORWARD;
				break;
			case VK_BROWSER_REFRESH:                      // 0xA8  Browser Refresh key
				*tnKey = VVM_BROWSER_REFRESH;
				break;
			case VK_BROWSER_STOP:                         // 0xA9  Browser Stop key
				*tnKey = VVM_BROWSER_STOP;
				break;
			case VK_BROWSER_SEARCH:                       // 0xAA  Browser Search key
				*tnKey = VVM_BROWSER_SEARCH;
				break;
			case VK_BROWSER_FAVORITES:                    // 0xAB  Browser Favorites key
				*tnKey = VVM_BROWSER_FAVORITES;
				break;
			case VK_BROWSER_HOME:                         // 0xAC  Browser Start and Home key
				*tnKey = VVM_BROWSER_HOME;
				break;
			case VK_VOLUME_MUTE:                          // 0xAD  Volume Mute key
				*tnKey = VVM_VOLUME_MUTE;
				break;
			case VK_VOLUME_DOWN:                          // 0xAE  Volume Down key
				*tnKey = VVM_VOLUME_DOWN;
				break;
			case VK_VOLUME_UP:                            // 0xAF  Volume Up key
				*tnKey = VVM_VOLUME_UP;
				break;
			case VK_MEDIA_NEXT_TRACK:                     // 0xB0  Next Track key
				*tnKey = VVM_MEDIA_NEXT_TRACK;
				break;
			case VK_MEDIA_PREV_TRACK:                     // 0xB1  Previous Track key
				*tnKey = VVM_MEDIA_PREV_TRACK;
				break;
			case VK_MEDIA_STOP:                           // 0xB2  Stop Media key
				*tnKey = VVM_MEDIA_STOP;
				break;
			case VK_MEDIA_PLAY_PAUSE:                     // 0xB3  Play/Pause Media key
				*tnKey = VVM_MEDIA_PLAY_PAUSE;
				break;
			case VK_LAUNCH_MAIL:                          // 0xB4  Start Mail key
				*tnKey = VVM_LAUNCH_MAIL;
				break;
			case VK_LAUNCH_MEDIA_SELECT:                  // 0xB5  Select Media key
				*tnKey = VVM_LAUNCH_MEDIA_SELECT;
				break;
			case VK_LAUNCH_APP1:                          // 0xB6  Start Application 1 key
				*tnKey = VVM_LAUNCH_APP1;
				break;
			case VK_LAUNCH_APP2:                          // 0xB7  Start Application 2 key
				*tnKey = VVM_LAUNCH_APP2;
				break;
			case VK_OEM_1:                                // 0xBA  Used for miscellaneous characters; it can vary by keyboard.
				*tnKey = VVM_OEM_1;
				break;
			case VK_OEM_PLUS:                             // 0xBB  For any country/region, the '+' key
				*tnKey = VVM_OEM_PLUS;
				break;
			case VK_OEM_COMMA:                            // 0xBC  For any country/region, the ',' key
				*tnKey = VVM_OEM_COMMA;
				break;
			case VK_OEM_MINUS:                            // 0xBD  For any country/region, the '-' key
				*tnKey = VVM_OEM_MINUS;
				break;
			case VK_OEM_PERIOD:                           // 0xBE  For any country/region, the '.' key
				*tnKey = VVM_OEM_PERIOD;
				break;
			case VK_OEM_2:                                // 0xBF  Used for miscellaneous characters; it can vary by keyboard.
				*tnKey = VVM_OEM_2;
				break;
			case VK_OEM_3:                                // 0xC0  Used for miscellaneous characters; it can vary by keyboard.
				*tnKey = VVM_OEM_3;
				break;
			case VK_OEM_4:                                // 0xDB  Used for miscellaneous characters; it can vary by keyboard.
				*tnKey = VVM_OEM_4;
				break;
			case VK_OEM_5:                                // 0xDC  Used for miscellaneous characters; it can vary by keyboard.
				*tnKey = VVM_OEM_5;
				break;
			case VK_OEM_6:                                // 0xDD  Used for miscellaneous characters; it can vary by keyboard.
				*tnKey = VVM_OEM_6;
				break;
			case VK_OEM_7:                                // 0xDE  Used for miscellaneous characters; it can vary by keyboard.
				*tnKey = VVM_OEM_7;
				break;
			case VK_OEM_8:                                // 0xDF  Used for miscellaneous characters; it can vary by keyboard.
				*tnKey = VVM_OEM_8;
				break;
			case VK_OEM_102:                              // 0xE2  Either the angle bracket key or the backslash key on the RT 102-key keyboard
				*tnKey = VVM_OEM_102;
				break;
			case VK_PROCESSKEY:                           // 0xE5  IME PROCESS key
				*tnKey = VVM_PROCESSKEY;
				break;
			case VK_PACKET:                               // 0xE7  Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
				*tnKey = VVM_PACKET;
				break;
			case VK_ATTN:                                 // 0xF6  Attn key
				*tnKey = VVM_ATTN;
				break;
			case VK_CRSEL:                                // 0xF7  CrSel key
				*tnKey = VVM_CRSEL;
				break;
			case VK_EXSEL:                                // 0xF8  ExSel key
				*tnKey = VVM_EXSEL;
				break;
			case VK_EREOF:                                // 0xF9  Erase EOF key
				*tnKey = VVM_EREOF;
				break;
			case VK_PLAY:                                 // 0xFA  Play key
				*tnKey = VVM_PLAY;
				break;
			case VK_ZOOM:                                 // 0xFB  Zoom key
				*tnKey = VVM_ZOOM;
				break;
			case VK_NONAME:                               // 0xFC  Reserved
				*tnKey = VVM_NONAME;
				break;
			case VK_PA1:                                  // 0xFD  PA1 key
				*tnKey = VVM_PA1;
				break;
			case VK_OEM_CLEAR:                            // 0xFE  Clear key
				*tnKey = VVM_OEM_CLEAR;
				break;

			default:
				*tnKey = VVM_UNKNOWN;
				break;
		}
	}




//////////
//
// Signal that this window has now been activated and has focus, and signal to the old
// window that it has lost focus.
//
//////
	bool iioss_signalWindowFocusCallbacksCallback(SStartEndCallback* cb)
	{
		_iswSOssWindowLL*	w;
		SOssWindow			lisw;
		_iswSFocusCallback*	lfc;


		// Make sure our environment is sane
		if (cb && cb->ptr)
		{
			w = (_iswSOssWindowLL*)cb->ptr;
			lfc = (_iswSFocusCallback*)cb->extra;

			// See if this is the window that should receive focus
			if (w->isw.osHandle == lfc->osHandle)
				lfc->forFocus = w;		// It is

			// See if this window currently has focus
			if (w->isw.hasFocus)
			{
				// Is this window losing focus?
				if (w->isw.osHandle != lfc->osHandle)
				{
					// This window is losing focus
					if (w->isw.callback.window._callback_lostFocus)
					{
						// Signal this window that it's losing focus
						ioss_lockSemaphore(w->isw.callback.window.semaphore_lostFocus);
						memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
						w->isw.callback.window.callback_lostFocus(w->isw.uniqueId, &lisw);
						ioss_unlockSemaphore(w->isw.callback.window.semaphore_lostFocus);
					}
					// And make it so
					w->isw.hasFocus = false;

				} else {
					// This window already had focus
					// And it should, so we're good
				}
			}
		}
		// Not found
		return(false);
	}




//////////
//
// Signals that the window is being destroyed
//
//////
	void ioss_signalWindowUnloadCallback(HWND hwnd)
	{
		_iswSOssWindowLL*		w;
		SOssWindow		lisw;


		// Iterate through known windows to find our man
		w = ioss_findSOssWindowLLByHwnd(hwnd);
		if (w)
		{
			// Signal the move if we are supposed to
			if (w->isw.callback.window._callback_unload)
			{
				ioss_lockSemaphore(w->isw.callback.window.semaphore_unload);
				memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
				w->isw.callback.window.callback_unload(w->isw.uniqueId, &lisw);
				ioss_unlockSemaphore(w->isw.callback.window.semaphore_unload);
			}

			// Signal the closed callback if necessary, if not, then just delete the window
			if (w->isw.callback.window._callback_closed)
			{
				// Send a message to the message queue so that after the window is destroyed, its callback will happen when it's no longer viable
				PostMessage(ghWndMsg/*message window*/, VVMOSS_VISIBLE_WINDOW_CLOSED, (WPARAM)w, NULL);

			} else {
				// They don't want the callback, so we'll just delete the window now and be done with it already. :-)
				ioss_signalWindowClosedCallback(w);
			}
		}
	}




//////////
//
// Signals that the window has closed
//
//////
	void ioss_signalWindowClosedCallback(_iswSOssWindowLL* w)
	{
		SOssWindow lisw;


		// Make sure there's something to do! :-)
		if (w)
		{
			// Do the callback
			if (w->isw.callback.window._callback_closed)
			{
				ioss_lockSemaphore(w->isw.callback.window.semaphore_closed);
				memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
				w->isw.callback.window.callback_closed(w->isw.uniqueId, &lisw);
				ioss_unlockSemaphore(w->isw.callback.window.semaphore_closed);
			}

			// Release the window
			ioss_deleteVisibleWindow(w);
		}
	}




//////////
//
// BitBlt the indicated SBGRA buffer to the specified screen
//
//////
	u64 ioss_lowLevel_bitBlt_Sgra_onto_ossWindow(_iswSOssWindowLL* tw, SBGRA* bd, u32 width, u32 height)
	{
		u64		lnResult;
		u32		lnX, lnY, lnActualWidth;
		SRGB*	lrgb;
		SBGRA*	lrgba;


		// Make sure there's something to do
		if (tw)
		{
			// Draw for every pixel indicated
			lnResult		= 0;
			lnActualWidth	= ioss_computeActualWidth(tw->isw.width);
			for (lnY = 0; lnY < tw->isw.height; lnY++)
			{
				if (lnY < height)
				{
					// Grab our offset for the source
					lrgba = bd + (lnY * tw->isw.width);

					// Grab our offset for the destination
					lrgb = (SRGB*)((s8*)tw->isw.osBitData + ((tw->isw.height - lnY - 1) * lnActualWidth));

					// Draw this row of pixels
					for (lnX = 0; lnX < tw->isw.width; lnX++)
					{
						if (lnX < width)
						{
							// Copy this pixel
							lrgb->red = lrgba->red;
							lrgb->grn = lrgba->grn;
							lrgb->blu = lrgba->blu;

							// Increase the pixel copy count
							++lnResult;
						}
						// Move to next pixel
						++lrgb;
						++lrgba;
					}
				}
			}

			// Tell Windows to redraw it
			InvalidateRect((HWND)tw->isw.osHandle, NULL, false);

		} else {
			// Indicate failure
			lnResult = -1;
		}
		// Indicate success or failure
		return lnResult;
	}





//////////
//
// Called to open and read the specified bitmap into memory
//
// Returns:
//		Sets tbh, tbi, tbd and tnResult to indicate the explicit return value
//		true	- success opening
//		false	- error opening or the header is not the right format
//
// tnResult will be set to:
//		0				- Success
//		-1				- No 'BM' header
//		-2				- Planes wrong, must be 1
//		-3				- Bits must be 24 or 32
//		-4				- Unable to allocate memory for bits
//		-5				- Unable to read file
//		-6				- Offset to bits in header not correct
//		-7				- Unable to allocate memory for internal SBGRA bits
//		-8				- Unable to open pathname
//
//////
	bool ioss_openAndReadBitmapFile(s8* tcPathname, SBitmapHeader* tbh, SBitmapInfo* tbi, s8** tbd, u32* tnResult)
	{
		u32			lnNumread;
		FILE*		lfh;


		while (1)
		{
			// Try to open the indicated file
			lfh = fopen(tcPathname, "rb+");		// File must already exist, open for reading/writing
			if (!lfh)
			{
				// Failure opening
				*tnResult = -8;
				return(false);
			}
			// We opened the file successfully

			// Read in the header bytes
			lnNumread = fread(tbh, 1, sizeof(SBitmapHeader), lfh);
			if (lnNumread != sizeof(SBitmapHeader))
			{
				// Disk/file read error
				fclose(lfh);
				*tnResult = -5;
				break;
			}
			// If we get here, the header's been read

			// Check the sanity of the header
			if (tbh->type != 'MB')
			{
				// It's not a valid bitmap file, the valid bitmap file will have a 'BM' as its first two bytes
				fclose(lfh);
				*tnResult = -1;
				break;
			}
			// We have our identifier, continue on

			lnNumread = fread(tbi, 1, sizeof(SBitmapInfo), lfh);
			if (lnNumread != sizeof(SBitmapInfo))
			{
				// Disk/file read error
				fclose(lfh);
				*tnResult = -5;
				break;
			}
			// If we get here, the info's been read

			// Check the sanity of the info block
			if (tbi->planes != 1)
			{
				// It's not a valid bitmap file, or at least not one we can read as we only use 1-plane bitmaps
				fclose(lfh);
				*tnResult = -2;
				break;
			}
			if (tbi->bitCount != 24 && tbi->bitCount != 32)
			{
				// It's not a valid bitmap file, or at least not one we can read as we only use 24- or 32-bit bitmaps
				fclose(lfh);
				*tnResult = -3;
				break;
			}
			if (tbh->offsetToBits != sizeof(SBitmapHeader) + tbi->sizeOfInfoBlock)
			{
				// Offset to bits not correct
				fclose(lfh);
				*tnResult = -6;
				break;
			}

			// We're sane, read the data
			*tbd = (s8*)malloc(tbi->sizeOfImage);
			if (!*tbd)
			{
				// Failure allocating memory
				*tnResult = -4;
				fclose(lfh);
				break;
			}
			// If we get here, we're good

			// Move to the bit data start in the file
			fseek(lfh, tbh->offsetToBits, SEEK_SET);

			// Read the bits
			lnNumread = fread(*tbd, 1, tbi->sizeOfImage, lfh);
			fclose(lfh);
			if (lnNumread != tbi->sizeOfImage)
			{
				// Disk/file read error
				fclose(lfh);
				*tnResult = -5;
				break;
			}
			// If we get here, the bitmap is loaded, we have the color data

			// Indicate success
			*tnResult = 0;
			return(true);
		}
		// tnResult would've already been set above for actual error condition

		// Indicate failure
		return(false);
	}




//////////
//
// Called to allocate the SBGRA bitmap data, and copy the indicated 32-bit disk-based bitmap
// to the SBGRA buffer, when the disk bitmap data is in top-down format.
//
// Returns:
//		0			- success
//		errorValue	- Error allocating memory
//
//////
	void ioss_allocateSBGRAandCopy32Bit_BitmapTopDown(SBGRA** trgbad, SBitmapHeader* tbh, SBitmapInfo* tbi, SBGRA* lrgbas, u32* tnResult, u32 tnErrorValue)
	{
		u32		lnX, lnY;
		SBGRA*	lrgbad;


		// Allocate our block
		lrgbad = (SBGRA*)malloc(tbi->height * tbi->width * sizeof(SBGRA));
		if (!lrgbad)
		{
			// Failure allocating memory
			*tnResult = tnErrorValue;
			return;
		}
		// Store the pointer
		*trgbad = lrgbad;

		// Copy the entire bitmap
		for (lnY = 0; lnY < tbi->height; lnY++)
		{
			// Iterate for every pixel column on this row
			for (lnX = 0; lnX < tbi->width; lnX++)
			{
				// Copy this pixel
				lrgbad->red = lrgbas->red;
				lrgbad->grn = lrgbas->grn;
				lrgbad->blu = lrgbas->blu;
				lrgbad->alp = lrgbas->alp;

				// Move to next bit
				++lrgbad;
				++lrgbas;
			}
		}
		// Indicate success
		*tnResult = 0;
	}




//////////
//
// Called to allocate the SBGRA bitmap data, and copy the indicated 32-bit disk-based bitmap
// to the SBGRA buffer, when the disk bitmap data is in bottom-up format.
//
// Returns:
//		0			- success
//		errorValue	- Error allocating memory
//
//////
	void ioss_allocateSBGRAandCopy32Bit_BitmapBottomUp(SBGRA** trgbad, SBitmapHeader* tbh, SBitmapInfo* tbi, SBGRA* lrgbasRoot, u32* tnResult, u32 tnErrorValue)
	{
		u32		lnX, lnY, lnPixels;
		SBGRA*	lrgbad;
		SBGRA*	lrgbas;


		// Allocate our block
		lrgbad = (SBGRA*)malloc(tbi->height * tbi->width * sizeof(SBGRA));
		if (!lrgbad)
		{
			// Failure allocating memory
			*tnResult = tnErrorValue;
			return;
		}
		// Store the pointer
		*trgbad = lrgbad;

		// Copy the entire bitmap
		lnPixels = 0;
		for (lnY = 0; lnY < tbi->height; lnY++)
		{
			// Calculate the offset for this line
			lrgbas = (SBGRA*)((s8*)lrgbasRoot + ((tbi->height - lnY - 1) * tbi->width * sizeof(SBGRA)));

			// Iterate for every pixel column on this row
			for (lnX = 0; lnX < tbi->width; lnX++)
			{
				// Copy this pixel
// TODO: Verify that the alpha channel is correct on 32-bit BMP files
				lrgbad->red = lrgbas->red;
				lrgbad->grn = lrgbas->grn;
				lrgbad->blu = lrgbas->blu;
				lrgbad->alp = lrgbas->alp;

				// Increase our count
				++lnPixels;

				// Move to next bit
				++lrgbad;
				++lrgbas;
			}
		}
		// Indicate success
		*tnResult = lnPixels;
	}




//////////
//
// Called to allocate the SBGRA bitmap data, and copy the indicated 24-bit disk-based bitmap
// to the SBGRA buffer, when the disk bitmap data is in top-down format.
//
// Returns:
//		0			- success
//		errorValue	- Error allocating memory
//
//////
	void ioss_allocateSBGRAandCopy24Bit_BitmapTopDown(SBGRA** trgbad, SBitmapHeader* tbh, SBitmapInfo* tbi, SRGB* lrgbsRoot, u32* tnResult, u32 tnErrorValue)
	{
		u32		lnX, lnY;
		SBGRA*	lrgbad;
		SRGB*	lrgbs;


		// Allocate our block
		lrgbad = (SBGRA*)malloc(tbi->height * tbi->width * sizeof(SBGRA));
		if (!lrgbad)
		{
			// Failure allocating memory
			*tnResult = tnErrorValue;
			return;
		}
		// Store the pointer
		*trgbad = lrgbad;

		// Copy the entire bitmap
		for (lnY = 0; lnY < tbi->height; lnY++)
		{
			// Calculate the offset for this line
			lrgbs = (SRGB*)((s8*)lrgbsRoot + (lnY * tbi->actualWidth));

			// Iterate for every pixel column on this row
			for (lnX = 0; lnX < tbi->width; lnX++)
			{
				// Copy this pixel
				lrgbad->red = lrgbs->red;
				lrgbad->grn = lrgbs->grn;
				lrgbad->blu = lrgbs->blu;
				lrgbad->alp = 255;

				// Move to next bit
				++lrgbad;
				++lrgbs;
			}
		}
		// Indicate success
		*tnResult = 0;
	}




//////////
//
// Called to allocate the SBGRA bitmap data, and copy the indicated 24-bit disk-based bitmap
// to the SBGRA buffer, when the disk bitmap data is in bottom-up format.
//
// Returns:
//		0			- success
//		errorValue	- Error allocating memory
//
//////
	void ioss_allocateSBGRAandCopy24Bit_BitmapBottomUp(SBGRA** trgbad, SBitmapHeader* tbh, SBitmapInfo* tbi, SRGB* lrgbsRoot, u32* tnResult, u32 tnErrorValue)
	{
		u32		lnX, lnY;
		SBGRA*	lrgbad;
		SRGB*	lrgbs;


		// Allocate our block
		lrgbad = (SBGRA*)malloc(tbi->height * tbi->width * sizeof(SBGRA));
		if (!lrgbad)
		{
			// Failure allocating memory
			*tnResult = tnErrorValue;
			return;
		}
		// Store the pointer
		*trgbad = lrgbad;

		// Copy the entire bitmap
		for (lnY = 0; lnY < tbi->height; lnY++)
		{
			// Calculate the offset for this line
			lrgbs = (SRGB*)((s8*)lrgbsRoot + ((tbi->height - lnY - 1) * tbi->actualWidth));

			// Iterate for every pixel column on this row
			for (lnX = 0; lnX < tbi->width; lnX++)
			{
				// Copy this pixel
				lrgbad->red = lrgbs->red;
				lrgbad->grn = lrgbs->grn;
				lrgbad->blu = lrgbs->blu;
				lrgbad->alp = 255;

				// Move to next bit
				++lrgbad;
				++lrgbs;
			}
		}
		// Indicate success
		*tnResult = 0;
	}




//////////
//
// Performs our 10ms activities.
//
// Direct Windows callback for timer.
// Should not be called directly.
//
// Timer fires every 10ms (in theory), but regardless of system sluggishness, for the sake
// of maintaining coherency and flow within, this function assumes it was exactly 10ms. :-)
//
//////
	LRESULT CALLTYPE iioss_timerProc_10ms(HWND hwnd, UINT msg, UINT_PTR idEvent, DWORD dwTime)
	{
		SStartEndCallback cb;


		// The timer has fired, updating timers and trigger any hover events
		cb._func = (u64)iioss_update10msTimersCallback;
		oss_SEChain_searchByCallback(&gseRootWindows, &cb);

		// All done
		return 0;
	}

	bool iioss_update10msTimersCallback(SStartEndCallback* cb)
	{
		u64					lnTimerDiff;
		_iswSOssWindowLL*	w;
		SOssWindow			lisw;


		// Make sure our environment's sane
		if (cb && cb->ptr)
		{
			w = (_iswSOssWindowLL*)cb->ptr;
			// Increase the timer
			w->isw.timer += 10;

			// Increase the accumulation timers
			if (w->isw.osIsMouseButtonDown)
				w->isw.osMouseDownAccumulationCounter += 10;	// Increments that this item has been pressed down for this long

			// See if we're beginning a drag:
			//		(1) At least one mouse button is down
			//		(2) Not already dragging
			//		(3) They want dragDrop callbacks
			//		(4) They've dragged at least 7 pixels as the crow flies
			if (w->isw.osIsMouseButtonDown)
			{
				if (!w->isw.osIsDragging)
				{
					if (w->isw.callback.drag._callback_start)
					{
						if (ioss_distanceBetween(	w->isw.osMouseMove.x,		w->isw.osMouseMove.y,
												w->isw.osMouseDownFirst.x,	w->isw.osMouseDownFirst.y) > gfMouseDragThreshold)
						{
							// A drag has now started
							ioss_lockSemaphore(w->isw.callback.drag.semaphore_start);
							memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
							w->isw.callback.drag.callback_start(w->isw.uniqueId, &lisw, w->isw.osMouseDownFirst.x, w->isw.osMouseDownFirst.y, w->isw.osMouseMove.buttons, w->isw.osMouseMove.keys);
							ioss_unlockSemaphore(w->isw.callback.drag.semaphore_start);
							w->isw.osIsDragging = true;
						}
					}
				}
			}

			// See if a hover event has been triggered
			if (w->isw.callback.mouse._callback_hover && !w->isw.osHoverCallbackFired && !w->isw.osIsDragging)
			{
				// The hover function is defined, see if the timing is right
				lnTimerDiff = w->isw.timer - w->isw.osMouseMove.timer;
				if (lnTimerDiff > gnHoverTimeout)
				{
					// Raise the flag
					w->isw.osHoverCallbackFired = true;

				//////////
				// Do the callback
				//////
				// Note:  The callback function should NOT do its work in this thread.
				//        This thread should only be used for notification to kick off
				//        worker threads.
				//////
					ioss_lockSemaphore(w->isw.callback.mouse.semaphore_hover);
					memcpy(&lisw, &w->isw, sizeof(SOssWindow));		// Make a copy of the record in case the user goes nutty coo-coo! :-)
					w->isw.callback.mouse.callback_hover(w->isw.uniqueId, &lisw, w->isw.osMouseMove.x, w->isw.osMouseMove.y, w->isw.osMouseMove.buttons, w->isw.osMouseMove.keys, lnTimerDiff, false);
					ioss_unlockSemaphore(w->isw.callback.mouse.semaphore_hover);
				}
			}
		}
		// Indicate a false condition here
		// We do this so we can continue receiving the callbacks for all SOssWindows
		return(false);
	}





//////////
//
// Code to continually update our 1ms tick counter
//
// Designed to be self-contained.
// Directed from WM_CREATE on message window startup, specifically for this timer.
// Should not be called directly.
//
// For higher resolution timers:
//		HANDLE CreateTimedEvent(BOOL bManualReset, LPCTSTR lpTimerName);
//		long long Time(void);
//		int SetTimedEvent(HANDLE hTimerEvent, long long TimerDueTime, long long TimerPeriod);
//		int CancelTimedEvent(HANDLE hTimerEvent);
//		HANDLE OpenTimedEvent(LPCTSTR lpTimerName);
//		int DeleteTimedEvent(HANDLE hTimerEvent);
//
//////
	DWORD CALLTYPE iioss_1MsTimerThread(LPVOID lpParameter)
	{
		LARGE_INTEGER lnStartTime;


		// Create the timer
// TODO: If we are not the only running VVM instance, we need to give it a unique name
		ghTimer1ms = CreateWaitableTimer(0, 0, cgw1msTimer);

		// Activate it
		lnStartTime.QuadPart = 0;
		if (!SetWaitableTimer(ghTimer1ms, &lnStartTime, 1, &iiioss_1MsTimerThreadTimerAPCProc, 0, FALSE))
		{
			// Timer was NOT created ... what to do? Hmmm...
			SendMessage(ghWndMsg, VVMOSS_FATAL_ERROR, VVMOSS_FATAL_ERROR_IN_1MS_TIMER, 0);
			return 0;
		}

		// Wait forever processing only the tick count
		while (1)
		{
			SleepEx(INFINITE, TRUE);
		}
	}

	// Only called by Windows through the iioss_1MsTimerThread SetWaitableTimer() function.
	// Do not call directly.
	void CALLTYPE iiioss_1MsTimerThreadTimerAPCProc(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
	{
		// Note:  No semaphore access.  This value is ONLY updated by this thread.
		++gnTickCount;

		// Copy for external visibility
		gnExternallyVisibleTickCount = gnTickCount;
	}





//////////
//
// Callback from oss_sharedAsciiCloseFile() or oss_sharedUnicodeCloseFile() to unlock any file
// locks which remain as the user is closing the file
//
//////
	void iioss_sharedAsciiCloseFileLocksCallback(void* ptr, u64 tnParam)
	{
		_iswSSharedFile*		lfs;
		_iswSSharedFileLocks*	lfsl;


		lfs		= (_iswSSharedFile*)tnParam;						// Get the shared file pointer
		lfsl	= (_iswSSharedFileLocks*)ptr;						// Get the lock pointer

		// Do the work
		_lseeki64(lfs->handle, lfsl->offset, SEEK_SET);				// Seek to offset
		_locking(lfs->handle, _LK_UNLCK, (s32)lfsl->length);		// Unlock
	}




//////////
//
// Callback from oss_realloc() and oss_free() to find out if the memory pointer they're
// trying to realloc or free matches that stored in the SDatumLL structure.
//
//////
	bool iioss_reallocAndFreeCallback(SStartEndCallback* cb)
	{
		SDatumLL* ldll;


		// Convert to our SDatumLL structure
		ldll = (SDatumLL*)cb->ptr;

		// See if this is our man
		if (ldll->datum.data._s8 == (void*)cb->extra)
			return(true);

		// Nope
		return(false);
	}




//////////
//
// Scans from the indicated location forward until finding CR/LF or any combination thereof,
// nothing whitespaces, content, and total line length (including cr/lf combinations at the end)
//
//////
	u64 ioss_breakoutAsciiTextDataIntoLines_ScanLine(s8* tcData, u64 tnMaxLength, u64* tnLength, u64* tnWhitespaces)
	{
		u64 lnLength, lnWhitespaces, lnCRLF_Length;


		// Make sure we have something to do
		lnLength		= 0;
		lnWhitespaces	= 0;
		lnCRLF_Length	= 0;
		if (tcData && tnMaxLength > 0)
		{
			// Skip past any whitespaces
			lnWhitespaces = ioss_skipWhitespaces(tcData, tnMaxLength);
			if (tnWhitespaces)
				*tnWhitespaces = lnWhitespaces;


			// Skip to the ending carriage return / line feed
			lnLength = ioss_skipToCarriageReturnLineFeed(tcData + lnWhitespaces, tnMaxLength - lnWhitespaces, &lnCRLF_Length);
			if (tnLength)
				*tnLength = lnLength;
		}
		// Return the total length
		return(lnWhitespaces + lnLength + lnCRLF_Length);
	}




//////////
//
// Scans from the indicated location forward until finding a non-whitespace character
//
//////
	u64 ioss_skipWhitespaces(s8* tcData, u64 tnMaxLength)
	{
		u64 lnLength;


		// Make sure our environment's sane
		lnLength = 0;		// Initially indicate no whitespaces
		if (tcData && tnMaxLength > 0)
		{
			// While we encounter spaces or tabs, count them
			while (lnLength < tnMaxLength && (tcData[lnLength] == 32 || tcData[lnLength] == 9))
				++lnLength;
			// When we get here, lnLength is the number of whitespaces (if any)
		}
		// Indicate the total length encountered
		return(lnLength);
	}




//////////
//
// Scans from the indicated location forward until finding a non-whitespace, non-cr, non-lf
// character.
//
//////
	u64 ioss_skipWhitespacesAndCrLf(s8* tcData, u64 tnMaxLength)
	{
		u64 lnLength;


		// Make sure our environment's sane
		lnLength = 0;		// Initially indicate no whitespaces
		if (tcData && tnMaxLength > 0)
		{
			// While we encounter spaces or tabs, count them
			while (lnLength < tnMaxLength && (tcData[lnLength] == 32 || tcData[lnLength] == 9 || tcData[lnLength] == 10 || tcData[lnLength] == 13))
				++lnLength;
			// When we get here, lnLength is the number of whitespace/cr/lf (if any)
		}
		// Indicate the total length encountered
		return(lnLength);
	}




//////////
//
// Scans from the indicated location forward until finding CR/LF or any combination thereof
//
//////
	u64 ioss_skipToCarriageReturnLineFeed(s8* tcData, u64 tnMaxLength, u64* tnCRLF_Length)
	{
		u64 lnLength, lnCRLF_Length;


		// Make sure our environment's sane
		lnLength		= 0;		// Initially indicate a line length of 0
		lnCRLF_Length	= 0;		// Same for CR/LF length
		if (tcData && tnMaxLength > 0)
		{
			// While we do not counter a CR or LF, continue
			while (lnLength < tnMaxLength && tcData[lnLength] != 13 && tcData[lnLength] != 10)
				++lnLength;

			// See if we are done
			if (lnLength < tnMaxLength)
			{
				// We did not reach the end of the entire data available to us to search
				// So, when we get here, we're sitting on a CR or LF, which is the end of line
				if (tcData[lnLength] == 13)
				{
					// We're sitting on a carriage return
					// If the next character is a line feed, we count it
					if (tcData[lnLength + 1] == 10)		lnCRLF_Length = 2;		// We have a pair
					else								lnCRLF_Length = 1;		// Just the one

				} else {
					// We know we're sitting on a line feed
					// If the next character is a carriage return, we count it
					if (tcData[lnLength + 1] == 13)		lnCRLF_Length = 2;		// We have a pair
					else								lnCRLF_Length = 1;		// Just the one
				}

			} else {
				// We reached the end
				// We don't do anything here, but just return the length
			}
		}
		// When we get here, return the lengths
		// The CR/LF length
		if (tnCRLF_Length)
			*tnCRLF_Length = lnCRLF_Length;

		// The stuff before length :-)
		return(lnLength);
	}




//////////
//
// Search the haystack for the needle, the haystack can be tupels, as in "_az" meaning
// (is it between "a" and "z" inclusive?)  To set this condition, use a length of 1,
// a leading "_" in tcHaystack, and two characters (one of which must NOT be NULL) after.
// Examples:
//		_az		= lower-case a to z inclusive
//		_AZ		= upper-case a to z inclusive
//		_09		= numeric 0 to 9 inclusive
//
// Returns:
//		0		= matches
//		!0		= does not tmach
//
//////
	s32 ioss_translateSOssLinesToSOssCompsTest(s8* tcHaystack, s8* tcNeedle, s32 tnLength)
	{
		u32		lnI;
		bool	llSigned;


		// Make sure our environment is sane
		if (tnLength != 0)
		{
			// See if we're a signed or unsigned compare
			if (tnLength < 0)
			{
				// Case sensitive compare
				tnLength	= -tnLength;
				llSigned	= true;

			} else {
				// Case insensitive compare
				llSigned = false;
			}

			// See if we're looking for a tuple, or a regular compare
			if (tcHaystack[0] == '_' && tnLength == 1)
			{
				// It's an explicit match of a range (this is ALWAYS subject to case as it is an explicit range)
				for (lnI = 1; tcHaystack[lnI] != 0 || tcHaystack[lnI + 1] != 0; lnI += 2)
				{
					//		within the range low			.........			up to the range high
					if (tcNeedle[0] >= tcHaystack[lnI]			&&		tcNeedle[0] <= tcHaystack[lnI + 1])
						return(0);		// It's a match, needle is in the range
				}
				// Not a match, will fall through to below

			} else {
				// Just a regular compare
				if (llSigned)	return(  memcmp(tcHaystack, tcNeedle, tnLength));
				else			return(_memicmp(tcHaystack, tcNeedle, tnLength));
			}
		}
		// If we get here, no match
		return(-1);
	}




//////////
//
// Callback, used to translate existing components into other components
// Note:  Always returns false, so it will continue being fed every component
//
//////
	bool iioss_translateSOssCompsToOthersCallback(SStartEndCallback* cb)
	{
		s32					lnLacsLength;
		SOssComp*			comp;
		SAsciiCompSearcher*	lacs;


		// Make sure the environment is sane
		if (cb && cb->ptr)
		{
			// Grab our pointers into recognizable thingamajigs
			comp	= (SOssComp*)cb->ptr;
			lacs	= (SAsciiCompSearcher*)cb->extra;

			// Iterate through this item to see if any match
			for (	/* lacs is initialize above */;
					lacs->length != 0;
					lacs++		)
			{
				// Grab the normalized length
				lnLacsLength = abs(lacs->length);

				// We only test if they're the same length
				if (lnLacsLength == comp->length || (lacs->repeats && lnLacsLength <= comp->length))
				{
					// We only test if this item is not the first item on line, or if must be the first
					// item on the line, then this component must be the first component on the line.  Simple, yes? :-)
					if (!lacs->firstOnLine || comp->start == 0)
					{
						// Physically conduct the exact comparison
						if (ioss_translateSOssLinesToSOssCompsTest((s8*)lacs->keyword, 
																	comp->line->base + comp->line->start + comp->line->whitespace + comp->start, 
																	lacs->length) == 0)
						{
							// This is a match, convert it, translate it, whatever you want to call it, just make it be the new code, per the user's request, got it? :-)
							comp->iCode = lacs->iCode;

							// All done with this component
							break;
						}
					}
				}
			}

		}
		// We always simulate a false condition so we'll keep receiving each item
		return(false);
	}




//////////
//
// Verifies that the indicated length is allowed based on the maximum length / position.
//
//////
	inline bool ioss_verifyLength(u64 tnGoingTo, u64 tnMaxAllowable)
	{
		return(tnGoingTo <= tnMaxAllowable);
	}




//////////
//
// Returns whether or not the indicated character is alpha or alphanumeric
//
//////
	bool ioss_isAlpha(s8 c)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
			return(true);

		// If we get here, it wasn't alpha
		return(false);
	}

	bool ioss_isNumeric(s8 c)
	{
		if (c >= '0' && c <= '9')
			return(true);

		// If we get here, it wasn't numeric
		return(false);
	}

	bool ioss_isAlphanumeric(s8 c)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
			return(true);

		// If we get here, it wasn't alphanumeric
		return(false);
	}




//////////
//
// Called to convert the sequence of numeric digits, which must be pre-validated to exist as
// numeric digits, into a number.
//
//////
	u32 ioss_convertValidatedNumericStringToU32(s8* tcData, u32 tnMaxLength)
	{
		u32 lnI, lnValue;


		// Make sure our environment is sane
		lnValue = 0;
		if (tcData && tnMaxLength != 0)
		{
			// Repeat for every digit
			for (lnI = 0; lnI < tnMaxLength; lnI++)
			{
				lnValue = lnValue * 10;
				lnValue = lnValue + (u32)(tcData[lnI] - '0');
			}
		}

		// Return our value
		return(lnValue);
	}

	u64 ioss_convertValidatedNumericStringToU64(s8* tcData, u32 tnMaxLength)
	{
		u32 lnI;
		u64 lnValue;


		// Make sure our environment is sane
		lnValue = 0;
		if (tcData && tnMaxLength != 0)
		{
			// Repeat for every digit
			for (lnI = 0; lnI < tnMaxLength; lnI++)
			{
				lnValue = lnValue * 10;
				lnValue = lnValue + (u64)(tcData[lnI] - '0');
			}
		}

		// Return our value
		return(lnValue);
	}




//////////
//
// Called to ensure the indicated number of bytes can be appended onto the buffer without
// issue.  If not, reallocates the buffer.
//
//////
	void ioss_bufferVerifySizeForNewBytes(SBuffer* buffRoot, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot && tnDataLength != 0)
		{
			// Repeatedly allocate our allocation size until we get big enough
			while (buffRoot->data)
			{
				// Are we there yet?
				if (buffRoot->populatedLength + tnDataLength < buffRoot->allocatedLength)
				{
					// We're good, update our populated size
					buffRoot->populatedLength += tnDataLength;
					return;
				}
				// If we get here, we need to allocate more space

				// Reallocate and continue
				buffRoot->data				= (s8*)oss_realloc(buffRoot->data, buffRoot->allocatedLength + buffRoot->allocateBlockSize);
				buffRoot->allocatedLength	+= buffRoot->allocateBlockSize;
			}
		}
		// If we get here, there's been an error
	}




//////////
//
// Scales the canvas from source to destination
//
//////
	u64 iioss_canvasScale(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap** tsSm)
	{
		u64			lnPixelsDrawn;
		f64			lfVertical, lfHorizontal;
		SScaleMap*	lsm;
		SScaleMap**	lsmLast;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		// We have valid source and destination canvases
		if (tsSrc->width == tsDst->width && tsSrc->height == tsDst->height)
		{
			// They're the same size, just copy them
			memcpy(tsDst->bd, tsSrc->bd, tsSrc->width * tsSrc->height * sizeof(SBGRA));
			lnPixelsDrawn = tsSrc->width * tsSrc->height;

		} else {
			// We need to scale
			lsmLast	= tsSm;
			lsm		= NULL;

			// See if there is already an existing map
			if (*tsSm)
			{
				// Maybe one of those can be used
				lsm = *tsSm;
				while (lsm)
				{
					// See if it's the same size
					if (     /*Source*/ lsm->src.width == tsSrc->width && lsm->src.height == tsSrc->height &&
					    /*Destination*/ lsm->dst.width == tsDst->width && lsm->dst.height == tsDst->height)
					{
						// It is a full match, we can use this scale computation
						break;
					}

					// Move to the next entry
					lsmLast = (SScaleMap**)&lsm->next;
					lsm		= (SScaleMap*)lsm->next;
				}
			}

			// Do we need to create a new block?
			if (!lsm)
			{
				// Yes
				lsm = (SScaleMap*)malloc(sizeof(SScaleMap));

				// If we fail, we cannot proceed
				if (!lsm)
					return(0);

				// Initialize the block
				memset(lsm, 0, sizeof(SScaleMap));

				// Update the back-link
				*lsmLast = lsm;
			}

			// Physically conduct the scale
			lfVertical		= (f64)tsSrc->height / (f64)tsDst->height;
			lfHorizontal	= (f64)tsSrc->width  / (f64)tsDst->width;
			lnPixelsDrawn	= iioss_canvasScaleProcess(tsDst, tsSrc, lsm, lfVertical, lfHorizontal);
		}

		// Indicate our failure or success
		return(lnPixelsDrawn);
	}




//////////
//
// Takes a 24-bit bitmap, and scales it up or down to the specified size, with a
// minimum of a 1x1 pixel size.
//
// Returns:
//		-1		- Input file could not be opened
//		-2		- Invalid input bitmap
//		-3		- Unable to allocate memory for input bitmap
//		-4		- Error reading input bitmap
//		-5		- Unable to allocate memory for output bitmap
//		-6		- Unable to create the output file
//		-7		- Unable to write to output file
//
//////
	u64 iioss_canvasScaleProcess(SCanvas* tsDst, SCanvas* tsSrc, SScaleMap* tsSm, f64 tfVerticalScaler, f64 tfHorizontalScaler)
	{
		u64							lnPixelsDrawn;
		f64							lfMult, lfRed, lfGrn, lfBlu, lfAlp;
		s32							lnY, lnX;
		u32							lnOffset;
		_isSSpannedPixelProcessing	spp;
		SScaleCompute*				lsc;
		SBGRA*						lbgras;
		SBGRA*						lbgrad;


		// Initialize everything in the spp
		memset(&spp, 0, sizeof(spp));

		// Are we scaling based on the formula already derived?
		if (!tsSm->firstScale)
		{
			// Build the scale computation
			spp.dst			= tsDst;
			spp.src			= tsSrc;
			spp.sm			= tsSm;
			spp.ratioV		= (f64)tsSrc->height	/ (f64)tsDst->height;
			spp.ratioH		= (f64)tsSrc->width		/ (f64)tsDst->width;
			spp.rowWidth	= tsSrc->width * sizeof(SBGRA);

			// Iterate through every pixel row by row, column by column
			lnPixelsDrawn = 0;
			for (lnY = 0; lnY < tsDst->height; lnY++)
			{
				for (lnX = 0; lnX < tsDst->width; lnX++)
				{
					// Compute data for this spanned pixel
					spp.uly			= min((f64)lnY * spp.ratioV, (f64)tsSrc->height - spp.ratioV);
					spp.ulx			= min((f64)lnX * spp.ratioH, (f64)tsSrc->width  - spp.ratioH);
					spp.lry			= spp.uly + spp.ratioV - 0.000000000001f;
					spp.lrx			= spp.ulx + spp.ratioH - 0.000000000001f;
					spp.areaSpanned	= (spp.lrx - spp.ulx) * (spp.lry - spp.uly);

					spp.offsetSrc	= (((s32)spp.uly * tsSrc->width) + (s32)spp.ulx) * sizeof(SBGRA);
					spp.offsetDst	= ((lnY          * tsDst->width) + lnX         ) * sizeof(SBGRA);

// if ((lnY == 2 && lnX == 516) || (lnY == 5 && lnX == 516) || (lnY == 798 && lnX == 516))
// 	_asm nop;
					// Derive the scale computation for this spanned pixel
					iioss_getSpannedPixelComputation(&spp);
				}
			}
			// When we get here, we've computed everything
		}


		// Now perform the scale
		if (tsSm->firstScale)
		{
			// Initialize everything in the destination to black and 0 alpha (because every pixel computation is added to the prior values)
			oss_memset4((u32*)tsDst->bd, 0, tsDst->width * tsDst->height);

			// Apply the scaling computation
			lsc = tsSm->firstScale;
			while (lsc)
			{
				// Compute this portion
				lbgras		= (SBGRA*)((s8*)tsSrc->bd + lsc->sbgraOffsetSrc);
				lbgrad		= (SBGRA*)((s8*)tsDst->bd + lsc->sbgraOffsetDst);
				lfMult		= lsc->multiplier;

				// Compute the translation
				lfAlp		= (f64)lbgras->alp * lfMult;
				lfRed		= (f64)lbgras->red * lfMult;
				lfGrn		= (f64)lbgras->grn * lfMult;
				lfBlu		= (f64)lbgras->blu * lfMult;
				lnOffset	= lsc->sbgraOffsetDst;
				
				// Move to next scale entry
				lsc = (SScaleCompute*)lsc->next;

				// So long as we're dealing with the same destination pixel, acumulate the alpha, red, green and blue values
				if (lsc && lsc->sbgraOffsetDst == lnOffset)
				{
					// Accumulate everything for this destination offset
					do {
						// Get the multiplier for this pixel
						lbgras	= (SBGRA*)((s8*)tsSrc->bd + lsc->sbgraOffsetSrc);
						lfMult	= lsc->multiplier;

						// Add in this part of the computation
						lfAlp	+= (f64)lbgras->alp * lfMult;
						lfRed	+= (f64)lbgras->red * lfMult;
						lfGrn	+= (f64)lbgras->grn * lfMult;
						lfBlu	+= (f64)lbgras->blu * lfMult;

						// Move to next scale entry
						lsc = (SScaleCompute*)lsc->next;

					} while (lsc && lsc->sbgraOffsetDst == lnOffset);
				}

				// Store the physical data
				lbgrad->alp	+= (u8)lfAlp;
				lbgrad->red	+= (u8)lfRed;
				lbgrad->grn	+= (u8)lfGrn;
				lbgrad->blu	+= (u8)lfBlu;
			}
			// When we get here, the source is scaled into the destination
		}

		// Finished, indicate the pixel count
		return(tsDst->width * tsDst->height);
	}




//////////
//
// Get spanned pixel data, meaning the input (bii, bdi) values are scanned based on the
// location of tnY,tnX and the relationship between bii and bio, meaning the input and
// output sizes.  If bii is bigger, then each bio pixel maps to more than one bii pixel.
// If they're identical, it's 1:1.  If bii is smaller, then each bio pixel maps to less
// than one full bii pixel.  There are no other options. :-)  This algorithm should not
// be used for 1:1 ratio conversions.
//
// Note that each of the above conditions applies to both width and height, meaning the
// relationship between bii and bio is analyzed on each axis, resulting in nine possible
// states (wider+taller, wider+equal, wider+shorter, equal+taller, equal+equal, equal+shorter,
// narrower+taller, narrower+equal, narrower+shorter).
//
// This natural relationship breaks down into nine general point forms:
//		Original pixels:			Output pixels span original pixels:
//		 ______________ 			 ______________ 			 ______________
//		|    |    |    |			|    |    |    |			|1   | 2  |   3|
//		|____|____|____|			|__+--------+__|			|__+--------+__|
//		|    |    |    |	==>		|  |        |  |	==>		|4 |   5    | 6|
//		|____|____|____|	==>		|__|        |__|	==>		|__|        |__|
//		|    |    |    |			|  +--------+  |			|7 +---8----+ 9|
//		|____|____|____|			|____|____|____|			|____|____|____|
//
// This form is comprised of 9 general parts, eight of which may not be present in all
// relationships, and five of which may span multiple columns, rows or both.
//
// These are:
//		1	- upper-left	(always,	spans at most one pixel)
//		2	- upper-middle	(optional,	spans at most multiple partial or full pixels)
//		3	- upper-right	(optional,	spans at most one pixel)
//		4	- middle-left	(optional,	spans at most multiple partial or full pixels)
//		5	- middle-middle	(optional,	can span multiple partial or full pixels)
//		6	- middle-right	(optional,	spans at most multiple partial or full pixels)
//		7	- lower-left	(optional,	spans at most one pixel)
//		8	- lower-middle	(optional,	spans at most multiple partial or full pixels)
//		9	- lower-right	(optional,	spans at most one pixel)
//
//////
	void iioss_getSpannedPixelComputation(_isSSpannedPixelProcessing* spp)
	{
		// Raise the flags for which portions are valid / required
		spp->spans2H		= (ioss_getIntegersBetween(spp->ulx, spp->lrx) >= 1);		// It occupies at least two pixels horizontally (itself and one more)
		spp->spans3H		= (ioss_getIntegersBetween(spp->ulx, spp->lrx) >= 2);		// It occupies at least three pixels horizontally (itself, at least one in the middle, and one at the right)
		spp->spans2V		= (ioss_getIntegersBetween(spp->uly, spp->lry) >= 1);		// It occupies at least two pixels vertically (itself and one more)
		spp->spans3V		= (ioss_getIntegersBetween(spp->uly, spp->lry) >= 2);		// It occupies at least three pixels vertically (itself, at least one in the middle, and one at the right)

		// Compute the information necessary to process each of the 9 portions of points
		// Store left- and right-sides for this spanned pixel
		spp->left			= (s32)min(spp->ulx,			spp->src->width - 1);
		spp->right			= (s32)min(spp->lrx,			spp->src->width - 1);

		// Compute the middle section in pixels
		// Note: -2 is for -1 base 0, and -1 because we want the max value to be one before the width/height
		spp->middleStartH	= (s32)min(spp->ulx + 1,		spp->src->width  - 1);		// next pixel right of upper-left
		spp->middleFinishH	= (s32)min(spp->lrx - 1,		spp->src->width  - 1);		// next pixel left of upper-right (which is actually lower-right, but on this upper line)
		spp->middleStartV	= (s32)min(spp->uly + 1,		spp->src->height - 1);		// next pixel right of left-side pixels
		spp->middleFinishV	= (s32)min(spp->lry - 1,		spp->src->height - 1);		// next pixel left of right-side pixels

		// Compute how far over the right-most pixel is, and how far down the bottom-most pixel is
		spp->rightDelta		= (s32)(spp->lrx - spp->ulx);
		spp->bottomDelta	= (s32)(spp->lry - spp->uly);

		// Find out where this upper-left pixel falls
		if (!spp->spans2H)		spp->widthLeft	=      spp->lrx          - spp->ulx;		// Entire width is within this one pixel, so it's only a portion of the pixel's overall width
		else					spp->widthLeft	= (f64)spp->middleStartH - spp->ulx;		// It spans from where it is to the right of the pixel square

		if (!spp->spans2V)		spp->height		=      spp->lry          - spp->uly;		// It's entire height is within this one pixel, so it's only a portion of the pixel's overall height
		else					spp->height		= (f64)spp->middleStartV - spp->uly;		// It spans from where it is to the bottom of the pixel square

		//////////
		// The following functions (if called) update the number of pieces of picture data to add to the output
		//////
			//////////
			// 1 - upper-left (always, spans at most one pixel)
			//////
				// Compute the area for this pixel component
				spp->area = spp->widthLeft * spp->height;
				// Store the colors for this point
				iioss_getSpannedPixelComputationAppend(spp, 0, 0, spp->area);


			//////////
			// 2 - upper-middle (optional, spans at most multiple partial or full pixels, but only if 1, 2 and 3 exist)
			//////
				if (spp->spans3H)
				{
					s32 lnX, lnPixel;
					// For every middle pixel, apply these values
					for (lnX = 1, lnPixel = spp->middleStartH; lnPixel <= spp->middleFinishH; lnX++, lnPixel++)
						iioss_getSpannedPixelComputationAppend(spp, lnX, 0, spp->height);
				}


			//////////
			// 3 - upper-right (optional, spans at most one pixel, but only if 1 and 3 exist (as 1 and 2))
			//////
				if (spp->spans2H)
				{
					// Find out where this upper-left pixel falls
					spp->widthRight	= spp->lrx - (f64)spp->right;		// It spans from the start of the right-most pixel to wherever it falls therein
					// Compute the area for this pixel component
					spp->area = spp->widthRight * spp->height;
					// Store this pixel data
					iioss_getSpannedPixelComputationAppend(spp, spp->rightDelta, 0, spp->area);
				}


			//////////
			// 4 - middle-left (optional, spans at most multiple partial or full pixels)
			//////
				if (spp->spans3V)
				{
					s32 lnY, lnPixelY;
					// Repeat for each middle pixel
					for (lnY = 1, lnPixelY = spp->middleStartV; lnPixelY <= spp->middleFinishV; lnY++, lnPixelY++)
						iioss_getSpannedPixelComputationAppend(spp, 0, lnY, spp->widthLeft);
				}


			//////////
			// 5 - middle-middle (optional, can span multiple partial or full pixels)
			//////
				if (spp->spans3V && spp->spans3H)
				{
					s32 lnX, lnY, lnPixelY, lnPixelX;
					// Iterate for each pixel row vertically
					for (lnY = 1, lnPixelY = spp->middleStartV; lnPixelY <= spp->middleFinishV; lnY++, lnPixelY++)
					{
						// And each individual pixel horizontally
						for (lnX = 1, lnPixelX = spp->middleStartH; lnPixelX <= spp->middleFinishH; lnX++, lnPixelX++)
						{
							iioss_getSpannedPixelComputationAppend(spp, lnX, lnY, 1.0f);
						}
					}
				}


			//////////
			// 6 - middle-right (optional, spans at most multiple partial or full pixels)
			//////
				if (spp->spans3V && spp->spans2H)
				{
					s32 lnY, lnPixelY;
					// Repeat for each middle pixel
					for (lnY = 1, lnPixelY = spp->middleStartV; lnPixelY <= spp->middleFinishV; lnY++, lnPixelY++)
						iioss_getSpannedPixelComputationAppend(spp, spp->rightDelta, lnY, spp->widthRight);
				}


			//////////
			// 7 - lower-left (optional, spans at most one pixel)
			//////
				if (spp->spans2V)
				{
					// Compute the area
					spp->height	= spp->lry - (f64)((s32)spp->lry);
					spp->area	= spp->widthLeft * spp->height;
					iioss_getSpannedPixelComputationAppend(spp, 0, spp->bottomDelta, spp->area);
				}


			//////////
			// 8 - lower-middle (optional, spans at most multiple partial or full pixels)
			//////
				if (spp->spans2V && spp->spans3H)
				{
					s32 lnX, lnPixelX;
					// For every middle pixel, apply these values
					for (lnX = 1, lnPixelX = spp->middleStartH; lnPixelX <= spp->middleFinishH; lnX++, lnPixelX++)
						iioss_getSpannedPixelComputationAppend(spp, lnX, spp->bottomDelta, spp->height);
				}


			//////////
			// 9 - lower-right (optional, spans at most one pixel)
			//////
				if (spp->spans2V && spp->spans2H)
				{
					// Compute the area
					spp->area = spp->widthRight * spp->height;
					iioss_getSpannedPixelComputationAppend(spp, spp->rightDelta, spp->bottomDelta, spp->area);
				}
	}




//////////
//
// Store the pixel for this as another step for the addition and subtraction of pixel information
//
//////
	void iioss_getSpannedPixelComputationAppend(_isSSpannedPixelProcessing* spp, s32 tnDeltaX, s32 tnDeltaY, f64 tfMultiplier)
	{
		SScaleCompute*	lsc;
		SScaleCompute**	lscLast;

		// Make sure there's some valid data here (something that a human eye could see)
		if (tfMultiplier > 0.00001f)
		{
			// See where we're adding
			if (spp->lastSc)
			{
				// We're appending to the existing chain
				lscLast = (SScaleCompute**)&spp->lastSc->next;

			} else {
				// This is the first entry
				lscLast = &spp->sm->firstScale;
			}

			// Create the new entry
			lsc = (SScaleCompute*)malloc(sizeof(SScaleCompute));

			// Did it create okay?
			if (lsc)
			{
				// Initialize it to emptiness
				memset(lsc, 0, sizeof(SScaleCompute));

				// Set this item's properties
				*lscLast				= lsc;								// Update the back-link
				spp->lastSc				= lsc;								// Update the last scale

				// Store information specific to this part of the computation
				// Compute the relative offset into the source canvas (unscaled canvas)
				lsc->sbgraOffsetSrc		= spp->offsetSrc;

				// If there is a Y delta, apply it
				if (tnDeltaY != 0)
					lsc->sbgraOffsetSrc	+= (tnDeltaY * spp->rowWidth);

				// If there is an X delta, apply it
				if (tnDeltaX != 0)
					lsc->sbgraOffsetSrc	+= (tnDeltaX * sizeof(SBGRA));

				// Store the destination offset and multiplier for this portion of the pixel
				lsc->sbgraOffsetDst		= spp->offsetDst;					// Offset into the destination canvas (scaled canvas)
				lsc->multiplier			= tfMultiplier / spp->areaSpanned;	// Multiplier for this pixel portion to add in to the total for that spanned pixel
			}
		}
	}




//////////
//
// Integers between means which maximum integer is touched?
// Basically, chopping off decimals reveals the range, such that values of
// 1.001 and 2.999 only touch integers 1 and 2, even though with rounding
// they would go from 1 to 3.  Their numerical roots are in only integers
// 1 and 2.
//
//////
	u32 ioss_getIntegersBetween(f64 p1, f64 p2)
	{
		f64 v1, v2;


		// Get the lower integers
		v1 = floor(min(p1,p2));
		v2 = floor(max(p1,p2));

		// Indicate the number between
		return((u32)(v2 - v1));
	}




//////////
//
// Called to set the status of the SFindFile
//
//////
	void ioss_setFindFileStatus(SFindFile* tsFileInfo, WIN32_FIND_DATAA* twfd)
	{
		s8 buffer[_MAX_PATH];


		// Make sure the environment is sane
		if (tsFileInfo && twfd)
		{
			// Mark all attributes
			tsFileInfo->isDirectory				= ((twfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)		? true : false);
			tsFileInfo->isFile					= !tsFileInfo->isDirectory;
			tsFileInfo->isMarkedArchive			= ((twfd->dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)		? true : false);
			tsFileInfo->isMarkedCompressed		= ((twfd->dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED)		? true : false);
			tsFileInfo->isMarkedEncrypted		= ((twfd->dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED)		? true : false);
			tsFileInfo->isMarkedHidden			= ((twfd->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)			? true : false);
			tsFileInfo->isMarkedOffline			= ((twfd->dwFileAttributes & FILE_ATTRIBUTE_OFFLINE)		? true : false);
			tsFileInfo->isMarkedReadOnly		= ((twfd->dwFileAttributes & FILE_ATTRIBUTE_READONLY)		? true : false);
			tsFileInfo->isMarkedSystem			= ((twfd->dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)			? true : false);
			tsFileInfo->isMarkedTemporary		= ((twfd->dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)		? true : false);
			tsFileInfo->isMarkedVirtual			= ((twfd->dwFileAttributes & FILE_ATTRIBUTE_VIRTUAL)		? true : false);

			// Set the normal attribute based on potentially unusable, or generally unusual, conditions
			if (tsFileInfo->isDirectory || tsFileInfo->isMarkedHidden || tsFileInfo->isMarkedOffline || tsFileInfo->isMarkedReadOnly || tsFileInfo->isMarkedSystem || tsFileInfo->isMarkedTemporary || tsFileInfo->isMarkedVirtual)
				tsFileInfo->isNormal = false;
			else
				tsFileInfo->isNormal = true;
			
			//////////
			// Copy the filenames
			//////
				// Primary filename
				memset(buffer, 0, sizeof(buffer));
				if (tsFileInfo->pathnameOfSearch.data._u8)
					oss_memcpy(buffer, tsFileInfo->pathnameOfSearch.data._s8, tsFileInfo->pathnameOfSearch.length);

				oss_memcpy(buffer + oss_strlen(_csu8p(buffer)), twfd->cFileName, oss_strlen(_csu8p(twfd->cFileName)));
				oss_datumSet(&tsFileInfo->file, (u8*)buffer, oss_strlen(_csu8p(buffer)), true);

				// Alternate filename
				memset(buffer, 0, sizeof(buffer));
				if (tsFileInfo->pathnameOfSearch.data._s8)
					oss_memcpy(buffer, tsFileInfo->pathnameOfSearch.data._s8, tsFileInfo->pathnameOfSearch.length);

				memcpy(buffer + strlen(buffer), twfd->cAlternateFileName, strlen(twfd->cAlternateFileName));
				oss_datumSet(&tsFileInfo->file2, (u8*)buffer, oss_strlen(_csu8p(buffer)), true);

			// Store the file size
			tsFileInfo->size		= ((u64)twfd->nFileSizeHigh < 32) | ((u64)twfd->nFileSizeLow);

			// Store the dates
			ioss_convertFileTimeToSDateTime(&tsFileInfo->created,	&twfd->ftCreationTime);
			ioss_convertFileTimeToSDateTime(&tsFileInfo->accessed,	&twfd->ftLastAccessTime);
			ioss_convertFileTimeToSDateTime(&tsFileInfo->updated,	&twfd->ftLastWriteTime);
		}
	}




//////////
//
// Called to convert the indicated filetime to a standard date and time
//
//////
	void ioss_convertFileTimeToSDateTime(SFileTime* tsDateTime, FILETIME* tsFiletime)
	{
		FILETIME	lft;
		SYSTEMTIME	lst;


		// Make sure our environment is sane
		if (tsDateTime && tsFiletime)
		{
			FileTimeToLocalFileTime(tsFiletime, &lft);		// Convert filetime format to local filetime
			FileTimeToSystemTime(&lft, &lst);				// Convert local filetime to system time

			// Convert from file time to standard time
			tsDateTime->year			=     lst.wYear;
			tsDateTime->month			= (u8)lst.wMonth;
			tsDateTime->day				= (u8)lst.wDay;
			tsDateTime->dayOfWeek		= (u8)lst.wDayOfWeek + 1;		// 1=Sunday, 7=Saturday
			tsDateTime->hour			= (u8)lst.wHour;
			tsDateTime->minute			= (u8)lst.wMinute;
			tsDateTime->second			= (u8)lst.wSecond;
			tsDateTime->milliseconds	= ((u32)lst.wHour * 3600000) + ((u32)lst.wMinute * 60000) + (u32)lst.wMilliseconds;

			// Store the common epochs
			tsDateTime->epoch1601		= (((u64)tsFiletime->dwHighDateTime << 32) | (u64)tsFiletime->dwLowDateTime);
			tsDateTime->epoch1970		= (u32)((tsDateTime->epoch1601 / 10000000/*ticks per second*/) - 11644473600/*seconds from 1601 to unix epoch*/);
		}
	}




//////////
//
// Called to delete all nodes 
//
//////
	void ioss_ll4_deleteChainAllNodes(SLL4Callback* cb, SLL4* node)
	{
		u32			lnI;
		SStartEnd	nodeList;


// TODO:  UNTESTED CODE
		// Make sure our environment is sane
		if (node)
		{
			//////////
			// Initialize a buffer for all the of the nodes (we traverse to get a unique node list before deleting them all)
			//////
				memset(&nodeList, 0, sizeof(nodeList));
				oss_SEChain_allocateAdditionalMasterSlots(&nodeList, _COMMON_START_END_BIG_BLOCK_SIZE);


			//////////
			// Build the list from the node mesh
			//////
				iioss_ll4_deleteChainAllNodes(&nodeList, node,			_LL4_EAST);		// Conduct self plus everything east
				iioss_ll4_deleteChainAllNodes(&nodeList, node->west,	_LL4_WEST);		// Conduct everything west
				iioss_ll4_deleteChainAllNodes(&nodeList, node->north,	_LL4_NORTH);	// Conduct everything north
				iioss_ll4_deleteChainAllNodes(&nodeList, node->south,	_LL4_SOUTH);	// Conduct everything south


			//////////
			// Now we have our list of items to delete
			//////
				for (lnI = 0; lnI < nodeList.masterCount; lnI++)
				{
					//////////
					// When we're done, we're done
					//////
						if (!nodeList.ptr[lnI])
							break;	// We're done


					//////////
					// Callback if need be
					//////
						if (cb && cb->_func)
						{
							cb->node = node;
							cb->funcVoid(cb);
						}


					//////////
					// Free this node, which also orphanizes it if need be
					//////
						oss_ll4_delete((SLL4*)nodeList.ptr[lnI]);
				}


			//////////
			// Delete the list of nodes, which is no longer required
			//////
				oss_SEChain_delete(&nodeList, 0, 0, false);
		}
	}




//////////
//
// We scan each pointer to see if it exists in the already compiled list
//
//////
	void iioss_ll4_deleteChainAllNodes(SStartEnd* nodeList, SLL4* node, u32 tnDirection)
	{
		u32		lnI;
		SLL4*	nodeNext;


// TODO:  UNTESTED CODE
		// Iterate through every node in the indicated direction
		while (node)
		{
			//////////
			// See if this pointer is already known
			//////
				for (lnI = 0; lnI < nodeList->masterCount; lnI++)
				{
					// Are we out of slots to test?
					if (!nodeList->ptr[lnI])
						break;	// Yes, we're done searching for slots (the new pointer can go here)

					// See if this is a match
					if (nodeList->ptr[lnI] == node)
						return;	// Yes, we're done with this direction
				}
				// When we get here, we know it wasn't found and we need to add it


			//////////
			// Is there enough space?
			//////
				if (lnI == nodeList->masterCount)
					oss_SEChain_allocateAdditionalMasterSlots(nodeList, _COMMON_START_END_BIG_BLOCK_SIZE);		// No, allocate more space


			//////////
			// Append this data to this slot
			//////
				nodeList->ptr[lnI] = node;


			//////////
			// Grab the next node
			/////
				switch (tnDirection)
				{
					case _LL4_NORTH:
						nodeNext = node->north;
						// Spawn off a search easterly, and westerly
						iioss_ll4_deleteChainAllNodes(nodeList, node->east,		_LL4_EAST);
						iioss_ll4_deleteChainAllNodes(nodeList, node->west,		_LL4_WEST);
						break;

					case _LL4_SOUTH:
						nodeNext = node->south;
						// Spawn off a search easterly, and westerly
						iioss_ll4_deleteChainAllNodes(nodeList, node->east,		_LL4_EAST);
						iioss_ll4_deleteChainAllNodes(nodeList, node->west,		_LL4_WEST);
						break;

					case _LL4_WEST:
						nodeNext = node->west;
						// Spawn off a search northerly, and southerly
						iioss_ll4_deleteChainAllNodes(nodeList, node->north,	_LL4_NORTH);
						iioss_ll4_deleteChainAllNodes(nodeList, node->south,	_LL4_SOUTH);
						break;

					case _LL4_EAST:
						nodeNext = node->east;
						// Spawn off a search northerly, and southerly
						iioss_ll4_deleteChainAllNodes(nodeList, node->north,	_LL4_NORTH);
						iioss_ll4_deleteChainAllNodes(nodeList, node->south,	_LL4_SOUTH);
						break;

					default:
						// Invalid direction, abort
						return;
				}


			//////////
			// Move to the next node
			/////
				node = nodeNext;
		}
	}




//////////
//
// Called to find the first match from the indicated location.
//
// Note:  *x must be NULL on the first call.  If x is populated, and *x is not NULL, it is assumed
//        to have been populated by a prior call to iioss_bxmlFindFirst() and is reused.
//
// Note:  Use oss_free(x) to release the memory when it's no longer needed.
//
//////
	bool iioss_bxmlFindFirst(SBxml* bxmlRoot, SBxml** bxmlNodeFound, SBxmla** bxmlaAttributeFound, SDatum* tsWildcard, bool tlTraverseChildren, bool tlSearchAttributes, void** x)
	{
		_isSBxmlFind*	bxmlFind;
		_isSBxmlFind	xTemp;


		//////////
		// Create our x structure (if they want one)
		//////
			if (x)
			{
				// They want one
				if (!*x)
				{
					// It hasn't been populated yet
					bxmlFind = (_isSBxmlFind*)oss_alloc(sizeof(_isSBxmlFind), true);	// Initially set everything to NULL
					if (!bxmlFind)
					{
						// Failure allocating memory
						return(false);
					}
					// Store the pointer for the user's use
					*x = bxmlFind;

				} else {
					// Grab the existing pointer
					bxmlFind = (_isSBxmlFind*)*x;
				}
				// Initialize the memory block to empty
				memset(bxmlFind, 0, sizeof(_isSBxmlFind));

			} else {
				// We will create a fake x for the purpose of a one-shot find
				memset(&xTemp, 0, sizeof(_isSBxmlFind));
				bxmlFind = &xTemp;
			}


		//////////
		// Populate the initial information, so oss_bxmlFindcontinue() knows how to proceed, and where to stop
		//////
			bxmlFind->bxmlRoot				= bxmlRoot;
			bxmlFind->bxmlRootParent		= (SBxml*)bxmlRoot->ll4.parent;

			bxmlFind->traverseChildren		= tlTraverseChildren;
			bxmlFind->searchAttributes		= tlSearchAttributes;

			bxmlFind->bxmlNodeFound			= bxmlNodeFound;
			bxmlFind->bxmlaAttributeFound	= bxmlaAttributeFound;
			bxmlFind->wildcard				= tsWildcard;


		//////////
		// Call the function
		//////
			if (x)		return(iioss_bxmlFindContinue(*x));					// Call the function and return the result
			else		return(iioss_bxmlFindContinue((void*)&xTemp));		// Call the function using our xTemp, and return the result
	}




//////////
//
// Called to continue a prior call to oss_bxmlFindFirst() and the x that was populated there.
//
// Note:  The pointers for bxmlNodeFound and bxmlaAttributeFound will be reused and populated based
//        on the results of this find continue.
//
// Note:  The previous tsWildcard SDatum must remain viable for this to continue.  The wildcard
//        values used in tsWildcard can be updated during the middle of the search, but the search
//        will only continue forward from the last find unless oss_bxmlFindFirst() is called.
//
//////
	bool iioss_bxmlFindContinue(void* x)
	{
		_isSBxmlFind*	bxmlFind;


		// Grab our pointer
		bxmlFind = (_isSBxmlFind*)x;


		//////////
		// What is our status?
		//////
				 if (bxmlFind->lastFindOnNode)			goto continueToAttributes;				// Last find was this node, so we continue on beyond that node
			else if (bxmlFind->lastFindOnAttribute)		goto continueToNextAttribute;			// Last find was this attribute, so we continue on to the next attribute
			else										bxmlFind->bxml = bxmlFind->bxmlRoot;	// There was no last find.  So we start at the beginning.


		///////////
		// Search for the first match
		//////
			while (bxmlFind->bxml)
			{
				//////////
				// Is this node name a match?
				//////
					if (bxmlFind->bxmlNodeFound && oss_wildcardMatch(_csu8p(bxmlFind->bxml->_name.data._u8), _csu8p(bxmlFind->wildcard->data._u8), false) == 0)
					{
						// Yes, store the found information node
															*bxmlFind->bxmlNodeFound		= bxmlFind->bxml;	// Store the found node
						if (bxmlFind->bxmlaAttributeFound)	*bxmlFind->bxmlaAttributeFound	= NULL;				// Indicate the attribute was not found

						// Update user's x for subsequent calls to oss_bxmlFindContinue()
						bxmlFind->lastFindOnNode		= true;		// Was found on a node, not an attribute
						bxmlFind->lastFindOnAttribute	= false;	// Was found on a node, not an attribute

						// Indicate success
						return(true);
					}
					// If we get here, no match on node name


				//////////
				// Does it match on any of the attributes?
				//////
continueToAttributes:
					if (bxmlFind->bxmlaAttributeFound)
					{
						// Iterate through any attributes
						if (!bxmlFind->bxml && bxmlFind->bxmla)
							bxmlFind->bxml = bxmlFind->bxmla->_parent;		// Update the bxml by the current attribute's parent

						// Make sure this attribute still has a parent
						if (!bxmlFind->bxml)
							break;		// Nope, we're done with this search

						for ( ; bxmlFind->_mlIterator < bxmlFind->bxml->_attributes.masterCount; )
						{
							// Grab this attribute
							bxmlFind->_ml = bxmlFind->bxml->_attributes.master[bxmlFind->_mlIterator];

							// Is this master slot used?
							if (bxmlFind->_ml && bxmlFind->_ml->used)
							{
								// Grab the master list's associated pointer, which is the attribute
								bxmlFind->bxmla = (SBxmla*)bxmlFind->_ml->ptr;

								// Does this attribute name match
								if (bxmlFind->bxmla && oss_wildcardMatch(_csu8p(bxmlFind->bxmla->_name.data._u8), _csu8p(bxmlFind->wildcard->data._u8), false) == 0)
								{
									// Yes, store the found information node
																	*bxmlFind->bxmlaAttributeFound	= bxmlFind->bxmla;	// Store the found attribute
									if (bxmlFind->bxmlNodeFound)	*bxmlFind->bxmlNodeFound		= NULL;				// Indicate the node was not found


									// Update user's x for subsequent calls to oss_bxmlFindContinue()
									bxmlFind->lastFindOnNode		= false;	// Was found on an attribute, not a node
									bxmlFind->lastFindOnAttribute	= true;		// Was found on an attribute, not a node

									// Indicate success
									return(true);
								}
							}
continueToNextAttribute:
							// Move to next entry
							++bxmlFind->_mlIterator;
						}
					}


				//////////
				// See if they are any children?
				//////
					if (bxmlFind->traverseChildren && bxmlFind->bxml->ll4.firstChild)
					{
						// Search child nodes
						bxmlFind->bxml			= (SBxml*)bxmlFind->bxml->ll4.firstChild;
						bxmlFind->_mlIterator	= 0;

					} else {
						// Iterate until we find a sibling or reach the end of the parentage
						while (1)
						{
							if (bxmlFind->bxml->ll4.next)
							{
								// Continue on to the next sibling
								bxmlFind->bxml			= (SBxml*)bxmlFind->bxml->ll4.next;
								bxmlFind->_mlIterator	= 0;
								break;

							} else {
								// We're done at this level, can we go back up one?
								if (!bxmlFind->bxml->ll4.parent || (SBxml*)bxmlFind->bxml->ll4.parent == bxmlFind->bxmlRootParent)
								{
									// No, if we go up another level we'll exit the bxml, or we'll be at the root's parent
									// Yes, no more finds
									if (bxmlFind->bxmlNodeFound)			*bxmlFind->bxmlNodeFound		= NULL;		// Not found on a node
									if (bxmlFind->bxmlaAttributeFound)		*bxmlFind->bxmlaAttributeFound	= NULL;		// Not found on an attribute
									return(false);

								} else {
									// Go back up to the parent
									bxmlFind->bxml = (SBxml*)bxmlFind->bxml->ll4.parent;
									// And by looping, then to the parent's next sibling
								}
							}
						}
					}
			}
			// When we get here, no additional find was made with all the nodes at this level


		//////////
		// Indicate failure
		//////
			return(false);
	}




//////////
//
// Called to find the first data match from the indicated location.
//
// Note:  *x must be NULL on the first call.  If x is populated, and *x is not NULL, it is assumed
//        to have been populated by a prior call to iioss_bxmlDataFindFirst() and is reused.
//
// Note:  Use oss_free(x) to release the memory when it's no longer needed.
//
//////
	bool iioss_bxmlDataFindFirst(SBxml* bxmlRoot, SBxmla** bxmlaAttributeFound, SDatum* tsWildcard, bool tlTraverseChildren, void** x)
	{
		_isSBxmlFind*	bxmlFind;
		_isSBxmlFind	xTemp;


		//////////
		// Create our x structure (if they want one)
		//////
			if (x)
			{
				// They want one
				if (!*x)
				{
					// It hasn't been populated yet
					bxmlFind = (_isSBxmlFind*)oss_alloc(sizeof(_isSBxmlFind), true);	// Initially set everything to NULL
					if (!bxmlFind)
					{
						// Failure allocating memory
						return(false);
					}
					// Store the pointer for the user's use
					*x = bxmlFind;
				}
				//else it's already been created, but will be re-populated below

			} else {
				// We will create a fake x for the purpose of a one-shot find
				memset(&xTemp, 0, sizeof(_isSBxmlFind));
				bxmlFind = &xTemp;
			}


		//////////
		// Populate the initial information, so oss_bxmlFindcontinue() knows how to proceed, and where to stop
		//////
			bxmlFind->bxmlRoot				= bxmlRoot;
			bxmlFind->bxmlRootParent		= (SBxml*)bxmlRoot->ll4.parent;
			bxmlFind->bxml					= NULL;
			bxmlFind->bxmla					= NULL;

			bxmlFind->traverseChildren		= tlTraverseChildren;

			bxmlFind->bxmlaAttributeFound	= bxmlaAttributeFound;
			bxmlFind->wildcard				= tsWildcard;


		//////////
		// Call the function
		//////
			if (x)		return(iioss_bxmlDataFindContinue(*x));					// Call the function and return the result
			else		return(iioss_bxmlDataFindContinue((void*)&xTemp));		// Call the function using our xTemp, and return the result
	}




//////////
//
// Called to continue a prior call to oss_bxmlFindFirst() and the x that was populated there.
//
// Note:  The pointers for bxmlNodeFound and bxmlaAttributeFound will be reused and populated based
//        on the results of this find continue.
//
// Note:  The previous tsWildcard SDatum must remain viable for this to continue.  The wildcard
//        values used in tsWildcard can be updated during the middle of the search, but the search
//        will only continue forward from the last find unless oss_bxmlFindFirst() is called.
//
//////
	bool iioss_bxmlDataFindContinue(void* x)
	{
		_isSBxmlFind* bxmlFind;


		// Grab our pointer
		bxmlFind = (_isSBxmlFind*)x;


		//////////
		// What is our status?
		//////
			if (bxmlFind->lastFindOnAttribute)		goto continueToNextAttribute;			// Last find was this attribute, so we continue on to the next attribute
			else									bxmlFind->bxml = bxmlFind->bxmlRoot;	// There was no last find.  So we start at the beginning.


		///////////
		// Search for the first match
		//////
			while (bxmlFind->bxml)
			{
				//////////
				// Does it match on any of the attribute's data?
				//////
					// Iterate through any attributes
					bxmlFind->_ml = bxmlFind->bxml->_attributes.root;
					while (bxmlFind->_ml)
					{
						// Is this master slot used?
						if (bxmlFind->_ml->used)
						{
							// Grab the master list's associated pointer, which is the attribute
							bxmlFind->bxmla = (SBxmla*)bxmlFind->_ml->ptr;

							// Does this attribute name match
							if (bxmlFind->bxmla && oss_wildcardMatch(_csu8p(bxmlFind->bxmla->_data.datum.data._u8), _csu8p(bxmlFind->wildcard->data._u8), false) == 0)
							{
								// Yes, store the found information node
								*bxmlFind->bxmlaAttributeFound	= bxmlFind->bxmla;	// Store the found attribute
								bxmlFind->lastFindOnAttribute	= true;				// Was found on an attribute

								// Indicate success
								return(true);
							}
						}

continueToNextAttribute:
						// Move to next record
						bxmlFind->_ml = (SMasterList*)bxmlFind->_ml->ll.next;
					}


				//////////
				// See if they are any children?
				//////
					if (bxmlFind->traverseChildren && bxmlFind->bxml->ll4.firstChild)
					{
						// Search child nodes
						bxmlFind->bxml = (SBxml*)bxmlFind->bxml->ll4.firstChild;

					} else {
						// Iterate until we find a sibling or reach the end of the parentage
						while (1)
						{
							if (bxmlFind->bxml->ll4.next)
							{
								// Continue on to the next sibling
								bxmlFind->bxml = (SBxml*)bxmlFind->bxml->ll4.next;
								break;

							} else {
								// We're done at this level, can we go back up one?
								if (!bxmlFind->bxml->ll4.parent || (SBxml*)bxmlFind->bxml->ll4.parent == bxmlFind->bxmlRootParent)
								{
									// No, if we go up another level we'll exit the bxml, or we'll be at the root's parent
									// Yes, no more finds
									*bxmlFind->bxmlaAttributeFound = NULL;		// Not found on an attribute
									return(false);

								} else {
									// Go back up to the parent
									bxmlFind->bxml = (SBxml*)bxmlFind->bxml->ll4.parent;
									// And by looping, then to the parent's next sibling
								}
							}
						}
					}
			}
			// When we get here, no additional find was made with all the nodes at this level


		//////////
		// Indicate failure
		//////
			return(false);
	}




//////////
//
// Called to search for the attribute and store it optionally if indicated
//
//////
	SBxmla* iioss_bxmlFindAttribute(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance)
	{
		SBxmla* lbxmla;


		// Find and store the attribute
		lbxmla = oss_bxmlFindAttribute(bxml, tsWildcardSearch, tnInstance);
		if (bxmla)
			*bxmla = lbxmla;

		// Indicate our success or failure
		return(lbxmla);
	}




//////////
//
// Create a new screen in the master list
//
//////
	SScreen* ioss_createScreen(u64 tnAssociatedId)
	{
		SScreen* ls;


		// Lock the screen access semaphore
		oss_lockSemaphore(gsemScreenAccess);

		// Create the canvas
		ls = (SScreen*)oss_SEChain_append(&gseRootScreen, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SScreen), 1, NULL);
		if (ls)
		{
			// Store the associated id
			ls->associatedId	= tnAssociatedId;

			// Create this screen's refresh semaphore
			ls->semRefresh		= oss_createSemaphore();
		}

		// Unlock the screen access semaphore
		oss_unlockSemaphore(gsemScreenAccess);

		// Indicate our status
		return(ls);
	}




//////////
//
// Create a new canvas in the master list
//
//////
	SCanvas* ioss_createCanvas(u64 tnAssociatedId, u32 tnWidth, u32 tnHeight, SBGRA tnBackColor)
	{
		SCanvas*	lc;


		// Lock the canvas access semaphore
		oss_lockSemaphore(gsemCanvasAccess);

		// Create the canvas
		lc = (SCanvas*)oss_SEChain_append(&gseRootCanvas, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SCanvas), _COMMON_START_END_BLOCK_SIZE, NULL);

		// If it's valid, update it
		if (lc)
		{
			// Store any associated information
			lc->associatedId	= tnAssociatedId;

			// Store the properties
			lc->width			= tnWidth;													// width
			lc->height			= tnHeight;													// height
			lc->backColor		= tnBackColor;												// If transparency, we will use this default color

			// Create this canvas's refresh semaphore
			lc->semRefresh		= oss_createSemaphore();

			// Initialize the canvas buffers
			lc->bd				= (SBGRA*)malloc(tnHeight * tnWidth * 4);					// buffer data
			lc->bda				= (SBGRA*)malloc(tnHeight * tnWidth * 4);					// buffer accumulator data (for building child items onto a canvas before copying and using this canvas above)
			lc->bd_vvmoss		= oss_systemCreateBitmap(tnWidth, tnHeight);				// Used primarily for rendering system fonts

			// Initialize it with the default background color
			if (lc->bd)			oss_memset4((u32*)lc->bd,  oss_swapEndian(oss_RGBA2BGRA(tnBackColor.color)), tnHeight * tnWidth);	// Initialize bd to the indicated color
			if (lc->bda)		oss_memset4((u32*)lc->bda, oss_swapEndian(oss_RGBA2BGRA(tnBackColor.color)), tnHeight * tnWidth);	// Initialize bda to the indicated color
		}

		// Unlock the canvas access semaphore
		oss_unlockSemaphore(gsemCanvasAccess);

		// Indicate our status
		return(lc);
	}




//////////
//
// Create a region object.  Regions are areas which can respond to keyboard and mouse
// events, and can be an optional tab stop.
//
//////
	SRegion* ioss_createRegion(u64 tnAssociatedId, SRegionState* tsState, u32 tnType, f32 ulx, f32 uly, f32 lrx, f32 lry, SCallbacks* callback, SStartEnd* events)
	{
		SRegion*			lr;
		SStartEndCallback	cb;


		// Lock the canvas access semaphore
		oss_lockSemaphore(gsemRegionAccess);

		// Create the canvas
		lr = (SRegion*)oss_SEChain_append(&gseRootRegion, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SRegion), _COMMON_START_END_BLOCK_SIZE, NULL);
		if (lr)
		{
			//////////
			// Standard initialization
			//////
				memset(lr, 0, sizeof(SRegion));
				lr->associatedId	= tnAssociatedId;					// Store any associated information
				lr->semRefresh		= oss_createSemaphore();			// Create this region's refresh semaphore
				lr->x				= ulx;
				lr->y				= uly;
				lr->width			= lrx - ulx;						// Width of this region
				lr->height			= lry - uly;						// Height of this region
				lr->type			= tnType;							// type of region (see _VVM_REGION_* constants in common_vvm.h)

			//////////
			// Copy state information
			//////
				if (tsState)
				{
					// Copy the indicated state
					memcpy(&lr->state, tsState, sizeof(SRegionState));

				} else {
					// Set the state to its default values
					lr->state.isActive		= true;
					lr->state.isVisible		= true;
					lr->state.hasFocus		= false;
					lr->state.tabOrder		= 0;
					lr->state.useCallbacks	= (callback != NULL);
				}


			//////////
			// Copy the callback definitions if specified
			//////
				if (callback)
					memcpy(&lr->callback, callback, sizeof(SCallbacks));


			//////////
			// Copy the events if specified
			//////
				if (events)
				{
					cb._func	= (u64)iioss_createRegionAppendEventsCallback;
					cb.extra	= (u64)lr;
					oss_SEChain_iterateThroughForCallback(events, &cb);
				}
		}

		// Unlock the canvas access semaphore
		oss_unlockSemaphore(gsemRegionAccess);

		// Indicate our status
		return(lr);
	}




//////////
//
// We use cb->extra for the total pixels drawn
//
//////
	void ioss_regionRefreshCallback(SStartEndCallback* cb)
	{
		// Process this region
		oss_regionRefresh(cb->ptrRegion, cb->ex1PtrRegion);
	}




//////////
//
// Called to draw some text in the indicated font onto the indicated dib bitmap
//
// Note:  tnSystemFont and tnSystemBitmap are _isWSystem* structures
//
//////
	u64 ioss_drawText(s8* tcText, u32 tnTextLength, s32 ulx, s32 uly, s32 lrx, s32 lry, SBGRA foreground, SBGRA background, u64 tnSystemFont, u64 tnSystemBitmap)
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
// This function draws fixed point text onto the indicated canvas using the specified font,
// colors, text, etc.  These facilities will look identically regardless of the OSS font that
// could be used by the ioss_drawText() function.
//
//////
	u64 ioss_drawFixedPoint(SCanvas* tc, SBGRA* bd, u32 fontWidth, u32 fontHeight, s32 ulx, s32 uly, s8* tcText, u32 tnTextLength, SBGRA foreground, SBGRA background)
	{
		u64		lnPixels;
        s32		lnX, lnY, lnFontWidth, lnFontHeight, lnPixelY, lnSX, lnScalerY, lnScalerX;
		u8		lcThisCharacter, lcRowBits, lcMask, fred, fgrn, fblu, bred, bgrn, bblu;
        u8*		lcFontBase;
        u32		lnCharacterOffset;
		SBGRA*	lrgba;


        // See what font they're using
		lnScalerY	= 1;
		lnScalerX	= 1;
		switch (fontWidth)
		{
			case 8:
				lnFontWidth	= 8;
				break;

			case -16:
				lnFontWidth	= 8;
				lnScalerX	= 2;
				break;

			case -24:
				lnFontWidth	= 8;
				lnScalerX	= 3;
				break;

			case -32:
				lnFontWidth	= 8;
				lnScalerX	= 4;
				break;

			default:
				return -2;
		}

        switch (fontHeight)
        {
			case -12:
				lcFontBase		= (u8*)gxFontBase_8x6;
				lnFontHeight	= 6;
				lnScalerY		= 2;
				break;

			case -18:
				lcFontBase		= (u8*)gxFontBase_8x6;
				lnFontHeight	= 6;
				lnScalerY		= 3;
				break;

            case 6:
                lcFontBase		= (u8*)gxFontBase_8x6;
                lnFontHeight	= 6;
                break;

            case 8:
                lcFontBase		= (u8*)gxFontBase_8x8;
                lnFontHeight	= 8;
                break;

			case -16:
				lcFontBase		= (u8*)gxFontBase_8x8;
				lnFontHeight	= 8;
				lnScalerY		= 2;
				break;

            case 14:
                lcFontBase		= (u8*)gxFontBase_8x14;
                lnFontHeight	= 14;
                break;

			case -28:
				lcFontBase		= (u8*)gxFontBase_8x14;
				lnFontHeight	= 14;
				lnScalerY		= 2;
				break;

			case -42:
				lcFontBase		= (u8*)gxFontBase_8x14;
				lnFontHeight	= 14;
				lnScalerY		= 3;
				break;

			case -56:
				lcFontBase		= (u8*)gxFontBase_8x14;
				lnFontHeight	= 14;
				lnScalerY		= 4;
				break;

            case 16:
                lcFontBase		= (u8*)gxFontBase_8x16;
                lnFontHeight	= 16;
                break;

			case -32:
				lcFontBase		= (u8*)gxFontBase_8x16;
				lnFontHeight	= 16;
				lnScalerY		= 2;
				break;

			case -48:
				lcFontBase		= (u8*)gxFontBase_8x16;
				lnFontHeight	= 16;
				lnScalerY		= 3;
				break;

			case -64:
				lcFontBase		= (u8*)gxFontBase_8x16;
				lnFontHeight	= 16;
				lnScalerY		= 4;
				break;

            default:
				// Invalid parameters
                return -1;
        }

		// Extract the colors
		fred	= foreground.red;
		fgrn	= foreground.grn;
		fblu	= foreground.blu;

		bred	= background.red;
		bgrn	= background.grn;
		bblu	= background.blu;

        // Begin drawing the text
		lnPixels = 0;
        while (tnTextLength > 0)
        {
            // Grab this character
            lcThisCharacter		= *tcText;
            lnCharacterOffset	= (u32)lcThisCharacter * (u32)lnFontHeight;

            // Put it into the tbDst
            for (lnY = 0; lnY < lnFontHeight; lnY++)
            {
				for (lnPixelY = 0; lnPixelY < lnScalerY; lnPixelY++)
				{
					if ((uly + (lnY * lnScalerY) + lnPixelY) < tc->height)
					{
						// Position the pointer for this part of the font's
						lrgba = bd + ((uly + (lnY * lnScalerY) + lnPixelY) * tc->width) + (ulx * lnScalerX);

						// Grab the bits
						lcRowBits = lcFontBase[lnCharacterOffset];
						lcMask = 0x80;

						// Iterate through all of the bits
						for (lnX = 0; lnX < lnFontWidth; lnX++)
						{
							for (lnSX = 0; lnSX < lnScalerX; lnSX++)
							{
								if ((ulx + (lnX * lnScalerX) + lnSX) < tc->width)
								{
									// This character is within the bitmap
									++lnPixels;
									if ((lcRowBits & lcMask) != 0)
									{
										// Foreground bit
										lrgba->red = fred;
										lrgba->grn = fgrn;
										lrgba->blu = fblu;

									} else {
										// Background bit
										lrgba->red = bred;
										lrgba->grn = bgrn;
										lrgba->blu = bblu;
									}
								}
								// Move to the next pixel
								++lrgba;
							}

							// Shift the mask over 1 bit to get to the next pixel
							lcMask >>= 1;
						}
					}
				}

                // Move to the next row of pixels in the font
                ++lnCharacterOffset;
            }

            // Move to next position
            ulx += lnFontWidth;

            // Move to next character
            ++tcText;
            --tnTextLength;
        }
		// Return the number of pixels updated
		return(lnPixels);
	}




//////////
//
// Called to BitBlt a 32-bit RGBA canvas onto another one.
//
// Returns:
//		0		- error
//		other	- Number of rows painted (partial or otherwise)
//
//////
	u64 ioss_bitBltAll(SCanvas* tsDst, bool tlDstIsAccumulatorBuffer, s32 tnX, s32 tnY, SCanvas* tsSrc, bool tlSrcIsAccumulatorBuffer)
	{
		u64			lnRowCount;
		SBGRA*		lrgbaDstRoot;
		SBGRA*		lrgbaSrcRoot;


// OPTIMIZATION:  We can go through here and determine line portions to process to speed this up.
//                This will likely be a heavily called function, and that optimization would be welcomed.  Any takers? :-)
// UNTESTED CODE:  Breakpoint and examine!
		// Make sure the environment is sane
		lnRowCount = 0;
		if (tsDst && tsSrc)
		{
			// See if we're copying from accumulation buffer to (non-accumulation) buffer on the same entry
			if (tsDst == tsSrc && !tlDstIsAccumulatorBuffer && tlSrcIsAccumulatorBuffer)
			{
				// Are the parameters valid for the copy?
				if (tsDst->bd && tsDst->bda)
				{
					// We are doing a copy from accumulation to non-accumulation
					memcpy(tsDst->bd, tsDst->bda, tsDst->height * tsDst->width * sizeof(SBGRA));		// Copy the entire buffer

					// Indicate we copied all of them
					lnRowCount = tsDst->height;
				}

			} else {
				// Find out our source and destination buffers
				lrgbaDstRoot = (tlDstIsAccumulatorBuffer) ? tsDst->bda : tsDst->bd;
				lrgbaSrcRoot = (tlSrcIsAccumulatorBuffer) ? tsSrc->bda : tsSrc->bd;

				// Make sure the pointers are valid
				if (lrgbaDstRoot || lrgbaSrcRoot)
				{
					iioss_bitBltAll_Alpha( lrgbaDstRoot, tsDst, tnX, tnY, lrgbaSrcRoot, tsSrc);				// Use the slower algorithm to blend the the two 
					//iioss_bitBltAll_Opaque(lrgbaDstRoot, tsDst, tnX, tnY, lrgbaSrcRoot, tsSrc);			// Iterate through every row for all pixels to copy
					
					// We always indicate we processed this many rows, even if something wasn't updated
					lnRowCount = tsSrc->height;
				}
			}
		}
		// Indicate our success/failure
		return(lnRowCount);
	}




//////////
//
// Perform an alpha blending from the src canvas to the dst canvas, based on the
// src alpha settings.
//
//////
	void iioss_bitBltAll_Alpha(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 tnX, s32 tnY, SBGRA* trgbaSrcRoot, SCanvas* tsSrc)
	{
		s32			lnY, lnX;
		u8			redd, grnd, blud;
		f32			alp, malp;
		SBGRA*		lrgbad;
		SBGRA*		lrgbas;


// TODO:  this algorithm needs to more properly consider transparency, of the source to destination, along with individual bits within
		// Derive the colors from the back color
		oss_deriveRGBA(tsDst->backColor.color, &redd, &grnd, &blud, &malp);
		alp		= (f32)tsSrc->backColor.alp / 255.0f;
		malp	= 1.0f - alp;


		// Repeat for every row
		for (lnY = tnY; lnY < (s32)tsSrc->height; lnY++)
		{
			// Can we copy this row?
			if (lnY >= 0 && lnY < (s32)tsDst->height)
			{
				// Yes we can, recompute the positions for this line
				lrgbad = trgbaDstRoot + (lnY * tsDst->width);
				lrgbas = trgbaSrcRoot + (lnY * tsSrc->width);

				// Iterate for as many pixels as will fit
				for (lnX = tnX; lnX < (s32)tsSrc->width; lnX++)
				{
					// Can we copy this pixel?
					if (lnX >= 0 && lnX < (s32)tsDst->width)
					{
						// Yes we can each color channel of this pixel
						lrgbad->red	= (u8)(((f32)lrgbas->red * alp) + ((f32)lrgbad->red * malp));
						lrgbad->grn = (u8)(((f32)lrgbas->grn * alp) + ((f32)lrgbad->grn * malp));
						lrgbad->blu = (u8)(((f32)lrgbas->blu * alp) + ((f32)lrgbad->blu * malp));
						lrgbad->alp = 255;
					}

					// Move to the next pixel
					++lrgbad;
					++lrgbas;
				}
			}
		}
	}




//////////
//
// Perform an alpha blending from the src canvas to the dst canvas, based on the
// src alpha settings.
//
//////
	// It is probbaly best NOT to call this function directory, but rather call ioss_bitBltAll()
	void iioss_bitBltAll_Opaque(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 tnX, s32 tnY, SBGRA* trgbaSrcRoot, SCanvas* tsSrc)
	{
		s32			lnY, lnX;
		SBGRA*		lrgbad;
		SBGRA*		lrgbas;


		// Repeat for every row
		for (lnY = tnY; lnY < (s32)tsSrc->height; lnY++)
		{
			// Can we copy this row?
			if (lnY >= 0 && lnY < (s32)tsDst->height)
			{
				// Yes we can, recompute the positions for this line
				lrgbad = trgbaDstRoot + (lnY * tsDst->width);
				lrgbas = trgbaSrcRoot + (lnY * tsSrc->width);

				// Iterate for as many pixels as will fit
				for (lnX = tnX; lnX < (s32)tsSrc->width; lnX++)
				{
					// Can we copy this pixel?
					if (lnX >= 0 && lnX < (s32)tsDst->width)
					{
						// Yes we can each color channel of this pixel
						lrgbad->red	= lrgbas->red;
						lrgbad->grn = lrgbas->grn;
						lrgbad->blu = lrgbas->blu;
						lrgbad->alp = lrgbas->alp;
					}

					// Move to the next pixel
					++lrgbad;
					++lrgbas;
				}
			}
		}
	}




//////////
//
// Called to BitBlt a 32-bit RGBA canvas onto another one, for the section indicated.
// Note:  This function will be slightly slower than the ioss_bitBltAll()
//
// Returns:
//		0		- error
//		other	- Number of rows painted (partial or otherwise)
//
//////
	// It is probbaly best NOT to call this function directory, but rather call ioss_bitBltSection()
	u64 ioss_bitBltSection(SCanvas* tsDst, bool tlDstIsAccumulatorBuffer, s32 dulx, s32 duly, SCanvas* tsSrc, bool tlSrcIsAccumulatorBuffer, s32 sulx, s32 suly, s32 slrx, s32 slry)
	{
		u64			lnRowCount;
		SBGRA*		lrgbaDstRoot;
		SBGRA*		lrgbaSrcRoot;


// OPTIMIZATION:  We can go through here and determine line portions to process to speed this up.
//                This will likely be a heavily called function, and that optimization would be welcomed.  Any takers? :-)
// UNTESTED CODE:  Breakpoint and examine!
		// Make sure the environment is sane
		lnRowCount = 0;
		if (tsDst && tsSrc)
		{
			// See if we're copying from accumulation buffer to (non-accumulation) buffer on the same entry
			if (tsDst == tsSrc && !tlDstIsAccumulatorBuffer && tlSrcIsAccumulatorBuffer)
			{
				// Are the parameters valid for the copy?
				if (tsDst->bd && tsDst->bda)
				{
					// We are doing a copy from accumulation to non-accumulation
					memcpy(tsDst->bd, tsDst->bda, tsDst->height * tsDst->width * sizeof(SBGRA));		// Copy the entire buffer

					// Indicate we copied all of them
					lnRowCount = tsDst->height;
				}

			} else {
				// Find out our source and destination buffers
				lrgbaDstRoot = (tlDstIsAccumulatorBuffer) ? tsDst->bda : tsDst->bd;
				lrgbaSrcRoot = (tlSrcIsAccumulatorBuffer) ? tsSrc->bda : tsSrc->bd;

				// Make sure the pointers are valid
				if (lrgbaDstRoot || lrgbaSrcRoot)
				{
					iioss_bitBltSection_Alpha( lrgbaDstRoot, tsDst, dulx, duly, lrgbaSrcRoot, tsSrc, sulx, suly, slrx, slry);		// Use the slower algorithm to blend the the two 
					//iioss_bitBltSection_Opaque(lrgbaDstRoot, tsDst, dulx, duly, lrgbaSrcRoot, tsSrc, sulx, suly, slrx, slry);		// Iterate through every row for all pixels to copy
					
					// We always indicate we processed this many rows, even if something wasn't updated
					lnRowCount = tsSrc->height;
				}
			}
		}
		// Indicate our success/failure
		return(lnRowCount);
	}




//////////
//
// Perform an alpha blending from the src canvas to the dst canvas, based on the
// src alpha settings, for the section indicated.
//
//////
	void iioss_bitBltSection_Opaque(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 dulx, s32 duly, SBGRA* trgbaSrcRoot, SCanvas* tsSrc, s32 sulx, s32 suly, s32 slrx, s32 slry)
	{
		s32			lnY, lnX, lnThisX, lnThisY, lnWidth, lnHeight;
		u8			redd, grnd, blud;
		f32			alp, malp;
		SBGRA*		lrgbad;
		SBGRA*		lrgbas;


// TODO:  this algorithm needs to more properly consider transparency, of the source to destination, along with individual bits within
		// Derive the colors from the back color
		oss_deriveRGBA(tsDst->backColor.color, &redd, &grnd, &blud, &malp);
		alp		= (f32)tsSrc->backColor.alp / 255.0f;
		malp	= 1.0f - alp;

		// Derive our size for the source rectangular region
		lnWidth		= slrx - sulx;
		lnHeight	= slry - suly;


		//////////
		// Repeat for every row
		//////
			for (	lnY = duly, lnThisY = 0;
					lnY < (s32)tsSrc->height && lnThisY < lnHeight;
					lnY++, lnThisY++	)
			{
				// Can we copy this row?
				if (lnY >= 0 && lnY < (s32)tsDst->height && lnThisY < lnHeight)
				{
					// Yes we can, recompute the positions for this line
					lrgbad = trgbaDstRoot + (lnY              * tsDst->width);
					lrgbas = trgbaSrcRoot + ((lnThisY + suly) * tsSrc->width) + sulx;

					//////////
					// Iterate for as many pixels as will fit
					//////
						for (	lnX = dulx, lnThisX = 0;
								lnX < (s32)tsSrc->width && lnThisX < lnWidth;
								lnX++, lnThisX++	)
						{
							// Can we copy this pixel?
							if (lnX >= 0 && lnX < (s32)tsDst->width && lnThisX < lnWidth)
							{
								// Yes we can each color channel of this pixel
								lrgbad->red	= (u8)(((f32)lrgbas->red * alp) + ((f32)lrgbad->red * malp));
								lrgbad->grn = (u8)(((f32)lrgbas->grn * alp) + ((f32)lrgbad->grn * malp));
								lrgbad->blu = (u8)(((f32)lrgbas->blu * alp) + ((f32)lrgbad->blu * malp));
								lrgbad->alp = 255;
							}

							// Move to the next pixel
							++lrgbad;
							++lrgbas;
						}	// end for lnX...
				}	// end if lnY...
			}	// end for lnY...
	}




//////////
//
// Perform an alpha blending from the src canvas to the dst canvas, based on the
// src alpha settings, for the section indicated.
//
//////
	void iioss_bitBltSection_Alpha(SBGRA* trgbaDstRoot, SCanvas* tsDst, s32 dulx, s32 duly, SBGRA* trgbaSrcRoot, SCanvas* tsSrc, s32 sulx, s32 suly, s32 slrx, s32 slry)
	{
		s32			lnY, lnX, lnThisX, lnThisY, lnWidth, lnHeight;
		SBGRA*		lrgbad;
		SBGRA*		lrgbas;


		// Derive our size for the source rectangular region
		lnWidth		= slrx - sulx;
		lnHeight	= slry - suly;


		//////////
		// Repeat for every row
		//////
			for (	lnY = duly, lnThisY = 0;
					lnY < (s32)tsSrc->height && lnThisY < lnHeight;
					lnY++, lnThisY++	)
			{
				// Can we copy this row?
				if (lnY >= 0 && lnY < (s32)tsDst->height && lnThisY < lnHeight)
				{
					// Yes we can, recompute the positions for this line
					lrgbad = trgbaDstRoot + (lnY              * tsDst->width);
					lrgbas = trgbaSrcRoot + ((lnThisY + suly) * tsSrc->width) + sulx;


					//////////
					// Iterate for as many pixels as will fit
					//////
						for (	lnX = dulx, lnThisX = 0;
								lnX < (s32)tsSrc->width && lnThisX < lnWidth;
								lnX++, lnThisX++	)
						{
							// Can we copy this pixel?
							if (lnX >= 0 && lnX < (s32)tsDst->width && lnThisX < lnWidth)
							{
								// Yes we can each color channel of this pixel
								lrgbad->red	= lrgbas->red;
								lrgbad->grn = lrgbas->grn;
								lrgbad->blu = lrgbas->blu;
								lrgbad->alp = lrgbas->alp;
							}

							// Move to the next pixel
							++lrgbad;
							++lrgbas;
						}
				}
			}
	}




//////////
//
// Draws a gradient on the indicated canvas.
//
//////
	u32 iioss_gradient(SCanvas* tc, SBGRA* bd, SBGRA ul, SBGRA ur, SBGRA lr, SBGRA ll)
	{
		s32		lnY, lnX;
		f32		red, grn, blu, redColumnStep, grnColumnStep, bluColumnStep;
		f32		redLeft,  grnLeft,  bluLeft;
		f32		redRight, grnRight, bluRight;
		f32		redRowLeftStep,  grnRowLeftStep,  bluRowLeftStep;
		f32		redRowRightStep, grnRowRightStep, bluRowRightStep;
		SBGRA*	lrgba;


		// Grab our colors
		redLeft			= ul.red;
		grnLeft			= ul.grn;
		bluLeft			= ul.blu;
		redRight		= ur.red;
		grnRight		= ur.grn;
		bluRight		= ur.blu;

		// Compute the row step
		redRowLeftStep	= ((f32)ll.red - (f32)ul.red) / (f32)tc->height;
		grnRowLeftStep	= ((f32)ll.grn - (f32)ul.grn) / (f32)tc->height;
		bluRowLeftStep	= ((f32)ll.blu - (f32)ul.blu) / (f32)tc->height;
		redRowRightStep	= ((f32)lr.red - (f32)ur.red) / (f32)tc->height;
		grnRowRightStep	= ((f32)lr.grn - (f32)ur.grn) / (f32)tc->height;
		bluRowRightStep	= ((f32)lr.blu - (f32)ur.blu) / (f32)tc->height;

		// Iterate through every row
		for (lnY = 0; lnY < tc->height; lnY++)
		{
			// Grab our starting color
			red = redLeft;
			grn = grnLeft;
			blu = bluLeft;

			// Determine our column steppings
			redColumnStep = (redRight - redLeft) / (f32)tc->width;
			grnColumnStep = (grnRight - grnLeft) / (f32)tc->width;
			bluColumnStep = (bluRight - bluLeft) / (f32)tc->width;

			// Compute this row's offset
			lrgba = bd + (lnY * tc->width);

			// Repeat for every pixel across
			for (lnX = 0; lnX < tc->width; lnX++)
			{
				// Store this gradient pixel
				lrgba->red	= (u8)red;
				lrgba->grn	= (u8)grn;
				lrgba->blu	= (u8)blu;

				// Increase the color horizontally
				red += redColumnStep;
				grn += grnColumnStep;
				blu += bluColumnStep;

				// Move to next pixel
				++lrgba;
			}

			// Increase the colors vertically
			redLeft		+= redRowLeftStep;
			grnLeft		+= grnRowLeftStep;
			bluLeft		+= bluRowLeftStep;
			redRight	+= redRowRightStep;
			grnRight	+= grnRowRightStep;
			bluRight	+= bluRowRightStep;
		}

		// Indicate success
		return(0);
	}




//////////
//
// Callback for the ioss_createRegion() function, which duplicates each event in the Start/End
// list from the template for the new region.
//
//////
	void iioss_createRegionAppendEventsCallback(SStartEndCallback* cb)
	{
		bool		llResult;
		SEvent*		le;
		SEvent*		leNew;
		SRegion*	lr;


		// Make sure our environment is sane
		if (cb && cb->ptr && cb->extra)
		{
			le = (SEvent*)cb->ptr;
			lr = (SRegion*)cb->extra;

			// Add a copy of this event to the region
			leNew = (SEvent*)oss_SEChain_append(&lr->events, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SEvent), _COMMON_START_END_BLOCK_SIZE, &llResult);
			if (llResult && leNew)
			{
				// Copy over the relevant parts
				leNew->eventId		= le->eventId;
				leNew->signalFlags	= le->signalFlags;
				leNew->_event		= le->_event;
			}
		}
	}




//////////
//
// Painting algorithms for standard controls
//
//////
	u64 ioss_regionDefaultPaintEditbox(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionEditboxData* editbox)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && editbox)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}

	u64 ioss_regionDefaultPaintButton(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionButtonData* button)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && button)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}

	u64 ioss_regionDefaultPaintImage(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionImageData* image)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && image)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}

	u64 ioss_regionDefaultPaintLabel(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionLabelData* label)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && label)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}

	u64 ioss_regionDefaultPaintCheckbox(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionCheckboxData* checkbox)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && checkbox)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}

	u64 ioss_regionDefaultPaintRectangle(SRegion* tr, SCanvas* tc, SBGRA* bd, SRegionRectangleData* rectangle)
	{
		u64 lnPixelsDrawn;


		// Make sure our environment is sane
		lnPixelsDrawn = 0;
		if (tr && tc && bd && rectangle)
		{
		}
		// Indicate if we did anything
		return(lnPixelsDrawn);
	}




//////////
//
// Called to see if there is a debug trap callback we can call to signal that something odd happened
//
//////
	void ioss_regionDoDefaultDebugTrapCallback(SRegion* tr, u64 tnIdentifier, u64 tnExtra)
	{
		// Try the region's callback itself
		if (tr->callback.region._callback_debugTrap)
		{
			// We're good, do this region's callback
			tr->callback.region.callback_debugTrap(tr, tnIdentifier, tnExtra);

		} else if (tr->parentScreen && tr->parentScreen->activeRegion && tr->parentScreen->activeRegion->callback.region._callback_debugTrap) {
			// Try the parent screen's activeRegion default callback
			tr->parentScreen->activeRegion->callback.region.callback_debugTrap(tr, tnIdentifier, tnExtra);
		}
	}




//////////
//
// Called to register plugins, or their functions, or to unregister entirely, or their functions
//
//////
	_isSInterfacePlugin* ioss_plugin_register(u64 DllInstance)
	{
		_isSInterfacePlugin* plugin;


		// Allocate the plugin
		plugin = (_isSInterfacePlugin*)oss_SEChain_append(&gsRootFunctionPlugins, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(_isSInterfacePlugin), _COMMON_START_END_BLOCK_SIZE, NULL);

		// IF it was allocated, set the dll instance
		if (plugin)
			plugin->DllInstance = DllInstance;

		// Indicate our success or failure
		return(plugin);
	}

	u64 ioss_plugin_unregister(u64 DllInstance)
	{
		// Not currently supported
		return(-1);
	}




//////////
//
// Callback for searching a plugin by DllInstance id
//
//////
	bool ioss_plugin_registerCallback(SStartEndCallback* cb)
	{
		// Make sure the environment is sane
		if (cb->ptr && cb->extra)
		{
			// Is this a match?
			if (((_isSInterfacePlugin*)cb->ptr)->DllInstance == cb->extra)
				return(true);	// Yes
		}
		// Not found
		return(false);
	}




//////////
//
// Callback for the enumerate monitors function
//
//////
	BOOL CALLBACK iioss_enumerateMonitors(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
	{
		bool			llResult;
		MONITORINFO		lmi;
		SOssWindow*		low;
		SStartEnd*		lse;


		// Grab the monitor info
		lmi.cbSize = sizeof(MONITORINFO);
		if (GetMonitorInfo(hMonitor, &lmi))
		{
			lse = (SStartEnd*)dwData;
			low = (SOssWindow*)oss_SEChain_append(lse, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SOssWindow), 2, &llResult);
			if (low)
			{
				// Initialize the structure
				memset(low, 0, sizeof(SOssWindow));

				// Store the data
				low->osX			= lmi.rcMonitor.left;
				low->osY			= lmi.rcMonitor.top;
				low->width			= lmi.rcMonitor.right	- lmi.rcMonitor.left;
				low->height			= lmi.rcMonitor.bottom	- lmi.rcMonitor.top;
			}
		}
		// Indicate we want more
		return TRUE;
	}

	void iioss_enumerateMonitorsIterateCallback(SStartEndCallback* cb)
	{
		SOssWindow*			lowOld;
		SOssWindow*			lowNew;
		SOssWindow**		lowp;
		f32					lfHypOld, lfHypNew;


		// Make sure the environment is sane
		if (cb && cb->ptr && cb->extra != 0)
		{
			// Grab the existing pointer
			lowNew	= (SOssWindow*)cb->ptr;
			lowp	= (SOssWindow**)cb->extra;

			// Has a monitor already been selected to compare against?
			if (*lowp)
			{
				// Grab the previous monitor pointer
				lowOld	= *lowp;

				// If the line from upper-left to lower-right is longer, then this is our new man
				lfHypOld	= (f32)sqrt((f32)(lowOld->width * lowOld->width)	+ (f32)(lowOld->height * lowOld->height));
				lfHypNew	= (f32)sqrt((f32)(lowNew->width * lowNew->width)	+ (f32)(lowNew->height * lowNew->height));

				// See which one is longer
				if (lfHypNew > lfHypOld)
					*lowp = lowNew;		// We've found our new biggest monitor

			} else {
				// This is the first monitor, so by default we store it
				*lowp = lowNew;
			}
		}
	}




/////////
//
// Delete the scale compute chain for the indicated scale map
//
//////
	void ioss_deleteScaleCompute(SScaleMap* tsm)
	{
		SScaleCompute*	lsc;
		SScaleCompute*	lscNext;


		// Make sure our environment is sane
		if (tsm)
		{
			// Grab the starting point
			lsc = tsm->firstScale;

			// Indicate this entry no longer exists
			tsm->firstScale	= NULL;

			// Iterate through every entry
			while (lsc)
			{
				// Grab the next entry
				lscNext = (SScaleCompute*)lsc->next;

				// Delete this entry
				free(lsc);

				// Move to next entry
				lsc = lscNext;
			}
		}
	}
