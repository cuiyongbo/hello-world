***********
Binary Tree
***********

Thinking for an hour and coding for an hour.

**Rooted-tree property**

The number of children of a node x in a rooted tree T equals the **degree** of x.
The length of the simple path from the root r to a node x is the **depth** of x in T.
A **level** of a tree consists of all nodes at the same depth. The **height** of a node
in a tree is the number of edges on the longest simple downward path from the node to a leaf,
and **the height of a tree is the height of its root.**

**binary-search-tree property**

Let x be a node in a binary search tree. If y is a node in the left subtree
of x, then :math:`y.key \leq x.key`. If y is a node in the right subtree of x,
then :math:`y.key \geq x.key`.

**Implementation**

.. code-block:: none

    Inorder-Tree-Walk(x):
        if x != NIL
            Inorder-Tree-Walk(x.left)
            print x.key
            Inorder-Tree-Walk(x.right)

    Tree-Search(x, k)
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

    Tree-Maximum(x)
        ASSERT(x != NIL)
        while x.right != NIL
            x = x.right
        return x

    # the successor of node x is the node with smallest key
    # that is larger than x.key
    Tree-Successor(x)
        if x.right != NIL
            return Tree-Minimum(x.right)
        y = x.p
        while y != NIL and x == y.right
            x = y
            y = y.p
        return y

    # the predecessor of node x is the node with largest key
    # that is smaller than x.key
    Tree-Predecessor(x)
        if x.left != NIL
            return Tree-Maximum(x.left)
        y = x.p
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

    Transplant(T, u, v)
        if u.p == NIL
            T.root = v
        else if u == u.p.left
            u.p.left = v
        else
            u.p.right = v

        if v != NIL
            v.p = u.p

    Tree-Delete(T, z)
        if z.left == NIL
            Transplant(T, z, z.right)
        else if z.right == NIL
            Transplant(T, z, z.left)
        else
            y = Tree-Minimum(z.right) # find z's successor
            if y != z.right
               Transplant(T, y, y.right)
               y.right = z.right
               z.right.p = y
            Transplant(T, z, y)
            y.left = z.left
            z.left.p = y

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

#. leetcode exercise

    * Explore - BST
    *
