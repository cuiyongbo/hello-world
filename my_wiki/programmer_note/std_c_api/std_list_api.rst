*********
std::list
*********

**Introduction**

std::list is a container that supports constant time insertion and removal of elements from anywhere in the container. 
Fast random access is not supported. It is usually implemented as a **doubly-linked list.** Compared to std::forward_list 
this container provides bidirectional iteration capability while being less space efficient.

Adding, removing and moving the elements within the list or across several lists does not invalidate the iterators 
or references. An iterator is invalidated only when the corresponding element is deleted.

MSVC implementation contains a dummy node as the head node.

#. reverse
   
   Reverses the order of the elements in the container. No references or iterators become invalidated.
   
   **Complexity:** Linear in the size of the container.

   .. code-block:: cpp
      :caption: MSVC implementation

      void reverse() _NOEXCEPT
      {  // reverse sequence
         const _Nodeptr _Phead = this->_Myhead;
         _Nodeptr _Pnode = _Phead;
   
         for (; ; )
         {  // flip pointers in a node
            const _Nodeptr _Pnext = this->_Nextnode(_Pnode);
            this->_Nextnode(_Pnode) = this->_Prevnode(_Pnode);
            this->_Prevnode(_Pnode) = _Pnext;
   
            if (_Pnext == _Phead)
               break;
            _Pnode = _Pnext;
         }
      }

#. unique
   
   .. code-block:: cpp

      void unique();
      
      template< class BinaryPredicate >
      void unique( BinaryPredicate p );

   Removes all consecutive duplicate elements from the container. 
   Only the first element in each group of equal elements is left. 
   The first version uses ``operator==`` to compare the elements, 
   the second version uses the given binary predicate ``p.``

   Binary predicate returns ​true if the elements should be treated as equal. 
   The signature of the predicate function should be equivalent to the following::

      bool pred(const Type1 &a, const Type2 &b);

   The signature does not need to have ``const &,`` but the function must not modify the objects passed to it.

   **Complexity:** Linear in the size of the container.

   .. code-block:: cpp
      :caption: MSVC implementation

      void unique()
      {  // erase each element matching previous
         unique(equal_to<>());
      }

      template<class _Pr2>
      void unique(_Pr2 _Pred)
      {  // erase each element satisfying _Pred with previous
         const _Nodeptr _Phead = this->_Myhead;
         _Nodeptr _Pprev = this->_Nextnode(_Phead);
         _Nodeptr _Pnode = this->_Nextnode(_Pprev);
   
         while (_Pnode != _Phead)
         {
            if (_Pred(_Pprev->_Myval, _Pnode->_Myval))
            {  // match, remove it
               const _Nodeptr _Perase = _Pnode;
               _Pnode = this->_Nextnode(_Pnode);
   
               this->_Nextnode(_Pprev) = _Pnode;
               this->_Prevnode(_Pnode) = _Pprev;
               this->_Freenode(_Perase);
   
               --this->_Mysize;
            }
            else
            {  // no match, advance
               _Pprev = _Pnode;
               _Pnode = this->_Nextnode(_Pnode);
            }
         }
      }

#. sort
   
   .. code-block:: cpp

      void sort();
   
      template< class Compare > 
      void sort( Compare comp );

   Sorts the elements in ascending order. The order of equal elements is preserved. 
   The first version uses ``operator<`` to compare the elements, the second version 
   uses the given comparison function ``comp.``

   If an exception is thrown, the order of elements in ``*this`` is unspecified.

   **Complexity:** Approximately **N log N** comparisons, where N is the number of elements in the list.

   ``std::sort`` requires random access iterators and so cannot be used with list. 
   This function also differs from ``std::sort`` in that it does not require the element 
   type of the list to be swappable, preserves the values of all iterators, and performs 
   a **stable** sort.

   The MSVC implementation is merge sort.

#. merge
   
   .. code-block:: cpp
      :caption: MSVC implementation

      void merge(_Myt& _Right)
      {  // merge in elements from _Right, both ordered by operator<
         merge(_Right, less<>());
      }

      template<class _Pr2>
      void merge(_Myt& _Right, _Pr2 _Pred)
      {  // merge in elements from _Right, both ordered by _Pred
         if (&_Right != this)
         {  // safe to merge, do it
            iterator _First1 = begin(), _Last1 = end();
            iterator _First2 = _Right.begin(), _Last2 = _Right.end();
            _DEBUG_ORDER_PRED(_First1, _Last1, _Pred);
            _DEBUG_ORDER_PRED(_First2, _Last2, _Pred);
   
            while (_First1 != _Last1 && _First2 != _Last2)
            {            
               if (_DEBUG_LT_PRED(_Pred, *_First2, *_First1))
               {  // splice in an element from _Right
                  iterator _Mid2 = _First2;
                  _Splice(_First1, _Right, _First2, ++_Mid2, 1);
                  _First2 = _Mid2;
               }
               else
                  ++_First1;
            }

            if (_First2 != _Last2) 
               _Splice(_Last1, _Right, _First2, _Last2, _Right._Mysize);  // splice remainder of _Right
         }
      }

   Merges two sorted lists into one. The lists should be sorted into ascending order.

   No elements are copied. The container other becomes empty after the operation. 
   The function does nothing if other refers to the same object as ``*this.`` 
   If ``get_allocator() != other.get_allocator(),`` the behavior is undefined. 
   No iterators or references become invalidated, except that the iterators of 
   moved elements now refer into ``*this,`` not into ``other.`` The first version 
   uses ``operator<`` to compare the elements, the second version uses the given 
   comparison function ``comp.``

   This operation is stable: for equivalent elements in the two lists, the elements 
   from ``*this`` shall always precede the elements from other, and the order of 
   equivalent elements of ``*this`` and other does not change.

**Example**

   .. code-block:: cpp

      #include <iostream>
      #include <list>
       
      std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
      {
          for (auto &i : list)
              ostr << " " << i;
          return ostr;
      }
       
      int main()
      {
          std::list<int> list = { 8,7,5,9,0,1,3,2,6,4,2,3 };
       
          std::cout << "before:     " << list << "\n";
          list.sort();
          std::cout << "ascending:  " << list << "\n";
          list.reverse();
          std::cout << "descending: " << list << "\n";
          list.unique();
          std::cout << "removing dupicates: " << list << "\n";
      }

   OutPut::

      before:      8 7 5 9 0 1 3 2 6 4 2 3
      ascending:   0 1 2 2 3 3 4 5 6 7 8 9
      descending:  9 8 7 6 5 4 3 3 2 2 1 0
      removing dupicates:  9 8 7 6 5 4 3 2 1 0