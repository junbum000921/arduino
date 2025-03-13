#define touch 7
#define motor 6
int step=1;
void setup() {
  pinMode(motor,OUTPUT);
  pinMode(touch,INPUT);
}

void loop() {
  int value = digitalRead(touch);

  analogWrite(motor, 100);
  if(value==HIGH){
    step++;
    switch(step){

      case 1:
        analogWrite(motor, 50);
        break;
      case 2:
        analogWrite(motor, 100);
        break;
      case 3:
        analogWrite(motor, 150);
        break;
      case 4:
        analogWrite(motor, 200);
        break;
      case 5:
        analogWrite(motor, 250);
        break;
      case 6:
        analogWrite(motor, 0);
        step=0;
        break;


    }
  }
  
}
