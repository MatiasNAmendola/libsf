//////////
//
// /libsf/source/vjr/vjr_structs.h
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




struct SExtraInfo
{
	SExtraInfo* next;													// Next extra info item in chain (if any)
	u32			use_identifier;											// A registered identifier with the system for this extra info block
	u32			type;													// Application defined type, identifies what's stored in this.info.data
	SDatum		info;													// The extra info

	// Functions to use to access this extra info block
	void		(*onAccess)					(SEditChainManager* chainMgr, SEditChain* chain, SExtraInfo* extra_info);	// When the parent chain is accessed
	void		(*onArrival)				(SEditChainManager* chainMgr, SEditChain* chain, SExtraInfo* extra_info);	// When the target implementation is sitting on the chain record
	void		(*onUpdate)					(SEditChainManager* chainMgr, SEditChain* chain, SExtraInfo* extra_info);	// When the parent chain is updated

	// Functions called before freeing, and after allocating, the this.info datum
	SExtraInfo*	(*extra_info_allocate)		(SEditChainManager* chainMgr, SEditChain* chain, SExtraInfo* extra_info);	// Called to allocate this.info per needs
	SExtraInfo*	(*extra_info_duplicate)		(SEditChainManager* chainMgr, SEditChain* chain, SExtraInfo* extra_info);	// Called when a chain is duplicated, determines what if any of the source's data needs to be duplicated as well
	SExtraInfo*	(*extra_info_free)			(SEditChainManager* chainMgr, SEditChain* chain, SExtraInfo* extra_info);	// Called to free any data in this.info
};

struct SDateTime
{
	u32		julian;														// Julian day number
	f32		seconds;													// Seconds elapsed since midnight
};

struct SUndo
{
	u32			uidBefore;												// The item before
	u32			uidAfter;												// The item after

	SEditChain*	first;													// The first SEditChain that would've gone between them
	// If multiple lines were deleted, the chain is moved here.
	// If the line was changed, the old value is here
};

struct SEditChain
{
	SLL			ll;														// Link list throughout
	u32			uid;													// Unique id for this line, used for undos and identifying individual lines which may move about

	u32			line;													// This line's number
	SDatum*		sourceCode;												// The text on this line is LEFT(d.data, dPopulated)
	s32			sourceCodePopulated;									// The actual populated length of d (d is allocated in blocks to allow for minor edits without constantly reallocating)

	// Compiler information (see compiler.cpp)
	bool		forceRecompile;											// A flag that if set forces a recompile of this line
	SCompiler*	compilerInfo;											// Information about the last time this line was compiled

	// General purpose extra data
	SExtraInfo*	extra_info;												// Extra information about this item in the chain
};

struct SEditChainManager
{
	SEditChain*			ecFirst;										// First in the chain (first->prev is NULL)
	SEditChain*			ecLast;											// Last in the chain (last->next is NULL)
	bool				isReadOnly;										// If read-only no changes are allowed, only navigation

	// If populated, this ECM is only a placeholder for this instance, and the this->reference points to the real ECM we should use
	SEditChainManager*	indirect;										// If not NULL, this ECM points to another ECM which is the real code block
	// NOTE:  Everything below is used ONLY IF INDIRECT IS NULL


	//////////
	// For display
	//////
		SEditChain*		ecTopLine;										// Top item in the current view
		SEditChain*		ecCursorLine;									// Line where the cursor is
		SEditChain*		ecCursorLineLast;								// The last location before movement was made
		bool			isOverwrite;									// Are we in overwrite mode?
		s32				column;											// Column we're currently inputting
		s32				leftColumn;										// The column we're displaying at the left-most position (of horizontally scrolled, this will be greater than 0)


	//////////
	// Selected lines
	//////
		SEditChain*		ecSelectedLineStart;							// First line that's selected
		SEditChain*		ecSelectedLineEnd;								// Last line that's selected


	//////////
	// Note:  If not isColumn or isAnchor, then it is full line select.
	//        If isColumn, then column select mode.
	//        If isAnchor, then anchor select mode.
	//////
		bool			isColumn;										// If column select mode...
		u32				selectedColumnStart;							// Column select mode start
		u32				selectedColumnEnd;								// end
		bool			isAnchor;										// If anchor select mode...
		u32				selectedAnchorStart;							// Anchor select mode start
		u32				selectedAnchorEnd;								// end


	//////////
	// For compiled programs
	//////
		SFunction		firstFunction;									// By default, we always create a function head for any code blocks that don't have an explicit "FUNCTION" at the top.


