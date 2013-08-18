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
			if (!iivvmt_testSll_3(lnHandleLog, &root))
				return false;		// failure


		//////////
		// Clean house
		//////
			oss_ll_deleteChain(&root);


		// When we get here, success
		vvm_resourcePrintf(IDS_VVM_TEST_SLL_PASSED);
		return true;
	}




//////////
//
// The 2-way link-list test builds everything off the root.  This function adds the previous
// and next nodes.
//	 ____ ____ ____ 
//	| p1 |root| n1 |
//	|____|____|____|
//
//////
	bool iivvmt_testSll_1(u64 lnHandleLog, SLL** root)
	{
		SLLCallback		cb;
		u64				lnSha1As64Bit;
		u32				lnSha1As32Bit;
		u8				sha20Bytes[20];
		u8				context[92];
		SLL*			nodePrev;
		SLL*			nodeNext;


		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL_CREATE);


		//////////
		// Create a single node
		//////
			*root = i3vvmt_testSll_1_createSll(cgnLlBufferSize);
			if (!*root)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// Initialize our callback data
			cb._func	= (u64)&i3vvmt_testSll_1_sha1Callback;
			cb.node		= *root;
			cb.extra1	= (u64)&context[0];
			cb.extra2	= (u64)&sha20Bytes[0];


		//////////
		// Determine the SHA-1 on that one node
		//////
			oss_sha1ComputeSha1_Start(context);
			oss_ll_iterateViaCallback(&cb);
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


		//////////
		// Create a node to go before
		//////
			nodePrev = i3vvmt_testSll_1_createSll(cgnLlBufferSize);
			if (!nodePrev)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go after
		//////
			nodeNext = i3vvmt_testSll_1_createSll(cgnLlBufferSize);
			if (!nodeNext)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Insert the node after
		//////
			oss_ll_insert(nodeNext, *root, true);


		//////////
		// Determine the SHA-1 on the two nodes
		//////
			oss_sha1ComputeSha1_Start(context);
			oss_ll_iterateViaCallback(&cb);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl2NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl2NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node before
		//////
			oss_ll_insert(nodePrev, *root, false);


		//////////
		// Determine the SHA-1 on the three nodes
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodePrev;
			oss_ll_iterateViaCallback(&cb);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl3NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl3NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Determine the SHA-1 on the three nodes going backwards
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodeNext;
			oss_ll_iterateBackwardViaCallback(&cb);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl4NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl4NodeSha1As32Bit)
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




//////////
//
// This test adds the "1" nodes, which make the former "1" nodes become "2" nodes, as they are
// 2 hops away from root.
//	 ____ ____ ____ ____ ____ 
//	| p2 | p1 |root| n1 | n2 |
//	|____|____|____|____|____|
//
//////
	bool iivvmt_testSll_2(u64 lnHandleLog, SLL* root)
	{
		SLLCallback		cb;
		u64				lnSha1As64Bit;
		u32				lnSha1As32Bit;
		u8				sha20Bytes[20];
		u8				context[92];
		SLL*			nodePrev;
		SLL*			nodeNext;


		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL_APPEND);


		//////////
		// Prepare for our callbacks
		//////
			cb._func	= (u64)&i3vvmt_testSll_1_sha1Callback;
			cb.node		= root->prev;
			cb.extra1	= (u64)&context[0];
			cb.extra2	= (u64)&sha20Bytes[0];


		//////////
		// Create a node to go before
		//////
			nodePrev = i3vvmt_testSll_1_createSll(cgnLlBufferSize);
			if (!nodePrev)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go after
		//////
			nodeNext = i3vvmt_testSll_1_createSll(cgnLlBufferSize);
			if (!nodeNext)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Insert the node after
		//////
			oss_ll_insert(nodeNext, root, true);


		//////////
		// Determine the SHA-1 on that one node
		//////
			oss_sha1ComputeSha1_Start(context);
			oss_ll_iterateViaCallback(&cb);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl5NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl5NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node before
		//////
			oss_ll_insert(nodePrev, root, false);


		//////////
		// Determine the SHA-1 on that one node
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodePrev->prev;
			oss_ll_iterateViaCallback(&cb);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl6NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl6NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Determine the SHA-1 on that one node
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodeNext->next;
			oss_ll_iterateBackwardViaCallback(&cb);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl7NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl7NodeSha1As32Bit)
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




	bool iivvmt_testSll_3(u64 lnHandleLog, SLL** root)
	{
		SLLCallback		cb;
		u64				lnSha1As64Bit;
		u32				lnSha1As32Bit;
		u8				sha20Bytes[20];
		u8				context[92];
		SLL*			nodePrev;


		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL_DELETE);


		//////////
		// Prepare for our callbacks
		//////
			cb._func	= (u64)&i3vvmt_testSll_1_sha1Callback;
			cb.node		= (*root)->prev;
			cb.extra1	= (u64)&context[0];
			cb.extra2	= (u64)&sha20Bytes[0];


		//////////
		// Delete the first node
		//////
			oss_ll_delete((*root)->prev->prev);


		//////////
		// Determine the SHA-1 on that one node
		//////
			oss_sha1ComputeSha1_Start(context);
			oss_ll_iterateViaCallback(&cb);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl8NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl8NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete the last node
		//////
			oss_ll_delete((*root)->next->next);


		//////////
		// Determine the SHA-1 on that one node
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = (*root)->prev;
			oss_ll_iterateViaCallback(&cb);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl9NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl9NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete the last node
		//////
			// Get what will become the new root, which is the first item
			nodePrev = (*root)->prev;

			// Delete the middle node
			oss_ll_delete(*root);

			// Store the new root
			*root = nodePrev;


		//////////
		// Determine the SHA-1 on the remaining two nodes going forward
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodePrev;
			oss_ll_iterateViaCallback(&cb);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl10NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl10NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Determine the SHA-1 on the remaining two nodes going backward
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodePrev->next;
			oss_ll_iterateBackwardViaCallback(&cb);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl11NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl11NodeSha1As32Bit)
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
					llInit[lnI] = oss_getPredictableSequentialPattern(lnI, gnLlInitializerValue++);
			}


		//////////
		// Indicate our success or failure
		//////
			return(ll);
	}




	void i3vvmt_testSll_1_sha1Callback(SLLCallback* cb)
	{
		if (cb)
		{
			// Conduct our processing
			oss_sha1ComputeSha1_ProcessThisData((u8*)cb->extra1, (s8*)cb->node + sizeof(SLL), cgnLlBufferSize);
		}
	}
