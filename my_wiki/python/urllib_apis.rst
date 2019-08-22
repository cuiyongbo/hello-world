***********
urllib APIS
***********

.. function:: urllib2.urlopen(url[, data[, timeout[, cafile[, capath[, cadefault[, context]]]]])

    Open the URL *url*, which can be either a string or a :class:`Request` object.

    *data* may be a string specifying additional data to send to the server, or ``None`` 
    if no such data is needed. Currently HTTP requests are the only ones that use data; 
    the HTTP request will be a POST instead of a GET when the *data* parameter is provided. 
    data should be a buffer in the standard application/x-www-form-urlencoded format. T
    he ``urllib.urlencode()`` function takes a mapping or sequence of 2-tuples and returns 
    a string in this format. urllib2 module sends HTTP/1.1 requests with ``Connection:close`` 
    header included.

    The optional *timeout* parameter specifies a timeout in seconds for blocking operations 
    like the connection attempt (if not specified, the global default timeout setting will be 
    used). This actually only works for HTTP, HTTPS and FTP connections.

    Raises :exc:`URLError` on errors.

    .. note::

        *timeout* is not a time limit on the entire response download;
        rather, an exception is raised if the server has not issued a
        response for *timeout* seconds (more precisely, if no bytes
        have been received on the underlying socket for *timeout* seconds).
        If no *timeout* is specified explicitly, requests do not time out.

.. function:: urllib.urlencode(query[, doseq])

    Convert a mapping object or a sequence of two-element tuples to a “percent-encoded” string, 
    suitable to pass to ``urlopen()`` above as the optional *data* argument. This is useful to 
    pass a dictionary of form fields to a POST request. The resulting string is a series of 
    ``key=value`` pairs separated by '&' characters. [But it is more suitable for GET.]


**Example**

#. urllib2 basic usage
   
    .. code-block:: python

        >>> import urllib2
        >>> response = urllib2.urlopen("http://www.baidu.com")
        >>> dir(response)
        [ 'close', 'code', 'fileno', 'fp', 'getcode', 'geturl', 'headers', 'info', 'msg', 
        'next', 'read', 'readline', 'readlines', 'url']
        >>> response.geturl()
        'http://www.baidu.com'
        >>> response.getcode()
        200
        >>> response.code
        200
        >>> response.msg
        'OK'
        >>> response.info()
        <httplib.HTTPMessage instance at 0x107742dd0>
        >>> response.headers
        <httplib.HTTPMessage instance at 0x107742dd0>
        >>> pprint(response.headers.dict)
        {'bdpagetype': '1',
         'bdqid': '0xa8a93c57000e54a9',
         'cache-control': 'private',
         'connection': 'close',
         'content-type': 'text/html',
         # ...
        'vary': 'Accept-Encoding',
        'x-ua-compatible': 'IE=Edge,chrome=1'}


#. urllib.encode basic usage
   
    .. code-block:: python

        >>> import urllib
        >>> fields = {'bdpagetype': '1', 'bdqid': '0xa8a93c57000e54a9', 'vary': 'Accept-Encoding', 'connection': 'close'}
        >>> urllib.urlencode(fields)
        'connection=close&vary=Accept-Encoding&bdpagetype=1&bdqid=0xa8a93c57000e54a9'
        >>> fs = {'name':"cherry", 'age':26, 'hobbies':["programming", "photography", "climbing"]}
        >>> urllib.urlencode(fs)
        'age=26&name=cherry&hobbies=%5B%27programming%27%2C+%27photography%27%2C+%27climbing%27%5D'
        >>> urllib.urlencode(fs, True)
        'age=26&name=cherry&hobbies=programming&hobbies=photography&hobbies=climbing'


#. Python requests
   
    Requests is an HTTP library, written in Python, for human beings. 

    .. code-block:: py
        :caption: Quick start

        >>> r = requests.get('http://www.baidu.com')                                                                                                           
        >>> r.status_code
        200
        >>> r.content[:100]
        b'<!DOCTYPE html>\r\n<!--STATUS OK--><html> <head><meta http-equiv=content-type content=text/html;charse'

        >>> r = requests.post('https://httpbin.org/post', data = {'key':'value'})
        >>> r = requests.put('https://httpbin.org/put', data = {'key':'value'})
        >>> r = requests.delete('https://httpbin.org/delete')
        >>> r = requests.head('https://httpbin.org/get')
        >>> r = requests.options('https://httpbin.org/get')

        >>> [p for p in dir(requests) if '__' not in p]                                                                                                        
        ['ConnectTimeout', 'ConnectionError', 'DependencyWarning', 'FileModeWarning', 'HTTPError', 
        'NullHandler', 'PreparedRequest', 'ReadTimeout', 'Request', 'RequestException', 'RequestsDependencyWarning', 
        'Response', 'Session', 'Timeout', 'TooManyRedirects', 'URLRequired', '_internal_utils', 'adapters', 'api', 
        'auth', 'certs', 'chardet', 'check_compatibility', 'codes', 'compat', 'cookies', 'delete', 'exceptions', 
        'get', 'head', 'hooks', 'logging', 'models', 'options', 'packages', 'patch', 'post', 'put', 'request', 
        'session', 'sessions', 'status_codes', 'structures', 'urllib3', 'utils', 'warnings']  
