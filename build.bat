@ECHO off
::Script build the project

:BUILD 
IF NOT EXIST build mkdir build
CD build; 
cmake ../ ../ -G "Visual Studio 15 2017 Win64"
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe" CommonTests.sln /p:Configuration=%BUILD_TYPE% /p:Platform=x64 
CD ..
EXIT /b

IF %1 == "--help" GOTO HELP

IF %1== []( set build_type = Debug & goto BUILD)
IF %1 == "debug"( goto BUILD)
IF %1 == "release"( set build_type = Release goto BUILD)

ECHO "%build_type%"
ECHO "ERROR: unrecognized argument "%1%"" & GOTO HELP
EXIT /b



:HELP
ECHO ""
ECHO "usage: build.bat ['debug'] | ['release']"
ECHO "Options:"
ECHO "build the project in debug/release type"
