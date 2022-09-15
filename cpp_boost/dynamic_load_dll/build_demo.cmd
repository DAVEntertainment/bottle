call library\build_shared.cmd

set SOURCE_DIR=%~dp0
set BUILD_DIR=%SOURCE_DIR%.build

rmdir /s /q %BUILD_DIR%

mkdir %BUILD_DIR%
cmake -S %SOURCE_DIR% -B %BUILD_DIR%
cmake --build %BUILD_DIR% --config Debug
%BUILD_DIR%\Debug\lib_ref_demo.exe
cmake --build %BUILD_DIR% --config Release
%BUILD_DIR%\Release\lib_ref_demo.exe
