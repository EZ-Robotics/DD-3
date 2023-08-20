#pragma once

#include <SoftEasyTransfer.h>

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t eye_y_;
  int16_t eye_x_;
  int16_t eyebrow_left_;
  int16_t eyebrow_right_;
};
//give a name to the group of data
extern SEND_DATA_STRUCTURE BtH_data;

extern SoftEasyTransfer BtH; 

void body_to_head_init();
void body_to_head_send();