******************
std\:\:nth_element
******************

**Language support**

.. code-block:: cpp

   #include <algorithm>
   
   template< class RandomIt >
   void nth_element( RandomIt first, RandomIt nth, RandomIt last );
   
   template< class RandomIt, class Compare >
   void nth_element( RandomIt first, RandomIt nth, RandomIt last, Compare comp );

nth_element is a partial sorting algorithm that rearranges elements in ``[first, last)`` such that:

    * The element placed in the nth position is exactly the element 
      that would occur in this position if the range was fully sorted.

    * All of the elements before this new nth element are less than or 
      equal to the elements after the new nth element.

nth may be the end iterator, in this case the function has no effect.

**Complexity**: Linear in ``std::distance(first, last)`` on average.

**Notes**

The algorithm used is typically introselect [#introselect]_ 
although other selection algorithms [#select_sort]_ with suitable average-case complexity are allowed.

.. rubric:: Footnotes

.. [#introselect] https://en.wikipedia.org/wiki/Introselect
.. [#select_sort] https://en.wikipedia.org/wiki/Selection_algorithm