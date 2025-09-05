#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

vector<int> PlusOne(vector<int> A) {
	if (A.empty()) {
		return vector<int>();
	}

	A.back() += 1;
	int carry = A.back() / 10;
	A.back() %= 10;

	auto it = A.rbegin();
	++it;

	while (it != A.rend() && carry != 0) {
		*it += carry;
		carry = *it / 10;
		*it %= 10;
		++it;
	}

	if (carry) {
		A[0] = 1;
		A.push_back(0);
	}

	return A;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A" };
	return GenericTestMain(args, "int_as_array_increment.cc",
		"int_as_array_increment.tsv", &PlusOne,
		DefaultComparator{}, param_names);
}
