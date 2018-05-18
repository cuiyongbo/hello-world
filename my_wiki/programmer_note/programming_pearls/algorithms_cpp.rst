:orphan:

*************************
Frquently Used Algorithms
*************************

Reverse algorithm
=================

.. code-block:: c++
   :caption: std::reverse 

   template<class BidirIt>
   void reverse(BidirIt first, BidirIt last)
   {
      for(; first != last && first != --last; ++first)
         std::iter_swap(first, last);
   }


Rotate algorithm
================

#. Possible implementation 1
   
   .. code-block:: c++
      :caption: std::rotate
   
      template<class _BidIt> inline
      void _Rotate(_BidIt _First, _BidIt _Mid, _BidIt _Last)
      {  // rotate [_First, _Last), _Mid as the pivot
         reverse(_First, _Mid);
         reverse(_Mid, _Last);
         reverse(_First, _Last);
      }
   
   .. note::
   
      reverse can be seen as an instance of rotate where the pivot is the midpoint.

#. Possible implementation 2
   
   .. code-block:: c++
      :caption: std::rotate
   
      template <class ForwardIt>
      void rotate(ForwardIt first, ForwardIt mid, ForwardIt last)
      {
         ForwardIt next = mid;
         while (first != next) {
            std::iter_swap(first++, next++);
            if (next == last) {
                next = mid;
            } else if (first == mid) {
                mid = next;
            }
         }
      }


Unique algorithm
================

#. Possible implementation 1

   .. code-block:: c++
      :caption: std::unique
   
      template<class ForwardIt>
      ForwardIt unique(ForwardIt first, ForwardIt last)
      {
         if (first == last)
            return last;
      
         ForwardIt result = first;
         while (++first != last) {
            if (!(*result == *first) && ++result != first) {
              *result = std::move(*first);
            }
         }
         return ++result;
      }

#. Possible implementation 2

   .. code-block:: c++
      :caption: std::unique
   
      template<class ForwardIt, class BinaryPredicate>
      ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
      {
         if (first == last)
            return last;
       
         ForwardIt result = first;
         while (++first != last) {
            if (!p(*result, *first) && ++result != first) {
                *result = std::move(*first);
            }
         }
         return ++result;
      }
   
#. Possible implementation 3

   .. code-block:: c++
      :caption: std::unique
   
      template<class _FwdIt, class _Pr> inline
         _FwdIt _Unique(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
      {  // remove each satisfying _Pred with previous
         if (_First != _Last)
         {
            for (_FwdIt _Firstb; (_Firstb = _First), ++_First != _Last; )
            {
               if (_Pred(*_Firstb, *_First))
               {  // copy down
                  for (; ++_First != _Last; )
                  {
                     if (!_Pred(*_Firstb, *_First))
                        *++_Firstb = _Move(*_First);
                  }
                  return (++_Firstb);
               }
            }
         }
         return (_Last);
      }
