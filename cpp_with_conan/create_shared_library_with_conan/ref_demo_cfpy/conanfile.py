from conans import ConanFile


class RefDemo(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = "add/1.0.0@demo/testing"        # [requires]
   generators = "CMakeDeps", "CMakeToolchain" # [generators]

   def imports(self): # [imports]
      self.copy("*.dll", dst="bin", src="bin") # From bin to bin

########################################################################
# Same as conanfile.txt below
########################################################################
# [requires]
# add/1.0.0@demo/testing
# 
# [generators]
# CMakeDeps
# CMakeToolchain
# 
# [options]
# 
# [imports]
# bin, *.dll -> ./bin
