*********
Quicksort
*********
Keyword: in-place, not stable, divide-and-conquer


.. sidebar:: QuickSort

   .. image:: images/quicksort_anim.gif

   Animated visualization of the quicksort algorithm. 
   The red pillars are pivot values.


Introduction
============

Quicksort is an efficient sorting algorithm, serving as a systematic method for placing the elements of an array in order. 
Developed by *Tony Hoare* in 1959 and published in 1961, it is still a commonly used algorithm for sorting. When implemented well, 
it can be about two or three times faster than its main competitors, merge sort and heapsort.

Quicksort is a comparison sort, meaning that it can sort items of any type for which a "less-than" relation (formally, a total order) 
is defined. In efficient implementations it is NOT a stable sort, Quicksort can operate in-place on an array, requiring small additional 
amounts of memory to perform the sorting. It is very similar to **selection sort**, except that it does not always choose worst-case partition.

Mathematical analysis of quicksort shows that, on average, the algorithm takes **O(n log n)** comparisons to sort n items. 
In the worst case, it makes :math:`O(n^2)` comparisons, though this behavior is rare.


Property
========

+-----------------------------+----------------------------------------+
| Data structure              | Array                                  |
+=============================+========================================+
| Worst-case performance      | :math:`O(n^2)`                         |
+-----------------------------+----------------------------------------+
| Best-case performance       | :math:` O(n log n)` (simple partition) |
+-----------------------------+----------------------------------------+
| Average performance         | :math:`O(n log n)`                     |
+-----------------------------+----------------------------------------+
| Worst-case space complexity | :math:`O(n)`                           |
+-----------------------------+----------------------------------------+


Algorithm
=========

Quicksort is a **divide and conquer** algorithm. Quicksort first divides a large array into two smaller 
sub-arrays: the low elements and the high elements. Quicksort can then recursively sort the sub-arrays.

The steps are:

   #. Pick an element, called a pivot, from the array.
   
   #. Partitioning: reorder the array so that all elements with values less than 
      the pivot come before the pivot, while all elements with values greater than 
      the pivot come after it (equal values can go either way). After this partitioning, 
      the pivot is in its final position. This is called the partition operation.
   
   #. Recursively apply the above steps to the sub-arrays.
   
The base case of the recursion is arrays of size zero or one, 
which are in order by definition, so they never need to be sorted.

The pivot selection and partitioning steps can be done in several different ways; 
the choice of specific implementation schemes greatly affects the algorithm's performance.

.. code-block:: none
   :caption: Lomuto partition scheme
   
   algorithm quicksort(A, lo, hi) is
       if lo < hi then
           p := partition(A, lo, hi)
           quicksort(A, lo, p - 1 )
           quicksort(A, p + 1, hi)
   
   algorithm partition(A, lo, hi) is
       pivot := A[hi]
       i := lo - 1    
       for j := lo to hi - 1 do
           if A[j] < pivot then
               i := i + 1
               swap A[i] with A[j]
       swap A[i + 1] with A[hi]
       return i + 1

Sorting the entire array is accomplished by ``quicksort(A, 0, length(A) - 1).``

.. code-block:: cpp
   :caption: Lomuto partition scheme implementation

   #include <stdio.h>

   #define swapWithType(Type, a, b) {if(a != b) {Type tmp = a; a=b; b=tmp;}}
   #define element_of(a) sizeof(a)/sizeof(a[0])

   int partition(int* a, int lo, int hi)
   {
      int pivot = a[hi];
      int i= lo - 1;
      for(int j=lo; j<hi; j++)
      {
         if(a[j] < pivot)
         {
            i++;
            swapWithType(int, a[i], a[j]);
         }
      }
      swapWithType(int, a[i+1], a[hi]);
      return i+1;
   }
   
   void quickSort(int* a, int lo, int hi)
   {
      if(lo >= hi)
         return;
   
      int p = partition(a, lo, hi);
      quickSort(a, lo, p-1);
      quickSort(a, p+1, hi);
   }
   
   int main()
   {
      int a[] = {3, 7, 8, 5 ,2, 1, 9, 5, 4}; 
   
      quickSort(a, 0, element_of(a)-1);
      
      for(int i=0; i<element_of(a); i++)
         printf("%d ", a[i]);
      printf("\n");
   
      return 0;
   }



.. code-block:: none
   :caption: Hoare partition scheme

   algorithm quicksort(A, lo, hi) is
       if lo < hi then
           p := partition(A, lo, hi)
           quicksort(A, lo, p)
           quicksort(A, p + 1, hi)
   
   algorithm partition(A, lo, hi) is
       pivot := A[lo]
       i := lo - 1
       j := hi + 1
       loop forever
           do
               i := i + 1
           while A[i] < pivot
   
           do
               j := j - 1
           while A[j] > pivot
   
           if i >= j then
               return j
   
           swap A[i] with A[j]

The entire array is sorted by ``quicksort(A, 0, length(A)-1).``

.. code-block:: cpp
   :caption: A Hoare partition scheme implementation

   int qPartition(int*a, int lo, int hi)
   {
      int pivot = a[lo];
      int i = lo - 1;
      int j = hi + 1;
      while (1)
      {
         do {
            i++;
         } while (a[i] < pivot);
   
         do {
            j--;
         } while (a[j] > pivot);
   
         if (i >= j)
            return j;
   
         swapWithType(int, a[i], a[j]);
      }
   }
   
   void quickSort(int* a, int lo, int hi)
   {
      if (lo < hi)
      {
         int p = qPartition(a, lo, hi);
         quickSort(a, lo, p);
         quickSort(a, p + 1, hi);
      }
   }