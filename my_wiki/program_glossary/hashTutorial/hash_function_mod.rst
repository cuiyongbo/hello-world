Section 2.1 - Simple Modulus Function
=====================================

Consider the following hash function used to hash integers to a table of sixteen slots:

.. code-block:: c

   int hash(int x) 
   {
     return x % 16;
   }

Recall that the values 0 to 15 can be represented with four bits (i.e., 0000 to 1111). The value returned by this hash function depends solely on the least significant four bits of the key. Because these bits are likely to be poorly distributed. As an example, a high percentage of the keys might be even numbers, which means that the low order bit is zero, the result will also be poorly distributed. This example shows that the size of the table M can have a big effect on the performance of a hash system because the table size is typically used as the modulus to ensure that the hash function produces a number in the range 0 to M-1.
