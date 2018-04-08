The Pthreads API
================

* The original Pthreads API was defined in the ANSI/IEEE POSIX 1003.1 - 1995 standard. The POSIX standard has continued to evolve and undergo revisions, including the Pthreads specification.
  
* Copies of the standard can be purchased from IEEE or downloaded for free from other sites online.
  
* The subroutines which comprise the Pthreads API can be informally grouped into four major groups:
  
   * **Thread management**: Routines that work directly on threads - creating, detaching, joining, etc. They also include functions to set/query thread attributes (joinable, scheduling etc.)
   * **Mutexes**: Routines that deal with synchronization, called a :abbr:`mutex (mutual exclusion)`. Mutex functions provide for creating, destroying, locking and unlocking mutexes. These are supplemented by mutex attribute functions that set or modify attributes associated with mutexes.
   * **Condition variables**: Routines that address communications between threads that share a mutex. Based upon programmer specified conditions. This group includes functions to create, destroy, wait and signal based upon specified variable values. Functions to set/query condition variable attributes are also included.
   * **Synchronization**: Routines that manage read/write locks and barriers.

* Naming conventions: All identifiers in the threads library begin with ``pthread_``. Some examples are shown below.
  
  +---------------------+--------------------------------------------------+
  | Routine Prefix      | Functional Group                                 |
  +=====================+==================================================+
  | pthread\_           | Threads themselves and miscellaneous subroutines |
  +---------------------+--------------------------------------------------+
  | pthread_attr\_      | Thread attributes objects                        |
  +---------------------+--------------------------------------------------+
  | pthread_mutex\_     | Mutexes                                          |
  +---------------------+--------------------------------------------------+
  | pthread_mutexattr\_ | Mutex attributes objects.                        |
  +---------------------+--------------------------------------------------+
  | pthread_cond\_      | Condition variables                              |
  +---------------------+--------------------------------------------------+
  | pthread_condattr\_  | Condition attributes objects                     |
  +---------------------+--------------------------------------------------+
  | pthread_key\_       | Thread-specific data keys                        |
  +---------------------+--------------------------------------------------+
  | pthread_rwlock\_    | Read/write locks                                 |
  +---------------------+--------------------------------------------------+
  | pthread_barrier\_   | Synchronization barriers                         |
  +---------------------+--------------------------------------------------+


* The concept of **opaque objects** pervades the design of the API. The basic calls work to create or modify opaque objects - the opaque objects can be modified by calls to attribute functions, which deal with opaque attributes.
  
* The Pthreads API contains around 100 subroutines. This tutorial will focus on a subset of these - specifically, those which are most likely to be immediately useful to the beginning Pthreads programmer.
  
* For portability, the ``pthread.h`` header file should be included in each source file using the Pthreads library.
  
* The current POSIX standard is defined only for the C language. Fortran programmers can use wrappers around C function calls. Some Fortran compilers may provide a Fortran pthreads API.
  
* A number of excellent books about Pthreads are available. Several of these are listed in the References section of this tutorial.


.. toctree::
   :maxdepth: 2

   api_creating_and_terminating
   api_thread_management
   api_mutex
   api_condition_var


.. note::

   pthread_** functions, is among the few Linux functions that do not follow
   the convention of using a return value of ``1`` for errors. Unless you are
   very sure, it’s always safest to double-check the manual before checking
   the return code.

