//////////
//
// /libsf/source/vjr/compiler.cpp
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jun.17.2014
//////
// Change log:
//     Jun.17.2014 - Initial creation
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




struct SStartEnd;
struct SMasterList;
struct SComp;
struct SCompCallback;
struct SSubInstr;
struct SOp;
struct SAsciiCompSearcher;
struct SStartEndCallback;
struct SLL;
struct SLLCallback;
struct SVariable;

//////////
//
// Forward declarations for parsing VXB-- lines and components
//
//////////
	u32						compile_Vxbmm								(SEditChainManager* codeBlock, bool tlEditAndContinue);
	void					iiTranslateSOpsToSubInstr					(SEditChain* line, SSubInstr** siRoot);
 	SComp*					iTranslateSourceLineToSComps				(SAsciiCompSearcher* tsComps, SEditChain* line);
 	bool					iTranslateSCompsToOthers					(SAsciiCompSearcher* tsComps, SEditChain* line);
	s32						iTranslateSCompsToOthers_test				(s8* tcHaystack, s8* tcNeedle, s32 tnLength);
	bool					iFindFirstOccurrenceOfAsciiCharacter		(s8* tcHaystack, u32 tnHaystackLength, s8 tcNeedle, u32* tnPosition);
	SComp*					iFindNextSCompBy_iCode						(SComp* comp, u32 tniCode, SComp** compLastScanned);
	SComp*					iSkipPastSComp_iCode						(SComp* comp, u32 tniCode);
	u32						iCombine2SComps								(SEditChain* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2,                     u32 tniCodeCombined);
	u32						iCombine3SComps								(SEditChain* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeNeedle3, u32 tniCodeCombined);
	u32						iCombineAllBetweenSComps					(SEditChain* line, u32 tniCodeNeedle,                                          u32 tniCodeCombined);
	u32						iCombineAllAfterSComp						(SEditChain* line, u32 tniCodeNeedle);
	u32						iRemoveExtraneousWhitespaceSComps			(SEditChain* line, u32 tniCodeWhitespace);
	void					iTranslateSCompsToNaturalGroupings			(SEditChain* line);

//////////
// Jun.25.2014 -- This block of code was originally created before I began working on
// iiTranslateSOpsToSubInstr() above.  As such, it is stale and will probably be
// refactored or deleted.
// BEGIN
//////
	void					iiTranslateSCompsToSubInstr					(SEditChain* line);
	SComp*					iiTranslateSCompsToSubInstr_findInmostExpression	(SSubInstr* si, SEditChain* line);
	void					iiTranslateSCompsToSubInstr_findStartOfComponent	(SComp* compRoot, SOp* op);
	void					iiTranslateSCompsToSubInstr_findFullComponent		(SComp* compRoot, SOp* op);
	bool					iiTranslateSCompsToSubInstr_isEqualAssignment		(SEditChain* line);
	s32						iiCharactersBetweenSComps							(SComp* compLeft, SComp* compRight);
