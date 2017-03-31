#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
Adafruit_SSD1306 display(12);

int amosize = 200;
int clipsize = 50;
byte id = 0;
byte type = 0;
String pName = "num: " + String(id);
int damage = 100;
int armor = 100;
int fireRate = 100;
byte team = 0;

int mode = 0;
int health = 100;
int lives = 3;
int amo = 200;
int clip = 50;
int mins = 5;
int secs = 30;

String data = "";
const uint16_t port = 8081;
const char * host = "192.168.1.50"; // ip or dns

#define Health16_GLCD_HEIGHT 11
#define Health16_GLCD_WIDTH  16
static const unsigned char PROGMEM Health16_glcd_bmp[] = {
  B00111000, B11100000,
  B01111101, B11110000,
  B11111111, B11111000,
  B11111111, B11111000,
  B11111111, B11111000,
  B01111111, B11110000,
  B00111111, B11100000,
  B00011111, B11000000,
  B00001111, B10000000,
  B00000111, B00000000,
  B00000010, B00000000,


};

void draw() {
  //time
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(display.width() / 2 - 15, 0);
  if (mins < 10) {
    display.print(0);
  }
  display.print(mins);
  display.print(":");
  if (secs < 10) {
    display.print(0);
  }
  display.println(secs);
  display.drawFastHLine(0, 3, 46, 1);
  display.drawFastHLine(81, 3, 50, 1);

  //health
  display.drawBitmap(0, 8, Health16_glcd_bmp, Health16_GLCD_WIDTH, Health16_GLCD_HEIGHT, 1);
  display.drawRect(15, 9, 98, 7, 1);
  display.fillRect(15, 10, map(health, 0, 100, 0, 97), 5, 1);
  display.setCursor(115, 9);
  display.print("x");
  display.println(lives);

  //clip
  display.setTextSize(2);
  display.setCursor(34, 21);
  if (clip < 10) {
    display.print(0);
  }
  display.print(clip);
  display.print("/");
  display.setCursor(70, 23);
  display.setTextSize(1);
  if (amosize > 100) {
    if (amo < 100) {
      display.print(0);
    }
  }
  if (amo < 10) {
    display.print(0);
  }
  display.println(amo);

  //Name,id,team
  display.setTextSize(2);
  //display.setCursor(0, 38);
  if (pName.length() < 10) {
    display.setCursor(64 - (pName.length() * 11) / 2 - 1, 40);
  } else {
    display.setCursor(0, 40);
  }
  display.println(pName);
  display.setTextSize(1);
  if (team == 0) {
    display.setCursor(46, 57);
  } else {
    display.setCursor(0, 57);
  }
  display.print("ID: ");
  if (id < 10) {
    display.print(0);
  }
  display.print(id);
  display.print("        ");
  if (team > 0) {
    display.print("Team ");
    display.print(team);
  }
  display.display();
}

void setup() {
  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network
  WiFiMulti.addAP("lasertagContoller", "lasertag");
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  display.setTextColor(1);
  display.setTextWrap(false);
  delay(500);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  while (data != "OK") {
    Serial.print("connecting to ");
    Serial.println(host);
    while (!client.connect(host, port)) {
      Serial.println("connection failed");
      Serial.println("wait 1 sec...");
      delay(1000);
    }
    Serial.println("sending data");
    data = "init," + String(id) + "," + String(type) + "," + String(team) + "," + String(pName) + "," + String(damage) + "," + String(armor) + "," + String(fireRate) + "," + String(amosize) + "," + String(clipsize);
    client.println(data);
    delay(1000);
    data = client.readStringUntil('\r');
    client.stop();
  }


  //  while (data != "START") {
  //    if (!client.connect(host, port)) {
  //      Serial.println("connection failed");
  //      Serial.println("wait 5 sec...");
  //      delay(5000);
  //      continue;
  //    }
  //    // This will send the request to the server
  //    //client.print(num);
  //
  //    //read back one line from server
  //    data = client.readStringUntil('\r');
  //    client.println(data);
  //    Serial.println(data);
  //
  //    Serial.println("closing connection");
  //    client.stop();
  //
  //    Serial.println("wait 1 sec...");
  //    delay(1000);
  //  }
}


void loop() {
  secs--;
  if (secs < 0) {
    if (mins == 0) {
      mins = 20;
    }
    mins--;
    secs = 59;
  }

  health -= 5;
  if (health < 0) {
    lives--;
    if (lives < 1) {
      lives = 3;
    }
    health = 100;
  }
  clip--;
  if (clip < 0) {
    amo -= clipsize;
    clip = clipsize;
    if (amo < 0) {
      amo = amosize;
    }
  }
  draw();
  delay(1000);
}



