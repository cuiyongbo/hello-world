*************
SIGNAL Manual
*************

.. contents::
   :local:

signal -- simplified software signal facilities
===============================================

**DESCRIPTION**

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
   allowing the process to manipulate itself or copies of itself (children). There
   are two general types of signals: those that cause termination of a process and
   those that do not. Signals which cause termination of a program might result
   from an irrecoverable error or might be the result of a user at a terminal typing
   the 'interrupt' character. Signals are used when a process is stopped because it
   wishes to access its control terminal while in the background (see :manpage:`tty(4)`).
   Signals are optionally generated when a process resumes after being stopped, when
   the status of child processes changes, or when input is ready at the control terminal.
   Most signals result in the termination of the process receiving them, if no action is taken;
   some signals instead cause the process receiving them to be stopped, or are simply discarded
   if the process has not requested otherwise. **Except for the SIGKILL and SIGSTOP signals,**
   the ``signal()`` function allows for a signal to be caught, to be ignored, or to generate an interrupt.
   These signals are defined in the file **signal.h:**

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

   The *sig* argument specifies which signal was received. 
   The operation is determined by *func*::

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
   If the calling process subsequently issues a call to :manpage:`wait(2)` or equivalent,
   it will block until all of the calling process's children terminate,
   and then return a value of ``-1`` with *errno* set to ``ECHILD``.


**RETURN VALUES**

   The previous action is returned on a successful call.  
   Otherwise, ``SIG_ERR`` is returned and the global 
   variable *errno* is set to indicate the error.


