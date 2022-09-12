call static\build.cmd
call static\build.cmd
call shared_a\build.cmd
call shared_b\build.cmd


set SOURCE_DIR=%~dp0
set BUILD_DIR=%SOURCE_DIR%.build

rmdir /s /q %BUILD_DIR%

mkdir %BUILD_DIR%
cmake -S %SOURCE_DIR% -B %BUILD_DIR% -DBoost_DEBUG=1
cmake --build %BUILD_DIR% --config Debug
%BUILD_DIR%\Debug\lib_ref_demo.exe
cmake --build %BUILD_DIR% --config Release
%BUILD_DIR%\Release\lib_ref_demo.exe
