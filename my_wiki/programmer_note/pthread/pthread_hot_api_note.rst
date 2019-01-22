****************
Pthread Hot APIs
****************

.. code-block:: c

   #include <pthread.h>

    pthread_t pthread_self(void);
    int pthread_equal(pthread_t t1, pthread_t t2);

    int pthread_setname_np(pthread_t thread, const char *name);
    int pthread_getname_np(pthread_t thread, char *name, size_t len);

    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
                           void *(*start_routine)(void *), void *arg);
    void pthread_exit(void *rval_ptr);
   
    int pthread_attr_init(pthread_attr_t *attr);
    int pthread_attr_destroy(pthread_attr_t *attr);
    int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
    int pthread_attr_getdetachstate(pthread_attr_t *attr, int *detachstate);
    int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
    int pthread_attr_getstacksize(const pthread_attr_t *restrict attr, size_t *restrict stacksize);
    int pthread_attr_setstackaddr(pthread_attr_t *attr, void *stackaddr);
    int pthread_attr_getstackaddr(const pthread_attr_t *restrict attr, void **restrict stackaddr);
    int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize);
    int pthread_attr_getguardsize(const pthread_attr_t *attr, size_t *guardsize);

    int pthread_detach(pthread_t tid);
    int pthread_join(pthread_t thread, void **rval_ptr);

    int pthread_mutexattr_init(pthread_mutexattr_t *attr);
    int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);

    // macOS
    int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *attr, int prioceiling);
    int pthread_mutexattr_getprioceiling(pthread_mutexattr_t *attr, int *prioceiling);
    int pthread_mutexattr_setprotocol(pthread_mutexattr_t *attr, int protocol);
    int pthread_mutexattr_getprotocol(pthread_mutexattr_t *attr, int *protocol);

    // ubuntu
    int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
    int pthread_mutexattr_getpshared(const pthread_mutexattr_t *restrict attr, int *restrict pshared);
   
    int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
    int pthread_mutexattr_gettype(pthread_mutexattr_t *attr, int *type);

    int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
    int pthread_mutex_destroy(pthread_mutex_t *mutex);
    int pthread_mutex_lock(pthread_mutex_t *mutex);
    int pthread_mutex_trylock(pthread_mutex_t *mutex);
    int pthread_mutex_timedlock(pthread_mutex_t *mutex, struct timespec* t); /* not support in MacOS */
    int pthread_mutex_unlock(pthread_mutex_t *mutex);

    int pthread_rwlockattr_init(pthread_rwlockattr_t *attr);       
    int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr);
    int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, int pshared);
    int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *restrict attr, int *restrict pshared);

    int pthread_rwlock_init(pthread_rwlock_t *lock, const pthread_rwlockattr_t *attr);
    int pthread_rwlock_destroy(pthread_rwlock_t *lock);
    int pthread_rwlock_rdlock(pthread_rwlock_t *lock);
    int pthread_rwlock_tryrdlock(pthread_rwlock_t *lock);
    int pthread_rwlock_wrlock(pthread_rwlock_t *lock);
    int pthread_rwlock_trywrlock(pthread_rwlock_t *lock);
    int pthread_rwlock_unlock(pthread_rwlock_t *lock);
    int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rwlock, const struct timespec *restrict tsptr);
    int pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict rwlock, const struct timespec *restrict tsptr);

    int pthread_spin_destroy(pthread_spinlock_t *lock);
    int pthread_spin_init(pthread_spinlock_t *lock, int pshared);
    int pthread_spin_lock(pthread_spinlock_t *lock);
    int pthread_spin_trylock(pthread_spinlock_t *lock);
    int pthread_spin_unlock(pthread_spinlock_t *lock);

    int pthread_condattr_init(pthread_condattr_t *attr);
    int pthread_condattr_destroy(pthread_condattr_t *attr);
    int pthread_condattr_setpshared(pthread_condattr_t *attr, int pshared);
    int pthread_condattr_getpshared(const pthread_condattr_t *restrict attr, int *restrict pshared);
    int pthread_condattr_setclock(pthread_condattr_t *attr, clockid_t clock_id);
    int pthread_condattr_getclock(const pthread_condattr_t *restrict attr, clockid_t *restrict clock_id);

    int pthread_cond_destroy(pthread_cond_t *cond);
    int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
    int pthread_cond_timedwait(pthread_cond_t *restrict cond, 
             pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
    int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
    int pthread_cond_broadcast(pthread_cond_t *cond);
    int pthread_cond_signal(pthread_cond_t *cond);

    int pthread_barrierattr_destroy(pthread_barrierattr_t *attr);
    int pthread_barrierattr_init(pthread_barrierattr_t *attr);
    int pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared);
    int pthread_barrierattr_getpshared(const pthread_barrierattr_t *restrict attr, int *restrict pshared);

    int pthread_barrier_destroy(pthread_barrier_t *barrier);
    int pthread_barrier_init(pthread_barrier_t *restrict barrier,
                            const pthread_barrierattr_t *restrict attr, unsigned count);
    int pthread_barrier_wait(pthread_barrier_t *barrier);

    int pthread_key_create(pthread_key_t *key, void (*destructor)(void*));
    int pthread_key_delete(pthread_key_t key);
       
    pthread_once_t once_control = PTHREAD_ONCE_INIT;
    int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));

    void pthread_testcancel(void);
    int pthread_cancel(pthread_t thread)
    int pthread_setcancelstate(int state, int *oldstate);
    int pthread_setcanceltype(int type, int *oldtype);
    void pthread_cleanup_pop(int execute);
    void pthread_cleanup_push(void (*rtn)(void *), void *arg); 

    int pthread_sigmask(int how, const sigset_t * restrict set, sigset_t * restrict oset);
    int sigwait(const sigset_t *set, int *sig);
    int pthread_kill(pthread_t thread, int sig);
    int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));
