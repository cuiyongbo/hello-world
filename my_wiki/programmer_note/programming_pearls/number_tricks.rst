:orphan:

***************
Number's tricks
***************

Memory alignment
================

find the least integer *c* to make ``c*b`` no less than *a*::

   (size + alignment - 1) / alignment

typically used for memory alignment.


Bit tricks
==========

Check if an unsigned integer *x* is a power of 2::

   x & (x-1)

0 means *x* is a power of 2, otherwise not.

**Note first check if x equals 0.**

Check if an unsigned integer x is of form :math:`2^n -1`::

   x & (x+1)

0 means yes, otherwise not. This can also be used to turning
off all trailing 1.

**Note first check if x is 0 or all 1.**

Find the left most 1
====================

.. code-block:: c
   :caption: Find the highest order bit in C

   // Solution 1
   1 << (int)log2(x)

   // Solution 2
   int hibit1 (int num)
   {
      if (!num)
         return 0;
   
      int ret = 1;
   
      while (num >>= 1)
         ret <<= 1;
   
      return ret;
   }

   // Solution 3, Taken for hacker's delight
   int hibit2(int32 n)
   {
      n |= (n >> 1);
      n |= (n >> 2);
      n |= (n >> 4);
      n |= (n >> 8);
      n |= (n >> 16);

      return n - (n >> 1);
   }


Find the right most 1
=====================

Use the formula to isolate the rightmost 1-bit::

   x & (-x)

return 0 if none.


