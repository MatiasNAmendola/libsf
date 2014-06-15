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
	iObjectLoad(&winScreen.appIcon,				cgc_appIconBmp);
	iObjectLoad(&winScreen.minimize,			cgc_minimizeBmp);
	iObjectLoad(&winScreen.maximize,			cgc_maximizeBmp);
	iObjectLoad(&winScreen.move,				cgc_moveBmp);
	iObjectLoad(&winScreen.close,				cgc_closeBmp);
	iObjectLoad(&winScreen.arrowUl,				cgc_arrowUlBmp);
	iObjectLoad(&winScreen.arrowUr,				cgc_arrowUrBmp);
	iObjectLoad(&winScreen.arrowLr,				cgc_arrowLrBmp);
	iObjectLoad(&winScreen.arrowLl,				cgc_arrowLlBmp);

	iObjectLoad(&winJDebi.appIcon,				cgc_jdebiAppIconBmp);
	iObjectLoad(&winJDebi.minimize,				cgc_minimizeBmp);
	iObjectLoad(&winJDebi.maximize,				cgc_maximizeBmp);
	iObjectLoad(&winJDebi.close,				cgc_closeBmp);
	iObjectLoad(&winJDebi.arrowUl,				cgc_arrowUlBmp);
	iObjectLoad(&winJDebi.arrowUr,				cgc_arrowUrBmp);
	iObjectLoad(&winJDebi.arrowLr,				cgc_arrowLrBmp);
	iObjectLoad(&winJDebi.arrowLl,				cgc_arrowLlBmp);


	// Create our message window
	iCreateMessageWindow();


	// Create our main screen window
	iCreateScreenWindow();


	// Create our JDebi window
	iCreateJDebiWindow();
}




//////////
//
// Called to convert the indicated bitmap to 32-bits if need be
//
//////
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
		SBgr*	lbgr;
		SBgra*	lbgra;


		// Iterate through every row
		for (lnY = 0; lnY < bmp24->bi.biHeight; lnY++)
		{
			// Grab our pointers
			lbgr	= (SBgr*)(bmp24->bd  + ((bmp24->bi.biHeight - lnY - 1) * bmp24->rowWidth));
			lbgra	= (SBgra*)(bmp32->bd + ((bmp32->bi.biHeight - lnY - 1) * bmp32->rowWidth));

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
		// Call Windows' default procedure handler
		return(DefWindowProc(hwnd, m, w, l));
	}




//////////
//
// Called to find or create the KSI interface window
//
//////
	HWND iCreateScreenWindow(void)
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
				if (!GetClassInfoExA(ghInstance, cgcScreenWindowClass, &classa))
				{
					// Initialize
					memset(&classa, 0, sizeof(classa));

					// Populate
					classa.cbSize				= sizeof(WNDCLASSEXA);
					classa.hInstance			= ghInstance;
					classa.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
					classa.lpszClassName		= cgcScreenWindowClass;
					classa.hIcon				= LoadIcon(ghInstance, MAKEINTRESOURCE(IDI_VJR));
					classa.hCursor				= LoadCursor(NULL, IDC_ARROW);
					classa.lpfnWndProc			= &iWndProc_screenWindow;

					// Register
					atom = RegisterClassExA(&classa);
					if (!atom)
						break;
				}


			//////////
			// Find out how big the window should be
			//////
				iComputeScreenWindowClientAreaDimensions(&client);
				iComputeScreenWindowNonclientAreaDimensions(&nonclient);
				overall.width	= client.width + nonclient.width;
				overall.height	= client.height + nonclient.width;
				iAdjustScreenWindowDimensions(&overall);


			//////////
			// Physically create the interface window
			//////
				GetWindowRect(GetDesktopWindow(), &lrc);
				lnLeft	= ((lrc.right - lrc.left) - overall.width)  / 2;
				lnTop	= ((lrc.bottom - lrc.top) - overall.height) / 2;
				ghwndScreen	= CreateWindowA(cgcScreenWindowClass, cgcScreenTitle, WS_POPUP, lnLeft, lnTop, overall.width, overall.height, NULL, NULL, ghInstance, 0);
				if (ghwndScreen)
				{
					///////////
					// Read events from the window
					//////
						CreateThread(NULL, 0, &iReadEvents_screenWindow, 0, 0, 0);


					//////////
					// Create the fonts
					//////
						font				= iFontCreate(cgcWindowTitleBarFont, 10,	FW_BOLD, false, false);
						winScreen.font		= iFontDuplicate(font);


					//////////
					// Draw the initial window state
					//////
						iResizeScreenWindow(true);


					//////////
					// Make it visible
					//////
						SetWindowPos(ghwndScreen, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
						ShowWindow(ghwndScreen, SW_SHOW);


					// All done
					return(ghwndScreen);
				}
				break;
			}
			// We should never get here
			MessageBoxA(NULL, "Error creating main screen window.", "Fatal Error", MB_OK);
			return(NULL);
	}




//////////
//
// 
//
//////
	HWND iCreateJDebiWindow(void)
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
				if (!GetClassInfoExA(ghInstance, cgcJDebiWindowClass, &classa))
				{
					// Initialize
					memset(&classa, 0, sizeof(classa));

					// Populate
					classa.cbSize				= sizeof(WNDCLASSEXA);
					classa.hInstance			= ghInstance;
					classa.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
					classa.lpszClassName		= cgcJDebiWindowClass;
					classa.hIcon				= LoadIcon(ghInstance, MAKEINTRESOURCE(IDI_VJR));
					classa.hCursor				= LoadCursor(NULL, IDC_ARROW);
					classa.lpfnWndProc			= &iWndProc_jDebiWindow;

					// Register
					atom = RegisterClassExA(&classa);
					if (!atom)
						break;
				}


			//////////
			// Find out how big the window should be
			//////
				iComputeJDebiWindowClientAreaDimensions(&client);
				iComputeJDebiWindowNonclientAreaDimensions(&nonclient);
				overall.width	= client.width + nonclient.width;
				overall.height	= client.height + nonclient.width;
				iAdjustJDebiWindowDimensions(&overall);


			//////////
			// Physically create the interface window
			//////
				GetWindowRect(GetDesktopWindow(), &lrc);
				lnLeft	= ((lrc.right - lrc.left) - overall.width)  / 2;
				lnTop	= ((lrc.bottom - lrc.top) - overall.height) / 2;
				ghwndJDebi = CreateWindowA(cgcJDebiWindowClass, cgcJDebiTitle, WS_POPUP, lnLeft, lnTop, overall.width, overall.height, NULL, NULL, ghInstance, 0);
				if (ghwndJDebi)
				{
					///////////
					// Read events from the window
					//////
						CreateThread(NULL, 0, &iReadEvents_jDebiWindow, 0, 0, 0);


					//////////
					// Create the font
					//////
						font						= iFontCreate(cgcWindowTitleBarFont, 10,	FW_BOLD, false, false);
						winJDebi.font		= iFontDuplicate(font);


					//////////
					// Draw the initial window state
					//////
						iResizeJDebiWindow(true);


					//////////
					// Make it visible
					//////
						SetWindowPos(ghwndJDebi, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
						ShowWindow(ghwndJDebi, SW_SHOW);


					// All done
					return(ghwndJDebi);
				}
				break;
			}
			// We should never get here
			MessageBoxA(NULL, "Error creating JDebi debugger window.", "Fatal Error", MB_OK);
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
			bmp->rowWidth			= iBmpComputeRowWidth(bmp);
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
// Called to resize the window if need be based upon new client size settings
//
//////
	void iResizeScreenWindow(bool tlForce)
	{
		s32		lnLeft, lnTop;
		RECT	lrcDesktop;
		SSize	client, nonclient, overall;


		//////////
		// Find out how big the window should be
		//////
			iComputeScreenWindowClientAreaDimensions(&client);
			iComputeScreenWindowNonclientAreaDimensions(&nonclient);
			overall.width	= client.width + nonclient.width;
			overall.height	= client.height + nonclient.width;
			iAdjustScreenWindowDimensions(&overall);


		//////////
		// Determine the windows desktop size
		//////
			GetWindowRect(GetDesktopWindow(), &lrcDesktop);

		
		//////////
		// If the window size is different than this, we need to resize it
		//////
			lnLeft	= (lrcDesktop.right  - lrcDesktop.left)  / 16;
			lnTop	= (lrcDesktop.bottom - lrcDesktop.top)   / 16;
			iSetScreenWindowSize(lnLeft, lnTop, overall.width, overall.height, tlForce);
	}




//////////
//
// Called to resize the JDebi window
//
//////
	void iResizeJDebiWindow(bool tlForce)
	{
		s32		lnLeft, lnTop;
		RECT	lrcDesktop;
		SSize	client, nonclient, overall;
		SSize	clientScreen, nonclientScreen, overallScreen;


		//////////
		// Find out how big the window should be
		//////
			iComputeJDebiWindowClientAreaDimensions(&client);
			iComputeJDebiWindowNonclientAreaDimensions(&nonclient);
			overall.width	= client.width + nonclient.width;
			overall.height	= client.height + nonclient.width;
			iAdjustJDebiWindowDimensions(&overall);
			
			// Main screen
			iComputeScreenWindowClientAreaDimensions(&clientScreen);
			iComputeScreenWindowNonclientAreaDimensions(&nonclientScreen);
			overallScreen.width		= clientScreen.width + nonclientScreen.width;
			overallScreen.height	= clientScreen.height + nonclientScreen.width;
			iAdjustScreenWindowDimensions(&overallScreen);


		//////////
		// Determine the windows desktop size
		//////
			GetWindowRect(GetDesktopWindow(), &lrcDesktop);

		
		//////////
		// If the window size is different than this, we need to resize it
		//////
			lnLeft	= winScreen.rc.right;
			lnTop	= winScreen.rc.top;
			iSetJDebiWindowSize(lnLeft, lnTop, ((lrcDesktop.right - lrcDesktop.left) - overallScreen.width) - (2 * winScreen.rc.left), overallScreen.height, tlForce);
	}




