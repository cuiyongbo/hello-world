****************
Hackers' Delight
****************

#. Memory alignment


   find the least integer *c* to make ``c*b`` no less than *a*: 
   ``(size + alignment - 1) / alignment`` typically used for 
   memory alignment.


#. Bit tricks

   Check if an unsigned integer *x* is a power of 2: ``x & (x-1)``
   0 means *x* is a power of 2, otherwise not. **Note** first check 
   if x equals 0.
   
   Check if an unsigned integer x is of form :math:`2^{n} - 1:` ``x & (x+1)``
   0 means yes, otherwise not. This can also be used to turning
   off all trailing 1. **Note** first check if x is 0 or all 1.
   
   #. Find the left most 1
   
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


#. Find the right most 1

   Use the formula to isolate the rightmost 1-bit: ``x & (-x)``
   return 0 if none.


#. Negation

   The negation of a number a can be computed by ``~a + 1``.


#. Check NAN
   
   According to the *IEEE standard,* NaN values have the odd property that comparisons involving 
   them are always false. That is, for a float f, ``f != f`` will be true only if f is ``NaN.``
   **Note** that not all compilers respect this when optimizing code.

   .. code-block:: c

      /*Taken */
      #ifndef _HUGE_ENUF
      #define _HUGE_ENUF  1e+300 /* _HUGE_ENUF*_HUGE_ENUF must overflow */
      #endif /* _HUGE_ENUF */
      
      #define INFINITY   ((float)(_HUGE_ENUF * _HUGE_ENUF))  /* causes warning C4756: overflow in constant arithmetic (by design) */
      #define NAN        ((float)(INFINITY * 0.0F))

      #define IS_NAN(o) ((o) != (o))

#. Comparison of float or double numbers

   .. code-block:: cpp
      :caption: taken from *The art of computer programming*

      bool approximatelyEqual(float a, float b, float epsilon)
      {
          return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
      }
      
      bool essentiallyEqual(float a, float b, float epsilon)
      {
          return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
      }
      
      bool definitelyGreaterThan(float a, float b, float epsilon)
      {
          return (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
      }
      
      bool definitelyLessThan(float a, float b, float epsilon)
      {
          return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
      }

      // Choosing epsilon depends on the context, and how close you want the numbers to be.
      // basically you can just write this
      bool floatEqualWithEpsilon(float a, float b, float epsilon)
      {
          return fabs(a - b) < epsilon;
      }