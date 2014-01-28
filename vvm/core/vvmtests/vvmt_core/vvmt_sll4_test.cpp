//////////
//
// /libsf/vvm/core/vvmtests/vvmt_core/vvmt_sll4_test.cpp
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
	bool ivvmt_testSll4(u64 lnHandleLog)
	{
		SLL4* root;


		// Indicate which test
		vvm_resourcePrintf(IDS_VVM_TEST_SLL4_TESTING);


		//////////
		// #01 - Create a nine element 4-way linked list, one in the middle, and two extending out in all four directions
		//////
			if (!iivvmt_testSll4_1(lnHandleLog, &root))
				return false;		// failure


		//////////
		// #02 - Append a chain
		//////
			if (!iivvmt_testSll4_2(lnHandleLog, root))
				return false;		// failure


		//////////
		// #03 - Delete everything in pieces and in chains
		//////
			if (!iivvmt_testSll4_3(lnHandleLog, &root))
				return false;		// failure


		//////////
		// #04 - Re-create everything as in test #01, then delete the entire chain
		//////
			if (!iivvmt_testSll4_4(lnHandleLog, &root))
				return false;		// failure


		// When we get here, success
		vvm_resourcePrintf(IDS_VVM_TEST_SLL4_PASSED);
		return true;
	}




