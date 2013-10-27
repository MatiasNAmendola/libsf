//////////
//
// /libsf/vvm/vvmoss/vo_istructs.h
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
// VVMOSS Internal Structures
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
//////
//
// Note:  For the naming conventions,  for example "_iswSFont"
//			_i		- indicates internal
//			s		- is a system structure, not one the VVM knows about, but one only used here internally
//			w		- indicates this contains some Windows structures or handles
//			SFont	- the font structure
//
//




	struct _iswSwindowExtraKeyData
	{
		u32				repeatCount	: 16;					// 0-15		The repeat count for the current message. The value is the number of times the keystroke is autorepeated as a result of the user holding down the key. If the keystroke is held long enough, multiple messages are sent. However, the repeat count is not cumulative.
		u8				scanCode	: 8;					// 16-23	The scan code. The value depends on the OEM.
		bool			extendedKey	: 1;					// 24		Indicates whether the key is an extended key, such as the right-hand ALT and CTRL keys that appear on an enhanced 101- or 102-key keyboard. The value is 1 if it is an extended key; otherwise, it is 0.
		u8				reserved	: 4;					// 25-28	Reserved; do not use.
		bool			context		: 1;					// 29		The context code. The value is always 0 for a WM_KEYDOWN message.
		bool			previous	: 1;					// 30		The previous key state. The value is 1 if the key is down before the message is sent, or it is zero if the key is up.
		bool			transition	: 1;					// 31		The transition state. The value is always 0 for a WM_KEYDOWN message.
	};

	struct _iswSSystemBitmap
	{
		// Note:  This is the bdoss member of the VVM SCanvas structure
		HDC				hdc;								// Device context for this instance
		HBITMAP			hbmp;								// Handle to the DIB bitmap
		BITMAPINFO		bi;									// Information used at creation for its size
		s8*				bd;									// Root pointer to the bits
		// Speedups
		u32				width;								// Shortcut to bi.bmiHeader.biWidth
		u32				height;								// Shortcut to bi.bmiHeader.biHeight
		u32				actualWidth;						// Stride across each row rounded to nearest dword
	};

	struct _iswSSystemFont
	{
		SLL				ll;									// Pointer to siblings in chain

		// System font handle
		HFONT			handle;								// Handle to the font, which is the system handle, or HFONT

		// User-provided attributes (Note:  These may not match the actual font, were the font substituted because it wasn't present on the system)
		s8*				fontName;							// Name given by user for font
		u32				fontPointSize;						// point size
		bool			bold;								// is this font bold?
		bool			italics;							// Is this font italic?
		bool			underline;							// Is this font underlined?
		bool			strikethrough;						// Does this font have a strikethrough?
	};

	struct RGB_QUAD
	{
		u8			blu;
		u8			grn;
		u8			red;
		u8			alp;										// Alpha
	};

	struct RGB_TRIPLE
	{
		u8			blu;
		u8			grn;
		u8			red;
	};

	// Threads allocated in oss_createThread()
	struct _iswSThreads
	{
		SLL			ll;										// 2-way link list

		// Set at creation, and updated as accessed afterward
		bool		isViable;								// Is this thread a viable entity (if created successfully, will always be true)
		bool		isSuspended;							// Is this thread suspended?

		// OS-assigned variables upon thread creation
		u32			os_threadId;							// OS-assigned thread id
		HANDLE		os_threadHandle;						// OS-assigned thread handle
	};

	struct _iswSSharedFileLocks
	{
		SLL				ll;									// 2-way link list
		u64				offset;								// Start of the lock
		u64				length;								// Length of the lock
		SDateTime		locked;								// When was it locked?
	};

	struct _iswSSharedFile
	{
		SLL				ll;									// 2-way link list

		int				handle;								// Returned from sopen() or wsopen()
		SStartEnd		locks;								// Any file locks
		SDateTime		fileOpened;							// Date and time the file was opened
		SDateTime		fileAccessed;						// Date and time the file was last accessed (read/written/seeked)

		// For reference and debugging information only, may not be accurate
		u64				lastOffset;							// The last offset (for reference / debugging viewing only, may not be accurate)
		u64				bytesRead;							// Number of bytes read
		u64				bytesWritten;						// Number of bytes written
		u64				locksIssued;						// Number of locks created on file
		u64				locksCleared;						// Number of locks released on file
	};

	struct _iswSOssWindowLL
	{
		SLL				ll;									// Link list chain
		SOssWindow		isw;								// Local copy of the window data
	};

	struct _iswSFocusCallback
	{
		u64					osHandle;
		_iswSOssWindowLL*	forFocus;
	};

	// Parameters used for the iibxml_nodeCopyAttributes() function (can only pass one parameter to the callback, so we need a vehicle/bus to carry the load)
	struct _isSBxmlCopyAttrParams
	{
		SBxml*				bxmlDst;
		bool*				tlResult;
	};

	// Parameters used for the iioss_bxmlComputeSha1OnNode() function (can only pass one parameter to the callback, so we need a vehicle/bus to carry the load)
	struct _isSBxmlComputeSha1NodeParams
	{
		u8*		handle92Bytes;								// Holds the 92-byte interim value the SHA-1 algorithm uses for computing its hash
		u8*		buffer64Bytes;								// A temporary buffer used for computing values with sprintf
	};

	struct _isSBitmapProcess
	{
		// Holds canvas information
		SCanvas*			dst;				// Destination for the scale
		SCanvas*			src;				// Source for the scale
		SScaleMap*			sm;					// Scale map being computed

		// Holds storage data for single spanned pixels
		u32					red;
		u32					grn;
		u32					blu;
		u32					alp;

		// tpoints is a buffer created to store the conversion pixel data during accumulation
		// Use formula:
		//		tpoints	= (SBGRAF*)malloc(		((u32)(1.0/ratioV) + 3)   *
		//										((u32)(1.0/ratioH) + 3))
		//
		f32					ratioV;				// (f32)bio->biHeight	/ (f32)bii->biHeight;
		f32					ratioH;				// (f32)bio->biWidth	/ (f32)bii->biWidth;
		u32					count;				// Number of valid points in tpoints
		SBGRAF*				pixels;				// Accumulation buffer for point data needed to feed into destination

		// Temporary variables used for processing
		SBGRA*				optr;				// Output pointer to the upper-left pixel for this x,y
		SBGRA*				iptra;				// Input pointer to the left-most pixel of the first row (the anchor)
		SBGRA*				iptr;				// Input pointer to the left-most pixel for this y row
		u32					x;					// X-coordinate
		u32					y;					// Y-coordinate
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

	// Used for the oss_bxmlFindFirst() and oss_bxmlFindContinue() functions
	struct _isSBxmlFind
	{
		SBxml*				bxmlRoot;			// The root where the search started
		SBxml*				bxmlRootParent;		// The parent node of the root (used to indicate when we're reached the end of the root's siblings)

		// Each subsequent find, the find data is stored here for future changes
		SBxml*				bxml;				// If populated, the last item found was this node
		SBxmla*				bxmla;				// If populated, the last item found was this attribute
		u32					_mlIterator;		// For entries related to attributes, holds the last entry through _attributes.master[]
		SMasterList*		_ml;				// For entries related to attributes
		bool				lastFindOnNode;		// Was the last find found on a node?
		bool				lastFindOnAttribute;// Was the last find found on an attribute?

		// Initial flag settings
		SDatum*				wildcard;			// The wildcard being searched for
		bool				traverseChildren;	// Are child nodes being traversed?
		bool				searchAttributes;	// Are we searching attributes?
		SBxml**				bxmlNodeFound;		// Where to store the found node for the user
		SBxmla**			bxmlaAttributeFound;// Where to store the found attribute for the user
	};

	struct _isSBxmlAttributeDeleteParams
	{
		SBxmla*				bxmla;				// The attribute to delete
		bool				freeMemory;			// Should its memory be freed?
	};



//////////
// Note:  There are sound plugin structures in vo_plugins.h
//////
