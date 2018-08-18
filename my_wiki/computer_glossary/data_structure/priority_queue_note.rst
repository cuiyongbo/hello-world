**************
Priority Queue
**************

#. Implement a max-priority queue with max-heap.

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
         # A[i, A.heap_size] maintains the heap property
         while i > 1 and A[Parent(i)] < A[i]
            swap(A[i], A[Parent(i)])
            i = Parent(i)

      Heap-Increase-to-Key(A, i, key)
         if key < A[i]
            error "new key is smaller than current key"
         A[i] = key
         # A[i, A.heap_size] maintains the heap property
         while i > 1 and A[Parent(i)] < key
            A[i] = A[Parent(i)]
            i = Parent(i)
         A[i] = key

      Max-Heap-Insert(A, key)
         A.heap_size = A.heap_size + 1
         A[A.heap_size] = -inf
         Heap-Increase-to-Key(A, A.heap_size, key)

      Heap-Delete(A, i)
         if A[i] < A[A.heap_size]
            Heap-Increase-to-Key(A, i, A[A.heap_size])
            A.heap_size = A.heap_size - 1
         else
            A[i] = A[A.heap_size]
            A.heap_size = A.heap_size - 1]
            Max-Heapify-siftDown(A, i)

      # You can't assume there always be A[i] > A[A.heap-size]. For example:
      #          10
      #        /    \
      #       5      9
      #      / \    / \
      #     2   3  7   8
      # If you want to delete key 2, the A[A.heap-size] is 8. But 8 should climb up to the position of 5.

#. Implement a min-priority queue with min-heap
   
   .. code-block:: none

      # O(1)
      Heap-Minimum(A)
         return A[1]

      # O(log n)
      Heap-Extract-Min(A)
         if A.heap_size < 1
            error "heap overflow"
         min = A[1]
         A[1] = A[A.heap_size]
         A.heap_size = A.heap_size - 1
         Min-Heapify-siftDown(A, 1)
         return min

      Min-Heapify-siftDown(A, i)
         l = Left(i)
         smallest = i
         if l < A.heap_size and A[l] < A[i]
            smallest = l
         if l+1 < A.heap_size and A[l+1] < A[smallest]
            smallest = r
         if smallest != i
            swap(A[smallest], A[i])
            Min-Heapify-siftDown(A, smallest)

      # O(log n)
      Heap-Decrease-to-key(A, i, key)
         if key > A[i]
            error "new key is larger than current key" 
         A[i] = key
         # A[i, A.heap_size] maintains the heap property
         while i > i and A[Parent(i)] > A[i]
            swap(A[Parent(i)], A[i])
            i = Parent(i)
      
      # O(log n)
      Min-Heap-insert(A, key)
         A.heap_size = A.heap_size + 1
         A[A.heap_size] = +inf
         Heap-Decrease-to-key(A, A.heap_size, key)
