**************
POSIX concepts
**************

#. Concurrence vs Parallelism

   +-----------------------------------+-----------------------------------+
   | Concurrence                       | Parallelism                       |
   +===================================+===================================+
   | .. image:: images/concurrency.jpg | .. image:: images/parallelism.jpg |
   +-----------------------------------+-----------------------------------+

#. Reentry Routines vs Thread-safe Routines

   Re-entrant code can be called more than once, whether by different threads
   or by nested invocations in some way, and still function correctly. Thus,
   the re-entrant section of code usually must use local variables only in such
   a way that each and every call to the code gets its own unique copy of the data.

#. MT-Safe vs MT-Unsafe

   MT-Safe or Thread-Safe functions are safe to call in the presence of other threads.  
   MT, in MT-Safe, stands for Multi Thread.

   Being MT-Safe does not imply a function is atomic, nor that it uses any of the memory 
   synchronization mechanisms POSIX exposes to users. It is even possible that calling 
   MT-Safe functions in sequence does not yield an MT-Safe combination. For example, 
   having a thread call two MT-Safe functions one right after the other does not guarantee  
   behavior equivalent to atomic execution of a combination of both functions, since concurrent 
   calls in other threads may interfere in a destructive way.

   Whole-program optimizations that could inline functions across library interfaces may expose 
   unsafe reordering, and so performing inlining across the GNU C Library interface is not recommended.  
   The documented MT-Safety status is not guaranteed under whole-program optimization. However, functions 
   defined in user-visible headers are designed to be safe for inlining.

#. Thread-safety Implementation approaches
   
   Below we discuss two approaches for avoiding race conditions to achieve thread safety.

   The first class of approaches focuses on **avoiding shared state**, 
   and includes:

      - Re-entrancy 
        
      - Thread-local storage 
        
      - Immutable objects 
        
         The state of an object cannot be changed after construction. 
         This implies both that only read-only data is shared. Mutable (non-const) 
         operations can then be implemented in such a way that they create new objects 
         instead of modifying existing ones. This approach is characteristic of functional 
         programming and is also used by the string implementations in Python.

   The second class of approaches are **synchronization-related**, and are used in situations 
   where shared state cannot be avoided:

      - Mutual exclusion
        
      - Atomic operations 
        
         Shared data is accessed by using atomic operations which cannot be interrupted by other threads.
         This usually requires using special machine language instructions, which might be available in a 
         runtime library. Since the operations are atomic, the shared data is always kept in a valid state, 
         no matter how other threads access it. Atomic operations form the basis of many thread locking 
         mechanisms, and are used to implement mutual exclusion primitives.

   .. code-block:: c
      :caption: Mutex example

      # include <pthread.h>
      int increment_counter ()
      {
         static int counter = 0;
         static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
         pthread_mutex_lock(&mutex);
         ++counter;
         int result = counter;
         pthread_mutex_unlock(&mutex);
         return result;
      }

   .. code-block:: cpp
      :caption: Atomicity example

      # include <atomic>
      int increment_counter ()
      {
         static std::atomic<int> counter(0);
         // increment is guaranteed to be done atomically
         int result = ++counter;
         return result;
      }


#. Reentrancy 
   
   In computing, a computer program or subroutine is called reentrant if it can be interrupted 
   in the middle of its execution and then safely be called again ("re-entered") before its 
   previous invocations complete execution. The interruption could be caused by an internal 
   action such as a jump or call, or by an external action such as an interrupt or signal. 
   Once the interruption completes, the previous invocations will resume correct execution.

   This definition originates from single-threaded programming environments where the flow of control 
   could be interrupted by an interruption and transferred to an :abbr:`ISR (interrupt service routine)`. 
   Any subroutine used by the ISR that could potentially have been executing when the interruption was 
   triggered should be reentrant.

   Reentrancy is distinct from, but closely related to, thread-safety. A function can be thread-safe 
   and still not reentrant. For example, a function could be wrapped all around with a mutex, 
   but, if that function were used in an ISR, it could starve waiting for the first execution 
   to release the mutex. The key for avoiding confusion is that **reentrant refers to only one thread 
   executing. It is a concept from the time when no multitasking operating systems existed.** 
   Rules for reentrancy come following:

      - Reentrant code may not hold any static or global non-constant data.
      - Reentrant code may not modify itself.
      - Reentrant code may not call non-reentrant routines.

   .. note::

      The OS might allow a process to modify its code. 
      There are various reasons for this (e.g., blitting graphics quickly) 
      but this would cause a problem with reentrancy, since the code might 
      not be the same next time. It may, however, modify itself if it resides 
      in its own unique memory. That is, if each new invocation uses a different 
      physical machine code location where a copy of the original code is made, 
      it will not affect other invocations even if it modifies itself during 
      execution of that particular invocation (thread).