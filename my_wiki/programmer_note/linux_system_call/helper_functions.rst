***********************
Miscellaneous Functions
***********************

.. contents::
   :local:


getpid & getppid
================

**NAME**

   getpid, getppid -- get parent or calling process identification


**SYNOPSIS**

   .. code-block:: c

      #include <unistd.h>

      pid_t getpid(void);
      pid_t getppid(void);


**DESCRIPTION**

   ``getpid()`` returns the process ID of the calling process. 
   The ID is guaranteed to be unique and is useful for
   constructing temporary file names.

   ``getppid()`` returns the process ID of the parent
   of the calling process.


**ERRORS**

   The ``getpid()`` and ``getppid()`` functions are always successful,
   and no return value is reserved to indicate an error.


**SEE ALSO**

   :manpage:`gethostid(2)`, :manpage:`compat(5)`


gethostname & sethostname
=========================

**NAME**

   gethostname, sethostname -- get/set name of current host


**SYNOPSIS**

   .. code-block:: c

      #include <unistd.h>
      int gethostname(char *name, size_t namelen);
      int sethostname(const char *name, int namelen);


**DESCRIPTION**

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


**ERRORS**

   [EFAULT]           
      The *name* or *namelen* argument gave an invalid address.

   [ENAMETOOLONG]     
      The current host name is longer than namelen.  (For ``gethostname()`` only.)

   [EPERM]            
      The caller tried to set the host name and was not the super-user.


**SEE ALSO**

   :manpage:`sysconf(3)`, :manpage:`sysctl(3)`


nanosleep
=========

**NAME**
   
   nanosleep -- suspend thread execution for an interval measured in nanoseconds


**SYNOPSIS**
   
   .. code-block:: c

      #include <time.h>
      int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);


**DESCRIPTION**

   The ``nanosleep()`` function causes the calling thread to sleep for the amount of
   time specified in *rqtp* (the actual time slept may be longer, due to system 
   latencies and possible limitations in the timer resolution of the hardware).  An
   unmasked signal will cause ``nanosleep()`` to terminate the sleep early, regardless
   of the ``SA_RESTART`` value on the interrupting signal.


**RETURN VALUES**

   If ``nanosleep()`` returns because the requested time has elapsed,
   the value returned will be zero.

   If ``nanosleep()`` returns due to the delivery of a signal, the value
   returned will be the ``-1``, and the global variable **errno** will be
   set to indicate the interruption. If *rmtp* is non-NULL, the ``timespec``
   structure it references is updated to contain the unslept amount
   (the request time minus the time actually slept).


**ERRORS**

   The ``nanosleep()`` call fails if:

   [EINTR]            

      ``nanosleep()`` was interrupted by the delivery of a signal.

   [EINVAL]           

      *rqtp* specified a nanosecond value less than zero or greater
      than or equal to 1000 million.


**SEE ALSO**

   :manpage:`sigsuspend(2)`, :manpage:`sleep(3)`


sleep & usleep
==============

**NAME**

   sleep -- suspend thread execution for an interval measured in seconds

   usleep -- suspend thread execution for an interval measured in microseconds


**SYNOPSIS**

   .. code-block:: c

      #include <unistd.h>
   
      unsigned int sleep(unsigned int seconds);
      int usleep(useconds_t microseconds); 


**DESCRIPTION**

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

   If the **sleep()** function returns because the requested time has elapsed, the value
   returned will be zero.  If the ``sleep()`` function returns due to the delivery of a
   signal, the value returned will be the unslept amount (the requested time minus
   the time actually slept) in seconds.


**SEE ALSO**

   :manpage:`nanosleep(2)`, :manpage:`usleep(3)`


pause
=====

**NAME**
     
   pause -- stop until signal

**SYNOPSIS**

   .. code-block:: c

      #include <unistd.h>
      int pause(void);

**DESCRIPTION**

   The ``pause()`` function forces a process to pause until a signal is received from
   either the :manpage:`kill(2)` function or an interval timer. (See :manpage:`setitimer(2)`.)  
   Upon termination of a signal handler started during a ``pause()``, the ``pause()`` call will
   return.

**RETURN VALUES**

   Always returns -1.

**ERRORS**

   The ``pause()`` function always returns:

   EINTR
      The call was interrupted.

**SEE ALSO**

   :manpage:`kill(2)`, :manpage:`select(2)`, :manpage:`sigsuspend(2)`

.. note::

   ``pause()`` is made obsolete by :manpage:`sigsuspend(2)`.


kill
====

**NAME**

   kill -- send signal to a process


**SYNOPSIS**

   .. code-block:: c

      #include <signal.h>
      
      int kill(pid_t pid, int sig);


**DESCRIPTION**

   The ``kill()`` function sends the signal specified by *sig* to *pid*, a process
   or a group of processes.  Typically, *Sig* will be one of the signals specified
   in :manpage:`sigaction(2)`.  A value of ``0``, however, will cause error checking
   to be performed (with no signal being sent). This can be used to check
   the validity of *pid*.

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

   If *pid* is -1:
      If the user has super-user privileges, the signal is sent to all pro-
      cesses excluding system processes and the process sending the signal.  If
      the user is not the super user, the signal is sent to all processes with
      the same uid as the user, excluding the process sending the signal. No
      error is returned if any process could be signaled.


**RETURN VALUES**

   Upon successful completion, a value of ``0`` is returned. Otherwise,
   a value of ``-1`` is returned and ``errno`` is set to indicate the error.


**ERRORS**

   ``kill()`` will fail and no signal will be sent if:

   [EINVAL]
      *Sig* is not a valid, supported signal number.

   [EPERM]
      The sending process is not the super-user and its effective
      user id does not match the effective user-id of the receiving
      process.  When signaling a process group, this error is returned
      if any members of the group could not be signaled.

   [ESRCH]
      No process or process group can be found corresponding to that
      specified by pid.

   [ESRCH]
      The process id was given as ``0``, but the sending process does
      not have a process group.


**SEE ALSO**
   :manpage:`getpgrp(2)`, :manpage:`getpid(2)`,
   :manpage:`killpg(2)`, :manpage:`sigaction(2)`.


killpg
======

**NAME**

   killpg -- send signal to a process group


**SYNOPSIS**

   .. code-block:: c
   
      #include <signal.h>
   
      int killpg(pid_t pgrp, int sig);


**DESCRIPTION**

   The ``killpg()`` function sends the signal *sig* to the process group *pgrp*.
   See :manpage:`sigaction(2)` for a list of signals. If *pgrp* is ``0``,
   ``killpg()`` sends the signal to the sending process's process group.

   The sending process and members of the process group must have the same effective
   user ID, or the sender must be the super-user.  As a single special case the con-
   tinue signal ``SIGCONT`` may be sent to any process with the same session ID
   as the caller.


**RETURN VALUES**
   
   The ``killpg()`` function returns the value ``0`` if successful;
   otherwise the value ``-1`` is returned and the global variable
   ``errno`` is set to indicate the error.


**ERRORS**

   The ``killpg()`` function will fail and no signal will be sent if:

     [EINVAL]
         The *sig* argument is not a valid signal number.

     [EPERM]
         The sending process is not the super-user and one or more of
         the target processes has an effective user ID different from
         that of the sending process.

     [ESRCH]
         No process can be found in the process group
         specified by *pgrp*.

     [ESRCH]
         The process group was given as ``0`` but the sending process
         does not have a process group.


**SEE ALSO**

   :manpage:`getpgrp(2)`, :manpage:`kill(2)`,
   :manpage:`sigaction(2)`, :manpage:`compat(5)`.