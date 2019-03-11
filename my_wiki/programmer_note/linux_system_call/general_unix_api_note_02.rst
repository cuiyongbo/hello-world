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
