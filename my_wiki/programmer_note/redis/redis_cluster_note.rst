Redis Cluster Note
==================


#. start nodes

    ./redis-server ./7001/redis.conf
    ./redis-server ./7002/redis.conf
    ./redis-server ./7003/redis.conf
    ./redis-server ./8001/redis.conf
    ./redis-server ./8002/redis.conf
    ./redis-server ./8003/redis.conf

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

