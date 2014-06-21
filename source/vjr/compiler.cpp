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
struct SOssCompCallback;
struct SAsciiCompSearcher;
struct SStartEndCallback;
struct SLL;
struct SLLCallback;

//////////
//
// Forward declarations for parsing VXB-- lines and components
//
//////////
	u32						compile_VxbMm								(SEditChainManager* codeBlock, bool tlEditAndContinue);
 	SComp*					iTranslateSourceLineToSComps				(SAsciiCompSearcher* tsComps, SEditChain* line);
 	void					iTranslateSCompsToOthers					(SAsciiCompSearcher* tsComps, SEditChain* line);
// 	u32 CALLTYPE			oss_writeSOssLineSequenceToDisk				(s8* tcPathname, SStartEnd* tseLines);
// 	u32 CALLTYPE			oss_writeSOssLineSequenceCompsToDisk		(s8* tcPathname, SStartEnd* tseLines);
// 	u32 CALLTYPE			oss_writeSOssLineSequenceCompsDebuggingToDisk(s8* tcPathname, SStartEnd* tseLines);
	bool					iFindFirstOccurrenceOfAsciiCharacter		(s8* tcHaystack, u32 tnHaystackLength, s8 tcNeedle, u32* tnPosition);
	SComp*					iFindNextSCompBy_iCode						(SComp* comp, u32 tniCode, SComp** compLastScanned);
	SComp*					iSkipPastSComp_iCode						(SComp* comp, u32 tniCode);
	u32						iCombine2SComps								(SEditChain* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2,                     u32 tniCodeCombined);
	u32						iCombine3SComps								(SEditChain* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeNeedle3, u32 tniCodeCombined);
	u32						iCombineAllBetweenSOssComps					(SEditChain* line, u32 tniCodeNeedle,                                          u32 tniCodeCombined);
	u32						iCombineAllAfterSOssComp					(SEditChain* line, u32 tniCodeNeedle);
