**********
nginx conf
**********

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


.. rubric:: Footnotes

.. [#] `FastCGI repository <https://fastcgi-archives.github.io/>`_
.. [#] `Spawn-fcgi repository <https://github.com/lighttpd/spawn-fcgi>`_
.. [#] `Another FastCGI Library <http://althenia.net/fcgicc>`_
.. [#] `Tencent Server frame <https://github.com/Tencent/phxpaxos.git>`
.. [#] `NGINX FastCGI example <http://nginx.org/en/docs/http/ngx_http_fastcgi_module.html#example>`_
.. [#] `NGINX Connect Cpp FastCGI <http://chriswu.me/blog/writing-hello-world-in-fcgi-with-c-plus-plus/>`_
.. [#] `Inside the nginx <https://www.nginx.com/blog/inside-nginx-how-we-designed-for-performance-scale/>`
