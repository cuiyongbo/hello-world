******************
getaddrinfo Manual
******************

**NAME**

   getaddrinfo, freeaddrinfo, gai_strerror - network address and service translation

**SYNOPSIS**

   .. code-block:: c

      #include <sys/types.h>
      #include <sys/socket.h>
      #include <netdb.h>

      int getaddrinfo(const char *node, const char *service,
                       const struct addrinfo *hints, struct addrinfo **res);

      void freeaddrinfo(struct addrinfo *res);
      const char *gai_strerror(int errcode);


**DESCRIPTION**

   Given node and service, which identify an Internet host and a service, 
   *getaddrinfo()* returns one or more addrinfo structures, each of which 
   contains an Internet address that can be specified in a call to *bind(2)* 
   or *connect(2)*. The *getaddrinfo()* function combines the functionality 
   provided by the *gethostbyname(3)* and *getservbyname(3)* functions into a 
   single interface, but unlike the latter functions, *getaddrinfo()* is **reentrant** 
   and allows programs to eliminate IPv4-versus-IPv6 dependencies.

   The *addrinfo* structure used by *getaddrinfo()* contains the following fields::

      struct addrinfo 
      {
          int              ai_flags;
          int              ai_family;
          int              ai_socktype;
          int              ai_protocol;
          socklen_t        ai_addrlen;
          struct sockaddr *ai_addr;
          char            *ai_canonname;
          struct addrinfo *ai_next;
      };

   The *hints* argument points to an addrinfo structure that specifies criteria 
   for selecting the socket address structures returned in the list pointed to by *res*.  
   If *hints* is not NULL it points to an addrinfo structure whose *ai_family*, *ai_socktype*, 
   and *ai_protocol* specify criteria that limit the set of socket addresses returned by *getaddrinfo()*, 
   as follows::

      ai_family   

      This field specifies the desired address family for the returned addresses.  
      Valid values for this field include AF_INET and AF_INET6. The value AF_UNSPEC 
      indicates that getaddrinfo() should return socket addresses for any address 
      family (either IPv4 or IPv6, for example) that can be used with node and service.

      ai_socktype 

      This field specifies the preferred socket type, for example SOCK_STREAM or SOCK_DGRAM.  
      Specifying 0 in this field indicates that socket addresses of any type can be returned by getaddrinfo().

      ai_protocol 

      This field specifies the protocol for the returned socket addresses.  
      Specifying 0 in this field indicates that socket addresses with any  
      protocol can be returned by getaddrinfo().

      ai_flags    

      This field specifies additional options, described below.  
      Multiple flags are specified by bitwise OR-ing them together.

      All the other fields in the structure pointed to by hints must 
      contain either 0 or a null pointer, as appropriate.

   Specifying *hints* as NULL is equivalent to setting ai_socktype and ai_protocol to 0; ai_family to AF_UNSPEC; 
   and ai_flags to (AI_V4MAPPED | AI_ADDRCONFIG). *node* specifies either a numerical network address (for IPv4, 
   numbers-and-dots notation as supported by *inet_aton(3)*; for IPv6, hexadecimal string format as supported by 
   *inet_pton(3)*), or a network hostname, whose network addresses are looked up and resolved. If *hints.ai_flags* 
   contains the *AI_NUMERICHOST* flag, then node must be a numerical network address. The AI_NUMERICHOST flag 
   suppresses any potentially lengthy network host address lookups.

   If the *AI_PASSIVE* flag is specified in *hints.ai_flags*, and *node* is NULL, then the returned socket addresses 
   will be suitable for bind(2)ing a socket that will accept(2) connections. The returned socket address will contain 
   the "wildcard  address" (*INADDR_ANY* for IPv4 addresses, *IN6ADDR_ANY_INIT* for IPv6 address). The wildcard address 
   is used by applications (typically servers) that intend to accept connections on any of the hosts's network addresses.  
   If *node* is not NULL, then the *AI_PASSIVE* flag is ignored.

   If the *AI_PASSIVE* flag is not set in *hints.ai_flags*, then the returned socket addresses will be suitable for use 
   with *connect(2)*, *sendto(2)*, or *sendmsg(2)*. If *node* is NULL, then the network address will be set to the loopback 
   interface address (*INADDR_LOOPBACK* for IPv4 addresses, *IN6ADDR_LOOPBACK_INIT* for IPv6 address); this is used by 
   applications that intend to communicate with peers running on the same host.

   *service* sets the port in each returned address structure. If this argument is a service name (see services(5)), 
   it is translated to the corresponding port number.  This argument can also be specified as a decimal number, which 
   is simply converted to binary. If *service* is NULL, then the port number of the returned socket addresses will be 
   left uninitialized. If *AI_NUMERICSERV* is specified in *hints.ai_flags* and *service* is not NULL, then *service* 
   must point to a string containing a numeric port number. This flag is used to inhibit the invocation of a name 
   resolution service in cases where it is known not to be required.

   Either *node* or *service*, but not both, may be NULL.

   The *freeaddrinfo()* function frees the memory that was allocated for the dynamically allocated linked list *res*.

   The *gai_strerror()* function translates these error codes return by *getaddrinfo()*  to a human readable string, 
   suitable for error reporting. [**Not strerr() or perror()**]

