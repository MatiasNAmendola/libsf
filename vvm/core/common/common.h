//////////
//
// /libsf/vvm/common/common.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     September 19, 2012 - Initial creation
//     September 29, 2012 - PBL v1.0 license included directly in source files.
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




typedef unsigned long long			u64;
typedef unsigned long				u32;
typedef unsigned short				u16;
typedef unsigned char				u8;
typedef const unsigned long long	cu64;
typedef const unsigned long			cu32;
typedef const unsigned short		cu16;
typedef const unsigned char			cu8;

typedef long long					s64;
typedef long						s32;
typedef short						s16;
typedef char						s8;
typedef const long long				cs64;
typedef const long					cs32;
typedef const short					cs16;
typedef const char					cs8;
typedef wchar_t						w16;
typedef const wchar_t				cw16;

union UCsu8
{
	union {
		// By default this format is u8
		u8			_u8;

		// But we can also pass in other types
		union {
			s8		_s8;
			cu8		_cu8;
			cs8		_su8;
		};
	};
};
#define csu8 UCsu8

// Union of const, signed, unsigned, 8-bit pointers
union UCsu8p
{
	union {
		// By default this format is u8*
		u8*			_u8;

		// But we can also pass in other types
		union {
			cu8*	_cu8;
			s8*		_s8;
			cs8*	_cs8;
			csu8*	_csu8;
			void*	_v;
		};
	};
};
#define csu8p UCsu8p

// Helper macros
csu8p _csu8p_NULL()		{ csu8p x;	x._u8	= NULL;	return(x);	}
csu8p _csu8p(u8* p)		{ csu8p x;	x._u8	= p;	return(x);	}
csu8p _csu8p(cu8* p)	{ csu8p x;	x._cu8	= p;	return(x);	}
csu8p _csu8p(s8* p)		{ csu8p x;	x._s8	= p;	return(x);	}
csu8p _csu8p(cs8* p)	{ csu8p x;	x._cs8	= p;	return(x);	}
csu8p _csu8p(void* p)	{ csu8p x;	x._v	= p;	return(x);	}

typedef float						f32;
typedef double						f64;
typedef const float					cf32;
typedef const double				cf64;




//////////
// Indicate which platform is being compiled for
//////
	#define VVM_WINDOWS			1
//	#define VVM_LINUX			1
//	#define VVM_FREEBSD			1
//	#define VVM_ANDROID			1
#if VVM_WINDOWS == 1
	#define CALLTYPE WINAPI
#endif


//////////
// Common constants for use in the internal functions below
/////
	// Constant integers
	cu32					_COMMON_START_END_BLOCK_SIZE			= 32;			// Allocate 32 entries/slots at a time (Start/end)
	cu32					_COMMON_START_END_SMALL_BLOCK_SIZE		= 4;			// Allocate 4 entries/slots at a time (Start/end)
	cu32					_COMMON_BUFFER_BLOCK_SIZE				= 16384;		// Allocate 16KB at a time
	// Constant strings
	cs8						cgcSpace1[]								= " ";			// A single space
	cs8						cgcSpaceBxmlIndent[]					= "\t";			// We use tab characters for each indentation level
	cs8						cgcTagLeader[]							= "<";			// The <  in an BXML file
	cs8						cgcTagClosingLeader[]					= "</";			// The </ in an BXML file
	cs8						cgcTagCloser[]							= ">";			// The >  in an BXML file
	cs8						cgcTagSingleCloser[]					= "/>";			// The /> in an BXML file
	cs8						cgcColon[]								= ":";			// The :  in attributes, as in "attributeName:5=12345"
	cs8						cgcColonColon[]							= "::";			// The :: in the attributes, as in "attributeName::20"
	cs8						cgcEqual[]								= "=";			// The =  in attributes
	cs8						cgcCrLf[]								= "\015\012";	// The CR/LF combination

//////////
// Various macros
//////
	#define icommon_strlen(tcData)			icommon_scanForwardUntilCharacter(tcData, 0)
	#define defineCallback2(x, arg1, arg2) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													void	(CALLTYPE *callback_ ## x )( arg1, arg2 ); \
												};
	#define defineCallback4(x, arg1, arg2, arg3, arg4) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													void	(CALLTYPE *callback_ ## x )( arg1, arg2, arg3, arg4 ); \
												};
	#define defineCallback6(x, arg1, arg2, arg3, arg4, arg5, arg6) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													void	(CALLTYPE *callback_ ## x )( arg1, arg2, arg3, arg4, arg5, arg6 ); \
												};
	#define defineCallback7(x, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													void	(CALLTYPE *callback_ ## x )( arg1, arg2, arg3, arg4, arg5, arg6, arg7 ); \
												};
	#define defineCallback8(x, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													void	(CALLTYPE *callback_ ## x )( arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8 ); \
												};



//////////
// Universal structures
//////
struct SBxml;
struct SBxmla;

	struct SLL
	{
		union {
			SLL*		next;					// Next entry in linked list
			SBxmla*		bxmla;					// To allow viewing as a bxmla structure
		};
		SLL*			prev;					// Previous entry in linked list
		u64				uniqueId;				// Unique id associated with this object
	};

	struct SLL4
	{
		union {
			SLL4*		next;					// Next entry in a 4-way linked list for BXML
			SLL4*		east;					// Eastern entry in a 4-way linked list for nodes
			SBxml*		bxml;					// To allow viewing as a bxml structure
		};
		union {
			SLL4*		prev;					// Previous entry in a 4-way linked list for BXML
			SLL4*		west;					// Western entry in a 4-way linked list for nodes
		};

		u64				uniqueId;				// Unique id associated with this object

		// Note: The structure above is identical to SSL.  This is so that the standard facilities can be used on both SLL and SLL4 for normal next/prev navigation, with only special facilities being required for parent/child navigation
		union {
			SLL4*		parent;					// Parent entry in 4-way linked list for BXML
			SLL4*		north;					// Northern entry in a 4-way linked list for nodes
		};
		union {
			SLL4*		child;					// Child entry in 4-way linked list
			SLL4*		firstChild;				// First child entry in certain circumstances
			SLL4*		south;					// Southern entry in a 4-way linked list for nodes
		};
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

		SMasterList**	master;					// Every item in the start/end chain is appended here when created (used primarily for suspension and resumption of the VVM)
		u32				masterCount;			// Number of entries in the master array (used for resizing)

		// Not used and reserved for future use
		void*			extra;					// For future expansion
	};

	// Stores allocated data
	struct SDatum
	{
		csu8p			data;					// Pointer to start of data block
		u64				length;					// Length of data block
	};

	// Stores allocated data with a total length, and used length
	struct SDatum2
	{
		SDatum			datum;					// Data for this datum item
		u64				lengthTotal;			// Total length of the data block
	};

	// This structure does not contain allocated data, but rather a reference to some other data (which is derived in meaning by context)
	struct SRef
	{
		u32				start;					// A starting offset into something
		u32				length;					// Length of data block
	};

	struct SDatumLL
	{
		SLL				ll;						// 2-way link list
		SDatum			datum;					// Data stored there
	};

	struct SBitmapHeader
	{
		u16		type;							// Will be 'BM'
		u32		size;							// Total size of the entire file
		u16		reserved1;						// Unused
		u16		reserved2;						// Unused
		u32		offsetToBits;					// At what offset in the file do actual bits start?
	};

	struct SBitmapInfo
	{
		u32		sizeOfInfoBlock;				// Size of header (sizeof(SBitmapInfo))
		u32		width;							// Image width in pixels
		u32		height;							// Image height in pixels
		u16		planes;							// Planes (for 24-bit or 32-bit bitmap, will be 1)
		u16		bitCount;						// Bit count (24 or 32)
		union {
			u32	compression;					// For 24-bit or 32-bit bitmap, should be 0
			u32	actualWidth;					// Doubles as a post-load variable for the actual width
		};
		u32		sizeOfImage;					// Total size of image in bytes (height * actualWidth)
		u32		ppmX;							// Pixels per meter
		u32		ppmY;							// Pixels per meter
		u32		colorsUsed;						// Unused
		u32		colorsImportant;				// Unused
	};
	BITMAPINFOHEADER foo;


	struct SRGB
	{
		u8		blu;							// 24-bit RGB values in bitmap files are physically stored as BGR
		u8		grn;
		u8		red;
	};

	struct SRGBA
	{
		union {
			struct {
				u8		blu;
				u8		grn;
				u8		red;
				u8		alp;					// Alpha
			};
			int			color;					// RGBA color in integer form
		};
	};

	struct SRGBAF
	{
		f32		blu;				// 24-bit RGB values in bitmap files are physically stored as BGR
		f32		grn;
		f32		red;
		f32		alp;				// Alpha
		f32		area;				// Holds area
	};

	struct SStartEndCallback
	{
		union
		{
			u64		_iiCallbackFunction;
			bool	(*iiCallbackFunctionBool)	(void* ptr, u64 tnExtra);
			void	(*iiCallbackFunctionVoid)	(void* ptr, u64 tnExtra);
			//////
			// Uses the following format for the callback:
			//		bool iiCallbackFunction(void* ptr, u64 tnExtra)
			//////////
		};
	};

	struct SFileTime
	{
		s16		year;				// Year, positive=AD, negative=BC
		u8		month;				// 1=Jan, 12=Dec
		u8		day;				// 0..31
		u8		hour24;				// 0..23
		u8		hour;				// 0..12
		u8		minute;				// 0..59
		u8		second;				// 0..59
		u8		dayOfWeek;			// 1=Sunday, 7=Saturday
		u64		milliseconds;		// Milliseconds since midnight

		u32		epoch1970;			// Seconds since UNIX epoch (00:00:00 1970-01-01 UTC, will overflow in February 19, 2038)
		u64		epoch1601;			// 100-nanosecond intervals since 00:00:00 1601-01-01 (UTC)
	};



