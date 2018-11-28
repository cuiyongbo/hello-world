*************************
Agumenting Data Structure
*************************

.. code-block:: none
   :caption: Taken from *Introduction to Algorithms*

   // OS stands for order-statistic tree
   // Retrieving an element with a given rank
   OS-Select(x, i)
      r = x.left.size+1
      if i==r
         return x
      else if i<r
         return OS-Select(x.left, i)
      else
         return OS-Select(x.right, i-r)

   // Determining the rank of an element
   OS-Rank(T, x)
      r = x.left.size+1
      y=x
      while y != T.root
         if y == y.p.right
            r = r + y.p.left.size + 1
         y = y.p
      return r

   OS-Left-Rotate(T, x)
      y = x.right
      x.right = y.left
      if y.left != T.NIL
         y.left.p = x
      y.p = x.p
      if x.p == T.NIL
         T.root = y
      else if x == x.p.left
         x.p.left = y
      else 
         x.p.right = y
      y.left = x
      x.p = y
      y.size = x.size
      x.size = x.left.size + x.right.size + 1

   OS-Right-Rotate(T, x)
      y = x.left
      y.left = x.right
      if x.right != T.NIL
         x.right.p = y
      y.p = x.p
      if x.p == T.NIL
         T.root = y
      else if x == x.p.left
         x.p.left = y
      else
         x.p.right = y
      y.right = x
      x.p = y
      y.size = x.size
      x.size = x.left.size + x.right + 1




