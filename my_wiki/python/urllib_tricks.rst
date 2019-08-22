*************
urllib tricks
*************

.. toctree::

   urllib_apis

.. contents::
   :local:

HTTP Headers
============

Typical headers include 'Content-length', 'Content-type', and so on. 
See Quick Reference to HTTP Headers [#]_ for a useful listing 
of HTTP headers with brief explanations of their meaning and use.

.. code-block:: py

    >>> s = requests.get("http://www.baidu.com")
    >>> s.headers                                                                                                                                          
    {'Cache-Control': 'private, no-cache, no-store, proxy-revalidate, no-transform', 
    'Connection': 'Keep-Alive', 'Content-Encoding': 'gzip', 
    'Content-Type': 'text/html', 'Date': 'Thu, 22 Aug 2019 03:35:40 GMT', 
    'Last-Modified': 'Mon, 23 Jan 2017 13:27:36 GMT', 'Pragma': 'no-cache', 
    'Server': 'bfe/1.0.8.18', 'Set-Cookie': 'BDORZ=27315; max-age=86400; 
    domain=.baidu.com; path=/', 'Transfer-Encoding': 'chunked'}

HTTP response codes
===================

All HTTP response status codes are separated into five classes. The first digit of the status 
code defines the class of response. The last two digits do not have any class or categorization role. 
There are five values for the first digit:

    * 1xx (Informational): The request was received, continuing process
    * 2xx (Successful): The request was successfully received, understood, and accepted
    * 3xx (Redirection): Further action needs to be taken in order to complete the request
    * 4xx (Client Error): The request contains bad syntax or cannot be fulfilled
    * 5xx (Server Error): The server failed to fulfill an apparently valid request

Because the default handlers handle redirects (codes in the 300 range), and
codes in the 100--299 range indicate success, you will usually only see error
codes in the 400--599 range.

.. code-block:: py

    >>> import http.server
    >>> statusCode = http.server.BaseHTTPRequestHandler.responses
    >>> pprint(statusCode)

:attr:`http.server.BaseHTTPRequestHandler.responses` is a useful dictionary of
response codes in that shows all the response codes used by RFC 2616. The
dictionary is reproduced here for convenience::

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

Another http response code lookup table::
   
    import requests
    table = requests.codes.__dict__
    pprint(table)


#. http header - ``cache-control``
   
    ``cache-control`` is an HTTP header used to specify browser caching policies in both client requests and server responses. 
    Policies include how a resource is cached, where it’s cached and its maximum age before expiring (i.e., time to live).

    The cache-control header is broken up into directives, the most common of which are detailed below:

    - Cache-Control: Max-Age

        The max-age request directive defines, in seconds, 
        the amount of time it takes for a cached copy of a resource to expire. 

    - Cache-Control: No-Cache
        
        The no-cache directive means that a browser may cache a response, 
        but must first submit a validation request to an origin server.

    - Cache-Control: No-Store

        The no-store directive means browsers aren’t allowed to cache a response 
        and must pull it from the server each time it’s requested. 
        This setting is usually used for sensitive data, such as personal banking details.

    - Cache-Control: Public

        The public response directive indicates that a resource can be cached by any cache.

    - Cache-Control: Private

        The private response directive indicates that a resource is user specific—it can still be cached, 
        but only on a client device. For example, a web page response marked as private can be cached 
        by a desktop browser, but not a :abbr:`CDN (content delivery network)`.



.. rubric:: Footnotes

.. [#] `Quick Reference to HTTP Headers <http://jkorpela.fi/http.html>`_
.. [#] `Quick reference to common Http Status code <https://wiki.apache.org/httpd/CommonHTTPStatusCodes>`_
.. [#] `List of HTTP status codes <https://en.wikipedia.org/wiki/List_of_HTTP_status_codes>`_

