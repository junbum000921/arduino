#define TOUCH 2
#define LED 6
int state = 1;
int current_state=1;
int previous_state=0;
void setup() {
  pinMode(TOUCH, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  
}
int mode=0;
void loop() {
  int touch_value = digitalRead(TOUCH);
  current_state = touch_value;
  if (current_state == HIGH){
     mode++;
     int starttime=millis();
     if(mode > 4){
      mode=0;
     }
     while(digitalRead(TOUCH)==HIGH);
     int endtime=millis();
     if(endtime - starttime > 2000){
      mode=0;
     }
    }
  analogWrite(LED,mode*50);
}
