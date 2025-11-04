#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

// 시간 복잡도: O(N)
//int RomanToInteger(const string& s) {
//	std::unordered_map<char, int> roman_to_int;
//	roman_to_int['I'] = 1;
//	roman_to_int['V'] = 5;
//	roman_to_int['X'] = 10;
//	roman_to_int['L'] = 50;
//	roman_to_int['C'] = 100;
//	roman_to_int['D'] = 500;
//	roman_to_int['M'] = 1000;
//
//	int result = 0;
//	size_t index = 1;
//
//	if (s.size() == 1) {
//		result = roman_to_int[s.front()];
//	}
//	else {
//		while (index < s.size()) {
//			char curr = s[index];
//			char prev = s[index - 1];
//			int x = roman_to_int[curr];
//			int y = roman_to_int[prev];
//			if (x > y) {
//				result += x - y;
//				index += 2;
//			}
//			else {
//				result += y;
//				index += 1;
//			}
//		}
//
//		if (index - s.size() == 0) {
//			result += roman_to_int[s.back()];
//		}
//	}
//
//	return result;
//}

// 책에 나온 구현
int RomanToInteger(const string& s) {
	std::unordered_map<char, int> roman_to_int;
	roman_to_int['I'] = 1;
	roman_to_int['V'] = 5;
	roman_to_int['X'] = 10;
	roman_to_int['L'] = 50;
	roman_to_int['C'] = 100;
	roman_to_int['D'] = 500;
	roman_to_int['M'] = 1000;

	int result = roman_to_int[s.back()];

	for (int i = s.size() - 2; i >= 0; --i) {
		int curr = roman_to_int[s[i]];
		int next = roman_to_int[s[i + 1]];

		if (curr < next) {
			result -= curr;
		}
		else {
			result += curr;
		}
	}

	return result;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "s" };
	return GenericTestMain(args, "roman_to_integer.cc", "roman_to_integer.tsv",
		&RomanToInteger, DefaultComparator{}, param_names);
}
