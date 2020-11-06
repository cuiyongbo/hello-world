Gdb Usage 03
============

#. set parent/child to debug

    .. code-block:: sh

        (gdb) help set follow-fork-mode
        Set debugger response to a program call of fork or vfork.
        A fork or vfork creates a new process.  follow-fork-mode can be:
          parent  - the original process is debugged after a fork
          child   - the new process is debugged after a fork
        The unfollowed process will continue to run.
        By default, the debugger will follow the parent process.

#. value of type '***' requires 49346472 bytes, which is more than max-value-size

    .. code-block:: sh

        (gdb) help set max-value-size
        Set maximum sized value gdb will load from the inferior.
        Use this to control the maximum size, in bytes, of a value that gdb
        will load from the inferior.  Setting this value to 'unlimited'
        disables checking.
        Setting this does not invalidate already allocated values, it only
        prevents future values, larger than this size, from being allocated.
        (gdb) set max-value-size unlimited

#. print core infomation to file

    .. code-block:: sh

        (gdb) help set loggin
        Set logging options

        List of set logging subcommands:

        set logging file -- Set the current logfile
        set logging off -- Disable logging
        set logging on -- Enable logging
        set logging overwrite -- Set whether logging overwrites or appends to the log file
        set logging redirect -- Set the logging output mode

        Type "help set logging" followed by set logging subcommand name for full documentation.
        Type "apropos word" to search for commands related to "word".
        Command name abbreviations are allowed if unambiguous.

        (gdb) help thread apply 
        Apply a command to a list of threads.

        List of thread apply subcommands:

        thread apply all -- Apply a command to all threads

        Type "help thread apply" followed by thread apply subcommand name for full documentation.
        Type "apropos word" to search for commands related to "word".
        Command name abbreviations are allowed if unambiguous.
        (gdb) help thread apply all bt # output thread stack and heap information 