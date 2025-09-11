#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool HasDuplicate(const vector<vector<int>>& partial_assignment,
	int start_row, int end_row, int start_col, int end_col)
{
	std::deque<bool> is_present(std::size(partial_assignment) + 1, false);
	for (int i = start_row; i < end_row; ++i) {
		for (int j = start_col; j < end_col; ++j) {
			if (partial_assignment[i][j] != 0 && is_present[partial_assignment[i][j]]) {
				return true;
			}
			is_present[partial_assignment[i][j]] = true;
		}
	}
	return false;
}

// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
	// row
	for (size_t i = 0; i < std::size(partial_assignment); ++i) {
		if (HasDuplicate(partial_assignment, i, i + 1, 0, std::size(partial_assignment))) {
			return false;
		}
	}

	// col
	for (size_t i = 0; i < partial_assignment.size(); ++i) {
		if (HasDuplicate(partial_assignment, 0, std::size(partial_assignment), i, i + 1)) {
			return false;
		}
	}

	int subsize = std::sqrt(partial_assignment.size());
	for (int i = 0; i < subsize; ++i) {
		for (int j = 0; j < subsize; ++j) {
			if (HasDuplicate(partial_assignment,
				subsize * i, subsize * (i + 1),
				subsize * j, subsize * (j + 1))) {
				return false;
			}
		}
	}

	return true;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "partial_assignment" };
	return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
		&IsValidSudoku, DefaultComparator{}, param_names);
}
