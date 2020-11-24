************
grep Manual
************

**DESCRIPTION**

   .. code-block:: sh

      grep [OPTIONS] PATTERN [FILE...]
      grep [OPTIONS] [-e PATTERN | -f FILE] [FILE...]

   grep searches the named input *FILEs* (or standard input if no files are
   named, or if a single hyphen-minus (-) is given as file name) for lines
   containing a match to the given *PATTERN*. By default, grep prints the
   matching lines.


**OPTIONS**

   #. Matcher Selection

      .. option:: -E, --extended-regexp

        Interpret *PATTERN* as an extended regular expression 

    .. option:: -P, --perl-regexp
        
        Interpret PATTERN as a Perl regular expression.

      .. option:: -F, --fixed-strings

         Interpret *PATTERN* as a list of fixed strings (rather than
         regular expressions), separated by newlines, any of which is to
         be matched. (-F is specified by POSIX.)

      .. option:: -G, --basic-regexp

         Interpret *PATTERN* as a basic regular expression (BRE, see
         below). This is the default.

   #. Matching Control

      .. option:: -i, --ignore-case

         Ignore case distinctions in both the *PATTERN* and the input files.

      .. option:: -v, --invert-match

         Invert the sense of matching, to select non-matching lines.

      .. option:: -x, --line-regexp

         Select only those matches that exactly match the whole line.
         This option has the same effect as anchoring the expression with
         ``^`` and ``$``.

   #. General Output Control

      .. option:: -c, --count

         Suppress normal output; instead print a count of matching lines
         for each input file. With the ``-v, --invert-match`` option,
         count non-matching lines.

      .. option:: --color[=WHEN], --colour[=WHEN]

         Surround the matched (non-empty) strings, matching lines, context
         lines, file names, line numbers, byte offsets, and separators
         (for fields and groups of context lines) with escape sequences to
         display them in color on the terminal. *WHEN* is ``never``, ``always``,
         or ``auto``.

      .. option:: -L, --files-without-match

         Suppress normal output; instead print the name of each input
         file from which no output would normally have been printed. The
         scanning will stop on the first match.

      .. option:: -l, --files-with-matches

         Suppress normal output; instead print the name of each input file
         from which output would normally have been printed. The scanning
         will stop on the first match. (:option:`-l`  is specified by POSIX.)

      .. option:: -m NUM, --max-count=NUM

         Stop reading a file after *NUM* matching lines.

      .. option:: -o, --only-matching

         Print only the matched (non-empty) parts of a matching line,
         with each such part on a separate output line.

      .. option:: -q, --quiet, --silent

         Quiet; do not write anything to standard output. Exit immediately with
         zero status if any match is found, even if an error was detected.

      .. option:: -s, --no-messages

         Suppress error messages about nonexistent or unreadable files.

   #. Output Line Prefix Control

      .. option:: -b, --byte-offset

         Print the 0-based byte offset within the input file before each
         line of output. If :option:`-o, --only-matching` is specified,
         print the offset of the matching part itself.

      .. option:: -H, --with-filename

         Print the file name for each match. This is the default when
         there is more than one file to search.

      .. option:: -h, --no-filename

         Suppress the prefixing of file names on output. This is the
         default when there is only one file (or only standard input) to
         search.

      .. option:: -n, --line-number

         Prefix each line of output with the 1-based line number within
         its input file. (:option:`-n` is specified by POSIX.)

      .. option:: -Z, --null

         Output a zero byte (the ASCII NUL character) instead of the
         character that normally follows a file name. For example,
         ``grep -lZ`` outputs a zero byte after each file name instead
         of the usual newline. This option makes the output unambiguous,
         even in the presence of file names containing unusual characters
         like newlines. This option can be used with commands like
         ``find -print0``, ``perl -0``, ``sort -z``, and ``xargs -0``
         to process arbitrary file names, even those that contain
         newline characters.

   #. Context Line Control

      .. option:: -A NUM, --after-context=NUM
      .. option:: -B NUM, --before-context=NUM

         Print *NUM* lines of trailing context before/after matching lines.

      .. option:: -C NUM, -NUM, --context=NUM

         Print *NUM* lines of output context.

   #. File and Directory Selection

      .. option:: -a, --text

         Process a binary file as if it were text; this is equivalent to
         the ``--binary-files=text`` option.

      .. option:: --binary-files=TYPE

         If the first few bytes of a file indicate that the file contains
         binary data, assume that the file is of type TYPE. By default,
         *TYPE* is binary, and :command:`grep` normally outputs either
         a one-line message saying that a binary file matches, or no message if
         there is no match. If *TYPE* is ``without-match``, :command:`grep` assumes
         that a binary file does not match; this is equivalent to the :option:`-I`
         option.

      .. option:: -I

         Process a binary file as if it did not contain matching data;
         this is equivalent to the `--binary-files=without-match` option.

      .. option:: -r, --recursive

         Read all files under each directory, recursively, following
         symbolic links only if they are on the command line.

      .. option:: -R, --dereference-recursive

         Read all files under each directory, recursively. Follow all
         symbolic links, unlike :option:`-r`.

      .. option:: --exclude=GLOB

         Skip files whose base name matches *GLOB* (using wildcard
         matching). A file-name glob can use ``*``, ``?``, and ``[...]``
         as wildcards, and ``\`` to quote a wildcard or backslash
         character literally.

      .. option:: --include=GLOB

         Search only files whose base name matches *GLOB* (using wildcard
         matching as described under :option:`--exclude`).

      .. option:: --exclude-from=FILE

         Skip files whose base name matches any of the file-name globs
         read from *FILE* (using wildcard matching as described under
         :option:`--exclude`).

      .. option:: --exclude-dir=DIR

         Exclude directories matching the pattern *DIR* from
         recursive searches.

