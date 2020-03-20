******************
Depth First Search
******************

.. code-block:: none
    :caption: Taken from *Introduction to Algorithms*

    # \Theta(V+E)
    DFS(G)
        for each vertex u in G.V
            u.color = WHITE
            u.p = NIL # predecessor
        time = 0 # global variable used for timestamp
        for each vertex u in G.V
            if u.color == WHITE
                DFS-Visit(G, u)

    DFS-Visit(G, u)
        time = time + 1
        u.d = time # discovery time
        u.color = GRAY
        for each vertex v in G.Adj[u]
            if v.color == WHITE
                v.p = u
                DFS-Visit(G, v)
        u.color = BLACK
        time = time + 1
        u.f = time # finishing time

    TOPOLOGICAL-SORT(G)
        call DFS(G) to compute finishing times f for each vertex
        as each vertex is finished, insert it onto the front of a linked list
        return the linked list of vertices

:abbr:`SCC (Strongly Connected Component)` : a SCC of a directed graph **G(V, E)** is a maximal set
of vertices :math:`C \in V` such that for every pair of vertices u and v in C , we have :math:`u \rightleftharpoons v`.

.. code-block:: none

    call DFS(G) to compute finishing times u.f for each vertex u
    compute the transpose of G (G.T)
    call DFS(G.T), but in the main loop of DFS, consider
        the vertices in order of decreasing u.f
    Output the vertices of each tree in the depth-first forest as
        a separate strongly connected component

#. Tarjan's algorithm - a procedure for finding SCCs of a directed graph.

    .. code-block:: none
        :caption: Algorithm pesudocode taken from wiki

        index = 0
        S = empty stack
        scc_list = empty list

        tarjanAlgorithm(G)
            for u in G.V
                if v is not visited
                    strongConnect(G, u)

        strongConnect(G, u)
            u.index = index     // index defined by DFS order
            u.lowlink = index   // the smallest index of node reachable from v, including v itself.
            index += 1
            S.push(u)
            u.onStack = true
            for v in G.adj[u]
                if v is not visited
                    strongConnect(v)
                    u.lowlink = min(u.lowlink, v.lowlink)
                else if v.onStack
                    u.lowlink = min(u.lowlink, v.index)

            if u.lowlink == u.index
                scc = empty list
                do
                    v = S.pop()
                    v.onStack = false
                    scc.add(v)
                while(u != v)
                scc_list.add(scc)

#. Leetcode exercises

    - Friend circles
    - Smallest String With Swaps (Connected Component)
    - Critical Connections in a Network (SCC)
