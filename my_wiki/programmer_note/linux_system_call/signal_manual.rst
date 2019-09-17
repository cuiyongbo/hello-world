******************
Unix signal Manual
******************

.. note::

    Signals are **software interrupts**.

    Signals provide a way of handling **asynchronous** events.

    We need to define some of the terms used throughout our discussion of signals.
    First, a signal is **generated** for a process when the event that causes the
    signal occurs. The event could be a hardware exception (e.g., divided by 0),
    a software condition (e.g., an alarm timer expiring), a terminal-generated signal,
    or a call to the kill function. When the signal is generated, the kernel usually
    sets a flag of some form in the process table. We say that a signal is **delivered**
    to a process when the action for a signal is taken. During the time between
    the generation of a signal and its delivery, the signal is said to be **pending.**

====  ===========  ===================  ============================================
No    Name         Default Action       Description
====  ===========  ===================  ============================================
1     SIGHUP       terminate process    terminal line hangup
2     SIGINT       terminate process    interrupt program
3     SIGQUIT      create core image    quit program
4     SIGILL       create core image    illegal instruction
5     SIGTRAP      create core image    trace trap
6     SIGABRT      create core image    abort program (formerly SIGIOT)
7     SIGEMT       create core image    emulate instruction executed
8     SIGFPE       create core image    floating-point exception
9     SIGKILL      terminate process    kill program (cannot be caught or ignored)
10    SIGBUS       create core image    bus error
11    SIGSEGV      create core image    segmentation violation
12    SIGSYS       create core image    non-existent system call invoked
13    SIGPIPE      terminate process    write on a pipe with no reader
14    SIGALRM      terminate process    real-time timer expired
15    SIGTERM      terminate process    software termination signal
16    SIGURG       discard signal       urgent condition present on socket
17    SIGSTOP      stop process         stop (cannot be caught or ignored)
18    SIGTSTP      stop process         stop signal generated from keyboard
19    SIGCONT      discard signal       continue after stop
20    SIGCHLD      discard signal       child status has changed
21    SIGTTIN      stop process         background read attempted from control
22    SIGTTOU      stop process         background write attempted to control
23    SIGIO        discard signal       I/O is possible on a descriptor
24    SIGXCPU      terminate process    cpu time limit exceeded
25    SIGXFSZ      terminate process    file size limit exceeded
26    SIGVTALRM    terminate process    virtual time alarm
27    SIGPROF      terminate process    profiling timer alarm
28    SIGWINCH     discard signal       Window size change
29    SIGINFO      discard signal       status request from keyboard
30    SIGUSR1      terminate process    User defined signal 1
31    SIGUSR2      terminate process    User defined signal 2
====  ===========  ===================  ============================================

#. signal -- simplified software signal facilities

    .. code-block:: c
        :caption: SYNOPSIS

        #include <signal.h>
        void (*signal(int sig, void (*func)(int)))(int);
        // or in the equivalent but easier to read typedef'd version:
        typedef void (*sig_t) (int);
        sig_t signal(int sig, sig_t func);

    This ``signal()`` facility is a simplified interface to the more
    general :manpage:`sigaction(2)` facility.

    Signals allow the manipulation of a process from outside its domain, as well as
    allowing the process to manipulate itself or its children. There are two general
    types of signals: those that cause termination of a process and those that do not.
    Signals which cause termination of a program might result
    from an irrecoverable error or might be the result of a user at a terminal typing
    the interrupt character. Signals are used when a process is stopped because it
    wishes to access its control terminal while in the background.
    Signals are optionally generated when a process resumes after being stopped, when
    the status of child processes changes, or when input is ready at the control terminal.
    **Note that SIGKILL and SIGSTOP signals can neither be caught nor ignored.**

    The *sig* argument specifies which signal was received.
    The operation (a.k.a. **signal disposition**) is determined by *func*::

        SIG_DFL --  set the default action of the signal to occur.
        SIG_IGN -- ignore the signal
        handler -- user-define operation

    For some system calls, if a signal is caught while the call is executing and the
    call is prematurely terminated, the call is automatically restarted. Any handler
    installed with :manpage:`signal(3)` will have the ``SA_RESTART`` flag set,
    meaning that any restartable system call will not return on receipt of a signal.
    The affected system calls include :manpage:`read(2)`, :manpage:`write(2)`,
    :manpage:`sendto(2)`, :manpage:`recvfrom(2)`, :manpage:`sendmsg(2)`, and
    :manpage:`recvmsg(2)` on a communications channel or a low speed device and
    during a :manpage:`ioctl(2)` or :manpage:`wait(2)`.  However, calls that
    have already committed are not restarted, but instead return a partial
    success (for example, a short read count). These semantics could be
    changed with :manpage:`siginterrupt(3)`.

    When a process which has installed signal handlers forks, the child process
    inherits the signals. All caught signals may be reset to their default action
    by a call to the :manpage:`execve(2)` function; ignored signals remain ignored.

    If a process explicitly specifies ``SIG_IGN`` as the action for the signal ``SIGCHLD``,
    the system will not create zombie processes when children of the calling process exit.
    As a consequence, the system will discard the exit status from the child processes.
    If the calling process subsequently issues a call to **wait(2)** or equivalent,
    it will block until all of the calling process's children terminate, and then
    return a value of ``-1`` with *errno* set to ``ECHILD``.

    The previous action is returned on a successful call.
    Otherwise, ``SIG_ERR`` is returned and the global
    variable *errno* is set to indicate the error.

