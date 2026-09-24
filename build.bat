@echo off
setlocal

echo ========================================
echo       Herion Hero - Build
echo ========================================
echo.

set "BUILD_DIR=build"

REM ------------------------------------------------------------
REM Check CMake
REM ------------------------------------------------------------

echo Checking CMake...

where cmake >nul 2>&1
if errorlevel 1 (
    echo ERROR: CMake was not found in PATH.
    exit /b 1
)

cmake --version
echo.

REM ------------------------------------------------------------
REM Check Ninja
REM ------------------------------------------------------------

echo Checking Ninja...

where ninja >nul 2>&1
if errorlevel 1 (
    echo ERROR: Ninja was not found in PATH.
    exit /b 1
)

echo Ninja:
ninja --version
echo.

REM ------------------------------------------------------------
REM Check MSVC
REM ------------------------------------------------------------

echo Checking MSVC...

where cl >nul 2>&1
if errorlevel 1 (
    echo ERROR: MSVC cl.exe was not found in PATH.
    echo.
    echo Run this script from:
    echo Visual Studio Developer Command Prompt
    echo or
    echo Visual Studio Developer PowerShell
    exit /b 1
)

cl 2>&1 | findstr /C:"Version"
echo.

REM ------------------------------------------------------------
REM Configure CMake
REM ------------------------------------------------------------

echo Configuring CMake...

cmake -S . -B "%BUILD_DIR%" -G Ninja -DCMAKE_BUILD_TYPE=Debug

if errorlevel 1 (
    echo.
    echo ERROR: CMake configuration failed.
    exit /b 1
)

echo.
echo CMake configuration completed.
echo.

REM ------------------------------------------------------------
REM Build
REM ------------------------------------------------------------

echo Building Herion Hero...
echo.

cmake --build "%BUILD_DIR%" --parallel

if errorlevel 1 (
    echo.
    echo ERROR: Build failed.
    exit /b 1
)

echo.
echo ========================================
echo       Build completed successfully
echo ========================================
echo.
echo Build directory: %BUILD_DIR%

endlocal