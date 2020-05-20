Redis note
==========

Redis is an in-memory database that persists on disk. it is similar to memcached but
the dataset is not volatile, The data model is key-value, but many different kind of
values are supported: Strings, Lists, Sets, Sorted Sets, Hashes, Streams, HyperLogLogs,
Bitmaps.


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
    redis/redis_faq


2015年毕业于中南大学，目前已经工作5年，从事C++后端开发，技术栈集中在网络编程，多线程开发，nosql数据库，缓存设计。
目前在四维图新，负责路况数据的编译和发布，出行规划服务的设计和开发工作。

eta计算服务：实现路线的Eta计算，优化出行规划服务的的架构，减少代码重复，（限行政策，交通事件，沿途城市，沿途天气，沿路adas...)
服务器架构选型：组内实现的类nginx的多进程架构模型，传输协议采用http+json协议，快速原型开发，功能验证
性能优化：1. 网络架构