	//////////
	// The undo history operates in two levels:
	// (1) When going through ecm-> it is undoHistory.
	// (2) If accessing ecm->undoHistory-> then it is theUndo, which holds the undo information for that operation.
	//////
		union {
			// If referenced through ecm-> then undoHistory is the undo history for this sec
			SEditChainManager*	undoHistory;							// The lines affected by the undo

			// If referenced through ecm->undoHistory, then theUndo is the one in use here
			SUndo*				theUndo;								// If referenced through ecm->undoHistory-> then it only uses theUndo
		};
};

struct SFont
{
	HDC			hdc;						// Device context used for its creation

	// Current font instance flags
	SDatum		name;						// Name of this font
	s32			charset;					// Font charset
	bool		isBold;						// Is the font bold? (Note: This is independent of the font name itself having bold in it, such as "Ubuntu Bold"
	bool		isItalic;					// Is the font italic?
	bool		isUnderline;				// Is the font underline?
	bool		isStrikethrough;			// Is the font strikethrough?
	bool		isCondensed;				// Is the font condensed?
	bool		isExtended;					// Is the font extended?
	bool		isOutline;					// Is the font outlined?
	bool		isShadow;					// Is the font shadowed?

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

struct SEventsGeneral
{
	bool		(*onLoad)			(SObject* o);							// Called to load anything needed by the init() event (holds a template/skeleton object)
	bool		(*onInit)			(SObject* o);							// Called to initialize anything
	bool		(*onCreated)		(SObject* o);							// Called after initialization, before the object is sized
	bool		(*onResize)			(SObject* o, u32* widthRequired_out, u32* heightRequired_out);	// Called to size or resize the object
	bool		(*onMoved)			(SObject* o, u32* xOverride_out, u32* yOverride_out);			// Called when the object has been moved
	bool		(*onRender)			(SObject* o);							// Called to render to bmp (returns if anything was drawn)
	bool		(*onPublish)		(SObject* o);							// Called to publish the control onto the parent (which will populate bmpScale if need be)
	bool		(*onQueryUnload)	(SObject* o);							// Called before onDestroy, determines if the form should actually be destroyed
	bool		(*onDestroy)		(SObject* o);							// Called when the object will be destroyed
	bool		(*onUnload)			(SObject* o);							// Called after the object has been destroyed, to unload anything (holds a template/skeleton object)
	bool		(*onGotFocus)		(SObject* o);							// Called when the object receives focus (note multiple items can have simultaneous focus)
	bool		(*onLostFocus)		(SObject* o);							// Called when the object loses focus
	bool		(*onAddObject)		(SObject* o);							// Called when an object is added
	bool		(*onAddProperty)	(SObject* o);							// Called when a property is added
	bool		(*onError)			(SObject* o);							// Called when an error is triggered in code on an object
	bool		(*onScrolled)		(SObject* o);							// Called when an object has been scrolled
};

struct SEventsMouse
{
	// Holds status for changes
	u32			_lastClick;
	bool		isMouseOver;												// Used for signaling enter/leave events
	u64			startHoverTimer;											// At each last mouseMove the startHoverTimer is set, if the interval elapses the hover event is triggered

	// Mouse callbacks issued by VJr to the internal object controller.
	// These will be translated by the internal object controller into executable VJr VXB-- code.
	// Return value indicates if the event should be sent to its parent instead (if NODEFAULT was issued during execution).
	bool		(*onMouseClickEx)		(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);	// 1=left, 2=middle, 4=right, 2^n bit positions indicate which buttons are clicked
	bool		(*onMouseWheel)		(SObject* o, s32 tnUnits);				// Signed units indicating direction and velocity
	bool		(*onMouseMove)		(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);	// Coordinates for the move
	bool		(*onMouseDown)		(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick, u32 tnLastClick);	// Coordinates for where the mouse button changed
	bool		(*onMouseUp)		(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick, u32 tnLastClick);	// Coordinates for where the mouse button changed
	bool		(*onMouseEnter)		(SObject* o);							// When mouse enters an object
	bool		(*onMouseLeave)		(SObject* o);							// When mouse leaves an object
	bool		(*onMouseHover)		(SObject* o, u32 x, u32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClick);	// Coordinates where hovering
};

struct SEventsKeyboard
{
	// Keyboard callbacks
	// Bool indicates if the event should be sent to its parent instead
	bool		(*onKeyDown)		(SObject* o, bool tlCtrl, bool tlAlt, bool tlShift, s16 tcAscii, u16 tnVKey, bool tlIsCAS, bool tlIsAscii);
	bool		(*onKeyUp)			(SObject* o, bool tlCtrl, bool tlAlt, bool tlShift, s16 tcAscii, u16 tnVKey, bool tlIsCAS, bool tlIsAscii);
};

struct SEvents
{
	SEventsGeneral		general;										// General object events
	SEventsMouse		mouse;											// Mouse events for the object
	SEventsKeyboard		keyboard;										// Keyboard events for the object
};

struct SObject
{
	SLL			ll;														// Linked list
	SObject*	parent;													// Pointer to parent object for this instance
	SObject*	firstChild;												// Pointer to child objects (all objects are containers)

