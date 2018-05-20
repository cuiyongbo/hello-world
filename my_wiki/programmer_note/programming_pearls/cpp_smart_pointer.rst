:orphan:

*************
Smart Pointer
*************

A smart pointer is an object encapsulating a dumb pointer
by overloading the ``->`` and ``*`` operators.

-- Scott Meyers *Effective C++*
 
.. code-block:: c++
   :caption: Example take from *Effective C++*

   template <typename T>
   class RCPtr
   {
   public:

      T* operator->() const { return m_ptr; }
      T& operator*() const { return *m_ptr; }

   private:
      T* m_ptr;
   };