//////////
//
// Called to programmatically set the screen window size after a resize
//
//////
	void iSetScreenWindowSize(s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight, bool tlForce)
	{
		bool llChangedSomething;


		// Do we need to resize?
		if (!IsWindowVisible(ghwndScreen) && !tlForce)
			return;

		// Begin resizing
		ShowWindow(ghwndScreen, SW_RESTORE);
		llChangedSomething = tlForce;
		if (winScreen.rc.right - winScreen.rc.left != tnWidth || winScreen.rc.bottom - winScreen.rc.top != tnHeight)
		{
			// Yes
			llChangedSomething = true;
			SetWindowPos(ghwndScreen, NULL, 0, 0, tnWidth, tnHeight,	SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOMOVE);
		}


		// Do we need to move?
		if (winScreen.rc.left != tnLeft || winScreen.rc.top != tnTop)
		{
			// Yes
			llChangedSomething = true;
			SetWindowPos(ghwndScreen, NULL, tnLeft, tnTop, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOSIZE);
		}


		// Get the current size
		SetRect(&winScreen.rc, tnLeft, tnTop, tnLeft + tnWidth, tnTop + tnHeight);


		// Did we change anything?
		if (llChangedSomething)
		{
			//////////
			// If there's already an image, release it
			//////
				DeleteObject((HGDIOBJ)winScreen.bmp.hbmp);
				DeleteDC(winScreen.bmp.hdc);
				memset(&winScreen.bmp, 0, sizeof(SBitmap));


			//////////
			// Create the buffers for it
			//////
				winScreen.bmp.hdc		= CreateCompatibleDC(GetDC(GetDesktopWindow()));
				winScreen.bmp.hbmp		= iCreateBitmap(winScreen.bmp.hdc, tnWidth, tnHeight, 1, 32, (void**)&winScreen.bmp.bd, &winScreen.bmp.bh, &winScreen.bmp.bi);
				winScreen.bmp.rowWidth	= iBmpComputeRowWidth(&winScreen.bmp);
				SelectObject(winScreen.bmp.hdc, winScreen.bmp.hbmp);


			//////////
			// Redraw the window
			//////
				GetClientRect(ghwndScreen, &winScreen.rcClient);
				iRedrawScreen(&winScreen);
		}
	}




