***********
poll Manual
***********

**NAME**
  
   poll, ppoll - wait for some event on a file descriptor

**SYNOPSIS**

   .. code-block:: c

      #include <poll.h>
      int poll(struct pollfd *fds, nfds_t nfds, int timeout);
      int ppoll(struct pollfd *fds, nfds_t nfds, const struct timespec *timeout_ts, const sigset_t *sigmask);

**DESCRIPTION**

   **poll()** performs a similar task to **select(2)**: it waits for one of a set 
   of file descriptors to become ready to perform I/O.

   The set of file descriptors to be monitored is specified in the fds argument, 
   which is an array of structures of the following form::

      struct pollfd {
          int   fd;         /* file descriptor */
          short events;     /* requested events */
          short revents;    /* returned events */
      };

   The caller should specify the number of items in the *fds* array in *nfds*.

   The field *fd* contains a file descriptor for an open file. If this field is negative, 
   then the corresponding events field is ignored and the *revents* field returns zero.  
   This provides an easy way of ignoring a file descriptor for a single *poll()* call: 
   simply negate the *fd* field.

   The field *events* is an input parameter, a bit mask specifying the events the application 
   is interested in for the file descriptor *fd*. If this field is specified as zero, then all 
   events are ignored for *fd* and *revents* returns zero.

   The field *revents* is an output parameter, filled by the kernel with the events that actually 
   occurred. The bits returned in *revents* can include any of those specified in *events*, or one of 
   the values POLLERR, POLLHUP, or POLLNVAL. (These three bits are meaningless in the *events* field, 
   and will be set in the *revents* field whenever the corresponding condition is true.)

   If none of the events requested (and no error) has occurred for any of the file descriptors, 
   then *poll()* blocks until one of the events occurs.

   The *timeout* argument specifies the number of milliseconds that *poll()* should block waiting for 
   a file descriptor to become ready. This interval will be rounded up to the system clock granularity, 
   and kernel scheduling delays mean that the blocking interval may overrun by a small amount. 

   Specifying a negative value in *timeout* means an infinite timeout. Specifying a *timeout* of zero 
   causes *poll()* to return immediately, even if no file descriptors are ready.

   The bits that may be set/returned in *events* and *revents* are defined in <*poll.h*>::

      POLLIN      There is data to read.
      POLLOUT     Writing now will not block.
      POLLERR     Error condition (output only).
      POLLHUP     Hang up (output only).
      POLLNVAL    Invalid request: fd not open (output only).

      POLLPRI
                     
      There is urgent data to read (e.g., out-of-band data on TCP socket; 
      pseudoterminal master in packet mode has seen state change in slave).

      POLLRDHUP (since Linux 2.6.17)
                     
      Stream socket peer closed connection, or shut down writing half of connection.  


   The relationship between *poll()* and *ppoll()* is analogous to the relationship between 
   *select(2)* and *pselect(2)*: like *pselect(2)*, *ppoll()* allows an application to safely 
   wait until either a file descriptor becomes ready or until a signal is caught.

   Other than the difference in the precision of the *timeout* argument, 
   the following *ppoll()* call::

      ready = ppoll(&fds, nfds, timeout_ts, &sigmask);

   is equivalent to atomically executing the following calls::

      sigset_t origmask;
      int timeout = (timeout_ts == NULL) ? -1 :
                (timeout_ts.tv_sec * 1000 + timeout_ts.tv_nsec / 1000000);
      sigprocmask(SIG_SETMASK, &sigmask, &origmask);
      ready = poll(&fds, nfds, timeout);
      sigprocmask(SIG_SETMASK, &origmask, NULL);

   See the description of *pselect(2)* for an explanation of why *ppoll()* is necessary.

   If the *sigmask* argument is specified as *NULL*, then no signal mask manipulation is performed 
   (and thus *ppoll()* differs from *poll()* only in the precision of the *timeout* argument).

   The *timeout_ts* argument specifies an upper limit on the amount of time that *ppoll()* will block.  
   This argument is a pointer to a structure of the following form::

      struct timespec {
          long    tv_sec;         /* seconds */
          long    tv_nsec;        /* nanoseconds */
      };

   If *timeout_ts* is specified as *NULL*, then *ppoll()* can block indefinitely.


**RETURN VALUE**

   On success, the number of descriptor(s) with events or errors reported is returned;  
   A value of 0 indicates that the call timed out and no file descriptors were ready. 
   On error, -1 is returned, and errno is set appropriately.