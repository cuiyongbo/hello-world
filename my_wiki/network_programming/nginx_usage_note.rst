***********
Nginx Usage
***********

#. nginx configure file demo

    .. code-block:: none

        user www-data;
        worker_processes auto;
        pid /run/nginx.pid;
        include /etc/nginx/modules-enabled/*.conf;

        events {
            worker_connections 768;
            # multi_accept on;
        }

        http {

            ##
            # Basic Settings
            ##

            sendfile on;
            tcp_nopush on;
            tcp_nodelay on;
            keepalive_timeout 65;
            types_hash_max_size 2048;
            # server_tokens off;

            # server_names_hash_bucket_size 64;
            # server_name_in_redirect off;

            include /etc/nginx/mime.types;
            default_type application/octet-stream;

            ##
            # SSL Settings
            ##

            ssl_protocols TLSv1 TLSv1.1 TLSv1.2; # Dropping SSLv3, ref: POODLE
            ssl_prefer_server_ciphers on;

            ##
            # Logging Settings
            ##

            access_log /var/log/nginx/access.log;
            error_log /var/log/nginx/error.log;

            ##
            # Gzip Settings
            ##

            gzip on;

            # gzip_vary on;
            # gzip_proxied any;
            # gzip_comp_level 6;
            # gzip_buffers 16 8k;
            # gzip_http_version 1.1;
            # gzip_types text/plain text/css application/json application/javascript text/xml application/xml application/xml+rss text/javascript;

            ##
            # Virtual Host Configs
            ##

            include /etc/nginx/conf.d/*.conf;
            include /etc/nginx/sites-enabled/*;
        }


#. nginx to turn on `gzip`

    Add following options to configure file::

        gzip  on;
        gzip_min_length 1000;
        gzip_types text/plain text/css application/json application/x-javascript text/xml application/xml application/xml+rss text/javascript application/octet-stream application/javascript;

#. nginx to configure http connection

    .. code-block:: none

        server {
            listen       80;
            server_name  localhost;
            location / {
                root   html;
                index  index.html index.htm;
            }

            location /nc/v1/test {
               root           html;
               fastcgi_pass   127.0.0.1:8888;
               fastcgi_index  index.php;
               fastcgi_param  SCRIPT_FILENAME  /scripts$fastcgi_script_name;
               include        fastcgi_params;
            }
        }

#. nginx src compilation problem

    .. code-block:: sh

        sudo apt-get install zlib1g zlib1g.dev
        sudo apt-get install libpcre3 libpcre3-dev


.. rubric:: Footnotes

.. [#] `NGINX FastCGI example <http://nginx.org/en/docs/http/ngx_http_fastcgi_module.html#example>`_
.. [#] `NGINX Connect Cpp FastCGI <http://chriswu.me/blog/writing-hello-world-in-fcgi-with-c-plus-plus/>`_
.. [#] `Inside the nginx <https://www.nginx.com/blog/inside-nginx-how-we-designed-for-performance-scale/>`_
.. [#] `Http load balancer <https://docs.nginx.com/nginx/admin-guide/load-balancer/http-load-balancer/>`_
