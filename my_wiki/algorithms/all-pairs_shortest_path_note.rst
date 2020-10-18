****************************
All-pairs Shortest Path Note
****************************

.. note::

    Unlike the single-source algorithms, which assume an adjacency-list representation
    of the graph, most of the algorithms in this note use an **adjacency-matrix** representation if unspecified.

.. code-block:: none

    Print-All-Pairs-Shortest-Path(Matrix, i, j)
        if i == j
            print i
        else if Matrix[i][j] == NIL
            print "no path from " i " to " j " exists"
        else
            Print-All-Pairs-Shortest-Path(Matrix, i, Matrix[i][j])
            print j


.. code-block:: none
    :caption: Shortest paths and matrix multiplication

    Square-Matrix-Multiply(A, B)
        n = A.rows
        Let C be a new n x n matrix
        for i = 1 to n
            for j = 1 to n
                c[i][j] = 0
                for k = 1 to n
                    c[i][j] += a[i][k] * b[k][j]
        return C

    // Theta(n^3)
    Extend-Shortest-Paths(L, W)
        n = L.rows
        Let L' = (l'[i][j]) be a new n x n matrix
        for i = 1 to n
            for j = 1 to n
                l'[i][j] = inf
                for k = 1 to n
                    l'[i][j] = min(l'[i][j], l[i][k] + w[k][j])
        return L'

    // Theta(n^4)
    Slow-All-Pairs-Shortest-Paths(W)
        n = W.rows
        L^(1) = W
        for m = 2 to n-1
            let L^(m) be a new n x n matrix
            L^(m) = Extend-Shortest-Paths(L^(m-1), W)
        return L^(n-1)

    // Theta(n^3*lg(n))
    Faster-All-Pairs-Shortest-Paths(W)
        L^(1) = W
        m, n = 1, W.rows
        while m < n-1
            let L^(2m) be a new n x n matrix
            L^(2m) = Extend-Shortest-Paths(L^(m), L^(m))
            m *= 2
        return L^(m)

.. code-block:: py

    def matrix_product(L, W):
        n = len(W)
        new_L = [[float(0)] * n for i in range(n)]
        for i in range(n):
            for j in range(n):
                new_L[i][j] = float("inf")
                for k in range(n):
                    new_L[i][j] = min(new_L[i][j], L[i][k] + W[k][j])
        return new_L

    def fast_solution(W):
        L = W
        m, n = 1, len(W)
        while m < n-1:
            L = matrix_product(L, L)
            m = 2 * m
        return L

    def slow_solution(W):
        L = W
        n = len(W)
        for m in range(2, n):
            L = matrix_product(L, W)
        return L

    W = [[0,3,8,float("inf"),-4],
        [float("inf"),0,float("inf"),1,7],
        [float("inf"),4,0,float("inf"),float("inf")],
        [2,float("inf"),-5,0,float("inf")],
        [float("inf"),float("inf"),float("inf"),6,0]]

    >>> L2 = func(W, W)
    >>> L3 = func(L2, W)
    >>> L4 = func(L3, W)
    >>> L5 = func(L4, W)
    >>> L5 == L4
    True

    >>> fl = fast_solution(W)
    >>> fl == L4
    True
    >>> sl = slow_solution(W)
    >>> sl == fl
    True


:math:`d^{(k)}_{ij}` means weight of the shortest path from i to j
with all intermediate vertices are in the set :math:`\{ 1,2,\ldots,k \}`.

We define the **transitive closure** of G as the graph :math:`G^* = (V, E^*)`
where :math:`E^* = \{(i, j): \text{there is a path from vertex i to vertex j in G} \}.`

.. code-block:: none
    :caption: The Floyd-Warshall algorithm

    Floyd-Warshall(W)
        n = W.rows
        D^(0) = W
        for k = 1 to n
            let D^(k) be a new n x n matrix
            for i = 1 to n
                for j = 1 to n
                    d^(k)[i][j] = min(d^(k-1)[i][j], d^(k-1)[i][k] + d^(k-1)[k][j])

    Transitive-Closure(G)
        n = |G.V|
        let T^(0) be a new n x n matrix
        for i = 1 to n
            for j = 1 to n
                if i==j or (i, j) in G.E
                    t^(0)[i][j] = 1
                else
                    t^(0)[i][j] = 0
        for k = 1 to n
            let T^(k) be a new n x n matrix
            for i = 1 to n
                for j = 1 to n
                    t^(k)[i][j] = t^(k-1)[i][j] or (t^(k-1)[i][k] and t^(k-1)[k][j])
        return T^(n)
