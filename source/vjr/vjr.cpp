//////////
//
// /libsf/source/vjr/vjr.cpp
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




#include "vjr.h"




int CALLBACK WinMain(	HINSTANCE	hInstance,
						HINSTANCE	hPrevInstance,
						LPSTR		lpCmdLine,
						int			nCmdShow	)
{
	MSG		msg;
	HACCEL	hAccelTable;


	// Initialize
	ghInstance = hInstance;
	initialize(&hAccelTable);

	// Read events
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int) msg.wParam;
}




// ATOM MyRegisterClass(HINSTANCE hInstance)
// {
// 	WNDCLASSEX wcex;
// 
// 	wcex.cbSize = sizeof(WNDCLASSEX);
// 
// 	wcex.style			= CS_HREDRAW | CS_VREDRAW;
// 	wcex.lpfnWndProc	= WndProc;
// 	wcex.cbClsExtra		= 0;
// 	wcex.cbWndExtra		= 0;
// 	wcex.hInstance		= hInstance;
// 	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VJR));
// 	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
// 	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
// 	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_VJR);
// 	wcex.lpszClassName	= szWindowClass;
// 	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
// 
// // 		case WM_COMMAND:
// // 			wmId    = LOWORD(w);
// // 			wmEvent = HIWORD(w);
// // 			// Parse the menu selections:
// // 			switch (wmId)
// // 			{
// // 				case IDM_ABOUT:
// // 					DialogBox(ghInst, MAKEINTRESOURCE(IDD_ABOUTBOX), h, About);
// // 					break;
// // 				case IDM_EXIT:
// // 					DestroyWindow(h);
// // 					break;
// // 				default:
// // 					return DefWindowProc(h, m, w, l);
// // 			}
// // 			break;
// 
// 	return RegisterClassEx(&wcex);
// }




//////////
//
// Message handler for about box
//
//////
	INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		UNREFERENCED_PARAMETER(lParam);
		switch (message)
		{
			case WM_INITDIALOG:
				return (INT_PTR)TRUE;

			case WM_COMMAND:
				if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
				{
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				break;
		}
		return (INT_PTR)FALSE;
	}
