Run with:

    conan install
    conan build

If dependencies fail you may need to run:

    conan install --build

Which forces all dependencies to be built. Run this until it passes- for OpenSSL you might need to run the vcvars script included with Visual Studio to make NMake available on the path.

TO install the debug version:

    conan install -s build_type=Debug -s arch=x86_64
    conan build

After that, conan will remember the settings(?).

