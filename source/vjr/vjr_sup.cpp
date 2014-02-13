//////////
//
// /libsf/source/vjr/vjr_sup.cpp
//
//////
// Version 0.10
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




void initialize(HACCEL* hAccelTable)
{
	HRESULT hRes;


	// Keyboard shortcuts
	*hAccelTable = LoadAccelerators(ghInstance, MAKEINTRESOURCE(IDC_VJR));



	// Taskbar interface
	hRes = OleInitialize(NULL);
	CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void**)&giTaskbar);


	// Initialize our builder
	builder_createAndInitialize(&gWindows,	-1);
	builder_createAndInitialize(&gFonts,	-1);


	// Get startup time
	systemStartedMs = iGetLocalTimeMs();


	// Load our images
	iLoadObject(&winIface.appIcon,				cgc_appIconBmp,					cgc_appIconBmp);
	iLoadObject(&winIface.minimize,				cgc_minimizeBmp,				cgc_minimizeOverBmp);
	iLoadObject(&winIface.maximize,				cgc_maximizeBmp,				cgc_maximizeOverBmp);
	iLoadObject(&winIface.close,				cgc_closeBmp,					cgc_closeOverBmp);
	iLoadObject(&winIface.arrowUl,				cgc_arrowUlBmp,					cgc_arrowUlOverBmp);
	iLoadObject(&winIface.arrowUr,				cgc_arrowUrBmp,					cgc_arrowUrOverBmp);
	iLoadObject(&winIface.arrowLr,				cgc_arrowLrBmp,					cgc_arrowLrOverBmp);
	iLoadObject(&winIface.arrowLl,				cgc_arrowLlBmp,					cgc_arrowLlOverBmp);


	// Create our message window
	iCreateMessageWindow();
	iCreateInterfaceWindow();
}




//////////
//
// Called to load a bitmap file that was loaded from disk, or simulated loaded from disk.
//
//////
	void iLoadObject(SObject* obj, const u8* bmpRawFileData, const u8* bmpRawFileDataOver)
	{
		BITMAPFILEHEADER*	bh;
		BITMAPINFOHEADER*	bi;


		//////////
		// Grab the headers
		//////
			bh = (BITMAPFILEHEADER*)bmpRawFileData;
			bi = (BITMAPINFOHEADER*)(bh + 1);


		//////////
		// Initialize the bitmap, and populate
		//////
			memset(&obj->bmp, 0, sizeof(SBitmap));
			memcpy(&obj->bmp.bh, bh, sizeof(obj->bmp.bh));
			memcpy(&obj->bmp.bi, bi, sizeof(obj->bmp.bi));
			obj->bmp.bd			= (s8*)(bmpRawFileData + bh->bfOffBits);
			obj->bmp.rowWidth	= iComputeRowWidth(&obj->bmp);
			if (obj->bmp.bi.biBitCount == 24)
				iConvertBitmapTo32Bits(&obj->bmp);


		//////////
		// Initialize the bitmap for when the mouse is over the control, and populate
		//////
			bh = (BITMAPFILEHEADER*)bmpRawFileDataOver;
			bi = (BITMAPINFOHEADER*)(bh + 1);


		//////////
		// Initialize the bitmap and populate
		//////
			memset(&obj->bmpOver, 0, sizeof(SBitmap));
			memcpy(&obj->bmpOver.bh, bh, sizeof(obj->bmpOver.bh));
			memcpy(&obj->bmpOver.bi, bi, sizeof(obj->bmpOver.bi));
			obj->bmpOver.bd			= (s8*)(bmpRawFileDataOver + bh->bfOffBits);
			obj->bmpOver.rowWidth	= iComputeRowWidth(&obj->bmpOver);
			if (obj->bmpOver.bi.biBitCount == 24)
				iConvertBitmapTo32Bits(&obj->bmpOver);
	}

	void iConvertBitmapTo32Bits(SBitmap* bmp)
	{
		SBitmap bmp32;


		// Are we already there?
		if (bmp && bmp->bi.biBitCount != 32)
		{
			// No, but we only know how to handle 24-bit bitmaps
			if (bmp->bi.biBitCount == 24)
			{
				// We need to convert it
				// Create the 32-bit version
				iPopulateAndCreateBitmap(&bmp32, bmp->bi.biWidth, bmp->bi.biHeight);

				// Copy it
				iCopyBitmap24ToBitmap32(&bmp32, bmp);

				// Free the (now old) bitmap
				iDeleteBitmap(bmp);

				// Copy our bitmap to the destination
				memcpy(bmp, &bmp32, sizeof(SBitmap));
			}
		}
	}

	// Assumes both bitmaps are the same size
	void iCopyBitmap24ToBitmap32(SBitmap* bmp32, SBitmap* bmp24)
	{
		s32		lnX, lnY;
		SBGR*	lbgr;
		SBGRA*	lbgra;


		// Iterate through every row
		for (lnY = 0; lnY < bmp24->bi.biHeight; lnY++)
		{
			// Grab our pointers
			lbgr	= (SBGR*)(bmp24->bd  + ((bmp24->bi.biHeight - lnY - 1) * bmp24->rowWidth));
			lbgra	= (SBGRA*)(bmp32->bd + ((bmp32->bi.biHeight - lnY - 1) * bmp32->rowWidth));

			// Iterate though every column
			for (lnX = 0; lnX < bmp24->bi.biWidth; lnX++, lbgr++, lbgra++)
			{
				// Copy the pixel
				lbgra->alp	= 255;
				lbgra->red	= lbgr->red;
				lbgra->grn	= lbgr->grn;
				lbgra->blu	= lbgr->blu;
			}
		}
	}

	void iDeleteBitmap(SBitmap* bmp)
	{
		if (bmp->hbmp)
		{
			DeleteObject((HGDIOBJ)bmp->hbmp);
			bmp->hbmp = NULL;
		}

		if (bmp->hdc)
		{
			DeleteDC(bmp->hdc);
			bmp->hdc = NULL;
		}
	}




