@echo off

cd ../../src

gcc -Wall -Werror -Wextra -std=c99 -O3 -c -o../bin/memory.obj memory.c

if %ERRORLEVEL% EQU 0 (
	goto success
) else (
	goto failure
)

:success
cd ../lib
ar rcv libcp-win.a ../bin/memory.obj
cd ../cmp/win
echo.
echo Memory compilation is successful.
echo.
pause 1>nul
exit /b 0

:failure
cd ../cmp/win
pause 1>nul
exit /b 1