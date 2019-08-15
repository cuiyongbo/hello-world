**************
Red Black Tree
**************

**Property**

A red-black tree is a binary tree that satisfies the following **red-black properties**:

   #. Every node is either red or black.
   #. The root is black.
   #. Every leaf (nil) is black.
   #. If a node is red, then both its children are black.
   #. For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.

**Operation**

.. code-block:: none
   :caption: Taken from *Introduction to Algorithms*

   Left-Rotate(T, x)
      y = x.right
      x.right = y.left
      if y.left != T.nil
         y.left.p = x
      y.p = x.p
      if x.p == T.nil
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
      if y.right != T.nil
         y.right.p = x
      y.p = x.p
      if x.p == T.nil
         T.root = y
      else if x == x.p.left
         x.p.left = y
      else 
         x.p.right = y
      y.right = x
      x.p = y
   
   RB-Insert(T, z)
      y = T.nil
      x = T.root
      while x != T.nil
         y = x
         if z.key < x.key
            x = x.left
         else
            x = x.right
      z.p = y
      if y == T.nil
         T.root = z
      else if z.key < y.key
         y.left = z
      else
         y.right = z
      z.left = z.right = T.nil
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

   RB-Transplant(T, u, v)
      if u.p = T.nil
         T.root = v
      else if u = u.p.left
         u.p.left = v
      else 
         u.p.right = v
      v.p = u.p 

   RB-Delete(T, z)
      y = z
      y-original-color = y.color
      if z.left = T.nil
         x = z.right
         RB-Transplant(T, z, z.right)
      else if z.right = T.nil
         x = z.left
         RB-Transplant(T, z, z.left)
      else
         y = Tree-Minimum(z.right)
         y-original-color = y.color
         x = y.right
         if y.p == z
            x.p = y
         else 
            RB-Transplant(T, y, y.right)
            y.right = z.right
            y.right.p = y
         RB-Transplant(T, z, y)
         y.left = z.left
         y.left.p = y
         y.color = z.color
      if y-original-color == BLACK
         RB-Delete-Fixup(T, x)

   RB-Delete-Fixup(T, x)
      while x != T.root and x.color == BLACK
         if x == x.p.left
            w = x.p.right  // x's sibling                  
            if w.color == RED
               w.color = BLACK               // case 1
               x.p.color = RED
               Left-Rotate(T, x.p)
               w = x.p.right
            if w.left.color == BLACK and w.right.color == BLACK
               w.color = RED                 // case 2
               x = x.p
            else if w.right.color == BLACK
                  w.left.color == BLACK     // case 3
                  w.color = RED
                  Right-Rotate(T, w)
                  w = x.p.right
               w.color = x.p.color          // case 4
               x.p.color = BLACK
               w.right.color = BLACK
               Left-Rotate(T, x.p)
               x = T.root
         else (same as then clause with right and left exchanged)
      x.color = BLACK

#. Case study - nginx red black tree

   * ngx_rbtree_min - find left-most node
   * ngx_rbtree_next - find a node's successor
   * ngx_rbtree_insert
   * ngx_rbtree_delete