//////////
//
// Called to programmatically set the JDebi window size after a resize
//
//////
	void iSetJDebiWindowSize(s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight, bool tlForce)
	{
		bool llChangedSomething;


		// Do we need to resize?
		if (!IsWindowVisible(ghwndJDebi) && !tlForce)
			return;

		// Begin resizing
		ShowWindow(ghwndJDebi, SW_RESTORE);
		llChangedSomething = tlForce;
		if (winJDebi.rc.right - winJDebi.rc.left != tnWidth || winJDebi.rc.bottom - winJDebi.rc.top != tnHeight)
		{
			// Yes
			llChangedSomething = true;
			SetWindowPos(ghwndJDebi, NULL, 0, 0, tnWidth, tnHeight,	SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOMOVE);
		}


		// Do we need to move?
		if (winJDebi.rc.left != tnLeft || winJDebi.rc.top != tnTop)
		{
			// Yes
			llChangedSomething = true;
			SetWindowPos(ghwndJDebi, NULL, tnLeft, tnTop, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOSIZE);
		}


		// Get the current size
		SetRect(&winJDebi.rc, tnLeft, tnTop, tnLeft + tnWidth, tnTop + tnHeight);


		// Did we change anything?
		if (llChangedSomething)
		{
			//////////
			// If there's already an image, release it
			//////
				DeleteObject((HGDIOBJ)winJDebi.bmp.hbmp);
				DeleteDC(winJDebi.bmp.hdc);
				memset(&winJDebi.bmp, 0, sizeof(SBitmap));


			//////////
			// Create the buffers for it
			//////
				winJDebi.bmp.hdc		= CreateCompatibleDC(GetDC(GetDesktopWindow()));
				winJDebi.bmp.hbmp		= iCreateBitmap(winJDebi.bmp.hdc, tnWidth, tnHeight, 1, 32, (void**)&winJDebi.bmp.bd, &winJDebi.bmp.bh, &winJDebi.bmp.bi);
				winJDebi.bmp.rowWidth	= iBmpComputeRowWidth(&winJDebi.bmp);
				SelectObject(winJDebi.bmp.hdc, winJDebi.bmp.hbmp);


			//////////
			// Redraw the window
			//////
				GetClientRect(ghwndJDebi, &winJDebi.rcClient);
				iRedrawJDebi(&winJDebi);
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
				lbi->biSizeImage		= iBmpComputeRowWidth(&bmp) * tnHeight;
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
// Thread to handle interface window events
//
//////
	DWORD WINAPI iReadEvents_screenWindow(LPVOID lpParameter)
	{
		MSG msg;


		// Read until the message window goes bye bye
		while (GetMessage(&msg, ghwndScreen, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// When we get here, we're shutting down
		return 0;
	}




//////////
//
// Processes messages from the interface window, to forward on to the original window
//
//////
	LRESULT CALLBACK iWndProc_screenWindow(HWND h, UINT m, WPARAM w, LPARAM l)
	{
// 		s32				id, event;
		HDC				lhdc;
		PAINTSTRUCT		ps;


		// See if we know this hwnd
		// It was one of our windows
		switch (m)
		{
			case WM_LBUTTONDOWN:
				glMouseLeftButton = true;
				return(iProcessMouseMessage(m, w, l));
				break;

			case WM_LBUTTONUP:
				if (glMoving || glResizing)
					ReleaseCapture();

				glMouseLeftButton = false;
				return(iProcessMouseMessage(m, w, l));
				break;

			case WM_RBUTTONDOWN:
				glMouseRightButton = true;
				return(iProcessMouseMessage(m, w, l));
				break;

			case WM_RBUTTONUP:
				glMouseRightButton = false;
				return(iProcessMouseMessage(m, w, l));
				break;

			case WM_MBUTTONDOWN:
				glMouseMiddleButton = true;
				return(iProcessMouseMessage(m, w, l));
				break;

			case WM_MBUTTONUP:
				glMouseMiddleButton = false;
				return(iProcessMouseMessage(m, w, l));
				break;

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
				break;

			case WM_KEYDOWN:
			case WM_KEYUP:
//			case WM_CHAR:
//			case WM_DEADCHAR:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
//			case WM_SYSCHAR:
//			case WM_SYSDEADCHAR:
				return 0;
				break;

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
				BitBlt(lhdc, 0, 0, winScreen.bmp.bi.biWidth, winScreen.bmp.bi.biHeight, winScreen.bmp.hdc, 0, 0, SRCCOPY);
				EndPaint(h, &ps);
				return 0;
		}

		// Call Windows' default procedure handler
		return(DefWindowProc(h, m, w, l));
	}




//////////
//
// 
//
//////
	DWORD WINAPI iReadEvents_jDebiWindow(LPVOID lpParameter)
	{
		MSG msg;


		// Read until the message window goes bye bye
		while (GetMessage(&msg, ghwndJDebi, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// When we get here, we're shutting down
		return 0;
	}




//////////
//
// 
//
//////
	LRESULT CALLBACK iWndProc_jDebiWindow(HWND h, UINT m, WPARAM w, LPARAM l)
	{
// 		s32				id, event;
		HDC				lhdc;
		PAINTSTRUCT		ps;


		// See if we know this hwnd
		// It was one of our windows
		switch (m)
		{
			case WM_LBUTTONDOWN:
				glMouseLeftButton = true;
				return(iProcessMouseMessage(m, w, l));
				break;

			case WM_LBUTTONUP:
				if (glMoving || glResizing)
					ReleaseCapture();

				glMouseLeftButton = false;
				return(iProcessMouseMessage(m, w, l));
				break;

			case WM_RBUTTONDOWN:
				glMouseRightButton = true;
				return(iProcessMouseMessage(m, w, l));
				break;

			case WM_RBUTTONUP:
				glMouseRightButton = false;
				return(iProcessMouseMessage(m, w, l));
				break;

			case WM_MBUTTONDOWN:
				glMouseMiddleButton = true;
				return(iProcessMouseMessage(m, w, l));
				break;

			case WM_MBUTTONUP:
				glMouseMiddleButton = false;
				return(iProcessMouseMessage(m, w, l));
				break;

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
				break;

			case WM_KEYDOWN:
			case WM_KEYUP:
//			case WM_CHAR:
//			case WM_DEADCHAR:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
//			case WM_SYSCHAR:
//			case WM_SYSDEADCHAR:
				return 0;
				break;

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
				BitBlt(lhdc, 0, 0, winJDebi.bmp.bi.biWidth, winJDebi.bmp.bi.biHeight, winJDebi.bmp.hdc, 0, 0, SRCCOPY);
				EndPaint(h, &ps);
				return 0;
				break;
		}

		// Call Windows' default procedure handler
		return(DefWindowProc(h, m, w, l));
	}




//////////
//
// Called to shutdown the system politely, closing everything that's open
//
//////
	bool iShutdownPolitely(void)
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
	SFont* iFontDuplicate(SFont* fontSource)
	{
		SFont* font;


		// Make sure our environment is sane
		font = NULL;
		if (fontSource)
		{
			//////////
			// Allocate a new pointer
			//////
				font = iFontAllocate();
				if (!font)
					return(font);


			//////////
			// Create a copy
			//////
				font->hdc					= CreateCompatibleDC(GetDC(GetDesktopWindow()));
				font->hfont					= CreateFont(fontSource->_sizeUsedForCreateFont, 0, 0, 0, fontSource->_weight, (fontSource->_italics != 0), (fontSource->_underline != 0), false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, fontSource->name.data);
				SelectObject(font->hdc, font->hfont);
				iDatumDuplicate(&font->name, fontSource->name.data, fontSource->name.length);
				font->_size					= fontSource->_size;
				font->_weight				= fontSource->_weight;
				font->_italics				= fontSource->_italics;
				font->_underline			= fontSource->_underline;
				memcpy(&font->tm, &fontSource->tm, sizeof(font->tm));
		}
		// Indicate our success or failure
		return(font);
	}




//////////
//
// Allocate an empty structure
//
//////
	SFont* iFontAllocate(void)
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
	SFont* iFontCreate(cs8* tcFontName, u32 tnFontSize, u32 tnFontWeight, u32 tnItalics, u32 tnUnderline)
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
			font = (SFont*)builder_allocateBytes(gFonts, sizeof(SFont));
			if (!font)
				return(font);

			// Initialize
			memset(font, 0, sizeof(SFont));


		//////////
		// Populate
		//////
			font->hdc						= CreateCompatibleDC(GetDC(GetDesktopWindow()));
			font->_sizeUsedForCreateFont	= -MulDiv(tnFontSize, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);
			font->hfont						= CreateFont(font->_sizeUsedForCreateFont, 0, 0, 0, tnFontWeight, (tnItalics != 0), (tnUnderline != 0), false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, tcFontName);
			SelectObject(font->hdc, font->hfont);
			iDatumDuplicate(&font->name, (s8*)tcFontName, lnLength);
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
			font = iFontCreate(tcFontName, tnFontSize + lnI, lnFontBold, tnFontItalic, tnFontUnderline);

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
			if (winScreen.rc.right > winScreen.rc.left)
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
				if (PtInRect(&winScreen.rcClient, lpt))
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
// EditChainManager processing
//
//////
	void iEditChainManagerDuplicate(SEditChainManager** root, SEditChainManager* chain)
	{
		SEditChainManager* ecm;


		// Create the master record
		ecm = (SEditChainManager*)malloc(sizeof(SEditChainManager));
		if (ecm)
		{
			// Initialize
			memset(ecm, 0, sizeof(SEditChainManager));

			// Update caller
			*root = ecm;

// TODO:  Code the duplication
		}
	}




//////////
//
// Datum storage
//
//////
	void iDatumDuplicate(SDatum* datum, s8* data, u32 dataLength)
	{
		// Make sure our environment is sane
		if (datum)
		{
			// Release anything that's already there
			iiDatumFree(datum);

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

	void iDatumDuplicate(SDatum* datumDst, SDatum* datumSrc)
	{
		if (datumDst && datumSrc && datumSrc->data)
			iDatumDuplicate(datumDst, datumSrc->data, datumSrc->length);
	}

	void iiDatumFree(SDatum* datum)
	{
		// Store the data
		if (datum->data)
		{
			free(datum->data);
			datum->data = NULL;
		}

		// Reset the length to zero
		datum->length = 0;
	}




//////////
// Allocates a new structure
//////
	SBitmap* iBmpAllocate(void)
	{
		SBitmap* bmp;


		// Allocate our new structure
		bmp = (SBitmap*)malloc(sizeof(SBitmap));

		// Initialize if successful
		if (bmp)
			memset(bmp, 0, sizeof(SBitmap));

		// Indicate our success or failure
		return(bmp);
	}
;




//////////
//
// Called to copy a bitmap, to duplicate it completely
//
//////
	SBitmap* iBmpCopy(SBitmap* bmpSrc)
	{
		SBitmap*	bmp;
		RECT		lrc;


		// Make sure our environment is sane
		bmp = NULL;
		if (bmpSrc && iBmpValidate(bmpSrc))
		{
			// Allocate a new structure
			bmp = iBmpAllocate();
			if (bmp)
			{
				// Create a bitmap of the target size
				iBmpCreateBySize(bmp, bmpSrc->bi.biWidth, bmpSrc->bi.biHeight, bmpSrc->bi.biBitCount);
				
				// Copy the bitmap over
				SetRect(&lrc, 0, 0, bmpSrc->bi.biWidth, bmpSrc->bi.biHeight);
				iBmpBitBlt(bmp, &lrc, bmpSrc);
			}
		}

		// Indicate our success or failure
		return(bmp);
	}




//////////
//
// Performs basic tests on the bitmap to see if it appears to be a valid structure.
//
//////
	bool iBmpValidate(SBitmap* bmp)
	{
		// Planes must be 1
		if (bmp->bi.biPlanes != 1)
			return(false);

		// Bits must be 24 or 32
		if (bmp->bi.biBitCount != 24 && bmp->bi.biBitCount != 32)
			return(false);

		// No compression (meaning default BMP file)
		if (bmp->bi.biCompression != 0)
			return(false);

		// Make sure the biSizeImage is accurate
		iBmpComputeRowWidth(bmp);
		if (bmp->rowWidth * bmp->bi.biHeight != bmp->bi.biSizeImage)
			return(false);

		// Make sure the pixels per meter are set
		if (bmp->bi.biXPelsPerMeter <= 0)			bmp->bi.biXPelsPerMeter = 2835;					// Default to 72 pixels per inch, a "twip" as it were
		if (bmp->bi.biYPelsPerMeter <= 0)			bmp->bi.biYPelsPerMeter = 2835;

		// We're good
		return(true);
	}




//////////
//
// Computes the row width of the pixels using BGR format (3 bytes per pixel) then rounded up to
// the nearest DWORD.
//
//////
	s32 iBmpComputeRowWidth(SBitmap* bmp)
	{
		s32 lnWidth;


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
// Called to create a basic bitmap by the indicated size, and initially populate it to white
//
//////
	void iBmpCreateBySize(SBitmap* bmp, u32 width, u32 height, u32 tnBitCount)
	{
		// Populate the initial structure
		if (tnBitCount == 24)		iBmpPopulateBitmapStructure(bmp, width, height, 24);
		else						iBmpPopulateBitmapStructure(bmp, width, height, 32);

		// Create the HDC and DIB Section
		bmp->hdc	= CreateCompatibleDC(GetDC(GetDesktopWindow()));
		bmp->hbmp	= CreateDIBSection(bmp->hdc, (BITMAPINFO*)&bmp->bi, DIB_RGB_COLORS, (void**)&bmp->bd, NULL, 0);
		SelectObject(bmp->hdc, bmp->hbmp);

		// Paint it white initially (the fast/easy way)
		memset(bmp->bd, 255, bmp->bi.biSizeImage);
	}




//////////
//
// Called to create an empty 24-bit bitmap
//
//////
	void iBmpPopulateBitmapStructure(SBitmap* bmp, u32 tnWidth, u32 tnHeight, u32 tnBitCount)
	{
		memset(&bmp->bi, 0, sizeof(bmp->bi));
		bmp->bi.biSize				= sizeof(bmp->bi);
		bmp->bi.biWidth				= tnWidth;
		bmp->bi.biHeight			= tnHeight;
		bmp->bi.biCompression		= 0;
		bmp->bi.biPlanes			= 1;
		bmp->bi.biBitCount			= (u16)((tnBitCount == 24 || tnBitCount == 32) ? tnBitCount : 32);
		bmp->bi.biXPelsPerMeter		= 2835;	// Assume 72 dpi
		bmp->bi.biYPelsPerMeter		= 2835;
		iBmpComputeRowWidth(bmp);
		bmp->bi.biSizeImage			= bmp->rowWidth * tnHeight;
//////////
// Note:  The compression formats can be:
// 0	BI_RGB	none (most common)
// 4	BI_JPEG	data bits following need to be fed into a JPG decoder to access bit rows, to save back to disk a JPG encoder is required, lossy compression (always loses bitmap color data)
// 5	BI_PNG	data bits following need to be fed into a PNG decoder to access bit rows, to save back to disk a PNG encoder is required, lossless compression (always maintains original color data)
//////
	}




//////////
//
// Called to delete the indicated bitmap and optionally free all resources.
//
//////
	void iBmpDelete(SBitmap* bmp, bool tlFreeBits)
	{
		if (bmp)
		{
			// Do we need to free the internals?
			if (tlFreeBits)
			{
				// Free the internal/Windows bits
				DeleteObject((HGDIOBJ)bmp->hbmp);
				DeleteDC(bmp->hdc);
			}

			// Release the bitmap
			free(bmp);
		}
	}




//////////
//
// Draw the indicated object
//
//////
	void iBmpBitBltObject(SBitmap* bmpDst, SObject* objSrc, SBitmap* bmpSrc)
	{
		iBmpBitBlt(bmpDst, &objSrc->rc, bmpSrc);
	}




//////////
//
// Draws all except bits with the mask color rgb(222,22,222)
//
//////
	void iBmpBitBltObjectMask(SBitmap* bmpDst, SObject* obj, SBitmap* bmpSrc)
	{
		iBmpBitBltMask(bmpDst, &obj->rc, bmpSrc);
	}




//////////
//
// Physically render the bitmap atop the bitmap
//
//////
	u32 iBmpBitBlt(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc)
	{
		u32			lnPixelsRendered;
		s32			lnY, lnX, lnYDst, lnXDst;
		f64			lfAlp, lfMalp;
		SBgr*		lbgrDst;
		SBgr*		lbgrSrc;
		SBgra*		lbgraDst;
		SBgra*		lbgraSrc;


		//////////
		// Draw it
		//////
			lnPixelsRendered = 0;
			for (lnY = 0, lnYDst = trc->top; lnY < bmpSrc->bi.biHeight && lnYDst < trc->bottom; lnYDst++, lnY++)
			{
				// Are we on the image?
				if (lnYDst >= 0 && lnYDst < bmpDst->bi.biHeight)
				{
					// Build the pointer
					lbgrDst		= (SBgr*)((s8*)bmpDst->bd  + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgrSrc		= (SBgr*)((s8*)bmpSrc->bd  + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));
					lbgraDst	= (SBgra*)((s8*)bmpDst->bd + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgraSrc	= (SBgra*)((s8*)bmpSrc->bd + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));

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
									++lnPixelsRendered;
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
									++lnPixelsRendered;
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
									++lnPixelsRendered;
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
									++lnPixelsRendered;
								}

								// Move to next pixel on both
								++lbgraDst;
								++lbgraSrc;
							}
						}
					}
				}
			}


		//////////
		// Indicate how many pixels were rendered
		//////
			return(lnPixelsRendered);
	}




//////////
//
// Physically render the bitmap atop the bitmap, with without the mask bits rgb(222,22,222)
//
//////
	void iBmpBitBltMask(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc)
	{
		s32			lnY, lnX, lnYDst, lnXDst;
		f64			lfAlp, lfMalp;
		SBgr*		lbgrDst;
		SBgr*		lbgrSrc;
		SBgra*		lbgraDst;
		SBgra*		lbgraSrc;


		//////////
		// Draw it
		//////
			for (lnY = 0, lnYDst = trc->top; lnY < bmpSrc->bi.biHeight && lnYDst < trc->bottom; lnYDst++, lnY++)
			{
				// Are we on the image?
				if (lnYDst >= 0 && lnYDst < bmpDst->bi.biHeight)
				{
					// Build the pointer
					lbgrDst		= (SBgr*)((s8*)bmpDst->bd  + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgrSrc		= (SBgr*)((s8*)bmpSrc->bd  + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));
					lbgraDst	= (SBgra*)((s8*)bmpDst->bd + ((bmpDst->bi.biHeight - lnYDst - 1) * bmpDst->rowWidth) + (trc->left * (bmpDst->bi.biBitCount / 8)));
					lbgraSrc	= (SBgra*)((s8*)bmpSrc->bd + ((bmpSrc->bi.biHeight - lnY    - 1) * bmpSrc->rowWidth));

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

	void iBmpDrawPoint(SBitmap* bmp, s32 tnX, s32 tnY, SBgra color)
	{
		SBgr*	lbgr;


		// Make sure our coordinates are valid
		if (tnX >= 0 && tnX < bmp->bi.biWidth && tnY >= 0 && tnY < bmp->bi.biHeight)
		{
			// Get our offset
			lbgr = (SBgr*)(bmp->bd + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));

			// Draw it
			lbgr->red	= color.red;
			lbgr->grn	= color.grn;
			lbgr->blu	= color.blu;
		}
	}

	void iBmpFillRect(SBitmap* bmp, RECT* rc, SBgra colorNW, SBgra colorNE, SBgra colorSW, SBgra colorSE, bool tlUseGradient)
	{
		s32		lnY;
		f32		lfRed, lfGrn, lfBlu, lfRedTo, lfGrnTo, lfBluTo, lfRedInc, lfGrnInc, lfBluInc, lfPercent, lfPercentInc, lfHeight, lfWidth;


		//////////
		// Fill every row
		//////
			lfWidth			= (f32)(rc->right  - 1 - rc->left);
			lfHeight		= (f32)(rc->bottom - 1 - rc->top);
			lfPercentInc	= 1.0f / lfHeight;
			for (lfPercent = 0.0, lnY = rc->top; lnY < rc->bottom; lnY++, lfPercent += lfPercentInc)
			{
				if (tlUseGradient)
				{
					//////////
					// Compute FROM colors
					//////
						lfRed		= (f32)colorNW.red + (((f32)colorSW.red - (f32)colorNW.red) * lfPercent);
						lfGrn		= (f32)colorNW.grn + (((f32)colorSW.grn - (f32)colorNW.grn) * lfPercent);
						lfBlu		= (f32)colorNW.blu + (((f32)colorSW.blu - (f32)colorNW.blu) * lfPercent);


					//////////
					// Compute TO colors
					//////
						lfRedTo		= (f32)colorNE.red + (((f32)colorSE.red - (f32)colorNE.red) * lfPercent);
						lfGrnTo		= (f32)colorNE.grn + (((f32)colorSE.grn - (f32)colorNE.grn) * lfPercent);
						lfBluTo		= (f32)colorNE.blu + (((f32)colorSE.blu - (f32)colorNE.blu) * lfPercent);


					//////////
					// Compute increment
					//////
						lfRedInc	= (lfRedTo - lfRed) / lfWidth;
						lfGrnInc	= (lfGrnTo - lfGrn) / lfWidth;
						lfBluInc	= (lfBluTo - lfBlu) / lfWidth;


					//////////
					// Draw this line with its gradient
					//////
						iBmpDrawHorizontalLineGradient(bmp, rc->left, rc->right - 1, lnY, lfRed, lfGrn, lfBlu, lfRedInc, lfGrnInc, lfBluInc);

				} else {
					// Draw this line with the NW color
					iBmpDrawHorizontalLine(bmp, rc->left, rc->right - 1, lnY, colorNW);
				}
			}
	}

	void iBmpFrameRect(SBitmap* bmp, RECT* rc, SBgra colorNW, SBgra colorNE, SBgra colorSW, SBgra colorSE, bool tlUseGradient)
	{
		f32 lfRed, lfGrn, lfBlu, lfRedTo, lfGrnTo, lfBluTo, lfRedInc, lfGrnInc, lfBluInc, lfHeight, lfWidth;


		if (tlUseGradient)
		{
			// Compute standards
			lfWidth		= (f32)(rc->right  - 1 - rc->left);
			lfHeight	= (f32)(rc->bottom - 1 - rc->top);

			//////////
			// Top (NW to NE)
			//////
				// Compute FROM and TO colors
				lfRed = (f32)colorNW.red;			lfRedTo = (f32)colorNE.red;
				lfGrn = (f32)colorNW.grn;			lfGrnTo = (f32)colorNE.grn;
				lfBlu = (f32)colorNW.blu;			lfBluTo = (f32)colorNE.blu;

				// Compute increment
				lfRedInc	= (lfRedTo - lfRed) / lfWidth;
				lfGrnInc	= (lfGrnTo - lfGrn) / lfWidth;
				lfBluInc	= (lfBluTo - lfBlu) / lfWidth;

				// Draw it
				iBmpDrawHorizontalLineGradient(bmp, rc->left, rc->right - 1, rc->top, lfRed, lfGrn, lfBlu, lfRedInc, lfGrnInc, lfBluInc);


			//////////
			// Bottom (SW to SE)
			//////
				// Compute FROM and TO colors
				lfRed = (f32)colorSW.red;			lfRedTo = (f32)colorSE.red;
				lfGrn = (f32)colorSW.grn;			lfGrnTo = (f32)colorSE.grn;
				lfBlu = (f32)colorSW.blu;			lfBluTo = (f32)colorSE.blu;

				// Compute increment
				lfRedInc	= (lfRedTo - lfRed) / lfWidth;
				lfGrnInc	= (lfGrnTo - lfGrn) / lfWidth;
				lfBluInc	= (lfBluTo - lfBlu) / lfWidth;

				// Draw it
				iBmpDrawHorizontalLineGradient(bmp, rc->left, rc->right - 1, rc->bottom - 1, lfRed, lfGrn, lfBlu, lfRedInc, lfGrnInc, lfBluInc);


			//////////
			// Left (NW to SW)
			//////
				// Compute FROM and TO colors
				lfRed = (f32)colorNW.red;			lfRedTo = (f32)colorSW.red;
				lfGrn = (f32)colorNW.grn;			lfGrnTo = (f32)colorSW.grn;
				lfBlu = (f32)colorNW.blu;			lfBluTo = (f32)colorSW.blu;

				// Compute increment
				lfRedInc	= (lfRedTo - lfRed) / lfWidth;
				lfGrnInc	= (lfGrnTo - lfGrn) / lfWidth;
				lfBluInc	= (lfBluTo - lfBlu) / lfWidth;

				// Draw it
				iBmpDrawVerticalLineGradient(bmp, rc->top, rc->bottom - 1, rc->left, lfRed, lfGrn, lfBlu, lfRedInc, lfGrnInc, lfBluInc);


			//////////
			// Right (NE to SE)
			//////
				// Compute FROM and TO colors
				lfRed = (f32)colorNE.red;			lfRedTo = (f32)colorSE.red;
				lfGrn = (f32)colorNE.grn;			lfGrnTo = (f32)colorSE.grn;
				lfBlu = (f32)colorNE.blu;			lfBluTo = (f32)colorSE.blu;

				// Compute increment
				lfRedInc	= (lfRedTo - lfRed) / lfWidth;
				lfGrnInc	= (lfGrnTo - lfGrn) / lfWidth;
				lfBluInc	= (lfBluTo - lfBlu) / lfWidth;

				// Draw it
				iBmpDrawVerticalLineGradient(bmp, rc->top, rc->bottom - 1, rc->right - 1, lfRed, lfGrn, lfBlu, lfRedInc, lfGrnInc, lfBluInc);

		} else {
			// Just draw in a solid color
			iBmpDrawHorizontalLine(bmp, rc->left, rc->right - 1, rc->top, colorNW);
			iBmpDrawHorizontalLine(bmp, rc->left, rc->right - 1, rc->bottom - 1, colorNW);
			iBmpDrawVerticalLine(bmp, rc->top, rc->bottom - 1, rc->left, colorNW);
			iBmpDrawVerticalLine(bmp, rc->top, rc->bottom - 1, rc->right - 1, colorNW);
		}
	}

	void iBmpDrawHorizontalLine(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, SBgra color)
	{
		s32		lnX;
		SBgr*	lbgr;
		SBgra*	lbgra;


		// Get our starting point
		lbgr	= (SBgr*)(bmp->bd  + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX1 * (bmp->bi.biBitCount / 8)));
		lbgra	= (SBgra*)(bmp->bd + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX1 * (bmp->bi.biBitCount / 8)));

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

	void iBmpDrawVerticalLine(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, SBgra color)
	{
		s32		lnY;
		SBgr*	lbgr;
		SBgra*	lbgra;


		// Get our starting point
		lbgr	= (SBgr*)(bmp->bd  + ((bmp->bi.biHeight - tnY1 - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));
		lbgra	= (SBgra*)(bmp->bd + ((bmp->bi.biHeight - tnY1 - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));

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
					lbgr = (SBgr*)((s8*)lbgr - bmp->rowWidth);
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
					lbgra->alp	= 255;
					lbgra->red	= color.red;
					lbgra->grn	= color.grn;
					lbgra->blu	= color.blu;

					// Move to next row
					lbgra = (SBgra*)((s8*)lbgra - bmp->rowWidth);
				}
			}
		}
	}




//////////
//
// Gradient line algorithms
//
//////
	void iBmpDrawHorizontalLineGradient(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc)
	{
		s32		lnX;
		SBgr*	lbgr;
		SBgra*	lbgra;


		// Get our starting point
		lbgr	= (SBgr*)(bmp->bd  + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX1 * (bmp->bi.biBitCount / 8)));
		lbgra	= (SBgra*)(bmp->bd + ((bmp->bi.biHeight - tnY - 1) * bmp->rowWidth) + (tnX1 * (bmp->bi.biBitCount / 8)));

		if (bmp->bi.biBitCount == 24)
		{
			// Iterate for each column
			for (lnX = tnX1; lnX <= tnX2; lnX++, tfRed += tfRedInc, tfGrn += tfGrnInc, tfBlu += tfBluInc)
			{
				// Are we on the bitmap?
				if (lnX >= 0 && lnX < bmp->bi.biWidth)
				{
					// Draw the pixel
					lbgr->red	= (u8)tfRed;
					lbgr->grn	= (u8)tfGrn;
					lbgr->blu	= (u8)tfBlu;

					// Move to next column
					++lbgr;
				}
			}

		} else if (bmp->bi.biBitCount == 32) {
			// Iterate for each column
			for (lnX = tnX1; lnX <= tnX2; lnX++, tfRed += tfRedInc, tfGrn += tfGrnInc, tfBlu += tfBluInc)
			{
				// Are we on the bitmap?
				if (lnX >= 0 && lnX < bmp->bi.biWidth)
				{
					// Draw the pixel
					lbgra->alp	= 255;
					lbgra->red	= (u8)tfRed;
					lbgra->grn	= (u8)tfGrn;
					lbgra->blu	= (u8)tfBlu;

					// Move to next column
					++lbgra;
				}
			}
		}
	}

	void iBmpDrawVerticalLineGradient(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc)
	{
		s32		lnY;
		SBgr*	lbgr;
		SBgra*	lbgra;


		// Get our starting point
		lbgr	= (SBgr*)(bmp->bd  + ((bmp->bi.biHeight - tnY1 - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));
		lbgra	= (SBgra*)(bmp->bd + ((bmp->bi.biHeight - tnY1 - 1) * bmp->rowWidth) + (tnX * (bmp->bi.biBitCount / 8)));

		if (bmp->bi.biBitCount == 24)
		{
			// Iterate for each column
			for (lnY = tnY1; lnY <= tnY2; lnY++, tfRed += tfRedInc, tfGrn += tfGrnInc, tfBlu += tfBluInc)
			{
				// Are we on the bitmap?
				if (lnY >= 0 && lnY < bmp->bi.biHeight)
				{
					// Draw the pixel
					lbgr->red	= (u8)tfRed;
					lbgr->grn	= (u8)tfGrn;
					lbgr->blu	= (u8)tfBlu;

					// Move to next row
					lbgr = (SBgr*)((s8*)lbgr - bmp->rowWidth);
				}
			}

		} else if (bmp->bi.biBitCount == 32) {
			// Iterate for each column
			for (lnY = tnY1; lnY <= tnY2; lnY++, tfRed += tfRedInc, tfGrn += tfGrnInc, tfBlu += tfBluInc)
			{
				// Are we on the bitmap?
				if (lnY >= 0 && lnY < bmp->bi.biHeight)
				{
					// Draw the pixel
					lbgra->alp	= 255;
					lbgra->red	= (u8)tfRed;
					lbgra->grn	= (u8)tfGrn;
					lbgra->blu	= (u8)tfBlu;

					// Move to next row
					lbgra = (SBgra*)((s8*)lbgra - bmp->rowWidth);
				}
			}
		}
	}




//////////
//
// Called to scale one bitmap into another.
//
// Note:  All of this code was adapted from the Visual FreePro.
// Note:  See https://github.com/RickCHodgin/libsf (in vvm\core\).
//
//////
	u32 iBmpScale(SBitmap* bmpDst, SBitmap* bmpSrc)
	{
		u32		lnResult;
		f32		lfVertical, lfHorizontal;
		RECT	lrc;


		// Make sure our environment is sane
		lnResult = -1;
		if (bmpDst->bi.biBitCount == 24 || bmpDst->bi.biBitCount == 32)
		{
			if (bmpSrc->bi.biBitCount == 24 || bmpSrc->bi.biBitCount == 32)
			{
				// We have valid source and destination bitmaps
				if (bmpSrc->bi.biWidth == bmpDst->bi.biWidth && bmpSrc->bi.biHeight == bmpDst->bi.biHeight)
				{
					// They're the same size
					if (bmpSrc->bi.biBitCount == bmpDst->bi.biBitCount)
					{
						// They're the same bit counts, do a fast copy
						memcpy(bmpDst->bd, bmpSrc->bd, bmpSrc->bi.biSizeImage);

					} else {
						// Do a bitBlt to translate bit counts
						SetRect(&lrc, 0, 0, bmpDst->bi.biWidth, bmpDst->bi.biHeight);
						iBmpBitBlt(bmpDst, &lrc, bmpSrc);
					}
					// Indicate success
					lnResult = 1;

				} else {
					// We need to scale
					lfVertical		= (f32)bmpSrc->bi.biHeight / (f32)bmpDst->bi.biHeight;
					lfHorizontal	= (f32)bmpSrc->bi.biWidth  / (f32)bmpDst->bi.biWidth;
					lnResult		= iiBmpScale_Process(bmpDst, bmpSrc, lfVertical, lfHorizontal);
				}
			}
		}

		// Indicate our failure or success
		return(lnResult);
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
	u32 iiBmpScale_Process(SBitmap* bmpDst, SBitmap* bmpSrc, f32 tfVerticalScaler, f32 tfHorizontalScaler)
	{
		s32				lnY, lnX;
		SBitmapProcess	bp;


		// Being the scaling procedure
		bp.src		= bmpSrc;
		bp.ratioV	= (f32)bmpSrc->bi.biHeight	/ (f32)bmpDst->bi.biHeight;
		bp.ratioH	= (f32)bmpSrc->bi.biWidth	/ (f32)bmpDst->bi.biWidth;
		bp.pixels	= (SBgraf*)malloc(((u32)bp.ratioV + 16) * ((u32)bp.ratioH + 16) * sizeof(SBgraf));

		// Iterate through every pixel
		for (lnY = 0; lnY < bmpDst->bi.biHeight; lnY++)
		{
			// Grab the offset for this line
			if (bmpDst->bi.biBitCount == 24)		bp.optr		= (SBgr*)( bmpDst->bd + ((bmpDst->bi.biHeight - lnY - 1) * bmpDst->rowWidth));
			else									bp.optra	= (SBgra*)(bmpDst->bd + ((bmpDst->bi.biHeight - lnY - 1) * bmpDst->rowWidth));

			// Repeat for every pixel across this row
			for (lnX = 0; lnX < bmpDst->bi.biWidth; lnX++)
			{
				// Compute data for this spanned pixel
				bp.uly	= min((f32)lnY * bp.ratioV, (f32)bmpSrc->bi.biHeight - bp.ratioV);
				bp.ulx	= min((f32)lnX * bp.ratioH, (f32)bmpSrc->bi.biWidth  - bp.ratioH);
				bp.lry	= bp.uly + bp.ratioV;
				bp.lrx	= bp.ulx + bp.ratioH;

				// Get all the color information for this potentially spanned pixel
				iiBmpScale_processPixels(&bp);

				// Store the color
				if (bmpDst->bi.biBitCount == 24)
				{
					bp.optr->red = (u8)bp.red;
					bp.optr->grn = (u8)bp.grn;
					bp.optr->blu = (u8)bp.blu;
					// Move to the next pixel
					++bp.optr;

				} else {
					bp.optra->red = (u8)bp.red;
					bp.optra->grn = (u8)bp.grn;
					bp.optra->blu = (u8)bp.blu;
					// Move to the next pixel
					++bp.optra;
				}
			}
		}
		// When we get here, we've computed everything

		// Finished, indicate the pixel count
		return(bmpDst->bi.biHeight * bmpDst->bi.biWidth * sizeof(SBgr));
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
	void iiBmpScale_processPixels(SBitmapProcess* bp)
	{
		u32		lnI;
		f32		lfRed, lfGrn, lfBlu, lfAlp, lfAreaAccumulator;


		// Raise the flags for which portions are valid / required
		bp->spans2H		= (iiBmpScale_processGetIntegersBetween(bp->ulx, bp->lrx) >= 1);		// It occupies at least two pixels horizontally (itself and one more)
		bp->spans3H		= (iiBmpScale_processGetIntegersBetween(bp->ulx, bp->lrx) >= 2);		// It occupies at least three pixels horizontally (itself, at least one in the middle, and one at the right)
		bp->spans2V		= (iiBmpScale_processGetIntegersBetween(bp->uly, bp->lry) >= 1);		// It occupies at least two pixels vertically (itself and one more)
		bp->spans3V		= (iiBmpScale_processGetIntegersBetween(bp->uly, bp->lry) >= 2);		// It occupies at least three pixels vertically (itself, at least one in the middle, and one at the right)

		// Reset the point count
		bp->count		= 0;

		// Indicate the start of this input line
		if (bp->src->bi.biBitCount == 24)
		{
			// 24-bit bitmap
			bp->iptr		= (SBgr*)(bp->src->bd + ((bp->src->bi.biHeight - (s32)bp->uly - 1) * bp->src->rowWidth));	// current line
			bp->iptrAnchor	= (SBgr*)(bp->src->bd + ((bp->src->bi.biHeight                   ) * bp->src->rowWidth));	// root anchor (does not include the conversion from base-1)

		} else {
			// 32-bit bitmap
			bp->iptra		= (SBgra*)(bp->src->bd + ((bp->src->bi.biHeight - (s32)bp->uly - 1) * bp->src->rowWidth));	// current line
			bp->iptrAnchora	= (SBgra*)(bp->src->bd + ((bp->src->bi.biHeight                   ) * bp->src->rowWidth));	// root anchor (does not include the conversion from base-1)
		}


		//////////
		// The following functions (if called) update the number of pieces of picture data to add to the output
		//////
			//////////
			// 1 - upper-left (always, spans at most one pixel)
			//////
				iiBmpScale_processSpannedPixel1(bp);

			//////////
			// 2 - upper-middle (optional, spans at most multiple partial or full pixels, but only if 1, 2 and 3 exist)
			//////
				if (bp->spans3H)
					iiBmpScale_processSpannedPixel2(bp);


			//////////
			// 3 - upper-right (optional, spans at most one pixel, but only if 1 and 3 exist (as 1 and 2))
			//////
				if (bp->spans2H || bp->spans3H)
					iiBmpScale_processSpannedPixel3(bp);


			//////////
			// 4 - middle-left (optional, spans at most multiple partial or full pixels)
			//////
				if (bp->spans3V && bp->spans2V)
					iiBmpScale_processSpannedPixel4(bp);


			//////////
			// 5 - middle-middle (optional, can span multiple partial or full pixels)
			//////
				if (bp->spans3V && bp->spans3H)
					iiBmpScale_processSpannedPixel5(bp);


			//////////
			// 6 - middle-right (optional, spans at most multiple partial or full pixels)
			//////
				if (bp->spans3V && (bp->spans2H || bp->spans3H))
					iiBmpScale_processSpannedPixel6(bp);


			//////////
			// 7 - lower-left (optional, spans at most one pixel)
			//////
				if (bp->spans2V)
					iiBmpScale_processSpannedPixel7(bp);


			//////////
			// 8 - lower-middle (optional, spans at most multiple partial or full pixels)
			//////
				if (bp->spans2V && bp->spans3H)
					iiBmpScale_processSpannedPixel8(bp);


			//////////
			// 9 - lower-right (optional, spans at most one pixel)
			//////
				if (bp->spans2V && (bp->spans2H || bp->spans3H))
					iiBmpScale_processSpannedPixel9(bp);


		//////////
		// Add up all the pixels to compute the specified value
		//////
			lfAreaAccumulator = 0.0;
			for (lnI = 0; lnI < bp->count; lnI++)
				lfAreaAccumulator += bp->pixels[lnI].area;

			// Initialize
			lfRed	= 0;
			lfGrn	= 0;
			lfBlu	= 0;
			lfAlp	= 0;

			// Now, compute each component as its part of the total area
			for (lnI = 0; lnI < bp->count; lnI++)
			{
				// Derive this portion component
				lfRed	+=		bp->pixels[lnI].red	*	(bp->pixels[lnI].area / lfAreaAccumulator);
				lfGrn	+=		bp->pixels[lnI].grn	*	(bp->pixels[lnI].area / lfAreaAccumulator);
				lfBlu	+=		bp->pixels[lnI].blu	*	(bp->pixels[lnI].area / lfAreaAccumulator);
				lfAlp	+=		bp->pixels[lnI].alp	*	(bp->pixels[lnI].area / lfAreaAccumulator);
			}

			// When we get here, we have our values, now create the final summed up output
			bp->red = (u8)(lfRed + 0.5);
			bp->grn = (u8)(lfGrn + 0.5);
			bp->blu = (u8)(lfBlu + 0.5);
			bp->alp = (u8)(lfAlp + 0.5);
	}




//////////
//
// 1 - upper-left (see iGetSpannedPixelColors() above)
// Upper left pixels is ALWAYS computed. It may be the ONLY one computed, but it is always computed.
//
//////
	void iiBmpScale_processSpannedPixel1(SBitmapProcess* bp)
	{
		// Store left- and right-sides for this spanned pixel
		bp->left			= (s32)min(bp->ulx,			bp->src->bi.biWidth - 1);
		bp->right			= (s32)min(bp->lrx,			bp->src->bi.biWidth - 1);

		// Compute the middle section in pixels
		// Note: -2 is for -1 base 0, and -1 because we want the max value to be one before the width/height
		bp->middleStartH	= (s32)min(bp->ulx + 1,		bp->src->bi.biWidth  - 1);		// next pixel right of upper-left
		bp->middleFinishH	= (s32)min(bp->lrx - 1,		bp->src->bi.biWidth  - 1);		// next pixel left of upper-right (which is actually lower-right, but on this upper line)
		bp->middleStartV	= (s32)min(bp->uly + 1,		bp->src->bi.biHeight - 1);		// next pixel right of left-side pixels
		bp->middleFinishV	= (s32)min(bp->lry - 1,		bp->src->bi.biHeight - 1);		// next pixel left of right-side pixels

		// Find out where this upper-left pixel falls
		if (!bp->spans2H)	bp->widthLeft	=      bp->lrx          - bp->ulx;		// Entire width is within this one pixel, so it's only a portion of the pixel's overall width
		else				bp->widthLeft	= (f32)bp->middleStartH - bp->ulx;		// It spans from where it is to the right of the pixel square

 		if (!bp->spans2V)	bp->height		=      bp->lry          - bp->uly;			// It's entire height is within this one pixel, so it's only a portion of the pixel's overall height
		else				bp->height		= (f32)bp->middleStartV - bp->uly;			// It spans from where it is to the bottom of the pixel square

		// Compute the area for this pixel component
		bp->area = bp->widthLeft * bp->height;

		// Store the colors for this point
		if (bp->src->bi.biBitCount == 24)
		{
			// 24-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->left * 3)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->left * 3)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->left * 3)))->blu);
			(bp->pixels[bp->count]).area	= bp->area;

		} else {
			// 32-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->left * 4)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->left * 4)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->left * 4)))->blu);
			(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->left * 4)))->alp);
			(bp->pixels[bp->count]).area	= bp->area;
		}

		// Move over for the next point
		++bp->count;
	}




//////////
//
// 2 - upper-middle (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least one, full, middle pixel
//
//////
	void iiBmpScale_processSpannedPixel2(SBitmapProcess* bp)
	{
		s32 lnPixel;


		// For every middle pixel, apply these values
		for (lnPixel = bp->middleStartH; lnPixel < bp->middleFinishH; lnPixel++)
		{
			// Store this pixel data
			if (bp->src->bi.biBitCount == 24)
			{
				// 24-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptr + (lnPixel * 3)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptr + (lnPixel * 3)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptr + (lnPixel * 3)))->blu);
				(bp->pixels[bp->count]).area	= bp->height;

			} else {
				// 32-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptra + (lnPixel * 4)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptra + (lnPixel * 4)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptra + (lnPixel * 4)))->blu);
				(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptra + (lnPixel * 4)))->alp);
				(bp->pixels[bp->count]).area	= bp->height;
			}

			// Move over for the next point
			++bp->count;
		}
	}




//////////
//
// 3 - upper-right (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row
//
//////
	void iiBmpScale_processSpannedPixel3(SBitmapProcess* bp)
	{
		// Find out where this upper-left pixel falls
		bp->widthRight = bp->lrx - (f32)bp->right;		// It spans from the start of the right-most pixel to wherever it falls therein

		// Compute the area for this pixel component
		bp->area = bp->widthRight * bp->height;

		// Store this pixel data
		if (bp->src->bi.biBitCount == 24)
		{
			// 24-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->right * 3)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->right * 3)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptr + (bp->right * 3)))->blu);
			(bp->pixels[bp->count]).area	= bp->area;

		} else {
			// 32-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->right * 4)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->right * 4)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->right * 4)))->blu);
			(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptra + (bp->right * 4)))->alp);
			(bp->pixels[bp->count]).area	= bp->area;
		}

		// Move over for the next point
		++bp->count;
	}




