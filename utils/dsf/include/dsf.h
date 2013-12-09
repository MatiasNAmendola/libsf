**********
*
* /libsf/vvm/utils/dsf/include/dsf.h
*
*****
* Version 0.60
* Copyright (c) 2013 by Rick C. Hodgin
*****
* Last update:
*     Dec.09.2013
*****
* Change log:
*     Dec.09.2013	- Initial creation
*****
*
* This include file is used by the DSF project, and includes windows message
* values above WM_USER for custom message handling between DSF.DLL and this app.
*
*****
*
* This software is released as Liberty Software under a Repeat License, as governed
* by the Public Benefit License v1.0 or later (PBL).
*
* You are free to use, copy, modify and share this software.  However, it can only
* be released under the PBL version indicated, and every project must include a copy
* of the pbl.txt document for its version as is at http:*www.libsf.org/licenses/.
*
* For additional information about this project, or to view the license, see:
*
*     http:*www.libsf.org/
*     http:*www.libsf.org/licenses/
*     http:*www.visual-freepro.org
*     http:*www.visual-freepro.org/blog/
*     http:*www.visual-freepro.org/forum/
*     http:*www.visual-freepro.org/wiki/
*     http:*www.visual-freepro.org/wiki/index.php/PBL
*     http:*www.visual-freepro.org/wiki/index.php/Repeat_License
*
* Thank you.  And may The Lord bless you richly as you lift up your life, your
* talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
*
*****




**********
* Note:  The following messages must match the values used in the DSF.DLL
* Note:  See dsf.h in the DSF.DLL project/solution.
*****
	#define WM_USER						0x400
	#define WM_REDRAW_WINDOW 			(WM_USER + 1)