#. sigaction - examine and change a signal action

    .. code-block:: c

        #include <signal.h>
        int sigaction(int signum,
            const struct sigaction *act,
            struct sigaction *oldact);

    The  ``sigaction()`` system call is used to change the action taken by
    a process on receipt of a specific signal.

    *signum* specifies the signal and can be any valid signal except **SIGKILL** and **SIGSTOP.**

    If *act* is non-NULL, the new action for signal *signum* is installed from act.
    If *oldact* is non-NULL, the previous action is saved in *oldact*.

    The sigaction structure is defined as something like::

        struct sigaction
        {
           void     (*sa_handler)(int);
           void     (*sa_sigaction)(int, siginfo_t *, void *);
           sigset_t   sa_mask;
           int        sa_flags;
           void     (*sa_restorer)(void);
        };

    On some architectures a union is involved: don't assign to both *sa_handler*
    and *sa_sigaction*. The *sa_restorer* element is obsolete and **should not be used.**

    *sa_handler* specifies the action to be associated with *signum*
    and it may take values as specified in **signal(2)**.
    If ``SA_SIGINFO`` is specified in *sa_flags*, then *sa_sigaction*
    specifies the signal-handling function for *signum*.

   ``sa_mask`` specifies a mask of signals which should be blocked during execution of the signal handler. Any signal that is blocked cannot be delivered
   to a process. In addition, the signal
   which triggered the handler will be blocked, unless the ``SA_NODEFER`` flag
   is used.

    *sa_flags* specifies a set of flags which modify the behavior of the signal.
    It is formed by the bitwise OR of zero or more of the following:

        SA_NOCLDSTOP
        This flag is meaningful only when establishing a handler for ``SIGCHLD``.
        Don't receive notification when child processes stop (i.e., when they receive
        one of ``SIGSTOP``, ``SIGTSTP``, ``SIGTTIN``, or ``SIGTTOU``)
        or resume (i.e., they receive ``SIGCONT``)

        SA_NOCLDWAIT (since Linux 2.6)
        Don't transform children into zombies when they terminate.
        This flag is meaningful only when establishing a handler for ``SIGCHLD``,
        or when setting that signal's disposition to ``SIG_DFL``.

        SA_NODEFER
        Do not prevent the signal from being received from within
        its own signal handler. This flag is meaningful only when
        establishing a signal handler. ``SA_NOMASK`` is an obsolete,
        nonstandard synonym for this flag.

        SA_ONSTACK
        Call the signal handler on an alternate signal stack
        provided by :manpage:`sigaltstack(2)`. If an alternate
        stack is not available, the default stack will be used.
        This flag is meaningful only when establishing a signal handler.

        SA_RESETHAND
        Restore the signal action to the default upon entry to the
        signal handler. This flag is meaningful only when establishing
        a signal handler. ``SA_ONESHOT`` is an obsolete, nonstandard
        synonym for this flag.

        SA_RESTART
        Provide behavior compatible with BSD signal semantics by
        making certain system calls restartable across signals.
        This flag is meaningful only when establishing a signal
        handler.

        SA_SIGINFO (since Linux 2.2)
        The signal handler takes three arguments, not one. In this
        case, *sa_sigaction* should be set instead of *sa_handler*.
        This flag is meaningful only when establishing a signal handler.


    ``sigaction()`` returns ``0`` on success; on error, ``-1`` is returned,
    and *errno* is set to indicate the error.


