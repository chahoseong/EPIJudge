#include <set>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
    //std::set<int> a;
    //for (int x : A) {
    //    a.insert(x);
    //}

    //std::set<int> b;
    //for (int x : B) {
    //    b.insert(x);
    //}

    //std::vector<int> result;
    //for (int x : a) {
    //    auto found = b.find(x);
    //    if (found != b.end()) {
    //        result.push_back(*found);
    //    }
    //}

    //return result;

    int x = 0;
    int y = 0;
    int last = 0;
    vector<int> result;

    while (x < A.size() && y < B.size()) {
        if (A[x] == B[y]) {
            if (result.empty() || last != A[x]) {
                result.push_back(A[x]);
                last = A[x];
            }
            ++x;
            ++y;
        }
        else {
            if (A[x] < B[y]) {
                ++x;
            }
            else {
                ++y;
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
