Predefined Macros
=================

``__FUNCTION__`` is non standard, ``__func__`` exists in C99 / C++11.
The others (``__LINE__`` and ``__FILE__``) are just fine.

It will always report the right file and line (and function if you choose to
use ``__FUNCTION__``/``__func__``). Optimization is a non-factor since it is
a compile time macro expansion; it will never effect performance in any way.

.. code-block:: c++
   :caption: Codes taken from Jansson

   #define failhdr fprintf(stderr, "%s:%d: ", __FILE__, __LINE__)


``inline`` keyword
==================

In the C and C++ programming languages, an inline function is one qualified with the keyword ``inline``; this serves two purposes.

   * Firstly, it serves as a compiler directive that suggests (but does not require) that the compiler substitute
     the body of the function inline by performing inline expansion, i.e. by inserting the function code at
     the address of each function call, thereby saving the overhead of a function call.
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


