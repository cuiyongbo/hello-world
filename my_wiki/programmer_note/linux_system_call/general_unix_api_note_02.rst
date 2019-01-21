*******************
General Unix API 02
*******************

.. contents::
   :local:

getpid, getppid -- get parent or calling process identification
===============================================================

**DESCRIPTION**

   .. code-block:: c

      #include <unistd.h>

      pid_t getpid(void);
      pid_t getppid(void);

   ``getpid()`` returns the process ID of the calling process. 
   The ID is guaranteed to be unique and is useful for
   constructing temporary file names.

   ``getppid()`` returns the process ID of the parent
   of the calling process.

**ERRORS**

   The ``getpid()`` and ``getppid()`` functions are always successful,
   and no return value is reserved to indicate an error.

gettid - get thread identification
==================================

**DESCRIPTION**

   .. code-block:: c

      #include <sys/types.h>
      pid_t gettid(void);

      // Note: There is no glibc wrapper for this system call; see NOTES.

   **gettid()** returns the caller's thread ID (TID).  In a single-threaded process, 
   the thread ID is equal to the process ID (PID, as returned by **getpid(2)**).  
   In a multithreaded process, all threads have the same PID, but each one has a 
   unique TID.  For further details, see the discussion of CLONE_THREAD in clone(2).

**NOTES**

   * Glibc does not provide a wrapper for this system call; call it using **syscall(2)**.

   * The thread ID returned by this call is not the same thing as a POSIX thread ID 
     (as returned by **pthread_self(3)**).

   .. code-block:: c

      #ifdef SYS_gettid
      printf("thread PID: %ld\n", (long)syscall(SYS_gettid));
      #else
      #error "SYS_gettid unavailable on this system"
      #endif

   The PID column in top / htop, the SPID in ps for a thread refers to this TID.

geteuid, getuid -- get user identification
==========================================

**DESCRIPTION**

   .. code-block:: c

      #include <unistd.h>
      #include <sys/types.h>
      uid_t geteuid(void);
      uid_t getuid(void);


   The ``getuid()`` function returns the real user ID of the calling process.  
   The ``geteuid()`` function returns the effective user ID of the calling process.

   The real user ID is that of the user who has invoked the program. 
   As the effective user ID gives the process additional permissions 
   during execution of **set-user-ID** mode processes, ``getuid()`` 
   is used to determine the **real-user-id** of the calling process.

**ERRORS**

   The ``getuid()`` and ``geteuid()`` functions are always successful, 
   and no return value is reserved to indicate an error.


getegid, getgid -- get group process identification
===================================================

**DESCRIPTION**

   .. code-block:: c

      #include <unistd.h>
      #include <sys/types.h>
      gid_t getegid(void);
      gid_t getgid(void);
      
   The ``getgid()`` function returns the real group ID of the calling process, 
   ``getegid()`` returns the effective group ID of the calling process.

   The real group ID is specified at login time.

   The real group ID is the group of the user who invoked the program.  
   As the effective group ID gives the process additional permissions 
   during the execution of **set-group-ID** mode processes, 
   ``getgid()`` is used to determine the **real-user-id** (still real-user-id??)
   of the calling process.

**ERRORS**
     
   The ``getgid()`` and ``getegid()`` functions are always successful; 
   no return value is reserved to indicate an error.


getpgid, getpgrp -- get process group
=====================================

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS
        
         #include <unistd.h>
         pid_t getpgrp(void);
         pid_t getpgid(pid_t pid);
   
   The process group of the current process is returned by *getpgrp().*  
   The process group of the process identified by *pid* is returned by *getpgid().*  
   If *pid* is zero, *getpgid()* returns the process group of the current process.
   
   Process groups are used for distribution of signals, and by terminals 
   to arbitrate requests for their input: processes that have the same 
   process group as the terminal are foreground and may read, 
   while others will block with a signal if they attempt to read.

**RETURN VALUES**

   The **getpgrp()** call always succeeds.  
   Upon successful completion, the **getpgid()** call 
   returns the process group of the specified process; 
   otherwise, it returns a value of -1 and sets errno to 
   indicate the error.


gethostname, sethostname -- get/set name of current host
========================================================

**DESCRIPTION**

   .. code-block:: c

      #include <unistd.h>
      int gethostname(char *name, size_t namelen);
      int sethostname(const char *name, int namelen);

   The ``gethostname()`` function returns the standard host name for the current processor,
   as previously set by ``sethostname()``.  The *namelen* argument specifies the size of the
   *name* array.  The returned *name* is null-terminated, unless insufficient space is provided.

   The ``sethostname()`` function sets the name of the host machine to be *name*, which has
   length *namelen*. This call is restricted to the super-user and is normally used only
   when the system is bootstrapped.

   Host names are limited in length to {``sysconf(_SC_HOST_NAME_MAX)``} characters, not
   including the trailing null, currently 255.

**RETURN VALUES**

   Upon successful completion, the value ``0`` is returned; otherwise the value ``-1`` is
   returned and the global variable ``errno`` is set to indicate the error.


sleep functions
===============

