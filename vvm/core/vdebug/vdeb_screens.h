//////////
//
// /libsf/vvm/core/vdebug/vdebug/vdeb_screens.h
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
//     Nov.07.2012 - 0.60 development begins
//     Oct.21.2012 - PBL v1.0 license included directly in source files.
//     Oct.21.2012 - Initial creation
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
// VDeb supports the following screens:
//		Locals.1, Locals.2, Locals.3
//		Regs.1, Int.1, Float.1
//		CFSCA.3
//		Ready.3
//		Memory.1, Memory.2, Memory.3
//		Watch.3
//		Autos.3
//		Stack.1
//		Hover.2
//		Timer.2
//		Programs.2
//		Threads.2
//////
	SLocal1		gsLoc1;
	SLocal2		gsLoc2;
	SLocal3		gsLoc3;
	SRegs1		gsRegs1;
	SInt1		gsInt1;
	SFloat1		gsFloat1;
	SCFSCA1		gsCFSCA1;
	SReady3		gsReady3;
	SMemory1	gsMemory1;
	SMemory2	gsMemory2;
	SMemory3	gsMemory3;
	SWatch3		gsWatch3;
	SAutos3		gsAutos3;
	SStack1		gsStack1;
	SHover2		gsHover2;
	STimer2		gsTimer2;
	SPrograms2	gsPrograms2;
	SThreads2	gsThreads2;

	SBxml*		gsBxmlScreens;
