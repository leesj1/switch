#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);

int led = D2;

char ssid[] = "WIFISSID";
char pass[] = "PASSWORD";
 
void setup(void){
  delay(1000);
  WiFi.disconnect();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Serial.begin(115200);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", [](){
    server.send(200, "text/html", "<h1>ESP8266 LED</h1><a href=\"/on\"><button style=\"font-size:2em\">ON</button></a><a href=\"/off\"><button style=\"font-size:2em\">Off</button></a>");
  });
  server.on("/on", [](){
    digitalWrite(led, HIGH);
    server.send(200, "text/html", "<h1>LED On</h1><a href=\"/on\"><button style=\"font-size:2em\">ON</button></a><a href=\"/off\"><button style=\"font-size:2em\">Off</button></a>");
  });
  server.on("/off", [](){
    digitalWrite(led, LOW);
    server.send(200, "text/html", "<h1>LED Off</h1><a href=\"/on\"><button style=\"font-size:2em\">ON</button></a><a href=\"/off\"><button style=\"font-size:2em\">Off</button></a>");
  });
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