	// Information about the object itself
	s32			tabIndex;												// The tab order
	bool		tabStop;												// Does this object stop for tabs?
	s32			helpContextId;											// Help context
	bool		hasWhatsThisButton;										// Does it have a what's this button?
	bool		hasWhatsThisHelp;										// Does it have what's this help?
	s32			whatsThisHelpId;										// The what's this help id

	// Defined class, class information
	SDatum		name;													// If a user object, this object's name
	u32			objType;												// Object base type/class (see _OBJECT_TYPE_* constants)
	SDatum		className;												// The class
	SDatum		classLibrary;											// The class location
	SDatum		comment;
	SDatum		tooltip;
	SDatum		tag;

	// Mouse information
	SBitmap*	mouseIcon;												// The mouse icon
	u32			mousePointer;											// The mouse pointer to use

	// Object flags
	bool		isEnabled;												// If it is responding to events
	bool		hasFocus;												// Does this object have focus?
	bool		isMovable;												// Is this object movable?
	bool		isRendered;												// Is it rendered (can be rendered even if it's not visible)?
	bool		isPublished;											// Should this control be published?  Every object has a .lockScreen property which allows it to not be published while changes are made.
	bool		isVisible;												// If it's visible
	bool		isDirty;												// Is set if this or any child object needs re-rendered

	// Data unique to this object
	void*		sub_obj;												// Varies by type, see SObject* structures below

	// Related position in the member hierarchy
	SVariable*			firstProperty;									// Runtime-added user-defined property
	SEditChainManager*	firstMethod;									// Runtime-added user-defined methods

	// Events
	SEvents		ev;														// Events for this object


	//////////
	// Object size in pixels, per the .Left, .Top, .Width, and .Height properties
	//////
		RECT		rc;													// Object's current position in its parent
		RECT		rco;												// Object's original position in its parent
		RECT		rcp;												// Original size of parent at creation
		u32			anchor;												// Method this item uses when its parent is resized


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

struct SSubObjEmpty
{
	// _OBJECT_TYPE_EMPTY
	SObject*	parent;													// parent object this object belongs to
};

struct SSubObjForm
{
	// _OBJECT_TYPE_FORM
	SObject*	parent;													// parent object this object belongs to

	RECT		rcMax;													// The maximum rectangle for the form
	RECT		rcMin;													// The minimum rectangle for the form

	SFont*		font;													// Default font instance
	SBgra		nwRgba;													// Northwest back color for border
	SBgra		neRgba;													// Northeast back color for border
	SBgra		swRgba;													// Southwest back color for border
	SBgra		seRgba;													// Southeast back color for border
	SBgra		backColor;												// Back color for the client content
	SBgra		foreColor;												// Default text fore color
	SBgra		captionColor;											// Color of the caption

	SBitmap*	bmpFormIcon;											// Icon for the form
	SDatum		caption;												// Caption

	SDatum		pictureName;											// The name of the file used for the picture
	SBitmap*	bmpPicture;												// The image for the picture

	// General flags and settings
	bool		allowOutput;											// Allow output to the form?
	bool		alwaysOnBottom;											// Is this form always on the bottom of the Z-order?
	bool		alwaysOnTop;											// Is this form always on the top of the z-order?
	bool		autoCenter;												// Should this form auto-center itself relative to its parent?
	s32			borderStyle;											// 0=none, 1=fixed, 2=fixed standard presentation, 3=sizable presentation
	bool		isCloseable;											// Is the form closeable through user interaction?
	bool		processKeyPreviewEvents;								// Do keystrokes for controls on the form go through the form's Key* events as well?
	bool		hasControlBox;											// Does the form show its control box?
	bool		hasMinButton;											// Is the minimize button shown?
	bool		hasMaxButton;											// Is the maximize button shown?
	bool		hasCloseButton;											// Is the close button shown?
	s32			scaleMode;												// 0=foxels, 3=pixels (default)
	bool		showInTaskBar;											// Is this form shown in a taskbar?  Only relates to top-level forms (no parent, or parent is _screen).
	s32			windowState;											// 0=normal, 1=minimized, 2=maximized

