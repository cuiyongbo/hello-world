Gflags Example
==============

.. code-block:: cpp
    :caption: foo.cc

    #include <iostream>
    #include <string>
    #include <stdint.h>

    #include <gflags/gflags.h>

    DEFINE_bool(big_menu, true, "Include 'advanced' options in the menu listing");
    DEFINE_string(languages, "english,french,german",
                    "comma-separated list of languages to offer in the 'lang' menu");

    static bool ValidatePort(const char* flagname, gflags::int32 value) {
        if (value > 0 && value < 32768) {   // value is ok
            return true;
        }
        printf("Invalid value for --%s: %d\n", flagname, (int)value);
        return false;
    }

    DEFINE_int32(port, 0, "which port to listen on");
    DEFINE_validator(port, &ValidatePort);

    using namespace std;

    int main(int argc, char* argv[]) {
        gflags::SetUsageMessage("author cyb");
        gflags::SetVersionString("version 0.0.1");
        int ret = gflags::ParseCommandLineFlags(&argc, &argv, false); 

        for (int i=1; i<argc; ++i) {
            printf("argv[%d]: %s\n", i, argv[i]);
        }

        cout << "the first argument index: " << ret << endl;
        cout << "big_menu: " << FLAGS_big_menu << endl;
        cout << "languages: " << FLAGS_languages << endl;
        cout << "port: " << FLAGS_port << endl;
        
        return 0;
    }

.. code-block:: cpp
    :caption: CMakeLists.txt

    cmake_minimum_required(VERSION 3.17)

    project(FOO)

    find_package(gflags REQUIRED)

    add_executable(foo foo.cc)
    target_link_libraries(foo gflags)