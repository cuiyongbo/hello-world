********************
Breadth-first search
********************


.. code-block:: none
    :caption: Taken from *Introduction to Algorithms*

    # The breadth-first-search procedure BFS below assumes
    # that the input graph G = (V, E) is represented using
    # adjacency lists. and we can refer to the adjacency list
    # of a vetex u in G.V with `G.Adj[u]`.
    # referer to `Ch22.1 representations of Graph` for further information.

    # O(V+E)
    BFS(G, s)
        for each vertex u in G.V
            u.color = WHITE
            u.d = inf # distance
            u.p = NIL # predecessor
        s.color = GRAY
        s.d = 0
        initial Q to empty # a first-in, first-out queue
        Enqueue(Q, s)
        # invariant: Q consists of the set of gray vertice
        while not isEmpty(Q):
            u = Dequeue(Q)
            for each v in G.Adj[u]
                if v.color == WHITE
                    v.color = GRAY
                    v.d = u.d + 1
                    v.p = u
                    Enqueue(Q, v)
            u.color = BLACK

    PrintPath(G, s, v)
        if v==s
            print s
        elseif v.p == NIL
            print "no path from" s "to" v "exists"
        else
            PrintPath(G, s, v.p)
            print v

#. leetcode exercise

    - Is Graph Bipartite
    - As Far from Land as Possible
