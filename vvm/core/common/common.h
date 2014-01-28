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
	cu32					_COMMON_BUILDER_BLOCK_SIZE				= 16384;		// Allocate 16KB at a time
	cu32					_COMMON_BUILDER_BLOCK_SIZE_BIG			= 10240000;		// Allocate 1MB at a time

	// Common constants
	cf64					_2PI									= 6.28318530717959;		// 2*pi
	cf64					_3PI_2									= 4.71238898038469;		// 3*pi/2
	cf64					_4PI_3									= 4.18879020478639;		// 4*pi/3
	cf64					_PI										= 3.14159265358979;		// pi
	cf64					_2PI_3									= 2.09439510239320;		// 2*pi/3
	cf64					_PI_2									= 1.57079632679490;		// pi/2
	cf64					_PI_3									= 1.04719755119660;		// pi/3
	cf64					_PI_4									= 0.78539816339745;		// pi/4
	cf64					_PI_6									= 0.52359877559830;		// pi/6
	cf64					_E										= 2.718281828459045;	// e
	cf64					_GR										= 1.618033988749895;	// golden ratio


//////////
// Compass directions, used by iioss_canvasPolygon()
//////
// TODO: I'd like to revisit these naming conventions
	cu32					_COMPASS_UP_DOWN								= 0x10;
	cu32					_COMPASS_SIDE_SIDE								= 0x20;
	cu32					_COMPASS_ORDINAL								= 0x40;		// Note:  If this bit is 0, then it's a cardinal position
	cu32					_COMPASS_CARDINAL								= 0x80;		// This bit is not used, but can be.  Normally test the _COMPASS_ORDINAL bit for 0 to determine if cardinal.

	cu32					_COMPASS_DECORATION_TOP							= 0x100;	// NW,N,NE
	cu32					_COMPASS_DECORATION_BOTTOM						= 0x200;	// SW,S,SE
	cu32					_COMPASS_DECORATION_LEFT						= 0x400;	// NW,W,SW
	cu32					_COMPASS_DECORATION_RIGHT						= 0x800;	// NE,E,SE
	cu32					_COMPASS_DECORATION_LEFT_TOP					= _COMPASS_DECORATION_LEFT		| _COMPASS_DECORATION_TOP;
	cu32					_COMPASS_DECORATION_RIGHT_TOP					= _COMPASS_DECORATION_RIGHT		| _COMPASS_DECORATION_TOP;
	cu32					_COMPASS_DECORATION_LEFT_BOTTOM					= _COMPASS_DECORATION_LEFT		| _COMPASS_DECORATION_BOTTOM;
	cu32					_COMPASS_DECORATION_RIGHT_BOTTOM				= _COMPASS_DECORATION_RIGHT		| _COMPASS_DECORATION_BOTTOM;
	cu32					_COMPASS_DECORATION_MASK						= 0xf00;

	// Cardinal
	cu32					_COMPASS_NORTH									= 0x01;
	cu32					_COMPASS_SOUTH									= 0x02;
	cu32					_COMPASS_EAST									= 0x04;
	cu32					_COMPASS_WEST									= 0x08;
	cu32					_COMPASS_CARDINAL_ORDINAL_MASK					= 0xf;

	// Ordinal
	cu32					_COMPASS_NORTH_EAST								= _COMPASS_NORTH	| _COMPASS_EAST;
	cu32					_COMPASS_SOUTH_EAST								= _COMPASS_SOUTH	| _COMPASS_EAST;
	cu32					_COMPASS_SOUTH_WEST								= _COMPASS_SOUTH	| _COMPASS_WEST;
	cu32					_COMPASS_NORTH_WEST								= _COMPASS_NORTH	| _COMPASS_WEST;

	// Cross
	cu32					_COMPASS_NORTH_SOUTH							= _COMPASS_NORTH	| _COMPASS_SOUTH;
	cu32					_COMPASS_EAST_WEST								= _COMPASS_EAST		| _COMPASS_WEST;
	cu32					_COMPASS_SOUTH_NORTH							= _COMPASS_NORTH_SOUTH;
	cu32					_COMPASS_WEST_EAST								= _COMPASS_EAST_WEST;
	// Note: In vo_sup.cpp, there are the polygon functions, and they use an alternate numbering system for the directions to the constraints of navigating a small array of function addresses for a speedup.


