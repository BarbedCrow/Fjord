@echo off
pushd %~dp0\..\
call vendor\bin\premake\premake5.exe vs2022
call Fjord.sln
popd
PAUSE