//////////
//
// The 4-way link-list test builds everything off the root.  It first adds the "2" nodes,
// which initially occupy the positions immediate off root.  It then adds the "1" nodes, which
// are inserted between the "2" nodes and root in each direction.
//
//	           ____ north
//	          | n2 |
//	          |____|
//	          | n1 |
//	 ____ ____|____|____ ____ 
//	| w2 | w1 |root| e1 | e2 |
//	|____|____|____|____|____|
//	west      | s1 |      east
//	          |____|
//	          | s2 |
//	          |____|
//       south
//////
	bool iivvmt_testSll4_1(u64 lnHandleLog, SLL4** root)
	{
		SLL4Callback	cb;
		u64				lnSha1As64Bit;
		u32				lnSha1As32Bit;
		u8				sha20Bytes[20];
		u8				context[92];
		SLL4*			nodeNorth2;
		SLL4*			nodeSouth2;
		SLL4*			nodeWest2;
		SLL4*			nodeEast2;
		SLL4*			nodeNorth1;
		SLL4*			nodeSouth1;
		SLL4*			nodeWest1;
		SLL4*			nodeEast1;


		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL4_CREATE);


		//////////
		// Create a single node
		//////
			*root = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!*root)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// Initialize our callback data
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.extra1	= (u64)&context[0];
			cb.extra2	= (u64)&sha20Bytes[0];


		//////////
		// Determine the SHA-1 on that one node
		//////
			vvm_sha1ComputeSha1_Start(context);
			cb.node = *root;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest1Ll41NodeSha1As64Bit || lnSha1As32Bit != cgnTest1Ll41NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Create a node to go to the west
		//////
			nodeWest2 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeWest2)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the east
		//////
			nodeEast2 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeEast2)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the north
		//////
			nodeNorth2 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeNorth2)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the south
		//////
			nodeSouth2 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeSouth2)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Insert the node to the west
		//////
			vvm_ll4_insertWestEast(nodeWest2, *root, false);


		//////////
		// Determine the SHA-1 on the two nodes
		//////
			vvm_sha1ComputeSha1_Start(context);
			cb.node = nodeWest2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = *root;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest1Ll42NodeSha1As64Bit || lnSha1As32Bit != cgnTest1Ll42NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the east
		//////
			vvm_ll4_insertWestEast(nodeEast2, *root, true);


		//////////
		// Determine the SHA-1 on the three nodes
		//////
			vvm_sha1ComputeSha1_Start(context);
			cb.node = nodeWest2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest1Ll43NodeSha1As64Bit || lnSha1As32Bit != cgnTest1Ll43NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the north
		//////
			vvm_ll4_insertNorthSouth(nodeNorth2, *root, false);


		//////////
		// Determine the SHA-1 on the two nodes
		//////
			vvm_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = *root;
			vvm_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest1Ll44NodeSha1As64Bit || lnSha1As32Bit != cgnTest1Ll44NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the south
		//////
			vvm_ll4_insertNorthSouth(nodeSouth2, *root, true);


		//////////
		// Determine the SHA-1 on the three nodes
		//////
			vvm_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = nodeSouth2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest1Ll45NodeSha1As64Bit || lnSha1As32Bit != cgnTest1Ll45NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Create a node to go to the west
		//////
			nodeWest1 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeWest1)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the east
		//////
			nodeEast1 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeEast1)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the north
		//////
			nodeNorth1 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeNorth1)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the south
		//////
			nodeSouth1 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeSouth1)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Insert the node to the west
		//////
			vvm_ll4_insertWestEast(nodeWest1, *root, false);


		//////////
		// Determine the SHA-1 on the two nodes
		//////
			vvm_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = nodeSouth2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest1Ll46NodeSha1As64Bit || lnSha1As32Bit != cgnTest1Ll46NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the east
		//////
			vvm_ll4_insertWestEast(nodeEast1, *root, true);


		//////////
		// Determine the SHA-1 on the three nodes
		//////
			vvm_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = nodeSouth2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest1Ll47NodeSha1As64Bit || lnSha1As32Bit != cgnTest1Ll47NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the north
		//////
			vvm_ll4_insertNorthSouth(nodeNorth1, *root, false);


		//////////
		// Determine the SHA-1 on the two nodes
		//////
			vvm_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = nodeSouth2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest1Ll48NodeSha1As64Bit || lnSha1As32Bit != cgnTest1Ll48NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the south
		//////
			vvm_ll4_insertNorthSouth(nodeSouth1, *root, true);


		//////////
		// Determine the SHA-1 on the three nodes
		//////
			vvm_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = nodeSouth2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest1Ll49NodeSha1As64Bit || lnSha1As32Bit != cgnTest1Ll49NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
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
// The 4-way link-list will be of the w2..e2 and n2..s2 form.  This process creates a north/south
// chain and inserts it west of w2, calling it x1..x5.  After doing this, it deletes x2, then x5,
// then x3, then x4, leaving x1.  Then it deletes x1, e2, w1, then the chain east from e1, and west
// from w2.  Then it deletes the chain north from n1, and south from s1, leaving only root.
//
//	                    ____ north
//	                   | n2 |
//	                   |____|
//	                   | n1 |
//	     ____ ____ ____|____|____ ____ 
//	    | x1 | w2 | w1 |root| e1 | e2 |
//	    |____|____|____|____|____|____|
//	    | x2 |west     | s1 |      east
//	    |____|         |____|
//	    | x3 |         | s2 |
//	    |____|         |____|
//	    | x4 |               south
//	    |____|
//	    | x5 |
//	    |____|
//
//////
	bool iivvmt_testSll4_2(u64 lnHandleLog, SLL4* root)
	{
		SLL4Callback	cb;
		u64				lnSha1As64Bit;
		u32				lnSha1As32Bit;
		u8				sha20Bytes[20];
		u8				context[92];
		u32				lnCount;
		SLL4*			ll4x1;
		SLL4*			ll4w1;
		SLL4*			ll4w2;
		SLL4*			ll4e1;
		SLL4*			ll4e2;
		SLL4*			ll4n1;
		SLL4*			ll4n2;
		SLL4*			ll4s1;
		SLL4*			ll4s2;


		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL4_APPEND);


		///////////
		// Verify we still have our root setup properly
		//////
			// Check w2..root
			if (!root->west || !root->west->west || root->west->west->west)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_CORRUPT_ROOT_STRUCTURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// Check root..e2
			if (!root->east || !root->east->east || root->east->east->east)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_CORRUPT_ROOT_STRUCTURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// Check root..n2
			if (!root->north || !root->north->north || root->north->north->north)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_CORRUPT_ROOT_STRUCTURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// Check root..s2
			if (!root->south || !root->south->south || root->south->south->south)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_CORRUPT_ROOT_STRUCTURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab w2 by navigation the chain
			ll4w2 = vvm_ll4_getLastNode(root, _LL4_WEST);
			if (ll4w2 != root->west->west)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab w1
			ll4w1 = ll4w2->east;
			if (ll4w1 != root->west)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab e2 by navigation the chain
			ll4e2 = vvm_ll4_getLastNode(root, _LL4_EAST);
			if (ll4e2 != root->east->east)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab e1
			ll4e1 = ll4e2->west;
			if (ll4e1 != root->east)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab n2 by navigation the chain
			ll4n2 = vvm_ll4_getLastNode(root, _LL4_NORTH);
			if (ll4n2 != root->north->north)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab n1
			ll4n1 = ll4n2->south;
			if (ll4n1 != root->north)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab s2 by navigation the chain
			ll4s2 = vvm_ll4_getLastNode(root, _LL4_SOUTH);
			if (ll4s2 != root->south->south)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab s1
			ll4s1 = ll4s2->north;
			if (ll4s1 != root->south)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create the chain
		//////
			lnCount	= 5;
			ll4x1	= vvm_ll4_createChain(cgnLl4BufferSize, &lnCount, _LL4_SOUTH);
			if (lnCount != 5 || !ll4x1)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Populate the chain with known data
		//////
			cb._func	= (u64)&i3vvmt_testSll4_initiallyPopulateCallback;
			cb.node		= ll4x1;
			cb.extra1	= (u64)&context[0];
			cb.extra2	= (u64)&sha20Bytes[0];
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);


		//////////
		// Validate that it was setup and populated correctly
		//////
			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= ll4x1;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll41NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll41NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Attach x1 onto w2's west, and validate it's on there good
		//////
			vvm_ll4_insertWestEast(ll4x1, ll4w2, false);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= ll4e2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			cb.node		= ll4x1;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll42NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll42NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		// If we get here, we're good, only root remains
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




