#include "test_framework/generic_test.h"

//double Power(double x, int y) {
//	if (y == 0) {
//		return 1.0;
//	}
//	
//	double result = 1.0;
//	for (int i = 1; i <= std::abs(y); ++i) {
//		result *= x;
//	}
//	return y < 0 ? 1.0 / result : result;
//}

//double Power(double x, int y) {
//	int y_abs = std::abs(y);
//
//	if (y_abs == 2) {
//		double result = x * x;
//		return y < 0 ? (1.0 / result) : result;
//	}
//	else if (y_abs == 1) {
//		return y < 0 ? (1.0 / x) : x;
//	}
//	else if (y == 0) {
//		return 1;
//	}
//
//	double half = Power(x, y / 2);
//	if (y % 2 == 0) {
//		return half * half;
//	}
//	else {
//		double r = half * half;
//		return y < 0 ? (r * (1.0 / x)) : r * x;
//	}
//}

// solution
double Power(double x, int y)
{
	double result = 1.0;
	long long power = y;
	if (y < 0) {
		power = -power;
		x = 1.0 / x;
	}
	while (power) {
		if (power & 1) {
			result *= x;
		}
		x *= x;
		power >>= 1;
	}
	return result;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "x", "y" };
	return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
		DefaultComparator{}, param_names);
}
