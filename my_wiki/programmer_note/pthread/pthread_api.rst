****************
The Pthreads API
****************

.. toctree::

   api_creating_and_terminating
   api_thread_management
   api_mutex
   api_condition_var

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

The subroutines which comprise the Pthreads API 
can be informally grouped into four major groups:
  
   - **Thread management**: Routines that work directly on threads - creating, 
     detaching, joining, etc. They also include functions to set/query 
     thread attributes (joinable, scheduling etc.)

   - **Mutexes**: Routines that deal with synchronization, 
     called a :abbr:`mutex (mutual exclusion)`. Mutex functions 
     provide for creating, destroying, locking and unlocking mutexes. 
     These are supplemented by mutex attribute functions that set/modify 
     attributes associated with mutexes.

   - **Condition variables**: Routines that address communications between threads 
     that share a mutex. Based upon programmer specified conditions. This group 
     includes functions to create, destroy, wait and signal based upon specified 
     variable values. Functions to set/query condition variable attributes 
     are also included.

   - **Synchronization**: Routines that manage read/write locks and barriers.

The concept of **opaque objects** pervades the design of the API. 
The basic calls work to create or destroy opaque objects, and the 
opaque objects can be modified by calls to attribute functions, 
which deal with opaque attributes.
