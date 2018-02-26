Creating and Terminating Threads
================================

Routines
--------

.. code-block:: c
   
   pthread_create (thread,attr,start_routine,arg)
   pthread_exit (status)
   pthread_cancel (thread)
   pthread_attr_init (attr)
   pthread_attr_destroy (attr)


Creating Threads
----------------

* Initially, your ``main()`` program comprises a single, default thread. All other threads must be explicitly created by the programmer.
  
* ``pthread_create`` creates a new thread and makes it executable. This routine can be called any number of times from anywhere within your code.
  
* ``pthread_create`` arguments:
  
   * ``thread``: An opaque, unique identifier for the new thread returned by the subroutine.
   * ``attr``: An opaque attribute object that may be used to set thread attributes. You can specify a thread attributes object, or ``NULL`` for the default values.
   * ``start_routine``: the C routine that the thread will execute once it is created.
   * ``arg``: A single argument that may be passed to ``start_routine``. It must be passed by reference as a pointer cast of type void. ``NULL`` may be used if no argument is to be passed.

* The maximum number of threads that may be created by a process is implementation dependent. Programs that attempt to exceed the limit can fail or produce wrong results.

* Querying and setting your implementation's thread limit - Linux example shown. Demonstrates querying the default (soft) limits and then setting the maximum number of processes (including threads) to the hard limit. Then verifying that the limit has been overridden.

.. code-block:: bash
  
   $ ulimit -a
   core file size          (blocks, -c) unlimited
   data seg size           (kbytes, -d) unlimited
   file size               (blocks, -f) unlimited
   open files                      (-n) 256
   pipe size            (512 bytes, -p) 8
   stack size              (kbytes, -s) 2032
   cpu time               (seconds, -t) unlimited
   max user processes              (-u) 256 # current limit
   virtual memory          (kbytes, -v) unlimited

   $ ulimit  -Hu # maximum of user process OS surpports
   256

   $ ulimit  -u 128

   $ ulimit -a
   core file size          (blocks, -c) unlimited
   data seg size           (kbytes, -d) unlimited
   file size               (blocks, -f) unlimited
   open files                      (-n) 256
   pipe size            (512 bytes, -p) 8
   stack size              (kbytes, -s) 2032
   cpu time               (seconds, -t) unlimited
   max user processes              (-u) 128
   virtual memory          (kbytes, -v) unlimited

* Once created, threads are peers, and may create other threads. There is no implied hierarchy or dependency between threads.
  
.. image:: images/peerThreads.png


Thread Attributes
-----------------

* By default, a thread is created with certain attributes. Some of these attributes can be changed by the programmer via the thread attribute object. ``pthread_attr_init`` and ``pthread_attr_destroy`` are used to initialize/destroy the thread attribute object.

* Other routines are then used to query/set specific attributes in the thread attribute object. Attributes include:

   * Detached or joinable state
   * Scheduling inheritance
   * Scheduling policy
   * Scheduling parameters
   * Scheduling contention scope
   * Stack size
   * Stack address
   * Stack guard (overflow) size

* Some of these attributes will be discussed later.


Thread Binding and Scheduling
-----------------------------

.. note::

   Question: After a thread has been created, how do you know a)when it will be scheduled to run by the operating system, and b)which processor/core it will run on? 

   |

   ANSWER: Unless you are using the Pthreads scheduling mechanism, it is up to the implementation and/or OS to decide where and when threads will execute. Robust programs should not depend upon threads executing in a specific order or on a specific processor/core.

* The Pthreads API provides several routines that may be used to specify how threads are scheduled for execution. For example, threads can be scheduled to run :abbr:`FIFO (first-in first-out)`, :abbr:`RR (round-robin)` , :abbr:`OTHER (operating system determines)`. It also provides the ability to set a thread's scheduling priority value.

* These topics are not covered here, however a good overview of "how things work" under Linux can be found in the ``sched_setscheduler`` man page.

* The Pthreads API does not provide routines for binding threads to specific cpus/cores. However, local implementations may include this functionality - such as providing the non-standard ``pthread_setaffinity_np`` routine. Note that "_np" in the name stands for "non-portable".

* Also, the local operating system may provide a way to do this. For example, Linux provides the ``sched_setaffinity`` routine.


Terminating Threads & pthread_exit()
------------------------------------

* There are several ways in which a thread may be terminated:
  
   * The thread returns normally from its starting routine. Its work is done.
   * The thread makes a call to the ``pthread_exit`` subroutine - whether its work is done or not.
   * The thread is canceled by another thread via the ``pthread_cancel`` routine.
   * The entire process is terminated due to making a call to either the ``exec()`` or ``exit()``.
   * If ``main()`` finishes first, without calling ``pthread_exit`` explicitly itself.
     
* The ``pthread_exit()`` routine allows the programmer to specify an optional termination ``status`` parameter. This optional parameter is typically returned to threads "joining" the terminated thread (covered later).

* In subroutines that execute to completion normally, you can often dispense with calling ``pthread_exit()`` - unless, of course, you want to pass the optional ``status`` code back.
  
* Cleanup: the ``pthread_exit()`` routine does not close files; any files opened inside the thread will remain open after the thread is terminated.
  
* Discussion on calling ``pthread_exit()`` from ``main()``:
  
   * There is a definite problem if ``main()`` finishes before the threads it spawned if you don't call ``pthread_exit()`` explicitly. All of the threads it created will terminate because ``main()`` is done and no longer exists to support the threads.
   * By having ``main()`` explicitly call ``pthread_exit()`` as the last thing it does, ``main()`` will block and be kept alive to support the threads it created until they are done.
     

Example: Pthread Creation and Termination
-----------------------------------------

This simple example code creates 5 threads with the ``pthread_create()`` routine. Each thread prints a "Hello World!" message, and then terminates with a call to ``pthread_exit()``.

:download:`View source code <src_files/hello.c>`
