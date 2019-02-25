*********************
Flexible array member
*********************

Flexible array member is a feature introduced in the C99 standard of the C
programming language. It is a member of a struct, which is an array without
a given dimension, and **it must be the last member of such a struct**,
as in the following example::

    struct vectord 
    {
       size_t len;
       double arr[]; // the flexible array member must be last
    };

The ``sizeof`` operator on such a struct gives the size of the structure as if
the flexible array member had been omitted except that it may have more trailing
padding than the omission would imply. As such it is preferable to use ``offsetof``
when determining size for dynamic allocation, as in the following example::

    size = offsetof(struct vectord, arr) + nr_entries * sizeof(double);

When allocating such structures on the heap, it is generally required to reserve
some space for the flexible array member,as in the following example::

    struct vectord *allocate_vectord (size_t len) 
    {
       struct vectord *vec = malloc(offsetof(struct vectord, arr[len]);
       vec->len = len;
       for (size_t i = 0; i < len; i++)
          vec->arr[i] = 0;
       return vec;
    }
    
    struct Base3
    {
        int count;
        char data[1];
    };

    Base3* bb3 = (Base3*)malloc(offsetof(Base3, data[8]));
    std::cout << offsetof(Base3, data[8]) << '\n'; // 12 in win64 MSVC

    // Taken from linux manual
    struct inotify_event 
    {
       int      wd;       /* Watch descriptor */
       uint32_t mask;     /* Mask describing event */
       uint32_t cookie;   /* Unique cookie associating related
                   events (for rename(2)) */
       uint32_t len;      /* Size of name field */
       char     name[];   /* Optional null-terminated name */
    };

   inotify_event* event = (inotify_event*)malloc(sizeof(inotify_event) + len);

.. code-block:: c++
   :caption: Taken from Jansson library

    struct hashtable_pair 
    {
        struct hashtable_list list;
        struct hashtable_list ordered_list;
        size_t hash;
        json_t *value;
        char key[1]; // also a flexible array member
    };

    {
       // ...
       size_t len = strlen(key);
       pair = jsonp_malloc(offsetof(pair_t, key) + len + 1);
       if(!pair)
          return -1;  
       // ...
    }


.. rubric:: Footnotes

.. [#] `Arrays of Length Zero <http://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html>`_ 
.. [#] `Why do some structures end with an array of size 1? <https://blogs.msdn.microsoft.com/oldnewthing/20040826-00/?p=38043>`_