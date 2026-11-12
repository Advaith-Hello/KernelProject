#pragma once

#include <stdint.h>


extern void loadPageDirectory(uint32_t*);
extern void enablePaging();

extern uint32_t page_directory   [1024];
extern uint32_t all_page_tables  [1024][1024];
extern uint32_t first_page_table [1024];

void setup_paging();