//////////
//
// 4 - middle-left (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least an entire second row
//
//////
// 	void iValidatePoint(SBitmapProcess* bp, s32 tnX, s32 tnY)
// 	{
// 		if (tnX >= bp->bii->biWidth)
// 			_asm nop;
// 
// 		if (tnY >= bp->bii->biHeight)
// 			_asm nop;
// 	}

	void iiBmpScale_processSpannedPixel4(SBitmapProcess* bp)
	{
		s32 lnPixelY;


		// Repeat for each middle pixel
		for (lnPixelY = bp->middleStartV; lnPixelY <= bp->middleFinishV; lnPixelY++)
		{
			// Store the colors for this point
			if (bp->src->bi.biBitCount == 24)
			{
				// 24-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->left * 3)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->left * 3)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->left * 3)))->blu);
				(bp->pixels[bp->count]).area	= bp->widthLeft;

			} else {
				// 32-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->left * 4)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->left * 4)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->left * 4)))->blu);
				(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->left * 4)))->alp);
				(bp->pixels[bp->count]).area	= bp->widthLeft;
			}

			// Move over for the next point
			++bp->count;
		}
	}




//////////
//
// 5 - middle-middle (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row, and at least
// one pixel in the middle
//
//////
	void iiBmpScale_processSpannedPixel5(SBitmapProcess* bp)
	{
		s32 lnPixelY, lnPixelX;


		// Iterate for each pixel row vertically
		for (lnPixelY = bp->middleStartV; lnPixelY <= bp->middleFinishV; lnPixelY++)
		{
			// And each individual pixel horizontally
			for (lnPixelX = bp->middleStartH; lnPixelX <= bp->middleFinishH; lnPixelX++)
			{
				// Store the colors for this point
				if (bp->src->bi.biBitCount == 24)
				{
					// 24-bit bitmap
					(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 3)))->red);
					(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 3)))->grn);
					(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 3)))->blu);
					(bp->pixels[bp->count]).area	= 1.0;

				} else {
					// 32-bit bitmap
					(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 4)))->red);
					(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 4)))->grn);
					(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 4)))->blu);
					(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (lnPixelX * 4)))->alp);
					(bp->pixels[bp->count]).area	= 1.0;
				}

				// Move over for the next point
				++bp->count;
			}
		}
	}




