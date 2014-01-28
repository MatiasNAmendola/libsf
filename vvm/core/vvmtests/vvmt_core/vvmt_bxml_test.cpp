//////////
//
// /libsf/vvm/core/vvmtests/vvmt_core/vvmt_BXML_test.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     Mar.02.2013
//////
// Change log:
//     Mar.02.2013	- Initial creation
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
// Top level for running test cases against the BXML engine.
//
//////
	bool ivvmt_testBxml(u64 lnHandleLog)
	{
		SBxml* bxml;


		//////////
		// Indicate what test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_BXML_TESTING);


		//////////
		// Note: These tests cascade, so that if one fails the ones after cannot continue
		//////
			if (!iivvmt_testBxml_1	(lnHandleLog, &bxml))	return false;			// #01 - Process the sample bxml file (in Bxml_test1.h as cgc_Test_Bxml_1_1)
			if (!iivvmt_testBxml_2	(lnHandleLog, bxml))	return false;			// #02 - Save the processed bxml file to disk (should match cgc_Test_Bxml_2_1 in Bxml_test2.h)
			if (!iivvmt_testBxml_3	(lnHandleLog, bxml))	return false;			// #03 - Create a bxml duplicate copy of our input.bxml, then delete it
			if (!iivvmt_testBxml_4	(lnHandleLog, bxml))	return false;			// #04 - Search for nodes, attributes, and data
			if (!iivvmt_testBxml_5	(lnHandleLog, bxml))	return false;			// #05 - Append sibling nodes (append and prepend)
			if (!iivvmt_testBxml_6	(lnHandleLog, bxml))	return false;			// #06 - Append child nodes (append and prepend)
			if (!iivvmt_testBxml_7	(lnHandleLog, bxml))	return false;			// #07 - Append attributes (append and prepend)
			if (!iivvmt_testBxml_8	(lnHandleLog, bxml))	return false;			// #08 - Move sibling nodes (delete, insert before, and insert after)
			if (!iivvmt_testBxml_9	(lnHandleLog, bxml))	return false;			// #09 - Move child nodes (delete, insert before, and insert after)
			if (!iivvmt_testBxml_10	(lnHandleLog, bxml))	return false;			// #10 - Move attributes (delete, insert before, and insert after)
			if (!iivvmt_testBxml_11	(lnHandleLog, bxml))	return false;			// #11 - Delete sibling nodes (first, middle, last)
			if (!iivvmt_testBxml_12	(lnHandleLog, bxml))	return false;			// #12 - Delete child nodes (first, middle, last)
			if (!iivvmt_testBxml_13	(lnHandleLog, bxml))	return false;			// #13 - Delete attributes (first, middle, last)


		//////////
		// When we get here, success
		/////
			vvm_resourcePrintf(IDS_VVM_TEST_BXML_PASSED);
			return true;
	}




//////////
//
// Called to compute the SHA1 of the bxml attribute
//
//////
	void iivvmt_testBxml_computeSha1CallbackBxml(SStartEndCallback* cb)
	{
		SBxmlList*		bxmlList;
		SBxml*			bxml;


		bxmlList	= (SBxmlList*)cb->ptr;
		bxml		= bxmlList->bxml;
		vvm_sha1ComputeSha1_ProcessThisData((u8*)cb->extra, bxml->_name.data._s8, (u32)bxml->_name.length);
	}




//////////
//
// Called to compute the SHA1 of the bxml attribute
//
//////
	void iivvmt_testBxml_computeSha1CallbackBxmla(SStartEndCallback* cb)
	{
		SBxmlaList*	bxmlaList;
		SBxmla*		bxmla;


		bxmlaList	= (SBxmlaList*)cb->ptr;
		bxmla		= bxmlaList->bxmla;
		vvm_sha1ComputeSha1_ProcessThisData((u8*)cb->extra, bxmla->_name.data._s8, (u32)bxmla->_name.length);
	}




