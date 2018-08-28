***********
fork Manual
***********

.. code-block:: c
   :caption: Language support

   /* fork - create a child process */
   
   #include <unistd.h>
   pid_t fork(void);

**DESCRIPTION**

   ``fork()``  creates  a  new process by duplicating the calling process. 
   The new process is referred to as the child process.
   The calling process is referred to as the parent process.

   The child process and the parent process run in separate memory spaces.
   At the time of ``fork()`` both memory spaces have the same content.
   Memory writes, file mappings (:manpage:`mmap(2)`), and unmappings (:manpage:`munmap(2)`)
   performed by one of the processes do not affect the other.

   The child process is an exact duplicate of the parent process except for the following points:

      * The child has its own unique :abbr:`PID (Process ID)`, and this PID does not match
        the ID of any existing process group (:manpage:`setpgid(2)`).

      * The child's parent PID is the same as the parent's PID.

      * The child does not inherit its parent's memory locks
        (:manpage:`mlock(2)`, :manpage:`mlockall(2)`).

      * Process resource utilizations (:manpage:`getrusage(2)`) and
        CPU time counters (:manpage:`times(2)`) are reset to zero in the child.

      * The child's set of pending signals is initially empty (:manpage:`sigpending(2)`).

      * The child does not inherit semaphore adjustments from its parent (:manpage:`semop(2)`).

      * The  child  does not inherit process-associated record locks from its parent (:manpage:`fcntl(2)`).
        (On the other hand, it does inherit :manpage:`fcntl(2)` open file description locks
        and :manpage:`flock(2)` locks from its parent.)

      * The child does not inherit timers from its parent
        (:manpage:`setitimer(2)`, :manpage:`alarm(2)`, :manpage:`timer_create(2)`).

      * The child does not inherit outstanding asynchronous I/O operations from its parent
        (:manpage:`aio_read(3)`, :manpage:`aio_write(3)`), nor does it inherit any
        asynchronous I/O contexts from its parent (see :manpage:`io_setup(2)`).

   The process attributes in the preceding list are all specified in POSIX.1.
   The parent and child also differ with respect to the following Linux-specific
   process attributes:

      * The child does not inherit directory change notifications (dnotify) from its parent.
        (see the description of ``F_NOTIFY`` in :manpage:`fcntl(2)`).

      * The :manpage:`prctl(2)` ``PR_SET_PDEATHSIG`` setting is reset so that the child
        does not receive a signal when its parent terminates.

      * The default timer slack value is set to the parent's current timer slack value.
        See the description of ``PR_SET_TIMERSLACK`` in :manpage:`prctl(2)`.

      * Memory mappings that have been marked with the :manpage:`madvise(2)`
        ``MADV_DONTFORK`` flag are not inherited across a ``fork()``.

      * The termination signal of the child is always ``SIGCHLD``
        (see :manpage:`clone(2)`).

      * The port access permission bits set by :manpage:`ioperm(2)`
        are not inherited by the child; the child must turn on any bits
        that it requires using :manpage:`ioperm(2)`.

   Note the following further points:

      * The  child  process is created with a single thread—the one that called ``fork()``.
        The entire virtual address space of the parent is replicated in the child, including
        the states of mutexes, condition variables, and other pthreads objects; the use of
        :manpage:`pthread_atfork(3)` may be helpful for dealing with problems that this can cause.

      * After a :manpage:`fork(2)` in a multithreaded program, the child can safely
        call only async-signal-safe functions (see :manpage:`signal(7)`) until
        such time as it calls :manpage:`execve(2)`.

      * The child inherits copies of the parent's set of open file descriptors. Each file descriptor in the child
        refers to the same open file description (see :manpage:`open(2)`) as the corresponding file descriptor in the parent.
        This means that the two descriptors share open file status flags, current file offset, and signal-driven I/O attributes
        (see the description of ``F_SETOWN`` and ``F_SETSIG`` in :manpage:`fcntl(2)`).

      * The child inherits copies of the parent's set of open message queue descriptors (see :manpage:`mq_overview(7)`).
        Each descriptor in the child refers to the same open message queue description as the corresponding descriptor
        in the parent. This means that the two descriptors share the same flags (mq_flags).

      * The child inherits copies of the parent's set of open directory streams (see :manpage:`opendir(3)`).
        POSIX.1 says that the corresponding directory streams in the parent and child may share
        the directory stream positioning; on :file:`Linux/glibc` they do not.

**RETURN VALUE**

   On success, the PID of the child process is returned in the parent, and 0 is returned in the child. 
   On failure, -1 is returned in the parent, no child process is created, and *errno* is set appropriately.

**NOTES**

   Under Linux, ``fork()`` is implemented using **copy-on-write** pages, so the only penalty that it incurs is the time and
   memory required to duplicate the parent's page tables, and to create a unique task structure for the child.


**Examples**

.. code-block:: c

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <unistd.h>
   
   int g_var=6;
   char g_buf[] = "hello world!\n";
   
   int main()
   {
       int var = 88;
       fputs(g_buf, stdout);
       puts("before fork");
   
       pid_t pid = fork();
       if(pid < 0)
       {
           perror("fork");
           exit(EXIT_FAILURE);
       }
       else if(pid == 0)
       {
           g_var++;
           var++;
       }        
       else
       {
           sleep(2);
       }
   
       printf("pid = %ld, global = %d, local = %d\n",
           (long)getpid(), g_var, var);
   
       return 0;
   }

Output::

   $ ./a.out 
   hello world!
   before fork
   pid = 11136, global = 7, local = 89 # child's variable were changed
   pid = 11135, global = 6, local = 88 # parent's copy remain unchanged.
   
