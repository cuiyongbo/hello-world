***********
Binary Tree
***********

**Implementation**

.. code-block:: none

   Inorder-Tree-Walk(x):
      if x != NIL
         Inorder-Tree-Walk(x.left)
         print x.key
         Inorder-Tree-Walk(x.right)


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
