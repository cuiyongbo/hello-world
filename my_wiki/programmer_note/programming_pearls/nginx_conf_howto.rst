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