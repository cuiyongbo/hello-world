*************
Git Tricks 01
*************

#. Create a new repository

    Start a repository from blank::

        $ cd projectDir
        $ git init

        git init projecName

    .. note::

        git will create a directory named *projecName*

#. Remove project from git version control

    Remove :file:`.git` directory from your projects, you may
    have multi such folders. Try this command: ``find git-project/ -type d -path "*.git" -print0 | xargs -0 rm -rf``.

#. Git to checkout a new branch and track itself

    .. code-block:: sh

        $ git checkout -b brach_name
        # perform changing and commit changes
        $ git push -u origin branch_name
        $ git push -u origin local_branch:remote_branch # remote_branch may be not existing.

        # second solution
        $ git branch dark_web_eye origin/dark_web_eye
        Branch dark_web_eye set up to track remote branch dark_web_eye from origin.

#. Create a new local branch

    .. code-block:: sh

        git checkout -B branch_name remotes/origin/branch_name --
        git checkout -B branch_name origin/branch_name
        git checkout -b branch_name # branch_name doesn't exist.

    .. code-block:: none
        :caption: Manual

        git checkout -b|-B <new_branch> [<start point>]

        Specifying -b causes a new branch to be created as if git-branch(1) were called
        and then checked out. In this case you can use the --track or --no-track options,
        which will be passed to git branch. As a convenience, --track without -b implies
        branch creation; see the description of --track below.

        If -B is given, <new_branch> is created if it doesn’t exist; otherwise, it is reset.
        This is the transactional equivalent of

            $ git branch -f <branch> [<start point>]
            $ git checkout <branch>

        that is to say, the branch is not reset/created unless "git checkout" is successful.

#. Find the information about branchs

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
        git branch -vv # attach upstream branch
            master b351f2e [origin/master: ahead 1] Added git to delete a remote branch
        * test   40eebf1 [origin/test] Reviewed git note

#. Rename a local branch

   If you want to rename a non-current branch, try: ``git branch -m <oldname> <newname>``.
   If you want to rename the current branch, try: ``git branch -m <newname>``.

#. Delete a local branch: ``git branch -D <branch_name>``

#. Delete a remote branch

    .. code-block:: sh

        git push <remote_name> :<branch_name>

    .. note:: Mostly the <remote_name> is ``origin``. no need to switch to remote_name/branch_name

#. Rename a remote branch

    .. code-block:: sh

        git checkout -b test1 # swith to a test branch, create test branch if it doesn't exist
        git push --set-upstream origin test1 # push the current branch and set the remote as upstream
        git branch -m test # rename branch name to the desired one
        git push origin :test1 # delete the old-name remote branch
        git push --set-upstream origin test # reset the upstream branch for the new branch

#. Commit skip add

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

#. Commit with amendment

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
            $ git push --force-with-lease --progress "origin" master:master

#. Git to add removals to version control

    .. code-block:: sh

        $ git add .
        warning: You ran 'git add' with neither '-A (--all)' or '--ignore-removal',
        whose behaviour will change in Git 2.0 with respect to paths you removed.
        Paths like 'src/traffic/te_file_parser.cpp' that are
        removed from your working tree are ignored with this version of Git.

        * 'git add --ignore-removal <pathspec>', which is the current default,
            ignores paths you removed from your working tree.

        * 'git add --all <pathspec>' will let you also record the removals.

        Run 'git status' to check the paths you removed from your working tree.

#. Stash current changes

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

#. Discard unstaged changes in working directory: ``git checkout -- <file>...``

#. Git to abort git pull

    .. code-block:: sh

            git reset --keep HEAD@{1}
            # or
            git reset --hard HEAD^1

    .. note:: Note that any local changes will be discarded.

#. Git force pull

    .. warning::

        If you have any local changes, they will be lost.
        With or without ``--hard`` option, any local commits
        that haven't been pushed will be lost. If you have any
        files that are not tracked by Git (e.g. uploaded user
        content), these files will not be affected.

    Basically: ``git fetch --all``,
    Then, you have two options: ``git reset --hard origin/master``,
    OR If you are on some other branch:`` git reset --hard origin/<branch_name>``.

#. Change remote url

    .. code-block:: sh

        git remote get-url [--push] [--all] <name>

    Retrieves the URLs for a remote. Configurations for insteadOf and pushInsteadOf
    are expanded here. By default, only the first fetch URL is listed.

    * With ``--push``, push URLs are queried rather than fetch URLs.
    * With ``--all``, all URLs for the remote will be listed. [only FETCH url]

    .. code-block:: sh

        git remote set-url [--push] <name> <newurl> [<oldurl>]
        git remote set-url --add <name> <newurl>
        git remote set-url --delete <name> <url>

    Changes URLs for the remote. Sets first URL for remote *name* (mostly, *name* is ``origin``) that
    matches regex *oldurl* (first URL if no *oldurl* is given) to  *newurl*. If *oldurl* doesn’t match
    any URL, an error occurs and nothing is changed.

    * With ``--push``, push URLs are manipulated instead of fetch URLs.
    * With ``--add``, instead of changing existing URLs, new URL is added.
    * With ``--delete``, instead of changing existing URLs, all URLs matching regex *url* are deleted
        for remote *name*. Trying to delete all non-push URLs is an error.

    .. note::

        Note that the push URL and the fetch URL, even though they can be set differently,
        must still refer to the same place. What you pushed to the push URL should be what
        you would see if you immediately fetched from the fetch URL. If you are trying to
        fetch from one place (e.g. your upstream) and push to another (e.g. your publishing
        repository), use two separate remotes.

    .. code-block:: sh

        git remote set-url origin https://github.com/akheron/jansson.git

#. Cherry-pick one commit: ``git cherry-pick <commit-id>``

#. Diff two different files

    .. code-block:: sh

        # First
        $ git diff --no-index fileA  fileB

        # Second
        $ diff fileA fileB

        # Third, colorfully diff, side by side comparison.
        $ vimdiff fileA fileB

#. Comparing with arbitrary commits

    .. code-block:: sh

        # Instead of using the tip of the current branch, compare with the tip of "test" branch
        git diff test

        # Compare with the tip of the current branch, but limit the comparison to the file "test"
        git diff HEAD -- ./test

        # Compare the version before the last commit and the last commit
        git diff HEAD^ HEAD

        # Changes between the tips of the <topic> and the <master> branches
        git diff topic master

        # Changes that occurred on the master branch since when the topic branch was started off it
        git diff topic...master

#. Merge branch

    .. code-block:: sh

        # Merge current branch with <branch>
        git merge <branch>

#. Remove files and keep local

    .. code-block:: sh

        $ git rm
        usage: git rm [<options>] [--] <file>...

        -n, --dry-run         dry run
        -q, --quiet           do not list removed files
        --cached              only remove from the index
        -f, --force           override the up-to-date check
        -r                    allow recursive removal
        --ignore-unmatch      exit with a zero status even if nothing matched

        git rm --cached -r file/directory

    afterwards add file/directory to *.gitignore* so git doesn't add it back.

    .. note::

        gitignore - Specifies intentionally untracked files to ignore

        The purpose of gitignore files is to ensure that certain files
        not tracked by Git remain untracked.

        To stop tracking a file that is currently tracked,
        use **git rm --cached**.

#. Exclude certain commit: ``git revert commit_hash_to_exclude``
