#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

int ReplaceAndRemove(int size, char s[]) {
	int write_idx = 0, a_count = 0;
	for (int i = 0; i < size; ++i) {
		if (s[i] != 'b') {
			s[write_idx++] = s[i];
		}
		if (s[i] == 'a') {
			++a_count;
		}
	}

	int cur_idx = write_idx - 1;
	write_idx = write_idx + a_count - 1;
	const int final_size = write_idx + 1;
	while (cur_idx >= 0) {
		if (s[cur_idx] == 'a') {
			s[write_idx--] = 'd';
			s[write_idx--] = 'd';
		}
		else {
			s[write_idx--] = s[cur_idx];
		}
		--cur_idx;
	}

	return final_size;
}


//int ReplaceAndRemove(int size, char s[]) {
//	vector<int> t(size);
//	
//	int step = 0;
//
//	for (int i = 0; i < size; ++i) {
//		if (s[i] == 'a') {
//			t[i] = step;
//			step += 1;
//		}
//		else if (s[i] == 'b') {
//			step -= 1;
//			t[i] = 0;
//		}
//		else {
//			t[i] = step;
//		}
//	}
//
//	for (int i = size - 1; i >= 0; --i) {
//		int step = t[i];
//		if (step > 0) {
//			s[i + step] = s[i];
//		}
//	}
//
//	for (int i = 0; i < size; ++i) {
//		int step = t[i];
//		if (step < 0) {
//			s[i + step] = s[i];
//		}
//	}
//
//	int newSize = size + step;
//
//	for (int i = 0; i < newSize; ++i) {
//		if (s[i] == 'a') {
//			s[i] = 'd';
//			s[i + 1] = 'd';
//		}
//		else if (s[i] == 'b') {
//			s[i] = s[i + 1];
//		}
//	}
//
//	return newSize;
//}

vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
	const vector<string>& s) {
	std::vector<char> s_copy(s.size(), '\0');
	for (int i = 0; i < s.size(); ++i) {
		if (!s[i].empty()) {
			s_copy[i] = s[i][0];
		}
	}

	int res_size =
		executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

	vector<string> result;
	for (int i = 0; i < res_size; ++i) {
		result.emplace_back(string(1, s_copy[i]));
	}
	return result;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "size", "s" };
	return GenericTestMain(args, "replace_and_remove.cc",
		"replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
		DefaultComparator{}, param_names);
}
