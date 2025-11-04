#include <string>
#include <sstream>

#include "test_framework/generic_test.h"
using std::string;

// 시간복잡도: O(N * 2^n)
// 최악의 경우, 현재 수열은 이전 수열의 두배 커질 수 있다.
string LookAndSay(int n) {
	string sequence = "1";

	for (int i = 1; i < n; ++i) {
		char ch = sequence.front();
		int count = 1;
		std::ostringstream oss;

		for (size_t j = 1; j < sequence.size(); ++j) {
			if (sequence[j] == ch) {
				++count;
			}
			else {
				oss << count << ch;

				count = 1;
				ch = sequence[j];
			}
		}

		oss << count << ch;

		sequence = oss.str();
	}

	return sequence;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "n" };
	return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
		&LookAndSay, DefaultComparator{}, param_names);
}
