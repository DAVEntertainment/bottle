del /s demo.exe
mkdir .build

@REM configure
cmake -S . -B .build

@REM build
cmake --build .build --config Release

@REM install
cmake --install .build --config Release

@REM run demo
demo.exe
