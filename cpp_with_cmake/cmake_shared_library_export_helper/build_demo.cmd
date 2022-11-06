call %~dp0\library\build_shared.cmd

set SOURCE_DIR=%~dp0
set BUILD_DIR=%SOURCE_DIR%.build
set INSTALL_DIR=%SOURCE_DIR%.install

rmdir /s /q %BUILD_DIR%
rmdir /s /q %INSTALL_DIR%

cmake -S %SOURCE_DIR% -B %BUILD_DIR% -DCMAKE_INSTALL_PREFIX=%INSTALL_DIR%
cmake --build %BUILD_DIR% --config Debug
cmake --install %BUILD_DIR% --config Debug
%INSTALL_DIR%\bin\lib_ref_demo.exe
cmake --build %BUILD_DIR% --config Release
cmake --install %BUILD_DIR% --config Release
%INSTALL_DIR%\bin\lib_ref_demo.exe
