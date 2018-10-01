#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h> 

ESP8266WebServer server(80);
Servo myservo;  

char ssid[] = "WIFISSID";
char pass[] = "PASSWORD";
 
void setup(void){
  delay(1000);
  WiFi.disconnect();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  Serial.begin(115200);
  myservo.attach(2);

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
    server.send(200, "text/html", "<h1>ESP8266 Servo Motor</h1><a href=\"/0\"><button style=\"font-size:2em\">0</button></a><a href=\"/90\"><button style=\"font-size:2em\">90</button></a>");
  });
  server.on("/0", [](){//ON 으로 접속시 LED를 켭니다.
    //myservo.write(0);
    int pos;
  for(pos = 0; pos <= 180; pos += 1){
    myservo.write(pos);
    delay(15);
  } 
  for(pos = 180; pos>=0; pos-=1){                                
    myservo.write(pos); 
    delay(15); 
  } 
     server.send(200, "text/html", "<h1>Servo 0</h1><a href=\"/0\"><button style=\"font-size:2em\">0</button></a><a href=\"/90\"><button style=\"font-size:2em\">90</button></a>");
  });
  server.on("/90", [](){//OFF 으로 접속시 LED를 끕니다.
    myservo.write(90);
    server.send(200, "text/html", "<h1>Servo 90</h1><a href=\"/0\"><button style=\"font-size:2em\">0</button></a><a href=\"/90\"><button style=\"font-size:2em\">90</button></a>");
  });
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
