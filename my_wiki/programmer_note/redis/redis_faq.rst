Redis FAQ
=========

#. Error condition on socket for SYNC: Connection refused

    An ugly solution: edit ``redis.conf`` change ``bind ipaddress`` to ``bind 0.0.0.0``
    to allow connections from any host.

#. Snapshotting

    By default Redis saves snapshots of the dataset on disk, in a binary file called ``dump.rdb``.
    Whenever Redis needs to dump the dataset to disk, this is what happens:

        - Redis ``forks``. We now have a child and a parent process.
        - The child starts to write the dataset to a temporary RDB file.
        - When the child is done writing the new RDB file, it replaces the old one.

    This method allows Redis to benefit from :abbr:`COW (copy-on-write)` semantics.

    .. code-block:: none
        :caption: SAVE directive

        ################################ SNAPSHOTTING  ################################
        #
        # Save the DB on disk: save <seconds> <changes>
        #
        #   Will save the DB if both the given number of seconds and the given
        #   number of write operations against the DB occurred.
        #
        #   For example:
        #       ``save 900 1`` means after 900 sec (15 min) if at least 1 key changed
        #       ``save 300 10` after 300 sec (5 min) if at least 10 keys changed
        #
        #   Note: you can disable saving completely by commenting out all "save" lines.
        #
        #   It is also possible to remove all the previously configured save
        #   points by adding a save directive with a single empty string argument
        #   like in the following example: ``save ""``

#. Data Consistency solution

    - cache expiration mechanism
    - delay double deletion strategy

        How to determine timeout; more write requests; still data inconsistency during timeout.

    - mysql binlog + asynchronous update cache (using message queue)
    - use Redis WAIT command to ensure Data consistency between master- slave replications

        WAIT makes sure that a write can wait for acknowledgment until multiple replicas
        confirm that write. This makes sure that a write confirmed with WAIT on replicas
        are durable even if a node catches on fire and never comes back to the cluster.

#. So far redis is not a single threaded program, ``bioInit()`` would start ``BIO_NUM_OPS`` threads to do background I/O jobs.

.. rubric:: Footnotes

.. [#] `如何更有效的处理数据检索缓存 <https://mp.weixin.qq.com/s/upNsmiPdqxkr-2ZbGjk6fg>`_
.. [#] `Redis 数据一致性解决方案 <https://developpaper.com/redis-cache-and-mysql-data-consistency-scheme-details/>`_
.. [#] `Consistency and Durability <https://docs.redislabs.com/latest/rs/concepts/data-access/consistency-durability/>`_
.. [#] `top 10 message queue libraries <https://dingyuliang.me/mq-best-10-message-queue-open-source-libraries/>`_
.. [#] `Distributed cache related articals <https://www.163yun.com/search/5YiG5biD5byP57yT5a2Y5LiA6Ie05oCn>`_
