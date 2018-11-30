**************
Red Black Tree
**************

**Property**

A red-black tree is a binary tree that satisfies the following **red-black properties**:

   #. Every node is either red or black.
   #. The root is black.
   #. Every leaf (NIL) is black.
   #. If a node is red, then both its children are black.
   #. For each node, all simple paths from the node to descendant leaves 
      contain the same number of black nodes.

**Operation**

.. code-block:: none
   :caption: Taken from *Introduction to Algorithms*

   Left-Rotate(T, x)
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
   
   Right-Rotate(T, x)
      y = x.left
      x.left = y.right
      if y.right != T.NIL
         y.right.p = x
      y.p = x.p
      if x.p == T.NIL
         T.root = y
      else if x == x.p.left
         x.p.left = y
      else 
         x.p.right = y
      y.right = x
      x.p = y
   
   RB-Insert(T, z)
      y = T.NIL
      x = T.root
      while x != T.NIL
         y = x
         if z.key < x.key
            x = x.left
         else
            x = x.right
      z.p = y
      if y == T.NIL
         T.root = z
      else if z.key < y.key
         y.left = z
      else
         y.right = z
      z.left = z.right = T.NIL
      z.color = RED
      RB-Insert-Fixup(T, z)

   RB-Insert-Fixup(T, z)
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
                  Left-Rotate(T, z)
               z.p.color = BLACK      // case 3
               z.p.p.color = RED
               Right-Rotate(T, z.p.p)
         else
            same as then clause with right and left exchanged
      T.root.color = BLACK
