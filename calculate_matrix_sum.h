#ifndef CALCULATE_MATRIX_SUM_H
#define CALCULATE_MATRIX_SUM_H
#include <vector>
#include <cstdint>
#include <future>
#include "paginator.h"

using namespace std;

template<typename Container>
int64_t SumSingleThread(const Page<Container>& page){
  int64_t sum = 0;
  for(const auto& row : page){
    for (const auto& item : row) {
      sum += item;
    }
  }
  return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  int64_t result = 0;
  size_t page_size = matrix.size() / 4;
  //size_t first_row = 0;
  vector<future<int64_t>> futures;

  for(const auto& page : Paginate(matrix, page_size)) {
    futures.push_back(
      async([&page]{ return SumSingleThread(page); })
    );
  }
 // first_row += page_size;

  for(auto& item : futures){
    result += item.get();
  }
  return result;
}


#endif // CALCULATE_MATRIX_SUM_H
