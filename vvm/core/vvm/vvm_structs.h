//////////
//
// /libsf/vmm/vmm/vmm_structs.h
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
//     Sep.19.2012 - Initial creation
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



struct	SVvm;

struct	SProgram;
struct	SVariable;
struct	SSnipExec;
struct	SSnip;
struct	STimer;
struct	SThread;
struct	SDynSnipData;
struct	SDatum;

struct	SScreen;
struct	SCanvas;
struct	SCanvasList;
struct	SRegion;
struct	SRegionList;
struct	SRegionState;
struct	SEvent;

struct	SBreakpoint;
struct	SBreakCond;

struct	SRegs;
struct	SStack;

struct	SLine;
struct	SUpLine;
struct	SUpSnip;




//////////
//
// For resource texts
//
//////
	struct SVvmResourceText
	{
		u32		resourceNumber;						// The resource number
		s8*		text;								// The text that goes with it (NULL-terminated)
	};




//////////
//
// Dynamic snippets take on three forms:
//		
//		(1) Calls to loaded BXML files (loaded at runtime)
//		(2) Calls to a loaded DLL
//		(3) Calls to changed VVM snippets or dynamic snippets (edit-and-continue)
//
//////
	struct SDynSnipDll;
	struct SDynSnip;
	struct SDynSnipVvm;

	// Dynamic snippets loaded via runtime Bxmls
	struct SDynSnipBxml
	{
		SLL				ll;						// 2-way link list

		// Function information
		u64				funcId;					// The snippet's unique id as is compiled in source code (as the DSNIP_Bxml definition)
		SSnip*			snip;					// The actual loaded code snippet at runtime
	};

	struct SDSnipDllFuncs
	{
		SLL				ll;						// 2-way link list
		SDynSnipDll*	parent;					// For optimization, the SDSnipDllFuncs may be in its own list for searching functions by uniqueId, and when found will need to know its parent

		// For DLL support
		SDatum			funcName;				// This specific function name
		u64				funcAddress;			// Physical address within the DLL

		// For processing
		SVariable*		_return;				// Indicates the return value format
		SStartEnd		_params;				// Defined parameters							(SVariable)
	};

	// Dynamic snippets loaded as external DLL functions
	struct SDynSnipDll
	{
		SLL				ll;						// 2-way link list
		SDynSnip*		parent;					// For optimization, its child SDSnipDllFuncs may be in its own list for searching functions by uniqueId, and when found will need to know its parent, which will need to know its parent (or grandparent depending on point of view)

// TODO:  related to the request in this BXML file is the oss_loadDll() function, which will need to be written
		bool			isLoaded;				// Has this function been loaded?
		u64				ossDllId;				// Id/handle given this dll by the OSS code
		SDatum			ossDllDataBlock;		// Information the OSS needs to store about this DLL

		// Information
		SDatum			dllPathname;			// DLL path name to access the physical file on disk (such as vcodec.dll)
		SDatum			dllName;				// DLL given name (what the programmer said the program in this DLL is called, such as "Video Encoder")
		SDatum			dllVersion;				// Version information (a string identifying the version)

		// Callback to an interface function to request information
		SStartEnd		dsnips;					// DL functions known to this dsnip				(SDSnipDllFuncs)
	};

	// Edit-and-continue dynamic snippets
	struct SDynSnipVvm
	{
		SLL				ll;						// 2-way link list

		// Information for accessing the specified dynamic snippet
		SDatum			functionName;			// Name of the function

		// Information about what was replaced
		u32				typePrev;				// Either _VVM_SNIP or _VVM_DSNIP
		union {
			SSnip*			snipPrev;			// The snippet this dynamic snippet is replacing
			SDynSnipVvm*	dsnipPrev;			// The dynamic snippet this dynamic snippet is replacing
		};

		// Used for quick reference by machine code
		u64				funcId;					// The previous snippet's unique id
		SSnip*			snip;					// The snippet this edit-and-continue will now execute
	};

	// Dynamic snippets are one of three forms (see VVM_DSNIP_* in common_vvm.h)
	struct SDynSnip
	{
		SLL				ll;						// 2-way link list

		// Type of dynamic snippet
		u32				type;					// See VVM_DSNIP_* in common_vvm.h

		// Based on the type, one of three pieces of source data:
		union {
			SStartEnd		dsnipBxml;			// Pointer to data for the DSNIP_Bxml info		(SDynSnipBxml)
			SStartEnd		dsnipDll;			// Pointer to data for the DSNIP_DLL info		(SDynSnipDll)
			SDynSnipVvm*	dsnipVvm;			// Pointer to data for edit-and-continue dynamic snippets
		};
	};


	// Snippet structure, used at compile/assembly time, as well as run-time
	struct SSnip
	{
		SLL				ll;						// 2-way link list

		// Meta data about this snippet
		SDatum			functionName;			// Name of this snippet
		SStartEnd		pdb;					// Program database																		(SPdb struct)

		// At this snippet level
		SStartEnd		_params;				// Passed parameters (or references) are limited to 16 slots (4-bit nibble max size)	(SVariable)
		SStartEnd		_returns;				// Return parameters are also limited to 16 slots (4-bit nibble max size)				(SVariable)
		SStartEnd		_locals;				// Locals are allocated as needed														(SVariable)

		// References this snippet uses
		SStartEnd		refGlobals;				// Global variable references in this snippet											(SDatum)
		SStartEnd		refSnips;				// References to snippets																(SDatum)
		SStartEnd		refDSnips;				// References to dynamic snippets														(SDatum)

		// Physical assembly/machine code to execute
		SDatum			machineCode;			// Pointer to machine code bytes for execution in VVM's CPU engine
	};





