urllib tricks
=============

Quick Reference to HTTP Headers
-------------------------------

Typical headers include 'Content-length', 'Content-type', and so on. See the
`Quick Reference to HTTP Headers <http://jkorpela.fi/http.html>`_
for a useful listing of HTTP headers with brief explanations of their meaning
and use.

.. code-block:: python

   >>> response = urllib.request.urlopen(full_url)
   >>> response.url
   'https://www.python.org/'
   >>> response.version
   11
   >>> response.status
   200
   >>> response.reason
   'OK'
   >>> response.getcode()
   200
   >>> response.msg
   'OK'
   >>> response.info()
   <http.client.HTTPMessage object at 0x1042eab38>
   >>> response.headers == response.info()
   True
   >>> response._method
   'GET'
   >>> pprint(response.headers.items())
   [('Connection', 'close'),
    ('Server', 'meinheld/0.6.1'),
    ('Date', 'Sat, 24 Mar 2018 15:24:10 GMT'),
    ('Content-Type', 'text/html; charset=utf-8'),
    ('Content-Length', '13129'),
    ('Access-Control-Allow-Origin', '*'),
    ('Access-Control-Allow-Credentials', 'true'),
    ('X-Powered-By', 'Flask'),
    ('X-Processed-Time', '0'),
    ('Via', '1.1 vegur')]


Quick reference to http response codes
--------------------------------------

Because the default handlers handle redirects (codes in the 300 range), and
codes in the 100--299 range indicate success, you will usually only see error
codes in the 400--599 range.

.. code-block:: python

   >>> import http.server
   >>> statusCode = http.server.BaseHTTPRequestHandler.responses
   >>> pprint(statusCode)

:attr:`http.server.BaseHTTPRequestHandler.responses` is a useful dictionary of
response codes in that shows all the response codes used by RFC 2616. The
dictionary is reproduced here for convenience ::

   import http.server
   responses = http.server.BaseHTTPRequestHandler.responses
   pprint(responses)
   # Table mapping response codes to messages; entries have the
   # form {code: (shortmessage, longmessage)}.
   responses = {
      100: ('Continue', 'Request received, please continue'),
      101: ('Switching Protocols',
            'Switching to new protocol; obey Upgrade header'),

      200: ('OK', 'Request fulfilled, document follows'),
      201: ('Created', 'Document created, URL follows'),
      202: ('Accepted',
            'Request accepted, processing continues off-line'),
      203: ('Non-Authoritative Information', 'Request fulfilled from cache'),
      204: ('No Content', 'Request fulfilled, nothing follows'),
      205: ('Reset Content', 'Clear input form for further input.'),
      206: ('Partial Content', 'Partial content follows.'),

      300: ('Multiple Choices',
            'Object has several resources -- see URI list'),
      301: ('Moved Permanently', 'Object moved permanently -- see URI list'),
      302: ('Found', 'Object moved temporarily -- see URI list'),
      303: ('See Other', 'Object moved -- see Method and URL list'),
      304: ('Not Modified',
            'Document has not changed since given time'),
      305: ('Use Proxy',
            'You must use proxy specified in Location to access this '
            'resource.'),
      307: ('Temporary Redirect',
            'Object moved temporarily -- see URI list'),

      400: ('Bad Request',
            'Bad request syntax or unsupported method'),
      401: ('Unauthorized',
            'No permission -- see authorization schemes'),
      402: ('Payment Required',
            'No payment -- see charging schemes'),
      403: ('Forbidden',
            'Request forbidden -- authorization will not help'),
      404: ('Not Found', 'Nothing matches the given URI'),
      405: ('Method Not Allowed',
            'Specified method is invalid for this server.'),
      406: ('Not Acceptable', 'URI not available in preferred format.'),
      407: ('Proxy Authentication Required', 'You must authenticate with '
            'this proxy before proceeding.'),
      408: ('Request Timeout', 'Request timed out; try again later.'),
      409: ('Conflict', 'Request conflict.'),
      410: ('Gone',
            'URI no longer exists and has been permanently removed.'),
      411: ('Length Required', 'Client must specify Content-Length.'),
      412: ('Precondition Failed', 'Precondition in headers is false.'),
      413: ('Request Entity Too Large', 'Entity is too large.'),
      414: ('Request-URI Too Long', 'URI is too long.'),
      415: ('Unsupported Media Type', 'Entity body in unsupported format.'),
      416: ('Requested Range Not Satisfiable',
            'Cannot satisfy request range.'),
      417: ('Expectation Failed',
            'Expect condition could not be satisfied.'),

      500: ('Internal Server Error', 'Server got itself in trouble'),
      501: ('Not Implemented',
            'Server does not support this operation'),
      502: ('Bad Gateway', 'Invalid responses from another server/proxy.'),
      503: ('Service Unavailable',
            'The server cannot process the request due to a high load'),
      504: ('Gateway Timeout',
            'The gateway server did not receive a timely response'),
      505: ('HTTP Version Not Supported', 'Cannot fulfill request.'),
   }

Note: `Quick reference to common Http Status code <https://wiki.apache.org/httpd/CommonHTTPStatusCodes>`_

Another http response code lookup table::
   
   import requests
   table = requests.codes.__dict__
   pprint(table)

4XX was a client error and 5XX a server one.

.. note::

   *timeout* is not a time limit on the entire response download;
   rather, an exception is raised if the server has not issued a
   response for *timeout* seconds (more precisely, if no bytes
   have been received on the underlying socket for *timeout* seconds).
   If no *timeout* is specified explicitly, requests do not time out.

