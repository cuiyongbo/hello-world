***********************
Path Finding Algorithms
***********************

**今日事今日毕**

.. figure:: images/Manhattan_distance.svg

    Manhanttan Distance

    | Red: Manhattan distance.
    | Green: diagonal, straight-line distance.
    | Blue, yellow: equivalent Manhattan distances.

The Manhattan distance is the simple sum of the horizontal and vertical components,
whereas the diagonal distance might be computed by applying the Pythagorean theorem. [勾股定理]

.. code-block:: py

    # breadth-first logic
    frontier = Queue()
    frontier.put(src)
    visited = {}
    visited[src] = True
    while not frontier.empty():
        current = frontier.get()
        for next in graph.neighbours(current):
            if next not in visited:
                frontier.put(next)
                visited[next] = True

    # keep track of where we came from for every visited location
    frontier = Queue()
    frontier.put(src)
    came_from = {}
    Node = namedtuple("Node", ['predecessor', 'distance_from_src'])
    came_from[src] = Node(None, 0)
    while not frontier.empty():
        current = frontier.get()
        if current == dest:
            break
        for next in graph.neighbours(current):
            if next not in came_from:
                frontier.put(next)
                came_from[next] = Node(current, came_from[current].distance_from_src+1)

    # reconstruct the path
    current = dest
    path = []
    while current != None:
        path.append(current.predecessor)
        current = came_from[current].predecessor
    path.reverse() # optional

    # Dijkstra's algorithm using distance from src
    frontier = PriorityQueue()
    frontier.put(src, 0)
    came_from = {}
    came_from[src] = None
    cost_sofar = {}
    cost_sofar[src] = 0
    while not frontier.empty():
        current = frontier.get()
        if current == dest: break
        for next in graph.neighbours(current):
            new_cost = cost_sofar[current] + graph.cost(current, next)
            if next not in came_from or new_cost < cost_sofar[next]:
                cost_sofar[next] = new_cost
                priority = new_cost
                frontier.put(next, priority)
                came_from[next] = current

    def heuristic(a, b):
        # Manhattan distance on a square grid
        return abs(a.x-b.x) + abs(a.y-b.y)

    # Greedy Best-first-search using distance to dest
    frontier = PriorityQueue()
    frontier.put(src, 0)
    came_from = {}
    came_from[src] = None
    while not frontier.empty():
        current = frontier.get()
        if current == dest: break
        for next in graph.neighbours(current):
            if next not in came_from:
                priority = heuristic(dest, next)
                frontier.put(next, priority)
                came_from[next] = current

    # A* algorithm using both
    frontier = PriorityQueue()
    frontier.put(src, 0)
    came_from = {}
    came_from[src] = None
    cost_sofar = {}
    cost_sofar[src] = 0
    while not frontier.empty():
        current = frontier.get()
        if current == dest: break
        for next in graph.neighbours(current):
            new_cost = cost_sofar[current] + graph.cost(current, next)
            if next not in came_from or new_cost < cost_sofar[next]:
                priority = heuristic(dest, next) + new_cost
                frontier.put(next, priority)
                came_from[next] = current
                cost_sofar[next] = new_cost


.. code-block:: none
    :caption: A* implementation

    OPEN = priority queue containing START
    CLOSED = empty set
    while lowest rank in OPEN is not the GOAL:
      current = remove lowest rank item from OPEN
      add current to CLOSED
      for neighbors of current:
        cost = g(current) + movement_cost(current, neighbor)
        if neighbor in OPEN and cost < g(neighbor):
          remove neighbor from OPEN, because new path is better
        if neighbor in CLOSED and cost < g(neighbor): # note
          remove neighbor from CLOSED
        if neighbor not in OPEN and neighbor not in CLOSED:
          set g(neighbor) to cost
          add neighbor to OPEN
          set priority queue rank to g(neighbor) + h(neighbor)
          set neighbor's parent to current

    reconstruct reverse path from goal to start
    by following parent pointers

    # note This should never happen if you have an consistent admissible heuristic.

.. code-block:: py
    :caption: Distance to selected points

    frontier = Queue()
    cost_sofar = {}
    seed = {}

    # set the distance to 0 at all start points
    # each start point is its own seed
    for s in start:
        frontier.put(s)
        cost_sofar[s] = 0
        seed[s] = s

    # Expand outwards from existing points
    while not frontier.empty():
        current = frontier.get()
        for next in current.neighbors():
            if next not in cost_sofar:
                cost_sofar[next] = cost_sofar[current] + 1
                frontier.put(next)
                seed[next] = seed[current]

