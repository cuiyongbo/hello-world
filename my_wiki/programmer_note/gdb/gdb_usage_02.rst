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
            -r--------  1 cherry  admin   701M Jul 15 21:37 core.3379
            -r--------  1 cherry  admin   701M Jul 15 21:40 core.3424

#. Gdb to debug a running process
   
    .. code-block:: sh

        # Solution one
        gdb -p PID

        # Solution two
        gdb attach pid

        # Solution three
        gdb program_name program_pid

#. Gdb to peek all methods in a class
   
    .. code-block:: sh

        (gdb) ptype PastTiCompiler
        type = class PastTiCompiler {
          private:
            int64 m_lastTiUpdateTime;
          public:
            PastTiCompiler(void);
            bool prepare(void);
            void finalize(void);
          private:
            void initPast7TiSharedMem(void);
            void loadPast7TiFromDisk(int64);
        }

        (gdb) info functions PastTiCompiler
        All functions matching regular expression "PastTiCompiler":
      
        File /past_ti_compiler/src/past_ti_compiler.cpp:
        void PastTiCompiler::PastTiCompiler();
        TiLinkMap *PastTiCompiler::allocFilteredMap(TiData*);
        void PastTiCompiler::finalize();
        void PastTiCompiler::initPast7TiSharedMem();
        void PastTiCompiler::initWeeklyPastTiSharedMem();
        bool PastTiCompiler::prepare();

#. Gdb to print all function names
   
    .. code-block:: sh

        (gdb) file a.out
        (gdb) info function
        All defined functions:
      
        File selection_partial_sort_alg.c:
        int main();
        int randint(int, int);
        void select_nthElement(int *, int, int, int);
        void select_nthElement_2(int *, int, int, int);
        void select_nthElement_loop(int *, int, int, int);
      
        Non-debugging symbols:
        0x0000000000400460  _init
        ...