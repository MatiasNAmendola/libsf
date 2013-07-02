//////////
//
// /libsf/vvm/vvm/vvm_const.h
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 07, 2012
//////
// Change log:
//     September 24, 2012 - Initial creation
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
// Constant strings
//////
	const s8	cgcVvmVersion[]								= "VVM.EXE Version 0.60";							// The format of this version string will remain consistent throughout all future releases
	const s8	cgcEnu[]									= "enu";
	const s8	cgcVvmEngDll[]								= "vvmeng.dll";
	const s8	cgcUnableToLocateResource[]					= "Unable to locate resource";




//////////
// For vvm_tests.cpp
//////
	const u8	cgcVvmTestDll_firstCallback[]				= "vvmt_firstCallback";
	const u8	cgcVvmTestDll_bootstrapInitialization[]		= "vvmt_bootstrapInitialization";
	const u8	cgcVvmTestDll_initialization[]				= "vvmt_initialization";
	const u8	cgcVvmTestDll_getVersion[]					= "vvmt_getVersion";
	const u8	cgcVvmTestDll_executeTests[]				= "vvmt_executeTests";
	const u8	cgcVvmTestsDirectory[]						= ".\\tests\\";
	const u8	cgcVvmTestCoreDll[]							= "vvmt_core.dll";
	const u8	cgcVvmTestFilePattern[]						= "*.dll";
	const u8	cgcVvmTestLogFile[]							= "vvm_test_results.txt";




//////////
// Constants used to define region events
//////
	// vvm_structs.h, see SRegion definition
	const u32	_VVM_REGION_ENTER				= 1;
	const u32	_VVM_REGION_LEAVE				= 2;
	const u32	_VVM_REGION_MOUSE_DOWN			= 4;
	const u32	_VVM_REGION_MOUSE_UP			= 8;
	const u32	_VVM_REGION_MOUSE_MOVE			= 16;
	const u32	_VVM_REGION_HOVER				= 32;
	const u32	_VVM_REGION_DRAG_START			= 64;
	const u32	_VVM_REGION_DRAG_STOP			= 128;
	const u32	_VVM_REGION_DRAG_MOVE			= 256;



	
//////////
// Dynamic snippet types, loaded as needed at runtime
//////
	const u32	_VVM_DYNSNIP_TYPE_VVM			= 1;			// A call to the VVM itself
	const u32	_VVM_DYNSNIP_TYPE_DLL			= 2;			// A call to the a specified DLL
	const u32	_VVM_DYNSNIP_TYPE_Bxml			= 3;			// A call to a loaded BXML snippet
