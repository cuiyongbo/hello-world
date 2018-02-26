Pthreads Programming Exercise
=============================

Exercise 1
----------

+-----------------------------------------------------------+--------------------------------------------------------------------------+
| Filename                                                  | Description                                                              |
+===========================================================+==========================================================================+
| :download:`arrayloops.c <src_files/arrayloops.c>`         | Data decomposition by loop distribution.                                 |
+-----------------------------------------------------------+--------------------------------------------------------------------------+
| :download:`condvar.c <src_files/condvar.c>`               | Condition variable example.                                              |
+-----------------------------------------------------------+--------------------------------------------------------------------------+
| :download:`detached.c <src_files/detached.c>`             | Demonstrates how to explicitly create pthreads in a detached state.      |
+-----------------------------------------------------------+--------------------------------------------------------------------------+
| :download:`join.c <src_files/join.c>`                     | Demonstrates how to explicitly create pthreads in a joinable state.      |
+-----------------------------------------------------------+--------------------------------------------------------------------------+
| :download:`dotprod_mutex.c <src_files/dotprod_mutex.c>`   | Mutex variable example using a dot product program.                      |
+-----------------------------------------------------------+--------------------------------------------------------------------------+
| :download:`dotprod_serial.c <src_files/dotprod_serial.c>` | Ditto, but a serial version.                                             |
+-----------------------------------------------------------+--------------------------------------------------------------------------+
| :download:`hello32.c <src_files/hello32.c>`               | "Hello World" pthreads program demonstrating thread scheduling behavior. |
+-----------------------------------------------------------+--------------------------------------------------------------------------+
| :download:`hello_arg1.c <src_files/hello_arg1.c>`         | One correct way of passing the pthread_create() argument.                |
+-----------------------------------------------------------+--------------------------------------------------------------------------+
| :download:`hello_arg2.c <src_files/hello_arg2.c>`         | Ditto.                                                                   |
+-----------------------------------------------------------+--------------------------------------------------------------------------+
| :download:`hello_arg3.c <src_files/hello_arg3.c>`         | One incorrect way of passing the pthread_create() argument.              |
+-----------------------------------------------------------+--------------------------------------------------------------------------+

+---------------------------------------+---------------------------------------------------+---------------------------------------------+
| Bug Code                              | Bug Behavior                                      | Fix Code                                    |
+=======================================+===================================================+=============================================+
| :download:`bug1.c <src_files/bug1.c>` | Hang                                              | :download:`bug1fix.c <src_files/bug1fix.c>` |
+---------------------------------------+---------------------------------------------------+---------------------------------------------+
| :download:`bug2.c <src_files/bug2.c>` | Seg fault/coredump                                | :download:`bug2fix.c <src_files/bug2fix.c>` |
+---------------------------------------+---------------------------------------------------+---------------------------------------------+
| :download:`bug3.c <src_files/bug3.c>` | Wrong Answer                                      | :download:`bug3fix.c <src_files/bug3fix.c>` |
+---------------------------------------+---------------------------------------------------+---------------------------------------------+
| :download:`bug4.c <src_files/bug4.c>` | Hangs (usually)                                   | :download:`bug4fix.c <src_files/bug4fix.c>` |
+---------------------------------------+---------------------------------------------------+---------------------------------------------+
| :download:`bug5.c <src_files/bug5.c>` | Threads die and never get to do their work        | :download:`bug5fix.c <src_files/bug5fix.c>` |
+---------------------------------------+---------------------------------------------------+---------------------------------------------+
| :download:`bug6.c <src_files/bug6.c>` | Wrong answer - run it several times to prove this | :download:`bug6fix.c <src_files/bug6fix.c>` |
+---------------------------------------+---------------------------------------------------+---------------------------------------------+

.. note::

   EXPLANATION: bug3.c shows an unsafe way to pass the argument parameter in the pthread_create routine. It passes the address of t, rather than the value. As a result, each thread looks at the same location for their supposed unique instance of t. By the times the threads start, the thread creation loop is done and t is equal to 8 - usually. This means each thread gets an invalid and non-unique value for t.

.. note::

   EXPLANATION: bug4.c demonstrates a synchronization problem because the condition signal gets sent before the condition wait is posted. Plus, the waiting thread does not check to see if the condition it needs is true or not. So it blindly calls the condition wait and will hang forever. The solution bug4fix.c shows one way of overcoming this problem.
