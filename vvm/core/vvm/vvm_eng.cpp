//////////
//
// /libsf/vvm/vvm/vvm_eng.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     October 05, 2012 - Initial creation
//     October 05, 2012 - PBL v1.0 license included directly in source files.
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
// Initializes the VVM to its power-on state.
// Processes any load commands found on the command line.
//
//////
	bool ivvme_initialize(LPWSTR tcCmdLine, bool* tlTestCasesOnly)
	{
		bool		llResult;
		SProgram*	lp;


// TODO:  load the command line bxml file to run (if any), also observing the rules / requirements of being in test-case only mode
		// Initially indicate failure
		llResult = false;


		// Create the base VVM state
		lp = (SProgram*)vvm1_SEChain_append(&gsVvm.gseRootPrograms, vvm1_getNextUniqueId(), vvm1_getNextUniqueId(), sizeof(SProgram), 1, NULL);


		// Enter a loop so we can break out
		while (lp)
		{
			// Reset the structure to its default state, which will also allocate sub-structures (see OBED.txt definition)
			llResult = ivvm_initializeProgram(lp);
			if (!llResult)
				break;		// Failed to initialize the system with the base program


			// Start the thread mizer
			llResult = ivvmtm_initialize();
			if (!llResult)
				break;		// Failed to initialize the thread mizer


			// When we get here, we're successful
			break;
		}


		// See if the command line contains the "-test" option
		if (tlTestCasesOnly && vvm1_isNeedleInHaystack_Unicode(tcCmdLine, L"-test"))
			*tlTestCasesOnly = true;	// Raise the flag

		// Indicate our success or failure
		return(llResult);
	}
/*
 * Note:  Used for internal debugging only!
 *        Can be used to verify that the gnVvmMachineOpcodeHandlers table was setup correctly
 *
		u32 lnI;
		union {
			u32		_address;
			void	(*opcodeHandler) (void);
		};
		for (lnI = 0; lnI < sizeof(gnVvmMachineOpodeHandlers) / sizeof(u32); lnI++)
		{
			_address = gnVvmMachineOpodeHandlers[lnI];
			opcodeHandler();	// in vvm_eng.cpp
		}
 *
 */




//////////
//
// Called to execute the specified thread for (at least) the number of ticks.  It is said "at least"
// because some operations may push beyond the indicated number, but at the next instruction above
// the indicated number of ticks, execution will cease.
//
// To determine if the ticks have passed:
//		- Compare that 64-bit value at *gsSysInfo.addressOf1MsTickCount to tt->status.startTick
//		- If difference is greater than tnTicks, this thread execution cycle is done
//
//////
	void ivvme_executeThread(SThread* tt, u64 tnTicks)
	{
		// Make sure the machine state is valid, must be:
		//	1) currently set to a valid snippet or dynamic snippet
		//	2) not in error
		//	3) not suspended
		//	4) ip must be valid for snippet or dynamic snippet
		if (tt->current && 
			!tt->regs.flags._in_error && 
			!tt->regs.flags._is_suspended)
		{
			// Execute this snippet
			ivvme_executeThreadSnippet(tt, tnTicks, tt->current->snip);
		}
		return;
	}




