Gprof Note
==========

"Ggprof" produces an execution profile of C, Pascal, or Fortran77 programs. The effect of called routines is
incorporated in the profile of each caller. The profile data is taken from the call graph profile file
(**gmon.out** default) which is created by programs that are compiled with the ``-pg`` option of gcc.
The ``-pg`` option also links in versions of the library routines that are compiled for profiling.
"Gprof" reads the given object file (the default is **a.out**) and establishes the relation between its symbol
table and the call graph profile from *gmon.out*.

"Gprof" calculates the amount of time spent in each routine. Next, these times are propagated along the edges
of the call graph. Cycles are discovered, and calls into a cycle are made to share the time of the cycle.

Several forms of output are available from the analysis:

    The **flat profile** shows how much time your program spent in each function, and how many times that function was
    called. If you simply want to know which functions burn most of the cycles, it is stated concisely here.

    The **call graph** shows, for each function, which functions called it, which other functions it called, and how
    many times. There is also an estimate of how much time was spent in the subroutines of each function.
    This can suggest places where you might try to eliminate function calls that use a lot of time.

    The **annotated source** listing is a copy of the program's source code, labeled with the number of times each
    line of the program was executed.

.. option:: -b, --brief

    Ignore explanation for each kind of output.

.. option:: -p, --flat-profile

    Print flat profile, inverse of :option:`-P, --no-flat-profile`.

.. option:: -q, --graph

    Print call graph, inverse of :option:`-Q, --no-graph`.

.. code-block:: sh
    :caption: easy tutorial

    # Suppress printing statically declared functions with ``-a`` option
    $ gprof -b -a TestGprof gmon.out > analysis.out

    # Print only flat profile using ``-p`` option
    $ gprof -b -p TestGprof

    # Print info related to specific function
    $ gprof -b -pStaticFunc TestGprof

    # Suppress printing of flat profile using ``-P`` option
    $ gprof -b -P TestGprof

    # Print only call graph using ``-q`` option
    $ gprof -b -q TestGprof

    # Suppress printing of call graph using ``-Q`` option
    $ gprof -b -Q TestGprof

#. Sample interval

    the sample interval is 0.01s, routines with execution time less than than won't be included.

#. Compile program with ``-pg`` option, but no gmon.out after executing

    Possible reasons:

        - prog may have ignored **SIGPROF (profiling timer alarm)** signal.
        - prog has exited abnormally or crashed

