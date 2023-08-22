#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>

#include "body_to_head.hpp"

// Based on
// https://github.com/madsci1016/Arduino-EasyTransfer/tree/master/SoftEasyTransfer

SEND_DATA_STRUCTURE BtH_data;
SoftEasyTransfer BtH;

SoftwareSerial mySerial(0, 1);

void body_to_head_init() {
  mySerial.begin(9600);
  // start the library, pass in the data details and the name of the serial port.
  BtH.begin(details(BtH_data), &mySerial);
}

void body_to_head_send() {
  BtH.sendData();
}