//////////
// Red,Grn,Blu,Alp color maker
//////
	#define rgba(r,g,b,a)					((a & 0xff) << 24) + \
											((r & 0xff) << 16) + \
											((g & 0xff) <<  8) + \
											((b & 0xff))

	#define rgb(r,g,b)						(0xff       << 24) + \
											((r & 0xff) << 16) + \
											((g & 0xff) <<  8) + \
											((b & 0xff))

	#define alp(rgbaColor)					((rgbaColor >> 24) & 0xff)
	#define red(rgbaColor)					((rgbaColor >> 16) & 0xff)
	#define grn(rgbaColor)					((rgbaColor >> 8)  & 0xff)
	#define blu(rgbaColor)					( rgbaColor        & 0xff)


//////////
// Common functions
//////
	u64					(CALLTYPE *vvm_debuggerInterface)						(s8* tcFunctionName);

	// Prototype definitions
	u8*					icommon_duplicateString									(u8* ptr, u64 length);
	w16*				icommon_duplicateUnicodeString							(w16* tuText);
	void				icommon_duplicateStringIntoDatum						(SDatum*  datum,  u8* ptr, u64 length,                  bool tlFreeExisting);
	void				icommon_duplicateStringIntoDatum2						(SDatum2* datum2, u8* ptr, u64 length, u64 totalLength, bool tlFreeExisting);
	void				icommon_duplicateDatum									(SDatum*  datumDst,  SDatum*  datumSrc);
	void				icommon_duplicateDatum2									(SDatum2* datum2Dst, SDatum2* datum2Src);
	void				icommon_deleteDatum										(SDatum*  datum);
	void				icommon_deleteDatum2									(SDatum2* datum2);
	void				icommon_allocateNullStringIntoDatum2					(SDatum2* datum2, u64 length, bool tlInitialize);
	void				icommon_copyUpToShortestString							(u8* dst, u32 tnDstLength, u8* src, u32 tnSrcLength);
	s32					icommon_wildcardMatch									(csu8p candidate, csu8p wildcardPattern, bool tlCaseSensitive);
	w16*				icommon_asciiToUnicode									(u8* tcText, u32 tnTextLength);
	s8*					icommon_unicodeToAscii									(w16* tuText, u32 tnTextLength);
	w16					icommon_asciiToUnicodeChar								(u8 tcChar);
	s8					icommon_unicodeToAsciiCharacter							(w16 tuChar);
	u64					icommon_scanForwardUntilCharacterChanges				(csu8p tcData, u64 tnMaxLength);
	u64					icommon_scanForwardUntilCharacter						(csu8p tcData, s8 c);
	int					icommon_unicodeMemcmp									(w16* l, w16* r, u32 tnLength);
	int					icommon_unicodeMemicmp									(w16* l, w16* r, u32 tnLength);
	int					icommon_unicodeMemset									(w16* p, w16 c, u32 tnLength);
	w16					icommon_upperCaseW										(w16 u);
	w16					icommon_lowerCaseW										(w16 u);
	void				icommon_memset											(s8* dst, s8 c, u64 tnCount);
	void				icommon_memset4											(u32* dst, u32 val, u64 tnCount);
	void				icommon_memcpy											(s8* dst, s8* src, u64 tnCount);
	s32					icommon_memcmp											(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
	s32					icommon_memicmp											(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount);
	s32					icommon_memicmpTwoLengths								(csu8p l/*eft*/, u64 tnLeftLength, csu8p r/*ight*/, u64 tnRightLength);
	s32					icommon_memicmpDatum									(SDatum*  datum,  csu8p r/*ight*/, u64 tnRightLength);
	s32					icommon_memicmpDatum2									(SDatum2* datum2, csu8p r/*ight*/, u64 tnRightLength);
	s32					icommon_memicmpDatumDatum								(SDatum*  datumL,  SDatum*  datumR);
	s32					icommon_memicmpDatum2Datum2								(SDatum2* datum2L, SDatum2* datum2R);
	void				icommon_deriveRGBA										(u32 tnColor, u8* tnRed, u8* tnGrn, u8* tnBlu, f32* tfAlp);

	bool				icommon_ll4_orphanizeAsBxml								(SLL4* bxml);
	bool				icommon_ll4_orphanizeAsNode								(SLL4* node);
	bool				icommon_ll4_insertAsBxml								(SLL4* bxml, SLL4* bxmlRef,                   bool tlAfter);
	bool				icommon_ll4_insertAsBxmlAsChild							(SLL4* bxml, SLL4* bxmlParent,                bool tlPrepend);
	bool				icommon_ll4_insertAsBxmlAsChildRegarding				(SLL4* bxml, SLL4* bxmlParent, SLL4* bxmlRef, bool tlAfter);
	bool				icommon_ll4_insertAsNodeNorthSouth						(SLL4* node, SLL4* nodeRef,                   bool tlAfter);
	bool				icommon_ll4_insertAsNodeEastWest						(SLL4* node, SLL4* nodeRef,                   bool tlAfter);

	void*				icommon_SEChain_prepend									(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*				icommon_SEChain_append									(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*				iicommon_SEChain_appendOrPrepend						(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult);
	void*				iicommon_SEChain_appendOrPrependExisting				(SStartEnd* ptrSE, SLL* ptrExisting, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult);
	void*				icommon_SEChain_appendRelativeToMember					(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize,     u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);
	void*				icommon_SEChain_appendExistingRelativeToMember			(SStartEnd* ptrSE, SLL* ptrRef,                 u64 tnUniqueIdExtra, SLL* ptrCaller, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult);
	void				iicommon_SEChain_appendMasterList						(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded);
	void				iicommon_SEChain_freeUpSlot								(SStartEnd* ptrSE, u32 tnSlot, u32 tnBlockSizeIfNewBlockNeeded);

	void*				icommon_SEChain_migrateAll								(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc);
	SMasterList*		icommon_SEChain_migrate									(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, void* ptr,    u32 tnHint, u32 tnBlockSize);
	SMasterList*		icommon_SEChain_migrate									(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);
	SLL*				icommon_SEChain_completelyMigrateSLL					(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr,     u32 tnHint, u32 tnBlockSize);
	SLL*				icommon_SEChain_completelyMigrateSLL					(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);

	u32					icommon_SEChain_countValids								(SStartEnd* ptrSE);
	u32					icommon_SEChain_delete									(SStartEnd* ptrSE, u64 tnCallback, u64 tnParam, bool tlDeletePointers);
	void				icommon_SEChain_deleteFrom								(SStartEnd* ptrSE, void* ptrDel, bool tlDeletePointers);
	bool				icommon_SEChain_deleteFromAfterCallback					(SStartEnd* ptrSE, bool tlDeletePointers, u64 iiCallbackFunction, u64 tnExtra);

	bool				icommon_allocateAdditionalStartEndMasterSlots			(SStartEnd* ptrSE, u32 tnBlockSize);
	void				iicommon_deleteFromStartEndChainMasterList				(SStartEnd* ptrSE, void* ptrDel);
	void*				icommon_searchStartEndChainByUniqueId					(SStartEnd* ptrSE, u64 tnUniqueId);
	void*				icommon_searchStartEndChainByCallback					(SStartEnd* ptrSE, u64 iiCallbackFunction, u64 tnExtra);
	void				icommon_iterateThroughStartEndForCallback				(SStartEnd* ptrSE, u64 iiCallbackFunction, u64 tnExtra);
	void				icommon_validateStartEnd								(SStartEnd* ptrSE, u64 iiCallbackFunction);
	u32					icommon_swapEndian										(u32 tnValue);
	u32					icommon_RGBA2BGRA										(u32 tnColor);
	void*				icommon_allocateAndNull									(u32 tnSize, bool tnInitToZeros);
	bool				icommon_isNeedleInHaystack								(csu8p tcHaystack, s32 tnHaystackLength, csu8p tcNeedle, s32 tnNeedleLength, bool tlCaseSensitive, u32* tnFoundPosition);
	bool				icommon_isNeedleInHaystack_Unicode						(w16* twHaystack, w16* twNeedle);
	u32					icommon_countConsecutiveAsciiNumericDigits				(s8* buffer, u32 tnMaxLength);
	u32					icommon_convertTextToU32								(s8* tcNumbers, u32 tnMaxLength);




//////////
//
// Note: All of these are called from the window's message thread.
//       Each one should raise flags or copy whatever data is necessary
//       to some external areas for a post-return respond in another thread.
//
//////

	struct SOssWindow;

	// Generic callbacks
	struct SCallbacks
	{
		// If a semaphore exists for any defined callback (it is non-NULL),
		// it is locked immediately before,
		// and unlocked immediately after, example:  u64 semaphore_x;
		defineCallback2( windowCreated,		u64 tnUniqueId, SOssWindow* tisw)																					// Called after window is created, before it is displayed
		defineCallback2( windowUnload,		u64 tnUniqueId, SOssWindow* tisw)																					// Called when a window will be closed, while everything related to it is still viable
		defineCallback2( windowClosed,		u64 tnUniqueId, SOssWindow* tisw)																					// Called after a window has been destroyed, before it is released by VVMOSS's internal lists of known windows
		defineCallback4( windowMoved,		u64 tnUniqueId, SOssWindow* tisw, u32 tnXNew, u32 tnYNew)															// After a window has been moved from one place to another (not while it is moving)
		defineCallback4( windowResized,		u64 tnUniqueId, SOssWindow* tisw, u32 tnWidthNew, u32 tnHeightNew)													// After a window has been resized, and the buffers related to its screen have been allocated
		defineCallback2( windowGotFocus,	u64 tnUniqueId, SOssWindow* tisw)																					// After a window has received focus, and after the window that lost focus (if any) has been signaled
		defineCallback2( windowLostFocus,	u64 tnUniqueId, SOssWindow* tisw)																					// Before a new window receives focus
		defineCallback6( mouseDown,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)										// When a mouse button is pressed down
		defineCallback6( mouseUp,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)										// When a mouse button is released
		defineCallback6( mouseMove,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)										// When a mouse is moved either with its buttons down or up
		defineCallback8( mouseHover,		u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)	// When a mouse has positioned itself at a fixed location for a period of time after previously moving
		defineCallback6( keyDown,			u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)								// When a key is pressed down, or when the OS sends repeated keystrokes if it is a repeating key which is held down
		defineCallback6( keyUp,				u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)								// When a key is released
		defineCallback6( keyPress,			u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)								// When a key is pressed and interpreted to a known key
		defineCallback4( keyFlags,			u64 tnUniqueId, SOssWindow* tisw, u32 tnKeyFlagsOld, u32 tnKeyFlagsNew)												// When keyboard flags change (such as a non-printable key going up and down, like shift, caps lock, or control)
		defineCallback6( dragStart,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)										// When any mouse button has been depressed and the mouse has moved more than a minimal number of pixels
		defineCallback7( dragging,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds)					// Called as each MouseMove event while dragging
		defineCallback7( dragDrop,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds)					// Called when the mouse button initiating the drag is released
		defineCallback4( custom,			u64 tnUniqueId, SOssWindow* tisw, u64 tnCustomEventId, u64 tnOtherData)												// Called when to when a custom event is triggered programmatically
	};


	// Body functions
	u8* icommon_duplicateString(u8* ptr, u64 length)
	{
		u8* ptrNew;


		// Make sure our environment is sane
		ptrNew = NULL;
		if (ptr && length < 0xffffffff)
		{
			// Try to create the new string
			ptrNew = (u8*)malloc((u32)length + 1);

			//  Copy the string if successful
			if (ptrNew)
			{
				// Copy the string and null-terminate it
				memcpy(ptrNew, ptr, (u32)length);
				ptrNew[(u32)length] = 0;
			}
		}
		// All done
		return(ptrNew);
	}




	// Duplicate the unicode string
	w16* icommon_duplicateUnicodeString(w16* tuText)
	{
		u32		tnLength;
		w16*	tuNewText;


		// Make sure our environment is sane
		tuNewText = NULL;
		if (tuText)
		{
			// Get the length
			tnLength = wcslen(tuText) * sizeof(w16);

			// Allocate that much space
			tuNewText = (w16*)malloc(tnLength);

			// If we're good, complete the copy
			if (tuNewText)
				memcpy(tuNewText, tuText, tnLength);
		}
		// Indicate our status
		return(tuNewText);
	}




	// Duplicate and store to a datum structure
	void icommon_duplicateStringIntoDatum(SDatum* datum, u8* ptr, u64 length, bool tlFreeExisting)
	{
		u8* lptr;


		// Make sure our environment is sane
		if (datum)
		{
			if (length != 0)
			{
				// If there is already a value here, free it up
				if (tlFreeExisting && datum->data._u8)
				{
					// Grab the pointer
					lptr				= datum->data._u8;

					// Indicate it is NULL in the structure (in case a task switch happens right now)
					datum->data._u8		= NULL;
					datum->length		= 0;

					// Release the allocated memory
					free(lptr);
				}

				if (ptr)
				{
					// Duplicate the string
					datum->data._u8 = icommon_duplicateString(ptr, length);

				} else {
					// Create a blank string and initialize it to NULLs
					datum->data._u8 = (u8*)malloc((u32)length);
					if (datum->data._u8)
						memset(datum->data._u8, 0, (u32)length);
				}

				// Verify our string was allocated properly
				if (datum->data._u8)	datum->length = length;
				else					datum->length = 0;

			} else {
				// Initialize it to NULL
				datum->data._u8		= NULL;
				datum->length		= 0;
			}
		}
	}



	// Duplicate and store to a datum2 structure
	void icommon_duplicateStringIntoDatum2(SDatum2* datum2, u8* ptr, u64 length, u64 lengthTotal, bool tlFreeExisting)
	{
		// Make sure our environment is sane
		if (datum2)
		{
			if (length != 0)
			{
				// Duplicate the datum string
				icommon_duplicateStringIntoDatum(&datum2->datum, ptr, length, tlFreeExisting);

				// Update our totals if the string was allocated appropriately
				if (datum2->datum.data._u8)
				{
					// We allocated and copied correctly
					datum2->lengthTotal	= lengthTotal;

				} else {
					// We did not, so this string is not valid
					datum2->lengthTotal	= 0;
				}

			} else {
				// They are clearing out whatever is already there
				icommon_deleteDatum(&datum2->datum);

				// Initialize it to NULL
				datum2->lengthTotal	= lengthTotal;
			}
		}
	}




	void icommon_duplicateDatum(SDatum* datumDst, SDatum* datumSrc)
	{
		// Make sure our environment is sane
		if (datumDst && datumSrc && datumSrc->data._u8 && datumSrc->length != 0)
		{
			// If it's already populated, release it
			if (datumDst->data._u8)
				free(datumDst->data._u8);

			// Copy the item
			datumDst->data._u8 = icommon_duplicateString(datumSrc->data._u8, datumSrc->length);

			// If it was copied, update the length
			if (datumDst->data._u8)		datumDst->length	= datumSrc->length;
			else						datumDst->length	= 0;
		}
	}




	void icommon_duplicateDatum2(SDatum2* datum2Dst, SDatum2* datum2Src)
	{
		// Make sure our environment is sane
		if (datum2Dst && datum2Src && datum2Src->datum.data._u8 && datum2Src->datum.length != 0)
		{
			// If it's already populated, release it
			if (datum2Dst->datum.data._u8)
				free(datum2Dst->datum.data._u8);

			// Copy the item
			datum2Dst->datum.data._u8 = icommon_duplicateString(datum2Src->datum.data._u8, datum2Src->datum.length);

			// If it was copied, update the length
			if (datum2Dst->datum.data._u8)
			{
				// Success
				datum2Dst->datum.length		= datum2Src->datum.length;
				datum2Dst->lengthTotal		= datum2Src->lengthTotal;

			} else {
				// Failure
				datum2Dst->datum.length		= 0;
				datum2Dst->lengthTotal		= 0;
			}
		}
	}




	void icommon_deleteDatum(SDatum* datum)
	{
		if (datum)
		{
			if (datum->data._u8)
			{
				// Free the memory
				free(datum->data._u8);

				// Reset the datum structure
				datum->data._u8 = NULL;
			}

			// Reset the length
			datum->length = 0;
		}
	}




	void icommon_deleteDatum2(SDatum2* datum2)
	{
		if (datum2 && datum2->datum.data._u8)
		{
			// Free the memory
			icommon_deleteDatum(&datum2->datum);

			// Reset the datum2 total size
			datum2->lengthTotal	= 0;
		}
	}




	void icommon_allocateNullStringIntoDatum2(SDatum2* datum2, u64 length, bool tlInitialize)

	{
		// Make sure our environment is sane
		if (datum2)
		{
			if (length != 0)
			{
				// Create the string space
				datum2->datum.data._u8 = (u8*)malloc((u32)length);		// Note:  This function does not automatically allocate the trailing NULL as the iDuplicateStringIntoDatum() function does
				if (datum2->datum.data._u8)
				{
					// We're good, set up the length
					datum2->datum.length	= length;
					datum2->lengthTotal		= length;

					// Set it to NULLs if we need to
					if (tlInitialize)
						memset(datum2->datum.data._u8, 0, (u32)length);

				} else {
					// Store the length value of 0
					datum2->datum.length	= 0;
					datum2->lengthTotal		= 0;
				}

			} else {
				// Initialize it to NULL
				datum2->datum.data._u8		= NULL;
				datum2->datum.length		= 0;
				datum2->lengthTotal			= 0;
			}
		}
	}




	void icommon_copyUpToShortestString(u8* dst, u32 tnDstLength, u8* src, u32 tnSrcLength)
	{
		u32 lnI;


		// Copy as many characters as are allowed
		for (lnI = 0; lnI < tnDstLength && lnI < tnSrcLength; lnI++)
			dst[lnI] = src[lnI];
	}




	w16* icommon_asciiToUnicode(u8* tcText, u32 tnTextLength)
	{
		u32		lnI;
		w16*	luOut;


		// Allocate 2 bytes for every ascii byte, plus 2 more for the trailing s16 null
		luOut = (w16*)malloc((tnTextLength * 2) + 2);
		if (luOut)
		{
			// Convert to 16-bit forms
			for (lnI = 0; lnI < tnTextLength; lnI++)
				luOut[lnI] = (w16)tcText[lnI];

			// Append an extra trailing null
			luOut[lnI] = 0;
		}
		return(luOut);
	}




	s8* icommon_unicodeToAscii(w16* tuText, u32 tnTextLength)
	{
		u32		lnI;
		s8*		lcOut;


		// Allocate 2 bytes for every ascii byte, plus 2 more for the trailing s16 null
		lcOut = (s8*)malloc(tnTextLength + 1);
		if (lcOut)
		{
			// Convert to 16-bit forms
			for (lnI = 0; lnI < tnTextLength; lnI++)
				lcOut[lnI] = (s8)tuText[lnI];

			// Append an extra trailing null
			lcOut[lnI] = 0;
		}
		return(lcOut);
	}




	w16 icommon_asciiToUnicodeChar(u8 tcChar)
	{
		return((w16)tcChar);
	}




	s8 icommon_unicodeToAsciiCharacter(w16 tuChar)
	{
		return((s8)tuChar);
	}




	u64 icommon_scanForwardUntilCharacterChanges(csu8p tcData, u64 tnMaxLength)
	{
		u64 lnI;


		// Make sure our environment is sane
		lnI = 0;
		if (tcData._cu8 && tnMaxLength != 0)
		{
			// Continue comparing every character
			for (++lnI; lnI < tnMaxLength; lnI++)
			{
				// If the character changes, we're done
				if (tcData._cu8[lnI] != tcData._cu8[0])
					return(lnI);		// We're done
			}
		}
		// When we get here, lnI is how far we skipped
		return(lnI);
	}




	u64 icommon_scanForwardUntilCharacter(csu8p tcData, s8 c)
	{
		u64 lnI;


		// Scan through the data
		lnI = 0;
		if (tcData._cu8)
		{
			for ( ; tcData._cu8[lnI] != c; )
				++lnI;
		}
		// Indicate our length
		return(lnI);
	}




	int icommon_unicodeMemcmp(w16* l, w16* r, u32 tnLength)
	{
		u32 lnI;


		// For every character in the length, compare left to right
		for (lnI = 0; lnI < tnLength; lnI++)
		{
			if (l[lnI] != r[lnI])
			{
				if (l[lnI] < r[lnI])
					return -1;		// Left is less than right
				return 1;			// Left is greater than right
			}
		}
		// They're equal
		return 0;
	}




	int icommon_unicodeMemicmp(w16* l, w16* r, u32 tnLength)
	{
		w16		ll, rl;		// Left- and right-lower
		u32		lnI;


		// For every character in the length, compare left to right
		for (lnI = 0; lnI < tnLength; lnI++)
		{
			ll = icommon_lowerCaseW(l[lnI]);
			rl = icommon_lowerCaseW(r[lnI]);
			if (ll != rl)
			{
				if (ll < rl)
					return -1;		// Left is less than right
				return 1;			// Left is greater than right
			}
		}
		// They're equal
		return 0;
	}




	int icommon_unicodeMemset(w16* p, w16 uc, u32 tnLength)
	{
		u32 lnI;


		// Make sure the environment is sane
		lnI = 0;
		if (p)
		{
			// For the indicated length, stick the indicated unicode character in there
			for (; lnI < tnLength; lnI++)
				p[lnI + lnI] = uc;
		}

		// Indicate the number of characters we processed
		return(lnI);
	}




	w16 icommon_upperCaseW(w16 u)
	{
		s8 c;
// TODO:  (unicode) foreign languages will need to have other tests here

		// See if it's a lower-case character in ASCII
		c = (s8)u;
		if (c >= 'a' && c <= 'z')
			return((w16)(c - 0x20));		// It is, convert to upper-case

		// If we get here, we're good as we are
		return(u);
	}




	w16 icommon_lowerCaseW(w16 u)
	{
		s8 c;
// TODO:  (unicode) foreign languages will need to have other tests here


		// See if it's a lower-case character in ASCII
		c = (s8)u;
		if (c >= 'A' && c <= 'Z')
			return((w16)(c + 0x20));		// It is, convert to lower-case

		// If we get here, we're good as we are
		return(u);
	}




	void icommon_memset(s8* dst, s8 c, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (dst)
		{
			// Iterate for every indicated character
			for (lnI = 0; lnI < tnCount; lnI++)
				dst[lnI] = c;
		}
	}




	void icommon_memset4(u32* dst, u32 val, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (dst)
		{
			// Iterate for every indicated dword
			for (lnI = 0; lnI < tnCount; lnI++)
				dst[lnI] = val;
		}
	}




	void icommon_memcpy(s8* dst, s8* src, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (dst && src)
		{
			// Copy everything
			for (lnI = 0; lnI < tnCount; lnI++)
				dst[lnI] = src[lnI];
		}
	}




	s32 icommon_memcmp(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount)
	{
		u64 lnI;


		// Make sure our environment is sane
		if (l._cu8 && r._cu8)
		{
			for (lnI = 0; lnI < tnCount; lnI++)
			{
				if (l._cu8[lnI] != r._cu8[lnI])
				{
					if (l._cu8[lnI] < r._cu8[lnI])		return(-1);		// left is less than right
					else								return(1);		// left is greater than right
				}
				// Still good, keep going
			}
			// When we get here, they're equal
			return(0);
		}
		// Invalid configuration
		return(-2);
	}




	s32 icommon_memicmp(csu8p l/*eft*/, csu8p r/*ight*/, u64 tnCount)
	{
		u64		lnI;
		u8		cl, cr;


		// Make sure our environment is sane
		if (l._cu8 && r._cu8 && tnCount != 0)
		{
			for (lnI = 0; lnI < tnCount; lnI++)
			{
				// Grab the bytes
				cl = l._cu8[lnI];
				cr = r._cu8[lnI];

				// Ignore case
				if (cl >= 'A' && cl <= 'Z')		cl |= 0x20;
				if (cr >= 'A' && cr <= 'Z')		cr |= 0x20;

				if (cl != cr)
				{
					if (cl < cr)		return(-1);		// left is less than right
					else				return(1);		// left is greater than right
				}
				// Still good, keep going
			}
			// When we get here, they're equal
			return(0);
		}
		// Invalid configuration
		return(-2);
	}




	s32 icommon_memicmpTwoLengths(csu8p l/*eft*/, u64 tnLeftLength, csu8p r/*ight*/, u64 tnRightLength)
	{
		u64		lnI;
		u8		cl, cr;


		// Make sure our environment is sane
		if (l._cu8 && r._cu8 && tnLeftLength != 0 && tnRightLength != 0)
		{
			for (lnI = 0; lnI < tnLeftLength && lnI < tnRightLength; lnI++)
			{
				// Grab the bytes
				cl = l._cu8[lnI];
				cr = r._cu8[lnI];

				// Ignore case
				if (cl >= 'A' && cl <= 'Z')		cl |= 0x20;
				if (cr >= 'A' && cr <= 'Z')		cr |= 0x20;

				if (cl != cr)
				{
					if (cl < cr)		return(-1);		// left is less than right
					else				return(1);		// left is greater than right
				}
				// Still good, keep going
			}
			// When we get here, they're equal
			if (tnLeftLength == tnRightLength)
				return(0);		// They're equal

			// If we get here, they're different lengths, so based on whichever one is shorter, return that result
			if (tnRightLength >= tnLeftLength)		return(1);		// Left is shorter
			else									return(-1);		// Right is shorter
		}
		// Invalid configuration
		return(-2);
	}




	s32 icommon_memicmpDatum(SDatum* datum, csu8p r/*ight*/, u64 tnRightLength)
	{
		// Make sure our environment is sane
		if (datum && r._cu8 && tnRightLength != 0 && datum->length != 0)
			return(icommon_memicmpTwoLengths(datum->data, datum->length, r, tnRightLength));

		// If we get here, failure
		return(-2);
	}




	s32 icommon_memicmpDatum2(SDatum2* datum2, csu8p r/*ight*/, u64 tnRightLength)
	{
		// Make sure our environment is sane
		if (datum2 && r._cu8 && tnRightLength != 0 && datum2->datum.length != 0)
			return(icommon_memicmpTwoLengths(datum2->datum.data, datum2->datum.length, r, tnRightLength));

		// If we get here, failure
		return(-2);
	}




	s32 icommon_memicmpDatumDatum(SDatum* datumL, SDatum* datumR)
	{
		if (datumL && datumR)
			return(icommon_memicmpTwoLengths(datumL->data, datumL->length, datumR->data, datumR->length));

		// If we get here, failure
		return(-2);
	}




	s32 icommon_memicmpDatum2Datum2(SDatum2* datum2L, SDatum2* datum2R)
	{
		if (datum2L && datum2R)
			return(icommon_memicmpTwoLengths(datum2L->datum.data, datum2L->datum.length, datum2R->datum.data, datum2R->datum.length));

		// If we get here, failure
		return(-2);
	}




	inline void icommon_deriveRGBA(u32 tnColor, u8* tnRed, u8* tnGrn, u8* tnBlu, f32* tfAlp)
	{
		*tnRed = red(tnColor);
		*tnGrn = grn(tnColor);
		*tnBlu = blu(tnColor);
		*tfAlp = (f32)(alp(tnColor)) / 255.0f;
	}




//////////
//
// Disconnects an SLL4 structure from either an BXML or a traditional node configuration.
// LL4 entries go off in four directions, toward siblings (prev/next), and toward parents
// and children.  These can be thought of as the cardinal directions as well (north/east/
// south/west).
//
//////
	// Note:  The common code itself knows nothing about SBxml structure formally, but it
	//        has at its header the SLL4 structure, which it does know about.
	//
	// In SBxml structures, we always update siblings, but if we have no previous entry,
	// then we must make the parent (if any) point to our next sibling, and we always
	// keep the children (for they are indeed most important!) :-)
	bool icommon_ll4_orphanizeAsBxml(SLL4* bxml)
	{
		bool	llResult;


// TODO:  tested code working properly, but not tested thoroughly enough
		// Make sure our environment is sane
		llResult = false;
		if (bxml)
		{
			// We have something to work with, but of what caliber is it?
			// Should we accept it on its word that it is a good bxml and not being merely deceptive so as to harm our system? :-)

			// Update its elements if any
			// See if this is the first child
			if (!bxml->prev && bxml->parent)
				bxml->parent->child = bxml->next;		// This is the first item, so our parent must now point to our next sibling

			// Disconnect this node from its siblings
			if (bxml->next)		bxml->next->prev = bxml->prev;
			if (bxml->prev)		bxml->prev->next = bxml->next;

			// When we get here, this node has been made an orphan
			// Let it now believe so
			bxml->parent	= NULL;
			bxml->next		= NULL;
			bxml->prev		= NULL;
			// Note:  It will still keep its children

			// If we get here, we were good
			llResult = true;
		}
		// Indicate our status
		return(llResult);
	}

	// In nodes, we always update north/south paths, as well as east/west paths, as the node is
	// just a point on a mesh or clutter mesh.
	bool icommon_ll4_orphanizeAsNode(SLL4* node)
	{
		bool llResult;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (node)
		{
			// Disconnect this node in/from the four cardinal directions
			if (node->north)	node->north->south = node->south;		// It points to an entry above itself
			if (node->south)	node->south->north = node->north;		// It points to an entry below itself
			if (node->east)		node->east->west = node->west;			// It points to an entry to the right
			if (node->west)		node->west->east = node->east;			// It points to an entry to the left

			// Update the node to reflects its new orphaned status
			node->north		= NULL;
			node->south		= NULL;
			node->east		= NULL;
			node->west		= NULL;
		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// Called to insert the indicated node where it should go
//
//////
	// Inserts only as a sibling, either before or after the reference bxml
	bool icommon_ll4_insertAsBxml(SLL4* bxml, SLL4* bxmlRef, bool tlAfter)
	{
		bool	llResult;
		SLL4*	bxmlNext;
		SLL4*	bxmlPrev;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment's sane
		if (bxml && bxmlRef)
		{
			// Only success at this point. :-)
			llResult = true;

			// Are we inserting before or after?
			if (tlAfter)
			{
				// We're inserting this one AFTER the reference bxml
				bxmlNext		= bxmlRef->next;			// Grab the original next

				// Going between BxmlRef and BxmlNext
				bxml->prev		= bxmlRef;					// The one we're inserting points back to the reference
				bxml->next		= bxmlNext;					// The one we're inserting points forward to what used to be the next
				bxmlRef->next	= bxml;						// The reference points forward to the one we're inserting

				// Update the other one that's out there, you know, "on the other side"
				if (bxmlNext)
					bxmlNext->prev = bxml;					// The original next now points backward to the one we're inserting

			} else {
				// We're inserting this one BEFORE the reference bxml
				bxmlPrev		= bxmlRef->prev;			// Grab original previous

				// Going between BxmlPrev and BxmlRef
				bxml->prev		= bxmlPrev;					// The one we're inserting before points back to the original previous
				bxml->next		= bxmlRef;					// The one we're inserting before points forward to the reference
				bxmlRef->prev	= bxml;						// The reference points back to the one we're inserting before
				if (bxmlPrev)
					bxmlPrev->next = bxml;					// The previous points forward to the one we're inserting

				// Was this the first item we just inserted before?
				if (bxmlRef->parent && bxmlRef->parent->firstChild == bxmlRef)
				{
					// Yes, it needs to now point to the new item
					bxmlRef->parent->firstChild = bxml;
				}
			}

		} else {
			// Failure on parameters
			llResult = false;
		}

		// Indicate our status
		return(llResult);
	}

	// Positions the element as a child either at the start (faster) or end (slower)
	bool icommon_ll4_insertAsBxmlAsChild(SLL4* bxml, SLL4* bxmlParent, bool tlAfter)
	{
		bool	llResult;
		SLL4*	bxmlRunner;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment's sane
		if (bxml && bxmlParent)
		{
			// Only success at this point
			llResult = true;

			// Before or after?
			if (tlAfter)
			{
				// Going to the tail
				if (bxmlParent->child)
				{
					// We need to iterate to the end
					bxmlRunner = bxmlParent->child;
					while (bxmlRunner->next)
						bxmlRunner = bxmlRunner->next;

					// When we get here, we have the last child
					bxmlRunner->next		= bxml;
					bxml->prev				= bxmlRunner;

				} else {
					// First child
					bxmlParent->firstChild	= bxml;
					bxml->prev				= NULL;
				}
				// Nothing point after
				bxml->next = NULL;

			} else {
				// Going to the start
				if (bxmlParent->child)
					bxml->next = bxmlParent->child;		// There is already a child, make sure this new one points to that child

				// Update the parent to point to its new first child
				bxmlParent->firstChild		= bxml;

				// Nothing pointing before
				bxml->prev					= NULL;
			}
			// If we get here, we're good
			llResult = true;

		} else {
			// Invalid parameters
			llResult = false;
		}

		// Indicate our status
		return(llResult);
	}

	// Positions the element relative to the bxml reference, either before or after, and
	// therefore "regarding" it.
	bool icommon_ll4_insertAsBxmlAsChildRegarding(SLL4* bxml, SLL4* bxmlParent, SLL4* BxmlRef, bool tlAfter)
	{
		bool	llResult;
		SLL4*	BxmlNext;
		SLL4*	BxmlPrev;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (bxml && bxmlParent && BxmlRef)
		{
			if (tlAfter)
			{
				// It's going AFTER the reference entry
				if (BxmlRef->next)
				{
					// There IS an entry after this one
					// bxml is going between BxmlRef and BxmlNext
					BxmlNext = BxmlRef->next;

					// Insert the node
					bxml->prev			= BxmlRef;
					bxml->next			= BxmlNext;
					BxmlRef->next		= bxml;
					BxmlNext->prev		= bxml;

				} else {
					// BxmlRef is the last entry
					BxmlRef->next		= bxml;
					bxml->prev			= BxmlRef;
					bxml->next			= NULL;
				}

			} else {
				// It's going BEFORE the reference entry
				if (BxmlRef->prev)
				{
					// There IS an entry before this one
					BxmlPrev = BxmlRef->prev;
					// This is going between BxmlPrev and BxmlRef
					bxml->prev				= BxmlPrev;
					bxml->next				= BxmlRef;
					BxmlPrev->next			= bxml;
					BxmlRef->prev			= bxml;

				} else {
					// xmlRef is the first entry
					bxml->prev				= NULL;
					bxml->next				= BxmlRef;
					bxmlParent->firstChild	= bxml;
					BxmlRef->prev			= bxml;
				}
			}
			// Update the pointer to point back up to its new parent.
			bxml->parent = bxmlParent;

			// Success
			llResult = true;
		}
		// Indicate our status
		return(llResult);
	}

	// Inserts the node before or after the indicated node
	bool icommon_ll4_insertAsNodeNorthSouth(SLL4* node, SLL4* nodeRef, bool tlAfter)
	{
		bool	llResult;
		SLL4*	nodePrev;
		SLL4*	nodeNext;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (node && nodeRef)
		{
			if (tlAfter)
			{
				// node is going after nodeRef
				if (nodeRef->south)
				{
					// There is an entry after nodeRef, so we insert it between nodeRef and nodeRef->next
					nodeNext		= nodeRef->next;

					// Update nodeRef to point to this one
					node->next		= nodeRef->next;
					nodeRef->next	= node;

					// Update nodeNext to point back to this one
					node->prev		= nodeNext->prev;
					nodeNext->prev	= node;

				} else {
					// There is no entry after nodeRef, so we just put it after
					nodeRef->south	= node;
					node->north		= nodeRef;
					node->south		= NULL;				// Make sure this entry is not hooked up otherwise
				}

			} else {
				// node is going before nodeRef
				if (nodeRef->north)
				{
					// There is an entry before nodeRef, so we insert it between nodeRef and nodeRef->prev
					nodePrev		= nodeRef->next;

					// Update nodeRef to point to this one
					node->prev		= nodeRef->prev;
					nodeRef->prev	= node;

					// Update nodePrev to point forward to this one
					node->next		= nodeRef;
					nodePrev->next	= node;

				} else {
					// There is no entry before nodeRef, so we just put it before
					nodeRef->north	= node;
					node->south		= nodeRef;
					node->north		= NULL;				// Make sure this entry is not hooked up otherwise
				}
			}
		}
		// Indicate our status
		return(llResult);
	}

	// Inserts the node before or after the indicated node
	bool icommon_ll4_insertAsNodeEastWest(SLL4* node, SLL4* nodeRef, bool tlAfter)
	{
		bool	llResult;
		SLL4*	nodeWest;
		SLL4*	nodeEast;


// TODO:  untested code, breakpoint and examine
		// Make sure our environment is sane
		llResult = false;
		if (node && nodeRef)
		{
			if (tlAfter)
			{
				// node is going after (east) nodeRef
				if (nodeRef->east)
				{
					// There is an entry after nodeRef, so we insert it between nodeRef and nodeRef->next
					nodeEast		= nodeRef->east;

					// Update nodeRef to point to this one
					node->east		= nodeRef->east;
					nodeRef->east	= node;

					// Update nodeNext to point back to this one
					node->west		= nodeEast->west;
					nodeEast->west	= node;

				} else {
					// There is no entry after nodeRef, so we just put it after
					nodeRef->south	= node;
					node->north		= nodeRef;
					node->south		= NULL;				// Make sure this entry is not hooked up otherwise
				}

			} else {
				// node is going before (west) nodeRef
				if (nodeRef->north)
				{
					// There is an entry before nodeRef, so we insert it between nodeRef and nodeRef->west
					nodeWest		= nodeRef->east;

					// Update nodeRef to point to this one
					node->west		= nodeRef->west;
					nodeRef->west	= node;

					// Update nodePrev to point forward to this one
					node->east		= nodeRef;
					nodeWest->east	= node;

				} else {
					// There is no entry before nodeRef, so we just put it before
					nodeRef->north	= node;
					node->south		= nodeRef;
					node->north		= NULL;				// Make sure this entry is not hooked up otherwise
				}
			}
		}
		// Indicate our status
		return(llResult);
	}




//////////
//
// Append a new record of indicated size to the start/end chain
//
// Returns:
//		NULL		- If error
//		other		- A pointer to the new object
//
// Note:  Initializes memory block of tnSize to NULLs upon successful allocation
//
//////
	void* icommon_SEChain_prepend(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(iicommon_SEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, true, tlResult));
	}

	void* icommon_SEChain_append(SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult)
	{
		return(iicommon_SEChain_appendOrPrepend(ptrSE, tnUniqueId, tnUniqueIdExtra, tnSize, tnBlockSizeIfNewBlockNeeded, false, tlResult));
	}

	// Prepends or appends to the Start/end chain
	void* iicommon_SEChain_appendOrPrepend (SStartEnd* ptrSE, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult)
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
					iicommon_SEChain_appendMasterList(ptrSE, ptrNew, 0, tnBlockSizeIfNewBlockNeeded);

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




	// Appends or prepends an existing (already allocated) orphan pointer to the indicated Start/end list
	void* iicommon_SEChain_appendOrPrependExisting(SStartEnd* ptrSE, SLL* ptrExisting, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult)
	{
		SMasterList*	ptrNew;
		SMasterList*	ptrPrev;
		SMasterList**	prev;


// TODO:  untested code, breakpoint and examine
// Note:  This code has been tested, but it is truly essential to operations of the VVM, and needs thoroughly tested many, many, many times. :-)
		// See where we are
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
				// Store the memory variable for the caller memory block
				ptrNew->ptr			= ptrExisting;

				// Update the back-link
				*prev				= ptrNew;

				// Update the other part of the back link
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
				iicommon_SEChain_appendMasterList(ptrSE, ptrNew, 0, tnBlockSizeIfNewBlockNeeded);
				// All done!

				// Indicate our success
				return(ptrExisting);
			}
		}
		// Indicate our failure
		return(NULL);
	}




	// Appends an entry relative to the indicated SMasterList* member (either before or after the entry)
	void* icommon_SEChain_appendRelativeToMember(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueId, u64 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult)
	{
		SLL* ptrCaller;


		// See where we are
		if (ptrSE)
		{
			if (!ptrSE->root)
				return(NULL);		// There are no entries, so we can't be adding relative to the reference pointer

			// Create the new caller structure
			ptrCaller = (SLL*)malloc(tnSize);
			if (ptrCaller)
			{
				// Initialize the structure
				memset(ptrCaller, 0, tnSize);

				// Indicate its unique ID
				ptrCaller->uniqueId	= tnUniqueId;

				// Append the now existing pointer
				return(icommon_SEChain_appendExistingRelativeToMember(ptrSE, ptrRef, tnUniqueIdExtra, ptrCaller, tnBlockSizeIfNewBlockNeeded, tlAfter, tlResult));
			}
		}
		// If we get here, error
		return(NULL);
	}

	void* icommon_SEChain_appendExistingRelativeToMember(SStartEnd* ptrSE, SLL* ptrRef, u64 tnUniqueIdExtra, SLL* ptrCaller, u32 tnBlockSizeIfNewBlockNeeded, bool tlAfter, bool* tlResult)
	{
		u32				lnI, lnHint;
		bool			llFound;
		SMasterList*	lmlNew;


		// See where we are
// TODO:  untested code, breakpoint and examine
// Note:  This code has been tested, but it is truly essential to operations of the VVM, and needs thoroughly tested
		if (ptrSE)
		{
			if (!ptrSE->root)
				return(NULL);		// There are no entries, so we can't be adding relative to the reference pointer

			// Locate the indicated reference in this list
			llFound = false;
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				if (ptrSE->master[lnI]->used && ptrSE->master[lnI]->ptr == ptrRef)
				{
					// We found our match
					if (tlAfter)		lnHint = lnI + 1;		// Should go after
					else				lnHint = lnI;			// Should go before, which means where the current entry was found

					// Make sure there's room
					iicommon_SEChain_freeUpSlot(ptrSE, lnHint, tnBlockSizeIfNewBlockNeeded);

					// Continue to insert this item
					llFound = true;
					break;
				}
			}

			// See if we found our entry
			if (!llFound)
				return(NULL);		// The indicated ptrRef was not found as a member of this Start/End list

			// When we get here, we have the relative of where the new entry will go

			// Allocate for our SMasterList pointer
			lmlNew = (SMasterList*)malloc(sizeof(SMasterList));
			if (lmlNew)
			{
				// We have our new pointer, initialize the structure
				memset(lmlNew, 0, sizeof(SMasterList));

				// Store the data
				lmlNew->ll.uniqueId	= tnUniqueIdExtra;
				lmlNew->ptr			= ptrCaller;

				// Store it in the master list (so when VM is suspended, this data gets saved)
				iicommon_SEChain_appendMasterList(ptrSE, lmlNew, lnHint, tnBlockSizeIfNewBlockNeeded);


				///////////
				// Adjust this item relative to its ptrRef
				//////
					if (tlAfter)
					{
						// ptrNew goes after ptrRef
						ptrCaller->prev		= ptrRef;			// New one points backward to reference
						ptrCaller->next		= ptrRef->next;		// New one points forward to what reference used to point to
						ptrRef->next		= ptrCaller;		// Reference points forward to thew new one

						// Update the one after where reference used to be
						if (ptrCaller->next)
							ptrCaller->next->prev = ptrCaller;	// One originally after reference points backward to new one

					} else {
						// ptrNew goes before ptrRef
						ptrCaller->next		= ptrRef;			// New one points forward to what reference
						ptrCaller->prev		= ptrRef->prev;		// New one points backward to what reference used to point backward to
						ptrRef->prev		= ptrCaller;		// Reference points backward to the new one

						// Update the one before where reference used to be
						if (ptrCaller->prev)
							ptrCaller->prev->next = ptrCaller;	// One originally before reference points forward to new one
					}


				// When we get here, ptrCaller is either populated or NULL indicating success or failure
				return(ptrCaller);
			}
		}
		// If we get here, error
		return(NULL);
	}




	// NOTE!  Do not call this function directly!  Call iAppendToStarEndChain() only.
	void iicommon_SEChain_appendMasterList(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded)
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
			icommon_allocateAdditionalStartEndMasterSlots(ptrSE, tnBlockSizeIfNewBlockNeeded);
			// We never break out of this loop because we will always return above from it
		}
	}


	void iicommon_SEChain_freeUpSlot(SStartEnd* ptrSE, u32 tnSlot, u32 tnBlockSizeIfNewBlockNeeded)
	{
		u32		lnI;
		bool	llFound;


		//////////
		// See if the indicated slot is already open
		//////
			if (!ptrSE->master[tnSlot] || !ptrSE->master[tnSlot]->used)
				return;	// We're good already, the slot is free


		//////////
		// If we get here, we have to make room
		//////
			do {

				//////////
				// Find the first free slot after the indicated slot
				//////
					llFound = false;
					for (lnI = tnSlot + 1; lnI < ptrSE->masterCount; lnI++)
					{
						// Is this slot open?
						if (!ptrSE->master[lnI] || !ptrSE->master[lnI]->used)
						{
							// Yes
							llFound = true;
							break;
						}
					}


				//////////
				// Did we find a free slot?
				//////
					if (llFound)
						break;	// Yes


				//////////
				// We did not find room
				// Allocate some pointer space
				//////
					icommon_allocateAdditionalStartEndMasterSlots(ptrSE, tnBlockSizeIfNewBlockNeeded);
					// We never break out of this loop because we will always return above from it

			} while (1);


		//////////
		// When we get here, lnI is the free slot
		//////
			for (--lnI; lnI <= tnSlot; lnI--)
			{
				// Move this slot to the next slot
				ptrSE->master[lnI+1] = ptrSE->master[lnI];
			}


		//////////
		// Free up the new slot
		//////
			ptrSE->master[tnSlot] = NULL;
	}

	bool icommon_allocateAdditionalStartEndMasterSlots(SStartEnd* ptrSE, u32 tnBlockSize)
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
				// Allocate the first 32 pointers
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
// Migrate all SMasterList items from source to destination
//
//////
	void* icommon_SEChain_migrateAll(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc)
	{
		u32 lnI, lnStartCount;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && ptrSESrc->masterCount > 0)
		{
			// Grab a reasonable starting point (the end), for the first hint
			lnStartCount = (ptrSEDst->masterCount >= _COMMON_START_END_BLOCK_SIZE) ? (ptrSEDst->masterCount - _COMMON_START_END_BLOCK_SIZE) : 0;

			// Iterate through every source
			for (lnI = 0; lnI < ptrSESrc->masterCount; lnI++)
			{
				// Copy every populated slot
				if (ptrSESrc->master[lnI] && ptrSESrc->master[lnI]->used)
				{
					// Append it to the destination list
					iicommon_SEChain_appendMasterList(ptrSEDst, ptrSESrc->master[lnI], lnStartCount + lnI, _COMMON_START_END_BLOCK_SIZE);

					// Clear out the source slot
					ptrSESrc->master[lnI] = NULL;
				}
			}
		}
		// Failure if we get here
		return(NULL);
	}




