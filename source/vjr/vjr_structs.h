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
struct SVariable;




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

struct SDatum
{
	s8*			data;													// Content
	u32			length;													// Content length
};

struct SEditChain
{
	SEditChain*	prev;													// Pointer backward to previous text item
	SEditChain*	next;													// Pointer forward to next text item

	u32			line;													// This line's number
	SDatum*		d;														// The text on this line is LEFT(d.data, dPopulated)
	u32			dPopulated;												// The actual populated length of d (d is allocated in blocks to allow for minor edits without constantly reallocating)

	// General purpose extra data
	void*		extra_info;												// Extra info that can be stored on this item
};

struct SUndo
{
	SEditChain*	before;													// The item before
	SEditChain*	after;													// The item after

	SEditChain*	first;													// The first SEditChain that would've gone between them
																		// If multiple lines were deleted, the chain is moved here.
																		// If the line was changed, the old value is here
};

struct SEditChainManager
{
	SEditChain*	first;													// First in the chain (first->prev is NULL)
	SEditChain*	last;													// Last in the chain (last->next is NULL)

	// For display
	SEditChain*	top;													// Top item in the current view
	SEditChain*	cursorLine;												// Line where the cursor is
	SEditChain*	cursorLineLast;											// The last location before movement was made

	// Selected lines
	SEditChain*	selectedLineStart;										// First line that's selected
	SEditChain*	selectedLineEnd;										// Last line that's selected
	// Note:  If not isColumn or isAnchor, then it is full line select.
	//        If isColumn, then column select mode.
	//        If isAnchor, then anchor select mode.
	bool		isColumn;												// If column select mode...
	u32			selectedColumnStart;									// Column select mode start
	u32			selectedColumnEnd;										// end
	bool		isAnchor;												// If anchor select mode...
	u32			selectedAnchorStart;									// Anchor select mode start
	u32			selectedAnchorEnd;										// end

	// undoHistory.extra_info holds the SUndo structure
	SEditChainManager*	undoHistory;									// The lines affected by the undo
};

struct SFont
{
	HDC			hdc;						// Device context used for its creation

	// Current font instance flags
	SDatum		name;						// Name of this font
	bool		isBold;						// Is the font bold? (Note: This is independent of the font name itself having bold in it, such as "Ubuntu Bold"
	bool		isItalic;					// Is the font italic?
	bool		isUnderline;				// Is the font underline?
	bool		isStrikethrough;			// Is the font strikethrough?
	bool		isCondensed;				// Is the font condensed?

	// Handles to the current font setting
	HFONT		hfont;

	// Internal Windows settings
	s32			_sizeUsedForCreateFont;
	u32			_size;
	u32			_weight;
	u32			_italics;
	u32			_underline;
	TEXTMETRIC	tm;
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

struct SCode
{
	SCode*		next;													// If part of a chain, then points to the next item, otherwise null

	// Raw source code
	SDatum*		sourceCode;												// Raw source code

	// During compilation
	SDatum*		compiledCode;											// Compiled code executed by the VJr interpreter
	SVariable*	params;													// Parameters
	SVariable*	returns;												// Returns
	SVariable*	locals;													// Local variables (known to the compiler, or added at runtime)
};

struct SVariable
{
	SVariable*	next;													// If part of a chain, then points to the next item, otherwise null

	u32			type;													// Variable type (see _VARIABLE_TYPE_* constants)
	SDatum		name;													// Property name
	SDatum		value;													// Data for this value

	// If assign or access
	SCode*		assign;													// Called when this variable is assigned
	SCode*		access;													// Called when this variable is accessed
};

struct SObject
{
	SObject*	next;													// Next object in chain (if any)
	SObject*	parent;													// Parent object (if any)
	SObject*	firstChild;												// Pointer to child objects (all objects are containers)

