#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#define TRIGGERPIN D1
#define ECHOPIN    D2

Servo servo;

char auth[] = "KQ4FwCAVW8G_NerZd_R46mcAJWhMGoaQ";
char ssid[] = "TAMUNUSAIBAH";
char pass[] = "sayatamu";

WidgetLCD lcd(V1);
BLYNK_WRITE(V2){
  servo.write(90);
  delay(100);
  servo.write(0);
}

void setup(){
  Serial.begin(9600);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8080);
  servo.attach(D8);
  lcd.clear(); 
  lcd.print(2, 0, "Makanan Ikan"); 
}

void loop(){
  lcd.clear();
  lcd.print(2, 0, "Makanan Ikan"); 
  long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
  
  if(distance <= 3){
    lcd.print(2, 1, "Masih Banyak!");
    if(distance <= 2){
      Blynk.virtualWrite(V3, 80);
    } else if(distance == 3){
      Blynk.virtualWrite(V3, 70);
    }
  } else if(distance > 3 && distance <= 5){
    lcd.print(0, 1, "Tinggal Setengah!");
    if(distance == 4){
      Blynk.virtualWrite(V3, 60);
    } else if(distance == 5){
      Blynk.virtualWrite(V3, 50);
    } else if(distance == 6){
      Blynk.virtualWrite(V3, 40);
    }
  } else if(distance > 5 && distance < 8){
    lcd.print(0, 1, "Tinggal Sedikit!");
    if(distance == 6){
      Blynk.virtualWrite(V3, 30);
    } else if(distance == 7){
      Blynk.virtualWrite(V3, 10);
    }
  } else if(distance >= 8){
    lcd.print(4, 1, "Habis!!!");
    Blynk.virtualWrite(V3, 5);
  }
  
  Serial.print(distance);
  Serial.println("Cm");
  
  Blynk.run();

  delay(1000);
}
