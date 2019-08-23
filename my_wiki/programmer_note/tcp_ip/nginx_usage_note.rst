***********
Nginx Usage
***********

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
