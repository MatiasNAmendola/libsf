//////////
//
// /libsf/source/vjr/compiler.h
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jun.29.2014
//////
// Change log:
//     Jun.29.2014 - Initial creation
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




struct SEditChainManager;
struct SEditChain;
struct SFunction;
struct SNode;
struct SLL;
struct SLLCallback;
struct SComp;
struct SCompCallback;
struct SCompiler;
struct SCompileContext;
struct SCompileNote;
struct SAsciiCompSearcher;
struct SStartEnd;
struct SStartEndCallback;
struct SOp;
struct SMasterList;
struct SVariable;


//////////
// compiler.cpp
//////////
	u32						compile_Vxbmm								(SEditChainManager* codeBlock, SCompileContext* ccData, bool tlEditAndContinue);

	SFunction*				iiComps_xlatToFunction						(SEditChainManager* codeBlock, SEditChain* line);
	bool					iiComps_xlatToNodes							(SEditChain* line, SCompiler* compiler);
	SNode*					iiComps_xlatToNodes_parenthesis_left		(SNode** root, SNode* active, SComp* comp);
	SNode*					iiComps_xlatToNodes_parenthesis_right		(SNode** root, SNode* active, SComp* comp);

	void					iComps_removeAll							(SEditChain* line);
 	SComp*					iComps_translateSourceLineTo				(SAsciiCompSearcher* tsComps, SEditChain* line);
 	bool					iComps_translateToOthers					(SAsciiCompSearcher* tsComps, SEditChain* line);
	s32						iComps_translateToOthers_test				(s8* tcHaystack, s8* tcNeedle, s32 tnLength);
	SComp*					iComps_findNextBy_iCode						(SComp* comp, u32 tniCode, SComp** compLastScanned);
	SComp*					iComps_skipPast_iCode						(SComp* comp, u32 tniCode);
	u32						iComps_combineNextN							(SComp* comp, u32 tnCount, s32 tnNewICode);
	u32						iComps_combine2								(SEditChain* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2,                     u32 tniCodeCombined);
	u32						iComps_combine3								(SEditChain* line, u32 tniCodeNeedle1, u32 tniCodeNeedle2, u32 tniCodeNeedle3, u32 tniCodeCombined);
	u32						iComps_CombineAdjacentAlphanumeric			(SEditChain* line);
	u32						iComps_CombineAdjacentNumeric				(SEditChain* line);
	u32						iComps_CombineAllBetween					(SEditChain* line, u32 tniCodeNeedle,                                          u32 tniCodeCombined);
	u32						iComps_combineAllAfter						(SEditChain* line, u32 tniCodeNeedle);
	u32						iComps_removeWhitespaces					(SEditChain* line);
	void					iComps_removeStartEndComments				(SEditChain* line);
	void					iComps_xlatNaturalGroupings					(SEditChain* line);
	s32						iiComps_charactersBetween					(SComp* compLeft, SComp* compRight);

//////////
// Jun.25.2014 -- This block of code was originally created before I began working on
// iiTranslateSOpsToSubInstr() above.  As such, it is stale and will probably be
// refactored or deleted.
// BEGIN
//////
	void					iiComps_xlatToSubInstr						(SEditChain* line);
	SComp*					iiComps_xlatToSubInstr_findInmostExpression	(SNode* si, SEditChain* line);
	void					iiComps_xlatToSubInstr_findStartOfComponent	(SComp* compRoot, SOp* op);
	void					iiComps_xlatToSubInstr_findFullComponent	(SComp* compRoot, SOp* op);
	bool					iiComps_xlatToSubInstr_isEqualAssignment	(SEditChain* line);
