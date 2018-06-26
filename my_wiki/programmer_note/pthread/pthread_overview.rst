****************
Pthread Overview
****************

What is a Thread?
=================

Technically, **a thread is defined as an independent stream of instructions that can
be scheduled to run as such by the OS**. But what does this mean?

To the software developer, the concept of a **procedure** that runs independently
from its main program may best describe a thread. To go one step further, imagine
a program that contains a number of procedures. Then imagine all of these procedures
being able to be scheduled to run simultaneously and/or independently by OS. That
would describe a multithreaded program. But how is this accomplished?
  
Before understanding a thread, one first needs to understand a UNIX **process**.
A process is created by OS, and requires a fair amount of "overhead". Processes
contain information about program resources and program execution state, including:

   - Process ID, process group ID, user ID, and group ID
   - Environment
   - Working directory
   - Program instructions
   - Registers
   - Stack
   - Heap
   - File descriptors
   - Signal actions
   - Shared libraries
   - IPC tools (such as message queues, pipes, semaphores, or shared memory).

+-----------------------------------------+----------------------------------------+
| process structure                       | thread structure                       |
+=========================================+========================================+
| .. image:: images/process_structure.png | .. image:: images/thread_structure.png |
+-----------------------------------------+----------------------------------------+

Threads use and exist within these process resources, yet are able to be scheduled by OS
and run as independent entities largely because they duplicate only the bare essential
resources that enable them to exist as executable code. This independent flow of control
is accomplished because a thread maintains its own:

   - Stack pointer
   - Registers
   - Scheduling properties (such as policy or priority)
   - Set of pending and blocked signals
   - Thread specific data.

So, in summary, in the UNIX environment a thread:

   * Exists within a process and uses the process resources
   * Has its own independent flow of control as long as its parent process exists and the OS supports it
   * Duplicates only the essential resources it needs to be independently schedulable
   * May share the process resources with other threads that act equally independently (and dependently)
   * Dies if the parent process dies - or something similar
   * Is "lightweight" because most of the overhead has already been accomplished through the creation of its process.

Because threads within the same process share resources:

   * Changes made by one thread to shared system resources (such as closing a file) will be seen by all other threads.
   * Two pointers having the same value point to the same data.
   * Reading and writing to the same memory locations is possible, and therefore requires explicit **synchronization**
     by the programmer.


Designing Threaded Programs
===========================

Parallel Programming
--------------------

On modern multi-core machines, pthreads are ideally suited for parallel programming,
and whatever applies to parallel programming in general, applies to parallel pthreads
programs.

There are many considerations for designing parallel programs, such as:
  
   * What type of parallel programming model to use?
   * Problem partitioning
   * Load balancing
   * Communications
   * Data dependencies
   * Synchronization and race conditions
   * Memory issues
   * I/O issues
   * Program complexity
   * Programmer effort/costs/time
   * ...

Covering these topics is beyond the scope of this tutorial, however interested readers
can obtain a quick overview in the *Introduction to Parallel Computing tutorial*.

In general though, in order for a program to take advantage of Pthreads, it must be able
to be organized into discrete, independent tasks which can execute concurrently. For example,
if *routine1* and *routine2* can be interchanged, interleaved and/or overlapped in real time,
they are candidates for threading.
  
.. image:: images/concurrent.png

Programs having the following characteristics may be well suited for pthreads:
  
   * Work that can be executed, or data that can be operated on by multiple tasks simultaneously
   * Block for potentially long I/O waits
   * Use many CPU cycles in some places but not others
   * Must respond to asynchronous events
   * Some work is more important than other work (priority interrupts)
     
Several common models for threaded programs exist:
  
   * **Manager/worker**: a single thread, the manager assigns work to other threads,
     the workers. Typically, the manager handles all input and parcels out work to 
     the other tasks. At least two forms of the manager/worker model are common:
     **static worker pool** and **dynamic worker pool**.

   * **Pipeline**: a task is broken into a series of suboperations, each of which
     is handled in series, but concurrently, by a different thread. An automobile
     assembly line best describes this model.

   * **Peer**: similar to the manager/worker model, but after the main thread
     creates other threads, it participates in the work.
     

Shared Memory Model
-------------------

* All threads have access to the same global, shared memory
  
* Threads also have their own private data
  
* Programmers are responsible for synchronizing access (protecting) globally shared data.
  
.. image:: images/sharedMemoryModel.png


Thread-safeness
---------------

In a nutshell, refers an application's ability to execute multiple
threads simultaneously without "clobbering" shared data or creating "race" conditions.  
For example, suppose that your application creates several threads, each of which makes
a call to the same library routine; this library routine accesses/modifies a global
structure or location in memory. As each thread calls this routine it is possible
that they may try to modify this global structure/memory location at the same time.
If the routine does not employ some sort of synchronization constructures to prevent
data corruption, then it is not thread-safe.
     
.. image:: images/threadUnsafe.png

The implication to users of external library routines is that if you aren't 100%
certain the routine is thread-safe, then you take your chances with problems that
could arise. So be careful if your application uses libraries or other objects that
don't explicitly guarantee thread-safeness. When in doubt, assume that they are not
thread-safe until proven otherwise. This can be done by "serializing" the calls to
the uncertain routine, etc.

.. note::

   #. Pthreads
         
      *POSIX.1* specifies a set of interfaces (functions, header files) for threaded programming 
      commonly known as POSIX threads, or Pthreads. A single process can contain multiple threads, 
      all of which are executing the same program. These threads share the same global memory (data 
      and heap segments), but each thread has its own stack (automatic variables).

      POSIX.1 also requires that threads share a range of other attributes (i.e., these attributes 
      are process-wide rather than per-thread):

         -  process ID
         -  parent process ID
         -  process group ID and session ID
         -  controlling terminal
         -  user and group IDs
         -  open file descriptors
         -  record locks (see fcntl(2))
         -  signal dispositions
         -  file mode creation mask (umask(2))
         -  current directory (chdir(2)) and root directory (chroot(2))
         -  interval timers (setitimer(2)) and POSIX timers (timer_create(2))
         -  nice value (setpriority(2))
         -  resource limits (setrlimit(2))
         -  measurements of the consumption of CPU time (times(2)) and resources (getrusage(2))

      As well as the stack, *POSIX.1* specifies that various other attributes are distinct 
      for each thread, including:

         -  thread ID (the pthread_t data type)
         -  signal mask (pthread_sigmask(3))
         -  the errno variable
         -  alternate signal stack (sigaltstack(2))
         -  real-time scheduling policy and priority (sched_setscheduler(2) and sched_setparam(2))

      The following Linux-specific features are also per-thread:

         -  capabilities (see capabilities(7))
         -  CPU affinity (sched_setaffinity(2))

   #. Pthreads function return values
      
      Most pthreads functions return 0 on success, and an error number of failure.  
      **Note that the pthreads functions do not set errno.** For each of the pthreads 
      functions that can return an error, *POSIX.1-2001* specifies that the function 
      can never fail with the error *EINTR*.

   #. Compiling on Linux

      On Linux, programs that use the Pthreads API should be compiled using ``cc -pthread``.
