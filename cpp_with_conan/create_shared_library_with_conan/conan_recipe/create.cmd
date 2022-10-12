set SOURCE_DIR=%~dp0

conan create --profile %SOURCE_DIR%\conanprofile.txt %SOURCE_DIR%/all/conanfile.py add/1.1.0@demo/testing
