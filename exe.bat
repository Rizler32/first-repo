@echo off

bin\app

echo Exit code: %errorlevel%
if errorlevel 1 (
    exit /b %errorlevel%
)
