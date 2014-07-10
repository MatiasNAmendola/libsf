//////////
//
// /libsf/source/vjr/vjr_sup.cpp
//
//////
// Version 0.30
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.12.2014
//////
// Change log:
//     Feb.12.2014 - Initial creation
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
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




//////////
//
// Startup initialization, called from WinMain() only.
//
//////
	void iInit_vjr(HACCEL* hAccelTable)
	{
		HRESULT hRes;


		// Keyboard shortcuts
		*hAccelTable = LoadAccelerators(ghInstance, MAKEINTRESOURCE(IDC_VJR));

		// Taskbar interface
		hRes = OleInitialize(NULL);
		CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void**)&giTaskbar);

		// Initialize our builder
		iBuilder_createAndInitialize(&gWindows,	-1);
		iBuilder_createAndInitialize(&gFonts,	-1);

		// Initialize our critical sections
		InitializeCriticalSection(&gcsUniqueIdAccess);

		// Get startup time
		systemStartedMs = iTime_getLocalMs();

		// Default font
		gsFont					= iFont_create(cgcDefaultFont,			10, FW_NORMAL,	0, 0);
		gsWindowTitleBarFont	= iFont_create(cgcWindowTitleBarFont,	12, FW_NORMAL,	0, 0);


		//////////
		// Load our icons and images
		//////
			bmpVjrIcon		= iBmp_rawLoad(cgc_appIconBmp);
			bmpJDebiIcon	= iBmp_rawLoad(cgc_jdebiAppIconBmp);

			// Create a 1x1 no image bitmap placeholder
			bmpNoImage		= iBmp_allocate();
			iBmp_createBySize(bmpNoImage, 1, 1, 32);

			bmpClose		= iBmp_rawLoad(cgc_closeBmp);
			bmpMaximize		= iBmp_rawLoad(cgc_maximizeBmp);
			bmpMinimize		= iBmp_rawLoad(cgc_minimizeBmp);
			bmpMove			= iBmp_rawLoad(cgc_moveBmp);

			bmpArrowUl		= iBmp_rawLoad(cgc_arrowUlBmp);
			bmpArrowUr		= iBmp_rawLoad(cgc_arrowUrBmp);
			bmpArrowLl		= iBmp_rawLoad(cgc_arrowLlBmp);
			bmpArrowLr		= iBmp_rawLoad(cgc_arrowLrBmp);


		// Create the default reference datetimes
		iInit_createDefaultDatetimes();

		// Create our message window
		iInit_createMessageWindow();

		// Create our default objects
		iInit_createDefaultObjects();

		// Create the buffers for screen and command history
		screenData		= iEditChainManager_allocate();
		commandHistory	= iEditChainManager_allocate();

		// Set the cursor line data on commandHistory only
		commandHistory->showCursorLine	= true;
		commandHistory->showEndLine		= true;

		// Create our main screen window
		iInit_create_screenObject();
		iInit_create_jdebiObject();

		// Initially render each one
		iObj_render(gobj_screen, true, true);
		iObj_render(gobj_jdebi, true, true);

		// Attach them to physical windows
		gWinScreen	= iWindow_allocate();
		gWinJDebi	= iWindow_allocate();
		iObj_createWindowForForm(gobj_screen,	gWinScreen,	IDI_VJR);
		iObj_createWindowForForm(gobj_jdebi,	gWinJDebi,	IDI_JDEBI);

		// Initially populate _screen
		iEditChainManager_appendLine(screenData, (s8*)cgcScreenTitle, -1);
		iEditChainManager_appendLine(screenData, NULL, 0);
		iEditChainManager_appendLine(screenData, "Please report any bugs:  http://www.visual-freepro.org/forum", -1);
		iEditChainManager_appendLine(screenData, "Thank you, and may the Lord Jesus Christ bless you richly. :-)", -1);
		iEditChainManager_appendLine(screenData, NULL, 0);
		iEditChainManager_appendLine(screenData, "              _____", -1);
		iEditChainManager_appendLine(screenData, "             |     |", -1);
		iEditChainManager_appendLine(screenData, "             |     |", -1);
		iEditChainManager_appendLine(screenData, "     ________|     |________     In God's sight we've come together.", -1);
		iEditChainManager_appendLine(screenData, "    |                       |    We've come together to help each other.", -1);
		iEditChainManager_appendLine(screenData, "    |________       ________|    Let's grow this project up ... together!", -1);
		iEditChainManager_appendLine(screenData, "             |     |             In service and love to The Lord, forever!", -1);
		iEditChainManager_appendLine(screenData, "             |     |", -1);
		iEditChainManager_appendLine(screenData, "             |     |             Sponsored by:", -1);
		iEditChainManager_appendLine(screenData, "             |     |                LibSF -- Liberty Software Foundation", -1);
		iEditChainManager_appendLine(screenData, "             |     |", -1);
		iEditChainManager_appendLine(screenData, "             |     |             We need more coders. Please consider helping out.", -1);
		iEditChainManager_appendLine(screenData, "             |     |             Your contribution would make a difference.", -1);
		iEditChainManager_appendLine(screenData, "             |     |", -1);
		iEditChainManager_appendLine(screenData, "             |_____|", -1);
		iEditChainManager_appendLine(screenData, NULL, 0);
		iEditChainManager_navigateEnd(screenData, gobj_screen);
		gobj_screen->isDirty = true;
		iObj_render(gobj_screen, true, true);

		// Initially populate _jdebi
		iEditChainManager_appendLine(commandHistory, "*** Welcome to Visual FreePro, Junior! :-)", -1);
		iEditChainManager_appendLine(commandHistory, "*** For now, this can be thought of as a command window ... with a twist.", -1);
		iEditChainManager_appendLine(commandHistory, "*** It works like an editor window.  You can insert new lines, edit old ones, etc.", -1);
		iEditChainManager_appendLine(commandHistory, "*** To execute a command, press F6 or Enter if you're on the last line, or use F6 on any line.", -1);
		iEditChainManager_appendLine(commandHistory, "*** You can use ? 999 and ? \"sample\" in this daily build.", -1);
		iEditChainManager_appendLine(commandHistory, "-----", -1);
		iEditChainManager_appendLine(commandHistory, NULL, 0);
		iEditChainManager_navigateEnd(commandHistory, gobj_jdebi);
		gobj_jdebi->isDirty = true;
		iObj_render(gobj_jdebi, true, true);
	}




//////////
//
// Creates the message window used for communicating actions
//
//////
	void iInit_createMessageWindow(void)
	{
		ATOM			atom;
		WNDCLASSEXA		classa;


		//////////
		// Register the classes if need be
		//////
			while (1)
			{
				if (!GetClassInfoExA(ghInstance, cgcMessageWindowClass, &classa))
				{
					// Initialize
					memset(&classa, 0, sizeof(classa));

					// Populate
					classa.cbSize				= sizeof(WNDCLASSEXA);
					classa.hInstance			= ghInstance;
					classa.lpszClassName		= cgcMessageWindowClass;
					classa.lpfnWndProc			= &iMessage_wndProcWindow;

					// Register
					atom = RegisterClassExA(&classa);
					if (!atom)
						break;
				}



			//////////
			// Create the message window
			//////
				ghwndMsg = CreateWindowA(cgcMessageWindowClass, cgcMessageWindowClass, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, ghInstance, 0);
				if (ghwndMsg)
				{
					// Read events
					CreateThread(NULL, 0, &iReadEvents_messageWindow, 0, 0, 0);
					return;
				}
				break;
			}
			// We should never get here
			MessageBoxA(NULL, "Error creating Visual FreePro Jr's message window.", "VJr - Fatal Error", MB_OK);
	}




