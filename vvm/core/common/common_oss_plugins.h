//////////
//
// /libsf/vvm/common/common_vvmoss_plugins.h
//
//////
// Version 0.60
// Copyright (c) 2013 by Rick C. Hodgin
//////
// Last update:
//	   May.07.2013
//////
// Change log:
//	   May.07.2013 - Initial creation
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
//	   http://www.libsf.org/
//	   http://www.libsf.org/licenses/
//	   http://www.visual-freepro.org
//	   http://www.visual-freepro.org/blog/
//	   http://www.visual-freepro.org/forum/
//	   http://www.visual-freepro.org/wiki/
//	   http://www.visual-freepro.org/wiki/index.php/PBL
//	   http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.	In Jesus' name I pray.  Amen.
//
//




//////////
// The following are function names referenced by plugins
//////
	// For sound plugins
	const s8		cgcOssSoundInitialize[]								= "oss_soundInitialize";
	const s8		cgcOssSoundCreateTone[]								= "oss_soundCreateTone";
	const s8		cgcOssSoundCreateStream[]							= "oss_soundCreateStream";
	const s8		cgcOssSoundSetVolume[]								= "oss_soundSetVolume";
	const s8		cgcOssSoundPlayStart[]								= "oss_soundPlayStart";
	const s8		cgcOssSoundPlayCancel[]								= "oss_soundPlayCancel";
	const s8		cgcOssSoundDelete[]									= "oss_soundDelete";

	// For function plugins (these are not called directly by the VVMOSS, but rather by currently active function as there can be several plugins which provide the same functionality, able to be context-switched by selecting one or the other at random)
	const s8		cgcOssPluginRequestor[]								= "vvmoss_plugin_requestor";
	const s8		cgcOssPluginInterface[]								= "vvmoss_plugin_interface";


//////////
// vo.cpp, sound.cpp
//////
#ifdef _NATIVE_CALLS
	//////////
	// For sound plugins
	//////
		void CALLTYPE			oss_soundInitialize							(u64 tnDebuggerInterfaceAddress);
		u64 CALLTYPE			oss_soundCreateTone							(f32 tnHertz1, f32 tnHertz2, f32 tnHertz3, f32 tnHertz4, u32 tnDurationMilliseconds);
		u64 CALLTYPE			oss_soundCreateStream						(u32 tnSamplesPerSecond, u64 tnSoundFillerCallbackFunction);
		u64 CALLTYPE			oss_soundSetVolume							(u64 tnHandle, f32 tfVolume);
		u64 CALLTYPE			oss_soundPlayStart							(u64 tnHandle, f32 tfVolume);
		u64 CALLTYPE			oss_soundPlayCancel							(u64 tnHandle);
		u64 CALLTYPE			oss_soundDelete								(u64 tnHandle);

	//////////
	// For oss_soundCreateStream()'s callback to populate each stream.
	// Samples should be -1.0 to 1.0, and are auto-adjusted to the target.
	//////
		struct _isSSoundPluginCallback
		{
			union {
				u64		_callback;
				void	(CALLTYPE *callback)	(f32* sampleBuffer, u32 tnSamples, bool* tlContinueAfterThisSampleSet);
			};
		};

#else
	//////////
	// For sound plugins
	//////
		void (CALLTYPE			*oss_soundInitialize)						(u64 tnDebuggerInterfaceAddress);
		u64	(CALLTYPE			*oss_soundCreateTone)						(f32 tnHertz1, f32 tnHertz2, f32 tnHertz3, f32 tnHertz4, u32 tnDurationMilliseconds);
		u64	(CALLTYPE			*oss_soundCreateStream)						(u32 tnSamplesPerSecond, u64 tnSoundFillerCallbackFunction);
		u64 (CALLTYPE			*oss_soundSetVolume)						(u64 tnHandle, f32 tfVolume);
		u64	(CALLTYPE			*oss_soundPlayStart)						(u64 tnHandle, f32 tfVolume);
		u64	(CALLTYPE			*oss_soundPlayCancel)						(u64 tnHandle);
		u64	(CALLTYPE			*oss_soundDelete)							(u64 tnHandle);
#endif
