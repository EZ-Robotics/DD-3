#include <SoftEasyTransfer.h>
/*   For Arduino 1.0 and newer, do this:   */
#include <SoftwareSerial.h>
#include "body_to_head.hpp"

SEND_DATA_STRUCTURE BtH_data;
SoftEasyTransfer BtH;

SoftwareSerial mySerial(0, 1);
/*   For Arduino 22 and older, do this:   */
//#include <NewSoftSerial.h>
//NewSoftSerial mySerial(2, 3);
//create object

void body_to_head_init() {
  mySerial.begin(9600);
  //start the library, pass in the data details and the name of the serial port.
  BtH.begin(details(BtH_data), &mySerial);
  pinMode(13, OUTPUT);
  randomSeed(analogRead(0));
}

void body_to_head_send() {
  BtH.sendData();
}