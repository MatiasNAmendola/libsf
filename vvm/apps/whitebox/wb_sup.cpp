//////////
//
// /libsf/vvm/apps/whitebox/wb_sup.cpp
//
//////
// Version 0.10
// Copyright (c) 2013 by Rick C. Hodgin
//////
// Last update:
//     April 29, 2013
//////
// Change log:
//     April 29, 2013 - Initial creation
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
// Test code, builds various screen forms to try out features
//
/////
	SOssWindow* iwb_buildScreenTemplate(u64 tnUniqueId,
										s8* tcCaption, u32 tnCaptionLength,
										u32 tnX, u32 tnY,
										u32 tnWidth, u32 tnHeight,
										u32 tnWidthMin, u32 tnHeightMin,
										u32 tnWidthMax, u32 tnHeightMax,
										SBGRA foreColor, SBGRA backColor,
										bool tlResizable, bool tlMovable, bool tlClosable, bool tlVisible, bool tlBorder,
										SCallbacksW* screenCallbacks	)
	{
		SOssWindow* lisw;


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
											screenCallbacks);

// TODO:  Append the unique ID on here to the caption if there is more than one instance running
		// All done
		return(lisw);
	}




//////////
//
// Set the callbacks to an empty/null state
//
//////
	void iwb_initializeCallbacks(SCallbacksW* tcbw, SCallbacks* tcb)
	{
		if (tcbw)		memset(tcbw, 0, sizeof(SCallbacksW));
		if (tcb)		memset(tcb,  0, sizeof(SCallbacks));
	}




//////////
//
// White Box main screen designer
//
//////
	bool iwb_buildNewMainScreen(u64 tnUniqueId, SWBScreen* tsWbScreen)
	{
		//////////
		// Physically build the screen
		//////
			if (!iiwb_createScreenCanvas(tnUniqueId, 848, 480, &tsWbScreen->screen, &tsWbScreen->screenCallbacks, &tsWbScreen->canvas, &tsWbScreen->canvasCallbacks))
				return(false);	// Failure allocating OS window, or screen or canvas


		//////////
		// Logically define regions and sub-canvases within
		//////
			if (!iiwb_createMainRegions(tsWbScreen->canvas))
				return(false);	// Failure creating sub-regions within


		//////////
		// Update the OS window so it repaints itself
		//////
			oss_screenRefresh(tsWbScreen->screen);

		// We're good
		return(true);
	}




//////////
//
// White Box media screen designer
//
//////
	bool iwb_buildNewMediaScreen(u64 tnUniqueId, SWBScreen* tsWbScreen)
	{
		//////////
		// Physically build the screen
		//////
			if (!iiwb_createScreenCanvas(tnUniqueId, 212, 480, &tsWbScreen->screen, &tsWbScreen->screenCallbacks, &tsWbScreen->canvas, &tsWbScreen->canvasCallbacks))
				return(false);	// Failure allocating OS window, or screen or canvas


		//////////
		// Logically define regions and sub-canvases within
		//////
			if (!iiwb_createMediaRegions(tsWbScreen->canvas))
				return(false);	// Failure creating sub-regions within


		//////////
		// Update the OS window
		//////
			oss_screenRefresh(tsWbScreen->screen);

		// We're good
		return(true);
	}




//////////
//
// White Box channel screen designer
//
//////
	bool iwb_buildNewChannelScreen(u64 tnUniqueId, SWBScreen* tsWbScreen)
	{
		//////////
		// Physically build the screen
		//////
			if (!iiwb_createScreenCanvas(tnUniqueId, 848, 160, &tsWbScreen->screen, &tsWbScreen->screenCallbacks, &tsWbScreen->canvas, &tsWbScreen->canvasCallbacks))
				return(false);	// Failure allocating OS window, or screen or canvas


		//////////
		// Logically define regions and sub-canvases within
		//////
			if (!iiwb_createChannelRegions(tsWbScreen->canvas))
				return(false);	// Failure creating sub-regions within


		//////////
		// Update the OS window
		//////
			oss_screenRefresh(tsWbScreen->screen);

		// We're good
		return(true);
	}