#. Beam Seach

    In the main A* loop, the `OPEN` set stores all the nodes that may need to be searched to find a path.
    The Beam Search is a variation of A* that places a limit on the size of the `OPEN` set.
    If the set becomes too large, the node with the worst chances of giving a good path is dropped.
    One drawback is that you have to keep your set sorted to do this, which limits the choices of data structures.

#. Dynamic weighting

    With dynamic weighting, you get the cost function as ``f(p) = g(p) + w(p) * h(p)``,
    you assume that at the beginning of your search, it’s more important to get (anywhere)
    quickly; at the end of the search, it’s more important to get to the goal.

    There is a weight (``w >= 1``) associated with the heuristic. As you get closer to the goal,
    you decrease the weight; this decreases the importance of the heuristic, and increases the
    relative importance of the actual cost of the path.

#. Iterative deepening

    Iterative Deepening is an approach used in many AI algorithms to start with an approximate answer,
    then make it more accurate. The name comes from game tree searches, where you look some number of
    moves ahead (for example, in Chess). You can try to deepen the tree by looking ahead more moves.
    Once your answer doesn’t change or improve much, you assume that you have a pretty good answer,
    and it won’t improve when you try to make it more accurate again. In `IDA*`, **the depth is a cutoff for f values.**
    When the `f` value is too large, the node won’t even be considered (i.e., it won’t be added to the `OPEN` set).
    The first time through you process very few nodes. Each subsequent pass, you increase the number of nodes you visit.
    If you find that the path improves, then you continue to increase the cutoff; otherwise, you can stop.

#. Bidirectional Search

    Instead of searching from the start to the finish, you can start two searches
    in parallel―one from start to finish, and one from finish to start. When they meet,
    you should have a good path.

    It’s a good idea that will help in some situations. The idea behind bidirectional searches
    is that searching results in a “tree” that fans out over the map. A big tree is much worse
    than two small trees, so it’s better to have two small search trees.

    The front-to-front variation links the two searches together. Instead of choosing the best
    forward-search node, ``g(start,x) + h(x,goal)`` or the best backward-search node, ``g(y,goal) + h(start,y)``,
    this algorithm chooses a pair of nodes with the best ``g(start,x) + h(x,y) + g(y,goal)``.

    The retargeting approach abandons simultaneous searches in the forward and backward directions.
    Instead, it performs a forward search for a short time, chooses the best forward candidate,
    and then performs a backward search―not to the starting point, but to that candidate.
    After a while, it chooses a best backward candidate and performs a forward search from
    the best forward candidate to the best backward candidate. This process continues until
    the two candidates are the same point.


.. rubric:: Footnotes

.. [#] `Introduction to A* (Animated) <https://www.redblobgames.com/pathfinding/a-star/introduction.html>`_
.. [#] `Introduction to A* Algorithm <http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html>`_
.. [#] `A* Demonstration <http://www.ccg.leeds.ac.uk/people/j.macgill/xaStar/>`_
.. [#] `Pathfinding for tower defence <https://www.redblobgames.com/pathfinding/tower-defense/>`_
.. [#] `Recastnavigation - a C++ implementation <https://github.com/recastnavigation/recastnavigation>`_
.. [#] `A* implementation <https://www.redblobgames.com/pathfinding/a-star/implementation.html>`_
.. [#] `Easystar - javascript version <https://easystarjs.com/>`_
.. [#] `Simple C++ version <https://github.com/vandersonmr/A_Star_Algorithm.git>`_
.. [#] `Simple Java version <https://github.com/coderodde/cskit.git>`_
.. [#] `Respository with different benchmark <https://github.com/quantumelixir/pathfinding>`_
.. [#] `Algorithm benchmark sets <https://www.movingai.com/benchmarks/grids.html>`_
.. [#] `An instruction <https://www.oreilly.com/library/view/graph-algorithms/9781492047674/ch04.html>`_
.. [#] `An orelly book Respository with graph theory <https://github.com/neo4j-graph-analytics>`_


graph algorithms : practical examples in apache spark and neo4j

http://finelybook.com/graph-algorithms-practical-examples-in-apache-spark-and-neo4j/
