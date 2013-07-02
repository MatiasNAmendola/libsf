//////////
//
// /libsf/vvm/localization/vvmenu/vvmenu.cpp
//
//////
// Version 0.50
// Copyright (c) 2012 by Rick C. Hodgin
//////
// Last update:
//     October 05, 2012
//////
// Change log:
//     October 05, 2012 - Initial creation
//     October 05, 2012 - PBL v1.0 license included directly in source files.
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
// English Resource DLL.  See resources.
//////
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include "resource.h"




//////////
// At some future point, there may be exported items.
// For now, this dll merely holds language-specific resources.
//////
	BOOL APIENTRY DllMain(	HMODULE	hModule,
							DWORD	ul_reason_for_call,
							LPVOID	lpReserved	)
	{
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
			case DLL_THREAD_ATTACH:
			case DLL_THREAD_DETACH:
			case DLL_PROCESS_DETACH:
				break;
		}
		return TRUE;
	}
