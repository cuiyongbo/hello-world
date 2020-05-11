Redis String Note
=================

String are the most basic kind of Redis value.
Redis Strings are binary safe, this means that
a Redis String can contain any kind of data,
for instance a JPED image or a serialized Ruby object.

Command list:

    - get, set, getset, strlen
    - mget, mset
    - incr, decr
    - incrby, decrby
    - append
    - getrange, setrange
    - getbit, setbit, bitcount
