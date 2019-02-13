*********
Quicksort
*********

Keyword: in-place, not stable, divide-and-conquer

.. sidebar:: QuickSort

   .. image:: images/quicksort_anim.gif

   Animated visualization of the quicksort algorithm. 
   The red pillars are pivot values.

**Introduction**

Developed by *Tony Hoare* in 1959 and published in 1961, Quicksort is an efficient sorting algorithm, 
serving as a systematic method for sorting an array. 

Quicksort is a **comparison sort**, meaning that it can sort items of any type for which a *less-than* relation  
is defined. In efficient implementations it is **NOT** a stable sort, Quicksort can operate **in-place** on an array, requiring small additional amounts of memory to perform the sorting. It is very similar to **selection sort**, 
except that it does not always choose worst-case partition.

**Property**

+-----------------------------+----------------------------------------+
| Data structure              | Array                                  |
+=============================+========================================+
| Worst-case performance      | :math:`O(n^2)`                         |
+-----------------------------+----------------------------------------+
| Average performance         | :math:`O(n \log n)`                    |
+-----------------------------+----------------------------------------+
| Worst-case space complexity | :math:`O(n)`                           |
+-----------------------------+----------------------------------------+

**Algorithm**

Quicksort is a **divide and conquer** algorithm. It behaves as following:

    #. Pick an element, called a pivot, from the array.
   
    #. Partitioning: reorder the array so that all elements with values less than 
       the pivot come before the pivot, while all elements with values greater than 
       the pivot come after it (equal values can go either way). After this partitioning, 
       the pivot is in its final position. This is called the partition operation.
   
    #. Recursively apply the above steps to the sub-arrays.
   
.. code-block:: none
   :caption: Taken from *Introduction to algorithms*

    QuickSort(A, p, r)
        if(p<r)
            q = Partition(A, p, r)
            Quicksort(A, p, q-1)
            Quicksort(A, q+1, r)

    Partition(A, p, r)
        x, i = A[r], p-1
        for j=p to r-1
            if(A[j] <= x)
                i = i + 1
                swap(A[i], A[j])
        swap(A[i+1], A[r])
        return i+1

    Partition-Randomized(A, p, r)
        i = Random(p, r) // return an integer among [p, r]
        swap(A[r], A[i])
        return Partition(A, p, r)

    QuickSort-Randomized(A, p, r)
        if p < r
            q = Partition-Randomized(A, p, r)
            QuickSort-Randomized(A, p, q-1)
            QuickSort-Randomized(A, q+1, r)

    Partition-Hoare(A, p, r)
        x = A[p]
        i, j = p-1, r+1
        while True
            while True
                j = j-1
                if A[j] <= x
                    break
            while True
                i = i+1
                if A[i] >= x
                    break
            if i<j
                swap(A[i], A[j])
            else return j

    QuickSort-Hoare(A, p, r)
        if p < r
            # The Partition-Hoare procedure always places the pivot value
            # into one of the two partitions A[p, j], and A[j+1, r]
            q = Partition-Hoare(A, p, r) 
            QuickSort-Hoare(A, p, q)
            QuickSort-Hoare(A, q+1, r)

    # To sort the entire array A, call QuickSort(A, 1, A.length)

.. code-block:: py

    # return [low, high] element indices with the same value
    # invariant: A[i, low] < x < A[high, r]
    def threeWayPartition(A, p, r):
        i, pivot = p+1, A[p]
        low, high = p, r
        while i<=high:
            if A[i] < pivot:
                A[i], A[low] = A[low], A[i]
                i, low = i+1, low+1
            elif A[i] > pivot:
                A[i], A[high] = A[high], A[i]
                high -= 1
            else:
                i += 1
        return low, high 

    def quick_sort_three_way_partition(items, p, r):
        if p < r:
            low, high = threeWayPartition(items, p, r)
            quick_sort_three_way_partition(items, p, low-1)
            quick_sort_three_way_partition(items, high+1, r)