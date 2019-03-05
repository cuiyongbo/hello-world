********
Heapsort
********

**少壮无所就，入门愧家老**

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
rather than a linear-time search to find the maximum.

Although somewhat slower in practice on most machines than a well-implemented quicksort, it has the advantage of a more favorable 
worst-case :math:`O(n\log n)` runtime. Heapsort is an **in-place** algorithm, but it is **not a stable sort.**

Heapsort was invented by *J. W. J. Williams* in 1964. This was also the birth of the heap, presented already by `Williams` as a useful 
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
the new first value into its position in the heap. This repeats until the range descrease to one.

The steps are:

   #. Call the *buildMaxHeap()* function on the list.
   #. Swap the first element of the list with the final element. 
   #. Call the *siftDown()* function on the list to sift the new first element to its appropriate index in the heap.
   #. Go to step 2 unless the considered range of the list is one element.

The *buildMaxHeap()* operation is run once, and is *O(n)* in performance. The *siftDown()* function is **O(log n),** 
and is called *n* times. Therefore, the performance of this algorithm is :math:`O(n + n \log n) = O(n \log n).`

.. image:: images/heapsort-example.gif

.. code-block:: none
    :caption: Taken from **Introduction to algorithms**

    Parent(i): return i>>1
    Left(i): return 2*i
    Right(i): return 2*i+1

    Max-Heapify(A, i)
        largest = i
        l, r = Left(i), Right(i)
        if l <= A.heap_size and A[l] > A[largest]
            largest = l
        if r <= A.heap_size and A[r] > A[largest]
            largest = r
        if largest != i
            swap(A[i], A[largest])
            Max-Heapify(A, largest)

    Iterative-Max-Heapify(A, i)
        while i < A.heap_size
            largest = i
            l, r = Left(i), Right(i)
            if l <= A.heap_size and A[l] > A[largest]
                largest = l
            if r <= A.heap_size and A[r] > A[largest]
                largest = r

            if largest == i
                break
      
            swap(A[i], A[largest])
            i = largest

    Build-Max-Heap(A)
        A.heap_size = A.length
        for i=A.length/2 downto 1
            Max-Heapify(A, i)

    HeapSort(A)
        Build-Max-Heap(A)
        for i=A.length downto 2
            swap(A[1], A[i])
            A.heap_size--
            Max-Heapify(A, 1)