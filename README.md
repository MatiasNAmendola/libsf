This repository contains all source code maintained by the
Liberty Software Foundation.

--------------

May.31.2013 - Development of WhiteBox ongoing.
May.11.2013 - Development of WhiteBox continues.  About 2500 lines of code.
Apr.29.2013 - Development on Visual FreePro is suspended pending the completion of WhiteBox.
Apr.29.2013 - Development of WhiteBox begins.

As of February 20, 2013, it contains The Visual FreePro Project, which is comprised of several sub-components:

1. VVM - The Visual FreePro Virtual Machine top-level program.
2. VVMOSS - The VVM Operating System Specific code.
3. VVMMC - The VVM Machine Code assembler, disassembler for debugger.
4. VDebug - The VVM Debugger (a compiled DLL).
5. VDebugLauncher - The VVM Debugger launcher (tells VVM to load the debugger DLL).
6. VASM - The VVM source code assembler.
7. Localization - Supporting resource DLLs for English and Spanish.
8. For more information, see:  https://github.com/RickCHodgin/libsf/blob/master/vvm/how_to_contribute.txt
9. For more information, see:  http://www.visual-freepro.org/videos/

vvm
====
        The Visual FreePro Virtual Machine, independent and capable
        of being used for non-VFrP applications.  The VVM is localized
        through vvmenu.dll, with "enu" being replicated to other
        languages, such as "es" for Spanish, etc.
        
        Note:  To run the application, see README.md in vvm\bin\.
        Note:  To contribute to vvm, email rick.c.hodgin@gmail.com
        
        If you'd like to compile and try the application yourself, in-
        stall to the \libsf\ directory.  Some paths are currently hard-
        coded to that location.  In time, this will be made relative.


vvm\vvmoss
====
        VVM's Operating System Specific code.


vvm\vvmmc
====
        VVM's Machine Code support DLL. It is a common/shared component
        used to carry out work converting assembly source code into VVM
        machine code (assembly), the reverse (dissassembly), and other
        functions related to symbolic debugging information and convertying
        to and from the VVM's executable file format, which is RXML format.


vvm\vdebug
====
        A VVM debugger used for debugging native VVM programs.  The
        debugger is resource localized through vdebugenu.dll, with "enu"
        being the default. It is then replicated to other languages.
        Currently, The Visual FreePro Project maintains: English, Spanish.


vvm\vdebugLauncher
====
        The VVM debugger launcher (loads vdebug.dll into a running
        VVM instance).  Multiple debugger connections to a single,
        running VVM instance can be achieved, each debugging a different
        program, thread, or snippet (function).


vvm\vasm
====
        VVM's Assembler. This is a stand-alone application sed to convert
        from the command line VVM assembly source code into machine code
        the VVM can execute. As of Nov 23, 2012, development is focused
        on VASM, VVMMC and VVM's execution engine.


vvm\localization
====
        VVM supports localization DLLs in English and Spanish for three
        separate modules:  vvm, vdebug and vvmmc.


apps\whitebox
====
        WhiteBox is a non-linear audio/video editor.


Future Plans
====
		Apr.30.2014 - (planned) Visual FreePro 1.20 is released, fully supporting Android, plus bug fixes.  VVM 1.20 is also released for bug fixes.
		Dec.31.2013 - (planned) Visual FreePro 1.10 is released, adds support for Linux, FreeBSD and limited Android support, bug fixes.
		Dec.31.2013 - (planned) Visual FreePro 0.90 is released, a 1.00 candidate awaiting bug fixes.  VVM 1.10 is released for bug fixes.
		Dec.31.2013 - (planned) VVM 0.90 is released, a 1.00 candidate awaiting bug fixes.
		Mar.31.2013 - (planned) Visual FreePro's XBase engine is framed, functional, and more functionality is being added daily.
		Feb.28.2013 - (planned) Work begins on Visual FreePro's XBase engine, called VXB++ ([V]isual Freepro [XB]ase language[++]).
		Feb.28.2013 - (planned) VVM's execution engine will be largely complete, well debugged, with vdebug partly functional.
		Feb.28.2013 - (planned) VVM will be executing native VVM machine code.