//////////
//
// Called to execute the specified snippet
//
//////
	void ivvme_executeThreadSnippet(SThread* tt, u64 tnTicks, SSnip* ts)
	{
		_ivvme_executeThreadSnippetData lsed;


		// Make sure the environment is sane
		while (ts)
		{
			if (tt->regs.ip >= ts->machineCode.length)
			{
				// Error, the instruction pointer is pointing beyond the end of the snippet's machine code
				tt->regs.flags._in_error		= true;
				tt->regs.flags._is_suspended	= true;
				return;
			}
			// If we get here, we can (at least) start decoding the instruction


		//////////
		//
		// Opcodes are 12-bit format:
		//   [----][--------]    [--------]    [----]
		//    (1)     (2)          (3:opt)     (4:opt)
		//
		//////
		// 
		//		(1) Predicate
		//		(2) Opcode byte, if 0xff then followed by a 2nd opcode byte
		//		(3) (only if (2) is 0xff) 2nd opcode byte
		//		(4) source information, immediate data, etc, determined by opcode's requirements
		//
		// All instructions are nibble- or byte-aligned in definition, but are byte-aligned for padding.
		//
		//////
			lsed.lid = ts->machineCode.data._u8 + tt->regs.ip;

			// Grab the machine code DWORD (all snippets include NOPs to pad out to at least the next highest DWORD beyond the last instruction executed)
			lsed.lnDecoder	= *(u32*)lsed.lid;

			// Break it out into predicate and opocde
			lsed.lnPredicate	= (lsed.lnDecoder & 0xf0000000) >> 28;
			lsed.lnOpcode		= (lsed.lnDecoder & 0x0ff00000) >> 20;

			// Decode and execute the opcode
			lsed._vvmOpcodeExecute = gnVvmMachineOpodeHandlers[lsed.lnOpcode];
			lsed.vvmOpcodeExecute(&lsed);
		}
		// When we get here, we're done with this snippet, or there's an error
	}


	// OPCODE:0
	// UADD64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_uadd64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:1
	// UADD32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_uadd32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:2
	// UADD16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_uadd16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:3
	// UADD8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_uadd8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:4
	// USUB64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_usub64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:5
	// USUB32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_usub32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:6
	// USUB16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_usub16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:7
	// USUB8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_usub8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:8
	// UMUL64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_umul64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:9
	// UMUL32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_umul32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:10
	// UMUL16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_umul16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:11
	// UMUL8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_umul8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:12
	// UDIV64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_udiv64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:13
	// UDIV32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_udiv32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:14
	// UDIV16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_udiv16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:15
	// UDIV8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_udiv8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:16
	// UCOMP64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_ucomp64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:17
	// UCOMP32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_ucomp32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:18
	// UCOMP16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_ucomp16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:19
	// UCOMP8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_ucomp8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:20
	// SADDF64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_saddf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:21
	// SADDF32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_saddf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:22
	// SADD64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_sadd64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:23
	// SADD32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_sadd32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:24
	// SADD16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_sadd16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:25
	// SADD8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_sadd8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:26
	// SSUBF64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_ssubf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:27
	// SSUBF32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_ssubf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:28
	// SSUB64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_ssub64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:29
	// SSUB32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_ssub32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:30
	// SSUB16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_ssub16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:31
	// SSUB8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_ssub8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:32
	// SMULF64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_smulf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:33
	// SMULF32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_smulf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:34
	// SMUL64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_smul64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:35
	// SMUL32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_smul32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:36
	// SMUL16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_smul16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:37
	// SMUL8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_smul8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:38
	// SDIVF64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_sdivf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:39
	// SDIVF32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_sdivf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:40
	// SDIV64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_sdiv64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:41
	// SDIV32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_sdiv32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:42
	// SDIV16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_sdiv16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:43
	// SDIV8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_sdiv8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:44
	// SCOMPF64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_scompf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:45
	// SCOMPF32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_scompf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:46
	// SCOMP64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_scomp64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:47
	// SCOMP32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_scomp32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:48
	// SCOMP16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_scomp16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:49
	// SCOMP8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_scomp8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:50
	// COPYF64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_copyf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:51
	// COPYF32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_copyf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:52
	// COPY64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_copy64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:53
	// COPY32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_copy32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:54
	// COPY16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_copy16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:55
	// COPY8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_copy8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:56
	// MOVEF64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_movef64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:57
	// MOVEF32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_movef32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:58
	// MOVE64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_move64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:59
	// MOVE32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_move32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:60
	// MOVE16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_move16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:61
	// MOVE8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_move8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:62
	// XCHF64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:63
	// XCHF32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:64
	// XCH64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xch64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:65
	// XCH32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xch32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:66
	// XCH16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xch16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:67
	// XCH8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xch8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:68
	// XCHUADD64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchuadd64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:69
	// XCHUADD32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchuadd32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:70
	// XCHUADD16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchuadd16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:71
	// XCHUADD8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchuadd8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:72
	// XCHUMUL64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchumul64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:73
	// XCHUMUL32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchumul32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:74
	// XCHUMUL16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchumul16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:75
	// XCHUMUL8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchumul8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:76
	// XCHSADDF64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsaddf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:77
	// XCHSADDF32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsaddf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:78
	// XCHSADD64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsadd64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:79
	// XCHSADD32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsadd32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:80
	// XCHSADD16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsadd16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:81
	// XCHSADD8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsadd8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:82
	// XCHSMULF64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsmulf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:83
	// XCHSMULF32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsmulf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:84
	// XCHSMUL64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsmul64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:85
	// XCHSMUL32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsmul32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:86
	// XCHSMUL16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsmul16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:87
	// XCHSMUL8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xchsmul8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:88
	// AND64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_and64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:89
	// AND32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_and32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:90
	// AND16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_and16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:91
	// AND8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_and8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:92
	// OR64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_or64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:93
	// OR32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_or32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:94
	// OR16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_or16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:95
	// OR8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_or8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:96
	// NOT64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_not64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:97
	// NOT32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_not32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:98
	// NOT16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_not16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:99
	// NOT8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_not8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:100
	// XOR64 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xor64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:101
	// XOR32 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xor32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:102
	// XOR16 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xor16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:103
	// XOR8 [SOURCE] TO [SOURCE]
	void ivvme_executeThreadSnippet_xor8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:104
	// CHGSF64 [SOURCE]
	void ivvme_executeThreadSnippet_chgsf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:105
	// CHGSF32 [SOURCE]
	void ivvme_executeThreadSnippet_chgsf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:106
	// NEG64 [SOURCE]
	void ivvme_executeThreadSnippet_neg64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:107
	// NEG32 [SOURCE]
	void ivvme_executeThreadSnippet_neg32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:108
	// NEG16 [SOURCE]
	void ivvme_executeThreadSnippet_neg16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:109
	// NEG8 [SOURCE]
	void ivvme_executeThreadSnippet_neg8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:110
	// INCF64 [SOURCE]
	void ivvme_executeThreadSnippet_incf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:111
	// INCF32 [SOURCE]
	void ivvme_executeThreadSnippet_incf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:112
	// INC64 [SOURCE]
	void ivvme_executeThreadSnippet_inc64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:113
	// INC32 [SOURCE]
	void ivvme_executeThreadSnippet_inc32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:114
	// INC16 [SOURCE]
	void ivvme_executeThreadSnippet_inc16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:115
	// INC8 [SOURCE]
	void ivvme_executeThreadSnippet_inc8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:116
	// DECF64 [SOURCE]
	void ivvme_executeThreadSnippet_decf64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:117
	// DECF32 [SOURCE]
	void ivvme_executeThreadSnippet_decf32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:118
	// DEC64 [SOURCE]
	void ivvme_executeThreadSnippet_dec64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:119
	// DEC32 [SOURCE]
	void ivvme_executeThreadSnippet_dec32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:120
	// DEC16 [SOURCE]
	void ivvme_executeThreadSnippet_dec16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:121
	// DEC8 [SOURCE]
	void ivvme_executeThreadSnippet_dec8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:122
	// SHL64 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shl64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:123
	// SHL32 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shl32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:124
	// SHL16 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shl16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:125
	// SHL8 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shl8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:126
	// SHUR64 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shur64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:127
	// SHUR32 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shur32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:128
	// SHUR16 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shur16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:129
	// SHUR8 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shur8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:130
	// SHSR64 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shsr64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:131
	// SHSR32 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shsr32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:132
	// SHSR16 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shsr16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:133
	// SHSR8 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_shsr8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:134
	// ROL64 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_rol64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:135
	// ROL32 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_rol32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:136
	// ROL16 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_rol16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:137
	// ROL8 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_rol8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:138
	// ROR64 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_ror64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:139
	// ROR32 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_ror32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:140
	// ROR16 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_ror16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:141
	// ROR8 [SOURCE] BY [SOURCE]
	void ivvme_executeThreadSnippet_ror8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:142
	// CNVOBJ [REG] TO VVM TYPE [IMM8]	; TAKES OBJECT TYPE AND CONVERTS TO THE NEW FORMAT SUPPORTED BY THE VVM
	void ivvme_executeThreadSnippet_cnvobj(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:143
	// COPY3232 [FREG32] TO [REG32]
	void ivvme_executeThreadSnippet_copy3232fi(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:144
	// COPY3232 [REG32] TO [FREG32]
	void ivvme_executeThreadSnippet_copy3232if(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:145
	// COPY6464 [FREG64] TO [REG64]
	void ivvme_executeThreadSnippet_copy6464fi(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:146
	// COPY6464 [REG64] TO [FREG64]
	void ivvme_executeThreadSnippet_copy6464if(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:147
	// COPY3264 [FREG32] TO [REG64]
	void ivvme_executeThreadSnippet_copy3264fi(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:148
	// COPY3264 [REG32] TO [FREG64]
	void ivvme_executeThreadSnippet_copy3264if(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:149
	// COPY6432 [FREG64] TO [REG32]
	void ivvme_executeThreadSnippet_copy6432fi(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:150
	// COPY6432 [REG64] TO [FREG32]
	void ivvme_executeThreadSnippet_copy6432if(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:151
	// COPY64 FLAGS TO [SOURCE]
	void ivvme_executeThreadSnippet_copy64fs(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:152
	// COPY64 [SOURCE] TO FLAGS
	void ivvme_executeThreadSnippet_copy64sf(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:153
	// COPY RESULT64 TO [SOURCE]
	void ivvme_executeThreadSnippet_copyresult(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:154
	// ALLOCS [IMM8]					; ALLOCATE SCRATCH SPACE
	void ivvme_executeThreadSnippet_allocs(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:155
	// DEALLOCS [IMM8]					; DEALLOCATE SCRATCH SPACE
	void ivvme_executeThreadSnippet_deallocs(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:156
	// DEBUG						; PAUSES FOR DEBUGGER
	void ivvme_executeThreadSnippet_debug(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:157
	// HALT							; HALTS TIMESLICE EXECUTION UNTIL NEXT SCHEDULING
	void ivvme_executeThreadSnippet_halt(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:158
	// NOP							; USED FOR PADDING
	void ivvme_executeThreadSnippet_nop(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:159
	// LENOBJ						; LENGTH OF OBJECT NUMBER
	void ivvme_executeThreadSnippet_lenobj(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:160
	// NUMOBJA						; NUMBER OF OBJECT ASCII NAME
	void ivvme_executeThreadSnippet_numobja(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:161
	// NUMOBJU						; NUMBER OF OBJECT UNICODE NAME
	void ivvme_executeThreadSnippet_numobju(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:162
	// NUA							; NEXT UNIQUE NAME
	void ivvme_executeThreadSnippet_nua(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:163
	// NUN							; NEXT UNIQUE NUMBER
	void ivvme_executeThreadSnippet_nun(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:164
	// SETIPXS TO [SNIPPET SOURCE] + [OFFSET SOURCE]	; EXPLICIT ADDRESS FROM [SNIPPET NUMBER]'S OFFSET 0
	void ivvme_executeThreadSnippet_setipxs(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:165
	// SETIPX TO [OFFSET SOURCE]		                ; EXPLICIT ADDRESS FROM CURRENT SNIPPET'S OFFSET 0
	void ivvme_executeThreadSnippet_setipx(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:166
	// ADJIP64 [SOURCE]					; ADJUST IP FORWARD/BACKWARD BY SIGNED [SOURCE]
	void ivvme_executeThreadSnippet_adjip64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:167
	// ADJIP32 [SOURCE]					; ADJUST IP FORWARD/BACKWARD BY SIGNED [SOURCE]
	void ivvme_executeThreadSnippet_adjip32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:168
	// ADJIP16 [IMM16]					; ADJUST IP FORWARD/BACKWARD BY SIGNED [IMM16]
	void ivvme_executeThreadSnippet_adjip16(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:169
	// ADJIP8 [IMM8]					; ADJUST IP FORWARD BACKWARD BY SIGNED [IMM8]
	void ivvme_executeThreadSnippet_adjip8(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:170
	// CALLSN [SOURCE]					; CALL SNIPPET NUMBER
	void ivvme_executeThreadSnippet_callsn(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:171
	// CALLSNA [SOURCE]					; CALL SNIPPET NAME ASCII
	void ivvme_executeThreadSnippet_callsna(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:172
	// CALLSNU [SOURCE]					; CALL SNIPPET NAME UNICODE
	void ivvme_executeThreadSnippet_callsnu(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:173
	// CALLDSN [SOURCE]					; CALL DYNAMIC SNIPPET NUMBER
	void ivvme_executeThreadSnippet_callsdn(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:174
	// CALLDSNA [SOURCE]				        ; CALL DYNAMIC SNIPPET NAME ASCII
	void ivvme_executeThreadSnippet_calldsna(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:175
	// CALLDSNU [SOURCE]				        ; CALL DYNAMIC SNIPPET NAME UNICODE
	void ivvme_executeThreadSnippet_calldsnu(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:176
	// CALLHN [SOURCE]					; CALL HOST NUMBER
	void ivvme_executeThreadSnippet_callhn(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:177
	// CALLHNA [SOURCE]					; CALL HOST NAME ASCII (ALL HOST FUNCTIONS ARE ONLY ASCII)
	void ivvme_executeThreadSnippet_callhna(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:178
	// PUSH64 [SOURCE]					; PUSHES 64-BIT QUANTITY ONTO STACK FROM SOURCE
	void ivvme_executeThreadSnippet_push64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:179
	// POP64 [SOURCE]					; POPS 64-BIT QUANTITY BACK OFF STACK INTO SOURCE
	void ivvme_executeThreadSnippet_pop64(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:180
	// PUSH32 [SOURCE]					; PUSHES 32-BIT QUANTITY ONTO STACK FROM SOURCE
	void ivvme_executeThreadSnippet_push32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:181
	// POP32 [SOURCE]					; POPS 32-BIT QUANTITY BACK OFF STACK INTO SOURCE
	void ivvme_executeThreadSnippet_pop32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:182
	// STACKCPY32 [SOURCE][LENGTH][SOURCE]	; COPY STACK [SOURCE] [LENGTH IN DWORDS] TO [DESTINATION]
	void ivvme_executeThreadSnippet_stackcpy32(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:183
	// RETURN						; EXPLICIT RETURN TO IMMEDIATE PARENT, IF AT TOP LEVEL, TERMINATES PROGRAM
	void ivvme_executeThreadSnippet_return(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:184
	// RETTONAM [SOURCE]				        ; RETURN TO SNIPPET NAME IN PARENT LINEAGE
	void ivvme_executeThreadSnippet_rettonam(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:185
	// RETTONUM [SOURCE]				        ; RETURN TO SNIPPET NUMBER IN PARENT LINEAGE
	void ivvme_executeThreadSnippet_rettonum(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:186
	// SFLAG [IMM8]						; SET FLAG BITS
	void ivvme_executeThreadSnippet_sflag(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:187
	// CFLAG [IMM8]						; CLEAR FLAG BITS
	void ivvme_executeThreadSnippet_cflag(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:188
	// TFLAG [IMM8]						; TOGGLE FLAG BITS
	void ivvme_executeThreadSnippet_tflag(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:189
	// INFLAG [SOURCE]					; COPY [SOURCE] TO FLAGS
	void ivvme_executeThreadSnippet_inflag(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:190
	// OUTFLAG [SOURCE]					; COPY FLAGS TO [SOURCE]
	void ivvme_executeThreadSnippet_outflag(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:191
	// SETC							; SET CARRY? FLAG
	void ivvme_executeThreadSnippet_setc(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:192
	// SETO							; SET OVERFLOW? FLAG
	void ivvme_executeThreadSnippet_seto(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:193
	// SETU							; SET UNDERFLOW? FLAG
	void ivvme_executeThreadSnippet_setu(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:194
	// SETE							; SET EQUAL? FLAG
	void ivvme_executeThreadSnippet_sete(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:195
	// SETZ							; SET ZERO? FLAG
	void ivvme_executeThreadSnippet_setz(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:196
	// SETN							; SET NEGATIVE? FLAG
	void ivvme_executeThreadSnippet_setn(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:197
	// SETP							; SET POSITIVE? FLAG
	void ivvme_executeThreadSnippet_setp(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:198
	// SETA							; SET APP? FLAG
	void ivvme_executeThreadSnippet_seta(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:199
	// SETAN [IMM4]						; SET APPn? FLAG
	void ivvme_executeThreadSnippet_setan(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:200
	// CLRAN [IMM4]						; CLEAR APPn? FLAG
	void ivvme_executeThreadSnippet_clran(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:201
	// TOGAN [IMM4]						; MOVE APPn? IN TO APP? FLAG
	void ivvme_executeThreadSnippet_togan(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:202
	// LOADTHEME [SOURCE]				        ; ASCII NAME OF THE THEME TO LOAD
	void ivvme_executeThreadSnippet_loadtheme(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:203
	// RENDERSTART [SOURCE]				        ; SIGNAL TO THE VVM THAT RENDER UPDATES ARE BEGINNING USING [THEME]
	void ivvme_executeThreadSnippet_renderstart(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:204
	// RENDERREGION [SOURCE] [SOURCE] [SOURCE]	        ; RENDER THE INDICATED [SCREEN], [CANVAS] AND [REGION] USING VIA HOST DEFAULT
	void ivvme_executeThreadSnippet_rendrregion(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:205
	// RENDERCANVAS [SOURCE]			        ; RENDER THE INDICATED [CANVAS] (DRAWS ALL CHILD CANVASES ONTO IT)
	void ivvme_executeThreadSnippet_rendercanvas(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:206
	// RENDERSCREEN [SOURCE]			        ; RENDER THE INDICATED [SCREEN] (DRAWS ALL CHILD CANVASES ONTO IT)
	void ivvme_executeThreadSnippet_renderscreen(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:207
	// RENDERSTOP						; SIGNAL VVM RENDER UPDATES ARE COMPLETE
	void ivvme_executeThreadSnippet_renderstop(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:208
	// APPOAPA [SOURCE] TO [SOURCE]		                ; APPEND OBJECT [REG] TO OBJECT [REG] AS PARENT
	void ivvme_executeThreadSnippet_appoapa(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:209
	// APPOACH [SOURCE] TO [SOURCE]		                ; APPEND OBJECT [REG] TO OBJECT [REG] AS CHILD
	void ivvme_executeThreadSnippet_appoach(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:210
	// APPOAPR [SOURCE] TO [SOURCE]		                ; APPEND OBJECT [REG] TO OBJECT [REG] AS PREV
	void ivvme_executeThreadSnippet_appoapr(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:211
	// APPOANE [SOURCE] TO [SOURCE]		                ; APPEND OBJECT [REG] TO OBJECT [REG] AS NEXT
	void ivvme_executeThreadSnippet_appoane(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:212
	// DELOFO [SOURCE] FROM [SOURCE]	                ; DELETE/PRUNE [REG] FROM OBJECT [REG] (STILL EXISTS AS INSTANCE OBJECT, AND POSSIBLY ON OTHER PARENTS)
	void ivvme_executeThreadSnippet_delofo(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:213
	// DESTROY [SOURCE]					; DESTROY OBJECT
	void ivvme_executeThreadSnippet_destroy(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:214
	// ISCATTER [SOURCE]				        ; ISCATTER (INTEGER REGISTERS TO MEMORY BLOCK)
	void ivvme_executeThreadSnippet_iscatter(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:215
	// FSCATTER [SOURCE]				        ; FSCATTER (FLOATING POINT REGISTERS TO MEMORY BLOCK)
	void ivvme_executeThreadSnippet_fscatter(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:216
	// IGATHER [SOURCE]					; IGATHER (MEMORY BLOCK TO INTEGER REGISTERS)
	void ivvme_executeThreadSnippet_igather(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:217
	// FGATHER [SOURCE]					; FGATHER (MEMORY BLOCK TO FLOATING POINT REGISTERS)
	void ivvme_executeThreadSnippet_fgather(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:218
	// TMRAG [INTERVAL] [SNIPPET]		                ; TIMER ADD GLOBAL INTERVAL [REG] USING SNIPPET [REG]
	void ivvme_executeThreadSnippet_tmraddg(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:219
	// TMRDELG [SOURCE]					; TIMER DELETE GLOBAL [REG]
	void ivvme_executeThreadSnippet_tmrdelg(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:220
	// TMRENAG [SOURCE]					; TIMER ENABLE GLOBAL [REG]
	void ivvme_executeThreadSnippet_tmrenag(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:221
	// TMRDISG [SOURCE]					; TIMER DISABLE GLOBAL [REG]
	void ivvme_executeThreadSnippet_tmrdisg(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:222
	// TMRADDT [INTERVAL] [SNIPPET]		                ; TIMER ADD THREAD INTERVAL [REG] USING SNIPPET [REG]
	void ivvme_executeThreadSnippet_tmraddt(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:223
	// TMRDELT [SOURCE]					; TIMER DELETE THREAD [REG]
	void ivvme_executeThreadSnippet_tmrdelt(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:224
	// TMRENAT [SOURCE]					; TIMER ENABLE THREAD [REG]
	void ivvme_executeThreadSnippet_tmrenat(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:225
	// TMRDIST [SOURCE]					; TIMER DISABLE THREAD [REG]
	void ivvme_executeThreadSnippet_tmrdist(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:226
	// PASSIVE						; ENTER PASSIVE MODE, READ EVENTS AND RESPOND TO THEM WITHOUT CONTINUING THREAD EXECUTION
	void ivvme_executeThreadSnippet_passive(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:227
	// ACTIVE						; LEAVE PASSIVE MODE UPON COMPLETION OF CURRENT SNIPPET, CLEAR EVENTS AND RESUME LINEAR EXECUTION
	void ivvme_executeThreadSnippet_active(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:228
	// SETEXS [SOURCE]					; EXCEPTION SET DEFAULT SNIPPET [REG]
	void ivvme_executeThreadSnippet_setexs(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:229
	// EXCEPS [SOURCE SNIPPET]			        ; EXCEPTION TRIGGER EXPLICIT SNIPPET [NUMBER]
	void ivvme_executeThreadSnippet_exceps(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:230
	// THRAP						; THREAD ADD, PAUSED, NO SNIPPET DEFINED
	void ivvme_executeThreadSnippet_thrap(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:231
	// THRAPS [SOURCE]					; THREAD ADD, PAUSED, USING SNIPPET [REG]
	void ivvme_executeThreadSnippet_thraps(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:232
	// THRAS [SOURCE]					; THREAD ADD, NOT PAUSED, USING SNIPPET [REG]
	void ivvme_executeThreadSnippet_thras(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:233
	// THRAF [SOURCE THREAD] [IMM8 CPU]	                ; THREAD [REG] ASCRIBE AFFINITY [REG]
	void ivvme_executeThreadSnippet_thraf(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:234
	// THRST						; THREAD SELF TERMINATE
	void ivvme_executeThreadSnippet_thrst(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:235
	// THRSP						; THREAD SELF PAUSE
	void ivvme_executeThreadSnippet_thrsp(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:236
	// THRXT [SOURCE]					; THREAD [REG] TERMINATE
	void ivvme_executeThreadSnippet_thrxt(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:237
	// THRXP [SOURCE]						; THREAD [REG] PAUSE
	void ivvme_executeThreadSnippet_thrxp(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:238
	// THRXR [SOURCE]						; THREAD [REG] RESUME
	void ivvme_executeThreadSnippet_thrxr(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:239
	// THRXRS [SOURCE THREAD] [SNIPPET]		; THREAD [REG] RESUME USING SNIPPET [REG]
	void ivvme_executeThreadSnippet_thrxrs(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:240
	// THRXJ [SOURCE]						; THREAD [REG] JOIN
	void ivvme_executeThreadSnippet_thrxj(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:241
	// SCREATE								; SEMAPHORE CREATE
	void ivvme_executeThreadSnippet_screate(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:242
	// SLOCK	[SOURCE]					; SEMAPHORE LOCK, WAIT UNTIL LOCKS
	void ivvme_executeThreadSnippet_slock(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:243
	// STRYLOCK [SOURCE]		        	; TRY SEMAPHORE LOCK, RETURN IMMEDIATELY IF FAILS
	void ivvme_executeThreadSnippet_strylock(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:244
	// SUNLOCK [SOURCE]						; SEMAPHORE UNLOCK
	void ivvme_executeThreadSnippet_sunlock(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:245
	// SDELETE [SOURCE]						; SEMAPHORE DELETE
	void ivvme_executeThreadSnippet_sdelete(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:246
	// PREDICATE [IMM16]					; USES AN EXTENDED PREDICATE FOR A HIGH COMBINATION OF EXPLICIT CONDITIONS
	void ivvme_executeThreadSnippet_predicate(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:247
	// COPYPRED [SOURCE]					; COPIES 24-BIT QUANTITY INTO PRED (PREDICATE) REGISTER
	void ivvme_executeThreadSnippet_copypred(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:248..254
	// UNUSED
	void ivvme_executeThreadSnippet_unused(_ivvme_executeThreadSnippetData* tsed)
	{
	}

	// OPCODE:255
	// EXTENDED
	void ivvme_executeThreadSnippet_extended(_ivvme_executeThreadSnippetData* tsed)
	{
	}
