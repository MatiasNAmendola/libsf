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

typedef float						f32;
typedef double						f64;
typedef const float					cf32;
typedef const double				cf64;

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
	cu32					_COMMON_START_END_BIG_BLOCK_SIZE		= 256;			// Allocate 256 entries/slots at a time (Start/end)
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
	#define oss_strlen(tcData)			oss_scanForwardUntilCharacter(tcData, 0)
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
	static union {
		u64		_vvm_debuggerInterface;
		u64		(CALLTYPE *vvm_debuggerInterface)						(s8* tcFunctionName);
	};


	struct SLL;
	struct SLL4;
	struct SMasterList;
	struct SStartEnd;
	struct SDatum;
	struct SDatum2;
	struct SAsciiCompSearcher;
	struct SBxml;
	struct SBxmla;
	struct SBxmlError;
	struct SBuffer;
	struct SFileTime;
	struct SDateTime;
	struct SFindFile;
	struct SBxmlList;
	struct SBxmlaList;
	struct SSha1;
	struct SRef;
	struct SDatumLL;
	struct SBitmapHeader;
	struct SBitmapInfo;
	struct SRGB;
	struct SRGBA;
	struct SRGBAF;
	struct SLLCallback;
	struct SLL4Callback;
	struct SStartEndCallback;
	struct SOssMouseEvent;
	struct SOssKbdEvent;
	struct SOssWindow;
	struct SOssLine;
	struct SOssComp;
	struct SCallbacks;
	struct SSysInfo;
	struct SCanvas;
	struct SScreen;
	struct SRectXYWH;
	struct SRectXYXY;
	struct SRegion;




//////////
//
// General system information
//
//////
	struct SSysInfo
	{
		s32			cores;							// Number of cores (including hyper-threaded cores)
		u64*		addressOf1MsTickCount;			// Address of the system 1ms tick counter (continually updated every millisecond)
	};


