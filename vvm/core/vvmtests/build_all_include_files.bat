@echo off


REM Core
cd vvmt_core\include_file_builders\
call build_all_include_files.bat
cd ..\..


REM Canvas
cd vvmt_canvas\include_file_builders\
call build_all_include_files.bat
cd ..\..
