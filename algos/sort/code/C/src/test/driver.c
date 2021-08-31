/* A very ugly testing code at the moment */

#include <mergesort.h>
#include <stdlib.h>
#include <stdio.h>

struct record {
  int key;
  int data;
};

typedef struct record record_t;

static int comp_fn(void *a, void *b) {
  return (*(int *)a) < (*(int *)b) ? 1 : 0;
}

static int comp_rec_fn(void *a, void *b) {
  record_t *reca = (record_t *)a, *recb = (record_t *)b;

  return reca->key < recb->key ? 1 : 0;
}

int main(void) {
  int arr[] = {5,1,2,3,4,0};
  size_t nmem = sizeof(arr) / sizeof(arr[0]);
  size_t size = sizeof(arr[0]);

  printf("Before sorting.\n");

  for (int i = 0; i < nmem; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  printf("\nAfter sorting.\n");

  merge_sort(arr, nmem, size, comp_fn);

  for (int i = 0; i < nmem; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // test sorting structures

  record_t rec[5];

  for (int i = 0; i < 5; ++i) {
    rec[i].key = 5 - i;
    rec[i].data = i;
  }

  printf("\nBefore sorting.\n");

  for (int i = 0; i < 5; ++i) {
    printf("rec.key=%d, rec.data=%d\n", rec[i].key, rec[i].data);
  }
  printf("\n");

  printf("After sorting.\n");

  nmem = 5;
  size = sizeof(record_t);
  merge_sort(rec, nmem, size, comp_rec_fn);

  for (int i = 0; i < nmem; ++i) {
    printf("rec.key=%d, rec.data=%d\n", rec[i].key, rec[i].data);
  }
  printf("\n");

  return 0;
}