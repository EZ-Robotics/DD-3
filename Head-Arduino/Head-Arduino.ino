#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>

// Based on
// https://arduino.stackexchange.com/questions/72138/send-structure-through-serial
// and
// https://docs.arduino.cc/tutorials/communication/SoftwareSerialExample

SoftwareSerial mySerial(2, 3);  // RX, TX

struct SEND_DATA_STRUCTURE {
  int16_t eye_y_;
  int16_t eye_x_;
  int16_t eyebrow_left_;
  int16_t eyebrow_right_;
};

SEND_DATA_STRUCTURE BtH_data;

void easytransfer_init() {
  Serial1.begin(9600);
}

#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41, Wire);

void pwm_init() {
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
  Serial.begin(9600);
  easytransfer_init();
  pwm_init();
}

bool receive(SEND_DATA_STRUCTURE* table) {
  return (Serial1.readBytes((char*)table, sizeof(SEND_DATA_STRUCTURE)) == sizeof(SEND_DATA_STRUCTURE));
}

void loop() {
  receive(&BtH_data);

  Serial.print(BtH_data.eye_y_);
  Serial.print("\t");
  Serial.print(BtH_data.eye_x_);
  Serial.print("\t");
  Serial.print(BtH_data.eyebrow_left_);
  Serial.print("\t");
  Serial.print(BtH_data.eyebrow_right_);
  Serial.print("\t");
  Serial.println();
  /*
  receive(&BtH_data);
  eye_y_set(BtH_data.eye_y_);
  eye_x_set(BtH_data.eye_x_);
  eyebrow_left_set(BtH_data.eyebrow_left_);
  eyebrow_right_set(BtH_data.eyebrow_right_);
  */

  delay(10);
}

void receive(int numBytes) {}