#pragma once

#include <stddef.h>

// compare to `elements` based on the their keys.
typedef int comp_fn_t(void *, void *);

/**
 * @brief  A generic bubble sort implementation for sorting elements by `keys`
 * @note   
 * @param  *arr: pointer to an array of elements
 * @param  nele: number of elements
 * @param  size: size of each element
 * @param  comp: key comparing functions 
 * @retval None
 */
void bubble_sort(void *arr, size_t nele, size_t size, comp_fn_t comp);