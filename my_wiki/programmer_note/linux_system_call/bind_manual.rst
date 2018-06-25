***********
bind Manual
***********

**NAME**
    
   bind - bind a name to a socket

**SYNOPSIS**

   .. code-block:: c

      #include <sys/types.h>          /* See NOTES */
      #include <sys/socket.h>
      int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

**DESCRIPTION**

   When a socket is created with *socket(2)*, it exists in a name space (address family) but has no address 
   assigned to it. *bind()* assigns the address specified by *addr* to the socket referred to by the file 
   descriptor *sockfd*.  *addrlen* specifies the size, in bytes, of the address structure pointed to by *addr*.  
   Traditionally, this operation is called “assigning a name to a socket”.

   It is normally necessary to assign a local address using *bind()* before a *SOCK_STREAM* socket may 
   receive connections (see accept(2)).

   The rules used in name binding vary between address families. Consult the manual entries in Section 7 
   for detailed information. For *AF_INET* see *ip(7)*, for AF_INET6 see ipv6(7), for AF_UNIX see unix(7), 
   for AF_APPLETALK see ddp(7), for AF_PACKET see packet(7), for AF_X25 see x25(7) and for AF_NETLINK see netlink(7).

   The actual structure passed for the *addr* argument will depend on the address family.  
   The *sockaddr* structure is defined as something like::

      struct sockaddr 
      {
          sa_family_t sa_family;
          char        sa_data[14];
      }

   The only purpose of this structure is to cast the structure pointer passed in *addr* 
   in order to avoid compiler warnings.

**RETURN VALUE**
   
   On success, zero is returned.  On error, -1 is returned, 
   and *errno* is set appropriately.

**ERRORS**

    *bind()* will fail if::

      EACCES The address is protected, and the user is not the superuser.
      EADDRINUSE The given address is already in use.
      EBADF  sockfd is not a valid descriptor.
      EINVAL The socket is already bound to an address.
      ENOTSOCK sockfd is a descriptor for a file, not a socket.

   The following errors are specific to UNIX domain (AF_UNIX) sockets::

      EACCES         Search permission is denied on a component of the path prefix.  (See also path_resolution(7).)
      EADDRNOTAVAIL  A nonexistent interface was requested or the requested address was not local.
      EFAULT         addr points outside the user's accessible address space.
      EINVAL         The addrlen is wrong, or the socket was not in the AF_UNIX family.
      ELOOP          Too many symbolic links were encountered in resolving addr.
      ENAMETOOLONG   addr is too long.
      ENOENT         The file does not exist.
      ENOMEM         Insufficient kernel memory was available.
      ENOTDIR        A component of the path prefix is not a directory.
      EROFS          The socket inode would reside on a read-only filesystem.


**EXAMPLE**

   An example of the use of **bind()** with 
   Internet domain sockets can be found in *getaddrinfo(3)*.

   The following example shows how to bind a stream socket in 
   the UNIX (*AF_UNIX*) domain, and accept connections::

      #include <sys/socket.h>
      #include <sys/un.h>
      #include <stdlib.h>
      #include <stdio.h>
      #include <string.h>
      
      #define MY_SOCK_PATH "/somepath"
      #define LISTEN_BACKLOG 50
      
      #define FAIL(msg) \
                 do { perror(msg); exit(EXIT_FAILURE); } while (0)
      
      int main(int argc, char *argv[])
      {
           int sfd = socket(AF_UNIX, SOCK_STREAM, 0); 
           if (sfd == -1) 
               FAIL("socket");
      
           struct sockaddr_un myAddr;
           memset(&myAddr, 0, sizeof(struct sockaddr_un));
           myAddr.sun_family = AF_UNIX;
           strncpy(myAddr.sun_path, MY_SOCK_PATH, sizeof(myAddr.sun_path) - 1); 
      
           if (bind(sfd, (struct sockaddr *) &myAddr, sizeof(struct sockaddr_un)) == -1) 
                FAIL("bind");
      
           if (listen(sfd, LISTEN_BACKLOG) == -1) 
                FAIL("listen");
            
           struct sockaddr_un peerAddr;
           socklen_t peerAddrSize = sizeof(struct sockaddr_un);
           int cfd = accept(sfd, (struct sockaddr *) &peerAddr, &peerAddrSize);
           if (cfd == -1) 
              FAIL("accept");
      
           /* Code to deal with incoming connection(s)... */
      
           /* When no longer required, the socket pathname, MY_SOCK_PATH
                    should be deleted using unlink(2) or remove(3) */
      }



