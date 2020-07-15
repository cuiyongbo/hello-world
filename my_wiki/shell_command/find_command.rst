***********
find Manual
***********

**DESCRIPTION**

    .. code-block:: sh

        find [-H] [-L] [-P] [-D debugopts] [-Olevel] [starting-point...] [expression]

    This manual page documents the GNU version of :command:`find`. GNU :command:`find` searches the directory tree
    rooted at each given *starting-point* by evaluating the given expression from left to right, according to the
    rules of precedence (see section OPERATORS), until the outcome is known (the left hand side is false for and
    operations, true for or), at which point :command:`find` moves on to the next file name. If no *starting-point*
    is specified, ``'.'`` is assumed.

**HOT OPTIONS**

    .. option:: -maxdepth levels

        Descend at most levels (a non-negative integer) levels of directories
        below the starting-points. -maxdepth 0 means only apply the tests
        and actions to the starting-points themselves.

    .. option:: -name pattern, -iname pattern

        Base of file name (**the path with the leading directories removed**) matches shell pattern *pattern*.
        Because the leading directories are removed, the file names considered for a match with ``-name`` will never include
        a slash, so '-name a/b' will never match anything (you probably need to use ``-path`` instead). The metacharacters
        ('*',  '?', and '[]') match a '.' at the start of the base name. To ignore a directory and the files under it,
        use ``-prune``;  ``-iname`` is the case-insensitive counterpart.

    .. option:: -regex pattern, -iregex pattern

        File name matches regular expression pattern. **This is a match on the whole path, not a search.**
        ``-iregex`` is the case-insensitive counterpart.

    .. option:: -path pattern, -ipath pattern

        File name matches shell pattern pattern. The metacharacters do not treat '/' or '.' specially;
        **Note that the pattern match test applies to the whole file name**, starting from one of the start points
        named on the command line. It would only make sense to use an absolute path name here if the relevant
        start point is also an absolute path. Since the concatenation will never end with a slash, ``-path`` arguments
        ending in a slash will match nothing (except perhaps a start point specified on the command line).
        ``-ipath`` is the case-insensitive counterpart.

    .. option:: -fstype type

        File is on a filesystem of type *type*. You can use -printf with the %F
        directive to see the types of your filesystems.

    .. option:: -samefile name

        File refers to the same inode as name. When -L is in effect, this can include symbolic links.

    .. option:: -readable, -writable, -executable

        Matches files which are readable / writable / excutable.

    .. option:: -type c

        File is of type *c*:

            - b: block (buffered) special
            - c: character (unbuffered) special
            - d: directory
            - p: named pipe (FIFO)
            - f: regular file
            - l: symbolic link
            - s: socket

    .. option:: -uid n

        File's numeric user ID is *n*.

    .. option:: -user uname

        File is owned by user *uname* (numeric user ID allowed).

    .. option:: -perm [-|+]mode

        The mode may be either symbolic (see chmod(1)) or an octal number.
        If the mode is preceded by a dash ('-''), this primary evaluates to true
        if at least all of the bits in the mode are set in the file's mode bits.
        If the mode is preceded by a plus ('+'), this primary evaluates to true
        if any of the bits in the mode are set in the file's mode bits. Otherwise,
        this primary evaluates to true if the bits in the mode exactly match the file's mode bits.

    .. option:: -delete

        Delete files; true if removal succeeded. If the removal failed, an error message is issued.
        and find's exit status will be nonzero (when it eventually exits).

    .. option:: -prune

        True; if the file is a directory, do not descend into it. If -depth is given, false; no effect.
        Because -delete implies -depth, you cannot usefully use -prune and -delete together.

    .. option:: -exec command ; / -exec command {} +

        Execute *command*; true if 0 status is returned. All following arguments to find are taken to be arguments
        to the *command* until an argument consisting of ';' is encountered. The string '{}' is replaced by the
        current file name being processed everywhere it occurs in the arguments to the *command*, not just in
        arguments where it is alone, as in some versions of find. Both of these constructions might need to be
        escaped (with a '\') or quoted to protect them from expansion by the shell. The specified *command* is
        run once for each matched file. The command is executed in the starting directory. There are unavoidable
        security problems surrounding use of the -exec action; you should use the -execdir option instead.

    .. code-block:: none

        expr1 -a expr2, expr1 -o expr2

            logical and and logical or.

.. code-block:: sh
    :caption: Examples

    find /dev/shm/ -iname "*hashmap" -print0 | xargs -0 rm >/dev/null 2>&1
    find /dev/shm/ -name "[a-zA-Z]*-[0-9]*" -print0 | xargs -0 rm >/dev/null 2>&1
    find /dev/shm/ -iname "*hashmap" -delete
    find /dev/shm/ -name "[a-zA-Z]*-[0-9]*" -delete

    find /xixi_backup/xixi_backup/download_xixi/2018/05/15/15/ -name "shanghai.txt.gz" -exec cp --parents \{\} shanghai_xixi/ \;

    $ find /run/shm/ | grep -E "pepsiMap|cokeMap"
    /run/shm/pepsiMap
    /run/shm/cokeMap

#. display line of codes in a project

    Solution: ``find xx-servers/ -name *.cpp -o -name *.h | xargs wc -l \{\} \;``

#. batch rename files

    Solution: ``find . -type f -exec mv \{\} \{\}.jpg \;``

#. find all executables in a directory

    .. code-block:: sh

        $ find . -maxdepth 1 -type f -perm +111
        ./backtrace_permutation
        ./backtrace_combination
        ...

#. skip certain directory

    .. code-block:: sh

        # skip ``english_note_book`` and ``japanese_note_book``
        $ find . -path "./english_note_book" -prune -o -path "./japanese_note_book" -prune -o -name "*.rst"
        ./english_note_book
        ./english_study.rst
        ./japanese_note_book
        ./japanese_study.rst
        ./military_terms.rst
        ...

#. inverse match: ``find base/ -type f ! -name '*.jpg' -exec rm \{\} \;``
