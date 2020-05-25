Server Design Note
==================

#. Shorten that long URL into a tiny URL

    Purpose: ease the cost to type a longer url, hide url parameters from users.
    Note:

        - length of target url
        - hash conflicts resolution
        - expiration mechanism

    Examples: TinyURL

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

    when considering weight, the node with more weight will generate more virtual nodes.

#. :abbr:`DBSCAN (Density-based spatial clustering of applications with noise)`

    DBSCAN requires two parameters: :math:`\epsilon (eps)` and the minimum number of points required to
    form a dense region (minPts). It starts with an arbitrary starting point that has not been visited.
    This point's :math:`\epsilon`-neighborhood is retrieved, and if it contains sufficiently many points,
    a cluster is started. Otherwise, the point is labeled as noise.

    If a point is found to be a dense part of a cluster, its :math:`\epsilon`-neighborhood is also part
    of that cluster. Hence, all points that are found within the :math:`\epsilon`-neighborhood are added,
    as is their own :math:`\epsilon`-neighborhood when they are also dense.
    This process continues until the density-connected cluster is completely found. Then, a new unvisited
    point is retrieved and processed, leading to the discovery of a further cluster or noise.

    DBSCAN can be used with any distance function as well as similarity functions or other predicates.

    .. code-block:: none

        DBSCAN(DB, distFunc, eps, minPts)
        {
            C = 0 /* Cluster counter */
            foreach P in DB
            {
                /* Previously processed in inner loop */
                if(label(P) != undefined)
                    continue

                Neighbors N = RangeQuery(DB, distFunc, P, eps)
                if(N.size() < minPts)
                {
                    label(P) = Noise /* Label as Noise */
                    continue
                }

                C = C + 1
                label(P) = C /* Label initial point */
                Seed set S = N - {P} /* Neighbors to expand */
                foreach point Q in S
                {
                    if(label(Q) = Noise) label(Q) = C
                    if (label(Q) != undefined) continue

                    label(Q) = C

                    Neighbors N = RangeQuery(DB, distFunc, Q, eps)
                    if(N.size() >= minPts)
                        S = S + N
                }
            }
        }

        RangeQuery(DB, distFunc, Q, eps)
        {
            Neighbors = empty list
            foreach P in DB
            {
                if(distFunc(Q, P) <= eps)
                    Neighbors = Neighbors + { P }
            }
            return Neighbors
        }

#. GeoHash
