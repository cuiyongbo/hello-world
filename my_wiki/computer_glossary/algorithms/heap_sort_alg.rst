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
   :caption: pseudocode

   function heapsort(a, count)

       heapify(a, count)
   
       end := count - 1
       while end > 0 do
           swap(a[end], a[0])
           end := end - 1
           siftDown(a, 0, end)
   
   function heapify-siftDown(a, count)
       start = Parent(count-1)
       while start >= 0 do
           siftDown(a, start, count - 1)
           start := start - 1

   
   function siftDown(a, start, end)
       root := start
       while LeftChild(root) <= end do   
           child := LeftChild(root)  
           swap := root            
           if a[swap] < a[child]
               swap := child
           if child+1 ≤ end and a[swap] < a[child+1]
               swap := child + 1
           if swap = root
               return
           else
               swap(a[root], a[swap])
               root := swap           

   function heapify-siftUp(a,count)
    end := 1
    while end < count
        siftUp(a, 0, end)
        end := end + 1
 
   function siftUp(a, start, end)
       child := end 
       while child > start
           parent := Parent(child)
           if a[parent] < a[child] then (out of max-heap order)
               swap(a[parent], a[child])
               child := parent
           else
               return


**Example**

Let ``{ 6, 5, 3, 1, 8, 7, 2, 4 }`` be the list that we want to sort from the smallest to the largest. 
(NOTE, for 'Building the Heap' step: Larger nodes don't stay below smaller node parents. They are swapped 
with parents, and then recursively checked if another swap is needed, to keep larger numbers above smaller 
numbers on the heap binary tree.)

.. image:: images/heapsort-example.gif
