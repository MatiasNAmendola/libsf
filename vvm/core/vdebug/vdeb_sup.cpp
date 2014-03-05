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
//		SBxml* bxmlScreen;
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
// ˜ֽֽֽֽֽֽֽֽֽÝRegs.1Þֽֽֽֽֽֽֽֽ»
//    SNIP תתתתתתתת:תתתתתתתת  ÷
//      IP תתתתתתתת:תתתתתתתת  ÷
//      SP תתתתתתתת:תתתתתתתת  ÷
//      BP תתתתתתתת:תתתתתתתת  ÷
//    PRED תתתתתתתת:תתתתתתתת  ÷
//            COUNT תת        ÷
//  RESULT תתתתתתתת:תתתתתתתת  ÷
//  EXSNIP תתתתתתתת:Xxx       ÷
//   ERROR תתתתתתתת:תתתתתתתת  ÷
//   FLAGS תתתתתתתת:תתתתתתתת  ÷
//     תתתת-תתתת-תתתת-תתתת    ÷
//     תתתת-תתתת-תתתת-תתתת    ÷
//     תתתת-תתתת-תתתת-תתתת    ÷
//     תתתת-תתתת-תתתת-תתתת    ÷
//       ov? cy? ab? app?     ÷
//       un? eq? be?          ÷

	void ivdeb_updateRegs1(SThread* th)
	{
		u8		lcSnippet[32];
		u8		lcBuffer1[32];
		u8		lcBuffer2[32];


		// Get the snippet number in dot form
// TODO: ivdeb_lookupSnippetName(th->regs.snip, lcSnippet, 17);
		sprintf(gsRegs1.line1,	"  SNIP %s\0",			ivdeb_getU64WithSpaceAndDots(th->regs.snip,			lcSnippet));
		sprintf(gsRegs1.line2,	"    IP %s\0",			ivdeb_getU64WithSpaceAndDots(th->regs.ip,			lcBuffer1));
		sprintf(gsRegs1.line3,	"    SP %s\0",			ivdeb_getU64WithSpaceAndDots(th->regs.sp,			lcBuffer1));
		sprintf(gsRegs1.line4,	"    BP %s\0",			ivdeb_getU64WithSpaceAndDots(th->regs.bp,			lcBuffer1));
		sprintf(gsRegs1.line5,	"  PRED %s\0",			ivdeb_getU64WithSpaceAndDots(th->regs.pred,			lcBuffer1));
		sprintf(gsRegs1.line6,	"          COUNT %s\0",	ivdeb_getU8WithSpaceAndDots((u8)th->regs.predCount,	lcBuffer1));
		sprintf(gsRegs1.line7,	"RESULT %s\0",			ivdeb_getU64WithSpaceAndDots(th->regs.result,		lcBuffer1));
		sprintf(gsRegs1.line8,	"EXSNIP %s\0",			ivdeb_getU64WithSpaceAndDots(th->regs.exsnip,		lcBuffer1));
		sprintf(gsRegs1.line9,	" ERROR %s\0",			ivdeb_getU64WithSpaceAndDots(th->regs.error,		lcBuffer1));
		sprintf(gsRegs1.line10,	" FLAGS %s\0",			ivdeb_getU64WithSpaceAndDots(th->regs._flags,		lcBuffer1));
		sprintf(gsRegs1.line11,	"   %s\0",				ivdeb_getU16AsBinaryWithSpaceAndDots((u16)((th->regs._flags & 0xffff000000000000) >> 48),		lcBuffer1));
		sprintf(gsRegs1.line12,	"   %s\0",				ivdeb_getU16AsBinaryWithSpaceAndDots((u16)((th->regs._flags & 0x0000ffff00000000) >> 32),		lcBuffer1));
		sprintf(gsRegs1.line13,	"   %s\0",				ivdeb_getU16AsBinaryWithSpaceAndDots((u16)((th->regs._flags & 0x00000000ffff0000) >> 16),		lcBuffer1));
		sprintf(gsRegs1.line14,	"   %s\0",				ivdeb_getU16AsBinaryWithSpaceAndDots((u16)((th->regs._flags & 0x000000000000ffff) >> 0),		lcBuffer1));
		ivdeb_getFlags(th->regs.flags, lcBuffer1, lcBuffer2);
		sprintf(gsRegs1.line15,	" %s\0",				lcBuffer1);
		sprintf(gsRegs1.line16,	" %s\0",				lcBuffer2);
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




//////////
//
// Returns 00000000:00000000 in hexadecimal with dots for all leading 0s
//
//////
	u8* ivdeb_getU64WithSpaceAndDots(u64 tnValue, u8* buffer)
	{
		u8		lc0;
		bool	llLeadingZeros;
		u32		lnI, lnJ;
		u64		lnMask, lnShifter;


		//////////
		// Iterate through two 32-bit nibbles
		//////
			llLeadingZeros	= true;
			lnMask			= 0xf000000000000000;
			lnShifter		= 60;
			for (lnJ = 0; lnJ < 2; lnJ++)
			{
				// Iterate for this 32-bit segment
				for (lnI = 0; lnI < 8; lnI++, lnShifter -= 4, lnMask >>= 4)
				{
					// Grab this nibble and convert to hexadecimal
					lc0			= (u8)((tnValue & lnMask) >> lnShifter);
					lc0			= ((lc0 > 10)						? 'a' + lc0 - 10	: '0' + lc0);
					buffer[1]	= ((llLeadingZeros && lc0 == '0')	? 250				: lc0);

					// Are we still displaying leading zeros?
					if (lc0 != 0)
						llLeadingZeros = false;
				}
			}

		// All done
		return(buffer);
	}




//////////
//
// Returns 00 in hexadecimal with dots for all leading 0s
//
//////
	u8* ivdeb_getU8WithSpaceAndDots(u8 tnValue, u8* buffer)
	{
		u8 lc0, lc1;


		//////////
		// Extract out the nibbles
		//////
			lc0 = ((tnValue & 0xf0) >> 8);
			lc1 =  (tnValue & 0x0f);


		//////////
		// Convert to hexadecimal
		//////
			lc0 = ((lc0 > 10) ? 'a' + lc0 - 10 : '0' + lc0);
			lc1 = ((lc1 > 10) ? 'a' + lc1 - 10 : '0' + lc1);
			buffer[0] = ((lc0 == '0')               ? 250 : lc0);
			buffer[1] = ((lc1 == '0' && lc1 == '0') ? 250 : lc1);


		//////////
		// All done
		//////
			return(buffer);
	}




//////////
//
// Returns 16-bits broken out as 0000-0000-0000-0000 in binary with dots for all 0s
//
//////
	u8* ivdeb_getU16AsBinaryWithSpaceAndDots(u16 tnBits, u8* buffer)
	{
		u32 lnI, lnJ, lnMask;


		//////////
		// Iterate through all 16 bits, storing in the format
		//////
			// Iterate for four 4-bit blocks
			for (lnMask = 0x8000, lnI = 0; lnI < 4; lnI++)
			{
				// Repeat for the next four bits
				for (lnJ = 0; lnJ < 4; lnJ++, lnMask >>= 1)
				{
					// Stick a 1 in there, or a dot
					buffer[(lnI * 4) + lnJ] = ((tnBits & lnMask) ? '1' : 250);
				}

				// Store the nibble divider
				buffer[(lnI * 4) + lnJ] = '-';
			}

		// All done
		return(buffer);
	}




//////////
//
// Returns:
//                11111111112222
//      012345678901234567890123
//     " sus   co=a  1234  step "
//     " pend  zu+-  5678  error"
//
//////
	void ivdeb_getFlags(SFlags flags, u8* line1, u8* line2)
	{
		//////////
		// Line 1
		//////
			memcpy(&line1[1], ((flags._is_suspended) ? "sus" : "   "), 3);

			line1[7]	= ((flags._carry)		? 'C'	: 250);
			line1[8]	= ((flags._overflow)	? 'O'	: 250);
			line1[9]	= ((flags._equal)		? '='	: 250);
			line1[10]	= ((flags._app)			? 'A'	: 250);

			line1[13]	= ((flags._app1)		? '1'	: 250);
			line1[14]	= ((flags._app2)		? '2'	: 250);
			line1[15]	= ((flags._app3)		? '3'	: 250);
			line1[16]	= ((flags._app4)		? '4'	: 250);

			memcpy(&line1[19], ((flags._single_step) ? "step" : "    "), 4);


		//////////
		// Line 2
		//////
			memcpy(&line2[1], ((flags._is_suspended) ? "pend" : "    "), 4);

			line2[7]	= ((flags._zero)		? 'Z'	: 250);
			line2[8]	= ((flags._underflow)	? 'U'	: 250);
			line2[9]	= ((flags._positive)	? '+'	: 250);
			line2[10]	= ((flags._negative)	? '-'	: 250);

			line2[13]	= ((flags._app5)		? '5'	: 250);
			line2[14]	= ((flags._app6)		? '6'	: 250);
			line2[15]	= ((flags._app7)		? '7'	: 250);
			line2[16]	= ((flags._app8)		? '8'	: 250);

			memcpy(&line2[19], ((flags._in_error) ? "error" : "     "), 5);
	}
