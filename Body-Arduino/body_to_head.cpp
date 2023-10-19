#include <Arduino.h>
#include <SoftwareSerial.h>

#include "body_to_head.hpp"

// Based on
// https://arduino.stackexchange.com/questions/72138/send-structure-through-serial

SEND_DATA_STRUCTURE BtH_data;

SoftwareSerial mySerial(2, 3);  // RX, TX

int size_data = sizeof(struct SEND_DATA_STRUCTURE);
void send(const SEND_DATA_STRUCTURE* table) {
  mySerial.write((const char*)table, size_data);
}

void body_to_head_init() {
  mySerial.begin(9600);
}

void body_to_head_send() {
  send(&BtH_data);
  mySerial.println();
}
