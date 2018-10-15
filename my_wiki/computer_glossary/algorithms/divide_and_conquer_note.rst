*************************
Divide and Conquer Design
*************************

Case 1: Maximum subarray problem
================================

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

   Find-Max-SubArray(A, low, high)
      if high == low
         return (low, high, A[low])
      else mid = (low+high)/2
         (left-low, left-high, left-sum) = 
            Find-Max-SubArray(A, low, mid)
         (right-low, right-hight, right-sum) = 
            Find-Max-SubArray(A, mid, high)
         (cross-low, cross-high, cross-sum) = 
            Find-Max-Crossing-SubArray(A, low, mid, high)
      if left-sum >= right-sum and left-sum >= cross-sum
         return (left-low, left-high, left-sum)
      else if right-sum >= left-sum and right-sum >= cross-sum
         return (right-low, right-high, right-sum)
      else 
         return (cross-low, cross-high, cross-sum)

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
               max-i-right = i
         if max-i-sum > max-sum
            max-sum = max-i-sum
            max-left = max-i-left
            max-right = max-i-right
      return (max-left, max-right, max-sum)

   // The initial call Find-Max-SubArray(A, 1, A.length) 
   // will find a maximum subarray of A[1...n]