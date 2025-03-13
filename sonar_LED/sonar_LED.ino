
#include <U8glib.h>
#define TRIG 3
#define ECHO 2
#define R 11
#define G 10
#define B 9
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(9600);
  delay(1000);
}
int flag=0;
void loop() {
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
  if(distance<10){
    analogWrite(R, 255);
    analogWrite(G, 0);
    analogWrite(B, 0);
    flag=1;
  }
  else{
    analogWrite(R, 0);
    analogWrite(G, 255);
    analogWrite(B, 0);
    flag=0;
  }
  delay(1000);
  u8g.firstPage();
  do{
    u8g.setFont(u8g_font_fub14);
    u8g.setPrintPos(5,20);
    u8g.print(distance);
    u8g.print("cm");
    u8g.setFont(u8g_font_fub14);
    u8g.setPrintPos(5,40);
    if(flag==0){
      u8g.print("OK");
    }
    else{
      u8g.print("FULL");
    }
  }while(u8g.nextPage());
}
