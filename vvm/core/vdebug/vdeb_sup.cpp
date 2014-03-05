//////////
//
// /libsf/VDebug/VDebug/vdeb_support.cpp
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.25.2014
//////
// Change log:
//     Feb.25.2014 - Development on 0.70 begins
//     Nov.07.2012 - 0.60 development begins
//     Sep.29.2012 - PBL v1.0 license included directly in source files.
//     Sep.28.2012 - Initial creation
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
// Template keyboard processor
//
//////
	void CALLTYPE iVDebLauncherCallbackKeyDown(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
	{
		switch (tnKey)
		{
			case VVM_F1:
				break;

			case VVM_F2:
				break;

			case VVM_F3:
				break;

			case VVM_F4:
				break;

			case VVM_F5:
				break;

			case VVM_F6:
				break;

			case VVM_F7:
				break;

			case VVM_F8:
				break;

			case VVM_F9:
				break;

			case VVM_F10:
				break;

			case VVM_F11:
				break;

			case VVM_F12:
				break;

			default:
				// Unknown key
				return;
		}
	}




//////////
//
// Called to create the initial debugger screen environment based on the indicated layout
//
//////
	SBxml* ivdeb_debuggerScreensCreate(SBxml* bxml)
	{
		SBxml* bxmlScreen;
		return(NULL);
	}




//////////
//
// Deletes the previous screens created
//
//////
	void ivdeb_debuggerScreensDelete(SBxml* bxml)
	{
	}




//////////
//
// Update the Locals.1 window source data
//
//////
	void ivdeb_updateLocal1(SThread* th)
	{
	}




//////////
//
// Update the Locals.2 window source data
//
//////
	void ivdeb_updateLocal2(SThread* th)
	{
	}




//////////
//
// Update the Locals.3 window source data
//
//////
	void ivdeb_updateLocal3(SThread* th)
	{
	}




//////////
//
// Update the Regs.1 window source data
//
//////
// 	struct SThread
// 	{
// 		SLL				ll;						// 2-way link list
// 		SThreadControl	status;					// Status of this thread
// 
// 		// Thread variables
// 		SDatum			stack;					// Pointer to the stack's data block
// 		SRegs			regs;					// Pointer to the registers for the VM
// 
// 		// For the local thread, individual timers which interrupt the current thread for execution
// 		SStartEnd		_timers;				// Pointer to the list of STimer entries (if any)
// 		SStartEnd		_globals;				// Pointer to thread-specific global variables
// 
// 		// For the current snippet:
// 		SSnipExec*		current;				// Shortcut pointer to the currently executing snippet
// 		SStartEnd		snippet;				// Pointer to the list of SSnippet entries in the program chain from main (levels down, SSnipExec structure)
// 	};
	void ivdeb_updateRegs1(SThread* th)
	{
		s8		lcSnippet[32];


		// Get the snippet number in dot form
// TODO: ivdeb_lookupSnippetName(th->regs.snip, lcSnippet, 17);
		sprintf(gsRegs1.line1, "  SNIP %s\0",				ivdeb_getU64WithSpaceAndDots(th->regs.snip, lcSnippet));

// 		ivdeb_getU64WithSpaceAndDots(th->regs.snip, buffer1);
// 		ivdeb_lookupSnippetName(th->regs.snip, buffer2, 10);
	}

	s8* ivdeb_getU64WithSpaceAndDots(u64 tnValue, s8* buffer)
	{
// TODO:  working here
		return(NULL);
	}




//////////
//
// Update the Int.1 window source data
//
//////
	void ivdeb_updateInt1(SThread* th)
	{
	}




//////////
//
// Update the Float.1 window source data
//
//////
	void ivdeb_updateFloat1(SThread* th)
	{
	}




//////////
//
// Update the CFSCA.1 window source data
//
//////
	void ivdeb_updateCFSCA1(SThread* th)
	{
	}




//////////
//
// Update the Ready.3 window source data
//
//////
	void ivdeb_updateReady3(SThread* th)
	{
	}




//////////
//
// Update the Memory.1 window source data
//
//////
	void ivdeb_updateMemory1(SThread* th)
	{
	}




//////////
//
// Update the Memory.2 window source data
//
//////
	void ivdeb_updateMemory2(SThread* th)
	{
	}




//////////
//
// Update the Memory.3 window source data
//
//////
	void ivdeb_updateMemory3(SThread* th)
	{
	}




//////////
//
// Update the Watch.3 window source data
//
//////
	void ivdeb_updateWatch3(SThread* th)
	{
	}




//////////
//
// Update the Autos.3 window source data
//
//////
	void ivdeb_updateAutos3(SThread* th)
	{
	}




//////////
//
// Update the Stack.1 window source data
//
//////
	void ivdeb_updateStack1(SThread* th)
	{
	}




//////////
//
// Update the Hover.2 window source data
//
//////
	void ivdeb_updateHover2(SThread* th)
	{
	}




//////////
//
// Update the Timer.2 window source data
//
//////
	void ivdeb_updateTimer2(SThread* th)
	{
	}




//////////
//
// Update the Programs.2 window source data
//
//////
	void ivdeb_updatePrograms2(SThread* th)
	{
	}




//////////
//
// Update the Threads.2 window source data
//
//////
	void ivdeb_updateThreads2(SThread* th)
	{
	}
