*****************
exit system calls
*****************

#. atexit - register a function to be called at normal process termination

    Declaration: ``int atexit(void (*function)(void));``

    The atexit() function registers the given function to be called at normal process
    termination, either via exit(3) or via return from the program's main(). Functions
    so registered are called in the reverse order of their registration; no arguments are
    passed. The same function may be registered multiple times: it is called once for each
    registration.

    When a child process is created via fork(2), it inherits copies of its parent's registrations.
    Upon a successful call to one of the exec(3) functions, all registrations are removed.

#. exit - cause normal process termination

    .. code-block:: c

        #include <stdlib.h>
        void exit(int status);

    The ``exit()`` function causes normal process termination and the value of ``status & 0377`` is returned to the parent.


#. _exit, _Exit - terminate the calling process

    .. code-block:: c

        #include <stdlib.h>
        #include <unistd.h>

        void _exit(int status);
        void _Exit(int status);

    The function ``_exit()`` terminates the calling process "immediately". Any open file descriptors
    belonging to the process are closed. Any children of the process are inherited by init(1),
    The process's parent is sent a SIGCHLD signal.

.. note::

    After calling ``exit(3)``, All open ``stdio(3)`` streams are flushed and closed.
    Files created by ``tmpfile(3)`` are removed.

    ``_exit()`` is like ``exit(3)``, but does not call any functions registered with
    ``atexit(3)`` or ``on_exit(3)``. Open ``stdio(3)`` streams are not flushed.
