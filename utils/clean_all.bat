@echo off
REM VVM
cd \libsf\utils\
call vvm__clean_all_dll_and_exe.bat

REM SHA-1
cd \libsf\utils\
call sha1__clean.bat

REM F2H
cd \libsf\utils\
call f2h__clean.bat

REM Remove the exceedingly large canvas test2 include file
erase \libsf\vvm\core\vvmtests\include\vvmt_canvas_test2.h

REM All done
pause