**REGULAR EXPRESSIONS**

   A regular expression is a pattern that describes a set of strings.
   Regular expressions are constructed analogously to arithmetic expressions,
   by using various operators to combine smaller expressions.

   grep understands three different versions of regular expression syntax:
   “basic” (BRE), “extended” (ERE) and “perl” (PRCE). In GNU grep, there
   is no difference in available functionality between basic and extended
   syntaxes. In other implementations, basic regular expressions are less
   powerful. The following description applies to extended regular
   expressions; differences for basic regular expressions are summarized
   afterwards.

   The fundamental building blocks are the regular expressions that match
   a single character. Most characters, including all letters and digits,
   are regular expressions that match themselves. Any meta-character with
   special meaning may be quoted by preceding it with a backslash.

   The period ``.`` matches any single character.

   #. Character Classes and Bracket Expressions

      A bracket expression is a list of characters enclosed by ``[`` and ``]``.
      It matches any single character in that list; if the first character of
      the list is the caret ``^`` then it matches any character not in the list.
      For example, the regular expression ``[0123456789]`` matches any single
      digit.

      Within a bracket expression, a range expression consists of two characters
      separated by a hyphen (``-``).  For example, in the default C locale, ``[a-d]``
      is equivalent to ``[abcd]``.

      Finally, certain named classes of characters are predefined within bracket
      expressions, as follows. Their names are self explanatory, and
      they are [:alnum:], [:alpha:], [:cntrl:], [:digit:], [:graph:],
      [:lower:], [:print:], [:punct:], [:space:], [:upper:], and [:xdigit:].
      For example, [[:alnum:]] means ``[0-9A-Za-z]``. (Note that the brackets in
      these class names are part of the symbolic names, and must be included
      in addition to the brackets delimiting the bracket expression.)

      .. note::

         Most meta-characters lose their special meaning inside bracket expressions.
         To include a literal ``]`` place it first in the list. Similarly, to include
         a literal ``^`` place it anywhere but first. Finally, to include a
         literal ``-`` place it last.

   #. Anchoring

      The caret ``^`` and the dollar sign ``$`` are meta-characters that
      respectively match the empty string at the beginning and end of a line.

   #. The Backslash Character and Special Expressions

      The symbols ``\<`` and ``\>`` respectively match the empty string at the
      beginning and end of a word. The symbol ``\b`` matches the empty string at
      the edge of a word, and ``\B`` matches the empty string provided it's not
      at the edge of a word. The symbol ``\w`` is a synonym for ``[_[:alnum:]]``
      and ``\W`` is a synonym for ``[^_[:alnum:]]``. for more information refer
      to **re_format(7)** [macOS], or **regex(7)** [ubntu].

   #. Repetition

      A regular expression may be followed by one of several repetition
      operators::

         ?      The preceding item is optional and matched at most once.
         *      The preceding item will be matched zero or more times.
         +      The preceding item will be matched one or more times.
         {n}    The preceding item is matched exactly n times.
         {n,}   The preceding item is matched n or more times.
         {,m}   The preceding item is matched at most m times. This is a GNU
                extension.
         {n,m}  The preceding item is matched at least n times, but not more
                than m times.

   #. Alternation

      Two regular expressions may be joined by the infix operator (|); the
      resulting regular expression matches any string matching either
      alternate expression.


