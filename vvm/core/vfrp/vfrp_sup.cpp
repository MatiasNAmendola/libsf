//////////
//
// /libsf/vvm/core/vfrp/vfrp_sup.cpp
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//     Mar.08.2014
//////
// Change log:
//     Mar.08.2012 - Initial creation
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
// Called to load the VVM.DLL stuff, following the startup protocol.
//
//////
	bool ivfrp_loadAndInitializeVvm(void)
	{
		// Load the DLL
		if (!iLoadVvmFunctionsFromDll())
			return(false);

		// Let it initialize itself
		vvm_firstCallback(0);
		vvm_bootstrapInitialization();

		// We're good
		return(true);
	}




//////////
//
// Called to load the OSS.DLL stuff, following the startup protocol.
//
//////
	bool ivfrp_loadAndInitializeOss(void)
	{
		// Load the DLL
		if (!iLoadOssFunctionsFromDll())
			return(false);

		// Let it initialize itself
		oss_firstCallback(0);
		oss_bootstrapInitialization();

		// We're good
		return(true);
	}





//////////
//
// Called to load the MC.DLL stuff, following the startup protocol.
//
//////
	bool ivfrp_loadAndInitializeMc(void)
	{
		// Load the DLL
		if (!iLoadMcFunctionsFromDll())
			return(false);

		// Let it initialize itself
		mc_firstCallback(0);
		mc_bootstrapInitialization();

		// We're good
		return(true);
	}
