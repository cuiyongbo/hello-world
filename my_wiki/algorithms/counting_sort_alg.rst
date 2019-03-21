*************
Counting Sort
*************

**Introduction**

In computer science, counting sort is an algorithm 
for sorting a collection of objects according to keys 
that are small integers; that is, it is an integer 
sorting algorithm. It operates by counting the number 
of objects that have each distinct key value, and using 
arithmetic on those counts to determine the positions 
of each key value in the output sequence. Its running 
time is linear in the number of items and the difference 
between the maximum and minimum key values, so it is only 
suitable for direct use in situations where the variation 
in keys is not significantly greater than the number of items. 
However, it is often used as a subroutine in another sorting 
algorithm, radix sort, that can handle larger keys more efficiently.

Because counting sort uses key values as indexes into an array, 
it is not a comparison sort, and the **O(n log n)** lower bound 
for comparison sorting does not apply to it. Bucket sort may be 
used for many of the same tasks as counting sort, with a similar 
time analysis; however, compared to counting sort, bucket sort 
requires linked lists, dynamic arrays or a large amount of 
preallocated memory to hold the sets of items within each bucket, 
whereas counting sort instead stores a single number (the count of 
items) per bucket.

**Input and output assumptions**

In the most general case, the input to counting sort consists of a collection
of *n* items, each of which has a non-negative integer key whose maximum value
is at most *k*. In some descriptions of counting sort, the input to be sorted is 
assumed to be more simply a sequence of integers itself, but this simplification 
does not accommodate many applications of counting sort. For instance, when used 
as a subroutine in radix sort, the keys for each call to counting sort are individual 
digits of larger item keys; it would not suffice to return only a sorted list of the 
key digits, separated from the items.

The output is an array of the items, in order by their keys. Because of the application 
to radix sorting, it is important for counting sort to be a **stable sort**.

.. code-block:: none
    :caption: Take from *Introduction to algorithms*

    Counting-Sort(A, B, k)
        let C[0, k] be a new array
        for i=0 to k
            C[i] = 0
        for j=1 to A.length
            C[A[j]] = C[A[j]] + 1
        // C[i] contains the number of elements equal to i
        for i=1 to k
            C[i] = C[i] + C[i-1]
        // C[i] contains the number of elements less than or equal to i
        for j=A.length downto 1 // for a stable-sort
            B[C[A[j]]] = A[j]
            C[A[j]] = C[A[j]] - 1

**Complexity analysis**

Because the algorithm uses only simple for loops, without recursion or subroutine calls, 
it is straightforward to analyze. The initialization of the count array, and the second 
for loop which performs a prefix sum on the count array, each iterate at most ``k + 1`` 
times and therefore take **O(k)** time. The other two for loops, and the initialization 
of the output array, each take **O(n)** time. Therefore, the time for the whole algorithm 
is the sum of the times for these steps, **O(n + k)**.

Because it uses arrays of length ``k + 1`` and *n*, the total space usage of the algorithm 
is also ``O(n + k)``. For problem instances in which the maximum key value is significantly 
smaller than the number of items, counting sort can be highly space-efficient, as the only 
storage it uses other than its input and output arrays is the Count array which uses space **O(k)**.

**Variant algorithms**

If each item to be sorted is itself an integer, and used as key as well, then the second 
and third loops of counting sort can be combined; in the second loop, instead of computing 
the position where items with key *i* should be placed in the output, simply append *Count[i]* 
copies of the number *i* to the output.

This algorithm may also be used to **eliminate duplicate keys**, by replacing the Count array 
with a bit vector that stores a one for a key that is present in the input and a zero for 
a key that is not present. If additionally the items are the integer keys themselves, 
both second and third loops can be omitted entirely and the bit vector will itself serve 
as output, representing the values as offsets of the non-zero entries, added to the range's 
lowest value. Thus the keys are sorted and the duplicates are eliminated in this variant 
just by being placed into the bit array.
