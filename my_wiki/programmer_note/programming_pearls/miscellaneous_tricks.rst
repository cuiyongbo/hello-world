:orphan:

**************************
C/C++ Miscellaneous Tricks
**************************

Macro
=====

See :doc:`macro_tricks`.


``inline`` keyword
==================

In the C and C++ programming languages, an inline function is one qualified with the keyword ``inline``; this serves two purposes.

   * Firstly, it serves as a compiler directive that suggests (but does not require) that the compiler substitute
     the body of the function inline by performing inline expansion, i.e. by inserting the function code at
     the address of each function call, thereby avoiding the overhead of a function call.
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

Introduction
------------

Flexible array member is a feature introduced in the C99 standard of the C
programming language. It is a member of a struct, which is an array without
a given dimension, and **it must be the last member of such a struct**,
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
In the example above, the convention is that the member *arr* has *len* double-precision numbers.

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

More examples
-------------

.. code-block:: c++

   #pragma warning(disable: 4200)

   struct inotify_event {
      int      wd;       /* Watch descriptor */
      uint32_t mask;     /* Mask describing event */
      uint32_t cookie;   /* Unique cookie associating related
                  events (for rename(2)) */
      uint32_t len;      /* Size of name field */
      char     name[];   /* Optional null-terminated name */
   };

   int main()
   {
      const char* str = "hello world";
      uint32 len = (uint32)strlen(str) + 1;
      inotify_event* event = (inotify_event*)malloc(sizeof(inotify_event) + len);
      event->wd = 2;
      event->mask = 7;
      event->cookie = 0;
      event->len = len;
      strcpy(event->name, str);
   
      FILE* fp = fopen("test", "wb");
      fwrite(event, sizeof(inotify_event) + len, 1, fp);
      fclose(fp);
      free(event);
   
      fp = fopen("test", "rb");
      char buffer[1024];
      fread(buffer, 1, sizeof(buffer), fp);
      event = (inotify_event*)buffer;
      fclose(fp);
   }


``sizeof`` operator
===================

**Concept**

Queries size of the object or type.
Used when actual size of the object must be known.

**Syntax**
   
   .. code-block:: c++

      sizeof( type )   
      sizeof expression


Both versions return a constant of type ``std::size_t``.

1) Returns size in bytes of the object representation of *type*.
   
2) Returns size in bytes of the object representation of the type
   that would be returned by *expression*, if evaluated.

**Notes**

Depending on the computer architecture, a byte may consist of 8 or more bits, 
the exact number being recorded in ``CHAR_BIT``.

``sizeof(char)``, ``sizeof(signed char)``, and ``sizeof(unsigned char)`` always return 1.

``sizeof`` cannot be used with function types, incomplete types, or bit-field glvalues.

When applied to a reference type, the result is the size of the referenced type.

When applied to a class type, the result is the size of an object of that class
plus any additional padding required to place such object in an array.

When applied to an empty class type, always returns 1.

When applied to an expression, ``sizeof`` does not evaluate the expression,
and even if the expression designates a polymorphic object, the result is the
size of the static type of the expression.

**Example**

.. code-block:: c++
   :caption: Example 1

   #include <iostream>
    
   struct Empty {};
   struct Base { int a; };
   struct Derived : Base { int b; };
   struct Bit { unsigned bit: 1; };
    
   int main()
   {
      Empty e;
      Derived d;
      Base& b = d;
      Bit bit;
      int a[10];
      std::cout << "size of empty class: "              << sizeof e          << '\n'
         << "size of pointer : "                 << sizeof &e         << '\n'
   //    << "size of function: "                 << sizeof(void())    << '\n'  // error
   //    << "size of incomplete type: "          << sizeof(int[])     << '\n'  // error
   //    << "size of bit field: "                << sizeof bit.bit    << '\n'  // error
         << "size of array of 10 int: "          << sizeof(int[10])   << '\n'
         << "size of array of 10 int (2): "      << sizeof a          << '\n'
         << "length of array of 10 int: "        << ((sizeof a) / (sizeof *a)) << '\n'
         << "length of array of 10 int (2): "    << ((sizeof a) / (sizeof a[0])) << '\n'
         << "size of the Derived: "              << sizeof d          << '\n'
         << "size of the Derived through Base: " << sizeof b          << '\n'; 
   }

.. code-block:: c++
   :caption: Example 2

   #include <iostream>
 
   // objects of type S can be allocated at any address
   // because both S.a and S.b can be allocated at any address
   struct S {
     char a; // size: 1, alignment: 1
     char b; // size: 1, alignment: 1
   }; // size: 2, alignment: 1
    
   // objects of type X must be allocated at 4-byte boundaries
   // because X.n must be allocated at 4-byte boundaries
   // because int's alignment requirement is (usually) 4
   struct X {
     int n;  // size: 4, alignment: 4
     char c; // size: 1, alignment: 1
     // three bytes padding
   }; // size: 8, alignment: 4 
    
   int main() {
      std::cout << "sizeof(S) = " << sizeof(S)
                  << " alignof(S) = " << alignof(S) << '\n';
      std::cout << "sizeof(X) = " << sizeof(X)
                  << " alignof(X) = " << alignof(X) << '\n';
   }


