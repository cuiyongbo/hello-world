*********************
Minimus Spanning Tree
*********************

Minimus-spanning-tree problem: Assume that we have a connected, undirected graph :math:`G = (V, E)`
with a weight function :math:`w: E \rightarrow \mathbb{R}`, and we wish to find a spanning tree for G
with minimum weight.

.. code-block:: none

    // loop invariant: Prior to each iteration, A is a subset of some minimum spanning tree.
    Generic-MST(G, w)
        A = empty set
        while A does not form a spanning tree
            find an edge (u, v) that is safe for A
            A.union({(u, v)})
        return A

    MST-Kruskal(G, w)
        A = empty set
        for each vertex v in G.V
            Make-set(v)
        sort G.E into nondecreasing order by weight w
        for each edge (u,v) in G.E, taken in nondecreasing order by w
            if Find-Set(u) != Find-set(v)
                A.union((u, v))
                Union(u, v)
        return A

   MST-Prim(G, w, r)
      for each u in G.V
         u.key = inf
         u.p = NIL
      r.key = 0
      Q = G.V # build-min-heap comes here
      while not isEmpty(Q)
         u = Extract-Min(Q)
         for each v in G.adj[u]
            if v in Q and w(u, v) < v.key
               v.p = u
               v.key = w(u, v)
               # Decrease-key (Q, v) comes here

