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
