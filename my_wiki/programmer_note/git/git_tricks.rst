**********
Git Tricks
**********

Create a new local branch
=========================

   .. code-block:: sh

      git checkout -B branch_name remotes/origin/branch_name --
      git checkout -B branch_name origin/branch_name
      git checkout -b branch_name # branch_name doesn't exist.


Find the information about branchs
==================================

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
=====================

   If you want to rename a branch while pointed to any branch, do:
   
   .. code-block:: sh
   
      git branch -m <oldname> <newname>
   
   If you want to rename the current branch, you can do:
   
   .. code-block:: sh
   
      git branch -m <newname>
   
   A way to remember this, is ``-m`` is for "move" (or mv), which is how you rename files.


Delete a local branch
=====================

   .. code-block:: sh
   
      git branch -D <branch_name>


Delete a remote branch
======================

   .. code-block:: sh
   
      git push <remote_name> :<branch_name>
   
   .. note::
   
      Mostly the <remote_name> is ``origin``. no need to switch to remote_name/branch_name


Rename a remote branch
======================

   .. code-block:: sh
   
      git checkout -b test1 # swith to a test branch, create test branch if it doesn't exist
      git push --set-upstream origin test1 # push the current branch and set the remote as upstream
      git branch -m test # rename branch name to the desired one
      git push origin :test1 test # delete the old-name remote branch and push the new-name local branch
      git push --set-upstream origin test # reset the upstream branch for the new branch


Commit skip add
===============

   By using the ``-a`` switch with the commit command to automatically "add" changes from
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
=====================

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
=====================

   .. code-block:: sh
      :caption: git stash usage 
   
      $ git stash help
      usage: git stash list [<options>]
         or: git stash show [<stash>]
         or: git stash drop [-q|--quiet] [<stash>]
         or: git stash ( pop | apply ) [--index] [-q|--quiet] [<stash>]
         or: git stash branch <branchname> [<stash>]
         or: git stash [save [--patch] [-k|--[no-]keep-index] [-q|--quiet]
                             [-u|--include-untracked] [-a|--all] [<message>]]
         or: git stash clear
      
   .. code-block:: sh

      $ git stash save -- combine_commits
      Saved working directory and index state On test: combine_commits
      HEAD is now at cd1e124 commit another 3 commits
      
      $ git stash list
      stash@{0}: On test: combine_commits
      
      $ git stash drop stash@{0} # delete a stash
      Dropped stash@{0} (243d8bf957027713d5bc89be8b66c214e9e7abf9)
      
      $ git stash pop # restore changes


Combine several commits into one
================================

#. combine last 2 commits

   .. code-block:: sh
  
      $ git log -5 --oneline
      7d00a71 deleted python_indention_error.PNG
      b589a16 Added boolean functions
      d404925 Added iterator functions
      55d5b05 added help and dir
      a89a0e3 added int, long, float, complex
      
      $ git reset --soft HEAD^
      
      $ git commit -a --amend
      
      cuiyb@cuiyb MINGW64 /c/VS-Demo/hello-world/my_wiki (test)
      $ git log --oneline -5
      ded0055 Added boolean functions
      d404925 Added iterator functions
      55d5b05 added help and dir
      a89a0e3 added int, long, float, complex
      5fec164 Added type, isinstance

#. combine last n commits

   .. code-block:: sh

      $ git log --oneline -5
      ded0055 Added boolean functions
      d404925 Added iterator functions
      55d5b05 added help and dir
      a89a0e3 added int, long, float, complex
      5fec164 Added type, isinstance
      
      $ git rebase -i HEAD~4
      
      $ git log --oneline -5
      2bc541a added int, long, float, complex
      5fec164 Added type, isinstance
      00e1ffb added chr, ord, unichr, all, any
      0edff53 Added raillery, habit-forming, off-license
      ab4b8b8 Added extern c linkage
   
   .. code-block:: sh
      :caption: rebase options

      pick   a89a0e3 added int, long, float, complex     
      squash 55d5b05 added help and dir
      squash d404925 Added iterator functions
      squash ded0055 Added boolean functions
   
#. another method to combine last n commits

   .. code-block:: sh

      $ git log --oneline -5
      2bc541a added int, long, float, complex
      5fec164 Added type, isinstance
      00e1ffb added chr, ord, unichr, all, any
      0edff53 Added raillery, habit-forming, off-license
      ab4b8b8 Added extern c linkage
      
      $ git rebase -i 0edff53
      
      $ git log --oneline -5
      e4afdcd added chr, ord, unichr, all, any
      0edff53 Added raillery, habit-forming, off-license
      ab4b8b8 Added extern c linkage
      90a7dc6 Failed to refrain myself in weekends
      3639325 added clamp

   .. code-block:: sh
      :caption: rebase options

      pick   00e1ffb added chr, ord, unichr, all, any
      squash 5fec164 Added type, isinstance
      squash 2bc541a added int, long, float, complex

