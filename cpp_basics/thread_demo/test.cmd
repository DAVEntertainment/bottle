del /s test_thread0.exe
del /s test_thread1.exe
@REM rmdir /s /q .build
mkdir .build

@REM configure
cmake -S . -B .build

@REM build
cmake --build .build --config Release

@REM install
cmake --install .build --config Release

@REM run demo
test_thread0.exe
test_thread1.exe
