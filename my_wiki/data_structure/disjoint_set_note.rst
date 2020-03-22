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


#. disjoint-set forests optimization

    find path: The nodes visited on this simple path toward the root constitute the find path.

    rank: the upperbound on the height of the node.

    - union by rank

        - we make the root with smaller rank point to the root with larger rank in Union operation.

    - path compresssion

        - we use it during Find-Set operations to make each node on the find path point directly to the root.
          Path compression does not change any ranks.

.. code-block:: none
    :caption: Disjoint-set forests

    # require x not already in some other set
    Make-Set(x)
        x.p = x

        # the number of edges in the longest simple path
        # between x and a descendant leaf
        x.rank = 0

    # assume two sets are disjoint prior to the operation
    Union(x, y)
        Link(Find-Set(x), Find-Set(y))

    Link(x, y)
        if x.rank > y.rank
            y.p = x
        else
            x.p = y
            if x.rank = y.rank
                y.rank += 1

    Find-Set(x)
        if x != x.p
            x.p = Find-Set(x.p)
        return x.p

    Find-Set(x)
        initialize an empty stack s
        while x != x.p
            s.push(x)
            x = x.p
        while s not empty
            t = s.top(); s.pop()
            t.p = x
        return x
