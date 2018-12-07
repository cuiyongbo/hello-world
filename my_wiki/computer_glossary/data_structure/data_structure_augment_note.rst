*************************
Agumenting Data Structure
*************************

.. code-block:: none
   :caption: Taken from *Introduction to Algorithms*

   x.size = x.left.size + x.right.size + 1

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

   OS-Select-Loop(x, i)
      while x != T.nil
         r = x.left.size + 1
         if i == r
            break
         else if i < r
            x = x.left
         else
            x = x.right
            i = i - r
      return x

   // Determining the rank of an element
   OS-Rank(T, x)
      r = x.left.size+1
      y=x
      while y != T.root
         if y == y.p.right
            r = r + y.p.left.size + 1
         y = y.p
      return r

   OS-Rank-Recursive(T, x)
      r = T.root.left.size + 1
      if x.key == T.root.key
         return r
      else if x.key > T.root.key
         return r + OS-Rank-Recursive(T.root.right, x)
      else
         return OS-Rank-Recursive(T.root.left, x.p)

.. code-block:: none

   OS-Insert(T, z)
      y = T.nil
      x = T.root
      while x != T.nil
         y = x
         x.size = x.size + 1
         if z.key < x.key
            x = x.left
         else 
            x = x.right
      z.p = y
      if y == T.nil
         T.root = z
      else if y.key > z.key
         y.left = z
      else
         y.right = z
      z.left = z.right = T.nil
      z.color = RED
      z.size = 1
      OS-Insert-Fixup(T, z)

   OS-Insert-Fixup(T, z)
      while z.p.color == RED
         if z.p == z.p.p.left
            y = z.p.p.right   // z's uncle   
            if y.color == RED      // case 1
               z.p.color = BlACK
               y.color = BLACK
               z.p.p.color = RED
               z = z.p.p
            else if z == z.p.right  
                  z = z.p            // case 2
                  OS-Left-Rotate(T, z)
               z.p.color = BLACK      // case 3
               z.p.p.color = RED
               OS-Right-Rotate(T, z.p.p)
         else
            y = z.p.p.left
            if y.color = RED
               z.p.color = BLACK
               y.color = BLACK
               z.p.p.color = RED
               z = z.p.p
            else if z == z.p.left
                  z = z.p
                  OS-Right-Rotate(T, z)
               z.p.color = BLACK
               z.p.p.color = RED
               OS-Left-Rotate(T, z.p.p)
      T.root.color = BLACK 
      
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

.. code-block:: none

  OS-Transplant(T, u, v)
      if u.p = T.nil
         T.root = v
      else if u = u.p.left
         u.p.left = v
      else 
         u.p.right = v
      v.p = u.p 

   OS-Delete(T, z)
      y = z
      y-original-color = y.color
      x = y.p
      while x != T.nil
         x.size = x.size - 1
         x = x.p
      if z.left = T.nil
         x = z.right
         OS-Transplant(T, z, z.right)
      else if z.right = T.nil
         x = z.left
         OS-Transplant(T, z, z.left)
      else
         y = Tree-Minimum(z.right)
         y-original-color = y.color
         x = y.right
         if y.p == z
            x.p = y
         else 
            OS-Transplant(T, y, y.right)
            y.right = z.right
            y.right.p = y
         OS-Transplant(T, z, y)
         y.left = z.left
         y.left.p = y
         y.color = z.color
      if y-original-color == BLACK
         OS-Delete-Fixup(T, x)

.. code-block:: none

   x.max = max(x.int.high, x.left.max, x.right.max)

   Interval-Search(T, i)
      x = T.root
      while x != T.nil and i does not overlap x.int
         if x.left != T.nil and x.left.max >= i.low
            x = x.left
         else
            x = x.right
      return x
