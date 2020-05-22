HTTP Note
=========

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
    The technique was superseded by multiplexing via HTTP/2, in which server
    doesn't have to process requests serially.

    .. image:: images/http_pipelining.png

    +------------------------------------------+------------------------------------------+
    | HTTP/1.1 pipelining                      | HTTP/2 Multiplexing                      |
    +==========================================+==========================================+
    | .. image:: images/http1.1_pipelining.jpg | .. image:: images/http2_multiplexing.jpg |
    +------------------------------------------+------------------------------------------+

.. rubric:: Footnotes

.. [#] `HTTP questions <https://mp.weixin.qq.com/s/bUy220-ect00N4gnO0697A>`_
.. [#] `Multiplexing and Demultiplexing <http://macao.communications.museum/eng/Exhibition/secondfloor/moreinfo/2_8_6_Multiplexing.html>`_
