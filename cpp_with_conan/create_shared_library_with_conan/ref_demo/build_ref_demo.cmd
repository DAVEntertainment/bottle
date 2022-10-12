set SOURCE_DIR=%~dp0
set BUILD_DIR=%SOURCE_DIR%\.build

rmdir /s /q %BUILD_DIR%

conan install %SOURCE_DIR% -if %BUILD_DIR% --build=missing --profile %SOURCE_DIR%\conanprofile.txt -s build_type=Release
cmake -S %SOURCE_DIR% -B %BUILD_DIR% -DCMAKE_TOOLCHAIN_FILE=%BUILD_DIR%\conan_toolchain.cmake
@REM cmake --build %BUILD_DIR% --config Release
@REM @REM %BUILD_DIR%\Release\lib_ref_demo.exe

@REM conan install %SOURCE_DIR% -if %BUILD_DIR% --build --profile %SOURCE_DIR%\conanprofile.txt -s build_type=Debug
@REM cmake -S %SOURCE_DIR% -B %BUILD_DIR% -DCMAKE_TOOLCHAIN_FILE=%BUILD_DIR%\conan_toolchain.cmake
@REM @REM cmake --build %BUILD_DIR% --config Debug
@REM @REM @REM %BUILD_DIR%\Debug\lib_ref_demo.exe
