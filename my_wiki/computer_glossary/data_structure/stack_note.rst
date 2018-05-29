*****
Stack
*****

**Implementation**

.. code-block:: none

   STACK-EMPTY(S):
      return S.top == 0

   PUSH(S, x):
      S.top = S.top + 1
      S[S.top] = x

   POP(S):
      if STACK-EMPTY(S):
         error "underflow"
      else
         S.top = S.top - 1
         return S[S.top + 1]

Each of the three stack operations takes **O(1)** time.

