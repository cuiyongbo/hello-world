*******************
Backtrace Utilities
*******************

**NAME**
      
   backtrace, backtrace_symbols, backtrace_symbols_fd - support for application self-debugging

**SYNOPSIS**

    .. code-block:: c 

        #include <execinfo.h>
        int backtrace(void **buffer, int size);
        char **backtrace_symbols(void *const *buffer, int size);
        void backtrace_symbols_fd(void *const *buffer, int size, int fd);

**DESCRIPTION**

    ``backtrace()`` returns a backtrace for the calling program, in the array pointed to by *buffer*. A backtrace
    is the series of currently active function calls for the program. Each item in the array pointed to by *buffer*
    is of type ``void*``, and is the return address from the corresponding stack frame. The *size* argument specifies
    the maximum number of addresses that can be stored in buffer. If the backtrace is larger than *size*, then the
    addresses corresponding to the *size* most recent function calls are returned; to obtain the complete backtrace,
    make sure that *buffer* and *size* are large enough.

    Given the set of addresses returned by ``backtrace()`` in *buffer*, ``backtrace_symbols()`` translates the addresses
    into an array of strings that describe the addresses symbolically.  The *size* argument specifies the number of addresses
    in *buffer*. **The symbolic representation of each address consists of the function name (if this can be determined), a
    hexadecimal offset into the function, and the actual return address (in hexadecimal).** The address of the array of string
    pointers is returned as the function result of ``backtrace_symbols()``. This array is malloc(3)ed by ``backtrace_symbols()``,
    and **MUST** be freed by the caller. (The strings pointed to by the array of pointers **NEED NOT and SHOULD NOT** be freed.)

    ``backtrace_symbols_fd()`` takes the same *buffer* and *size* arguments as ``backtrace_symbols()``, but instead of returning
    an array of strings to the caller, it writes the strings, one per line, to the file descriptor fd. ``backtrace_symbols_fd()``
    does not call :manpage:`malloc(3)`, and so can be employed in situations where the latter function might fail.

**RETURN VALUE**

    ``backtrace()`` returns the *number* of addresses returned in *buffer*, which is not greater than *size*.
    If the return value is less than *size*, then the full backtrace was stored; if it is equal to *size*,
    then it may have been truncated, in which case the addresses of the oldest stack frames are not returned.

    On success, ``backtrace_symbols()`` returns a pointer to the array malloc(3)ed by the call; on error,
    ``NULL`` is returned.

**EXAMPLE**

    The program below demonstrates the use of ``backtrace()`` and ``backtrace_symbols()``.
    The following shell session shows what we might see when running the program::

        $ gcc -rdynamic -g -o prog backtrace_demo.c
        $ ./prog 4
        backtrace() returned 9 address(es).
        Frame 0: ./prog(myFunc3+0x93) [0x400a30]
        Frame 1: ./prog() [0x400ad8]
        Frame 2: ./prog(myFunc1+0x25) [0x400aff]
        Frame 3: ./prog(myFunc1+0x1e) [0x400af8]
        Frame 4: ./prog(myFunc1+0x1e) [0x400af8]
        Frame 5: ./prog(myFunc1+0x1e) [0x400af8]
        Frame 6: ./prog(main+0x52) [0x400b53]
        Frame 7: /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf5) [0x7f4edaa20f45]
        Frame 8: ./prog() [0x4008d9]

        $ addr2line 0x4008d5
        /home/cherry/program-demo/cpp-demo/backtrace_demo.c:43

    Program source::

        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include <execinfo.h>
      
        void myFunc3(void)
        {
            const int bufferSize = 100;
            void* buffer[bufferSize];
            int nptrs = backtrace(buffer, bufferSize);
            printf("backtrace() returned %d address(es).\n", nptrs);
            
            /*
            The call backtrace_symbols_fd(buffer, nptrs, fileno(stdout))
            would produce similar oupput to the following:
            */
        
            char** strings = backtrace_symbols(buffer, nptrs);
            if(strings == NULL) {
                perror("backtrace_symbols");
                exit(EXIT_FAILURE);
            }
        
            int j;
            for(j=0; j<nptrs; j++)
                printf("Frame %d: %s\n", j, strings[j]);
        
            free(strings);
        }
      
        /* static means don't export the symbol... */
        static void myFunc2(void)
        {
            myFunc3();
        }
        
        void myFunc1(int ncalls)
        {
            if(ncalls > 1)
                myFunc1(ncalls-1);
            else
                myFunc2();
        }
        
        int main(int argc, char* argv[])
        {
            if(argc != 2) {
                printf("Usage: %s num-Calls\n", argv[0]);
                exit(EXIT_FAILURE);
            }

            myFunc1(atoi(argv[1]));
            exit(EXIT_SUCCESS);
        }
