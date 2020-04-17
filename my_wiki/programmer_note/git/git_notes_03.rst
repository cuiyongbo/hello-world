*************
Git Tricks 03
*************

#. Create a new repository

    .. code-block:: sh

        git clone git@XXX/**.git
        cd kangshifu/
        touch README.md
        git add README.md
        git commit -m "add README"
        git push -u origin master

#. Existing project

    .. code-block:: sh

        cd existing_folder
        git init
        git remote add origin git@XXX/**.git
        git add .
        git commit -m "Initial commit"
        git push -u origin master

#. Existing Git repository

    .. code-block:: sh

        cd existing_repo
        git remote rename origin old-origin
        git remote set-url origin git@XXX/**.git
        git push -u origin --all
        git push -u origin --tags

#. Existing local repository

    .. code-block:: sh

        # first solution
        $ git remote rm origin # you may need remove `origin` configuration in global gitconfig
        $ git remote add origin git@XXX/**.git

        # second solution, works but no remote branch in git log
        $ git remote set-url --add origin git@XXX/**.git

        $ git push -u origin master

#. Git to track the commit history of a file

    You really removed all variants of a filename, if a blob was moved over its lifetime.
    ``git log --name-only --follow --all -- filename`` can help you find renames.

#. Git to shrink the size of a repository

    * Cleanup ignore files: ``git clean -dx -ff``, Make sure you really want to get rid of them,
      Alway perform ``git clean -dx -n`` to see the files will be removed. Another shortcut would
      be git clone the repository in a new location.

    * If you really don’t want to clone it, for whatever reasons, then check the following points instead.
      This is a very destructive approach, so make a backup or go back to cloning it. You have been warned.

    * Remove the original refs backed up by git-filter-branch:
      ``git for-each-ref --format="%(refname)" refs/original/ | xargs -n 1 git update-ref -d``.

    * Expire all reflogs: ``git reflog expire --expire=now --all``.

    * Garbage collect all unreferenced objects with ``git gc --prune=now``.

#. Git to change the author of last commit

    .. code-block:: sh

        $ git commit -a -m'added git to force line ending to LF'
        # [master 0d44322] added git to force line ending to LF
        #  Committer: natsume-pc <natsume@mlubuntu.localdomain>
        # Your name and email address were configured automatically based
        # on your username and hostname. Please check that they are accurate.
        # You can suppress this message by setting them explicitly:
        #
        #     git config --global user.name "Your Name"
        #     git config --global user.email you@example.com
        #
        # After doing this, you may fix the identity used for this commit with:
        #
        #     git commit --amend --reset-author

        $ git config --global user.name "natsume"
        $ git config --global user.email "csu20140909@gmail.com"
        $ git commit --amend --reset-author

#. Undo ``git update-index --skip-worktree``

    Solution:: ``git update-index --no-skip-worktree <file>``

#. Git - Difference Between ``assume-unchanged`` and ``skip-worktree``

    ``assume-unchanged`` is designed for cases where it is expensive to check
    whether a group of files have been modified; when you set the bit, git assumes
    the files corresponding to that portion of the index have not been modified in
    the working copy. So it avoids a mess of ``stat`` calls.

    ``skip-worktree`` is more than that: even where git knows that the file has been
    modified, it will pretend it has not been, using the version from the index instead.

    ``--assume-unchanged`` assumes that a developer shouldn’t change a file.
    This flag is meant for improving performance for not-changing folders like SDKs.

    ``--skip-worktree`` is useful when you instruct git not to touch a specific file ever
    because developers should change it. For example, if the main repository upstream hosts
    some production-ready configuration files and you don’t want to accidentally commit changes
    to those files, ``--skip-worktree`` is exactly what you want.

#. Git - Check out, review, and merge locally

    * Fetch and check out the branch for this merge request

        .. code-block:: sh

            git fetch origin
            git checkout -b stable_ti_selectionCost origin/stable_ti_selectionCost

    * Review the changes locally

    * Merge the branch and fix any conflicts that come up

        .. code-block:: sh

            git fetch origin
            git checkout origin/master
            git merge --no-ff stable_ti_selectionCost

    * Push the result of the merge to GitLab

        ``git push origin master``

#. Git bash command line can't drag and drop files

    Enable ``Run as Administrator`` when running git bash.

#. Git to show a list of modified files between commits

    Solution: ``git diff --name-only commit1Hash commit2Hash``.

    Particularly, if you want compare between a commit and HEAD,
    run ``git diff --name-only commit1Hash HEAD``, or ``git diff --name-only commit1Hash``
    if you want to include changed-not-yet-committed files.
    Using the ``--name-status`` flag instead of ``--name-only`` is handy
    to get a list of files and see their modification status, such as Added or Modified.

    .. code-block:: sh

        $ git log -3 --format=format:'%h:%s'
        64ce04de:added loon pic
        2ddcc7cc:added a tree pic
        96074ea8:added cross-grained

        $ git diff --name-status 2ddcc7cc
        M       my_wiki/Makefile
        ...

#. Git to find authors of remote branches

    .. code-block:: sh

        $ git for-each-ref --format='%(authorname) %09 %(refname)' | grep origin | grep pepsi
        pepsi    refs/remotes/origin/extract_route_result_logic
        pepsi    refs/remotes/origin/fix_navicore-4025

#. Git to view changes of a specific commit

    .. code-block:: sh

        git diff COMMIT_HASH~ COMMIT_HASH

#. Remove unused reference

    .. figure:: images/unsupported_reference.png

        Solution: ``git update-ref -d refs/original/refs/heads/master``

#. Remove file/directory from commit history

    .. code-block:: sh

        $ git filter-branch -f --index-filter 'git rm -r --ignore-unmatch python-2.7.14-docs-pdf-a4/'
        $ git filter-branch -f --index-filter 'git rm  --cached --ignore-unmatch *.docx'
        $ git filter-branch -f --index-filter 'git rm  --ignore-unmatch "google test frame.docx"'

#. git to fastward pull

    Solution: ``git pull -ff``.
