***************
Git Gonfig Note
***************

**Good, better, best**

#. location of configure file

    .. code-block:: sh

        # solution one
        git config --list --show-origin

        # solution two
        git config --global --edit

#. Git global setup

    .. code-block:: sh

        git config --global user.name "Cherry Luo"
        git config --global user.email "csu20120504@126.com"

        # set vim as the default commit message editor
        git config --global core.editor "vim"

        git config --global core.autocrlf true

#. git to save username and password

    .. code-block:: sh

        # solution one will save your information permanently unless you change it later
        git config --global credential.helper store

        # solution two will cache your information for a while, default to 15 minutes.
        git config --global credential.helper  cache
        git config --global credential.helper  'cache  --timeout=3600' # in second

#. Git to force line ending to CRLF

    .. code-block:: sh

        # https://help.github.com/en/articles/configuring-git-to-handle-line-endings
        git config --global core.autocrlf true

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

#. Git push customization

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
