*************************
Memory allocation options
*************************

Refer to ``man mallopt`` for futher information.

#. M_MMAP_THRESHOLD

    For allocations greater than or equal to the limit specified (in bytes) by ``M_MMAP_THRESHOLD``
    that can't be satisfied from the free list, the memory-allocation functions employ *mmap(2)*
    instead of increasing the program break using *sbrk(2)*.

#.  M_TRIM_THRESHOLD

    When the amount of contiguous free memory at the top of the heap grows sufficiently large, ``free(3)``
    employs ``sbrk(2)`` to release this memory back to the system. (This can be useful in programs that
    continue to execute for a long period after freeing a significant amount of memory.) The ``M_TRIM_THRESHOLD``
    parameter specifies the minimum size (in bytes) that this block of memory must reach before ``sbrk(2)`` is
    used to trim the heap.
