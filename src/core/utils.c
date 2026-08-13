#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "utils.h"



size_t strlen(const char* str) {
	int i = 0;
	while (str[i]) i++;
	return (size_t)i;
}


int strcmp(const char* s1, const char* s2) {
	while(*s1 && (*s1 == *s2)) {
  	s1++;
  	s2++;
  }
  return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}


// CRITICAL: str MUST be of length 9 minimum

int hex_to_str(const unsigned int num, char *str)
{
	const char hex_chars[] = "0123456789ABCDEF";

	for (int i = 0; i < 8; i++) {
		uint8_t nybble = (num >> ((7 - i) * 4)) & 0xF;
		str[i] = hex_chars[nybble];
	}

	str[8] = '\0';
	return 0;
}


// CRICIAL: str MUST be of length 3 minimum

int uint8_hex_to_str(const uint8_t num, char *str)
{
	const char hex_chars[] = "0123456789ABCDEF";

	str[0] = hex_chars[num >> 4];
  str[1] = hex_chars[num & 0x0F];
	str[2] = '\0';
	
	return 0;
}

