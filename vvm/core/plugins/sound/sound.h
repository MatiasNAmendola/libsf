//////////
//
// /libsf/vvm/core/plugins/sound/sound.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     Jun.01.2013
//////
// Change log:
//     Jun.01.2013 - Initial creation
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
// Tone
//////
	struct _isSoundTone
	{
		u32				nMilliseconds;									// How many milliseconds to generate?
		u32				nSamplesToGenerate;								// Based on milliseconds, how many samples to generate?
		u32				nSamplesGenerated;								// How many samples have been generated thus far?

		// Tone 1
		f32				fAccumulator1;									// Accumulated value for sine wave tones
		f32				fHertz1;										// Frequency

		// Tone 2
		f32				fAccumulator2;									// Accumulated value for sine wave tones
		f32				fHertz2;										// Frequency

		// Tone 3
		f32				fAccumulator3;									// Accumulated value for sine wave tones
		f32				fHertz3;										// Frequency

		// Tone 4
		f32				fAccumulator4;									// Accumulated value for sine wave tones
		f32				fHertz4;										// Frequency
	};




//////////
// Stream
//////
	struct _isSoundStream
	{
		_isSSoundPluginCallback filler;									// Callback to fill our stream data
	};




//////////
// Sound
//////
	struct _isSSound
	{
		SLL				ll;												// 2-way link list
		
		// Flags
		bool			isPlaying;										// Is the stream playing?
		bool			inDeleteQueue;									// Should this item be deleted when next it stops playing?

		// Stream buffer and channel volume
		// Each sound channel populates its own samples, and then these are mixed together
		f32*			samples;										// Each sample is 0.0 to 1.0 based on its value
		f32				volume;											// How loud should this channel be (0.0f - 1.0f)

		// Shared structure based on whatever identity it has
		bool			isStream;										// Is this a sound stream? no=tone
		union {
			_isSoundStream	stream;										// Sound streams are callbacks to request sound data
			_isSoundTone	tone;										// Sound tones are combined tones computed upon demand
		};
	};
