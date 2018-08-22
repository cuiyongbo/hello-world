**************
Selection Sort
**************

**Keywords**: in-place sort, quadratic algorithms

**Introduction**

In computer science, selection sort is a sorting algorithm, specifically an in-place 
comparison sort. It has :math:`O(n^2)` time complexity, making it inefficient on large 
lists, and generally performs worse than the similar insertion sort. Selection sort is 
noted for its simplicity, and it has performance advantages over more complicated 
algorithms in certain situations, particularly where auxiliary memory is limited.

The algorithm divides the input list into two parts: the sublist of items already sorted, 
which is built up from left to right at the front of the list, and the sublist of items 
remaining to be sorted that occupy the rest of the list. Initially, the sorted sublist 
is empty and the unsorted sublist is the entire input list. The algorithm proceeds by finding 
the smallest (or largest, depending on sorting order) element in the unsorted sublist, exchanging 
it with the leftmost unsorted element, and moving the sublist boundaries one element to the right.

**Property **

.. figure:: images/Selection_sort_animation.gif
   :align: center

   Selection Sort

+-----------------------------+------------------------------+
| Data structure              | Array                        |
+-----------------------------+------------------------------+
| Worst-case performance      |                              |
+-----------------------------+ - :math:`О(n^2)` comparisons +
| Best-case performance       |                              |
+-----------------------------+ - :math:`О(n)` swaps         +
| Average performance         |                              |
+-----------------------------+------------------------------+
| Worst-case space complexity | **O(1)** auxiliary           |
+-----------------------------+------------------------------+

**Algorithms**

.. code-block:: none
   :caption: Pseudocode

   function selectionSort(A)
      for i=1 to A.length-1
         pos = i
         for j=i+1 to A.length
            if (A[j] < A[pos])
               pos = j
         if pos != i
            swap(A[pos], A[j])

.. code-block:: cpp
   :caption: C++ implementation

   template<typename T, BinPre BinCmp>
   void selectionSort(T* array, size_t count, BinCmp cmp)
   {

      for(size_t i=0; i < count-1; i++)
      {
         size_t pos = i;
         for(size_t j = i+1; j != count; j++)
         {
            if(!cmp(arr[pos], arr[j])
               pos = j;
         }

         if(pos != i)
            swap(arr[pos], arr[i]);
      }
   }


Complexity
==========

Selection sort is not difficult to analyze compared to other sorting algorithms 
since none of the loops depend on the data in the array. Selecting the minimum 
requires scanning *n* elements (taking *n-1* comparisons) and then swapping it 
into the first position. Finding the next lowest element requires scanning the 
remaining *n-1* elements and so on. Therefore, the total number of comparisons is

.. math::

   {(n-1)+(n-2)+...+1 = \sum_{i=1}^{n-1}i = \sum_{i=1}^{n-1}{\binom {i}{1}}}

By the hockey-stick identity,

.. math::

   { \sum_{i=1}^{n-1}{\binom {i}{1}} = {\binom {n}{2}} 
               = {\frac{n!}{2!(n-2)!}} = {\frac{1}{2}}n(n-1) 
               = {\frac{1}{2}}(n^{2}-n)}

which is of complexity :math:`O(n^{2})` in terms of number of comparisons. 
Each of these scans requires one swap for *n-1* elements (the final element 
is already in place).


Comparison to other sorting algorithms
======================================

Among simple average-case :math:`\Theta (n^2)` algorithms, selection sort almost 
always outperforms bubble sort and gnome sort. Insertion sort is very similar in 
that after the :math:`k^{th}` iteration, the first *k* elements in the array are 
in sorted order. Insertion sort's advantage is that it only scans as many elements 
as it needs in order to place the :math:`k + 1^{st}` element, while selection sort 
must scan all remaining elements to find the :math:`k + 1^{st}` element.

Simple calculation shows that insertion sort will therefore usually perform about 
half as many comparisons as selection sort, although it can perform just as many 
or far fewer depending on the order the array was in prior to sorting. It can be 
seen as an advantage for some real-time applications that selection sort will perform 
identically regardless of the order of the array, while insertion sort's running time 
can vary considerably. However, this is more often an advantage for insertion sort in 
that it runs much more efficiently if the array is already sorted or "close to sorted."

While selection sort is preferable to insertion sort in terms of number of writes 
(:math:`\Theta (n)` swaps versus :math:`\Theta (n^2)` swaps), it almost always far 
exceeds (and never beats) the number of writes that cycle sort makes, as cycle sort 
is theoretically optimal in the number of writes. This can be important if writes are 
significantly more expensive than reads, such as with EEPROM or Flash memory, where every 
write lessens the lifespan of the memory.

Finally, selection sort is greatly outperformed on larger arrays by :math:`\Theta (n \log{n})` 
divide-and-conquer algorithms such as mergesort. However, insertion sort or selection sort are 
both typically faster for small arrays (i.e. fewer than 10–20 elements). A useful optimization 
in practice for the recursive algorithms is to switch to insertion sort or selection sort for 
"small enough" sublists.


Variants
========

**Heapsort** greatly improves the basic algorithm by using an **implicit heap data structure** to 
speed up finding and removing the lowest datum. If implemented correctly, the heap will allow 
finding the next lowest element in :math:`\Theta (\log{n})` time instead of :math:`\Theta (n)` 
for the inner loop in normal selection sort, reducing the total running time to :math:`\Theta (n \log{n}).`

A bidirectional variant of selection sort, called **cocktail sort**, is an algorithm which finds 
both the minimum and maximum values in the list in every pass. This reduces the number of scans 
of the list by a factor of 2, eliminating some loop overhead but not actually decreasing the number 
of comparisons or swaps. Note, however, that cocktail sort more often refers to a bidirectional 
variant of bubble sort. Sometimes this is double selection sort.

Selection sort can be implemented as a stable sort. If, rather than swapping in step 2, the minimum 
value is inserted into the first position (that is, all intervening items moved down), the algorithm 
is stable. However, this modification either requires a data structure that supports efficient insertions 
or deletions, such as a linked list, or it leads to performing :math:`\Theta (n^2)` writes.

In the **bingo sort** variant, items are ordered by repeatedly looking through the remaining items to 
find the greatest value and moving all items with that value to their final location. Like **counting sort**, 
this is an efficient variant if there are many duplicate values. Indeed, selection sort does one pass 
through the remaining items for each item moved. Bingo sort does one pass for each value (not item): 
after an initial pass to find the biggest value, the next passes can move every item with that value 
to its final location while finding the next value as in the following pseudocode (arrays are zero-based 
and the for-loop includes both the top and bottom limits, as in Pascal)::

   bingo(array A)
   
   { This procedure sorts in ascending order. }
   begin
       max := length(A)-1;
   
       { The first iteration is written to look very similar to the subsequent ones, but
         without swaps. }
       nextValue := A[max];
       for i := max - 1 downto 0 do
           if A[i] > nextValue then
               nextValue := A[i];
       while (max > 0) and (A[max] = nextValue) do
           max := max - 1;
   
       while max > 0 do begin
           value := nextValue;
           nextValue := A[max];
           for i := max - 1 downto 0 do
                if A[i] = value then begin
                    swap(A[i], A[max]);
                    max := max - 1;
                end else if A[i] > nextValue then
                    nextValue := A[i];
           while (max > 0) and (A[max] = nextValue) do
               max := max - 1;
       end;
   end;

Thus, if on average there are more than two items with the same value, bingo sort can be expected 
to be faster because it executes the inner loop fewer times than selection sort.

