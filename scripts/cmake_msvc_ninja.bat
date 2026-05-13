@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
call "%SCRIPT_DIR%msvc_env.bat"
if errorlevel 1 (
    exit /b %ERRORLEVEL%
)

if "%~1"=="" (
    echo Usage: scripts\cmake_msvc_ninja.bat ^<configure^|build^|test^|release-configure^|release-build^>
    exit /b 1
)

if /i "%~1"=="configure" (
    cmake --preset debug
    exit /b %ERRORLEVEL%
)

if /i "%~1"=="build" (
    cmake --build --preset debug
    exit /b %ERRORLEVEL%
)

if /i "%~1"=="test" (
    ctest --preset debug
    exit /b %ERRORLEVEL%
)

if /i "%~1"=="release-configure" (
    cmake --preset release
    exit /b %ERRORLEVEL%
)

if /i "%~1"=="release-build" (
    cmake --build --preset release
    exit /b %ERRORLEVEL%
)

echo ERROR: Unknown command: %~1
exit /b 1

