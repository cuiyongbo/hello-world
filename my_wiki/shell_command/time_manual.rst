***********
time Manual
***********

**NAME**

   time - run programs and summarize system resource usage

**SYNOPSIS**

.. code-block:: sh

   time  [ -apqvV ] [ -f FORMAT ] [ -o FILE ]
         [ --append ] [ --verbose ] [ --quiet ] [ --portability ]
         [ --format=FORMAT ] [ --output=FILE ] [ --version ]
         [ --help ] COMMAND [ ARGS ]

**DESCRIPTION**

   time run the program *COMMAND* with any given arguments *ARG....*  
   When *COMMAND* finishes, time displays information about resources 
   used by *COMMAND* (on the standard error output, by default). If
   *COMMAND* exits with non-zero status, time displays a warning message 
   and the exit status.

   time determines which information to display about the resources used 
   by the *COMMAND* from the string *FORMAT*.  If no format is specified 
   on the command line, but the **TIME** environment variable is set, its 
   value is used as the format.  Otherwise, a default format built into 
   time is used.

   Options to time must appear on the command line before *COMMAND*. Anything 
   on the command line after *COMMAND* is passed as arguments to *COMMAND*.

**Example**

   .. code-block:: sh
   
      cherry scaffold$ time ./bad_code_no_opt 
      Result: 22515
      
      real  0m0.643s # Elapsed real (wall clock) time used by the process, includeing process scheduling, context switch.
      user  0m0.637s # Total number of CPU-seconds that the process used directly (in user mode).
      sys   0m0.002s # Total number of CPU-seconds used by the system on behalf of the process (in kernel mode).
   
**ACCURACY**

   The elapsed time is not collected atomically with the execution of the program; 
   as a result, in bizarre circumstances (if the time command gets stopped or swapped 
   out in between when the program being timed exits and when time calculates how long 
   it took to run), it could be much larger than the actual execution time.

   When the running time of a command is very nearly zero, some values (e.g., the percentage 
   of CPU used) may be reported as either zero (which is wrong) or a question mark.

   Most information shown by time is derived from the wait3(2) system call. The numbers are 
   only as good as those returned by wait3(2). On systems that do not have a wait3(2) call, 
   the times(2) system call is used instead. However, it provides much less information than 
   wait3(2), so on those systems time reports the majority of the resources as zero.
