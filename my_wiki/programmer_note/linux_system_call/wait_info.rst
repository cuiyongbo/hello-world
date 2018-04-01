************
wait Mannual
************

**NAME**

   wait, waitpid, waitid - wait for process to change state


**SYNOPSIS**

   .. code-block:: c

      #include <sys/types.h>
      #include <sys/wait.h>

      pid_t wait(int *status);
      pid_t waitpid(pid_t pid, int *status, int options);

      /* This is the glibc and POSIX interface; see NOTES for information on the raw system call. */
      int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);


**DESCRIPTION**

   All of these system calls are used to wait for state changes
   in a child of the calling process, and obtain information about
   the child whose state has changed.  A state change is considered
   to be: the child terminated; the child was stopped by a signal;
   or the child was resumed by a signal. In the case of a terminated
   child, performing a wait allows the system to release the resources
   associated with the child; if a wait is not performed, then the
   terminated child remains in a "zombie" state (see NOTES below).

   If a child has already changed state, then these calls return immediately.
   Otherwise, they block until either a child changes state or a signal handler
   interrupts the call (assuming that system calls are not automatically restarted
   using the ``SA_RESTART`` flag of :manpage:`sigaction(2)`). In the remainder of
   this page, a child whose state has changed and which has not yet been waited upon
   by one of these system calls is termed waitable.

   The call wait(&status) is equivalent to ``waitpid(-1, &status, 0)``;

   The  ``waitpid()``  system  call  suspends execution of the calling
   process until a child specified by *pid* argument has changed state.
   By default, ``waitpid()`` waits only for terminated children, but
   this behavior is modifiable via the *options* argument, as described below.

   The value of pid can be:

      * < -1   meaning wait for any child process whose process group ID is equal to the absolute value of pid.
      * -1     meaning wait for any child process.
      * 0      meaning wait for any child process whose process group ID is equal to that of the calling process.
      * > 0    meaning wait for the child whose process ID is equal to the value of pid.

   The value of *options* is an OR of zero or more of the following
   constants: ``WNOHANG``, ``WUNTRACED``,``WCONTINUED``.


   If status is not NULL, wait() and waitpid() store status information in the int to which it points.
   This integer can be inspected with the following macros::

      WIFEXITED(status)
      WEXITSTATUS(status)
      WIFSIGNALED(status)
      WTERMSIG(status)
      WCOREDUMP(status)
      WIFSTOPPED(status)
      WSTOPSIG(status)
      WIFCONTINUED(status)

   The ``waitid()`` system call provides more precise control over
   which child state changes to wait for.

   The *idtype* and *id* arguments select the child(ren) to wait for, as follows:

      idtype == P_PID
         Wait for the child whose process ID matches id.

      dtype == P_PGID
         Wait for any child whose process group ID matches id.

      idtype == P_ALL
         Wait for any child; id is ignored.

   The child state changes to wait for are specified by ORing one or more of
   the following flags in options: ``WEXITED``, ``WSTOPPED``, ``WCONTINUED``, 
   ``WNOHANG``, ``WNOWAIT``.

   Upon successful return, ``waitid()`` fills in the following fields of
   the ``siginfo_t`` structure pointed to by *infop*:

      si_pid      
         The process ID of the child.

      si_uid      
         The real user ID of the child. (This field is not set on most other implementations.)

      si_signo    
         Always set to ``SIGCHLD``.

      si_status 
         Either the exit status of the child, as given to _exit(2) (or exit(3)),
         or the signal that caused the child to terminate, stop, or continue.
         The si_code field can be used to determine how to interpret this field.

      si_code     
         Set to one of:  ``CLD_EXITED``  (child  called  :manpage:`_exit(2)`);
         ``CLD_KILLED`` (child killed by signal); ``CLD_DUMPED`` (child killed
         by signal, and dumped core); ``CLD_STOPPED`` (child stopped by signal);
         ``CLD_TRAPPED`` (traced child has trapped);
         or ``CLD_CONTINUED`` (child continued by ``SIGCONT``).

   If ``WNOHANG`` was specified in options and there were no children in a waitable state,
   then ``waitid()`` returns 0 immediately and the state of the  ``siginfo_t``  structure 
   pointed to by *infop* is unspecified. To distinguish this case from that where a child
   was in a waitable state, zero out the ``si_pid`` field before the call and check for a
   nonzero value in this field after the call returns.


