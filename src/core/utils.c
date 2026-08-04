#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "utils.h"


size_t strlen(const char* str) {
	int i = 0;
	while (str[i]) i++;
	return (size_t)i;
}

