//////////
//
// /libsf/vvm/vvmoss/vo_plugins.cpp
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
//     May.31.2013 - Initial creation
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
// Called to search the relative plugins\ directory and load any plugins that
// are found matching the plugins known to the vvmoss.
//
//////
/////////
//
// The VVMOSS contains placeholder functions (in vo_plugins.cpp) which do nothing if the
// plugin wasn't loaded, but are used to allow any existing application to call those
// functions so their code does not need changed.
//
//////
	void ioss_loadPlugins(void)
	{
		u64			lnHandle;
		bool		llMore;
		SFindFile	lff;


		//////////
		// Initialize
		//////
			memset(&lff, 0, sizeof(lff));
			vvm_datumSet(&lff.pathnameOfSearch, (u8*)".\\plugins\\",	-1, false);
			vvm_datumSet(&lff.filenameSearched, (u8*)"*.dll",			-1, false);


		//////////
		// Get the filenames
		//////
			lnHandle = oss_fileFindFirst(&lff);
			if (lnHandle != -1)
			{
				llMore = true;
				while (llMore)
				{
					do {

						//////////
						// Sound plugins
						//////
							// Do we still need to load the sound plugin?
							if (!gsSoundPlugin.DllInstance)
								if (ioss_loadPlugin_sound(&lff))
									break;
	

						//////////
						// Function plugins
						//////
							// See if there are any function plugins that need loaded
							if (ioss_loadPlugin_function(&lff))
								break;


//////////
//
// TODO: Other plugins will be tested for here
//
//////
							break;
					} while (1);

					// Get the next file
					llMore = oss_fileFindNext(lnHandle, &lff);
				}
				// When we get here, we're done.

				// Close the handle
				oss_fileFindClose(lnHandle, &lff);
			}
	}




//////////
//
// Called to load the sound plugin if possible.
// Note:  Sound plugins are singletons.
//        Only the first sound plugin found is loaded, and any further sound plugins are ignored.
//
//////
	bool ioss_loadPlugin_sound(SFindFile* tff)
	{
		u64		lnInitialize, lnCreateTone, lnCreateStream, lnSetVolume, lnPlayStart, lnPlayCancel, lnDelete;
		HMODULE	lnHmod;
		s8		filename[_MAX_PATH];


		// Make sure our environment is sane
		if (tff)
		{
			// Initialize our filename
			memset(&filename, 0, sizeof(filename));
			memcpy(&filename, tff->file.data._s8, (u32)tff->file.length);

			// Attempt to open the DLL
			lnHmod = LoadLibraryA(filename);
			if (lnHmod)
			{
				// Try to locate the functions
				lnInitialize	= (u64)GetProcAddress(lnHmod, cgcOssSoundInitialize);
				lnCreateTone	= (u64)GetProcAddress(lnHmod, cgcOssSoundCreateTone);
				lnCreateStream	= (u64)GetProcAddress(lnHmod, cgcOssSoundCreateStream);
				lnSetVolume		= (u64)GetProcAddress(lnHmod, cgcOssSoundSetVolume);
				lnPlayStart		= (u64)GetProcAddress(lnHmod, cgcOssSoundPlayStart);
				lnPlayCancel	= (u64)GetProcAddress(lnHmod, cgcOssSoundPlayCancel);
				lnDelete		= (u64)GetProcAddress(lnHmod, cgcOssSoundDelete);

				// Did we get them all?
				if (lnInitialize != 0 && lnCreateTone != 0 && lnCreateStream != 0 && lnSetVolume != 0 && lnPlayStart != 0 && lnPlayCancel != 0 && lnDelete != 0)
				{
					// We found our plugin
					gsSoundPlugin.DllInstance				= (u64)lnHmod;

					// Store the interfaces
					gsSoundPlugin._sound_initialize			= lnInitialize;
					gsSoundPlugin._sound_createTone			= lnCreateTone;
					gsSoundPlugin._sound_createStream		= lnCreateStream;
					gsSoundPlugin._sound_setVolume			= lnSetVolume;
					gsSoundPlugin._sound_playCancel			= lnPlayCancel;
					gsSoundPlugin._sound_playStart			= lnPlayStart;
					gsSoundPlugin._sound_deleteHandle		= lnDelete;

					// Ask it to initialize itself
					oss_soundInitialize();

					// All done!
					return true;
				}
				// If we get her, not found
				FreeLibrary(lnHmod);
			}
		}
		// If we get here, failure
		return false;
	}




