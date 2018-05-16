***********
Linked List
***********

**IMPLEMENTATION**

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