//////
// END
//////////

	u32						iBreakoutAsciiTextDataIntoLines_ScanLine	(s8* tcData, u32 tnMaxLength, u32* tnLength, u32* tnWhitespaces);
	u32						iGetNextUid									(void);
	void*					iSEChain_prepend							(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*					iSEChain_append								(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*					iSEChain_appendOrPrepend					(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult);
	u32						iSkipWhitespaces							(s8* tcData, u32 tnMaxLength);
	u32						iSkipToCarriageReturnLineFeed				(s8* tcData, u32 tnMaxLength, u32* tnCRLF_Length);
	void					iSEChain_appendMasterList					(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded);
	bool					iSEChain_allocateAdditionalMasterSlots		(SStartEnd* ptrSE, u32 tnBlockSize);
	s32						iTranslateToSCompsTest						(s8* tcHaystack, s8* tcNeedle, s32 tnLength);
	bool					iioss_translateSCompsToOthersCallback	(SStartEndCallback* cb);
	void*					iSEChain_searchByCallback					(SStartEnd* ptrSE, SStartEndCallback* cb);
	void					iiTranslateSCompsToOthersCallback__insertCompByCompCallback		(SComp* compRef, SComp* compNew, bool tlInsertAfter);
	void					iiTranslateSCompsToOthersCallback__insertCompByParamsCallback	(SComp* compRef, SEditChain* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter);
	void					iiTranslateSCompsToOthersCallback__deleteCompsCallback			(SComp* comp, SEditChain* line);
	SComp*					iiTranslateSCompsToOthersCallback__cloneCompsCallback			(SComp* comp, SEditChain* line);
	SComp*					iiTranslateSCompsToOthersCallback__mergeCompsCallback			(SComp* comp, SEditChain* line, u32 tnCount, u32 tniCodeNew);
	void					iSEChain_deleteFrom							(SStartEnd* ptrSE, void* ptrCaller, bool tlDeletePointers);
	SLL*					iSEChain_completelyMigrateSLLByPtr			(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr, u32 tnHint, u32 tnBlockSize);
	SLL*					iSEChain_completelyMigrateSLLByNum			(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);
	SMasterList*			iSEChain_migrateByNum						(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);

	// Linked list functions
	SLL*					iLl_appendNode								(SLL** root, SLL* nodeHint, SLL* nodeNext, SLL* nodePrev, u32 tnUniqueId, u32 tnSize);
	SLL*					iLl_createNode								(                           SLL* nodePrev, SLL* nodeNext, u32 tnUniqueId, u32 tnSize);
	void					iLl_deleteNode								(SLL* node);
	void					iLl_deleteNodesWithCallback					(SLLCallback* cb);
	bool					iLl_insertNode								(SLL* node, SLL* nodeRef, bool tlAfter);
	void					iLl_orphanizeNode							(SLL* node);
	void					iLl_deleteNodeChain							(SLL** root);
	void					iLl_deleteNodeChainWithCallback				(SLLCallback* cb);
	void					iLl_iterateViaCallback						(SLLCallback* cb);
	void					iLl_iterateBackwardViaCallback				(SLLCallback* cb);
	SLL*					iLl_getFirstNode							(SLL* node);
	SLL*					iLl_getLastNode								(SLL* node);



//////////
// Constant integers
//////
	cu32					_COMMON_START_END_BLOCK_SIZE			= 32;			// Allocate 32 entries/slots at a time (Start/end)
	cu32					_COMMON_START_END_SMALL_BLOCK_SIZE		= 4;			// Allocate 4 entries/slots at a time (Start/end)
	cu32					_COMMON_START_END_BIG_BLOCK_SIZE		= 256;			// Allocate 256 entries/slots at a time (Start/end)
	cu32					_COMMON_BUILDER_BLOCK_SIZE				= 16384;		// Allocate 16KB at a time
	cu32					_COMMON_BUILDER_BLOCK_SIZE_BIG			= 10240000;		// Allocate 1MB at a time


//////////
// Structures taken from Visual FreePro
//////
	struct SLL
	{
		SLL*			next;					// Next entry in linked list
		SLL*			prev;					// Previous entry in linked list
		u32				uniqueId;				// Unique id associated with this object
	};

	struct SLLCallback
	{
		union
		{
			u32		_func;
			bool	(*funcBool)	(SLLCallback* cb);
			void	(*funcVoid)	(SLLCallback* cb);
			//////
			// Uses the following format for the callback:
			//		void func(SLLCallback* cb)
			//		bool func(SLLCallback* cb)
			//////////
		};

		// Data items for this callback
		SLL*	node;
		union {
			u32		extra;
			u32		extra1;
		};
		u32		extra2;
	};

	struct SMasterList
	{
		SLL				ll;						// 2-way link list to hold the related pointer
		bool			used;					// Is this entry/slot used?

		// The reference pointer used to occupy this slot/position
		void*			ptr;					// The pointer associated with this entry
	};

	// The rigidity of this structure is extremely important.
	// Every item in the chain between root and last must be included in the master list!
	struct SStartEnd
	{
		SMasterList*	root;					// Root item
		SMasterList*	last;					// Last item

		// SStartEnd lists can have a master (which points to other items using the SMasterList protocol), or it can be used merely a pointer holder
		union {
			SMasterList**	master;				// Every item in the start/end chain is appended here when created (used primarily for suspension and resumption of the VVM)
			void**			ptr;
		};
		u32				masterCount;			// Number of entries in the master array (used for resizing)

		// Not used and reserved for future use
		void*			extra;					// For future expansion
	};

	// Structure to search for things
	struct SAsciiCompSearcher
	{
		const s8*		keyword;										// Text keyword being searched
		s32				length;											// Length of the keyword (negative for case sensitive, positive case insensitive, 0 for termination entry)
		bool			repeats;										// Can this item repeat?  Or is this a one-shot keyword?
		u32				iCode;											// An associated code to store when this entry is found
		bool			firstOnLine;									// Should this item ONLY be the first on line?

		// Used for an explicit callback to validate if this match (as by text) is really a match (as by context)
		union {
			u32			_validate;
			bool		(*validate)(SCompCallback* val);
		};

		// Used for an explicit callback to handle this component or text
		union {
			u32			_custom;
			void		(*custom)(void);
		};
	};

	struct SFunction
	{
		SFunction*		next;												// Next function in the chain
		SDatum			name;												// Function name (Note that code appearing at the top of a program without being enclosed in a function will have the source code line "FUNCTION top_of_program" automatically inserted at compile time

		// Knowns identified during compilation
		SVariable*		params;												// The first parameter in the function
		SVariable*		locals;												// The first local variable declared
		SVariable*		returns;											// The first return variable declared
		SVariable*		temps;												// The first temporary variable needed by the function

		// Where the function began in source code as of last compile
		SEditChain*		funcFirst;											// First line of the function
	};

	struct SVariable
	{
		SVariable*	next;													// If part of a chain, then points to the next item, otherwise null
		SDatum		name;													// Name of this variable
		u32			uid;													// Names may change during edit-and-continue, but the references they possess remain the same
		SVariable*	indirect;												// If non-NULL, this variable is an indirect reference to an underlying variable

		// Variable content based on type
		u32			type;													// Variable type (see _VARIABLE_TYPE_* constants)
		union {
			SVariable*		indirect;										// If the lower-bit of type is set (BIT0=1), it is an indirect reference to another variable
			SObject*		obj;											// If the lower-bit of type is clear, and it's an object, the object it relates to
			SDatum			value;											// If the lower-bit of type is clear, the actual data value based on its type
			SFunction*		thisCode;										// Pointer to the code block this relates to
		};

		// If assign or access
		SEditChainManager*	assign;											// Source code executed whenever this variable is assigned
		SEditChainManager*	access;											// Source code executed whenever this variable is accessed
	};

//////////
//
// Sub-instructions are components of a source code line broken out into individual tasks.
//
// They conduct those individual operations only, being part of the larger computation
// taking place across multiple sub-instructions.
//
// This structure is used for two operations in VJr.  One is for parsing source code into
// sub-instructions, the second is for generating actual sub-instruction lists for faster
// execution by the processing engine while still retaining edit-and-continue abilities.
//
//                      ______
//                     |parent|
//                     |______|
//                        ^
//                        |
//                     ___|___
//       _____        | Sub-  |        _____
//      | prev|<------| Instr |------>|next |
//      |_____|       |_______|       |_____|
//                    /       \
//                   /         \
//               ___/_         _\___
//              |left |       |right|
//              |_____|       |_____|
//
//////
	struct SSubInstr
	{
		SSubInstr*		parent;											// Up to the higher node
		SSubInstr*		prev;											// Previous item in the horizontal chain
		SSubInstr*		next;											// Next item in the horizontal chain
		SSubInstr*		left;											// Left node
		SSubInstr*		right;											// Right node
		u32				uid;											// Unique ID for this sub-instruction

		// Operation layer/level and instruction at that level
		s32				sub_level;										// The sub-instruction operation level related to the bigger picture
		s32				sub_instr;										// The sub-instruction being executed, such as "+" in "2 + 4", see _SUB_INSTR_* constants
		SOp*			op;												// Any operand data for this node (if it is a terminating node)
		SVariable*		variable;										// As results are computed or referenced, they are stored in scoped/temporary variables
	};

	struct SOp
	{
		u32				op_type;										// The type of operand, see _OP_TYPE_* constants
		SVariable*		variable;										// The actual local variable contents (if it is a converted type at compile time, such as "2" being converted to the integer, referenced as a fixed variable)

		// Pointer to first (if there is a succession)
		union {
			SComp*		comp;											// The first component
			SVariable*	param;											// A parameter reference
			SVariable*	local;											// A local variable reference
			SVariable*	scoped;											// A temporary variable reference used for inter-source-code-line processing
			SVariable*	other;											// Unknown item which must be looked up in the context of the runtime environment
			void*		ptr;											// A general test to see if it exists
		};
		// Number thereafter
		s32				count;											// The number of components (in comp or other) as input
	};

	// Holds a component structure
	struct SComp
	{
		SLL				ll;												// 2-way link list

		// Information about the component
		SEditChain*		line;											// The line this component relates to
		u32				iCode;											// Refer to _VVMMC_COMP_* structs in mc_const.h
		u32				start;											// Start into the indicates line's source code
		s32				length;											// Length of the component

		// If this component has sub-components, they go here
		SStartEnd		childCompsUp;									// Pointer to any child components before the cask name
		SStartEnd		childCompsDown;									// Pointer to any child components after the cask name
	};

	struct SCompCallback
	{
		union {
			SComp*	comp;											// Component at start, and the component to continue processing after upon exit
			s8*			text;											// Raw text (depending on when it is being processed
		};
		u32				length;											// If raw text, the length of the thing being searched, otherwise 0.
		u32				iCode;											// The iCode being queried

		// Callback callbacks for adjustment
		union {
			u32			_insertCompByComp;
			void		(*insertCompByComp)		(SComp* compRef, SComp* compNew, bool tlInsertAfter);
		};
		union {
			u32			_insertCompByParams;
			void		(*insertCompByParams)	(SComp* compRef, SEditChain* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter);
		};
		union {
			u32			_deleteComps;
			void		(*deleteComps)			(SComp* comp, SEditChain* line);
		};
		union {
			u32			_cloneComps;
			SComp*		(*cloneComps)			(SComp* comp, SEditChain* line);
		};
		union {
			u32			_mergeComps;
			SComp*		(*mergeComps)			(SComp* comp, SEditChain* line, u32 tnCount, u32 tniCodeNew);
		};
	};

	struct SStartEndCallback
	{
		union
		{
			u32		_func;
			bool	(*funcBool)	(SStartEndCallback* cb);	// This callback should return false to continue searching, or true when the item is found
			void	(*funcVoid)	(SStartEndCallback* cb);
			//////
			// Uses the following format for the callback:
			//		bool func(SStartEndCallback* cb)
			//////////
		};

		// Data items for this callback
		// Primary pointer
		void*		ptr;

		union {
			// Extra1
			u32			ex1;
			u32			extra1;
			u32			extra;
			u32			count1;
			union {
				u32		count1_1;
				u32		count1_2;
			};
			void*		ex1Ptr;
		};

		union {
			// Extra2
			u32			ex2;
			u32			extra2;
			u32			count2;
			union {
				u32		count2_1;
				u32		count2_2;
			};
			void*		ex2Ptr;
		};
	};

	// For warnings, errors, and notes
	struct SCompileNote
	{
		SCompileNote*	next;											// The next compile note in this chain

		SDatum*			msg;											// The message
		u32				number;											// Related number
		SComp*			relatesTo;										// Column the note occurred on
	};

	// Holds compiler data
	struct SCompiler
	{
		// EC was designed with source code in mind, and that means a tight compiler relationship
		SEditChain*		parent;											// The EC this belongs to (parent->parent points back to ECM)

		// The last source code line
		SDatum*			sourceCode;										// Copy at last compile of LEFT(parent->sourceCode.data, parent->sourceCodePopulated)

		// Components compiled in prior compiler passes
		SComp*			firstComp;										// Pointer to the first component identified on this line

		// Executable code
		SSubInstr**		subInstr;										// Low-level executable code (sub instructions) for this line
		u32				subInstrCount;									// How many sub-instructions there are

		// Results of compilation
		SCompileNote*	errors;											// Noted error
		SCompileNote*	warnings;										// Noted warning
	};


//////////
// Known operators to the system
//////
	const u32		_SUB_INSTR_ADD									= 1;			// Pattern of x + y
	const u32		_SUB_INSTR_SUBTRACT								= 2;			// Pattern of x - y
	const u32		_SUB_INSTR_MULTIPLY								= 3;			// Pattern of x * y
	const u32		_SUB_INSTR_DIVIDE								= 4;			// Pattern of x / y
	const u32		_SUB_INSTR_MODULO								= 5;			// Pattern of x % y
	const u32		_SUB_INSTR_EXPONENT								= 6;			// Pattern of x^y or x**y
	const u32		_SUB_INSTR_FUNCTION								= 7;			// Pattern of xyz(....)
	const u32		_SUB_INSTR_ARRAY								= 8;			// Pattern of array[...]
	const u32		_SUB_INSTR_PLUS_PLUS_X							= 9;			// Pattern of ++x (increment, then get value)
	const u32		_SUB_INSTR_X_PLUS_PLUS							= 10;			// Pattern of x++ (get value, then increment)
	const u32		_SUB_INSTR_MINUS_MINUS_X						= 11;			// Pattern of --x (decrement, then get value)
	const u32		_SUB_INSTR_X_MINUS_MINUS						= 12;			// Pattern of x-- (get value, then decrement)
	const u32		_SUB_INSTR_AND									= 13;			// Pattern of x AND y
	const u32		_SUB_INSTR_OR									= 14;			// Pattern of x OR y
	const u32		_SUB_INSTR_NOT									= 15;			// Pattern of NOT x
	const u32		_SUB_INSTR_DOT_EXPANSION						= 16;			// Pattern of x.y
	const u32		_SUB_INSTR_EXCLAMATION_MARK_EXPANSION			= 17;			// Pattern of x!y
	const u32		_SUB_INSTR_LESS_THAN							= 18;			// Pattern of x < y
	const u32		_SUB_INSTR_GREATER_THAN							= 19;			// Pattern of x > y
	const u32		_SUB_INSTR_LESS_THAN_OR_EQUAL_TO				= 20;			// Pattern of x <= y
	const u32		_SUB_INSTR_GREATER_THAN_OR_EQUAL_TO				= 21;			// Pattern of x >= y
	const u32		_SUB_INSTR_NOT_EQUAL_TO							= 22;			// Pattern of x != y
	const u32		_SUB_INSTR_EQUAL_TO								= 23;			// Pattern of x = y
	const u32		_SUB_INSTR_EXACTLY_EQUAL_TO						= 24;			// Pattern of x == y
	const u32		_SUB_INSTR_FOUND_IN								= 25;			// Pattern of x $ y
	const u32		_SUB_INSTR_NOT_FOUND_IN							= 26;			// Pattern of x !$ y
	const u32		_SUB_INSTR_ERROR								= 1000;			// An error was encountered and we stop at this source code line
	const u32		_SUB_INSTR_FLAGS								= 1001;			// A flag was given for this line

	const u32		_OP_TYPE_COMP									= 1;			// A component
	const u32		_OP_TYPE_PARAM									= 2;			// A parameter
	const u32		_OP_TYPE_LOCAL									= 3;			// A local variable
	const u32		_OP_TYPE_SCOPED									= 4;			// A scoped / temporary variable
	const u32		_OP_TYPE_OTHER									= 5;			// A different variable
	
	const s8		cgcCaskRoundOpenParams[]						= "(||";
	const s8		cgcCaskRoundCloseParams[]						= "||)";
	const s8		cgcCaskSquareOpenParams[]						= "[||";
	const s8		cgcCaskSquareCloseParams[]						= "||]";
	const s8		cgcCaskTriangleOpenParams[]						= "<||";
	const s8		cgcCaskTriangleCloseParams[]					= "||>";
	const s8		cgcCaskTildeOpenParams[]						= "~||";
	const s8		cgcCaskTildeCloseParams[]						= "||~";
	const s8		cgcCaskRoundOpen[]								= "(|";
	const s8		cgcCaskRoundClose[]								= "|)";
	const s8		cgcCaskSquareOpen[]								= "[|";
	const s8		cgcCaskSquareClose[]							= "|]";
	const s8		cgcCaskTriangleOpen[]							= "<|";
	const s8		cgcCaskTriangleClose[]							= "|>";
	const s8		cgcCaskTildeOpen[]								= "~|";
	const s8		cgcCaskTildeClose[]								= "|~";

	const u32		_ICODE_CASK_ROUND_OPEN_PARAMS					= 1000001;
	const u32		_ICODE_CASK_ROUND_CLOSE_PARAMS					= 1000002;
	const u32		_ICODE_CASK_SQUARE_OPEN_PARAMS					= 1000003;
	const u32		_ICODE_CASK_SQUARE_CLOSE_PARAMS					= 1000004;
	const u32		_ICODE_CASK_TRIANGLE_OPEN_PARAMS				= 1000005;
	const u32		_ICODE_CASK_TRIANGLE_CLOSE_PARAMS				= 1000006;
	const u32		_ICODE_CASK_TILDE_OPEN_PARAMS					= 1000007;
	const u32		_ICODE_CASK_TILDE_CLOSE_PARAMS					= 1000008;
	const u32		_ICODE_CASK_ROUND_OPEN							= 1000009;
	const u32		_ICODE_CASK_ROUND_CLOSE							= 1000010;
	const u32		_ICODE_CASK_SQUARE_OPEN							= 1000011;
	const u32		_ICODE_CASK_SQUARE_CLOSE						= 1000012;
	const u32		_ICODE_CASK_TRIANGLE_OPEN						= 1000013;
	const u32		_ICODE_CASK_TRIANGLE_CLOSE						= 1000014;
	const u32		_ICODE_CASK_TILDE_OPEN							= 1000015;
	const u32		_ICODE_CASK_TILDE_CLOSE							= 1000016;

	// Standard types
	const u32		_ICODE_UNKNOWN									= -1;
	const u32		_ICODE_ALPHA									= 1;
	const u32		_ICODE_NUMERIC									= 2;
	const u32		_ICODE_ALPHANUMERIC								= 3;
	const u32		_ICODE_OPERATOR									= 4;
	const u32		_ICODE_WHITESPACE								= 5;
	const u32		_ICODE_PLUS										= 6;
	const u32		_ICODE_HYPHEN									= 7;
	const u32		_ICODE_ASTERISK									= 8;
	const u32		_ICODE_BACKSLASH								= 9;
	const u32		_ICODE_DOUBLE_QUOTE								= 10;
	const u32		_ICODE_SINGLE_QUOTE								= 11;
	const u32		_ICODE_TILDE									= 12;
	const u32		_ICODE_DOT										= 13;
	const u32		_ICODE_COLON									= 14;
	const u32		_ICODE_COMMA									= 15;
	const u32		_ICODE_UNDERSCORE								= 16;
	const u32		_ICODE_AT_SIGN									= 17;
	const u32		_ICODE_QUESTION_MARK							= 18;
	const u32		_ICODE_EXCLAMATION_MARK							= 19;
	const u32		_ICODE_POUND_SIGN								= 20;
	const u32		_ICODE_PERCENT_SIGN								= 21;
	const u32		_ICODE_EXPONENT									= 22;
	const u32		_ICODE_AMPERSAND								= 23;
	const u32		_ICODE_EQUAL_SIGN								= 24;
	const u32		_ICODE_PIPE_SIGN								= 25;
	const u32		_ICODE_REVERSE_QUOTE							= 26;
	const u32		_ICODE_SEMICOLON								= 27;
	const u32		_ICODE_GREATER_THAN								= 28;
	const u32		_ICODE_LESS_THAN								= 30;
	const u32		_ICODE_PARENTHESIS_LEFT							= 31;
	const u32		_ICODE_PARENTHESIS_RIGHT						= 32;
	const u32		_ICODE_BRACKET_LEFT								= 33;
	const u32		_ICODE_BRACKET_RIGHT							= 34;
	const u32		_ICODE_BRACE_LEFT								= 35;
	const u32		_ICODE_BRACE_RIGHT								= 36;
	const u32		_ICODE_SLASH									= 37;
	const u32		_ICODE_FOUND_IN									= 38;
	const u32		_ICODE_PLUS_PLUS								= 39;
	const u32		_ICODE_MINUS_MINUS								= 40;
	const u32		_ICODE_NOT_EQUAL								= 41;
	const u32		_ICODE_LESS_THAN_OR_EQUAL_TO					= 42;
	const u32		_ICODE_GREATER_THAN_OR_EQUAL_TO					= 43;
	const u32		_ICODE_EXACTLY_EQUAL_TO							= 44;
	const u32		_ICODE_NOT_FOUND_IN								= 45;
	const u32		_ICODE_SHIFT_LEFT								= 46;
	const u32		_ICODE_SHIFT_RIGHT								= 47;
	const u32		_ICODE_SHIFT_LEFT_ASSIGNMENT					= 48;
	const u32		_ICODE_SHIFT_RIGHT_ASSIGNMENT					= 49;

	// Combined items
	const u32		_ICODE_SINGLE_QUOTED_TEXT						= 90;
	const u32		_ICODE_DOUBLE_QUOTED_TEXT						= 91;

	// Preprocessor
	const u32		_ICODE_INCLUDE									= 101;
	const u32		_ICODE_DEFINE									= 102;

	// Miscellaneous
	const u32		_ICODE_COMMENT									= 103;
	const u32		_ICODE_LINE_COMMENT								= 104;

	// VJr-specific Keywords
	const u32		_ICODE_VJR										= 200;
	const u32		_ICODE_CMD										= 201;
	const u32		_ICODE_JDEBI									= 202;
	const u32		_ICODE_PROTECTED								= 203;
	const u32		_ICODE_MAIN										= 204;
	const u32		_ICODE_LOAD_LAST_FROM_VJR_USER_DBF				= 205;
	const u32		_ICODE_FLAGS									= 206;
	const u32		_ICODE_META										= 207;
	const u32		_ICODE_MEFA										= 208;
	const u32		_ICODE_MERA										= 209;
	const u32		_ICODE_MEMA										= 210;
	const u32		_ICODE_METAICASE								= 211;
	const u32		_ICODE_MEFAICASE								= 212;
	const u32		_ICODE_MERAICASE								= 213;
	const u32		_ICODE_MEMAICASE								= 214;
	const u32		_ICODE_FLOW										= 215;
	const u32		_ICODE_SUBFLOW									= 216;
	const u32		_ICODE_FLOWTO									= 217;
	const u32		_ICODE_FLOWOUT									= 218;
	const u32		_ICODE_RGBA										= 219;
    const u32       _ICODE_LOBJECT								    = 220;
	const u32		_ICODE_PARAMS									= 221;
	const u32		_ICODE_RETURNS									= 222;
	const u32		_ICODE_AS										= 223;
	const u32		_ICODE_CHARACTER								= 224;
	const u32		_ICODE_INTEGER									= 225;
	const u32		_ICODE_FLOAT									= 226;
	const u32		_ICODE_DOUBLE									= 227;
	const u32		_ICODE_LOGICAL									= 228;
	const u32		_ICODE_S32										= 229;
	const u32		_ICODE_S64										= 230;
	const u32		_ICODE_U32										= 231;
	const u32		_ICODE_U64										= 232;
	const u32		_ICODE_F32										= 233;
	const u32		_ICODE_F64										= 234;
	const u32		_ICODE_BI										= 235;
	const u32		_ICODE_BFP										= 236;
	const u32		_ICODE_S16										= 237;
	const u32		_ICODE_S8										= 238;
	const u32		_ICODE_U16										= 239;
	const u32		_ICODE_U8										= 240;


	// Logical operators
	const u32		_ICODE_NOT										= 500;
	const u32		_ICODE_AND										= 501;
	const u32		_ICODE_OR										= 502;

	// Functions
	const u32		_ICODE_ABS										= 1000;
	const u32		_ICODE_ACLASS                                   = 1001;
	const u32		_ICODE_ACOPY                                    = 1002;
	const u32		_ICODE_ACOS                                     = 1003;
	const u32		_ICODEADATABASES_                               = 1004;
	const u32		_ICODEADBOBJECTS_                               = 1005;
	const u32		_ICODE_ADDBS                                    = 1006;
	const u32		_ICODE_ADDPROPERTY                              = 1007;
	const u32		_ICODE_ADEL                                     = 1008;
	const u32		_ICODE_ADIR                                     = 1009;
	const u32		_ICODE_ADLLS                                    = 1010;
	const u32		_ICODE_ADOCKSTATE                               = 1011;
	const u32		_ICODE_AELEMENT                                 = 1012;
	const u32		_ICODE_AERROR                                   = 1013;
	const u32		_ICODE_AEVENTS                                  = 1014;
	const u32		_ICODE_AFIELDS                                  = 1015;
	const u32		_ICODE_AFONT                                    = 1016;
	const u32		_ICODE_AGETCLASS                                = 1017;
	const u32		_ICODE_AGETFILEVERSION                          = 1018;
	const u32		_ICODE_AINSTANCE                                = 1019;
	const u32		_ICODE_AINS                                     = 1020;
	const u32		_ICODE_ALANGUAGE                                = 1021;
	const u32		_ICODE_ALEN                                     = 1022;
	const u32		_ICODE_ALIAS                                    = 1023;
	const u32		_ICODE_ALINES                                   = 1024;
	const u32		_ICODE_ALLTRIM                                  = 1025;
	const u32		_ICODE_AMEMBERS                                 = 1026;
	const u32		_ICODE_AMOUSEOBJ                                = 1027;
	const u32		_ICODE_ANETRESOURCES                            = 1028;
	const u32		_ICODE_APRINTERS                                = 1029;
	const u32		_ICODE_APROCINFO                                = 1030;
	const u32		_ICODE_ASCAN                                    = 1031;
	const u32		_ICODE_ASC                                      = 1032;
	const u32		_ICODE_ASELOBJ                                  = 1033;
	const u32		_ICODE_ASESSIONS                                = 1034;
	const u32		_ICODE_ASIN                                     = 1035;
	const u32		_ICODE_ASORT                                    = 1036;
	const u32		_ICODE_ASQLHANDLES                              = 1037;
	const u32		_ICODE_ASTACKINFO                               = 1038;
	const u32		_ICODE_ASUBSCRIPT                               = 1039;
	const u32		_ICODE_AT_C                                     = 1040;
	const u32		_ICODE_AT                                       = 1041;
	const u32		_ICODE_ATAGINFO                                 = 1042;
	const u32		_ICODE_ATAN                                     = 1043;
	const u32		_ICODE_ATCLINE                                  = 1044;
	const u32		_ICODE_ATCC                                     = 1045;
	const u32		_ICODE_ATC                                      = 1046;
	const u32		_ICODE_ATLINE                                   = 1047;
	const u32		_ICODE_ATN2                                     = 1048;
	const u32		_ICODE_AUSED                                    = 1049;
	const u32		_ICODE_AVCXCLASSES                              = 1050;
	const u32		_ICODE_BARPROMPT                                = 1051;
	const u32		_ICODE_BARCOUNT                                 = 1052;
	const u32		_ICODE_BAR                                      = 1053;
	const u32		_ICODE_BETWEEN                                  = 1054;
	const u32		_ICODE_BINDEVENT                                = 1055;
	const u32		_ICODE_BINTOC                                   = 1056;
	const u32		_ICODE_BITAND                                   = 1057;
	const u32		_ICODE_BITCLEAR                                 = 1058;
	const u32		_ICODE_BITLSHIFT                                = 1059;
	const u32		_ICODE_BITNOT                                   = 1060;
	const u32		_ICODE_BITOR                                    = 1061;
	const u32		_ICODE_BITRSHIFT                                = 1062;
	const u32		_ICODE_BITSET                                   = 1063;
	const u32		_ICODE_BITTEST                                  = 1064;
	const u32		_ICODE_BITXOR                                   = 1065;
	const u32		_ICODE_BOF                                      = 1066;
	const u32		_ICODE_CANDIDATE                                = 1067;
	const u32		_ICODE_CAPSLOCK                                 = 1068;
	const u32		_ICODE_CAST                                     = 1069;
	const u32		_ICODE_CDOW                                     = 1070;
	const u32		_ICODE_CDX                                      = 1071;
	const u32		_ICODE_CEILING                                  = 1072;
	const u32		_ICODE_CHR                                      = 1073;
	const u32		_ICODE_CHRSAW                                   = 1074;
	const u32		_ICODE_CHRTRANC                                 = 1075;
	const u32		_ICODE_CHRTRAN                                  = 1076;
	const u32		_ICODE_CLEARRESULTSET                           = 1077;
	const u32		_ICODE_CMONTH                                   = 1078;
	const u32		_ICODE_CNTBAR                                   = 1079;
	const u32		_ICODE_CNTPAD                                   = 1080;
	const u32		_ICODE_COL                                      = 1081;
	const u32		_ICODE_COMARRAY                                 = 1082;
	const u32		_ICODE_COMCLASSINFO                             = 1083;
	const u32		_ICODE_COMMAND                                  = 1084;
	const u32		_ICODE_COMPOBJ                                  = 1085;
	const u32		_ICODE_COMPROP                                  = 1086;
	const u32		_ICODE_COMRETURNERROR                           = 1087;
	const u32		_ICODE_COMS                                     = 1088;
	const u32		_ICODE_COS                                      = 1089;
	const u32		_ICODE_CPCONVERT                                = 1090;
	const u32		_ICODE_CPCURRENT                                = 1091;
	const u32		_ICODE_CPDBF                                    = 1092;
	const u32		_ICODE_CREATEBINARY                             = 1093;
	const u32		_ICODE_CREATEOBJECT                             = 1094;
	const u32		_ICODE_CREATEOBJECTEX                           = 1095;
	const u32		_ICODE_CREATEOFFLINE                            = 1096;
	const u32		_ICODE_CTOBIN                                   = 1097;
	const u32		_ICODE_CTOD                                     = 1098;
	const u32		_ICODE_CTOT                                     = 1099;
	const u32		_ICODE_CURDIR                                   = 1100;
	const u32		_ICODE_CURSORGETPROP                            = 1101;
	const u32		_ICODE_CURSORSETPROP                            = 1102;
	const u32		_ICODE_CURSORTOXML                              = 1103;
	const u32		_ICODE_CURVAL                                   = 1104;
	const u32		_ICODE_DATETIME                                 = 1105;
	const u32		_ICODE_DATE                                     = 1106;
	const u32		_ICODE_DAY                                      = 1107;
	const u32		_ICODE_DBC                                      = 1108;
	const u32		_ICODE_DBF                                      = 1109;
	const u32		_ICODE_DBGETPROP                                = 1110;
	const u32		_ICODE_DBSETPROP                                = 1111;
	const u32		_ICODE_DBUSED                                   = 1112;
	const u32		_ICODE_DDEABORTTRANS                            = 1113;
	const u32		_ICODE_DDEADVISE                                = 1114;
	const u32		_ICODE_DDEENABLED                               = 1115;
	const u32		_ICODE_DDEEXECUTE                               = 1116;
	const u32		_ICODE_DDEINITIATE                              = 1117;
	const u32		_ICODE_DDELASTERROR                             = 1118;
	const u32		_ICODE_DDEPOKE                                  = 1119;
	const u32		_ICODE_DDEREQUEST                               = 1120;
	const u32		_ICODE_DDES                                     = 1121;
	const u32		_ICODE_DDESETOPTION                             = 1122;
	const u32		_ICODE_DDESETSERVICE                            = 1123;
	const u32		_ICODE_DDESETTOPIC                              = 1124;
	const u32		_ICODE_DDETERMINATE                             = 1125;
	const u32		_ICODE_DEFAULTEXT                               = 1126;
	const u32		_ICODE_DELETED                                  = 1127;
	const u32		_ICODE_DESCENDING                               = 1128;
	const u32		_ICODE_DIFFERENCE                               = 1129;
	const u32		_ICODE_DIRECTORY                                = 1130;
	const u32		_ICODE_DISKSPACE                                = 1131;
	const u32		_ICODE_DISPLAYPATH                              = 1132;
	const u32		_ICODE_DMY                                      = 1133;
	const u32		_ICODE_DODEFAULT                                = 1134;
	const u32		_ICODE_DOW                                      = 1135;
	const u32		_ICODE_DRIVETYPE                                = 1136;
	const u32		_ICODE_DROPOFFLINE                              = 1137;
	const u32		_ICODE_DTOC                                     = 1138;
	const u32		_ICODE_DTOR                                     = 1139;
	const u32		_ICODE_DTOS                                     = 1140;
	const u32		_ICODE_DTOT                                     = 1141;
	const u32		_ICODE_EDITSOURCE                               = 1142;
	const u32		_ICODE_EMPTY                                    = 1143;
	const u32		_ICODE_EOF                                      = 1144;
	const u32		_ICODE_ERROR                                    = 1145;
	const u32		_ICODE_EVALUATE                                 = 1146;
	const u32		_ICODE_EVENTHANDLER                             = 1147;
	const u32		_ICODE_EVL                                      = 1148;
	const u32		_ICODE_EXECSCRIPT                               = 1149;
	const u32		_ICODE_EXP                                      = 1150;
	const u32		_ICODE_FCHSIZE                                  = 1151;
	const u32		_ICODE_FCLOSE                                   = 1152;
	const u32		_ICODE_FCOUNT                                   = 1153;
	const u32		_ICODE_FCREATE                                  = 1154;
	const u32		_ICODE_FDATE                                    = 1155;
	const u32		_ICODE_FEOF                                     = 1156;
	const u32		_ICODE_FERROR                                   = 1157;
	const u32		_ICODE_FFLUSH                                   = 1158;
	const u32		_ICODE_FGETS                                    = 1159;
	const u32		_ICODE_FIELD                                    = 1160;
	const u32		_ICODE_FILETOSTR                                = 1161;
	const u32		_ICODE_FILE                                     = 1162;
	const u32		_ICODE_FILTER                                   = 1163;
	const u32		_ICODE_FKLABEL                                  = 1164;
	const u32		_ICODE_FKMAX                                    = 1165;
	const u32		_ICODE_FLDLIST                                  = 1166;
	const u32		_ICODE_FLOCK                                    = 1167;
	const u32		_ICODE_FLOOR                                    = 1168;
	const u32		_ICODE_FONTMETRIC                               = 1169;
	const u32		_ICODE_FOPEN                                    = 1170;
	const u32		_ICODE_FOR                                      = 1171;
	const u32		_ICODE_FORCEEXT                                 = 1172;
	const u32		_ICODE_FORCEPATH                                = 1173;
	const u32		_ICODE_FOUND                                    = 1174;
	const u32		_ICODE_FPUTS                                    = 1175;
	const u32		_ICODE_FREAD                                    = 1176;
	const u32		_ICODE_FSEEK                                    = 1177;
	const u32		_ICODE_FSIZE                                    = 1178;
	const u32		_ICODE_FTIME                                    = 1179;
	const u32		_ICODE_FULLPATH                                 = 1180;
	const u32		_ICODE_FV                                       = 1181;
	const u32		_ICODE_FWRITE                                   = 1182;
	const u32		_ICODE_GETAUTOINCVALUE                          = 1183;
	const u32		_ICODE_GETBAR                                   = 1184;
	const u32		_ICODE_GETCOLOR                                 = 1185;
	const u32		_ICODE_GETCP                                    = 1186;
	const u32		_ICODE_GETCURSORADAPTER                         = 1187;
	const u32		_ICODE_GETDIR                                   = 1188;
	const u32		_ICODE_GETENV                                   = 1189;
	const u32		_ICODE_GETFILE                                  = 1190;
	const u32		_ICODE_GETFLDSTATE                              = 1191;
	const u32		_ICODE_GETFONT                                  = 1192;
	const u32		_ICODE_GETINTERFACE                             = 1193;
	const u32		_ICODE_GETNEXTMODIFIED                          = 1194;
	const u32		_ICODE_GETOBJECT                                = 1195;
	const u32		_ICODE_GETPAD                                   = 1196;
	const u32		_ICODE_GETPEM                                   = 1197;
	const u32		_ICODE_GETPICT                                  = 1198;
	const u32		_ICODE_GETPRINTER                               = 1199;
	const u32		_ICODE_GETRESULTSET                             = 1200;
	const u32		_ICODE_GETWORDCOUNT                             = 1201;
	const u32		_ICODE_GETWORDNUM                               = 1202;
	const u32		_ICODE_GOMONTH                                  = 1203;
	const u32		_ICODE_HEADER                                   = 1204;
	const u32		_ICODE_HOME                                     = 1205;
	const u32		_ICODE_HOUR                                     = 1206;
	const u32		_ICODE_ICASE                                    = 1207;
	const u32		_ICODE_IDXCOLLATE                               = 1208;
	const u32		_ICODE_IIF                                      = 1209;
	const u32		_ICODE_IMESTATUS                                = 1210;
	const u32		_ICODE_INDBC                                    = 1211;
	const u32		_ICODE_INDEXSEEK                                = 1212;
	const u32		_ICODE_INKEY                                    = 1213;
	const u32		_ICODE_INLIST                                   = 1214;
	const u32		_ICODE_INPUTBOX                                 = 1215;
	const u32		_ICODE_INSMODE                                  = 1216;
	const u32		_ICODE_INT                                      = 1217;
	const u32		_ICODE_ISALPHA                                  = 1218;
	const u32		_ICODE_ISBLANK                                  = 1219;
	const u32		_ICODE_ISCOLOR                                  = 1220;
	const u32		_ICODE_ISDIGIT                                  = 1221;
	const u32		_ICODE_ISEXCLUSIVE                              = 1222;
	const u32		_ICODE_ISFLOCKED                                = 1223;
	const u32		_ICODE_ISLEADBYTE                               = 1224;
	const u32		_ICODE_ISLOWER                                  = 1225;
	const u32		_ICODE_ISMEMOFETCHED                            = 1226;
	const u32		_ICODE_ISMOUSE                                  = 1227;
	const u32		_ICODE_ISNULL                                   = 1228;
	const u32		_ICODE_ISPEN                                    = 1229;
	const u32		_ICODE_ISREADONLY                               = 1230;
	const u32		_ICODE_ISRLOCKED                                = 1231;
	const u32		_ICODE_ISTRANSACTABLE                           = 1232;
	const u32		_ICODE_ISUPPER                                  = 1233;
	const u32		_ICODE_JUSTDRIVE                                = 1234;
	const u32		_ICODE_JUSTEXT                                  = 1235;
	const u32		_ICODE_JUSTFNAME                                = 1236;
	const u32		_ICODE_JUSTPATH                                 = 1237;
	const u32		_ICODE_JUSTSTEM                                 = 1238;
	const u32		_ICODE_KEYMATCH                                 = 1239;
	const u32		_ICODE_KEY                                      = 1240;
	const u32		_ICODE_LASTKEY                                  = 1241;
	const u32		_ICODE_LEFTC                                    = 1242;
	const u32		_ICODE_LEFT                                     = 1243;
	const u32		_ICODE_LENC                                     = 1244;
	const u32		_ICODE_LEN                                      = 1245;
	const u32		_ICODE_LIKEC                                    = 1246;
	const u32		_ICODE_LIKE                                     = 1247;
	const u32		_ICODE_LINENO                                   = 1248;
	const u32		_ICODE_LOADPICTURE                              = 1249;
	const u32		_ICODE_LOCFILE                                  = 1250;
	const u32		_ICODE_LOCK                                     = 1251;
	const u32		_ICODE_LOG10                                    = 1252;
	const u32		_ICODE_LOG                                      = 1253;
	const u32		_ICODE_LOOKUP                                   = 1254;
	const u32		_ICODE_LOWER                                    = 1255;
	const u32		_ICODE_LTRIM                                    = 1256;
	const u32		_ICODE_LUPDATE                                  = 1257;
	const u32		_ICODE_MAKETRANSACTABLE                         = 1258;
	const u32		_ICODE_MAX                                      = 1259;
	const u32		_ICODE_MCOL                                     = 1260;
	const u32		_ICODE_MDOWN                                    = 1261;
	const u32		_ICODE_MDX                                      = 1262;
	const u32		_ICODE_MDY                                      = 1263;
	const u32		_ICODE_MEMLINES                                 = 1264;
	const u32		_ICODE_MEMORY                                   = 1265;
	const u32		_ICODE_MENU                                     = 1266;
	const u32		_ICODE_MESSAGEBOX                               = 1267;
	const u32		_ICODE_MESSAGE                                  = 1268;
	const u32		_ICODE_MINUTE                                   = 1269;
	const u32		_ICODE_MIN                                      = 1270;
	const u32		_ICODE_MLINE                                    = 1271;
	const u32		_ICODE_MOD                                      = 1272;
	const u32		_ICODE_MONTH                                    = 1273;
	const u32		_ICODE_MRKBAR                                   = 1274;
	const u32		_ICODE_MRKPAD                                   = 1275;
	const u32		_ICODE_MROW                                     = 1276;
	const u32		_ICODE_MTON                                     = 1277;
	const u32		_ICODE_MWINDOW                                  = 1278;
	const u32		_ICODE_NDX                                      = 1279;
	const u32		_ICODE_NEWOBJECT                                = 1280;
	const u32		_ICODE_NORMALIZE                                = 1281;
	const u32		_ICODE_NTOM                                     = 1282;
	const u32		_ICODE_NUMLOCK                                  = 1283;
	const u32		_ICODE_NVL                                      = 1284;
	const u32		_ICODE_OBJNUM                                   = 1285;
	const u32		_ICODE_OBJTOCLIENT                              = 1286;
	const u32		_ICODE_OBJVAR                                   = 1287;
	const u32		_ICODE_OCCURS                                   = 1288;
	const u32		_ICODE_OEMTOANSI                                = 1289;
	const u32		_ICODE_OLDVAL                                   = 1290;
	const u32		_ICODE_ON                                       = 1291;
	const u32		_ICODE_ORDER                                    = 1292;
	const u32		_ICODE_OS                                       = 1293;
	const u32		_ICODE_OVERVIEW                                 = 1294;
	const u32		_ICODE_PADC                                     = 1295;
	const u32		_ICODE_PADL                                     = 1296;
	const u32		_ICODE_PADR                                     = 1297;
	const u32		_ICODE_PAD                                      = 1298;
	const u32		_ICODE_PARAMETERS                               = 1299;
	const u32		_ICODE_PAYMENT                                  = 1300;
	const u32		_ICODE_PCOL                                     = 1301;
	const u32		_ICODE_PCOUNT                                   = 1302;
	const u32		_ICODE_PEMSTATUS                                = 1303;
	const u32		_ICODE_PI                                       = 1304;
	const u32		_ICODE_POPUP                                    = 1305;
	const u32		_ICODE_PRIMARY                                  = 1306;
	const u32		_ICODE_PRINTSTATUS                              = 1307;
	const u32		_ICODE_PRMBAR                                   = 1308;
	const u32		_ICODE_PRMPAD                                   = 1309;
	const u32		_ICODE_PROGRAM                                  = 1310;
	const u32		_ICODE_PROMPT                                   = 1311;
	const u32		_ICODE_PROPER                                   = 1312;
	const u32		_ICODE_PROW                                     = 1313;
	const u32		_ICODE_PRTINFO                                  = 1314;
	const u32		_ICODE_PUTFILE                                  = 1315;
	const u32		_ICODE_PV                                       = 1316;
	const u32		_ICODE_QUARTER                                  = 1317;
	const u32		_ICODE_RAISEEVENT                               = 1318;
	const u32		_ICODE_RAND                                     = 1319;
	const u32		_ICODE_RATC                                     = 1320;
	const u32		_ICODE_RAT                                      = 1321;
	const u32		_ICODE_RATLINE                                  = 1322;
	const u32		_ICODE_RDLEVEL                                  = 1323;
	const u32		_ICODE_READKEY                                  = 1324;
	const u32		_ICODE_RECCOUNT                                 = 1325;
	const u32		_ICODE_RECNO                                    = 1326;
	const u32		_ICODE_RECSIZE                                  = 1327;
	const u32		_ICODE_REFRESH                                  = 1328;
	const u32		_ICODE_RELATION                                 = 1329;
	const u32		_ICODE_REPLICATE                                = 1330;
	const u32		_ICODE_REQUERY                                  = 1331;
	const u32		_ICODE_RGB                                      = 1332;
	const u32		_ICODE_RGBSCHEME                                = 1333;
	const u32		_ICODE_RIGHT                                    = 1334;
	const u32		_ICODE_RIGHTC                                   = 1335;
	const u32		_ICODE_RLOCK                                    = 1336;
	const u32		_ICODE_ROUND                                    = 1337;
	const u32		_ICODE_ROW                                      = 1338;
	const u32		_ICODE_RTOD                                     = 1339;
	const u32		_ICODE_RTRIM                                    = 1340;
	const u32		_ICODE_SAVEPICTURE                              = 1341;
	const u32		_ICODE_SCHEME                                   = 1342;
	const u32		_ICODE_SCOLS                                    = 1343;
	const u32		_ICODE_SECONDS                                  = 1344;
	const u32		_ICODE_SEC                                      = 1345;
	const u32		_ICODE_SEEK                                     = 1346;
	const u32		_ICODE_SELECT                                   = 1347;
	const u32		_ICODE_SET                                      = 1348;
	const u32		_ICODE_SETFLDSTATE                              = 1349;
	const u32		_ICODE_SETRESULTSET                             = 1350;
	const u32		_ICODE_SIGN                                     = 1351;
	const u32		_ICODE_SIN                                      = 1352;
	const u32		_ICODE_SKPBAR                                   = 1353;
	const u32		_ICODE_SKPPAD                                   = 1354;
	const u32		_ICODE_SOUNDEX                                  = 1355;
	const u32		_ICODE_SPACE                                    = 1356;
	const u32		_ICODE_SQLCANCEL                                = 1357;
	const u32		_ICODE_SQLCOLUMNS                               = 1358;
	const u32		_ICODE_SQLCOMMIT                                = 1359;
	const u32		_ICODE_SQLCONNECT                               = 1360;
	const u32		_ICODE_SQLDISCONNECT                            = 1361;
	const u32		_ICODE_SQLEXEC                                  = 1362;
	const u32		_ICODE_SQLGETPROP                               = 1363;
	const u32		_ICODE_SQLIDLEDISCONNECT                        = 1364;
	const u32		_ICODE_SQLMORERESULTS                           = 1365;
	const u32		_ICODE_SQLPREPARE                               = 1366;
	const u32		_ICODE_SQLROLLBACK                              = 1367;
	const u32		_ICODE_SQLSETPROP                               = 1368;
	const u32		_ICODE_SQLSTRINGCONNECT                         = 1369;
	const u32		_ICODE_SQLTABLES                                = 1370;
	const u32		_ICODE_SQRT                                     = 1371;
	const u32		_ICODE_SROWS                                    = 1372;
	const u32		_ICODE_STRCONV                                  = 1373;
	const u32		_ICODE_STREXTRACT                               = 1374;
	const u32		_ICODE_STRTOFILE                                = 1375;
	const u32		_ICODE_STRTRAN                                  = 1376;
	const u32		_ICODE_STR                                      = 1377;
	const u32		_ICODE_STUFFC                                   = 1378;
	const u32		_ICODE_STUFF                                    = 1379;
	const u32		_ICODE_SUBSTRC                                  = 1380;
	const u32		_ICODE_SUBSTR                                   = 1381;
	const u32		_ICODE_SYSMETRIC                                = 1382;
	const u32		_ICODE_SYS                                      = 1383;
	const u32		_ICODE_TABLEREVERT                              = 1384;
	const u32		_ICODE_TABLEUPDATE                              = 1385;
	const u32		_ICODE_TAG                                      = 1386;
	const u32		_ICODE_TAGCOUNT                                 = 1387;
	const u32		_ICODE_TAGNO                                    = 1388;
	const u32		_ICODE_TAN                                      = 1389;
	const u32		_ICODE_TARGET                                   = 1390;
	const u32		_ICODE_TEXTMERGE                                = 1391;
	const u32		_ICODE_TIME                                     = 1392;
	const u32		_ICODE_TRANSFORM                                = 1393;
	const u32		_ICODE_TRIM                                     = 1394;
	const u32		_ICODE_TTOC                                     = 1395;
	const u32		_ICODE_TTOD                                     = 1396;
	const u32		_ICODE_TXNLEVEL                                 = 1397;
	const u32		_ICODE_TXTWIDTH                                 = 1398;
	const u32		_ICODE_TYPE                                     = 1399;
	const u32		_ICODE_UNBINDEVENTS                             = 1400;
	const u32		_ICODE_UNIQUE                                   = 1401;
	const u32		_ICODE_UPDATED                                  = 1402;
	const u32		_ICODE_UPPER                                    = 1403;
	const u32		_ICODE_USED                                     = 1404;
	const u32		_ICODE_VAL                                      = 1405;
	const u32		_ICODE_VARREAD                                  = 1406;
	const u32		_ICODE_VARTYPE                                  = 1407;
	const u32		_ICODE_VERSION                                  = 1408;
	const u32		_ICODE_WBORDER                                  = 1409;
	const u32		_ICODE_WCHILD                                   = 1410;
	const u32		_ICODE_WCOLS                                    = 1411;
	const u32		_ICODE_WDOCKABLE                                = 1412;
	const u32		_ICODE_WEEK                                     = 1413;
	const u32		_ICODE_WEXIST                                   = 1414;
	const u32		_ICODE_WFONT                                    = 1415;
	const u32		_ICODE_WLAST                                    = 1416;
	const u32		_ICODE_WLCOL                                    = 1417;
	const u32		_ICODE_WLROW                                    = 1418;
	const u32		_ICODE_WMAXIMUM                                 = 1419;
	const u32		_ICODE_WMINIMUM                                 = 1420;
	const u32		_ICODE_WONTOP                                   = 1421;
	const u32		_ICODE_WOUTPUT                                  = 1422;
	const u32		_ICODE_WPARENT                                  = 1423;
	const u32		_ICODE_WREAD                                    = 1424;
	const u32		_ICODE_WROWS                                    = 1425;
	const u32		_ICODE_WTITLE                                   = 1426;
	const u32		_ICODE_WVISIBLE                                 = 1427;
	const u32		_ICODE_XMLTOCURSOR                              = 1428;
	const u32		_ICODE_XMLUPDATEGRAM                            = 1429;
	const u32		_ICODE_YEAR                                     = 1430;

	// Commands
	const u32       _ICODE_ACTIVATE                                 = 2000;
	const u32       _ICODE_ADD                                      = 2001;
	const u32       _ICODE_ALTER                                    = 2002;
	const u32       _ICODE_ALTERNATE                                = 2003;
	const u32       _ICODE_ANSI                                     = 2004;
	const u32       _ICODE_APP                                      = 2005;
	const u32       _ICODE_APPEND                                   = 2006;
	const u32       _ICODE_ARRAY                                    = 2007;
	const u32       _ICODE_ASSERTS                                  = 2008;
	const u32       _ICODE_ASSERT                                   = 2009;
	const u32       _ICODE_ASSIST                                   = 2010;
	const u32       _ICODE_AUTOINCERROR                             = 2011;
	const u32       _ICODE_AUTOSAVE                                 = 2012;
	const u32       _ICODE_AVERAGE                                  = 2013;
	const u32       _ICODE_BEGIN                                    = 2014;
	const u32       _ICODE_BELL                                     = 2015;
	const u32       _ICODE_BLANK                                    = 2016;
	const u32       _ICODE_BLOCKSIZE                                = 2017;
	const u32       _ICODE_BORDER                                   = 2018;
	const u32       _ICODE_BOX                                      = 2019;
	const u32       _ICODE_BROWSE                                   = 2020;
	const u32       _ICODE_BROWSEIME                                = 2021;
	const u32       _ICODE_BRSTATUS                                 = 2022;
	const u32       _ICODE_BUILD                                    = 2023;
	const u32       _ICODE_CALCULATE                                = 2024;
	const u32       _ICODE_CALL                                     = 2025;
	const u32       _ICODE_CANCEL                                   = 2026;
	const u32       _ICODE_CARRY                                    = 2027;
	const u32       _ICODE_CASE                                     = 2028;
	const u32       _ICODE_CATCH                                    = 2029;
	const u32       _ICODE_CD                                       = 2030;
	const u32       _ICODE_CENTURY                                  = 2031;
	const u32       _ICODE_CHANGE                                   = 2032;
	const u32       _ICODE_CHDIR                                    = 2033;
	const u32       _ICODE_CLASS                                    = 2034;
	const u32       _ICODE_CLASSLIB                                 = 2035;
	const u32       _ICODE_CLEAR                                    = 2036;
	const u32       _ICODE_CLEARS                                   = 2037;
	const u32       _ICODE_CLOCK                                    = 2038;
	const u32       _ICODE_CLOSE                                    = 2039;
	const u32       _ICODE_CLOSES                                   = 2040;
	const u32       _ICODE_COLLATE                                  = 2041;
	const u32       _ICODE_COLOR                                    = 2042;
	const u32       _ICODE_COMPATIBLE                               = 2043;
	const u32       _ICODE_COMPILE                                  = 2044;
	const u32       _ICODE_CONFIRM                                  = 2045;
	const u32       _ICODE_CONNECTION                               = 2046;
	const u32       _ICODE_CONNECTIONS                              = 2047;
	const u32       _ICODE_CONSOLE                                  = 2048;
	const u32       _ICODE_CONTINUE                                 = 2049;
	const u32       _ICODE_COPY                                     = 2050;
	const u32       _ICODE_COUNT                                    = 2051;
	const u32       _ICODE_COVERAGE                                 = 2052;
	const u32       _ICODE_CPCOMPILE                                = 2053;
	const u32       _ICODE_CPDIALOG                                 = 2054;
	const u32       _ICODE_CREATE                                   = 2055;
	const u32       _ICODE_CURRENCY                                 = 2056;
	const u32       _ICODE_CURSOR                                   = 2057;
	const u32       _ICODE_DATABASE                                 = 2058;
	const u32       _ICODE_DATASESSION                              = 2059;
	const u32       _ICODE_DEACTIVATE                               = 2060;
	const u32       _ICODE_DEBUG                                    = 2061;
	const u32       _ICODE_DEBUGOUT                                 = 2062;
	const u32       _ICODE_DECIMALS                                 = 2063;
	const u32       _ICODE_DECLARE                                  = 2064;
	const u32       _ICODE_DEFAULT                                  = 2065;
	const u32       _ICODE_DELETE                                   = 2066;
	const u32       _ICODE_DELIMITERS                               = 2067;
	const u32       _ICODE_DEVELOPMENT                              = 2068;
	const u32       _ICODE_DEVICE                                   = 2069;
	const u32       _ICODE_DIMENSION                                = 2070;
	const u32       _ICODE_DIR                                      = 2071;
	const u32       _ICODE_DISPLAY                                  = 2072;
	const u32       _ICODE_DLLS                                     = 2073;
	const u32       _ICODE_DLL                                      = 2074;
	const u32       _ICODE_DO                                       = 2075;
	const u32       _ICODE_DOCK                                     = 2076;
	const u32       _ICODE_DOEVENTS                                 = 2077;
	const u32       _ICODE_DOHISTORY                                = 2078;
	const u32       _ICODE_DROP                                     = 2079;
	const u32       _ICODE_EACH                                     = 2080;
	const u32       _ICODE_ECHO                                     = 2081;
	const u32       _ICODE_EDIT                                     = 2082;
	const u32       _ICODE_EJECT                                    = 2083;
	const u32       _ICODE_END                                      = 2084;
	const u32       _ICODE_ENDCASE                                  = 2085;
	const u32       _ICODE_ENDDO                                    = 2086;
	const u32       _ICODE_ENDFOR                                   = 2087;
	const u32       _ICODE_ENDIF                                    = 2088;
	const u32       _ICODE_ENDPRINTJOB                              = 2089;
	const u32       _ICODE_ENDSCAN                                  = 2090;
	const u32       _ICODE_ENDTEXT                                  = 2091;
	const u32       _ICODE_ENDWITH                                  = 2092;
	const u32       _ICODE_ENGINEBEHAVIOR                           = 2093;
	const u32       _ICODE_ERASE                                    = 2094;
	const u32       _ICODE_ESCAPE                                   = 2095;
	const u32       _ICODE_EVENTLIST                                = 2096;
	const u32       _ICODE_EVENTS                                   = 2097;
	const u32       _ICODE_EVENTTRACKING                            = 2098;
	const u32       _ICODE_EXACT                                    = 2099;
	const u32       _ICODE_EXCLUSIVE                                = 2100;
	const u32       _ICODE_EXE                                      = 2101;
	const u32       _ICODE_EXIT                                     = 2102;
	const u32       _ICODE_EXPORT                                   = 2103;
	const u32       _ICODE_EXTENDED                                 = 2104;
	const u32       _ICODE_EXTERNAL                                 = 2105;
	const u32       _ICODE_FDOW                                     = 2106;
	const u32       _ICODE_FIELDS                                   = 2107;
	const u32       _ICODE_FILES                                    = 2108;
	const u32       _ICODE_FILL                                     = 2109;
	const u32       _ICODE_FINALLY                                  = 2110;
	const u32       _ICODE_FIND                                     = 2111;
	const u32       _ICODE_FIXED                                    = 2112;
	const u32       _ICODE_FLUSH                                    = 2113;
	const u32       _ICODE_FORMAT                                   = 2114;
	const u32       _ICODE_FORM                                     = 2115;
	const u32       _ICODE_FREE                                     = 2116;
	const u32       _ICODE_FROM                                     = 2117;
	const u32       _ICODE_FUNCTION                                 = 2118;
	const u32       _ICODE_FWEEK                                    = 2119;
	const u32       _ICODE_GATHER                                   = 2120;
	const u32       _ICODE_GENERAL                                  = 2121;
	const u32       _ICODE_GETEXPR                                  = 2122;
	const u32       _ICODE_GETS                                     = 2123;
	const u32       _ICODE_GET                                      = 2124;
	const u32       _ICODE_GO                                       = 2125;
	const u32       _ICODE_GOTO                                     = 2126;
	const u32       _ICODE_HEADINGS                                 = 2127;
	const u32       _ICODE_HELP                                     = 2128;
	const u32       _ICODE_HIDE                                     = 2129;
	const u32       _ICODE_HOURS                                    = 2130;
	const u32       _ICODE_ID                                       = 2131;
	const u32       _ICODE_IF                                       = 2132;
	const u32       _ICODE_IMPORT                                   = 2133;
	const u32       _ICODE_INDEXES                                  = 2134;
	const u32       _ICODE_INDEX                                    = 2135;
	const u32       _ICODE_INPUT                                    = 2136;
	const u32       _ICODE_INSERT                                   = 2137;
	const u32       _ICODE_INTENSITY                                = 2138;
	const u32       _ICODE_JOIN                                     = 2139;
	const u32       _ICODE_KEYBOARD                                 = 2140;
	const u32       _ICODE_KEYCOMP                                  = 2141;
	const u32       _ICODE_LABEL                                    = 2142;
	const u32       _ICODE_LIBRARY                                  = 2143;
	const u32       _ICODE_LISTS                                    = 2144;
	const u32       _ICODE_LIST                                     = 2145;
	const u32       _ICODE_LOAD                                     = 2146;
	const u32       _ICODE_LOCAL                                    = 2147;
	const u32       _ICODE_LOCATE                                   = 2148;
	const u32       _ICODE_LOGERRORS                                = 2149;
	const u32       _ICODE_LOOP                                     = 2150;
	const u32       _ICODE_LPARAMETERS                              = 2151;
	const u32       _ICODE_MACKEY                                   = 2152;
	const u32       _ICODE_MACROS                                   = 2153;
	const u32       _ICODE_MACRO                                    = 2154;
	const u32       _ICODE_MARGIN                                   = 2155;
	const u32       _ICODE_MARK                                     = 2156;
	const u32       _ICODE_MD                                       = 2157;
	const u32       _ICODE_MEMOWIDTH                                = 2158;
	const u32       _ICODE_MEMO                                     = 2159;
	const u32       _ICODE_MENUS                                    = 2160;
	const u32       _ICODE_MKDIR                                    = 2161;
	const u32       _ICODE_MODIFY                                   = 2162;
	const u32       _ICODE_MOUSE                                    = 2163;
	const u32       _ICODE_MOVE                                     = 2164;
	const u32       _ICODE_MTDLL                                    = 2165;
	const u32       _ICODE_MULTILOCKS                               = 2166;
	const u32       _ICODE_NEAR                                     = 2167;
	const u32       _ICODE_NEXT                                     = 2168;
	const u32       _ICODE_NOCPTRANS                                = 2169;
	const u32       _ICODE_NOTE                                     = 2170;
	const u32       _ICODE_NOTIFY                                   = 2171;
	const u32       _ICODE_NULL                                     = 2172;
	const u32       _ICODE_NULLDISPLAY                              = 2173;
	const u32       _ICODE_OBJECTS                                  = 2174;
	const u32       _ICODE_OBJECT                                   = 2175;
	const u32       _ICODE_ODOMETER                                 = 2176;
	const u32       _ICODE_OFF                                      = 2177;
	const u32       _ICODE_OF                                       = 2178;
	const u32       _ICODE_OLEOBJECT                                = 2179;
	const u32       _ICODE_OPEN                                     = 2180;
	const u32       _ICODE_OPTIMIZE                                 = 2181;
//	const u32       _ICODE_OR                                       = 2182;
	const u32       _ICODE_PACK                                     = 2183;
	const u32       _ICODE_PAGE                                     = 2184;
	const u32       _ICODE_PALETTE                                  = 2185;
	const u32       _ICODE_PATH                                     = 2186;
	const u32       _ICODE_PDSETUP                                  = 2187;
	const u32       _ICODE_PLAY                                     = 2188;
	const u32       _ICODE_POINT                                    = 2189;
	const u32       _ICODE_POP                                      = 2190;
	const u32       _ICODE_POPUPS                                   = 2191;
	const u32       _ICODE_PRINTER                                  = 2192;
	const u32       _ICODE_PRINTJOB                                 = 2193;
	const u32       _ICODE_PRIVATE                                  = 2194;
	const u32       _ICODE_PROCEDURES                               = 2195;
	const u32       _ICODE_PROCEDURE                                = 2196;
	const u32       _ICODE_PROJECT                                  = 2197;
	const u32       _ICODE_PUBLIC                                   = 2198;
	const u32       _ICODE_PUSH                                     = 2199;
	const u32       _ICODE_QUERY                                    = 2200;
	const u32       _ICODE_QUIT                                     = 2201;
	const u32       _ICODE_RD                                       = 2202;
	const u32       _ICODE_READ                                     = 2203;
	const u32       _ICODE_READBORDER                               = 2204;
	const u32       _ICODE_READERROR                                = 2205;
	const u32       _ICODE_RECALL                                   = 2206;
	const u32       _ICODE_REINDEX                                  = 2207;
	const u32       _ICODE_RELEASE                                  = 2208;
	const u32       _ICODE_REMOVE                                   = 2209;
	const u32       _ICODE_RENAME                                   = 2210;
	const u32       _ICODE_REPLACE                                  = 2211;
	const u32       _ICODE_REPORT                                   = 2212;
	const u32       _ICODE_REPROCESS                                = 2213;
	const u32       _ICODE_RESOURCE                                 = 2214;
	const u32       _ICODE_RESTORE                                  = 2215;
	const u32       _ICODE_RESUME                                   = 2216;
	const u32       _ICODE_RETRY                                    = 2217;
	const u32       _ICODE_RETURN                                   = 2218;
	const u32       _ICODE_RMDIR                                    = 2219;
	const u32       _ICODE_ROLLBACK                                 = 2220;
	const u32       _ICODE_RUN                                      = 2221;
	const u32       _ICODE_SAFETY                                   = 2222;
	const u32       _ICODE_SAVE                                     = 2223;
	const u32       _ICODE_SAY                                      = 2224;
	const u32       _ICODE_SCAN                                     = 2225;
	const u32       _ICODE_SCATTER                                  = 2226;
	const u32       _ICODE_SCREEN                                   = 2227;
	const u32       _ICODE_SCROLL                                   = 2228;
	const u32       _ICODE_SELECTION                                = 2229;
	const u32       _ICODE_SEPARATOR                                = 2230;
	const u32       _ICODE_SHOW                                     = 2231;
	const u32       _ICODE_SHUTDOWN                                 = 2232;
	const u32       _ICODE_SIZE                                     = 2233;
	const u32       _ICODE_SKIP                                     = 2234;
	const u32       _ICODE_SORT                                     = 2235;
	const u32       _ICODE_SQL                                      = 2236;
	const u32       _ICODE_STATUS                                   = 2237;
	const u32       _ICODE_STEP                                     = 2238;
	const u32       _ICODE_STORE                                    = 2239;
	const u32       _ICODE_STRICTDATE                               = 2240;
	const u32       _ICODE_STRUCTURE                                = 2241;
	const u32       _ICODE_SUM                                      = 2242;
	const u32       _ICODE_SUSPEND                                  = 2243;
	const u32       _ICODE_SYSFORMATS                               = 2244;
	const u32       _ICODE_SYSMENU                                  = 2245;
	const u32       _ICODE_TABLEVALIDATE                            = 2246;
	const u32       _ICODE_TABLES                                   = 2247;
	const u32       _ICODE_TABLE                                    = 2248;
	const u32       _ICODE_TALK                                     = 2249;
	const u32       _ICODE_TEXT                                     = 2250;
	const u32       _ICODE_TO                                       = 2251;
	const u32       _ICODE_TOPIC                                    = 2252;
	const u32       _ICODE_TOTAL                                    = 2253;
	const u32       _ICODE_TRANSACTION                              = 2254;
	const u32       _ICODE_TRBETWEEN                                = 2255;
	const u32       _ICODE_TRIGGER                                  = 2256;
	const u32       _ICODE_TRY                                      = 2257;
	const u32       _ICODE_TYPEAHEAD                                = 2258;
	const u32       _ICODE_UDFPARMS                                 = 2259;
	const u32       _ICODE_UNLOCK                                   = 2260;
	const u32       _ICODE_UPDATE                                   = 2261;
	const u32       _ICODE_USE                                      = 2262;
	const u32       _ICODE_VALIDATE                                 = 2263;
	const u32       _ICODE_VIEWS                                    = 2264;
	const u32       _ICODE_VIEW                                     = 2265;
	const u32       _ICODE_WAIT                                     = 2266;
	const u32       _ICODE_WHILE                                    = 2267;
	const u32       _ICODE_WINDOWS                                  = 2268;
	const u32       _ICODE_WINDOW                                   = 2269;
	const u32       _ICODE_WITH                                     = 2270;
	const u32       _ICODE_ZAP                                      = 2271;

	SAsciiCompSearcher	cgcKeywordOperators[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		validate handler,		custom handler
		{ cgcCaskRoundOpenParams,	3,			false,		_ICODE_CASK_ROUND_OPEN_PARAMS,			false,				NULL,					NULL },
		{ cgcCaskRoundCloseParams,	3,			false,		_ICODE_CASK_ROUND_CLOSE_PARAMS,			false,				NULL,					NULL },
		{ cgcCaskSquareOpenParams,	3,			false,		_ICODE_CASK_SQUARE_OPEN_PARAMS,			false,				NULL,					NULL },
		{ cgcCaskSquareCloseParams,	3,			false,		_ICODE_CASK_SQUARE_CLOSE_PARAMS,		false,				NULL,					NULL },
		{ cgcCaskTriangleOpenParams,3,			false,		_ICODE_CASK_TRIANGLE_OPEN_PARAMS,		false,				NULL,					NULL },
		{ cgcCaskTriangleCloseParams,3,			false,		_ICODE_CASK_TRIANGLE_CLOSE_PARAMS,		false,				NULL,					NULL },
		{ cgcCaskTildeOpenParams,	3,			false,		_ICODE_CASK_TILDE_OPEN_PARAMS,			false,				NULL,					NULL },
		{ cgcCaskTildeCloseParams,	3,			false,		_ICODE_CASK_TILDE_CLOSE_PARAMS,			false,				NULL,					NULL },
		{ cgcCaskRoundOpen,			2,			false,		_ICODE_CASK_ROUND_OPEN,					false,				NULL,					NULL },
		{ cgcCaskRoundClose,		2,			false,		_ICODE_CASK_ROUND_CLOSE,				false,				NULL,					NULL },
		{ cgcCaskSquareOpen,		2,			false,		_ICODE_CASK_SQUARE_OPEN,				false,				NULL,					NULL },
		{ cgcCaskSquareClose,		2,			false,		_ICODE_CASK_SQUARE_CLOSE,				false,				NULL,					NULL },
		{ cgcCaskTriangleOpen,		2,			false,		_ICODE_CASK_TRIANGLE_OPEN,				false,				NULL,					NULL },
		{ cgcCaskTriangleClose,		2,			false,		_ICODE_CASK_TRIANGLE_CLOSE,				false,				NULL,					NULL },
		{ cgcCaskTildeOpen,			2,			false,		_ICODE_CASK_TILDE_OPEN,					false,				NULL,					NULL },
		{ cgcCaskTildeClose,		2,			false,		_ICODE_CASK_TILDE_CLOSE,				false,				NULL,					NULL },
		{ "_azAZ__\000\000",		1,			true,		_ICODE_ALPHA,							false,				NULL,					NULL },
		{ "_09\000\000",			1,			true,		_ICODE_NUMERIC,							false,				NULL,					NULL },
		{ " ",						1,			true,		_ICODE_WHITESPACE,						false,				NULL,					NULL },
		{ "\t",						1,			true,		_ICODE_WHITESPACE,						false,				NULL,					NULL },
		{ "___",					1,			false,		_ICODE_UNDERSCORE,						false,				NULL,					NULL },
		{ "(",						1,			false,		_ICODE_PARENTHESIS_LEFT,				false,				NULL,					NULL },
		{ ")",						1,			false,		_ICODE_PARENTHESIS_RIGHT,				false,				NULL,					NULL },
		{ "[",						1,			false,		_ICODE_BRACKET_LEFT,					false,				NULL,					NULL },
		{ "]",						1,			false,		_ICODE_BRACKET_RIGHT,					false,				NULL,					NULL },
		{ "{",						1,			false,		_ICODE_BRACE_LEFT,						false,				NULL,					NULL },
		{ "}",						1,			false,		_ICODE_BRACE_RIGHT,						false,				NULL,					NULL },
		{ "+",						1,			false,		_ICODE_PLUS,							false,				NULL,					NULL },
		{ "-",						1,			false,		_ICODE_HYPHEN,							false,				NULL,					NULL },
		{ "^",						1,			false,		_ICODE_EXPONENT,						false,				NULL,					NULL },
		{ "**",						2,			false,		_ICODE_EXPONENT,						false,				NULL,					NULL },
		{ "*",						1,			true,		_ICODE_COMMENT,							true,				NULL,					NULL },
		{ "&&",						2,			false,		_ICODE_LINE_COMMENT,					false,				NULL,					NULL },
		{ "*",						1,			true,		_ICODE_ASTERISK,						false,				NULL,					NULL },
		{ "\\",						1,			true,		_ICODE_SLASH,							false,				NULL,					NULL },
		{ "/",						1,			true,		_ICODE_BACKSLASH,						false,				NULL,					NULL },
		{ "\"",						1,			false,		_ICODE_DOUBLE_QUOTE,					false,				NULL,					NULL },
		{ "'",						1,			false,		_ICODE_SINGLE_QUOTE,					false,				NULL,					NULL },
		{ ".",						1,			false,		_ICODE_DOT,								false,				NULL,					NULL },
		{ ",",						1,			false,		_ICODE_COMMA,							false,				NULL,					NULL },
		{ ":",						1,			false,		_ICODE_COLON,							false,				NULL,					NULL },
		{ "_",						1,			false,		_ICODE_UNDERSCORE,						false,				NULL,					NULL },
		{ "~",						1,			false,		_ICODE_TILDE,							false,				NULL,					NULL },
		{ "@",						1,			false,		_ICODE_AT_SIGN,							false,				NULL,					NULL },
		{ "?",						1,			false,		_ICODE_QUESTION_MARK,					false,				NULL,					NULL },
		{ "!$",						2,			false,		_ICODE_NOT_FOUND_IN,					false,				NULL,					NULL },
		{ "!=",                     2,          false,      _ICODE_NOT_EQUAL,                       false,              NULL,                   NULL },
		{ "!",						1,			false,		_ICODE_EXCLAMATION_MARK,				false,				NULL,					NULL },
		{ "#",						1,			false,		_ICODE_POUND_SIGN,						false,				NULL,					NULL },
		{ "$",						1,			false,		_ICODE_FOUND_IN,						false,				NULL,					NULL },
		{ "%",						1,			false,		_ICODE_PERCENT_SIGN,					false,				NULL,					NULL },
		{ "&",						1,			false,		_ICODE_AMPERSAND,						false,				NULL,					NULL },
		{ "=<",						2,			false,		_ICODE_LESS_THAN_OR_EQUAL_TO,			false,				NULL,					NULL },
		{ "=>",						2,			false,		_ICODE_GREATER_THAN_OR_EQUAL_TO,		false,				NULL,					NULL },
		{ "==",						2,			false,		_ICODE_EXACTLY_EQUAL_TO,				false,				NULL,					NULL },
		{ "=",						1,			false,		_ICODE_EQUAL_SIGN,						false,				NULL,					NULL },
		{ "|",						1,			false,		_ICODE_PIPE_SIGN,						false,				NULL,					NULL },
		{ "`",						1,			false,		_ICODE_REVERSE_QUOTE,					false,				NULL,					NULL },
		{ ";",						1,			false,		_ICODE_SEMICOLON,						false,				NULL,					NULL },
		{ "<<=",					3,			false,		_ICODE_SHIFT_LEFT_ASSIGNMENT,			false,				NULL,					NULL },
		{ "<<",						2,			false,		_ICODE_SHIFT_LEFT,						false,				NULL,					NULL },
		{ ">>=",					3,			false,		_ICODE_SHIFT_RIGHT_ASSIGNMENT,			false,				NULL,					NULL },
		{ ">>",						2,			false,		_ICODE_SHIFT_RIGHT,						false,				NULL,					NULL },
		{ "<=",						2,			false,		_ICODE_LESS_THAN_OR_EQUAL_TO,			false,				NULL,					NULL },
		{ ">=",						2,			false,		_ICODE_GREATER_THAN_OR_EQUAL_TO,		false,				NULL,					NULL },
		{ "<>",                     2,          false,      _ICODE_NOT_EQUAL,                       false,              NULL,                   NULL },
		{ ">",						1,			false,		_ICODE_GREATER_THAN,					false,				NULL,					NULL },
		{ "<",						1,			false,		_ICODE_LESS_THAN,						false,				NULL,					NULL },
		{ "++",						2,			false,		_ICODE_PLUS_PLUS,						false,				NULL,					NULL },
		{ "--",						2,			false,		_ICODE_MINUS_MINUS,						false,				NULL,					NULL },

		/* As a last-case condition, we tag every character that we didn't previously identify with the unknown tag */                      	
		{ "_\000\377\000\000",		1,			true,		_ICODE_UNKNOWN,							false,				NULL,					NULL },
		{ 0,						0,			0,			0,										0,					0,						0 }
	};

	// Zeroeth-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywords0[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		validate handler		custom handler
		{ "define",					6,			false,		_ICODE_DEFINE,							true,				NULL,					NULL },
//////////
// Jun.21.2014 -- For the time being, include files will not be supported
//		{ "include",				7,			false,		_ICODE_INCLUDE,							true,				NULL,					NULL },
//////
		{ 0,						0,			0,			0,										0,					0,						0 }
	};

	// First-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywords1[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		validate handler		custom handler
		{ "not",                    3,          false,      _ICODE_NOT,                             false,              NULL,                   NULL },
		{ "and",                    3,          false,      _ICODE_AND,                             false,              NULL,                   NULL },
		{ "or",                     2,          false,      _ICODE_OR,                              false,              NULL,                   NULL },
		{ "abs",                    3,          false,      _ICODE_ABS,                             false,              NULL,                   NULL },
		{ "aclass",                 6,          false,      _ICODE_ACLASS,                          false,              NULL,                   NULL },
		{ "acopy",                  5,          false,      _ICODE_ACOPY,                           false,              NULL,                   NULL },
		{ "acos",                   4,          false,      _ICODE_ACOS,                            false,              NULL,                   NULL },
		{ "adatabases",             10,         false,      _ICODEADATABASES_,                      false,              NULL,                   NULL },
		{ "adbobjects",             10,         false,      _ICODEADBOBJECTS_,                      false,              NULL,                   NULL },
		{ "addbs",                  5,          false,      _ICODE_ADDBS,                           false,              NULL,                   NULL },
		{ "addproperty",            11,         false,      _ICODE_ADDPROPERTY,                     false,              NULL,                   NULL },
		{ "adel",                   4,          false,      _ICODE_ADEL,                            false,              NULL,                   NULL },
		{ "adir",                   4,          false,      _ICODE_ADIR,                            false,              NULL,                   NULL },
		{ "adlls",                  5,          false,      _ICODE_ADLLS,                           false,              NULL,                   NULL },
		{ "adockstate",             10,         false,      _ICODE_ADOCKSTATE,                      false,              NULL,                   NULL },
		{ "aelement",               8,          false,      _ICODE_AELEMENT,                        false,              NULL,                   NULL },
		{ "aerror",                 6,          false,      _ICODE_AERROR,                          false,              NULL,                   NULL },
		{ "aevents",                7,          false,      _ICODE_AEVENTS,                         false,              NULL,                   NULL },
		{ "afields",                7,          false,      _ICODE_AFIELDS,                         false,              NULL,                   NULL },
		{ "afont",                  5,          false,      _ICODE_AFONT,                           false,              NULL,                   NULL },
		{ "agetclass",              9,          false,      _ICODE_AGETCLASS,                       false,              NULL,                   NULL },
		{ "agetfileversion",        15,         false,      _ICODE_AGETFILEVERSION,                 false,              NULL,                   NULL },
		{ "ainstance",              9,          false,      _ICODE_AINSTANCE,                       false,              NULL,                   NULL },
		{ "ains",                   4,          false,      _ICODE_AINS,                            false,              NULL,                   NULL },
		{ "alanguage",              9,          false,      _ICODE_ALANGUAGE,                       false,              NULL,                   NULL },
		{ "alen",                   4,          false,      _ICODE_ALEN,                            false,              NULL,                   NULL },
		{ "alias",                  5,          false,      _ICODE_ALIAS,                           false,              NULL,                   NULL },
		{ "alines",                 6,          false,      _ICODE_ALINES,                          false,              NULL,                   NULL },
		{ "alltrim",                7,          false,      _ICODE_ALLTRIM,                         false,              NULL,                   NULL },
		{ "amembers",               8,          false,      _ICODE_AMEMBERS,                        false,              NULL,                   NULL },
		{ "amouseobj",              9,          false,      _ICODE_AMOUSEOBJ,                       false,              NULL,                   NULL },
		{ "anetresources",          13,         false,      _ICODE_ANETRESOURCES,                   false,              NULL,                   NULL },
		{ "aprinters",              9,          false,      _ICODE_APRINTERS,                       false,              NULL,                   NULL },
		{ "aprocinfo",              9,          false,      _ICODE_APROCINFO,                       false,              NULL,                   NULL },
		{ "ascan",                  5,          false,      _ICODE_ASCAN,                           false,              NULL,                   NULL },
		{ "asc",                    3,          false,      _ICODE_ASC,                             false,              NULL,                   NULL },
		{ "aselobj",                7,          false,      _ICODE_ASELOBJ,                         false,              NULL,                   NULL },
		{ "asessions",              9,          false,      _ICODE_ASESSIONS,                       false,              NULL,                   NULL },
		{ "asin",                   4,          false,      _ICODE_ASIN,                            false,              NULL,                   NULL },
		{ "asort",                  5,          false,      _ICODE_ASORT,                           false,              NULL,                   NULL },
		{ "asqlhandles",            11,         false,      _ICODE_ASQLHANDLES,                     false,              NULL,                   NULL },
		{ "astackinfo",             10,         false,      _ICODE_ASTACKINFO,                      false,              NULL,                   NULL },
		{ "asubscript",             10,         false,      _ICODE_ASUBSCRIPT,                      false,              NULL,                   NULL },
		{ "at_c",                   4,          false,      _ICODE_AT_C,                            false,              NULL,                   NULL },
		{ "at",                     2,          false,      _ICODE_AT,                              false,              NULL,                   NULL },
		{ "ataginfo",               8,          false,      _ICODE_ATAGINFO,                        false,              NULL,                   NULL },
		{ "atan",                   4,          false,      _ICODE_ATAN,                            false,              NULL,                   NULL },
		{ "atcline",                7,          false,      _ICODE_ATCLINE,                         false,              NULL,                   NULL },
		{ "atcc",                   4,          false,      _ICODE_ATCC,                            false,              NULL,                   NULL },
		{ "atc",                    3,          false,      _ICODE_ATC,                             false,              NULL,                   NULL },
		{ "atline",                 6,          false,      _ICODE_ATLINE,                          false,              NULL,                   NULL },
		{ "atn2",                   4,          false,      _ICODE_ATN2,                            false,              NULL,                   NULL },
		{ "aused",                  5,          false,      _ICODE_AUSED,                           false,              NULL,                   NULL },
		{ "avcxclasses",            11,         false,      _ICODE_AVCXCLASSES,                     false,              NULL,                   NULL },
		{ "barprompt",              9,          false,      _ICODE_BARPROMPT,                       false,              NULL,                   NULL },
		{ "barcount",               8,          false,      _ICODE_BARCOUNT,                        false,              NULL,                   NULL },
		{ "bar",                    3,          false,      _ICODE_BAR,                             false,              NULL,                   NULL },
		{ "between",                7,          false,      _ICODE_BETWEEN,                         false,              NULL,                   NULL },
		{ "bindevent",              9,          false,      _ICODE_BINDEVENT,                       false,              NULL,                   NULL },
		{ "bintoc",                 6,          false,      _ICODE_BINTOC,                          false,              NULL,                   NULL },
		{ "bitand",                 6,          false,      _ICODE_BITAND,                          false,              NULL,                   NULL },
		{ "bitclear",               8,          false,      _ICODE_BITCLEAR,                        false,              NULL,                   NULL },
		{ "bitlshift",              9,          false,      _ICODE_BITLSHIFT,                       false,              NULL,                   NULL },
		{ "bitnot",                 6,          false,      _ICODE_BITNOT,                          false,              NULL,                   NULL },
		{ "bitor",                  5,          false,      _ICODE_BITOR,                           false,              NULL,                   NULL },
		{ "bitrshift",              9,          false,      _ICODE_BITRSHIFT,                       false,              NULL,                   NULL },
		{ "bitset",                 6,          false,      _ICODE_BITSET,                          false,              NULL,                   NULL },
		{ "bittest",                7,          false,      _ICODE_BITTEST,                         false,              NULL,                   NULL },
		{ "bitxor",                 6,          false,      _ICODE_BITXOR,                          false,              NULL,                   NULL },
		{ "bof",                    3,          false,      _ICODE_BOF,                             false,              NULL,                   NULL },
		{ "candidate",              9,          false,      _ICODE_CANDIDATE,                       false,              NULL,                   NULL },
		{ "capslock",               8,          false,      _ICODE_CAPSLOCK,                        false,              NULL,                   NULL },
		{ "cast",                   4,          false,      _ICODE_CAST,                            false,              NULL,                   NULL },
		{ "cdow",                   4,          false,      _ICODE_CDOW,                            false,              NULL,                   NULL },
		{ "cdx",                    3,          false,      _ICODE_CDX,                             false,              NULL,                   NULL },
		{ "ceiling",                7,          false,      _ICODE_CEILING,                         false,              NULL,                   NULL },
		{ "chr",                    3,          false,      _ICODE_CHR,                             false,              NULL,                   NULL },
		{ "chrsaw",                 6,          false,      _ICODE_CHRSAW,                          false,              NULL,                   NULL },
		{ "chrtranc",               8,          false,      _ICODE_CHRTRANC,                        false,              NULL,                   NULL },
		{ "chrtran",                7,          false,      _ICODE_CHRTRAN,                         false,              NULL,                   NULL },
		{ "clearresultset",         14,         false,      _ICODE_CLEARRESULTSET,                  false,              NULL,                   NULL },
		{ "cmonth",                 6,          false,      _ICODE_CMONTH,                          false,              NULL,                   NULL },
		{ "cntbar",                 6,          false,      _ICODE_CNTBAR,                          false,              NULL,                   NULL },
		{ "cntpad",                 6,          false,      _ICODE_CNTPAD,                          false,              NULL,                   NULL },
		{ "col",                    3,          false,      _ICODE_COL,                             false,              NULL,                   NULL },
		{ "comarray",               8,          false,      _ICODE_COMARRAY,                        false,              NULL,                   NULL },
		{ "comclassinfo",           12,         false,      _ICODE_COMCLASSINFO,                    false,              NULL,                   NULL },
		{ "command",                7,          false,      _ICODE_COMMAND,                         false,              NULL,                   NULL },
		{ "compobj",                7,          false,      _ICODE_COMPOBJ,                         false,              NULL,                   NULL },
		{ "comprop",                7,          false,      _ICODE_COMPROP,                         false,              NULL,                   NULL },
		{ "comreturnerror",         14,         false,      _ICODE_COMRETURNERROR,                  false,              NULL,                   NULL },
		{ "coms",                   4,          false,      _ICODE_COMS,                            false,              NULL,                   NULL },
		{ "cos",                    3,          false,      _ICODE_COS,                             false,              NULL,                   NULL },
		{ "cpconvert",              9,          false,      _ICODE_CPCONVERT,                       false,              NULL,                   NULL },
		{ "cpcurrent",              9,          false,      _ICODE_CPCURRENT,                       false,              NULL,                   NULL },
		{ "cpdbf",                  5,          false,      _ICODE_CPDBF,                           false,              NULL,                   NULL },
		{ "createbinary",           12,         false,      _ICODE_CREATEBINARY,                    false,              NULL,                   NULL },
		{ "createobject",           12,         false,      _ICODE_CREATEOBJECT,                    false,              NULL,                   NULL },
		{ "createobjectex",         14,         false,      _ICODE_CREATEOBJECTEX,                  false,              NULL,                   NULL },
		{ "createoffline",          13,         false,      _ICODE_CREATEOFFLINE,                   false,              NULL,                   NULL },
		{ "ctobin",                 6,          false,      _ICODE_CTOBIN,                          false,              NULL,                   NULL },
		{ "ctod",                   4,          false,      _ICODE_CTOD,                            false,              NULL,                   NULL },
		{ "ctot",                   4,          false,      _ICODE_CTOT,                            false,              NULL,                   NULL },
		{ "curdir",                 6,          false,      _ICODE_CURDIR,                          false,              NULL,                   NULL },
		{ "cursorgetprop",          13,         false,      _ICODE_CURSORGETPROP,                   false,              NULL,                   NULL },
		{ "cursorsetprop",          13,         false,      _ICODE_CURSORSETPROP,                   false,              NULL,                   NULL },
		{ "cursortoxml",            11,         false,      _ICODE_CURSORTOXML,                     false,              NULL,                   NULL },
		{ "curval",                 6,          false,      _ICODE_CURVAL,                          false,              NULL,                   NULL },
		{ "datetime",               8,          false,      _ICODE_DATETIME,                        false,              NULL,                   NULL },
		{ "date",                   4,          false,      _ICODE_DATE,                            false,              NULL,                   NULL },
		{ "day",                    3,          false,      _ICODE_DAY,                             false,              NULL,                   NULL },
		{ "dbc",                    3,          false,      _ICODE_DBC,                             false,              NULL,                   NULL },
		{ "dbf",                    3,          false,      _ICODE_DBF,                             false,              NULL,                   NULL },
		{ "dbgetprop",              9,          false,      _ICODE_DBGETPROP,                       false,              NULL,                   NULL },
		{ "dbsetprop",              9,          false,      _ICODE_DBSETPROP,                       false,              NULL,                   NULL },
		{ "dbused",                 6,          false,      _ICODE_DBUSED,                          false,              NULL,                   NULL },
		{ "ddeaborttrans",          13,         false,      _ICODE_DDEABORTTRANS,                   false,              NULL,                   NULL },
		{ "ddeadvise",              9,          false,      _ICODE_DDEADVISE,                       false,              NULL,                   NULL },
		{ "ddeenabled",             10,         false,      _ICODE_DDEENABLED,                      false,              NULL,                   NULL },
		{ "ddeexecute",             10,         false,      _ICODE_DDEEXECUTE,                      false,              NULL,                   NULL },
		{ "ddeinitiate",            11,         false,      _ICODE_DDEINITIATE,                     false,              NULL,                   NULL },
		{ "ddelasterror",           12,         false,      _ICODE_DDELASTERROR,                    false,              NULL,                   NULL },
		{ "ddepoke",                7,          false,      _ICODE_DDEPOKE,                         false,              NULL,                   NULL },
		{ "dderequest",             10,         false,      _ICODE_DDEREQUEST,                      false,              NULL,                   NULL },
		{ "ddes",                   4,          false,      _ICODE_DDES,                            false,              NULL,                   NULL },
		{ "ddesetoption",           12,         false,      _ICODE_DDESETOPTION,                    false,              NULL,                   NULL },
		{ "ddesetservice",          13,         false,      _ICODE_DDESETSERVICE,                   false,              NULL,                   NULL },
		{ "ddesettopic",            11,         false,      _ICODE_DDESETTOPIC,                     false,              NULL,                   NULL },
		{ "ddeterminate",           12,         false,      _ICODE_DDETERMINATE,                    false,              NULL,                   NULL },
		{ "defaultext",             10,         false,      _ICODE_DEFAULTEXT,                      false,              NULL,                   NULL },
		{ "deleted",                7,          false,      _ICODE_DELETED,                         false,              NULL,                   NULL },
		{ "descending",             10,         false,      _ICODE_DESCENDING,                      false,              NULL,                   NULL },
		{ "difference",             10,         false,      _ICODE_DIFFERENCE,                      false,              NULL,                   NULL },
		{ "directory",              9,          false,      _ICODE_DIRECTORY,                       false,              NULL,                   NULL },
		{ "diskspace",              9,          false,      _ICODE_DISKSPACE,                       false,              NULL,                   NULL },
		{ "displaypath",            11,         false,      _ICODE_DISPLAYPATH,                     false,              NULL,                   NULL },
		{ "dmy",                    3,          false,      _ICODE_DMY,                             false,              NULL,                   NULL },
		{ "dodefault",              9,          false,      _ICODE_DODEFAULT,                       false,              NULL,                   NULL },
		{ "dow",                    3,          false,      _ICODE_DOW,                             false,              NULL,                   NULL },
		{ "drivetype",              9,          false,      _ICODE_DRIVETYPE,                       false,              NULL,                   NULL },
		{ "dropoffline",            11,         false,      _ICODE_DROPOFFLINE,                     false,              NULL,                   NULL },
		{ "dtoc",                   4,          false,      _ICODE_DTOC,                            false,              NULL,                   NULL },
		{ "dtor",                   4,          false,      _ICODE_DTOR,                            false,              NULL,                   NULL },
		{ "dtos",                   4,          false,      _ICODE_DTOS,                            false,              NULL,                   NULL },
		{ "dtot",                   4,          false,      _ICODE_DTOT,                            false,              NULL,                   NULL },
		{ "editsource",             10,         false,      _ICODE_EDITSOURCE,                      false,              NULL,                   NULL },
		{ "empty",                  5,          false,      _ICODE_EMPTY,                           false,              NULL,                   NULL },
		{ "eof",                    3,          false,      _ICODE_EOF,                             false,              NULL,                   NULL },
		{ "error",                  5,          false,      _ICODE_ERROR,                           false,              NULL,                   NULL },
		{ "evaluate",               8,          false,      _ICODE_EVALUATE,                        false,              NULL,                   NULL },
		{ "eventhandler",           12,         false,      _ICODE_EVENTHANDLER,                    false,              NULL,                   NULL },
		{ "evl",                    3,          false,      _ICODE_EVL,                             false,              NULL,                   NULL },
		{ "execscript",             10,         false,      _ICODE_EXECSCRIPT,                      false,              NULL,                   NULL },
		{ "exp",                    3,          false,      _ICODE_EXP,                             false,              NULL,                   NULL },
		{ "fchsize",                7,          false,      _ICODE_FCHSIZE,                         false,              NULL,                   NULL },
		{ "fclose",                 6,          false,      _ICODE_FCLOSE,                          false,              NULL,                   NULL },
		{ "fcount",                 6,          false,      _ICODE_FCOUNT,                          false,              NULL,                   NULL },
		{ "fcreate",                7,          false,      _ICODE_FCREATE,                         false,              NULL,                   NULL },
		{ "fdate",                  5,          false,      _ICODE_FDATE,                           false,              NULL,                   NULL },
		{ "feof",                   4,          false,      _ICODE_FEOF,                            false,              NULL,                   NULL },
		{ "ferror",                 6,          false,      _ICODE_FERROR,                          false,              NULL,                   NULL },
		{ "fflush",                 6,          false,      _ICODE_FFLUSH,                          false,              NULL,                   NULL },
		{ "fgets",                  5,          false,      _ICODE_FGETS,                           false,              NULL,                   NULL },
		{ "field",                  5,          false,      _ICODE_FIELD,                           false,              NULL,                   NULL },
		{ "filetostr",              9,          false,      _ICODE_FILETOSTR,                       false,              NULL,                   NULL },
		{ "file",                   4,          false,      _ICODE_FILE,                            false,              NULL,                   NULL },
		{ "filter",                 6,          false,      _ICODE_FILTER,                          false,              NULL,                   NULL },
		{ "fklabel",                7,          false,      _ICODE_FKLABEL,                         false,              NULL,                   NULL },
		{ "fkmax",                  5,          false,      _ICODE_FKMAX,                           false,              NULL,                   NULL },
		{ "fldlist",                7,          false,      _ICODE_FLDLIST,                         false,              NULL,                   NULL },
		{ "flock",                  5,          false,      _ICODE_FLOCK,                           false,              NULL,                   NULL },
		{ "floor",                  5,          false,      _ICODE_FLOOR,                           false,              NULL,                   NULL },
		{ "fontmetric",             10,         false,      _ICODE_FONTMETRIC,                      false,              NULL,                   NULL },
		{ "fopen",                  5,          false,      _ICODE_FOPEN,                           false,              NULL,                   NULL },
		{ "for",                    3,          false,      _ICODE_FOR,                             false,              NULL,                   NULL },
		{ "forceext",               8,          false,      _ICODE_FORCEEXT,                        false,              NULL,                   NULL },
		{ "forcepath",              9,          false,      _ICODE_FORCEPATH,                       false,              NULL,                   NULL },
		{ "found",                  5,          false,      _ICODE_FOUND,                           false,              NULL,                   NULL },
		{ "fputs",                  5,          false,      _ICODE_FPUTS,                           false,              NULL,                   NULL },
		{ "fread",                  5,          false,      _ICODE_FREAD,                           false,              NULL,                   NULL },
		{ "fseek",                  5,          false,      _ICODE_FSEEK,                           false,              NULL,                   NULL },
		{ "fsize",                  5,          false,      _ICODE_FSIZE,                           false,              NULL,                   NULL },
		{ "ftime",                  5,          false,      _ICODE_FTIME,                           false,              NULL,                   NULL },
		{ "fullpath",               8,          false,      _ICODE_FULLPATH,                        false,              NULL,                   NULL },
		{ "function",               8,          false,      _ICODE_FUNCTION,                        false,              NULL,                   NULL },
		{ "fv",                     2,          false,      _ICODE_FV,                              false,              NULL,                   NULL },
		{ "fwrite",                 6,          false,      _ICODE_FWRITE,                          false,              NULL,                   NULL },
		{ "getautoincvalue",        15,         false,      _ICODE_GETAUTOINCVALUE,                 false,              NULL,                   NULL },
		{ "getbar",                 6,          false,      _ICODE_GETBAR,                          false,              NULL,                   NULL },
		{ "getcolor",               8,          false,      _ICODE_GETCOLOR,                        false,              NULL,                   NULL },
		{ "getcp",                  5,          false,      _ICODE_GETCP,                           false,              NULL,                   NULL },
		{ "getcursoradapter",       16,         false,      _ICODE_GETCURSORADAPTER,                false,              NULL,                   NULL },
		{ "getdir",                 6,          false,      _ICODE_GETDIR,                          false,              NULL,                   NULL },
		{ "getenv",                 6,          false,      _ICODE_GETENV,                          false,              NULL,                   NULL },
		{ "getfile",                7,          false,      _ICODE_GETFILE,                         false,              NULL,                   NULL },
		{ "getfldstate",            11,         false,      _ICODE_GETFLDSTATE,                     false,              NULL,                   NULL },
		{ "getfont",                7,          false,      _ICODE_GETFONT,                         false,              NULL,                   NULL },
		{ "getinterface",           12,         false,      _ICODE_GETINTERFACE,                    false,              NULL,                   NULL },
		{ "getnextmodified",        15,         false,      _ICODE_GETNEXTMODIFIED,                 false,              NULL,                   NULL },
		{ "getobject",              9,          false,      _ICODE_GETOBJECT,                       false,              NULL,                   NULL },
		{ "getpad",                 6,          false,      _ICODE_GETPAD,                          false,              NULL,                   NULL },
		{ "getpem",                 6,          false,      _ICODE_GETPEM,                          false,              NULL,                   NULL },
		{ "getpict",                7,          false,      _ICODE_GETPICT,                         false,              NULL,                   NULL },
		{ "getprinter",             10,         false,      _ICODE_GETPRINTER,                      false,              NULL,                   NULL },
		{ "getresultset",           12,         false,      _ICODE_GETRESULTSET,                    false,              NULL,                   NULL },
		{ "getwordcount",           12,         false,      _ICODE_GETWORDCOUNT,                    false,              NULL,                   NULL },
		{ "getwordnum",             10,         false,      _ICODE_GETWORDNUM,                      false,              NULL,                   NULL },
		{ "gomonth",                7,          false,      _ICODE_GOMONTH,                         false,              NULL,                   NULL },
		{ "header",                 6,          false,      _ICODE_HEADER,                          false,              NULL,                   NULL },
		{ "home",                   4,          false,      _ICODE_HOME,                            false,              NULL,                   NULL },
		{ "hour",                   4,          false,      _ICODE_HOUR,                            false,              NULL,                   NULL },
		{ "icase",                  5,          false,      _ICODE_ICASE,                           false,              NULL,                   NULL },
		{ "idxcollate",             10,         false,      _ICODE_IDXCOLLATE,                      false,              NULL,                   NULL },
		{ "iif",                    3,          false,      _ICODE_IIF,                             false,              NULL,                   NULL },
		{ "imestatus",              9,          false,      _ICODE_IMESTATUS,                       false,              NULL,                   NULL },
		{ "indbc",                  5,          false,      _ICODE_INDBC,                           false,              NULL,                   NULL },
		{ "indexseek",              9,          false,      _ICODE_INDEXSEEK,                       false,              NULL,                   NULL },
		{ "inkey",                  5,          false,      _ICODE_INKEY,                           false,              NULL,                   NULL },
		{ "inlist",                 6,          false,      _ICODE_INLIST,                          false,              NULL,                   NULL },
		{ "inputbox",               8,          false,      _ICODE_INPUTBOX,                        false,              NULL,                   NULL },
		{ "insmode",                7,          false,      _ICODE_INSMODE,                         false,              NULL,                   NULL },
		{ "int",                    3,          false,      _ICODE_INT,                             false,              NULL,                   NULL },
		{ "isalpha",                7,          false,      _ICODE_ISALPHA,                         false,              NULL,                   NULL },
		{ "isblank",                7,          false,      _ICODE_ISBLANK,                         false,              NULL,                   NULL },
		{ "iscolor",                7,          false,      _ICODE_ISCOLOR,                         false,              NULL,                   NULL },
		{ "isdigit",                7,          false,      _ICODE_ISDIGIT,                         false,              NULL,                   NULL },
		{ "isexclusive",            11,         false,      _ICODE_ISEXCLUSIVE,                     false,              NULL,                   NULL },
		{ "isflocked",              9,          false,      _ICODE_ISFLOCKED,                       false,              NULL,                   NULL },
		{ "isleadbyte",             10,         false,      _ICODE_ISLEADBYTE,                      false,              NULL,                   NULL },
		{ "islower",                7,          false,      _ICODE_ISLOWER,                         false,              NULL,                   NULL },
		{ "ismemofetched",          13,         false,      _ICODE_ISMEMOFETCHED,                   false,              NULL,                   NULL },
		{ "ismouse",                7,          false,      _ICODE_ISMOUSE,                         false,              NULL,                   NULL },
		{ "isnull",                 6,          false,      _ICODE_ISNULL,                          false,              NULL,                   NULL },
		{ "ispen",                  5,          false,      _ICODE_ISPEN,                           false,              NULL,                   NULL },
		{ "isreadonly",             10,         false,      _ICODE_ISREADONLY,                      false,              NULL,                   NULL },
		{ "isrlocked",              9,          false,      _ICODE_ISRLOCKED,                       false,              NULL,                   NULL },
		{ "istransactable",         14,         false,      _ICODE_ISTRANSACTABLE,                  false,              NULL,                   NULL },
		{ "isupper",                7,          false,      _ICODE_ISUPPER,                         false,              NULL,                   NULL },
		{ "justdrive",              9,          false,      _ICODE_JUSTDRIVE,                       false,              NULL,                   NULL },
		{ "justext",                7,          false,      _ICODE_JUSTEXT,                         false,              NULL,                   NULL },
		{ "justfname",              9,          false,      _ICODE_JUSTFNAME,                       false,              NULL,                   NULL },
		{ "justpath",               8,          false,      _ICODE_JUSTPATH,                        false,              NULL,                   NULL },
		{ "juststem",               8,          false,      _ICODE_JUSTSTEM,                        false,              NULL,                   NULL },
		{ "keymatch",               8,          false,      _ICODE_KEYMATCH,                        false,              NULL,                   NULL },
		{ "key",                    3,          false,      _ICODE_KEY,                             false,              NULL,                   NULL },
		{ "lastkey",                7,          false,      _ICODE_LASTKEY,                         false,              NULL,                   NULL },
		{ "leftc",                  5,          false,      _ICODE_LEFTC,                           false,              NULL,                   NULL },
		{ "left",                   4,          false,      _ICODE_LEFT,                            false,              NULL,                   NULL },
		{ "lenc",                   4,          false,      _ICODE_LENC,                            false,              NULL,                   NULL },
		{ "len",                    3,          false,      _ICODE_LEN,                             false,              NULL,                   NULL },
		{ "likec",                  5,          false,      _ICODE_LIKEC,                           false,              NULL,                   NULL },
		{ "like",                   4,          false,      _ICODE_LIKE,                            false,              NULL,                   NULL },
		{ "lineno",                 6,          false,      _ICODE_LINENO,                          false,              NULL,                   NULL },
		{ "loadpicture",            11,         false,      _ICODE_LOADPICTURE,                     false,              NULL,                   NULL },
		{ "locfile",                7,          false,      _ICODE_LOCFILE,                         false,              NULL,                   NULL },
		{ "lock",                   4,          false,      _ICODE_LOCK,                            false,              NULL,                   NULL },
		{ "log10",                  5,          false,      _ICODE_LOG10,                           false,              NULL,                   NULL },
		{ "log",                    3,          false,      _ICODE_LOG,                             false,              NULL,                   NULL },
		{ "lookup",                 6,          false,      _ICODE_LOOKUP,                          false,              NULL,                   NULL },
		{ "lower",                  5,          false,      _ICODE_LOWER,                           false,              NULL,                   NULL },
		{ "ltrim",                  5,          false,      _ICODE_LTRIM,                           false,              NULL,                   NULL },
		{ "lupdate",                7,          false,      _ICODE_LUPDATE,                         false,              NULL,                   NULL },
		{ "maketransactable",       16,         false,      _ICODE_MAKETRANSACTABLE,                false,              NULL,                   NULL },
		{ "max",                    3,          false,      _ICODE_MAX,                             false,              NULL,                   NULL },
		{ "mcol",                   4,          false,      _ICODE_MCOL,                            false,              NULL,                   NULL },
		{ "mdown",                  5,          false,      _ICODE_MDOWN,                           false,              NULL,                   NULL },
		{ "mdx",                    3,          false,      _ICODE_MDX,                             false,              NULL,                   NULL },
		{ "mdy",                    3,          false,      _ICODE_MDY,                             false,              NULL,                   NULL },
		{ "memlines",               8,          false,      _ICODE_MEMLINES,                        false,              NULL,                   NULL },
		{ "memory",                 6,          false,      _ICODE_MEMORY,                          false,              NULL,                   NULL },
		{ "menu",                   4,          false,      _ICODE_MENU,                            false,              NULL,                   NULL },
		{ "messagebox",             10,         false,      _ICODE_MESSAGEBOX,                      false,              NULL,                   NULL },
		{ "message",                7,          false,      _ICODE_MESSAGE,                         false,              NULL,                   NULL },
		{ "minute",                 6,          false,      _ICODE_MINUTE,                          false,              NULL,                   NULL },
		{ "min",                    3,          false,      _ICODE_MIN,                             false,              NULL,                   NULL },
		{ "mline",                  5,          false,      _ICODE_MLINE,                           false,              NULL,                   NULL },
		{ "mod",                    3,          false,      _ICODE_MOD,                             false,              NULL,                   NULL },
		{ "month",                  5,          false,      _ICODE_MONTH,                           false,              NULL,                   NULL },
		{ "mrkbar",                 6,          false,      _ICODE_MRKBAR,                          false,              NULL,                   NULL },
		{ "mrkpad",                 6,          false,      _ICODE_MRKPAD,                          false,              NULL,                   NULL },
		{ "mrow",                   4,          false,      _ICODE_MROW,                            false,              NULL,                   NULL },
		{ "mton",                   4,          false,      _ICODE_MTON,                            false,              NULL,                   NULL },
		{ "mwindow",                7,          false,      _ICODE_MWINDOW,                         false,              NULL,                   NULL },
		{ "ndx",                    3,          false,      _ICODE_NDX,                             false,              NULL,                   NULL },
		{ "newobject",              9,          false,      _ICODE_NEWOBJECT,                       false,              NULL,                   NULL },
		{ "normalize",              9,          false,      _ICODE_NORMALIZE,                       false,              NULL,                   NULL },
		{ "ntom",                   4,          false,      _ICODE_NTOM,                            false,              NULL,                   NULL },
		{ "numlock",                7,          false,      _ICODE_NUMLOCK,                         false,              NULL,                   NULL },
		{ "nvl",                    3,          false,      _ICODE_NVL,                             false,              NULL,                   NULL },
		{ "objnum",                 6,          false,      _ICODE_OBJNUM,                          false,              NULL,                   NULL },
		{ "objtoclient",            11,         false,      _ICODE_OBJTOCLIENT,                     false,              NULL,                   NULL },
		{ "objvar",                 6,          false,      _ICODE_OBJVAR,                          false,              NULL,                   NULL },
		{ "occurs",                 6,          false,      _ICODE_OCCURS,                          false,              NULL,                   NULL },
		{ "oemtoansi",              9,          false,      _ICODE_OEMTOANSI,                       false,              NULL,                   NULL },
		{ "oldval",                 6,          false,      _ICODE_OLDVAL,                          false,              NULL,                   NULL },
		{ "on",                     2,          false,      _ICODE_ON,                              false,              NULL,                   NULL },
		{ "order",                  5,          false,      _ICODE_ORDER,                           false,              NULL,                   NULL },
		{ "os",                     2,          false,      _ICODE_OS,                              false,              NULL,                   NULL },
		{ "overview",               8,          false,      _ICODE_OVERVIEW,                        false,              NULL,                   NULL },
		{ "padc",                   4,          false,      _ICODE_PADC,                            false,              NULL,                   NULL },
		{ "padl",                   4,          false,      _ICODE_PADL,                            false,              NULL,                   NULL },
		{ "padr",                   4,          false,      _ICODE_PADR,                            false,              NULL,                   NULL },
		{ "pad",                    3,          false,      _ICODE_PAD,                             false,              NULL,                   NULL },
		{ "parameters",             10,         false,      _ICODE_PARAMETERS,                      false,              NULL,                   NULL },
		{ "payment",                7,          false,      _ICODE_PAYMENT,                         false,              NULL,                   NULL },
		{ "pcol",                   4,          false,      _ICODE_PCOL,                            false,              NULL,                   NULL },
		{ "pcount",                 6,          false,      _ICODE_PCOUNT,                          false,              NULL,                   NULL },
		{ "pemstatus",              9,          false,      _ICODE_PEMSTATUS,                       false,              NULL,                   NULL },
		{ "pi",                     2,          false,      _ICODE_PI,                              false,              NULL,                   NULL },
		{ "popup",                  5,          false,      _ICODE_POPUP,                           false,              NULL,                   NULL },
		{ "primary",                7,          false,      _ICODE_PRIMARY,                         false,              NULL,                   NULL },
		{ "printstatus",            11,         false,      _ICODE_PRINTSTATUS,                     false,              NULL,                   NULL },
		{ "prmbar",                 6,          false,      _ICODE_PRMBAR,                          false,              NULL,                   NULL },
		{ "prmpad",                 6,          false,      _ICODE_PRMPAD,                          false,              NULL,                   NULL },
		{ "program",                7,          false,      _ICODE_PROGRAM,                         false,              NULL,                   NULL },
		{ "prompt",                 6,          false,      _ICODE_PROMPT,                          false,              NULL,                   NULL },
		{ "proper",                 6,          false,      _ICODE_PROPER,                          false,              NULL,                   NULL },
		{ "prow",                   4,          false,      _ICODE_PROW,                            false,              NULL,                   NULL },
		{ "prtinfo",                7,          false,      _ICODE_PRTINFO,                         false,              NULL,                   NULL },
		{ "putfile",                7,          false,      _ICODE_PUTFILE,                         false,              NULL,                   NULL },
		{ "pv",                     2,          false,      _ICODE_PV,                              false,              NULL,                   NULL },
		{ "quarter",                7,          false,      _ICODE_QUARTER,                         false,              NULL,                   NULL },
		{ "raiseevent",             10,         false,      _ICODE_RAISEEVENT,                      false,              NULL,                   NULL },
		{ "rand",                   4,          false,      _ICODE_RAND,                            false,              NULL,                   NULL },
		{ "ratc",                   4,          false,      _ICODE_RATC,                            false,              NULL,                   NULL },
		{ "rat",                    3,          false,      _ICODE_RAT,                             false,              NULL,                   NULL },
		{ "ratline",                7,          false,      _ICODE_RATLINE,                         false,              NULL,                   NULL },
		{ "rdlevel",                7,          false,      _ICODE_RDLEVEL,                         false,              NULL,                   NULL },
		{ "readkey",                7,          false,      _ICODE_READKEY,                         false,              NULL,                   NULL },
		{ "reccount",               8,          false,      _ICODE_RECCOUNT,                        false,              NULL,                   NULL },
		{ "recno",                  5,          false,      _ICODE_RECNO,                           false,              NULL,                   NULL },
		{ "recsize",                7,          false,      _ICODE_RECSIZE,                         false,              NULL,                   NULL },
		{ "refresh",                7,          false,      _ICODE_REFRESH,                         false,              NULL,                   NULL },
		{ "relation",               8,          false,      _ICODE_RELATION,                        false,              NULL,                   NULL },
		{ "replicate",              9,          false,      _ICODE_REPLICATE,                       false,              NULL,                   NULL },
		{ "requery",                7,          false,      _ICODE_REQUERY,                         false,              NULL,                   NULL },
		{ "rgb",                    3,          false,      _ICODE_RGB,                             false,              NULL,                   NULL },
		{ "rgbscheme",              9,          false,      _ICODE_RGBSCHEME,                       false,              NULL,                   NULL },
		{ "right",                  5,          false,      _ICODE_RIGHT,                           false,              NULL,                   NULL },
		{ "rightc",                 6,          false,      _ICODE_RIGHTC,                          false,              NULL,                   NULL },
		{ "rlock",                  5,          false,      _ICODE_RLOCK,                           false,              NULL,                   NULL },
		{ "round",                  5,          false,      _ICODE_ROUND,                           false,              NULL,                   NULL },
		{ "row",                    3,          false,      _ICODE_ROW,                             false,              NULL,                   NULL },
		{ "rtod",                   4,          false,      _ICODE_RTOD,                            false,              NULL,                   NULL },
		{ "rtrim",                  5,          false,      _ICODE_RTRIM,                           false,              NULL,                   NULL },
		{ "savepicture",            11,         false,      _ICODE_SAVEPICTURE,                     false,              NULL,                   NULL },
		{ "scheme",                 6,          false,      _ICODE_SCHEME,                          false,              NULL,                   NULL },
		{ "scols",                  5,          false,      _ICODE_SCOLS,                           false,              NULL,                   NULL },
		{ "seconds",                7,          false,      _ICODE_SECONDS,                         false,              NULL,                   NULL },
		{ "sec",                    3,          false,      _ICODE_SEC,                             false,              NULL,                   NULL },
		{ "seek",                   4,          false,      _ICODE_SEEK,                            false,              NULL,                   NULL },
		{ "select",                 6,          false,      _ICODE_SELECT,                          false,              NULL,                   NULL },
		{ "set",                    3,          false,      _ICODE_SET,                             false,              NULL,                   NULL },
		{ "setfldstate",            11,         false,      _ICODE_SETFLDSTATE,                     false,              NULL,                   NULL },
		{ "setresultset",           12,         false,      _ICODE_SETRESULTSET,                    false,              NULL,                   NULL },
		{ "sign",                   4,          false,      _ICODE_SIGN,                            false,              NULL,                   NULL },
		{ "sin",                    3,          false,      _ICODE_SIN,                             false,              NULL,                   NULL },
		{ "skpbar",                 6,          false,      _ICODE_SKPBAR,                          false,              NULL,                   NULL },
		{ "skppad",                 6,          false,      _ICODE_SKPPAD,                          false,              NULL,                   NULL },
		{ "soundex",                7,          false,      _ICODE_SOUNDEX,                         false,              NULL,                   NULL },
		{ "space",                  5,          false,      _ICODE_SPACE,                           false,              NULL,                   NULL },
		{ "sqlcancel",              9,          false,      _ICODE_SQLCANCEL,                       false,              NULL,                   NULL },
		{ "sqlcolumns",             10,         false,      _ICODE_SQLCOLUMNS,                      false,              NULL,                   NULL },
		{ "sqlcommit",              9,          false,      _ICODE_SQLCOMMIT,                       false,              NULL,                   NULL },
		{ "sqlconnect",             10,         false,      _ICODE_SQLCONNECT,                      false,              NULL,                   NULL },
		{ "sqldisconnect",          13,         false,      _ICODE_SQLDISCONNECT,                   false,              NULL,                   NULL },
		{ "sqlexec",                7,          false,      _ICODE_SQLEXEC,                         false,              NULL,                   NULL },
		{ "sqlgetprop",             10,         false,      _ICODE_SQLGETPROP,                      false,              NULL,                   NULL },
		{ "sqlidledisconnect",      17,         false,      _ICODE_SQLIDLEDISCONNECT,               false,              NULL,                   NULL },
		{ "sqlmoreresults",         14,         false,      _ICODE_SQLMORERESULTS,                  false,              NULL,                   NULL },
		{ "sqlprepare",             10,         false,      _ICODE_SQLPREPARE,                      false,              NULL,                   NULL },
		{ "sqlrollback",            11,         false,      _ICODE_SQLROLLBACK,                     false,              NULL,                   NULL },
		{ "sqlsetprop",             10,         false,      _ICODE_SQLSETPROP,                      false,              NULL,                   NULL },
		{ "sqlstringconnect",       16,         false,      _ICODE_SQLSTRINGCONNECT,                false,              NULL,                   NULL },
		{ "sqltables",              9,          false,      _ICODE_SQLTABLES,                       false,              NULL,                   NULL },
		{ "sqrt",                   4,          false,      _ICODE_SQRT,                            false,              NULL,                   NULL },
		{ "srows",                  5,          false,      _ICODE_SROWS,                           false,              NULL,                   NULL },
		{ "strconv",                7,          false,      _ICODE_STRCONV,                         false,              NULL,                   NULL },
		{ "strextract",             10,         false,      _ICODE_STREXTRACT,                      false,              NULL,                   NULL },
		{ "strtofile",              9,          false,      _ICODE_STRTOFILE,                       false,              NULL,                   NULL },
		{ "strtran",                7,          false,      _ICODE_STRTRAN,                         false,              NULL,                   NULL },
		{ "str",                    3,          false,      _ICODE_STR,                             false,              NULL,                   NULL },
		{ "stuffc",                 6,          false,      _ICODE_STUFFC,                          false,              NULL,                   NULL },
		{ "stuff",                  5,          false,      _ICODE_STUFF,                           false,              NULL,                   NULL },
		{ "substrc",                7,          false,      _ICODE_SUBSTRC,                         false,              NULL,                   NULL },
		{ "substr",                 6,          false,      _ICODE_SUBSTR,                          false,              NULL,                   NULL },
		{ "sysmetric",              9,          false,      _ICODE_SYSMETRIC,                       false,              NULL,                   NULL },
		{ "sys",                    3,          false,      _ICODE_SYS,                             false,              NULL,                   NULL },
		{ "tablerevert",            11,         false,      _ICODE_TABLEREVERT,                     false,              NULL,                   NULL },
		{ "tableupdate",            11,         false,      _ICODE_TABLEUPDATE,                     false,              NULL,                   NULL },
		{ "tag",                    3,          false,      _ICODE_TAG,                             false,              NULL,                   NULL },
		{ "tagcount",               8,          false,      _ICODE_TAGCOUNT,                        false,              NULL,                   NULL },
		{ "tagno",                  5,          false,      _ICODE_TAGNO,                           false,              NULL,                   NULL },
		{ "tan",                    3,          false,      _ICODE_TAN,                             false,              NULL,                   NULL },
		{ "target",                 6,          false,      _ICODE_TARGET,                          false,              NULL,                   NULL },
		{ "textmerge",              9,          false,      _ICODE_TEXTMERGE,                       false,              NULL,                   NULL },
		{ "time",                   4,          false,      _ICODE_TIME,                            false,              NULL,                   NULL },
		{ "transform",              9,          false,      _ICODE_TRANSFORM,                       false,              NULL,                   NULL },
		{ "trim",                   4,          false,      _ICODE_TRIM,                            false,              NULL,                   NULL },
		{ "ttoc",                   4,          false,      _ICODE_TTOC,                            false,              NULL,                   NULL },
		{ "ttod",                   4,          false,      _ICODE_TTOD,                            false,              NULL,                   NULL },
		{ "txnlevel",               8,          false,      _ICODE_TXNLEVEL,                        false,              NULL,                   NULL },
		{ "txtwidth",               8,          false,      _ICODE_TXTWIDTH,                        false,              NULL,                   NULL },
		{ "type",                   4,          false,      _ICODE_TYPE,                            false,              NULL,                   NULL },
		{ "unbindevents",           12,         false,      _ICODE_UNBINDEVENTS,                    false,              NULL,                   NULL },
		{ "unique",                 6,          false,      _ICODE_UNIQUE,                          false,              NULL,                   NULL },
		{ "updated",                7,          false,      _ICODE_UPDATED,                         false,              NULL,                   NULL },
		{ "upper",                  5,          false,      _ICODE_UPPER,                           false,              NULL,                   NULL },
		{ "used",                   4,          false,      _ICODE_USED,                            false,              NULL,                   NULL },
		{ "val",                    3,          false,      _ICODE_VAL,                             false,              NULL,                   NULL },
		{ "varread",                7,          false,      _ICODE_VARREAD,                         false,              NULL,                   NULL },
		{ "vartype",                7,          false,      _ICODE_VARTYPE,                         false,              NULL,                   NULL },
		{ "version",                7,          false,      _ICODE_VERSION,                         false,              NULL,                   NULL },
		{ "wborder",                7,          false,      _ICODE_WBORDER,                         false,              NULL,                   NULL },
		{ "wchild",                 6,          false,      _ICODE_WCHILD,                          false,              NULL,                   NULL },
		{ "wcols",                  5,          false,      _ICODE_WCOLS,                           false,              NULL,                   NULL },
		{ "wdockable",              9,          false,      _ICODE_WDOCKABLE,                       false,              NULL,                   NULL },
		{ "week",                   4,          false,      _ICODE_WEEK,                            false,              NULL,                   NULL },
		{ "wexist",                 6,          false,      _ICODE_WEXIST,                          false,              NULL,                   NULL },
		{ "wfont",                  5,          false,      _ICODE_WFONT,                           false,              NULL,                   NULL },
		{ "wlast",                  5,          false,      _ICODE_WLAST,                           false,              NULL,                   NULL },
		{ "wlcol",                  5,          false,      _ICODE_WLCOL,                           false,              NULL,                   NULL },
		{ "wlrow",                  5,          false,      _ICODE_WLROW,                           false,              NULL,                   NULL },
		{ "wmaximum",               8,          false,      _ICODE_WMAXIMUM,                        false,              NULL,                   NULL },
		{ "wminimum",               8,          false,      _ICODE_WMINIMUM,                        false,              NULL,                   NULL },
		{ "wontop",                 6,          false,      _ICODE_WONTOP,                          false,              NULL,                   NULL },
		{ "woutput",                7,          false,      _ICODE_WOUTPUT,                         false,              NULL,                   NULL },
		{ "wparent",                7,          false,      _ICODE_WPARENT,                         false,              NULL,                   NULL },
		{ "wread",                  5,          false,      _ICODE_WREAD,                           false,              NULL,                   NULL },
		{ "wrows",                  5,          false,      _ICODE_WROWS,                           false,              NULL,                   NULL },
		{ "wtitle",                 6,          false,      _ICODE_WTITLE,                          false,              NULL,                   NULL },
		{ "wvisible",               8,          false,      _ICODE_WVISIBLE,                        false,              NULL,                   NULL },
		{ "xmltocursor",            11,         false,      _ICODE_XMLTOCURSOR,                     false,              NULL,                   NULL },
		{ "xmlupdategram",          13,         false,      _ICODE_XMLUPDATEGRAM,                   false,              NULL,                   NULL },
		{ "year",                   4,          false,      _ICODE_YEAR,                            false,              NULL,                   NULL },

		{ "activate",              	8,          false,      _ICODE_ACTIVATE,						false,              NULL,                   NULL },
		{ "add",                   	3,          false,      _ICODE_ADD,								false,              NULL,                   NULL },
		{ "alter",                 	5,          false,      _ICODE_ALTER,							false,              NULL,                   NULL },
		{ "alternate",             	9,          false,      _ICODE_ALTERNATE,						false,              NULL,                   NULL },
		{ "ansi",                  	4,          false,      _ICODE_ANSI,							false,              NULL,                   NULL },
		{ "app",                   	3,          false,      _ICODE_APP,								false,              NULL,                   NULL },
		{ "append",                	6,          false,      _ICODE_APPEND,							false,              NULL,                   NULL },
		{ "array",                 	5,          false,      _ICODE_ARRAY,							false,              NULL,                   NULL },
		{ "asserts",               	7,          false,      _ICODE_ASSERTS,							false,              NULL,                   NULL },
		{ "assert",                	6,          false,      _ICODE_ASSERT,							false,              NULL,                   NULL },
		{ "assist",                	6,          false,      _ICODE_ASSIST,							false,              NULL,                   NULL },
		{ "autoincerror",         	12,         false,      _ICODE_AUTOINCERROR,					false,              NULL,                   NULL },
		{ "autosave",              	8,          false,      _ICODE_AUTOSAVE,						false,              NULL,                   NULL },
		{ "average",               	7,          false,      _ICODE_AVERAGE,							false,              NULL,                   NULL },
		{ "bar",                   	3,          false,      _ICODE_BAR,								false,              NULL,                   NULL },
		{ "begin",                 	5,          false,      _ICODE_BEGIN,							false,              NULL,                   NULL },
		{ "bell",                  	4,          false,      _ICODE_BELL,							false,              NULL,                   NULL },
		{ "blank",                 	5,          false,      _ICODE_BLANK,							false,              NULL,                   NULL },
		{ "blocksize",             	9,          false,      _ICODE_BLOCKSIZE,						false,              NULL,                   NULL },
		{ "border",                	6,          false,      _ICODE_BORDER,							false,              NULL,                   NULL },
		{ "box",                   	3,          false,      _ICODE_BOX,								false,              NULL,                   NULL },
		{ "browse",                	6,          false,      _ICODE_BROWSE,							false,              NULL,                   NULL },
		{ "browseime",             	9,          false,      _ICODE_BROWSEIME,						false,              NULL,                   NULL },
		{ "brstatus",              	8,          false,      _ICODE_BRSTATUS,						false,              NULL,                   NULL },
		{ "build",                 	5,          false,      _ICODE_BUILD,							false,              NULL,                   NULL },
		{ "calculate",             	9,          false,      _ICODE_CALCULATE,						false,              NULL,                   NULL },
		{ "call",                  	4,          false,      _ICODE_CALL,							false,              NULL,                   NULL },
		{ "cancel",                	6,          false,      _ICODE_CANCEL,							false,              NULL,                   NULL },
		{ "carry",                 	5,          false,      _ICODE_CARRY,							false,              NULL,                   NULL },
		{ "case",                  	4,          false,      _ICODE_CASE,							false,              NULL,                   NULL },
		{ "catch",                 	5,          false,      _ICODE_CATCH,							false,              NULL,                   NULL },
		{ "cd",                    	2,          false,      _ICODE_CD,								false,              NULL,                   NULL },
		{ "century",               	7,          false,      _ICODE_CENTURY,							false,              NULL,                   NULL },
		{ "change",                	6,          false,      _ICODE_CHANGE,							false,              NULL,                   NULL },
		{ "chdir",                 	5,          false,      _ICODE_CHDIR,							false,              NULL,                   NULL },
		{ "class",                 	5,          false,      _ICODE_CLASS,							false,              NULL,                   NULL },
		{ "classlib",              	8,          false,      _ICODE_CLASSLIB,						false,              NULL,                   NULL },
		{ "clear",                 	5,          false,      _ICODE_CLEAR,							false,              NULL,                   NULL },
		{ "clears",                	6,          false,      _ICODE_CLEARS,							false,              NULL,                   NULL },
		{ "clock",                 	5,          false,      _ICODE_CLOCK,							false,              NULL,                   NULL },
		{ "close",                 	5,          false,      _ICODE_CLOSE,							false,              NULL,                   NULL },
		{ "closes",                	6,          false,      _ICODE_CLOSES,							false,              NULL,                   NULL },
		{ "collate",               	7,          false,      _ICODE_COLLATE,							false,              NULL,                   NULL },
		{ "color",                 	5,          false,      _ICODE_COLOR,							false,              NULL,                   NULL },
		{ "compatible",           	10,         false,      _ICODE_COMPATIBLE,						false,              NULL,                   NULL },
		{ "compile",               	7,          false,      _ICODE_COMPILE,							false,              NULL,                   NULL },
		{ "confirm",               	7,          false,      _ICODE_CONFIRM,							false,              NULL,                   NULL },
		{ "connection",           	10,         false,      _ICODE_CONNECTION,						false,              NULL,                   NULL },
		{ "connections",          	11,         false,      _ICODE_CONNECTIONS,						false,              NULL,                   NULL },
		{ "console",               	7,          false,      _ICODE_CONSOLE,							false,              NULL,                   NULL },
		{ "continue",              	8,          false,      _ICODE_CONTINUE,						false,              NULL,                   NULL },
		{ "copy",                  	4,          false,      _ICODE_COPY,							false,              NULL,                   NULL },
		{ "count",                 	5,          false,      _ICODE_COUNT,							false,              NULL,                   NULL },
		{ "coverage",              	8,          false,      _ICODE_COVERAGE,						false,              NULL,                   NULL },
		{ "cpcompile",             	9,          false,      _ICODE_CPCOMPILE,						false,              NULL,                   NULL },
		{ "cpdialog",              	8,          false,      _ICODE_CPDIALOG,						false,              NULL,                   NULL },
		{ "create",                	6,          false,      _ICODE_CREATE,							false,              NULL,                   NULL },
		{ "currency",              	8,          false,      _ICODE_CURRENCY,						false,              NULL,                   NULL },
		{ "cursor",                	6,          false,      _ICODE_CURSOR,							false,              NULL,                   NULL },
		{ "database",              	8,          false,      _ICODE_DATABASE,						false,              NULL,                   NULL },
		{ "datasession",          	11,         false,      _ICODE_DATASESSION,						false,              NULL,                   NULL },
		{ "date",                  	4,          false,      _ICODE_DATE,							false,              NULL,                   NULL },
		{ "deactivate",           	10,         false,      _ICODE_DEACTIVATE,						false,              NULL,                   NULL },
		{ "debug",                 	5,          false,      _ICODE_DEBUG,							false,              NULL,                   NULL },
		{ "debugout",              	8,          false,      _ICODE_DEBUGOUT,						false,              NULL,                   NULL },
		{ "decimals",              	8,          false,      _ICODE_DECIMALS,						false,              NULL,                   NULL },
		{ "declare",               	7,          false,      _ICODE_DECLARE,							false,              NULL,                   NULL },
		{ "default",               	7,          false,      _ICODE_DEFAULT,							false,              NULL,                   NULL },
		{ "define",                	6,          false,      _ICODE_DEFINE,							false,              NULL,                   NULL },
		{ "delete",                	6,          false,      _ICODE_DELETE,							false,              NULL,                   NULL },
		{ "deleted",               	7,          false,      _ICODE_DELETED,							false,              NULL,                   NULL },
		{ "delimiters",           	10,         false,      _ICODE_DELIMITERS,						false,              NULL,                   NULL },
		{ "development",          	11,         false,      _ICODE_DEVELOPMENT,						false,              NULL,                   NULL },
		{ "device",                	6,          false,      _ICODE_DEVICE,							false,              NULL,                   NULL },
		{ "dimension",             	9,          false,      _ICODE_DIMENSION,						false,              NULL,                   NULL },
		{ "dir",                   	3,          false,      _ICODE_DIR,								false,              NULL,                   NULL },
		{ "directory",             	9,          false,      _ICODE_DIRECTORY,						false,              NULL,                   NULL },
		{ "display",               	7,          false,      _ICODE_DISPLAY,							false,              NULL,                   NULL },
		{ "dlls",                  	4,          false,      _ICODE_DLLS,							false,              NULL,                   NULL },
		{ "dll",                   	3,          false,      _ICODE_DLL,								false,              NULL,                   NULL },
		{ "do",                    	2,          false,      _ICODE_DO,								false,              NULL,                   NULL },
		{ "dock",                  	4,          false,      _ICODE_DOCK,							false,              NULL,                   NULL },
		{ "doevents",              	8,          false,      _ICODE_DOEVENTS,						false,              NULL,                   NULL },
		{ "dohistory",             	9,          false,      _ICODE_DOHISTORY,						false,              NULL,                   NULL },
		{ "drop",                  	4,          false,      _ICODE_DROP,							false,              NULL,                   NULL },
		{ "each",                  	4,          false,      _ICODE_EACH,							false,              NULL,                   NULL },
		{ "echo",                  	4,          false,      _ICODE_ECHO,							false,              NULL,                   NULL },
		{ "edit",                  	4,          false,      _ICODE_EDIT,							false,              NULL,                   NULL },
		{ "eject",                 	5,          false,      _ICODE_EJECT,							false,              NULL,                   NULL },
		{ "end",                   	3,          false,      _ICODE_END,								false,              NULL,                   NULL },
		{ "endcase",               	7,          false,      _ICODE_ENDCASE,							false,              NULL,                   NULL },
		{ "enddo",                 	5,          false,      _ICODE_ENDDO,							false,              NULL,                   NULL },
		{ "endfor",                	6,          false,      _ICODE_ENDFOR,							false,              NULL,                   NULL },
		{ "endif",                 	5,          false,      _ICODE_ENDIF,							false,              NULL,                   NULL },
		{ "endprintjob",          	11,         false,      _ICODE_ENDPRINTJOB,						false,              NULL,                   NULL },
		{ "endscan",               	7,          false,      _ICODE_ENDSCAN,							false,              NULL,                   NULL },
		{ "endtext",               	7,          false,      _ICODE_ENDTEXT,							false,              NULL,                   NULL },
		{ "endwith",               	7,          false,      _ICODE_ENDWITH,							false,              NULL,                   NULL },
		{ "enginebehavior",       	14,         false,      _ICODE_ENGINEBEHAVIOR,					false,              NULL,                   NULL },
		{ "erase",                 	5,          false,      _ICODE_ERASE,							false,              NULL,                   NULL },
		{ "error",                 	5,          false,      _ICODE_ERROR,							false,              NULL,                   NULL },
		{ "escape",                	6,          false,      _ICODE_ESCAPE,							false,              NULL,                   NULL },
		{ "eventlist",             	9,          false,      _ICODE_EVENTLIST,						false,              NULL,                   NULL },
		{ "events",                	6,          false,      _ICODE_EVENTS,							false,              NULL,                   NULL },
		{ "eventtracking",        	13,         false,      _ICODE_EVENTTRACKING,					false,              NULL,                   NULL },
		{ "exact",                 	5,          false,      _ICODE_EXACT,							false,              NULL,                   NULL },
		{ "exclusive",             	9,          false,      _ICODE_EXCLUSIVE,						false,              NULL,                   NULL },
		{ "exe",                   	3,          false,      _ICODE_EXE,								false,              NULL,                   NULL },
		{ "exit",                  	4,          false,      _ICODE_EXIT,							false,              NULL,                   NULL },
		{ "export",                	6,          false,      _ICODE_EXPORT,							false,              NULL,                   NULL },
		{ "extended",              	8,          false,      _ICODE_EXTENDED,						false,              NULL,                   NULL },
		{ "external",              	8,          false,      _ICODE_EXTERNAL,						false,              NULL,                   NULL },
		{ "fdow",                  	4,          false,      _ICODE_FDOW,							false,              NULL,                   NULL },
		{ "fields",                	6,          false,      _ICODE_FIELDS,							false,              NULL,                   NULL },
		{ "files",                 	5,          false,      _ICODE_FILES,							false,              NULL,                   NULL },
		{ "file",                  	4,          false,      _ICODE_FILE,							false,              NULL,                   NULL },
		{ "fill",                  	4,          false,      _ICODE_FILL,							false,              NULL,                   NULL },
		{ "filter",                	6,          false,      _ICODE_FILTER,							false,              NULL,                   NULL },
		{ "finally",               	7,          false,      _ICODE_FINALLY,							false,              NULL,                   NULL },
		{ "find",                  	4,          false,      _ICODE_FIND,							false,              NULL,                   NULL },
		{ "fixed",                 	5,          false,      _ICODE_FIXED,							false,              NULL,                   NULL },
		{ "flush",                 	5,          false,      _ICODE_FLUSH,							false,              NULL,                   NULL },
		{ "format",                	6,          false,      _ICODE_FORMAT,							false,              NULL,                   NULL },
		{ "form",                  	4,          false,      _ICODE_FORM,							false,              NULL,                   NULL },
		{ "for",                   	3,          false,      _ICODE_FOR,								false,              NULL,                   NULL },
		{ "free",                  	4,          false,      _ICODE_FREE,							false,              NULL,                   NULL },
		{ "from",                  	4,          false,      _ICODE_FROM,							false,              NULL,                   NULL },
		{ "fullpath",              	8,          false,      _ICODE_FULLPATH,						false,              NULL,                   NULL },
		{ "function",              	8,          false,      _ICODE_FUNCTION,						false,              NULL,                   NULL },
		{ "fweek",                 	5,          false,      _ICODE_FWEEK,							false,              NULL,                   NULL },
		{ "gather",                	6,          false,      _ICODE_GATHER,							false,              NULL,                   NULL },
		{ "general",               	7,          false,      _ICODE_GENERAL,							false,              NULL,                   NULL },
		{ "getexpr",               	7,          false,      _ICODE_GETEXPR,							false,              NULL,                   NULL },
		{ "gets",                  	4,          false,      _ICODE_GETS,							false,              NULL,                   NULL },
		{ "get",                   	3,          false,      _ICODE_GET,								false,              NULL,                   NULL },
		{ "go",                    	2,          false,      _ICODE_GO,								false,              NULL,                   NULL },
		{ "goto",                  	4,          false,      _ICODE_GOTO,							false,              NULL,                   NULL },
		{ "headings",              	8,          false,      _ICODE_HEADINGS,						false,              NULL,                   NULL },
		{ "help",                  	4,          false,      _ICODE_HELP,							false,              NULL,                   NULL },
		{ "hide",                  	4,          false,      _ICODE_HIDE,							false,              NULL,                   NULL },
		{ "hours",                 	5,          false,      _ICODE_HOURS,							false,              NULL,                   NULL },
		{ "id",                    	2,          false,      _ICODE_ID,								false,              NULL,                   NULL },
		{ "if",                    	2,          false,      _ICODE_IF,								false,              NULL,                   NULL },
		{ "import",                	6,          false,      _ICODE_IMPORT,							false,              NULL,                   NULL },
		{ "indexes",               	7,          false,      _ICODE_INDEXES,							false,              NULL,                   NULL },
		{ "index",                 	5,          false,      _ICODE_INDEX,							false,              NULL,                   NULL },
		{ "input",                 	5,          false,      _ICODE_INPUT,							false,              NULL,                   NULL },
		{ "insert",                	6,          false,      _ICODE_INSERT,							false,              NULL,                   NULL },
		{ "intensity",             	9,          false,      _ICODE_INTENSITY,						false,              NULL,                   NULL },
		{ "join",                  	4,          false,      _ICODE_JOIN,							false,              NULL,                   NULL },
		{ "key",                   	3,          false,      _ICODE_KEY,								false,              NULL,                   NULL },
		{ "keyboard",              	8,          false,      _ICODE_KEYBOARD,						false,              NULL,                   NULL },
		{ "keycomp",               	7,          false,      _ICODE_KEYCOMP,							false,              NULL,                   NULL },
		{ "label",                 	5,          false,      _ICODE_LABEL,							false,              NULL,                   NULL },
		{ "library",               	7,          false,      _ICODE_LIBRARY,							false,              NULL,                   NULL },
		{ "lists",                 	5,          false,      _ICODE_LISTS,							false,              NULL,                   NULL },
		{ "list",                  	4,          false,      _ICODE_LIST,							false,              NULL,                   NULL },
		{ "load",                  	4,          false,      _ICODE_LOAD,							false,              NULL,                   NULL },
		{ "local",                 	5,          false,      _ICODE_LOCAL,							false,              NULL,                   NULL },
		{ "locate",                	6,          false,      _ICODE_LOCATE,							false,              NULL,                   NULL },
		{ "lock",                  	4,          false,      _ICODE_LOCK,							false,              NULL,                   NULL },
		{ "logerrors",             	9,          false,      _ICODE_LOGERRORS,						false,              NULL,                   NULL },
		{ "loop",                  	4,          false,      _ICODE_LOOP,							false,              NULL,                   NULL },
		{ "lparameters",          	11,         false,      _ICODE_LPARAMETERS,						false,              NULL,                   NULL },
		{ "mackey",                	6,          false,      _ICODE_MACKEY,							false,              NULL,                   NULL },
		{ "macros",                	6,          false,      _ICODE_MACROS,							false,              NULL,                   NULL },
		{ "macro",                 	5,          false,      _ICODE_MACRO,							false,              NULL,                   NULL },
		{ "margin",                	6,          false,      _ICODE_MARGIN,							false,              NULL,                   NULL },
		{ "mark",                  	4,          false,      _ICODE_MARK,							false,              NULL,                   NULL },
		{ "md",                    	2,          false,      _ICODE_MD,								false,              NULL,                   NULL },
		{ "memowidth",             	9,          false,      _ICODE_MEMOWIDTH,						false,              NULL,                   NULL },
		{ "memory",                	6,          false,      _ICODE_MEMORY,							false,              NULL,                   NULL },
		{ "memo",                  	4,          false,      _ICODE_MEMO,							false,              NULL,                   NULL },
		{ "menus",                 	5,          false,      _ICODE_MENUS,							false,              NULL,                   NULL },
		{ "menu",                  	4,          false,      _ICODE_MENU,							false,              NULL,                   NULL },
		{ "message",               	7,          false,      _ICODE_MESSAGE,							false,              NULL,                   NULL },
		{ "mkdir",                 	5,          false,      _ICODE_MKDIR,							false,              NULL,                   NULL },
		{ "modify",                	6,          false,      _ICODE_MODIFY,							false,              NULL,                   NULL },
		{ "mouse",                 	5,          false,      _ICODE_MOUSE,							false,              NULL,                   NULL },
		{ "move",                  	4,          false,      _ICODE_MOVE,							false,              NULL,                   NULL },
		{ "mtdll",                 	5,          false,      _ICODE_MTDLL,							false,              NULL,                   NULL },
		{ "multilocks",           	10,         false,      _ICODE_MULTILOCKS,						false,              NULL,                   NULL },
		{ "near",                  	4,          false,      _ICODE_NEAR,							false,              NULL,                   NULL },
		{ "next",                  	4,          false,      _ICODE_NEXT,							false,              NULL,                   NULL },
		{ "nocptrans",             	9,          false,      _ICODE_NOCPTRANS,						false,              NULL,                   NULL },
		{ "note",                  	4,          false,      _ICODE_NOTE,							false,              NULL,                   NULL },
		{ "notify",                	6,          false,      _ICODE_NOTIFY,							false,              NULL,                   NULL },
		{ "null",                  	4,          false,      _ICODE_NULL,							false,              NULL,                   NULL },
		{ "nulldisplay",          	11,         false,      _ICODE_NULLDISPLAY,						false,              NULL,                   NULL },
		{ "objects",               	7,          false,      _ICODE_OBJECTS,							false,              NULL,                   NULL },
		{ "object",                	6,          false,      _ICODE_OBJECT,							false,              NULL,                   NULL },
		{ "odometer",              	8,          false,      _ICODE_ODOMETER,						false,              NULL,                   NULL },
		{ "off",                   	3,          false,      _ICODE_OFF,								false,              NULL,                   NULL },
		{ "of",                    	2,          false,      _ICODE_OF,								false,              NULL,                   NULL },
		{ "oleobject",             	9,          false,      _ICODE_OLEOBJECT,						false,              NULL,                   NULL },
		{ "on",                    	2,          false,      _ICODE_ON,								false,              NULL,                   NULL },
		{ "open",                  	4,          false,      _ICODE_OPEN,							false,              NULL,                   NULL },
		{ "optimize",              	8,          false,      _ICODE_OPTIMIZE,						false,              NULL,                   NULL },
		{ "order",                 	5,          false,      _ICODE_ORDER,							false,              NULL,                   NULL },
		{ "or",                    	2,          false,      _ICODE_OR,								false,              NULL,                   NULL },
		{ "overview",              	8,          false,      _ICODE_OVERVIEW,						false,              NULL,                   NULL },
		{ "pack",                  	4,          false,      _ICODE_PACK,							false,              NULL,                   NULL },
		{ "pad",                   	3,          false,      _ICODE_PAD,								false,              NULL,                   NULL },
		{ "page",                  	4,          false,      _ICODE_PAGE,							false,              NULL,                   NULL },
		{ "palette",               	7,          false,      _ICODE_PALETTE,							false,              NULL,                   NULL },
		{ "parameters",           	10,         false,      _ICODE_PARAMETERS,						false,              NULL,                   NULL },
		{ "path",                  	4,          false,      _ICODE_PATH,							false,              NULL,                   NULL },
		{ "pdsetup",               	7,          false,      _ICODE_PDSETUP,							false,              NULL,                   NULL },
		{ "play",                  	4,          false,      _ICODE_PLAY,							false,              NULL,                   NULL },
		{ "point",                 	5,          false,      _ICODE_POINT,							false,              NULL,                   NULL },
		{ "pop",                   	3,          false,      _ICODE_POP,								false,              NULL,                   NULL },
		{ "popups",                	6,          false,      _ICODE_POPUPS,							false,              NULL,                   NULL },
		{ "popup",                 	5,          false,      _ICODE_POPUP,							false,              NULL,                   NULL },
		{ "printer",               	7,          false,      _ICODE_PRINTER,							false,              NULL,                   NULL },
		{ "printjob",              	8,          false,      _ICODE_PRINTJOB,						false,              NULL,                   NULL },
		{ "private",               	7,          false,      _ICODE_PRIVATE,							false,              NULL,                   NULL },
		{ "procedures",           	10,         false,      _ICODE_PROCEDURES,						false,              NULL,                   NULL },
		{ "procedure",             	9,          false,      _ICODE_PROCEDURE,						false,              NULL,                   NULL },
		{ "project",               	7,          false,      _ICODE_PROJECT,							false,              NULL,                   NULL },
		{ "prompt",                	6,          false,      _ICODE_PROMPT,							false,              NULL,                   NULL },
		{ "public",                	6,          false,      _ICODE_PUBLIC,							false,              NULL,                   NULL },
		{ "push",                  	4,          false,      _ICODE_PUSH,							false,              NULL,                   NULL },
		{ "query",                 	5,          false,      _ICODE_QUERY,							false,              NULL,                   NULL },
		{ "quit",                  	4,          false,      _ICODE_QUIT,							false,              NULL,                   NULL },
		{ "rd",                    	2,          false,      _ICODE_RD,								false,              NULL,                   NULL },
		{ "read",                  	4,          false,      _ICODE_READ,							false,              NULL,                   NULL },
		{ "readborder",           	10,         false,      _ICODE_READBORDER,						false,              NULL,                   NULL },
		{ "readerror",             	9,          false,      _ICODE_READERROR,						false,              NULL,                   NULL },
		{ "recall",                	6,          false,      _ICODE_RECALL,							false,              NULL,                   NULL },
		{ "refresh",               	7,          false,      _ICODE_REFRESH,							false,              NULL,                   NULL },
		{ "reindex",               	7,          false,      _ICODE_REINDEX,							false,              NULL,                   NULL },
		{ "relation",              	8,          false,      _ICODE_RELATION,						false,              NULL,                   NULL },
		{ "release",               	7,          false,      _ICODE_RELEASE,							false,              NULL,                   NULL },
		{ "remove",                	6,          false,      _ICODE_REMOVE,							false,              NULL,                   NULL },
		{ "rename",                	6,          false,      _ICODE_RENAME,							false,              NULL,                   NULL },
		{ "replace",               	7,          false,      _ICODE_REPLACE,							false,              NULL,                   NULL },
		{ "report",                	6,          false,      _ICODE_REPORT,							false,              NULL,                   NULL },
		{ "reprocess",             	9,          false,      _ICODE_REPROCESS,						false,              NULL,                   NULL },
		{ "resource",              	8,          false,      _ICODE_RESOURCE,						false,              NULL,                   NULL },
		{ "restore",               	7,          false,      _ICODE_RESTORE,							false,              NULL,                   NULL },
		{ "resume",                	6,          false,      _ICODE_RESUME,							false,              NULL,                   NULL },
		{ "retry",                 	5,          false,      _ICODE_RETRY,							false,              NULL,                   NULL },
		{ "return",                	6,          false,      _ICODE_RETURN,							false,              NULL,                   NULL },
		{ "rmdir",                 	5,          false,      _ICODE_RMDIR,							false,              NULL,                   NULL },
		{ "rollback",              	8,          false,      _ICODE_ROLLBACK,						false,              NULL,                   NULL },
		{ "run",                   	3,          false,      _ICODE_RUN,								false,              NULL,                   NULL },
		{ "safety",                	6,          false,      _ICODE_SAFETY,							false,              NULL,                   NULL },
		{ "save",                  	4,          false,      _ICODE_SAVE,							false,              NULL,                   NULL },
		{ "say",                   	3,          false,      _ICODE_SAY,								false,              NULL,                   NULL },
		{ "scan",                  	4,          false,      _ICODE_SCAN,							false,              NULL,                   NULL },
		{ "scatter",               	7,          false,      _ICODE_SCATTER,							false,              NULL,                   NULL },
		{ "scheme",                	6,          false,      _ICODE_SCHEME,							false,              NULL,                   NULL },
		{ "screen",                	6,          false,      _ICODE_SCREEN,							false,              NULL,                   NULL },
		{ "scroll",                	6,          false,      _ICODE_SCROLL,							false,              NULL,                   NULL },
		{ "seconds",               	7,          false,      _ICODE_SECONDS,							false,              NULL,                   NULL },
		{ "seek",                  	4,          false,      _ICODE_SEEK,							false,              NULL,                   NULL },
		{ "select",                	6,          false,      _ICODE_SELECT,							false,              NULL,                   NULL },
		{ "selection",             	9,          false,      _ICODE_SELECTION,						false,              NULL,                   NULL },
		{ "separator",             	9,          false,      _ICODE_SEPARATOR,						false,              NULL,                   NULL },
		{ "set",                   	3,          false,      _ICODE_SET,								false,              NULL,                   NULL },
		{ "show",                  	4,          false,      _ICODE_SHOW,							false,              NULL,                   NULL },
		{ "shutdown",              	8,          false,      _ICODE_SHUTDOWN,						false,              NULL,                   NULL },
		{ "size",                  	4,          false,      _ICODE_SIZE,							false,              NULL,                   NULL },
		{ "skip",                  	4,          false,      _ICODE_SKIP,							false,              NULL,                   NULL },
		{ "sort",                  	4,          false,      _ICODE_SORT,							false,              NULL,                   NULL },
		{ "space",                 	5,          false,      _ICODE_SPACE,							false,              NULL,                   NULL },
		{ "sql",                   	3,          false,      _ICODE_SQL,								false,              NULL,                   NULL },
		{ "status",                	6,          false,      _ICODE_STATUS,							false,              NULL,                   NULL },
		{ "step",                  	4,          false,      _ICODE_STEP,							false,              NULL,                   NULL },
		{ "store",                 	5,          false,      _ICODE_STORE,							false,              NULL,                   NULL },
		{ "strictdate",           	10,         false,      _ICODE_STRICTDATE,						false,              NULL,                   NULL },
		{ "structure",             	9,          false,      _ICODE_STRUCTURE,						false,              NULL,                   NULL },
		{ "sum",                   	3,          false,      _ICODE_SUM,								false,              NULL,                   NULL },
		{ "suspend",               	7,          false,      _ICODE_SUSPEND,							false,              NULL,                   NULL },
		{ "sysformats",           	10,         false,      _ICODE_SYSFORMATS,						false,              NULL,                   NULL },
		{ "sysmenu",               	7,          false,      _ICODE_SYSMENU,							false,              NULL,                   NULL },
		{ "sys",                   	3,          false,      _ICODE_SYS,								false,              NULL,                   NULL },
		{ "tablevalidate",        	13,         false,      _ICODE_TABLEVALIDATE,					false,              NULL,                   NULL },
		{ "tables",                	6,          false,      _ICODE_TABLES,							false,              NULL,                   NULL },
		{ "table",                 	5,          false,      _ICODE_TABLE,							false,              NULL,                   NULL },
		{ "tag",                   	3,          false,      _ICODE_TAG,								false,              NULL,                   NULL },
		{ "talk",                  	4,          false,      _ICODE_TALK,							false,              NULL,                   NULL },
		{ "textmerge",             	9,          false,      _ICODE_TEXTMERGE,						false,              NULL,                   NULL },
		{ "text",                  	4,          false,      _ICODE_TEXT,							false,              NULL,                   NULL },
		{ "to",                    	2,          false,      _ICODE_TO,								false,              NULL,                   NULL },
		{ "topic",                 	5,          false,      _ICODE_TOPIC,							false,              NULL,                   NULL },
		{ "total",                 	5,          false,      _ICODE_TOTAL,							false,              NULL,                   NULL },
		{ "transaction",          	11,         false,      _ICODE_TRANSACTION,						false,              NULL,                   NULL },
		{ "trbetween",             	9,          false,      _ICODE_TRBETWEEN,						false,              NULL,                   NULL },
		{ "trigger",               	7,          false,      _ICODE_TRIGGER,							false,              NULL,                   NULL },
		{ "try",                   	3,          false,      _ICODE_TRY,								false,              NULL,                   NULL },
		{ "type",                  	4,          false,      _ICODE_TYPE,							false,              NULL,                   NULL },
		{ "typeahead",             	9,          false,      _ICODE_TYPEAHEAD,						false,              NULL,                   NULL },
		{ "udfparms",              	8,          false,      _ICODE_UDFPARMS,						false,              NULL,                   NULL },
		{ "unique",                	6,          false,      _ICODE_UNIQUE,							false,              NULL,                   NULL },
		{ "unlock",                	6,          false,      _ICODE_UNLOCK,							false,              NULL,                   NULL },
		{ "update",                	6,          false,      _ICODE_UPDATE,							false,              NULL,                   NULL },
		{ "use",                   	3,          false,      _ICODE_USE,								false,              NULL,                   NULL },
		{ "validate",              	8,          false,      _ICODE_VALIDATE,						false,              NULL,                   NULL },
		{ "views",                 	5,          false,      _ICODE_VIEWS,							false,              NULL,                   NULL },
		{ "view",                  	4,          false,      _ICODE_VIEW,							false,              NULL,                   NULL },
		{ "wait",                  	4,          false,      _ICODE_WAIT,							false,              NULL,                   NULL },
		{ "while",                 	5,          false,      _ICODE_WHILE,							false,              NULL,                   NULL },
		{ "windows",               	7,          false,      _ICODE_WINDOWS,							false,              NULL,                   NULL },
		{ "window",                	6,          false,      _ICODE_WINDOW,							false,              NULL,                   NULL },
		{ "with",                  	4,          false,      _ICODE_WITH,							false,              NULL,                   NULL },
		{ "zap",                   	3,          false,      _ICODE_ZAP,								false,              NULL,                   NULL },

		{ "_vjr",					4,			false,		_ICODE_VJR,								false,				NULL,					NULL },
		{ "_jdebi",					6,			false,		_ICODE_JDEBI,							false,				NULL,					NULL },
		{ "_cmd",					4,			false,		_ICODE_CMD,								false,				NULL,					NULL },
		{ "protected",				9,			false,		_ICODE_PROTECTED,						false,				NULL,					NULL },
		{ "main",					4,			false,		_ICODE_MAIN,							false,				NULL,					NULL },
		{ "loadlastfromvjruserdbf", 22,			false,		_ICODE_LOAD_LAST_FROM_VJR_USER_DBF,		false,				NULL,					NULL },
		{ "flags",					5,			false,		_ICODE_FLAGS,							false,				NULL,					NULL },
		{ "metaicase",				9,			false,		_ICODE_METAICASE,						false,				NULL,					NULL },
		{ "mefaicase",				9,			false,		_ICODE_MEFAICASE,						false,				NULL,					NULL },
		{ "meraicase",				9,			false,		_ICODE_MERAICASE,						false,				NULL,					NULL },
		{ "memaicase",				9,			false,		_ICODE_MEMAICASE,						false,				NULL,					NULL },
		{ "meta",					4,			false,		_ICODE_META,							false,				NULL,					NULL },
		{ "mefa",					4,			false,		_ICODE_MEFA,							false,				NULL,					NULL },
		{ "mera",					4,			false,		_ICODE_MERA,							false,				NULL,					NULL },
		{ "mema",					4,			false,		_ICODE_MEMA,							false,				NULL,					NULL },
		{ "flowto",					6,			false,		_ICODE_FLOWTO,							false,				NULL,					NULL },
		{ "flowout",				7,			false,		_ICODE_FLOWOUT,							false,				NULL,					NULL },
		{ "flow",					4,			false,		_ICODE_FLOW,							false,				NULL,					NULL },
		{ "subflow",				7,			false,		_ICODE_SUBFLOW,							false,				NULL,					NULL },
		{ "rgba",					4,			false,		_ICODE_RGBA,							false,				NULL,					NULL },
		{ "lobject",				7,			false,		_ICODE_LOBJECT,							true,				NULL,					NULL },
		{ "params",					7,			false,		_ICODE_PARAMS,							true,				NULL,					NULL },
		{ "returns",				7,			false,		_ICODE_RETURNS,							true,				NULL,					NULL },
		{ "as",						2,			false,		_ICODE_AS,								false,				NULL,					NULL },
		{ "character",				9,			false,		_ICODE_CHARACTER,						false,				NULL,					NULL },
		{ "integer",				7,			false,		_ICODE_INTEGER,							false,				NULL,					NULL },
		{ "float",					5,			false,		_ICODE_FLOAT,							false,				NULL,					NULL },
		{ "double",					6,			false,		_ICODE_DOUBLE,							false,				NULL,					NULL },
		{ "logical",				7,			false,		_ICODE_LOGICAL,							false,				NULL,					NULL },
//		{ "date",					4,			false,		_ICODE_DATE,							false,				NULL,					NULL },
//		{ "datetime",				8,			false,		_ICODE_DATETIME,						false,				NULL,					NULL },
//		{ "currency",				8,			false,		_ICODE_CURRENCY,						false,				NULL,					NULL },
		{ "s32",					3,			false,		_ICODE_S32,								false,				NULL,					NULL },
		{ "s64",					3,			false,		_ICODE_S64,								false,				NULL,					NULL },
		{ "u32",					3,			false,		_ICODE_U32,								false,				NULL,					NULL },
		{ "u64",					3,			false,		_ICODE_U64,								false,				NULL,					NULL },
		{ "f32",					3,			false,		_ICODE_F32,								false,				NULL,					NULL },
		{ "f64",					3,			false,		_ICODE_F64,								false,				NULL,					NULL },
		{ "bi",						2,			false,		_ICODE_BI,								false,				NULL,					NULL },
		{ "bfp",					3,			false,		_ICODE_BFP,								false,				NULL,					NULL },
		{ "s16",					3,			false,		_ICODE_S16,								false,				NULL,					NULL },
		{ "s8",						2,			false,		_ICODE_S8,								false,				NULL,					NULL },
		{ "u16",					3,			false,		_ICODE_U16,								false,				NULL,					NULL },
		{ "u8",						2,			false,		_ICODE_U8,								false,				NULL,					NULL },

		{ 0,						0,			0,			0,										0,					0,						0 }
	};