//////////
//
// Called to load the function plugin if possible
// Note:  Multiple function plugins can be added.
//        Each one will be called where it sets itself up and self-registers its published abilities.
//
//////
	bool ioss_loadPlugin_function(SFindFile* tff)
	{
		u64						lnRequestor;
		HMODULE					lnHmod;
		_isSInterfacePlugin*	plugin;
		s8						filename[_MAX_PATH];


		// Make sure our environment is sane
		if (tff)
		{
			// Initialize our filename
			memset(&filename, 0, sizeof(filename));
			memcpy(&filename, tff->file.data._s8, (u32)tff->file.length);

			// Attempt to open the DLL
			lnHmod = LoadLibraryA(filename);
			if (lnHmod)
			{
				// Try to locate the functions
				lnRequestor = (u64)GetProcAddress(lnHmod, cgcOssPluginRequestor);

				// Did we get it?
				if (lnRequestor != 0)
				{
					// We found our plugin
					plugin = ioss_plugin_register((u64)lnHmod);
					if (plugin)
					{
						// Store the interfaces
						plugin->_requestor = lnRequestor;

						// Ask this plugin to expost its abilities to the VVMOSS
						plugin->requestor(plugin->DllInstance);

						// All done!
						return true;
					}
				}
				// If we get her, not found
				FreeLibrary(lnHmod);
			}
		}
		// If we get here, failure
		return false;
	}




//////////
//
// Plays a tone for the indicated duration.
// Returns a handle to the sound play.
//
//////
	void CALLTYPE oss_soundInitialize(void)
	{
		if (gsSoundPlugin.DllInstance && gsSoundPlugin._sound_initialize)
		{
			// Call the plugin to handle the load
			gsSoundPlugin.sound_initialize();
		}
	}




//////////
//
// Plays a tone for the indicated duration.
// Returns a handle to the sound play.
//
//////
	u64 CALLTYPE oss_soundCreateTone(f32 tfHertz1, f32 tfHertz2, f32 tfHertz3, f32 tfHertz4, u32 tnDurationMilliseconds)
	{
		if (gsSoundPlugin.DllInstance && gsSoundPlugin._sound_createTone)
		{
			// Call the plugin to handle the load
			return(gsSoundPlugin.sound_createTone(tfHertz1, tfHertz2, tfHertz3, tfHertz4, tnDurationMilliseconds));
		}
		// If we get here, sound is not loaded
		return(-1);
	}




//////////
//
// Plays a stream as long as data is fed to it.
// Returns a handle to the sound play.
//
//////
	u64 CALLTYPE oss_soundCreateStream(u32 tnSamplesPerSecond, u64 tnSoundFillerCallbackFunction)
	{
		if (gsSoundPlugin.DllInstance && gsSoundPlugin._sound_createStream)
		{
			// Call the plugin to handle the load
			return(gsSoundPlugin.sound_createStream(tnSamplesPerSecond, tnSoundFillerCallbackFunction));
		}
		// If we get here, sound is not loaded
		return(-1);
	}




//////////
//
// Sets the volume of a given sound
//
//////
	u64 CALLTYPE oss_soundSetVolume(u64 tnHandle, f32 tfVolume)
	{
		if (gsSoundPlugin.DllInstance && gsSoundPlugin._sound_setVolume)
		{
			// Call the plugin to handle the load
			return(gsSoundPlugin.sound_setVolume(tnHandle, tfVolume));
		}
		// If we get here, sound is not loaded
		return(-1);
	}




//////////
//
// Begins playing a tone or stream
//
//////
	u64 CALLTYPE oss_soundPlayStart(u64 tnHandle, f32 tfVolume)
	{
		if (gsSoundPlugin.DllInstance && gsSoundPlugin._sound_playStart)
		{
			// Call the plugin to handle the load
			return(gsSoundPlugin.sound_playStart(tnHandle, tfVolume));
		}
		// If we get here, sound is not loaded
		return(-1);
	}




//////////
//
// Cancels playing a tone or stream
//
//////
	u64 CALLTYPE oss_soundPlayCancel(u64 tnHandle)
	{
		if (gsSoundPlugin.DllInstance && gsSoundPlugin._sound_playCancel)
		{
			// Call the plugin to handle the load
			return(gsSoundPlugin.sound_playCancel(tnHandle));
		}
		// If we get here, sound is not loaded
		return(-1);
	}




//////////
//
// Deletes a previously created tone or stream
//
//////
	u64 CALLTYPE oss_soundDelete(u64 tnHandle)
	{
		if (gsSoundPlugin.DllInstance && gsSoundPlugin._sound_deleteHandle)
		{
			// Call the plugin to handle the load
			return(gsSoundPlugin.sound_deleteHandle(tnHandle));
		}
		// If we get here, sound is not loaded
		return(-1);
	}
