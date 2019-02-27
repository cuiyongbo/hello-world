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




