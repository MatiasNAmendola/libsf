//////////
//
// /libsf/utils/dsf/msvc++/dsf/dsf/builder.cpp
//
//////
//
//
//////
// Version 0.60
// Copyright (c) 2013 by Rick C. Hodgin
//////
// Last update:
//     Dec.02.2013
//////
// Change log:
//     Dec.02.2013	- Initial creation
//////
//
// This file is self-contained and handles all builder algorithms.  It can be used as an include
// file for other stand-alone projects.  It was extracted from the Visual FreePro Virtual Machine.
//
//////////
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




// A builder is a buffer accumulator
struct SBuilder
{
	s8*			data;												// Pointer to a buffer allocated in blocks
	u32			allocatedLength;									// How much of space has been allocated for the buffer
	u32			populatedLength;									// How much of the allocated buffer is actually populated with data
	u32			allocateBlockSize;									// Typically 16KB, the larger the size the fewer reallocs() are required
};




//////////
//
// Called to ensure the indicated number of bytes can be appended onto the buffer without
// issue.  If not, reallocates the buffer.
//
//////
	void iBuilder_verifySizeForNewBytes(SBuilder* buffRoot, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot && tnDataLength != 0)
		{
			// Repeatedly allocate our allocation size until we get big enough
			while (buffRoot->data)
			{
				// Are we there yet?
				if (buffRoot->populatedLength + tnDataLength < buffRoot->allocatedLength)
				{
					// We're good, update our populated size
					buffRoot->populatedLength += tnDataLength;
					return;
				}
				// If we get here, we need to allocate more space

				// Reallocate and continue
				buffRoot->data				= (s8*)realloc(buffRoot->data, buffRoot->allocatedLength + buffRoot->allocateBlockSize);
				buffRoot->allocatedLength	+= buffRoot->allocateBlockSize;
			}
		}
		// If we get here, there's been an error
	}




//////////
//
// Initializes a new buffer to the default allocation size.
// No content is changed.
//
// Returns:  
//		Pointer to the point in the buffer where the
//////
	void builder_createAndInitialize(SBuilder** buffRoot, u32 tnAllocationBlockSize)
	{
		SBuilder*	buffNew;


		// See if they want to use the default size
		if (tnAllocationBlockSize == -1)
			tnAllocationBlockSize = 16384;

		// Make sure our environment is sane
		if (buffRoot && tnAllocationBlockSize != 0)
		{
			buffNew = (SBuilder*)malloc(sizeof(SBuilder));
			if (buffNew)
			{
				// Initialize
				memset(buffNew, 0, sizeof(SBuilder));

				// Store the pointer
				*buffRoot = buffNew;

				// Make sure our allocation block size is at least 4KB
				tnAllocationBlockSize		= max(4096, tnAllocationBlockSize);

				// Allocate the data space
				buffNew->data				= (s8*)malloc(tnAllocationBlockSize);

				// If we allocated, we're good
				if (buffNew->data)
				{
					buffNew->allocatedLength = tnAllocationBlockSize;
					memset(buffNew->data, 0, tnAllocationBlockSize);

				} else {
					buffNew->allocatedLength = 0;
				}

				// Update the allocation size
				buffNew->allocateBlockSize	= tnAllocationBlockSize;
			}
		}
	}




