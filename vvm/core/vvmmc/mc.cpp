//////////
//
// /libsf/vvm/mc/mc.cpp
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
//     Nov.12.2012 - Initial creation
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



#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include "stdlib.h"
#include "stdio.h"
#include "windows.h"
#include "stdio.h"
#include "\libsf\vvm\core\common\common.h"
#include "\libsf\vvm\core\common\vvm_key_const.h"
#include "\libsf\vvm\core\vvmoss\oss_class.h"
#include "\libsf\vvm\core\vvm\vvm_structs.h"
#include "\libsf\vvm\core\vvmoss\oss_structs.h"
#include "mc_const.h"
#include "mc_structs.h"
#include "mc_istructs.h"
#include "mc_defs.h"
#include "mc_glob.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_oss.h"
#include "\libsf\vvm\core\localization\vvmmcenu\resource.h"




//////////
//
// Main entry point for the VVM's Operating System Specific code
//
//////
	BOOL APIENTRY DllMainW(	HMODULE	hModule,
							DWORD	ul_reason_for_call,
							LPVOID	lpReserved )
	{
		ghInstance = hModule;
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
				break;
			case DLL_PROCESS_DETACH:
				break;
			case DLL_THREAD_ATTACH:
			case DLL_THREAD_DETACH:
				break;
		}
		return TRUE;
	}




	// This function is called ONLY from the VVM after loading this DLL.
	// If this DLL is loaded from another source (not the VVM), it is not
	// to call this function.  The VVM calls to give it the address to call
	// for debugger API requests, as well as those of the already loaded VVMOSS.
	u64 CALLTYPE mc_firstCallback(u64 tnCallbackAddress)
	{
		//////////
		// Load all VVM and VVMOSS functions
		//////
			iLoadVvmFunctionsFromVVM((void**)tnCallbackAddress);
			iLoadVvmOssFunctionsFromVVM((void**)tnCallbackAddress);


		//////////
		// Load the resource, which contains text and graphics
		//////
			iLoadResource(vvm_getLanguage(NULL));


		// Indicate success
		return(gVvmFunctionCount);
	}




//////////
//
// Called to handle any bootstrap initialization, things where only primitive services of the
// VVM and VVMOSS are available, and not completely at that.
//
//////
	void CALLTYPE mc_bootstrapInitialization(u64 tnDebuggerInterfaceAddress)
	{
_asm int 3;
		// Store the address of the VVM interface for function address requests
		_vvm_debuggerInterface = tnDebuggerInterfaceAddress;

		// Nothing else is currently defined for bootstrap initialization
	}





//////////
//
// Called to handle any initialization after the system has been through bootstrapping, and
// all initial conditions are met, able to service requests.
//
//////
	void CALLTYPE mc_initialization(u64 tnDebuggerInterfaceAddress)
	{
		// Nothing is currently defined for initialization
	}




//////////
//
// Called to indicate the VVMMC.DLL version
//
//////
	const s8* CALLTYPE mc_getVersion(void)
	{
		return(cgcVvmmcVersion);
	}




//////////
//
// Called to ask the VVMMC to load VvmOss functions, now that they're available by the
// original caller's use/activity.
//
//////
	bool CALLTYPE mc_loadVvmmOssFunctions(void)
	{
		return(iLoadOssFunctionsFromDll());
	}




//////////
//
// Called to load the vvmmc resource file for the indicated language.
// This function is called from non-VVM users of this DLL.
//
//////
	bool CALLTYPE mc_loadResourceLanguage(s8* tcResourceLanguage, u64* tnDllHandle)
	{
		bool llResult;


		// Try to load our localization resource
		llResult = iLoadResource(tcResourceLanguage);

		// Store the resource DLL handle
		if (llResult && tnDllHandle)
			*tnDllHandle = (u64)ghResourceDll;

		// Indicate success or failure
		return(llResult);
	}




