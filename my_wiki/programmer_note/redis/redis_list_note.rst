Redis List Note
===============

Redis list is implemented via **Linked List**.

Command list:

    - lpush, rpush
    - lpop, rpop
    - blpop, brpop # b means blocking
    - lrange, ltrim
    - llen # the key no longer exists after all the elements are popped
    - rpoplpush, brpoplpush
    - lset, lrem

#. Pattern: Reliable queue

    rpoplpush can be used to implement a safer queue,
    because the operation is atomic.

    Synposis: ``RPOPLPUSH source destination``

    similar to  ``val = rpop source; lpush destination val``
    but differs in that RPOPLPUSH operation is atomic.
    Because of this, RPOPLPUSH can be used to implement a safer queue.

#. Pattern: Circular list

    Using RPOPLPUSH with the same source and destination key,
    a client can visit all the elements of an N-elements list,
    one after the other, in O(N) without transferring the
    full list from the server to the client using a single
    LRANGE operation. this works even there are multiple clients
    operating on the list.
