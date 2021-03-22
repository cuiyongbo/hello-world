Redis Sort Command
==================

.. code-block:: bash
    :caption: Command help

    127.0.0.1:6379> help sort
    SORT key [BY pattern] [LIMIT offset count] [GET pattern [GET pattern ...]] [ASC|DESC] [ALPHA] [STORE destination]
    summary: Sort the elements in a list, set or sorted set
    since: 1.0.0
    group: generic

.. code-block:: bash
    :caption: Usage examples

    127.0.0.1:6379> rpush days 15 45 23 7 198 56
    (integer) 6
    127.0.0.1:6379> sort days
    1) "7"
    2) "15"
    3) "23"
    4) "45"
    5) "56"
    6) "198"
    127.0.0.1:6379> sort days desc
    1) "198"
    2) "56"
    3) "45"
    4) "23"
    5) "15"
    6) "7"
    127.0.0.1:6379> sort days alpha
    1) "15"
    2) "198"
    3) "23"
    4) "45"
    5) "56"
    6) "7"  

    # additional struct  
    127.0.0.1:6379> hset d-7 field 5
    (integer) 1
    127.0.0.1:6379> hset d-15 field 1
    (integer) 1
    127.0.0.1:6379> hset d-23 field 8
    (integer) 1
    127.0.0.1:6379> hset d-45 field 9
    (integer) 1
    127.0.0.1:6379> hset d-56 field 79
    (integer) 1
    127.0.0.1:6379> hset d-198 field 49
    (integer) 1

    # sort by external data
    127.0.0.1:6379> sort days by d-*->field
    1) "15"
    2) "7"
    3) "23"
    4) "45"
    5) "198"
    6) "56"
    127.0.0.1:6379> sort days by d-*->field get d-*->field
    1) "1"
    2) "5"
    3) "8"
    4) "9"
    5) "49"
    6) "79"