:orphan:

******************
Allocator Examples
******************

std::allocator
==============

**Language Support**

   .. code-block:: c++
   
      #include <memory>
      template< class T > struct allocator;
   
   The ``std::allocator`` class template is the default Allocator
   used by all standard library containers if no user-specified
   allocator is provided. The default allocator is stateless,
   that is, all instances of the given allocator are interchangeable,
   compare equal and can deallocate memory allocated by any other
   instance of the same allocator type.

**Example**

.. code-block:: c++

   #include <memory>
   #include <iostream>
   #include <string>
 
   int main()
   {
      std::allocator<int> a1;   // default allocator for ints
      int* a = a1.allocate(1);  // space for one int
      a1.construct(a, 7);       // construct the int
      std::cout << a[0] << '\n';
      a1.deallocate(a, 1);      // deallocate space for one int
    
      // default allocator for strings
      std::allocator<std::string> a2;
      std::string* s = a2.allocate(2); // space for 2 strings
      a2.construct(s, "foo");
      a2.construct(s + 1, "bar");
      std::cout << s[0] << ' ' << s[1] << '\n';
      a2.destroy(s);
      a2.destroy(s + 1);
      a2.deallocate(s, 2);
   }


C++ allocator Example 1: malloc & free
======================================

.. code-block:: c++

   template <typename T>
   struct Mallocator
   {
      typedef T value_type;
      Mallocator() = default;
      template<typename U> Mallocator(const Malloctor<U>&) noexcept {}
      T* allocate(std::size_t n)
      {
         if (n > std::size_t(-1) / sizeof(T)) throw std::bad_alloc();
   
         if (auto p = static_cast<T*>(std::malloc(n*sizeof(T)))) return p;
         throw std::bad_alloc();
      }
      void deallocate(T*p, std::size_t) noexcept { std::free(p); }
   };
   
   template <typename T, typename U>
   bool operator==(const Mallocator<T>&, const Mallocator<T>&) { return true; }
   template <typename T, typename U>
   bool operator!=(const Mallocator<T>&, const Mallocator<T>&) { return false; }


C++ allocator Example 2: operator new & operator delete
=======================================================

.. code-block:: c++

   // minimal C++11 allocator with debug output
   template<typename T>
   struct Nallocator
   {
      typedef T value_type;
      Nallocator() = default;
      template <typename U> Nallocator(const Nalloctor<U>&) {}
      T* allocator(std::size_t n) {
         n *= sizeof(T);
         std::cout << "allocating " << n << " bytes\n";
         return static_cast<T*>(::operator new(n));
      }
      void deallocate(T* p, std::size_t n) {
         std::cout << "deallocating " << n*sizeof*p << " bytes\n";
         ::operator delete(p);
      }
   };
   
   template <typename T, typename U>
   bool operator==(const Nallocator<T>&, const Nallocator<U>&) { return true; }
   template <typename T, typename U>
   bool operator!=(const Nallocator<T>&, const Nallocator<U>&) { return false; }


vector::reserve
===============

.. function:: vector::reserve(size_type new_cap)

   Increase the capacity of the vector to a value that's greater or equal to *new_cap*.
   If *new_cap* is greater than the current ``capacity()``, new storage is allocated,
   otherwise the method does nothing.

   If *new_cap* is greater than ``capacity()``, all iterators, including the past-the-end
   iterator, and all references to the elements are invalidated. Otherwise, no iterators
   or references are invalidated.

   .. note::

      Correctly using ``reserve()`` can prevent unnecessary reallocations, but inappropriate
      uses of ``reserve()`` (for instance, calling it before every ``push_back()`` call) may
      actually increase the number of reallocations (by causing the capacity to grow linearly
      rather than exponentially) and result in increased computational complexity and decreased
      performance. For example, a function that receives an arbitrary vector by reference and
      appends elements to it should usually not call ``reserve()`` on the vector, since it does
      not know of the vector's usage characteristics.

      When inserting a range, the range version of ``insert()`` is generally preferable as it
      preserves the correct capacity growth behavior, unlike ``reserve()`` followed by a series
      of ``push_back()``.

      ``reserve()`` cannot be used to reduce the capacity of the container,
      to that end ``shrink_to_fit()`` is provided.


.. function:: vector::shrink_to_fit()

   Requests the removal of unused capacity.

   It is a non-binding request to reduce ``capacity()`` to ``size()``. It depends on the implementation
   whether the request is fulfilled.

   If reallocation occurs, all iterators, including the past the end iterator, and all references to
   the elements are invalidated. If no reallocation takes place, no iterators or references are
   invalidated.

.. code-block:: c++

   #include <cstddef>
   #include <new>
   #include <vector>
   #include <iostream>
    
   // minimal C++11 allocator with debug output
   template <class Tp>
   struct NAlloc {
       typedef Tp value_type;
       NAlloc() = default;
       template <class T> NAlloc(const NAlloc<T>&) {}
       Tp* allocate(std::size_t n) {
           n *= sizeof(Tp);
           std::cout << "allocating " << n << " bytes\n";
           return static_cast<Tp*>(::operator new(n));
       }
       void deallocate(Tp* p, std::size_t n) {
           std::cout << "deallocating " << n*sizeof*p << " bytes\n";
           ::operator delete(p);
       }
   };
   template <class T, class U>
   bool operator==(const NAlloc<T>&, const NAlloc<U>&) { return true; }
   template <class T, class U>
   bool operator!=(const NAlloc<T>&, const NAlloc<U>&) { return false; }
    
   int main()
   {
       int sz = 100;
       std::cout << "using reserve: \n";
       {
           std::vector<int, NAlloc<int>> v1;
           v1.reserve(sz);
           for(int n = 0; n < sz; ++n)
               v1.push_back(n);
       }
       std::cout << "not using reserve: \n";
       {
           std::vector<int, NAlloc<int>> v1;
           for(int n = 0; n < sz; ++n)
               v1.push_back(n);
       }
   }
   

