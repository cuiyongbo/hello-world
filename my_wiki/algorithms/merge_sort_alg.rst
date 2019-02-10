**********
Merge sort
**********

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
Most implementations produce a stable sort, Merge sort is a divide and conquer algorithm that was 
invented by *John von Neumann* in 1945.

**Property**

+-----------------------------+----------------------------------+
| Data structure              | Array                            |
+-----------------------------+----------------------------------+
| Worst-case performance      | :math:`O(n \log n)`              |
+-----------------------------+----------------------------------+
| Average performance         | :math:`O(n \log n)`              |
+-----------------------------+----------------------------------+
| Worst-case space complexity | О(n) auxiliary with array,       |
|                             | O(1) auxiliary with linked lists |
+-----------------------------+----------------------------------+

**Algorithm**

Conceptually, a merge sort works as follows:

    #. Divide the unsorted list into n sublists, each containing 1 element
      
    #. Repeatedly merge sublists to produce new sorted sublists until there 
       is only 1 sublist remaining. This will be the sorted list.

.. code-block:: none
    :caption: Pseudocode taken from *Introduction to algorithms*

    MergeSort(A, p, r)
        if p < r
            q = floor((p+r)/2)
            MergeSort(A, p, q)
            MergeSort(A, q+1, r)
            Merge(A, p, q, r)

    Merge-with-sentinel(A, p, q, r)
        n1, n2 = q-p+1, r-q
        L, R = Array[n1+1], Array[n2+1]
        for i=1 to n1
            L[i] = A[p+i]
        for j=1 to n2
            R[j] = A[q+j]
        L[n1+1], R[n2+1] = inf, inf
        i, j = 1, 1
        for k=p to r
            if L[i] <= R[j]
                A[k] = L[i]
                i++
            else 
                A[k] = R[j]
                j++

    Merge(A, p, q, r)
        n1, n2 = q-p+1, r-q
        L, R = Array[n1], Array[n2]
        for i=1 to n1
            L[i] = A[p+i]
        for j=1 to n2
            R[j] = A[q+j]
        i, j = 1, 1
        for k=p to r
        if (i <= n1 and L[i] <= R[j]) || j>n2  
           A[k] = L[i]
           i = i + 1
        else 
           A[k] = R[j]
           j = j + 1

.. code-block:: none
    :caption: Top-down implementation

    // Array A[] has the items to sort; array B[] is a work array.
    TopDownMergeSort(src[], n)
    {
        allocate(B)
        CopyArray(A, 0, n, B);  
        TopDownSplitMerge(B, 0, n, A);   // sort data from B[] into A[]
    }
   
    // Sort the given run of array dest[] using array src[] as a source.
    // [iBegin, iEnd)
    TopDownSplitMerge(src[], iBegin, iEnd, dest[])
    {
        if(iEnd - iBegin  2)                       
            return;                     
        iMiddle = (iEnd + iBegin) / 2;    
        TopDownSplitMerge(dest, iBegin,  iMiddle, src);
        TopDownSplitMerge(dest, iMiddle,    iEnd, src);
        TopDownMerge(src, iBegin, iMiddle, iEnd, dest);
    }
   
    // Left:   src[iBegin:iMiddle-1].
    // Right:  src[iMiddle:iEnd-1  ].
    // Result: B[  iBegin:iEnd-1   ].
    Merge(src[], iBegin, iMiddle, iEnd, dest[])
    {
        i = iBegin, j = iMiddle;
        for (k = iBegin; k < iEnd; k++) {
            if (i < iMiddle && (j >= iEnd || src[i] <= src[j])) {
                dest[k] = src[i];
                i++;
            } else {
                dest[k] = src[j];
                j++;
            }
        }
    }

.. code-block:: none
    :caption: Bottom-up implementation

    // array A[] has the items to sort; 
    // array B[] is a work array
    void BottomUpMergeSort(A[], B[], n)
    {
        for (width = 1; width < n; width = 2 * width)
        {
           // Array A is full of runs of length width.
           for (i = 0; i < n; i = i + 2 * width)
           {
               // Merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[]
               // or copy A[i:n-1] to B[] ( if(i+width >= n) )
               Merge(A, i, min(i+width, n), min(i+2*width, n), B);
           }
           // Now work array B is full of runs of length 2*width.
           // A more efficient implementation would swap the roles of A and B.
           CopyArray(B, 0, n, A);
        }
    }
