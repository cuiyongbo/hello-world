************
std Heapsort
************

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