************************************************
find - search for files in a directory hierarchy
************************************************

**DESCRIPTION**

   .. code-block:: sh

      find [-H] [-L] [-P] [-D debugopts] [-Olevel] [starting-point...] [expression]

   This manual page documents the GNU version of :command:`find`. GNU :command:`find` searches the directory tree
   rooted at each given *starting-point* by evaluating the given expression from left to right, according to the
   rules of precedence (see section OPERATORS), until the outcome is known (the left hand side is false for and
   operations, true for or), at which point :command:`find` moves on to the next file name. If no *starting-point*
   is specified, ``'.'`` is assumed.

   If you are using :command:`find` in an environment where security is important (for example if you are using it
   to search directories that are writable by other users), you should read the "Security Considerations" chapter of the
   findutils documentation, which is called **Finding Files** and comes with findutils. That document also includes a
   lot more detail and discussion than this manual page, so you may find it a more useful source of information.


**OPTIONS**

   This manual page talks about options within the expression list. These options control the behaviour of :command:`find`
   but are specified immediately after the last path name. The five 'real' options :option:`-H`, :option:`-L`, :option:`-P`,
   :option:`-D`, and :option:`-O` must appear before the first path name, if at all. A double dash ``--`` can also be used
   to signal that any remaining arguments are not options (though ensuring that all start points begin with either './' or
   '/' is generally safer if you use wildcards in the list of start points).

   .. option:: -P     

      Never follow symbolic links. This is the default behaviour. 

   .. option:: -L     

      Follow symbolic links.  When find examines or prints information about files, the information used shall
      be taken from the properties of the file to which the link points, not from the link itself (unless it is
      a broken symbolic link or find is unable to examine the file to which the link points).  Use of this
      option implies -noleaf. If you later use the -P option, -noleaf will still be in effect.  If -L is in
      effect and find discovers a symbolic link to a subdirectory during its search, the subdirectory pointed
      to by the symbolic link will be searched.

      When the -L option is in effect, the -type predicate will always match against the type of the file that
      a symbolic link points to rather than the link itself (unless the symbolic link is broken).  Actions that
      can cause symbolic links to become broken while find is executing (for example -delete) can give rise  to
      confusing behaviour.  Using -L causes the -lname and -ilname predicates always to return false.

   .. option:: -H     

      Do not follow symbolic links, except while processing the command line arguments. If -H is in effect
      and one of the  paths specified on the command line is a symbolic link to a directory, the contents of
      that directory will be examined (though of course -maxdepth 0 would prevent this).

      If more than one of -H, -L and -P is specified, each overrides the others; the last one appearing on
      the command line takes effect. 


