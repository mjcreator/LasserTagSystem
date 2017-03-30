import socketserver

HOST, PORT = "192.168.1.50", 8081

class MyTCPHandler(socketserver.BaseRequestHandler):
    """
    The request handler class for our server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    """

    def handle(self):
        # self.request is the TCP socket connected to the client
        self.data = self.request.recv(1024).strip()
        print("{} wrote:".format(self.client_address[0]))
        print(self.data)
        data = str(self.data).replace("b'","").replace("'","")
        values = data.split(",")
        print(values)
        if(values[0] == "init"):
            f = open("data.txt","r+")
            fr = f.read()
            print(fr)
            values.pop(0)
            for x in range(len(values)):
                f.write(values[x] + ",")
            f.write(self.client_address[0] + "\n")
            self.request.sendall(bytes("OK","utf8"))
            f.close()
        else:
        # just send back the same data, but upper-cased
            self.request.sendall(self.data.upper())

if __name__ == "__main__":
    f = open("data.txt","w")
    f.write("")
    f.close

    # Create the server, binding to localhost on port 9999
    server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)# as server:
    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()