//////////
//
// Called to define the standard WhiteBox regions on two screens, the main and media, which
// remain in relative position to each other, but are separate screens.
//		 __________________________________________________________________   ___ ___ ___ ___
//		|                                                                  | |               |
//		|                                                                  | |               |
//		|                                                                  | |               |
//		|                                                                  | |               |
//		|                                                                  | |               |
//		|                              main                                | |     media     |
//		|                                                                  | |               |
//		|                                                                  | |               |
//		|                                                                  | |               |
//		|                                                                  | |               |
//		|                                                                  | |               |
//		|__________________________________________________________________| |_______________|
//
// The main screen is divided into four base regions, left, video, right, lines; and the
// media window is divided into icons, and preview; and the channels window into an extended
// lines area:
//		 __________________________________________________________________   ___ ___ ___ ___
//		|        |                                                |        | |               |
//		|        |                                                |        | |               |
//		|        |                                                |        | |               |
//		|  left  |                     video                      | right  | |     icons     |
//		|        |                                                |        | |               |
//		|        |                                                |        | |               |
//		|        |                                                |        | |               |
//		|________|________________________________________________|________| |_______________|
//		|                                                                  | |               |
//		|                              lines                               | |    content    |
//		|                                                                  | |               |
//		|__________________________________________________________________| |_______________|
//		 __________________________________________________________________ 
//		|                             channels                             |
//		|__________________________________________________________________|
//
//
// The four base regions on the main window are then divided into sub-regions, (upper-left),
// (right), (video upper-left, video upper-right, video lower-left, video lower-right),
// (timeline), (video), (audio), and (edits); with the media window being divided into
// (icons), (preview), and (controls); with the channels window becoming two additional
// edit lines (edit1), and (edit2):
//		 __________________________________________________________________   ___ ___ ___ ___
//		| upper ||                       ||                       ||       | |               |
//		|  left ||      video ul         ||       video ur        ||       | |               |
//		|_______||                       ||                       ||       | |               |
//		|       ||_______________________||_______________________|| right | |     icons     |
//		|       ||                       ||                       ||       | |               |
//		|       ||      video ll         ||       video lr        ||       | |               |
//		|       ||                       ||                       ||       | |               |
//		|       ||_______________________||_______________________||_______| |_______________|
//		|_____________________________timeline_____________________________| |               |
//		|_______________________________video______________________________| |    preview    |
//		|_______________________________audio______________________________| |_______________|
//		|_______________________________edits______________________________| |____controls___|
//		 __________________________________________________________________ 
//		|_______________________________edit1______________________________|
//		|_______________________________edit2______________________________|
//
//
// And ultimately, each sub-region is divided into component rectangles of 53x40 pixels,
// which are displayed as icons:
//		 ___ ___  ___ ___ ___ ___ ___ ___  ___ ___ ___ ___ ___ ___  ___ ___   ___ ___ ___ ___
//		|       ||                       ||                       ||       | |___|___|___|___|
//		|_______||                       ||                       ||       | |___|___|___|___|
//		|       ||                       ||                       ||       | |___|___|___|___|
//		|       ||_______________________||_______________________||       | |___|___|___|___|
//		|       ||                       ||                       ||       | |___|___|___|___|
//		|       ||                       ||                       ||       | |___|___|___|___|
//		|       ||                       ||                       ||       | |___|___|___|___|
//		|       ||_______________________||_______________________||_______| |___|___|___|___|
//		|__________________________________________________________________| |___|___|___|___|
//		|___|___||________________________________________________||___|___| |               |
//		|___|___||________________________________________________||___|___| |_______________|
//		|___|___||________________________________________________||___|___| |___|___|___|___|
//		 ___ ___  ________________________________________________  ___ ___ 
//		|___|___||________________________________________________||___|___|
//		|___|___||________________________________________________||___|___|

