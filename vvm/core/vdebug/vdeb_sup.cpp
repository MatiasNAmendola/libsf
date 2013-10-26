//////////
//
// /libsf/VDebug/VDebug/vdeb_support.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     September 28, 2012 - Initial creation
//     September 29, 2012 - PBL v1.0 license included directly in source files.
//     November 07, 2012 - 0.60 development begins
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
// Template keyboard processor
//
//////
	void CALLTYPE iVDebLauncherCallbackKeyDown(u64 tnUniqueId, SOssWindow* tisw, u32 tnKey, u32 tnKeyFlags, u8 tcAscii, u16 tcUnicode)
	{
		switch (tnKey)
		{
			case VVM_F1:
				break;

			case VVM_F2:
				break;

			case VVM_F3:
				break;

			case VVM_F4:
				break;

			case VVM_F5:
				break;

			case VVM_F6:
				break;

			case VVM_F7:
				break;

			case VVM_F8:
				break;

			case VVM_F9:
				break;

			case VVM_F10:
				break;

			case VVM_F11:
				break;

			case VVM_F12:
				break;

			default:
				// Unknown key
				return;
		}
	}
