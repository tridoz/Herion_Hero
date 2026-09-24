@echo off
setlocal

set "EXECUTABLE=%~dp0bin\Herion_Hero.exe"

echo Checking game executable...

if not exist "%EXECUTABLE%" (
    echo ERROR: Executable not found:
    echo %EXECUTABLE%
    echo.
    echo Run build.bat first.
    exit /b 1
)

echo Executable found:
echo %EXECUTABLE%
echo.

echo Launching Herion Hero...
echo.

"%EXECUTABLE%"

set "EXIT_CODE=%ERRORLEVEL%"

echo.

if %EXIT_CODE% EQU 0 (
    echo Game closed normally.
) else (
    echo Game exited with code %EXIT_CODE%.
)

endlocal
exit /b %EXIT_CODE%