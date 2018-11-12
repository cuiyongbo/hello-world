*************
Hash Function
*************

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

.. toctree::

   hash_function_mid_square
   hash_function_string
   more_hash_function
   

Simple Modulus Function
=======================

Consider the following hash function used to hash integers to a table of sixteen slots:

.. code-block:: c

   int hash(int x) 
   {
     return x % 16;
   }

Recall that the values 0 to 15 can be represented with four bits (i.e., 0000 to 1111). 
The value returned by this hash function depends solely on the least significant four bits 
of the key. Because these bits are likely to be poorly distributed. As an example, a high 
percentage of the keys might be even numbers, which means that the low order bit is zero, 
the result will also be poorly distributed.


Binning
=======

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

