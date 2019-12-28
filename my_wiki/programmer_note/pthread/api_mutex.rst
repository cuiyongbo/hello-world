***************
Mutex Variables
***************

**Overview**

:abbr:`Mutex (mutual exclusion)` variables are one of the primary means
of implementing thread synchronization and for protecting shared data
when multiple writes occur.

A mutex variable acts like a "lock" protecting access to a shared data resource.
**The basic concept of a mutex as used in Pthreads is that only one thread can lock
a mutex variable at any given time.** Thus, even if several threads try to
lock a mutex only one thread will be successful. No other thread can own that mutex
until the owning thread unlocks that mutex. Threads must "take turns" accessing
protected data.

Mutexes can be used to prevent race conditions. An example of a race condition
involving a bank transaction is shown below:

   +---------------------------+---------------------------+---------+
   | Thread 1                  | Thread 2                  | Balance |
   +===========================+===========================+=========+
   | Read balance: $1000       |                           | $1000   |
   +---------------------------+---------------------------+---------+
   |                           | Read balance: $1000       | $1000   |
   +---------------------------+---------------------------+---------+
   |                           | Deposit $200              | $1000   |
   +---------------------------+---------------------------+---------+
   | Deposit $200              |                           | $1000   |
   +---------------------------+---------------------------+---------+
   | Update balance $1000+$200 |                           | $1200   |
   +---------------------------+---------------------------+---------+
   |                           | Update balance $1000+$200 | $1200   |
   +---------------------------+---------------------------+---------+

In the above example, a mutex should be used to lock the "Balance" while
a thread is using this shared data resource.

Very often the action performed by a thread owning a mutex is the updating
of global variables. This is a safe way to ensure that when several threads
update the same variable, the final value is the same as what it would be
if only one thread performed the update.

A typical sequence in the use of a mutex is as follows:

   * Create and initialize a mutex variable
   * Several threads attempt to lock the mutex
   * Only one succeeds and that thread owns the mutex
   * The owner thread performs some set of actions
   * The owner unlocks the mutex
   * Another thread acquires the mutex and repeats the process
   * Finally the mutex is destroyed

When several threads compete for a mutex, the losers block at that call - an
unblocking call is available with trylock instead of the lock call.

When protecting shared data, it is the programmer's responsibility to make
sure every thread that needs to use a mutex does so. For example, if 4 threads
are updating the same data, but only one uses a mutex, the data can still be
corrupted.


**Creating and Destroying Mutexes**


Mutex variables must be declared with type ``pthread_mutex_t``, and must be initialized
before they can be used. There are two ways to initialize a mutex variable:

   * Statically, when it is declared. For example::

      pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

   * Dynamically, with the ``pthread_mutex_init()`` routine.
     This method permits setting mutex object attributes, ``attr.``

The mutex is initially unlocked. The ``attr`` object is used to establish properties for
the mutex object, and must be of type ``pthread_mutexattr_t`` if used (may be specified
as ``NULL`` to accept defaults). The Pthreads standard defines three optional mutex
attributes:

   * Protocol: Specifies the protocol used to prevent priority inversions for a mutex.
   * Prioceiling: Specifies the priority ceiling of a mutex.
   * Process-shared: Specifies the process sharing of a mutex.

.. note::

   Note that not all implementations may provide the three optional mutex attributes.

**Locking and Unlocking Mutexes**

The ``pthread_mutex_lock()`` routine is used by a thread to acquire a lock
on the specified mutex variable. If the mutex is already locked by another
thread, this call will block the calling thread until the mutex is unlocked.

``pthread_mutex_trylock()`` will attempt to lock a mutex. However, if the
mutex is already locked, the routine will return immediately with a "busy"
error code. This routine may be useful in preventing deadlock conditions,
as in a priority-inversion situation.

``pthread_mutex_unlock()`` will unlock a mutex if called by the owning thread.
Calling this routine is required after a thread has completed its use of protected
data if other threads are to acquire the mutex for their work with the protected
data. An error will be returned:

   * If the mutex was already unlocked (call it multi-times)
   * If the mutex is owned by another thread (a thread doesn't own the mutex)

There is nothing "magical" about mutexes, in fact they are akin to a "gentlemen's agreement"
between participating threads. It is up to the code writer to ensure that the necessary threads
all make the the mutex lock and unlock calls correctly. The following scenario demonstrates a
logical error:

   +----------+----------+----------+
   | Thread 1 | Thread 2 | Thread 3 |
   +==========+==========+==========+
   | Lock     | Lock     |          |
   +----------+----------+----------+
   | A = 2    | A = A+1  | A = A*B  |
   +----------+----------+----------+
   | Unlock   | Unlock   |          |
   +----------+----------+----------+

.. note::

   QUESTION: When more than one thread is waiting for a locked mutex,
   which thread will be granted the lock first after it is released?

   ANSWER: Unless thread priority scheduling is used, the assignment
   will be left to the native system scheduler and may appear to be
   more or less random.
