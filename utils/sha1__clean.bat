@echo off

REM move to starting directory
cd \libsf\utils\sha1\

REM remove all the debug subdirs
echo Removing debug and release folders
for /d /r . %%d in (Debug Release) do @if exist "%%d" echo "%%d" && rd /s/q "%%d"

REM remove all NCB intellisense databases
echo Removing intellisense databases
del /s *.ncb
REM All done
