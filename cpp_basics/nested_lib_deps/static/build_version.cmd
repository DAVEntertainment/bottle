set VERSION=%1
set SOURCE_DIR=%~dp0
set BUILD_DIR=%SOURCE_DIR%\.build_v%VERSION%
set INSTALL_DIR=%SOURCE_DIR%\.install_v%VERSION%

rmdir /s /q %BUILD_DIR%
rmdir /s /q %INSTALL_DIR%

mkdir %BUILD_DIR%
cmake -S %SOURCE_DIR% -B %BUILD_DIR% -DCMAKE_INSTALL_PREFIX=%INSTALL_DIR% -DVERSION=%VERSION%
cmake --build %BUILD_DIR% --config Debug
cmake --install %BUILD_DIR% --config Debug
cmake --build %BUILD_DIR% --config Release
cmake --install %BUILD_DIR% --config Release
