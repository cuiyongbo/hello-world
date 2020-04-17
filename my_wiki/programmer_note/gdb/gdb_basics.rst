**********
Gdb Basics
**********

#. Frequently used commands

   Here are some of the most frequently needed GDB commands::

      help [name]
         Show information about GDB command name, or general information about using GDB.

      break [file:]functiop
      Set a breakpoint at function (in file).

      run [arglist]
      Start your program (with arglist, if specified).

      c   Continue running your program (after stopping, e.g. at a breakpoint).

      bt  Backtrace: display the program stack.

      print expr
      Display the value of an expression.

      edit [file:]function
         look at the program line where it is presently stopped.

      list [file:]function
         type the text of the program in the vicinity of where it is presently stopped.

      next
         Execute next program line (after stopping); step over any function calls in the line.

      step
         Execute next program line (after stopping); step into any function calls in the line.

      quit
         Exit from GDB.


#. breakpoint howto

   +---------------------+--------------------------------------------------------------+
   | Command             | Description                                                  |
   +=====================+==============================================================+
   | b file.c: N         | Set a breakpoint at line number N of file “file.c”           |
   +---------------------+--------------------------------------------------------------+
   | b file.c: funcname  | Set a breakpoint at funcname of file “file.c”                |
   +---------------------+--------------------------------------------------------------+
   | b class\:\:function | Set a breakpoint at class\:\:function                        |
   +---------------------+--------------------------------------------------------------+
   | b N if condition    | Set a conditional breakpoint at line N of the current file   |
   +---------------------+--------------------------------------------------------------+
   | info break          | List all breakpoints                                         |
   +---------------------+--------------------------------------------------------------+
   | enable/disable N    | Enable or disable breakpoint number N                        |
   +---------------------+--------------------------------------------------------------+
   | enable N once       | Enable given breakpoint once, and disable it after it is hit |
   +---------------------+--------------------------------------------------------------+
   | delete              | delete all breakpoints, watchpoints or catchpoints           |
   +---------------------+--------------------------------------------------------------+
   | d N                 | Remove breakpoint number N                                   |
   +---------------------+--------------------------------------------------------------+

#. Other commands

   +------------------+----------------------------------------------------------------------+
   | Command          | Description                                                          |
   +==================+======================================================================+
   | info threads     | Display information about current thread                             |
   +------------------+----------------------------------------------------------------------+
   | info watchpoints | Display list of watchpoints                                          |
   +------------------+----------------------------------------------------------------------+
   | info register    | Display processor register content                                   |
   +------------------+----------------------------------------------------------------------+
   | finish           | Runs untill the current function is finished                         |
   +------------------+----------------------------------------------------------------------+
   | step N           | Runs the next N lines of program                                     |
   +------------------+----------------------------------------------------------------------+
   | set var=val      | Assign “val” to the variable “var”                                   |
   +------------------+----------------------------------------------------------------------+
   | watch condition  | Set a watchpoint for given condition, suspend when condition is true |
   +------------------+----------------------------------------------------------------------+

#. Gdb info command

   .. code-block:: sh

      (gdb) help info
      Generic command for showing things about the program being debugged.

      List of info subcommands:

      info address -- Describe where symbol SYM is stored
      info args -- Argument variables of current stack frame
      info auto-load -- Print current status of auto-loaded files
      info auto-load-scripts -- Print the list of automatically loaded Python scripts
      info breakpoints -- Status of specified breakpoints (all user-settable breakpoints if no argument)
      info extensions -- All filename extensions associated with a source language
      info files -- Names of targets and files being debugged
      info frame -- All about selected stack frame
      info frame-filter -- List all registered Python frame-filters
      info functions -- All function names
      info line -- Core addresses of the code for a source line
      info locals -- Local variables of current stack frame
      info macro -- Show the definition of MACRO
      info macros -- Show the definitions of all macros at LINESPEC
      info mem -- Memory region attributes
      info os -- Show OS data ARG
      info proc -- Show /proc process information about any running process
      info program -- Execution status of the program
      info sharedlibrary -- Status of loaded shared object libraries
      info source -- Information about the current source file
      info sources -- Source files in the program
      info stack -- Backtrace of the stack
      info symbol -- Describe what symbol is at location ADDR
      info target -- Names of targets and files being debugged
      info threads -- Display currently known threads
      info types -- All type names
      info variables -- All global and static variable names
      info vtbl -- Show the virtual function table for a C++ object
      info watchpoints -- Status of specified watchpoints (all watchpoints if no argument)

