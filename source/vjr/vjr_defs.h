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
//////
//
// Jun.17.2014
// Note:  The function definitions below use a naming convention to indicate some of
//        their functionality.  All functions prefixed with "i" are internal functions.
//        If you see one with "ii" or "iii" they bypass standard checks (like null pointers)
//        and are only called from the internal functions.  In general, always use the
//        "i" functions if you are unsure if something will be populated or not.  If you
//        have already tested it and know it's populated, then it is safe to call an "ii"
//        function.
//
//////
//
//




//////////
// vjr.cpp
//////
//	int APIENTRY			WinMain									(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, s32 nCmdShow);


//////////
// objects.cpp
//////
	SObject*				iObj_create								(u32 tnBaseType, void* obj_data);
	SObject*				iObj_copy								(SObject* template_obj, SObject* next, SObject* parent, bool tlCopyChildren, bool tlCopySubobjects, bool tlCreateSeparateBitmapBuffers);
	void					iObj_delete								(SObject* obj, bool tlDeleteSelf);
	u32						iObj_render								(SObject* obj, bool tlRenderChildren, bool tlRenderSiblings);
	void					iObj_renderChildrenAndSiblings			(SObject* obj, bool tlRenderChildren, bool tlRenderSiblings);
	u32						iObj_publish							(SBitmap* bmpDst, RECT* trc, SObject* obj, bool tlPublishChildren, bool tlPublishSiblings);
	void					iObj_duplicateChain						(SObject** root, SObject* chain);

	// Creation of individual sub-objects
	void*					iSubobj_copy							(SObject* template_obj);
	SSubObjEmpty*			iSubobj_createEmpty						(SSubObjEmpty*		template_subobj, SObject* parent);
	SSubObjForm*			iSubobj_createForm						(SSubObjForm*		template_subobj, SObject* parent);
	SSubObjSubform*			iSubobj_createSubform					(SSubObjSubform*	template_subobj, SObject* parent);
	SSubObjLabel*			iSubobj_createLabel						(SSubObjLabel*		template_subobj, SObject* parent);
	SSubObjTextbox*			iSubobj_createTextbox					(SSubObjTextbox*	template_subobj, SObject* parent);
	SSubObjButton*			iSubobj_createButton					(SSubObjButton*		template_subobj, SObject* parent);
	SSubObjEditbox*			iSubobj_createEditbox					(SSubObjEditbox*	template_subobj, SObject* parent);
	SSubObjImage*			iSubobj_createImage						(SSubObjImage*		template_subobj, SObject* parent);
	SSubObjCheckbox*		iSubobj_createCheckbox					(SSubObjCheckbox*	template_subobj, SObject* parent);
	SSubObjOption*			iSubobj_createOption					(SSubObjOption*		template_subobj, SObject* parent);
	SSubObjRadio*			iSubobj_createRadio						(SSubObjRadio*		template_subobj, SObject* parent);

	// Delete individual sub-objects
	void					iSubobj_deleteEmpty						(SSubObjEmpty*		subobj, bool tlFreeSelf);
	void					iSubobj_deleteForm						(SSubObjForm*		subobj, bool tlFreeSelf);
	void					iSubobj_deleteSubform					(SSubObjSubform*	subobj, bool tlFreeSelf);
	void					iSubobj_deleteLabel						(SSubObjLabel*		subobj, bool tlFreeSelf);
	void					iSubobj_deleteTextbox					(SSubObjTextbox*	subobj, bool tlFreeSelf);
	void					iSubobj_deleteButton					(SSubObjButton*		subobj, bool tlFreeSelf);
	void					iSubobj_deleteEditbox					(SSubObjEditbox*	subobj, bool tlFreeSelf);
	void					iSubobj_deleteImage						(SSubObjImage*		subobj, bool tlFreeSelf);
	void					iSubobj_deleteCheckbox					(SSubObjCheckbox*	subobj, bool tlFreeSelf);
	void					iSubobj_deleteOption					(SSubObjOption*		subobj, bool tlFreeSelf);
	void					iSubobj_deleteRadio						(SSubObjRadio*		subobj, bool tlFreeSelf);

	// Default render of sub-objects
	u32						iSubobj_renderEmpty						(SObject* obj,		SSubObjEmpty*		subobj,		bool tlRenderChildren,	bool tlRenderSiblings);
	u32						iSubobj_renderForm						(SObject* obj,		SSubObjForm*		subobj,		bool tlRenderChildren,	bool tlRenderSiblings);
	u32						iSubobj_renderSubform					(SObject* obj,		SSubObjSubform*		subobj,		bool tlRenderChildren,	bool tlRenderSiblings);
	u32						iSubobj_renderLabel						(SObject* obj,		SSubObjLabel*		subobj,		bool tlRenderChildren,	bool tlRenderSiblings);
	u32						iSubobj_renderTextbox					(SObject* obj,		SSubObjTextbox*		subobj,		bool tlRenderChildren,	bool tlRenderSiblings);
	u32						iSubobj_renderButton					(SObject* obj,		SSubObjButton*		subobj,		bool tlRenderChildren,	bool tlRenderSiblings);
	u32						iSubobj_renderEditbox					(SObject* obj,		SSubObjEditbox*		subobj,		bool tlRenderChildren,	bool tlRenderSiblings);
	u32						iSubobj_renderImage						(SObject* obj,		SSubObjImage*		subobj,		bool tlRenderChildren,	bool tlRenderSiblings);
	u32						iSubobj_renderCheckbox					(SObject* obj,		SSubObjCheckbox*	subobj,		bool tlRenderChildren,	bool tlRenderSiblings);
	u32						iSubobj_renderOption					(SObject* obj,		SSubObjOption*		subobj,		bool tlRenderChildren,	bool tlRenderSiblings);
	u32						iSubobj_renderRadio						(SObject* obj,		SSubObjRadio*		subobj,		bool tlRenderChildren,	bool tlRenderSiblings);


