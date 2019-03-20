#!/usr/bin/env python

# Grids and Graphs

all_nodes = []
for x in range(20):
    for y in range(10):
        all_nodes.append([x, y])

def neighbors(node):
    dirs = [[1,0], [0, 1], [-1, 0], [0, -1]] # east, north, west, south
    result = []
    for dir in dirs:
        result.append([node[0]+dir[0], node[1]+dir[0]])

def neighbors_1(node):
    dirs = [[1,0], [0, 1], [-1, 0], [0, -1]] # east, north, west, south
    result = []
    for dir in dirs:
        neighbor = [node[0]+dir[0], node[1]+dir[0]]
        if neighbor in all_nodes:
            result.append(neighbor)