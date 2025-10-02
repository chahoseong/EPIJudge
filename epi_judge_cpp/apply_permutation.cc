#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void ApplyPermutation(vector<int> perm, vector<int>* A_ptr) {
	vector<int>& sequence = *A_ptr;
	size_t index = 0;

	while (index < perm.size()) {
		int next = perm[index];
		if (index == next) {
			++index;
		}
		else {
			std::swap(sequence[index], sequence[next]);
			std::swap(perm[next], perm[index]);
		}
	}

}
vector<int> ApplyPermutationWrapper(const vector<int>& perm, vector<int> A) {
	ApplyPermutation(perm, &A);
	return A;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "perm", "A" };
	return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
		&ApplyPermutationWrapper, DefaultComparator{},
		param_names);
}
