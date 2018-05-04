:orphan:

*********
git clean
*********

**NAME**

   git-clean - Remove untracked files from the working tree

**SYNOPSIS**

   git clean [-d] [-f] [-i] [-n] [-q] [-e <pattern>] [-x | -X] [--] <path>...

**DESCRIPTION**

Cleans the working tree by recursively removing files that are not under version control,
starting from the current directory.

Normally, only files unknown to Git are removed, but if the ``-x`` option is specified,
ignored files are also removed. This can, for example, be useful to remove all build products.

If any optional ``<path>...`` arguments are given, only those paths are affected.

**OPTIONS**

.. option:: -d

   Remove untracked directories in addition to untracked files.
   If an untracked directory is managed by a different Git repository,
   it is not removed by default. Use :option:`-f` option twice if you
   really want to remove such a directory.

.. option:: -f, --force

   If the Git configuration variable *clean.requireForce* is not set to false,
   git clean will refuse to delete files or directories unless given :option:`-f`,
   :option:`-n`, :option:`-i`. Git will refuse to delete directories with :file:`.git`
   subdirectory or file unless a second :option:`-f` is given.

.. option:: -i, --interactive

   Show what would be done and clean files interactively.

.. option:: -n, --dry-run

   Don’t actually remove anything, just show what would be done.

.. option:: -q, --quiet
   
   Be quiet, only report errors, but not the files that are successfully removed.

.. option:: -e <pattern>, --exclude=<pattern>

   In addition to those found in :file:`.gitignore` (per directory) and
   :file:`$GIT_DIR/info/exclude`, also consider these patterns to be in
   the set of the ignore rules in effect.

.. option:: -x

   Don’t use the standard ignore rules read from  :file:`.gitignore` (per directory)
   and :file:`$GIT_DIR/info/exclude`, but do still use the ignore rules given with
   :option:`-e` options. This allows removing all untracked files, including build
   products. This can be used (possibly in conjunction with ``git reset``) to
   create a pristine working directory to test a clean build.

.. option:: -X

   Remove only files ignored by Git. This may be useful to
   rebuild everything from scratch, but keep manually created files.

Example

.. code-block:: sh

   $ git clean -d -f -x --dry-run
   Would remove C_Jumps.pdf
   Would remove MIT6_096IAP11_lec08_C++_memory_management.pdf
   Would remove MIT6_096IAP11_lec09_C++_template_overload.pdf
   Would remove MIT6_096IAP11_lec10_C++_File_Handling.pdf
   Would remove hacker's_delight_basics.pdf

