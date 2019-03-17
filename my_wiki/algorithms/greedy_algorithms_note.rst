*****************
Greedy algorithms
*****************

**路漫漫其修远兮，吾将上下而求索。**

**Greedy-choice property**: we can assemble a globally optimal solution 
by making locally optimal choices. 

A problem exhibits **optimal substructure** if an optimal solution 
to the problem contains within it optimal solutions to subproblems.

**Problem definition:** Suppose we have a set :math:`S={a_1,a_2, \ldots,a_n}` of n proposed 
activities that wish to use a resource, such as a lecture hall, which can serve only one activity at a time. 
Each activity :math:`a_i` has a start time :math:`s_i` and a finish time :math:`f_i` ,
where :math:`0 \le  s_i \lt f_i \lt \infty`. If selected, activity :math:`a_i` takes place 
during the half-open time interval :math:`[s_i, f_i)`. Activities :math:`a_i` and :math:`a_j`
are compatible if the intervals :math:`[s_i, f_i)` and :math:`[s_j, f_j)` do not overlap. 
That is, :math:`a_i` and :math:`a_j` are compatible if :math:`s_i \ge  f_j` or :math:`s_j \ge  f_i`. 
In the **activity-selection problem**, we wish to select a maximum-size subset of mutually compatible activities.

.. code-block:: none
    :caption: Taken from *Introduction to Algorithms*

    Recursive-Activity-Selector(s, f, k, n)
        m = k+1
        while m <= n and s[m] < f[k]
            m++
        if m <= n
            return union(a[m], Recursive-Activity-Selector(s, f, m, n))
        else 
            return empty-set

    Iterative-Activity-Selector(s, f)
        result-set.append(a[1])
        j = 1
        for i=2 to s.length
            if s[i] >= f[j]
                result-set.append(a[i])
                j = i
        return result-set

* The 0-1 knapsack problem
* The fractional knapsack problem
  
#. Huffman code
   
    .. code-block:: none
    
        // O(n log n)
        Huffman(C)
            n = C.alphabetSize
            Q = C // build a min-priority queue, keyed by frequency of occurrence of character, from input in O(n)
            for i=1 to n-1
                allocate a new node z
                z.left = Extract-Min(Q) // O(log n)
                z.right = Extract-Min(Q) 
                z.freq = z.left.freq + z.right.freq
                Insert(Q, z)
            return Extract-Min(Q) // return the root of the tree

.. code-block:: py
    :caption: Python implementation

    #!/usr/bin/env python3

    denom = [100, 50, 10, 5, 1, .5, .1]
    denom.sort(reverse=True)
    owed = 56329
    payed = []
    for d in denom:
        while owed >= d:
            owed -= d
            payed.append(d)
    
    sum(payed)
    len(payed)

    from heapq import heapify, heappush, heappop
    from itertools import count
    
    def huffman(seq, frq):
        num = count()
        tree = list(zip(frq, num, seq))
        heapify(tree)
        while len(tree) > 1:
            fa, _, a = heappop(tree)
            fb, _, b = heappop(tree)
            n = next(num)
            heappush(tree, (fa+fb, n, [a, b]))
        return tree[0][-1]
    
    def codes(tree, prefix=""):
        if len(tree) == 1:
            yield (tree, prefix)
            return 
        for bit, child in zip("01", tree): # left (0) and right (1)
            for pair in codes(child, prefix+bit): 
                yield pair
    
    seq = "abcdefghi"
    frq = [4,5,6,9, 11, 12, 15, 16, 20]
    huffman_codec = list(codes(huffman(seq, frq)))
    for character, code in huffman_codec:
        print("%s: %s" % (character, code))
