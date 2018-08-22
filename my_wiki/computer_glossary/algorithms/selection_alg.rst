*******************
Selection Algorithm
*******************

Partial selection sort
======================

A simple example of selection by partial sorting is to use the partial selection sort.

The obvious linear time algorithm to find the minimum (or maximum) – iterating over 
the list and keeping track of the minimum (or maximum) element so far – can be seen 
as a partial selection sort that selects the 1 smallest element. However, many other 
partial sorts also reduce to this algorithm for the case k = 1, such as a partial heap sort.

More generally, a partial selection sort yields a simple selection algorithm which takes **O(kn)** 
time. This is asymptotically inefficient, but can be sufficiently efficient if k is small, and is 
easy to implement. Concretely, we simply find the minimum value and move it to the beginning, repeating 
on the remaining list until we have accumulated k elements, and then return the kth element. Here is 
partial selection sort-based algorithm:

.. code-block:: none

   function select(list[1..n], k)
       for i from 1 to k
           minIndex = i
           for j from i+1 to n
               if list[j] < list[minIndex]
                   minIndex = j
           swap(list[i], list[minIndex])
       return list[k]


.. code-block:: cpp
   :caption: a c++ implementation

   #define swapWithType(Type, a, b) {if(a != b){Type tmp = a; a = b; b = tmp;}}

   void local_kth_element(int* a, int n, int k)
   {
       for(int i=0; i<k; i++)
       {
           int minIdx=i;
           int minVal=a[i];
           for(int j=i+1; j<n; j++)
           {
               if(a[j] < minVal)
               {
                   minIdx=j;
                   minVal = a[j];
               }
           }
           swapWithType(int, a[i], a[minIdx]);
       }
   }

   int main()
   {
       std::vector<int> v{5, 6, 4, 3, 2, 6, 7, 9, 3};
       std::cout << "Originally\n";
       for(int n: v)
           std::cout << n << " ";
       std::cout << '\n'; 
   
       local_kth_element(v.data(), (int)v.size(), 3);
       std::cout << "local_kth_element(3)\n";
       for(int n: v)
           std::cout << n << " ";
       std::cout << '\n'; 
   }

Output::

   Originally
   5 6 4 3 2 6 7 9 3 
   local_kth_element(3)
   2 3 3 6 5 7 4 6 9 


Introselect
===========

In computer science, :abbr:`introselect (introspective selection)` is a selection algorithm that is a hybrid of 
quickselect and median of medians which has fast average performance and optimal worst-case performance. 
Introselect is related to the introsort sorting algorithm: these are analogous refinements of the basic 
quickselect and quicksort algorithms, in that they both start with the quick algorithm, which has good 
average performance and low overhead, but fall back to an optimal worst-case algorithm (with higher overhead) 
if the quick algorithm does not progress rapidly enough. Both algorithms were introduced by *David Musser,* 
with the purpose of providing generic algorithms for the C++ STL which had both fast average performance 
and optimal worst-case performance, thus allowing the performance requirements to be tightened. 
However, in most C++ STL implementations, another introselect algorithm is used, which combines 
quickselect and heapselect, and has a worst-case running time of ``O(n log n).``