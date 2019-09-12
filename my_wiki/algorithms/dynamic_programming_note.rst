*******************
Dynamic Programming
*******************

**Applying dynamic programming**

   #. Characterize the structure of an optimal solution
   #. Recursively define the value of an optimal solution
   #. Compute the value of an optimal solution
   #. Construct an optimal solution from computed information

#. Rod-cutting problem

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


#. Matrix-chain multiplication problem

   Given a chain :math:`\bigl( A_1, A_2,\ldots, A_n \bigr)` of n matrices, where
   for :math:`i=1,2,\ldots, n`, matrix :math:`A_i` has dimension :math:`p_{i-1} \times p_i`,
   fully parenthize the product :math:`A_1A_2 \cdots A_n` in a way that minimizes the number of
   scalar multiplications.

   A product of matrices is **fully parenthesized** if it is either a single matrix
   or a product of two fully parenthesized matrix products, surrounded by parentheses.

   .. code-block:: none

      // O(n^3)
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

      Matrix-Chain-Order(p)
         n = p.length - 1
         let m[1..n, 1..n] and s[1..n-1, 2..n] be new tables
         for i = 1 to n
            m[i][i] = 0
         for l=2 to n
            for i=1 to n-l+1
               j=i+l-1
               m[i][j] = inf
               for k = i to j-1
                  q = m[i][k] + m[k+1][j] + p[k-1]p[k]p[j]
                  if q < m[i][j]
                     m[i][j] = q
                     s[i][j] = k
         return (m, s)

      Print-Optimal-Parens(s, i, j)
         if i==j
            print "Ai"
         else
            print "("
            Print-Optimal-Parens(s, i, s[i][j])
            Print-Optimal-Parens(s, s[i][j]+1, j)
            print ")"

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
