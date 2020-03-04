**********************
Ubuntu problem note 03
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

#. Ubuntu link error: fatal error: xxxxx: Input/output error

    This problem is due to the fact that the code project resides in virtual machine's shared folder,
    moving the project to ``/home/$USER`` can solve it.
