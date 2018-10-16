**********************************
create a pair of connected sockets
**********************************

**DESCRIPTION**

   .. code-block:: c
   
      #include <sys/types.h>
      #include <sys/socket.h>
      int socketpair(int domain, int type, int protocol, int sv[2]);
   
   The **socketpair()** call creates an unnamed pair of connected sockets 
   in the specified *domain*, of the specified *type*, and using the optionally 
   specified *protocol.* For further details of these arguments, see socket(2).
   
   The descriptors used in referencing the new sockets are returned in *sv[0]* 
   and *sv[1].*  The two sockets are indistinguishable.

**RETURN VALUE**

   On success, zero is returned.  
   On error, -1 is returned, and errno is set appropriately.

**NOTES**

   On Linux, the only supported domain for this call is **AF_UNIX** 
   (or synonymously, **AF_LOCAL**). (Most implementations have the same restriction.)

