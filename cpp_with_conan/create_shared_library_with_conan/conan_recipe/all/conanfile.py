from conans import ConanFile, CMake, tools
from conan.tools.files import update_conandata
from functools import lru_cache
from os.path import join as joinpath
from os.path import split as splitpath
from os.path import basename, dirname, abspath
from os import getcwd, environ
from sys import argv
from shutil import copy, rmtree, copytree


class HelloConan(ConanFile):
    name = "add"
    version = "1.1.0"
    description = """\"add\" library"""
    settings = "os", "arch", "compiler", "build_type"
    url = "https://github.com/DAVEntertainment/simple_cpp.git"
    generators = "CMakeDeps", "CMakeToolchain"
    settings = "os", "arch", "compiler", "build_type"

    def export(self):
        source_dir = joinpath(dirname(__file__), '..', self.name)

        update_conandata(self, {
            "source_origin": abspath(source_dir),
            "__file__ in export": __file__
        })

    def source(self):
        source_origin = self.conan_data["source_origin"]
        source_dir = abspath(joinpath(getcwd(), basename(source_origin)))

        print("@@@ start source phase")
        print("@@@ working in: {}".format(getcwd()))
        print("@@@ conan_data: {}".format(self.conan_data))
        print("@@@ version: {}".format(self.version))
        print("@@@ source_origin: {}".format(source_origin))
        print("@@@ source_dir: {}".format(source_dir))

        copytree(source_origin, source_dir)

    @lru_cache(1)
    def _configure(self):
        print("@@@ configuring cmake")
        print("@@@ working in: {}".format(getcwd()))
        cmake = CMake(self)
        cmake.configure(source_folder=self.name) # we use copytree copy src files into a folder, so we need to specify source folder here
        return cmake

    def build(self):
        cmake = self._configure()
        print("@@@ start build")
        print("@@@ working in: {}".format(getcwd()))
        cmake.build()

    def package(self):
        cmake = self._configure()
        print("@@@ start install")
        print("@@@ working in: {}".format(getcwd()))
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["add"]
        self.cpp_info.set_property("cmake_target_name", "Add::add")