//////////
// callbacks.cpp
//////
	bool					iDefaultCallback_load					(SObject* o);
	void					iDefaultCallback_init					(SObject* o);
	void					iDefaultCallback_created				(SObject* o);
	void					iDefaultCallback_resize					(SObject* o, u32* widthRequired_out, u32* heightRequired_out);
	bool					iDefaultCallback_render					(SObject* o);
	bool					iDefaultCallback_publish				(SObject* o);
	void					iDefaultCallback_destroy				(SObject* o);
	void					iDefaultCallback_unload					(SObject* o);
	bool					iDefaultCallback_gotFocus				(SObject* o);
	bool					iDefaultCallback_lostFocus				(SObject* o);
	bool					iDefaultCallback_clickex				(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);
	bool					iDefaultCallback_wheel					(SObject* o, s32 tnUnits);
	bool					iDefaultCallback_move					(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);
	bool					iDefaultCallback_down					(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick, u32 tnLastClick);
	bool					iDefaultCallback_up						(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick, u32 tnLastClick);
	bool					iDefaultCallback_enter					(SObject* o);
	bool					iDefaultCallback_leave					(SObject* o);
	bool					iDefaultCallback_hover					(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);
	bool					iDefaultCallback_keyDown				(SObject* o, bool tlCtrl, bool tlAlt, bool tlShift, s16 tcAscii, u16 tnVKey, bool tlIsCAS, bool tlIsAscii);
	bool					iDefaultCallback_keyUp					(SObject* o, bool tlCtrl, bool tlAlt, bool tlShift, s16 tcAscii, u16 tnVKey, bool tlIsCAS, bool tlIsAscii);
	bool					iDefaultCallback_activate				(SObject* o);
	bool					iDefaultCallback_deactivate				(SObject* o);
	bool					iDefaultCallback_interactiveChange		(SObject* o);
	bool					iDefaultCallback_programmaticChange		(SObject* o);
	bool					iDefaultCallback_onSelect				(SObject* o, SObject* oItem);
	bool					iDefaultCallback_onDeselect				(SObject* o, SObject* oItem);



