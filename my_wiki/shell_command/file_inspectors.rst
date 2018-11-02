***********************
File inspection command
***********************

head Command
============

**NAME**

   head -- display first lines of a file


**SYNOPSIS**

   .. code-block:: sh

      head [-n count | -c bytes] [file ...]


**DESCRIPTION**

   This filter displays the first count lines or bytes of each of the specified files,
   or of the standard input if no files are specified. If count is omitted it defaults to 10.
   If more than a single file is specified, each file is preceded by a header consisting of
   the string "==> XXX <==" where "XXX" is the name of the file.


**OPTIONS**

  .. option:: head -c, --bytes=[-]NUM

      print the first **NUM** bytes of each file;
      with the leading '-', print all but the last **NUM** bytes of each file

  .. option:: -n, --lines=[-]NUM       

      print the first **NUM** lines instead of the first 10;
      with the leading '-', print all but the last **NUM** lines of each file

.. note::

   **NUM** may have a multiplier suffix: b 512, kB 1000, K 1024, MB 1000*1000,
   M 1024*1024, GB 1000*1000*1000, G 1024*1024*1024, and so on for T, P, E, Z, Y.


**EXAMPLE**

   .. code-block:: sh

      cat data | head -c 1K


tail Command
============

**NAME**

   tail -- display the last part of a file


**SYNOPSIS**

   .. code-block:: sh

      tail [-F | -f | -r] [-q] [-b number | -c number | -n number] [file ...]


**DESCRIPTION**

   The tail utility displays the contents of file or, by default, its standard input,
   to the standard output.

   The display begins at a byte, line or 512-byte block location in the input.
   Numbers having a leading plus ('+') sign are relative to the beginning of the input,
   for example, ``-c +2`` starts the display at the second byte of the input. 
   Numbers having a leading minus ('-') sign or no explicit sign are relative to the end of the input,
   for example, ``-n 2`` displays the last two lines of the input. 
   The default starting location is ``-n 10``, or the last 10 lines of the input.

   If more than a single file is specified, each file is preceded by a header consisting of
   the string "==> XXX <==" where XXX is the name of the file unless :option:`-q` flag is specified.


**OPTIONS**

   ===========  ===============================================================================
   Option       Description                                                                    
   ===========  ===============================================================================
   -b number    The location is *number* 512-byte blocks.                                      
   -c number    The location is *number* bytes.                                                
   -n number    The location is number lines.                                                  
   -q           Suppresses printing of headers when multiple files are being examined.         
   -r           The ``-r`` option causes the input to be displayed in reverse order, by line.  
   ===========  ===============================================================================


wc Command
==========

**NAME**

   wc -- word, line, character, and byte count


**SYNOPSIS**

   .. code-block:: sh

      wc [-clmw] [file ...]


**DESCRIPTION**

   The :command:`wc` utility displays the number of lines, words, and bytes
   contained in each input file, or standard input (if no file is specified)
   to the standard output.  A line is defined as a string of characters delimited
   by a <newline> character. Characters beyond the final <newline> character will
   not be included in the line count.

   A word is defined as a string of characters delimited by white space characters.
   White space characters are the set of characters for which the :manpage:`iswspace(3)`
   function returns ``true``.  If more than one input file is specified, a line of
   cumulative counts for all the files is displayed on a separate line after
   the output for the last file.

   When an option is specified, wc only reports the information requested by that option.
   The order of output always takes the form of line, word, byte, and file name.
   The default action is equivalent to specifying the -c, -l and -w options.

   If no files are specified, the standard input is used and no file name is displayed.
   The prompt will accept input until receiving EOF, or [^D] in most environments.


**OPTIONS**

   .. option:: wc -c      

      The number of bytes in each input file is written to the standard output.
      This will cancel out any prior usage of the :option:`-m` option.

   .. option:: -l      

      The number of lines in each input file is written to the standard output.

   .. option:: -m      

      The number of characters in each input file is written to the standard output.
      If the current locale does not support multibyte characters, this is equivalent
      to the :option:`-c` option.  This will cancel out any prior usage of
      the :option:`-c` option.

   .. option:: -w

      The number of words in each input file is written to the standard output.


**EXAMPLES**

   .. code-block:: sh

      # Count the number of characters, words and lines
      # in each of the files *test.c* and *test.cpp* 
      # as well as the totals for both
      $ wc -mlw test.c test.cpp
      70     148    1231 test.c
      29      53     370 test.cpp
      99     201    1601 total
