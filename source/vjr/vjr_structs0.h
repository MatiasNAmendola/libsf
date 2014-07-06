//////////
//
// /libsf/source/vjr/vjr_structs0.h
//
//////
// Version 0.30
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




// Forward definition for references
struct SObject;
struct SVariable;
struct SEditChainManager;
struct SEditChain;
struct SComp;
struct SCompiler;
struct SFunction;




struct SBgr
{
	u8	blu;
	u8	grn;
	u8	red;
};

struct SBgra
{
	union {
		u32		color;
		struct {
			u8	blu;
			u8	grn;
			u8	red;
			u8	alp;
		};
	};
};


struct SBgraf
{
	f32		blu;				// 24-bit RGB values in bitmap files are physically stored as BGR
	f32		grn;
	f32		red;
	f32		alp;				// For 32-bit bitmaps

	f32		area;				// Holds area
};

struct SBitmap
{
	// Device context and bitmap handle to this data
	HDC					hdc;
	HBITMAP				hbmp;

	// Raw bitmap data (suitable for writing to disk)
	BITMAPFILEHEADER	bh;
	BITMAPINFOHEADER	bi;
	s8*					bd;
	u32					rowWidth;
};


// For processing the scaling of bitmaps
struct SBitmapProcess
{
	// Holds the source canvas
	SBitmap*			src;

	// Holds storage data for single spanned pixels
	u32					red;
	u32					grn;
	u32					blu;
	u32					alp;

	// tpoints is a buffer created to store the conversion pixel data during accumulation.
	// Use formula:
	//		tpoints	= (SRGBAF*)malloc(		((u32)(1.0/ratioV) + 3)   *
	//										((u32)(1.0/ratioH) + 3))
	//
	f32					ratioV;				// (f32)bio->biHeight	/ (f32)bii->biHeight;
	f32					ratioH;				// (f32)bio->biWidth	/ (f32)bii->biWidth;
	u32					count;				// Number of valid points in tpoints
	SBgraf*				pixels;				// Accumulation buffer for point data needed to feed into destination

	// Temporary variables used for processing
	union {
		SBgra*			optra;				// (For 32-bit bitmaps) Output pointer to the upper-left pixel for this x,y
		SBgr*			optr;				// (For 24-bit bitmaps) Output pointer to the upper-left pixel for this x,y
	};
	union {
		SBgra*			iptrAnchora;		// (For 32-bit bitmaps) Input pointer to the left-most pixel of the first row (the anchor)
		SBgr*			iptrAnchor;			// (For 24-bit bitmaps) Input pointer to the left-most pixel of the first row (the anchor)
	};
	union {
		SBgra*			iptra;				// (For 32-bit bitmaps) Input pointer to the left-most pixel for this y row
		SBgr*			iptr;				// (For 24-bit bitmaps) Input pointer to the left-most pixel for this y row
	};
	f32					ulx;				// Upper-left X
	f32					uly;				// Upper-left Y
	f32					lrx;				// Lower-right X
	f32					lry;				// Lower-right Y
	f32					widthLeft;			// Width for each left-most pixel
	f32					widthRight;			// Width for each right-most pixel
	f32					height;				// Height for a particular pixel portion (upper, lower)
	f32					area;				// Temporary computed area for various pixels
	s32					left;				// Left-side pixel offset into line
	s32					right;				// Number of pixels to reach the right-most pixel
	s32					middleStartH;		// Starting pixel offset for middle span
	s32					middleFinishH;		// Ending pixel offset for middle span
	s32					middleStartV;		// Middle starting pixel
	s32					middleFinishV;		// Middle ending pixel

	// Indicates the span from upper-left corner
	bool				spans2H;			// Spans at least 2 pixels horizontally, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 2.x
	bool				spans3H;			// Spans at least 3 pixels horizontally, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 3.x
	bool				spans2V;			// Spans at least 2 pixels vertically, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 2.x
	bool				spans3V;			// Spans at least 3 pixels vertically, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 3.x
};