//////////
//
// DynSnip data items are data blocks allocated by DynSnip code, data
// which must persist beyond running instances of the VM, so it can be
// saved and later restored as part of the execution state.
//
//////
	struct SDynSnipData
	{
		SLL				ll;						// 2-way link list

		// Each dynamic data item has a name associated with it
		SDatum			tag;

		// All allocated remote data portions are relative to this base.
		// They are not linear addresses in memory, but linear addresses from this base.
		// So every internal referenced pointer begin at dataBase[*otherPtr], where
		// otherPtr is a variable offset to some other data.
		// This is done so that the complete state of the virtual machine can be
		// paused, saved to disk, restored, and restarted, either on this machine
		// or another, at any time.
		SDatum			data;					// Data block 
	};




//////////
//
// 8-bit, 16-bit, 32-bit and 64-bit integer registers
//  ___________________________________ _________________ ________ ________
// |                 X64               |       X32       |  X16   |   X8   |
// |........|........|........|........|........|........|........|........|
// 63                                32                16        8        0
//
//////
	struct SRegsI	// Integer
	{
		union
		{
			u64		x64;		// 64-bit integer
			u32		x32;		// 32-bit integer
			u16		x16;		// 16-bit integer
			u8		x8;			// 8-bit integer
		};
	};




//////////
//
// 32-bit and 64-bit floating point registers
//  ___________________________________ _________________ ________ ________
// |                FX64               |                FX32               |
// |........|........|........|........|........|........|........|........|
// 63                                32                                   0
//
//////
	struct SRegsFP
	{
		// Note:  The validity of this register depends on prior use or initialization
		union
		{
			f64		fx64;		// 64-bit floating point
			f32		fx32;		// 32-bit floating point
		};
	};




//////////
//
// Flags registers
//
//////
	struct SFlags
	{
		union
		{
			// Reference as a single quality (for saving on stack)
			u64			_flags;

			// Reference as components
			struct {
				// debuggerActivity is a quicker access to test for debugger conditions each iteration
				union {
					u8	debuggerActivity;
					struct {
						u32		_debx_active	: 1;	// Is there an extended debug condition active?
						u32		_deb4_active	: 1;	// Are the debugger4 registers (DSNP4, DOFF4) active?
						u32		_deb3_active	: 1;	// Are the debugger3 registers (DSNP3, DOFF3) active?
						u32		_deb2_active	: 1;	// Are the debugger2 registers (DSNP2, DOFF2) active?
						u32		_deb1_active	: 1;	// Are the debugger1 registers (DSNP1, DOFF1) active?
						u32		_single_step	: 1;	// Should this thread only execute one instruction and then trap back to the debugger?
						u32		_in_error		: 1;	// Has this thread generated an error?
						u32		_is_suspended	: 1;	// Is the thread suspended?
					};
				};

				// appN_Activity is a quicker access to test for appN predicate conditions when needed
				// The _appN flags have a single instruction with a mask that can be used to set these conditions. They can be tested using an extended predicate.
				union {
					u8	appN_Activity;
					struct {
						u32		_app8			: 1;	// Application specific flag #8
						u32		_app7			: 1;	// Application specific flag #7
						u32		_app6			: 1;	// Application specific flag #6
						u32		_app5			: 1;	// Application specific flag #5
						u32		_app4			: 1;	// Application specific flag #4
						u32		_app3			: 1;	// Application specific flag #3
						u32		_app2			: 1;	// Application specific flag #2
						u32		_app1			: 1;	// Application specific flag #1
					};
				};

				// The _app flag below has stand-alone VVM assembly opcodes which process it, can be used as a predicate
				u32		_app			: 1;	// Application specific
				u32		_positive		: 1;	// Was the last result positive?
				u32		_negative		: 1;	// Was the last result negative?
				u32		_zero			: 1;	// Zero?
				u32		_equal			: 1;	// Equal?
				u32		_underflow		: 1;	// Underflow?
				u32		_overflow		: 1;	// Overflow?
				u32		_carry			: 1;	// Carry?
			};
		};
		// Total: 64 bits
	};




