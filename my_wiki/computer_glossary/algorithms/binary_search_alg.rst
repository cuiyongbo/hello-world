*************
Binary search
*************

**Algorithm**

Binary search works on **sorted arrays.** Binary search begins by comparing the middle element of the array with the target value. 
If the target value matches the middle element, its position in the array is returned. If the target value is less than or greater 
than the middle element, the search continues in the lower or upper half of the array, respectively, eliminating the other half 
from consideration.

Given an array A of n elements with values or records :math:`A_0, A_1, ..., A_{n−1},` sorted such that 
:math:`A_0 \le A_1 \le ... \le A_{n−1},` and target value T, the following subroutine uses binary search 
to find the index of T in A.

   - Set L to 0 and R to n − 1.
   - If L > R, the search terminates as unsuccessful.
   - Set m (the position of the middle element) to the ``floor((L + R)/2).``
   - If A[m] < T, set L to m + 1 and go to step 2.
   - If A[m] > T, set R to m − 1 and go to step 2.
   - Now A[m] = T, the search is done; return m.

.. code-block:: none
   :caption: Pseudocode

   function binary_search(A, n, T):
       L := 0
       R := n − 1
       while L <= R:
           m := floor((L + R) / 2)
           if A[m] < T:
               L := m + 1
           else if A[m] > T:
               R := m - 1
           else:
               return m
       return unsuccessful

The procedure may return any index whose element is equal to the target value, 
even if there are duplicate elements in the array. For example, if the array to 
be searched was ``[1, 2, 3, 4, 4, 5, 6, 7]`` and the target was 4, then it would 
be correct for the algorithm to either return the 4th (index 3) or 5th (index 4) element. 
The regular procedure would return the 4th element (index 3). However, it is sometimes necessary 
to find the leftmost element or the rightmost element if the target value is duplicated in the array. 

**Procedure for finding the leftmost element**

To find the leftmost element, the following procedure can be used:

   - Set L to 0 and R to n.
   - If L >= R, go to step 6.
   - Set m (the position of the middle element) to ``floor((L + R)/2).``
   - If A[m] < T, set L to m + 1 and go to step 2.
   - Otherwise, if A[m] >= T, set R to m and go to step 2.
   - Now L = R, the search is done, return L.

If L < n and A[L] = T, then A[L] is the leftmost element that equals T. 
Even if T is not in the array, L is the rank of T in the array, or the 
number of elements in the array that are less than T.

.. code-block:: none
   :caption: Pseudocode

   function binary_search_leftmost(A, n, T):
       L := 0
       R := n
       while L < R:
           m := floor((L + R) / 2)
           if A[m] < T:
               L := m + 1
           else:
               R := m
       return L

**Procedure for finding the rightmost element**

To find the rightmost element, the following procedure can be used:

   - Set L to 0 and R to n.
   - If L >= R, go to step 6.
   - Set m (the position of the middle element) to ``floor((L + R)/2).``
   - If A[m] > T, set R to m and go to step 2.
   - Otherwise, if A[m] <= T, set L to m + 1 and go to step 2.
   - Now L = R, the search is done, return L - 1.

If L > 0 and A[L-1] = T, then A[L-1] is the rightmost element that equals T. 
Even if T is not in the array, n - L is the number of elements in the array 
that are greater than T.

.. code-block:: none
   :caption: Pseudocode

   function binary_search_rightmost(A, n, T):
       L := 0
       R := n
       while L < R:
           m := floor((L + R) / 2)
           if A[m] > T:
               R := m
           else:
               L := m + 1
       return L - 1


.. sidebar:: Performance Analysis

   .. image:: images/Binary_search_complexity.svg.png

   The worst case is reached when the search reaches the deepest level of the tree, 
   while the best case is reached when the target value is the middle element.

**Performance**

The performance of binary search can be analyzed by reducing the procedure to 
a binary comparison tree, where the root node is the middle element of the array. 
The middle element of the lower half is the left child node of the root and the middle 
element of the upper half is the right child node of the root. The rest of the tree is 
built in a similar fashion. This model represents binary search; starting from the root 
node, the left or right subtrees are traversed depending on whether the target value is less 
or more than the node under consideration, representing the successive elimination of elements.

