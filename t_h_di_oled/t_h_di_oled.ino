#include <U8glib.h>

#include "DHT.h"
#define DHTPIN 2    
#define DHTTYPE DHT11   
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
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
  u8g.firstPage();
  do{
    u8g.setFont(u8g_font_fub14);
    u8g.setPrintPos(5,20);
    u8g.print(t,1);
    u8g.print("\xb0""C");
    u8g.setPrintPos(70,20);
    u8g.print(h,1);
    u8g.print("%");
    u8g.setFont(u8g_font_fub20);
    u8g.setPrintPos(40,55);
    u8g.print(di,1);
  }while(u8g.nextPage());
}
