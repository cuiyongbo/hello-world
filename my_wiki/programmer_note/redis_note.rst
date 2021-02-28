Redis note
==========

:abbr:`Redis (Remote Dictionary Server)` is an in-memory database that persists on disk. it is similar to memcached but
the dataset is not volatile, The data model is key-value, but many different kind of
values are supported: Strings, Lists, Sets, Sorted Sets, Hashes, Streams, HyperLogLogs, Bitmaps.

.. toctree::

    redis/redis_string_note
    redis/redis_list_note
    redis/redis_hash_note
    redis/redis_set_note
    redis/redis_sorted_set_note
    redis/redis_cli_note
    redis/redis_cluster_note
    redis/redis_threaded_io_note
    redis/redis_event_loop_note
    redis/redis_persistence_note
    redis/redis_memory_management
    redis/redis_faq

.. rubric:: Footnotes

.. [#] `Redis Client <https://redis.io/clients>`_
.. [#] `The Little Redis Book <https://www.openmymind.net/2012/1/23/The-Little-Redis-Book/>`_