//////////
//
// Migrate the existing SMasterList item from one Start/end chain to another, by either pointer
// or physical position number
//
//////
	SMasterList* icommon_SEChain_migrate(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, void* ptr, u32 tnHint, u32 tnBlockSize)
	{
		u32 lnI;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && ptrSESrc->masterCount >= 1)
		{
			for (lnI = 0; lnI < ptrSESrc->masterCount; lnI++)
			{
				// Is this our pointer?
				if (ptrSESrc->master[lnI] && ptrSESrc->master[lnI]->ptr == ptr)
				{
					// This is our man, migrate it
// TODO:  (enhancement) we want some kind of better hinting algorithm here, such as the end of the list - common block size, for now we'll just pass 0
					return(icommon_SEChain_migrate(ptrSEDst, ptrSESrc, lnI, 0, tnBlockSize));
				}
			}
			// If we get here, not found
		}
		// Indicate failure
		return(NULL);
	}

	SMasterList* icommon_SEChain_migrate(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize)
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
				icommon_allocateAdditionalStartEndMasterSlots(ptrSEDst, tnBlockSize);

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
// Migrate the existing SMasterList item, and its associated SLL item, from one Start/end chain
// to another, by either pointer or physical position number.
//
//////
	SLL* icommon_SEChain_completelyMigrateSLL(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr, u32 tnHint, u32 tnBlockSize)
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
					return(icommon_SEChain_completelyMigrateSLL(ptrSEDst, ptrSESrc, lnI, 0, tnBlockSize));
				}
			}
			// If we get here, not found
		}
		// Indicate failure
		return(NULL);
	}

	SLL* icommon_SEChain_completelyMigrateSLL(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize)
	{
		SLL*			lllPrev;
		SLL*			lllNext;
		SLL*			lll;
		SMasterList*	lml;


		// Make sure our environment is sane
		if (ptrSEDst && ptrSESrc && lnSrcNum < ptrSESrc->masterCount && lnSrcNum <= ptrSESrc->masterCount)
		{
			// Migrate it, and get its SMasterList entry
			lml = icommon_SEChain_migrate(ptrSEDst, ptrSESrc, lnSrcNum, tnHint, tnBlockSize);
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




//////////
//
// Counts how many actual items in the masterCount are valid (contain entries that are in use,
// versus
//
//////
	u32 icommon_SEChain_countValids(SStartEnd* ptrSE)
	{
		u32	lnI, lnValidCount;


		// Make sure our environment is sane
		if (!ptrSE)
			return(0);

		// Iterate through each one, and for every valid entry increase our count
		for (lnValidCount = 0, lnI = 0; 
			 lnI < ptrSE->masterCount; 
			 lnI++)
		{
			// If this entry is valid, increase our count
			if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				++lnValidCount;
		}
		// Return our value
		return(lnValidCount);
	}




//////////
//
// Called to delete an entire Start/end chain
//
// Returns:
//		-1 error in ptrSE, ptrSE->master or ptrSE->masterCount
//		Number of records deleted
//
//////
	u32 icommon_SEChain_delete(SStartEnd* ptrSE, u64 tnCallback, u64 tnParam, bool tlDeletePointers)
	{
		u32			lnI, lnDeletedCount;
		union {
			u64		_callbackAddress;
			void	(*callbackAddress)(void* ptrSE, u64 tnParam);
		};


		// Make sure the environment's sane
		if (ptrSE && ptrSE->master && ptrSE->masterCount != 0)
		{
			// Store our callback address
			_callbackAddress = tnCallback;

			//  Iterate through all entries
			lnDeletedCount = 0;
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
				{
					// Callback to the caller if they need to do something special to delete this entry
					if (tnCallback != 0)
						callbackAddress(ptrSE->master[lnI]->ptr, tnParam);

					// Delete the pointer from the list
					icommon_SEChain_deleteFrom(ptrSE, ptrSE->master[lnI]->ptr, tlDeletePointers);
					++lnDeletedCount;
				}
			}
			// When we get here, everything's deleted, now delete the container for everything. :-)
			free(ptrSE->master);
			ptrSE->master = NULL;

			// Indicate the number we deleted
			return(lnDeletedCount);
		}
		// Indicate failure
		return(-1);
	}




//////////
//
// Delete the indicated item from the chain
//
//////
	void icommon_SEChain_deleteFrom(SStartEnd* ptrSE, void* ptrCaller, bool tlDeletePointers)
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
// Search by callback for the indicated element, and when found delete it
//
//////
	bool icommon_SEChain_deleteFromAfterCallback(SStartEnd* ptrSE, bool tlDeletePointers, u64 iiCallbackFunction, u64 tnExtra)
	{
		u32					lnI;
		SStartEndCallback	cb;
		bool				llResult;


		// Make sure the environment is sane
		llResult = false;
		if (ptrSE && iiCallbackFunction != 0)
		{
			// Store the callback
			cb._iiCallbackFunction = iiCallbackFunction;

			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Ask the caller if this is it
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used && cb.iiCallbackFunctionBool(ptrSE->master[lnI]->ptr, tnExtra))
				{
					// This is the entry they want to delete
					icommon_SEChain_deleteFrom(ptrSE, ptrSE->master[lnI]->ptr, tlDeletePointers);
					llResult = true;
					break;
				}
			}
		}
		// If we get here, it wasn't found
		return(llResult);
	}






