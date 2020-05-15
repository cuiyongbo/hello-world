**************
TCP Layer Note
**************

#. TCP three-way handshake, connection termination sequence, and state transition diagram

    .. figure:: images/tcp_state_transition_diagram.png

        TCP State Transition Diagram

        Refer to *Unix Network Programming vol 1, section 2.6* for details.

#. why there are 3 handshakes in establishing tcp connections, while 4 in terminating

    We take the situation where client actively close the connection as example.
    Because when server receives the FIN packet from client, it may still have data to send,
    only after finishing sending data, can server also send its FIN, this means server
    can't combine the FIN and ACK packets as in establishing the connection.

#. why TIME_WAIT has to stay for 2 * MSL times

    This comes in 2 reasons:

        - allow the end whose actively close the connection to retransmit find FIN packet
        - allow the packets belongs to the old connection to expire

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

#. TCP Keepalive

    Keepalive is non-invasive, and in most cases, if you're in doubt,
    you can turn it on without the risk of doing something wrong.
    But do remember that it generates extra network traffic,
    which can have an impact on routers and firewalls.

    Two target tasks for keepalive:

        - Checking for dead peers
        - Preventing disconnection due to network inactivity

#. TCP sliding window protocol




.. rubric:: Footnote

.. [#] `TCP interview questions <https://blog.csdn.net/qq_38950316/article/details/81087809>`_
.. [#] `TCP Keepalive HOWTO <http://www.tldp.org/HOWTO/html_single/TCP-Keepalive-HOWTO/>`_
.. [#] `TCP sliding window protocol <https://www.ibm.com/support/knowledgecenter/en/SSGSG7_7.1.0/com.ibm.itsm.perf.doc/c_network_sliding_window.html>`_
