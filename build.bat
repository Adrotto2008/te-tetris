@echo off
setlocal EnableExtensions EnableDelayedExpansion
REM Script per eseguire la build del progetto

cd cmake-build-debug

REM Aggiunge la cartella del compilatore (da CMakeCache) al PATH per i DLL MinGW
if exist CMakeCache.txt (
    for /f "tokens=2 delims==" %%A in ('findstr /r /c:"^CMAKE_CXX_COMPILER:FILEPATH=" CMakeCache.txt') do (
        set "CXX_COMPILER=%%A"
        set "CXX_COMPILER=!CXX_COMPILER:/=\!"
        for %%B in ("!CXX_COMPILER!") do set "COMPILER_DIR=%%~dpB"
    )
    if defined COMPILER_DIR set "PATH=!COMPILER_DIR!;%PATH%"
)
cmake --build .

if %errorlevel% equ 0 (
    echo Build completata con successo!
) else (
    echo Errore durante la build!
)
pause

