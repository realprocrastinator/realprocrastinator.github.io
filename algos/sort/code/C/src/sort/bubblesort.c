/* A generic Bubble Sort implementation for sorting elements */
#include <bubblesort.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

// Go to the next element by adding offset 
#define NEXT(ptr, offset) ((void *)((uintptr_t) ptr + offset))
#define GET_ELE_BYOFFSET(ptr, offset) ((void *)((uintptr_t) (ptr) + (offset)))

static void swap(void *lele, void *rele, size_t size) {
  // C99 allows us to do this :D
  char tmp[size];
  memcpy(tmp, lele, size);
  memcpy(lele, rele, size);
  memcpy(rele, tmp, size);
}

void bubble_sort(void *arr, size_t nele, size_t size, comp_fn_t comp) {
  int is_swapped = 0;
  
  void *cur = arr;

  size_t i = 0;
  while (i < nele) {
    // for the ith element, need to compare n - 1 - i times 
    size_t j = 0;
    while (j < nele - 1 - i) {
      cur = GET_ELE_BYOFFSET(arr, j * size);
      // If the rules user expected doesn't hold, we swap the elements
      if (!comp(cur, NEXT(cur, size))) {
        swap(cur, NEXT(cur, size), size);
        is_swapped = 1;
      }

      ++j;
    }

    if (!is_swapped) {
      break;
    }     
    
    ++i;
  }
}