*****************************
Algorithm analysis and design
*****************************

Fibonacci series
================

.. code-block:: python

   # exponential complexity O(2^n)
   def fibnacci_1(n):
      """return the nth element in fibonacci series."""
      if n < 2:
         return n
      else:
         return fibnacci_1(n-1) + fibnacci_1(n-2) 

   # linear complexity O(n)
   def fibonacci_2(n):
      """Return a list containing the Fibonacci series up to n."""
      result = []
      a, b = 0, 1
      while a<n:
         result.append(a)
         a, b = b, b+a
      return result