sigaction - examine and change a signal action
==============================================

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS

      #include <signal.h>
      int sigaction(int signum, 
                     const struct sigaction *act,
                     struct sigaction *oldact);

   The  ``sigaction()``  system call is used to change the action taken by a
   process on receipt of a specific signal.

   *signum* specifies the signal and can be any valid signal except **SIGKILL**
   and **SIGSTOP.**

   If *act* is non-NULL, the new action for signal *signum* is installed  from
   act.  If *oldact* is non-NULL, the previous action is saved in *oldact*.

   The sigaction structure is defined as something like::

      struct sigaction {
         void     (*sa_handler)(int);
         void     (*sa_sigaction)(int, siginfo_t *, void *);
         sigset_t   sa_mask;
         int        sa_flags;
         void     (*sa_restorer)(void);
      };

   On some architectures a union is involved: do not assign to both
   *sa_handler* and *sa_sigaction*.

   The *sa_restorer* element is obsolete and **should not be used.**

   *sa_handler* specifies the action to be associated with *signum* and may be
   ``SIG_DFL`` for the default action, ``SIG_IGN`` to ignore  this  signal, 
   or a pointer to a signal handling function. This function receives the
   signal number as its only argument.

   If ``SA_SIGINFO`` is specified in *sa_flags*, then *sa_sigaction* (instead
   of *sa_handler*) specifies the signal-handling function for *signum*. This
   function receives the signal number as its first argument, a pointer to
   a ``siginfo_t`` as its second argument and a pointer to a ``ucontext_t``
   (cast to ``void *``) as its third argument. (Commonly, the handler function
   doesn't make any use of the third argument. See :manpage:`getcontext(3)` for
   further information about ``ucontext_t``.)

   ``sa_mask`` specifies a mask of signals which should be blocked (i.e.,
   added to the signal mask of the thread in which the signal handler is
   invoked) during execution of the signal handler. In addition, the signal
   which triggered the handler will be blocked, unless the ``SA_NODEFER`` flag
   is used.

   *sa_flags* specifies a set of flags which modify the behavior of the signal.
   It is formed by the bitwise OR of zero or more of the following:

      SA_NOCLDSTOP
         If signum is ``SIGCHLD``, do not receive notification when child
         processes stop (i.e., when they receive one of ``SIGSTOP``,
         ``SIGTSTP``, ``SIGTTIN``, or ``SIGTTOU``) or resume (i.e., they
         receive ``SIGCONT``) (see :manpage:`wait(2)`). This flag is 
         meaningful only when establishing a handler for ``SIGCHLD``.

      SA_NOCLDWAIT (since Linux 2.6)
         If signum is ``SIGCHLD``, do not transform children into zombies
         when they terminate.  See also  :manpage:`waitpid(2)`. This flag is
         meaningful only when establishing a handler for ``SIGCHLD``, or
         when setting that signal's disposition to ``SIG_DFL``.

         If the ``SA_NOCLDWAIT`` flag is set when establishing a handler
         for ``SIGCHLD``, POSIX.1 leaves it unspecified whether a ``SIGCHLD``
         signal is generated when a child process terminates. On Linux, a
         ``SIGCHLD`` signal is generated in this case; on some other
         implementations, it is not.

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

      The ``siginfo_t`` argument to ``sa_sigaction`` is a struct with
      the following elements::

         siginfo_t {
            int      si_signo;    /* Signal number */
            int      si_errno;    /* An errno value */
            int      si_code;     /* Signal code */
            int      si_trapno;   /* Trap number that caused
                                     hardware-generated signal
                                     (unused on most architectures) */
            pid_t    si_pid;      /* Sending process ID */
            uid_t    si_uid;      /* Real user ID of sending process */
            int      si_status;   /* Exit value or signal */
            clock_t  si_utime;    /* User time consumed */
            clock_t  si_stime;    /* System time consumed */
            sigval_t si_value;    /* Signal value */
            int      si_int;      /* POSIX.1b signal */
            void    *si_ptr;      /* POSIX.1b signal */
            int      si_overrun;  /* Timer overrun count; POSIX.1b timers */
            int      si_timerid;  /* Timer ID; POSIX.1b timers */
            void    *si_addr;     /* Memory location which caused fault */
            long     si_band;     /* Band event (was int in
                                     glibc 2.3.2 and earlier) */
            int      si_fd;       /* File descriptor */
            short    si_addr_lsb; /* Least significant bit of address
                                     (since Linux 2.6.32) */
         }

      *si_signo*, *si_errno* and *si_code* are defined for all signals. (*si_errno*
      is generally unused on Linux.)  The rest of the struct may be a union,
      so that one should read only the fields that are meaningful for the
      given signal:

         * Signals sent with kill(2) and sigqueue(3) fill in si_pid and  si_uid.
           In  addition, signals sent with sigqueue(3) fill in si_int and si_ptr
           with  the  values  specified  by  the  sender  of  the  signal;   see
           sigqueue(3) for more details.

         * Signals  sent by POSIX.1b timers (since Linux 2.6) fill in si_overrun
           and si_timerid.  The si_timerid field is an internal ID used  by  the
           kernel  to  identify  the  timer;  it is not the same as the timer ID
           returned by timer_create(2).  The si_overrun field is the timer over‐
           run  count;  this is the same information as is obtained by a call to
           timer_getoverrun(2).  These fields are nonstandard Linux extensions.

         * Signals sent for message queue notification (see the  description  of
           SIGEV_SIGNAL   in  mq_notify(3))  fill  in  si_int/si_ptr,  with  the
           sigev_value supplied to mq_notify(3); si_pid, with the process ID  of
           the  message sender; and si_uid, with the real user ID of the message
           sender.

         * SIGCHLD fills in si_pid, si_uid, si_status, si_utime,  and  si_stime,
           providing  information  about  the  child.   The  si_pid field is the
           process ID of the child; si_uid is the child's  real  user  ID.   The
           si_status  field contains the exit status of the child (if si_code is
           CLD_EXITED), or the signal number that caused the process  to  change
           state.   The  si_utime  and  si_stime contain the user and system CPU
           time used by the child process; these fields do not include the times
           used  by  waited-for children (unlike getrusage(2) and times(2)).  In
           kernels up to 2.6, and since 2.6.27, these fields report CPU time  in
           units  of  sysconf(_SC_CLK_TCK).  In 2.6 kernels before 2.6.27, a bug
           meant that these fields reported time in units of the  (configurable)
           system jiffy (see time(7)).

         * SIGILL, SIGFPE, SIGSEGV, SIGBUS, and SIGTRAP fill in si_addr with the
           address of the fault.  On some architectures, these signals also fill
           in  the  si_trapno  field.   Some  suberrors of SIGBUS, in particular
           BUS_MCEERR_AO and BUS_MCEERR_AR,  also  fill  in  si_addr_lsb.   This
           field indicates the least significant bit of the reported address and
           therefore the extent of the corruption.  For example, if a full  page
           was   corrupted,  si_addr_lsb  contains  log2(sysconf(_SC_PAGESIZE)).
           BUS_MCERR_* and si_addr_lsb are Linux-specific extensions.

         * SIGIO/SIGPOLL (the two names are synonyms on Linux) fills in  si_band
           and  si_fd.  The si_band event is a bit mask containing the same val‐
           ues as are filled in the revents field by poll(2).  The  si_fd  field
           indicates the file descriptor for which the I/O event occurred.

      *si_code* is a value (not  a bit mask) indicating why this signal was
      sent. The following list shows the values which can be placed in *si_code*
      for any signal, along with reason that the signal was generated::

         SI_USER        kill(2)
         SI_KERNEL      Sent by the kernel.
         SI_QUEUE       sigqueue(3)
         SI_TIMER       POSIX timer expired
         SI_MESGQ       POSIX  message  queue  state  changed  (since  Linux
                        2.6.6); see mq_notify(3)
         SI_ASYNCIO     AIO completed
         SI_SIGIO       Queued  SIGIO (only in kernels up to Linux 2.2; from
                        Linux 2.4 onward SIGIO/SIGPOLL fills in  si_code  as
                        described below).
         SI_TKILL       tkill(2) or tgkill(2) (since Linux 2.4.19)

      The following values can be placed in *si_code* for
      a ``SIGILL`` signal::

         ILL_ILLOPC     illegal opcode
         ILL_ILLOPN     illegal operand
         ILL_ILLADR     illegal addressing mode
         ILL_ILLTRP     illegal trap
         ILL_PRVOPC     privileged opcode
         ILL_PRVREG     privileged register
         ILL_COPROC     coprocessor error
         ILL_BADSTK     internal stack error

      The following values can be placed in *si_code* for
      a ``SIGFPE`` signal::

         FPE_INTDIV     integer divide by zero
         FPE_INTOVF     integer overflow
         FPE_FLTDIV     floating-point divide by zero
         FPE_FLTOVF     floating-point overflow
         FPE_FLTUND     floating-point underflow
         FPE_FLTRES     floating-point inexact result
         FPE_FLTINV     floating-point invalid operation
         FPE_FLTSUB     subscript out of range

      The following values can be placed in *si_code* for
      a ``SIGSEGV`` signal::

         SEGV_MAPERR    address not mapped to object
         SEGV_ACCERR    invalid permissions for mapped object

      The following values can be placed in *si_code* for
      a ``SIGBUS`` signal::

         BUS_ADRALN     invalid address alignment
         BUS_ADRERR     nonexistent physical address
         BUS_OBJERR     object-specific hardware error
         BUS_MCEERR_AR (since Linux 2.6.32)
                        Hardware  memory  error consumed on a machine check;
                        action required.
         BUS_MCEERR_AO (since Linux 2.6.32)
                        Hardware memory error detected in  process  but  not
                        consumed; action optional.

      The following values can be placed in *si_code* for
      a ``SIGTRAP`` signal::

         TRAP_BRKPT     process breakpoint
         TRAP_TRACE     process trace trap
         TRAP_BRANCH (since Linux 2.4)
                        process taken branch trap
         TRAP_HWBKPT (since Linux 2.4)
                        hardware breakpoint/watchpoint

      The following values can be placed in *si_code* for
      a ``SIGCHLD`` signal::

         CLD_EXITED     child has exited
         CLD_KILLED     child was killed
         CLD_DUMPED     child terminated abnormally
         CLD_TRAPPED    traced child has trapped
         CLD_STOPPED    child has stopped
         CLD_CONTINUED  stopped child has continued (since Linux 2.6.9)

      The following values can be placed in *si_code* for
      a ``SIGIO/SIGPOLL`` signal::

         POLL_IN        data input available
         POLL_OUT       output buffers available
         POLL_MSG       input message available
         POLL_ERR       I/O error
         POLL_PRI       high priority input available
         POLL_HUP       device disconnected


