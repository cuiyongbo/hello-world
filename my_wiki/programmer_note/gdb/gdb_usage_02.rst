*************
Gdb Tricks 02
*************

**You force yourself to speed up because you don't want to keep others waitting.**

#. Generate core dump

    First to check if core dump is enabled::

        $ ulimit -c
        0
        $ ulimit -c unlimited

    Second compile test program with ``gcc -g core_dump_demo.c``
    then run::

        $ ./a.out
        Aborted (core dumped)
        $ ls
        a.out  core  core_dump_demo.c
        $ gdb a.out core
        (gdb) bt
        ****#0  0x00007f66b0c06428 in __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:54
        #1  0x00007f66b0c0802a in __GI_abort () at abort.c:89
        ...
        (gdb) frame 6
        #6  0x0000000000400594 in main () at core_dump_demo.c:8
        8      free(a);
        (gdb) list
        3
        4  int main()
        5  {
        6      int* a = (int*)malloc(sizeof(int));
        7      free(a);
        8      free(a);
        9      return 0;
        10 }

    .. note::

        Most implementations leave the core file in the current working directory
        of the corresponding process; Mac OS X places all core files
        in **/cores** instead::

            cherry@MacBook-Pro scaffold$ ll /cores/
            total 8712904
            -r--------  1 cherry  admin   718M Sep 11 22:33 core.1038

        how to control core pattern, refer to `/proc/sys/kernel/core_pattern`.
        In most linux releases, the content of core_pattern file is simply `core`,
        which means that OS will generate a core file with name 'core' in current directory
        when coredump is triggered.

#. Gdb to debug a running process

    .. code-block:: sh

        # Solution one
        gdb -p PID

        # Solution two
        gdb attach pid

        # Solution three
        gdb program_name program_pid

        # if you want change the process to debug, use `attach` command
        attach new_pid

    .. important:: Sometime you man need `sudo` previlege to see debug symbol table.

#. attach command

    Attach to a process or file outside of GDB.

    This command attaches to another target, of the same type as your last
    "target" command ("info files" will show your target stack).
    The command may take as argument a process id or a device file.
    For a process id, you must have permission to send the process a signal,
    and it must have the same effective uid as the debugger.
    When using "attach" with a process id, the debugger finds the
    program running in the process, looking first in the current working
    directory, or (if not found there) using the source file search path
    (see the "directory" command).  You can also use the "file" command
    to specify the program, and to load its symbol table.

#. Gdb to peek all methods in a class

    .. code-block:: sh

        (gdb) ptype BlueGlass
        type = class BlueGlass {
          private:
            int64 m_hugo;
          public:
            BlueGlass(void);
            ...
        }

        (gdb) info functions BlueGlass
        All functions matching regular expression "BlueGlass":

        File /blue_glass/src/blue_glass.cpp:
        void BlueGlass::BlueGlass();
        void BlueGlass::finalize();
        bool BlueGlass::prepare();
        ...

#. Gdb to print all function names

    .. code-block:: sh

        (gdb) help info functions
        All function names, or those matching REGEXP.

        (gdb) info function
        All defined functions:

        File selection_partial_sort_alg.c:
        int main();
        int randint(int, int);
        void select_nthElement(int *, int, int, int);
        void select_nthElement_loop(int *, int, int, int);

        Non-debugging symbols:
        0x0000000000400460  _init
        ...

        (gdb) info functions map_*
        All functions matching regular expression "map_*":

        File ../src/map.c:
        void map_deinit_(map_base_t *);
        void *map_get_(map_base_t *, const char *);
        map_iter_t map_iter_(void);
        ...

#. Gdb to print long string

    .. code-block:: sh

        set print elements 0

        # set print elements number-of-elements
        # Set a limit on how many elements of an array GDB will print.
        # If GDB is printing a large array, it stops printing after it
        # has printed the number of elements set by the ``set print elements`` command.
        # This limit also applies to the display of strings. When GDB starts, this limit
        # is set to 200. Setting number-of-elements to zero means that the printing is unlimited.

        (gdb) set print element 0
        (gdb) p (char*)postData->m_bytes
        $24 = 0x2b88680 "{very long string ...}"

