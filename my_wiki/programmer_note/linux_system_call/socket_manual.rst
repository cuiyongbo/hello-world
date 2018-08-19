*************
socket Manual
*************

**NAME**
     
   socket -- create an endpoint for communication

**SYNOPSIS**

   .. code-block:: c

      #include <sys/socket.h>
      #include <sys/types.h>
      int socket(int domain, int type, int protocol);

**DESCRIPTION**

   *socket()* creates an endpoint for communication and returns a descriptor.

   The *domain* parameter specifies a communications domain within which communication will take
   place; this selects the protocol family which should be used. These families are defined in
   the include file <*sys/socket.h*>.  The currently understood formats are::

      PF_LOCAL        Host-internal protocols, formerly called PF_UNIX,
      PF_UNIX         Host-internal protocols, deprecated, use PF_LOCAL,
      PF_INET         Internet version 4 protocols,
      PF_ROUTE        Internal Routing protocol,
      PF_KEY          Internal key-management function,
      PF_INET6        Internet version 6 protocols,
      PF_SYSTEM       System domain,
      PF_NDRV         Raw access to network device

   The socket has the indicated *type*, which specifies the semantics of communication. Currently
   defined types are::

      SOCK_STREAM
      SOCK_DGRAM
      SOCK_RAW

   A *SOCK_STREAM* type provides sequenced, reliable, two-way connection based byte streams. An
   out-of-band data transmission mechanism may be supported. A *SOCK_DGRAM* socket supports 
   datagrams (connectionless, unreliable messages of a fixed (typically small) maximum length).
   *SOCK_RAW* sockets provide access to internal network protocols and interfaces. The type
   *SOCK_RAW*, which is available only to the super-user.

   The *protocol* specifies a particular protocol to be used with the socket. Normally only a
   single protocol exists to support a particular socket type within a given protocol family.
   However, it is possible that many protocols may exist, in which case a particular protocol
   must be specified in this manner. The protocol number to use is particular to the 
   communication domain in which communication is to take place; see *protocols(5)*.

   Sockets of type *SOCK_STREAM* are full-duplex byte streams, similar to pipes. A stream socket
   must be in a connected state before any data may be sent or received on it. A connection to
   another socket is created with a *connect(2)* call. Once connected, data may be transferred 
   using *read(2)* and *write(2)* calls or some variant of the *send(2)* and *recv(2)*
   calls.  When a session has been completed a *close(2)* may be performed. Out-of-band data may
   also be transmitted as described in *send(2)* and received as described in *recv(2)*.

   The communications protocols used to implement a *SOCK_STREAM* insure that data is not lost or
   duplicated. If a piece of data for which the peer protocol has buffer space cannot be suc-
   cessfully transmitted within a reasonable length of time, then the connection is considered
   broken and calls will indicate an error with -1 returns and with *ETIMEDOUT* as the specific
   code in the global variable *errno*. The protocols optionally keep sockets "warm" by forcing
   transmissions roughly every minute in the absence of other activity. An error is then 
   indicated if no response can be elicited on an otherwise idle connection for a extended period
   (e.g. 5 minutes). A *SIGPIPE* signal is raised if a process sends on a broken stream; this
   causes naive processes, which do not handle the signal, to exit.

   *SOCK_DGRAM* and *SOCK_RAW* sockets allow sending of datagrams to correspondents named in 
   *send(2)* calls. Datagrams are generally received with *recvfrom(2)*, which returns the next 
   datagram with its return address.

   An *fcntl(2)* call can be used to specify a process group to receive a *SIGURG* signal when the
   out-of-band data arrives. It may also enable non-blocking I/O and asynchronous notification
   of I/O events via *SIGIO*.

   The operation of sockets is controlled by socket level options. These options are defined in
   the file <*sys/socket.h*>.  *setsockopt(2)* and *getsockopt(2)* are used to set and get 
   options, respectively.

**RETURN VALUES**

   A -1 is returned if an error occurs, otherwise the return value is a descriptor referencing
   the socket.

**ERRORS**

   The socket() system call fails if::

      [EACCES]           Permission to create a socket of the specified type and/or protocol is denied.
      [EAFNOSUPPORT]     The specified address family is not supported.
      [EMFILE]           The per-process descriptor table is full.
      [ENFILE]           The system file table is full.
      [ENOBUFS]          Insufficient buffer space is available. The socket cannot be created
                         until sufficient resources are freed.
      [ENOMEM]           Insufficient memory was available to fulfill the request.
      [EPROTONOSUPPORT]  The protocol type or the specified protocol is not supported within this domain.
      [EPROTOTYPE]       The socket type is not supported by the protocol.

   If a new protocol family is defined, the socreate process is free to return any desired error
   code. The *socket()* system call will pass this error code along (even if it is undefined).