	// Object flags
	u32			type;													// Object type (see _OBJECT_TYPE_* constants)
	bool		isEnabled;												// If it is responding to events
	bool		hasFocus;												// Does this object have focus?
	bool		isRendered;												// Is it rendered (can be rendered even if it's not visible)?
	bool		isVisible;												// If it's visible
	bool		isDirty;												// Is set if this or any child object needs re-rendered

	// Data unique to this object
	void*		obj_data;												// Varies by type, see SObject* structures below

	// Related position in the member hierarchy
	SVariable*	firstProperty;											// Runtime-added user-defined property
	SCode*		firstMethod;											// Runtime-added user-defined methods

	// Events
	SEvents		ev;														// Events for this object


	//////////
	// Object size in pixels, per the .Left, .Top, .Width, and .Height properties
	//////
		RECT		rc;													// Object's current position in its parent
		RECT		rco;												// Object's original position in its parent
		RECT		rcp;												// Original size of parent at creation
		u32			anchorMode;											// Method this item uses when its parent is resized


	//////////
	// Drawing canvas
	//////
		SBitmap*	bmp;												// If exists, canvas for the content
		SBitmap*	bmpPriorRendered;									// Used for speedups when not isDirty
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
};

struct SObjectForm
{
	// _OBJECT_TYPE_FORM
	SObject*	parent;													// parent object this object belongs to

	SFont*		font;													// Default font instance
	SBgra		borderColorNW;											// Northwest back color for border
	SBgra		borderColorNE;											// Northeast back color for border
	SBgra		borderColorSW;											// Southwest back color for border
	SBgra		borderColorSE;											// Southeast back color for border
	SBgra		backColor;												// Back color for the client content
	SBgra		foreColor;												// Default text fore color
	SBgra		captionColor;											// Color of the caption

	SBitmap*	bmpIcon;												// Icon for the form
	SDatum		caption;												// Caption
	SDatum		comment;												// Comment
	SDatum		toolTip;												// What to display if hovering

	// Events unique to this object
	bool		(*activate)							(SObject* o);		// Called when the data changes
	bool		(*deactivate)						(SObject* o);		// Called when the data changes
};

struct SObjectSubform
{
	// _OBJECT_TYPE_SUBFORM
	SObject*	parent;													// parent object this object belongs to

	SFont*		font;													// Default font instance
	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color
	SBgra		captionColor;											// Color of the caption

	SBitmap*	bmpIcon;												// Icon for the subform
	SDatum		caption;												// Caption
	SDatum		comment;												// Comment
	SDatum		toolTip;												// What to display if hovering

	// Events unique to this object
	bool		(*activate)							(SObject* o);		// Called when the data changes
	bool		(*deactivate)						(SObject* o);		// Called when the data changes
};

struct SObjectLabel
{
	// _OBJECT_TYPE_LABEL
	SObject*	parent;													// parent object this object belongs to

	SFont*		font;													// Default font instance
	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color

	// Data
	u32			alignment;												// 0=left, 1=right, 2=center, always centered vertically
	SDatum		caption;												// Caption
	SDatum		comment;												// Comment
	SDatum		toolTip;												// What to display if hovering

	// Flags for rendering
	bool		isOpaque;												// Is the label opaque?
	bool		isBorder;												// Is there a border?
	SBgra		borderColor;											// Border color
	SBgra		disabledBackColor;										// Disabled background color
	SBgra		disabledForeColor;										// Disabled foreground color

	// Used only for labels in lists, like SObjectOption
	bool		selected;												// Is this item selected?
};

struct SObjectTextbox
{
	// _OBJECT_TYPE_TEXTBOX
	SObject*	parent;													// parent object this object belongs to

	SFont*		font;													// Default font instance
	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color