**EXAMPLE**

.. code-block:: sh

    $ grep -o -E ".{100,100}801857" event.json  # output the matched and the 100 characters before it.

    $ grep -E ^-?33615290, SWID.txt
    33615290,140
    -33615290,140

    $ find . -name "*.c" -exec grep -Hn exponential \{\} \;
    ./fig_16_11.c:11:    /*Try to connect with exponential backoff*/ 

    $ wc -l fig_03_05.c
          17 fig_03_05.c

    # non-empty line count
    $ grep -Hcve "^\s*$" fig_03_05.c
    fig_03_05.c:14
    14

    $ find /run/shm/ | grep -E "cokeMap|pepsiMap"
    /run/shm/cokeMap
    /run/shm/pepsiMap

    $ grep -A 5 -B 2 20181111142200_6802_43145_56_458_2 formatted_event.json
    ....

    $ grep -C 2 20181111142200_6802_43145_56_458_2 formatted_event.json
    ....

    $ grep 20181111142200_6802_43145_56_458_2 event.json -o
    20181111142200_6802_43145_56_458_2

    $ grep 20181111142200_6802_43145_56_458_2 event.json -ob
    61391497:20181111142200_6802_43145_56_458_2

    $ find shell_command/ -name "*.rst" -exec grep -l grep {} \;
    shell_command//awk_manual.rst
    shell_command//binary_executable_inspectors.rst
    ...

    $ find shell_command/ -name "*.rst" -exec grep -L grep {} \;
    shell_command//addr2line_note.rst
    shell_command//binary_file_viewer.rst
    ...

    $ grep -rIH label .
    ./nan_test.py:plt.xlabel('time (s)')
    ./nan_test.py:plt.ylabel('voltage (mV)')

    # in ubuntu, you don't need add '-r' option when searching a directory
    $ grep "uint8" /usr/include/*.h
    /usr/include/stdint.h:typedef unsigned char     uint8_t;

#. search file with specified pattern

    .. code-block:: sh
    
        $ grep -rHn ' tr ' --include=*.rst
        shell_command/tr_manual.rst:9:      tr [OPTION]... SET1 [SET2]
        $ grep -r '^[ \t\v]ADD_STRATEGY' --include=*.h  --include=*.cpp .  | cut -d, -f2 > strategy_list

#. find file(s) ending with certain patterns

    .. code-block:: sh

        $ find xxx-prog -type f | grep -E "*\.(md|py)"
        xxx-prog/make.py
        xxx-prog/README.md
        xxx-prog/src/changelog/changelog.py

#. Count the number of lines in a project

    .. code-block:: sh

        $ find xxx-prog/ -type f | grep -E "*\.(h|cpp|md|rst|py)" | xargs wc -l
        ...
        2898 total

        $ find xxx-prog/ -name "*.cpp" -exec wc -l \{\} \; | awk '{s+=$1}END{print s}'
        1272

#. Calculate average: ``grep -Eo " tm=\w+" search_ac.log | awk 'BEGIN{FS="="}{sum+=$2}END{print sum/NR}'``

#. Greedy match vs nongreedy match

    .. code-block:: sh

        $ grep -Po '<.*>' <<< '<title>hello world</title>'
        <title>My webpage title</title>
        $ grep -Po '<.*?>' <<< '<title>hello world</title>'
        <title>
        </title>

#. `Lookaround <http://www.regular-expressions.info/lookaround.html>`_

    - positive lookhead ``(?=regex)``
    - negative lookhead ``(?!regex)``
    - positive lookbehind ``(?<=text)``
    - negative lookbehind ``(?<!text)``

    .. code-block:: sh

        # not work in some linux release
        $ echo 'yongbo <yongbo.shan@mm.com>, junqing <junqing.li@mm.com>' |grep -oP '\b[^<]+(?=>)'
        $ echo 'yongbo <yongbo.shan@mm.com>, junqing <junqing.li@mm.com>' | grep -oP '(?<=<)[^>]+\b'
        $ echo 'yongbo <yongbo.shan@mm.com>, junqing <junqing.li@mm.com>' |grep -oP '(?<=<).*?(?=>)' 
        $ echo "this is (test.com)" | grep -Po '(?<=\().*(?=\))'