//////////
//
// Called to compute the SHA1 of the bxml attribute's data
//
//////
	void iivvmt_testBxml_computeSha1CallbackBxmlaData(SStartEndCallback* cb)
	{
		SBxmlaList*	bxmlaList;
		SBxmla*		bxmla;


		bxmlaList	= (SBxmlaList*)cb->ptr;
		bxmla		= bxmlaList->bxmla;
		vvm_sha1ComputeSha1_ProcessThisData((u8*)cb->extra, bxmla->_data.datum.data._s8, (u32)bxmla->_data.datum.length);
	}




	//////////
	// #01 - Process the sample bxml file (in Bxml_test1.h as cgc_Test_Bxml_1_1)
	//////
		bool iivvmt_testBxml_1(u64 lnHandleLog, SBxml** bxml)
		{
			u64		lnErrorOffset, lnErrorCode, lnSha1As64Bit;
			u32		lnSha1As32Bit;
			u8		sha20Bytes[20];


			// Tell which test we're running
			vvm_resourcePrintf(IDS_VVM_TEST_BXML_1);

			// Make sure the SHA-1 value matches our expectation
			vvm_sha1ComputeSha1((s8*)cgc_Test_Bxml_1_1, sizeof(cgc_Test_Bxml_1_1), sha20Bytes);
			lnSha1As64Bit = vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit = vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgn_Test_Bxml_1_1Sha1As64Bit || lnSha1As32Bit != cgn_Test_Bxml_1_1Sha1As32Bit)
			{
				// The file does not match the expected SHA-1 value
				vvm_resourcePrintf(IDS_VVM_TEST_BXML_INVALID_FILE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Try to load bxml file
			lnErrorOffset	= 0;
			lnErrorCode		= 0;
			*bxml = vvm_bxmlLoadFromBuffer((s8*)cgc_Test_Bxml_1_1, sizeof(cgc_Test_Bxml_1_1) - 1, &lnErrorOffset, &lnErrorCode);
			if (*bxml && lnErrorOffset == 0 && lnErrorCode == 0)
			{
				// Grab the SHA-1 value from the converted file
				lnSha1As64Bit	= vvm_bxmlNodeSha1(*bxml, sha20Bytes);
				lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgnTestBxmlDotHNodeSha1As64Bit || lnSha1As32Bit != cgnTestBxmlDotHNodeSha1As32Bit)
				{
					// The file does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_BXML_INVALID_FILE);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}
				// If we get here, we're good

			} else {
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_BXML_UNABLE_TO_LOAD);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #02 - Save the processed bxml file to disk (should match cgc_Test_Bxml_2_1 in Bxml_test2.h)
	//////
		bool iivvmt_testBxml_2(u64 lnHandleLog, SBxml* bxml)
		{
			u64		lnBytesWritten, lnBytesRead, lnErrorOffset, lnErrorCode, lnSha1As64Bit;
			u32		lnSha1As32Bit;
			u8		sha20Bytes[20];
			s8*		lcFileOut;
			SBxml*	bxml2;


			// Tell which test we're running
			vvm_resourcePrintf(IDS_VVM_TEST_BXML_2);

			// Save the current state to see how she fared
			lcFileOut = oss_sharedAsciiGetTempFilename();
			if (!lcFileOut)
			{
				// Unable to allocate the temporary filename
				vvm_resourcePrintf(IDS_VVM_TEST_BXML_UNABLE_TO_GET_TEMP_FILE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Save the file to disk
			vvm_bxmlSave(bxml, lcFileOut, sizeof(lcFileOut) - 1, true, true, &lnBytesWritten);

			// Try to read it back in, and compare the memory
			bxml2 = vvm_bxmlLoad(lcFileOut, strlen(lcFileOut), &lnBytesRead, &lnErrorOffset, &lnErrorCode);

			// Clean house
			oss_sharedAsciiDeleteFile(lcFileOut);
			oss_free(lcFileOut);

			// Did we read it back in correctly?
			if (!bxml2 || lnErrorCode != 0 || lnBytesRead != lnBytesWritten)
			{
				// Unable to load the temporary file back in correctly
				vvm_resourcePrintf(IDS_VVM_TEST_BXML_UNABLE_TO_RELOAD_TEMP_FILE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, file was loaded properly

			// Grab the SHA-1 value from the loaded file
			lnSha1As64Bit	= vvm_bxmlNodeSha1(bxml2, sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestBxmlDotHNodeSha1As64Bit || lnSha1As32Bit != cgnTestBxmlDotHNodeSha1As32Bit)
			{
				// The file does not match the expected SHA-1 value
				vvm_resourcePrintf(IDS_VVM_TEST_BXML_RELOAD_DOES_NOT_MATCH);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good, the re-loaded file matched the form with which it was
			// saved, and the SHA-1 validation upon reload indicated they were identical.
			// In short, it's time to do a little dance! Woo hoo! :-)

			// Delete the loaded node
			vvm_bxmlNodeDelete(bxml2, true);
			bxml2 = NULL;

			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #03 - Create a bxml duplicate copy of our input.bxml, then delete it
	//////
		// For debugging:
		// vvm_bxmlSave(bxml,		"c:\\temp\\bxml.bxml",		18, true, true, &lnSha1As64Bit);
		// vvm_bxmlSave(bxmlCopy,	"c:\\temp\\bxmlCopy.bxml",	18, true, true, &lnSha1As64Bit);
		bool iivvmt_testBxml_3(u64 lnHandleLog, SBxml* bxml)
		{
			u64		lnSha1As64Bit;
			u32		lnSha1As32Bit;
			bool	llResult;
			SBxml*	bxmlCopy;
			u8		sha20Bytes[20];


			// Tell which test we're running
			vvm_resourcePrintf(IDS_VVM_TEST_BXML_3);

			// Copy the node
			bxmlCopy = vvm_bxmlNodeCopy(bxml, true, true, &llResult);
			if (!bxmlCopy || !llResult)
			{
				// Unable to copy the node
				vvm_resourcePrintf(IDS_VVM_TEST_BXML_COPY_FAILED);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Make sure it copied correctly
			lnSha1As64Bit	= vvm_bxmlNodeSha1(bxmlCopy, sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestBxmlDotHNodeSha1As64Bit || lnSha1As32Bit != cgnTestBxmlDotHNodeSha1As32Bit)
			{
				// The file does not match the expected SHA-1 value
				vvm_resourcePrintf(IDS_VVM_TEST_BXML_RELOAD_DOES_NOT_MATCH);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good, the re-loaded file matched the form with which it was
			// saved, and the SHA-1 validation upon reload indicated they were identical.
			// In short, it's time to do a little dance! Woo hoo! :-)


			// Delete the duplicate node
			vvm_bxmlNodeDelete(bxmlCopy, true);
			bxmlCopy = NULL;

			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #04 - Search for nodes, attributes, and data
	//////
		bool iivvmt_testBxml_4(u64 lnHandleLog, SBxml* bxml)
		{
			u64				lnSha1As64Bit;
			u32				lnSha1As32Bit, lnCount, lnCountAttributes, lnDataCount;
			void*			x;
			u8				sha20Bytes[_SHA1_NUMBER_SIZE];
			u8				context[_SHA1_CONTEXT_SIZE];
			SBxml*			bxmlReference;
			SDatum			wildcardSearch;
			SDatum			wildcardSearchAttributes;
			SDatum			wildcardSearchData;
			SStartEnd		bxmlFinds;
			SStartEnd		bxmlaFinds;
			SStartEnd		bxmlDataFinds;


			//////////
			// Tell which test we're running
			//////
				printf("\tSearch nodes, attributes, data...");


			//////////
			// Initialize
			//////
				wildcardSearch.data._cs8			= cgcTestBxml4FindChildNode;
				wildcardSearch.length				= sizeof(cgcTestBxml4FindChildNode) - 1;
				wildcardSearchAttributes.data._cs8	= cgcTestBxml4FindAttributes;
				wildcardSearchAttributes.length		= sizeof(cgcTestBxml4FindAttributes) - 1;
				wildcardSearchData.data._cs8		= cgcTestBxml4FindData;
				wildcardSearchData.length			= sizeof(cgcTestBxml4FindData) - 1;
				x									= NULL;
				lnCount								= -1;
				lnDataCount							= -1;
				memset(&bxmlFinds, 0, sizeof(bxmlFinds));
				memset(&bxmlaFinds, 0, sizeof(bxmlaFinds));
				memset(&bxmlDataFinds, 0, sizeof (bxmlDataFinds));


			//////////
			// Find our first *child* reference
			//////
 				if (!vvm_bxmlFindFirst(bxml, &bxmlReference, NULL, &wildcardSearch, true, false, &x))
 				{
 					// Was not found, error
 					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
 					return(false);
 				}
				vvm_sha1ComputeSha1(bxmlReference->_name.data._s8, (u32)bxmlReference->_name.length, sha20Bytes);
				lnSha1As64Bit = vvm_sha1Compute64BitFromSha1(sha20Bytes);
				lnSha1As32Bit = vvm_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgnTestBxml41_Sha1As64Bit || lnSha1As32Bit != cgnTestBxml41_Sha1As32Bit)
				{
					// The file does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_BXML_RELOAD_DOES_NOT_MATCH);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Get the count of how many items are found in total
			//////
 				u32 lnFinds = 1;
 				while (vvm_bxmlFindContinue(x))
 					++lnFinds;

				// We should've found 13 separate instances throughout looking for "*child*" (includes child, grandchild, ggrandchild, child2, etc.)
				if (lnFinds != 13)
				{
					// The appropriate number was not found
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Get the node and attribute name finds as lists, compute their SHA-1 values
			//////
				vvm_sha1ComputeSha1_Start(context);
				vvm_bxmlFindAllAsStartEndLists(bxml, &bxmlFinds,	NULL,			&wildcardSearch,			&lnCount,			true, true);
				vvm_bxmlFindAllAsStartEndLists(bxml, NULL,			&bxmlaFinds,	&wildcardSearchAttributes,	&lnCountAttributes,	true, true);

				// Compute SHA-1 of bxml node finds
				SStartEndCallback cb;
				cb._func = (u64)&iivvmt_testBxml_computeSha1CallbackBxml;
				cb.extra = (u64)&context[0];
				vvm_SEChain_iterateThroughForCallback(&bxmlFinds, &cb);
				vvm_SEChain_delete(&bxmlFinds, 0, 0, false);

				// And continue by computing SHA-1 of bxmla attribute name finds on top of the just computed SHA-1 from bxml node finds
				cb._func = (u64)&iivvmt_testBxml_computeSha1CallbackBxmla;
				vvm_SEChain_iterateThroughForCallback(&bxmlaFinds, &cb);
				vvm_SEChain_delete(&bxmlaFinds, 0, 0, false);

				// Determine the SHA-1 based on the finds
				vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, true);
				lnSha1As64Bit = vvm_sha1Compute64BitFromSha1(sha20Bytes);
				lnSha1As32Bit = vvm_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgnTestBxml42_Sha1As64Bit || lnSha1As32Bit != cgnTestBxml42_Sha1As32Bit)
				{
					// The file does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_BXML_RELOAD_DOES_NOT_MATCH);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Get the attribute data finds as lists, compute their sha1 values
			//////
				vvm_sha1ComputeSha1_Start(context);
				vvm_bxmlDataFindAllAsStartEndList(bxml, &bxmlaFinds, &wildcardSearchData, &lnDataCount, true);

				// Compute SHA-1 of bxmla attribute data finds
				cb._func = (u64)&iivvmt_testBxml_computeSha1CallbackBxmlaData;
				vvm_SEChain_iterateThroughForCallback(&bxmlDataFinds, &cb);
				vvm_SEChain_delete(&bxmlDataFinds,	0, 0, false);

				// Determine the SHA-1 based on the finds
				vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, true);
				lnSha1As64Bit = vvm_sha1Compute64BitFromSha1(sha20Bytes);
				lnSha1As32Bit = vvm_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgnTestBxml43_Sha1As64Bit || lnSha1As32Bit != cgnTestBxml43_Sha1As32Bit)
				{
					// The file does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_BXML_RELOAD_DOES_NOT_MATCH);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #05 - Append sibling nodes (append and prepend)
	//////
		bool iivvmt_testBxml_5(u64 lnHandleLog, SBxml* bxml)
		{
			u64			lnSha1As64Bit;
			u32			lnSha1As32Bit;
			SBxml*		bxmlAppend;
			SBxml*		bxmlPrepend;
			SBxml*		bxmlReference;
			SDatum		wildcardSearch;
			u8			sha20Bytes[_SHA1_NUMBER_SIZE];


			//////////
			// Tell which test we're running
			//////
				printf("\tAppend sibling nodes...");


			//////////
			// Create the prepend node to add
			//////
				bxmlPrepend = vvm_bxmlNodeCreate((s8*)cgcTestBxml4PrependNodeName,	sizeof(cgcTestBxml4PrependNodeName) - 1);
				if (!bxmlPrepend)
				{
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Create the append node to add
			//////
				bxmlAppend = vvm_bxmlNodeCreate((s8*)cgcTestBxml4AppendNodeName,	sizeof(cgcTestBxml4AppendNodeName) - 1);
				if (!bxmlAppend)
				{
					// Failure
					vvm_bxmlNodeDelete(bxmlPrepend, true);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Prepend and append the items appropriately
			//////
				wildcardSearch.data._cs8	= cgcTestBxml4FindChildNode;
				wildcardSearch.length		= sizeof(cgcTestBxml4FindChildNode) - 1;
				vvm_bxmlFindFirst(bxml, &bxmlReference, NULL, &wildcardSearch, true, false, NULL);
				// Note:  We know from iivvmt_testBxml_4 that this node will be found at this point

				// Insert one before and after that node
				vvm_bxmlNodeInsert(bxmlPrepend,	bxmlReference, false);
// vvm_bxmlSave(bxml, "c:\\temp\\bxml_prepend.bxml", -1, true, true, NULL);
				vvm_bxmlNodeInsert(bxmlAppend,	bxmlReference, true);
// vvm_bxmlSave(bxml, "c:\\temp\\bxml_append.bxml", -1, true, true, NULL);
				// Note, at this point we leave them installed in the original bxml file, where they are


			//////////
			// Compute the SHA-1
			//////
				lnSha1As64Bit	= vvm_bxmlNodeSha1(bxml, sha20Bytes);
				lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgnTestBxml51_Sha1As64Bit || lnSha1As32Bit != cgnTestBxml51_Sha1As32Bit)
				{
					// The file does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_BXML_RELOAD_DOES_NOT_MATCH);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #06 - Append child nodes (append and prepend)
	//////
		bool iivvmt_testBxml_6(u64 lnHandleLog, SBxml* bxml)
		{
			u64			lnSha1As64Bit;
			u32			lnSha1As32Bit;
			SBxml*		bxmlAppend;
			SBxml*		bxmlPrepend;
			SBxml*		bxmlReference;
			SDatum		wildcardSearch;
			u8			sha20Bytes[_SHA1_NUMBER_SIZE];


			//////////
			// Tell which test we're running
			//////
				printf("\tAppend child nodes...");
	

			//////////
			// Create the prepend node to add
			//////
				bxmlPrepend = vvm_bxmlNodeCreate((s8*)cgcTestBxml6PrependNodeName,	sizeof(cgcTestBxml6PrependNodeName) - 1);
				if (!bxmlPrepend)
				{
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Create the append node to add
			//////
				bxmlAppend = vvm_bxmlNodeCreate((s8*)cgcTestBxml6AppendNodeName,	sizeof(cgcTestBxml6AppendNodeName) - 1);
				if (!bxmlAppend)
				{
					// Failure
					vvm_bxmlNodeDelete(bxmlPrepend, true);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Prepend and append the items appropriately
			//////
				wildcardSearch.data._cs8	= cgcTestBxml6FindChildNode;
				wildcardSearch.length		= sizeof(cgcTestBxml6FindChildNode) - 1;
				vvm_bxmlFindFirst(bxml, &bxmlReference, NULL, &wildcardSearch, true, false, NULL);
				if (!bxmlReference)
				{
					// Failure, node wasn't found
					vvm_bxmlNodeDelete(bxmlPrepend,	true);
					vvm_bxmlNodeDelete(bxmlAppend,	true);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}

				// Insert one before and after that node
				vvm_bxmlNodeInsertAsChild(bxmlPrepend,	bxmlReference, false);
// vvm_bxmlSave(bxml, "c:\\temp\\bxml_cprepend.bxml", -1, true, true, NULL);
				vvm_bxmlNodeInsertAsChild(bxmlAppend,	bxmlReference, true);
// vvm_bxmlSave(bxml, "c:\\temp\\bxml_cappend.bxml", -1, true, true, NULL);
				// Note, at this point we leave them installed in the original bxml file, where they are


			//////////
			// Compute the SHA-1
			//////
				lnSha1As64Bit	= vvm_bxmlNodeSha1(bxml, sha20Bytes);
				lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgnTestBxml61_Sha1As64Bit || lnSha1As32Bit != cgnTestBxml61_Sha1As32Bit)
				{
					// The file does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_BXML_RELOAD_DOES_NOT_MATCH);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #07 - Append attributes (append and prepend)
	//////
		bool iivvmt_testBxml_7(u64 lnHandleLog, SBxml* bxml)
		{
			u64			lnSha1As64Bit;
			u32			lnSha1As32Bit;
			SBxmla*		bxmlaAppend;
			SBxmla*		bxmlaPrepend;
			SBxmla*		bxmlaReference;
			SDatum		wildcardSearch;
			u8			sha20Bytes[_SHA1_NUMBER_SIZE];


			//////////
			// Tell which test we're running
			//////
				printf("\tAppend attributes...");
	

			//////////
			// Create the prepend node to add
			//////
				bxmlaPrepend = vvm_bxmlaCreate((s8*)cgcTestBxml7PrependAttributeName,	sizeof(cgcTestBxml7PrependAttributeName) - 1, NULL, 0, 7);
				if (!bxmlaPrepend)
				{
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Create the append node to add
			//////
				bxmlaAppend = vvm_bxmlaCreate((s8*)cgcTestBxml7AppendAttributeName,	sizeof(cgcTestBxml7AppendAttributeName) - 1, NULL, 0, 7);
				if (!bxmlaAppend)
				{
					// Failure
					vvm_bxmlaDelete(bxmlaPrepend, true);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Prepend and append the items appropriately
			//////
				wildcardSearch.data._cs8	= cgcTestBxml7FindChildAttribute;
				wildcardSearch.length		= sizeof(cgcTestBxml7FindChildAttribute) - 1;
				vvm_bxmlFindFirst(bxml, NULL, &bxmlaReference, &wildcardSearch, true, true, NULL);
				if (!bxmlaReference)
				{
					// Failure, node wasn't found
					vvm_bxmlaDelete(bxmlaPrepend,	true);
					vvm_bxmlaDelete(bxmlaAppend,	true);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}

				// Insert one before and after that node
				vvm_bxmlaInsertExisting(bxmlaReference->_parent, bxmlaReference, bxmlaPrepend, false);
// vvm_bxmlSave(bxml, "c:\\temp\\bxml_aprepend.bxml", -1, true, true, NULL);
				vvm_bxmlaInsertExisting(bxmlaReference->_parent, bxmlaReference, bxmlaAppend, true);
// vvm_bxmlSave(bxml, "c:\\temp\\bxml_aappend.bxml", -1, true, true, NULL);
				// Note, at this point we leave them installed in the original bxml file, where they are


			//////////
			// Compute the SHA-1
			//////
				lnSha1As64Bit	= vvm_bxmlNodeSha1(bxml, sha20Bytes);
				lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgnTestBxml71_Sha1As64Bit || lnSha1As32Bit != cgnTestBxml71_Sha1As32Bit)
				{
					// The file does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_BXML_RELOAD_DOES_NOT_MATCH);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #08 - Move sibling nodes (delete, insert before, and insert after)
	//////
		bool iivvmt_testBxml_8(u64 lnHandleLog, SBxml* bxml)
		{
			u64			lnSha1As64Bit;
			u32			lnSha1As32Bit;
			SBxml*		bxmlReference1;
			SBxml*		bxmlReference2;
			SDatum		wildcardSearch1;
			SDatum		wildcardSearch2;
			u8			sha20Bytes[_SHA1_NUMBER_SIZE];


			//////////
			// Tell which test we're running
			//////
				printf("\tMove sibling nodes...");
	

			//////////
			// Grab items for subsequent delete and insert
			//////
				// Grandchild1
				wildcardSearch1.data._cs8	= cgcTestBxml8FindChildNode1;
				wildcardSearch1.length		= sizeof(cgcTestBxml8FindChildNode1) - 1;
				vvm_bxmlFindFirst(bxml, &bxmlReference1, NULL, &wildcardSearch1, true, false, NULL);
				if (!bxmlReference1)
				{
					// Failure, node wasn't found
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}

				// Grandchild2
				wildcardSearch2.data._cs8	= cgcTestBxml8FindChildNode2;
				wildcardSearch2.length		= sizeof(cgcTestBxml8FindChildNode2) - 1;
				vvm_bxmlFindFirst(bxml, &bxmlReference2, NULL, &wildcardSearch2, true, false, NULL);
				if (!bxmlReference1)
				{
					// Failure, node wasn't found
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Make grandchild2 an orphan
			//////
				vvm_bxmlNodeDelete(bxmlReference2, false);
vvm_bxmlSave(bxml, "c:\\temp\\bxml_8delete.bxml", -1, true, true, NULL);


			//////////
			// Compute the SHA-1
			//////
				lnSha1As64Bit	= vvm_bxmlNodeSha1(bxml, sha20Bytes);
				lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgnTestBxml81_Sha1As64Bit || lnSha1As32Bit != cgnTestBxml81_Sha1As32Bit)
				{
					// The file does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_BXML_RELOAD_DOES_NOT_MATCH);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Insert grandchild2 before grandchild1
			//////
// TODO:  Working here.  I think the insert child is not updating the prev links properly, such as on grandchild1->prev pointing back to prependNode6
				vvm_bxmlNodeInsert(bxmlReference2, bxmlReference1, false);
vvm_bxmlSave(bxml, "c:\\temp\\bxml_8insertbefore.bxml", -1, true, true, NULL);
				// Note, at this point we leave them installed in the original bxml file, where they are


			//////////
			// Compute the SHA-1
			//////
				lnSha1As64Bit	= vvm_bxmlNodeSha1(bxml, sha20Bytes);
				lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgnTestBxml82_Sha1As64Bit || lnSha1As32Bit != cgnTestBxml82_Sha1As32Bit)
				{
					// The file does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_BXML_RELOAD_DOES_NOT_MATCH);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);

			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #09 - Move child nodes (delete, insert before, and insert after)
	//////
		bool iivvmt_testBxml_9(u64 lnHandleLog, SBxml* bxml)
		{
			// Tell which test we're running
			printf("\tMove child nodes...");

			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #10 - Move attributes (delete, insert before, and insert after)
	//////
		bool iivvmt_testBxml_10(u64 lnHandleLog, SBxml* bxml)
		{
			// Tell which test we're running
			printf("\tMove attributes...");

			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #11 - Delete sibling nodes (first, middle, last)
	//////
		bool iivvmt_testBxml_11(u64 lnHandleLog, SBxml* bxml)
		{
			// Tell which test we're running
			printf("\tDelete sibling nodes...");

			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #12 - Delete child nodes (first, middle, last)
	//////
		bool iivvmt_testBxml_12(u64 lnHandleLog, SBxml* bxml)
		{
			// Tell which test we're running
			printf("\tDelete child nodes...");

			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #13 - Delete attributes (first, middle, last)
	//////
		bool iivvmt_testBxml_13(u64 lnHandleLog, SBxml* bxml)
		{
			// Tell which test we're running
			printf("\tDelete attributes...");

			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}
