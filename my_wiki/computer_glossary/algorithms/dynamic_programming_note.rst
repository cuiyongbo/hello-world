*******************
Dynamic Programming
*******************

**Rod-cutting problem**
   
.. code-block:: none

   // Naive method, take O(2^n)
   Cut-Rod(p, n)
      if n == 0
         return 0
      q = -inf
      for i = 1 to n
         q = max(q, p[i] + Cut-Rod(p, n-i))
      return q
   
   // Top-down implementation, take O(n^2)
   Top-Down-Cut-Rod(p, n)
      let r[0, n] be a new array
      for i=0 to n
         r[i] = -inf
      return Top-Down-Cut-Rod-Aux(p, n, r)
   
   Top-Down-Cut-Rod-Aux(p, n, r)
      if r[n] >= 0
         return r[n]
      if n == 0
         q = 0
      else
         q = -inf
         for i=1 to n
            q = max(q, p[i] + Top-Down-Cut-Rod-Aux(p, n-i, r))
      r[n] = q
      return q
   
   // Bottom-up implementation, take O(n^2)
   Bottom-Up-Cut-Rod(p, n)
      let r[0, n] be a new array
      r[0] = 0
      for j=1 to n
         q = -inf
         for i=1 to j
            q = max(q, p[i]+r[j-i])
         r[j] = q
      return r[n]

   Extended-Bottom-Up-Cut-Rod(p, n)
      let r[0, n] , s[0, n] be a new array
      r[0] = 0
      for j=1 to n
         q = -inf
         for i=1 to j
            if q < p[i] + r[j-i]
               q = p[i] + r[j-1]
               s[j] = i
         r[j] = q
      return r, s

   Print-Bottom-Up-Cut-Rod-Solution(p, n)
      r, s = Extended-Bottom-Up-Cut-Rod(p, n)
      while n > 0
         print s[n]
         n = n - s[n]


**Matrix-chain multiplication problem**

.. code-block:: none

   Matrix-Multiply(A, B)
      if A.columns != B.rows
         error "incompatible dimensions"
      else 
         let C be a new A.rows X B.columns matrix
         for i=1 to A.rows
            for j=1 to B.columns
               c[i][j] = 0
               for k=1 to A.columns
                  c[i][j] = c[i][j] + a[i][k] * b[k][j]
         return C

   Recursive-Matrix-Chain(p, i, j)
      if i==j
         return 0
      m[i][j] = -inf
      for k=i to j-1
         q = Recursive-Matrix-Chain(p, i, k)
            + Recursive-Matrix-Chain(p, k+1, j)
            + p[i-1] * p[k] * p[j]
         if q < m[i][j]
            m[i][j] = q
      return m[i][j]
      
   Memorized-Matrix-Chain(p)
      n = p.length - 1
      let m[n*n] be a new table
      for i=1 to n
         for j=1 to n
            m[i][j] = inf
      return lookUp-Chain(m, p, 1, n)

   lookUp-Chain(m, p, i, j)
      if m[i][j] < inf
         return m[i][j]
      if i == j
         m[i][j] = 0
      else
         for k=i to j-1
            q = lookUp-Chain(m, p, i, k)
               + lookUp-Chain(m, p, k+1, j) + p[i-1]*p[k]*p[j]
            if q < m[i][j]
               m[i][j] = q
      return m[i][j]


**Longest common subsequence problem**

