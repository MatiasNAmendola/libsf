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
		// Indicate which test
		vvm_resourcePrintf(IDS_VVM_TEST_SLL_TESTING);


		//////////
		// #01 - Create a three element linked list
		//////
			if (!iivvmt_testSll_1(lnHandleLog))
				return false;		// failure


		//////////
		// #02 - Append an item before and after the middle item, then before and after the beginning and ending items
		//////
			if (!iivvmt_testSll_2(lnHandleLog))
				return false;		// failure


		//////////
		// #03 - Delete first item, last item, middle item
		//////
			if (!iivvmt_testSll_3(lnHandleLog))
				return false;		// failure


		// When we get here, success
		vvm_resourcePrintf(IDS_VVM_TEST_SLL_PASSED);
		return true;
	}




	bool iivvmt_testSll_1(u64 lnHandleLog)
	{
		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL_CREATE);


		//////////
		// Create a single node
		//////



		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




	bool iivvmt_testSll_2(u64 lnHandleLog)
	{
		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL_APPEND);


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




	bool iivvmt_testSll_3(u64 lnHandleLog)
	{
		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL_DELETE);


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}
