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
