File Encoding FAQ
=================

#. related commands

    .. code-block:: sh

        $ iconv --help
        Usage: iconv [OPTION...] [FILE...]
        Convert encoding of given files from one encoding to another.

         Input/Output format specification:
          -f, --from-code=NAME       encoding of original text
          -t, --to-code=NAME         encoding for output

         Information:
          -l, --list                 list all known coded character sets

         Output control:
          -c                         omit invalid characters from output
          -o, --output=FILE          output file
          -s, --silent               suppress warnings
              --verbose              print progress information

          -?, --help                 Give this help list
              --usage                Give a short usage message
          -V, --version              Print program version

#. how to see file encoding

    .. code-block:: sh
        
        # solution one
        $ file -i perf.log.2020071618 
        perf.log.2020071618: text/plain; charset=iso-8859-1

        # solution two: vi file_name, and run `:set fileencoding`

#. List known charsets on your OS

    .. code-block:: sh

        $ iconv -l
        The following list contain all the coded character sets known.  This does
        not necessarily mean that all combinations of these names can be used for
        the FROM and TO command line parameters.  One coded character set can be
        listed with several different names (aliases).

          437, 500, 500V1, 850, 851, 852, 855, 856, 857, 860, 861, 862, 863, 864, 865,
          866, 866NAV, 869, 874, 904, 1026, 1046, 1047, 8859_1, 8859_2, 8859_3, 8859_4,
          8859_5, 8859_6, 8859_7, 8859_8, 8859_9, 10646-1:1993, 10646-1:1993/UCS4,
          ANSI_X3.4-1968, ANSI_X3.4-1986, ANSI_X3.4, ANSI_X3.110-1983, ANSI_X3.110,
          ...

#. How to change file encoding

    .. code-block:: sh

        # solution one: vi file_name, and run `:set fileencoding=encoding`

        # solution two
        $ file -i perf.log.2020071618 
        perf.log.2020071618: text/plain; charset=iso-8859-1
        $ iconv -f iso-8859-1 -t utf-8 -o tt.log perf.log.2020071618
        $ file -i tt.log 
        tt.log: text/plain; charset=utf-8
