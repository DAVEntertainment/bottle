from conans import ConanFile, CMake, tools
from functools import lru_cache
from os.path import join as joinpath


class HelloConan(ConanFile):
    name = "add"
    version = "1.1.0"
    description = """\"add\" library"""
    settings = "os", "arch", "compiler", "build_type"
    url = "https://github.com/DAVEntertainment/simple_cpp.git"
    generators = "CMakeDeps", "CMakeToolchain"

    def source(self):
        print("@@@ start source phase")
        print("@@@ conan_data: {}".format(self.conan_data))
        print("@@@ version: {}".format(self.version))
        # self.conan_data, loaded from conandata.yml
        tools.get(**self.conan_data["sources"][self.version], strip_root = True)

    @lru_cache(1)
    def _configure(self):
        print("@@@ configuring cmake")
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure()
        print("@@@ start build")
        cmake.build()

    def package(self):
        cmake = self._configure()
        print("@@@ start install")
        cmake.install()
        tools.rmdir(joinpath(self.package_folder, "lib", "cmake"))
        tools.remove_files_by_mask(joinpath(self.package_folder, "lib"), "*.pdb")

    def package_info(self):
        self.cpp_info.libs = ["add"]
        self.cpp_info.set_property("cmake_target_name", "Add::add")
