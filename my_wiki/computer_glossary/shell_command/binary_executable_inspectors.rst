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
        -v        --version                 Display the program's version
   
      size: supported targets: elf64-x86-64 elf32-i386 elf32-x86-64 a.out-i386-linux pei-i386 pei-x86-64 elf64-l1om elf64-k1om elf64-little elf64-big elf32-little elf32-big pe-x86-64 pe-i386 plugin srec symbolsrec verilog tekhex binary ihex

      $ size /bin/ls /usr/bin/cc
      text     data      bss      dec      hex  filename
      105182     2044     3424   110650    1b03a  /bin/ls
      761967     8160    81056   851183    cfcef  /usr/bin/cc
   
#. file — determine file type
   
   .. code-block:: sh

      $ file a.out 
      a.out: ELF 64-bit LSB  executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=221dd2443eaa05493fc2d2861c09551676ba60dc, not stripped
      $ file test.c
      test.c: C source, ASCII text

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
      __libc_start_main(0x400c40, 1, 0x7fff8a80f9a8, 0x4010f0 <unfinished ...>
      setlocale(LC_ALL, "")                                                                                                                                                  = "en_US.UTF-8"
      bindtextdomain("procps-ng", "/usr/share/locale")                                                                                                                       = "/usr/share/locale"
      textdomain("procps-ng")                                                                                                                                                = "procps-ng"
      __cxa_atexit(0x401080, 0, 0, 0x676e2d7370636f)                                                                                                                         = 0
      getopt_long(1, 0x7fff8a80f9a8, "phsV", 0x401340, nil)                                                                                                                  = -1
      print_uptime(0, 0x401224, 0x7f6c978be280, 0 20:12:36 up 5 days, 21:05,  3 users,  load average: 0.00, 0.01, 0.05
      )                                                                                                                           = 70
      __fpending(0x7f6c978bf400, 0, 64, 0x7f6c978bfeb0)                                                                                                                      = 0
      ferror(0x7f6c978bf400)                                                                                                                                                 = 0
      fclose(0x7f6c978bf400)                                                                                                                                                 = 0
      __fpending(0x7f6c978bf1c0, 0, 0, 0xfbad000c)                                                                                                                           = 0
      ferror(0x7f6c978bf1c0)                                                                                                                                                 = 0
      fclose(0x7f6c978bf1c0)                                                                                                                                                 = 0
      +++ exited (status 0) +++