//////////
//
// Compiles a VXB-- source code block.  If tlEditAndContinue is true, then only those
// lines which have differing line->compilerInfo->sourceCode and line->sourceCode are
// compiled.  If the current debug environment is operating on this line, the debugger
// will need to take special note about the before and after sub-instructions to
// to determine if the current location can be maintained, or if the line needs to
// start over.
//
//////
	u32 compile_Vxbmm(SEditChainManager* codeBlock, bool tlEditAndContinue)
	{
		u32				lnCompiledLines;
		bool			llProcessThisLine;
		SEditChain*		line;


		// Make sure our environment is sane
		lnCompiledLines = 0;
		if (codeBlock && codeBlock->ecFirst)
		{
			line = codeBlock->ecFirst;
			while (line)
			{
				// Is there anything to parse on this line?
				if (line->sourceCode && line->sourceCodePopulated > 0)
				{
					//////////
					// Breakout this line
					//////
						if (tlEditAndContinue)
						{
							// We only process this line if its contents have changed
							if (!line->compilerInfo || !line->compilerInfo->sourceCode)
							{
								// This line has not yet been compiled.
								// This line needs to be compiled.
								llProcessThisLine = true;

							} else if (line->sourceCode->length != line->compilerInfo->sourceCode->length) {
								// The lines are no longer the same length.  Something has changed.
								// This line needs to be compiled.
								llProcessThisLine = true;

							} else if (iDatumCompare(line->sourceCode, line->compilerInfo->sourceCode) != 0) {
								// The source code contents have changed.
								// This line needs to be compiled.
								llProcessThisLine = true;

							} else {
								// The lines are identical.  Does not need re-compiled.
								llProcessThisLine = false;
							}

						} else {
							llProcessThisLine = true;
						}


					//////////
					// Should we process this line?
					//////
						while (llProcessThisLine)
						{
							// Convert raw source code to known character sequences
							iTranslateSourceLineToSComps(&cgcKeywordOperators[0], line);

							// If it's a comment, we don't need to process it
							if (line->compilerInfo->firstComp->iCode == _ICODE_COMMENT || line->compilerInfo->firstComp->iCode == _ICODE_LINE_COMMENT)
								break;

							// Fixup natural groupings
							iTranslateSCompsToNaturalGroupings(line);

							// Convert character sequences to known keywords
							iTranslateSCompsToOthers(&cgcKeywordKeywords1[0], line);

							// Translate into operations
							iiTranslateSOpsToSubInstr(line, line->compilerInfo->subInstr);

							// All done
							break;
						}
				}


				//////////
				// Move to the next line
				//////
					line = line->next;
			}
		}

		// Indicate our result
		return(lnCompiledLines);
	}




