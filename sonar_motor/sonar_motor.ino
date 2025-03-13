#define TRIG 3
#define ECHO 2
#define motor 6
#include "DHT.h"
#define DHTPIN 7    
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(motor, OUTPUT);
  dht.begin();
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float di = (float)9/5*t-0.55*((float)1-h/100)*((float)9/5*t-26)+32;
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO,HIGH);
  if(duration == 0){
    return;
  }
  long distance = duration / 58;
  Serial.print(distance, 1);
  Serial.println("cm");
  Serial.println(di,1);
  if(distance<10){
    if(di>=67){
      analogWrite(motor, 250);
    }
    else if(di>=65){
       analogWrite(motor, 170);
     }
    else{
       analogWrite(motor, 100);
    }
  }
  else{
    analogWrite(motor, 0);
  }
  delay(1000);
}
