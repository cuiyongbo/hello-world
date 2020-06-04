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
