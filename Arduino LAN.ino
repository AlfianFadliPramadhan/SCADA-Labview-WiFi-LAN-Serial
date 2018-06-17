//ARDUINO + ETHERNET SHIELD CODE

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x85, 0xD9 };   //physical mac address
IPAddress ip(192,168,2,113);
//byte ip[] = { 192, 168, 2, 133 };                   // ip in lan
IPAddress gateway(192,168,2,1);
IPAddress subnet(255,255,255,0);
//byte gateway[] = { 192, 168, 2, 1 };              // default gateway
//byte subnet[] = { 255, 255, 255, 0 };              //subnet mask

EthernetClient client; 

EthernetServer server(80);

String inputString = "";         // a String to hold incoming data
String dt = "";

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop() {

  client = server.available();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>");
  client.println("Web SCADA");
  client.println("</title>");
  client.println("<meta http-equiv=\"refresh\" content=\"1\">");

  client.println("</head>");
  client.println("<body>");
  client.println("<h1>Peringatan Dini Tsunami </h1>");
  client.println("<h2>Data Sensor</h2>");
  
  if (Serial.available() > 0) {
    dt = "";
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      client.print("<h3>");
      client.print(inputString);
      client.println("</h3>");
      dt = inputString;

      client.println("</body>");
      client.println("</html>");

      delay(1);

      client.stop();
    } 
  } else {
    if (dt != "") {
      client.print("<h3>");
      client.print(dt);
      client.println("</h3>");
      inputString = "";

      client.println("</body>");
      client.println("</html>");

      delay(1);

      client.stop();
    }
  }

  client.println("</body>");
  client.println("</html>");

  delay(1);

  client.stop();
}