**RETURN VALUE**

   ``sigaction()`` returns ``0`` on success; on error, ``-1`` is returned,
   and *errno* is set to indicate the error.


POSIX signal set operations
===========================

**SYNOPSIS**

   .. code-block:: c

      #include <signal.h>

      int sigemptyset(sigset_t *set);
      int sigfillset(sigset_t *set);
      int sigaddset(sigset_t *set, int signum);
      int sigdelset(sigset_t *set, int signum);
      int sigismember(const sigset_t *set, int signum);


**DESCRIPTION**

   These functions allow the manipulation of POSIX signal sets.

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


**RETURN VALUE**

   ``sigemptyset()``, ``sigfillset()``, ``sigaddset()``, and ``sigdelset()``
   return ``0`` on success and ``-1`` on error.

   ``sigismember()`` returns ``1`` if signum is a member of set,
   ``0`` if signum is not a member, and ``-1`` on error.
   On error, these functions set *errno* to indicate the cause.


**NOTES**

   If the ``_GNU_SOURCE`` feature test macro is defined, then :file:`signal.h`
   exposes three other functions for manipulating signal sets::

      int sigisemptyset(const sigset_t *set);
      int sigorset(sigset_t *dest, const sigset_t *left,
                    const sigset_t *right);
      int sigandset(sigset_t *dest, const sigset_t *left,
                    const sigset_t *right);

   ``sigisemptyset()`` returns ``1`` if set contains no signals, and ``0`` otherwise.

   ``sigorset()`` places the union of the sets *left* and *right* in *dest*.
   ``sigandset()`` places the intersection of the sets *left* and *right* in *dest*.
   Both functionsreturn ``0`` on  success,  and ``-1`` on failure.

   These functions are nonstandard (a few other systems provide similar functions)
   and their use should be avoided in portable applications.