//////////
//
// Creates the message window used for communicating actions
//
//////
	void iCreateMessageWindow(void)
	{
		ATOM			atom;
		WNDCLASSEXA		classa;


		//////////
		// Register the class if need be
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
					classa.lpfnWndProc			= &iWndProc_messageWindow;

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
	LRESULT CALLBACK iWndProc_messageWindow(HWND hwnd, UINT m, WPARAM w, LPARAM l)
	{
		SWindow* win;


		// Is it an internal message?
		if (isValidWindow(w))
		{
			// Yes, explore the possibilities
			win = (SWindow*)w;
			if (win->slotUsed)
			{
// TODO:  receive message window messages
// 				switch (m)
// 				{
// 					case WMU_NEW_WINDOW:
// 						// A new window has been added from the user
// 						iRedrawAll();			// Redraw windows, which will include this tab now
// 						// All done!
// 						break;
// 				}
			}
			// Indicate we've processed this message
			return 0;
		}
		// Call Windows' default procedure handler
		return(DefWindowProc(hwnd, m, w, l));
	}




//////////
//
// Called to find or create the KSI interface window
//
//////
	HWND iCreateInterfaceWindow(void)
	{
		s32				lnLeft, lnTop;
		ATOM			atom;
		WNDCLASSEXA		classa;
		RECT			lrc;
		SFont*			font;
		SSize			client, nonclient, overall;


		//////////
		// Register the class if need be
		//////
			while (1)
			{
				if (!GetClassInfoExA(ghInstance, cgcInterfaceWindowClass, &classa))
				{
					// Initialize
					memset(&classa, 0, sizeof(classa));

					// Populate
					classa.cbSize				= sizeof(WNDCLASSEXA);
					classa.hInstance			= ghInstance;
					classa.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
					classa.lpszClassName		= cgcInterfaceWindowClass;
					classa.hIcon				= LoadIcon(ghInstance, MAKEINTRESOURCE(IDI_VJR));
//					classa.lpszMenuName			= MAKEINTRESOURCE(IDC_VJR);
					classa.lpfnWndProc			= &iWndProc_interfaceWindow;

					// Register
					atom = RegisterClassExA(&classa);
					if (!atom)
						break;
				}


			//////////
			// Find out how big the window should be
			//////
				iComputeWindowClientAreaDimensions(&client);
				iComputeWindowNonclientAreaDimensions(&nonclient);
				overall.width	= client.width + nonclient.width;
				overall.height	= client.height + nonclient.width;
				iAdjustInterfaceWindowDimensions(&overall);


			//////////
			// Physically create the interface window
			//////
				GetWindowRect(GetDesktopWindow(), &lrc);
				lnLeft	= ((lrc.right - lrc.left) - overall.width)  / 2;
				lnTop	= ((lrc.bottom - lrc.top) - overall.height) / 2;
				ghwndIface	= CreateWindowA(cgcInterfaceWindowClass, cgcTitle, WS_POPUP, lnLeft, lnTop, overall.width, overall.height, NULL, NULL, ghInstance, 0);
				if (ghwndIface)
				{
					///////////
					// Read events from the window
					//////
						CreateThread(NULL, 0, &iReadEvents_interfaceWindow, 0, 0, 0);


					//////////
					// Create the fonts
					//////
						font					= iCreateFont(cgcTahoma, 10,	FW_SEMIBOLD, false, false);
						winIface.fontCaption	= iDuplicateFont(font);
						font					= iCreateFont(cgcTahoma, 8,		FW_SEMIBOLD, false, false);
						winIface.fontTabs		= iDuplicateFont(font);


					//////////
					// Draw the initial window state
					//////
						iResizeInterfaceWindow(true);


					//////////
					// Make it visible
					//////
						SetWindowPos(ghwndIface, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
						ShowWindow(ghwndIface, SW_SHOW);


					// All done
					return(ghwndIface);
				}
				break;
			}
			// We should never get here
			MessageBoxA(NULL, "Error creating KSI interface window.", "KSI - Fatal Error", MB_OK);
			return(NULL);
	}




//////////
//
// Called to create a DIB section bitmap based on size and the indicated information
//
//////
	void iPopulateAndCreateBitmap(SBitmap* bmp, int tnWidth, int tnHeight)
	{
		//////////
		// Header
		//////
			bmp->bh.bfType			= 'MB';
			bmp->bh.bfOffBits		= sizeof(bmp->bh) + sizeof(bmp->bi);
			bmp->bh.bfReserved1		= 0;
			bmp->bh.bfReserved2		= 0;


		//////////
		// Info
		//////
			bmp->bi.biSize			= sizeof(bmp->bi);
			bmp->bi.biWidth			= tnWidth;
			bmp->bi.biHeight		= tnHeight;
			bmp->bi.biPlanes		= 1;
			bmp->bi.biBitCount		= 32;
			bmp->bi.biXPelsPerMeter	= 3270;
			bmp->bi.biYPelsPerMeter	= 3270;
			bmp->bi.biCompression	= 0;
			bmp->bi.biClrImportant	= 0;
			bmp->bi.biClrUsed		= 0;
			bmp->rowWidth			= iComputeRowWidth(bmp);
			bmp->bi.biSizeImage		= tnHeight * bmp->rowWidth;


		///////////
		// Set the overall size, and some parameters
		//////
			bmp->bh.bfSize			= bmp->bh.bfOffBits + bmp->bi.biSizeImage;


		//////////
		// Create handles
		//////
			bmp->hdc				= CreateCompatibleDC(GetDC(GetDesktopWindow()));
			bmp->hbmp				= CreateDIBSection(bmp->hdc, (BITMAPINFO*)&bmp->bi, DIB_RGB_COLORS, (void**)&bmp->bd, NULL, 0);
			memset(bmp->bd, 0, bmp->bi.biSizeImage);
			SelectObject(bmp->hdc, bmp->hbmp);
	}




//////////
//
// Thread to handle interface window events
//
//////
	DWORD WINAPI iReadEvents_interfaceWindow(LPVOID lpParameter)
	{
		MSG msg;


		// Read until the message window goes bye bye
		while (GetMessage(&msg, ghwndIface, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// When we get here, we're shutting down
		return 0;
	}




//////////
//
// Called to resize the window if need be based upon new client size settings
//
//////
	void iResizeInterfaceWindow(bool tlForce)
	{
		SSize	client, nonclient, overall;


		//////////
		// Find out how big the window should be
		//////
			iComputeWindowClientAreaDimensions(&client);
			iComputeWindowNonclientAreaDimensions(&nonclient);
			overall.width	= client.width + nonclient.width;
			overall.height	= client.height + nonclient.width;
			iAdjustInterfaceWindowDimensions(&overall);

		
		//////////
		// If the window size is different than this, we need to resize it
		//////
// TODO:  need to determine the window's position during the resize, for lnTop, lnLeft
			iSetInterfaceWindowSize(0/*lnLeft*/, 0/*lnTop*/, overall.width, overall.height, tlForce);
	}




//////////
//
// Called to programmatically set the interface window size after a resize
//
//////
	void iSetInterfaceWindowSize(s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight, bool tlForce)
	{
		bool llChangedSomething;


		// Do we need to resize?
		if (!IsWindowVisible(ghwndIface) && !tlForce)
			return;

		// Begin resizing
		ShowWindow(ghwndIface, SW_RESTORE);
		llChangedSomething = tlForce;
		if (winIface.rc.right - winIface.rc.left != tnWidth || winIface.rc.bottom - winIface.rc.top != tnHeight)
		{
			// Yes
			llChangedSomething = true;
			SetWindowPos(ghwndIface, NULL, 0, 0, tnWidth, tnHeight,	SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOMOVE);
		}


		// Do we need to move?
		if (winIface.rc.left != tnLeft || winIface.rc.top != tnTop)
		{
			// Yes
			llChangedSomething = true;
			SetWindowPos(ghwndIface, NULL, tnLeft, tnTop, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOSIZE);
		}


		// Get the current size
		SetRect(&winIface.rc, tnLeft, tnTop, tnLeft + tnWidth, tnTop + tnHeight);


		// Did we change anything?
		if (llChangedSomething)
		{
			//////////
			// If there's already an image, release it
			//////
				DeleteObject((HGDIOBJ)winIface.bmp.hbmp);
				DeleteDC(winIface.bmp.hdc);
				memset(&winIface.bmp, 0, sizeof(SBitmap));


			//////////
			// Create the buffers for it
			//////
				winIface.bmp.hdc		= CreateCompatibleDC(GetDC(GetDesktopWindow()));
				winIface.bmp.hbmp		= iCreateBitmap(winIface.bmp.hdc, tnWidth, tnHeight, 1, 32, (void**)&winIface.bmp.bd, &winIface.bmp.bh, &winIface.bmp.bi);
				winIface.bmp.rowWidth	= iComputeRowWidth(&winIface.bmp);
				SelectObject(winIface.bmp.hdc, winIface.bmp.hbmp);


			//////////
			// Redraw the window
			//////
				GetClientRect(ghwndIface, &winIface.rcClient);
				iRedrawAll(&winIface);
		}
	}




//////////
//
// Create a bitmap of the indicated size, and create a DIB section for it
//
//////
	HBITMAP iCreateBitmap(HDC thdc, int tnWidth, int tnHeight, int tnPlanes, int tnBits, void** tbd, BITMAPFILEHEADER* tbh, BITMAPINFOHEADER* tbi)
	{
		BITMAPFILEHEADER	bf;
		BITMAPINFOHEADER	bi;
		BITMAPINFOHEADER*	lbi;
		HBITMAP				lhbmp;
		SBitmap				bmp;


		//////////
		// Use remote or local
		//////
			if (tbi)		lbi = tbi;		// Use caller's
			else			lbi = &bi;		// Use ours


		//////////
		// Create a new DIB (these parts are required for CreateDIBSection to work)
		//////
			memset(lbi, 0, sizeof(BITMAPINFOHEADER));
			lbi->biSize			= sizeof(BITMAPINFOHEADER);
			lbi->biWidth		= tnWidth;
			lbi->biHeight		= tnHeight;
			lbi->biPlanes		= tnPlanes;
			lbi->biBitCount		= tnBits;


		//////////
		// Populate caller parts (these parts are also required for disk files)
		//////
			if (tbi)
			{
				memcpy(&bmp.bi, tbi, sizeof(bmp.bi));
				lbi->biSizeImage		= iComputeRowWidth(&bmp) * tnHeight;
				lbi->biXPelsPerMeter	= 3270;
				lbi->biYPelsPerMeter	= 3270;
			}
			if (tbh)
			{
				tbh->bfType				= 'MB';
				tbh->bfReserved1		= 0;
				tbh->bfReserved2		= 0;
				tbh->bfOffBits			= sizeof(bf) + sizeof(bi);
				tbh->bfSize				= tbh->bfOffBits + tbi->biSizeImage;
			}


		//////////
		// Physically create the bitmap
		//////
			lhbmp = CreateDIBSection(thdc, (BITMAPINFO*)lbi, DIB_RGB_COLORS, tbd, NULL, 0);
			return(lhbmp);
	}




//////////
//
// Computes the row width of the pixels using BGR format (3 bytes per pixel) then rounded up to
// the nearest DWORD.
//
//////
	int iComputeRowWidth(SBitmap* bmp)
	{
		int lnWidth;


		// See the bit counts
		if (bmp->bi.biBitCount == 24)
		{
			// 24-bit formats are rounded up to nearest DWORD
			lnWidth = bmp->bi.biWidth * 3;
			if (lnWidth % 4 == 0)
				return(lnWidth);

			// Increase the width
			lnWidth += (4 - (lnWidth % 4));
			return(lnWidth);


		} else if (bmp->bi.biBitCount == 32) {
			// 32-bit formats are also DWORD aligned, but naturally, of course. :-)
			return(bmp->bi.biWidth * 4);


		} else {
			// Uh oh, spaghetti-oh!
			return(bmp->bi.biSizeImage / bmp->bi.biHeight);
		}
	}




//////////
//
// Processes messages from the interface window, to forward on to the original window
//
//////
	LRESULT CALLBACK iWndProc_interfaceWindow(HWND h, UINT m, WPARAM w, LPARAM l)
	{
// 		s32				id, event;
		HDC				lhdc;
		PAINTSTRUCT		ps;


		// See if we know this hwnd
		// It was one of our windows
		switch (m)
		{
// 			case WM_COMMAND:
// 				id    = LOWORD(w);
// 				event = HIWORD(w);
// 				// Parse the menu selections:
// 				switch (id)
// 				{
// 					case IDM_ABOUT:
// 						DialogBox(ghInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), h, About);
// 						break;
// 
// 					case IDM_EXIT:
// 						if (iShutdownPolitely())
// 							PostQuitMessage(0);
// 						break;
// 
// 					default:
// 						return DefWindowProc(h, m, w, l);
// 				}
// 				break;

			case WM_LBUTTONDOWN:
				PostQuitMessage(-1);
				break;
// 				glMouseLeftButton = true;
// 				return(iProcessMouseMessage(m, w, l));

			case WM_LBUTTONUP:
				if (glMoving || glResizing)
					ReleaseCapture();

				glMouseLeftButton = false;
				return(iProcessMouseMessage(m, w, l));

			case WM_RBUTTONDOWN:
				glMouseRightButton = true;
				return(iProcessMouseMessage(m, w, l));

			case WM_RBUTTONUP:
				glMouseRightButton = false;
				return(iProcessMouseMessage(m, w, l));

			case WM_MBUTTONDOWN:
				glMouseMiddleButton = true;
				return(iProcessMouseMessage(m, w, l));

			case WM_MBUTTONUP:
				glMouseMiddleButton = false;
				return(iProcessMouseMessage(m, w, l));

			case WM_RBUTTONDBLCLK:
			case WM_LBUTTONDBLCLK:
			case WM_MBUTTONDBLCLK:
			case WM_MOUSEHWHEEL:
			case WM_MOUSEWHEEL:
			case WM_MOUSEMOVE:
				glMouseLeftButton	= ((w & MK_LBUTTON) != 0);		// The left mouse button is down
				glMouseMiddleButton	= ((w & MK_MBUTTON) != 0);		// The middle mouse button is down
				glMouseRightButton	= ((w & MK_RBUTTON) != 0);		// The right mouse button is down
				return(iProcessMouseMessage(m, w, l));

			case WM_KEYDOWN:
			case WM_KEYUP:
//			case WM_CHAR:
//			case WM_DEADCHAR:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
//			case WM_SYSCHAR:
//			case WM_SYSDEADCHAR:
				return 0;

			case WM_CAPTURECHANGED:
				if (glMoving)
				{
					// Stop the movement
// TODO:					iStopMove();

				} else if (glResizing) {
					// Stop the resize
// TODO:					iStopResize();

				} else {
					// Make sure our flags are lowered
					glMoving	= false;
					glResizing	= false;
				}
				break;

			case WM_PAINT:
				// Paint it
				lhdc = BeginPaint(h, &ps);
				BitBlt(lhdc, 0, 0, winIface.bmp.bi.biWidth, winIface.bmp.bi.biHeight, winIface.bmp.hdc, 0, 0, SRCCOPY);
				EndPaint(h, &ps);
				return 0;
		}

		// Call Windows' default procedure handler
		return(DefWindowProc(h, m, w, l));
	}

	bool iShutdownPolitely(void)
	{
		return(true);
	}




//////////
//
// Compute the client area dimensions based on the current settings
//
//////
	void iComputeWindowClientAreaDimensions(SSize* size)
	{
		RECT lrc;


		//////////
		// Iterate through each item
		//////
			// Default to half the overall screen size
			GetWindowRect(GetDesktopWindow(), &lrc);
			size->width		= (lrc.right - lrc.left) / 2;
			size->height	= (lrc.bottom - lrc.top) / 2;

			// When we get here, they are set by value, either to the minimum, or to the maximum
			// Note:  They could be hugely too large.  The caller will have to deal with that.
	}

	void iComputeWindowNonclientAreaDimensions(SSize* size)
	{
		//////////
		// Set minimum dimensions
		//////
			size->width		= 8 + 8;		// left + right
			size->height	= 24 + 24;		// top + bottom
	}

	void iAdjustInterfaceWindowDimensions(SSize* size)
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
	s64 iComputeTimeMilliseconds(SYSTEMTIME* time)
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

	s64 iGetSystemTimeMs(void)
	{
		SYSTEMTIME time;
		GetSystemTime(&time);
		return(iComputeTimeMilliseconds(&time));
	}

	s64 iGetLocalTimeMs(void)
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		return(iComputeTimeMilliseconds(&time));
	}

	s64 iDiff(s64 tnBaseValue, s64 tnSubtractionValue)
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
	SFont* iDuplicateFont(SFont* fontSource)
	{
		SFont* font;


		// Make sure our environment is sane
		font = NULL;
		if (fontSource)
		{
			//////////
			// Allocate a new pointer
			//////
				font = (SFont*)malloc(sizeof(SFont));
				if (!font)
					return(font);


			//////////
			// Create a copy
			//////
				font->hdc					= CreateCompatibleDC(GetDC(GetDesktopWindow()));
				font->hfont					= CreateFont(fontSource->sizeUsedForCreateFont, 0, 0, 0, fontSource->weight, (fontSource->italics != 0), (fontSource->underline != 0), false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, fontSource->name);
				SelectObject(font->hdc, font->hfont);
				font->name					= iDuplicateString(fontSource->name);
				font->nameLength			= fontSource->nameLength;
				font->size					= fontSource->size;
				font->weight				= fontSource->weight;
				font->italics				= fontSource->italics;
				font->underline				= fontSource->underline;
				memcpy(&font->tm, &fontSource->tm, sizeof(font->tm));
		}
		// Indicate our success or failure
		return(font);
	}




//////////
//
// Create a new font
//
//////
	SFont* iCreateFont(cs8* tcFontName, u32 tnFontSize, u32 tnFontWeight, u32 tnItalics, u32 tnUnderline)
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
				if (font->size == tnFontSize && font->weight == tnFontWeight && font->italics == tnItalics && font->underline == tnUnderline && font->nameLength == lnLength)
					if (_memicmp(font->name, tcFontName, lnLength) == 0)
						return(font);
			}


		//////////
		// Allocate a new pointer
		//////
			font = (SFont*)builder_allocateBytes(gFonts, sizeof(SFont));
			if (!font)
				return(font);


		//////////
		// Populate
		//////
			font->hdc					= CreateCompatibleDC(GetDC(GetDesktopWindow()));
			font->sizeUsedForCreateFont	= -MulDiv(tnFontSize, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);
			font->hfont					= CreateFont(font->sizeUsedForCreateFont, 0, 0, 0, tnFontWeight, (tnItalics != 0), (tnUnderline != 0), false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, tcFontName);
			SelectObject(font->hdc, font->hfont);
			font->name					= iDuplicateString((s8*)tcFontName);
			font->nameLength			= lnLength;
			font->size					= tnFontSize;
			font->weight				= tnFontWeight;
			font->italics				= tnItalics;
			font->underline				= tnUnderline;

			// Find out the text metrics
			GetTextMetricsA(font->hdc, &font->tm);


		// Indicate our success
		return(font);
	}




//////////
//
// A particular font occupies a certain physical amount of text relative to the rectangle it inhabits.
// In order for this font to be scaled up, the font dynamics will need to change somewhat as per the limitations
// within the font design.  As such, we have to scan upward to find the closest matching font that is equal to
// or less than the ratios indicated at the current size, yet for the desired size.
//
//////
	u32 iFindClosestFontSizeMatch(s8* tcText, s8* tcFontName, u32 tnFontSize, u32 tnFontBold, u32 tnFontItalic, u32 tnFontUnderline, u32 tnWidth, u32 tnHeight, u32 tnWidthDesired, u32 tnHeightDesired)
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
			font = iCreateFont(tcFontName, tnFontSize + lnI, lnFontBold, tnFontItalic, tnFontUnderline);

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
	int iProcessMouseMessage(UINT m, WPARAM w, LPARAM l)
	{
		// Translate the mouse from the scaled position to its real position
		iTranslateMousePosition((POINTS*)&l);

		// If it's not in the client area, 
		if (glMouseInClientArea)
		{
			// It's in the client area

// TODO:			iProcessClientMouseEvents((POINTS*)&l);

		} else {
			// It's in the non-client area
// TODO:			iProcessNonclientMouseEvents((POINTS*)&l);
		}

		return 0;
	}




//////////
//
// Called to translate the mouse position for the source window.
//
//////
	void iTranslateMousePosition(POINTS* pt)
	{
		POINT lpt;


		//////////
		// If we're a valid window, process the mouse
		//////
			if (winIface.rc.right > winIface.rc.left)
			{
				// Get the mouse pointer in screen coordinates
				if (glMoving || glResizing)
					GetCursorPos(&lpt);

				// Translate our SHORT points structure to the LONG point structure
				lpt.x				= pt->x;
				lpt.y				= pt->y;
				gMousePosition.x	= lpt.x;
				gMousePosition.y	= lpt.y;

				if (glMoving || glResizing)
					return;

				// Are we inside the client area?
				if (PtInRect(&winIface.rcClient, lpt))
				{
					// We are.  We are.  We are in the client area. :-)
					glMouseInClientArea = true;

					// Update our caller for the translated point
					pt->x	= (s16)gMousePosition.x;
					pt->y	= (s16)gMousePosition.y;

				} else {
					glMouseInClientArea = false;
				}
			}
			// else leave the mouse state as it is
	}




//////////
//
// Based on the mouseover flag, should the bmp or the bmpOver be drawn?
//
//////
	SBitmap* iBmpOrBmpOver(SObject* obj, bool tlAdditionalTest)
	{
		if (tlAdditionalTest || obj->isMouseOver)		return(&obj->bmpOver);
		else											return(&obj->bmp);

	}




//////////
//
// Draw the indicated object
//
//////
	void iBitBltObject(SBitmap* bmpDst, SObject* objSrc, SBitmap* bmpSrc)
	{
		iBitBlt(bmpDst, &objSrc->rc, bmpSrc);
	}




//////////
//
// Draws all except bits with the mask color rgb(222,22,222)
//
//////
	void iBitBltObjectMask(SBitmap* bmpDst, SObject* obj, SBitmap* bmpSrc)
	{
		iBitBltMask(bmpDst, &obj->rc, bmpSrc);
	}




//////////
//
// Physically render the bitmap atop the bitmap
//
//////
	void iBitBlt(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc)
	{
		s32			lnY, lnX, lnYDst, lnXDst;
		f64			lfAlp, lfMalp;
		SBGR*		lbgrDst;
		SBGR*		lbgrSrc;
		SBGRA*		lbgraDst;
		SBGRA*		lbgraSrc;


		//////////
		// Draw it
		//////
			for (lnY = 0, lnYDst = trc->top; lnY < bmpSrc->bi.biHeight && lnYDst < trc->bottom; lnYDst++, lnY++)
			{
				// Are we on the image?
				if (lnYDst >= 0 && lnYDst < bmpDst->bi.biHeight)
				{
					// Build the pointer
					lbgrDst		= (SBGR*)((s8*)bmpDst->bd  + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgrSrc		= (SBGR*)((s8*)bmpSrc->bd  + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));
					lbgraDst	= (SBGRA*)((s8*)bmpDst->bd + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgraSrc	= (SBGRA*)((s8*)bmpSrc->bd + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));

					// What exactly are we copying?
					if (bmpSrc->bi.biBitCount == 24)
					{
						// 24-bit source
						if (bmpDst->bi.biBitCount == 24)
						{
							// 24-bit to 24-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth)
								{
									// Copy the pixel
									lbgrDst->red	= lbgrSrc->red;
									lbgrDst->grn	= lbgrSrc->grn;
									lbgrDst->blu	= lbgrSrc->blu;
								}

								// Move to next pixel on both
								++lbgrDst;
								++lbgrSrc;
							}

						} else {
							// 24-bit to 32-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth)
								{
									// Copy the pixel
									lbgraDst->alp	= 255;
									lbgraDst->red	= lbgrSrc->red;
									lbgraDst->grn	= lbgrSrc->grn;
									lbgraDst->blu	= lbgrSrc->blu;
								}

								// Move to next pixel on both
								++lbgraDst;
								++lbgrSrc;
							}
						}

					} else {
						// 32-bit source
						if (bmpDst->bi.biBitCount == 24)
						{
							// 32-bit to 24-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth && lbgraSrc->alp != 0)
								{
									// Copy the pixel
									lfAlp			= ((f64)lbgraSrc->alp / 255.0);
									lfMalp			= 1.0 - lfAlp;
									lbgrDst->red	= (u8)min(max(((f64)lbgrDst->red * lfMalp) + (lbgraSrc->red * lfAlp), 0.0), 255.0);
									lbgrDst->grn	= (u8)min(max(((f64)lbgrDst->grn * lfMalp) + (lbgraSrc->grn * lfAlp), 0.0), 255.0);
									lbgrDst->blu	= (u8)min(max(((f64)lbgrDst->blu * lfMalp) + (lbgraSrc->blu * lfAlp), 0.0), 255.0);
								}

								// Move to next pixel on both
								++lbgrDst;
								++lbgraSrc;
							}

						} else {
							// 32-bit to 32-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth && lbgraSrc->alp != 0)
								{
									// Copy the pixel
									lfAlp			= ((f64)lbgraSrc->alp / 255.0);
									lfMalp			= 1.0 - lfAlp;
// 									lbgraDst->alp	= lbgraSrc->alp;
									lbgraDst->red	= (u8)min(max(((f64)lbgraDst->red * lfMalp) + (lbgraSrc->red * lfAlp), 0.0), 255.0);
									lbgraDst->grn	= (u8)min(max(((f64)lbgraDst->grn * lfMalp) + (lbgraSrc->grn * lfAlp), 0.0), 255.0);
									lbgraDst->blu	= (u8)min(max(((f64)lbgraDst->blu * lfMalp) + (lbgraSrc->blu * lfAlp), 0.0), 255.0);
								}

								// Move to next pixel on both
								++lbgraDst;
								++lbgraSrc;
							}
						}
					}
				}
			}
	}




