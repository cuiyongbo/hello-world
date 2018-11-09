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

   hash_function_mod
   hash_function_bin
   hash_function_mid_square
   hash_function_string
   more_hash_function
   
