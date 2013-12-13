**********
*
* /libsf/vvm/utils/dsf/progs/dsf_dll.prg
*
*****
* Version 0.60
* Copyright (c) 2013 by Rick C. Hodgin
*****
* Last update:
*     Nov.26.2013
*****
* Change log:
*     Nov.26.2013	- Initial creation
*****
*
* This function should be in sync with the dsf_*() functions defined in:
*		/libsf/vvm/utils/dsf/msvc++/dsf/dsf.cpp
*
*****
*
* This software is released as Liberty Software under a Repeat License, as governed
* by the Public Benefit License v1.0 or later (PBL).
*
* You are free to use, copy, modify and share this software.  However, it can only
* be released under the PBL version indicated, and every project must include a copy
* of the pbl.txt document for its version as is at http:*www.libsf.org/licenses/.
*
* For additional information about this project, or to view the license, see:
*
*     http:*www.libsf.org/
*     http:*www.libsf.org/licenses/
*     http:*www.visual-freepro.org
*     http:*www.visual-freepro.org/blog/
*     http:*www.visual-freepro.org/forum/
*     http:*www.visual-freepro.org/wiki/
*     http:*www.visual-freepro.org/wiki/index.php/PBL
*     http:*www.visual-freepro.org/wiki/index.php/Repeat_License
*
* Thank you.  And may The Lord bless you richly as you lift up your life, your
* talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
*
*****




