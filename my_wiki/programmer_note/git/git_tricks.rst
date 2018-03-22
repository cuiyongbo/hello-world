Git Tricks
==========

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
   git branch -a # both local and remote branch
   * master
     remotes/origin/HEAD -> origin/master
     remotes/origin/master
   git branch -v
     master b351f2e [ahead 1] Added git to delete a remote branch
   * test   40eebf1 Reviewed git note
   git branch -vv
     master b351f2e [origin/master: ahead 1] Added git to delete a remote branch
   * test   40eebf1 [origin/test] Reviewed git note
   

Rename a local branch
---------------------

If you want to rename a branch while pointed to any branch, do:

.. code-block:: sh

   git branch -m <oldname> <newname>

If you want to rename the current branch, you can do:

.. code-block:: sh

   git branch -m <newname>

A way to remember this, is ``-m`` is for "move" (or mv), which is how you rename files.


Delete a local branch
---------------------

.. code-block:: sh

   git branch -D <branch_name>


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


Commit skip add
---------------

by using the ``-a`` switch with the commit command to automatically "add" changes from
all known files (i.e. all files that are already listed in the index) and
to automatically "rm" files in the index that have been removed from the working tree,
and then perform the actual commit. 

.. code-block:: sh

   $ git commit -a -m "added git commit: -a, --amend options"
   $ git status
   On branch master
   Your branch is ahead of 'origin/master' by 1 commit.
     (use "git push" to publish your local commits)
   Untracked files:
     (use "git add <file>..." to include in what will be committed)
   
           programmer_note/number_tricks.rst # untracking files still unstaged, thus, uncommitted. 
   
   nothing added to commit but untracked files present (use "git add" to track)


Commit with amendment
---------------------

   .. code-block:: sh
   
      $ git log -2 --oneline
      8b8ce2f added number tricks
      6cbd05f added git commit: -a, --amend options
      
      $ git commit -a --amend
   
      $ git log -2 --oneline
      edb911d added number tricks # note that the commit ID has changed
      6cbd05f added git commit: -a, --amend options
   
      $ git log -2 --oneline
      8710e3c implemented git commit --amend
      edb911d added number tricks
      
      $ git commit -a --amend -m"implemented git commit --amend, and fix"
      
      $ git log -2 --oneline
      2ee7aee implemented git commit --amend, and fix
      edb911d added number tricks

   .. note::

      Important: If you've already pushed commits to remote server, and then squash them locally,
      you will have to force the push to your branch.

      .. code-block:: sh

         $ git push origin branch-name --force


Stash current changes
---------------------

   .. code-block:: sh
   
      $ git stash help
      usage: git stash list [<options>]
         or: git stash show [<stash>]
         or: git stash drop [-q|--quiet] [<stash>]
         or: git stash ( pop | apply ) [--index] [-q|--quiet] [<stash>]
         or: git stash branch <branchname> [<stash>]
         or: git stash [save [--patch] [-k|--[no-]keep-index] [-q|--quiet]
                             [-u|--include-untracked] [-a|--all] [<message>]]
         or: git stash clear
      
      
      $ git stash save -- combine_commits
      Saved working directory and index state On test: combine_commits
      HEAD is now at cd1e124 commit another 3 commits
      
      $ git stash list
      stash@{0}: On test: combine_commits
      
      $ git stash drop stash@{0} # delete a stash
      Dropped stash@{0} (243d8bf957027713d5bc89be8b66c214e9e7abf9)
      
      $ git stash pop # restore changes