// 	u32 CALLTYPE			oss_combineAllCasks							(SOssComp* firstComp, bool* tlNestingError, SOssComp** compError);
	u32						iRemoveExtraneousWhitespaceSOssComps		(SEditChain* line, u32 tniCodeWhitespace);

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
	bool					iioss_translateSOssCompsToOthersCallback	(SStartEndCallback* cb);
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
			bool		(*validate)(SOssCompCallback* val);
		};

		// Used for an explicit callback to handle this component or text
		union {
			u32			_custom;
			void		(*custom)(void);
		};
	};

	struct SOp
	{
		bool			isComp;											// If it is a target component, such as a literal value
		bool			isParam;										// If it references a parameter variable
		bool			isLocal;										// If it is a local variable
		bool			isScoped;										// If it is a scoped/temporary variable (scoped variables are reused continually during normal processing for each different source code line)
		// Note:  If it's not one of the above, it's an "other" which must be looked up in the current runtime environment

		// Pointer to first (if there is a succession)
		union {
			SComp*		comp;											// The first component
			SVariable*	param;											// A parameter reference
			SVariable*	local;											// A local variable reference
			SVariable*	scoped;											// A temporary variable reference used for inter-source-code-line processing
			SVariable*	other;											// Unknown item which must be looked up in the context of the runtime environment
		};
		// Number thereafter
		u32				count;											// The number of components (in comp or other) as input
	};

	// Sub-instructions are components of an xbase source code line.
	// They conduct individual operations only, being part of the larger computation across multiple sub-instructions.
	struct SSubInstr
	{
		u32				operation;										// The sub-instruction operation related to the bigger picture
		u32				sub_instr;										// The sub-instruction being executed, such as "+" in "2 + 4"

		// Operands used for the sub-instruction
		SOp				left;											// The left operand, such as "2" in "2 + 4"
		SOp				right;											// The right operand, such as "4" in "2 + 4"
		SVariable*		result;											// Where the result is stored
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
		SDatum			sourceCode;										// Copy at last compile of LEFT(parent->sourceCode.data, parent->sourceCodePopulated)

		// Components compiled in prior compiler passes
		SComp*			firstComp;										// Pointer to the first component identified on this line

		// Executable code
		SSubInstr*		subInstr[];										// Low-level executable code for this line
		u32				subInstrCount;									// How many sub-instructions there are

		// Results of compilation
		SCompileNote*	errors;											// Noted error
		SCompileNote*	warnings;										// Noted warning
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

	struct SOssCompCallback
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


//////////
// Known operators to the system
//////
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
	const u32		_ICODE_UNKNOWN									= 0;
	const u32		_ICODE_ALPHA									= 1;
	const u32		_ICODE_ALPHANUMERIC								= 2;
	const u32		_ICODE_NUMERIC									= 3;
	const u32		_ICODE_OPERATOR									= 4;
	const u32		_ICODE_WHITESPACE								= 5;
	const u32		_ICODE_PLUS										= 6;
	const u32		_ICODE_MINU										= 7;
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
	const u32		_ICODE_CARET									= 22;
	const u32		_ICODE_AMPERSAND								= 23;
	const u32		_ICODE_EQUAL_SIGN								= 24;
	const u32		_ICODE_PIPE_SIGN								= 25;
	const u32		_ICODE_REVERSE_QUOTE							= 26;
	const u32		_ICODE_SEMICOLON								= 27;
	const u32		_ICODE_GREATER_THAN								= 28;
	const u32		_ICODE_LESS_THAN								= 30;
	const u32		_ICODE_LEFT_PARENTHESIS							= 31;
	const u32		_ICODE_RIGHT_PARENTHESIS						= 32;
	const u32		_ICODE_LEFT_BRACKET								= 33;
	const u32		_ICODE_RIGHT_BRACKET							= 34;
	const u32		_ICODE_LEFT_BRACE								= 35;
	const u32		_ICODE_RIGHT_BRACE								= 36;
	const u32		_ICODE_SLASH									= 37;
	const u32		_ICODE_DOLLAR_SIGN								= 38;
	// Preprocessor
	const u32		_ICODE_INCLUDE									= 100;
	const u32		_ICODE_DEFINE									= 101;
	// Keywords
	const u32		_ICODE_WITH										= 200;
	const u32		_ICODE_ENDWITH									= 201;
	const u32		_ICODE_IF										= 202;
	const u32		_ICODE_ENDIF									= 203;
	const u32		_ICODE_FUNCTION									= 204;
	const u32		_ICODE_ENDFUNC									= 205;
	const u32		_ICODE_PUBLIC									= 206;
	const u32		_ICODE_LOCAL									= 207;
	const u32		_ICODE_NOT										= 208;
	const u32		_ICODE_AND										= 209;
	const u32		_ICODE_OR										= 210;
	const u32		_ICODE_OVJR										= 211;
	const u32		_ICODE_RGB										= 212;
	const u32		_ICODE_MIN										= 213;
	const u32		_ICODE_MAX										= 214;
	const u32		_ICODE_INT										= 215;
	const u32		_ICODE_SYSMETRIC								= 216;
	const u32		_ICODE_VERSION									= 217;
	const u32		_ICODE_FLAGS									= 218;
	const u32		_ICODE_JDEBI									= 219;
	const u32		_ICODE_INHERIT									= 220;
	const u32		_ICODE_ADDOBJECT								= 221;
	const u32		_ICODE_LEFT										= 222;
	const u32		_ICODE_TOP										= 223;
	const u32		_ICODE_RIGHT									= 224;
	const u32		_ICODE_BOTTOM									= 225;
	const u32		_ICODE_WIDTH									= 226;
	const u32		_ICODE_HEIGHT									= 227;
	const u32		_ICODE_VISIBLE									= 228;
	const u32		_ICODE_PROTECTED								= 229;
	const u32		_ICODE_MAIN										= 230;
	const u32		_ICODE_LOAD_LAST_FROM_VJR_USER_DBF				= 231;


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
		{ "(",						1,			false,		_ICODE_LEFT_PARENTHESIS,				false,				NULL,					NULL },
		{ ")",						1,			false,		_ICODE_RIGHT_PARENTHESIS,				false,				NULL,					NULL },
		{ "[",						1,			false,		_ICODE_LEFT_BRACKET,					false,				NULL,					NULL },
		{ "]",						1,			false,		_ICODE_RIGHT_BRACKET,					false,				NULL,					NULL },
		{ "{",						1,			false,		_ICODE_LEFT_BRACE,						false,				NULL,					NULL },
		{ "}",						1,			false,		_ICODE_RIGHT_BRACE,						false,				NULL,					NULL },
		{ "+",						1,			false,		_ICODE_PLUS,							false,				NULL,					NULL },
		{ "-",						1,			false,		_ICODE_MINU,							false,				NULL,					NULL },
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
		{ "!",						1,			false,		_ICODE_EXCLAMATION_MARK,				false,				NULL,					NULL },
		{ "#",						1,			false,		_ICODE_POUND_SIGN,						false,				NULL,					NULL },
		{ "$",						1,			false,		_ICODE_DOLLAR_SIGN,						false,				NULL,					NULL },
		{ "%",						1,			false,		_ICODE_PERCENT_SIGN,					false,				NULL,					NULL },
		{ "^",						1,			false,		_ICODE_CARET,							false,				NULL,					NULL },
		{ "&",						1,			false,		_ICODE_AMPERSAND,						false,				NULL,					NULL },
		{ "=",						1,			false,		_ICODE_EQUAL_SIGN,						false,				NULL,					NULL },
		{ "|",						1,			false,		_ICODE_PIPE_SIGN,						false,				NULL,					NULL },
		{ "`",						1,			false,		_ICODE_REVERSE_QUOTE,					false,				NULL,					NULL },
		{ ";",						1,			false,		_ICODE_SEMICOLON,						false,				NULL,					NULL },
		{ ">",						1,			false,		_ICODE_GREATER_THAN,					false,				NULL,					NULL },
		{ "<",						1,			false,		_ICODE_LESS_THAN,						false,				NULL,					NULL },
		/* As a last-case condition, we tag every character that we didn't previously identify with the unknown tag */                      	
		{ "_\000\377\000\000",		1,			true,		_ICODE_UNKNOWN,							false,				NULL,					NULL },
		{ 0,						0,			0,			0,										0,					0,						0 }
	};

	// Zeroeth-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywords0[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		validate handler		custom handler
		{ "include",				7,			false,		_ICODE_INCLUDE,							true,				NULL,					NULL },
		{ "define",					6,			false,		_ICODE_DEFINE,							true,				NULL,					NULL },
		{ 0,						0,			0,			0,										0,					0,						0 }
	};

	// First-pass keywords
	SAsciiCompSearcher	cgcKeywordKeywords1[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		validate handler		custom handler
		{ "with",					4,			false,		_ICODE_WITH,							true,				NULL,					NULL },
		{ "endwith",				7,			false,		_ICODE_ENDWITH,							true,				NULL,					NULL },
		{ "if",						2,			false,		_ICODE_IF,								true,				NULL,					NULL },
		{ "endif",					5,			false,		_ICODE_ENDIF,							true,				NULL,					NULL },
		{ "function",				8,			false,		_ICODE_FUNCTION,						true,				NULL,					NULL },
		{ "endfunc",				7,			false,		_ICODE_ENDFUNC,							true,				NULL,					NULL },
		{ "public",					6,			false,		_ICODE_PUBLIC,							true,				NULL,					NULL },
		{ "local",					5,			false,		_ICODE_LOCAL,							true,				NULL,					NULL },
		{ "not",					3,			false,		_ICODE_NOT,								false,				NULL,					NULL },
		{ "and",					3,			false,		_ICODE_AND,								false,				NULL,					NULL },
		{ "or",						2,			false,		_ICODE_OR,								false,				NULL,					NULL },
		{ "_vjr",					4,			false,		_ICODE_OVJR,							false,				NULL,					NULL },
		{ "rgb",					3,			false,		_ICODE_RGB,								false,				NULL,					NULL },
		{ "min",					3,			false,		_ICODE_MIN,								false,				NULL,					NULL },
		{ "max",					3,			false,		_ICODE_MAX,								false,				NULL,					NULL },
		{ "int",					3,			false,		_ICODE_INT,								false,				NULL,					NULL },
		{ "sysmetric",				9,			false,		_ICODE_SYSMETRIC,						false,				NULL,					NULL },
		{ "version",				7,			false,		_ICODE_VERSION,							false,				NULL,					NULL },
		{ "flags",					5,			false,		_ICODE_FLAGS,							false,				NULL,					NULL },
		{ "jdebi",					5,			false,		_ICODE_JDEBI,							false,				NULL,					NULL },
		{ "inherit",				7,			false,		_ICODE_INHERIT,							false,				NULL,					NULL },
		{ "addobject",				9,			false,		_ICODE_ADDOBJECT,						false,				NULL,					NULL },
		{ "left",					4,			false,		_ICODE_LEFT,							false,				NULL,					NULL },
		{ "top",					3,			false,		_ICODE_TOP,								false,				NULL,					NULL },
		{ "right",					5,			false,		_ICODE_RIGHT,							false,				NULL,					NULL },
		{ "bottom",					6,			false,		_ICODE_BOTTOM,							false,				NULL,					NULL },
		{ "width",					5,			false,		_ICODE_WIDTH,							false,				NULL,					NULL },
		{ "height",					6,			false,		_ICODE_HEIGHT,							false,				NULL,					NULL },
		{ "visible",				7,			false,		_ICODE_VISIBLE,							false,				NULL,					NULL },
		{ "protected",				9,			false,		_ICODE_PROTECTED,						false,				NULL,					NULL },
		{ "main",					4,			false,		_ICODE_MAIN,							false,				NULL,					NULL },
		{ "loadlastfromvjruserdbf", 22,			false,		_ICODE_LOAD_LAST_FROM_VJR_USER_DBF,		false,				NULL,					NULL },
		{ 0,						0,			0,			0,										0,					0,						0 }
	};









