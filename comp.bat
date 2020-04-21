@echo off
set config=%1
IF "%1" == "" (
   set config=debug
)
make config=%config% -j 9
