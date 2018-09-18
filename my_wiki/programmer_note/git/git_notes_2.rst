************
Git Tricks 2
************

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
   
   .. code-block:: sh

   $ git pull -ff
   Updating ed2f9a2..d1f3dc1
   Fast-forward
   .../computer_glossary/shell_command/tar_manual.rst | 34 ++++++++++------------
   my_wiki/languages/english_notes_7.rst              |  2 +-
   my_wiki/pending_tasks.rst                          |  2 ++
   my_wiki/programmer_note/gcc/makefile_basics.rst    | 14 +++++++++
   4 files changed, 33 insertions(+), 19 deletions(-)

#. git to automatically prunes deleted remote branch
   
   Without ``git fetch --prune,`` remote-tracking branches for a branch the other side 
   already has removed will stay forever. Some people want to always run ``git fetch --prune.``

   To accommodate users who want to either prune always or when fetching from a particular remote, 
   add two new configuration variables "fetch.prune" and "remote.<name>.prune":

      - ``fetch.prune`` allows to enable prune for all fetch operations.
      - ``remote.<name>.prune`` allows to change the behaviour per remote.

   The latter will naturally override the former, and the ``--[no-]prune`` option from the command 
   line will override the configured default.

   Since ``--prune`` is a potentially destructive operation (Git doesn't keep reflogs for deleted references yet), 
   we don't want to prune without users consent, so this configuration will not be on by default.

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
      From gitlab.mapbar.com:server/route-server
       x [deleted]         (none)     -> origin/add_auto_test
       x [deleted]         (none)     -> origin/better_detail
