//////////
//
// /libsf/vvm/vvm/vvm_res.cpp
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
//     Oct.05.2012 - PBL v1.0 license included directly in source files.
//     Oct.05.2012 - Initial creation
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
// Attempt to load vvmext.dll and access all required functions
//
//////
	bool ivvm_loadVvmResourceDll()
	{
		s8 buffer[MAX_PATH];


		// Try to load the dll
		if (gsVvm.gcVvmResourceLang)
		{
			sprintf_s(buffer, sizeof(buffer), "vvm%s.dll\000", gsVvm.gcVvmResourceLang);
			gsVvm.ghVvmResourceDll = LoadLibraryA(buffer);
		}
		if (!gsVvm.gcVvmResourceLang || !gsVvm.ghVvmResourceDll)
		{
			// There was an error loading the indicated resource dll
			// Fallback to English
			gsVvm.ghVvmResourceDll = LoadLibraryA(cgcVvmEngDll);
			if (!gsVvm.ghVvmResourceDll)
				return(false);		// If we get here, then it's bad, bad, bad news, mister!
		}
		// We're good
		return(true);
	}
