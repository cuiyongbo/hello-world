*************
Git Tricks 02
*************

**Good, better, best**

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

#. git to automatically prunes deleted remote branch
   
    Without ``git fetch --prune,`` remote-tracking branches for a branch the other side 
    already has removed will stay forever. Some people want to always run ``git fetch --prune.``

    To accommodate users who want to either prune always or when fetching from a particular remote, 
    add two new configuration variables `fetch.prune` and `remote.<name>.prune`:

      - ``fetch.prune`` allows to enable prune for all fetch operations.
      - ``remote.<name>.prune`` allows to change the behaviour per remote.

    The latter will naturally override the former, and the ``--[no-]prune`` option from the command 
    line will override the configured default.

    .. code-block:: sh

        git config --global --add remote.origin.prune true
        # or
        git config --global --add fetch.prune true
        # view options
        git config --list
        # delete
        $ git config --global --unset fetch.prune

        # see the result without actually running it
        $ git fetch --prune --dry-run 

#. location of configure file
   
    .. code-block:: sh
    
        # solution one
        git config --list --show-origin

        # solution two
        git config --global --edit

#. git to save username and password
   
    .. code-block:: sh
        
        # solution one will save your information permanently unless you change it later
        git config --global credential.helper store

        # solution two will cache your information for a while, default to 15 minutes.
        git config --global credential.helper  cache
        git config --global credential.helper  'cache  --timeout=3600' # in second


