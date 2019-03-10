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
        if current == dest:
            break
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
        if current == dest:
            break
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
        if current == dest:
            break
        for next in graph.neighbours(current):
            new_cost = cost_sofar[current] + graph.cost(current, next)
            if next not in came_from or new_cost < cost_sofar[next]:
                priority = heuristic(dest, next) + new_cost
                frontier.put(next, priority)
                came_from[next] = current


.. code-block:: none
    :caption: A* implementation

    OPEN = priority queue containing START
    CLOSED = empty set
    while lowest rank in OPEN is not the GOAL:
      current = remove lowest rank item from OPEN
      add current to CLOSED
      for neighbors of current:
        cost = g(current) + movementcost(current, neighbor)
        if neighbor in OPEN and cost less than g(neighbor):
          remove neighbor from OPEN, because new path is better
        if neighbor in CLOSED and cost less than g(neighbor): # note
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
.. [#] `Simple C++ version - <https://github.com/vandersonmr/A_Star_Algorithm.git>`_