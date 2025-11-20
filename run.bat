@echo off
chcp 65001 > nul
echo Starting Wt application...
echo Access CSS at: http://localhost:8080/style/style.css
echo.
cd build
Release\webapp.exe --docroot "D:\cppWebApp" --http-address 0.0.0.0 --http-port 8080
pause