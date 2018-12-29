*******************************
Longest Common Subsequence Note
*******************************

**流水不腐，户枢不蠹。**

**Definition** 

Given a sequence :math:`X = \bigl( x_1, x_2, ..., x_m \bigr)`, another sequence 
:math:`Z = \bigl( z_1, z_2, ..., z_k \bigr)` is a **subsequence** of :math:`X`
if there exits a strictly increasing sequence :math:`\bigl( i_1, i_2, ..., i_k \bigr)` of
indices of :math:`X` such that for :math:`j = 1,2,...,k`, we have :math:`x_{i_j} = z_j`.

Given two sequences :math:`X` and :math:`Y`, we say that a sequence :math:`Z` is a
**commond subsequence** of :math:`X` and :math:`Y` if :math:`Z` is a subsequence of both
:math:`X` and :math:`Y`.

In the **longest-common-subsequence problem**, we are given two sequences 
:math:`X = \bigl( x_1, x_2, ..., x_m \bigr)` and :math:`Y = \bigl( y_1, y_2, ..., y_n \bigr)`
and wish to find a maximum-length common subsequence of :math:`X` and :math:`Y`. 


**Implementation**

.. code-block:: none

   // O(mn)
   LCS-Length(x, y)
      m = x.length
      n = y.length
      let b[1..m,1..n] and c[0..m,0..n] be new tables
      for i=1 to m
         c[i][0] = 0
      for j=0 to n
         c[0][j] = 0
      for i=1 to m
         for j=1 to n
            if x[i] == y[j]
               c[i][j] = c[i-1][j-1] + 1
               b[i][j] = LEFTUP
            else if c[i-1][j] >= c[i][j-1]
               c[i][j] = c[i-1][j]
               b[i][j] = UP
            else
               c[i][j] = c[i-1][j]
               b[i][j] = LEFT
      return (c, b)
   
   // O(m+n)
   Print-LCS(b, x, i, j)
      if i==0 || j==0
         return
      if b[i][j] == LEFTUP
         Print-LCS(b, x, i-1, j-1)
         print x[i]
      else if b[i][j] == UP
         Print-LCS(b, x, i-1, j)
      else
         Print-LCS(b, x, i, j-1)