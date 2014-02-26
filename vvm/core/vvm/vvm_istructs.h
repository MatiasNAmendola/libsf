//////////
//
// /libsf/vmm/vmm/vmm_istructs.h
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
//     Nov.11.2012 - Initial creation
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



//////////
//
// Internal structures
// These are NOT designed to be referenced anywhere outside of the VVM's core engine.
//
//////




	// The main VVM app's data variables
	struct _isSVvmApp
	{
		int				gnVvmReturnResult;				// Indicate an initial return of failure
		bool			glVvmIsRunning;					// The VVM will continue as long as it is set to continue ... oh yes indeed. :-)
		bool			glVvmDebugBreaks;				// A global debugging flag if INT3 should be signaled when certain debugging conditions occur
		HINSTANCE		ghVvmResourceDll;				// Handle to the loaded resource dll instance
		s8*				gcVvmResourceLang;				// By default, points to English, override using command line switch "-r:" (such as "-r:es" for "vvmes.dll", for example)

		// Command-line determined instance sizes for variable allocation
		// NOTE:  The allocation size here will need to be inspected when the VVM is running to determine a better default size
		u32				gnGlobalAllocationBlockSize;	// The default size to increase the global variable allocation
		u32				gnLocalAllocationBlockSize;		// The default size to increase the global variable allocation
		u32				gnStackAllocationBlockSize;		// Default to an 8K stack per thread
		u32				gnSnippetAllocationBlockSize;	// The default size to increase the snippet level allocation


		// The root objects
		SStartEnd		gseRootPrograms;				// Master programs list
		SStartEnd		gseRootThreadMizer;				// Master thread mizer list
		SStartEnd		gseRootResourceTexts;			// Previously loaded / cached resource texts


		// Semaphores for synchronized access to master lists
		u64				gsemProgramsAccess;				// Master program inventory
	};

	// Used in ivvmtm_* functions
	struct _ivvmtm_SMainLoop
	{
		// Local variables used in ivvmtm_mainLoop.  They were moved into a structure so they can
		// be passed to separate functions which break out the logic and make it easier to understood.
		bool			llProgramsGeneralAccessLocked, llProgramsAccessLocked, llThreadsAccessLocked;
		bool			llProcessedSomething;
		u32				lnI, lnJ;
		SThreadMizer*	ltm;
		SProgram*		lp;
		SThread*		lt;
	};

	struct _ivvme_executeThreadSnippetData
	{
		u8*		lid;			// Pointer to start of instruction
		u32		lnDecoder;		// Grab the first DWORD and load it as the initial decoder
		u32		lnPredicate;	// Stores the predicate, or extended predicate if indicated
		u32		lnOpcode;		// Stores the instruction opcode, or extended/2nd opcode if indicated

		// Opcode address we're immediately processing
		union {
			u32		_vvmOpcodeExecute;			// Target address for the opcode decoding
			void	(*vvmOpcodeExecute)	(_ivvme_executeThreadSnippetData* tsed);
		};
	};


//////////
//
// Refer to the vvmt_defs.h file in the vvm_core.sln or vvm_canvas.sln (two test DLLs written at
// the time of this structure's creation) to see the actual definition of these functions, which
// must match up with what is coded here
//
//////
	struct _isSVvmTests
	{
		u64 DllInstance;


		//////////
		// firstCallback
		//////
			union {
				u64		_firstCallback;
				u64		(CALLTYPE *firstCallback)				(u64 tnDebuggerInterfaceAddress);
			};


		//////////
		// bootstrapInitialization
		//////
			union {
				u64		_bootstrapInitialization;
				void	(CALLTYPE *bootstrapInitialization)		(u64 tnDebuggerInterfaceAddress);
			};


		//////////
		// initialization
		//////
			union {
				u64		_initialization;
				void	(CALLTYPE *initialization)				(u64 tnDebuggerInterfaceAddress);
			};


		//////////
		// getVersion
		//////
			union {
				u64			_getVersion;
				const s8*	(CALLTYPE *getVersion)				(void);
			};


		//////////
		// executeTests
		//////
			union {
				u64		_executeTests;
				bool	(CALLTYPE *executeTests)				(u64 lnHandleLog);
			};
	};

	// Parameters used for the iibxml_nodeCopyAttributes() function (can only pass one parameter to the callback, so we need a vehicle/bus to carry the load)
	struct _isSBxmlCopyAttrParams
	{
		SBxml*				bxmlDst;
		bool*				tlResult;
	};

	// Parameters used for the iivvm_bxmlComputeSha1OnNode() function (can only pass one parameter to the callback, so we need a vehicle/bus to carry the load)
	struct _isSBxmlComputeSha1NodeParams
	{
		u8*		handle92Bytes;								// Holds the 92-byte interim value the SHA-1 algorithm uses for computing its hash
		u8*		buffer64Bytes;								// A temporary buffer used for computing values with sprintf
	};

	// Used for the vvm_bxmlFindFirst() and vvm_bxmlFindContinue() functions
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
//
// Used by iioss_canvasPolygon_storeFloans() to rapidly drawn floans
//
//////
	struct _isSStoreFloan_lineData
	{
		SBuilder*			floans;				// Where we're storing the floans

		SXYS32				end;				// Where does this end?
		SXYS32				po;					// Where is this pixel's origin (the pixel number identifying the pixel's coordinate closest to (0,0))?
		u32					offset;				// The destination offset within the canvas

		SXYF64				p1;					// Point 1 (from point)
		SXYF64				p2;					// Point 2 (destination point)
		f64					m;					// Slope
		f64					theta;				// Theta
		u32					gravityDecorated;	// Gravity with cardinal, ordinal, and decorations
		s32					gravity07;			// Gravity with the range of 0..7, as from SW=0, clockwise to S=7 (see vo_sup.cpp polygon functions)
	};

	struct _isSStoreFloan_cornerData
	{
		SXYF64						po;					// Corner point
		SXYF64						pi;					// Intercept point from within the pixel
		_isSStoreFloan_lineData		lineData;			// Data computed when this line was stored
	};

	struct _isS_iioss_canvasPolygon_storeFloans
	{
		union {
			u32				_storeFloan_pointToPoint;
			void			(*storeFloan_pointToPoint)		(_isSStoreFloan_lineData* sfld);
		};
	};


