@ECHO off
::Script build the project


if ["%1"]==["--help"] goto HELP

if ["%1"]==["debug"] (set BUILD_TYPE=Debug & goto BUILD) 
if [%1]==[] (set BUILD_TYPE=Debug & goto BUILD)
if ["%1"]==["release"] (set BUILD_TYPE=Release & goto BUILD)

echo "ERROR: unrecognized argument "%1%"" & GOTO HELP
goto HELP

:BUILD
echo BUILD_TYPE = %BUILD_TYPE%
if not exist build (mkdir build)
cd build
cmake ../ ../ -G "Visual Studio 15 2017 Win64"
MSBuild.exe CommonTests.sln /p:Configuration=%BUILD_TYPE% /p:Platform=x64 
cd ..
exit /b

:HELP
echo
echo usage: build.bat ['debug'] ^| ['release']
echo Options:
echo build the project in debug/release type
