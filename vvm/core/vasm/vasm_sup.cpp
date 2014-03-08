




//////////
//
// Called to load the VVM.DLL stuff, following the startup protocol.
//
//////
	bool ivasm_loadAndInitializeVvm(void)
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
	bool ivasm_loadAndInitializeOss(void)
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
	bool ivasm_loadAndInitializeMc(void)
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
