        This repository contains all source code maintained
        by the Liberty Software Foundation.

--------------

        May.31.2013 - Development of WhiteBox ongoing.
        May.11.2013 - Development of WhiteBox continues.  About 2500 lines of code.
        Apr.29.2013 - Development on Visual FreePro is suspended pending the completion of WhiteBox.
        Apr.29.2013 - Development of WhiteBox begins.

--------------

        As of Feb.20.2013, it contains The Visual FreePro Project,
        which is comprised of several sub-components:

        (1) VVM    - The Visual FreePro Virtual Machine top-level program.
        (2) VVMOSS - The VVM Operating System Specific code.
        (3) VVMMC  - The VVM Machine Code assembler, disassembler for debugger.
        (4) VASM   - The VVM source code assembler.
        (5) VDebug - The VVM Debugger (a compiled DLL).
        (6) VDebugLauncher - The VVM Debugger launcher (tells VVM to load the debugger DLL).
        (7) Localization - Supporting resource DLLs for English and Spanish.
        (8) For more information, see:  https://github.com/RickCHodgin/libsf/blob/master/vvm/how_to_contribute.txt
        (9) For more information, see:  http://www.visual-freepro.org/videos/

--------------

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


Timeline
====
        See the https://github.com/RickCHodgin/libsf-full for the historic timeline.
