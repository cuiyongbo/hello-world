**********************
Ubuntu problem note 02
**********************

#. Check glibc version

    .. code-block:: sh
        :caption: Solution one

        $ ldd --version
        ldd (Ubuntu GLIBC 2.27-3ubuntu1) 2.27

    .. code-block:: sh
        :caption: Solution two

        $ cat test.c
        #include <stdio.h>
        #include <gnu/libc-version.h>
        int main (void) { puts (gnu_get_libc_version ()); return 0; }

        $ gcc test.c; ./a.out
        2.27
