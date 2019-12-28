*******************
Condition Variables
*******************

Condition variables provide yet another way for threads to synchronize. While mutexes
implement synchronization by controlling thread access to data, condition variables allow
threads to synchronize based upon the actual value of data.

Without condition variables, the programmer would need to have threads continually polling
to check if the condition is met. This can be very resource consuming since the thread would
be continuously busy in this activity. A condition variable is a way to achieve the same goal
without polling.

A condition variable is always used in conjunction with a mutex lock.

A representative sequence for using condition variables is shown below:

   * Main Thread

      * Declare and initialize global data which requires synchronization.
      * Declare and initialize a condition variable object.
      * Declare and initialize an associated mutex.
      * Create threads A and B to do work.

   * Thread A

      * Do work up to the point where a certain condition must occur.

      * Lock associated mutex and check value of a global variable.

      * Call ``pthread_cond_wait()`` to perform a blocking wait for signal
        from Thread-B. Note that a call to ``pthread_cond_wait()`` automatically
        and atomically unlocks the associated mutex variable so that it can be
        used by Thread-B.

      * When signalled, wake up. Mutex is automatically and atomically locked.

      * Explicitly unlock mutex.

      * Continue

   * Thread B

      * Do work.
      * Lock associated mutex.
      * Change the value of the global variable that Thread-A is waiting upon.
      * Check the value. If it fulfills the desired condition, signal Thread-A.
      * Unlock mutex.
      * Continue.

   * Main Thread

      * Join / Continue


**Creating and Destroying Condition Variables**

Condition variables must be declared with type ``pthread_cond_t``,
There are two ways to initialize a condition variable:

   * Statically, when it is declared. For example::

      pthread_cond_t myconvar = PTHREAD_COND_INITIALIZER;

   * Dynamically, with the ``pthread_cond_init()`` routine. The ID of the created
     condition variable is returned to the calling thread through the ``condition`` parameter.
     This method permits setting condition variable object attributes, ``attr``.

The optional ``attr`` object is used to set condition variable attributes. There is only one attribute
defined for condition variables: process-shared, which allows the condition variable to be seen by threads
in other processes. The attribute object, if used, must be of type ``pthread_condattr_t`` (may be specified
as ``NULL`` to accept defaults).

**Note** that not all implementations may provide the process-shared attribute.

**Waiting and Signaling on Condition Variables**

``pthread_cond_wait()`` blocks the calling thread until the specified condition is signalled.
This routine should be called while mutex is locked, and it will automatically release the
mutex while it waits. After signal is received and thread is awakened, mutex will be automatically
locked for use by the thread. The programmer is then responsible for unlocking mutex when the thread
is finished with it.

**Recommendation**: Using a WHILE loop instead of an IF statement to check the waited for condition
can help deal with several potential problems, such as:

   * If several threads are waiting for the same wake up signal,
     they will take turns acquiring the mutex, and any one of them
     can then modify the condition they all waited for.

   * If the thread received the signal in error due to a program bug.

   * The Pthreads library is permitted to issue spurious wake ups
     to a waiting thread without violating the standard.

The ``pthread_cond_signal()`` is used to signal another thread which is waiting on
the condition variable. It should be called after mutex is locked,
and must unlock mutex in order for ``pthread_cond_wait()`` routine to complete.

The ``pthread_cond_broadcast()`` routine should be used instead of ``pthread_cond_signal()``
if more than one thread is in a blocking wait state.

It is a logical error to call ``pthread_cond_signal()`` before calling ``pthread_cond_wait()``.

Proper locking and unlocking of the associated mutex variable is essential when using these routines.
For example:

   * Failing to lock the mutex before calling ``pthread_cond_wait()`` may cause it NOT to block.

   * Failing to unlock the mutex after calling ``pthread_cond_signal()`` may not allow a matching
     ``pthread_cond_wait()`` routine to complete (it will remain blocked).
