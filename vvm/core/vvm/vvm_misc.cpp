//////////
//
// /libsf/vvm/vvm/vvm_vo.cpp
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
//     Nov.07.2012 - 0.60 development begins
//     Oct.03.2012 - PBL v1.0 license included directly in source files.
//     Oct.03.2012 - Initial creation
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
// Once the VVM is started, we need to engage the engine in the way it's designed to run.
//
//////
	bool ivvm_loadAndInitializeOss(void)
	{
		// Create our main message window
		if (!oss_createMessageWindow())
			return(false);

		// We're good
		return(true);
	}




//////////
//
// Called to load the OSS.DLL stuff, following the startup protocol.
//
//////
	bool ivvm_loadAndInitializeMc(void)
	{
		// Nothing is defined at the current time
		return(true);
	}




//////////
//
// Called at bootup to initialize internal data structures
//
//////
	void iivvm_bootupInitialization(void)
	{
		gsVvm.gnVvmReturnResult				= -1;							// Indicate an initial return of failure
		gsVvm.glVvmIsRunning				= true;							// The VVM will continue as long as it is set to continue ... oh yes indeed. :-)
		gsVvm.glVvmDebugBreaks				= false;						// A global debugging flag if INT3 should be signaled when certain debugging conditions occur
		gsVvm.ghVvmResourceDll				= NULL;							// Handle to the loaded resource dll instance
		gsVvm.gcVvmResourceLang				= (s8*)cgcEnu;					// By default, points to English, override using command line switch "-r:" (such as "-r:es" for "vvmes.dll", for example)
		memset(&gsVvmSysInfo, 0, sizeof(gsVvmSysInfo));						// Populated during ivvmtm_initialize(), holds system information

		// Command-line determined instance sizes for variable allocation
		// NOTE:  The allocation size here will need to be inspected when the VVM is running to determine a better default size
		gsVvm.gnGlobalAllocationBlockSize	= 256;							// The default size to increase the global variable allocation
		gsVvm.gnLocalAllocationBlockSize	= 128;							// The default size to increase the global variable allocation
		gsVvm.gnStackAllocationBlockSize	= 8192;							// Default to an 8K stack per thread
		gsVvm.gnSnippetAllocationBlockSize	= 256;							// The default size to increase the snippet level allocation


		// The root objects
		memset(&gsVvm.gseRootPrograms,		0, sizeof(gsVvm.gseRootPrograms));		// Master programs list
		memset(&gsVvm.gseRootThreadMizer,	0, sizeof(gsVvm.gseRootThreadMizer));	// Master thread mizer list
		memset(&gsVvm.gseRootResourceTexts,	0, sizeof(gsVvm.gseRootResourceTexts));	// Previously loaded / cached resource texts


		// Semaphores for synchronized access to master lists
		gsVvm.gsemProgramsAccess				= 0;					// Master program inventory


		// Set our initial BXML error condition to a no-error state
		iibxml_recordLastError(IDS_BXML_NO_ERROR, 0, NULL, NULL, NULL, 0);
	}