FUNCTION declare_dsf_dll

	* Obtains the bitmap for the indicated character
	DECLARE INTEGER		dsf_get_character_bitmap	IN exe\dsf.dll ;
							INTEGER		tnAsciiCharacter, ;		&& CHR(tnAsciiCharacter) to get
							STRING		tcBitmapFilename, ;		&& Name of the bitmap file to write to (NULL if you don't want to keep the character bitmap)
							STRING		tcFloanFilename, ;		&& Grab the floan data representing the full outline of the character
							STRING		tcFontName, ;			&& "Arial", "Ubuntu", etc.
							INTEGER		tnBitmapHeight, ;		&& Typically 400
							INTEGER		tnBitmapWidth			&& Typically 400

	* Scales the bitmap to a new size for adjusted viewing
	DECLARE INTEGER		dsf_scale_and_clip_bitmap	IN exe\dsf.dll ;
							STRING		tcBitmapFilenameIn, ;	&& Input bitmap of image already drawn
							STRING		tcBitmapFilenameOut, ;	&& Output bitmap of image scaled
							SINGLE		tfWidthAdjust, ;		&& 1.0 leaves it the same horizontally
							SINGLE		tfHeightAdjust, ;		&& 1.0 leaves it the same vertically
							INTEGER		tnClipLeft, ;			&& In pixels, how many to clip/crop at the left after scaling
							INTEGER		tnClipTop, ;			&& In pixels, how many to clip/crop at the top after scaling
							INTEGER		tnNewWidth, ;			&& New width after scaling, typically 400
							INTEGER		tnNewHeight				&& New height after scaling, typically 400

	* Creates a new instance connection to the DLL for a separate frmEdit window
	* Returns a handle to the new instance to use for all functions below
	DECLARE INTEGER		dsf_create_new_instance		IN exe\dsf.dll
	
	* Closes an intance once it is done being edited
	* Returns 0=ok, others error code
	DECLARE INTEGER		dsf_close_instance		IN exe\dsf.dll ;
							INTEGER		tnInstance				&& Instance handle returned by dsf_create_new_instance()
	
	* Sets the font data
	* Returns 0=ok, others error code
	DECLARE INTEGER		dsf_load_font		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							SINGLE		tfAscent, ;				&& See explanation of these in frmNew::create_tables()
							SINGLE		tfUpper, ;				&& These must be in synchronization with those fields,
							SINGLE		tfLower, ;				&& as well as the function in the DSF.DLL.
							SINGLE		tfLeft, ;
							SINGLE		tfRight, ;
							SINGLE		tfBase, ;
							SINGLE		tfDescent, ;
							SINGLE		tfWidth, ;
							SINGLE		tfItalics, ;
							SINGLE		tfBold, ;
							SINGLE		tfUnderTop, ;
							SINGLE		tfUnderBot, ;
							SINGLE		tfStrikeTop, ;
							SINGLE		tfStrikeBot

	* Called to load part of a character definition
	DECLARE INTEGER		dsf_load_character		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		tnType, ;				&& See explanation of these in frmNew::create_tables()
							INTEGER		tiid, ;					&& These must be in synchronization with those fields,
							INTEGER		tiOrder, ;				&& as well as the function in the DSF.DLL.
							STRING		tcDesc10, ;
							INTEGER		tlNewStroke, ;
							INTEGER		tlSelected, ;
							SINGLE		tfOx, ;
							SINGLE		tfOy, ;
							SINGLE		tfOt, ;
							SINGLE		tfLr, ;
							SINGLE		tfLt, ;
							SINGLE		tfRr, ;
							SINGLE		tfRt, ;
							INTEGER		tiSubdivs, ;
							INTEGER		tiLnkId, ;
							INTEGER		tiLnkOrder

	* Called to load reference line data
	DECLARE INTEGER		dsf_load_reference		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		tnType, ;				&& See explanation of these in frmNew::create_tables()
							STRING		tcDesc40, ;				&& These must be in synchronization with those fields,
							SINGLE		tfRef1X, ;				&& as well as the function in the DSF.DLL.
							SINGLE		tfRef1Y, ;
							SINGLE		tfRef2X, ;
							SINGLE		tfRef2Y, ;
							SINGLE		tfRef3X, ;
							SINGLE		tfRef3Y, ;
							SINGLE		tfRef4X, ;
							SINGLE		tfRef4Y, ;
							SINGLE		tfRef5X, ;
							SINGLE		tfRef5Y, ;
							INTEGER		tlVisible, ;
							STRING		tcChars1_128, ;
							STRING		tcChars2_128

	* Called to load template point data
	DECLARE INTEGER		dsf_load_template		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		tipid, ;				&& iid of the character this template relates to (parent id)
							SINGLE		tfX, ;					&& X coordinate of this template
							SINGLE		tfY, ;					&& Y coordinate of this template
							INTEGER		tnRecno					&& The original record number used to reference this item
	
	* Called when all data has been loaded.  Used to allow the DLL to build any
	* speedups or shortcuts it needs for more rapid GUI processing.
	DECLARE INTEGER		dsf_initial_load_complete		IN exe\dsf.dll ;
							INTEGER		tnInstance, ;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		tnWidth, ;				&& Width of the primary edit window
							INTEGER		tnHeight				&& Height of the primary edit window
	
	* Called during the save operations to save any changed template data (template data is maintained by the DLL due to its high number of items)
	* Returns 0 if valid, -2 if the indicated tipid is invalid, -3 if there are no more new items for a valid tipid
	DECLARE INTEGER		dsf_get_changed_template		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		tipid, ;				&& iid of the character this template relates to (parent id)
							STRING		@tcX12, ;				&& SPACE(12) area for the X coordinate in #.###### form
							STRING		@tcY12, ;				&& SPACE(12) area for the Y coordinate in #.###### form
							STRING		@tcRecno12,	;			&& The record number used to reference this item. If it's set to tnNextNewRecno, then it is a newly added record which has now acquired this recno()
							INTEGER		tnNextNewRecno			&& If we need to add a new record, this will be its recno().
	
	* Called during the save operations to delete any template data the user has deleted
	* Returns 0 if valid, -2 if the indicated tipid is invalid, -3 if there are no more deleted items for a valid tipid
	DECLARE INTEGER		dsf_get_deleted_template		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		tipid, ;				&& iid of the character this template relates to (parent id)
							STRING		@tcRecno12				&& The record number used to reference this item.

	* User cues are visible on the display if set to 1, 0 if hidden.
	* Note:  Setting the cues does not trigger a refresh.  Only dsf_user_settings() triggers a refresh.
	* Note:  This allows the cues to be setup in stages, followed by the settings, to only have one refresh, rather than several.
	DECLARE INTEGER		dsf_user_cues		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		ascent, ;				&& The ascent (highest point of the font, top of umlaut above a capital letter, for example
							INTEGER		trackAscent, ;			&& Should the mouse track near to ascent strokes?
							INTEGER		upper, ;				&& The upper (highest point of an upper-case letter, or number)
							INTEGER		trackUpper, ;			&& Should the mouse track near to the upper-line?
							INTEGER		lower, ;				&& The lower (highest point of a lower-case letter)
							INTEGER		trackLower, ;			&& Should the mouse track near to the lower-line?
							INTEGER		base, ;					&& The base (base of all characters, numbers, everything drawn)
							INTEGER		trackBase, ;			&& Should the mouse track near to the lower-line?
							INTEGER		descent, ;				&& The descent (lowest point of a letter, bottom of a y or g, for example)
							INTEGER		trackDescent, ;			&& Should the mouse track near to the descent-line?
							INTEGER		strikethrough, ;		&& Strikethrough lines (upper and lower, as per the line thickness)
							INTEGER		trackStrike, ;			&& Should the mouse track near to the strikethrough lines?
							INTEGER		underline, ;			&& Underscore lines (upper and lower, as per the line thickness)
							INTEGER		trackUnderline, ;		&& Should the mouse track near to the underline lines?
							INTEGER		refs, ;					&& Custom references
							INTEGER		trackRefs				&& Should the mouse track near to the custom references?

	* A continuation for additional settings
	DECLARE INTEGER		dsf_user_cues2		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		left, ;					&& Should the left items be displayed?
							INTEGER		trackLeft, ;			&& Should the mouse track near to the left items?
							INTEGER		right, ;				&& Should the right items be displayed?
							INTEGER		trackRight, ;			&& Should the mouse track near to the right items?
							INTEGER		width, ;				&& Should the width be displayed?
							INTEGER		trackWidth, ;			&& Should the mouse track near to the width items?
							INTEGER		tems, ;					&& Should the tems be displayed?
							INTEGER		trackTems, ;			&& Should the mouse track near to the tems items?
							INTEGER		grid, ;					&& Should the grid be displayed?
							INTEGER		trackGrid				&& Should the mouse track near tot he grid lines?
	
	* Called to set the user settings
	DECLARE INTEGER		dsf_user_settings		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		tnDisposition, ;		&& 0=select, 1=unselect, 2=toggle, 3=flip left to right, right to left, 4=flip left/middle to right/middle, and right/middle to left/middle
							INTEGER		tnMode, ;				&& 0=point, 1=spline, 2=stroke, 3=before and current, 4=current and after
							INTEGER		tnMethod, ;				&& 0=left, 1=middle, 2=right, 3=left+middle, 4=middle+right, 5=left+right, 6=spline, 7=point
							INTEGER		tnRange, ;				&& 0=active character, 1=AZ, 2=az, 3=AZaz, 4=09, 5=AZaz09, 6=AZaz09!@.., 7=all
							INTEGER		tlShowSplines, ;		&& 0=no, 1=yes
							INTEGER		tnSplinesType, ;		&& 0=Fill, 1=Outline, 2=LOR only
							INTEGER		tlHighlighSelection, ;	&& 0=no, 1=yes, should the selection be highlighted on renderings?
							INTEGER		tlShowPenDowns, ;		&& 0=no, 1=yes, should the pen/brush strokes be highlighted?
							INTEGER		tlShowCrosshairX, ;		&& 0=no, 1=yes, should mouse X-axis crosshair be shown?
							INTEGER		tlShowCrosshairY, ;		&& 0=no, 1=yes, should mouse Y-axis crosshair be shown?
							INTEGER		tlInvert, ;				&& 0=no, 1=yes, should the display be inverted (negative image)
							INTEGER		tlZoomLens, ;			&& 0=no, 1=yes, should a zoom lense be displayed
							INTEGER		tlCuesUnder, ;			&& 0=on top, 1=under, should cues be rendered above or below the splines?
							INTEGER		tnSelectArea			&& Number of pixels (10..30) for the mouse select area
	
	* Called to indicate what character is being referenced
	DECLARE INTEGER		dsf_set_active_character		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		tiId, ;					&& Character or definition component to render

	* Called to render a markup version (for editing)
	DECLARE INTEGER		dsf_render_markup		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		tnWidth, ;				&& Width to render
							INTEGER		tnHeight, ;				&& Height to render
							INTEGER		tlBold, ;				&& Should it be rendered in bold?
							INTEGER		tlItalic, ;				&& Should it be rendered in italic?
							INTEGER		tlUnderline, ;			&& Should it be rendered with underline?
							INTEGER		tlStrikethrough, ;		&& Should it be rendered with strikethrough?
							STRING		tcBitmapPathname, ;		&& Either the pathname, or NULL if not file should be generated
							INTEGER		tnHwnd, ;				&& Either NULL or the form's HWND if you want it drawn directly to the form
							INTEGER		tnX, ;					&& If tnHwnd is not NULL, then the X coordinate of the client area to render at
							INTEGER		tnY						&& If tnHwnd is not NULL, then the Y coordinate of the client area to render at

	* Called to render a final version (as would be used for rendering fonts)
	DECLARE INTEGER		dsf_render_final		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		tnWidth, ;				&& Width to render
							INTEGER		tnHeight, ;				&& Height to render
							INTEGER		tlBold, ;				&& Should it be rendered in bold?
							INTEGER		tlItalic, ;				&& Should it be rendered in italic?
							INTEGER		tlUnderline, ;			&& Should it be rendered with underline?
							INTEGER		tlStrikethrough, ;		&& Should it be rendered with strikethrough?
							STRING		tcBitmapPathname, ;		&& Either the pathname, or NULL if not file should be generated
							INTEGER		tnHwnd, ;				&& Either NULL or the form's HWND if you want it drawn directly to the form
							INTEGER		tnX, ;					&& If tnHwnd is not NULL, then the X coordinate of the client area to render at
							INTEGER		tnY						&& If tnHwnd is not NULL, then the Y coordinate of the client area to render at

	* Called to re-render a previously rendered window.  This is typically done as mouse movement occurs, etc.
	DECLARE INTEGER		dsf_re_render		IN exe\dsf.dll ;
							INTEGER		tnInstance,	;			&& Instance handle returned by dsf_create_new_instance()
							INTEGER		tnWindow				&& The return value given by the last call to dsf_render_markup() or dsf_render_final()
