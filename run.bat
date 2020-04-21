@echo off
set config=%1
IF "%1" == "" (
   set config=Debug
)
cd bin/%config%-windows-x86_64/TypedEditor/ && call TypedEditor.exe && cd ../../../
