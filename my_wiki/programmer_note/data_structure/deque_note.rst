*****
Deque
*****

**Implementation**

.. code-block:: none

   DEQUE-EMPTY(D):
      return D.head == D.tail

   DEQUE-FULL(D):
      return (D.tail + 1) % D.length == D.head

   PUSH_BACK(D, x):
      if DEQUE-FULL(D):
         error "overflow"

      D[D.tail] = x
      if D.tail = D.length:
         D.tail = 1
      else D.tail = D.tail + 1

   PUSH_FRONT(D, x):
      if DEQUE-FULL(D):
         error "overflow"

      if D.head == 1:
         D.head = D.length
      else D.head = D.head - 1

      D[D.head] = x

   POP_BACK(D):
      if DEQUE-EMPTY(D):
         error "underflow"

      x = D[D.tail]
      if D.tail == 1:
         D.tail = D.length
      else D.tail = D.tail - 1
      return x

   POP_FRONT(D):
      if DEQUE-EMPTY(D):
         error "underflow"

      x = D[D.head]
      if D.head == D.length:
         D.head = 1
      else D.head = D.head + 1
      return x

Each of the six deque operations takes **O(1)** time.
