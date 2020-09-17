Redis Cluster Note
==================

The ``redis-cli cluster`` support is very basic so it always uses the fact
that Redis Cluster nodes are able to redirect a client to the right node.
A serious client is able to do better than that, and cache the map between
hash slots and nodes addresses, to directly use the right connection to the right node.
The map is refreshed only when something changed in the cluster configuration,
for example after a failover or after the system administrator changed the cluster
layout by adding or removing nodes.

#. start nodes:

    .. code-block:: sh
        :caption: minimal Redis cluster configure file

        port 7000
        cluster-enabled yes
        cluster-config-file nodes.conf
        cluster-node-timeout 5000
        appendonly yes

    and start node: ``../redis-server redis.conf``

#. cluster meet

    ./redis-cli -p 7001
    127.0.0.1:7001> CLUSTER MEET 127.0.0.1 7002
    OK
    127.0.0.1:7001> CLUSTER MEET 127.0.0.1 7003
    OK
    127.0.0.1:7001> CLUSTER MEET 127.0.0.1 8001
    OK
    127.0.0.1:7001> CLUSTER MEET 127.0.0.1 8002
    OK
    127.0.0.1:7001> CLUSTER MEET 127.0.0.1 8003

#. assign slot

    ./redis-cli -p 7001 cluster addslots {0..5461}
    ./redis-cli -p 7002 cluster addslots {5462..10922}
    ./redis-cli -p 7003 cluster addslots {10933..16383}

#. replication

    ./redis-cli -p 8001 cluster replicate 09fd54be922da9ab74213de86f1379ca2bb0519f
    ./redis-cli -p 8002 cluster replicate 49b0b4c916dc6529e589fd367049151cbd74c54b
    ./redis-cli -p 8002 cluster replicate dbd11e21363972684eb52bbb9bfcb67acc537b1a

#. create cluster

    .. code-block:: sh

        ./redis-cli --cluster create 127.0.0.1:7001 127.0.0.1:7002 127.0.0.1:7003 \
        127.0.0.1:8001 127.0.0.1:8002 127.0.0.1:8003 \
        --cluster-replicas 1

        # --cluster-replicas 1 means one slave for each master
        # The redis-cli utility implements basic cluster support when started with the -c switch.

#. inspect cluster node information

    .. code-block:: sh

        $ ./redis-cli -p 7000 cluster nodes
        b43684c40c1b42a80430a0249e9f87722600fb1e 127.0.0.1:7005@17005 slave 31109a1247cf8b130112c5a53d0ae4c752b77fd4 0 1590332522285 6 connected
        cc59c8237141cc75f3b9ad34622b092f34c45ed9 127.0.0.1:7000@17000 myself,master - 0 1590332521000 1 connected 0-5460
        06daec5d5b238b1be87f9a6ba0ccbb10a96ed893 127.0.0.1:7001@17001 master - 0 1590332521000 2 connected 5461-10922
        31109a1247cf8b130112c5a53d0ae4c752b77fd4 127.0.0.1:7002@17002 master - 0 1590332523295 3 connected 10923-16383
        d6b513eace19fabd9173cce02cdea1be155d834e 127.0.0.1:7003@17003 slave cc59c8237141cc75f3b9ad34622b092f34c45ed9 0 1590332521000 4 connected
        5ab511163bd89b1ecfe8c01265cddc4c7bc90eb1 127.0.0.1:7004@17004 slave 06daec5d5b238b1be87f9a6ba0ccbb10a96ed893 0 1590332521276 5 connected

        $ ./redis-cli -p 7000 cluster info
        cluster_state:ok
        cluster_slots_assigned:16384
        cluster_slots_ok:16384
        cluster_slots_pfail:0
        cluster_slots_fail:0
        cluster_known_nodes:6
        cluster_size:3
        ...

#. (error) CLUSTERDOWN Hash slot not served: ``./redis-cli --cluster fix ip:port``

#. Creating cluster [ERR] Node 127.0.0.1:7000 is not empty.

   Full Description: Creating cluster [ERR] Node 127.0.0.1:7000 is not empty.
   Either the node already knows other nodes (check with CLUSTER NODES) or
   contains some key in database 0.

    .. code-block:: sh

        $ ./redis-cli -p 7001
        127.0.0.1:7001> flushall
        OK
        127.0.0.1:7001> cluster reset
        OK
        127.0.0.1:7001> exit

#. Redis pidfile file not found

    Probable the permission problem, change ``pidfile`` to your home directory.

#. Resharding the cluster

    Resharding basically means to move hash slots from a set of nodes to another set of nodes,
    and like cluster creation it is accomplished using the redis-cli utility.

    To start a resharding just type: ``redis-cli --cluster reshard ip:port``

#. Why 16384 (:math:`2^{14}`) hash slots in redis cluster?

    Normal heartbeat packets carry the full configuration of a node, that can be
    replaced in an idempotent way with the old in order to update an old config.
    This means they contain the slots configuration for a node, in raw form,
    that uses 2k of space with 16k slots, but would use a prohibitive 8k of
    space using 65k slots.

    At the same time it is unlikely that Redis Cluster would scale to more than
    1000 master nodes because of other design tradeoffs. So 16k was in the right
    range to ensure enough slots per master with a max of 1000 masters, but a small
    enough number to propagate the slot configuration as a raw bitmap easily.

.. rubric:: Footnotes

.. [#] `Redis Cluster Tutorial <https://redis.io/topics/cluster-tutorial>`_
.. [#] `Install ruby client <https://blog.whsir.com/post-2659.html>`_
.. [#] https://blog.csdn.net/zhoujian_Liu/article/details/80866415
.. [#] https://www.cnblogs.com/yaoyangding/p/12097806.html
.. [#] https://www.cnblogs.com/esofar/p/10486621.html
