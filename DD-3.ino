#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SWITCH 0
#define HEAD_SPIN A0
#define HEAD_TILT 15 // 16th channel on PCA9685
#define SERVOMIN 350   // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 425   // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 600      // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2400     // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates

Servo headspin;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

bool switch_enabled() { return digitalRead(SWITCH); }
void switch_init() { headspin.attach(HEAD_SPIN); }

void head_set(int input) {
  if (switch_enabled()) {
    headspin.write(input);
  } else {
    headspin.write(0);
  }
}
void head_init() { headspin.attach(HEAD_SPIN); }

void pwm_init() {   
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}
void set_tilt(int input) {
  if (switch_enabled()) {
    input = map(input, -100, 100, SERVOMIN , SERVOMAX); 
    pwm.setPWM(HEAD_TILT, 0, input);
  } 
}

void setup() {
  // put your setup code here, to run once:
  switch_init();
  head_init();
  pwm_init();
  delay(10);
}

void loop() {
  printf("%i\n", switch_enabled());

  head_set(160);

  for (uint16_t pulselen = 0; pulselen < 100; pulselen++) {
    set_tilt(pulselen);
  }
 
  delay(100);
  for (uint16_t pulselen = 100; pulselen > 0; pulselen--) {
     set_tilt(pulselen);
  }
  delay(100);
}
