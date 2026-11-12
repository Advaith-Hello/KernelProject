#include <stddef.h>

#include "paging/mapping.h"
#include "paging/paging.h"


void mmap_physical(void* addr_begin, size_t size)
{
  uintptr_t addr_begin_ = (uintptr_t)addr_begin;
  uintptr_t addr_end_   = (uintptr_t)addr_begin + size;

  for (uint32_t i = 0; i < 1024; i++)
  {
    uintptr_t page_start  = (uintptr_t)i * 1024 * 4096;
    uintptr_t page_end    = page_start + (1024 * 4096);

    if (page_end <= addr_begin_) continue;
    if (page_start >= addr_end_) break;

    for (uint32_t j = 0; j < 1024; j++)
    {
      uintptr_t phys_addr = (uintptr_t)(i * 1024 + j) * 4096;

      if (phys_addr >= addr_begin_ && phys_addr < addr_end_) {
        all_page_tables[i][j] = ((i * 0x400 + j) * 0x1000) | 3;;
      }
    }

    page_directory[i] = ((unsigned int)all_page_tables[i]) | 3;
  }

  loadPageDirectory(page_directory); 
}