//////////
//
// Search for the indicated uniqueId in the chain.
//
// Returns:
//		NULL if error
//		The associated pointer if found
//
//////
	struct SScreen2
	{
		SLL				ll;						// 2-way link list
		u64				associatedId;			// A user-defined id of something associated with this screen

		// Limited access is granted during a refresh operation
		u64				semRefresh;				// Limited access to 
		bool			isRefreshing;			// Is this screen refreshing?

		// Associated canvas for this screen
		void*		activeCanvas;			// Pointer to this screen's active canvas (must be a member of the canvastList
		SStartEnd		canvasList;				// Pointer to this screen's first SCanvasList entry

		// Internal information used to make it happen for the target OS
		u64				ossWindowId;			// information necessary to render this screen on the OSS (pointer to _iSWindow struct, for example)
	};
	void* icommon_searchStartEndChainByUniqueId(SStartEnd* ptrSE, u64 tnUniqueId)
	{
		u32 lnI;


		// Make sure the environment is sane
		if (ptrSE)
		{
			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used && ((SLL*)(ptrSE->master[lnI]->ptr))->uniqueId == tnUniqueId)
				{
					// We've found our man
					return(ptrSE->master[lnI]->ptr);
				}
			}
		}
		// If we get here, failure
		return(NULL);
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
	void* icommon_searchStartEndChainByCallback(SStartEnd* ptrSE, u64 iiCallbackFunction, u64 tnExtra)
	{
		u32					lnI;
		SStartEndCallback	cb;


		// Make sure the environment is sane
		if (ptrSE && iiCallbackFunction != 0)
		{
			// Store the callback
			cb._iiCallbackFunction = iiCallbackFunction;

			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Ask the caller if this is it
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used && cb.iiCallbackFunctionBool(ptrSE->master[lnI]->ptr, tnExtra))
				{
					// We've found our man
					return(ptrSE->master[lnI]->ptr);
				}
			}
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Iterates through the indicated Start/End list, calling back the callback function for every item.
//
//////
	void icommon_iterateThroughStartEndForCallback(SStartEnd* ptrSE, u64 iiCallbackFunction, u64 tnExtra)
	{
		u32					lnI;
		SStartEndCallback	cb;


		// Make sure the environment is sane
		if (ptrSE && iiCallbackFunction != 0)
		{
			// Store the callback
			cb._iiCallbackFunction = iiCallbackFunction;

			// Iterate through the master list calling every valid entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Give this to the caller for their processing
				if (ptrSE->master[lnI] && ptrSE->master[lnI]->used)
					cb.iiCallbackFunctionVoid(ptrSE->master[lnI]->ptr, tnExtra);
			}
		}
	}