//		 ___ ___  ___ ___ ___ ___ ___ ___  ___ ___ ___ ___ ___ ___  ___ ___   ___ ___ ___ ___
//		|___|___||___|___|___|___|___|___||___|___|___|___|___|___||___|___| |___|___|___|___|
//		|___|___||___|___|___|___|___|___||___|___|___|___|___|___||___|___| |___|___|___|___|
//		|___|___||___|___|___|___|___|___||___|___|___|___|___|___||___|___| |___|___|___|___|
//		|___|___||___|___|___|___|___|___||___|___|___|___|___|___||___|___| |___|___|___|___|
//		|___|___||___|___|___|___|___|___||___|___|___|___|___|___||___|___| |___|___|___|___|
//		|___|___||___|___|___|___|___|___||___|___|___|___|___|___||___|___| |___|___|___|___|
//		|___|___||___|___|___|___|___|___||___|___|___|___|___|___||___|___| |___|___|___|___|
//		|___|___||___|___|___|___|___|___||___|___|___|___|___|___||___|___| |___|___|___|___|
//		|___|___||________________________________________________||___|___| |               |
//		|___|___||________________________________________________||___|___| |               |
//		|___|___||________________________________________________||___|___| |_______________|
//		|___|___||________________________________________________||___|___| |___|___|___|___|
//		 ___ ___  ________________________________________________  ___ ___ 
//		|___|___||________________________________________________||___|___|
//		|___|___||________________________________________________||___|___|
//
//////
	bool iiwb_createMainRegions(SCanvas* canvas)
	{
// TODO:  working here
		return(false);
	}

	bool iiwb_createMediaRegions(SCanvas* canvas)
	{
		return(false);
	}

	bool iiwb_createChannelRegions(SCanvas* canvas)
	{
		return(false);
	}




//////////
//
// Build the physical OS-layer window, and VVM-layer screen and canvas
//
//////
	bool iiwb_createScreenCanvas(u64 tnUniqueId, u32 tnWidth, u32 tnHeight, SScreen** tsScreen, SCallbacksW* screenCallbacks, SCanvas** tsCanvas, SCallbacks* canvasCallbacks)
	{
		SOssWindow*	lisw;
		u64			lnScreen;
		SBGRA 		foreColor, backColor;
		SScreen*	ls;
		SCanvas*	lc;


		//////////
		// Initialize memory variables
		//////
			foreColor.color	= rgba(0,0,0,255);
			backColor.color	= rgba(255,255,255,255);
			*tsScreen		= NULL;
			*tsCanvas		= NULL;


		//////////
		// Callbacks for the screen
		//////
			iwb_initializeCallbacks(screenCallbacks, canvasCallbacks);
			screenCallbacks->keyboard._callback_down = (u64)&iwb_callbackKeyDown;


		//////////
		// Request a screen
		//////
			// Allocate a screen
			lisw = iwb_buildScreenTemplate(	oss_getNextUniqueId(), 
											gcWhiteBoxLauncherCaption, sizeof(gcWhiteBoxLauncherCaption),
											0, 0, tnWidth, tnHeight, 
											-1, -1, 
											-1, -1, 
											foreColor, backColor,
											false, true, false, true, true,
											screenCallbacks	);

			// If we have a screen structure, create it
			if (lisw)
			{
				ls = oss_createScreenAndVisibleWindow(tnUniqueId, lisw);
				if (ls)
				{
					// Request a canvas for it
					lnScreen	= ls->ll.uniqueId;
					lc			= oss_createCanvasForScreen(ls);
				}
			}

			// Report any errors
			if (!lisw || !ls || !lc)
			{
				vvm_messageBox(tnUniqueId, "Failed to allocate primary screen.\nTerminating.", "White Box Error", false, false, false, false, true);
				// Terminate the thread
				return(false);
			}
			// If we get here, we're good, we have a screen and a canvas


		//////////
		// Store our pointers
		//////
			*tsScreen = ls;
			*tsCanvas = lc;


		// Success
		return(true);
	}
