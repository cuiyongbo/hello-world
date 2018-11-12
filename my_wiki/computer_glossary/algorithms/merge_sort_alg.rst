**********
Merge sort
**********

**不能把这个世界让给你所鄙视的人。**

**Keyword:** stable, O(n log n), locality of reference.

.. sidebar:: Merge sort

   .. image:: images/Merge_sort_2.gif
   .. image:: images/Merge-sort-example-300px.gif

   An example of merge sort. First divide the list into the 
   smallest unit (1 element), then compare each element with 
   the adjacent list to sort and merge the two adjacent lists. 
   Finally all the elements are sorted and merged.


**Origin**

In computer science, merge sort is an efficient, general-purpose, comparison-based sorting algorithm. 
Most implementations produce a stable sort, Merge sort is a divide and conquer algorithm that was invented 
by *John von Neumann* in 1945.


**Property**

+-----------------------------+----------------------------------+
| Data structure              | Array                            |
+-----------------------------+----------------------------------+
| Worst-case performance      | O(n log n)                       |
+-----------------------------+----------------------------------+
| Average performance         | O(n log n)                       |
+-----------------------------+----------------------------------+
| Worst-case space complexity | О(n) auxiliary with array,       |
|                             | O(1) auxiliary with linked lists |
+-----------------------------+----------------------------------+


**Algorithm**

Conceptually, a merge sort works as follows:

   #. Divide the unsorted list into n sublists, each containing 1 element
      (a list of 1 element is considered sorted).
      
   #. Repeatedly merge sublists to produce new sorted sublists until there 
      is only 1 sublist remaining. This will be the sorted list.

.. code-block:: none
   :caption: Top-down implementation

   CopyArray(src[], iBegin, iEnd, dest[])
   {
       for(k = iBegin; k < iEnd; k++)
           dest[k] = src[k];
   }

   // Array A[] has the items to sort; array B[] is a work array.
   TopDownMergeSort(src[], n)
   {
       allocate(B)
       CopyArray(A, 0, n, B);  
       TopDownSplitMerge(B, 0, n, A);   // sort data from B[] into A[]
   }
   
   // Sort the given run of array dest[] using array src[] as a source.
   // iBegin is inclusive; iEnd is exclusive.
   TopDownSplitMerge(src[], iBegin, iEnd, dest[])
   {
       if(iEnd - iBegin < 2)                       
           return;                     
       // split the run longer than 1 item into halves
       iMiddle = (iEnd + iBegin) / 2;    
       // recursively sort both runs from array dest[] into src[]
       TopDownSplitMerge(dest, iBegin,  iMiddle, src);  // sort the left  run
       TopDownSplitMerge(dest, iMiddle,    iEnd, src);  // sort the right run
       // merge the resulting runs from array src[] into dest[]
       TopDownMerge(src, iBegin, iMiddle, iEnd, dest);
   }
   
   // Left source half is  src[iBegin:iMiddle-1].
   // Right source half is src[iMiddle:iEnd-1  ].
   // Result is            B[ iBegin:iEnd-1   ].
   TopDownMerge(src[], iBegin, iMiddle, iEnd, dest[])
   {
       i = iBegin, j = iMiddle;
       for (k = iBegin; k < iEnd; k++) {
           if (i < iMiddle && (j >= iEnd || src[i] <= src[j])) {
               dest[k] = src[i];
               i = i + 1;
           } else {
               dest[k] = src[j];
               j = j + 1;
           }
       }
   }

   TopDownMerge_2(src[], iBegin, iMiddle, iEnd, B[])
   {
      k = i = iBegin, j = iMiddle
      
      while(i<iMiddle && j<iEnd)
      {
         if(src[i] <= src[j])
            dest[k++] = src[i++];
         else
            B[k++] = src[j++];
      }

      while(i<iMiddle)
         B[k++] = src[i++];

      while(j<iEnd)
         B[k++] = src[j++];
   }


