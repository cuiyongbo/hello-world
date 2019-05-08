****************************
Binary executable inspectors
****************************

#. which - locate a command

    .. code-block:: sh

        # which returns the pathnames of the files (or links) which would be executed in the current environment, 
        # had its arguments been given as commands in a strictly POSIX-conformant shell. It does this by searching 
        # the PATH for executable files matching the names of the arguments. It does not follow symbolic links.
        $ which cc
        /usr/bin/cc

#. size

    .. code-block:: sh

        $ size -h
        Usage: size [option(s)] [file(s)]
         Displays the sizes of sections inside binary files
         If no input file(s) are specified, a.out is assumed
         The options are:
          -A|-B     --format={sysv|berkeley}  Select output style (default is berkeley)
          -o|-d|-x  --radix={8|10|16}         Display numbers in octal, decimal or hex
          -t        --totals                  Display the total sizes (Berkeley only)
                    --common                  Display total size for *COM* syms
                    --target=<bfdname>        Set the binary file format
                    @<file>                   Read options from <file>
          -h        --help                    Display this information
   
        $ size /bin/ls /usr/bin/cc
        text     data      bss      dec      hex  filename
        105182     2044     3424   110650    1b03a  /bin/ls
        761967     8160    81056   851183    cfcef  /usr/bin/cc
   
#. file — determine file type
   
    .. code-block:: sh

        $ file a.out 
        a.out: ELF 64-bit LSB  executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), 
        for GNU/Linux 2.6.24, BuildID[sha1]=221dd2443eaa05493fc2d2861c09551676ba60dc, not stripped
        $ file test.c
        test.c: C source, ASCII text

#. ldd - Print shared library dependencies

    .. code-block:: sh

        $ ldd Shadowsocks.exe
        ntdll.dll => /c/WINDOWS/SYSTEM32/ntdll.dll (0x7ffe1ab80000)
        wow64win.dll => /c/WINDOWS/System32/wow64win.dll (0x7ffe18c50000)
        wow64cpu.dll => /c/WINDOWS/System32/wow64cpu.dll (0x77c70000)
        ...

#. strip - remove symbols
   
    .. code-block:: sh

        Usage: strip <option(s)> in-file(s)
         Removes symbols and sections from files
         The options are:
          -I --input-target=<bfdname>      Assume input file is in format <bfdname>
          -O --output-target=<bfdname>     Create an output file in format <bfdname>
          -F --target=<bfdname>            Set both input and output format to <bfdname>
          -p --preserve-dates              Copy modified/access timestamps to the output
          -D --enable-deterministic-archives
                                           Produce deterministic output when stripping archives (default)
          -U --disable-deterministic-archives
                                           Disable -D behavior
          -R --remove-section=<name>       Also remove section <name> from the output
          -s --strip-all                   Remove all symbol and relocation information
          -g -S -d --strip-debug           Remove all debugging symbols & sections
             --strip-dwo                   Remove all DWO sections
             --strip-unneeded              Remove all symbols not needed by relocations
             --only-keep-debug             Strip everything but the debug information
          -N --strip-symbol=<name>         Do not copy symbol <name>
          -K --keep-symbol=<name>          Do not strip symbol <name>
             --keep-file-symbols           Do not strip file symbol(s)
          -w --wildcard                    Permit wildcard in symbol comparison
          -x --discard-all                 Remove all non-global symbols
          -X --discard-locals              Remove any compiler-generated symbols
          -v --verbose                     List all object files modified
          -V --version                     Display this program's version number
          -h --help                        Display this output
             --info                        List object formats & architectures supported
          -o <file>                        Place stripped output into <file>

    .. code-block:: sh

        cherry apue$ gcc -g test.c
        cherry apue$ strip a.out -o a.out.s
        cherry apue$ ll a.out*
        -rwxrwxr-x 1 cherry cherry 8.6K May  9 06:34 a.out*
        -rwxrwxr-x 1 cherry cherry 5.5K May  9 06:34 a.out.s*

#. readelf
   
#. strace and ltrace

    .. code-block:: sh

        #   strace options
        #   -f          
        #   Trace child processes as they are created by currently traced processes 
        #   as a result of the fork(2), vfork(2) and clone(2) system calls. 
        #   Note that -p PID -f will attach all threads of process PID if 
        #   it is multi-threaded, not only thread with thread_id = PID.
        #   -ff         
        #   If the -o filename option is in effect, each processes trace is written to filename.pid 
        #   where pid is the numeric process id of each process.

        $ ltrace uptime
    
#. peek fuction list in a ``*.so`` object
   
    .. code-block:: sh

        $ nm -D  libfcgi.so | grep FCG
        0000000000005bf0 T FCGI_Accept
        0000000000006520 T FCGI_clearerr
        0000000000005db0 T FCGI_fclose
        00000000000065c0 T FCGI_fdopen
        00000000000064c0 T FCGI_feof
        ...

#. type - view alias information
   
    .. code-block:: sh
    
        $ type ll
        ll is aliased to `ls -hlGF'