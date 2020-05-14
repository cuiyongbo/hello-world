*********************
Nginx insight note 03
*********************

Load balancing methods:

    - Round Robin
    - Least Connections
    - IP Hash
    - Generic Hash

.. code-block:: none
    :caption: Basic Configure

    http {
        # backend is just a alias, you can replace it with a more meaning name.
        upstream backend {
            server backend1.example.com;
            server backend2.example.com;
            server 192.0.0.1 backup;
        }

        server {
            location / {
                proxy_pass http://backend;
            }
        }
    }

#. Round Robin

    Requests are distributed evenly across the servers, with server weights taken into consideration.
    This method is used by default (there is no directive for enabling it)::

        upstream backend {
           # no load balancing method is specified for Round Robin
           server backend1.example.com;
           server backend2.example.com;
        }

#. Least Connections

    A request is sent to the server with the least number of active connections,
    again with server weights taken into consideration::

        upstream backend {
            least_conn;
            server backend1.example.com;
            server backend2.example.com;
        }

#. IP Hash

    The server to which a request is sent is determined from the client IP address.
    In this case, either the first three octets of the IPv4 address or the whole IPv6
    address are used to calculate the hash value. The method guarantees that requests
    from the same address get to the same server unless it is not available::

        upstream backend {
            ip_hash;
            server backend1.example.com;
            server backend2.example.com;
        }

    If one of the servers needs to be temporarily removed from the load balancing rotation,
    it can be marked with the ``down`` parameter in order to preserve the current hashing of
    client IP addresses. Requests that were to be processed by this server are automatically
    sent to the next server in the group::

        upstream backend {
            server backend1.example.com;
            server backend2.example.com;
            server backend3.example.com down;
        }

#. Server Weights

    By default, NGINX distributes requests among the servers in the group according to their weights
    using the Round Robin method. The ``weight`` parameter to the server directive sets the weight of
    a server; the default is 1::

        upstream backend {
            server backend1.example.com weight=5;
            server backend2.example.com;
            server 192.0.0.1 backup;
        }

    In the example, ``backend1.example.com`` has weight 5; the other two servers have the default weight (1),
    but the one with IP address ``192.0.0.1`` is marked as a ``backup`` server and does not receive requests
    unless both of the other servers are unavailable. With this configuration of weights, out of every 6 requests,
    5 are sent to ``backend1.example.com`` and 1 to ``backend2.example.com.``

#. Load balance source code:

    - ngx_http_upstream_get_peer
    - ngx_stream_upstream_free_round_robin_peer
    - ngx_stream_upstream_get_least_conn_peer
    - ngx_stream_upstream_get_hash_peer

.. rubric:: Footnotes

.. [#] `Http load balancer <https://docs.nginx.com/nginx/admin-guide/load-balancer/http-load-balancer/>`_