#. Gdb to locate your current location

    .. code-block:: sh

        (gdb) info frame
        Stack level 0, frame at 0x7ffffffee150:
         rip = 0x8000fce in map_set_ (../src/map.c:150); saved rip = 0x800091e
         called by frame at 0x7ffffffee1b0
         source language c.
         Arglist at 0x7ffffffee140, args: m=0x7ffffffee170, key=0x8001248 "cyb", value=0x7ffffffee188, vsize=4
         Locals at 0x7ffffffee140, Previous frame's sp is 0x7ffffffee150
         Saved registers:
          rbp at 0x7ffffffee140, rip at 0x7ffffffee148

        (gdb) info line
        Line 150 of "../src/map.c" starts at address 0x8000fce <map_set_+95> and ends at 0x8000fe8 <map_set_+121>.

        (gdb) bt
        #0  map_set_ (m=0x7ffffffee170, key=0x8001248 "cyb", value=0x7ffffffee188, vsize=4) at ../src/map.c:150
        #1  0x000000000800091e in main () at example.c:12
        (gdb) frame 1
        #1  0x000000000800091e in main () at example.c:12
        12          map_set(&m, "cyb", 1);
        (gdb) frame
        #1  0x000000000800091e in main () at example.c:12
        12          map_set(&m, "cyb", 1);
        (gdb) info line
        Line 12 of "example.c" starts at address 0x80008f7 <main+45> and ends at 0x800091e <main+84>.

#. Gdb to return from the current function

    .. code-block:: sh

        (gdb) help return
        Make selected stack frame return to its caller.
        Control remains in the debugger, but when you continue
        execution will resume in the frame above the one now selected.
        If an argument is given, it is an expression for the value to return.

#. Gdb `command` note

    .. code-block:: sh

        (gdb) help command
        Set commands to be executed when the given breakpoints are hit.
        Give a space-separated breakpoint list as argument after "commands".
        A list element can be a breakpoint number (e.g. `5') or a range of numbers
        (e.g. `5-7').
        With no argument, the targeted breakpoint is the last one set.
        The commands themselves follow starting on the next line.
        Type a line containing "end" to indicate the end of them.
        Give "silent" as the first line to make the breakpoint silent;
        then no output is printed when it is hit, except what the commands print.

        (gdb) command
        Type commands for breakpoint(s) 10, one per line.
        End with a line saying just "end".
        >silent
        >p number_of_contracted_nodes
        >end
        (gdb) info b 10
        Num     Type           Disp Enb Address            What
        10      breakpoint     keep y   0x0000000008796361 in osrm::contractor::contractGraph(...) at graph_contractor.cpp:761
                breakpoint already hit 40 times
                silent
                p number_of_contracted_nodes

        (gdb) c
        Continuing.
        $50 = 2412
        (gdb) c
        Continuing.
         10% $51 = 3061
        (gdb) disable 10 # disabling breakpoint will cancle command as well

#. gdb to view stl containers' contents

    - Check-out the latest Python libstdc++ printers to a place on your machine.
      In a local directory, do: ``svn co svn://gcc.gnu.org/svn/gcc/trunk/libstdc++-v3/python``.

    - Add the following to your ``~/.gdbinit``. The path needs to match where the python module above was checked-out.
      So if checked out to: ``/home/maude/gdb_printers/``, the path would be as written in the example::

        python
        import sys
        sys.path.insert(0, '/home/maude/gdb_printers/python')
        from libstdcxx.v6.printers import register_libstdcxx_printers
        register_libstdcxx_printers (None)
        end

.. rubric:: Footnotes

.. [#] `GDB STL Support Tools <http://sourceware.org/gdb/wiki/STLSupport>`_
