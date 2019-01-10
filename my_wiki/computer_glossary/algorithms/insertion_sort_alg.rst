**************
Insertion Sort
**************

Easy to gain, easy to forget.

**KeyWords**: Stable, In-place, quadratic algorithms

**Introduction**

.. sidebar:: Insertion Sort

    .. image:: images/Insertion_sort.gif

Insertion sort is a simple sorting algorithm that builds the final sorted array (or list) 
one item at a time. It is much less efficient on large lists than more advanced algorithms 
such as quicksort, heapsort, or merge sort. However, insertion sort provides several advantages:

    * Efficient for (quite) small data sets。
   
    * Adaptive, i.e., efficient for data sets that are already substantially 
      sorted: the time complexity is **O(nk)** when each element in the input 
      is no more than k places away from its sorted position.
   
    * Stable; i.e., does not change the relative order of elements with equal keys.
   
    * In-place; i.e., only requires a constant amount **O(1)** of additional memory space.
   
    * Online; i.e., can sort a list as it receives it.


**Property**

+-----------------------------+--------------------------------------+
| Data structure              | Array                                |
+-----------------------------+--------------------------------------+
| Worst-case performance      | :math:`О(n^2)` comparisons, swaps    |
+-----------------------------+--------------------------------------+
| Average performance         | :math:`О(n^2)` comparisons, swaps    |
+-----------------------------+--------------------------------------+
| Worst-case space complexity | **О(n)** total, **O(1)** auxiliary   |
+-----------------------------+--------------------------------------+


**Algorithm Implementation**

.. sidebar:: Insertion sort example

    .. figure:: images/Insertion-sort-example.gif

    A graphical example of insertion sort. The partial sorted list (black) 
    initially contains only the first element in the list. With each iteration 
    one element (red) is removed from the input data and inserted in-place into 
    the sorted list.

.. code-block:: none
    :caption: Taken from **Introduction to algorithms**

    InsertionSort(A)
        for j=2 to A.length
            key = A[j]
            i = j-1
            while i>0 and A[i] > key
                A[i+1] = A[i]
                i = i-1
            A[i+1] = key


**Relation to other sorting algorithms**

Insertion sort is very similar to **selection sort**. As in selection sort, after *k* passes through the array, 
the first *k* elements are in sorted order. However, the fundamental difference between the two algorithms is 
that for selection sort these are the *k* smallest elements of the unsorted input, while in insertion sort they 
are simply the first *k* elements of the input. The primary advantage of insertion sort over selection sort is 
that selection sort must always scan all remaining elements to find the absolute smallest element in the unsorted 
portion of the list, while insertion sort requires only a single comparison when the :math:`k+1^{th}` element is 
greater than the :math:`k^{th}` element; when this is frequently true (such as if the input array is already sorted 
or partially sorted), insertion sort is distinctly more efficient compared to selection sort. 

However, a disadvantage of insertion sort over selection sort is that 
it requires more writes due to the fact that, on each iteration, inserting the :math:`k+1^{th}` element into the 
sorted portion of the array requires many element swaps to shift all of the following elements, while only a single 
swap is required for each iteration of selection sort. In general, insertion sort will write to the array :math:`O(n^2)` 
times, whereas selection sort will write only *O(n)* times. For this reason selection sort may be preferable in cases 
where writing to memory is significantly more expensive than reading, such as with EEPROM or flash memory.

While some divide-and-conquer algorithms such as quicksort and mergesort outperform insertion sort for larger arrays, 
non-recursive sorting algorithms such as insertion sort or selection sort are generally faster for very small arrays 
(the exact size varies by environment and implementation, but is **typically between 7 and 50 elements**). Therefore, 
a useful optimization in the implementation of those algorithms is a **hybrid approach**, using the simpler algorithm when 
the array has been divided to a small size.


**Variants**