The worst case is :math:`{ \lfloor \log _{2}(n)+1\rfloor }` iterations of the comparison loop, 
The worst case is reached when the search reaches the deepest level of the tree, equivalent to 
a binary search that has reduced to one element and, in each iteration, always eliminates the 
smaller subarray out of the two if they are not of equal size.

**Hashing**

For implementing associative arrays, **hash tables,** a data structure that maps keys to records using a hash function, 
are generally faster than binary search on a sorted array of records; most implementations require only amortized constant 
time on average. However, hashing is not useful for approximate matches, such as computing the next-smallest, next-largest, 
and nearest key, as the only information given on a failed search is that the target is not present in any record. Binary 
search is ideal for such matches, performing them in logarithmic time. Binary search also supports approximate matches. 
Some operations, like finding the smallest and largest element, can be done efficiently on sorted arrays but not on hash tables.

**Trees**

Binary search trees are searched using an algorithm similar to binary search.
A binary search tree is a binary tree data structure that works based on the principle of binary search. 
The records of the tree are arranged in sorted order, and each record in the tree can be searched using 
an algorithm similar to binary search, taking on average logarithmic time. Insertion and deletion also 
require on average logarithmic time in binary search trees. This can be faster than the linear time 
insertion and deletion of sorted arrays, and binary trees retain the ability to perform all the operations 
possible on a sorted array, including range and approximate queries.

However, binary search is usually more efficient for searching as binary search trees will most likely be 
imperfectly balanced, resulting in slightly worse performance than binary search. This even applies to balanced 
binary search trees, binary search trees that balance their own nodes, because they rarely produce optimally-balanced 
trees. Although unlikely, the tree may be severely imbalanced with few internal nodes with two children, resulting in 
the average and worst-case search time approaching n comparisons. Binary search trees take more space than sorted arrays.

Binary search trees lend themselves to fast searching in external memory stored in hard disks, as binary search trees 
can efficiently be structured in filesystems. The B-tree generalizes this method of tree organization; B-trees are frequently 
used to organize long-term storage such as databases and filesystems.

**Linear search**

Linear search is a simple search algorithm that checks every record until it finds the target value. Linear search can be done on 
a linked list, which allows for faster insertion and deletion than an array. Binary search is faster than linear search for sorted 
arrays except if the array is short, although the array needs to be sorted beforehand. All sorting algorithms based on comparing elements, 
such as quicksort and merge sort, require at least :math:`O(n\log n)` comparisons in the worst case. Unlike linear search, binary search can 
be used for efficient approximate matching. There are operations such as finding the smallest and largest element that can be done efficiently 
on a sorted array but not on an unsorted array.

**Set membership algorithms**

A related problem to search is set membership. Any algorithm that does lookup, like binary search, can also be used for set membership. 
There are other algorithms that are more specifically suited for set membership. A bit array is the simplest, useful when the range of keys 
is limited. It compactly stores a collection of bits, with each bit representing a single key within the range of keys. Bit arrays are very 
fast, requiring only **O(1)** time. 

For approximate results, **Bloom filters,** another probabilistic data structure based on hashing, store a set of keys by encoding the keys 
using a bit array and multiple hash functions. Bloom filters are much more space-efficient than bit arrays in most cases and not much slower: 
with k hash functions, membership queries require only **O(k)** time. However, Bloom filters suffer from false positives.

**Other data structures**

There exist data structures that may improve on binary search in some cases for both searching and other operations available for sorted arrays. 
For example, searches, approximate matches, and the operations available to sorted arrays can be performed more efficiently than binary search 
on specialized data structures such as **van Emde Boas trees, fusion trees, tries, and bit arrays.** However, while these operations can always 
be done at least efficiently on a sorted array regardless of the keys, such data structures are usually only faster because they exploit the 
properties of keys with a certain attribute (usually keys that are small integers), and thus will be time or space consuming for keys that 
lack that attribute. Some structures, such as **Judy arrays,** use a combination of approaches to mitigate this while retaining efficiency 
and the ability to perform approximate matching