**DESCRIPTION**
   
   .. code-block:: c

      /*
         suspend thread execution for an interval 
         measured in nanoseconds/seconds/microseconds
      */
      #include <time.h>
      int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);

      #include <unistd.h>
      unsigned int sleep(unsigned int seconds);
      int usleep(useconds_t microseconds); 

   The ``nanosleep()`` function causes the calling thread to sleep for the amount of
   time specified in *rqtp* (the actual time slept may be longer, due to system 
   latencies and possible limitations in the timer resolution of the hardware).  An
   unmasked signal will cause ``nanosleep()`` to terminate the sleep early, regardless
   of the ``SA_RESTART`` value on the interrupting signal.

   The ``sleep()`` function suspends execution of the calling thread until either
   *seconds* seconds have elapsed or a signal is delivered to the thread and its
   action is to invoke a signal-catching function or to terminate the thread or
   process. System activity may lengthen the sleep by an indeterminate amount.

   This function is implemented using :manpage:`nanosleep(2)` by pausing for *seconds* 
   seconds or until a signal occurs.  Consequently, in this implementation, 
   sleeping has no effect on the state of process timers, and there is no 
   special handling for ``SIGALRM``.

   .. note::

      The ``usleep()`` function is obsolescent. 
      Use :manpage:`nanosleep(2)` instead.

**RETURN VALUES**

   If ``nanosleep()`` returns because the requested time has elapsed,
   the value returned will be zero.

   If ``nanosleep()`` returns due to the delivery of a signal, the value
   returned will be the ``-1``, and the global variable **errno** will be
   set to indicate the interruption. If *rmtp* is non-NULL, the ``timespec``
   structure it references is updated to contain the unslept amount
   (the request time minus the time actually slept).

   If the **sleep()** function returns because the requested time has elapsed, the value
   returned will be zero.  If the ``sleep()`` function returns due to the delivery of a
   signal, the value returned will be the unslept amount in seconds.


pause -- stop until signal
==========================

**DESCRIPTION**

   .. code-block:: c

      #include <unistd.h>
      int pause(void);

   **Note** that ``pause()`` is made obsolete by :manpage:`sigsuspend(2).`

   The ``pause()`` function forces a process to pause until a signal is received from
   either the :manpage:`kill(2)` function or an interval timer. (See :manpage:`setitimer(2)`.)  
   Upon termination of a signal handler started during a ``pause()``, the ``pause()`` call will
   return.

**RETURN VALUES**

   Always returns -1. and set errno to ``EINTR.``


abort - cause abnormal process termination
==========================================

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS
   
         #include <stdlib.h>
         void abort(void);

   The abort() first unblocks the SIGABRT signal, and then raises that signal for the calling process.  
   This results in the abnormal termination of the process unless the SIGABRT signal is caught 
   and the signal handler does not return (see longjmp(3)).

   If the abort() function causes process termination, all open streams are closed and flushed.
   If the SIGABRT signal is ignored, or caught by a handler that returns, the abort() function 
   will still terminate the process. It does this by restoring the default disposition for SIGABRT 
   and then raising the signal for a second time.

**Example**

   .. code-block:: c

      #include <stdio.h>
      #include <stdlib.h>
      #include <string.h>
      #include <unistd.h>
      #include <signal.h>
      
      int main()
      {
          signal(SIGABRT, SIG_IGN);
      
          abort();
      
          return 0;
      }

   // Ubuntu output: Aborted (core dumped)


alarm -- set signal timer alarm
===============================

**DESCRIPTION**

   .. code-block:: c

      #include <unistd.h>
      unsigned alarm(unsigned seconds);

   **Note** that This interface is made obsolete by setitimer(2).

   The ``alarm()`` function sets a timer to deliver the signal ``SIGALRM`` 
   to the calling process after the specified number of *seconds.*  If
   an alarm has already been set with ``alarm()`` but has not been delivered, 
   another call to ``alarm()`` will supersede the prior call. The request ``alarm(0)`` 
   voids the current alarm and the signal ``SIGALRM`` will not be delivered.

   Due to **setitimer(2)** restriction the maximum number of *seconds* allowed is 100000000.

**RETURN VALUES**

   The return value of ``alarm()`` is the amount of time left on the timer from 
   a previous call to ``alarm().`` If no alarm is currently set, the return value is 0.


kill -- send signal to a process
================================

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS

      #include <signal.h>
      
      int kill(pid_t pid, int sig);
      
      /*killpg -- send signal to a process group*/
      int killpg(pid_t pgrp, int sig);

   The ``kill()`` function sends the signal specified by *sig* to *pid*, a process
   or a group of processes.  Typically, *Sig* will be one of the signals specified
   in :manpage:`sigaction(2)`.  A value of ``0``, however, will cause error checking
   to be performed (with no signal being sent). This can be used to check the validity of *pid*.

   For a process to have permission to send a signal to a process designated by *pid*,
   the real or effective user ID of the receiving process must match that of the
   sending process or the user must have appropriate privileges (such as given by a
   set-user-ID program or the user is the super-user).  A single exception is the
   signal ``SIGCONT``, which may always be sent to any descendant of the current
   process.

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
      excluding system processes and the process sending the signal. If
      the user is not the super user, the signal is sent to all processes with
      the same uid as the user, excluding the process sending the signal. No
      error is returned if any process could be signaled.

**RETURN VALUES**

   Upon successful completion, a value of ``0`` is returned. Otherwise,
   a value of ``-1`` is returned and ``errno`` is set to indicate the error.

.. note::

   A process needs permission to send a signal to another process. 
   The superuser can send a signal to any process. For other users, 
   the basic rule is that the real or effective user ID of the sender 
   has to equal the real or effective user ID of the receiver.

raise - send a signal to the caller
===================================

**DESCRIPTION**
   
   .. code-block:: c
      :caption: SYNOPSIS
         
      #include <signal.h>
      int raise(int sig);
   
   The *raise()* function sends a signal to the calling process or thread.  
   In a single-threaded program it is equivalent to ``kill(getpid(), sig);``
   In a multithreaded program it is equivalent to ``pthread_kill(pthread_self(), sig);``
   
   If the signal causes a handler to be called, *raise()* will 
   return only after the signal handler has returned.
   
**RETURN VALUE**

   *raise()* returns 0 on success, and nonzero for failure.