//////////
//
// Physically render the bitmap atop the bitmap, with without the mask bits rgb(222,22,222)
//
//////
	void iBitBltMask(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc)
	{
		s32			lnY, lnX, lnYDst, lnXDst;
		f64			lfAlp, lfMalp;
		SBGR*		lbgrDst;
		SBGR*		lbgrSrc;
		SBGRA*		lbgraDst;
		SBGRA*		lbgraSrc;


		//////////
		// Draw it
		//////
			for (lnY = 0, lnYDst = trc->top; lnY < bmpSrc->bi.biHeight && lnYDst < trc->bottom; lnYDst++, lnY++)
			{
				// Are we on the image?
				if (lnYDst >= 0 && lnYDst < bmpDst->bi.biHeight)
				{
					// Build the pointer
					lbgrDst		= (SBGR*)((s8*)bmpDst->bd  + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgrSrc		= (SBGR*)((s8*)bmpSrc->bd  + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));
					lbgraDst	= (SBGRA*)((s8*)bmpDst->bd + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgraSrc	= (SBGRA*)((s8*)bmpSrc->bd + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));

					// What exactly are we copying?
					if (bmpSrc->bi.biBitCount == 24)
					{
						// 24-bit source
						if (bmpDst->bi.biBitCount == 24)
						{
							// 24-bit to 24-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth)
								{
									// Copy the pixel if it's not a mask pixel
									if (lbgrSrc->red != 222 && lbgrSrc->grn != 22 && lbgrSrc->blu != 222)
									{
										lbgrDst->red	= lbgrSrc->red;
										lbgrDst->grn	= lbgrSrc->grn;
										lbgrDst->blu	= lbgrSrc->blu;
									}
								}

								// Move to next pixel on both
								++lbgrDst;
								++lbgrSrc;
							}

						} else {
							// 24-bit to 32-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth)
								{
									// Copy the pixel if it's not a mask pixel
									if (lbgrSrc->red != 222 && lbgrSrc->grn != 22 && lbgrSrc->blu != 222)
									{
										lbgraDst->alp	= 255;
										lbgraDst->red	= lbgrSrc->red;
										lbgraDst->grn	= lbgrSrc->grn;
										lbgraDst->blu	= lbgrSrc->blu;
									}
								}

								// Move to next pixel on both
								++lbgraDst;
								++lbgrSrc;
							}
						}

					} else {
						// 32-bit source
						if (bmpDst->bi.biBitCount == 24)
						{
							// 32-bit to 24-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth && lbgraSrc->alp != 0)
								{
									// Copy the pixel if it's not a mask pixel
									if (lbgraSrc->red != 222 && lbgraSrc->grn != 22 && lbgraSrc->blu != 222)
									{
										lfAlp			= ((f64)lbgraSrc->alp / 255.0);
										lfMalp			= 1.0 - lfAlp;
										lbgrDst->red	= (u8)min(max(((f64)lbgrDst->red * lfMalp) + (lbgraSrc->red * lfAlp), 0.0), 255.0);
										lbgrDst->grn	= (u8)min(max(((f64)lbgrDst->grn * lfMalp) + (lbgraSrc->grn * lfAlp), 0.0), 255.0);
										lbgrDst->blu	= (u8)min(max(((f64)lbgrDst->blu * lfMalp) + (lbgraSrc->blu * lfAlp), 0.0), 255.0);
									}
								}

								// Move to next pixel on both
								++lbgrDst;
								++lbgraSrc;
							}

						} else {
							// 32-bit to 32-bit
							// Iterate through every visible column
							for (lnX = 0, lnXDst = trc->left; lnX < bmpSrc->bi.biWidth && lnXDst < trc->right; lnXDst++, lnX++)
							{
								// Are we on the image?
								if (lnXDst >= 0 && lnXDst < bmpDst->bi.biWidth && lbgraSrc->alp != 0)
								{
									// Copy the pixel if it's not a mask pixel
									if (lbgraSrc->red != 222 && lbgraSrc->grn != 22 && lbgraSrc->blu != 222)
									{
										lfAlp			= ((f64)lbgraSrc->alp / 255.0);
										lfMalp			= 1.0 - lfAlp;
//										lbgraDst->alp	= lbgraSrc->alp;
										lbgraDst->red	= (u8)min(max(((f64)lbgraDst->red * lfMalp) + (lbgraSrc->red * lfAlp), 0.0), 255.0);
										lbgraDst->grn	= (u8)min(max(((f64)lbgraDst->grn * lfMalp) + (lbgraSrc->grn * lfAlp), 0.0), 255.0);
										lbgraDst->blu	= (u8)min(max(((f64)lbgraDst->blu * lfMalp) + (lbgraSrc->blu * lfAlp), 0.0), 255.0);
									}
								}

								// Move to next pixel on both
								++lbgraDst;
								++lbgraSrc;
							}
						}
					}
				}
			}
	}




