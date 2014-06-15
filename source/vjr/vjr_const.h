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
// Textbox styles
//////
	const u32			_TEXTBOX_STYLE_PLAIN				= 0;
	const u32			_TEXTBOX_STYLE_2D					= 1;
	const u32			_TEXTBOX_STYLE_3D					= 2;


//////////
// Editbox styles
//////
	const u32			_EDITBOX_STYLE_PLAIN				= 0;
	const u32			_EDITBOX_STYLE_2D					= 1;
	const u32			_EDITBOX_STYLE_3D					= 2;


//////////
// Button styles
//////
	const u32			_BUTTON_STYLE_PLAIN					= 0;
	const u32			_BUTTON_STYLE_2D					= 1;
	const u32			_BUTTON_STYLE_3D					= 2;


//////////
// Checkbox styles
//////
	const u32			_CHECKBOX_STYLE_PLAIN				= 0;
	const u32			_CHECKBOX_STYLE_2D					= 1;
	const u32			_CHECKBOX_STYLE_3D					= 2;


//////////
// Constant strings
//////
	const s8			cgcMessageWindowClass[]				= "VJr.MessageWindow";
	const s8			cgcScreenWindowClass[]				= "VJr.ScreenWindow";
	const s8			cgcJDebiWindowClass[]				= "VJr.JDebiWindow";
	const s8			cgcScreenTitle[]					= "Visual FreePro, Jr.";
	const s8			cgcJDebiTitle[]						= "JDebi Debugger";
	const s8			cgcWindowTitleBarFont[]				= "Ubuntu";
	const s8			cgcSubwindowTitleBarFont[]			= "Ubuntu Condensed";
