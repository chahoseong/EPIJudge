#include "test_framework/generic_test.h"

// lookup table을 사용하면 더 빠르게 문제를 풀 수 있다.
// 비트의 부분을 테이블의 키로 활용하여 미리 계산한 결과를 사용한다.
// 전체 비트를 분할할 다음 계산된 결과를 역순으로 합치면 된다.
// a b c d => rev(d) rev(c) rev(b) rev(a)

unsigned long long ReverseBits(unsigned long long x) {
	size_t bits = sizeof(x) * 8;
	unsigned long long r = 0;

	for (size_t i = bits; i > 0; --i) {
		r |= (x & 1) << (i - 1);
		x >>= 1;
	}

	return r;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "x" };
	return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
		&ReverseBits, DefaultComparator{}, param_names);
}