//////////
//
// Appends the indicated text to the end of the buffer.
//
// Returns:  
//		Pointer to the point in the buffer where the text was inserted, can be used
//		for a furthering or continuance of this function embedded in a higher call.
//////
	s8* builder_appendData(SBuilder* buffRoot, s8* tcData, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot)
		{
			// If they want us to populate the length, do so
			if (tnDataLength == -1)
				tnDataLength = (u32)strlen(tcData);

			// If there's anything to do, do it
			if (tnDataLength != 0)
			{
				// Make sure this much data will fit there in the buffer
				iBuilder_verifySizeForNewBytes(buffRoot, tnDataLength);

				// If we're still valid, proceed with the copy
				if (buffRoot->data && tcData)
					memcpy(buffRoot->data + buffRoot->populatedLength - tnDataLength, tcData, tnDataLength);
			}
			// Indicate where the start of that buffer is
			return(buffRoot->data + buffRoot->populatedLength - tnDataLength);
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Called to allocate bytes in the builder, but not yet populate them with anything
//
//////
	s8* builder_allocateBytes(SBuilder* buffRoot, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot)
		{
			// Make sure this much data will fit there in the buffer
			if (tnDataLength != 0)
				iBuilder_verifySizeForNewBytes(buffRoot, tnDataLength);
			
			// Indicate where the start of that buffer is
			return(buffRoot->data + buffRoot->populatedLength - tnDataLength);
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Specifies the size the buffer should be.  Either allocates up or down. No content
// is changed, however the buffer pointer value could be changed from oss_realloc().
// In addition, this function should not be used for resizing in general.  Simply call
// the builder_AppendData() function and it will automatically resize if needed, as
// per the allocated block size.
//
//////
	void builder_setSize(SBuilder* buffRoot, u32 tnBufferLength)
	{
		s8* lcNew;


		// Make sure our environment is sane
		if (buffRoot)
		{
			//////////
			// See if they want to make it whatever the populated size is
			//////
				if (tnBufferLength == -1)
					tnBufferLength = buffRoot->populatedLength;


			//////////
			// See if they're releasing everything
			//////
				if (tnBufferLength == 0)
				{
					//////////
					// They are freeing everything
					//////
						free(buffRoot->data);
						buffRoot->data				= NULL;
						buffRoot->populatedLength	= 0;
						buffRoot->allocatedLength	= 0;


				} else if (tnBufferLength != buffRoot->allocatedLength) {
					//////////
					// They are resizing
					//////
						lcNew = (s8*)realloc(buffRoot->data, tnBufferLength);
						if (lcNew)
						{
							//////////
							// Set the allocated length
							//////
								buffRoot->data				= lcNew;
								buffRoot->allocatedLength	= tnBufferLength;


							//////////
							// If our populated length no longer fits into the new allocated space, then adjust it down
							//////
								if (buffRoot->populatedLength > buffRoot->allocatedLength)
									buffRoot->populatedLength = buffRoot->allocatedLength;		// Bring the populated area down to the new size

						} else {
							// Failure on resize -- should not happen
							_asm int 3;
						}
				}
		}
	}




//////////
//
// Releases the buffer allocated for the SBuilder structure
//
//////
	void builder_FreeAndRelease(SBuilder** buffRoot)
	{
		SBuilder* buffDelete;


		// Make sure our environment is sane
		if (buffRoot && *buffRoot)
		{
			// Copy our *buffRoot pointer to local space so we can "appear" to kill it before it's actually killed
			buffDelete	= *buffRoot;
			*buffRoot	= NULL;

			// Release the data buffer
			if (buffDelete->data)
			{
				// Trim our sizes down to 0
				buffDelete->allocatedLength = 0;
				buffDelete->populatedLength = 0;

				// Release our buffer
				free(buffDelete->data);

				// Mark it as no longer valid
				buffDelete->data = NULL;
			}

			// Release the SBuilder structure
			free(buffDelete);
		}
	}




//////////
//
// Called to write out the indicated builder file as an 8-bit ASCII file
//
//////
	u32 builder_asciiWriteOutFile(SBuilder* buffRoot, s8* tcFilename)
	{
		FILE* lfh;


		// Make sure there's something to write
		if (buffRoot && tcFilename)	
		{
			// Try to create the file
			lfh = fopen(tcFilename, "wb+");
			if (lfh)
			{
				// Write out the data if need be
				if (buffRoot->data && buffRoot->populatedLength != 0)
				{
					fwrite(buffRoot->data, 1, buffRoot->populatedLength, lfh);
					fclose(lfh);
					return(buffRoot->populatedLength);
				}
				// If we get here, nothing to write
				fclose(lfh);
				return(0);
			}
		}
		// If we get here, failure
		return(-1);
	}