//////////
//
// Break things out vertically to determine operation order.
//
// Example:  k = 2 + 4
//		Converts to:
//			00:   =
//			01: k     +
//			02:     2   4
//
//		Order of operations:
//			+
//			=
//
//		For +:  Load 2 as left, 4 as right, add, and create t0, resulting in:
//			00:   =
//			01: k   t0
//
//		For =:  Load k as left, 4 as right, and store right to left.
//
/////
	void iiTranslateSOpsToSubInstr(SEditChain* line, SSubInstr** siRoot)
	{
		SComp*		comp;
		SComp*		compLast;
		SComp*		compFirstEqual;
//		SSubInstr*	si;
		SSubInstr**	siPrev;


		// Iterate through every component building the operations as we go
		comp			= line->compilerInfo->firstComp;
		compLast		= comp;
		compFirstEqual	= NULL;
		siPrev			= siRoot;
		while (comp)
		{
			//////////
			// If it's an operand we're looking for, then we process it
			//////
				switch (comp->iCode)
				{
					// (
					case _ICODE_PARENTHESIS_LEFT:
						break;

					// )
					case _ICODE_PARENTHESIS_RIGHT:
						break;

					// [
					case _ICODE_BRACKET_LEFT:
						break;

					// ]
					case _ICODE_BRACKET_RIGHT:
						break;

					// {
					case _ICODE_BRACE_LEFT:
						break;

					// }
					case _ICODE_BRACE_RIGHT:
						break;

					// <<
					case _ICODE_SHIFT_LEFT:
						break;

					// >>
					case _ICODE_SHIFT_RIGHT:
						break;

					// ^ or **
					case _ICODE_EXPONENT:
						break;

					// ++
					case _ICODE_PLUS_PLUS:
						break;

					// --
					case _ICODE_MINUS_MINUS:
						break;

					// *
					case _ICODE_ASTERISK:
						break;

					// /
					case _ICODE_SLASH:
						break;

					// %
					case _ICODE_PERCENT_SIGN:
						break;

					// +
					case _ICODE_PLUS:
						break;

					// -
					case _ICODE_HYPHEN:
						break;

					// $
					case _ICODE_FOUND_IN:
						break;

					// !$
					case _ICODE_NOT_FOUND_IN:
						break;

					// NOT or !
					case _ICODE_NOT:
					case _ICODE_EXCLAMATION_MARK:
						break;

					// AND
					case _ICODE_AND:
						break;

					// OR
					case _ICODE_OR:
						break;

					// <<=
					case _ICODE_SHIFT_LEFT_ASSIGNMENT:
						break;

					// >>=
					case _ICODE_SHIFT_RIGHT_ASSIGNMENT:
						break;

					// =
					case _ICODE_EQUAL_SIGN:
						break;

					// <
					case _ICODE_LESS_THAN:
						break;

					// >
					case _ICODE_GREATER_THAN:
						break;

					// <>, #, !=
					case _ICODE_NOT_EQUAL:
					case _ICODE_POUND_SIGN:
						break;

					// <= or =<
					case _ICODE_LESS_THAN_OR_EQUAL_TO:
						break;

					// >= or =>
					case _ICODE_GREATER_THAN_OR_EQUAL_TO:
						break;

					// ==
					case _ICODE_EXACTLY_EQUAL_TO:
						break;

					// FLAGS
					case _ICODE_FLAGS:
						break;
				}


			//////////
			// Move to next component
			//////
				compLast	= comp;
				comp		= (SComp*)comp->ll.next;
		}
	}




