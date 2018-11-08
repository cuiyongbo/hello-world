*************
Hash Tutorial
*************

**Section 1 - Introduction**

Hashing is a method for storing and retrieving records from a database.
It lets you insert, delete, and search for records based on a search
key value. When properly implemented, these operations can be performed
in constant time. This is far better than the :math:`O(\log n)` average cost required to do
a binary search on a sorted array of n records, or the :math:`O(\log n)`
average cost required to do an operation on a binary search tree.

A hash system stores records in an array called a **hash table**, which
we will call **HT**. Hashing works by performing a computation on a search
key *K* in a way that is intended to identify the position in HT that contains
the record with key K. The function that does this calculation is called the
**hash function**, and will be denoted by the letter *h*. Since hashing schemes
place records in the table in whatever order satisfies the needs of the address
calculation, records are not ordered by value. A position in the hash table is
also known as a **slot**. The number of slots in hash table HT will be denoted
by the variable **M** with slots numbered from 0 to :math:`M - 1`.

The goal for a hashing system is to arrange things such that, for any key value *K*
and some hash function *h*, **i = h(K)** is a slot in the table such that :math:`0 <= i < M`,
and *HT[i] = K*.

Hashing is not good for applications where multiple records with the same key
value are permitted. Hashing is not a good method for answering range searches.
In other words, we cannot easily find all records (if any) whose key values fall
within a certain range. Nor can we easily find the record with the minimum or
maximum key value, or visit the records in key order. 
**Hashing is most appropriate for answering the question, "What record, if any, has key value K?"** 
For applications where all search is done by exact-match queries, hashing
is the search method of choice because it is extremely efficient when
implemented correctly. As this tutorial shows, however, there are many approaches
to hashing and it is easy to devise an inefficient implementation. Hashing is
suitable for both in-memory and disk-based searching and is one of the two most
widely used methods for organizing large databases stored on disk (the other is the **B-tree**).

In most applications, there are many more values in the key range than there are
slots in the hash table, and we must devise a hash function that allows us to store the records in a much smaller table.
Because the key range is larger than the size of the table, at least some of the
slots must be mapped to from multiple key values. Given a hash function *h* and
two keys *k1* and *k2*, if :math:`h(k1) = β = h(k2)` where *β* is a slot in the
table, then we say that *k1* and *k2* have a **collision** at slot *β* under
hash function *h*.

Another introduction to hash table, see :download:`Introduction to hash table <hashTutorial/docs/hashing_introduction.pdf>`.


.. toctree::
   :maxdepth: 2

   hashTutorial/hash_function
   hashTutorial/open_hashing
   hashTutorial/bucket_hashing
   hashTutorial/collision_resolution
   hashTutorial/improved_collision_resolution_methods
   hashTutorial/closed_hashing_analysis
   hashTutorial/deletion
   hashTutorial/int_hash