	// The following are ignored, maintained only for backward compatibility
	bool		bindControls;											// Are controls bound to their source?
	s32			bufferMode;												// 0=none, 1=pessimistic, 1=optimistic, VJr always uses optimistic. Developers can use the LOCK command if they want a record explicitly locked.
	bool		clipControls;											// Ignored. VJr always re-renders the entire control.
	s32			colorSource;											// Ignored. VJr always uses its themed controls.
	bool		continuousScroll;										// Ignored.
	SObject*	dataSession;											// Ignored, always set to .NULL..
	s32			dataSessionId;											// Ignored, always set to -1.
	SDatum		declass;												// Ignored, always empty.
	SDatum		declasslibrary;											// Ignored, always empty.
	s32			defolecid;												// Ignored, always uses system locale.
	bool		desktop;												// Ignored, all VJr forms can be shown anywhere.  To keep inside a window, parent it to _screen or a form.
	bool		isDockable;												// Ignored, always set to .F., docking is not supported in VJr.
	bool		isDocked;												// Ignored, always set to .F..
	s32			dockPosition;											// Ignored, always set to -1.
	s32			drawmode;												// Ignored, drawing is not supported in VJr this way.  See the _graphics object.
	s32			drawstyle;												// Ignored, always set to 13.
	s32			drawwidth;												// Ignored, always set to 1.
	SBgra		fillColor;												// Ignored, always set to RGB(255,255,255).
	s32			fillStyle;												// Ignored, always set to 0.
	bool		halfHeightCaption;										// Ignored, always set to .F..
	s32			hScrollSmallChange;										// Ignored, always uses system defaults.
	s32			vScrollSmallChange;										// Ignored, always uses system defaults.
	bool		macDesktop;												// Ignored, always set to .F..
	bool		mdiForm;												// Ignroed, always set to .F..
	s32			oleDragMode;											// Ignored, always set to 0.
	SBitmap*	oleDragPicture;											// Ignored, always set to .NULL..
	s32			oleDropEffects;											// Ignored, always set to 3.
	s32			oleDropHasData;											// Ignored, always set to -1.
	s32			oleDropMode;											// Ignored, always set to 0.
	s32			releaseType;											// Ignored, always returns 0.
	bool		rightToLeft;											// Ignored, always returns .F..
	s32			scrollbars;												// Ignored, always returns 3 both, scrollbars are automatic in VJr.
	s32			showTips;												// Ignored, always returns .T..
	s32			showWindow;												// Ignored, always returns 2, all forms in VJr are top-level modeless forms. Min/max constraints can keep it in a fixed position it within a parent window.
	bool		sizeBox;												// Ignored, always returns .F..
	bool		themes;													// Ignored, always returns .T., VJr always uses its own themes for graphics.
	s32			titleBar;												// Ignored, returns what is indicated by borderStyle.
	s32			windowType;												// Ignored, always returns 0=modeless, all forms in VJr are modeless.
	bool		zoomBox;												// Ignored, always returns .F.

	// Events unique to this object
	bool		(*activate)							(SObject* o);		// Called when activated
	bool		(*deactivate)						(SObject* o);		// Called when deactivated

	// Updating each render
	RECT		rcClient;												// The client area of the form
	RECT		rcCaption;												// The caption area (used for moving the form around)
	RECT		rcArrowUl;												// The upper-left resize arrow is
	RECT		rcArrowUr;												// The upper-right resize arrow is
	RECT		rcArrowLl;												// The lower-left resize arrow is
	RECT		rcArrowLr;												// The lower-right resize arrow is
	RECT		rcIcon;													// The form icon
	RECT		rcMove;													// The move button of the form
	RECT		rcMinimize;												// The minimize button of the form
	RECT		rcMaximize;												// The maximize button of the form
	RECT		rcClose;												// The close button of the form
};

struct SSubObjSubform
{
	// _OBJECT_TYPE_SUBFORM
	SObject*	parent;													// parent object this object belongs to

	RECT		rcMax;													// The maximum rectangle for the form
	RECT		rcMin;													// The minimum rectangle for the form

	SFont*		font;													// Default font instance
	SBgra		nwRgba;													// Northwest back color for border
	SBgra		neRgba;													// Northeast back color for border
	SBgra		swRgba;													// Southwest back color for border
	SBgra		seRgba;													// Southeast back color for border
	SBgra		backColor;												// Back color for the client content
	SBgra		foreColor;												// Default text fore color
	SBgra		captionColor;											// Color of the caption