//////////
//
// Added for debugging.  Validates that all of the entries in a Start/end chain have proper
// ll.prev and ll.next members.  Should only need to be used during initial development, and
// in tracking down future bugs.  I intend for these Start/end functions to be heavily tested
// and made completely reliable in all conditions.
//
// If the iiCallbackFunction is populated, then if it returns:
//			true		- test was good
//			false		- test failed
// Note:  The callback is only needed if the lml->ptr structure itself has Start/end members
//        that need to be examined.  If iiCallbackFunction is not populated, only tests
//        the members contained in the ptrSE Start/end structure.
//
// This function doesn't return anything.
// If there is an error, it will trap to the debugger so the machine state can be examined.
//
//////
	void icommon_validateStartEnd(SStartEnd* ptrSE, u64 iiCallbackFunction)
	{
		u32					lnI;
		SMasterList*		lml;
		SStartEndCallback	cb;


		// Make sure the environment is sane
		if (ptrSE)
		{
			// Store the callback
			cb._iiCallbackFunction = iiCallbackFunction;

			// Iterate through the master list until we find the associated entry
			for (lnI = 0; lnI < ptrSE->masterCount; lnI++)
			{
				// Ask the caller if this is it
				lml = ptrSE->master[lnI];
				if (lml && lml->used)
				{
					if (lml == ptrSE->root)
					{
						if (lml == ptrSE->last)
						{
							// This is the ONLY entry
							// ll.prev and ll.next need to be null
							if (lml->ll.prev != NULL)
								_asm int 3;
							if (lml->ll.next != NULL)
								_asm int 3;

						} else {
							// This is the first entry
							// ll.prev needs to be null, ll.next needs to be not null
							if (lml->ll.prev != NULL)
								_asm int 3;
							if (lml->ll.next == NULL)
								_asm int 3;
						}

					} else if (lml == ptrSE->last) {
						// This is the last entry
						// ll.prev needs to be not null, ll.next needs to be null
						if (lml->ll.prev == NULL)
							_asm int 3;
						if (lml->ll.next != NULL)
							_asm int 3;

					} else {
						// Somewhere in the middle
						// ll.prev and ll.next need to be not null
						if (lml->ll.prev == NULL)
							_asm int 3;
						if (lml->ll.next == NULL)
							_asm int 3;
					}

					// If there's a callback on this entry, try it out
					// If it returns false, there's an issue, if it returns true it's okay
					if (iiCallbackFunction != 0 && !cb.iiCallbackFunctionBool(lml->ptr, 0))
						_asm int 3;
				}
			}
		}
	}




