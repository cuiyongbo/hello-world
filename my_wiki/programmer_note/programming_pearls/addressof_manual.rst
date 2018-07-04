**************
std::addressof
**************

.. code-block:: cpp
   :caption: language support

   #include <memory>

   template< class T >
   T* addressof(T& arg) noexcept; // (since C++11) 

**Description**

 ``std::addressof()`` Obtains the actual address of the object or function *arg*, 
 even in presence of overloaded ``operator&``.

.. code-block:: cpp
   :caption: Possible implementation
   
   template< class T > 
   T* addressof(T& arg) 
   {
       return reinterpret_cast<T*>(
                  &const_cast<char&>(
                     reinterpret_cast<const volatile char&>(arg)));
   }

**Example**

.. code-block:: cpp

   #include <iostream>
   #include <memory>
    
   template<class T>
   struct Ptr 
   {
       T* pad; // add pad to show difference between 'this' and 'data'
       T* data;
       Ptr(T* arg) : pad(nullptr), data(arg) 
       {
           std::cout << "Ctor this = " << this << std::endl;
       }
    
       ~Ptr() { delete data; }
       T** operator&() { return &data; }
   };
    
   template<class T>
   void f(Ptr<T>* p) 
   {
       std::cout << "Ptr   overload called with p = " << p << '\n';
   }
    
   void f(int** p) 
   {
       std::cout << "int** overload called with p = " << p << '\n';
   }
    
   int main() 
   {
       Ptr<int> p(new int(42));
       f(&p);                 // calls int** overload
       f(std::addressof(p));  // calls Ptr<int>* overload, (= this)
   }

Possible output::

   $ g++ addressof-demo.cpp -std=c++11 && ./a.out
   Ctor this = 0x7fffbe1fdc80
   int** overload called with p = 0x7fffbe1fdc88
   Ptr   overload called with p = 0x7fffbe1fdc80