//////////
//
// Called to search the SAsciiCompSearcher format list of text item keywords.
//
// Note:  If the length column of the SAsciiCompSearcher entry is negative, it is a case-sensitive search.
//
// Returns:
//		The first component created (if any)
//
//////
	SComp* iTranslateSourceLineToSComps(SAsciiCompSearcher* tsComps, SEditChain* line)
	{
		s32						lnI, lnMaxLength, lnStart, lnLength, lnLacsLength;
		bool					llSigned, llResult;
		SComp*					compFirst;
		SComp*					compLast;
		SComp*					comp;
		s8*						lcData;
		SAsciiCompSearcher*		lacs;
		SCompCallback			lccb;


		// Make sure the environment's sane
		compFirst = NULL;
		if (tsComps && line)
		{
			// Scan starting at the beginning of the line
			lcData = line->sourceCode->data;

			// Iterate through every byte identifying every component we can
			compLast	= NULL;
			lnMaxLength	= line->sourceCodePopulated;
			for (lnI = 0; lnI < lnMaxLength; )
			{
				// Search through the tsComps list one by one
				for (	lacs = tsComps;
						lacs->length != 0;
						lacs++)
				{
					// Find out our signed status and get normalized length
					llSigned		= (lacs->length < 0);
					lnLacsLength	= abs(lacs->length);

					// Process through this entry
					if ((!lacs->firstOnLine || lnI == 0) && lnLacsLength <= lnMaxLength - lnI)
					{
						// There is enough room for this component to be examined
						// See if it matches
						if (iTranslateToSCompsTest((s8*)lacs->keyword, lcData + lnI, lacs->length) == 0)
						{
							// It matches
							// Is there a secondary validation?
							if (lacs->_validate)
							{
								// Yes, make sure it validates there as well
								lccb.text					= lcData + lnI;
								lccb.length					= lacs->length;
								lccb.iCode					= lacs->iCode;
								lccb._insertCompByComp		= NULL;
								lccb._insertCompByParams	= NULL;
								lccb._deleteComps			= NULL;
								lccb._cloneComps			= NULL;
								lccb._mergeComps			= NULL;

								// Perform the validation
								llResult = lacs->validate(&lccb);

							} else {
								// If there is no extra validation, we just pass through
								llResult = true;
							}
							
							// Are we still good?
							if (llResult)
							{
								// mark its current condition
								lnStart		= lnI;
								lnLength	= lnLacsLength;
								// See if it's allowed to repeat
								if (lacs->repeats)
								{
									while (	lnStart + lnLength + lnLacsLength <= lnMaxLength
											&& iTranslateToSCompsTest((s8*)lacs->keyword, lcData + lnStart + lnLength, lacs->length) == 0)
									{
										// We found another repeated entry
										lnLength += lnLacsLength;
									}
									// When we get here, every repeated entry has been found (if any)
								}
								// When we get here, we have the starting point and the full length (including any repeats)


								//////////
								// Allocate this entry
								///////
									comp = (SComp*)iLl_appendNode((SLL**)&line->compilerInfo->firstComp, (SLL*)compLast, NULL, (SLL*)compLast, iGetNextUid(), sizeof(SComp));


								//////////
								// Populate the component with specified information
								//////
									//
									//////
										if (comp)
										{
											// Update the back links
											if (compLast)	compLast->ll.next = (SLL*)comp;			// Previous one points to this one
											comp->ll.prev	= (SLL*)compLast;						// This one points back to previous one

											// Update the component's information
											comp->line		= line;
											comp->start		= lnStart;
											comp->length	= lnLength;
											comp->iCode		= lacs->iCode;

											// Update our first component (if it's not updated already)
											if (!compFirst)	compFirst = comp;

											// All done
											compLast = comp;
										}
									//////
									//
								//////
								// END
								//////////


								//////////
								// Move beyond this entry, and continue on search again afterward
								//////
									lnI += lnLength;
									break;		// leaves lnJ loop, continues with lnI loop
							}
						}
						//else it doesn't match, this isn't a good find
					}
				}
				// When we get here, we've processed through everything here
				if (lacs->length == 0)
					lnI++;			// We didn't find anything at that character, continue on to the next
			}
			// When we get here, lnI has been updated to its new location,
			// and any indicated components have been added
		}
		// Return the count
		return(compFirst);
	}




