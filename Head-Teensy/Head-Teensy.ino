#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <SoftEasyTransfer.h>
 
/*   For Arduino 1.0 and newer, do this:   */
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1);
 
//create object
SoftEasyTransfer BtH; 
 
struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t eye_y_;
  int16_t eye_x_;
  int16_t eyebrow_left_;
  int16_t eyebrow_right_;
};
//give a name to the group of data
SEND_DATA_STRUCTURE BtH_data;
//give a name to the group of data
void easytransfer_init() {
  mySerial.begin(9600);
  //start the library, pass in the data details and the name of the serial port.
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
  //check and see if a data packet has come in. 
  if(BtH.receiveData()){
 
    //this is how you access the variables. [name of the group].[variable name]
    //since we have data, we will blink it out. 
    /*Serial.println(mydata.switch_);
    Serial.println(mydata.eye_y_);
    Serial.println(mydata.eye_x_);
    Serial.println(mydata.eyebrow_right_);
    Serial.println(mydata.eyebrow_left_);
    Serial.println();*/
  Serial.println(BtH_data.eye_y_);
  Serial.println(BtH_data.eye_x_);
  Serial.println(BtH_data.eyebrow_left_);
  Serial.println(BtH_data.eyebrow_right_);
  Serial.println();

  eye_y_set(BtH_data.eye_y_);
  eye_x_set(BtH_data.eye_x_);
  eyebrow_left_set(BtH_data.eyebrow_left_);
  eyebrow_right_set(BtH_data.eyebrow_right_);
  
  }
 
    // Serial.println();
    //this is how you access the variables. [name of the group].[variable name]
 
  // put your main code here, to run repeatedly:
 
 
  //for (int i = -127; i < 127; i+=2) {
    //eye_y_set(i);
    //eye_x_set(i);
    //eyebrow_right_set(i);
    //eyebrow_left_set(i);
    //delay(10);
    //delay(1);
  //}
  //delay(125);
 
  //for (int i = 127; i > -127; i-=2) {
    //eye_y_set(i);
    //eye_x_set(i);
    //eyebrow_right_set(i);
    //eyebrow_left_set(i);
    //delay(10);
    //delay(1);
  //}
  delay(10);
 
}
 
void receive(int numBytes) {}