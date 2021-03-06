**********************
Section 3 Open Hashing
**********************

While the goal of a hash function is to minimize collisions,
some collisions are unavoidable in practice. Thus, hashing
implementations must include some form of collision resolution
policy. Collision resolution techniques can be broken into two
classes: **open hashing** (also called separate chaining) and
**closed hashing** (also called open addressing). (Yes, it is
confusing when "open hashing" means the opposite of "open addressing,"
but unfortunately, that is the way it is.) *The difference between
the two has to do with whether collisions are stored outside
the table (open hashing), or whether collisions result in storing
one of the records at another slot in the table (closed hashing)*.
Open hashing is treated in this section, and closed hashing in
:doc:`Closed hashing with bucketing <closed_hashing_with_bucketing>`
and :doc:`Closed hashing without bucketing <closed_hashing_without_bucketing>`.

The simplest form of open hashing defines each slot in the hash table
to be the head of a linked list. All records that hash to a particular
slot are placed on that slot's linked list. The figure illustrates a hash
table where each slot stores one record and a link pointer to the rest of
the list.

.. image:: images/OpenHash.png

Records within a slot's list can be ordered in several ways: by insertion order,
by key value order, or by frequency-of-access order. Ordering the list by key
value provides an advantage in the case of an unsuccessful search, because we
know to stop searching the list once we encounter a key that is greater than
the one being searched for. If records on the list are unordered or ordered
by frequency, then an unsuccessful search will need to visit every record on
the list.

Given a table of size *M* storing *N* records, the hash function will (ideally)
spread the records evenly among the M positions in the table, yielding on
average N/M records for each list. Assuming that the table has more slots
than there are records to be stored, we can hope that few slots will contain
more than one record. In the case where a list is empty or has only one record,
a search requires only one access to the list. However, if clustering causes many records to hash to only
a few of the slots, then the cost to access a record will be much higher because
more elements on the linked list must be searched.

**Open hashing is most appropriate when the hash table is kept in main memory,
with the lists implemented by a standard in-memory linked list.** Storing an
open hash table on disk in an efficient way is difficult, because members
of a given linked list might be stored on different disk blocks. This
would result in multiple disk accesses when searching for a particular key
value, which defeats the purpose of using hashing.

Known Applications:

    - Jansson.json_object_t.hashtable_t
