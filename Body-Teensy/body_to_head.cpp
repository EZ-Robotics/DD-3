#include <Arduino.h>

#include "body_to_head.hpp"

// Based on
// https://arduino.stackexchange.com/questions/72138/send-structure-through-serial

SEND_DATA_STRUCTURE BtH_data;

int size_data = sizeof(struct SEND_DATA_STRUCTURE);
void send(const SEND_DATA_STRUCTURE* table) {
  Serial1.write((const char*)table, size_data);
}

void body_to_head_init() {
  Serial1.begin(9600);
}

void body_to_head_send() {
  send(&BtH_data);
  Serial1.println();
}
