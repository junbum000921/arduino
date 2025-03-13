#define TOUCH 7
#define LED 6

int count = 0;
int bright = 0;
int current=1;
int previous=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(TOUCH, INPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
}


void loop() {
  if(digitalRead(TOUCH)==HIGH){
    count++;
  }
  if(count%2==0){
    digitalWrite(GREEN,HIGH);
    delay(200);
    digitalWrite(GREEN,LOW);
    delay(200);
  }
  else{
    digitalWrite(RED,HIGH);
    delay(200);
    digitalWrite(RED,LOW);
    delay(200);
  }
  


}
