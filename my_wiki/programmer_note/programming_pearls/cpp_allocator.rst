**************
std::allocator
**************

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

.. code-block:: c++
   :caption: language support

   #include <memory>
   template< class T > struct allocator;
   
The ``std::allocator`` class template is the default Allocator
used by all standard library containers if no user-specified
allocator is provided. The default allocator is stateless,
that is, all instances of the given allocator are interchangeable,
compare equal and can deallocate memory allocated by any other
instance of the same allocator type.

**Example**

#. basic use
   
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

#. C++ allocator Example 1: malloc & free

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
      bool operator==(const Mallocator<T>&, const Mallocator<U>&) { return true; }
      template <typename T, typename U>
      bool operator!=(const Mallocator<T>&, const Mallocator<U>&) { return false; }

#. C++ allocator Example 2: operator new & operator delete

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
      
   Possible output::
   
      $ g++ allocator-dmeo.cpp -std=c++11 && ./a.out
      using reserve: 
      allocating 400 bytes
      deallocating 400 bytes
      not using reserve: 
      allocating 4 bytes
      allocating 8 bytes
      deallocating 4 bytes
      allocating 16 bytes
      deallocating 8 bytes
      allocating 32 bytes
      deallocating 16 bytes
      allocating 64 bytes
      deallocating 32 bytes
      allocating 128 bytes
      deallocating 64 bytes
      allocating 256 bytes
      deallocating 128 bytes
      allocating 512 bytes
      deallocating 256 bytes
      deallocating 512 bytes  