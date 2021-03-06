****************
Hackers' Delight
****************

#. Memory alignment

    find the least integer *c* to make ``c*b`` no less than *a*: 
    ``(size + alignment - 1) / alignment`` typically used for memory alignment.

    .. code-block:: c
        :caption: Taken from *fcgi* source code

        int AlignInt8(unsigned n) { return (n + 7) & (UINT_MAX - 7); }

#. Bit tricks

    Check if an unsigned integer x is a power of 2: ``x & (x-1)``
    0 means x is a power of 2, otherwise not. **Note** first check if x equals 0.
   
    Check if an unsigned integer x is of form :math:`2^{n} - 1:` ``x & (x+1)``
    0 means yes, otherwise not. This can also be used to turning off all trailing 1. 
    **Note** first check if x is 0 or UINT_MAX.
   
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
            n |= (n >> 1); // xx11xx
            n |= (n >> 2); // xx1111xx
            n |= (n >> 4); // xx1111111xx
            n |= (n >> 8); // xx11111111111111xx
            n |= (n >> 16); // set all the bits from highest order bit to the 0-th one to 1
            return n - (n >> 1);
        }   

#. Find the right most 1

   Use the formula to isolate the rightmost 1-bit: ``x & (-x)``, return 0 if none.

#. Negation

    The negation of a number a can be computed by ``~a + 1``.

#. Check :abbr:`NAN (not-a-number)`
   
    According to the *IEEE standard,* NaN values have the odd property that comparisons involving 
    them are always false. That is, for a float f, ``f != f`` will be true only if f is ``NaN.``
    **Note** that not all compilers respect this when optimizing code.

    .. code-block:: c

        #define IS_NAN(o) ((o) != (o))

#. Comparison of float or double numbers

    .. code-block:: cpp
        :caption: Taken from *The art of computer programming*

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

#. swap endian
   
    .. code-block:: c
        :caption: From CodeGuru

        inline void endian_swap(unsigned int& x)
        {
            x = (x>>24) | 
                ((x<<8) & 0x00FF0000) |
                ((x>>8) & 0x0000FF00) |
                (x<<24);
        }