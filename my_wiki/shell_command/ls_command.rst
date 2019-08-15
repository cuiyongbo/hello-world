****************************
ls - list directory contents
****************************

**DESCRIPTION**

   List information about the FILEs (the current directory by default).
   Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.

   Mandatory arguments to long options are mandatory for short options too.

   .. option:: -a, --all
      
      do not ignore entries starting with .

   .. option:: -A, --almost-all
      
      do not list implied . and ..

   .. option:: --color[=WHEN]
              
      colorize the output; WHEN can be ``'always'`` 
      (default if omitted), ``'auto'``, or ``'never'``.

   .. option:: -F, --classify
      
      append type indicator (one of '\*/=>@|') to entries::

         @ means symbolic link (or that the file has extended attributes).
         * means executable.
         = means socket.
         | means named pipe.
         > means door.
         / means directory.

   .. option:: -h, --human-readable
      
      with -l and/or -s, print human readable sizes (e.g., 1K 234M 2G).

   .. option:: -i, --inode
              
      print the index number of each file

   .. option:: -I, --ignore=PATTERN
         
      do not list implied entries matching shell PATTERN

   .. option:: -l

      use a long listing format.

   .. option:: -o     

      like -l, but do not list group information.

   .. option:: -L, --dereference
              
      when showing file information for a symbolic link,
      show information for the file the link references
      rather than for the link itself.

   .. option:: -R, --recursive
      
      list subdirectories recursively.

   .. option:: -r, --reverse
              
      reverse order while sorting.

   --sort=WORD
         
      sort by WORD instead of name: none (-U), size (-S), time (-t), version (-v), extension (-X).

   .. option:: -c     

      with -lt: sort by, and show, ctime (time of last modification of file status information);
      with -l: show ctime and sort by name; otherwise: sort by ctime, newest first.

   .. option:: -S 

      sort by file size, largest first.

   .. option:: -t     

      sort by modification time, newest first

   .. option:: -U     

      do not sort; list entries in directory order.

   .. option:: -v     

      natural sort of (version) numbers within text.

   .. option:: -X     

      sort alphabetically by entry extension.

   .. option:: -x     

      list entries by lines instead of by columns.


**Example**

.. code-block:: sh

   $ ls -l
   -rwxrw-r--    10    root   root 2048    Jan 13 07:11 afile.exe
   ?UUUGGGOOOS   00  UUUUUU GGGGGG ####    ^-- date modified and file name)
   ^ ^  ^  ^ ^    ^      ^      ^    ^
   | |  |  | |    |      |      |    \--- File Size
   | |  |  | |    |      |      \-------- Group Name (for example, Users, Administrators, etc)
   | |  |  | |    |      \--------------- Owner Acct
   | |  |  | |    \---------------------- Link count (what constitutes a "link" here varies)
   | |  |  | \--------------------------- Alternative Access (blank means none defined, anything else varies)
   | \--\--\----------------------------- Read, Write and Special access modes for [U]ser, [G]roup, and [O]thers (everyone else)
   \------------------------------------- File type flag


   # find -type c
   # File is of type *c*:
   #    - b: block (buffered) special
   #    - c: character (unbuffered) special
   #    - d: directory
   #    - p: named pipe (FIFO)
   #    - f: regular file
   #    - l: symbolic link
   #    - s: socket

#. tree - list contents of directories in a tree-like format