***********
Http Server
***********

.. code-block:: python

    #!/usr/bin/env python
    # coding: utf-8

    import os, time, sys, ssl, zlib, gzip,json
    from threading import Thread
    from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer

    HTTP_PORT_NUMBER = 8010
    HTTPS_PORT_NUMBER = 8443

    class TestHTTPHandler(BaseHTTPRequestHandler):
        """
        This class will handles any incoming requests
        from the browser or NaviCore client.
        """
        BaseHTTPRequestHandler.protocol_version = 'HTTP/1.1'

        def make_plain_text_response(self, content):
            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.send_header('Content-length', len(content))
            self.end_headers()
            self.wfile.write(content)

        def make_json_response(self, data):
            root_and_nodes = data.split('?', 2)
            root = root_and_nodes[0]
            node_dict = {}
            nodes = root_and_nodes[1].split('&')
            for node in nodes:
                key_and_val = node.split('=', 2)
                node_dict[key_and_val[0]] = key_and_val[1]
            root_dict = {}
            root_dict[root] = node_dict
            response = json.JSONEncoder().encode(root_dict)
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.send_header('Content-length', len(response))
            self.end_headers()
            self.wfile.write(response) 

        def do_GET(self):
            """Handler for the GET requests"""
            print self.raw_requestline
            print self.path
            if self.path=="/":
                self.make_plain_text_response("Hello world!")
            elif self.path.startswith("/test-json"):
                self.make_json_response(self.path)
            elif self.path.startswith("/echo/"):
                # echo back things after /echo/
                self.make_plain_text_response(self.path[6:])
             else:
                return

        def do_POST(self):
            """"Handler for the POST requests"""
            pass

    class HttpServerThread(Thread):
        def __init__(self, security):
           ''' http server '''
           Thread.__init__(self)
           self.security = security
           self.server = None
           self.stopped = False
           # https://docs.python.org/2/library/threading.html#thread-objects
           # The entire Python program exits when no alive non-daemon threads are left.
           self.setDaemon(True)
      
    def run(self):
        if self.security:
            print 'Starting https server on port ', HTTPS_PORT_NUMBER
            server = HTTPServer(('', HTTPS_PORT_NUMBER), TestHTTPHandler)
            # http://www.mynewsdesk.com/devcorner/blog_posts/a-simple-https-server-for-development-28395
            # openssl req -new -x509 -keyout server.pem -out server.pem -days 365 -nodes
            server.socket = ssl.wrap_socket(server.socket, server_side=True, certfile='server.pem')
        else:
            print 'Starting http server on port ', HTTP_PORT_NUMBER
            server = HTTPServer(('', HTTP_PORT_NUMBER), TestHTTPHandler)
       
        self.server = server
        while not self.stopped:
            self.server.handle_request()
   
    def stop(self):
        self.stopped = True
        self.server.server_close()
        self.server.socket.close()
      
    if __name__  == '__main__':
        os.chdir(os.path.dirname(os.path.abspath(__file__)))
   
        http = HttpServerThread(False)
        http.start()
        https = HttpServerThread(True)
        https.start()
   
        try:
            while True:
                time.sleep(2)
        except KeyboardInterrupt:
            print '^C received, shutting down the web server'
            http.stop()
            https.stop()
