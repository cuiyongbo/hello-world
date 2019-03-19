***********************
File inspection command
***********************

#. head - display first lines of a file


    SYNOPSIS: `head [-n count | -c bytes] [file ...]`

    This filter displays the first count lines or bytes of each of the specified files,
    or of the standard input if no files are specified. If count is omitted it defaults to 10.

    options are similar to `tail` command's options. 


#. tail - display the last part of a file


    SYNOPSIS: `tail [-F | -f | -r] [-q] [-b number | -c number | -n number] [file ...]`

    The tail utility displays the contents of file or, by default, its standard input,
    to the standard output.

    The display begins at a byte, line or 512-byte block location in the input.
    Numbers having a leading plus ('+') sign are relative to the beginning of the input,
    for example, ``-c +2`` starts the display at the second byte of the input. 
    Numbers having a leading minus ('-') sign or no explicit sign are relative to the end of the input,
    for example, ``-n 2`` displays the last two lines of the input. 
    The default starting location is ``-n 10``, or the last 10 lines of the input.

    ===========  ===============================================================================
    Option       Description                                                                    
    ===========  ===============================================================================
    -b number    The location is *number* 512-byte blocks.                                      
    -c number    The location is *number* bytes.                                                
    -n number    The location is number lines.                                                  
    -q           Suppresses printing of headers when multiple files are being examined.         
    -r           The ``-r`` option causes the input to be displayed in reverse order, by line.  
    ===========  ===============================================================================


#. wc -- word, line, character, and byte count

    SYNOPSIS: `wc [-clmw] [file ...]`

    The :command:`wc` utility displays the number of lines, words, and bytes
    contained in each input file, or standard input (if no file is specified)
    to the standard output. A line is defined as a string of characters delimited
    by a <newline> character. Characters beyond the final <newline> character will
    not be included in the line count.

    A word is defined as a string of characters delimited by white space characters.
    White space characters are the set of characters for which the :manpage:`iswspace(3)`
    function returns ``true``.  If more than one input file is specified, a line of
    cumulative counts for all the files is displayed on a separate line after
    the output for the last file.

    ========  ==========
    option    meaning   
    ========  ==========
    -c        in bytes  
    -l        in line   
    -w        in words  
    ========  ==========

#. less - opposite of more

    * ``ng``: Jump to line number n. Default is the start of the file.

    * ``nG``: Jump to line number n. Default is the end of the file.

    ========  =========================
    option    meaning                  
    ========  =========================
    -n        Suppresses line numbers  
    -N        Show line numbers        
    ========  =========================