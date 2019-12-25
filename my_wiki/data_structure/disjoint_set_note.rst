*****************
Disjoint Set Note
*****************

Application: grouping n distinct elements into a collection of disjoint sets.

.. code-block:: none

    Connected-Components(G)
        for each vertex v in G.V
            Make-Set(v)
        for each edge (u,v) in G.E
            if Find-Set(u) != Find-Set(v)
                Union(u, v)

    Same-Component(u, v)
        return Find-Set(u) == Find-Set(v)


#. disjoint-set forests

    - union by rank
    - path compresssion

.. code-block:: none
    :caption: Disjoint-set forests

    Make-Set(x)
        x.p = x

        # the number of edges in the longest simple path
        # between x and a descendant leaf
        x.rank = 0

    Union(x, y)
        Link(Find-Set(x), Find-Set(y))

    Link(x, y)
        if x.rank > y.rank
            y.p = x
        else
            x.p == y
            if x.rank == y.rank
                y.rank += 1

    Find-Set(x)
        if x != x.p
            x.p = Find-Set(x.p)
        return x.p
