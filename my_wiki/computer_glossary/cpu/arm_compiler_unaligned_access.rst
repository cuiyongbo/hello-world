How does the ARM Compiler support unaligned accesses?
=====================================================

Answer
------

Older ARM processors require data load and stores to be to/from architecturally aligned addresses.  This means::

   LDRB/STRB          - address must be byte aligned
   LDRH/STRH          - address must be 2-byte aligned 
   LDR/STR            - address must be 4-byte aligned

Load/store instructions that act on multiple registers, for example ``LDM``, are considered as working with multiple word quantities, so these instructions also require 4-byte aligned addresses. An unaligned load is one where the address does not match the architectural alignment.

On older processors, such as ARM9 family based processors, an unaligned load had to be synthesised in software.  Typically by doing a series of small accesses, and combining the results.
The ARMv6 architecture introduced the first hardware support for unaligned accesses.  ARM11 and Cortex-A/R processors can deal with unaligned accesses in hardware, removing the need for software routines. 

Support for unaligned accesses is limited to a sub-set of load/store instructions::

   LDRB/LDRSB/STRB
   LDRH/LDRSH/STRH
   LDR/STR

Instructions which do **NOT** support unaligned accesses include::

   LDM/STM
   LDRD/STRD

Further, unaligned accesses are only allowed to regions marked as Normal memory type, and unaligned access support must be enabled by setting the ``SCTLR.A`` bit in the system control coprocessor. Attempts to perform unaligned accesses when not allowed will cause an alignment fault (data abort).

How hardware supports unaligned accesses
----------------------------------------

In many cases a processor cannot generate an unaligned access on its interfaces to the memory system. This applies to caches, TCMs and the system bus.  In these situations, the processor will generate a series of accesses, to implement the unaligned access.  This is similar to the software routines used for previous processors.

For example::

    LDR r0, [0x8001]

Most modern ARM processors have 64-bit or 128-bit interfaces.  In the above example a processor would typically read the 64-bit or 128-bit block contains bytes ``0x8001, 0x8002, 0x8003 and 0x8004``.  Discarding the other bytes.

Another example::

    LDR r0, [0x81FC]

The four bytes of this load span both a 64-bit and 128-bit boundary.  So with either interface width, the processor would have to perform two reads.

In both of these examples it is possible to see that unaligned accesses require more work by the hardware.  While more efficient than the software routines required by previous processors, it is still less efficient than aligned accesses.

Pointer alignment in C
----------------------

When compiling C, variables are by default architecturally aligned.  A global of type ``int`` (or ``uint32_t``) will be 4-byte aligned in memory.  Similarly, a pointer of type ``int*`` is expected to contain a 4-byte aligned address.

Where this is not the case (or may not be the case) the variable or pointer MUST be marked with the ``__packed`` keyword.  This is a warning to the compiler that this variable, structure or pointer is potentially unaligned.  Technically, it reduces the expected alignment of the pointer to 1-byte. It is possible to set the alignment of all pointers to 1 by using the compiler command line switch ``--pointer_alignment=1``, it which case the compiler will treat all accesses through pointers as though they may be unaligned.

Compiler assumptions
--------------------

When compiling for a ARMv6 or ARMv7-A/R processor, the ARM Compiler will assume that it can use unaligned accesses.
The ``--no_unaligned_access`` flag tells the compiler not to knowingly generate unaligned accesses.  What is the significance of knowingly?

As mentioned above, a pointer should contain an address with correct alignment for the type.

.. code-block:: c

   uint32_t*  requires 4-byte alignment
   uint16_t*  requires 2-byte alignment
   uint8_t*  requires 1-byte alignment

For structures, the alignment is that of the most aligned member.
The compiler will generate code on the assumption that a pointer is correctly aligned.  It does not add code to perform run-time checks.  A pointer may contain an incorrectly aligned address for a number of reasons.  A common cause is casting:

.. code-block:: c

   uint8_t tmp;
   uint32_t* pMyPointer = (uint32_t*)(&tmp);

This code takes the address of an ``uint8_t`` variable, then casts that address as a ``uint32_t`` pointer.  The compiler will still assume that ``pMyPointer`` is correctly aligned for a ``uint32_t`` pointer.  The compiler might then generate code that results in an unaligned access unknowingly.

This can be avoided using the ``__packed`` qualifier:

.. code-block:: c

   __packed uint32_t* pMyPointer = (__packed uint32_t*)(&tmp);

Code Generation
---------------

When unaligned accesses are permitted, the compiler will continue to use instructions that support unaligned accesses (for example ``LDR`` and ``STR``) for accesses through ``__packed`` pointers.  However it will not use instructions such as ``LDM`` which do not support unaligned accesses.

When unaligned accesses are not permitted, either because the code is being built for an ARMv4 or ARMv5 processor, or because ``--no_unaligned_access`` is specified, the compiler will access ``__packed`` data by a performing a number of aligned accesses.  Usually, this is done by calling a library function such as ``__aeabi_uread4()``.

Device Memory
-------------

Address regions that are used to access peripherals rather than memory should be marked as Device memory. Depending upon the processor, this may be configured in the :abbr:`MPU (Memory Protection Unit)` or :abbr:`MMU (Memory Management Unit)`. Unaligned accesses are not permitted to these regions even when unaligned access support is enabled.  If an unaligned access is attempted, the processor will take an abort.

The compiler does not have any information on which address ranges are device memory, and it is therefore the responsibility of programmer to ensure that accesses to devices are aligned.  In practice, this usually is the case simply because peripheral registers are at aligned addresses.  It is also usual to access peripheral registers through ``volatile`` variables or pointers, which restricts the compiler to accessing the data with the size of access specified where possible.  For further information on the restrictions imposed on ``volatile`` types, please see :download:`the Procedure Call Standard for the ARM Architecture <downloads/Procedure_Call_Standard_for_the ARM_Architecture.pdf>`.

It is also necessary to avoid using C library functions such as ``memcpy()`` to access Device memory, as there is no guarantee of the type of accesses these functions will use.  If it is necessary to copy a buffer of memory to a Device memory, you should provide a suitable copying routine and call this instead of ``memcpy()``.



Performance
-----------

If code frequently accesses unaligned data, there may be a performance advantage in enabling unaligned accesses.  However, the extent of this advantage will be dependent on many factors. Even though this support allows a single instruction to access unaligned data, this will often require multiple bus accesses to occur.  Therefore the bus transactions performed by an unaligned access may be similar to those performed by the multiple instructions used when unaligned access support is disabled.  The code without unaligned access support will have to perform various shift and logical operations, but on a multi-issue processor the execution time of these may be hidden by executing them in parallel with the memory accesses.  There will also be a function call overhead when functions such as ``__aeabi_uread4()`` are used, though the impact of these may be reduced by branch prediction.