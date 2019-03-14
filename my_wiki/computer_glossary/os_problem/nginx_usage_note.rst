***********
Nginx Usage
***********

#. nginx to turn on `gzip`
   
    Add following options to configure file::

        gzip  on;
        gzip_min_length 1000;
        gzip_types text/plain text/css application/json application/x-javascript text/xml application/xml application/xml+rss text/javascript application/octet-stream application/javascript;
