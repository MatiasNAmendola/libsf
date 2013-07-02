@echo off


REM Canvas
echo Building Canvas test include files
cd canvas
call build_vvmt_canvas_test_file.bat
cd ..


REM All done
pause
