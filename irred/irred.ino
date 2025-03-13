#include <IRremote.h>
#include <Servo.h>
Servo servo;
int value = 0;
int S = 5;
int IRSensor = 2;
int led = 3;
int bright = 120;
int Toggle = 0;
void setup()
{
servo.attach(S);
IrReceiver.begin(IRSensor);
pinMode(led,OUTPUT);
Serial.begin(9600);

}
void loop()
{
  servo.write(value);
if (IrReceiver.decode()){
// 리모컨 신호가 들어온다면?
unsigned long code = IrReceiver.decodedIRData.decodedRawData;
// 리모컨 신호를 code 변수에 저장
Serial.println(code, HEX); // 시리얼로 리모컨 신호 출력
if (code == 0xBF40FF00){
// 리모컨으로 원하는 값이 들어왔다면?
Toggle = !Toggle;
digitalWrite(led,Toggle);
}
else if(code == 0xBC43FF00){
  value+=30;
  if (value>=180){
    value=180;
  }
}
else if(code == 0xBB44FF00){
  value-=30;
  if (value<=0){
    value=0;
  }
}
Serial.println(value);
IrReceiver.resume();
}
delay(10);
}