//////////
//
// Called to reverse the endian
//
//////
	u32 icommon_swapEndian(u32 tnValue)
	{
		_asm {
			mov		eax,tnValue
			bswap	eax
			mov		tnValue,eax
		}
		return tnValue;
	}




//////////
//
// For certain operations, colors are reversed
//
//////
	u32 icommon_RGBA2BGRA(u32 tnColor)
	{
		u8 lnRed, lnGrn, lnBlu, lnAlp;


		// Grab the indicated colors
		lnRed	= red(tnColor);
		lnGrn	= grn(tnColor);
		lnBlu	= blu(tnColor);
		lnAlp	= alp(tnColor);

		// Encode and return the new color
		return(rgba(lnBlu, lnGrn, lnRed, lnAlp));
	}




//////////
//
// Allocate the indicated size memory block, and initialize it to nulls
//
// Returns:
//		pointer to the newly allocated block
//
// Note:  The allocated memory is initialized to null if allocated successfully
//
//////
	void* icommon_allocateAndNull(u32 tnSize, bool tnInitToZeros)
	{
		s8* lp;


		// Allocate
		lp = (s8*)malloc(tnSize);

		// Null if valid
		if (lp && tnInitToZeros)
			icommon_memset(lp, 0, tnSize);

		// Return the fruits of our labor
		return(lp);
	}




