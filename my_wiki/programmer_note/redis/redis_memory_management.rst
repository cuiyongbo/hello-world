Redis Memory Management Note
============================

Basically speaking, Redis manages memory using **reference counting**.
the basic structure can be found:

.. code-block:: c

    #define LRU_BITS 24
    #define OBJ_SHARED_REFCOUNT INT_MAX
    typedef struct redisObject {
        unsigned type:4;
        unsigned encoding:4;
        unsigned lru:LRU_BITS; /* LRU time (relative to global lru_clock) or
                                * LFU data (least significant 8 bits frequency
                                * and most significant 16 bits access time). */
        int refcount;
        void *ptr;
    } robj;


There are serval data structures in redis:

    - SDS (Simple Dynamic String) (string command)
    - ADList ( A general doubly linked List)
    - skiplist
    - ziplist
    - quicklist (list command)
    - dict
