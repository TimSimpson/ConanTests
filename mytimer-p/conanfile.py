import conans
import os
import os.path

class MyProjectWithConan(conans.ConanFile):
    settings = ["os", "compiler", "build_type", "arch"]
    requires = (
        "Poco/1.6.1@lasote/stable",
        "OpenSSL/1.0.2d@lasote/stable"
    )
    generators = (
        "cmake",
        "gcc",
        "txt"
    )
    default_options = (
        "Poco:poco_static=False",
        "OpenSSL:shared=False"
    )

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin

    def build(self):
        cmake = conans.CMake(self.settings)
        if not os.path.exists("build"):
            os.makedirs("build")
        # cmake.command_line = -G "Visual Studio 14 Win64" -DCONAN_LINK_RUNTIME=/MD -DCONAN_COMPILER="Visual Studio" -DCONAN_COMPILER_VERSION="14" -Wno-dev
        self.run('cd build && cmake .. %s' % cmake.command_line)
        self.run('cd build && cmake --build . %s' % cmake.build_config)
