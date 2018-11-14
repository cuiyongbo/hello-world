**************
Hash Functions
**************

Hashing generally takes records whose key values come from a large range
and stores those records in a table with a relatively small number of slots.
**Collisions** occur when two records hash to the same slot in the table.
If we are careful — or lucky — when selecting a hash function, then the actual
number of collisions will be few. Unfortunately, even under the best of circumstances,
collisions are nearly unavoidable.

.. image:: images/hash_collision.png

We would like to pick a hash function that stores the actual records in the collection such that each slot
in the hash table has equal probablility of being filled. Unfortunately, we normally have no control over
the key values of the actual records, **so how well any particular hash function does depends on the distribution
of the keys within the allowable key range.** 

When designing hash functions, we are generally faced with one of two situations:

   #. We know nothing about the distribution of the incoming keys.
      In this case, we wish to select a hash function that evenly
      distributes the key range across the hash table, while avoiding
      obvious opportunities for clustering such as hash functions that
      are sensitive to the high- or low-order bits of the key value.
     
   #. We know something about the distribution of the incoming keys. 
      In this case, we should use a distribution-dependent hash function
      that avoids assigning clusters of related key values to the same
      hash table slot. For example, if hashing English words, we should
      not hash on the value of the first character because this is likely
      to be unevenly distributed.
     
Next, you will see several examples of hash functions that illustrate these points.


Simple Modulus Method
=====================

Consider the following hash function used to hash integers to a table of 16 slots::

   int hash(int x) 
   {
     return x % 16;
   }

Recall that the values 0 to 15 can be represented with four bits (i.e., 0000 to 1111). 
The value returned by this hash function depends solely on the least significant four bits 
of the key. Because these bits are likely to be poorly distributed. As an example, a high 
percentage of the keys might be even numbers, which means that the low order bit is zero, 
the result will also be poorly distributed.


Binning Method
==============

Say we are given keys in the range 0 to 999, and have a hash table of size 10. 
In this case, a possible hash function might simply divide the key value by 100. 
Thus, all keys in the range 0 to 99 would hash to slot 0, keys 100 to 199 would 
hash to slot 1, and so on. In other words, this hash function "bins" the first 100 
keys to the first slot, the next 100 keys to the second slot, and so on.

"Binning" in this way has the problem that it will cluster together keys if the 
distribution does not divide evenly on the high-order bits. In the above example, 
if more records have keys in the range 900-999 (first digit 9) than ones have keys in 
the range 100-199 (first digit 1), more records will hash to slot 9 than to slot 1. 
(A similar, analogous problem arises if we were instead hashing strings based on the 
first letter in the string.)

Binning is like the inverse of the mod function: the mod function, for a power of two, 
looks at the low-order bits, while binning looks at the high-order bits. As another example, 
consider hashing a collection of keys whose values follow a normal distribution. Keys near the 
mean of the normal distribution are far more likely to occur than keys near the tails of the 
distribution. For a given slot, think of where the keys come from within the distribution. 
Binning would be taking thick slices out of the distribution and assign those slice to bins. 
If we use a hash table of size 16, we would divide the key range into 16 equal-width slices 
and assign each slice to a slot in the table. Since a normal distribution is more likely to 
generate keys from the middle slice, the middle slot of the table is most likely to be used. 
In contrast, if we use the mod function, then we are assigning to any given slot in the table 
a series of thin slices in steps of 16. In the normal distribution, some of these slices 
associated with any given slot are near the tails, and some are near the center. 
Thus, each table slot is equally likely (roughly) to get a key value.


Mid-Square Method
=================

A good hash function to use with integer key values is the **mid-square** method. The mid-square method
squares the key value, and then takes out the middle r bits of the result, giving a value in the range 0 
to :math:`2^r - 1`. This works well because most of all bits of the key value contribute to the result. 
For example, consider records whose keys are 4-digit numbers in base 10. The goal is to hash these key 
values to a table of size 100 (i.e., a range of 0 to 99). This range is equivalent to 2 digits in base 10.
That is, r = 2. If the input is the number 4567, squaring yields an 8-digit number, 20857489. The middle 
two digits of this result are 57. All digits of the original key value (equivalently, all bits when the 
number is viewed in binary) contribute to the middle two digits of the squared value. Thus, the result 
is not dominated by the distribution of the bottom digit or the top digit of the original key value. 
Of course, if the key values all tend to be small numbers, then their squares will only affect the 
low-order digits of the hash value.


Hash Functions for Strings
==========================

Now we will examine some hash functions suitable for storing strings of characters. 
We start with a simple summation function::

   int hashForString(string x, int M) 
   {
      int i, sum;
      for (sum=0, i=0; i < x.length(); i++) sum += x[i];
      return sum % M;
   }

This function sums the ASCII values of the letters in a string. If the hash table size **M** is small 
compared to the resulting summations, then this hash function should do a good job of distributing 
strings evenly among the hash table slots, because it gives equal weight to all characters in the 
string.  **Note that the order of the characters in the string has no effect on the result**. 
A similar method for integers would add the digits of the key value, assuming that there are enough 
digits to keep any one or two digits with bad distribution from skewing the results of the process 
and generate a sum much larger than **M**.

As with many other hash functions, the final step is to apply the modulus operator to the result, 
using table size **M** to generate a value within the table range. If the sum is not sufficiently 
large, then the modulus operator will yield a poor distribution. For example, because the ASCII 
value for "A" is 65 and "Z" is 90, sum will always be in the range 650 to 900 for a string of 10 
upper case letters. For a hash table of size 100 or less, a reasonable distribution results. 
For a hash table of size 1000, the distribution is terrible because only slots 650 to 900 can 
possibly be the home slot for some key value, and the values are not evenly distributed even 
within those slots.

Here is a much better hash function for strings:

.. code-block:: java

   // Use folding on a string, summed 4 bytes at a time
   long hashForStringWithFolding(string s, int M) 
   {
      long sum = 0;
      int intLength = s.length() / 4;
      for (int j = 0; j < intLength; j++) 
      {
          long mult = 1;
          char c[] = s.substring(j * 4, (j * 4) + 4).toCharArray();
          for (int k = 0; k < c.length; k++) 
          {
            sum += c[k] * mult;
            mult <<= 8;
          }
      }
      return(Math.abs(sum) % M);
   }

For example, if the string "aaaabbbb" is passed to *hashForStringWithFolding*, then the first four bytes ("aaaa") 
will be interpreted as the integer value ``416,611,827,615``, and the next four bytes ("bbbb") will be interpreted 
as the integer value ``420,906,794,910``. Their sum is ``837,518,622,525`` (when treated as an unsigned integer). 
If the table size is 101 then the modulus function will cause this key to hash to
slot 36 in the table. Note that for any sufficiently long string, the sum for the integer quantities will
typically cause a 32-bit integer to overflow (thus losing some of the high-order bits) because the 
resulting values are so large. But this causes no problems when the goal is to compute a hash function.