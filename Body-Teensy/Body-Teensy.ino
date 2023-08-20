#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <SoftEasyTransfer.h>
/*   For Arduino 1.0 and newer, do this:   */
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1);
/*   For Arduino 22 and older, do this:   */
//#include <NewSoftSerial.h>
//NewSoftSerial mySerial(2, 3);
//create object
SoftEasyTransfer ET; 
struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t blinks;
  int16_t pause;
};
//give a name to the group of data
SEND_DATA_STRUCTURE mydata;
void easytransfer_init() {
  mySerial.begin(9600);
  //start the library, pass in the data details and the name of the serial port.
  ET.begin(details(mydata), &mySerial);
  pinMode(13, OUTPUT);
  randomSeed(analogRead(0));
}

#define SWITCH 2

#define HEAD_SPIN 3
Servo headspin;

#define HEAD_TILT 15   // 16th channel on PCA9685
#define SERVOMIN 350   // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 425   // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates

#define R_MOTOR_CH 21
#define L_MOTOR_CH 20
#define CH1 15
#define CH2 14
#define CH3 23
#define CH4 22

#include <Audio.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
Servo L_MOTOR;  // create servo object to control the ESC
Servo R_MOTOR;  // create servo object to control the ESC

bool switch_enabled() {
  return digitalRead(SWITCH);
}
void switch_init() {
  pinMode(SWITCH, INPUT);
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
    r = r * 1.2;
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

double FWD_SCALE = 5.0;
double TURN_SCALE = 8.0;
double fwd_curve(double x) {
  return (powf(2.718, -(FWD_SCALE / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(FWD_SCALE / 10)))) * x;
}
double turn_curve(double x) {
  return (powf(2.718, -(TURN_SCALE / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(TURN_SCALE / 10)))) * x;
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
  easytransfer_init();

  delay(10);
}

void loop() {
  /*
  double ch3 = fwd_curve(ch(CH3));
  double ch4 = turn_curve(ch(CH4));
  int left = ch3 + ch4;
  int right = ch3 - ch4;
  head_set(ch(CH1));
  set_tilt(ch(CH2));
  drive_set(left, right);
  */

    //this is how you access the variables. [name of the group].[variable name]
  mydata.blinks = random(5);
  mydata.pause = random(5);
  //send the data
  ET.sendData();
  Serial.println(mydata.blinks);
  Serial.println(mydata.pause);
  Serial.println();
  
  //Just for fun, we will blink it out too
   for(int i = mydata.blinks; i>0; i--){
      digitalWrite(13, HIGH);
      delay(mydata.pause * 100);
      digitalWrite(13, LOW);
      delay(mydata.pause * 100);
    }
  
  delay(5000);
  

  delay(10);
}