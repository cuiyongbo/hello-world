:orphan:

******************
C/C++ Macro Tricks
******************

Predefined Macros
=================

``__FUNCTION__`` is non standard, ``__func__`` exists in C99 / C++11.
The others (``__LINE__`` and ``__FILE__``) are just fine. they will always
report the right file and line. And function if you choose to use ``__FUNCTION__``/``__func__``,
optimization is a non-factor since it is a compile time macro expansion;
it will never effect performance in any way.

.. code-block:: c++
   :caption: Codes taken from Jansson

   #define failhdr fprintf(stderr, "%s:%d: ", __FILE__, __LINE__)


Variadic Macro
==============

**Remarks**

   Variadic macros are function-like macros that contain a variable number of arguments.
   
   To use variadic macros, the ellipsis ``'...'`` may be specified as the final formal argument
   in a macro definition, and the replacement identifier ``__VA_ARGS__`` may be used in the
   definition to insert the extra arguments. ``__VA_ARGS__`` is replaced by all of the arguments
   that match the ellipsis, including commas between them.
   
   The C Standard specifies that at least one argument must be passed to the ellipsis, to ensure
   that the macro does not resolve to an expression with a trailing comma. The Visual C++ implementation
   will suppress a trailing comma if no arguments are passed to the ellipsis.


**Examples**

   .. code-block:: c++
      :caption: Example taken from MSDN

      #include <stdio.h>  
      #define EMPTY  
        
      #define CHECK1(x, ...) if (!(x)) { printf(__VA_ARGS__); }  
      #define CHECK2(x, ...) if ((x)) { printf(__VA_ARGS__); }  
      #define CHECK3(...) { printf(__VA_ARGS__); }  
      #define MACRO(format, ...) printf(format, __VA_ARGS__)  
        
      int main() {  
         CHECK1(0, "here %s %s %s", "are", "some", "varargs1(1)\n");  
         CHECK1(1, "here %s %s %s", "are", "some", "varargs1(2)\n");   // won't print  
        
         CHECK2(0, "here %s %s %s", "are", "some", "varargs2(3)\n");   // won't print  
         CHECK2(1, "here %s %s %s", "are", "some", "varargs2(4)\n");  
        
         // always invokes printf in the macro  
         CHECK3("here %s %s %s", "are", "some", "varargs3(5)\n");  
        
         MACRO("hello, world\n");  
         MACRO("error\n", EMPTY); // would cause error C2059, except VC++   
                                  // suppresses the trailing comma  
      }        


   .. code-block:: c++
      :caption: More Examples

      #define eprintf(format, …) fprintf (stderr, format, __VA_ARGS__)

      #define MyLoger(format, ...) fprintf(stderr, "%s(%u): " format "\n", __FILE__, __LINE__, __VA_ARGS__)

      #define OperationWithLock(mutex, ...)  {     \
         pthread_mutex_lock(mutex);                \
         (__VA_ARGS__);                            \
         pthread_mutex_unlock(mutex);              \
      }

