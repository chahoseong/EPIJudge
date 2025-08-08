#include "test_framework/generic_test.h"
#include <array>

// lookup table을 사용하면 더 빠르게 패리티를 구할 수 있다.
short Parity(unsigned long long x) {
	short result = 0;
	while (x) {
		result ^= 1;
		x &= (x - 1);
	}
	return result;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "x" };
	return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
		DefaultComparator{}, param_names);
}
