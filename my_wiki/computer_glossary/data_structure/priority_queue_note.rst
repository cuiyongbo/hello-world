**************
Priority Queue
**************

#. Implement a max-priority queue with max-heap.

   .. code-block:: none
   
      Max-Heapify-siftDown(A, i)
         largest = i
         l = Left(i)
         r = Right(i)
         if l < A.length and A[l] < A[largest]
            largest = l
         if r < A.length and A[r] < A[largest]
            largest = r

         if largest == i
            break

         swap(A[i], A[largest])
         Max-Heapify(A, largest)

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

      Heap-Increase-to-Key_2(A, i, key)
         if key < A[i]
            error "new key is smaller than current key"
         # A[i, A.heap_size] maintains the heap property
         while i > 1 and A[Parent(i)] < key
            A[i] = A[Parent(i)]
            i = Parent(i)
         A[i] = key

      Max-Heap-Insert(A, key)
         A.heap_size = A.heap_size + 1
         A[A.heap_size] = -inf
         Heap-Increase-to-Key(A, A.heap_size, key)

      Heap-Delete_2(A, i)
         A.heap_size = i-1
         for j=i+1 to A.length
            Max-Heap-Insert(A, A[j])

      Heap-Delete(A, i)
         if A[i] < A[A.heap_size]
            Heap-Increase-to-Key(A, i, A[A.heap_size])
            A.heap_size = A.heap_size - 1
         else
            A[i] = A[A.heap_size]
            A.heap_size = A.heap_size - 1
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

#. python max priority queue toy
   
   .. code-block:: py

      #!/usr/bin/env python
      import sys, random

      def parent(i):
         return (i-1)/2
      
      def left(i):
         return i*2+1
      
      def right(i):
         return i*2+2
      
      def max_heapify_siftdown(array, i):
         assert i<len(array), "index out of range"
         while i < len(array):
            largest = i
            l = left(i)
            r = right(i)
            if l<len(array) and array[l] > array[largest]:
               largest = l
            if r<len(array) and array[r] > array[largest]:
               largest = r
            if largest == i:
               break
            else:
               array[largest], array[i] = array[i], array[largest]
               i = largest
      
      def maximum(array):
         return array[0]
      
      def extract_maximum(array):
         assert len(array) > 0, "underflow"
         max = array[0]
         array[0] = array[-1]
         array.pop() # decrease heap size by one
         if len(array) > 1:
            max_heapify_siftdown(array, 0)
         return max
      
      def increase_to_key(array, i, key):
         assert i<len(array), "index out of range"
         assert array[i]<key, "new key must be larger than current key"
         while i>0 and array[parent(i)] < key:
            array[i] = array[parent(i)]
            i = parent(i)
         array[i] = key
      
      def insert_new_key(array, key):
         array.append(-sys.maxint)
         increase_to_key(array, len(array)-1, key)
      
      def heap_delete(array, i):
         assert i<len(array), "index out of range"
         tmp = array[:i]
         for x in array[i+1:]:
            insert_new_key(tmp, x)
         return tmp
      
      a = random.sample(range(1, 1000), 10)
      array = []
      for i in a:
         insert_new_key(array, i)
      print array
      
      array = heap_delete(array, random.choice(range(10)))
      print array
      
      while len(array)>0:
         print extract_maximum(array)