//////////
//
// Draw the icon controls
//
//////
	void iDrawControls(RECT* trc)
	{
		//////////
		// Icon and controls
		//////
			SetRect(&winIface.appIcon.rc,		30,					1,				30 + winIface.appIcon.bmp.bi.biWidth,					1 + winIface.appIcon.bmp.bi.biHeight);
			SetRect(&winIface.minimize.rc,		trc->right - 132,	trc->top + 1,	trc->right - 132 + winIface.minimize.bmp.bi.biWidth,	trc->top + 1 + winIface.minimize.bmp.bi.biHeight);
			SetRect(&winIface.maximize.rc,		trc->right - 104,	trc->top + 1,	trc->right - 104 + winIface.maximize.bmp.bi.biWidth,	trc->top + 1 + winIface.maximize.bmp.bi.biHeight);
			SetRect(&winIface.close.rc,			trc->right - 77,	trc->top + 1,	trc->right - 77  + winIface.close.bmp.bi.biWidth,		trc->top + 1 + winIface.close.bmp.bi.biHeight);

			iBitBltObject(&winIface.bmp, &winIface.appIcon,		iBmpOrBmpOver(&winIface.appIcon,	false));
			iBitBltObject(&winIface.bmp, &winIface.minimize,	iBmpOrBmpOver(&winIface.minimize,	false));
			iBitBltObject(&winIface.bmp, &winIface.maximize,	iBmpOrBmpOver(&winIface.maximize,	false));
			iBitBltObject(&winIface.bmp, &winIface.close,		iBmpOrBmpOver(&winIface.close,		false));


		//////////
		// Corner triangles
		//////
			// Set the areas for mouse identifying
			SetRect(&winIface.arrowUl.rc, trc->left, trc->top, trc->left + winIface.arrowUl.bmp.bi.biWidth, trc->top + winIface.arrowUl.bmp.bi.biHeight);
			SetRect(&winIface.arrowUr.rc, trc->right - winIface.arrowUr.bmp.bi.biWidth, trc->top, trc->right, trc->top + winIface.arrowUr.bmp.bi.biHeight);
			SetRect(&winIface.arrowLr.rc, trc->right - winIface.arrowLr.bmp.bi.biWidth, trc->bottom - winIface.arrowLr.bmp.bi.biHeight, trc->right, trc->bottom);
			SetRect(&winIface.arrowLl.rc, trc->left, trc->bottom - winIface.arrowLl.bmp.bi.biHeight, trc->left + winIface.arrowLl.bmp.bi.biWidth, trc->bottom);

			// Draw them
			iBitBltObjectMask(&winIface.bmp, &winIface.arrowUl, iBmpOrBmpOver(&winIface.arrowUl, false));
			iBitBltObjectMask(&winIface.bmp, &winIface.arrowUr, iBmpOrBmpOver(&winIface.arrowUr, false));
			iBitBltObjectMask(&winIface.bmp, &winIface.arrowLr, iBmpOrBmpOver(&winIface.arrowLr, false));
			iBitBltObjectMask(&winIface.bmp, &winIface.arrowLl, iBmpOrBmpOver(&winIface.arrowLl, false));


		//////////
		// Draw the app title
		//////
			SetRect(&winIface.rcCaption, winIface.appIcon.rc.right + 8, winIface.appIcon.rc.top + 2, winIface.minimize.rc.left - 8, winIface.appIcon.rc.bottom);
			SelectObject(winIface.bmp.hdc, winIface.fontCaption->hfont);
			SetTextColor(winIface.bmp.hdc, (COLORREF)RGB(black.red, black.grn, black.blu));
			SetBkColor(winIface.bmp.hdc, (COLORREF)RGB(light_green.red, light_green.grn, light_green.blu));
			DrawTextA(winIface.bmp.hdc, cgcTitle, sizeof(cgcTitle) - 1, &winIface.rcCaption, DT_VCENTER | DT_END_ELLIPSIS);
	}

	void iDrawPoint(SBitmap* bmp, s32 tnX, s32 tnY, SBGRA color)
	{
		SBGR*	lbgr;


		// Make sure our coordinates are valid
		if (tnX >= 0 && tnX < bmp->bi.biWidth && tnY >= 0 && tnY < bmp->bi.biHeight)
		{
			// Get our offset
			lbgr = (SBGR*)(bmp->bd + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));

			// Draw it
			lbgr->red	= color.red;
			lbgr->grn	= color.grn;
			lbgr->blu	= color.blu;
		}
	}

	void iFillRect(SBitmap* bmp, RECT* rc, SBGRA color)
	{
		s32 lnY;


		// Fill every row
		for (lnY = rc->top; lnY < rc->bottom; lnY++)
			iDrawHorizontalLine(bmp, rc->left, rc->right - 1, lnY, color);
	}

	void iFrameRect(SBitmap* bmp, RECT* rc, SBGRA color)
	{
		iDrawHorizontalLine(bmp, rc->left, rc->right - 1, rc->top, color);
		iDrawHorizontalLine(bmp, rc->left, rc->right - 1, rc->bottom - 1, color);
		iDrawVerticalLine(bmp, rc->top, rc->bottom - 1, rc->left, color);
		iDrawVerticalLine(bmp, rc->top, rc->bottom - 1, rc->right - 1, color);
	}

	void iDrawHorizontalLine(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, SBGRA color)
	{
		s32		lnX;
		SBGR*	lbgr;
		SBGRA*	lbgra;


		// Get our starting point
		lbgr	= (SBGR*)(bmp->bd  + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX1 * (bmp->bi.biBitCount / 8)));
		lbgra	= (SBGRA*)(bmp->bd + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX1 * (bmp->bi.biBitCount / 8)));

		if (bmp->bi.biBitCount == 24)
		{
			// Iterate for each column
			for (lnX = tnX1; lnX <= tnX2; lnX++)
			{
				// Are we on the bitmap?
				if (lnX >= 0 && lnX < bmp->bi.biWidth)
				{
					// Draw the pixel
					lbgr->red	= color.red;
					lbgr->grn	= color.grn;
					lbgr->blu	= color.blu;

					// Move to next column
					++lbgr;
				}
			}

		} else if (bmp->bi.biBitCount == 32) {
			// Iterate for each column
			for (lnX = tnX1; lnX <= tnX2; lnX++)
			{
				// Are we on the bitmap?
				if (lnX >= 0 && lnX < bmp->bi.biWidth)
				{
					// Draw the pixel
					lbgra->alp	= 255;
					lbgra->red	= color.red;
					lbgra->grn	= color.grn;
					lbgra->blu	= color.blu;

					// Move to next column
					++lbgra;
				}
			}
		}
	}

	void iDrawVerticalLine(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, SBGRA color)
	{
		s32		lnY;
		SBGR*	lbgr;
		SBGRA*	lbgra;


		// Get our starting point
		lbgr	= (SBGR*)(bmp->bd  + ((bmp->bi.biHeight - tnY1 - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));
		lbgra	= (SBGRA*)(bmp->bd + ((bmp->bi.biHeight - tnY1 - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));

		if (bmp->bi.biBitCount == 24)
		{
			// Iterate for each column
			for (lnY = tnY1; lnY <= tnY2; lnY++)
			{
				// Are we on the bitmap?
				if (lnY >= 0 && lnY < bmp->bi.biHeight)
				{
					// Draw the pixel
					lbgr->red	= color.red;
					lbgr->grn	= color.grn;
					lbgr->blu	= color.blu;

					// Move to next row
					lbgr = (SBGR*)((s8*)lbgr - bmp->rowWidth);
				}
			}

		} else if (bmp->bi.biBitCount == 32) {
			// Iterate for each column
			for (lnY = tnY1; lnY <= tnY2; lnY++)
			{
				// Are we on the bitmap?
				if (lnY >= 0 && lnY < bmp->bi.biHeight)
				{
					// Draw the pixel
					lbgra->red	= color.red;
					lbgra->grn	= color.grn;
					lbgra->blu	= color.blu;

					// Move to next row
					lbgra = (SBGRA*)((s8*)lbgra - bmp->rowWidth);
				}
			}
		}
	}




//////////
//
// Called to redraw the main window
//
//////
	void iRedrawAll(SWindowIface* win)
	{
//		u32		lnI;
		RECT	lrc;


		// White background
		iFillRect(&winIface.bmp, &winIface.rc, light_green);

		// Draw the border around the whole window
		iFrameRect(&winIface.bmp, &winIface.rc, black);

		// Draw the controls
		iDrawControls(&winIface.rc);

		// Draw the border around the client area
		SetRect(&lrc, 8, 24, winIface.rc.right - 8, winIface.rc.bottom - 24);
		iFillRect(&winIface.bmp, &lrc, white);
		InflateRect(&lrc, 1, 1);
		iFrameRect(&winIface.bmp, &lrc, black);
	}
