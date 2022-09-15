call static\build.cmd
call shared_a\build.cmd
call shared_b\build.cmd

set SOURCE_DIR=%~dp0
set BUILD_DIR=%SOURCE_DIR%.build

rmdir /s /q %BUILD_DIR%

mkdir %BUILD_DIR%
cmake -S %SOURCE_DIR% -B %BUILD_DIR%
cmake --build %BUILD_DIR% --config Debug
%BUILD_DIR%\Debug\nested_lib_deps.exe
cmake --build %BUILD_DIR% --config Release
%BUILD_DIR%\Release\nested_lib_deps.exe
