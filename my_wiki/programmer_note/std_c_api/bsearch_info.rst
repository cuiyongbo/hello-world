*********************
bsearch and bsearch_s
*********************


.. code-block:: c

   #include <stdlib.h>
   
   void* bsearch( const void *key, const void *ptr, size_t count, size_t size,
                     int (*comp)(const void*, const void*) );
   
   void* bsearch_s( const void *key, const void *ptr, rsize_t count, rsize_t size,
                     int (*comp)(const void *, const void *, void *), void *context);

Finds an element equal to element pointed to by key in an array pointed to by ptr. 
The array contains count elements of size bytes and must be partitioned with respect to key, 
that is, all the elements that compare less than must appear before all the elements that 
compare equal to, and those must appear before all the elements that compare greater than 
the key object. A fully sorted array satisfies these requirements. The elements are compared 
using function pointed to by comp. The behavior is undefined if the array is not already 
partitioned with respect to \*key in ascending order according to the same criterion that comp uses.

If the array contains several elements that comp would indicate as equal to the element searched for, 
then it is unspecified which element the function will return as the result.

.. note::

   Despite the name, neither C nor POSIX standards require this function to be implemented 
   using binary search or make any complexity guarantees.

   Unlike other bounds-checked functions, bsearch_s does not treat arrays of zero size 
   as a runtime constraint violation and instead indicates element not found 
   (the other function that accepts arrays of zero size is qsort_s).

   Until bsearch_s, users of bsearch often used global variables to pass additional 
   context to the comparison function.

.. code-block:: c
   :caption: Example taken from cppreference

   #include <stdio.h>
   #include <stdlib.h>
    
   struct data {
       int nr;
       char const *value;
   } dat[] = {
       {1, "Foo"}, {2, "Bar"}, {3, "Hello"}, {4, "World"}
   };
   
   int data_cmp(void const *lhs, void const *rhs) 
   {
       struct data const *const l = lhs;
       struct data const *const r = rhs;
   
       if (l->nr < r->nr) return -1;
       else if (l->nr > r->nr) return 1;
       else return 0;
    
       // return (l->nr > r->nr) - (l->nr < r->nr); // possible shortcut
       // return l->nr - r->nr; // erroneous shortcut (fails if INT_MIN is present)
   }
   
   int main(void) 
   {
       struct data key = { .nr = 3 };
       struct data const *res = bsearch(&key, dat, sizeof dat / sizeof dat[0],
                                        sizeof dat[0], data_cmp);
       if (res) {
           printf("No %d: %s\n", res->nr, res->value);
       } else {
           printf("No %d not found\n", key.nr);
       }
   }
