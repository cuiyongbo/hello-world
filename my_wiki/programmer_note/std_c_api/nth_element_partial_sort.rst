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

The element pointed at by nth is changed to whatever element would occur in that position 
if ``[first, last)`` were sorted. All of the elements before this new nth element are less 
than or equal to the elements after the new nth element. More formally, nth_element partially 
sorts the range [first, last) in ascending order so that the condition ``comp(*i, *j) == true`` 
is met for any i in the range ``[first, nth)`` and for any j in the range ``[nth, last).``
The element placed in the nth position is exactly the element that would occur in this position 
if the range was fully sorted.

nth may be the end iterator, in this case the function has no effect.

**Complexity**

Linear in ``std::distance(first, last)`` on average.

**Notes**

The algorithm used is typically `introselect <https://en.wikipedia.org/wiki/Introselect>`__ 
although other `selection algorithms <https://en.wikipedia.org/wiki/Selection_algorithm>`__ 
with suitable average-case complexity are allowed.

**Example**

.. code-block:: cpp

   #include <iostream>
   #include <vector>
   #include <algorithm>
   #include <functional>
     
   int main()
   {
       std::vector<int> v{5, 6, 4, 3, 2, 6, 7, 9, 3};
       std::cout << "Originally\n";
       for(int n: v)
           std::cout << n << " ";
       std::cout << '\n'; 
    
       std::nth_element(v.begin(), v.end(), v.end(), std::greater<int>());
       std::cout << "nth_element(v.end())\n";
       for(int n: v)
           std::cout << n << " ";
       std::cout << '\n'; 
   
       std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
       std::cout << "The median is " << v[v.size()/2] << '\n';
       for(int n: v)
           std::cout << n << " ";
       std::cout << '\n'; 
   
       std::nth_element(v.begin(), v.begin()+1, v.end(), std::greater<int>());
       std::cout << "The second largest element is " << v[1] << '\n';
       for(int n: v)
           std::cout << n << " ";
       std::cout << '\n'; 
   }

Output::

   Originally
   5 6 4 3 2 6 7 9 3 
   nth_element(v.end())
   5 6 4 3 2 6 7 9 3 
   The median is 5
   3 2 3 4 5 6 7 9 6 
   The second largest element is 7
   9 7 6 6 5 3 4 3 2 
