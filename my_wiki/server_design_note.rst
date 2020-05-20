Server Design Note
==================

#. Resolutions for Service Avalanche Effect

    There are different solutions for different causes of Service Avalanche:

        Traffic control
        Improve cache model
        Service auto-scale
        Service caller fallback

#. rate limit method

    - 计数器

    - 漏桶(Leaky Bucket)算法思路：水(请求)先进入到漏桶里,漏桶以一定的速度出水(接口有响应速率),
      当水流入速度过大会直接溢出(访问频率超过接口响应速率), 然后就拒绝请求。

    - 令牌桶算法(Token Bucket)和 Leaky Bucket 效果一样但方向相反的算法,更加容易理解.随着时间流逝,
      系统会按恒定 1/QPS 时间间隔往桶里加入Token,如果桶已经满了就不再加了。新请求来临时,
      会各自拿走一个Token,如果没有Token可拿了就阻塞或者拒绝服务.

#. Consistent Hashing

    In computer science, consistent hashing is a special kind of hashing
    such that when a hash table is resized, only n/m keys need to be remapped
    on average where n is the number of keys and m is the number of slots.

    In contrast, in most traditional hash tables, a change in the number of array slots
    causes nearly all keys to be remapped because the mapping between the keys and the slots
    is defined by a modular operation.