//////////
// Constant strings
//////
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
	#define oss_strlen(tcData)			vvm_scanForwardUntilCharacter(tcData, 0)
	#define defineCallback1(x, arg1) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													u64		(CALLBACK *callback_ ## x )( arg1 ); \
												};

	#define defineCallback2(x, arg1, arg2) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													u64		(CALLBACK *callback_ ## x )( arg1, arg2 ); \
												};
	#define defineCallback3(x, arg1, arg2, arg3) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													u64		(CALLBACK *callback_ ## x )( arg1, arg2, arg3 ); \
												};
	#define defineCallback4(x, arg1, arg2, arg3, arg4) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													u64		(CALLBACK *callback_ ## x )( arg1, arg2, arg3, arg4 ); \
												};
	#define defineCallback6(x, arg1, arg2, arg3, arg4, arg5, arg6) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													u64		(CALLBACK *callback_ ## x )( arg1, arg2, arg3, arg4, arg5, arg6 ); \
												};
	#define defineCallback7(x, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													u64		(CALLBACK *callback_ ## x )( arg1, arg2, arg3, arg4, arg5, arg6, arg7 ); \
												};
	#define defineCallback8(x, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
											u64 semaphore_ ## x; \
												union { \
													u64		_callback_ ## x; \
													u64		(CALLBACK *callback_ ## x )( arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8 ); \
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
	struct SBuilder;
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
	struct SBGRA;
	struct SBGRAF;
	struct SLLCallback;
	struct SLL4Callback;
	struct SStartEndCallback;
	struct SOssMouseEvent;
	struct SOssKbdEvent;
	struct SOssWindow;
	struct SOssLine;
	struct SOssComp;
	struct SCallbacksW;
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

	// Window callbacks
	struct SCallbackPartsWindow
	{
		defineCallback2( created,		u64 tnUniqueId, SOssWindow* tisw)																					// Called after window is created, before it is displayed
		defineCallback2( unload,		u64 tnUniqueId, SOssWindow* tisw)																					// Called when a window will be closed, while everything related to it is still viable
		defineCallback2( closed,		u64 tnUniqueId, SOssWindow* tisw)																					// Called after a window has been destroyed, before it is released by VVMOSS's internal lists of known windows
		defineCallback4( moved,			u64 tnUniqueId, SOssWindow* tisw, u32 tnXNew, u32 tnYNew)															// After a window has been moved from one place to another (not while it is moving)
		defineCallback4( resized,		u64 tnUniqueId, SOssWindow* tisw, u32 tnWidthNew, u32 tnHeightNew)													// After a window has been resized, and the buffers related to its screen have been allocated
		defineCallback2( gotFocus,		u64 tnUniqueId, SOssWindow* tisw)																					// After a window has received focus, and after the window that lost focus (if any) has been signaled
		defineCallback2( lostFocus,		u64 tnUniqueId, SOssWindow* tisw)																					// Before a new window receives focus
		// Simple templates to build from:
		//u64 CALLTYPE _window_created(u64 tnUniqueId, SOssWindow* tisw);
		//u64 CALLTYPE _window_unload(u64 tnUniqueId, SOssWindow* tisw);
		//u64 CALLTYPE _window_closed(u64 tnUniqueId, SOssWindow* tisw);
		//u64 CALLTYPE _window_moved(u64 tnUniqueId, SOssWindow* tisw, u32 tnXNew, u32 tnYNew);
		//u64 CALLTYPE _window_resized(u64 tnUniqueId, SOssWindow* tisw, u32 tnWidthNew, u32 tnHeightNew);
		//u64 CALLTYPE _window_gotFocus(u64 tnUniqueId, SOssWindow* tisw);
		//u64 CALLTYPE _window_lostFocus(u64 tnUniqueId, SOssWindow* tisw);
	};
	#define SCbPW SCallbackPartsWindow

	struct SCallbackPartsRegion
	{
		defineCallback1( enter,			SRegion* tr)																										// When the mouse moves into a region
		defineCallback1( leave,			SRegion* tr)																										// When the mouse leaves a region
		defineCallback3( paint,			SRegion* tr, SCanvas* tc, SBGRA* bd)																				// When the region needs repainted
		defineCallback3( debugTrap,		SRegion* tr, u64 tnIdentifier, u64 tnExtra);																		// When unexpected things happen, this will be called
		// Simple templates to build from:
		//u64 CALLTYPE _region_enter(SRegion* tr);
		//u64 CALLTYPE _region_leave(SRegion* tr);
		//u64 CALLTYPE _region_paint(SRegion* tr, SCanvas* tc, SBGRA* bd);
		//u64 CALLTYPE _region_debugTrap(SRegion* tr, u64 tnIdentifier, u64 tnExtra); // See the _VVM_DEBUGTRAP_* constants in common_vvmoss_const.h
	};
	#define SCbPO SCallbackPartsObject

	struct SCallbackPartsMouse
	{
		defineCallback6( down,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)										// When a mouse button is pressed down
		defineCallback6( up,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)										// When a mouse button is released
		defineCallback6( move,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)										// When a mouse is moved either with its buttons down or up
		defineCallback8( hover,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing)	// When a mouse has positioned itself at a fixed location for a period of time after previously moving
		// Simple templates to build from:
		//u64 CALLTYPE _mouse_down(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
		//u64 CALLTYPE _mouse_up(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
		//u64 CALLTYPE _mouse_move(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
		//u64 CALLTYPE _mouse_hover(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds, bool tlClosing);
	};
	#define SCbPM SCallbackPartsMouse

	struct SCallbackPartsKeyboard
	{
		defineCallback6( down,			u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)								// When a key is pressed down, or when the OS sends repeated keystrokes if it is a repeating key which is held down
		defineCallback6( up,			u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)								// When a key is released
		defineCallback6( press,			u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)								// When a key is pressed and interpreted to a known key
		defineCallback4( flags,			u64 tnUniqueId, SOssWindow* tisw, u32 tnKeyFlagsOld, u32 tnKeyFlagsNew)												// When keyboard flags change (such as a non-printable key going up and down, like shift, caps lock, or control)
		// Simple templates to build from:
		//u64 CALLTYPE _keyboard_down(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
		//u64 CALLTYPE _keyboard_up(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
		//u64 CALLTYPE _keyboard_press(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode);
		//u64 CALLTYPE _keyboard_flags(u64 tnUniqueId, SOssWindow* tisw, u32 tnKeyFlagsOld, u32 tnKeyFlagsNew);
	};
	#define SCbPK SCallbackPartsKeyboard

	struct SCallbackPartsDrag
	{
		defineCallback6( start,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys)										// When any mouse button has been depressed and the mouse has moved more than a minimal number of pixels
		defineCallback7( dragging,		u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds)					// Called as each MouseMove event while dragging
		defineCallback7( drop,			u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds)					// Called when the mouse button initiating the drag is released
		// Simple templates to build from:
		//u64 CALLTYPE _drag_start(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys);
		//u64 CALLTYPE _drag_dragging(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds);
		//u64 CALLTYPE _drag_drop(u64 tnUniqueId, SOssWindow* tisw, u32 tnX, u32 tnY, u32 tnButtons, u32 tnKeys, u64 tnMilliseconds);
	};
	#define SCbPD SCallbackPartsDrag

	struct SCallbackPartsCustom
	{
		defineCallback4( custom,			u64 tnUniqueId, SOssWindow* tisw, u64 tnCustomEventId, u64 tnOtherData)											// Called when to when a custom event is triggered programmatically
		// Simple templates to build from:
		//u64 CALLTYPE _custom_custom(u64 tnUniqueId, SOssWindow* tisw, u64 tnCustomEventId, u64 tnOtherData);
	};
	#define SCbPC SCallbackPartsCustom

	// Generic callbacks
	struct SCallbacksW
	{
		// Used also in SCallbacks
		// If a semaphore exists for any defined callback (it is non-NULL),
		// it is locked immediately before,
		// and unlocked immediately after, example:  u64 semaphore_x;
		SCallbackPartsWindow		window;
		SCallbackPartsRegion		region;
		SCallbackPartsMouse			mouse;
		SCallbackPartsKeyboard		keyboard;
		SCallbackPartsDrag			drag;
		SCallbackPartsCustom		custom;
	};
	#define SCbW SCallbacksW

	// Callbacks for everything except window controls
	struct SCallbacks
	{
		SCallbackPartsRegion		region;
		SCallbackPartsMouse			mouse;
		SCallbackPartsKeyboard		keyboard;
		SCallbackPartsDrag			drag;
		SCallbackPartsCustom		custom;
	};
	#define SCb SCallbacks

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
	const u32 _LL4_ALL			= 16;			// Go out in every direction (only valid on vvm_ll4_deleteChain() and vvm_ll4_deleteChainWithCallback())
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
	struct SBuilder
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
		SDatum		filenameSearched;									// The filename being searched for
		SDatum		pathnameOfSearch;									// The parent path where we looked, such as the ".\plugin\" portion in the name ".\plugin\plugin.dll"

		SDatum		file;												// The found filename (as in "pluginSomething.dll")
		SDatum		file2;												// An alternate name for the file (as in "PLUGIN~1.DLL")

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

	struct SBGRA
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

	struct SXYS32
	{
		s32			x;
		s32			y;
	};

	struct SXYF32
	{
		f32			x;
		f32			y;
	};

	struct SXYF64
	{
		f64			x;
		f64			y;
	};

	struct SRTF32
	{
		f32			radius;
		f32			theta;
	};

	struct SRTF64
	{
		f64			radius;
		f64			theta;
	};

	struct SPointF32
	{
		SXYF32		point;						// Point
		SRTF32		trig;						// Radius and theta
	};

	struct SPointF64
	{
		SXYF64		point;						// Point
		SRTF64		trig;						// Radius and theta
	};

	struct SMMPF32
	{
		f32			m;							// Slope
		f32			mp;							// Perpendicular slope
	};

	struct SMMPF64
	{
		f64			m;							// Slope
		f64			mp;							// Perpendicular slope
	};

	struct SRectXYWH
	{
		u32			x;
		u32			y;
		u32			width;
		u32			height;
	};

	struct SRectXYXY
	{
		u32			ulx;
		u32			uly;
		u32			lrx;
		u32			lry;
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

	// This is a compute accumulator.
	// It is used inside a builder to rapidly allocate structures used in creating the final product.
	// This compute component represents a mathematical operation to take some source data and apply
	// it do the destination, without having to re-compute what to do on successive operations.
	// Typically the first time through it is computed, then applied, then on successive times through
	// it is simply applied.  It is only re-computed when it has been deleted and is no longer
	// available.  Each compute relates to its parent, which is something like a scale operation,
	// a rotate operation, a polygon operation, etc.
	struct SBGRACompute
	{
		// For an example, refer to the oss_canvasScale() functionality of how this structure is used
		union {
			u32			start;					// For lines, the starting offset (lower value)
			u32			offsetSrc;				// Offset to the source SBGRA pixel
			s32			x;						// X coordinate
			f32			fx;						// X coordinate in floating point space
			// This structure is used for when there needs to be a starting and ending x,y coordinate set
			struct {
				s16		xStart;
				s16		yStart;
			};
		};

		union {
			u32			end;					// For lines, the ending offset (greater value)
			u32			offsetDst;				// Offset to the destination SBGRA pixel
			s32			y;						// Y coordinate
			f32			fy;						// Y coordinate in floating point space
			// This structure is used for when there needs to be a starting and ending x,y coordinate set
			struct {
				s16		xEnd;
				s16		yEnd;
			};
		};

		f64				alpha;					// The alpha percentage for the pixel
		// Note:  If using an accumulator, then dst += source * alpha
		// Note:  If alpha blending, then dst = (dst * 1.0 - alpha) + (source * alpha)
	};

	struct SScaleMap
	{
		// Refer to the oss_canvasScale() functionality
		SLL*			next;					// Pointer to next scale map in the chain
		SSize			src;					// Width of the source SBGRA
		SSize			dst;					// Width of the destination SBGRA
		SBuilder*		scaleData;				// The mathematical progression to use for this scale (SBbgraCompute array)
	};

	struct SRotateMap
	{
		// Refer to the oss_canvasRotate() and oss_canvasRotateAbout() functionality
		SLL*			next;					// Pointer to next scale map in the chain
		SRectXYWH		src;					// X, Y, width and height of the source SBGRA
		SBuilder*		scale_Data;				// The mathematical progression to use for this scale (SBbgraCompute array)
	};

	struct STriangleF64
	{
		// Points of the triangle can start anywhere
		SXYF64		p1;
		SXYF64		p2;
		SXYF64		p3;

		f64			p1_p2;						// Length of p1..p2
		f64			p2_p3;						// Length of p2..p3
		f64			p3_p1;						// Length of p3..p1

		f64			sp;							// Semiperimeter:  s = (l12 + l23 + l31) / 2
		f64			area;						// Heron's formula:  area = sqrt(s * (s - l12) * (s - l23) * (s - l31))
	};

	struct STriangleInOutF64
	{
		STriangleF64*	input;					// The input STriangle structure
		STriangleF64*	output;					// The computed output values after manipulation
	};

	struct SSquareF64
	{
		// Points proceed clockwise from upper-left.  I use upper-left because on a video display, upper-left is 0,0 which, on the number lines, would be the origin
		SXYF64		p1;							// Upper-left
		SXYF64		p2;							// Upper-right
		SXYF64		p3;							// Lower-right
		SXYF64		p4;							// Lower-left
	};

	struct SSquareComputeF64
	{
		SXYF64		center;						// Center point of the square
		SXYF64		origin;						// Origin point (used for rotation or scaling)

		// Computed point data
		SRTF64		p1rt;						// p1 radius and theta relative to center
		SRTF64		p2rt;						// p1 radius and theta relative to center
		SRTF64		p3rt;						// p1 radius and theta relative to center
		SRTF64		p4rt;						// p1 radius and theta relative to center

		SXYF64		p1_p2mid;					// p1..p2 midpoint 
		SXYF64		p2_p3mid;					// p2..p3 midpoint 
		SXYF64		p3_p4mid;					// p3..p4 midpoint 
		SXYF64		p4_p1mid;					// p4..p1 midpoint 

		// Computed side data
		f64			p1_p2;						// Length of p1..p2
		f64			p2_p3;						// Length of p2..p3
		f64			p3_p4;						// Length of p3..p4
		f64			p4_p1;						// Length of p4..p1
		f64			p1_p3;						// Hypotenuse, should be the same as p2_p4, but we don't compute that one

		// Computed side slope data
		SMMPF64		p1_p2mmp;					// p1's m and mp
		SMMPF64		p2_p3mmp;					// p2's m and mp
		SMMPF64		p3_p4mmp;					// p3's m and mp
		SMMPF64		p4_p1mmp;					// p4's m and mp
	};

	struct SSquareInOutF64
	{
		SSquareF64*			input;				// The input square
		SSquareComputeF64*	compute;			// Other computed data for this square
		SSquareF64*			output;				// Output square
	};

	struct SLineF64
	{
		union {
			SXYF64	start;						// [input] Starting point
			SXYF64	p1;
		};

		union {
			SXYF64	end;						// [input] Ending point
			SXYF64	p2;
		};

		// The following are computed with vvm_math_computeLine()
		SXYF64		delta;						// Delta between start and end
		SXYF64		mid;						// Midpoint
		union {
			f64		length;						// Length
			f64		radius;						// Radius for the trig function
		};
		f64			m;							// Slope
		f64			mp;							// Perpendicular slope

		// Only used and computed if trig is true
		bool		trig;						// Should trig functions be computed?
		f64			theta;						// Theta (from p1 to p2, note: add _PI to reverse the angle from p2 to p1)

		// Only used and computed if ints is true
		bool		ints;						// Should integer approximations be calculated?
		union {
			SXYS32	starti;						// Starting x,y
			SXYS32	p1i;
		};
		union {
			SXYS32	endi;						// Ending x,y
			SXYS32	p2i;
		};

		// Only used and computed if quads is true
		bool		quads;						// Should we compute quadrants?
		union {
			s32		start_quad;					// What quadrant is start/p1 in?
			s32		p1_quad;
		};
		union {
			s32		end_quad;					// What quadrant is end/p2 in?
			s32		p2_quad;
		};
	};

	struct SPolyLine
	{
		SXYF64		start;						// Where this line starts
		SXYF64		end;						// Where this line ends
		SXYF64		gravity;					// The side that should be filled in (a point somewhere that is to the left/right/top/bottom of the start..end line, depending on its slope -- typically, choose a point which is perpendicular out some distance from the midpoint of the start..end line)
	};

	struct SPolyTriangle
	{
		// Points of the triangle can start anywhere
		SXYF64		p1;
		SXYF64		p2;
		SXYF64		p3;
		f64			area;						// Heron's formula:  area = sqrt(s * (s - l12) * (s - l23) * (s - l31))
	};

	// Note:  A polygon should be complete, meaning it should start somewhere and return back to where it started.
	struct SPolygon
	{
		// Number of lines in the original polygon
		u32				lineCount;				// Number of polylines
		SPolyLine**		line;					// An array to access each polyline

		// The derived data for where they are drawn
		SBuilder*		pixelFloans;			// (SBGRACompute) Individual pixel floans, at the indicated x,y
		SBuilder*		rangeFloans;			// (SBGRACompute) A range of floans to write beginning at start, ending at end (poetic, isn't it?)
	};

	struct SBezier
	{
		// Beziers are either 3-point, 4-point, or 5-point (so far), and we compute fx,fy floan data
		// This allows them to be drawn later using applied polygons as per the target resolution.
		u32				curveCount;				// Number of control points comprising the bezier curve
		u32				computePointCount;		// Number of step points to compute/generate for the bezier curve (higher = more round, lower = more jagged)
		SBGRA			color;					// The color to draw in

		// Based on the number of points, some of these may not be populated or used
		SXYF64			p1;						// First point
		SXYF64			p2;						// Second point
		SXYF64			p3;						// Third point (used when points >= 3)
		SXYF64			p4;						// Fourth point (used when points >= 4)
		SXYF64			p5;						// Fifth point (used when points >= 5)

		// Holds each point generated for the Bezier curve
		bool			wash;					// The bezier drawing algorithm can compute raw points, or it can wash them to be either only the X- and Y-Intercepts for pixel borders, or for drawing onto a canvas.  This is determined by this setting, and whether or not a valid SCanvas and SBGRA were passed to the computation algorithm.
		SBuilder*		pointFloans;			// (SXYF64) The individually generated points
		SBuilder*		washFloans;				// (SBGRACompute, fx, fy, alpha) The points washed to pixel boundaries
		SBuilder*		drawFloans;				// (SBGRACompute, offsetDst, alpha) The draw floans for border points
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
			bool	(*funcBool)	(SStartEndCallback* cb);	// This callback should return false to continue searching, or true when the item is found
			void	(*funcVoid)	(SStartEndCallback* cb);
			//////
			// Uses the following format for the callback:
			//		bool func(SStartEndCallback* cb)
			//////////
		};

		// Data items for this callback
		// Primary pointer
		union {
			void*		ptr;
			SScreen*	ptrScreen;
			SRegion*	ptrRegion;
			SCanvas*	ptrCanvas;
			SBxml*		ptrBxml;
			SBxmla*		ptrBxmla;
		};

		union {
			// Extra1
			u64			ex1;
			u64			extra1;
			u64			extra;
			u64			count1;
			union {
				u32		count1_1;
				u32		count1_2;
			};
			void*		ex1Ptr;
			SScreen*	ex1PtrScreen;
			SRegion*	ex1PtrRegion;
			SCanvas*	ex1PtrCanvas;
			SBxml*		ex1PtrBxml;
			SBxmla*		ex1PtrBxmla;
		};

		union {
			// Extra2
			u64			ex2;
			u64			extra2;
			u64			count2;
			union {
				u32		count2_1;
				u32		count2_2;
			};
			void*		ex2Ptr;
			SScreen*	ex2PtrScreen;
			SRegion*	ex2PtrRegion;
			SCanvas*	ex2PtrCanvas;
			SBxml*		ex2PtrBxml;
			SBxmla*		ex2PtrBxmla;
		};
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

		// Note:  This window is displayed at the (osX,osY) coordinates for the upper-left corner
		// Note:  The width and height here are pixels, not physical window dimensions
		u32				width;								// Width of the client portion of the window
		u32				height;								// Height of the client portion of the window
		u32				widthMin;							// Minimum width the window can have (including the border)
		u32				heightMin;							// Minimum height the window can have (including the border)
		u32				widthMax;							// Maximum width the window can have (including the border)
		u32				heightMax;							// Maximum height the window can have (including the border)

		// Default colors
		SBGRA			foreColor;							// Default foreground color
		SBGRA			backColor;							// Default background color

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
		SCallbacksW		callback;							// Callback definitions (common.h)
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

		// Instance/application defined information
		void*			extraInfo;				// Extra info this screen stores which is application specific

		// Single-access is granted to multiple threads vying
		u64				semRefresh;				// Limit access to this screen
		bool			isRefreshing;			// Is this screen refreshing?

		// Associated region to this screen
		SRegion*		activeRegion;			// Pointer to this screen's first region, which must have a canvas

		// Internal information used to make it happen for the target OS
		u64				_iOssWindowId;			// OSS specific information for this instance (pointer to SOssWindow struct, for example)
	};



//////////
//
// Canvases are used exclusively for drawing.  They can exist independently, or as part of a
// region.  In that way, each canvas can be associated with a rectangle, allowing it to respond
// to events and redraw itself.  Each region can have sub-regions, allowing sub-components to
// be drawn upon the top of the region's canvas, allowing for complex controls to be constructed
// inside the VVM as they would be in a higher level language.
//
//////
	struct SCanvas
	{
		SLL				ll;						// 2-way link list
		u64				associatedId;			// The associated id, provided at creation for creator's private use and reference

		// Limited access is granted during a refresh operation, only the bd memory area is accessible publicly
		bool			isDirty;				// Has this canvas been drawn to?  Reset after each oss_canvasRefresh()
		u64				semRefresh;				// Limited access to 
		bool			isRefreshing;			// Is this canvas currently refreshing?  If yes, this means its children are also potentially busy.

		// All Canvas objects are always 32-bit RGBA format, even if they're ultimately rendered by the OS onto some lesser or greater color system
		s32				width;					// width (stored as s32 for easy comparison during drawing operations, will always be positive)
		s32				height;					// height (stored as s32 for easy comparison during drawing operations, will always be positive)
		SBGRA			backColor;				// A default back color to use for transparency operations

		// Bit buffers
		SBGRA*			bd;						// buffer data
		SBGRA*			bda;					// buffer data accumulator (for building child items onto this item)
		u64				bd_vvmoss;				// OS-specific information used for drawing OSS-fonts (used only by vvmoss code)

		// For scale operations
		SScaleMap*		firstScaleMap;			// List of computed scale maps (used for scaling operations)
	};




//////////
//
// Regions are rectangular single instance objects.  Each region may have a canvas, but does not
// have to, except for the first region associated with a screen, which must have a canvas.  If
// other regions do not have a canvas, it simply responds to events within its defined area.  This
// feature is used for the new mouseGlow features of Visual FreePro.  The mouseGlow is an area
// outside of the control which allows some action to take place when the mouse enters that outer
// region.  This allows the object to respond to mouse events in a space larger than it is drawn.
// This is useful for stand-alone controls which are a ways off, to aid in the user not having to
// exercise their precision mouse moving skills to click exactly on the control, but only close.
// In addition, for touch operations, it can also have added benefit for more rapid navigation.
//
// If a region has a canvas, then it will be drawn (re-drawn if dirty) whenever that region is
// updated with the vvm_screenRefresh() function.
//
//////
//
// The State condition is used on regions by the VVM to maintain their status, and determine how
// to handle messages issued by the VVMOSS.  It was separated out so entire states can be copied
// with a single operation, allowing entire blocks of controls to be changed in a similar motion.
//
//////
	// Used to indicate the state of settings on the root object, or an instance of its use
	struct SRegionState
	{
		// The state of a region or a region instance
		bool			isActive;				// Is this instance active? (does it respond to updates if/when it has focus? It still can even if it's not visible)
		bool			isVisible;				// Is this instance visible?
		bool			hasFocus;				// Does this instance have focus?
		bool			useCallbacks;			// Should callbacks be used for this instance?
		u32				tabOrder;				// -1=not a tab stop, 0 or greater, tab order
	};

	// Rectangular definitions
	struct SRegion
	{
		SLL				ll;						// 2-way link list
		u64				associatedId;			// The associated id, provided at creation for creator's private use and reference
		SScreen*		parentScreen;			// The screen this region belongs to
		SRegionState	state;					// Settings like active, focus, tab order, etc.

		// Instance/application defined information
		void*			extraInfo;				// Extra info this region stores which is application specific

		// Limited access is granted during a refresh operation
		u64				semRefresh;				// Limited access to 
		bool			isRefreshing;			// Is this region refreshing?

		// If this is a region that is drawn to, it has at least canvas defined.
		SCanvas*		canvas;					// Canvas for this region (if any, not all regions have a canvas)

		// If canvas is not the same size as the logical region, it must be scaled into that size
		SCanvas*		canvasScale;			// Canvas for scaling operations

		// Region information
		u32				type;					// Type of input, see _VVM_REGION_* constants
		void*			data;					// Based on the type of input, data may or may not be populated
		f32				x;						// Upper-left X coordinate (relative to the parent object)
		f32				y;						// Upper-left Y coordinate (relative to the parent object)
		f32				width;					// Width of the region (relative to the width of the parent object)
		f32				height;					// Height of the region (relative to the width of the parent object)
		// Note:  The x,y coordinates are assigned when they are applied to a canvas or other region as part of the SRegionList entry

		// Default region callbacks and sub-regions
		SCallbacks		callback;				// Callbacks for activities for this region
		SStartEnd		events;					// A list of user-defined events this region responds to	(SEvent*)
		SStartEnd		subRegions;				// A list of sub-regions within this one					(SRegion*)
	};

	// For standard controls, the data associated with each type
	// Note:  Each of these standard controls are low-level controls using the 8x14 font only.
	struct SRegionEditboxData
	{
		SDatum2			data;					// Whatever is being input
		u32				maxLength;				// Maximum length of input

		u32				fontWidth;				// Always 8
		u32				fontHeight;				// Can be 6, 8, -12, 14, 16, -16, etc.

		SBGRA			foreColor;				// Typically black
		SBGRA			backColor;				// Typically white
	};

	struct SRegionButtonData
	{
		SDatum			caption;

		u32				fontWidth;				// Always 8
		u32				fontHeight;				// Can be 6, 8, -12, 14, 16, -16, etc.

		SBGRA			foreColor;
		SBGRA			backColor;
	};

	struct SRegionImageData
	{
		SCanvas*		canvas;					// Canvas of the image
	};

	struct SRegionLabelData
	{
		SDatum			caption;

		u32				fontWidth;				// Always 8
		u32				fontHeight;				// Can be 6, 8, -12, 14, 16, -16, etc.

		SBGRA			foreColor;
		SBGRA			backColor;
	};

	struct SRegionCheckboxData
	{
		SDatum			caption;
		bool			checked;				// Is this control checked?

		u32				fontWidth;				// Always 8
		u32				fontHeight;				// Can be 6, 8, -12, 14, 16, -16, etc.

		SBGRA			foreColor;
		SBGRA			backColor;
	};

	struct SRegionRectangleData
	{
		bool			framed;					// Is this a framed-only rectangle?
		u32				borderWidth;

		SBGRA			borderColor;
		SBGRA			fillColor;
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
		SRectXYXY	rect;						// The coordinate range of this pip within the cask ((0,0) is upper-left)
		SCb			o;							// Callbacks for this pip

		// Pip colors can be anything
		SBGRA		colorNeutral;				// What color is displayed when there is no mouse activity?
		SBGRA		colorOver;					// What color is displayed when the mouse moves over it?
		SBGRA		colorClick;					// What color is displayed when the user clicks down on it?
	};

	struct SCaskSide
	{
		bool		active;						// Is this side active?
		SRectXYXY	rect;						// The coordinate range of this side within the cask ((0,0) is upper-left)
		u32			style;						// Closed, minimal, text, or extended text
		u32			pips;						// Supports 0 through 3
		SCb			o;							// Callbacks for this side


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

	struct SCaskText
	{
		bool		active;						// Is the text active?
		SRectXYXY	rect;						// The coordinate range of this text within the cask ((0,0) is upper-left)
		SCb			o;							// Callbacks for this text

		SBGRA		backColor;					// The back color
		SBGRA		foreColor;					// The fore color
		csu8p		text;						// Cask middle text
	};

	struct SCask
	{
		u32			style;						// [Standard plus round, square, diamond coupled to information in left and right], or encompassing rectangle, up rectangle, or down rectangle (all of which use the fixed semi-rounded form)
		SCb			o;							// Callbacks for this cask

		//////////
		// The canvas of the appropriately scaled item
		//////
			SCanvas*	canvas;
			SSize		size;					// If a standard cask, will be initially drawn in default resolution, and then scaled up or down to this level
												// If height is -1, will be natural height of whatever is required.  If width is -1, then will use natural width as required for indicated type


		//////////
		// Used only for standard types:
		//////
			SCaskSide*	left;					// Left-side cask information
			SCaskText*	text;					// Text information
			SCaskSide*	right;					// Right-side cask information


		//////////
		// Only used internally
		//////
			SCanvas*	_canvasRaw;				// The canvas of the original un-scaled item.  This canvas is used to copy or scale into the canvas.
	};
