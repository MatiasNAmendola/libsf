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
//	int APIENTRY			WinMain									(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, s32 nCmdShow);


//////////
// objects.cpp
//////
	void					iLoadObject								(SObject* obj, const u8* bmpRawFileData);
	SObject*				iCreateObject							(u32 tnType, void* obj_data);

	// Creation of individual objects
	SObjectEmpty*			iCreateObjectEmpty						(SObjectEmpty*		template_obj, SObject* parent);
	SObjectForm*			iCreateObjectForm						(SObjectForm*		template_obj, SObject* parent);
	SObjectSubform*			iCreateObjectSubform					(SObjectSubform*	template_obj, SObject* parent);
	SObjectLabel*			iCreateObjectLabel						(SObjectLabel*		template_obj, SObject* parent);
	SObjectTextbox*			iCreateObjectTextbox					(SObjectTextbox*	template_obj, SObject* parent);
	SObjectButton*			iCreateObjectButton						(SObjectButton*		template_obj, SObject* parent);
	SObjectEditbox*			iCreateObjectEditbox					(SObjectEditbox*	template_obj, SObject* parent);
	SObjectImage*			iCreateObjectImage						(SObjectImage*		template_obj, SObject* parent);
	SObjectCheckbox*		iCreateObjectCheckbox					(SObjectCheckbox*	template_obj, SObject* parent);
	SObjectOption*			iCreateObjectOption						(SObjectOption*		template_obj, SObject* parent);
	SObjectRadio*			iCreateObjectRadio						(SObjectRadio*		template_obj, SObject* parent);

	// Default render of individual objects
	u32						iRenderEmpty							(SObjectEmpty*		obj);
	u32						iRenderForm								(SObjectForm*		obj);
	u32						iRenderSubform							(SObjectSubform*	obj);
	u32						iRenderLabel							(SObjectLabel*		obj);
	u32						iRenderTextbox							(SObjectTextbox*	obj);
	u32						iRenderButton							(SObjectButton*		obj);
	u32						iRenderEditbox							(SObjectEditbox*	obj);
	u32						iRenderImage							(SObjectImage*		obj);
	u32						iRenderCheckbox							(SObjectCheckbox*	obj);
	u32						iRenderOption							(SObjectOption*		obj);
	u32						iRenderRadio							(SObjectRadio*		obj);


