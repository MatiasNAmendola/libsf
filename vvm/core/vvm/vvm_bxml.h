//////////
//
// /libsf/vvm/vvmoss/vo_Bxml.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     December 31, 2012
//////
// Change log:
//     December 31, 2012 - Initial creation
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
// Examples:
//		/this(0).level(0).data(3).attrib(0).name
//		/this(0).level(0).data(3).attrib(0).value
//		/this(0).level(0).data(3).attrib(name).value
//		/this(1).field(2):_avalue(1)
//		/this(1).field(2):_aname(1)
//		/this*.foo*.way
//		/this.foo.way
//
//




//////////
//
// Forward declarations
//
/////
	SBxml*				ibxml_asciiLoadFile								(s8* filename, u64* tnBytesRead, u64* tnErrorOffset, u64* tnErrorCode);
	SBxml*				ibxml_asciiLoadBuffer							(s8* buffer, u64 tnLength, u64* tnErrorOffset, u64* tnErrorCode);

	// Internal supporting functions
	u64					iibxml_scanForwardToNonAlphanumeric				(s8* buffer, u64 tnMaxLength);
	u64					iibxml_scanForwardToNonNumeric					(s8* buffer, u64 tnMaxLength);
	u64					iibxml_scanForwardToCharacter					(s8* buffer, u64 tnMaxLength, s8 tcChar);
	SBxml*				iibxml_createNewSBxml							(u32 tnLevel, SBxml* bxmlRelation, bool tlIsChild, SBxml* next, SBxml* prev, SBxml* parent, SBxml* child);
	void				iibxml_storeErrorCode							(u64* tnErrorOffsetStore, u64 tnErrorOffset, u64* tnErrorCodeStore, u64 tnErrorCode);
	void				ibxml_saveNode									(SBuilder* build, SBxml* bxml, bool tlSaveChildNodes, bool tlSaveSiblings, u64* lnError);
	void				iibxml_saveNodeCallback							(SStartEndCallback* cb);
	bool				iibxml_AttributeDeleteCallback					(SStartEndCallback* cb);
	bool				iibxml_attributeInsertCallback					(SStartEndCallback* cb);
	SBxmla*				ibxml_attributeDuplicate						(SBxmla* bxmlaOriginal);
	SBxmla*				ibxml_attributeDuplicateAs						(SBxmla* bxmlaOriginal, s8* tcNewName, u32 tnNewNameLength);
	SBxmla*				ibxml_attributeCreateAs							(s8* tcNewName, u32 tnNewNameLength);
	SBxmla*				ibxml_attributeCreateAsWithData					(s8* tcNewName, u32 tnNewNameLength, s8* tcData, u32 tnDataLength, u32 tnTotalDataLength);
	SBxml*				ibxml_nodeCreateAs								(s8* tcNewName, u32 tnNewNameLength);
	SBxml*				ibxml_nodeCopyAs								(SBxml* bxmlSrc, s8* tcNewName, u64 tnNewNameLength, bool tlCopyAttributes, bool tlCopyChildren, bool* tlResult);
	void				iibxml_nodeCopyAttributes						(SBxml* bxmlDst, SBxml* bxmlSrc, bool* tlResult);
	void				iibxml_nodeCopyAttributesCallback				(SStartEndCallback* cb);
	void				iibxml_nodeCopyChildren							(SBxml* bxmlDst, SBxml* bxmlSrc, bool tlCopyAttributes, bool* tlResult);
	void				iibxml_recordLastError							(u32 tnResourceNumber, u32 tnErrorNumber, s8* tcDescriptionZ, SBxml* bxml, SBxmla* bxmla, u64 tnErrorOffset);
	bool				ibxml_nodeDeleteBranch							(SBxml* bxml);
	void				iibxml_nodeDeleteBranchAttributeCallback		(SStartEndCallback* cb);
	u64					ivvm_bxmlAttributeSha1One						(SBxmla* bxmla, u8 sha20Bytes[20]);
	u64					ivvm_bxmlAttributeSha1							(SBxml*  bxml,  u8 sha20Bytes[20]);
	u64					ivvm_bxmlAttributeSha1Tag						(SBxml*  bxml,  u8 sha20Bytes[20]);
	u64					ivvm_bxmlAttributeSha1Data						(SBxml*  bxml,  u8 sha20Bytes[20]);
	u64					ivvm_bxmlNodeSha1								(SBxml*  bxml,  u8 sha20Bytes[20]);
	u64					ivvm_bxmlNodeSha1Tag							(SBxml*  bxml,  u8 sha20Bytes[20]);
	u64					ivvm_bxmlNodeSha1Data							(SBxml*  bxml,  u8 sha20Bytes[20]);
	void				iivvm_bxmlComputeSha1OnNode						(SBxml*  bxml,  u8 handle[92], u8 buffer[64], u32 tnLevel, bool tlAttributes, bool tlChildren, bool tlSiblings);
	void				iivvm_bxmlComputeSha1OnNodeAttributeCallback	(SStartEndCallback* cb);
	void				iivvm_bxmlComputeSha1OnAttribute				(SBxmla* bxmla, u8 handle[92], u8 buffer[64], bool tlName, bool tlData);

	bool				iivvm_bxmlFindFirst								(SBxml* bxmlRoot, SBxml** bxmlNodeFound, SBxmla** bxmlaAttributeFound, SDatum* tsWildcard, bool tlTraverseChildren, bool tlSearchAttributes, void** x);
	bool				iivvm_bxmlFindContinue							(void* x);
	bool				iivvm_bxmlDataFindFirst							(SBxml* bxmlRoot, SBxmla** bxmlaAttributeFound, SDatum* tsWildcard, bool tlTraverseChildren, void** x);
	bool				iivvm_bxmlDataFindContinue						(void* x);
	SBxmla*				iivvm_bxmlFindAttribute							(SBxml* bxml, SBxmla** bxmla, SDatum* tsWildcardSearch, u32 tnInstance);




//////////
//
// Constants used in the BXML engine
//
//////
	const s8		cgcAutoComment[]						= "autoComment";
	const s8		cgcAnonymousTagName[]					= "a";
