#include "DHT.h"
#define DHTPIN 7    
#define DHTTYPE DHT11   // DHT 11
#define motor 6
int step=0;

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  pinMode(motor,OUTPUT);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
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

  if(di>=67){
    analogWrite(motor, 250);
  }
  else if(di>=65){
    analogWrite(motor, 170);
  }
  else{
    analogWrite(motor, 100);
  }
  Serial.println(di, 1);
  delay(15);
  
}
