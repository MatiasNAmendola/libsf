//////////
//
// /libsf/source/vjr/events.cpp
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jul.04.2014
//////
// Change log:
//     Jul.04.2014 - Initial creation
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




void iEvents_resetToDefault(SEvents* ev)
{
	SEventsGeneral*		g;
	SEventsMouse*		m;
	SEventsKeyboard*	k;


	// Make sure our environment is sane
	if (ev)
	{
		//////////
		// Grab our events
		//////
			g = &ev->general;
			m = &ev->mouse;
			k = &ev->keyboard;


		//////////
		// Reset general events
		//////
			*(u32*)&g->onLoad			= (u32)&iDefaultCallback_onLoad;
			*(u32*)&g->onInit			= (u32)&iDefaultCallback_onInit;
			*(u32*)&g->onCreated		= (u32)&iDefaultCallback_onCreated;
			*(u32*)&g->onResize			= (u32)&iDefaultCallback_onResize;
			*(u32*)&g->onMoved			= (u32)&iDefaultCallback_onMoved;
			*(u32*)&g->onRender			= (u32)&iDefaultCallback_onRender;
			*(u32*)&g->onPublish		= (u32)&iDefaultCallback_onPublish;
			*(u32*)&g->onQueryUnload	= (u32)&iDefaultCallback_onQueryUnload;
			*(u32*)&g->onDestroy		= (u32)&iDefaultCallback_onDestroy;
			*(u32*)&g->onUnload			= (u32)&iDefaultCallback_onUnload;
			*(u32*)&g->onGotFocus		= (u32)&iDefaultCallback_onGotFocus;
			*(u32*)&g->onLostFocus		= (u32)&iDefaultCallback_onLostFocus;
			*(u32*)&g->onAddObject		= (u32)&iDefaultCallback_onAddObject;
			*(u32*)&g->onAddProperty	= (u32)&iDefaultCallback_onAddProperty;
			*(u32*)&g->onError			= (u32)&iDefaultCallback_onError;
			*(u32*)&g->onScrolled		= (u32)&iDefaultCallback_onScrolled;


		//////////
		// Reset mouse events
		//////
			*(u32*)&m->onMouseClickEx	= (u32)&iDefaultCallback_onMouseClickEx;
			*(u32*)&m->onMouseWheel		= (u32)&iDefaultCallback_onMouseWheel;
			*(u32*)&m->onMouseMove		= (u32)&iDefaultCallback_onMouseMove;
			*(u32*)&m->onMouseDown		= (u32)&iDefaultCallback_onMouseDown;
			*(u32*)&m->onMouseUp		= (u32)&iDefaultCallback_onMouseUp;
			*(u32*)&m->onMouseEnter		= (u32)&iDefaultCallback_onMouseEnter;
			*(u32*)&m->onMouseLeave		= (u32)&iDefaultCallback_onMouseLeave;
			*(u32*)&m->onMouseHover		= (u32)&iDefaultCallback_onMouseHover;


		//////////
		// Reset keyboard events
		//////
			*(u32*)&k->onKeyDown		= (u32)&iDefaultCallback_onKeyDown;
			*(u32*)&k->onKeyUp			= (u32)&iDefaultCallback_onKeyUp;
	}
}