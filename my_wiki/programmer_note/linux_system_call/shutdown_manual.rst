******************************************
Shut down part of a full-duplex connection
******************************************

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS
   
      #include <sys/socket.h>
      int shutdown(int socket, int how);


   The ``shutdown()`` call causes all or part of a full-duplex connection on the socket 
   associated with *socket* to be shut down. If *how* is ``SHUT_RD``, further receives will be disallowed.
   If *how* is ``SHUT_WR``, further sends will be disallowed.  If *how* is ``SHUT_RDWR``, further sends and 
   receives will be disallowed.

**RETURN VALUES**

   The ``shutdown()`` function returns the value 0 if successful; otherwise the value -1 
   is returned and the global variable *errno* is set to indicate the error.


.. note::

   Given that we can close a socket, why is shutdown needed? There are several
   reasons. First, close will deallocate the network endpoint only when the last active
   reference is closed. If we duplicate the socket (with dup, for example), the socket won’t
   be deallocated until we close the last file descriptor referring to it. The shutdown
   function allows us to deactivate a socket independently of the number of active file
   descriptors referencing it. Second, it is sometimes convenient to shut a socket down in
   one direction only. For example, we can shut a socket down for writing if we want the
   process we are communicating with to be able to tell when we are done transmitting
   data, while still allowing us to use the socket to receive data sent to us by the process.