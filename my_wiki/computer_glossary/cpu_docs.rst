**********
CPU Basics
**********

.. toctree::

    cpu/cpu_term_notes_01
    cpu/cpu_architecture
    cpu/arm_compiler_unaligned_access
    cpu/android_cpu_differences


#. Linux to inspect cpu information

    .. code-block:: sh

        # A silver solution: just have a look at `/proc/cpuinfo`.
        # count the number of processing units
        $ grep 'processor' /proc/cpuinfo 
        processor       : 0
        processor       : 1
        processor       : 2
        processor       : 3
        processor       : 4
        processor       : 5
        processor       : 6
        processor       : 7

        # get the actual number of cores, check the core id for unique values
        $ grep 'core id' /proc/cpuinfo | sort -u
        core id         : 0
        core id         : 1
        core id         : 2
        core id         : 3

        # Another solution, use lscpu command
        $ lscpu
        Architecture:          x86_64
        CPU op-mode(s):        32-bit, 64-bit
        Byte Order:            Little Endian
        CPU(s):                8
        On-line CPU(s) list:   0-7
        Thread(s) per core:    2
        Core(s) per socket:    4
        CPU socket(s):         1
        NUMA node(s):          1
        CPU MHz:               2394.374
        ...


.. rubric:: Footnotes

.. [#] `Branch predication <https://en.wikipedia.org/wiki/Predication_(computer_architecture)>`_
.. [#] `Branch predicator <https://en.wikipedia.org/wiki/Branch_predictor>`_
