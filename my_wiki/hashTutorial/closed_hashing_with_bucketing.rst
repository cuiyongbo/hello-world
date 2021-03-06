****************************************
Section 4  Closed Hashing with Bucketing
****************************************

Closed hashing (aka Open addressing) stores all records directly in the hash table.
Each record *R* with key value :math:`k_R` has a home position
that is h(:math:`k_R`), the slot computed by the hash function.
If *R* is to be inserted and another record already occupies R's
home position, then *R* will be stored at some other slot in the
table. It is the business of the collision resolution policy to
determine which slot that will be. Naturally, the same policy
must be followed during search as during insertion, so that any
record not found in its home position can be recovered by repeating
the collision resolution process.

One implementation for closed hashing groups hash table slots into buckets.
The *M* slots of the hash table are divided into *B* buckets, with each bucket
consisting of M/B slots. The hash function assigns each record to the first
slot within one of the buckets. If this slot is already occupied, then the
bucket slots are searched sequentially until an open slot is found. If a bucket
is entirely full, then the record is stored in an overflow bucket of infinite
capacity at the end of the table. **All buckets share the same overflow bucket**.
A good implementation will use a hash function that distributes the records
evenly among the buckets so that as few records as possible go into the
overflow bucket.

When searching for a record, the first step is to hash the key to determine
which bucket should contain the record. The records in this bucket are then
searched. If the desired key value is not found and the bucket still has free
slots, then the search is done. If the bucket is full, then it is possible
that the desired record is stored in the overflow bucket. In this case, the
overflow bucket must be searched until the record is found or all records
in the overflow bucket have been checked. If there are many records in the
overflow bucket, this will be an expensive process.

A simple variation on bucket hashing is to hash a key value to some slot
in the hash table as though bucketing were not being used. If the home
position is full, then the collision resolution process is to move down
through the table toward the end of the bucket while searching for a free
slot in which to store the record. If the bottom of the bucket is reached,
then the collision resolution routine wraps around to the top of the bucket
to continue the search for an open slot. For example, assume that buckets
contain eight records, with the first bucket consisting of slots 0 through 7.
If a record is hashed to slot 5, the collision resolution process will
attempt to insert the record into the table in the order 5, 6, 7, 0, 1, 2, 3,
and finally 4. If all slots in this bucket are full, then the record is assigned
to the overflow bucket. The advantage of this approach is that initial collisions
are reduced, Because any slot can be a home position rather than just the first
slot in the bucket.

**Bucket methods are good for implementing hash tables stored on disk**,
because the bucket size can be set to the size of a disk block. Whenever
search or insertion occurs, the entire bucket is read into memory. Because
the entire bucket is then in memory, processing an insert or search operation
requires only one disk access, unless the bucket is full. If the bucket is
full, then the overflow bucket must be retrieved from disk as well.
Naturally, overflow should be kept small to minimize unnecessary disk accesses.
