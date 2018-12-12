*****************
Non-throwing swap
*****************

A typical implementation of swap could be given as follows:

.. code-block:: cpp

   template<class T>
   void swap (T &a, T &b)
   {
     T temp (a);
     a = b;
     b = temp;
   }

This can be problematic for two reasons:

   - **Performance**: Swapping of two large, complex objects of the same type is 
     inefficient due to acquisition and release of resources for the intermediate temporary object.

   - **Exception-safety**: This generic swap implementation may throw if resources are not available. 
     (Such a behavior does not make sense where in fact no new resources should have been requested 
     in the first place.) 


Non-throwing swap idiom uses Handle Body idiom to achieve the desired effect. 
The abstraction under consideration is split between two implementation classes. 
One is handle and other one is body. The handle holds a pointer to a body object. 
The swap is implemented as a simple swap of pointers, which are guaranted to not 
throw exceptions and it is very efficient as no new resources are acquired or released.

.. code-block:: cpp

   namespace Orange {
   class String 
   {
       char * str;
     public:
       void swap (String &s) // throw ()
       {
         std::swap (this->str, s.str);
       }
   };
   }

Although an efficient and exception-safe swap function can be implemented as a member function, 
non-throwing swap idiom goes further than that for simplicity, consistency, and to facilitate 
generic programming. An explicit specialization of ``std::swap`` should be added in the std 
namespace as well as the namespace of the class itself.

.. code-block:: cpp

   namespace Orange { // namespace of String
     void swap (String & s1, String & s2) // throw ()
     {
       s1.swap (s2);
     }
   }

   namespace std {
     template <>
     void swap (Orange::String & s1, Orange::String & s2) // throw ()
     {
       s1.swap (s2);
     }
   }

Adding it in two places takes care of two different common usage styles of swap: **unqualified swap** 
and **fully qualified swap** (e.g., ``std::swap``). When unqualified swap is used, right swap is looked up 
using **Koenig lookup.** If fully qualified swap is used, Koenig lookup is suppressed and one in the std 
namespace is used instead. 

.. code-block:: cpp

   template <class T>
   void zoo (T t1, T t2) {
   //...
   int i1, i2;
   std::swap(i1,i2); // note uniformity
   std::swap(t1,t2); // Ditto here
   }

In such a case, the right, efficient implementation of swap is chosen when zoo is instantiated with String class 
defined earlier. Otherwise, the default ``std::swap`` function template would be instantiated -- completely 
defeating the purpose of defining the member swap and namespace scope swap function. This idiom of defining 
explicit specialization of swap in std namespace is particularly useful in generic programming.

.. code-block:: cpp

   class UserDefined 
   {
       String str;
     public:
       void swap (UserDefined & u) // throw () 
       { 
         std::swap (str, u.str); 
       }
   };
   namespace std
   {
     // Full specializations of the templates in std namespace can be added in std namespace.
     template <>
     void swap (UserDefined & u1, UserDefined & u2) // throw ()
     {
       u1.swap (u2);
     }
   }
   class Myclass
   {
       UserDefined u;
       char * name;
     public:
       void swap (Myclass & m) // throw ()
       {
         std::swap (u, m.u);       // cascading use of the idiom due to uniformity
         std::swap (name, m.name); // Ditto here
       }   
   }
   namespace std
   {
      // Full specializations of the templates in std namespace can be added in std namespace.
      template <> 
      void swap (Myclass & m1, Myclass & m2) // throw ()
      {
        m1.swap (m2);
      }
   };

Therefore, it is a good idea to define a specialization of ``std::swap`` for the types that are amenable 
to an exception safe, efficient swap implementation. The C++ standard does not currently allow us to add 
new templates to the std namespace, but it does allow us to specialize templates from that namespace 
and add them back in it.