//////////
//
// /libsf/vvm/vdebug/vdebug/vdeb_screens.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     October 21, 2012 - Initial creation
//     October 21, 2012 - PBL v1.0 license included directly in source files.
//     November 07, 2012 - 0.60 development begins
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
// Scratch memory
//////
	s8	gcScratch01[]				= "ɘ���������Scratch��������͚�";
	s8	gcScratch02[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch03[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch04[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch05[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch06[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch07[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch08[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch09[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch10[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch11[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch12[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch13[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch14[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch15[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch16[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch17[]				= "� 000:0000:00:00:0000:00:00 �";
	s8	gcScratch18[]				= "���������������������������ʼ";

	u64 iBuildNewScreen_Scratch(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iScratchCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcScratchCaption, sizeof(gcScratchCaption), 
								0, 0, 
								(sizeof(gcScratch01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc					= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch01, sizeof(gcScratch01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch02, sizeof(gcScratch02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch03, sizeof(gcScratch03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch04, sizeof(gcScratch04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch05, sizeof(gcScratch05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch06, sizeof(gcScratch06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch07, sizeof(gcScratch07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch08, sizeof(gcScratch08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch09, sizeof(gcScratch09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch10, sizeof(gcScratch10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch11, sizeof(gcScratch11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch12, sizeof(gcScratch12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch13, sizeof(gcScratch13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch14, sizeof(gcScratch14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch15, sizeof(gcScratch15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch16, sizeof(gcScratch16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch17, sizeof(gcScratch17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcScratch18, sizeof(gcScratch18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iScratchCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Program registers
//////
	s8	gcProgramRegisters01[]		= "ɘ����Program Registers���͚�";
	s8	gcProgramRegisters02[]		= "�                           �";
	s8	gcProgramRegisters03[]		= "�   PPO  00000000:00000000  �";
	s8	gcProgramRegisters04[]		= "�  PLOC  00000000:00000000  �";
	s8	gcProgramRegisters05[]		= "�  PREG  00000000:00000000  �";
	s8	gcProgramRegisters06[]		= "�  PPAR  00000000:00000000  �";
	s8	gcProgramRegisters07[]		= "�  PRET  00000000:00000000  �";
	s8	gcProgramRegisters08[]		= "�                           �";
	s8	gcProgramRegisters09[]		= "�   CPO  00000000:00000000  �";
	s8	gcProgramRegisters10[]		= "�  CLOC  00000000:00000000  �";
	s8	gcProgramRegisters11[]		= "�  CREG  00000000:00000000  �";
	s8	gcProgramRegisters12[]		= "�  CPAR  00000000:00000000  �";
	s8	gcProgramRegisters13[]		= "�  CRET  00000000:00000000  �";
	s8	gcProgramRegisters14[]		= "�                           �";
	s8	gcProgramRegisters15[]		= "�                           �";
	s8	gcProgramRegisters16[]		= "�                           �";
	s8	gcProgramRegisters17[]		= "�                           �";
	s8	gcProgramRegisters18[]		= "���������������������������ʼ";

	u64 iBuildNewScreen_ProgramRegisters(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iProgramRegistersCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcProgramRegistersCaption, sizeof(gcProgramRegistersCaption), 
								0, 0, 
								(sizeof(gcProgramRegisters01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc					= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters01, sizeof(gcProgramRegisters01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters02, sizeof(gcProgramRegisters02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters03, sizeof(gcProgramRegisters03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters04, sizeof(gcProgramRegisters04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters05, sizeof(gcProgramRegisters05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters06, sizeof(gcProgramRegisters06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters07, sizeof(gcProgramRegisters07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters08, sizeof(gcProgramRegisters08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters09, sizeof(gcProgramRegisters09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters10, sizeof(gcProgramRegisters10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters11, sizeof(gcProgramRegisters11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters12, sizeof(gcProgramRegisters12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters13, sizeof(gcProgramRegisters13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters14, sizeof(gcProgramRegisters14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters15, sizeof(gcProgramRegisters15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters16, sizeof(gcProgramRegisters16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters17, sizeof(gcProgramRegisters17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcProgramRegisters18, sizeof(gcProgramRegisters18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iProgramRegistersCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Control registers
//////
	s8	gcControlRegisters01[]		= "ɘ����Control Registers���͚�";
	s8	gcControlRegisters02[]		= "�                           �";
	s8	gcControlRegisters03[]		= "�    IP  00000000:00000000  �";
	s8	gcControlRegisters04[]		= "�  CTHR  00000000:00000000  �";
	s8	gcControlRegisters05[]		= "�  XSNP  00000000:00000000  �";
	s8	gcControlRegisters06[]		= "�             SP  00000000  �";
	s8	gcControlRegisters07[]		= "� FLAGS                     �";
	s8	gcControlRegisters08[]		= "�    0000-0000-0000-0000    �";
	s8	gcControlRegisters09[]		= "�    0000-0000-0000-0000    �";
	s8	gcControlRegisters10[]		= "�    0000-0000-0000-0000    �";
	s8	gcControlRegisters11[]		= "�    0000-0000-0000-0000    �";
	s8	gcControlRegisters12[]		= "�    0000-0000-0000-0000    �";
	s8	gcControlRegisters13[]		= "�    0000-0000-0000-0000    �";
	s8	gcControlRegisters14[]		= "�    0000-0000-0000-0000    �";
	s8	gcControlRegisters15[]		= "�    0000-0000-0000-0000    �";
	s8	gcControlRegisters16[]		= "�   ov?   cy?   ab?   app?  �";
	s8	gcControlRegisters17[]		= "�   un?   eq?   be?         �";
	s8	gcControlRegisters18[]		= "���������������������������ʼ";

	u64 iBuildNewScreen_ControlRegisters(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iControlRegistersCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
			gcProgramRegistersCaption, sizeof(gcProgramRegistersCaption), 
			0, 0, 
			(sizeof(gcControlRegisters01) - 1) * lnFontWidth, 
			18 * lnFontSkip, 
			-1, -1, 
			-1, -1, 
			foreColor, backColor, 
			false, true, false, true, true,
			&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc					= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters01, sizeof(gcControlRegisters01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters02, sizeof(gcControlRegisters02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters03, sizeof(gcControlRegisters03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters04, sizeof(gcControlRegisters04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters05, sizeof(gcControlRegisters05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters06, sizeof(gcControlRegisters06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters07, sizeof(gcControlRegisters07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters08, sizeof(gcControlRegisters08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters09, sizeof(gcControlRegisters09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters10, sizeof(gcControlRegisters10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters11, sizeof(gcControlRegisters11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters12, sizeof(gcControlRegisters12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters13, sizeof(gcControlRegisters13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters14, sizeof(gcControlRegisters14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters15, sizeof(gcControlRegisters15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters16, sizeof(gcControlRegisters16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters17, sizeof(gcControlRegisters17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcControlRegisters18, sizeof(gcControlRegisters18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iControlRegistersCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Integer registers
//////
	s8	gcIntegerRegisters01[]	= "ɘ����Integer Registers���͚�";
	s8	gcIntegerRegisters02[]	= "�   A 00000000:0000:00:00   �";
	s8	gcIntegerRegisters03[]	= "�   B 00000000:0000:00:00   �";
	s8	gcIntegerRegisters04[]	= "�   C 00000000:0000:00:00   �";
	s8	gcIntegerRegisters05[]	= "�   D 00000000:0000:00:00   �";
	s8	gcIntegerRegisters06[]	= "�   E 00000000:0000:00:00   �";
	s8	gcIntegerRegisters07[]	= "�   F 00000000:0000:00:00   �";
	s8	gcIntegerRegisters08[]	= "�   G 00000000:0000:00:00   �";
	s8	gcIntegerRegisters09[]	= "�   H 00000000:0000:00:00   �";
	s8	gcIntegerRegisters10[]	= "�   I 00000000:0000:00:00   �";
	s8	gcIntegerRegisters11[]	= "�   J 00000000:0000:00:00   �";
	s8	gcIntegerRegisters12[]	= "�   K 00000000:0000:00:00   �";
	s8	gcIntegerRegisters13[]	= "�   L 00000000:0000:00:00   �";
	s8	gcIntegerRegisters14[]	= "�   M 00000000:0000:00:00   �";
	s8	gcIntegerRegisters15[]	= "�   N 00000000:0000:00:00   �";
	s8	gcIntegerRegisters16[]	= "�   O 00000000:0000:00:00   �";
	s8	gcIntegerRegisters17[]	= "�   P 00000000:0000:00:00   �";
	s8	gcIntegerRegisters18[]	= "���������������������������ʼ";

	u64 iBuildNewScreen_IntegerRegisters(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iIntegerRegistersCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcIntegerRegistersCaption, sizeof(gcIntegerRegistersCaption), 
								0, 0, 
								(sizeof(gcIntegerRegisters01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc					= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters01, sizeof(gcIntegerRegisters01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters02, sizeof(gcIntegerRegisters02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters03, sizeof(gcIntegerRegisters03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters04, sizeof(gcIntegerRegisters04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters05, sizeof(gcIntegerRegisters05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters06, sizeof(gcIntegerRegisters06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters07, sizeof(gcIntegerRegisters07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters08, sizeof(gcIntegerRegisters08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters09, sizeof(gcIntegerRegisters09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters10, sizeof(gcIntegerRegisters10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters11, sizeof(gcIntegerRegisters11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters12, sizeof(gcIntegerRegisters12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters13, sizeof(gcIntegerRegisters13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters14, sizeof(gcIntegerRegisters14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters15, sizeof(gcIntegerRegisters15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters16, sizeof(gcIntegerRegisters16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters17, sizeof(gcIntegerRegisters17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcIntegerRegisters18, sizeof(gcIntegerRegisters18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iIntegerRegistersCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}





//////////
// Floating point registers
//////
	s8	gcFloatingPointRegisters01[]	= "ɘ���Floating Point Regs��͚�";
	s8	gcFloatingPointRegisters02[]	= "�   FA +0.000000000000000   �";
	s8	gcFloatingPointRegisters03[]	= "�   FB +0.000000000000000   �";
	s8	gcFloatingPointRegisters04[]	= "�   FC +0.000000000000000   �";
	s8	gcFloatingPointRegisters05[]	= "�   FD +0.000000000000000   �";
	s8	gcFloatingPointRegisters06[]	= "�   FE +0.000000000000000   �";
	s8	gcFloatingPointRegisters07[]	= "�   FF +0.000000000000000   �";
	s8	gcFloatingPointRegisters08[]	= "�   FG +0.000000000000000   �";
	s8	gcFloatingPointRegisters09[]	= "�   FH +0.000000000000000   �";
	s8	gcFloatingPointRegisters10[]	= "�   FI +0.000000000000000   �";
	s8	gcFloatingPointRegisters11[]	= "�   FJ +0.000000000000000   �";
	s8	gcFloatingPointRegisters12[]	= "�   FK +0.000000000000000   �";
	s8	gcFloatingPointRegisters13[]	= "�   FL +0.000000000000000   �";
	s8	gcFloatingPointRegisters14[]	= "�   FM +0.000000000000000   �";
	s8	gcFloatingPointRegisters15[]	= "�   FN +0.000000000000000   �";
	s8	gcFloatingPointRegisters16[]	= "�   FO +0.000000000000000   �";
	s8	gcFloatingPointRegisters17[]	= "�   FP +0.000000000000000   �";
	s8	gcFloatingPointRegisters18[]	= "���������������������������ʼ";

	u64 iBuildNewScreen_FloatingPointRegisters(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iIntegerRegistersCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcFloatingPointRegistersCaption, sizeof(gcFloatingPointRegistersCaption), 
								0, 0, 
								(sizeof(gcFloatingPointRegisters01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc					= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters01, sizeof(gcFloatingPointRegisters01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters02, sizeof(gcFloatingPointRegisters02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters03, sizeof(gcFloatingPointRegisters03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters04, sizeof(gcFloatingPointRegisters04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters05, sizeof(gcFloatingPointRegisters05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters06, sizeof(gcFloatingPointRegisters06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters07, sizeof(gcFloatingPointRegisters07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters08, sizeof(gcFloatingPointRegisters08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters09, sizeof(gcFloatingPointRegisters09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters10, sizeof(gcFloatingPointRegisters10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters11, sizeof(gcFloatingPointRegisters11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters12, sizeof(gcFloatingPointRegisters12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters13, sizeof(gcFloatingPointRegisters13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters14, sizeof(gcFloatingPointRegisters14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters15, sizeof(gcFloatingPointRegisters15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters16, sizeof(gcFloatingPointRegisters16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters17, sizeof(gcFloatingPointRegisters17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcFloatingPointRegisters18, sizeof(gcFloatingPointRegisters18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iFloatingPointRegistersCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}





//////////
// Stack
//////
	s8	gcStack01[]					= "ɘ����������Stack���������͚�";
	s8	gcStack02[]					= "� 00000000 00000000:00000000�";
	s8	gcStack03[]					= "� 00000000 00000000:00000000�";
	s8	gcStack04[]					= "� 00000000 00000000:00000000�";
	s8	gcStack05[]					= "� 00000000 00000000:00000000�";
	s8	gcStack06[]					= "� 00000000 00000000:00000000�";
	s8	gcStack07[]					= "� 00000000 00000000:00000000�";
	s8	gcStack08[]					= "� 00000000 00000000:00000000�";
	s8	gcStack09[]					= "� 00000000 00000000:00000000�";
	s8	gcStack10[]					= "� 00000000 00000000:00000000�";
	s8	gcStack11[]					= "� 00000000 00000000:00000000�";
	s8	gcStack12[]					= "� 00000000 00000000:00000000�";
	s8	gcStack13[]					= "� 00000000 00000000:00000000�";
	s8	gcStack14[]					= "� 00000000 00000000:00000000�";
	s8	gcStack15[]					= "� 00000000 00000000:00000000�";
	s8	gcStack16[]					= "� 00000000 00000000:00000000�";
	s8	gcStack17[]					= "� 00000000 00000000:00000000�";
	s8	gcStack18[]					= "���������������������������ʼ";

	u64 iBuildNewScreen_Stack(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iStackCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcStackCaption, sizeof(gcStackCaption), 
								0, 0, 
								(sizeof(gcStack01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc					= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack01, sizeof(gcStack01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack02, sizeof(gcStack02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack03, sizeof(gcStack03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack04, sizeof(gcStack04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack05, sizeof(gcStack05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack06, sizeof(gcStack06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack07, sizeof(gcStack07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack08, sizeof(gcStack08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack09, sizeof(gcStack09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack10, sizeof(gcStack10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack11, sizeof(gcStack11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack12, sizeof(gcStack12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack13, sizeof(gcStack13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack14, sizeof(gcStack14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack15, sizeof(gcStack15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack16, sizeof(gcStack16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack17, sizeof(gcStack17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcStack18, sizeof(gcStack18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iStackCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Watch Window
//////
	s8	gcWatch01[]					= "ɘ���������������������������Watch Window���������������������������͚�";
	s8	gcWatch02[]					= "�             �                                                       �";
	s8	gcWatch03[]					= "�             �                                                       �";
	s8	gcWatch04[]					= "�             �                                                       �";
	s8	gcWatch05[]					= "�             �                                                       �";
	s8	gcWatch06[]					= "�             �                                                       �";
	s8	gcWatch07[]					= "�             �                                                       �";
	s8	gcWatch08[]					= "�             �                                                       �";
	s8	gcWatch09[]					= "�             �                                                       �";
	s8	gcWatch10[]					= "�             �                                                       �";
	s8	gcWatch11[]					= "�             �                                                       �";
	s8	gcWatch12[]					= "�             �                                                       �";
	s8	gcWatch13[]					= "�             �                                                       �";
	s8	gcWatch14[]					= "�             �                                                       �";
	s8	gcWatch15[]					= "�             �                                                       �";
	s8	gcWatch16[]					= "�             �                                                       �";
	s8	gcWatch17[]					= "�             �                                                       �";
	s8	gcWatch18[]					= "���������������������������������������������������������������������ʼ";

	u64 iBuildNewScreen_Watch(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iWatchCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcWatchCaption, sizeof(gcWatchCaption), 
								0, 0, 
								(sizeof(gcWatch01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc					= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch01, sizeof(gcWatch01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch02, sizeof(gcWatch02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch03, sizeof(gcWatch03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch04, sizeof(gcWatch04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch05, sizeof(gcWatch05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch06, sizeof(gcWatch06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch07, sizeof(gcWatch07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch08, sizeof(gcWatch08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch09, sizeof(gcWatch09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch10, sizeof(gcWatch10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch11, sizeof(gcWatch11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch12, sizeof(gcWatch12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch13, sizeof(gcWatch13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch14, sizeof(gcWatch14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch15, sizeof(gcWatch15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch16, sizeof(gcWatch16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch17, sizeof(gcWatch17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcWatch18, sizeof(gcWatch18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iWatchCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Hover Window
//////
	s8	gcHover01[]					= "ɘ�����������������Hover Window����������������͚�";
	s8	gcHover02[]					= "�             �                                  �";
	s8	gcHover03[]					= "�             �                                  �";
	s8	gcHover04[]					= "�             �                                  �";
	s8	gcHover05[]					= "�             �                                  �";
	s8	gcHover06[]					= "�             �                                  �";
	s8	gcHover07[]					= "�             �                                  �";
	s8	gcHover08[]					= "�             �                                  �";
	s8	gcHover09[]					= "�             �                                  �";
	s8	gcHover10[]					= "�             �                                  �";
	s8	gcHover11[]					= "�             �                                  �";
	s8	gcHover12[]					= "�             �                                  �";
	s8	gcHover13[]					= "�             �                                  �";
	s8	gcHover14[]					= "�             �                                  �";
	s8	gcHover15[]					= "�             �                                  �";
	s8	gcHover16[]					= "�             �                                  �";
	s8	gcHover17[]					= "�             �                                  �";
	s8	gcHover18[]					= "������������������������������������������������ʼ";

	u64 iBuildNewScreen_Hover(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iHoverCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcHoverCaption, sizeof(gcHoverCaption), 
								0, 0, 
								(sizeof(gcHover01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc					= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover01, sizeof(gcHover01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover02, sizeof(gcHover02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover03, sizeof(gcHover03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover04, sizeof(gcHover04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover05, sizeof(gcHover05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover06, sizeof(gcHover06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover07, sizeof(gcHover07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover08, sizeof(gcHover08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover09, sizeof(gcHover09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover10, sizeof(gcHover10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover11, sizeof(gcHover11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover12, sizeof(gcHover12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover13, sizeof(gcHover13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover14, sizeof(gcHover14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover15, sizeof(gcHover15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover16, sizeof(gcHover16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover17, sizeof(gcHover17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcHover18, sizeof(gcHover18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iHoverCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Locals
//////
	s8	gcLocals01[]				= "ɘ��������������������Locals�������������������͚�";
	s8	gcLocals02[]				= "�             �    �                             �";
	s8	gcLocals03[]				= "�             �    �                             �";
	s8	gcLocals04[]				= "�             �    �                             �";
	s8	gcLocals05[]				= "�             �    �                             �";
	s8	gcLocals06[]				= "�             �    �                             �";
	s8	gcLocals07[]				= "�             �    �                             �";
	s8	gcLocals08[]				= "�             �    �                             �";
	s8	gcLocals09[]				= "�             �    �                             �";
	s8	gcLocals10[]				= "�             �    �                             �";
	s8	gcLocals11[]				= "�             �    �                             �";
	s8	gcLocals12[]				= "�             �    �                             �";
	s8	gcLocals13[]				= "�             �    �                             �";
	s8	gcLocals14[]				= "�             �    �                             �";
	s8	gcLocals15[]				= "�             �    �                             �";
	s8	gcLocals16[]				= "�             �    �                             �";
	s8	gcLocals17[]				= "�             �    �                             �";
	s8	gcLocals18[]				= "������������������������������������������������ʼ";

	u64 iBuildNewScreen_Locals(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iLocalsCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcLocalsCaption, sizeof(gcLocalsCaption), 
								0, 0, 
								(sizeof(gcLocals01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc					= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals01, sizeof(gcLocals01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals02, sizeof(gcLocals02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals03, sizeof(gcLocals03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals04, sizeof(gcLocals04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals05, sizeof(gcLocals05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals06, sizeof(gcLocals06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals07, sizeof(gcLocals07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals08, sizeof(gcLocals08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals09, sizeof(gcLocals09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals10, sizeof(gcLocals10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals11, sizeof(gcLocals11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals12, sizeof(gcLocals12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals13, sizeof(gcLocals13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals14, sizeof(gcLocals14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals15, sizeof(gcLocals15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals16, sizeof(gcLocals16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals17, sizeof(gcLocals17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcLocals18, sizeof(gcLocals18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iLocalsCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Autos
//////
	s8	gcAutos01[]					= "ɘ���������������������Autos�������������������͚�";
	s8	gcAutos02[]					= "�             �    �                             �";
	s8	gcAutos03[]					= "�             �    �                             �";
	s8	gcAutos04[]					= "�             �    �                             �";
	s8	gcAutos05[]					= "�             �    �                             �";
	s8	gcAutos06[]					= "�             �    �                             �";
	s8	gcAutos07[]					= "�             �    �                             �";
	s8	gcAutos08[]					= "�             �    �                             �";
	s8	gcAutos09[]					= "�             �    �                             �";
	s8	gcAutos10[]					= "�             �    �                             �";
	s8	gcAutos11[]					= "�             �    �                             �";
	s8	gcAutos12[]					= "�             �    �                             �";
	s8	gcAutos13[]					= "�             �    �                             �";
	s8	gcAutos14[]					= "�             �    �                             �";
	s8	gcAutos15[]					= "�             �    �                             �";
	s8	gcAutos16[]					= "�             �    �                             �";
	s8	gcAutos17[]					= "�             �    �                             �";
	s8	gcAutos18[]					= "������������������������������������������������ʼ";

	u64 iBuildNewScreen_Autos(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iAutosCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcAutosCaption, sizeof(gcAutosCaption), 
								0, 0, 
								(sizeof(gcAutos01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc					= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos01, sizeof(gcAutos01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos02, sizeof(gcAutos02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos03, sizeof(gcAutos03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos04, sizeof(gcAutos04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos05, sizeof(gcAutos05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos06, sizeof(gcAutos06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos07, sizeof(gcAutos07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos08, sizeof(gcAutos08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos09, sizeof(gcAutos09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos10, sizeof(gcAutos10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos11, sizeof(gcAutos11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos12, sizeof(gcAutos12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos13, sizeof(gcAutos13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos14, sizeof(gcAutos14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos15, sizeof(gcAutos15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos16, sizeof(gcAutos16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos17, sizeof(gcAutos17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAutos18, sizeof(gcAutos18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iAutosCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Timers
//////
	s8	gcTimers01[]				= "ɘ���������������������Timers�������������������͚�";
	s8	gcTimers02[]				= "�         �     �     �                          �";
	s8	gcTimers03[]				= "�         �     �     �                          �";
	s8	gcTimers04[]				= "�         �     �     �                          �";
	s8	gcTimers05[]				= "�         �     �     �                          �";
	s8	gcTimers06[]				= "�         �     �     �                          �";
	s8	gcTimers07[]				= "�         �     �     �                          �";
	s8	gcTimers08[]				= "�         �     �     �                          �";
	s8	gcTimers09[]				= "�         �     �     �                          �";
	s8	gcTimers10[]				= "�         �     �     �                          �";
	s8	gcTimers11[]				= "�         �     �     �                          �";
	s8	gcTimers12[]				= "�         �     �     �                          �";
	s8	gcTimers13[]				= "�         �     �     �                          �";
	s8	gcTimers14[]				= "�         �     �     �                          �";
	s8	gcTimers15[]				= "�         �     �     �                          �";
	s8	gcTimers16[]				= "�         �     �     �                          �";
	s8	gcTimers17[]				= "�         �     �     �                          �";
	s8	gcTimers18[]				= "������������������������������������������������ʼ";

	u64 iBuildNewScreen_Timers(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iTimersCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcTimersCaption, sizeof(gcTimersCaption), 
								0, 0, 
								(sizeof(gcTimers01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc				= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers01, sizeof(gcTimers01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers02, sizeof(gcTimers02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers03, sizeof(gcTimers03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers04, sizeof(gcTimers04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers05, sizeof(gcTimers05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers06, sizeof(gcTimers06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers07, sizeof(gcTimers07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers08, sizeof(gcTimers08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers09, sizeof(gcTimers09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers10, sizeof(gcTimers10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers11, sizeof(gcTimers11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers12, sizeof(gcTimers12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers13, sizeof(gcTimers13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers14, sizeof(gcTimers14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers15, sizeof(gcTimers15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers16, sizeof(gcTimers16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers17, sizeof(gcTimers17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcTimers18, sizeof(gcTimers18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iTimersCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Memory Window
//////
	s8	gcMemory01[]				= "ɘ�����������������������Memory���������������������͚�";
	s8	gcMemory02[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory03[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory04[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory05[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory06[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory07[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory08[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory09[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory10[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory11[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory12[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory13[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory14[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory15[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory16[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory17[]				= "�00000�00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00�";
	s8	gcMemory18[]				= "�����������������������������������������������������ʼ";

	u64 iBuildNewScreen_Memory(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iMemoryCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcMemoryCaption, sizeof(gcMemoryCaption), 
								0, 0, 
								(sizeof(gcMemory01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc				= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory01, sizeof(gcMemory01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory02, sizeof(gcMemory02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory03, sizeof(gcMemory03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory04, sizeof(gcMemory04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory05, sizeof(gcMemory05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory06, sizeof(gcMemory06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory07, sizeof(gcMemory07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory08, sizeof(gcMemory08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory09, sizeof(gcMemory09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory10, sizeof(gcMemory10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory11, sizeof(gcMemory11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory12, sizeof(gcMemory12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory13, sizeof(gcMemory13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory14, sizeof(gcMemory14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory15, sizeof(gcMemory15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory16, sizeof(gcMemory16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory17, sizeof(gcMemory17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcMemory18, sizeof(gcMemory18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iMemoryCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Programs
//////
	s8	gcPrograms01[]				= "ɘ�������������������Programs������������������͚�";
	s8	gcPrograms02[]				= "�             �    �                             �";
	s8	gcPrograms03[]				= "�             �    �                             �";
	s8	gcPrograms04[]				= "�             �    �                             �";
	s8	gcPrograms05[]				= "�             �    �                             �";
	s8	gcPrograms06[]				= "�             �    �                             �";
	s8	gcPrograms07[]				= "�             �    �                             �";
	s8	gcPrograms08[]				= "�             �    �                             �";
	s8	gcPrograms09[]				= "�             �    �                             �";
	s8	gcPrograms10[]				= "�             �    �                             �";
	s8	gcPrograms11[]				= "�             �    �                             �";
	s8	gcPrograms12[]				= "�             �    �                             �";
	s8	gcPrograms13[]				= "�             �    �                             �";
	s8	gcPrograms14[]				= "�             �    �                             �";
	s8	gcPrograms15[]				= "�             �    �                             �";
	s8	gcPrograms16[]				= "�             �    �                             �";
	s8	gcPrograms17[]				= "�             �    �                             �";
	s8	gcPrograms18[]				= "������������������������������������������������ʼ";

	u64 iBuildNewScreen_Programs(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iProgramsCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcProgramsCaption, sizeof(gcProgramsCaption), 
								0, 0, 
								(sizeof(gcPrograms01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc				= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms01, sizeof(gcPrograms01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms02, sizeof(gcPrograms02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms03, sizeof(gcPrograms03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms04, sizeof(gcPrograms04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms05, sizeof(gcPrograms05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms06, sizeof(gcPrograms06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms07, sizeof(gcPrograms07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms08, sizeof(gcPrograms08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms09, sizeof(gcPrograms09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms10, sizeof(gcPrograms10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms11, sizeof(gcPrograms11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms12, sizeof(gcPrograms12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms13, sizeof(gcPrograms13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms14, sizeof(gcPrograms14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms15, sizeof(gcPrograms15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms16, sizeof(gcPrograms16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms17, sizeof(gcPrograms17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcPrograms18, sizeof(gcPrograms18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iProgramsCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Threads
//////
	s8	gcThreads01[]				= "ɘ��������������������Threads������������������͚�";
	s8	gcThreads02[]				= "�             �    �                             �";
	s8	gcThreads03[]				= "�             �    �                             �";
	s8	gcThreads04[]				= "�             �    �                             �";
	s8	gcThreads05[]				= "�             �    �                             �";
	s8	gcThreads06[]				= "�             �    �                             �";
	s8	gcThreads07[]				= "�             �    �                             �";
	s8	gcThreads08[]				= "�             �    �                             �";
	s8	gcThreads09[]				= "�             �    �                             �";
	s8	gcThreads10[]				= "�             �    �                             �";
	s8	gcThreads11[]				= "�             �    �                             �";
	s8	gcThreads12[]				= "�             �    �                             �";
	s8	gcThreads13[]				= "�             �    �                             �";
	s8	gcThreads14[]				= "�             �    �                             �";
	s8	gcThreads15[]				= "�             �    �                             �";
	s8	gcThreads16[]				= "�             �    �                             �";
	s8	gcThreads17[]				= "�             �    �                             �";
	s8	gcThreads18[]				= "������������������������������������������������ʼ";

	u64 iBuildNewScreen_Threads(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= gnFontSize;
		lnFontSkip		= gnFontSize;
		lnTop			= -gnFontSize;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iThreadsCallbackMouseHover;

		// Request a screen
		lisw = iBuildScreen(	tnUniqueId,
								gcThreadsCaption, sizeof(gcThreadsCaption), 
								0, 0, 
								(sizeof(gcThreads01) - 1) * lnFontWidth, 
								18 * lnFontSkip, 
								-1, -1, 
								-1, -1, 
								foreColor, backColor, 
								false, true, false, true, true,
								&lsCallbacks);

		ls = (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc				= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads01, sizeof(gcThreads01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads02, sizeof(gcThreads02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads03, sizeof(gcThreads03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads04, sizeof(gcThreads04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads05, sizeof(gcThreads05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads06, sizeof(gcThreads06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads07, sizeof(gcThreads07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads08, sizeof(gcThreads08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads09, sizeof(gcThreads09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads10, sizeof(gcThreads10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads11, sizeof(gcThreads11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads12, sizeof(gcThreads12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads13, sizeof(gcThreads13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads14, sizeof(gcThreads14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads15, sizeof(gcThreads15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads16, sizeof(gcThreads16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads17, sizeof(gcThreads17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcThreads18, sizeof(gcThreads18) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iThreadsCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Ascii chart
//////
	s8 gcAsciiChart01[]				= "ɘ���Ascii Chart��͚�";
	s8 gcAsciiChart02[]				= "�  0123456789ABCDEF �";
	s8 gcAsciiChart03[]				= "� 0                 �";
	s8 gcAsciiChart04[]				= "� 1                 �";
	s8 gcAsciiChart05[]				= "� 2                 �";
	s8 gcAsciiChart06[]				= "� 3                 �";
	s8 gcAsciiChart07[]				= "� 4                 �";
	s8 gcAsciiChart08[]				= "� 5                 �";
	s8 gcAsciiChart09[]				= "� 6                 �";
	s8 gcAsciiChart10[]				= "� 7                 �";
	s8 gcAsciiChart11[]				= "� 8                 �";
	s8 gcAsciiChart12[]				= "� 9                 �";
	s8 gcAsciiChart13[]				= "� A                 �";
	s8 gcAsciiChart14[]				= "� B                 �";
	s8 gcAsciiChart15[]				= "� C                 �";
	s8 gcAsciiChart16[]				= "� D                 �";
	s8 gcAsciiChart17[]				= "� E                 �";
	s8 gcAsciiChart18[]				= "� F                 �";
	s8 gcAsciiChart19[]				= "�������������������ʼ";
	
	void iPopulateAsciiSegment(s8* text, u8 c)
	{
		u32 lnI;

		for (lnI = 0; lnI < 16; lnI++)
			text[lnI + 3] = (s8)c++;
	}

	u64 iBuildNewScreen_AsciiChart(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= -16;
		lnFontSkip		= 16;
		lnTop			= -16;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.mouse._callback_hover = (u64)&iAsciiCallbackMouseHover;

		// Request a screen
		lisw		= iBuildScreen(	tnUniqueId,
									gcAsciiCaption, sizeof(gcAsciiCaption), 
									0, 0, 
									(sizeof(gcAsciiChart01) - 1) * lnFontWidth, 
									19 * lnFontSkip, 
									-1, -1, 
									-1, -1, 
									foreColor, backColor, 
									false, true, false, true, true,
									&lsCallbacks);

		ls			= (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc				= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Populate the portion at runtime
		iPopulateAsciiSegment(gcAsciiChart03, 0x00);
		iPopulateAsciiSegment(gcAsciiChart04, 0x10);
		iPopulateAsciiSegment(gcAsciiChart05, 0x20);
		iPopulateAsciiSegment(gcAsciiChart06, 0x30);
		iPopulateAsciiSegment(gcAsciiChart07, 0x40);
		iPopulateAsciiSegment(gcAsciiChart08, 0x50);
		iPopulateAsciiSegment(gcAsciiChart09, 0x60);
		iPopulateAsciiSegment(gcAsciiChart10, 0x70);
		iPopulateAsciiSegment(gcAsciiChart11, 0x80);
		iPopulateAsciiSegment(gcAsciiChart12, 0x90);
		iPopulateAsciiSegment(gcAsciiChart13, 0xa0);
		iPopulateAsciiSegment(gcAsciiChart14, 0xb0);
		iPopulateAsciiSegment(gcAsciiChart15, 0xc0);
		iPopulateAsciiSegment(gcAsciiChart16, 0xd0);
		iPopulateAsciiSegment(gcAsciiChart17, 0xe0);
		iPopulateAsciiSegment(gcAsciiChart18, 0xf0);

/*
		FILE* lfh = fopen("ascii.txt", "wb+");
		fwrite(gcAsciiChart02, 1, sizeof(gcAsciiChart02) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart03, 1, sizeof(gcAsciiChart03) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart04, 1, sizeof(gcAsciiChart04) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart05, 1, sizeof(gcAsciiChart05) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart06, 1, sizeof(gcAsciiChart06) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart07, 1, sizeof(gcAsciiChart07) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart08, 1, sizeof(gcAsciiChart08) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart09, 1, sizeof(gcAsciiChart09) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart10, 1, sizeof(gcAsciiChart10) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart11, 1, sizeof(gcAsciiChart11) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart12, 1, sizeof(gcAsciiChart12) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart13, 1, sizeof(gcAsciiChart13) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart14, 1, sizeof(gcAsciiChart14) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart15, 1, sizeof(gcAsciiChart15) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart16, 1, sizeof(gcAsciiChart16) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart17, 1, sizeof(gcAsciiChart17) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fwrite(gcAsciiChart18, 1, sizeof(gcAsciiChart18) - 3, lfh);
		fwrite("\n", 1, 1, lfh);
		fclose(lfh);
*/

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart01, sizeof(gcAsciiChart01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart02, sizeof(gcAsciiChart02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart03, sizeof(gcAsciiChart03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart04, sizeof(gcAsciiChart04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart05, sizeof(gcAsciiChart05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart06, sizeof(gcAsciiChart06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart07, sizeof(gcAsciiChart07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart08, sizeof(gcAsciiChart08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart09, sizeof(gcAsciiChart09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart10, sizeof(gcAsciiChart10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart11, sizeof(gcAsciiChart11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart12, sizeof(gcAsciiChart12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart13, sizeof(gcAsciiChart13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart14, sizeof(gcAsciiChart14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart15, sizeof(gcAsciiChart15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart16, sizeof(gcAsciiChart16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart17, sizeof(gcAsciiChart17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart18, sizeof(gcAsciiChart18) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcAsciiChart19, sizeof(gcAsciiChart19) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iAsciiCallbackMouseHover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)
	{
		if (!tlClosing)
			_asm nop;
	}




//////////
// Ascii chart
//////
	s8 gcVDebLauncher01[]			= "ɘ��VDeb Launcher�͚�ɘ��VDeb Launcher�͚�ɘ��VDeb Launcher�͚�ɘ��VDeb Launcher�͚�";
	s8 gcVDebLauncher02[]			= "�                   ��                   ��                   ��                   �";
	s8 gcVDebLauncher03[]			= "�   f1:Ascii Chart  ��   f1:Ascii Chart  ��   f1:Ascii Chart  ��   f1:Ascii Chart  �";
	s8 gcVDebLauncher04[]			= "�   f2:Scratch      ��   f2:Scratch      ��   f2:Scratch      ��   f2:Scratch      �";
	s8 gcVDebLauncher05[]			= "�   f3:Program Regs ��   f3:Program Regs ��   f3:Program Regs ��   f3:Program Regs �";
	s8 gcVDebLauncher06[]			= "�   f4:Control Regs ��   f4:Control Regs ��   f4:Control Regs ��   f4:Control Regs �";
	s8 gcVDebLauncher07[]			= "�   f5:Integer Regs ��   f5:Integer Regs ��   f5:Integer Regs ��   f5:Integer Regs �";
	s8 gcVDebLauncher08[]			= "�   f6:FP Regs      ��   f6:FP Regs      ��   f6:FP Regs      ��   f6:FP Regs      �";
	s8 gcVDebLauncher09[]			= "�   f7:Stack        ��   f7:Stack        ��   f7:Stack        ��   f7:Stack        �";
	s8 gcVDebLauncher10[]			= "�   f8:Watch Window ��   f8:Watch Window ��   f8:Watch Window ��   f8:Watch Window �";
	s8 gcVDebLauncher11[]			= "�   f9:Hover Window ��   f9:Hover Window ��   f9:Hover Window ��   f9:Hover Window �";
	s8 gcVDebLauncher12[]			= "�  f10:Locals       ��  f10:Locals       ��  f10:Locals       ��  f10:Locals       �";
	s8 gcVDebLauncher13[]			= "�  f11:Autos        ��  f11:Autos        ��  f11:Autos        ��  f11:Autos        �";
	s8 gcVDebLauncher14[]			= "�  f12:Timers       ��  f12:Timers       ��  f12:Timers       ��  f12:Timers       �";
	s8 gcVDebLauncher15[]			= "�                   ��                   ��                   ��                   �";
	s8 gcVDebLauncher16[]			= "�  ^f5:Memory       ��  ^f5:Memory       ��  ^f5:Memory       ��  ^f5:Memory       �";
	s8 gcVDebLauncher17[]			= "�  ^f6:Programs     ��  ^f6:Programs     ��  ^f6:Programs     ��  ^f6:Programs     �";
	s8 gcVDebLauncher18[]			= "�  ^f7:Threads      ��  ^f7:Threads      ��  ^f7:Threads      ��  ^f7:Threads      �";
	s8 gcVDebLauncher19[]			= "�������������������ʼ�������������������ʼ�������������������ʼ�������������������ʼ";


	u64 iBuildNewScreen_VDebLauncher(u64 tnUniqueId)
	{
		u64			lisw, lnOssWindowId, lnScreen;
		SScreen*	ls;
		SCanvas*	lc;
		s32			lnFontWidth, lnFontHeight, lnFontSkip, lnTop;
		SCallbacksW	lsCallbacks;
		u32			foreColor, backColor;


		// Initialize memory variables
		lnFontWidth		= 8;
		lnFontHeight	= -16;
		lnFontSkip		= 16;
		lnTop			= -16;
		foreColor		= rgba(0,255,0,255);
		backColor		= rgba(0,0,0,255);

		// Callbacks for the ASCII screen
		iInitializeCallbacksToNull(&lsCallbacks);
		lsCallbacks.keyboard._callback_down = (u64)&iVDebLauncherCallbackKeyDown;

		// Request a screen
		lisw		= iBuildScreen(	tnUniqueId,
									gcVDebLauncherCaption, sizeof(gcVDebLauncherCaption), 
									0, 0, 
									(sizeof(gcVDebLauncher01) - 1) * lnFontWidth, 
									19 * lnFontSkip, 
									-1, -1, 
									-1, -1, 
									foreColor, backColor, 
									false, true, false, true, true,
									&lsCallbacks);

		ls			= (SScreen*)oss_requestScreen(tnUniqueId, lisw);
		if (!ls)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// We're good
		lnOssWindowId	= ls->ossWindowId;
		lnScreen		= ls->ll.uniqueId;
		lc				= (SCanvas*)oss_requestCanvasForScreen(ls);
		if (!lc)
		{
			vvm_messageBox(tnUniqueId, "Failed to allocate canvas for debugger screen.\nTerminating.", "VDebug Error", false, false, false, false, true);
			// Terminate the thread
			return(0);
		}

		// Draw the initial screen
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher01, sizeof(gcVDebLauncher01) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher02, sizeof(gcVDebLauncher02) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher03, sizeof(gcVDebLauncher03) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher04, sizeof(gcVDebLauncher04) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher05, sizeof(gcVDebLauncher05) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher06, sizeof(gcVDebLauncher06) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher07, sizeof(gcVDebLauncher07) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher08, sizeof(gcVDebLauncher08) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher09, sizeof(gcVDebLauncher09) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher10, sizeof(gcVDebLauncher10) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher11, sizeof(gcVDebLauncher11) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher12, sizeof(gcVDebLauncher12) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher13, sizeof(gcVDebLauncher13) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher14, sizeof(gcVDebLauncher14) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher15, sizeof(gcVDebLauncher15) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher16, sizeof(gcVDebLauncher16) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher17, sizeof(gcVDebLauncher17) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher18, sizeof(gcVDebLauncher18) - 1, foreColor, backColor);
		oss_canvasDrawFixedPointText(lc, lc->bd, lnFontWidth, lnFontHeight, 0, (lnTop += lnFontSkip), gcVDebLauncher19, sizeof(gcVDebLauncher19) - 1, foreColor, backColor);
		//vvm_canvasBitBlt(lc, false, 0, 0, lc->width, lc->height, lc, true, 0, 0, lc->width, lc->height);
		oss_canvasRefresh(lc);

		// We're good
		return 0;
	}

	void CALLTYPE iVDebLauncherCallbackKeyDown(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
	{
		switch (tnKey)
		{
			case VVM_F1:
				iBuildNewScreen_AsciiChart(tnUniqueId);
				break;

			case VVM_F2:
				iBuildNewScreen_Scratch(tnUniqueId);
				break;

			case VVM_F3:
				iBuildNewScreen_ProgramRegisters(tnUniqueId);
				break;

			case VVM_F4:
				iBuildNewScreen_ControlRegisters(tnUniqueId);
				break;

			case VVM_F5:
				if (tnKeyFlags & VVMOSS_KEYBOARD_CONTROL)
					iBuildNewScreen_IntegerRegisters(tnUniqueId);
			else
					iBuildNewScreen_Memory(tnUniqueId);
				break;

			case VVM_F6:
				if (tnKeyFlags & VVMOSS_KEYBOARD_CONTROL)
					iBuildNewScreen_Programs(tnUniqueId);
				else
					iBuildNewScreen_FloatingPointRegisters(tnUniqueId);
				break;

			case VVM_F7:
				if (tnKeyFlags & VVMOSS_KEYBOARD_CONTROL)
					iBuildNewScreen_Stack(tnUniqueId);
				else
					iBuildNewScreen_Threads(tnUniqueId);
				break;

			case VVM_F8:
				iBuildNewScreen_Watch(tnUniqueId);
				break;

			case VVM_F9:
				iBuildNewScreen_Hover(tnUniqueId);
				break;

			case VVM_F10:
				iBuildNewScreen_Locals(tnUniqueId);
				break;

			case VVM_F11:
				iBuildNewScreen_Autos(tnUniqueId);
				break;

			case VVM_F12:
				iBuildNewScreen_Timers(tnUniqueId);
				break;

			default:
				// Unknown key
				return;
		}
		// Restore focus on this window
		oss_setFocus(tisw->screenId);
	}
