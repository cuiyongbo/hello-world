**************
Priority Queue
**************

Implement a max-priority queue with max-heap.

.. code-block:: none

   Heap-Maximum(A)
      return A[1]

   Heap-Extract-Max(A)
      if A.heap_size < 1
         error "heap underflow"
      max = A[1]
      A[1] = A[A.heap_size]
      A.heap_size = A.heap_size - 1
      Max-Heapify-siftDown(A, 1)
      return max

   Heap-Increase-to-Key(A, i, key)
      if key < A[i]
         error "new key is smaller than current key"
      A[i] = key
      # A[1, i-1] is alread a heap
      # A[i, length] is also a heap
      while i > 1 and A[Parent(i)] < A[i]
         swap(A[i], A[Parent(i)])
         i = Parent(i)

   Max-Heap-Insert(A, key)
      A.heap_size = A.heap_size + 1
      A[A.heap_size] = -inf
      Heap-Increase-to-Key(A, A.heap_size, key)
