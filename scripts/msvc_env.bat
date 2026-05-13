@echo off
setlocal

if defined VSCMD_VER (
    endlocal & exit /b 0
)

if defined VS_VCVARS64 (
    if exist "%VS_VCVARS64%" (
        endlocal & call "%VS_VCVARS64%"
        exit /b %ERRORLEVEL%
    )
    echo ERROR: VS_VCVARS64 points to a missing file: %VS_VCVARS64%
    endlocal & exit /b 1
)

set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo ERROR: vswhere.exe was not found. Install Visual Studio 2022 Build Tools or set VS_VCVARS64.
    endlocal & exit /b 1
)

for /f "usebackq tokens=* delims=" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
    set "VS_INSTALL=%%i"
)

if not defined VS_INSTALL (
    echo ERROR: Visual Studio C++ x64 tools were not found.
    endlocal & exit /b 1
)

set "VCVARS=%VS_INSTALL%\VC\Auxiliary\Build\vcvars64.bat"
if not exist "%VCVARS%" (
    echo ERROR: vcvars64.bat was not found at: %VCVARS%
    endlocal & exit /b 1
)

endlocal & call "%VCVARS%"
exit /b %ERRORLEVEL%

