Number's tricks
===============

Memory alignment
----------------

find the least integer *c* to make ``c*b`` no less than *a*::

   (size + alignment - 1) / alignment

typically used for memory alignment.


Bit tricks
----------

Check if an unsigned integer is a power of 2::

   x & (x-1)

0 means *x* is a power of 2, otherwise not.

