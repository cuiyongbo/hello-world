***********
pipe Manual
***********

**SYNOPSIS**

   .. code-block:: c

      #include <unistd.h>
      int pipe(int pipefd[2]);

      #define _GNU_SOURCE             /* See feature_test_macros(7) */
      #include <fcntl.h>              /* Obtain O_* constant definitions */
      #include <unistd.h>
      int pipe2(int pipefd[2], int flags); /* Linux-specific */

**DESCRIPTION**

   *pipe()* creates a pipe,  a unidirectional data channel that can be used for interprocess communication.  
   The array pipefd is used to return two file descriptors referring to the ends of the pipe. *pipefd[0]* 
   refers to the read end of the pipe. *pipefd[1]* refers to the write end of the pipe.  Data written to 
   the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe. 
   For further details, see *pipe(7)*.

   If *flags* is 0, then *pipe2()* is the same as *pipe()*. The following values can be bitwise ORed 
   in *flags* to obtain different behavior::

      O_NONBLOCK
      Set the O_NONBLOCK file status flag on the two new open file descriptions.
      Using this flag saves extra calls to fcntl(2) to achieve the same result.

      O_CLOEXEC
      Set the close-on-exec (FD_CLOEXEC) flag on the two new file descriptors.

**RETURN VALUE**

   On success, zero is returned. On error, -1 is returned, and *errno* is set appropriately.