//////
// END
//////////

	u32						iBreakoutAsciiTextDataIntoLines_ScanLine	(s8* tcData, u32 tnMaxLength, u32* tnLength, u32* tnWhitespaces);
	bool					iFindFirstOccurrenceOfAsciiCharacter		(s8* tcHaystack, u32 tnHaystackLength, s8 tcNeedle, u32* tnPosition);
	u32						iGetNextUid									(void);
	void*					iSEChain_prepend							(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*					iSEChain_append								(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*					iSEChain_appendOrPrepend					(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult);
	u32						iSkipWhitespaces							(s8* tcData, u32 tnMaxLength);
	u32						iSkipToCarriageReturnLineFeed				(s8* tcData, u32 tnMaxLength, u32* tnCRLF_Length);
	void					iSEChain_appendMasterList					(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded);
	bool					iSEChain_allocateAdditionalMasterSlots		(SStartEnd* ptrSE, u32 tnBlockSize);
	s32						iTranslateToCompsTest						(s8* tcHaystack, s8* tcNeedle, s32 tnLength);
	bool					iioss_translateCompsToOthersCallback		(SStartEndCallback* cb);
	void*					iSEChain_searchByCallback					(SStartEnd* ptrSE, SStartEndCallback* cb);
	void					iiComps_xlatToOthersCallback__insertCompByCompCallback		(SComp* compRef, SComp* compNew, bool tlInsertAfter);
	void					iiComps_xlatToOthersCallback__insertCompByParamsCallback	(SComp* compRef, SEditChain* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter);
	void					iiComps_xlatToOthersCallback__deleteCompsCallback			(SComp* comp, SEditChain* line);
	SComp*					iiComps_xlatToOthersCallback__cloneCompsCallback			(SComp* comp, SEditChain* line);
	SComp*					iiComps_xlatToOthersCallback__mergeCompsCallback			(SComp* comp, SEditChain* line, u32 tnCount, u32 tniCodeNew);
	void					iSEChain_deleteFrom							(SStartEnd* ptrSE, void* ptrCaller, bool tlDeletePointers);
	SLL*					iSEChain_completelyMigrateSLLByPtr			(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr, u32 tnHint, u32 tnBlockSize);
	SLL*					iSEChain_completelyMigrateSLLByNum			(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);
	SMasterList*			iSEChain_migrateByNum						(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);

	// Linked list functions
	SLL*					iLl_appendNode								(SLL** root, SLL* nodeHint, SLL* nodeNext, SLL* nodePrev, u32 tnUniqueId, u32 tnSize);
	SLL*					iLl_createNode								(                           SLL* nodePrev, SLL* nodeNext, u32 tnUniqueId, u32 tnSize);
	SLL*					iLl_appendNodeAtEnd							(SLL** root, u32 tnSize);
	SLL*					iLl_deleteNode								(SLL* node, bool tlDeleteSelf);
	void					iLl_deleteNodesWithCallback					(SLLCallback* cb);
	bool					iLl_insertNode								(SLL* node, SLL* nodeRef, bool tlAfter);
	void					iLl_orphanizeNode							(SLL* node);
	void					iLl_deleteNodeChain							(SLL** root);
	void					iLl_deleteNodeChainWithCallback				(SLLCallback* cb);
	void					iLl_iterateViaCallback						(SLLCallback* cb);
	void					iLl_iterateBackwardViaCallback				(SLLCallback* cb);
	SLL*					iLl_getFirstNode							(SLL* node);
	SLL*					iLl_getLastNode								(SLL* node);

	// Node functions
	SNode*					iNode_create								(SNode** root, SNode* hint, u32 tnDirection, SNode* parent, SNode* prev, SNode* next, SNode* left, SNode* right);
	SNode*					iNode_insertBetween							(SNode** root, SNode* node1, SNode* node2, u32 tnNode1Direction, u32 tnNode2Direction);
	void					iNode_politelyDeleteAll						(SNode** root, bool tlDeleteSelf, bool tlTraversePrev, bool tlTraverseNext, bool tlTraverseLeft, bool tlTraverseRight);

	// Function functions (LOL)
	SFunction*				iFunction_allocate							(s8* tcFuncName);
	SVariable*				iFunction_addVariable_scoped				(SFunction* func);
	void					iFunction_politelyDeleteCompiledInfo		(SFunction* func, bool tlDeleteSelf);

	// Variable functions
	SVariable*				iVariable_create							(void);
	void					iVariable_delete							(SVariable* var, bool tlDeleteSelf);
	void					iVariable_politelyDeleteChain				(SVariable** root);
	void					iVariable_politelyDeleteChain_callback		(SLLCallback* cb);

	// Op functions
	bool					iOp_setNull									(SOp* op);
	bool					iOp_setVariable_param						(SOp* op, SVariable* var, bool isOpAllocated);
	bool					iOp_setVariable_local						(SOp* op, SVariable* var, bool isOpAllocated);
	bool					iOp_setVariable_scoped						(SOp* op, SVariable* var, bool isOpAllocated);
	bool					iOp_setVariable_return						(SOp* op, SVariable* var, bool isOpAllocated);
	void					iOp_politelyDelete							(SOp* op, bool tlDeleteSelf);

	// Error functions
	void					iComp_appendError							(SComp* comp, u32 tnErrorNum, s8* tcMessage);

	// Line functions
	void					iLine_appendError							(SEditChain* line, u32 tnErrorNum, s8* tcMessage, u32 tnStartColumn, u32 tnLength);

	// Compiler functions
	SCompiler*				iCompiler_allocate							(void);

	// Compile note functions
	SCompileNote*			iCompileNote_create							(u32 tnStart, u32 tnEnd, u32 tnNumber, s8* tcMessage);
	SCompileNote*			iCompileNote_appendMessage					(SCompileNote** noteRoot, u32 tnStartColumn, u32 tnEndColumn, u32 tnNumber, s8* tcMessage);