struct SSize
{
	union {
		s32		width;
		f32		fWidth;
	};
	union {
		s32		height;
		f32		fHeight;
	};
};

struct SRect
{
	s32			left;
	s32			top;
	s32			right;
	s32			bottom;
};

struct SXYS32
{
	s32			x;
	s32			y;
};

struct SWindow
{
	bool				isValid;										// When windows fall out of scope they are marked not valid

	HWND				hwnd;											// The window's hwnd
	RECT				rc;												// Rectangle of window's physical position
	SObject*			obj;											// The top-level object being rendered in this window

	SXYS32				mousePosition;									// Mouse position in this window
	bool				isMouseLeftButton;								// Is the left mouse button down?
	bool				isMouseMiddleButton;							// Is the middle mouse button down?
	bool				isMouseRightButton;								// Is the right mouse button down?
	bool				isMoving;										// Is this window moving?
	bool				isResizing;										// Is this window resizing?
	u32					resizingFrom;									// If resizing, the arrow (upper-left, upper-right, lower-left, lower-right)

	// Updated as the mouse moves across the form
	SXYS32				mouseLastPosition;								// The last recorded position of the mouse on the form (the mouse may have moved off the form and is somewhere else, but this is the last point)
	SXYS32				mousePositionClick;								// When the mouse was last left-clicked, this is where it was clicked
	SXYS32				mousePositionClickScreen;						// In screen coordinates, the location where the mouse was last left-button clicked down
	bool				isMouseInClientArea;							// When the mouse is in the client area (not on the form border)

	CRITICAL_SECTION	cs;												// Atomic access
};

struct SDatum
{
	union {
		s8*		data;													// Content
		u8*		udata;													// Access to it as unsigned
	};
	u32			length;													// Content length
};

struct STranslate
{
	void*		p1;														// Pointer 1
	void*		p2;														// Pointer 2
};

// struct STranslateExtra
// {
// 	void*		p1;														// Pointer 1
// 	void*		p2;														// Pointer 2
// 
// 	// Extra information
// 	union {
// 		struct {
// 			u8		u8Data1;
// 			u8		u8Data2;
// 			u8		u8Data3;
// 			u8		u8Data4;
// 		};
// 		struct {
// 			s8		s8Data1;
// 			s8		s8Data2;
// 			s8		s8Data3;
// 			s8		s8Data4;
// 		};
// 		struct {
// 			u16		u16Data1;
// 			u16		u16Data2;
// 		};
// 		struct {
// 			s16		s16Data1;
// 			s16		s16Data2;
// 		};
// 		u32		u32Data;
// 		s32		s32Data;
// 		bool	used;
// 		void*	extra;
// 	};
// };

struct SLL
{
	SLL*			next;					// Next entry in linked list
	SLL*			prev;					// Previous entry in linked list
	u32				uniqueId;				// Unique id associated with this object
};

struct SVariable
{
	SLL			ll;
	SVariable*	indirect;												// If non-NULL, this variable is an indirect reference to an underlying variable

	// Variable data
	SDatum		name;													// Name of this variable

	// Variable content based on type
	u32			var_type;												// Variable type (see _VAR_TYPE_* constants)
	bool		isVarAllocated;											// If true, it was a variable that was allocated, and needs to be released.
	union {
		SObject*		obj;											// If the lower-bit of type is clear, and it's an object, the object it relates to
		SFunction*		thisCode;										// Pointer to the code block this relates to
		SDatum			value;											// If the lower-bit of type is clear, the actual data value based on its type
	};

	// If assign or access
	SFunction*	assign;													// Source code executed whenever this variable is assigned
	SFunction*	access;													// Source code executed whenever this variable is accessed

	// Used only during compilation
	bool		isStale;												// Variables are marked stale if the line they're defined on changes and needs recompiled.
																		// Once recompiled, if the variable declaration still exists, the isStale flag is lowered.
																		// If the variable no longer exists, any lines of code referencing the old variable are
																		// marked for recompilation and errors will likely be generated.
																		// To avoid this issue, use symbol refactoring in the IDE.
};
