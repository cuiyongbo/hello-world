***********
Binary Tree
***********

Thinking for an hour and coding for an hour.

**Implementation**

.. code-block:: none

   Inorder-Tree-Walk(x):
      if x != NIL
         Inorder-Tree-Walk(x.left)
         print x.key
         Inorder-Tree-Walk(x.right)

   Tree-Search(x, k)
      if x == NIL or x.key == k
         return x
      if x.key > k
         Tree-Search(x.left, k)
      else
         Tree-Search(x.right. k)

   Iterative-Tree-Search(x, k)
      while x != NIL and x.key != k
         if x.key > k
            x = x.left
         else
            x = x.right
      return x

   Tree-Minimum(x)
      ASSERT(x != NIL)
      while x.left != NIL
         x = x.left
      return x

   Recursive-Tree-Minimum(x)
      ASSERT(x != NIL)
      if x.left != NIL
         x = Recursive-Tree-Minimum(x.left)
      return x

   Tree-Maximum(x)
      ASSERT(x != NIL)
      while x.right != NIL
         x = x.right
      return x
   
   Recursive-Tree-Maximum(x)
      ASSERT(x != NIL)
      if x.right != NIL
         x = Recursive-Tree-Maximum(x.right)
      return x

   Tree-Successor(x)
      if x.right != NIL
         return Tree-Minimum(x.right)
      y = x.p
      while y != NIL and x == y.right
         x = y
         y = y.p
      return y

   // symmetric
   Tree-Predecessor(x)
      if x.left != NIL
         return Tree-Maximum(x.left)
      y = y.p
      while y != NIL and x == y.left
         x = y
         y = y.p
      return y

   Tree-Insert(T, z)
      y = NIL
      x = T.root
      while x != NIL
         y = x
         if z.key < x.key
            x = x.left
         else
            x = x.right
      z.p = y
      if y == NIL
         T.root = z
      else if z.key < y.key
         y.left = z
      else
         y.right = z

   Recursive-Tree-Insert(T, z)
      x = T
      if x == NIL
         T.root = z
      else if z.key > x.key
         Recursive-Tree-Insert(x.right, z) 
      else
         Recursive-Tree-Insert(x.left, z)

   Translate(T, u, v)
      if u.p = NIL
         T.root = v
      else if u == u.p.left
         u.p.left = v
      else
         u.p.right = v
      if v != NIL
         v.p = u.p

   Tree-Delete(T, z)
      if z.left == NIL
         Translate(T, z, z.right)
      else if z.right == NIL
         Translate(T, z, z.left)
      else
         y = Tree-Minimum(z.right)
         if y.p != z
            Translate(T, y, y.right)
            z.right.p = y
            y.right = z.right
         Translate(T, z, y)
         z.left.p = y
         y.left = z.left

#. Full v.s. Complete binary trees

   +----------------------------------------+--------------------------------------------+
   | Full binary tree                       | Complete binary tree                       |
   +========================================+============================================+
   | .. image:: images/full_binary_tree.jpg | .. image:: images/complete_binary_tree.jpg |
   +----------------------------------------+--------------------------------------------+
   
   According to wikipedia, A full binary tree is a tree in which every node 
   other than the leaves has two children. A complete binary tree is a binary 
   tree in which every level, except possibly the last, is completely filled, 
   and all nodes are as far left as possible.
