//////////
//
// /libsf/vvm/core/vvmtests/vvmt_core/vvmt_sha1_test.cpp
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
// Top level for running test cases against the SHA-1 engine.
//
//////
	bool ivvmt_testSha1(u64 lnHandleLog)
	{
		// Indicate which test
		vvm_resourcePrintf(IDS_VVM_TEST_SHA1_TESTING);


		//////////
		//
		// #01 - FIPS PUB 180-1
		//
		//////
			if (!iivvmt_testSha1_1(lnHandleLog))
				return false;		// failure


		// When we get here, success
		vvm_resourcePrintf(IDS_VVM_TEST_SHA1_PASSED);
		return true;
	}




	bool iivvmt_testSha1_1(u64 lnHandleLog)
	{
		// Used for test #3
		u32		lnI;
		u8		context[96];


		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SHA1_FIPS_PUB_180_1);


		//////////
		// "abc"
		// A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
		//////
			vvm_resourcePrintf(IDS_VVM_1DOTDOTDOT);
			vvm_sha1ComputeSha1AsHex((s8*)cgc_Test_Sha1_1_1, sizeof(cgc_Test_Sha1_1_1) - 1, cgc_Test_Sha1_1_3, true);;
			if (vvm_memicmp(_csu8p(cgc_Test_Sha1_1_2), _csu8p(cgc_Test_Sha1_1_3), sizeof(cgc_Test_Sha1_1_2) - 1) != 0)
			{
failure:
				// Error
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);

				// Indicate we failed
				return false;
			}


		//////////
		// "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
		// 84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
		//////
			vvm_resourcePrintf(IDS_VVM_2DOTDOTDOT);
			vvm_sha1ComputeSha1AsHex((s8*)cgc_Test_Sha1_2_1, sizeof(cgc_Test_Sha1_2_1) - 1, cgc_Test_Sha1_2_3, true);;
			if (vvm_memicmp(_csu8p(cgc_Test_Sha1_2_2), _csu8p(cgc_Test_Sha1_2_3), sizeof(cgc_Test_Sha1_2_2) - 1) != 0)
				goto failure;		// Failure


		//////////
		// A million repetitions of "a"
		// 34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
		//////
			vvm_resourcePrintf(IDS_VVM_3DOTDOTDOT);

			// Initialize
			vvm_sha1ComputeSha1_Start(context);

			// Process one million lower-case "a" characters in succession, one at a time
			for (lnI = 0; lnI < 1000000; lnI++)
				vvm_sha1ComputeSha1_ProcessThisData(context, (s8*)cgc_Test_Sha1_3_1, sizeof(cgc_Test_Sha1_3_1) - 1);

			// Finalize and compute the value a hex
			vvm_sha1ComputeSha1_FinishAsHex(context, cgc_Test_Sha1_3_3, true, true);
			if (vvm_memicmp(_csu8p(cgc_Test_Sha1_3_2), _csu8p(cgc_Test_Sha1_3_3), sizeof(cgc_Test_Sha1_3_2) - 1) != 0)
				goto failure;		// Failure


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}
