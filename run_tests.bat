@echo off
REM Test runner script for WiFi RSSI Analyzer (Windows)
REM 
REM Usage:
REM   run_tests.bat              - Run all tests
REM   run_tests.bat verbose      - Run with verbose output
REM   run_tests.bat filter NAME  - Run specific test suite

setlocal enabledelayedexpansion

echo.
echo WiFi RSSI Analyzer - Test Runner
echo ==================================

REM Check if platformio is installed
where pio >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: PlatformIO is not installed
    echo Install it with: pip install platformio
    exit /b 1
)

REM Parse arguments
set VERBOSE=
set FILTER=

if "%1"=="verbose" (
    set VERBOSE=-v
) else if "%1"=="filter" (
    if not "%2"=="" (
        set FILTER=--filter %2
    )
)

REM Run tests
echo.
echo Running tests...
echo.

pio test -e native_test %VERBOSE% %FILTER%

if %errorlevel% equ 0 (
    echo.
    echo ^✓ All tests passed!
    exit /b 0
) else (
    echo.
    echo ^✗ Some tests failed
    exit /b 1
)
