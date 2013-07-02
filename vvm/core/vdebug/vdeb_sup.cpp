//////////
//
// /libsf/VDebug/VDebug/vdeb_support.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     September 28, 2012 - Initial creation
//     September 29, 2012 - PBL v1.0 license included directly in source files.
//     November 07, 2012 - 0.60 development begins
//////
// See devhelp.txt.
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
//     http://www.visual-freepro.org/blog/
//     http://www.visual-freepro.org/forum/
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
// Test code, builds various screen forms to try out features
//
/////
	u64 iBuildScreen(	u64 tnUniqueId,
						s8* tcCaption, u32 tnCaptionLength,
						u32 tnX, u32 tnY,
						u32 tnWidth, u32 tnHeight,
						u32 tnWidthMin, u32 tnHeightMin,
						u32 tnWidthMax, u32 tnHeightMax,
						u32 foreColor, u32 backColor,
						bool tlResizable, bool tlMovable, bool tlClosable, bool tlVisible, bool tlBorder,
						SCallbacks* callbacks)
	{
		u64 lisw;


		// Validate parameters
		if (tnWidthMin  == -1 || !tlResizable)		tnWidthMin	= tnWidth;
		if (tnHeightMin == -1 || !tlResizable)		tnHeightMin	= tnHeight;
		if (tnWidthMax  == -1 || !tlResizable)		tnWidthMax	= tnWidth;
		if (tnHeightMax == -1 || !tlResizable)		tnHeightMax	= tnHeight;

		// Create the indicated screen structure
		lisw = oss_createScreenTemplate(	tnUniqueId, vvm_getNextUniqueId(),
											tcCaption, tnCaptionLength,
											tnX, tnY,
											tnWidth, tnHeight,
											tnWidthMin, tnHeightMin,
											tnWidthMax, tnHeightMax,
											0, 0, tnWidth, 32, 4,
											foreColor, backColor,
											tlResizable, tlMovable, tlClosable, tlVisible, tlBorder,
											callbacks);

// TODO:  Append the unique ID on here to the caption if there is more than one instance running
		// All done
		return(lisw);
	}




//////////
//
// Set the callbacks to an empty/null state
//
//////
	void iInitializeCallbacksToNull(SCallbacks* tcb)
	{
		memset(tcb, 0, sizeof(SCallbacks));
	}





//////////
//
// Callback when the window is moved by user or programmatically
//
/////
	void CALLTYPE iCallbackWindowMoved(u64 tnUniqueId, SOssWindow* tisw, u32 tnXNew, u32 tnYNew)
	{
		_asm nop;
	}




//////////
//
// Callback when the window is resized
//
/////
	void CALLTYPE iCallbackWindowResized(u64 tnUniqueId, SOssWindow* tisw, u32 tnWidthNew, u32 tnHeightNew)
	{
		_asm nop;
	}




//////////
//
// Callback when the window receives focus, including after initial creation
//
/////
	void CALLTYPE iCallbackWindowGotFocus(u64 tnUniqueId, SOssWindow* tisw)
	{
		_asm nop;
	}




//////////
//
// Callback when the window loses focus
//
/////
	void CALLTYPE iCallbackWindowLostFocus(u64 tnUniqueId, SOssWindow* tisw)
	{
		_asm nop;
	}





//////////
//
// Callback when a mouse button is pressed down
//
/////
	void CALLTYPE iCallbackMouseDown(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
	{
		_asm nop;
	}




//////////
//
// Callback when a mouse button is released
//
/////
	void CALLTYPE iCallbackMouseUp(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
	{
		_asm nop;
	}




//////////
//
// Callback when the mouse is moved with buttons either up or down
//
/////
	void CALLTYPE iCallbackMouseMove(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
	{
		_asm nop;
	}




//////////
//
// Callback when the mouse hovers over a particular point
// Closing flag is signaled if a hover event has been signaled, and now it's no longer hovering
//
/////
	void CALLTYPE iCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		_asm nop;
	}




//////////
//
// Callback when a drag by the mouse is detected
//
/////
	void CALLTYPE iCallbackDragStart(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)
	{
		_asm nop;
	}




//////////
//
// Callback when a drag by the mouse is in motion, called in lieu of iCallbackMouseMove()
//
/////
	void CALLTYPE iCallbackDragging(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds)
	{
		_asm nop;
	}




//////////
//
// Callback when a drag by the mouse has ended and the dragging button released
//
/////
	void CALLTYPE iCallbackDragDrop(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds)
	{
		_asm nop;
	}





//////////
//
// Callback when a key is pressed down.  It is not called on repeated keystrokes.  Use KeyPress for that.
//
/////
	void CALLTYPE iCallbackKeyDown(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
	{
		_asm nop;
	}




//////////
//
// Callback when a key is released.
//
/////
	void CALLTYPE iCallbackKeyUp(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
	{
		_asm nop;
	}




//////////
//
// Callback when a key is signaled by being pressed down, either initially, or through repeating.
// This function is identical to KeyDown except that it is signaled for every repeat.
//
/////
	void CALLTYPE iCallbackKeyPress(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
	{
		_asm nop;
	}




//////////
//
// Callback when a special key flag condition changes.  Makes it easy to identify shift, alt,
// control, caps lock, num lock and scroll lock.
//
/////
	void CALLTYPE iCallbackKeyFlags(u64 tnUniqueId, SOssWindow* tisw, u32 tnKeyFlagsOld, u32 tnKeyFlagsNew)
	{
		_asm nop;
	}
