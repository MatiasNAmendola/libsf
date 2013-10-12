//////////
//
// /libsf/vvm/vvm/vvm_tests.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     February 16, 2013
//////
// Change log:
//     February 16, 2013 - Initial creation
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
// Top level for running test cases against the current system.
// Attempts to load each plugin in turn, vvmt_core.dll first, then all other DLLs.
//
//////
	void ivvm_runTestPlugins(void)
	{
		u64 lnHandle;


		//////////
		// Prepare the test results file
		//////
			lnHandle = oss_sharedAsciiOpenFile((s8*)cgcVvmTestLogFile, true, false, true, true, false, true, false, false);
			if (!lnHandle)
			{
				// The log file is an essential, integral component of testing.  We cannot leave it out.
				oss_messageBox(NULL, "Unable to open log file for test results. Terminating.", "Test Failure", false, false, false, false, true);
				return;
			}

		//////////
		// Run the tests, core first, then all other tests
		//////
			// vvmt_core.dll -- the core test must be run first and must pass, or the other tests cannot run
			if (ivvm_loadTestsByName(lnHandle, _csu8p(cgcVvmTestsDirectory)/*.\tests\*/, _csu8p(cgcVvmTestCoreDll)/*vvmt_core.dll*/, _csu8p_NULL()))
			{
				// *.dll -- all other tests, but don't run vvmt_core.dll again
				ivvm_loadTestsByName(lnHandle, _csu8p(cgcVvmTestsDirectory)/*.\tests\*/, _csu8p(cgcVvmTestFilePattern)/**.dll*/, _csu8p(cgcVvmTestCoreDll)/*exclude this test*/);
			}
	}




//////////
//
// 
//
//////
	bool ivvm_loadTestsByName(u64 lnHandleLog, csu8p tcDirectory, csu8p tcFilePattern, csu8p tcExclusionList)
	{
		u64			lnHandleFind;
		u32			lnExclusionListLength;
		bool		llMore, llCumulativeResult;
		SFindFile	lff;


		//////////
		// Initialize
		//////
			memset(&lff, 0, sizeof(lff));
			lnExclusionListLength	= (u32)oss_strlen(tcExclusionList);
			llCumulativeResult		= true;


		//////////
		// Attempt to load the pattern
		//////
			lnHandleFind = oss_fileFindFirst(tcDirectory, tcFilePattern, &lff);
			if (lnHandleFind != -1)
			{
				llMore = true;
				while (llMore)
				{
					// Make sure it's not a file to exclude
					if (!oss_isNeedleInHaystack(tcExclusionList, lnExclusionListLength, lff.file.data, (u32)lff.file.length, false, NULL))
					{
						//////////
						// Run this test
						//////
							llCumulativeResult = (llCumulativeResult & iivvm_runVvmTest(lnHandleLog, &lff));
					}

					// Get the next file
					llMore = oss_fileFindNext(lnHandleFind, &lff);
				}
				// When we get here, we're done.

				// Close the handle
				oss_fileFindClose(lnHandleFind);

				// Release any allocated memory blocks
				oss_datumDelete(&lff.file);
				oss_datumDelete(&lff.file2);
			}


		//////////
		// Indicate the overall success
		//////
			return(llCumulativeResult);
	}




//////////
//
// Called to see if this specific DLL is a VVM test DLL, and if so, then run it.
// 
// Requires these functions exist:
//
//		vvmt_firstCallback
//		vvmt_bootstrapInitialization
//		vvmt_initialization
//		vvmt_getVersion				// Not directly used, however, this function must be present
//		vvmt_executeTests
//
//////
	bool iivvm_runVvmTest(u64 lnHandleLog, SFindFile* tff)
	{
		u64		lnFirstCallback, lnBootstrapInitialization, lnInitialization, lnGetVersion, lnExecuteTests, lnDebuggerInterface;
		bool	llResult;
		HMODULE	lnHmod;
		s8		filename[_MAX_PATH];


		// Make sure our environment is sane
		llResult = false;
		if (tff)
		{
			// Set our constant initializations
			lnDebuggerInterface = (u64)&vvm_debuggerInterfaceCallback;


			// Get a local copy of our file into a null-terminated buffer
			memset(&filename, 0, sizeof(filename));
			memcpy(&filename, tff->file.data._u8, (u32)tff->file.length);

			// Attempt to open the DLL
			lnHmod = LoadLibraryA(filename);
			if (lnHmod)
			{
				//////////
				// Try to locate the functions
				//////
					lnFirstCallback				= (u64)GetProcAddress(lnHmod, (cs8*)cgcVvmTestDll_firstCallback);
					lnBootstrapInitialization	= (u64)GetProcAddress(lnHmod, (cs8*)cgcVvmTestDll_bootstrapInitialization);
					lnInitialization			= (u64)GetProcAddress(lnHmod, (cs8*)cgcVvmTestDll_initialization);
					lnGetVersion				= (u64)GetProcAddress(lnHmod, (cs8*)cgcVvmTestDll_getVersion);
					lnExecuteTests				= (u64)GetProcAddress(lnHmod, (cs8*)cgcVvmTestDll_executeTests);


				//////////
				// Did we load them all?
				//////
					if (lnFirstCallback != 0 && lnBootstrapInitialization != 0 && lnInitialization != 0 && lnGetVersion != 0 && lnExecuteTests != 0)
					{
						//////////
						// We found our test
						//////
							gsVvmTest.DllInstance = (u64)lnHmod;


						//////////
						// Store the interfaces
						//////
							gsVvmTest._firstCallback			= lnFirstCallback;
							gsVvmTest._bootstrapInitialization	= lnBootstrapInitialization;
							gsVvmTest._initialization			= lnInitialization;
							gsVvmTest._getVersion				= lnGetVersion;
							gsVvmTest._executeTests				= lnExecuteTests;


						//////////
						// Initialize
						//////
							gsVvmTest.firstCallback				(lnDebuggerInterface);
							gsVvmTest.bootstrapInitialization	(lnDebuggerInterface);
							gsVvmTest.initialization			(lnDebuggerInterface);


						//////////
						// Run the tests
						//////
							llResult = gsVvmTest.executeTests(lnHandleLog);
							// All done!
					}

				// When we get here, this test is completed
				FreeLibrary(lnHmod);
			}
		}
		// When we get here, indicate our status
		return(llResult);
	}
