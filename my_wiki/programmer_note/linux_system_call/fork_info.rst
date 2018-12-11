***********
fork Manual
***********

**DESCRIPTION**

   .. code-block:: c
   
      #include <unistd.h>
      pid_t fork(void);


   ``fork()`` creates a new process by duplicating the calling process. 
   The new process is referred to as the child process.
   The calling process is referred to as the parent process.

   The child process and the parent process run in separate memory spaces.
   At the time of ``fork()`` both memory spaces have the same content.
   Memory writes, file mappings (**mmap(2)**), and unmappings (**munmap(2)**)
   performed by one of the processes do not affect the other.

   The child process is an exact duplicate of the parent process except for the following points:

      * The child has its own unique PID, and this PID does not match
        the ID of any existing process group.

      * The child's parent PID is the same as the parent's PID.

      * The child does not inherit its parent's memory locks.
        
      * Process resource utilizations and CPU time counters are reset to zero in the child.

      * The child's set of pending signals is initially empty.

      * The child does not inherit semaphore adjustments from its parent.

      * The  child  does not inherit process-associated record locks from its parent.
        (On the other hand, it does inherit **fcntl(2)** open file description locks
        and **flock(2)** locks from its parent.)

      * The child does not inherit timers from its parent

      * The child does not inherit outstanding asynchronous I/O operations from its parent, 
        nor does it inherit any asynchronous I/O contexts from its parent.

   The process attributes in the preceding list are all specified in POSIX.1.
   The parent and child also differ with respect to the following Linux-specific
   process attributes:

      * The child does not inherit directory change notifications (dnotify) from its parent.

      * The :manpage:`prctl(2)` ``PR_SET_PDEATHSIG`` setting is reset so that the child
        does not receive a signal when its parent terminates.

      * The default timer slack value is set to the parent's current timer slack value.

      * Memory mappings that have been marked with the :manpage:`madvise(2)`
        ``MADV_DONTFORK`` flag are not inherited across a ``fork()``.

      * The termination signal of the child is always ``SIGCHLD``.

      * The port access permission bits set by :manpage:`ioperm(2)`
        are not inherited by the child; the child must turn on any bits
        that it requires using :manpage:`ioperm(2)`.

   Note the following further points:

      * The child process is created with a single thread—the one that called ``fork()``.
        The entire virtual address space of the parent is replicated in the child, including
        the states of mutexes, condition variables, and other pthreads objects; the use of
        :manpage:`pthread_atfork(3)` may be helpful for dealing with problems that this can cause.

      * After a **fork()** in a multithreaded program, the child can safely
        call only async-signal-safe functions until such time as it calls **execve(2)**.

      * The child inherits copies of the parent's set of open file descriptors. Each file descriptor in the child
        refers to the same open file description as the corresponding file descriptor in the parent.
        This means that the two descriptors share open file status flags, current file offset, and signal-driven I/O attributes

      * The child inherits copies of the parent's set of open message queue descriptors.
        Each descriptor in the child refers to the same open message queue description 
        as the corresponding descriptor in the parent. This means that the two descriptors 
        share the same flags (mq_flags).

      * The child inherits copies of the parent's set of open directory streams.
        POSIX.1 says that the corresponding directory streams in the parent and child may share
        the directory stream positioning; on :file:`Linux/glibc` they do not.

**RETURN VALUE**

   On success, the PID of the child process is returned in the parent, and 0 is returned in the child. 
   On failure, -1 is returned in the parent, no child process is created, and *errno* is set appropriately.

**NOTES**

   Under Linux, ``fork()`` is implemented using **copy-on-write** pages, so the only penalty that it incurs 
   is the time and memory required to duplicate the parent's page tables, and to create a unique task 
   structure for the child.

**Examples**

.. code-block:: c

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <unistd.h>
   
   int g_var=6;
   
   int main()
   {
       int var = 88;
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

   // Output:
   //$ ./a.out 
   //before fork
   //pid = 11136, global = 7, local = 89 # child's variable were changed
   //pid = 11135, global = 6, local = 88 # parent's copy remain unchanged.
   

.. rubric:: Footnotes

.. [#] `threads and fork mixed usage <https://www.linuxprogrammingblog.com/threads-and-fork-think-twice-before-using-them>`_