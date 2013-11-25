//////////
//
// /libsf/vvm/core/vvmtests/vvmt_core/vvmt_core.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     Jun.20.2013
//////
// Change log:
//     Mar.02.2013	- Initial creation
//     Jun.20.2013	- Refactoring into a stand-alone DLL loaded at runtime only if -test is specified on the command line
//////
//
// VVM Primary Test application.
// Tests the SHA-1 and BXML functionality, upon which the remaining tests all depend upon.
//
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




#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <share.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <sys\locking.h>
#include <errno.h>
#include <windows.h>
#include <math.h>
#include "\libsf\vvm\core\common\common.h"
#include "\libsf\vvm\core\localization\vvmenu\resource.h"					// Resource constants
#include "vvmt_const.h"
#include "\libsf\vvm\core\vvm\vvm_structs.h"
#include "\libsf\vvm\core\vvmoss\vo_structs.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_vvmoss.h"
#include "vvmt_structs.h"
#include "vvmt_defs.h"
#include "vvmt_glob.h"
#include "\libsf\vvm\core\vvmoss\vo_class.h"
#include "\libsf\vvm\core\common\vvm_key_const.h"

// The following are include files of external (non-VVM) LibSF projects
#include "\libsf\utils\sha1\sha1.h"		// SHA-1 hashing algorithm

// Test source files
#include "vvmt_sha1_test.cpp"
#include "vvmt_bxml_test.cpp"
#include "vvmt_sll_test.cpp"
#include "vvmt_sll4_test.cpp"




//////////
//
// Main entry point for the VVM's Operating System Specific code
//
//////
	BOOL APIENTRY DllMain(	HMODULE	hModule,
							DWORD	ul_reason_for_call,
							LPVOID	lpReserved )
	{
		ghInstance = hModule;
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
			case DLL_PROCESS_DETACH:
			case DLL_THREAD_ATTACH:
			case DLL_THREAD_DETACH:
				break;
		}
		return TRUE;
	}