//////////
// vjr_sup.cpp
//////
	void					initialize								(HACCEL* hAccelTable);
	void					iInit_createMessageWindow				(void);
	bool					isValidWindow							(u32 tnWindow);
	void					iInit_createDefaultObjects				(void);
	SObject*				iInit_createScreenForm					(void);
	SObject*				iInit_createJDebiForm					(void);

	DWORD	WINAPI			iReadEvents_messageWindow				(LPVOID lpParameter);
	LRESULT	CALLBACK		iWndProc_messageWindow					(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	LRESULT	CALLBACK		iWndProc_screenWindow					(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	bool					iShutdownPolitely						(void);

	void					iResizeScreenWindow						(bool tlForce);
	void					iResizeJDebiWindow						(bool tlForce);
	void					iSetScreenWindowSize					(s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight, bool tlForce);
	void					iSetJDebiWindowSize						(s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight, bool tlForce);
	void					iComputeScreenWindowClientAreaDimensions	(SSize* size);
	void					iComputeScreenWindowNonclientAreaDimensions	(SSize* size);
	void					iAdjustScreenWindowDimensions				(SSize* size);
	void					iComputeJDebiWindowClientAreaDimensions		(SSize* size);
	void					iComputeJDebiWindowNonclientAreaDimensions	(SSize* size);
	void					iAdjustJDebiWindowDimensions				(SSize* size);

	s64						iTime_computeMilliseconds				(SYSTEMTIME* time);
	s64						iTime_getSystemMs						(void);
	s64						iTime_getLocalMs						(void);
	s64						iMath_delta								(s64 tnBaseValue, s64 tnSubtractionValue);
	s8*						iDuplicateString						(s8* tcText);
	SFont*					iFont_allocate							(void);
	SFont*					iFont_duplicate							(SFont* fontSource);
	SFont*					iFont_create							(cs8* tcFontName, u32 tnFontSize, u32 tnFontWeight, u32 tnItalics, u32 tnUnderline);
	void					iFont_free								(SFont* font, bool tlFreeSelf);
	u32						iFont_findClosestSizeMatch				(s8* tcText, s8* tcFontName, u32 tnFontSize, u32 tnFontBold, u32 tnFontItalic, u32 tnFontUnderline, u32 tnWidth, u32 tnHeight, u32 tnWidthDesired, u32 tnHeightDesired);
	int						iProcessMouseMessage					(UINT m, WPARAM w, LPARAM l);
	void					iTranslateMousePosition					(POINTS* pt);

	// EditChainManager
	bool					iEditChainManager_duplicate				(SEditChainManager** root, SEditChainManager* chain, bool tlIncludeUndoHistory);
	void					iEditChainManager_free					(SEditChainManager** root, bool tlFreeSelf);

	// Edit Chain
	void					iEditChain_free							(SEditChain** root, bool tlFreeSelf);

	// Translate
	void*					iTranslate_p1_to_p2						(SBuilder* root, void* ptr);
	void*					iTranslate_p2_to_p1						(SBuilder* root, void* ptr);

	// ExtraInfo
	void					iExtraInfo_free							(SEditChainManager* ecm, SEditChain* ec, SExtraInfo** root, bool tlFreeSelf);

	// Datum
	SDatum*					iDatum_allocate							(               s8* data, u32 dataLength);
	void					iDatum_duplicate						(SDatum* datum, s8* data, u32 dataLength);
	void					iDatum_duplicate						(SDatum* datumDst, SDatum* datumSrc);
	s32						iDatum_compare							(SDatum* datumLeft, SDatum* datumRight);
	void					iDatum_free								(SDatum* datum, bool tlFreeSelf);
	void					iiDatum_free							(SDatum* datum);


//////////
// bitmaps.cpp
//////
	SBitmap*				iBmp_allocate							(void);
	SBitmap*				iBmp_copy								(SBitmap* bmpSrc);
	SBitmap*				iBmp_verifyCopyIsSameSize				(SBitmap* bmpCopy, SBitmap* bmp);
	SBitmap*				iBmp_rawLoad							(cu8* bmpRawFileData);
	void					iBmp_convertTo32Bits					(SBitmap* bmp);
	void					iBmp_copy24To32							(SBitmap* bmp32, SBitmap* bmp24);
	bool					iBmp_validate							(SBitmap* bmp);
	s32						iBmp_computeRowWidth					(SBitmap* bmp);
	void					iBmp_createBySize						(SBitmap* bmp, u32 width, u32 height, u32 tnBitCount);
	void					iBmp_populateBitmapStructure			(SBitmap* bmp, u32 tnWidth, u32 tnHeight, u32 tnBitCount);
	void					iBmp_delete								(SBitmap* bmp, bool tlFreeBits, bool tlFreeSelf);
	void					iBmp_bitBltObject						(SBitmap* bmpDst, SObject* obj, SBitmap* bmpSrc);
	void					iBmp_bitBltObjectMask					(SBitmap* bmpDst, SObject* obj, SBitmap* bmpSrc);
	u32						iBmp_bitBlt								(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc);
// TODO:  The following void functions need to be changed to u32 and indicate how many pixels were rendered
	void					iBmp_bitBltMask							(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc);
	void					iBmp_drawPoint							(SBitmap* bmp, s32 tnX, s32 tnY, SBgra color);
	void					iBmp_fillRect							(SBitmap* bmp, RECT* rc, SBgra colorNW, SBgra colorNE, SBgra colorSW, SBgra colorSE, bool tlUseGradient);
	void					iBmp_frameRect							(SBitmap* bmp, RECT* rc, SBgra colorNW, SBgra colorNE, SBgra colorSW, SBgra colorSE, bool tlUseGradient);
	void					iBmp_drawHorizontalLine					(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, SBgra color);
	void					iBmp_drawVerticalLine					(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, SBgra color);
	void					iBmp_drawHorizontalLineGradient			(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc);
	void					iBmp_drawVerticalLineGradient			(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc);

	//////////
	// For scaling
	//////
		u32					iBmp_scale								(SBitmap* bmpScaled, SBitmap* bmp);
		u32					iiBmp_scale_Process						(SBitmap* bmpDst, SBitmap* bmpSrc, f32 tfVerticalScaler, f32 tfHorizontalScaler);
		void				iiBmp_scale_processPixels				(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel1		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel2		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel3		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel4		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel5		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel6		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel7		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel8		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel9		(SBitmapProcess* bp);
		u32					iiBmp_scale_processGetIntegersBetween	(f32 p1, f32 p2);
	//////
	// End
	//////////


//////////
// vjr_dbf.cpp
//////
	u32						dbf_open								(s8* tcPathname, s8* tcAlias, bool tlExclusive);
	u32						dbf_close								(u32 tnHandle);
	u32						dbf_goto								(u32 tnHandle, u32 tnRecno);
	u32						dbf_read_field							(u32 tnHandle, u32 tnFieldNumber, s8* tcFieldName, s8** txData, u32** txDataLength);
	u32						dbf_write_field							(u32 tnHandle, u32 tnFieldNumber, s8* tcFieldName, s8* txData, u32* txDataLength);
