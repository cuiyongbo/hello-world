*************
select Manual
*************

**NAME**

    select, pselect, FD_CLR, FD_ISSET, FD_SET, FD_ZERO - synchronous I/O multiplexing

**SYNOPSIS**

    .. code-block:: c

        #include <sys/select.h>
        #include <sys/time.h>
        #include <sys/types.h>
        #include <unistd.h>

        void FD_ZERO(fd_set *set);
        void FD_CLR(int fd, fd_set *set);
        void FD_SET(int fd, fd_set *set);
        int  FD_ISSET(int fd, fd_set *set);

        int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
                                                                 struct timeval *timeout);
        int pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
                                   const struct timespec *timeout, const sigset_t *sigmask);

        struct timeval {
           long    tv_sec;      /* seconds */
           long    tv_usec;     /* microseconds */
        };

        struct timespec {
            long    tv_sec;         /* seconds */
            long    tv_nsec;        /* nanoseconds */
        };

**DESCRIPTION**

    *select()* and *pselect()* allow a program to monitor multiple file descriptors,
    waiting until one or more of the file descriptors become "ready" for some class
    of I/O operation (e.g., input possible). A file descriptor is considered ready
    if it is possible to perform the corresponding I/O operation (e.g., read(2))
    without blocking.

    Three independent sets of file descriptors are watched. Those listed in *readfds* will be watched to
    see if characters become available for reading (more precisely, to see if a read will not block; in
    particular, a file descriptor is also ready on end-of-file), those in *writefds* will be watched to
    see if a write will not block, and those in *exceptfds* will be watched for exceptions. On exit, the
    sets are modified in place to indicate which file descriptors actually changed status. Each of the
    three file descriptor sets may be specified as NULL if no file descriptors are to be watched for the
    corresponding class of events.

    **nfds is the highest-numbered file descriptor in any of the three sets, plus 1.**
    i.e., the descriptors from 0 through *nfds-1* in the descriptor sets are examined.
    (Example: If you have set two file descriptors "4" and "17", nfds should not be "2",
    but rather "17 + 1" or "18".)

    The *timeout* argument specifies the interval that *select()* should block waiting for a file descriptor to
    become ready. This interval will be rounded up to the system clock granularity, and kernel scheduling delays
    mean that the blocking interval may overrun by a small amount. If both fields of the *timeval* structure are zero,
    then *select()* returns immediately. (This is useful for polling.) If *timeout* is NULL (no timeout), *select()*
    can block indefinitely.

    *sigmask* is a pointer to a signal mask (see sigprocmask(2)); if it is not NULL, then *pselect()* first replaces
    the current signal mask by the one pointed to by *sigmask*, then on return restores the original signal mask.

    Other than the difference in the precision of the *timeout* argument, the following *pselect()* call::

        ready = pselect(nfds, &readfds, &writefds, &exceptfds, timeout, &sigmask);

    is equivalent to atomically executing the following calls::

        sigset_t origmask;
        pthread_sigmask(SIG_SETMASK, &sigmask, &origmask);
        ready = select(nfds, &readfds, &writefds, &exceptfds, timeout);
        pthread_sigmask(SIG_SETMASK, &origmask, NULL);

    The reason that *pselect()* is needed is that if one wants to wait for either a signal or for
    a file descriptor to become ready, then an atomic test is needed to prevent race conditions.

    Suppose the signal handler sets a global flag and returns. Then a test of this global flag
    followed by a call of *select()* could hang indefinitely if the signal arrived just after the
    test but just before the call. By contrast, *pselect()* allows one to first block signals,
    handle the signals that have come in, then call *pselect()* with the desired *sigmask*,
    avoiding the race.

    Some code calls *select()* with all three sets empty, *nfds* zero, and a non-NULL *timeout*
    as a fairly portable way to sleep with subsecond precision.

**RETURN VALUE**

    On success, *select()* and *pselect()* return the number of file descriptors contained in the
    three returned descriptor sets (that is, the total number of bits that are set in *readfds*,
    *writefds*, *exceptfds*) which may be zero if the *timeout* expires before anything interesting
    happens. On error, -1 is returned, and *errno* is set appropriately; the sets and timeout become
    undefined, so do not rely on their contents after an error.

**NOTES**

    An *fd_set* is a fixed size buffer. Executing *FD_CLR()* or *FD_SET()* with a value of *fd*
    that is negative or is equal to or larger than *FD_SETSIZE* will result in undefined behavior.
    Moreover, POSIX requires fd to be a valid file descriptor.

    In multithreaded applications, If a file descriptor being monitored by *select()* is closed in
    another thread, the result is unspecified.