//////////
//
// Called to search the already parsed SAsciiCompSearcher list of components, looking for
// combinations which relate to other component types.  The primary translations here are
// alpha/alphanumeric/numeric forms to other forms.
//
//////
	bool iTranslateSCompsToOthers(SAsciiCompSearcher* tacs, SEditChain* line)
	{
		bool			llResult;
		s32				lnTacsLength;
		SComp*			comp;
		SCompCallback	lccb;


		// Make sure the environment is sane
		llResult = false;
		if (tacs && line)
		{
			// Grab our pointers into recognizable thingamajigs
			comp = line->compilerInfo->firstComp;

			// Iterate through this item to see if any match
			for (/* tacs is initialize above */; tacs->length != 0; tacs++)
			{
				// Grab the normalized length
				lnTacsLength = abs(tacs->length);

				// We only test if they're the same length
				if (lnTacsLength == comp->length || (tacs->repeats && lnTacsLength <= comp->length))
				{
					// We only test if this item is not the first item on line, or if must be the first
					// item on the line, then this component must be the first component on the line.  Simple, yes? :-)
					if (!tacs->firstOnLine || comp->start == 0)
					{
						// Physically conduct the exact comparison
						if (iTranslateSCompsToOthers_test((s8*)tacs->keyword, comp->line->sourceCode->data + comp->start, tacs->length) == 0)
						{
							// This is a match
							// Is there a secondary test?
							if (tacs->_validate)
							{
								// Yes, make sure it validates there as well
								lccb.comp					= comp;
								lccb.length					= 0;
								lccb.iCode					= tacs->iCode;
								// Setup the functions the custom handler would require
								lccb._insertCompByComp		= (u64)&iiTranslateSCompsToOthersCallback__insertCompByCompCallback;
								lccb._insertCompByParams	= (u64)&iiTranslateSCompsToOthersCallback__insertCompByParamsCallback;
								lccb._deleteComps			= (u64)&iiTranslateSCompsToOthersCallback__deleteCompsCallback;
								lccb._cloneComps			= (u64)&iiTranslateSCompsToOthersCallback__cloneCompsCallback;
								lccb._mergeComps			= (u64)&iiTranslateSCompsToOthersCallback__mergeCompsCallback;

								// Perform the validation
								llResult = tacs->validate(&lccb);

							} else {
								// No, just let it fall through
								llResult = true;
							}

							if (llResult)
							{
								// Convert it, translate it, whatever you want to call it, just make it be the new code, per the user's request, got it? :-)
								comp->iCode = tacs->iCode;
								// All done with this component
								break;
							}
						}
					}
				}
			}

		}
		// We always simulate a false condition so we'll keep receiving each item
		return(false);
	}




