@echo off
set config=%1
IF "%1" == "" (
   set config=debug
)
IF exist bin/%config%-windows-x86_64/TypedEditor/ (
	robocopy vendor/bin/gcc bin/%config%-windows-x86_64/TypedEditor/
) ELSE (
	echo directory does not exist! build first!
)