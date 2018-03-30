POD Type
========

Concepts
--------

Specifies that the type is :abbr:`POD (Plain Old Data)` type. This means the type is compatible with the types
used in the C programming language, can be manipulated using C library functions: it can be created with ``std::malloc``,
it can be copied with ``std::memmove``, etc, and can be exchanged with C libraries directly, in its binary form.

Note, that the standard doesn't define a named requirement or concept with this name.
This is a type category defined by the core language. It is included here as concept only for consistency.


Basics::

   std::is_pod
   
   Defined in header <type_traits>
   
   template< class T >
   struct is_pod;

   template< class T >
   struct is_standard_layout;

If T is a :abbr:`PODType (plain old data type)`, that is, both trivial and standard-layout,
provides the member constant *value* equal ``true``. For any other type, *value* is ``false``.

a class type (class or struct or union) that:

   * has no user-defined copy constructor;
   * has no user-defined destructor;
   * All non-static data members have the same access control
   * Has no virtual functions or virtual base classes
   * Has no non-static data members of reference type
   * All non-static data members and base classes are themselves POD;

Example

   .. code-block:: c++
   
      #include <iostream>
      #include <type_traits>
    
      struct A {
          int m;
      };
      
      struct B {
          int m1;
      private:
          int m2;
      };
       
      struct C {
          virtual void foo();
      };
      
      struct Point
      {
         int x, y;
      
         float length() {return 0.0f;};   // it can have members
      };
      
      int main()
      {
          std::cout << std::boolalpha;
          std::cout << std::is_pod<A>::value << '\n';
          std::cout << std::is_pod<B>::value << '\n';
          std::cout << std::is_pod<C>::value << '\n';
          std::cout << std::is_pod<Point>::value << '\n';
      }  