//////////
//
// Search the haystack for the needle, the haystack can be tupels, as in "_az" meaning
// (is it between "a" and "z" inclusive?)  To set this condition, use a length of 1,
// a leading "_" in tcHaystack, and two characters (one of which must NOT be NULL) after.
// Examples:
//		_az		= lower-case a to z inclusive
//		_AZ		= upper-case a to z inclusive
//		_09		= numeric 0 to 9 inclusive
//
// Returns:
//		0		= matches
//		!0		= does not tmach
//
//////
	s32 iTranslateSCompsToOthers_test(s8* tcHaystack, s8* tcNeedle, s32 tnLength)
	{
		u32		lnI;
		bool	llSigned;


		// Make sure our environment is sane
		if (tnLength != 0)
		{
			// See if we're a signed or unsigned compare
			if (tnLength < 0)
			{
				// Case sensitive compare
				tnLength	= -tnLength;
				llSigned	= true;

			} else {
				// Case insensitive compare
				llSigned = false;
			}

			// See if we're looking for a tuple, or a regular compare
			if (tcHaystack[0] == '_' && tnLength == 1)
			{
				// It's an explicit match of a range (this is ALWAYS subject to case as it is an explicit range)
				for (lnI = 1; tcHaystack[lnI] != 0 || tcHaystack[lnI + 1] != 0; lnI += 2)
				{
					//		within the range low			.........			up to the range high
					if (tcNeedle[0] >= tcHaystack[lnI]			&&		tcNeedle[0] <= tcHaystack[lnI + 1])
						return(0);		// It's a match, needle is in the range
				}
				// Not a match, will fall through to below

			} else {
				// Just a regular compare
				if (llSigned)	return(  memcmp(tcHaystack, tcNeedle, tnLength));
				else			return(_memicmp(tcHaystack, tcNeedle, tnLength));
			}
		}
		// If we get here, no match
		return(-1);
	}




