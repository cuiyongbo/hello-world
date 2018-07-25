***********
Linked List
***********

**IMPLEMENTATION: Doubly linked list**

.. code-block:: none

   LIST-SEARCH(L, k):
      x = L.head
      while x != NIL and x.key != k
         x = x.next
      return x

   LIST-PUSHFRONT(L, x):
      x.next = L.head
      if L.head != NIL:
         L.head.prev = x
      L.head = x
      x.prev = NIL

   LIST-PUSHBACK(L, x):
      if L.tail == NIL:
         L.head = L.tail = x
      else
         x.prev = tail
         tail.next = x
         tail = x

   LIST-DELETE(L, x):
      if x == L.head:
         L.head = x.next
      if x == L.tail:
         L.tail = x.prev

      if x.prev != NIL:
         x.prev.next = x.next
      if x.next != NIL:
         x.next.prev = x.prev

      x.next = x.prev = NIL

To seach a list of n elements, It will take **O(n)** time in the worst case.
The running time for LIST-PUSHFRONT and LIST-PUSHBACK on a list of n elements is **O(1)**.


**IMPLEMENTATION: Circular, doubly linked list with a sentinel**

.. code-block:: none

   LIST-SEARCH'(L, k):
      x = L.nil.next
      while x != L.nil && x.key != k
         x = x.next
      return x

   LIST-DELETE'(L, x)
      x.next.prev = x.prev
      x.prev.next = x.next

   LIST-PUSHFRONT'(L, x):
      x.next = L.nil.next
      L.nil.next.prev = x
      x.prev = L.nil
      L.nil.next = x

The gain from using sentinels within loops is usually a matter of clarity of code rather than speed.


**EXERCISES**

#. Give a :math:`\Theta(n)` time nonrecursive procedure that reverses a singly linked list of n elements.
   The procedure should use no more than constant storage beyond that needed for the list itself.

.. code-block:: cpp
   :caption: Possible Solution

   namespace solution
   {
      struct Node
      {
         int data;
         Node* next;
         Node(): data(0), next(NULL) {}
      };

      typedef Node* LinkList;

      Node* reversedLink(LinkList l)
      {
         Node* tmp = NULL;
         Node* newHead = NULL;
         while (l != NULL)
         {
            tmp = l->next;
            l->next = newHead;
            newHead = l;
            l = tmp;
         }
         return newHead;
      }
   }
