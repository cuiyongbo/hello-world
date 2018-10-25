********
Hot APIs
********

.. code-block:: c

   #include <pthread.h>

   pthread_t pthread_self(void);
   int pthread_equal(pthread_t t1, pthread_t t2);

   int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
                           void *(*start_routine)(void *), void *arg);

   void pthread_exit(void *rval_ptr);
   
   int pthread_detach(pthread_t tid);
   int pthread_join(pthread_t thread, void **rval_ptr);

   int pthread_cancel(pthread_t tid);
   void pthread_cleanup_pop(int execute);
   void pthread_cleanup_push(void (*rtn)(void *), void *arg); 

   int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
   int pthread_mutex_destroy(pthread_mutex_t *mutex);
   int pthread_mutex_lock(pthread_mutex_t *mutex);
   int pthread_mutex_trylock(pthread_mutex_t *mutex);
   int pthread_mutex_timedlock(pthread_mutex_t *mutex, struct timespec* t); /* not support in MacOS */
   int pthread_mutex_unlock(pthread_mutex_t *mutex);

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

   int pthread_cond_destroy(pthread_cond_t *cond);
   int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
   pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
   int pthread_cond_timedwait(pthread_cond_t *restrict cond, 
            pthread_mutex_t *restrict mutex,
           const struct timespec *restrict abstime);
   int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
   int pthread_cond_broadcast(pthread_cond_t *cond);
   int pthread_cond_signal(pthread_cond_t *cond);

   int pthread_barrier_destroy(pthread_barrier_t *barrier);
   int pthread_barrier_init(pthread_barrier_t *restrict barrier,
                           const pthread_barrierattr_t *restrict attr, unsigned count);
   int pthread_barrier_wait(pthread_barrier_t *barrier);