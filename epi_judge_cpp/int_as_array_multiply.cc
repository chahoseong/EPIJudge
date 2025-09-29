#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> Multiply(vector<int> num1, vector<int> num2) {
	const int sign = (num1.front() < 0) ^ (num2.front() < 0) ? -1 : 1;
	
	num1.front() = std::abs(num1.front());
	num2.front() = std::abs(num2.front());

	vector<int> result(std::size(num1) + std::size(num2), 0);
	for (int i = std::size(num1) - 1; i >= 0; --i) {
		for (int j = std::size(num2) - 1; j >= 0; --j) {
			result[i + j + 1] += num1[i] * num2[j];
			result[i + j] += result[i + j + 1] / 10;
			result[i + j + 1] %= 10;
		}
	}

	// 0으로 시작하는 부분을 제거한다.
	result = vector<int>(std::find_if_not(std::begin(result), std::end(result), [](int v) { return v == 0; }), std::end(result));
	
	if (std::empty(result)) {
		return { 0 };
	}

	result.front() *= sign;
	return result;
}

//vector<int> Multiply(vector<int> num1, vector<int> num2) {
//	vector<int>* a = &num1;
//	vector<int>* b = &num2;
//
//	if (num2.size() > num1.size()) {
//		a = &num2;
//		b = &num1;
//	}
//
//	if (b->size() == 1 && b->front() == 0) {
//		return vector<int>(1, 0);
//	}
//
//	vector<int> result(1);
//	int cursor = 0;
//
//	for (int i = 0; i < b->size(); ++i) {
//		int x = *(b->rbegin() + i);
//		x = std::abs(x);
//
//		cursor = i;
//		int carry = 0;
//
//		for (int j = 0; j < a->size(); ++j) {
//			int y = *(a->rbegin() + j);
//			y = std::abs(y);
//
//			int z = carry + result[cursor] + (y * x);
//			result[cursor] = z % 10;
//			carry = z / 10;
//
//			++cursor;
//
//			if (cursor >= result.size()) {
//				result.emplace_back(0);
//			}
//		}
//
//		if (carry != 0)
//		{
//			if (cursor >= result.size()) {
//				result.emplace_back(carry);
//			}
//			else {
//				result[cursor] = carry;
//			}
//		}
//	}
//
//	if (result.back() == 0) {
//		result.pop_back();
//	}
//
//	int sign = 1;
//	if (a->front() < 0) {
//		sign = -1;
//	}
//	if (b->front() < 0) {
//		sign *= -1;
//	}
//
//	if (!result.empty())
//	{
//		result.back() *= sign;
//	}
//
//	std::reverse(result.begin(), result.end());
//
//	return result;
//}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "num1", "num2" };
	return GenericTestMain(args, "int_as_array_multiply.cc",
		"int_as_array_multiply.tsv", &Multiply,
		DefaultComparator{}, param_names);
}
