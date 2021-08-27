/* A generic mergesort implementation which can sort any `records` based on the given `key`.
 * The code is written for self-learning purpose not for performance. 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <mergesort.h>

// short-hand for index/size coversion and pointer arithmetics 
#define IDXTOSZ(i, elesz) ((i) * (elesz))
#define SZTOIDX(i, elesz) ((sz) / (elesz))
#define NEWBASE(ptr, offset) ((void *)((uintptr_t)ptr + offset)) 

static void merge(void *data, int l, int mid, int r, size_t elesz, comp_fn_t comp_fn) {
  // number of elements on the left and right
  size_t nl = mid - l + 1;
  size_t nr = r - mid;

  // size of elements on the left and right 
  size_t lsz = IDXTOSZ(nl, elesz);
  size_t rsz = IDXTOSZ(nr, elesz);

  // temp storage for elements on the left and right. 
  // C99 allows us to do that :-)
  char tmpl[lsz];
  char tmpr[rsz];

  // we locate the new base where we need to copy the data  
  void *new_base = NEWBASE(data, l * elesz);
  memcpy(tmpl, new_base, lsz);
  memcpy(tmpr, NEWBASE(new_base, lsz), rsz);

  // offset in bytes
  size_t loffset, roffset;

  // i is the index on the left array of elements and j is the index of right array
  // of elements.
  // k if the index of where we need to a in-place copy
  int i = 0, j = 0, k = 0;
  while (i < nl && j < nr) {
    loffset = IDXTOSZ(i, elesz);
    roffset = IDXTOSZ(j, elesz);

    // we sort based on the user provided comparing funtion, move the element to the
    // front if function returns non-zero integer. 
    if (comp_fn(NEWBASE(tmpl, loffset), NEWBASE(tmpr, roffset))) {
      memcpy(NEWBASE(data, IDXTOSZ(k + l, elesz)), NEWBASE(tmpl, loffset), elesz);
      ++i;
    } else {
      memcpy(NEWBASE(data, IDXTOSZ(k + l, elesz)), NEWBASE(tmpr, roffset), elesz);
      ++j;
    }

    ++k;
  }

  // find the offset where contains the rest of the data 
  loffset = IDXTOSZ(i, elesz);
  roffset = IDXTOSZ(j, elesz);

  if (i < nl) {
    memcpy(NEWBASE(data, IDXTOSZ(k + l, elesz)), NEWBASE(tmpl, loffset), elesz * (nl - i));
    i += (nl - i);
  } 
  
  if (j < nr) {
    memcpy(NEWBASE(data, IDXTOSZ(k + l, elesz)), NEWBASE(tmpr, roffset), elesz * (nr - j));
    j += (nr - j);
  }
}

static void merge_sort_core(void *data, int l, int r, size_t elesz, comp_fn_t com_fn) {
  if (l < r) {
    // (l + r) might overflow! Do this instead :-) 
    int mid = l + (r - l) / 2;
    merge_sort_core(data, l, mid, elesz, com_fn);
    merge_sort_core(data, mid + 1, r, elesz, com_fn);
    merge(data, l, mid, r, elesz, com_fn);
  }
}

void merge_sort(void *data, size_t nmem, size_t size, comp_fn_t com_fn) {
  merge_sort_core(data, 0, nmem - 1, size, com_fn);
}