**************
std::allocator
**************

**Overview**

C++ allocator encapsulates strategies for access/addressing, allocation/deallocation
and construction/destruction of objects.

Every standard library component that may need to allocate or release storage, 
from `std::string`, `std::vector`, and every container except `std::array`,
to `std::shared_ptr` and `std::function`, does so through an Allocator.

Some requirements are optional: the template ``std::allocator_traits`` supplies the
default implementations for all optional requirements, and all standard library
containers and other allocator-aware classes access the allocator through
``std::allocator_traits``, not directly.
   
The ``std::allocator`` class template is the default Allocator used by all std containers if no user-specified
allocator is provided. The default allocator is stateless, that is, all instances of the given allocator are 
interchangeable, compare equal and can deallocate memory allocated by any otherinstance of the same allocator type.

As mentioned, *allocate* and *deallocate* are simply low level memory management 
and do not play a part in object construction and destruction. This would mean 
that the default usage of the keywords ``new`` and ``delete`` would not apply in 
these functions. As any intermediate C++ programmer should know, the following 
code::

    A* a = new A;
    delete a;

is actually interpreted by the compiler as::

    // assuming new throws std::bad_alloc upon failure
    A* a = ::operator new(sizeof(A)); 
    a->A::A();
    if ( a != 0 ) 
    {  // a check is necessary for delete
        a->~A();
        ::operator delete(a);
    }

**Implementation**

.. code-block:: cpp
    :caption: MSVC std::allocator implementation

    template<class _Ty>
    struct _Allocator_base
    {  // base class for generic allocators
       typedef _Ty value_type;
    };

    template<class _Ty>
    class allocator : public _Allocator_base<_Ty>
    {  // generic allocator for objects of class _Ty
    public:

        pointer address(reference _Val) const _NOEXCEPT
        {  // return address of mutable _Val
           return (_STD addressof(_Val));
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
   
      // ....
    };

    template<class _Ty> inline
    _Ty *_Allocate(size_t _Count, _Ty *)
    {   // allocate storage for _Count elements of type _Ty
        void *_Ptr = 0;
        if (_Count == 0)
            ;
        else if (((size_t)(-1) / sizeof (_Ty) < _Count)
            || (_Ptr = ::operator new(_Count * sizeof (_Ty))) == 0)
            _Xbad_alloc();  // report no memory
    
        return ((_Ty *)_Ptr);
    }

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