*************
listen Manual
*************

**NAME**

   listen -- listen for connections on a socket

**SYNOPSIS**

   .. code-block:: c
   
      #include <sys/socket.h>
      #include <sys/types.h>
      int listen(int socket, int backlog);

**DESCRIPTION**

   Creation of socket-based connections requires several operations. First, a socket is created
   with *socket(2)*. Next, a willingness to accept incoming connections and a queue limit for
   incoming connections are specified with *listen()*. Finally, the connections are accepted with
   *accept(2)*. **The listen() call applies only to sockets of type SOCK_STREAM.**

   The *backlog* parameter defines the maximum length for the queue of pending connections. If a
   connection request arrives with the queue full, the client may receive an error with an indication 
   of *ECONNREFUSED*.  The *backlog* is currently limited (silently) to 128. Alternatively, if the 
   underlying protocol supports retransmission, the request may be ignored so that retries may succeed.

**RETURN VALUES**
   
   The *listen()* function returns the value 0 if successful; otherwise the value -1 is returned
   and the global variable *errno* is set to indicate the error.

**ERRORS**

   *listen()* will fail if::

      [EACCES]           The current process has insufficient privileges.
      [EBADF]            The argument socket is not a valid file descriptor.
      [EDESTADDRREQ]     The socket is not bound to a local address and the protocol does not support listening on an unbound socket.
      [EINVAL]           socket is already connected.
      [ENOTSOCK]         The argument socket does not reference a socket.
      [EOPNOTSUPP]       The socket is not of a type that supports the operation listen().