//////////
//
// Called to search the haystack for the needle
//
//////
	bool icommon_isNeedleInHaystack(csu8p tcHaystack, s32 tnHaystackLength, csu8p tcNeedle, s32 tnNeedleLength, bool tlCaseSensitive, u32* tnFoundPosition)
	{
		s32		lnI;
		u32		lnResult;
		csu8p	ptr;


		// Make sure our environment's sane
		if (tcHaystack._cu8 && tcNeedle._cu8 && tnHaystackLength > 0 && tnNeedleLength > 0 && tnHaystackLength >= tnNeedleLength)
		{
			// Iterate until we reach the end
			for (lnI = 0; lnI + tnNeedleLength <= tnHaystackLength; lnI++)
			{
				// Get this offset to this location
				ptr._cu8 = tcHaystack._cu8 + lnI;

				// Scan from this location
				if (tlCaseSensitive)	lnResult = icommon_memcmp(ptr, tcNeedle, tnNeedleLength);
				else					lnResult = icommon_memicmp(ptr, tcNeedle, tnNeedleLength);

				// What were the findings?
				if (lnResult == 0)
				{
					// It was found, store the position
					if (tnFoundPosition)
						*tnFoundPosition = lnI;

					// Indicate success
					return(true);
				}
			}
		}
		// If we get here, failure
		if (tnFoundPosition)
			*tnFoundPosition = -1;

		// Indicate failure
		return(false);
	}




