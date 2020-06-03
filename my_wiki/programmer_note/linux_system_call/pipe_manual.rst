***********
pipe Manual
***********

.. code-block:: c
    :caption: SYNOPSIS

    #include <unistd.h>
    int pipe(int pipefd[2]);

    #define _GNU_SOURCE             /* See feature_test_macros(7) */
    #include <fcntl.h>              /* Obtain O_* constant definitions */
    #include <unistd.h>
    int pipe2(int pipefd[2], int flags); /* Linux-specific */


*pipe()* creates a pipe, a unidirectional data channel that can be used for interprocess communication.
The array pipefd is used to return two file descriptors referring to the ends of the pipe. *pipefd[0]*
refers to the read end of the pipe. *pipefd[1]* refers to the write end of the pipe.  Data written to
the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe.
For further details, see *pipe(7)*.

If *flags* is 0, then *pipe2()* is the same as *pipe()*. The following values can be bitwise ORed
in *flags* to obtain different behavior:

    - O_NONBLOCK
    - O_CLOEXEC

#. pipe with multiple writers

    POSIX.1 says that write(2)s of less than **PIPE_BUF** bytes must be atomic: the output data is written to the pipe
    as  a contiguous sequence. Writes of more than PIPE_BUF bytes may be nonatomic: the kernel may interleave the
    data with data written by other processes. POSIX.1 requires PIPE_BUF to be at least 512 bytes. (On Linux,
    PIPE_BUF is 4096 bytes.) The precise semantics depend on whether the file descriptor is nonblocking,
    whether there are multiple writers to the pipe, and on n, the number of bytes to be written:

        - O_NONBLOCK disabled, n <= PIPE_BUF

            All n bytes are written atomically; write(2) may block if there is not room
            for n bytes to be written immediately

        - O_NONBLOCK enabled, n <= PIPE_BUF

            If there is room to write n bytes to the pipe, then write(2) succeeds immediately, writing all n bytes;
            otherwise write(2) fails, with errno set to EAGAIN.

        - O_NONBLOCK disabled, n > PIPE_BUF

            The write is nonatomic: the data given to write(2) may be interleaved with write(2)s by other process;
            the write(2) blocks until n bytes have been written.

        - O_NONBLOCK enabled, n > PIPE_BUF

            If the pipe is full, then write(2) fails, with errno set to EAGAIN.  Otherwise, from 1 to n bytes may
            be written (i.e., a "partial write" may occur; the caller should check the return value  from  write(2)
            to  see  how many bytes were actually written), and these bytes may be interleaved with writes by other processes.

#. Application: In webbench, parent process uses pipe to communicate with child processes
