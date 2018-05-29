*************
LRU Algorithm
*************

IMPLEMENTATION
==============
   
   * double linked list
      - LIST-ADD
      - LIST-DELETE
      
   * hash map
      - SERARCH   

   * element
     - key
     - m_prev, m_next
       

STRUCTURE
=========

.. code-block:: c++

   template <typename T>
   struct CacheUnit
   {
      T key;
      CacheUnit* m_prev;
      CacheUnit* m_next;
   };

   class LRUList
   {

   private:
      HashMap m_keyMap;
      CacheUnit* m_head;
      CacheUnit* m_tail;
   };


METHOD
======

.. code-block:: c++

   void _listAppend(CacheUnit* node)
   {
      if(m_head == NULL)
      {
         m_head = m_tail = node;
      }
      else
      {
         node->prev = m_tail;
         m_tail->next = node;
         m_tail = node;
      }
   }

   void _listDelete(CacheUnit* node)
   {
      if(m_head == node)
      {
         m_head = m_head->next;
      }
      else if(m_tail == node)
      {
         m_tail = m_tail->prev;
      }
      else
      {
         node->next->prev = node->prev;
         node->prev->next = node->next;
         node->prev = node->next = NULL;
      }
   }