.. code-block:: none
   :caption: Top-down implementation using lists

   function merge_sort(list m)
    // Base case. A list of zero or one elements is sorted, by definition.
    if length of m ≤ 1 then
        return m

    // Recursive case. First, divide the list into equal-sized sublists
    // consisting of the first half and second half of the list.
    // This assumes lists start at index 0.
    var left := empty list
    var right := empty list
    for each x with index i in m do
        if i < (length of m)/2 then
            add x to left
        else
            add x to right

    // Recursively sort both sublists.
    left := merge_sort(left)
    right := merge_sort(right)

    // Then merge the now-sorted sublists.
    return merge(left, right)

   function merge(left, right)
       var result := empty list
   
       while left is not empty and right is not empty do
           if first(left) ≤ first(right) then
               append first(left) to result
               left := rest(left)
           else
               append first(right) to result
               right := rest(right)
   
       // Either left or right may have elements left; consume them.
       // (Only one of the following loops will actually be entered.)
       while left is not empty do
           append first(left) to result
           left := rest(left)
       while right is not empty do
           append first(right) to result
           right := rest(right)
       return result

.. code-block:: none
   :caption: Bottom-up implementation

   void CopyArray(B[], A[], n)
   {
       for(i = 0; i < n; i++)
           A[i] = B[i];
   }

   // array A[] has the items to sort; array B[] is a work array
   void BottomUpMergeSort(A[], B[], n)
   {
       // Each 1-element run in A is already "sorted".
       // Make successively longer sorted runs of length 2, 4, 8, 16... until whole array is sorted.
       for (width = 1; width < n; width = 2 * width)
       {
           // Array A is full of runs of length width.
           for (i = 0; i < n; i = i + 2 * width)
           {
               // Merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[]
               // or copy A[i:n-1] to B[] ( if(i+width >= n) )
               BottomUpMerge(A, i, min(i+width, n), min(i+2*width, n), B);
           }
           // Now work array B is full of runs of length 2*width.
           // Copy array B to array A for next iteration.
           // A more efficient implementation would swap the roles of A and B.
           CopyArray(B, A, n);
           // Now array A is full of runs of length 2*width.
       }
   }
   
   //  Left run is A[iLeft :iRight-1].
   // Right run is A[iRight:iEnd-1  ].
   void BottomUpMerge(A[], iLeft, iRight, iEnd, B[])
   {
       i = iLeft, j = iRight;
       // While there are elements in the left or right runs...
       for (k = iLeft; k < iEnd; k++) {
           // If left run head exists and is <= existing right run head.
           if (i < iRight && (j >= iEnd || A[i] <= A[j])) {
               B[k] = A[i];
               i = i + 1;
           } else {
               B[k] = A[j];
               j = j + 1;    
           }
       } 
   }


**Analysis**

In sorting n objects, merge sort has an average and worst-case performance of **O(n log n).** 
If the running time of merge sort for a list of length n is T(n), then the recurrence **T(n) = 2T(n/2) + n** 
follows from the definition of the algorithm (apply the algorithm to two lists of half the size of the original 
list, and add the n steps taken to merge the resulting two lists). The closed form follows from the master 
theorem for divide-and-conquer recurrences.

.. image:: images/Merge_sort_algorithm_diagram.svg.png


.. code-block:: none
   :caption: Pseudocode taken from *Introduction to algorithms*

   MergeSort(A, p, r)
      if p < r
         q = floor((p+r)/2)
         MergeSort(A, p, q)
         MergeSort(A, q+1, r)
         Merge(A, p, q, r)

   Merge-with-sentinel(A, p, q, r)
      n1 = q-p+1
      n2 = r-q
      L = Array[n1+1]
      R = Array[n2+1]
      for i=1 to n1
         L[i] = A[p+i]
      for j=1 to n2
         R[j] = A[q+j]
      L[n1+1] = inf
      R[n2+1] = inf
      i = 1
      j = 1
      for k=p to r
         if L[i] <= R[j]
            A[k] = L[i]
            i = i + 1
         else 
            A[k] = R[j]
            j = j + 1

   Merge(A, p, q, r)
      n1 = q-p+1
      n2 = r-q
      L = Array[n1]
      R = Array[n2]
      for i=1 to n1
         L[i] = A[p+i]
      for j=1 to n2
         R[j] = A[q+j]
      i = 1
      j = 1
      for k=p to r
         if (i <= n1 and L[i] <= R[j]) || j>n2  
            A[k] = L[i]
            i = i + 1
         else 
            A[k] = R[j]
            j = j + 1