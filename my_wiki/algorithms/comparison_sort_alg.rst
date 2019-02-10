***************
Comparison Sort
***************

Introduction
============

A comparison sort is a type of sorting algorithm that only reads the list elements 
through a single abstract comparison operation (often a "less than or equal to" operator 
or a three-way comparison) that determines which of two elements should occur first in 
the final sorted list. The only requirement is that the operator obey two of the 
properties of a total order:

   * if a ≤ b and b ≤ c then a ≤ c (transitivity).
   * for all a and b, either a ≤ b or b ≤ a (totalness or trichotomy).

It is possible that both ``a ≤ b and b ≤ a``; in this case either may come first in the sorted list. 
In a stable sort, the input order determines the sorted order in this case.

.. sidebar:: Balance Scale

   .. image:: images/Balance_Scale.JPG

   Sorting a set of unlabelled weights by weight using only 
   a balance scale requires a comparison sort algorithm

A metaphor for thinking about comparison sorts is that someone has a set 
of unlabelled weights and a balance scale. Their goal is to line up the 
weights in order by their weight without any information except that 
obtained by placing two weights on the scale and seeing which one is 
heavier (or if they weigh the same).


Examples
========

* Quicksort
* Heapsort
* Shellsort
* Merge sort
* Introsort
* Insertion sort
* Selection sort
* Bubble sort
* Odd–even sort
* Cocktail shaker sort
* Cycle sort
* Merge insertion (Ford–Johnson) sort
* Smoothsort
* Timsort
  

Performance limits and advantages of different sorting techniques
=================================================================

There are fundamental limits on the performance of comparison sorts. 
A comparison sort must have an average-case lower bound of **O(n log n)** 
comparison operations, which is known as linearithmic time. This is a 
consequence of the limited information available through comparisons 
alone — or, to put it differently, of the vague algebraic structure of 
totally ordered sets. In this sense, mergesort, heapsort, and introsort 
are asymptotically optimal in terms of the number of comparisons they 
must perform, although this metric neglects other operations. 
Non-comparison sorts (such as the examples discussed below) can achieve 
**O(n)** performance by using operations other than comparisons, allowing 
them to sidestep this lower bound (assuming elements are constant-sized).

Note that comparison sorts may run faster on some lists; many adaptive sorts 
such as insertion sort run in **O(n)** time on an already-sorted or nearly-sorted 
list. The **O(n log n)** lower bound applies only to the case in which the input 
list can be in any possible order.

Also note that real-world measures of sorting speed may need to take into account 
the ability of some algorithms to optimally use relatively fast cached computer 
memory, or the application may benefit from sorting methods where sorted data 
begins to appear to the user quickly (and then user's speed of reading will be 
the limiting factor) as opposed to sorting methods where no output is available 
for display until the whole list is sorted.

Despite these limitations, comparison sorts offer the notable practical advantage 
that control over the comparison function allows sorting of many different datatypes 
and fine control over how the list is sorted. For example, reversing the result of the 
comparison function allows the list to be sorted in reverse; and one can sort a list of 
tuples in lexicographic order by just creating a comparison function that compares each 
part in sequence::

   function tupleCompare((lefta, leftb, leftc), (righta, rightb, rightc))
    if lefta ≠ righta
        return compare(lefta, righta)
    else if leftb ≠ rightb
        return compare(leftb, rightb)
    else
        return compare(leftc, rightc)

Balanced ternary notation allows comparisons to be made in one step, whose result will be 
one of "less than", "greater than" or "equal to".

Comparison sorts generally adapt more easily to complex orders such as the order of floating-point 
numbers. Additionally, once a comparison function is written, any comparison sort can be used without 
modification; non-comparison sorts typically require specialized versions for each datatype.

This flexibility, together with the efficiency of the above comparison sorting algorithms on modern 
computers, has led to widespread preference for comparison sorts in most practical work.


Alternatives
============

Some sorting problems admit a strictly faster solution than the :math:`O(n \log n)` bound for comparison sorting; 
an example is integer sorting, where all keys are integers. When the keys form a small (compared to n) range, 
counting sort is an example algorithm that runs in linear time. Other integer sorting algorithms, such as 
radix sort, are not asymptotically faster than comparison sorting, but can be faster in practice.

The problem of sorting pairs of numbers by their sum is not subject to the :math:`\Omega(n^2 \log n)` bound either 
(the square resulting from the pairing up); the best known algorithm still takes :math:`\Omega(n^2 \log n)` time, 
but only :math:`\Omega(n^2)` comparisons.


Number of comparisons required to sort a list
=============================================

The number of comparisons that a comparison sort algorithm requires increases in proportion to 
:math:`O(n \log n)`, where *n* is the number of elements to sort. This bound is asymptotically 
tight.

Given a list of distinct numbers (we can assume this because this is a worst-case analysis), 
there are :math:`n!` permutations exactly one of which is the list in sorted order. 
The sort algorithm must gain enough information from the comparisons to identify the correct 
permutation. If the algorithm always completes after at most **f(n)** steps, it cannot distinguish 
more than :math:`2^{f(n)}` cases because the keys are distinct and each comparison has only two 
possible outcomes. Therefore,

.. math::

   2^{f(n)} \ge n!,\ or\ equivalently\ f(n) \ge \log_2 (n!)

From Stirling's approximation we know that

.. math::

   \log_2 (n!) = n\log_2 n - n\log_2 e + O(\log n) = \Omega(n^2 \log_2 n)

This provides the lower-bound part of the claim.

An identical upper bound follows from the existence of the algorithms that attain 
this bound in the worst case. 

The above argument provides an absolute, rather than only asymptotic lower bound 
on the number of comparisons, namely :math:`\log_2 (n!)` comparisons. This lower 
bound is fairly good (it can be approached within a linear tolerance by a simple 
merge sort), but it is known to be inexact. For example, :math:`\log_2 (13!) = 33`,
but the minimal number of comparisons to sort 13 elements has been proved to be 34. 
Determining the exact number of comparisons needed to sort a given number of entries 
is a computationally hard problem even for small *n*, and no simple formula for the 
solution is known. 


Lower bound for the average number of comparisons
=================================================

A similar bound applies to the average number of comparisons. Assuming that

   * all keys are distinct, i.e. every comparison will give either a>b or a<b.
   * the input is a random permutation, chosen uniformly from the set of all 
     possible permutations of n elements,

it is impossible to determine which order the input is in with fewer than 
:math:`\log_2 (n!)` comparisons on average.

This can be most easily seen using concepts from information theory. 
The Shannon entropy of such a random permutation is :math:`\log_2 (n!)` 
bits. Since a comparison can give only two results, the maximum amount 
of information it provides is 1 bit. Therefore, after *k* comparisons the 
remaining entropy of the permutation, given the results of those comparisons, 
is at least :math:`\log_2 (n!)\ -\ k` bits on average. To perform the sort, 
complete information is needed, so the remaining entropy must be 0. It follows 
that *k* must be at least :math:`\log_2 (n!)`.

Note that this differs from the worst case argument given above, in that it does 
not allow rounding up to the nearest integer. For example, for ``n = 3``, the lower 
bound for the worst case is 3, the lower bound for the average case as shown above 
is approximately 2.58, while the highest lower bound for the average case is 
8/3 (:math:`\frac{2^n}{n}`), approximately 2.67.

In the case that multiple items may have the same key, there is no obvious statistical 
interpretation for the term "average case", so an argument like the above cannot be applied 
without making specific assumptions about the distribution of keys.
