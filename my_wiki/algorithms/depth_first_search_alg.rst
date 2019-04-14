****************************
Depth-first Search Algorithm
****************************

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