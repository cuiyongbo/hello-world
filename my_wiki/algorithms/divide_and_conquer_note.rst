*************************
Divide and Conquer Design
*************************

**Maximum subarray problem**

.. code-block:: none
   :caption: Implementation

   Find-Max-Crossing-SubArray(A, low, mid, high)
      left-sum = -inf
      sum = 0
      for i = mid downto low
         sum += A[i]
         if sum > left-sum
            left-sum = sum
            max-left = i
      sum = 0
      right-sum = -inf
      for j = mid+1 to high
         sum += A[j]
         if sum > right-sum
            right-sum = sum
            max-right = j
      return (max-left, max-right, left-sum + right-sum)

   // O(n log n)
   Find-Max-SubArray(A, low, high)
      if high == low
         return (low, high, A[low])
      else mid = (low+high)/2
         (left-low, left-high, left-sum) = 
            Find-Max-SubArray(A, low, mid)
         (right-low, right-hight, right-sum) = 
            Find-Max-SubArray(A, mid+1, high)
         (cross-low, cross-high, cross-sum) = 
            Find-Max-Crossing-SubArray(A, low, mid, high)
      if left-sum >= right-sum and left-sum >= cross-sum
         return (left-low, left-high, left-sum)
      else if right-sum >= left-sum and right-sum >= cross-sum
         return (right-low, right-high, right-sum)
      else 
         return (cross-low, cross-high, cross-sum)

   // O(n^2)
   Brute-Find-Max-SubArray(A, low, high)
      max-sum = -inf
      for i=low to high
         sum = 0
         max-i-left = i
         max-i-sum = -inf
         for j=i to high
            sum += A[j]
            if sum > max-i-sum
               max-i-sum = sum
               max-i-right = j
         if max-i-sum > max-sum
            max-sum = max-i-sum
            max-left = max-i-left
            max-right = max-i-right
      return (max-left, max-right, max-sum)

   // The initial call Find-Max-SubArray(A, 1, A.length) 
   // will find a maximum subarray of A[1...n]

   // O(n)
   // Assume the sum of zero-element subarray is zero
   // and the sum of max subarray has to be nonnegative. 
   Linear-Find-Max-SubArray(A, low, high)
      max-sum = 0
      max-sofar = 0
      max-left = max-right = low
      for i=low to high
         max-sofar = max(max-sofar+A[i], 0)
         if max-sofar == 0
            max-left = i
         if max-sofar > max-sum
            max-sum = max-sofar
            max-right = i
      return (max-left, max-right, max-sum)


**Strassen's algorithm for matrix multiplication**

.. code-block:: none
   :caption: Brute version implementation

   // O(n^3)
   Square-Matrix-Multiply(A, b)
      n = A.rows
      let C be a new n x n matrix
      for i=1 to n
         for j=1 to n
            c[i][j] = 0
            for k=1 to n
               c[i][j] += a[i][k] * b[k][j]
      return C

Suppose n is an exact power of 2, then partition 
each of A, B, and C into four n/2 x n/2 matrices:

.. math::

   A = \begin{pmatrix}
         A_{11} & A_{12} \\
         A_{21} & A_{22} \\
       \end{pmatrix}

   B = \begin{pmatrix}
         B_{11} & B_{12} \\
         B_{21} & B_{22} \\
       \end{pmatrix}

   C = \begin{pmatrix}
         C_{11} & C_{12} \\
         C_{21} & C_{22} \\
       \end{pmatrix}

and we can rewrite :math:`C = A \cdot B` as

.. math::

   C_{11} &= A_{11} \cdot B_{11} + A_{12} \cdot B_{21} \\
   C_{12} &= A_{11} \cdot B_{21} + A_{12} \cdot B_{22} \\
   C_{21} &= A_{21} \cdot B_{11} + A_{22} \cdot B_{12} \\
   C_{22} &= A_{21} \cdot B_{21} + A_{22} \cdot B_{22}

.. code-block:: none
   :caption: Recursion version implementation

   // still O(n^3)
   Square-matrix-Multiply-Recursive(A, B)
      n = A.rows
      let C be a new n x n matrix
      if n == 1
         c[1][1] = a[1][1] * b[1][1]
      else partition A, B, and C as above
         C[1][1] = Square-matrix-Multiply-Recursive(A[1][1], B[1][1])
                  + Square-matrix-Multiply-Recursive(A[1][2], B[2][1])
         C[1][2] = Square-matrix-Multiply-Recursive(A[1][1], B[1][2])
                  + Square-matrix-Multiply-Recursive(A[1][2], B[2][2])
         C[2][1] = Square-matrix-Multiply-Recursive(A[2][1], B[1][1])
                  + Square-matrix-Multiply-Recursive(A[2][2], B[2][1])
         C[2][2] = Square-matrix-Multiply-Recursive(A[2][1], B[1][2])
                  + Square-matrix-Multiply-Recursive(A[2][2], B[2][2])
      return C


.. code-block:: none
   :caption: Strassen's method

   // take O(n^(lg7))