D.L. Shell made substantial improvements to the algorithm; the modified version is called **Shell sort**. 
The sorting algorithm compares elements separated by a distance that decreases on each pass. Shell sort 
has distinctly improved running times in practical work, with two simple variants requiring :math:`O(n^{3/2})` 
and :math:`O(n^{4/3})` running time.

A variant named **binary merge sort** uses a binary insertion sort to sort groups of 32 elements, 
followed by a final sort using merge sort. It combines the speed of insertion sort on small data 
sets with the speed of merge sort on large data sets.

To avoid having to make a series of swaps for each insertion, the input could be stored in a linked list, 
which allows elements to be spliced into or out of the list in constant-time when the position in the list 
is known. However, searching a linked list requires sequentially following the links to the desired position: 
a linked list does not have random access, so it cannot use a faster method such as binary search. Therefore, 
the running time required for searching is **O(n)** and the time for sorting is :math:`O(n^2)`. If a more sophisticated 
data structure (e.g., heap or binary tree) is used, the time required for searching and insertion can be reduced significantly; 
this is the essence of **heap sort** and **binary tree sort**.

If a skip list is used, the insertion time is brought down to :math:`O(\log n)`, and swaps are not needed because the 
skip list is implemented on a linked list structure. The final running time for insertion would be :math:`O(n \log n)`.

**List insertion sort**

If the items are stored in a linked list, then the list can be sorted with **O(1)** additional space. 
The algorithm starts with an initially empty list. The input items are taken off the list one at a time, 
and then inserted in the proper place in the sorted list. When the input list is empty, 
the sorted list has the desired result.

.. code-block:: c

    struct LIST
    {
        struct LIST* pNext;
        int          iValue;
    };

    struct LIST* SortList1(struct LIST * pList) 
    {
        if(!pList || !pList->pNext)
            return pList;

        struct LIST* pSorted = NULL;
        while(pList != NULL) 
        {
           struct LIST* current = pList;
           pList = pList->pNext;
           if(pSorted == NULL || current->iValue < pSorted->iValue) 
           {
                // 1. sorted list is empty
                // 2. A[j] < A[0] to avoid worst case
               current->pNext = pSorted;
               pSorted = current;
           } 
           else 
           {
               struct LIST* p = pSorted;
               while(p != NULL) 
               {
                    if(p->pNext == NULL // last element of the sorted list
                        || current->iValue < p->pNext->iValue) // middle of the list
                    {
                        // insert into middle of the sorted list or as the last element
                        current->pNext = p->pNext;
                        p->pNext = current;
                        break;
                   }
                   p = p->pNext;
               }
           }
       }
       return pSorted;
    }

    struct LIST * SortList(struct LIST* pList)
    {
        if(!pList || !pList->pNext)
            return pList;
   
        struct LIST* pSorted = NULL;
        while (pList != NULL)
        {
            struct LIST*   pHead  = pList;
            struct LIST** ppTrail = &pSorted;
            pList = pList->pNext;
            while (*ppTrail != NULL && (*ppTrail)->iValue) < pHead->iValue)
            {
               ppTrail = &(*ppTrail)->pNext;
            }
   
            pHead->pNext = *ppTrail;
            *ppTrail = pHead;
        }
        return pSorted;
    }

.. code-block:: cpp
    :caption: std implementation taken from MSVC

    template<class BinPred, class BidIterator, class ElementType>
    void insertionSort(BidIterator first, BidIterator last, BinPred pred)
    {
        if(first != last)
        {
            for (BidIterator next=first; ++next != last; )
            {
                BidIterator next1 = next;
                ElementType tmpVal = move(next)
               
                // avoid worst case 
                if(pred(tmpVal, *first))
                {
                    count = next - first;
                    ++next1;
                    memmove(next1-count, first, count*sizeof(ElementType));
                    *first = move(tmpVal);
                }
                else
                {
                    for(BidIterator first1 = next1; pred(tmpVal, *(--first1)); next1=first1)
                    {
                        *next1 = move(*first1)
                    }
                    *next1 = move(tmpVal);
                }
            }
        }
    }
  