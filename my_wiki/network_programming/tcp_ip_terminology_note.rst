******************
TCP/IP Terminology
******************

The Four layers of TCP/IP suite:

+-------------+-----------------------------------+
| Application | Telnet, FTP, e-mail, Http, etc    |
+-------------+-----------------------------------+
| Transport   | TCP, UDP, SCTP                    |
+-------------+-----------------------------------+
| Network     | IP, ICMP, IGMP                    |
+-------------+-----------------------------------+
| Linker      | device drivers and interface card |
+-------------+-----------------------------------+

Range for 5 different classes of IP addresses:

+-------+------------------------------+
| Class | Range                        |
+=======+==============================+
| A     | 0.0.0.0 to 127.255.255.255   |
+-------+------------------------------+
| B     | 128.0.0.0 to 191.255.255.255 |
+-------+------------------------------+
| C     | 192.0.0.0 to 223.255.255.255 |
+-------+------------------------------+
| D     | 224.0.0.0 to 239.255.255.255 |
+-------+------------------------------+
| E     | 240.0.0.0 to 255.255.255.255 |
+-------+------------------------------+

IP address structures::

    A: 0    | netid(7 bits)  | hostid(24 bits)
    B: 10   | netid(14 bits) | hostid(16 bits)
    C: 110  | netid(21 bits) | hostid(8 bits)
    D: 1110 | multicast group ID(28 bits)
    D: 1111 | reserved(28 bits)

.. image:: images/tcpip_data_flow_encapsulation.gif
.. image:: images/ethernet_frame_demultiplex.gif

| IP = Internet Protocol
| ICMP = Internet Control Message Protocol
| IGMP = Internet Group Management Protocol
| TCP = Transport Control Protocol
| UDP = User Datagram Protocol
| FTP = File Transfer Protocol
| SCTP = Stream Control Transmission Protocol
| SMTP = Simple Mail Transport Protocol
| SNMP = Simple Network Management Protocol
| LAN = Local Area Network
| Wan = Wide Area Network
| VPN = Virtual Priavte Network
| SSH = Secure Shell
| ARP = Address Resolution Protocol
| RARP = Reverse Address Resolution Protocol
| DNS = Domain Name System
| RFC = Request For Comment
| RTT = Round Trip Time
| RTO = Retransmission Timeout
| MTU = Maximum Transfer Unit (1500 bytes for Ethernet)
| MSS = Maximum Segment Size
| MSL = Maximum Segment Life
| Out-of-band data and Urgent mode
| TLS = Transportation Layer Security
| SSL = Secure Sockets Layer
|
| :abbr:`TTL (Time To Live)`
| Definition: a value in an IP packet that limits the lifespan of a packet of data in a computer or network.
|
| multiplex
| Definition: consisting of many elements in a complex relationship
| Usage: multiplex ties of work and friendship.
| Definition: involving simultaneous transmission of several messages along a single channel of communication.
| Definition: (of a movie theater) having several separate screens within one building.
|

.. code-block:: sh
    :caption: Snacks

    $ grep ^telnet /etc/services
    telnet           23/udp
    telnet           23/tcp
    $ grep ^domain /etc/services
    domain           53/udp     # Domain Name Server
    domain           53/tcp     # Domain Name Server

#. Four-layered TCP Model and :abbr:`OSI (Open System Interaction)` Model

    +--------------+-------------+
    | Application  |             |
    +--------------+             +
    | Presentation |             |
    +--------------+ Application +
    | Session      |             |
    +--------------+-------------+
    | Transport    | Transport   |
    +--------------+-------------+
    | Network      | Network     |
    +--------------+-------------+
    | Datalink     |             |
    +--------------+ Linker      +
    | Physical     |             |
    +--------------+-------------+

    Refer to *Unix Network Programming vol 1, section 1.1 and section 1.7* for details.

#. Http Persistent Connection

    HTTP persistent connection, also called HTTP keep-alive, or HTTP connection reuse,
    is the idea of using a single TCP connection to send and receive multiple HTTP requests/responses,
    as opposed to opening a new connection for every single request/response pair. The newer HTTP/2 protocol
    uses the same idea and takes it further to allow multiple concurrent requests/responses to be multiplexed
    over a single connection.

    .. image:: images/http_persistent_connection.png

#. Http pipelining

    HTTP pipelining is a technique in which multiple HTTP requests are sent on a single
    TCP connection without waiting for the corresponding responses.
    The technique was superseded by multiplexing via HTTP/2, which is supported by most modern browsers.
    As of 2018, HTTP pipelining is not enabled by default in modern browsers, due to several issues
    including buggy proxy servers and HOL blocking.

    .. image:: images/http_pipelining.png

.. rubric:: Footnotes

.. [#] `Multiplexing and Demultiplexing <http://macao.communications.museum/eng/Exhibition/secondfloor/moreinfo/2_8_6_Multiplexing.html>`_


