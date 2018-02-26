Pthreads Programming Exercise
=============================

Exercise 1
----------

Overview
^^^^^^^^

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

   EXPLANATION: **bug3.c** shows an unsafe way to pass the argument parameter in the pthread_create routine. It passes the address of t, rather than the value. As a result, each thread looks at the same location for their supposed unique instance of t. By the times the threads start, the thread creation loop is done and t is equal to 8 - usually. This means each thread gets an invalid and non-unique value for t.

.. note::

   EXPLANATION: **bug4.c** demonstrates a synchronization problem because the condition signal gets sent before the condition wait is posted. Plus, the waiting thread does not check to see if the condition it needs is true or not. So it blindly calls the condition wait and will hang forever. The solution bug4fix.c shows one way of overcoming this problem.


Thread Scheduling
^^^^^^^^^^^^^^^^^

* Review the example code **hello32.c**. Note that it will create 32 threads. A ``sleep();`` statement has been introduced to help insure that all threads will be in existence at the same time. Also, each thread performs actual work to demonstrate how the OS scheduler behavior determines the order of thread completion.

* Compile and run the program. Notice the order in which thread output is displayed. Is it ever in the same order? How is this explained?


Argument Passing
^^^^^^^^^^^^^^^^

* Review the **hello_arg1.c** and **hello_arg2.c** example codes. Notice how the single argument is passed and how to pass multiple arguments through a structure.

* Compile and run both programs, and observe output.

* Now review, compile and run the **bug3.c** program. What's wrong? How would you fix it? See the explanation in the bug programs table above.
  

Thread Exiting
^^^^^^^^^^^^^^

* Review, compile (for gcc include the **-lm** flag) and run the **bug5.c** program.

* What happens? Why? How would you fix it?
  

Thread Joining
^^^^^^^^^^^^^^

* Review, compile (for gcc include the **-lm** flag) and run the **join.c** program.

* Modify the program so that threads send back a different return code - you pick. Compile and run. Did it work?

* For comparison, review, compile (for gcc include the **-lm** flag) and run the **detached.c** example code.

* Observe the behavior and note there is no "join" in this example.


Stack Management
^^^^^^^^^^^^^^^^

* Review, compile and run the **bug2.c** program.
  
* What happens? Why? How would you fix it?


Exercise 2
----------

Mutexes
^^^^^^^

* Review, compile and run the **dotprod_serial.c** program. As its name implies, it is serial - no threads are created.
  
* Now review, compile and run the **dotprod_mutex.c** program. This version of the dotprod program uses threads and requires a mutex to protect the global *sum* as each thread updates it with their partial sums.
  
* Execute the **dotprod_mutex** program several times and notice that the order in which threads update the global *sum* varies.
  
* Review, compile and run the **bug6.c** program.
  
* Run it several times and notice what the global *sum* is each time? See if you can figure out why and fix it. The explanation is provided in the bug examples table above, and an example solution is provided by the **bug6fix.c** program.
  
* The **arrayloops.c** program is another example of using a mutex to protect updates to a global *sum*. Feel free to review, compile and run this example code as well.
 

Condition Variables
^^^^^^^^^^^^^^^^^^^

* Review, compile and run the **condvar.c** program. This example is essentially the same as the shown in the tutorial. Observe the output of the three threads.
  
* Now, review, compile and run the **bug1.c** program. Observe the output of the five threads. What happens? See if you can determine why and fix the problem. 

* The **bug4.c** program is yet another example of what can go wrong when using condition variables. 
   
* Review, compile (for gcc include the **-lm** flag) and run the code. Observe the output and then see if you can fix the problem. 


