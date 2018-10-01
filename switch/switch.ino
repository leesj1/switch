#define BLYNK_PRINT Serial

#include <Servo.h> 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define button D1

char auth[] = "YOURTOKEN";

char ssid[] = "WIFISSID";
char pass[] = "PASSWORD";

BlynkTimer timer;

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0);
}

Servo myservo1;
Servo myservo2;

bool oneTimeFlag;
bool check;

BLYNK_WRITE(V0){
  int on = param.asInt();
  if(on==1 && check == 0){
    myservo1.write(30);
    delay(500);
    myservo1.write(80);
    delay(500);
    check = 1;
  } else if (on == 0 && check == 1){
    myservo2.write(90);
    delay(500);
    myservo2.write(40);
    delay(500);
    check = 0;
  }
}

void checkPhysical(){
  if(digitalRead(button) == LOW){
    if(oneTimeFlag == 0){
      oneTimeFlag = 1;
      if(check == 0){
        myservo1.write(30);
        delay(500);
        myservo1.write(80);
        delay(500);
     } else if(check == 1){
        myservo2.write(90);
        delay(500);
        myservo2.write(40);
        delay(500);
      }
      check = !check;
      Blynk.virtualWrite(V0, check);
    } 
  } else{
      oneTimeFlag = 0;
  }
}

void setup(){
  myservo1.attach(D3);
  myservo2.attach(D4);
  myservo1.write(80);
  myservo2.write(40);
  pinMode(D1, INPUT_PULLUP);
  Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  timer.setInterval(100L, checkPhysical);
}

void loop(){
  Blynk.run();
  timer.run();  
}
