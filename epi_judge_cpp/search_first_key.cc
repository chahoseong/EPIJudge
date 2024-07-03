#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
    bool is_existed = std::binary_search(std::begin(A), std::end(A), k);

    if (is_existed) {
        return std::lower_bound(std::begin(A), std::end(A), k) - std::begin(A);
    }
    else {
        return -1;
    }

    /*auto left = A.begin();
    auto right = A.end();

    int index = -1;

    while (left < right) {
        int size = right - left;
        auto mid = left + size / 2;
        int target = *mid;

        if (k <= target) {
            if (k == target) {
                index = mid - std::begin(A);
            }
            right = mid;
        }
        else if (k > target) {
            left = mid + 1;
        }
    }

    return index;*/
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
