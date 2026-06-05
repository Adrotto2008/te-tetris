@echo off
setlocal EnableExtensions EnableDelayedExpansion
REM Script per compilare il cmake e avviare il gioco se ha successo

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
echo Compilazione in corso...
cmake --build .

if %errorlevel% equ 0 (
    echo Compilazione completata con successo!
    echo Avvio del gioco...
    cd ../bin
    call avvio.cmd
) else (
    echo Errore durante la compilazione!
    pause
)

