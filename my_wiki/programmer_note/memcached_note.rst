Memcached Note
==============

memcached is a **distributed memory object caching system**,
generic in nature, but originally intended for use in speeding up dynamic
web applications by alleviating database load.

You can think of it as a **short-term memory** for your applications.

Also note that Memcached on its own is simply a key/value store daemon.
Installing it does not automatically accelerate or cache any of your data:
**Your applications need to be programmed to utilize the service.**

The key features of Memcached are as follows −

   - Memcached server is a big hash table.
   - It significantly reduces the database load
   - It is perfectly efficient for websites with high database load.
   - It is a client-server application over TCP or UDP.

Memcached is not −

   - a persistent data store
   - a database
   - application-specific
   - a large object cache
   - fault-tolerant or highly available


.. toctree::

    memcached/memcached_introduction
    memcached/memcached_design_philosophy
    memcached/memcached_faq


.. rubric:: Footnotes

.. [#] `Memcached repository <https://github.com/memcached/memcached.git>`_
.. [#] `Memcached Wiki repository <https://github.com/memcached/memcached.wiki.git>`_
.. [#] `libmemcached <https://github.com/whupro2017/libmemcached.git>`_
