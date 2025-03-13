#include <IRremote.h>
int IRSensor = 2;
int Toggle = 0;
void setup()
{
IrReceiver.begin(IRSensor);
Serial.begin(9600);
pinMode(3, OUTPUT);
}
void loop()
{
if (IrReceiver.decode()){
// 리모컨 신호가 들어온다면?
unsigned long code = IrReceiver.decodedIRData.decodedRawData;
// 리모컨 신호를 code 변수에 저장
Serial.println(code, HEX); // 시리얼로 리모컨 신호 출력
if (code == 0xFF00BF00){
// 리모컨으로 원하는 값이 들어왔다면?
Toggle = !Toggle;
digitalWrite(3,Toggle);
}
IrReceiver.resume();
}
delay(300);
}