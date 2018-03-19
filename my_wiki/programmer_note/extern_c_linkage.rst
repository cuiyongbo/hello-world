What is the effect of ``extern C`` in C++?
==========================================

``extern C`` makes a function-name in C++ have C linkage (compiler does not mangle the name) 
so that client C code can link to your function using a C compatible header file that contains 
just the declaration of your function. Your function definition is contained in a binary format (that was compiled by your C++ compiler) 
that the client C linker will then link to using the C name.

Since C++ has overloading of function names and C does not, the C++ compiler cannot just use the function name as a unique id to link to, 
so it mangles the name by adding information about the arguments. A C compiler does not need to mangle the name since you can not overload function names in C. 
When you state that a function has ``extern C`` linkage in C++, the C++ compiler does not add argument/parameter type information to the name used for linkage.

Just so you know, you can specify C linkage to each individual declaration/definition explicitly 
or use a block to group a sequence of declarations/definitions to have a certain linkage:

.. code-block:: c

   extern "C" void foo(int);
   extern "C"
   {
      void g(char);
      int i;
   }

If you care about the technicalities, they are listed in section 7.5 of the C++03 standard, 
here is a brief summary (with emphasis on extern C):

   * extern C is a linkage-specification
   * Every compiler is required to provide C linkage
   * a linkage specification shall occur only in namespace scope
   * Only function names and variable names with external linkage have a language linkage
   * two function types with distinct language linkages are distinct types even if otherwise identical
   * linkage specs nest, inner one determines the final linkage
   * ``extern C`` is ignored for class members
   * at most one function with a particular name can have C linkage (regardless of namespace)
   * ``extern C`` forces a function to have external linkage (cannot make it static)