sigprocmask - examine and change blocked signals
================================================

**SYNOPSIS**

   .. code-block:: c

      #include <signal.h>
      int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);

**DESCRIPTION**

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

   If *oldset* is non-NULL, the previous value of the signal mask is stored in *oldset*.

   If *set* is NULL, then the signal mask is unchanged (i.e., how is ignored), 
   but the current value of the signal mask is nevertheless returned in *oldset* 
   if it is not NULL.

   The use of *sigprocmask()* is unspecified in a multithreaded process; see *pthread_sigmask(3)*.

**RETURN VALUE**

   *sigprocmask()* returns 0 on success and -1 on error.  
   In the event of an error, *errno* is set to indicate the cause.

**NOTES**

   It is not possible to block SIGKILL or SIGSTOP.  Attempts to do so are silently ignored.

   Each of the threads in a process has its own signal mask.

   A child created via **fork(2)** inherits a copy of its parent's signal mask; 
   the signal mask is preserved across execve(2).

   If *SIGBUS*, *SIGFPE*, *SIGILL*, or *SIGSEGV* are generated while they are blocked, 
   the result is undefined, unless the signal was generated by kill(2), sigqueue(3), or raise(3).


sigsuspend -- atomically release blocked signals and wait for interrupt
=======================================================================

**SYNOPSIS**

   .. code-block:: c

      #include <signal.h>
      int sigsuspend(const sigset_t *sigmask);

**DESCRIPTION**

   ``sigsuspend()`` temporarily changes the blocked signal mask to the set to which
   *sigmask* points, and then waits for a signal to arrive; on return the previous set
   of masked signals is restored. The signal mask set is usually empty to indicate
   that all signals are to be unblocked for the duration of the call.

   In normal usage, a signal is blocked using :manpage:`sigprocmask(2)` to begin
   a critical section, variables modified on the occurrence of the signal are examined
   to determine that there is no work to be done, and the process pauses awaiting work
   by using ``sigsuspend()`` with the previous mask returned by *sigprocmask*.

**RETURN VALUES**

   The ``sigsuspend()`` function always terminates by being interrupted,
   returning ``-1`` with *errno* set to ``EINTR``.


strsignal - return string describing signal
===========================================

**SYNOPSIS**

   .. code-block:: c

      #include <string.h>
      char *strsignal(int sig);
      extern const char * const sys_siglist[];

**DESCRIPTION**

   The *strsignal()* function returns a string describing the signal number passed in the argument *sig*.  
   The string can be used only until the next call to *strsignal().*

   The array *sys_siglist* holds the signal description strings indexed by signal number.  
   The *strsignal()* function should be used if possible instead of this array.

**RETURN VALUE**

   The *strsignal()* function returns the appropriate description string, 
   or an unknown signal message if the signal number is invalid.  
   On some systems (but not on Linux), NULL may instead be returned 
   for an invalid signal number.

