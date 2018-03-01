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



Delete a remote branch
----------------------

.. code-block:: sh

   git push <remote_name> :<branch_name>

.. note::

   Mostly the <remote_name> is ``origin``. no need to switch to remote_name/branch_name

