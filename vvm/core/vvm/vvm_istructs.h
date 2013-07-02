//////////
//
// /libsf/vmm/vmm/vmm_istructs.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 11, 2012
//////
// Change log:
//     November 11, 2012 - Initial creation
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
// Internal structures
// These are NOT designed to be referenced anywhere outside of the VVM's core engine.
//
//////




	// The main VVM app's data variables
	struct _isSVvmApp
	{
		int				gnVvmReturnResult;				// Indicate an initial return of failure
		bool			glVvmIsRunning;					// The VVM will continue as long as it is set to continue ... oh yes indeed. :-)
		bool			glVvmDebugBreaks;				// A global debugging flag if INT3 should be signaled when certain debugging conditions occur
		HINSTANCE		ghVvmResourceDll;				// Handle to the loaded resource dll instance
		s8*				gcVvmResourceLang;				// By default, points to English, override using command line switch "-r:" (such as "-r:es" for "vvmes.dll", for example)

		// Command-line determined instance sizes for variable allocation
		// NOTE:  The allocation size here will need to be inspected when the VVM is running to determine a better default size
		u32				gnGlobalAllocationBlockSize;	// The default size to increase the global variable allocation
		u32				gnLocalAllocationBlockSize;		// The default size to increase the global variable allocation
		u32				gnStackAllocationBlockSize;		// Default to an 8K stack per thread
		u32				gnSnippetAllocationBlockSize;	// The default size to increase the snippet level allocation


		// The root objects
		SStartEnd		gseRootPrograms;				// Master programs list
		SStartEnd		gseRootThreadMizer;				// Master thread mizer list
		SStartEnd		gseRootResourceTexts;			// Previously loaded / cached resource texts


		// Semaphores for synchronized access to master lists
		u64				gsemProgramsAccess;				// Master program inventory
	};

	// Used in ivvmtm_* functions
	struct _ivvmtm_SMainLoop
	{
		// Local variables used in ivvmtm_mainLoop.  They were moved into a structure so they can
		// be passed to separate functions which break out the logic and make it easier to understood.
		bool			llProgramsGeneralAccessLocked, llProgramsAccessLocked, llThreadsAccessLocked;
		bool			llProcessedSomething;
		u32				lnI, lnJ;
		SThreadMizer*	ltm;
		SProgram*		lp;
		SThread*		lt;
	};

	struct _ivvme_executeThreadSnippetData
	{
		u8*		lid;			// Pointer to start of instruction
		u32		lnDecoder;		// Grab the first DWORD and load it as the initial decoder
		u32		lnPredicate;	// Stores the predicate, or extended predicate if indicated
		u32		lnOpcode;		// Stores the instruction opcode, or extended/2nd opcode if indicated

		// Opcode address we're immediately processing
		union {
			u32		_vvmOpcodeExecute;			// Target address for the opcode decoding
			void	(*vvmOpcodeExecute)	(_ivvme_executeThreadSnippetData* tsed);
		};
	};


//////////
//
// Refer to the vvmt_defs.h file in the vvm_core.sln or vvm_canvas.sln (two test DLLs written at
// the time of this structure's creation) to see the actual definition of these functions, which
// must match up with what is coded here
//
//////
	struct _isSVvmTests
	{
		u64 DllInstance;


		//////////
		// firstCallback
		//////
			union {
				u64		_firstCallback;
				u64		(CALLTYPE *firstCallback)				(u64 tnDebuggerInterfaceAddress);
			};


		//////////
		// bootstrapInitialization
		//////
			union {
				u64		_bootstrapInitialization;
				void	(CALLTYPE *bootstrapInitialization)		(u64 tnDebuggerInterfaceAddress);
			};


		//////////
		// initialization
		//////
			union {
				u64		_initialization;
				void	(CALLTYPE *initialization)				(u64 tnDebuggerInterfaceAddress);
			};


		//////////
		// getVersion
		//////
			union {
				u64			_getVersion;
				const s8*	(CALLTYPE *getVersion)				(void);
			};


		//////////
		// executeTests
		//////
			union {
				u64		_executeTests;
				bool	(CALLTYPE *executeTests)				(u64 lnHandleLog);
			};
	};