set RECIPE_DIR=%~dp0

conan create --profile %RECIPE_DIR%\conanprofile.txt -s build_type=Debug   %RECIPE_DIR%/conanfile.py add/1.0.0@demo/testing
conan create --profile %RECIPE_DIR%\conanprofile.txt -s build_type=Release %RECIPE_DIR%/conanfile.py add/1.0.0@demo/testing
