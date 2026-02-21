@echo off
echo.
echo =============================================
echo   File Search Utility - Build Script
echo =============================================
echo.

gcc --version >nul 2>&1
IF %ERRORLEVEL% NEQ 0 (
    echo [ERROR] GCC pawa jacche na!
    echo Please install MinGW from: https://winlibs.com
    pause
    exit /b 1
)

echo [1/3] Folder check korchi...
IF NOT EXIST bin mkdir bin
IF NOT EXIST build mkdir build

echo [2/3] Compile korchi...
gcc src\main.c src\search.c src\utils.c src\gui.c ^
    -Iinclude ^
    -mwindows ^
    -lcomctl32 -lole32 -lshell32 ^
    -o bin\FileSearch.exe

IF %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] Compile hoy ni!
    pause
    exit /b 1
)

echo [3/3] Success!
echo.
echo =============================================
echo   FileSearch.exe ready  -  bin\ folder e
echo =============================================
echo.
echo Run korte: bin\FileSearch.exe double-click korun
echo.
pause
