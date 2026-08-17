#pragma once

#include <stdint.h>


extern uint32_t page_directory[1024];
extern uint32_t first_page_table[1024];

void setup_paging();

