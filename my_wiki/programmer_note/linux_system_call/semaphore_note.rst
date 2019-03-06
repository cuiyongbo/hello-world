**************
Semaphore note
**************

.. code-block:: c
    :caption: POSIX Semaphore APIs

    #include <semaphore.h>
    #include <fcntl.h>           /* For O_* constants */
    #include <sys/stat.h>

    // Link with -pthread.
    sem_t *sem_open(const char *name, int oflag);
    sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
    int sem_close(sem_t *sem);
    int sem_unlink(const char *name);

    int sem_init(sem_t *sem, int pshared, unsigned int value);
    int sem_destroy(sem_t *sem);
    
    int sem_post(sem_t *sem);
    int sem_wait(sem_t *sem);
    int sem_trywait(sem_t *sem);
    int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
    
    int sem_getvalue(sem_t *sem, int *sem_val);

On success, sem_open() returns the address of the new semaphore; this address is used 
when calling other semaphore-related functions. On error, sem_open() returns ``SEM_FAILED``, 
with errno set to indicate the error.

All of these functions except ``sem_open()`` return 0 on success; on error, 
-1 is returned, and errno is set to indicate the error. 

POSIX semaphores allow processes and threads to synchronize their actions.
A semaphore is an integer whose value is never allowed to fall below zero. 
Two operations can be performed on semaphores: increment the semaphore value by one (`sem_post(3)`); 
and decrement the semaphore value by one (`sem_wait(3)`). If the value of a semaphore is currently zero, 
then a `sem_wait(3)` operation will block until the value becomes greater than zero.

POSIX semaphores come in two forms: **named semaphores and unnamed semaphores.**

    * Named semaphores

        A named semaphore is identified by a name of the form `/somename`; 
        the name convension is the same as POSIX shared memory.
        Two processes can operate on the same named semaphore by passing the same name to `sem_open(3)`.
        The      function creates a new named semaphore or opens an existing named semaphore. 
        After the semaphore has been opened, it can be operated on using `sem_post(3)` and `sem_wait(3)`. 
        When a process has finished using the semaphore, it can use `sem_close(3)` to close the semaphore. 
        When all processes have finished using the semaphore, it can be removed from the system using `sem_unlink(3)`.

    * Unnamed semaphores (memory-based semaphores)
      
        An unnamed semaphore does not have a name. Instead the semaphore is placed in a region of memory 
        that is shared between multiple threads or processes. 
        A thread-shared semaphore is placed in an area of memory shared between the threads of a process, 
        for example, a global variable. A process-shared semaphore must be placed in a shared memory region.

        Before being used, an unnamed semaphore must be initialized using `sem_init(3)`. It can then be operated 
        on using `sem_post(3)` and `sem_wait(3)`. When the semaphore is no longer required, and before the memory 
        in which it is located is deallocated, the semaphore should be destroyed using `sem_destroy(3)`.


`sem_init()` initializes the unnamed semaphore at the address pointed to by `sem`. 
The value argument specifies the initial value for the semaphore. The `pshared` argument 
indicates whether this semaphore is to be shared between the threads of a process, or between processes.

If `pshared` has the value 0, then the semaphore is shared between the threads of a process, 
and should be located at some address that is visible to all threads (e.g., a global variable, 
or a variable allocated dynamically on the heap).

If `pshared` is nonzero, then the semaphore is shared between processes, and should be located in a region of shared memory. 
Since a child created by `fork(2)` inherits its parent's memory mappings, it can also access the semaphore. 
Any process that can access the shared memory region can operate on the semaphore using `sem_post(3)`, `sem_wait(3)`, etc.

Only a semaphore that has been initialized by `sem_init(3)` should be destroyed using `sem_destroy()`.
Destroying a semaphore that other processes or threads are currently blocked on (in `sem_wait(3)`) produces undefined behavior.
An unnamed semaphore should be destroyed with `sem_destroy()` before the memory in which it is located is deallocated. 
Failure to do this can result in resource leaks on some implementations.