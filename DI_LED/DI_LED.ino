#include "DHT.h"
#define DHTPIN 2    
#define DHTTYPE DHT11   // DHT 11
#define R 9
#define G 6
#define B 5


DHT dht(DHTPIN, DHTTYPE);

void colorPrint(int red, int green, int blue);

void setup() {
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

  if(di>=80){
    colorPrint(255,0,0);
  }
  else if(di>=75){
    colorPrint(255,128,0);
  }
  else if(di>=68){
    colorPrint(0,255,0);
  }
  else{
    colorPrint(0,0,255);
  }
  Serial.print("DI : ");
  Serial.println(di, 1);
  Serial.print("Humidity : ");
  Serial.print(h,1);
  Serial.println("%");
  Serial.print("Temperature : ");
  Serial.print(t,1);
  Serial.println("C");


}

void colorPrint(int red, int green, int blue){
  analogWrite(R, red);
  analogWrite(G, green);
  analogWrite(B, blue);
}
