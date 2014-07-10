//////////
//
// /libsf/source/vjr/vjr_const.h
//
//////
// Version 0.30
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




struct SVariable;


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
// Processing helpers
//////
	#define iVariable_isValid(var)					(var && var->value.data && var->value.length != 0)
	#define iVariable_getType(var)					var->varType


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
// Reference datetimes
//////
	SVariable*			_datetime_Jan_01_2000				= NULL;


//////////
// Min/max constants
//////
	const s8			_s8_min								= (s8)-128;
	const s8			_s8_max								= 127;
	const u8			_u8_max								= 255;
	const s16			_s16_min							= (s16)-32768;
	const s16			_s16_max							= 32767;
	const u16			_u16_max							= 65535;
	const s32			_s32_min							= 0xffffffff;
	const s32			_s32_max							= 0x7fffffff;
	const u32			_u32_max							= 0xffffffff;
	const s64			_s64_min							= 0xffffffffffffffff;
	const s64			_s64_max							= 0x7fffffffffffffff;
	const u64			_u64_max							= 0xffffffffffffffff;


//////////
// Object types
//////
	const u32			_OBJ_TYPE_EMPTY						= 0;						// Empty, used as a placeholder object that is not drawn
	const u32			_OBJ_TYPE_FORM						= 1;						// Form class, the main outer window the OS sees
	const u32			_OBJ_TYPE_SUBFORM					= 2;						// A new class which has its own drawing content and can be moved about using UI features
	const u32			_OBJ_TYPE_LABEL						= 3;						// A label
	const u32			_OBJ_TYPE_TEXTBOX					= 4;						// An input textbox
	const u32			_OBJ_TYPE_BUTTON					= 5;						// A push button
	const u32			_OBJ_TYPE_EDITBOX					= 6;						// An input multi-line editbox
	const u32			_OBJ_TYPE_IMAGE						= 7;						// A graphical image
	const u32			_OBJ_TYPE_CHECKBOX					= 8;						// A checkbox
	const u32			_OBJ_TYPE_OPTION					= 9;						// A combination selection
	const u32			_OBJ_TYPE_RADIO						= 10;						// A radio dial, which can also present as a slider or spinner


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
// Form border styles
//////
	const u32			_BORDER_STYLE_NONE					= 0;						// No border, not sizable
	const u32			_BORDER_STYLE_OUTLINE				= 1;						// Outline border, not sizable
	const u32			_BORDER_STYLE_FIXED					= 2;						// Normal border, not sizable
	const u32			_BORDER_STYLE_SIZABLE				= 3;						// Normal border, sizable


//////////
// Form scale mode
//////
	const u32			_SCALE_MODE_FOXELS					= 0;						// Foxels, based on sysmetrics() average font width and height
	//const u32			_SCALE_MODE_INCHES					= 1;						// Inches, based on correlating inches to default dpi
	const u32			_SCALE_MODE_PIXELS					= 3;						// Pixels, based on individual pixels


//////////
// Form window state
//////
	const u32			_WINDOW_STATE_NORMAL				= 0;						// Normal
	const u32			_WINDOW_STATE_MINIMIZED				= 1;						// Minimized
	const u32			_WINDOW_STATE_MAXIMIZED				= 2;						// Maximized


