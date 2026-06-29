from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout, CMakeDeps
from conan.tools.build import check_min_cppstd

class packageRecipt(ConanFile):
    name = "ccwc"
    version = "0.1"
    license = "MIT"
    author = "Riko111"
    description = "Coding Challenge: Word Count"
    topics = ("coding-challenges", "word-count")

    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [False]}
    default_options = {"shared": False}
    generators = "CMakeToolchain", "CMakeDeps"
    export_sources = "CMakeLists.txt", "main.cpp", "include/*", "src/*", "test/*"

    def validate(self):
        check_min_cppstd(self, 17)
    
    def requirements(self):
        if not self.conf.get("tools.build:skip_test", default=False):
            self.requires("gtest/1.16.0")
    
    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure(variables={"PACKAGE_NAME": self.name, "CMAKE_EXPORT_COMPILE_COMMANDS": "ON"})
        cmake.build()
        if not self.conf.get("tools.build:skip_test", default=False):
            cmake.ctest(cli_args=["--test-dir test"])
    
    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = [self.name]