//////////
//
// 6 - middle-right (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row, and a right pixel
//
//////
	void iiBmpScale_processSpannedPixel6(SBitmapProcess* bp)
	{
		s32 lnPixelY;


		// Repeat for each middle pixel
		for (lnPixelY = bp->middleStartV; lnPixelY <= bp->middleFinishV; lnPixelY++)
		{
			// Store the colors for this point
			if (bp->src->bi.biBitCount == 24)
			{
				// 24-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->right * 3)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->right * 3)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - (lnPixelY * bp->src->rowWidth) + (bp->right * 3)))->blu);
				(bp->pixels[bp->count]).area	= bp->widthRight;

			} else {
				// 32-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->right * 4)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->right * 4)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->right * 4)))->blu);
				(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - (lnPixelY * bp->src->rowWidth) + (bp->right * 4)))->alp);
				(bp->pixels[bp->count]).area	= bp->widthRight;
			}

			// Move over for the next point
			++bp->count;
		}
	}




//////////
//
// 7 - lower-left (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row
//
//////
	void iiBmpScale_processSpannedPixel7(SBitmapProcess* bp)
	{
		// Compute the area
		bp->height	= bp->lry - (f32)((s32)bp->lry);
		bp->area	= bp->widthLeft * bp->height;

		// Store the colors for this point
		if (bp->src->bi.biBitCount == 24)
		{
			// 24-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 3)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 3)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 3)))->blu);
			(bp->pixels[bp->count]).area	= bp->area;

		} else {
			// 32-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 4)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 4)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 4)))->blu);
			(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->left * 4)))->alp);
			(bp->pixels[bp->count]).area	= bp->area;
		}

		// Move over for the next point
		++bp->count;
	}




