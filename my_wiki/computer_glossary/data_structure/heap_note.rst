****
Heap
****

**举一隅不以三隅反，则不复也。**

**Introduction**

.. sidebar:: Max Heap

    .. image:: images/Max-Heap.svg.png

In computer science, a heap is a specialized tree-based data structure 
that satisfies the **heap property**::

    A[Parent(i)] >= A[i] (in a max-heap) 
    A[Parent(i)] <= A[i] (in a min-heap)

The heap is one maximally efficient implementation of an abstract data type called a **priority queue,** and in 
fact priority queues are often referred to as "heaps", regardless of how they may be implemented. A common implementation 
of a heap is the **binary heap,** in which the tree is a binary tree. The heap data structure, specifically 
the binary heap, was introduced by *J. W. J. Williams* in 1964, as a data structure for the **heapsort sorting** algorithm. 
Heaps are also crucial in several efficient graph algorithms such as **Dijkstra's algorithm.** 
A heap is not a sorted structure and can be regarded as partially ordered. 
As visible from the heap-diagram, **there is no particular relationship among nodes on any given level, even among the siblings.**
When a heap is a complete binary tree, it has a smallest possible height—a heap with N nodes and for each node a branches always 
has :math:`\log N` height. 

Note that, as shown in the graphic, there is no implied ordering between siblings or cousins and no implied sequence for 
an in-order traversal (as there would be in, e.g., a binary search tree). The heap relation mentioned above applies only between 
nodes and their parents, grandparents, etc.

**Operations**

The common operations involving heaps are:

#. Basic

    - find-max [or find-min]
    - insert
    - extract-max [or extract-min]
    - delete-max [or delete-min]
    - replace: pop root and push a new key

#. Creation
   
    - create-heap: create an empty heap.
    - heapify: create a heap out of given array of elements.

    - merge (union): joining two heaps to form a valid new heap 
      containing all the elements of both, preserving the original heaps.

    - meld: joining two heaps to form a valid new heap containing all the 
      elements of both, destroying the original heaps.

#. Inspection

    - size
    - is-empty

#. Internal
   
    - increase-key or decrease-key
    - delete: delete an arbitrary node (followed by moving last node and sifting to maintain heap).
    - sift-up: move a node up in the tree, as long as needed; used to restore heap condition after insertion. 
    - sift-down: move a node down in the tree, similar to sift-up; used to restore heap condition after deletion or replacement.

..sidebar:: Heap as array

    .. image:: images/Heap-as-array.svg.png

    Example of a complete binary max-heap with node keys 
    being integers from 1 to 100 and how it would be stored in an array.

**Implementation**

Heaps are usually implemented in an array (fixed size or dynamic array), 
and do not require pointers between elements. After an element is inserted 
into or deleted from a heap, the heap property may be violated and the heap 
must be balanced by internal operations.

Binary heaps may be represented in a very space-efficient way using an array alone. 
The first element will contain the root. The next two elements of the array contain 
its children. The next four contain the four children of the two child nodes, etc. 
**Thus the children of the node at position n would be at positions 2n and 2n + 1 
in a one-based array, or 2n + 1 and 2n + 2 in a zero-based array.** This allows moving up 
or down the tree by doing simple index computations. Balancing a heap is done by sift-up 
or sift-down operations. As we can build a heap from an array without requiring extra memory, 
heapsort can be used to sort an array **in-place.**

.. code-block:: none
   :caption: Taken from **Introduction to Algorithms**

   Parent(i):
      return i/2

   Left(i):
      return 2*i

   Right(i):
      return 2*i + 1
 
   # pre: [i-1, n] is a heap
   # post: [i, n] is a heap
   siftDown(A, i):
      l = Left(i)
      r = Right(i)

      if l <= A.heap_size and A[l] > A[i]
         largest = l
      else largest = i

      if r <= A.heap_size and A[r] > A[i]
         largest = r

      if largest != i
         swap(A[i], A[largest])
         siftDown(A, largest)

   siftDown-loop(A, i)
      largest = i
      while largest < heap_size
         tmp = largest
         l = Left(largest)
         r = Right(largest)
         if l <= A.heap_size and A[l] > A[largest]
            largest = l
         if r <= A.heap_size and A[r] > A[largest]
            largest = r
         
         if tmp == largest
            break
         
         swap(A[tmp], A[largest])

   Build-max-heap-siftDown(A)
      A.heap_size = A.length
      for i = A.length/2 downto 1
         Max-heapify(A, i)
   
   # pre: [1, i-1] is a heap 
   # post: [1, i] is a heap
   siftUp(A, i):
      p = Parent(child)
      if A[p] < A[child]
         swap(A[p], A[child])

   Build-max-heap-siftUp(A)
      A.heap_size = A.length
      for i = 2 upto A.length
         siftUp(A, i)

   HeapSort(A)
      Build-max-heap(A)
      for i=A.length downto 2
         swap(A[1], A[i])
         A.heap_size = A.heap_size -1
         siftDown(A, 1)

.. code-block:: none
   :caption: Take from *Programming pearls*

   root = 1
   value(i) = x[i]
   leftchild(i) = 2*i
   rightchild(i) = 2*i + 1
   parent(i) = i/2
   null(i) = (i<1) or (i>n)

   siftup(n)
   /*
      pre n>0 && heap(1, n-1)
      post heap(1, n)
   */
      i=n
      loop
      /* invariant: heap(1, n) except perhaps between i and its parents */
         if i==1
            break
         p=i/2
         if x[p] <= x[i]
            break
         swap(i, p)
         i=p

   siftdown(n)
   /*
      pre n>0 && heap(2, n)
      post heap(1, n)
   */
   i=1
   loop
   /* invariant: heap(1, n) except perhaps between i and its children */
      c=2*i
      if c>n 
         break
      if c+1 < n
         if x[c+1] < x[c]
            c++
      if x[i] <= x[c]
         break
      swap(i, c)
      i=c

   insert(t)
      if n>maxsize
         error("heap overflow")
      n++
      x[n] = t
      siftup(n)

   extractmin()
      if n < 1
         error("heap underflow")
      t = x[1]
      n--
      x[1] = x[n]
      siftdown(n)