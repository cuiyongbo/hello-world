Predefined Macros
=================

``__FUNCTION__`` is non standard, ``__func__`` exists in C99 / C++11.
The others (``__LINE__`` and ``__FILE__``) are just fine. they will always
report the right file and line. And function if you choose to use ``__FUNCTION__``/``__func__``,
optimization is a non-factor since it is a compile time macro expansion;
it will never effect performance in any way.

.. code-block:: c++
   :caption: Codes taken from Jansson

   #define failhdr fprintf(stderr, "%s:%d: ", __FILE__, __LINE__)


``inline`` keyword
==================

In the C and C++ programming languages, an inline function is one qualified with the keyword ``inline``; this serves two purposes.

   * Firstly, it serves as a compiler directive that suggests (but does not require) that the compiler substitute
     the body of the function inline by performing inline expansion, i.e. by inserting the function code at
     the address of each function call, thereby saving the overhead of a function call.
     In this respect it is analogous to the register storage class specifier, which similarly provides an optimization hint. 

   * The second purpose of inline is to change linkage behavior; the details of this are complicated.
     This is necessary due to the C/C++ separate compilation + linkage model,
     specifically because the definition (body) of the function must be duplicated in all translation units where it is used,
     to allow inlining during compiling, which, if the function has external linkage, causes a collision during linking 
     (it violates uniqueness of external symbols). C and C++ (and dialects such as GNU C and Visual C++) resolve this in different ways.


Microsoft Visual C++ (``__forceinline``) and gcc (``__attribute__((always_inline))``) allow the programmer to
force the compiler to inline a function. Indiscriminate uses of that can result in larger code (bloated executable file),
minimal or no performance gain, and in some cases even a loss in performance.
The compiler cannot inline the function in all circumstances,even when inlining is forced.
In this case both gcc and Visual C++ generate a warning.

Forcing inlining is useful if

   * inline is not respected by the compiler (ignored by compiler cost/benefit analyzer),
   * inlining results in a necessary performance boost
     
For code portability, the following preprocessor directives can be used::

   #ifdef _MSC_VER
   #define forceinline __forceinline
   #elif defined(__GNUC__)
   #define forceinline __attribute__((always_inline)) inline
   #else
   #define forceinline inline
   #endif


Flexible array member
=====================


Flexible array member is a feature introduced in the C99 standard of the C programming language
(in particular, in section §6.7.2.1, item 16, page 103). It is a member of a struct,
which is an array without a given dimension, and it must be the last member of such a struct,
as in the following example::

   struct vectord {
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
   
      struct vectord *vec = malloc(offsetof(struct vectord, arr) 
                                          + len * sizeof(vec->arr[0]));
   
      if (!vec) {
         perror("malloc vectord failed");
         exit(EXIT_FAILURE);
      }
   
      vec->len = len;
   
      for (size_t i = 0; i < len; i++)
         vec->arr[i] = 0;
   
      return vec;
   }

When using structures with a flexible array member, some convention regarding the actual size of that member should be defined.
In the example above, the convention is that the member *arr* has len double-precision numbers.

In previous standards of the C language, it was common to declare a zero-sized array member instead of a flexible array member.
The GCC compiler explicitly accepts zero-sized arrays for such purposes. while C++ does not have flexible array members.

.. note::

   ``offsetof`` is a macro defined in :file:`stddef.h`, typically like this::

      #define offsetof(TYPE, MEMBER) ((size_t) &(((TYPE*)0)->MEMBER))

   .. code-block:: c
      :caption: code block taken from Jansson

         #define container_of(ptr_, type_, member_)  \
                              ((type_ *)((char *)ptr_ - offsetof(type_, member_)))

         #define json_to_object(json_)  container_of(json_, json_object_t, json)
         #define json_to_array(json_)   container_of(json_, json_array_t, json)
         #define json_to_string(json_)  container_of(json_, json_string_t, json)
         #define json_to_real(json_)    container_of(json_, json_real_t, json)
         #define json_to_integer(json_) container_of(json_, json_integer_t, json)