//////////
//
// This function is called ONLY from the VVM after loading this DLL.
// If this DLL is loaded from another source (not the VVM), it is not
// to call this function.  The VVM calls to give it the address to call
// for debugger API requests, as well as those of the already loaded VVMOSS.
//
//////
	u64 CALLTYPE vvmt_firstCallback(u64 tnCallbackAddress)
	{
		//////////
		// Load all VVM and VVMOSS functions
		//////
			iLoadVvmFunctionsFromVVM((void**)tnCallbackAddress);
			iLoadVvmOssFunctionsFromVVM((void**)tnCallbackAddress);


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to handle any bootstrap initialization, things where only primitive services of the
// VVM and VVMOSS are available, and not completely at that.
//
//////
	void CALLTYPE vvmt_bootstrapInitialization(u64 tnDebuggerInterfaceAddress)
	{
		// Nothing is currently defined for bootstrap initialization
	}





//////////
//
// Called to handle any initialization after the system has been through bootstrapping, and
// all initial conditions are met, able to service requests.
//
//////
	void CALLTYPE vvmt_initialization(u64 tnDebuggerInterfaceAddress)
	{
		// Nothing is currently defined for initialization
	}




//////////
//
// Called to indicate the VVMTESTS.DLL version
//
//////
	const s8* CALLTYPE vvmt_getVersion(void)
	{
		return(cgcVvmtVersion);
	}




//////////
//
// Called to execute the tests, returns true or false if the tests passed.
// Uses the vvm_resourcePrintf() function to direct output made during the tests.
//
//////
	bool CALLTYPE vvmt_executeTests(u64 lnHandleLog)
	{
		bool llResult;


//////////
// Test code
//////
	SBGRA		white				= {255,255,255,255};
	SBGRA		black				= {0,0,0,255};
//	SDateTime	lsdtStart, lsdtStop;
//	u32			lnI;
	u32			lnWidth, lnHeight;
	SCanvas*	lc;
//	SCanvas*	lcScaled;
	SCanvas*	lcExtract;
	SBuilder*	builder;
//	f64			lnH, lnW, lnHStep, lnWStep;
//	s8			timing[4096];


// 	//////////
// 	// Debug the area algorithms
// 	//////
// 
// 	f64			lfTheta, lfArea;
// 	s32			lnGravity, lnGravity1Intercept, lnGravity2Intercept;
// 	SXYS32		lnPo;
// 	SXYF64		lfPo, p1, p2, pg;
// 	s8			buffer[4096];
// 
// 		oss_builderCreateAndInitialize(&builder, 2048);
// 		// po
// 		lnPo.x = 0;
// 		lnPo.y = 0;
// 		lfPo.x = 0.5;
// 		lfPo.y = 0.5;
// 
// 		// Repeat around the circle
// 		for (lfTheta = (_PI / 4.0) + (_PI / 500.0); lfTheta < _2PI; lfTheta += _2PI / 500.0)
// 		{
// 			//////////
// 			// Reset the points
// 			//////
// 				// p1
// 				p1.x = lfPo.x;
// 				p1.y = lfPo.y;
// 				// p2
// 				p2.x = lfPo.x;
// 				p2.y = lfPo.y;
// 				// pg
// 				pg.x = lfPo.x;
// 				pg.y = lfPo.y;
// 
// 
// 			//////////
// 			// Compute their intercepts
// 			//////
// 				oss_math_getNextAxisInterceptXY(&p1, oss_math_adjustTheta(lfTheta));
// 				oss_math_getNextAxisInterceptXY(&pg, oss_math_adjustTheta(lfTheta - (_PI / 8.0)));
// 				oss_math_getNextAxisInterceptXY(&p2, oss_math_adjustTheta(lfTheta + (_PI / 4.0)));
// 
// 
// 			//////////
// 			// Grab their gravities
// 			//////
// 				lnGravity				= oss_math_getGravityByRelativePosition(&pg, &lnPo);
// 				lnGravity1Intercept		= oss_math_getGravityByRelativePosition(&p1, &lnPo);
// 				lnGravity2Intercept		= oss_math_getGravityByRelativePosition(&p2, &lnPo);
// 				lnGravity				= oss_math_fineAdjustGravityByTheta(&lfPo, &p1, &pg, lnGravity1Intercept, lnGravity);
// 
// 
// 			//////////
// 			// Compute their floan based on gravity of the first line, and use its points for the area
// 			// Note:  We assume these two sides have gravities facing toward each other, so we only need one
// 			//////
// // if (lfTheta >= 3.932)
// // 	_asm nop;
// 				lfArea = oss_math_getAreaOfSquareUsing_po_p1_p2(lnGravity1Intercept, lnGravity2Intercept, lnGravity, &lfPo, &p1, &p2);
// 
// 
// 			//////////
// 			// Note the result
// 			//////
// 				// theta, p1.x,p1.y, p2.x,p2.y, area
// 				sprintf_s(buffer, sizeof(buffer), "%lf, , %lf,%lf, , %lf,%lf, %lf, %u, %u, %u\n\0", lfTheta, p1.x, p1.y, p2.x, p2.y, lfArea, lnGravity1Intercept, lnGravity2Intercept, lnGravity);
// 				oss_builderAppendData(builder, buffer, -1);
// 		}
// 		// When we get here, we're done
// 		oss_builderAsciiWriteOutFile(builder, "c:\\temp\\information.txt");


	//////////
	// Create a canvas, draw a line
	//////
		lc = oss_createCanvas(0, 600, 600, white);
		if (lc)
		{
			f64		lfTheta, lfCos50, lfSin50, lfCos300, lfSin300;
			SXYF32	p1, p2;

			for (lfTheta = _PI / 4.0; lfTheta < _2PI / 2.0; lfTheta += _2PI / 32.0)
			{
if (lfTheta >= 2.1598 && lfTheta <= 2.1599)
	_asm nop;
				// Inner radius
				lfCos50		= 50.0 * cos(lfTheta);
				lfSin50		= 50.0 * sin(lfTheta);

				// Outer radius
				lfCos300	= 290.0 * cos(lfTheta);
				lfSin300	= 290.0 * sin(lfTheta);

				// Set the points
				p1.x		= (f32)(300.0 + lfCos50);
				p1.y		= (f32)(300.0 + lfSin50);
				p2.x		= (f32)(300.0 + lfCos300);
				p2.y		= (f32)(300.0 + lfSin300);

				// Draw this line
				oss_canvasLine(lc, lc->bd, &p1, &p2, 5.0, black, true);
			}
			oss_bitmapSaveToDisk(lc, lc->bd, "c:\\temp\\test.bmp");
		}


//////////
// Test for rotating an image
//////
	oss_builderCreateAndInitialize(&builder, 2048);
	oss_bitmapLoadFromDisk("c:\\temp\\test.bmp", &lc, &lnWidth, &lnHeight, white);

	lcExtract = oss_canvasExtract(lc, lc->bd, 200, 200, 205, 205);
	oss_canvasRotate(lc, lc->bd, 200, 200, lcExtract, lcExtract->bd, 6.28f * (45.0f / 360.0f));

// 	lnHStep = (f64)lnHeight / 5.0;
// 	lnWStep = (f64)lnWidth / 5.0;
// 	for (lnH = lnHeight / 5, lnW = lnWidth / 5; lnH < (f64)lnHeight * 2.0f; lnH += lnHStep, lnW += lnWStep)
// 	{
// 		lcScaled = oss_createCanvas(0, (u32)lnW, (u32)lnH, white);
// 		for (lnI = 0; lnI < 10; lnI++)
// 		{
// 			oss_dateTimeGet(&lsdtStart);
// 			oss_canvasScale(lcScaled, lc, &lcScaled->firstScaleMap);
// 			oss_dateTimeGet(&lsdtStop);
// 			sprintf(timing, "\\temp\\Scale_%ux%u_Iteration_%u_Milliseconds_%f.bmp\0", (u32)lnW, (u32)lnH, lnI, (f32)((f64)(lsdtStop.tickCount - lsdtStart.tickCount) / (f64)lsdtStart.frequency));
// 			oss_builderAppendData(builder, timing + 6, strlen(timing) - 6 - 4);
// 	//		oss_bitmapSaveToDisk(lcScaled, lcScaled->bd, timing);
// 			oss_builderAppendData(builder, "\n", 1);
// 		}
// 		//oss_bitmapSaveToDisk(lcScaled, lcScaled->bd, buffer);
// 		//oss_deleteCanvas(lcScaled);
// 	}
// 	oss_sharedAsciiWriteOutFile("c:\\temp\\information.txt", builder->data, builder->populatedLength);

		//////////
		// If any test fails, early out
		//////
			llResult =	(true		& ivvmt_testSha1(lnHandleLog));
			llResult =	(llResult	& ivvmt_testSll(lnHandleLog));
			llResult =	(llResult	& ivvmt_testSll4(lnHandleLog));
			llResult =	(llResult	& ivvmt_testBxml(lnHandleLog));


		//////////
		// Indicate total success or not
		//////
			return(llResult);
	}




//////////
//
// For debugging, turns on/off the internal breakpoint flag.
//
//////
	void CALLTYPE vvmt_enableBreakpoints(void)
	{
	}

	void CALLTYPE vvmt_disableBreakpoints(void)
	{
	}