//////////
//
// In order for a window pointer to be valid, it must be in the range gWindows->data to
// gWindows->data + gWindows->populatedLength.
//
//////
	bool isValidWindow(u32 w)
	{
		return(w >= (u32)gWindows->data && w < (u32)(gWindows->data + gWindows->populatedLength));
	}




//////////
//
// Thread to handle message window events
//
//////
	DWORD WINAPI iReadEvents_messageWindow(LPVOID lpParameter)
	{
		MSG msg;


		// Read until the message window goes bye bye
		while (GetMessage(&msg, ghwndMsg, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// When we get here, we're shutting down
		return 0;
	}




//////////
//
// Processes internal messages to process things internally.
//
//////
	LRESULT CALLBACK iMessage_wndProcWindow(HWND hwnd, UINT m, WPARAM w, LPARAM l)
	{
		// Call Windows' default procedure handler
		return(DefWindowProc(hwnd, m, w, l));
	}




//////////
//
// Loads the default settings for each object, populating them in turn.
//
//////
	void iInit_createDefaultObjects(void)
	{
		//////////
		// Create each default object
		//////
			gobj_defaultEmpty		= iObj_create(_OBJ_TYPE_EMPTY,		NULL);
			gobj_defaultLabel		= iObj_create(_OBJ_TYPE_LABEL,		NULL);
			gobj_defaultTextbox		= iObj_create(_OBJ_TYPE_TEXTBOX,		NULL);
			gobj_defaultButton		= iObj_create(_OBJ_TYPE_BUTTON,		NULL);
			gobj_defaultImage		= iObj_create(_OBJ_TYPE_IMAGE,		NULL);
			gobj_defaultCheckbox	= iObj_create(_OBJ_TYPE_CHECKBOX,	NULL);
			// Option and radio both have label controls within
			gobj_defaultOption		= iObj_create(_OBJ_TYPE_OPTION,		NULL);
			gobj_defaultRadio		= iObj_create(_OBJ_TYPE_RADIO,		NULL);
			// Forms and subforms are created last because they have objects referenced within which must be created before
			gobj_defaultForm		= iObj_create(_OBJ_TYPE_FORM,		NULL);
			gobj_defaultSubform		= iObj_create(_OBJ_TYPE_SUBFORM,		NULL);
	}




//////////
//
// Called to create the _screen object with all of its stuff.
//
//////
	void iInit_create_screenObject(void)
	{
		s32				lnLeft, lnTop, lnWidth, lnHeight;
		SSubObjForm*	sof;
		RECT			lrc;


		//////////
		// Create the object
		//////
			// Create sub-object
			sof = iSubobj_createForm((SSubObjForm*)gobj_defaultForm->sub_obj, NULL);
			if (!sof)
				return;

			// Create object
			gobj_screen = iObj_create(_OBJ_TYPE_FORM, sof);
			if (!gobj_screen)
			{
				iSubobj_deleteForm(sof, true);
				return;
			}

			// Set the app icon
			iSubobj_form_setIcon(gobj_screen, bmpVjrIcon);

			// Give it a caption
			iSubobj_form_setCaption(gobj_screen, (s8*)cgcScreenTitle, sizeof(cgcScreenTitle) - 1);
			iSubobj_form_setCaptionColor(gobj_screen, black.color);

			// Set its colors
			iSubobj_form_setBorderRgba(gobj_screen, NwColor.color, NeColor.color, SwColor.color, SeColor.color);
			iSubobj_form_setBackColor(gobj_screen, white.color);
			iSubobj_form_setForeColor(gobj_screen, black.color);

			// Give it a fixed point font
			iSubobj_form_setFont(gobj_screen, (s8*)cgcDefaultFixedFont, 9, false, false, false, false, false, false);

			// Set it visible
			iObj_setVisible(gobj_screen, true);


		//////////
		// Size it to just under half the screen initially
		//////
			GetWindowRect(GetDesktopWindow(), &lrc);
			lnWidth		= (lrc.right - lrc.left) / 2;
			lnHeight	= (lrc.bottom - lrc.top);

		
		//////////
		// Size and position it
		//////
			lnLeft		= (lrc.right  - lrc.left)  / 32;
			lnTop		= (lrc.bottom - lrc.top)   / 32;
			lnWidth		-= lnLeft;
			lnHeight	-= (2 * lnTop);
			iObj_setSize(gobj_screen, lnLeft, lnTop, lnWidth, lnHeight);
	}




//////////
//
// 
//
//////
	void iInit_create_jdebiObject(void)
	{
		s32		lnLeft, lnTop, lnWidth, lnHeight;
		SSubObjForm*	sof;
		RECT			lrc;


		//////////
		// Create the object
		//////
			// Create sub-object
			sof = iSubobj_createForm((SSubObjForm*)gobj_defaultForm->sub_obj, NULL);
			if (!sof)
				return;

			// Create object
			gobj_jdebi = iObj_create(_OBJ_TYPE_FORM, sof);
			if (!gobj_jdebi)
			{
				iSubobj_deleteForm(sof, true);
				return;
			}

			// Set the app icon
			iSubobj_form_setIcon(gobj_jdebi, bmpJDebiIcon);

			// Set it visible
			iObj_setVisible(gobj_jdebi, true);

			// Give it a caption
			iSubobj_form_setCaption(gobj_jdebi, (s8*)cgcJDebiTitle, sizeof(cgcJDebiTitle) - 1);
			iSubobj_form_setCaptionColor(gobj_jdebi, black.color);

			// Set its colors
			iSubobj_form_setBorderRgba(gobj_jdebi, NwColor.color, NeColor.color, SwColor.color, SeColor.color);
			iSubobj_form_setBackColor(gobj_jdebi, white.color);
			iSubobj_form_setForeColor(gobj_jdebi, black.color);

			// Give it a fixed point font
			iSubobj_form_setFont(gobj_jdebi, (s8*)cgcDefaultFixedFont, 10, false, false, false, false, false, false);


		//////////
		// Size it to just under half the screen initially
		//////
			GetWindowRect(GetDesktopWindow(), &lrc);
			lnWidth		= (lrc.right - lrc.left) / 2;
			lnHeight	= (lrc.bottom - lrc.top);

		
		//////////
		// Size and position it
		//////
			lnLeft		= lnWidth;
			lnTop		= 3 * lnHeight / 4;
			lnWidth		-= ((lrc.right - lrc.left) / 32);
			lnHeight	= lnHeight / 4 - ((lrc.bottom - lrc.top) / 32);
			iObj_setSize(gobj_jdebi, lnLeft, lnTop, lnWidth, lnHeight);
	}




//////////
//
// Called to create the default datetime variable that are constant references
//
//////
	void iInit_createDefaultDatetimes(void)
	{
		SDateTime dt;


		//////////
		// Jan.01.2000 00:00:00.000
		//////
			_datetime_Jan_01_2000 = iVariable_create(_VAR_TYPE_DATETIME, NULL);
			dt.julian	= 2451545;
			dt.seconds	= 0.0f;
			iDatum_duplicate(&_datetime_Jan_01_2000->value, (s8*)&dt, 8);
	}




//////////
//
// Processes messages from the interface window, to forward on to the original window
//
//////
	LRESULT CALLBACK iWindow_wndProc(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		SWindow*		win;
		HDC				lhdc;
		PAINTSTRUCT		ps;


		// See if we know this hwnd
		win = iWindow_findByHwnd(h);
		if (win)
		{
			// It was one of our windows
			switch (m)
			{
				case WMVJR_FIRST_CREATION:
					// Currently unused
					break;

				case WM_DESTROY:
					// Currently unused
					break;

				case WM_LBUTTONDOWN:
					return(iMouse_processMessage(win, m, w, l));
					break;

				case WM_LBUTTONUP:
					return(iMouse_processMessage(win, m, w, l));
					break;

				case WM_RBUTTONDOWN:
					return(iMouse_processMessage(win, m, w, l));
					break;

				case WM_RBUTTONUP:
					return(iMouse_processMessage(win, m, w, l));
					break;

				case WM_MBUTTONDOWN:
					return(iMouse_processMessage(win, m, w, l));
					break;

				case WM_MBUTTONUP:
					return(iMouse_processMessage(win, m, w, l));
					break;

				case WM_RBUTTONDBLCLK:
				case WM_LBUTTONDBLCLK:
				case WM_MBUTTONDBLCLK:
				case WM_MOUSEHWHEEL:
				case WM_MOUSEWHEEL:
				case WM_MOUSEMOVE:
					win->isMouseLeftButton		= ((w & MK_LBUTTON) != 0);		// The left mouse button is down
					win->isMouseMiddleButton	= ((w & MK_MBUTTON) != 0);		// The middle mouse button is down
					win->isMouseRightButton		= ((w & MK_RBUTTON) != 0);		// The right mouse button is down
					return(iMouse_processMessage(win, m, w, l));
					break;

				case WM_KEYDOWN:
//				case WM_KEYUP:
//				case WM_CHAR:
//				case WM_DEADCHAR:
//				case WM_SYSKEYDOWN:
//				case WM_SYSKEYUP:
//				case WM_SYSCHAR:
//				case WM_SYSDEADCHAR:
					return(iKeyboard_processMessage(win, m, w, l));
					break;

				case WM_CAPTURECHANGED:
					if (win->isMoving)
					{
						// Stop the movement
//						iStopMove();

					} else if (win->isResizing) {
						// Stop the resize
//						iStopResize();

					} else {
						// Make sure our flags are lowered
						win->isMoving	= false;
						win->isResizing	= false;
					}
					break;

				case WM_PAINT:
					// Paint it
					lhdc = BeginPaint(h, &ps);
					BitBlt(lhdc, 0, 0, win->obj->bmp->bi.biWidth, win->obj->bmp->bi.biHeight, win->obj->bmp->hdc, 0, 0, SRCCOPY);
					EndPaint(h, &ps);
					return 0;
			}
		}

		// Call Windows' default procedure handler
		return(DefWindowProc(h, m, w, l));
	}




//////////
//
// Called to create the Windows-facing window for the indicated object.
// Note:  Any object can be presented in a window, though typically on form objects are.
//
//////
	SWindow* iWindow_createForObject(SObject* obj, SWindow* win, s32 icon)
	{
		SWindow*		winNew;
		WNDCLASSEXA		classex;
		ATOM			atom;
		s8				buffer[128];
		s8				bufferClass[256];


		// Make sure our environment is sane
		winNew = NULL;
		if (obj)
		{
			//////////
			// Create if need be
			//////
				if (!win)		winNew = iWindow_allocate();
				else			winNew = win;


			//////////
			// If we have a window, prepare it
			//////
				if (winNew)
				{
					// Lock down
					EnterCriticalSection(&winNew->cs);

					// Initialize
					memset(buffer, 0, sizeof(buffer));

					// Populate
					CopyRect(&winNew->rc, &obj->rc);
					winNew->obj = obj;


					//////////
					// Register the general window class if need be
					//////
						icon = ((icon <= 0) ? IDI_VJR : icon);
						sprintf(bufferClass, "%s%u\0", (s8*)cgcWindowClass, icon);
						if (!GetClassInfoExA(ghInstance, bufferClass, &classex))
						{
							// Initialize
							memset(&classex, 0, sizeof(classex));

							// Populate
							classex.cbSize				= sizeof(WNDCLASSEXA);
							classex.hInstance			= ghInstance;
							classex.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
							classex.lpszClassName		= bufferClass;
							classex.hIcon				= LoadIcon(ghInstance, MAKEINTRESOURCE(icon));
							classex.hCursor				= LoadCursor(NULL, IDC_ARROW);
							classex.lpfnWndProc			= &iWindow_wndProc;

							// Register
							atom = RegisterClassExA(&classex);
						}


					//////////
					// Physically create the window
					//////
						// Window name
						if (obj->name.data)		memcpy(buffer, obj->name.data,		min(obj->name.length, sizeof(buffer) - 1));
						else					memcpy(buffer, cgcScreenTitle,		sizeof(cgcScreenTitle));

						// Build it
						winNew->hwnd = CreateWindow(bufferClass, buffer, WS_POPUP, obj->rc.left, obj->rc.top, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top, NULL, NULL, ghInstance, 0);

						// Initialize it internally
						PostMessage(winNew->hwnd, WMVJR_FIRST_CREATION, 0, 0);

						// If visible, show it
						if (obj->isVisible)
							ShowWindow(winNew->hwnd, SW_SHOW);

					// Unlock
					LeaveCriticalSection(&winNew->cs);
				}
		}

		// Indicate our status
		return(winNew);
	}




//////////
//
// Called to search the known windows for the indicated window by hwnd
//
//////
	SWindow* iWindow_findByHwnd(HWND hwnd)
	{
		u32			lnI;
		HWND		lnHwnd;
		SWindow*	win;


		// Iterate through all known windows and see which one is which
		for (lnI = 0; lnI < gWindows->populatedLength; lnI += sizeof(SWindow))
		{
			// Grab this one
			win = (SWindow*)(gWindows->data + lnI);

			// Lock it down
			EnterCriticalSection(&win->cs);

			// Grab the hwnd
			lnHwnd = win->hwnd;

			// Unlock it
			LeaveCriticalSection(&win->cs);

			// Is this our man?
			if (lnHwnd == hwnd)
			{
				// Indicate our find
				return(win);
			}
		}
		// If we get here, not found
		return(NULL);
	}




//////////
//
// Called to
//
//////
	SWindow* iWindow_allocate(void)
	{
		u32			lnI;
		bool		llFound;
		SWindow*	win;
		
		
		// Iterate through existing slots for isValid=false windows
		for (lnI = 0; lnI < gWindows->populatedLength; lnI += sizeof(SWindow))
		{
			// Grab this one
			win = (SWindow*)(gWindows->data + lnI);

			// Lock it down
			if (TryEnterCriticalSection(&win->cs))
			{
				// Is this one invalid?
				if (!win->isValid)
				{
					// We can use this one
					llFound			= true;
					win->isValid	= true;

				} else {
					// We must continue looking
					llFound			= false;
				}

				// Unlock it
				LeaveCriticalSection(&win->cs);

				// If we found it, use it
				if (llFound)
					return(win);
			}
		}

		// If we get here, it wasn't found
		win = (SWindow*)iBuilder_allocateBytes(gWindows, sizeof(SWindow));
		if (win)
		{
			// Initialize
			memset(win, 0, sizeof(SWindow));

			// Initially populate
			InitializeCriticalSection(&win->cs);
			win->isValid = true;
		}

		// Indicate our status
		return(win);
	}




//////////
//
// Called to re-render the indicated window
//
//////
	void iWindow_render(SWindow* win)
	{
		// Make sure we have something to render
		if (win && win->obj)
		{
			iObj_render(win->obj, true, true);
			InvalidateRect(win->hwnd, 0, FALSE);
		}
	}




//////////
//
// Adjusts the brightness of the indicated color by the indicated percentage.
//
//////
	void iColor_adjustBrightness(SBgra& color, f32 tfPercent)
	{
		f32 red, grn, blu;


		//////////
		// Adjust the color
		//////
			tfPercent	= (100.0f + tfPercent) / 100.0f;
			red			= (f32)color.red * tfPercent;
			grn			= (f32)color.grn * tfPercent;
			blu			= (f32)color.blu * tfPercent;


		//////////
		// Constrict it into range
		//////
			red			= min(max(red, 0.0f), 255.0f);
			grn			= min(max(grn, 0.0f), 255.0f);
			blu			= min(max(blu, 0.0f), 255.0f);


		//////////
		// Set the color back
		//////
			color.red	= (u8)red;
			color.grn	= (u8)grn;
			color.blu	= (u8)blu;
	}




//////////
//
// Called to shutdown the system politely, closing everything that's open
//
//////
	bool iInit_shutdownPolitely(void)
	{
		return(true);
	}




//////////
//
// Compute the client area dimensions based on the current settings
//
//////
	void iComputeScreenWindowClientAreaDimensions(SSize* size)
	{
		RECT lrc;


		//////////
		// Iterate through each item
		//////
			// Default to half the overall screen size
			GetWindowRect(GetDesktopWindow(), &lrc);
			size->width		= (lrc.right - lrc.left) * 7 / 16;
			size->height	= (lrc.bottom - lrc.top) * 7 / 8;

			// When we get here, they are set by value, either to the minimum, or to the maximum
			// Note:  They could be hugely too large.  The caller will have to deal with that.
	}

	void iComputeScreenWindowNonclientAreaDimensions(SSize* size)
	{
		//////////
		// Set minimum dimensions
		//////
			size->width		= 8 + 8;		// left + right
			size->height	= 24 + 24;		// top + bottom
	}

	void iAdjustScreenWindowDimensions(SSize* size)
	{
		s32		lnDesktopWidth, lnDesktopHeight, lnWidthOverhang, lnHeightOverhang;
		f32		lfWidthRatio, lfHeightRatio;
		RECT	lrc;


		//////////
		// Find out how big the desktop is
		//////
			GetWindowRect(GetDesktopWindow(), &lrc);


		//////////
		// Make sure we're smaller than that
		//////
			lnDesktopWidth		= lrc.right - lrc.left;
			lnDesktopHeight		= lrc.bottom - lrc.top;
			if (size->width < lnDesktopWidth && size->height < lnDesktopHeight)
				return;		// We're good


		//////////
		// Find out which size needs to be decreased the most
		//////
			lnWidthOverhang		= size->width  - lnDesktopWidth;
			lnHeightOverhang	= size->height - lnDesktopHeight;
			lfWidthRatio		= ((f32)lnWidthOverhang  + (f32)lnDesktopWidth)  / (f32)lnDesktopWidth;
			lfHeightRatio		= ((f32)lnHeightOverhang + (f32)lnDesktopHeight) / (f32)lnDesktopHeight;
			if (lfWidthRatio >= lfHeightRatio)
			{
				// Adjust down by the width's ratio
				size->width		= lnDesktopWidth;
				size->height	= (s32)((f32)size->height / lfWidthRatio);

			} else {
				// Adjust down by the height's ratio
				size->width		= (s32)((f32)size->width / lfHeightRatio);
				size->height	= lnDesktopHeight;
			}
	}




//////////
//
// Compute the client area JDebi window dimensions
//
//////
	void iComputeJDebiWindowClientAreaDimensions(SSize* size)
	{
		RECT lrc;


		//////////
		// Iterate through each item
		//////
			// Default to one sixth wide, one eighth tall of the overall screen size
			GetWindowRect(GetDesktopWindow(), &lrc);
			size->width		= (lrc.right - lrc.left) * 7 / 16;
			size->height	= (lrc.bottom - lrc.top) * 7 / 8;
	}

	void iComputeJDebiWindowNonclientAreaDimensions(SSize* size)
	{
		//////////
		// Set minimum dimensions
		//////
			size->width		= 8 + 8;		// left + right
			size->height	= 24 + 24;		// top + bottom
	}

	void iAdjustJDebiWindowDimensions(SSize* size)
	{
		s32		lnDesktopWidth, lnDesktopHeight, lnWidthOverhang, lnHeightOverhang;
		f32		lfWidthRatio, lfHeightRatio;
		RECT	lrc;


		//////////
		// Find out how big the desktop is
		//////
			GetWindowRect(GetDesktopWindow(), &lrc);


		//////////
		// Make sure we're smaller than that
		//////
			lnDesktopWidth		= lrc.right - lrc.left;
			lnDesktopHeight		= lrc.bottom - lrc.top;
			if (size->width < lnDesktopWidth && size->height < lnDesktopHeight)
				return;		// We're good


		//////////
		// Find out which size needs to be decreased the most
		//////
			lnWidthOverhang		= size->width  - lnDesktopWidth;
			lnHeightOverhang	= size->height - lnDesktopHeight;
			lfWidthRatio		= ((f32)lnWidthOverhang  + (f32)lnDesktopWidth)  / (f32)lnDesktopWidth;
			lfHeightRatio		= ((f32)lnHeightOverhang + (f32)lnDesktopHeight) / (f32)lnDesktopHeight;
			if (lfWidthRatio >= lfHeightRatio)
			{
				// Adjust down by the width's ratio
				size->width		= lnDesktopWidth;
				size->height	= (s32)((f32)size->height / lfWidthRatio);

			} else {
				// Adjust down by the height's ratio
				size->width		= (s32)((f32)size->width / lfHeightRatio);
				size->height	= lnDesktopHeight;
			}
	}




//////////
//
// Time functions
//
//////
	s64 iTime_computeMilliseconds(SYSTEMTIME* time)
	{
		s64 lnMs;
		

		// Compute the milliseconds
		lnMs	=		(time->wMilliseconds)
					+	(time->wSecond			* 1000)
					+	(time->wMinute			* 1000 * 60)
					+	(time->wHour			* 1000 * 60 * 60)
					+	(time->wDay				* 1000 * 60 * 60 * 24)
					+	(time->wMonth			* 1000 * 60 * 60 * 24 * 31)
					+	(time->wYear			* 1000 * 60 * 60 * 24 * 31 * 366);
		return(lnMs);
	}

	s64 iTime_getSystemMs(void)
	{
		SYSTEMTIME time;
		GetSystemTime(&time);
		return(iTime_computeMilliseconds(&time));
	}

	s64 iTime_getLocalMs(void)
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		return(iTime_computeMilliseconds(&time));
	}

	s64 iMath_delta(s64 tnBaseValue, s64 tnSubtractionValue)
	{
		return(tnBaseValue - tnSubtractionValue);
	}




//////////
//
// Called to duplicate the indicated string
//
//////
	s8* iDuplicateString(s8* tcText)
	{
		u32		lnLength;
		s8*		ptr;


		// Allocate it
		lnLength	= strlen(tcText) + 1;
		ptr			= (s8*)malloc(lnLength);

		// Copy it (including the trailing null)
		if (ptr)
			memcpy(ptr, tcText, lnLength);

		// All done
		return(ptr);
	}




//////////
//
// Called to duplicate a font that was found from the list of known system fonts
//
//////
	SFont* iFont_duplicate(SFont* fontSource)
	{
		SFont* font;


		// Make sure our environment is sane
		font = NULL;
		if (fontSource)
		{
			//////////
			// Allocate a new pointer
			//////
				font = iFont_allocate();
				if (!font)
					return(font);


			//////////
			// Create a copy
			//////
				// Initialize the copy
				memcpy(font, fontSource, sizeof(SFont));
				font->name.data		= NULL;
				font->name.length	= 0;
				iDatum_duplicate(&font->name, fontSource->name.data, fontSource->name.length);

				// Set unique parts
				font->hdc						= CreateCompatibleDC(GetDC(GetDesktopWindow()));
				font->hfont						= CreateFont(font->_sizeUsedForCreateFont, 0, 0, 0, font->_weight, (font->_italics != 0), (font->_underline != 0), false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, font->name.data);
				SelectObject(font->hdc, font->hfont);
		}
		// Indicate our success or failure
		return(font);
	}




//////////
//
// Allocate an empty structure
//
//////
	SFont* iFont_allocate(void)
	{
		SFont* font;


		// Allocate the indicated size
		font = (SFont*)malloc(sizeof(SFont));

		// If allocated, initialize it
		if (font)
			memset(font, 0, sizeof(SFont));

		// Indicate our success or failure
		return(font);
	}





//////////
//
// Create a new font
//
//////
	SFont* iFont_create(cs8* tcFontName, u32 tnFontSize, u32 tnFontWeight, u32 tnItalics, u32 tnUnderline)
	{
		u32		lnI, lnLength;
		SFont*	font;


		//////////
		// See if the indicated font already exists
		//////
			lnLength = strlen(tcFontName);
			for (lnI = 0; lnI < gFonts->populatedLength; lnI += sizeof(SFont))
			{
				// Grab the pointer
				font = (SFont*)(gFonts->data + lnI);

				// See if it matches
				if (font->_size == tnFontSize && font->_weight == tnFontWeight && font->_italics == tnItalics && font->_underline == tnUnderline && font->name.length == lnLength)
					if (_memicmp(font->name.data, tcFontName, lnLength) == 0)
						return(font);
			}


		//////////
		// Allocate a new pointer
		//////
			font = (SFont*)iBuilder_allocateBytes(gFonts, sizeof(SFont));
			if (!font)
				return(font);

			// Initialize
			memset(font, 0, sizeof(SFont));


		//////////
		// Populate
		//////
			font->hdc						= CreateCompatibleDC(GetDC(GetDesktopWindow()));
			font->_sizeUsedForCreateFont	= -MulDiv(tnFontSize, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);
			font->hfont						= CreateFont(font->_sizeUsedForCreateFont, 0, 0, 0, tnFontWeight, (tnItalics != 0), (tnUnderline != 0), false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, FF_SWISS, tcFontName);
			SelectObject(font->hdc, font->hfont);
			iDatum_duplicate(&font->name, (s8*)tcFontName, lnLength);
			font->_size						= tnFontSize;
			font->_weight					= tnFontWeight;
			font->_italics					= tnItalics;
			font->_underline				= tnUnderline;

			// Find out the text metrics
			GetTextMetricsA(font->hdc, &font->tm);


		// Indicate our success
		return(font);
	}




//////////
//
// Free the indicated font resource
//
//////
	void iFont_delete(SFont** fontRoot, bool tlDeleteSelf)
	{
		SFont* font;


		if (fontRoot && *fontRoot)
		{
			// Grab our pointer
			font = *fontRoot;

			//////////
			// Free components
			//////
				DeleteObject((HGDIOBJ)font->hfont);
				DeleteDC(font->hdc);


			//////////
			// Free self
			//////
				if (tlDeleteSelf)
				{
					free(font);
					*fontRoot = NULL;
				}
		}
	}




//////////
//
// A particular font occupies a certain physical amount of text relative to the rectangle it inhabits.
// In order for this font to be scaled up, the font dynamics will need to change somewhat as per the limitations
// within the font design.  As such, we have to scan upward to find the closest matching font that is equal to
// or less than the ratios indicated at the current size, yet for the desired size.
//
//////
	u32 iFont_findClosestSizeMatch(s8* tcText, s8* tcFontName, u32 tnFontSize, u32 tnFontBold, u32 tnFontItalic, u32 tnFontUnderline, u32 tnWidth, u32 tnHeight, u32 tnWidthDesired, u32 tnHeightDesired)
	{
		s32			lnI, lnJ, lnTextLength, lnFontBold;
		f64			lfRatioH, lfRatioV, lfRatioHThis, lfRatioVThis;
		SSize		size[200];
		RECT		lrc;
		SFont*		font;


		// Iterate from the current size upward for a maximum of 200 font point sizes, but also not more than 3x its current point size
		lnTextLength	= strlen(tcText);
		lnFontBold		= ((tnFontBold) ? FW_BOLD : FW_NORMAL);
		for (lnI = 0; lnI == 0 || (lnI < 200 && (s32)(tnFontSize + lnI) < (s32)(tnFontSize * 3) && lrc.bottom < (s32)((f32)tnHeightDesired * 1.25f) && lrc.right < (s32)((f32)tnWidthDesired * 1.25f)); lnI++)
		{
			// Grab this font
			font = iFont_create(tcFontName, tnFontSize + lnI, lnFontBold, tnFontItalic, tnFontUnderline);

			// Find out how big this font would be drawn for this text
			SetRect(&lrc, 0, 0, 0, 0);
			DrawText(font->hdc, tcText, lnTextLength, &lrc, DT_CALCRECT);
			size[lnI].fWidth	= (f32)(lrc.right - lrc.left);
			size[lnI].fHeight	= (f32)(lrc.bottom - lrc.top);
		}
		// When we get here, we have all of the fonts computed
		// size[0] contains the raw font
		// We search for size[1..N] which has the font which most closely matches its proportions for the tnWidthDesired, tnHeightDesired,
		// as per the ratio 

		// Compute the size[0]
		lfRatioH	= (f64)(size[0].fWidth)  / (f64)tnWidth;
		lfRatioV	= (f64)(size[0].fHeight) / (f64)tnHeight;

		// Search backwards to find the first one that matches
		for (lnJ = lnI - 1; lnJ > 0; lnJ--)
		{
			if ((s32)size[lnJ].fWidth <= (s32)tnWidthDesired && (s32)size[lnJ].fHeight <= (s32)tnHeightDesired)
			{
				// Calculate this item's size
				lfRatioHThis	= (f64)(size[lnJ].fWidth)  / (f64)tnWidthDesired;
				lfRatioVThis	= (f64)(size[lnJ].fHeight) / (f64)tnHeightDesired;

				// See if we've found our font
				if (lfRatioHThis <= lfRatioH && lfRatioVThis <= lfRatioV)
					return(tnFontSize + (u32)lnJ);
			}
		}
		// If we get here, we couldn't find one ... indicate failure
		return(0);
	}




//////////
//
// Called to process the mouse messages.
//
//////
	s32 iMouse_processMessage(SWindow* win, UINT m, WPARAM w, LPARAM l)
	{
		//////////
		// If we're a valid window, process the mouse
		//////
			if (win && win->obj && win->obj->sub_obj && win->obj->rc.right > win->obj->rc.left)
			{
				// Translate the mouse from the scaled position to its real position
				iiMouse_translatePosition(win, (POINTS*)&l);

				// Signal the event(s)
				if (win->isMouseInClientArea)		return(iiMouse_processMouseEvents_client(win, m, w, l));			// In the client area
				else								return(iiMouse_processMouseEvents_nonclient(win, m, w, l));		// In the non-client area
			}
			// If we get here, invalid
			return(-1);
	}




//////////
//
// Called to translate the mouse position for the source window.
// Note:  The win parameter is required.
//
//////
	void iiMouse_translatePosition(SWindow* win, POINTS* pt)
	{
		SSubObjForm*	form;
		POINT			lpt;


		//////////
		// Grab the related form object
		//////
			form = (SSubObjForm*)win->obj->sub_obj;


		//////////
		// If we're moving or resizing, we're reading screen coordinate mouse data
		//////
			if (win->isMoving || win->isResizing)
				GetCursorPos(&lpt);		// Get the mouse pointer in screen coordinates


		//////////
		// Translate our SHORT points structure to the LONG point structure
		//////
			lpt.x						= pt->x;
			lpt.y						= pt->y;
			win->mousePosition.x		= lpt.x;
			win->mousePosition.y		= lpt.y;


		//////////
		// If we're moving or resizing, we're reading screen coordinate mouse data
		//////
			if (win->isMoving || win->isResizing)
				return;

		
		//////////
		// Store the mouse position on the form in form coordinates
		//////
			win->mouseLastPosition.x	= lpt.x -= (SHORT)form->rcClient.left;
			win->mouseLastPosition.y	= lpt.x -= (SHORT)form->rcClient.top;


		//////////
		// Are we inside the client area?
		//////
			if (PtInRect(&form->rcClient, lpt))
			{
				// Yes
				win->isMouseInClientArea	= true;

				// Update our caller for the translated point
				pt->x	= (s16)win->mousePosition.x;
				pt->y	= (s16)win->mousePosition.y;

			} else {
				// We're not in the client area
				win->isMouseInClientArea	= false;
				win->isMouseInClientArea	= false;
			}
	}




//////////
//
// Process the mouse events in the client area for this form
//
//////
	s32 iiMouse_processMouseEvents_client(SWindow* win, UINT m, WPARAM w, LPARAM l)
	{
		s32				lnResult;
		SObject*		obj;
		SSubObjForm*	form;


		//////////
		// Grab our pointers
		//////
			obj		= win->obj;
			form	= (SSubObjForm*)obj->sub_obj;


		//////////
		// Iterate through objects to see where it is the mouse is traipsing
		//////


		// Indicate our status
		lnResult = 0;
		return(lnResult);
	}




//////////
//
// Process the mouse events in the non-client area for this form
//
//////
	s32 iiMouse_processMouseEvents_nonclient(SWindow* win, UINT m, WPARAM w, LPARAM l)
	{
		s32				lnResult, lnDeltaX, lnDeltaY, lnWidth, lnHeight, lnLeft, lnTop;
		bool			llCtrl, llAlt, llShift, llLeft, llRight, llMiddle, llCaps;
		SObject*		obj;
		SSubObjForm*	form;
		RECT			lrc;
		POINT			pt, ptScreen;


		//////////
		// Grab our pointers
		//////
			obj		= win->obj;
			form	= (SSubObjForm*)obj->sub_obj;


		//////////
		// Determine mouse button and keyboard key attributes
		//////
			iiMouse_getFlags(&llCtrl, &llAlt, &llShift, &llLeft, &llMiddle, &llRight, &llCaps);


		//////////
		// Iterate through the known objects
		//////
			pt.x = win->mouseLastPosition.x;
			pt.y = win->mouseLastPosition.y;

			// They clicked on something
			if (m == WM_LBUTTONDOWN)
			{
				// Close button
				if (PtInRect(&form->rcClose, pt))
				{
					// Send the quit message
					PostQuitMessage(0);

				// Minimize button
				} else if (PtInRect(&form->rcMinimize, pt)) {
					// Minimize the window
					CloseWindow(win->hwnd);

				} else {
					// The mouse has gone down in a nonclient area.
					// Note where the mouse went down in case they are beginning a move.
					win->mousePositionClick.x = pt.x;
					win->mousePositionClick.y = pt.y;

					// Get the current mouse position
					GetCursorPos(&ptScreen);
					win->mousePositionClickScreen.x = ptScreen.x;
					win->mousePositionClickScreen.y = ptScreen.y;
				}

			} else if (m == WM_MOUSEMOVE) {
				// The mouse is moving
				if (win->isMoving)
				{
					// Update to the new position
					// Get the current mouse position
					GetCursorPos(&ptScreen);

					// Determine the deltas
					lnDeltaX = ptScreen.x - win->mousePositionClickScreen.x;
					lnDeltaY = ptScreen.y - win->mousePositionClickScreen.y;

					// Position the window at that delta
					GetWindowRect(win->hwnd, &lrc);

					// It has moved since the last positioning
					SetWindowPos(win->hwnd, NULL,
									obj->rc.left + lnDeltaX,
									obj->rc.top + lnDeltaY,
									obj->rc.right  - obj->rc.left,
									obj->rc.bottom - obj->rc.top,
									SWP_NOSIZE | SWP_NOREPOSITION);

				} else if (win->isResizing) {
					// Update to the new size

				} else if (!glIsMoving && !glIsResizing) {
					// They may be beginning a move or resize
					if (llLeft)
					{
						// Did they move in a button?
						if (!(PtInRect(&form->rcIcon, pt) || PtInRect(&form->rcMove, pt) || PtInRect(&form->rcMinimize, pt) || PtInRect(&form->rcMaximize, pt) || PtInRect(&form->rcClose, pt)))
						{
							// Nope.  Are they moving in a resizing arrow?
							if (PtInRect(&form->rcArrowUl, pt) || PtInRect(&form->rcArrowUr, pt) || PtInRect(&form->rcArrowLl, pt) || PtInRect(&form->rcArrowLr, pt))
							{
								// We are beginning a resize
								win->isResizing	= true;
								glIsResizing	= true;
								SetCapture(win->hwnd);
// TODO:  write the resizing code

							} else {
								// We are beginning a move
								win->isMoving	= true;
								glIsMoving		= true;
								SetCapture(win->hwnd);
							}
						}
					}
				}

			} else if (m == WM_LBUTTONUP) {
				// They've released the mouse
				if (win->isMoving)
				{
					// We're done moving
					win->isMoving	= false;
					glIsMoving		= false;
					ReleaseCapture();

					// Get the current mouse position
					GetCursorPos(&ptScreen);

					// Determine the deltas
					lnDeltaX = ptScreen.x - win->mousePositionClickScreen.x;
					lnDeltaY = ptScreen.y - win->mousePositionClickScreen.y;

					// Position the window finally
					lnWidth		= obj->rc.right  - obj->rc.left;
					lnHeight	= obj->rc.bottom - obj->rc.top;
					lnLeft		= obj->rc.left   + lnDeltaX;
					lnTop		= obj->rc.top    + lnDeltaY;
					SetRect(&obj->rc, lnLeft, lnTop, lnLeft + lnWidth, lnTop + lnHeight);

					// Position the window at that delta
					SetWindowPos(win->hwnd, NULL, lnLeft, lnTop, lnWidth, lnHeight, SWP_NOSIZE | SWP_NOREPOSITION);

				} else if (win->isResizing) {
					// We're done resizing
					win->isResizing = false;
					glIsResizing	= false;
					ReleaseCapture();

				} else {
					// The mouse is simply released.  How nice. :-)
					win->isMoving	= false;
					win->isResizing = false;
					glIsMoving		= false;
					glIsResizing	= false;
				}
			}


		// Indicate our status
		lnResult = 0;
		return(lnResult);
	}




//////////
//
// Based upon the WPARAM we determine the keys, except Alt, which is
// determined by the VK_MENU key's current state.
//
//////
	void iiMouse_getFlags(bool* tlCtrl, bool* tlAlt, bool* tlShift, bool* tlLeft, bool* tlMiddle, bool* tlRight, bool* tlCaps)
	{
// 		//////////
// 		// If we had WPARAM, we could use these:
// 		//////
// 			*tlCtrl		= ((w & MK_CONTROL)		!= 0);
// 			*tlAlt		= (GetKeyState(VK_MENU)	< 0);
// 			*tlShift	= ((w & MK_SHIFT)		!= 0);
// 			*tlLeft		= ((w & MK_LBUTTON)		!= 0);
// 			*tlRight	= ((w & MK_RBUTTON)		!= 0);
// 			*tlMiddle	= ((w & MK_MBUTTON)		!= 0);


		//////////
		// Grab each one asynchronously
		//////
			*tlCtrl		= ((GetAsyncKeyState(VK_CONTROL)	& 0x8000)	!= 0);
			*tlAlt		= (GetKeyState(VK_MENU)							< 0);
			*tlShift	= ((GetAsyncKeyState(VK_SHIFT)		& 0x8000)	!= 0);
			*tlLeft		= ((GetAsyncKeyState(VK_LBUTTON)	& 0x8000)	!= 0);
			*tlMiddle	= ((GetAsyncKeyState(VK_MBUTTON)	& 0x8000)	!= 0);
			*tlRight	= ((GetAsyncKeyState(VK_RBUTTON)	& 0x8000)	!= 0);
			*tlCaps		= (GetAsyncKeyState(VK_CAPITAL)		& 0x8000)	!= 0;
	}




//////////
//
// Process the indicated keystroke
//
//////
	s32 iKeyboard_processMessage(SWindow* win, UINT m, WPARAM vKey, LPARAM tnScanCode)
	{
		s16		lnAsciiChar;
		u32		lnScanCode;
		bool	llCtrl, llAlt, llShift, llLeft, llMiddle, llRight, llCaps, llIsAscii;
		u8		keyboardState[256];


		//////////
		// Grab our key states
		//////
			iiMouse_getFlags(&llCtrl, &llAlt, &llShift, &llLeft, &llMiddle, &llRight, &llCaps);


		//////////
		// See if it's a printable character
		//////
			lnScanCode	= (tnScanCode & 0xff000) >> 12;
			lnAsciiChar	= 0;
			GetKeyboardState(&keyboardState[0]);
			llIsAscii	= (ToAscii(vKey, lnScanCode, &keyboardState[0], (LPWORD)&lnAsciiChar, 0) >= 1);


		//////////
		// Are we already inputting?
		// If not, and it's a printable character, we can start
		//////
			if (!llCtrl && !llShift && !llAlt)
			{
				// Regular key without special flags
				switch (vKey)
				{
					case VK_F6:
					case VK_F10:
						// Execute this line of code
						if (commandHistory && commandHistory->ecCursorLine && commandHistory->ecCursorLine->sourceCodePopulated > 0 && iEngine_executeStandaloneCommand(commandHistory->ecCursorLine))
							iWindow_render(gWinScreen);

						// Move to next line and redraw
						if (iEditChainManager_navigate(commandHistory, win->obj, 1, -commandHistory->column))
							iWindow_render(win);
						break;

					case VK_UP:
						if (iEditChainManager_navigate(commandHistory, win->obj, -1, 0))
							iWindow_render(win);
						return(1);

					case VK_DOWN:
						if (iEditChainManager_navigate(commandHistory, win->obj, 1, 0))
							iWindow_render(win);
						return(1);

					case VK_PRIOR:		// Page up
						if (iEditChainManager_navigatePages(commandHistory, win->obj, -1))
							iWindow_render(win);
						return(1);

					case VK_NEXT:		// Page down
						if (iEditChainManager_navigatePages(commandHistory, win->obj, 1))
							iWindow_render(win);
						return(1);

					case VK_ESCAPE:		// They hit escape, and are cancelling the input
						if (iEditChainManager_clearLine(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_TAB:
						if (iEditChainManager_tabIn(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_RETURN:
						//////////
						// Are we on the last line?
						//////
							if (commandHistory && commandHistory->ecCursorLine && !commandHistory->ecCursorLine->ll.next && commandHistory->ecCursorLine->sourceCodePopulated > 0 && iEngine_executeStandaloneCommand(commandHistory->ecCursorLine))
								iWindow_render(gWinScreen);


						//////////
						// Draw it like normal
						//////
							if (iEditChainManager_returnKey(commandHistory, win->obj))
								iWindow_render(win);

						return(1);

					case VK_LEFT:
						if (iEditChainManager_navigate(commandHistory, win->obj, 0, -1))
							iWindow_render(win);
						return(1);

					case VK_RIGHT:
						if (iEditChainManager_navigate(commandHistory, win->obj, 0, 1))
							iWindow_render(win);
						return(1);

					case VK_HOME:
						if (iEditChainManager_navigate(commandHistory, win->obj, 0, -(commandHistory->column)))
							iWindow_render(win);
						return(1);

					case VK_END:
						if (commandHistory->column != commandHistory->ecCursorLine->sourceCodePopulated)
						{
							iEditChainManager_navigate(commandHistory, win->obj, 0, commandHistory->ecCursorLine->sourceCodePopulated - commandHistory->column);
							iWindow_render(win);
						}
						return(1);

					case VK_INSERT:
						if (iEditChainManager_toggleInsert(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_BACK:
						if (iEditChainManager_deleteLeft(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_DELETE:
					if (iEditChainManager_deleteRight(commandHistory, win->obj))
							iWindow_render(win);
						return(1);
				}

			} else if (llCtrl && !llShift && !llAlt) {
				// CTRL+
				switch (vKey)
				{
					case 'A':		// Select all
						if (iEditChainManager_selectAll(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case 'X':		// Cut
						if (iEditChainManager_cut(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case 'C':		// Copy
						if (iEditChainManager_copy(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case 'V':		// Paste
						if (iEditChainManager_paste(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case 'W':		// Save and close
						break;

					case 'Q':		// Quit
						break;

					case VK_LEFT:	// Word left
						if (iEditChainManager_navigateWordLeft(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_RIGHT:	// Word right
						if (iEditChainManager_navigateWordRight(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_HOME:	// Home (go to top of content)
						if (iEditChainManager_navigateTop(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_END:	// Page down (go to end of content)
						if (iEditChainManager_navigateEnd(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_BACK:
						if (iEditChainManager_deleteWordLeft(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_DELETE:
						if (iEditChainManager_deleteWordRight(commandHistory, win->obj))
							iWindow_render(win);
						return(1);
				}

			} else if (!llCtrl && llShift && !llAlt) {
				// SHIFT+
				switch (vKey)
				{
					case VK_UP:		// Select line up
						if (iEditChainManager_selectLineUp(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_DOWN:	// Select line down
						if (iEditChainManager_selectLineDown(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_LEFT:	// Select left
						if (iEditChainManager_selectLeft(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_RIGHT:	// Select right
						if (iEditChainManager_selectRight(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_END:	// Select to end
						if (iEditChainManager_selectToEndOfLine(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_HOME:	// Select to start
						if (iEditChainManager_selectToBeginOfLine(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_TAB:	// Shift tab
						if (iEditChainManager_tabOut(commandHistory, win->obj))
							iWindow_render(win);
						return(1);
				}

			} else if (!llCtrl && !llShift && llAlt) {
				// ALT+
				switch (vKey)
				{
					case 'K':		// Select column mode
						if (iEditChainManager_selectColumnToggle(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case 'L':		// Select full line mode
						if (iEditChainManager_selectLineToggle(commandHistory, win->obj))
							iWindow_render(win);
						return(1);
				}

			} else if (llCtrl && llShift && !llAlt) {
				// CTRL+SHIFT+
				switch (vKey)
				{
					case VK_LEFT:	// Select word left
						if (iEditChainManager_selectWordLeft(commandHistory, win->obj))
							iWindow_render(win);
						return(1);

					case VK_RIGHT:	// Select word right
						if (iEditChainManager_selectWordRight(commandHistory, win->obj))
							iWindow_render(win);
						return(1);
				}

			} else if (llCtrl && !llShift && llAlt) {
				// CTRL+ALT+

			} else if (!llCtrl && llShift && llAlt) {
				// SHIFT+ALT

			} else if (llCtrl && llShift && llAlt) {
				// CTRL+ALT+SHIFT+
			}

			// If we get here, it wasn't processed above.  Try to stick it in the buffer
			if (llIsAscii)
			{
				// It's a regular input key
				if (iEditChainManager_keystroke(commandHistory, win->obj, (u8)lnAsciiChar))
					iWindow_render(win);
				return(1);
			}


		// All done
		return(0);
	}




//////////
//
// Added to do a simple top-down translation of the pointers from p1 to p2.
//
//////
	void* iTranslate_p1_to_p2(SBuilder* root, void* ptr)
	{
		u32				lnI, lnCount;
		STranslate*		xlat;


// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
		//////////
		// Iterate in a top-down manner
		//////
			lnCount	= root->populatedLength / sizeof(STranslate);
			xlat	= (STranslate*)root->data;
			for (lnI = 0; lnI < lnCount; lnI++, xlat++)
			{
				// See if this translation is the translation
				if (xlat->p1 == ptr)
					return(xlat->p2);		// Yes
			}
			// If we get here, not found


		//////////
		// Indicate failure
		//////
			return(NULL);
	}

	void* iTranslate_p2_to_p1(SBuilder* root, void* ptr)
	{
		u32				lnI, lnCount;
		STranslate*		xlat;


// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
		//////////
		// Iterate in a top-down manner
		//////
			lnCount = root->populatedLength / sizeof(STranslate);
			xlat	= (STranslate*)root->data;
			for (lnI = 0; lnI < lnCount; lnI++, xlat++)
			{
				// See if this translation is the translation
				if (xlat->p2 == ptr)
					return(xlat->p1);		// Yes
			}
			// If we get here, not found


		//////////
		// Indicate failure
		//////
			return(NULL);
	}




//////////
//
// Called to free the extra info associated with this entry
//
//////
	void iExtraInfo_free(SEditChainManager* ecm, SEditChain* ec, SExtraInfo** root, bool tlDeleteSelf)
	{
		SExtraInfo*		ei;
		SExtraInfo*		eiNext;


// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
_asm int 3;
		// Make sure our environment is sane
		if (root && *root)
		{
			// Iterate through all entries in the chain
			ei = *root;
			while (ei)
			{
				//////////
				// Note the next entry
				//////
					ei = ei->next;


				//////////
				// Free the data contained within
				// Note:  If they have an extra_info_free() function defined, we need to call it first so they can release whatever is contained within the info block
				//////
					if (*(u32*)&ei->extra_info_free != 0)
					{
						// Free anything within using the callback
						ei->extra_info_free(NULL, ec, ei);
						// At this point we anything it had inside is now free
					}

					// Now, manually free the actual info block itself
					iDatum_delete(&ei->info, false);


				//////////
				// Free self if need be
				//////
					if (tlDeleteSelf)
						free(ei);


				//////////
				// Move to next entry
				//////
					ei = eiNext;
			}
		}
	}




//////////
//
// Datum storage
//
//////
	void iDatum_allocateSpace(SDatum* datum, s32 dataLength)
	{
		// Make sure our environment is sane
		if (datum)
		{
			if (datum->length != dataLength)
			{
				// Release anything that's already there
				iiDatum_delete(datum);

				// Allocate the space
				if (dataLength > 0)
					datum->data = (s8*)malloc(dataLength);

				// Set the length
				datum->length = dataLength;
			}

			// Initialize
			if (datum->data)
				memset(datum->data, 0, dataLength);
		}
	}

	SDatum* iDatum_allocate(s8* data, s32 dataLength)
	{
		SDatum* datumNew;


		// Allocate our new datum
		datumNew = (SDatum*)malloc(sizeof(SDatum));
		if (datumNew)
		{
			// Initialize
			memset(datumNew, 0, sizeof(SDatum));

			if (data && dataLength)
			{
				// We may need to set the length
				if (dataLength < 1)
					dataLength = max(strlen(data), 1);

				// Initialize
				memset(datumNew, 0, sizeof(SDatum));

				// Populate
				iDatum_duplicate(datumNew, data, dataLength);
			}
		}

		// Indicate our status
		return(datumNew);
	}

	void iDatum_duplicate(SDatum* datum, s8* data, s32 dataLength)
	{
		// Make sure our environment is sane
		if (datum && data)
		{
			// We may need to set the length
			if (dataLength < 1)
				dataLength = max(strlen(data), 1);

			// Release anything that's already there
			iiDatum_delete(datum);

			// Store the new data
			datum->data = (s8*)malloc(dataLength);

			// Copy over if we were successful
			if (datum->data)
			{
				memcpy(datum->data, data, dataLength);
				datum->length = dataLength;
			}
		}
	}

	void iDatum_duplicate(SDatum* datum, cs8* data, s32 dataLength)
	{
		iDatum_duplicate(datum, (s8*)data, dataLength);
	}

	void iDatum_duplicate(SDatum* datumDst, SDatum* datumSrc)
	{
		// Make sure our environment is sane
		if (datumDst && datumSrc && datumSrc->data)
			iDatum_duplicate(datumDst, datumSrc->data, datumSrc->length);
	}

	bool iDatum_resize(SDatum* datum, s32 newDataLength)
	{
		s8* ptr;


		// Make sure our environment is sane
		if (datum && newDataLength != 0)
		{
			if (datum->length == newDataLength)
				return(true);		// It's already the same length

			// Allocate our new block
			ptr = (s8*)malloc(newDataLength);
			if (ptr)
			{
				// Copy everything that will fit
				memcpy(ptr, datum->data, min(newDataLength, datum->length));

				// Fill the remainder with NULLs if any
				if (newDataLength > datum->length)
					memset(ptr + datum->length, 0, newDataLength - datum->length);

				// Delete the old data
				if (datum->data)
					free(datum->data);

				// And populate with the new data
				datum->data		= ptr;
				datum->length	= newDataLength;

				// All done
				return(true);

			} else {
				// Failure
				return(false);
			}

		} else {
			// No data to work with
			return(false);
		}
	}

	// Returns -1, 0, or 1 (indicating left is less than, equal to, or greater than right)
	s32 iDatum_compare(SDatum* datumLeft, SDatum* datumRight)
	{
		s32 lnResult;


		// Default to invalid data
		lnResult = -2;

		// Make sure our environment is sane
		if (datumLeft && datumRight)
		{
			// Do a standard compare
			lnResult = memcmp(datumLeft->data, datumRight->data, min(datumLeft->length, datumRight->length));
		}

		// Indicate our result
		return(lnResult);
	}

	void iDatum_delete(SDatum* datum, bool tlDeleteSelf)
	{
		// Make sure our environment is sane
		if (datum)
		{
			// Delete the content
			iiDatum_delete(datum);

			// Delete self if need be
			if (tlDeleteSelf)
				free(datum);
		}
	}

	void iiDatum_delete(SDatum* datum)
	{
		// Make sure our environment is sane
		if (datum->data)
		{
			free(datum->data);
			datum->data = NULL;
		}

		// Reset the length to zero
		datum->length = 0;
	}
