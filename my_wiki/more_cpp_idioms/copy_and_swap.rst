*************
Copy and Swap
*************

Create a temporary and swap idiom acquires new resource before it forfeits its current resource. 
To acquire the new resource, it uses RAII idiom. If the acquisition of the new resource is successful, 
it exchanges the resources using the non-throwing swap idiom. Finally, the old resource is released 
as a side effect of using RAII in the first step.

**Solution and Sample Code**

.. code-block:: cpp

   class String
   {
       char * str; 
   public:
       String & operator=(const String & s)
       {
           String temp(s); // Copy-constructor -- RAII
           temp.swap(*this); // Non-throwing swap
           
           return *this;
       } // Old resources released when destructor of temp is called.
       void swap(String & s) throw() // Also see the non-throwing swap idiom
       {
           std::swap(this->str, s.str);
       }
   };

Some variations of the above implementation are also possible. 
A check for self assignment is not strictly necessary but can 
give some performance improvements in (rarely occurring) self-assignment cases.

.. code-block:: cpp

   class String
   {
       char * str;
   public:
       String & operator=(const String & s)
       {
           if (this != &s)
           {
               String(s).swap(*this); //Copy-constructor and non-throwing swap
           }
         
           // Old resources are released with the destruction of the temporary above
           return *this;
       }
       void swap(String & s) throw() // Also see non-throwing swap idiom
       {
           std::swap(this->str, s.str);
       }
   };

**copy elision and copy-and-swap idiom**

Strictly speaking, explicit creation of a temporary inside the assignment operator is not necessary. 
The parameter (right hand side) of the assignment operator can be passed-by-value to the function. 
The parameter itself serves as a temporary.

.. code-block:: cpp

   String & operator = (String s) // the pass-by-value parameter serves as a temporary
   {
      s.swap (*this); // Non-throwing swap
      return *this;
   }// Old resources released when destructor of s is called.

This is not just a matter of convenience but in fact an optimization. 
If the parameter (s) binds to an lvalue (another non-const object), 
a copy of the object is made automatically while creating the parameter (s). 
However, when s binds to an rvalue (temporary object, literal), the copy is typically elided, 
which saves a call to a copy constructor and a destructor. In the earlier version of the assignment 
operator where the parameter is accepted as const reference, copy elision does not happen when the 
reference binds to an rvalue. This results in an additional object being created and destroyed.

In C++11, such an assignment operator is known as a unifying assignment operator because it eliminates 
the need to write two different assignment operators: copy-assignment and move-assignment. As long as 
a class has a move-constructor, a C++11 compiler will always use it to optimize creation of a copy 
from another temporary (rvalue)::

   String createString(); // a function that returns a String object.
   String s;
   s = createString(); 
   // right hand side is a rvalue. Pass-by-value style assignment operator 
   // could be more efficient than pass-by-const-reference style assignment 
   // operator.

Not every class benefits from this style of assignment operator. Consider a String assignment operator, 
which releases old memory and allocates new memory only if the existing memory is insufficient to hold 
a copy of the right hand side String object. To implement this optimization, one would have to write a 
custom assignment operator. Since a new String copy would nullify the memory allocation optimization, 
this custom assignment operator would have to avoid copying its argument to any temporary Strings, 
and in particular would need to accept its parameter by const reference.
