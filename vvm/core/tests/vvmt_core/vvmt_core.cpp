//////////
//
// /libsf/vvm/core/vvmtests/vvmt_core/vvmt_core.cpp
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
//     Jun.20.2013	- Refactoring into a stand-alone DLL loaded at runtime only if -test is specified on the command line
//     Mar.02.2013	- Initial creation
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
#include "\libsf\utils\sha1\sha1.h"											// SHA-1 hashing algorithm
#include "\libsf\vvm\core\localization\vvmenu\resource.h"					// Resource constants
#include "vvmt_const.h"
#include "\libsf\vvm\core\vvm\vvm_structs.h"
#include "\libsf\vvm\core\oss\oss_structs.h"
#include "\libsf\vvm\core\common\common_vvm.h"
#include "\libsf\vvm\core\common\common_oss.h"
#include "vvmt_structs.h"
#include "vvmt_defs.h"
#include "vvmt_glob.h"
#include "\libsf\vvm\core\oss\oss_class.h"
#include "\libsf\vvm\core\common\vvm_key_const.h"

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
			iLoadVvmFunctionsFromDll();
			iLoadOssFunctionsFromDll();


		//////////
		// Tell each DLL to initialize itself
		//////
			vvm_firstCallback(0);
			vvm_bootstrapInitialization();
			oss_firstCallback(0);
			oss_bootstrapInitialization();


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
	SXYF64* make_SXYF64(SXYF64* p, f64 x, f64 y)
	{
		p->x = x;
		p->y = y;
		return(p);
	}

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
// 		vvm_builderCreateAndInitialize(&builder, 2048);
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
// 				vvm_math_getNextAxisInterceptXY(&p1, vvm_math_adjustTheta(lfTheta));
// 				vvm_math_getNextAxisInterceptXY(&pg, vvm_math_adjustTheta(lfTheta - (_PI / 8.0)));
// 				vvm_math_getNextAxisInterceptXY(&p2, vvm_math_adjustTheta(lfTheta + (_PI / 4.0)));
// 
// 
// 			//////////
// 			// Grab their gravities
// 			//////
// 				lnGravity				= vvm_math_getGravityByRelativePosition(&pg, &lnPo);
// 				lnGravity1Intercept		= vvm_math_getGravityByRelativePosition(&p1, &lnPo);
// 				lnGravity2Intercept		= vvm_math_getGravityByRelativePosition(&p2, &lnPo);
// 				lnGravity				= vvm_math_fineAdjustGravityByTheta(&lfPo, &p1, &pg, lnGravity1Intercept, lnGravity);
// 
// 
// 			//////////
// 			// Compute their floan based on gravity of the first line, and use its points for the area
// 			// Note:  We assume these two sides have gravities facing toward each other, so we only need one
// 			//////
// // if (lfTheta >= 3.932)
// // 	_asm nop;
// 				lfArea = vvm_math_getAreaOfSquareUsing_po_p1_p2(lnGravity1Intercept, lnGravity2Intercept, lnGravity, &lfPo, &p1, &p2);
// 
// 
// 			//////////
// 			// Note the result
// 			//////
// 				// theta, p1.x,p1.y, p2.x,p2.y, area
// 				sprintf_s(buffer, sizeof(buffer), "%lf, , %lf,%lf, , %lf,%lf, %lf, %u, %u, %u\n\0", lfTheta, p1.x, p1.y, p2.x, p2.y, lfArea, lnGravity1Intercept, lnGravity2Intercept, lnGravity);
// 				vvm_builderAppendData(builder, buffer, -1);
// 		}
// 		// When we get here, we're done
// 		vvm_builderAsciiWriteOutFile(builder, "c:\\temp\\information.txt");


	//////////
	// Create a canvas, draw a line
	//////
		lc = oss_createCanvas(0, 600, 600, white);
		if (lc)
		{
			// Draw a bezier-3 curve, a bezier-4 curve, and a bezier-5 curve
			//////////
			// Initialize
			//////
				SBezier bez3, bez4, bez5;
				SXYF64 p1, p2, p3, p4, p5;
				SBGRA black, white;


			//////////
			// Bezier-3
			//////
				black.color = rgba(0,0,0,255);
				// 100,500 to 300,50 to 500,500
// 				vvm_bezier_initialize(&bez3, 3, 1000, true);
// 				vvm_bezier_setByValues(&bez3, black, make_SXYF64(&p1, 100.0, 500.0), make_SXYF64(&p2, 300.0, 50.0), make_SXYF64(&p3, 500.0, 500.0), NULL, NULL);
// 				oss_canvasBezier(lc, lc->bd, &bez3);
// 				oss_bitmapSaveToDisk(lc, lc->bd, "c:\\temp\\bezier3.bmp");


			//////////
			// Bezier-4
			//////
				white.color = rgba(255,255,255,255);
				// 100,500 to 200,50 to 300,300 to 500, 500
// 				oss_canvasFillRect(lc, lc->bd, 0, 0, lc->width, lc->height, 0, white, white);
// 				vvm_bezier_initialize(&bez4, 4, 1000, true);
// 				vvm_bezier_setByValues(&bez4, black, make_SXYF64(&p1, 100.0, 500.0), make_SXYF64(&p2, 200.0, 50.0), make_SXYF64(&p3, 300.0, 300.0), make_SXYF64(&p4, 500.0, 500.0), NULL);
// 				oss_canvasBezier(lc, lc->bd, &bez4);
// 				oss_bitmapSaveToDisk(lc, lc->bd, "c:\\temp\\bezier4.bmp");


			//////////
			// Bezier-5
			//////
				// 100,500 to 200,50 to 300,300 to 400,100 to 500,300
// 				oss_canvasFillRect(lc, lc->bd, 0, 0, lc->width, lc->height, 0, white, white);
// 				vvm_bezier_initialize(&bez5, 5, 1000, true);
// 				vvm_bezier_setByValues(&bez5, black, make_SXYF64(&p1, 100.0, 500.0), make_SXYF64(&p2, 200.0, 50.0), make_SXYF64(&p3, 300.0, 300.0), make_SXYF64(&p4, 400.0, 100.0), make_SXYF64(&p5, 500.0, 300.0));
// 				oss_canvasBezier(lc, lc->bd, &bez5);
// 				oss_bitmapSaveToDisk(lc, lc->bd, "c:\\temp\\bezier5.bmp");
// 				_asm nop;

// 			f64			lfTheta, lfDeltaX, lfDeltaY, lfLineLength, lfHalfLineX, lfHalfLineY, lfStepXM, lfStepYM;
// 			u64			lnPixelsDrawn;
// 			SPolygon	polygon;
// 			SXYF64		p1, p2, p3, p4, gravity;
// 
// 			// Initialize the polygon
// 			memset(&polygon, 0, sizeof(polygon));
// 			polygon.line		= (SPolyLine**)NULL;
// 			vvm_polygon_initialize(&polygon, 4, true);
// 
// 			lfTheta = 0.0;
// 			for (lfTheta = 0.0; lfTheta < _2PI; lfTheta += _2PI / 8.0)
// 			{
// 				// Set the points
// 				// p1
// 				p1.x			= 300.0 + (50.0 * cos(lfTheta + _PI / 32.0));
// 				p1.y			= 300.0 + (50.0 * sin(lfTheta + _PI / 32.0));
// 				// p2
// 				p2.x			= 300.0 + (50.0 * cos(lfTheta - _PI / 32.0));
// 				p2.y			= 300.0 + (50.0 * sin(lfTheta - _PI / 32.0));
// 				// p3
// 				p3.x			= 300.0 + (290.0 * cos(lfTheta - _PI / 32.0));
// 				p3.y			= 300.0 + (290.0 * sin(lfTheta - _PI / 32.0));
// 				// p2
// 				p4.x			= 300.0 + (290.0 * cos(lfTheta + _PI / 32.0));
// 				p4.y			= 300.0 + (290.0 * sin(lfTheta + _PI / 32.0));
// 
// 				// Gravity is the center point of the line's 4 point coordinates
// 				gravity.x		= (p1.x + p2.x + p3.x + p4.x) / 4.0;
// 				gravity.y		= (p1.y + p2.y + p3.y + p4.y) / 4.0;
// 
// 				// Set the lines
// 				vvm_polygon_setByValues(&polygon, 0, &p1, &p2, &gravity);		// p1..p2
// 				vvm_polygon_setByValues(&polygon, 1, &p2, &p3, &gravity);		// p2..p3
// 				vvm_polygon_setByValues(&polygon, 2, &p3, &p4, &gravity);		// p3..p4
// 				vvm_polygon_setByValues(&polygon, 3, &p4, &p1, &gravity);		// p4..p1
// 
// 				// Draw the polygon
// 				lnPixelsDrawn = oss_canvasPolygon(lc, lc->bd, &polygon, black);
// 
// 				// Reset it for the next go-round
// 				vvm_polygon_reset(&polygon, true);

// 				// Draw this line
//				SXYF32 p1, p2;
// 				oss_canvasLine(lc, lc->bd, &p1, &p2, 5.0, black, true);
//			}
//			oss_bitmapSaveToDisk(lc, lc->bd, "c:\\temp\\test.bmp");
		}


//////////
// Test for rotating an image
//////
	vvm_builderCreateAndInitialize(&builder, 2048);
	oss_bitmapLoadFromDisk("c:\\temp\\test.bmp", &lc, &lnWidth, &lnHeight, white);

	lcExtract = vvm_canvasExtract(lc, lc->bd, 200, 200, 205, 205);
	vvm_canvasRotate(lc, lc->bd, 200, 200, lcExtract, lcExtract->bd, 6.28f * (45.0f / 360.0f));

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
// 			vvm_builderAppendData(builder, timing + 6, strlen(timing) - 6 - 4);
// 	//		oss_bitmapSaveToDisk(lcScaled, lcScaled->bd, timing);
// 			vvm_builderAppendData(builder, "\n", 1);
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