//////////
//
// Master register image
//
//////
	struct SRegs
	{
		u64				_result;				// 000, 8  - Each assembly instruction that performs some complex operation returns its result here

		// Integer registers
		SRegsI			a;						// 008, 8  - 64-bit integer
		SRegsI			b;						// 016, 8  - 64-bit integer
		SRegsI			c;						// 024, 8  - 64-bit integer
		SRegsI			d;						// 032, 8  - 64-bit integer
		SRegsI			e;						// 040, 8  - 64-bit integer
		SRegsI			f;						// 048, 8  - 64-bit integer
		SRegsI			g;						// 056, 8  - 64-bit integer
		SRegsI			h;						// 064, 8  - 64-bit integer
		SRegsI			i;						// 072, 8  - 64-bit integer
		SRegsI			j;						// 080, 8  - 64-bit integer
		SRegsI			k;						// 088, 8  - 64-bit integer
		SRegsI			l;						// 096, 8  - 64-bit integer
		SRegsI			m;						// 104, 8  - 64-bit integer
		SRegsI			n;						// 112, 8  - 64-bit integer
		SRegsI			o;						// 120, 8  - 64-bit integer
		SRegsI			p;						// 128, 8  - 64-bit integer

		// Floating point registers
		SRegsI			fa;						// 136, 8  - 64-bit floating point
		SRegsI			fb;						// 144, 8  - 64-bit floating point
		SRegsI			fc;						// 152, 8  - 64-bit floating point
		SRegsI			fd;						// 160, 8  - 64-bit floating point
		SRegsI			fe;						// 168, 8  - 64-bit floating point
		SRegsI			ff;						// 176, 8  - 64-bit floating point
		SRegsI			fg;						// 184, 8  - 64-bit floating point
		SRegsI			fh;						// 192, 8  - 64-bit floating point
		SRegsI			fi;						// 200, 8  - 64-bit floating point
		SRegsI			fj;						// 208, 8  - 64-bit floating point
		SRegsI			fk;						// 216, 8  - 64-bit floating point
		SRegsI			fl;						// 224, 8  - 64-bit floating point
		SRegsI			fm;						// 232, 8  - 64-bit floating point
		SRegsI			fn;						// 240, 8  - 64-bit floating point
		SRegsI			fo;						// 248, 8  - 64-bit floating point
		SRegsI			fp;						// 256, 8  - 64-bit floating point

		// Control registers
		u64				snip;					// 264, 8  - current snippet number executing for this thread
		u64				ip;						// 272, 8  - instruction pointer
		u64				sp;						// 280, 8  - stack pointer
		u64				bp;						// 288, 8  - base pointer

		u64				ready;					// 296, 8  - READY block of data to snippet
		u64				readyOffset;			// 304, 8  - The incrementing offset into the ready block

		SFlags			flags;					// 312, 8  - flags register
		u64				pred;					// 320, 8  - predicate flags
		u64				predCount;				// 328, 8  - predicate reset count

		u64				exsnip;					// 336, 8  - Exception snippet
		u64				error;					// 344, 8  - Error number signaled by the VVM

		u64				nuserved1;				// 352, 8  - #2 Snippet or Dynamic Snippet debug break number
		u64				nuserved2;				// 360, 8  - #2 Offset into snippet where we are to break
		u64				nuserved3;				// 368, 8  - #3 Snippet or Dynamic Snippet debug break number
		u64				nuserved4;				// 376, 8  - #3 Offset into snippet where we are to break
		u64				nuserved5;				// 384, 8  - #4 Snippet or Dynamic Snippet debug break number
		u64				nuserved6;				// 392, 8  - #4 Offset into snippet where we are to break
		// Total 400 bytes
		// See current OBED definition
	};




//////////
//
// Master Virtual Machine, one instance for each program
//
//////
	struct SVvm
	{
		SLL				ll;						// 2-way link list
		SStartEnd*		program;				// Programs loaded
	};





