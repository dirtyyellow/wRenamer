@echo off
echo test
@REM mkdir build
cd .\build\
cmake ..
make
.\wRenamer.exe
echo Finish