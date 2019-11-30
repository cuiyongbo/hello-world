*************
Git Tricks 04
*************

#. Git to cherry-pick

    .. code-block:: sh

        $ git log --oneline local_stuff
        368ac83 (local_stuff) refactored map_deinit
        655b11c added an example
        d6c355f (origin/master, origin/HEAD) Added copyright/license header to source files
        ...

        $ git checkout master
        $ git log --oneline
        d6c355f (HEAD -> master, origin/master, origin/HEAD) Added copyright/license header to source files
        ec5f33c Added package.json file
        ...

        $ git cherry-pick 655b11c 368ac83 # the order matters
        [master 5aef46c] added an example
         Date: Tue Nov 26 23:43:19 2019 +0800
         4 files changed, 74 insertions(+), 1 deletion(-)
         create mode 100644 .gitignore
         create mode 100644 example/Makefile
         create mode 100644 example/example.c
        [master 89e03a1] refactored map_deinit
         Date: Wed Nov 27 00:02:01 2019 +0800
         3 files changed, 58 insertions(+), 57 deletions(-)

        $ git log --oneline
        89e03a1 (HEAD -> master) refactored map_deinit
        5aef46c added an example
        d6c355f (origin/master, origin/HEAD) Added copyright/license header to source files