//////////
//
// 8 - lower-middle (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row, and at least one
// pixel in the middle
//
//////
	void iiBmpScale_processSpannedPixel8(SBitmapProcess* bp)
	{
		s32 lnPixelX;


		// For every middle pixel, apply these values
		for (lnPixelX = bp->middleStartH; lnPixelX <= bp->middleFinishH; lnPixelX++)
		{
			// Store the colors for this point
			if (bp->src->bi.biBitCount == 24)
			{
				// 24-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 3)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 3)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 3)))->blu);
				(bp->pixels[bp->count]).area	= bp->height;

			} else {
				// 32-bit bitmap
				(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 4)))->red);
				(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 4)))->grn);
				(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 4)))->blu);
				(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (lnPixelX * 4)))->alp);
				(bp->pixels[bp->count]).area	= bp->height;
			}

			// Move over for the next point
			++bp->count;
		}
	}




//////////
//
// 9 - lower-right (see iGetSpannedPixelColors() above)
// It is known when this function is called that there is at least a second row, and a right pixel
//
//////
	void iiBmpScale_processSpannedPixel9(SBitmapProcess* bp)
	{
		// Compute the area
		bp->area = bp->widthRight * bp->height;

		// Store the colors for this point
		if (bp->src->bi.biBitCount == 24)
		{
			// 24-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 3)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 3)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgr*)((u8*)bp->iptrAnchor - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 3)))->blu);
			(bp->pixels[bp->count]).area	= bp->area;

		} else {
			// 32-bit bitmap
			(bp->pixels[bp->count]).red		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 4)))->red);
			(bp->pixels[bp->count]).grn		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 4)))->grn);
			(bp->pixels[bp->count]).blu		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 4)))->blu);
			(bp->pixels[bp->count]).alp		= (f32)(((SBgra*)((u8*)bp->iptrAnchora - ((bp->middleFinishV + 1) * bp->src->rowWidth) + (bp->right * 4)))->alp);
			(bp->pixels[bp->count]).area	= bp->area;
		}

		// Move over for the next point
		++bp->count;
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
	u32 iiBmpScale_processGetIntegersBetween(f32 p1, f32 p2)
	{
		u32 lfMin, lfMax;


		// Grab the integer values (without rounding)
		lfMin = (u32)min(p1,p2);
		lfMax = (u32)max(p1,p2);

		// Indicate the number between
		return(lfMax - lfMin);
	}





