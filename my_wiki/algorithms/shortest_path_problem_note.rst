*********************
Shortest path problem
*********************

In a **shortest-paths problem**, we are given a weighted, directed graph
:math:`G=(V, E),` with weight function :math:`w: E \rightarrow \mathbb{R}`
mapping edges to real-valued weights. The weight :math:`w(p)` of path 
:math:`p=\langle {v_0, v_1, \ldots, v_k} \rangle` 
is the sum of the weights of its constituent edges:

.. math::

    w(p) = \sum_{i=1}^k{w(v_{i-1}, v_i)}

We define the shortest-path weight :math:`\delta(u,v)` from u to v by

.. math::

    \delta(u,v)=
    \begin{cases}
    min\{w(p): u \xrightarrow{p} v\}, &\text{if there is a path from u to v} \\
    \infty, &\text{otherwise}
    \end{cases}

A **shortest path** from vertex u to vertex v is then defined as any path p 
with weight :math:`w(p)=\delta(u,v)`.

Optimal structure for a shortest path: **Subpaths of shortest paths are shortest paths.** 

.. code-block:: none
    :caption: Bellman Ford Algorithm implementation

    Initialize-Single-Source(G, s)
        for each vertex v in G.v
            v.d = inf
            v.p = NIL
        s.d = 0

    Relax(u, v, w)
        if v.d > u.d + w(u, v)
            v.d = u.d + w(u, v)
            v.p = u

    Bellman-Ford(G, w, s)
        Initialize-Single-Source(G, s)
        for i=1 to len(G.v)-1
            for each edge (u,v) in G.E
                Relax(u, v, w)
        for each edge (u, v) in G.E
            if v.d > u.d + w(u, v)
                return False
        return True

.. code-block:: none

    # DAG stands for Directed Acycle Graph
    DAG-Shortest-Paths(G, w, s)
        topologically sort G.V
        Initialize-Single-Source(G, s)
        for each vertex u, taken in topologically sorted order
            for each vertex v in G.Adj[u]
                Relax(u, v, w)

.. code-block:: none
    :caption: Dijkstra Algorithm implementation

    # Dijkstra's algorithm solves the single-source shortest-paths 
    # problem on a weighted, directed graph G=(V,E) for the case in
    # which all edge weights are nonnegative.

    Dijkstra(G, w, s)
        Initialize-Single-Source(G, s)
        S = emptySet
        Q = G.V # establish a min-priority queue keyed on v.d
        while not isEmpty(Q)
            u = Extract-Min(Q)
            S.union(u)
            for each vertex v in G.Adj[u]
                Relax(u, v, w) // implicity call Decrease-Key if v.d is updated
