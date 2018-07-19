*****************************
Algorithm analysis and design
*****************************

Fibonacci series
================

.. code-block:: python

   # exponential complexity O(2^n)

   def fibonacci(n):
      """Return a list containing the Fibonacci series up to n."""
      result = []
      a, b = 0, 1
      while a<n:
         result.append(a)
         a, b = b, b+a
      return result