//////////
//
// Draw the icon controls
//
//////
	void iDrawScreen(RECT* trc)
	{
		//////////
		// Icon and controls
		//////
			SetRect(&winScreen.appIcon.rc,		30,					1,				30 + winScreen.appIcon.bmp->bi.biWidth,					1 + winScreen.appIcon.bmp->bi.biHeight);
			SetRect(&winScreen.minimize.rc,		trc->right - 132,	trc->top + 1,	trc->right - 132 + winScreen.minimize.bmp->bi.biWidth,	trc->top + 1 + winScreen.minimize.bmp->bi.biHeight);
			SetRect(&winScreen.maximize.rc,		trc->right - 104,	trc->top + 1,	trc->right - 104 + winScreen.maximize.bmp->bi.biWidth,	trc->top + 1 + winScreen.maximize.bmp->bi.biHeight);
			SetRect(&winScreen.close.rc,		trc->right - 77,	trc->top + 1,	trc->right - 77  + winScreen.close.bmp->bi.biWidth,		trc->top + 1 + winScreen.close.bmp->bi.biHeight);

			iBmpBitBltObject(&winScreen.bmp, &winScreen.appIcon,	winScreen.appIcon.bmp);
			iBmpBitBltObject(&winScreen.bmp, &winScreen.minimize,	winScreen.minimize.bmp);
			iBmpBitBltObject(&winScreen.bmp, &winScreen.maximize,	winScreen.maximize.bmp);
			iBmpBitBltObject(&winScreen.bmp, &winScreen.close,		winScreen.close.bmp);


		//////////
		// Corner triangles
		//////
			// Set the areas for mouse identifying
			SetRect(&winScreen.arrowUl.rc, trc->left, trc->top, trc->left + winScreen.arrowUl.bmp->bi.biWidth, trc->top + winScreen.arrowUl.bmp->bi.biHeight);
			SetRect(&winScreen.arrowUr.rc, trc->right - winScreen.arrowUr.bmp->bi.biWidth, trc->top, trc->right, trc->top + winScreen.arrowUr.bmp->bi.biHeight);
			SetRect(&winScreen.arrowLr.rc, trc->right - winScreen.arrowLr.bmp->bi.biWidth, trc->bottom - winScreen.arrowLr.bmp->bi.biHeight, trc->right, trc->bottom);
			SetRect(&winScreen.arrowLl.rc, trc->left, trc->bottom - winScreen.arrowLl.bmp->bi.biHeight, trc->left + winScreen.arrowLl.bmp->bi.biWidth, trc->bottom);

			// Draw them
			iBmpBitBltObjectMask(&winScreen.bmp, &winScreen.arrowUl, winScreen.arrowUl.bmp);
			iBmpBitBltObjectMask(&winScreen.bmp, &winScreen.arrowUr, winScreen.arrowUr.bmp);
			iBmpBitBltObjectMask(&winScreen.bmp, &winScreen.arrowLr, winScreen.arrowLr.bmp);
			iBmpBitBltObjectMask(&winScreen.bmp, &winScreen.arrowLl, winScreen.arrowLl.bmp);


		//////////
		// Draw the app title
		//////
			SetRect(&winScreen.rcCaption, winScreen.appIcon.rc.right + 8, winScreen.appIcon.rc.top + 2, winScreen.minimize.rc.left - 8, winScreen.appIcon.rc.bottom);
			SelectObject(winScreen.bmp.hdc, winScreen.font->hfont);
			SetTextColor(winScreen.bmp.hdc, (COLORREF)RGB(black.red, black.grn, black.blu));
//			SetBkColor(winScreen.bmp.hdc, (COLORREF)RGB(light_green.red, light_green.grn, light_green.blu));
			SetBkMode(winScreen.bmp.hdc, TRANSPARENT);
			DrawTextA(winScreen.bmp.hdc, cgcScreenTitle, sizeof(cgcScreenTitle) - 1, &winScreen.rcCaption, DT_VCENTER | DT_END_ELLIPSIS);
	}

	void iDrawJDebi(RECT* trc)
	{
		//////////
		// Icon
		//////
			SetRect(&winJDebi.appIcon.rc,		30,					1,				30 + winJDebi.appIcon.bmp->bi.biWidth,				1 + winJDebi.appIcon.bmp->bi.biHeight);
			SetRect(&winJDebi.close.rc,			trc->right - 77,	trc->top + 1,	trc->right - 77  + winJDebi.close.bmp->bi.biWidth,	trc->top + 1 + winJDebi.close.bmp->bi.biHeight);
			SetRect(&winJDebi.maximize.rc,		trc->right - 104,	trc->top + 1,	trc->right - 104 + winJDebi.maximize.bmp->bi.biWidth,	trc->top + 1 + winJDebi.maximize.bmp->bi.biHeight);
			SetRect(&winJDebi.minimize.rc,		trc->right - 132,	trc->top + 1,	trc->right - 132 + winJDebi.minimize.bmp->bi.biWidth,	trc->top + 1 + winJDebi.minimize.bmp->bi.biHeight);
			SetRect(&winJDebi.move.rc,			trc->right - 132,	trc->top + 1,	trc->right - 132 + winJDebi.minimize.bmp->bi.biWidth,	trc->top + 1 + winJDebi.minimize.bmp->bi.biHeight);

			iBmpBitBltObject(&winJDebi.bmp, &winJDebi.appIcon,		winJDebi.appIcon.bmp);
			iBmpBitBltObject(&winJDebi.bmp, &winJDebi.minimize,		winJDebi.minimize.bmp);
			iBmpBitBltObject(&winJDebi.bmp, &winJDebi.maximize,		winJDebi.maximize.bmp);
			iBmpBitBltObject(&winJDebi.bmp, &winJDebi.close,		winJDebi.close.bmp);


		//////////
		// Corner triangles
		//////
			// Set the areas for mouse identifying
			SetRect(&winJDebi.arrowUl.rc, trc->left, trc->top, trc->left + winJDebi.arrowUl.bmp->bi.biWidth, trc->top + winJDebi.arrowUl.bmp->bi.biHeight);
			SetRect(&winJDebi.arrowUr.rc, trc->right - winJDebi.arrowUr.bmp->bi.biWidth, trc->top, trc->right, trc->top + winJDebi.arrowUr.bmp->bi.biHeight);
			SetRect(&winJDebi.arrowLr.rc, trc->right - winJDebi.arrowLr.bmp->bi.biWidth, trc->bottom - winJDebi.arrowLr.bmp->bi.biHeight, trc->right, trc->bottom);
			SetRect(&winJDebi.arrowLl.rc, trc->left, trc->bottom - winJDebi.arrowLl.bmp->bi.biHeight, trc->left + winJDebi.arrowLl.bmp->bi.biWidth, trc->bottom);

			// Draw them
			iBmpBitBltObjectMask(&winJDebi.bmp, &winJDebi.arrowUl, winJDebi.arrowUl.bmp);
			iBmpBitBltObjectMask(&winJDebi.bmp, &winJDebi.arrowUr, winJDebi.arrowUr.bmp);
			iBmpBitBltObjectMask(&winJDebi.bmp, &winJDebi.arrowLr, winJDebi.arrowLr.bmp);
			iBmpBitBltObjectMask(&winJDebi.bmp, &winJDebi.arrowLl, winJDebi.arrowLl.bmp);


		//////////
		// Draw the app title
		//////
			SetRect(&winJDebi.rcCaption, winJDebi.appIcon.rc.right + 8, winJDebi.appIcon.rc.top + 2, winJDebi.rcClient.right - 8, winJDebi.appIcon.rc.bottom);
			SelectObject(winJDebi.bmp.hdc, winJDebi.font->hfont);
			SetTextColor(winJDebi.bmp.hdc, (COLORREF)RGB(black.red, black.grn, black.blu));
//			SetBkColor(winJDebi.bmp.hdc, (COLORREF)RGB(light_green.red, light_green.grn, light_green.blu));
			SetBkMode(winJDebi.bmp.hdc, TRANSPARENT);
			DrawTextA(winJDebi.bmp.hdc, cgcJDebiTitle, sizeof(cgcJDebiTitle) - 1, &winJDebi.rcCaption, DT_VCENTER | DT_END_ELLIPSIS);
	}




