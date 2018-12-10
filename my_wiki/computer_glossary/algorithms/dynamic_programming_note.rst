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
   Memorized-Cut-Rod(p, n)
      let r[0, n] be a new array
      for i=0 to n
         r[i] = -inf
      return Memorized-Cut-Rod-Aux(p, n, r)
   
   Memorized-Cut-Rod-Aux(p, n, r)
      if r[n] >= 0
         return r[n]
      if n == 0
         q = 0
      else
         q = -inf
         for i=1 to n
            q = max(q, p[i] + Memorized-Cut-Rod-Aux(p, n-i, r))
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


Matrix-chain multiplication problem

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