//////////
//
// Used by the iioss_canvasPolygon() function to handle passed parameters for divvying
// up work to logical function breakouts.
//
//////
	struct _isSCanvasDrawPolygonParameters
	{
		u32							lnI, lnJ, lnINext, lnFloanCount;
		bool						llLeft;
		u64							lnPixelsDrawn;
		f64							alpc, alp, malp, lfDeltaX, lfDeltaY, lfLength, lfRed, lfGrn, lfBlu;
		SPolyLine*					lpl;
		SBuilder*					corners;		// SXYF64 indicating where the corner falls
		SBGRA*						sbgra;
		SBGRACompute*				sbgrac;
		SBGRACompute*				sbgrac1;
		SBGRACompute*				sbgrac2;
		_isSStoreFloan_lineData		sfld;
		_isSStoreFloan_cornerData*	sfcdRoot;
		_isSStoreFloan_cornerData*	sfcd;
	};

	struct _isSSpannedPixelProcessing
	{
		// Holds canvas information
		SCanvas*			dst;				// Destination for the scale
		SCanvas*			src;				// Source for the scale
		SScaleMap*			sm;					// Scale map being computed
		SBGRACompute*		lastSc;			// Used to rapidly append new entries to the end

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
		f64					ratioV;				// (f64)bio->biHeight	/ (f64)bii->biHeight;
		f64					ratioH;				// (f64)bio->biWidth	/ (f64)bii->biWidth;

		// For iterating through the destination and source, deriving pixel offsets
		s32					offsetSrc;			// Offset to the source pixel for this iteration
		s32					offsetDst;			// Offset to the destination pixel for this iteration

		// Temporary variables used for processing
		// 		SBGRA*				optr;				// Output pointer to the upper-left pixel for this x,y
		// 		SBGRA*				iptra;				// Input pointer to the left-most pixel of the first row (the anchor)
		// 		SBGRA*				iptr;				// Input pointer to the left-most pixel for this y row
		u32					x;					// X-coordinate
		u32					y;					// Y-coordinate
		f64					ulx;				// Upper-left X
		f64					uly;				// Upper-left Y
		f64					lrx;				// Lower-right X
		f64					lry;				// Lower-right Y
		f64					widthLeft;			// Width for each left-most pixel
		f64					widthRight;			// Width for each right-most pixel
		f64					height;				// Height for a particular pixel portion (upper, lower)
		f64					area;				// Temporary computed area for various pixels
		f64					areaSpanned;		// The total area of the spanned pixel
		s32					left;				// Left-side pixel offset into line
		s32					right;				// Number of pixels to reach the right-most pixel
		s32					middleStartH;		// Starting pixel offset for middle span
		s32					middleFinishH;		// Ending pixel offset for middle span
		s32					middleStartV;		// Middle starting pixel
		s32					middleFinishV;		// Middle ending pixel
		s32					rightDelta;			// How far over is the right-most pixel?
		s32					bottomDelta;		// How far over was the bottom-most pixel?
		s32					rowWidth;			// How wide is each row in bytes?

		// Indicates the span from upper-left corner
		bool				spans2H;			// Spans at least 2 pixels horizontally, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 2.x
		bool				spans3H;			// Spans at least 3 pixels horizontally, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 3.x
		bool				spans2V;			// Spans at least 2 pixels vertically, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 2.x
		bool				spans3V;			// Spans at least 3 pixels vertically, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 3.x
	};
