from http.server import BaseHTTPRequestHandler, HTTPServer
import cgi
# HTTPRequestHandler class
class testHTTPServer_RequestHandler(BaseHTTPRequestHandler):
 
  # GET
  def do_GET(self):
        # Send response status code
        file = open("data.txt","r")
        self.send_response(200)
 
        # Send headers
        self.send_header('Content-type','text/html')
        self.end_headers()
 
        # Send message back to client
        message = """<!DOCTYPE html>
<html>
	<head>
		<title>Lasser Tag Controller</title>
		<script>
		function senddata(data){
			var xhttp = new XMLHttpRequest();
			xhttp.onreadystatechange = function() {
				if (this.readyState == 4 && this.status == 200) {
				  document.getElementById("demo").innerHTML = this.responseText;
				}
			};
			xhttp.open("POST", "", true);
			xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
			xhttp.send("data="+data);
		}
		</script>
	</head>
	<body>
		<h2><u>Overview</u></h2>
		
		<p style="color:green;">status: </p>
		<table border="2">
			<tr>
				<th>ID</th> <th>Status</th> <th>Address</th> <th>Type</th> <th>Team</th> <th>Name</th> <th>Damage</th> <th>Armor</th> <th>Rate of Fire (milliseconds)</th> <th>Amo Amount</th> <th>Clip Size</th> <th>Test Connection</th>
			</tr>
			"""
        
        self.wfile.write(bytes(message,"utf16"))
        status = "Online"
        data = file.readline()
        while data:
          info = data.replace("\n","").split(",")
          message = "<tr><td>"+info[0]+"</td> <td>" + status + "</td> <td>"+info[9]+"</td> <td>"+info[1]+"</td>"
          message = message + "<td><input type=\"number\" name=\"Pteam\" value=\""+info[2]+"\"></td> <td><input type=\"text\" name=\"Pname\" value=\""+info[3]+"\"></td>"
          message = message + "<td><input type=\"number\" name=\"Pdam\" value=\""+info[4]+"\"></td> <td><input type=\"number\" name=\"Parm\" value=\""+info[5]+"\"></td>"
          message = message + "<td><input type=\"number\" name=\"Prof\" value=\""+info[6]+"\"></td> <td><input type=\"number\" name=\"Pamo\" value=\""+info[7]+"\"></td>"
          message = message + "<td><input type=\"number\" name=\"Pclip\" value=\""+info[8]+"\"></td> <td><button>test</button></td></tr>"
          self.wfile.write(bytes(message,"utf16"))
          data = file.readline()
        # Write content as utf-8 data
        message = """</table>
		
		<h2><u>Game Setings</u></h2>
		<form method="post">
			<div>
				<u>Game Mode:</u>
				<input type="radio" name="Gmode" checked value="1">Free for all
				<input type="radio" name="Gmode" value="2">Team Battle
				<input type="radio" name="Gmode" value="3">Capture the Flag
				<input type="radio" name="Gmode" value="4">Elimination
				<input type="radio" name="Gmode" value="5">Team Elimination
				<input type="radio" name="Gmode" value="6">Kill the Caption
				<input type="radio" name="Gmode" value="7">Plague<br><br>
			</div>
			Friendly Fire:
			<select name="friendFire">
				<option selected value="no">off</option>
				<option value="yes">on</option>
			</select>
			<br>Player advantages:
			<select name="Gadvant">
				<option value="yes" selected>yes</option>
				<option value="no">no</option>
			</select><br><br>
			Player Health: <input type="number" name="health" value="100" min="1" max="500"><br>
			Player Lives: <input type="number" name="lives" value="3" min="1" max="20"><br>
			
			<br>
			<input type="submit" value="Begin">
		</form>
	</body>
</html>"""
        self.wfile.write(bytes(message,"utf16"))
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
    if(form.getvalue("data")!="None"):
      print(form.getvalue("data"))
    else:
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