//////////
//
// Note: All of these are called from the window's message thread.
//       Each one should raise flags or copy whatever data is necessary
//       to some external areas for a post-return respond in another thread.
//
//////
	struct SOssCallback
	{
		union
		{
			u64		_func;
			void	(*funcBool)	(SOssCallback* cb);
			void	(*funcVoid)	(SOssCallback* cb);
			//////
			// Uses the following format for the callback:
			//		void func(SOssCallback* cb)
			//		bool func(SOssCallback* cb)
			//////////
		};
	};

	struct SOssCbData1Boolean
	{
		union {
			u64		_callback;
			bool	(*callback)(SOssCbData1Boolean* ptr);
		};
		void*			ptr;					// Related pointer
		u64				extra;					// Data item
	};

	struct SOssCbData2Boolean
	{
		union {
			u64		_callback;
			bool	(*callback)(SOssCbData2Boolean* ptr);
		};
		void*			ptr;					// Related pointer
		union {									// Data item 1
			u64			extra;
			u64			extra1;
		};
		u64				extra2;					// Data item 2
	};

	struct SOssCbData1Void
	{
		union {
			u64		_callback;
			void	(*callback)(SOssCbData1Void* ptr);
		};
		void*			ptr;					// Related pointer
		u64				extra;					// Data item
	};

	struct SOssCbData2Void
	{
		union {
			u64		_callback;
			void	(*callback)(SOssCbData2Void* ptr);
		};
		void*			ptr;					// Related pointer
		union {									// Data item 1
			u64			extra;
			u64			extra1;
		};
		u64				extra2;					// Data item 2
	};

	// Generic callback structure
	struct SCallback
	{
		union
		{
			u64		_func;
			bool	(*funcBool)	(SCallback* cb);
			void	(*funcVoid)	(SCallback* cb);
			//////
			// Uses the following format for the callback:
			//		void func(SCallback* cb)
			//		bool func(SCallback* cb)
			//////////
		};

		// Data items for this callback
		void*		ptr;
		union {
			u64		extra;
			u64		extra1;
		};
		u64			extra2;
	};


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

	struct SLL
	{
		union {
			SLL*		next;					// Next entry in linked list
			SBxmla*		bxmla;					// To allow viewing as a bxmla structure
		};
		SLL*			prev;					// Previous entry in linked list
		u64				uniqueId;				// Unique id associated with this object
	};

	// Direction for navigation through an SLL4
	const u32 _LL4_WEST			= 1;
	const u32 _LL4_EAST			= 2;
	const u32 _LL4_NORTH		= 4;
	const u32 _LL4_SOUTH		= 8;
	const u32 _LL4_ALL			= 16;			// Go out in every direction (only valid on oss_ll4_deleteChain() and oss_ll4_deleteChainWithCallback())
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

		// SStartEnd lists can have a master (which points to other items using the SMasterList protocol), or it can be used merely a pointer holder
		union {
			SMasterList**	master;					// Every item in the start/end chain is appended here when created (used primarily for suspension and resumption of the VVM)
			void**			ptr;
		};
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

	// Structure to search for things
	struct SAsciiCompSearcher
	{
		const s8*		keyword;										// Text keyword being searched
		s32				length;											// Length of the keyword (negative for case sensitive, positive case insensitive, 0 for termination entry)
		bool			repeats;										// Can this item repeat?  Or is this a one-shot keyword?
		u32				iCode;											// An associated code to store when this entry is found
		bool			firstOnLine;									// Should this item ONLY be the first on line?

		// Used for an explicit callback to handle this component text
		union {
			u64			_addressHandler;
			u64			(*handler)(void);
		};
	};

	// BXML structure (tag level)
	struct SBxml
	{
		SLL4			ll4;											// 4-way link list, holds parent, child, and sibling (next/prev) Bxml nodes
		u32				level;											// root=0, first child=1, etc.
		bool			closed;											// Is this level closed?  This is used during loading to determine if the closing </tag> was found.

		// All attributes (if any) are here
		SDatum			_name;											// Name of this tag
		SStartEnd		_attributes;									// A list of attributes for this node		(SBxmla)
	};

	// BxmlA structure (attribute level)
	struct SBxmla
	{
		SLL				ll;												// 2-way link list, each attribute only points forward and backward to its siblings

		SBxml*			_parent;										// The parent Bxmla related to this attribute
		SDatum			_name;											// Name of the attribute
		SDatum2			_data;											// The data for this attribute
	};

	struct SBxmlError
	{
		SDatum		description;										// Error description

		u64*		lastErrorOffset;									// If parsing a string, the last error offset, otherwise undefined
		u32			lastErrorCode;										// The error code having been logged

		SBxml*		bxmlInError;										// The bxml being worked on when the error occurred (if any)
		SBxmla*		bxmlaInError;										// The Bxmla being worked on when the error occurred (if any)
	};

	// Buffer accumulators
	struct SBuffer
	{
		s8*			data;												// Pointer to a buffer allocated in blocks
		u32			allocatedLength;									// How much of space has been allocated for the buffer
		u32			populatedLength;									// How much of the allocated buffer is actually populated with data
		u32			allocateBlockSize;									// Typically 16KB
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

	struct SDateTime
	{
		s16			year;						// Literal value for all dates, meaning -32,767 to 32,768 for year
		u8			month;						// Month number, 1=January
		u8			day;						// Day of month, 1=First
		u8			hour;						// Hour of day, 0=midnight
		u8			minute;						// Minute of hour, 0=top of hour
		u8			second;						// Second of minute, 0=start of minute
		u16			millisecond;				// Milliseconds

		// Using machine-dependent high resolution timer
		u64			tickCount;					// For high resolution purposes
		u64			frequency;					// Frequency at which the tick count ticks, used to compute time deltas
	};

	struct SFindFile
	{
		SDatum		file;												// The found filename
		SDatum		file2;												// An alternate name for the file
		u64			size;												// How big is the file?
		SFileTime	created;											// FileTime of file's creation date
		SFileTime	accessed;											// FileTime of file's last access date
		SFileTime	updated;											// FileTime of file's last updated date

		bool		isNormal;											// File has no specific attribute set
		bool		isFile;												// Is it a regular file?
		bool		isDirectory;										// Is it a directory?

		bool		isMarkedArchive;									// Does the file have the archive attribute marked?
		bool		isMarkedCompressed;									// Does the file have the compressed attribute marked?
		bool		isMarkedEncrypted;									// Does the file have the encrypted attribute marked?
		bool		isMarkedOffline;									// Does the file have the offline attribute marked?
		bool		isMarkedReadOnly;									// Does the file have the readonly attribute marked?
		bool		isMarkedSystem;										// Does the file have the system attribute marked?
		bool		isMarkedHidden;										// Does the file have the hidden attribute marked?
		bool		isMarkedTemporary;									// Does the file have the temporary attribute marked?
		bool		isMarkedVirtual;									// Does the file have the virtual attribute marked?
	};

	struct SBxmlList
	{
		SBxml*		bxml;
	};

	struct SBxmlaList
	{
		SBxmla*		bxmla;
	};

	struct SSha1
	{
		u8			sha20Bytes[20];										// 20-byte buffer used for computing SHA1
		u64			sha1_u64;											// 64-bit form of the 20-byte buffer
		u32			sha1_u32;											// 32-bit form of the 20-byte buffer
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
			u32			color;					// RGBA color in integer form
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

	struct SRectXYWH
	{
		u32		x;
		u32		y;
		u32		width;
		u32		height;
	};

	struct SRectXYXY
	{
		u32		ulx;
		u32		uly;
		u32		lrx;
		u32		lry;
	};

	struct SSize
	{
		union {
			u32		width;
			u32		w;
		};

		union {
			u32		height;
			u32		h;
		};
	};

	struct SLLCallback
	{
		union
		{
			u64		_func;
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
			u64		extra;
			u64		extra1;
		};
		u64		extra2;
	};

	struct SLL4Callback
	{
		union
		{
			u64		_func;
			bool	(*funcBool)	(SLL4Callback* cb);
			void	(*funcVoid)	(SLL4Callback* cb);
			//////
			// Uses the following format for the callback:
			//		void func(SLL4Callback* cb)
			//		bool func(SLL4Callback* cb)
			//////////
		};

		// Data items for this callback
		SLL4*	node;
		union {
			u64		extra;
			u64		extra1;
		};
		u64		extra2;
	};

	struct SStartEndCallback
	{
		union
		{
			u64		_func;
			bool	(*funcBool)	(SStartEndCallback* cb);
			void	(*funcVoid)	(SStartEndCallback* cb);
			//////
			// Uses the following format for the callback:
			//		bool func(SStartEndCallback* cb)
			//////////
		};

		// Data items for this callback
		void*	ptr;
		u64		extra;
	};

	// The values here have been changed into VVMOSS_* values, which are common throughout the system externally.
	struct SOssMouseEvent
	{
		u64				timer;								// Timer when event triggered/signaled
		u32				x;									// X coordinate of action
		u32				y;									// Y coordinate of action
		u32				buttons;							// Holds buttons (see VVMOSS_MOUSE_BUTTON_* constants)
		u32				keys;								// State of the keys when called (shift, ctrl, alt)
	};

	// The values here have been changed into VVMOSS_* values, which are common throughout the system externally.
	struct SOssKbdEvent
	{
		u64				timer;								// Timer when event triggered/signaled
		s8				ascii;								// ASCII character that was typed
		u16				_unicode;							// UNICODE character that was typed
		u32				keyCode;							// Code uniquely identifying the key (see VVMOSS_KEYCODE_* constants)
		u32				keyFlags;							// State of the modifier keys when called (shift, ctrl, alt, caps)
	};


	// Low-level OSS window structure, but one slightly abstracted from the OSS so components are visible to external apps
	struct SOssWindow
	{
		// Note:  This structure is encapsulated in SOssWindow, which is the Start/end container for this
		// Identifier
		u64				uniqueId;							// The unique identifier
		u64				screenId;							// The VVM screen object this window relates to
		s64				timer;								// Timer values recorded from the time of creation of the window (0 at creation, incremented every "logical" 10ms)
		bool			hasFocus;							// Does this window have focus?

		// Input
		s8*				caption;							// (copy or original) Window title (only supports ASCII characters for now)
		u32				captionLength;						// Length of the title

		s32				x;									// Window x position
		s32				y;									// Window y position
		u32				width;								// Width of the client portion of the window
		u32				height;								// Height of the client portion of the window
		u32				widthMin;							// Minimum width the window can have (including the border)
		u32				heightMin;							// Minimum height the window can have (including the border)
		u32				widthMax;							// Maximum width the window can have (including the border)
		u32				heightMax;							// Maximum height the window can have (including the border)

		// Default colors
		SRGBA			foreColor;							// Default foreground color
		SRGBA			backColor;							// Default background color

		// Flags
		bool			resizable;							// Is the window resizable?
		bool			movable;							// Is the window movable?
		bool			closable;							// Is the window closable?
		bool			visible;							// Is the window visible?
		bool			border;								// Does the window have an OS-specific border?  If not, it must be manually manipulated by the app

		// If the window doesn't have an OSS-border, what is the non-client rectangle used to auto-process movements and to send back events?
		u32				ncUlX;								// Non-client upper-left X
		u32				ncUlY;								// Non-client upper-left Y
		u32				ncLrX;								// Non-client lower-right x
		u32				ncLrY;								// Non-client lower-right y
		u32				ncBorder;							// How big is the non-client border (used for resizing if resizable)

		// Output
		u64				osHandle;							// HWND
		u64				osDC;								// Device Context
		u64				osBitmap;							// Holds bitmap handle for window
		void*			osBitData;							// Pointer to physical bit data
		s32				osX;								// visible X position (if visible)
		s32				osY;								// visible Y position (if visible)
		u32				osWidth;							// width adjusted for window borders
		u32				osHeight;							// width adjusted for window borders plus title bar

		// Mouse processing
		SOssMouseEvent	osMouseDownFirst;					// When/where the first mouse button was pressed
		SOssMouseEvent	osMouseDown;						// When/where the last mouse button was pressed
		SOssMouseEvent	osMouseUp;							// When/where the last mouse button was released
		SOssMouseEvent	osMouseMove;						// When/where the last mouse move occurred
		bool			osIsMouseButtonDown;				// When the user presses a button down, is raised
		bool			osHoverCallbackFired;				// Flag indicates if the hover callback has been fired or not
		u64				osMouseDownAccumulationCounter;		// Increments continually after the mouse is pressed down

		// Dragging
		bool			osIsDragging;						// Is something being dragged?
		u64				osDragStartTimer;					// Timer when the drag started
		SOssMouseEvent	osDragStart;						// Where the drag was initiated
		SOssMouseEvent	osDragLast;							// Where the drag event is currently

		// Keyboard processing
		SOssKbdEvent	osKeyDownLast;						// Down events
		SOssKbdEvent	osKeyDown;
		SOssKbdEvent	osKeyUpLast;						// Up events
		SOssKbdEvent	osKeyUp;

		// Callbacks
		SCallbacks		callback;							// Callback definitions (common.h)
	};


	// Holds a line structure, one entry for every line in a file
	struct SOssLine
	{
		SLL				ll;												// 2-way link list

		// Information about the line
		s8*				alternateBase;									// (Optional) If used, indicates we are not using "the associated base memory blocK" as the the reference pointer for this line, but have replaced it with our own oss_malloc allocation, if so then it will need manually freed with oss_free
		s8*				base;											// Base for the start of this line
		u64				start;											// Start of the line in the associated base memory block
		u64				length;											// Length of the line (excluding trailing CR/LF combinations)
		u64				whitespace;										// How much whitespace precedes the start of non-whitespace content on the line
		u64				lineNumber;										// Line number when initially parsed

		// Parsed / processed information about the raw source line (if used)
		SStartEnd		comps;											// Pointer to the first component identified on this line	(SOssComp)
		SStartEnd		compsCombined;									// When comps are combined, the first element is morphed into the new type, but any that were replaced go here	(SOssComp)
		// Note:  components begin at (line->base + line->start + line->whitespace), which is what would be found if comp->start = 0

		// For portions of the line which have been parsed
		void*			extra;											// Extra data associated with this structure (application specific)
	};

	// Holds a component structure
	struct SOssComp
	{
		SLL				ll;												// 2-way link list

		// Information about the component
		SOssLine*		line;											// The line this component relates to
		u32				iCode;											// Refer to _VVMMC_COMP_* structs in vvmmc_const.h
		u64				start;											// Start into the indicates line's source code
		s64				length;											// Length of the component

		// If this component has sub-components, they go here
		SStartEnd		comps;											// Pointer to any child components
	};




//////////
//
// Every window (visible or not) has an associated screen
//
//////
	struct SScreen
	{
		SLL				ll;						// 2-way link list
		u64				associatedId;			// A user-defined id of something associated with this screen

		// Limited access is granted during a refresh operation
		u64				semRefresh;				// Limited access to 
		bool			isRefreshing;			// Is this screen refreshing?

		// Associated canvas for this screen
		SCanvas*		activeCanvas;			// Pointer to this screen's active canvas (must be a member of the canvastList
		SStartEnd		canvasList;				// Pointer to this screen's first SCanvasList entry

		// Internal information used to make it happen for the target OS
		u64				ossWindowId;			// information necessary to render this screen on the OSS (pointer to _iSWindow struct, for example)
	};
//////////
//
// Used for text, indicates the drawing state for the text item
//
//////
	// Attributes to use for drawing text
	struct SDrawState
	{
		bool			condensed		: 1;				// Is this item to be drawn condensed (shrunk)
		bool			extend			: 1;				// Is this item to be drawn extended (wide)
		bool			shadow			: 1;				// Is this item to be drawn with a shadow
		bool			outline			: 1;				// Is this item to be drawn with an outline
		u32				alignment		: 1;				// 0-left, 1-right, 2-center
	};



//////////
//
// Canvases are used exclusively for drawing, and as a parent for child objects.
// Every canvas is a single-instance creation.  It exists as a logical object,
// but only has interaction with the VVM when it is associated with a screen
// directly, or is the child of a canvas associated with a screen.
//
// Canvases will respond properly to events, but they will only render
// themselves on render events if they are associated with a Screen.  Since
// a single Canvas can exist on multiple Screens, the Canvas will be rendered
// one time, and then painted as needed onto each parent screen to which it
// belongs.
//
//////
	// Used to indicate the state of settings on the root object, or an instance of its use
	struct SCanvasState
	{
		// The state of a canvas or a canvas instance
		bool			isEnabled		: 1;				// Is this instance enabled?  (does it respond to updates if/when it has focus? It still can even if it's not visible)
		bool			isVisible		: 1;				// Is this instance visible?  (which also controls the visibility of all children)
		bool			useTransparency	: 1;				// Does this canvas use transparency?
	};

	struct SCanvas
	{
		SLL				ll;						// 2-way link list
		u64				associatedId;			// The associated id, provided at creation for creator's private use and reference
		SCanvasState	state;					// Settings like active, focus, tab order, etc.

		// Limited access is granted during a refresh operation, only the bd memory area is accessible publicly
		u64				semRefresh;				// Limited access to 
		bool			isRefreshing;			// Is this canvas currently refreshing?  If yes, this means its children are also potentially busy.

		// All Canvas objects are always 32-bit RGBA format, even if they're ultimately rendered by the OS onto some lesser or greater color system
		u32				width;					// width
		u32				height;					// height
		SRGBA			backColor;				// A default back color to use for transparency operations

		// Bit buffers
		SRGBA*			bd;						// buffer data
		SRGBA*			bda;					// buffer data accumulator (for building child items onto this item)
		u64				bd_vvmoss;				// OS-specific information used for drawing OSS-fonts (used only by vvmoss code)

		// Items related specifically to this canvas
		SStartEnd		canvasList;				// Pointer to this canvas's first child SCanvasList entry
		SStartEnd		regionList;				// Pointer to this canvas's first SRegionList entry
	};


	// Canvases exist in one place. To be used by the VVM, they must be associated with a canvas list,
	// which allows the single instance objects to be employed where required.  In most cases this is
	// likely to be a 1:1 ratio.  However, the VVM allows single instance objects to appear multiple
	// places on multiple parents.  This allows a control to be on several different items without its
	// related data requiring mirroring to other controls.
	struct SCanvasList
	{
		SLL				ll;						// 2-way link list
		u64				associatedId;			// The associated id, provided at creation for creator's private use and reference

		// Conditions for this particular instance
		SCanvasState	state;					// Settings like active, focus, tab order, etc.

		// The canvas associated here
		SCanvas*		canvas;					// Pointer to the canvas associated with this entry

		// Relative position to the associated parent
		s32				x;						// Upper-left X coordinate
		s32				y;						// Upper-left Y coordinate
		SRGBA			backColor;				// The instance's default back color to use for transparency operations (if state.useTransparency)

		// Items related specifically for this one instance of the canvas (in addition to the ones related to the canvas)
		SStartEnd		canvasList;				// Pointer to the first SCanvasList entry of this canvasList instance
		SStartEnd		regionList;				// Pointer to the first SRegionList entry of this canvasList instance
	};




//////////
//
// The State condition is used on regions by the VVM to maintain their status, and determine how
// to handle messages issued by the VVMOSS.
//
// The order of precedence for SRegionState determination is:
//		root object overrides instances if root is negative (switched off/disabled)
//			- This means if the root is not active, even if instances are set to active, then instances are also inactive
//		instance object overrides root if root is positive (switched on/enabled)
//			- If root is active, but instance is not active, then instance is not active
//		callbacks can be set independently on root, or instances, or both
//		only instance callbacks are called if defined, otherwise root callbacks are called
//		if the instance desires to have the root object's callback called as well, then it must issue that call explicitly itself
//			- This consideration was given because it may be desirable to perform some operation, then call the root object, then continue after root's processing is completed
//			- This also more closely models xbase languages with their SUPER() or DODEFAULT() type codes
//////
	// Used to indicate the state of settings on the root object, or an instance of its use
	struct SRegionState
	{
		// The state of a region or a region instance
		bool			isActive		: 1;				// Is this instance active? (does it respond to updates if/when it has focus? It still can even if it's not visible)
		bool			isVisible		: 1;				// Is this instance visible?
		bool			hasFocus		: 1;				// Does this instance have focus?
		bool			useCallbacks	: 1;				// Should callbacks be used for this instance?
		u32				tabOrder		: 16;				// -1=not a tab stop, 0 or greater, tab order
	};




//////////
//
// Regions are rectangular instance objects which can be applied to canvases.  They typically define
// something that will be drawn, or responded to via keyboard or mouse interaction and callbacks.  They
// can also trigger custom events programmatically.  Regions are instance objects that can exist on
// multiple parents.  For this reason, SRegionList instances are used to reference regions indirectly,
// and potentially multiply if an event is triggered on more than one parent simultaneously (such as
// if two parent objects have focus and receive a keystroke, mouse movement, etc).
//
//////
	// Rectangular definitions
	struct SRegion
	{
		SLL				ll;						// 2-way link list
		u64				associatedId;			// The associated id, provided at creation for creator's private use and reference

		// Limited access is granted during a refresh operation
		u64				semRefresh;				// Limited access to 
		bool			isRefreshing;			// Is this region refreshing?

		// Conditions for this particular instance
		SRegionState	state;					// Settings like active, focus, tab order, etc.

		// Region information
		u32				type;					// Type of input, see _REGION_* constants
		u32				width;					// Width of the region
		u32				height;					// Height of the region
		// Note:  The x,y coordinates are assigned when they are applied to a canvas or other region as part of the SRegionList entry

		// Default region callbacks and sub-regions
		SCallbacks		callback;				// Callbacks for activities when this region has focus
		SStartEnd		events;					// A list of events this region responds to		(SEvent*)
		SStartEnd		regionList;				// A list of sub-regions relative to this one	(SRegion*)
	};


	// Instances of a rectangular definition
	struct SRegionList
	{
		SLL				ll;						// 2-way link list
		u64				associatedId;			// The associated id, provided at creation for creator's private use and reference

		// The region associated here at this location, and its instance state
		SRegion*		region;					// The region instance related to this entry
		SRegionState	state;					// Settings like active, focus, tab order, etc.

		// Relative position to the associated parent
		s32				x;						// Upper-left X coordinate for this instance
		s32				y;						// Upper-left Y coordinate

		// Region instance callbacks and sub-regions
		SCallbacks		callback;				// Callbacks for activities when this instance of the region has focus
		SStartEnd		regionList;				// A list of sub-regions relative to this one
	};




//////////
//
// Each event is a custom event that is signaled when manually raised.
//
//////
	struct SEvent
	{
		SLL			ll;							// 2-way link list

		u64			eventId;					// App-assigned ID number
		u64			signalFlags;				// What signal flags cause this event to fire (any bits enabled will cause it to signal)

		// Function to call when this event is signaled
		union {
			u64		_event;
			void	(CALLTYPE *event)(SEvent* te, u64 tnSignal, u64 tnValue, u64 tnExtra);
		};
	};




//////////
//
// Cask structures
//
//////
	// Refer to _VVMOSS_CASK_* constants
	struct SCaskPip
	{
		bool		active;						// Is this pip active?

		SRectXYXY	rect;						// The coordinate within the cask
		SRegion		foo;

		SRGBA		colorNeutral;				// What color is displayed when there is no mouse activity?
		SRGBA		colorOver;					// What color is displayed when the mouse moves over it?
		SRGBA		colorClick;					// What color is displayed when the user clicks down on it?

		SCallback*	enter;						// Called when the pip is entered
		SCallback*	leave;						// Called when the pip is left
		SCallback*	hover;						// Called when the pip is hovered over
		SCallback*	click;						// Called when the pip is clicked
	};

	struct SCaskSide
	{
		u32			style;						// Closed, minimal, text, or extended text
		u32			pips;						// Supports 0 through 3

		//////////
		// Only used for extended text
		//////
			csu8p		extendedText;			// If there is any text on this side, include it here

		//////////
		// Only used if the number of pips is not 0
		//////
			SCaskPip*	pip1;					// What to do when pip1 is acted upon
			SCaskPip*	pip2;					// What to do when pip2 is acted upon
			SCaskPip*	pip3;					// What to do when pip3 is acted upon
	};

	struct SCask
	{
		u32			style;						// [Standard plus round, square, diamond coupled to information in left and right], or encompassing rectangle, up rectangle, or down rectangle (all of which use the fixed semi-rounded form)
		SSize		size;						// If a standard cask, will be initially drawn in default resolution, and then scaled up or down to this level
												// If height is -1, will be natural height of whatever is required.  If width is -1, then will use natural width as required for indicated type

		//////////
		// The canvas of the appropriately scaled item
		//////
			SCanvas*	canvas;

		//////////
		// Used only for standard types:
		//////
			csu8p		text;					// Cask middle text
			SCaskSide*	left;					// Left-side cask information
			SCaskSide*	right;					// Right-side cask information

		//////////
		// Only used internally
		//////
			SCanvas*	_canvasRaw;				// The canvas of the original un-scaled item.  This canvas is used to copy or scale into the canvas.
	};
