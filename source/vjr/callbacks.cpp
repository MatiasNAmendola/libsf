//////////
//
// /libsf/source/vjr/callbacks.cpp
//
//////
// Version 0.30
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jun.15.2014
//////
// Change log:
//     Jun.15.2014 - Initial creation
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
// Default callbacks
//
//////
	bool iDefaultCallback_onLoad(SObject* o)
	{
		// Assume it's okay to load
		return(true);
	}

	bool iDefaultCallback_onInit(SObject* o)
	{
		// Assume we consumed the gotFocus, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onCreated(SObject* o)
	{
		// Assume we consumed the gotFocus, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onResize(SObject* o, u32* widthRequired_out, u32* heightRequired_out)
	{
		// Assume we consumed the gotFocus, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onRender(SObject* o)
	{
		// Assume it was rendered okay
		return(true);
	}

	bool iDefaultCallback_onPublish(SObject* o)
	{
		// Assume it was published okay
		return(true);
	}

	bool iDefaultCallback_onDestroy(SObject* o)
	{
		// Assume we consumed the gotFocus, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onUnload(SObject* o)
	{
		// Assume we consumed the gotFocus, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onGotFocus(SObject* o)
	{
		// Assume we consumed the gotFocus, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onLostFocus(SObject* o)
	{
		// Assume we consumed the lostFocus, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onMouseClickEx(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick)
	{
		// Assume we consumed the mouse click, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onMouseWheel(SObject* o, s32 tnUnits)
	{
		// Assume we consumed the mouse wheel, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onMouseMove(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick)
	{
		// Assume we consumed the mouse move, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onMouseDown(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick, u32 tnLastClick)
	{
		// Assume we consumed the mouse down event, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onMouseUp(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick, u32 tnLastClick)
	{
		// Assume we consumed the mosue up event, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onMouseEnter(SObject* o)
	{
		// Assume we consumed the enter, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onMouseLeave(SObject* o)
	{
		// Assume we consumed the leave, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onMouseHover(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick)
	{
		// Assume we consumed the hover, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onKeyDown(SObject* o, bool tlCtrl, bool tlAlt, bool tlShift, s16 tcAscii, u16 tnVKey, bool tlIsCAS, bool tlIsAscii)
	{
		// Assume we consumed the keydown, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onKeyUp(SObject* o, bool tlCtrl, bool tlAlt, bool tlShift, s16 tcAscii, u16 tnVKey, bool tlIsCAS, bool tlIsAscii)
	{
		// Assume we consumed the keyup, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onActivate(SObject* o)
	{
		// Assume we consumed the activate, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onDeactivate(SObject* o)
	{
		// Assume we consumed the deactivate, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onInteractiveChange(SObject* o)
	{
		// Assume we consumed the interactiveChange, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onProgrammaticChange(SObject* o)
	{
		// Assume we consumed the programmaticChange, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onSelect(SObject* o, SObject* oItem)
	{
		// Assume we consumed the onSelect, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onDeselect(SObject* o, SObject* oItem)
	{
		// Assume we consumed the onDeselect, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onMoved(SObject* o, u32* xOverride_out, u32* yOverride_out)
	{
		// Assume we consumed the onDeselect, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onQueryUnload(SObject* o)
	{
		// Assume we consumed the onDeselect, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onAddObject(SObject* o)
	{
		// Assume we consumed the onDeselect, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onAddProperty(SObject* o)
	{
		// Assume we consumed the onDeselect, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onError(SObject* o)
	{
		// Assume we consumed the onDeselect, and that the parent doesn't need to receive it
		return(false);
	}

	bool iDefaultCallback_onScrolled(SObject* o)
	{
		// Assume we consumed the onDeselect, and that the parent doesn't need to receive it
		return(false);
	}
