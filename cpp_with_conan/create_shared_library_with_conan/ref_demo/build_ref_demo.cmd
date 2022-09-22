call library\build_shared.cmd

set SOURCE_DIR=%~dp0
set BUILD_DIR=%SOURCE_DIR%\.build

rmdir /s /q %BUILD_DIR%

mkdir %BUILD_DIR%

conan install %SOURCE_DIR% -if %BUILD_DIR% --build=missing

cmake -S %SOURCE_DIR% -B %BUILD_DIR% -DCMAKE_TOOLCHAIN_FILE=%BUILD_DIR%\conan_paths.cmake
cmake --build %BUILD_DIR% --config Debug
%BUILD_DIR%\Debug\lib_ref_demo.exe
cmake --build %BUILD_DIR% --config Release
%BUILD_DIR%\Release\lib_ref_demo.exe
