************
std::bsearch
************

.. code-block:: c

    #include <stdlib.h>
    void* bsearch( const void *key, const void *ptr, size_t count, size_t size,
                      int (*comp)(const void*, const void*) );
    void* bsearch_s( const void *key, const void *ptr, rsize_t count, rsize_t size,
                      int (*comp)(const void *, const void *, void *), void *context);

Finds an element equal to element pointed to by `key` in an array pointed to by ptr. 
The array contains `count` elements of `size` bytes and must be sorted with elements compared 
using function pointed by `comp`. If the array contains several elements that `comp` would 
indicate as equal to the element searched for, then it is unspecified which element the 
function will return as the result.

.. note::

    Despite the name, neither C nor POSIX standards require this function to be implemented 
    using binary search or make any complexity guarantees.

    Until `bsearch_s`, users of bsearch often used global variables to pass additional 
    context to the comparison function.