//////////
//
// Display a message box using the indicated resource texts
//
//////
	u64 ivvm_resourceMessageBox(int tnMessage, int tnCaption, bool tlYes, bool tlNo, bool tlOk, bool tlRetry, bool tlCancel)
	{
		u64		lnResult;
		w16		luMessage[2048];
		w16		luCaption[256];
		

		// Load the indicated strings
		if (!LoadStringW(gsVvm.ghVvmResourceDll, tnMessage, luMessage, sizeof(luMessage)))
		{
			wcscpy_s(luMessage, sizeof(luMessage), L"Unable to locate resource");
			ivvm_debugBreak();
		}
		if (!LoadStringW(gsVvm.ghVvmResourceDll, tnCaption, luCaption, sizeof(luCaption)))
		{
			wcscpy_s(luCaption, sizeof(luCaption), L"Unable to locate resource");
			ivvm_debugBreak();
		}

		// Display the message box
		lnResult = oss_messageBoxUnicode(NULL, luMessage, luCaption, tlYes, tlNo, tlOk, tlRetry, tlCancel);

		// Indicate their response
		return(lnResult);
	}

	u64 ivvm_resourceMessageBoxLocal(int tnMessage, int tnCaption, bool tlYes, bool tlRetry, bool tlCancel)
	{
		u32		lnButton;
		u64		lnResult;
		w16		luMessage[2048];
		w16		luCaption[256];


		// Load the indicated strings
		if (!LoadStringW(gsVvm.ghVvmResourceDll, tnMessage, luMessage, sizeof(luMessage)))
		{
			wcscpy_s(luMessage, sizeof(luMessage), L"Unable to locate resource");
			ivvm_debugBreak();
		}
		if (!LoadStringW(gsVvm.ghVvmResourceDll, tnCaption, luCaption, sizeof(luCaption)))
		{
			wcscpy_s(luCaption, sizeof(luCaption), L"Unable to locate resource");
			ivvm_debugBreak();
		}

		// Prepare the buttonage :-)
		if (tlYes)			lnButton = (tlCancel) ? MB_YESNOCANCEL : MB_YESNO;
		else if (tlRetry)	lnButton = MB_RETRYCANCEL;
		else				lnButton = MB_OK;

		// Display the message box
#ifdef VVM_WINDOWS
		lnResult = MessageBox(NULL, luMessage, luCaption, lnButton);
#else
	#pragma message("vvm_misc::ivvm_resourceMessageBoxLocal() does not contain a MessageBox() function for this OS.")
#endif

		// Indicate their response
		return(lnResult);
	}

	void ivvm_resourceGetString(int tnMessage, wchar_t** tuString)
	{
		w16 luMessage[4096];


		// Make sure we have a proper pointer
		if (tuString)
		{
			// Load the indicated strings
			memset(luMessage, 0, sizeof(luMessage));
			if (!LoadStringW(gsVvm.ghVvmResourceDll, tnMessage, luMessage, sizeof(luMessage)))
			{
				wcscpy_s(luMessage, sizeof(luMessage), L"Unable to locate resource");
				ivvm_debugBreak();
			}
			// Create a copy to be used
			*tuString = vvm_duplicateUnicodeString(luMessage);
		}
	}

	void ivvm_resourcePrintf(int tnMessage)
	{
		w16 luMessage[4096];


		// Load the indicated strings
		memset(luMessage, 0, sizeof(luMessage));
		if (!LoadStringW(gsVvm.ghVvmResourceDll, tnMessage, luMessage, sizeof(luMessage)))
		{
			wcscpy_s(luMessage, sizeof(luMessage), L"Unable to locate resource");
			ivvm_debugBreak();
		}
		wprintf(luMessage);
	}

	void ivvm_resourcePrintf1(int tnMessage, void* p1)
	{
		w16 luMessage[4096];


		// Load the indicated strings
		memset(luMessage, 0, sizeof(luMessage));
		if (!LoadStringW(gsVvm.ghVvmResourceDll, tnMessage, luMessage, sizeof(luMessage)))
		{
			wcscpy_s(luMessage, sizeof(luMessage), L"Unable to locate resource");
			ivvm_debugBreak();
		}
		wprintf(luMessage, p1);
	}

	int ivvm_unicodeMemicmp(w16* l, w16* r, u32 tnLength)
	{
		w16		ll, rl;		// Left- and right-lower
		u32		lnI;


		// For every character in the length, compare left to right
		for (lnI = 0; lnI < tnLength; lnI++)
		{
			ll = ivvm_lowerCaseW(l[lnI]);
			rl = ivvm_lowerCaseW(r[lnI]);
			if (ll != rl)
			{
				if (ll < rl)
					return -1;		// Left is less than right
				return 1;			// Left is greater than right
			}
		}
		// They're equal
		return 0;
	}

	w16 ivvm_lowerCaseW(w16 u)
	{
		s8 c;
		// TODO:  (unicode) foreign languages will need to have other tests here


		// See if it's a lower-case character in ASCII
		c = (s8)u;
		if (c >= 'A' && c <= 'Z')
			return((w16)(c + 0x20));		// It is, convert to lower-case

		// If we get here, we're good as we are
		return(u);
	}




//////////
//
// Skip forward until the next whitespace, and then replace it with a NULL terminator
//
//////
	int ivvm_scanStringAndNullTerminateAtNextWhitespaceW(w16* tuString)
	{
		int lnSkipped;


		// Skip past every character until we find a whitespace
		lnSkipped = 0;
		while (*tuString != (w16)32 && *tuString != (w16)9 && *tuString != (w16)0)
		{
			// Skip this character
			++lnSkipped;
			++tuString;
		}
		// NULL-terminate
		*tuString = (w16)0;
		return(lnSkipped);
	}




//////////
//
// Callback to search for matching resources to those already loaded
//
//////
	bool iivvm_loadResourceAsciiTextCallback(SStartEndCallback* cb)
	{
		SVvmResourceText*	lr;


		// Make sure the environment is sane
		if (cb && cb->ptr)
		{
			lr = (SVvmResourceText*)cb->ptr;
			if (lr->resourceNumber == cb->extra)
				return(true);		// It's a match
		}
		// Not a match
		return(false);
	}




//////////
//
// Debug breaks should be turned on
//
//////
	bool ivvm_debugBreaksOn(void)
	{
		bool llPrev;


		// Get the old value, set the new value
		llPrev					= gsVvm.glVvmDebugBreaks;
		gsVvm.glVvmDebugBreaks	= true;

		// Allows previous version to be later restored
		return(llPrev);
	}




//////////
//
// Debug breaks should not be on
//
//////
	bool ivvm_debugBreaksOff(void)
	{
		bool llPrev;


		// Get the old value, set the new value
		llPrev					= gsVvm.glVvmDebugBreaks;
		gsVvm.glVvmDebugBreaks	= false;

		// Allows previous versions to be later restored
		return(llPrev);
	}




//////////
//
// Break if debug breaks are on, if not, then continue unabated
//
//////
	void ivvm_debugBreak(void)
	{
		if (gsVvm.glVvmDebugBreaks)
			_asm int 3;
	}




//////////
//
// Sets the indicated test condition to be raised, and returns its previous value
//
//////
	bool ivvm_debugBreaksOn(bool* tlTest)
	{
		bool llPrev;


		llPrev	= *tlTest;
		*tlTest	= true;
		return(llPrev);
	}




//////////
//
// Sets the indicated test condition should NOT be raised, and returns its previous value
//
//////
	bool ivvm_debugBreaksOff(bool* tlTest)
	{
		bool llPrev;


		llPrev	= *tlTest;
		*tlTest	= false;
		return(llPrev);
	}




//////////
//
// Breaks based on the condition of the indicated test condition
//
//////
	void ivvm_debugBreak(bool* tlTest)
	{
		if (*tlTest)
			_asm int 3;
	}
