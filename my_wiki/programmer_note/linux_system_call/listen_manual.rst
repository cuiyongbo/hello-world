********************************************
listen -- listen for connections on a socket
********************************************

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
    of *ECONNREFUSED*.

#. listen.backlog meaning

    Linux内核中会维护两个队列：

        - 未完成连接队列（SYN 队列）：接收到一个 SYN 建立连接请求，处于 SYN_RCVD 状态
        - 已完成连接队列（Accpet 队列）：已完成 TCP 三次握手过程，处于 ESTABLISHED 状态

    在早期 Linux 内核 backlog 是 SYN 队列大小，也就是未完成的队列大小。
    在 Linux 内核 2.2 之后，backlog 变成 accept 队列，
    也就是已完成连接建立的队列长度，所以现在通常认为 backlog 是 accept 队列。

    .. image:: images/tcp_socket_listen_queue.jpg
