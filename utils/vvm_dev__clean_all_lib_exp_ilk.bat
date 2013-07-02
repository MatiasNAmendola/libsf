@echo off

REM move to developmental directory
cd \libsf\vvm\dev\
erase /Q *.ilk
erase /Q *.lib
erase /Q *.exp

REM move to plugins directory
cd \libsf\vvm\dev\plugins\
erase /Q *.ilk
erase /Q *.lib
erase /Q *.exp

REM move to tests directory
cd \libsf\vvm\dev\tests\
erase /Q *.ilk
erase /Q *.lib
erase /Q *.exp

REM All done
