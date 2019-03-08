#!/usr/bin/env python
from __future__ import print_function
import collections

class SimpleGraph:
    def __init__(self):
        self.edges = {}

    def neighbors(self, id):
        return self.edges[id]

class Queue:
    def __init__(self):
        self.elements = collections.deque()

    def empty(self):
        return len(self.elements) == 0

    def put(self, x):
        self.elements.append(x)

    def get(self):
        return self.elements.popleft()

def breadth_first_search_1(graph, start):
    frontier = Queue()
    frontier.put(start)
    visited = {}
    visited[start] = True
    while not frontier.empty():
        current = frontier.get()
        print('Visiting %r' % current)
        for next in graph.neighbors(current):
            if next not in visited:
                frontier.put(next)
                visited[next] = True

def breadth_first_search_2(graph, start):
    frontier = Queue()
    frontier.put(start)
    came_from = {}
    came_from[start] = None
    while not frontier.empty():
        current = frontier.get()
        for next in graph.neighbors(current):
            if next not in came_from:
                frontier.put(next)
                came_from[next] = current
    return came_from

def breadth_first_search_3(graph, start, goal):
    frontier = Queue()
    frontier.put(start)
    came_from = {}
    came_from[start] = None
    while not frontier.empty():
        current = frontier.get()
        if current == goal: break
        for next in graph.neighbors(current):
            if next not in came_from:
                frontier.put(next)
                came_from[next] = current
    return came_from

class SquareGrid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.walls = []

    def in_bounds(self, id):
        (x, y) = id
        return 0 <= x < self.width and 0 <= y < self.height

    def passable(self, id):
        return id not in self.walls

    def neighbors(self, id):
        (x, y) = id
        results = [(x-1, y), (x+1, y), (x, y-1), (x, y+1)]
        if(x+y)%2==0: results.reverse()
        results = filter(self.in_bounds, results)
        results = filter(self.passable, results)
        return results

class GridWithWeights(SquareGrid):
    def __init__(self, width, height):
        #SquareGrid.__init__(self, width, height) # python2.x patch
        super().__init__(width, height) # python3
        self.weights = {}

    def cost(self, from_node, to_node):
        return self.weights.get(to_node, 1)

import heapq

class PriorityQueue:
    def __init__(self):
        Node = collections.namedtuple('Node', ['priority', 'item'])
        self.elements = []

    def empty(self):
        return len(self.elements) == 0

    def put(self, item, priority):
        heapq.heappush(self.elements, Node(priority, item))

    def get(self):
        return heapq.heappop(self.elements).item

# utility functions for dealing with square grids
def from_id_width(id, width):
    return (id % width, id // width)

def draw_tile(graph, id, style, width):
    r = "."
    if 'number' in style and id in style['number']: r = "%d" % style['number'][id]
    if 'point_to' in style and style['point_to'].get(id, None) is not None:
        (x1, y1) = id
        (x2, y2) = style['point_to'][id]
        if x2 == x1 + 1: r = ">"
        if x2 == x1 - 1: r = "<"
        if y2 == y1 + 1: r = "v"
        if y2 == y1 - 1: r = "^"
    if 'start' in style and id == style['start']: r = "A"
    if 'goal' in style and id == style['goal']: r = "Z"
    if 'path' in style and id in style['path']: r = "@"
    if id in graph.walls: r = "#" * width
    return r

def draw_grid(graph, width=2, **style):
    for y in range(graph.height):
        for x in range(graph.width):
            print("%%-%ds" % width % draw_tile(graph, (x, y), style, width), end="")
        print()

if __name__ == '__main__':
  
    example_graph = SimpleGraph()
    example_graph.edges = {
        'A': ['B'],
        'B': ['A', 'C', 'D'],
        'C': ['A'],
        'D': ['A', 'E'],
        'E': ['B']
    }

    # breadth_first_search_1(example_graph, 'A')

    ll = [21,22,51,52,81,82,93,94,111,112,123,124,133,134,141,142,153,154,163,164,171,172,
    173,174,175,183,184,193,194,201,202,203,204,205,213,214,223,224,243,244,253,254,273,
    274,283,284,303,304,313,314,333,334,343,344,373,374,403,404,433,434]

    g = SquareGrid(30, 15)
    g.walls = [from_id_width(id, width=30) for id in ll]
    #draw_grid(g)

    #parents = breadth_first_search_2(g, (8,7))
    parents = breadth_first_search_3(g, (8,7), (17, 12))
    draw_grid(g, width=2, point_to=parents, start=(8,7), goal=(17,12))




