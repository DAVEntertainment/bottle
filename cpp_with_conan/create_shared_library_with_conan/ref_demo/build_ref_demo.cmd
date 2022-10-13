set SOURCE_DIR=%~dp0

@REM Better to build debug and release in separate folder, or they will affect each otehr
set BUILD_DIR=%SOURCE_DIR%\.build_release
rmdir /s /q %BUILD_DIR%
conan install %SOURCE_DIR% -if %BUILD_DIR% --build=missing --profile:build %SOURCE_DIR%\conanprofile.txt --profile:host %SOURCE_DIR%\conanprofile.txt -s build_type=Release
cmake -S %SOURCE_DIR% -B %BUILD_DIR% -DCMAKE_TOOLCHAIN_FILE=%BUILD_DIR%\conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=%BUILD_DIR%
cmake --build %BUILD_DIR% --config Release
cmake --install %BUILD_DIR% --config Release
call %BUILD_DIR%\bin\lib_ref_demo.exe


set BUILD_DIR=%SOURCE_DIR%\.build_debug
rmdir /s /q %BUILD_DIR%
conan install %SOURCE_DIR% -if %BUILD_DIR% --build=missing --profile:build %SOURCE_DIR%\conanprofile.txt --profile:host %SOURCE_DIR%\conanprofile.txt -s build_type=Debug
cmake -S %SOURCE_DIR% -B %BUILD_DIR% -DCMAKE_TOOLCHAIN_FILE=%BUILD_DIR%\conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=%BUILD_DIR%
cmake --build %BUILD_DIR% --config Debug
cmake --install %BUILD_DIR% --config Debug
call %BUILD_DIR%\bin\lib_ref_demo.exe
