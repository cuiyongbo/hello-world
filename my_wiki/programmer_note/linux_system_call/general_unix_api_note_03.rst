*******************
General Unix API 03
*******************

#. getrlimit, setrlimit, prlimit - get/set resource limits
   
    .. code-block:: c

        #include <sys/time.h>
        #include <sys/resource.h>

        int getrlimit(int resource, struct rlimit *rlim);
        int setrlimit(int resource, const struct rlimit *rlim);
        int prlimit(pid_t pid, int resource, 
                    const struct rlimit *new_limit,
                    struct rlimit *old_limit);

    The `getrlimit()` and `setrlimit()` system calls get and set resource limits respectively.  
    Each resource has an associated soft and hard limit, as defined by the rlimit structure::

        struct rlimit 
        {
            rlim_t rlim_cur;  /* Soft limit */
            rlim_t rlim_max;  /* Hard limit (ceiling for rlim_cur) */
        };

    The soft limit is the value that the kernel enforces for the  corresponding  resource.   
    The hard limit acts as a ceiling for the soft limit: an unprivileged process may set only 
    its soft limit to a value in the range from 0 up to the hard limit, and (irreversibly) lower 
    its hard limit. A privileged process (under Linux: one with the `CAP_SYS_RESOURCE` capability) 
    may make arbitrary changes to either limit value.

    The value `RLIM_INFINITY` denotes no limit on a resource.

    The Linux-specific `prlimit()` system call combines and extends the functionality of `setrlimit()` 
    and `getrlimit()`.  It can be used to both set and get the resource limits of an arbitrary process.

    The `pid` argument specifies the ID of the process on which the call is to operate. If pid is 0,
    then the call applies to the calling process. To set or get the resources of a process other than
    itself, the caller must have the `CAP_SYS_RESOURCE` capability, or the real, effective, and saved
    set user IDs of the target process must match the real user ID of the caller and the real, effective, 
    and saved set group IDs of the target process must match the real group ID of the caller.

    The `resource` argument can be one of (only list frequently used options)::

        RLIMIT_AS
        The maximum size of the process's virtual memory (address space) in bytes.  

        RLIMIT_CORE
        Maximum size of a core file (see `core(5)`). When 0 no core dump files are created.  
        When nonzero, larger dumps are truncated to this size.

        RLIMIT_CPU
        CPU time limit in seconds. When the process reaches the soft limit, 
        it is sent a `SIGXCPU` signal. 

        RLIMIT_DATA
        The maximum size of the process's data segment (initialized data, uninitialized data, and
        heap). This limit affects calls to `brk(2)` and `sbrk(2)`, which fail with the error `ENOMEM`
        upon encountering the soft limit of this resource.

        RLIMIT_FSIZE
        The maximum size of files that the process may create. 
        Attempts to extend a file beyond this limit result in delivery of a `SIGXFSZ` signal.

        RLIMIT_RSS
        Specifies the limit (in bytes) of the process's resident set (the number of 
        virtual pages resident in RAM).

        RLIMIT_STACK
        The maximum size of the process stack, in bytes. 
        Upon reaching this limit, a SIGSEGV signal is generated.
    
    On success, these system calls return 0. On error, -1 is returned, and  `errno` is set appropriately.

#. pause -- stop until signal

    .. code-block:: c

        #include <unistd.h>
        int pause(void);

    **Note** that ``pause()`` is made obsolete by :manpage:`sigsuspend(2).`

    The ``pause()`` function forces a process to pause until a signal is received from
    either the :manpage:`kill(2)` function or an interval timer. (See :manpage:`setitimer(2)`.)  
    Upon termination of a signal handler started during a ``pause()``, the ``pause()`` call will return.

    Always returns -1. and set errno to ``EINTR.``

#. abort - cause abnormal process termination

    .. code-block:: c
   
        #include <stdlib.h>
        void abort(void);

    The `abort()` first unblocks the `SIGABRT` signal, and then raises that signal for the calling process.  
    This results in the abnormal termination of the process unless the `SIGABRT` signal is caught 
    and the signal handler does not return (see `longjmp(3)`).

    If the `abort()` function causes process termination, all open streams are closed and flushed.
    If the `SIGABRT` signal is ignored, or caught by a handler that returns, the `abort()` function 
    will still terminate the process. It does this by restoring the default disposition for SIGABRT 
    and then raising the signal for a second time.

#. alarm -- set signal timer alarm

    .. code-block:: c

        #include <unistd.h>
        unsigned alarm(unsigned seconds);

    **Note** that This interface is made obsolete by `setitimer(2)`.

    The ``alarm()`` function sets a timer to deliver the signal ``SIGALRM`` 
    to the calling process after the specified number of `seconds`.  
    If an alarm has already been set with ``alarm()`` but has not been delivered, 
    another call to ``alarm()`` will supersede the prior call. The request ``alarm(0)`` 
    voids the current alarm and the signal ``SIGALRM`` will not be delivered.

    Due to **setitimer(2)** restriction the maximum number of *seconds* allowed is 100000000.

    The return value of ``alarm()`` is the amount of time left on the timer from 
    a previous call to ``alarm().`` If no alarm is currently set, the return value is 0.

#. kill -- send signal to a process

    .. code-block:: c

        #include <signal.h>
      
        int kill(pid_t pid, int sig);
      
        /*killpg -- send signal to a process group*/
        int killpg(pid_t pgrp, int sig);

    The ``kill()`` function sends the signal specified by *sig* to *pid*, a process
    or a group of processes. Typically, *Sig* will be one of the signals specified
    in :manpage:`sigaction(2)`.  A value of ``0``, however, will cause error checking
    to be performed (with no signal being sent). This can be used to check the validity of *pid*.

    For a process to have permission to send a signal to a process designated by *pid*,
    the real or effective user ID of the receiving process must match that of the
    sending process or the user must have appropriate privileges (such as given by a
    set-user-ID program or the user is the super-user). A single exception is the
    signal ``SIGCONT``, which may always be sent to any descendant of the current process.

    If *pid* is greater than zero:
        *Sig* is sent to the process whose ID is equal to *pid*.

    If *pid* is zero:
        *Sig* is sent to all processes whose group ID is equal to the process
        group ID of the sender, and for which the process has permission;
        this is a variant of :manpage:`killpg(2)`.

    if *pid* is negative:
        *Sig* is sent to all processes whose process group ID equals the absolute
        value of *pid* and for which the sender has permission to send the signal.

    If *pid* is -1:
        If the user has super-user privileges, the signal is sent to all processes 
        excluding system processes and the process sending the signal. 
        If the user is not the super user, the signal is sent to all processes with
        the same uid as the user, excluding the process sending the signal. 
        No error is returned if any process could be signaled.

    Upon successful completion, a value of ``0`` is returned. Otherwise,
    a value of ``-1`` is returned and ``errno`` is set to indicate the error.

    .. note::

        A process needs permission to send a signal to another process. 
        The superuser can send a signal to any process. For other users, 
        the basic rule is that the real or effective user ID of the sender 
        has to equal the real or effective user ID of the receiver.

#. raise - send a signal to the caller

    .. code-block:: c
         
        #include <signal.h>
        int raise(int sig);
   
    The *raise()* function sends a signal to the calling process or thread.  
    In a single-threaded program it is equivalent to ``kill(getpid(), sig);``
    In a multithreaded program it is equivalent to ``pthread_kill(pthread_self(), sig);``
   
    If the signal causes a handler to be called, *raise()* will 
    return only after the signal handler has returned.
   
    *raise()* returns 0 on success, and nonzero for failure.
