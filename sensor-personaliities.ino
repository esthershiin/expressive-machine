#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <stdlib.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  130 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  470 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// +++ Photocell Sensors +++
float env1 = 0;
float env2 = 0;

// +++++ Servo Motors +++++
int degree1 = 0;
int degree2 = 0;
int degree3 = 0;
int dir1 = 1;
int dir2 = 1;
int dir3 = 1;

// +++++++++++++++++++++++++++

// put your setup code here, to run once:
void setup() {

  // get average sensor readings of environment
  float total1 = 0;
  float total2 = 0;
  for (int i = 0; i < 50; i++) {
    total1 += analogRead(A0);
    total2 += analogRead(A1);
    delay(10);
  }
  env1 = total1 / 50;
  env2 = total2 / 50;

  // start servo driver
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  Serial.begin(9600);

  // initial open state
  int pulseLen = map(0, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(0, 0, pulseLen);
  pwm.setPWM(1, 0, pulseLen);
  pwm.setPWM(2, 0, pulseLen);
}

// put your main code here, to run repeatedly:
void loop() {
  
  /* 
  Config 0 -> Paused
  Config 1 -> Back and Forth Movement
  Config 2 -> Sensor activation (initially open; 1=closed 2=openclose 3=nothing)
  Config 3 -> Wave
  */
  int closed = map(180, 0, 180, SERVOMIN, SERVOMAX);
  int open = map(0, 0, 180, SERVOMIN, SERVOMAX);
  
  // sensor 1 (flower1)
  float total = 0;
  for (int i = 0; i < 50; i++) {
    total += analogRead(A0);
    delay(10);
  }
  float sensorValue1 = total / 50;
  if (sensorValue1 < env1 * 0.5) {
    pwm.setPWM(0, 0, closed);
    delay(3000);
    pwm.setPWM(0, 0, open);
  }

  // sensor 2 (flower2)
  total = 0;
  for (int i = 0; i < 50; i++) {
    total += analogRead(A1);
    delay(10);
  }
  float sensorValue2 = total / 50;
  if (sensorValue2 < env2 * 0.5) {
    pwm.setPWM(1, 0, closed);
    delay(400);
    pwm.setPWM(1, 0, open);
    delay(400);
    pwm.setPWM(1, 0, closed);
    delay(400);
    pwm.setPWM(1, 0, open);
    delay(400);
    pwm.setPWM(1, 0, closed);
    delay(400);
    pwm.setPWM(1, 0, open);
    delay(400);
    pwm.setPWM(1, 0, closed);
    delay(400);
    pwm.setPWM(1, 0, open);
  }
}

// +++++++++++++++++++++++++++

void readSensors() {
  int sensorValue1 = analogRead(A0);
  int sensorValue2 = analogRead(A1);

  Serial.println(sensorValue1);
  Serial.println(sensorValue2);
  Serial.println("+++++");
  delay(500);
}

void moveServo1(float spd) {
  if (degree1 > 180 || degree1 < 0) {
    dir1 *= -1;
  }
  degree1 = degree1 + dir1 * spd;

  int pulseLen = map(degree1, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(0, 0, pulseLen);
}

void moveServo2(float spd) {
  if (degree2 > 180 || degree2 < 0) {
    dir2 *= -1;
  }
  degree2 = degree2 + dir2 * spd;

  int pulseLen = map(degree2, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(1, 0, pulseLen);
}


void moveServo3(float spd) {
  if (degree3 > 180 || degree3 < 0) {
    dir3 *= -1;
  }
  degree3 = degree3 + dir3 * spd;

  int pulseLen = map(degree3, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(2, 0, pulseLen);
}