//////////
//
// Search the specified unicode string haystack for the needle
//
//////
	bool icommon_isNeedleInHaystack_Unicode(w16* twHaystack, w16* twNeedle)
	{
		s32 lnI, lnLengthHaystack, lnLengthNeedle;


		// Make sure our environment's sane
		if (twHaystack && twNeedle)
		{
			// Get the lengths
			lnLengthHaystack	= wcslen(twHaystack);
			lnLengthNeedle		= wcslen(twNeedle);

			// Repeat throughout the unicode string
			for (lnI = 0; lnI <= lnLengthHaystack - lnLengthNeedle; lnI++)
			{
				// Did we find a match?
				if (_wcsicmp(twHaystack + lnI, twNeedle) == 0)
					return(true);
			}
		}
		// If we get here, not found
		return(false);
	}




//////////
//
// Scans forward so long as there are numerical digits (ASCII-48 through ASCII-57, "0" through "9")
//
//////
	u32 icommon_countConsecutiveAsciiNumericDigits(s8* buffer, u32 tnMaxLength)
	{
		u32 lnLength;


		// While we have numbers, continue
		for (lnLength = 0;		lnLength < tnMaxLength && buffer[lnLength] >= '0' && buffer[lnLength] <= '9';		)
			++lnLength;

		// We have our length
		return(lnLength);
	}




//////////
//
// Reads through the numbers, presumably previously determined by iScanConsecutiveNumbers(),
// to obtain the numerical value after converting from text to an unsigned integer
//
//////
	u32 icommon_convertTextToU32(s8* tcNumbers, u32 tnMaxLength)
	{
		u32 lnLength, lnValue, lnMultiplier;


		// Scan through every number
		for (lnLength = 0, lnValue = 0, lnMultiplier = 10;
			 lnLength < tnMaxLength;
			 lnLength++)
		{
			lnValue = (lnValue * lnMultiplier) + (u32)(tcNumbers[lnLength] - '0');
		}

		// We have our converted value
		return(lnValue);
	}
