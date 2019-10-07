**************
TCP Layer Note
**************

#. TCP three-way handshake, connection termination sequence, and state transition diagram

    .. figure:: images/tcp_state_transition_diagram.png

        TCP State Transition Diagram

        Refer to *Unix Network Programming vol 1, section 2.6* for details.

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
        acknowledgement, retransimission, timeout
        sequence numbers, RTT estimation
        flow control (advertised window)

    UDP Characteristics: connectionless

#. IPv4 version of ping: ch28
#. Why UDP other than TCP: 22.4
#. TCP's slow-start and congestion avoidance algorithms: *TCPv1 Ch21*
