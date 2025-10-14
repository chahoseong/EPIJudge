#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

// 시간복잡도: O(N)
// 공간복잡도: O(N)
//void ReverseWords(string* s) {
//	size_t offset = 0;
//
//	std::vector<string> tokens;
//	while (true) {
//		size_t cursor = s->find(' ', offset);
//		if (cursor == string::npos) {
//			break;
//		}
//		tokens.emplace_back(s->substr(offset, cursor - offset));
//		offset = cursor + 1;
//	}
//	tokens.emplace_back(s->substr(offset));
//
//	s->clear();
//
//	for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
//		*s += *it;
//		s->push_back(' ');
//	}
//	s->pop_back();
//}

// 시간복잡도: O(N)
// 공간복잡도: O(1)
void ReverseWords(string* s) {
	std::reverse(s->begin(), s->end());

	size_t cursor = string::npos;
	size_t offset = 0;
	auto it = s->begin();

	do {
		cursor = s->find(' ', offset);
		if (cursor != string::npos) {
			std::reverse(it + offset, it + cursor);
			offset = cursor + 1;
		}
	} while (cursor != string::npos);

	std::reverse(it + offset, s->end());
}

string ReverseWordsWrapper(TimedExecutor& executor, string s) {
	string s_copy = s;

	executor.Run([&] { ReverseWords(&s_copy); });

	return s_copy;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "s" };
	return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
		&ReverseWordsWrapper, DefaultComparator{},
		param_names);
}
