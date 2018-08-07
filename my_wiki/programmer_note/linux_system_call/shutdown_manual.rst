***************
shutdown Manual
***************

**NAME**
   
   shutdown -- shut down part of a full-duplex connection

.. code-block:: c
   :caption: SYNOPSIS

   #include <sys/socket.h>
   int shutdown(int socket, int how);

**DESCRIPTION**

   The ``shutdown()`` call causes all or part of a full-duplex connection on the socket 
   associated with *socket* to be shut down. If *how* is ``SHUT_RD``, further receives will be disallowed.
   If *how* is ``SHUT_WR``, further sends will be disallowed.  If *how* is ``SHUT_RDWR``, further sends and 
   receives will be disallowed.

**RETURN VALUES**

   The ``shutdown()`` function returns the value 0 if successful; otherwise the value -1 
   is returned and the global variable *errno* is set to indicate the error.

**ERRORS**
   
   The call succeeds unless::

      [EBADF]            Socket is not a valid descriptor.
      [EINVAL]           The how argument is invalid.
      [ENOTCONN]         The specified socket is not connected.
      [ENOTSOCK]         Socket is a file, not a socket.

