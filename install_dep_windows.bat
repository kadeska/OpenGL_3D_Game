@echo on
setlocal enabledelayedexpansion

echo Checking for required dependencies...
set "VCPKG_DIR=C:\vcpkg"

:: Check if vcpkg exists
if not exist "%VCPKG_DIR%\vcpkg.exe" (
    echo vcpkg not found! Installing vcpkg...
    git clone https://github.com/microsoft/vcpkg.git "%VCPKG_DIR%"
    cd "%VCPKG_DIR%"
    .\bootstrap-vcpkg.bat
    cd ..
)

:: Check and install dependencies (including assimp)
for %%L in (glfw3 glew boost assimp) do (
    "%VCPKG_DIR%\vcpkg.exe" list | findstr /C:"%%L" > nul
    if errorlevel 1 (
        echo Installing %%L...
        "%VCPKG_DIR%\vcpkg.exe" install %%L:x64-windows
    ) else (
        echo %%L is already installed.
    )
)

echo All dependencies are installed.
pause
