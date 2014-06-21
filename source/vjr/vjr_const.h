//////////
//
// /libsf/source/vjr/vjr_const.h
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.12.2014
//////
// Change log:
//     Feb.12.2014 - Initial creation
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




// Unsigned
typedef		unsigned __int64	u64;
typedef		unsigned long		u32;
typedef		unsigned short		u16;
typedef		unsigned char		u8;

// Signed
typedef		__int64				s64;
typedef		long				s32;
typedef		short				s16;
typedef		char				s8;

// Floating point
typedef		float				f32;
typedef		double				f64;

// Constant signed
typedef		const s8			cs8;
typedef		const s16			cs16;
typedef		const s32			cs32;
typedef		const s64			cs64;

// Constant unsigned
typedef		const u8			cu8;
typedef		const u16			cu16;
typedef		const u32			cu32;
typedef		const u64			cu64;

// Constant floating point
typedef		const f64			cf64;
typedef		const f64			cf64;


//////////
// Union helper
//////
	#define _union(x, y, z) union { x z; y _ ## z; };


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
// Object types
//////
	const u32			_OBJECT_TYPE_EMPTY					= 0;						// Empty, used as a placeholder object that is not drawn
	const u32			_OBJECT_TYPE_FORM					= 1;						// Form class, the main outer window the OS sees
	const u32			_OBJECT_TYPE_SUBFORM				= 2;						// A new class which has its own drawing content and can be moved about using UI features
	const u32			_OBJECT_TYPE_LABEL					= 3;						// A label
	const u32			_OBJECT_TYPE_TEXTBOX				= 4;						// An input textbox
	const u32			_OBJECT_TYPE_BUTTON					= 5;						// A push button
	const u32			_OBJECT_TYPE_EDITBOX				= 6;						// An input multi-line editbox
	const u32			_OBJECT_TYPE_IMAGE					= 7;						// A graphical image
	const u32			_OBJECT_TYPE_CHECKBOX				= 8;						// A checkbox
	const u32			_OBJECT_TYPE_OPTION					= 9;						// A combination selection
	const u32			_OBJECT_TYPE_RADIO					= 10;						// A radio dial, which can also present as a slider or spinner


//////////
// Image styles
//////
	const u32			_IMAGE_STYLE_OPAQUE					= 0;
	const u32			_IMAGE_STYLE_TRANSPARENT			= 1;


//////////
// Option styles
//////
	const u32			_STYLE_PLAIN						= 0;
	const u32			_STYLE_2D							= 1;
	const u32			_STYLE_3D							= 2;


//////////
// Alignment modes
//////
	const u32			_ALIGNMENT_LEFT						= 0;
	const u32			_ALIGNMENT_RIGHT					= 1;
	const u32			_ALIGNMENT_CENTER					= 2;


//////////
// Variable types
//////
	// Note:  Lower-bit is a flag:	0-variable, 1-reference to a variable
	const u32			_VARIABLE_TYPE_LOGICAL				= 0;						// Logical values are 0=.F., others=.T., and explicit values for 2=.O., 3=.P., 4=.X., 5=.Y., and 6=.Z. through SETLOGICALX() and GETLOGICALX()
	const u32			_VARIABLE_TYPE_NUMERIC				= 1 << 1;					// Maintains its value in converted-to-text form, but is numeric
	const u32			_VARIABLE_TYPE_CHARACTER			= 2 << 1;					// A character string
	const u32			_VARIABLE_TYPE_F32					= 3 << 1;					// A 32-bit floating point value with length and decimals
	const u32			_VARIABLE_TYPE_F64					= 4 << 1;					// A 64-bit floating point value with length and decimals
	const u32			_VARIABLE_TYPE_S8					= 5 << 1;					// An 8-bit signed integer
	const u32			_VARIABLE_TYPE_U8					= 6 << 1;					// An 8-bit unsigned integer
	const u32			_VARIABLE_TYPE_S16					= 7 << 1;					// A 16-bit signed integer
	const u32			_VARIABLE_TYPE_U16					= 8 << 1;					// A 16-bit unsigned integer
	const u32			_VARIABLE_TYPE_S32					= 9 << 1;					// A 32-bit signed integer
	const u32			_VARIABLE_TYPE_U32					= 10 << 1;					// A 32-bit unsigned integer
	const u32			_VARIABLE_TYPE_S64					= 11 << 1;					// A 64-bit signed integer
	const u32			_VARIABLE_TYPE_U64					= 12 << 1;					// A 64-bit unsigned integer
	const u32			_VARIABLE_TYPE_CURRENCY				= 13 << 1;					// A 64-bit signed integer with fixed length and decimals
	const u32			_VARIABLE_TYPE_DATE					= 14 << 1;					// A date
	const u32			_VARIABLE_TYPE_DATETIME				= 15 << 1;					// A datetime
	const u32			_VARIABLE_TYPE_DATETIMEX			= 16 << 1;					// A datetimex
	const u32			_VARIABLE_TYPE_BI					= 17 << 1;					// Big integer with length
	const u32			_VARIABLE_TYPE_BFP					= 18 << 1;					// Big floating with length and decimals
	const u32			_VARIABLE_TYPE_COLOR				= 19 << 1;					// An RGB() color
	const u32			_VARIABLE_TYPE_COLORA				= 20 << 1;					// An RGBA() color
	const u32			_VARIABLE_TYPE_ARRAY				= 80 << 1;					// Indicates the variable is an array
	const u32			_VARIABLE_TYPE_GUID8				= 90 << 1;					// GUID-8 byte form (automatically coordinated data across multiple physical locations of an application, even when offline)
	const u32			_VARIABLE_TYPE_GUID16				= 91 << 1;					// GUID-16 byte form (a form allowing for more unique records)
	const u32			_VARIABLE_TYPE_OBJECT				= 100 << 1;					// An object (class structure)
	const u32			_VARIABLE_TYPE_THISCODE				= 200 << 1;					// thisCode reference
	const u32			_VARIABLE_TYPE_FIELD				= 1000 << 1;				// A field from something with an alias


//////////
// Constant strings
//////
	const s8			cgcMessageWindowClass[]				= "VJr.MessageWindow";
	const s8			cgcWindowClass[]					= "VJr.Window";
	const s8			cgcScreenTitle[]					= "Visual FreePro, Jr.";
	const s8			cgcJDebiTitle[]						= "JDebi Debugger";
	const s8			cgcUbuntu[]							= "Ubuntu";
	const s8			cgcWindowTitleBarFont[]				= "Ubuntu";
	const s8			cgcSubwindowTitleBarFont[]			= "Ubuntu Condensed";
