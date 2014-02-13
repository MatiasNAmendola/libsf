//////////
//
// /libsf/source/vjr/vjr_defs.h
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




//////////
// vjr.cpp
//////
//	int APIENTRY		WinMain									(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, s32 nCmdShow);
	INT_PTR CALLBACK	About									(HWND h, UINT m, WPARAM w, LPARAM l);


//////////
// vjr_sup.cpp
//////
	void				initialize								(HACCEL* hAccelTable);
	void				iLoadObject								(SObject* obj, const u8* bmpRawFileData, const u8* bmpRawFileDataOver);
	void				iConvertBitmapTo32Bits					(SBitmap* bmp);
	void				iCopyBitmap24ToBitmap32					(SBitmap* bmp32, SBitmap* bmp24);
	void				iDeleteBitmap							(SBitmap* bmp);
	void				iCreateMessageWindow					(void);
	HWND				iCreateInterfaceWindow					(void);
	void				iPopulateAndCreateBitmap				(SBitmap* bmp, int tnWidth, int tnHeight);
	bool				isValidWindow							(u32 tnWindow);

	DWORD WINAPI		iReadEvents_messageWindow				(LPVOID lpParameter);
	LRESULT CALLBACK	iWndProc_messageWindow					(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	DWORD WINAPI		iReadEvents_interfaceWindow				(LPVOID lpParameter);
	LRESULT CALLBACK	iWndProc_interfaceWindow				(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	bool				iShutdownPolitely						(void);

	void				iResizeInterfaceWindow					(bool tlForce);
	void				iSetInterfaceWindowSize					(s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight, bool tlForce);
	HBITMAP				iCreateBitmap							(HDC thdc, int tnWidth, int tnHeight, int tnPlanes, int tnBits, void** tbd, BITMAPFILEHEADER* tbh, BITMAPINFOHEADER* tbi);
	int					iComputeRowWidth						(SBitmap* bmp);
	void				iComputeWindowClientAreaDimensions		(SSize* size);
	void				iComputeWindowNonclientAreaDimensions	(SSize* size);
	void				iAdjustInterfaceWindowDimensions		(SSize* size);
	s64					iComputeTimeMilliseconds				(SYSTEMTIME* time);
	s64					iGetSystemTimeMs						(void);
	s64					iGetLocalTimeMs							(void);
	s64					iDiff									(s64 tnBaseValue, s64 tnSubtractionValue);
	s8*					iDuplicateString						(s8* tcText);
	SFont*				iDuplicateFont							(SFont* fontSource);
	SFont*				iCreateFont								(cs8* tcFontName, u32 tnFontSize, u32 tnFontWeight, u32 tnItalics, u32 tnUnderline);
	u32					iFindClosestFontSizeMatch				(s8* tcText, s8* tcFontName, u32 tnFontSize, u32 tnFontBold, u32 tnFontItalic, u32 tnFontUnderline, u32 tnWidth, u32 tnHeight, u32 tnWidthDesired, u32 tnHeightDesired);
	int					iProcessMouseMessage					(UINT m, WPARAM w, LPARAM l);
	void				iTranslateMousePosition					(POINTS* pt);

	SBitmap*			iBmpOrBmpOver							(SObject* obj, bool tlAdditionalTest);
	void				iBitBltObject							(SBitmap* bmpDst, SObject* obj, SBitmap* bmpSrc);
	void				iBitBltObjectMask						(SBitmap* bmpDst, SObject* obj, SBitmap* bmpSrc);
	void				iBitBlt									(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc);
	void				iBitBltMask								(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc);
	void				iDrawControls							(RECT* trc);
	void				iDrawPoint								(SBitmap* bmp, s32 tnX, s32 tnY, SBGRA color);
	void				iFillRect								(SBitmap* bmp, RECT* rc, SBGRA color);
	void				iFrameRect								(SBitmap* bmp, RECT* rc, SBGRA color);
	void				iDrawHorizontalLine						(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, SBGRA color);
	void				iDrawVerticalLine						(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, SBGRA color);

	void				iRedrawAll								(SWindowIface* win);