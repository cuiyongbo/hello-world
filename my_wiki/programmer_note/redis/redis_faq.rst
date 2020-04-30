Redis FAQ
=========

#. Error condition on socket for SYNC: Connection refused

    An ugly solution: edit ``redis.conf`` change ``bind ipaddress`` to ``bind 0.0.0.0``
    to allow connections from any host.
