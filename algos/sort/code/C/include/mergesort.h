#pragma once

#include <stdlib.h>

// compare to `records` based on the their keys.
typedef int comp_fn_t(void *, void *);

/**
 * @brief  merge sort
 * @note   
 * @param  *data: The pointer to elements to be sorted
 * @param  nmem: number of elements to be sorted
 * @param  size: size of each element
 * @param  com_fn: function for comparing keys
 * @retval None
 */
void merge_sort(void *data, size_t nmem, size_t size, comp_fn_t com_fn);