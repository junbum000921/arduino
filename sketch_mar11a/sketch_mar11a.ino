#define PIR 7

void setup() {
  pinMode(PIR, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int status = digitalRead(PIR);
  if(status == HIGH){
    Serial.println("Detected");
  }
  else{
    Serial.println("Not detected");
  }
  delay(1000);
}
