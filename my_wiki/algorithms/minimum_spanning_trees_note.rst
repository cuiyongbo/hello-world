*********************
Minimus Spanning Tree
*********************

Minimus-spanning-tree problem: Assume that we have a connected, undirected graph **G = (V, E)**
with a weight function :math:`w: E /rightarrow \mathbb{R}`, and we wish to find a spanning tree for G 
with minimum weight.

.. code-block:: none

   Generic-MST(G, w)
      A = empty set
      while A does not form a spanning tree
         find an edge (u, v) that is safe for A
         A.union({(u, v)})
      return A