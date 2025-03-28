#define INPUT_PULSE 2
#define OUTPUT_VOLTAGE A5
#define RED_PIN 11
#define GREEN_PIN 10
#define BLUE_PIN 9

float preVoltage = 0;
float voltage = 0;
float dustDensity = 0;
float sumDustDensity = 0;
float avgDustDensity = 0;

void colorPrint(int red, int green, int blue);

void setup() {                
  pinMode(INPUT_PULSE, OUTPUT);
  pinMode(OUTPUT_VOLTAGE, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);
} 

void loop() {
  sumDustDensity = 0;
  for(int i=0; i<30; i++) {
    digitalWrite(INPUT_PULSE, LOW);
    delayMicroseconds(280);
    preVoltage = analogRead(OUTPUT_VOLTAGE);
    delayMicroseconds(40);
    digitalWrite(INPUT_PULSE, HIGH);
    delayMicroseconds(9680);
    voltage = preVoltage * 5.0 / 1024.0;
    dustDensity = (voltage - 0.3) / 0.005;
    sumDustDensity += dustDensity;
    delay(10);
  }
  avgDustDensity = sumDustDensity / 30.0;
  Serial.print("dustDensity : ");
  Serial.println(avgDustDensity);
  
  if(avgDustDensity >= 101) {
    colorPrint(255, 0, 0);
  }
  else if(avgDustDensity >= 51) {
    colorPrint(255, 10, 0);
  } 
  else if(avgDustDensity >= 31) {
    colorPrint(0, 255, 0);
  }
  else {
    colorPrint(0, 0, 255);
  }
  delay(1000);
}

void colorPrint(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}
