*************
Git Tricks 03
*************

Command line instructions

#. Git global setup

    .. code-block:: sh
   
        git config --global user.name "cuiyb"
        git config --global user.email "cuiyb@mapbar.com"

#. Create a new repository
      
    .. code-block:: sh

        git clone git@gitlab.mapbar.com:cuiyb/past-ti-fetcher.git
        cd past-ti-fetcher
        touch README.md
        git add README.md
        git commit -m "add README"
        git push -u origin master

#. Existing folder

    .. code-block:: sh

        cd existing_folder
        git init
        git remote add origin git@gitlab.mapbar.com:cuiyb/past-ti-fetcher.git
        git add .
        git commit -m "Initial commit"
        git push -u origin master

#. Existing Git repository

    .. code-block:: sh

        cd existing_repo
        git remote rename origin old-origin
        git remote add origin git@gitlab.mapbar.com:cuiyb/past-ti-fetcher.git
        git push -u origin --all
        git push -u origin --tags

#. Existing local repository
   
    .. code-block:: sh

        $ git remote set-url --add origin git@gitlab.mapbar.com:cuiyb/past-ti-fetcher.git
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

#. Git to force line ending to LF
   
    .. code-block:: sh

        git config --global core.autocrlf true

#. Git to reset commit author
   
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
