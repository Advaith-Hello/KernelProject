#pragma once

#include <stdint.h>
#include <stddef.h>



typedef struct {
  char buffer[256];
  volatile int latest_idx;
} stream_object;


extern uint8_t control_char;
extern stream_object keyboard_stream;


int init_keyboard_streams(void);
int input_stdin(char* buffer, size_t buffer_len);

void push_to_key_stream(char chr);
char get_from_key_stream(int stream_idx);


/* Special char table 
 *
 *  LEFT SHIFT  = bit 1 = 0x33
 *  LEFT CTRL   = bit 2 = 0x34
 *  SUPER       = bit 3 = 0x35
 *  LEFT ALT    = bit 4 = 0x36
 *  RIGHT ALT   = bit 5 = 0x37
 *  MENU        = bit 6 = 0x38
 *  RIGHT CTRL  = bit 7 = 0x39
 *  RIGHT SHIFT = bit 8 = 0x3A
 * 
 * */

