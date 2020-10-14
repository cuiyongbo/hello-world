Cache Terms
===========

#. Cache penetration

    Cache penetration is a scenario where **the data to be searched doesn't exist** at DB
    and the returned **empty result set is not cached** as well and hence every search for
    the key will hit the DB eventually. If a hacker tries to initiate some attack by
    launching lots of searches with such key, the underlying DB layer will be hit too
    often and may eventually be brought down.

    In such cases, there are a few mitigation plans.

        - also cache the empty result but set a short expiration time.

        - Using Bloom filter. Bloom filter is similar to hbase set which can be used to check
          whether a key exists in the data set. If it doesn't exists in the data set, then just return.

    If the searched key has high repeat rate, then can adopt the first solution.
    Otherwise if the searched key has low repeat rate and the searched keys are too many,
    can adopt the second solution to filter most of them first.

#. Cache breakdown

    Cache breakdown is a scenario where the cached data expires and at the same time there are
    lots of search on the expired data which suddenly cause the searches to hit DB directly and
    increase the load to the DB layer dramatically. Note that it differ from Cache avalanche in
    that the epxired data is not thay many.

    Normally in this case, there needs to be a lock on the searched key so that other threads need to
    wait when some thread is trying to search the key and update the cache. After the cache is updated 
    and lock is released, other threads will be able to read the newly cached data::

        if (memcache.get(key) == null) {
            // 3 min timeout to avoid mutex holder crash
            if (memcache.add(key_mutex, 3 * 60 * 1000) == true) {
                value = db.get(key);
                memcache.set(key, value);
                memcache.delete(key_mutex);
            } else {
                sleep(50);
                retry();
            }
        }

    Another feasible method is to asynchronously update the cached data through a worker thread
    so that the hot data will never expire. (force cache to update)

#. Cache avalanche

    Cache avalanche is a scenario where lots of cached data expire at the same time or
    the cache service is down and all of a sudden all searches of these data will hit DB
    and cause high load to the DB layer and impact the performance.

    To mitigate the problem, some methods can be adopted.

        - Using clusters like redis clusters to ensure that some cache server instance is in service at any point of time

        - Some other approaches like hystrix circuit breaker and rate limit can be configured so that
          the underlying system can still serve traffic and avoid high load

        -  Adjust the expiration time for different keys so that they will not expire at the same time.

#. Cache update strategy

    - Cache aside
    - Read through / Write through
    - Write behind

    .. note::

        In cache-aside, application updates the database directly synchronously. Whereas,
        a Write-behind lets your application quickly update the cache and return.
        Then it lets the cache update the database in the background.

.. rubric:: Footnotes

.. [#] `Cache terms <https://www.pixelstech.net/article/1586522853-What-is-cache-penetration-cache-breakdown-and-cache-avalanche>`_
.. [#] `Cache avalanche solutions <https://blog.csdn.net/weixin_33813128/article/details/92658963>`_
