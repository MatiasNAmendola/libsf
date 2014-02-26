//////////
//
// /libsf/vvm/core/vvmtests/vvmt_canvas/vvmt_canvas.cpp
//
//////
// Version 0.70
// Copyright (c) 2013, 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.25.2014
//////
// Change log:
//     Feb.25.2014 - Development on 0.70 begins
//     Jun.20.2013	- Refactoring into a stand-alone DLL loaded at runtime only if -test is specified on the command line
//     Mar.08.2013	- Initial creation
//////
//
// VVM Test application.
// Tests the Canvas functionality.
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




//////////
//
// Top level for running test cases against the Canvas engine.
//
//////
	bool ivvmt_testCanvas(u64 lnHandleLog)
	{
		// Indicate what test we're running
		vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_TESTING);

		// These tests cascade, if one fails the ones after cannot continue
		if (!iivvmt_testCanvas_1(lnHandleLog))			return false;							// #01 - Process gradient and large scaling
		if (!iivvmt_testCanvas_2(lnHandleLog))			return false;							// #01 - Process fine grained scaling

		// When we get here, success
		vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_PASSED);
		return true;
	}




	//////////
	// #01 - Create a canvas, give it a gradient, scale it a couple times and validate SHA-1s
	//////
		bool iivvmt_testCanvas_1(u64 lnHandleLog)
		{
			SRGBA		ul, ur, lr, ll;
			u64			lnSha1As64Bit;
			u32			lnSha1As32Bit;
			u8			sha20Bytes[20];
			SCanvas*	canvas;
			SCanvas*	canvasScaled1;
			SCanvas*	canvasScaled2;


			// Tell which test we're running
			vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_1);


			//////////
			// Create the standard canvas
			//////
				canvas = oss_requestCanvas(0, 640, 480, rgba(0,0,0,255), true, true);
				if (!canvas)
				{
					// Failure creating the canvas
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_CANNOT_CREATE);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Create a canvas for scaling
			//////
				canvasScaled1 = oss_requestCanvas(0, 517, 799, rgba(0,0,0,255), true, true);
				if (!canvasScaled1)
				{
					// Failure creating the canvas
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_SCALED_CANNOT_CREATE);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Create another canvas for scaling
			//////
				canvasScaled2 = oss_requestCanvas(0, 128, 16, rgba(0,0,0,255), true, true);
				if (!canvasScaled2)
				{
					// Failure creating the canvas
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_SCALED_CANNOT_CREATE);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Perform a gradient
			//////
				ul.color	= rgba(255, 255, 255, 255);		// white
				ur.color	= rgba(255,   0,   0, 255);		// red
				lr.color	= rgba(  0, 255,   0, 255);		// green
				ll.color	= rgba(  0,   0, 255, 255);		// blue
				oss_canvasGradient(canvas, canvas->bd, ul, ur, lr, ll);
				// For debugging:
				oss_saveBitmapToDisk(canvas, canvas->bd, "\\temp\\gradient.bmp");


			//////////
			// Was it valid?
			//////
				oss_sha1ComputeSha1((s8*)canvas->bd, canvas->width * canvas->height * sizeof(SRGBA), sha20Bytes);
				lnSha1As64Bit = oss_sha1Compute64BitFromSha1(sha20Bytes);
				lnSha1As32Bit = oss_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgn_Test1_Canvas_Sha1As64Bit || lnSha1As32Bit != cgn_Test1_Canvas_Sha1As32Bit)
				{
					// The gradient does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_INVALID_GRADIENT);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Scale the gradient
			//////
				oss_canvasScale(canvasScaled1, canvas);
				// For debugging:
				oss_saveBitmapToDisk(canvasScaled1, canvasScaled1->bd, "\\temp\\gradientScaled1.bmp");


			//////////
			// Was it valid?
			//////
				oss_sha1ComputeSha1((s8*)canvasScaled1->bd, canvasScaled1->width * canvasScaled1->height * sizeof(SRGBA), sha20Bytes);
				lnSha1As64Bit = oss_sha1Compute64BitFromSha1(sha20Bytes);
				lnSha1As32Bit = oss_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgn_Test1_CanvasScaled1_Sha1As64Bit || lnSha1As32Bit != cgn_Test1_CanvasScaled1_Sha1As32Bit)
				{
					// The gradient does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_SCALED_INVALID_GRADIENT);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Scale the gradient
			//////
				oss_canvasScale(canvasScaled2, canvas);
				// For debugging:
				oss_saveBitmapToDisk(canvasScaled2, canvasScaled2->bd, "\\temp\\gradientScaled2.bmp");


			//////////
			// Was it valid?
			//////
				oss_sha1ComputeSha1((s8*)canvasScaled2->bd, canvasScaled2->width * canvasScaled2->height * sizeof(SRGBA), sha20Bytes);
				lnSha1As64Bit = oss_sha1Compute64BitFromSha1(sha20Bytes);
				lnSha1As32Bit = oss_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgn_Test1_CanvasScaled2_Sha1As64Bit || lnSha1As32Bit != cgn_Test1_CanvasScaled2_Sha1As32Bit)
				{
					// The gradient does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_SCALED_INVALID_GRADIENT);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}




	//////////
	// #02 - Create a canvas, load an image, validate SHA-1, scale it a couple times and validate SHA-1s
	//////
		bool iivvmt_testCanvas_2(u64 lnHandleLog)
		{
			s64			lnResult;
			u64			lnSha1As64Bit;
			u32			lnSha1As32Bit, lnWidth, lnHeight;
			u8			sha20Bytes[20];
			s8*			lcTemp;
			SCanvas*	canvas;
			SCanvas*	canvasScaled1;
			SCanvas*	canvasScaled2;


			// Tell which test we're running
			vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_1);


			//////////
			// Create the standard canvas
			//////
				lcTemp = oss_sharedAsciiGetTempFilename();
				if (!oss_sharedAsciiWriteOutFile(lcTemp, (s8*)&cgc_Test2_Canvas[0], sizeof(cgc_Test2_Canvas)))
				{
					// Failure writing out the temp file
// TODO: localization here
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_CANNOT_CREATE/*IDS_VVM_TEST_CANVAS_CANNOT_SAVE_TEST_BITMAP_TO_DISK*/);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}

				// Attempt to load it as a valid bitmap
				lnResult = (s64)oss_loadBitmapFromDisk(lcTemp, &canvas, &lnWidth, &lnHeight, rgba(0,0,0,255));

				// Delete the temp file
				oss_sharedAsciiDeleteFile(lcTemp);

				// Did the bitmap load okay?
				if (lnResult < 0 || !canvas)
				{
					// Failure creating the canvas
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_CANNOT_CREATE);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}

				// For debugging:
				oss_saveBitmapToDisk(canvas, canvas->bd, "\\temp\\canvas2.bmp");


			//////////
			// Create a canvas for scaling
			//////
				canvasScaled1 = oss_requestCanvas(0, lnWidth - 1, lnHeight - 1, rgba(0,0,0,255), true, true);
				if (!canvasScaled1)
				{
					// Failure creating the canvas
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_SCALED_CANNOT_CREATE);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Create another canvas for scaling
			//////
				canvasScaled2 = oss_requestCanvas(0, lnWidth + 1, lnHeight + 1, rgba(0,0,0,255), true, true);
				if (!canvasScaled2)
				{
					// Failure creating the canvas
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_SCALED_CANNOT_CREATE);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Was it valid?
			//////
				oss_sha1ComputeSha1((s8*)canvas->bd, canvas->width * canvas->height * sizeof(SRGBA), sha20Bytes);
				lnSha1As64Bit = oss_sha1Compute64BitFromSha1(sha20Bytes);
				lnSha1As32Bit = oss_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgn_Test2_Canvas_Sha1As64Bit || lnSha1As32Bit != cgn_Test2_Canvas_Sha1As32Bit)
				{
					// The gradient does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_INVALID_GRADIENT);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Scale the gradient
			//////
				oss_canvasScale(canvasScaled1, canvas);
				// For debugging:
				oss_saveBitmapToDisk(canvasScaled1, canvasScaled1->bd, "\\temp\\canvas2Scaled1.bmp");


			//////////
			// Was it valid?
			//////
				oss_sha1ComputeSha1((s8*)canvasScaled1->bd, canvasScaled1->width * canvasScaled1->height * sizeof(SRGBA), sha20Bytes);
				lnSha1As64Bit = oss_sha1Compute64BitFromSha1(sha20Bytes);
				lnSha1As32Bit = oss_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgn_Test2_CanvasScaled1_Sha1As64Bit || lnSha1As32Bit != cgn_Test2_CanvasScaled1_Sha1As32Bit)
				{
					// The gradient does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_SCALED_INVALID_GRADIENT);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			//////////
			// Scale the gradient
			//////
				oss_canvasScale(canvasScaled2, canvas);
				// For debugging:
				oss_saveBitmapToDisk(canvasScaled2, canvasScaled2->bd, "\\temp\\canvas2Scaled2.bmp");


			//////////
			// Was it valid?
			//////
				oss_sha1ComputeSha1((s8*)canvasScaled2->bd, canvasScaled2->width * canvasScaled2->height * sizeof(SRGBA), sha20Bytes);
				lnSha1As64Bit = oss_sha1Compute64BitFromSha1(sha20Bytes);
				lnSha1As32Bit = oss_sha1Compute32BitFromSha1(sha20Bytes);
				if (lnSha1As64Bit != cgn_Test2_CanvasScaled2_Sha1As64Bit || lnSha1As32Bit != cgn_Test2_CanvasScaled2_Sha1As32Bit)
				{
					// The gradient does not match the expected SHA-1 value
					vvm_resourcePrintf(IDS_VVM_TEST_CANVAS_SCALED_INVALID_GRADIENT);
					vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
					return(false);
				}


			// If we get here, we're good
			vvm_resourcePrintf(IDS_VVM_TEST_PASS);
			return(true);
		}