//////////
//
// Master Program
//
//////
	struct SProgram
	{
		SLL				ll;						// 2-way link list
		u64				semForThreadsAccess;	// Explicit atomic program-level access

		// Program components
		SStartEnd		screens;				// List of screens								(SScreen)
		SStartEnd		_globals;				// List of global variables						(SVariable)
		SStartEnd		snips;					// List of snippets								(SSnip)
		SStartEnd		dsnips;					// List of dynamic snippets						(SDynSnip)
		SStartEnd		_timers;				// List of timers								(STimer)
		SStartEnd		_threads;				// List of threads								(SThread)

		// Memory needed / allocated by external DLLs
		SStartEnd		dsnipRemoteData;		// Allocated blocks of memory requested by dynamic snippets (SDynSnipData)

		// Runtime loaded components
		SStartEnd		dlls;					// DLLs required to be loaded					(SProgDlls)

		// Private components referenced for debugging, or during compilation/assembly.
		// Generally speaking, these will not be populated at runtime.  However, they can be
		// if that information is conveyed in the written BXML file.
		SStartEnd		_defines;				// List of constants/defines					(SVariable)
		SStartEnd		_sourceFiles;			// List of source files							(SDatum)
		SStartEnd		_compile;				// Used during compile time						(SRDC)
		SStartEnd		_assembly;				// Used during assembly time					(SAssembly)
	};




//////////
//
// General format for variable options (global variables, parameters, locals, return values
//
//////
	// Instances of variables are stored here
	struct SVarInst
	{
		u32				type;					// See _VVM_VARIABLE_TYPE_* constants in common_vvm.h
		u64				integer;				// Value if it's a fixed integer short form
		SDatum			_value;					// If it's an extended form, longer storage form
	};

	struct SVariable
	{
		SLL				ll;						// 2-way link list

		// If this is a reference to another variable, it is encoded
		SVariable*		reference;				// If populated, we don't use this variable, but this is a place holder to access the other variable's information

		// Properties for this variable
		SDatum			name;					// Public name of the variable in ASCII
		SStartEnd		aliases;				// Any aliases for this name
		SDatum			unicodeName;			// (optional) Public name of the variable in unicode
		SStartEnd		unicodeAliases;			// (optional) Any aliases for this name in unicode

		// Current variable value
		SVarInst		current;				// The current value
		SVarInst		prior;					// The immediately prior value
		SVarInst		_default;				// If specified, an optional default value

		// Variable components
		SDatum			overflowValue;			// If specified, possesses the overflow value
		SDatum			underflowValue;			// If specified, possesses the underflow value
		SDatum			min;					// If specified, the min value it can be
		SDatum			max;					// If specified, the max value it can be
		bool			_protected;				// If true, this variable is NOT released with CLEAR ALL or RELEASE ALL
		bool			_readonly;				// If true, this variable cannot be changed
	};




//////////
//
// Data gathered and used during compilation and assembly
//
//////
	struct SBlock;
	struct SOssLine;
	struct SOssComp;

	// For every label that's encountered
	struct SLabelInfo
	{
		SLL				ll;						// 2-way link list

		// Data about the label
		SBlock*			blockAssociation;		// The block to which this line is associated
		SOssComp*		comp;					// The component that was found
	};

	// For every pipe-sign-related entry for the snippet/dynSnippet/DllFunction, etc
	struct SPipeInfo
	{
		SLL				ll;						// 2-way link list

		// Data about the pipe entry
		SOssComp*		comp;					// The component that was found
	};

	struct SDllFuncInfo
	{
		SLL				ll;						// 2-way link list

		// Data about the function info
		SOssComp*		comp;					// The component where the DLL_FUNCTION was defined
		SStartEnd		pipeData;				// The |PARAMS-like items for this entry		(SPipeInfo)
	};

	struct SBlock
	{
		SLL				ll;						// 2-way link list

		// Block range
		SOssLine*		start;					// Declaration line
		SOssComp*		compTrigger;			// The component which triggered the start of this block
		SOssLine*		end;					// End declaration line
		SStartEnd		labels;					// A list of labels within the block			(SLabelInfo)
		SStartEnd		pipeData;				// The |PARAMS-like items for the block			(SPipeInfo)
		SStartEnd		dllFuncs;				// List of declared DLL functions within		(SDllFuncInfo)

		// Based on the context to which this SBlock entry belongs
		union {
			SSnip*		snip;					// The snippet being built for this code
			SDynSnip*	dsnip;					// The dynamic snippet being built for this code
		};
	};

	struct SSourceFile
	{
		SLL				ll;						// 2-way link list

		SDatum			pathname;				// Relative or full pathname to the source file
		SDatum			sourceCode;				// The source code as loaded from disk at the time (Note:  In BXML files the source code will not be here, but will be in the SPdb portions)

		// Information about the source code
		SStartEnd		lines;					// lines identified within this source file		(SOssLine)
		SStartEnd		errors;					// Errors encountered processing this file		(SErrors)
		SStartEnd		warnings;				// Warnings encountered processing this file	(SWarnings)
		SStartEnd		blocks;					// Snippets encountered in source code			(SBlock)
	};

	// Data gathered at assembly time
	struct SAssembly
	{
		SLL				ll;						// 2-way link list
		SStartEnd		includeFiles;			// Each file that is included in a project		(SSourceFile)
		SProgram*		prog;					// The program points to this SAssembly entry, but we still need to reference it in code without constantly passing another parameter
	};




