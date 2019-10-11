**************************
C/C++ Miscellaneous Tricks
**************************

.. toctree::
   :titlesonly:

   addressof_manual
   extern_c_linkage
   cpp_smart_pointer
   cpp_allocator
   pointer_to_function_demo
   flexible_array_tricks
   cpp_std_map_notes

#. ``#pragma pack(n)`` VS ``#pragma pack(push, n)``

   ``#pragma pack(n)`` sets compiler alignment to n bytes. Calling pack with no arguments
   sets *n* to the value set in the compiler option ``/Zp``. If the compiler option is not
   set, the default value is 8.

   ``#pragma pack(push[,n])`` pushes the current alignment setting on an internal compiler
   stack and then optionally sets the new alignment. ``#pragma pack(pop)`` restores the alignment
   setting to the one at the top of the internal compiler stack (and removes that stack entry).

   **Note** that ``#paragma pack([n])`` doesn't influence this internal stack; thus it's
   possible to have ``#pragma pack(push)`` followed by multiple ``#pragma pack(n)`` instances
   and finalized by a single ``#pragma pack(pop)``.

   .. code-block:: cpp
      :caption: taken from `MSDN pack directive <https://msdn.microsoft.com/en-us/library/2e70t5y1.aspx>`_

      // compile with: /W1 /c
      #pragma pack()   // n defaults to 8; equivalent to /Zp8
      #pragma pack(show)   // C4810
      #pragma pack(4)   // n = 4
      #pragma pack(show)   // C4810
      #pragma pack(push, r1, 16)   // n = 16, pushed to stack
      #pragma pack(show)   // C4810
      #pragma pack(pop, r1, 2)   // n = 2 , stack popped
      #pragma pack(show)   // C4810

#. Use constant :math:`\pi`

   .. code-block:: c

      // math.h
      #define M_PI        3.14159265358979323846264338327950288
      #define M_PI_2      1.57079632679489661923132169163975144
      #define M_PI_4      0.785398163397448309615660845819875721
