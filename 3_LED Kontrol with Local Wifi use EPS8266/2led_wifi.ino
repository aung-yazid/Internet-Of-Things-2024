#include <ESP8266WiFi.h>

const char* ssid = "Masukkan Nama Koneksi yang digunakan";
const char* password = "Password Koneksi yang digunakan";

WiFiServer server(80);

void setup() {
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);

  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);

  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("NodeMCU is connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  delay(3000);
}

void loop() {
  WiFiClient client;
  client = server.available();

 if (client == 1) {
    String request = client.readStringUntil('\n');
    client.flush();
    Serial.println(request);
    
    if (request.indexOf("led-on-1") != -1)
    { 
      digitalWrite(D1, HIGH);
      Serial.println("LED is ON");
    }

    if (request.indexOf("led-off-1") != -1)
    { 
      digitalWrite(D1, LOW);
      Serial.println("LED is OFF");
    }

    if (request.indexOf("led-on-2") != -1)
    { 
      digitalWrite(D2, HIGH);
      Serial.println("LED is ON");
    }

    if (request.indexOf("led-off-2") != -1)
    { 
      digitalWrite(D2, LOW);
      Serial.println("LED is OFF");
    }
 
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); 
  
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title> Controlling LED with Local WiFi </title>");
    client.println("</head>");
    client.println("<body align= \"center\" >");
    client.println("<h1 style=\"text-align: center\"> <font size = \"25\" >  LED Control with Local Wifi Network  </font> </h1> ");
    client.println("<h2 style=\"text-align: center\"> <font size = \"17\" >  RED LED  </font> </h2> ");
    client.println("<p style=\"text-align: center\"> <a href=\"/led-on-1\">  <button style=\"height:60px; background-color: red; width:200px; margin: 0 auto; text-align: center; cursor: pointer\"> ON  </button> <a> </font></p> ");
    client.println("<p style=\"text-align: center\"> <a href=\"/led-off-1\"> <button style=\"height:60px; background-color: red; width:200px; margin: 0 auto; text-align: center; cursor: pointer\" > OFF </button> <a> </font></p> ");
    client.println("<h2 style=\"text-align: center\"> <font size = \"17\" >  YELLOW LED  </font> </h2> ");
    client.println("<p style=\"text-align: center\"> <a href=\"/led-on-2\">  <button style=\"height:60px; background-color: blue; width:200px; margin: 0 auto; text-align: center; cursor: pointer\"> ON  </button> <a> </font></p> ");
    client.println("<p style=\"text-align: center\"> <a href=\"/led-off-2\"> <button style=\"height:60px; background-color: blue; width:200px; margin: 0 auto; text-align: center; cursor: pointer\" > OFF </button> <a> </font></p> ");
    client.println("</body>");
    client.println("</html>");

    Serial.println("Client disonnected");
    Serial.println("------------------");
    Serial.println("                  ");
       
  }
}
