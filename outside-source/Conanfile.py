import conans
from conans.client import b2


class SuperLib(conans.ConanFile):
    name = "super-lib"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    exports = "super-lib/*"

    def build(self):
        bb = b2.BoostBuild(self.settings)
        self.run('cd super-lib && b2 %s' % bb.command_line)

    def package(self):
        self.copy("*.h", dst="include", src="hello")
        self.copy("*.lib", dst="lib", src="hello/lib")
        self.copy("*.a", dst="lib", src="hello/lib")

    def package_info(self):
        self.cpp_info.libs = ["hello"]
