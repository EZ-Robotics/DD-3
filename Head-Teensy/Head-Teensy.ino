#include <Adafruit_PWMServoDriver.h>
#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial mySerial(0, 1);

// Based on
// https://github.com/madsci1016/Arduino-EasyTransfer/tree/master/SoftEasyTransfer

// create object
SoftEasyTransfer BtH;

struct SEND_DATA_STRUCTURE {
  int16_t eye_y_;
  int16_t eye_x_;
  int16_t eyebrow_left_;
  int16_t eyebrow_right_;
};

SEND_DATA_STRUCTURE BtH_data;

void easytransfer_init() {
  mySerial.begin(9600);
  BtH.begin(details(BtH_data), &mySerial);
}

#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41, Wire);

void pwm_init() {
  Wire.setSCL(19);
  Wire.setSDA(18);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

// Eye Y
#define EYE_Y 12
void eye_y_set(int input) {
  pwm.setPWM(EYE_Y, 0, input);
}

// Eye X
#define EYE_X 13
void eye_x_set(int input) {
  pwm.setPWM(EYE_X, 0, input);
}

// Eyebrow Right
#define EYEBROW_RIGHT 0
void eyebrow_right_set(int input) {
  pwm.setPWM(EYEBROW_RIGHT, 0, input);
}

// Eyebrow Right
#define EYEBROW_LEFT 1
void eyebrow_left_set(int input) {
  pwm.setPWM(EYEBROW_LEFT, 0, input);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  easytransfer_init();
  pwm_init();
}

void loop() {
  // check and see if a data packet has come in.
  if (BtH.receiveData()) {
    /*
    Serial.println(BtH_data.eye_y_);
    Serial.println(BtH_data.eye_x_);
    Serial.println(BtH_data.eyebrow_left_);
    Serial.println(BtH_data.eyebrow_right_);
    Serial.println();
    */

    eye_y_set(BtH_data.eye_y_);
    eye_x_set(BtH_data.eye_x_);
    eyebrow_left_set(BtH_data.eyebrow_left_);
    eyebrow_right_set(BtH_data.eyebrow_right_);
  }

  delay(10);
}

void receive(int numBytes) {}