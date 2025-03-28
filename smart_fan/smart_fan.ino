#include <U8glib.h>
#include "DHT.h"
#define DHTPIN 7    
#define DHTTYPE DHT11
#include <Servo.h>
#define touch 8
#define motor 6
#define TRIG 3
#define ECHO 2
#define R 5
#define G 11
#define B 10

Servo myservo;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
DHT dht(DHTPIN, DHTTYPE);

void motor_control(int speed);
void colorPrint(int red, int green, int blue);
void print_t_h_di_led_oled(int t, int h, int di);

void setup() {
  dht.begin();
  myservo.attach(9);
  pinMode(touch, INPUT);
  pinMode(motor, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(9600);
  delay(1000);
}

int move_servo = 0;
int reverse = 0;
int power = 1;
int lotate = 0;
int automode = 0;

void loop() {
  

  // 온습도 센서 값 읽기
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float di = 9.0 / 5.0 * t - 0.55 * (1 - h / 100.0) * (9.0 / 5.0 * t - 26) + 32;
  print_t_h_di_led_oled(t, h, di);

  // 터치 버튼 동작 처리
  if (digitalRead(touch) == HIGH) {
    Serial.println("Touch detected");
    int start = millis();
    while (digitalRead(touch) == HIGH);
    int press_time = millis() - start;

    if (press_time >= 1000 && press_time <= 3000) {
      move_servo++;
      Serial.println("Movee servo increased");
    } else if (press_time > 3000) {
      automode++;
      Serial.println("Auto mode toggled");
    } else if (press_time < 1000) {
      power++;
      if(power>5){
        power=0;
      }
      Serial.println("Power changed");
    }

    Serial.println(press_time);
    Serial.print("Move Servo : ");
    Serial.println(move_servo);
    Serial.print("POWER : ");
    Serial.println(power);

    Serial.print("auto : ");
    if(automode%2==1){
      Serial.println("ON");
    }
    else{
      Serial.println("OFF");
    }
   
  }

  // 모터 및 서보 제어 로직
  if (automode %2== 0) { // 수동 모드
    if (move_servo%2==1 && power != 0) {
      if(reverse==0){
        lotate=lotate+2;
      }
      else if(reverse==1){
        lotate=lotate-2;
      }
      if (lotate > 60) reverse = 1;
      else if (lotate < 10) reverse = 0;
    }
  } else { // 자동 모드
  // 초음파 센서 거리 측정
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    long duration = pulseIn(ECHO, HIGH, 30000);  // 타임아웃 설정
    long distance = (duration > 0) ? duration / 58 : 999; // 999는 오류 처리

    Serial.print(distance);
    Serial.println("cm");
    delay(2000);
    if (distance <= 10) {
      if (di >= 80) power = 3;
      else if (di >= 70) power = 2;
      
    }
    else power = 0;
  }

  if (move_servo == 0) {
    lotate = 30;
  }

  motor_control(power * 50);
  myservo.write(lotate);
  delay(15);
}

void motor_control(int speed) {
  analogWrite(motor, speed);
}

void colorPrint(int red, int green, int blue) {
  analogWrite(R, red);
  analogWrite(G, green);
  analogWrite(B, blue);
}

void print_t_h_di_led_oled(int temperature, int humidity, int di1) {
  if (di1 >= 80) {
    colorPrint(255, 0, 0);
  } else if (di1 >= 75) {
    colorPrint(255, 128, 0);
  } else if (di1 >= 68) {
    colorPrint(0, 255, 0);
  } else {
    colorPrint(0, 0, 255);
  }

  Serial.print("DI : ");
  Serial.println(di1, 1);
  Serial.print("Humidity : ");
  Serial.print(humidity, 1);
  Serial.println("%");
  Serial.print("Temperature : ");
  Serial.print(temperature, 1);
  Serial.println("C");

  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_fub14);
    u8g.setPrintPos(5, 20);
    u8g.print(temperature, 1);
    u8g.print("\xb0""C");
    u8g.setPrintPos(70, 20);
    u8g.print(humidity, 1);
    u8g.print("%");
    u8g.setFont(u8g_font_fub20);
    u8g.setPrintPos(40, 55);
    u8g.print(di1, 1);
  } while (u8g.nextPage());
}
