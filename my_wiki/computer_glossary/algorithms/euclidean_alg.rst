*******************
Euclidean Algorithm
*******************

.. code-block:: none
   :caption: Implementation

   // gcd - greatest common divisor 
   // or
   // gcf - greatest common factor

   gcd-division(a, b)
      while b != 0
         t = b
         b = a mod b
         a = t
      return a

   gcd-recursion(a, b)
      if b == 0
         return a
      else 
         return gcd(b, a mod b)

   gcd-substraction(a, b)
      while a != b
         if a>b
            a = a - b
         else
            b = b - a
      return a
