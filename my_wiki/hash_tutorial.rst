*******************
Hash Table Tutorial
*******************

**Hash table** is a data structure supporting dictionary operations: **search, insert, and delete.**
and it requires :math:`O(1)` time for such operations(**insert and delete in doubt**) in *average-case time.*
Hash table is typically used in case where the keys to store split in a large range, but the
number of keys is much less relative to the range. When storing a key K, it first uses **hash function** h
to calculate the **hash value** h(K) of K, which identifies the slot to store K in the table.
However, two keys may end up with the same hash value, we call this situation a **collision**.
when a collision happens, we take certain collision resolution method, such as chaining, open addressing to resolve it.

**Hashing is most appropriate for answering the question, "What record, if any, has key value K?"**
For applications where all search is done by exact-match queries, hashing
is the search method of choice because it is extremely efficient when
implemented correctly. Hashing is suitable for both in-memory and disk-based searching and
is one of the two most widely used methods for organizing large databases stored on disk (the other is the **B-tree**).

Hashing is not good for applications where multiple records with the same key
value are permitted, nor for answering range searches. Neighter can we easily find the
record with the minimum or maximum key value, nor visit the records in key order.

Another introduction to hash table, see :download:`Introduction to hash table <hashTutorial/docs/hashing_introduction.pdf>`.

.. toctree::
    :titlesonly:

    hashTutorial/hash_function
    hashTutorial/more_hash_function
    hashTutorial/open_hashing
    hashTutorial/closed_hashing_with_bucketing
    hashTutorial/closed_hashing_without_bucketing
    hashTutorial/improved_collision_resolution_methods
    hashTutorial/closed_hashing_analysis
    hashTutorial/deletion
