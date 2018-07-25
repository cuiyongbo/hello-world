*********
Heap Sort
*********

.. note::

   A max heap is a range of elements [f,l) that has the following properties:

      * With N = l - f, for all 0 < i < N, f[floor((i-1)/2)] does not compare less than f[i].
      * a new element can be added using ``std::push_heap().``
      * the first element can be removed ``using std::pop_heap().``


**Language Support**

.. code-block:: cpp

   #include <algorithm>

   template< class RandomIt >
   void make_heap( RandomIt first, RandomIt last );
   
   template< class RandomIt, class Compare >
   void make_heap( RandomIt first, RandomIt last, Compare comp );

   template< class RandomIt >
   void pop_heap( RandomIt first, RandomIt last );
   
   template< class RandomIt, class Compare >
   void pop_heap( RandomIt first, RandomIt last, Compare comp );

   template< class RandomIt >
   void push_heap( RandomIt first, RandomIt last );
   
   template< class RandomIt, class Compare >
   void push_heap( RandomIt first, RandomIt last, Compare comp );

*make_heap()* constructs a max heap in the range [first, last). The first version of the function 
uses ``operator<`` to compare the elements, the second uses the given comparison function ``comp``.

*pop_heap()* swaps the value in the position ``first`` and the value in the position ``last-1`` 
and makes the subrange ``[first, last-1)`` into a max heap. This has the effect of 
removing the first (largest) element from the heap defined by the range ``[first, last)``.

*push_heap()* Inserts the element at the position ``last-1`` into the max heap defined by the 
range ``[first, last-1).`` 

.. note::

   *comp* returns ``​true`` if the first argument is less than the second. 
   The signature of the comparison function should be equivalent to the following:
   ``bool cmp(const Type1 &a, const Type2 &b);`` The signature does not need to 
   have ``const &``, but the function object must not modify the objects passed to it.
   The types *Type1* and *Type2* must be such that an object of type *RandomIt* can be 
   dereferenced and then implicitly converted to both of them. ​


**Complexity**


* At most ``3*std::distance(first, last)`` comparisons for *make_heap().*
* At most 2log(N) comparisons where ``N=std::distance(first, last)`` for *pop_heap().*
* At most log(N) comparisons where ``N=std::distance(first, last).`` for *push_heap().*


**Example**


.. code-block:: cpp

   #include <iostream>
   #include <algorithm>
   #include <vector>
    
   int main()
   {
       std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    
       std::cout << "initially, v: ";
       for (auto i : v) std::cout << i << ' ';
       std::cout << '\n';
    
       std::make_heap(v.begin(), v.end());
    
       std::cout << "after make_heap, v: ";
       for (auto i : v) std::cout << i << ' ';
       std::cout << '\n';
    
       std::pop_heap(v.begin(), v.end());
       auto largest = v.back();
       v.pop_back();
       std::cout << "largest element: " << largest << '\n';
    
       std::cout << "after pop_heap, v: ";
       for (auto i : v) std::cout << i << ' ';
       std::cout << '\n';
   
       v.push_back(8);
       std::push_heap(v.begin(), v.end());
   
       std::cout << "after push_heap, v: ";
       for (auto i : v) std::cout << i << ' ';
       std::cout << '\n';
   }

Output::

   initially, v: 3 1 4 1 5 9 
   after make_heap, v: 9 5 4 1 1 3 
   largest element: 9
   after pop_heap, v: 5 3 4 1 1 
   after push_heap, v: 8 3 5 1 1 4