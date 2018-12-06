*************
Copy-on-write
*************

**Intent**

Achieve lazy copy optimization. Like lazy initialization, do the work just 
when you need because of efficiency.

**Motivation**

Copying an object can sometimes cause a performance penalty. 
If objects are frequently copied but infrequently modified later, 
copy-on-write can provide significant optimization. To implement copy-on-write, 
a smart pointer to the real content is used to encapsulate the object's value, 
and on each modification an object reference count is checked; if the object is 
referenced more than once, a copy of the content is created before modification.

.. code-block:: cpp
   :caption: Solution and Sample Code

   #include <memory>
   
   template <class T>
   class CowPtr
   {
       public:
           typedef std::shared_ptr<T> RefPtr;
   
       private:
           RefPtr m_sp;
   
           void detach()
           {
               T* tmp = m_sp.get();
               if( !( tmp == 0 || m_sp.unique() ) ) {
                   m_sp = RefPtr( new T( *tmp ) );
               }
           }
   
       public:
           CowPtr(T* t)
               :   m_sp(t)
           {}
           CowPtr(const RefPtr& refptr)
               :   m_sp(refptr)
           {}
           const T& operator*() const
           {
               return *m_sp;
           }
           T& operator*()
           {
               detach();
               return *m_sp;
           }
           const T* operator->() const
           {
               return m_sp.operator->();
           }
           T* operator->()
           {
               detach();
               return m_sp.operator->();
           }
   };
   

This implementation of copy-on-write is generic, but apart from the inconvenience 
of having to refer to the inner object through smart pointer dereferencing, 
it suffers from at least one drawback: classes that return references to their 
internal state, like ``char & String::operator[](int)`` can lead to unexpected behaviour.

Consider the following code snippet::

   CowPtr<String> s1 = "Hello";
   char &c = s1->operator[](4); // Non-const detachment does nothing here
   CowPtr<String> s2(s1); // Lazy-copy, shared state
   c = '!'; // Uh-oh

The intention of the last line is to modify the original string s1, not the copy, 
but as a side effect s2 is also accidentally modified.

A better approach is to write a custom copy-on-write implementation which is encapsulated 
in the class we want to lazy-copy, transparently to the user. In order to fix the problem above, 
one can flag objects that have given away references to inner state as "unshareable"—in other words, 
force copy operations to deep-copy the object. As an optimisation, one can revert the object to shareable 
after any non-const operations that do not give away references to inner state 
(for example, ``void string::clear()``), because client code expects such references to be invalidated anyway.

**Known Uses**

* Active Template Library
* Many Qt classes (implicit sharing)