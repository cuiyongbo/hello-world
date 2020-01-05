****************
Memory Alignment
****************

"X bytes aligned" means that the base address of your data must be a multiple of X.
An object that is "8 bytes aligned" is stored at a memory address that is a multiple of 8.
It can be used by using some special hardware like a DMA in some special hardware,
for a faster access by the cpu, etc...

Many CPUs will only load some data types from aligned locations; on some CPUs such access
is just faster. There's also several other possible reasons for using memory alignment - without
seeing the code it's hard to say why.

Aligned access is faster because **the external bus to memory is not a single byte wide** - it is
typically 4 or 8 bytes wide (or even wider). This means that the CPU doesn't fetch a single byte
at a time - it fetches 4 or 8 bytes starting at the requested address. As a consequence of this,
the 2 or 3 least significant bits of the memory address are not actually sent by the CPU - the
external memory can only be read or written at addresses that are a multiple of the bus width.
If you requested a byte at address "9", the CPU would actually ask the memory for the block of
bytes beginning at address 8, and load the second one into your register (discarding the others).

This implies that a misaligned access can require more reads from memory: If you ask for 8 bytes
beginning at address 9, the CPU must fetch the 8 bytes beginning at address 8 as well as the 8 bytes
beginning at address 16, then mask out the bytes you wanted. On the other hand, if you ask for the 8
bytes beginning at address 8, then only a single fetch is needed.

.. code-block:: c

    srand((unsigned int)time(NULL));
    uint8* ptr = NULL;
    for (int i=0; i<10; i++)
    {
       ptr = (uint8*)malloc(rand());
       if ((size_t)&ptr & 7)
       {
          printf("misaligned\n");
       }
       free(ptr);
    }

#. posix_memalign, aligned_alloc, memalign, valloc, pvalloc - allocate aligned memory

    The ``function posix_memalign()`` allocates size bytes and places the address of the
    allocated memory in ``*memptr``. The address of the allocated memory will be a multiple
    of *alignment*, which must be a power of two and a multiple of ``sizeof(void *)``. If *size* is 0,
    then  the value placed in ``*memptr`` is either ``NULL``, or a unique pointer value that
    can later be successfully passed to ``free(3)``.
