@echo off
gen > in
a < in > out
stupid < in > ok
fc ok out
if errorlevel 1 exit
test
