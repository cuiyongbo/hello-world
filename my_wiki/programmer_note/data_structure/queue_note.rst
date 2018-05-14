*****
Queue
*****

**Implementation**

.. code-block:: none

   ENQUEUE(Q, x):
      Q[Q.tail] = x
      if Q.tail == Q.length:
         Q.tail = 1
      else Q.tail = Q.tail + 1

   DEQUEUE(Q):
      x = Q[Q.head]
      if Q.head == Q.length:
         Q.head = 1
      else Q.head = Q.head + 1

Each of the three stack operations takes **O(1)** time.
 