**RETURN VALUE**

   wait()
      on success, returns the process ID of the terminated child;
      on error, -1 is return.

   waitpid()
      on success, returns the process ID of the child whose state has changed;
      if ``WNOHANG`` was specified and one or more child(ren) specified by pid exist,
      but have not yet changed state, then 0 is returned. On error, -1 is return.

   waitid()
      returns 0 on success or if ``WNOHANG`` was specified and no child(ren) specified
      by id has yet changed state; on error, -1 is return.

   Each of these calls sets ``errno`` to an appropriate value in the case of an error.


**ERRORS**

   ECHILD
     (for ``wait()``) The calling process does not have any unwaited-for children.

   ECHILD 
      (for ``waitpid()`` or ``waitid()``) The process specified by *pid* (``waitpid()``)
      or *idtype* and *id* (``waitid()``) does not exist or is not a child of the calling process. 
      (This can happen or one's own child if the action for ``SIGCHLD`` is set to ``SIG_IGN``. )

   EINTR
      ``WNOHANG`` was not set and an unblocked signal or a ``SIGCHLD`` was caught;
      see :manpage:`signal(7)`.

   EINVAL
      The options argument was invalid.


**NOTES**
       
   A child that terminates, but has not been waited for becomes a "zombie".  The kernel maintains a minimal set of information about the  zombie  process  (PID,  termination  status,
   resource  usage  information) in order to allow the parent to later perform a wait to obtain information about the child.  As long as a zombie is not removed from the system via a
   wait, it will consume a slot in the kernel process table, and if this table fills, it will not be possible to create further processes.  If a parent process terminates,  then  its
   "zombie" children (if any) are adopted by init(8), which automatically performs a wait to remove the zombies.

   POSIX.1-2001  specifies  that  if  the disposition of SIGCHLD is set to SIG_IGN or the SA_NOCLDWAIT flag is set for SIGCHLD (see sigaction(2)), then children that terminate do not
   become zombies and a call to wait() or waitpid() will block until all children have terminated, and then fail with errno set to ECHILD.  (The  original  POSIX  standard  left  the
   behavior of setting SIGCHLD to SIG_IGN unspecified.  Note that even though the default disposition of SIGCHLD is "ignore", explicitly setting the disposition to SIG_IGN results in
   different treatment of zombie process children.)

   Linux 2.6 conforms to the POSIX requirements.  However, Linux 2.4 (and earlier) does not: if a wait() or waitpid() call is made while SIGCHLD is being ignored,  the  call  behaves
   just as though SIGCHLD were not being ignored, that is, the call blocks until the next child terminates and then returns the process ID and status of that child.


**EXAMPLE**

   The  following program demonstrates the use of :manpage:`fork(2)` and ``waitpid()``. 
   The program creates a child process.  If no command-line argument is supplied to the program,
   then the child suspends its execution using :manpage:`pause(2)`, to allow the user to send
   signals to the child. Otherwise, if a command-line argument is supplied, then the child
   exits immediately, using the integer supplied on the command line as the exit status. 
   The parent process executes a loop that monitors the child using ``waitpid()``, and
   uses the ``W*()`` macros described above to analyze the wait status value.

   The following shell session demonstrates the use of the program::

      $ ./a.out &
      Child PID is 32360
      [1] 32359
      $ kill -STOP 32360
      stopped by signal 19
      $ kill -CONT 32360
      continued
      $ kill -TERM 32360
      killed by signal 15
      [1]+  Done                    ./a.out

   Program source::

      #include <sys/wait.h>
      #include <stdlib.h>
      #include <unistd.h>
      #include <stdio.h>

      int main(int argc, char *argv[])
      {
         pid_t cpid = fork();
         if (cpid == -1)
         {
           perror("fork");
           exit(EXIT_FAILURE);
         }

         if (cpid == 0) 
         { /* Code executed by child */
            printf("Child PID is %ld\n", (long) getpid());
            if (argc == 1)
               pause(); /* Wait for signals */
            _exit(atoi(argv[1]));
         } 
         else 
         { /* Code executed by parent */
            int status;
            do 
            {
               pid_t w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
               if (w == -1) {
                   perror("waitpid");
                   exit(EXIT_FAILURE);
               }

               if (WIFEXITED(status)) {
                  printf("exited, status=%d\n", WEXITSTATUS(status));
               } else if (WIFSIGNALED(status)) {
                  printf("killed by signal %d\n", WTERMSIG(status));
               } else if (WIFSTOPPED(status)) {
                  printf("stopped by signal %d\n", WSTOPSIG(status));
               } else if (WIFCONTINUED(status)) {
                  printf("continued\n");
               }
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));

            exit(EXIT_SUCCESS);
         }
      }