//////////
// vjr_sup.cpp
//////
	void					initialize								(HACCEL* hAccelTable);
	void					iConvertBitmapTo32Bits					(SBitmap* bmp);
	void					iCopyBitmap24ToBitmap32					(SBitmap* bmp32, SBitmap* bmp24);
	void					iDeleteBitmap							(SBitmap* bmp);
	void					iCreateMessageWindow					(void);
	HWND					iCreateScreenWindow						(void);
	HWND					iCreateJDebiWindow						(void);
	void					iPopulateAndCreateBitmap				(SBitmap* bmp, int tnWidth, int tnHeight);
	bool					isValidWindow							(u32 tnWindow);

	DWORD	WINAPI			iReadEvents_messageWindow				(LPVOID lpParameter);
	LRESULT	CALLBACK		iWndProc_messageWindow					(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	DWORD	WINAPI			iReadEvents_screenWindow				(LPVOID lpParameter);
	LRESULT	CALLBACK		iWndProc_screenWindow					(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	DWORD	WINAPI			iReadEvents_jDebiWindow					(LPVOID lpParameter);
	LRESULT	CALLBACK		iWndProc_jDebiWindow					(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	bool					iShutdownPolitely						(void);

	void					iResizeScreenWindow						(bool tlForce);
	void					iResizeJDebiWindow						(bool tlForce);
	void					iSetScreenWindowSize					(s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight, bool tlForce);
	void					iSetJDebiWindowSize						(s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight, bool tlForce);
	HBITMAP					iCreateBitmap							(HDC thdc, int tnWidth, int tnHeight, int tnPlanes, int tnBits, void** tbd, BITMAPFILEHEADER* tbh, BITMAPINFOHEADER* tbi);
	void					iComputeScreenWindowClientAreaDimensions	(SSize* size);
	void					iComputeScreenWindowNonclientAreaDimensions	(SSize* size);
	void					iAdjustScreenWindowDimensions				(SSize* size);
	void					iComputeJDebiWindowClientAreaDimensions		(SSize* size);
	void					iComputeJDebiWindowNonclientAreaDimensions	(SSize* size);
	void					iAdjustJDebiWindowDimensions				(SSize* size);
	s64						iComputeTimeMilliseconds				(SYSTEMTIME* time);
	s64						iGetSystemTimeMs						(void);
	s64						iGetLocalTimeMs							(void);
	s64						iDiff									(s64 tnBaseValue, s64 tnSubtractionValue);
	s8*						iDuplicateString						(s8* tcText);
	SFont*					iFontAllocate							(void);
	SFont*					iFontDuplicate							(SFont* fontSource);
	SFont*					iFontCreate								(cs8* tcFontName, u32 tnFontSize, u32 tnFontWeight, u32 tnItalics, u32 tnUnderline);
	u32						iFindClosestFontSizeMatch				(s8* tcText, s8* tcFontName, u32 tnFontSize, u32 tnFontBold, u32 tnFontItalic, u32 tnFontUnderline, u32 tnWidth, u32 tnHeight, u32 tnWidthDesired, u32 tnHeightDesired);
	int						iProcessMouseMessage					(UINT m, WPARAM w, LPARAM l);
	void					iTranslateMousePosition					(POINTS* pt);

	// EditChain
	void					iEditChainManagerDuplicate				(SEditChainManager** root, SEditChainManager* source);

	// Datum
	void					iDatumDuplicate							(SDatum* datum, s8* data, u32 dataLength);
	void					iDatumDuplicate							(SDatum* datumDst, SDatum* datumSrc);
	void					iiDatumFree								(SDatum* datum);


	//////////
	// Bitmap functions
	//////
		SBitmap*			iBmpAllocate							(void);
		SBitmap*			iBmpCopy								(SBitmap* bmpSrc);
		bool				iBmpValidate							(SBitmap* bmp);
		s32					iBmpComputeRowWidth						(SBitmap* bmp);
		void				iBmpCreateBySize						(SBitmap* bmp, u32 width, u32 height, u32 tnBitCount);
		void				iBmpPopulateBitmapStructure				(SBitmap* bmp, u32 tnWidth, u32 tnHeight, u32 tnBitCount);
		void				iBmpDelete								(SBitmap* bmp, bool tlFreeBits);
		void				iBmpBitBltObject						(SBitmap* bmpDst, SObject* obj, SBitmap* bmpSrc);
		void				iBmpBitBltObjectMask					(SBitmap* bmpDst, SObject* obj, SBitmap* bmpSrc);
		void				iBmpBitBlt								(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc);
		void				iBmpBitBltMask							(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc);
		void				iBmpDrawPoint							(SBitmap* bmp, s32 tnX, s32 tnY, SBgra color);
		void				iBmpFillRect							(SBitmap* bmp, RECT* rc, SBgra colorNW, SBgra colorNE, SBgra colorSW, SBgra colorSE, bool tlUseGradient);
		void				iBmpFrameRect							(SBitmap* bmp, RECT* rc, SBgra colorNW, SBgra colorNE, SBgra colorSW, SBgra colorSE, bool tlUseGradient);
		void				iBmpDrawHorizontalLine					(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, SBgra color);
		void				iBmpDrawVerticalLine					(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, SBgra color);
		void				iBmpDrawHorizontalLineGradient			(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc);
		void				iBmpDrawVerticalLineGradient			(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc);
	
		// For scaling
		u32					iBmpScale								(SBitmap* bmpScaled, SBitmap* bmp);
		u32					iiBmpScale_Process						(SBitmap* bmpDst, SBitmap* bmpSrc, f32 tfVerticalScaler, f32 tfHorizontalScaler);
		void				iiBmpScale_processPixels				(SBitmapProcess* bp);
		void				iiBmpScale_processSpannedPixel1			(SBitmapProcess* bp);
		void				iiBmpScale_processSpannedPixel2			(SBitmapProcess* bp);
		void				iiBmpScale_processSpannedPixel3			(SBitmapProcess* bp);
		void				iiBmpScale_processSpannedPixel4			(SBitmapProcess* bp);
		void				iiBmpScale_processSpannedPixel5			(SBitmapProcess* bp);
		void				iiBmpScale_processSpannedPixel6			(SBitmapProcess* bp);
		void				iiBmpScale_processSpannedPixel7			(SBitmapProcess* bp);
		void				iiBmpScale_processSpannedPixel8			(SBitmapProcess* bp);
		void				iiBmpScale_processSpannedPixel9			(SBitmapProcess* bp);
		u32					iiBmpScale_processGetIntegersBetween	(f32 p1, f32 p2);
	//////
	// End
	//////////

	void					iDrawScreen								(RECT* trc);
	void					iDrawJDebi								(RECT* trc);
	void					iRedrawScreen							(SWindow* win);
	void					iRedrawJDebi							(SWindow* win);


//////////
// vjr_dbf.cpp
//////
	u32						dbf_open								(s8* tcPathname, s8* tcAlias, bool tlExclusive);
	u32						dbf_close								(u32 tnHandle);
	u32						dbf_goto								(u32 tnHandle, u32 tnRecno);
	u32						dbf_read_field							(u32 tnHandle, u32 tnFieldNumber, s8* tcFieldName, s8** txData, u32** txDataLength);
	u32						dbf_write_field							(u32 tnHandle, u32 tnFieldNumber, s8* tcFieldName, s8* txData, u32* txDataLength);
