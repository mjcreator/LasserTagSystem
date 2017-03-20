/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "ESPap";
const char *password = "1234567890";

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
	server.send(200, "text/html", "<!DOCTYPE html><html><head><script>function button1(){var s = parseInt(prompt('please enter the available number'));document.getElementById('spot1').innerHTML = s;}function button2(){var s = parseInt(prompt('please enter the available number'));document.getElementById('spot2').innerHTML = s;}function button3(){var s = parseInt(prompt('please enter the available number'));document.getElementById('spot3').innerHTML = s;}function button4(){var s = parseInt(prompt('please enter the available number'));document.getElementById('spot4').innerHTML = s;}function button5(){var s = parseInt(prompt('please enter the available number'));document.getElementById('spot5').innerHTML = s;}function button6(){var s = parseInt(prompt('please enter the available number'));document.getElementById('spot6').innerHTML = s;}</script><title>shoes</title></head><body><h2><u>shoe size</u></h1><table border='2'><tr><th></th><th>9</th><th>10</th><th>10.5</th></tr><tr><th>Asixs</th><td id='spot1'>?</td><td id='spot2'>?</td><td id='spot3'>?</td></tr><tr><th>Puma</th><td id='spot4'>?</td><td id='spot5'>?</td><td id='spot6'>?</td></tr></table><br><table><tr><td><button onclick='button1()'>1st</button></td><td><button onclick='button2()'>2nd</button></td><td><button onclick='button3()'>3rd</button></td></tr><tr><td><button onclick='button4()'>4th</button></td><td><button onclick='button5()'>5th</button></td><td><button onclick='button6()'>6th</button></td></tr></table></body></html>");
}

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}
