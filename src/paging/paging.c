#include "paging/paging.h"


uint32_t page_directory   [1024] __attribute__((aligned(4096)));
uint32_t all_page_tables  [1024][1024] __attribute__((aligned(4096))); 
uint32_t first_page_table [1024] __attribute__((aligned(4096)));


void setup_paging()
{
  
  for (int i = 0; i < 1024; i++)
  {
    // Ring 0, Read-Write, Not Present
    page_directory[i] = 0x00000002;
  }

  for (int i = 0; i < 4; i++) {
    // Maps 4 MiB
    for (int j = 0; j < 1024; j++)
    {
      // Since * 0x1000, the final 12 bytes are zeros
      // Those zeros are used by the attributes
      all_page_tables[i][j] = (i * 1024 + j) * 0x1000 | 3;
    }
    page_directory[i] = ((unsigned int)all_page_tables[i]) | 3;
  }

  loadPageDirectory(page_directory);
  enablePaging();
}

