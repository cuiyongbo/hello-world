************
Gdb Tricks 2
************

**You force yourself to speed up because you don't want to keep others waitting.**

#. Generate core dump
   
   first to if core dump is enabled::

      $ ulimit -c
      0
      $ ulimit -c unlimited

   second compile test program with ``gcc -g core_dump_demo.c`` 
   the run it::

      $ ./a.out 
      *** Error in `./a.out': double free or corruption (fasttop): 0x000000000062d010 ***
      ======= Backtrace: =========
      /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7f66b0c487e5]
      /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7f66b0c5137a]
      /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7f66b0c5553c]
      ./a.out[0x400594]
      /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7f66b0bf1830]
      ./a.out[0x400499]
      ======= Memory map: ========
      00400000-00401000 r-xp 00000000 08:01 2359519                            /home/cherry/program-demo/cpp-demo/a.out
      00600000-00601000 r--p 00000000 08:01 2359519                            /home/cherry/program-demo/cpp-demo/a.out
      00601000-00602000 rw-p 00001000 08:01 2359519                            /home/cherry/program-demo/cpp-demo/a.out
      0062d000-0064e000 rw-p 00000000 00:00 0                                  [heap]
      7f66ac000000-7f66ac021000 rw-p 00000000 00:00 0 
      7f66ac021000-7f66b0000000 ---p 00000000 00:00 0 
      7f66b09bb000-7f66b09d1000 r-xp 00000000 08:01 1840155                    /lib/x86_64-linux-gnu/libgcc_s.so.1
      7f66b09d1000-7f66b0bd0000 ---p 00016000 08:01 1840155                    /lib/x86_64-linux-gnu/libgcc_s.so.1
      7f66b0bd0000-7f66b0bd1000 rw-p 00015000 08:01 1840155                    /lib/x86_64-linux-gnu/libgcc_s.so.1
      7f66b0bd1000-7f66b0d91000 r-xp 00000000 08:01 1836539                    /lib/x86_64-linux-gnu/libc-2.23.so
      7f66b0d91000-7f66b0f91000 ---p 001c0000 08:01 1836539                    /lib/x86_64-linux-gnu/libc-2.23.so
      7f66b0f91000-7f66b0f95000 r--p 001c0000 08:01 1836539                    /lib/x86_64-linux-gnu/libc-2.23.so
      7f66b0f95000-7f66b0f97000 rw-p 001c4000 08:01 1836539                    /lib/x86_64-linux-gnu/libc-2.23.so
      7f66b0f97000-7f66b0f9b000 rw-p 00000000 00:00 0 
      7f66b0f9b000-7f66b0fc1000 r-xp 00000000 08:01 1836537                    /lib/x86_64-linux-gnu/ld-2.23.so
      7f66b11a7000-7f66b11aa000 rw-p 00000000 00:00 0 
      7f66b11bf000-7f66b11c0000 rw-p 00000000 00:00 0 
      7f66b11c0000-7f66b11c1000 r--p 00025000 08:01 1836537                    /lib/x86_64-linux-gnu/ld-2.23.so
      7f66b11c1000-7f66b11c2000 rw-p 00026000 08:01 1836537                    /lib/x86_64-linux-gnu/ld-2.23.so
      7f66b11c2000-7f66b11c3000 rw-p 00000000 00:00 0 
      7fffc3a94000-7fffc3ab5000 rw-p 00000000 00:00 0                          [stack]
      7fffc3b4a000-7fffc3b4d000 r--p 00000000 00:00 0                          [vvar]
      7fffc3b4d000-7fffc3b4f000 r-xp 00000000 00:00 0                          [vdso]
      ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
      Aborted (core dumped)
      $ ls
      a.out  core  core_dump_demo.c
      $ gdb a.out core
      (gdb) bt
      ****#0  0x00007f66b0c06428 in __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:54
      #1  0x00007f66b0c0802a in __GI_abort () at abort.c:89
      #2  0x00007f66b0c487ea in __libc_message (do_abort=do_abort@entry=2, fmt=fmt@entry=0x7f66b0d61ed8 "*** Error in `%s': %s: 0x%s ***\n") at ../sysdeps/posix/libc_fatal.c:175
      #3  0x00007f66b0c5137a in malloc_printerr (ar_ptr=<optimized out>, ptr=<optimized out>, str=0x7f66b0d61fa0 "double free or corruption (fasttop)", action=3) at malloc.c:5006
      #4  _int_free (av=<optimized out>, p=<optimized out>, have_lock=0) at malloc.c:3867
      #5  0x00007f66b0c5553c in __GI___libc_free (mem=<optimized out>) at malloc.c:2968
      #6  0x0000000000400594 in main () at core_dump_demo.c:8
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

      # without core dump
      $ addr2line 0x0000000000400594
      /home/cherry/program-demo/cpp-demo/core_dump_demo.c:9