**EXAMPLE**

   The following programs demonstrate the use of *getaddrinfo()*, *gai_strerror()*, 
   *freeaddrinfo()*, and *getnameinfo(3)*.  The programs are an echo server and client 
   for UDP datagrams.

   .. code-block:: c
      :caption: Server program

      #include <sys/types.h>
      #include <stdio.h>
      #include <stdlib.h>
      #include <unistd.h>
      #include <string.h>
      #include <sys/socket.h>
      #include <netdb.h>
      
      #define BUF_SIZE 500
      
      int main(int argc, char *argv[])
      {
          if (argc != 2) {
              fprintf(stderr, "Usage: %s port\n", argv[0]);
              exit(EXIT_FAILURE);
          }
      
          struct addrinfo hints;
          memset(&hints, 0, sizeof(struct addrinfo));
          hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
          hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
          hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
          hints.ai_protocol = 0;          /* Any protocol */
          hints.ai_canonname = NULL;
          hints.ai_addr = NULL;
          hints.ai_next = NULL;
      
          struct addrinfo *result, *rp;
          int s = getaddrinfo(NULL, argv[1], &hints, &result);
          if (s != 0) {
              fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
              exit(EXIT_FAILURE);
          }
      
          /* getaddrinfo() returns a list of address structures.
             Try each address until we successfully bind(2).
             If socket(2) (or bind(2)) fails, we (close the socket
             and) try the next address. */
      
          int sockFd;
          for (rp = result; rp != NULL; rp = rp->ai_next) 
          {
              sockFd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
              if (sockFd == -1)
                  continue;
      
              if (bind(sockFd, rp->ai_addr, rp->ai_addrlen) == 0)
                  break;                  /* Success */
      
               close(sockFd);
          }
      
          if (rp == NULL) {               /* No address succeeded */
              fprintf(stderr, "Could not bind\n");
              exit(EXIT_FAILURE);
          }
      
          freeaddrinfo(result);           /* No longer needed */
      
           /* Read datagrams and echo them back to sender */
      
          char buf[BUF_SIZE];
          for (;;) 
          {
              struct sockaddr_storage peerAddr;
              socklen_t peerAddrLen = sizeof(struct sockaddr_storage);
              ssize_t nread = recvfrom(sockFd, buf, BUF_SIZE, 0, (struct sockaddr *) &peerAddr, &peerAddrLen);
              if (nread == -1)
                  continue;               /* Ignore failed request */
      
              char host[NI_MAXHOST], service[NI_MAXSERV];
              s = getnameinfo((struct sockaddr *) &peerAddr,
                                     peerAddrLen, host, NI_MAXHOST,
                                     service, NI_MAXSERV, NI_NUMERICSERV);
              if (s == 0)
                   printf("Received %zd bytes from %s:%s\n", nread, host, service);
              else
                   fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
      
              if (sendto(sockFd, buf, nread, 0, (struct sockaddr *) &peerAddr, peerAddrLen) != nread)
                  fprintf(stderr, "Error sending response\n");
          }
      
          return 0;
      }


   .. code-block:: c
      :caption: Client program

      #include <sys/types.h>
      #include <sys/socket.h>
      #include <netdb.h>
      #include <stdio.h>
      #include <stdlib.h>
      #include <unistd.h>
      #include <string.h>
      
      #define BUF_SIZE 500
      
      int main(int argc, char *argv[])
      {
          if (argc < 3) {
              fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
              exit(EXIT_FAILURE);
          }
      
          struct addrinfo hints;
          struct addrinfo *result, *rp;
          memset(&hints, 0, sizeof(struct addrinfo));
          hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
          hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
          hints.ai_flags = 0;
          hints.ai_protocol = 0;          /* Any protocol */
      
          int s = getaddrinfo(argv[1], argv[2], &hints, &result);
          if (s != 0) {
              fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
              exit(EXIT_FAILURE);
          }
      
          /* getaddrinfo() returns a list of address structures.
             Try each address until we successfully connect(2).
             If socket(2) (or connect(2)) fails, we (close the socket
             and) try the next address. */
      
          int sfd;
          for (rp = result; rp != NULL; rp = rp->ai_next) 
          {
              sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
              if (sfd == -1)
                  continue;
      
              if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
                  break;                  /* Success */
      
              close(sfd);
          }
      
          if (rp == NULL) {               /* No address succeeded */
             fprintf(stderr, "Could not connect\n");
             exit(EXIT_FAILURE);
          }
      
          freeaddrinfo(result);           /* No longer needed */
      
          /* Send remaining command-line arguments as separate
             datagrams, and read responses from server */
      
          int j;
          char buf[BUF_SIZE];
          for (j = 3; j < argc; j++) 
          {
              size_t len = strlen(argv[j]) + 1; /* +1 for terminating null byte */
              if (len + 1 > BUF_SIZE) {
                  fprintf(stderr, "Ignoring long message in argument %d\n", j);
                  continue;
              }
      
              if (write(sfd, argv[j], len) != len) {
                  fprintf(stderr, "partial/failed write\n");
                  exit(EXIT_FAILURE);
              }
      
              ssize_t nread = read(sfd, buf, BUF_SIZE);
              if (nread == -1) {
                  perror("read");
                  exit(EXIT_FAILURE);
              }
      
              printf("Received %zd bytes: %s\n", nread, buf);
          }
      
          exit(EXIT_SUCCESS);
      }     