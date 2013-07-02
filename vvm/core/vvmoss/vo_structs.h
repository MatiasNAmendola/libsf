//////////
//
// /libsf/vvm/vvmoss/vo_structs.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     September 24, 2012 - Initial creation
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




// In other structure definition files
struct SCallbacks;


//////////
// OSS screen-specific stuff (should be updated only internally, but can be referenced anywhere)
//////
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
		u32				foreColor;							// Default foreground color
		u32				backColor;							// Default background color

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
		bool			closed;											// Is this level closed?

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
		u8		sha20Bytes[20];											// 20-byte buffer used for computing SHA1
		u64		sha1_u64;												// 64-bit form of the 20-byte buffer
		u32		sha1_u32;												// 32-bit form of the 20-byte buffer
	};
