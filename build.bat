@echo off
echo === Wt C++ Web Application Build ===

set "CMAKE=C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
set "VCPKG_TOOLCHAIN=D:\vcpkg\scripts\buildsystems\vcpkg.cmake"

echo Cleaning previous build...
if exist build rmdir /s /q build

echo Configuring CMake...
"%CMAKE%" -B build -S . -DCMAKE_TOOLCHAIN_FILE=%VCPKG_TOOLCHAIN% -G "Visual Studio 17 2022" -A x64

if %errorlevel% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b %errorlevel%
)

echo Building project...
"%CMAKE%" --build build --config Release

if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b %errorlevel%
)

echo Build successful!
echo Found: build\Release\webapp.exe

echo.
echo To run your application:
echo   build\Release\webapp.exe --docroot . --http-address 0.0.0.0 --http-port 8080
echo.
echo Then open: http://localhost:8080
echo.
set /p run="Run the application now? (y/n): "
if /i "%run%"=="y" (
    echo.
    echo Starting Wt application...
    echo Press Ctrl+C to stop the server
    build\Release\webapp.exe --docroot . --http-address 0.0.0.0 --http-port 8080
)

pause