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
	void					iObj_delete								(SObject** obj, bool tlDeleteSelf);
	u32						iObj_render								(SObject* obj, bool tlRenderChildren, bool tlRenderSiblings);
	void					iObj_renderChildrenAndSiblings			(SObject* obj, bool tlRenderChildren, bool tlRenderSiblings);
	u32						iObj_publish							(SBitmap* bmpDst, RECT* trc, SObject* obj, bool tlPublishChildren, bool tlPublishSiblings);
	void					iObj_duplicateChain						(SObject** root, SObject* chain);
	void					iObj_appendObjToParent					(SObject* parent, SObject* obj);
	void					iObj_duplicateChildren					(SObject* parent);
	void					iObj_setSize							(SObject* obj, s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight);
	SWindow* 				iObj_createWindowForForm				(SObject* obj_form);
	bool					iObj_setVisible							(SObject* obj, bool tlNewVisible);
	void*					iObj_copySubobj							(SObject* template_obj);
	void					iiObj_resetToDefault					(SObject* obj, bool tlResetProperties, bool tlResetMethods);
	void					iiObj_resetToDefaultCommon				(SObject* obj, bool tlResetProperties, bool tlResetMethods);

	// Creation of individual sub-objects
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

	// For initialization
	void					iiSubobj_resetToDefaultEmpty			(SSubObjEmpty*		subobj, bool tlResetObject, bool tlResetProperties, bool tlResetMethods);
	void					iiSubobj_resetToDefaultForm				(SSubObjForm*		subobj, bool tlResetObject, bool tlResetProperties, bool tlResetMethods);
	void					iiSubobj_resetToDefaultSubform			(SSubObjSubform*	subobj, bool tlResetObject, bool tlResetProperties, bool tlResetMethods);
	void					iiSubobj_resetToDefaultLabel			(SSubObjLabel*		subobj, bool tlResetObject, bool tlResetProperties, bool tlResetMethods);
	void					iiSubobj_resetToDefaultTextbox			(SSubObjTextbox*	subobj, bool tlResetObject, bool tlResetProperties, bool tlResetMethods);
	void					iiSubobj_resetToDefaultButton			(SSubObjButton*		subobj, bool tlResetObject, bool tlResetProperties, bool tlResetMethods);
	void					iiSubobj_resetToDefaultEditbox			(SSubObjEditbox*	subobj, bool tlResetObject, bool tlResetProperties, bool tlResetMethods);
	void					iiSubobj_resetToDefaultImage			(SSubObjImage*		subobj, bool tlResetObject, bool tlResetProperties, bool tlResetMethods);
	void					iiSubobj_resetToDefaultCheckbox			(SSubObjCheckbox*	subobj, bool tlResetObject, bool tlResetProperties, bool tlResetMethods);
	void					iiSubobj_resetToDefaultOption			(SSubObjOption*		subobj, bool tlResetObject, bool tlResetProperties, bool tlResetMethods);
	void					iiSubobj_resetToDefaultRadio			(SSubObjRadio*		subobj, bool tlResetObject, bool tlResetProperties, bool tlResetMethods);


	// For specific sub-objects
	void					iSubobj_form_setIcon					(SObject* obj, SBitmap* bmp);
	void					iSubobj_form_setCaption					(SObject* obj, s8* tcCaption, u32 tnCaptionLength);
	void					iSubobj_form_setBorderRgba				(SObject* obj, u32 tnNwRgba, u32 tnNeRgba, u32 tnSwRgba, u32 tnSeRgba);
	u32						iSubobj_form_setBackColor				(SObject* obj, u32 tnRgba);
	u32						iSubobj_form_setForeColor				(SObject* obj, u32 tnRgba);
	u32						iSubobj_form_setCaptionColor			(SObject* obj, u32 tnRgba);

	// Delete individual sub-objects
	void					iSubobj_deleteEmpty						(SSubObjEmpty*		subobj, bool tlDeleteSelf);
	void					iSubobj_deleteForm						(SSubObjForm*		subobj, bool tlDeleteSelf);
	void					iSubobj_deleteSubform					(SSubObjSubform*	subobj, bool tlDeleteSelf);
	void					iSubobj_deleteLabel						(SSubObjLabel*		subobj, bool tlDeleteSelf);
	void					iSubobj_deleteTextbox					(SSubObjTextbox*	subobj, bool tlDeleteSelf);
	void					iSubobj_deleteButton					(SSubObjButton*		subobj, bool tlDeleteSelf);
	void					iSubobj_deleteEditbox					(SSubObjEditbox*	subobj, bool tlDeleteSelf);
	void					iSubobj_deleteImage						(SSubObjImage*		subobj, bool tlDeleteSelf);
	void					iSubobj_deleteCheckbox					(SSubObjCheckbox*	subobj, bool tlDeleteSelf);
	void					iSubobj_deleteOption					(SSubObjOption*		subobj, bool tlDeleteSelf);
	void					iSubobj_deleteRadio						(SSubObjRadio*		subobj, bool tlDeleteSelf);

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
	bool					iDefaultCallback_onLoad					(SObject* o);
	bool					iDefaultCallback_onInit					(SObject* o);
	bool					iDefaultCallback_onCreated				(SObject* o);
	bool					iDefaultCallback_onResize				(SObject* o, u32* widthRequired_out, u32* heightRequired_out);
	bool					iDefaultCallback_onRender				(SObject* o);
	bool					iDefaultCallback_onPublish				(SObject* o);
	bool					iDefaultCallback_onDestroy				(SObject* o);
	bool					iDefaultCallback_onUnload				(SObject* o);
	bool					iDefaultCallback_onGotFocus				(SObject* o);
	bool					iDefaultCallback_onLostFocus			(SObject* o);
	bool					iDefaultCallback_onMouseClickEx			(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);
	bool					iDefaultCallback_onMouseWheel			(SObject* o, s32 tnUnits);
	bool					iDefaultCallback_onMouseMove			(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);
	bool					iDefaultCallback_onMouseDown			(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick, u32 tnLastClick);
	bool					iDefaultCallback_onMouseUp				(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick, u32 tnLastClick);
	bool					iDefaultCallback_onMouseEnter			(SObject* o);
	bool					iDefaultCallback_onMouseLeave			(SObject* o);
	bool					iDefaultCallback_onMouseHover			(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);
	bool					iDefaultCallback_onKeyDown				(SObject* o, bool tlCtrl, bool tlAlt, bool tlShift, s16 tcAscii, u16 tnVKey, bool tlIsCAS, bool tlIsAscii);
	bool					iDefaultCallback_onKeyUp				(SObject* o, bool tlCtrl, bool tlAlt, bool tlShift, s16 tcAscii, u16 tnVKey, bool tlIsCAS, bool tlIsAscii);
	bool					iDefaultCallback_onActivate				(SObject* o);
	bool					iDefaultCallback_onDeactivate			(SObject* o);
	bool					iDefaultCallback_onInteractiveChange	(SObject* o);
	bool					iDefaultCallback_onProgrammaticChange	(SObject* o);
	bool					iDefaultCallback_onSelect				(SObject* o, SObject* oItem);
	bool					iDefaultCallback_onDeselect				(SObject* o, SObject* oItem);
	bool					iDefaultCallback_onMoved				(SObject* o, u32* xOverride_out, u32* yOverride_out);
	bool					iDefaultCallback_onQueryUnload			(SObject* o);
	bool					iDefaultCallback_onAddObject			(SObject* o);
	bool					iDefaultCallback_onAddProperty			(SObject* o);
	bool					iDefaultCallback_onError				(SObject* o);
	bool					iDefaultCallback_onScrolled				(SObject* o);


