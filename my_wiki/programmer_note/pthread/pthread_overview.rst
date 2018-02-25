Pthread Overview
================


What is a Thread?
-----------------

* Technically, **a thread is defined as an independent stream of instructions that can be scheduled to run as such by the operating system**. But what does this mean?

* To the software developer, the concept of a "procedure" that runs independently from its main program may best describe a thread.

* To go one step further, imagine a main program (a.out) that contains a number of procedures. Then imagine all of these procedures being able to be scheduled to run simultaneously and/or independently by OS. That would describe a "multithreaded" program.

* How is this accomplished?
  
* Before understanding a thread, one first needs to understand a UNIX process. A process is created by OS, and requires a fair amount of "overhead". Processes contain information about program resources and program execution state, including:
  
   * Process ID, process group ID, user ID, and group ID
   * Environment
   * Working directory.
   * Program instructions
   * Registers
   * Stack
   * Heap
   * File descriptors
   * Signal actions
   * Shared libraries
   * Inter-process communication tools (such as message queues, pipes, semaphores, or shared memory).

+-----------------------------------------+----------------------------------------+
| process structure                       | thread structure                       |
+=========================================+========================================+
| .. image:: images/process_structure.png | .. image:: images/thread_structure.png |
+-----------------------------------------+----------------------------------------+

* Threads use and exist within these process resources, yet are able to be scheduled by OS and run as independent entities largely because they duplicate only the bare essential resources that enable them to exist as executable code. This independent flow of control is accomplished because a thread maintains its own:
  
   * Stack pointer
   * Registers
   * Scheduling properties (such as policy or priority)
   * Set of pending and blocked signals
   * Thread specific data.

* So, in summary, in the UNIX environment a thread:
  
   * Exists within a process and uses the process resources
   * Has its own independent flow of control as long as its parent process exists and the OS supports it
   * Duplicates only the essential resources it needs to be independently schedulable
   * May share the process resources with other threads that act equally independently (and dependently)
   * Dies if the parent process dies - or something similar
   * Is "lightweight" because most of the overhead has already been accomplished through the creation of its process.

* Because threads within the same process share resources:
  
   * Changes made by one thread to shared system resources (such as closing a file) will be seen by all other threads.
   * Two pointers having the same value point to the same data.
   * Reading and writing to the same memory locations is possible, and therefore requires explicit synchronization by the programmer.
     
* Historically, hardware vendors have implemented their own proprietary versions of threads. These implementations differed substantially from each other making it difficult for programmers to develop portable threaded applications.

* In order to take full advantage of the capabilities provided by threads, a standardized programming interface was required.
  
   * For UNIX systems, this interface has been specified by the IEEE POSIX 1003.1c standard (1995).
   * Implementations adhering to this standard are referred to as POSIX threads, or Pthreads.
   * Most hardware vendors now offer Pthreads in addition to their proprietary API's.

* The POSIX standard has continued to evolve and undergo revisions, including the Pthreads specification. Some useful links:
  
   * standards.ieee.org/findstds/standard/1003.1-2008.html
   * www.opengroup.org/austin/papers/posix_faq.html
   * www.unix.org/version3/ieee_std.html

* Pthreads are defined as a set of C language programming types and procedure calls, implemented with a ``pthread.h`` header/include file and a thread library - though this library may be part of another library, such as ``libc``, in some implementations.
  

Designing Threaded Programs
---------------------------

Parallel Programming
^^^^^^^^^^^^^^^^^^^^

* On modern, multi-core machines, pthreads are ideally suited for parallel programming, and whatever applies to parallel programming in general, applies to parallel pthreads programs.

* There are many considerations for designing parallel programs, such as:
  
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

* Covering these topics is beyond the scope of this tutorial, however interested readers can obtain a quick overview in the Introduction to Parallel Computing tutorial.

* In general though, in order for a program to take advantage of Pthreads, it must be able to be organized into discrete, independent tasks which can execute concurrently. For example, if routine1 and routine2 can be interchanged, interleaved and/or overlapped in real time, they are candidates for threading.
  
.. image:: images/concurrent.png

* Programs having the following characteristics may be well suited for pthreads:
  
   * Work that can be executed, or data that can be operated on, by multiple tasks simultaneously:
   * Block for potentially long I/O waits
   * Use many CPU cycles in some places but not others
   * Must respond to asynchronous events
   * Some work is more important than other work (priority interrupts)
     
* Several common models for threaded programs exist:
  
   * **Manager/worker**: a single thread, the manager assigns work to other threads, the workers. Typically, the manager handles all input and parcels out work to the other tasks. At least two forms of the manager/worker model are common: static worker pool and dynamic worker pool.
   * **Pipeline**: a task is broken into a series of suboperations, each of which is handled in series, but concurrently, by a different thread. An automobile assembly line best describes this model.
   * **Peer**: similar to the manager/worker model, but after the main thread creates other threads, it participates in the work.
     

Shared Memory Model
^^^^^^^^^^^^^^^^^^^

* All threads have access to the same global, shared memory
  
* Threads also have their own private data
  
* Programmers are responsible for synchronizing access (protecting) globally shared data.
  
.. image:: images/sharedMemoryModel.png


Thread-safeness
^^^^^^^^^^^^^^^

* Thread-safeness: in a nutshell, refers an application's ability to execute multiple threads simultaneously without "clobbering" shared data or creating "race" conditions.
  
* For example, suppose that your application creates several threads, each of which makes a call to the same library routine:
  
   * This library routine accesses/modifies a global structure or location in memory.
   * As each thread calls this routine it is possible that they may try to modify this global structure/memory location at the same time.
   * If the routine does not employ some sort of synchronization constructs to prevent data corruption, then it is not thread-safe.
     
.. image:: images/threadUnsafe.png

* The implication to users of external library routines is that if you aren't 100% certain the routine is thread-safe, then you take your chances with problems that could arise.
  
* Recommendation: Be careful if your application uses libraries or other objects that don't explicitly guarantee thread-safeness. When in doubt, assume that they are not thread-safe until proven otherwise. This can be done by "serializing" the calls to the uncertain routine, etc.

  
Thread Limits
^^^^^^^^^^^^^

* Although the Pthreads API is an ANSI/IEEE standard, implementations can, and usually do, vary in ways not specified by the standard.

* Because of this, a program that runs fine on one platform, may fail or produce wrong results on another platform.

* For example, the maximum number of threads permitted, and the default thread stack size are two important limits to consider when designing your program.

* Several thread limits are discussed in more detail later in this tutorial.
  