//////////
//
// Called to redraw the screen
//
//////
	void iRedrawScreen(SWindow* win)
	{
//		u32		lnI;
		RECT	lrc;


		// White background
		iBmpFillRect(&winScreen.bmp, &winScreen.rcClient, colorNW, colorNE, colorSW, colorSE, true);

		// Draw the border around the whole window
		iBmpFrameRect(&winScreen.bmp, &winScreen.rcClient, black, black, black, black, false);

		// Draw the controls
		iDrawScreen(&winScreen.rcClient);

		// Draw the border around the client area
		SetRect(&lrc, 8, winScreen.appIcon.bmp->bi.biHeight + 2, winScreen.rcClient.right - winScreen.appIcon.bmp->bi.biHeight - 2, winScreen.rcClient.bottom - winScreen.appIcon.bmp->bi.biHeight - 2);
		iBmpFillRect(&winScreen.bmp, &lrc, white, white, white, white, false);
		InflateRect(&lrc, 1, 1);
		iBmpFrameRect(&winScreen.bmp, &lrc, black, black, black, black, false);
	}




//////////
//
// Called to redraw the JDebi window
//
//////
	void iRedrawJDebi(SWindow* win)
	{
//		u32		lnI;
		RECT	lrc;


		// White background
		iBmpFillRect(&winJDebi.bmp, &winJDebi.rcClient, colorNW, colorNE, colorSW, colorSE, true);

		// Draw the border around the whole window
		iBmpFrameRect(&winJDebi.bmp, &winJDebi.rcClient, black, black, black, black, false);

		// Draw the JDebi inner content
		iDrawJDebi(&winJDebi.rcClient);

		// Draw the border around the client area
		SetRect(&lrc, 8, winScreen.appIcon.bmp->bi.biHeight + 2, winJDebi.rcClient.right - winScreen.appIcon.bmp->bi.biHeight - 2, winJDebi.rcClient.bottom - winScreen.appIcon.bmp->bi.biHeight - 1);
		iBmpFillRect(&winJDebi.bmp, &lrc, white, white, white, white, false);
		InflateRect(&lrc, 1, 1);
		iBmpFrameRect(&winJDebi.bmp, &lrc, black, black, black, black, false);
	}
