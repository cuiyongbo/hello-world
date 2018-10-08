*****************************************
accept -- accept a connection on a socket
*****************************************

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS

      #include <sys/types.h>
      #include <sys/socket.h>
      int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);

   The argument *socket* is a socket that has been created with *socket(2)*, bound to an
   *address* with *bind(2)*, and is listening for connections after a *listen(2)*.
   *accept()* extracts the first connection request on the queue of pending connections, 
   creates a new socket with the same properties of socket, and allocates a new file 
   descriptor for the socket. If no pending connections are present on the queue, and 
   the socket is not marked as non-blocking, *accept()* blocks the caller until a connection 
   is present. If the socket is marked non-blocking and no pending connections are present 
   on the queue, *accept()* returns an error as described below. The accepted socket may 
   not be used to accept more connections. The original socket socket, remains open.

   The argument *address* is a result parameter that is filled in with the address of
   the connecting entity, as known to the communications layer. The exact format of
   the *address* parameter is determined by the domain in which the communication is
   occurring. The *address_len* is a value-result parameter; it should initially contain 
   the amount of space pointed to by address; on return it will contain the actual length 
   (in bytes) of the address returned.  This call is used with connection-based socket types, 
   currently with *SOCK_STREAM*.

   It is possible to *select(2)* a socket for the purposes of doing an *accept()* by
   selecting it for read.

**RETURN VALUES**

   The call returns -1 on error and the global variable *errno* is set to indicate the
   error. If it succeeds, it returns a non-negative integer that is a descriptor for
   the accepted socket.
