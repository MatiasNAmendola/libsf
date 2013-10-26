//////////
//
// /libsf/vvm/apps/whitebox/wb_cb.cpp
//
//////
// Version 0.10
// Copyright (c) 2013 by Rick C. Hodgin
//////
// Last update:
//     May.17.2013 - Initial creation
//////
// Change log:
//     May.17.2013 - Initial creation
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
//     http://www.visual-freepro.org
//     http://www.visual-freepro.org/wiki/
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//








//////////
//
// Callback when the window is moved by user or programmatically
//
/////
	void CALLTYPE iwb_callbackWindowMoved(u64 tnUniqueId, SOssWindow* tisw, u32 tnXNew, u32 tnYNew)
	{
		_asm nop;
	}




//////////
//
// Callback when the window is resized
//
/////
	void CALLTYPE iwb_callbackWindowResized(u64 tnUniqueId, SOssWindow* tisw, u32 tnWidthNew, u32 tnHeightNew)
	{
		_asm nop;
	}




//////////
//
// Callback when the window receives focus, including after initial creation
//
/////
	void CALLTYPE iwb_callbackWindowGotFocus(u64 tnUniqueId, SOssWindow* tisw)
	{
		_asm nop;
	}




//////////
//
// Callback when the window loses focus
//
/////
	void CALLTYPE iwb_callbackWindowLostFocus(u64 tnUniqueId, SOssWindow* tisw)
	{
		_asm nop;
	}




//////////
//
// Callback when a mouse button is pressed down
//
/////
	void CALLTYPE iwb_callbackMouseDown(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)

	{
		_asm nop;
	}




//////////
//
// Callback when a mouse button is released
//
/////
	void CALLTYPE iwb_callbackMouseUp(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
	{
		_asm nop;
	}




//////////
//
// Callback when the mouse is moved with buttons either up or down
//
/////
	void CALLTYPE iwb_callbackMouseMove(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
	{
		_asm nop;
	}




//////////
//
// Callback when the mouse hovers over a particular point
// Closing flag is signaled if a hover event has been signaled, and now it's no longer hovering
//
/////
	void CALLTYPE iwb_callbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		_asm nop;
	}




//////////
//
// Callback when a drag by the mouse is detected
//
/////
	void CALLTYPE iwb_callbackDragStart(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
	{
		_asm nop;
	}




//////////
//
// Callback when a drag by the mouse is in motion, called in lieu of iCallbackMouseMove()
//
/////
	void CALLTYPE iwb_callbackDragging(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds)
	{
		_asm nop;
	}




//////////
//
// Callback when a drag by the mouse has ended and the dragging button released
//
/////
	void CALLTYPE iwb_callbackDragDrop(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds)
	{
		_asm nop;
	}





//////////
//
// Callback when a key is pressed down.  It is not called on repeated keystrokes.  Use KeyPress for that.
//
/////
	void CALLTYPE iwb_callbackKeyDown(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
	{
		switch (tnKey)
		{
			case VVM_F12:
				_asm int 3;
				break;

			default:
				// Unknown key
				return;
		}
	}




//////////
//
// Callback when a key is released.
//
/////
	void CALLTYPE iwb_callbackKeyUp(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
	{
		_asm nop;
	}




//////////
//
// Callback when a key is signaled by being pressed down, either initially, or through repeating.
// This function is identical to KeyDown except that it is signaled for every repeat.
//
/////
	void CALLTYPE iwb_callbackKeyPress(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
	{
		_asm nop;
	}




//////////
//
// Callback when a special key flag condition changes.  Makes it easy to identify shift, alt,
// control, caps lock, num lock and scroll lock.
//
/////
	void CALLTYPE iwb_callbackKeyFlags(u64 tnUniqueId, SOssWindow* tisw, u32 tnKeyFlagsOld, u32 tnKeyFlagsNew)
	{
		_asm nop;
	}
