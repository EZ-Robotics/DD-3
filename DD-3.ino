#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SWITCH 0
#define HEAD_SPIN A0
#define HEAD_TILT 15   // 16th channel on PCA9685
#define SERVOMIN 350   // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 425   // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 600      // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2400     // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates
#define R_MOTOR_CH 21
#define L_MOTOR_CH 20
#define CH1 15
#define CH2 16
#define CH3 17
#define CH4 22


Servo headspin;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Servo L_MOTOR;  // create servo object to control the ESC
Servo R_MOTOR;  // create servo object to control the ESC

bool switch_enabled() {
  return digitalRead(SWITCH);
}
void switch_init() {
  headspin.attach(HEAD_SPIN);
}

void head_set(int input) {
  if (switch_enabled()) {
    headspin.write(map(input, -127, 127, 20, 170));
  } else {
    headspin.write(0);
  }
}
void head_init() {
  headspin.attach(HEAD_SPIN);
}

void pwm_init() {
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}
void set_tilt(int input) {
  if (switch_enabled()) {
    input = map(input, -127, 127, SERVOMIN, SERVOMAX);
    pwm.setPWM(HEAD_TILT, 0, input);
  }
}

void drive_init() {
  L_MOTOR.attach(L_MOTOR_CH, 1000, 2000);  // (pin, min pulse width, max pulse width in microseconds)
  R_MOTOR.attach(R_MOTOR_CH, 1000, 2000);  // (pin, min pulse width, max pulse width in microseconds)
}
void drive_set(double l, double r) {
  if (switch_enabled()) {
    l = l - 5;
    L_MOTOR.write(map(l, -127, 127, 0, 180));  // Send the signal to the ESC
    R_MOTOR.write(map(r, -127, 127, 0, 180));  // Send the signal to the ESC
  } else {
    l = 0;
    r = 0;
    l = l - 5;
    L_MOTOR.write(map(l, -127, 127, 0, 180));  // Send the signal to the ESC
    R_MOTOR.write(map(r, -127, 127, 0, 180));  // Send the signal to the ESC
  }
}

void receiver_init() {
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
}
int ch(int channel) {
  return map(pulseIn(channel, HIGH, 30000), 990, 2014, -127, 127);
}

void setup() {
  // put your setup code here, to run once:
  switch_init();
  head_init();
  pwm_init();
  drive_init();
  receiver_init();
  delay(10);
}

void loop() {
  int left = ch(CH3) + ch(CH4);
  int right = ch(CH3) - ch(CH4);
  head_set(ch(CH1));
  set_tilt(ch(CH2));
  drive_set(left, right);



  delay(10);
}
