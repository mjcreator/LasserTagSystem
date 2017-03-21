from http.server import BaseHTTPRequestHandler, HTTPServer
import cgi
# HTTPRequestHandler class
class testHTTPServer_RequestHandler(BaseHTTPRequestHandler):
 
  # GET
  def do_GET(self):
        # Send response status code
        file = open("laserTagUserInterface.html","r")
        self.send_response(200)
 
        # Send headers
        self.send_header('Content-type','text/html')
        self.end_headers()
 
        # Send message back to client
        message = file.read()
        self.wfile.write(bytes(message,"utf16"))
        # Write content as utf-8 data
        file.close()
        return
      
  def do_POST(self):
    form = cgi.FieldStorage(
      fp=self.rfile, 
      headers=self.headers,
      environ={'REQUEST_METHOD':'POST',
               'CONTENT_TYPE':self.headers['Content-Type'],
               })
    self.send_response(200)
    print(form.getvalue("Gmode"))
    print(form.getvalue("friendFire"))
    print(form.getvalue("Gadvant"))
    print(form.getvalue("health"))
    print(form.getvalue("lives"))
    #print()
    # Send headers
    self.send_header('Content-type','text/html')
    self.end_headers()

    # Send message back to client
    message = form.getvalue("Gmode")
    #self.wfile.write(bytes(message,"utf16"))
    # Write content as utf-8 data
    return
 
def run():
  print('starting server...')
 
  # Server settings
  # Choose port 8080, for port 80, which is normally used for a http server, you need root access
  server_address = ('127.0.0.1', 8080)
  httpd = HTTPServer(server_address, testHTTPServer_RequestHandler)
  print('running server...',server_address)
  httpd.serve_forever()
 
 
run()