	// Flags for data
	u32			style;													// See _TEXTBOX_STYLE_* constants (plain, 2D, 3D)
	u32			alignment;												// 0=left, 1=right, 2=center, always centered vertically
	SDatum		value;													// Space allocated for the current value.  Note that LEFT(value, valueLength) is the actual value
	u32			valueLength;											// Length of the field
	SDatum		picture;												// Picture clause (value is formated to this form for input)
	SDatum		mask;													// Only allow these input characters
	SDatum		comment;												// Comment
	SDatum		toolTip;												// What to display if hovering

	// Flags for display and input
	s32			cursor;													// Position of the flashing cursor, where input goes
	s32			selectStart;											// Where does the selection begin?
	s32			selectEnd;												// Where does the selection end?

	// Flags for rendering
	bool		isOpaque;												// Is the label opaque?
	bool		isBorder;												// Is there a border?
	SBgra		borderColor;											// Border color
	SBgra		selectedBackColor;										// Selected background color
	SBgra		selectedForeColor;										// Selected foreground color
	SBgra		disabledBackColor;										// Disabled background color
	SBgra		disabledForeColor;										// Disabled foreground color

	// Events unique to this object
	bool		(*interactiveChange)				(SObject* o);		// Called when the data changes
	bool		(*programmaticChange)				(SObject* o);		// Called when the data changes
};

struct SObjectButton
{
	// _OBJECT_TYPE_BUTTON
	SObject*	parent;													// parent object this object belongs to

	SFont*		font;													// Default font instance
	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color

	// Flags for data
	u32			style;													// See _BUTTON_STYLE_* constants (plain, 2D, 3D)
	u32			alignment;												// 0=left, 1=right, 2=center, always centered vertically
	SDatum		comment;												// Comment
	SDatum		toolTip;												// What to display if hovering

	SBgra		disabledBackColor;										// Disabled background color
	SBgra		disabledForeColor;										// Disabled foreground color

	// Events unique to this object
	bool		(*interactiveChange)				(SObject* o);		// Called when the data changes
	bool		(*programmaticChange)				(SObject* o);		// Called when the data changes
};

struct SObjectEditbox
{
	// _OBJECT_TYPE_EDITBOX
	SObject*	parent;													// parent object this object belongs to

	SFont*		font;													// Default font instance
	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color

	// Flags for data
	u32			style;													// See _EDITBOX_STYLE_* constants (plain, 2D, 3D)
	u32			alignment;												// 0=left, 1=right, 2=center, always centered vertically
	SEditChainManager*	value;											// The content being edited
	SDatum		comment;												// Comment
	SDatum		toolTip;												// What to display if hovering

	// Flags for display and input
	s32			cursor;													// Position of the flashing cursor, where input goes
	s32			selectStart;											// Where does the selection begin?
	s32			selectEnd;												// Where does the selection end?

	// Flags for rendering
	bool		isOpaque;												// Is the label opaque?
	bool		isBorder;												// Is there a border?
	SBgra		borderColor;											// Border color
	SBgra		selectedBackColor;										// Selected background color
	SBgra		selectedForeColor;										// Selected foreground color
	SBgra		disabledBackColor;										// Disabled background color
	SBgra		disabledForeColor;										// Disabled foreground color

	// Events unique to this object
	bool		(*interactiveChange)				(SObject* o);		// Called when the data changes
	bool		(*programmaticChange)				(SObject* o);		// Called when the data changes
};

struct SObjectImage
{
	// _OBJECT_TYPE_IMAGE
	SObject*	parent;													// parent object this object belongs to

	u32			style;													// See _EDITBOX_STYLE_* constants (plain, 2D, 3D)
	SDatum		comment;												// Comment
	SDatum		toolTip;												// What to display if hovering

	SBitmap*	image;													// Image displayed when the mouse IS NOT over this control
	SBitmap*	imageOver;												// Image displayed when the mouse IS over this control

	// Events unique to this object
	bool		(*programmaticChange)				(SObject* o);		// Called when the data changes
};

struct SObjectCheckbox
{
	// _OBJECT_TYPE_CHECKBOX
	SObject*	parent;													// parent object this object belongs to

