**************************
C/C++ Miscellaneous Tricks
**************************

.. toctree::
   :titlesonly:

   addressof_manual
   macro_tricks
   extern_c_linkage
   cpp_smart_pointer
   cpp_allocator
   pointer_to_function_demo
   flexible_array_tricks
   cpp_std_map_notes
   cpp_atomic_note

.. contents::
   :local:

#. ``inline`` keyword

   In the C and C++ programming languages, an inline function is one qualified with the keyword ``inline``; 
   this serves two purposes:
   
      * Firstly, it serves as a compiler directive that suggests (but does not require) that the compiler 
        substitute the body of the function inline by performing inline expansion, i.e. by inserting the 
        function code at the address of each function call, thereby avoiding the overhead of a function call.
        In this respect it is analogous to the register storage class specifier, which similarly provides 
        an optimization hint. 
   
      * The second purpose of inline is to change linkage behavior; the details of this are complicated.
        This is necessary due to the C/C++'s separate compilation + linkage model, specifically because 
        the definition (body) of the function must be duplicated in all translation units where it is used,
        to allow inlining during compiling, which, if the function has external linkage, causes a collision 
        during linking (it violates uniqueness of external symbols). 
   
   Indiscriminate uses of inline function can result in larger code (bloated executable file), 
   minimal or no performance gain, and in some cases even a loss in performance.
   The compiler cannot inline the function in all circumstances, even when inlining is forced.
   
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

#. ``sizeof`` operator

   .. code-block:: cpp

      sizeof( type )   
      sizeof expression

   Queries size of the object or type.
   Used when actual size of the object must be known.
   Both versions return a constant of type ``std::size_t``.
   
   1) Returns size in bytes of the object representation of *type*.
      
   2) Returns size in bytes of the object representation of the type
      that would be returned by *expression*, if evaluated.

   ``sizeof`` cannot be used with function types, incomplete types, or bit-field glvalues.
   When applied to a reference type, the result is the size of the referenced type.
   When applied to a class type, the result is the size of an object of that class
   plus any additional padding required to place such object in an array.
   When applied to an empty class type, always returns 1.
   When applied to an expression, ``sizeof`` does not evaluate the expression,
   and even if the expression designates a polymorphic object, the result is the
   size of the static type of the expression.
   
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

#. ``alignof`` operator

   .. code-block:: cpp
   
      alignof( type-id )      
   
   Queries alignment requirements of a type. Returns a value of type ``std::size_t``.
   
   Returns the alignment,a value of type ``std::size_t`` in bytes, required for any
   instance of the type indicated by *type-id*, which is either complete type, an
   array type, or a reference type.
   
   If the type is reference type, the operator returns the alignment of referenced type;
   if the type is array type, alignment requirement of the element type is returned.
   
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
   

#. ``#pragma pack(n)`` VS ``#pragma pack(push, n)``

   ``#pragma pack(n)`` sets compiler alignment to n bytes. Calling pack with no arguments
   sets *n* to the value set in the compiler option ``/Zp``. If the compiler option is not
   set, the default value is 8.
   
   ``#pragma pack(push[,n])`` pushes the current alignment setting on an internal compiler 
   stack and then optionally sets the new alignment. ``#pragma pack(pop)`` restores the alignment
   setting to the one at the top of the internal compiler stack (and removes that stack entry).
   
   **Note** that ``#paragma pack([n])`` doesn't influence this internal stack; thus it's
   possible to have ``#pragma pack(push)`` followed by multiple ``#pragma pack(n)`` instances
   and finalized by a single ``#pragma pack(pop)``.
   
   .. code-block:: cpp
      :caption: taken from `MSDN pack directive <https://msdn.microsoft.com/en-us/library/2e70t5y1.aspx>`_
   
      // compile with: /W1 /c  
      #pragma pack()   // n defaults to 8; equivalent to /Zp8  
      #pragma pack(show)   // C4810  
      #pragma pack(4)   // n = 4  
      #pragma pack(show)   // C4810  
      #pragma pack(push, r1, 16)   // n = 16, pushed to stack  
      #pragma pack(show)   // C4810  
      #pragma pack(pop, r1, 2)   // n = 2 , stack popped  
      #pragma pack(show)   // C4810  
  
#. Use constant :math:`\pi`
   
   .. code-block:: c

      // math.h
      #define M_PI        3.14159265358979323846264338327950288
      #define M_PI_2      1.57079632679489661923132169163975144
      #define M_PI_4      0.785398163397448309615660845819875721

#. Disable compiler warnings

   .. code-block:: c

      #if defined(__clang__)
      // disable warning about "this != NULL"
      #  pragma clang diagnostic ignored "-Wtautological-undefined-compare"
      // disabled warning "delete called on non-final 'XXX' that has virtual functions but non-virtual destructor [-Wdelete-non-virtual-dtor]"
      #  pragma clang diagnostic ignored "-Wdelete-non-virtual-dtor"
      #elif defined(__GNUC__)
      #  pragma GCC diagnostic ignored "-Wunknown-pragmas"
      #endif
      #if defined(_MSC_VER)
      #  pragma warning(disable: 4068)
      #endif

#. explicit keyword
   
  The explicit specifier specifies that a constructor or conversion function is explicit, 
  that is, it cannot be used for implicit conversions and copy-initialization.

   A constructor with a single non-default parameter that is declared without 
   the function specifier explicit is called a converting constructor.

   .. code-block:: cpp

      struct A
      {
          A(int) { }      // converting constructor
          A(int, int) { } // converting constructor (C++11)
          operator bool() const { return true; }
      };
       
      struct B
      {
          explicit B(int) { }
          explicit B(int, int) { }
          explicit operator bool() const { return true; }
      };
       
      int main()
      {
          A a1 = 1;      // OK: copy-initialization selects A::A(int)
          A a2(2);       // OK: direct-initialization selects A::A(int)
          A a3 {4, 5};   // OK: direct-list-initialization selects A::A(int, int)
          A a4 = {4, 5}; // OK: copy-list-initialization selects A::A(int, int)
          A a5 = (A)1;   // OK: explicit cast performs static_cast
          if (a1) ;      // OK: A::operator bool()
          bool na1 = a1; // OK: copy-initialization selects A::operator bool()
          bool na2 = static_cast<bool>(a1); // OK: static_cast performs direct-initialization
       
      //  B b1 = 1;      // error: copy-initialization does not consider B::B(int)
          B b2(2);       // OK: direct-initialization selects B::B(int)
          B b3 {4, 5};   // OK: direct-list-initialization selects B::B(int, int)
      //  B b4 = {4, 5}; // error: copy-list-initialization does not consider B::B(int,int)
          B b5 = (B)1;   // OK: explicit cast performs static_cast
          if (b2) ;      // OK: B::operator bool()
      //  bool nb1 = b2; // error: copy-initialization does not consider B::operator bool()
          bool nb2 = static_cast<bool>(b2); // OK: static_cast performs direct-initialization
      }     