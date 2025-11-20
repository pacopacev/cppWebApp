# build.ps1
$cmakePath = "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
$vcpkgToolchain = "D:/vcpkg/scripts/buildsystems/vcpkg.cmake"

Write-Host "=== Wt C++ Web Application Build ===" -ForegroundColor Green
Write-Host "Project directory: $(Get-Location)" -ForegroundColor Yellow

# Clean previous build
if (Test-Path "build") {
    Write-Host "Cleaning previous build..." -ForegroundColor Yellow
    Remove-Item -Recurse -Force build
}

# Configure CMake
Write-Host "`nConfiguring CMake..." -ForegroundColor Green
& $cmakePath -B build -S . -DCMAKE_TOOLCHAIN_FILE=$vcpkgToolchain -G "Visual Studio 17 2022" -A x64

if ($LASTEXITCODE -ne 0) {
    Write-Host "CMake configuration failed!" -ForegroundColor Red
    Write-Host "Check your CMakeLists.txt and vcpkg installation" -ForegroundColor Yellow
    pause
    exit 1
}

# Build project
Write-Host "`nBuilding project..." -ForegroundColor Green
& $cmakePath --build build --config Release

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed!" -ForegroundColor Red
    pause
    exit 1
}

Write-Host "`nBuild successful!" -ForegroundColor Green

# Check if executable was created
if (Test-Path "build\Release\my-wt-app.exe") {
    Write-Host "`nExecutable created: build\Release\my-wt-app.exe" -ForegroundColor Cyan
    Write-Host "`nTo run your application:" -ForegroundColor Yellow
    Write-Host "  .\build\Release\my-wt-app.exe --docroot . --http-address 0.0.0.0 --http-port 8080" -ForegroundColor White
    Write-Host "`nThen open: http://localhost:8080" -ForegroundColor Cyan
    
    $run = Read-Host "`nRun the application now? (y/n)"
    if ($run -eq 'y' -or $run -eq 'Y') {
        Write-Host "`nStarting Wt application..." -ForegroundColor Green
        Write-Host "Press Ctrl+C to stop the server" -ForegroundColor Yellow
        & "build\Release\my-wt-app.exe" --docroot . --http-address 0.0.0.0 --http-port 8080
    }
} else {
    Write-Host "Executable not found! Build may have issues." -ForegroundColor Red
    Write-Host "Available files in build directory:" -ForegroundColor Yellow
    if (Test-Path "build") {
        Get-ChildItem "build" -Recurse
    }
}

pause