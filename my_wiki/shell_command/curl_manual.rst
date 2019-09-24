*********************
curl - transfer a URL
*********************

**DESCRIPTION**

   .. code-block:: sh

      curl [options] [URL...]

   curl is a tool to transfer data from or to a server, using one of the supported protocols
   The command is designed to work without user interaction.

   curl offers a busload of useful tricks like proxy support, user authentication, FTP upload,
   HTTP post, SSL connections, cookies, file transfer resume, Metalink, and more.

   curl will attempt to re-use connections for multiple file transfers, so that getting many files
   from the same server will not do multiple connects/handshakes. This improves speed. Of course
   this is only done on files specified on a single command line and cannot be used between separate
   curl invokes.

**Hot Options**

   .. option:: -#, --progress-bar

      Make curl display progress as a simple progress bar instead of the standard, more informational, meter.

   .. option:: -d, --data <data>

      (HTTP) Sends the specified data in a POST request to the HTTP server, This will cause curl to pass the data
      to the server  using  the  content-type ``application/x-www-form-urlencoded``.

      ``-d, --data`` is the same as ``--data-ascii``. To post data purely binary, you should instead use
      the ``--data-binary``. To URL-encode the value of a form field you may use ``--data-urlencode``.

      If any of these options is used more than once on the same command line, the data pieces specified will
      be merged together with a separating &-symbol. Thus, using ``-d name=daniel -d skill=``lousy would
      generate a post chunk that looks like ``name=daniel&skill=lousy``.

      If you start the data with the letter @, the rest should be a file name to read the data from,
      Multiple files can also be specified. Posting data from a file named ``foobar`` would thus be done with
      ``--data @foobar``.

   .. option:: -D, --dump-header <file>

      Write the protocol headers to the specified file. note the ``-`` after the ``-D``
      which indicates that the output file is ``stdout``. e.g. ``curl -D - http://www.baidu.com``

   .. option:: --connect-timeout <seconds>

      Maximum time in seconds that you allow the connection to the server to take.
      This only limits the connection phase, once curl has connected this option is of no more use.

   .. option:: --create-dirs

      When used in conjunction with the -o option, curl will create the necessary local directory hierarchy as needed.
      This option creates the dirs mentioned with the -o option, nothing else. If the -o file name uses no dir or if
      the dirs it mentions  already exist, no dir will be created.

   .. option:: -o, --output <file>

      Write output to <file> instead of stdout.

   .. option:: -m, --max-time <seconds>

      Maximum time in seconds that you allow the whole operation to take.
      This is useful for preventing your batch jobs from hanging for hours
      due to slow networks or links going down.

   .. option:: -s, --silent

      Silent or quiet mode. Don't show progress meter or error messages.
      Makes Curl mute. It will still output the data you ask for, potentially
      even to the terminal/stdout unless you redirect it.

   .. option:: -i, --include

      (HTTP) Include the HTTP-header in the output.

   .. option:: -I, --head

      (HTTP/FTP/FILE) Fetch the HTTP-header only! HTTP-servers feature the command HEAD
      which this uses to get nothing but the header of a document. When used on an FTP
      or FILE file, curl displays the file size and last modification time only.

   .. option:: -H, --header <header>

      (HTTP) Extra header to use when getting a web page. You may specify any number of extra headers.
      Note that if you should add a custom header that has the same name as one of the internal ones
      curl would use, your externally set header will be used instead of the internal one.
      You should not replace internally set headers without knowing perfectly well what you're doing.
      Remove an internal header by giving a replacement without content on the right side of the colon,
      as in: ``-H "Host:"``. If you send the custom header with no-value then its header must be terminated
      with a semicolon, such as ``-H "X-Custom-Header;"`` to send ``"X-Custom-Header:"``.

      curl will make sure that each header you add/replace is sent with the proper end-of-line marker,
      you should thus not add that as a part of the header content: do not add newlines or carriage returns,
      they will only mess things up for you.

      This option can be used multiple times to add/replace/remove multiple headers.

**EXAMPLE**

.. code-block:: sh

   # HTTP GET
   $  curl  http://w.mapbar.com/nc/v1/tile/tmc/fastTimestamp -s
   {"nextUpdateTime":15,"updateTime":1542364560}

   # HTTP POST
   $ curl -s -d '{"linkIds":"0", "flags":"speeds"}' http://116.213.115.77:81/nc/v1/nav2tmc?ver=2.1
   {"timestamp": 1542364620, "trafficColors": "4", "trafficSpeeds": "0.50"}

   # HTTP HEAD
   $ curl -sI file:///C:/WorkSpace/Work-Project/RouteData/data/realtime.data
   Content-Length: 4706728
   Accept-ranges: bytes
   Last-Modified: Thu, 22 Nov 2018 05:45:08 GMT

   $ curl -s -d `getRouteLinks.py -i '(11602934,4014603)(11606411,4016913)' -vv` http://w.mapbar.com/nc/v1/nav2tmc?ver=2.0


#. Download Http directiory with all files and subdirectories

   Example: ``wget -r -np -nH --cut-dirs=3 -e robots=off -R index.html http://hostname/aaa/bbb/ccc/ddd/``

   Explanation::

      It will download all files and subfolders in ddd directory
      -r : recursively
      -np : not going to upper directories, like ccc/…
      -nH : not saving files to hostname folder
      --cut-dirs=3 : but saving it to ddd by omitting first 3 folders aaa, bbb, ccc
      -e robots=off: disable robot check if there exists a robot.txt
      -R index.html : excluding index.html files

#. wget error: Unable to establish SSL connection.

   To connect to ndownloader.figshare.com insecurely, use ``--no-check-certificate``.
   e.g. ``wget --no-check-certificate https://ndownloader.figshare.com/files/5975967``
