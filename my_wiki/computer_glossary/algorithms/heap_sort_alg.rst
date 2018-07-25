********
Heapsort
********

**少壮无所就，入门愧家老。**

**Keyword**: comparison-based sorting, in-place, not stable, :math:`O(n \log n).`

.. sidebar:: Heapsort

   .. image:: images/Sorting_heapsort_anim.gif

   A run of heapsort sorting an array of randomly permuted values. 
   In the first stage of the algorithm the array elements are reordered 
   to satisfy the heap property. Before the actual sorting takes place, 
   the heap tree structure is shown briefly for illustration.


**Origin**

In computer science, heapsort is a comparison-based sorting algorithm. Heapsort can be thought of as an improved selection sort: 
like that algorithm, it divides its input into a sorted and an unsorted region, and it iteratively shrinks the unsorted region by 
extracting the largest element and moving that to the sorted region. The improvement consists of the use of a heap data structure 
rather than a linear-time search to find the maximum.[1]

Although somewhat slower in practice on most machines than a well-implemented quicksort, it has the advantage of a more favorable 
worst-case **O(n log n)** runtime. Heapsort is an **in-place** algorithm, but it is **not a stable sort.**

Heapsort was invented by *J. W. J. Williams* in 1964. This was also the birth of the heap, presented already by Williams as a useful 
data structure in its own right.


**Property**

+-----------------------------+--------------------+
| Worst-case performance      | :math:`O(n\log n)` |
+-----------------------------+--------------------+
| Average performance         | :math:`O(n\log n)` |
+-----------------------------+--------------------+
| Worst-case space complexity | **O(1)** auxiliary |
+-----------------------------+--------------------+


**Algorithm**

The heapsort algorithm involves preparing the list by first turning it into a max heap. 
The algorithm then repeatedly swaps the first value of the list with the last value, 
decreasing the range of values considered in the heap operation by one, and sifting 
the new first value into its position in the heap. This repeats until the range 
of considered values is one value in length.

The steps are:

   #. Call the *buildMaxHeap()* function on the list, also refered as *heapify().*
   #. Swap the first element of the list with the final element. Decrease the considered range of the list by one.
   #. Call the *siftDown()* function on the list to sift the new first element to its appropriate index in the heap.
   #. Go to step *(2)* unless the considered range of the list is one element.

The *buildMaxHeap()* operation is run once, and is *O(n)* in performance. The *siftDown()* function is **O(log n),** 
and is called *n* times. Therefore, the performance of this algorithm is :math:`O(n + n \log n) = O(n \log n).`

The following is a simple way to implement the algorithm in pseudocode. Arrays are zero-based. 
Movement 'down' means from the root towards the leaves, or from lower indices to higher. 
Note that during the sort, the largest element is at the root of the heap at ``a[0],`` 
while at the end of the sort, the largest element is in ``a[end].``

.. code-block:: none
   :caption: pseudo code

   procedure heapsort(a, count) is
       input: an unordered array a of length count
    
       (Build the heap in array a so that largest value is at the root)
       heapify(a, count)
   
       (The following loop maintains the invariants that a[0:end] is a heap 
       and a[end:count] is in sorted order)
       end := count - 1
       while end > 0 do
           (a[0] is the root and largest value.)
           swap(a[end], a[0])
           (the heap size is reduced by one)
           end := end - 1
           (the swap ruined the heap property, so restore it)
           siftDown(a, 0, end)
   
   (Put elements of 'a' in heap order, in-place)
   procedure heapify(a, count) is
       (find the parent of the last element in 'a')
       start := iParent(count-1)
       
       while start ≥ 0 do
           (sift down the node at index 'start' to the proper place 
           such that all nodes below the start index are in heap order)
           siftDown(a, start, count - 1)
           (go to the next parent node)
           start := start - 1

   
   (Repair the heap whose root element is at index 'start', assuming the heaps rooted at its children are valid)
   procedure siftDown(a, start, end) is
       root := start
   
       while iLeftChild(root) ≤ end do    (While the root has at least one child)
           child := iLeftChild(root)   (Left child of root)
           swap := root                (Keeps track of child to swap with)
   
           if a[swap] < a[child]
               swap := child
           (If there is a right child and that child is greater)
           if child+1 ≤ end and a[swap] < a[child+1]
               swap := child + 1
           if swap = root
               (The root holds the largest element. Since we assume the heaps rooted at the
                children are valid, this means that we are done.)
               return
           else
               swap(a[root], a[swap])
               root := swap            (repeat to continue sifting down the child now)