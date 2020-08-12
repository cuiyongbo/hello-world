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
        ...
        [master 89e03a1] refactored map_deinit
        ...

        $ git log --oneline
        89e03a1 (HEAD -> master) refactored map_deinit
        5aef46c added an example
        d6c355f (origin/master, origin/HEAD) Added copyright/license header to source files

#. git to cherry-pick file changes from certain commit: ``git checkout commit_hash_to_pick -- file1/to/restore file2/to/restore`` 

#. Git to make patch and apply patch

    .. code-block:: sh

        hello-world $ git log --oneline -8
        70d16586 (HEAD -> master) restructure os problem note
        96c44f26 add a trick to check glibc version
        07287b88 added a gdb note of return command; added cmake note of passing customized environment
        8ecf2810 add a cpp note: scoped enumeration
        1dca4811 (origin/master, origin/HEAD) added ubuntu notes: install node.js, restart network
        ...

        $ git format-patch --stdout origin/master >local_changes.patch
        $ ll local_changes.patch
        -rwxrwxrwx 1 cuiyb cuiyb 461K Feb 28 20:49 local_changes.patch*

        $ git apply --stat local_changes.patch # view changes in these commits
         .../programming_pearls/cpp_keyword_note.rst        |  156 ++++++++++++++++----
         my_wiki/biology_glossary/biology_terms_3.rst       |    1
         .../images/polar_bear_family_1582797794.jpg        |  Bin
        ...
         18 files changed, 250 insertions(+), 84 deletions(-)

        $ git checkout -B patch_demo origin/master
        Branch 'patch_demo' set up to track remote branch 'master' from 'origin'.
        Switched to a new branch 'patch_demo'

        hello-world $ git log --oneline -2
        1dca4811 (HEAD -> patch_demo, origin/master, origin/HEAD) added ubuntu notes: install node.js, restart network
        a52b5836 reviewed hash tutorial: hash function, collision resolution policy, and performance analysis

        hello-world $ git am --signoff <local_changes.patch
        Applying: add a cpp note: scoped enumeration
        .git/rebase-apply/patch:249: new blank line at EOF.
        +
        warning: 1 line adds whitespace errors.
        Applying: added a gdb note of return command; added cmake note of passing customized environment
        Applying: add a trick to check glibc version
        .git/rebase-apply/patch:200: new blank line at EOF.
        +
        warning: 1 line adds whitespace errors.
        Applying: restructure os problem note

        $ git log --oneline -8
        5bdc76a1 (HEAD -> patch_demo) restructure os problem note
        dee13c45 add a trick to check glibc version
        776e37b6 added a gdb note of return command; added cmake note of passing customized environment
        059d64e8 add a cpp note: scoped enumeration
        1dca4811 (origin/master, origin/HEAD) added ubuntu notes: install node.js, restart network
        // ...

#. git to set upstream branch for local branch

    .. code-block:: sh

        # local_branch default to current branch if omitted
        # -u, --set-upstream-to
        git branch --set-upstream-to=origin/<branch> local_branch 
