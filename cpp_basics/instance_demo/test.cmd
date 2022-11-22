@set SOURCE_DIR=%~dp0
@set BUILD_DIR=%SOURCE_DIR%\.build

@echo #############################################################
@echo # SOURCE_DIR = %SOURCE_DIR%
@echo # BUILD_DIR  = %BUILD_DIR%
@echo #############################################################

rmdir %BUILD_DIR% /s /q

@REM configure CMake projects
cmake -DCMAKE_INSTALL_PREFIX=%BUILD_DIR% -S . -B %BUILD_DIR%

@REM build executable target
cmake --build %BUILD_DIR% --config Release

@REM install executable target to where CMAKE_INSTALL_PREFIX defined
cmake --install %BUILD_DIR% --config Release

@REM run demo
%BUILD_DIR%\bin\demo.exe
