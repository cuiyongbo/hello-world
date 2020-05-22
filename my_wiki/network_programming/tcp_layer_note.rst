**************
TCP Layer Note
**************

#. TCP three-way handshake, connection termination sequence, and state transition diagram

    .. figure:: images/tcp_state_transition_diagram.png

        TCP State Transition Diagram

        Refer to *Unix Network Programming vol 1, section 2.6* for details.

#. why there are 3 handshakes in establishing tcp connections, while 4 in terminating

    The principle reason for the three-way handshake is to prevent old duplicate connection
    initiations from causing confusion.

    We take the situation where client actively close the connection as example.
    Because when server receives the FIN packet from client, it may still have data to send,
    only after finishing sending data, can server also send its FIN, this means server
    can't combine the FIN and ACK packets as in establishing the connection.

    TCP 建立连接时，通过三次握手能防止历史连接的建立，能减少双方不必要的资源开销，
    能帮助双方同步初始化序列号。序列号能够保证数据包不重复、不丢弃和按序传输。

    不使用「两次握手」和「四次握手」的原因：

        - 「两次握手」：无法防止历史连接的建立，会造成双方资源的浪费，也无法可靠的同步双方序列号；
        - 「四次握手」：三次握手就已经理论上最少可靠连接建立，所以不需要使用更多的通信次数。

#. why TIME_WAIT has to stay for 2 * MSL times

    This comes in 2 reasons:

        - allow the end whose actively close the connection to retransmit find FIN packet
        - allow the packets belongs to the old connection to expire

    And you can skip TIME_WAIT by set ``SO_LINGER`` option, which will send RST to
    its peer on calling ``close()``.

    Refer to *Unix Network Programming vol 1, section 2.7* for details.

#. Server Framework

    - Iterative server
        - iterative through each client, one at a time

    - Concurrent server
        - fork one process for each child
        - create one thread for each child
        - pre-fork a fixed number of child processes at start-up

#. TCP vs UDP

    TCP Characteristics::

        connection-oriented
        positive acknowledgements,
        retransimission of lost packets,
        duplicate detection,
        sequencing of packets reorder by the network.
        timeout, RTT estimation,
        windowed flow control,
        slow start and congestion avoidance

    UDP Characteristics::

        connectionless (no connection setup or teardown),
        support broadcast and multicast

    Refer to *Unix Network Programming vol 1, section 22.4* for details.

#. IPv4 version of ping: ch28
#. TCP's slow-start and congestion avoidance algorithms: *TCPv1 Ch21*

#. TCP Keepalive (保活)

    Keepalive is non-invasive, and in most cases, if you're in doubt,
    you can turn it on without the risk of doing something wrong.
    But do remember that it generates extra network traffic,
    which can have an impact on routers and firewalls.

    Two target tasks for keepalive:

        - Checking for dead peers
        - Preventing disconnection due to network inactivity

    Related kernel options with their default values::

        net.ipv4.tcp_keepalive_time=7200
        net.ipv4.tcp_keepalive_intvl=75
        net.ipv4.tcp_keepalive_probes=9

    In other words, kernel will detect a dead peer after
    ``tcp_keepalive_time + tcp_keepalive_probes*tcp_keepalive_intvl`` seconds.
    And keepalive is is closed by default, you can configure it use ``SO_KEEPALIVE``
    at ``SOL_SOCKET`` level using ``setsockopt`` system call.

    There are also three other socket options you can set for keepalive.
    They all use the ``SOL_TCP`` level instead of ``SOL_SOCKET``,
    and they override system-wide variables only for the current socket::

        TCP_KEEPCNT: overrides tcp_keepalive_probes
        TCP_KEEPIDLE: overrides tcp_keepalive_time
        TCP_KEEPINTVL: overrides tcp_keepalive_intvl

    .. code-block:: sh

        $ sysctl -a | grep "ipv4.tcp"
        ...
        net.ipv4.tcp_keepalive_intvl = 75
        net.ipv4.tcp_keepalive_probes = 9
        net.ipv4.tcp_keepalive_time = 7200


#. TCP sliding window protocol

    - the window size of sender is determined by the one of receiver.
    - TCP zero window probe (a timer mechanism similar to keepalive and TIME_WAIT)
    - TCP Silly Window syndrom (糊涂窗口综合征，Nagle algorithm)
    - TCP Congestion window (拥塞控制)

#. Configure TCP Nagle algorithm: ``setsockopt(sock_fd, IPPROTO_TCP, TCP_NODELAY);``
#. TCP Congestion window (拥塞控制)

    拥塞窗口 cwnd 是发送方维护的一个的状态变量，它会根据网络的拥塞程度动态变化的。
    它和发送窗口 swnd 和接收窗口 rwnd 的关系：``swnd = min(cwnd, rwnd)``

    其实只要「发送方」没有在规定时间内接收到 ACK 应答报文，也就是发生了超时重传，
    就会认为网络出现了用拥塞。拥塞控制主要是四个算法：

        - 慢启动 (slow start, increase exponentialy until reaching slow start threshold)
        - 拥塞避免 (increase linearly)
        - 拥塞发生
        - 快速恢复

.. rubric:: Footnote

.. [#] `TCP interview questions <https://blog.csdn.net/qq_38950316/article/details/81087809>`_
.. [#] `TCP interview questions 02 <https://mp.weixin.qq.com/s/KxmSGxTAYe9eiEEVcLkJZg>`_
.. [#] `TCP interview questions 03 <https://mp.weixin.qq.com/s/Tc09ovdNacOtnMOMeRc_uA>`_
.. [#] `TCP Keepalive HOWTO <http://www.tldp.org/HOWTO/html_single/TCP-Keepalive-HOWTO/>`_
.. [#] `TCP sliding window protocol <https://www.ibm.com/support/knowledgecenter/en/SSGSG7_7.1.0/com.ibm.itsm.perf.doc/c_network_sliding_window.html>`_