**EXPRESSION**

   The part of the command line after the list of *starting points* is the expression.
   This is a kind of query specification describing how we match files and what we do
   with the files that were matched. An expression is composed of a sequence
   of things::

      Tests  
         Tests return a true or false value, usually on the basis of some property
         of a file we are considering. The -empty test for example is true only
         when the current file is empty.

      Actions
         Actions have side effects (such as printing something on the standard output)
         and return either true or false, usually based on whether or not they are successful.
         The -print action for example prints the name of the current file on the standard output.

       Global options
         Global options affect the operation of tests and actions specified on any part
         of the command line. Global options always return true. The -depth option for
         example makes find traverse the file system in a depth-first order.

       Positional options
         Positional optiona affect only tests or actions which follow them.
         Positional options always return true. The -regextype option for example
         is positional, specifying the regular expression dialect for regulat
         expressions occurring later on the command line.

       Operators
         Operators join together the other items within the expression.
         They include for example -o (meaning logical OR) and -a (meaning
         logical AND). Where an operator is missing, -a is assumed.

   If the whole expression contains no actions other than -prune or -print,
   -print is performed on all files for which the whole expression is true.

   The -delete action also acts like an option (since it implies -depth).

   **POSITIONAL OPTIONS**

   .. option:: -regextype type

      Changes the regular expression syntax understood
      by -regex and -iregex tests which occur later on
      the command line.

   .. option:: -warn, -nowarn

      Turn warning messages on or off. 

   **GLOBAL OPTIONS**

      Global options always return true. To prevent confusion, global options
      should specified on the command-line after the list of start points, just
      before the first test, positional option or action::

      .. option:: -d / -depth
         
         Process each directory's contents before the directory itself.
         The -delete action also implies -depth.

      .. option:: -maxdepth levels
         
         Descend at most levels (a non-negative integer) levels of directories
         below the starting-points. -maxdepth 0 means only apply the tests
         and actions to the starting-points themselves.

      .. option:: -mount / -xdev
         
         Don't descend directories on other filesystems. 

      .. option:: -noleaf

         Do not optimize by assuming that directories contain 2 fewer subdirectories than their hard link count.
         This option is needed when searching filesystems that do not follow the Unix directory-link convention,
         such as CD-ROM or MS-DOS filesystems or AFS volume mount points. Each directory on a normal Unix filesystem
         has at least 2 hard links: its name and its '.' entry. Additionally, its subdirectories (if any) each
         have a '..' entry linked to that directory. When find is examining a directory, after it has statted 2
         fewer subdirectories than the directory's link count, it knows that the rest of the entries in the
         directory are non-directories ('leaf' files in the directory tree). If only the files' names need to
         be examined, there is no need to stat them; this gives a significant increase in search speed.

   **TESTS**

      .. option:: -fstype type
         
         File is on a filesystem of type *type*. You can use -printf with the %F
         directive to see the types of your filesystems.

      .. option:: -name pattern, -iname pattern

         Base of file name (**the path with the leading directories removed**) matches shell pattern *pattern*.
         Because the leading directories are removed, the file names considered for a match with -name will never include
         a slash, so '-name a/b' will never match anything (you probably need to use -path instead). The metacharacters
         ('*',  '?', and '[]') match a '.' at the start of the base name . To ignore a directory and the files under it,
         use -prune; Braces are not recognised as being special, despite the fact that some shells including Bash imbue
         braces with a special meaning in shell patterns. The filename matching is performed with the use of the
         :manpage:`fnmatch(3)` library function. Don't forget to enclose the *pattern* in quotes in order to protect
         it from expansion by the shell. -iname is the case-insensitive counterpart.

      .. option:: -regex pattern, -iregex pattern

         File name matches regular expression pattern. **This is a match on the whole path, not a search.**  For
         example, to match a file named './fubar3', you can use the regular expression '.*bar.' or '.*b.*3', but
         not 'f.*r3'. The regular expressions understood by find are by default Emacs Regular Expressions,  but
         this can be changed with the -regextype option. -iregex is the case-insensitive counterpart.

      .. option:: -samefile name

         File refers to the same inode as name. When -L is in effect, this can include symbolic links.

      .. option:: -path pattern, -ipath pattern

         File name matches shell pattern pattern. The metacharacters do not treat '/' or '.' specially;
         so, for example, ``find . -path "./sr*sc"`` will print an entry for a directory called './src/misc'
         (if one exists). To ignore a whole directory tree, use -prune rather than checking every file in
         the tree. For example, to skip the directory 'src/emacs' and all files and directories under it,
         and print the names of the other files found, do something like this: ``find . -path ./src/emacs -prune -o -print``.
         **Note that the pattern match test applies to the whole file name**, starting from one of the start points
         named on the command line. It would only make sense to use an absolute path name here if the relevant
         start point is also an absolute path. This means that this command will never match anything:
         ``find bar -path /foo/bar/myfile -print``. Find compares the -path argument with the concatenation of
         a directory name and the base name of the file it's examining. Since the concatenation will never end
         with a slash, -path arguments ending in a slash will match nothing (except perhaps a start point
         specified on the command line).-ipath is the case-insensitive counterpart.

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

      .. option:: -xtype c
      
         The same as -type unless the file is a symbolic link.
         -xtype checks the type of the file that -type does not check.

      .. option:: -uid n

         File's numeric user ID is *n*.

      .. option:: -user uname

         File is owned by user *uname* (numeric user ID allowed).

   **ACTIONS**

      .. option:: -delete

         Delete files; true if removal succeeded. If the removal failed, an error message is issued.
         and find's exit status will be nonzero (when it eventually exits). Use of -delete automatically
         turns on the :option:`-depth`.

         Warnings: Don't forget that the find command line is evaluated as an expression, so putting -delete first
         will make find try to delete everything below the starting points you specified.  When testing a find
         command line that you later intend to use with -delete, you should explicitly specify -depth in order to
         avoid later surprises. Because -delete implies -depth, you cannot usefully use -prune and -delete together.

      .. option:: -print 

         True; print the full file name on the standard output, followed by a newline. If you are piping the
         output of find into another program and there is the faintest possibility that the files which you are
         searching for might contain a newline, then you should seriously consider using the -print0 option
         instead of -print.

      .. option:: -print0

         True; print the full file name on the standard output, followed by a null character
         (instead of the newline character that -print uses). This allows file names that contain
         newlines or other types of whitespace to be correctly interpreted by programs that process
         the find output. This option corresponds to the -0 option of :command:`xargs`.

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

         This variant of the -exec action runs the specified command on the selected files, but the command line
         is built by appending each selected file name at the end; the total number of invocations of the command
         will be much less than the number of matched files. The command line is built in much the same way that
         xargs builds its command lines. Only one instance of '{}' is allowed within the command. The command is
         executed in the starting directory.

      .. option:: -execdir command ; / -execdir command {} +

         Like -exec, but the specified command is run from the subdirectory containing the matched file,
         which is not normally the directory in which you started find. This a much more secure method
         for invoking commands, as it avoids race conditions during resolution of the paths to the matched
         files. As with the -exec action, the '+' form of -execdir will build a command line to process more
         than one matched file, but any given invocation of command will only list files that exist in the
         same subdirectory. If you use this option, you must ensure that your :envvar:`PATH` environment
         variable does not reference '.'; otherwise, an attacker can run any commands they like by leaving
         an appropriately-named file in a directory in which you will run -execdir. The same applies to having
         entries in :envvar:`PATH` which are empty or which are not absolute directory names.


