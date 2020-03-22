Memcached Design Philosophy
===========================

Memcached-based service consists of following components:

   - Client software, which is given a list of available memcached servers.
   - A client-based hashing algorithm, which chooses a server based on the "key".
   - Server software, which stores values with their keys into an internal hash table.
   - LRU, which determine when to throw out old data (if out of memory), or reuse memory.

#. Simple key/value store

#. Logic half in client, half in server

    Memcached on its own is simply a key/value store daemon.
    Installing it does not automatically accelerate or cache any of your data:
    **Your applications need to be programmed to utilize the service.**

#. Servers are disconnected from each other

    There is no communication between memcached servers.
    so no synchronization, no broadcasting, no replication.
    Cache invalidation is simplified, as clients delete or overwrite data
    on servers which own it directly.

#. Cache invalidation

    Rather than broadcasting changes to all available hosts,
    clients directly address the server holding the data to be invalidated.

#. O(1) execution

#. Forgetting is a Feature

    Memcached is, by default, a :abbr:`LRU (Least Recently Used)` cache.
    Items expire after a specified amount of time.
