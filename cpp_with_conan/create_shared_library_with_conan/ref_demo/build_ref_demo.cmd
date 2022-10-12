set SOURCE_DIR=%~dp0
set BUILD_DIR=%SOURCE_DIR%\.build

rmdir /s /q %BUILD_DIR%

mkdir %BUILD_DIR%

conan install %SOURCE_DIR% -if %BUILD_DIR% --build=outdated -s build_type=Release
cmake -S %SOURCE_DIR% -B %BUILD_DIR% -DCMAKE_TOOLCHAIN_FILE=%BUILD_DIR%\conan_toolchain.cmake
cmake --build %BUILD_DIR% --config Release
@REM %BUILD_DIR%\Release\lib_ref_demo.exe

@REM conan install %SOURCE_DIR% -if %BUILD_DIR% --build=outdated -s build_type=Debug
@REM cmake -S %SOURCE_DIR% -B %BUILD_DIR% -DCMAKE_TOOLCHAIN_FILE=%BUILD_DIR%\conan_toolchain.cmake
@REM cmake --build %BUILD_DIR% --config Debug
@REM @REM %BUILD_DIR%\Debug\lib_ref_demo.exe