	SFont*		font;													// Default font instance
	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color

	// Data
	u32			alignment;												// 0=left, 1=right, 2=center, always centered vertically
	u32			style;													// See _CHECKBOX_STYLE_* constants (plain, 2D, 3D)
	s32			value;													// 0=unchecked, positive=checked, negative=multiple
	SDatum		comment;												// Comment
	SDatum		caption;												// Caption stored for this object (if any)
	SDatum		toolTip;												// What to display if hovering

	// Flags for rendering
	bool		isOpaque;												// Is the label opaque?
	bool		isBorder;												// Is there a border?
	SBgra		borderColor;											// Border color
	SBgra		disabledBackColor;										// Disabled background color
	SBgra		disabledForeColor;										// Disabled foreground color

	// Events unique to this object
	bool		(*interactiveChange)				(SObject* o);		// Called when the data changes
	bool		(*programmaticChange)				(SObject* o);		// Called when the data changes
};

struct SObjectOption
{
	// _OBJECT_TYPE_OPTION
	SObject*	parent;													// parent object this object belongs to

	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color

	// Data
	u32			alignment;												// 0=left, 1=right, 2=center, always centered vertically
	u32			style;													// See _RADIO_STYLE_* constants (radio, slider, spinner)
	SDatum		comment;												// Comment
	SDatum		toolTip;												// What to display if hovering

	u32			optionCount;											// How many options are there?
	SObject*	firstOption;											// Each option has its own set of properties, and each is of _OBJECT_TYPE_LABEL
	bool		multiSelect;											// Allow multiple items to be selected?

	// Events unique to this object
	bool		(*onSelect)							(SObject* o, SObject* oItem);	// When an option is selected
	bool		(*onDeselect)						(SObject* o, SObject* oItem);	// When an option is deselected
	bool		(*interactiveChange)				(SObject* o);		// Called when the data changes
	bool		(*programmaticChange)				(SObject* o);		// Called when the data changes
};

struct SObjectRadio
{
	// _OBJECT_TYPE_RADIO
	SObject*	parent;													// parent object this object belongs to

	SFont*		font;													// Default font instance
	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color

	// Data
	u32			alignment;												// 0=left, 1=right, 2=center, always centered vertically
	u32			style;													// See _RADIO_STYLE_* constants (radio, slider, spinner)
	f64			value;													// Current value
	f64			minValue;												// Minimum value to display
	f64			maxValue;												// Maximum value to display
	f64			roundTo;												// Round 10=tens place, 1=whole integers, 0.1=one decimal place, 0.01=two decimal places, and so on
	SDatum		comment;												// Comment
	SDatum		toolTip;												// What to display if hovering

	// Flags for rendering
	bool		isOpaque;												// Is the label opaque?
	bool		isBorder;												// Is there a border?
	SBgra		borderColor;											// Border color
	SBgra		disabledBackColor;										// Disabled background color
	SBgra		disabledForeColor;										// Disabled foreground color

	// Events unique to this object
	bool		(*interactiveChange)				(SObject* o);		// Called when the data changes
	bool		(*programmaticChange)				(SObject* o);		// Called when the data changes
};

struct SWindow
{
	RECT		rc;														// Rectangle of window's physical position
	SBitmap		bmp;													// Bitmap data for the window
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

	// Icon
	SBitmap*	bmpWindowIcon;											// Icon for the window

	// For the corner triangles
	SBitmap*	bmpArrowUl;												// Icons used for the move arrows
	SBitmap*	bmpArrowUr;
	SBitmap*	bmpArrowLr;
	SBitmap*	bmpArrowLl;

	// For mouse objects
	SBitmap*	bmpMove;												// Icons used for move, minimize, maximize, close
	SBitmap*	bmpMinimize;
	SBitmap*	bmpMaximize;
	SBitmap*	bmpClose;
};
