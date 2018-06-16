**************************************
Single-precision floating-point format
**************************************

Overview
========

Single-precision floating-point format is a computer number format, 
usually occupying 32 bits in computer memory; it represents a wide 
dynamic range of numeric values by using a floating radix point.

A floating point variable can represent a wider range of numbers than 
a fixed point variable of the same bit width at the cost of precision. 
A signed 32-bit integer variable has a maximum value of :math:`2^31 − 1 = 2,147,483,647`, 
whereas an IEEE 754 32-bit base-2 floating-point variable has a maximum value of 
:math:`(2 − 2^{−23}) \times 2^{127} \approx 3.402823 \times 10^{38}`. All integers 
with 6 or fewer significant decimal digits, and any number that can be written as 
:math:`2^n` such that n is a whole number from -126 to 127, can be converted into 
an IEEE 754 floating-point value without loss of precision.


IEEE 754 single-precision binary floating-point format: binary32
================================================================

The IEEE 754 standard specifies a binary32 as having:

   * Sign bit: 1 bit
   * Exponent width: 8 bits
   * Significand precision: 24 bits (23 explicitly stored)
     
This gives from 6 to 9 significant decimal digits precision. 
If a decimal string with at most 6 significant digits is converted 
to IEEE 754 single-precision representation, and then converted back 
to a decimal string with the same number of digits, the final result 
should match the original string. If an IEEE 754 single-precision number 
is converted to a decimal string with at least 9 significant digits, and 
then converted back to single-precision representation, the final result 
must match the original number.

**Sign bit** determines the sign of the number, which is the sign of the 
significand as well. **Exponent** is either an 8-bit signed integer from
−128 to 127 (2's complement) or an 8-bit unsigned integer from 0 to 255, 
which is the accepted biased form in IEEE 754 binary32 definition. If 
the unsigned integer format is used, the exponent value used in the arithmetic 
is the exponent shifted by a bias – for the IEEE 754 binary32 case, an exponent 
value of 127 represents the actual zero (i.e. for 2^{e − 127} to be one, e must 
be 127). Exponents range from −126 to +127 because exponents of −127 (all 0s) 
and +128 (all 1s) are reserved for special numbers.

The true significand includes 23 **fraction bits** to the right of the binary point 
and an implicit leading bit (to the left of the binary point) with value 1, unless 
the exponent is stored with all zeros. Thus only 23 fraction bits of the significand 
appear in the memory format, but the total precision is 24 bits (equivalent to 
:math:`\log_{10}(2^{24}) \approx 7.225` decimal digits). The bits are laid out as follows:

.. image:: images/Float_example.svg

The real value assumed by a given 32-bit binary32 data with a given biased sign, 
exponent e (the 8-bit unsigned integer), and a 23-bit fraction is

.. math:: 

   { (-1)^{b_{31}} \times 2^{(b_{30}b_{29}\dots b_{23})_{2}-127}\times (1.b_{22}b_{21}\dots b_{0})_{2},}

which in decimal yields

.. math::

   {{\text{value}}=(-1)^{\text{sign}} \times 2^{(e-127)} \times (1+\sum_{i=1}^{23}b_{23-i}2^{-i}).}

In this example:

.. math::

   & {\text{sign}} = b_{31}=0, \\
   & {(-1)^{\text{sign}} = (-1)^{0}=+1 \in \{-1,+1\}}, \\
   & {e = \sum_{i=0}^{7}b_{23+i}2^{+i} = 124 \in \{1,\ldots ,(2^{8}-1)-1\}=\{1,\ldots ,254\}}, \\
   & {2^{(e-127)} = 2^{124-127} = 2^{-3} \in \{2^{-126},\ldots ,2^{127}\}}, \\
   & {1 + \sum_{i=1}^{23}b_{23-i}2^{-i} = 1 + 2^{-2} = 1.25 \in \{1,1+2^{-23},\ldots ,2-2^{-23}\} \subset [1;2)}.

thus:

.. math::

   {{\text{value}}=(+1) \times 1.25 \times 2^{-3} = +0.15625}.

Note:

.. math::

   {1+2^{-23} \approx 1.000\,000\,119}, \\
   {2-2^{-23}\approx 1.999\,999\,881}, \\
   {2^{-126} \approx 1.175\,494\,35 \times 10^{-38}}, \\
   {2^{+127} \approx 1.701\,411\,83 \times 10^{+38}}.
