**************
std::allocator
**************

**Overview**

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

**Implementation**

.. code-block:: cpp
   :caption: MSVC std::allocator implementation

   template<class _Ty>
   struct _Allocator_base
   {  // base class for generic allocators
      typedef _Ty value_type;
   };
   
   template<class _Ty>
   struct _Allocator_base<const _Ty>
   {  // base class for generic allocators for const _Ty
      typedef _Ty value_type;
   };

   template<class _Ty>
   class allocator : public _Allocator_base<_Ty>
   {  // generic allocator for objects of class _Ty
   public:
   
      typedef _Allocator_base<_Ty> _Mybase;
      typedef typename _Mybase::value_type value_type;
   
      typedef value_type *pointer;
      typedef const value_type *const_pointer;
      typedef void *void_pointer;
      typedef const void *const_void_pointer;
   
      typedef value_type& reference;
      typedef const value_type& const_reference;
   
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
   
      pointer address(reference _Val) const _NOEXCEPT
      {  // return address of mutable _Val
         return (_STD addressof(_Val));
      }
   
      allocator() _THROW0()
      {  // construct default allocator (do nothing)
      }
   
      template<class _Other>
      allocator<_Ty>& operator=(const allocator<_Other>&)
      {  // assign from a related allocator (do nothing)
         return (*this);
      }
   
      void deallocate(pointer _Ptr, size_type)
      {  // deallocate object at _Ptr, ignore size
         ::operator delete(_Ptr);
      }
   
      pointer allocate(size_type _Count)
      {  // allocate array of _Count elements
         return (_Allocate(_Count, (pointer)0));
      }
   
      void construct(_Ty *_Ptr)
      {  // default construct object at _Ptr
         ::new ((void *)_Ptr) _Ty();
      }
   
      template<class _Uty>
      void destroy(_Uty *_Ptr)
      {  // destroy object at _Ptr
         _Ptr->~_Uty();
      }
   
      size_t max_size() const _THROW0()
      {  // estimate maximum array size
         return ((size_t)(-1) / sizeof (_Ty));
      }
   
      // ....
   };

   template<class _Ty, class _Other> inline
   bool operator==(const allocator<_Ty>&, const allocator<_Other>&) _THROW0()
   {  // test for allocator equality
      return (true);
   }

   template<class _Ty, class _Other> inline
   bool operator!=(const allocator<_Ty>& _Left, const allocator<_Other>& _Right) _THROW0()
   {  // test for allocator inequality
      return (!(_Left == _Right));
   }

.. code-block:: cpp
   :caption: MSVC std::allocator_traits implementation

   template<class _Ty>
   struct allocator_traits<allocator<_Ty> >
   {  // defines traits for allocators (increases compiler speed)
   
      static pointer allocate(_Alloc& _Al, size_type _Count)
      {  // allocate array of _Count elements
         return (_Al.allocate(_Count));
      }
   
      static pointer allocate(_Alloc& _Al, size_type _Count, const_void_pointer _Hint)
      {  // allocate array of _Count elements, with hint
         return (_Al.allocate(_Count, _Hint));
      }
   
      template<class _Objty, class... _Types>
      static void construct(_Alloc& _Al, _Objty *_Ptr, _Types&&... _Args)
      {  // construct _Objty(_Types...) at _Ptr
         _Al.construct(_Ptr, _STD forward<_Types>(_Args)...);
      }
   
   
      template<class _Uty>
      static void destroy(_Alloc& _Al, _Uty *_Ptr)
      {  // destroy object at _Ptr
         _Al.destroy(_Ptr);
      }
   
      static size_type max_size(const _Alloc& _Al)
      {  // get maximum size
         return (_Al.max_size());
      }
   };






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