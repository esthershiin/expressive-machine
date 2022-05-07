#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <stdlib.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  130 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  470 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// +++++ Servo Motors +++++
float degree1 = 0;
float degree2 = 0;
float degree3 = 0;
int dir1 = 1;
int dir2 = 1;
int dir3 = 1;

// +++++++++++++++++++++++++++

// put your setup code here, to run once:
void setup() {

  // start servo driver
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  Serial.begin(9600);
}

// put your main code here, to run repeatedly:
void loop() {

  /* 
  Config 0 -> Paused
  Config 1 -> Back and Forth Movement
  Config 2 -> Sensor activation (initially open; 1=closed 2=openclose 3=nothing)
  Config 3 -> Wave
  */
  
  moveServo1(1);
  moveServo2(1);
  moveServo3(1);
  delay(15);
}

// +++++++++++++++++++++++++++

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