//////////
//
// #03 - Delete everything in pieces and in chains
//
//////
	bool iivvmt_testSll4_3(u64 lnHandleLog, SLL4** root)
	{
		SLL4Callback	cb;
		u64				lnSha1As64Bit;
		u32				lnSha1As32Bit;
		u8				sha20Bytes[20];
		u8				context[92];
		SLL4*			ll4x1;
		SLL4*			ll4x2;
		SLL4*			ll4x3;
		SLL4*			ll4x4;
		SLL4*			ll4x5;
		SLL4*			ll4w1;
		SLL4*			ll4w2;
		SLL4*			ll4e1;
		SLL4*			ll4e2;
		SLL4*			ll4n1;
		SLL4*			ll4n2;
		SLL4*			ll4s1;
		SLL4*			ll4s2;


		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL4_DELETE);


		///////////
		// Verify we still have our root setup properly
		//////
			// Check w2..root
			if (!(*root)->west || !(*root)->west->west || !(*root)->west->west->west)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_CORRUPT_ROOT_STRUCTURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// Check root..e2
			if (!(*root)->east || !(*root)->east->east || (*root)->east->east->east)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_CORRUPT_ROOT_STRUCTURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// Check root..n2
			if (!(*root)->north || !(*root)->north->north || (*root)->north->north->north)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_CORRUPT_ROOT_STRUCTURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// Check root..s2
			if (!(*root)->south || !(*root)->south->south || (*root)->south->south->south)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_CORRUPT_ROOT_STRUCTURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab w2 by navigation the chain
			ll4x1 = vvm_ll4_getLastNode(*root, _LL4_WEST);
			if (ll4x1 != (*root)->west->west->west)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab w2
			ll4w2 = ll4x1->east;
			if (ll4w2 != (*root)->west->west)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab w1
			ll4w1 = ll4w2->east;
			if (ll4w1 != (*root)->west)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab e2 by navigation the chain
			ll4e2 = vvm_ll4_getLastNode(*root, _LL4_EAST);
			if (ll4e2 != (*root)->east->east)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab e1
			ll4e1 = ll4e2->west;
			if (ll4e1 != (*root)->east)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab n2 by navigation the chain
			ll4n2 = vvm_ll4_getLastNode(*root, _LL4_NORTH);
			if (ll4n2 != (*root)->north->north)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab n1
			ll4n1 = ll4n2->south;
			if (ll4n1 != (*root)->north)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab s2 by navigation the chain
			ll4s2 = vvm_ll4_getLastNode(*root, _LL4_SOUTH);
			if (ll4s2 != (*root)->south->south)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab s1
			ll4s1 = ll4s2->north;
			if (ll4s1 != (*root)->south)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}

			// Grab each item down from ll4x1
			if (!ll4x1->south || !ll4x1->south->south || !ll4x1->south->south->south || !ll4x1->south->south->south->south)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_NAVIGATE_CHAIN);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			ll4x2 = ll4x1->south;
			ll4x3 = ll4x2->south;
			ll4x4 = ll4x3->south;
			ll4x5 = ll4x4->south;


		//////////
		// Delete x2
		//////
			vvm_ll4_delete(ll4x2);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= ll4x1;
			cb.extra1	= (u64)&context[0];
			cb.extra2	= (u64)&sha20Bytes[0];
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node		= ll4x5;
			vvm_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll43NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll43NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete x5
		//////
			vvm_ll4_delete(ll4x5);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= ll4x1;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node		= ll4x4;
			vvm_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll44NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll44NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete x3
		//////
			vvm_ll4_delete(ll4x3);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= ll4x1;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node		= ll4x4;
			vvm_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll45NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll45NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete x4
		//////
			vvm_ll4_delete(ll4x4);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= ll4x1;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll46NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll46NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete x1
		//////
			vvm_ll4_delete(ll4x1);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= ll4e2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll47NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll47NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete e2
		//////
			vvm_ll4_delete(ll4e2);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= ll4e1;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			cb.node		= ll4w2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll48NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll48NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete w1
		//////
			vvm_ll4_delete(ll4w1);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= ll4e1;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			cb.node		= ll4w2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll49NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll49NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete e1 and chain east
		//////
			vvm_ll4_deleteChain(&ll4e1, _LL4_EAST);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= *root;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			cb.node		= ll4w2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll410NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll410NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete w2 and chain west
		//////
			vvm_ll4_deleteChain(&ll4w2, _LL4_WEST);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= *root;
			vvm_ll4_iterateViaCallback(&cb, _LL4_WEST);
			vvm_ll4_iterateViaCallback(&cb, _LL4_EAST);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll411NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll411NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete n1 and chain north
		//////
			vvm_ll4_deleteChain(&ll4n1, _LL4_NORTH);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= ll4s2;
			vvm_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll412NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll412NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete s1 and chain south
		//////
			vvm_ll4_deleteChain(&ll4s1, _LL4_SOUTH);

			vvm_sha1ComputeSha1_Start(context);
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.node		= *root;
			vvm_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			vvm_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			vvm_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= vvm_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= vvm_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTest2Ll413NodeSha1As64Bit || lnSha1As32Bit != cgnTest2Ll413NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Delete root and chain south
		//////
			vvm_ll4_deleteChain(root, _LL4_SOUTH);
			if (*root)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
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
// #04 - Re-create everything as in test #01, then delete the entire chain
//
//////
	bool iivvmt_testSll4_4(u64 lnHandleLog, SLL4** root)
	{
		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL4_DELETE_CHAIN);


		//////////
		// Populate the root with our original 9-panel arrangement
		// Note:  If we are at this point it the test, we know it will pass
		//////
			iivvmt_testSll4_1(lnHandleLog, root);


		//////////
		// Clean house
		//////
			vvm_ll4_deleteChain(root, _LL4_ALL);
			if (*root)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE_AFTER_DELETE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




	SLL4* i3vvmt_testSll4_1_createSll4(u32 tnSize)
	{
		SLL4* ll4;
		
		
		//////////
		// Create the SLL
		//////
			ll4 = vvm_ll4_create(NULL, NULL, NULL, NULL, vvm_getNextUniqueId(), tnSize);


		//////////
		// Prepare that value
		//////
			if (ll4)
				i3vvmt_testSll4_initiallyPopulate(ll4, tnSize);


		//////////
		// Indicate our success or failure
		//////
			return(ll4);
	}




	void i3vvmt_testSll4_initiallyPopulateCallback(SLL4Callback* cb)
	{
		// Pass along to the initialization function
		i3vvmt_testSll4_initiallyPopulate(cb->node, cgnLl4BufferSize);
	}




	void i3vvmt_testSll4_initiallyPopulate(SLL4* ll4, u32 tnSize)
	{
		u32		lnI;
		u8*		llInit;


		// Iterate through every portion to initialize
		llInit = (u8*)ll4 + sizeof(SLL4);
		for (lnI = 0; lnI < tnSize; lnI++)
			llInit[lnI] = vvm_getPredictableSequentialPattern(lnI, gnLlInitializerValue++);

	}




	void i3vvmt_testSll4_1_sha1Callback(SLL4Callback* cb)
	{
		if (cb)
		{
			// Conduct our processing
			vvm_sha1ComputeSha1_ProcessThisData((u8*)cb->extra1, (s8*)cb->node + sizeof(SLL4), cgnLlBufferSize);
		}
	}
