@echo off


REM BXML
echo Building BXML test include files
cd bxml
call build_vvmt_bxml_test_file.bat
cd ..


REM All done
pause
