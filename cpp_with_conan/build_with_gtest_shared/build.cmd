rmdir build /s /q
mkdir build

@REM install thirdparties with conan
@REM    --build=missing     <<<===>>>  if binaries not exists, conan will download sources and build locally
@REM    -if build           <<<===>>>  conan install directory, gtest.dll will be installed to `build/bin`,
@REM                                   `build/bin` is defined in conanfile.txt [imports]
conan install . -if build --build=missing

@REM configure CMake projects
@REM    -DCMAKE_TOOLCHAIN_FILE=build/conan_paths.cmake  <<<===>>>  cmake paths to include conan packages, defined in conanfile.txt [generators]
@REM    -DCMAKE_INSTALL_PREFIX=build                    <<<===>>>  add install prefix for `cmake --install` command,
@REM                                                               so that demo will be installed to `build/bin`,
@REM                                                               when demo.exe executed, gtest.dll will be searched in demo.exe dir, then PATH
cmake -DCMAKE_TOOLCHAIN_FILE=build/conan_paths.cmake -DCMAKE_INSTALL_PREFIX=build -S . -B build

@REM build executable target
cmake --build build --config Release

@REM install executable target to where CMAKE_INSTALL_PREFIX defined
cmake --install build --config Release
