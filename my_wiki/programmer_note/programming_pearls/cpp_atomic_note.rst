***********
std::atomic
***********

If one thread writes to an atomic object while another thread reads from it, 
the behavior is well-defined (see `memory model <https://en.cppreference.com/w/cpp/language/memory_model>`_
for details on data races). In addition, accesses to atomic objects may establish inter-thread synchronization 
and order non-atomic memory accesses as specified by ``std::memory_order.``
``std::atomic`` is neither copyable nor movable.


.. code-block:: cpp
   :caption: a MSVC implementation
      
   template<class _Ty> struct atomic
         : _Atomic<_Ty, sizeof (_Ty)>
   {  // template that manages values of _Ty atomically
      typedef _Atomic<_Ty, sizeof (_Ty)> _My_base;
   
      atomic() _NOEXCEPT
      {  // default constructor
      }
   
      // Disallow copying
      atomic(const atomic&) = delete; 
      atomic& operator=(const atomic&) = delete;
      atomic& operator=(const atomic&) volatile = delete;
   
      atomic(_Ty _Val) _NOEXCEPT
         : _My_base(_Val)
      {  // construct from _Val
      }
   
      _Ty operator=(_Ty _Right) volatile _NOEXCEPT
      {  // assign from _Right
         return _My_base::operator=(_Right);
      }
   
      _Ty operator=(_Ty _Right) _NOEXCEPT
      {  // assign from _Right
         return _My_base::operator=(_Right);
      }
   };

.. code-block:: cpp

   class NonAssignable {
   public:
      // disallow copying or assignmentf
      NonAssignable(NonAssignable const&) = delete; // 
      NonAssignable& operator=(NonAssignable const&) = delete;
      NonAssignable() {}
   };

   NonAssignable n1;
   NonAssignable n2 = n1; 'NonAssignable::NonAssignable(const NonAssignable &)' : attempting to reference a deleted function