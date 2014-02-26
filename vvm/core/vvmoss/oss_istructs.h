//////////
//
// /libsf/vvm/vvmoss/vo_istructs.h
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.25.2014
//////
// Change log:
//     Feb.25.2014 - Development on 0.70 begins
//     Nov.07.2012 - 0.60 development begins
//     Sep.29.2012 - PBL v1.0 license included directly in source files.
//     Sep.24.2012 - Initial creation
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

	struct _iswSFocusCallback
	{
		u64				osHandle;
		SOssWindowLL*	forFocus;
	};


//////////
// Note:  There are sound plugin structures in vo_plugins.h
//////