Timeline
====
        (next up)    - Flushing out, fully debugging screen-related graphics, mouse and keyboard algorithms, Visual FreePro xbase language (VXB++).
        (after that) - Simultaneous development of VVM execution engine and the debugger (vdebug).
		May.31.2013 - WhiteBox development in progres.
		Apr.29.2013 - Work on WhiteBox begins.
		Apr.29.2013 - Work on Visual FreePro is suspended.
		Feb.20.2013 - Work continues on VVMC as of Feb.20.2013. Target of Feb.28.2012 for basic, functional execution engine.
		Nov.23.2012 - visual-freepro.org gets a limited facelift. Mostly so Rick can better access site on mobile device.
        Nov.17.2012 - VVMMC development (shared assembler, disassembler, symbolic processor, rxml handler).
        Nov.16.2012 - Work begins on VASM (VVM Assembler) and VVMMC (VVM Machine Code).  Framed.  VASM mostly coded.
        Nov.13.2012 - VVM instantiates empty bootup VM engine w/program+threading model, globals, timers, etc.
        Nov.11.2012 - VVM instantiates empty, VVM program+multi-thread scheduling and pseudo-thread execution engine framed.
        Nov.08.2012 - OSS supports loading 24-bit and 32-bit BMP images to VVM's RGBA format, rendering of OSS-font text to Canvas.
        Nov.06.2012 - Seven videos published, eight recorded. The first video had sound issues and likely won't be published.
        Nov.03.2012 - Video blogging begins. Refresh Screens and Canvas, alpha rendering, Canvas and Region progeny enforced (no circular references).
        Nov.02.2012 - Canvases rendering to parent canvases, onto Screens.
        Nov.01.2012 - Regions defined for Canvases, Canvases defined for Canvases, Canvases defined for Screens.
        Oct.30.2012 - OBED 0.50 spec. Coding as published. Planned completion of basic VVM functionality November 30.
        Oct.28.2012 - Optional semaphored access to callbacks (by future implementation of messages passed in multiple threads).
        Oct.24.2012 - VDebugger creates screens, processes events properly. Moving to graphics algorithms.
        Oct.21.2012 - VDebugger instantiating, connecting with VVM, VVMOSS.
        Oct.19.2012 - Added exe\vvm\ directory for release (stable development) versions for user testing.
		Oct.06.2012 - Added helper app to make complex, multi-model, multi-project function prototyping easier.
        Oct.05.2012 - Added ENU resource DLL. Need someone to create ES resource DLL.
        Oct.03.2012 - Beginning serious design work on VVM execution engine.  Decision to use DLLs for VFrP made (no stand-alone VFrP executable except the launcher).
        Oct.03.2012 - VVMOSS Focus events handled correctly.  Refactoring.
        Oct.02.2012 - VVMOSS Keyboard events handled correctly.
        Oct.01.2012 - VVM and VVMOSS process window movement, resizing, and mouse events correctly
        Sep.29.2012 - Added PBL 1.0 license text to all source files, and pbl_v1.txt file to project root.
        Sep.27.2012 - VVM and VVMOSS visibly create screens, process OSS messages.
        Sep.26.2012 - VVM and VVMOSS support for screen creation.
        Sep.24.2012 - VDebugLauncher connects with running VVM through messaging system. Refactoring. GUI development begins.
        Sep.22.2012 - VVM connects with VVMOSS.DLL. Development proceeds on VDebug and VDebugLauncher.
        Sep.19.2012 - Source code development begins on creating VVM, all work since August 18 has been on paper.
        Sep.17.2012 - libsf project created on github.
        Sep.11.2012 - Third official draft of VVM released, 4th in progress.
        Sep.01.2012 - First official draft of the Visual FreePro Virtual Machine (VVM) released.
        Aug.25.2012 - Rick makes official decision to use virtual machine.
		Aug.18.2012 - Rick begins contemplating the idea of creating and using a new virtual machine for VFrP's processing engine.
		Aug.xx.2012 - Development proceeds along .EXE/.DLL lines. Rick C. Hodgin becomes inspired, has a vision.
		Jul.xx.2012 - Development proceeds along .EXE/.DLL lines.
        Jul.12.2012 - The Visual FreePro Project begins. Initial plan is stand-alone .EXE with supporting .DLL.

