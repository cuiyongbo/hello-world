************
diff & patch
************

.. contents::
   :local:

diff - compare files line by line
=================================

**Description**

.. code-block:: none
   :caption: SYNOPSIS

   diff [OPTION]... FILES

FILES are  'FILE1  FILE2' or 'DIR1 DIR2' or 'DIR FILE...' or 'FILE... DIR'.  
If --from-file or --to-file is given, there are no restrictions on FILE(s). 
If a FILE is '-', read standard input. Exit status is 0 if inputs are the same, 
1 if different, 2 if trouble.

.. code-block:: none
   :caption: Hot Options

   -q, --brief
      report only when files differ

   -s, --report-identical-files
      report when two files are the same

   -y, --side-by-side
      output in two columns

   -t, --expand-tabs
      expand tabs to spaces in output

   -T, --initial-tab
      make tabs line up by prepending a tab

   --tabsize=NUM
      tab stops every NUM (default 8) print columns

   --suppress-blank-empty
      suppress space or tab before empty output lines

   -r, --recursive
      recursively compare any subdirectories found

   -N, --new-file
      treat absent files as empty

   --unidirectional-new-file
      treat absent first files as empty

   --ignore-file-name-case
      ignore case when comparing file names

   --no-ignore-file-name-case
      consider case when comparing file names

   -x, --exclude=PAT
      exclude files that match PAT

   -i, --ignore-case
      ignore case differences in file contents

   --strip-trailing-cr
      strip trailing carriage return on input

   --from-file=FILE1
      compare FILE1 to all operands; FILE1 can be a directory

   --to-file=FILE2
      compare all operands to FILE2; FILE2 can be a directory

.. code-block:: sh
   :caption: Examples

   $ cat file1
   apples
   oranges
   kiwis
   carrots
   $ cat file2
   apples
   kiwis
   carrots
   grapefruites

   # diff side by side
   $ diff -y file1 file2
   apples                        apples
   oranges                          <
   kiwis                      kiwis
   carrots                       carrots
                              >  grapefruites

   $ diff ti-diff/ ti-diff-2/
   Only in ti-diff: analysis.log
   Common subdirectories: ti-diff/appdata and ti-diff-2/appdata
   Only in ti-diff: profile.log
   Only in ti-diff-2: profiler
   Common subdirectories: ti-diff/test_data and ti-diff-2/test_data
   Only in ti-diff: ti-update
   Common subdirectories: ti-diff/userdata and ti-diff-2/userdata


patch - apply a diff file to an original
========================================

**Description**

.. code-block:: none
   :caption: SYNOPSIS
      
   patch [options] [originalfile [patchfile]]
   
   # but usually just
   
   patch -pnum <patchfile

patch takes a patch file *patchfile* containing a difference listing 
produced by the diff program and applies those differences to one or 
more original files, producing patched versions. Normally the patched 
versions are put in place of the originals. Backups can be made; 
see the -b or --backup option. The names of the files to be patched 
are usually taken from the patch file, but if there's just one file 
to be patched it can be specified on the command line as *originalfile.*

.. code-block:: none
   :caption: Hot options

   -i patchfile  or  --input=patchfile
      Read the patch from patchfile. 
      If patchfile is -, read from standard input, the default.

   -o outfile  or  --output=outfile
      Send output to outfile instead of patching files in place. 
      Do not use this option if outfile is one of the files to be patched.  
      When outfile is -, send output to standard output, and send any messages 
      that would usually go to standard output to standard error.

   -r rejectfile  or  --reject-file=rejectfile
      Put rejects into rejectfile instead of the default .rej file.  
      When rejectfile is -, discard rejects.

   -R  or  --reverse
      Assume that this patch was created with the old and new files swapped.  
      patch attempts to swap each hunk around before applying it. 
      Rejects come out in the swapped format.
   
   -pnum  or  --strip=num
      Strip the smallest prefix containing num leading slashes from 
      each file name found in the patch file. A sequence of one or 
      more adjacent slashes is counted as a single slash. 
      This controls how file names found in the patch file are treated, 
      in case you keep your files in a different directory than the 
      person who sent out the patch. For example, supposing the file name 
      in the patch file was ``/u/howard/src/blurfl/blurfl.c.``
      setting -p0 gives the entire file name unmodified, -p1 gives
      ``u/howard/src/blurfl/blurfl.c`` without the leading slash, 
      -p4 gives b``lurfl/blurfl.c``. and not specifying -p at all just 
      gives you ``blurfl.c.`` Whatever you end up with is looked for either 
      in the current directory, or the directory specified by the -d option.