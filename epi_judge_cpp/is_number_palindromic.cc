#include "test_framework/generic_test.h"

// 내가 푼 방법
//bool IsPalindrome(const std::string& str)
//{
//	size_t left = 0;
//	size_t right = str.length() - 1;
//
//	while (left < right) {
//		if (str[left] != str[right]) {
//			return false;
//		}
//		++left;
//		--right;
//	}
//
//	return true;
//}
//
//bool IsPalindromeNumber(int x) {
//	std::string str = std::to_string(x);
//	return IsPalindrome(str);
//}

// 책에 나온 해답
bool IsPalindromeNumber(int x) {
	if (x <= 0) {
		return x == 0;
	}
	
	// 로그를 사용해서 숫자의 최대 자리수 구하기
	const int numDigits = static_cast<int>(floor(log10(x)) + 1);
	// 숫자의 최대 자리수에 있는 값을 읽어오기 위한 마스크
	int mask = static_cast<int>(pow(10, numDigits - 1));
	for (int i = 0; i < (numDigits / 2); ++i) {
		if (x / mask != x % 10) {
			return false;
		}
		x %= mask;	// 최대 자리수에 있는 값 제거
		x /= 10;	// 최소 자리수에 있는 값 제거
		mask /= 100;	// 위에서 숫자 2개를 제거했기 때문에 mask는 2자리 제거
	}

	return true;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "x" };
	return GenericTestMain(args, "is_number_palindromic.cc",
		"is_number_palindromic.tsv", &IsPalindromeNumber,
		DefaultComparator{}, param_names);
}
