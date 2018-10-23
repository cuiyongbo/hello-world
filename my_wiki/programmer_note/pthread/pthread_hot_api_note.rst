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