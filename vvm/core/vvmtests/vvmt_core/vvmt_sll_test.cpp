//////////
//
// /libsf/vvm/core/vvmtests/vvmt_core/vvmt_sll_test.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     Jul.24.2013
//////
// Change log:
//     Jul.24.2013	- Initial creation
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
// Top level for running test cases against the SHA-1 engine.
//
//////
	bool ivvmt_testSll(u64 lnHandleLog)
	{
		SLL* root;


		// Indicate which test
		vvm_resourcePrintf(IDS_VVM_TEST_SLL_TESTING);


		//////////
		// #01 - Create a three element linked list
		//////
			if (!iivvmt_testSll_1(lnHandleLog, &root))
				return false;		// failure


		//////////
		// #02 - Append an item before and after the middle item, then before and after the beginning and ending items
		//////
			if (!iivvmt_testSll_2(lnHandleLog, root))
				return false;		// failure


		//////////
		// #03 - Delete first item, last item, middle item
		//////
			if (!iivvmt_testSll_3(lnHandleLog, root))
				return false;		// failure


		//////////
		// Clean house
		//////
			oss_ll_deleteChainWithCallback(root, NULL, 0);

		// When we get here, success
		vvm_resourcePrintf(IDS_VVM_TEST_SLL_PASSED);
		return true;
	}




	bool iivvmt_testSll_1(u64 lnHandleLog, SLL** root)
	{
		SOssCbData2Void		cb;
		u64					lnSha1As64Bit;
		u32					lnSha1As32Bit;
		u8					sha20Bytes[20];
		u8					context[92];


		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL_CREATE);


		//////////
		// Create a single node
		//////
			*root = i3vvmt_testSll_1_createSll(cgnBufferSize);
			if (!*root)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Determine the SHA-1 on it
		//////
			oss_sha1ComputeSha1_Start(context);

			cb._callback	= (u64)&i3vvmt_testSll_1_sha1Callback;
			cb.extra1		= (u64)&context[0];
			cb.extra2		= (u64)&sha20Bytes[0];
			oss_ll_iterateViaCallback(*root, &cb);

			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl1NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl1NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




	bool iivvmt_testSll_2(u64 lnHandleLog, SLL* root)
	{
		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL_APPEND);


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




	bool iivvmt_testSll_3(u64 lnHandleLog, SLL* root)
	{
		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL_DELETE);


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




	SLL* i3vvmt_testSll_1_createSll(u32 tnSize)
	{
		u32		lnI;
		SLL*	ll;
		u8*		llInit;
		
		
		//////////
		// Create the SLL
		//////
			ll = oss_ll_create(NULL, NULL, oss_getNextUniqueId(), tnSize);


		//////////
		// Prepare that value
		//////
			if (ll)
			{
				// Iterate through every portion to initialize
				llInit = (u8*)ll + sizeof(SLL);
				for (lnI = 0; lnI < tnSize; lnI++)
					llInit[lnI] = oss_getPredictableSequentialPattern(lnI, gnInitializerValue++);
			}


		//////////
		// Indicate our success or failure
		//////
			return(ll);
	}




	void i3vvmt_testSll_1_sha1Callback(SOssCbData2Void* cb)
	{
		if (cb)
		{
			// Conduct our processing
			oss_sha1ComputeSha1_ProcessThisData((u8*)cb->extra1, (s8*)cb->ptr + sizeof(SLL), cgnBufferSize);
		}
	}
