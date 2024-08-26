#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
	auto it = A.rbegin();

	int digit = *it + 1;
	int carry = digit / 10;
	*it = digit % 10;

	++it;

	while (it != A.rend()) {
		digit = *it + carry;
		carry = digit / 10;
		*it = digit % 10;

		if (carry == 0) {
			break;
		}

		++it;
	}

	if (carry != 0)
	{
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
