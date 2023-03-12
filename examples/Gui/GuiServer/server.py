from http.server import BaseHTTPRequestHandler, HTTPServer

class XMLServer(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path.endswith('.xml'):
            # Open the XML file and read its contents
            try:
                f = open(self.path[1:], 'rb')
                self.send_response(200)
                self.send_header('Content-type', 'text/xml')
                self.end_headers()
                self.wfile.write(f.read())
                f.close()
                return
            except IOError:
                self.send_error(404, 'File Not Found: %s' % self.path)
        else:
            self.send_error(400, 'Bad Request: %s' % self.path)

def run(server_class=HTTPServer, handler_class=XMLServer, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print('Starting httpd on port %d...' % port)
    httpd.serve_forever()

if __name__ == '__main__':
    run()

