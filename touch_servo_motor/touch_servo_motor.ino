/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>
#define touch 8
#define motor 6
Servo myservo;  // create Servo object to control a servo
// twelve Servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
void motor_control(int speed);
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the Servo object
  pinMode(touch, INPUT);
  pinMode(motor, OUTPUT);
  Serial.begin(9600);
}
int move_servo=-1;
int reverse=0;
int power;
int lotate=0;
void loop() {
  if(digitalRead(touch)==HIGH){
    
    int start = millis();
    while(digitalRead(touch)==HIGH);
    int end = millis()-start;
    if(end>=1000 && end<=3000){
      move_servo++;
      Serial.println("Servo mode changed");
      if(move_servo==1){
        Serial.println("move");
      }
      else{
        Serial.println("stop");
      }
    }
    else if(end<1000){
      power++;
      if(power>6){
        power=0;
      }
    }
    Serial.println(end);
    Serial.println(move_servo);
  }
  if(move_servo%2==1 && power != 0){
    if(reverse==0){
      lotate++;
    }
    else if(reverse==1){
      lotate--;
    }
    if(lotate>120){
      reverse=1;
    }
    else if(lotate<0){
      reverse=0;
    }

  }

  motor_control(power*50);
  myservo.write(lotate);
  delay(15);

  
}

void motor_control(int speed){
  analogWrite(motor, speed);
}