**EXAMPLES**

   Examples::

      find /tmp -name core -type f -print | xargs /bin/rm -f

      Find files named core in or below the directory /tmp and delete them.
      Note that this will work incorrectly if there are any filenames containing
      newlines, single or double quotes, or spaces. To combat this using:

      find /tmp -name core -type f -print0 | xargs -0 /bin/rm -f

      find . -type f -exec file '{}' \;

      Runs 'file' on every file in or below the current directory. Notice that the braces are enclosed in single
      quote marks to protect them from interpretation as shell script punctuation. The semicolon is similarly pro‐
      tected by the use of a backslash, though single quotes could have been used in that case also.

      find /sbin /usr/sbin -executable \! -readable -print

      Search for files which are executable but not readable.

      find . -perm 664

      Search for files which have read and write permission for their owner, and group, but which other users can read
      but not write to. Files which meet these criteria but have other permissions bits set (for example if someone
      can execute the file) will not be matched. To combat this using:

      find . -perm -664

      cd /source-dir
      find . -name .snapshot -prune -o \( \! -name *~ -print0 \)|
      cpio -pmd0 /dest-dir

      This command copies the contents of /source-dir to /dest-dir, but omits files and directories named .snapshot
      (and anything in them). It also omits files or directories whose name ends in ~, but not their contents.  The
      construct -prune -o  \(  ...  -print0  \) is quite common.  The idea here is that the expression before -prune
      matches things which are to be pruned. However, the -prune action itself returns true, so the following -o
      ensures that the right hand side is evaluated only for those directories which didn't get pruned (the contents
      of the pruned directories are not even visited, so their contents are irrelevant). The expression on the right
      hand side of the -o is in parentheses only for clarity. It emphasises that the -print0 action takes place only
      for things that didn't have -prune applied to them. Because the default 'and' condition between tests binds
      more tightly than -o, this is the default anyway, but the parentheses help to show what is going on.

      find repo/ -exec test -d {}/.svn \; -or \
      -exec test -d {}/.git \; -or -exec test -d {}/CVS \; \
      -print -prune

      Given the following directory of projects and their associated SCM administrative directories, perform an
      efficient search for the projects' roots:

      repo/project1/CVS
      repo/gnu/project2/.svn
      repo/gnu/project3/.svn
      repo/gnu/project3/src/.svn
      repo/project4/.git

      In this example, -prune prevents unnecessary descent into directories that have already been discovered (for
      example we do not search project3/src because we already found project3/.svn), but ensures sibling directories
      (project2 and project3) are found.

      find /dev/shm/ -iname "*hashmap" -print0 | xargs -0 rm >/dev/null 2>&1
      find /dev/shm/ -name "[a-zA-Z]*-[0-9]*" -print0 | xargs -0 rm >/dev/null 2>&1
      find /dev/shm/ -iname "*hashmap" -delete
      find /dev/shm/ -name "[a-zA-Z]*-[0-9]*" -delete

      find /tmc_backup/tmc_backup/download_tmc/2018/05/15/15/ -name "shanghai.txt.gz" -exec cp --parents \{\} shanghai_tmc/ \;

      $ find /run/shm/ | grep -E "idListHashMap|teHashMap"
      /run/shm/idListHashMap
      /run/shm/teHashMap
      
      # display loc in a project
      $ find ti-servers/ -name *.cpp -o -name *.h | xargs wc -l \{\} \;

      # batch rename files
      $ find . -type f -exec mv \{\} \{\}.jpg \; 