#. Gdb info example

   .. code-block:: sh

      (gdb) info proc
      process 16918
      cmdline = '/scaffold'
      cwd = '/scaffold'
      exe = '/scaffold/scaffold'

      (gdb) info program
         Using the running image of child Thread 0x7ffff7fdd780 (LWP 16918).
      Program stopped at 0x44685d.
      It stopped after being stepped.
      $ addr2line -f -e scaffold 0x44685d
      main
      /cpp/scaffold/src/main.cpp:104

      (gdb) info target
      Symbols from "/scaffold/scaffold".
      Unix child process:
         Using the running image of child Thread 0x7ffff7fdd780 (LWP 16918).
         While running this, GDB does not access memory from...
      Local exec file:
         `/scaffold/scaffold', file type       elf64-x86-64.
         Entry point: 0x446a46

      (gdb) info line 78
      Line 78 of "/cpp/scaffold/src/main.cpp" starts at address 0x446782 <main()+2> and ends at 0x44678c <main()+12>.
      $ addr2line -f -e scaffold 0x446782
      main
      /home/natsume/workspace/projects/cpp/scaffold/src/main.cpp:78

      (gdb) info sharedlibrary
      From                To                  Syms Read   Shared Object Library
      0x00007ffff7ddab00  0x00007ffff7df5660  Yes         /lib64/ld-linux-x86-64.so.2
      0x00007ffff7bd4350  0x00007ffff7bd733c  Yes         /lib/x86_64-linux-gnu/librt.so.1
      0x00007ffff79ceed0  0x00007ffff79cf9ce  Yes         /lib/x86_64-linux-gnu/libdl.so.2
      0x00007ffff77709b0  0x00007ffff77b6ac5  Yes (*)     /usr/lib/x86_64-linux-gnu/libcurl.so.4
      0x00007ffff754e9f0  0x00007ffff755b471  Yes         /lib/x86_64-linux-gnu/libpthread.so.0
      0x00007ffff72a0620  0x00007ffff7303803  Yes (*)     /usr/lib/x86_64-linux-gnu/libstdc++.so.6

      (gdb) info source
      Current source file is /home/natsume/workspace/projects/cpp/scaffold/src/main.cpp
      Compilation directory is /home/cuiyb/workspace/projects/haha-servers/tmp/tmp/scaffold
      Located in /home/natsume/workspace/projects/cpp/scaffold/src/main.cpp
      Contains 131 lines.
      Source language is c++.
      Compiled with DWARF 2 debugging format.
      Does not include preprocessor macro info.
      $ wc -l scaffold/src/main.cpp
      131 scaffold/src/main.cpp

      (gdb) info stack
      #0  main () at /home/natsume/workspace/projects/cpp/scaffold/src/main.cpp:104

      (gdb) info threads
        Id   Target Id         Frame
        3    Thread 0x7ffff2008700 (LWP 16923) "ring" 0x00007ffff6a50c5d in poll () at ../sysdeps/unix/syscall-template.S:81
        2    Thread 0x7ffff7fdb700 (LWP 16922) "timer" 0x00007ffff7558b9d in nanosleep () at ../sysdeps/unix/syscall-template.S:81
      * 1    Thread 0x7ffff7fdd780 (LWP 16918) "bravo_server" main () at /scaffold/src/main.cpp:104

     (gdb) ptype ChineseFestival
     type = enum ChineseFestival {ChineseFestival_none, ChineseFestival_newYearDay, ChineseFestival_springFestival,
     ChineseFestival_qingmingFestival, ChineseFestival_mayDay, ChineseFestival_dragonBoatFestival,
     ChineseFestival_midAutumnDay, ChineseFestival_nationalDay, ChineseFestival_max}

     (gdb) info variables g_isRunning
      All variables matching regular expression "g_isRunning":

      File /home/natsume/workspace/projects/cpp/scaffold/src/main.cpp:
      static std::atomic_bool g_isRunning;

      (gdb) info vtbl s
      vtable for 'BravoServer' @ 0x6091f0 (subobject @ 0x8a53f0):
      [0]: 0x451ce4 <BravoServer::~BravoServer()>
      [1]: 0x451d52 <BravoServer::~BravoServer()>
      [2]: 0x451bf2 <dilidili::prepareProcess()>

