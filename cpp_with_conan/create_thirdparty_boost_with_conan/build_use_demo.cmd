set SOURCE_DIR=%~dp0use_boost_cache_demo
set BUILD_DIR=%SOURCE_DIR%\build
set INSTALL_DIR=%SOURCE_DIR%\install

rmdir %BUILD_DIR% /s /q
rmdir %INSTALL_DIR% /s /q
mkdir %BUILD_DIR%

@REM install thirdparties with conan
conan install %SOURCE_DIR% -if %BUILD_DIR% --build=missing

@REM configure CMake projects
@REM we choose cmake paths to include conan packages, so we add -DCMAKE_TOOLCHAIN_FILE=build/conan_paths.cmake
@REM add install prefix -DCMAKE_INSTALL_PREFIX=build
cmake -DCMAKE_TOOLCHAIN_FILE=%BUILD_DIR%\conan_paths.cmake -DCMAKE_INSTALL_PREFIX=%INSTALL_DIR% -S %SOURCE_DIR% -B %BUILD_DIR%

@REM build executable target
cmake --build %BUILD_DIR% --config Release

@REM install executable target to where CMAKE_INSTALL_PREFIX defined
cmake --install %BUILD_DIR% --config Release

@REM run demo
%BUILD_DIR%\Release\demo.exe