//////////
// events.cpp
//////
	void					iEvents_resetToDefault					(SEvents* ev);



//////////
// vjr_sup.cpp
//////
	void					iInit_vjr								(HACCEL* hAccelTable);
	void					iInit_createMessageWindow				(void);
	bool					isValidWindow							(u32 tnWindow);
	void					iInit_createDefaultObjects				(void);
	void					iInit_create_screenObject				(void);
	void					iInit_create_jdebiObject				(void);

	DWORD	WINAPI			iReadEvents_messageWindow				(LPVOID lpParameter);
	LRESULT	CALLBACK		iMessage_wndProcWindow					(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	LRESULT	CALLBACK		iWindow_wndProc							(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	SWindow* 				iWindow_createForObject					(SObject* obj);
	SWindow*				iWindow_findByHwnd						(HWND hwnd);
	SWindow*				iWindow_allocate						(void);
	bool					iInit_shutdownPolitely					(void);

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
	void					iFont_delete							(SFont** font, bool tlDeleteSelf);
	u32						iFont_findClosestSizeMatch				(s8* tcText, s8* tcFontName, u32 tnFontSize, u32 tnFontBold, u32 tnFontItalic, u32 tnFontUnderline, u32 tnWidth, u32 tnHeight, u32 tnWidthDesired, u32 tnHeightDesired);
	int						iProcessMouseMessage					(UINT m, WPARAM w, LPARAM l);
	void					iTranslateMousePosition					(POINTS* pt);

	// EditChainManager
	bool					iEditChainManager_duplicate				(SEditChainManager** root, SEditChainManager* chain, bool tlIncludeUndoHistory);
	void					iEditChainManager_delete				(SEditChainManager** root, bool tlDeleteSelf);
	void					iEditChainManager_deleteChain			(SEditChainManager** root, bool tlDeleteSelf);

	// Edit Chain
	void					iEditChain_free							(SEditChain** root, bool tlDeleteSelf);

	// Translate
	void*					iTranslate_p1_to_p2						(SBuilder* root, void* ptr);
	void*					iTranslate_p2_to_p1						(SBuilder* root, void* ptr);

	// ExtraInfo
	void					iExtraInfo_free							(SEditChainManager* ecm, SEditChain* ec, SExtraInfo** root, bool tlDeleteSelf);

	// Datum
	SDatum*					iDatum_allocate							(               s8* data, u32 dataLength);
	void					iDatum_duplicate						(SDatum* datum, s8* data, u32 dataLength);
	void					iDatum_duplicate						(SDatum* datumDst, SDatum* datumSrc);
	s32						iDatum_compare							(SDatum* datumLeft, SDatum* datumRight);
	void					iDatum_delete							(SDatum* datum, bool tlDeleteSelf);
	void					iiDatum_delete							(SDatum* datum);


//////////
// bitmaps.cpp
//////
	SBitmap*				iBmp_allocate							(void);
	SBitmap*				iBmp_copy								(SBitmap* bmpSrc);
	SBitmap*				iBmp_verifyCopyIsSameSize				(SBitmap* bmpCopy, SBitmap* bmp);
	SBitmap*				iBmp_verifySizeOrResize					(SBitmap* bmp, u32 tnWidth, u32 tnHeight);
	SBitmap*				iBmp_rawLoad							(cu8* bmpRawFileData);
	void					iBmp_convertTo32Bits					(SBitmap* bmp);
	void					iBmp_copy24To32							(SBitmap* bmp32, SBitmap* bmp24);
	bool					iBmp_validate							(SBitmap* bmp);
	s32						iBmp_computeRowWidth					(SBitmap* bmp);
	void					iBmp_createBySize						(SBitmap* bmp, u32 width, u32 height, u32 tnBitCount);
	void					iBmp_populateBitmapStructure			(SBitmap* bmp, u32 tnWidth, u32 tnHeight, u32 tnBitCount);
	void					iBmp_delete								(SBitmap** bmp, bool tlFreeBits, bool tlDeleteSelf);
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