//////////
//
// Thread Mizer execution of programs, threads
//
//////
	// Is the structure for the actual thread mizer engine (see vvm_tm.cpp)
	struct SThreadMizer
	{
		SLL				ll;						// 2-way link list
		bool			isThreadAlive;			// Set by the OS when the thread is active, be it paused, or resumed, cleared when the thread has terminated

		// Thread information
		u32				threadNum;				// Number of the thread, as created at startup
		u32				terminationValue;		// Value given at termination if not running

		// OSS data
		u64				ossInfo;				// Any required OSS info needed for this thread
	};




//////////
//
// Thread execution state
//
//////
	// Holds individual thread execution status
	struct SThreadControl
	{
		bool			inUse;					// Is this thread slot in use?
		bool			isSuspended;			// Is this thread suspended, or is it able to be scheduled by the scheduler?
		u32				affinity;				// Set to -1 if none specified, otherwise looking for an explicit thread

		// Parameters during execution
		u64				semaphoreAccess;				// Explicit thread-level access
		u64				startTick;			// The internal counter at the last execution given this thread
	};

	struct SThread
	{
		SLL				ll;						// 2-way link list
		SThreadControl	status;					// Status of this thread

		// Thread variables
		SDatum			stack;					// Pointer to the stack's data block
		SRegs			regs;					// Pointer to the registers for the VM

		// For the local thread, individual timers which interrupt the current thread for execution
		SStartEnd		_timers;				// Pointer to the list of STimer entries (if any)
		SStartEnd		_globals;				// Pointer to thread-specific global variables

		// For the current snippet:
		SSnipExec*		current;				// Shortcut pointer to the currently executing snippet
		SStartEnd		snippet;				// Pointer to the list of SSnippet entries in the program chain from main (levels down, SSnipExec structure)
	};

	// Executing snippet chain from main
	struct SSnipExec
	{
		SLL				ll;						// 2-way link list

		// Snippet executing at this level
		SSnip*			snip;					// If snippet, pointer to the SSnip structure

		// At this snippet level
		SStartEnd		_params;				// Passed parameters (or references) are limited to 16 slots (4-bit nibble max size)	(SVariable)
		SStartEnd		_returns;				// Return parameters are also limited to 16 slots (4-bit nibble max size)				(SVariable)
		SStartEnd		_locals;				// Locals are allocated as needed														(SVariable)
	};




	// Source code line
	struct SLine
	{
		SLL				ll;						// 2-way link list

		// Information about offset into the binary execution code
		SRef			lineMC;					// This line's start and length into the related snippet's machineCode

		// Information about original source code
		u32				number;					// The source code line number, or component number if a sub-component
		SDatum			sourceCode;				// Original line/block of source code
	};


	// Code snippet
	struct SPdbComp
	{
		SLL				ll;						// 2-way link list

		// Where this item comes into scope
		SRef			subSubMC;				// Offset into the machine code where this component exists
		SRef			subSourceCode;			// Offset into the source code line where this component exists
	};


	// Program database, outlining the original source code as well as offset into machine code snippets
	struct SPdb
	{
		SLL				ll;						// 2-way link list

		// Relative to parent snippet or dynamic snippet
		SRef			subMC;					// Offset into the parent's machine code for this entry

		// Information about the source code
		SSourceFile*	sourceFile;				// The related source file
		SStartEnd		sourceCode;				// Source code lines backing into this block											(SLine)

		// Individual components within this range
		SStartEnd		comps;					// Components within that line of source code											(SPdbComp)
	};




	struct	STimer
	{
// TODO:  guess. :-)
	};
