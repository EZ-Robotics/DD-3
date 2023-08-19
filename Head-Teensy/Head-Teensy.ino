#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <SoftEasyTransfer.h>
 
/*   For Arduino 1.0 and newer, do this:   */
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1);
 
//create object
SoftEasyTransfer ET; 
 
struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t blinks;
  int16_t pause;
};

 
//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;
//give a name to the group of data
void easytransfer_init() {
  mySerial.begin(9600);
  //start the library, pass in the data details and the name of the serial port.
  ET.begin(details(mydata), &mySerial);
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
#define EYE_Y_MIN 150
#define EYE_Y_MAX 300
void eye_y_set(int input) {
  // if (switch_enabled()) {
    input = map(input, -127, 127, EYE_Y_MIN, EYE_Y_MAX);
    pwm.setPWM(EYE_Y, 0, input);
  // }
}
 
// Eye X
#define EYE_X 13
#define EYE_X_MIN 150
#define EYE_X_MAX 300
void eye_x_set(int input) {
  // if (switch_enabled()) {
    input = map(input, -127, 127, EYE_X_MIN, EYE_X_MAX);
    pwm.setPWM(EYE_X, 0, input);
  // }
}
 
// Eyebrow Right
#define EYEBROW_RIGHT 0
#define EYEBROW_RIGHT_MIN 300
#define EYEBROW_RIGHT_MAX  400
void eyebrow_right_set(int input) {
  // if (switch_enabled()) {
    input = map(input, -127, 127, EYEBROW_RIGHT_MIN, EYEBROW_RIGHT_MAX);
    pwm.setPWM(EYEBROW_RIGHT, 0, input);
  // }
}
 
// Eyebrow Right
#define EYEBROW_LEFT 1
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
  Serial.begin(9600);
  easytransfer_init();
  pwm_init();
  pinMode(13, OUTPUT);
}
 
void loop() {
  //check and see if a data packet has come in. 
  if(ET.receiveData()){
 
    //this is how you access the variables. [name of the group].[variable name]
    //since we have data, we will blink it out. 
    /*Serial.println(mydata.switch_);
    Serial.println(mydata.eye_y_);
    Serial.println(mydata.eye_x_);
    Serial.println(mydata.eyebrow_right_);
    Serial.println(mydata.eyebrow_left_);
    Serial.println();*/
    Serial.println(mydata.blinks);
    Serial.println(mydata.pause);
    Serial.println();
        //since we have data, we will blink it out. 
    for(int i = mydata.blinks; i>0; i--){
      digitalWrite(13, HIGH);
      delay(mydata.pause * 100);
      digitalWrite(13, LOW);
      delay(mydata.pause * 100);
    }
  }
 
    // Serial.println();
    //this is how you access the variables. [name of the group].[variable name]
 
  // put your main code here, to run repeatedly:
 
 
  for (int i = -127; i < 127; i+=2) {
    //eye_y_set(i);
    //eye_x_set(i);
    eyebrow_right_set(i);
    //eyebrow_left_set(i);
    //delay(10);
    delay(1);
  }
  delay(125);
 
  for (int i = 127; i > -127; i-=2) {
    //eye_y_set(i);
    //eye_x_set(i);
    eyebrow_right_set(i);
    //eyebrow_left_set(i);
    //delay(10);
    delay(1);
  }
  
  

  delay(125);
 
}
 
void receive(int numBytes) {}