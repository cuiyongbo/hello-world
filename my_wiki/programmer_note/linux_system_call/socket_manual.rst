*************
socket Manual
*************

NAME: ``socket -- create an endpoint for communication``

**DESCRIPTION**

    .. code-block:: c
        :caption: SYNOPSIS

        #include <sys/socket.h>
        #include <sys/types.h>
        int socket(int domain, int type, int protocol);

    *socket()* creates an endpoint for communication and returns a descriptor.

    The *domain* parameter specifies a communications domain within which communication will take
    place; this selects the protocol family which should be used. These families are defined in
    the include file **sys/socket.h**.  The currently understood formats are:

        * AF_LOCAL        Host-internal protocols, formerly called AF_UNIX,
        * AF_UNIX         Host-internal protocols, deprecated, use AF_LOCAL,
        * AF_INET         Internet version 4 protocols,
        * AF_INET6        Internet version 6 protocols,

    The socket has the indicated *type*, which specifies the semantics of communication.
    Currently defined types are:

        * SOCK_STREAM
        * SOCK_DGRAM
        * SOCK_RAW

    A *SOCK_STREAM* type provides sequenced, reliable, two-way connection based byte streams. An
    out-of-band data transmission mechanism may be supported. A *SOCK_DGRAM* socket supports
    datagrams (connectionless, unreliable messages of a fixed (typically small) maximum length).
    *SOCK_RAW* sockets provide access to internal network protocols and interfaces. The type
    *SOCK_RAW*, which is available only to the super-user.

    The *protocol* specifies a particular protocol to be used with the socket.
    **It is usually zero, to select the default protocol for the given domain and socket type.**

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

    A -1 is returned if an error occurs, otherwise the return value is a descriptor referencing the socket.

#. Under What Conditions Is a Descriptor Ready?

    Refer to *Unix Network Programming, vol 1, ch 6* for further information.

#. Iterative server and concurrent server

    Refer to *Unix Network Programming, vol 1, ch 4* for further information.
    And there is a brilliant explanation about
    *Why doesn't the close of connfd by the parent terminate its connection with the client.*

