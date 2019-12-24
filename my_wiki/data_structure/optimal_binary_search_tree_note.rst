**************************
Optimal binary search tree
**************************

**Definition**: For a given set of probabilities, we wish to construct a binary search tree
whose expected search cost is smallest. We call such a tree an optimal binary search tree.

.. code-block:: none

    Optimal-BST(p, q, n)
        let e[1,n+1][0,n], w[1,n+1][0,n]
        and root[1,n][1,n] be new tables
        for i=1 to n+1
            e[i][i-1] = q[i-1]
            w[i][i-1] = q[i-1]
        for l=1 to n
            for i=1 to n-l+1
                j = i+l-1
                e[i][j] = inf
                w[i][j] = w[i][j-1] + p[j] + q[j]
                for r=i to j
                    t = e[i][r-1] + e[r+1][j] + w[i][j]
                    if t < e[i][j]
                        e[i][j] = t
                        root[i][j] = r
        return (e, root)

    Optimal-BST-2(p, q, n)
        let e[1,n+1][0,n], w[1,n+1][0,n]
        and root[1,n][1,n] be new tables
        for i=1 to n+1
            e[i][i-1] = q[i-1]
            w[i][i-1] = q[i-1]
        for i=1 to n
            for j=i to n
                e[i][j] = inf
                w[i][j] = w[i][j-1] + p[j] + q[j]
                for r=i to j
                    t = e[i][r-1] + e[r+1][j] + w[i][j]
                    if t < e[i][j]
                        e[i][j] = t
                        root[i][j] = r
        return (e, root)
