************************
C++ Operator overloading
************************

.. [MSDN]   https://msdn.microsoft.com/en-us/library/5tk49fh2.aspx
.. [Cppreference]  https://en.cppreference.com/w/cpp/language/operators

.. contents::
   :local:

Stream extraction and insertion
===============================

The overloads of ``operator>>`` and ``operator<<`` that take a ``std::istream&`` or ``std::ostream&`` 
as the left hand argument are known as insertion and extraction operators. Since they take the user-defined 
type as the right argument (``b in a@b``), they must be implemented as non-members.

.. code-block:: cpp

   std::ostream& operator<<(std::ostream& os, const T& obj)
   {
       // write obj to stream
       return os;
   }
   std::istream& operator>>(std::istream& is, T& obj)
   {
       // read obj from stream
       if( /* T could not be constructed */ )
           is.setstate(std::ios::failbit);
       return is;
   }


Assignment operator
===================

The canonical copy-assignment operator is expected to perform no action on self-assignment, 
and to return the *lhs* by reference::

   // assume the object holds reusable storage, such as a heap-allocated buffer mArray
   T& operator=(const T& other) // copy assignment
   {
       if (this != &other) { // self-assignment check expected
           if (other.size != size) {         // storage cannot be reused
               delete[] mArray;              // destroy storage in this
               size = 0;
               mArray = nullptr;             // preserve invariants in case next line throws
               mArray = new int[other.size]; // create storage in this
               size = other.size;
           } 
           std::copy(other.mArray, other.mArray + other.size, mArray);
       }
       return *this;
   }

The canonical move assignment is expected to leave the moved-from object in invalid state, 
and either do nothing or at least leave the object in a valid state on self-assignment, 
and return the *lhs* by reference to non-const, and be noexcept::

   T& operator=(T&& other) noexcept // move assignment
   {
       if(this != &other) { // no-op on self-move-assignment (delete[]/size=0 also ok)
           delete[] mArray;                               // delete this storage
           mArray = std::exchange(other.mArray, nullptr); // leave moved-from in valid state
           size = std::exchange(other.size, 0);
       }
       return *this;
   }

In those situations where copy assignment cannot benefit from resource reuse (it does not manage a heap-allocated array 
and does not have a (possibly transitive) member that does, such as a member ``std::vector`` or ``std::string``), there 
is a popular convenient shorthand: the copy-and-swap assignment operator, which takes its parameter by value (thus working 
as both copy- and move-assignment depending on the value category of the argument), swaps with the parameter, and lets 
the destructor clean it up::

   T& T::operator=(T arg) noexcept // copy/move constructor is called to construct arg
   {
       swap(arg); // resources are exchanged between *this and arg
       return *this;
   } // destructor of arg is called to release the resources formerly held by *this

This form automatically provides strong exception guarantee, but prohibits resource reuse.


Allocation and deallocation Functions
=====================================

.. code-block:: cpp

   #include <new>

   void* operator new  ( std::size_t count ); (1)
   void* operator new[]( std::size_t count ); (2)

   void operator delete  ( void* ptr );       (3)
   void operator delete[]( void* ptr );       (4)


``operator new / operator new[]`` allocates requested number of bytes. These allocation functions are called by 
*new-expressions* to allocate memory in which new object would then be initialized.

``operator delete / operator delete[]`` Deallocates storage previously allocated by a matching ``operator new.`` 
These deallocation functions are called by *delete-expressions* and by *new-expressions* to deallocate memory 
after destructing (or failing to construct) objects with dynamic storage duration. 

They may also be called using regular function call syntax.

#. Called by non-array *new-expressions* to allocate storage required for a **single object**. The standard library 
   implementation allocates *count* bytes from free store. In case of failure, the standard library implementation 
   calls the function pointer returned by ``std::get_new_handler`` and repeats allocation attempts until new handler 
   does not return or becomes a null pointer, at which time it throws ``std::bad_alloc.`` This function is required 
   to return a pointer suitably aligned to hold an object of any fundamental alignment.

#. Called by the array form of *new[]-expressions* to allocate all storage required for an **array** 
   (including possible new-expression overhead). The standard library implementation calls version (1).

#. Called by delete-expressions to deallocate storage previously allocated for a single object. 
   The behavior of the standard library implementation of this function is undefined unless *ptr* 
   is a null pointer or is a pointer previously obtained from the standard library implementation 
   of ``operator new(size_t)``.

#. Called by *delete[]-expressions* to deallocate storage previously allocated for an array of objects. 
   The behavior of the standard library implementation of this function is undefined unless *ptr* is a 
   null pointer or is a pointer previously obtained from the standard library implementation of 
   ``operator new[](size_t).``


.. note:: 

   Both single-object and array allocation functions may be defined as public static member functions of a class. 
   If defined, these allocation functions are called by *new-expressions* to allocate memory for single objects 
   and arrays of this class, unless the new expression used the form ``::new`` which bypasses class-scope lookup. 
   The keyword static is optional for these functions: whether used or not, the allocation function is a static member function.

   The new expression looks for appropriate allocation function's name firstly in the class scope, and after that in the global 
   scope. Note, that as per name lookup rules, any allocation functions declared in class scope hides all global allocation functions 
   for the new-expressions that attempt to allocate objects of this class.

.. code-block:: cpp
   :caption: Global replacements and Class-specific overloads

   #include <cstdio>
   #include <cstdlib>
   #include <iostream>
   
   // Global replacement of a minimal set of functions:
   void* operator new(std::size_t sz) {
       std::printf("global op new called, size = %zu\n",sz);
       return std::malloc(sz);
   }
   void operator delete(void* ptr) noexcept
   {
       std::puts("global op delete called");
       std::free(ptr);
   }
   
   // class-specific allocation functions
   struct X {
    static void* operator new(std::size_t sz)
    {
        std::cout << "custom new for size " << sz << '\n';
        return ::operator new(sz);
    }
    static void* operator new[](std::size_t sz)
    {
        std::cout << "custom new for size " << sz << '\n';
        return ::operator new(sz);
    }
    int xx;
   };
   
   int main() {
        int* p1 = new int;
        delete p1;
    
        int* p2 = new int[10]; // guaranteed to call the replacement in C++11
        delete[] p2;

        X* x = new X;
        delete x;

        X* xs = new X[2];
        delete[] xs;
   }

Output::

   global op new called, size = 4
   global op delete called
   global op new called, size = 40
   global op delete called
   custom new for size 4
   global op new called, size = 4
   global op delete called
   custom new for size 8
   global op new called, size = 8
   global op delete called


Pointer-to-member operator howto
================================

**Not suggested to use.**

.. code-block:: cpp

   struct  Integer
   {
       int f() {printf("f()\n");}
       int a;
   };
   
   int main()
   {
       Integer tt;
       int (Integer::*intMemPtr);
       intMemPtr = &Integer::a;
       tt.*intMemPtr = 123;
       printf("tt.a = %d\n", tt.a);
   
       int (Integer::*intFunc)();
       intFunc = &Integer::f;
       (tt.*intFunc)();
   
       return 0;
   }

Output::

   tt.a = 123
   f()