//////////
//
// Compiles
//
//////
	u32 compile_VxbMm(SEditChainManager* codeBlock, bool tlEditAndContinue)
	{
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
		SOssCompCallback		lccb;


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
									comp = (SComp*)iLl_appendNode((SLL**)&line->firstComp, (SLL*)compLast, NULL, (SLL*)compLast, iGetNextUid(), sizeof(SComp));


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
// Called to search the already parsed SAsciiCompSearcher list of components, looking for
// combinations which relate to other component types.  The primary translations here are
// alpha/alphanumeric/numeric forms to other forms.
//
//////
	void iTranslateSCompsToOthers(SAsciiCompSearcher* tsComps, SEditChain* line)
	{
		SStartEndCallback cb;


		cb._func	= (u32)iioss_translateSOssCompsToOthersCallback;
		cb.extra	= (u32)tsComps;
// TODO:  need to bring this callback code into this algorithm
//		vvm_SEChain_searchByCallback(&line->comps, &cb);
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
		if (line && line->firstComp)
		{
			// Grab the first component
			comp = line->firstComp;

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
		if (line && line->firstComp)
		{
			// Grab the first component
			comp = line->firstComp;

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
	u32 iCombineAllBetweenSOssComps(SEditChain* line, u32 tniCodeNeedle, u32 tniCodeCombined)
	{
		u32		lnCount;
		SComp*	compNext;
		SComp*	comp;
		SComp*	compSearcher;


// UNTESTED CODE:  breakpoint and examine
		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->firstComp)
		{
			// Grab the first component
			comp = line->firstComp;

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
	u32 iCombineAllAfterSOssComp(SEditChain* line, u32 tniCodeNeedle)
	{
		u32		lnCount;
		SComp*	compNext;
		SComp*	comp;


// UNTESTED CODE:  breakpoint and examine
		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->firstComp)
		{
			// Grab the first component
			comp = (SComp*)line->firstComp;

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
	u32 iRemoveExtraneousWhitespaceSOssComps(SEditChain* line, u32 tniCodeWhitespace)
	{
		return(0);
	}




//////////
//
// Callback, used to translate existing components into other components
// Note:  Always returns false, so it will continue being fed every component
//
//////
	bool iioss_translateSOssCompsToOthersCallback(SStartEndCallback* cb)
	{
		bool					llResult;
		s32						lnLacsLength;
		SComp*				comp;
		SAsciiCompSearcher*		lacs;
		SOssCompCallback		lccb;


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
		if (compRef && line)
		{
			// Allocate a new pointer
			compNew = (SComp*)iLl_appendNode((SLL**)&line->firstComp, NULL, NULL, NULL, iGetNextUid(), sizeof(SComp));
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
			if (line)
			{
				// Add the new component to line->comps
				compNew = (SComp*)iLl_appendNode((SLL**)&line->firstComp, NULL, NULL, NULL, iGetNextUid(), sizeof(SComp));

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
