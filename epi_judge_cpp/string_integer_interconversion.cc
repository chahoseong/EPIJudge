#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
	string converted;

	int sign = x >= 0 ? 1 : -1;

	long long abs_x = std::abs(static_cast<long long>(x));
	while (abs_x) {
		int digit = abs_x % 10;
		converted.push_back('0' + digit);
		abs_x /= 10ll;
	}

	if (sign == -1) {
		converted.push_back('-');
	}
	
	if (converted.length() > 0) {
		std::reverse(converted.begin(), converted.end());
	}
	else {
		converted.push_back('0');
	}

	return converted;
}

int StringToInt(const string& s) {
	int result = 0;

	if (!s.empty()) {
		int sign = 1;
		if (s.front() == '-') {
			sign = -1;
		}

		for (char ch : s) {
			int digit = ch - '0';
			if (digit < 0 || digit > 9) {
				continue;
			}
			result = result * 10 + digit;
		}

		result *= sign;
	}

	return result;
}

void Wrapper(int x, const string& s) {
	if (stoi(IntToString(x)) != x) {
		throw TestFailure("Int to string conversion failed");
	}

	if (StringToInt(s) != x) {
		throw TestFailure("String to int conversion failed");
	}
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "x", "s" };
	return GenericTestMain(args, "string_integer_interconversion.cc",
		"string_integer_interconversion.tsv", &Wrapper,
		DefaultComparator{}, param_names);
}
