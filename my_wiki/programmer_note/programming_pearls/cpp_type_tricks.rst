:orphan:

**********************
C/C++ Data Type tricks
**********************

POD Type
========

Concepts
--------

   Specifies that the type is :abbr:`POD (Plain Old Data)` type. This means the type is compatible with the types
   used in the C programming language, can be manipulated using C library functions: it can be created with
   ``std\:\:malloc``, it can be copied with ``std\:\:memmove``, etc, and can be exchanged with C libraries directly,
   in its binary form.
   
   Note that the standard doesn't define a named requirement or concept with this name.
   This is a type category defined by the core language. It is included here as concept
   only for consistency.

Language Support
----------------
   
   .. code-block:: c++
      
      #include <type_traits>   
      template< class T > struct is_pod;
      template< class T > struct is_standard_layout;

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
-------

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
      
      struct Point {
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


C/C++ int-string Conversion
===========================

#. string --> number
   
   .. code-block:: c++

      int num1 = atoi(str);
      long num2 = atol(str);
      double num3 = atof(str);

#. number --> string
   
   .. code-block:: c++

      int sprintf( char* buffer, const char* format, ... );
      int snprintf( char* buffer, std::size_t buf_size, const char* format, ... );

      // using sprintf
      char* buffer[32];
      int value = 4564;
      sprintf(buffer, "%d", value);
      
      // using snprintf
      char buffer[10];
      int value = 234452;
      snprintf(buffer, 10, "%d", value);


   .. note::
   
      you can convert a string to integer type, or otherwise, using :class:`std\:\:istringstream` 
      and :class:`std\:\:ostringstream` like this::
   
         istringstream convert1(Text); //string Text="456"
         convert1 >> Number; //string to int, Number=456
         ostringstream convert2;
         convert2 << Number;
         Text = convert2.str(); //int to string, Text="456"

   
Character types
===============

* ``signed char`` - type for signed character representation.

* ``unsigned char`` - type for unsigned character representation.
  Also used to inspect object representations (raw memory).

* ``char`` - type for character representation which can be most efficiently
  processed on the target system (has the same representation and alignment
  as either signed char or unsigned char, but is always a distinct type).
  Multibyte characters strings use this type to represent code units. The
  character types are large enough to represent any UTF-8 code unit (since C++14).
  The signedness of char depends on the compiler and the target platform: the
  defaults for ARM and PowerPC are typically unsigned, the defaults for x86
  and x64 are typically signed.

* ``wchar_t`` - type for wide character representation. Required to be large
  enough to represent any supported character code point (32 bits on systems
  that support Unicode. A notable exception is Windows, where wchar_t is 16
  bits and holds UTF-16 code units) It has the same size, signedness, and
  alignment as one of the integer types, but is a distinct type.

.. note::

   * char16_t - type for UTF-16 character representation, required to be
     large enough to represent any UTF-16 code unit (16 bits). It has the
     same size, signedness, and alignment as ``std\:\:uint_least16_t``, but
     is a distinct type.

   * ``char32_t`` - type for UTF-32 character representation, required to be
     large enough to represent any UTF-32 code unit (32 bits). It has the same
     size, signedness, and alignment as ``std\:\:uint_least32_t``, but is a
     distinct type.
