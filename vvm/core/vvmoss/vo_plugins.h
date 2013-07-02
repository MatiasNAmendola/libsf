//////////
//
// /libsf/vvm/vvmoss/vo_plugins.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     May.31.2013
//////
// Change log:
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
// Sound
//
//////
	//////////
	// Structures
	//////
		struct _isSSoundPlugin
		{
			u64 DllInstance;


			//////////
			// initialize
			//////
				union {
					u64		_sound_initialize;
					u64		(CALLTYPE *sound_initialize)			(void);
				};


			//////////
			// createTone
			//////
				union {
					u64		_sound_createTone;
					u64		(CALLTYPE *sound_createTone)			(f32 tfHertz1, f32 tfHertz2, f32 tfHertz3, f32 tfHertz4, u32 tnDurationMilliseconds);
				};


			//////////
			// createStream
			//////
				union {
					u64		_sound_createStream;
					u64		(CALLTYPE *sound_createStream)			(u32 tnSamplesPerSecond, u64 tnSoundFillerCallbackFunction);
				};


			//////////
			// setVolume
			//////
				union {
					u64		_sound_setVolume;
					u64		(CALLTYPE *sound_setVolume)				(u64 tnHandle, f32 tfVolume);
				};


			//////////
			// playStart
			//////
				union {
					u64		_sound_playStart;
					u64		(CALLTYPE *sound_playStart)				(u64 tnHandle, f32 tfVolume);
				};


			//////////
			// playCancel
			//////
				union {
					u64		_sound_playCancel;
					u64		(CALLTYPE *sound_playCancel)			(u64 tnHandle);
				};


			//////////
			// delete
			//////
				union {
					u64		_sound_deleteHandle;
					u64		(CALLBACK *sound_deleteHandle)			(u64 tnHandle);
				};
		};


	//////////
	// vo_plugins.cpp
	//////
		void					ioss_loadPlugins								(void);
		void					ioss_loadPlugin_sound							(SFindFile* tff);
