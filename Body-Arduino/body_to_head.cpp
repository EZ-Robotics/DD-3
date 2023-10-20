#include <Arduino.h>
#include <SoftwareSerial.h>

#include "body_to_head.hpp"

// Based on
// https://arduino.stackexchange.com/questions/72138/send-structure-through-serial
// and
// https://docs.arduino.cc/learn/built-in-libraries/software-serial

SEND_DATA_STRUCTURE BtH_data;

// SoftwareSerial mySerial(3, 2);  // RX, TX

int size_data = sizeof(struct SEND_DATA_STRUCTURE);
void send(const SEND_DATA_STRUCTURE* table) {
  Serial1.write((const char*)table, size_data);
}

void body_to_head_init() {
  //Serial1.begin(9600);
}

void body_to_head_send() {
  send(&BtH_data);
  Serial1.println();
}

/*
int timer = 0;
void body_to_head_send() {
  timer += 10;
  if (timer >= 150) {
    send(&BtH_data);
    mySerial.println();
    timer = 0;
  }
}
*/

/*
void send(int data) {
  analogWrite(A0, data);
}

void body_to_head_init() {
  pinMode(A0, OUTPUT);  // sets the pin as output
}

int counter = 0;
int send_data[4];
void body_to_head_send() {
  send_data[0] = (BtH_data.eye_y_ + 127.0) / 4.0;
  send_data[1] = ((BtH_data.eye_x_ + 127.0) / 4.0) + 63.75;
  send_data[2] = ((BtH_data.eyebrow_left_ + 127.0) / 4.0) + (63.75 * 2);
  send_data[3] = ((BtH_data.eyebrow_right_ + 127.0) / 4.0) + (63.75 * 3);

  send(send_data[counter]);
  counter++;
  if (counter == 4) counter = 0;

  int eye_y = (send_data[0] * 4.0) - 127;
  int eye_x = ((send_data[1] - 63.75));
  int eyebrow_left = ((send_data[2]) - (63.75 * 2.0));
  // int eyebrow_left = ((send_data[2] * 4.0) - (63.75 * 2)) - 127;
  int eyebrow_right = ((send_data[3] * 4.0) - (63.75 * 3)) - 127;

  Serial.print(BtH_data.eye_x_);
  Serial.print("\t");
  Serial.print(send_data[1]);
  Serial.print("\t");
  Serial.print(eye_x);

  Serial.print("\n");


  //if (timer >= 150) {
  //  send(&BtH_data);
  //  mySerial.println();
  //  timer = 0;
  //}

}
*/

/*
struct SEND_DATA_STRUCTURE {
  // put your variable definitions here for the data you want to send
  // THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t eye_y_;
  int16_t eye_x_;
  int16_t eyebrow_left_;
  int16_t eyebrow_right_;
};
*/