``alignof`` operator
====================

**Language Support**

.. code-block:: c++

   alignof( type-id )      

Queries alignment requirements of a type. Returns a value of type ``std::size_t``.

Returns the alignment,a value of type ``std::size_t`` in bytes, required for any
instance of the type indicated by *type-id*, which is either complete type, an
array type, or a reference type.

If the type is reference type, the operator returns the alignment of referenced type;
if the type is array type, alignment requirement of the element type is returned.

**Example**

.. code-block:: c++

   #include <iostream>
 
   struct Foo {
      int   i;
      float f;
      char  c;
      double d;
   };
    
   struct Empty {};
   struct alignas(64) Empty64 {};
    
   int main()
   {
      std::cout << "Alignment of"  "\n"
         "- char             : " << alignof(char)    << "\n"
         "- pointer          : " << alignof(int*)    << "\n"
         "- class Foo        : " << alignof(Foo)     << "\n"
         "- empty class      : " << alignof(Empty)   << "\n"
         "- alignas(64) Empty: " << alignof(Empty64) << "\n";
   }


Effect of ``extern C`` in C++
=============================

See :doc:`extern_c_linkage`.


Allocator Examples
==================

C++ allocator encapsulates strategies for access/addressing, allocation/deallocation
and construction/destruction of objects.

Every standard library component that may need to allocate or release storage, from
``std::string``, ``std::vector``, and every container except ``std::array``,
to ``std::shared_ptr`` and ``std::function``, does so through an Allocator: an object
of a class type that satisfies the following requirements.

Some requirements are optional: the template ``std::allocator_traits`` supplies the
default implementations for all optional requirements, and all standard library
containers and other allocator-aware classes access the allocator through
``std::allocator_traits``, not directly.

See some examples in :doc:`cpp_allocator`.


Smart Pointer Examples
======================

See in :doc:`cpp_smart_pointer`.


``#pragma pack(n)`` VS ``#pragma pack(push, n)``
================================================

``#pragma pack(n)`` sets compiler alignment to n bytes. Calling pack with no arguments
sets *n* to the value set in the compiler option ``/Zp``. If the compiler option is not
set, the default value is 8.

``#pragma pack(push[,n])`` pushes the current alignment setting on an internal compiler 
stack and then optionally sets the new alignment. ``#pragma pack(pop)`` restores the alignment
setting to the one at the top of the internal compiler stack (and removes that stack entry).

**Note** that ``#paragma pack([n])`` doesn't influence this internal stack; thus it's
possible to have ``#pragma pack(push)`` followed by multiple ``#pragma pack(n)`` instances
and finalized by a single ``#pragma pack(pop)``.

See `MSDN pack directive <https://msdn.microsoft.com/en-us/library/2e70t5y1.aspx>`_ for more
information.

The following sample, taken from MSDN, shows how to use the ``push``, ``pop``,
and ``show`` syntax.

.. code-block:: c++

   // compile with: /W1 /c  
   #pragma pack()   // n defaults to 8; equivalent to /Zp8  
   #pragma pack(show)   // C4810  
   #pragma pack(4)   // n = 4  
   #pragma pack(show)   // C4810  
   #pragma pack(push, r1, 16)   // n = 16, pushed to stack  
   #pragma pack(show)   // C4810  
   #pragma pack(pop, r1, 2)   // n = 2 , stack popped  
   #pragma pack(show)   // C4810  


``std::unordered_multimap::equal_range()``
==========================================

**Language Support**

   .. code-block:: c++
   
      //(since C++11)
      std::pair<iterator,iterator> equal_range( const Key& key ); 
      std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

   Returns a range containing all elements with key *key* in the container. The range
   is defined by two iterators, the first pointing to the first element of the wanted range
   and the second pointing past the last element of the range.

   Return a ``std::pair`` containing a pair of iterators defining the wanted range
   if elements are found. Otherwise, past-the-end (``end()``) iterators are returned
   as both elements of the pair.

**Complexity**

   Average case linear in the number of elements with the key *key*,
   worst case linear in the size of the container.

**Example**

   .. code-block:: c++
      :caption: Example taken from cppreference

      #include <iostream>
      #include <unordered_map>
       
      int main()
      {  
         std::unordered_multimap<int,char> map = {{1,'a'},{2,'b'},{1,'d'},{2,'b'}};
         auto range = map.equal_range(1);
         for (auto it = range.first; it != range.second; ++it) {
            std::cout << it->first << ' ' << it->second << '\n';
         }
         std::cout << std::distance(range.first, range.second) << "\n"; 
      }


printf using '/r'
=================

.. code-block:: c++

   typedef long long int64;
   typedef unsigned long long uint64;
   
   uint64 loaded, total;
   printf("Loaded: %9llu, total: %9llu\r", loaded, total)

