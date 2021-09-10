/* Generic Merge Sort, not designed for performance, just for self learning! */
#pragma once

#include <iterator>
#include <vector>

namespace algo {
  
  /* This is a helper function */
  template<typename RandomAccessItr, class Comp>
  static auto merge(RandomAccessItr first, RandomAccessItr mid, RandomAccessItr last, Comp comp) -> std::vector<typename RandomAccessItr::value_type> {
    using value_t = typename RandomAccessItr::value_type;

    // allocate a temporary buffer with size of last - first
    auto temp_buf = std::vector<value_t>();
    temp_buf.reserve((std::distance(first, last)));
    
    auto it_l = RandomAccessItr{first};
    auto it_r = RandomAccessItr{mid};
    auto temp_cur_it = temp_buf.begin();

    while (it_l != mid && it_r != last) {
        // use move semantic here to avoid copy!
        temp_buf.push_back(std::move(comp(*it_l, *it_r) ? *it_l++ : *it_r++));
        temp_cur_it++;
    }

    temp_buf.insert(temp_cur_it, it_l, mid);
    temp_buf.insert(temp_cur_it, it_r, last);

    return temp_buf;
  }

  /* This is a helper function actually implements the merge sort */
  template<typename RandomAccessItr, typename Compare>
  auto merge_sort_core(RandomAccessItr first, RandomAccessItr last, Compare comp) -> void {
    auto dist = std::distance(first, last);
    if (dist > 1) {
      auto mid = dist / 2;
      merge_sort_core(first, first + mid, comp);
      merge_sort_core(first + mid, last, comp);

      auto&& buf = merge(first, first + mid, last, comp); 
      std::move(buf.cbegin(), buf.cend(), first);
    }
  }  
  
  /**
   * @brief  Sort elements by accending order by default in a range of [*first, * (last - 1)]
   * @note   This is not a stable sort! Have no rules when key of elements are  same 
   * @param  first: iterator of the first element
   * @param  last: iterator of the last element
   * @retval void
   */
  template<typename RandomAccessItr>
  auto merge_sort(RandomAccessItr first, RandomAccessItr last) -> void {
    using value_t = typename RandomAccessItr::value_type;
    merge_sort_core(first, last, std::less<value_t>());
  }

  /**
  * @brief  Sort elements by accending order according to the comparing rules in a range of [*first, *(last - 1)]
  * @note    
  * @param  first: iterator of the first element
  * @param  last: iterator of the last element
  * @param  comp: comparing functions for elements' keys 
  * @retval void
  */
  template<typename RandomAccessItr, typename Compare>
  auto merge_sort(RandomAccessItr first, RandomAccessItr last, Compare comp) -> void {
    merge_sort_core(first, last, comp);
  }
} // namespace algo 