//////////
//
// Search for the indicated record in the chain by using a user-defined callback on the pointer.
// Callback function should return true when found, false to continue sending other items back.
//
// Returns:
//		NULL if error
//		The associated pointer if found
//
//////
	void* vvm_SEChain_searchByCallback(SStartEnd* ptrSE, SStartEndCallback* cb)
	{
		u32 lnI;


		// Make sure the environment is sane
		if (ptrSE)
		{
			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Ask the caller if this is it
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				{
					// Store the pointer for the caller
					cb->ptr = ptrSE->master[lnI]->ptr;

					// Perform the call
					if (cb->funcBool(cb))
						return(ptrSE->master[lnI]->ptr);	// We've found our man
				}
			}
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Searches the haystack for the indicated needle, and reports the position if found
//
// Returns:
//		true	- found, tnPosition is updated
//		false	- not found, tnPosition unchanged
//
//////
	bool iFindFirstOccurrenceOfAsciiCharacter(s8* tcHaystack, u32 tnHaystackLength, s8 tcNeedle, u32* tnPosition)
	{
		u32		lnI;
		bool	llFound;


		// Make sure our environment is sane
		llFound = false;
		if (tcHaystack && tnHaystackLength != 0)
		{
			// Repeat for the length of the string
			for (lnI = 0; lnI < tnHaystackLength; lnI++)
			{
				// See if this is the character we're after
				if (tcHaystack[lnI] == tcNeedle)
				{
					// We found it
					llFound = true;

					// Update caller's pointer if need be
					if (tnPosition)
						*tnPosition = lnI;

					// All done
					break;
				}
			}
			// When we get here, either found or not
		}
		// Indicate our found condition
		return(llFound);
	}




//////////
//
// Searches forward to find the indicated component by the indicated type.
//
// Returns:
//		The matching component
//		If NULL, the compLastScanned indicates the last component that was searched where it wasn't found
//
//////
	SComp* iFindNextSCompBy_iCode(SComp* comp, u32 tniCode, SComp** compLastScanned)
	{
		// Initially indicate failure
		if (compLastScanned)
			*compLastScanned = comp;

		// Continue while the environment is sane
		while (comp)
		{
			// Store the component we're scanning
			if (compLastScanned)
				*compLastScanned = comp;

			// See if this is it
			if (comp->iCode == tniCode)
				break;		// It is, we're done

			// Move to the next component
			comp = (SComp*)comp->ll.next;
		}
		// When we get here, we either found it or not
		// Store our results
		return(comp);
	}




//////////
//
// Searches for the next non-whitespace component, including itself
//
//////
	SComp* iSkipPastSComp_iCode(SComp* comp, u32 tniCode)
	{
		while (comp && comp->iCode == tniCode)
		{
			// Move to next component
			comp = (SComp*)comp->ll.next;
		}
		// When we get here, we're sitting on either no valid component, or the one which does not match the specified type
		return(comp);
	}




//////////
//
// Called to combine two components which are touching into one.
//
// Source:		define user32		something here
// Example:		[define][whitespace][user][32][whitespace][something][here]
// Search:		[alpha][numeric], convert to [alphanumeric]
// After:		[define][whitespace][user32][whitespace][something][here]
//
//////
	u32 iCombine2SComps(SEditChain* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeCombined)
	{
		u32		lnCount;
		SComp*	compNext;
		SComp*	comp;
		SComp*	comp1;
		SComp*	comp2;


		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp = line->compilerInfo->firstComp;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = (SComp*)comp->ll.next;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Grab the one after that
				comp1 = comp;
				comp2 = (SComp*)comp1->ll.next;
				if (!comp2)
					return(lnCount);	// We're done

				// When we get here, we have needle-1 and needle-2 candidates.
				// Are they touching?
				if (comp1->start + comp1->length == comp2->start)
				{
					// Uh ... yes.  Can we get a chaperon over here, please?  Thank you!
					// Are they our requested?
					if (comp1->iCode == tniCodeNeedle1 && comp2->iCode == tniCodeNeedle2)
					{
						// YES!  This is the moment we've been waiting for. THIS is why we showed up for work today. THIS is why we came!
						// Gentlemen, we have a job to do.  Now, let's get to it!
						++lnCount;


						//////////
						// Combine these into one
						//////
							// Increase comp1's length, then move comp2 from line->comps to line->compsCombined
							comp1->length	+= comp2->length;
							comp1->iCode	= tniCodeCombined;
							iLl_deleteNode((SLL*)comp2);


						//////////
						// Point to the new next thing, which is now the thing after what previously had been comp2, but is now simply comp->ll.next (which could now be nothing)
						//////
							compNext = (SComp*)comp->ll.next;
					}
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to combine three components which are touching into one.
//
// Source:		saddf32		a,20.50
// Example:		[saddf32][whitespace][a][comma][20][period][50]
// Search:		[numeric][period][numeric], convert to [numeric]
// After:		[sadf32][whitespace][a][comma][20.50]
//
//////
	u32 iCombine3SComps(SEditChain* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeNeedle3, u32 tniCodeCombined)
	{
		u32		lnCount;
		SComp*	compNext;
		SComp*	comp;
		SComp*	comp1;
		SComp*	comp2;
		SComp*	comp3;


// UNTESTED CODE:  breakpoint and examine
		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp = line->compilerInfo->firstComp;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = (SComp*)comp->ll.next;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Grab the one after that
				comp1 = compNext;
				comp2 = (SComp*)comp1->ll.next;
				if (!comp2)
					return(lnCount);	// We're done

				// Grab the one after that
				comp3 = (SComp*)comp2->ll.next;
				if (!comp3)
					return(lnCount);	// We're done

				// When we get here, we have needle-1, needle-2, and needle-3 candidates.
				// Are they touching?
				if (comp1->start + comp1->length == comp2->start && comp2->start + comp2->length == comp3->start)
				{
					// Are they our requested?
					if (comp1->iCode == tniCodeNeedle1 && comp2->iCode == tniCodeNeedle2 && comp3->iCode == tniCodeNeedle3)
					{
						// It's a match
						lnCount += 2;

						//////////
						// Combine these into one
						//////
							// Increase comp1's length, then move comp2 from line->comps to line->compsCombined
							comp1->length	+= comp2->length + comp3->length;
							comp1->iCode	= tniCodeCombined;
							iLl_deleteNode((SLL*)comp2);
							iLl_deleteNode((SLL*)comp3);


						//////////
						// Point to the new next thing, which is now the thing after what previously had been comp2, but is now simply comp->ll.next (which could now be nothing)
						//////
							compNext = (SComp*)comp->ll.next;
					}
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to combine everything between two components
//
// Source:		u8 name[] = "foo"
// Example:		[u8][whitespace][name][left bracket][right bracket][whitespace][equal][whitespace][double quote][foo][double quote]
// Search:		[double quote], replace with [double quoted text]
// After:		[u8][whitespace][name][left bracket][right bracket][whitespace][equal][whitespace][double quote text]
//
//////
	u32 iCombineAllBetweenSComps(SEditChain* line, u32 tniCodeNeedle, u32 tniCodeCombined)
	{
		u32		lnCount;
		SComp*	compNext;
		SComp*	comp;
		SComp*	compSearcher;


// UNTESTED CODE:  breakpoint and examine
		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp = line->compilerInfo->firstComp;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = (SComp*)comp->ll.next;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Is this our intended?
				if (comp->iCode == tniCodeNeedle)
				{
					// Search forward to see if there is a matching entry
					compSearcher = compNext;
					while (compSearcher)
					{
						if (compSearcher->iCode == tniCodeNeedle)
						{
							// This is the match, combine everything between
							comp->length	= (compSearcher->start + compSearcher->length) - comp->start;
							comp->iCode		= tniCodeCombined;

							// Iterate and merge in
							while (compNext)
							{
								// Increase our count
								++lnCount;

								// Delete this one (as it was technically merged above with the comp->length = line)
								iLl_deleteNode((SLL*)compNext);

								// See if we're done
								if (compNext == compSearcher)
									break;		// This was the last one, we're done

								// Move to the next component (which is the comp->ll.next component again, because we just migrated the previous compNext
								compNext = (SComp*)comp->ll.next;
							}
							// When we get here, everything's migrated

							// Grab the new next, which is the one after the matched entry
							compNext = (SComp*)comp->ll.next;

							// Continue looking for more combinations on this line
							break;
						}

						// Move to the next component
						compSearcher = (SComp*)compSearcher->ll.next;
					}
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to combine everything after the indicated component
//
// Source:		u8* name		// user name
// Example:		[u8][asterisk][whitespace][name][whitespace][comment][whitespace][user][whitespace][name]
// Search:		[comment]
// After:		[u8][asterisk][whitespace][name][whitespace][comment]
//
//////
	u32 iCombineAllAfterSComp(SEditChain* line, u32 tniCodeNeedle)
	{
		u32		lnCount;
		SComp*	compNext;
		SComp*	comp;


// UNTESTED CODE:  breakpoint and examine
		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp = (SComp*)line->compilerInfo->firstComp;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = (SComp*)comp->ll.next;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Is this our intended?
				if (comp->iCode == tniCodeNeedle)
				{
					//////////
					// Combine from here on out into one
					//////
						// Increase the original component to the line's whole length
						comp->length = line->sourceCodePopulated - comp->start;
						while (compNext)
						{
							// Indicate the number combined
							++lnCount;

							// Move this one along
							iLl_deleteNode((SLL*)compNext);

							// Move to next component (which is now again the comp->ll.next entry, because we've just migrated the prior compNext entry to compsCombined)
							compNext = (SComp*)comp->ll.next;
						}
						// When we get here, we're done
						break;
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to remove extraneous whitespaces
//
// Source:		u8* name		// user name
// Example:		[u8][asterisk][whitespace][name][whitespace][comment][whitespace][user][whitespace][name]
// Search:		[comment]
// After:		[u8][asterisk][whitespace][name][whitespace][comment]
//
//////
	u32 iRemoveExtraneousWhitespaceSComps(SEditChain* line, u32 tniCodeWhitespace)
	{
		return(0);
	}




//////////
//
// Fixes up common things found in VXB-- source code.
//
//////
	void iTranslateSCompsToNaturalGroupings(SEditChain* line)
	{
		//////////
		// Combine standard things
		//////
			// _0
			iCombine2SComps			(line,	_ICODE_UNDERSCORE,		_ICODE_NUMERIC,			_ICODE_ALPHANUMERIC);
			// a_
			iCombine2SComps			(line,	_ICODE_ALPHA,			_ICODE_UNDERSCORE,		_ICODE_ALPHA);
			// _a
			iCombine2SComps			(line,	_ICODE_UNDERSCORE,		_ICODE_ALPHA,			_ICODE_ALPHA);
			// a0
			iCombine2SComps			(line,	_ICODE_ALPHA,			_ICODE_NUMERIC,			_ICODE_ALPHANUMERIC);
			// a9_
			iCombine2SComps			(line,	_ICODE_ALPHANUMERIC,	_ICODE_UNDERSCORE,		_ICODE_ALPHANUMERIC);
			// 0.0
			iCombine3SComps			(line,	_ICODE_NUMERIC,			_ICODE_DOT,				_ICODE_NUMERIC,			_ICODE_NUMERIC);


		//////////
		// Fixup quotes, comments
		//////
			iCombineAllBetweenSComps(line, _ICODE_SINGLE_QUOTE,		_ICODE_SINGLE_QUOTED_TEXT);
			iCombineAllBetweenSComps(line, _ICODE_DOUBLE_QUOTE,		_ICODE_DOUBLE_QUOTED_TEXT);
			iCombineAllAfterSComp	(line, _ICODE_LINE_COMMENT);
	}




//////////
//
// Scans from the indicated location forward until finding CR/LF or any combination thereof,
// nothing whitespaces, content, and total line length (including cr/lf combinations at the end)
//
//////
	u32 iBreakoutAsciiTextDataIntoLines_ScanLine(s8* tcData, u32 tnMaxLength, u32* tnLength, u32* tnWhitespaces)
	{
		u32 lnLength, lnWhitespaces, lnCRLF_Length;


		// Make sure we have something to do
		lnLength		= 0;
		lnWhitespaces	= 0;
		lnCRLF_Length	= 0;
		if (tcData && tnMaxLength > 0)
		{
			// Skip past any whitespaces
			lnWhitespaces = iSkipWhitespaces(tcData, tnMaxLength);
			if (tnWhitespaces)
				*tnWhitespaces = lnWhitespaces;


			// Skip to the ending carriage return / line feed
			lnLength = iSkipToCarriageReturnLineFeed(tcData + lnWhitespaces, tnMaxLength - lnWhitespaces, &lnCRLF_Length);
			if (tnLength)
				*tnLength = lnLength;
		}
		// Return the total length
		return(lnWhitespaces + lnLength + lnCRLF_Length);
	}




//////////
//
// Called to translate the indicated keywords into their corresponding operation.
//
//////
	void iiTranslateSCompsToSubInstr(SEditChain* line)
	{
		SSubInstr	si;
		SComp*		saveComps;


		//////////
		// Copy the comps
		//////
			saveComps = line->compilerInfo->firstComp;


		//////////
		// Find the inmost expression
		//////
			while (iiTranslateSCompsToSubInstr_findInmostExpression(&si, line))
			{
				// Was it a valid operation?
				if (si.sub_instr >= 0)
				{
					// We found the operation
					// Did we find appropriate components?
// TODO:  Working here

				} else {
					// The sub_instruction is not valid, which means were done
					break;
				}

				// When we get here, try to find another
			}


		//////////
		// There are no more "inner" expressions.
		// Now we parse out by keyword.
		//////
			if (iiTranslateSCompsToSubInstr_isEqualAssignment(line))
			{
				// It's something like x = y, but it could be x,y,z = a(b,c)

			} else {
				// Based upon keyword, process it
			}
	}




//////////
//
// Called to search for the thing that needs to be done next.  Order of searching:
//
// First level:
//		(1)		exponents
//		(2)		multiply, divide
//		(3)		add, subtract
//
// Second level:
//		(4)		parenthetical expressions
//		(5)		bracket expressions (arrays)
//		(6)		
//
//////
	SComp* iiTranslateSCompsToSubInstr_findInmostExpression(SSubInstr* si, SEditChain* line)
	{
		bool	llFound;
		SComp*	comp;


		//////////
		// Initially indicate that we did not find an inmost expression
		//////
			memset(si, 0, sizeof(SSubInstr));
			si->sub_instr	= -1;			// Indicate failure initially (until something is found)
			si->sub_level	= -1;			// Unused during parsing


		//////////
		// Search for exponents
		//////
			comp	= line->compilerInfo->firstComp;
			llFound	= true;
			while (comp)
			{
				//////////
				// Is it an exponent?
				//////
					if (comp->iCode == _ICODE_EXPONENT)
					{
						// Exponent
						si->sub_instr	= _SUB_INSTR_EXPONENT;
						llFound			= true;

					} else if (comp->iCode == _ICODE_SLASH) {
						// Division
						si->sub_instr	= _SUB_INSTR_DIVIDE;
						llFound			= true;

					} else if (comp->iCode == _ICODE_ASTERISK) {
						// Multiplication
						si->sub_instr	= _SUB_INSTR_MULTIPLY;
						llFound			= true;

					} else if (comp->iCode == _ICODE_PLUS) {
						// Addition
						si->sub_instr	= _SUB_INSTR_ADD;
						llFound			= true;

					} else if (comp->iCode == _ICODE_HYPHEN) {
						// Subtraction
						si->sub_instr	= _SUB_INSTR_SUBTRACT;
						llFound			= true;
					}


				//////////
				// Was it found?
				//////
					if (llFound)
					{
						// Search for something to the left of the exponent, like the "someTable.someField" in "k = someTable.someField ^ xyz"
						// Search for something to the right of the exponent, like the "thisForm.someObject.someProperty" in "k = xyz ^ thisForm.someObject.someProperty"
// TODO:  Refactor for left and right nodes
						iiTranslateSCompsToSubInstr_findStartOfComponent	((SComp*)comp->ll.prev, si->op);
						iiTranslateSCompsToSubInstr_findFullComponent		((SComp*)comp->ll.next, si->op);

						// When we get here, si has been populated if there are operations there.
						// If they are null, then it is a syntax error
						break;
					}


				// Move to next component
				comp = (SComp*)comp->ll.next;
			}

		// Indicate our result
		return(comp);
	}




//////////
//
// We scan backwards until we get to any component other than a period or exclamation point.
//
//////
	void iiTranslateSCompsToSubInstr_findStartOfComponent(SComp* compRoot, SOp* op)
	{
		SComp*	comp;
		SComp*	compPrev;


		//////////
		// Iterate through
		//////
			comp		= compRoot;
			op->count	= 0;
			while (comp && comp->ll.prev && iiCharactersBetweenSComps((SComp*)comp->ll.prev, comp) == 0)
			{
				//////////
				// Previous component
				//////
					compPrev = (SComp*)comp->ll.prev;


				//////////
				// Is the component before this one still immediately adjacent?
				//////
					if (comp->iCode != _ICODE_DOT && comp->iCode != _ICODE_EXCLAMATION_MARK)
						break;		// We've reached the end, the previous component is not a continuation


				//////////
				// If we get here, we're continuing through this component at least
				//////
					comp = compPrev;
					++op->count;
			}


		//////////
		// If we get here, we will return the starting point
		//////
			op->comp = comp;
	}




//////////
//
// We scan forward so long as we are hitting a period or exclamation point which is
// immediately adjacent.
//
//////
	void iiTranslateSCompsToSubInstr_findFullComponent(SComp* compRoot, SOp* op)
	{
		SComp*	comp;
		SComp*	compNext;


		//////////
		// Iterate through
		//////
			comp		= compRoot;
			op->count	= 0;
			while (comp && comp->ll.next && iiCharactersBetweenSComps(comp, (SComp*)comp->ll.next) == 0)
			{
				//////////
				// Next component
				//////
					compNext = (SComp*)comp->ll.next;


				//////////
				// Is the component before this one still immediately adjacent?
				//////
					if (comp->iCode != _ICODE_DOT && comp->iCode != _ICODE_EXCLAMATION_MARK)
						break;	// We've reached the end, the next component is not a continuation


				//////////
				// If we get here, we're continuing through this component at least
				//////
					comp = compNext;
					++op->count;
			}


		//////////
		// At this point comp indicates the last component
		//////
			op->comp = comp;
	}




//////////
//
// Called to see if the instruction is an assignment:
//		x = y
//
//////
	bool iiTranslateSCompsToSubInstr_isEqualAssignment(SEditChain* line)
	{
// TODO:  Write this function :-)
		return(false);
	}




//////////
//
// Returns the number of characters between two components.
//
//////
	s32 iiCharactersBetweenSComps(SComp* compLeft, SComp* compRight)
	{
		// Start of right component and end of left component
		return(compRight->start - (compLeft->start + compLeft->length));
	}




//////////
//
// Scans from the indicated location forward until finding a non-whitespace character
//
//////
	u32 iSkipWhitespaces(s8* tcData, u32 tnMaxLength)
	{
		u32 lnLength;


		// Make sure our environment's sane
		lnLength = 0;		// Initially indicate no whitespaces
		if (tcData && tnMaxLength > 0)
		{
			// While we encounter spaces or tabs, count them
			while (lnLength < tnMaxLength && (tcData[lnLength] == 32 || tcData[lnLength] == 9))
				++lnLength;
			// When we get here, lnLength is the number of whitespaces (if any)
		}
		// Indicate the total length encountered
		return(lnLength);
	}




//////////
//
// Scans from the indicated location forward until finding CR/LF or any combination thereof
//
//////
	u32 iSkipToCarriageReturnLineFeed(s8* tcData, u32 tnMaxLength, u32* tnCRLF_Length)
	{
		u32 lnLength, lnCRLF_Length;


		// Make sure our environment's sane
		lnLength		= 0;		// Initially indicate a line length of 0
		lnCRLF_Length	= 0;		// Same for CR/LF length
		if (tcData && tnMaxLength > 0)
		{
			// While we do not counter a CR or LF, continue
			while (lnLength < tnMaxLength && tcData[lnLength] != 13 && tcData[lnLength] != 10)
				++lnLength;

			// See if we are done
			if (lnLength < tnMaxLength)
			{
				// We did not reach the end of the entire data available to us to search
				// So, when we get here, we're sitting on a CR or LF, which is the end of line
				if (tcData[lnLength] == 13)
				{
					// We're sitting on a carriage return
					// If the next character is a line feed, we count it
					if (tcData[lnLength + 1] == 10)		lnCRLF_Length = 2;		// We have a pair
					else								lnCRLF_Length = 1;		// Just the one

				} else {
					// We know we're sitting on a line feed
					// If the next character is a carriage return, we count it
					if (tcData[lnLength + 1] == 13)		lnCRLF_Length = 2;		// We have a pair
					else								lnCRLF_Length = 1;		// Just the one
				}

			} else {
				// We reached the end
				// We don't do anything here, but just return the length
			}
		}
		// When we get here, return the lengths
		// The CR/LF length
		if (tnCRLF_Length)
			*tnCRLF_Length = lnCRLF_Length;

		// The stuff before length :-)
		return(lnLength);
	}




//////////
//
// Get the next Unique ID
//
//////
	u32 iGetNextUid(void)
	{
		u32 lnValue;

		// Synchronized access
		EnterCriticalSection(&gcsUniqueIdAccess);

		// Get our value and increment
		lnValue = gnNextUniqueId;
		++gnNextUniqueId;

		// All done
		LeaveCriticalSection(&gcsUniqueIdAccess);

		// Return that value
		return(lnValue);
	}



	void* iSEChain_prepend(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(iSEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, true, tlResult));
	}

	void* iSEChain_append(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(iSEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, false, tlResult));
	}

	// Prepends or appends to the Start/end chain
	void* iSEChain_appendOrPrepend (SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult)
	{
		SLL*			ptrCaller;
		SMasterList*	ptrNew;
		SMasterList*	ptrPrev;
		SMasterList**	prev;


// TODO:  untested code, breakpoint and examine
// Note:  This code has been tested, but it is truly essential to operations of the VVM, and needs thoroughly tested many, many, many times. :-)
		// See where we are
		ptrCaller = NULL;
		if (ptrSE)
		{
			if (!ptrSE->root)
			{
				// This is the first item
				ptrPrev	= NULL;
				prev	= &ptrSE->root;

			} else {
				// We're appending
				if (tlPrepend)
				{
					// We go to the beginning
					ptrPrev	= ptrSE->root;
					prev	= &ptrSE->root;

				} else {
					// We are appending to the end
					ptrPrev	= ptrSE->last;
					prev	= (SMasterList**)&ptrSE->last->ll.next;
				}
			}

			// Allocate for our SMasterList pointer
			ptrNew = (SMasterList*)malloc(sizeof(SMasterList));
			if (ptrNew)
			{
				// We have our new pointer, initialize the structure
				memset(ptrNew, 0, sizeof(SMasterList));

				// Create the new caller structure
				ptrCaller = (SLL*)malloc(tnSize);
				if (ptrCaller)
				{
					// Initialize the structure
					memset(ptrCaller, 0, tnSize);

					// Indicate its unique ID
					ptrCaller->uniqueId	= tnUniqueId;

					// Store the memory variable for the caller memory block
					ptrNew->ptr			= ptrCaller;

					// Update the back-link
					*prev				= ptrNew;

					// Update the other part of the back link
					ptrNew->ll.uniqueId	= tnUniqueIdExtra;
					if (tlPrepend)
					{
						// Previous ptrSE->root points backward to ptrNew, which is now the entry pointed to by ptrSE->root
						ptrPrev->ll.prev	= (SLL*)ptrNew;		// Old first entry points backward to new first entry
						ptrNew->ll.next		= (SLL*)ptrPrev;	// New first entry points forward to old first entry
						ptrSE->root			= ptrNew;			// New first entry

					} else {
						// We are appending to the end
						ptrNew->ll.prev		= (SLL*)ptrPrev;	// Previous last entry pointing forward to new last entry
						ptrSE->last			= ptrNew;			// New last entry
					}

					// Store it in the master list (so when VM is suspended, this data gets saved)
					iSEChain_appendMasterList(ptrSE, ptrNew, 0, tnBlockSizeIfNewBlockNeeded);

					// All done!
				}
				// When we get here, ptrCaller is either populated or NULL
			}
		}
		// Indicate our success or failure explicitly if required
		if (tlResult)
			*tlResult = !(ptrCaller == NULL);

		// Return our pointer
		return(ptrCaller);
	}

	// NOTE!  Do not call this function directly!  Call iAppendToStarEndChain() only.
	void iSEChain_appendMasterList(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded)
	{
		// This function should not be called directly.  It is automatically called from
		// iAppendToStarEndChain().  It stores pointers in the master list, pointers
		// which are part of the chain in ptrSE->root..ptrSE->last.
		u32 lnI;


// UNTESTED CODE:  Breakpoint and examine!
		lnI = tnHint;
		while (1)
		{
			// Search for first unused item
			if (ptrSE->master)
			{
				// Check to see if there is an unused slot
				for ( ; lnI < ptrSE->masterCount; lnI++)
				{
					if (!ptrSE->master[lnI])
					{
						// This slot is unused, store it
						ptrSE->master[lnI] = ptrNew;

						// Update it
						ptrNew->used = true;

						// All done
						return;
					}
				}
				// If we get here, there were no unused slots
			}
			// If we get here, no slots are available, add some more

			// Allocate some pointer space
			iSEChain_allocateAdditionalMasterSlots(ptrSE, tnBlockSizeIfNewBlockNeeded);
			// We never break out of this loop because we will always return above from it
		}
	}

	
	bool iSEChain_allocateAdditionalMasterSlots(SStartEnd* ptrSE, u32 tnBlockSize)
	{
		bool			llResult;
		SMasterList**	lml;


		// Indicate failure initially
		llResult = false;

		// Make sure our environment is sane
		if (ptrSE)
		{
			// Make sure we're really doing something
			tnBlockSize = max(tnBlockSize, 1);

			// See where we are
			if (ptrSE->master)
			{
				// Allocate another _COMMON_START_END_BLOCK_SIZE pointers
				lml = (SMasterList**)realloc(ptrSE->master, sizeof(SMasterList*) * (ptrSE->masterCount + tnBlockSize));
				if (lml)
				{
					// We're good, initialize the new section
					ptrSE->master = lml;
					memset(&ptrSE->master[ptrSE->masterCount], 0, sizeof(SMasterList*) * tnBlockSize);
					ptrSE->masterCount += tnBlockSize;
					llResult = true;

				} else {
					// It failed here
// TODO:  Something major needs to happen here.  This is more or less a catastrophic failure.  It could require shutting down the VVM.
_asm int 3;
					ptrSE->masterCount += tnBlockSize;
				}

			} else {
				// Allocate the first N pointers
				ptrSE->master = (SMasterList**)malloc(sizeof(SMasterList*) * tnBlockSize);
				if (ptrSE->master)
				{
					// We're good, initialize the new section
					memset(&ptrSE->master[0], 0, sizeof(SMasterList*) * tnBlockSize);
					ptrSE->masterCount	= tnBlockSize;
					llResult = true;
				}
			}
		}
		// If we get here, failure
		return(llResult);
	}




//////////
//
// Search the haystack for the needle, the haystack can be tupels, as in "_az" meaning
// (is it between "a" and "z" inclusive?)  To set this condition, use a length of 1,
// a leading "_" in tcHaystack, and two characters (one of which must NOT be NULL) after.
// Examples:
//		_az		= lower-case a to z inclusive
//		_AZ		= upper-case a to z inclusive
//		_09		= numeric 0 to 9 inclusive
//
// Returns:
//		0		= matches
//		!0		= does not tmach
//
//////
	s32 iTranslateToSCompsTest(s8* tcHaystack, s8* tcNeedle, s32 tnLength)
	{
		u32		lnI;
		bool	llSigned;


		// Make sure our environment is sane
		if (tnLength != 0)
		{
			// See if we're a signed or unsigned compare
			if (tnLength < 0)
			{
				// Case sensitive compare
				tnLength	= -tnLength;
				llSigned	= true;

			} else {
				// Case insensitive compare
				llSigned = false;
			}

			// See if we're looking for a tuple, or a regular compare
			if (tcHaystack[0] == '_' && tnLength == 1)
			{
				// It's an explicit match of a range (this is ALWAYS subject to case as it is an explicit range)
				for (lnI = 1; tcHaystack[lnI] != 0 || tcHaystack[lnI + 1] != 0; lnI += 2)
				{
					//		within the range low			.........			up to the range high
					if (tcNeedle[0] >= tcHaystack[lnI]			&&		tcNeedle[0] <= tcHaystack[lnI + 1])
						return(0);		// It's a match, needle is in the range
				}
				// Not a match, will fall through to below

			} else {
				// Just a regular compare
				if (llSigned)	return(  memcmp(tcHaystack, tcNeedle, tnLength));
				else			return(_memicmp(tcHaystack, tcNeedle, tnLength));
			}
		}
		// If we get here, no match
		return(-1);
	}




//////////
//
// Callback, used to translate existing components into other components
// Note:  Always returns false, so it will continue being fed every component
//
//////
	bool iioss_translateSCompsToOthersCallback(SStartEndCallback* cb)
	{
		bool					llResult;
		s32						lnLacsLength;
		SComp*				comp;
		SAsciiCompSearcher*		lacs;
		SCompCallback		lccb;


		// Make sure the environment is sane
		if (cb && cb->ptr)
		{
			// Grab our pointers into recognizable thingamajigs
			comp	= (SComp*)cb->ptr;
			lacs	= (SAsciiCompSearcher*)cb->extra;

			// Iterate through this item to see if any match
			for (	/* lacs is initialize above */;
					lacs->length != 0;
					lacs++		)
			{
				// Grab the normalized length
				lnLacsLength = abs(lacs->length);

				// We only test if they're the same length
				if (lnLacsLength == comp->length || (lacs->repeats && lnLacsLength <= comp->length))
				{
					// We only test if this item is not the first item on line, or if must be the first
					// item on the line, then this component must be the first component on the line.  Simple, yes? :-)
					if (!lacs->firstOnLine || comp->start == 0)
					{
						// Physically conduct the exact comparison
						if (iTranslateToSCompsTest((s8*)lacs->keyword, 
														comp->line->sourceCode->data + comp->start, 
														lacs->length) == 0)
						{
							// This is a match
							// Is there a secondary test?
							if (lacs->_validate)
							{
								// Yes, make sure it validates there as well
								lccb.comp					= comp;
								lccb.length					= 0;
								lccb.iCode					= lacs->iCode;
								lccb._insertCompByComp		= (u32)&iiTranslateSCompsToOthersCallback__insertCompByCompCallback;
								lccb._insertCompByParams	= (u32)&iiTranslateSCompsToOthersCallback__insertCompByParamsCallback;
								lccb._deleteComps			= (u32)&iiTranslateSCompsToOthersCallback__deleteCompsCallback;
								lccb._cloneComps			= (u32)&iiTranslateSCompsToOthersCallback__cloneCompsCallback;
								lccb._mergeComps			= (u32)&iiTranslateSCompsToOthersCallback__mergeCompsCallback;

								// Perform the validation
								llResult = lacs->validate(&lccb);

							} else {
								// No, just let it fall through
								llResult = true;
							}
							
							if (llResult)
							{
								// Convert it, translate it, whatever you want to call it, just make it be the new code, per the user's request, got it? :-)
								comp->iCode = lacs->iCode;
								// All done with this component
								break;
							}
						}
					}
				}
			}

		}
		// We always simulate a false condition so we'll keep receiving each item
		return(false);
	}




//////////
//
// Search for the indicated record in the chain by using a user-defined callback on the pointer.
// Callback function should return true when found, false to continue sending other items back.
//
// Returns:
//		NULL if error
//		The associated pointer if found
//
//////
	void* iSEChain_searchByCallback(SStartEnd* ptrSE, SStartEndCallback* cb)
	{
		u32 lnI;


		// Make sure the environment is sane
		if (ptrSE)
		{
			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Ask the caller if this is it
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				{
					// Store the pointer for the caller
					cb->ptr = ptrSE->master[lnI]->ptr;

					// Perform the call
					if (cb->funcBool(cb))
						return(ptrSE->master[lnI]->ptr);	// We've found our man
				}
			}
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Called as a callback from the custom handler callback function, to do some manual insertion.
// Note:  If a rogue component is inserted here, one not already defined in the ref's SOssLine parent,
//        then it will need to be either manually added to the line->comps, or manually tended to.
//
//////
	void iiTranslateSCompsToOthersCallback__insertCompByCompCallback(SComp* compRef, SComp* compNew, bool tlInsertAfter)
	{
// TODO:  untested code, breakpoint and examine
_asm int 3;
		// Make sure our environment is sane
		if (compRef && compNew)
		{
			// Before or after?
			if (tlInsertAfter)
			{
				// Add the new comp after the reference comp
				if (compRef->ll.next)
					compRef->ll.next->prev	= (SLL*)compNew;	// One originally after ref points back to new

				compNew->ll.next	= compRef->ll.next;			// New points forward to the one originally after ref
				compNew->ll.prev	= (SLL*)compRef;			// New points back to ref
				compRef->ll.next	= (SLL*)compNew;			// Ref points forward to new

			} else {
				// Add the new comp before the reference comp
				if (compRef->ll.prev)
					compRef->ll.prev->next	= (SLL*)compNew;	// One originally before ref points forward to new

				compNew->ll.next	= (SLL*)compRef;			// New points forward to ref
				compNew->ll.prev	= compRef->ll.prev;			// New points back to the one originally before ref
				compRef->ll.prev	= (SLL*)compNew;			// Ref points back to new
			}
		}
	}




//////////
//
// Called as a callback from the custom handler callback function, to do some manual insertion.
//
//////
	void iiTranslateSCompsToOthersCallback__insertCompByParamsCallback(SComp* compRef, SEditChain* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter)
	{
		SComp* compNew;


// TODO:  untested code, breakpoint and examine
_asm int 3;
		// Make sure our environment is sane
		if (compRef && line && line->compilerInfo)
		{
			// Allocate a new pointer
			compNew = (SComp*)iLl_appendNode((SLL**)&line->compilerInfo->firstComp, NULL, NULL, NULL, iGetNextUid(), sizeof(SComp));
			if (compNew)
			{
				// Initialize it
				memset(compNew, 0, sizeof(SComp));

				// Populate it
				compNew->line		= line;
				compNew->iCode		= tniCode;
				compNew->start		= tnStart;
				compNew->length		= tnLength;

				// Add the new component as a component
				iiTranslateSCompsToOthersCallback__insertCompByCompCallback(compRef, compNew, tlInsertAfter);
			}
		}
	}




//////////
//
// Called as a callback from the custom handler callback function, to do delete the
// indicated component.
//
//////
	void iiTranslateSCompsToOthersCallback__deleteCompsCallback(SComp* comp, SEditChain* line)
	{
// TODO:  untested code, breakpoint and examine
_asm int 3;
		//////////
		// Disconnect the component from its siblings
		//////
			// Make the one before point forward to one after
			if (comp->ll.prev)
				comp->ll.prev->next = comp->ll.next;

			// Make the one after point back to the one before
			if (comp->ll.next)
				comp->ll.next->prev = comp->ll.prev;


		//////////
		// Delete it from the list of known components.
		// Component go bye bye. :-)
		//////
			if (line)
			{
				// Delete the entry from line->comps
				iLl_deleteNode((SLL*)comp);

			} else {
				// Free the rogue entry
				free(comp);
			}
	}




//////////
//
// Called as a callback from the custom handler callback function, to clone the indicated
// component.  If line is not NULL, the component is automatically added to line->comps;
//
//////
	SComp* iiTranslateSCompsToOthersCallback__cloneCompsCallback(SComp* comp, SEditChain* line)
	{
		SComp* compNew;


// TODO:  untested code, breakpoint and examine
_asm int 3;
		// Make sure our environment is sane
		if (comp)
		{
			// Are we adding to to a line?
			if (line && line->compilerInfo)
			{
				// Add the new component to line->comps
				compNew = (SComp*)iLl_appendNode((SLL**)&line->compilerInfo->firstComp, NULL, NULL, NULL, iGetNextUid(), sizeof(SComp));

			} else {
				// Just create a rogue one
				compNew = (SComp*)malloc(sizeof(SComp));
			}

			// Was it valid?
			if (compNew)
			{
				// Initialize it
				memset(compNew, 0, sizeof(SComp));

				// Populate it
				compNew->line		= line;
				compNew->iCode		= comp->iCode;
				compNew->start		= comp->start;
				compNew->length		= comp->length;

				// All done!
			}
		}

		// Return our new one, no matter if it was a success or not
		return(compNew);
	}




//////////
//
// Called as a callback from the custom handler callback function, to do merge components into
// a new one, and delete the one(s) which were merged.
//
// NOTE:  It's theoretically possible that there could be a gap here, such as a component next to
//        another component where there used to be a whitespace inbetween (or anything else), so
//        the components are no longer right by each other.  The caller will have to manually
//        handle that condition.
//
//////
	SComp* iiTranslateSCompsToOthersCallback__mergeCompsCallback(SComp* comp, SEditChain* line, u32 tnCount, u32 tniCodeNew)
	{
		u32			lnI;
		SComp*	compThis;


// TODO:  untested code, breakpoint and examine
_asm int 3;
		// Make sure our environment is sane
		if (comp)
		{
			// Iterate for each merging
			for (lnI = 1, compThis = (SComp*)comp->ll.next; compThis && lnI < tnCount; lnI++, compThis = (SComp*)comp->ll.next)
			{
				// Absorb compThis's length into comp's "collective"
				comp->length += compThis->length;

				// Delete this component
				iiTranslateSCompsToOthersCallback__deleteCompsCallback(compThis, comp->line);

				// Note:  compThis is always assigned comp->ll.next, because its next component keeps being updated after the delete
			}
			// When we get here, everything's merged
		}
		// Return the original component as a pass through (in case this is used as an intermediate function)
		return(comp);
	}




//////////
//
// Delete the indicated item from the chain
//
//////
	void iSEChain_deleteFrom(SStartEnd* ptrSE, void* ptrCaller, bool tlDeletePointers)
	{
		u32				lnI;
		SMasterList*	ptrDel;
		SMasterList**	master;


		// See where we are
// UNTESTED CODE:  Breakpoint and examine!
		if (ptrSE)
		{
			if (!ptrSE->root)
			{
				// There are no existing items, nothing to do, why are they messing around with our brains? :-)
				return;
			}

			// Iterate through the master list to find the matching record to delete in the chain
			master = ptrSE->master;
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// See if this item matches
				ptrDel = master[lnI];
				if (ptrDel && ptrDel->used && ptrDel->ptr == ptrCaller)
				{
					// Mark it as not being used
					ptrDel->used = false;

					// Remove it from its chain
					if (ptrDel == ptrSE->root)
					{
//////////
// This is the first item
//////
						// We are deleting the first item in the list
						if (ptrDel == ptrSE->last)
						{
							// Which is also the last item in the list
							ptrSE->root = NULL;
							ptrSE->last = NULL;
							// No items exist after this

						} else {
							// It's just the first item in a chain
							ptrSE->root = (SMasterList*)ptrDel->ll.next;
						}


					} else if (ptrDel == ptrSE->last) {
//////////
// This is the last item
//////
						// We are deleting the last item in the list
						ptrSE->last									= (SMasterList*)ptrDel->ll.prev;	// This will never be NULL because we've already checked the first condition
						((SMasterList*)(ptrDel->ll.prev))->ll.next	= NULL;								// Make the one before this point to nothing, because it is now the last item


					} else {
//////////
// This is an entry in the middle somewhere
//////
						// We are deleting an entry in the middle somewhere
						((SMasterList*)(ptrDel->ll.prev))->ll.next	= ptrDel->ll.next;		// Make the one before this point to the one after this
						((SMasterList*)(ptrDel->ll.next))->ll.prev	= ptrDel->ll.prev;		// Make the one after this point to the one before this
					}
					// When we get here, the start/end chain is updated


					// Release our SMasterList pointer
					free(ptrDel);
					master[lnI] = NULL;


					// Release the caller's memory (or not if they want to keep it)
					if (tlDeletePointers)
						free(ptrCaller);		// Delete this pointer
					// All done
				}
			}
		}
		//else not found
	}




//////////
//
// Migrate the existing SMasterList item, and its associated SLL item, from one Start/end chain
// to another, by either pointer or physical position number.
//
//////
	SLL* iSEChain_completelyMigrateSLLByPtr(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr, u32 tnHint, u32 tnBlockSize)
	{
		u32 lnI;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && ptrSESrc->masterCount >= 1)
		{
			for (lnI = 0; lnI < ptrSESrc->masterCount; lnI++)
			{
				// Is this our pointer?
				if (ptrSESrc->master[lnI] && ptrSESrc->master[lnI]->ptr == (void*)ptr)
				{
					// This is our man, migrate it
// TODO:  (enhancement) we want some kind of better hinting algorithm here, such as the end of the list - common block size, for now we'll just pass 0
					return(iSEChain_completelyMigrateSLLByNum(ptrSEDst, ptrSESrc, lnI, 0, tnBlockSize));
				}
			}
			// If we get here, not found
		}
		// Indicate failure
		return(NULL);
	}

	SLL* iSEChain_completelyMigrateSLLByNum(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize)
	{
		SLL*			lllPrev;
		SLL*			lllNext;
		SLL*			lll;
		SMasterList*	lml;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && lnSrcNum < ptrSESrc->masterCount && lnSrcNum <= ptrSESrc->masterCount)
		{
			// Migrate it, and get its SMasterList entry
			lml = iSEChain_migrateByNum(ptrSEDst, ptrSESrc, lnSrcNum, tnHint, tnBlockSize);
			if (lml && lml->ptr)
			{
				// Grab the pointer to the SLL entry
				lll = (SLL*)lml->ptr;
				// Right now, lll points to the SLL* object from ptrSESrc

				// Grab ptrSESrc's preceding, and following objects (if any)
				lllPrev	= lll->prev;
				lllNext = lll->next;


				//////////
				// Update the ptrSESrc entry, to remove this lll entry from its lists
				//////
					// Update the pointer for the preceding entry
					if (lllPrev)
						lllPrev->next = lllNext;
					// Update the pointer for the following entry
					if (lllNext)
						lllNext->prev = lllPrev;
					// Right now, lllPrev points forward past lll, and lllNext points backward past lll


				//////////
				// lll is currently an orphan entry that thinks it's not orphaned because it still has prev and next pointers potentially pointing off somewhere
				//////
					// Update lll's prev and next entries to point nowhere
					lll->next = NULL;
					lll->prev = NULL;
					// At this point, lll is only pointed to by its lml entry.


				// All done!
				return(lll);
			}
		}
		// If we get here, invalid environment
		return(NULL);
	}

	SMasterList* iSEChain_migrateByNum(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize)
	{
		u32				lnI;
		SMasterList*	lml;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && lnSrcNum < ptrSESrc->masterCount && lnSrcNum <= ptrSESrc->masterCount)
		{
			// We enter an infinite loop in case we have to
			while (1)
			{
				// Find an empty slot in the destination
				for (lnI = tnHint; lnI < ptrSEDst->masterCount; lnI++)
				{
					if (!ptrSEDst->master[lnI] || !ptrSEDst->master[lnI]->used)
					{
						// We found an empty slot, migrate it
						lml							= ptrSESrc->master[lnSrcNum];
						ptrSEDst->master[lnI]		= lml;

						// Clear out the source slot
						ptrSESrc->master[lnSrcNum]	= NULL;

						// See if the thing that was pointed to was the first or last entry (or both (only entry))
						if (ptrSESrc->root == lml)
						{
							// This was the first entry
							if (ptrSESrc->last == lml)
							{
								// And it was the last entry, making it the ONLY entry
								ptrSESrc->root = NULL;
								ptrSESrc->last = NULL;

							} else {
								// It was just the first entry
								ptrSESrc->root = (SMasterList*)lml->ll.next;
							}

						} else if (ptrSESrc->last == lml) {
							// It was the last entry
							ptrSESrc->last = (SMasterList*)lml->ll.prev;
						}
						//else it's just one in the middle, so no worries

						// Detach from its former list (former's previous points to former's next, former's next points to former's previous, basically they both skip over this item)
						if (lml->ll.prev)	((SMasterList*)(lml->ll.prev))->ll.next = lml->ll.next;
						if (lml->ll.next)	((SMasterList*)(lml->ll.next))->ll.prev = lml->ll.prev;
						// Right now, lml is an orphan, but it has pointers to its old slots

						// Append it to the new list, and update its pointers to its new home
						if (!ptrSEDst->root)
						{
							// This is the first item in the destination
							ptrSEDst->root	= lml;
							ptrSEDst->last	= lml;
							lml->ll.prev	= NULL;

						} else {
							// Append it to the end of the chain
							ptrSEDst->last->ll.next = (SLL*)lml;
							lml->ll.prev			= (SLL*)ptrSEDst->last;
							ptrSEDst->last			= lml;
						}
						// Make the newly migrated item now point to nothing, because it is the last item
						lml->ll.next = NULL;

						// All done!
						return(lml);
					}
				}
				// If we get here, no empty slots. Allocate some, rinse, and repeat. :-)
				iSEChain_allocateAdditionalMasterSlots(ptrSEDst, tnBlockSize);

				// Process through again beginning at the newly added portion
				tnHint = lnI;
				// We'll never break out of this loop because we will always return above
			}
			// Control will never get here
		}
		// If we get here, error
		return(NULL);
	}




//////////
//
// Append a new node to the list, and return the pointer.
// The nodeHint is provided and can be used to find the end of the chain faster than iterating
// from the root.  Typically it is the last returned node.  However, if NULL, this process will
// iterate from the root node forward.
//
//////
	SLL* iLl_appendNode(SLL** root, SLL* nodeHint, SLL* nodeNext, SLL* nodePrev, u32 tnUniqueId, u32 tnSize)
	{
		SLL* node;


		// Make sure our environment is sane
		node = NULL;
		if (root)
		{
			// Create a new node
			node = iLl_createNode(nodePrev, nodeNext, tnUniqueId, tnSize);
			
			// Append it to the chain
			if (*root)
			{
				// There is already data
				if (!nodeHint)
					nodeHint = *root;

				// Iterate forward until we reach the end
				while (nodeHint->next)
					nodeHint = nodeHint->next;

				// Append as the next item from where we are
				nodeHint->next = node;

			} else {
				// This will be the first entry
				*root = node;
			}
		}
		// Indicate our success or failure
		return(node);
	}




//////////
//
// Creates a new 2-way linked list with optional nodePrev and nodeNext info, using
// the indicated size for the allocation (which is beyond the SLL portion at the head).
//////
	SLL* iLl_createNode(SLL* nodePrev, SLL* nodeNext, u32 tnUniqueId, u32 tnSize)
	{
		SLL* node;


		// Allocate the size
		node = (SLL*)malloc(sizeof(SLL) + tnSize);
		if (node)
		{
			// We're good
			memset(node, 0, tnSize);
			
			// Store a unique id
			node->uniqueId	= tnUniqueId;

			// Update our pointers
			node->prev		= nodePrev;
			node->next		= nodeNext;
		}

		// Indicate our success or failure
		return(node);
	}




//////////
//
// Called to delete a link list node.  If need be it orphanizes the node first.
//
//////
	void iLl_deleteNode(SLL* node)
	{
		if (node)
		{
			//////////
			// Disconnect
			//////
				if (node->prev || node->next)
					iLl_orphanizeNode(node);


			//////////
			// Delete the node
			//////
				free(node);
		}
	}




//////////
//
// Called to delete a link list node with a callback.  If need be it orphanizes the node first.
//
//////
	void iLl_deleteNodesWithCallback(SLLCallback* cb)
	{
		if (cb && cb->node)
		{
			//////////
			// Disconnect
			//////
				if (cb->node->prev || cb->node->next)
					iLl_orphanizeNode(cb->node);


			//////////
			// Let the user say their goodbyes
			//////
				if (cb->_func)
					cb->funcVoid(cb);


			//////////
			// Delete the node
			//////
				free(cb->node);
		}
	}




//////////
//
// Inserts a 2-way linked relative to the nodeRef, either before or after.  If the
// node is already connected, it is disconnected.
//
//////
	bool iLl_insertNode(SLL* node,  SLL* nodeRef,  bool tlAfter)
	{
// TODO:  UNTESTED CODE
		// Is our environment sane?
		if (node && nodeRef)
		{
			//////////
			// Disconnect
			//////
				if (node->prev || node->next)
					iLl_orphanizeNode(node);


			//////////
			// Is it going before or after?
			//////
				if (tlAfter)
				{
					// Point the one after this back to node to be inserted
					if (nodeRef->next)
						nodeRef->next->prev	= node;		// The one after points back to the node we're inserting

					// Are we updating to a valid node?
					if (node)
					{
						// The node is valid, so we can update relative pointers
						// Point this node to the one that will be after
						node->next = nodeRef->next;
						node->prev = nodeRef;
					}

					// Store the pointer to the node
					nodeRef->next = node;


				} else {
					// Positioning this node before
					// Point the one before this forward to the node to be inserted
					if (nodeRef->prev)
						nodeRef->prev->next = node;

					// Are we updating to a valid node?
					if (node)
					{
						// The node is valid, so we can update relative pointers
						// Point this node to the one that will be after
						node->prev = nodeRef->prev;
						node->next = nodeRef;
					}

					// Store the pointer to the node
					nodeRef->prev = node;
				}
		}
		// Failure
		return(false);
	}




//////////
//
// Disconnects a node from its existing chain
//
//////
	void iLl_orphanizeNode(SLL* node)
	{
// TODO:  UNTESTED CODE
		// Is our environment sane?
		if (node)
		{

			//////////
			// Is there one before?
			//////
				if (node->prev)
					node->prev->next = node->next;		// Make the one before point to the one after

			//////////
			// Is there one after?
			//////
				if (node->next)
					node->next->prev = node->prev;		// Make the one after point to the one before

			//////////
			// Free up all parts
			//////
				node->next	= NULL;
				node->prev	= NULL;
		}
	}




//////////
//
// Called to delete the entire chain (beginning from where it's at
//
//////
	void iLl_deleteNodeChain(SLL** root)
	{
		SLL* node;
		SLL* nodeNext;


		// Make sure the environment is sane
		if (root)
		{
			// Iterate through deleting each entry
			node = *root;
			while (node)
			{
				// Grab the next node
				nodeNext = node->next;
				
				// Delete the node
				free(node);

				// Move to next item
				node = nodeNext;
			}

			// Reset the pointer
			*root = NULL;
		}
	}




//////////
//
// Called to delete the entire chain (beginning from where it's at on) using an optional callback.
// The callback should not delete the node, but only anything the node points to.
//
//////
	void iLl_deleteNodeChainWithCallback(SLLCallback* cb)
	{
		SLL* nodeNext;


		// Make sure the environment is sane
		if (cb)
		{
			// Iterate through deleting each entry
			while (cb->node)
			{
				// Grab the next node
				nodeNext = cb->node->next;

				// Perform the callback
				if (cb->_func)
					cb->funcVoid(cb);

				// Delete the node
				free(cb->node);

				// Move to next node
				cb->node = nodeNext;
			}
			// All done
		}
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
//////
	void iLl_iterateViaCallback(SLLCallback* cb)
	{
		//////////
		// For each node, process its portion
		//////
			while (cb->node)
			{

				//////////
				// Callback to compute the SHA1 on this item
				//////
					cb->funcVoid(cb);
					//vvm_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


				//////////
				// Move to next node
				//////
					cb->node = cb->node->next;
			}
	}




//////////
//
// Called to iterate from the indicated node backwards
//
//////
	void iLl_iterateBackwardViaCallback(SLLCallback* cb)
	{
		//////////
		// For each node, process its portion
		//////
			while (cb->node)
			{

				//////////
				// Callback to compute the SHA1 on this item
				//////
					cb->funcVoid(cb);
					//vvm_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


				//////////
				// Move to next node
				//////
					cb->node = cb->node->prev;
			}
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
//////
	SLL* iLl_getFirstNode(SLL* node)
	{
		// Make sure the environment is sane
		if (node)
		{
			// Iterate backwards to the top
			while (node->prev)
				node = node->prev;
		}

		// Indicate where we are
		return(node);
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
// The parameters in the callback are:
//		ptr			-- LL node
//////
	SLL* iLl_getLastNode(SLL* node)
	{
		// Make sure the environment is sane
		if (node)
		{
			// Iterate forwards to the end
			while (node->next)
				node = node->next;
		}

		// Indicate where we are
		return(node);
	}
