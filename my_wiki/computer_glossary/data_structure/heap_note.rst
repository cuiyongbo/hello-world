****
Heap
****

**Introduction**

.. sidebar:: Max Heap

   .. image:: images/Max-Heap.svg.png

In computer science, a heap is a specialized tree-based data structure that satisfies the heap property: 
if P is a parent node of C, then the key (the value) of P is either greater than or equal to (in a max heap) 
or less than or equal to (in a min heap) the key of C. The node at the "top" of the heap (with no parents) 
is called the **root** node.

The heap is one maximally efficient implementation of an abstract data type called a **priority queue,** and in 
fact priority queues are often referred to as "heaps", regardless of how they may be implemented. A common implementation 
of a heap is the **binary heap,** in which the tree is a binary tree (see figure). The heap data structure, specifically 
the binary heap, was introduced by *J. W. J. Williams* in 1964, as a data structure for the **heapsort sorting** algorithm. 
Heaps are also crucial in several efficient graph algorithms such as **Dijkstra's algorithm.** In a heap, the highest (or lowest) 
priority element is always stored at the root. A heap is not a sorted structure and can be regarded as partially ordered. 
As visible from the heap-diagram, there is no particular relationship among nodes on any given level, even among the siblings.
When a heap is a complete binary tree, it has a smallest possible height—a heap with N nodes and for each node a branches always 
has **log N** height. A heap is a useful data structure when you need to remove the object with the highest (or lowest) priority.

Note that, as shown in the graphic, there is no implied ordering between siblings or cousins and no implied sequence for 
an in-order traversal (as there would be in, e.g., a binary search tree). The heap relation mentioned above applies only between 
nodes and their parents, grandparents, etc. The maximum number of children each node can have depends on the type of heap, 
but in many types it is at most two, which is known as a **binary heap.**


**Operations**

The common operations involving heaps are:

#. Basic

   - find-max [or find-min]: find a maximum item of a max-heap, 
     or a minimum item of a min-heap, respectively (a.k.a. peek).
   
   - insert: adding a new key to the heap (a.k.a., push).
    
   - extract-max [or extract-min]: returns the node of maximum value from a max heap 
     [or minimum value from a min heap] after removing it from the heap (a.k.a., pop).

   - delete-max [or delete-min]: removing the root node of a max heap [or min heap], respectively.
     
   - replace: pop root and push a new key. More efficient than pop followed by push, since only 
     need to balance once, not twice, and appropriate for fixed-size heaps.

#. Creation
   
   - create-heap: create an empty heap.
     
   - heapify: create a heap out of given array of elements.

   - merge (union): joining two heaps to form a valid new heap 
     containing all the elements of both, preserving the original heaps.

   - meld: joining two heaps to form a valid new heap containing all the 
     elements of both, destroying the original heaps.

#. Inspection

   - size: return the number of items in the heap.
   
   - is-empty: return true if the heap is empty, false otherwise.

#. Internal
   
   - increase-key or decrease-key: updating a key within a max- or min-heap, respectively.
     
   - delete: delete an arbitrary node (followed by moving last node and sifting to maintain heap).
     
   - sift-up: move a node up in the tree, as long as needed; used to restore heap condition after 
     insertion. Called "sift" because node moves up the tree until it reaches the correct level, 
     as in a sieve.

   - sift-down: move a node down in the tree, similar to sift-up; used to restore heap condition 
     after deletion or replacement.



..sidebar:: Heap as array

   .. image:: images/Heap-as-array.svg.png

   Example of a complete binary max-heap with node keys 
   being integers from 1 to 100 and how it would be stored 
   in an array.


**Implementation**

Heaps are usually implemented in an array (fixed size or dynamic array), and do not require pointers between elements. 
After an element is inserted into or deleted from a heap, the heap property may be violated and the heap must be balanced 
by internal operations.

Binary heaps may be represented in a very space-efficient way (as an implicit data structure) using an array alone. 
The first (or last) element will contain the root. The next two elements of the array contain its children. The next 
four contain the four children of the two child nodes, etc. Thus the children of the node at position n would be at 
positions 2n and 2n + 1 in a one-based array, or 2n + 1 and 2n + 2 in a zero-based array. This allows moving up or 
down the tree by doing simple index computations. Balancing a heap is done by sift-up or sift-down operations (swapping 
elements which are out of order). As we can build a heap from an array without requiring extra memory (for the nodes, 
for example), heapsort can be used to sort an array in-place.