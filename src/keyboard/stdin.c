#include <stddef.h>

#include "vga/print.h"
#include "keyboard/stdin.h"



uint8_t control_char = 0x0;

stream_object ascii_keyboard_stream;


int init_keyboard_streams() {
  ascii_keyboard_stream.latest_idx = 0;
  return 0;
}


void push_to_key_stream(char chr) {
  ascii_keyboard_stream.buffer[
    ascii_keyboard_stream.latest_idx] = chr;
  ascii_keyboard_stream.latest_idx++;
}


char get_from_key_stream(int stream_idx) {
  return ascii_keyboard_stream.buffer[
    (uint8_t)stream_idx];
}


int input_stdin(char* buffer, size_t buffer_len)
{
  int buffer_idx = 0;
  int stream_idx = ascii_keyboard_stream.latest_idx;

  while (buffer_idx < (int)buffer_len - 1) {
    if (ascii_keyboard_stream.latest_idx > stream_idx) {
      char chr = get_from_key_stream(stream_idx);
      if (chr == '\n') break;
      if (chr == '\b') break;
      terminal_put(chr);
      buffer[buffer_idx] = chr;
      buffer_idx++;
      stream_idx++;
    }
  }

  buffer[buffer_idx] = '\n';
  vga_puts("\n");
  if (buffer_idx == (int)buffer_len - 1) return 1;
  else return 0;
}

