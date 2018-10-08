******************
Socket Helper APIs
******************

.. contents::
   :local:

getsockname & getpeername
=========================

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS
         
      #include <sys/socket.h>

      /*getsockname - get socket name*/
      int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

      /*get name of connected peer socket*/
      int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

   *getsockname()* returns the current address to which the socket *sockfd* is bound, 
   in the buffer pointed to by *addr*. The *addrlen* argument should be initialized to 
   indicate the amount of space (in bytes) pointed to by *addr*. On return it contains 
   the actual size of the socket address.

   The returned address is truncated if the buffer provided is too small; 
   in this case, addrlen will return a value greater than was supplied to the call.

   Other than returning the peer's address, *getpeername()* is identical to *getsockname()*.

**RETURN VALUE**

   On success, zero is returned. On error, -1 is returned, 
   and *errno* is set appropriately.


Convert values between host and network byte order
==================================================

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS
      
      #include <arpa/inet.h>
      uint32_t htonl(uint32_t hostlong);
      uint16_t htons(uint16_t hostshort);
      uint32_t ntohl(uint32_t netlong);
      uint16_t ntohs(uint16_t netshort);

   The h stands for "host" byteorder, n stands for "network" byteorder; 
   l stands for long (4 bytes) integer, and the s stands for short (2 bytes) integer.

   On the i386 the host byte order is :abbr:`LSB (Least Significant Byte)` first, 
   whereas the network byte order, as used on the Internet, is :abbr:`MSB (Most Significant Byte)` first.


Convert IPv4 and IPv6 addresses from binary to text form
========================================================

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS
      
      #include <arpa/inet.h>
      const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);

   This function converts the network address structure *src* in the *af* address family 
   into a character string. The resulting string is copied to the buffer pointed to by *dst*, 
   which must be a non-null pointer. The caller specifies the number of bytes available 
   in this buffer in the argument *size*.

   The following address families are currently supported::

      AF_INET
      src points to a struct in_addr (in  network  byte  order)
      which is converted to an IPv4 network address in the dotted-decimal format,
      "ddd.ddd.ddd.ddd". The buffer dst must be at least INET_ADDRSTRLEN bytes long.

      AF_INET6
      src points to a struct in6_addr (in network byte order) which is converted 
      to a representation of this address in the most appropriate IPv6 network
      address format for this address. The buffer dst must be at least 
      INET6_ADDRSTRLEN bytes long.

**RETURN VALUE**

   On success, i*net_ntop()* returns a non-null pointer to *dst*.  
   *NULL* is returned if there was an error, with *errno* set to indicate the error.


convert IPv4 and IPv6 addresses from text to binary form
========================================================

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS
      
      #include <arpa/inet.h>
      int inet_pton(int af, const char *src, void *dst);

   This function converts the character string *src* into a network address structure 
   in the *af* address family, then copies the network address structure to *dst*.  

   The following address families are currently supported::

      AF_INET
      src points to a character string containing an IPv4 network address 
      in dotted-decimal format, "ddd.ddd.ddd.ddd", where ddd is a decimal 
      number of up to three digits in the range 0 to 255. The address is 
      converted to a struct in_addr and copied to dst, which must be 
      sizeof(struct in_addr) (4 bytes) long.

      AF_INET6
      src points to a character string containing an IPv6 network address.  
      The address is converted to a struct in6_addr and copied to dst, 
      which must be sizeof(struct in6_addr) (16 bytes) long.

**RETURN VALUE**

   *inet_pton()* returns 1 on success. 0 is returned if src does not contain 
   a character string representing a valid network address in the specified 
   address family. If af does not contain a valid address family, -1 is 
   returned and *errno* is set to EAFNOSUPPORT.


getsockopt, setsockopt - get and set options on sockets
=======================================================

**DESCRIPTION**

   .. code-block:: c
      :caption: SYNOPSIS
   
      #include <sys/types.h>         
      #include <sys/socket.h>
      int getsockopt(int sockfd, int level, int optname,
                     void *optval, socklen_t *optlen);
      int setsockopt(int sockfd, int level, int optname,
                         const void *optval, socklen_t optlen);

   *getsockopt()* and *setsockopt()* manipulate options for the socket 
   referred to by the file descriptor *sockfd.*  Options may exist at 
   multiple protocol levels; they are always present at the uppermost 
   socket level.

   When manipulating socket options, the level at which the option resides 
   and the name of the option must be specified. To manipulate options at 
   the sockets API level, level is specified as **SOL_SOCKET.** To manipulate 
   options at any other level the protocol number of the appropriate protocol 
   controlling the option is supplied. For example, to indicate that an option 
   is to be interpreted by the TCP protocol, level should be set to the protocol 
   number of TCP; see *getprotoent(3).*

   The arguments *optval* and *optlen* are used to access option values for *setsockopt().*  
   For *getsockopt()* they identify a buffer in which the value for the requested 
   option(s) are to be returned. For *getsockopt(),* *optlen* is a value-result argument,
   initially containing the size of the buffer pointed to by *optval*, and modified on 
   return to indicate the actual size of the value returned. If no option value is to 
   be supplied or returned, optval may be NULL.

   *Optname* and any specified options are passed uninterpreted to the appropriate protocol 
   module for interpretation. The include file **<sys/socket.h>** contains definitions 
   for socket level options, described below. Options at other protocol levels vary in 
   format and name; consult the appropriate entries in section 4 of the manual.

   Most socket-level options utilize an int argument for optval. 
   For setsockopt(), the argument should be nonzero to enable a
   boolean option, or zero if the option is to be disabled.

   For a description of the available socket options see *socket(7)* 
   and the appropriate protocol man pages.

**RETURN VALUE**

   On success, zero is returned for the standard options. 
   On error, -1 is returned, and errno is set appropriately.

   Netfilter allows the programmer to define custom socket 
   options with associated handlers; for such options, 
   the return value on success is the value returned by the handler.
