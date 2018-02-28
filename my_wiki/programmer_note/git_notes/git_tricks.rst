Git Tricks
==========

Rename a local branch
---------------------

If you want to rename a branch while pointed to any branch, do:

.. code-block:: sh

   git branch -m <oldname> <newname>

If you want to rename the current branch, you can do:

.. code-block:: sh

   git branch -m <newname>

A way to remember this, is ``-m`` is for "move" (or mv), which is how you rename files.
