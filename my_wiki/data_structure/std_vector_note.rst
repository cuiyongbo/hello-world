****************
std::vector note
****************

#. `std::vector::reserve` note

    Increase the capacity of the vector to a value that's greater or equal to `new_cap`. 
    If `new_cap` is greater than the current `capacity()`, new storage is allocated, 
    otherwise the method does nothing.

    If `new_cap` is greater than `capacity()`, all iterators, including the past-the-end iterator, 
    and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.

    .. important:: 
    
        Correctly using `reserve()` can prevent unnecessary reallocations, but inappropriate uses of `reserve()` 
        (for instance, calling it before every `push_back()` call) may actually increase the number of reallocations 
        (by causing the capacity to grow linearly rather than exponentially) and result in increased computational 
        complexity and decreased performance. For example, a function that receives an arbitrary vector by reference 
        and appends elements to it should usually not call `reserve()` on the vector, since it does not know of the 
        vector's usage characteristics.

        When inserting a range, the range version of `insert()` is generally preferable as it preserves the correct 
        capacity growth behavior, unlike `reserve()` followed by a series of `push_back()s`.

        `reserve()` cannot be used to reduce the capacity of the container; to that end `shrink_to_fit()` is provided.

        `reserve()` does not change the size of the vector; to that end `resize()` is provided.

#. `std::vector::resize` note

    `resize()` resizes the container to contain count elements.

    If the current size is greater than `count`, the container is reduced to its first `count` elements.
    If the current size is less than `count`, additional elements are appended and initialized with copies of value.

    .. important:: 

        Vector capacity is never reduced when resizing to smaller size because 
        that would invalidate all iterators, rather than only the ones that would
        be invalidated by the equivalent sequence of `pop_back()` calls.