#. POSIX signal set operations

    .. code-block:: c

        #include <signal.h>
        int sigemptyset(sigset_t *set);
        int sigfillset(sigset_t *set);
        int sigaddset(sigset_t *set, int signum);
        int sigdelset(sigset_t *set, int signum);
        int sigismember(const sigset_t *set, int signum);

    ``sigemptyset()`` initializes the signal set given by set to empty,
    with all signals excluded from the set.

    ``sigfillset()`` initializes set to full, including all signals.

    ``sigaddset()`` and ``sigdelset()`` add and delete respectively signal signum from set.

    ``sigismember()`` tests whether signum is a member of set.

    Objects of type ``sigset_t`` must be initialized by a call to either
    ``sigemptyset()`` or ``sigfillset()`` before being passed to the functions
    ``sigaddset()``, ``sigdelset()`` and ``sigismember()`` or the additional glibc
    functions described below (``sigisemptyset()``, ``sigandset()``, and ``sigorset()``).
    The results are undefined if this is not done.


    ``sigemptyset()``, ``sigfillset()``, ``sigaddset()``, and ``sigdelset()``
    return ``0`` on success and ``-1`` on error.
    ``sigismember()`` returns ``1`` if signum is a member of set,
    ``0`` if signum is not a member, and ``-1`` on error.
    On error, these functions set *errno* to indicate the cause.


#. sigprocmask - examine and change blocked signals

    .. code-block:: c

        #include <signal.h>
        int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);

    *sigprocmask()* is used to fetch and/or change the signal mask of the calling thread.
    The signal mask is the set of signals whose delivery is currently blocked for the caller.

    The behavior of the call is dependent on the value of *how*, as follows::

        SIG_BLOCK
        The set of blocked signals is the union of the current set
        and the set argument.

        SIG_UNBLOCK
        The signals in set are removed from the current set of blocked signals.
        It is permissible to attempt to unblock a signal which is not blocked.

        SIG_SETMASK
        The set of blocked signals is set to the argument set.

    If *oldset* is non-NULL, the previous signal mask is stored in *oldset*.

    If *set* is NULL, then the signal mask is unchanged, but the current signal mask
    is nevertheless returned in *oldset* if it is not NULL.

    The use of *sigprocmask()* is unspecified in a multithreaded process; see *pthread_sigmask(3)*.

    *sigprocmask()* returns 0 on success and -1 on error.
    In the event of an error, *errno* is set to indicate the cause.

    **It is not possible to block SIGKILL or SIGSTOP.** Attempts to do so are silently ignored.

    Each of the threads in a process has its own signal mask.

    A child created via **fork(2)** inherits a copy of its parent's signal mask;
    the signal mask is preserved across execve(2).

    If *SIGBUS*, *SIGFPE*, *SIGILL*, or *SIGSEGV* are generated while they are blocked,
    the result is undefined, unless the signal was generated by kill(2), sigqueue(3), or raise(3).

#. sigsuspend -- atomically release blocked signals and wait for interrupt

    .. code-block:: c

        #include <signal.h>
        int sigsuspend(const sigset_t *sigmask);

    ``sigsuspend()`` temporarily changes the blocked signal mask to the set to which
    *sigmask* points, and then waits for a signal to arrive; **on return the previous set
    of masked signals is restored.** The signal mask set is usually empty to indicate
    that all signals are to be unblocked for the duration of the call.

    In normal usage, a signal is blocked using :manpage:`sigprocmask(2)` to begin
    a critical section, variables modified on the occurrence of the signal are examined
    to determine that there is no work to be done, and the process pauses awaiting work
    by using ``sigsuspend()`` with the previous mask returned by *sigprocmask*.

    The ``sigsuspend()`` function always terminates by being interrupted,
    returning ``-1`` with *errno* set to ``EINTR``.

#. sigpending - examine pending signals

    .. code-block:: c

        #include <signal.h>
        int sigpending(sigset_t *set);

    ``sigpending()`` returns the set of signals that are pending for
    delivery to the calling thread (i.e., the signals which have been
    raised while blocked). The mask of pending signals is returned in *set.*

    **sigpending()** returns 0 on success and -1 on error.
    In the event of an error, *errno* is set to indicate the cause.

    If a signal is both blocked and has a disposition of "ignored",
    it is not added to the mask of pending signals when generated.

    The set of signals that is pending for a thread is the union
    of the set of signals that is pending for that thread and
    the set of signals that is pending for the process as a whole.

#. strsignal - return string describing signal

    .. code-block:: c

        #include <string.h>
        char *strsignal(int sig);
        extern const char * const sys_siglist[];

    The *strsignal()* function returns a string describing the signal number passed in the argument *sig*.
    The string can be used only until the next call to *strsignal().*

    The array *sys_siglist* holds the signal description strings indexed by signal number.
    The *strsignal()* function should be used if possible instead of this array.

    The *strsignal()* function returns the appropriate description string,
    or an unknown signal message if the signal number is invalid.
    On some systems (but not on Linux), NULL may instead be returned
    for an invalid signal number.

    See also `psignal(3)` for similar APIs.
