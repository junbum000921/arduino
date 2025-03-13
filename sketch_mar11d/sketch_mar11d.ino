
#define TRIG 3
#define ECHO 2
#define motor 6

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(motor, OUTPUT);
  Serial.begin(9600);
  delay(1000);
}

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
    analogWrite(motor, 200);
  }
  else{
    analogWrite(motor,0);
  }
  delay(1000);
}
