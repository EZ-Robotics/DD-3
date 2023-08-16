#include <Adafruit_PWMServoDriver.h>

#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void pwm_init() {
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

// Eye Y
#define EYE_Y 0
#define EYE_Y_MIN 150
#define EYE_Y_MAX 300
void eye_y_set(int input) {
  // if (switch_enabled()) {
    input = map(input, -127, 127, EYE_Y_MIN, EYE_Y_MAX);
    pwm.setPWM(EYE_Y, 0, input);
  // }
}

// Eye X
#define EYE_X 1
#define EYE_X_MIN 150
#define EYE_X_MAX 300
void eye_x_set(int input) {
  // if (switch_enabled()) {
    input = map(input, -127, 127, EYE_X_MIN, EYE_X_MAX);
    pwm.setPWM(EYE_X, 0, input);
  // }
}

// Eyebrow Right
#define EYEBROW_RIGHT 2
#define EYEBROW_RIGHT_MIN 300
#define EYEBROW_RIGHT_MAX  400
void eyebrow_right_set(int input) {
  // if (switch_enabled()) {
    input = map(input, -127, 127, EYEBROW_RIGHT_MIN, EYEBROW_RIGHT_MAX);
    pwm.setPWM(EYEBROW_RIGHT, 0, input);
  // }
}

// Eyebrow Right
#define EYEBROW_LEFT 3
#define EYEBROW_LEFT_MIN 150
#define EYEBROW_LEFT_MAX  200
void eyebrow_left_set(int input) {
  // if (switch_enabled()) {
    input = map(input, -127, 127, EYEBROW_LEFT_MAX, EYEBROW_LEFT_MIN);
    pwm.setPWM(EYEBROW_LEFT, 0, input);
  // }
}


void setup() {
  // put your setup code here, to run once:
  pwm_init();
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = -127; i < 127; i+=2) {
    eye_y_set(i);
    eye_x_set(i);
    eyebrow_right_set(i);
    eyebrow_left_set(i);
    //delay(10);
    delay(1);
  }

  for (int i = 127; i > -127; i-=2) {
    eye_y_set(i);
    eye_x_set(i);
    eyebrow_right_set(i);
    eyebrow_left_set(i);
    //delay(10);
    delay(1);
  }

}
