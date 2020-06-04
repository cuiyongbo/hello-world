Redis FAQ
=========

#. Error condition on socket for SYNC: Connection refused

    An ugly solution: edit ``redis.conf`` change ``bind ipaddress`` to ``bind 0.0.0.0``
    to allow connections from any host.

#. Data Consistency solution

    - cache expiration mechanism
    - delay double deletion strategy

        How to determine timeout; more write requests; still data inconsistency during timeout.

    - mysql binlog + asynchronous update cache (using message queue)
    - use Redis WAIT command to ensure Data consistency between master-slave replications

        WAIT makes sure that a write can wait for acknowledgement until multiple replicas
        confirm that write. This makes sure that a write confirmed with WAIT on replicas
        are durable even if a node catches on fire and never comes back to the cluster.

.. rubric:: Footnotes

.. [#] `如何更有效的处理数据检索缓存 <https://mp.weixin.qq.com/s/upNsmiPdqxkr-2ZbGjk6fg>`_
.. [#] `Redis 数据一致性解决方案 <https://developpaper.com/redis-cache-and-mysql-data-consistency-scheme-details/>`_
.. [#] `Consistency and Durability <https://docs.redislabs.com/latest/rs/concepts/data-access/consistency-durability/>`_
.. [#] `top 10 message queue libraries <https://dingyuliang.me/mq-best-10-message-queue-open-source-libraries/>`_
.. [#] `Distributed cache related articals <https://www.163yun.com/search/5YiG5biD5byP57yT5a2Y5LiA6Ie05oCn>`_
.. [#] `Redis FAQ <https://redis.io/topics/faq>`_
