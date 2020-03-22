Libtbb FAQ
==========

#. Build tbb as a static library

    .. code-block:: sh

        $ make extra_inc=big_iron.inc

        $ find build/ -name "*.a"
        build/linux_intel64_gcc_cc4.8_libc2.19_kernel3.13.0_release/libtbbmalloc.a
        build/linux_intel64_gcc_cc4.8_libc2.19_kernel3.13.0_release/libtbb.a

        $ cp build/linux_intel64_gcc_cc4.8_libc2.19_kernel3.13.0_release/*.a lib/

        $ ll -h lib/
        total 5.9M
        drwxrwxr-x  2 cuiyb cuiyb 4.0K Mar 30 15:32 ./
        drwxrwxr-x 11 cuiyb cuiyb 4.0K Mar 30 15:31 ../
        -rw-rw-r--  1 cuiyb cuiyb 4.5M Mar 30 15:54 libtbb.a
        -rw-rw-r--  1 cuiyb cuiyb 1.4M Mar 30 15:54 libtbbmalloc.a
