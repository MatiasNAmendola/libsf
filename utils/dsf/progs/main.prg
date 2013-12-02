**********
*
* /libsf/vvm/utils/dsf/progs/main.prg
*
*****
* Version 0.60
* Copyright (c) 2013 by Rick C. Hodgin
*****
* Last update:
*     Nov.26.2013
*****
* Change log:
*     Nov.26.2013	- Initial creation
*****
*
* Top-level program for the DSF (Dynamic Scalable Font) application.  It was created to
* allow a simple GUI for creating new fonts in the DSF format.  Each DSF is an XML file
* with the standard 256-character ASCII set, along with definable characters beyond that.
* DSF files also have colors and layers with a Z-order.  They are not true 3D fonts in
* that there is no way to connect layers to other layers.  A future D3F format will be
* created to allow for true 3D fonts.
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
LPARAMETERS tcOption1, tcOption2, tcOption3

SET STATUS OFF
SET BELL OFF
SET DOHISTORY OFF
SET TALK OFF
SET ENGINEBEHAVIOR 70
SET STATUS BAR ON
SET SAFETY OFF


**********
* Set the app paths
*****
	SET PROCEDURE	TO dsf_dll.prg			ADDITIVE
	SET PROCEDURE	TO main.prg				ADDITIVE
	SET CLASSLIB	TO helper.vcx			ADDITIVE


**********
* Load global variables
*****
	PUBLIC gcStartupDirectory
	gcStartupDirectory = FULLPATH(CURDIR())


**********
* Declare the extension DLLs
*****
	DO declare_dsf_dll					&& dsf.dll


**********
* Display the main launcher screen.  If they passed a font filename
* to begin editing, it will bring up the edit screen.
*****
	* Display the splash screen
	DO FORM frmMain WITH tcOption1, tcOption2, tcOption3


**********
* Wait until we're done
*****
	READ EVENTS


**********
* Upon termination, restore things
*****
	_vfp.Visible = .t.
	SET TALK ON
