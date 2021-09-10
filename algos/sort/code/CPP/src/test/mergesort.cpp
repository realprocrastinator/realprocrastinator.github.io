#include <mergesort.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

template<typename T>
void print(std::vector<T>& v) {
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << ' '; 
  }
  
  std::cout << '\n';
}

int main () {
  std::vector<int> v(30, 0);

  for (int i =  0; i < 30; ++i) {
    v[i] = 30 - i;
  }

  algo::merge_sort(v.begin(), v.end());

  print(v);
  
  return 0;
}