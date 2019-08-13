***********************
Nginx Memory Management
***********************

In Nginx memory management is implemented using memmory pools, and the pool is
implemented using singly linked list. and has several benefits:

    - minimize memory leak
    - reduce the number of malloc, calloc system calls, thus reduce fragmentations
    - minimize the overhead of the allocation of small objects
    - improve memory access: in the memory pool the memory addresses are aligned and there is a memory paging 
      mechanism that improve CPU page hists and memory access.

Source files: ``ngx_palloc.h, ngx_palloc.c, ngx_alloc.h, ngx_alloc.c``.



.. rubric:: Footnotes

.. [#] `What is memory mapping <http://ecomputernotes.com/fundamental/input-output-and-memory/memory-mapping>`_