@ECHO off
::Script set up .gitignore

if ["%1"]==["--help"] goto HELP

if not exist .gitignore (
echo here should be text
)>".gitignore"

if exist "build" if not exist "build/.gitignore" echo *.* > "build/.gitignore"
if exist "bin" if not exist "bin/.gitignore" echo *.* > "bin/.gitignore"
if exist ".vs" if not exist ".vs/.gitignore" echo *.* > ".vs/.gitignore"
exit /b

:HELP
echo
echo "Set up gitignore. Run scripts from working tree to:"
echo "ignore system files in working tree"
echo "ignore everything in build"
echo "ignore everything in bin"
echo "ignore everything in .vs"
