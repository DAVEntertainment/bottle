@REM del /s /f demo.exe
@REM rmdir build /s /q
mkdir build

@REM install thirdparties with conan
conan install . -if build --build=missing

@REM configure CMake projects
@REM we choose cmake paths to include conan packages, so we add -DCMAKE_TOOLCHAIN_FILE=build/conan_paths.cmake
@REM add install prefix -DCMAKE_INSTALL_PREFIX=build
cmake -DCMAKE_TOOLCHAIN_FILE=build/conan_paths.cmake -DCMAKE_INSTALL_PREFIX=build -S . -B build

@REM build executable target
cmake --build build --config Release

@REM install executable target to where CMAKE_INSTALL_PREFIX defined
cmake --install build --config Release

@REM run demo
build\bin\demo.exe