#. more examples
   
   .. code-block:: sh

      $ git log --oneline -5
      e4afdcd added chr, ord, unichr, all, any
      0edff53 Added raillery, habit-forming, off-license
      ab4b8b8 Added extern c linkage
      90a7dc6 Failed to refrain myself in weekends
      3639325 added clamp
      
      $ git rebase -i HEAD~4
      
      $ git log --oneline -5
      8442056 added chr, ord, unichr, all, any
      eb4ad04 Failed to refrain myself in weekends
      3639325 added clamp
      7583d4b added pansy
      a4ffedb Moved lethargy
      
      .. code-block:: sh
         :caption: rebase option
      
         pick   90a7dc6 Failed to refrain myself in weekends
         squash ab4b8b8 Added extern c linkage
         squash 0edff53 Added raillery, habit-forming, off-license
         pick   e4afdcd added chr, ord, unichr, all, any

   .. note::
   
      Important: If you've already pushed commits to remote server, 
      and then squash them locally, you will have to force the push to your branch.
      
      .. code-block:: sh
      
         $ git push origin branch-name --force
      
      Helpful hint: You can always edit your last commit message, 
      before pushing, by using:
      
      .. code-block:: sh
      
         $ git commit --amend


Discard unstaged changes in working directory
=============================================

   .. code-block:: sh
   
      git checkout -- <file>...


Git customization
=================

   warning: *push.default* is unset; its implicit value is changing in
   Git 2.0 from ``'matching'`` to ``'simple'``. To squelch this message
   and maintain the current behavior after the default changes, use::
   
     git config --global push.default matching
   
   To squelch this message and adopt the new behavior now, use::
   
     git config --global push.default simple
   
   When *push.default* is set to ``'matching'``, git will push local branches
   to the remote branches that already exist with the same name.
   
   In Git 2.0, Git will default to the more conservative ``'simple'``
   behavior, which only pushes the current branch to the corresponding
   remote branch that ``'git pull'`` uses to update the current branch.
   
   See ``'git help config'`` and search for ``'push.default'`` for further
   information. (the ``'simple'`` mode was introduced in Git 1.7.11. Use the
   similar mode ``'current'`` instead of ``'simple'`` if you sometimes use
   older versions of Git).


Git to abort git pull
=====================

   .. code-block:: sh
      
         git reset --keep HEAD@{1}

   .. note:: 

      Note that any local changes will be discarded.


Git to checkout a new branch and track itself
=============================================

   .. code-block:: sh

      $ git checkout -b brach_name
      # perform changing and commit changes
      $ git push -u origin branch_name


Git force pull
==============

   .. note:: 
   
      If you have any local changes, they will be lost.
      With or without ``--hard`` option, any local commits
      that haven't been pushed will be lost. If you have any
      files that are not tracked by Git (e.g. uploaded user
      content), these files will not be affected.
   
   Basically::
   
      git fetch --all
   
   Then, you have two options::
   
      git reset --hard origin/master
   
   OR If you are on some other branch::
   
      git reset --hard origin/<branch_name>
   
   Explanation:
   
   ``git fetch`` downloads the latest from remote without trying to
   merge or rebase anything. Then the ``git reset`` resets the ``master``
   branch to what you just fetched. The ``--hard`` option changes all the files
   in your working tree to match the files in ``origin/master``.
   
   and you can maintain current local commits by creating a branch from master
   before resetting::
   
      git checkout master
      git branch new-branch-to-save-current-commits
      git fetch --all
      git reset --hard origin/master
   
   After this, all of the old commits will be kept in ``new-branch-to-save-current-commits``.
   Uncommitted changes however (even staged), will be lost. Make sure to stash and commit anything you need.


Change remote url
=================

**Syntax**

   .. code-block:: sh
   
      git remote get-url [--push] [--all] <name>
   
   Retrieves the URLs for a remote. Configurations for insteadOf and pushInsteadOf
   are expanded here. By default, only the first fetch URL is listed.
   
   #. With ``--push``, push URLs are queried rather than fetch URLs.
   #. With ``--all``, all URLs for the remote will be listed. [only FETCH url]
   
   
   .. code-block:: sh
   
      git remote set-url [--push] <name> <newurl> [<oldurl>]
      git remote set-url --add <name> <newurl>
      git remote set-url --delete <name> <url>
   
   
   Changes URLs for the remote. Sets first URL for remote *name* (mostly, *name* is ``origin``) that
   matches regex *oldurl* (first URL if no *oldurl* is given) to  *newurl*. If *oldurl* doesn’t match
   any URL, an error occurs and nothing is changed.
   
   #. With ``--push``, push URLs are manipulated instead of fetch URLs.
   
   #. With ``--add``, instead of changing existing URLs, new URL is added.
   
   #. With ``--delete``, instead of changing existing URLs, all URLs matching regex *url* are deleted
      for remote *name*. Trying to delete all non-push URLs is an error.
   
   
   .. note::
   
      Note that the push URL and the fetch URL, even though they can be set differently,
      must still refer to the same place. What you pushed to the push URL should be what
      you would see if you immediately fetched from the fetch URL. If you are trying to
      fetch from one place (e.g. your upstream) and push to another (e.g. your publishing
      repository), use two separate remotes.

**Example**

   .. code-block:: sh

      git remote set-url origin https://github.com/akheron/jansson.git


Clean up project
================

   See :doc:`git_clean_tricks`.


Cherry-pick one commit
======================

   .. code-block::

      $ git cherry-pick <commit-id>


