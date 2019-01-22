***************
Socket Overview
***************

.. toctree::

    socket_manual
    bind_manual
    listen_manual
    accept_manual
    connect_manual
    getaddrinfo_manual
    shutdown_manual
    socketpair_note
    socket_helper_apis


.. note:: 

    UNIX domain sockets are used to communicate with processes running on the same
    machine. Although Internet domain sockets can be used for this same purpose, UNIX
    domain sockets are more efficient. UNIX domain sockets only copy data; they have no
    protocol processing to perform, no network headers to add or remove, no checksums to
    calculate, no sequence numbers to generate, and no acknowledgements to send.