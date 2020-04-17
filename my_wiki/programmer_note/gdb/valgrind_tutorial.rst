*****************
valgrind tutorial
*****************

NAME: valgrind - a suite of tools for debugging and profiling programs

SYNOPSIS: `valgrind [valgrind-options] [your-program] [your-program-options]`

.. code-block:: cpp
    :caption: Sample: test.cpp
    :linenos:

    #include <iostream>

    using namespace std;

    class Base
    {
    public:
            virtual ~Base() {}
    };

    class Derived : public Base
    {
            int m_a;
    };

    int main()
    {

            Base* p = new Derived[10];
            delete[] p;
            return 0;
    }

.. code-block:: sh
    :caption: Check memory leak in your program

    # basic option about leak-checking
    $ valgrind --help | grep leak
        --leak-check=no|summary|full     search for memory leaks at exit?  [summary]
        --leak-resolution=low|med|high   differentiation of leak stack traces [high]
        --show-leak-kinds=kind1,kind2,.. which leak kinds to show?
        --errors-for-leak-kinds=kind1,kind2,..  which leak kinds are errors?
        --leak-check-heuristics=heur1,heur2,... which heuristics to use for
            improving leak search false positive [all]
        --show-reachable=yes             same as --show-leak-kinds=all
                                         same as --show-leak-kinds=definite,possible
                                         same as --show-leak-kinds=definite

    # compile your program with debug information
    $ g++ -g test.cpp

    # run valgrind with your program
    $ valgrind ./a.out
    ...
    ==57684== Use of uninitialised value of size 8
    ==57684==    at 0x4008E3: main (test.cpp:20)
    ==57684==
    ==57684== Invalid read of size 8
    ==57684==    at 0x4008E3: main (test.cpp:20)
    ...
    ==57684== Process terminating with default action of signal 11 (SIGSEGV)
    ==57684==  Access not within mapped region at address 0x0
    ==57684==    at 0x4008E3: main (test.cpp:20)
    ==57684==  If you believe this happened as a result of a stack
    ==57684==  overflow in your program's main thread (unlikely but
    ==57684==  possible), you can try to increase the size of the
    ==57684==  main thread stack using the --main-stacksize= flag.
    ==57684==  The main thread stack size used in this run was 8388608.
    ==57684==
    ==57684== HEAP SUMMARY:
    ==57684==     in use at exit: 72,872 bytes in 2 blocks
    ==57684==   total heap usage: 2 allocs, 0 frees, 72,872 bytes allocated
    ==57684==
    ==57684== LEAK SUMMARY:
    ==57684==    definitely lost: 0 bytes in 0 blocks
    ==57684==    indirectly lost: 0 bytes in 0 blocks
    ==57684==      possibly lost: 0 bytes in 0 blocks
    ==57684==    still reachable: 72,872 bytes in 2 blocks
    ==57684==                       of which reachable via heuristic:
    ==57684==                         newarray           : 168 bytes in 1 blocks
    ==57684==         suppressed: 0 bytes in 0 blocks
    ==57684== Rerun with --leak-check=full to see details of leaked memory
    ==57684==
    ==57684== For counts of detected and suppressed errors, rerun with: -v
    ==57684== Use --track-origins=yes to see where uninitialised values come from
    ==57684== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
    Segmentation fault

    # more advance options
    $ valgrind --track-origins=yes -v ./a.out
    ...
    --57690-- REDIR: 0x525b570 (libc.so.6:__strcmp_sse2_unaligned) redirected to 0x4c31f90 (strcmp)
    --57690-- REDIR: 0x4ec7f10 (libstdc++.so.6:operator new[](unsigned long)) redirected to 0x4c2e7a0 (operator new[](unsigned long))
    ==57690== Use of uninitialised value of size 8
    ...
    --57690-- REDIR: 0x52404f0 (libc.so.6:free) redirected to 0x4c2ed80 (free)
    ...
    ==57690== 1 errors in context 1 of 2:
    ==57690== Invalid read of size 8
    ==57690==    at 0x4008E3: main (test.cpp:20)
    ==57690==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
    ...
    ==57690== 1 errors in context 2 of 2:
    ==57690== Use of uninitialised value of size 8
    ==57690==    at 0x4008E3: main (test.cpp:20)
    ==57690==  Uninitialised value was created by a heap allocation
    ==57690==    at 0x4C2E80F: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==57690==    by 0x40087C: main (test.cpp:19)

.. code-block:: sh

    # --tool=<toolname> [default: memcheck]
    #     Run the Valgrind tool called toolname, e.g. memcheck, cachegrind, callgrind,
    #     helgrind, drd, massif, lackey, none, exp-sgcheck, exp-bbv, exp-dhat, etc.

    $ valgrind --tool=maxif ./test
    $ less massif.txt