	SBitmap*	bmpFormIcon;											// Icon for the form
	SDatum		caption;												// Caption

	SDatum		pictureName;											// The name of the file used for the picture
	SBitmap*	bmpPicture;												// The image for the picture

	// General flags and settings
	bool		allowOutput;											// Allow output to the form?
	s32			borderStyle;											// 0=none, 1=fixed, 2=fixed standard presentation, 3=sizable presentation
	bool		processKeyPreviewEvents;								// Do keystrokes for controls on the form go through the form's Key* events as well?
	s32			scaleMode;												// 0=foxels, 3=pixels (default)
	s32			windowState;											// 0=normal, 1=minimized

	// Events unique to this object
	bool		(*activate)							(SObject* o);		// Called when activated
	bool		(*deactivate)						(SObject* o);		// Called when deactivated

	// Updating each render
	RECT		rcClient;												// The client area of the subform
	RECT		rcCaption;												// The caption area (used for moving the subform around)
	RECT		rcIcon;													// The subform icon
};

struct SSubObjLabel
{
	// _OBJECT_TYPE_LABEL
	SObject*	parent;													// parent object this object belongs to

	SFont*		font;													// Default font instance
	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color

	// Data
	u32			alignment;												// 0=left, 1=right, 2=center, always centered vertically
	SDatum		caption;												// Caption

	// Flags for rendering
	bool		isOpaque;												// Is the label opaque?
	bool		isBorder;												// Is there a border?
	SBgra		borderColor;											// Border color
	SBgra		disabledBackColor;										// Disabled background color
	SBgra		disabledForeColor;										// Disabled foreground color

	// Used only for labels in lists, like SObjectOption
	bool		selected;												// Is this item selected?
};

struct SSubObjTextbox
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

struct SSubObjButton
{
	// _OBJECT_TYPE_BUTTON
	SObject*	parent;													// parent object this object belongs to

	SFont*		font;													// Default font instance
	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color

	// Flags for data
	u32			style;													// See _BUTTON_STYLE_* constants (plain, 2D, 3D)
	u32			alignment;												// 0=left, 1=right, 2=center, always centered vertically
	SDatum		caption;												// Caption

	SBgra		disabledBackColor;										// Disabled background color
	SBgra		disabledForeColor;										// Disabled foreground color

	// Events unique to this object
	bool		(*interactiveChange)				(SObject* o);		// Called when the data changes
	bool		(*programmaticChange)				(SObject* o);		// Called when the data changes
};

struct SSubObjEditbox
{
	// _OBJECT_TYPE_EDITBOX
	SObject*	parent;													// parent object this object belongs to

	SFont*		font;													// Default font instance
	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color

	// Flags for data
	u32			style;													// See _EDITBOX_STYLE_* constants (plain, 2D, 3D)
	u32			alignment;												// 0=left, 1=right, 2=center, always centered vertically
	SEditChainManager*	codeBlock;										// The content being edited, typically source code

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

struct SSubObjImage
{
	// _OBJECT_TYPE_IMAGE
	SObject*	parent;													// parent object this object belongs to

	u32			style;													// See _EDITBOX_STYLE_* constants (plain, 2D, 3D)

	SBitmap*	image;													// Image displayed when the mouse IS NOT over this control
	SBitmap*	imageOver;												// Image displayed when the mouse IS over this control

	// Events unique to this object
	bool		(*programmaticChange)				(SObject* o);		// Called when the data changes
};

struct SSubObjCheckbox
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
	SDatum		caption;												// Caption stored for this object (if any)

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

struct SSubObjOption
{
	// _OBJECT_TYPE_OPTION
	SObject*	parent;													// parent object this object belongs to

	SBgra		backColor;												// Back color (only RGB() channels are used, but RGBA() channels are maintained)
	SBgra		foreColor;												// Default text fore color

	// Data
	u32			alignment;												// 0=left, 1=right, 2=center, always centered vertically
	u32			style;													// See _RADIO_STYLE_* constants (radio, slider, spinner)

	u32			optionCount;											// How many options are there?
	SObject*	firstOption;											// Each option has its own set of properties, and each is of _OBJECT_TYPE_LABEL
	bool		multiSelect;											// Allow multiple items to be selected?

	// Events unique to this object
	bool		(*onSelect)							(SObject* o, SObject* oItem);	// When an option is selected
	bool		(*onDeselect)						(SObject* o, SObject* oItem);	// When an option is deselected
	bool		(*interactiveChange)				(SObject* o);		// Called when the data changes
	bool		(*programmaticChange)				(SObject* o);		// Called when the data changes
};

struct SSubObjRadio
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

