#include <map>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"

using std::map;
using std::string;
using std::vector;

// 시간 복잡도: O(N)
string SnakeString(const string& s) {
	int sin_value[] = { 0, 1, 0, -1 };

	map<int, string> table;
	int cursor = 0;

	for (size_t i = 0; i < s.size(); ++i) {
		table[sin_value[cursor]].push_back(s[i]);
		cursor = (cursor + 1) % 4;
	}

	string result;
	for (auto it = table.rbegin(); it != table.rend(); ++it) {
		result += it->second;
	}

	return result;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "s" };
	return GenericTestMain(args, "snake_string.cc", "snake_string.tsv",
		&SnakeString, DefaultComparator{}, param_names);
}
