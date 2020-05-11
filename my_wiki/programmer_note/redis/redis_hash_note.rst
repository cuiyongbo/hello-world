Redis Hashes Note
=================

Every hash can store up to :math:`2^{32}-1` field-value pairs.

Command list:

   - hget, hset
   - hgetall, hmset, hsetnx
   - hexists, hdel
   - hincrby, hincrbyfloat
   - hkeys, hvals, hlen

Refer to ``help @hash`` for futher information.

.. code-block:: sh

    127.0.0.1:6379> HMSET user:1000 name cyb age 27
    OK
    127.0.0.1:6379> HGET user:1000 name
    "cyb"
    127.0.0.1:6379> HSET user:1000 sex male
    (integer) 1
    127.0.0.1:6379> HGETALL user:1000
    1) "name"
    2) "cyb"
    3) "age"
    4) "27"
    5) "sex"
    6) "male"
    127.0.0.1:6379> hkeys user:1000
    7) "name"
    8) "age"
    9) "sex"
    127.0.0.1:6379> HVALS user:1000
    10) "cyb"
    11) "27"
    12) "male"
    127.0.0.1:6379> HLEN user:1000
    (integer) 313)
