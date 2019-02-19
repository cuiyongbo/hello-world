*************************
Frquently Used Algorithms
*************************

Unique algorithm
================

#. std\:\:list\:\:unique
   
   .. code-block:: cpp
      
      template <typename ValueType>
      struct ListNode
      {
         struct ListNode* next;       // successor node, or first element if head
         struct ListNode* prev;       // predecessor node, or last element if head
         ValueType val;               // the stored value, unused if head
      private:
         ListNode& operator=(const ListNode&);
      };

      typedef struct ListNode* NodePtr;

      template<typename ValueType>
      template<typename Pred2>
      void List<ValueType>::unique(Pred2 _Pred)
      {
         const NodePtr pHead = this->m_head;
         NodePtr pPrev = pHead->next;
         NodePtr pNode = pPrev->next;
         while(pNode != pHead)
         {
            if(_Pred(pPrev->val, pNode->val))
            {
               const NodePtr pErase = pNode;
               
               pNode = pNode->next;
               pPrev->next = pNode;
               pNode->prev = pPrev;

               freeNode(pErase);
               --this->m_size;
            }
            else
            {
               pPrev = pNode;
               pNode = pNode->next;
            }
         }
      }
