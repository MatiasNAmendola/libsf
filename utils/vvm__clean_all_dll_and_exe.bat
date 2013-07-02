@echo off

REM move to developmental directory
cd \libsf\vvm\dev\
erase /Q *.*

REM move to developmental plugins directory
cd \libsf\vvm\dev\plugins
erase /Q *.*

REM move to developmental tests directory
cd \libsf\vvm\dev\tests
erase /Q *.*

REM remove all the debug subdirs
echo Removing debug and release folders
cd \libsf\vvm\
for /d /r . %%d in (Debug Release debug_vasm) do @if exist "%%d" echo "%%d" && rd /s/q "%%d"

REM remove all NCB intellisense databases, program databases, and intermediate files
echo Removing intellisense databases
del /s *.ncb
del /s *.pdb
del /s *.manifest
REM All done
