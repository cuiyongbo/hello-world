*********************
Nginx insight note 03
*********************

Load balancing method:

   - Round Robin
   - Least Connections
   - IP Hash
   - Generic Hash


Server Weights

By default, NGINX distributes requests among the servers in the group according to their weights
using the Round Robin method. The ``weight`` parameter to the server directive sets the weight of
a server; the default is 1:

.. code-block:: none

    upstream backend {
        server backend1.example.com weight=5;
        server backend2.example.com;
        server 192.0.0.1 backup;
    }

In the example, ``backend1.example.com`` has weight 5; the other two servers have the default weight (1),
but the one with IP address ``192.0.0.1`` is marked as a ``backup`` server and does not receive requests
unless both of the other servers are unavailable. With this configuration of weights, out of every 6 requests,
5 are sent to ``backend1.example.com`` and 1 to ``backend2.example.com.``

#. Load balance source code: ``ngx_http_upstream_get_peer``

.. rubric:: Footnotes

.. [#] `Http load balancer <https://docs.nginx.com/nginx/admin-guide/load-balancer/http-load-balancer/>`_
