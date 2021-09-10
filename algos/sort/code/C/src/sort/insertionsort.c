/* A generic Bubble Sort implementation for sorting elements */
#include <insertionsort.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

// short-hands for going to the previous element by adding offset 
#define PREV(ptr, offset) ((void *)((uintptr_t) ptr - offset))
// short-hands for getting the pointer to the element by adding offset
#define GET_ELE_BYOFFSET(ptr, offset) ((void *)((uintptr_t) (ptr) + (offset)))

void insertion_sort(void *arr, size_t nele, size_t size, comp_fn_t comp) {
  
  int i = 1;
  while (nele > 1) {
    // make a copy of the current to-be-insterted element
    char key[size]; 
    memcpy(key, GET_ELE_BYOFFSET(arr, i * size), size);
    
    // find an appropriate position to inster the element 
    int j = i;
    void *cur, *prev;
    while (j > 0) {
      cur  = GET_ELE_BYOFFSET(arr, j * size);
      prev = PREV(cur, size);
      
      // move the element one position ahead if necessary
      if (comp(key, prev)) {
        memcpy(cur, prev, size);
      } else {
        // correct position found
        break;
      }

      --j;
    }

    // insert the element
    cur  = GET_ELE_BYOFFSET(arr, j * size);
    memcpy(cur, key, size);

    ++i;
    --nele;
  }
}