//////////
// Object mouse pointers
//////
	const u32			_MOUSE_POINTER_DEFAULT				= 0;
	const u32			_MOUSE_POINTER_ARROW1				= 1;
	const u32			_MOUSE_POINTER_CROSS				= 2;
	const u32			_MOUSE_POINTER_I_BEAM				= 3;
	const u32			_MOUSE_POINTER_ICON					= 4;
	const u32			_MOUSE_POINTER_SIZE					= 5;
	const u32			_MOUSE_POINTER_SIZE_NE_SW			= 6;
	const u32			_MOUSE_POINTER_SIZE_NS				= 7;
	const u32			_MOUSE_POINTER_SIZE_NW_SE			= 8;
	const u32			_MOUSE_POINTER_SIZE_W_E				= 9;
	const u32			_MOUSE_POINTER_UP_ARROW				= 10;
	const u32			_MOUSE_POINTER_HOURGLASS			= 11;
	const u32			_MOUSE_POINTER_NO_DROP				= 12;
	const u32			_MOUSE_POINTER_HIDE_POINTER			= 13;
	const u32			_MOUSE_POINTER_ARROW2				= 14;
	const u32			_MOUSE_POINTER_HAND					= 15;
	const u32			_MOUSE_POINTER_DOWN_ARROW			= 16;
	const u32			_MOUSE_POINTER_MAGNIFYING_GLASS		= 17;
	const u32			_MOUSE_POINTER_CUSTOM				= 18;


//////////
// Object anchor mode bit masks
// Note:  If conflicting values are attempted, they are ignored.
//////
	const u32			_ANCHOR_FIXED_NORESIZE				= 0;
	const u32			_ANCHOR_TOP_ABSOLUTE				= 1;
	const u32			_ANCHOR_LEFT_ABSOLUTE				= 2;
	const u32			_ANCHOR_BOTTOM_ABSOLUTE				= 4;
	const u32			_ANCHOR_RIGHT_ABSOLUTE				= 8;
	const u32			_ANCHOR_TOP_RELATIVE				= 16;
	const u32			_ANCHOR_LEFT_RELATIVE				= 32;
	const u32			_ANCHOR_BOTTOM_RELATIVE				= 64;
	const u32			_ANCHOR_RIGHT_RELATIVE				= 128;
	const u32			_ANCHOR_DO_NOT_RESIZE_HORIZONTALLY	= 256;
	const u32			_ANCHOR_DO_NOT_RESIZE_VERTICALLY	= 512;


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
// Internal messages
//////
	const u32			WMVJR_FIRST_CREATION				= WM_USER + 1;


//////////
// Constant strings
//////
	const s8			cgcMessageWindowClass[]				= "VJr.MessageWindow";
	const s8			cgcWindowClass[]					= "VJr.Window";
	const s8			cgcScreenTitle[]					= "Visual FreePro, Jr. 0.29 -- Jul.09.2014";
	const s8			cgcJDebiTitle[]						= "JDebi Debugger 0.29 -- Jul.09.2014";
	const s8			cgcDefaultFont[]					= "Ubuntu";
	const s8			cgcDefaultFixedFont[]				= "Ubuntu Mono";
	const s8			cgcWindowTitleBarFont[]				= "Ubuntu Condensed";
	const s8			cgcSubwindowTitleBarFont[]			= "Ubuntu Condensed";


//////////
// Base class control names
//////
	const s8			cgcName_empty[]						= "empty";
	const s8			cgcName_form[]						= "form";
	const s8			cgcName_subform[]					= "subform";
	const s8			cgcName_label[]						= "label";
	const s8			cgcName_textbox[]					= "textbox";
	const s8			cgcName_button[]					= "button";
	const s8			cgcName_editbox[]					= "editbox";
	const s8			cgcName_image[]						= "image";
	const s8			cgcName_checkbox[]					= "checkbox";
	const s8			cgcName_option[]					= "option";
	const s8			cgcName_radio[]						= "radio";


//////////
// Auto-added child object names
//////
	const s8			cgcName_icon[]						= "_icon";								// Forms automatically get an app icon
	const s8			cgcCaption_icon[]					= "_caption";							// Forms, subforms automatically get a caption
	const s8			cgcName_iconMove[]					= "_move";								// Forms automatically get a move button (to move any subforms within using bars)
	const s8			cgcName_iconMinimize[]				= "_minimize";							// Forms automatically get a minimize button
	const s8			cgcName_iconMaximize[]				= "_maximize";							// Forms automatically get a maximize button
	const s8			cgcName_iconClose[]					= "_close";								// Forms automatically get a close button