//////////
//
// Loads the indicated resource string from the localization file
//
//////
	s8* CALLTYPE mc_loadResourceAsciiText(u32 tnResourceNumber)
	{
		u32					lnLength;
		SVvmmcResourceText*	lr;
		s8					buffer[1024];
		SStartEndCallback	cb;


		// Try to find the resource we've already loaded
		cb._func	= (u64)&iimc_loadResourceAsciiTextCallback;
		cb.extra	= tnResourceNumber;
		lr = (SVvmmcResourceText*)vvm_SEChain_searchByCallback(&gseRootResourceTexts, &cb);
		if (lr)
			return(lr->text);		// It's already been loaded

		// Try to locate it
		if (!LoadStringA(ghResourceDll, tnResourceNumber, buffer, sizeof(buffer)))
			return((s8*)cgcUnableToLocateResource);		// Use the default failure string

		// Allocate the new item
		lr = (SVvmmcResourceText*)vvm_SEChain_append(&gseRootResourceTexts, vvm_getNextUniqueId(), vvm_getNextUniqueId(), sizeof(SVvmmcResourceText), _COMMON_START_END_BLOCK_SIZE, NULL);
		if (lr)
		{
			// Store the resource information
			lr->resourceNumber	= tnResourceNumber;

			// Duplicate the loaded string
			lnLength			= strlen(buffer) + 1;
			lr->text			= (s8*)oss_alloc(lnLength, true);
			if (lr->text)		memcpy(lr->text, buffer, lnLength - 1);

			// All done
			return(lr->text);
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Verify the specified variable name is in the proper form.
//
// Rules:
//		(1)	Cannot begin with a number
//		(2) Contains only alphanumeric or underscores
//
// Returns:
//		true	- valid form
//		false	- invalid form
//
//////
	bool CALLTYPE mc_verifyVariableAsciiName(SOssComp* compName, u64* tnCompOffsetOfError)
	{
		s64			lnI;
		u8			ch;
		SOssLine*	line;
		s8*			lcName;


		// Initially indicate a failure at the get-go
		if (tnCompOffsetOfError)
			*tnCompOffsetOfError = -1;

		// Make sure the environment is sane
		if (compName && compName->line && compName->line->base)
		{
			// Grab a pointer to the start of this control
			line = compName->line;
			lcName = line->base + line->start + line->whitespace + compName->start;
			if (lcName[0] == '_' || (lcName[0] >= 'a' && lcName[0] <= 'z') || (lcName[0] >= 'A' && lcName[0] <= 'Z'))
			{
				// First character is a letter or underscore
				// Make sure every character is alphanumeric or underscore
				for (lnI = 0; lnI < compName->length; lnI++)
				{
					// Grab the character
					ch = lcName[lnI];

					// Verify this character
					if (!	((ch >= 'a' && ch <= 'z') ||
							 (ch >= 'A' && ch <= 'Z') ||
							 (ch >= '0' && ch <= '9') ||
								ch == '_'))
					{
						// Failure at this point
						if (tnCompOffsetOfError)
							*tnCompOffsetOfError = lnI;
						return(false);
					}
				}
				// If we get here, we're good
				return(true);
			}
		}
		// If we get here, failure in parameters
		return(false);
	}




//////////
//
// Verify the filename specified to start at (compFilename->line->base + compFilename->line->start +
// compFilename->line->whitespace + compFilename->start) is valid, meaning if it starts with a
// quote it ends with an identical quote, and if it does not start with a quote, then it has no
// spaces in it.
//
// Returns:
//		false		- tnCompOffsetOfError indicates the error
//		true		- tnCompOffsetOfError indicates the length of the pathname specified (which could be across many components)
//
//////
	bool CALLTYPE mc_verifyAsciiFilename(SOssComp* compFilename, u64* tnCompOffsetOfError)
	{
		u64		lnI, lnLength;
		s8*		lcFilename;


		// Make sure the environment is sane
		if (compFilename)
		{
			// Grab the start
			lcFilename = (compFilename->line->base + compFilename->line->start + compFilename->line->whitespace) + compFilename->start;

			// Determine if it's a quoted filename, or not
			if (compFilename->iCode == _MC_ICODE_SINGLE_QUOTED_TEXT || compFilename->iCode == _MC_ICODE_DOUBLE_QUOTED_TEXT)
			{
				// Quoted text, so we reduce the name by one on each side, resulting in a length of 2 less than its current length
				++lcFilename;		// Move past the leading quote
				lnLength = compFilename->length - 2;

			} else {
				// It's something else, it will end at the end of line, or at the first whitespace
				for (	lnLength = 0, lnI = compFilename->start; 
						lnI < compFilename->line->length;
						lnLength++, lnI++)
				{
					if (lcFilename[lnLength] == 32)
						break;		// We found a space
				}
				// When we get here, we've gone to the end of the line, or until we found a space
			}

			// At this point we have the start and the length
			// Valid characters are determined by calls to oss_validateFilenameCharacter()
			if (tnCompOffsetOfError)
				*tnCompOffsetOfError = lnLength;		// Store the length of the filename if it winds up being valid (if oss_validateFilenameCharacters() returns true)

			// Ask the OSS to determine if this is a valid filename or not for this operation system
			return(oss_validateFilenameCharacter(lcFilename, lnLength, tnCompOffsetOfError));
		}
		// If we get here, failure in parameters
		return(false);
	}




	void CALLTYPE mc_enableBreakpoints(void)
	{
	}

	void CALLTYPE mc_disableBreakpoints(void)
	{
	}


#include "mc_asm.cpp"
#include "mc_disasm.cpp"
#include "mc_save.cpp"
#include "mc_sup.cpp"
