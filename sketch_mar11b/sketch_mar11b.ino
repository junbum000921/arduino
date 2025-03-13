#define RED 9
#define GREEN 6
#define BLUE 5


void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  for(int r = 200; r>=0; r--){
      for(int b=0; b<200; b++){
        analogWrite(RED, r);
        analogWrite(BLUE, b);
        delay(50);
      }
  }

}
