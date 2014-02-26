//////////
//
// /libsf/vvm/vvmoss/vo_plugins.h
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
// Forward declarations
//
//////
	//////////
	// vo_plugins.cpp
	//////
		void					ioss_loadPlugins								(u64 tnDebuggerInterfaceAddress);
		bool					ioss_loadPlugin_sound							(SFindFile* tff, u64 tnDebuggerInterfaceAddress);
		bool					ioss_loadPlugin_function						(SFindFile* tff, u64 tnDebuggerInterfaceAddress);




//////////
//
// Sound plugins
//
//////

	//////////
	// Structures
	//////
		// For sound plugins
		struct _isSSoundPlugin
		{
			u64			DllInstance;

			union {
				u64		_sound_initialize;
				u64		(CALLTYPE *sound_initialize)		(u64 tnDebuggerInterfaceAddress);
			};

			union {
				u64		_sound_createTone;
				u64		(CALLTYPE *sound_createTone)		(f32 tfHertz1, f32 tfHertz2, f32 tfHertz3, f32 tfHertz4, u32 tnDurationMilliseconds);
			};

			union {
				u64		_sound_createStream;
				u64		(CALLTYPE *sound_createStream)		(u32 tnSamplesPerSecond, u64 tnSoundFillerCallbackFunction);
			};

			union {
				u64		_sound_setVolume;
				u64		(CALLTYPE *sound_setVolume)			(u64 tnHandle, f32 tfVolume);
			};

			union {
				u64		_sound_playStart;
				u64		(CALLTYPE *sound_playStart)			(u64 tnHandle, f32 tfVolume);
			};

			union {
				u64		_sound_playCancel;
				u64		(CALLTYPE *sound_playCancel)		(u64 tnHandle);
			};

			union {
				u64		_sound_deleteHandle;
				u64		(CALLTYPE *sound_deleteHandle)		(u64 tnHandle);
			};
		};





//////////
//
// Function plugins
//
//////

	//////////
	// Structures
	//////
		// Each function plugin has a direct callback for every registered function
		struct _isSInterfaceFunction
		{
			bool		available;						// Has this function been specified by this plugin?
			f32			version;						// What is the version, as in "999.999" maximum (3.3).
			u32			build;							// Build number within a specified version
			SDatum		identifier;						// Visual name for display purposes

			// Callback for this function
			union {
				u64		_func;
				u64		(CALLTYPE *func)				(u64 tnSubfunction, u64 extra, u64 extra2);
			};
		};

		// Each function plugin has an entry
		struct _isSInterfacePlugin
		{
			u64			DllInstance;


			//////////
			// Primary interface callbacks
			//////
				union {
					u64		_requestor;
					u64		(CALLTYPE *requestor)				(u64 tnDebuggerInterfaceAddress, u64 tnInstanceId);
				};


			//////////
			// Each function that is exposed by this plugin is available here
			//////
				_isSInterfaceFunction		editor;			// See _VVMOSS_PLUGIN_EDITOR
		};
