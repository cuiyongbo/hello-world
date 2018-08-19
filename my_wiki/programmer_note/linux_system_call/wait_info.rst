************
WAIT Mannual
************

**NAME**

   wait, waitpid - wait for process to change state


**SYNOPSIS**

   .. code-block:: c

      #include <sys/types.h>
      #include <sys/wait.h>

      pid_t wait(int *status);
      pid_t waitpid(pid_t pid, int *status, int options);


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

   The call ``wait(&status)`` is equivalent to ``waitpid(-1, &status, 0)``;

   The  ``waitpid()``  system  call  suspends execution of the calling
   process until a child specified by *pid* argument has changed state.
   By default, ``waitpid()`` waits only for terminated children, but
   this behavior is modifiable via the *options* argument, as described below.

   The value of *pid* can be::

      < -1   meaning wait for any child process whose process group ID is equal to the absolute value of pid.
      -1     meaning wait for any child process.
      0      meaning wait for any child process whose process group ID is equal to that of the calling process.
      > 0    meaning wait for the child whose process ID is equal to the value of pid.

   The value of *options* is an OR of zero or more of the following
   constants: ``WNOHANG``, ``WUNTRACED,`` ``WCONTINUED.``

   If *status* is not NULL,* wait()* and *waitpid()* store status information in the integer 
   to which it points. This integer can be inspected with the following macros::

      WIFEXITED(status)
      WEXITSTATUS(status)
      WIFSIGNALED(status)
      WTERMSIG(status)
      WCOREDUMP(status)
      WIFSTOPPED(status)
      WSTOPSIG(status)
      WIFCONTINUED(status)


**RETURN VALUE**

   wait()
      on success, returns the process ID of the terminated child;
      on error, -1 is return.

   waitpid()
      on success, returns the process ID of the child whose state has changed;
      if ``WNOHANG`` was specified and one or more child(ren) specified by pid exist,
      but have not yet changed state, then ``0`` is returned. On error, ``-1`` is return.

   Each of these calls sets ``errno`` to an appropriate value in the case of an error.


**ERRORS**

   ECHILD
     (for ``wait()``) The calling process does not have any unwaited-for children.

   ECHILD 
      The process specified by *pid* (``waitpid()``) does not exist or is not a child 
      of the calling process. This can happen for one's own child if the action for 
      ``SIGCHLD`` is set to ``SIG_IGN``.

   EINTR
      ``WNOHANG`` was not set and an unblocked signal or a ``SIGCHLD`` was caught;
      see :manpage:`signal(7)`.

   EINVAL
      The options argument was invalid.


**NOTES**
       
   A child that terminates, but has not been waited for becomes a "zombie".
   The kernel maintains a minimal set of information about the zombie process
   (PID, termination status, resource usage information) in order to allow the
   parent to later perform a ``wait`` to obtain information about the child.
   As long as a zombie is not removed from the system via a ``wait``, it will
   consume a slot in the kernel process table, and if this table fills, it will
   not be possible to create further processes. If a parent process terminates, 
   then its "zombie" children (if any) are adopted by :manpage:`init(8)`,
   which automatically performs a ``wait`` to remove the zombies.


**EXAMPLE**

   The following program demonstrates the use of :manpage:`fork(2)` and ``waitpid()``. 
   The program creates a child process. If no command-line argument is supplied to the program,
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

