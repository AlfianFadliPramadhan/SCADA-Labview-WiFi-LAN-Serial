//ARDUINO + ESP8266 CODE

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "MyESP8266AP";
const char *password = "testpassword";
 
WiFiServer server(80);

String inputString = "";
String dt = "";

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><meta http-equiv=\"refresh\" content=\"1\"><title>Web SCADA</title></head><body>";
String html_2 = "<h1>Peringatan Dini Tsunami</h1>";
String html_3 = "<h2>Data Sensor</h2><br>";
String html_4 = "</body></html>";
   
void setup() {

  Serial.begin(9600);
 
  WiFi.softAP(ssid, password);

  server.begin();
 
}
 
void loop() {

  WiFiClient client = server.available();
  
    client.print( header );
    client.print( html_1 );
    client.print( html_2 );
    client.print( html_3 );

    if (Serial.available() > 0) {
    dt = "";
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      client.print("<h3>" + inputString + "</h3>");
      dt = inputString;

      client.print( html_4 );

      delay(1);
      client.flush();
    } 
  } else {
    if (dt != "") {
      client.print("<h3>" + dt + "</h3>");
      inputString = "";

      client.print( html_4 );

      delay(1);
      client.flush();

    }
  }
    
    client.print( html_4 );
 
    delay(1);
    client.flush();
}
