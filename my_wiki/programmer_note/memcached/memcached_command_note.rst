Memcached Command Note
======================

#. Standard Protocol

    This stuff of memcached involves running a command against an item.
    An item consists of:

        - A key (arbitrary string up to 250 bytes in length. No space or newlines for ASCII mode)
        - A 32bit "flag" value
        - An expiration time, in seconds. '0' means never expire.
        - A 64bit "CAS" value, which is kept unique.
        - Arbitrary data

   .. note::

        CAS is optional (can be disabled entirely with ``-C``,
        and there are more fields that internally make up an item,
        but these are what your client interacts with.

#. Storage Commands

    .. code-block:: sh

        set key flags expire_time value_len [noreply]
        value

        add key flags expire_time value_len [noreply]
        value

        replace key flags expire_time value_len [noreply]
        value

        append key flags expire_time value_len [noreply]
        value

        prepend key flags expire_time value_len [noreply]
        value

        cas key flags expire_time value_len unique_cas_key [noreply]
        value

#. Retrieval Commands

    .. code-block:: sh

        get key
        gets key # also return cas value
        delete key [noreply]
        incr key increment_value
        decr key increment_value

#. Statistics

    .. code-block:: sh

        stats
        stats items
        stats slabs
        stats sizes
        flush_all [timeout] [noreply]

#. set

    Most common command. Store this data, possibly overwriting any existing data.
    New items are at the top of the LRU.

#. add

    Store this data, only if it does not already exist.
    New items are at the top of the LRU. If an item already
    exists and an add fails, it promotes the item to the front of the LRU anyway.

#. append

    Add this data after the last byte in an existing item.
    This does not allow you to extend past the item limit. Useful for managing lists.

#. prepend

    Same as append, but adding new data before existing data.

#. cas

    Check And Set (or Compare And Swap). An operation that stores data,
    but only if no one else has updated the data since you read it last.
    Useful for resolving race conditions on updating cache data.
