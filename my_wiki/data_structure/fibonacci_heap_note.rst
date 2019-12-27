**************
Fibonacci Heap
**************

A Fibonacci heap is a collection of rooted trees that
are **min-heap ordered**. That is, each tree obeys the
**min-heap property**: the key of a node is greater than or equal
to the key of its parents.

.. code-block:: none

    Fib-Heap-Insert(H, x)
        x.degree = 0  // number of children
        x.p = NULL
        x.child = NULL
        x.mark = false
        if(H.min == NULL)
            create a root list for H containing just x
            H.min = x
        else
            insert x into H's root list
            if(x.key < H.min.key)
                H.min = x
            H.n = H.n + 1

    Fib-Heap-Union(H1, H2)
        H = Make-Fib-Heap()
        H.min = H1.min()
        concatenate the root list of H2 with the root list of H
        if((H1.min == NULL) or (H2.min != NULL and H2.min.key < H1.min.key))
            H.min = H2.min
        H.n = H1.n + H2.n
        return H

    Fib-Heap-Extract-Min(H)
        z = H.min
        if(z != NULL)
            for each child x of z
                add x to the root list of H
                x.p = NULL
            remove z from the root list of H
            if(z == z.right)
                H.min = NULL
            else
                H.min = z.right
                Consolidate(H)
            H.n = H.n - 1
        return z

    Consolidate(H)
        // D(H.n) means the maximum degree of any node
        // in an n-node Fibnacci heap
        let A[0, D(H.n)] be a new array
        for i=0 to D(H.n)
            A[i] = NULL
        for each node w in the root list of H
            x, d = w, w.degree
            while(A[d] != NULL)
                y = A[d]
                if(x.key > y.key)
                    exchange x with y
                Fib-Heap-Link(H, y, x)
                A[d] = NULL
                d = d + 1
            A[d] = x
        H.min = NULL
        for i=0 to D(H.n)
            if(A[i] != NULL)
                if(H.min == NULL)
                    create a root list for H containing just A[i]
                    H.min = A[i]
                else
                    insert A[i] into H's root list
                    if(A[i].key < H.min.key)
                        H.min = A[i]

    Fib-Heap-Link(H, y, x)
        remove y from the root list of H
        make y a child of x, incrementing x.degree
        y.mark = false
