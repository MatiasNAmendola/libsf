//////////
//
// /libsf/source/vjr/vjr_structs.h
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



// Forward definition for references
struct SObject;




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


// For scaling bitmaps
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


struct SFont
{
	HDC			hdc;
	HFONT		hfont;

	s8*			name;
	u32			nameLength;
	s32			sizeUsedForCreateFont;
	u32			size;
	u32			weight;
	u32			italics;
	u32			underline;
	TEXTMETRIC	tm;
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

struct SGeneralEvents
{
	// Called in this order
	bool		(*load)			(SObject* o);							// Called to load anything needed by the init() event (holds a template/skeleton object)
	// Note:  If load() returns false, the object is not created
	void		(*init)			(SObject* o);							// Called to initialize anything
	void		(*created)		(SObject* o);							// Called after initialization, before the object is sized
	void		(*resize)		(SObject* o, u32* widthRequired_out, u32* heightRequired_out);	// Called to size or resize the object
	bool		(*render)		(SObject* o);							// Called to render to bmp (returns if anything was drawn)
	bool		(*publish)		(SObject* o);							// Called to publish the control onto the parent (which will populate bmpScale if need be)
	void		(*destroy)		(SObject* o);							// Called when the object will be destroyed
	void		(*unload)		(SObject* o);							// Called after the object has been destroyed, to unload anything (holds a template/skeleton object)
};

struct SMouseEvent
{
	// Holds status for changes
	u32			_lastClick;
	bool		isMouseOver;											// Used for signaling enter/leave events
	u64			startHoverTimer;										// At each last mouseMove the startHoverTimer is set, if the interval elapses the hover event is triggered

	// Mouse callbacks
	// Bool indicates if the event should be sent to its parent instead
	bool		(*clickex)		(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);	// 1=left, 2=middle, 4=right, 2^n bit positions indicate which buttons are clicked
	bool		(*wheel)		(SObject* o, s32 tnUnits);				// Signed units indicating direction and velocity
	bool		(*move)			(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);	// Coordinates for the move
	bool		(*down)			(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick, u32 tnLastClick);	// Coordinates for where the mouse button changed
	bool		(*up)			(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick, u32 tnLastClick);	// Coordinates for where the mouse button changed
	bool		(*enter)		(SObject* o);							// When mouse enters an object
	bool		(*leave)		(SObject* o);							// When mouse leaves an object
	bool		(*hover)		(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);	// Coordinates where hovering
};

struct SKeyboardEvent
{
	// Keyboard callbacks
	// Bool indicates if the event should be sent to its parent instead
	bool		(*keyDown)		(SObject* o, bool tlCtrl, bool tlAlt, bool tlShift, s16 tcAscii, u16 tnVKey, bool tlIsCAS, bool tlIsAscii);
	bool		(*keyUp)		(SObject* o, bool tlCtrl, bool tlAlt, bool tlShift, s16 tcAscii, u16 tnVKey, bool tlIsCAS, bool tlIsAscii);
};

struct SEvents
{
	SGeneralEvents	general;											// General object events
	SMouseEvent		mouse;												// Mouse events for the object
	SKeyboardEvent	keyboard;											// Keyboard events for the object
};

struct SObject
{
	u32			type;													// Object type (see _OBJECT_TYPE_* constants)
	bool		isEnabled;												// If it is responding to events
	bool		hasFocus;												// Does this object have focus?
	bool		isRendered;												// Is it rendered (can be rendered even if it's not visible)?
	bool		isVisible;												// If it's visible
	bool		isDirty;												// Is set if this or any child object needs re-rendered

	// Events
	SEvents		ev;														// Events for this object
	void*		obj_data;												// Varies by type
	SObject*	parent;													// Parent object (if available, may not be populated)
	SObject*	firstObj;												// Pointer to child objects

	//////////
	// Object size in pixels
	//////
		RECT		rc;													// Object's current position in its parent
		RECT		rco;												// Object's original position in its parent
		RECT		rcp;												// Original size of parent at creation
		u32			anchorMode;											// Method this item uses when its parent is resized

