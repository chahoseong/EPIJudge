#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsPalindrome(const string& s) {
	if (s.length() <= 1) {
		return true;
	}
	
	int left = 0;
	int right = s.length() - 1;

	while (left < right) {
		if (std::isalnum(s[left]) && std::isalnum(s[right])) {
			if (std::tolower(s[left]) != std::tolower(s[right])) {
				return false;
			}
			++left;
			--right;
		}
		else {
			if (!std::isalnum(s[left])) {
				++left;
			}
			if (!std::isalnum(s[right])) {
				--right;
			}
		}
	}

	return true;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "s" };
	return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
		"is_string_palindromic_punctuation.tsv", &IsPalindrome,
		DefaultComparator{}, param_names);
}
