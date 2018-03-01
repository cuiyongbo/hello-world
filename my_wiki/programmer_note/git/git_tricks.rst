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


Rename a remote branch
----------------------

.. code-block:: sh

   git checkout -b test1 # swith to a test branch, create test branch if it doesn't exist
   git push --set-upstream origin test1 # push the current branch and set the remote as upstream
   git branch -m test # rename branch name to the desired one
   git push origin :test1 test # delete the old-name remote branch and push the new-name local branch
   git push --set-upstream origin test # reset the upstream branch for the new branch


Find the information about branchs
----------------------------------

.. code-block:: sh

   git branch # show local branches
     master
   * test # current branch
   git branch -r # show remote branches
     origin/HEAD -> origin/master # where current local branch points to 
     origin/master
     origin/test
   git branch -v
     master b351f2e [ahead 1] Added git to delete a remote branch
   * test   40eebf1 Reviewed git note
   git branch -vv
     master b351f2e [origin/master: ahead 1] Added git to delete a remote branch
   * test   40eebf1 [origin/test] Reviewed git note
   