	//////////
	// Drawing canvas
	//////
		SBitmap*	bmp;												// If exists, canvas for the content
		// If not scaled:
		s32			scrollOffsetX;										// If the bmp->bi coordinates are larger than its display area, the upper-left X coordinate
		s32			scrollOffsetY;										// ...the upper-left Y coordinate
		// If scaled, updated only during publish():
		bool		isScaled;											// If the bmp->bi coordinates are larger than its display area, should it be scaled?
		SBitmap*	bmpScaled;											// The bmp scaled into RC's size
};

struct SObjectEmpty
{
	// _OBJECT_TYPE_EMPTY
	SObject*	parent;													// parent object this object belongs to
	u32			data1;													// User data 1
	u32			data2;													// User data 2
	u32			data3;													// User data 3
};

struct SObjectForm
{
	// _OBJECT_TYPE_FORM
	SObject*	parent;													// parent object this object belongs to
	u32			data1;													// User data 1
	u32			data2;													// User data 2
	u32			data3;													// User data 3
};

struct SObjectSubform
{
	// _OBJECT_TYPE_SUBFORM
	SObject*	parent;													// parent object this object belongs to
	u32			data1;													// User data 1
	u32			data2;													// User data 2
	u32			data3;													// User data 3
};

struct SObjectLabel
{
	// _OBJECT_TYPE_LABEL
	SObject*	parent;													// parent object this object belongs to
	u32			data1;													// User data 1
	u32			data2;													// User data 2
	u32			data3;													// User data 3
};

struct SObjectTextbox
{
	// _OBJECT_TYPE_TEXTBOX
	SObject*	parent;													// parent object this object belongs to
	u32			data1;													// User data 1
	u32			data2;													// User data 2
	u32			data3;													// User data 3
};

struct SObjectButton
{
	// _OBJECT_TYPE_BUTTON
	SObject*	parent;													// parent object this object belongs to
	u32			data1;													// User data 1
	u32			data2;													// User data 2
	u32			data3;													// User data 3
};

struct SObjectEditbox
{
	// _OBJECT_TYPE_EDITBOX
	SObject*	parent;													// parent object this object belongs to
	u32			data1;													// User data 1
	u32			data2;													// User data 2
	u32			data3;													// User data 3
};

struct SObjectImage
{
	// _OBJECT_TYPE_IMAGE
	SObject*	parent;													// parent object this object belongs to
	u32			data1;													// User data 1
	u32			data2;													// User data 2
	u32			data3;													// User data 3
};

struct SObjectCheckbox
{
	// _OBJECT_TYPE_CHECKBOX
	SObject*	parent;													// parent object this object belongs to
	u32			data1;													// User data 1
	u32			data2;													// User data 2
	u32			data3;													// User data 3
};

struct SObjectOption
{
	// _OBJECT_TYPE_OPTION
	SObject*	parent;													// parent object this object belongs to
	u32			data1;													// User data 1
	u32			data2;													// User data 2
	u32			data3;													// User data 3
};

struct SObjectRadio
{
	// _OBJECT_TYPE_RADIO
	SObject*	parent;													// parent object this object belongs to
	u32			data1;													// User data 1
	u32			data2;													// User data 2
	u32			data3;													// User data 3
};

struct SDatum
{
	s8*			data;													// Content
	u32			length;													// Content length
};

struct STextChain
{
	STextChain*	prev;													// Pointer backward to previous text item
	STextChain*	next;													// Pointer forward to next text item

	// The text
	SDatum		d;														// The text item

	// General purpose extra data
	void*		extraInfo;												// Other info that can be stored on this item

	// For selected areas
	s32			selectedStart;											// A general purpose selection, where it starts, or -1 if not used
	s32			selectedEnd;											// Where the selection ends, or -1 if not used
};

struct STextChainManager
{
	STextChain*	first;													// First in the chain (first->prev is NULL)
	STextChain*	last;													// Last in the chain (last->next is NULL)
};

struct SWindow
{
	RECT		rc;														// Rectangle of window's physical position
	SBitmap		bmp;													// Bitmap data for the window
	SObject		appIcon;												// Icon for the window
	SFont*		font;													// Default window font (Ubuntu 10)

	// Is the window scaled?
	bool		isScaled;												// If it's scaled, meaning bmp->bi is larger than rc
	SBitmap*	bmpScaled;												// Holds scaled window content

	// User-based flags
	bool		isMaximized;											// Is the window maximized?
	RECT		rcBeforeMaximize;										// Used when switching to/from maximized size, holds the window rectangle before the maximize

	// Rectangles for non-object drawn components
	RECT		rcCaption;												// Caption area
	RECT		rcClient;												// Client area where content is drawn

	// For the corner triangles
	SObject		arrowUl;
	SObject		arrowUr;
	SObject		arrowLr;
	SObject		arrowLl;

	// For mouse objects
	SObject		minimize;
	SObject		maximize;
	SObject		close;
	SObject		move;
};
