#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      12
#define ECHO           2
#define TRIG           3
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void rainbow();
int delayval = 500; // delay for half a second

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  pixels.begin(); // This initializes the NeoPixel library.
  //pinMode(TOUCH, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

}
int lotation = 0;
int prev_lotation=0;
int count=0;
int bright=0;
int reverse_flag=0;
int bright_interval=500;
int interval = 100;
void loop() {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH);
  if(duration == 0){
    return;
  }
  long distance = duration / 58;
  
  /*if(digitalRead(TOUCH) == HIGH){
    if(reverse_flag == 0){ 
      count++;
      if(count>5){
        reverse_flag=1;
        count--;
      }
      
    }
    else if(reverse_flag == 1){
      count--;
      if(count<0){
        reverse_flag=0;
        count++;
      }
    }
    int start = millis();
    while(digitalRead(TOUCH)==HIGH);
    if(millis()-start>2000){
      count=0;
      reverse_flag=0;
    }
  }
  bright=count*20;
  if(count==5){
    pixels.setPixelColor(0, pixels.Color(100,0,0));
    pixels.setPixelColor(1, pixels.Color(255,140,0));
    pixels.setPixelColor(2, pixels.Color(100,100,0));
    pixels.setPixelColor(3, pixels.Color(0,100,0));
    pixels.setPixelColor(4, pixels.Color(0,0,100));
    pixels.setPixelColor(5, pixels.Color(50,0,100));
    pixels.setPixelColor(6, pixels.Color(100,0,100));
    pixels.setPixelColor(7, pixels.Color(100,0,0));
    pixels.setPixelColor(8, pixels.Color(255,140,0));
    pixels.setPixelColor(9, pixels.Color(100,100,0));
    pixels.setPixelColor(10, pixels.Color(0,100,0));
    pixels.setPixelColor(11, pixels.Color(0,0,100));
  }*/
  if(distance<10){
    interval = 100;
  }
  else if(distance>=10 && distance <20){
    interval = 500;
  }
  else{
    interval = 1000;
  }
  for(int i=0; i<NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(20,20,20)); 
  }
  pixels.show();
  delay(interval);
  for(int i=0; i<NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(0,0,0)); 
  }
  pixels.show();
  delay(interval);
}
