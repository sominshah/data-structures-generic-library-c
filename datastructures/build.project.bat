@echo off
setlocal

:: -- 1. Create & enter the build directory
if not exist build (
    mkdir build
)
cd build

:: -- 3. Run CMake to generate MinGW Makefiles. Chane the below line with this in case of debug - [cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..]


cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
if errorlevel 1 (
    echo ERROR: CMake configuration failed
    exit /b 1
)




:: -- 4. Build everything
mingw32-make -j%NUMBER_OF_PROCESSORS%
if errorlevel 1 (
    echo ERROR: Build failed
    exit /b 1
)

echo SUCCESS: Build succeeded
endlocal
exit /b 0
