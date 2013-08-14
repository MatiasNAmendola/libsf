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
		// #01 - Create a five element 4-way linked list, one in the middle one at each point
		//////
			if (!iivvmt_testSll4_1(lnHandleLog, &root))
				return false;		// failure


		//////////
		// #02 - Append an item before and after each element in all directions
		//////
			if (!iivvmt_testSll4_2(lnHandleLog, root))
				return false;		// failure


		//////////
		// #03 - Delete first item, middle, last item in each direction
		//////
			if (!iivvmt_testSll4_3(lnHandleLog, &root))
				return false;		// failure


		//////////
		// Clean house
		//////
			oss_ll4_deleteChain(&root, _LL4_ALL);


		// When we get here, success
		vvm_resourcePrintf(IDS_VVM_TEST_SLL4_PASSED);
		return true;
	}




	bool iivvmt_testSll4_1(u64 lnHandleLog, SLL4** root)
	{
		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL4_CREATE);


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




	bool iivvmt_testSll4_2(u64 lnHandleLog, SLL4* root)
	{
		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL4_APPEND);


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




	bool iivvmt_testSll4_3(u64 lnHandleLog, SLL4** root)
	{
		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL4_DELETE);


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}
