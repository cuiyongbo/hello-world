Redis Sorted Set Note
=====================

Redis Sorted Sets are, simlilar to Redis Set,
non repeating collections of Strings. The difference
is that every member of a sorted set is associated with
a *score*, which is used to sort the set in acending order.
while members are unique, scores may be repeated.

Command list:

    - zadd, zincrby
    - zcard, zcount
    - zscore, zrank, zrevrank
    - zrange, zrevrange
    - zrangebyscore, zrevrangebyscore
    - zrem, zremrangebyrank, zremrangebyscore
    - zunionstore, zinterstore

Refer to ``help @sorted_set`` for further information.

.. code-block:: sh

    127.0.0.1:6379> zadd hackers 1957 'sophie wilson'
    127.0.0.1:6379> zadd hackers 1953 'richard stallman'
    127.0.0.1:6379> zadd hackers 1949 'anita borg'
    127.0.0.1:6379> zadd hackers 1965 'yukihiro matsumoto'
    127.0.0.1:6379> zadd hackers 1914 'hedy lamarr'
    127.0.0.1:6379> zadd hackers 1916 'claude shannon'
    127.0.0.1:6379> zadd hackers 1969 'linus torvalds'
    127.0.0.1:6379> zadd hackers 1912 'alan turing'

    127.0.0.1:6379> zcard hackers
    (integer) 9
    127.0.0.1:6379> ZRANGE hackers 0 -1
    1) "alan turing"
    2) "hedy lamarr"
    3) "claude shannon"
    4) "alan kay"
    5) "anita borg"
    6) "richard stallman"
    7) "sophie wilson"
    8) "yukihiro matsumoto"
    9) "linus torvalds"
    127.0.0.1:6379> ZREVRANGE hackers 0 -1 # in reverse order
    1) "linus torvalds"
    2) "yukihiro matsumoto"
    3) "sophie wilson"
    4) "richard stallman"
    5) "anita borg"
    6) "alan kay"
    7) "claude shannon"
    8) "hedy lamarr"
    9) "alan turing"
    127.0.0.1:6379> ZREVRANGE hackers 0 -1 withscores
     1) "linus torvalds"
     2) "1969"
     3) "yukihiro matsumoto"
     4) "1965"
     5) "sophie wilson"
     6) "1957"
     7) "richard stallman"
     8) "1953"
     9) "anita borg"
    10) "1949"
    11) "alan kay"
    12) "1940"
    13) "claude shannon"
    14) "1916"
    15) "hedy lamarr"
    16) "1914"
    17) "alan turing"
    18) "1912"
    127.0.0.1:6379> ZRANGEBYSCORE hackers -inf 1950
    1) "alan turing"
    2) "hedy lamarr"
    3) "claude shannon"
    4) "alan kay"
    5) "anita borg"
